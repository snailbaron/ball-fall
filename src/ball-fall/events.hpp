#pragma once

#include "evening.hpp"

namespace evt {

struct Quit {};

evening::Channel& bus();

} // namespace evt