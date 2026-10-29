# End-to-end: tools/packer writes a pak from a directory tree, tools/verify_pak
# checks it both ways (every source file is in the pak with identical bytes,
# and the pak holds no entry without a source file).
# -DPACKER=<packer> -DVERIFY=<verify_pak> -DWORK=<scratch dir>
if(NOT DEFINED PACKER OR NOT DEFINED VERIFY OR NOT DEFINED WORK)
    message(FATAL_ERROR "PACKER, VERIFY and WORK are required")
endif()
file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}/src/sub/deeper")
file(WRITE "${WORK}/src/a.txt" "alpha")
file(WRITE "${WORK}/src/sub/b.lua" "return 2")
file(WRITE "${WORK}/src/sub/deeper/c.bin" "")

execute_process(COMMAND "${PACKER}" "${WORK}/out.pak" "${WORK}/src"
                RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "packer failed (${rc}): ${out}${err}")
endif()
execute_process(COMMAND "${VERIFY}" "${WORK}/out.pak" "${WORK}/src"
                RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "verify_pak rejected a fresh pak (${rc}): ${out}${err}")
endif()
if(NOT out MATCHES "3 pak entries")
    message(FATAL_ERROR "verify_pak did not report 3 pak entries: ${out}")
endif()

# A source file removed after packing leaves an orphan entry in the pak.
file(REMOVE "${WORK}/src/sub/b.lua")
execute_process(COMMAND "${VERIFY}" "${WORK}/out.pak" "${WORK}/src"
                RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
if(rc EQUAL 0)
    message(FATAL_ERROR "verify_pak accepted a pak with an entry missing on disk")
endif()
if(NOT err MATCHES "sub/b.lua")
    message(FATAL_ERROR "verify_pak did not name the orphan entry: ${err}")
endif()

# A changed source file is a byte mismatch.
file(WRITE "${WORK}/src/sub/b.lua" "return 3")
execute_process(COMMAND "${VERIFY}" "${WORK}/out.pak" "${WORK}/src"
                RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
if(rc EQUAL 0)
    message(FATAL_ERROR "verify_pak accepted changed content")
endif()
# Two inputs with the same pak name would produce duplicate entries; packer
# must refuse and leave no output behind.
file(MAKE_DIRECTORY "${WORK}/dupA" "${WORK}/dupB")
file(WRITE "${WORK}/dupA/same.txt" "A")
file(WRITE "${WORK}/dupB/same.txt" "B")
execute_process(COMMAND "${PACKER}" "${WORK}/dup.pak" "${WORK}/dupA/same.txt"
                        "${WORK}/dupB/same.txt"
                RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
if(rc EQUAL 0)
    message(FATAL_ERROR "packer accepted duplicate pak names: ${out}")
endif()
if(EXISTS "${WORK}/dup.pak")
    message(FATAL_ERROR "packer left an output file after refusing")
endif()

# More files than a pak can hold must fail, not silently drop the excess.
file(MAKE_DIRECTORY "${WORK}/many")
foreach(i RANGE 0 4096)
    file(WRITE "${WORK}/many/f${i}" "")
endforeach()
execute_process(COMMAND "${PACKER}" "${WORK}/many.pak" "${WORK}/many"
                RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
if(rc EQUAL 0)
    message(FATAL_ERROR "packer silently truncated 4097 files: ${out}")
endif()
if(EXISTS "${WORK}/many.pak")
    message(FATAL_ERROR "packer left an output file after refusing")
endif()

# An existing pak is replaced only by a complete new one.
file(WRITE "${WORK}/keep.pak" "OLD")
execute_process(COMMAND "${PACKER}" "${WORK}/keep.pak" "${WORK}/many"
                RESULT_VARIABLE rc OUTPUT_QUIET ERROR_QUIET)
file(READ "${WORK}/keep.pak" kept)
if(NOT kept STREQUAL "OLD")
    message(FATAL_ERROR "a failed pack clobbered the existing output")
endif()
if(EXISTS "${WORK}/keep.pak.tmp")
    message(FATAL_ERROR "a failed pack left keep.pak.tmp behind")
endif()
file(REMOVE_RECURSE "${WORK}")
