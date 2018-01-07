#include "holder.hpp"

void WidgetHolder::renderer(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

void WidgetHolder::update(double delta)
{
    for (auto widget : _widgets) {
        widget->update(delta);
    }
}

void WidgetHolder::render() const
{
    for (auto widget : _widgets) {
        widget->render();
    }
}

void WidgetHolder::processEvent(const SDL_Event& event)
{
    switch (event.type) {
        case SDL_MOUSEMOTION:
        {
            auto focused = _focusedWidgetPtr.lock();
            auto pressed = _pressedWidgetPtr.lock();

            // Staying inside the focused widget
            if (focused && focused->contains(event.motion.x, event.motion.y)) {
                break;
            }

            // Moving out of focused widget
            if (focused) {
                focused->onVisualState(Widget::VisualState::Normal);
                _focusedWidgetPtr.reset();
            }

            // Check if moving into a widget
            for (auto it = _widgets.rbegin(); it != _widgets.rend(); ++it) {
                if ((*it)->contains(event.motion.x, event.motion.y)) {
                    if (!pressed) {
                        (*it)->onVisualState(Widget::VisualState::Focused);
                    } else if (*it == pressed) {
                        (*it)->onVisualState(Widget::VisualState::Pressed);
                    }
                    _focusedWidgetPtr = *it;
                    break;
                }
            }

            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            auto focused = _focusedWidgetPtr.lock();
            if (focused) {
                focused->onVisualState(Widget::VisualState::Pressed);
                _pressedWidgetPtr = focused;
            }

            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            auto focused = _focusedWidgetPtr.lock();
            auto pressed = _pressedWidgetPtr.lock();
            if (focused == pressed) {
                focused->onActivate();
            }

            _pressedWidgetPtr.reset();
            if (focused) {
                focused->onVisualState(Widget::VisualState::Focused);
            }

            break;
        }
    }
}

void WidgetHolder::clear()
{
    _widgets.clear();
}