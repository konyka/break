# Plugins / NVDEC

- module root: `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVDEC`
- headers: 3; symbols: 79
- symbol kinds: class=2, function=6, macro=1, member=29, namespace=1, prototype=23, struct=4, typedef=13
- PrivateDependencyModuleNames: AVCodecsCore, CUDA, Engine, NVCodecs, VulkanRHI
- PublicDependencyModuleNames: Core, RHI, RenderCore, nvDecode

### `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVDEC/Public/NVDEC.h` (Public)


#### struct `NV_DECODE_API_FUNCTION_LIST`  
`struct NV_DECODE_API_FUNCTION_LIST`  
_L27-56_
- L29 _public typedef_ `typedef CUresult (*cuvidCreateDecoderPtr)(CUvideodecoder*, CUVIDDECODECREATEINFO*);`
- L30 _public typedef_ `typedef CUresult (*cuvidParseVideoDataPtr)(CUvideoparser, CUVIDSOURCEDATAPACKET*);`
- L31 _public typedef_ `typedef CUresult (*cuvidCreateVideoParserPtr)(CUvideoparser*, CUVIDPARSERPARAMS*);`
- L32 _public typedef_ `typedef CUresult (*cuvidDestroyVideoParserPtr)(CUvideoparser);`
- L33 _public typedef_ `typedef CUresult (*cuvidCtxLockCreatePtr)(CUvideoctxlock*, CUcontext);`
- L34 _public typedef_ `typedef CUresult (*cuvidCtxLockDestroyPtr)(CUvideoctxlock);`
- L35 _public typedef_ `typedef CUresult (*cuvidDecodePicturePtr)(CUvideodecoder, CUVIDPICPARAMS*);`
- L36 _public typedef_ `typedef CUresult (*cuvidGetDecoderCapsPtr)(CUVIDDECODECAPS*);`
- L37 _public typedef_ `typedef CUresult (*cuvidGetDecodeStatusPtr)(CUvideodecoder, int, CUVIDGETDECODESTATUS*);`
- L38 _public typedef_ `typedef CUresult (*cuvidReconfigureDecoderPtr)(CUvideodecoder, CUVIDRECONFIGUREDECODERINFO*);`
- L39 _public typedef_ `typedef CUresult (*cuvidDestroyDecoderPtr)(CUvideodecoder);`
- L40 _public typedef_ `typedef CUresult (*cuvidMapVideoFramePtr)(CUvideodecoder, int, CUdeviceptr*, unsigned int*, CUVIDPROCPARAMS*);`
- L41 _public typedef_ `typedef CUresult (*cuvidUnmapVideoFramePtr)(CUvideodecoder, CUdeviceptr);`
- L43 _public member_ `cuvidCreateDecoderPtr cuvidCreateDecoder = nullptr;`
- L44 _public member_ `cuvidParseVideoDataPtr cuvidParseVideoData = nullptr;`
- L45 _public member_ `cuvidCreateVideoParserPtr cuvidCreateVideoParser = nullptr;`
- L46 _public member_ `cuvidDestroyVideoParserPtr cuvidDestroyVideoParser = nullptr;`
- L47 _public member_ `cuvidCtxLockCreatePtr cuvidCtxLockCreate = nullptr;`
- L48 _public member_ `cuvidCtxLockDestroyPtr cuvidCtxLockDestroy = nullptr;`
- L49 _public member_ `cuvidDecodePicturePtr cuvidDecodePicture = nullptr;`
- L50 _public member_ `cuvidGetDecoderCapsPtr cuvidGetDecoderCaps = nullptr;`
- L51 _public member_ `cuvidGetDecodeStatusPtr cuvidGetDecodeStatus = nullptr;`
- L52 _public member_ `cuvidReconfigureDecoderPtr cuvidReconfigureDecoder = nullptr;`
- L53 _public member_ `cuvidDestroyDecoderPtr cuvidDestroyDecoder = nullptr;`
- L54 _public member_ `cuvidMapVideoFramePtr cuvidMapVideoFrame = nullptr;`
- L55 _public member_ `cuvidUnmapVideoFramePtr cuvidUnmapVideoFrame = nullptr;`

#### class `FNVDEC`  
`class FNVDEC : public FAPI, public NV_DECODE_API_FUNCTION_LIST`  
_L58-71_
- inherits: `FAPI,NV_DECODE_API_FUNCTION_LIST`
- L61 _public member_ `bool bHasCompatibleGPU = true;`
- L63 _public prototype_ `FNVDEC();`
- L65 _public prototype_ `virtual bool IsValid() const override;`
- L67 _public prototype_ `FString GetErrorString(CUresult ErrorCode) const;`
- L70 _private member_ `void* DllHandle = nullptr;`

### `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVDEC/Public/Video/Decoders/Configs/VideoDecoderConfigNVDEC.h` (Public)


#### struct `FVideoDecoderConfigNVDEC`  
`struct FVideoDecoderConfigNVDEC : public CUVIDDECODECREATEINFO, public FAVConfig`  
_L13-65_
- inherits: `CUVIDDECODECREATEINFO,FAVConfig`
- L23 _public function_ `FVideoDecoderConfigNVDEC(EAVPreset Preset = EAVPreset::Default) : CUVIDDECODECREATEINFO({}) , FAVConfig(Preset)`
- L39 _public function_ `FVideoDecoderConfigNVDEC(FVideoDecoderConfigNVDEC const& Other)`
- L44 _public function_ `FVideoDecoderConfigNVDEC& operator=(FVideoDecoderConfigNVDEC const& Other)`
- L51 _public function_ `bool operator==(FVideoDecoderConfigNVDEC const& Other) const`
- L56 _public function_ `bool operator!=(FVideoDecoderConfigNVDEC const& Other) const`
- L61 _public function_ `FAVResult Parse(TSharedRef<FAVInstance> const& Instance, FVideoPacket const& Packet, TArray<FParsedPicture>& OutPictures)`
- L64 _private member_ `int RefPicIdx[16];`

#### struct `FVideoDecoderConfigNVDEC::FParsedPicture`  
`struct FParsedPicture : public CUVIDPICPARAMS`  
_L16-21_
- inherits: `CUVIDPICPARAMS`
- L19 _public member_ `CUVIDDECODECREATEINFO DecodeCreateInfo;`
- L20 _public member_ `TArray<uint32> SliceOffsets;`

#### Free symbols / members of external scopes

- L68 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigNVDEC& OutConfig, struct FVideoDecoderConfig const& InConfig);` (scope `FAVExtension`)
- L71 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoDecoderConfig& OutConfig, FVideoDecoderConfigNVDEC const& InConfig);` (scope `FAVExtension`)
- L74 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigNVDEC& OutConfig, struct FVideoDecoderConfigH264 const& InConfig);` (scope `FAVExtension`)
- L77 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigNVDEC& OutConfig, struct FVideoDecoderConfigH265 const& InConfig);` (scope `FAVExtension`)
- L80 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigNVDEC& OutConfig, struct FVideoDecoderConfigAV1 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVDEC/Public/Video/Decoders/VideoDecoderNVDEC.h` (Public)


#### class `FVideoDecoderNVDEC`  
`class FVideoDecoderNVDEC : public TVideoDecoder<FVideoResourceCUDA, FVideoDecoderConfigNVDEC>`  
_L16-59_
- inherits: `TVideoDecoder<FVideoResourceCUDA,FVideoDecoderConfigNVDEC>`
- L19 _private member_ `uint8 bIsOpen : 1;`
- L20 _private member_ `CUvideodecoder Decoder = nullptr;`
- L21 _private member_ `CUvideoparser Parser = nullptr;`
- L22 _private member_ `CUvideoctxlock CtxLock;`
- L34 _private member_ `int32 FramesCount = 0;`
- L35 _private member_ `TQueue<FFrame> Frames;`
- L38 _public prototype_ `FVideoDecoderNVDEC() = default;`
- L41 _public prototype_ `virtual bool IsOpen() const override;`
- L42 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L43 _public prototype_ `virtual void Close() override;`
- L45 _public prototype_ `bool IsInitialized() const;`
- L47 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L49 _public prototype_ `bool GetCapability(CUVIDDECODECAPS& CapsToQuery) const;`
- L51 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) override;`
- L53 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<FVideoResourceCUDA>& InOutResource) override;`
- L56 _public prototype_ `int HandleVideoSequence(CUVIDEOFORMAT *VideoFormat);`
- L57 _public prototype_ `int HandlePictureDecode(CUVIDPICPARAMS *PicParams);`
- L58 _public prototype_ `int HandlePictureDisplay(CUVIDPARSERDISPINFO *DispInfo);`

#### struct `FVideoDecoderNVDEC::FFrame`  
`struct FFrame`  
_L24-32_
- L26 _public member_ `int32 SurfaceIndex;`
- L27 _public member_ `uint32 Width;`
- L28 _public member_ `uint32 Height;`
- L29 _public member_ `cudaVideoSurfaceFormat SurfaceFormat;`
- L31 _public member_ `CUVIDPROCPARAMS MapParams;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API NVDEC_API`
- L61 _namespace_ `namespace Internal`
- L63 _prototype_ `int HandleVideoSequenceCallback(void *UserData, CUVIDEOFORMAT *VideoFormat);` (scope `Internal`)
- L64 _prototype_ `int HandlePictureDecodeCallback(void *UserData, CUVIDPICPARAMS *PicParams);` (scope `Internal`)
- L65 _prototype_ `int HandlePictureDisplayCallback(void *UserData, CUVIDPARSERDISPINFO *DispInfo);` (scope `Internal`)
