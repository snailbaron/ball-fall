#include "screen_impl.hpp"

#include <config.hpp>
#include <platform.hpp>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <stdexcept>
#include <cassert>

namespace {

SDL_Color sdlColor(const Color& color)
{
    return {color.r, color.g, color.b, color.a};
}

} // namespace

const Color Color::Black {0, 0, 0};

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

void ScreenImpl::show()
{
    SDL_ShowWindow(_window);
}

void ScreenImpl::clear(const Color& color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(_renderer);
}

void ScreenImpl::present()
{
    SDL_RenderPresent(_renderer);
}

void ScreenImpl::drawRect(
    const Vector<int>& position, const Vector<int>& size, const Color& color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect {position.x, position.y, size.x, size.y};
    SDL_RenderFillRect(_renderer, &rect);
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

void ScreenImpl::drawTexture(
    const Vector<int>& position,
    const Texture& texture)
{
    SDL_Rect dstRect {
        position.x,
        position.y,
        position.x + texture.width,
        position.y + texture.height
    };
    SDL_RenderCopy(_renderer, texture.ptr, nullptr, &dstRect);
}

Texture ScreenImpl::textTexture(
    const std::string& text,
    res::FontId font,
    const Color& textColor,
    const Color& bgColor,
    const Vector<int>& desiredSize)
{
    int height = desiredSize.y;
    TTF_Font* fontPtr = platform::resources().font(font, height);
    int width;
    TTF_SizeUTF8(fontPtr, text.c_str(), &width, nullptr);
    while (width > desiredSize.x) {
        height = height * desiredSize.x / width;
        fontPtr = platform::resources().font(font, height);
        TTF_SizeUTF8(fontPtr, text.c_str(), &width, nullptr);
    }

    SDL_Surface* surface = TTF_RenderUTF8_Shaded(
        fontPtr,
        text.c_str(),
        sdlColor(textColor),
        sdlColor(bgColor));
    Texture texture(
        surface->w,
        surface->h,
        SDL_CreateTextureFromSurface(_renderer, surface));
    SDL_FreeSurface(surface);

    return texture;
}
