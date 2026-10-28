# Plugins / ApvMedia

- module root: `Plugins/Media/TmvMedia/Source/ApvMedia`
- headers: 13; symbols: 297
- symbol kinds: class=7, delegate=1, enum=9, enumerator=72, function=79, macro=8, member=54, namespace=14, prototype=39, struct=13, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, Media, Projects, RHI, RenderCore, Renderer, TmvMedia, UEOpenAPV

### `Plugins/Media/TmvMedia/Source/ApvMedia/Internal/ApvMediaTmvEncoderOptions.h` (Internal)


#### struct `FApvMediaTmvEncoderOptions`  
`struct FApvMediaTmvEncoderOptions : public FTmvMediaEncoderOptions`  
_L17-104_
- reflection: `USTRUCT(DisplayName = "OpenApv Tmv Encoder Options")`
- inherits: `FTmvMediaEncoderOptions`
- desc: OpenApv Tmv Encoder options.
- L21 _public function_ `FApvMediaTmvEncoderOptions()`
- L31 _public prototype_ `virtual ~FApvMediaTmvEncoderOptions() override = default;`
- L34 _public prototype_ `virtual FName GetEncoderName() const override;`
- L35 _public function_ `virtual FString GetFileSequenceExtension() const override`
- L36 _public prototype_ `virtual uint32 GetCodecFourCC() const override;`
- L38 _public function_ `virtual void GetSupportedDestinationColorSpaces(TArray<ETextureColorSpace>& OutSupportedColorSpaces) const override`
- L45 _public function_ `virtual void GetSupportedDestinationEncodings(TArray<ETmvMediaEncoderEncoding>& OutSupportedEncodings) const override`
- L58 _public function_ `EApvMediaChromaFormat GetChromaFormat() const` — Get currently configured color/chromat format.
- L64 _public function_ `int8 GetBitDepth() const` — Get currently configured bit depth
- L75 _public member_ `FIntPoint TileSize = FIntPoint(256, 256);` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.0"))` — Dimensions of a tile in pixels. The tile size determines parallelism and performance. Frames are divided into rectangular tiles that can be encoded and decoded simultaneously, enabling high throughput on multicore processors.
- L82 _public member_ `EApvMediaProfile Profile = EApvMediaProfile::YCbCr422_10;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Specify the color/chroma profile, includes bitdepth. Input video will be converted to the given profile.
- L89 _public member_ `EApvMediaBand Band = EApvMediaBand::Band2;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Coded data rate band Setting. If the bitrate is not specified otherwise, this determines the max coded data rate (higher band leads to higher bit rate).
- L97 _public member_ `EApvMediaPreset Preset = EApvMediaPreset::Medium;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Specify the encoding optimization level.
- L103 _public member_ `int32 NumThreads = 0;` — `UPROPERTY(EditAnywhere, Category = "Advanced", meta = (ClampMin = "0.0"))` — Number of worker thread to encode tiles (0 = automatically use the available number of cores).

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API APVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/ApvMedia/Internal/ApvMediaTypes.h` (Internal)


#### enum `EApvMediaChromaFormat`  
`enum class EApvMediaChromaFormat : uint8`  
_L11-23_
- reflection: `UENUM()`
- desc: List of color/chroma image buffer formats used by OpenApv.
- L14 _public enumerator_ `YCbCr400 = 0` — 1 component (monochrome)
- L16 _public enumerator_ `YCbCr422 = 2` — 3 components YUV 422
- L18 _public enumerator_ `YCbCr444 = 3` — 3 components YUV 444
- L20 _public enumerator_ `YCbCrA4444 = 4` — 4 components YUV 444 + alpha
- L22 _public enumerator_ `YCbCr422_P2 = 5` — 3 components YUV 422 with UV in the same memory plane.

#### enum `EApvMediaPreset`  
`enum class EApvMediaPreset : uint8`  
_L27-34_
- reflection: `UENUM()`
- desc: Optimization level control presets
- L29 _public enumerator_ `Fastest = 0`
- L30 _public enumerator_ `Fast = 1`
- L31 _public enumerator_ `Medium = 2`
- L32 _public enumerator_ `Slow = 3`
- L33 _public enumerator_ `Placebo = 4`

#### enum `EApvMediaProfile`  
`enum class EApvMediaProfile : uint8`  
_L40-49_
- reflection: `UENUM()`
- desc: Each profile specifies a subset of algorithmic features and limits that must be supported by all decoders conforming to that profile.
- L42 _public enumerator_ `YCbCr422_10 UMETA(DisplayName = "4:2:2 10 bits", ToolTip = "422-10: YCbCr422 10 bits")`
- L43 _public enumerator_ `YCbCr422_12 UMETA(DisplayName = "4:2:2 12 bits", ToolTip = "422-12: YCbCr422 12 bits")`
- L44 _public enumerator_ `YCbCr444_10 UMETA(DisplayName = "4:4:4 10 bits", ToolTip = "444-10: YCbCr444 10 bits")`
- L45 _public enumerator_ `YCbCr444_12 UMETA(DisplayName = "4:4:4 12 bits", ToolTip = "444-12: YCbCr444 12 bits")`
- L46 _public enumerator_ `YCbCr4444_10 UMETA(DisplayName = "4:4:4:4 10 bits", ToolTip = "4444-10: YCbCrA4444 10 bits")`
- L47 _public enumerator_ `YCbCr4444_12 UMETA(DisplayName = "4:4:4:4 12 bits", ToolTip = "4444-12: YCbCrA4444 12 bits")`
- L48 _public enumerator_ `YCbCr400_10 UMETA(DisplayName = "4:0:0 10 bits Monochrome", ToolTip = "400-10: YCbCr400 (monochrome) 10 bits")`

#### enum `EApvMediaBitDepth`  
`enum class EApvMediaBitDepth : uint8`  
_L55-61_
- reflection: `UENUM()`
- desc: Supported bit depths.
- L58 _public enumerator_ `BitDepth_10 = 10` — 10 bits per component
- L60 _public enumerator_ `BitDepth_12 = 12` — 12 bits per component

#### enum `EApvMediaBand`  
`enum class EApvMediaBand : uint8`  
_L67-77_
- reflection: `UENUM()`
- desc: Determines the max coded data rate (higher band leads to higher bit rate).
- L70 _public enumerator_ `Band0 = 0 UMETA(DisplayName = "0")` — Lowest coded bit rate
- L72 _public enumerator_ `Band1 = 1 UMETA(DisplayName = "1")` — Low coded bit rate (~150% of lowest)
- L74 _public enumerator_ `Band2 = 2 UMETA(DisplayName = "2")` — Medium coded bit rate (~200% of lowest)
- L76 _public enumerator_ `Band3 = 3 UMETA(DisplayName = "3")` — Highest coded bit rate (~300% of lowest)

#### enum `EApvMediaColorTransfer`  
`enum class EApvMediaColorTransfer : uint8`  
_L84-105_
- reflection: `UENUM()`
- desc: Color transfer functions defined in OpenApv. Reference: Rec H.273 https://www.itu.int/rec/T-REC-H.273
- L86 _public enumerator_ `Reserved0 = 0 UMETA(Hidden)`
- L87 _public enumerator_ `Bt709 = 1`
- L88 _public enumerator_ `Unspecified = 2`
- L89 _public enumerator_ `Reserved3 = 3 UMETA(Hidden)`
- L90 _public enumerator_ `Bt470M = 4`
- L91 _public enumerator_ `Bt470BG = 5`
- L92 _public enumerator_ `Smpte170m = 6`
- L93 _public enumerator_ `Smpte240m = 7`
- L94 _public enumerator_ `Linear = 8`
- L95 _public enumerator_ `Log100 = 9`
- L96 _public enumerator_ `Log316 = 10`
- L97 _public enumerator_ `Iec61966_2_4 = 11`
- L98 _public enumerator_ `Bt1361e = 12`
- L99 _public enumerator_ `Iec61966_2_1 = 13`
- L100 _public enumerator_ `Bt2020_10 = 14`
- L101 _public enumerator_ `Bt2020_12 = 15`
- L102 _public enumerator_ `Smpte2084 = 16`
- L103 _public enumerator_ `Smpte428 = 17`
- L104 _public enumerator_ `Arib_std_b67 = 18`

#### enum `EApvMediaColorSpace`  
`enum class EApvMediaColorSpace : uint8`  
_L112-127_
- reflection: `UENUM()`
- desc: Color primaries defined in OpenApv. Reference: Rec H.273 https://www.itu.int/rec/T-REC-H.273
- L114 _public enumerator_ `Reserved0 = 0 UMETA(Hidden)`
- L115 _public enumerator_ `Bt709 = 1`
- L116 _public enumerator_ `Unspecified = 2`
- L117 _public enumerator_ `Reserved3 = 3 UMETA(Hidden)`
- L118 _public enumerator_ `Bt470m = 4`
- L119 _public enumerator_ `Bt470bg = 5`
- L120 _public enumerator_ `Smpte170m = 6`
- L121 _public enumerator_ `Smpte240m = 7`
- L122 _public enumerator_ `Film = 8`
- L123 _public enumerator_ `Bt2020 = 9`
- L124 _public enumerator_ `Smpte428 = 10`
- L125 _public enumerator_ `Smpte431 = 11`
- L126 _public enumerator_ `Smpte432 = 12`

#### enum `EApvMediaColorMatrix`  
`enum class EApvMediaColorMatrix : uint8`  
_L134-151_
- reflection: `UENUM()`
- desc: YUV color matrices defined in OpenApv. Reference: Rec H.273 https://www.itu.int/rec/T-REC-H.273
- L136 _public enumerator_ `Gbr = 0`
- L137 _public enumerator_ `Bt709 = 1`
- L138 _public enumerator_ `Unspecified = 2`
- L139 _public enumerator_ `Reserved3 = 3 UMETA(Hidden)`
- L140 _public enumerator_ `Fcc = 4`
- L141 _public enumerator_ `Bt470bg = 5`
- L142 _public enumerator_ `Smpte170m = 6`
- L143 _public enumerator_ `Smpte240m = 7`
- L144 _public enumerator_ `Ycgco = 8`
- L145 _public enumerator_ `Bt2020nc = 9`
- L146 _public enumerator_ `Bt2020c = 10`
- L147 _public enumerator_ `Smpte2085 = 11`
- L148 _public enumerator_ `Chroma_derived_nc = 12`
- L149 _public enumerator_ `Chroma_derived_c = 13`
- L150 _public enumerator_ `Ictcp = 14`

#### enum `EApvMediaColorMatrixRange`  
`enum class EApvMediaColorMatrixRange : uint8`  
_L159-165_
- reflection: `UENUM()`
- desc: YUV color matrix ranges defined in OpenApv. Specifies the scaling and offset applied in association with the YUV matrix coefficients. Reference: Rec H.273 https://www.itu.int/rec/T-REC-H.273
- L162 _public enumerator_ `Limited = 0` — Standard for television, broadcast and video content. Typically defines black at 16 and white at 235 (standard dependent).
- L164 _public enumerator_ `Full = 1` — Standard for PC graphics and image processing. Defines black at 0 and white at 255.

#### Free symbols / members of external scopes

- L167 _namespace_ `namespace UE`
- L167 _namespace_ `namespace ApvMedia` (scope `UE`)
- L170 _function_ `inline EApvMediaChromaFormat GetChromaFormat(const EApvMediaProfile InProfile)` (scope `UE::ApvMedia`) — Get the color/chroma format from the given apv profile.
- L194 _function_ `inline int8 GetBitDepth(const EApvMediaProfile InProfile)` (scope `UE::ApvMedia`) — Get the bit depth from the given apv profile.
- L218 _function_ `inline int32 GetNumComponents(const EApvMediaChromaFormat InFormat)` (scope `UE::ApvMedia`) — Get the number of components from the given apv chroma format.
- L236 _function_ `inline int32 GetNumPlanes(const EApvMediaChromaFormat InFormat)` (scope `UE::ApvMedia`) — Get the number of memory planes for the given color/chroma format.
- L255 _function_ `inline int32 GetPlaneNumComponents(const int32 InPlaneIndex, const EApvMediaChromaFormat InFormat)` (scope `UE::ApvMedia`) — Get the number of components packed in the given plane for the given format.
- L265 _function_ `inline int32 GetSubWidthC(const EApvMediaChromaFormat InFormat)` (scope `UE::ApvMedia`) — Returns the width factor for the chroma samples of the given format.
- L276 _function_ `inline int32 GetSubHeightC(const EApvMediaChromaFormat InFormat)` (scope `UE::ApvMedia`) — Returns the height factor for the chroma samples of the given format.

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/Apv/ApvCommon.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define OAPV_STATIC_DEFINE`
- L19 _macro_ `#define OAPV_HAS_SELECTIVE_MULTI_MIPS_DECODE_API 0`
- L24 _macro_ `#define OAPV_HAS_SELECTIVE_DECODE_API 0`
- L29 _macro_ `#define OAPV_HAS_FRAME_DECODE_API 0`
- L34 _macro_ `#define OAPV_HAS_LOGGING_API 0`
- L39 _macro_ `#define OAPV_HAS_MEMORY_API 0`
- L43 _macro_ `#define OAPV_HAS_CPU_TRACE_API 0`

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/Apv/ApvDecoder.h` (Private)


#### struct `UE::ApvMedia::FApvImageBitmap`  
`struct FApvImageBitmap : public oapv_imgb_t`  
_L16-63_
- inherits: `oapv_imgb_t`
- desc: Utility wrapper for the decoding image buffer.
- L18 _public prototype_ `FApvImageBitmap();`
- L21 _public prototype_ `static oapv_imgb_t* Create(int InWidth, int InHeight, int InColorSpace, bool bInAllocate = true);` — Creates an image buffer of the given dimensions and color space.
- L24 _public prototype_ `bool Init(int InWidth, int InHeight, int InColorSpace, bool bInAllocate = true);` — Initialise
- L28 _private member_ `std::atomic<int> ReferenceCount;` — Adding an actual atomic ref count here (may not be necessary though).
- L30 _private function_ `int AddRefImpl()`
- L36 _private function_ `int DecRefImpl()`
- L42 _private function_ `int GetRefImpl() const`
- L47 _private prototype_ `int ReleaseImpl();`
- L49 _private function_ `static int AddRef(oapv_imgb_t *imgb)`
- L54 _private function_ `static int GetRef(oapv_imgb_t *imgb)`
- L59 _private function_ `static int Release(oapv_imgb_t *imgb)`

#### struct `UE::ApvMedia::FApvFrames`  
`struct FApvFrames : public oapv_frms_t`  
_L66-83_
- inherits: `oapv_frms_t`
- desc: Wrapper utility for oapv frames
- L68 _public function_ `FApvFrames()`
- L73 _public function_ `~FApvFrames()`

#### struct `UE::ApvMedia::FApvDecoderContext`  
`struct FApvDecoderContext`  
_L89-109_
- desc: Recyclable Context for a "ReadFrame" function call, which is on a worker thread. Not meant to be thread safe directly (but must be acquired and released by a thread safe pool container).
- L91 _public prototype_ `FApvDecoderContext(int32 InNumDecodeThreads);`
- L93 _public prototype_ `~FApvDecoderContext();`
- L95 _public function_ `bool IsValid() const`
- L101 _public member_ `oapvd_t did = nullptr;` — oapv decoder context
- L104 _public member_ `oapvm_t mid = nullptr;` — oapv metadata container
- L108 _public member_ `FApvFrames DecodedFrames;` — oapv frame buffers Contains the destination frame buffers the decoder will write to.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ApvMedia` (scope `UE`)
- L11 _prototype_ `const TCHAR* GetApvErrorString(int32 InError);` (scope `UE::ApvMedia`) — Returns the error string corresponding to the error code (OAPV_ERR_...) to use for error reporting.

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/Apv/ApvEncoder.h` (Private)


#### struct `UE::ApvMedia::FApvEncoderContext`  
`struct FApvEncoderContext`  
_L18-54_
- desc: Utility wrapper for OpenApv Encoder context.
- L28 _public prototype_ `FApvEncoderContext( const FApvMediaTmvEncoderOptions& InOptions, const FTmvMediaEncoderMipInfo& InMipInfo, const FTmvMediaFrameTimeInfo& InTimeInfo, FTmvMediaMessageContext* OutMessageContext);` — Construct the OpenApv encoder context. @param InOptions Encoder options (user specified) @param InMipInfo Primary Mip (mip 0) descriptor @param InTimeInfo Only Time info's frame rate is used as a hint for bit rate calculations. @param OutMessageContext Optional message context for the given operation. @remark Sequence's frame rate can't be stored by OpenApv frame header (not supported).
- L35 _public prototype_ `FApvEncoderContext(const FApvEncoderContext& InOther) = delete;` — Non-copiable
- L36 _public prototype_ `FApvEncoderContext& operator=(const FApvEncoderContext& InOther) = delete;`
- L38 _public prototype_ `~FApvEncoderContext();`
- L41 _public function_ `bool IsValid() const` — returns true if the context is valid.
- L47 _public member_ `oapve_t eid = nullptr;` — OpenApv encoder context
- L50 _public member_ `oapvm_t mid = nullptr;` — OpenApv metadata container
- L53 _public member_ `FApvFrames Frames;` — Contains the frame buffers the encoder will read from.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ApvMedia` (scope `UE`)

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/Apv/ApvMipBufferUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ApvMedia` (scope `UE`)
- L18 _function_ `inline int32 GetApvColorFormat(const FTmvMediaFrameMipInfo& InMipInfo)` (scope `UE::ApvMedia`) — Determines the Apv original color format from the setup of the mip color planes.
- L47 _function_ `inline uint8 GetBitDepth(const FTmvMediaFrameMipInfo& InMipInfo)` (scope `UE::ApvMedia`) — Safely gets the bit depth from plane 0.
- L53 _function_ `inline int32 GetApvColorSpace(const FTmvMediaFrameMipInfo& InMipInfo)` (scope `UE::ApvMedia`) — Determines the original color space from the setup of the mip color planes.
- L59 _function_ `inline oapv_imgb_t* ApvSetupImageBuffer(const FTmvMediaFrameMipInfo& InMipInfo, FTmvMediaFrameMipBuffer& InResourceBuffer)` (scope `UE::ApvMedia`) — Wrap a FrameMipBuffer in an Apv Image buffer structure.
- L116 _function_ `template<typename Enum> constexpr auto ToUnderlyingType(Enum Val)` (scope `UE::ApvMedia`) — Enum conversion utility: Converts an enum value to it's underlying type for OpenApv struct fields.
- L125 _function_ `inline TOptional<EApvMediaColorTransfer> GetApvColorTransfer(UE::Color::EEncoding InEncoding)` (scope `UE::ApvMedia`) — Convert UE encoding to OpenApv color transfer if possible. @remark potential match only. (wip)
- L188 _function_ `inline Color::EEncoding GetColorEncoding(EApvMediaColorTransfer InApvTransfer)` (scope `UE::ApvMedia`) — Convert OpenApv color transfer to UE encoding. @remark Must match GetApvColorTransfer above.
- L221 _function_ `inline TOptional<EApvMediaColorSpace> GetApvColorSpace(Color::EColorSpace InColorSpace)` (scope `UE::ApvMedia`) — Convert UE color space to OpenApv color space if possible. @remark potential match only. (wip)
- L279 _function_ `inline Color::EColorSpace GetColorSpace(EApvMediaColorSpace InApvColorSpace)` (scope `UE::ApvMedia`) — Convert OpenApv color space to UE color space. @remark must match GetApvColorSpace above.
- L302 _function_ `inline EApvMediaColorMatrix GetApvColorMatrix(ETmvMediaFrameColorMatrix InColorMatrix)` (scope `UE::ApvMedia`) — Convert Tmv (Yuv) color matrix to OpenApv color matrix.
- L329 _function_ `inline ETmvMediaFrameColorMatrix GetColorMatrix(EApvMediaColorMatrix InApvColorMatrix)` (scope `UE::ApvMedia`) — Convert OpenApv color matrix enum to Tmv (Yuv) color matrix.
- L356 _function_ `inline EApvMediaColorMatrixRange GetApvColorMatrixRange(ETmvMediaFrameColorMatrixRange InColorMatrixRange)` (scope `UE::ApvMedia`) — Convert matrix coefficient range to Apv enum.
- L362 _function_ `inline ETmvMediaFrameColorMatrixRange GetColorMatrixRange(EApvMediaColorMatrixRange InApvColorMatrixRange)` (scope `UE::ApvMedia`) — Convert matrix coefficient range to Tmv enum.

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/Apv/ApvParser.h` (Private)


#### class `UE::ApvMedia::FApvBitReader`  
`class FApvBitReader`  
_L28-190_
- desc: Utility class to read bit stream out of an FArchive. Adapted from the oapv_bs (bitstream) code. Seems to be similar to FBitReader, except it is backed directly by an FArchive. Benefits: - The bitstream can be parsed without having to load the whole buffer. It is limited to parsing a int32 at a time (for simplicity), but the oapv parsing code doesn't need more than that. - Supports seeking the underlying archive and pick up bitstream parsing at any point. - It is also possible to use interchangeably with the oapv implementation, however it requires reading the whole buffer in memory and is thus undesirable in the context of TMV.
- L36 _public prototype_ `explicit FApvBitReader(const FString& InFilename, FArchive* InArchive = nullptr);` — Construct the bit reader. @param InFileName filename of the file to read from. @param InArchive Archive to use instead of opening one.
- L38 _public prototype_ `~FApvBitReader();`
- L40 _public function_ `bool IsValid() const`
- L45 _public function_ `int64 Tell() const`
- L50 _public function_ `int64 TotalSize() const`
- L55 _public function_ `bool AtEnd() const`
- L60 _public function_ `void Seek(int64 InOffset)`
- L70 _public function_ `bool Flush(int32 InNumBytes)`
- L104 _public function_ `void Align8()`
- L111 _public function_ `void SkipCode(int32 InNumBits)`
- L125 _public function_ `void Skip(int32 InNumBits)`
- L142 _public function_ `uint32 ReadBits(int32 InNumBits)`
- L163 _public function_ `template<typename T> void ReadValue(T& OutValue)`
- L176 _public member_ `FString Filename;` — Loaded file name
- L179 _public member_ `FArchive* FileReader;` — File reader
- L183 _private member_ `uint32 Code = 0;` — Intermediate code buffer.
- L186 _private member_ `int32 LeftBits = 0;` — Number of bits left in Code.
- L189 _private member_ `TUniquePtr<FArchive> OwnedFileReader;` — File reader internally opened.

#### struct `UE::ApvMedia::FApvAccessUnitHeader`  
`struct FApvAccessUnitHeader`  
_L194-206_
- L196 _public member_ `int32 Size = 0;`
- L197 _public member_ `int64 StartOffset = 0;`
- L199 _public function_ `void Read(FApvBitReader& InBitStream)`

#### struct `UE::ApvMedia::FApvPbuHeader`  
`struct FApvPbuHeader`  
_L208-219_
- L210 _public member_ `int8 Type = 0;`
- L211 _public member_ `int16 GroupId = 0;`
- L213 _public function_ `void Read(FApvBitReader& InBitStream)`

#### struct `UE::ApvMedia::FApvFrameInfo`  
`struct FApvFrameInfo`  
_L221-373_
- L223 _public member_ `uint8 ProfileIdc;`
- L224 _public member_ `uint8 LevelIdc;`
- L225 _public member_ `uint8 BandIdc;`
- L226 _public member_ `uint32 Width;`
- L227 _public member_ `uint32 Height;`
- L228 _public member_ `uint8 ChromaFormatIdc;` — See: https://www.ietf.org/archive/id/draft-lim-apv-04.html#_table-chroma_format_idc
- L229 _public member_ `uint8 BitDepth;`
- L230 _public member_ `uint8 CaptureTimeDistance;`
- L232 _public function_ `void Read(FApvBitReader& InBitStream)`
- L246 _public function_ `int32 GetNumComponents() const`
- L256 _public function_ `int32 GetColorFormat() const`
- L270 _public function_ `int32 GetColorSpace() const` — In oapv, "Colorspace" if a FrameInfo is defined as the combo of bit depth and color format.
- L278 _public function_ `static inline int32 AlignWidthToMB(int32 InWidth)` — Align the given width to Macroblock dimensions.
- L284 _public function_ `static inline int32 AlignHeightToMB(int32 InHeight)` — Align the given height to Macroblock dimensions.
- L294 _public function_ `int32 GetPlaneWidth(int32 InComponent, bool bInMBAligned) const` — Return the given component's plane width. @param InComponent Specify the component @param bInMBAligned Indicate if the value is to be aligned to Macroblock.
- L302 _public function_ `int32 GetPlaneHeight(int32 InComponent, bool bInMBAligned) const` — Get the Macro block aligned height.
- L310 _public function_ `int32 GetWidth_MBAligned() const` — Get the full frame's width aligned to macroblock.
- L316 _public function_ `int32 GetHeight_MBAligned() const` — Get the full frame's height aligned to macroblock.
- L321 _public function_ `int32 GetSubWidthC() const`
- L327 _public function_ `int32 GetSubHeightC() const`
- L334 _public function_ `void ToFrameInfo(const FApvPbuHeader& InPbuHeader, oapv_frm_info_t& OutFrameInfo) const` — Utility to convert the parsed frame info back to the oapv type for inter op.
- L349 _public function_ `void SetChromaFormatFromColorSpace(int InColorSpace)`
- L362 _public function_ `void FromFrameInfo(const oapv_frm_info_t& InFrameInfo)`

#### struct `UE::ApvMedia::FApvColorDescription`  
`struct FApvColorDescription`  
_L375-389_
- L377 _public member_ `uint8 ColorPrimaries = 2;` — Unspecified
- L378 _public member_ `uint8 TransferCharacteristic = 2;` — Unspecified
- L379 _public member_ `uint8 MatrixCoefficients = 2;` — Unspecified
- L380 _public member_ `uint8 FullRangeFlag = 0;`
- L382 _public function_ `void Read(FApvBitReader& InBitStream)`

#### struct `UE::ApvMedia::FApvTileInfo`  
`struct FApvTileInfo`  
_L391-455_
- L393 _public member_ `int32 TileWidthInMbs = 0;`
- L394 _public member_ `int32 TileHeightInMbs = 0;`
- L395 _public member_ `int8 TileSizePresentInHeaderFlag = 0;`
- L396 _public member_ `TArray<uint32> TileSizes;`
- L398 _public function_ `void Read(const FApvFrameInfo& InFrameInfo, FApvBitReader& InBitStream)`
- L423 _public function_ `int32 GetTileWidthInSamples() const`
- L428 _public function_ `int32 GetTileHeightInSamples() const`
- L433 _public function_ `FIntPoint GetTileSizeInSamples() const`
- L438 _public function_ `FIntPoint GetNumTiles(const FApvFrameInfo& InFrameInfo) const`

#### struct `UE::ApvMedia::FApvFrameHeader`  
`struct FApvFrameHeader`  
_L458-556_
- desc: https://www.ietf.org/archive/id/draft-lim-apv-04.html#name-frame-header
- L460 _public member_ `FApvFrameInfo FrameInfo;`
- L461 _public member_ `uint8 ColorDescriptionPresentFlag = 0;`
- L462 _public member_ `FApvColorDescription ColorDescription;`
- L463 _public member_ `uint8 UseQMatrix = 0;`
- L464 _public member_ `uint8 QMatrix[OAPV_MAX_CC][OAPV_BLK_H][OAPV_BLK_W];`
- L465 _public member_ `FApvTileInfo TileInfo;`
- L467 _public function_ `void Read(FApvBitReader& InBitStream)`
- L497 _public function_ `void ToFrameInfo(const FApvPbuHeader& InPbuHeader, oapv_frm_info_t& OutFrameInfo) const`
- L516 _public function_ `FIntPoint GetTileSizeInSamples() const`
- L521 _public function_ `FIntPoint GetNumTiles() const`
- L527 _private function_ `void ReadQMatrix(FApvBitReader& InBitStream)`
- L542 _private function_ `void InitQMatrix()`

#### struct `UE::ApvMedia::FApvParserFrameHeader`  
`struct FApvParserFrameHeader`  
_L559-572_
- desc: Wraps a frame header during parsing to be able to seek again.
- L562 _public member_ `int64 PbuStartOffset = 0;` — Keep track of the frame pbu start offset (after reading pbu size) in the file so we can seek to it.
- L565 _public member_ `int32 PbuSize = 0;` — Keep track of the frame pbu size.
- L568 _public member_ `int16 GroupId = 0;` — Frame pbu group Id.
- L571 _public member_ `FApvFrameHeader FrameHeader;` — Parsed frame header.

#### struct `UE::ApvMedia::FApvParser`  
`struct FApvParser`  
_L577-584_
- desc: Apv Bitstream Parser utility functions.
- L583 _public prototype_ `static bool ParseFrameInfo(FApvBitReader& InStream, const FApvAccessUnitHeader& InAccessUnitHeader, TArray<FApvParserFrameHeader>& OutFrameHeaders);` — This function is a version of oapvd_info that doesn't require reading the whole access unit in memory. It parses info on all primary and non-primary frames.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ApvMedia` (scope `UE`)
- L169 _function_ `template<typename T> friend FApvBitReader& operator<<(FApvBitReader& InBitStream, T& OutValue)` (scope `UE::ApvMedia`)
- L192 _variable_ `static constexpr uint32 Apv1Signature = 0x61507631;` (scope `UE::ApvMedia`) — "aPv1"

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/ApvMediaLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogApvMedia, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogApvMedia, Log, All);`

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/ApvMediaSettings.h` (Private)


#### class `UApvMediaSettings`  
`class UApvMediaSettings : public UDeveloperSettings`  
_L10-36_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UDeveloperSettings`
- L15 _public function_ `UApvMediaSettings()`
- L25 _public member_ `uint32 DecoderThreads = 0;` — `UPROPERTY(config, EditAnywhere, Category = Decoder)` — Number of worker thread to decode tiles (0 = automatically use the available number of cores up to a max of 32).
- L35 _public member_ `uint32 MaxEncoderBitStreamBufferSize = 128*1024*1024;` — `UPROPERTY(config, EditAnywhere, Category = Encoder)` — Maximum size for the encoder bit stream buffer. OpenApv requires specification of a maximum bit stream buffer size since the encoder doesn't reallocate its bit stream buffer. We must specify enough space to store the whole encoded access unit including all mips.

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/ApvMediaTmvDecoder.h` (Private)


#### class `FApvMediaParser`  
`class FApvMediaParser : public ITmvMediaParser`  
_L15-24_
- inherits: `ITmvMediaParser`
- desc: Implementation of a APV1 access unit parser.
- L18 _public prototype_ `FApvMediaParser() = default;`
- L19 _public prototype_ `virtual ~FApvMediaParser() override = default;`
- L22 _public prototype_ `virtual ETmvMediaDecoderResult ParseMipInfos(ITmvMediaDecoderAccessUnit& InAccessUnit, TArray<FTmvMediaFrameMipInfo>& OutMipInfos) override;`

#### class `FApvMediaTmvDecoder`  
`class FApvMediaTmvDecoder : public ITmvMediaDecoder`  
_L29-41_
- inherits: `ITmvMediaDecoder`
- desc: Implementation of a TMV decoder for the APV codec.
- L32 _public prototype_ `FApvMediaTmvDecoder(int32 InNumDecodeThreads);`
- L36 _public prototype_ `virtual ETmvMediaDecoderResult Decode(ITmvMediaDecoderAccessUnit& InAccessUnit, TArrayView<FTmvMediaDecoderMipRequest> InMipRequests) override;`
- L40 _private member_ `TUniquePtr<UE::ApvMedia::FApvDecoderContext> DecoderContext;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ApvMedia` (scope `UE`)

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/ApvMediaTmvDecoderFactory.h` (Private)


#### class `FApvMediaTmvDecoderFactory`  
`class FApvMediaTmvDecoderFactory : public ITmvMediaDecoderFactory`  
_L7-21_
- inherits: `ITmvMediaDecoderFactory`
- L10 _public prototype_ `virtual ~FApvMediaTmvDecoderFactory() = default;`
- L13 _public prototype_ `virtual const FString& GetName() const override;`
- L14 _public prototype_ `virtual TArray<FString> GetSupportedFileExtensions() const override;`
- L15 _public prototype_ `virtual int32 SupportsFormat(const FString& InCodecFormat, const TMap<FString, FVariant>& InOptions) const override;`
- L16 _public prototype_ `virtual void GetParserOptions(TMap<FString, FVariant>& OutOptions) const override;`
- L17 _public prototype_ `virtual TSharedPtr<ITmvMediaParser, ESPMode::ThreadSafe> CreateParser(const FString& InAccessUnitFormat, const TMap<FString, FVariant>& InOptions) override;`
- L18 _public prototype_ `virtual void GetDecoderOptions(TMap<FString, FVariant>& OutOptions) const override;`
- L19 _public prototype_ `virtual TSharedPtr<ITmvMediaDecoder, ESPMode::ThreadSafe> CreateDecoder(const FString& InCodecFormat, const TMap<FString, FVariant>& InOptions) override;`

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/ApvMediaTmvEncoder.h` (Private)


#### class `FApvMediaTmvEncoder`  
`class FApvMediaTmvEncoder : public ITmvMediaEncoder`  
_L16-45_
- inherits: `ITmvMediaEncoder`
- desc: Implementation of a TMV encoder for the APV codec.
- L19 _public prototype_ `FApvMediaTmvEncoder(const FApvMediaTmvEncoderOptions& InEncoderOptions);`
- L23 _public prototype_ `virtual ETmvMediaEncoderResult RequestMipInfos( const FTmvMediaFrameTimeInfo& InTimeInfo, const FTmvMediaEncoderMipInfo& InFrameInfo, TArray<FTmvMediaFrameMipInfo>& OutFrameMipInfo, FTmvMediaMessageContext* OutMessageContext) override;`
- L29 _public prototype_ `virtual ETmvMediaEncoderResult Encode( const FTmvMediaFrameTimeInfo& InTimeInfo, ITmvMediaEncoderAccessUnit& InAccessUnit, TArrayView<FTmvMediaEncoderMipRequest> InMipRequests, FTmvMediaMessageContext* OutMessageContext) override;`
- L38 _private member_ `FApvMediaTmvEncoderOptions EncoderOptions;` — Copy of the Apv Encoder options for safe access in the encoding worker thread.
- L41 _private member_ `TUniquePtr<UE::ApvMedia::FApvEncoderContext> EncoderContext;` — Wrapper for the OpenApv encoding related objects. Reason: the lifetime is not the same as the TmvEncoder itself.
- L44 _private member_ `TArray64<uint8_t> BitStreamBuffer;` — Temporary bitstream buffer for encoding. Note: encoders are already pooled, no need to pool this buffer.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ApvMedia` (scope `UE`)

### `Plugins/Media/TmvMedia/Source/ApvMedia/Private/ApvMediaTmvEncoderFactory.h` (Private)


#### class `FApvMediaTmvEncoderFactory`  
`class FApvMediaTmvEncoderFactory : public ITmvMediaEncoderFactory`  
_L8-23_
- inherits: `ITmvMediaEncoderFactory`
- desc: Implementation of OpenApv Tmv Encoder Factory
- L11 _public prototype_ `virtual ~FApvMediaTmvEncoderFactory() override = default;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public function_ `virtual bool SupportsMemoryAccessUnit() const override`
- L17 _public prototype_ `virtual void GetEncoderOptions(TInstancedStruct<FTmvMediaEncoderOptions>& OutOptions) const override;`
- L18 _public prototype_ `virtual TSharedPtr<ITmvMediaEncoder, ESPMode::ThreadSafe> CreateEncoder(const FString& InCodecFormat, const TInstancedStruct<FTmvMediaEncoderOptions>& InOptions) override;`
- L22 _public member_ `static const FLazyName EncoderName;` — Encoder Name.
