#pragma once

#include "game_states/game_state.hpp"
#include <client.hpp>
#include <platform/screen.hpp>
#include <platform/resources.hpp>

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
    Screen _screen;
    Resources _resources;
    std::unique_ptr<GameState> _gameState;
};
