#include "client.hpp"
#include "widgets.hpp"
#include "config.hpp"
#include "resources.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <utility>

Client::Client()
{
    SDL_ShowWindow(_context.window());

    res::load("resources.data", _context.renderer());

    auto background = std::make_unique<SolidBackground>();
    background->color = {0, 200, 100};
    _widgets.push_back(std::move(background));

    auto newGameButton = std::make_unique<Button>();
    newGameButton->position = {100, 100};
    newGameButton->size = {200, 100};
    newGameButton->text = "New Game";
    _widgets.push_back(std::move(newGameButton));
}

void Client::render()
{
    for (const auto& widget : _widgets) {
        widget->render(_context.renderer());
    }

    SDL_RenderPresent(_context.renderer());
}