#include "screen_impl.hpp"

#include <client/config.hpp>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <stdexcept>
#include <cassert>

namespace platform {

ScreenImpl::ScreenImpl()
{
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

ScreenImpl::~ScreenImpl()
{
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;

    SDL_DestroyWindow(_window);
    _window = nullptr;
}

void ScreenImpl::clear(const Color& color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(_renderer);
}

void ScreenImpl::drawRoundedBox(
    const Vector<int16_t>& position,
    const Vector<int16_t>& size,
    int16_t cornerRadius,
    const Color& color)
{
    int result = roundedBoxRGBA(
        _renderer,
        position.x, position.y, position.x + size.x, position.y + size.y,
        cornerRadius,
        color.r, color.g, color.b, color.a);
    assert(result == 0);
}

} // namespace platform
