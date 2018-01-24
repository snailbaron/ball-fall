#pragma once

#include "../widget.hpp"
#include "../color.hpp"
#include "../../vector.hpp"
#include "../resources.hpp"

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
