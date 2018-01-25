#pragma once

#include <SDL2/SDL.h>

class GameState {
public:
    virtual void processEvent(const SDL_Event& event) = 0;
    virtual void update(double delta) = 0;
    virtual void render() const = 0;
};