#pragma once

#include <sdl_wrapper/internal/wrapper.hpp>
#include <sdl_wrapper/render.hpp>

#include <cstdint>
#include <string>

namespace sdl {

class Window : public internal::Wrapper<SDL_Window, SDL_DestroyWindow> {
public:
    using Wrapper::Wrapper;
    using Wrapper::reset;

    Renderer createRenderer(int index, uint32_t flags) const
    {
        return Renderer(SDL_CreateRenderer(get(), index, flags));
    }

    void show() const
    {
        SDL_ShowWindow(get());
    }
};

Window createWindow(
    const std::string& title, int x, int y, int w, int h, uint32_t flags)
{
    return Window(SDL_CreateWindow(title.c_str(), x, y, w, h, flags));
}

} // namespace sdl