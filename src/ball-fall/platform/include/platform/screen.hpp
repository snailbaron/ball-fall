#pragma once

#include <platform/color.hpp>
#include <util/vector.hpp>

#include <cstdint>

namespace platform {

class Screen {
public:
    virtual ~Screen() {}

    virtual void clear(const Color& color) = 0;

    virtual void drawRoundedBox(
        const Vector<int16_t>& position,
        const Vector<int16_t>& size,
        int16_t cornerRadius,
        const Color& color) = 0;
};

} // namespace platform
