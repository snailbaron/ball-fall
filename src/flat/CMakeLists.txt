find_program (FLATC_PROGRAM_PATH flatc)

set (generated_header ${generated_include_dir}/resources_generated.h)

add_custom_command (
    OUTPUT ${generated_header}
    COMMAND ${FLATC_PROGRAM_PATH}
        --cpp
        -o ${generated_include_dir}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources.fbs
)

add_custom_target (
    flat-headers
    DEPENDS ${generated_header}
)