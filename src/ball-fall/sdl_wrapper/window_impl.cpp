#include "window_impl.hpp"
#include "renderer_impl.hpp"

#include <cassert>
#include <utility>

namespace sdl {

WindowImpl::WindowImpl(std::shared_ptr<Library> library, SDL_Window* window)
    : _library(std::move(library))
    , _window(window, SDL_DestroyWindow)
{
    assert(_library);
    assert(_window);
}

std::shared_ptr<Renderer> WindowImpl::createRenderer(
    int index, std::uint32_t flags) const
{
    SDL_Renderer* renderer = SDL_CreateRenderer(_window.get(), index, flags);
    return std::make_shared<RendererImpl>(shared_from_this(), renderer);
}

} // namespace sdl
