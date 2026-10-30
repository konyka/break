# Contract for the crash-reporting server side: the new libraries are dev/server
# tools, not part of any shipped binary, and break_crash itself stays free of
# network and server code.
# -DENGINE_CMAKE -DCRASH_ARCHIVE -DUPLOAD_ARCHIVE -DCLUSTER_ARCHIVE -DSYMBOLIZE_ARCHIVE

foreach(var ENGINE_CMAKE CRASH_ARCHIVE UPLOAD_ARCHIVE CLUSTER_ARCHIVE SYMBOLIZE_ARCHIVE)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()
file(READ "${ENGINE_CMAKE}" cmake_text)

# --- 1. each library owns exactly its one TU
foreach(pair
        "break_crash_symbolize|src/crash/break_crash_symbolize.c"
        "break_crash_cluster|src/crash/break_crash_cluster.c"
        "break_crash_upload_http|src/crash/break_crash_upload_http.c")
    string(REPLACE "|" ";" parts "${pair}")
    list(GET parts 0 lib)
    list(GET parts 1 src)
    if(NOT cmake_text MATCHES "add_library\\(${lib} STATIC ${src}\\)")
        message(FATAL_ERROR "${lib} must be a STATIC library owning exactly ${src}")
    endif()
    string(REGEX MATCHALL "${src}" mentions "${cmake_text}")
    list(LENGTH mentions n)
    if(NOT n EQUAL 1)
        message(FATAL_ERROR "${src} must appear exactly once, got ${n}")
    endif()
endforeach()

# --- 2. no shipped binary links any of them
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break|editor)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_crash_symbolize|break_crash_cluster|break_crash_upload_http")
        message(FATAL_ERROR "a crash server library leaked into a shipped binary's link line: ${line}")
    endif()
endforeach()
string(REGEX MATCH "add_library\\(engine STATIC[^)]*\\)" engine_block "${cmake_text}")
if(engine_block MATCHES "crash_symbolize|crash_cluster|crash_upload")
    message(FATAL_ERROR "engine must not compile the crash server sources")
endif()

# --- 3. exact exported surface of each archive
find_program(NM NAMES nm llvm-nm)
if(NOT NM)
    message(FATAL_ERROR "nm not found")
endif()
function(exports archive outvar)
    execute_process(COMMAND ${NM} -g --defined-only --format=posix "${archive}"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(NOT rc EQUAL 0)
        message(FATAL_ERROR "nm failed on ${archive}: ${err}")
    endif()
    string(REPLACE "\n" ";" lines "${out}")
    set(actual "")
    foreach(line IN LISTS lines)
        if(line MATCHES "^([A-Za-z_][A-Za-z0-9_]*) [TDBR] ")
            list(APPEND actual "${CMAKE_MATCH_1}")
        endif()
    endforeach()
    list(SORT actual)
    set(${outvar} "${actual}" PARENT_SCOPE)
endfunction()

exports("${UPLOAD_ARCHIVE}" got)
set(want break_crash_upload_http)
if(NOT got STREQUAL want)
    message(FATAL_ERROR "break_crash_upload_http exports differ.\n  actual: ${got}\n  expected: ${want}")
endif()

exports("${CLUSTER_ARCHIVE}" got)
set(want
    break_crash_signature break_crash_cluster_open break_crash_cluster_destroy
    break_crash_cluster_register_build break_crash_cluster_build_known break_crash_cluster_add
    break_crash_cluster_mark_fixed break_crash_cluster_find break_crash_cluster_resolve_prefix
    break_crash_cluster_signature_count break_crash_cluster_build_count break_crash_cluster_save
    break_crash_cluster_report break_crash_cluster_serialize break_crash_cluster_parse
    break_crash_cluster_lock break_crash_cluster_unlock)
list(SORT want)
if(NOT got STREQUAL want)
    message(FATAL_ERROR "break_crash_cluster exports differ.\n  actual: ${got}\n  expected: ${want}")
endif()

exports("${SYMBOLIZE_ARCHIVE}" got)
set(want
    break_elf_symbols_open break_elf_symbols_destroy break_elf_symbols_count break_elf_symbols_lookup
    break_elf_symbols_is_exec break_elf_symbols_build_id break_crash_symbol_store_open
    break_crash_symbol_store_destroy break_crash_symbol_store_lookup break_crash_symbolize_address
    break_crash_symbolize_record)
list(SORT want)
if(NOT got STREQUAL want)
    message(FATAL_ERROR "break_crash_symbolize exports differ.\n  actual: ${got}\n  expected: ${want}")
endif()

# --- 4. break_crash has no network or server symbols
execute_process(COMMAND ${NM} -g --format=posix "${CRASH_ARCHIVE}" OUTPUT_VARIABLE crash_all RESULT_VARIABLE rc)
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "nm failed on break_crash")
endif()
if(crash_all MATCHES "break_http|SSL_|socket|connect|accept")
    message(FATAL_ERROR "the break_crash archive references network code")
endif()

# --- 5. no test hook or insecure switch anywhere in the new surface
foreach(sym IN LISTS got)
    if(sym MATCHES "for_test|_test_|testing|insecure|noverify")
        message(FATAL_ERROR "test hook or insecure switch exported: ${sym}")
    endif()
endforeach()

# --- 6. the server keeps its transport rules in the source
get_filename_component(ENGINE_DIR "${ENGINE_CMAKE}" DIRECTORY)
file(READ "${ENGINE_DIR}/tools/break_crash_server.c" server_src)
foreach(needle "TLS1_2_VERSION" "TLS is required" "needs a loopback --bind address")
    if(NOT server_src MATCHES "${needle}")
        message(FATAL_ERROR "break_crash_server.c lost a rule: ${needle}")
    endif()
endforeach()

message(STATUS "crash server contract OK")
