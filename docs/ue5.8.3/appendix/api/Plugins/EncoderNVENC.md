# Plugins / EncoderNVENC

- module root: `Plugins/Media/HardwareEncoders/Source/EncoderNVENC`
- headers: 3; symbols: 121
- symbol kinds: class=5, delegate=1, function=19, macro=1, member=47, namespace=5, prototype=42, struct=1
- PrivateDependencyModuleNames: AVEncoder, CUDA, Engine, VulkanRHI, nvEncode
- PublicDependencyModuleNames: Core, RHI, RenderCore

### `Plugins/Media/HardwareEncoders/Source/EncoderNVENC/Private/NVENCStats.h` (Private)


#### class `FNVENCStats`  
`class FNVENCStats : FTickableGameObject`  
_L9-146_
- inherits: `FTickableGameObject`
- desc: Stats about NVENC that can displayed either in the in-application HUD or in the log.
- L13 _public function_ `FNVENCStats() : bOutputToLog(false) , bOutputToScreen(false)`
- L20 _public function_ `static FNVENCStats& Get()`
- L26 _public function_ `void Tick(float DeltaTime)`
- L49 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L51 _public function_ `void SetOutputToScreen(bool bInOutputToScreen)`
- L57 _public function_ `void SetOutputToLog(bool bInOutputToLog)`
- L62 _public function_ `void SetProcessFramesFuncLatency(double InProcessFramesFuncMs)`
- L67 _public function_ `void SetTotalEncoderLatency(double InTotalEncoderLatencyMs)`
- L72 _public function_ `void SetnvEncEncodePictureLatency(double InnvEncEncodePictureMs)`
- L77 _public function_ `void SetReconfigureLatency(double InReconfigureMs)`
- L82 _public function_ `void SetQueueEncodeLatency(double InQueueEncodeMs)`
- L87 _public function_ `void SetLockOutputBufferLatency(double InLockOutputBufferMs)`
- L92 _public function_ `void SetUnlockOutputBufferLatency(double InUnlockOutputBufferMs)`
- L98 _private function_ `void EmitStat(int UniqueId, FString StringToEmit)`
- L135 _private member_ `static constexpr uint32 SmoothingPeriod = 3 * 60;`
- L136 _private member_ `bool bOutputToLog;`
- L137 _private member_ `bool bOutputToScreen;`
- L139 _private member_ `FSmoothedValue<SmoothingPeriod> ProcessFramesFuncMs;`
- L140 _private member_ `FSmoothedValue<SmoothingPeriod> TotalEncoderLatencyMs;`
- L141 _private member_ `FSmoothedValue<SmoothingPeriod> nvEncEncodePictureMs;`
- L142 _private member_ `FSmoothedValue<SmoothingPeriod> QueueEncodeMs;`
- L143 _private member_ `FSmoothedValue<SmoothingPeriod> ReconfigureMs;`
- L144 _private member_ `FSmoothedValue<SmoothingPeriod> LockOutputBufferMs;`
- L145 _private member_ `FSmoothedValue<SmoothingPeriod> UnlockOutputBufferMs;`

#### class `FNVENCStats::FSmoothedValue`  
`template<uint32 SmoothingPeriod> class FSmoothedValue`  
_L111-131_
- L114 _public function_ `double Get() const`
- L119 _public function_ `void Update(double NewValue)`
- L124 _public function_ `void Reset()`
- L130 _private member_ `TAtomic<double> Value{ 0 };`

### `Plugins/Media/HardwareEncoders/Source/EncoderNVENC/Private/NVENC_Common.h` (Private)


#### class `AVEncoder::FNVENCCommon`  
`class FNVENCCommon : public NV_ENCODE_API_FUNCTION_LIST`  
_L34-65_
- inherits: `NV_ENCODE_API_FUNCTION_LIST`
- L38 _public prototype_ `static FNVENCCommon& Setup();` — attempt to load NVENC
- L40 _public prototype_ `static void Shutdown();` — shutdown - release loaded dll
- L42 _public function_ `bool GetIsAvailable() const`
- L44 _public function_ `FString GetErrorString(void* Encoder, NVENCSTATUS ForStatus)`
- L56 _private prototype_ `FNVENCCommon() = default;`
- L58 _private prototype_ `void SetupNVENCFunctions();`
- L60 _private member_ `static FCriticalSection ProtectSingleton;`
- L61 _private member_ `static FNVENCCommon Singleton;`
- L62 _private member_ `void* DllHandle = nullptr;`
- L63 _private member_ `bool bIsAvailable = false;`
- L64 _private member_ `bool bWasSetUp = false;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEncoderNVENC, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEncoderNVENC, Log, All);`
- L26 _macro_ `#define NVENCStruct(OfType, VarName) \` — helper macro to define and clear NVENC structures also sets the struct version number
- L32 _namespace_ `namespace AVEncoder`

### `Plugins/Media/HardwareEncoders/Source/EncoderNVENC/Private/NVENC_EncoderH264.h` (Private)


#### class `AVEncoder::FVideoEncoderNVENC_H264`  
`class FVideoEncoderNVENC_H264 : public FVideoEncoder PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L18-135_
- inherits: `FVideoEncoderPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L26 _public prototype_ `bool Setup(TSharedRef<FVideoEncoderInput> InputFrameFactory, const FLayerConfig& InitConfig) override;`
- L28 _public prototype_ `void Shutdown() override;`
- L32 _public prototype_ `static bool GetIsAvailable(const FVideoEncoderInput& InFrameFactory, FVideoEncoderInfo& OutEncoderInfo);` — Query whether or not encoder is supported and available
- L36 _public prototype_ `static void Register(FVideoEncoderFactory& InFactory);` — Register encoder with video encoder factory
- L39 _public prototype_ `void Encode(const TSharedPtr<FVideoEncoderInputFrame> InFrame, const FEncodeOptions& EncodeOptions) override;`
- L41 _public prototype_ `void Flush();`
- L45 _protected prototype_ `FLayer* CreateLayer(uint32 InLayerIndex, const FLayerConfig& InLayerConfig) override;`
- L46 _protected prototype_ `void DestroyLayer(FLayer* layer) override;`
- L50 _private prototype_ `FVideoEncoderNVENC_H264();`
- L128 _private member_ `FNVENCCommon& NVENC;`
- L130 _private member_ `EVideoFrameFormat FrameFormat = EVideoFrameFormat::Undefined;`
- L134 _private member_ `void* EncoderDevice;` — this could be a TRefCountPtr<ID3D11Device>, CUcontext or void*

#### class `AVEncoder::FVideoEncoderNVENC_H264::FNVENCLayer`  
`class FNVENCLayer : public FLayer PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L53-126_
- inherits: `FLayerPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L79 _public prototype_ `FNVENCLayer(uint32 layerIdx, FLayerConfig const& config, FVideoEncoderNVENC_H264& encoder);`
- L81 _public prototype_ `~FNVENCLayer();`
- L82 _public prototype_ `bool Setup();`
- L83 _public prototype_ `bool CreateSession();`
- L84 _public prototype_ `bool CreateInitialConfig();`
- L85 _public prototype_ `int GetCapability(NV_ENC_CAPS CapsToQuery) const;`
- L86 _public prototype_ `FString GetError(NVENCSTATUS ForStatus) const;`
- L87 _public prototype_ `void MaybeReconfigure();`
- L88 _public prototype_ `void UpdateConfig();`
- L89 _public prototype_ `void UpdateLastEncodedQP(uint32 InLastEncodedQP);`
- L91 _public prototype_ `void Encode(const TSharedPtr<FVideoEncoderInputFrame> InFrame, const FEncodeOptions& EncodeOptions);`
- L93 _public prototype_ `void EncodeBuffer(FInputOutput* Buffer);`
- L94 _public prototype_ `void ProcessEncodedBuffer(FInputOutput* Buffer);`
- L95 _public prototype_ `void Flush();`
- L96 _public prototype_ `void Shutdown();`
- L97 _public prototype_ `void UpdateBitrate(uint32 InMaxBitRate, uint32 InTargetBitRate);`
- L98 _public prototype_ `void UpdateResolution(uint32 InMaxBitRate, uint32 InTargetBitRate);`
- L99 _public prototype_ `FInputOutput* GetOrCreateBuffer(const TSharedPtr<FVideoEncoderInputFrameImpl> InFrame);`
- L100 _public prototype_ `FInputOutput* CreateBuffer();`
- L101 _public prototype_ `void DestroyBuffer(FInputOutput* InBuffer);`
- L102 _public prototype_ `bool RegisterInputTexture(FInputOutput* InBuffer);`
- L103 _public prototype_ `bool UnregisterInputTexture(FInputOutput* InBuffer);`
- L104 _public prototype_ `bool MapInputTexture(FInputOutput* InBuffer);`
- L105 _public prototype_ `bool UnmapInputTexture(FInputOutput* InBuffer);`
- L106 _public prototype_ `bool LockOutputBuffer(FInputOutput* InBuffer);`
- L107 _public prototype_ `bool UnlockOutputBuffer(FInputOutput* InBuffer);`
- L108 _public prototype_ `void CreateResourceDIRECTX(FInputOutput* InBuffer, NV_ENC_REGISTER_RESOURCE& RegisterParam, FIntPoint TextureSize);`
- L109 _public prototype_ `void CreateResourceCUDAARRAY(FInputOutput* InBuffer, NV_ENC_REGISTER_RESOURCE& RegisterParam, FIntPoint TextureSize);`
- L112 _public member_ `FVideoEncoderNVENC_H264& Encoder;`
- L113 _public member_ `FNVENCCommon& NVENC;`
- L114 _public member_ `GUID CodecGUID;`
- L115 _public member_ `uint32 LayerIndex;`
- L116 _public member_ `void* NVEncoder = nullptr;`
- L117 _public member_ `NV_ENC_INITIALIZE_PARAMS EncoderInitParams;`
- L118 _public member_ `NV_ENC_CONFIG EncoderConfig;`
- L119 _public member_ `FDateTime LastKeyFrameTime = 0;`
- L120 _public member_ `bool bForceNextKeyframe = false;`
- L121 _public member_ `uint32 LastEncodedQP = 0;`
- L124 _private member_ `FThreadSafeBool bIsProcessingFrame = false;`
- L125 _private member_ `FInputOutput* InputOutputBuffer = nullptr;`

#### struct `AVEncoder::FVideoEncoderNVENC_H264::FNVENCLayer::FInputOutput`  
`struct FInputOutput`  
_L58-76_
- L60 _public member_ `TSharedPtr<AVEncoder::FVideoEncoderInputFrameImpl> SourceFrame = nullptr;`
- L61 _public member_ `void* InputTexture = nullptr;`
- L62 _public member_ `uint32 Width = 0;`
- L63 _public member_ `uint32 Height = 0;`
- L64 _public member_ `uint32 Pitch = 0;`
- L65 _public member_ `NV_ENC_BUFFER_FORMAT BufferFormat = NV_ENC_BUFFER_FORMAT_UNDEFINED;`
- L66 _public member_ `NV_ENC_REGISTERED_PTR RegisteredInput = nullptr;`
- L67 _public member_ `NV_ENC_INPUT_PTR MappedInput = nullptr;`
- L68 _public member_ `NV_ENC_PIC_PARAMS PicParams = {};`
- L69 _public member_ `NV_ENC_OUTPUT_PTR OutputBitstream = nullptr;`
- L70 _public member_ `const void* BitstreamData = nullptr;`
- L71 _public member_ `uint32 BitstreamDataSize = 0;`
- L72 _public member_ `NV_ENC_PIC_TYPE PictureType = NV_ENC_PIC_TYPE_UNKNOWN;`
- L73 _public member_ `uint32 FrameAvgQP = 0;`
- L74 _public member_ `uint64 TimeStamp;`
- L75 _public member_ `uint64 SubmitTimeCycles;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AVEncoder`
- L12 _namespace_ `namespace AVEncoder`
- L13 _namespace_ `namespace AVEncoder`
- L15 _namespace_ `namespace AVEncoder`
