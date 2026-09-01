if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" engine_cmake)

foreach(required_text
        "RULE_ENGINE_REDIS_SOURCE_DIR"
        "deps/hiredis"
        "add_library(rule_engine_hiredis STATIC"
        "alloc.c"
        "hiredis.c"
        "target_link_libraries(rule_engine_hiredis"
        "no fallback")
    string(FIND "${engine_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "Redis dependency contract missing: ${required_text}")
    endif()
endforeach()

if(NOT engine_cmake MATCHES "RULE_ENGINE_ENABLE_REDIS requested but hiredis not found")
    message(FATAL_ERROR "Redis dependency contract must retain the missing-client no-fallback boundary")
endif()
