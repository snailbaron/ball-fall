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

}

void WidgetHolder::clear()
{
    _widgets.clear();
}