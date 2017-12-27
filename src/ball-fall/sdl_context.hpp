#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SdlContext {
public:
    SdlContext();
    ~SdlContext();

    SDL_Window* window() const { return _window; }
    SDL_Renderer* renderer() const { return _renderer; }

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
};