#pragma once

#include "../vector.hpp"
#include "resources.hpp"

#include <SDL2/SDL.h>

struct SDL_Renderer;

class Widget {
public:
    enum class VisualState {
        Normal,
        Focused,
        Pressed,
    };

    virtual ~Widget() {}

    virtual void position(int x, int y) { _position = {x, y}; }
    virtual void size(int width, int height) { _size = {width, height}; }

    virtual void processEvent(const SDL_Event& /*event*/) {}
    virtual void render() const {}
    virtual void update(double /*delta*/) {}

    virtual bool contains(int /*x*/, int /*y*/) { return false; }

    virtual void onVisualState(VisualState /*state*/) {}
    virtual void onActivate() {}

protected:
    Vector<int> _position;
    Vector<int> _size;
};
