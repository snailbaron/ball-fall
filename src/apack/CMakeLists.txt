add_executable (
    apack
        ${CMAKE_CURRENT_BINARY_DIR}/include/resources_generated.h

        serialization/header_writer.cpp
        serialization/header_writer.hpp
        serialization/resource_serialization.cpp
        serialization/resource_serialization.hpp
        file_ops.cpp
        file_ops.hpp
        generator.cpp
        generator.hpp
        main.cpp
        packers.cpp
        packers.hpp
)

find_program (FLATC_PROGRAM_PATH flatc)
add_custom_command (
    OUTPUT include/resources_generated.h
    COMMAND ${FLATC_PROGRAM_PATH}
        --cpp
        -o ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/resources.fbs
)
target_include_directories (apack PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)

# Flatbuffers
find_path (FLATBUFFERS_INCLUDE_DIR flatbuffers/flatbuffers.h)
find_library (FLATBUFFERS_LIBRARY flatbuffers)
target_include_directories (apack PRIVATE ${FLATBUFFERS_INCLUDE_DIR})
target_link_libraries (apack ${FLATBUFFERS_LIBRARY})

# TCLAP
find_path (TCLAP_INCLUDE_DIR tclap/CmdLine.h)
target_include_directories (apack PRIVATE ${TCLAP_INCLUDE_DIR})

# GraphicsMagick
find_path (
    GRAPHICSMAGICK_INCLUDE_DIR
    NAMES magick/magick.h Magick++/Magick++.h)
find_library (GRAPHICSMAGICK_LIBRARY graphicsmagick)
target_include_directories (apack PRIVATE ${GRAPHICSMAGICK_INCLUDE_DIR})
target_link_libraries (apack ${GRAPHICSMAGICK_LIBRARY})
