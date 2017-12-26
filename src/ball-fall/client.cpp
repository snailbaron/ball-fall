#include "client.hpp"
#include "widgets.hpp"
#include "config.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <utility>

Client::Client()
{
    auto background = std::make_unique<SolidBackground>();
    background->color = {0, 200, 100};
    _widgets.push_back(std::move(background));
}

void Client::render()
{
    for (const auto& widget : _widgets) {
        widget->render(_context.renderer());
    }

    SDL_RenderPresent(_context.renderer());
}