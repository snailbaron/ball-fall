#pragma once

#include "widget.hpp"
#include "color.hpp"
#include "vector.hpp"

#include <cstdint>
#include <string>

class SolidBackground : public Widget {
public:
    void render(SDL_Renderer* renderer) const override;

    Color color = Color::Black;
};

class Button : public Widget {
public:
    void render(SDL_Renderer* renderer) const override;




    Vector<int> position;
    Vector<int> size;
    std::string text;
};