#pragma once

#include "sdl_library_impl.hpp"

#include <sdl_wrapper/surface.hpp>

#include <SDL2/SDL.h>

#include <memory>

namespace sdl {

class SurfaceImpl : public Surface {
public:
    SurfaceImpl(std::shared_ptr<Library> library, SDL_Surface* surface);

private:
    std::shared_ptr<LibraryImpl> _library;
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> _surface;
};

} // namespace sdl
