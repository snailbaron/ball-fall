#include "player_client.hpp"
#include "../config.hpp"
#include "resources.hpp"
#include "game_states/main_menu.hpp"
#include "game_states/gameplay.hpp"
#include "media.hpp"

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

    _gameState = std::make_unique<MainMenu>();

    render();
    SDL_ShowWindow(media::window());
}

void PlayerClient::processEvent(const SDL_Event& event)
{
    if (event.type == SDL_QUIT) {
        _active = false;
        return;
    }
    _gameState->processEvent(event);
}

void PlayerClient::update(double delta)
{
    _gameState->update(delta);
}

void PlayerClient::render() const
{
    SDL_SetRenderDrawColor(media::renderer(), 0, 0, 0, 255);
    SDL_RenderClear(media::renderer());

    _gameState->render();

    SDL_RenderPresent(media::renderer());
}

bool PlayerClient::active() const
{
    return _active;
}
