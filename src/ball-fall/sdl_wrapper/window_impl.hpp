#pragma once

#include "sdl_library_impl.hpp"

#include <sdl_wrapper/window.hpp>

#include <SDL2/SDL.h>

#include <memory>

namespace sdl {

class WindowImpl : public Window, std::enable_shared_from_this {
public:
    WindowImpl(std::shared_ptr<Library> library, SDL_Window* window);

    std::shared_ptr<Renderer> createRenderer(
        int index, std::uint32_t flags) const override;

private:
    std::shared_ptr<LibraryImpl> _library;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;
};

} // namespace sdl