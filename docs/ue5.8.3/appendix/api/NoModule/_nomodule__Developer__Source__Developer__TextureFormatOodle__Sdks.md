# NoModule / _nomodule__Developer__Source__Developer__TextureFormatOodle__Sdks

- module root: `.`
- headers: 25; symbols: 2878
- symbol kinds: enum=119, enumerator=1240, function=2, macro=618, prototype=470, typedef=429

### `Source/Developer/TextureFormatOodle/Sdks/2.9.10/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2023, Epic Games Tools LLC"`
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
- L101 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L103 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L106 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L117 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L119 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L120 _macro_ `#define OOFUNC2 OOEXPLINK`
- L121 _macro_ `#define OOFUNCSTART`
- L122 _macro_ `#define OODLE_CALLBACK OOLINK`
- L130 _macro_ `#define NULL (0)`
- L134 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L136 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L141 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L146 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L149 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L155 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.10/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-73_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L72 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L83-111_
- L85 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L86 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L87 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L88 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L89 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L91 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L92 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L93 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L94 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L96 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L98 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L100 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L104 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L105 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L106 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L109 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L110 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L146-163_
- L148 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L149 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L150 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L151 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L152 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L153 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L154 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L155 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L156 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L157 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L158 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L159 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L160 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L161 _public enumerator_ `OodleTex_BC_Max = 12`
- L162 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L255-262_
- L257 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L258 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L259 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L260 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L261 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L283-294_
- L285 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L286 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L287 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L288 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L331-341_
- L333 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L334 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L335 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L336 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L337 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L338 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L339 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats
- L340 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L375-380_
- L377 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L378 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L379 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L388-395_
- L390 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L391 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L392 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L393 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L394 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L426-433_
- L428 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L429 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L430 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L431 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L432 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L465-469_
- L467 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L468 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 10`
- L34 _macro_ `#define OodleTextureVersion "2.9.10" /*`
- L73 _typedef_ `} OodleTex_Err;`
- L111 _typedef_ `} OodleTex_PixelFormat;`
- L163 _typedef_ `} OodleTex_BC;`
- L224 _typedef_ `} OodleTex_Surface;`
- L242 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 16384 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).`
- L248 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L262 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L294 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L341 _typedef_ `} OodleTex_BCNFlags;`
- L380 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L395 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L433 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L469 _typedef_ `} OodleTex_RDO_Flags;`
- L488 _typedef_ `} OodleTex_RDO_Options;`
- L521 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L526 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L534 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L558 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L571 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L578 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L600 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L622 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L642 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L651 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L690 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L703 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L722 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L738 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L757 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L758 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L759 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L760 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L761 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L762 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L763 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L778 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L782 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L786 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L790 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L794 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L803 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L811 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L819 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L859 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L897 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L960 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1017 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1042 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1059 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1096 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1121 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1126 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1133 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1140 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1145 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1150 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1180 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1225 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1229 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1258 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1299 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1330 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1398 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.11/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2023, Epic Games Tools LLC"`
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

### `Source/Developer/TextureFormatOodle/Sdks/2.9.11/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-73_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L72 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L83-111_
- L85 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L86 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L87 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L88 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L89 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L91 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L92 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L93 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L94 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L96 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L98 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L100 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L104 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L105 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L106 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L109 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L110 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L146-163_
- L148 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L149 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L150 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L151 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L152 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L153 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L154 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L155 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L156 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L157 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L158 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L159 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L160 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L161 _public enumerator_ `OodleTex_BC_Max = 12`
- L162 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L255-262_
- L257 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L258 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L259 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L260 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L261 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L283-294_
- L285 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L286 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L287 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L288 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L331-341_
- L333 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L334 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L335 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L336 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L337 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L338 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L339 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats
- L340 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L375-380_
- L377 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L378 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L379 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L388-395_
- L390 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L391 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L392 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L393 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L394 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L426-433_
- L428 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L429 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L430 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L431 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L432 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L465-469_
- L467 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L468 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 11`
- L34 _macro_ `#define OodleTextureVersion "2.9.11" /*`
- L73 _typedef_ `} OodleTex_Err;`
- L111 _typedef_ `} OodleTex_PixelFormat;`
- L163 _typedef_ `} OodleTex_BC;`
- L224 _typedef_ `} OodleTex_Surface;`
- L242 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 16384 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).`
- L248 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L262 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L294 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L341 _typedef_ `} OodleTex_BCNFlags;`
- L380 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L395 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L433 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L469 _typedef_ `} OodleTex_RDO_Flags;`
- L488 _typedef_ `} OodleTex_RDO_Options;`
- L521 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L526 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L534 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L558 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L571 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L578 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L600 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L622 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L642 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L651 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L690 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L703 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L722 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L738 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L757 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L758 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L759 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L760 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L761 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L762 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L763 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L778 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L782 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L786 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L790 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L794 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L803 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L811 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L819 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L859 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L897 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L960 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1017 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1042 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1059 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1096 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1121 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1126 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1133 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1140 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1145 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1150 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1180 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1225 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1229 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1258 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1299 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1330 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1398 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.12/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2024, Epic Games Tools LLC"`
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

### `Source/Developer/TextureFormatOodle/Sdks/2.9.12/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-74_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L71 _public enumerator_ `OodleTex_Err_BadSurfaceCount = -26` — Oodle Texture invocations accept between 0 and at most $OODLETEX_MAX_SURFACE_COUNT per invocation.
- L73 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L84-112_
- L86 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L87 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L88 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L89 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L91 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L92 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L93 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L94 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L96 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L98 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L100 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L103 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L105 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L106 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L108 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L110 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L111 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L147-164_
- L149 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L150 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L151 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L152 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L153 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L154 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L155 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L156 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L157 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L158 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L159 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L160 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L161 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L162 _public enumerator_ `OodleTex_BC_Max = 12`
- L163 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L261-268_
- L263 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L264 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L265 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L266 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L267 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L289-300_
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L294 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L295 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L296 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L297 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L298 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L299 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L337-347_
- L339 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L340 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L341 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L342 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L343 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L344 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L345 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats
- L346 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L381-386_
- L383 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L384 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L385 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L394-401_
- L396 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L397 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L398 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L399 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L400 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L432-439_
- L434 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L435 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L436 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L437 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L438 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L471-475_
- L473 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L474 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 12`
- L34 _macro_ `#define OodleTextureVersion "2.9.12" /*`
- L74 _typedef_ `} OodleTex_Err;`
- L112 _typedef_ `} OodleTex_PixelFormat;`
- L164 _typedef_ `} OodleTex_BC;`
- L225 _typedef_ `} OodleTex_Surface;`
- L244 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 2097152 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).` — NOTE: limiter for surface dimension and count is BlockLocation8 internals
- L249 _macro_ `#define OODLETEX_MAX_SURFACE_COUNT 2097152 /* Maximum number of OodleTex_Surfaces passed to a single Oodle Texture invocation.`
- L254 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L268 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L300 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L347 _typedef_ `} OodleTex_BCNFlags;`
- L386 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L401 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L439 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L475 _typedef_ `} OodleTex_RDO_Flags;`
- L494 _typedef_ `} OodleTex_RDO_Options;`
- L527 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L532 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L540 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L564 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L577 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L584 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L606 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L628 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L648 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L657 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L696 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L709 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L728 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L744 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L763 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L764 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L765 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L767 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L768 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L775 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L784 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L788 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L792 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L796 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L800 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L809 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L817 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L825 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L865 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L903 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L966 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1023 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1048 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1065 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1102 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1127 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1132 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1139 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1146 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1151 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1156 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1186 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1231 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1235 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1264 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1305 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1336 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1404 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.13/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2024, Epic Games Tools LLC"`
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

### `Source/Developer/TextureFormatOodle/Sdks/2.9.13/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-74_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L71 _public enumerator_ `OodleTex_Err_BadSurfaceCount = -26` — Oodle Texture invocations accept between 0 and at most $OODLETEX_MAX_SURFACE_COUNT per invocation.
- L73 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L84-112_
- L86 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L87 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L88 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L89 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A (most RGBA BCN formats accept this as input)
- L90 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A (only accepted as input for BC6H)
- L91 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L92 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L93 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L94 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L96 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L98 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L100 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L103 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L105 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L106 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G
- L108 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R
- L110 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L111 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L147-164_
- L149 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L150 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L151 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L152 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L153 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L154 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L155 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L156 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L157 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L158 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L159 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L160 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L161 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L162 _public enumerator_ `OodleTex_BC_Max = 12`
- L163 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L261-268_
- L263 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L264 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L265 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L266 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L267 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L287-298_
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L294 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L295 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L296 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L297 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L335-345_
- L337 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L338 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L339 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L340 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L341 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L342 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L343 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats. Applies to RGB only, A channel is always linear.
- L344 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L381-386_
- L383 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L384 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L385 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L394-401_
- L396 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L397 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L398 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L399 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L400 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L432-439_
- L434 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L435 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L436 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L437 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L438 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L471-475_
- L473 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L474 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 13`
- L34 _macro_ `#define OodleTextureVersion "2.9.13" /*`
- L74 _typedef_ `} OodleTex_Err;`
- L112 _typedef_ `} OodleTex_PixelFormat;`
- L164 _typedef_ `} OodleTex_BC;`
- L225 _typedef_ `} OodleTex_Surface;`
- L244 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 2097152 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).` — NOTE: limiter for surface dimension and count is BlockLocation8 internals
- L249 _macro_ `#define OODLETEX_MAX_SURFACE_COUNT 2097152 /* Maximum number of OodleTex_Surfaces passed to a single Oodle Texture invocation.`
- L254 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L268 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L298 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L345 _typedef_ `} OodleTex_BCNFlags;`
- L386 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L401 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L439 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L475 _typedef_ `} OodleTex_RDO_Flags;`
- L494 _typedef_ `} OodleTex_RDO_Options;`
- L527 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L532 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L540 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L564 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L577 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L584 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L606 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L628 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L648 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L657 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L696 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L709 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L728 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L744 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L763 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L764 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L765 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L767 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L768 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L775 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L784 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L788 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L792 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L796 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L800 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L809 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L817 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L825 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L865 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L903 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L966 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1023 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1048 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1065 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1102 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1127 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1132 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1139 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1146 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1151 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1156 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1186 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1231 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1235 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1264 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1305 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1336 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1404 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.14/include/oodle2base.h` (Other)


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

### `Source/Developer/TextureFormatOodle/Sdks/2.9.14/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-76_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L71 _public enumerator_ `OodleTex_Err_BadSurfaceCount = -26` — Oodle Texture invocations accept between 0 and at most $OODLETEX_MAX_SURFACE_COUNT per invocation.
- L73 _public enumerator_ `OodleTex_Err_Canceled = -27` — Operation was canceled
- L75 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L86-114_
- L88 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L89 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L91 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A (most RGBA BCN formats accept this as input)
- L92 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A (only accepted as input for BC6H)
- L93 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L94 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L95 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L96 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L98 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L99 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L100 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L102 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L103 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L104 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L105 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L107 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L108 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L109 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G
- L110 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R
- L112 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L113 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L149-166_
- L151 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L152 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L153 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L154 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L155 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L156 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L157 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L158 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L159 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L160 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L161 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L162 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L163 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L164 _public enumerator_ `OodleTex_BC_Max = 12`
- L165 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L263-270_
- L265 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L266 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L267 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L268 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L269 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L289-300_
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L294 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L295 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L296 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L297 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L298 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L299 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L337-347_
- L339 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L340 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L341 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L342 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L343 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L344 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L345 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats. Applies to RGB only, A channel is always linear.
- L346 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L383-388_
- L385 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L386 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L387 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L396-403_
- L398 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L399 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L400 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L401 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L402 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L434-441_
- L436 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L437 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L438 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L439 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L440 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L473-477_
- L475 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L476 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 14`
- L34 _macro_ `#define OodleTextureVersion "2.9.14" /*`
- L76 _typedef_ `} OodleTex_Err;`
- L114 _typedef_ `} OodleTex_PixelFormat;`
- L166 _typedef_ `} OodleTex_BC;`
- L227 _typedef_ `} OodleTex_Surface;`
- L246 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 2097152 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).` — NOTE: limiter for surface dimension and count is BlockLocation8 internals
- L251 _macro_ `#define OODLETEX_MAX_SURFACE_COUNT 2097152 /* Maximum number of OodleTex_Surfaces passed to a single Oodle Texture invocation.`
- L256 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L270 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L300 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L347 _typedef_ `} OodleTex_BCNFlags;`
- L388 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L403 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L441 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L477 _typedef_ `} OodleTex_RDO_Flags;`
- L496 _typedef_ `} OodleTex_RDO_Options;`
- L529 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L534 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L542 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L566 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L579 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L586 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L608 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L630 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L650 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L659 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L698 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L711 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L730 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L746 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L765 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L767 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L768 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L769 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L770 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L771 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L777 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L786 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L790 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L794 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L798 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L802 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L811 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L819 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L827 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L867 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L905 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L968 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1025 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1050 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1067 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1104 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1129 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1134 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1141 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1148 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1153 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1158 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1188 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1233 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1237 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1266 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1307 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1338 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1406 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`
- L1423 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_CancelRequested)(void * user_ptr);`
- L1435 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetCancelRequested(t_fp_OodleTex_Plugin_CancelRequested * fp_CancelRequested);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.15/include/oodle2base.h` (Other)


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

### `Source/Developer/TextureFormatOodle/Sdks/2.9.15/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-76_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L71 _public enumerator_ `OodleTex_Err_BadSurfaceCount = -26` — Oodle Texture invocations accept between 0 and at most $OODLETEX_MAX_SURFACE_COUNT per invocation.
- L73 _public enumerator_ `OodleTex_Err_Canceled = -27` — Operation was canceled
- L75 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L86-114_
- L88 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L89 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L91 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A (most RGBA BCN formats accept this as input)
- L92 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A (only accepted as input for BC6H)
- L93 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L94 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L95 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L96 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L98 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L99 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L100 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L102 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L103 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L104 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L105 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L107 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L108 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L109 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G
- L110 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R
- L112 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L113 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L149-166_
- L151 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L152 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L153 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L154 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L155 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L156 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L157 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L158 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L159 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L160 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L161 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L162 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L163 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L164 _public enumerator_ `OodleTex_BC_Max = 12`
- L165 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L263-270_
- L265 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L266 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L267 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L268 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L269 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L289-300_
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L294 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L295 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L296 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L297 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L298 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L299 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L337-347_
- L339 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L340 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L341 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L342 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L343 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L344 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L345 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats. Applies to RGB only, A channel is always linear.
- L346 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L383-388_
- L385 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L386 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L387 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L396-403_
- L398 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L399 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L400 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L401 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L402 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L434-441_
- L436 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L437 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L438 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L439 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L440 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L473-477_
- L475 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L476 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 15`
- L34 _macro_ `#define OodleTextureVersion "2.9.15" /*`
- L76 _typedef_ `} OodleTex_Err;`
- L114 _typedef_ `} OodleTex_PixelFormat;`
- L166 _typedef_ `} OodleTex_BC;`
- L227 _typedef_ `} OodleTex_Surface;`
- L246 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 2097152 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).` — NOTE: limiter for surface dimension and count is BlockLocation8 internals
- L251 _macro_ `#define OODLETEX_MAX_SURFACE_COUNT 2097152 /* Maximum number of OodleTex_Surfaces passed to a single Oodle Texture invocation.`
- L256 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L270 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L300 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L347 _typedef_ `} OodleTex_BCNFlags;`
- L388 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L403 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L441 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L477 _typedef_ `} OodleTex_RDO_Flags;`
- L496 _typedef_ `} OodleTex_RDO_Options;`
- L529 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L534 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L542 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L566 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L579 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L586 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L608 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L630 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L650 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L659 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L698 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L711 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L730 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L746 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L765 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L767 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L768 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L769 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L770 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L771 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L777 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L786 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L790 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L794 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L798 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L802 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L811 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L819 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L827 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L867 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L905 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L968 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1025 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1050 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1067 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1104 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1129 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1134 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1141 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1148 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1153 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1158 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1188 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1233 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1237 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1266 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1307 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1338 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1406 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`
- L1423 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_CancelRequested)(void * user_ptr);`
- L1435 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetCancelRequested(t_fp_OodleTex_Plugin_CancelRequested * fp_CancelRequested);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.16/include/oodle2base.h` (Other)


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

### `Source/Developer/TextureFormatOodle/Sdks/2.9.16/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-76_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L71 _public enumerator_ `OodleTex_Err_BadSurfaceCount = -26` — Oodle Texture invocations accept between 0 and at most $OODLETEX_MAX_SURFACE_COUNT per invocation.
- L73 _public enumerator_ `OodleTex_Err_Canceled = -27` — Operation was canceled
- L75 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L86-114_
- L88 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L89 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L91 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A (most RGBA BCN formats accept this as input)
- L92 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A (only accepted as input for BC6H)
- L93 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L94 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L95 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L96 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L98 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L99 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L100 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L102 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L103 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L104 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L105 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L107 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L108 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L109 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G
- L110 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R
- L112 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L113 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L149-166_
- L151 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L152 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L153 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L154 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L155 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L156 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L157 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L158 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L159 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L160 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L161 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L162 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L163 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L164 _public enumerator_ `OodleTex_BC_Max = 12`
- L165 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L263-270_
- L265 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L266 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L267 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L268 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L269 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L289-300_
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L294 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L295 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L296 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L297 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L298 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L299 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L337-347_
- L339 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L340 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L341 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L342 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L343 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L344 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L345 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats. Applies to RGB only, A channel is always linear.
- L346 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L383-388_
- L385 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L386 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L387 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L396-403_
- L398 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L399 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L400 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L401 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L402 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L434-441_
- L436 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L437 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L438 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L439 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L440 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L473-477_
- L475 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L476 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 16`
- L34 _macro_ `#define OodleTextureVersion "2.9.16" /*`
- L76 _typedef_ `} OodleTex_Err;`
- L114 _typedef_ `} OodleTex_PixelFormat;`
- L166 _typedef_ `} OodleTex_BC;`
- L227 _typedef_ `} OodleTex_Surface;`
- L246 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 2097152 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).` — NOTE: limiter for surface dimension and count is BlockLocation8 internals
- L251 _macro_ `#define OODLETEX_MAX_SURFACE_COUNT 2097152 /* Maximum number of OodleTex_Surfaces passed to a single Oodle Texture invocation.`
- L256 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L270 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L300 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L347 _typedef_ `} OodleTex_BCNFlags;`
- L388 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L403 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L441 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L477 _typedef_ `} OodleTex_RDO_Flags;`
- L496 _typedef_ `} OodleTex_RDO_Options;`
- L529 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L534 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L542 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L566 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L579 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L586 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L608 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L630 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L650 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L659 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L698 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L711 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L730 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L746 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L765 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L766 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L767 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L768 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L769 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L770 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L771 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L777 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L786 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L790 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L794 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L798 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L802 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L811 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L819 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L827 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L867 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L905 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L968 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1025 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1050 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1067 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1104 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1129 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1134 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1141 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1148 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1153 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1158 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1188 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1233 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1237 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1266 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1307 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1338 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1406 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`
- L1423 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_CancelRequested)(void * user_ptr);`
- L1435 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetCancelRequested(t_fp_OodleTex_Plugin_CancelRequested * fp_CancelRequested);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.16/include/oodle2texrt.h` (Other)


#### enum `OodleTexRT_Err`  
`typedef enum OodleTexRT_Err`  
_L37-53_
- L39 _public enumerator_ `OodleTexRT_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTexRT_Err_Internal = -101` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L42 _public enumerator_ `OodleTexRT_Err_BC7PrepHeaderCorrupt = -102` — BC7Prep header corrupted (or unsupported versin)
- L43 _public enumerator_ `OodleTexRT_Err_BC7PrepOutputBufTooSmall = -103` — BC7Prep output buffer too small for given block count
- L44 _public enumerator_ `OodleTexRT_Err_BC7PrepScratchBufTooSmall = -104` — BC7Prep scratch buffer too small for input data
- L45 _public enumerator_ `OodleTexRT_Err_BC7PrepPayloadCorrupt = -105` — BC7Prep payload data chunk was corrupted
- L46 _public enumerator_ `OodleTexRT_Err_BC7PrepInputTooSmall = -106` — BC7Prep input data to small for given header block count
- L47 _public enumerator_ `OodleTexRT_Err_BC7PrepTooManyBlocks = -107` — Too many blocks in a single BC7Prep blob for GPU decode (limits exist in some GPU variants)
- L49 _public enumerator_ `OodleTexRT_Err_GPU_OutOfShaderMem = -108` — Insufficient shader memory passed to GPU init
- L50 _public enumerator_ `OodleTexRT_Err_GPU_BadMemoryType = -109` — The given GPU resource memory type is not permitted in this context.
- L52 _public enumerator_ `OodleTexRT_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTexRT_BC7PrepDecodeFlags`  
`typedef enum OodleTexRT_BC7PrepDecodeFlags`  
_L94-101_
- L96 _public enumerator_ `OodleTexRT_BC7PrepDecodeFlags_None = 0` — No special processing.
- L97 _public enumerator_ `OodleTexRT_BC7PrepDecodeFlags_DestinationIsCached = 1` — Destination is in write-back cached memory.
- L98 _public enumerator_ `OodleTexRT_BC7PrepDecodeFlags_AvoidWideVectors = 2` — Avoid using wide (>=256b) vector instructions.
- L100 _public enumerator_ `OodleTexRT_BC7PrepDecodeFlags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEXRT_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEXRT_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEXRT_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEXRT_VERSION_MINOR 16`
- L34 _macro_ `#define OodleTextureRTVersion "2.9.16" /*`
- L53 _typedef_ `} OodleTexRT_Err;`
- L66 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L68 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10 /* Number of distinct mode streams in BC7Prep data.`
- L78 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L101 _typedef_ `} OodleTexRT_BC7PrepDecodeFlags;`
- L123 _function_ `static inline OodleTexRT_BC7PrepDecodeFlags operator |(const OodleTexRT_BC7PrepDecodeFlags a, const OodleTexRT_BC7PrepDecodeFlags b)` — Operator overload to enable ORing flags together in a type-safe manner in C++.
- L128 _function_ `static inline OodleTexRT_BC7PrepDecodeFlags& operator |=(OodleTexRT_BC7PrepDecodeFlags & a, const OodleTexRT_BC7PrepDecodeFlags b)`
- L137 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTexRT_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L150 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTexRT_Plugin_Free)( void * ptr );`
- L157 _prototype_ `OOFUNC1 void OOFUNC2 OodleTexRT_Plugins_SetAllocators( t_fp_OodleTexRT_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTexRT_Plugin_Free * fp_OodleFree);`
- L179 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTexRT_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L201 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTexRT_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L221 _prototype_ `OOFUNC1 void OOFUNC2 OodleTexRT_Plugins_SetJobSystem( t_fp_OodleTexRT_Plugin_RunJob * fp_RunJob, t_fp_OodleTexRT_Plugin_WaitJob * fp_WaitJob);`
- L230 _prototype_ `OOFUNC1 void OOFUNC2 OodleTexRT_Plugins_SetJobSystemAndCount( t_fp_OodleTexRT_Plugin_RunJob * fp_RunJob, t_fp_OodleTexRT_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L269 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTexRT_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L282 _prototype_ `OOFUNC1 t_fp_OodleTexRT_Plugin_Printf * OOFUNC2 OodleTexRT_Plugins_SetPrintf(t_fp_OodleTexRT_Plugin_Printf * fp_rrRawPrintf);`
- L301 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTexRT_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L317 _prototype_ `OOFUNC1 t_fp_OodleTexRT_Plugin_DisplayAssertion * OOFUNC2 OodleTexRT_Plugins_SetAssertion(t_fp_OodleTexRT_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L336 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTexRT_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L337 _prototype_ `OOFUNC1 void OOFUNC2 OodleTexRT_Plugin_Free_Default(void * ptr);`
- L338 _prototype_ `OOFUNC1 void OOFUNC2 OodleTexRT_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L339 _prototype_ `OOFUNC1 void OOFUNC2 OodleTexRT_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L340 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTexRT_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L341 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTexRT_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L342 _prototype_ `OOFUNC1 void OOFUNC2 OodleTexRT_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L348 _prototype_ `OOFUNC1 OodleTexRT_Err OOFUNC2 OodleTexRT_LogVersion();`
- L356 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTexRT_Err_GetName(OodleTexRT_Err error);`
- L364 _prototype_ `OOFUNC1 OodleTexRT_Err OOFUNC2 OodleTexRT_BC7Prep_ReadHeader(const OodleTexRT_BC7PrepHeader * header, OO_SINTa * out_num_blocks, OO_SINTa * out_payload_size);`
- L383 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTexRT_BC7Prep_MinDecodeScratchSize(OO_SINTa nblocks);`
- L400 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTexRT_BC7Prep_Decode(void * output_buf, OO_SINTa output_size, const void * bc7prep_data, OO_SINTa bc7prep_data_size, const OodleTexRT_BC7PrepHeader * header, OodleTexRT_BC7PrepDecodeFlags flags, void * scratch_buf, OO_SINTa scratch_size);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.5/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2021, Epic Games Tools LLC"`
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
- L101 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L103 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L106 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L117 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L119 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L120 _macro_ `#define OOFUNC2 OOEXPLINK`
- L121 _macro_ `#define OOFUNCSTART`
- L122 _macro_ `#define OODLE_CALLBACK OOLINK`
- L130 _macro_ `#define NULL (0)`
- L134 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L136 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L141 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L146 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L149 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L155 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.5/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-71_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L81-109_
- L83 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L84 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L85 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L86 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L87 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L88 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L89 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L90 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L91 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L92 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L93 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L94 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L96 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L97 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L98 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L100 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L103 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L104 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L105 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L108 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L144-161_
- L146 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L147 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L148 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L149 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L150 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L151 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L152 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L153 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L154 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L155 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L156 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L157 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L158 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L159 _public enumerator_ `OodleTex_BC_Max = 12`
- L160 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L253-260_
- L255 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L256 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L257 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L258 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L259 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L281-292_
- L283 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L284 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L285 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L286 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L287 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L288 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L329-335_
- L331 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L332 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — BC3-5: preserve 0 and 255 (0.0 and 1.0) exactly
- L333 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L334 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L353-360_
- L355 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L356 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L357 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L358 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L359 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L391-398_
- L393 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L394 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L395 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L396 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L397 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L430-434_
- L432 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L433 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 5`
- L34 _macro_ `#define OodleTextureVersion "2.9.5" /*`
- L71 _typedef_ `} OodleTex_Err;`
- L109 _typedef_ `} OodleTex_PixelFormat;`
- L161 _typedef_ `} OodleTex_BC;`
- L222 _typedef_ `} OodleTex_Surface;`
- L240 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 16384 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).`
- L246 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L260 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L292 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L335 _typedef_ `} OodleTex_BCNFlags;`
- L360 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L398 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L434 _typedef_ `} OodleTex_RDO_Flags;`
- L453 _typedef_ `} OodleTex_RDO_Options;`
- L486 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L491 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L499 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L523 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L536 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L543 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L565 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L587 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L607 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L616 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L655 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L668 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L687 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L703 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L722 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L723 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L724 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L725 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L726 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L727 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L728 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L734 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L743 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L747 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L751 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L755 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L759 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L768 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L776 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L784 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L824 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L862 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L925 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L982 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1008 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1048 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1053 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1060 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1067 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1072 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1077 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1107 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1152 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1156 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1185 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1226 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1257 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1325 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.6/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2022, Epic Games Tools LLC"`
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
- L101 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L103 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L106 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L117 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L119 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L120 _macro_ `#define OOFUNC2 OOEXPLINK`
- L121 _macro_ `#define OOFUNCSTART`
- L122 _macro_ `#define OODLE_CALLBACK OOLINK`
- L130 _macro_ `#define NULL (0)`
- L134 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L136 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L141 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L146 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L149 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L155 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.6/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-71_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L81-109_
- L83 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L84 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L85 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L86 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L87 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L88 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L89 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L90 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L91 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L92 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L93 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L94 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L96 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L97 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L98 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L100 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L103 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L104 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L105 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L108 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L144-161_
- L146 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L147 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L148 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L149 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L150 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L151 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L152 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L153 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L154 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L155 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L156 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L157 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L158 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L159 _public enumerator_ `OodleTex_BC_Max = 12`
- L160 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L253-260_
- L255 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L256 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L257 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L258 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L259 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L281-292_
- L283 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L284 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L285 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L286 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L287 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L288 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L329-337_
- L331 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L332 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — BC3-5: preserve 0 and 255 (0.0 and 1.0) exactly
- L333 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L334 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L335 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 4` — Prefer wide vector instruction sets
- L336 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L368-375_
- L370 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L371 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L372 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L373 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L374 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L406-413_
- L408 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L409 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L410 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L411 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L412 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L445-449_
- L447 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L448 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 6`
- L34 _macro_ `#define OodleTextureVersion "2.9.6" /*`
- L71 _typedef_ `} OodleTex_Err;`
- L109 _typedef_ `} OodleTex_PixelFormat;`
- L161 _typedef_ `} OodleTex_BC;`
- L222 _typedef_ `} OodleTex_Surface;`
- L240 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 16384 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).`
- L246 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L260 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L292 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L337 _typedef_ `} OodleTex_BCNFlags;`
- L375 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L413 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L449 _typedef_ `} OodleTex_RDO_Flags;`
- L468 _typedef_ `} OodleTex_RDO_Options;`
- L501 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L506 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L514 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L538 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L551 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L558 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L580 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L602 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L622 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L631 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L670 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L683 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L702 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L718 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L737 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L738 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L739 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L740 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L741 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L742 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L743 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L749 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L758 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L762 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L766 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L770 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L774 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L783 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L791 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L799 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L839 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L877 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L940 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L997 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1023 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1063 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1068 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1075 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1082 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1087 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1092 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1122 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1167 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1171 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1200 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1241 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1272 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1340 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.7/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2022, Epic Games Tools LLC"`
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
- L101 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L103 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L106 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L117 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L119 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L120 _macro_ `#define OOFUNC2 OOEXPLINK`
- L121 _macro_ `#define OOFUNCSTART`
- L122 _macro_ `#define OODLE_CALLBACK OOLINK`
- L130 _macro_ `#define NULL (0)`
- L134 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L136 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L141 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L146 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L149 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L155 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.7/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-71_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L81-109_
- L83 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L84 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L85 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L86 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L87 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L88 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L89 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L90 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L91 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L92 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L93 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L94 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L96 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L97 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L98 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L100 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L103 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L104 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L105 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L108 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L144-161_
- L146 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L147 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L148 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L149 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L150 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L151 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L152 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L153 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L154 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L155 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L156 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L157 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L158 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L159 _public enumerator_ `OodleTex_BC_Max = 12`
- L160 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L253-260_
- L255 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L256 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L257 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L258 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L259 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L281-292_
- L283 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L284 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L285 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L286 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L287 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L288 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L329-338_
- L331 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L332 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L333 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L334 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L335 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L336 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 4` — Prefer wide vector instruction sets
- L337 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L370-377_
- L372 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L373 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L374 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L375 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L376 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L408-415_
- L410 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L411 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L412 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L413 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L414 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L447-451_
- L449 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L450 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 7`
- L34 _macro_ `#define OodleTextureVersion "2.9.7" /*`
- L71 _typedef_ `} OodleTex_Err;`
- L109 _typedef_ `} OodleTex_PixelFormat;`
- L161 _typedef_ `} OodleTex_BC;`
- L222 _typedef_ `} OodleTex_Surface;`
- L240 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 16384 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).`
- L246 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L260 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L292 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L338 _typedef_ `} OodleTex_BCNFlags;`
- L377 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L415 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L451 _typedef_ `} OodleTex_RDO_Flags;`
- L470 _typedef_ `} OodleTex_RDO_Options;`
- L503 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L508 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L516 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L540 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L553 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L560 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L582 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L604 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L624 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L633 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L672 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L685 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L704 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L720 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L739 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L740 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L741 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L742 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L743 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L744 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L745 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L751 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L760 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L764 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L768 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L772 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L776 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L785 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L793 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L801 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L841 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L879 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L942 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L999 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1025 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1065 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1070 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1077 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1084 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1089 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1094 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1124 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1169 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1173 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1202 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1243 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1274 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1342 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.8/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2022, Epic Games Tools LLC"`
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
- L101 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L103 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L106 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L117 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L119 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L120 _macro_ `#define OOFUNC2 OOEXPLINK`
- L121 _macro_ `#define OOFUNCSTART`
- L122 _macro_ `#define OODLE_CALLBACK OOLINK`
- L130 _macro_ `#define NULL (0)`
- L134 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L136 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L141 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L146 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L149 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L155 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.8/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-73_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L72 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L83-111_
- L85 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L86 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L87 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L88 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L89 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L91 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L92 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L93 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L94 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L96 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L98 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L100 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L104 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L105 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L106 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L109 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L110 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L146-163_
- L148 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L149 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L150 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L151 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L152 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L153 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L154 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L155 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L156 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L157 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L158 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L159 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L160 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L161 _public enumerator_ `OodleTex_BC_Max = 12`
- L162 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L255-262_
- L257 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L258 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L259 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L260 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L261 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L283-294_
- L285 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L286 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L287 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L288 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L331-341_
- L333 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L334 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L335 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L336 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L337 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L338 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L339 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats
- L340 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L375-380_
- L377 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L378 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L379 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L388-395_
- L390 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L391 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L392 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L393 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L394 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L426-433_
- L428 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L429 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L430 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L431 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L432 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L465-469_
- L467 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L468 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 8`
- L34 _macro_ `#define OodleTextureVersion "2.9.8" /*`
- L73 _typedef_ `} OodleTex_Err;`
- L111 _typedef_ `} OodleTex_PixelFormat;`
- L163 _typedef_ `} OodleTex_BC;`
- L224 _typedef_ `} OodleTex_Surface;`
- L242 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 16384 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).`
- L248 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L262 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L294 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L341 _typedef_ `} OodleTex_BCNFlags;`
- L380 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L395 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L433 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L469 _typedef_ `} OodleTex_RDO_Flags;`
- L488 _typedef_ `} OodleTex_RDO_Options;`
- L521 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L526 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L534 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L558 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L571 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L578 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L600 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L622 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L642 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L651 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L690 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L703 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L722 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L738 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L757 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L758 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L759 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L760 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L761 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L762 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L763 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L778 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L782 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L786 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L790 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L794 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L803 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L811 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L819 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L859 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L897 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L960 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1017 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1042 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1059 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1096 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1121 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1126 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1133 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1140 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1145 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1150 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1180 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1225 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1229 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1258 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1299 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1330 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1398 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.9/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2023, Epic Games Tools LLC"`
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
- L101 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L103 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L106 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L117 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L119 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L120 _macro_ `#define OOFUNC2 OOEXPLINK`
- L121 _macro_ `#define OOFUNCSTART`
- L122 _macro_ `#define OODLE_CALLBACK OOLINK`
- L130 _macro_ `#define NULL (0)`
- L134 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L136 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L141 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L146 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L149 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L155 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Source/Developer/TextureFormatOodle/Sdks/2.9.9/include/oodle2tex.h` (Other)


#### enum `OodleTex_Err`  
`typedef enum OodleTex_Err`  
_L37-73_
- L39 _public enumerator_ `OodleTex_Err_OK = 0` — no error
- L40 _public enumerator_ `OodleTex_Err_UnsupportedCPU = -1` — CPU is not supported. Oodle Texture encoding requires SSE4.1.
- L41 _public enumerator_ `OodleTex_Err_BadBCnFormat = -2` — Specified BCn format is not supported.
- L42 _public enumerator_ `OodleTex_Err_BadPixelFormat = -3` — Specified pixel format is not supported.
- L43 _public enumerator_ `OodleTex_Err_SurfaceCountMismatch = -4` — The number of surface specified does not match the $OodleTex_Layout (without a layout, surface count must be 1).
- L44 _public enumerator_ `OodleTex_Err_BlockCountMismatch = -5` — The number of blocks specified does not match the surface dimensions or $OodleTex_Layout.
- L45 _public enumerator_ `OodleTex_Err_LayoutFormatMismatch = -6` — The given $OodleTex_Layout does not match the target BCn format.
- L46 _public enumerator_ `OodleTex_Err_NegativeLambda = -7` — The specified Lagrange multiplier (lambda) is negative.
- L47 _public enumerator_ `OodleTex_Err_Internal = -8` — Unspecified internal error (this should not happen; if you can, please report a bug.)
- L49 _public enumerator_ `OodleTex_Err_BC7PrepHeaderCorrupt = -9` — BC7Prep header corrupted (or unsupported versin)
- L50 _public enumerator_ `OodleTex_Err_BC7PrepOutputBufTooSmall = -10` — BC7Prep output buffer too small for given block count
- L51 _public enumerator_ `OodleTex_Err_BC7PrepScratchBufTooSmall = -11` — BC7Prep scratch buffer too small for input data
- L52 _public enumerator_ `OodleTex_Err_BC7PrepPayloadCorrupt = -12` — BC7Prep payload data chunk was corrupted
- L53 _public enumerator_ `OodleTex_Err_BC7PrepNoHeader = -13` — BC7Prep missing output header pointer on encode
- L54 _public enumerator_ `OodleTex_Err_BC7PrepIllegalBlockCount = -14` — BC7Prep block count outside legal bounds
- L56 _public enumerator_ `OodleTex_Err_InvalidSurfaceIndex = -15` — The given surface index is out of bounds
- L57 _public enumerator_ `OodleTex_Err_MalformedBlockIDs = -16` — The block IDs passed to SetBlockLayout don't have the required form
- L59 _public enumerator_ `OodleTex_Err_BadMetric = -17` — OodleTex_RDO_ErrorMetric invalid
- L60 _public enumerator_ `OodleTex_Err_BadEncodeEffortLevel = -18` — OodleTex_EncodeEffortLevel invalid
- L62 _public enumerator_ `OodleTex_Err_SurfaceSizeMismatch = -19` — One of the surfaces passed to the Encode/Decode functions does not match the size of the corresponding surface in the $OodleTex_Layout.
- L64 _public enumerator_ `OodleTex_Err_NoLicense_Unused = -20` — unused
- L65 _public enumerator_ `OodleTex_Err_BufferTooSmall = -21` — Provided buffer is too small
- L66 _public enumerator_ `OodleTex_Err_SurfaceTooLarge = -22` — One of the input surfaces is larger than the maximum supported size (width or height above $OODLETEX_MAX_SURFACE_DIMENSION)
- L67 _public enumerator_ `OodleTex_Err_BadUniversalTiling = -23` — OodleTex_RDO_UniversalTiling invalid
- L68 _public enumerator_ `OodleTex_Err_LayoutAndUniversalTilingIncompatible = -24` — Both layout and universal tiling specified, they're mutually exclusive.
- L70 _public enumerator_ `OodleTex_Err_BadSRGBFormat = -25` — Linear<->sRGB conversion flag is allowed for BC1237 formats and, between 4xF32 and 4xU8 pixel formats
- L72 _public enumerator_ `OodleTex_Err_Force32 = 0x40000000` — not an actual error!

#### enum `OodleTex_PixelFormat`  
`typedef enum OodleTex_PixelFormat`  
_L83-111_
- L85 _public enumerator_ `OodleTex_PixelFormat_Invalid = 0`
- L86 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBA = 1` — 4 uint8s per pixel: R,G,B,A
- L87 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRA = 2` — 4 uint8s per pixel: B,G,R,A
- L88 _public enumerator_ `OodleTex_PixelFormat_4_F32_RGBA = 3` — 4 floats per pixel: R,G,B,A
- L89 _public enumerator_ `OodleTex_PixelFormat_4_F16_RGBA = 4` — 4 halfs per pixel: R,G,B,A
- L90 _public enumerator_ `OodleTex_PixelFormat_3_F32_RGB = 5` — 3 floats per pixel: R,G,B
- L91 _public enumerator_ `OodleTex_PixelFormat_3_U8_RGB = 6` — 3 uint8s per pixel: R,G,B
- L92 _public enumerator_ `OodleTex_PixelFormat_3_U8_BGR = 7` — 3 uint8s per pixel: B,G,R
- L93 _public enumerator_ `OodleTex_PixelFormat_2_U16 = 8` — 2 uint16s per pixel: R,G
- L94 _public enumerator_ `OodleTex_PixelFormat_2_S16 = 9` — 2 int16s per pixel: R,G
- L95 _public enumerator_ `OodleTex_PixelFormat_2_U8 = 10` — 2 uint8s per pixel: R,G
- L96 _public enumerator_ `OodleTex_PixelFormat_2_S8 = 11` — 2 int8s per pixel: R,G
- L97 _public enumerator_ `OodleTex_PixelFormat_1_U16 = 12` — 1 uint16 per pixel: R
- L98 _public enumerator_ `OodleTex_PixelFormat_1_S16 = 13` — 1 int16 per pixel: R
- L99 _public enumerator_ `OodleTex_PixelFormat_1_U8 = 14` — 1 uint8 per pixel: R
- L100 _public enumerator_ `OodleTex_PixelFormat_1_S8 = 15` — 1 int8 per pixel: R
- L101 _public enumerator_ `OodleTex_PixelFormat_4_U8_RGBx = 16` — 4 uint8s per pixel: R, G, B, (ignored) - like U3_RGB with a padding byte per pixel
- L102 _public enumerator_ `OodleTex_PixelFormat_4_U8_BGRx = 17` — 4 uint8s per pixel: B, G, R, (ignored) - like U3_BGR with a padding byte per pixel
- L104 _public enumerator_ `OodleTex_PixelFormat_4_U16 = 18` — 4 uint16s per pixel: R,G,B,A (bonus convenience format, not for direct encoding to BCN)
- L105 _public enumerator_ `OodleTex_PixelFormat_3_U16 = 19` — 3 uint16s per pixel: R,G,B (bonus convenience format, not for direct encoding to BCN)
- L106 _public enumerator_ `OodleTex_PixelFormat_2_F32 = 20` — 2 floats per pixel: R,G (bonus convenience format, not for direct encoding to BCN)
- L107 _public enumerator_ `OodleTex_PixelFormat_1_F32 = 21` — 1 floats per pixel: R (bonus convenience format, not for direct encoding to BCN)
- L109 _public enumerator_ `OodleTex_PixelFormat_Max = 21`
- L110 _public enumerator_ `OodleTex_PixelFormat_Force32 = 0x40000000`

#### enum `OodleTex_BC`  
`typedef enum OodleTex_BC`  
_L146-163_
- L148 _public enumerator_ `OodleTex_BC_Invalid = 0`
- L149 _public enumerator_ `OodleTex_BC1 = 1` — BC1 for UNORM RGB color images; may use transparent to send black, output A can be 255 or 0.
- L150 _public enumerator_ `OodleTex_BC1_WithTransparency = 2` — BC1 with 1-bit alpha transparency
- L151 _public enumerator_ `OodleTex_BC2 = 3` — BC2 encodes 8-bit UNORM RGBA
- L152 _public enumerator_ `OodleTex_BC3 = 4` — BC3 encodes 8-bit UNORM RGBA
- L153 _public enumerator_ `OodleTex_BC4U = 5` — BC4 UNORM. Encodes R channel only.
- L154 _public enumerator_ `OodleTex_BC4S = 6` — BC4 SNORM. Encodes R channel only.
- L155 _public enumerator_ `OodleTex_BC5U = 7` — BC5 UNORM. Encodes R and G channels.
- L156 _public enumerator_ `OodleTex_BC5S = 8` — BC5 SNORM. Encodes R and G channels.
- L157 _public enumerator_ `OodleTex_BC6U = 9` — BC6H UF16 - unsigned BC6H data.
- L158 _public enumerator_ `OodleTex_BC6S = 10` — BC6H SF16 - signed BC6H data.
- L159 _public enumerator_ `OodleTex_BC7RGBA= 11` — BC7 encodes 8-bit UNORM RGBA
- L160 _public enumerator_ `OodleTex_BC7RGB = 12` — BC7 only using RGB channels, with alpha ignored. Increases quality in RGB channels but output A is undefined.
- L161 _public enumerator_ `OodleTex_BC_Max = 12`
- L162 _public enumerator_ `OodleTex_BC_Force32 = 0x40000000`

#### enum `OodleTex_EncodeEffortLevel`  
`typedef enum OodleTex_EncodeEffortLevel`  
_L255-262_
- L257 _public enumerator_ `OodleTex_EncodeEffortLevel_Default = 0`
- L258 _public enumerator_ `OodleTex_EncodeEffortLevel_Low = 10`
- L259 _public enumerator_ `OodleTex_EncodeEffortLevel_Normal = 20`
- L260 _public enumerator_ `OodleTex_EncodeEffortLevel_High = 30`
- L261 _public enumerator_ `OodleTex_EncodeEffortLevel_Force32 = 0x40000000`

#### enum `OodleTex_RDOLagrangeLambda`  
`typedef enum OodleTex_RDOLagrangeLambda`  
_L283-294_
- L285 _public enumerator_ `OodleTex_RDOLagrangeLambda_NearLossless = 1` — almost lossless (relative to baseline BCN)
- L286 _public enumerator_ `OodleTex_RDOLagrangeLambda_VeryHighQuality = 10`
- L287 _public enumerator_ `OodleTex_RDOLagrangeLambda_HighQuality = 20`
- L288 _public enumerator_ `OodleTex_RDOLagrangeLambda_Default = 30`
- L289 _public enumerator_ `OodleTex_RDOLagrangeLambda_MediumQuality = 40`
- L290 _public enumerator_ `OodleTex_RDOLagrangeLambda_LowQuality = 60`
- L291 _public enumerator_ `OodleTex_RDOLagrangeLambda_Min = 1`
- L292 _public enumerator_ `OodleTex_RDOLagrangeLambda_Max = 100`
- L293 _public enumerator_ `OodleTex_RDOLagrangeLambda_Force32 = 0x40000000`

#### enum `OodleTex_BCNFlags`  
`typedef enum OodleTex_BCNFlags`  
_L331-341_
- L333 _public enumerator_ `OodleTex_BCNFlags_None = 0`
- L334 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC3457 = 1` — BC3-5 and BC7: preserve 0 and 255 (0.0 and 1.0) in alpha channel exactly.
- L335 _public enumerator_ `OodleTex_BCNFlag_PreserveExtremes_BC345 = 1` — Alias for BCNFlags_PreserveExtremes_BC3457 (old name)
- L336 _public enumerator_ `OodleTex_BCNFlag_BC6_NonRGBData = 2` — BC6: texture contains non-image data and should be treated scalar channels
- L337 _public enumerator_ `OodleTex_BCNFlag_AvoidWideVectors = 4` — Avoid wide vector instruction sets
- L338 _public enumerator_ `OodleTex_BCNFlag_PreferWideVectors = 8` — Prefer wide vector instruction sets
- L339 _public enumerator_ `OodleTex_BCNFlag_LinearToSRGB = 16` — Convert linear float input to sRGB, currently only for BC1237 formats
- L340 _public enumerator_ `OodleTex_BCNFlag_Force32 = 0x40000000`

#### enum `OodleTex_BCNDecodeFlags`  
`typedef enum OodleTex_BCNDecodeFlags`  
_L375-380_
- L377 _public enumerator_ `OodleTex_BCNDecodeFlags_None = 0`
- L378 _public enumerator_ `OodleTex_BCNDecodeFlag_SRGBToLinear = 1` — Convert sRGB to linear float output, currently only for BC1237 formats
- L379 _public enumerator_ `OodleTex_BCNDecodeFlag_Force32 = 0x40000000`

#### enum `OodleTex_RDO_ErrorMetric`  
`typedef enum OodleTex_RDO_ErrorMetric`  
_L388-395_
- L390 _public enumerator_ `OodleTex_RDO_ErrorMetric_Default = 0` — Default is Perceptual
- L391 _public enumerator_ `OodleTex_RDO_ErrorMetric_RMSE_RGBA = 1`
- L392 _public enumerator_ `OodleTex_RDO_ErrorMetric_Perceptual_RGBA = 2`
- L393 _public enumerator_ `OodleTex_RDO_ErrorMetric_Max = 2`
- L394 _public enumerator_ `OodleTex_RDO_ErrorMetric_Force32 = 0x40000000`

#### enum `OodleTex_RDO_UniversalTiling`  
`typedef enum OodleTex_RDO_UniversalTiling`  
_L426-433_
- L428 _public enumerator_ `OodleTex_RDO_UniversalTiling_Disable = 0` — No universal tiling, the default. This option must be used when an $OodleTex_Layout is specified.
- L429 _public enumerator_ `OodleTex_RDO_UniversalTiling_256KB = 1` — Universal tiling with 256KB blocks
- L430 _public enumerator_ `OodleTex_RDO_UniversalTiling_64KB = 2` — Universal tiling with 64KB blocks
- L431 _public enumerator_ `OodleTex_RDO_UniversalTiling_Max = 2`
- L432 _public enumerator_ `OodleTex_RDO_UniversalTiling_Force32 = 0x40000000`

#### enum `OodleTex_RDO_Flags`  
`typedef enum OodleTex_RDO_Flags`  
_L465-469_
- L467 _public enumerator_ `OodleTex_RDO_Flags_None = 0`
- L468 _public enumerator_ `OodleTex_RDO_Flags_Force32 = 0x40000000`

#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2TEX_H_INCLUDED__`
- L11 _macro_ `#define OODLE2TEX_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2TEX_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2TEX_VERSION_MINOR 9`
- L34 _macro_ `#define OodleTextureVersion "2.9.9" /*`
- L73 _typedef_ `} OodleTex_Err;`
- L111 _typedef_ `} OodleTex_PixelFormat;`
- L163 _typedef_ `} OodleTex_BC;`
- L224 _typedef_ `} OodleTex_Surface;`
- L242 _macro_ `#define OODLETEX_MAX_SURFACE_DIMENSION 16384 /* Maximum dimensions of an OodleTex_Surface in either direction (width or height).`
- L248 _macro_ `#define OodleTex_Surface_NumBlocks(surf) ((( (surf)->width + 3 )/4)*(( (surf)->height + 3 )/4)) /* Number of 4x4 blocks in an OodleTex_Surface`
- L262 _typedef_ `} OodleTex_EncodeEffortLevel;`
- L294 _typedef_ `} OodleTex_RDOLagrangeLambda;`
- L341 _typedef_ `} OodleTex_BCNFlags;`
- L380 _typedef_ `} OodleTex_BCNDecodeFlags;`
- L395 _typedef_ `} OodleTex_RDO_ErrorMetric;`
- L433 _typedef_ `} OodleTex_RDO_UniversalTiling;`
- L469 _typedef_ `} OodleTex_RDO_Flags;`
- L488 _typedef_ `} OodleTex_RDO_Options;`
- L521 _macro_ `#define OODLETEX_JOBS_DEFAULT ( 0) /* Use all the installed threads`
- L526 _macro_ `#define OODLETEX_JOBS_DISABLE (-1) /* Run single-threaded`
- L534 _typedef_ `typedef struct OodleTex_Layout OodleTex_Layout;`
- L558 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleTex_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L571 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Free)( void * ptr );`
- L578 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetAllocators( t_fp_OodleTex_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleTex_Plugin_Free * fp_OodleFree);`
- L600 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleTex_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L622 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L642 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystem( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob);`
- L651 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugins_SetJobSystemAndCount( t_fp_OodleTex_Plugin_RunJob * fp_RunJob, t_fp_OodleTex_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L690 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleTex_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L703 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_Printf * OOFUNC2 OodleTex_Plugins_SetPrintf(t_fp_OodleTex_Plugin_Printf * fp_rrRawPrintf);`
- L722 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleTex_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L738 _prototype_ `OOFUNC1 t_fp_OodleTex_Plugin_DisplayAssertion * OOFUNC2 OodleTex_Plugins_SetAssertion(t_fp_OodleTex_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L757 _prototype_ `OOFUNC1 void * OOFUNC2 OodleTex_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L758 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Free_Default(void * ptr);`
- L759 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L760 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L761 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleTex_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L762 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleTex_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L763 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L769 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_LogVersion();`
- L778 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_Err_GetName(OodleTex_Err error);`
- L782 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_PixelFormat_GetName(OodleTex_PixelFormat pf);`
- L786 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_BC_GetName(OodleTex_BC bcn);`
- L790 _prototype_ `OOFUNC1 const char * OOFUNC2 OodleTex_RDO_UniversalTiling_GetName(OodleTex_RDO_UniversalTiling tiling);`
- L794 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_BC_BytesPerBlock(OodleTex_BC bcn);`
- L803 _prototype_ `OOFUNC1 OO_S32 OOFUNC2 OodleTex_PixelFormat_BytesPerPixel(OodleTex_PixelFormat pf);`
- L811 _prototype_ `OOFUNC1 OodleTex_PixelFormat OOFUNC2 OodleTex_BC_GetNaturalDecodeFormat(OodleTex_BC bcn);`
- L819 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_LinearSurfaces( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L859 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_Blocks( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const void * from_pixel_blocks,OodleTex_PixelFormat from_format, OodleTex_EncodeEffortLevel level,OodleTex_BCNFlags flags, int num_job_threads,void * jobify_user_ptr);`
- L897 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda,OodleTex_BCNFlags flags, OodleTex_RDO_ErrorMetric rdo_metric, int num_job_threads,void * jobify_user_ptr);`
- L960 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_EncodeBCN_RDO_Ex( OodleTex_BC to_bcn,void * to_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Surface * from_surfaces,OO_SINTa num_from_surfaces,OodleTex_PixelFormat from_format, const OodleTex_Layout * layout, int rdo_lagrange_lambda, const OodleTex_RDO_Options * options, int num_job_threads,void * jobify_user_ptr);`
- L1017 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks( void * to_pixel_blocks,OodleTex_PixelFormat to_format,OO_SINTa num_blocks, OodleTex_BC from_bcn,const void * from_bcn_blocks );`
- L1042 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_Blocks_Ex( void* to_pixel_blocks, OodleTex_PixelFormat to_format, OO_SINTa num_blocks, OodleTex_BC from_bcn, const void* from_bcn_blocks, OodleTex_BCNDecodeFlags flags );` — Decode Block Compressed surface to pixels in 4x4 block order. $:to_pixel_blocks   memory to write output pixels to $:to_format         format of pixels in _to_pixel_blocks_ $:num_blocks        number of blocks to process $:from_bcn          Block Compressed texture format contained in _from_bcn_blocks_ $:from_bcn_blocks   array of BCN blocks to read $:return            $OodleTex_Err indicating the error condition, or $OodleTex_Err_OK on success. Decodes _num_blocks_ BCN blocks and writes them to _to_pixel_blocks_ in 4x4 block order. _to_format_ may be $OodleTex_BC_GetNaturalDecodeFormat or any other. Decoding of BC1-5 is only specified within error bounds, not precisely.  We decode to a compromise approximation in between AMD, Apple, Intel and NVidia GPU hardware.  The approximation is also within the allowed tolerances of the D3D12 reference specification.  This behavior has changed in Oodle 2.9.5, see $OodleTex_About_BCNDecoding for details. See also $OodleTex_DecodeBCN_LinearSurfaces.
- L1059 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces( OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces,OodleTex_PixelFormat to_format, OodleTex_BC from_bcn,const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1096 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_DecodeBCN_LinearSurfaces_Ex( OodleTex_Surface* to_surfaces, OO_SINTa num_to_surfaces, OodleTex_PixelFormat to_format, OodleTex_BC from_bcn, const void* from_bcn_blocks, OO_SINTa num_blocks, const OodleTex_Layout* layout, OodleTex_BCNDecodeFlags flags );`
- L1121 _macro_ `#define OODLETEXRT_BC7PREP_DEFINED`
- L1126 _macro_ `#define OODLETEXRT_BC7PREP_MODE_COUNT 10`
- L1133 _typedef_ `} OodleTexRT_BC7PrepHeader;`
- L1140 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeOutputSize(OO_SINTa nblocks);`
- L1145 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_MinEncodeScratchSize(OO_SINTa nblocks);`
- L1150 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleTex_BC7Prep_Encode(OodleTexRT_BC7PrepHeader * out_header, void * output_buf, OO_SINTa output_size, const void * input_bc7, OO_SINTa num_blocks, void * scratch_buf, OO_SINTa scratch_size);`
- L1180 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_Create( OodleTex_BC bcn_format, const OodleTex_Surface * surfaces,int num_surfaces, OodleTex_Layout ** out_layout );`
- L1225 _prototype_ `OOFUNC1 void OOFUNC2 OodleTex_Layout_Destroy(OodleTex_Layout * layout);`
- L1229 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_GenerateBlockIDs( const OodleTex_Layout * layout, int surface_index, void * block_ids, OO_SINTa block_id_row_stride_bytes );`
- L1258 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_SetBlockLayout( OodleTex_Layout * layout, const void * reordered_block_ids, OO_SINTa num_reordered_blocks );`
- L1299 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_Layout_CopyBCNToLinear( OodleTex_BC bcn, OodleTex_Surface * to_surfaces,OO_SINTa num_to_surfaces, const void * from_bcn_blocks,OO_SINTa num_blocks, const OodleTex_Layout * layout );`
- L1330 _prototype_ `OOFUNC1 OO_F32 OOFUNC2 OodleTex_RMSE_Normalized_BCNAware( OodleTex_BC was_bcn, const OodleTex_Surface * surf1,OodleTex_PixelFormat format1, const OodleTex_Surface * surf2,OodleTex_PixelFormat format2);`
- L1398 _prototype_ `OOFUNC1 OodleTex_Err OOFUNC2 OodleTex_BlitNormalized( OodleTex_Surface * to_surf,OodleTex_PixelFormat to_format, const OodleTex_Surface * from_surf,OodleTex_PixelFormat from_format);`
