add_subdirectory (repal)

add_subdirectory (apack)

set (generated_dir ${CMAKE_CURRENT_BINARY_DIR}/generated)
set (resource_data_file ${generated_dir}/resources.data)
set (generated_include_dir ${generated_dir}/include)
set (resource_header_file ${generated_include_dir}/resource_ids.hpp)

add_custom_command (
    OUTPUT
        ${resource_data_file}
        ${resource_header_file}
    COMMAND $<TARGET_FILE:apack>
        --assets ${CMAKE_SOURCE_DIR}/assets
        --data ${resource_data_file}
        --header ${resource_header_file})

add_custom_target (
    pack-resources
    DEPENDS
        ${resource_data_file}
        ${resource_header_file})

add_subdirectory (ball-fall)

add_dependencies (ball-fall pack-resources)
target_include_directories (ball-fall PRIVATE ${generated_include_dir})