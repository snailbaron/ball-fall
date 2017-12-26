#pragma once

struct SDL_Renderer;

class Widget {
public:
    virtual ~Widget() {}

    virtual void render(SDL_Renderer* renderer) const = 0;
};

