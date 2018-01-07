#include "client.hpp"
#include "timer.hpp"
#include "config.hpp"

int main(int /*argc*/, char* /*argv*/[])
{
    client().init();

    auto timer = FrameTimer(config::GameFps);
    while (client().active()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            client().processInput(event);
        }

        auto framesPassed = timer.framesPassed();
        if (framesPassed > 0) {
            for (int i = 0; i < framesPassed; i++) {
                client().update(timer.delta());
            }
            client().render();
        }
    }

    return 0;
}