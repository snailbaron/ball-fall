#pragma once

#include <SDL2/SDL.h>

namespace media {

void init();
void kill();

SDL_Window* window();
SDL_Renderer* renderer();

} // namespace media
