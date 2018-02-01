#include <platform/events.hpp>

namespace evt {

namespace {

evening::Channel g_bus;
evening::Channel g_input;

} // namespace

evening::Channel& bus()
{
    return g_bus;
}

evening::Channel& input()
{
    return g_input;
}

} // namespace evt