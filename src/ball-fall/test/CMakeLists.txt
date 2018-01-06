add_executable (lru-cache-test lru_cache_test.cpp)
target_include_directories (lru-cache-test PRIVATE ${CATCH_INCLUDE_DIR})

if (MSVC)
    target_compile_options (lru-cache-test PRIVATE "/wd4996")
endif ()

add_test (
    NAME lru-cache-test
    COMMAND lru-cache-test
)
