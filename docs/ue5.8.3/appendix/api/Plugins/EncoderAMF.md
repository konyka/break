# Plugins / EncoderAMF

- module root: `Plugins/Media/HardwareEncoders/Source/EncoderAMF`
- headers: 2; symbols: 81
- symbol kinds: class=4, delegate=1, function=4, macro=1, member=30, namespace=8, prototype=33
- PrivateDependencyModuleNames: AVEncoder, Amf, Core, Engine, RHI, RenderCore, VulkanRHI

### `Plugins/Media/HardwareEncoders/Source/EncoderAMF/Private/Amf_Common.h` (Private)


#### class `AVEncoder::FAmfCommon`  
`class FAmfCommon`  
_L51-95_
- L55 _public prototype_ `static FAmfCommon &Setup();` — attempt to load Amf
- L58 _public prototype_ `static void Shutdown();` — shutdown - release loaded dll
- L60 _public function_ `bool GetIsAvailable() const`
- L62 _public function_ `bool GetIsCtxInitialized() const`
- L64 _public prototype_ `bool CreateEncoder(amf::AMFComponentPtr& outEncoder);`
- L66 _public function_ `AMFContextPtr GetContext()`
- L68 _public prototype_ `bool InitializeContext(ERHIInterfaceType RHIType, const FString& RHIName, void* NativeDevice, void* NativeInstance = nullptr, void* NativePhysicalDevice = nullptr);`
- L70 _public function_ `void DestroyContext()`
- L81 _private prototype_ `FAmfCommon() = default;`
- L83 _private prototype_ `void SetupAmfFunctions();`
- L85 _private member_ `static FCriticalSection ProtectSingleton;`
- L86 _private member_ `static FAmfCommon Singleton;`
- L88 _private member_ `amf_handle DllHandle = nullptr;`
- L89 _private member_ `AMFFactory* AmfFactory = NULL;`
- L90 _private member_ `AMFContextPtr AmfContext = NULL;`
- L91 _private member_ `AMFVulkanDevice AmfVulkanDevice;`
- L92 _private member_ `bool bIsAvailable = false;`
- L93 _private member_ `bool bWasSetUp = false;`
- L94 _private member_ `bool bIsCtxInitialized = false;`

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEncoderAMF, Log, All);`
- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEncoderAMF, Log, All);`
- L31 _namespace_ `namespace amf`
- L33 _namespace_ `namespace amf`
- L37 _macro_ `#define CHECK_AMF_RET(AMF_call)\`
- L47 _namespace_ `namespace AVEncoder`

### `Plugins/Media/HardwareEncoders/Source/EncoderAMF/Private/Amf_EncoderH264.h` (Private)


#### class `AVEncoder::FVideoEncoderAmf_H264`  
`class FVideoEncoderAmf_H264 : public FVideoEncoder PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L28-123_
- inherits: `FVideoEncoderPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L36 _public prototype_ `static bool GetIsAvailable(FVideoEncoderInputImpl &InInput, FVideoEncoderInfo &OutEncoderInfo);` — query whether or not encoder is supported and available
- L40 _public prototype_ `static void Register(FVideoEncoderFactory &InFactory);` — register encoder with video encoder factory
- L43 _public prototype_ `bool Setup(TSharedRef<FVideoEncoderInput> input, FLayerConfig const& config) override;`
- L44 _public prototype_ `void Encode(const TSharedPtr<FVideoEncoderInputFrame> frame, FEncodeOptions const& options) override;`
- L46 _public prototype_ `void Flush();`
- L47 _public prototype_ `void Shutdown() override;`
- L51 _protected prototype_ `FLayer* CreateLayer(uint32 layerIdx, FLayerConfig const& config) override;`
- L52 _protected prototype_ `void DestroyLayer(FLayer *layer) override;`
- L56 _private prototype_ `FVideoEncoderAmf_H264();`
- L113 _private member_ `FAmfCommon& Amf;`
- L115 _private member_ `EVideoFrameFormat FrameFormat = EVideoFrameFormat::Undefined;`
- L117 _private member_ `void* EncoderDevice;`
- L119 _private member_ `uint32 MaxFramerate = 0;`
- L120 _private member_ `amf_int64 MinQP = -1;`
- L121 _private member_ `RateControlMode RateMode = RateControlMode::CBR;`
- L122 _private member_ `bool FillData = false;`

#### class `AVEncoder::FVideoEncoderAmf_H264::FAMFLayer`  
`class FAMFLayer : public FLayer PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L59-111_
- inherits: `FLayerPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L72 _public prototype_ `FAMFLayer(uint32 layerIdx, FLayerConfig const& config, FVideoEncoderAmf_H264& encoder);`
- L74 _public prototype_ `~FAMFLayer();`
- L76 _public prototype_ `bool Setup();`
- L77 _public prototype_ `bool CreateSession();`
- L78 _public prototype_ `bool CreateInitialConfig();`
- L79 _public prototype_ `void UpdateConfig();`
- L82 _public prototype_ `template<class T> bool GetProperty(const TCHAR* PropertyToQuery, T& outProperty, const T& (*func)(const AMFVariantStruct*)) const;`
- L85 _public prototype_ `template<class T> bool GetCapability(const TCHAR* CapToQuery, T& OutCap) const;`
- L88 _public prototype_ `AMF_RESULT Encode(const TSharedPtr<FVideoEncoderInputFrameImpl> frame, FEncodeOptions const& options);`
- L90 _public prototype_ `void Flush();`
- L91 _public prototype_ `void Shutdown();`
- L92 _public prototype_ `void UpdateBitrate(uint32 InMaxBitRate, uint32 InTargetBitRate);`
- L93 _public prototype_ `void UpdateResolution(uint32 InMaxBitRate, uint32 InTargetBitRate);`
- L94 _public prototype_ `void MaybeReconfigure();`
- L95 _public prototype_ `void ProcessFrameBlocking();`
- L96 _public prototype_ `TSharedPtr<FInputOutput> GetOrCreateSurface(const TSharedPtr<FVideoEncoderInputFrameImpl> InFrame);`
- L97 _public prototype_ `bool CreateSurface(TSharedPtr<FInputOutput>& OutBuffer, const TSharedPtr<FVideoEncoderInputFrameImpl> SourceFrame, void* TextureToCompress);`
- L99 _public member_ `FVideoEncoderAmf_H264& Encoder;`
- L100 _public member_ `FAmfCommon& Amf;`
- L101 _public member_ `uint32 LayerIndex;`
- L102 _public member_ `AMFComponentPtr AmfEncoder = NULL;`
- L103 _public member_ `FDateTime LastKeyFrameTime = 0;`
- L104 _public member_ `bool bForceNextKeyframe = false;`
- L105 _public member_ `TArray<TSharedPtr<FInputOutput>> CreatedSurfaces;`
- L106 _public member_ `FThreadSafeBool bUpdateConfig = false;`
- L107 _public member_ `uint32 CurrentWidth;`
- L108 _public member_ `uint32 CurrentHeight;`
- L109 _public member_ `uint32 CurrentFrameRate;`
- L110 _public member_ `FThreadSafeBool bIsProcessingFrame = false;`

#### class `AVEncoder::FVideoEncoderAmf_H264::FAMFLayer::FInputOutput`  
`class FInputOutput`  
_L64-69_
- L67 _public member_ `void* TextureToCompress;`
- L68 _public member_ `AMFSurfacePtr Surface;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace AVEncoder`
- L19 _namespace_ `namespace AVEncoder`
- L20 _namespace_ `namespace AVEncoder`
- L21 _namespace_ `namespace AVEncoder`
- L23 _namespace_ `namespace AVEncoder`
