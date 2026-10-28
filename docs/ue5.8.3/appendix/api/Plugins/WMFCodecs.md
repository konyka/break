# Plugins / WMFCodecs

- module root: `Plugins/Experimental/AVCodecs/WMFCodecs/Source/WMFCodecs`
- headers: 2; symbols: 21
- symbol kinds: class=1, function=3, member=7, prototype=9, struct=1
- PrivateDependencyModuleNames: AVCodecsCore, Engine
- PublicDependencyModuleNames: Core, RenderCore

### `Plugins/Experimental/AVCodecs/WMFCodecs/Source/WMFCodecs/Public/Audio/Encoders/AudioEncoderWMF.h` (Public)


#### class `FAudioEncoderWMF`  
`class FAudioEncoderWMF : public TAudioEncoder<FAudioResourceCPU, FAudioEncoderConfigWMF>`  
_L19-47_
- inherits: `TAudioEncoder<FAudioResourceCPU,FAudioEncoderConfigWMF>`
- L22 _private member_ `TRefCountPtr<IMFTransform> Encoder = nullptr;`
- L23 _private member_ `MFT_INPUT_STREAM_INFO InputStreamInfo;`
- L24 _private member_ `MFT_OUTPUT_STREAM_INFO OutputStreamInfo;`
- L26 _private member_ `uint64 FrameCount = 0;`
- L28 _private member_ `TQueue<FAudioPacket> Packets;`
- L31 _public member_ `uint8 bOpen : 1;`
- L33 _public prototype_ `FAudioEncoderWMF() = default;`
- L36 _public prototype_ `virtual bool IsOpen() const override;`
- L37 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L38 _public prototype_ `virtual void Close() override;`
- L40 _public prototype_ `bool IsInitialized() const;`
- L42 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L44 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<FAudioResourceCPU> const& Resource, uint32 Timestamp) override;`
- L46 _public prototype_ `virtual FAVResult ReceivePacket(FAudioPacket& OutPacket) override;`

### `Plugins/Experimental/AVCodecs/WMFCodecs/Source/WMFCodecs/Public/Audio/Encoders/Configs/AudioEncoderConfigWMF.h` (Public)


#### struct `FAudioEncoderConfigWMF`  
`struct FAudioEncoderConfigWMF : public FAudioEncoderConfig`  
_L15-34_
- inherits: `FAudioEncoderConfig`
- L18 _public member_ `GUID CodecType = {};`
- L20 _public function_ `FAudioEncoderConfigWMF(EAVPreset Preset = EAVPreset::Default) : FAudioEncoderConfig(Preset)`
- L25 _public function_ `bool operator==(FAudioEncoderConfigWMF const& Other) const`
- L30 _public function_ `bool operator!=(FAudioEncoderConfigWMF const& Other) const`

#### Free symbols / members of external scopes

- L37 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FAudioEncoderConfigWMF& OutConfig, struct FAudioEncoderConfigAAC const& InConfig);` (scope `FAVExtension`)
