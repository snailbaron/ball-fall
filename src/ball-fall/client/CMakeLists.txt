set (sources
    media.cpp
    player_client.cpp
    resources.cpp
)

string (REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1" sources "${sources}")
target_sources (ball-fall PRIVATE ${sources})

add_subdirectory (game_states)