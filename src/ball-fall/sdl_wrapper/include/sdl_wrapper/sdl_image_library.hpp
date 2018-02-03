#pragma once

#include <sdl_wrapper/surface.hpp>

#include <memory>
#include <string>

namespace sdl {
namespace img {

class Library {
public:
    virtual ~Library() {}

    virtual std::shared_ptr<Surface> load(const std::string& file) const = 0;
};

}} // namespace sdl::img
