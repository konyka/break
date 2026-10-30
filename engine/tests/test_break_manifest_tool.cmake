# End-to-end for the OFFLINE release tooling (tools/break_manifest_tool.c):
#   keygen <private key file> <public key hex file>
#   build  <dir> <version> <channel> <platform> <min-version> <body out>
#   sign   <private key file> <body file> <manifest out>
# The client-side verifier (break_update_manifest_parse + _verify, driven by
# tools/break_manifest_verify.c) must accept the signed manifest with the
# generated public key, and reject it after any body byte changes or with
# another key.
# -DTOOL=<break_manifest_tool> -DVERIFY=<break_manifest_verify> -DWORK=<dir>
if(NOT DEFINED TOOL OR NOT DEFINED VERIFY OR NOT DEFINED WORK)
    message(FATAL_ERROR "TOOL, VERIFY and WORK are required")
endif()
file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}/rel/bin" "${WORK}/rel/data")
file(WRITE "${WORK}/rel/bin/engine" "alpha")
file(WRITE "${WORK}/rel/data/base.pak" "beta-beta")
file(WRITE "${WORK}/rel/a.txt" "")

function(run expect_ok)
    execute_process(COMMAND ${ARGN} RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(expect_ok AND NOT rc EQUAL 0)
        message(FATAL_ERROR "${ARGN} failed (${rc}): ${out}${err}")
    endif()
    if(NOT expect_ok AND rc EQUAL 0)
        message(FATAL_ERROR "${ARGN} unexpectedly succeeded: ${out}")
    endif()
endfunction()

run(TRUE "${TOOL}" keygen "${WORK}/k.priv" "${WORK}/k.pub")
run(TRUE "${TOOL}" keygen "${WORK}/k2.priv" "${WORK}/k2.pub")
run(FALSE "${TOOL}" keygen "${WORK}/k.priv" "${WORK}/k3.pub") # never overwrite a key
if(UNIX)
    execute_process(COMMAND ls -l "${WORK}/k.priv" OUTPUT_VARIABLE mode OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT mode MATCHES "^-rw-------")
        message(FATAL_ERROR "private key must be mode 600, got ${mode}")
    endif()
endif()
file(READ "${WORK}/k.pub" pub)
string(STRIP "${pub}" pub)
if(NOT pub MATCHES "^[0-9a-f]+$")
    message(FATAL_ERROR "public key file must be lowercase hex: ${pub}")
endif()
string(LENGTH "${pub}" publen)
if(NOT publen EQUAL 64)
    message(FATAL_ERROR "public key must be 32 bytes hex: ${pub}")
endif()

run(TRUE "${TOOL}" build "${WORK}/rel" 1.2.3 stable linux-x86-64 1.0.0 "${WORK}/body.txt")
file(READ "${WORK}/body.txt" body)
set(expect_head "break-manifest-v1\nversion: 1.2.3\nchannel: stable\nplatform: linux-x86-64\nmin-version: 1.0.0\n")
string(FIND "${body}" "${expect_head}" at)
if(NOT at EQUAL 0)
    message(FATAL_ERROR "unexpected manifest header:\n${body}")
endif()
# chunk lines sorted by name, sha256 of the file bytes, decimal size
file(SHA256 "${WORK}/rel/a.txt" ha)
file(SHA256 "${WORK}/rel/bin/engine" hb)
file(SHA256 "${WORK}/rel/data/base.pak" hc)
set(expect_body "${expect_head}chunk: ${ha} 0 a.txt\nchunk: ${hb} 5 bin/engine\nchunk: ${hc} 9 data/base.pak\n")
if(NOT body STREQUAL expect_body)
    message(FATAL_ERROR "manifest body mismatch:\n${body}\nexpected:\n${expect_body}")
endif()
run(FALSE "${TOOL}" build "${WORK}/rel" 1.2 stable linux-x86-64 1.0.0 "${WORK}/bad.txt")
run(FALSE "${TOOL}" build "${WORK}/rel" 1.2.3 Stable linux-x86-64 1.0.0 "${WORK}/bad.txt")

run(TRUE "${TOOL}" sign "${WORK}/k.priv" "${WORK}/body.txt" "${WORK}/manifest.txt")
run(TRUE "${VERIFY}" "${WORK}/manifest.txt" "${pub}")
file(READ "${WORK}/k2.pub" pub2)
string(STRIP "${pub2}" pub2)
run(FALSE "${VERIFY}" "${WORK}/manifest.txt" "${pub2}")
# a single changed byte in the signed body fails verification
file(READ "${WORK}/manifest.txt" signed)
string(REPLACE "version: 1.2.3" "version: 1.2.4" tampered "${signed}")
file(WRITE "${WORK}/tampered.txt" "${tampered}")
run(FALSE "${VERIFY}" "${WORK}/tampered.txt" "${pub}")
# signing an invalid body is refused
file(WRITE "${WORK}/junk.txt" "not a manifest\n")
run(FALSE "${TOOL}" sign "${WORK}/k.priv" "${WORK}/junk.txt" "${WORK}/junk.signed")
file(REMOVE_RECURSE "${WORK}")
message(STATUS "break_manifest_tool OK")
