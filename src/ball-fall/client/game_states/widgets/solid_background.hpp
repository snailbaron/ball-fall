#pragma once

#include "widget.hpp"
#include <util/vector.hpp>
#include <platform.hpp>

#include <cstdint>
#include <string>
#include <functional>

class SolidBackground : public Widget {
public:
    using Widget::Widget;

    SolidBackground& color(const Color& color);

    void render() const override;

private:
    Color _color = Color::Black;
};