#pragma once

#include "internal/wrapper.hpp"

namespace sdl {

class Surface : public internal::Wrapper<SDL_Surface, SDL_FreeSurface> {
public:
    using Wrapper::Wrapper;
};

} // namespace sdl
