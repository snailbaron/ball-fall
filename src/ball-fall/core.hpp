#pragma once

#include "events.hpp"
#include "field.hpp"

#include <optional>

class Core : evening::Subscriber {
public:
    Core();

    void update(double delta);
    bool active() const { return _active; }

private:
    bool _active = true;
    std::optional<Field> _field;
};