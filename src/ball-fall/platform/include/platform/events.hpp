#pragma once

#include <evening.hpp>
#include "geometry/2dspace.hpp"

namespace evt {

struct Quit {};
struct NewGame {};

struct BallMove {
    geometry::Vector position;
};

struct PlatformMove
{
    double position;
};

evening::Channel& bus();
evening::Channel& input();

} // namespace evt