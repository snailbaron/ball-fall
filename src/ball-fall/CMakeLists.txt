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

find_package (SDL2 REQUIRED SDL2::SDL2 SDL2::SDL2main)
target_link_libraries (ball-fall SDL2::SDL2 SDL2::SDL2main)

function (LinkSdlLibrary header library)
    find_path (include_dir ${header})
    find_library (library_path ${library})
    target_include_directories (ball-fall PRIVATE ${include_dir})
    target_link_libraries (ball-fall ${library_path})
endfunction()

LinkSdlLibrary (SDL2/SDL_ttf.h SDL2_ttf)
LinkSdlLibrary (SDL2/SDL_image.h SDL2_image)