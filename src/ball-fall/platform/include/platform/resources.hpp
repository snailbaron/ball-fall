#pragma once

#include <platform/visuals.hpp>

#include <resource_ids.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

class Resources {
public:
    virtual ~Resources() {}

    virtual void load() = 0;
    virtual void clear() = 0;

    virtual TTF_Font* Resources::font(res::FontId fontId, int ptSize) = 0;
    virtual const Texture& Resources::texture(res::BitmapId bitmapId) = 0;
};
