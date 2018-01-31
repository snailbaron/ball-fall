#pragma once

class Core {
public:
    virtual void update(double delta) = 0;
    virtual bool active() const = 0;
};