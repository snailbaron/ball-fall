#pragma once

#include "window_impl.hpp"

#include <sdl_wrapper/renderer.hpp>

#include <SDL2/SDL.h>

#include <memory>

namespace sdl {

class RendererImpl {
public:
    RendererImpl(std::shared_ptr<Window> window, SDL_Renderer* renderer);

private:
    std::shared_ptr<WindowImpl> _window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> _renderer;
};

} // namespace sdl
