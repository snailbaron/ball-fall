#pragma once

#include "sdl_context.hpp"
#include "resources.hpp"
#include "widget.hpp"

#include <memory>
#include <vector>

class Client {
public:
    void init();
    void render() const;

    TTF_Font* font(res::FontId fontId, int ptSize);
    const SDL_Texture* texture(res::BitmapId bitmapId);

private:
    template <class W> W& addWidget();

    SdlContext _context;
    Resources _resources;
    std::vector<std::unique_ptr<Widget>> _widgets;
};

Client& client();
