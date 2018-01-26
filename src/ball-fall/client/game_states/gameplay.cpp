#include "gameplay.hpp"

Gameplay::Gameplay()
{
}

void Gameplay::processEvent(const SDL_Event& event)
{
    switch (event.type) {
        case SDL_MOUSEMOTION:
            break;
    }
}

void Gameplay::render() const
{
    _scene.render();
}
