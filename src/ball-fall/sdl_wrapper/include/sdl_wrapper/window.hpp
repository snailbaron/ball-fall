#pragma once

#include <sdl_wrapper/renderer.hpp>

#include <cstdint>

namespace sdl {

class Window {
public:
    virtual ~Window() {}

    virtual std::shared_ptr<Renderer> createRenderer(
        int index, std::uint32_t flags) const = 0;
};

} // namespace sdl