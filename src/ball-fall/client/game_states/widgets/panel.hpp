#pragma once

#include "widget.hpp"

#include <util/vector.hpp>
#include <platform.hpp>

#include <vector>
#include <memory>
#include <type_traits>

class Panel : public Widget {
public:
    using Widget::Widget;

    void processEvent(const SDL_Event& event) override;
    void render() const override;

    template <class W>
    W& make()
    {
        static_assert(
            std::is_base_of<Widget, W>(),
            "trying to add a non-subclass of Widget");

        add(std::make_unique<W>());
        return *static_cast<W*>(_widgets.back().get());
    }

    void add(std::unique_ptr<Widget>&& widget);

private:
    static constexpr auto CornerRadius = 10;
    static constexpr auto BgColor = Color(200, 100, 200);
    static constexpr auto Offset = 30;

    std::vector<std::unique_ptr<Widget>> _widgets;
    Widget* _focused = nullptr;
    Widget* _pressed = nullptr;
};