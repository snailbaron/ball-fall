#pragma once

#include "game_state.hpp"
#include "scene.hpp"

#include <SDL2/SDL.h>

class Gameplay : public GameState {
public:
    Gameplay();

    void processEvent(const SDL_Event& event) override;
    void render() const override;

private:
    Scene _scene;
};