if(NOT DEFINED RECEIPT)
    message(FATAL_ERROR "RECEIPT is required")
endif()
if(NOT EXISTS "${RECEIPT}")
    message(FATAL_ERROR "receipt missing: ${RECEIPT}")
endif()
file(READ "${RECEIPT}" receipt_text)
# 键存在性检查（不是 JSON 解析器；字段级校验以
# docs/rhi_benchmark_receipt_schema.md 的校验脚本为准，本检查是 CI 烟雾门）。
foreach(required_key
        "\"schema_version\"" "\"timestamp\"" "\"platform\"" "\"os_version\""
        "\"backend\"" "\"gpu\"" "\"driver_version\"" "\"cpu\"" "\"ram\""
        "\"build_commit\"" "\"build_config\"" "\"command\"" "\"metrics\""
        "\"fps_avg\"" "\"fps_p1\"" "\"frame_ms_avg\"" "\"frame_ms_p99\""
        "\"evidence_level\"" "\"runner\"")
    string(FIND "${receipt_text}" "${required_key}" key_offset)
    if(key_offset EQUAL -1)
        message(FATAL_ERROR "receipt missing key: ${required_key}")
    endif()
endforeach()
