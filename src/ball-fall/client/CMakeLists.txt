set (sources
    color.cpp
    main_menu.cpp
    media.cpp
    player_client.cpp
    resources.cpp
    scene.cpp

    widgets/button.cpp
    widgets/panel.cpp
    widgets/solid_background.cpp
)

string (REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1" sources "${sources}")

target_sources (ball-fall PRIVATE ${sources})