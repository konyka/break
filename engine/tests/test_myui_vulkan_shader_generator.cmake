if(NOT DEFINED CMAKE_BIN OR NOT DEFINED GENERATOR OR NOT DEFINED SHADER_DIR OR
   NOT DEFINED OUTPUT_DIR OR NOT DEFINED GLSLANG_VALIDATOR)
    message(FATAL_ERROR
        "CMAKE_BIN, GENERATOR, SHADER_DIR, OUTPUT_DIR and GLSLANG_VALIDATOR are required")
endif()

file(MAKE_DIRECTORY "${OUTPUT_DIR}")
execute_process(
    COMMAND "${CMAKE_BIN}"
        -DGLSLANG_VALIDATOR=${GLSLANG_VALIDATOR}
        -DSHADER_DIR=${SHADER_DIR}
        -DOUTPUT_DIR=${OUTPUT_DIR}
        -P ${GENERATOR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Vulkan shader generation failed:\n${output}${error}")
endif()

foreach(shader_name
        flat.vert flat.frag tex.vert text.frag img.frag)
    if(NOT EXISTS "${OUTPUT_DIR}/${shader_name}.inc")
        message(FATAL_ERROR "missing generated shader include: ${shader_name}.inc")
    endif()
    file(READ "${OUTPUT_DIR}/${shader_name}.inc" shader_include LIMIT 256)
    if(NOT shader_include MATCHES "0x07230203u")
        message(FATAL_ERROR "generated shader has invalid SPIR-V header: ${shader_name}.inc")
    endif()
endforeach()
