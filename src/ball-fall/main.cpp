#include "client.hpp"
#include "timer.hpp"
#include "config.hpp"

int main(int /*argc*/, char* /*argv*/[])
{
    client().init();

    auto done = false;
    auto timer = FrameTimer(config::GameFps);
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
            }
        }

        auto framesPassed = timer.framesPassed();
        if (framesPassed > 0) {
            client().render();
        }
    }

    return 0;
}