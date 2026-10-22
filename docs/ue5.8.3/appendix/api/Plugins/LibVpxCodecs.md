# Plugins / LibVpxCodecs

- module root: `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs`
- headers: 12; symbols: 311
- symbol kinds: class=8, enum=2, enumerator=4, function=87, macro=3, member=123, namespace=1, prototype=74, struct=9
- PrivateDependencyModuleNames: Engine, LibVpx
- PublicDependencyModuleNames: AVCodecsCore, Core, RenderCore

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/LibVpx.h` (Public)


#### class `FLibVpx`  
`class FLibVpx : public FAPI`  
_L24-30_
- inherits: `FAPI`
- L27 _public prototype_ `FLibVpx() = default;`
- L29 _public prototype_ `virtual bool IsValid() const override;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API LIBVPXCODECS_API`

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Decoders/Configs/VideoDecoderConfigLibVpx.h` (Public)


#### struct `FVideoDecoderConfigLibVpx`  
`struct FVideoDecoderConfigLibVpx : public FAVConfig`  
_L9-46_
- inherits: `FAVConfig`
- L13 _public member_ `uint32 MaxOutputWidth = 0;` — Values are parsed from the bitstream during decoding
- L14 _public member_ `uint32 MaxOutputHeight = 0;`
- L16 _public member_ `int32 NumberOfCores = 0;`
- L18 _public function_ `FVideoDecoderConfigLibVpx() : FAVConfig()`
- L23 _public function_ `FVideoDecoderConfigLibVpx(FVideoDecoderConfigLibVpx const& Other)`
- L28 _public function_ `FVideoDecoderConfigLibVpx& operator=(FVideoDecoderConfigLibVpx const& Other)`
- L35 _public function_ `bool operator==(FVideoDecoderConfigLibVpx const& Other) const`
- L42 _public function_ `bool operator!=(FVideoDecoderConfigLibVpx const& Other) const`

#### Free symbols / members of external scopes

- L49 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigLibVpx& OutConfig, struct FVideoDecoderConfig const& InConfig);` (scope `FAVExtension`)
- L52 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoDecoderConfig& OutConfig, FVideoDecoderConfigLibVpx const& InConfig);` (scope `FAVExtension`)
- L55 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigLibVpx& OutConfig, struct FVideoDecoderConfigVP8 const& InConfig);` (scope `FAVExtension`)
- L58 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigLibVpx& OutConfig, struct FVideoDecoderConfigVP9 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Decoders/VideoDecoderLibVpxVP8.h` (Public)


#### class `TVideoDecoderLibVpxVP8`  
`template <typename TResource> class TVideoDecoderLibVpxVP8 : public TVideoDecoder<TResource, FVideoDecoderConfigLibVpx>`  
_L14-54_
- inherits: `TVideoDecoder<TResource,FVideoDecoderConfigLibVpx>`
- L17 _private member_ `uint8 bInitialized : 1;`
- L18 _private member_ `uint64 FrameCount = 0;`
- L19 _private member_ `bool bIsOpen = false;`
- L20 _private member_ `vpx_codec_ctx_t* Decoder = nullptr;`
- L21 _private member_ `int PropagationCount = -1;`
- L22 _private member_ `bool bKeyFrameRequired = true;`
- L34 _private member_ `TQueue<FFrame> Frames;`
- L37 _public prototype_ `TVideoDecoderLibVpxVP8() = default;`
- L40 _public prototype_ `virtual bool IsOpen() const override;`
- L41 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L42 _public prototype_ `virtual void Close() override;`
- L44 _public prototype_ `bool IsInitialized() const;`
- L46 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L48 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource) override;`
- L50 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) override;`
- L53 _private prototype_ `FAVResult Destroy();`

#### struct `TVideoDecoderLibVpxVP8::FFrame`  
`struct FFrame`  
_L24-32_
- L26 _public member_ `TArray<uint8> RawData;`
- L27 _public member_ `int StrideY = 0;`
- L28 _public member_ `int StrideUV = 0;`
- L29 _public member_ `int Width = 0;`
- L30 _public member_ `int Height = 0;`
- L31 _public member_ `uint64 FrameNumber = 0;`

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Decoders/VideoDecoderLibVpxVP8.hpp` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `template <typename TResource> TVideoDecoderLibVpxVP8<TResource>::~TVideoDecoderLibVpxVP8()` (scope `TVideoDecoderLibVpxVP8`)
- L15 _function_ `template <typename TResource> bool TVideoDecoderLibVpxVP8<TResource>::IsOpen() const` (scope `TVideoDecoderLibVpxVP8`)
- L21 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP8<TResource>::Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` (scope `TVideoDecoderLibVpxVP8`)
- L35 _function_ `template <typename TResource> void TVideoDecoderLibVpxVP8<TResource>::Close()` (scope `TVideoDecoderLibVpxVP8`)
- L43 _function_ `template <typename TResource> bool TVideoDecoderLibVpxVP8<TResource>::IsInitialized() const` (scope `TVideoDecoderLibVpxVP8`)
- L49 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP8<TResource>::ApplyConfig()` (scope `TVideoDecoderLibVpxVP8`)
- L106 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP8<TResource>::SendPacket(FVideoPacket const& Packet)` (scope `TVideoDecoderLibVpxVP8`)
- L212 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP8<TResource>::ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource)` (scope `TVideoDecoderLibVpxVP8`)
- L241 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP8<TResource>::Destroy()` (scope `TVideoDecoderLibVpxVP8`)

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Decoders/VideoDecoderLibVpxVP9.h` (Public)


#### class `TVideoDecoderLibVpxVP9`  
`template <typename TResource> class TVideoDecoderLibVpxVP9 : public TVideoDecoder<TResource, FVideoDecoderConfigLibVpx>`  
_L15-58_
- inherits: `TVideoDecoder<TResource,FVideoDecoderConfigLibVpx>`
- L18 _private member_ `uint8 bInitialized : 1;`
- L20 _private member_ `uint64 FrameCount = 0;`
- L22 _private member_ `bool bIsOpen = false;`
- L24 _private member_ `vpx_codec_ctx_t *Decoder = nullptr;`
- L26 _private member_ `bool bKeyFrameRequired = true;`
- L38 _private member_ `TQueue<FFrame> Frames;`
- L41 _public prototype_ `TVideoDecoderLibVpxVP9() = default;`
- L44 _public prototype_ `virtual bool IsOpen() const override;`
- L45 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const &NewDevice, TSharedRef<FAVInstance> const &NewInstance) override;`
- L46 _public prototype_ `virtual void Close() override;`
- L48 _public prototype_ `bool IsInitialized() const;`
- L50 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L52 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource> &InOutResource) override;`
- L54 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const &Packet) override;`
- L57 _private prototype_ `FAVResult Destroy();`

#### struct `TVideoDecoderLibVpxVP9::FFrame`  
`struct FFrame`  
_L28-36_
- L30 _public member_ `TArray<uint8> RawData;`
- L31 _public member_ `int StrideY = 0;`
- L32 _public member_ `int StrideUV = 0;`
- L33 _public member_ `int Width = 0;`
- L34 _public member_ `int Height = 0;`
- L35 _public member_ `uint64 FrameNumber = 0;`

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Decoders/VideoDecoderLibVpxVP9.hpp` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `template <typename TResource> TVideoDecoderLibVpxVP9<TResource>::~TVideoDecoderLibVpxVP9()` (scope `TVideoDecoderLibVpxVP9`)
- L15 _function_ `template <typename TResource> bool TVideoDecoderLibVpxVP9<TResource>::IsOpen() const` (scope `TVideoDecoderLibVpxVP9`)
- L21 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP9<TResource>::Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` (scope `TVideoDecoderLibVpxVP9`)
- L35 _function_ `template <typename TResource> void TVideoDecoderLibVpxVP9<TResource>::Close()` (scope `TVideoDecoderLibVpxVP9`)
- L41 _function_ `template <typename TResource> bool TVideoDecoderLibVpxVP9<TResource>::IsInitialized() const` (scope `TVideoDecoderLibVpxVP9`)
- L47 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP9<TResource>::ApplyConfig()` (scope `TVideoDecoderLibVpxVP9`)
- L125 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP9<TResource>::SendPacket(FVideoPacket const& Packet)` (scope `TVideoDecoderLibVpxVP9`)
- L215 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP9<TResource>::ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource)` (scope `TVideoDecoderLibVpxVP9`)
- L244 _function_ `template <typename TResource> FAVResult TVideoDecoderLibVpxVP9<TResource>::Destroy()` (scope `TVideoDecoderLibVpxVP9`)

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Encoders/Configs/VideoEncoderConfigLibVpx.h` (Public)


#### struct `FVideoEncoderConfigLibVpx`  
`struct FVideoEncoderConfigLibVpx : public FAVConfig`  
_L13-134_
- inherits: `FAVConfig`
- L16 _public member_ `uint32 Width = 1920;`
- L17 _public member_ `uint32 Height = 1080;`
- L18 _public member_ `uint32 Framerate = 60;`
- L19 _public member_ `int32 MaxBitrate = 20000000;`
- L20 _public member_ `int32 TargetBitrate = 10000000;`
- L21 _public member_ `int32 MinBitrate = 5000000;`
- L22 _public member_ `TOptional<int32> Bitrates[Video::MaxSpatialLayers][Video::MaxTemporalStreams];`
- L23 _public member_ `uint32 KeyframeInterval = 0;`
- L24 _public member_ `EVideoFormat PixelFormat;`
- L25 _public member_ `uint32 MinQP;`
- L26 _public member_ `uint32 MaxQP;`
- L28 _public member_ `int32 NumberOfCores = 0;`
- L29 _public member_ `bool bDenoisingOn = false;`
- L30 _public member_ `bool bAdaptiveQpMode = false;`
- L31 _public member_ `bool bAutomaticResizeOn = false;`
- L32 _public member_ `bool bFlexibleMode = false;`
- L33 _public member_ `EInterLayerPrediction InterLayerPrediction = EInterLayerPrediction::Off;`
- L35 _public member_ `uint8 NumberOfSpatialLayers = 1;`
- L36 _public member_ `uint8 NumberOfTemporalLayers = 1;`
- L37 _public member_ `FSpatialLayer SpatialLayers[Video::MaxSpatialLayers];`
- L39 _public member_ `uint8 NumberOfSimulcastStreams;`
- L40 _public member_ `FSpatialLayer SimulcastStreams[Video::MaxSimulcastStreams];`
- L42 _public member_ `EScalabilityMode ScalabilityMode = EScalabilityMode::None;`
- L44 _public function_ `FVideoEncoderConfigLibVpx() : FAVConfig()`
- L49 _public function_ `FVideoEncoderConfigLibVpx(FVideoEncoderConfigLibVpx const& Other)`
- L54 _public function_ `FVideoEncoderConfigLibVpx& operator=(FVideoEncoderConfigLibVpx const& Other)`
- L61 _public function_ `bool operator==(FVideoEncoderConfigLibVpx const& Other) const`
- L88 _public function_ `bool operator!=(FVideoEncoderConfigLibVpx const& Other) const`
- L93 _public function_ `bool SameBitrates(const TOptional<int32> OtherBitrates[Video::MaxSpatialLayers][Video::MaxTemporalStreams]) const`
- L109 _public function_ `bool SameSpatialLayers(const FSpatialLayer OtherSpatialLayers[Video::MaxSpatialLayers]) const`
- L122 _public function_ `bool SameSimulcastStreams(const FSpatialLayer OtherSimulcastStreams[Video::MaxSimulcastStreams]) const`

#### Free symbols / members of external scopes

- L137 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigLibVpx& OutConfig, struct FVideoEncoderConfig const& InConfig);` (scope `FAVExtension`)
- L140 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoEncoderConfig& OutConfig, FVideoEncoderConfigLibVpx const& InConfig);` (scope `FAVExtension`)
- L143 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigLibVpx& OutConfig, struct FVideoEncoderConfigVP8 const& InConfig);` (scope `FAVExtension`)
- L146 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigLibVpx& OutConfig, struct FVideoEncoderConfigVP9 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Encoders/VideoEncoderLibVpxVP8.h` (Public)


#### class `TVideoEncoderLibVpxVP8`  
`template <typename TResource> class TVideoEncoderLibVpxVP8 : public TVideoEncoder<TResource, FVideoEncoderConfigLibVpx>`  
_L16-70_
- inherits: `TVideoEncoder<TResource,FVideoEncoderConfigLibVpx>`
- L19 _private member_ `bool bIsOpen = false;`
- L21 _private member_ `int64_t Timestamp = 0;`
- L22 _private member_ `int QpMax = 56;`
- L23 _private member_ `int CpuSpeedDefault = -6;`
- L24 _private member_ `int NumCores = 0;`
- L25 _private member_ `uint32_t RCMaxIntraTarget = 0;`
- L26 _private member_ `int NumActiveStreams = 0;`
- L27 _private member_ `bool bKeyFrameRequest = false;`
- L28 _private member_ `bool bSendStream = false;`
- L29 _private member_ `int CpuSpeed = 0;`
- L30 _private member_ `uint64 FrameCount = 0;`
- L32 _private member_ `TUniquePtr<vpx_image_t, LibVpxUtil::FImageDeleter> RawImage;`
- L33 _private member_ `TUniquePtr<vpx_codec_ctx_t, LibVpxUtil::FCodecContextDeleter> Encoder;`
- L34 _private member_ `TUniquePtr<vpx_codec_enc_cfg_t> VpxConfig;`
- L36 _private member_ `TQueue<FVideoPacket> Packets;`
- L38 _private member_ `TQueue<UE::AVCodecCore::VP8::FVP8FrameConfig> PendingFrames;`
- L41 _public prototype_ `TVideoEncoderLibVpxVP8() = default;`
- L44 _public prototype_ `virtual bool IsOpen() const override;`
- L45 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L46 _public prototype_ `virtual void Close() override;`
- L48 _public prototype_ `bool IsInitialized() const;`
- L50 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L52 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<FVideoResourceCPU> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) override;`
- L54 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override;`
- L63 _private prototype_ `FAVResult Destroy();`
- L64 _private prototype_ `uint32_t MaxIntraTarget(uint32_t OptimalBuffersize, uint32_t MaxFramerate);`
- L65 _private prototype_ `int GetCpuSpeed(uint32_t Width, uint32_t Height);`
- L66 _private prototype_ `int NumberOfThreads(uint32_t Width, uint32_t Height, int Cpus);`
- L67 _private prototype_ `FAVResult InitAndSetControlSettings(FVideoEncoderConfigLibVpx const& Config);`
- L68 _private prototype_ `void MaybeUpdatePixelFormat(vpx_img_fmt Format);`
- L69 _private prototype_ `EEncodeResult GetEncodedPartitions(uint32 Timestamp, bool bRetransmissionAllowed);`

#### enum `TVideoEncoderLibVpxVP8::EEncodeResult`  
`enum class EEncodeResult : uint8`  
_L57-61_
- L59 _public enumerator_ `Success`
- L60 _public enumerator_ `TargetBitrateOvershoot`

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Encoders/VideoEncoderLibVpxVP8.hpp` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define SAFECONTROL(Encoder, Setting, Value) \`
- L21 _function_ `template <typename TResource> TVideoEncoderLibVpxVP8<TResource>::~TVideoEncoderLibVpxVP8()` (scope `TVideoEncoderLibVpxVP8`)
- L27 _function_ `template <typename TResource> bool TVideoEncoderLibVpxVP8<TResource>::IsOpen() const` (scope `TVideoEncoderLibVpxVP8`)
- L33 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP8<TResource>::Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` (scope `TVideoEncoderLibVpxVP8`)
- L47 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP8<TResource>::Close()` (scope `TVideoEncoderLibVpxVP8`)
- L55 _function_ `template <typename TResource> bool TVideoEncoderLibVpxVP8<TResource>::IsInitialized() const` (scope `TVideoEncoderLibVpxVP8`)
- L61 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP8<TResource>::ApplyConfig()` (scope `TVideoEncoderLibVpxVP8`)
- L212 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP8<TResource>::SendFrame(TSharedPtr<FVideoResourceCPU> const& Resource, uint32 InTimestamp, bool bForceKeyframe)` (scope `TVideoEncoderLibVpxVP8`)
- L304 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP8<TResource>::ReceivePacket(FVideoPacket& OutPacket)` (scope `TVideoEncoderLibVpxVP8`)
- L320 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP8<TResource>::Destroy()` (scope `TVideoEncoderLibVpxVP8`)
- L343 _function_ `template <typename TResource> uint32_t TVideoEncoderLibVpxVP8<TResource>::MaxIntraTarget(uint32_t OptimalBuffersize, uint32_t MaxFramerate)` (scope `TVideoEncoderLibVpxVP8`)
- L360 _function_ `template <typename TResource> int TVideoEncoderLibVpxVP8<TResource>::GetCpuSpeed(uint32_t Width, uint32_t Height)` (scope `TVideoEncoderLibVpxVP8`)
- L373 _function_ `template <typename TResource> int TVideoEncoderLibVpxVP8<TResource>::NumberOfThreads(uint32_t Width, uint32_t Height, int Cpus)` (scope `TVideoEncoderLibVpxVP8`)
- L403 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP8<TResource>::InitAndSetControlSettings(FVideoEncoderConfigLibVpx const& Config)` (scope `TVideoEncoderLibVpxVP8`)
- L426 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP8<TResource>::MaybeUpdatePixelFormat(vpx_img_fmt Format)` (scope `TVideoEncoderLibVpxVP8`)
- L439 _function_ `template <typename TResource> typename TVideoEncoderLibVpxVP8<TResource>::EEncodeResult TVideoEncoderLibVpxVP8<TResource>::GetEncodedPartitions(uint32 InTimestamp, bool bRetransmissionAllowed)` (scope `TVideoEncoderLibVpxVP8`)

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Encoders/VideoEncoderLibVpxVP9.h` (Public)


#### class `TVideoEncoderLibVpxVP9`  
`template <typename TResource> class TVideoEncoderLibVpxVP9 : public TVideoEncoder<TResource, FVideoEncoderConfigLibVpx>`  
_L17-215_
- inherits: `TVideoEncoder<TResource,FVideoEncoderConfigLibVpx>`
- L20 _private member_ `uint64 FrameCount = 0;`
- L22 _private member_ `TQueue<FVideoPacket> Packets;`
- L24 _private member_ `bool bIsOpen = false;`
- L27 _public prototype_ `TVideoEncoderLibVpxVP9() = default;`
- L30 _public prototype_ `virtual bool IsOpen() const override;`
- L31 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L32 _public prototype_ `virtual void Close() override;`
- L34 _public prototype_ `bool IsInitialized() const;`
- L36 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L38 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<FVideoResourceCPU> const& Resource, uint32 Timestamp, bool bTriggerKeyFrame = false) override;`
- L40 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override;`
- L43 _private prototype_ `FAVResult Destroy();`
- L44 _private prototype_ `uint32 MaxIntraTarget(uint32 OptimalBuffersize, uint32 MaxFramerate);`
- L45 _private prototype_ `int NumberOfThreads(uint32 Width, uint32 Height, int Cpus);`
- L46 _private prototype_ `FAVResult InitAndSetControlSettings(FVideoEncoderConfigLibVpx const& Config);`
- L47 _private prototype_ `bool ExplicitlyConfiguredSpatialLayers(FVideoEncoderConfigLibVpx const& Config) const;`
- L48 _private prototype_ `void UpdatePerformanceFlags(FVideoEncoderConfigLibVpx const& Config);`
- L49 _private prototype_ `TUniquePtr<FScalableVideoController> CreateScalabilityStructureFromConfig(FVideoEncoderConfigLibVpx const& Config);`
- L50 _private prototype_ `bool SetSvcRates(FVideoEncoderConfigLibVpx const& Config, const FVideoBitrateAllocation& Allocation);`
- L51 _private prototype_ `void MaybeRewrapRawWithFormat(const vpx_img_fmt Format);`
- L52 _private prototype_ `TTuple<size_t, size_t> GetActiveLayers(const FVideoBitrateAllocation& Allocation);`
- L56 _private prototype_ `void EnableSpatialLayer(int Sid);` — Configures which spatial layers libvpx should encode according to configuration provided by SvcController.
- L57 _private prototype_ `void DisableSpatialLayer(int Sid);`
- L58 _private prototype_ `void SetActiveSpatialLayers();`
- L60 _private prototype_ `void DeliverBufferedFrame(bool bEndOfPicture);`
- L61 _private prototype_ `bool PopulateCodecSpecific(FCodecSpecificInfo* CodecSpecificInfo, TOptional<int>* SpatialIdx, TOptional<int>* TemporalIdx, const vpx_codec_cx_pkt& Packet);`
- L62 _private prototype_ `void FillReferenceIndices(const vpx_codec_cx_pkt& Packet, const size_t PicNum, const bool bInterLayerPredicted, FCodecSpecificInfoVP9* Info);`
- L63 _private prototype_ `void UpdateReferenceBuffers(const vpx_codec_cx_pkt& Packet, size_t PicNum);`
- L64 _private prototype_ `vpx_svc_ref_frame_config_t SetReferences(TArray<FScalableVideoController::FLayerFrameConfig>& LayerFrames);`
- L65 _private prototype_ `vpx_svc_ref_frame_config_t SetReferences(bool bIsKeyPic, int FirstActiveSpatialLayerId);`
- L70 _private function_ `friend bool operator==(const FRefFrameBuffer& Lhs, const FRefFrameBuffer& Rhs)`
- L105 _private prototype_ `static FPerformanceFlags GetDefaultPerformanceFlags();`
- L170 _private member_ `EProfile Profile = EProfile::Profile0;`
- L171 _private member_ `int64 Timestamp = 0;`
- L172 _private member_ `bool bForceKeyFrame = true;`
- L173 _private member_ `size_t PicsSinceKey = 0;`
- L174 _private member_ `uint8 NumTemporalLayers = 0;` — Number of configured TLs
- L175 _private member_ `uint8 NumSpatialLayers = 0;` — Number of configured SLs
- L176 _private member_ `uint8 NumActiveSpatialLayers = 0;` — Number of actively encoded SLs
- L177 _private member_ `uint8 FirstActiveLayer = 0;`
- L178 _private member_ `bool bIsSvc = false;`
- L179 _private member_ `bool bIsFlexibleMode = false;`
- L180 _private member_ `EInterLayerPrediction InterLayerPrediction = EInterLayerPrediction::On;`
- L181 _private member_ `bool bExternalRefControl = false;`
- L182 _private member_ `bool bFullSuperframeDrop = true;`
- L183 _private member_ `bool bLayerBuffering = false;`
- L184 _private member_ `bool bFirstFrameInPicture = true;`
- L185 _private member_ `uint32 RCMaxIntraTarget = 0;`
- L186 _private member_ `FEncodedImage EncodedImage;`
- L187 _private member_ `FGroupOfFramesInfo Gof;`
- L188 _private member_ `FVideoBitrateAllocation CurrentBitrateAllocation;`
- L189 _private member_ `bool bSsInfoNeeded = false;`
- L190 _private member_ `bool bForceAllActiveLayers = false;`
- L191 _private member_ `bool bVpxConfigChanged = true;`
- L192 _private member_ `FCodecSpecificInfo CodecSpecific;`
- L195 _private member_ `const FPerformanceFlags PerformanceFlags = GetDefaultPerformanceFlags();` — Performance flags, ordered by `min_pixel_count`.
- L198 _private member_ `TArray<FParameterSet> PerformanceFlagsBySpatialIndex;` — Caching of of `speed_configs_`, where index i maps to the resolution as specified in `codec_.spatialLayer[i]`.
- L200 _private member_ `TArray<FRefFrameBuffer> RefBuf;`
- L201 _private member_ `TArray<FScalableVideoController::FLayerFrameConfig> LayerFrames;`
- L203 _private member_ `TUniquePtr<FScalableVideoController> SvcController = nullptr;`
- L204 _private member_ `TUniquePtr<FInputImage> InputImage = nullptr;`
- L207 _private member_ `TUniquePtr<vpx_codec_ctx_t, LibVpxUtil::FCodecContextDeleter> Encoder = nullptr;`
- L208 _private member_ `TUniquePtr<vpx_codec_enc_cfg_t> VpxConfig = nullptr;`
- L209 _private member_ `TUniquePtr<vpx_image_t, LibVpxUtil::FImageDeleter> RawImage = nullptr;`
- L210 _private member_ `TUniquePtr<vpx_svc_extra_cfg_t> SvcParams = nullptr;`
- L211 _private member_ `TUniquePtr<vpx_svc_frame_drop_t> SvcDropFrame = nullptr;`
- L214 _public prototype_ `void GetEncodedLayerFrame(const vpx_codec_cx_pkt* Packet);`

#### struct `TVideoEncoderLibVpxVP9::FRefFrameBuffer`  
`struct FRefFrameBuffer`  
_L68-78_
- L75 _public member_ `size_t PicNum = 0;`
- L76 _public member_ `int SpatialLayerId = 0;`
- L77 _public member_ `int TemporalLayerId = 0;`

#### struct `TVideoEncoderLibVpxVP9::FParameterSet`  
`struct FParameterSet`  
_L80-89_
- L82 _public member_ `int BaseLayerSpeed = -1;` — Speed setting for TL0.
- L83 _public member_ `int HighLayerSpeed = -1;` — Speed setting for TL1-TL3.
- L87 _public member_ `int DeblockMode = 0;` — 0 = deblock all temporal layers (TL) 1 = disable deblock for top-most TL 2 = disable deblock for all TLs
- L88 _public member_ `bool bAllowDenoising = true;`

#### struct `TVideoEncoderLibVpxVP9::FPerformanceFlags`  
`struct FPerformanceFlags`  
_L91-104_
- L99 _public member_ `bool bUsePerLayerSpeed = false;` — If false, a lookup will be made in `settings_by_resolution` base on the highest currently active resolution, and the overall speed then set to to the `base_layer_speed` matching that entry. If true, each active resolution will have it's speed and deblock_mode set based on it resolution, and the high layer speed configured for non base temporal layer frames.
- L103 _public member_ `TSortedMap<int, FParameterSet> SettingsByResolution;` — Map from min pixel count to settings for that resolution and above. E.g. if you want some settings A if below wvga (640x360) and some other setting B at wvga and above, you'd use map {{0, A}, {230400, B}}.

#### enum `TVideoEncoderLibVpxVP9::EFrameType`  
`enum class EFrameType : uint8`  
_L107-111_
- L109 _public enumerator_ `I`
- L110 _public enumerator_ `P`

#### class `TVideoEncoderLibVpxVP9::FInputImage`  
`class FInputImage`  
_L113-122_
- L116 _public function_ `FInputImage(uint32 Timestamp) : Timestamp(Timestamp)`
- L121 _public member_ `uint32 Timestamp;`

#### class `TVideoEncoderLibVpxVP9::FEncodedImage`  
`class FEncodedImage`  
_L124-167_
- L127 _public function_ `TArray<uint8> GetEncodedData()`
- L132 _public function_ `void SetEncodedData(TArray<uint8> InEncodedData)`
- L138 _public function_ `size_t GetSize() const`
- L143 _public function_ `void SetSize(size_t NewSize)`
- L151 _public member_ `EFrameType FrameType = EFrameType::P;`
- L152 _public member_ `int32 Width = 0;`
- L153 _public member_ `int32 Height = 0;`
- L154 _public member_ `uint32 Timestamp = 0;`
- L155 _public member_ `int32 QP = -1;`
- L156 _public member_ `TOptional<int> SpatialIndex;`
- L157 _public member_ `TOptional<int> TemporalIndex;`
- L160 _private function_ `size_t Capacity() const`
- L165 _private member_ `TArray<uint8> EncodedData;`
- L166 _private member_ `size_t Size = 0;` — Size of encoded frame data.

#### Free symbols / members of external scopes

- L217 _namespace_ `namespace Internal`
- L220 _function_ `template <typename TResource> inline void EncoderOutputCodedPacketCallback(vpx_codec_cx_pkt* Packet, void* UserData)` (scope `Internal`)

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Encoders/VideoEncoderLibVpxVP9.hpp` (Public)


#### Free symbols / members of external scopes

- L15 _macro_ `#define SAFECONTROLVP9(Encoder, Setting, Value) \`
- L27 _function_ `template <typename TResource> typename TVideoEncoderLibVpxVP9<TResource>::FPerformanceFlags TVideoEncoderLibVpxVP9<TResource>::GetDefaultPerformanceFlags()` (scope `TVideoEncoderLibVpxVP9`)
- L52 _function_ `template <typename TResource> TVideoEncoderLibVpxVP9<TResource>::~TVideoEncoderLibVpxVP9()` (scope `TVideoEncoderLibVpxVP9`)
- L58 _function_ `template <typename TResource> bool TVideoEncoderLibVpxVP9<TResource>::IsOpen() const` (scope `TVideoEncoderLibVpxVP9`)
- L64 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP9<TResource>::Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` (scope `TVideoEncoderLibVpxVP9`)
- L78 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::Close()` (scope `TVideoEncoderLibVpxVP9`)
- L86 _function_ `template <typename TResource> bool TVideoEncoderLibVpxVP9<TResource>::IsInitialized() const` (scope `TVideoEncoderLibVpxVP9`)
- L92 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP9<TResource>::ApplyConfig()` (scope `TVideoEncoderLibVpxVP9`)
- L356 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP9<TResource>::SendFrame(TSharedPtr<FVideoResourceCPU> const& Resource, uint32 InTimestamp, bool bTriggerKeyFrame)` (scope `TVideoEncoderLibVpxVP9`)
- L608 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP9<TResource>::ReceivePacket(FVideoPacket& OutPacket)` (scope `TVideoEncoderLibVpxVP9`)
- L624 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP9<TResource>::Destroy()` (scope `TVideoEncoderLibVpxVP9`)
- L652 _function_ `template <typename TResource> uint32_t TVideoEncoderLibVpxVP9<TResource>::MaxIntraTarget(uint32_t OptimalBuffersize, uint32_t MaxFramerate)` (scope `TVideoEncoderLibVpxVP9`)
- L669 _function_ `template <typename TResource> int TVideoEncoderLibVpxVP9<TResource>::NumberOfThreads(uint32_t Width, uint32_t Height, int Cpus)` (scope `TVideoEncoderLibVpxVP9`)
- L692 _function_ `template <typename TResource> FAVResult TVideoEncoderLibVpxVP9<TResource>::InitAndSetControlSettings(FVideoEncoderConfigLibVpx const& Config)` (scope `TVideoEncoderLibVpxVP9`)
- L878 _function_ `template <typename TResource> TUniquePtr<FScalableVideoController> TVideoEncoderLibVpxVP9<TResource>::CreateScalabilityStructureFromConfig(FVideoEncoderConfigLibVpx const& Config)` (scope `TVideoEncoderLibVpxVP9`)
- L961 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::EnableSpatialLayer(int Sid)` (scope `TVideoEncoderLibVpxVP9`)
- L978 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::DisableSpatialLayer(int Sid)` (scope `TVideoEncoderLibVpxVP9`)
- L994 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::SetActiveSpatialLayers()` (scope `TVideoEncoderLibVpxVP9`)
- L1018 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::GetEncodedLayerFrame(const vpx_codec_cx_pkt* Packet)` (scope `TVideoEncoderLibVpxVP9`)
- L1083 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::DeliverBufferedFrame(bool bEndOfPicture)` (scope `TVideoEncoderLibVpxVP9`)
- L1113 _function_ `template <typename TResource> bool TVideoEncoderLibVpxVP9<TResource>::PopulateCodecSpecific(FCodecSpecificInfo* CodecSpecificInfo, TOptional<int>* SpatialIdx, TOptional<int>* TemporalIdx, const vpx_codec_cx_pkt& Packet)` (scope `TVideoEncoderLibVpxVP9`)
- L1263 _function_ `FScalableVideoController::FLayerFrameConfig* FoundLayer = LayerFrames.FindByPredicate([&LayerId](FScalableVideoController::FLayerFrameConfig& Config) { return Config.GetSpatialId() == LayerId.spatial_layer_id; });` (scope `TVideoEncoderLibVpxVP9::PopulateCodecSpecific`)
- L1304 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::FillReferenceIndices(const vpx_codec_cx_pkt& Packet, const size_t PicNum, const bool bInterLayerPredicted, FCodecSpecificInfoVP9* Info)` (scope `TVideoEncoderLibVpxVP9`)
- L1413 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::UpdateReferenceBuffers(const vpx_codec_cx_pkt& Packet, size_t PicNum)` (scope `TVideoEncoderLibVpxVP9`)
- L1454 _function_ `template <typename TResource> vpx_svc_ref_frame_config_t TVideoEncoderLibVpxVP9<TResource>::SetReferences(TArray<FScalableVideoController::FLayerFrameConfig>& InLayerFrames)` (scope `TVideoEncoderLibVpxVP9`)
- L1494 _function_ `template <typename TResource> vpx_svc_ref_frame_config_t TVideoEncoderLibVpxVP9<TResource>::SetReferences(bool bIsKeyPic, int FirstActiveSpatialLayerId)` (scope `TVideoEncoderLibVpxVP9`)
- L1597 _function_ `template <typename TResource> bool TVideoEncoderLibVpxVP9<TResource>::SetSvcRates(FVideoEncoderConfigLibVpx const& Config, const FVideoBitrateAllocation& Allocation)` (scope `TVideoEncoderLibVpxVP9`)
- L1746 _function_ `template <typename TResource> bool TVideoEncoderLibVpxVP9<TResource>::ExplicitlyConfiguredSpatialLayers(FVideoEncoderConfigLibVpx const& Config) const` (scope `TVideoEncoderLibVpxVP9`)
- L1754 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::UpdatePerformanceFlags(FVideoEncoderConfigLibVpx const& Config)` (scope `TVideoEncoderLibVpxVP9`)
- L1759 _function_ `const auto FindSpeed = [&ParamsByResolution](int MinPixelCount)` (scope `TVideoEncoderLibVpxVP9::UpdatePerformanceFlags`)
- L1788 _function_ `template <typename TResource> void TVideoEncoderLibVpxVP9<TResource>::MaybeRewrapRawWithFormat(const vpx_img_fmt Format)` (scope `TVideoEncoderLibVpxVP9`)
- L1804 _function_ `template <typename TResource> TTuple<size_t, size_t> TVideoEncoderLibVpxVP9<TResource>::GetActiveLayers(const FVideoBitrateAllocation& Allocation)` (scope `TVideoEncoderLibVpxVP9`)

### `Plugins/Experimental/AVCodecs/LibVpxCodecs/Source/LibVpxCodecs/Public/Video/Util/LibVpxUtil.h` (Public)


#### class `LibVpxUtil`  
`class LibVpxUtil`  
_L7-47_
- L26 _public prototype_ `static void CopyI420(const uint8_t* RESTRICT SrcY, int SrcStrideY, const uint8_t* RESTRICT SrcU, int SrcStrideU, const uint8_t* RESTRICT SrcV, int SrcStrideV, uint8_t* RESTRICT DstY, int DstStrideY, uint8_t* RESTRICT DstU, int DstStrideU, uint8_t* RESTRICT DstV, int DstStrideV, int Width, int Height);`
- L41 _public prototype_ `static void CopyPlane(const uint8_t* RESTRICT SrcY, int SrcStrideY, uint8_t* RESTRICT DstY, int DstStrideY, int Width, int Height);`

#### struct `LibVpxUtil::FImageDeleter`  
`struct FImageDeleter`  
_L10-16_
- L12 _public function_ `void operator()(vpx_image_t* Image) const`

#### struct `LibVpxUtil::FCodecContextDeleter`  
`struct FCodecContextDeleter`  
_L18-24_
- L20 _public function_ `void operator()(vpx_codec_ctx_t* Context) const`
