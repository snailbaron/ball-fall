#pragma once

#include "lru_cache.hpp"

#include <platform/resources.hpp>

#include <memory>
#include <vector>

namespace platform {

class ResourcesImpl {
public:
    ResourcesImpl()
        : _sizedFonts(
            20,
            [this] (res::FontId fontId, int ptSize) {
                return loadFont(fontId, ptSize);
            })
    { }

    void load(SDL_Renderer* renderer)
    {
        auto resourceData = util::readFile(config::ResourceFile);
        const auto* resources = flat::GetResources(resourceData.data());

        for (const auto& font : *resources->fonts()) {
            _fonts.emplace_back(
                font->data()->data(),
                font->data()->data() + font->data()->size());
        }

        for (const auto& bitmap : *resources->bitmaps()) {
            SDL_Surface* surface =
                IMG_Load_RW(
                    SDL_RWFromConstMem(
                        bitmap->data()->data(), bitmap->data()->size()), 0);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            _textures.push_back(
                std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(
                    texture, SDL_DestroyTexture));
        }
    }

    TTF_Font* ResourcesImpl::font(res::FontId fontId, int ptSize)
    {
        return _sizedFonts.get(fontId, ptSize).get();
    }

    SDL_Texture* ResourcesImpl::texture(res::BitmapId bitmapId)
    {
        return _textures.at(static_cast<size_t>(bitmapId)).get();
    }

private:
    using TexturePtr = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;
    using FontPtr = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>;

    ResourcesImpl::FontPtr ResourcesImpl::loadFont(res::FontId fontId, int ptSize)
    {
        auto index = static_cast<size_t>(fontId);
        const auto& fontData = _fonts.at(index);
        TTF_Font* rawPtr = TTF_OpenFontRW(
            SDL_RWFromConstMem(fontData.data(), (int)fontData.size()), 0, ptSize);
        return {rawPtr, TTF_CloseFont};
    }

    std::vector<std::vector<uint8_t>> _fonts;
    MultiKeyLruCache<FontPtr, res::FontId, int> _sizedFonts;
    std::vector<TexturePtr> _textures;
};

} // namespace platform
