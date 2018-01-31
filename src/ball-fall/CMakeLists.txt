add_executable (
    ball-fall
        resources.data
        main.cpp
)

macro (MODULE)
    set (options "")
    set (oneValueArgs NAME)
    set (multiValueArgs SOURCES)
    cmake_parse_arguments (
        MODULE "${options}" "${oneValueArgs}" "${multiValueArgs}" "${ARGN}")

    message (STATUS "adding include directory: ${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_include_directories (ball-fall PRIVATE include)

    set (sources ${MODULE_SOURCES})
    string (REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1" sources "${sources}")

    target_sources (ball-fall PRIVATE ${sources})
endmacro ()

add_subdirectory (util)
add_subdirectory (client)
add_subdirectory (core)
add_subdirectory (geometry)
add_subdirectory (platform)

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