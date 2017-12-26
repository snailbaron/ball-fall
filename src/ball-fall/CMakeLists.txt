add_executable (
    ball-fall
        client.cpp
        client.hpp
        color.cpp
        color.hpp
        config.hpp
        main.cpp
        sdl_context.cpp
        sdl_context.hpp
        timer.cpp
        timer.hpp
        widget.hpp
        widgets.cpp
        widgets.hpp
)

find_package (SDL2 REQUIRED SDL2::SDL2 SDL2::SDL2main)
target_link_libraries (ball-fall SDL2::SDL2 SDL2::SDL2main)
