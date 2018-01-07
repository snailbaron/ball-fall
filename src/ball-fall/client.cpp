#include "client.hpp"
#include "widgets.hpp"
#include "config.hpp"
#include "resources.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <utility>
#include <type_traits>

void Client::init()
{
    _resources.load(_context.renderer());

    SDL_ShowWindow(_context.window());

    addWidget<SolidBackground>()
        .color({0, 200, 100});

    addWidget<Button>()
        .position(100, 100)
        .size(200, 100)
        .text("New Game");
}

void Client::render() const
{
    for (const auto& widget : _widgets) {
        widget->render();
    }

    SDL_RenderPresent(_context.renderer());
}

TTF_Font* Client::font(res::FontId fontId, int ptSize)
{
    return _resources.font(fontId, ptSize);
}

const SDL_Texture* Client::texture(res::BitmapId bitmapId)
{
    return _resources.texture(bitmapId);
}

template <class W>
W& Client::addWidget()
{
    static_assert(
        std::is_base_of<Widget, W>(),
        "trying to add a non-subclass of Widget with Client::addWidget");

    _widgets.push_back(std::make_unique<W>(_context.renderer()));
    return *static_cast<W*>(_widgets.back().get());
}

Client& client()
{
    static Client c;
    return c;
}