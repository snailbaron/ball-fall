add_executable (
    apack
        writers/header_writer.cpp
        writers/header_writer.hpp
        writers/resource_writer.cpp
        writers/resource_writer.hpp
        file_ops.cpp
        file_ops.hpp
        generator.cpp
        generator.hpp
        main.cpp
        packers.cpp
        packers.hpp
)

# Flatbuffers
find_path (FLATBUFFERS_INCLUDE_DIR flatbuffers/flatbuffers.h)
find_library (FLATBUFFERS_LIBRARY flatbuffers)
target_include_directories (apack PRIVATE ${FLATBUFFERS_INCLUDE_DIR})
target_link_libraries (apack ${FLATBUFFERS_LIBRARY})

# TCLAP
find_path (TCLAP_INCLUDE_DIR tclap/CmdLine.h)
target_include_directories (apack PRIVATE ${TCLAP_INCLUDE_DIR})

# SDL2
target_link_libraries (apack SDL2::SDL2)

set (resource_data_file ${generated_dir}/resources.data)
set (resource_header_file ${generated_include_dir}/resource_ids.hpp)

add_custom_command (
    OUTPUT
        ${resource_data_file}
        ${resource_header_file}
    COMMAND $<TARGET_FILE:apack>
        --assets ${CMAKE_SOURCE_DIR}/assets
        --data ${resource_data_file}
        --header ${resource_header_file}
    DEPENDS apack)

add_custom_target (
    pack-resources
    DEPENDS
        ${resource_data_file}
        ${resource_header_file})