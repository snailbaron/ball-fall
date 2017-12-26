#include "widgets.hpp"

#include <SDL2/SDL.h>

void SolidBackground::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}