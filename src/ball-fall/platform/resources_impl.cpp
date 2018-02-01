#pragma once

#include "resources_impl.hpp"
#include "lru_cache.hpp"
#include "screen_impl.hpp"

#include <platform.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <util.hpp>
#include <config.hpp>

namespace flat = BallFall::Resources;

ResourcesImpl::ResourcesImpl()
    : _sizedFonts(
        20,
        [this] (res::FontId fontId, int ptSize) {
            return loadFont(fontId, ptSize);
        })
{ }

void ResourcesImpl::load()
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

        auto& screenImpl = dynamic_cast<ScreenImpl&>(platform::screen());

        SDL_Texture* texture = SDL_CreateTextureFromSurface(screenImpl.renderer(), surface);
        int width = surface->w;
        int height = surface->h;
        SDL_FreeSurface(surface);
        _textures.emplace_back(width, height, texture);
    }
}

void ResourcesImpl::clear()
{
    _sizedFonts.clear();
    _fonts.clear();
    _textures.clear();
}

TTF_Font* ResourcesImpl::font(res::FontId fontId, int ptSize)
{
    return _sizedFonts.get(fontId, ptSize).get();
}

const Texture& ResourcesImpl::texture(res::BitmapId bitmapId)
{
    return _textures.at(static_cast<size_t>(bitmapId));
}

ResourcesImpl::FontPtr ResourcesImpl::loadFont(res::FontId fontId, int ptSize)
{
    auto index = static_cast<size_t>(fontId);
    const auto& fontData = _fonts.at(index);
    TTF_Font* rawPtr = TTF_OpenFontRW(
        SDL_RWFromConstMem(fontData.data(), (int)fontData.size()), 0, ptSize);
    return {rawPtr, TTF_CloseFont};
}