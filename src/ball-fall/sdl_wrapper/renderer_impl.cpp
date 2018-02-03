#include "renderer_impl.hpp"

#include <cassert>
#include <utility>

namespace sdl {

RendererImpl::RendererImpl(
        std::shared_ptr<Window> window, SDL_Renderer* renderer)
    : _window(std::move(window))
    , _renderer(renderer, SDL_DestroyRenderer)
{
    assert(window);
    assert(_renderer);
}

} // namespace sdl