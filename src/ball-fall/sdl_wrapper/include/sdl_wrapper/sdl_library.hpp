#pragma once

#include <sdl_wrapper/window.hpp>

#include <SDL2/SDL.h>

#include <cstdint>
#include <optional>
#include <memory>
#include <string>

namespace sdl {

class Library {
public:
    virtual ~Library() {}

    // Events
    virtual std::optional<SDL_Event> pollEvent() const = 0;

    virtual std::shared_ptr<Window> createWindow(
        const std::string& title,
        int x,
        int y,
        int w,
        int h,
        uint32_t flags) const = 0;
};

} // namespace sdl