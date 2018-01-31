#include "panel.hpp"
#include <platform.hpp>

void Panel::processEvent(const SDL_Event& event)
{
    switch (event.type) {
        case SDL_MOUSEMOTION:
        {
            const auto& motion = event.motion;

            // Staying inside the focused widget
            if (_focused && _focused->contains(motion.x, motion.y)) {
                break;
            }

            // Moving out of focused widget
            if (_focused) {
                _focused->onVisualState(Widget::VisualState::Normal);
                _focused = nullptr;
            }

            // Check if moving into a widget
            for (auto it = _widgets.rbegin(); it != _widgets.rend(); ++it) {
                if ((*it)->contains(motion.x, motion.y)) {
                    if (!_pressed) {
                        (*it)->onVisualState(Widget::VisualState::Focused);
                    } else if (it->get() == _pressed) {
                        (*it)->onVisualState(Widget::VisualState::Pressed);
                    }
                    _focused = it->get();
                    break;
                }
            }

            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            if (_focused) {
                _focused->onVisualState(Widget::VisualState::Pressed);
                _pressed = _focused;
            }

            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            if (_focused && _focused == _pressed) {
                _focused->onActivate();
            }

            _pressed = nullptr;
            if (_focused) {
                _focused->onVisualState(Widget::VisualState::Focused);
            }

            break;
        }
    }
}

void Panel::render() const
{
    platform::screen().drawRoundedBox(
        vectorCast<int16_t>(_position),
        vectorCast<int16_t>(_size),
        CornerRadius,
        BgColor);

    for (const auto& widget : _widgets) {
        widget->render();
    }
}

void Panel::add(std::unique_ptr<Widget>&& widget)
{
    _widgets.push_back(std::move(widget));

    int freeSpace = _size.y - Offset * (static_cast<int>(_widgets.size()) + 1);
    int rowHeight = static_cast<int>(freeSpace / _widgets.size());
    int rowDiff = rowHeight + Offset;
    int offset = _position.y + Offset;
    for (const auto& wp : _widgets) {
        wp->position(_position.x + Offset, offset);
        wp->size(_size.x - 2 * Offset, rowHeight);
        offset += rowDiff;
    }
}