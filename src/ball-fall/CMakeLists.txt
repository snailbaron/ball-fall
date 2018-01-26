add_executable (
    ball-fall
        resources.data

        config.hpp
        core.cpp
        core.hpp
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
add_subdirectory (client)

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
target_link_libraries (ball-fall evening)
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