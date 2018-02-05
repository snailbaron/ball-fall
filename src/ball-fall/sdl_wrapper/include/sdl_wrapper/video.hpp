#pragma once

#include "internal/wrapper.hpp"
#include "render.hpp"

#include <cstdint>
#include <string>

namespace sdl {

class Window : public internal::Wrapper<SDL_Window, SDL_DestroyWindow> {
public:
    using Wrapper::Wrapper;

    Renderer createRenderer(int index, uint32_t flags) const
    {
        return Renderer(SDL_CreateRenderer(get(), index, flags));
    }
};

Window createWindow(
    const std::string& title, int x, int y, int w, int h, uint32_t flags)
{
    return Window(SDL_CreateWindow(title.c_str(), x, y, w, h, flags));
}

} // namespace sdl