#pragma once

#include <util/vector.hpp>

#include <sdl_wrapper.hpp>

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
public:
    virtual ~Image() {}

    virtual const sdl::Texture& texture() const = 0;
    virtual const SDL_Rect* srcrect() const = 0;

    virtual void update(double /*delta*/) {}
};

class Sprite : public Image {
public:
    Sprite(sdl::Texture texture);

    const sdl::Texture& texture() const override;
    const SDL_Rect* srcrect() const override;

private:
    sdl::Texture _texture;
};
