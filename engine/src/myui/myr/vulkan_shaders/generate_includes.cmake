if(NOT DEFINED GLSLANG_VALIDATOR OR GLSLANG_VALIDATOR STREQUAL "")
  message(FATAL_ERROR "glslangValidator is required to regenerate myui Vulkan shaders")
endif()
if(NOT DEFINED SHADER_DIR OR NOT IS_DIRECTORY "${SHADER_DIR}")
  message(FATAL_ERROR "myui Vulkan shader directory is invalid: ${SHADER_DIR}")
endif()
if(NOT DEFINED OUTPUT_DIR OR NOT IS_DIRECTORY "${OUTPUT_DIR}")
  message(FATAL_ERROR "myui Vulkan shader output directory is invalid: ${OUTPUT_DIR}")
endif()

file(GLOB shader_files
  "${SHADER_DIR}/*.vert"
  "${SHADER_DIR}/*.frag")
list(SORT shader_files)
if(NOT shader_files)
  message(FATAL_ERROR "no Vulkan GLSL shaders found in ${SHADER_DIR}")
endif()

set(temp_dir "${CMAKE_CURRENT_BINARY_DIR}/myui_vulkan_shader_tmp")
file(MAKE_DIRECTORY "${temp_dir}")

foreach(shader_file IN LISTS shader_files)
  get_filename_component(shader_name "${shader_file}" NAME)
  get_filename_component(shader_stem "${shader_file}" NAME_WE)
  get_filename_component(shader_ext "${shader_file}" EXT)
  string(SUBSTRING "${shader_ext}" 1 -1 shader_stage)
  string(REPLACE "." "_" symbol_name "${shader_stem}_${shader_stage}")
  string(TOUPPER "${symbol_name}" symbol_name)

  set(spv_file "${temp_dir}/${shader_name}.spv")
  execute_process(
    COMMAND "${GLSLANG_VALIDATOR}" -V "${shader_file}" -o "${spv_file}"
    RESULT_VARIABLE compile_result
    OUTPUT_VARIABLE compile_output
    ERROR_VARIABLE compile_error)
  if(NOT compile_result EQUAL 0)
    message(FATAL_ERROR
      "glslangValidator failed for ${shader_file}:\n${compile_output}${compile_error}")
  endif()

  file(READ "${spv_file}" shader_hex HEX)
  string(LENGTH "${shader_hex}" hex_length)
  math(EXPR remainder "${hex_length} % 8")
  if(NOT remainder EQUAL 0)
    message(FATAL_ERROR "SPIR-V output is not a sequence of 32-bit words: ${spv_file}")
  endif()

  set(output_file "${OUTPUT_DIR}/${shader_name}.inc")
  file(WRITE "${output_file}"
    "/* generated from ${shader_name} by glslangValidator -V; do not edit */\n"
    "static const uint32_t VKSPV_${symbol_name}[] = {\n")
  set(line "")
  math(EXPR last_byte "${hex_length} - 1")
  foreach(offset RANGE 0 ${last_byte} 8)
    string(SUBSTRING "${shader_hex}" ${offset} 2 byte0)
    math(EXPR byte1_offset "${offset} + 2")
    math(EXPR byte2_offset "${offset} + 4")
    math(EXPR byte3_offset "${offset} + 6")
    string(SUBSTRING "${shader_hex}" ${byte1_offset} 2 byte1)
    string(SUBSTRING "${shader_hex}" ${byte2_offset} 2 byte2)
    string(SUBSTRING "${shader_hex}" ${byte3_offset} 2 byte3)
    string(APPEND line "  0x${byte3}${byte2}${byte1}${byte0}u,")
    string(LENGTH "${line}" line_length)
    if(line_length GREATER 90)
      file(APPEND "${output_file}" "${line}\n")
      set(line "")
    endif()
  endforeach()
  if(NOT line STREQUAL "")
    file(APPEND "${output_file}" "${line}\n")
  endif()
  file(APPEND "${output_file}" "};\n")
endforeach()
