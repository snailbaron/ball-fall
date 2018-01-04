add_executable (
    ball-fall
        client.cpp
        client.hpp
        color.cpp
        color.hpp
        config.hpp
        main.cpp
        resources.cpp
        resources.cpp
        sdl_context.cpp
        sdl_context.hpp
        timer.cpp
        timer.hpp
        vector.hpp
        widget.hpp
        widgets.cpp
        widgets.hpp
)

target_link_libraries (ball-fall PRIVATE SDL2::SDL2 SDL2::SDL2main)

target_include_directories (ball-fall PRIVATE ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries (ball-fall PRIVATE ${SDL2_TTF_LIBRARY})

target_include_directories (ball-fall PRIVATE ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries (ball-fall PRIVATE ${SDL2_IMAGE_LIBRARY})
