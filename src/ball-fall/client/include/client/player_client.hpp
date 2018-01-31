#pragma once

#include <SDL2/SDL.h>

class Client {
public:
    virtual ~Client() {}

    virtual void processEvent(const SDL_Event& event) = 0;
    virtual void update(double delta) = 0;
    virtual void render() const = 0;

    virtual bool active() const = 0;
};
