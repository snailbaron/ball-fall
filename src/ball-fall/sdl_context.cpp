#include "sdl_context.hpp"
#include "config.hpp"

#include <stdexcept>

SdlContext::SdlContext()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        throw std::runtime_error("SDL_Init failed");
    }

    _window = SDL_CreateWindow(
        config::WindowTitle,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config::WindowWidth,
        config::WindowHeight,
        0);
    if (!_window) {
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    _renderer = SDL_CreateRenderer(
        _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
        throw std::runtime_error("SDL_CreateRenderer failed");
    }
}

SdlContext::~SdlContext()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}