if(NOT DEFINED AUDIO_EXTENDED OR NOT DEFINED AUDIO_DSP OR NOT DEFINED AUDIO_LEGACY)
    message(FATAL_ERROR "audio source paths are required")
endif()

function(assert_callback_clean path begin_marker end_marker)
    file(READ "${path}" source)
    string(FIND "${source}" "${begin_marker}" begin)
    if(end_marker STREQUAL "__EOF__")
        string(LENGTH "${source}" end)
    else()
        string(FIND "${source}" "${end_marker}" end)
    endif()
    if(begin LESS 0 OR end LESS 0 OR end LESS begin)
        message(FATAL_ERROR "callback markers not found in ${path}")
    endif()
    string(LENGTH "${begin_marker}" marker_length)
    math(EXPR body_begin "${begin} + ${marker_length}")
    math(EXPR body_length "${end} - ${body_begin}")
    string(SUBSTRING "${source}" ${body_begin} ${body_length} body)
    foreach(forbidden IN ITEMS malloc calloc realloc free fopen fread fwrite
            ma_decoder audio_event_trigger audio_music_update ext->ray)
        string(FIND "${body}" "${forbidden}" found)
        if(NOT found EQUAL -1)
            message(FATAL_ERROR "${forbidden} is forbidden in ${path}:${begin_marker}")
        endif()
    endforeach()
endfunction()

assert_callback_clean("${AUDIO_EXTENDED}" "static bool voice_dequeue"
                      "static void voice_finish")
assert_callback_clean("${AUDIO_EXTENDED}" "static void voice_finish"
                      "static void voice_configure_dsp")
assert_callback_clean("${AUDIO_EXTENDED}" "static void voice_configure_dsp"
                      "static void voice_drain_commands")
assert_callback_clean("${AUDIO_EXTENDED}" "static void voice_drain_commands"
                      "static void voice_advance_fade")
assert_callback_clean("${AUDIO_EXTENDED}" "static void voice_advance_fade"
                      "static ma_result voice_read")
assert_callback_clean("${AUDIO_EXTENDED}" "static ma_result voice_read"
                      "static ma_result voice_seek")
assert_callback_clean("${AUDIO_DSP}" "static u32 reverb_delay"
                      "void audio_dsp_chain_process")
assert_callback_clean("${AUDIO_DSP}" "void audio_dsp_chain_process" "__EOF__")

file(READ "${AUDIO_DSP}" dsp_source)
string(FIND "${dsp_source}" "usize base = (usize)frame * channels;" wide_index)
if(wide_index EQUAL -1)
    message(FATAL_ERROR "DSP frame indexing must widen before multiplication")
endif()

file(READ "${AUDIO_LEGACY}" legacy)
string(FIND "${legacy}" "MA_SOUND_FLAG_STREAM" stream_flag)
if(NOT stream_flag EQUAL -1)
    message(FATAL_ERROR "legacy playback must not stream from the audio callback")
endif()
string(FIND "${legacy}" "MA_SOUND_FLAG_DECODE" decode_flag)
if(decode_flag EQUAL -1)
    message(FATAL_ERROR "legacy file playback must decode before mixing")
endif()
string(FIND "${legacy}" "MA_SOUND_FLAG_NO_PITCH" no_pitch)
if(NOT no_pitch EQUAL -1)
    message(FATAL_ERROR "legacy decoded playback must retain pitch and Doppler")
endif()
