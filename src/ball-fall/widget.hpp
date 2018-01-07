#pragma once

struct SDL_Renderer;

class Widget {
public:
    Widget(SDL_Renderer* renderer) : _renderer(renderer) {}
    virtual ~Widget() {}

    virtual void render() const = 0;

protected:
    SDL_Renderer* renderer() const { return _renderer; }

private:
    SDL_Renderer* _renderer;
};

