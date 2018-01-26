set (sources
    gameplay.cpp
    main_menu.cpp
    scene.cpp
)

string (REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1" sources "${sources}")
target_sources (ball-fall PRIVATE ${sources})

add_subdirectory (widgets)