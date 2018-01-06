find_package (SDL2 REQUIRED SDL2::SDL2 SDL2::SDL2main)

find_path (SDL2_TTF_INCLUDE_DIR SDL2/SDL_ttf.h)
find_library (SDL2_TTF_LIBRARY SDL2_ttf)

find_path (SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_image.h)
find_library (SDL2_IMAGE_LIBRARY SDL2_image)

find_path (FLATBUFFERS_INCLUDE_DIR flatbuffers/flatbuffers.h)
find_library (FLATBUFFERS_LIBRARY flatbuffers)

find_path (TCLAP_INCLUDE_DIR tclap/CmdLine.h)

find_path (CATCH_INCLUDE_DIR catch.hpp)

set (generated_dir ${CMAKE_CURRENT_BINARY_DIR}/generated)
set (generated_include_dir ${generated_dir}/include)

include_directories (${generated_include_dir})

add_subdirectory (flat)
add_subdirectory (util)

add_subdirectory (apack)
add_dependencies (apack flat-headers)

add_subdirectory (ball-fall)
add_dependencies (ball-fall pack-resources apack)
