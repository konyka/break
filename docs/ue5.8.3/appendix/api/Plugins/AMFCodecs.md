# Plugins / AMFCodecs

- module root: `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs`
- headers: 7; symbols: 118
- symbol kinds: class=3, function=34, macro=2, member=28, prototype=45, struct=6
- PrivateDependencyModuleNames: AVCodecsCore, Amf, Engine, Vulkan
- PublicDependencyModuleNames: Core, RenderCore

### `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs/Public/AMF.h` (Public)


#### class `FAMF`  
`class FAMF : public FAPI`  
_L33-47_
- inherits: `FAPI`
- L36 _public member_ `bool bHasCompatibleGPU = true;`
- L38 _public prototype_ `FAMF();`
- L40 _public prototype_ `virtual bool IsValid() const override;`
- L42 _public function_ `amf::AMFFactory* GetFactory() const`
- L45 _private member_ `amf_handle DllHandle = nullptr;`
- L46 _private member_ `amf::AMFFactory* Factory = nullptr;`

### `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs/Public/Video/Decoders/Configs/VideoDecoderConfigAMF.h` (Public)


#### struct `FVideoDecoderConfigAMF`  
`struct FVideoDecoderConfigAMF : public FAVConfig`  
_L12-114_
- inherits: `FAVConfig`
- L15 _private member_ `TMap<wchar_t const*, amf::AMFVariantStruct, FDefaultSetAllocator, TStringPointerMapKeyFuncs_DEPRECATED<wchar_t const*, amf::AMFVariantStruct>> Variants;`
- L24 _public member_ `static FName const CodecTypeH264;`
- L25 _public member_ `static FName const CodecTypeH265;`
- L27 _public member_ `FName CodecType;`
- L29 _public member_ `uint32 Width = 1920;`
- L30 _public member_ `uint32 Height = 1080;`
- L32 _public function_ `FVideoDecoderConfigAMF(EAVPreset Preset = EAVPreset::Default) : FAVConfig(Preset)`
- L37 _public function_ `bool operator==(FVideoDecoderConfigAMF const& Other) const`
- L67 _public function_ `bool operator!=(FVideoDecoderConfigAMF const& Other) const`
- L73 _public function_ `template <typename TVariant> void SetProperty(wchar_t const* Name, TVariant const& Variant)`
- L79 _public function_ `template <typename TVariant> bool GetProperty(wchar_t const* Name, TVariant* OutVariant) const`
- L91 _public function_ `void CopyTo(amf::AMFPropertyStorage* Other) const`
- L99 _public function_ `void CopyFrom(amf::AMFPropertyStorage const* Other)`
- L113 _public prototype_ `FAVResult Parse(TSharedRef<FAVInstance> const& Instance, FVideoPacket const& Packet, TArray<FParsedPicture>& OutPictures);`

#### struct `FVideoDecoderConfigAMF::FParsedPicture`  
`struct FParsedPicture`  
_L18-22_
- L21 _public member_ `TArray<uint8> ExtraData;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AMFCODECS_API`
- L117 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigAMF& OutConfig, struct FVideoDecoderConfig const& InConfig);` (scope `FAVExtension`)
- L120 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoDecoderConfig& OutConfig, FVideoDecoderConfigAMF const& InConfig);` (scope `FAVExtension`)
- L123 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigAMF& OutConfig, struct FVideoDecoderConfigH264 const& InConfig);` (scope `FAVExtension`)
- L126 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigAMF& OutConfig, struct FVideoDecoderConfigH265 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs/Public/Video/Decoders/VideoDecoderAMF.h` (Public)


#### class `TVideoDecoderAMF`  
`template <typename TResource> class TVideoDecoderAMF : public TVideoDecoder<TResource, FVideoDecoderConfigAMF>`  
_L13-46_
- inherits: `TVideoDecoder<TResource,FVideoDecoderConfigAMF>`
- L16 _private member_ `amf::AMFComponentPtr Decoder = nullptr;`
- L25 _private member_ `TQueue<FFrame> Frames;`
- L28 _public member_ `amf::AMFContextPtr Context = nullptr;`
- L30 _public prototype_ `TVideoDecoderAMF() = default;`
- L33 _public prototype_ `virtual bool IsOpen() const override;`
- L34 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L35 _public prototype_ `virtual void Close() override;`
- L37 _public prototype_ `bool IsInitialized() const;`
- L39 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L43 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) override;`
- L45 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource) override;`

#### struct `TVideoDecoderAMF::FFrame`  
`struct FFrame`  
_L18-23_
- L20 _public member_ `int32 SurfaceIndex;`
- L21 _public member_ `uint32 Width;`
- L22 _public member_ `uint32 Height;`

#### struct `FVideoDecoderAMF`  
`struct FVideoDecoderAMF`  
_L49-56_
- desc: TODO (Andrew) Hack until I get back to AMF
- L52 _public prototype_ `template <typename TResource> static FAVResult SetupContext(TVideoDecoderAMF<TResource>& This) = delete;`
- L55 _public prototype_ `template <typename TResource> static FAVResult CopySurface(TVideoDecoderAMF<TResource>& This, TSharedPtr<TResource>& OutResource, amf::AMFSurfacePtr const& InSurface) = delete;`
- L63 _prototype_ `template <> FAVResult FVideoDecoderAMF::SetupContext<class FVideoResourceD3D11>(TVideoDecoderAMF<class FVideoResourceD3D11>& This);`
- L66 _prototype_ `template <> FAVResult FVideoDecoderAMF::CopySurface<class FVideoResourceD3D11>(TVideoDecoderAMF<FVideoResourceD3D11>& This, TSharedPtr<FVideoResourceD3D11>& OutResource, amf::AMFSurfacePtr const& InSurface);`
- L69 _prototype_ `template <> FAVResult FVideoDecoderAMF::SetupContext<class FVideoResourceD3D12>(TVideoDecoderAMF<class FVideoResourceD3D12>& This);`
- L72 _prototype_ `template <> FAVResult FVideoDecoderAMF::CopySurface<class FVideoResourceD3D12>(TVideoDecoderAMF<FVideoResourceD3D12>& This, TSharedPtr<FVideoResourceD3D12>& OutResource, amf::AMFSurfacePtr const& InSurface);`
- L77 _prototype_ `template <> FAVResult FVideoDecoderAMF::SetupContext<class FVideoResourceVulkan>(TVideoDecoderAMF<class FVideoResourceVulkan>& This);`
- L80 _prototype_ `template <> FAVResult FVideoDecoderAMF::CopySurface<class FVideoResourceVulkan>(TVideoDecoderAMF<FVideoResourceVulkan>& This, TSharedPtr<FVideoResourceVulkan>& OutResource, amf::AMFSurfacePtr const& InSurface);`

### `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs/Public/Video/Decoders/VideoDecoderAMF.hpp` (Public)


#### Free symbols / members of external scopes

- L8 _function_ `template <typename TResource> TVideoDecoderAMF<TResource>::~TVideoDecoderAMF()` (scope `TVideoDecoderAMF`)
- L14 _function_ `template <typename TResource> bool TVideoDecoderAMF<TResource>::IsOpen() const` (scope `TVideoDecoderAMF`)
- L20 _function_ `template <typename TResource> FAVResult TVideoDecoderAMF<TResource>::Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` (scope `TVideoDecoderAMF`)
- L42 _function_ `template <typename TResource> void TVideoDecoderAMF<TResource>::Close()` (scope `TVideoDecoderAMF`)
- L71 _function_ `template <typename TResource> bool TVideoDecoderAMF<TResource>::IsInitialized() const` (scope `TVideoDecoderAMF`)
- L77 _function_ `template <typename TResource> FAVResult TVideoDecoderAMF<TResource>::ApplyConfig()` (scope `TVideoDecoderAMF`)
- L140 _function_ `template <typename TResource> FAVResult TVideoDecoderAMF<TResource>::SendPacket(FVideoPacket const& Packet)` (scope `TVideoDecoderAMF`)
- L194 _function_ `template <typename TResource> FAVResult TVideoDecoderAMF<TResource>::ReceiveFrame(TResolvableVideoResource<TResource>& InOutResource)` (scope `TVideoDecoderAMF`)

### `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs/Public/Video/Encoders/Configs/VideoEncoderConfigAMF.h` (Public)


#### struct `FVideoEncoderConfigAMF`  
`struct FVideoEncoderConfigAMF : public FAVConfig`  
_L12-158_
- inherits: `FAVConfig`
- L15 _private member_ `TMap<wchar_t const*, amf::AMFVariantStruct, FDefaultSetAllocator, TStringPointerMapKeyFuncs_DEPRECATED<wchar_t const*, amf::AMFVariantStruct>> Variants;`
- L18 _public prototype_ `static TAVResult<AMF_VIDEO_ENCODER_RATE_CONTROL_METHOD_ENUM> ConvertRateControlMode(ERateControlMode Mode);`
- L19 _public prototype_ `static TAVResult<ERateControlMode> ConvertRateControlMode(AMF_VIDEO_ENCODER_RATE_CONTROL_METHOD_ENUM Mode);`
- L21 _public member_ `static FName const CodecTypeH264;`
- L22 _public member_ `static FName const CodecTypeH265;`
- L24 _public member_ `FName CodecType;`
- L26 _public member_ `uint32 Width = 1920;`
- L27 _public member_ `uint32 Height = 1080;`
- L29 _public member_ `bool RepeatSPSPPS = false;`
- L31 _public function_ `FVideoEncoderConfigAMF(EAVPreset Preset = EAVPreset::Default) : FAVConfig(Preset)`
- L36 _public function_ `bool operator==(FVideoEncoderConfigAMF const& Other) const`
- L66 _public function_ `bool operator!=(FVideoEncoderConfigAMF const& Other) const`
- L72 _public function_ `template <typename TVariant> void SetProperty(wchar_t const* Name, TVariant const& Variant)`
- L78 _public function_ `template <typename TVariant> bool GetProperty(wchar_t const* Name, TVariant* OutVariant) const`
- L90 _public function_ `bool CompareProperty(wchar_t const* Name, FVideoEncoderConfigAMF const& Other) const`
- L115 _public function_ `void CopyTo(amf::AMFPropertyStorage* Other) const`
- L123 _public function_ `void SetDifferencesOnly(FVideoEncoderConfigAMF const& NewConfig, amf::AMFPropertyStorage* Storage)`
- L145 _public function_ `void CopyFrom(amf::AMFPropertyStorage const* Other)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AMFCODECS_API`
- L161 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigAMF& OutConfig, struct FVideoEncoderConfig const& InConfig);` (scope `FAVExtension`)
- L164 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoEncoderConfig& OutConfig, FVideoEncoderConfigAMF const& InConfig);` (scope `FAVExtension`)
- L167 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigAMF& OutConfig, struct FVideoEncoderConfigH264 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs/Public/Video/Encoders/VideoEncoderAMF.h` (Public)


#### class `TVideoEncoderAMF`  
`template <typename TResource> class TVideoEncoderAMF : public TVideoEncoder<TResource, FVideoEncoderConfigAMF>`  
_L14-44_
- inherits: `TVideoEncoder<TResource,FVideoEncoderConfigAMF>`
- L17 _private member_ `amf::AMFComponentPtr Encoder = nullptr;`
- L18 _private member_ `uint8 bInitialized : 1;`
- L20 _private member_ `uint64 FrameCount = 0;`
- L22 _private member_ `TQueue<FVideoPacket> Packets;`
- L25 _public member_ `amf::AMFContextPtr Context = nullptr;`
- L27 _public prototype_ `TVideoEncoderAMF() = default;`
- L30 _public prototype_ `virtual bool IsOpen() const override;`
- L31 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L32 _public prototype_ `virtual void Close() override;`
- L34 _public prototype_ `bool IsInitialized() const;`
- L36 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L40 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) override;`
- L41 _public prototype_ `FAVResult SendFrame(amf::AMFSurfacePtr Input, bool bShouldApplyConfig = true);`
- L43 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override;`

#### struct `FVideoEncoderAMF`  
`struct FVideoEncoderAMF`  
_L47-54_
- desc: TODO (Andrew) Hack until I get back to AMF
- L50 _public prototype_ `template <typename TResource> static FAVResult SetupContext(TVideoEncoderAMF<TResource>& This) = delete;`
- L53 _public prototype_ `template <typename TResource> static FAVResult MapSurface(TVideoEncoderAMF<TResource>& This, TSharedPtr<amf::AMFSurfacePtr>& OutSurface, TSharedPtr<TResource> const& InResource) = delete;`
- L61 _prototype_ `template <> FAVResult FVideoEncoderAMF::SetupContext<class FVideoResourceD3D11>(TVideoEncoderAMF<class FVideoResourceD3D11>& This);`
- L64 _prototype_ `template <> FAVResult FVideoEncoderAMF::MapSurface<class FVideoResourceD3D11>(TVideoEncoderAMF<class FVideoResourceD3D11>& This, TSharedPtr<amf::AMFSurfacePtr>& OutSurface, TSharedPtr<class FVideoResourceD3D11> const& InResource);`
- L67 _prototype_ `template <> FAVResult FVideoEncoderAMF::SetupContext<class FVideoResourceD3D12>(TVideoEncoderAMF<class FVideoResourceD3D12>& This);`
- L70 _prototype_ `template <> FAVResult FVideoEncoderAMF::MapSurface<class FVideoResourceD3D12>(TVideoEncoderAMF<class FVideoResourceD3D12>& This, TSharedPtr<amf::AMFSurfacePtr>& OutSurface, TSharedPtr<class FVideoResourceD3D12> const& InResource);`
- L75 _prototype_ `template <> FAVResult FVideoEncoderAMF::SetupContext<class FVideoResourceVulkan>(TVideoEncoderAMF<class FVideoResourceVulkan>& This);`
- L78 _prototype_ `template <> FAVResult FVideoEncoderAMF::MapSurface<class FVideoResourceVulkan>(TVideoEncoderAMF<class FVideoResourceVulkan>& This, TSharedPtr<amf::AMFSurfacePtr>& OutSurface, TSharedPtr<class FVideoResourceVulkan> const& InResource);`

### `Plugins/Experimental/AVCodecs/AMFCodecs/Source/AMFCodecs/Public/Video/Encoders/VideoEncoderAMF.hpp` (Public)


#### Free symbols / members of external scopes

- L6 _function_ `template <typename TResource> TVideoEncoderAMF<TResource>::~TVideoEncoderAMF()` (scope `TVideoEncoderAMF`)
- L12 _function_ `template <typename TResource> bool TVideoEncoderAMF<TResource>::IsOpen() const` (scope `TVideoEncoderAMF`)
- L18 _function_ `template <typename TResource> FAVResult TVideoEncoderAMF<TResource>::Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` (scope `TVideoEncoderAMF`)
- L42 _function_ `template <typename TResource> void TVideoEncoderAMF<TResource>::Close()` (scope `TVideoEncoderAMF`)
- L73 _function_ `template <typename TResource> bool TVideoEncoderAMF<TResource>::IsInitialized() const` (scope `TVideoEncoderAMF`)
- L79 _function_ `template <typename TResource> FAVResult TVideoEncoderAMF<TResource>::ApplyConfig()` (scope `TVideoEncoderAMF`)
- L158 _function_ `template <typename TResource> FAVResult TVideoEncoderAMF<TResource>::SendFrame(TSharedPtr<TResource> const& Resource, uint32 Timestamp, bool bForceKeyframe)` (scope `TVideoEncoderAMF`)
- L222 _function_ `template <typename TResource> FAVResult TVideoEncoderAMF<TResource>::SendFrame(amf::AMFSurfacePtr Input, bool bShouldApplyConfig)` (scope `TVideoEncoderAMF`)
- L289 _function_ `template <typename TResource> FAVResult TVideoEncoderAMF<TResource>::ReceivePacket(FVideoPacket& OutPacket)` (scope `TVideoEncoderAMF`)
