#include "resources.hpp"
#include "lru_cache.hpp"

#include <resources_generated.h>
#include <util.hpp>

#include <vector>
#include <fstream>
#include <cstdint>
#include <memory>

namespace flat = BallFall::Resources;

namespace res {

namespace {

TTF_Font* loadFont(FontId fontId, int ptSize);

std::vector<std::vector<uint8_t>> g_fonts;
MultiKeyLruCache<TTF_Font*, FontId, int> g_sizedFonts(20, loadFont);
std::vector<std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>> g_textures;

TTF_Font* loadFont(FontId fontId, int ptSize)
{
    auto index = static_cast<size_t>(fontId);
    const auto& fontData = g_fonts.at(index);
    return TTF_OpenFontRW(
        SDL_RWFromConstMem(fontData.data(), (int)fontData.size()), 0, ptSize);
}

} // namespace

void load(const std::string& resourceFile, SDL_Renderer* renderer)
{
    auto resourceData = util::readFile(resourceFile);
    const auto* resources = flat::GetResources(resourceData.data());

    for (const auto& font : *resources->fonts()) {
        g_fonts.emplace_back(
            font->data()->data(),
            font->data()->data() + font->data()->size());
    }

    //for (const auto& bitmap : *resources->bitmaps()) {
    //    SDL_Surface* surface =
    //        IMG_Load_RW(
    //            SDL_RWFromConstMem(
    //                bitmap->data()->data(), bitmap->data()->size()), 0);
    //    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    //    SDL_FreeSurface(surface);
    //    g_textures.push_back(
    //        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(
    //            texture, SDL_DestroyTexture));
    //}
}

TTF_Font* font(res::FontId fontId, int ptSize)
{
    return g_sizedFonts.get(fontId, ptSize);
}

const SDL_Texture* texture(res::BitmapId bitmapId)
{
    return g_textures.at(static_cast<size_t>(bitmapId)).get();
}

} // namespace res
