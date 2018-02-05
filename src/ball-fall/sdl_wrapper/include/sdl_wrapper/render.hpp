#pragma once

#include "internal/wrapper.hpp"

#include <SDL2/SDL_render.h>

namespace sdl {

class Texture : public internal::Wrapper<SDL_Texture, SDL_DestroyTexture> {
public:
    using Wrapper::Wrapper;
};

class RendererImpl
    : public internal::Wrapper<SDL_Renderer, SDL_DestroyRenderer> {
public:
    using Wrapper::Wrapper;
};

} // namespace sdl