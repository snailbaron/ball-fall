#pragma once

#include <sdl_wrapper/internal/wrapper.hpp>

#include <SDL2/SDL_render.h>

namespace sdl {

class Texture : public internal::Wrapper<SDL_Texture, SDL_DestroyTexture> {
public:
    using Wrapper::Wrapper;
    using Wrapper::reset;
};

class Renderer : public internal::Wrapper<SDL_Renderer, SDL_DestroyRenderer> {
public:
    using Wrapper::Wrapper;
    using Wrapper::reset;
};

} // namespace sdl