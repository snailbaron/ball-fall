#pragma once

#include <platform/screen.hpp>

struct Config {
    Screen::Config screen {};
    constexpr auto gameFps = 60;
    constexpr auto resourceFile = "resources.data";
};