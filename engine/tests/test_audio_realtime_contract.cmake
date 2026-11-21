if(NOT DEFINED AUDIO_EXTENDED OR NOT DEFINED AUDIO_DSP OR NOT DEFINED AUDIO_LEGACY OR
   NOT DEFINED AUDIO_HRTF OR NOT DEFINED AUDIO_CAPTURE)
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
assert_callback_clean("${AUDIO_EXTENDED}" "static void pcm_stream_filter_to"
                      "static ma_result pcm_stream_read")
assert_callback_clean("${AUDIO_EXTENDED}" "static ma_result pcm_stream_read"
                      "static ma_result pcm_stream_seek")
assert_callback_clean("${AUDIO_DSP}" "static u32 reverb_delay"
                      "void audio_dsp_chain_process")
assert_callback_clean("${AUDIO_DSP}" "void audio_dsp_chain_process" "__EOF__")
assert_callback_clean("${AUDIO_HRTF}" "AudioResult audio_hrtf_renderer_init" "__EOF__")

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
assert_callback_clean("${AUDIO_CAPTURE}" "static i16 capture_sample"
                      "AudioResult audio_capture_create")

# Store-then-load handshakes between the mixer and close/set_hrtf need a
# full fence on both sides: qemu-user on x86 hosts lets a seq_cst store
# pass a later seq_cst load, and close then frees a ring still being read.
file(READ "${AUDIO_EXTENDED}" extended_source)
foreach(pair IN ITEMS
        "atomic_store_explicit(&stream->reading, true, memory_order_seq_cst);|&stream->open"
        "atomic_store_explicit(&stream->open, false, memory_order_seq_cst);|&stream->reading"
        "atomic_store_explicit(&stream->hrtf_set, (uintptr_t)set, memory_order_seq_cst);|&stream->reading")
    string(FIND "${pair}" "|" bar)
    string(SUBSTRING "${pair}" 0 ${bar} handshake)
    math(EXPR after_bar "${bar} + 1")
    string(SUBSTRING "${pair}" ${after_bar} -1 loaded)
    string(FIND "${extended_source}" "${handshake}" store_at)
    if(store_at EQUAL -1)
        message(FATAL_ERROR "handshake store not found: ${handshake}")
    endif()
    string(SUBSTRING "${extended_source}" ${store_at} 400 after_store)
    string(FIND "${after_store}" "atomic_load_explicit(${loaded}," load_at)
    string(FIND "${after_store}" "atomic_thread_fence(memory_order_seq_cst);" fence_at)
    if(fence_at EQUAL -1 OR load_at EQUAL -1 OR NOT fence_at LESS load_at)
        message(FATAL_ERROR "handshake store needs a seq_cst fence before its load: ${handshake}")
    endif()
endforeach()
