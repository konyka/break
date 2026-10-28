# Plugins / AVCodecsCoreRHI

- module root: `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI`
- headers: 9; symbols: 160
- symbol kinds: class=11, enum=3, enumerator=8, function=23, macro=6, member=34, prototype=68, struct=7
- PrivateDependencyModuleNames: AVCodecsCore, D3D11RHI, D3D12RHI, Engine, MetalRHI, RHI, RHICore, Vulkan, VulkanRHI
- PublicDependencyModuleNames: Core, CoreUObject, RenderCore

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Audio/Encoders/SimpleAudioEncoder.h` (Public)


#### struct `FSimpleAudioEncoderConfig`  
`struct FSimpleAudioEncoderConfig`  
_L19-54_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public member_ `int32 Bitrate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")`
- L28 _public member_ `int32 Samplerate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")`
- L31 _public member_ `int32 NumChannels;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")`
- L33 _public function_ `FSimpleAudioEncoderConfig(ESimpleAVPreset Preset = ESimpleAVPreset::Default) : FSimpleAudioEncoderConfig(FAudioEncoderConfig(USimpleAudioHelper::ConvertPreset(Preset)))`
- L38 _public function_ `FSimpleAudioEncoderConfig(FAudioEncoderConfig const& From) : Bitrate(From.Bitrate) , Samplerate(From.Samplerate) , NumChannels(From.NumChannels)`
- L45 _public function_ `operator FAudioEncoderConfig() const`

#### class `USimpleAudioEncoder`  
`class USimpleAudioEncoder : public UObject, public FRunnable`  
_L57-119_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject,FRunnable`
- L62 _private member_ `TSharedPtr<TAudioEncoder<class FAudioResourceCPU>> Child;`
- L77 _private member_ `FRunnableThread* AsyncThread = nullptr;`
- L78 _private member_ `TQueue<FAsyncFrame> AsyncQueue;`
- L79 _private member_ `TQueue<TSharedPtr<FAudioResourceCPU>> AsyncPool;`
- L81 _private prototype_ `virtual uint32 Run() override;`
- L82 _private prototype_ `virtual void Exit() override;`
- L86 _public prototype_ `bool IsAsync() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L89 _public prototype_ `bool IsOpen() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L92 _public prototype_ `UPARAM(DisplayName = "Was Success") bool Open(ESimpleAudioCodec Codec, FSimpleAudioEncoderConfig Config, bool bAsy` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L95 _public prototype_ `void Close();` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L98 _public prototype_ `UPARAM(DisplayName = "Was Success") bool SendFrameFloat(TArray<float> const& Resource, double Timestamp, int32 NumSamples, float Sampl` — `UFUNCTION(BlueprintCallable, Category = "Audio", meta = (DisplayName = "Send Frame (PCM16)"))`
- L100 _public prototype_ `bool SendFrame(Audio::TSampleBuffer<float> const& Resource, double Timestamp);`
- L101 _public prototype_ `bool SendFrame(float const* ResourceData, double Timestamp, int32 NumSamples, float SampleDuration);`
- L104 _public prototype_ `UPARAM(DisplayName = "Was Success") bool ReceivePacket(FSimpleAudioPacket&` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L107 _public prototype_ `void ReceivePackets(TArray<FSimpleAudioPacket>& OutPackets);` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L112 _public prototype_ `ESimpleAudioCodec GetCodec() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L115 _public prototype_ `FSimpleAudioEncoderConfig GetConfig() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L118 _public prototype_ `void SetConfig(FSimpleAudioEncoderConfig NewConfig);` — `UFUNCTION(BlueprintCallable, Category = "Audio")`

#### struct `USimpleAudioEncoder::FAsyncFrame`  
`struct FAsyncFrame`  
_L64-75_
- L66 _public member_ `TSharedPtr<FAudioResourceCPU> Resource;`
- L67 _public member_ `uint32 Timestamp;`
- L69 _public prototype_ `FAsyncFrame() = default;`
- L70 _public function_ `FAsyncFrame(TSharedPtr<FAudioResourceCPU> const& Resource, uint32 Timestamp) : Resource(Resource) , Timestamp(Timestamp)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AVCODECSCORERHI_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Audio/SimpleAudio.h` (Public)


#### enum `ESimpleAudioCodec`  
`enum class ESimpleAudioCodec : uint8`  
_L15-18_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `AAC = 0`

#### struct `FSimpleAudioPacket`  
`struct FSimpleAudioPacket`  
_L21-27_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `FAudioPacket RawPacket;`

#### class `USimpleAudioHelper`  
`class USimpleAudioHelper : public USimpleAVHelper`  
_L30-36_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `USimpleAVHelper`
- L35 _public prototype_ `static ESimpleAudioCodec GuessCodec(TSharedRef<FAVInstance> const& Instance);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AVCODECSCORERHI_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/SimpleAV.h` (Public)


#### enum `ESimpleAVPreset`  
`enum class ESimpleAVPreset : uint8`  
_L12-20_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Default`
- L16 _public enumerator_ `UltraLowQuality`
- L17 _public enumerator_ `LowQuality`
- L18 _public enumerator_ `HighQuality`
- L19 _public enumerator_ `Lossless`

#### class `USimpleAVHelper`  
`class USimpleAVHelper : public UObject`  
_L23-29_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L28 _public prototype_ `static EAVPreset ConvertPreset(ESimpleAVPreset From);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVCODECSCORERHI_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Video/Decoders/SimpleVideoDecoder.h` (Public)


#### class `USimpleVideoDecoder`  
`class USimpleVideoDecoder : public UObject, public FRunnable`  
_L17-53_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject,FRunnable`
- L22 _private member_ `TSharedPtr<TVideoDecoder<class FVideoResourceRHI>> Child;`
- L24 _private member_ `FRunnableThread* AsyncThread = nullptr;`
- L25 _private member_ `TQueue<FSimpleVideoPacket> AsyncQueue;`
- L27 _private prototype_ `virtual uint32 Run() override;`
- L28 _private prototype_ `virtual void Exit() override;`
- L32 _public prototype_ `bool IsAsync() const;` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L35 _public prototype_ `bool IsOpen() const;` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L38 _public prototype_ `UPARAM(DisplayName = "Was Success") bool Open(ESimpleVideoCodec Codec, bool bAsy` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L41 _public prototype_ `void Close();` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L44 _public prototype_ `UPARAM(DisplayName = "Was Success") bool SendPacket(FSimpleVideoPacket cons` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L47 _public prototype_ `UPARAM(DisplayName = "Was Success") bool ReceiveFrame(UTextureRenderTarget2D*` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L52 _public prototype_ `ESimpleVideoCodec GetCodec() const;` — `UFUNCTION(BlueprintCallable, Category = "Video")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AVCODECSCORERHI_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Video/Decoders/VideoDecoderRHI.h` (Public)


#### class `TVideoDecoderRHI`  
`template <typename TConfig> class TVideoDecoderRHI : public TVideoDecoder<FVideoResourceRHI, TConfig>`  
_L20-138_
- inherits: `TVideoDecoder<FVideoResourceRHI,TConfig>`
- L24 _public function_ `template <typename TChildConfig> static FVideoDecoder::TFactory<FVideoResourceRHI, TConfig>& Register()`
- L29 _public member_ `TSharedPtr<TVideoDecoder<FVideoResourceRHI, TConfig>> Child;`
- L31 _public prototype_ `TVideoDecoderRHI() = default;`
- L33 _public function_ `virtual bool IsOpen() const override`
- L38 _public function_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override`
- L87 _public function_ `virtual void Close() override`
- L95 _public function_ `virtual FAVResult ApplyConfig() override`
- L113 _public function_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) override`
- L129 _public function_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<FVideoResourceRHI>& InOutResource) override`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Video/Encoders/SimpleVideoEncoder.h` (Public)


#### struct `FSimpleVideoEncoderConfig`  
`struct FSimpleVideoEncoderConfig`  
_L19-64_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public member_ `int32 Width;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")`
- L28 _public member_ `int32 Height;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")`
- L31 _public member_ `int32 TargetFramerate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")`
- L34 _public member_ `int32 TargetBitrate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")`
- L37 _public member_ `int32 MaxBitrate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")`
- L39 _public function_ `FSimpleVideoEncoderConfig(ESimpleAVPreset Preset = ESimpleAVPreset::Default) : FSimpleVideoEncoderConfig(FVideoEncoderConfig(USimpleVideoHelper::ConvertPreset(Preset)))`
- L44 _public function_ `FSimpleVideoEncoderConfig(FVideoEncoderConfig const& From) : Width(From.Width) , Height(From.Height) , TargetFramerate(From.TargetFramerate) , TargetBitrate(From.TargetBitrate) , MaxBitrate(From.MaxBitrate)`
- L53 _public function_ `operator FVideoEncoderConfig() const`

#### class `USimpleVideoEncoder`  
`class USimpleVideoEncoder : public UObject, public FRunnable`  
_L67-133_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject,FRunnable`
- L72 _private member_ `TSharedPtr<TVideoEncoder<class FVideoResourceRHI>> Child;`
- L89 _private member_ `FRunnableThread* AsyncThread = nullptr;`
- L90 _private member_ `TQueue<FAsyncFrame> AsyncQueue;`
- L91 _private member_ `TQueue<TSharedPtr<FVideoResourceRHI>> AsyncPool;`
- L93 _private prototype_ `virtual uint32 Run() override;`
- L94 _private prototype_ `virtual void Exit() override;`
- L98 _public prototype_ `bool IsAsync() const;` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L101 _public prototype_ `bool IsOpen() const;` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L104 _public prototype_ `UPARAM(DisplayName = "Was Success") bool Open(ESimpleVideoCodec Codec, FSimpleVideoEncoderConfig Config, bool bAsy` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L107 _public prototype_ `void Close();` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L110 _public prototype_ `UPARAM(DisplayName = "Was Success") bool SendFrameRenderTarget(UTextureRenderTarget2D* Resource, double Timestamp, bool bForceKeyfram` — `UFUNCTION(BlueprintCallable, Category = "Video", meta = (DisplayName = "Send Frame (Render Target)"))`
- L113 _public prototype_ `UPARAM(DisplayName = "Was Success") bool SendFrameTexture(UTexture2D* Resource, double Timestamp, bool bForceKeyfram` — `UFUNCTION(BlueprintCallable, Category = "Video", meta = (DisplayName = "Send Frame (Texture)"))`
- L115 _public prototype_ `bool SendFrame(FTextureRHIRef const& Resource, double Timestamp, bool bForceKeyframe = false);`
- L118 _public prototype_ `UPARAM(DisplayName = "Was Success") bool ReceivePacket(FSimpleVideoPacket&` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L121 _public prototype_ `void ReceivePackets(TArray<FSimpleVideoPacket>& OutPackets);` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L126 _public prototype_ `ESimpleVideoCodec GetCodec() const;` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L129 _public prototype_ `FSimpleVideoEncoderConfig GetConfig() const;` — `UFUNCTION(BlueprintCallable, Category = "Video")`
- L132 _public prototype_ `void SetConfig(FSimpleVideoEncoderConfig NewConfig);` — `UFUNCTION(BlueprintCallable, Category = "Video")`

#### struct `USimpleVideoEncoder::FAsyncFrame`  
`struct FAsyncFrame`  
_L74-87_
- L76 _public member_ `TSharedPtr<FVideoResourceRHI> Resource;`
- L77 _public member_ `uint32 Timestamp;`
- L78 _public member_ `bool bForceKeyframe;`
- L80 _public prototype_ `FAsyncFrame() = default;`
- L81 _public function_ `FAsyncFrame(TSharedPtr<FVideoResourceRHI> const& Resource, uint32 Timestamp, bool bForceKeyframe) : Resource(Resource) , Timestamp(Timestamp) , bForceKeyframe(bForceKeyframe)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AVCODECSCORERHI_API`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Video/Encoders/VideoEncoderRHI.h` (Public)


#### class `TVideoEncoderRHI`  
`template <typename TConfig> class TVideoEncoderRHI : public TVideoEncoder<FVideoResourceRHI, TConfig>`  
_L19-137_
- inherits: `TVideoEncoder<FVideoResourceRHI,TConfig>`
- L23 _public function_ `template <typename TChildConfig> static FVideoEncoder::TFactory<FVideoResourceRHI, TConfig>& Register()`
- L28 _public member_ `TSharedPtr<TVideoEncoder<FVideoResourceRHI, TConfig>> Child;`
- L30 _public prototype_ `TVideoEncoderRHI() = default;`
- L32 _public function_ `virtual bool IsOpen() const override`
- L37 _public function_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override`
- L86 _public function_ `virtual void Close() override`
- L94 _public function_ `virtual FAVResult ApplyConfig() override`
- L112 _public function_ `virtual FAVResult SendFrame(TSharedPtr<FVideoResourceRHI> const& Resource, uint32 Timestamp, bool bForceKeyframe) override`
- L128 _public function_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override`

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Video/Resources/VideoResourceRHI.h` (Public)


#### class `FVideoContextRHI`  
`class FVideoContextRHI : public FAVContext`  
_L17-19_
- inherits: `FAVContext`

#### class `FVideoResourceRHI`  
`class FVideoResourceRHI : public TVideoResource<FVideoContextRHI>`  
_L21-64_
- inherits: `TVideoResource<FVideoContextRHI>`
- L36 _private member_ `FRawData Raw;`
- L39 _public prototype_ `static FAVLayout GetLayoutFrom(TSharedRef<FAVDevice> const& Device, FTextureRHIRef const& Raw);`
- L40 _public prototype_ `static FVideoDescriptor GetDescriptorFrom(TSharedRef<FAVDevice> const& Device, FTextureRHIRef const& Raw);`
- L42 _public prototype_ `static TSharedPtr<FVideoResourceRHI> Create(TSharedPtr<FAVDevice> const& Device, FVideoDescriptor const& Descriptor, ETextureCreateFlags AdditionalFlags = ETextureCreateFlags::None, bool bIsSRGB = true);`
- L45 _public function_ `inline FRawData const& GetRaw() const`
- L47 _public prototype_ `FVideoResourceRHI(TSharedRef<FAVDevice> const& Device, FRawData const& Raw, FVideoDescriptor const& OverrideDescriptor);`
- L48 _public prototype_ `FVideoResourceRHI(TSharedRef<FAVDevice> const& Device, FRawData const& Raw);`
- L49 _public prototype_ `virtual ~FVideoResourceRHI() override = default;`
- L51 _public prototype_ `virtual FAVResult Validate() const override;`
- L53 _public prototype_ `virtual void Lock() override;`
- L54 _public prototype_ `virtual FScopeLock LockScope() override;`
- L56 _public prototype_ `void CopyFrom(TArrayView64<uint8> const& From);`
- L57 _public prototype_ `void CopyFrom(TArrayView<uint8> const& From);`
- L58 _public prototype_ `void CopyFrom(TArray64<uint8> const& From);`
- L59 _public prototype_ `void CopyFrom(TArray<uint8> const& From);`
- L60 _public prototype_ `void CopyFrom(FTextureRHIRef const& From);`
- L62 _public prototype_ `TSharedPtr<FVideoResourceRHI> TransformResource(FVideoDescriptor const& OutDescriptor);`
- L63 _public prototype_ `void TransformResourceTo(FRHICommandListImmediate& RHICmdList, FTextureRHIRef Target, FVideoDescriptor const& OutDescriptor);`

#### struct `FVideoResourceRHI::FRawData`  
`struct FRawData`  
_L24-33_
- L26 _public member_ `FTextureRHIRef Texture;`
- L28 _public member_ `TRefCountPtr<ID3D12Fence> Fence;` — TODO replace with an RHI fence and convert in a transform function
- L30 _public member_ `FGPUFenceRHIRef Fence;`
- L32 _public member_ `uint64 FenceValue;`

#### class `FResolvableVideoResourceRHI`  
`class FResolvableVideoResourceRHI : public TResolvableVideoResource<FVideoResourceRHI>`  
_L66-73_
- inherits: `TResolvableVideoResource<FVideoResourceRHI>`
- L69 _public member_ `ETextureCreateFlags AdditionalFlags = ETextureCreateFlags::None;`
- L72 _protected prototype_ `virtual TSharedPtr<FVideoResourceRHI> TryResolve(TSharedPtr<FAVDevice> const& Device, FVideoDescriptor const& Descriptor) override;`

#### Free symbols / members of external scopes

- L79 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<FVideoResourceRHI>& OutResource, TSharedPtr<class FVideoResourceRHI> const& InResource);` (scope `FAVExtension`) — Handles pixel format or colorspace transformations
- L82 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<FVideoResourceRHI>& OutResource, TSharedPtr<class FVideoResourceCPU> const& InResource);` (scope `FAVExtension`)
- L87 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<class FVideoResourceD3D11>& OutResource, TSharedPtr<FVideoResourceRHI> const& InResource);` (scope `FAVExtension`)
- L90 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<class FVideoResourceD3D12>& OutResource, TSharedPtr<FVideoResourceRHI> const& InResource);` (scope `FAVExtension`)
- L97 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<class FVideoResourceVulkan>& OutResource, TSharedPtr<FVideoResourceRHI> const& InResource);` (scope `FAVExtension`)
- L104 _prototype_ `template <> FAVResult FAVExtension::TransformResource(TSharedPtr<class FVideoResourceMetal>& OutResource, TSharedPtr<FVideoResourceRHI> const& InResource);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/AVCodecsCore/Source/AVCodecsCoreRHI/Public/Video/SimpleVideo.h` (Public)


#### enum `ESimpleVideoCodec`  
`enum class ESimpleVideoCodec : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `H264 = 0`
- L18 _public enumerator_ `H265 = 1`

#### struct `FSimpleVideoPacket`  
`struct FSimpleVideoPacket`  
_L22-28_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public member_ `FVideoPacket RawPacket;`

#### class `USimpleVideoHelper`  
`class USimpleVideoHelper : public USimpleAVHelper`  
_L31-40_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `USimpleAVHelper`
- L36 _public prototype_ `static ESimpleVideoCodec GuessCodec(TSharedRef<FAVInstance> const& Instance);`
- L39 _public prototype_ `static void ShareRenderTarget2D(class UTextureRenderTarget2D* RenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "Video", meta = (WorldContext = "WorldContext"))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AVCODECSCORERHI_API`
