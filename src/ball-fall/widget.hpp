#pragma once

#include "vector.hpp"

#include <SDL2/SDL.h>

struct SDL_Renderer;

class Widget {
public:
    enum class VisualState {
        Normal,
        Focused,
        Pressed,
    };

    Widget(SDL_Renderer* renderer) : _renderer(renderer) {}
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
    SDL_Renderer* renderer() const { return _renderer; }
    Vector<int> _position;
    Vector<int> _size;

private:
    SDL_Renderer* _renderer;
};
