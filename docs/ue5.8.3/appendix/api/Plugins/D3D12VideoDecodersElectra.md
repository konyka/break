# Plugins / D3D12VideoDecodersElectra

- module root: `Plugins/Media/D3D12VideoDecodersElectra/Source`
- headers: 7; symbols: 258
- symbol kinds: class=9, delegate=1, enum=2, enumerator=4, function=47, macro=7, member=115, namespace=3, prototype=59, struct=11
- PrivateDependencyModuleNames: Core, ElectraBase, ElectraCodecFactory, ElectraDecoders, ElectraSamples, RHI
- PrivateIncludePathModuleNames: D3D12RHI

### `Plugins/Media/D3D12VideoDecodersElectra/Source/Private/D3D12VideoDecodersElectraModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D12VideoDecodersElectra, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D12VideoDecodersElectra, Log, All);`

### `Plugins/Media/D3D12VideoDecodersElectra/Source/Private/DecoderErrors_D3D12.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define ERRCODE_INTERNAL_NO_ERROR 0`
- L6 _macro_ `#define ERRCODE_INTERNAL_BAD_PARAMETER 1`
- L7 _macro_ `#define ERRCODE_INTERNAL_ALREADY_CLOSED 2`
- L8 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_PARSE_CSD 3`
- L9 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CREATE_DECODER 4`
- L10 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CREATE_BUFFER 5`
- L11 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_DECODE 6`

### `Plugins/Media/D3D12VideoDecodersElectra/Source/Private/VideoDecoder_D3D12.h` (Private)


#### class `FD3D12VideoDecoder`  
`class FD3D12VideoDecoder`  
_L7-12_
- L10 _public prototype_ `static void Startup();`
- L11 _public prototype_ `static void Shutdown();`

### `Plugins/Media/D3D12VideoDecodersElectra/Source/Private/VideoDecoder_D3D12_Common.h` (Private)


#### class `ElectraVideoDecodersD3D12Video::FCodecFormatHelper`  
`class FCodecFormatHelper`  
_L25-80_
- L47 _public prototype_ `FCodecFormatHelper() = default;`
- L48 _public prototype_ `~FCodecFormatHelper() = default;`
- L49 _public prototype_ `int32 FindSupportedFormats(ID3D12Device* InD3D12Device);`
- L50 _public prototype_ `const FCodecInfo* HaveFormat(ECodecType InType, int32 InNumBits);`
- L52 _public function_ `TRefCountPtr<ID3D12VideoDevice> GetVideoDevice()`
- L56 _public function_ `uint32 GetVideoDeviceNodeIndex()`
- L63 _private member_ `const GUID D3D12_VIDEO_DECODE_PROFILE_H264 = { 0x1b81be68, 0xa0c7, 0x11d3, { 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5 } };` — The profile GUIDs we support.
- L64 _private member_ `const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN = { 0x5b11d51b, 0x2f4c, 0x4452, { 0xbc, 0xc3, 0x09, 0xf2, 0xa1, 0x16, 0x0c, 0xc0 } };`
- L65 _private member_ `const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10 = { 0x107af0e0, 0xef1a, 0x4d19, { 0xab, 0xa8, 0x67, 0xa1, 0x63, 0x07, 0x3d, 0x13 } };`
- L66 _private member_ `const GUID D3D12_VIDEO_DECODE_PROFILE_VP9 = { 0x463707f8, 0xa1d0, 0x4585, { 0x87, 0x6d, 0x83, 0xaa, 0x6d, 0x60, 0xb8, 0x9e } };`
- L67 _private member_ `const GUID D3D12_VIDEO_DECODE_PROFILE_VP9_10BIT_PROFILE2 = { 0xa4c749ef, 0x6ecf, 0x48aa, { 0x84, 0x48, 0x50, 0xa7, 0xa1, 0x16, 0x5f, 0xf7 } };`
- L77 _private member_ `TArray<FCodecInfo> CodecInfos;`
- L78 _private member_ `TRefCountPtr<ID3D12VideoDevice> DxVideoDevice;`
- L79 _private member_ `uint32 DxDeviceNodeIndex = 0;`

#### enum `ElectraVideoDecodersD3D12Video::FCodecFormatHelper::ECodecType`  
`enum class ECodecType`  
_L28-33_
- L30 _public enumerator_ `H264`
- L31 _public enumerator_ `H265`
- L32 _public enumerator_ `VP9`

#### struct `ElectraVideoDecodersD3D12Video::FCodecFormatHelper::FCodecInfo`  
`struct FCodecInfo`  
_L35-45_
- L37 _public member_ `ECodecType CodecType;`
- L38 _public member_ `bool b10Bit = false;`
- L39 _public member_ `GUID ProfileGUID;`
- L40 _public member_ `TArray<DXGI_FORMAT> PixelFormats;`
- L41 _public function_ `bool operator == (const FCodecInfo& rhs) const`

#### class `ElectraVideoDecodersD3D12Video::FSyncObject`  
`class FSyncObject`  
_L82-147_
- L85 _public function_ `virtual ~FSyncObject()`
- L94 _public function_ `HRESULT Create(const TRefCountPtr<ID3D12Device>& InDevice, uint64 InInitialValue)`
- L107 _public function_ `TRefCountPtr<ID3D12Fence> GetFence()`
- L111 _public function_ `void* GetID3D12Fence()`
- L115 _public function_ `uint64 IncrementAndGetNewFenceValue()`
- L120 _public function_ `uint64& GetFenceValue()`
- L125 _public function_ `bool AwaitCompletion(uint32 InTimeoutMillisec)`
- L144 _private member_ `TRefCountPtr<ID3D12Fence> Fence;`
- L145 _private member_ `HANDLE EventHandle = INVALID_HANDLE_VALUE;`
- L146 _private member_ `uint64 Value = 0;`

#### struct `ElectraVideoDecodersD3D12Video::FDecodedFrame`  
`struct FDecodedFrame`  
_L149-154_
- L151 _public member_ `TRefCountPtr<ID3D12Resource> Texture;`
- L152 _public member_ `FSyncObject Sync;`
- L153 _public member_ `int32 IndexInPictureBuffer = 0;`

#### class `ElectraVideoDecodersD3D12Video::FDecodedPictureBuffer`  
`class FDecodedPictureBuffer`  
_L156-169_
- L159 _public prototype_ `~FDecodedPictureBuffer();`
- L160 _public prototype_ `void ReleaseAllFrames(int32 InWaitForEachFrameMillis);`
- L161 _public prototype_ `TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe> GetFrameAtIndex(int32 InIndex);`
- L162 _public prototype_ `TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe> GetFrameForResource(const ID3D12Resource* InResource);`
- L163 _public prototype_ `TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe> GetNextUnusedFrame();`
- L164 _public prototype_ `void ReturnUnusedFrameToAvailableQueue(TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe>&& InFrame);`
- L165 _public prototype_ `void ReturnFrameToAvailableQueue(TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe>&& InFrame);`
- L167 _public member_ `TArray<TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe>> Frames;`
- L168 _public member_ `TArray<TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe>> AvailableQueue;`

#### class `ElectraVideoDecodersD3D12Video::FVideoDecoderOutputD3D12Electra`  
`class FVideoDecoderOutputD3D12Electra : public IElectraDecoderVideoOutput, public IElectraDecoderVideoOutputImageBuffers`  
_L171-329_
- inherits: `IElectraDecoderVideoOutput,IElectraDecoderVideoOutputImageBuffers`
- L174 _public prototype_ `virtual ~FVideoDecoderOutputD3D12Electra() = default;`
- L176 _public function_ `FTimespan GetPTS() const override`
- L180 _public function_ `uint64 GetUserValue() const override`
- L185 _public function_ `EOutputType GetOutputType() const`
- L190 _public function_ `int32 GetWidth() const override`
- L194 _public function_ `int32 GetHeight() const override`
- L198 _public function_ `int32 GetDecodedWidth() const override`
- L202 _public function_ `int32 GetDecodedHeight() const override`
- L206 _public function_ `FElectraVideoDecoderOutputCropValues GetCropValues() const override`
- L210 _public function_ `int32 GetAspectRatioW() const override`
- L214 _public function_ `int32 GetAspectRatioH() const override`
- L218 _public function_ `int32 GetFrameRateNumerator() const override`
- L222 _public function_ `int32 GetFrameRateDenominator() const override`
- L226 _public function_ `int32 GetNumberOfBits() const override`
- L230 _public function_ `void GetExtraValues(TMap<FString, FVariant>& OutExtraValues) const override`
- L234 _public function_ `void* GetPlatformOutputHandle(EElectraDecoderPlatformOutputHandleType InTypeOfHandle) const override`
- L242 _public function_ `IElectraDecoderVideoOutput::EImageCopyResult CopyPlatformImage(IElectraDecoderVideoOutputCopyResources* InCopyResources) const override`
- L248 _public function_ `uint32 GetCodec4CC() const override` — Methods from IElectraDecoderVideoOutputImageBuffers
- L252 _public function_ `int32 GetNumberOfBuffers() const override`
- L256 _public function_ `TSharedPtr<TArray64<uint8>, ESPMode::ThreadSafe> GetBufferDataByIndex(int32 InBufferIndex) const override`
- L262 _public function_ `void* GetBufferTextureByIndex(int32 InBufferIndex) const override`
- L271 _public function_ `EPixelFormat GetBufferFormatByIndex(int32 InBufferIndex) const override`
- L275 _public function_ `EElectraTextureSamplePixelEncoding GetBufferEncodingByIndex(int32 InBufferIndex) const override`
- L279 _public function_ `int32 GetBufferPitchByIndex(int32 InBufferIndex) const override`
- L283 _public function_ `bool GetBufferTextureSyncByIndex(int32 InBufferIndex, FElectraDecoderOutputSync& SyncObject) const override`
- L301 _public member_ `FTimespan PTS;`
- L302 _public member_ `uint64 UserValue = 0;`
- L304 _public member_ `FElectraVideoDecoderOutputCropValues Crop;`
- L305 _public member_ `int32 ImageWidth = 0;`
- L306 _public member_ `int32 ImageHeight = 0;`
- L307 _public member_ `int32 Width = 0;`
- L308 _public member_ `int32 Height = 0;`
- L309 _public member_ `int32 Pitch = 0;`
- L310 _public member_ `int32 NumBits = 0;`
- L311 _public member_ `int32 AspectW = 1;`
- L312 _public member_ `int32 AspectH = 1;`
- L313 _public member_ `int32 FrameRateN = 0;`
- L314 _public member_ `int32 FrameRateD = 0;`
- L315 _public member_ `int32 PixelFormat = 0;`
- L316 _public member_ `TMap<FString, FVariant> ExtraValues;`
- L317 _public member_ `EOutputType OutputType = EOutputType::Output;`
- L319 _public member_ `uint64 UserValue0 = 0;`
- L320 _public member_ `bool bDoNotOutput = false;`
- L322 _public member_ `uint32 Codec4CC = 0;`
- L323 _public member_ `EPixelFormat BufferFormat = EPixelFormat::PF_Unknown;`
- L324 _public member_ `EElectraTextureSamplePixelEncoding BufferEncoding = EElectraTextureSamplePixelEncoding::Native;`
- L327 _public member_ `TSharedPtr<FDecodedPictureBuffer, ESPMode::ThreadSafe> OwningDPB;`
- L328 _public member_ `TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe> DecodedFrame;`

#### class `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder`  
`class FD3D12VideoDecoder : public IElectraDecoder`  
_L332-495_
- inherits: `IElectraDecoder`
- L335 _public prototype_ `static bool CheckPlatformDecodeCapabilities(D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT& InOutDecodeSupport, const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InOptions);`
- L336 _public prototype_ `FD3D12VideoDecoder(const FCodecFormatHelper::FCodecInfo& InCodecInfo, const D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT& InDecodeSupport, const TMap<FString, FVariant>& InOptions, const TRefCountPtr<ID3D12Device>& InD3D12Device, const TRefCountPtr<ID3D12VideoDevice>& InVideoDevice, uint32 InVideoDeviceNodeIndex);`
- L337 _public prototype_ `virtual ~FD3D12VideoDecoder();`
- L339 _protected function_ `EType GetType() const override`
- L341 _protected prototype_ `void GetFeatures(TMap<FString, FVariant>& OutFeatures) const override;`
- L342 _protected function_ `FError GetError() const override`
- L344 _protected prototype_ `void Close() override;`
- L345 _protected prototype_ `ECSDCompatibility IsCompatibleWith(const TMap<FString, FVariant>& CSDAndAdditionalOptions) = 0;`
- L346 _protected prototype_ `bool ResetToCleanStart() override;`
- L347 _protected prototype_ `EDecoderError DecodeAccessUnit(const FInputAccessUnit& InInputAccessUnit, const TMap<FString, FVariant>& InAdditionalOptions) = 0;`
- L348 _protected prototype_ `EDecoderError SendEndOfData() = 0;`
- L349 _protected prototype_ `EDecoderError Flush() = 0;`
- L350 _protected prototype_ `EOutputStatus HaveOutput() override;`
- L351 _protected prototype_ `TSharedPtr<IElectraDecoderOutput, ESPMode::ThreadSafe> GetOutput() override;`
- L352 _protected prototype_ `TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> CreateBitstreamProcessor() = 0;`
- L353 _protected function_ `void Suspend() override`
- L355 _protected function_ `void Resume() override`
- L359 _protected function_ `bool PostError(HRESULT ApiReturnValue, FString Message, int32 Code)`
- L447 _protected prototype_ `bool InternalDecoderCreate();`
- L448 _protected prototype_ `void ReturnAllFrames();`
- L450 _protected prototype_ `bool CreateDecoderHeap(int32 InDPBSize, int32 InMaxWidth, int32 InMaxHeight, int32 InImageSizeAlignment);`
- L451 _protected prototype_ `bool CreateDPB(TSharedPtr<FDecodedPictureBuffer, ESPMode::ThreadSafe>& OutDPB, int32 InMaxWidth, int32 InMaxHeight, int32 InImageSizeAlignment, int32 InNumFrames);`
- L453 _protected function_ `constexpr uint32 GetNodeMask() const`
- L456 _protected prototype_ `bool PrepareBitstreamBuffer(const TSharedPtr<FFrameDecodeResource, ESPMode::ThreadSafe>& InFrameDecodeResourceToPrepare, uint32 InMaxInputBufferSize);`
- L458 _protected prototype_ `EDecoderError ExecuteCommonDecode(const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS& InInputArgs, const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS& InOutputArgs);`
- L460 _protected prototype_ `virtual bool InternalResetToCleanStart() = 0;`
- L462 _protected member_ `FCodecFormatHelper::FCodecInfo CodecInfo;`
- L463 _protected member_ `D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT DecodeSupport;`
- L464 _protected member_ `Electra::FCodecTypeFormat InitialCodecFormat;`
- L465 _protected member_ `TMap<FString, FVariant> InitialCreationOptions;`
- L466 _protected member_ `TRefCountPtr<ID3D12Device> D3D12Device;`
- L467 _protected member_ `TRefCountPtr<ID3D12VideoDevice> VideoDevice;`
- L468 _protected member_ `uint32 VideoDeviceNodeIndex = 0;`
- L469 _protected member_ `IElectraDecoder::FError LastError;`
- L471 _protected member_ `TUniquePtr<FSyncObject> VideoDecoderSync;`
- L472 _protected member_ `TRefCountPtr<ID3D12CommandQueue> VideoDecoderCommandQueue;`
- L473 _protected member_ `TRefCountPtr<ID3D12CommandAllocator> VideoDecoderCommandAllocator;`
- L474 _protected member_ `TRefCountPtr<ID3D12VideoDecodeCommandList> VideoDecoderCommandList;`
- L475 _protected member_ `TRefCountPtr<ID3D12VideoDecoder> VideoDecoder;`
- L476 _protected member_ `uint32 StatusReportFeedbackNumber = 0;`
- L478 _protected member_ `FDecoderConfiguration CurrentConfig;`
- L481 _protected member_ `TQueue<TSharedPtr<FFrameDecodeResource, ESPMode::ThreadSafe>> AvailableFrameDecodeResourceQueue;` — Queue of frame decode resources that are available again for re-use.
- L485 _protected member_ `TSharedPtr<FDecodedPictureBuffer, ESPMode::ThreadSafe> DPB;`
- L486 _protected member_ `TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe> MissingReferenceFrame;`
- L488 _protected member_ `uint32 RunningFrameNumLo = 0;`
- L489 _protected member_ `uint32 RunningFrameNumHi = 0;`
- L490 _protected member_ `bool bIsDraining = false;`
- L492 _protected member_ `TArray<TSharedPtr<FVideoDecoderOutputD3D12Electra, ESPMode::ThreadSafe>> FramesInDecoder;`
- L493 _protected member_ `TArray<TSharedPtr<FVideoDecoderOutputD3D12Electra, ESPMode::ThreadSafe>> FramesReadyForOutput;`
- L494 _protected member_ `TArray<TSharedPtr<FVideoDecoderOutputD3D12Electra, ESPMode::ThreadSafe>> FramesGivenOutForOutput;`

#### class `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FAutoReturnUnusedFrame`  
`class FAutoReturnUnusedFrame`  
_L367-387_
- L370 _public function_ `FAutoReturnUnusedFrame(const TSharedPtr<FDecodedPictureBuffer, ESPMode::ThreadSafe>& InDPB, const TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe>& InFrame) : OwningDPB(InDPB), ThisFrame(InFrame)`
- L373 _public function_ `~FAutoReturnUnusedFrame()`
- L380 _public function_ `void ReleaseOwnership()`
- L385 _private member_ `TSharedPtr<FDecodedPictureBuffer, ESPMode::ThreadSafe> OwningDPB;`
- L386 _private member_ `TSharedPtr<FDecodedFrame, ESPMode::ThreadSafe> ThisFrame;`

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FFrameDecodeResource`  
`struct FFrameDecodeResource`  
_L390-426_
- desc: A structure holding every resource needed to decode one frame.
- L393 _public member_ `TRefCountPtr<ID3D12VideoDecoder> D3DDecoder;` — Decoder keep-alive resources.
- L394 _public member_ `TRefCountPtr<ID3D12VideoDecoderHeap> D3DDecoderHeap;`
- L401 _public member_ `ID3D12Resource* ReferenceFrameList[kMaxRefFrames] {};`
- L402 _public member_ `UINT ReferenceFrameListSubRes[kMaxRefFrames] { 0 };`
- L403 _public member_ `TRefCountPtr<ID3D12Resource> D3DBitstreamBuffer;`
- L404 _public member_ `uint32 D3DBitstreamBufferAllocatedSize = 0;`
- L405 _public member_ `uint32 D3DBitstreamBufferPayloadSize = 0;`
- L425 _public member_ `TVariant<FInputEmpty, FInputH264, FInputH265> PicInput;`

#### enum `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FFrameDecodeResource::(anonymous)`  
``  
_L398-400_

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FFrameDecodeResource::FInputEmpty`  
`struct FInputEmpty`  
_L407-409_

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FFrameDecodeResource::FInputH264`  
`struct FInputH264`  
_L411-416_
- L413 _public member_ `DXVA_PicParams_H264 PicParams;`
- L414 _public member_ `DXVA_Qmatrix_H264 QuantMtx;`
- L415 _public member_ `TArray<DXVA_Slice_H264_Short> SliceHeaders;`

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FFrameDecodeResource::FInputH265`  
`struct FInputH265`  
_L418-423_
- L420 _public member_ `DXVA_PicParams_HEVC PicParams;`
- L421 _public member_ `DXVA_Qmatrix_HEVC QuantMtx;`
- L422 _public member_ `TArray<DXVA_Slice_HEVC_Short> SliceHeaders;`

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FDecoderConfiguration`  
`struct FDecoderConfiguration`  
_L428-445_
- L430 _public function_ `void Reset()`
- L439 _public member_ `int32 MaxDecodedWidth = 0;`
- L440 _public member_ `int32 MaxDecodedHeight = 0;`
- L441 _public member_ `int32 MaxNumInDPB = 0;`
- L442 _public member_ `TRefCountPtr<ID3D12VideoDecoderHeap> VideoDecoderHeap;`
- L443 _public member_ `int32 VideoDecoderDPBWidth = 0;`
- L444 _public member_ `int32 VideoDecoderDPBHeight = 0;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace ElectraVideoDecodersD3D12Video`
- L399 _enumerator_ `kMaxRefFrames = 32` (scope `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder::FFrameDecodeResource::__anon69a9f4f50103`)

### `Plugins/Media/D3D12VideoDecodersElectra/Source/Private/VideoDecoder_D3D12_H264.h` (Private)


#### class `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder_H264`  
`class FD3D12VideoDecoder_H264 : public FD3D12VideoDecoder`  
_L12-60_
- inherits: `FD3D12VideoDecoder`
- L15 _public prototype_ `FD3D12VideoDecoder_H264(const FCodecFormatHelper::FCodecInfo& InCodecInfo, const D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT& InDecodeSupport, const TMap<FString, FVariant>& InOptions, const TRefCountPtr<ID3D12Device>& InD3D12Device, const TRefCountPtr<ID3D12VideoDevice>& InVideoDevice, uint32 InVideoDeviceNodeIndex);`
- L16 _public prototype_ `virtual ~FD3D12VideoDecoder_H264();`
- L19 _protected prototype_ `ECSDCompatibility IsCompatibleWith(const TMap<FString, FVariant>& CSDAndAdditionalOptions) override;`
- L20 _protected prototype_ `TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> CreateBitstreamProcessor() override;`
- L21 _protected prototype_ `EDecoderError DecodeAccessUnit(const FInputAccessUnit& InInputAccessUnit, const TMap<FString, FVariant>& InAdditionalOptions) override;`
- L22 _protected prototype_ `EDecoderError SendEndOfData() override;`
- L23 _protected prototype_ `EDecoderError Flush() override;`
- L26 _private prototype_ `bool InternalResetToCleanStart() override;`
- L54 _private prototype_ `EDecoderError GetCodecSpecificDataH264(FBitstreamParamsH264& OutBitstreamParamsH264, const TMap<FString, FVariant>& InAdditionalOptions, bool bIsRequired);`
- L55 _private prototype_ `EDecoderError DecodeAccessUnitH264(const FInputAccessUnit& InInputAccessUnit, const TMap<FString, FVariant>& InAdditionalOptions);`
- L56 _private prototype_ `EDecoderError DecodeSlicesH264(const FInputAccessUnit& InInputAccessUnit, const TArray<FBitstreamParamsH264::FSliceDecodeInfo>& InSliceInfos, const ElectraDecodersUtil::MPEG::H264::FSequenceParameterSet& InSequenceParameterSet, const ElectraDecodersUtil::MPEG::H264::FPictureParameterSet& InPictureParameterSet);`
- L57 _private prototype_ `EDecoderError HandleOutputListH264(const TArray<ElectraDecodersUtil::MPEG::H264::FOutputFrameInfo>& InOutputFrameInfos);`
- L59 _private member_ `FBitstreamParamsH264 BitstreamParamsH264;`

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder_H264::FBitstreamParamsH264`  
`struct FBitstreamParamsH264`  
_L28-52_
- L30 _public function_ `void Reset()`
- L48 _public member_ `TMap<uint32, ElectraDecodersUtil::MPEG::H264::FSequenceParameterSet> SPSs;`
- L49 _public member_ `TMap<uint32, ElectraDecodersUtil::MPEG::H264::FPictureParameterSet> PPSs;`
- L51 _public member_ `ElectraDecodersUtil::MPEG::H264::FSlicePOCVars DPBPOC;`

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder_H264::FBitstreamParamsH264::FSliceDecodeInfo`  
`struct FSliceDecodeInfo`  
_L36-46_
- L38 _public member_ `uint8 NalUnitType = 0;`
- L39 _public member_ `uint8 NalRefIdc = 0;`
- L41 _public member_ `ElectraDecodersUtil::MPEG::H264::FSliceHeader Header;` — Parsed slice header.
- L43 _public member_ `const uint8* NalUnitStartAddress = nullptr;` — Address of the nal unit byte of this slice.
- L45 _public member_ `uint32 NumBytesInSlice = 0;` — The number of bytes making up this slice, including the nal unit byte.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ElectraVideoDecodersD3D12Video`

### `Plugins/Media/D3D12VideoDecodersElectra/Source/Private/VideoDecoder_D3D12_H265.h` (Private)


#### class `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder_H265`  
`class FD3D12VideoDecoder_H265 : public FD3D12VideoDecoder`  
_L12-76_
- inherits: `FD3D12VideoDecoder`
- L15 _public prototype_ `FD3D12VideoDecoder_H265(const FCodecFormatHelper::FCodecInfo& InCodecInfo, const D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT& InDecodeSupport, const TMap<FString, FVariant>& InOptions, const TRefCountPtr<ID3D12Device>& InD3D12Device, const TRefCountPtr<ID3D12VideoDevice>& InVideoDevice, uint32 InVideoDeviceNodeIndex);`
- L16 _public prototype_ `virtual ~FD3D12VideoDecoder_H265();`
- L19 _protected prototype_ `ECSDCompatibility IsCompatibleWith(const TMap<FString, FVariant>& CSDAndAdditionalOptions) override;`
- L20 _protected prototype_ `TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> CreateBitstreamProcessor() override;`
- L21 _protected prototype_ `EDecoderError DecodeAccessUnit(const FInputAccessUnit& InInputAccessUnit, const TMap<FString, FVariant>& InAdditionalOptions) override;`
- L22 _protected prototype_ `EDecoderError SendEndOfData() override;`
- L23 _protected prototype_ `EDecoderError Flush() override;`
- L26 _private prototype_ `bool InternalResetToCleanStart() override;`
- L65 _private prototype_ `EDecoderError GetCodecSpecificDataH265(FBitstreamParamsH265& OutBitstreamParamsH265, const TMap<FString, FVariant>& InAdditionalOptions, bool bIsRequired);`
- L66 _private prototype_ `EDecoderError DecodeAccessUnitH265(const FInputAccessUnit& InInputAccessUnit, const TMap<FString, FVariant>& InAdditionalOptions);`
- L67 _private prototype_ `EDecoderError DecodeSlicesH265(const FInputAccessUnit& InInputAccessUnit, const TArray<FBitstreamParamsH265::FSliceDecodeInfo>& InSliceInfos, const ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet& InSequenceParameterSet, const ElectraDecodersUtil::MPEG::H265::FPictureParameterSet& InPictureParameterSet);`
- L68 _private prototype_ `EDecoderError HandleOutputListH265(const TArray<ElectraDecodersUtil::MPEG::H265::FDecodedPictureBuffer::FDPBOutputFrame>& InOutputFrameInfos);`
- L70 _private member_ `FBitstreamParamsH265 BitstreamParamsH265;`
- L71 _private member_ `static const uint8 ScanOrderDiag4[16];`
- L72 _private member_ `static const uint8 ScanOrderDiag8[64];`
- L74 _private function_ `constexpr int32 GetFrameAlignment()` — Use the maximum MinCbSizeY value for image alignment as stipulated in the DXVA HEVC documentation.

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder_H265::FBitstreamParamsH265`  
`struct FBitstreamParamsH265`  
_L28-63_
- L30 _public function_ `void Reset()`
- L55 _public member_ `TMap<uint32, ElectraDecodersUtil::MPEG::H265::FVideoParameterSet> VPSs;`
- L56 _public member_ `TMap<uint32, ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet> SPSs;`
- L57 _public member_ `TMap<uint32, ElectraDecodersUtil::MPEG::H265::FPictureParameterSet> PPSs;`
- L58 _public member_ `TArray<uint8> CurrentCSD;`
- L59 _public member_ `ElectraDecodersUtil::MPEG::H265::FDecodedPictureBuffer DPB;`
- L60 _public member_ `int32 AssociatedIRAP = -1;`
- L61 _public member_ `int32 IRAPCount = 0;`
- L62 _public member_ `bool bIsFirstInSequence = true;`

#### struct `ElectraVideoDecodersD3D12Video::FD3D12VideoDecoder_H265::FBitstreamParamsH265::FSliceDecodeInfo`  
`struct FSliceDecodeInfo`  
_L41-53_
- L43 _public member_ `uint8 NalUnitType = 0;`
- L44 _public member_ `uint8 NuhLayerId = 0;`
- L45 _public member_ `uint8 NumTemporalIdPlus1 = 0;`
- L48 _public member_ `ElectraDecodersUtil::MPEG::H265::FSliceSegmentHeader Header;` — Parsed slice header.
- L50 _public member_ `const uint8* NalUnitStartAddress = nullptr;` — Address of the nal unit byte of this slice.
- L52 _public member_ `uint32 NumBytesInSlice = 0;` — The number of bytes making up this slice, including the nal unit byte.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ElectraVideoDecodersD3D12Video`

### `Plugins/Media/D3D12VideoDecodersElectra/Source/Private/Windows/WindowsPlatformHeaders_Video_D3D.h` (Private)
_(no declarations extracted)_
