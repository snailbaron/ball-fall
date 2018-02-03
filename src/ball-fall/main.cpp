#include <core.hpp>
#include <util/timer.hpp>
#include <config.hpp>
#include <client/client.hpp>
#include <platform.hpp>

#include <sdl_wrapper.hpp>

int main(int /*argc*/, char* /*argv*/[])
{
    sdl::init();

    auto core = makeCore();
    auto client = makePlayerClient();

    auto timer = FrameTimer(config::GameFps);
    while (client->active()) {
        while (auto event = sdl().pollEvent()) {
            evt::input().send(*event);
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

    client.reset();
    core.reset();

    sdl::quit();

    return 0;
}