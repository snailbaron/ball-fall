#include "widgets.hpp"
#include "resources.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>

void SolidBackground::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Button::render(SDL_Renderer* renderer) const
{
    static constexpr auto BorderSize = 5;
    static constexpr auto BorderColor = Color(100, 50, 50);
    static constexpr auto BgColor = Color(150, 150, 100);

    SDL_SetRenderDrawColor(
        renderer, BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
    SDL_Rect outerRect {position.x, position.y, size.x, size.y};
    SDL_RenderFillRect(renderer, &outerRect);

    SDL_SetRenderDrawColor(
        renderer, BgColor.r, BgColor.g, BgColor.b, BgColor.a);
    SDL_Rect innerRect {
        outerRect.x + BorderSize,
        outerRect.y + BorderSize,
        outerRect.w - 2 * BorderSize,
        outerRect.h - 2 * BorderSize};
    SDL_RenderFillRect(renderer, &innerRect);

    TTF_Font* font = res::font(res::FontId::MechaBold, innerRect.h);
    int w;
    TTF_SizeUTF8(font, text.c_str(), &w, nullptr);
    if (w > innerRect.w) {
        int fixedSize = innerRect.h * innerRect.w / w;
        font = res::font(res::FontId::Mecha, fixedSize);
    }
    SDL_Surface* surface = TTF_RenderUTF8_Shaded(
        font,
        text.c_str(),
        SDL_Color{0, 0, 0, 255},
        SDL_Color{BgColor.r, BgColor.g, BgColor.b, BgColor.a});
    SDL_Rect dstRect {
        innerRect.x + (innerRect.w - surface->w) / 2,
        innerRect.y + (innerRect.h - surface->h) / 2,
        surface->w,
        surface->h};

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);




    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}