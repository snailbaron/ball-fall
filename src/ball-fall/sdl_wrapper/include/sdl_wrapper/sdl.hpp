#pragma once

#include <cstdint>

namespace sdl {

void init(uint32_t flags)
{
    SDL_Init(flags);
}

void quit()
{
    SDL_Quit();
}

} // namespace sdl
