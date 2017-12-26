#pragma once

#include "widget.hpp"
#include "color.hpp"

#include <cstdint>

class SolidBackground : public Widget {
public:
    void render(SDL_Renderer* renderer) const override;

    Color color = Color::Black;
};