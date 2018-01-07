#include "client.hpp"
#include "widgets/all.hpp"
#include "config.hpp"
#include "resources.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <utility>
#include <type_traits>

void Client::init()
{
    _resources.load(_context.renderer());
    _widgetHolder.renderer(_context.renderer());

    SDL_ShowWindow(_context.window());

    _widgetHolder.add<SolidBackground>()
        .color({255, 240, 190});

    _widgetHolder.add<Button>()
        .position(100, 100)
        .size(200, 100)
        .text("New Game");

    _widgetHolder.add<Button>()
        .position(100, 300)
        .size(200, 100)
        .text("Options");

    _widgetHolder.add<Button>()
        .position(100, 500)
        .size(200, 100)
        .text("Quit")
        .action([this] {
            _active = false;
        });
}

void Client::processInput(const SDL_Event& event)
{
    if (event.type == SDL_QUIT) {
        _active = false;
        return;
    }

    _widgetHolder.processEvent(event);
}

void Client::update(double delta)
{
    _widgetHolder.update(delta);
}

void Client::render() const
{
    _widgetHolder.render();

    SDL_RenderPresent(_context.renderer());
}

bool Client::active() const
{
    return _active;
}

TTF_Font* Client::font(res::FontId fontId, int ptSize)
{
    return _resources.font(fontId, ptSize);
}

const SDL_Texture* Client::texture(res::BitmapId bitmapId)
{
    return _resources.texture(bitmapId);
}

Client& client()
{
    static Client c;
    return c;
}