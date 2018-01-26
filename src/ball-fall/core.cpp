#include "core.hpp"

Core::Core()
{
    //subscribe<evt::NewGame>(evt::bus(), [this] (const auto&) {
    //    _field = Field();
    //});
}

void Core::update(double delta)
{
    if (_field) {
        _field->update(delta);
    }
}
