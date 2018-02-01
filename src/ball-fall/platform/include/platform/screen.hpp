#pragma once

#include <platform/visuals.hpp>
#include <util/vector.hpp>

#include <resource_ids.hpp>

#include <cstdint>
#include <string>

class Screen {
public:
    virtual ~Screen() {}

    virtual void show() = 0;
    virtual void clear(const Color& color) = 0;
    virtual void present() = 0;

    virtual void drawRect(
        const Vector<int>& position,
        const Vector<int>& size,
        const Color& color) = 0;
    virtual void drawRoundedBox(
        const Vector<int16_t>& position,
        const Vector<int16_t>& size,
        int16_t cornerRadius,
        const Color& color) = 0;

    virtual void drawTexture(
        const Vector<int>& position,
        const Texture& texture) = 0;

    virtual Texture textTexture(
        const std::string& text,
        res::FontId font,
        const Color& textColor,
        const Color& bgColor,
        const Vector<int>& desiredSize) = 0;
};
