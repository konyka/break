# NoModule / _nomodule__Runtime__Source__Runtime__RadAudioCodec__SDK

- module root: `.`
- headers: 27; symbols: 1131
- symbol kinds: enum=12, enumerator=51, externvar=7, function=52, macro=620, member=179, namespace=2, prototype=96, struct=25, typedef=44, union=1, variable=42

### `Source/Runtime/RadAudioCodec/SDK/Include/rada_decode.h` (Other)


#### struct `SeekTableEnumerationState`  
`struct SeekTableEnumerationState`  
_L129-133_
- L131 _public member_ `uint64_t state[2];`
- L132 _public function_ `SeekTableEnumerationState()`

#### enum `RadASeekTableReturn`  
`enum class RadASeekTableReturn`  
_L135-148_
- L138 _public enumerator_ `Done` — All seek table entries have been decoded
- L139 _public enumerator_ `InvalidParam`
- L141 _public enumerator_ `InvalidData` — The input data is invalid in some way
- L144 _public enumerator_ `NeedsMoreData` — The buffer provided needs to be advanced by the bytes consumed, filled up, and the function called again.
- L147 _public enumerator_ `Needs64Bits` — The seek table output is too big for 32 bits, start over with 64 bits.

#### enum `RadAExamineBlockResult`  
`enum class RadAExamineBlockResult : uint8_t`  
_L200-208_
- L203 _public enumerator_ `Valid` — The buffer provided can be passed to RadADecodeBlock and expect to succeed.
- L205 _public enumerator_ `Incomplete` — We need more data in order to determine. OutBufferLenBytesNeeded contained how much we need.
- L207 _public enumerator_ `Invalid` — The buffer can't be decoded.

#### Free symbols / members of external scopes

- L27 _macro_ `#define RADA_LIBRARY_VERSION 1` — RADA compatibility version - if these are the same the exports are named the same so we expect that if the linker selects a different copy they all work.
- L30 _macro_ `#define RR_STRING_JOIN3(arg1, arg2, arg3) RR_STRING_JOIN_DELAY3(arg1, arg2, arg3)`
- L31 _macro_ `#define RR_STRING_JOIN_DELAY3(arg1, arg2, arg3) RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3)`
- L32 _macro_ `#define RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3) arg1 ## arg2 ## arg3`
- L36 _macro_ `#define RR_STRING_JOIN(arg1, arg2) RR_STRING_JOIN_DELAY(arg1, arg2)`
- L37 _macro_ `#define RR_STRING_JOIN_DELAY(arg1, arg2) RR_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L38 _macro_ `#define RR_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L42 _macro_ `#define RADA_NAME(name) RR_STRING_JOIN3(RADA_WRAP, name##_, RADA_LIBRARY_VERSION )`
- L47 _macro_ `#define RadAGetFileHeader RADA_NAME(RadAGetFileHeader)`
- L48 _macro_ `#define RadAGetSeekTableHeader RADA_NAME(RadAGetSeekTableHeader)`
- L49 _macro_ `#define RadAStripSeekTable RADA_NAME(RadAStripSeekTable)`
- L50 _macro_ `#define RadAGetMemoryNeededToOpen RADA_NAME(RadAGetMemoryNeededToOpen)`
- L51 _macro_ `#define RadAOpenDecoder RADA_NAME(RadAOpenDecoder)`
- L52 _macro_ `#define RadADecodeSeekTable RADA_NAME(RadADecodeSeekTable)`
- L53 _macro_ `#define RadADirectSeekTableLookup RADA_NAME(RadADirectSeekTableLookup)`
- L54 _macro_ `#define RadASeekTableLookup RADA_NAME(RadASeekTableLookup)`
- L55 _macro_ `#define RadAExamineBlock RADA_NAME(RadAExamineBlock)`
- L56 _macro_ `#define RadANotifySeek RADA_NAME(RadANotifySeek)`
- L57 _macro_ `#define RadADecodeBlock RADA_NAME(RadADecodeBlock)`
- L58 _macro_ `#define RadAInterleave RADA_NAME(RadAInterleave)`
- L62 _function_ `static uint32_t RadAGetSeekTableSizeOnDisk(const RadAFileHeader* FileHeader)` — The number of bytes the seek table takes up on disk. It exists after RadABytesToOpen, and before RadABytesToFirstBlock
- L78 _function_ `static uint32_t RadAGetBytesToOpen(const RadAFileHeader* FileHeader)` — Returns the number of bytes of the rada file have to be in memory in order to call RadAOpenDecoder. Since this requires a valid file header, getting the size to open is a two phase operation: read the file header (sizeof(FileHeader)), then query the file header with this function. This is also the offset to the first encoded block.
- L90 _function_ `static uint32_t RadAGetOffsetToSeekTable(const RadAFileHeader* FileHeader)`
- L101 _prototype_ `const RadAFileHeader* RadAGetFileHeader(const uint8_t* InFileData, size_t InFileDataLenBytes);` — Returns a pointer to the file header from the given data. The header will be validated. This function needs at least sizeof(RadAFileHeader) passed to it to succeed. If insufficient data is provided, or the header is incorrect in any way, 0 is returned.
- L102 _prototype_ `const RadASeekTableHeader* RadAGetSeekTableHeader(const uint8_t* InFileData, size_t InFileDataLenBytes);`
- L105 _function_ `static const RadAFileHeader* RadAGetFileHeaderFromContainer(const RadAContainer* InContainer)` — Retrieves the file header from an opened decoder.
- L109 _prototype_ `size_t RadAStripSeekTable(uint8_t* InFileData, size_t InFileDataLenBytes);` — Removes the seek table, if present, from the given file and returns the new size of the data. Returns 0 on invalid file.
- L118 _prototype_ `int32_t RadAGetMemoryNeededToOpen(const uint8_t* InFileData, size_t InFileDataLenBytes, uint32_t* OutMemoryRequired);` — Gets the size of the RadAContainer to pass to RadAOpenDecoder. You use this to determine how much to allocate for the entirely of the decoder structure (note: you are responsible for allocating seek table space yourself) returns: 0 on success -1 on bad data >0 is the amount of file data we need to make progress in getting the result. This can happen multiple times in a row.
- L126 _prototype_ `int32_t RadAOpenDecoder(const uint8_t* InFileData, size_t InFileDataLenBytes, RadAContainer* InContainer, size_t InContainerBytes);` — InData is the file data loaded in to memory. The amount to read is specified by RadABytesToOpen(). InContainer must be allocated to the size specified by RadAGetMemoryNeeded. When done decoding, no function needs to be called, just free the container. RadAContainer* Container = malloc(RadAGetMemoryNeeded()); RadAOpenDecoder(FileData, FileDataSize, Container, RadAGetMemoryNeeded()); Returns 1 on success, 0 on fail.
- L184 _prototype_ `RadASeekTableReturn RadADecodeSeekTable(const RadAFileHeader* InFileHeader, const RadASeekTableHeader* InSeekHeader, uint8_t* InSeekTableData, size_t InSeekTableDataLenBytes, bool InSeekTableIs64Bits, SeekTableEnumerationState* InOutEnumerationState, uint8_t* OutSeekTableSamples, uint8_t* OutSeekTableBytes, size_t* OutConsumed);` — Iteratively decode the seek table in to your own management structures. This is to facilitate allocating during opening or needing a large stack. InData is the on disk encoded seek table. This is offset from the beginning of the file at RadABytesToOpen(). This can be streamed in chunks, but to get the entire table you'll need to overall provide RadASeekTableSizeOnDisk() to the function (at which point it will return ::Done. OutSeekTableSamples and OutSeekTableBytes need to be point to arrays of either uint32s or uint64s based on whether InSeekTableIs64Bits, of size InFileHeader->seek_table_entry_count. OutConsumed will emit how much of the buffer got consumed this run. This might not be completely consumed before more data is needed. You can of course just pass the entire seek table in one go. Roughly: SeekTableEnumerationState EnumState; for (;;) { size_t bytes_consumed = 0; RadASeekTableReturn result = RadADecodeSeekTable(file_header, seek_table_buffer, seek_table_buffer_valid_bytes, false, &EnumState, ptr_to_samples, ptr_to_bytes, &bytes_consumed); if (result == RadASeekTableReturn::Done) break; if (result != RadASeekTableReturn::NeedsMoreData) return failure; seek_table_bytes_remaining -= bytes_consumed; seek_table_buffer_valid -= bytes_consumed; if (seek_table_bytes_remaining == 0) return MilesDecoderOpenReturnFail; // they asked for more data but exceed what they said they'd need! }
- L195 _prototype_ `size_t RadADirectSeekTableLookup(const uint8_t* InFileData, size_t InFileDataLenBytes, uint64_t InTargetFrame, size_t* OutFrameAtLocation, size_t* OutFrameBlockSize);` — Look up where a given frame is in the file without doing a full decoder open. This is a binary search on the seek table and should be fairly fast. The return is 0 on failure, or the byte location of the encoded block that will provide the given frame. OutFrameAtLocation returns the frame that first gets emitted when decoding starts at that location, and OutFrameBlockSize will return the size required to decode the first block at that location. NOTE!! OutFrameBlockSize will allow you to decode at least 1 block, however due to the mDCT nature of the codec, one block must be "wasted" to prime the decoder before it starts to emit. So do not expect to get the desired frame out after one decode, and you may need more than that amount. That just gets you *a* block.
- L198 _prototype_ `size_t RadASeekTableLookup(const RadAContainer* InContainer, uint64_t InTargetFrame, size_t* OutFrameAtLocation, size_t* OutFrameBlockSize);` — Same as above, except if you've opened the decoder.
- L211 _prototype_ `RadAExamineBlockResult RadAExamineBlock(const RadAContainer* InContainer, const uint8_t* InBuffer, size_t InBufferLenBytes, uint32_t* OutBufferLenBytesNeeded);` — Examine encoded data to determine how much data is needed to decode the next block.
- L214 _prototype_ `void RadANotifySeek(RadAContainer* InContainer);` — This function must be called before RadADecodeBlock if data from the file is not provided sequentially.
- L217 _variable_ `constexpr uint32_t RadADecodeBlock_MaxOutputFrames = 1024;` — A single call to RadADecodeBlock can never put more than this number of frames in to the output reservoir.
- L219 _macro_ `#define RadADecodeBlock_Error -2`
- L220 _macro_ `#define RadADecodeBlock_Done -1`
- L236 _prototype_ `int16_t RadADecodeBlock(RadAContainer* InContainer, const uint8_t* InBuffer, size_t InBufferLenBytes, float* InOutputBuffer, size_t InOutBufferStrideInFloats, size_t* OutConsumedBytes);` — Decode a single block of encoded rad audio data. The data provided shoulid have passed a RadAExamineBlock check beforehand. The return value is the number of frames decoded, or one of RadADecodeBlock_Error or RadADecodeBlock_Done, which indicates end of file. At most RadADecodeBlock_MaxOutputFrames will be emitted into the output buffer. It is normal for 0 frames to get emitted after a seek or the beginning of the file. InBuffer should be advanced by OutConsumedBytes, which should then point at the next block to pass to RadAExamineBlock.
- L242 _macro_ `#define RADA_HAS_INTERLEAVING` — utility function to interleave N buffers of float data into one output buffer of S16 (scales and clamps from -1.0 to 1 into -32768 to 32767)
- L243 _prototype_ `void RadAInterleave( int16_t * output, float const ** inputs, uint32_t input_count, uint32_t samples );`

### `Source/Runtime/RadAudioCodec/SDK/Include/rada_encode.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define RADA_LIBRARY_VERSION 1`
- L8 _macro_ `#define RR_STRING_JOIN3(arg1, arg2, arg3) RR_STRING_JOIN_DELAY3(arg1, arg2, arg3)`
- L9 _macro_ `#define RR_STRING_JOIN_DELAY3(arg1, arg2, arg3) RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3)`
- L10 _macro_ `#define RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3) arg1 ## arg2 ## arg3`
- L14 _macro_ `#define RR_STRING_JOIN(arg1, arg2) RR_STRING_JOIN_DELAY(arg1, arg2)`
- L15 _macro_ `#define RR_STRING_JOIN_DELAY(arg1, arg2) RR_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L16 _macro_ `#define RR_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L21 _macro_ `#define RADA_NAME(name) RR_STRING_JOIN3(RADA_WRAP, name##_, RADA_LIBRARY_VERSION )`
- L27 _typedef_ `typedef void* RadACompressAllocFnType(uintptr_t ByteCount);`
- L28 _typedef_ `typedef void RadACompressFreeFnType(void* Ptr);`
- L30 _macro_ `#define RADA_COMPRESS_SUCCESS 0`
- L31 _macro_ `#define RADA_COMPRESS_ERROR_CHANS 1`
- L32 _macro_ `#define RADA_COMPRESS_ERROR_SAMPLES 2`
- L33 _macro_ `#define RADA_COMPRESS_ERROR_RATE 3`
- L34 _macro_ `#define RADA_COMPRESS_ERROR_QUALITY 4`
- L35 _macro_ `#define RADA_COMPRESS_ERROR_ALLOCATORS 5`
- L36 _macro_ `#define RADA_COMPRESS_ERROR_OUTPUT 6`
- L37 _macro_ `#define RADA_COMPRESS_ERROR_SEEKTABLE 7`
- L38 _macro_ `#define RADA_COMPRESS_ERROR_SIZE 8`
- L39 _macro_ `#define RADA_COMPRESS_ERROR_ENCODER 9`
- L40 _macro_ `#define RADA_COMPRESS_ERROR_ALLOCATION 10`
- L42 _macro_ `#define RadAErrorString RADA_NAME(RadAErrorString)`
- L43 _macro_ `#define EncodeRadAFile RADA_NAME(EncodeRadAFile)`
- L44 _macro_ `#define RadAGetBuildVersion RADA_NAME(RadAGetBuildVersion)`
- L49 _macro_ `#define RADA_BUILD_VERSION (0x00000001U)` — The build version of the rad audio library in it's entirety. This is distinct from the compilation version that determine linker compatibility. This is incremented each time the library is released
- L52 _prototype_ `uint32_t RadAGetBuildVersion();` — Return the build version that the library was compiled with. This should match RADA_BUILD_VERSION!
- L56 _prototype_ `const char* RadAErrorString(uint8_t InError);` — Pass in one of the above values to get a human readable error, returned as a utf8 string.
- L58 _variable_ `static const uint32_t RADA_MAX_CHANS = 32;`
- L59 _variable_ `static const uint32_t RADA_VALID_RATES[] = {48000, 44100, 32000, 24000};`
- L78 _prototype_ `uint8_t EncodeRadAFile( void* InPcmData, uint64_t InPcmDataLen, uint32_t InPcmRate, uint8_t InPcmChannels, uint8_t InQuality, uint8_t InSeamlessLooping, uint8_t InGenerateSeekTable, uint16_t InSeekTableMaxEntries, RadACompressAllocFnType* InMemAlloc, RadACompressFreeFnType* InMemFree, void** OutData, uint64_t* OutDataLen);`

### `Source/Runtime/RadAudioCodec/SDK/Include/rada_file_header.h` (Other)


#### enum `ERadASampleRate`  
`enum class ERadASampleRate : uint8_t`  
_L9-16_
- L11 _public enumerator_ `Rate_24000`
- L12 _public enumerator_ `Rate_32000`
- L13 _public enumerator_ `Rate_44100`
- L14 _public enumerator_ `Rate_48000`
- L15 _public enumerator_ `Rate_COUNT`

#### struct `RadAFileHeader`  
`struct RadAFileHeader`  
_L18-47_
- L20 _public member_ `uint32_t tag;` — RADA
- L23 _public member_ `uint32_t bytes_for_first_decode;` — Bytes from the file necessary to completely decode the first block of audio.
- L25 _public member_ `uint8_t version;`
- L26 _public member_ `uint8_t channels;`
- L29 _public member_ `uint16_t rada_header_bytes;` — Bytes of rad audio stream header data, located right after RadAFileHeader.
- L30 _public member_ `uint8_t shift_bits_for_seek_table_samples;`
- L31 _public member_ `uint8_t bits_for_seek_table_bytes;`
- L32 _public member_ `uint8_t bits_for_seek_table_samples;`
- L33 _public member_ `ERadASampleRate sample_rate;`
- L36 _public member_ `uint64_t frame_count;` — total number of samples/frames in the file.
- L38 _public member_ `uint64_t file_size;`
- L40 _public member_ `uint16_t seek_table_entry_count;`
- L44 _public member_ `uint16_t max_block_size;` — The maximum size of any block of audio, including any RadA block header. This can be used to allocate a buffer that can be used to decode the entire file one block at a time.
- L46 _public member_ `uint16_t PADDING[2];`

#### struct `RadASeekTableHeader`  
`struct RadASeekTableHeader`  
_L49-57_
- L51 _public member_ `int64_t byte_line_slope[2];`
- L52 _public member_ `int64_t byte_intercept;`
- L53 _public member_ `int64_t byte_bias;`
- L54 _public member_ `int64_t sample_line_slope[2];`
- L55 _public member_ `int64_t sample_intercept;`
- L56 _public member_ `int64_t sample_bias;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define RADA_SYNC_BYTE (0b01010101)`
- L7 _macro_ `#define RADA_MAX_CHANNELS 32`
- L59 _function_ `static uint32_t RadASampleRateFromEnum(ERadASampleRate InRate)`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/cpux86.h` (Other)


#### Free symbols / members of external scopes

- L11 _macro_ `#define RADAUDIO_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L13 _macro_ `#define RADAUDIO_NAME(name) ( name )`
- L17 _macro_ `#define RRX86_CPU_INITIALIZED (1U<<0) // bit gets set on CPUx86_detect() call`
- L18 _macro_ `#define RRX86_CPU_SSE2 (1U<<1)`
- L19 _macro_ `#define RRX86_CPU_SSSE3 (1U<<2)`
- L20 _macro_ `#define RRX86_CPU_SSE41 (1U<<3)`
- L21 _macro_ `#define RRX86_CPU_SSE42 (1U<<4)`
- L22 _macro_ `#define RRX86_CPU_AVX (1U<<5)`
- L23 _macro_ `#define RRX86_CPU_BMI1 (1U<<6) // bit manipulation instructions 1`
- L24 _macro_ `#define RRX86_CPU_BMI2 (1U<<7) // bit manipulation instructions 2`
- L25 _macro_ `#define RRX86_CPU_AVX2 (1U<<8)`
- L26 _macro_ `#define RRX86_CPU_AMD_ZEN (1U<<9) // not a CPUID bit; checks for AMD Zen uArch chips`
- L27 _macro_ `#define RRX86_CPU_F16C (1U<<10) // float16 conversion instructions`
- L28 _macro_ `#define RRX86_CPU_AVX512 (1U<<11) // Skylake feature set: AVXF512{F,VL,BW,DQ}`
- L29 _macro_ `#define RRX86_CPU_PREFER512 (1U<<12) // Set when 512-bit vector usage is preferred with no major caveats`
- L30 _macro_ `#define RRX86_CPU_POPCNT (1U<<13)`
- L41 _macro_ `#define g_rrCPUx86_feature_flags (RRX86_CPU_INITIALIZED | RRX86_CPU_SSE2 | RRX86_CPU_SSSE3 | RRX86_CPU_SSE41 | RRX86_CPU_SSE42 | RRX86_CPU_AVX | RRX86_CPU_BMI1 | RRX86_CPU_F16C) // these are known on Jaguar`
- L42 _macro_ `#define rrCPUx86_detect() /**/`
- L46 _macro_ `#define g_rrCPUx86_feature_flags (RRX86_CPU_INITIALIZED | RRX86_CPU_SSE2 | RRX86_CPU_SSSE3 | RRX86_CPU_SSE41 | RRX86_CPU_SSE42 | RRX86_CPU_AVX | RRX86_CPU_BMI1 | RRX86_CPU_BMI2 | RRX86_CPU_AVX2 | RRX86_CPU_AMD_ZEN | RRX86_CPU_F16C) // Zen 2`
- L53 _macro_ `#define RRX86_CPU_DYNAMIC_DETECT` — feel free to add other known targets before here this is the fallback where we CPUID at runtime
- L55 _macro_ `#define g_rrCPUx86_feature_flags RADAUDIO_NAME(g_rrCPUx86_feature_flags)`
- L56 _macro_ `#define rrCPUx86_detect RADAUDIO_NAME(rrCPUx86_detect)`
- L59 _externvar_ `extern "C" U32 g_rrCPUx86_feature_flags`
- L60 _prototype_ `extern "C" void rrCPUx86_detect()`
- L62 _externvar_ `extern U32 g_rrCPUx86_feature_flags;`
- L63 _prototype_ `extern void rrCPUx86_detect();`
- L70 _function_ `static RADINLINE U8 rrCPUx86_feature_present(U32 bit)`
- L78 _function_ `static RADINLINE U8 rrCPUx86_all_features_present(U32 bits)`
- L89 _macro_ `#define rrCPUx86_feature_present(bit) (false)` — #define rrCPUx86_detect()		 /
- L90 _macro_ `#define rrCPUx86_all_features_present(bits) (false)`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/egttypes.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define __EGTTYPESH__`
- L7 _macro_ `#define __RADTYPESH__`
- L8 _macro_ `#define __RADRR_COREH__ // block old rr_core`
- L65 _macro_ `#define RADDEFFUNC extern "C"`
- L66 _macro_ `#define RADDEFSTART extern "C" {`
- L67 _macro_ `#define RADDEFEND }`
- L68 _macro_ `#define RADDEFAULT( val ) =val`
- L70 _macro_ `#define RADDEFFUNC`
- L71 _macro_ `#define RADDEFSTART`
- L72 _macro_ `#define RADDEFEND`
- L73 _macro_ `#define RADDEFAULT( val )`
- L78 _macro_ `#define RR_STRINGIZE( L ) #L` — preprocessor string stuff
- L79 _macro_ `#define RR_DO_MACRO( M, X ) M(X)`
- L80 _macro_ `#define RR_STRINGIZE_DELAY( X ) RR_DO_MACRO( RR_STRINGIZE, X )`
- L82 _macro_ `#define RR_STRING_JOIN(arg1, arg2) RR_STRING_JOIN_DELAY(arg1, arg2)`
- L83 _macro_ `#define RR_STRING_JOIN_DELAY(arg1, arg2) RR_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L84 _macro_ `#define RR_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L87 _macro_ `#define RR_PLATFORM_PATH_STR( plat, file ) RR_STRINGIZE_DELAY( RR_STRING_JOIN( plat, file ) )` — makes "plat/plat_file"
- L101 _macro_ `#define __RADANDROID__ 1`
- L102 _macro_ `#define __RADDETECTED__ __RADANDROID__`
- L106 _macro_ `#define __RADQNX__ 2`
- L107 _macro_ `#define __RADDETECTED__ __RADQNX__`
- L118 _macro_ `#define RAD_WINAPI_IS_APP (!WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))`
- L120 _macro_ `#define __RADWINRTAPI__`
- L121 _macro_ `#define __RADWINRT__ 13`
- L122 _macro_ `#define __RADDETECTED__ __RADWINRT__`
- L125 _macro_ `#define RAD_WINAPI_IS_APP 0`
- L130 _macro_ `#define __RADNT__ 14` — if we aren't WinRT, then we are plain old NT
- L131 _macro_ `#define __RADDETECTED__ __RADNT__`
- L138 _macro_ `#define __RADIPHONE__ 15`
- L139 _macro_ `#define __RADIPHONESIM__ 16`
- L140 _macro_ `#define __RADDETECTED__ __RADIPHONESIM__`
- L143 _macro_ `#define __RADDETECTED__ __RADIPHONE__`
- L145 _macro_ `#define __RADMAC__ 17`
- L146 _macro_ `#define __RADDETECTED__ __RADMAC__`
- L150 _macro_ `#define __RADIOS__ 18`
- L153 _macro_ `#define __RADTVOS__ 19`
- L156 _macro_ `#define __RADWATCHOS__ 20`
- L161 _macro_ `#define __RADEMSCRIPTEN__ 22`
- L162 _macro_ `#define __RADDETECTED__ __RADEMSCRIPTEN__`
- L167 _macro_ `#define __RADLINUX__ 3`
- L168 _macro_ `#define __RADDETECTED__ __RADLINUX__`
- L173 _macro_ `#define __RADUNKNOWN__ 99` — this is the catch all, when you aren't building internally at rad
- L174 _macro_ `#define __RADDETECTED__ __RADUNKNOWN__`
- L187 _macro_ `#define __RAD32__ // we have no non-at-least-32-bit cpus any more`
- L190 _macro_ `#define __RADARM__ 1`
- L191 _macro_ `#define __RADDETECTEDPROC__ __RADARM__`
- L192 _macro_ `#define __RADLITTLEENDIAN__`
- L194 _macro_ `#define __RADNEON__`
- L197 _macro_ `#define __RADSOFTFP__`
- L201 _macro_ `#define __RADX86__ 2`
- L204 _macro_ `#define __RADMMX__` — only use mmx on PC, Win, Linux - not iphone sim!
- L206 _macro_ `#define __RADDETECTEDPROC__ __RADX86__`
- L211 _macro_ `#define __RADX64__ 3`
- L215 _macro_ `#define __RADDETECTEDPROC__ __RADX64__`
- L219 _macro_ `#define __RADPPC__ 4`
- L220 _macro_ `#define __RADALTIVEC__`
- L221 _macro_ `#define __RADDETECTEDPROC__ __RADPPC__`
- L222 _macro_ `#define __RADBIGENDIAN__`
- L226 _macro_ `#define __RADARM64__ 6`
- L227 _macro_ `#define __RADDETECTEDPROC__ __RADARM64__`
- L232 _macro_ `#define __RADDETECTEDPROC__`
- L241 _macro_ `#define __RAD64__`
- L242 _macro_ `#define __RAD64REGS__ // need to set this for platforms that aren't 64-bit, but have 64-bit regs (old consoles)`
- L256 _macro_ `#define RADEXPFUNC RADDEFFUNC` — if we are in a static lib, or exports are off, or if we are in an EXE we asked for no exe exports (or imports) then EXPFUNC is just a normal function
- L260 _macro_ `#define RADEXPFUNC RADDEFFUNC RADDLLEXPORTDLL`
- L262 _macro_ `#define RADEXPFUNC RADDEFFUNC RADDLLIMPORTDLL`
- L267 _macro_ `#define RADRESTRICT __restrict`
- L268 _macro_ `#define RADSTRUCT struct __attribute__((__packed__))`
- L270 _macro_ `#define RADLINK`
- L271 _macro_ `#define RADEXPLINK`
- L272 _macro_ `#define RADDLLEXPORTDLL __attribute__((visibility("default")))`
- L273 _macro_ `#define RADDLLIMPORTDLL`
- L281 _macro_ `#define RADEXPLINK RADLINK`
- L282 _macro_ `#define RADDLLEXPORTDLL`
- L291 _macro_ `#define RADLINK __attribute__((cdecl))`
- L292 _macro_ `#define RADEXPLINK __attribute__((cdecl))`
- L304 _macro_ `#define __RADWIN__`
- L309 _macro_ `#define RADRESTRICT` — vc6 and older
- L310 _macro_ `#define __RADNOVARARGMACROS__`
- L312 _macro_ `#define RADSTRUCT struct`
- L314 _macro_ `#define RADLINK __stdcall`
- L315 _macro_ `#define RADEXPLINK __stdcall`
- L317 _macro_ `#define RADDLLEXPORTDLL __declspec(dllexport)`
- L323 _macro_ `#define RADDLLIMPORTDLL __declspec(dllimport)` — normal win32 dll import
- L342 _macro_ `#define __RADMACAPI__`
- L353 _macro_ `#define __RADMACH__`
- L368 _macro_ `#define __RADCARBON__`
- L380 _macro_ `#define RADEXPLINK EMSCRIPTEN_KEEPALIVE`
- L390 _macro_ `#define RADINLINE __inline`
- L392 _macro_ `#define RADINLINE inline`
- L401 _macro_ `#define RR_NUMBERNAME(name) RR_STRING_JOIN(name,__COUNTER__)`
- L403 _macro_ `#define RR_NUMBERNAME(name) RR_STRING_JOIN(name,__LINE__)`
- L411 _macro_ `#define RR_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L413 _macro_ `#define RR_COMPILER_ASSERT_UNUSED`
- L416 _macro_ `#define RR_COMPILER_ASSERT(exp) typedef char RR_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] RR_COMPILER_ASSERT_UNUSED`
- L423 _macro_ `#define RAD_S8 signed char`
- L424 _macro_ `#define RAD_U8 unsigned char`
- L425 _macro_ `#define RAD_U16 unsigned short`
- L426 _macro_ `#define RAD_S16 signed short`
- L429 _macro_ `#define RAD_U32 unsigned int`
- L430 _macro_ `#define RAD_S32 signed int`
- L434 _macro_ `#define RAD_SINTa __w64 signed __int64`
- L435 _macro_ `#define RAD_UINTa __w64 unsigned __int64`
- L438 _macro_ `#define RAD_UINTa unsigned long long` — non-vc.net compiler or /Wp64 turned off
- L439 _macro_ `#define RAD_SINTa signed long long`
- L448 _macro_ `#define RAD_SINTa __w64 signed long`
- L449 _macro_ `#define RAD_UINTa __w64 unsigned long`
- L453 _macro_ `#define RAD_SINTa signed long`
- L454 _macro_ `#define RAD_UINTa unsigned long`
- L456 _macro_ `#define RAD_SINTa signed int`
- L457 _macro_ `#define RAD_UINTa unsigned int`
- L462 _macro_ `#define RAD_F32 float`
- L463 _macro_ `#define RAD_F64 double`
- L466 _macro_ `#define RAD_U64 unsigned __int64`
- L467 _macro_ `#define RAD_S64 signed __int64`
- L469 _macro_ `#define RAD_U64 unsigned long long`
- L470 _macro_ `#define RAD_S64 signed long long`
- L480 _macro_ `#define S8_DEFINED`
- L481 _typedef_ `typedef RAD_S8 S8;`
- L485 _macro_ `#define U8_DEFINED`
- L486 _typedef_ `typedef RAD_U8 U8;`
- L490 _macro_ `#define S16_DEFINED`
- L491 _typedef_ `typedef RAD_S16 S16;`
- L495 _macro_ `#define U16_DEFINED`
- L496 _typedef_ `typedef RAD_U16 U16;`
- L500 _macro_ `#define S32_DEFINED`
- L501 _typedef_ `typedef RAD_S32 S32;`
- L505 _macro_ `#define U32_DEFINED`
- L506 _typedef_ `typedef RAD_U32 U32;`
- L510 _macro_ `#define S64_DEFINED`
- L511 _typedef_ `typedef RAD_S64 S64;`
- L515 _macro_ `#define U64_DEFINED`
- L516 _typedef_ `typedef RAD_U64 U64;`
- L520 _macro_ `#define F32_DEFINED`
- L521 _typedef_ `typedef RAD_F32 F32;`
- L525 _macro_ `#define F64_DEFINED`
- L526 _typedef_ `typedef RAD_F64 F64;`
- L530 _macro_ `#define SINTa_DEFINED`
- L531 _typedef_ `typedef RAD_SINTa SINTa;`
- L535 _macro_ `#define UINTa_DEFINED`
- L536 _typedef_ `typedef RAD_UINTa UINTa;`
- L540 _macro_ `#define RRBOOL_DEFINED`
- L541 _typedef_ `typedef S32 rrbool;`
- L542 _typedef_ `typedef S32 RRBOOL;`
- L549 _macro_ `#define S8 RAD_S8`
- L554 _macro_ `#define U8 RAD_U8`
- L559 _macro_ `#define S16 RAD_S16`
- L564 _macro_ `#define U16 RAD_U16`
- L569 _macro_ `#define S32 RAD_S32`
- L574 _macro_ `#define U32 RAD_U32`
- L579 _macro_ `#define S64 RAD_S64`
- L584 _macro_ `#define U64 RAD_U64`
- L589 _macro_ `#define F32 RAD_F32`
- L594 _macro_ `#define F64 RAD_F64`
- L599 _macro_ `#define SINTa RAD_SINTa`
- L604 _macro_ `#define UINTa RAD_UINTa`
- L609 _macro_ `#define rrbool S32`
- L610 _macro_ `#define RRBOOL S32`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_common.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L23-23_

#### struct `(anonymous)`  
``  
_L73-84_

#### enum `(anonymous)`  
``  
_L87-92_

#### enum `(anonymous)`  
``  
_L97-100_

#### struct `(anonymous)`  
``  
_L105-107_

#### struct `(anonymous)`  
``  
_L110-123_

#### struct `(anonymous)`  
``  
_L126-135_

#### struct `(anonymous)`  
``  
_L138-151_

#### union `__anon232b53c60808::(anonymous)`  
`union`  
_L147-150_

#### struct `(anonymous)`  
``  
_L154-172_

#### struct `(anonymous)`  
``  
_L175-192_

#### struct `(anonymous)`  
``  
_L195-198_

#### struct `(anonymous)`  
``  
_L201-204_

#### struct `(anonymous)`  
``  
_L207-217_

#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_COMMON_H`
- L5 _macro_ `#define MAX_VALID_VERSION 1`
- L17 _macro_ `#define FFT_ALIGN(type, name) RAD_ALIGN(type, name, 64)` — determined by the FFT code
- L20 _macro_ `#define RADAUDIO_PI 3.1415926535897932384626433832795028` — rather than fight with whether math.h is included we just name our own.
- L26 _macro_ `#define RADAUDIO_LONG_BLOCK_LEN 1024 // number of mdct coefficients for a long block`
- L27 _macro_ `#define RADAUDIO_SHORT_BLOCK_LEN 128 // number of mdct coefficients for a short block`
- L29 _macro_ `#define MAX_BANDS 24`
- L30 _macro_ `#define MAX_COEFFS 1024`
- L31 _macro_ `#define MAX_SUBBANDS 72`
- L32 _macro_ `#define MAX_SUBBANDS_QUANTIZED 56`
- L33 _macro_ `#define MAX_MDCT_SAMPLES 2048`
- L34 _macro_ `#define MAX_RADAUD_CHANNELS 2`
- L35 _macro_ `#define MAX_COEFF_PER_BAND 512`
- L36 _macro_ `#define MAX_COEFF_PER_SUBBAND 32`
- L38 _macro_ `#define MAX_RUNLEN 240`
- L39 _macro_ `#define END_OF_ZERORUN 255 // token indicating end of the zero-runlength data`
- L40 _macro_ `#define COARSE_RUNLEN_THRESHOLD 60 // runlengths larger than this have bottom two bits sent by varbits`
- L41 _macro_ `#define PREDICT_FIRST_BAND_EXP 0 // exponent to use as prediction for first band of left channel`
- L43 _macro_ `#define MAX_FINE_ENERGY_BITS 16`
- L44 _macro_ `#define COEFFS_PER_SUBBAND 16 // maximum`
- L46 _macro_ `#define EXPONENT_NEGATIVE_INFINITY -17 // encoding of -inf exponent, i.e. 0 amplitude`
- L47 _macro_ `#define EXPONENT_NEGATIVE_16 -16 // encoding of -16 exponent`
- L48 _macro_ `#define EXPONENT_ZERO 0`
- L49 _macro_ `#define EXPONENT_POSITIVE_14 14`
- L50 _macro_ `#define BAND_EXPONENT_NONE -17 // encoding indicating no data in band, i.e. -inf`
- L52 _macro_ `#define SUBBANDS_SKIP_EMPTY_BANDS true`
- L54 _macro_ `#define MACRO_BAND_SIZE 3`
- L55 _macro_ `#define LARGEST_BIASED_SUBBAND 63`
- L56 _macro_ `#define SUBBAND_BIAS_CENTER 12`
- L58 _macro_ `#define NUM_NZ_MODE 4 // num long block modes`
- L59 _macro_ `#define NUM_SELECTOR_MODES (NUM_NZ_MODE+1) // short blocks get separate selectors`
- L60 _macro_ `#define NUM_NZ_SELECTOR 4 // num selectors per mode`
- L61 _macro_ `#define NUM_NZ_HUFF 6 // number of nonzero huffman tables`
- L62 _macro_ `#define MAX_NZ_BLOCKS 12 // maximum number of nonzero 8-byte blocks`
- L64 _macro_ `#define CLAMPED_INTEGER_EXPONENT_TO_CODED_EXPONENT(is_neg_inf, n) \`
- L68 _macro_ `#define CODED_EXPONENT_TO_INTEGER(n) (n)`
- L70 _macro_ `#define MAX_ENCODED_BLOCK_BYTES 16383`
- L75 _member_ `U8 has_sse2;` (scope `__anon232b53c60208`)
- L76 _member_ `U8 has_ssse3;` (scope `__anon232b53c60208`)
- L77 _member_ `U8 has_sse4_1;` (scope `__anon232b53c60208`)
- L78 _member_ `U8 has_popcnt;` (scope `__anon232b53c60208`)
- L79 _member_ `U8 has_avx2;` (scope `__anon232b53c60208`)
- L80 _member_ `U8 padding[3];` (scope `__anon232b53c60208`)
- L84 _typedef_ `} radaudio_cpu_features;`
- L88 _enumerator_ `RADA_48000` (scope `__anon232b53c60303`)
- L89 _enumerator_ `RADA_44100` (scope `__anon232b53c60303`)
- L90 _enumerator_ `RADA_32000` (scope `__anon232b53c60303`)
- L91 _enumerator_ `RADA_24000` (scope `__anon232b53c60303`)
- L92 _typedef_ `} radaudio_samprate_code;`
- L93 _macro_ `#define RADAUDIO_NUM_RATES 4`
- L98 _enumerator_ `RADAUDIO_LONG` (scope `__anon232b53c60403`)
- L99 _enumerator_ `RADAUDIO_SHORT` (scope `__anon232b53c60403`)
- L106 _member_ `U16 bytes_bias[2][3];` (scope `__anon232b53c60508`) — bias for blocktype, num_channels
- L107 _typedef_ `} radaudio_block_header_biases;`
- L111 _member_ `U32 version;` (scope `__anon232b53c60608`)
- L112 _member_ `int num_channels;` (scope `__anon232b53c60608`)
- L113 _member_ `int sample_rate_mode;` (scope `__anon232b53c60608`)
- L115 _member_ `int sample_rate;` (scope `__anon232b53c60608`)
- L116 _member_ `S8 mantissa_param[2][MAX_BANDS][2];` (scope `__anon232b53c60608`)
- L117 _member_ `U8 subband_predicted_sum[MAX_BANDS];` (scope `__anon232b53c60608`)
- L118 _member_ `S8 subband_bias[MAX_BANDS];` (scope `__anon232b53c60608`)
- L119 _member_ `U16 bytes_bias;` (scope `__anon232b53c60608`)
- L120 _member_ `U8 nzmode_num64[NUM_NZ_MODE];` (scope `__anon232b53c60608`) — num64[3] is always 0 (not transmitted)
- L121 _member_ `S8 nzmode_huff[3][12];` (scope `__anon232b53c60608`)
- L122 _member_ `U8 nzmode_selectors[NUM_NZ_SELECTOR][NUM_SELECTOR_MODES];` (scope `__anon232b53c60608`) — other huffman table selectors
- L123 _typedef_ `} radaudio_stream_header_unpacked;`
- L128 _member_ `U8 num_8byte_chunks;` (scope `__anon232b53c60708`) — first 3-4 members get initialized by data
- L129 _member_ `U8 huffman_table_for_chunk[MAX_NZ_BLOCKS];` (scope `__anon232b53c60708`)
- L130 _member_ `U8 invert_chunk[MAX_NZ_BLOCKS];` (scope `__anon232b53c60708`) — 0 (don't invert) or 1 (invert)
- L133 _member_ `U8 num_chunks_per_huff[NUM_NZ_HUFF];` (scope `__anon232b53c60708`) — remaining members get initialized by code
- L134 _member_ `U8 source_pos[3][MAX_NZ_BLOCKS];` (scope `__anon232b53c60708`) — for each channel, where its source offset is, in blocks, separately for left & right
- L135 _typedef_ `} radaudio_nonzero_blockmode_descriptor;`
- L139 _member_ `int num_bands;` (scope `__anon232b53c60808`)
- L140 _member_ `int num_quantized_subbands;` (scope `__anon232b53c60808`)
- L141 _member_ `int num_quantized_coeffs;` (scope `__anon232b53c60808`)
- L142 _member_ `int band_exponent[MAX_BANDS];` (scope `__anon232b53c60808`) — MAX_BANDS
- L143 _member_ `U8 band_mantissa_bitcount[MAX_BANDS];` (scope `__anon232b53c60808`) — MAX_BANDS
- L144 _member_ `int band_mantissa[MAX_BANDS];` (scope `__anon232b53c60808`) — MAX_BANDS
- L145 _member_ `U16 quantized_subbands[MAX_SUBBANDS+7];` (scope `__anon232b53c60808`) — excess_read7
- L146 _member_ `S8 quantized_coeff_decode[MAX_COEFFS];` (scope `__anon232b53c60808`)
- L148 _member_ `int quantized_coeff_encode[MAX_COEFFS];` (scope `__anon232b53c60808::__anon232b53c6090a`) — encoder uses this space for full-size quantized coeffs
- L149 _prototype_ `FFT_ALIGN(F32, dequantized_coeff_decode[MAX_COEFFS]);` (scope `__anon232b53c60808::__anon232b53c6090a`) — decoder uses it for float dequantized coeffs
- L151 _typedef_ `} radaudio_block_data;`
- L155 _member_ `int rate;` (scope `__anon232b53c60a08`)
- L156 _member_ `int num_bands;` (scope `__anon232b53c60a08`)
- L157 _member_ `int num_quantized_coeffs;` (scope `__anon232b53c60a08`)
- L158 _member_ `int num_coeffs;` (scope `__anon232b53c60a08`)
- L159 _member_ `int num_subbands;` (scope `__anon232b53c60a08`)
- L160 _member_ `int num_quantized_subbands;` (scope `__anon232b53c60a08`)
- L161 _member_ `int num_bands_without_subbands;` (scope `__anon232b53c60a08`)
- L162 _member_ `int num_coeffs_for_band [MAX_BANDS];` (scope `__anon232b53c60a08`)
- L163 _member_ `int num_subbands_for_band [MAX_BANDS];` (scope `__anon232b53c60a08`) — only long blocks
- L166 _member_ `int first_subband_for_band [MAX_BANDS];` (scope `__anon232b53c60a08`) — computed values:
- L167 _member_ `int first_coeff_for_band [MAX_BANDS];` (scope `__anon232b53c60a08`)
- L168 _member_ `int num_coeffs_for_subband [MAX_SUBBANDS];` (scope `__anon232b53c60a08`)
- L169 _member_ `int first_coeff_for_subband[MAX_SUBBANDS];` (scope `__anon232b53c60a08`)
- L170 _member_ `float band_scale_encode [MAX_BANDS];` (scope `__anon232b53c60a08`)
- L171 _member_ `float band_scale_decode [MAX_BANDS];` (scope `__anon232b53c60a08`)
- L172 _typedef_ `} radaudio_rate_info;`
- L176 _member_ `rrbool final_block;` (scope `__anon232b53c60b08`)
- L177 _member_ `rrbool prev_block_short;` (scope `__anon232b53c60b08`)
- L178 _member_ `rrbool this_block_short;` (scope `__anon232b53c60b08`)
- L179 _member_ `rrbool next_block_short;` (scope `__anon232b53c60b08`)
- L180 _member_ `rrbool mid_side_encoded;` (scope `__anon232b53c60b08`)
- L181 _member_ `unsigned int num_channels_encoded;` (scope `__anon232b53c60b08`)
- L182 _member_ `rrbool disable_final_subband_predict;` (scope `__anon232b53c60b08`)
- L183 _member_ `rrbool predict_stereo_subband;` (scope `__anon232b53c60b08`)
- L184 _member_ `rrbool predict_stereo_exponent;` (scope `__anon232b53c60b08`)
- L185 _member_ `rrbool mid_side_bands;` (scope `__anon232b53c60b08`)
- L186 _member_ `unsigned int nonzero_bitarray_mode;` (scope `__anon232b53c60b08`)
- L188 _member_ `U32 block_bytes;` (scope `__anon232b53c60b08`)
- L189 _member_ `U32 num_runlength_array;` (scope `__anon232b53c60b08`)
- L190 _member_ `U32 vbstream0_length;` (scope `__anon232b53c60b08`)
- L191 _member_ `U32 final_samples_discard;` (scope `__anon232b53c60b08`) — number of fully-computed samples to discard from the final block
- L192 _typedef_ `} radaudio_block_header_unpacked;`
- L196 _member_ `U8 length;` (scope `__anon232b53c60c08`)
- L197 _member_ `U8 symbol;` (scope `__anon232b53c60c08`)
- L198 _typedef_ `} radaudio_huff_symbol;`
- L202 _member_ `U16 code;` (scope `__anon232b53c60d08`)
- L203 _member_ `U8 length;` (scope `__anon232b53c60d08`)
- L204 _typedef_ `} radaudio_huff_code;`
- L209 _member_ `radaudio_huff_code encode[256];` (scope `__anon232b53c60e08`)
- L212 _member_ `radaudio_huff_symbol decode[2048];` (scope `__anon232b53c60e08`)
- L215 _member_ `int dummy;` (scope `__anon232b53c60e08`) — so struct isn't empty (which is not allowed)
- L217 _typedef_ `} radaudio_huffman;`
- L220 _macro_ `#define LCG_MUL 2147001325` — BCPL lcg
- L221 _macro_ `#define LCG_ADD 715136305`
- L223 _function_ `static RADINLINE U32 lcg(U32 value)`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_common.inl` (Other)


#### enum `(anonymous)`  
``  
_L63-66_

#### struct `(anonymous)`  
``  
_L243-245_

#### enum `(anonymous)`  
``  
_L248-252_

#### struct `(anonymous)`  
``  
_L427-445_

#### Free symbols / members of external scopes

- L7 _variable_ `static int sample_rates[4] = { 48000, 44100, 32000, 24000, };`
- L18 _variable_ `static radaudio_huffman *rada_nonzero_bitflags_huff[6] = { &rada_nonzero_bitflags_huff0, &rada_nonzero_bitflags_huff1, &rada_nonzero_bitflags_huff2, &rada_nonzero_bitflags_huff3, &rada_nonzero_bitflags_huff4, &rada_nonzero_bitflags_huff5, };`
- L28 _variable_ `static radaudio_huffman *rada_nonzero_coefficient_pair_huff[4] = { &rada_nonzero_coefficient_pair_huff0, &rada_nonzero_coefficient_pair_huff1, &rada_nonzero_coefficient_pair_huff2, &rada_nonzero_coefficient_pair_huff3, };`
- L36 _variable_ `static radaudio_huffman *rada_nonzero_coefficient_big_huff[4] = { &rada_nonzero_coefficient_big_huff0, &rada_nonzero_coefficient_big_huff1, &rada_nonzero_coefficient_big_huff2, &rada_nonzero_coefficient_big_huff3, };`
- L64 _enumerator_ `HS_COEFF_PAIR=0` (scope `__anon9b4f70210103`) — nibble pairs
- L65 _enumerator_ `HS_COEFF_BIG=1` (scope `__anon9b4f70210103`) — values whose magnitude exceeeds 7
- L71 _function_ `static void compute_packorder(radaudio_nonzero_blockmode_descriptor *nz_desc)` — compute derived data about the bitflag byte packing to make decoding not require any branching. all 8-byte blocks that use the same huffman table will be packed together, and a table is built for how to reorder those to original order.
- L108 _function_ `static void radaudio_init_nz_desc(radaudio_nonzero_blockmode_descriptor nz_desc[4])`
- L116 _variable_ `static float *radaudio_windows [2] = { window_long , window_short };` — mdct windows
- L118 _function_ `static radaudio_cpu_features cpu_detect(void)`
- L137 _variable_ `static int rate_scale[4] = { 235,` — values to scale band energy by to "normalize" for sample rate
- L146 _function_ `static void compute_mantissa_bitcount(int rate_mode, int is_short_block, S8 mantissa_param[][MAX_BANDS][2], int *exponents, U8 *mantissa_bitcount)` — this function must compute same data in encoder and decoder so they stay in sync, so it's integer/fixed-point only
- L174 _function_ `static int radaudio_code_sample_rate(int rate)`
- L184 _function_ `static void compute_bias_set(radaudio_block_header_biases *bc, U16 bias)`
- L200 _macro_ `#define RADAUDIO_BLOCKFLAG_8BIT_PARITY (1u << 0)` — 0 overhead to use:
- L201 _macro_ `#define RADAUDIO_BLOCKFLAG_THIS_SHORT (1u << 1)`
- L202 _macro_ `#define RADAUDIO_BLOCKFLAG_NEXT_SHORT (1u << 2)`
- L203 _macro_ `#define RADAUDIO_BLOCKFLAG_STEREO (1u << 3)`
- L204 _macro_ `#define RADAUDIO_BLOCKFLAG_MIDSIDE_BANDS (1u << 4)`
- L205 _macro_ `#define RADAUDIO_BLOCKFLAG_PREDICT_SUBBAND_STEREO (1u << 5)`
- L206 _macro_ `#define RADAUDIO_BLOCKFLAG_PREDICT_EXPONENT_STEREO (1u << 6)`
- L207 _macro_ `#define RADAUDIO_BLOCKFLAG_16BIT_FLAGS (1u << 7)`
- L209 _macro_ `#define RADAUDIO_BLOCKFLAG_NONZERO_BITARRAY_MASK (3u << 8)` — if any of these are set, it costs one more byte:
- L210 _macro_ `#define RADAUDIO_BLOCKFLAG_DISABLE_SUBBAND_PREDICT (1u << 10)`
- L211 _macro_ `#define RADAUDIO_BLOCKFLAG_MIDSIDE_ENCODED (1u << 11)`
- L212 _macro_ `#define RADAUDIO_BLOCKFLAG_EXCESS_RUNLENGTH_ARRAY (1u << 12)`
- L213 _macro_ `#define RADAUDIO_BLOCKFLAG_EXCESS_VBSTREAM0_LENGTH (1u << 13)`
- L214 _macro_ `#define RADAUDIO_BLOCKFLAG_EXCESS_BLOCK_BYTES (1u << 14)`
- L215 _macro_ `#define RADAUDIO_BLOCKFLAG_FINAL (1u << 15)`
- L217 _macro_ `#define RADAUDIO_BLOCKFLAG_NONZERO_BITARRAY_MODE_GET(x) (((x) >> 8) & 3u)`
- L218 _macro_ `#define RADAUDIO_BLOCKFLAG_NONZERO_BITARRAY_MODE_SET(x) ((x) << 8)`
- L222 _macro_ `#define RADAUDIO_STREAMHEADER_FLAGS ( \` — use invalid flag combination as first byte of stream header, allows us to detect looping automatically mono block, but stereo predict, also incorrect parity
- L227 _function_ `static int countbits8(U32 flags)`
- L234 _function_ `static int put_8bits_or_16bits(U8 buffer[9], int offset, U16 value)`
- L244 _member_ `U16 flags, bytes, runlen, vbstream0;` (scope `__anon9b4f70210208`)
- L244 _member_ `U16 flags, bytes, runlen, vbstream0;` (scope `__anon9b4f70210208`)
- L244 _member_ `U16 flags, bytes, runlen, vbstream0;` (scope `__anon9b4f70210208`)
- L244 _member_ `U16 flags, bytes, runlen, vbstream0;` (scope `__anon9b4f70210208`)
- L245 _typedef_ `} block_header_info;`
- L249 _enumerator_ `COMMON_INCOMPLETE_DATA = -2` (scope `__anon9b4f70210303`)
- L250 _enumerator_ `COMMON_INVALID_DATA = -3` (scope `__anon9b4f70210303`)
- L251 _enumerator_ `COMMON_STREAM_HEADER = -4` (scope `__anon9b4f70210303`)
- L254 _function_ `static int radaudio_encode_block_header(U8 buffer[10], const radaudio_block_header_biases *bc, const radaudio_block_header_unpacked *bh)`
- L331 _function_ `static int radaudio_decode_block_header(const U8 buffer[10], const radaudio_block_header_biases *bc, radaudio_block_header_unpacked *bh, size_t memavail)` — returns length of header in bytes returns RADAUDIO_INCOMPLETE_DATA if there's not enough data to decode the header returns RADAUDIO_INVALID_DATA if the header fails some simple validity tests
- L428 _member_ `char magic[8];` (scope `__anon9b4f70210408`)
- L429 _member_ `U32 version;` (scope `__anon9b4f70210408`)
- L430 _member_ `U16 sample_rate;` (scope `__anon9b4f70210408`)
- L431 _member_ `U16 bytes_bias;` (scope `__anon9b4f70210408`)
- L434 _member_ `U8 num_channels;` (scope `__anon9b4f70210408`) — must be 1 or 2
- L435 _member_ `U8 nzmode_data1[NUM_NZ_MODE/2];` (scope `__anon9b4f70210408`) — 4 modes, 1 nibble each, packed number of 8-byte chunks for 4 modes
- L436 _member_ `U8 nzmode_data2[NUM_SELECTOR_MODES*1];` (scope `__anon9b4f70210408`) — 5 modes, 1 byte each, coding 4 2-bit huffman selectors
- L437 _member_ `U8 nzmode_data3[(NUM_NZ_MODE-1)*(MAX_NZ_BLOCKS/2)];` (scope `__anon9b4f70210408`) — 3 modes, 12 nibbles each, coding 12 4-bit huffman selectors + inversion bit
- L440 _member_ `U8 subband_predicted_sum[MAX_BANDS];` (scope `__anon9b4f70210408`)
- L441 _member_ `S8 mantissa_param[2][MAX_BANDS/4][2];` (scope `__anon9b4f70210408`)
- L444 _member_ `U8 padding[128-16-26-48];` (scope `__anon9b4f70210408`)
- L445 _typedef_ `} radaudio_stream_header;`
- L449 _variable_ `static const char RADAUDIO_MAGIC[8] = { RADAUDIO_STREAMHEADER_FLAGS, 'R', 'a', 'd', 'A', 'u', 'd', '\032',`
- L459 _macro_ `#define NZ_MODE_INVERT (1<<3)` — bitflag in packed and unpacked stream header signalling to if an 8-byte block should be xor-with-255 we don't process it here, we let client process it
- L461 _function_ `static size_t radaudio_pack_stream_header(U8 *raw_header, radaudio_stream_header_unpacked *h)`
- L516 _function_ `static rrbool radaudio_check_stream_header(U8 *raw_header, size_t raw_header_bytes_valid)`
- L524 _function_ `static size_t radaudio_unpack_stream_header(U8 *raw_header, size_t raw_header_bytes_valid, radaudio_stream_header_unpacked *h)`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_data_tables.inl` (Other)


#### Free symbols / members of external scopes

- L2 _variable_ `static radaudio_rate_info radaudio_rateinfo[2][4] = { { { 48000, 20,800, 1024, 54, 42, 12, { 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 32, 32, 48, 48, 48, 144, 160, 160, 0, 0, 0, 0, }, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3, 9, 10, 10, 0, 0, 0, 0, }, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 19, 22, 25, 34, 44, 0, 0, 0, 0, }, { 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 240, 288, 336, 480, 640, 0, 0, 0, 0, }, { 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, { 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 256, 272, 288, 304, 320, 336, 352, 368, 384, 400, 416, 432, 448, 464, 480, 496, 512, 528, 544, 560, 576, 592, 608, 624, 640, 656, 672, 688, 704, 720, 736, 752, 768, 784, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, { 0.353553384542f, 0.353553384542f, 0.353553384542f, 0.353553384542f, 0.353553384542f, 0.353553384542f, 0.353553384542f, 0.353553384542f, 0.250000000000f, 0.250000000000f, 0.250000000000f, 0.250000000000f, 0.176776692271f, 0.176776692271f, 0.144337564707f, 0.144337564707f, 0.144337564707f, 0.083333335817f, 0.079056940973f, 0.079056940973f, 0.000000000000f, 0.000000000000f, 0.000000000000f, 0.000000000000f, }, { 0.000030517576f, 0.000030517576f, 0.000030517576f ...`
- L90 _variable_ `static float window_long[1024] = { 0.000000924059f, 0.000008316517f, 0.000023101364f, 0.000045278459f, 0.000074847594f, 0.000111808491f, 0.000156160808f, 0.000207904115f, 0.000267037918f, 0.000333561708f, 0.000407474785f, 0.000488776539f, 0.000577466097f, 0.000673542731f, 0.000777005451f, 0.000887853326f, 0.001006085309f, 0.001131700235f, 0.001264696941f, 0.001405074261f, 0.001552830683f, 0.001707964926f, 0.001870475593f, 0.002040361054f, 0.002217619680f, 0.002402249724f, 0.002594249556f, 0.002793617314f, 0.003000351135f, 0.003214448923f, 0.003435908817f, 0.003664728720f, 0.003900906071f, 0.004144439008f, 0.004395325202f, 0.004653562326f, 0.004919147119f, 0.005192078184f, 0.005472352263f, 0.005759966560f, 0.006054918282f, 0.006357205100f, 0.006666823756f, 0.006983771455f, 0.007308044937f, 0.007639640942f, 0.007978556678f, 0.008324787952f, 0.008678332902f, 0.009039186873f, 0.009407347068f, 0.009782808833f, 0.010165570304f, 0.010555625893f, 0.010952972807f, 0.011357606389f, 0.011769523844f, 0.012188719586f, 0.012615191750f, 0.013048933819f, 0.013489942066f, 0.013938212767f, 0.014393741265f, 0.014856522903f, 0.015326553956f, 0.015803826973f, 0.016288341954f, 0.016780089587f, 0.017279066145f, 0.017785267904f, 0.018298687413f, 0.018819322810f, 0.019347166643f, 0.019882213324f, 0.020424459130f, 0.020973896608f, 0.021530522034f, 0.022094327956f, 0.022665310651f, 0.023243462667f, 0.023828778416f, 0.024421252310f, 0.025020876899f, 0.025627648458f, 0.026241557673f, 0.026862600818f, 0.0 ...`
- L221 _variable_ `static float window_short[128] = { 0.000059139038f, 0.000532197882f, 0.001478030114f, 0.002896063495f, 0.004785436206f, 0.007144992705f, 0.009973277338f, 0.013268529437f, 0.017028674483f, 0.021251311526f, 0.025933710858f, 0.031072795391f, 0.036665130407f, 0.042706914246f, 0.049193959683f, 0.056121692061f, 0.063485108316f, 0.071278803051f, 0.079496912658f, 0.088133141398f, 0.097180701792f, 0.106632351875f, 0.116480343044f, 0.126716434956f, 0.137331858277f, 0.148317337036f, 0.159663051367f, 0.171358674765f, 0.183393299580f, 0.195755511522f, 0.208433344960f, 0.221414253116f, 0.234685227275f, 0.248232662678f, 0.262042462826f, 0.276100039482f, 0.290390282869f, 0.304897606373f, 0.319605946541f, 0.334498882294f, 0.349559515715f, 0.364770591259f, 0.380114465952f, 0.395573228598f, 0.411128699780f, 0.426762402058f, 0.442455708981f, 0.458189755678f, 0.473945677280f, 0.489704459906f, 0.505447089672f, 0.521154582500f, 0.536808073521f, 0.552388727665f, 0.567878007889f, 0.583257555962f, 0.598509252071f, 0.613615453243f, 0.628558754921f, 0.643322288990f, 0.657889604568f, 0.672244906425f, 0.686372935772f, 0.700258910656f, 0.713888943195f, 0.727249741554f, 0.740328788757f, 0.753114342690f, 0.765595495701f, 0.777762115002f, 0.789605021477f, 0.801115870476f, 0.812287271023f, 0.823112726212f, 0.833586633205f, 0.843704402447f, 0.853462278843f, 0.862857580185f, 0.871888458729f, 0.880554080009f, 0.888854384422f, 0.896790385246f, 0.904363751411f, 0.911577284336f, 0.918434441090f, 0.924939453602f, 0.9 ...`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_decoder.h` (Other)


#### struct `(anonymous)`  
``  
_L11-17_

#### Free symbols / members of external scopes

- L3 _macro_ `#define INCLUDE_RADAUDIO_DECODER_H`
- L8 _typedef_ `typedef struct RadAudioDecoder RadAudioDecoder;`
- L12 _member_ `U16 sequential_version;` (scope `__anonc498fbb30108`)
- L13 _member_ `U8 minor_version;` (scope `__anonc498fbb30108`)
- L14 _member_ `U8 major_version;` (scope `__anonc498fbb30108`)
- L15 _member_ `int sample_rate;` (scope `__anonc498fbb30108`)
- L16 _member_ `int num_channels;` (scope `__anonc498fbb30108`)
- L17 _typedef_ `} RadAudioInfo;`
- L19 _macro_ `#define RADAUDIO_DECODER_AT_EOF -1`
- L20 _macro_ `#define RADAUDIO_DECODER_INCOMPLETE_DATA -2`
- L21 _macro_ `#define RADAUDIO_DECODER_INVALID_DATA -3`
- L22 _macro_ `#define RADAUDIO_DECODER_START_OF_STREAM -4`
- L23 _macro_ `#define RADAUDIO_DECODER_INTERNAL_ERROR -5`
- L24 _macro_ `#define RADAUDIO_DECODER_MAX_OUTPUT_SAMPLES_PER_CHANNEL_PER_CHUNK 1024`
- L30 _macro_ `#define RADAUDIO_DECODER_LIBRARY_VERSION 1` — RADAUDIO compatibility version - if these are the same the exports are named the same so we expect that if the linker selects a different copy they all work.
- L32 _macro_ `#define RADAUDIO_DECODER_HAS_INTERLEAVING`
- L36 _macro_ `#define RADAUDIO_STREAM_HEADER_SIZE 128` — The max size of a stream header. It could be smaller but this is a safe size for buffers.
- L39 _macro_ `#define RR_STRING_JOIN3(arg1, arg2, arg3) RR_STRING_JOIN_DELAY3(arg1, arg2, arg3)`
- L40 _macro_ `#define RR_STRING_JOIN_DELAY3(arg1, arg2, arg3) RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3)`
- L41 _macro_ `#define RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3) arg1 ## arg2 ## arg3`
- L45 _macro_ `#define RADAUDIO_DECODER_NAME(name) RR_STRING_JOIN3(RADAUDIO_WRAP, name##_, RADAUDIO_DECODER_LIBRARY_VERSION )`
- L50 _macro_ `#define RadAudioDecoderMemoryRequired RADAUDIO_DECODER_NAME(RadAudioDecoderMemoryRequired)`
- L51 _macro_ `#define RadAudioDecoderOpen RADAUDIO_DECODER_NAME(RadAudioDecoderOpen)`
- L52 _macro_ `#define RadAudioDecoderGetInfo RADAUDIO_DECODER_NAME(RadAudioDecoderGetInfo)`
- L53 _macro_ `#define RadAudioDecoderGetInfoHeader RADAUDIO_DECODER_NAME(RadAudioDecoderGetInfoHeader)`
- L54 _macro_ `#define RadAudioDecoderDecodeChunk RADAUDIO_DECODER_NAME(RadAudioDecoderDecodeChunk)`
- L55 _macro_ `#define RadAudioDecoderGetProfileData RADAUDIO_DECODER_NAME(RadAudioDecoderGetProfileData)`
- L56 _macro_ `#define RadAudioDecoderDidSeek RADAUDIO_DECODER_NAME(RadAudioDecoderDidSeek)`
- L57 _macro_ `#define RadAudioDecoderGetChunkLength RADAUDIO_DECODER_NAME(RadAudioDecoderGetChunkLength)`
- L59 _macro_ `#define RadAudioInterleave RADAUDIO_DECODER_NAME(RadAudioInterleave)`
- L60 _macro_ `#define RadAudio1ChToS16 RADAUDIO_DECODER_NAME(RadAudio1ChToS16)`
- L61 _macro_ `#define RadAudioInterleave2ChToS16 RADAUDIO_DECODER_NAME(RadAudioInterleave2ChToS16)`
- L62 _macro_ `#define RadAudioInterleave4ChToS16 RADAUDIO_DECODER_NAME(RadAudioInterleave4ChToS16)`
- L70 _prototype_ `RADDEFFUNC size_t RadAudioDecoderMemoryRequired(U8* stream_header, size_t stream_header_bytes_valid);` — RadAudioDecoderMemoryRequired() returns the amount of memory that needs to be passed to Open(). stereo requires more than mono. Returns 0 if the header is invalid. Pass in NULL to get the maximum size required for any stream.
- L85 _prototype_ `RADDEFFUNC RadAudioDecoder* RadAudioDecoderOpen(U8 *stream_header, size_t stream_header_bytes_valid, void *mem, size_t memsize, size_t *out_header_size);` — RadAudioDecoderOpen() returns a pointer to a decoder structure that is allocated in 'mem'. you don't need to close it, just dispose of the memory yourself when done returns NULL if header is invalid or if memsize is smaller than RadAudioDecoderMemoryRequired() or if stream_header_bytes_valid is too small (needs to be RADAUDIO_STREAM_HEADER_SIZE bytes) if the header is large enough to be read, the size of the header will be written to *header_size there is no RadAudioDecoderClose() function as the structure holds no resources; just free the memory you passed in as necessary
- L94 _prototype_ `RADDEFFUNC void RadAudioDecoderGetInfo(const RadAudioDecoder *radaudio_decoder, RadAudioInfo *out_info);` — RadAudioDecoderGetInfo* return info about the decoder either from an unopened stream header or an open decoder.
- L97 _prototype_ `RADDEFFUNC size_t RadAudioDecoderGetInfoHeader(U8* stream_header, size_t stream_header_bytes_valid, RadAudioInfo *out_info);` — returns size of the header on success, false if not a valid stream header
- L125 _prototype_ `RADDEFFUNC int RadAudioDecoderDecodeChunk(RadAudioDecoder *radaudio_decoder, const U8 *data, size_t data_avail, size_t *data_consumed, F32 *(output_samples[2]), size_t max_samples);` — RadAudioDecoderChunk() - `radaudio_decoder`: a pointer to a decoder created with `RadAudioDecoderOpen()` - `data`            : pointer to the next chunk of compressed data to decode - `data_avail`      : the length of the data pointed to by `data` - `data_consumed`   : output value, the amount of data consumed decoding this chunk - `output_samples`  : a pointer to an array of pointers where to write the output, one pointer per channel - `max_samples`     : the maximum number of samples that can be written to each of the `output_samples` pointers For the first call, `data` should either point to the full stream (that is, it points to the stream header), or it can point to the first block output by radaudio_encode_block (e.g. if you store the stream header separately from the sequence of blocks in the stream). returns the number of samples output per channel, and sets `data_consumed` to the number of bytes of input data consumed... you should advance `data` by this much. data_consumed can be 0 if there wasn't enough data. Note that 0 is a valid "number of samples" decoded, it means it decoded a block but there were no samples fully decoded due to the way the codec works. (This should only happen at the start of the stream and after seeks.) returns RADAUDIO_DECODER_AT_EOF if at the "end of stream", i.e. there's no more data in the audio stream returns RADAUDIO_DECODER_INCOMPLETE_DATA if there's not enough data to decode a block returns RADAUDIO_DECODER_INVALID_DATA if the block 
- L134 _prototype_ `RADDEFFUNC int RadAudioDecoderGetChunkLength(RadAudioDecoder *radaudio_decoder, const U8 *data, size_t data_avail);` — Returns the length of the next block, given the block header (needs as much as 6 bytes). returns RADAUDIO_DECODER_AT_START_OF_STREAM if you pass in the stream header instead of the block header returns RADAUDIO_DECODER_AT_EOF if at the "end of stream", i.e. there's no more data expected in the audio stream (regardless of the block you pass in) returns RADAUDIO_DECODER_INCOMPLETE_DATA if there's not enough data to decode the block header returns RADAUDIO_DECODER_INVALID_DATA if the block header is invalid
- L138 _prototype_ `RADDEFFUNC void RadAudioDecoderDidSeek(RadAudioDecoder *radaudio_decoder);` — inform the decoder that you performed a seek operation on the input stream, such that the next decoder call is not continuous with the previous one.
- L143 _prototype_ `RADDEFFUNC void RadAudioInterleave( S16 * output, float const ** inputs, U32 input_count, U32 samples );` — utility function to interleave N buffers of float data into one output buffer of S16 (scales and clamps from -1.0 to 1 into -32768 to 32767)
- L147 _prototype_ `RADDEFFUNC int RadAudio1ChToS16( S16 * output, float const * input, U32 samples );` — low level direct routines, if these return 0, then they converted NOTHING (the sample count is too small for even one SIMD round). if they return 1, then the ENTIRE buffer was converted.
- L148 _prototype_ `RADDEFFUNC int RadAudioInterleave2ChToS16( S16 * output, float const * input_left, float const * input_right, U32 samples );`
- L149 _prototype_ `RADDEFFUNC int RadAudioInterleave4ChToS16( S16 * output, float const * input_left, float const * input_right, float const * input_back_left, float const * input_back_right, U32 samples );`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_decoder_avx2.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_AVX2_DECODE_H`
- L13 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L15 _macro_ `#define radaudio_avx2_save_samples WRAPPED_NAME(radaudio_avx2_save_samples)`
- L16 _macro_ `#define radaudio_avx2_compute_windowed_sum_multiple16 WRAPPED_NAME(radaudio_avx2_compute_windowed_sum_multiple16)`
- L20 _prototype_ `extern float radaudio_avx2_save_samples(S16 *buffer, const float *data, int num);`
- L21 _prototype_ `extern void radaudio_avx2_compute_windowed_sum_multiple16(float *output, int n, const float *fwd_data, const S16 *rev_data, float rev_scale, const float *window);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_decoder_internal.h` (Other)


#### struct `(anonymous)`  
``  
_L10-13_

#### Free symbols / members of external scopes

- L3 _macro_ `#define INCLUDE_RADAUDIO_DECODER_INTERNAL_H`
- L11 _member_ `const char *name;` (scope `__anonb600b5cf0108`)
- L12 _member_ `double time;` (scope `__anonb600b5cf0108`)
- L13 _typedef_ `} radaudio_profile_value;`
- L17 _prototype_ `extern int RadAudioDecoderGetProfileData(RadAudioDecoder *hradaud, radaudio_profile_value *profile, int num_profile);` — also call GetProfileData to enable profiling, profile=NULL, num_prof=1 is normal profiling, num_prof=2 is full profile
- L20 _prototype_ `extern void RadAudioDecoderForceIntelCPU (RadAudioDecoder *hradaud, rrbool has_sse2, rrbool has_ssse3, rrbool has_sse4_1, rrbool has_popcnt, rrbool has_avx2);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_decoder_neon.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_NEON_DECODE_H`
- L12 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L14 _macro_ `#define radaudio_neon_expand_coefficients_excess_read15 WRAPPED_NAME(radaudio_neon_expand_coefficients_excess_read15)`
- L15 _macro_ `#define radaudio_neon_compute_band_energy_multiple4 WRAPPED_NAME(radaudio_neon_compute_band_energy_multiple4)`
- L16 _macro_ `#define radaudio_neon_compute_subband_energy_skip12_excess_read7 WRAPPED_NAME(radaudio_neon_compute_subband_energy_skip12_excess_read7)`
- L17 _macro_ `#define radaudio_neon_compute_windowed_sum_multiple8 WRAPPED_NAME(radaudio_neon_compute_windowed_sum_multiple8)`
- L18 _macro_ `#define radaudio_neon_unpack_nibbles_read_sentinel16_write_multiple32 WRAPPED_NAME(radaudio_neon_unpack_nibbles_read_sentinel16_write_multiple32)`
- L19 _macro_ `#define radaudio_neon_count_set_bits_read_multiple8_sentinel8 WRAPPED_NAME(radaudio_neon_count_set_bits_read_multiple8_sentinel8)`
- L20 _macro_ `#define radaudio_neon_save_samples WRAPPED_NAME(radaudio_neon_save_samples)`
- L21 _macro_ `#define radaudio_neon_dequantize_long_block_replace_0_with_random_8x8_Nx16 WRAPPED_NAME(radaudio_neon_dequantize_long_block_replace_0_with_random_8x8_Nx16)`
- L22 _macro_ `#define radaudio_neon_dequantize_short_block WRAPPED_NAME(radaudio_neon_dequantize_short_block)`
- L23 _macro_ `#define radaudio_neon_distribute_bitflag_coefficients_multiple16 WRAPPED_NAME(radaudio_neon_distribute_bitflag_coefficients_multiple16)`
- L24 _macro_ `#define radaudio_neon_count_bytes_below_value_sentinel16 WRAPPED_NAME(radaudio_neon_count_bytes_below_value_sentinel16)`
- L27 _prototype_ `extern rrbool radaudio_neon_expand_coefficients_excess_read15(S8 *nonzero_coefficients, int num_nonzero, S8 *big_coeff, S8 *big_limit);`
- L28 _prototype_ `extern void radaudio_neon_compute_band_energy_multiple4(F32 *band_energy, int num_bands, int band_exponent[], U16 fine_energy[], F32 band_scale_decode[]);`
- L29 _prototype_ `extern void radaudio_neon_compute_subband_energy_skip12_excess_read7(F32 *subband_energy, const F32 *band_energy, int num_bands, int *num_subbands_for_band, U16 *quantized_subbands);`
- L30 _prototype_ `extern void radaudio_neon_compute_windowed_sum_multiple8(float *output, int n, const float *fwd_data, const S16 *rev_data, float rev_scale, const float *window);`
- L31 _prototype_ `extern void radaudio_neon_unpack_nibbles_read_sentinel16_write_multiple32(S8 *unpacked, U8 *packed, int num_packed, U64 default_nibbles);`
- L32 _prototype_ `extern int radaudio_neon_count_set_bits_read_multiple8_sentinel8(U8 *data, int num_bytes);`
- L33 _prototype_ `extern float radaudio_neon_save_samples(S16 *buffer, const float *data, int num);`
- L34 _prototype_ `extern void radaudio_neon_dequantize_long_block_replace_0_with_random_8x8_Nx16(F32 *coeffs, S8 *quantized_coeff, F32 *subband_energy, int num_subbands, U32 rand_state[4]);`
- L35 _prototype_ `extern void radaudio_neon_dequantize_short_block(float *coeffs, S8 *quantized_coeff, float *band_energy, int num_bands, int *num_coeffs_for_band);`
- L36 _prototype_ `extern void radaudio_neon_distribute_bitflag_coefficients_multiple16(S8 *quantized_coeff, int num_coeff, U8 *nonzero_flagbits, S8 *nonzero_coeffs, int *pcur_nonzero_coeffs);`
- L37 _prototype_ `extern int radaudio_neon_count_bytes_below_value_sentinel16(U8 *data, int num_bytes, U8 threshold);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_decoder_simd_tables.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_DECODER_SIMD_TABLES_H`
- L39 _variable_ `static const U8 s_popcnt_table[256] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, };`
- L58 _variable_ `static const S8 s_shuffle_table[256][8] = { { -1,-1,-1,-1,-1,-1,-1,-1, },{ 0,-1,-1,-1,-1,-1,-1,-1, },{ -1, 0,-1,-1,-1,-1,-1,-1, },{ 0, 1,-1,-1,-1,-1,-1,-1, }, { -1,-1, 0,-1,-1,-1,-1,-1, },{ 0,-1, 1,-1,-1,-1,-1,-1, },{ -1, 0, 1,-1,-1,-1,-1,-1, },{ 0, 1, 2,-1,-1,-1,-1,-1, }, { -1,-1,-1, 0,-1,-1,-1,-1, },{ 0,-1,-1, 1,-1,-1,-1,-1, },{ -1, 0,-1, 1,-1,-1,-1,-1, },{ 0, 1,-1, 2,-1,-1,-1,-1, }, { -1,-1, 0, 1,-1,-1,-1,-1, },{ 0,-1, 1, 2,-1,-1,-1,-1, },{ -1, 0, 1, 2,-1,-1,-1,-1, },{ 0, 1, 2, 3,-1,-1,-1,-1, }, { -1,-1,-1,-1, 0,-1,-1,-1, },{ 0,-1,-1,-1, 1,-1,-1,-1, },{ -1, 0,-1,-1, 1,-1,-1,-1, },{ 0, 1,-1,-1, 2,-1,-1,-1, }, { -1,-1, 0,-1, 1,-1,-1,-1, },{ 0,-1, 1,-1, 2,-1,-1,-1, },{ -1, 0, 1,-1, 2,-1,-1,-1, },{ 0, 1, 2,-1, 3,-1,-1,-1, }, { -1,-1,-1, 0, 1,-1,-1,-1, },{ 0,-1,-1, 1, 2,-1,-1,-1, },{ -1, 0,-1, 1, 2,-1,-1,-1, },{ 0, 1,-1, 2, 3,-1,-1,-1, }, { -1,-1, 0, 1, 2,-1,-1,-1, },{ 0,-1, 1, 2, 3,-1,-1,-1, },{ -1, 0, 1, 2, 3,-1,-1,-1, },{ 0, 1, 2, 3, 4,-1,-1,-1, }, { -1,-1,-1,-1,-1, 0,-1,-1, },{ 0,-1,-1,-1,-1, 1,-1,-1, },{ -1, 0,-1,-1,-1, 1,-1,-1, },{ 0, 1,-1,-1,-1, 2,-1,-1, }, { -1,-1, 0,-1,-1, 1,-1,-1, },{ 0,-1, 1,-1,-1, 2,-1,-1, },{ -1, 0, 1,-1,-1, 2,-1,-1, },{ 0, 1, 2,-1,-1, 3,-1,-1, }, { -1,-1,-1, 0,-1, 1,-1,-1, },{ 0,-1,-1, 1,-1, 2,-1,-1, },{ -1, 0,-1, 1,-1, 2,-1,-1, },{ 0, 1,-1, 2,-1, 3,-1,-1, }, { -1,-1, 0, 1,-1, 2,-1,-1, },{ 0,-1, 1, 2,-1, 3,-1,-1, },{ -1, 0, 1, 2,-1, 3,-1,-1, },{ 0, 1, 2, 3,-1, 4,-1,-1, }, { -1,-1,-1,-1, 0, 1,-1,-1, },{ 0,-1,-1,-1, 1, 2,-1,-1, },{ -1, 0,-1,-1, 1, 2 ...`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_decoder_sse2.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_SSE4_DECODE_H`
- L13 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L15 _macro_ `#define radaudio_sse2_compute_windowed_sum_multiple8 WRAPPED_NAME(radaudio_sse2_compute_windowed_sum_multiple8)`
- L16 _macro_ `#define radaudio_sse2_compute_band_energy_multiple4 WRAPPED_NAME(radaudio_sse2_compute_band_energy_multiple4)`
- L17 _macro_ `#define radaudio_sse2_count_bytes_below_value_sentinel16 WRAPPED_NAME(radaudio_sse2_count_bytes_below_value_sentinel16)`
- L18 _macro_ `#define radaudio_sse2_unpack_nibbles_read_sentinel16_write_multiple32 WRAPPED_NAME(radaudio_sse2_unpack_nibbles_read_sentinel16_write_multiple32)`
- L19 _macro_ `#define radaudio_sse2_expand_coefficients_excess_read15 WRAPPED_NAME(radaudio_sse2_expand_coefficients_excess_read15)`
- L20 _macro_ `#define radaudio_sse2_save_samples WRAPPED_NAME(radaudio_sse2_save_samples)`
- L21 _macro_ `#define radaudio_sse2_find_next_coarse_run_excess16 WRAPPED_NAME(radaudio_sse2_find_next_coarse_run_excess16)`
- L24 _prototype_ `extern void radaudio_sse2_compute_windowed_sum_multiple8(float *output, int n, const float *fwd_data, const S16 *rev_data, float rev_scale, const float *window);`
- L25 _prototype_ `extern void radaudio_sse2_compute_band_energy_multiple4(F32 *band_energy, int num_bands, int band_exponent[], U16 fine_energy[], F32 band_scale_decode[]);`
- L26 _prototype_ `extern int radaudio_sse2_count_bytes_below_value_sentinel16(U8 *data, int num_bytes, U8 threshold);`
- L27 _prototype_ `extern void radaudio_sse2_unpack_nibbles_read_sentinel16_write_multiple32(S8 *unpacked, U8 *packed, int num_packed, U64 default_nibbles);`
- L28 _prototype_ `extern rrbool radaudio_sse2_expand_coefficients_excess_read15(S8 *nonzero_coefficients, int num_nonzero, S8 *big_coeff, S8 *big_limit);`
- L29 _prototype_ `extern float radaudio_sse2_save_samples(S16 *buffer, const float *data, int num);`
- L30 _prototype_ `extern U8 * radaudio_sse2_find_next_coarse_run_excess16(U8 *cur, U8 *end);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_decoder_sse4.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_SSE_DECODE_H`
- L9 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L11 _macro_ `#define radaudio_sse4_compute_subband_energy_skip12_excess_read7 WRAPPED_NAME(radaudio_sse4_compute_subband_energy_skip12_excess_read7)`
- L12 _macro_ `#define radaudio_sse4_dequantize_long_block_8x8_Nx16 WRAPPED_NAME(radaudio_sse4_dequantize_long_block_8x8_Nx16)`
- L13 _macro_ `#define radaudio_sse4_dequantize_short_block_sse4 WRAPPED_NAME(radaudio_sse4_dequantize_short_block_sse4)`
- L14 _macro_ `#define radaudio_sse4_randomize_long_block_8x8_Nx16 WRAPPED_NAME(radaudio_sse4_randomize_long_block_8x8_Nx16)`
- L15 _macro_ `#define radaudio_sse4_dequantize_long_block_replace_0_with_random_8x8_Nx16 WRAPPED_NAME(radaudio_sse4_dequantize_long_block_replace_0_with_random_8x8_Nx16)`
- L16 _macro_ `#define radaudio_ssse3_distribute_bitflag_coefficients_multiple16 WRAPPED_NAME(radaudio_ssse3_distribute_bitflag_coefficients_multiple16)`
- L17 _macro_ `#define radaudio_intel_popcnt_count_set_bits_read_multiple8_sentinel8 WRAPPED_NAME(radaudio_intel_popcnt_count_set_bits_read_multiple8_sentinel8)`
- L20 _prototype_ `extern void radaudio_sse4_compute_subband_energy_skip12_excess_read7(F32 *subband_energy, const F32 *band_energy, int num_bands, int *num_subbands_for_band, U16 *quantized_subbands);`
- L21 _prototype_ `extern void radaudio_sse4_dequantize_long_block_8x8_Nx16(float *coeffs, S8 *quantized_coeff, float *subband_energy, int num_subbands);`
- L22 _prototype_ `extern void radaudio_sse4_dequantize_short_block_sse4(float *coeffs, S8 *quantized_coeff, float *band_energy, int num_bands, int *num_coeffs_for_band);`
- L23 _prototype_ `extern void radaudio_sse4_randomize_long_block_8x8_Nx16(S8 *quantized_coeff, U32 rand_state[4], int num_subbands);`
- L24 _prototype_ `extern void radaudio_sse4_dequantize_long_block_replace_0_with_random_8x8_Nx16(F32 *coeffs, S8 *quantized_coeff, F32 *subband_energy, int num_subbands, U32 rand_state[4]);`
- L25 _prototype_ `extern void radaudio_ssse3_distribute_bitflag_coefficients_multiple16(radaudio_cpu_features cpu, S8 *quantized_coeff, int num_coeff, U8 *nonzero_flagbits, S8 *nonzero_coeffs, int *pcur_nonzero_coeffs);`
- L26 _prototype_ `extern int radaudio_intel_popcnt_count_set_bits_read_multiple8_sentinel8(U8 *data, int num_bytes);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_encoder.h` (Other)


#### struct `(anonymous)`  
``  
_L18-22_

#### enum `(anonymous)`  
``  
_L164-170_

#### struct `(anonymous)`  
``  
_L173-203_

#### Free symbols / members of external scopes

- L3 _macro_ `#define INCLUDE_RADAUDIO_ENCODER_H`
- L10 _variable_ `static const int approximate_data_rate_for_quality_setting_in_kilobits[2][10] = { { 30, 36, 39, 43, 48, 55, 65, 85,125,205 },` — for feedback to user. actual rate varies, and is sample rate dependent the 0th value is support but should never be used; it allows you to hear what the native artifacts sound like
- L20 _member_ `RAD_U64 dummy[200];` (scope `__anon8765e89d0108`) — placeholder fields to make it large enough
- L21 _member_ `U8 buffer[5000];` (scope `__anon8765e89d0108`)
- L22 _typedef_ `} radaudio_encoder;`
- L24 _macro_ `#define RADAUDIOENC_AT_EOF 0`
- L25 _macro_ `#define RADAUDIOENC_INSUFFICIENT_BUFFER -1`
- L26 _macro_ `#define RADAUDIOENC_INTERNAL_ERROR -2`
- L27 _macro_ `#define RADAUDIOENC_MAX_OUTPUT_SAMPLES_PER_CHANNEL_PER_CHUNK 1024`
- L33 _macro_ `#define RADAUDIO_ENC_LIBRARY_VERSION 1` — RADAUDIO compatibility version - if these are the same the exports are named the same so we expect that if the linker selects a different copy they all work.
- L36 _macro_ `#define RR_STRING_JOIN3(arg1, arg2, arg3) RR_STRING_JOIN_DELAY3(arg1, arg2, arg3)`
- L37 _macro_ `#define RR_STRING_JOIN_DELAY3(arg1, arg2, arg3) RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3)`
- L38 _macro_ `#define RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3) arg1 ## arg2 ## arg3`
- L42 _macro_ `#define RADAUDIO_ENC_NAME(name) RR_STRING_JOIN3(RADAUDIO_WRAP, name##_, RADAUDIO_ENC_LIBRARY_VERSION )`
- L47 _macro_ `#define radaudio_encode_create RADAUDIO_ENC_NAME(radaudio_encode_create)`
- L48 _macro_ `#define radaudio_encode_block RADAUDIO_ENC_NAME(radaudio_encode_block)`
- L49 _macro_ `#define radaudio_encode_create_internal RADAUDIO_ENC_NAME(radaudio_encode_create_internal)`
- L50 _macro_ `#define RadAudioCompressGetProfileData RADAUDIO_ENC_NAME(RadAudioCompressGetProfileData)`
- L51 _macro_ `#define radaudio_determine_preferred_next_block_length RADAUDIO_ENC_NAME(radaudio_determine_preferred_next_block_length)`
- L52 _macro_ `#define radaudio_determine_preferred_first_block_length RADAUDIO_ENC_NAME(radaudio_determine_preferred_first_block_length)`
- L53 _macro_ `#define radaudio_encode_block_ext RADAUDIO_ENC_NAME(radaudio_encode_block_ext)`
- L81 _macro_ `#define RADAUDIO_STREAM_HEADER_MAX 128` — radaudio_encode_create() Creates a new RADaudio encoder. Pass in an uninitialized radaudio_encoder structure, space to output the stream header, and then a description of the stream and the quality settings desired. - `num_channels` must be 1 or 2 - `sample_rate` must be 48000, 44100, 32000, or 24000 - if the automated quality measurement is to be trusted, then 32K and 24K encodings are lower quality at same size than converting the files to 44.1K or 48K (but ogg vorbis shows same behavior, so maybe automatic quality measurement is wrong for 32K and 24K) - `quality` should be 1..9. - larger values are higher quality and larger files - 5 is recommended setting; it gives comparable results to vorbis 96 kbps - going above 5 gives larger, higher quality files; could default to 6 if paranoid - settings below 5 have not been tuned, as they are not expected to be "transparent" quality - they are only provided for people who want to experiment and explore what it sounds like - `header` is a buffer to store the header - supply RADAUDIO_STREAM_HEADER_MAX - the actual size of the header is returned returns size of header on success, otherwise returns 0 there is no destroy() function as the structure holds no other resources just free the memory you passed in as necessary
- L82 _prototype_ `RADDEFFUNC size_t radaudio_encode_create( radaudio_encoder *rae, U8 header[RADAUDIO_STREAM_HEADER_MAX], int num_channels, int sample_rate, int quality, U32 flags);`
- L89 _macro_ `#define RADAUDIO_ENC_FLAG_improve_seamless_loop 1 // actually boosts precision of short block low-frequency coefficients`
- L116 _prototype_ `RADDEFFUNC int radaudio_encode_block(radaudio_encoder *es, float *input, size_t input_len,` — radaudio_encode_block() Generate a block of audio data in RADaudio format. Pass in a radaudio_encoder initialized by radaudio_encode_init. - `encode_buffer`     :  storage where the encoder will write compressed data - `encode_buffer_max` :  size of encode buffer - `input`             :  an array of audio samples - values from [-1..1] (can exceed this range, but will distort if you go too far) - for stereo input, interleave the channels in a single array - `input_len`         :  the number of mono samples or stereo sample pairs in the input - `offset`            :  the current encoding offset within the input buffer (in mono samples or stereo pairs) - initialize to 0 for the first call - the encoder will encode samples in the range up to [offset-1024, offset+1024) - the encoder will potentially look at samples up to [offset-1024, offset+2047) - the encoder will update `*offset` to reflect the number of samples partially encoded - samples up to `*offset` are only fully encoded after the NEXT encoder step returns: n > 0                   number of bytes of data output for this block RADAUDIOENC_AT_EOF                at end of stream, previously generated block is last block RADAUDIOENC_INSUFFICIENT_BUFFER   if output buffer isn't large enough RADAUDIOENC_INTERNAL_ERROR        an internal error occurred. this is probably a bug
- L146 _macro_ `#define MAX_ENCODED_BLOCK_SIZE 5000 // 5000 plus slop due to forgetting to count stuff`
- L165 _enumerator_ `RADAUDIO_BLOCKTYPE_short = 1` (scope `__anon8765e89d0203`)
- L166 _enumerator_ `RADAUDIO_BLOCKTYPE_long = 2` (scope `__anon8765e89d0203`)
- L169 _enumerator_ `RADAUDIO_BLOCKTYPE_default = 0` (scope `__anon8765e89d0203`) — radaudio_encode_block_ext only
- L170 _typedef_ `} radaudio_blocktype;`
- L174 _member_ `radaudio_blocktype force_first_blocktype;` (scope `__anon8765e89d0308`) — only used on first call
- L175 _member_ `radaudio_blocktype force_next_blocktype;` (scope `__anon8765e89d0308`) — used on all calls
- L179 _member_ `F32 *padding;` (scope `__anon8765e89d0308`) — you can achieve seamless looping using the following fields: use this as the data to pad the beginning and/or end of the stream with, instead of 0s
- L180 _member_ `size_t padding_len;` (scope `__anon8765e89d0308`) — in samples (stereo pairs count as one). Set to 0 to disable.
- L203 _typedef_ `} radaudio_encode_info;` — At the beginning and end of the stream, based on offset going from 0..input_len, the above data will be used to "pad" the audio stream instead of the 0 value used by default. - at the beginning of the stream, the END of the padding block will be used, pushed up against the start of the stream audio - at the end of the stream, the BEGINNING of the padding block will be used, pushed right up against the end of the stream audio for best results when looping, supply 2048 samples, or the entire stream if the stream is shorter than 2048 samples. the above logic should do the right thing if the entire stream is very small, even smaller than a block In theory the logic should be something like this (assuming the stream is > 2048 samples): if (offset < 1024) point padding at end of stream if (offset > length-2048) point padding at beginning of stream In theory the padding data should only be needed in the first block and the last two blocks, but in debugging I actually saw the data accessed in the last 3 blocks. I didn't investigate since the output was correct, but I suspect when this happened it was on short/long block transitions in which the data in the third-to-last-block was used but windowed to 0 anyway, so it wouldn't matter if it wasn't available. Also because it requires a short/long transition the above logic should cover the case anyway. But maybe I'm misunderstanding and the end logic might need to be triggered further from the end--stb
- L205 _prototype_ `RADDEFFUNC int radaudio_encode_block_ext(radaudio_encoder *es, float *input, size_t input_len,`
- L218 _prototype_ `RADDEFFUNC radaudio_blocktype radaudio_determine_preferred_first_block_length(radaudio_encoder *rae, F32 *input, size_t input_len);` — determine the preferred blocktype for the first block in the stream; pass this in as radaudio_encode_info.force_first_blocktype. you can specify a different value than this function returns by overriding radaudio_encode_info, but specifying long when short is requested will decrease quality, and specifying short when long is requested will increase rate
- L227 _prototype_ `RADDEFFUNC int radaudio_determine_preferred_next_block_length(radaudio_encoder *rae, radaudio_blocktype firsttype, F32 *input, size_t input_len, size_t offset);` — determine the preferred blocktype for the next block in the stream; this is stateful; it assumes `offset` points into the middle of the block to encode, as described for encode_block you can specify a different value than this function returns by overriding radaudio_encode_info, but specifying long when short is requested will decrease quality, and specifying short when long is requested will increase rate

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_encoder_internal.h` (Other)


#### struct `(anonymous)`  
``  
_L8-11_

#### enum `(anonymous)`  
``  
_L14-25_

#### enum `(anonymous)`  
``  
_L28-43_

#### struct `coefficient_encode_heuristics`  
`typedef struct coefficient_encode_heuristics`  
_L45-81_
- L48 _public member_ `float pulse_quality;` — base calculation for number of pulses to use
- L51 _public member_ `float short_block_pulse_scale;` — short block total pulses are reduced compared to long blocks
- L54 _public member_ `float band_exponent_base [2];` — weight coefficient pulse counts by band
- L55 _public member_ `float band_count_exponent[2];` — weight by pow(num_coeff    , band_ecount_exp)
- L56 _public member_ `float quality_weight_low [2];` — weight by lerp(band_index, quality_weight_low, 1.0)
- L59 _public member_ `float large_boost_median_test[2];` — coefficients in a subband get a boost depending on how many coefficients greatly exceed the median
- L60 _public member_ `float small_boost_median_test[2];`
- L63 _public member_ `float expectation_base;` — miscellany
- L64 _public member_ `float expectation_scale;`
- L66 _public member_ `int side_exp_threshold_all;`
- L67 _public member_ `int side_exp_start2_all;`
- L68 _public member_ `int side_exp_start2;`
- L69 _public member_ `int side_exp_threshold;`
- L70 _public member_ `int side_exp_end_all;`
- L71 _public member_ `int side_exp_start_all;`
- L72 _public member_ `int side_exp_start;`
- L73 _public member_ `int side_exp_end;`
- L74 _public member_ `int mid_side_tiny;`
- L75 _public member_ `int mid_side_offset;`
- L76 _public member_ `int mid_side_threshold;`
- L77 _public member_ `int mid_side_max_bad_bands;`
- L79 _public member_ `float short_overlap_scale1;`
- L80 _public member_ `float short_overlap_scale2;`

#### struct `(anonymous)`  
``  
_L84-122_

#### struct `(anonymous)`  
``  
_L131-134_

#### Free symbols / members of external scopes

- L3 _macro_ `#define INCLUDE_RADAUDIO_ENCODER_INTERNAL_H`
- L9 _member_ `size_t bit_allocation[8];` (scope `__anoncdbfc9f90108`)
- L10 _member_ `U32 block_events [16];` (scope `__anoncdbfc9f90108`)
- L11 _typedef_ `} encode_stats;`
- L15 _enumerator_ `S_header` (scope `__anoncdbfc9f90203`)
- L16 _enumerator_ `S_band_exponent` (scope `__anoncdbfc9f90203`)
- L17 _enumerator_ `S_band_mantissa` (scope `__anoncdbfc9f90203`)
- L18 _enumerator_ `S_subband` (scope `__anoncdbfc9f90203`)
- L19 _enumerator_ `S_coeff_location` (scope `__anoncdbfc9f90203`)
- L20 _enumerator_ `S_coeff_value` (scope `__anoncdbfc9f90203`)
- L21 _enumerator_ `S_coeff_value_large` (scope `__anoncdbfc9f90203`)
- L22 _enumerator_ `S_padding` (scope `__anoncdbfc9f90203`)
- L24 _enumerator_ `S_count` (scope `__anoncdbfc9f90203`)
- L29 _enumerator_ `E_predict_band_stereo` (scope `__anoncdbfc9f90303`)
- L30 _enumerator_ `E_predict_subband_stereo` (scope `__anoncdbfc9f90303`)
- L31 _enumerator_ `E_stereo_as_mono` (scope `__anoncdbfc9f90303`)
- L32 _enumerator_ `E_subband_nopredict` (scope `__anoncdbfc9f90303`)
- L33 _enumerator_ `E_subband_renormalize` (scope `__anoncdbfc9f90303`)
- L34 _enumerator_ `E_coefficients_renormalize` (scope `__anoncdbfc9f90303`)
- L35 _enumerator_ `E_many_big_coefficients` (scope `__anoncdbfc9f90303`)
- L36 _enumerator_ `E_toomany_big_coefficients` (scope `__anoncdbfc9f90303`)
- L37 _enumerator_ `E_nzmode0` (scope `__anoncdbfc9f90303`)
- L38 _enumerator_ `E_nzmode1` (scope `__anoncdbfc9f90303`)
- L39 _enumerator_ `E_nzmode2` (scope `__anoncdbfc9f90303`)
- L40 _enumerator_ `E_nzmode3` (scope `__anoncdbfc9f90303`)
- L42 _enumerator_ `E_count` (scope `__anoncdbfc9f90303`)
- L81 _typedef_ `} coefficient_encode_heuristics;`
- L85 _member_ `int num_channels;` (scope `__anoncdbfc9f90408`)
- L87 _member_ `rrbool current_block_short;` (scope `__anoncdbfc9f90408`)
- L88 _member_ `rrbool prev_block_short;` (scope `__anoncdbfc9f90408`)
- L89 _member_ `rrbool next_block_short;` (scope `__anoncdbfc9f90408`)
- L90 _member_ `int samprate_mode;` (scope `__anoncdbfc9f90408`) — ba2r_bitrate_code
- L92 _member_ `int band_mantissa_exp_scale, band_mantissa_band_decay;` (scope `__anoncdbfc9f90408`)
- L92 _member_ `int band_mantissa_exp_scale, band_mantissa_band_decay;` (scope `__anoncdbfc9f90408`)
- L93 _member_ `rrbool allow_mid_side;` (scope `__anoncdbfc9f90408`)
- L95 _member_ `int sample_rate;` (scope `__anoncdbfc9f90408`) — implied by bitrate_mode
- L96 _member_ `int quality_mode;` (scope `__anoncdbfc9f90408`)
- L97 _member_ `S8 subband_bias [MAX_BANDS] ;` (scope `__anoncdbfc9f90408`)
- L98 _member_ `U8 subband_predicted_sum [MAX_BANDS] ;` (scope `__anoncdbfc9f90408`)
- L99 _member_ `S8 mantissa_param [2][MAX_BANDS][2];` (scope `__anoncdbfc9f90408`)
- L100 _member_ `U8 subband_sum_adjusted [2][MAX_BANDS] ;` (scope `__anoncdbfc9f90408`)
- L101 _member_ `int subband_bias_adjusted [2][MAX_BANDS] ;` (scope `__anoncdbfc9f90408`)
- L103 _member_ `U32 block_number;` (scope `__anoncdbfc9f90408`)
- L104 _member_ `U64 samples_fully_coded;` (scope `__anoncdbfc9f90408`)
- L106 _member_ `radaudio_block_header_biases biases;` (scope `__anoncdbfc9f90408`)
- L107 _member_ `radaudio_cpu_features cpu;` (scope `__anoncdbfc9f90408`)
- L108 _member_ `radaudio_rate_info * info[2];` (scope `__anoncdbfc9f90408`) — indexed by short/long
- L110 _member_ `radaudio_nonzero_blockmode_descriptor nz_desc[4];` (scope `__anoncdbfc9f90408`)
- L111 _member_ `U8 nz_correlated_huffman_selectors[NUM_NZ_SELECTOR][NUM_SELECTOR_MODES];` (scope `__anoncdbfc9f90408`)
- L113 _member_ `coefficient_encode_heuristics heur;` (scope `__anoncdbfc9f90408`)
- L115 _member_ `U32 lastblock_block_bytes;` (scope `__anoncdbfc9f90408`)
- L116 _member_ `U32 lastblock_vbstream0_length;` (scope `__anoncdbfc9f90408`)
- L117 _member_ `U32 lastblock_num_runlength_array;` (scope `__anoncdbfc9f90408`)
- L118 _member_ `encode_stats stats;` (scope `__anoncdbfc9f90408`)
- L119 _member_ `U64 profile_times[32];` (scope `__anoncdbfc9f90408`)
- L121 _member_ `U8 buffer[5000];` (scope `__anoncdbfc9f90408`)
- L122 _typedef_ `} radaudio_encoder_state;`
- L124 _prototype_ `RADDEFFUNC size_t radaudio_encode_create_internal(radaudio_encoder *es, unsigned char header[64], int num_channels, int sample_rate, int quality, float pulse_quality_override,`
- L132 _member_ `const char *name;` (scope `__anoncdbfc9f90508`)
- L133 _member_ `double time;` (scope `__anoncdbfc9f90508`)
- L134 _typedef_ `} radaudio_eprofile_value;`
- L136 _prototype_ `RADDEFFUNC int RadAudioCompressGetProfileData(radaudio_encoder *hradaud, radaudio_eprofile_value *profile, int num_profile);`
- L138 _prototype_ `RADDEFFUNC void radaudio_hack_encoder(int *data, U8 *small, U8 *large);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_encoder_neon.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define RADAUDIO_ENCODER_NEON_H`
- L9 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L11 _macro_ `#define radaudio_neon_compute_best_quantized_coeff16_loop WRAPPED_NAME(radaudio_neon_compute_best_quantized_coeff16_loop)`
- L12 _macro_ `#define radaudio_neon_find_median_4th_of_8 WRAPPED_NAME(radaudio_neon_find_median_4th_of_8)`
- L13 _macro_ `#define radaudio_neon_find_median_8th_of_16 WRAPPED_NAME(radaudio_neon_find_median_8th_of_16)`
- L17 _prototype_ `extern void radaudio_neon_compute_best_quantized_coeff16_loop(S16 best_quantized[], F32 best_so_far, F32 ncoeff[], F32 quantizer, F32 step_quantizer, int num_quantizers);`
- L19 _prototype_ `extern int radaudio_neon_find_median_4th_of_8(S16 *data);`
- L20 _prototype_ `extern int radaudio_neon_find_median_8th_of_16(S16 *data);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_encoder_sse.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_ENCODER_SSE_H`
- L9 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L11 _macro_ `#define radaudio_sse2_compute_best_quantized_coeff16_loop WRAPPED_NAME(radaudio_sse2_compute_best_quantized_coeff16_loop)`
- L12 _macro_ `#define radaudio_sse2_compute_best_quantized_coeff8_loop WRAPPED_NAME(radaudio_sse2_compute_best_quantized_coeff8_loop)`
- L13 _macro_ `#define radaudio_sse2_fabs_coefficients WRAPPED_NAME(radaudio_sse2_fabs_coefficients)`
- L14 _macro_ `#define radaudio_sse4_find_median_4th_of_8 WRAPPED_NAME(radaudio_sse4_find_median_4th_of_8)`
- L15 _macro_ `#define radaudio_sse4_findnth_of_8_or_less WRAPPED_NAME(radaudio_sse4_findnth_of_8_or_less)`
- L16 _macro_ `#define radaudio_sse4popcnt_find_median_8th_of_16 WRAPPED_NAME(radaudio_sse4popcnt_find_median_8th_of_16)`
- L20 _prototype_ `extern void radaudio_sse2_compute_best_quantized_coeff16_loop(S16 best_quantized[], F32 best_so_far, F32 ncoeff[], F32 quantizer, F32 step_quantizer, int num_quantizers);`
- L21 _prototype_ `extern void radaudio_sse2_compute_best_quantized_coeff8_loop(S16 best_quantized[], F32 best_so_far, F32 ncoeff[], F32 quantizer, F32 step_quantizer, int num_quantizers);`
- L23 _prototype_ `extern void radaudio_sse2_fabs_coefficients(float *absval, float *data, int num_coeff);`
- L24 _prototype_ `extern int radaudio_sse4_find_median_4th_of_8(S16 *data);`
- L25 _prototype_ `extern int radaudio_sse4_findnth_of_8_or_less(S16 *data, int count, int n);`
- L26 _prototype_ `extern int radaudio_sse4popcnt_find_median_8th_of_16(S16 *data);`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_huffman_tables.inl` (Other)


#### Free symbols / members of external scopes

- L3 _variable_ `static radaudio_huffman rada_band_exponent_correct_huff = { #ifdef HUFFMAN_ENCODE { { 0, 2}, { 2, 2}, { 7, 5}, { 15, 6}, { 31, 8}, { 95, 9}, { 223,10}, { 735,10}, { 479,10}, { 991,10}, { 703,11}, {1727,11}, { 447,11}, {1471,11}, { 959,11}, {1983,11}, { 127,11}, {1151,11}, { 639,11}, {1663,11}, { 383,11}, {1407,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, ...`
- L303 _variable_ `static radaudio_huffman rada_band_exponent_stereo_correct_huff = { #ifdef HUFFMAN_ENCODE { { 0, 1}, { 1, 2}, { 7, 4}, { 31, 7}, { 63, 8}, { 127, 9}, { 383, 9}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, ...`
- L603 _variable_ `static radaudio_huffman rada_subband_value_huff = { #ifdef HUFFMAN_ENCODE { { 991,11}, {2015,11}, { 63,11}, {1087,11}, { 575,11}, {1599,11}, { 319,11}, {1343,11}, { 495,10}, { 23, 6}, { 3, 4}, { 1, 3}, { 0, 2}, { 2, 2}, { 5, 3}, { 11, 4}, { 7, 5}, { 55, 6}, { 15, 6}, { 47, 7}, { 111, 8}, { 239, 9}, {1007,10}, { 31,10}, { 543,10}, { 287,10}, { 799,10}, { 159,10}, { 671,10}, { 415,10}, { 927,10}, { 95,10}, { 607,10}, { 351,10}, { 863,10}, { 223,10}, { 735,10}, { 479,10}, { 831,11}, {1855,11}, { 191,11}, {1215,11}, { 703,11}, {1727,11}, { 447,11}, {1471,11}, { 959,11}, {1983,11}, { 127,11}, {1151,11}, { 639,11}, {1663,11}, { 383,11}, {1407,11}, { 895,11}, {1919,11}, { 255,11}, {1279,11}, { 767,11}, {1791,11}, { 511,11}, {1535,11}, {1023,11}, {2047,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, {  ...`
- L903 _variable_ `static radaudio_huffman rada_subband_value_stereo_correct_huff = { #ifdef HUFFMAN_ENCODE { { 0, 1}, { 1, 2}, { 7, 5}, { 15, 6}, { 31, 8}, { 415,10}, { 927,11}, {1951,11}, { 95,11}, {1119,11}, { 607,11}, {1631,11}, { 351,11}, {1375,11}, { 863,11}, {1887,11}, { 223,11}, {1247,11}, { 735,11}, {1759,11}, { 479,11}, {1503,11}, { 991,11}, {2015,11}, { 63,11}, {1087,11}, { 575,11}, {1599,11}, { 319,11}, {1343,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0},  ...`
- L1203 _variable_ `static radaudio_huffman rada_subband_value_last_in_band_correct_huff = { #ifdef HUFFMAN_ENCODE { { 0, 1}, { 3, 3}, { 15, 5}, { 63, 8}, { 447,11}, {1471,11}, { 959,11}, {1983,11}, { 127,11}, {1151,11}, { 639,11}, {1663,11}, { 383,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0 ...`
- L1503 _variable_ `static radaudio_huffman rada_zero_runlength_huff = { #ifdef HUFFMAN_ENCODE { { 0, 1}, { 1, 3}, { 5, 4}, { 13, 4}, { 3, 5}, { 19, 5}, { 11, 6}, { 43, 6}, { 27, 6}, { 59, 7}, { 123, 7}, { 7, 7}, { 39, 8}, { 167, 8}, { 103, 8}, { 231, 8}, { 23, 8}, { 151, 8}, { 87, 8}, { 215, 8}, { 55, 8}, { 183, 8}, { 119, 9}, { 375, 9}, { 247, 9}, { 503, 9}, { 15, 9}, { 271, 9}, { 47,10}, { 559,10}, { 303,10}, { 815,10}, { 143, 9}, { 399, 9}, { 79, 9}, { 335, 9}, { 175,10}, { 687,10}, { 431,10}, { 943,10}, { 111,10}, { 623,10}, { 367,10}, { 95,11}, {1119,11}, { 607,11}, {1631,11}, { 351,11}, { 879,10}, { 239,10}, { 751,10}, { 495,10}, {1375,11}, { 863,11}, {1887,11}, { 223,11}, {1247,11}, { 735,11}, {1759,11}, { 479,11}, {1007,10}, { 735,11}, {1759,11}, { 479,11}, { 207, 9}, { 0, 0}, { 0, 0}, { 0, 0}, { 463, 9}, { 0, 0}, { 0, 0}, { 0, 0}, { 31,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 543,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 287,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 799,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 159,10}, { 0, 0}, { 0, 0}, { 0, 0}, {1503,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 671,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 415,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 991,11}, { 0, 0}, { 0, 0}, { 0, 0}, {2015,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 927,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 63,11}, { 0, 0}, { 0, 0}, { 0, 0}, {1087,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 575,11}, { 0, 0}, { 0, 0}, { 0, 0}, {1599,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 319,11}, { 0, 0}, { 0, 0}, { 0, 0}, {1343,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 831,11}, { 0, 0}, { 0 ...`
- L1803 _variable_ `static radaudio_huffman rada_nonzero_bitflags_first64_huff = { #ifdef HUFFMAN_ENCODE { { 1, 8}, { 101, 9}, { 357, 9}, { 229, 9}, { 485, 9}, { 21, 9}, { 277, 9}, { 149, 9}, { 405, 9}, { 85, 9}, { 341, 9}, { 213, 9}, { 469, 9}, { 53, 9}, { 309, 9}, { 129, 8}, { 181, 9}, { 437, 9}, { 117, 9}, { 373, 9}, { 245, 9}, { 501, 9}, { 13, 9}, { 269, 9}, { 141, 9}, { 397, 9}, { 77, 9}, { 333, 9}, { 205, 9}, { 461, 9}, { 45, 9}, { 18, 7}, { 301, 9}, { 173, 9}, { 429, 9}, { 109, 9}, { 365, 9}, { 237, 9}, { 493, 9}, { 29, 9}, { 285, 9}, { 157, 9}, { 413, 9}, { 93, 9}, { 349, 9}, { 221, 9}, { 477, 9}, { 65, 8}, { 61, 9}, { 317, 9}, { 189, 9}, { 445, 9}, { 125, 9}, { 381, 9}, { 253, 9}, { 193, 8}, { 509, 9}, { 3, 9}, { 259, 9}, { 33, 8}, { 131, 9}, { 161, 8}, { 97, 8}, { 20, 6}, { 387, 9}, { 67, 9}, { 323, 9}, { 195, 9}, { 451, 9}, { 35, 9}, { 291, 9}, { 163, 9}, { 419, 9}, { 99, 9}, { 355, 9}, { 227, 9}, { 483, 9}, { 19, 9}, { 275, 9}, { 225, 8}, { 147, 9}, { 403, 9}, { 83, 9}, { 339, 9}, { 211, 9}, { 467, 9}, { 51, 9}, { 17, 8}, { 307, 9}, { 179, 9}, { 435, 9}, { 115, 9}, { 371, 9}, { 243, 9}, { 145, 8}, { 82, 7}, { 499, 9}, { 11, 9}, { 267, 9}, { 139, 9}, { 395, 9}, { 75, 9}, { 331, 9}, { 81, 8}, { 203, 9}, { 459, 9}, { 43, 9}, { 299, 9}, { 171, 9}, { 427, 9}, { 107, 9}, { 50, 7}, { 363, 9}, { 235, 9}, { 491, 9}, { 209, 8}, { 27, 9}, { 283, 9}, { 155, 9}, { 114, 7}, { 411, 9}, { 49, 8}, { 177, 8}, { 10, 7}, { 113, 8}, { 74, 7}, { 42, 7}, { 4, 5}, { 91, 9}, { 347, 9}, { 219, 9}, { 475, 9},  ...`
- L2103 _variable_ `static radaudio_huffman rada_nonzero_bitflags_huff0 = { #ifdef HUFFMAN_ENCODE { { 559,11}, {1583,11}, { 303,11}, {1327,11}, { 815,11}, {1839,11}, { 175,11}, {1199,11}, { 687,11}, {1711,11}, { 431,11}, {1455,11}, { 943,11}, {1967,11}, { 111,11}, { 199,10}, {1135,11}, { 623,11}, {1647,11}, { 367,11}, {1391,11}, { 879,11}, {1903,11}, { 711,10}, { 239,11}, {1263,11}, { 751,11}, { 455,10}, {1775,11}, { 967,10}, { 39,10}, { 53, 8}, { 495,11}, {1519,11}, {1007,11}, {2031,11}, { 31,11}, {1055,11}, { 543,11}, { 551,10}, {1567,11}, { 287,11}, {1311,11}, { 295,10}, { 799,11}, { 807,10}, { 167,10}, { 181, 8}, {1823,11}, { 159,11}, {1183,11}, { 679,10}, { 671,11}, { 423,10}, { 935,10}, { 117, 8}, {1695,11}, { 103,10}, { 615,10}, { 245, 8}, { 359,10}, { 13, 8}, { 71, 9}, { 17, 7}, { 415,11}, {1439,11}, { 927,11}, {1951,11}, { 95,11}, {1119,11}, { 607,11}, { 871,10}, {1631,11}, { 351,11}, {1375,11}, { 231,10}, { 863,11}, { 743,10}, { 487,10}, { 141, 8}, {1887,11}, { 223,11}, {1247,11}, { 999,10}, { 735,11}, { 23,10}, { 535,10}, { 77, 8}, {1759,11}, { 279,10}, { 791,10}, { 205, 8}, { 151,10}, { 45, 8}, { 173, 8}, { 81, 7}, { 479,11}, {1503,11}, { 991,11}, { 663,10}, {2015,11}, { 407,10}, { 919,10}, { 109, 8}, { 63,11}, { 87,10}, { 599,10}, { 237, 8}, { 343,10}, { 29, 8}, { 157, 8}, { 6, 6}, {1087,11}, { 855,10}, { 215,10}, { 93, 8}, { 727,10}, { 221, 8}, { 61, 8}, { 49, 7}, { 471,10}, { 189, 8}, { 125, 8}, { 38, 6}, { 253, 8}, { 22, 6}, { 113, 7}, { 4, 5}, { 575,11}, {1599,11}, { 319,11}, {1 ...`
- L2403 _variable_ `static radaudio_huffman rada_nonzero_bitflags_huff1 = { #ifdef HUFFMAN_ENCODE { { 0, 2}, { 42, 7}, { 106, 7}, { 54, 8}, { 2, 6}, { 182, 8}, { 118, 8}, { 101, 9}, { 34, 6}, { 246, 8}, { 14, 8}, { 357, 9}, { 142, 8}, { 229, 9}, { 485, 9}, { 21, 9}, { 26, 7}, { 78, 8}, { 206, 8}, { 277, 9}, { 46, 8}, { 149, 9}, { 405, 9}, { 85, 9}, { 174, 8}, { 341, 9}, { 213, 9}, { 469, 9}, { 53, 9}, { 309, 9}, { 181, 9}, { 437, 9}, { 90, 7}, { 110, 8}, { 238, 8}, { 117, 9}, { 30, 8}, { 373, 9}, { 245, 9}, { 501, 9}, { 158, 8}, { 13, 9}, { 269, 9}, { 141, 9}, { 397, 9}, { 77, 9}, { 333, 9}, { 205, 9}, { 94, 8}, { 461, 9}, { 45, 9}, { 301, 9}, { 173, 9}, { 429, 9}, { 109, 9}, { 365, 9}, { 237, 9}, { 493, 9}, { 29, 9}, { 285, 9}, { 157, 9}, { 413, 9}, { 93, 9}, { 222, 8}, { 18, 6}, { 62, 8}, { 190, 8}, { 349, 9}, { 126, 8}, { 221, 9}, { 477, 9}, { 61, 9}, { 254, 8}, { 317, 9}, { 189, 9}, { 445, 9}, { 125, 9}, { 381, 9}, { 253, 9}, { 509, 9}, { 1, 8}, { 3, 9}, { 259, 9}, { 131, 9}, { 387, 9}, { 67, 9}, { 323, 9}, { 195, 9}, { 451, 9}, { 35, 9}, { 291, 9}, { 163, 9}, { 419, 9}, { 99, 9}, { 355, 9}, { 129, 8}, { 65, 8}, { 227, 9}, { 483, 9}, { 19, 9}, { 275, 9}, { 147, 9}, { 403, 9}, { 83, 9}, { 339, 9}, { 211, 9}, { 467, 9}, { 51, 9}, { 307, 9}, { 179, 9}, { 435, 9}, { 193, 8}, { 115, 9}, { 371, 9}, { 243, 9}, { 499, 9}, { 11, 9}, { 267, 9}, { 139, 9}, { 33, 8}, { 395, 9}, { 75, 9}, { 331, 9}, { 161, 8}, { 203, 9}, { 97, 8}, { 225, 8}, { 58, 7}, { 50, 6}, { 17, 8}, { 145, 8}, { 459, 9}, { 81, 8}, { ...`
- L2703 _variable_ `static radaudio_huffman rada_nonzero_bitflags_huff2 = { #ifdef HUFFMAN_ENCODE { { 223,10}, { 991,11}, {2015,11}, { 63,11}, {1087,11}, { 575,11}, {1599,11}, { 61, 9}, { 319,11}, {1343,11}, { 831,11}, { 317, 9}, {1855,11}, { 189, 9}, { 445, 9}, { 125, 9}, { 191,11}, {1215,11}, { 735,10}, { 381, 9}, { 703,11}, { 253, 9}, { 509, 9}, { 3, 9}, {1727,11}, { 259, 9}, { 131, 9}, { 387, 9}, { 67, 9}, { 323, 9}, { 195, 9}, { 33, 8}, { 447,11}, {1471,11}, { 959,11}, { 451, 9}, {1983,11}, { 35, 9}, { 291, 9}, { 163, 9}, { 127,11}, { 419, 9}, { 99, 9}, { 355, 9}, { 227, 9}, { 483, 9}, { 19, 9}, { 161, 8}, {1151,11}, { 275, 9}, { 147, 9}, { 403, 9}, { 83, 9}, { 339, 9}, { 211, 9}, { 97, 8}, { 467, 9}, { 51, 9}, { 307, 9}, { 225, 8}, { 179, 9}, { 17, 8}, { 145, 8}, { 50, 7}, { 639,11}, {1663,11}, { 383,11}, { 435, 9}, {1407,11}, { 115, 9}, { 371, 9}, { 243, 9}, { 895,11}, { 499, 9}, { 11, 9}, { 267, 9}, { 139, 9}, { 395, 9}, { 75, 9}, { 81, 8}, {1919,11}, { 331, 9}, { 203, 9}, { 459, 9}, { 43, 9}, { 299, 9}, { 171, 9}, { 209, 8}, { 427, 9}, { 107, 9}, { 363, 9}, { 49, 8}, { 235, 9}, { 177, 8}, { 113, 8}, { 114, 7}, { 255,11}, { 491, 9}, { 27, 9}, { 283, 9}, { 155, 9}, { 411, 9}, { 91, 9}, { 241, 8}, { 347, 9}, { 219, 9}, { 475, 9}, { 9, 8}, { 59, 9}, { 137, 8}, { 73, 8}, { 10, 7}, { 315, 9}, { 187, 9}, { 443, 9}, { 201, 8}, { 123, 9}, { 41, 8}, { 169, 8}, { 74, 7}, { 379, 9}, { 105, 8}, { 233, 8}, { 42, 7}, { 25, 8}, { 106, 7}, { 26, 7}, { 8, 5}, {1279,11}, { 767,11}, {1791,11}, { 251, 9}, { ...`
- L3003 _variable_ `static radaudio_huffman rada_nonzero_bitflags_huff3 = { #ifdef HUFFMAN_ENCODE { { 679,11}, {1703,11}, { 423,11}, {1447,11}, { 935,11}, {1959,11}, { 103,11}, { 39,10}, {1127,11}, { 615,11}, {1639,11}, { 359,11}, {1383,11}, { 871,11}, {1895,11}, { 231,11}, {1255,11}, { 743,11}, {1767,11}, { 487,11}, {1511,11}, { 999,11}, {2023,11}, { 23,11}, {1047,11}, { 535,11}, {1559,11}, { 279,11}, {1303,11}, { 791,11}, {1815,11}, { 151,11}, {1175,11}, { 663,11}, {1687,11}, { 407,11}, {1431,11}, { 919,11}, {1943,11}, { 87,11}, {1111,11}, { 599,11}, {1623,11}, { 343,11}, {1367,11}, { 855,11}, {1879,11}, { 215,11}, {1239,11}, { 727,11}, {1751,11}, { 471,11}, {1495,11}, { 983,11}, {2007,11}, { 55,11}, {1079,11}, { 567,11}, {1591,11}, { 311,11}, {1335,11}, { 823,11}, {1847,11}, { 19, 8}, { 183,11}, {1207,11}, { 695,11}, {1719,11}, { 439,11}, {1463,11}, { 951,11}, {1975,11}, { 119,11}, {1143,11}, { 631,11}, {1655,11}, { 375,11}, {1399,11}, { 887,11}, {1911,11}, { 247,11}, {1271,11}, { 759,11}, {1783,11}, { 503,11}, {1527,11}, {1015,11}, {2039,11}, { 15,11}, {1039,11}, { 527,11}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, { 147, 8}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, { 551,10}, {1423,11}, { 911,11}, {1935,11}, { 79,11}, {1103,11}, { 591,11}, {1615,11}, { 295,10}, { 83, 8}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 207,11}, {1231,11}, { 719,11}, { 211, 8}, {1743,11}, { 463,11}, {1487,11}, { 51, 8}, { 975,11}, { 179, 8}, { 115, 8}, { 9, 5}, {1999,11}, { 47,11}, {1 ...`
- L3303 _variable_ `static radaudio_huffman rada_nonzero_bitflags_huff4 = { #ifdef HUFFMAN_ENCODE { { 983,11}, {2007,11}, { 55,11}, {1079,11}, { 567,11}, {1591,11}, { 311,11}, {1335,11}, { 823,11}, {1847,11}, { 183,11}, {1207,11}, { 695,11}, {1719,11}, { 439,11}, {1463,11}, { 951,11}, {1975,11}, { 119,11}, {1143,11}, { 631,11}, {1655,11}, { 375,11}, {1399,11}, { 887,11}, {1911,11}, { 247,11}, {1271,11}, { 759,11}, {1783,11}, { 503,11}, { 251,10}, {1527,11}, {1015,11}, {2039,11}, { 15,11}, {1039,11}, { 527,11}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 763,10}, { 399,11}, {1423,11}, { 911,11}, {1935,11}, { 79,11}, {1103,11}, { 591,11}, { 507,10}, {1615,11}, { 335,11}, {1359,11}, {1019,10}, { 847,11}, { 7,10}, { 519,10}, { 3, 8}, {1871,11}, { 207,11}, {1231,11}, { 719,11}, {1743,11}, { 463,11}, {1487,11}, { 975,11}, {1999,11}, { 47,11}, {1071,11}, { 559,11}, {1583,11}, { 303,11}, {1327,11}, { 263,10}, { 815,11}, {1839,11}, { 175,11}, {1199,11}, { 687,11}, {1711,11}, { 431,11}, { 775,10}, {1455,11}, { 943,11}, {1967,11}, { 135,10}, { 111,11}, { 647,10}, { 391,10}, { 131, 8}, {1135,11}, { 623,11}, {1647,11}, { 367,11}, {1391,11}, { 879,11}, {1903,11}, { 903,10}, { 239,11}, {1263,11}, { 751,11}, { 71,10}, {1775,11}, { 583,10}, { 327,10}, { 67, 8}, { 495,11}, {1519,11}, {1007,11}, { 839,10}, {2031,11}, { 199,10}, { 59, 9}, { 195, 8}, { 31,11}, { 711,10}, { 455,10}, { 35, 8}, { 967,10}, { 163, 8}, { 99, 8}, { 1, 5}, {1055,11}, { 543,11}, {1567, ...`
- L3603 _variable_ `static radaudio_huffman rada_nonzero_bitflags_huff5 = { #ifdef HUFFMAN_ENCODE { { 0, 2}, { 27, 9}, { 283, 9}, { 59,10}, { 155, 9}, { 571,10}, { 503,11}, {1527,11}, { 411, 9}, { 315,10}, {1015,11}, {2039,11}, { 827,10}, { 15,11}, {1039,11}, { 527,11}, { 91, 9}, { 187,10}, { 699,10}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, {1807,11}, { 443,10}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, {1423,11}, { 955,10}, { 347, 9}, { 123,10}, { 635,10}, { 911,11}, { 379,10}, {1935,11}, { 79,11}, {1103,11}, { 891,10}, { 591,11}, {1615,11}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 251,10}, { 763,10}, { 207,11}, {1231,11}, { 719,11}, {1743,11}, { 463,11}, {1487,11}, { 507,10}, { 975,11}, {1999,11}, { 47,11}, {1019,10}, {1071,11}, { 7,10}, { 519,10}, { 61, 8}, { 219, 9}, { 263,10}, { 559,11}, {1583,11}, { 775,10}, { 303,11}, {1327,11}, { 815,11}, {1839,11}, { 175,11}, {1199,11}, { 687,11}, {1711,11}, { 431,11}, {1455,11}, { 135,10}, { 647,10}, { 943,11}, {1967,11}, { 111,11}, {1135,11}, { 623,11}, {1647,11}, { 391,10}, { 367,11}, {1391,11}, { 879,11}, { 903,10}, {1903,11}, { 71,10}, { 583,10}, { 189, 8}, { 327,10}, { 239,11}, {1263,11}, { 751,11}, {1775,11}, { 495,11}, {1519,11}, { 839,10}, {1007,11}, {2031,11}, { 31,11}, { 199,10}, {1055,11}, { 711,10}, { 455,10}, { 125, 8}, { 543,11}, {1567,11}, { 287,11}, { 967,10}, {1311,11}, { 39,10}, { 551,10}, { 253, 8}, { 799,11}, { 295,10}, { 807,10}, { 3, 8}, { 167,10}, { 131, 8}, { 67, 8}, { 1, 5}, { 475, 9}, { 679,10}, {1823,11} ...`
- L3903 _variable_ `static radaudio_huffman rada_nonzero_coefficient_big_huff0 = { #ifdef HUFFMAN_ENCODE { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 3}, { 4, 3}, { 1, 4}, { 5, 5}, { 21, 5}, { 3, 6}, { 35, 6}, { 19, 6}, { 27, 7}, { 91, 7}, { 123, 8}, { 251, 8}, { 199, 9}, { 455, 9}, { 167,10}, { 935,11}, {1959,11}, { 103,11}, {1127,11}, { 615,11}, {1639,11}, { 359,11}, {1383,11}, { 871,11}, {1895,11}, { 231,11}, {1255,11}, { 743,11}, {1767,11}, { 487,11}, {1511,11}, { 999,11}, {2023,11}, { 23,11}, {1047,11}, { 535,11}, {1559,11}, { 279,11}, {1303,11}, { 791,11}, {1815,11}, { 151,11}, {1175,11}, { 663,11}, {1687,11}, { 407,11}, {1431,11}, { 919,11}, {1943,11}, { 87,11}, {1111,11}, { 599,11}, {1623,11}, { 343,11}, {1367,11}, { 855,11}, {1879,11}, { 215,11}, {1239,11}, { 727,11}, {1751,11}, { 471,11}, {1495,11}, { 983,11}, {2007,11}, { 55,11}, {1079,11}, { 567,11}, {1591,11}, { 311,11}, {1335,11}, { 823,11}, {1847,11}, { 183,11}, {1207,11}, { 695,11}, {1719,11}, { 439,11}, {1463,11}, { 951,11}, {1975,11}, { 119,11}, {1143,11}, { 631,11}, {1655,11}, { 375,11}, {1399,11}, { 887,11}, {1911,11}, { 247,11}, {1271,11}, { 759,11}, {1783,11}, { 503,11}, {1527,11}, {1015,11}, {2039,11}, { 15,11}, {1039,11}, { 527,11}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, {1423,11}, { 911,11}, {1935,11}, { 79,11}, {1103,11}, { 591,11}, {1615,11}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 207,11}, {1231,11}, { 719,11 ...`
- L4203 _variable_ `static radaudio_huffman rada_nonzero_coefficient_big_huff1 = { #ifdef HUFFMAN_ENCODE { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 3}, { 2, 4}, { 10, 4}, { 6, 4}, { 9, 5}, { 25, 5}, { 29, 6}, { 61, 6}, { 3, 6}, { 11, 7}, { 75, 7}, { 43, 7}, { 59, 8}, { 187, 8}, { 123, 8}, { 71, 9}, { 327, 9}, { 199, 9}, { 455, 9}, { 423,10}, { 935,10}, { 103,10}, { 487,11}, {1511,11}, { 999,11}, {2023,11}, { 23,11}, {1047,11}, { 535,11}, {1559,11}, { 279,11}, {1303,11}, { 791,11}, {1815,11}, { 151,11}, {1175,11}, { 663,11}, {1687,11}, { 407,11}, {1431,11}, { 919,11}, {1943,11}, { 87,11}, {1111,11}, { 599,11}, {1623,11}, { 343,11}, {1367,11}, { 855,11}, {1879,11}, { 215,11}, {1239,11}, { 727,11}, {1751,11}, { 471,11}, {1495,11}, { 983,11}, {2007,11}, { 55,11}, {1079,11}, { 567,11}, {1591,11}, { 311,11}, {1335,11}, { 823,11}, {1847,11}, { 183,11}, {1207,11}, { 695,11}, {1719,11}, { 439,11}, {1463,11}, { 951,11}, {1975,11}, { 119,11}, {1143,11}, { 631,11}, {1655,11}, { 375,11}, {1399,11}, { 887,11}, {1911,11}, { 247,11}, {1271,11}, { 759,11}, {1783,11}, { 503,11}, {1527,11}, {1015,11}, {2039,11}, { 15,11}, {1039,11}, { 527,11}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, {1423,11}, { 911,11}, {1935,11}, { 79,11}, {1103,11}, { 591,11}, {1615,11}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 207,11}, {1231,11}, { 719,11}, {1743,11}, { 463,11}, {1487,11}, { 975,11}, {1999,11}, { 47,11}, {1071,11}, {  ...`
- L4503 _variable_ `static radaudio_huffman rada_nonzero_coefficient_big_huff2 = { #ifdef HUFFMAN_ENCODE { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 4}, { 8, 4}, { 4, 4}, { 6, 5}, { 22, 5}, { 14, 5}, { 30, 5}, { 5, 6}, { 37, 6}, { 21, 6}, { 53, 6}, { 13, 6}, { 35, 7}, { 99, 7}, { 19, 7}, { 83, 7}, { 107, 8}, { 235, 8}, { 27, 8}, { 155, 8}, { 91, 8}, { 219, 8}, { 135, 9}, { 391, 9}, { 71, 9}, { 327, 9}, { 199, 9}, { 455, 9}, { 231,10}, { 743,10}, { 487,10}, { 999,10}, { 23,10}, { 535,10}, { 279,10}, { 343,11}, {1367,11}, { 855,11}, {1879,11}, { 215,11}, {1239,11}, { 727,11}, {1751,11}, { 471,11}, {1495,11}, { 983,11}, {2007,11}, { 55,11}, {1079,11}, { 567,11}, {1591,11}, { 311,11}, {1335,11}, { 823,11}, {1847,11}, { 183,11}, {1207,11}, { 695,11}, {1719,11}, { 439,11}, {1463,11}, { 951,11}, {1975,11}, { 119,11}, {1143,11}, { 631,11}, {1655,11}, { 375,11}, {1399,11}, { 887,11}, {1911,11}, { 247,11}, {1271,11}, { 759,11}, {1783,11}, { 503,11}, {1527,11}, {1015,11}, {2039,11}, { 15,11}, {1039,11}, { 527,11}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, {1423,11}, { 911,11}, {1935,11}, { 79,11}, {1103,11}, { 591,11}, {1615,11}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 207,11}, {1231,11}, { 719,11}, {1743,11}, { 463,11}, {1487,11}, { 975,11}, {1999,11}, { 47,11}, {1071,11}, { 559,11}, {1583,11}, { 303,11}, {1327,11}, { 815,11}, {1839,11}, { 175,11}, {1199,11}, { 687,11}, {1711,11}, { 431,11}, {1455, ...`
- L4803 _variable_ `static radaudio_huffman rada_nonzero_coefficient_big_huff3 = { #ifdef HUFFMAN_ENCODE { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 4}, { 4, 5}, { 20, 5}, { 12, 5}, { 28, 5}, { 2, 5}, { 18, 5}, { 30, 6}, { 62, 6}, { 1, 6}, { 33, 6}, { 17, 6}, { 49, 6}, { 53, 7}, { 117, 7}, { 13, 7}, { 77, 7}, { 45, 7}, { 109, 7}, { 29, 7}, { 93, 7}, { 51, 8}, { 179, 8}, { 115, 8}, { 243, 8}, { 11, 8}, { 139, 8}, { 75, 8}, { 203, 8}, { 43, 8}, { 123, 9}, { 379, 9}, { 251, 9}, { 507, 9}, { 7, 9}, { 263, 9}, { 135, 9}, { 391, 9}, { 71, 9}, { 327, 9}, { 151,10}, { 663,10}, { 407,10}, { 919,10}, { 87,10}, { 599,10}, { 343,10}, { 855,10}, { 215,10}, { 727,10}, { 471,10}, { 983,10}, { 55,10}, { 759,11}, {1783,11}, { 503,11}, {1527,11}, {1015,11}, {2039,11}, { 15,11}, {1039,11}, { 527,11}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, {1423,11}, { 911,11}, {1935,11}, { 79,11}, {1103,11}, { 591,11}, {1615,11}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 207,11}, {1231,11}, { 719,11}, {1743,11}, { 463,11}, {1487,11}, { 975,11}, {1999,11}, { 47,11}, {1071,11}, { 559,11}, {1583,11}, { 303,11}, {1327,11}, { 815,11}, {1839,11}, { 175,11}, {1199,11}, { 687,11}, {1711,11}, { 431,11}, { 199, 9}, {1455,11}, { 943,11}, {1967,11}, { 111,11}, {1135,11}, { 623,11}, {1647,11}, { 367,11}, {1391,11}, { 879,11}, {1903,11}, { 239,11}, {1263,11}, { 751,11}, {1775,11}, { 495,11}, {1519,11}, {1007,11}, {2031,11}, { 31,11}, {1 ...`
- L5103 _variable_ `static radaudio_huffman rada_nonzero_coefficient_pair_huff0 = { #ifdef HUFFMAN_ENCODE { { 503,11}, {1527,11}, {1015,11}, {2039,11}, { 15,11}, {1039,11}, { 231,10}, { 219, 9}, { 0, 0}, { 475, 9}, { 743,10}, { 527,11}, {1551,11}, { 271,11}, {1295,11}, { 783,11}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, {1423,11}, { 911,11}, { 0, 0}, {1935,11}, { 79,11}, {1103,11}, { 591,11}, {1615,11}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 207,11}, {1231,11}, { 719,11}, {1743,11}, { 463,11}, { 487,10}, { 0, 0}, { 999,10}, {1487,11}, { 975,11}, {1999,11}, { 47,11}, {1071,11}, { 559,11}, {1583,11}, { 303,11}, {1327,11}, { 815,11}, {1839,11}, { 175,11}, { 23,10}, { 59, 9}, { 0, 0}, { 535,10}, { 279,10}, {1199,11}, { 687,11}, {1711,11}, { 431,11}, {1455,11}, { 943,11}, {1967,11}, { 111,11}, {1135,11}, { 623,11}, { 791,10}, { 315, 9}, { 187, 9}, { 0, 0}, { 443, 9}, { 123, 9}, { 151,10}, {1647,11}, { 367,11}, {1391,11}, { 879,11}, { 663,10}, {1903,11}, { 239,11}, {1263,11}, { 407,10}, { 379, 9}, { 11, 8}, { 29, 7}, { 0, 0}, { 93, 7}, { 139, 8}, { 251, 9}, { 919,10}, { 751,11}, {1775,11}, { 495,11}, { 87,10}, {1519,11}, {1007,11}, { 599,10}, { 507, 9}, { 75, 8}, { 61, 7}, { 13, 6}, { 0, 0}, { 1, 5}, { 125, 7}, { 203, 8}, { 7, 9}, { 343,10}, {2031,11}, { 31,11}, { 263, 9}, {1055,11}, { 855,10}, { 215,10}, { 43, 8}, { 3, 7}, { 17, 5}, { 0, 3}, { 0, 0}, { 4, 3}, { 9, 5}, { 67, 7}, { 135, 9}, { 727,10}, { 471,10}, { 543,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0 ...`
- L5403 _variable_ `static radaudio_huffman rada_nonzero_coefficient_pair_huff1 = { #ifdef HUFFMAN_ENCODE { { 30, 6}, { 183,10}, { 75, 9}, { 331, 9}, { 203, 9}, { 29, 8}, { 157, 8}, { 25, 7}, { 0, 0}, { 89, 7}, { 93, 8}, { 221, 8}, { 459, 9}, { 43, 9}, { 299, 9}, { 695,10}, { 439,10}, { 111,11}, {1135,11}, { 623,11}, {1647,11}, { 367,11}, {1391,11}, { 951,10}, { 0, 0}, { 119,10}, { 879,11}, {1903,11}, { 239,11}, {1263,11}, { 751,11}, {1775,11}, { 171, 9}, { 495,11}, {1519,11}, {1007,11}, {2031,11}, { 31,11}, { 631,10}, { 427, 9}, { 0, 0}, { 107, 9}, { 375,10}, {1055,11}, { 543,11}, {1567,11}, { 287,11}, {1311,11}, { 363, 9}, { 799,11}, {1823,11}, { 159,11}, {1183,11}, { 887,10}, { 235, 9}, { 491, 9}, { 0, 0}, { 27, 9}, { 283, 9}, { 247,10}, { 759,10}, { 671,11}, {1695,11}, { 415,11}, { 155, 9}, {1439,11}, { 927,11}, {1951,11}, { 503,10}, { 411, 9}, { 91, 9}, { 61, 8}, { 0, 0}, { 189, 8}, { 347, 9}, { 219, 9}, {1015,10}, { 15,10}, { 95,11}, {1119,11}, { 125, 8}, { 607,11}, {1631,11}, { 527,10}, { 475, 9}, { 59, 9}, { 253, 8}, { 57, 7}, { 0, 0}, { 121, 7}, { 3, 8}, { 131, 8}, { 315, 9}, { 271,10}, { 351,11}, {1375,11}, { 67, 8}, { 863,11}, { 783,10}, { 187, 9}, { 443, 9}, { 195, 8}, { 5, 7}, { 62, 6}, { 0, 0}, { 1, 6}, { 69, 7}, { 35, 8}, { 123, 9}, { 379, 9}, { 143,10}, {1887,11}, { 37, 7}, { 655,10}, { 251, 9}, { 507, 9}, { 163, 8}, { 101, 7}, { 33, 6}, { 0, 3}, { 0, 0}, { 4, 3}, { 14, 5}, { 21, 7}, { 99, 8}, { 7, 9}, { 263, 9}, { 399,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, {  ...`
- L5703 _variable_ `static radaudio_huffman rada_nonzero_coefficient_pair_huff2 = { #ifdef HUFFMAN_ENCODE { { 35, 8}, { 207,11}, {1231,11}, { 231,10}, { 743,10}, { 155, 9}, { 411, 9}, { 163, 8}, { 0, 0}, { 99, 8}, { 91, 9}, { 347, 9}, { 487,10}, { 999,10}, { 719,11}, {1743,11}, { 463,11}, {1487,11}, { 975,11}, {1999,11}, { 47,11}, {1071,11}, { 559,11}, { 23,10}, { 0, 0}, { 535,10}, {1583,11}, { 303,11}, {1327,11}, { 815,11}, {1839,11}, { 175,11}, {1199,11}, { 687,11}, {1711,11}, { 431,11}, {1455,11}, { 943,11}, {1967,11}, { 279,10}, { 0, 0}, { 791,10}, { 151,10}, { 111,11}, {1135,11}, { 623,11}, {1647,11}, { 367,11}, { 663,10}, {1391,11}, { 879,11}, {1903,11}, { 239,11}, {1263,11}, { 407,10}, { 219, 9}, { 0, 0}, { 475, 9}, { 919,10}, { 87,10}, { 751,11}, {1775,11}, { 495,11}, {1519,11}, { 599,10}, {1007,11}, {2031,11}, { 31,11}, {1055,11}, { 343,10}, { 59, 9}, { 227, 8}, { 0, 0}, { 19, 8}, { 315, 9}, { 855,10}, { 215,10}, { 543,11}, {1567,11}, { 287,11}, { 187, 9}, {1311,11}, { 799,11}, {1823,11}, { 727,10}, { 443, 9}, { 147, 8}, { 53, 7}, { 0, 0}, { 117, 7}, { 83, 8}, { 123, 9}, { 471,10}, { 983,10}, { 159,11}, {1183,11}, { 379, 9}, { 671,11}, { 55,10}, { 567,10}, { 251, 9}, { 211, 8}, { 13, 7}, { 25, 6}, { 0, 0}, { 1, 5}, { 77, 7}, { 51, 8}, { 507, 9}, { 311,10}, { 823,10}, {1695,11}, { 179, 8}, { 183,10}, { 695,10}, { 7, 9}, { 115, 8}, { 45, 7}, { 57, 6}, { 0, 3}, { 0, 0}, { 4, 3}, { 17, 5}, { 109, 7}, { 243, 8}, { 263, 9}, { 439,10}, { 951,10}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, {  ...`
- L6003 _variable_ `static radaudio_huffman rada_nonzero_coefficient_pair_huff3 = { #ifdef HUFFMAN_ENCODE { { 59, 9}, { 271,11}, {1295,11}, { 783,11}, { 359,10}, { 871,10}, { 315, 9}, { 187, 9}, { 0, 0}, { 443, 9}, { 123, 9}, { 231,10}, { 743,10}, {1807,11}, { 143,11}, {1167,11}, { 655,11}, {1679,11}, { 399,11}, {1423,11}, { 911,11}, {1935,11}, { 79,11}, {1103,11}, { 0, 0}, { 591,11}, {1615,11}, { 335,11}, {1359,11}, { 847,11}, {1871,11}, { 207,11}, {1231,11}, { 719,11}, {1743,11}, { 463,11}, {1487,11}, { 975,11}, {1999,11}, { 487,10}, { 0, 0}, { 999,10}, { 47,11}, {1071,11}, { 559,11}, {1583,11}, { 303,11}, {1327,11}, { 815,11}, {1839,11}, { 175,11}, {1199,11}, { 687,11}, {1711,11}, { 23,10}, { 535,10}, { 0, 0}, { 279,10}, { 791,10}, { 431,11}, {1455,11}, { 943,11}, {1967,11}, { 111,11}, { 151,10}, {1135,11}, { 623,11}, {1647,11}, { 367,11}, { 663,10}, { 379, 9}, { 51, 8}, { 0, 0}, { 179, 8}, { 251, 9}, { 407,10}, {1391,11}, { 879,11}, {1903,11}, { 239,11}, { 919,10}, {1263,11}, { 751,11}, {1775,11}, { 87,10}, { 507, 9}, { 115, 8}, { 45, 7}, { 0, 0}, { 109, 7}, { 243, 8}, { 7, 9}, { 599,10}, { 495,11}, {1519,11}, {1007,11}, { 263, 9}, {2031,11}, { 31,11}, { 343,10}, { 135, 9}, { 11, 8}, { 29, 7}, { 21, 6}, { 0, 0}, { 1, 5}, { 93, 7}, { 139, 8}, { 391, 9}, { 855,10}, {1055,11}, { 543,11}, { 71, 9}, {1567,11}, { 215,10}, { 727,10}, { 75, 8}, { 61, 7}, { 53, 6}, { 0, 3}, { 0, 0}, { 4, 3}, { 17, 5}, { 125, 7}, { 203, 8}, { 471,10}, { 983,10}, { 287,11}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0},  ...`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_mdct.h` (Other)


#### Free symbols / members of external scopes

- L9 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L11 _macro_ `#define radaudio_mdct_fft WRAPPED_NAME(radaudio_mdct_fft)`
- L12 _macro_ `#define radaudio_imdct_fft_only_middle WRAPPED_NAME(radaudio_imdct_fft_only_middle)`
- L17 _prototype_ `void radaudio_mdct_fft(radaudio_cpu_features cpu, float *mdct_coef, size_t N, float const *signal0, float const *signal1, float *work);` — void radaudio_mdct_fft(float *mdct_coef, size_t N, float const *signal0, float const *signal1, float *work);
- L29 _prototype_ `void radaudio_imdct_fft_only_middle(radaudio_cpu_features cpu, float *signal_both, float *mdct_coef, size_t N);` — Abstractly, computes 2N IMDCT results signal0:signal1 from N input coeffs Practically, computes N IMDCT results [--:sig0:sig1:--] from N input coeffs and packs them as [sig0:sig1] in signal_both. mdct_coeff[] is overwritten in the process. (It's used internally as workspace.) both signal outputs are packed into a single buffer to allow the signal buffer to be used as an additional work buffer. N must be even, >=4.

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_mdct_internal.h` (Other)


#### enum `FftSign`  
`enum FftSign`  
_L9-13_
- L11 _public enumerator_ `FftSign_Negative = 0` — Negative exponential (the customary "forward" FFT)
- L12 _public enumerator_ `FftSign_Positive` — Positive exponential (customary "inverse" FFT)

#### struct `radaudio_fft_impl::FftKernelSet`  
`struct FftKernelSet`  
_L77-83_
- L79 _public member_ `InitialPassesKernel * initial;` — Initial bit reverse and first few passes
- L80 _public member_ `CFftKernel * cfft_pass;` — Complex FFT passes
- L81 _public member_ `ImdctPreFftKernel * imdct_pre;` — Pre-FFT IMDCT kernel
- L82 _public member_ `ImdctPostFftKernel * imdct_post;` — Post-FFT IMDCT kernel

#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_MDCT_INTERNAL_H`
- L17 _macro_ `#define WRAPPED_NAME(name) RR_STRING_JOIN(RADAUDIO_WRAP, name##_)`
- L19 _macro_ `#define radaudio_fft_impl WRAPPED_NAME(radaudio_fft_impl)`
- L24 _namespace_ `namespace radaudio_fft_impl`
- L26 _variable_ `static size_t const kMaxFFTLog2 = 9;` (scope `radaudio_fft_impl`)
- L27 _variable_ `static size_t const kMaxFFTN = 1 << kMaxFFTLog2;` (scope `radaudio_fft_impl`) — This is the largest straight FFT we support
- L41 _prototype_ `extern FFT_ALIGN(float, s_fft_twiddles[kMaxFFTN * 2]);` (scope `radaudio_fft_impl`) — Main twiddle array: sine of N values for N=1,2,4,8,...,kMaxN First radix2 level uses N/4 twiddles from N/2 twiddle array (so 1/2 the table); cosine table is offset by N/8 from it (another 1/4 the table); for inverse transform, we just start into the sine table from offset N/4 (halfway into the circle). That means we use all of the sine table. Second radix2 level uses N/4 twiddles from N twiddle array (1/4 the table) and has the cosine table offset by 1/4; for an inverse FFT the sine table is accessed offset by N/2. In total, we end up using 3/4 of that larger sine table.
- L45 _prototype_ `extern FFT_ALIGN(float, s_mdct_long_twiddles[RADAUDIO_LONG_BLOCK_LEN]);` (scope `radaudio_fft_impl`) — A size-N MDCT/IMDCT needs N/2 complex twiddles, which are just scaled complex exponentials. We store first all the real parts then all the imaginary parts.
- L46 _prototype_ `extern FFT_ALIGN(float, s_mdct_short_twiddles[RADAUDIO_SHORT_BLOCK_LEN]);` (scope `radaudio_fft_impl`)
- L49 _typedef_ `typedef U16 FFTIndex;` (scope `radaudio_fft_impl`)
- L51 _externvar_ `extern FFTIndex s_bit_reverse[kMaxFFTN];` (scope `radaudio_fft_impl`)
- L55 _variable_ `static size_t constexpr kBurstSize = 16;` (scope `radaudio_fft_impl`) — Burst-layout radix 2 FFTs First kBurstSize real values, then kBurstSize corresponding imaginary values, then kBurstSize reals again, and so forth.
- L56 _variable_ `static size_t constexpr kBurstMask = kBurstSize - 1;` (scope `radaudio_fft_impl`)
- L58 _function_ `static constexpr inline size_t burst_swizzle(size_t i)` (scope `radaudio_fft_impl`)
- L69 _typedef_ `typedef size_t InitialPassesKernel(float * out, float const * in, size_t N, FftSign sign);` (scope `radaudio_fft_impl`) — Bit reverse and initial passes, returns stride of next pass to run
- L71 _typedef_ `typedef void CFftKernel(float * out, size_t step, size_t swiz_N, FftSign sign);` (scope `radaudio_fft_impl`) — Complex FFT radix-4 (actually 2^2) pass
- L73 _typedef_ `typedef void ImdctPreFftKernel(float * dest, float const * coeffs, float const * tw_re, float const * tw_im, size_t N);` (scope `radaudio_fft_impl`) — IMDCT pre-FFT pass
- L75 _typedef_ `typedef void ImdctPostFftKernel(float * signal0, float * signal1, float const * dft, float const * tw_re, float const * tw_im, size_t N);` (scope `radaudio_fft_impl`) — IMDCT post-FFT pass
- L86 _externvar_ `extern FftKernelSet const kernels_scalar;` (scope `radaudio_fft_impl`) — available kernel sets
- L87 _externvar_ `extern FftKernelSet const kernels_sse2;` (scope `radaudio_fft_impl`)
- L88 _externvar_ `extern FftKernelSet const kernels_avx2;` (scope `radaudio_fft_impl`)
- L89 _externvar_ `extern FftKernelSet const kernels_neon;` (scope `radaudio_fft_impl`)

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_mdct_internal.inl` (Other)


#### struct `radaudio_fft_impl::DefaultBitReverse`  
`struct DefaultBitReverse`  
_L70-83_
- desc: Default bit reverse alg uses our LUT
- L72 _public member_ `size_t shift_amt;`
- L74 _public function_ `DefaultBitReverse(size_t fft_nbits) : shift_amt(kMaxFFTLog2 - fft_nbits)`
- L79 _public function_ `size_t operator()(size_t i) const`

#### Free symbols / members of external scopes

- L4 _namespace_ `namespace radaudio_fft_impl`
- L7 _function_ `template<typename T> static RADFORCEINLINE void swap(T& a, T& b)` (scope `radaudio_fft_impl`)
- L18 _function_ `template<typename T> static RADFORCEINLINE void radix2_bfly(T& ar, T& ai, T& br, T& bi)` (scope `radaudio_fft_impl`) — Pure radix2 butterfly a' = a + b b' = a - b
- L33 _function_ `template<typename T> static RADFORCEINLINE void radix2_twiddle_unfused(T& ar, T& ai, T& br, T& bi, T wr, T wi)` (scope `radaudio_fft_impl`) — Twiddle bt = b * w a' = a + bt b' = a - bt
- L48 _function_ `template<typename T> static RADFORCEINLINE void dft4_bfly_permuted(T& ar, T& ai, T& br, T& bi, T& cr, T& ci, T& dr, T& di)` (scope `radaudio_fft_impl`) — Permuted DFT4 butterfly for use in radix-2 decompositions
- L86 _function_ `template<typename T, typename TBitReverse=DefaultBitReverse> static size_t bitrev_initial_radix4_core_vec4(float *out, float const *in, size_t N, FftSign sign)` (scope `radaudio_fft_impl`)
- L148 _function_ `template<typename T> static void initial_radix2_core_vec4(float * out, size_t N, FftSign sign)` (scope `radaudio_fft_impl`)
- L177 _function_ `template<typename T, typename TBitReverse=DefaultBitReverse> static size_t bitrev_initial_radix8_core_vec4(float *out, float const *in, size_t N, FftSign sign)` (scope `radaudio_fft_impl`) — This is initial_radix4 + initial_radix2 in one fused pass, for archs with plenty of regs.
- L278 _function_ `template<typename T> static void burst_r4_fft_single_pass(float * out, size_t step, size_t swiz_N, FftSign sign)` (scope `radaudio_fft_impl`)
- L371 _function_ `template<typename T> static void burst_imdct_prefft(float * dest, float const * coeffs, float const * tw_re, float const * tw_im, size_t N)` (scope `radaudio_fft_impl`)
- L476 _function_ `template<typename T> static void burst_imdct_postfft(float * signal0, float * signal1, float const * dft, float const * tw_re, float const * tw_im, size_t N)` (scope `radaudio_fft_impl`)

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_mdct_tables.inl` (Other)


#### Free symbols / members of external scopes

- L2 _prototype_ `FFT_ALIGN(float, s_fft_twiddles[1024]) =`
- L133 _prototype_ `FFT_ALIGN(float, s_mdct_short_twiddles[128]) =`
- L152 _prototype_ `FFT_ALIGN(float, s_mdct_long_twiddles[1024]) =`
- L283 _variable_ `FFTIndex s_bit_reverse[512] = { 0, 256, 128, 384, 64, 320, 192, 448, 32, 288, 160, 416, 96, 352, 224, 480, 16, 272, 144, 400, 80, 336, 208, 464, 48, 304, 176, 432, 112, 368, 240, 496, 8, 264, 136, 392, 72, 328, 200, 456, 40, 296, 168, 424, 104, 360, 232, 488, 24, 280, 152, 408, 88, 344, 216, 472, 56, 312, 184, 440, 120, 376, 248, 504, 4, 260, 132, 388, 68, 324, 196, 452, 36, 292, 164, 420, 100, 356, 228, 484, 20, 276, 148, 404, 84, 340, 212, 468, 52, 308, 180, 436, 116, 372, 244, 500, 12, 268, 140, 396, 76, 332, 204, 460, 44, 300, 172, 428, 108, 364, 236, 492, 28, 284, 156, 412, 92, 348, 220, 476, 60, 316, 188, 444, 124, 380, 252, 508, 2, 258, 130, 386, 66, 322, 194, 450, 34, 290, 162, 418, 98, 354, 226, 482, 18, 274, 146, 402, 82, 338, 210, 466, 50, 306, 178, 434, 114, 370, 242, 498, 10, 266, 138, 394, 74, 330, 202, 458, 42, 298, 170, 426, 106, 362, 234, 490, 26, 282, 154, 410, 90, 346, 218, 474, 58, 314, 186, 442, 122, 378, 250, 506, 6, 262, 134, 390, 70, 326, 198, 454, 38, 294, 166, 422, 102, 358, 230, 486, 22, 278, 150, 406, 86, 342, 214, 470, 54, 310, 182, 438, 118, 374, 246, 502, 14, 270, 142, 398, 78, 334, 206, 462, 46, 302, 174, 430, 110, 366, 238, 494, 30, 286, 158, 414, 94, 350, 222, 478, 62, 318, 190, 446, 126, 382, 254, 510, 1, 257, 129, 385, 65, 321, 193, 449, 33, 289, 161, 417, 97, 353, 225, 481, 17, 273, 145, 401, 81, 337, 209, 465, 49, 305, 177, 433, 113, 369, 241, 497, 9, 265, 137, 393, 73, 329, 201, 457, 41, 297, 169, 425, 105, 361, 233, 489, 25, 281, 153, 4 ...`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/radaudio_sse.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define RADAUDIO_SSE_H`
- L10 _macro_ `#define DO_BUILD_SSE4`
- L15 _macro_ `#define DO_BUILD_AVX2`
- L20 _macro_ `#define DO_BUILD_NEON`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/rrCore.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define __RADRR_CORE2H__`
- L15 _macro_ `#define RADTODO(str) { char __str[0]=str; }`
- L17 _macro_ `#define RADTODO(str)`
- L21 _macro_ `#define __RADBSD__`
- L25 _macro_ `#define __RADPOSIX__`
- L29 _macro_ `#define RAD_PTRBITS 64`
- L30 _macro_ `#define RAD_PTRBYTES 8`
- L31 _macro_ `#define RAD_TWOPTRBYTES 16`
- L33 _macro_ `#define RAD_PTRBITS 32`
- L34 _macro_ `#define RAD_PTRBYTES 4`
- L35 _macro_ `#define RAD_TWOPTRBYTES 8`
- L40 _macro_ `#define RAD_TLS(type,var) __thread type var`
- L42 _macro_ `#define RR_BREAK() __builtin_trap()`
- L44 _macro_ `#define RR_CACHE_LINE_SIZE 32`
- L46 _macro_ `#define RR_CACHE_LINE_SIZE 64`
- L48 _macro_ `#define RAD_GUARANTEED_SSE3 // always sse3 on mac`
- L49 _macro_ `#define RAD_USES_SSE3 // don't need any special markup for sse3 on mac`
- L50 _macro_ `#define RAD_USES_SSSE3 // don't need any special markup for ssse3 on mac`
- L55 _macro_ `#define RAD_GUARANTEED_SSE3 // simulator has sse3`
- L56 _macro_ `#define RAD_USES_SSE3 // don't need any special markup for sse3 on sim`
- L90 _macro_ `#define __RAD64REGS__`
- L97 _macro_ `#define RR_BREAK __debugbreak`
- L100 _macro_ `#define RADASMLINK __cdecl`
- L102 _macro_ `#define RAD_TLS(type,var) __declspec(thread) type var`
- L115 _macro_ `#define RR_BREAK() RAD_STATEMENT_WRAPPER( __asm {int 3} )`
- L130 _macro_ `#define RAD_UINTr RAD_U64`
- L131 _macro_ `#define RAD_SINTr RAD_S64`
- L133 _macro_ `#define RAD_UINTr RAD_U32`
- L134 _macro_ `#define RAD_SINTr RAD_S32`
- L144 _macro_ `#define RADLINK`
- L145 _macro_ `#define RADEXPLINK`
- L146 _macro_ `#define RADDLLEXPORTDLL`
- L147 _macro_ `#define RADDLLIMPORTDLL`
- L156 _macro_ `#define RRSTRIPPABLE __declspec(selectany)`
- L157 _macro_ `#define RRSTRIPPABLEPUB __declspec(selectany)`
- L159 _macro_ `#define RRSTRIPPABLE static`
- L160 _macro_ `#define RRSTRIPPABLEPUB`
- L170 _macro_ `#define RAD_ALIGN(type,var,num) type __declspec(align(num)) var`
- L171 _macro_ `#define RADNOINLINE __declspec(noinline)`
- L173 _macro_ `#define RADNOINLINE`
- L177 _macro_ `#define RAD_USES_SSE3 // vs2008+ can compile SSE3 with no special markup`
- L180 _macro_ `#define RAD_USES_SSSE3 // vs2008+ can compile SSSE3 with no special markup`
- L183 _macro_ `#define RADFORCEINLINE __forceinline`
- L184 _macro_ `#define RADUNREACHABLE __assume(0)`
- L185 _macro_ `#define RADASSUME(exp) __assume(exp)`
- L189 _macro_ `#define RAD_EXPECT(expr,cond) (expr)`
- L193 _macro_ `#define RAD_ALIGN(type,var,num) type __attribute__ ((aligned (num))) var`
- L195 _macro_ `#define RADFORCEINLINE inline`
- L197 _macro_ `#define RADFORCEINLINE inline __attribute((always_inline))`
- L201 _macro_ `#define RAD_USES_SSE3 __attribute__((target("sse3")))`
- L204 _macro_ `#define RAD_USES_SSSE3 __attribute__((target("ssse3")))`
- L207 _macro_ `#define RADNOINLINE __attribute__((noinline))`
- L208 _macro_ `#define RADUNREACHABLE __builtin_unreachable()`
- L210 _macro_ `#define RADASSUME(exp) __builtin_assume(exp)`
- L212 _macro_ `#define RADASSUME(exp) RAD_STATEMENT_WRAPPER( if ( ! (exp) ) __builtin_unreachable(); )`
- L214 _macro_ `#define RAD_EXPECT(expr,cond) __builtin_expect(expr,cond)`
- L226 _macro_ `#define __RAD_GCC_VERSION__ (__GNUC__ * 10000 \`
- L234 _macro_ `#define RADUNREACHABLE RAD_INFINITE_LOOP( RR_BREAK(); )`
- L235 _macro_ `#define RADASSUME(exp)`
- L265 _macro_ `#define RADASSUME(exp) RAD_STATEMENT_WRAPPER( if ( ! (exp) ) RADUNREACHABLE; )`
- L268 _macro_ `#define RADUNREACHABLE`
- L270 _macro_ `#define RAD_EXPECT(exp,cond) !! no RAD_EXPECT defined !!`
- L271 _macro_ `#define RADASSUME(exp) !! no RADASSUME defined !!`
- L272 _macro_ `#define RADUNREACHABLE !! no RADUNREACHABLE defined !!`
- L273 _macro_ `#define RADFORCEINLINE !! no RADFORCEINLINE defined !!`
- L274 _macro_ `#define RADNOINLINE !! no RADNOINLINE defined !!`
- L281 _macro_ `#define RAD_LIKELY(expr) RAD_EXPECT(expr,1)` — helpers for doing an if ( ) with expect : if ( RAD_LIKELY(expr) ) { ... }
- L282 _macro_ `#define RAD_UNLIKELY(expr) RAD_EXPECT(expr,0)`
- L288 _macro_ `#define __RADX86ASM__`
- L301 _macro_ `#define RAD_STATEMENT_START \`
- L304 _macro_ `#define RAD_STATEMENT_END_FALSE \`
- L310 _macro_ `#define RAD_STATEMENT_END_TRUE \`
- L317 _macro_ `#define RAD_USE_STANDARD_LOOP_CONSTRUCT`
- L334 _macro_ `#define RAD_STATEMENT_WRAPPER( code ) \`
- L339 _macro_ `#define RAD_INFINITE_LOOP( code ) \`
- L349 _macro_ `#define RR_UNUSED_VARIABLE(x) (void) (x)`
- L351 _macro_ `#define RR_UNUSED_VARIABLE(x) (void)(sizeof(x))`
- L356 _macro_ `#define RR_STRINGIZE( L ) #L` — RR_LINESTRING is the current line number as a string
- L357 _macro_ `#define RR_DO_MACRO( M, X ) M(X)`
- L358 _macro_ `#define RR_STRINGIZE_DELAY( X ) RR_DO_MACRO( RR_STRINGIZE, X )`
- L359 _macro_ `#define RR_LINESTRING RR_STRINGIZE_DELAY( __LINE__ )`
- L361 _macro_ `#define RR_CAT(X,Y) X ## Y`
- L363 _macro_ `#define RR_STRING_JOIN3(arg1, arg2, arg3) RR_STRING_JOIN_DELAY3(arg1, arg2, arg3)`
- L364 _macro_ `#define RR_STRING_JOIN_DELAY3(arg1, arg2, arg3) RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3)`
- L365 _macro_ `#define RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3) arg1 ## arg2 ## arg3`
- L371 _macro_ `#define RR_MIN(a,b) ( (a) < (b) ? (a) : (b) )`
- L375 _macro_ `#define RR_MAX(a,b) ( (a) > (b) ? (a) : (b) )`
- L379 _macro_ `#define RR_ABS(a) ( ((a) < 0) ? -(a) : (a) )`
- L383 _macro_ `#define RR_CLAMP(val,lo,hi) RR_MAX( RR_MIN(val,hi), lo )`
- L389 _macro_ `#define RR_ARRAY_SIZE(array) ( sizeof(array)/sizeof(array[0]) )`
- L392 _macro_ `#define RR_MEMBER_OFFSET(type,member) offsetof(type, member)` — MEMBER_OFFSET tells you the offset of a member in a type
- L395 _macro_ `#define RR_MEMBER_SIZE(type,member) ( sizeof( ((type *) 0)->member) )` — MEMBER_SIZE tells you the size of a member in a type
- L398 _macro_ `#define RR_MEMBER_OFFSET_PTR(type,member,ptr) ( (SINTa) &(((type *)(ptr))->member) - (SINTa)(ptr) )` — just to make gcc shut up about derefing null :
- L399 _macro_ `#define RR_MEMBER_SIZE_PTR(type,member,ptr) ( sizeof( ((type *) (ptr))->member) )`
- L403 _macro_ `#define RR_MEMBER_TO_OWNER(type,member,ptr) (type *)( ((char *)(ptr)) - RR_MEMBER_OFFSET_PTR(type,member,ptr) )` — MEMBER_TO_OWNER takes a pointer to a member and gives you back the base of the object you should then RR_ASSERT( &(ret->member) == ptr );
- L417 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) // nop`
- L418 _macro_ `#define RR_PREFETCH_WRITE_INVALIDATE(ptr,offset) // nop`
- L420 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) // intentional NOP for now`
- L423 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) __prefetch((char *)(ptr) + (int)(offset))`
- L431 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) !! NO PREFETCH DEFINED !!`
- L434 _macro_ `#define RR_PREFETCH_WRITE_INVALIDATE(ptr,offset) !! NO PREFETCH DEFINED !!`
- L443 _macro_ `#define RR_DO_ASSERTS`
- L475 _macro_ `#define RR_ASSERT_BREAK() (void)0`
- L477 _macro_ `#define RR_ASSERT_BREAK() RR_BREAK()`
- L482 _macro_ `#define RR_ASSERT_ALWAYS(exp) RAD_STATEMENT_WRAPPER( if ( ! (exp) ) { RR_ASSERT_BREAK(); } )`
- L486 _macro_ `#define RR_ASSERT_FAILURE_ALWAYS(str) RAD_STATEMENT_WRAPPER( RR_ASSERT_BREAK(); )`
- L489 _macro_ `#define RR_ASSERT_LITE_ALWAYS(exp) RAD_STATEMENT_WRAPPER( if ( ! (exp) ) { RR_ASSERT_BREAK(); } )`
- L494 _macro_ `#define RR_ASSERT(exp) RR_ASSERT_ALWAYS(exp)`
- L495 _macro_ `#define RR_ASSERT_LITE(exp) RR_ASSERT_LITE_ALWAYS(exp)`
- L496 _macro_ `#define RR_ASSERT_NO_ASSUME(exp) RR_ASSERT_ALWAYS(exp)`
- L498 _macro_ `#define RR_DURING_ASSERT(exp) exp` — RR_DURING_ASSERT is to set up expressions or declare variables that are only used in asserts
- L499 _macro_ `#define RR_ASSERT_FAILURE(str) RR_ASSERT_FAILURE_ALWAYS(str)`
- L501 _macro_ `#define RR_CANT_GET_HERE() RAD_STATEMENT_WRAPPER( RR_ASSERT_FAILURE("can't get here"); RADUNREACHABLE; )` — RR_CANT_GET_HERE is for like defaults in switches that should never be hit
- L503 _macro_ `#define RR_ASSERT(exp) (void)0`
- L504 _macro_ `#define RR_ASSERT_LITE(exp) (void)0`
- L505 _macro_ `#define RR_ASSERT_NO_ASSUME(exp) (void)0`
- L506 _macro_ `#define RR_DURING_ASSERT(exp) (void)0`
- L507 _macro_ `#define RR_ASSERT_FAILURE(str) (void)0`
- L508 _macro_ `#define RR_CANT_GET_HERE() RADUNREACHABLE`
- L515 _macro_ `#define RR_ASSERT_RELEASE(exp) RR_ASSERT_ALWAYS(exp)`
- L516 _macro_ `#define RR_ASSERT_LITE_RELEASE(exp) RR_ASSERT_LITE_ALWAYS(exp)`
- L518 _macro_ `#define RR_ASSERT_RELEASE(exp) (void)0`
- L519 _macro_ `#define RR_ASSERT_LITE_RELEASE(exp) (void)0`
- L523 _macro_ `#define RR_ASSERT_ALIGNED(ptr) RR_ASSERT( (((UINTa)(ptr)) & (sizeof(*(ptr))-1)) == 0 )` — check a pointer for natural alignment :
- L527 _macro_ `#define RR_ASSERT_ALWAYS_NO_SHIP RR_ASSERT_RELEASE` — This never gets compiled away except for __RADFINAL__
- L529 _macro_ `#define rrAssert RR_ASSERT`
- L530 _macro_ `#define rrassert RR_ASSERT`
- L555 _macro_ `#define RR_GET_PTR_POST RADRESTRICT`
- L558 _macro_ `#define RR_GET_PTR_POST`
- L563 _macro_ `#define RR_GET16_NATIVE(ptr) *((const U16 * RR_GET_PTR_POST)(ptr))`
- L564 _macro_ `#define RR_PUT16_NATIVE(ptr,val) *((U16 * RR_GET_PTR_POST)(ptr)) = (U16)(val)`
- L567 _macro_ `#define RR_U16_PTR_OFFSET(ptr,offset) ((U16 * RR_GET_PTR_POST)((char *)(ptr) + (offset)))` — offset is in bytes
- L568 _macro_ `#define RR_GET16_NATIVE_OFFSET(ptr,offset) *( RR_U16_PTR_OFFSET((ptr),offset) )`
- L569 _macro_ `#define RR_PUT16_NATIVE_OFFSET(ptr,val,offset) *( RR_U16_PTR_OFFSET((ptr),offset)) = (val)`
- L571 _macro_ `#define RR_GET32_NATIVE(ptr) *((const U32 * RR_GET_PTR_POST)(ptr))`
- L572 _macro_ `#define RR_PUT32_NATIVE(ptr,val) *((U32 * RR_GET_PTR_POST)(ptr)) = (val)`
- L575 _macro_ `#define RR_U32_PTR_OFFSET(ptr,offset) ((U32 * RR_GET_PTR_POST)((char *)(ptr) + (offset)))` — offset is in bytes
- L576 _macro_ `#define RR_GET32_NATIVE_OFFSET(ptr,offset) *( RR_U32_PTR_OFFSET((ptr),offset) )`
- L577 _macro_ `#define RR_PUT32_NATIVE_OFFSET(ptr,val,offset) *( RR_U32_PTR_OFFSET((ptr),offset)) = (val)`
- L579 _macro_ `#define RR_GET64_NATIVE(ptr) *((const U64 * RR_GET_PTR_POST)(ptr))`
- L580 _macro_ `#define RR_PUT64_NATIVE(ptr,val) *((U64 * RR_GET_PTR_POST)(ptr)) = (val)`
- L583 _macro_ `#define RR_U64_PTR_OFFSET(ptr,offset) ((U64 * RR_GET_PTR_POST)((char *)(ptr) + (offset)))` — offset is in bytes
- L584 _macro_ `#define RR_GET64_NATIVE_OFFSET(ptr,offset) *( RR_U64_PTR_OFFSET((ptr),offset) )`
- L585 _macro_ `#define RR_PUT64_NATIVE_OFFSET(ptr,val,offset) *( RR_U64_PTR_OFFSET((ptr),offset)) = (val)`
- L590 _macro_ `#define RR_GET16_LE RR_GET16_NATIVE`
- L591 _macro_ `#define RR_PUT16_LE RR_PUT16_NATIVE`
- L592 _macro_ `#define RR_GET16_LE_OFFSET RR_GET16_NATIVE_OFFSET`
- L593 _macro_ `#define RR_PUT16_LE_OFFSET RR_PUT16_NATIVE_OFFSET`
- L595 _macro_ `#define RR_GET32_LE RR_GET32_NATIVE`
- L596 _macro_ `#define RR_PUT32_LE RR_PUT32_NATIVE`
- L597 _macro_ `#define RR_GET32_LE_OFFSET RR_GET32_NATIVE_OFFSET`
- L598 _macro_ `#define RR_PUT32_LE_OFFSET RR_PUT32_NATIVE_OFFSET`
- L600 _macro_ `#define RR_GET64_LE RR_GET64_NATIVE`
- L601 _macro_ `#define RR_PUT64_LE RR_PUT64_NATIVE`
- L602 _macro_ `#define RR_GET64_LE_OFFSET RR_GET64_NATIVE_OFFSET`
- L603 _macro_ `#define RR_PUT64_LE_OFFSET RR_PUT64_NATIVE_OFFSET`
- L605 _macro_ `#define RR_GET16_BE RR_GET16_NATIVE`
- L606 _macro_ `#define RR_PUT16_BE RR_PUT16_NATIVE`
- L607 _macro_ `#define RR_GET16_BE_OFFSET RR_GET16_NATIVE_OFFSET`
- L608 _macro_ `#define RR_PUT16_BE_OFFSET RR_PUT16_NATIVE_OFFSET`
- L610 _macro_ `#define RR_GET32_BE RR_GET32_NATIVE`
- L611 _macro_ `#define RR_PUT32_BE RR_PUT32_NATIVE`
- L612 _macro_ `#define RR_GET32_BE_OFFSET RR_GET32_NATIVE_OFFSET`
- L613 _macro_ `#define RR_PUT32_BE_OFFSET RR_PUT32_NATIVE_OFFSET`
- L615 _macro_ `#define RR_GET64_BE RR_GET64_NATIVE`
- L616 _macro_ `#define RR_PUT64_BE RR_PUT64_NATIVE`
- L617 _macro_ `#define RR_GET64_BE_OFFSET RR_GET64_NATIVE_OFFSET`
- L618 _macro_ `#define RR_PUT64_BE_OFFSET RR_PUT64_NATIVE_OFFSET`
- L627 _prototype_ `RADDEFFUNC unsigned short __cdecl _byteswap_ushort (unsigned short _Short);`
- L628 _prototype_ `RADDEFFUNC unsigned long __cdecl _byteswap_ulong (unsigned long _Long);`
- L631 _macro_ `#define RR_BSWAP16 _byteswap_ushort`
- L632 _macro_ `#define RR_BSWAP32 _byteswap_ulong`
- L634 _prototype_ `RADDEFFUNC unsigned __int64 __cdecl _byteswap_uint64 (unsigned __int64 val);`
- L636 _macro_ `#define RR_BSWAP64 _byteswap_uint64`
- L638 _function_ `RADDEFFUNC RADFORCEINLINE unsigned long RR_BSWAP16 (unsigned long _Long)`
- L648 _function_ `RADDEFFUNC RADFORCEINLINE unsigned long RR_BSWAP32 (unsigned long _Long)`
- L658 _function_ `RADDEFFUNC RADFORCEINLINE unsigned __int64 RR_BSWAP64 (unsigned __int64 _Long)`
- L674 _macro_ `#define RR_BSWAP16(u16) ( (U16) ( ((u16) >> 8) | ((u16) << 8) ) )` — GCC has __builtin_bswap16, but Clang only seems to have added it recently. We use __builtin_bswap32/64 but 16 just uses the macro version. (No big deal if that turns into shifts anyway)
- L675 _macro_ `#define RR_BSWAP32 __builtin_bswap32`
- L676 _macro_ `#define RR_BSWAP64 __builtin_bswap64`
- L679 _macro_ `#define RR_GET16_BE(ptr) RR_BSWAP16(*((U16 *)(ptr)))`
- L680 _macro_ `#define RR_PUT16_BE(ptr,val) *((U16 *)(ptr)) = (U16) RR_BSWAP16(val)`
- L681 _macro_ `#define RR_GET16_BE_OFFSET(ptr,offset) RR_BSWAP16(*RR_U16_PTR_OFFSET(ptr,offset))`
- L682 _macro_ `#define RR_PUT16_BE_OFFSET(ptr,val,offset) *RR_U16_PTR_OFFSET(ptr,offset) = RR_BSWAP16(val)`
- L684 _macro_ `#define RR_GET32_BE(ptr) RR_BSWAP32(*((U32 *)(ptr)))`
- L685 _macro_ `#define RR_PUT32_BE(ptr,val) *((U32 *)(ptr)) = RR_BSWAP32(val)`
- L686 _macro_ `#define RR_GET32_BE_OFFSET(ptr,offset) RR_BSWAP32(*RR_U32_PTR_OFFSET(ptr,offset))`
- L687 _macro_ `#define RR_PUT32_BE_OFFSET(ptr,val,offset) *RR_U32_PTR_OFFSET(ptr,offset) = RR_BSWAP32(val)`
- L689 _macro_ `#define RR_GET64_BE(ptr) RR_BSWAP64(*((U64 *)(ptr)))`
- L690 _macro_ `#define RR_PUT64_BE(ptr,val) *((U64 *)(ptr)) = RR_BSWAP64(val)`
- L691 _macro_ `#define RR_GET64_BE_OFFSET(ptr,offset) RR_BSWAP64(*RR_U64_PTR_OFFSET(ptr,offset))`
- L692 _macro_ `#define RR_PUT64_BE_OFFSET(ptr,val,offset) *RR_U64_PTR_OFFSET(ptr,offset) = RR_BSWAP64(val)`
- L700 _macro_ `#define RR_BSWAP32(u32) ( (U32) ( ((u32) >> 24) | (((u32)<<8) & 0x00FF0000) | (((u32)>>8) & 0x0000FF00) | ((u32) << 24) ) )`
- L701 _macro_ `#define RR_BSWAP64(u64) ( (U64) ( RR_BSWAP32((u64)>>32) | ((U64)RR_BSWAP32((U32)(u64))<<32) ) )`
- L704 _macro_ `#define RR_PUT16_BE(ptr,val) *((U16 *)(ptr)) = RR_BSWAP16(val)`
- L720 _macro_ `#define RR_GET16_BE(ptr) _byteswap_ushort(*((U16 *)(ptr)))`
- L721 _macro_ `#define RR_PUT16_BE(ptr,val) *((U16 *)(ptr)) = _byteswap_ushort(val)`
- L723 _macro_ `#define RR_GET32_BE(ptr) _byteswap_ulong(*((U32 *)(ptr)))`
- L724 _macro_ `#define RR_PUT32_BE(ptr,val) *((U32 *)(ptr)) = _byteswap_ulong(val)`
- L726 _macro_ `#define RR_GET64_BE(ptr) _byteswap_uint64(*((U64 *)(ptr)))`
- L727 _macro_ `#define RR_PUT64_BE(ptr,val) *((U64 *)(ptr)) = _byteswap_uint64(val)`
- L730 _macro_ `#define RR_BSWAP16 __builtin_bswap16`
- L762 _macro_ `#define RR_GET64_BE_UNALIGNED(ptr) RR_GET64_BE(ptr)`
- L763 _macro_ `#define RR_GET64_BE_UNALIGNED_OFFSET(ptr,offset) RR_GET64_BE_OFFSET(ptr,offset)`
- L764 _macro_ `#define RR_GET32_BE_UNALIGNED(ptr) RR_GET32_BE(ptr)`
- L765 _macro_ `#define RR_GET32_BE_UNALIGNED_OFFSET(ptr,offset) RR_GET32_BE_OFFSET(ptr,offset)`
- L766 _macro_ `#define RR_GET16_BE_UNALIGNED(ptr) RR_GET16_BE(ptr)`
- L767 _macro_ `#define RR_GET16_BE_UNALIGNED_OFFSET(ptr,offset) RR_GET16_BE_OFFSET(ptr,offset)`
- L769 _macro_ `#define RR_GET64_LE_UNALIGNED(ptr) RR_GET64_LE(ptr)`
- L770 _macro_ `#define RR_GET64_LE_UNALIGNED_OFFSET(ptr,offset) RR_GET64_LE_OFFSET(ptr,offset)`
- L771 _macro_ `#define RR_GET32_LE_UNALIGNED(ptr) RR_GET32_LE(ptr)`
- L772 _macro_ `#define RR_GET32_LE_UNALIGNED_OFFSET(ptr,offset) RR_GET32_LE_OFFSET(ptr,offset)`
- L773 _macro_ `#define RR_GET16_LE_UNALIGNED(ptr) RR_GET16_LE(ptr)`
- L774 _macro_ `#define RR_GET16_LE_UNALIGNED_OFFSET(ptr,offset) RR_GET16_LE_OFFSET(ptr,offset)`
- L777 _macro_ `#define RR_GET32_BE_UNALIGNED(ptr) ( \` — Unaligned via bytes :
- L783 _macro_ `#define RR_GET32_BE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L789 _macro_ `#define RR_GET16_BE_UNALIGNED(ptr) ( \`
- L793 _macro_ `#define RR_GET16_BE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L797 _macro_ `#define RR_GET32_LE_UNALIGNED(ptr) ( \`
- L803 _macro_ `#define RR_GET32_LE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L809 _macro_ `#define RR_GET16_LE_UNALIGNED(ptr) ( \`
- L813 _macro_ `#define RR_GET16_LE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L825 _prototype_ `RADDEFFUNC unsigned long __cdecl _lrotl(unsigned long, int);`
- L827 _macro_ `#define RR_ROTL32(x,k) _lrotl((unsigned long)(x),(int)(k))`
- L832 _macro_ `#define RR_ROTL32(u32v,num) ( ( (u32v) << (num) ) | ( (u32v) >> (32 - (num))) )` — NOTE(fg): Barring evidence to the contrary, let's just assume that compilers are smart enough to turn this into rotates (where supported) by now.
- L841 _prototype_ `RADDEFFUNC unsigned __int64 __cdecl _rotl64(unsigned __int64 _Val, int _Shift);`
- L843 _macro_ `#define RR_ROTL64(x,k) _rotl64((unsigned __int64)(x),(int)(k))`
- L848 _macro_ `#define RR_ROTL64(u64v,num) ( ( (u64v) << (num) ) | ( (u64v) >> (64 - (num))) )` — NOTE(fg): Barring evidence to the contrary, let's just assume that compilers are smart enough to turn this into rotates (where supported) by now.
- L864 _macro_ `#define UINTn UINTa`
- L867 _macro_ `#define SINTn SINTa`
- L871 _macro_ `#define RADDEFINEDATA extern "C"`
- L872 _macro_ `#define RADDECLAREDATA extern "C"`
- L874 _macro_ `#define RR_NAMESPACE rr`
- L875 _macro_ `#define RR_NAMESPACE_START namespace RR_NAMESPACE {`
- L876 _macro_ `#define RR_NAMESPACE_END };`
- L877 _macro_ `#define RR_NAMESPACE_USE using namespace RR_NAMESPACE;`
- L879 _macro_ `#define RADDEFINEDATA`
- L880 _macro_ `#define RADDECLAREDATA extern`
- L882 _macro_ `#define RR_NAMESPACE`
- L883 _macro_ `#define RR_NAMESPACE_START`
- L884 _macro_ `#define RR_NAMESPACE_END`
- L885 _macro_ `#define RR_NAMESPACE_USE`

### `Source/Runtime/RadAudioCodec/SDK/Src/RadAudio/rrbits.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __RADRR_BITSH__`
- L23 _prototype_ `static U32 rrClz32(U32 val);` — count leading zero bits of U32 (val != 0)
- L24 _prototype_ `static U32 rrClz64(U64 val);` — count leading zero bits of U64 (val != 0)
- L25 _prototype_ `static U32 rrCtz32(U32 val);` — count trailing zero bits of U32 (val != 0)
- L26 _prototype_ `static U32 rrCtz64(U64 val);` — count trailing zero bits of U64 (val != 0)
- L28 _prototype_ `static U32 rrClzBytes32(U32 val);` — count leading zero bytes of U32 (val != 0)
- L29 _prototype_ `static U32 rrClzBytes64(U64 val);` — count leading zero bytes of U64 (val != 0)
- L30 _prototype_ `static U32 rrCtzBytes32(U32 val);` — count trailing zero bytes of U32 (val != 0)
- L31 _prototype_ `static U32 rrCtzBytes64(U64 val);` — count trailing zero bytes of U64 (val != 0)
- L42 _function_ `static RADINLINE U32 rrLowestSetBitMask32(U32 val)` — Mask of lowest set bit in val. Return 0 if val=0, else a value with a single bit set.
- L43 _function_ `static RADINLINE U64 rrLowestSetBitMask64(U64 val)`
- L46 _function_ `static RADINLINE U32 rrMaskThroughToLowestSet32(U32 val)` — Mask up to and including the lowest set bit in val. Returns 0 if val=0.
- L47 _function_ `static RADINLINE U64 rrMaskThroughToLowestSet64(U64 val)`
- L50 _function_ `static RADINLINE U32 rrClearLowestSetBit32(U32 val)` — Clears the lowest set bit in val. Returns 0 if val=0.
- L51 _function_ `static RADINLINE U64 rrClearLowestSetBit64(U64 val)`
- L56 _function_ `static RADINLINE U32 rrClz32(U32 val)` — GCC-esque compilers just provide these built-ins everywhere.
- L57 _function_ `static RADINLINE U32 rrClz64(U64 val)`
- L59 _function_ `static RADINLINE U32 rrCtz32(U32 val)`
- L60 _function_ `static RADINLINE U32 rrCtz64(U64 val)`
- L62 _macro_ `#define SYNTHESIZE_BYTE_FUNCS`
- L69 _macro_ `#define SYNTHESIZE_ALL` — Don't have CLZ or anything similar here, use fall-back.
- L165 _function_ `static RADINLINE U32 rrClzBytes32(U32 val)` — Count leading/trailing zero bytes Same as the bit funcs, behavior for val=0 is not specified!
- L166 _function_ `static RADINLINE U32 rrClzBytes64(U64 val)`
- L168 _function_ `static RADINLINE U32 rrCtzBytes32(U32 val)`
- L169 _function_ `static RADINLINE U32 rrCtzBytes64(U64 val)`
