#include "surface_impl.hpp"

#include <cassert>
#include <utility>

namespace sdl {

SurfaceImpl::SurfaceImpl(
        std::shared_ptr<Library> library, SDL_Surface* surface)
    : _library(std::move(library))
    , _surface(surface, SDL_FreeSurface)
{
    assert(_library);
    assert(_surface);
}

} // namespace sdl
