#pragma once

#include "widget.hpp"
#include "sdl_context.hpp"

#include <memory>
#include <vector>

class Client {
public:
    Client();

    void render();

private:
    SdlContext _context;
    std::vector<std::unique_ptr<Widget>> _widgets;
};
