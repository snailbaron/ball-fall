#pragma once

#include <memory>

class Core {
public:
    virtual void update(double delta) = 0;
    virtual bool active() const = 0;
};

std::unique_ptr<Core> makeCore();
