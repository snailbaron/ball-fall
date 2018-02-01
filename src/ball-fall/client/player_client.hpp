#pragma once

#include "game_states/game_state.hpp"
#include <client/client.hpp>
#include <platform/events.hpp>

#include <SDL2/SDL.h>

#include <memory>

class PlayerClient
        : public Client
        , public evening::Subscriber {
public:
    PlayerClient();

    void update(double delta) override;
    void render() const override;

    bool active() const override;

private:
    bool _active = true;
    std::unique_ptr<GameState> _gameState;
};
