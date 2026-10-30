# End-to-end: tools/break_keygen provisions per-device keys for
# `editor --remote-keyring-file`.
#   break_keygen <keyring> <16-hex key id> <device psk out>
# appends "<id> <64 hex psk>" to the keyring (created mode 0600 if missing),
# writes the same 32 raw PSK bytes to the device file (mode 0600, must not
# exist), refuses duplicate ids and invalid ids, and never touches either
# file on failure.
# -DKEYGEN=<break_keygen> -DWORK=<scratch dir>
if(NOT DEFINED KEYGEN OR NOT DEFINED WORK)
    message(FATAL_ERROR "KEYGEN and WORK are required")
endif()
file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
set(RING "${WORK}/ring.txt")

function(keygen expect_ok)
    execute_process(COMMAND "${KEYGEN}" ${ARGN}
                    RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(expect_ok AND NOT rc EQUAL 0)
        message(FATAL_ERROR "break_keygen ${ARGN} failed (${rc}): ${out}${err}")
    endif()
    if(NOT expect_ok AND rc EQUAL 0)
        message(FATAL_ERROR "break_keygen ${ARGN} unexpectedly succeeded")
    endif()
endfunction()

keygen(TRUE "${RING}" 6465766963653031 "${WORK}/dev1.psk")
keygen(TRUE "${RING}" 6465766963653032 "${WORK}/dev2.psk")
file(STRINGS "${RING}" lines)
list(LENGTH lines n)
if(NOT n EQUAL 2)
    message(FATAL_ERROR "keyring should hold 2 lines, got ${n}: ${lines}")
endif()
list(GET lines 0 l0)
list(GET lines 1 l1)
if(NOT l0 MATCHES "^6465766963653031 [0-9a-f]+$" OR NOT l1 MATCHES "^6465766963653032 [0-9a-f]+$")
    message(FATAL_ERROR "unexpected keyring lines: ${lines}")
endif()
string(LENGTH "${l0}" len0)
if(NOT len0 EQUAL 81)
    message(FATAL_ERROR "keyring line must be 16+1+64 chars: ${l0}")
endif()
# the device file is the same secret as raw bytes
file(READ "${WORK}/dev1.psk" raw HEX)
string(LENGTH "${raw}" rawlen)
if(NOT rawlen EQUAL 64)
    message(FATAL_ERROR "device psk must be 32 bytes, got hex ${raw}")
endif()
string(SUBSTRING "${l0}" 17 64 hex0)
if(NOT raw STREQUAL hex0)
    message(FATAL_ERROR "device psk ${raw} does not match keyring ${hex0}")
endif()
# two keys are different
string(SUBSTRING "${l1}" 17 64 hex1)
if(hex0 STREQUAL hex1)
    message(FATAL_ERROR "two generated keys are identical")
endif()
if(UNIX)
    execute_process(COMMAND stat -c %a "${RING}" OUTPUT_VARIABLE m1 OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND stat -c %a "${WORK}/dev1.psk" OUTPUT_VARIABLE m2 OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT m1 STREQUAL "600" OR NOT m2 STREQUAL "600")
        message(FATAL_ERROR "files must be mode 600: ring ${m1}, psk ${m2}")
    endif()
endif()

file(READ "${RING}" before)
# duplicate id, bad id, existing device file, missing args: all fail and
# leave the keyring untouched
keygen(FALSE "${RING}" 6465766963653031 "${WORK}/dev3.psk")
if(EXISTS "${WORK}/dev3.psk")
    message(FATAL_ERROR "failed run left a device file behind")
endif()
keygen(FALSE "${RING}" 64657669636530 "${WORK}/dev4.psk")
keygen(FALSE "${RING}" zz65766963653033 "${WORK}/dev5.psk")
keygen(FALSE "${RING}" 6465766963653033 "${WORK}/dev1.psk")
keygen(FALSE "${RING}")
file(READ "${RING}" after)
if(NOT before STREQUAL after)
    message(FATAL_ERROR "a failed run modified the keyring")
endif()
# a full ring (8 keys) refuses a ninth
foreach(i 3 4 5 6 7 8)
    keygen(TRUE "${RING}" 646576696365300${i} "${WORK}/d${i}.psk")
endforeach()
keygen(FALSE "${RING}" 6465766963653039 "${WORK}/d9.psk")
file(REMOVE_RECURSE "${WORK}")
message(STATUS "break_keygen OK")
