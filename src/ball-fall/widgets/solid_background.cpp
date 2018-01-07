#include "solid_background.hpp"
#include "../client.hpp"

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
