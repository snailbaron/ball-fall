add_executable (
    apack
        main.cpp
        resources_generated.h
)

add_custom_command (
    OUTPUT resources_generated
    COMMAND ${FLATC_PROGRAM_PATH} --cpp ${CMAKE_CURRENT_SOURCE_DIR}/resources.fbs
)

find_program (FLATC_PROGRAM_PATH flatc)

find_path (TCLAP_INCLUDE_DIR tclap/CmdLine.h)
target_include_directories (apack PRIVATE ${TCLAP_INCLUDE_DIR})

find_path (ZLIB_INCLUDE_DIR zlib.h)
find_library (ZLIB_LIBRARY zlib)
target_include_directories (apack PRIVATE ${ZLIB_INCLUDE_DIR})
target_link_libraries (apack ${ZLIB_LIBRARY})