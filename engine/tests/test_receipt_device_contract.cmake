if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()
foreach(required REPO_ROOT WORK)
    if(NOT DEFINED ${required})
        message(FATAL_ERROR "${required} is required")
    endif()
endforeach()
file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
function(contract_failure message_text)
    set_property(GLOBAL APPEND PROPERTY RECEIPT_DEVICE_CONTRACT_FAILURES "${message_text}")
endfunction()

function(generate_receipt name level device_type vendor_id device_id)
    set(out "${WORK}/${name}.json")
    execute_process(
        COMMAND "${CMAKE_COMMAND}"
            -DOUT=${out}
            -DPLATFORM=linux-wayland
            -DBACKEND=vulkan
            -DEVIDENCE_LEVEL=${level}
            -DRUNNER=local
            -DCOMMAND_STR=rhi_swapchain_bench
            -DGPU=test-device
            -DDRIVER_VERSION=1
            -DCPU=test-cpu
            -DRAM=test-ram
            -DBUILD_CONFIG=Release
            -DDEVICE_TYPE=${device_type}
            -DVENDOR_ID=${vendor_id}
            -DDEVICE_ID=${device_id}
            -DFPS_AVG=60
            -DFPS_P1=30
            -DFRAME_MS_AVG=16.6
            -DFRAME_MS_P99=33.3
            -P "${REPO_ROOT}/engine/tools/make_evidence_receipt.cmake"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out_text ERROR_VARIABLE err_text)
    if(NOT rc EQUAL 0)
        contract_failure("generator failed for ${name}: ${out_text}${err_text}\n")
    endif()
    set(RECEIPT_PATH "${out}" PARENT_SCOPE)
endfunction()

function(expect_schema name should_pass)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -DRECEIPT=${WORK}/${name}.json
            -P "${REPO_ROOT}/engine/tests/test_evidence_receipt_schema.cmake"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out_text ERROR_VARIABLE err_text)
    if(should_pass AND NOT rc EQUAL 0)
        contract_failure("schema rejected ${name}: ${out_text}${err_text}\n")
    elseif(NOT should_pass AND rc EQUAL 0)
        contract_failure("schema accepted invalid ${name}\n")
    endif()
endfunction()

function(expect_deck name expected_vendor expected_device should_pass expected_reason)
    set(hw_file "${WORK}/${name}.env")
    set(args
        -DRECEIPT=${WORK}/${name}.json
        -DOUT=${hw_file}
        "-DEXPECTED_VENDOR_ID=${expected_vendor}"
        "-DEXPECTED_DEVICE_ID=${expected_device}")
    if(NOT EXISTS "${WORK}/${name}.json")
        set(args -DRECEIPT=${WORK}/${name}.json -DOUT=${hw_file}
            "-DEXPECTED_VENDOR_ID=${expected_vendor}"
            "-DEXPECTED_DEVICE_ID=${expected_device}")
    endif()
    execute_process(
        COMMAND "${CMAKE_COMMAND}" ${args}
            -P "${REPO_ROOT}/engine/tools/check_steam_deck_hardware.cmake"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out_text ERROR_VARIABLE err_text)
    if(NOT rc EQUAL 0)
        contract_failure("deck evaluation errored for ${name}: ${out_text}${err_text}\n")
        return()
    endif()
    if(NOT EXISTS "${hw_file}")
        contract_failure("deck evaluation wrote no result for ${name}\n")
        return()
    endif()
    file(READ "${hw_file}" result)
    if(should_pass)
        set(expected "hardware_ok=true")
        set(expected_rc 0)
    else()
        set(expected "hardware_ok=false")
        set(expected_rc 1)
    endif()
    string(FIND "${result}" "${expected}" found)
    if(found EQUAL -1)
        contract_failure("deck ${name}: ${expected} missing: ${result}\n")
    endif()
    string(FIND "${result}" "hardware_reason=${expected_reason}" reason_found)
    if(reason_found EQUAL -1)
        contract_failure("deck ${name}: want reason ${expected_reason}: ${result}\n")
    endif()
    execute_process(
        COMMAND "${CMAKE_COMMAND}" ${args} -DREQUIRE=ON
            -P "${REPO_ROOT}/engine/tools/check_steam_deck_hardware.cmake"
        RESULT_VARIABLE require_rc OUTPUT_VARIABLE require_out ERROR_VARIABLE require_err)
    if(NOT require_rc EQUAL expected_rc)
        contract_failure("deck ${name}: Require rc=${require_rc}, want ${expected_rc}: ${require_out}${require_err}\n")
    endif()
endfunction()

generate_receipt(runtime-cpu GPU_RUNTIME CPU 0 0)
expect_schema(runtime-cpu TRUE)
generate_receipt(comparable-cpu BENCHMARK_COMPARABLE CPU 4098 4660)
expect_schema(comparable-cpu FALSE)
generate_receipt(comparable-unknown BENCHMARK_COMPARABLE UNKNOWN 4098 4660)
expect_schema(comparable-unknown FALSE)
generate_receipt(comparable-virtual BENCHMARK_COMPARABLE VIRTUAL 4098 4660)
expect_schema(comparable-virtual FALSE)
generate_receipt(comparable-other BENCHMARK_COMPARABLE OTHER 4098 4660)
expect_schema(comparable-other FALSE)
generate_receipt(comparable-integrated BENCHMARK_COMPARABLE INTEGRATED 4098 4660)
expect_schema(comparable-integrated TRUE)
generate_receipt(comparable-discrete BENCHMARK_COMPARABLE DISCRETE 4098 4660)
expect_schema(comparable-discrete TRUE)
generate_receipt(runtime-bogus GPU_RUNTIME BOGUS 4098 4660)
expect_schema(runtime-bogus FALSE)
generate_receipt(runtime-missing GPU_RUNTIME CPU 0 0)
file(READ "${WORK}/runtime-missing.json" missing_text)
string(REGEX REPLACE "  \"device_type\": \"CPU\",\n" "" missing_text "${missing_text}")
file(WRITE "${WORK}/runtime-missing.json" "${missing_text}")
expect_schema(runtime-missing FALSE)

expect_deck(comparable-integrated 0x1002 0x1234 TRUE ok)
expect_deck(comparable-discrete 4098 4660 TRUE ok)
expect_deck(comparable-cpu 4098 4660 FALSE cpu-not-comparable)
expect_deck(comparable-unknown 4098 4660 FALSE unknown-not-comparable)
expect_deck(comparable-virtual 4098 4660 FALSE virtual-not-comparable)
expect_deck(comparable-other 4098 4660 FALSE other-not-comparable)
expect_deck(comparable-integrated 0x10de 0x1234 FALSE vendor-mismatch)
expect_deck(comparable-integrated 0x1002 0x9999 FALSE device-mismatch)
expect_deck(comparable-integrated "" 0x1234 FALSE missing-config)
expect_deck(comparable-integrated 0x1002 "" FALSE missing-config)
expect_deck(comparable-integrated invalid 0x1234 FALSE missing-config)
expect_deck(no-such-receipt 0x1002 0x1234 FALSE receipt-missing)

get_property(failure_lines GLOBAL PROPERTY RECEIPT_DEVICE_CONTRACT_FAILURES)
if(failure_lines)
    string(REPLACE ";" "\n" failures "${failure_lines}")
    message(FATAL_ERROR "receipt device contract failed:\n${failures}\n")
endif()
message(STATUS "receipt device mapping/serialization/schema/Deck Require contract OK")
