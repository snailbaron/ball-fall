#pragma once

#include "../widget.hpp"

#include <SDL2/SDL.h>

#include <vector>
#include <memory>

/**
 * Each widget on screen may be: focused or unfocused, pressed or unpressed.
 *
 * Widget is *focused* if the cursor currently overlaps its position on screen.
 * This may or may not be visually indicated. Only motion events can affect this
 * state.
 *
 * Widget is *pressed* if the pointer button was pressed while the widget was
 * focused, and has not yet been released. Only button events can affect this
 * state.
 */

class WidgetHolder {
public:
    void renderer(SDL_Renderer* renderer);

    void processEvent(const SDL_Event& event);
    void update(double delta);
    void render() const;

    template <class W> W& make()
    {
        static_assert(
            std::is_base_of<Widget, W>(),
            "trying to add a non-subclass of Widget with WidgetHolder::addWidget");

        _widgets.push_back(std::make_shared<W>(_renderer));
        return *static_cast<W*>(_widgets.back().get());
    }

    void add(std::unique_ptr<Widget>&& widget)
    {
        _widgets.push_back(std::move(widget));
    }

    void clear();

private:
    SDL_Renderer* _renderer = nullptr;
    std::vector<std::shared_ptr<Widget>> _widgets;
    std::weak_ptr<Widget> _focusedWidgetPtr;
    std::weak_ptr<Widget> _pressedWidgetPtr;
};