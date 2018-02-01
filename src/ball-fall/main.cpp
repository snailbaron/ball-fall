#include <core.hpp>
#include <util/timer.hpp>
#include <config.hpp>
#include <client/client.hpp>
#include <platform.hpp>

#include <SDL2/SDL.h>

int main(int /*argc*/, char* /*argv*/[])
{
    platform::init();

    auto core = makeCore();
    auto client = makePlayerClient();

    auto timer = FrameTimer(config::GameFps);
    while (client->active()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            evt::input().send(event);
        }

        auto framesPassed = timer.framesPassed();
        if (framesPassed > 0) {
            for (int i = 0; i < framesPassed; i++) {
                core->update(timer.delta());
                client->update(timer.delta());
                evt::bus().deliver();
            }

            client->render();
        }
    }

    platform::kill();

    return 0;
}