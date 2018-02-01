#include "player_client.hpp"
#include <config.hpp>
#include "game_states/main_menu.hpp"
#include "game_states/gameplay.hpp"
#include <platform.hpp>

#include <SDL2/SDL.h>

#include <stdexcept>
#include <utility>
#include <type_traits>

PlayerClient::PlayerClient()
{
    subscribe<evt::Quit>(evt::bus(), [this] (const auto&) {
        _active = false;
    });
    subscribe<evt::NewGame>(evt::bus(), [this] (const auto&) {
        _gameState = std::make_unique<Gameplay>();
    });

    subscribe<SDL_Event>(evt::input(), [this] (const auto& event) {
        if (event.type == SDL_QUIT) {
            _active = false;
            return;
        }
        _gameState->processEvent(event);
    });

    _gameState = std::make_unique<MainMenu>();

    render();
    platform::screen().show();
}

void PlayerClient::update(double delta)
{
    _gameState->update(delta);
}

void PlayerClient::render() const
{
    platform::screen().clear(Color::Black);

    _gameState->render();

    platform::screen().present();
}

bool PlayerClient::active() const
{
    return _active;
}

std::unique_ptr<Client> makePlayerClient()
{
    return std::make_unique<PlayerClient>();
}