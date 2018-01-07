add_executable (
    ball-fall
        resources.data

        client.cpp
        client.hpp
        color.cpp
        color.hpp
        config.hpp
        lru_cache.hpp
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

add_custom_command (
    OUTPUT resources.data
    COMMAND
        ${CMAKE_COMMAND} -E copy
            ${generated_dir}/resources.data
            resources.data
    DEPENDS
        pack-resources
        ${generated_dir}/resources.data
)

target_link_libraries (ball-fall util)

target_link_libraries (ball-fall SDL2::SDL2 SDL2::SDL2main)

target_include_directories (ball-fall PRIVATE ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries (ball-fall ${SDL2_TTF_LIBRARY})

target_include_directories (ball-fall PRIVATE ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries (ball-fall ${SDL2_IMAGE_LIBRARY})

target_include_directories (ball-fall PRIVATE ${generated_include_dir})

target_include_directories (ball-fall PRIVATE ${FLATBUFFERS_INCLUDE_DIR})
target_link_libraries (ball-fall ${FLATBUFFERS_LIBRARY})

add_subdirectory (test)