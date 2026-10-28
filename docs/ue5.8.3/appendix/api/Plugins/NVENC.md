# Plugins / NVENC

- module root: `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVENC`
- headers: 3; symbols: 93
- symbol kinds: class=5, function=6, macro=2, member=19, namespace=1, prototype=59, struct=1
- PrivateDependencyModuleNames: AVCodecsCore, Engine, VulkanRHI
- PublicDependencyModuleNames: CUDA, Core, NVCodecs, RHI, RenderCore, nvEncode

### `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVENC/Public/NVENC.h` (Public)


#### class `FNVENC`  
`class FNVENC : public FAPI, public NV_ENCODE_API_FUNCTION_LIST`  
_L26-39_
- inherits: `FAPI,NV_ENCODE_API_FUNCTION_LIST`
- L29 _public member_ `bool bHasCompatibleGPU = true;`
- L31 _public prototype_ `FNVENC();`
- L33 _public prototype_ `virtual bool IsValid() const override;`
- L35 _public prototype_ `FString GetErrorString(void* Encoder, NVENCSTATUS ForStatus) const;`
- L38 _private member_ `void* DllHandle = nullptr;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define NV_ENC_STRUCT(OfType, VarName) \`

### `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVENC/Public/Video/Encoders/Configs/VideoEncoderConfigNVENC.h` (Public)


#### struct `FVideoEncoderConfigNVENC`  
`struct FVideoEncoderConfigNVENC : public FAVConfig, public NV_ENC_INITIALIZE_PARAMS`  
_L12-92_
- inherits: `FAVConfig,NV_ENC_INITIALIZE_PARAMS`
- L15 _public prototype_ `static TAVResult<NV_ENC_PARAMS_RC_MODE> ConvertRateControlMode(ERateControlMode Mode);`
- L16 _public prototype_ `static TAVResult<ERateControlMode> ConvertRateControlMode(NV_ENC_PARAMS_RC_MODE Mode);`
- L17 _public prototype_ `static TAVResult<NV_ENC_MULTI_PASS> ConvertMultipassMode(EMultipassMode Mode);`
- L18 _public prototype_ `static TAVResult<EMultipassMode> ConvertMultipassMode(NV_ENC_MULTI_PASS Mode);`
- L19 _public prototype_ `static TAVResult<NV_ENC_BUFFER_FORMAT> ConvertFormat(EVideoFormat const& Format);`
- L22 _private member_ `NV_ENC_CONFIG Config = {};`
- L25 _public function_ `FVideoEncoderConfigNVENC() : FAVConfig() , NV_ENC_INITIALIZE_PARAMS({})`
- L52 _public function_ `FVideoEncoderConfigNVENC(FVideoEncoderConfigNVENC const& Other)`
- L57 _public function_ `FVideoEncoderConfigNVENC& operator=(FVideoEncoderConfigNVENC const& Other)`
- L67 _public function_ `bool operator==(FVideoEncoderConfigNVENC const& Other) const`
- L88 _public function_ `bool operator!=(FVideoEncoderConfigNVENC const& Other) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NVENC_API`
- L95 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigNVENC& OutConfig, struct FVideoEncoderConfig const& InConfig);` (scope `FAVExtension`)
- L98 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoEncoderConfig& OutConfig, FVideoEncoderConfigNVENC const& InConfig);` (scope `FAVExtension`)
- L101 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigNVENC& OutConfig, struct FVideoEncoderConfigH264 const& InConfig);` (scope `FAVExtension`)
- L104 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigNVENC& OutConfig, struct FVideoEncoderConfigH265 const& InConfig);` (scope `FAVExtension`)
- L107 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigNVENC& OutConfig, struct FVideoEncoderConfigAV1 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/NVCodecs/Source/NVENC/Public/Video/Encoders/VideoEncoderNVENC.h` (Public)


#### class `FEncoderNVENC`  
`class FEncoderNVENC`  
_L29-69_
- desc: This class is the core of the NVENC encoder logic. Specialisations should inherit from this class to reduce duplicated logic
- L32 _private member_ `uint32 MaxDeviceEncodeWidth = 0;`
- L33 _private member_ `uint32 MaxDeviceEncodeHeight = 0;`
- L34 _private member_ `bool bHasMaxDeviceResolution = false;`
- L36 _private prototype_ `void SetMaxResolution(FVideoEncoderConfigNVENC& PendingConfig);`
- L37 _private prototype_ `void GetMaxDeviceEncodeResolution(const FVideoEncoderConfigNVENC& PendingConfig);`
- L40 _public prototype_ `FEncoderNVENC() = default;`
- L41 _public prototype_ `virtual ~FEncoderNVENC() = default;`
- L44 _protected member_ `NV_ENC_DEVICE_TYPE SessionDeviceType;`
- L45 _protected member_ `void* SessionDevice;`
- L47 _protected member_ `void* Encoder = nullptr;`
- L48 _protected member_ `TQueue<FVideoPacket> Packets;`
- L50 _protected prototype_ `FAVResult ReOpen();`
- L51 _protected prototype_ `FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance, NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS& EncoderSessionParams);`
- L52 _protected prototype_ `FAVResult ApplyConfig(FVideoEncoderConfigNVENC const& AppliedConfig, FVideoEncoderConfigNVENC& PendingConfig);`
- L53 _protected prototype_ `FAVResult SendFrame(NV_ENC_PIC_PARAMS& Input, NV_ENC_LOCK_BITSTREAM& BitstreamLock);`
- L54 _protected prototype_ `FAVResult ReceivePacket(FVideoPacket& OutPacket);`
- L57 _protected prototype_ `virtual bool IsOpen() const = 0;`
- L58 _protected prototype_ `virtual void Close() = 0;`
- L59 _protected prototype_ `virtual bool IsInitialized() const = 0;`
- L60 _protected function_ `virtual FAVResult OnPostInitialization(FVideoEncoderConfigNVENC& PendingConfig)`
- L63 _protected prototype_ `FAVResult RegisterResource(NV_ENC_REGISTER_RESOURCE& OutRegisterResource, NV_ENC_INPUT_RESOURCE_TYPE ResourceType, NV_ENC_BUFFER_FORMAT ResourceFormat, void* Resource, uint32 Width, uint32 Height, uint32 Stride, NV_ENC_BUFFER_USAGE BufferUsage);`
- L64 _protected prototype_ `FAVResult UnregisterResource(NV_ENC_REGISTERED_PTR RegisteredResource);`
- L65 _protected prototype_ `FAVResult MapResource(NV_ENC_MAP_INPUT_RESOURCE& OutMapResource, NV_ENC_REGISTERED_PTR RegisteredResource);`
- L66 _protected prototype_ `FAVResult UnmapResource(NV_ENC_INPUT_PTR MappedResource);`
- L68 _protected prototype_ `int GetCapability(GUID EncodeGUID, NV_ENC_CAPS CapsToQuery) const;`

#### class `FVideoEncoderNVENCCUDA`  
`class FVideoEncoderNVENCCUDA : public TVideoEncoder<FVideoResourceCUDA, FVideoEncoderConfigNVENC>, public FEncoderNVENC`  
_L74-99_
- inherits: `TVideoEncoder<FVideoResourceCUDA,FVideoEncoderConfigNVENC>,FEncoderNVENC`
- desc: An AVCodecs VideoEncoder that takes a FVideoResourceCUDA.
- L77 _private member_ `NV_ENC_OUTPUT_PTR Buffer = nullptr;`
- L80 _public prototype_ `FVideoEncoderNVENCCUDA() = default;`
- L84 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L85 _public prototype_ `virtual void Close() override;`
- L86 _public prototype_ `virtual bool IsOpen() const override;`
- L87 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L88 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<FVideoResourceCUDA> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) override;`
- L89 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override;`
- L93 _public prototype_ `virtual bool IsInitialized() const override;`
- L94 _public prototype_ `virtual FAVResult OnPostInitialization(FVideoEncoderConfigNVENC& PendingConfig) override;`
- L98 _private prototype_ `void DebugDumpFrame(TSharedPtr<FVideoResourceCUDA> const& Resource, uint32 Timestamp);`

#### class `FVideoEncoderNVENCD3D11`  
`class FVideoEncoderNVENCD3D11 : public TVideoEncoder<FVideoResourceD3D11, FVideoEncoderConfigNVENC>, public FEncoderNVENC`  
_L105-130_
- inherits: `TVideoEncoder<FVideoResourceD3D11,FVideoEncoderConfigNVENC>,FEncoderNVENC`
- desc: An AVCodecs VideoEncoder that takes a FVideoResourceD3D11.
- L108 _private member_ `TRefCountPtr<ID3D11Device> EncoderDevice;`
- L109 _private member_ `TRefCountPtr<ID3D11DeviceContext> EncoderDeviceContext;`
- L111 _private member_ `NV_ENC_OUTPUT_PTR Buffer = nullptr;`
- L114 _public prototype_ `FVideoEncoderNVENCD3D11() = default;`
- L118 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L119 _public prototype_ `virtual void Close() override;`
- L120 _public prototype_ `virtual bool IsOpen() const override;`
- L121 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L122 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<FVideoResourceD3D11> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) override;`
- L123 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override;`
- L127 _public prototype_ `virtual bool IsInitialized() const override;`
- L128 _public prototype_ `virtual FAVResult OnPostInitialization(FVideoEncoderConfigNVENC& PendingConfig) override;`

#### class `FVideoEncoderNVENCD3D12`  
`class FVideoEncoderNVENCD3D12 : public TVideoEncoder<FVideoResourceD3D12, FVideoEncoderConfigNVENC>, public FEncoderNVENC`  
_L135-163_
- inherits: `TVideoEncoder<FVideoResourceD3D12,FVideoEncoderConfigNVENC>,FEncoderNVENC`
- desc: An AVCodecs VideoEncoder that takes a FVideoResourceD3D12.
- L138 _private member_ `TRefCountPtr<ID3D12Fence> InputFence;`
- L139 _private member_ `int64 InputFenceVal = 0;`
- L141 _private member_ `TRefCountPtr<ID3D12Fence> OutputFence;`
- L142 _private member_ `int64 OutputFenceVal = 0;`
- L144 _private member_ `TRefCountPtr<ID3D12Resource> OutputBitstreamResource;`
- L147 _public prototype_ `FVideoEncoderNVENCD3D12() = default;`
- L151 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L152 _public prototype_ `virtual void Close() override;`
- L153 _public prototype_ `virtual bool IsOpen() const override;`
- L154 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L155 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<FVideoResourceD3D12> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) override;`
- L156 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override;`
- L160 _public prototype_ `virtual bool IsInitialized() const override;`
- L161 _public prototype_ `virtual FAVResult OnPostInitialization(FVideoEncoderConfigNVENC& PendingConfig) override;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace AVUtils`
- L22 _prototype_ `const FString AVGetComErrorDescription(HRESULT Res);` (scope `AVUtils`)
