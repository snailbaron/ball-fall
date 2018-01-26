#include "core.hpp"
#include "client/player_client.hpp"
#include "timer.hpp"
#include "config.hpp"
#include "client/media.hpp"
#include "client/resources.hpp"
#include "events.hpp"

int main(int /*argc*/, char* /*argv*/[])
{
    media::init();
    resources::load(media::renderer());

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

    resources::clear();
    media::kill();

    return 0;
}