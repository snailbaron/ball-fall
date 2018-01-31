#pragma once

#include "field.hpp"
#include <core.hpp>
#include <evening.hpp>

#include <optional>

class CoreImpl : public Core, public evening::Subscriber {
public:
    CoreImpl();

    void update(double delta) override;
    bool active() const override { return _active; }

private:
    bool _active = true;
    std::optional<Field> _field;
};