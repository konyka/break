# Plugins / VTCodecs

- module root: `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs`
- headers: 8; symbols: 164
- symbol kinds: class=10, function=33, macro=1, member=48, namespace=2, prototype=66, struct=4
- PrivateDependencyModuleNames: AVCodecsCore, Engine, MetalRHI, RHI
- PublicDependencyModuleNames: Core, RHI, RenderCore

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/VT.h` (Public)


#### class `FVT`  
`class FVT : public FAPI`  
_L15-25_
- inherits: `FAPI`
- L18 _public member_ `bool bHasCompatibleGPU = false;`
- L20 _public prototype_ `FVT();`
- L22 _public prototype_ `virtual bool IsValid() const override;`
- L24 _private member_ `bool bIsIoSurfaceAvailable;`

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/Video/Decoders/Configs/VideoDecoderConfigVT.h` (Public)


#### struct `FVideoDecoderConfigVT`  
`struct FVideoDecoderConfigVT : public FAVConfig`  
_L13-83_
- inherits: `FAVConfig`
- L16 _public prototype_ `static TAVResult<OSType> ConvertFormat(EVideoFormat const& Format);`
- L19 _public member_ `CMVideoCodecType Codec;`
- L20 _public member_ `CMVideoFormatDescriptionRef VideoFormat = nullptr;`
- L22 _public function_ `FVideoDecoderConfigVT() : FAVConfig()`
- L28 _public function_ `~FVideoDecoderConfigVT()`
- L33 _public function_ `FVideoDecoderConfigVT(FVideoDecoderConfigVT const& Other)`
- L42 _public function_ `void SetVideoFormat(CMVideoFormatDescriptionRef Format)`
- L62 _public function_ `FVideoDecoderConfigVT& operator=(FVideoDecoderConfigVT const& Other)`
- L73 _public function_ `bool operator==(FVideoDecoderConfigVT const& Other) const`
- L79 _public function_ `bool operator!=(FVideoDecoderConfigVT const& Other) const`

#### Free symbols / members of external scopes

- L86 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigVT& OutConfig, struct FVideoDecoderConfig const& InConfig);` (scope `FAVExtension`)
- L89 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoDecoderConfig& OutConfig, FVideoDecoderConfigVT const& InConfig);` (scope `FAVExtension`)
- L92 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigVT& OutConfig, struct FVideoDecoderConfigH264 const& InConfig);` (scope `FAVExtension`)
- L95 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigVT& OutConfig, struct FVideoDecoderConfigH265 const& InConfig);` (scope `FAVExtension`)
- L98 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoDecoderConfigVT& OutConfig, struct FVideoDecoderConfigVP9 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/Video/Decoders/VideoDecoderVT.h` (Public)


#### class `FVideoDecoderVT`  
`class FVideoDecoderVT : public TVideoDecoder<FVideoResourceMetal, FVideoDecoderConfigVT>`  
_L19-89_
- inherits: `TVideoDecoder<FVideoResourceMetal,FVideoDecoderConfigVT>`
- L22 _private member_ `VTDecompressionSessionRef Decoder = nullptr;`
- L23 _private member_ `CVMetalTextureCacheRef TextureCache = nullptr;`
- L24 _private member_ `CMMemoryPoolRef MemoryPool;`
- L26 _private member_ `uint8 bInitialized : 1;`
- L28 _private member_ `uint64 FrameCount = 0;`
- L30 _private member_ `bool bIsOpen = false;`
- L69 _private member_ `TQueue<TSharedPtr<FFrame>> Frames;`
- L72 _public prototype_ `FVideoDecoderVT() = default;`
- L75 _public prototype_ `virtual bool IsOpen() const override;`
- L76 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L77 _public prototype_ `virtual void Close() override;`
- L78 _public prototype_ `void DestroyDecompressionSession();`
- L79 _public prototype_ `void ConfigureDecompressionSession();`
- L81 _public prototype_ `bool IsInitialized() const;`
- L83 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L85 _public prototype_ `virtual FAVResult ReceiveFrame(TResolvableVideoResource<FVideoResourceMetal>& InOutResource) override;`
- L86 _public prototype_ `FAVResult HandleFrame(void* Params, OSStatus Status, VTDecodeInfoFlags InfoFlags, CVImageBufferRef ImageBuffer, CMTime Timestamp, CMTime Duration);`
- L88 _public prototype_ `virtual FAVResult SendPacket(FVideoPacket const& Packet) override;`

#### class `FVideoDecoderVT::DecodeParams`  
`class DecodeParams`  
_L32-40_
- L35 _public function_ `DecodeParams()`
- L36 _public function_ `DecodeParams(CMTime Timestamp) : Timestamp(Timestamp)`
- L39 _public member_ `CMTime Timestamp;`

#### class `FVideoDecoderVT::FFrame`  
`class FFrame`  
_L42-67_
- L45 _public function_ `FFrame()`
- L47 _public function_ `FFrame(CVPixelBufferRef InImageBuffer, CMTime InTimestamp, CMTime InDuration) : ImageBuffer(InImageBuffer), Timestamp(InTimestamp), Duration(InDuration)`
- L56 _public function_ `~FFrame()`
- L64 _public member_ `CVPixelBufferRef ImageBuffer;`
- L65 _public member_ `CMTime Timestamp;`
- L66 _public member_ `CMTime Duration;`

#### Free symbols / members of external scopes

- L91 _namespace_ `namespace Internal`
- L93 _prototype_ `void VTDecompressionOutputCallback(void* Decoder, void* Params, OSStatus Status, VTDecodeInfoFlags InfoFlags, CVImageBufferRef ImageBuffer, CMTime Timestamp, CMTime Duration);` (scope `Internal`)

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/Video/Encoders/Configs/VideoEncoderConfigVT.h` (Public)


#### struct `FVideoEncoderConfigVT`  
`struct FVideoEncoderConfigVT : public FAVConfig`  
_L13-90_
- inherits: `FAVConfig`
- L16 _public prototype_ `static TAVResult<OSType> ConvertFormat(EVideoFormat const& Format);`
- L19 _public member_ `uint32 Width = 1920;`
- L20 _public member_ `uint32 Height = 1080;`
- L21 _public member_ `uint32 FrameRate = 60;`
- L22 _public member_ `int32 TargetBitrate = 10000000;`
- L23 _public member_ `int32 MaxBitrate = 20000000;`
- L24 _public member_ `ERateControlMode RateControlMode = ERateControlMode::CBR;`
- L25 _public member_ `uint8 bFillData : 1;`
- L26 _public member_ `uint32 KeyframeInterval = 0;`
- L27 _public member_ `CMVideoCodecType Codec;`
- L28 _public member_ `CFStringRef Profile;`
- L29 _public member_ `EVideoFormat PixelFormat;`
- L30 _public member_ `CFStringRef EntropyCodingMode;`
- L31 _public member_ `int32 MinQuality;`
- L32 _public member_ `int32 MaxQuality;`
- L34 _public function_ `FVideoEncoderConfigVT() : FAVConfig()`
- L40 _public function_ `FVideoEncoderConfigVT(FVideoEncoderConfigVT const& Other)`
- L45 _public function_ `FVideoEncoderConfigVT& operator=(FVideoEncoderConfigVT const& Other)`
- L52 _public function_ `bool operator==(FVideoEncoderConfigVT const& Other) const`
- L72 _public function_ `bool operator!=(FVideoEncoderConfigVT const& Other) const`
- L77 _public function_ `int64 GetCVPixelFormatType() const`

#### Free symbols / members of external scopes

- L93 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigVT& OutConfig, struct FVideoEncoderConfig const& InConfig);` (scope `FAVExtension`)
- L96 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(struct FVideoEncoderConfig& OutConfig, FVideoEncoderConfigVT const& InConfig);` (scope `FAVExtension`)
- L99 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigVT& OutConfig, struct FVideoEncoderConfigH264 const& InConfig);` (scope `FAVExtension`)
- L102 _prototype_ `template <> FAVResult FAVExtension::TransformConfig(FVideoEncoderConfigVT& OutConfig, struct FVideoEncoderConfigH265 const& InConfig);` (scope `FAVExtension`)

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/Video/Encoders/VideoEncoderVT.h` (Public)


#### class `TVideoEncoderVT`  
`template <typename TResource> class TVideoEncoderVT : public TVideoEncoder<TResource, FVideoEncoderConfigVT>`  
_L23-70_
- inherits: `TVideoEncoder<TResource,FVideoEncoderConfigVT>`
- L26 _private member_ `VTCompressionSessionRef Encoder = nullptr;`
- L29 _private member_ `FVideoDecoderConfigH264 H264;` — Create a dummy decoder config so we have access to its parsing capabilities
- L30 _private member_ `FVideoDecoderConfigH265 H265;`
- L32 _private member_ `uint8 bInitialized : 1;`
- L34 _private member_ `uint64 FrameCount = 0;`
- L36 _private member_ `TQueue<FVideoPacket> Packets;`
- L38 _private member_ `bool bIsOpen = false;`
- L52 _public prototype_ `TVideoEncoderVT() = default;`
- L55 _public prototype_ `virtual bool IsOpen() const override;`
- L56 _public prototype_ `virtual FAVResult Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance) override;`
- L57 _public prototype_ `virtual void Close() override;`
- L59 _public prototype_ `bool IsInitialized() const;`
- L61 _public prototype_ `virtual FAVResult ApplyConfig() override;`
- L62 _public prototype_ `FAVResult ConfigureCompressionSession(FVideoEncoderConfigVT const& Config);`
- L63 _public prototype_ `FAVResult SetEncoderBitrate(FVideoEncoderConfigVT const& Config);`
- L65 _public prototype_ `virtual FAVResult SendFrame(TSharedPtr<FVideoResourceMetal> const& Resource, uint32 Timestamp, bool bForceKeyframe = false) override;`
- L67 _public prototype_ `virtual FAVResult ReceivePacket(FVideoPacket& OutPacket) override;`
- L69 _public prototype_ `FAVResult HandlePacket(void* Params, OSStatus Status, VTEncodeInfoFlags InfoFlags, CMSampleBufferRef& SampleBuffer);`

#### class `TVideoEncoderVT::EncodeParams`  
`class EncodeParams`  
_L40-49_
- L43 _public function_ `EncodeParams()`
- L44 _public function_ `EncodeParams(CMVideoCodecType Codec, CMTime Timestamp) : Codec(Codec), Timestamp(Timestamp)`
- L47 _public member_ `CMVideoCodecType Codec;`
- L48 _public member_ `CMTime Timestamp;`

#### Free symbols / members of external scopes

- L72 _namespace_ `namespace Internal`
- L74 _prototype_ `void VTCompressionOutputCallback(void* Encoder, void* Params, OSStatus Status, VTEncodeInfoFlags InfoFlags, CMSampleBufferRef SampleBuffer);` (scope `Internal`)

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/Video/Encoders/VideoEncoderVT.hpp` (Public)


#### Free symbols / members of external scopes

- L13 _macro_ `#define CONDITIONAL_RELEASE(x) \`
- L21 _function_ `template <typename TResource> TVideoEncoderVT<TResource>::~TVideoEncoderVT()` (scope `TVideoEncoderVT`)
- L27 _function_ `template <typename TResource> bool TVideoEncoderVT<TResource>::IsOpen() const` (scope `TVideoEncoderVT`)
- L33 _function_ `template <typename TResource> FAVResult TVideoEncoderVT<TResource>::Open(TSharedRef<FAVDevice> const& NewDevice, TSharedRef<FAVInstance> const& NewInstance)` (scope `TVideoEncoderVT`)
- L47 _function_ `template <typename TResource> void TVideoEncoderVT<TResource>::Close()` (scope `TVideoEncoderVT`)
- L60 _function_ `template <typename TResource> bool TVideoEncoderVT<TResource>::IsInitialized() const` (scope `TVideoEncoderVT`)
- L66 _function_ `template <typename TResource> FAVResult TVideoEncoderVT<TResource>::ApplyConfig()` (scope `TVideoEncoderVT`)
- L161 _function_ `template <typename TResource> FAVResult TVideoEncoderVT<TResource>::ConfigureCompressionSession(FVideoEncoderConfigVT const& Config)` (scope `TVideoEncoderVT`)
- L194 _function_ `template <typename TResource> FAVResult TVideoEncoderVT<TResource>::SetEncoderBitrate(FVideoEncoderConfigVT const &Config)` (scope `TVideoEncoderVT`)
- L202 _function_ `template <typename TResource> FAVResult TVideoEncoderVT<TResource>::SendFrame(TSharedPtr<FVideoResourceMetal> const &Resource, uint32 Timestamp, bool bForceKeyframe)` (scope `TVideoEncoderVT`)
- L308 _function_ `template <typename TResource> FAVResult TVideoEncoderVT<TResource>::ReceivePacket(FVideoPacket &OutPacket)` (scope `TVideoEncoderVT`)
- L324 _function_ `template <typename TResource> FAVResult TVideoEncoderVT<TResource>::HandlePacket(void *Params, OSStatus Status, VTEncodeInfoFlags InfoFlags, CMSampleBufferRef &SampleBuffer)` (scope `TVideoEncoderVT`)

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/Video/Util/NaluRewriter.h` (Public)


#### class `NaluRewriter`  
`class NaluRewriter`  
_L20-144_
- L26 _public prototype_ `static bool H264CMSampleBufferToAnnexBBuffer(CMSampleBufferRef avcc_sample_buffer, bool is_keyframe, TArray<uint8>& annexb_buffer);` — Converts a sample buffer emitted from the VideoToolbox encoder into a buffer suitable for RTP. The sample buffer is in avcc format whereas the rtp buffer needs to be in Annex B format. Data is written directly to |annexb_buffer|.
- L34 _public prototype_ `static bool H264AnnexBBufferToCMSampleBuffer(const uint8* annexb_buffer, size_t annexb_buffer_size, CMVideoFormatDescriptionRef video_format, CMSampleBufferRef* out_sample_buffer, CMMemoryPoolRef memory_pool);` — Converts a buffer received from RTP into a sample buffer suitable for the VideoToolbox decoder. The RTP buffer is in annex b format whereas the sample buffer is in avcc format. If |is_keyframe| is true then |video_format| is ignored since the format will be read from the buffer. Otherwise |video_format| must be provided. Caller is responsible for releasing the created sample buffer.
- L39 _public prototype_ `static CMVideoFormatDescriptionRef CreateH264VideoFormatDescription(const uint8* annexb_buffer, size_t annexb_buffer_size);` — Returns a video format description created from the sps/pps information in the Annex B buffer. If there is no such information, nullptr is returned. The caller is responsible for releasing the description.
- L44 _public prototype_ `static bool H265CMSampleBufferToAnnexBBuffer(CMSampleBufferRef avcc_sample_buffer, bool is_keyframe, TArray<uint8>& annexb_buffer);` — Converts a sample buffer emitted from the VideoToolbox encoder into a buffer suitable for RTP. The sample buffer is in avcc format whereas the rtp buffer needs to be in Annex B format. Data is written directly to |annexb_buffer|.
- L52 _public prototype_ `static bool H265AnnexBBufferToCMSampleBuffer(const uint8* annexb_buffer, size_t annexb_buffer_size, CMVideoFormatDescriptionRef video_format, CMSampleBufferRef* out_sample_buffer, CMMemoryPoolRef memory_pool);` — Converts a buffer received from RTP into a sample buffer suitable for the VideoToolbox decoder. The RTP buffer is in annex b format whereas the sample buffer is in hvcc format. If |is_keyframe| is true then |video_format| is ignored since the format will be read from the buffer. Otherwise |video_format| must be provided. Caller is responsible for releasing the created sample buffer.
- L57 _public prototype_ `static CMVideoFormatDescriptionRef CreateH265VideoFormatDescription(const uint8* annexb_buffer, size_t annexb_buffer_size);` — Returns a video format description created from the sps/pps information in the Annex B buffer. If there is no such information, nullptr is returned. The caller is responsible for releasing the description.
- L62 _public prototype_ `static bool VP9BufferToCMSampleBuffer(const uint8* buffer, size_t buffer_size, CMVideoFormatDescriptionRef video_format, CMSampleBufferRef* out_sample_buffer, CMMemoryPoolRef memory_pool);` — Converts a buffer received from RTP into a sample buffer suitable for the VideoToolbox decoder. Caller is responsible for releasing the created sample buffer.
- L64 _public prototype_ `static CMVideoFormatDescriptionRef CreateVP9VideoFormatDescription(const uint8* rtp_buffer, size_t rtp_buffer_size);`

#### class `NaluRewriter::AnnexBBufferReader`  
`class AnnexBBufferReader final`  
_L67-121_
- desc: Helper class for reading NALUs from an RTP Annex B buffer.
- L70 _public prototype_ `AnnexBBufferReader(const uint8* annexb_buffer, size_t length, bool isH264 = true);`
- L71 _public prototype_ `~AnnexBBufferReader();`
- L72 _public prototype_ `AnnexBBufferReader(const AnnexBBufferReader& other) = delete;`
- L73 _public prototype_ `void operator=(const AnnexBBufferReader& other) = delete;`
- L77 _public prototype_ `bool ReadNalu(const uint8** out_nalu, size_t* out_length);` — Returns a pointer to the beginning of the next NALU slice without the header bytes and its length. Returns false if no more slices remain.
- L81 _public prototype_ `size_t BytesRemaining() const;` — Returns the number of unread NALU bytes, including the size of the header. If the buffer has no remaining NALUs this will return zero.
- L82 _public prototype_ `size_t BytesRemainingForAVC() const;`
- L85 _public prototype_ `void SeekToStart();` — Reset the reader to start reading from the first NALU
- L91 _public prototype_ `bool SeekToNextNaluOfType(UE::AVCodecCore::H264::ENaluType type);` — Seek to the next position that holds a NALU of the desired type, or the end if no such NALU is found. Return true if a NALU of the desired type is found, false if we reached the end instead
- L92 _public prototype_ `bool SeekToNextNaluOfType(UE::AVCodecCore::H265::ENaluType type);`
- L95 _private prototype_ `UE::AVCodecCore::H264::ENaluType ParseH264NaluType(uint8 data);`
- L96 _private prototype_ `UE::AVCodecCore::H265::ENaluType ParseH265NaluType(uint8 data);`
- L98 _private member_ `const uint8* const start_;`
- L100 _private member_ `const size_t length_;`
- L119 _private member_ `TArray<NaluIndex> offsets_;`
- L120 _private member_ `TArray<NaluIndex>::TIterator offset_;`

#### struct `NaluRewriter::AnnexBBufferReader::NaluIndex`  
`struct NaluIndex`  
_L102-110_
- L105 _public member_ `size_t start_offset;` — Start index of NALU, including start sequence.
- L107 _public member_ `size_t payload_start_offset;` — Start index of NALU payload, typically type header.
- L109 _public member_ `size_t payload_size;` — Length of NALU payload, in bytes, counting from payload_start_offset.

#### struct `NaluRewriter::AnnexBBufferReader::FFakeDeleter`  
`struct FFakeDeleter`  
_L112-117_
- L114 _public function_ `void operator()(uint8* Object) const`

#### class `NaluRewriter::AvccBufferWriter`  
`class AvccBufferWriter final`  
_L124-143_
- desc: Helper class for writing NALUs using avcc format into a buffer.
- L127 _public prototype_ `AvccBufferWriter(uint8* const avcc_buffer, size_t length);`
- L128 _public function_ `~AvccBufferWriter()`
- L129 _public prototype_ `AvccBufferWriter(const AvccBufferWriter& other) = delete;`
- L130 _public prototype_ `void operator=(const AvccBufferWriter& other) = delete;`
- L134 _public prototype_ `bool WriteNalu(const uint8* data, size_t data_size);` — Writes the data slice into the buffer. Returns false if there isn't enough space left.
- L137 _public prototype_ `size_t BytesRemaining() const;` — Returns the unused bytes in the buffer.
- L140 _private member_ `uint8* const start_;`
- L141 _private member_ `size_t offset_;`
- L142 _private member_ `const size_t length_;`

### `Plugins/Experimental/AVCodecs/VTCodecs/Source/VTCodecs/Public/Video/Util/VTSessionHelpers.h` (Public)


#### class `VTSessionHelpers`  
`class VTSessionHelpers`  
_L16-23_
- L19 _public prototype_ `static FString CFStringToString(const CFStringRef CfString);`
- L20 _public prototype_ `static void SetVTSessionProperty(VTSessionRef Session, CFStringRef Key, int32_t Value);`
- L21 _public prototype_ `static void SetVTSessionProperty(VTSessionRef Session, CFStringRef Key, bool Value);`
- L22 _public prototype_ `static void SetVTSessionProperty(VTSessionRef Session, CFStringRef Key, CFStringRef Value);`
