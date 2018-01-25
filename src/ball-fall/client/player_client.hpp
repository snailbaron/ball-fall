#pragma once

#include "game_state.hpp"
#include "../events.hpp"

#include <SDL2/SDL.h>

#include <memory>

class PlayerClient : public evening::Subscriber {
public:
    PlayerClient();

    void processEvent(const SDL_Event& event);
    void update(double delta);
    void render() const;

    bool active() const;

private:
    bool _active = true;
    std::unique_ptr<GameState> _gameState;
};
