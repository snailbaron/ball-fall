add_executable (
    ball-fall
        resources.data

        client/color.cpp
        client/color.hpp
        client/lru_cache.hpp
        client/player_client.cpp
        client/player_client.hpp
        client/resources.cpp
        client/resources.cpp
        client/scene.cpp
        client/scene.hpp
        client/sdl_context.cpp
        client/sdl_context.hpp
        client/widget.hpp
        client/widgets/all.hpp
        client/widgets/button.cpp
        client/widgets/button.hpp
        client/widgets/main_menu.cpp
        client/widgets/main_menu.hpp
        client/widgets/panel.cpp
        client/widgets/panel.hpp
        client/widgets/solid_background.cpp
        client/widgets/solid_background.hpp

        config.hpp
        core.cpp
        core.hpp
        evening.hpp
        events.cpp
        events.hpp
        field.cpp
        field.hpp
        main.cpp
        timer.cpp
        timer.hpp
        vector.hpp
)

add_subdirectory (geometry)

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

target_include_directories (ball-fall PRIVATE ${SDL2_GFX_INCLUDE_DIR})
target_link_libraries (ball-fall ${SDL2_GFX_LIBRARY})

target_include_directories (ball-fall PRIVATE ${generated_include_dir})

target_include_directories (ball-fall PRIVATE ${FLATBUFFERS_INCLUDE_DIR})
target_link_libraries (ball-fall ${FLATBUFFERS_LIBRARY})

add_subdirectory (test)