# NoModule / _nomodule__Runtime__Source__Runtime__BinkAudioDecoder__SDK

- module root: `.`
- headers: 20; symbols: 744
- symbol kinds: function=27, macro=573, member=45, prototype=43, struct=10, typedef=38, variable=8

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Include/binka_ue_decode.h` (Other)


#### struct `UEBinkAudioDecodeInterface`  
`typedef struct UEBinkAudioDecodeInterface`  
_L63-69_
- L65 _public member_ `DecodeMemoryFnType* MemoryFn;`
- L66 _public member_ `DecodeOpenFnType* OpenFn;`
- L67 _public member_ `DecodeFnType* DecodeFn;`
- L68 _public member_ `DecodeResetStartFrameFnType* ResetStartFn;`

#### Free symbols / members of external scopes

- L41 _macro_ `#define BINK_UE_DECODER_EXTRA_INPUT_SPACE 72` — with invalid data, we can read past the InputBuffer during parsing.
- L46 _macro_ `#define BINK_UE_DECODER_END_INPUT_SPACE 16` — with _normal_ data, we can read past the InputBuffer by 16 bytes due to vector bit decoding. It's highly unlikely that it reads that far, however _some_ amount of reading is all but certain.
- L51 _typedef_ `typedef uint32_t DecodeMemoryFnType(uint32_t rate, uint32_t chans);` — For the given rate and channels, this is the memory required for the decoder structure. Max 2 channels. Rates above 48000 are pretty useless as high freqs are crushed.
- L54 _typedef_ `typedef uint32_t DecodeOpenFnType(void* BinkAudioDecoderMemory, uint32_t rate, uint32_t chans, bool interleave_output, bool is_bink_audio_2);` — Initialize the decoder, returns 0 on invalid parameters. Unreal should always be encoding bink_audio_2
- L58 _typedef_ `typedef uint32_t DecodeFnType(void* BinkAudioDecoderMemory, uint8_t* OutputBuffer, uint32_t OutputBufferLen, uint8_t const** InputBuffer, uint8_t const* InputBufferEnd);` — Decode a single block. InputBuffer is updated with the amount of compressed data consumed for the block. Output is 16 bit pcm, interleaved if OpenFn() specified interleave_output.
- L61 _typedef_ `typedef void DecodeResetStartFrameFnType(void* BinkAudioDecoderMemory);` — Call this when seeking/looping, this clears the overlap buffers.
- L69 _typedef_ `} UEBinkAudioDecodeInterface;`
- L71 _prototype_ `UEBinkAudioDecodeInterface* UnrealBinkAudioDecodeInterface();`
- L75 _macro_ `#define BinkAudioDecodeOutputMaxSize() ( 2048 * sizeof(int16_t) * 2 ) // 2 is channels` — what is the maximum data that can be touched of the output for ANY Bink file OutputBufferLen never needs to be larger than this for 1 block.

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Include/binka_ue_encode.h` (Other)


#### Free symbols / members of external scopes

- L5 _typedef_ `typedef void* BAUECompressAllocFnType(uintptr_t ByteCount);`
- L6 _typedef_ `typedef void BAUECompressFreeFnType(void* Ptr);`
- L8 _macro_ `#define BINKA_COMPRESS_SUCCESS 0`
- L9 _macro_ `#define BINKA_COMPRESS_ERROR_CHANS 1`
- L10 _macro_ `#define BINKA_COMPRESS_ERROR_SAMPLES 2`
- L11 _macro_ `#define BINKA_COMPRESS_ERROR_RATE 3`
- L12 _macro_ `#define BINKA_COMPRESS_ERROR_QUALITY 4`
- L13 _macro_ `#define BINKA_COMPRESS_ERROR_ALLOCATORS 5`
- L14 _macro_ `#define BINKA_COMPRESS_ERROR_OUTPUT 6`
- L15 _macro_ `#define BINKA_COMPRESS_ERROR_SEEKTABLE 7`
- L16 _macro_ `#define BINKA_COMPRESS_ERROR_SIZE 8`
- L18 _macro_ `#define BINKA_MAX_CHANS_STR TEXT("16") // (8*2) MAX_STREAMS stereo`
- L19 _macro_ `#define BINKA_MIN_RATE_STR TEXT("2 khz")`
- L20 _macro_ `#define BINKA_MAX_RATE_STR TEXT("256 khz")`
- L36 _prototype_ `uint8_t UECompressBinkAudio( void* PcmData, uint32_t PcmDataLen, uint32_t PcmRate, uint8_t PcmChannels, uint8_t Quality, uint8_t GenerateSeekTable, uint16_t SeekTableMaxEntries, BAUECompressAllocFnType* MemAlloc, BAUECompressFreeFnType* MemFree, void** OutData, uint32_t* OutDataLen);` — Compresses a bink audio _file_. This is distinct from _blocks_, which is what binka_ue_decode handles. Compresses up to 16 channels. Sample rates above 48000 technically supported however it doesn't really add anything. Quality is between 0-9, with 0 being high quality. Below 4 is pretty bad. PcmData should be interleaved 16 bit pcm data. PcmDataLen is in bytes. OutData will be filled with a buffer allocated by MemAlloc that contains the compressed file data. SeekTableMaxEntries is used to cap the amount of disk space used on the seek table. Historically this has been capped at 4k, or 8k of data. If GenerateSeekTable is set, this should be at least 1k or so to be useful.

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Include/binka_ue_file_header.h` (Other)


#### struct `BinkAudioFileHeader`  
`struct BinkAudioFileHeader`  
_L10-41_
- L12 _public member_ `uint32 tag;` — UEBA
- L13 _public member_ `uint8 version;`
- L14 _public member_ `uint8 channels;`
- L15 _public member_ `uint16 PADDING;` — unused atm.
- L16 _public member_ `uint32 rate;`
- L17 _public member_ `uint32 sample_count;`
- L21 _public member_ `uint16 max_comp_space_needed;` — the max for a bink audio block - includes all streams, but does _not_ include the block header info.
- L24 _public member_ `uint16 flags;` — unused in UE (holds whether it's BA2 or not, which is always true for UE)
- L27 _public member_ `uint32 output_file_size;` — bytes for the whole file
- L31 _public member_ `uint16 seek_table_entry_count;` — number of encoded seek table entries stored directly after the file header. each one is 16 bits, and is the delta from the last entry.
- L40 _public member_ `uint16 blocks_per_seek_table_entry;` — number of bink audio blocks for a single entry in the seek table. Encoding keeps seek tables under 4k, so larger files will correspondingly have more distance between seek table lookup points. Note that while you could consider each bink audio stream decode a single block, this is referring to the set of low level bink audio blocks for a given timepoint (so for 6 channels, you have 3 low level bink streams, but the set of those 3 is referred to as one block for the purposes of this.)

#### Free symbols / members of external scopes

- L6 _typedef_ `typedef uint32_t uint32;`
- L7 _typedef_ `typedef uint16_t uint16;`
- L8 _typedef_ `typedef uint8_t uint8;`
- L43 _macro_ `#define BLOCK_HEADER_MAGIC 0x9999`
- L45 _function_ `static bool BinkAudioBlockSize(uint32 header_max_comp_space_needed, uint8 const* input_reservoir, uint32 input_reservoir_len, uint32* out_block_size)`
- L89 _macro_ `#define BINK_AUDIO_BLOCK_VALID 0 // The buffer can be passed to Bink.`
- L90 _macro_ `#define BINK_AUDIO_BLOCK_INCOMPLETE 1 // The buffer looks good but needs more data`
- L91 _macro_ `#define BINK_AUDIO_BLOCK_INVALID 2 // Buffer consistency checks failed.`
- L92 _function_ `static uint8 BinkAudioValidateBlock(uint32 header_max_comp_space_needed, uint8 const* input_reservoir, uint32 input_reservoir_len)`
- L151 _function_ `static void BinkAudioCrackBlock(uint8 const* input_reservoir, uint8 const** out_block_start, uint8 const** out_block_end, uint32* out_trim_to_sample_count)` — input_reservoir MUST have passed BinkAudioValidateBlock

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/binka_ue_decode_test_data_in.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define BinkBlocksSize 6940`
- L6 _variable_ `unsigned char static const BinkBlocksData[BinkBlocksSize]={ 132, 1,168,126,160,161, 35,220,229,165,130,161, 1,177,160,128,112,176,176 ,160,176,160,128,160,112,112, 80,112, 96, 80,128,240, 16,146, 69, 0,104 , 94,232,166, 5,154,229,114, 75, 4, 74,186, 33,204, 73,125, 96,216,211 , 33,133, 41,205, 70,189,100, 78,160, 57, 96,222,150, 75,168,208,100,136 ,211, 76, 41, 52,102,144,200,145, 8, 1,145,132,112, 80,152, 2, 68, 0 ,168,242,104, 2, 65, 76, 49, 66, 52,154,101,176,162,155, 44, 65, 26,191 , 75,178, 4,176, 73,101, 86,201, 12, 82,158,164, 36,196, 10, 6,193,171 ,157, 75,158, 40,254,202,196,204,114, 3,161, 49,201,156,187, 83,194, 16 , 34,137, 80,213, 32,239,211, 42, 21, 1, 48, 33, 16,205,100,226, 98,180 ,157, 9, 68, 82,105,100, 0, 42,156, 64,102, 46,101,164, 74, 14, 40,154 , 53, 48, 84,228,169,160,137, 39,225,116, 88,139, 89,200,108, 67, 49,146 , 43, 75,120, 53,156, 48, 51, 67,171,146, 10, 64, 73,132, 48, 56,198, 8 ,116, 8, 0,113,117,244,155, 28, 8, 8, 66, 38,240, 33, 76, 46, 4,224 , 41,196, 2,208, 33, 46, 4, 25, 35,123, 72,199,128,161, 5, 32,216, 33 , 65, 83,225,216, 3,240,185,193, 0, 0,192, 67, 16,192, 48, 96, 81, 96 , 9, 16,184, 24, 24, 2, 22,208, 37,128,140, 22, 70, 1,129,162,128, 5 , 64, 74,124, 0, 49, 6, 12, 0,128, 18,176, 24, 12,128, 30, 32, 8, 0 ,131, 3,243, 24, 3,128, 21, 4, 64, 65,112, 2, 10,192,130, 0, 12, 24 , 3, 0,232,209, 2,160, 0, 22,139, 6, 64, 14, 0, 0, 98,236,131, 12 ,128, 37, 8,154, 0,112, 0, 0, 3,200, 7, 36, 0, 0, 0, 1,216, 8 , 3, 88, 0, 28, 13, 24, 96, 8, 16, 1, ...`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/binka_ue_decode_test_data_out.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define PcmBlocksSize 46080`
- L6 _variable_ `unsigned char static const PcmBlocksData[PcmBlocksSize]={ 16, 0, 14, 0, 13, 0, 14, 0, 15, 0, 15, 0, 13, 0, 12, 0, 16, 0, 22 , 0, 26, 0, 25, 0, 22, 0, 20, 0, 22, 0, 23, 0, 19, 0, 11, 0, 4 , 0, 4, 0, 9, 0, 13, 0, 12, 0, 6, 0, 2, 0, 3, 0, 7, 0, 9 , 0, 6, 0, 2, 0, 2, 0, 5, 0, 9, 0, 10, 0, 8, 0, 7, 0, 8 , 0, 9, 0, 9, 0, 8, 0, 7, 0, 7, 0, 7, 0, 5, 0, 2, 0, 0 , 0, 3, 0, 7, 0, 9, 0, 7, 0, 4, 0, 3, 0, 6, 0, 9, 0, 10 , 0, 7, 0, 5, 0, 4, 0, 4, 0, 5, 0, 3, 0, 1, 0, 1, 0, 2 , 0, 5, 0, 6, 0, 6, 0, 4, 0, 1, 0,255,255,254,255,255,255, 0 , 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0, 1, 0, 1, 0, 2, 0, 3 , 0, 4, 0, 4, 0, 3, 0, 2, 0, 2, 0, 2, 0, 1, 0,254,255,254 ,255, 3, 0, 10, 0, 16, 0, 16, 0, 13, 0, 10, 0, 12, 0, 16, 0, 17 , 0, 14, 0, 12, 0, 12, 0, 15, 0, 16, 0, 14, 0, 10, 0, 9, 0, 14 , 0, 18, 0, 19, 0, 16, 0, 14, 0, 16, 0, 22, 0, 25, 0, 24, 0, 22 , 0, 21, 0, 24, 0, 27, 0, 26, 0, 23, 0, 21, 0, 22, 0, 26, 0, 29 , 0, 30, 0, 30, 0, 30, 0, 32, 0, 34, 0, 33, 0, 31, 0, 29, 0, 29 , 0, 31, 0, 34, 0, 38, 0, 39, 0, 38, 0, 36, 0, 34, 0, 34, 0, 38 , 0, 41, 0, 43, 0, 42, 0, 39, 0, 37, 0, 36, 0, 35, 0, 34, 0, 33 , 0, 32, 0, 33, 0, 35, 0, 34, 0, 31, 0, 26, 0, 23, 0, 22, 0, 23 , 0, 23, 0, 21, 0, 16, 0, 11, 0, 10, 0, 15, 0, 22, 0, 29, 0, 33 , 0, 34, 0, 35, 0, 39, 0, 44, 0, 47, 0, 48, 0, 46, 0, 43, 0, 41 , 0, 39, 0, 35, 0, 27, 0, 18, 0, 9, 0, 4, 0, 4, 0, 6, 0, 10 , 0, 13, 0, 15, 0, 18, 0, 21, 0, 25, 0, 26, 0, 24, 0, 20, 0, 16 , 0, 15, 0, 17, 0, 20, 0, 21, 0, 21, 0, 19, 0, 17, 0, 16, 0, 17 , 0, 18, 0, 20, 0, 22, 0, 24, 0,  ...`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/binkacd.h` (Other)


#### struct `BINKAC_OUT_RINGBUF`  
`typedef struct BINKAC_OUT_RINGBUF`  
_L41-54_
- L43 _public member_ `void * outptr;` — pointer within outstart and outend to write to (after return, contains the new end output ptr)
- L44 _public member_ `void * outstart;`
- L45 _public member_ `void * outend;`
- L47 _public member_ `U32 outlen;` — unused available (starting at outptr, possibly wrapping) - (after return, how many bytes copied)
- L50 _public member_ `U32 eatfirst;` — remove this many bytes from the start of the decompressed data (after return, how many bytes left)
- L53 _public member_ `U32 decoded_bytes;` — from the input stream, how many bytes decoded (usually outlen, unless outlen was smaller than a frame - that is, when not enough room in the ringbuffer)

#### struct `BINKAC_IN`  
`typedef struct BINKAC_IN`  
_L56-60_
- L58 _public member_ `void const * inptr;` — pointer to input data (after return, contains new end input ptr)
- L59 _public member_ `void const * inend;` — end of input buffer (there should be at least BINKACD_EXTRA_INPUT_SPACE bytes after this ptr)

#### Free symbols / members of external scopes

- L4 _macro_ `#define __BINKACDH__`
- L15 _macro_ `#define bamerge(name) RR_STRING_JOIN(name,WRAP_PUBLICS)`
- L16 _macro_ `#define BinkAudioDecompressMemory bamerge(BinkAudioDecompressMemory)`
- L17 _macro_ `#define BinkAudioDecompressOpen bamerge(BinkAudioDecompressOpen)`
- L18 _macro_ `#define BinkAudioDecompress bamerge(BinkAudioDecompress)`
- L19 _macro_ `#define BinkAudioDecompressResetStartFrame bamerge(BinkAudioDecompressResetStartFrame)`
- L20 _macro_ `#define BinkAudioDecompressOutputSize bamerge(BinkAudioDecompressOutputSize)`
- L23 _typedef_ `typedef struct BINKAUDIODECOMP * HBINKAUDIODECOMP;`
- L25 _macro_ `#define BINKACNODEINTERLACE 2`
- L26 _macro_ `#define BINKAC20 4`
- L28 _macro_ `#define BINKACD_EXTRA_INPUT_SPACE 72 // extra padding after inpend, that, given random data, Bink might read past (very unlikely, but possible)`
- L33 _macro_ `#define BINK_UE_DECODER_END_INPUT_SPACE 16` — with _normal_ data, we can read past the InputBuffer by 16 bytes due to vector bit decoding. It's highly unlikely that it reads that far, however _some_ amount of reading is all but certain.
- L36 _prototype_ `RADDEFFUNC U32 RADLINK BinkAudioDecompressMemory( U32 rate, U32 chans, U32 flags );` — how much memory should be allocated for the BinkAudioDecompressOpen mem ptr?
- L39 _prototype_ `RADDEFFUNC U32 RADLINK BinkAudioDecompressOpen( void * mem, U32 rate, U32 chans, U32 flags );` — open and initialize a decompression stream
- L54 _typedef_ `} BINKAC_OUT_RINGBUF;`
- L60 _typedef_ `} BINKAC_IN;`
- L63 _prototype_ `RADDEFFUNC void RADLINK BinkAudioDecompress(void* mem, BINKAC_OUT_RINGBUF * output, BINKAC_IN * compress_input);` — do the decompression - supports linear or ringbuffers (outptr==outstart on non-ring), will clamp, if no room
- L66 _prototype_ `RADDEFFUNC void RADLINK BinkAudioDecompressResetStartFrame(void* mem);` — resets the start flag to prevent blending in the last decoded frame.
- L69 _prototype_ `RADDEFFUNC U32 RADLINK BinkAudioDecompressOutputSize(void* mem);` — how much memory will decompress touch of the output (not how much was output - that's decoded_bytes)
- L72 _macro_ `#define BinkAudioDecompressOutputMaxSize() ( 2048 * sizeof(S16) * 2 ) // 2 is channels` — what is the maximum data that can be touched of the output for ANY Bink file

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/binkace.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define __BINKACEH__`
- L10 _macro_ `#define AUDIOFLOAT F32`
- L13 _macro_ `#define rfmerge3(name,add) name##add`
- L14 _macro_ `#define rfmerge2(name,add) rfmerge3(name,add)`
- L15 _macro_ `#define rfmerge(name) rfmerge2(name,WRAP_PUBLICS)`
- L16 _macro_ `#define BinkAudioCompressOpen rfmerge(BinkAudioCompressOpen)`
- L17 _macro_ `#define BinkAudioCompressLock rfmerge(BinkAudioCompressLock)`
- L18 _macro_ `#define BinkAudioCompressUnlock rfmerge(BinkAudioCompressUnlock)`
- L19 _macro_ `#define BinkAudioCompressClose rfmerge(BinkAudioCompressClose)`
- L27 _typedef_ `typedef struct BINKAUDIOCOMP * HBINKAUDIOCOMP;`
- L29 _typedef_ `typedef void* BinkAudioCompressAllocFnType(UINTa ByteCount);`
- L30 _typedef_ `typedef void BinkAudioCompressFreeFnType(void* Ptr);`
- L33 _macro_ `#define BINKAC20 4 // if set, BINKACNEWFORMAT is assumed` — #define BINKACNEWFORMAT 1
- L35 _prototype_ `RADDEFFUNC HBINKAUDIOCOMP RADLINK BinkAudioCompressOpen(U32 rate,U32 chans, U32 flags, BinkAudioCompressAllocFnType* memalloc, BinkAudioCompressFreeFnType* memfree);`
- L36 _prototype_ `RADDEFFUNC void RADLINK BinkAudioCompressLock(HBINKAUDIOCOMP ba,void**ptr, U32*len);`
- L37 _prototype_ `RADDEFFUNC void RADLINK BinkAudioCompressUnlock(HBINKAUDIOCOMP ba, U32 lossylevel, U32 filled, void** output,U32* outbytes, U32* uncompressedbytesused);`
- L38 _prototype_ `RADDEFFUNC void RADLINK BinkAudioCompressClose(HBINKAUDIOCOMP ba);`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/binkbits.h` (Other)


#### struct `BINKVARBITS`  
`typedef struct BINKVARBITS`  
_L9-9_
- L9 _public member_ `typedef struct BINKVARBITS { void * cur; U32 bits; U32 bitlen; } BINKVARBITS;`
- L9 _public member_ `typedef struct BINKVARBITS { void * cur; U32 bits; U32 bitlen; } BINKVARBITS;`
- L9 _public member_ `typedef struct BINKVARBITS { void * cur; U32 bits; U32 bitlen; } BINKVARBITS;`
- L88 _public member_ `typedef struct BINKVARBITS { void * cur; U64 bits; U32 bitlen; } BINKVARBITS;`
- L88 _public member_ `typedef struct BINKVARBITS { void * cur; U64 bits; U32 bitlen; } BINKVARBITS;`
- L88 _public member_ `typedef struct BINKVARBITS { void * cur; U64 bits; U32 bitlen; } BINKVARBITS;`

#### struct `BINKVARBITS`  
`typedef struct BINKVARBITS`  
_L88-88_
- L9 _public member_ `typedef struct BINKVARBITS { void * cur; U32 bits; U32 bitlen; } BINKVARBITS;`
- L9 _public member_ `typedef struct BINKVARBITS { void * cur; U32 bits; U32 bitlen; } BINKVARBITS;`
- L9 _public member_ `typedef struct BINKVARBITS { void * cur; U32 bits; U32 bitlen; } BINKVARBITS;`
- L88 _public member_ `typedef struct BINKVARBITS { void * cur; U64 bits; U32 bitlen; } BINKVARBITS;`
- L88 _public member_ `typedef struct BINKVARBITS { void * cur; U64 bits; U32 bitlen; } BINKVARBITS;`
- L88 _public member_ `typedef struct BINKVARBITS { void * cur; U64 bits; U32 bitlen; } BINKVARBITS;`

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef struct BINKVARBITS { void * cur; U32 bits; U32 bitlen; } BINKVARBITS;`
- L11 _macro_ `#define BINKBITSLOCALS( name ) void * name##cur; U32 name##bits; U32 name##bitlen`
- L12 _macro_ `#define BinkVarBitsOpen(vb,pointer) { (vb).bits=BINK_LOAD32(pointer); (vb).cur=((char*)pointer)+4; (vb).bitlen = 32; }`
- L17 _macro_ `#define BINK_LOAD32(ptr) ((U32)*((emscripten_align1_int*)(ptr)))`
- L20 _macro_ `#define BINK_LOAD32(ptr) RR_GET32_LE(ptr)`
- L22 _macro_ `#define BINK_LOAD32(ptr) RR_GET32_NATIVE(ptr)`
- L26 _macro_ `#define BinkBitsGet(v,typ,vb,len,mask) \`
- L43 _macro_ `#define MAX_AT_LEAST_BITS 25`
- L46 _macro_ `#define BinkBitsAtLeastStart( vb,len ) \` — load as many bytes as we can each load on little endian (unaligned loads)
- L57 _macro_ `#define BinkBitsAtLeastEnd(vb)`
- L61 _macro_ `#define MAX_AT_LEAST_BITS 32`
- L74 _macro_ `#define BinkBitsAtLeastEnd(vb) \`
- L88 _typedef_ `typedef struct BINKVARBITS { void * cur; U64 bits; U32 bitlen; } BINKVARBITS;`
- L90 _macro_ `#define BINKBITSLOCALS( name ) void * name##cur; U64 name##bits; U32 name##bitlen`
- L91 _macro_ `#define BinkVarBitsOpen(vb,pointer) { (vb).bits=*(U64*)(pointer); (vb).cur=((char*)pointer)+8; (vb).bitlen = 64; }`
- L93 _macro_ `#define BINK_LOAD32 RR_GET32_NATIVE`
- L110 _macro_ `#define MAX_AT_LEAST_BITS 57`
- L126 _macro_ `#define VarBits32Use(vb,len) { (vb).bits >>= (len); (vb).bitlen -= (len); }`
- L128 _macro_ `#define MAX_PEEK 64`
- L132 _macro_ `#define BINKBITSCOPY(name, from) { name##cur = from##cur; name##bits = from##bits; name##bitlen = from##bitlen; }`
- L134 _macro_ `#define BinkBitsInAtLeastPeek(vb) ( vb##bits )`
- L135 _macro_ `#define BinkBitsInAtLeastUse( vb, bl ) { (vb##bits) >>= (bl); (vb##bitlen) -= (bl); }`
- L137 _macro_ `#define BinkBitsPeek(v, typ, vb, len) \`
- L143 _macro_ `#define BinkBitsUse( vb, bl ) { BinkBitsInAtLeastUse( vb, bl ); BinkBitsAtLeastEnd( vb ); }`
- L145 _macro_ `#define BinkVarBitsUse(vb,len) { (vb).bits >>= (len); (vb).bitlen -= (len); }`
- L147 _macro_ `#define VarBitsCopyToBinkBits( local, vb ) local##cur = (vb).cur; local##bits = (vb).bits; local##bitlen = (vb).bitlen;`
- L148 _macro_ `#define BinkBitsCopyToVarBits( vb, local ) { (vb).cur = local##cur; (vb).bits = local##bits; (vb).bitlen = local##bitlen; }`
- L150 _macro_ `#define BinkBitsSizeBytesRoundedToU32( local, base ) ((((((U8*)(local##cur))-((U8*)base))-(local##bitlen/8))+3)&~3)`
- L151 _macro_ `#define BinkVarBitsSizeBytesRoundedToU32( vb, base ) ((((((U8*)((vb).cur))-((U8*)base))-((vb).bitlen/8))+3)&~3)`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/console.h` (Other)


#### Free symbols / members of external scopes

- L32 _function_ `static void console_printf(const char *fmt, ...)`
- L40 _function_ `static void console_init()`
- L41 _function_ `static void console_handleevents()`
- L42 _macro_ `#define CONSOLE_MAIN extern "C" int main(int argc, char** argv)`
- L50 _macro_ `#define CONSOLE_MAIN int main(int argc, char** argv)`
- L51 _function_ `static void console_printf(char const* fmt, ...)`
- L75 _variable_ `static struct termios initial_settings, new_settings;`
- L75 _variable_ `static struct termios initial_settings, new_settings;`
- L76 _variable_ `static int peek_character = -1;`
- L78 _prototype_ `int _kbhit();`
- L79 _function_ `int _kbhit()`
- L99 _prototype_ `int _getch();`
- L100 _function_ `int _getch()`
- L116 _function_ `static void console_cleanup()`
- L135 _macro_ `#define console_printf printf`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/cpu.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define __CPUH__`
- L19 _macro_ `#define CPU_MMX 1`
- L20 _macro_ `#define CPU_3DNOW 2`
- L21 _macro_ `#define CPU_SSE 4`
- L22 _macro_ `#define CPU_SSE2 8`
- L23 _macro_ `#define CPU_SSE3 16`
- L24 _macro_ `#define CPU_SSSE3 32`
- L28 _macro_ `#define CPU_ALTIVEC 1`
- L32 _macro_ `#define CPU_NEON 1`
- L34 _macro_ `#define CPU_check( u, du )`
- L35 _macro_ `#define CPU_clean_up()`
- L38 _macro_ `#define CPU_can_use( has ) ( ( has & CPU_NEON ) == has )`
- L39 _macro_ `#define CPU_can_use_any( has ) ( has & CPU_NEON )`
- L40 _macro_ `#define CPU_features() ( CPU_NEON )`
- L41 _macro_ `#define CPU_ALWAYS_NEON`
- L43 _macro_ `#define CPU_can_use( has ) 0`
- L44 _macro_ `#define CPU_can_use_any( has ) 0`
- L45 _macro_ `#define CPU_features() 0`
- L58 _macro_ `#define rfmerge3(name,add) name##add`
- L59 _macro_ `#define rfmerge2(name,add) rfmerge3(name,add)`
- L60 _macro_ `#define rfmerge(name) rfmerge2(name,WRAP_PUBLICS)`
- L61 _macro_ `#define cpu_features_to_use rfmerge(cpu_features_to_use)`
- L62 _macro_ `#define cpu_features_avail rfmerge(cpu_features_avail)`
- L63 _macro_ `#define CPU_check rfmerge(CPU_check)`
- L64 _macro_ `#define CPU_clear rfmerge(CPU_clear)`
- L68 _variable_ `RADDECLAREDATA S32 cpu_features_to_use;`
- L69 _variable_ `RADDECLAREDATA S32 cpu_features_avail;`
- L71 _macro_ `#define CPU_can_use( has ) ( ( cpu_features_to_use & has ) == has )`
- L72 _macro_ `#define CPU_can_use_any( has ) ( cpu_features_to_use & has )`
- L73 _macro_ `#define CPU_features() ( cpu_features_to_use )`
- L75 _prototype_ `RADDEFFUNC void CPU_check( S32 use, S32 dont_use );`
- L77 _prototype_ `RADDEFFUNC void CPU_clear( void );`
- L81 _macro_ `#define CPU_clean_up() \`
- L109 _macro_ `#define CPU_can_use( has ) 1`
- L110 _macro_ `#define CPU_can_use_any( has ) 1`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/crsfade.inl` (Other)


#### Free symbols / members of external scopes

- L14 _macro_ `#define CallCrossFade CrossFadeSSE2`
- L17 _macro_ `#define CallCrossFade CrossFadeDispatch` — x86 32-bit try sse or fallback to mmx
- L19 _function_ `static void CrossFadeMMX(S16* outp,S16* overlap, U32 windowsize, S32 windowshift)`
- L77 _prototype_ `static void CrossFadeSSE2(S16* outp,S16* overlap, U32 windowsize, S32 windowshift);`
- L78 _function_ `static void CrossFadeDispatch(S16* outp,S16* overlap, U32 windowsize, S32 windowshift)`
- L92 _function_ `static void CrossFadeSSE2(S16* outp,S16* overlap, U32 windowsize, S32 windowshift)`
- L148 _macro_ `#define CallCrossFade CrossFadeNeon`
- L152 _function_ `static void CrossFadeNeon(S16* outp,S16* overlap, U32 windowsize, S32 windowshift)`
- L199 _macro_ `#define CallCrossFade CrossFade` — this is just emscripten currently
- L200 _function_ `static void CrossFade(S16* outp,S16* overlap, U32 windowsize, S32 windowshift)`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/egttypes.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define __RADTYPESH__`
- L5 _macro_ `#define __EGTTYPESH__`
- L6 _macro_ `#define __RADRR_COREH__ // block old rr_core`
- L61 _macro_ `#define RADDEFFUNC extern "C"`
- L62 _macro_ `#define RADDEFSTART extern "C" {`
- L63 _macro_ `#define RADDEFEND }`
- L64 _macro_ `#define RADDEFAULT( val ) =val`
- L66 _macro_ `#define RADDEFFUNC`
- L67 _macro_ `#define RADDEFSTART`
- L68 _macro_ `#define RADDEFEND`
- L69 _macro_ `#define RADDEFAULT( val )`
- L74 _macro_ `#define RR_STRINGIZE( L ) #L` — preprocessor string stuff
- L75 _macro_ `#define RR_DO_MACRO( M, X ) M(X)`
- L76 _macro_ `#define RR_STRINGIZE_DELAY( X ) RR_DO_MACRO( RR_STRINGIZE, X )`
- L78 _macro_ `#define RR_STRING_JOIN(arg1, arg2) RR_STRING_JOIN_DELAY(arg1, arg2)`
- L79 _macro_ `#define RR_STRING_JOIN_DELAY(arg1, arg2) RR_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L80 _macro_ `#define RR_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L83 _macro_ `#define RR_PLATFORM_PATH_STR( plat, file ) RR_STRINGIZE_DELAY( RR_STRING_JOIN( plat, file ) )` — makes "plat/plat_file"
- L96 _macro_ `#define __RADANDROID__ 1`
- L97 _macro_ `#define __RADDETECTED__ __RADANDROID__`
- L101 _macro_ `#define __RADQNX__ 2`
- L102 _macro_ `#define __RADDETECTED__ __RADQNX__`
- L113 _macro_ `#define RAD_WINAPI_IS_APP (!WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))`
- L115 _macro_ `#define __RADWINRTAPI__`
- L116 _macro_ `#define __RADWINRT__ 13`
- L117 _macro_ `#define __RADDETECTED__ __RADWINRT__`
- L120 _macro_ `#define RAD_WINAPI_IS_APP 0`
- L125 _macro_ `#define __RADNT__ 14` — if we aren't WinRT, then we are plain old NT
- L126 _macro_ `#define __RADDETECTED__ __RADNT__`
- L133 _macro_ `#define __RADIPHONE__ 15`
- L134 _macro_ `#define __RADIPHONESIM__ 16`
- L135 _macro_ `#define __RADDETECTED__ __RADIPHONESIM__`
- L138 _macro_ `#define __RADDETECTED__ __RADIPHONE__`
- L140 _macro_ `#define __RADMAC__ 17`
- L141 _macro_ `#define __RADDETECTED__ __RADMAC__`
- L145 _macro_ `#define __RADIOS__ 18`
- L148 _macro_ `#define __RADTVOS__ 19`
- L151 _macro_ `#define __RADWATCHOS__ 20`
- L156 _macro_ `#define __RADEMSCRIPTEN__ 22`
- L157 _macro_ `#define __RADDETECTED__ __RADEMSCRIPTEN__`
- L162 _macro_ `#define __RADLINUX__ 3`
- L163 _macro_ `#define __RADDETECTED__ __RADLINUX__`
- L168 _macro_ `#define __RADUNKNOWN__ 99` — this is the catch all, when you aren't building internally at rad
- L169 _macro_ `#define __RADDETECTED__ __RADUNKNOWN__`
- L182 _macro_ `#define __RAD32__ // we have no non-at-least-32-bit cpus any more`
- L185 _macro_ `#define __RADARM__ 1`
- L186 _macro_ `#define __RADDETECTEDPROC__ __RADARM__`
- L187 _macro_ `#define __RADLITTLEENDIAN__`
- L189 _macro_ `#define __RADNEON__`
- L192 _macro_ `#define __RADSOFTFP__`
- L196 _macro_ `#define __RADX86__ 2`
- L199 _macro_ `#define __RADMMX__` — only use mmx on PC, Win, Linux - not iphone sim!
- L201 _macro_ `#define __RADDETECTEDPROC__ __RADX86__`
- L206 _macro_ `#define __RADX64__ 3`
- L210 _macro_ `#define __RADDETECTEDPROC__ __RADX64__`
- L214 _macro_ `#define __RADPPC__ 4`
- L215 _macro_ `#define __RADALTIVEC__`
- L216 _macro_ `#define __RADDETECTEDPROC__ __RADPPC__`
- L217 _macro_ `#define __RADBIGENDIAN__`
- L221 _macro_ `#define __RADARM64__ 6`
- L222 _macro_ `#define __RADDETECTEDPROC__ __RADARM64__`
- L227 _macro_ `#define __RADDETECTEDPROC__`
- L236 _macro_ `#define __RAD64__`
- L237 _macro_ `#define __RAD64REGS__ // need to set this for platforms that aren't 64-bit, but have 64-bit regs (old consoles)`
- L251 _macro_ `#define RADEXPFUNC RADDEFFUNC` — if we are in a static lib, or exports are off, or if we are in an EXE we asked for no exe exports (or imports) then EXPFUNC is just a normal function
- L255 _macro_ `#define RADEXPFUNC RADDEFFUNC RADDLLEXPORTDLL`
- L257 _macro_ `#define RADEXPFUNC RADDEFFUNC RADDLLIMPORTDLL`
- L262 _macro_ `#define RADRESTRICT __restrict`
- L263 _macro_ `#define RADSTRUCT struct __attribute__((__packed__))`
- L265 _macro_ `#define RADLINK`
- L266 _macro_ `#define RADEXPLINK`
- L267 _macro_ `#define RADDLLEXPORTDLL __attribute__((visibility("default")))`
- L268 _macro_ `#define RADDLLIMPORTDLL`
- L276 _macro_ `#define RADEXPLINK RADLINK`
- L277 _macro_ `#define RADDLLEXPORTDLL`
- L286 _macro_ `#define RADLINK __attribute__((cdecl))`
- L287 _macro_ `#define RADEXPLINK __attribute__((cdecl))`
- L299 _macro_ `#define __RADWIN__`
- L304 _macro_ `#define RADRESTRICT` — vc6 and older
- L305 _macro_ `#define __RADNOVARARGMACROS__`
- L307 _macro_ `#define RADSTRUCT struct`
- L309 _macro_ `#define RADLINK __stdcall`
- L310 _macro_ `#define RADEXPLINK __stdcall`
- L312 _macro_ `#define RADDLLEXPORTDLL __declspec(dllexport)`
- L318 _macro_ `#define RADDLLIMPORTDLL __declspec(dllimport)` — normal win32 dll import
- L337 _macro_ `#define __RADMACAPI__`
- L348 _macro_ `#define __RADMACH__`
- L363 _macro_ `#define __RADCARBON__`
- L375 _macro_ `#define RADEXPLINK EMSCRIPTEN_KEEPALIVE`
- L385 _macro_ `#define RADINLINE __inline`
- L387 _macro_ `#define RADINLINE inline`
- L396 _macro_ `#define RR_NUMBERNAME(name) RR_STRING_JOIN(name,__COUNTER__)`
- L398 _macro_ `#define RR_NUMBERNAME(name) RR_STRING_JOIN(name,__LINE__)`
- L406 _macro_ `#define RR_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L408 _macro_ `#define RR_COMPILER_ASSERT_UNUSED`
- L411 _macro_ `#define RR_COMPILER_ASSERT(exp) typedef char RR_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] RR_COMPILER_ASSERT_UNUSED`
- L418 _macro_ `#define RAD_S8 signed char`
- L419 _macro_ `#define RAD_U8 unsigned char`
- L420 _macro_ `#define RAD_U16 unsigned short`
- L421 _macro_ `#define RAD_S16 signed short`
- L424 _macro_ `#define RAD_U32 unsigned int`
- L425 _macro_ `#define RAD_S32 signed int`
- L429 _macro_ `#define RAD_SINTa __w64 signed __int64`
- L430 _macro_ `#define RAD_UINTa __w64 unsigned __int64`
- L433 _macro_ `#define RAD_UINTa unsigned long long` — non-vc.net compiler or /Wp64 turned off
- L434 _macro_ `#define RAD_SINTa signed long long`
- L443 _macro_ `#define RAD_SINTa __w64 signed long`
- L444 _macro_ `#define RAD_UINTa __w64 unsigned long`
- L448 _macro_ `#define RAD_SINTa signed long`
- L449 _macro_ `#define RAD_UINTa unsigned long`
- L451 _macro_ `#define RAD_SINTa signed int`
- L452 _macro_ `#define RAD_UINTa unsigned int`
- L457 _macro_ `#define RAD_F32 float`
- L458 _macro_ `#define RAD_F64 double`
- L461 _macro_ `#define RAD_U64 unsigned __int64`
- L462 _macro_ `#define RAD_S64 signed __int64`
- L464 _macro_ `#define RAD_U64 unsigned long long`
- L465 _macro_ `#define RAD_S64 signed long long`
- L475 _macro_ `#define S8_DEFINED`
- L476 _typedef_ `typedef RAD_S8 S8;`
- L480 _macro_ `#define U8_DEFINED`
- L481 _typedef_ `typedef RAD_U8 U8;`
- L485 _macro_ `#define S16_DEFINED`
- L486 _typedef_ `typedef RAD_S16 S16;`
- L490 _macro_ `#define U16_DEFINED`
- L491 _typedef_ `typedef RAD_U16 U16;`
- L495 _macro_ `#define S32_DEFINED`
- L496 _typedef_ `typedef RAD_S32 S32;`
- L500 _macro_ `#define U32_DEFINED`
- L501 _typedef_ `typedef RAD_U32 U32;`
- L505 _macro_ `#define S64_DEFINED`
- L506 _typedef_ `typedef RAD_S64 S64;`
- L510 _macro_ `#define U64_DEFINED`
- L511 _typedef_ `typedef RAD_U64 U64;`
- L515 _macro_ `#define F32_DEFINED`
- L516 _typedef_ `typedef RAD_F32 F32;`
- L520 _macro_ `#define F64_DEFINED`
- L521 _typedef_ `typedef RAD_F64 F64;`
- L525 _macro_ `#define SINTa_DEFINED`
- L526 _typedef_ `typedef RAD_SINTa SINTa;`
- L530 _macro_ `#define UINTa_DEFINED`
- L531 _typedef_ `typedef RAD_UINTa UINTa;`
- L535 _macro_ `#define RRBOOL_DEFINED`
- L536 _typedef_ `typedef S32 rrbool;`
- L537 _typedef_ `typedef S32 RRBOOL;`
- L544 _macro_ `#define S8 RAD_S8`
- L549 _macro_ `#define U8 RAD_U8`
- L554 _macro_ `#define S16 RAD_S16`
- L559 _macro_ `#define U16 RAD_U16`
- L564 _macro_ `#define S32 RAD_S32`
- L569 _macro_ `#define U32 RAD_U32`
- L574 _macro_ `#define S64 RAD_S64`
- L579 _macro_ `#define U64 RAD_U64`
- L584 _macro_ `#define F32 RAD_F32`
- L589 _macro_ `#define F64 RAD_F64`
- L594 _macro_ `#define SINTa RAD_SINTa`
- L599 _macro_ `#define UINTa RAD_UINTa`
- L604 _macro_ `#define rrbool S32`
- L605 _macro_ `#define RRBOOL S32`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/popmal.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define __POPMALH__`
- L9 _macro_ `#define Round32( num ) ( ( ( num ) + 31 ) & ~31 )`
- L11 _macro_ `#define PushMallocBytesForXPtrs( X ) ( ( X * sizeof(void*) ) + ( X * sizeof(U64) ) + 64 )`
- L15 _macro_ `#define rfmerge3(name,add) name##add`
- L16 _macro_ `#define rfmerge2(name,add) rfmerge3(name,add)`
- L17 _macro_ `#define rfmerge(name) rfmerge2(name,WRAP_PUBLICS)`
- L18 _macro_ `#define pushmallocinit rfmerge(pushmallocinit)`
- L19 _macro_ `#define pushmalloc rfmerge(pushmalloc)`
- L20 _macro_ `#define pushmalloco rfmerge(pushmalloco)`
- L21 _macro_ `#define popmalloctotal rfmerge(popmalloctotal)`
- L22 _macro_ `#define popmalloc rfmerge(popmalloc)`
- L26 _prototype_ `RADDEFFUNC void RADLINK pushmallocinit(void * base,U32 num_ptrs);`
- L27 _prototype_ `RADDEFFUNC void RADLINK pushmalloc( void * base, void * ptr, U64 amt );`
- L30 _prototype_ `RADDEFFUNC void RADLINK pushmalloco(void* base, void * ptr,U64 amt);` — ptr is an offset within the final allocation that will be popped (for allocating ptrs within a structure that you allocate with popmalloc)
- L32 _prototype_ `RADDEFFUNC U64 RADLINK popmalloctotal( void * base );`
- L34 _prototype_ `RADDEFFUNC void * RADLINK popmalloc( void * base, U64 amt, void* (*allocator)(UINTa bytes));`
- L36 _macro_ `#define popfree(ptr, memfree) memfree(ptr)`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/radfft.h` (Other)


#### struct `rfft_complex`  
`typedef struct rfft_complex`  
_L31-35_
- desc: Complex numbers are returned in this form
- L33 _public member_ `F32 re;` — real part
- L34 _public member_ `F32 im;` — imaginary part

#### Free symbols / members of external scopes

- L3 _macro_ `#define RADFFT_H`
- L8 _macro_ `#define RADFFT_ALIGN 32`
- L9 _macro_ `#define RADFFT_AVX // We know it's always there, might as well use it!`
- L11 _macro_ `#define RADFFT_ALIGN 16`
- L15 _macro_ `#define rfmerge3(name,add) name##add`
- L16 _macro_ `#define rfmerge2(name,add) rfmerge3(name,add)`
- L17 _macro_ `#define rfmerge(name) rfmerge2(name,WRAP_PUBLICS)`
- L18 _macro_ `#define radfft_init rfmerge(radfft_init)`
- L19 _macro_ `#define radfft_cfft rfmerge(radfft_cfft)`
- L20 _macro_ `#define radfft_cifft rfmerge(radfft_cifft)`
- L21 _macro_ `#define radfft_rfft rfmerge(radfft_rfft)`
- L22 _macro_ `#define radfft_rifft rfmerge(radfft_rifft)`
- L23 _macro_ `#define radfft_dct rfmerge(radfft_dct)`
- L24 _macro_ `#define radfft_idct rfmerge(radfft_idct)`
- L25 _macro_ `#define radfft_idct_to_S16 rfmerge(radfft_idct_to_S16)`
- L26 _macro_ `#define radfft_idct_to_S16_stereo_interleave rfmerge(radfft_idct_to_S16_stereo_interleave)`
- L35 _typedef_ `} rfft_complex;`
- L38 _prototype_ `RADDEFFUNC void RADLINK radfft_init();` — Initialize. Call this first!
- L47 _prototype_ `RADDEFFUNC void RADLINK radfft_cfft(rfft_complex out[], rfft_complex const in[], UINTa N);` — Complex FFT. Computes out[k] = sum_{j=0}^{N-1} in[k] * exp(-i*2*pi/N * (j*k)) This is the typical FFT definition (negative sign in the exponential). N must be a power of 2, "in" and "out" must be aligned to RADFFT_ALIGN.
- L58 _prototype_ `RADDEFFUNC void RADLINK radfft_cifft(rfft_complex out[], rfft_complex const in[], UINTa N);` — Complex IFFT. Computes out[k] = sum_{j=0}^{N-1} in[k] * exp(i*2*pi/N * (j*k)) This is the typical IFFT definition (positive sign in the exponential). cifft(fft(x)) = x * N N must be a power of 2, "in" and "out" must be aligned to RADFFT_ALIGN.
- L75 _prototype_ `RADDEFFUNC void RADLINK radfft_rfft(rfft_complex out[], F32 const in[], UINTa N);` — Real FFT of N elements in[0..N-1]. This computes (except for out[0] and out[N/2], see below!) out[k] = sum_{j=0}^{N-1} in[j] * exp(i*2*pi/N * (j*k)) Engineers often use the opposite sign convention (-i instead of i in the "exp"), and so does the "cfft" in here (sorry). We use this convention here because the code this replaced used it. Returns the first half of the N complex FFT coeffs in out[0..N/2-1]. The DC bin out[0] is always real for a real FFT. We use the imaginary part of out[0] to hold the (also always real) Nyquist bin that would otherwise be in out[N/2]. N must be a power of 2, "in" and "out" must be aligned to RADFFT_ALIGN.
- L96 _prototype_ `RADDEFFUNC void RADLINK radfft_rifft(F32 out[], rfft_complex in[], UINTa N);` — Real IFFT matching "radfft_rfft". This computes out[k] = (1/2) * sum_{j=0}^{N-1} in'[j] * exp(-i*2*pi/N * (j*k)) where in'[0]   = real(in[0]) in'[N/2] = imag(in[0]) in'[k]   = in[k],         1 <= k < N/2 in'[N-k] = conj(in[k]),   1 <= k < N/2 i.e. "in'" is "in" expanded from N/2 to N values with conjugate (Hermitian) symmetry (whew). Same comment as for "rfft" applies: this is the opposite exponent sign convention from what's typical in engineering, but it matches the code we're replacing. With these rules, we have rifft(rfft(x)) == (N/2) * x N must be a power of 2, "in" and "out" must be aligned to RADFFT_ALIGN.
- L108 _prototype_ `RADDEFFUNC void RADLINK radfft_dct(F32 out[], F32 in[], UINTa N);` — DCT-II Computes the type-II discrete cosine transform ("the" DCT) of "in": out[k] = sum_{j=0}^{N-1} in[j] * cos(pi/N * (j+0.5)*k) Input data is in in[0..N-1]; output is written to out[0..N-1]. The input data is destroyed. N must be a power of 2, "in" and "out" must be aligned to RADFFT_ALIGN.
- L131 _prototype_ `RADDEFFUNC void RADLINK radfft_idct(F32 out[], F32 in[], UINTa N);` — DCT-III Computes the type-III discrete cosine transform ("the" inverse DCT) of "in": out[k] = sum_{j=0}^{N-1} in[j] * cos(pi/N * j*(k+0.5)) Input data is in in[0..N-1]; output is written to out[0..N-1]. The input data is destroyed. Note that this is using the standard normalization which means it's only *almost* an inverse of "dct"; to be precise, the inverse of dct(data, work, N) is data[0] *= 0.5f; idct(data, work, N); // scale data by 2/N N must be a power of 2, "in" and "out" must be aligned to RADFFT_ALIGN.
- L132 _prototype_ `RADDEFFUNC void RADLINK radfft_idct_to_S16(S16 outs16[], F32 scale, F32 tmp[], F32 in[], UINTa N);`
- L133 _prototype_ `RADDEFFUNC void RADLINK radfft_idct_to_S16_stereo_interleave(S16 outs16[], S16 left[], F32 scale, F32 tmp[], F32 in[], UINTa N);`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/radfft_sse3.inl` (Other)


#### Free symbols / members of external scopes

- L9 _function_ `static void RADFFT_SSE3_PREFIX(rfpost)(rfft_complex out[], UINTa kEnd, UINTa N4)` — SSE3 real FFT post-pass.
- L65 _function_ `static void RADFFT_SSE3_PREFIX(ripre)(rfft_complex out[], UINTa kEnd, UINTa N4)` — SSE3 real IFFT pre-pass.
- L123 _function_ `static void RADFFT_SSE3_PREFIX(cfpass)(rfft_complex data[], PlanElement const *plan, UINTa Nover4)` — SSE3 complex forward conjugate split-radix reduction pass. This is the main workhorse inner loop for FFTs.
- L169 _function_ `static void RADFFT_SSE3_PREFIX(cipass)(rfft_complex data[], PlanElement const *plan, UINTa Nover4)` — SSE3 complex inverse conjugate split-radix reduction pass. This is the main workhorse inner loop for IFFTs.
- L214 _function_ `static void RADFFT_SSE3_PREFIX(dct2_modulate)(F32 out[], F32 const in[], UINTa N, UINTa Nlast, rfft_complex const *twiddle)`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/radfft_tables.inl` (Other)


#### Free symbols / members of external scopes

- L2 _typedef_ `typedef int fft_assert_MaxN[(kMaxN == 2048) ? 1 : -1];`
- L3 _typedef_ `typedef int fft_assert_LeafN[(kLeafN == 4) ? 1 : -1];`
- L5 _macro_ `#define s_twiddles ((rfft_complex const *)radfft_s_twiddles_data)`
- L6 _prototype_ `FFTTABLE(U32, radfft_s_twiddles_data[2048]) =`
- L137 _macro_ `#define s_dct_twiddles ((rfft_complex const *)radfft_s_dct_twiddles_data)`
- L138 _prototype_ `FFTTABLE(U32, radfft_s_dct_twiddles_data[3072]) =`
- L333 _macro_ `#define s_permute ((Index const *)radfft_s_permute)`
- L334 _prototype_ `FFTTABLE(Index, radfft_s_permute[1024]) =`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/radmath.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define __RADMATHH__`
- L9 _macro_ `#define mult64anddiv( a, b, c ) ( (U32) ( ( ( (U64) a ) * ( (U64) b ) ) / ( (U64) c ) ) )`
- L10 _macro_ `#define mult64andshift( a, b, c ) ( (U32) ( ( ( (U64) a ) * ( (U64) b ) ) >> ( (U64) c ) ) )`
- L11 _macro_ `#define radabs abs`
- L19 _macro_ `#define radatan2( val1, val2 ) ((float)atan2f ( (float)val1, (float)val2) )` — We use the floating point version of everything and have casts around everything to ensure we don't accidentally have an expression evaluate as double on one platform and float on the other. This was due to previously using e.g. sqrt on one platform and sqrtf on another, but there's no reason to _not_ have these casts.
- L20 _macro_ `#define radpow( val1, val2 ) ((float)powf ( (float)val1, (float)val2) )`
- L21 _macro_ `#define radfsqrt( val ) ((float)sqrtf ( (float)val) )`
- L22 _macro_ `#define radlog10( val ) ((float)log10f ( (float)val) )`
- L23 _macro_ `#define radexp( val ) ((float)expf ( (float)val) )`
- L24 _macro_ `#define radfabs( val ) ((float)fabsf ( (float)val) )`
- L25 _macro_ `#define radfloor( val ) ((float)floorf ( (float)val) )`
- L27 _prototype_ `float ranged_log_0p05_to_0p5(float x);`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/rrCore.h` (Other)


#### Free symbols / members of external scopes

- L3 _macro_ `#define __RADRR_CORE2H__`
- L10 _macro_ `#define RAD_PTRBITS 64`
- L11 _macro_ `#define RAD_PTRBYTES 8`
- L12 _macro_ `#define RAD_TWOPTRBYTES 16`
- L14 _macro_ `#define RAD_PTRBITS 32`
- L15 _macro_ `#define RAD_PTRBYTES 4`
- L16 _macro_ `#define RAD_TWOPTRBYTES 8`
- L20 _macro_ `#define RR_BREAK() __builtin_trap()`
- L21 _macro_ `#define RAD_GUARANTEED_SSE3 // always sse3 on mac`
- L22 _macro_ `#define RAD_USES_SSE3 // don't need any special markup for sse3 on mac`
- L23 _macro_ `#define RAD_USES_SSSE3 // don't need any special markup for ssse3 on mac`
- L27 _macro_ `#define RAD_GUARANTEED_SSE3 // simulator has sse3`
- L28 _macro_ `#define RAD_USES_SSE3 // don't need any special markup for sse3 on sim`
- L42 _macro_ `#define __RAD64REGS__`
- L44 _macro_ `#define RR_BREAK __debugbreak`
- L63 _macro_ `#define RAD_UINTr RAD_U64`
- L64 _macro_ `#define RAD_SINTr RAD_S64`
- L66 _macro_ `#define RAD_UINTr RAD_U32`
- L67 _macro_ `#define RAD_SINTr RAD_S32`
- L76 _macro_ `#define RRSTRIPPABLE __declspec(selectany)`
- L77 _macro_ `#define RRSTRIPPABLEPUB __declspec(selectany)`
- L79 _macro_ `#define RRSTRIPPABLE static`
- L80 _macro_ `#define RRSTRIPPABLEPUB`
- L88 _macro_ `#define RAD_ALIGN(type,var,num) type __declspec(align(num)) var`
- L93 _macro_ `#define RAD_USES_SSE3 // vs2008+ can compile SSE3 with no special markup`
- L96 _macro_ `#define RAD_USES_SSSE3 // vs2008+ can compile SSSE3 with no special markup`
- L99 _macro_ `#define RADFORCEINLINE __forceinline`
- L100 _macro_ `#define RADASSUME(exp) __assume(exp)`
- L104 _macro_ `#define RAD_ALIGN(type,var,num) type __attribute__ ((aligned (num))) var`
- L106 _macro_ `#define RADFORCEINLINE inline`
- L108 _macro_ `#define RADFORCEINLINE inline __attribute((always_inline))`
- L112 _macro_ `#define RAD_USES_SSE3 __attribute__((target("sse3")))`
- L115 _macro_ `#define RAD_USES_SSSE3 __attribute__((target("ssse3")))`
- L119 _macro_ `#define RADASSUME(exp) __builtin_assume(exp)`
- L121 _macro_ `#define RADASSUME(exp) RAD_STATEMENT_WRAPPER( if ( ! (exp) ) __builtin_unreachable(); )`
- L133 _macro_ `#define __RAD_GCC_VERSION__ (__GNUC__ * 10000 \`
- L140 _macro_ `#define RADASSUME(exp)`
- L158 _macro_ `#define RADASSUME(exp) !! no RADASSUME defined !!`
- L159 _macro_ `#define RADFORCEINLINE !! no RADFORCEINLINE defined !!`
- L171 _macro_ `#define RAD_STATEMENT_START \`
- L174 _macro_ `#define RAD_STATEMENT_END_FALSE \`
- L180 _macro_ `#define RAD_STATEMENT_END_TRUE \`
- L187 _macro_ `#define RAD_USE_STANDARD_LOOP_CONSTRUCT`
- L204 _macro_ `#define RAD_STATEMENT_WRAPPER( code ) \`
- L209 _macro_ `#define RAD_INFINITE_LOOP( code ) \`
- L219 _macro_ `#define RR_UNUSED_VARIABLE(x) (void) (x)`
- L221 _macro_ `#define RR_UNUSED_VARIABLE(x) (void)(sizeof(x))`
- L226 _macro_ `#define RR_STRINGIZE( L ) #L` — RR_LINESTRING is the current line number as a string
- L227 _macro_ `#define RR_DO_MACRO( M, X ) M(X)`
- L228 _macro_ `#define RR_STRINGIZE_DELAY( X ) RR_DO_MACRO( RR_STRINGIZE, X )`
- L229 _macro_ `#define RR_LINESTRING RR_STRINGIZE_DELAY( __LINE__ )`
- L231 _macro_ `#define RR_CAT(X,Y) X ## Y`
- L233 _macro_ `#define RR_STRING_JOIN3(arg1, arg2, arg3) RR_STRING_JOIN_DELAY3(arg1, arg2, arg3)`
- L234 _macro_ `#define RR_STRING_JOIN_DELAY3(arg1, arg2, arg3) RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3)`
- L235 _macro_ `#define RR_STRING_JOIN_IMMEDIATE3(arg1, arg2, arg3) arg1 ## arg2 ## arg3`
- L241 _macro_ `#define RR_MIN(a,b) ( (a) < (b) ? (a) : (b) )`
- L245 _macro_ `#define RR_MAX(a,b) ( (a) > (b) ? (a) : (b) )`
- L249 _macro_ `#define RR_ABS(a) ( ((a) < 0) ? -(a) : (a) )`
- L253 _macro_ `#define RR_CLAMP(val,lo,hi) RR_MAX( RR_MIN(val,hi), lo )`
- L259 _macro_ `#define RR_ARRAY_SIZE(array) ( sizeof(array)/sizeof(array[0]) )`
- L262 _macro_ `#define RR_MEMBER_OFFSET(type,member) offsetof(type, member)` — MEMBER_OFFSET tells you the offset of a member in a type
- L265 _macro_ `#define RR_MEMBER_SIZE(type,member) ( sizeof( ((type *) 0)->member) )` — MEMBER_SIZE tells you the size of a member in a type
- L268 _macro_ `#define RR_MEMBER_OFFSET_PTR(type,member,ptr) ( (SINTa) &(((type *)(ptr))->member) - (SINTa)(ptr) )` — just to make gcc shut up about derefing null :
- L269 _macro_ `#define RR_MEMBER_SIZE_PTR(type,member,ptr) ( sizeof( ((type *) (ptr))->member) )`
- L273 _macro_ `#define RR_MEMBER_TO_OWNER(type,member,ptr) (type *)( ((char *)(ptr)) - RR_MEMBER_OFFSET_PTR(type,member,ptr) )` — MEMBER_TO_OWNER takes a pointer to a member and gives you back the base of the object you should then RR_ASSERT( &(ret->member) == ptr );
- L287 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) // nop`
- L288 _macro_ `#define RR_PREFETCH_WRITE_INVALIDATE(ptr,offset) // nop`
- L290 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) // intentional NOP for now`
- L293 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) __prefetch((char *)(ptr) + (int)(offset))`
- L301 _macro_ `#define RR_PREFETCH_SEQUENTIAL(ptr,offset) !! NO PREFETCH DEFINED !!`
- L304 _macro_ `#define RR_PREFETCH_WRITE_INVALIDATE(ptr,offset) !! NO PREFETCH DEFINED !!`
- L313 _macro_ `#define RR_DO_ASSERTS`
- L339 _macro_ `#define RR_ASSERT(exp) RAD_STATEMENT_WRAPPER( if ( ! (exp) ) { RR_BREAK(); } )`
- L341 _macro_ `#define RR_ASSERT(exp) (void)0`
- L344 _macro_ `#define rrAssert RR_ASSERT`
- L345 _macro_ `#define rrassert RR_ASSERT`
- L370 _macro_ `#define RR_GET_PTR_POST RADRESTRICT`
- L373 _macro_ `#define RR_GET_PTR_POST`
- L378 _macro_ `#define RR_GET16_NATIVE(ptr) *((const U16 * RR_GET_PTR_POST)(ptr))`
- L379 _macro_ `#define RR_PUT16_NATIVE(ptr,val) *((U16 * RR_GET_PTR_POST)(ptr)) = (U16)(val)`
- L382 _macro_ `#define RR_U16_PTR_OFFSET(ptr,offset) ((U16 * RR_GET_PTR_POST)((char *)(ptr) + (offset)))` — offset is in bytes
- L383 _macro_ `#define RR_GET16_NATIVE_OFFSET(ptr,offset) *( RR_U16_PTR_OFFSET((ptr),offset) )`
- L384 _macro_ `#define RR_PUT16_NATIVE_OFFSET(ptr,val,offset) *( RR_U16_PTR_OFFSET((ptr),offset)) = (val)`
- L386 _macro_ `#define RR_GET32_NATIVE(ptr) *((const U32 * RR_GET_PTR_POST)(ptr))`
- L387 _macro_ `#define RR_PUT32_NATIVE(ptr,val) *((U32 * RR_GET_PTR_POST)(ptr)) = (val)`
- L390 _macro_ `#define RR_U32_PTR_OFFSET(ptr,offset) ((U32 * RR_GET_PTR_POST)((char *)(ptr) + (offset)))` — offset is in bytes
- L391 _macro_ `#define RR_GET32_NATIVE_OFFSET(ptr,offset) *( RR_U32_PTR_OFFSET((ptr),offset) )`
- L392 _macro_ `#define RR_PUT32_NATIVE_OFFSET(ptr,val,offset) *( RR_U32_PTR_OFFSET((ptr),offset)) = (val)`
- L394 _macro_ `#define RR_GET64_NATIVE(ptr) *((const U64 * RR_GET_PTR_POST)(ptr))`
- L395 _macro_ `#define RR_PUT64_NATIVE(ptr,val) *((U64 * RR_GET_PTR_POST)(ptr)) = (val)`
- L398 _macro_ `#define RR_U64_PTR_OFFSET(ptr,offset) ((U64 * RR_GET_PTR_POST)((char *)(ptr) + (offset)))` — offset is in bytes
- L399 _macro_ `#define RR_GET64_NATIVE_OFFSET(ptr,offset) *( RR_U64_PTR_OFFSET((ptr),offset) )`
- L400 _macro_ `#define RR_PUT64_NATIVE_OFFSET(ptr,val,offset) *( RR_U64_PTR_OFFSET((ptr),offset)) = (val)`
- L405 _macro_ `#define RR_GET16_LE RR_GET16_NATIVE`
- L406 _macro_ `#define RR_PUT16_LE RR_PUT16_NATIVE`
- L407 _macro_ `#define RR_GET16_LE_OFFSET RR_GET16_NATIVE_OFFSET`
- L408 _macro_ `#define RR_PUT16_LE_OFFSET RR_PUT16_NATIVE_OFFSET`
- L410 _macro_ `#define RR_GET32_LE RR_GET32_NATIVE`
- L411 _macro_ `#define RR_PUT32_LE RR_PUT32_NATIVE`
- L412 _macro_ `#define RR_GET32_LE_OFFSET RR_GET32_NATIVE_OFFSET`
- L413 _macro_ `#define RR_PUT32_LE_OFFSET RR_PUT32_NATIVE_OFFSET`
- L415 _macro_ `#define RR_GET64_LE RR_GET64_NATIVE`
- L416 _macro_ `#define RR_PUT64_LE RR_PUT64_NATIVE`
- L417 _macro_ `#define RR_GET64_LE_OFFSET RR_GET64_NATIVE_OFFSET`
- L418 _macro_ `#define RR_PUT64_LE_OFFSET RR_PUT64_NATIVE_OFFSET`
- L420 _macro_ `#define RR_GET16_BE RR_GET16_NATIVE`
- L421 _macro_ `#define RR_PUT16_BE RR_PUT16_NATIVE`
- L422 _macro_ `#define RR_GET16_BE_OFFSET RR_GET16_NATIVE_OFFSET`
- L423 _macro_ `#define RR_PUT16_BE_OFFSET RR_PUT16_NATIVE_OFFSET`
- L425 _macro_ `#define RR_GET32_BE RR_GET32_NATIVE`
- L426 _macro_ `#define RR_PUT32_BE RR_PUT32_NATIVE`
- L427 _macro_ `#define RR_GET32_BE_OFFSET RR_GET32_NATIVE_OFFSET`
- L428 _macro_ `#define RR_PUT32_BE_OFFSET RR_PUT32_NATIVE_OFFSET`
- L430 _macro_ `#define RR_GET64_BE RR_GET64_NATIVE`
- L431 _macro_ `#define RR_PUT64_BE RR_PUT64_NATIVE`
- L432 _macro_ `#define RR_GET64_BE_OFFSET RR_GET64_NATIVE_OFFSET`
- L433 _macro_ `#define RR_PUT64_BE_OFFSET RR_PUT64_NATIVE_OFFSET`
- L442 _prototype_ `RADDEFFUNC unsigned short __cdecl _byteswap_ushort (unsigned short _Short);`
- L443 _prototype_ `RADDEFFUNC unsigned long __cdecl _byteswap_ulong (unsigned long _Long);`
- L446 _macro_ `#define RR_BSWAP16 _byteswap_ushort`
- L447 _macro_ `#define RR_BSWAP32 _byteswap_ulong`
- L449 _prototype_ `RADDEFFUNC unsigned __int64 __cdecl _byteswap_uint64 (unsigned __int64 val);`
- L451 _macro_ `#define RR_BSWAP64 _byteswap_uint64`
- L453 _function_ `RADDEFFUNC RADFORCEINLINE unsigned long RR_BSWAP16 (unsigned long _Long)`
- L463 _function_ `RADDEFFUNC RADFORCEINLINE unsigned long RR_BSWAP32 (unsigned long _Long)`
- L473 _function_ `RADDEFFUNC RADFORCEINLINE unsigned __int64 RR_BSWAP64 (unsigned __int64 _Long)`
- L489 _macro_ `#define RR_BSWAP16(u16) ( (U16) ( ((u16) >> 8) | ((u16) << 8) ) )` — GCC has __builtin_bswap16, but Clang only seems to have added it recently. We use __builtin_bswap32/64 but 16 just uses the macro version. (No big deal if that turns into shifts anyway)
- L490 _macro_ `#define RR_BSWAP32 __builtin_bswap32`
- L491 _macro_ `#define RR_BSWAP64 __builtin_bswap64`
- L494 _macro_ `#define RR_GET16_BE(ptr) RR_BSWAP16(*((U16 *)(ptr)))`
- L495 _macro_ `#define RR_PUT16_BE(ptr,val) *((U16 *)(ptr)) = (U16) RR_BSWAP16(val)`
- L496 _macro_ `#define RR_GET16_BE_OFFSET(ptr,offset) RR_BSWAP16(*RR_U16_PTR_OFFSET(ptr,offset))`
- L497 _macro_ `#define RR_PUT16_BE_OFFSET(ptr,val,offset) *RR_U16_PTR_OFFSET(ptr,offset) = RR_BSWAP16(val)`
- L499 _macro_ `#define RR_GET32_BE(ptr) RR_BSWAP32(*((U32 *)(ptr)))`
- L500 _macro_ `#define RR_PUT32_BE(ptr,val) *((U32 *)(ptr)) = RR_BSWAP32(val)`
- L501 _macro_ `#define RR_GET32_BE_OFFSET(ptr,offset) RR_BSWAP32(*RR_U32_PTR_OFFSET(ptr,offset))`
- L502 _macro_ `#define RR_PUT32_BE_OFFSET(ptr,val,offset) *RR_U32_PTR_OFFSET(ptr,offset) = RR_BSWAP32(val)`
- L504 _macro_ `#define RR_GET64_BE(ptr) RR_BSWAP64(*((U64 *)(ptr)))`
- L505 _macro_ `#define RR_PUT64_BE(ptr,val) *((U64 *)(ptr)) = RR_BSWAP64(val)`
- L506 _macro_ `#define RR_GET64_BE_OFFSET(ptr,offset) RR_BSWAP64(*RR_U64_PTR_OFFSET(ptr,offset))`
- L507 _macro_ `#define RR_PUT64_BE_OFFSET(ptr,val,offset) *RR_U64_PTR_OFFSET(ptr,offset) = RR_BSWAP64(val)`
- L515 _macro_ `#define RR_BSWAP32(u32) ( (U32) ( ((u32) >> 24) | (((u32)<<8) & 0x00FF0000) | (((u32)>>8) & 0x0000FF00) | ((u32) << 24) ) )`
- L516 _macro_ `#define RR_BSWAP64(u64) ( (U64) ( RR_BSWAP32((u64)>>32) | ((U64)RR_BSWAP32((U32)(u64))<<32) ) )`
- L519 _macro_ `#define RR_PUT16_BE(ptr,val) *((U16 *)(ptr)) = RR_BSWAP16(val)`
- L528 _macro_ `#define RR_BSWAP16(u16) _arm_rev16(u16)`
- L529 _macro_ `#define RR_BSWAP32(u32) _arm_rev(u32)`
- L556 _macro_ `#define RR_GET64_BE_UNALIGNED(ptr) RR_GET64_BE(ptr)`
- L557 _macro_ `#define RR_GET64_BE_UNALIGNED_OFFSET(ptr,offset) RR_GET64_BE_OFFSET(ptr,offset)`
- L558 _macro_ `#define RR_GET32_BE_UNALIGNED(ptr) RR_GET32_BE(ptr)`
- L559 _macro_ `#define RR_GET32_BE_UNALIGNED_OFFSET(ptr,offset) RR_GET32_BE_OFFSET(ptr,offset)`
- L560 _macro_ `#define RR_GET16_BE_UNALIGNED(ptr) RR_GET16_BE(ptr)`
- L561 _macro_ `#define RR_GET16_BE_UNALIGNED_OFFSET(ptr,offset) RR_GET16_BE_OFFSET(ptr,offset)`
- L563 _macro_ `#define RR_GET64_LE_UNALIGNED(ptr) RR_GET64_LE(ptr)`
- L564 _macro_ `#define RR_GET64_LE_UNALIGNED_OFFSET(ptr,offset) RR_GET64_LE_OFFSET(ptr,offset)`
- L565 _macro_ `#define RR_GET32_LE_UNALIGNED(ptr) RR_GET32_LE(ptr)`
- L566 _macro_ `#define RR_GET32_LE_UNALIGNED_OFFSET(ptr,offset) RR_GET32_LE_OFFSET(ptr,offset)`
- L567 _macro_ `#define RR_GET16_LE_UNALIGNED(ptr) RR_GET16_LE(ptr)`
- L568 _macro_ `#define RR_GET16_LE_UNALIGNED_OFFSET(ptr,offset) RR_GET16_LE_OFFSET(ptr,offset)`
- L571 _macro_ `#define RR_GET32_BE_UNALIGNED(ptr) ( \` — Unaligned via bytes :
- L577 _macro_ `#define RR_GET32_BE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L583 _macro_ `#define RR_GET16_BE_UNALIGNED(ptr) ( \`
- L587 _macro_ `#define RR_GET16_BE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L591 _macro_ `#define RR_GET32_LE_UNALIGNED(ptr) ( \`
- L597 _macro_ `#define RR_GET32_LE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L603 _macro_ `#define RR_GET16_LE_UNALIGNED(ptr) ( \`
- L607 _macro_ `#define RR_GET16_LE_UNALIGNED_OFFSET(ptr,offset) ( \`
- L619 _prototype_ `RADDEFFUNC unsigned long __cdecl _lrotl(unsigned long, int);`
- L621 _macro_ `#define RR_ROTL32(x,k) _lrotl((unsigned long)(x),(int)(k))`
- L626 _macro_ `#define RR_ROTL32(u32v,num) ( ( (u32v) << (num) ) | ( (u32v) >> (32 - (num))) )` — NOTE(fg): Barring evidence to the contrary, let's just assume that compilers are smart enough to turn this into rotates (where supported) by now.
- L635 _prototype_ `RADDEFFUNC unsigned __int64 __cdecl _rotl64(unsigned __int64 _Val, int _Shift);`
- L637 _macro_ `#define RR_ROTL64(x,k) _rotl64((unsigned __int64)(x),(int)(k))`
- L642 _macro_ `#define RR_ROTL64(u64v,num) ( ( (u64v) << (num) ) | ( (u64v) >> (64 - (num))) )` — NOTE(fg): Barring evidence to the contrary, let's just assume that compilers are smart enough to turn this into rotates (where supported) by now.
- L658 _macro_ `#define UINTn UINTa`
- L661 _macro_ `#define SINTn SINTa`
- L665 _macro_ `#define RADDEFINEDATA extern "C"`
- L666 _macro_ `#define RADDECLAREDATA extern "C"`
- L668 _macro_ `#define RR_NAMESPACE rr`
- L669 _macro_ `#define RR_NAMESPACE_START namespace RR_NAMESPACE {`
- L670 _macro_ `#define RR_NAMESPACE_END };`
- L671 _macro_ `#define RR_NAMESPACE_USE using namespace RR_NAMESPACE;`
- L673 _macro_ `#define RADDEFINEDATA`
- L674 _macro_ `#define RADDECLAREDATA extern`
- L676 _macro_ `#define RR_NAMESPACE`
- L677 _macro_ `#define RR_NAMESPACE_START`
- L678 _macro_ `#define RR_NAMESPACE_END`
- L679 _macro_ `#define RR_NAMESPACE_USE`

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/ticks.h` (Other)


#### Free symbols / members of external scopes

- L8 _prototype_ `U64 baue_ticks( void );` — cross platform rdtsc equiv - just for test usage.

### `Source/Runtime/BinkAudioDecoder/SDK/BinkAudio/Src/varbits.h` (Other)


#### struct `_VARBITS`  
`typedef struct _VARBITS`  
_L57-63_
- L59 _public member_ `BITSTYPE bits;`
- L60 _public member_ `void* RADRESTRICT cur;`
- L61 _public member_ `U32 bitlen;`
- L62 _public member_ `void* RADRESTRICT init;`

#### struct `_VARBITSEND`  
`typedef struct _VARBITSEND`  
_L68-75_
- desc: FG: same as VARBITS (and can be used with the same macros), but has space for an "end" pointer not used by the macros, but useful if you need to propagate the "end" pointer downstream in a decoder.
- L70 _public member_ `BITSTYPE bits;`
- L71 _public member_ `void* RADRESTRICT cur;`
- L72 _public member_ `U32 bitlen;`
- L73 _public member_ `void* RADRESTRICT init;`
- L74 _public member_ `void* RADRESTRICT end;`

#### struct `_VARBITSB`  
`typedef struct _VARBITSB`  
_L707-714_
- L709 _public member_ `BITSTYPE bits;`
- L710 _public member_ `void* RADRESTRICT cur;`
- L711 _public member_ `U32 bitlen;`
- L712 _public member_ `void* RADRESTRICT init;`
- L713 _public member_ `int isPut;` — CB maybe temp ; help me find bugs

#### Free symbols / members of external scopes

- L3 _macro_ `#define __VARBITSH__`
- L10 _macro_ `#define rfmerge3(name,add) name##add`
- L11 _macro_ `#define rfmerge2(name,add) rfmerge3(name,add)`
- L12 _macro_ `#define rfmerge(name) rfmerge2(name,WRAP_PUBLICS)`
- L13 _macro_ `#define VarBitsCopy rfmerge(VarBitsCopy)`
- L14 _macro_ `#define VarBitsLens rfmerge(VarBitsLens)`
- L20 _variable_ `RADDECLAREDATA const RAD_ALIGN(U32,VarBitsLens[33],32);` — variable bit macros #if defined(__RADX86__)
- L34 _macro_ `#define BITSTYPE U64`
- L35 _macro_ `#define BITSTYPELEN 64`
- L36 _macro_ `#define BITSTYPEBYTES 8`
- L37 _macro_ `#define BITSTOPMASK (1UL64<<(BITSTYPELEN-1))`
- L40 _macro_ `#define VarBitsOpen(vb,pointer) { (vb).init=pointer; if (((U32)pointer)&4) { (vb).bits = *((U32* RADRESTRICT )pointer); (vb).cur = ((char*)pointer)+4; (vb).bitlen = 32; } else { (vb).cur=pointer; (vb).bits=(vb).bitlen=0; } }` — NOTE this is read-only on USE64BITVB!
- L41 _macro_ `#define VarBitsLocalOpen(vb,pointer) { if (((U32)pointer)&4) { vb##bits = *((U32 * RADRESTRICT)pointer); vb##cur = ((char*)pointer)+4; vb##bitlen = 32; } else { vb##cur=pointer; vb##bits=vb##bitlen=0; } }`
- L45 _macro_ `#define BITSTYPE U32`
- L46 _macro_ `#define BITSTYPELEN 32`
- L47 _macro_ `#define BITSTYPEBYTES 4`
- L48 _macro_ `#define BITSTOPMASK (1UL<<(BITSTYPELEN-1))`
- L50 _macro_ `#define VarBitsOpen(vb,pointer) { (vb).cur=(vb).init=pointer; (vb).bits=(vb).bitlen=0; }`
- L51 _macro_ `#define VarBitsLocalOpen(vb,pointer) { vb##cur=pointer; vb##bits=vb##bitlen=0; }`
- L55 _macro_ `#define VARBITSTEMP BITSTYPE`
- L63 _typedef_ `} VARBITS;`
- L75 _typedef_ `} VARBITSEND;`
- L79 _macro_ `#define VarBitsPut(vb,val,size) { U32 __s=size; U32 __v=(val)&VarBitsLens[__s]; (vb).bits|=__v<<((vb).bitlen); (vb).bitlen+=__s; if ((vb).bitlen>=32) { *((U32*)(vb).cur)=(vb).bits; (vb).cur=((char*)((vb).cur)+4); (vb).bitlen-=32; (vb).bits=`
- L80 _macro_ `#define VarBitsPut1(vb,boolean) { if (boolean) (vb).bits|=(1<<(vb).bitlen); if ((++(vb).bitlen)==32) { *((U32*)(vb).cur)=(vb).bits; (vb).cur=((char*)((vb).cur)+4); (vb).bits=(vb).bitlen=0; } }`
- L81 _macro_ `#define VarBitsPuta1(vb) { (vb).bits|=(1<<(vb).bitlen); if ((++(vb).bitlen)==32) { *((U32*)(vb).cur)=(vb).bits; (vb).cur=((char*)((vb).cur)+4); (vb).bits=(vb).bitlen=0; } }`
- L82 _macro_ `#define VarBitsPuta0(vb) { if ((++(vb).bitlen)==32) { *((U32*)(vb).cur)=(vb).bits; (vb).cur=((char*)((vb).cur)+4); (vb).bits=(vb).bitlen=0; } }`
- L83 _macro_ `#define VarBitsPutAlign(vb) { U32 __s2=(32-(vb).bitlen)&31; if (__s2) { VarBitsPut((vb),0,__s2); } }`
- L84 _macro_ `#define VarBitsFlushtoMemOnly(vb) { if (((vb).bitlen)) { *((U32*)(vb).cur)=(vb).bits; } }`
- L85 _macro_ `#define VarBitsConvertPutToGet(gvb,pvb) { if (((pvb).bitlen)) { (gvb).bits=(*((U32*)(pvb).cur))>>(pvb).bitlen; (gvb).bitlen=BITSTYPELEN-(pvb).bitlen; (gvb).cur=((char*)((pvb).cur)+4); } else { (gvb).bits=0; (gvb).bitlen=0; (gvb).cur=(pvb).c`
- L86 _macro_ `#define VarBitsFlush(vb) VarBitsPutAlign(vb)`
- L87 _macro_ `#define VarBitsSize(vb) ((U32)( (((char*)(vb).cur)-((char*)(vb).init))*8 +(vb).bitlen )) // in bits !!`
- L90 _prototype_ `RADDEFFUNC void VarBitsCopy(VARBITS* dest,VARBITS* src,U32 size);` — VarBitsCopy size is in bits of course; don't use this for big copies
- L103 _macro_ `#define getbitlevelconst(level) \` — WARNING : this getbitlevel only works on *constant* U16 values ! (up to 65535) it will fail to compile with strange errors if you use a variable
- L131 _macro_ `#define count_leading_zeros(count, x) count = __cntlzw(x)`
- L133 _prototype_ `RADDEFFUNC unsigned int __CLZ32(unsigned int a);`
- L134 _macro_ `#define count_leading_zeros(count, x) count = __CLZ32(x)`
- L136 _macro_ `#define count_leading_zeros(count, x) \`
- L143 _function_ `static RADINLINE U32 getbitlevelvar( register U32 n )`
- L153 _macro_ `#define __cntlzw _CountLeadingZeros`
- L156 _macro_ `#define getbitlevelvar(n) (U32) (32 - __cntlzw(n))`
- L176 _macro_ `#define getbitlevelvar(n) (U32) (32 - _CountLeadingZeros(n))`
- L180 _macro_ `#define getbitlevelvar(n) (U32) (32 - _arm_clz(n))`
- L186 _macro_ `#define getbitlevelvar(n) (U32) (32 - __builtin_clz(n))`
- L193 _prototype_ `unsigned char _BitScanReverse(unsigned long* Index, unsigned long Mask);`
- L197 _function_ `static RADINLINE U32 getbitlevelvar( register U32 val )`
- L240 _macro_ `#define VarBitsGetAlign(vb) { (vb).bitlen=0; }`
- L241 _macro_ `#define VarBitsPos(vb) ((U32)( (((U8*)(vb).cur)-((U8*)(vb).init))*8-(vb).bitlen ))`
- L246 _macro_ `#define GetBitsLen(val) (((U32)0xffffffff)>>(U32)(32-(val)))` — CB : GetBitsLen(bits) = (1<<bits)-1 except that values for bits=32 , GetBitsLen fails for bits=0 don't pass zero to this function
- L254 _macro_ `#define VarBitsGet1(vb,i) \` — get 1 bit best to use like : if ( VarBitsGet1(vb,i) ) This *doesn't* set i to the result - that's just a temp - the expression is the result!!! i will be the unmasked bits, but that's not guaranteed!
- L270 _macro_ `#define VarBitsGet1LE(vb,i) \` — not USE64BITVB safe!
- L286 _macro_ `#define VarBitsGet(v,typ,vb,len) \`
- L301 _macro_ `#define VarBitsGetWithCheck(v,typ,vb,len,endp,dowhat) \`
- L318 _macro_ `#define VarBitsGetWithCheckBE(v,typ,vb,len,endp,dowhat) \`
- L335 _macro_ `#define VarBitsGetWithCheckLE(v,typ,vb,len,endp,dowhat) \`
- L353 _macro_ `#define VarBitsPeek(v,typ,vb,len) \` — Peek : put len bits in v but don't shift the read pointer
- L364 _macro_ `#define VarBitsGetLE(v,typ,vb,len) \` — not USE64BITVB safe!
- L380 _macro_ `#define VarBitsUse(vb,len) \` — VarBitsUse : just skip 'len' bits ; useful after a Peek
- L400 _macro_ `#define VARBITSLOCAL(name) void * name##cur; BITSTYPE name##bits; U32 name##bitlen`
- L409 _macro_ `#define VBPREFETCH( ptr ) _mm_prefetch(((char*)(ptr))+1024, _MM_HINT_T0 )`
- L412 _macro_ `#define VBPREFETCH( ptr ) __builtin_prefetch(((char*)(ptr))+1024)` — should we do this??
- L414 _macro_ `#define VBPREFETCH( ptr )`
- L420 _macro_ `#define VarBitsLocalGet(v,typ,vb,len) \`
- L436 _macro_ `#define VarBitsLocalGetWithCheckBase(v,typ,vb,len,mask,endp,dowhat,load) \` — mask == GetBitsLen(len) - for when you know this in advance. load == what to do to load
- L488 _macro_ `#define radloadbitsnative(ptr) (*((BITSTYPE* RADRESTRICT)(ptr)))`
- L490 _macro_ `#define VarBitsLocalGetWithCheck(v,typ,vb,len,endp,dowhat) VarBitsLocalGetWithCheckBase(v,typ,vb,len,GetBitsLen(len),endp,dowhat,radloadbitsnative)`
- L491 _macro_ `#define VarBitsLocalGetWithCheckBE(v,typ,vb,len,endp,dowhat) VarBitsLocalGetWithCheckBase(v,typ,vb,len,GetBitsLen(len),endp,dowhat,radloadu32ptrBE)`
- L492 _macro_ `#define VarBitsLocalGetWithCheckLE(v,typ,vb,len,endp,dowhat) VarBitsLocalGetWithCheckBase(v,typ,vb,len,GetBitsLen(len),endp,dowhat,radloadu32ptr)`
- L495 _macro_ `#define VarBitsLocalGetWithCheckM(v,typ,vb,len,mask,endp,dowhat) VarBitsLocalGetWithCheckBase(v,typ,vb,len,mask,endp,dowhat,radloadbitsnative)` — same as LocalGetWithCheck, but passing in the bit mask yourself
- L496 _macro_ `#define VarBitsLocalGetWithCheckMBE(v,typ,vb,len,mask,endp,dowhat) VarBitsLocalGetWithCheckBase(v,typ,vb,len,mask,endp,dowhat,radloadu32ptrBE)`
- L497 _macro_ `#define VarBitsLocalGetWithCheckMLE(v,typ,vb,len,mask,endp,dowhat) VarBitsLocalGetWithCheckBase(v,typ,vb,len,mask,endp,dowhat,radloadu32ptr)`
- L501 _macro_ `#define VarBitsLocalFill1WithCheckBase(vb,endp,cond,dowhat,load)\` — just the refill for a VarBitsLocalGet1WithCheck, and with an extra conditional this turns out to be really useful to have in Bink Audio.
- L511 _macro_ `#define VarBitsLocalGet1WithCheckBase(v,vb,endp,dowhat,load) \`
- L520 _macro_ `#define VarBitsLocalFill1WithCheck(vb,endp,cond,dowhat) VarBitsLocalFill1WithCheckBase(vb,endp,cond,dowhat,radloadbitsnative)`
- L521 _macro_ `#define VarBitsLocalFill1WithCheckBE(vb,endp,cond,dowhat) VarBitsLocalFill1WithCheckBase(vb,endp,cond,dowhat,radloadu32ptrBE)`
- L522 _macro_ `#define VarBitsLocalFill1WithCheckLE(vb,endp,cond,dowhat) VarBitsLocalFill1WithCheckBase(vb,endp,cond,dowhat,radloadu32ptr)`
- L524 _macro_ `#define VarBitsLocalGet1WithCheck(v,vb,endp,dowhat) VarBitsLocalGet1WithCheckBase(v,vb,endp,dowhat,radloadbitsnative)`
- L525 _macro_ `#define VarBitsLocalGet1WithCheckBE(v,vb,endp,dowhat) VarBitsLocalGet1WithCheckBase(v,vb,endp,dowhat,radloadu32ptrBE)`
- L526 _macro_ `#define VarBitsLocalGet1WithCheckLE(v,vb,endp,dowhat) VarBitsLocalGet1WithCheckBase(v,vb,endp,dowhat,radloadu32ptr)`
- L532 _macro_ `#define VarBitsLocalGetIfxSM(v,typ,vb,len,i,x,mask) \`
- L575 _macro_ `#define VarBitsLocalGetIfx(v,typ,vb,len,i,x) \`
- L581 _macro_ `#define VarBitsLocalGetIfxNM(v,typ,vb,len,i,x) \`
- L585 _macro_ `#define VarBitsLocalPeek(v,typ,vb,len) \`
- L595 _macro_ `#define VarBitsLocalGet1BE(vb,i) \`
- L610 _macro_ `#define VarBitsLocalGet1LE(vb,i) \`
- L627 _macro_ `#define VarBitsLocalMaskFromMaskAndUse1(omask,vb,imask) \` — if imask is -1, then read a bit and then &-it with input mask so now you have a mask that you can (v^m)-m to neg a value
- L640 _macro_ `#define VarBitsLocalGet1(vb,i) \`
- L674 _macro_ `#define VarBitsLocalUse(vb,len) \`
- L687 _macro_ `#define VarBitsLocalPos(vb,origvb) ((U32)( (((char*)vb##cur)-((char*)(origvb)->init))*8 +(32-vb##bitlen) )) // in bits !!`
- L691 _macro_ `#define VarBitsCopyToLocal( local, vb ) local##cur = (vb).cur; local##bits = (vb).bits; local##bitlen = (vb).bitlen;`
- L693 _macro_ `#define VarBitsCopyFromLocal( vb, local ) (vb).cur = local##cur; (vb).bits = local##bits; (vb).bitlen = local##bitlen;`
- L699 _macro_ `#define CLASSIFY_SIGN( val ) ( (((U32)((S32)(val))) >> 31 ) + ((((U32)(-(S32)(val))) >> 30 ) & 2 ) )` — classifies a signed value into: 0 = zero, 1 = neg, 2 = pos
- L714 _typedef_ `} VARBITSB;`
- L716 _macro_ `#define VarBitsBPutOpen(vb,ptr) { (vb).cur=(vb).init=(void *)(ptr); (vb).bits=(vb).bitlen=0; (vb).isPut = 1; }`
- L717 _macro_ `#define VarBitsBGetOpen(vb,ptr) { (vb).cur=(vb).init=(void *)(ptr); (vb).bits=(vb).bitlen=0; (vb).isPut = 0; }`
- L720 _macro_ `#define VarBitsBPut(vb,val,size) do { U32 __s=size; U32 __v=(val); \` — __v=(val)&VarBitsLens[__s]
- L728 _macro_ `#define VarBitsBPuta1(vb) { (vb).bits = (vb).bits + (vb).bits + 1; if ((++(vb).bitlen)==BITSTYPELEN) { *((U32*)(vb).cur)=(vb).bits; (vb).cur=((char*)((vb).cur)+4); (vb).bits=(vb).bitlen=0; } }`
- L729 _macro_ `#define VarBitsBPuta0(vb) { (vb).bits <<= 1; if ((++(vb).bitlen)==BITSTYPELEN) { *((U32*)(vb).cur)=(vb).bits; (vb).cur=((char*)((vb).cur)+4); (vb).bits=(vb).bitlen=0; } }`
- L730 _macro_ `#define VarBitsBPut1(vb,bit) { (vb).bits = (vb).bits + (vb).bits + ((bit)?1:0); if ((++(vb).bitlen)==BITSTYPELEN) { *((U32*)(vb).cur)=(vb).bits; (vb).cur=((char*)((vb).cur)+4); (vb).bits=(vb).bitlen=0; } }`
- L732 _macro_ `#define VarBitsBPutAlign(vb) { U32 __s2=(32-(vb).bitlen)&31; if (__s2) { VarBitsBPut((vb),0,__s2); } }`
- L733 _macro_ `#define VarBitsBPutFlush(vb) VarBitsBPutAlign(vb)`
- L734 _macro_ `#define VarBitsBGetAlign(vb) { (vb).bitlen=0; }`
- L735 _macro_ `#define VarBitsBPutSize(vb) ((U32)( (((char*)(vb).cur)-((char*)(vb).init))*8 +(vb).bitlen )) // in bits !!`
- L736 _macro_ `#define VarBitsBGetSize(vb) ((U32)( (((char*)(vb).cur)-((char*)(vb).init))*8 -(vb).bitlen )) // in bits !!`
- L740 _macro_ `#define VarBitsBGet(v,typ,vb,len) \` — CB : stupid & with VarBitsLens just for len = 0 ! this is because >>32 = NOP !! (on x86 anyway)
- L756 _macro_ `#define VarBitsBPeek(v,typ,vb,len) \`
- L766 _macro_ `#define VarBitsBUse(vb,len) \`
- L784 _macro_ `#define VarBitsBGet1(vb,temp_u32) \` — get 1 bit best to use like : if ( VarBitsGet1(vb,i) ) or bit = VarBitsGet1(vb,temp); WARNING : CB: i is NOT masked by &1 in this function, you must do it yourself ! 'temp_u32' MUST be a U32 !!
- L807 _function_ `inline void _VarBitsBGet(U32 & v,VARBITSB & vb,int len)`
- L831 _macro_ `#define VarBitsBGet(v,typ,vb,len) _VarBitsBGet((U32 &)v,vb,len)`
- L835 _function_ `inline void _VarBitsBPut(VARBITSB & vb,U32 val,int size)` — __v=(val)&VarBitsLens[__s]
- L864 _macro_ `#define VarBitsBPut(vb,val,size) _VarBitsBPut(vb,val,size)`
