add_executable (
    apack
        main.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/include/resources_generated.h
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

find_path (TCLAP_INCLUDE_DIR tclap/CmdLine.h)
target_include_directories (apack PRIVATE ${TCLAP_INCLUDE_DIR})

find_path (ZLIB_INCLUDE_DIR zlib.h)
find_library (ZLIB_LIBRARY zlib)
target_include_directories (apack PRIVATE ${ZLIB_INCLUDE_DIR})
target_link_libraries (apack ${ZLIB_LIBRARY})