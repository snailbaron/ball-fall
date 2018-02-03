#pragma once

namespace sdl {

class LibraryImpl : public Library {
public:
    LibraryImpl();
    ~LibraryImpl();

    std::optional<SDL_Event> pollEvent() const override;

    std::shared_ptr<Window> createWindow(
        const std::string& title,
        int x,
        int y,
        int w,
        int h,
        Uint32 flags) const override;
};

} // namespace sdl
