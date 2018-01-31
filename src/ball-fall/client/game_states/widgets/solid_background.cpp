#include "solid_background.hpp"
#include "../../media.hpp"

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
    media::screen().clear(_color);
}
