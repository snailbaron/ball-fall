#pragma once

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

struct SDL_Texture;

struct Texture {
    Texture();
    Texture(int width, int height, SDL_Texture* texture);
    ~Texture();

    int width;
    int height;
    SDL_Texture* ptr;
};