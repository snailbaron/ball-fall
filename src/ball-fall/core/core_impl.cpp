#include "core_impl.hpp"
#include <platform/events.hpp>

CoreImpl::CoreImpl()
{
    subscribe<evt::NewGame>(evt::bus(), [this] (const auto&) {
        _field = Field();
    });
}

void CoreImpl::update(double delta)
{
    if (_field) {
        _field->update(delta);
    }
}

std::unique_ptr<Core> makeCore()
{
    return std::make_unique<CoreImpl>();
}