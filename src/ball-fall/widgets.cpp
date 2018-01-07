#include "widgets.hpp"
#include "client.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <utility>

SolidBackground& SolidBackground::color(const Color& color)
{
    _color = color;
    return *this;
}

void SolidBackground::render() const
{
    SDL_SetRenderDrawColor(renderer(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderClear(renderer());
}

Button& Button::position(int x, int y)
{
    _position = {x, y};
    return *this;
}

Button& Button::size(int width, int height)
{
    auto sizeVector = Vector<int>(width, height);
    if (_size != sizeVector) {
        _size = sizeVector;
        recalculateTexture();
    }
    return *this;
}

Button& Button::text(std::string text)
{
    if (text != _text) {
        _text = std::move(text);
        recalculateTexture();
    }
    return *this;
}

void Button::render() const
{
    SDL_SetRenderDrawColor(
        renderer(), BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
    SDL_Rect outerRect {_position.x, _position.y, _size.x, _size.y};
    SDL_RenderFillRect(renderer(), &outerRect);

    SDL_SetRenderDrawColor(
        renderer(), BgColor.r, BgColor.g, BgColor.b, BgColor.a);
    SDL_Rect innerRect {
        outerRect.x + BorderSize,
        outerRect.y + BorderSize,
        outerRect.w - 2 * BorderSize,
        outerRect.h - 2 * BorderSize};
    SDL_RenderFillRect(renderer(), &innerRect);

    SDL_Rect dstRect {
        innerRect.x + (innerRect.w - _textureSize.x) / 2,
        innerRect.y + (innerRect.h - _textureSize.y) / 2,
        _textureSize.x,
        _textureSize.y};

    if (_texture) {
        SDL_RenderCopy(renderer(), _texture, nullptr, &dstRect);
    }
}

void Button::recalculateTexture()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    const int targetWidth = _size.x - 2 * BorderSize;

    int height = _size.y - 2 * BorderSize;
    TTF_Font* font = client().font(Font, height);
    int width;
    TTF_SizeUTF8(font, _text.c_str(), &width, nullptr);
    while (width > targetWidth) {
        height = height * targetWidth / width;
        font = client().font(res::FontId::Mecha, height);
        TTF_SizeUTF8(font, _text.c_str(), &width, nullptr);
    }
    SDL_Surface* surface = TTF_RenderUTF8_Shaded(
        font,
        _text.c_str(),
        SDL_Color{0, 0, 0, 255},
        SDL_Color{BgColor.r, BgColor.g, BgColor.b, BgColor.a});
    if (surface) {
        _textureSize.x = surface->w;
        _textureSize.y = surface->h;

        _texture = SDL_CreateTextureFromSurface(renderer(), surface);
        SDL_FreeSurface(surface);
    }
}