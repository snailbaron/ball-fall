#pragma once

#include "sdl_context.hpp"
#include "resources.hpp"
#include "widget.hpp"
#include "../events.hpp"

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

class PlayerClient : public evening::Subscriber {
public:
    PlayerClient();

    void processInput(const SDL_Event& event);
    void update(double delta);
    void render() const;

    bool active() const;

    TTF_Font* font(res::FontId fontId, int ptSize);
    const SDL_Texture* texture(res::BitmapId bitmapId);

private:
    bool _active = true;
    SdlContext _context;
    Resources _resources;
    std::vector<std::unique_ptr<Widget>> _widgets;
};
