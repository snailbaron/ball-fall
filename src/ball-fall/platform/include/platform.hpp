#pragma once

#include <platform/events.hpp>
#include <platform/resources.hpp>
#include <platform/screen.hpp>

namespace platform {

void init();
void kill();

Screen& screen();
Resources& resources();

} // namespace platform