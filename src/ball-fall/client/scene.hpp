#pragma once

#include "resources.hpp"
#include "../vector.hpp"
#include "../events.hpp"

#include <SDL2/SDL.h>

#include <map>

struct BrickSprite {
    res::BitmapId bitmapId;
    int x;
    int y;
};

class Scene : public evening::Subscriber {
public:
    Scene(SDL_Renderer* renderer, Resources& resources);

    void render() const;

private:
    SDL_Renderer* _renderer;
    Resources& _resources;

    std::map<Vector<int>, BrickSprite> _bricks;
    geometry::Vector _ballPosition;
    float _platformPosition;
};
