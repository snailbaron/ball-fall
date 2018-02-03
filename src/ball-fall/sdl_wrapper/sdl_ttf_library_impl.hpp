#pragma once

#include "sdl_library_impl.hpp"

#include <memory>

namespace sdl {
namespace ttf {

class LibraryImpl : public Library, std::enable_shared_from_this {
public:
    LibraryImpl(std::shared_ptr<sdl::Library> sdlLibrary);
    ~LibraryImpl();

    const std::shared_ptr<sdl::Library> sdlLibrary() const;

    std::shared_ptr<Font> openFont(
        const std::string& file, int ptSize) const override;

private:
    std::shared_ptr<sdl::LibraryImpl> _sdlLibrary;
};

}} // namespace sdl::img