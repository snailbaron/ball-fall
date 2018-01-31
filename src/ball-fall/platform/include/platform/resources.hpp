#pragma once

#include <resource_ids.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace platform {

class Resources {
public:
    virtual ~Resources() {}

    virtual void load() = 0;
    virtual void clear() = 0;

    virtual TTF_Font* Resources::font(res::FontId fontId, int ptSize) = 0;
    virtual SDL_Texture* Resources::texture(res::BitmapId bitmapId) = 0;
};

} // namespace platform
