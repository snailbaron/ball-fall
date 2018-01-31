#include <platform/events.hpp>

namespace evt {

namespace {

evening::Channel g_eventChannel;

} // namespace

evening::Channel& bus()
{
    return g_eventChannel;
}

} // namespace evt