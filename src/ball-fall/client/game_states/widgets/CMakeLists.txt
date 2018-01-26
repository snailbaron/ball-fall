set (sources
    button.cpp
    color.cpp
    panel.cpp
    solid_background.cpp
)

string (REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1" sources "${sources}")
target_sources (ball-fall PRIVATE ${sources})
