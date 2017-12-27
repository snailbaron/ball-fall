#include "widgets.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void SolidBackground::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Button::render(SDL_Renderer* renderer) const
{
    static constexpr auto BorderSize = 10;
    static constexpr auto BorderColor = Color(50, 50, 50);
    static constexpr auto BgColor = Color(100, 100, 100);

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


}