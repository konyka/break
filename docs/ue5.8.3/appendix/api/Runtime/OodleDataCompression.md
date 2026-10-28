# Runtime / OodleDataCompression

- module root: `Source/Runtime/OodleDataCompression`
- headers: 6; symbols: 762
- symbol kinds: enum=39, enumerator=228, function=27, macro=192, prototype=156, typedef=120

### `Source/Runtime/OodleDataCompression/Sdks/2.9.14/include/oodle2.h` (Other)


#### enum `OodleLZ_Verbosity`  
`typedef enum OodleLZ_Verbosity`  
_L48-55_
- desc: Default verbosity selection of 0 will not even log when it sees corruption
- L50 _public enumerator_ `OodleLZ_Verbosity_None = 0`
- L51 _public enumerator_ `OodleLZ_Verbosity_Minimal = 1`
- L52 _public enumerator_ `OodleLZ_Verbosity_Some = 2`
- L53 _public enumerator_ `OodleLZ_Verbosity_Lots = 3`
- L54 _public enumerator_ `OodleLZ_Verbosity_Force32 = 0x40000000`

#### enum `OodleLZ_Compressor`  
`typedef enum OodleLZ_Compressor`  
_L63-88_
- L65 _public enumerator_ `OodleLZ_Compressor_Invalid = -1`
- L66 _public enumerator_ `OodleLZ_Compressor_None = 3` — None = memcpy, pass through uncompressed bytes
- L69 _public enumerator_ `OodleLZ_Compressor_Kraken = 8` — NEW COMPRESSORS :
- L70 _public enumerator_ `OodleLZ_Compressor_Leviathan = 13` — Leviathan = Kraken's big brother with higher compression, slightly slower decompression.
- L71 _public enumerator_ `OodleLZ_Compressor_Mermaid = 9` — Mermaid is between Kraken & Selkie - crazy fast, still decent compression.
- L72 _public enumerator_ `OodleLZ_Compressor_Selkie = 11` — Selkie is a super-fast relative of Mermaid.  For maximum decode speed.
- L73 _public enumerator_ `OodleLZ_Compressor_Hydra = 12` — Hydra, the many-headed beast = Leviathan, Kraken, Mermaid, or Selkie (see $OodleLZ_About_Hydra)
- L76 _public enumerator_ `OodleLZ_Compressor_BitKnit = 10` — no longer supported as of Oodle 2.9.0
- L77 _public enumerator_ `OodleLZ_Compressor_LZB16 = 4` — DEPRECATED but still supported
- L78 _public enumerator_ `OodleLZ_Compressor_LZNA = 7` — no longer supported as of Oodle 2.9.0
- L79 _public enumerator_ `OodleLZ_Compressor_LZH = 0` — no longer supported as of Oodle 2.9.0
- L80 _public enumerator_ `OodleLZ_Compressor_LZHLW = 1` — no longer supported as of Oodle 2.9.0
- L81 _public enumerator_ `OodleLZ_Compressor_LZNIB = 2` — no longer supported as of Oodle 2.9.0
- L82 _public enumerator_ `OodleLZ_Compressor_LZBLW = 5` — no longer supported as of Oodle 2.9.0
- L83 _public enumerator_ `OodleLZ_Compressor_LZA = 6` — no longer supported as of Oodle 2.9.0
- L86 _public enumerator_ `OodleLZ_Compressor_Count = 14`
- L87 _public enumerator_ `OodleLZ_Compressor_Force32 = 0x40000000`

#### enum `OodleLZ_PackedRawOverlap`  
`typedef enum OodleLZ_PackedRawOverlap`  
_L111-116_
- L113 _public enumerator_ `OodleLZ_PackedRawOverlap_No = 0`
- L114 _public enumerator_ `OodleLZ_PackedRawOverlap_Yes = 1`
- L115 _public enumerator_ `OodleLZ_PackedRawOverlap_Force32 = 0x40000000`

#### enum `OodleLZ_CheckCRC`  
`typedef enum OodleLZ_CheckCRC`  
_L120-125_
- L122 _public enumerator_ `OodleLZ_CheckCRC_No = 0`
- L123 _public enumerator_ `OodleLZ_CheckCRC_Yes = 1`
- L124 _public enumerator_ `OodleLZ_CheckCRC_Force32 = 0x40000000`

#### enum `OodleLZ_Profile`  
`typedef enum OodleLZ_Profile`  
_L138-143_
- L140 _public enumerator_ `OodleLZ_Profile_Main=0` — Main profile (all current features allowed)
- L141 _public enumerator_ `OodleLZ_Profile_Reduced=1` — Reduced profile (Kraken only, limited feature set)
- L142 _public enumerator_ `OodleLZ_Profile_Force32 = 0x40000000`

#### enum `OodleDecompressCallbackRet`  
`typedef enum OodleDecompressCallbackRet`  
_L151-157_
- L153 _public enumerator_ `OodleDecompressCallbackRet_Continue=0`
- L154 _public enumerator_ `OodleDecompressCallbackRet_Cancel=1`
- L155 _public enumerator_ `OodleDecompressCallbackRet_Invalid=2`
- L156 _public enumerator_ `OodleDecompressCallbackRet_Force32 = 0x40000000`

#### enum `OodleLZ_CompressionLevel`  
`typedef enum OodleLZ_CompressionLevel`  
_L176-203_
- L178 _public enumerator_ `OodleLZ_CompressionLevel_None=0` — don't compress, just copy raw bytes
- L179 _public enumerator_ `OodleLZ_CompressionLevel_SuperFast=1` — super fast mode, lower compression ratio
- L180 _public enumerator_ `OodleLZ_CompressionLevel_VeryFast=2` — fastest LZ mode with still decent compression ratio
- L181 _public enumerator_ `OodleLZ_CompressionLevel_Fast=3` — fast - good for daily use
- L182 _public enumerator_ `OodleLZ_CompressionLevel_Normal=4` — standard medium speed LZ mode
- L184 _public enumerator_ `OodleLZ_CompressionLevel_Optimal1=5` — optimal parse level 1 (faster optimal encoder)
- L185 _public enumerator_ `OodleLZ_CompressionLevel_Optimal2=6` — optimal parse level 2 (recommended baseline optimal encoder)
- L186 _public enumerator_ `OodleLZ_CompressionLevel_Optimal3=7` — optimal parse level 3 (slower optimal encoder)
- L187 _public enumerator_ `OodleLZ_CompressionLevel_Optimal4=8` — optimal parse level 4 (very slow optimal encoder)
- L188 _public enumerator_ `OodleLZ_CompressionLevel_Optimal5=9` — optimal parse level 5 (don't care about encode speed, maximum compression)
- L190 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast1=-1` — faster than SuperFast, less compression
- L191 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast2=-2` — faster than HyperFast1, less compression
- L192 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast3=-3` — faster than HyperFast2, less compression
- L193 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast4=-4` — fastest, less compression
- L196 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast=OodleLZ_CompressionLevel_HyperFast1` — aliases :
- L197 _public enumerator_ `OodleLZ_CompressionLevel_Optimal = OodleLZ_CompressionLevel_Optimal2` — alias optimal standard level
- L198 _public enumerator_ `OodleLZ_CompressionLevel_Max = OodleLZ_CompressionLevel_Optimal5` — maximum compression level
- L199 _public enumerator_ `OodleLZ_CompressionLevel_Min = OodleLZ_CompressionLevel_HyperFast4` — fastest compression level
- L201 _public enumerator_ `OodleLZ_CompressionLevel_Force32 = 0x40000000`
- L202 _public enumerator_ `OodleLZ_CompressionLevel_Invalid = OodleLZ_CompressionLevel_Force32`

#### enum `OodleLZ_Jobify`  
`typedef enum OodleLZ_Jobify`  
_L234-243_
- L236 _public enumerator_ `OodleLZ_Jobify_Default=0` — Use compressor default for level of internal job usage
- L237 _public enumerator_ `OodleLZ_Jobify_Disable=1` — Don't use jobs at all
- L238 _public enumerator_ `OodleLZ_Jobify_Normal=2` — Try to balance parallelism with increased memory usage
- L239 _public enumerator_ `OodleLZ_Jobify_Aggressive=3` — Maximize parallelism even when doing so requires large amounts of memory
- L240 _public enumerator_ `OodleLZ_Jobify_Count=4`
- L242 _public enumerator_ `OodleLZ_Jobify_Force32 = 0x40000000`

#### enum `OodleLZ_Decode_ThreadPhase`  
`typedef enum OodleLZ_Decode_ThreadPhase`  
_L397-403_
- L399 _public enumerator_ `OodleLZ_Decode_ThreadPhase1 = 1`
- L400 _public enumerator_ `OodleLZ_Decode_ThreadPhase2 = 2`
- L401 _public enumerator_ `OodleLZ_Decode_ThreadPhaseAll = 3`
- L402 _public enumerator_ `OodleLZ_Decode_Unthreaded = OodleLZ_Decode_ThreadPhaseAll`

#### enum `OodleLZ_FuzzSafe`  
`typedef enum OodleLZ_FuzzSafe`  
_L413-417_
- L415 _public enumerator_ `OodleLZ_FuzzSafe_No = 0`
- L416 _public enumerator_ `OodleLZ_FuzzSafe_Yes = 1`

#### enum `OodleLZSeekTable_Flags`  
`typedef enum OodleLZSeekTable_Flags`  
_L488-493_
- L490 _public enumerator_ `OodleLZSeekTable_Flags_None = 0` — default
- L491 _public enumerator_ `OodleLZSeekTable_Flags_MakeRawCRCs = 1` — make the _rawCRCs_ member of $OodleLZ_SeekTable
- L492 _public enumerator_ `OodleLZSeekTable_Flags_Force32 = 0x40000000`

#### enum `Oodle_UsageWarnings`  
`typedef enum Oodle_UsageWarnings`  
_L542-547_
- L544 _public enumerator_ `Oodle_UsageWarnings_Enabled = 0`
- L545 _public enumerator_ `Oodle_UsageWarnings_Disabled = 1`
- L546 _public enumerator_ `Oodle_UsageWarnings_Force32 = 0x40000000`

#### enum `OodleLZ_CompressScratchMemBoundType`  
`typedef enum OodleLZ_CompressScratchMemBoundType`  
_L1426-1432_
- L1428 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_WorstCase = 0` — Worst-case memory use estimate
- L1429 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_Typical = 1` — Typical memory use estimate; with this much scratch memory, allocations might still happen, but rarely.
- L1431 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2_H_INCLUDED__`
- L11 _macro_ `#define OODLE2_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2_VERSION_MINOR 14`
- L34 _macro_ `#define OodleVersion "2.9.14" /*`
- L55 _typedef_ `} OodleLZ_Verbosity;`
- L88 _typedef_ `} OodleLZ_Compressor;`
- L116 _typedef_ `} OodleLZ_PackedRawOverlap;`
- L125 _typedef_ `} OodleLZ_CheckCRC;`
- L143 _typedef_ `} OodleLZ_Profile;`
- L147 _macro_ `#define OodleLZ_Profile_Internal_Custom ((OodleLZ_Profile)100)` — Not flagged for idoc and done using a #define since it's internal (testing) use only
- L157 _typedef_ `} OodleDecompressCallbackRet;`
- L162 _typedef_ `OODEFFUNC typedef OodleDecompressCallbackRet (OODLE_CALLBACK OodleDecompressCallback)(void * userdata, const OO_U8 * rawBuf,OO_SINTa rawLen,const OO_U8 * compBuf,OO_SINTa compBufferSize , OO_SINTa rawDone, OO_SINTa compUsed);`
- L203 _typedef_ `} OodleLZ_CompressionLevel;`
- L243 _typedef_ `OodleLZ_Jobify_Force32 = 0x40000000, } OodleLZ_Jobify;`
- L269 _macro_ `#define OODLELZ_LOCALDICTIONARYSIZE_MAX (1<<30) /* Maximum value of maxLocalDictionarySize in OodleLZ_CompressOptions`
- L272 _macro_ `#define OODLELZ_SPACESPEEDTRADEOFFBYTES_DEFAULT (256) /* Default value of spaceSpeedTradeoffBytes in OodleLZ_CompressOptions`
- L303 _typedef_ `} OodleLZ_CompressOptions;`
- L403 _typedef_ `} OodleLZ_Decode_ThreadPhase;`
- L417 _typedef_ `} OodleLZ_FuzzSafe;`
- L432 _macro_ `#define OODLELZ_BLOCK_LEN (1<<18) /* The number of raw bytes per "seek chunk"`
- L436 _macro_ `#define OODLELZ_BLOCK_MAXIMUM_EXPANSION (2)`
- L437 _macro_ `#define OODLELZ_BLOCK_MAX_COMPLEN (OODLELZ_BLOCK_LEN+OODLELZ_BLOCK_MAXIMUM_EXPANSION) /* Maximum expansion per $OODLELZ_BLOCK_LEN is 1 byte.`
- L441 _macro_ `#define OODLELZ_QUANTUM_LEN (1<<14) /* Minimum decompression quantum (for old legacy codecs only)`
- L450 _macro_ `#define OODLELZ_QUANTUM_MAXIMUM_EXPANSION (5)` — 5 byte expansion per-quantum with CRC's
- L452 _macro_ `#define OODLELZ_QUANTUM_MAX_COMPLEN (OODLELZ_QUANTUM_LEN+OODLELZ_QUANTUM_MAXIMUM_EXPANSION)`
- L454 _macro_ `#define OODLELZ_SEEKCHUNKLEN_MIN OODLELZ_BLOCK_LEN`
- L455 _macro_ `#define OODLELZ_SEEKCHUNKLEN_MAX (1<<29) // half GB`
- L465 _typedef_ `} OodleLZ_DecodeSome_Out;`
- L486 _typedef_ `} OodleLZ_SeekTable;`
- L493 _typedef_ `} OodleLZSeekTable_Flags;`
- L510 _typedef_ `} OodleConfigValues;`
- L518 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_GetConfigValues(OodleConfigValues * ptr);`
- L528 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_SetConfigValues(const OodleConfigValues * ptr);`
- L547 _typedef_ `} Oodle_UsageWarnings;`
- L550 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_SetUsageWarnings(Oodle_UsageWarnings state);`
- L564 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleCore_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L577 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_Free)( void * ptr );`
- L584 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetAllocators( t_fp_OodleCore_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleCore_Plugin_Free * fp_OodleFree);`
- L606 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleCore_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L628 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L648 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetJobSystem( t_fp_OodleCore_Plugin_RunJob * fp_RunJob, t_fp_OodleCore_Plugin_WaitJob * fp_WaitJob);`
- L657 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetJobSystemAndCount( t_fp_OodleCore_Plugin_RunJob * fp_RunJob, t_fp_OodleCore_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L696 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L709 _prototype_ `OOFUNC1 t_fp_OodleCore_Plugin_Printf * OOFUNC2 OodleCore_Plugins_SetPrintf(t_fp_OodleCore_Plugin_Printf * fp_rrRawPrintf);`
- L728 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleCore_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L744 _prototype_ `OOFUNC1 t_fp_OodleCore_Plugin_DisplayAssertion * OOFUNC2 OodleCore_Plugins_SetAssertion(t_fp_OodleCore_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L763 _prototype_ `OOFUNC1 void * OOFUNC2 OodleCore_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L764 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Free_Default(void * ptr);`
- L765 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L767 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleCore_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L768 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleCore_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L776 _macro_ `#define OODLELZ_FAILED (0) /* Return value of OodleLZ_Decompress on failure`
- L927 _typedef_ `typedef struct _OodleLZDecoder OodleLZDecoder;`
- L934 _prototype_ `OOFUNC1 OodleLZDecoder * OOFUNC2 OodleLZDecoder_Create(OodleLZ_Compressor compressor,OO_S64 rawLen,void * memory, OO_SINTa memorySize);`
- L975 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_ThreadPhased_BlockDecoderMemorySizeNeeded(void);`
- L982 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZDecoder_Destroy(OodleLZDecoder * decoder);`
- L1008 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZDecoder_DecodeSome( OodleLZDecoder * decoder, OodleLZ_DecodeSome_Out * out,` — returns false if corruption detected
- L1096 _macro_ `#define OODLELZ_SEEKPOINTCOUNT_DEFAULT 16`
- L1098 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_MakeSeekChunkLen(OO_S64 rawLen, OO_S32 desiredSeekPointCount);`
- L1111 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_GetNumSeekChunks(OO_S64 rawLen, OO_S32 seekChunkLen);`
- L1121 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetSeekTableMemorySizeNeeded(OO_S32 numSeekChunks,OodleLZSeekTable_Flags flags);`
- L1135 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZ_FillSeekTable(OodleLZ_SeekTable * pTable,OodleLZSeekTable_Flags flags,OO_S32 seekChunkLen,const void * rawBuf, OO_SINTa rawLen,const void * compBuf,OO_SINTa compLen);`
- L1154 _prototype_ `OOFUNC1 OodleLZ_SeekTable * OOFUNC2 OodleLZ_CreateSeekTable(OodleLZSeekTable_Flags flags,OO_S32 seekChunkLen,const void * rawBuf, OO_SINTa rawLen,const void * compBuf,OO_SINTa compLen);`
- L1172 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZ_FreeSeekTable(OodleLZ_SeekTable * pTable);`
- L1176 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZ_CheckSeekTableCRCs(const void * rawBuf,OO_SINTa rawLen, const OodleLZ_SeekTable * seekTable);`
- L1193 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_FindSeekEntry( OO_S64 rawPos, const OodleLZ_SeekTable * seekTable);`
- L1203 _prototype_ `OOFUNC1 OO_S64 OOFUNC2 OodleLZ_GetSeekEntryPackedPos( OO_S32 seekI , const OodleLZ_SeekTable * seekTable );`
- L1215 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_CompressionLevel_GetName(OodleLZ_CompressionLevel compressSelect);`
- L1219 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_Compressor_GetName(OodleLZ_Compressor compressor);`
- L1223 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_Jobify_GetName(OodleLZ_Jobify jobify);`
- L1227 _prototype_ `OOFUNC1 const OodleLZ_CompressOptions * OOFUNC2 OodleLZ_CompressOptions_GetDefault( OodleLZ_Compressor compressor OODEFAULT(OodleLZ_Compressor_Invalid), OodleLZ_CompressionLevel lzLevel OODEFAULT(OodleLZ_CompressionLevel_Normal));`
- L1240 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZ_CompressOptions_Validate(OodleLZ_CompressOptions * pOptions);` — after you fiddle with options, call this to ensure they are allowed
- L1248 _prototype_ `OO_BOOL OodleLZ_Compressor_UsesWholeBlockQuantum(OodleLZ_Compressor compressor);`
- L1254 _prototype_ `OO_BOOL OodleLZ_Compressor_UsesLargeWindow(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor is "whole block quantum" ; must decode in steps of $OODLELZ_BLOCK_LEN , not $OODLELZ_QUANTUM_LEN like others.
- L1260 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeInCircularWindow(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor is "LargeWindow" or not, meaning it can benefit from a Long-Range-Matcher and windows larger than $OODLELZ_BLOCK_LEN
- L1266 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeThreadPhased(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be decoded using a fixed size circular window. deprecated as of 2.9.0
- L1273 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeInPlace(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be used with the $OodleLZ_Decode_ThreadPhase. See $OodleLZ_About_ThreadPhasedDecode
- L1284 _prototype_ `OO_BOOL OodleLZ_Compressor_MustDecodeWithoutResets(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be used with "in-place" decoding. This is now always true (all compressors support in-place decoding).  The function is left for backward compatibility. All compressors in the future will support in-place, you don't need to check this property.
- L1298 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeFuzzSafe(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor must decode contiguous ranges of buffer with the same Decoder. That is, most of the compressors can be Reset and restart on any block, not just seek blocks, as long as the correct window data is provided.  That is, if this returns false then the only state required across a non-reset block is the dictionary of previously decoded data. But if OodleLZ_Compressor_MustDecodeWithoutResets returns true, then you cannot do that, because the Decoder object must carry state across blocks (except reset blocks). This does not apply to seek points - you can always reset and restart decompression at a seek point.
- L1305 _prototype_ `OO_BOOL OodleLZ_Compressor_RespectsDictionarySize(OodleLZ_Compressor compressor);`
- L1315 _macro_ `#define OODLELZ_COMPRESSOR_MASK(c) (((OO_U32)1)<<((OO_S32)(c)))`
- L1317 _macro_ `#define OODLELZ_COMPRESSOR_BOOLBIT(s,c) (((s)>>(OO_S32)(c))&1)` — OODLELZ_COMPRESSOR_BOOLBIT : extract a value of 1 or 0 so it maps to "bool"
- L1319 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_IsNewLZFamily(OodleLZ_Compressor compressor)`
- L1330 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeFuzzSafe(OodleLZ_Compressor compressor)`
- L1349 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_RespectsDictionarySize(OodleLZ_Compressor compressor)`
- L1368 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_UsesWholeBlockQuantum(OodleLZ_Compressor compressor)`
- L1373 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeThreadPhased(OodleLZ_Compressor compressor)`
- L1378 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeInPlace(OodleLZ_Compressor compressor)`
- L1384 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeInCircularWindow(OodleLZ_Compressor compressor)`
- L1397 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_UsesLargeWindow(OodleLZ_Compressor compressor)`
- L1403 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_MustDecodeWithoutResets(OodleLZ_Compressor compressor)`
- L1422 _macro_ `#define OODLELZ_SCRATCH_MEM_NO_BOUND (-1) /* Scratch mem size when bound is unknown.`
- L1432 _typedef_ `OodleLZ_CompressScratchMemBoundType_Force32 = 0x40000000, } OodleLZ_CompressScratchMemBoundType;`
- L1447 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressScratchMemBound( OodleLZ_Compressor compressor, OodleLZ_CompressionLevel level, OO_SINTa rawLen, const OodleLZ_CompressOptions * pOptions OODEFAULT(NULL) );`
- L1477 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressScratchMemBoundEx( OodleLZ_Compressor compressor, OodleLZ_CompressionLevel level, OodleLZ_CompressScratchMemBoundType boundType, OO_SINTa rawLen, const OodleLZ_CompressOptions * pOptions OODEFAULT(NULL) );`
- L1515 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressedBufferSizeNeeded(OodleLZ_Compressor compressor,OO_SINTa rawSize);` — get maximum expanded size for compBuf alloc : (note this is actually larger than the maximum compressed stream, it includes trash padding)
- L1529 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetDecodeBufferSize(OodleLZ_Compressor compressor,OO_SINTa rawSize,OO_BOOL corruptionPossible);` — decBuf needs to be a little larger than rawLen, this will tell you exactly how much :
- L1564 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetInPlaceDecodeBufferSize(OodleLZ_Compressor compressor,OO_SINTa compLen, OO_SINTa rawLen);` — OodleLZ_GetInPlaceDecodeBufferSize : after compressing, ask how big the in-place buffer needs to be
- L1587 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressedStepForRawStep( const void * compPtr, OO_SINTa compAvail, OO_SINTa startRawPos, OO_SINTa rawSeekBytes, OO_SINTa * pEndRawPos OODEFAULT(NULL), OO_BOOL * pIndependent OODEFAULT(NULL) );` — GetCompressedStepForRawStep is at OODLELZ_QUANTUM_LEN granularity returns how many packed bytes to step to get the desired raw count step
- L1623 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetAllChunksCompressor(const void * compBuf,OO_SINTa compBufSize, OO_SINTa rawLen);`
- L1646 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetFirstChunkCompressor(const void * compChunkPtr, OO_SINTa compBufAvail, OO_BOOL * pIndependent);`
- L1666 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetChunkCompressor(const void * compChunkPtr, OO_SINTa compBufAvail, OO_BOOL * pIndependent);`
- L1677 _macro_ `#define OODLE_HEADER_VERSION ((46<<24)|(OODLE2_VERSION_MAJOR<<16)|(OODLE2_VERSION_MINOR<<8)|(OO_U32)sizeof(OodleLZ_SeekTable)) /* OODLE_HEADER_VERSION is used to ensure the Oodle header matches the lib. Don't copy the value of this macro, i`
- L1683 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 Oodle_CheckVersion(OO_U32 oodle_header_version, OO_U32 * pOodleLibVersion OODEFAULT(NULL));`
- L1694 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_LogHeader(void);`
- L1701 _macro_ `#define OODLECORE_PLUGIN_JOB_MAX_DEPENDENCIES OODLE_JOB_MAX_DEPENDENCIES` — define old names so they still compile :
- L1702 _macro_ `#define t_fp_OodleCore_Plugin_Job t_fp_Oodle_Job`

### `Source/Runtime/OodleDataCompression/Sdks/2.9.14/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2025, Epic Games Tools LLC"`
- L29 _typedef_ `typedef int8_t OO_S8;` — Typedefs
- L30 _typedef_ `typedef uint8_t OO_U8;`
- L31 _typedef_ `typedef int16_t OO_S16;`
- L32 _typedef_ `typedef uint16_t OO_U16;`
- L33 _typedef_ `typedef int32_t OO_S32;`
- L34 _typedef_ `typedef uint32_t OO_U32;`
- L35 _typedef_ `typedef int64_t OO_S64;`
- L36 _typedef_ `typedef uint64_t OO_U64;`
- L37 _typedef_ `typedef float OO_F32;`
- L38 _typedef_ `typedef double OO_F64;`
- L39 _typedef_ `typedef intptr_t OO_SINTa;`
- L40 _typedef_ `typedef uintptr_t OO_UINTa;`
- L41 _typedef_ `typedef int32_t OO_BOOL;`
- L45 _macro_ `#define OOSTRUCT struct __attribute__((__packed__))`
- L46 _macro_ `#define OOINLINEFUNC inline`
- L49 _macro_ `#define OOSTRUCT struct` — on VC++, we use pragmas for the struct packing
- L50 _macro_ `#define OOINLINEFUNC __inline`
- L55 _macro_ `#define OOLINK __stdcall`
- L56 _macro_ `#define OOEXPLINK __stdcall`
- L58 _macro_ `#define OOLINK`
- L59 _macro_ `#define OOEXPLINK`
- L64 _macro_ `#define OODEFFUNC extern "C"`
- L65 _macro_ `#define OODEFSTART extern "C" {`
- L66 _macro_ `#define OODEFEND }`
- L67 _macro_ `#define OODEFAULT( val ) =val`
- L69 _macro_ `#define OODEFFUNC`
- L70 _macro_ `#define OODEFSTART`
- L71 _macro_ `#define OODEFEND`
- L72 _macro_ `#define OODEFAULT( val )`
- L77 _macro_ `#define OOEXPFUNC OODEFFUNC` — Exported function declarations
- L81 _macro_ `#define OO_STRING_JOIN(arg1, arg2) OO_STRING_JOIN_DELAY(arg1, arg2)` — OO_STRING_JOIN joins strings in the preprocessor and works with LINESTRING
- L82 _macro_ `#define OO_STRING_JOIN_DELAY(arg1, arg2) OO_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L83 _macro_ `#define OO_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L91 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__COUNTER__)`
- L93 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__LINE__)`
- L101 _macro_ `#define OO_COMPILER_ASSERT(exp) static_assert(exp, "Assert " #exp)`
- L104 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L106 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L109 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L121 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L123 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L124 _macro_ `#define OOFUNC2 OOEXPLINK`
- L125 _macro_ `#define OOFUNCSTART`
- L126 _macro_ `#define OODLE_CALLBACK OOLINK`
- L134 _macro_ `#define NULL (0)`
- L138 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L140 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L145 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L150 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L153 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L159 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Runtime/OodleDataCompression/Sdks/2.9.15/include/oodle2.h` (Other)


#### enum `OodleLZ_Verbosity`  
`typedef enum OodleLZ_Verbosity`  
_L48-55_
- desc: Default verbosity selection of 0 will not even log when it sees corruption
- L50 _public enumerator_ `OodleLZ_Verbosity_None = 0`
- L51 _public enumerator_ `OodleLZ_Verbosity_Minimal = 1`
- L52 _public enumerator_ `OodleLZ_Verbosity_Some = 2`
- L53 _public enumerator_ `OodleLZ_Verbosity_Lots = 3`
- L54 _public enumerator_ `OodleLZ_Verbosity_Force32 = 0x40000000`

#### enum `OodleLZ_Compressor`  
`typedef enum OodleLZ_Compressor`  
_L63-88_
- L65 _public enumerator_ `OodleLZ_Compressor_Invalid = -1`
- L66 _public enumerator_ `OodleLZ_Compressor_None = 3` — None = memcpy, pass through uncompressed bytes
- L69 _public enumerator_ `OodleLZ_Compressor_Kraken = 8` — NEW COMPRESSORS :
- L70 _public enumerator_ `OodleLZ_Compressor_Leviathan = 13` — Leviathan = Kraken's big brother with higher compression, slightly slower decompression.
- L71 _public enumerator_ `OodleLZ_Compressor_Mermaid = 9` — Mermaid is between Kraken & Selkie - crazy fast, still decent compression.
- L72 _public enumerator_ `OodleLZ_Compressor_Selkie = 11` — Selkie is a super-fast relative of Mermaid.  For maximum decode speed.
- L73 _public enumerator_ `OodleLZ_Compressor_Hydra = 12` — Hydra, the many-headed beast = Leviathan, Kraken, Mermaid, or Selkie (see $OodleLZ_About_Hydra)
- L76 _public enumerator_ `OodleLZ_Compressor_BitKnit = 10` — no longer supported as of Oodle 2.9.0
- L77 _public enumerator_ `OodleLZ_Compressor_LZB16 = 4` — DEPRECATED but still supported
- L78 _public enumerator_ `OodleLZ_Compressor_LZNA = 7` — no longer supported as of Oodle 2.9.0
- L79 _public enumerator_ `OodleLZ_Compressor_LZH = 0` — no longer supported as of Oodle 2.9.0
- L80 _public enumerator_ `OodleLZ_Compressor_LZHLW = 1` — no longer supported as of Oodle 2.9.0
- L81 _public enumerator_ `OodleLZ_Compressor_LZNIB = 2` — no longer supported as of Oodle 2.9.0
- L82 _public enumerator_ `OodleLZ_Compressor_LZBLW = 5` — no longer supported as of Oodle 2.9.0
- L83 _public enumerator_ `OodleLZ_Compressor_LZA = 6` — no longer supported as of Oodle 2.9.0
- L86 _public enumerator_ `OodleLZ_Compressor_Count = 14`
- L87 _public enumerator_ `OodleLZ_Compressor_Force32 = 0x40000000`

#### enum `OodleLZ_PackedRawOverlap`  
`typedef enum OodleLZ_PackedRawOverlap`  
_L111-116_
- L113 _public enumerator_ `OodleLZ_PackedRawOverlap_No = 0`
- L114 _public enumerator_ `OodleLZ_PackedRawOverlap_Yes = 1`
- L115 _public enumerator_ `OodleLZ_PackedRawOverlap_Force32 = 0x40000000`

#### enum `OodleLZ_CheckCRC`  
`typedef enum OodleLZ_CheckCRC`  
_L120-125_
- L122 _public enumerator_ `OodleLZ_CheckCRC_No = 0`
- L123 _public enumerator_ `OodleLZ_CheckCRC_Yes = 1`
- L124 _public enumerator_ `OodleLZ_CheckCRC_Force32 = 0x40000000`

#### enum `OodleLZ_Profile`  
`typedef enum OodleLZ_Profile`  
_L138-143_
- L140 _public enumerator_ `OodleLZ_Profile_Main=0` — Main profile (all current features allowed)
- L141 _public enumerator_ `OodleLZ_Profile_Reduced=1` — Reduced profile (Kraken only, limited feature set)
- L142 _public enumerator_ `OodleLZ_Profile_Force32 = 0x40000000`

#### enum `OodleDecompressCallbackRet`  
`typedef enum OodleDecompressCallbackRet`  
_L151-157_
- L153 _public enumerator_ `OodleDecompressCallbackRet_Continue=0`
- L154 _public enumerator_ `OodleDecompressCallbackRet_Cancel=1`
- L155 _public enumerator_ `OodleDecompressCallbackRet_Invalid=2`
- L156 _public enumerator_ `OodleDecompressCallbackRet_Force32 = 0x40000000`

#### enum `OodleLZ_CompressionLevel`  
`typedef enum OodleLZ_CompressionLevel`  
_L176-203_
- L178 _public enumerator_ `OodleLZ_CompressionLevel_None=0` — don't compress, just copy raw bytes
- L179 _public enumerator_ `OodleLZ_CompressionLevel_SuperFast=1` — super fast mode, lower compression ratio
- L180 _public enumerator_ `OodleLZ_CompressionLevel_VeryFast=2` — fastest LZ mode with still decent compression ratio
- L181 _public enumerator_ `OodleLZ_CompressionLevel_Fast=3` — fast - good for daily use
- L182 _public enumerator_ `OodleLZ_CompressionLevel_Normal=4` — standard medium speed LZ mode
- L184 _public enumerator_ `OodleLZ_CompressionLevel_Optimal1=5` — optimal parse level 1 (faster optimal encoder)
- L185 _public enumerator_ `OodleLZ_CompressionLevel_Optimal2=6` — optimal parse level 2 (recommended baseline optimal encoder)
- L186 _public enumerator_ `OodleLZ_CompressionLevel_Optimal3=7` — optimal parse level 3 (slower optimal encoder)
- L187 _public enumerator_ `OodleLZ_CompressionLevel_Optimal4=8` — optimal parse level 4 (very slow optimal encoder)
- L188 _public enumerator_ `OodleLZ_CompressionLevel_Optimal5=9` — optimal parse level 5 (don't care about encode speed, maximum compression)
- L190 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast1=-1` — faster than SuperFast, less compression
- L191 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast2=-2` — faster than HyperFast1, less compression
- L192 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast3=-3` — faster than HyperFast2, less compression
- L193 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast4=-4` — fastest, less compression
- L196 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast=OodleLZ_CompressionLevel_HyperFast1` — aliases :
- L197 _public enumerator_ `OodleLZ_CompressionLevel_Optimal = OodleLZ_CompressionLevel_Optimal2` — alias optimal standard level
- L198 _public enumerator_ `OodleLZ_CompressionLevel_Max = OodleLZ_CompressionLevel_Optimal5` — maximum compression level
- L199 _public enumerator_ `OodleLZ_CompressionLevel_Min = OodleLZ_CompressionLevel_HyperFast4` — fastest compression level
- L201 _public enumerator_ `OodleLZ_CompressionLevel_Force32 = 0x40000000`
- L202 _public enumerator_ `OodleLZ_CompressionLevel_Invalid = OodleLZ_CompressionLevel_Force32`

#### enum `OodleLZ_Jobify`  
`typedef enum OodleLZ_Jobify`  
_L234-243_
- L236 _public enumerator_ `OodleLZ_Jobify_Default=0` — Use compressor default for level of internal job usage
- L237 _public enumerator_ `OodleLZ_Jobify_Disable=1` — Don't use jobs at all
- L238 _public enumerator_ `OodleLZ_Jobify_Normal=2` — Try to balance parallelism with increased memory usage
- L239 _public enumerator_ `OodleLZ_Jobify_Aggressive=3` — Maximize parallelism even when doing so requires large amounts of memory
- L240 _public enumerator_ `OodleLZ_Jobify_Count=4`
- L242 _public enumerator_ `OodleLZ_Jobify_Force32 = 0x40000000`

#### enum `OodleLZ_Decode_ThreadPhase`  
`typedef enum OodleLZ_Decode_ThreadPhase`  
_L397-403_
- L399 _public enumerator_ `OodleLZ_Decode_ThreadPhase1 = 1`
- L400 _public enumerator_ `OodleLZ_Decode_ThreadPhase2 = 2`
- L401 _public enumerator_ `OodleLZ_Decode_ThreadPhaseAll = 3`
- L402 _public enumerator_ `OodleLZ_Decode_Unthreaded = OodleLZ_Decode_ThreadPhaseAll`

#### enum `OodleLZ_FuzzSafe`  
`typedef enum OodleLZ_FuzzSafe`  
_L413-417_
- L415 _public enumerator_ `OodleLZ_FuzzSafe_No = 0`
- L416 _public enumerator_ `OodleLZ_FuzzSafe_Yes = 1`

#### enum `OodleLZSeekTable_Flags`  
`typedef enum OodleLZSeekTable_Flags`  
_L488-493_
- L490 _public enumerator_ `OodleLZSeekTable_Flags_None = 0` — default
- L491 _public enumerator_ `OodleLZSeekTable_Flags_MakeRawCRCs = 1` — make the _rawCRCs_ member of $OodleLZ_SeekTable
- L492 _public enumerator_ `OodleLZSeekTable_Flags_Force32 = 0x40000000`

#### enum `Oodle_UsageWarnings`  
`typedef enum Oodle_UsageWarnings`  
_L542-547_
- L544 _public enumerator_ `Oodle_UsageWarnings_Enabled = 0`
- L545 _public enumerator_ `Oodle_UsageWarnings_Disabled = 1`
- L546 _public enumerator_ `Oodle_UsageWarnings_Force32 = 0x40000000`

#### enum `OodleLZ_CompressScratchMemBoundType`  
`typedef enum OodleLZ_CompressScratchMemBoundType`  
_L1426-1432_
- L1428 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_WorstCase = 0` — Worst-case memory use estimate
- L1429 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_Typical = 1` — Typical memory use estimate; with this much scratch memory, allocations might still happen, but rarely.
- L1431 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2_H_INCLUDED__`
- L11 _macro_ `#define OODLE2_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2_VERSION_MINOR 15`
- L34 _macro_ `#define OodleVersion "2.9.15" /*`
- L55 _typedef_ `} OodleLZ_Verbosity;`
- L88 _typedef_ `} OodleLZ_Compressor;`
- L116 _typedef_ `} OodleLZ_PackedRawOverlap;`
- L125 _typedef_ `} OodleLZ_CheckCRC;`
- L143 _typedef_ `} OodleLZ_Profile;`
- L147 _macro_ `#define OodleLZ_Profile_Internal_Custom ((OodleLZ_Profile)100)` — Not flagged for idoc and done using a #define since it's internal (testing) use only
- L157 _typedef_ `} OodleDecompressCallbackRet;`
- L162 _typedef_ `OODEFFUNC typedef OodleDecompressCallbackRet (OODLE_CALLBACK OodleDecompressCallback)(void * userdata, const OO_U8 * rawBuf,OO_SINTa rawLen,const OO_U8 * compBuf,OO_SINTa compBufferSize , OO_SINTa rawDone, OO_SINTa compUsed);`
- L203 _typedef_ `} OodleLZ_CompressionLevel;`
- L243 _typedef_ `OodleLZ_Jobify_Force32 = 0x40000000, } OodleLZ_Jobify;`
- L269 _macro_ `#define OODLELZ_LOCALDICTIONARYSIZE_MAX (1<<30) /* Maximum value of maxLocalDictionarySize in OodleLZ_CompressOptions`
- L272 _macro_ `#define OODLELZ_SPACESPEEDTRADEOFFBYTES_DEFAULT (256) /* Default value of spaceSpeedTradeoffBytes in OodleLZ_CompressOptions`
- L303 _typedef_ `} OodleLZ_CompressOptions;`
- L403 _typedef_ `} OodleLZ_Decode_ThreadPhase;`
- L417 _typedef_ `} OodleLZ_FuzzSafe;`
- L432 _macro_ `#define OODLELZ_BLOCK_LEN (1<<18) /* The number of raw bytes per "seek chunk"`
- L436 _macro_ `#define OODLELZ_BLOCK_MAXIMUM_EXPANSION (2)`
- L437 _macro_ `#define OODLELZ_BLOCK_MAX_COMPLEN (OODLELZ_BLOCK_LEN+OODLELZ_BLOCK_MAXIMUM_EXPANSION) /* Maximum expansion per $OODLELZ_BLOCK_LEN is 1 byte.`
- L441 _macro_ `#define OODLELZ_QUANTUM_LEN (1<<14) /* Minimum decompression quantum (for old legacy codecs only)`
- L450 _macro_ `#define OODLELZ_QUANTUM_MAXIMUM_EXPANSION (5)` — 5 byte expansion per-quantum with CRC's
- L452 _macro_ `#define OODLELZ_QUANTUM_MAX_COMPLEN (OODLELZ_QUANTUM_LEN+OODLELZ_QUANTUM_MAXIMUM_EXPANSION)`
- L454 _macro_ `#define OODLELZ_SEEKCHUNKLEN_MIN OODLELZ_BLOCK_LEN`
- L455 _macro_ `#define OODLELZ_SEEKCHUNKLEN_MAX (1<<29) // half GB`
- L465 _typedef_ `} OodleLZ_DecodeSome_Out;`
- L486 _typedef_ `} OodleLZ_SeekTable;`
- L493 _typedef_ `} OodleLZSeekTable_Flags;`
- L510 _typedef_ `} OodleConfigValues;`
- L518 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_GetConfigValues(OodleConfigValues * ptr);`
- L528 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_SetConfigValues(const OodleConfigValues * ptr);`
- L547 _typedef_ `} Oodle_UsageWarnings;`
- L550 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_SetUsageWarnings(Oodle_UsageWarnings state);`
- L564 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleCore_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L577 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_Free)( void * ptr );`
- L584 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetAllocators( t_fp_OodleCore_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleCore_Plugin_Free * fp_OodleFree);`
- L606 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleCore_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L628 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L648 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetJobSystem( t_fp_OodleCore_Plugin_RunJob * fp_RunJob, t_fp_OodleCore_Plugin_WaitJob * fp_WaitJob);`
- L657 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetJobSystemAndCount( t_fp_OodleCore_Plugin_RunJob * fp_RunJob, t_fp_OodleCore_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L696 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L709 _prototype_ `OOFUNC1 t_fp_OodleCore_Plugin_Printf * OOFUNC2 OodleCore_Plugins_SetPrintf(t_fp_OodleCore_Plugin_Printf * fp_rrRawPrintf);`
- L728 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleCore_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L744 _prototype_ `OOFUNC1 t_fp_OodleCore_Plugin_DisplayAssertion * OOFUNC2 OodleCore_Plugins_SetAssertion(t_fp_OodleCore_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L763 _prototype_ `OOFUNC1 void * OOFUNC2 OodleCore_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L764 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Free_Default(void * ptr);`
- L765 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L767 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleCore_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L768 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleCore_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L776 _macro_ `#define OODLELZ_FAILED (0) /* Return value of OodleLZ_Decompress on failure`
- L927 _typedef_ `typedef struct _OodleLZDecoder OodleLZDecoder;`
- L934 _prototype_ `OOFUNC1 OodleLZDecoder * OOFUNC2 OodleLZDecoder_Create(OodleLZ_Compressor compressor,OO_S64 rawLen,void * memory, OO_SINTa memorySize);`
- L975 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_ThreadPhased_BlockDecoderMemorySizeNeeded(void);`
- L982 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZDecoder_Destroy(OodleLZDecoder * decoder);`
- L1008 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZDecoder_DecodeSome( OodleLZDecoder * decoder, OodleLZ_DecodeSome_Out * out,` — returns false if corruption detected
- L1096 _macro_ `#define OODLELZ_SEEKPOINTCOUNT_DEFAULT 16`
- L1098 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_MakeSeekChunkLen(OO_S64 rawLen, OO_S32 desiredSeekPointCount);`
- L1111 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_GetNumSeekChunks(OO_S64 rawLen, OO_S32 seekChunkLen);`
- L1121 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetSeekTableMemorySizeNeeded(OO_S32 numSeekChunks,OodleLZSeekTable_Flags flags);`
- L1135 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZ_FillSeekTable(OodleLZ_SeekTable * pTable,OodleLZSeekTable_Flags flags,OO_S32 seekChunkLen,const void * rawBuf, OO_SINTa rawLen,const void * compBuf,OO_SINTa compLen);`
- L1154 _prototype_ `OOFUNC1 OodleLZ_SeekTable * OOFUNC2 OodleLZ_CreateSeekTable(OodleLZSeekTable_Flags flags,OO_S32 seekChunkLen,const void * rawBuf, OO_SINTa rawLen,const void * compBuf,OO_SINTa compLen);`
- L1172 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZ_FreeSeekTable(OodleLZ_SeekTable * pTable);`
- L1176 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZ_CheckSeekTableCRCs(const void * rawBuf,OO_SINTa rawLen, const OodleLZ_SeekTable * seekTable);`
- L1193 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_FindSeekEntry( OO_S64 rawPos, const OodleLZ_SeekTable * seekTable);`
- L1203 _prototype_ `OOFUNC1 OO_S64 OOFUNC2 OodleLZ_GetSeekEntryPackedPos( OO_S32 seekI , const OodleLZ_SeekTable * seekTable );`
- L1215 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_CompressionLevel_GetName(OodleLZ_CompressionLevel compressSelect);`
- L1219 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_Compressor_GetName(OodleLZ_Compressor compressor);`
- L1223 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_Jobify_GetName(OodleLZ_Jobify jobify);`
- L1227 _prototype_ `OOFUNC1 const OodleLZ_CompressOptions * OOFUNC2 OodleLZ_CompressOptions_GetDefault( OodleLZ_Compressor compressor OODEFAULT(OodleLZ_Compressor_Invalid), OodleLZ_CompressionLevel lzLevel OODEFAULT(OodleLZ_CompressionLevel_Normal));`
- L1240 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZ_CompressOptions_Validate(OodleLZ_CompressOptions * pOptions);` — after you fiddle with options, call this to ensure they are allowed
- L1248 _prototype_ `OO_BOOL OodleLZ_Compressor_UsesWholeBlockQuantum(OodleLZ_Compressor compressor);`
- L1254 _prototype_ `OO_BOOL OodleLZ_Compressor_UsesLargeWindow(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor is "whole block quantum" ; must decode in steps of $OODLELZ_BLOCK_LEN , not $OODLELZ_QUANTUM_LEN like others.
- L1260 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeInCircularWindow(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor is "LargeWindow" or not, meaning it can benefit from a Long-Range-Matcher and windows larger than $OODLELZ_BLOCK_LEN
- L1266 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeThreadPhased(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be decoded using a fixed size circular window. deprecated as of 2.9.0
- L1273 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeInPlace(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be used with the $OodleLZ_Decode_ThreadPhase. See $OodleLZ_About_ThreadPhasedDecode
- L1284 _prototype_ `OO_BOOL OodleLZ_Compressor_MustDecodeWithoutResets(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be used with "in-place" decoding. This is now always true (all compressors support in-place decoding).  The function is left for backward compatibility. All compressors in the future will support in-place, you don't need to check this property.
- L1298 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeFuzzSafe(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor must decode contiguous ranges of buffer with the same Decoder. That is, most of the compressors can be Reset and restart on any block, not just seek blocks, as long as the correct window data is provided.  That is, if this returns false then the only state required across a non-reset block is the dictionary of previously decoded data. But if OodleLZ_Compressor_MustDecodeWithoutResets returns true, then you cannot do that, because the Decoder object must carry state across blocks (except reset blocks). This does not apply to seek points - you can always reset and restart decompression at a seek point.
- L1305 _prototype_ `OO_BOOL OodleLZ_Compressor_RespectsDictionarySize(OodleLZ_Compressor compressor);`
- L1315 _macro_ `#define OODLELZ_COMPRESSOR_MASK(c) (((OO_U32)1)<<((OO_S32)(c)))`
- L1317 _macro_ `#define OODLELZ_COMPRESSOR_BOOLBIT(s,c) (((s)>>(OO_S32)(c))&1)` — OODLELZ_COMPRESSOR_BOOLBIT : extract a value of 1 or 0 so it maps to "bool"
- L1319 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_IsNewLZFamily(OodleLZ_Compressor compressor)`
- L1330 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeFuzzSafe(OodleLZ_Compressor compressor)`
- L1349 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_RespectsDictionarySize(OodleLZ_Compressor compressor)`
- L1368 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_UsesWholeBlockQuantum(OodleLZ_Compressor compressor)`
- L1373 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeThreadPhased(OodleLZ_Compressor compressor)`
- L1378 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeInPlace(OodleLZ_Compressor compressor)`
- L1384 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeInCircularWindow(OodleLZ_Compressor compressor)`
- L1397 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_UsesLargeWindow(OodleLZ_Compressor compressor)`
- L1403 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_MustDecodeWithoutResets(OodleLZ_Compressor compressor)`
- L1422 _macro_ `#define OODLELZ_SCRATCH_MEM_NO_BOUND (-1) /* Scratch mem size when bound is unknown.`
- L1432 _typedef_ `OodleLZ_CompressScratchMemBoundType_Force32 = 0x40000000, } OodleLZ_CompressScratchMemBoundType;`
- L1447 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressScratchMemBound( OodleLZ_Compressor compressor, OodleLZ_CompressionLevel level, OO_SINTa rawLen, const OodleLZ_CompressOptions * pOptions OODEFAULT(NULL) );`
- L1477 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressScratchMemBoundEx( OodleLZ_Compressor compressor, OodleLZ_CompressionLevel level, OodleLZ_CompressScratchMemBoundType boundType, OO_SINTa rawLen, const OodleLZ_CompressOptions * pOptions OODEFAULT(NULL) );`
- L1515 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressedBufferSizeNeeded(OodleLZ_Compressor compressor,OO_SINTa rawSize);` — get maximum expanded size for compBuf alloc : (note this is actually larger than the maximum compressed stream, it includes trash padding)
- L1530 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetDecodeBufferSize(OodleLZ_Compressor compressor,OO_SINTa rawSize,OO_BOOL corruptionPossible);` — decBuf needs to be a little larger than rawLen, this will tell you exactly how much :
- L1565 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetInPlaceDecodeBufferSize(OodleLZ_Compressor compressor,OO_SINTa compLen, OO_SINTa rawLen);` — OodleLZ_GetInPlaceDecodeBufferSize : after compressing, ask how big the in-place buffer needs to be
- L1588 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressedStepForRawStep( const void * compPtr, OO_SINTa compAvail, OO_SINTa startRawPos, OO_SINTa rawSeekBytes, OO_SINTa * pEndRawPos OODEFAULT(NULL), OO_BOOL * pIndependent OODEFAULT(NULL) );` — GetCompressedStepForRawStep is at OODLELZ_QUANTUM_LEN granularity returns how many packed bytes to step to get the desired raw count step
- L1624 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetAllChunksCompressor(const void * compBuf,OO_SINTa compBufSize, OO_SINTa rawLen);`
- L1647 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetFirstChunkCompressor(const void * compChunkPtr, OO_SINTa compBufAvail, OO_BOOL * pIndependent);`
- L1667 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetChunkCompressor(const void * compChunkPtr, OO_SINTa compBufAvail, OO_BOOL * pIndependent);`
- L1678 _macro_ `#define OODLE_HEADER_VERSION ((46<<24)|(OODLE2_VERSION_MAJOR<<16)|(OODLE2_VERSION_MINOR<<8)|(OO_U32)sizeof(OodleLZ_SeekTable)) /* OODLE_HEADER_VERSION is used to ensure the Oodle header matches the lib. Don't copy the value of this macro, i`
- L1684 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 Oodle_CheckVersion(OO_U32 oodle_header_version, OO_U32 * pOodleLibVersion OODEFAULT(NULL));`
- L1695 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_LogHeader(void);`
- L1702 _macro_ `#define OODLECORE_PLUGIN_JOB_MAX_DEPENDENCIES OODLE_JOB_MAX_DEPENDENCIES` — define old names so they still compile :
- L1703 _macro_ `#define t_fp_OodleCore_Plugin_Job t_fp_Oodle_Job`

### `Source/Runtime/OodleDataCompression/Sdks/2.9.15/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2026, Epic Games Tools LLC"`
- L29 _typedef_ `typedef int8_t OO_S8;` — Typedefs
- L30 _typedef_ `typedef uint8_t OO_U8;`
- L31 _typedef_ `typedef int16_t OO_S16;`
- L32 _typedef_ `typedef uint16_t OO_U16;`
- L33 _typedef_ `typedef int32_t OO_S32;`
- L34 _typedef_ `typedef uint32_t OO_U32;`
- L35 _typedef_ `typedef int64_t OO_S64;`
- L36 _typedef_ `typedef uint64_t OO_U64;`
- L37 _typedef_ `typedef float OO_F32;`
- L38 _typedef_ `typedef double OO_F64;`
- L39 _typedef_ `typedef intptr_t OO_SINTa;`
- L40 _typedef_ `typedef uintptr_t OO_UINTa;`
- L41 _typedef_ `typedef int32_t OO_BOOL;`
- L45 _macro_ `#define OOSTRUCT struct __attribute__((__packed__))`
- L46 _macro_ `#define OOINLINEFUNC inline`
- L49 _macro_ `#define OOSTRUCT struct` — on VC++, we use pragmas for the struct packing
- L50 _macro_ `#define OOINLINEFUNC __inline`
- L55 _macro_ `#define OOLINK __stdcall`
- L56 _macro_ `#define OOEXPLINK __stdcall`
- L58 _macro_ `#define OOLINK`
- L59 _macro_ `#define OOEXPLINK`
- L64 _macro_ `#define OODEFFUNC extern "C"`
- L65 _macro_ `#define OODEFSTART extern "C" {`
- L66 _macro_ `#define OODEFEND }`
- L67 _macro_ `#define OODEFAULT( val ) =val`
- L69 _macro_ `#define OODEFFUNC`
- L70 _macro_ `#define OODEFSTART`
- L71 _macro_ `#define OODEFEND`
- L72 _macro_ `#define OODEFAULT( val )`
- L77 _macro_ `#define OOEXPFUNC OODEFFUNC` — Exported function declarations
- L81 _macro_ `#define OO_STRING_JOIN(arg1, arg2) OO_STRING_JOIN_DELAY(arg1, arg2)` — OO_STRING_JOIN joins strings in the preprocessor and works with LINESTRING
- L82 _macro_ `#define OO_STRING_JOIN_DELAY(arg1, arg2) OO_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L83 _macro_ `#define OO_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L91 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__COUNTER__)`
- L93 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__LINE__)`
- L101 _macro_ `#define OO_COMPILER_ASSERT(exp) static_assert(exp, "Assert " #exp)`
- L104 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L106 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L109 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L121 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L123 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L124 _macro_ `#define OOFUNC2 OOEXPLINK`
- L125 _macro_ `#define OOFUNCSTART`
- L126 _macro_ `#define OODLE_CALLBACK OOLINK`
- L134 _macro_ `#define NULL (0)`
- L138 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L140 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L145 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L150 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L153 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L159 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Runtime/OodleDataCompression/Sdks/2.9.16/include/oodle2.h` (Other)


#### enum `OodleLZ_Verbosity`  
`typedef enum OodleLZ_Verbosity`  
_L48-55_
- desc: Default verbosity selection of 0 will not even log when it sees corruption
- L50 _public enumerator_ `OodleLZ_Verbosity_None = 0`
- L51 _public enumerator_ `OodleLZ_Verbosity_Minimal = 1`
- L52 _public enumerator_ `OodleLZ_Verbosity_Some = 2`
- L53 _public enumerator_ `OodleLZ_Verbosity_Lots = 3`
- L54 _public enumerator_ `OodleLZ_Verbosity_Force32 = 0x40000000`

#### enum `OodleLZ_Compressor`  
`typedef enum OodleLZ_Compressor`  
_L63-88_
- L65 _public enumerator_ `OodleLZ_Compressor_Invalid = -1`
- L66 _public enumerator_ `OodleLZ_Compressor_None = 3` — None = memcpy, pass through uncompressed bytes
- L69 _public enumerator_ `OodleLZ_Compressor_Kraken = 8` — NEW COMPRESSORS :
- L70 _public enumerator_ `OodleLZ_Compressor_Leviathan = 13` — Leviathan = Kraken's big brother with higher compression, slightly slower decompression.
- L71 _public enumerator_ `OodleLZ_Compressor_Mermaid = 9` — Mermaid is between Kraken & Selkie - crazy fast, still decent compression.
- L72 _public enumerator_ `OodleLZ_Compressor_Selkie = 11` — Selkie is a super-fast relative of Mermaid.  For maximum decode speed.
- L73 _public enumerator_ `OodleLZ_Compressor_Hydra = 12` — Hydra, the many-headed beast = Leviathan, Kraken, Mermaid, or Selkie (see $OodleLZ_About_Hydra)
- L76 _public enumerator_ `OodleLZ_Compressor_BitKnit = 10` — no longer supported as of Oodle 2.9.0
- L77 _public enumerator_ `OodleLZ_Compressor_LZB16 = 4` — DEPRECATED but still supported
- L78 _public enumerator_ `OodleLZ_Compressor_LZNA = 7` — no longer supported as of Oodle 2.9.0
- L79 _public enumerator_ `OodleLZ_Compressor_LZH = 0` — no longer supported as of Oodle 2.9.0
- L80 _public enumerator_ `OodleLZ_Compressor_LZHLW = 1` — no longer supported as of Oodle 2.9.0
- L81 _public enumerator_ `OodleLZ_Compressor_LZNIB = 2` — no longer supported as of Oodle 2.9.0
- L82 _public enumerator_ `OodleLZ_Compressor_LZBLW = 5` — no longer supported as of Oodle 2.9.0
- L83 _public enumerator_ `OodleLZ_Compressor_LZA = 6` — no longer supported as of Oodle 2.9.0
- L86 _public enumerator_ `OodleLZ_Compressor_Count = 14`
- L87 _public enumerator_ `OodleLZ_Compressor_Force32 = 0x40000000`

#### enum `OodleLZ_PackedRawOverlap`  
`typedef enum OodleLZ_PackedRawOverlap`  
_L111-116_
- L113 _public enumerator_ `OodleLZ_PackedRawOverlap_No = 0`
- L114 _public enumerator_ `OodleLZ_PackedRawOverlap_Yes = 1`
- L115 _public enumerator_ `OodleLZ_PackedRawOverlap_Force32 = 0x40000000`

#### enum `OodleLZ_CheckCRC`  
`typedef enum OodleLZ_CheckCRC`  
_L120-125_
- L122 _public enumerator_ `OodleLZ_CheckCRC_No = 0`
- L123 _public enumerator_ `OodleLZ_CheckCRC_Yes = 1`
- L124 _public enumerator_ `OodleLZ_CheckCRC_Force32 = 0x40000000`

#### enum `OodleLZ_Profile`  
`typedef enum OodleLZ_Profile`  
_L138-143_
- L140 _public enumerator_ `OodleLZ_Profile_Main=0` — Main profile (all current features allowed)
- L141 _public enumerator_ `OodleLZ_Profile_Reduced=1` — Reduced profile (Kraken only, limited feature set)
- L142 _public enumerator_ `OodleLZ_Profile_Force32 = 0x40000000`

#### enum `OodleDecompressCallbackRet`  
`typedef enum OodleDecompressCallbackRet`  
_L151-157_
- L153 _public enumerator_ `OodleDecompressCallbackRet_Continue=0`
- L154 _public enumerator_ `OodleDecompressCallbackRet_Cancel=1`
- L155 _public enumerator_ `OodleDecompressCallbackRet_Invalid=2`
- L156 _public enumerator_ `OodleDecompressCallbackRet_Force32 = 0x40000000`

#### enum `OodleLZ_CompressionLevel`  
`typedef enum OodleLZ_CompressionLevel`  
_L176-203_
- L178 _public enumerator_ `OodleLZ_CompressionLevel_None=0` — don't compress, just copy raw bytes
- L179 _public enumerator_ `OodleLZ_CompressionLevel_SuperFast=1` — super fast mode, lower compression ratio
- L180 _public enumerator_ `OodleLZ_CompressionLevel_VeryFast=2` — fastest LZ mode with still decent compression ratio
- L181 _public enumerator_ `OodleLZ_CompressionLevel_Fast=3` — fast - good for daily use
- L182 _public enumerator_ `OodleLZ_CompressionLevel_Normal=4` — standard medium speed LZ mode
- L184 _public enumerator_ `OodleLZ_CompressionLevel_Optimal1=5` — optimal parse level 1 (faster optimal encoder)
- L185 _public enumerator_ `OodleLZ_CompressionLevel_Optimal2=6` — optimal parse level 2 (recommended baseline optimal encoder)
- L186 _public enumerator_ `OodleLZ_CompressionLevel_Optimal3=7` — optimal parse level 3 (slower optimal encoder)
- L187 _public enumerator_ `OodleLZ_CompressionLevel_Optimal4=8` — optimal parse level 4 (very slow optimal encoder)
- L188 _public enumerator_ `OodleLZ_CompressionLevel_Optimal5=9` — optimal parse level 5 (don't care about encode speed, maximum compression)
- L190 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast1=-1` — faster than SuperFast, less compression
- L191 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast2=-2` — faster than HyperFast1, less compression
- L192 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast3=-3` — faster than HyperFast2, less compression
- L193 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast4=-4` — fastest, less compression
- L196 _public enumerator_ `OodleLZ_CompressionLevel_HyperFast=OodleLZ_CompressionLevel_HyperFast1` — aliases :
- L197 _public enumerator_ `OodleLZ_CompressionLevel_Optimal = OodleLZ_CompressionLevel_Optimal2` — alias optimal standard level
- L198 _public enumerator_ `OodleLZ_CompressionLevel_Max = OodleLZ_CompressionLevel_Optimal5` — maximum compression level
- L199 _public enumerator_ `OodleLZ_CompressionLevel_Min = OodleLZ_CompressionLevel_HyperFast4` — fastest compression level
- L201 _public enumerator_ `OodleLZ_CompressionLevel_Force32 = 0x40000000`
- L202 _public enumerator_ `OodleLZ_CompressionLevel_Invalid = OodleLZ_CompressionLevel_Force32`

#### enum `OodleLZ_Jobify`  
`typedef enum OodleLZ_Jobify`  
_L234-243_
- L236 _public enumerator_ `OodleLZ_Jobify_Default=0` — Use compressor default for level of internal job usage
- L237 _public enumerator_ `OodleLZ_Jobify_Disable=1` — Don't use jobs at all
- L238 _public enumerator_ `OodleLZ_Jobify_Normal=2` — Try to balance parallelism with increased memory usage
- L239 _public enumerator_ `OodleLZ_Jobify_Aggressive=3` — Maximize parallelism even when doing so requires large amounts of memory
- L240 _public enumerator_ `OodleLZ_Jobify_Count=4`
- L242 _public enumerator_ `OodleLZ_Jobify_Force32 = 0x40000000`

#### enum `OodleLZ_Decode_ThreadPhase`  
`typedef enum OodleLZ_Decode_ThreadPhase`  
_L397-403_
- L399 _public enumerator_ `OodleLZ_Decode_ThreadPhase1 = 1`
- L400 _public enumerator_ `OodleLZ_Decode_ThreadPhase2 = 2`
- L401 _public enumerator_ `OodleLZ_Decode_ThreadPhaseAll = 3`
- L402 _public enumerator_ `OodleLZ_Decode_Unthreaded = OodleLZ_Decode_ThreadPhaseAll`

#### enum `OodleLZ_FuzzSafe`  
`typedef enum OodleLZ_FuzzSafe`  
_L413-417_
- L415 _public enumerator_ `OodleLZ_FuzzSafe_No = 0`
- L416 _public enumerator_ `OodleLZ_FuzzSafe_Yes = 1`

#### enum `OodleLZSeekTable_Flags`  
`typedef enum OodleLZSeekTable_Flags`  
_L488-493_
- L490 _public enumerator_ `OodleLZSeekTable_Flags_None = 0` — default
- L491 _public enumerator_ `OodleLZSeekTable_Flags_MakeRawCRCs = 1` — make the _rawCRCs_ member of $OodleLZ_SeekTable
- L492 _public enumerator_ `OodleLZSeekTable_Flags_Force32 = 0x40000000`

#### enum `Oodle_UsageWarnings`  
`typedef enum Oodle_UsageWarnings`  
_L542-547_
- L544 _public enumerator_ `Oodle_UsageWarnings_Enabled = 0`
- L545 _public enumerator_ `Oodle_UsageWarnings_Disabled = 1`
- L546 _public enumerator_ `Oodle_UsageWarnings_Force32 = 0x40000000`

#### enum `OodleLZ_CompressScratchMemBoundType`  
`typedef enum OodleLZ_CompressScratchMemBoundType`  
_L1421-1427_
- L1423 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_WorstCase = 0` — Worst-case memory use estimate
- L1424 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_Typical = 1` — Typical memory use estimate; with this much scratch memory, allocations might still happen, but rarely.
- L1426 _public enumerator_ `OodleLZ_CompressScratchMemBoundType_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2_H_INCLUDED__`
- L11 _macro_ `#define OODLE2_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2_VERSION_MINOR 16`
- L34 _macro_ `#define OodleVersion "2.9.16" /*`
- L55 _typedef_ `} OodleLZ_Verbosity;`
- L88 _typedef_ `} OodleLZ_Compressor;`
- L116 _typedef_ `} OodleLZ_PackedRawOverlap;`
- L125 _typedef_ `} OodleLZ_CheckCRC;`
- L143 _typedef_ `} OodleLZ_Profile;`
- L147 _macro_ `#define OodleLZ_Profile_Internal_Custom ((OodleLZ_Profile)100)` — Not flagged for idoc and done using a #define since it's internal (testing) use only
- L157 _typedef_ `} OodleDecompressCallbackRet;`
- L162 _typedef_ `OODEFFUNC typedef OodleDecompressCallbackRet (OODLE_CALLBACK OodleDecompressCallback)(void * userdata, const OO_U8 * rawBuf,OO_SINTa rawLen,const OO_U8 * compBuf,OO_SINTa compBufferSize , OO_SINTa rawDone, OO_SINTa compUsed);`
- L203 _typedef_ `} OodleLZ_CompressionLevel;`
- L243 _typedef_ `OodleLZ_Jobify_Force32 = 0x40000000, } OodleLZ_Jobify;`
- L269 _macro_ `#define OODLELZ_LOCALDICTIONARYSIZE_MAX (1<<30) /* Maximum value of maxLocalDictionarySize in OodleLZ_CompressOptions`
- L272 _macro_ `#define OODLELZ_SPACESPEEDTRADEOFFBYTES_DEFAULT (256) /* Default value of spaceSpeedTradeoffBytes in OodleLZ_CompressOptions`
- L303 _typedef_ `} OodleLZ_CompressOptions;`
- L403 _typedef_ `} OodleLZ_Decode_ThreadPhase;`
- L417 _typedef_ `} OodleLZ_FuzzSafe;`
- L432 _macro_ `#define OODLELZ_BLOCK_LEN (1<<18) /* The number of raw bytes per "seek chunk"`
- L436 _macro_ `#define OODLELZ_BLOCK_MAXIMUM_EXPANSION (2)`
- L437 _macro_ `#define OODLELZ_BLOCK_MAX_COMPLEN (OODLELZ_BLOCK_LEN+OODLELZ_BLOCK_MAXIMUM_EXPANSION) /* Maximum expansion per $OODLELZ_BLOCK_LEN is 1 byte.`
- L441 _macro_ `#define OODLELZ_QUANTUM_LEN (1<<14) /* Minimum decompression quantum (for old legacy codecs only)`
- L450 _macro_ `#define OODLELZ_QUANTUM_MAXIMUM_EXPANSION (5)` — 5 byte expansion per-quantum with CRC's
- L452 _macro_ `#define OODLELZ_QUANTUM_MAX_COMPLEN (OODLELZ_QUANTUM_LEN+OODLELZ_QUANTUM_MAXIMUM_EXPANSION)`
- L454 _macro_ `#define OODLELZ_SEEKCHUNKLEN_MIN OODLELZ_BLOCK_LEN`
- L455 _macro_ `#define OODLELZ_SEEKCHUNKLEN_MAX (1<<29) // half GB`
- L465 _typedef_ `} OodleLZ_DecodeSome_Out;`
- L486 _typedef_ `} OodleLZ_SeekTable;`
- L493 _typedef_ `} OodleLZSeekTable_Flags;`
- L510 _typedef_ `} OodleConfigValues;`
- L518 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_GetConfigValues(OodleConfigValues * ptr);`
- L528 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_SetConfigValues(const OodleConfigValues * ptr);`
- L547 _typedef_ `} Oodle_UsageWarnings;`
- L550 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_SetUsageWarnings(Oodle_UsageWarnings state);`
- L564 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleCore_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L577 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_Free)( void * ptr );`
- L584 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetAllocators( t_fp_OodleCore_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleCore_Plugin_Free * fp_OodleFree);`
- L606 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleCore_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L628 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L648 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetJobSystem( t_fp_OodleCore_Plugin_RunJob * fp_RunJob, t_fp_OodleCore_Plugin_WaitJob * fp_WaitJob);`
- L657 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugins_SetJobSystemAndCount( t_fp_OodleCore_Plugin_RunJob * fp_RunJob, t_fp_OodleCore_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L696 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleCore_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L709 _prototype_ `OOFUNC1 t_fp_OodleCore_Plugin_Printf * OOFUNC2 OodleCore_Plugins_SetPrintf(t_fp_OodleCore_Plugin_Printf * fp_rrRawPrintf);`
- L728 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleCore_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L744 _prototype_ `OOFUNC1 t_fp_OodleCore_Plugin_DisplayAssertion * OOFUNC2 OodleCore_Plugins_SetAssertion(t_fp_OodleCore_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L763 _prototype_ `OOFUNC1 void * OOFUNC2 OodleCore_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L764 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Free_Default(void * ptr);`
- L765 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L767 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleCore_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L768 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleCore_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 void OOFUNC2 OodleCore_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L776 _macro_ `#define OODLELZ_FAILED (0) /* Return value of OodleLZ_Decompress on failure`
- L927 _typedef_ `typedef struct _OodleLZDecoder OodleLZDecoder;`
- L934 _prototype_ `OOFUNC1 OodleLZDecoder * OOFUNC2 OodleLZDecoder_Create(OodleLZ_Compressor compressor,OO_S64 rawLen,void * memory, OO_SINTa memorySize);`
- L975 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_ThreadPhased_BlockDecoderMemorySizeNeeded(void);`
- L982 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZDecoder_Destroy(OodleLZDecoder * decoder);`
- L1008 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZDecoder_DecodeSome( OodleLZDecoder * decoder, OodleLZ_DecodeSome_Out * out,` — returns false if corruption detected
- L1096 _macro_ `#define OODLELZ_SEEKPOINTCOUNT_DEFAULT 16`
- L1098 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_MakeSeekChunkLen(OO_S64 rawLen, OO_S32 desiredSeekPointCount);`
- L1111 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_GetNumSeekChunks(OO_S64 rawLen, OO_S32 seekChunkLen);`
- L1121 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetSeekTableMemorySizeNeeded(OO_S32 numSeekChunks,OodleLZSeekTable_Flags flags);`
- L1135 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZ_FillSeekTable(OodleLZ_SeekTable * pTable,OodleLZSeekTable_Flags flags,OO_S32 seekChunkLen,const void * rawBuf, OO_SINTa rawLen,const void * compBuf,OO_SINTa compLen);`
- L1154 _prototype_ `OOFUNC1 OodleLZ_SeekTable * OOFUNC2 OodleLZ_CreateSeekTable(OodleLZSeekTable_Flags flags,OO_S32 seekChunkLen,const void * rawBuf, OO_SINTa rawLen,const void * compBuf,OO_SINTa compLen);`
- L1172 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZ_FreeSeekTable(OodleLZ_SeekTable * pTable);`
- L1176 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleLZ_CheckSeekTableCRCs(const void * rawBuf,OO_SINTa rawLen, const OodleLZ_SeekTable * seekTable);`
- L1193 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleLZ_FindSeekEntry( OO_S64 rawPos, const OodleLZ_SeekTable * seekTable);`
- L1203 _prototype_ `OOFUNC1 OO_S64 OOFUNC2 OodleLZ_GetSeekEntryPackedPos( OO_S32 seekI , const OodleLZ_SeekTable * seekTable );`
- L1215 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_CompressionLevel_GetName(OodleLZ_CompressionLevel compressSelect);`
- L1219 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_Compressor_GetName(OodleLZ_Compressor compressor);`
- L1223 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleLZ_Jobify_GetName(OodleLZ_Jobify jobify);`
- L1227 _prototype_ `OOFUNC1 const OodleLZ_CompressOptions * OOFUNC2 OodleLZ_CompressOptions_GetDefault( OodleLZ_Compressor compressor OODEFAULT(OodleLZ_Compressor_Invalid), OodleLZ_CompressionLevel lzLevel OODEFAULT(OodleLZ_CompressionLevel_Normal));`
- L1240 _prototype_ `OOFUNC1 void OOFUNC2 OodleLZ_CompressOptions_Validate(OodleLZ_CompressOptions * pOptions);` — after you fiddle with options, call this to ensure they are allowed
- L1248 _prototype_ `OO_BOOL OodleLZ_Compressor_UsesWholeBlockQuantum(OodleLZ_Compressor compressor);`
- L1254 _prototype_ `OO_BOOL OodleLZ_Compressor_UsesLargeWindow(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor is "whole block quantum" ; must decode in steps of $OODLELZ_BLOCK_LEN , not $OODLELZ_QUANTUM_LEN like others.
- L1260 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeInCircularWindow(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor is "LargeWindow" or not, meaning it can benefit from a Long-Range-Matcher and windows larger than $OODLELZ_BLOCK_LEN
- L1266 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeThreadPhased(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be decoded using a fixed size circular window. deprecated as of 2.9.0
- L1273 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeInPlace(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be used with the $OodleLZ_Decode_ThreadPhase. See $OodleLZ_About_ThreadPhasedDecode
- L1284 _prototype_ `OO_BOOL OodleLZ_Compressor_MustDecodeWithoutResets(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor can be used with "in-place" decoding. This is now always true (all compressors support in-place decoding).  The function is left for backward compatibility. All compressors in the future will support in-place, you don't need to check this property.
- L1298 _prototype_ `OO_BOOL OodleLZ_Compressor_CanDecodeFuzzSafe(OodleLZ_Compressor compressor);` — OodleLZ_Compressor properties helper. Tells you if this compressor must decode contiguous ranges of buffer with the same Decoder. That is, most of the compressors can be Reset and restart on any block, not just seek blocks, as long as the correct window data is provided.  That is, if this returns false then the only state required across a non-reset block is the dictionary of previously decoded data. But if OodleLZ_Compressor_MustDecodeWithoutResets returns true, then you cannot do that, because the Decoder object must carry state across blocks (except reset blocks). This does not apply to seek points - you can always reset and restart decompression at a seek point.
- L1305 _prototype_ `OO_BOOL OodleLZ_Compressor_RespectsDictionarySize(OodleLZ_Compressor compressor);`
- L1315 _macro_ `#define OODLELZ_COMPRESSOR_MASK(c) (((OO_U32)1)<<((OO_S32)(c)))`
- L1317 _macro_ `#define OODLELZ_COMPRESSOR_BOOLBIT(s,c) (((s)>>(OO_S32)(c))&1)` — OODLELZ_COMPRESSOR_BOOLBIT : extract a value of 1 or 0 so it maps to "bool"
- L1319 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_IsNewLZFamily(OodleLZ_Compressor compressor)`
- L1330 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeFuzzSafe(OodleLZ_Compressor compressor)`
- L1349 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_RespectsDictionarySize(OodleLZ_Compressor compressor)`
- L1368 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_UsesWholeBlockQuantum(OodleLZ_Compressor compressor)`
- L1373 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeThreadPhased(OodleLZ_Compressor compressor)`
- L1378 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeInPlace(OodleLZ_Compressor compressor)`
- L1384 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_CanDecodeInCircularWindow(OodleLZ_Compressor compressor)`
- L1392 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_UsesLargeWindow(OodleLZ_Compressor compressor)`
- L1398 _function_ `OOINLINEFUNC OO_BOOL OodleLZ_Compressor_MustDecodeWithoutResets(OodleLZ_Compressor compressor)`
- L1417 _macro_ `#define OODLELZ_SCRATCH_MEM_NO_BOUND (-1) /* Scratch mem size when bound is unknown.`
- L1427 _typedef_ `OodleLZ_CompressScratchMemBoundType_Force32 = 0x40000000, } OodleLZ_CompressScratchMemBoundType;`
- L1442 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressScratchMemBound( OodleLZ_Compressor compressor, OodleLZ_CompressionLevel level, OO_SINTa rawLen, const OodleLZ_CompressOptions * pOptions OODEFAULT(NULL) );`
- L1472 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressScratchMemBoundEx( OodleLZ_Compressor compressor, OodleLZ_CompressionLevel level, OodleLZ_CompressScratchMemBoundType boundType, OO_SINTa rawLen, const OodleLZ_CompressOptions * pOptions OODEFAULT(NULL) );`
- L1510 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressedBufferSizeNeeded(OodleLZ_Compressor compressor,OO_SINTa rawSize);` — get maximum expanded size for compBuf alloc : (note this is actually larger than the maximum compressed stream, it includes trash padding)
- L1525 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetDecodeBufferSize(OodleLZ_Compressor compressor,OO_SINTa rawSize,OO_BOOL corruptionPossible);` — decBuf needs to be a little larger than rawLen, this will tell you exactly how much :
- L1560 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetInPlaceDecodeBufferSize(OodleLZ_Compressor compressor,OO_SINTa compLen, OO_SINTa rawLen);` — OodleLZ_GetInPlaceDecodeBufferSize : after compressing, ask how big the in-place buffer needs to be
- L1583 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleLZ_GetCompressedStepForRawStep( const void * compPtr, OO_SINTa compAvail, OO_SINTa startRawPos, OO_SINTa rawSeekBytes, OO_SINTa * pEndRawPos OODEFAULT(NULL), OO_BOOL * pIndependent OODEFAULT(NULL) );` — GetCompressedStepForRawStep is at OODLELZ_QUANTUM_LEN granularity returns how many packed bytes to step to get the desired raw count step
- L1619 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetAllChunksCompressor(const void * compBuf,OO_SINTa compBufSize, OO_SINTa rawLen);`
- L1642 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetFirstChunkCompressor(const void * compChunkPtr, OO_SINTa compBufAvail, OO_BOOL * pIndependent);`
- L1662 _prototype_ `OOFUNC1 OodleLZ_Compressor OOFUNC2 OodleLZ_GetChunkCompressor(const void * compChunkPtr, OO_SINTa compBufAvail, OO_BOOL * pIndependent);`
- L1673 _macro_ `#define OODLE_HEADER_VERSION ((46<<24)|(OODLE2_VERSION_MAJOR<<16)|(OODLE2_VERSION_MINOR<<8)|(OO_U32)sizeof(OodleLZ_SeekTable)) /* OODLE_HEADER_VERSION is used to ensure the Oodle header matches the lib. Don't copy the value of this macro, i`
- L1679 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 Oodle_CheckVersion(OO_U32 oodle_header_version, OO_U32 * pOodleLibVersion OODEFAULT(NULL));`
- L1690 _prototype_ `OOFUNC1 void OOFUNC2 Oodle_LogHeader(void);`
- L1697 _macro_ `#define OODLECORE_PLUGIN_JOB_MAX_DEPENDENCIES OODLE_JOB_MAX_DEPENDENCIES` — define old names so they still compile :
- L1698 _macro_ `#define t_fp_OodleCore_Plugin_Job t_fp_Oodle_Job`

### `Source/Runtime/OodleDataCompression/Sdks/2.9.16/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2026, Epic Games Tools LLC"`
- L29 _typedef_ `typedef int8_t OO_S8;` — Typedefs
- L30 _typedef_ `typedef uint8_t OO_U8;`
- L31 _typedef_ `typedef int16_t OO_S16;`
- L32 _typedef_ `typedef uint16_t OO_U16;`
- L33 _typedef_ `typedef int32_t OO_S32;`
- L34 _typedef_ `typedef uint32_t OO_U32;`
- L35 _typedef_ `typedef int64_t OO_S64;`
- L36 _typedef_ `typedef uint64_t OO_U64;`
- L37 _typedef_ `typedef float OO_F32;`
- L38 _typedef_ `typedef double OO_F64;`
- L39 _typedef_ `typedef intptr_t OO_SINTa;`
- L40 _typedef_ `typedef uintptr_t OO_UINTa;`
- L41 _typedef_ `typedef int32_t OO_BOOL;`
- L45 _macro_ `#define OOSTRUCT struct __attribute__((__packed__))`
- L46 _macro_ `#define OOINLINEFUNC inline`
- L49 _macro_ `#define OOSTRUCT struct` — on VC++, we use pragmas for the struct packing
- L50 _macro_ `#define OOINLINEFUNC __inline`
- L55 _macro_ `#define OOLINK __stdcall`
- L56 _macro_ `#define OOEXPLINK __stdcall`
- L58 _macro_ `#define OOLINK`
- L59 _macro_ `#define OOEXPLINK`
- L64 _macro_ `#define OODEFFUNC extern "C"`
- L65 _macro_ `#define OODEFSTART extern "C" {`
- L66 _macro_ `#define OODEFEND }`
- L67 _macro_ `#define OODEFAULT( val ) =val`
- L69 _macro_ `#define OODEFFUNC`
- L70 _macro_ `#define OODEFSTART`
- L71 _macro_ `#define OODEFEND`
- L72 _macro_ `#define OODEFAULT( val )`
- L77 _macro_ `#define OOEXPFUNC OODEFFUNC` — Exported function declarations
- L81 _macro_ `#define OO_STRING_JOIN(arg1, arg2) OO_STRING_JOIN_DELAY(arg1, arg2)` — OO_STRING_JOIN joins strings in the preprocessor and works with LINESTRING
- L82 _macro_ `#define OO_STRING_JOIN_DELAY(arg1, arg2) OO_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L83 _macro_ `#define OO_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L91 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__COUNTER__)`
- L93 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__LINE__)`
- L101 _macro_ `#define OO_COMPILER_ASSERT(exp) static_assert(exp, "Assert " #exp)`
- L104 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L106 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L109 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L121 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L123 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L124 _macro_ `#define OOFUNC2 OOEXPLINK`
- L125 _macro_ `#define OOFUNCSTART`
- L126 _macro_ `#define OODLE_CALLBACK OOLINK`
- L134 _macro_ `#define NULL (0)`
- L138 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L140 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L145 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L150 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L153 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L159 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`
