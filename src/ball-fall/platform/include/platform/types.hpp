#pragma once

#include <util/vector.hpp>

#include <cstdint>
#include <memory>

struct Color {
    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a)
    { }

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    static const Color Black;
};

class Image {
};

class Sprite : public Image {
};

class Animation : public Image {
};
