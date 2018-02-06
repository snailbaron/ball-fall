#pragma once

#include <memory>

class Client {
public:
    virtual ~Client() {}

    virtual void update(double delta) = 0;
    virtual void render() const = 0;

    virtual bool active() const = 0;
};

std::unique_ptr<Client> makePlayerClient();
