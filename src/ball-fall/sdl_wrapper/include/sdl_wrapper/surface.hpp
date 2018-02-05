#pragma once

#include <sdl_wrapper/internal/wrapper.hpp>

namespace sdl {

class Surface : public internal::Wrapper<SDL_Surface, SDL_FreeSurface> {
public:
    using Wrapper::Wrapper;
    using Wrapper::reset;
};

} // namespace sdl
