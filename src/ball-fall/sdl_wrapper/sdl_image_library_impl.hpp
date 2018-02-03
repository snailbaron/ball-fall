#pragma once

#include "sdl_library_impl.hpp"

#include <memory>

namespace sdl {
namespace img {

class LibraryImpl : public Library, std::enable_shared_from_this {
public:
    LibraryImpl(std::shared_ptr<sdl::Library> sdlLibrary);
    ~LibraryImpl();

    std::shared_ptr<Surface> load(const std::string& file) const override;

private:
    std::shared_ptr<sdl::LibraryImpl> _sdlLibrary;
};

}} // namespace sdl::img