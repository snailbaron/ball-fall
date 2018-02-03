#pragma once

#include "resources.hpp"
#include "lru_cache.hpp"
#include "static_platform.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <util.hpp>
#include <config.hpp>

namespace flat = BallFall::Resources;

using static_platform::renderer;

Resources::Resources()
    : _sizedFonts(
        20,
        [this] (res::FontId fontId, int ptSize) {
            return loadFont(fontId, ptSize);
        })
{ }

void Resources::load()
{
    auto resourceData = util::readFile(config::ResourceFile);
    const auto* resources = flat::GetResources(resourceData.data());

    for (const auto& font : *resources->fonts()) {
        _fonts.emplace_back(
            font->data()->data(),
            font->data()->data() + font->data()->size());
    }

    for (const auto& bitmap : *resources->bitmaps()) {
        auto rawSurface =
            IMG_Load_RW(
                SDL_RWFromConstMem(
                    bitmap->data()->data(), bitmap->data()->size()), 0);

        int width = rawSurface->w;
        int height = rawSurface->h;

        auto rawTexture =
            SDL_CreateTextureFromSurface(renderer(), surface.raw());

        std::shared_ptr<Texture> texture = std::make_shared<TextureImpl>(
            {width, height}, rawTexture);

        SDL_FreeSurface(surface);
        _textures.push_back(texture);
    }
}

void Resources::clear()
{
    _sizedFonts.clear();
    _fonts.clear();
    _textures.clear();
}

std::shared_ptr<Font> Resources::font(res::FontId fontId, int ptSize)
{
    return _sizedFonts.get(fontId, ptSize).get();
}

std::shared_ptr<Texture> Resources::texture(res::BitmapId bitmapId)
{
    return _textures.at(static_cast<size_t>(bitmapId));
}

std::shared_ptr<Font> Resources::loadFont(res::FontId fontId, int ptSize) const
{
    auto index = static_cast<size_t>(fontId);
    const auto& fontData = _fonts.at(index);
    TTF_Font* rawPtr = TTF_OpenFontRW(
        SDL_RWFromConstMem(fontData.data(), (int)fontData.size()), 0, ptSize);
    return std::make_shared<FontImpl>(rawPtr);
}