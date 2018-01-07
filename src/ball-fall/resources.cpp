#include "resources.hpp"
#include "config.hpp"

#include <resources_generated.h>
#include <util.hpp>

#include <fstream>

namespace flat = BallFall::Resources;

Resources::Resources()
    : _sizedFonts(
        20,
        [this] (res::FontId fontId, int ptSize) {
            return loadFont(fontId, ptSize);
        })
{ }

void Resources::load(SDL_Renderer* renderer)
{
    auto resourceData = util::readFile(config::ResourceFile);
    const auto* resources = flat::GetResources(resourceData.data());

    auto len = resources->fonts()->Length();
    auto p0 = resources->fonts()->Get(0);
    auto p1 = resources->fonts()->Get(1);
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

TTF_Font* Resources::font(res::FontId fontId, int ptSize)
{
    return _sizedFonts.get(fontId, ptSize).get();
}

const SDL_Texture* Resources::texture(res::BitmapId bitmapId)
{
    return _textures.at(static_cast<size_t>(bitmapId)).get();
}

Resources::FontPtr Resources::loadFont(res::FontId fontId, int ptSize)
{
    auto index = static_cast<size_t>(fontId);
    const auto& fontData = _fonts.at(index);
    TTF_Font* rawPtr = TTF_OpenFontRW(
        SDL_RWFromConstMem(fontData.data(), (int)fontData.size()), 0, ptSize);
    return {rawPtr, TTF_CloseFont};
}
