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

class Texture {
public:
    virtual ~Texture() {}

    virtual const Vector<int>& size() const = 0;
};

class Font {
public:
    virtual ~Font() {}

    virtual int size() const = 0;
};