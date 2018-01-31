#include <core.hpp>
#include <client/player_client.hpp>
#include <util/timer.hpp>
#include <client/config.hpp>
#include <platform.hpp>

int main(int /*argc*/, char* /*argv*/[])
{
    platform::init();

    Core core;
    PlayerClient client;

    auto timer = FrameTimer(config::GameFps);
    while (client.active()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            client.processEvent(event);
        }

        auto framesPassed = timer.framesPassed();
        if (framesPassed > 0) {
            for (int i = 0; i < framesPassed; i++) {
                core.update(timer.delta());
                client.update(timer.delta());
                evt::bus().deliver();
            }

            client.render();
        }
    }

    platform::kill();

    return 0;
}