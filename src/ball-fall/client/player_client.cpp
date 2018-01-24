#include "player_client.hpp"
#include "../config.hpp"
#include "resources.hpp"
#include "widgets/main_menu.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <utility>
#include <type_traits>

PlayerClient::PlayerClient()
{
    subscribe<evt::Quit>(evt::bus(), [this] (const auto&) {
        _active = false;
    });

    _resources.load(_context.renderer());
    _widgets.push_back(std::make_unique<MainMenu>(_context.renderer(), _resources));

    render();
    SDL_ShowWindow(_context.window());
}

void PlayerClient::processInput(const SDL_Event& event)
{
    if (event.type == SDL_QUIT) {
        _active = false;
        return;
    }

    for (auto& widget : _widgets) {
        widget->processEvent(event);
    }
}

void PlayerClient::update(double delta)
{
    for (auto& widget : _widgets) {
        widget->update(delta);
    }
}

void PlayerClient::render() const
{
    for (const auto& widget : _widgets) {
        widget->render();
    }
    SDL_RenderPresent(_context.renderer());
}

bool PlayerClient::active() const
{
    return _active;
}

TTF_Font* PlayerClient::font(res::FontId fontId, int ptSize)
{
    return _resources.font(fontId, ptSize);
}

const SDL_Texture* PlayerClient::texture(res::BitmapId bitmapId)
{
    return _resources.texture(bitmapId);
}
