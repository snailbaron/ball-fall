#pragma once

#include <resource_ids.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace resources {

void load(SDL_Renderer* renderer);
void clear();

TTF_Font* font(res::FontId fontId, int ptSize);
SDL_Texture* texture(res::BitmapId bitmapId);

} // namespace resources
