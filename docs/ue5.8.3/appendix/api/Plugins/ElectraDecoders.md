# Plugins / ElectraDecoders

- module root: `Plugins/Media/ElectraCodecs/Source/ElectraDecoders`
- headers: 92; symbols: 2536
- symbol kinds: class=88, delegate=1, enum=35, enumerator=241, function=241, macro=52, member=1199, namespace=30, prototype=511, struct=105, typedef=11, variable=22
- PrivateDependencyModuleNames: Core, ElectraBase, ElectraSamples, MP4Boxes, MP4Utilities, Media, MediaUtils, RHI, SignalProcessing, dr_libs
- PrivateIncludePathModuleNames: MetalRHI
- PublicDependencyModuleNames: DirectX
- PublicIncludePathModuleNames: ElectraCodecFactory

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/AndroidPlatformElectraDecoders.h` (Private)


#### class `FPlatformElectraDecodersAndroid`  
`class FPlatformElectraDecodersAndroid`  
_L9-15_
- L12 _public prototype_ `static void Startup();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static void RegisterWithCodecFactory(IElectraCodecRegistry* InCodecFactoryToRegisterWith);`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FPlatformElectraDecoders = FPlatformElectraDecodersAndroid;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/DecoderErrors_Android.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define ERRCODE_INTERNAL_NO_ERROR 0`
- L6 _macro_ `#define ERRCODE_INTERNAL_UNEXPECTED_PROBLEM 1`
- L7 _macro_ `#define ERRCODE_INTERNAL_ALREADY_CLOSED 2`
- L8 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_PARSE_CSD 3`
- L9 _macro_ `#define ERRCODE_INTERNAL_COULD_NOT_CREATE_DECODER 4`
- L10 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_DECODE_INPUT 5`
- L11 _macro_ `#define ERRCODE_INTERNAL_DID_NOT_GET_INPUT_BUFFER 6`
- L12 _macro_ `#define ERRCODE_INTERNAL_DID_NOT_GET_OUTPUT_BUFFER 7`
- L13 _macro_ `#define ERRCODE_INTERNAL_COULD_NOT_GET_OUTPUT_FORMAT 8`
- L14 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_HANDLE_OUTPUT 9`
- L15 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CONVERT_OUTPUT_SAMPLE 10`
- L16 _macro_ `#define ERRCODE_INTERNAL_INVALID_OUTPUT_SURFACE 11`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/aac/AAC_AudioDecoder_Android.h` (Private)


#### class `FAACAudioDecoderAndroid`  
`class FAACAudioDecoderAndroid`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/aac/AudioDecoderAAC_Android.h` (Private)


#### class `IElectraAudioDecoderAAC_Android`  
`class IElectraAudioDecoderAAC_Android : public IElectraDecoder`  
_L8-15_
- inherits: `IElectraDecoder`
- L11 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L12 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L14 _public prototype_ `virtual ~IElectraAudioDecoderAAC_Android() = default;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/aac/AudioDecoderAAC_JavaWrapper_Android.h` (Private)


#### class `IElectraAACAudioDecoderAndroidJava`  
`class IElectraAACAudioDecoderAndroidJava`  
_L16-177_
- L19 _public prototype_ `static TSharedPtr<IElectraAACAudioDecoderAndroidJava, ESPMode::ThreadSafe> Create();`
- L21 _public prototype_ `virtual ~IElectraAACAudioDecoderAndroidJava() = default;`
- L84 _public prototype_ `virtual int32 InitializeDecoder(const ElectraDecodersUtil::MPEG::FAACDecoderConfigurationRecord& InParsedConfigurationRecord) = 0;` — Creates and initializes a Java instance of an AAC audio decoder. @param @return 0 if successful, 1 on error.
- L91 _public prototype_ `virtual int32 ReleaseDecoder() = 0;` — Releases (destroys) the Java audio decoder instance. @return 0 if successful, 1 on error.
- L98 _public prototype_ `virtual int32 Start() = 0;` — Starts the decoder instance. @return 0 if successful, 1 on error.
- L105 _public prototype_ `virtual int32 Stop() = 0;` — Stops the decoder instance. @return 0 if successful, 1 on error.
- L112 _public prototype_ `virtual int32 Flush() = 0;` — Flushes the decoder instance. @return 0 if successful, 1 on error.
- L121 _public prototype_ `virtual int32 DequeueInputBuffer(int32 InTimeoutUsec) = 0;` — Dequeues an input buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return >= 0 returns the index of the successfully dequeued buffer, negative values indicate an error.
- L133 _public prototype_ `virtual int32 QueueInputBuffer(int32 InBufferIndex, const void* InAccessUnitData, int32 InAccessUnitSize, int64 InTimestampUSec) = 0;` — Queues input for decoding in the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put data into and enqueue for decoding (see DequeueInputBuffer()). @param InAccessUnitData Data to be decoded. @param InAccessUnitSize Size of the data to be decoded. @param InTimestampUSec Timestamp (PTS) of the data, in microseconds. @return 0 if successful, 1 on error.
- L143 _public prototype_ `virtual int32 QueueEOSInputBuffer(int32 InBufferIndex, int64 InTimestampUSec) = 0;` — Queues end of stream for the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put the EOS flag into and enqueue for decoding (see DequeueInputBuffer()). @param InTimestampUSec Timestamp the previous data had. Can be 0. @return 0 if successful, 1 on error.
- L153 _public prototype_ `virtual int32 GetOutputFormatInfo(FOutputFormatInfo& OutFormatInfo, int32 InOutputBufferIndex) = 0;` — Returns format information of the decoded samples. @param OutFormatInfo @param InOutputBufferIndex RESERVED FOR NOW - Pass any negative value to get the output format after DequeueOutputBuffer() returns a BufferIndex of MediaCodec_INFO_OUTPUT_FORMAT_CHANGED. @return 0 if successful, 1 on error.
- L162 _public prototype_ `virtual int32 DequeueOutputBuffer(FOutputBufferInfo& OutBufferInfo, int32 InTimeoutUsec) = 0;` — Dequeues an output buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return 0 on success, 1 on failure. The OutBufferInfo.BufferIndex indicates the buffer index.
- L175 _public prototype_ `virtual int32 GetOutputBufferAndRelease(void*& OutBufferDataPtr, int32 OutBufferDataSize, const FOutputBufferInfo& InOutBufferInfo) = 0;` — Returns the decoded samples from a decoder output buffer in the decoder native format! Check the output format first to check if the format uses 2 bytes per sample (int16) or 4 (float) and the number of channels. @param OutBufferDataPtr @param OutBufferDataSize @param InOutBufferInfo @return 0 on success, 1 on failure.

#### struct `IElectraAACAudioDecoderAndroidJava::FOutputFormatInfo`  
`struct FOutputFormatInfo`  
_L23-45_
- L25 _public function_ `FOutputFormatInfo()`
- L30 _public function_ `void Clear()`
- L37 _public function_ `bool IsValid() const`
- L42 _public member_ `int32 SampleRate;`
- L43 _public member_ `int32 NumChannels;`
- L44 _public member_ `int32 BytesPerSample;`

#### struct `IElectraAACAudioDecoderAndroidJava::FOutputBufferInfo`  
`struct FOutputBufferInfo`  
_L47-75_
- L56 _public function_ `FOutputBufferInfo()`
- L61 _public function_ `void Clear()`
- L70 _public member_ `int32 BufferIndex;`
- L71 _public member_ `int64 PresentationTimestamp;`
- L72 _public member_ `int32 Size;`
- L73 _public member_ `bool bIsEOS;`
- L74 _public member_ `bool bIsConfig;`

#### enum `IElectraAACAudioDecoderAndroidJava::FOutputBufferInfo::EBufferIndexValues`  
`enum EBufferIndexValues`  
_L49-54_
- L51 _public enumerator_ `MediaCodec_INFO_TRY_AGAIN_LATER = -1`
- L52 _public enumerator_ `MediaCodec_INFO_OUTPUT_FORMAT_CHANGED = -2`
- L53 _public enumerator_ `MediaCodec_INFO_OUTPUT_BUFFERS_CHANGED = -3`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/h264/H264_VideoDecoder_Android.h` (Private)


#### class `FH264VideoDecoderAndroid`  
`class FH264VideoDecoderAndroid`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/h264/VideoDecoderH264_Android.h` (Private)


#### class `IElectraVideoDecoderH264_Android`  
`class IElectraVideoDecoderH264_Android : public IElectraDecoder`  
_L7-14_
- inherits: `IElectraDecoder`
- L10 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L11 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L13 _public prototype_ `virtual ~IElectraVideoDecoderH264_Android() = default;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/h264/VideoDecoderH264_JavaWrapper_Android.h` (Private)


#### class `IElectraH264VideoDecoderAndroidJava`  
`class IElectraH264VideoDecoderAndroidJava`  
_L15-261_
- L19 _public prototype_ `static TSharedPtr<IElectraH264VideoDecoderAndroidJava, ESPMode::ThreadSafe> Create();`
- L21 _public prototype_ `virtual ~IElectraH264VideoDecoderAndroidJava() = default;`
- L118 _public prototype_ `virtual int32 CreateDecoder() = 0;` — Creates a Java instance of an H.264 video decoder. @return 0 if successful, 1 on error.
- L127 _public prototype_ `virtual int32 InitializeDecoder(const FCreateParameters& InCreateParams) = 0;` — Initializes the video decoder instance. @param InCreateParams @return 0 if successful, 1 on error.
- L136 _public prototype_ `virtual int32 SetOutputSurface(jobject InNewOutputSurface) = 0;` — Attempts to set a new output surface on an existing and configured decoder. @param InNewOutputSurface @return 0 if successful, 1 on error.
- L143 _public prototype_ `virtual int32 ReleaseDecoder() = 0;` — Releases (destroys) the Java video decoder instance. @return 0 if successful, 1 on error.
- L150 _public prototype_ `virtual const FDecoderInformation* GetDecoderInformation() = 0;` — Returns decoder information after a successful InitializeDecoder(). @return Pointer to decoder information or null when no decoder has been created.
- L157 _public prototype_ `virtual int32 Start() = 0;` — Starts the decoder instance. @return 0 if successful, 1 on error.
- L164 _public prototype_ `virtual int32 Stop() = 0;` — Stops the decoder instance. @return 0 if successful, 1 on error.
- L171 _public prototype_ `virtual int32 Flush() = 0;` — Flushes the decoder instance. @return 0 if successful, 1 on error.
- L178 _public prototype_ `virtual int32 Reset() = 0;` — Resets the decoder instance. @return 0 if successful, 1 on error.
- L187 _public prototype_ `virtual int32 DequeueInputBuffer(int32 InTimeoutUsec) = 0;` — Dequeues an input buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return >= 0 returns the index of the successfully dequeued buffer, negative values indicate an error.
- L201 _public prototype_ `virtual int32 QueueInputBuffer(int32 InBufferIndex, const void* InPrefixData, int32 InPrefixSize, const void* InAccessUnitData, int32 InAccessUnitSize, int64 InTimestampUSec) = 0;` — Queues input for decoding in the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put data into and enqueue for decoding (see DequeueInputBuffer()). @param InPrefixData Data to prefix the data to decode with. If given it is usually the SPS & PPS. @param InPrefixSize Size of the prefix data. @param InAccessUnitData Data to be decoded. @param InAccessUnitSize Size of the data to be decoded. @param InTimestampUSec Timestamp (PTS) of the data, in microseconds. @return 0 if successful, 1 on error.
- L213 _public prototype_ `virtual int32 QueueCSDInputBuffer(int32 InBufferIndex, const void* InCSDData, int32 InCSDSize, int64 InTimestampUSec) = 0;` — Queues codec specific data for the following to-be-decoded data buffers. @param InBufferIndex Index of the buffer to put data into and enqueue for decoding (see DequeueInputBuffer()). @param InCSDData Codec specific data @param InCSDSize Size of the codec specific data @param InTimestampUSec Timestamp (PTS) of the data, in microseconds. Must be the same as the next data to be decoded. @return 0 if successful, 1 on error.
- L223 _public prototype_ `virtual int32 QueueEOSInputBuffer(int32 InBufferIndex, int64 InTimestampUSec) = 0;` — Queues end of stream for the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put the EOS flag into and enqueue for decoding (see DequeueInputBuffer()). @param InTimestampUSec Timestamp the previous data had. Can be 0. @return 0 if successful, 1 on error.
- L233 _public prototype_ `virtual int32 GetOutputFormatInfo(FOutputFormatInfo& OutFormatInfo, int32 InOutputBufferIndex) = 0;` — Returns format information of the decoded samples. @param OutFormatInfo @param InOutputBufferIndex RESERVED FOR NOW - Pass any negative value to get the output format after DequeueOutputBuffer() returns a BufferIndex of MediaCodec_INFO_OUTPUT_FORMAT_CHANGED. @return 0 if successful, 1 on error.
- L242 _public prototype_ `virtual int32 DequeueOutputBuffer(FOutputBufferInfo& OutBufferInfo, int32 InTimeoutUsec) = 0;` — Dequeues an output buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return 0 on success, 1 on failure. The OutBufferInfo.BufferIndex indicates the buffer index.
- L253 _public prototype_ `virtual int32 GetOutputBuffer(void*& OutBufferDataPtr, int32 OutBufferDataSize, const FOutputBufferInfo& InOutBufferInfo) = 0;` — Returns the decoded samples from a decoder output buffer in the decoder native format. @param OutBufferDataPtr @param OutBufferDataSize @param InOutBufferInfo @return 0 on success, 1 on failure.
- L260 _public prototype_ `virtual int32 ReleaseOutputBuffer(int32 BufferIndex, int32 ValidCount, bool bRender, int64 releaseAt) = 0;` — Releases the decoder output buffer back to the decoder. @return 0 on success, 1 on failure.

#### struct `IElectraH264VideoDecoderAndroidJava::FCreateParameters`  
`struct FCreateParameters`  
_L23-35_
- L25 _public member_ `int32 MaxWidth = 0;`
- L26 _public member_ `int32 MaxHeight = 0;`
- L27 _public member_ `int32 MaxProfile = 0;`
- L28 _public member_ `int32 MaxProfileLevel = 0;`
- L29 _public member_ `int32 MaxFrameRate= 0;`
- L30 _public member_ `const ElectraDecodersUtil::MPEG::H264::FAVCDecoderConfigurationRecord* CodecData = nullptr;`
- L31 _public member_ `uint32 NativeDecoderID = 0;`
- L32 _public member_ `bool bUseVideoCodecSurface = false;`
- L33 _public member_ `jobject VideoCodecSurface = nullptr;` — global reference expected
- L34 _public member_ `bool bSurfaceIsView = false;`

#### struct `IElectraH264VideoDecoderAndroidJava::FDecoderInformation`  
`struct FDecoderInformation`  
_L37-42_
- L39 _public member_ `int32 ApiLevel = 0;`
- L40 _public member_ `bool bIsAdaptive = false;`
- L41 _public member_ `bool bCanUse_SetOutputSurface = false;`

#### struct `IElectraH264VideoDecoderAndroidJava::FOutputFormatInfo`  
`struct FOutputFormatInfo`  
_L44-78_
- L46 _public function_ `FOutputFormatInfo()`
- L51 _public function_ `void Clear()`
- L64 _public function_ `bool IsValid() const`
- L69 _public member_ `int32 Width;`
- L70 _public member_ `int32 Height;`
- L71 _public member_ `int32 CropTop;`
- L72 _public member_ `int32 CropBottom;`
- L73 _public member_ `int32 CropLeft;`
- L74 _public member_ `int32 CropRight;`
- L75 _public member_ `int32 Stride;`
- L76 _public member_ `int32 SliceHeight;`
- L77 _public member_ `int32 ColorFormat;`

#### struct `IElectraH264VideoDecoderAndroidJava::FOutputBufferInfo`  
`struct FOutputBufferInfo`  
_L80-110_
- L89 _public function_ `FOutputBufferInfo()`
- L94 _public function_ `void Clear()`
- L104 _public member_ `int64 PresentationTimestamp;`
- L105 _public member_ `int32 BufferIndex;`
- L106 _public member_ `int32 Size;`
- L107 _public member_ `int32 ValidCount;`
- L108 _public member_ `bool bIsEOS;`
- L109 _public member_ `bool bIsConfig;`

#### enum `IElectraH264VideoDecoderAndroidJava::FOutputBufferInfo::EBufferIndexValues`  
`enum EBufferIndexValues`  
_L82-87_
- L84 _public enumerator_ `MediaCodec_INFO_TRY_AGAIN_LATER = -1`
- L85 _public enumerator_ `MediaCodec_INFO_OUTPUT_FORMAT_CHANGED = -2`
- L86 _public enumerator_ `MediaCodec_INFO_OUTPUT_BUFFERS_CHANGED = -3`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/h265/H265_VideoDecoder_Android.h` (Private)


#### class `FH265VideoDecoderAndroid`  
`class FH265VideoDecoderAndroid`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/h265/VideoDecoderH265_Android.h` (Private)


#### class `IElectraVideoDecoderH265_Android`  
`class IElectraVideoDecoderH265_Android : public IElectraDecoder`  
_L7-31_
- inherits: `IElectraDecoder`
- L25 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L27 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L28 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L30 _public prototype_ `virtual ~IElectraVideoDecoderH265_Android() = default;`

#### struct `IElectraVideoDecoderH265_Android::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L10-24_
- L12 _public function_ `FSupportedConfiguration(int32 InTier, int32 InProfile, uint32 InProfileCompatibility, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum8x8Macroblocks) : Tier(InTier), Profile(InProfile), ProfileCompatibility(InProfileCompatibility), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num8x8Macroblocks(InNum8x8Macroblocks)`
- L16 _public member_ `int32 Tier = 0;`
- L17 _public member_ `int32 Profile = 0;`
- L18 _public member_ `int32 ProfileCompatibility = 0;`
- L19 _public member_ `int32 Level = 0;`
- L20 _public member_ `int32 FramesPerSecond = 0;`
- L21 _public member_ `int32 Width = 0;`
- L22 _public member_ `int32 Height = 0;`
- L23 _public member_ `int32 Num8x8Macroblocks = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/h265/VideoDecoderH265_JavaWrapper_Android.h` (Private)


#### class `IElectraH265VideoDecoderAndroidJava`  
`class IElectraH265VideoDecoderAndroidJava`  
_L15-262_
- L19 _public prototype_ `static TSharedPtr<IElectraH265VideoDecoderAndroidJava, ESPMode::ThreadSafe> Create();`
- L21 _public prototype_ `virtual ~IElectraH265VideoDecoderAndroidJava() = default;`
- L119 _public prototype_ `virtual int32 CreateDecoder() = 0;` — Creates a Java instance of an H.265 video decoder. @return 0 if successful, 1 on error.
- L128 _public prototype_ `virtual int32 InitializeDecoder(const FCreateParameters& InCreateParams) = 0;` — Initializes the video decoder instance. @param InCreateParams @return 0 if successful, 1 on error.
- L137 _public prototype_ `virtual int32 SetOutputSurface(jobject InNewOutputSurface) = 0;` — Attempts to set a new output surface on an existing and configured decoder. @param InNewOutputSurface @return 0 if successful, 1 on error.
- L144 _public prototype_ `virtual int32 ReleaseDecoder() = 0;` — Releases (destroys) the Java video decoder instance. @return 0 if successful, 1 on error.
- L151 _public prototype_ `virtual const FDecoderInformation* GetDecoderInformation() = 0;` — Returns decoder information after a successful InitializeDecoder(). @return Pointer to decoder information or null when no decoder has been created.
- L158 _public prototype_ `virtual int32 Start() = 0;` — Starts the decoder instance. @return 0 if successful, 1 on error.
- L165 _public prototype_ `virtual int32 Stop() = 0;` — Stops the decoder instance. @return 0 if successful, 1 on error.
- L172 _public prototype_ `virtual int32 Flush() = 0;` — Flushes the decoder instance. @return 0 if successful, 1 on error.
- L179 _public prototype_ `virtual int32 Reset() = 0;` — Resets the decoder instance. @return 0 if successful, 1 on error.
- L188 _public prototype_ `virtual int32 DequeueInputBuffer(int32 InTimeoutUsec) = 0;` — Dequeues an input buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return >= 0 returns the index of the successfully dequeued buffer, negative values indicate an error.
- L202 _public prototype_ `virtual int32 QueueInputBuffer(int32 InBufferIndex, const void* InPrefixData, int32 InPrefixSize, const void* InAccessUnitData, int32 InAccessUnitSize, int64 InTimestampUSec) = 0;` — Queues input for decoding in the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put data into and enqueue for decoding (see DequeueInputBuffer()). @param InPrefixData Data to prefix the data to decode with. If given it is usually the SPS & PPS. @param InPrefixSize Size of the prefix data. @param InAccessUnitData Data to be decoded. @param InAccessUnitSize Size of the data to be decoded. @param InTimestampUSec Timestamp (PTS) of the data, in microseconds. @return 0 if successful, 1 on error.
- L214 _public prototype_ `virtual int32 QueueCSDInputBuffer(int32 InBufferIndex, const void* InCSDData, int32 InCSDSize, int64 InTimestampUSec) = 0;` — Queues codec specific data for the following to-be-decoded data buffers. @param InBufferIndex Index of the buffer to put data into and enqueue for decoding (see DequeueInputBuffer()). @param InCSDData Codec specific data @param InCSDSize Size of the codec specific data @param InTimestampUSec Timestamp (PTS) of the data, in microseconds. Must be the same as the next data to be decoded. @return 0 if successful, 1 on error.
- L224 _public prototype_ `virtual int32 QueueEOSInputBuffer(int32 InBufferIndex, int64 InTimestampUSec) = 0;` — Queues end of stream for the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put the EOS flag into and enqueue for decoding (see DequeueInputBuffer()). @param InTimestampUSec Timestamp the previous data had. Can be 0. @return 0 if successful, 1 on error.
- L234 _public prototype_ `virtual int32 GetOutputFormatInfo(FOutputFormatInfo& OutFormatInfo, int32 InOutputBufferIndex) = 0;` — Returns format information of the decoded samples. @param OutFormatInfo @param InOutputBufferIndex RESERVED FOR NOW - Pass any negative value to get the output format after DequeueOutputBuffer() returns a BufferIndex of MediaCodec_INFO_OUTPUT_FORMAT_CHANGED. @return 0 if successful, 1 on error.
- L243 _public prototype_ `virtual int32 DequeueOutputBuffer(FOutputBufferInfo& OutBufferInfo, int32 InTimeoutUsec) = 0;` — Dequeues an output buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return 0 on success, 1 on failure. The OutBufferInfo.BufferIndex indicates the buffer index.
- L254 _public prototype_ `virtual int32 GetOutputBuffer(void*& OutBufferDataPtr, int32 OutBufferDataSize, const FOutputBufferInfo& InOutBufferInfo) = 0;` — Returns the decoded samples from a decoder output buffer in the decoder native format. @param OutBufferDataPtr @param OutBufferDataSize @param InOutBufferInfo @return 0 on success, 1 on failure.
- L261 _public prototype_ `virtual int32 ReleaseOutputBuffer(int32 BufferIndex, int32 ValidCount, bool bRender, int64 releaseAt) = 0;` — Releases the decoder output buffer back to the decoder. @return 0 on success, 1 on failure.

#### struct `IElectraH265VideoDecoderAndroidJava::FCreateParameters`  
`struct FCreateParameters`  
_L23-36_
- L25 _public member_ `int32 MaxWidth = 0;`
- L26 _public member_ `int32 MaxHeight = 0;`
- L27 _public member_ `int32 MaxTier = 0;`
- L28 _public member_ `int32 MaxProfile = 0;`
- L29 _public member_ `int32 MaxProfileLevel = 0;`
- L30 _public member_ `int32 MaxFrameRate= 0;`
- L31 _public member_ `const ElectraDecodersUtil::MPEG::H265::FHEVCDecoderConfigurationRecord* CodecData = nullptr;`
- L32 _public member_ `uint32 NativeDecoderID = 0;`
- L33 _public member_ `bool bUseVideoCodecSurface = false;`
- L34 _public member_ `jobject VideoCodecSurface = nullptr;` — global reference expected
- L35 _public member_ `bool bSurfaceIsView = false;`

#### struct `IElectraH265VideoDecoderAndroidJava::FDecoderInformation`  
`struct FDecoderInformation`  
_L38-43_
- L40 _public member_ `int32 ApiLevel = 0;`
- L41 _public member_ `bool bIsAdaptive = false;`
- L42 _public member_ `bool bCanUse_SetOutputSurface = false;`

#### struct `IElectraH265VideoDecoderAndroidJava::FOutputFormatInfo`  
`struct FOutputFormatInfo`  
_L45-79_
- L47 _public function_ `FOutputFormatInfo()`
- L52 _public function_ `void Clear()`
- L65 _public function_ `bool IsValid() const`
- L70 _public member_ `int32 Width;`
- L71 _public member_ `int32 Height;`
- L72 _public member_ `int32 CropTop;`
- L73 _public member_ `int32 CropBottom;`
- L74 _public member_ `int32 CropLeft;`
- L75 _public member_ `int32 CropRight;`
- L76 _public member_ `int32 Stride;`
- L77 _public member_ `int32 SliceHeight;`
- L78 _public member_ `int32 ColorFormat;`

#### struct `IElectraH265VideoDecoderAndroidJava::FOutputBufferInfo`  
`struct FOutputBufferInfo`  
_L81-111_
- L90 _public function_ `FOutputBufferInfo()`
- L95 _public function_ `void Clear()`
- L105 _public member_ `int64 PresentationTimestamp;`
- L106 _public member_ `int32 BufferIndex;`
- L107 _public member_ `int32 Size;`
- L108 _public member_ `int32 ValidCount;`
- L109 _public member_ `bool bIsEOS;`
- L110 _public member_ `bool bIsConfig;`

#### enum `IElectraH265VideoDecoderAndroidJava::FOutputBufferInfo::EBufferIndexValues`  
`enum EBufferIndexValues`  
_L83-88_
- L85 _public enumerator_ `MediaCodec_INFO_TRY_AGAIN_LATER = -1`
- L86 _public enumerator_ `MediaCodec_INFO_OUTPUT_FORMAT_CHANGED = -2`
- L87 _public enumerator_ `MediaCodec_INFO_OUTPUT_BUFFERS_CHANGED = -3`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/vpx/VPx_VideoDecoder_Android.h` (Private)


#### class `FVPxVideoDecoderAndroid`  
`class FVPxVideoDecoderAndroid`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/vpx/VideoDecoderVPx_Android.h` (Private)


#### class `IElectraVideoDecoderVPx_Android`  
`class IElectraVideoDecoderVPx_Android : public IElectraDecoder`  
_L7-31_
- inherits: `IElectraDecoder`
- L25 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L27 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L28 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L30 _public prototype_ `virtual ~IElectraVideoDecoderVPx_Android() = default;`

#### struct `IElectraVideoDecoderVPx_Android::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L10-24_
- L12 _public function_ `FSupportedConfiguration(int32 InTier, int32 InProfile, uint32 InProfileCompatibility, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum8x8Macroblocks) : Tier(InTier), Profile(InProfile), ProfileCompatibility(InProfileCompatibility), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num8x8Macroblocks(InNum8x8Macroblocks)`
- L16 _public member_ `int32 Tier = 0;`
- L17 _public member_ `int32 Profile = 0;`
- L18 _public member_ `int32 ProfileCompatibility = 0;`
- L19 _public member_ `int32 Level = 0;`
- L20 _public member_ `int32 FramesPerSecond = 0;`
- L21 _public member_ `int32 Width = 0;`
- L22 _public member_ `int32 Height = 0;`
- L23 _public member_ `int32 Num8x8Macroblocks = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Android/vpx/VideoDecoderVPx_JavaWrapper_Android.h` (Private)


#### class `IElectraVPxVideoDecoderAndroidJava`  
`class IElectraVPxVideoDecoderAndroidJava`  
_L15-260_
- L19 _public prototype_ `static TSharedPtr<IElectraVPxVideoDecoderAndroidJava, ESPMode::ThreadSafe> Create();`
- L21 _public prototype_ `virtual ~IElectraVPxVideoDecoderAndroidJava() = default;`
- L117 _public prototype_ `virtual int32 CreateDecoder(bool bCreateVP9) = 0;` — Creates a Java instance of a VP8 or VP9 video decoder. @return 0 if successful, 1 on error.
- L126 _public prototype_ `virtual int32 InitializeDecoder(const FCreateParameters& InCreateParams) = 0;` — Initializes the video decoder instance. @param InCreateParams @return 0 if successful, 1 on error.
- L135 _public prototype_ `virtual int32 SetOutputSurface(jobject InNewOutputSurface) = 0;` — Attempts to set a new output surface on an existing and configured decoder. @param InNewOutputSurface @return 0 if successful, 1 on error.
- L142 _public prototype_ `virtual int32 ReleaseDecoder() = 0;` — Releases (destroys) the Java video decoder instance. @return 0 if successful, 1 on error.
- L149 _public prototype_ `virtual const FDecoderInformation* GetDecoderInformation() = 0;` — Returns decoder information after a successful InitializeDecoder(). @return Pointer to decoder information or null when no decoder has been created.
- L156 _public prototype_ `virtual int32 Start() = 0;` — Starts the decoder instance. @return 0 if successful, 1 on error.
- L163 _public prototype_ `virtual int32 Stop() = 0;` — Stops the decoder instance. @return 0 if successful, 1 on error.
- L170 _public prototype_ `virtual int32 Flush() = 0;` — Flushes the decoder instance. @return 0 if successful, 1 on error.
- L177 _public prototype_ `virtual int32 Reset() = 0;` — Resets the decoder instance. @return 0 if successful, 1 on error.
- L186 _public prototype_ `virtual int32 DequeueInputBuffer(int32 InTimeoutUsec) = 0;` — Dequeues an input buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return >= 0 returns the index of the successfully dequeued buffer, negative values indicate an error.
- L200 _public prototype_ `virtual int32 QueueInputBuffer(int32 InBufferIndex, const void* InPrefixData, int32 InPrefixSize, const void* InAccessUnitData, int32 InAccessUnitSize, int64 InTimestampUSec) = 0;` — Queues input for decoding in the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put data into and enqueue for decoding (see DequeueInputBuffer()). @param InPrefixData Data to prefix the data to decode with. If given it is usually the SPS & PPS. @param InPrefixSize Size of the prefix data. @param InAccessUnitData Data to be decoded. @param InAccessUnitSize Size of the data to be decoded. @param InTimestampUSec Timestamp (PTS) of the data, in microseconds. @return 0 if successful, 1 on error.
- L212 _public prototype_ `virtual int32 QueueCSDInputBuffer(int32 InBufferIndex, const void* InCSDData, int32 InCSDSize, int64 InTimestampUSec) = 0;` — Queues codec specific data for the following to-be-decoded data buffers. @param InBufferIndex Index of the buffer to put data into and enqueue for decoding (see DequeueInputBuffer()). @param InCSDData Codec specific data @param InCSDSize Size of the codec specific data @param InTimestampUSec Timestamp (PTS) of the data, in microseconds. Must be the same as the next data to be decoded. @return 0 if successful, 1 on error.
- L222 _public prototype_ `virtual int32 QueueEOSInputBuffer(int32 InBufferIndex, int64 InTimestampUSec) = 0;` — Queues end of stream for the buffer with a previously dequeued (calling DequeueInputBuffer()) index. @param InBufferIndex Index of the buffer to put the EOS flag into and enqueue for decoding (see DequeueInputBuffer()). @param InTimestampUSec Timestamp the previous data had. Can be 0. @return 0 if successful, 1 on error.
- L232 _public prototype_ `virtual int32 GetOutputFormatInfo(FOutputFormatInfo& OutFormatInfo, int32 InOutputBufferIndex) = 0;` — Returns format information of the decoded samples. @param OutFormatInfo @param InOutputBufferIndex RESERVED FOR NOW - Pass any negative value to get the output format after DequeueOutputBuffer() returns a BufferIndex of MediaCodec_INFO_OUTPUT_FORMAT_CHANGED. @return 0 if successful, 1 on error.
- L241 _public prototype_ `virtual int32 DequeueOutputBuffer(FOutputBufferInfo& OutBufferInfo, int32 InTimeoutUsec) = 0;` — Dequeues an output buffer. @param InTimeoutUsec Timeout in microseconds to wait for an available buffer. @return 0 on success, 1 on failure. The OutBufferInfo.BufferIndex indicates the buffer index.
- L252 _public prototype_ `virtual int32 GetOutputBuffer(void*& OutBufferDataPtr, int32 OutBufferDataSize, const FOutputBufferInfo& InOutBufferInfo) = 0;` — Returns the decoded samples from a decoder output buffer in the decoder native format. @param OutBufferDataPtr @param OutBufferDataSize @param InOutBufferInfo @return 0 on success, 1 on failure.
- L259 _public prototype_ `virtual int32 ReleaseOutputBuffer(int32 BufferIndex, int32 ValidCount, bool bRender, int64 releaseAt) = 0;` — Releases the decoder output buffer back to the decoder. @return 0 on success, 1 on failure.

#### struct `IElectraVPxVideoDecoderAndroidJava::FCreateParameters`  
`struct FCreateParameters`  
_L23-34_
- L25 _public member_ `int32 MaxWidth = 0;`
- L26 _public member_ `int32 MaxHeight = 0;`
- L27 _public member_ `int32 MaxProfile = 0;`
- L28 _public member_ `int32 MaxFrameRate= 0;`
- L29 _public member_ `const ElectraDecodersUtil::VPxVideo::FVP9UncompressedHeader* CodecData = nullptr;`
- L30 _public member_ `uint32 NativeDecoderID = 0;`
- L31 _public member_ `bool bUseVideoCodecSurface = false;`
- L32 _public member_ `jobject VideoCodecSurface = nullptr;` — global reference expected
- L33 _public member_ `bool bSurfaceIsView = false;`

#### struct `IElectraVPxVideoDecoderAndroidJava::FDecoderInformation`  
`struct FDecoderInformation`  
_L36-41_
- L38 _public member_ `int32 ApiLevel = 0;`
- L39 _public member_ `bool bIsAdaptive = false;`
- L40 _public member_ `bool bCanUse_SetOutputSurface = false;`

#### struct `IElectraVPxVideoDecoderAndroidJava::FOutputFormatInfo`  
`struct FOutputFormatInfo`  
_L43-77_
- L45 _public function_ `FOutputFormatInfo()`
- L50 _public function_ `void Clear()`
- L63 _public function_ `bool IsValid() const`
- L68 _public member_ `int32 Width;`
- L69 _public member_ `int32 Height;`
- L70 _public member_ `int32 CropTop;`
- L71 _public member_ `int32 CropBottom;`
- L72 _public member_ `int32 CropLeft;`
- L73 _public member_ `int32 CropRight;`
- L74 _public member_ `int32 Stride;`
- L75 _public member_ `int32 SliceHeight;`
- L76 _public member_ `int32 ColorFormat;`

#### struct `IElectraVPxVideoDecoderAndroidJava::FOutputBufferInfo`  
`struct FOutputBufferInfo`  
_L79-109_
- L88 _public function_ `FOutputBufferInfo()`
- L93 _public function_ `void Clear()`
- L103 _public member_ `int64 PresentationTimestamp;`
- L104 _public member_ `int32 BufferIndex;`
- L105 _public member_ `int32 Size;`
- L106 _public member_ `int32 ValidCount;`
- L107 _public member_ `bool bIsEOS;`
- L108 _public member_ `bool bIsConfig;`

#### enum `IElectraVPxVideoDecoderAndroidJava::FOutputBufferInfo::EBufferIndexValues`  
`enum EBufferIndexValues`  
_L81-86_
- L83 _public enumerator_ `MediaCodec_INFO_TRY_AGAIN_LATER = -1`
- L84 _public enumerator_ `MediaCodec_INFO_OUTPUT_FORMAT_CHANGED = -2`
- L85 _public enumerator_ `MediaCodec_INFO_OUTPUT_BUFFERS_CHANGED = -3`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/ApplePlatformElectraDecoders.h` (Private)


#### class `FPlatformElectraDecodersApple`  
`class FPlatformElectraDecodersApple`  
_L11-17_
- L14 _public prototype_ `static void Startup();`
- L15 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static void RegisterWithCodecFactory(IElectraCodecRegistry* InCodecFactoryToRegisterWith);`

#### Free symbols / members of external scopes

- L19 _typedef_ `using FPlatformElectraDecoders = FPlatformElectraDecodersApple;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/DecoderErrors_Apple.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define ERRCODE_INTERNAL_NO_ERROR 0`
- L6 _macro_ `#define ERRCODE_INTERNAL_UNEXPECTED_PROBLEM 1`
- L7 _macro_ `#define ERRCODE_INTERNAL_ALREADY_CLOSED 2`
- L8 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_PARSE_CSD 3`
- L9 _macro_ `#define ERRCODE_INTERNAL_COULD_NOT_CREATE_DECODER 4`
- L10 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_DECODE_INPUT 5`
- L11 _macro_ `#define ERRCODE_INTERNAL_DID_NOT_GET_INPUT_BUFFER 6`
- L12 _macro_ `#define ERRCODE_INTERNAL_DID_NOT_GET_OUTPUT_BUFFER 7`
- L13 _macro_ `#define ERRCODE_INTERNAL_COULD_NOT_GET_OUTPUT_FORMAT 8`
- L14 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_HANDLE_OUTPUT 9`
- L15 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CONVERT_OUTPUT_SAMPLE 10`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/aac/AAC_AudioDecoder_Apple.h` (Private)


#### class `FAACAudioDecoderApple`  
`class FAACAudioDecoderApple`  
_L12-17_
- L15 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/aac/AudioDecoderAAC_Apple.h` (Private)


#### class `IElectraAudioDecoderAAC_Apple`  
`class IElectraAudioDecoderAAC_Apple : public IElectraDecoder`  
_L9-16_
- inherits: `IElectraDecoder`
- L12 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L13 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L15 _public prototype_ `virtual ~IElectraAudioDecoderAAC_Apple() = default;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/h264/H264_VideoDecoder_Apple.h` (Private)


#### class `FH264VideoDecoderApple`  
`class FH264VideoDecoderApple`  
_L11-16_
- L14 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/h264/VideoDecoderH264_Apple.h` (Private)


#### class `IElectraVideoDecoderH264_Apple`  
`class IElectraVideoDecoderH264_Apple : public IElectraDecoder`  
_L9-31_
- inherits: `IElectraDecoder`
- L25 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L27 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L28 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L30 _public prototype_ `virtual ~IElectraVideoDecoderH264_Apple() = default;`

#### struct `IElectraVideoDecoderH264_Apple::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L12-24_
- L14 _public function_ `FSupportedConfiguration(int32 InProfile, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum16x16Macroblocks) : Profile(InProfile), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num16x16Macroblocks(InNum16x16Macroblocks)`
- L18 _public member_ `int32 Profile = 0;`
- L19 _public member_ `int32 Level = 0;`
- L20 _public member_ `int32 FramesPerSecond = 0;`
- L21 _public member_ `int32 Width = 0;`
- L22 _public member_ `int32 Height = 0;`
- L23 _public member_ `int32 Num16x16Macroblocks = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/h265/H265_VideoDecoder_Apple.h` (Private)


#### class `FH265VideoDecoderApple`  
`class FH265VideoDecoderApple`  
_L11-16_
- L14 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Apple/h265/VideoDecoderH265_Apple.h` (Private)


#### class `IElectraVideoDecoderH265_Apple`  
`class IElectraVideoDecoderH265_Apple : public IElectraDecoder`  
_L9-33_
- inherits: `IElectraDecoder`
- L27 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L29 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L30 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L32 _public prototype_ `virtual ~IElectraVideoDecoderH265_Apple() = default;`

#### struct `IElectraVideoDecoderH265_Apple::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L12-26_
- L14 _public function_ `FSupportedConfiguration(int32 InTier, int32 InProfile, uint32 InProfileCompatibility, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum8x8Macroblocks) : Tier(InTier), Profile(InProfile), ProfileCompatibility(InProfileCompatibility), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num8x8Macroblocks(InNum8x8Macroblocks)`
- L18 _public member_ `int32 Tier = 0;`
- L19 _public member_ `int32 Profile = 0;`
- L20 _public member_ `int32 ProfileCompatibility = 0;`
- L21 _public member_ `int32 Level = 0;`
- L22 _public member_ `int32 FramesPerSecond = 0;`
- L23 _public member_ `int32 Width = 0;`
- L24 _public member_ `int32 Height = 0;`
- L25 _public member_ `int32 Num8x8Macroblocks = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/DX/AudioDecoderAAC_DX.h` (Private)


#### class `IElectraAudioDecoderAAC_DX`  
`class IElectraAudioDecoderAAC_DX : public IElectraDecoder`  
_L9-16_
- inherits: `IElectraDecoder`
- L12 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L13 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L15 _public prototype_ `virtual ~IElectraAudioDecoderAAC_DX() = default;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/DX/DecoderErrors_DX.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define ERRCODE_INTERNAL_NO_ERROR 0`
- L6 _macro_ `#define ERRCODE_INTERNAL_BAD_PARAMETER 1`
- L7 _macro_ `#define ERRCODE_INTERNAL_ALREADY_CLOSED 2`
- L8 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_PARSE_CSD 3`
- L9 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CREATE_DECODER 4`
- L10 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_SET_OUTPUT_TYPE 5`
- L11 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CREATE_BUFFER 6`
- L12 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CREATE_INPUT_SAMPLE 7`
- L13 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_PROCESS_INPUT 8`
- L14 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_PROCESS_OUTPUT 9`
- L15 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CONVERT_OUTPUT_SAMPLE 10`
- L16 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_FLUSH_DECODER 11`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/DX/VideoDecoderH264_DX.h` (Private)


#### class `IElectraVideoDecoderH264_DX`  
`class IElectraVideoDecoderH264_DX : public IElectraDecoder`  
_L9-49_
- inherits: `IElectraDecoder`
- L12 _public prototype_ `static bool PlatformStaticInitialize();`
- L27 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L29 _public prototype_ `static void PlatformGetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L42 _public prototype_ `static FError PlatformCreateMFDecoderTransform(IPlatformHandle** OutPlatformHandle, const TMap<FString, FVariant>& InOptions);`
- L43 _public prototype_ `static void PlatformReleaseMFDecoderTransform(IPlatformHandle** OutPlatformHandle);`
- L46 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L48 _public prototype_ `virtual ~IElectraVideoDecoderH264_DX() = default;`

#### struct `IElectraVideoDecoderH264_DX::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L14-26_
- L16 _public function_ `FSupportedConfiguration(int32 InProfile, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum16x16Macroblocks) : Profile(InProfile), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num16x16Macroblocks(InNum16x16Macroblocks)`
- L20 _public member_ `int32 Profile = 0;`
- L21 _public member_ `int32 Level = 0;`
- L22 _public member_ `int32 FramesPerSecond = 0;`
- L23 _public member_ `int32 Width = 0;`
- L24 _public member_ `int32 Height = 0;`
- L25 _public member_ `int32 Num16x16Macroblocks = 0;`

#### class `IElectraVideoDecoderH264_DX::IPlatformHandle`  
`class IPlatformHandle`  
_L31-41_
- L34 _protected prototype_ `virtual ~IPlatformHandle() = default;`
- L36 _public prototype_ `virtual int32 GetDXVersionTimes1000() const = 0;`
- L37 _public prototype_ `virtual void* GetMFTransform() const = 0;`
- L38 _public prototype_ `virtual void* GetDXDevice() const = 0;`
- L39 _public prototype_ `virtual void* GetDXDeviceContext() const = 0;`
- L40 _public prototype_ `virtual bool IsSoftware() const = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/DX/VideoDecoderH265_DX.h` (Private)


#### class `IElectraVideoDecoderH265_DX`  
`class IElectraVideoDecoderH265_DX : public IElectraDecoder`  
_L9-51_
- inherits: `IElectraDecoder`
- L12 _public prototype_ `static bool PlatformStaticInitialize();`
- L29 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L31 _public prototype_ `static void PlatformGetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L44 _public prototype_ `static FError PlatformCreateMFDecoderTransform(IPlatformHandle** OutPlatformHandle, const TMap<FString, FVariant>& InOptions);`
- L45 _public prototype_ `static void PlatformReleaseMFDecoderTransform(IPlatformHandle** OutPlatformHandle);`
- L48 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L50 _public prototype_ `virtual ~IElectraVideoDecoderH265_DX() = default;`

#### struct `IElectraVideoDecoderH265_DX::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L14-28_
- L16 _public function_ `FSupportedConfiguration(int32 InTier, int32 InProfile, uint32 InProfileCompatibility, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum8x8Macroblocks) : Tier(InTier), Profile(InProfile), ProfileCompatibility(InProfileCompatibility), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num8x8Macroblocks(InNum8x8Macroblocks)`
- L20 _public member_ `int32 Tier = 0;`
- L21 _public member_ `int32 Profile = 0;`
- L22 _public member_ `int32 ProfileCompatibility = 0;`
- L23 _public member_ `int32 Level = 0;`
- L24 _public member_ `int32 FramesPerSecond = 0;`
- L25 _public member_ `int32 Width = 0;`
- L26 _public member_ `int32 Height = 0;`
- L27 _public member_ `int32 Num8x8Macroblocks = 0;`

#### class `IElectraVideoDecoderH265_DX::IPlatformHandle`  
`class IPlatformHandle`  
_L33-43_
- L36 _protected prototype_ `virtual ~IPlatformHandle() = default;`
- L38 _public prototype_ `virtual int32 GetDXVersionTimes1000() const = 0;`
- L39 _public prototype_ `virtual void* GetMFTransform() const = 0;`
- L40 _public prototype_ `virtual void* GetDXDevice() const = 0;`
- L41 _public prototype_ `virtual void* GetDXDeviceContext() const = 0;`
- L42 _public prototype_ `virtual bool IsSoftware() const = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/ElectraDecodersModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraDecoders, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraDecoders, Log, All);`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/ElectraMediaMP3Decoder.h` (Private)


#### class `FElectraMediaMP3Decoder`  
`class FElectraMediaMP3Decoder`  
_L8-14_
- L11 _public prototype_ `static void Startup();`
- L12 _public prototype_ `static void Shutdown();`
- L13 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/IOS/IOSPlatformElectraDecoders.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/DecoderErrors_Linux.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define ERRCODE_INTERNAL_NO_ERROR 0`
- L6 _macro_ `#define ERRCODE_INTERNAL_DECODER_NOT_SUPPORTED 1`
- L7 _macro_ `#define ERRCODE_INTERNAL_ALREADY_CLOSED 2`
- L8 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_PARSE_CSD 3`
- L9 _macro_ `#define ERRCODE_INTERNAL_COULD_NOT_CREATE_DECODER 4`
- L10 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_DECODE_INPUT 5`
- L11 _macro_ `#define ERRCODE_INTERNAL_DID_NOT_GET_INPUT_BUFFER 6`
- L12 _macro_ `#define ERRCODE_INTERNAL_DID_NOT_GET_OUTPUT_BUFFER 7`
- L13 _macro_ `#define ERRCODE_INTERNAL_COULD_NOT_GET_OUTPUT_FORMAT 8`
- L14 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_HANDLE_OUTPUT 9`
- L15 _macro_ `#define ERRCODE_INTERNAL_FAILED_TO_CONVERT_OUTPUT_SAMPLE 10`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/LinuxPlatformElectraDecoders.h` (Private)


#### class `FPlatformElectraDecodersLinux`  
`class FPlatformElectraDecodersLinux`  
_L11-17_
- L14 _public prototype_ `static void Startup();`
- L15 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static void RegisterWithCodecFactory(IElectraCodecRegistry* InCodecFactoryToRegisterWith);`

#### Free symbols / members of external scopes

- L19 _typedef_ `using FPlatformElectraDecoders = FPlatformElectraDecodersLinux;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/aac/AAC_AudioDecoder_Linux.h` (Private)


#### class `FAACAudioDecoderLinux`  
`class FAACAudioDecoderLinux`  
_L12-17_
- L15 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/aac/AudioDecoderAAC_Linux.h` (Private)


#### class `IElectraAudioDecoderAAC_Linux`  
`class IElectraAudioDecoderAAC_Linux : public IElectraDecoder`  
_L9-16_
- inherits: `IElectraDecoder`
- L12 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L13 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L15 _public prototype_ `virtual ~IElectraAudioDecoderAAC_Linux() = default;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/h264/H264_VideoDecoder_Linux.h` (Private)


#### class `FH264VideoDecoderLinux`  
`class FH264VideoDecoderLinux`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/h264/VideoDecoderH264_Linux.h` (Private)


#### class `IElectraVideoDecoderH264_Linux`  
`class IElectraVideoDecoderH264_Linux : public IElectraDecoder`  
_L7-29_
- inherits: `IElectraDecoder`
- L23 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L25 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L26 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L28 _public prototype_ `virtual ~IElectraVideoDecoderH264_Linux() = default;`

#### struct `IElectraVideoDecoderH264_Linux::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L10-22_
- L12 _public function_ `FSupportedConfiguration(int32 InProfile, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum16x16Macroblocks) : Profile(InProfile), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num16x16Macroblocks(InNum16x16Macroblocks)`
- L16 _public member_ `int32 Profile = 0;`
- L17 _public member_ `int32 Level = 0;`
- L18 _public member_ `int32 FramesPerSecond = 0;`
- L19 _public member_ `int32 Width = 0;`
- L20 _public member_ `int32 Height = 0;`
- L21 _public member_ `int32 Num16x16Macroblocks = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/h265/H265_VideoDecoder_Linux.h` (Private)


#### class `FH265VideoDecoderLinux`  
`class FH265VideoDecoderLinux`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/h265/VideoDecoderH265_Linux.h` (Private)


#### class `IElectraVideoDecoderH265_Linux`  
`class IElectraVideoDecoderH265_Linux : public IElectraDecoder`  
_L7-31_
- inherits: `IElectraDecoder`
- L25 _public prototype_ `static void PlatformGetSupportedConfigurations(TArray<FSupportedConfiguration>& OutSupportedConfigurations);`
- L27 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L28 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L30 _public prototype_ `virtual ~IElectraVideoDecoderH265_Linux() = default;`

#### struct `IElectraVideoDecoderH265_Linux::FSupportedConfiguration`  
`struct FSupportedConfiguration`  
_L10-24_
- L12 _public function_ `FSupportedConfiguration(int32 InTier, int32 InProfile, uint32 InProfileCompatibility, int32 InLevel, int32 InFramesPerSecond, int32 InWidth, int32 InHeight, int32 InNum8x8Macroblocks) : Tier(InTier), Profile(InProfile), ProfileCompatibility(InProfileCompatibility), Level(InLevel), FramesPerSecond(InFramesPerSecond), Width(InWidth), Height(InHeight), Num8x8Macroblocks(InNum8x8Macroblocks)`
- L16 _public member_ `int32 Tier = 0;`
- L17 _public member_ `int32 Profile = 0;`
- L18 _public member_ `int32 ProfileCompatibility = 0;`
- L19 _public member_ `int32 Level = 0;`
- L20 _public member_ `int32 FramesPerSecond = 0;`
- L21 _public member_ `int32 Width = 0;`
- L22 _public member_ `int32 Height = 0;`
- L23 _public member_ `int32 Num8x8Macroblocks = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/vpx/VPx_VideoDecoder_Linux.h` (Private)


#### class `FVPxVideoDecoderLinux`  
`class FVPxVideoDecoderLinux`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Linux/vpx/VideoDecoderVPx_Linux.h` (Private)


#### class `IElectraVideoDecoderVPx_Linux`  
`class IElectraVideoDecoderVPx_Linux : public IElectraDecoder`  
_L8-15_
- inherits: `IElectraDecoder`
- L11 _public prototype_ `static void GetConfigurationOptions(TMap<FString, FVariant>& OutOptions);`
- L12 _public prototype_ `static TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> Create(const Electra::FCodecTypeFormat& InCodecFormat, const TMap<FString, FVariant>& InAdditionalOptions);`
- L14 _public prototype_ `virtual ~IElectraVideoDecoderVPx_Linux() = default;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Mac/MacPlatformElectraDecoders.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/PlatformElectraDecoders.h` (Private)


#### class `FPlatformElectraDecodersNull`  
`class FPlatformElectraDecodersNull`  
_L11-23_
- L14 _public function_ `static void Startup()`
- L17 _public function_ `static void Shutdown()`
- L20 _public function_ `static void RegisterWithCodecFactory(IElectraCodecRegistry* InCodecFactoryToRegisterWith)`

#### Free symbols / members of external scopes

- L25 _typedef_ `using FPlatformElectraDecoders = FPlatformElectraDecodersNull;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/TVOS/TVOSPlatformElectraDecoders.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Utils/ElectraCodecFormatUtils.h` (Private)


#### class `FElectraCodecFormatUtilsModularFeature`  
`class FElectraCodecFormatUtilsModularFeature : public IElectraCodecFormatUtilsModularFeature`  
_L6-19_
- inherits: `IElectraCodecFormatUtilsModularFeature`
- L9 _public prototype_ `static void Startup();`
- L10 _public prototype_ `static void Shutdown();`
- L12 _public prototype_ `virtual ~FElectraCodecFormatUtilsModularFeature() = default;`
- L13 _public prototype_ `bool PrepareCodecTypeFormat(Electra::FCodecTypeFormat& InOutCodecTypeFormat, const FCodecTypeFormatParams& InCodecTypeFormatParams) override;`
- L15 _public prototype_ `static bool SetupCodecTypeFormat(Electra::FCodecTypeFormat& InOutCodecTypeFormat, const FCodecTypeFormatParams& InCodecTypeFormatParams);`
- L16 _public prototype_ `static bool SetupCodecTypeFormat(Electra::FCodecTypeFormat& InOutCodecTypeFormat);`
- L18 _private member_ `static FElectraCodecFormatUtilsModularFeature* Self;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Windows/WindowsPlatformElectraDecoders.h` (Private)


#### class `FPlatformElectraDecodersWindows`  
`class FPlatformElectraDecodersWindows`  
_L9-15_
- L12 _public prototype_ `static void Startup();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static void RegisterWithCodecFactory(IElectraCodecRegistry* InCodecFactoryToRegisterWith);`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FPlatformElectraDecoders = FPlatformElectraDecodersWindows;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Windows/WindowsPlatformHeaders_Audio_DX.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Windows/WindowsPlatformHeaders_Video_DX.h` (Private)


#### struct `FElectraVideoDecoderDXDeviceContext`  
`struct FElectraVideoDecoderDXDeviceContext`  
_L31-45_
- L33 _public function_ `void Release()`
- L38 _public function_ `void SetDeviceAndContext(void* InDxDevice, void* InDxDeviceContext)`
- L43 _public member_ `TRefCountPtr<ID3D11Device> DxDevice;`
- L44 _public member_ `TRefCountPtr<ID3D11DeviceContext> DxDeviceContext;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define ALLOW_MFSAMPLE_WITH_DX12 0`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Windows/aac/AAC_AudioDecoder_Windows.h` (Private)


#### class `FAACAudioDecoderWindows`  
`class FAACAudioDecoderWindows`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Windows/h264/H264_VideoDecoder_Windows.h` (Private)


#### class `FH264VideoDecoderWindows`  
`class FH264VideoDecoderWindows`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Private/Windows/h265/H265_VideoDecoder_Windows.h` (Private)


#### class `FH265VideoDecoderWindows`  
`class FH265VideoDecoderWindows`  
_L9-14_
- L12 _public prototype_ `static TSharedPtr<IElectraCodecFactory, ESPMode::ThreadSafe> CreateFactory();`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Android/AndroidElectraDecoderPlatformOutputHandleTypes.h` (Public)


#### enum `EElectraDecoderPlatformOutputHandleType`  
`enum class EElectraDecoderPlatformOutputHandleType`  
_L7-9_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Android/AndroidElectraDecodersPlatformResources.h` (Public)


#### class `FElectraDecodersPlatformResourcesAndroid`  
`class FElectraDecodersPlatformResourcesAndroid`  
_L18-57_
- L43 _public function_ `static const FName OptionKeyOutputTexturePoolID()`
- L45 _public prototype_ `static int64 RegisterOutputTexturePool(TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> InTexturePool);`
- L46 _public prototype_ `static void UnregisterOutputTexturePool(int64 InTexturePoolID);`
- L48 _public prototype_ `static IDecoderResourceInstance* CreateResourceInstance(int64 InResourceID);`
- L49 _public prototype_ `static void ReleaseResourceInstance(IDecoderResourceInstance* InInstanceToRelease);`
- L53 _public prototype_ `static IDecoderPlatformResource* CreatePlatformVideoResource(void* InOwnerHandle, const TMap<FString, FVariant> InOptions);`
- L54 _public prototype_ `static void ReleasePlatformVideoResource(void* InOwnerHandle, IDecoderPlatformResource* InHandleToRelease);`
- L56 _public prototype_ `static bool SetupOutputTextureSample(FString& OutErrorMessage, TSharedPtr<FElectraTextureSample, ESPMode::ThreadSafe> InOutTextureSampleToSetup, TSharedPtr<IElectraDecoderVideoOutput, ESPMode::ThreadSafe> InDecoderOutput, TSharedPtr<Electra::FParamDict, ESPMode::ThreadSafe> InOutBufferPropertes, IDecoderPlatformResource* InPlatformResource);`

#### class `FElectraDecodersPlatformResourcesAndroid::IDecoderResourceInstance`  
`class IDecoderResourceInstance`  
_L22-41_
- L25 _public prototype_ `virtual ~IDecoderResourceInstance() = default;`
- L40 _public prototype_ `virtual void RequestSurface(TWeakPtr<ISurfaceRequestCallback, ESPMode::ThreadSafe> InRequestCallback) = 0;` — The decoder calls this to request a surface onto which to decode.

#### class `FElectraDecodersPlatformResourcesAndroid::IDecoderResourceInstance::ISurfaceRequestCallback`  
`class ISurfaceRequestCallback : public TSharedFromThis<ISurfaceRequestCallback, ESPMode::ThreadSafe>`  
_L27-38_
- inherits: `TSharedFromThis<ISurfaceRequestCallback,ESPMode::ThreadSafe>`
- L30 _public prototype_ `virtual ~ISurfaceRequestCallback() = default;`
- L37 _public prototype_ `virtual void OnNewSurface(ESurfaceType InSurfaceType, jobject InSurface) = 0;`

#### enum `FElectraDecodersPlatformResourcesAndroid::IDecoderResourceInstance::ISurfaceRequestCallback::ESurfaceType`  
`enum class ESurfaceType`  
_L31-36_
- L33 _public enumerator_ `NoSurface` — No decoding surface. Must use CPU side buffer.
- L34 _public enumerator_ `Surface`
- L35 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L59 _typedef_ `using FElectraDecodersPlatformResources = FElectraDecodersPlatformResourcesAndroid;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Apple/AppleElectraDecoderPlatformOutputFormatTypes.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ElectraVideoDecoderFormatTypesApple`
- L15 _function_ `static inline int32 GetNumComponentBitsForPixelFormat(int32 InPixelFormat)` (scope `ElectraVideoDecoderFormatTypesApple`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Apple/AppleElectraDecoderPlatformOutputHandleTypes.h` (Public)


#### enum `EElectraDecoderPlatformOutputHandleType`  
`enum class EElectraDecoderPlatformOutputHandleType`  
_L9-12_
- L11 _public enumerator_ `ImageBuffers` — IElectraDecoderVideoOutputImageBuffers interface

#### class `FElectraDecoderOutputSync`  
`class FElectraDecoderOutputSync final`  
_L15-20_
- L18 _public prototype_ `FElectraDecoderOutputSync() = default;`
- L19 _public prototype_ `~FElectraDecoderOutputSync() = default;`

#### class `IElectraDecoderVideoOutputImageBuffers`  
`class IElectraDecoderVideoOutputImageBuffers`  
_L22-48_
- L26 _public prototype_ `virtual uint32 GetCodec4CC() const = 0;` — Return the 4cc of the codec. This determines how the rest of the information must be interpreted.
- L29 _public prototype_ `virtual int32 GetNumberOfBuffers() const = 0;` — Returns the number of separate image buffers making up the frame.
- L32 _public prototype_ `virtual TSharedPtr<TArray64<uint8>, ESPMode::ThreadSafe> GetBufferDataByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer data address.
- L35 _public prototype_ `virtual void* GetBufferTextureByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th CFImageBuffer ("texture") reference.
- L38 _public prototype_ `virtual bool GetBufferTextureSyncByIndex(int32 InBufferIndex, FElectraDecoderOutputSync& SyncObject) const = 0;` — Returns the n'th image buffer's GPU sync object to signal texture data as being ready to be read
- L41 _public prototype_ `virtual EPixelFormat GetBufferFormatByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer format
- L44 _public prototype_ `virtual EElectraTextureSamplePixelEncoding GetBufferEncodingByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer encoding
- L47 _public prototype_ `virtual int32 GetBufferPitchByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer pitch

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Apple/AppleElectraDecodersPlatformResources.h` (Public)


#### class `FElectraDecodersPlatformResourcesApple`  
`class FElectraDecodersPlatformResourcesApple`  
_L14-24_
- L17 _public prototype_ `static bool GetMetalDevice(void** OutMetalDevice);`
- L20 _public prototype_ `static IDecoderPlatformResource* CreatePlatformVideoResource(void* InOwnerHandle, const TMap<FString, FVariant> InOptions);`
- L21 _public prototype_ `static void ReleasePlatformVideoResource(void* InOwnerHandle, IDecoderPlatformResource* InHandleToRelease);`
- L23 _public prototype_ `static bool SetupOutputTextureSample(FString& OutErrorMessage, TSharedPtr<FElectraTextureSample, ESPMode::ThreadSafe> InOutTextureSampleToSetup, TSharedPtr<IElectraDecoderVideoOutput, ESPMode::ThreadSafe> InDecoderOutput, TSharedPtr<Electra::FParamDict, ESPMode::ThreadSafe> InOutBufferPropertes, IDecoderPlatformResource* InPlatformResource);`

#### Free symbols / members of external scopes

- L26 _typedef_ `using FElectraDecodersPlatformResources = FElectraDecodersPlatformResourcesApple;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/ElectraDecodersPlatformResources.h` (Public)


#### class `FElectraDecodersPlatformResourcesNull`  
`class FElectraDecodersPlatformResourcesNull`  
_L10-13_

#### Free symbols / members of external scopes

- L15 _typedef_ `using FElectraDecodersPlatformResources = FElectraDecodersPlatformResourcesNull;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/ElectraDecodersTypes.h` (Public)


#### struct `ElectraDecodersUtil::FFractionalValue`  
`struct FFractionalValue`  
_L9-16_
- L11 _public function_ `FFractionalValue(int64 InNumerator=0, uint32 InDenominator=0) : Num(InNumerator), Denom(InDenominator)`
- L14 _public member_ `int64 Num = 0;`
- L15 _public member_ `uint32 Denom = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ElectraDecodersUtil`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/ElectraDecodersUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ElectraDecodersUtil`
- L13 _function_ `static constexpr uint32 Make4CC(const uint8 A, const uint8 B, const uint8 C, const uint8 D)` (scope `ElectraDecodersUtil`)
- L20 _function_ `template <typename T, typename C> inline T AdvancePointer(T pPointer, C numBytes)` (scope `ElectraDecodersUtil`) — Advance a pointer by a number of bytes.
- L26 _function_ `template <typename T> inline T AbsoluteValue(T Value)` (scope `ElectraDecodersUtil`)
- L32 _function_ `template <typename T> inline T Min(T a, T b)` (scope `ElectraDecodersUtil`)
- L38 _function_ `template <typename T> inline T Max(T a, T b)` (scope `ElectraDecodersUtil`)
- L43 _function_ `inline uint32 BitReverse32(uint32 InValue)` (scope `ElectraDecodersUtil`)
- L59 _function_ `inline bool ExceedsMaxDimensions(const int64 InDimensionA, const int64 InDimensionB, const int64 InMaxDimensionA, const int64 InMaxDimensionB)` (scope `ElectraDecodersUtil`) — Returns true if the given dimensions exceed the configured maximum dimensions. The comparison is orientation-independent: the two dimensions are matched by magnitude (larger-against-larger, smaller-against-smaller) rather than positionally, so a portrait source is accepted against landscape-oriented limits and vice versa. A maximum of 0 means "no limit" for that dimension.
- L68 _prototype_ `bool PrepareCodecTypeFormat(Electra::FCodecTypeFormat& InOutCodecTypeFormat);` (scope `ElectraDecodersUtil`)
- L70 _prototype_ `int64 GetVariantValueSafeI64(const TMap<FString, FVariant>& InFromMap, const FString& InName, int64 InDefaultValue=0);` (scope `ElectraDecodersUtil`)
- L71 _prototype_ `uint64 GetVariantValueSafeU64(const TMap<FString, FVariant>& InFromMap, const FString& InName, uint64 InDefaultValue=0);` (scope `ElectraDecodersUtil`)
- L72 _prototype_ `double GetVariantValueSafeDouble(const TMap<FString, FVariant>& InFromMap, const FString& InName, double InDefaultValue=0.0);` (scope `ElectraDecodersUtil`)
- L73 _prototype_ `TArray<uint8> GetVariantValueUInt8Array(const TMap<FString, FVariant>& InFromMap, const FString& InName);` (scope `ElectraDecodersUtil`)
- L74 _prototype_ `FString GetVariantValueFString(const TMap<FString, FVariant>& InFromMap, const FString& InName);` (scope `ElectraDecodersUtil`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IElectraCodecFormatUtils.h` (Public)


#### class `IElectraCodecFormatUtilsModularFeature`  
`class IElectraCodecFormatUtilsModularFeature : public IModularFeature`  
_L12-40_
- inherits: `IModularFeature`
- L15 _public prototype_ `virtual ~IElectraCodecFormatUtilsModularFeature() = default;`
- L17 _public function_ `static FName GetModularFeatureName()`
- L39 _public prototype_ `virtual bool PrepareCodecTypeFormat(Electra::FCodecTypeFormat& InOutCodecTypeFormat, const FCodecTypeFormatParams& InCodecTypeFormatParams) = 0;` — Tries to prepare the given codec type format format with as much information as possible. On input: - set at least the .FourCC member OR the mime type with a codecs parameter - set the .RFC6381 member if possible and not already provided with the mime type - provide any additional boxes in .ExtraBoxes in ISO/IEC 14496-12 binary box format (these should be all boxes from the `stsd` or similar container box) On output: - true, with as many filled in values as could be derived from the given input. - false if no information could be derived from the given input.

#### struct `IElectraCodecFormatUtilsModularFeature::FCodecTypeFormatParams`  
`struct FCodecTypeFormatParams`  
_L23-26_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IElectraDecoder.h` (Public)


#### class `IElectraDecoderOutput`  
`class IElectraDecoderOutput`  
_L14-29_
- L17 _public prototype_ `virtual ~IElectraDecoderOutput() = default;`
- L25 _public prototype_ `virtual EType GetType() const = 0;`
- L27 _public prototype_ `virtual FTimespan GetPTS() const = 0;`
- L28 _public prototype_ `virtual uint64 GetUserValue() const = 0;`

#### enum `IElectraDecoderOutput::EType`  
`enum class EType`  
_L18-24_
- L20 _public enumerator_ `None`
- L21 _public enumerator_ `Video`
- L22 _public enumerator_ `Audio`
- L23 _public enumerator_ `Subtitle`

#### enum `EElectraDecoderFlags`  
`enum class EElectraDecoderFlags : uint32`  
_L32-42_
- L34 _public enumerator_ `None = 0`
- L35 _public enumerator_ `IsSyncSample = 0x01`
- L36 _public enumerator_ `IsDiscardable = 0x02`
- L37 _public enumerator_ `IsReplaySample = 0x04`
- L38 _public enumerator_ `IsLastReplaySample = 0x08`
- L39 _public enumerator_ `InitCSDOnly = 0x10`
- L40 _public enumerator_ `DoNotOutput = 0x20`
- L41 _public enumerator_ `InputIsProcessed = 0x100`

#### struct `FElectraDecoderInputAccessUnit`  
`struct FElectraDecoderInputAccessUnit`  
_L45-54_
- L47 _public member_ `const void* Data = nullptr;`
- L48 _public member_ `int64 DataSize = 0;`
- L49 _public member_ `FTimespan DTS;`
- L50 _public member_ `FTimespan PTS;`
- L51 _public member_ `FTimespan Duration;`
- L52 _public member_ `uint64 UserValue = 0;`
- L53 _public member_ `EElectraDecoderFlags Flags = EElectraDecoderFlags::None;`

#### class `IElectraDecoderBitstreamInfo`  
`class IElectraDecoderBitstreamInfo`  
_L58-62_
- L61 _public prototype_ `virtual ~IElectraDecoderBitstreamInfo() = default;`

#### class `IElectraDecoderBitstreamProcessor`  
`class IElectraDecoderBitstreamProcessor : public TSharedFromThis<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe>`  
_L66-108_
- inherits: `TSharedFromThis<IElectraDecoderBitstreamProcessor,ESPMode::ThreadSafe>`
- L69 _public prototype_ `virtual ~IElectraDecoderBitstreamProcessor() = default;`
- L82 _public prototype_ `virtual bool WillModifyBitstreamInPlace() = 0;` — Returns whether or not calling ProcessInputForDecoding() will modify the provided bitstream in place. If true you may need to create a temporary copy if you want to retain the bitstream in a cache.
- L87 _public prototype_ `virtual void Clear() = 0;` — Clears the processor. Must be called when seeking or flushing.
- L97 _public prototype_ `virtual EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) = 0;` — Processes the bitstream and places sideband information in the provided IElectraDecoderBitstreamInfo for use with a subsequent call to SetPropertiesOnOutput(). If necessary the bitstream is modified in place. See `WillModifyBitstreamInPlace()` Returns `Ok` or `Error`. If the codec specific data changed `CSDChanged` is returned which is only informational for you and is functionally the same as `Ok`.
- L102 _public prototype_ `virtual void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) = 0;` — Sets previously extracted sideband data in the provided output dictionary.
- L107 _public prototype_ `virtual FString GetLastError() = 0;` — Returns an error message if either method returned `Error`.

#### enum `IElectraDecoderBitstreamProcessor::EProcessResult`  
`enum class EProcessResult`  
_L71-76_
- L73 _public enumerator_ `Ok`
- L74 _public enumerator_ `CSDChanged`
- L75 _public enumerator_ `Error`

#### class `IElectraDecoder`  
`class IElectraDecoder : public TSharedFromThis<IElectraDecoder, ESPMode::ThreadSafe>`  
_L112-321_
- inherits: `TSharedFromThis<IElectraDecoder,ESPMode::ThreadSafe>`
- L116 _public prototype_ `virtual ~IElectraDecoder() = default;`
- L118 _public typedef_ `using FInputAccessUnit = FElectraDecoderInputAccessUnit;`
- L194 _public prototype_ `virtual EType GetType() const = 0;` — Returns the type of this decoder instance. This is useful to ensure that the correct type was indeed created and you did not get a different type of decoder from the factory if the format was ambiguous.
- L201 _public prototype_ `virtual void GetFeatures(TMap<FString, FVariant>& OutFeatures) const = 0;` — Populates the provided map with decoder features or required options. See IElectraDecoderFeature and IElectraDecoderOption. Not all decoders will provide the same features.
- L206 _public prototype_ `virtual FError GetError() const = 0;` — Returns the most recent error that you should retrieve when either method returns failure.
- L214 _public prototype_ `virtual void Close() = 0;` — Closes the decoder instance. This must be called prior to dropping the last reference of the decoder resulting in the call to its destructor. This may already close internally used resources. The decoder instance can no longer be used and all decoding and output related methods will return an error.
- L221 _public prototype_ `virtual ECSDCompatibility IsCompatibleWith(const TMap<FString, FVariant>& CSDAndAdditionalOptions) = 0;` — When a change in decoder specific data is detected, call this method to determine if the decoder can just continue decoding with the new CSD or if it needs to be drained or drained first and then reset.
- L227 _public prototype_ `virtual bool ResetToCleanStart() = 0;` — Tries to reset the decoder to a clean start state. If this fails and 'false' is returned the decoder must be destroyed and a new instance created.
- L247 _public prototype_ `virtual EDecoderError DecodeAccessUnit(const FInputAccessUnit& InInputAccessUnit, const TMap<FString, FVariant>& InAdditionalOptions) = 0;` — Decodes one access unit. The data sent for decoding must form one complete decodable unit. Partial data is not permitted. You are not required to retain the access unit. The decoder will copy the data internally if required. Not every call will result in a new decoded output. It is possible that several input access units are required before an output will be made available, even with complete decodable units being provided. The return value indicates the following: - None : No error, the access unit was accepted successfully. - EndOfData : SendEndOfData() was called to drain the decoder to produce output for every access unit that was delivered. All pending output must be retrieved before sending a new access unit. - NoBuffer : The decoder can not accept new input at the moment unless pending output has been retrieved. If there is no pending output this indicates some abnormal condition and the decoder should be destroyed. - Error : An error has occurred. Get the details by calling GetError(). The decoder will need to be destroyed and recreated.
- L263 _public prototype_ `virtual EDecoderError SendEndOfData() = 0;` — Sends an end-of-data notification to have the decoder process all pending input and generate as much output as possible. All output must be retrieved by calling HaveOutput() and GetOutput() in sequence. Once all output has been retrieved new data can be provided to the decoder. The return value indicates the following: - None : No error, the call was successful. - EndOfData : This is returned when SendEndOfData() is called more than once while the decoder is already processing the remaining input. - NoBuffer : This value is not returned by this method. - Error : An error has occurred. Get the details by calling GetError(). The decoder will need to be destroyed and recreated.
- L276 _public prototype_ `virtual EDecoderError Flush() = 0;` — Flushes the decoder to discard any pending input. No output will be generated. New data can be provided to the decoder immediately. The return value indicates the following: - None : No error, the call was successful. - EndOfData : This value is not returned by this method. - NoBuffer : This value is not returned by this method. - Error : An error has occurred. Get the details by calling GetError(). The decoder will need to be destroyed and recreated.
- L297 _public prototype_ `virtual EOutputStatus HaveOutput() = 0;` — Checks for available decoded output. Calling DecodeAccessUnit() may not produce any output at that moment. You need to check if output is available by calling this method. If new output is available it can be retrieved calling GetOutput(). After a call to SendEndOfData() you need to call this method to perform decoding of any pending input. The return value indicates the following: - Available : New output is available. It must be retrieved by calling GetOutput() - NeedInput : There is no output available. More data must be provided to the decoder through DecodeAccessUnit() or pending input be completed by calling SendEndOfData(). - EndOfData : Indicates the last output had been returned after a call to SendEndOfData(). This return value is returned only once. The next call will return NeedInput. - Error : An error has occurred. Get the details by calling GetError(). The decoder will need to be destroyed and recreated.
- L311 _public prototype_ `virtual TSharedPtr<IElectraDecoderOutput, ESPMode::ThreadSafe> GetOutput() = 0;` — Returns the next pending output. This call should be preceded by a call to HaveOutput() to check if output is available. Calling without checking first will return a nullptr when no output is available. NOTE: Ownership of the decoded output stays with the decoder. You may hold on to the returned pointer but it is recommended the output is processed immediately. If the output is not returned to the decoder (by resetting the pointer) it may be possible for the decoder to be unable to produce additional output.
- L317 _public prototype_ `virtual TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> CreateBitstreamProcessor() = 0;` — Creates a processor to pre-parse the decoder input bitstream.
- L319 _public prototype_ `virtual void Suspend() = 0;`
- L320 _public prototype_ `virtual void Resume() = 0;`

#### enum `IElectraDecoder::EDecoderError`  
`enum class EDecoderError`  
_L120-132_
- L123 _public enumerator_ `None` — No error, all is well.
- L125 _public enumerator_ `EndOfData`
- L127 _public enumerator_ `NoBuffer` — No buffer available when sending access unit to decode or no output available yet (more input required)
- L129 _public enumerator_ `LostDecoder` — The decoder was lost due to resource sharing conflicts or when the application was suspended.
- L131 _public enumerator_ `Error` — An internal decoder error occurred. Call GetError() to get the error code.

#### enum `IElectraDecoder::EOutputStatus`  
`enum class EOutputStatus`  
_L134-146_
- L137 _public enumerator_ `Available` — Output is available.
- L139 _public enumerator_ `NeedInput` — Output is not available. Provide more input.
- L141 _public enumerator_ `TryAgainLater` — Output is not available right now. New input is not required, call HaveOutput() again.
- L143 _public enumerator_ `EndOfData` — All output has been provided.
- L145 _public enumerator_ `Error` — An internal decoder error occurred. Call GetError() to get the error code.

#### enum `IElectraDecoder::ECSDCompatibility`  
`enum class ECSDCompatibility`  
_L148-156_
- L151 _public enumerator_ `Compatible` — Current decoder configuration is fully capable to continue decoding with the new configuration.
- L153 _public enumerator_ `Drain` — The decoder must be drained before it can continue with the new configuration.
- L155 _public enumerator_ `DrainAndReset` — The decoder must be drained and then ResetToCleanStart() before it can continue with the new configuration.

#### struct `IElectraDecoder::FError`  
`struct FError`  
_L158-179_
- L160 _public function_ `bool IsSet() const`
- L162 _public function_ `const FString& GetMessage() const`
- L164 _public function_ `int32 GetCode() const`
- L166 _public function_ `uint32 GetSdkCode() const`
- L169 _public function_ `FError& SetMessage(const FString& InMessage)`
- L171 _public function_ `FError& SetCode(int32 InCode)`
- L173 _public function_ `FError& SetSdkCode(uint32 InSdkCode)`
- L176 _public member_ `FString Message;`
- L177 _public member_ `int32 Code = 0;`
- L178 _public member_ `uint32 SdkCode = 0;`

#### enum `IElectraDecoder::EType`  
`enum class EType`  
_L181-187_
- L183 _public enumerator_ `None`
- L184 _public enumerator_ `Video`
- L185 _public enumerator_ `Audio`
- L186 _public enumerator_ `Subtitle`

#### Free symbols / members of external scopes

- L43 _prototype_ `ENUM_CLASS_FLAGS(EElectraDecoderFlags);`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IElectraDecoderFeaturesAndOptions.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace IElectraDecoderFeature`
- L19 _variable_ `const TCHAR* const MinimumNumberOfOutputFrames = TEXT("min` (scope `IElectraDecoderFeature`) — FVariant(int32) Indicates the minimum number of decoded frames the application must be able to take from the decoder.
- L36 _variable_ `const TCHAR* const IsAdaptive = TEXT("is_` (scope `IElectraDecoderFeature`) — FVariant(bool) : true - adaptive decoding supported, false - not supported Indicates whether or not the decoder is adaptive on input format changes, like different resolutions for video decoders. If the decoder is not adaptive then you need to perform end-of-stream handling like so: SendEndOfData();		// indicate no further data will be sent while(HaveOutput() == Available) { GetOutput(); } Reset();
- L46 _variable_ `const TCHAR* const SupportsDroppingOutput = TEXT("sup` (scope `IElectraDecoderFeature`) — FVariant(bool) : true - adaptive decoding supported, false - not supported Indicates if the decoder supports dropping output frames that we do not want to display. Such frames still need to be decoded to update the internal decoder state but the output is not needed and can already be discarded on the decoder level instead of being converted and passed up the pipeline where it will then be discarded.
- L65 _variable_ `const TCHAR* const StartcodeToLength = TEXT("sta` (scope `IElectraDecoderFeature`) — FVariant(int32) Value to add to the length of the decoding unit. Usually 4 to include the 32 bit length value replacing the start code in the length. If the start code is NOT to be replaced with the length then this element must NOT be returned as feature. A value of 0 still indicates replacement! Indicates that the decoder wants format specific start codes in the input to be replaced with the length of the decoding unit. This is primarily for video decoders of the H.264 and H.265 family that use a 32 bit value of 0x00000001 to separate individual decoding units in a single input access unit. Some decoders want this value to be the length of the following decoding unit. The byte order is the same as the startcode, which is almost always big endian.
- L75 _variable_ `const TCHAR* const ModifiesInputAUInPlace = TEXT("mod` (scope `IElectraDecoderFeature`) — FVariant(bool) true - input data gets modified in place false - input data remains unchanged If the input access unit is modified in place this should be set to true to have the higher up decoder layer create a copy of the data if necessary.
- L90 _variable_ `const TCHAR* const DecodeTimeOffset = TEXT("dec` (scope `IElectraDecoderFeature`) — FVariant(FTimespan) Time offset with which to feed decoder input earlier than indicated by the decode timestamp. This if typically used only by subtitle decoders that want an access unit to be fed only just in time. Such access units are sparse and should potentially not be fed ahead of time. The presence of this feature indicates the decoder wants to be provided with a new access unit only just in time with this value indicating how much earlier it wants it. Absence of this feature indicates no preference.
- L101 _variable_ `const TCHAR* const NeedsMediaLocalTime = TEXT("nee` (scope `IElectraDecoderFeature`) — FVariant(bool) : true - media local time needed in decode options, false - not needed The decoder may need to media local time in addition to the absolute decoding time. This is primarily used for subtitle decoders in multiperiod content in which the subtitle timing starts at zero for each period. If local time is required it must be passed as an additional option to DecodeAccessUnit() (see IElectraDecoderOption::MediaLocalTime)
- L110 _variable_ `const TCHAR* const MustBeSuspendedInBackground = TEXT("mus` (scope `IElectraDecoderFeature`) — FVariant(bool) : true - the decoder must not be used during application background, false - not needed This tends to be more of a per-platform setting than a per-decoder-instance one, but it is more flexible to do it this way.
- L125 _variable_ `const TCHAR* const NeedReplayDataOnDecoderLoss = TEXT("nee` (scope `IElectraDecoderFeature`) — FVariant(bool) : true - the decoder may get lost and if it does it needs to be fed previous samples If the decoder is lost and a new internal instance replaces it, the new instance needs to be provided with previous samples starting with the most recent keyframe. This flag indicates that you need to hold on to those samples for this eventuality. When you then provide those samples again you need to indicate this by setting the `IsReplaySample` flag on all replay samples and additionally `IsLastReplaySample` on the last replay sample before returning to normal decoding. This allows the decoder to perform decoding optimizations if possible. NOTE: The decoder must not provide decoded output for these samples!
- L136 _namespace_ `namespace IElectraDecoderOption`
- L144 _variable_ `const TCHAR* const MediaLocalTime = TEXT("med` (scope `IElectraDecoderOption`) — FVariant(FTimespan) Local time of the media corresponding to the absolute decoding time. See IElectraDecoderFeature::NeedsMediaLocalTime.
- L151 _variable_ `const TCHAR* const PresentationTimeOffset = TEXT("pre` (scope `IElectraDecoderOption`) — FVariant(FTimespan)
- L158 _variable_ `const TCHAR* const SideloadedID = TEXT("sid` (scope `IElectraDecoderOption`) — FVariant(String)
- L163 _variable_ `const TCHAR* const CodecSpecificData = TEXT("csd` (scope `IElectraDecoderOption`) — FVariant(ByteArray)
- L169 _variable_ `const TCHAR* const DecoderConfigurationRecord = TEXT("dcr` (scope `IElectraDecoderOption`) — FVariant(ByteArray)
- L177 _namespace_ `namespace IElectraDecoderFormatInfo`
- L186 _variable_ `const TCHAR* const IsEveryFrameKeyframe = TEXT("is_` (scope `IElectraDecoderFormatInfo`) — FVariant(bool) : true - The format uses only keyframes. Indicates that this format encodes every frame as a keyframe and no delta frames. This is used with video decoders only. Audio is assumed to be keyframe-only. The absence of this on a video decoder or a value of 'false' implies that delta frames are used.
- L193 _variable_ `const TCHAR* const HumanReadableFormatName = TEXT("hum` (scope `IElectraDecoderFormatInfo`) — FVariant(String) A human readable string of the format to be decoded.
- L201 _namespace_ `namespace IElectraDecoderBitstreamProcessorInfo`
- L208 _variable_ `const TCHAR* const NumBitsLuma = TEXT("num` (scope `IElectraDecoderBitstreamProcessorInfo`) — FVariant(uint8) Number of luminance bits.
- L215 _variable_ `const TCHAR* const CommonColorimetry = TEXT("com` (scope `IElectraDecoderBitstreamProcessorInfo`) — FVariant(FCommonColorimetry) Colorimetry information in standard MPEG definition.
- L222 _variable_ `const TCHAR* const CommonPictureTiming = TEXT("com` (scope `IElectraDecoderBitstreamProcessorInfo`) — FVariant(FCommonPictureTiming) Timing from a bitstream SEI message.
- L229 _variable_ `const TCHAR* const SeiMasteringDisplayColorVolume = TEXT("sei` (scope `IElectraDecoderBitstreamProcessorInfo`) — FVariant(FSEImastering_display_colour_volume) Mastering display colour volume from bitstream SEI message
- L236 _variable_ `const TCHAR* const SeiContentLightLeveInfo = TEXT("sei` (scope `IElectraDecoderBitstreamProcessorInfo`) — FVariant(FSEIcontent_light_level_info) Content light level info from bitstream SEI message
- L243 _variable_ `const TCHAR* const SeiAlternateTransferCharacteristics = TEXT("sei` (scope `IElectraDecoderBitstreamProcessorInfo`) — FVariant(FSEIalternative_transfer_characteristics) Alternate transfer characterisctics from bitstream SEI message

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IElectraDecoderOutputAudio.h` (Public)


#### class `IElectraDecoderAudioOutput`  
`class IElectraDecoderAudioOutput : public IElectraDecoderOutput`  
_L7-97_
- inherits: `IElectraDecoderOutput`
- L10 _public prototype_ `virtual ~IElectraDecoderAudioOutput() = default;`
- L11 _public function_ `EType GetType() const override`
- L40 _public prototype_ `virtual int32 GetNumChannels() const = 0;` — Returns the number of decoded channels.
- L46 _public prototype_ `virtual int32 GetSampleRate() const = 0;` — Returns the decoded sampling rate. This may be different from what was known about the input.
- L51 _public prototype_ `virtual int32 GetNumFrames() const = 0;` — Returns the number of decoded samples per channel.
- L59 _public prototype_ `virtual bool IsInterleaved() const = 0;` — If samples are interleaved they appear in memory alternatingly per channel. Eg. L,R,L,R,L,R,... If they are not interleaved there will be separate buffers containing samples of a single channel each.
- L67 _public prototype_ `virtual EChannelPosition GetChannelPosition(int32 InChannelNumber) const = 0;` — Returns the position of the decoded channel. If a position is not inferred or described by the format it is set to `Undefined`. If a channel failed to decode it may be included as `Disabled` with the sample data set to silence.
- L73 _public prototype_ `virtual ESampleFormat GetSampleFormat() const = 0;` — Returns the format of the decoded samples. The data pointers shall be cast to the appropriate type.
- L80 _public prototype_ `virtual int32 GetBytesPerSample() const = 0;` — Returns the number of bytes per decoded sample. This typically corresponds to the size of the decoded format, ie 2 for Int16 and 4 for Float.
- L88 _public prototype_ `virtual int32 GetBytesPerFrame() const = 0;` — Returns the number of bytes per decoded frame. For channel interleaved data this is typically GetNumChannels() * GetBytesPerSample() while per-channel data typically returns the same as GetBytesPerSample()
- L96 _public prototype_ `virtual const void* GetData(int32 InChannelNumber) const = 0;` — Returns a pointer to the start of the decoded data for the specified channel. This can be used for interleaved data as well although you would normally ask for the data pointer of channel 0 to get the base address of the interleaved data.

#### enum `IElectraDecoderAudioOutput::EChannelPosition`  
`enum class EChannelPosition`  
_L17-29_
- desc: Channel position as per ISO/IEC 23001-8 Table 7.
- L19 _public enumerator_ `Invalid = -1`
- L20 _public enumerator_ `L=0`
- L20 _public enumerator_ `L=0`
- L20 _public enumerator_ `L=0`
- L20 _public enumerator_ `L=0`
- L20 _public enumerator_ `L=0`
- L20 _public enumerator_ `L=0`
- L20 _public enumerator_ `L=0`
- L20 _public enumerator_ `L=0`
- L21 _public enumerator_ `Lsr`
- L21 _public enumerator_ `Lsr`
- L21 _public enumerator_ `Lsr`
- L21 _public enumerator_ `Lsr`
- L21 _public enumerator_ `Lsr`
- L21 _public enumerator_ `Lsr`
- L21 _public enumerator_ `Lsr`
- L21 _public enumerator_ `Lsr`
- L22 _public enumerator_ `Rw`
- L22 _public enumerator_ `Rw`
- L22 _public enumerator_ `Rw`
- L22 _public enumerator_ `Rw`
- L22 _public enumerator_ `Rw`
- L22 _public enumerator_ `Rw`
- L22 _public enumerator_ `Rw`
- L22 _public enumerator_ `Rw`
- L23 _public enumerator_ `Rvss`
- L23 _public enumerator_ `Rvss`
- L23 _public enumerator_ `Rvss`
- L23 _public enumerator_ `Rvss`
- L23 _public enumerator_ `Rvss`
- L23 _public enumerator_ `Rvss`
- L23 _public enumerator_ `Rvss`
- L23 _public enumerator_ `Rvss`
- L24 _public enumerator_ `Undefined = 128`
- L25 _public enumerator_ `Disabled = 255`
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L27 _public enumerator_ `Unspec0 = 256` — No specified position.
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`
- L28 _public enumerator_ `Unspec16`

#### enum `IElectraDecoderAudioOutput::ESampleFormat`  
`enum class ESampleFormat`  
_L31-35_
- L33 _public enumerator_ `Int16`
- L34 _public enumerator_ `Float`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IElectraDecoderOutputVideo.h` (Public)


#### enum `EElectraDecoderPlatformOutputHandleType`  
`enum class EElectraDecoderPlatformOutputHandleType`  
_L13-15_

#### struct `FElectraVideoDecoderOutputCropValues`  
`struct FElectraVideoDecoderOutputCropValues`  
_L20-33_
- L23 _public member_ `int32 Top = 0;` — Number of rows at the top that must not be displayed.
- L26 _public member_ `int32 Left = 0;` — Number of columns at the left that must not be displayed.
- L29 _public member_ `int32 Bottom = 0;` — Number of rows at the bottom that must not be displayed.
- L32 _public member_ `int32 Right = 0;` — Number of columns at the right that must not be displayed.

#### class `IElectraDecoderVideoOutput`  
`class IElectraDecoderVideoOutput : public IElectraDecoderOutput`  
_L38-159_
- inherits: `IElectraDecoderOutput`
- L41 _public prototype_ `virtual ~IElectraDecoderVideoOutput() = default;`
- L42 _public function_ `EType GetType() const override`
- L63 _public prototype_ `virtual EOutputType GetOutputType() const = 0;` — Returns the state of this output. Depending on the input bitstream the decoder might not have been able to produce a valid output or it may be partially corrupted. If the output should not be used for display `DoNotOutput` is returned.
- L70 _public prototype_ `virtual int32 GetWidth() const = 0;` — Returns the active number of horizontal pixels. This has potential cropping values applied and does not include any pitch requirements.
- L77 _public prototype_ `virtual int32 GetHeight() const = 0;` — Returns the active number of vertical pixels. This has potential cropping values applied and does not include any pitch requirements.
- L87 _public prototype_ `virtual int32 GetDecodedWidth() const = 0;` — Returns the number of decoded horizontal pixels. This value may be different from GetWidth() since it does not take any cropping values into account. Note that this represents the actual dimension of the data returned, which may differ from GetWidth() + cropping offsets! (e.g. if the data is returned as RGBA pixels, but represents a YUYV 4:2:2 format)
- L97 _public prototype_ `virtual int32 GetDecodedHeight() const = 0;` — Returns the number of decoded vertical pixels. This value may be greater than GetHeight() since it does not take any cropping values into account. Note that this represents the actual dimension of the data returned, which may differ from GetWidth() + cropping offsets! (e.g. if the data is returned as RGBA pixels, but represents a YUYV 4:2:2 format)
- L104 _public prototype_ `virtual FElectraVideoDecoderOutputCropValues GetCropValues() const = 0;` — Returns the cropping values. This is useful in combination with GetDecodedWidth() and GetDecodedHeight() that give you the number of pixels created by the decoder.
- L109 _public prototype_ `virtual int32 GetAspectRatioW() const = 0;` — Returns the aspect ratio w value.
- L114 _public prototype_ `virtual int32 GetAspectRatioH() const = 0;` — Returns the aspect ratio h value.
- L120 _public prototype_ `virtual int32 GetFrameRateNumerator() const = 0;` — Returns the numerator of the frame rate, if known. If unknown this returns 0.
- L126 _public prototype_ `virtual int32 GetFrameRateDenominator() const = 0;` — Returns the denominator of the frame rate, if known. If unknown this returns 0.
- L131 _public prototype_ `virtual int32 GetNumberOfBits() const = 0;` — Returns the number of bits. Usually 8, 10, or 12.
- L137 _public prototype_ `virtual void GetExtraValues(TMap<FString, FVariant>& OutExtraValues) const = 0;` — Returns additional values specific to the decoder and format that are used in handling this output in a platform specific way.
- L143 _public prototype_ `virtual void* GetPlatformOutputHandle(EElectraDecoderPlatformOutputHandleType InTypeOfHandle) const = 0;` — Returns the platform specific decoder output handle, if any. This value is specific to the decoder being used.
- L158 _public prototype_ `virtual EImageCopyResult CopyPlatformImage(IElectraDecoderVideoOutputCopyResources* InCopyResources) const = 0;` — Asks to create a copy of the image into a platform specific structure. Parameters for the operation are provided by a platform specific implementation of IElectraDecoderVideoOutputCopyResources provided to this method through which relevant parameters (eg. a device or texture handle, etc.) can be obtained.

#### enum `IElectraDecoderVideoOutput::EOutputType`  
`enum class EOutputType`  
_L47-55_
- L50 _public enumerator_ `Output` — Output this output.
- L54 _public enumerator_ `DoNotOutput` — Do not output this. Either the decoder did not produce an actual output for the given input, or the output has decoding errors that makes it unusable.

#### enum `IElectraDecoderVideoOutput::EImageCopyResult`  
`enum class EImageCopyResult`  
_L145-150_
- L147 _public enumerator_ `Succeeded`
- L148 _public enumerator_ `Failed`
- L149 _public enumerator_ `NotSupported`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IElectraDecodersModule.h` (Public)


#### class `IElectraDecodersModule`  
`class IElectraDecodersModule : public IModuleInterface`  
_L14-20_
- inherits: `IModuleInterface`
- desc: Interface for the `ElectraDecodersModule` module.
- L17 _public prototype_ `virtual ~IElectraDecodersModule() = default;`
- L19 _public prototype_ `virtual void RegisterDecodersWithCodecFactory(IElectraCodecRegistry* InCodecFactoryToRegisterWith) = 0;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IOS/IOSElectraDecoderPlatformOutputHandleTypes.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/IOS/IOSElectraDecodersPlatformResources.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Linux/LinuxElectraDecoderPlatformOutputHandleTypes.h` (Public)


#### enum `EElectraDecoderPlatformOutputHandleType`  
`enum class EElectraDecoderPlatformOutputHandleType`  
_L9-13_
- L11 _public enumerator_ `LibavDecoderDecodedImage` — Get POD pointer to a ILibavDecoderDecodedImage
- L12 _public enumerator_ `ImageBuffers` — IElectraDecoderVideoOutputImageBuffers interface

#### class `FElectraDecoderOutputSync`  
`class FElectraDecoderOutputSync final`  
_L16-21_
- L19 _public prototype_ `FElectraDecoderOutputSync() = default;`
- L20 _public prototype_ `~FElectraDecoderOutputSync() = default;`

#### class `IElectraDecoderVideoOutputImageBuffers`  
`class IElectraDecoderVideoOutputImageBuffers`  
_L23-49_
- L27 _public prototype_ `virtual uint32 GetCodec4CC() const = 0;` — Return the 4cc of the codec.
- L30 _public prototype_ `virtual int32 GetNumberOfBuffers() const = 0;` — Returns the number of separate image buffers making up the frame.
- L33 _public prototype_ `virtual TSharedPtr<TArray64<uint8>, ESPMode::ThreadSafe> GetBufferDataByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer as CPU data buffer.
- L36 _public prototype_ `virtual void* GetBufferTextureByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer as GPU texture resource.
- L39 _public prototype_ `virtual bool GetBufferTextureSyncByIndex(int32 InBufferIndex, FElectraDecoderOutputSync& SyncObject) const = 0;` — Returns the n'th image buffer's GPU sync object to signal texture data as being ready to be read
- L42 _public prototype_ `virtual EPixelFormat GetBufferFormatByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer format
- L45 _public prototype_ `virtual EElectraTextureSamplePixelEncoding GetBufferEncodingByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer encoding
- L48 _public prototype_ `virtual int32 GetBufferPitchByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer pitch

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Linux/LinuxElectraDecodersPlatformResources.h` (Public)


#### class `FElectraDecodersPlatformResourcesLinux`  
`class FElectraDecodersPlatformResourcesLinux`  
_L12-20_
- L16 _public prototype_ `static IDecoderPlatformResource* CreatePlatformVideoResource(void* InOwnerHandle, const TMap<FString, FVariant> InOptions);`
- L17 _public prototype_ `static void ReleasePlatformVideoResource(void* InOwnerHandle, IDecoderPlatformResource* InHandleToRelease);`
- L19 _public prototype_ `static bool SetupOutputTextureSample(FString& OutErrorMessage, TSharedPtr<FElectraTextureSample, ESPMode::ThreadSafe> InOutTextureSampleToSetup, TSharedPtr<IElectraDecoderVideoOutput, ESPMode::ThreadSafe> InDecoderOutput, TSharedPtr<Electra::FParamDict, ESPMode::ThreadSafe> InOutBufferPropertes, IDecoderPlatformResource* InPlatformResource);`

#### Free symbols / members of external scopes

- L22 _typedef_ `using FElectraDecodersPlatformResources = FElectraDecodersPlatformResourcesLinux;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Mac/MacElectraDecoderPlatformOutputHandleTypes.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Mac/MacElectraDecodersPlatformResources.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/TVOS/TVOSElectraDecoderPlatformOutputHandleTypes.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/TVOS/TVOSElectraDecodersPlatformResources.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Unix/UnixElectraDecoderPlatformOutputHandleTypes.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Unix/UnixElectraDecodersPlatformResources.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/AOMedia/ElectraBitstreamProcessor_AV1.h` (Public)


#### class `FElectraDecoderBitstreamProcessorAV1`  
`class FElectraDecoderBitstreamProcessorAV1 : public IElectraDecoderBitstreamProcessor`  
_L8-25_
- inherits: `IElectraDecoderBitstreamProcessor`
- L11 _public function_ `static TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> Create(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams)`
- L14 _public prototype_ `virtual ~FElectraDecoderBitstreamProcessorAV1();`
- L15 _public prototype_ `bool WillModifyBitstreamInPlace() override;`
- L16 _public prototype_ `void Clear() override;`
- L17 _public prototype_ `EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) override;`
- L18 _public prototype_ `void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) override;`
- L19 _public prototype_ `FString GetLastError() override;`
- L22 _private prototype_ `FElectraDecoderBitstreamProcessorAV1(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams);`
- L24 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/AOMedia/ElectraUtilsAV1Video.h` (Public)


#### class `ElectraDecodersUtil::AV1Video::FAV1CodecConfigurationRecord`  
`class FAV1CodecConfigurationRecord`  
_L19-77_
- desc: AV1 Codec ISO Media File Format Binding see: https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-syntax
- L34 _public prototype_ `bool Parse(const TConstArrayView<uint8>& InDCR);`
- L36 _public function_ `inline const TArray<uint8>& GetRawData() const`
- L38 _public function_ `inline const TArray<uint8>& GetCodecSpecificData() const`
- L41 _public function_ `inline uint8 GetProfile() const`
- L43 _public function_ `inline uint8 GetLevel() const`
- L45 _public function_ `inline uint8 GetTier() const`
- L47 _public function_ `inline uint8 GetBitDepth() const`
- L50 _public function_ `inline const FColorInfo& GetColorInfo() const`
- L53 _public function_ `inline FString GetCodecSpecifierRFC6381() const`
- L64 _public prototype_ `FString GetFormatInfo();`
- L66 _public prototype_ `static FString GetFormatInfo(uint32 InProfile, uint32 InLevel);`
- L68 _private member_ `TArray<uint8> RawData;`
- L69 _private member_ `TArray<uint8> CSD;`
- L70 _private member_ `FColorInfo ColorInfo;`
- L71 _private member_ `uint8 Profile = 0;`
- L72 _private member_ `uint8 Level = 0;`
- L73 _private member_ `uint8 Tier = 0;`
- L74 _private member_ `uint8 BitDepth = 0;`
- L75 _private member_ `uint8 initial_presentation_delay_present = 0;`
- L76 _private member_ `uint8 initial_presentation_delay_minus_one = 0;`

#### struct `ElectraDecodersUtil::AV1Video::FAV1CodecConfigurationRecord::FColorInfo`  
`struct FColorInfo`  
_L22-32_
- L24 _public member_ `uint8 monochrome = 0;`
- L25 _public member_ `uint8 chromaSubsamplingX = 1;`
- L26 _public member_ `uint8 chromaSubsamplingY = 1;`
- L27 _public member_ `uint8 chromaSamplingPosition = 0;`
- L28 _public member_ `uint8 colorPrimaries = 1;`
- L29 _public member_ `uint8 transferCharacteristics = 1;`
- L30 _public member_ `uint8 matrixCoefficients = 1;`
- L31 _public member_ `uint8 videoFullRangeFlag = 0;`

#### class `ElectraDecodersUtil::AV1Video::FBitstreamReaderAV1`  
`class FBitstreamReaderAV1 : public Electra::FBitstreamReader`  
_L81-135_
- inherits: `Electra::FBitstreamReader`
- L84 _public prototype_ `FBitstreamReaderAV1() = default;`
- L85 _public function_ `FBitstreamReaderAV1(const uint8* InData, uint64 InDataSize) : Electra::FBitstreamReader(InData, InDataSize)`
- L89 _public function_ `uint32 uvlc()`
- L103 _public function_ `uint8 GetByte()`
- L109 _public function_ `uint32 leb128(uint32& OutNumBytesRead)`
- L130 _public function_ `uint32 leb128()`

#### enum `ElectraDecodersUtil::AV1Video::EOBUType`  
`enum class EOBUType`  
_L138-151_
- L140 _public enumerator_ `Reserved0 = 0`
- L141 _public enumerator_ `OBU_SEQUENCE_HEADER`
- L142 _public enumerator_ `OBU_TEMPORAL_DELIMITER`
- L143 _public enumerator_ `OBU_FRAME_HEADER`
- L144 _public enumerator_ `OBU_TILE_GROUP`
- L145 _public enumerator_ `OBU_METADATA`
- L146 _public enumerator_ `OBU_FRAME`
- L147 _public enumerator_ `OBU_REDUNDANT_FRAME_HEADER`
- L148 _public enumerator_ `OBU_TILE_LIST`
- L149 _public enumerator_ `Reserved9 = 9`
- L150 _public enumerator_ `OBU_PADDING = 15`

#### enum `ElectraDecodersUtil::AV1Video::EMetadataType`  
`enum class EMetadataType`  
_L153-163_
- L155 _public enumerator_ `Reserved0 = 0`
- L156 _public enumerator_ `METADATA_TYPE_HDR_CLL`
- L157 _public enumerator_ `METADATA_TYPE_HDR_MDCV`
- L158 _public enumerator_ `METADATA_TYPE_SCALABILITY`
- L159 _public enumerator_ `METADATA_TYPE_ITUT_T35`
- L160 _public enumerator_ `METADATA_TYPE_TIMECODE`
- L161 _public enumerator_ `UnregisteredUserPrivate6 = 6`
- L162 _public enumerator_ `Reserved32 = 32`

#### enum `ElectraDecodersUtil::AV1Video::EColorPrimaries`  
`enum class EColorPrimaries : uint8`  
_L165-180_
- L167 _public enumerator_ `Undefined = 0`
- L168 _public enumerator_ `CP_BT_709 = 1`
- L169 _public enumerator_ `CP_UNSPECIFIED = 2`
- L170 _public enumerator_ `CP_BT_470_M = 4`
- L171 _public enumerator_ `CP_BT_470_B_G`
- L172 _public enumerator_ `CP_BT_601`
- L173 _public enumerator_ `CP_SMPTE_240`
- L174 _public enumerator_ `CP_GENERIC_FILM`
- L175 _public enumerator_ `CP_BT_2020`
- L176 _public enumerator_ `CP_XYZ`
- L177 _public enumerator_ `CP_SMPTE_431`
- L178 _public enumerator_ `CP_SMPTE_432`
- L179 _public enumerator_ `CP_EBU_3213 = 22`

#### enum `ElectraDecodersUtil::AV1Video::ETransferCharacteristics`  
`enum class ETransferCharacteristics : uint8`  
_L182-203_
- L184 _public enumerator_ `TC_RESERVED_0 = 0`
- L185 _public enumerator_ `TC_BT_709`
- L186 _public enumerator_ `TC_UNSPECIFIED`
- L187 _public enumerator_ `TC_RESERVED_3`
- L188 _public enumerator_ `TC_BT_470_M`
- L189 _public enumerator_ `TC_BT_470_B_G`
- L190 _public enumerator_ `TC_BT_601`
- L191 _public enumerator_ `TC_SMPTE_240`
- L192 _public enumerator_ `TC_LINEAR`
- L193 _public enumerator_ `TC_LOG_100`
- L194 _public enumerator_ `TC_LOG_100_SQRT10`
- L195 _public enumerator_ `TC_IEC_61966`
- L196 _public enumerator_ `TC_BT_1361`
- L197 _public enumerator_ `TC_SRGB`
- L198 _public enumerator_ `TC_BT_2020_10_BIT`
- L199 _public enumerator_ `TC_BT_2020_12_BIT`
- L200 _public enumerator_ `TC_SMPTE_2084`
- L201 _public enumerator_ `TC_SMPTE_428`
- L202 _public enumerator_ `TC_HLG`

#### enum `ElectraDecodersUtil::AV1Video::EMatrixCoefficients`  
`enum class EMatrixCoefficients : uint8`  
_L205-222_
- L207 _public enumerator_ `MC_IDENTITY = 0`
- L208 _public enumerator_ `MC_BT_709`
- L209 _public enumerator_ `MC_UNSPECIFIED`
- L210 _public enumerator_ `MC_RESERVED_3`
- L211 _public enumerator_ `MC_FCC`
- L212 _public enumerator_ `MC_BT_470_B_G`
- L213 _public enumerator_ `MC_BT_601`
- L214 _public enumerator_ `MC_SMPTE_240`
- L215 _public enumerator_ `MC_SMPTE_YCGCO`
- L216 _public enumerator_ `MC_BT_2020_NCL`
- L217 _public enumerator_ `MC_BT_2020_CL`
- L218 _public enumerator_ `MC_SMPTE_2085`
- L219 _public enumerator_ `MC_CHROMAT_NCL`
- L220 _public enumerator_ `MC_CHROMAT_CL`
- L221 _public enumerator_ `MC_ICTCP`

#### enum `ElectraDecodersUtil::AV1Video::EChromaSamplePosition`  
`enum class EChromaSamplePosition : uint8`  
_L224-230_
- L226 _public enumerator_ `CSP_UNKNOWN = 0`
- L227 _public enumerator_ `CSP_VERTICAL`
- L228 _public enumerator_ `CSP_COLOCATED`
- L229 _public enumerator_ `CSP_RESERVED`

#### struct `ElectraDecodersUtil::AV1Video::FMetadata_hdr_cll`  
`struct FMetadata_hdr_cll`  
_L232-237_
- L234 _public member_ `uint16 max_cll = 0;`
- L235 _public member_ `uint16 max_fall = 0;`
- L236 _public prototype_ `bool ParseFrom(FBitstreamReaderAV1& InReader);`

#### struct `ElectraDecodersUtil::AV1Video::FMetadata_hdr_mdvc`  
`struct FMetadata_hdr_mdvc`  
_L239-248_
- L241 _public member_ `uint16 primary_chromaticity_x[3] { 0 };` — CIE 1931; 0=red, 1=green, 2=blue
- L242 _public member_ `uint16 primary_chromaticity_y[3] { 0 };`
- L243 _public member_ `uint16 white_point_chromaticity_x = 0;`
- L244 _public member_ `uint16 white_point_chromaticity_y = 0;`
- L245 _public member_ `uint32 luminance_max = 0;` — a 24.8 fixed-point maximum luminance, represented in candelas per square meter
- L246 _public member_ `uint32 luminance_min = 0;` — a 18.14 fixed-point minimum luminance, represented in candelas per square meter
- L247 _public prototype_ `bool ParseFrom(FBitstreamReaderAV1& InReader);`

#### struct `ElectraDecodersUtil::AV1Video::FSequenceHeader`  
`struct FSequenceHeader`  
_L251-345_
- L253 _public member_ `uint8 seq_profile = 0;`
- L254 _public member_ `uint8 still_picture = 0;`
- L255 _public member_ `uint8 reduced_still_picture_header = 0;`
- L256 _public member_ `uint8 timing_info_present_flag = 0;`
- L264 _public member_ `FTimingInfo timing_info;`
- L266 _public member_ `uint8 decoder_model_info_present_flag = 0;`
- L274 _public member_ `FDecoderModelInfo decoder_model_info;`
- L276 _public member_ `uint8 initial_display_delay_present_flag = 0;`
- L277 _public member_ `uint8 operating_points_cnt_minus_1 = 0;`
- L288 _public member_ `FOperatingPoint operating_points[32];`
- L295 _public member_ `FOperatingParametersInfo operating_parameters_info[32];`
- L297 _public member_ `uint8 frame_width_bits_minus_1 = 0;`
- L298 _public member_ `uint8 frame_height_bits_minus_1 = 0;`
- L299 _public member_ `uint32 max_frame_width_minus_1 = 0;`
- L300 _public member_ `uint32 max_frame_height_minus_1 = 0;`
- L301 _public member_ `uint8 frame_id_numbers_present_flag = 0;`
- L302 _public member_ `uint8 delta_frame_id_length_minus_2 = 0;`
- L303 _public member_ `uint8 additional_frame_id_length_minus_1 = 0;`
- L304 _public member_ `uint8 use_128x128_superblock = 0;`
- L305 _public member_ `uint8 enable_filter_intra = 0;`
- L306 _public member_ `uint8 enable_intra_edge_filter = 0;`
- L307 _public member_ `uint8 enable_interintra_compound = 0;`
- L308 _public member_ `uint8 enable_masked_compound = 0;`
- L309 _public member_ `uint8 enable_warped_motion = 0;`
- L310 _public member_ `uint8 enable_dual_filter = 0;`
- L311 _public member_ `uint8 enable_order_hint = 0;`
- L312 _public member_ `uint8 enable_jnt_comp = 0;`
- L313 _public member_ `uint8 enable_ref_frame_mvs = 0;`
- L314 _public member_ `uint8 seq_choose_screen_content_tools = 0;`
- L315 _public member_ `uint8 seq_force_screen_content_tools = 0;`
- L316 _public member_ `uint8 seq_force_integer_mv = 0;`
- L317 _public member_ `uint8 seq_choose_integer_mv = 0;`
- L318 _public member_ `uint8 order_hint_bits_minus_1 = 0;`
- L319 _public member_ `uint8 OrderHintBits = 0;`
- L320 _public member_ `uint8 enable_superres = 0;`
- L321 _public member_ `uint8 enable_cdef = 0;`
- L322 _public member_ `uint8 enable_restoration = 0;`
- L339 _public member_ `FColorConfig color_config;`
- L341 _public member_ `uint8 film_grain_params_present = 0;`
- L344 _public prototype_ `bool ParseFrom(FBitstreamReaderAV1& InReader);`

#### struct `ElectraDecodersUtil::AV1Video::FSequenceHeader::FTimingInfo`  
`struct FTimingInfo`  
_L257-263_
- L259 _public member_ `uint32 num_units_in_display_tick = 0;`
- L260 _public member_ `uint32 time_scale = 0;`
- L261 _public member_ `uint8 equal_picture_interval = 0;`
- L262 _public member_ `uint32 num_ticks_per_picture_minus_1 = 0;`

#### struct `ElectraDecodersUtil::AV1Video::FSequenceHeader::FDecoderModelInfo`  
`struct FDecoderModelInfo`  
_L267-273_
- L269 _public member_ `uint8 buffer_delay_length_minus_1 = 0;`
- L270 _public member_ `uint32 num_units_in_decoding_tick = 0;`
- L271 _public member_ `uint8 buffer_removal_time_length_minus_1 = 0;`
- L272 _public member_ `uint8 frame_presentation_time_length_minus_1 = 0;`

#### struct `ElectraDecodersUtil::AV1Video::FSequenceHeader::FOperatingPoint`  
`struct FOperatingPoint`  
_L279-287_
- L281 _public member_ `uint16 operating_point_idc = 0;`
- L282 _public member_ `uint8 seq_level_idx = 0;`
- L283 _public member_ `uint8 seq_tier = 0;`
- L284 _public member_ `uint8 decoder_model_present_for_this_op = 0;`
- L285 _public member_ `uint8 initial_display_delay_present_for_this_op = 0;`
- L286 _public member_ `uint8 initial_display_delay_minus_1 = 0;`

#### struct `ElectraDecodersUtil::AV1Video::FSequenceHeader::FOperatingParametersInfo`  
`struct FOperatingParametersInfo`  
_L289-294_
- L291 _public member_ `uint32 decoder_buffer_delay = 0;`
- L292 _public member_ `uint32 encoder_buffer_delay = 0;`
- L293 _public member_ `uint8 low_delay_mode_flag = 0;`

#### struct `ElectraDecodersUtil::AV1Video::FSequenceHeader::FColorConfig`  
`struct FColorConfig`  
_L324-338_
- L326 _public member_ `uint8 high_bitdepth = 0;`
- L327 _public member_ `uint8 twelve_bit = 0;`
- L328 _public member_ `uint8 mono_chrome = 0;`
- L329 _public member_ `uint8 color_description_present_flag = 0;`
- L330 _public member_ `EColorPrimaries color_primaries = EColorPrimaries::CP_UNSPECIFIED;`
- L331 _public member_ `ETransferCharacteristics transfer_characteristics = ETransferCharacteristics::TC_UNSPECIFIED;`
- L332 _public member_ `EMatrixCoefficients matrix_coefficients = EMatrixCoefficients::MC_UNSPECIFIED;`
- L333 _public member_ `uint8 color_range = 0;`
- L334 _public member_ `uint8 subsampling_x = 0;`
- L335 _public member_ `uint8 subsampling_y = 0;`
- L336 _public member_ `EChromaSamplePosition chroma_sample_position = EChromaSamplePosition::CSP_UNKNOWN;`
- L337 _public member_ `uint8 separate_uv_delta_q = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ElectraDecodersUtil`
- L11 _namespace_ `namespace AV1Video` (scope `ElectraDecodersUtil`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/AudioChannelMapper.h` (Public)


#### class `Electra::FAudioChannelMapper`  
`class FAudioChannelMapper`  
_L24-80_
- desc: Class to map audio channels from some decoder-specific output order into the order expected by FMediaAudioResampler. Channels that are not supported by UE will be ignored and are silent. No effort to mix them into other channels is made. As fas as media playback is concerned we handle the most common channel layouts only, like mono, stereo, 5.1 and 7.1.
- L43 _public prototype_ `FAudioChannelMapper();`
- L44 _public prototype_ `~FAudioChannelMapper();`
- L47 _public prototype_ `bool Initialize(int32 NumBytesPerSample, uint32 ChannelConfiguration);` — Initializes with an ISO/IEC 23001-8 channel configuration value from Table 7 (compatible with ISO/IEC 14496-3:2009/Amd 4)
- L50 _public prototype_ `bool Initialize(int32 NumBytesPerSample, TArrayView<const FSourceLayout> ChannelPositions);` — Initializes with ISO/IEC 23001-8 channel positions.
- L52 _public prototype_ `bool IsInitialized() const;`
- L54 _public prototype_ `void Reset();`
- L57 _public prototype_ `int32 GetNumTargetChannels() const;` — Gets the number of output channels mapped to the UE internal layout.
- L60 _public prototype_ `void MapChannels(void* OutputBuffer, uint32 OutputBufferSize, const void* InputBuffer, uint32 InputBufferSize, int32 NumSamplesPerChannel) const;` — Maps the supported input channels to the output channels in UE internal layout.
- L62 _public prototype_ `bool Initialize(TSharedPtr<IElectraDecoderAudioOutput, ESPMode::ThreadSafe> InSampleBlock);`
- L72 _private prototype_ `static bool CanBeCopiedDirectly(TArrayView<const FSourceLayout> ChannelPositions);`
- L73 _private prototype_ `bool CanBeCopiedDirectly(TSharedPtr<IElectraDecoderAudioOutput, ESPMode::ThreadSafe> InSampleBlock);`
- L74 _private prototype_ `int32 MatchesResamplerLayout(TArray<FTargetSource>& InputSources);`
- L75 _private prototype_ `void CreateResamplerChannelMapping(int32 ResamplerChannelIndex, const TArray<FTargetSource>& InSources);`
- L77 _private member_ `TArray<FTargetSource> TargetSources;`
- L78 _private member_ `int32 BytesPerSample = 0;`
- L79 _private member_ `bool bCanCopyDirectly = false;`

#### struct `Electra::FAudioChannelMapper::FSourceLayout`  
`struct FSourceLayout`  
_L38-41_
- desc: Channel position as per ISO/IEC 23001-8 Table 7. enum class IElectraDecoderAudioOutput::EChannelPosition { L, R, C, LFE, Ls, Rs, Lc, Rc, Lsr, Rsr, Cs, Lsd, Rsd, Lss, Rss, Lw, Rw, Lv, Rv, Cv, Lvr, Rvr, Cvr, Lvss, Rvss, Ts, LFE2, Lb, Rb, Cb, Lvs, Rvs, Disabled = 255 };
- L40 _public member_ `IElectraDecoderAudioOutput::EChannelPosition ChannelPosition = IElectraDecoderAudioOutput::EChannelPosition::Disabled;`

#### struct `Electra::FAudioChannelMapper::FTargetSource`  
`struct FTargetSource`  
_L65-70_
- L67 _public member_ `IElectraDecoderAudioOutput::EChannelPosition ChannelPosition = IElectraDecoderAudioOutput::EChannelPosition::Disabled;`
- L68 _public member_ `int32 FirstOffset = 0;`
- L69 _public member_ `int32 Stride = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ELECTRADECODERS_API`
- L13 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/ElectraBitstreamProcessorDefault.h` (Public)


#### class `FElectraDecoderBitstreamProcessorDefault`  
`class FElectraDecoderBitstreamProcessorDefault : public IElectraDecoderBitstreamProcessor`  
_L8-25_
- inherits: `IElectraDecoderBitstreamProcessor`
- L11 _public function_ `static TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> Create()`
- L14 _public prototype_ `virtual ~FElectraDecoderBitstreamProcessorDefault();`
- L15 _public prototype_ `bool WillModifyBitstreamInPlace() override;`
- L16 _public prototype_ `void Clear() override;`
- L17 _public prototype_ `EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) override;`
- L18 _public prototype_ `void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) override;`
- L19 _public prototype_ `FString GetLastError() override;`
- L22 _private prototype_ `FElectraDecoderBitstreamProcessorDefault();`
- L24 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/ElectraBitstreamProcessorGenericVideo.h` (Public)


#### class `FElectraDecoderBitstreamProcessorGenericVideo`  
`class FElectraDecoderBitstreamProcessorGenericVideo : public IElectraDecoderBitstreamProcessor`  
_L8-25_
- inherits: `IElectraDecoderBitstreamProcessor`
- L11 _public function_ `static TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> Create(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams)`
- L14 _public prototype_ `virtual ~FElectraDecoderBitstreamProcessorGenericVideo();`
- L15 _public prototype_ `bool WillModifyBitstreamInPlace() override;`
- L16 _public prototype_ `void Clear() override;`
- L17 _public prototype_ `EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) override;`
- L18 _public prototype_ `void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) override;`
- L19 _public prototype_ `FString GetLastError() override;`
- L22 _private prototype_ `FElectraDecoderBitstreamProcessorGenericVideo(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams);`
- L24 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/Google/ElectraBitstreamProcessorVPx.h` (Public)


#### class `FElectraDecoderBitstreamProcessorVPx`  
`class FElectraDecoderBitstreamProcessorVPx : public IElectraDecoderBitstreamProcessor`  
_L8-25_
- inherits: `IElectraDecoderBitstreamProcessor`
- L11 _public function_ `static TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> Create(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams)`
- L14 _public prototype_ `virtual ~FElectraDecoderBitstreamProcessorVPx();`
- L15 _public prototype_ `bool WillModifyBitstreamInPlace() override;`
- L16 _public prototype_ `void Clear() override;`
- L17 _public prototype_ `EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) override;`
- L18 _public prototype_ `void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) override;`
- L19 _public prototype_ `FString GetLastError() override;`
- L22 _private prototype_ `FElectraDecoderBitstreamProcessorVPx(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams);`
- L24 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/Google/ElectraUtilsVPxVideo.h` (Public)


#### class `ElectraDecodersUtil::VPxVideo::FVPCodecConfigurationRecord`  
`class FVPCodecConfigurationRecord`  
_L20-74_
- desc: VP Codec ISO Media File Format Binding see: https://www.webmproject.org/vp9/mp4/#vp-codec-configuration-box This is the same configuration for both VP8 and VP9.
- L32 _public prototype_ `bool Parse(int32 InVP8Or9, const TConstArrayView<uint8>& InDCR);`
- L34 _public function_ `inline const TArray<uint8>& GetRawData() const`
- L36 _public function_ `inline const TArray<uint8>& GetCodecSpecificData() const`
- L39 _public function_ `inline int32 GetVPxVersion() const`
- L42 _public function_ `inline uint8 GetProfile() const`
- L44 _public function_ `inline uint8 GetLevel() const`
- L46 _public function_ `inline uint8 GetBitDepth() const`
- L49 _public function_ `inline const FColorInfo& GetColorInfo() const`
- L52 _public function_ `inline FString GetCodecSpecifierRFC6381() const`
- L62 _public prototype_ `FString GetFormatInfo();`
- L64 _public prototype_ `static FString GetFormatInfo(uint32 InProfile, uint32 InLevel);`
- L67 _private member_ `TArray<uint8> RawData;`
- L68 _private member_ `TArray<uint8> CSD;`
- L69 _private member_ `FColorInfo ColorInfo;`
- L70 _private member_ `int32 VPx = 0;`
- L71 _private member_ `uint8 Profile = 0;`
- L72 _private member_ `uint8 Level = 0;`
- L73 _private member_ `uint8 BitDepth = 0;`

#### struct `ElectraDecodersUtil::VPxVideo::FVPCodecConfigurationRecord::FColorInfo`  
`struct FColorInfo`  
_L23-30_
- L25 _public member_ `uint8 chromaSubsampling = 1;`
- L26 _public member_ `uint8 colourPrimaries = 1;`
- L27 _public member_ `uint8 transferCharacteristics = 1;`
- L28 _public member_ `uint8 matrixCoefficients = 1;`
- L29 _public member_ `uint8 videoFullRangeFlag = 0;`

#### struct `ElectraDecodersUtil::VPxVideo::FVP9UncompressedHeader`  
`struct FVP9UncompressedHeader`  
_L77-154_
- L79 _public member_ `uint8 frame_marker = 0;`
- L80 _public member_ `uint8 profile_low_bit = 0;`
- L81 _public member_ `uint8 profile_high_bit = 0;`
- L82 _public member_ `uint8 show_existing_frame = 0;`
- L83 _public member_ `uint8 frame_to_show_map_idx = 0;`
- L84 _public member_ `uint8 frame_type = 0;`
- L85 _public member_ `uint8 show_frame = 0;`
- L86 _public member_ `uint8 error_resilient_mode = 0;`
- L88 _public member_ `uint8 intra_only = 0;`
- L89 _public member_ `uint8 reset_frame_context = 0;`
- L91 _public member_ `uint8 ten_or_twelve_bit = 0;`
- L92 _public member_ `uint8 color_space = 0;`
- L93 _public member_ `uint8 color_range = 0;`
- L94 _public member_ `uint8 subsampling_x = 0;`
- L95 _public member_ `uint8 subsampling_y = 0;`
- L97 _public member_ `uint32 frame_width = 0;`
- L98 _public member_ `uint32 frame_height = 0;`
- L100 _public member_ `uint32 render_width = 0;`
- L101 _public member_ `uint32 render_height = 0;`
- L142 _public function_ `bool IsKeyframe() const`
- L144 _public function_ `int32 GetProfile() const`
- L146 _public function_ `int32 GetBitDepth() const`
- L148 _public function_ `EColorSpace GetColorSpace() const`
- L150 _public function_ `EColorRange GetColorRange() const`
- L152 _public function_ `ESubSampling GetSubSampling() const`

#### enum `ElectraDecodersUtil::VPxVideo::FVP9UncompressedHeader::EColorSpace`  
`enum EColorSpace`  
_L103-113_
- L105 _public enumerator_ `CS_Unknown = 0`
- L106 _public enumerator_ `CS_BT_601 = 1` — Rec. ITU-R BT.601-7
- L107 _public enumerator_ `CS_BT_709 = 2` — Rec. ITU-R BT.709-6
- L108 _public enumerator_ `CS_SMPTE_170 = 3` — SMPTE-170
- L109 _public enumerator_ `CS_SMPTE_240 = 4` — SMPTE-240
- L110 _public enumerator_ `CS_BT_2020 = 5` — Rec. ITU-R BT.2020-2
- L111 _public enumerator_ `CS_Reserved = 6`
- L112 _public enumerator_ `CS_RGB = 7` — sRGB (IEC 61966-2-1)

#### enum `ElectraDecodersUtil::VPxVideo::FVP9UncompressedHeader::EColorRange`  
`enum EColorRange`  
_L115-132_
- L128 _public enumerator_ `CR_StudioSwing = 0` — For BitDepth equals 8: Y is between 16 and 235 inclusive. U and V are between 16 and 240 inclusive. For BitDepth equals 10: Y is between 64 and 940 inclusive. U and V are between 64 and 960 inclusive. For BitDepth equals 12: Y is between 256 and 3760. U and V are between 256 and 3840 inclusive.
- L131 _public enumerator_ `CR_FullSwing = 1` — No restriction on Y, U, V values.

#### enum `ElectraDecodersUtil::VPxVideo::FVP9UncompressedHeader::ESubSampling`  
`enum ESubSampling`  
_L134-140_
- L136 _public enumerator_ `SS_YUV_444 = 0`
- L137 _public enumerator_ `SS_YUV_440 = 1`
- L138 _public enumerator_ `SS_YUV_422 = 2`
- L139 _public enumerator_ `SS_YUV_420 = 3`

#### struct `ElectraDecodersUtil::VPxVideo::FVP8UncompressedHeader`  
`struct FVP8UncompressedHeader`  
_L164-175_
- L166 _public member_ `uint8 key_frame = 0;`
- L167 _public member_ `uint8 version = 0;`
- L168 _public member_ `uint8 is_experimental = 0;`
- L169 _public member_ `uint8 show_frame = 0;`
- L170 _public member_ `uint16 horizontal_size_code = 0;`
- L171 _public member_ `uint16 vertical_size_code = 0;`
- L173 _public function_ `bool IsKeyframe() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ElectraDecodersUtil`
- L10 _namespace_ `namespace VPxVideo` (scope `ElectraDecodersUtil`)
- L156 _prototype_ `bool GetVP9SuperframeSizes(TArray<uint32>& OutSizes, const void* Data, int64 Size);` (scope `ElectraDecodersUtil::VPxVideo`)
- L157 _prototype_ `bool ParseVP9UncompressedHeader(FVP9UncompressedHeader& OutHeader, const void* Data, int64 Size);` (scope `ElectraDecodersUtil::VPxVideo`)
- L177 _prototype_ `bool ParseVP8UncompressedHeader(FVP8UncompressedHeader& OutHeader, const void* Data, int64 Size);` (scope `ElectraDecodersUtil::VPxVideo`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/MPEG/ElectraBitstreamProcessor_H264.h` (Public)


#### class `FElectraDecoderBitstreamProcessorH264`  
`class FElectraDecoderBitstreamProcessorH264 : public IElectraDecoderBitstreamProcessor`  
_L8-25_
- inherits: `IElectraDecoderBitstreamProcessor`
- L11 _public function_ `static TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> Create(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams)`
- L14 _public prototype_ `virtual ~FElectraDecoderBitstreamProcessorH264();`
- L15 _public prototype_ `bool WillModifyBitstreamInPlace() override;`
- L16 _public prototype_ `void Clear() override;`
- L17 _public prototype_ `EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) override;`
- L18 _public prototype_ `void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) override;`
- L19 _public prototype_ `FString GetLastError() override;`
- L22 _private prototype_ `FElectraDecoderBitstreamProcessorH264(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams);`
- L24 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/MPEG/ElectraBitstreamProcessor_H265.h` (Public)


#### class `FElectraDecoderBitstreamProcessorH265`  
`class FElectraDecoderBitstreamProcessorH265 : public IElectraDecoderBitstreamProcessor`  
_L8-25_
- inherits: `IElectraDecoderBitstreamProcessor`
- L11 _public function_ `static TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> Create(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams)`
- L14 _public prototype_ `virtual ~FElectraDecoderBitstreamProcessorH265();`
- L15 _public prototype_ `bool WillModifyBitstreamInPlace() override;`
- L16 _public prototype_ `void Clear() override;`
- L17 _public prototype_ `EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) override;`
- L18 _public prototype_ `void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) override;`
- L19 _public prototype_ `FString GetLastError() override;`
- L22 _private prototype_ `FElectraDecoderBitstreamProcessorH265(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams);`
- L24 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/MPEG/ElectraUtilsMP4.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ElectraDecodersUtil`
- L12 _namespace_ `namespace MP4` (scope `ElectraDecodersUtil`)
- L14 _prototype_ `bool GetTrackFormatInfo(FString& OutMessage, Electra::FCodecTypeFormat& OutCodecInfo, Electra::FDRMTypeFormat& OutDRMInfo, Electra::FDecoderInformation& OutDecoderInfo, const TSharedPtr<MP4Boxes::FMP4BoxTRAK, ESPMode::ThreadSafe>& InTrack, uint32 InTrackID, bool bInCheckIfDecodable);` (scope `ElectraDecodersUtil::MP4`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/MPEG/ElectraUtilsMPEGAudio.h` (Public)


#### class `ElectraDecodersUtil::MPEG::FESDescriptor`  
`class FESDescriptor`  
_L15-71_
- L18 _public prototype_ `bool Parse(const TConstArrayView<uint8>& InESDS);`
- L20 _public function_ `inline const TArray<uint8>& GetCodecSpecificData() const`
- L23 _public function_ `inline uint32 GetBufferSize() const`
- L26 _public function_ `inline uint32 GetMaxBitrate() const`
- L29 _public function_ `inline uint32 GetAvgBitrate() const`
- L53 _public function_ `inline FObjectTypeID GetObjectTypeID() const`
- L56 _public function_ `inline FStreamType GetStreamType() const`
- L60 _private member_ `TArray<uint8> RawData;`
- L61 _private member_ `TArray<uint8> CSD;`
- L62 _private member_ `FObjectTypeID ObjectTypeID = FObjectTypeID::Unknown;`
- L63 _private member_ `FStreamType StreamTypeID = FStreamType::Unknown;`
- L64 _private member_ `uint32 BufferSize = 0;`
- L65 _private member_ `uint32 MaxBitrate = 0;`
- L66 _private member_ `uint32 AvgBitrate = 0;`
- L67 _private member_ `uint16 ESID = 0;`
- L68 _private member_ `uint16 DependsOnStreamESID = 0;`
- L69 _private member_ `uint8 StreamPriority = 0;`
- L70 _private member_ `bool bDependsOnStream = false;`

#### enum `ElectraDecodersUtil::MPEG::FESDescriptor::FObjectTypeID`  
`enum class FObjectTypeID`  
_L33-45_
- desc: See http://mp4ra.org/#/object_types
- L35 _public enumerator_ `Unknown = 0`
- L36 _public enumerator_ `Text_Stream = 8`
- L37 _public enumerator_ `MPEG4_Video = 0x20`
- L38 _public enumerator_ `H264 = 0x21`
- L39 _public enumerator_ `H264_ParameterSets = 0x22`
- L40 _public enumerator_ `H265 = 0x23`
- L41 _public enumerator_ `MPEG4_Audio = 0x40` — ISO/IEC 14496-3
- L42 _public enumerator_ `MPEG2_AAC_LC = 0x67` — ISO/IEC 13818-7
- L43 _public enumerator_ `MPEG2_Audio = 0x69` — ISO/IEC 13818-3
- L44 _public enumerator_ `MPEG1_Audio = 0x6b` — ISO/IEC 11172-3

#### enum `ElectraDecodersUtil::MPEG::FESDescriptor::FStreamType`  
`enum class FStreamType`  
_L46-51_
- L48 _public enumerator_ `Unknown = 0`
- L49 _public enumerator_ `VisualStream = 4`
- L50 _public enumerator_ `AudioStream = 5`

#### class `ElectraDecodersUtil::MPEG::FAACDecoderConfigurationRecord`  
`class FAACDecoderConfigurationRecord`  
_L74-109_
- L77 _public prototype_ `FAACDecoderConfigurationRecord();`
- L79 _public prototype_ `bool ParseFrom(const void* Data, int64 Size);`
- L80 _public prototype_ `void Reset();`
- L81 _public prototype_ `const TArray<uint8>& GetCodecSpecificData() const;`
- L83 _public function_ `inline bool Parse(const TConstArrayView<uint8>& InDCR)`
- L86 _public function_ `inline void SetRawData(const TArray<uint8>& InRawData)`
- L89 _public function_ `inline const TArray<uint8>& GetRawData() const`
- L92 _public function_ `inline FString GetCodecSpecifierRFC6381() const`
- L95 _public prototype_ `FString GetFormatInfo() const;`
- L97 _public member_ `int32 SBRSignal;`
- L98 _public member_ `int32 PSSignal;`
- L99 _public member_ `uint32 ChannelConfiguration;`
- L100 _public member_ `uint32 SamplingFrequencyIndex;`
- L101 _public member_ `uint32 SamplingRate;`
- L102 _public member_ `uint32 ExtSamplingFrequencyIndex;`
- L103 _public member_ `uint32 ExtSamplingFrequency;`
- L104 _public member_ `uint32 AOT;`
- L105 _public member_ `uint32 ExtAOT;`
- L107 _private member_ `TArray<uint8> CodecSpecificData;`
- L108 _private member_ `TArray<uint8> RawData;`

#### struct `ElectraDecodersUtil::MPEG::AACUtils::ADTSheader`  
`struct ADTSheader`  
_L114-134_
- L116 _public member_ `uint16 SyncWord = 0;`
- L117 _public member_ `uint8 Version = 0;`
- L118 _public member_ `uint8 Layer = 0;`
- L119 _public member_ `uint8 ProtectionAbsent = 0;`
- L120 _public member_ `uint8 Profile = 0;`
- L121 _public member_ `uint8 SamplingFrequencyIndex = 0;`
- L122 _public member_ `uint8 PrivateStream = 0;`
- L123 _public member_ `uint8 ChannelConfiguration = 0;`
- L124 _public member_ `uint8 Originality = 0;`
- L125 _public member_ `uint8 Home = 0;`
- L126 _public member_ `uint8 Copyrighted = 0;`
- L127 _public member_ `uint8 CopyrightStart = 0;`
- L128 _public member_ `uint16 FrameLength = 0;`
- L129 _public member_ `uint16 BufferFullness = 0;`
- L130 _public member_ `uint8 NumFrames = 0;`
- L131 _public member_ `uint16 CRCifPresent = 0;`
- L133 _public member_ `uint16 HeaderSize = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ELECTRADECODERS_API`
- L10 _namespace_ `namespace ElectraDecodersUtil`
- L12 _namespace_ `namespace MPEG` (scope `ElectraDecodersUtil`)
- L112 _namespace_ `namespace AACUtils` (scope `ElectraDecodersUtil::MPEG`)
- L136 _prototype_ `int32 GetNumberOfChannelsFromChannelConfiguration(uint32 InChannelConfiguration);` (scope `ElectraDecodersUtil::MPEG::AACUtils`)
- L137 _prototype_ `int32 GetSampleRateFromFrequenceIndex(uint32 InSamplingFrequencyIndex);` (scope `ElectraDecodersUtil::MPEG::AACUtils`)
- L139 _prototype_ `bool ParseADTSHeader(ADTSheader& OutHeader, const TConstArrayView<uint8>& InHeaderData);` (scope `ElectraDecodersUtil::MPEG::AACUtils`)
- L143 _namespace_ `namespace UtilsMPEG123` (scope `ElectraDecodersUtil::MPEG`)
- L146 _prototype_ `bool HasValidSync(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — Raw bit methods
- L147 _prototype_ `int32 GetVersionId(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 0=MPEG2.5, 1=reserved, 2=MPEG2 (ISO/IEC 13818-3), 3=MPEG1 (ISO/IEC 11172-3)
- L148 _prototype_ `int32 GetLayerIndex(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 0=reserved, 1=Layer III, 2=Layer II, 3=Layer I
- L149 _prototype_ `int32 GetBitrateIndex(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 0-15
- L150 _prototype_ `int32 GetSamplingRateIndex(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 0-3
- L151 _prototype_ `int32 GetChannelMode(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 0-3
- L152 _prototype_ `int32 GetNumPaddingBytes(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 0 or 1
- L156 _prototype_ `int32 GetVersion(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — Convenience methods
- L157 _prototype_ `int32 GetLayer(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 0=reserved, 1=Layer I, 2=Layer II, 3=Layer III
- L158 _prototype_ `int32 GetBitrate(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — Bitrate in kbps, -1=invalid
- L159 _prototype_ `int32 GetSamplingRate(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — Sampling rate, -1=invalid
- L160 _prototype_ `int32 GetChannelCount(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — 1=mono, 2=stereo
- L162 _prototype_ `int32 GetSamplesPerFrame(uint32 InFrameHeader);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — number of samples encoded in the frame
- L163 _prototype_ `int32 GetFrameSize(uint32 InFrameHeader, int32 InForcedPadding=-1);` (scope `ElectraDecodersUtil::MPEG::UtilsMPEG123`) — number of bytes in the packet if CBR encoded, 0=could not calculate

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/MPEG/ElectraUtilsMPEGVideo.h` (Public)


#### struct `ElectraDecodersUtil::MPEG::FSEIMessage`  
`struct FSEIMessage`  
_L14-33_
- L31 _public member_ `uint32 PayloadType = ~uint32(0);`
- L32 _public member_ `TArray<uint8> Message;`

#### enum `ElectraDecodersUtil::MPEG::FSEIMessage::EPayloadType`  
`enum EPayloadType`  
_L16-30_
- L18 _public enumerator_ `PT_pic_timing = 1`
- L19 _public enumerator_ `PT_user_data_registered_itu_t_t35 = 4`
- L21 _public enumerator_ `PT_time_code = 136` — PT_tone_mapping_info = 23,							// not expected to be used (application custom)
- L22 _public enumerator_ `PT_mastering_display_colour_volume = 137`
- L26 _public enumerator_ `PT_content_light_level_info = 144` — PT_chroma_resampling_filter_hint = 140,				// not expected to be used PT_knee_function_info = 141,							// not expected to be used (application custom) PT_colour_remapping_info = 142,						// not expected to be used (application custom)
- L27 _public enumerator_ `PT_alternative_transfer_characteristics = 147`
- L28 _public enumerator_ `PT_ambient_viewing_environment = 148`
- L29 _public enumerator_ `PT_content_colour_volume = 149`

#### enum `ElectraDecodersUtil::MPEG::ESEIStreamType`  
`enum class ESEIStreamType`  
_L34-38_
- L36 _public enumerator_ `H264`
- L37 _public enumerator_ `H265`

#### struct `ElectraDecodersUtil::MPEG::FSEImastering_display_colour_volume`  
`struct FSEImastering_display_colour_volume`  
_L42-67_
- L44 _public member_ `uint16 display_primaries_x[3] { 0 };`
- L45 _public member_ `uint16 display_primaries_y[3] { 0 };`
- L46 _public member_ `uint16 white_point_x = 0;`
- L47 _public member_ `uint16 white_point_y = 0;`
- L48 _public member_ `uint32 max_display_mastering_luminance = 0;`
- L49 _public member_ `uint32 min_display_mastering_luminance = 0;`
- L50 _public function_ `bool operator==(const FSEImastering_display_colour_volume& rhs) const`
- L63 _public function_ `bool operator!=(const FSEImastering_display_colour_volume& rhs) const`

#### struct `ElectraDecodersUtil::MPEG::FSEIcontent_light_level_info`  
`struct FSEIcontent_light_level_info`  
_L72-84_
- L74 _public member_ `uint16 max_content_light_level = 0;`
- L75 _public member_ `uint16 max_pic_average_light_level = 0;`
- L76 _public function_ `bool operator==(const FSEIcontent_light_level_info& rhs) const`
- L80 _public function_ `bool operator!=(const FSEIcontent_light_level_info& rhs) const`

#### struct `ElectraDecodersUtil::MPEG::FSEIalternative_transfer_characteristics`  
`struct FSEIalternative_transfer_characteristics`  
_L90-93_
- L92 _public member_ `uint8 preferred_transfer_characteristics = 0;`

#### struct `ElectraDecodersUtil::MPEG::FSEIambient_viewing_environment`  
`struct FSEIambient_viewing_environment`  
_L96-101_
- L98 _public member_ `uint32 ambient_illuminance = 0;`
- L99 _public member_ `uint16 ambient_light_x = 0;`
- L100 _public member_ `uint16 ambient_light_y = 0;`

#### struct `ElectraDecodersUtil::MPEG::FSEIcontent_colour_volume`  
`struct FSEIcontent_colour_volume`  
_L103-116_
- L105 _public member_ `uint8 ccv_cancel_flag = 0;`
- L106 _public member_ `uint8 ccv_persistence_flag = 0;`
- L107 _public member_ `uint8 ccv_primaries_present_flag = 0;`
- L108 _public member_ `uint8 ccv_min_luminance_value_present_flag = 0;`
- L109 _public member_ `uint8 ccv_max_luminance_value_present_flag = 0;`
- L110 _public member_ `uint8 ccv_avg_luminance_value_present_flag = 0;`
- L111 _public member_ `int32 ccv_primaries_x[3] { 0 };`
- L112 _public member_ `int32 ccv_primaries_y[3] { 0 };`
- L113 _public member_ `uint32 ccv_min_luminance_value = 0;`
- L114 _public member_ `uint32 ccv_max_luminance_value = 0;`
- L115 _public member_ `uint32 ccv_avg_luminance_value = 0;`

#### struct `ElectraDecodersUtil::MPEG::FCommonColorimetry`  
`struct FCommonColorimetry`  
_L119-126_
- L121 _public member_ `uint8 colour_primaries = 2;`
- L122 _public member_ `uint8 transfer_characteristics = 2;`
- L123 _public member_ `uint8 matrix_coeffs = 2;`
- L124 _public member_ `uint8 video_full_range_flag = 0;`
- L125 _public member_ `uint8 video_format = 5;`

#### struct `ElectraDecodersUtil::MPEG::FCommonPictureTiming`  
`struct FCommonPictureTiming`  
_L131-154_
- L136 _public member_ `int64 clockTimestamp = 0;` — Calculated value as per: clockTimestamp = ( ( hH * 60 + mM ) * 60 + sS ) * time_scale + nFrames * ( num_units_in_tick * ( 1 + nuit_field_based_flag ) ) + tOffset, can only be valid when there is timing information.
- L138 _public member_ `uint32 num_units_in_tick = 0;` — Values from a pic_timing() SEI in H.264 or from a time_code() SEI in H.265
- L139 _public member_ `uint32 time_scale = 0;` — from the SPS
- L140 _public member_ `int32 time_offset = 0;`
- L141 _public member_ `uint16 n_frames = 0;`
- L142 _public member_ `uint8 timing_info_present_flag = 0;` — from the SPS
- L143 _public member_ `uint8 clock_timestamp_flag = 0;`
- L144 _public member_ `uint8 ct_type = 0;`
- L145 _public member_ `uint8 nuit_field_based_flag = 0;`
- L146 _public member_ `uint8 counting_type = 0;`
- L147 _public member_ `uint8 full_timestamp_flag = 0;`
- L148 _public member_ `uint8 discontinuity_flag = 0;`
- L149 _public member_ `uint8 cnt_dropped_flag = 0;`
- L150 _public member_ `uint8 seconds_value = 0;`
- L151 _public member_ `uint8 minutes_value = 0;`
- L152 _public member_ `uint8 hours_value = 0;`
- L153 _public member_ `uint8 FromH26x = 0;` — last digit of the codec this comes from. 4=H.264, 5=H.265, etc. In case values need different interpretation.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ElectraDecodersUtil`
- L12 _namespace_ `namespace MPEG` (scope `ElectraDecodersUtil`)
- L39 _prototype_ `bool ExtractSEIMessages(TArray<FSEIMessage>& OutMessages, const void* InBitstream, uint64 InBitstreamLength, ESEIStreamType StreamType, bool bIsPrefixSEI);` (scope `ElectraDecodersUtil::MPEG`)
- L68 _prototype_ `bool ParseFromSEIMessage(FSEImastering_display_colour_volume& OutMDCV, const FSEIMessage& InMessage);` (scope `ElectraDecodersUtil::MPEG`)
- L69 _prototype_ `bool ParseFromMDCVBox(FSEImastering_display_colour_volume& OutMDCV, const TConstArrayView<uint8>& InMDCVBox);` (scope `ElectraDecodersUtil::MPEG`)
- L70 _prototype_ `TArray<uint8> BuildMDCVBox(const FSEImastering_display_colour_volume& InFromDisplayColorVolume);` (scope `ElectraDecodersUtil::MPEG`)
- L85 _prototype_ `bool ParseFromSEIMessage(FSEIcontent_light_level_info& OutCLLI, const FSEIMessage& InMessage);` (scope `ElectraDecodersUtil::MPEG`)
- L86 _prototype_ `bool ParseFromCOLLBox(FSEIcontent_light_level_info& OutCLLI, const TConstArrayView<uint8>& InCOLLBox);` (scope `ElectraDecodersUtil::MPEG`)
- L87 _prototype_ `bool ParseFromCLLIBox(FSEIcontent_light_level_info& OutCLLI, const TConstArrayView<uint8>& InCLLIBox);` (scope `ElectraDecodersUtil::MPEG`)
- L88 _prototype_ `TArray<uint8> BuildCLLIBox(const FSEIcontent_light_level_info& InFromContentLightLevel);` (scope `ElectraDecodersUtil::MPEG`)
- L94 _prototype_ `bool ParseFromSEIMessage(FSEIalternative_transfer_characteristics& OutATC, const FSEIMessage& InMessage);` (scope `ElectraDecodersUtil::MPEG`)
- L127 _prototype_ `bool ParseFromCOLRBox(FCommonColorimetry& OutColorimetry, const TConstArrayView<uint8>& InCOLRBox);` (scope `ElectraDecodersUtil::MPEG`)
- L128 _prototype_ `TArray<uint8> BuildCOLRBox(const FCommonColorimetry& InFromColorimetry);` (scope `ElectraDecodersUtil::MPEG`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/MPEG/ElectraUtilsMPEGVideo_H264.h` (Public)


#### struct `ElectraDecodersUtil::MPEG::H264::FNaluInfo`  
`struct FNaluInfo`  
_L22-29_
- L24 _public member_ `uint64 Offset;` — Offset into the bitstream where the startcode begins
- L25 _public member_ `uint64 Size;` — Number of bytes, including the nal unit type, that follow the startcode
- L26 _public member_ `uint8 Type;` — Nal unit type
- L27 _public member_ `uint8 RefIdc;` — RefIdc
- L28 _public member_ `uint8 UnitLength;` — Length of the start code in bytes (3 or 4)

#### struct `ElectraDecodersUtil::MPEG::H264::FRBSP`  
`struct FRBSP`  
_L32-53_
- L34 _public function_ `FRBSP(uint64 InDataSize)`
- L38 _public function_ `void TrimToBitstream(const Electra::FBitstreamReader& InBSR)`
- L51 _public member_ `TArray<uint8> Data;`
- L52 _public member_ `TArray<uint64> RemovedAtSrc;`

#### class `ElectraDecodersUtil::MPEG::H264::FBitstreamReaderH264`  
`class FBitstreamReaderH264 : public Electra::FBitstreamReader`  
_L57-106_
- inherits: `Electra::FBitstreamReader`
- L60 _public prototype_ `FBitstreamReaderH264() = default;`
- L61 _public function_ `FBitstreamReaderH264(const uint8* InData, uint64 InDataSize) : Electra::FBitstreamReader(InData, InDataSize)`
- L65 _public function_ `uint32 ue_v()`
- L78 _public function_ `int32 se_v()`
- L84 _public function_ `const uint8* GetData() const`
- L89 _public function_ `bool more_rbsp_data()`

#### struct `ElectraDecodersUtil::MPEG::H264::FSequenceParameterSet`  
`struct FSequenceParameterSet`  
_L108-316_
- L110 _public function_ `FSequenceParameterSet()`
- L114 _public function_ `void Reset()`
- L194 _public prototype_ `int32 GetMaxDPBSize() const;`
- L195 _public prototype_ `int32 GetDPBSize() const;`
- L196 _public prototype_ `int32 GetWidth() const;`
- L197 _public prototype_ `int32 GetHeight() const;`
- L198 _public prototype_ `void GetDisplaySize(int32& OutWidth, int32& OutHeight) const;`
- L199 _public prototype_ `void GetDisplaySize(uint32& OutWidth, uint32& OutHeight) const;`
- L200 _public prototype_ `void GetCrop(int32& OutLeft, int32& OutRight, int32& OutTop, int32& OutBottom) const;`
- L201 _public prototype_ `void GetAspect(int32& OutSarW, int32& OutSarH) const;`
- L202 _public prototype_ `FFractionalValue GetTiming() const;`
- L203 _public prototype_ `FString GetFormatInfo() const;`
- L204 _public prototype_ `static FString GetFormatInfo(uint32 InProfileIDC, uint32 InLevelIDC, uint32 InConstraintFlags);`
- L206 _public member_ `TArray<uint8> ProcessedBitstream;`
- L208 _public member_ `uint32 profile_idc;` — u(8)
- L209 _public member_ `uint8 constraint_set0_flag;` — u(1)
- L210 _public member_ `uint8 constraint_set1_flag;` — u(1)
- L211 _public member_ `uint8 constraint_set2_flag;` — u(1)
- L212 _public member_ `uint8 constraint_set3_flag;` — u(1)
- L213 _public member_ `uint8 constraint_set4_flag;` — u(1)
- L214 _public member_ `uint8 constraint_set5_flag;` — u(1)
- L215 _public member_ `uint32 level_idc;` — u(8)
- L216 _public member_ `uint32 seq_parameter_set_id;` — ue(v), 0-31
- L217 _public member_ `uint32 chroma_format_idc;` — ue(v), 0-3, default 1
- L218 _public member_ `uint8 separate_colour_plane_flag;` — u(1)
- L219 _public member_ `uint32 bit_depth_luma_minus8;` — ue(v), 0-6
- L220 _public member_ `uint32 bit_depth_chroma_minus8;` — ue(v), 0-6
- L221 _public member_ `uint8 qpprime_y_zero_transform_bypass_flag;` — u(1)
- L222 _public member_ `uint8 seq_scaling_matrix_present_flag;` — u(1)
- L223 _public member_ `uint8 seq_scaling_list_present_flag[12];` — u(1)
- L224 _public member_ `uint8 ScalingList4x4[6][16];`
- L225 _public member_ `uint8 ScalingList8x8[6][64];`
- L226 _public member_ `uint32 log2_max_frame_num_minus4;` — ue(v), 0-12
- L227 _public member_ `uint32 pic_order_cnt_type;` — ue(v), 0-2
- L228 _public member_ `uint32 log2_max_pic_order_cnt_lsb_minus4;` — ue(v), 0-12
- L229 _public member_ `uint8 delta_pic_order_always_zero_flag;` — u(1)
- L230 _public member_ `int32 offset_for_non_ref_pic;` — se(v)
- L231 _public member_ `int32 offset_for_top_to_bottom_field;` — se(v)
- L232 _public member_ `uint32 num_ref_frames_in_pic_order_cnt_cycle;` — ue(v), 0-255
- L233 _public member_ `int32 offset_for_ref_frame[255];` — se(v)
- L234 _public member_ `uint32 max_num_ref_frames;` — ue(v), 0-MaxDpbFrames
- L235 _public member_ `uint8 gaps_in_frame_num_value_allowed_flag;` — u(1)
- L236 _public member_ `uint32 pic_width_in_mbs_minus1;` — ue(v)
- L237 _public member_ `uint32 pic_height_in_map_units_minus1;` — ue(v)
- L238 _public member_ `uint8 frame_mbs_only_flag;` — u(1)
- L239 _public member_ `uint8 mb_adaptive_frame_field_flag;` — u(1)
- L240 _public member_ `uint8 direct_8x8_inference_flag;` — u(1)
- L241 _public member_ `uint8 frame_cropping_flag;` — u(1)
- L242 _public member_ `uint32 frame_crop_left_offset;` — ue(v), 0 - ( PicWidthInSamplesL / CropUnitX ) - ( frame_crop_right_offset + 1 )
- L243 _public member_ `uint32 frame_crop_right_offset;` — ue(v)
- L244 _public member_ `uint32 frame_crop_top_offset;` — ue(v), 0 - ( 16 * FrameHeightInMbs / CropUnitY ) - ( frame_crop_bottom_offset + 1 )
- L245 _public member_ `uint32 frame_crop_bottom_offset;` — ue(v)
- L246 _public member_ `uint8 vui_parameters_present_flag;` — u(1)
- L248 _public member_ `uint8 aspect_ratio_info_present_flag;` — VUI Parameters
- L249 _public member_ `uint32 aspect_ratio_idc;` — u(8), 0-16, 255 (17-254 reserved)
- L250 _public member_ `uint32 sar_width;` — u(16)
- L251 _public member_ `uint32 sar_height;` — u(16)
- L252 _public member_ `uint8 overscan_info_present_flag;` — u(1)
- L253 _public member_ `uint8 overscan_appropriate_flag;` — u(1)
- L254 _public member_ `uint8 video_signal_type_present_flag;` — u(1)
- L255 _public member_ `uint32 video_format;` — u(3), 0-5 (6 & 7 reserved), default 5
- L256 _public member_ `uint8 video_full_range_flag;` — u(1)
- L257 _public member_ `uint8 colour_description_present_flag;` — u(1)
- L258 _public member_ `uint32 colour_primaries;` — u(8), 0-12, 22 (13-21 & 23-255 reserved), default 2
- L259 _public member_ `uint32 transfer_characteristics;` — u(8), 0-2, 4-18 (3 & 19-255 reserved), default 2
- L260 _public member_ `uint32 matrix_coefficients;` — u(8), 0-2, 4-14 (3 & 15-255 reserved), default 2
- L261 _public member_ `uint8 chroma_loc_info_present_flag;` — u(1)
- L262 _public member_ `uint32 chroma_sample_loc_type_top_field;` — ue(v), 0-5, default 0
- L263 _public member_ `uint32 chroma_sample_loc_type_bottom_field;` — ue(v), 0-5, default 0
- L264 _public member_ `uint8 timing_info_present_flag;` — u(1)
- L265 _public member_ `uint32 num_units_in_tick;` — u(32), >0
- L266 _public member_ `uint32 time_scale;` — u(32), >0
- L267 _public member_ `uint8 fixed_frame_rate_flag;` — u(1)
- L268 _public member_ `uint8 nal_hrd_parameters_present_flag;` — u(1)
- L269 _public member_ `uint8 vcl_hrd_parameters_present_flag;` — u(1)
- L270 _public member_ `uint8 low_delay_hrd_flag;` — u(1), default 1, must be 0 if fixed_frame_rate is 1
- L271 _public member_ `uint8 pic_struct_present_flag;` — u(1)
- L272 _public member_ `uint8 bitstream_restriction_flag;` — u(1)
- L273 _public member_ `uint8 motion_vectors_over_pic_boundaries_flag;` — u(1), default 1
- L274 _public member_ `uint32 max_bytes_per_pic_denom;` — ue(v), 0-16, default 2
- L275 _public member_ `uint32 max_bits_per_mb_denom;` — ue(v), 0-16, default 1
- L276 _public member_ `uint32 log2_max_mv_length_horizontal;` — ue(v), 0-15, default 15
- L277 _public member_ `uint32 log2_max_mv_length_vertical;` — ue(v), 0-15, default 15
- L278 _public member_ `uint32 max_num_reorder_frames;` — ue(v), 0-max_dec_frame_buffering,
- L281 _public member_ `uint32 max_dec_frame_buffering;` — defaults to: if profile_idc in [44,86,100,110,122,144] and constraint_set3_flag==1 then 0 otherwise MaxDpbFrames.
- L312 _public member_ `FHRDParameters nal_hrd_parameters;`
- L313 _public member_ `FHRDParameters vcl_hrd_parameters;`
- L315 _public member_ `int32 ExpectedDeltaPerPicOrderCntCycle;` — Calculated values

#### struct `ElectraDecodersUtil::MPEG::H264::FSequenceParameterSet::FHRDParameters`  
`struct FHRDParameters`  
_L282-311_
- L284 _public function_ `FHRDParameters()`
- L288 _public function_ `void Reset()`
- L301 _public member_ `uint32 cpb_cnt_minus1;` — ue(v), 0-31, if low_delay_hrd_flag==1 then 0, default 0
- L302 _public member_ `uint32 bit_rate_scale;` — u(4)
- L303 _public member_ `uint32 cpb_size_scale;` — u(4)
- L304 _public member_ `uint32 bit_rate_value_minus1[32];` — ue(v), 0-2^32-2
- L305 _public member_ `uint32 cpb_size_value_minus1[32];` — ue(v), 0-2^32-2
- L306 _public member_ `uint8 cbr_flag[32];` — u(1)
- L307 _public member_ `uint32 initial_cpb_removal_delay_length_minus1;` — u(5), default 23
- L308 _public member_ `uint32 cpb_removal_delay_length_minus1;` — u(5), default 23
- L309 _public member_ `uint32 dpb_output_delay_length_minus1;` — u(5), default 23
- L310 _public member_ `uint32 time_offset_length;` — u(5), default 24

#### struct `ElectraDecodersUtil::MPEG::H264::FPictureParameterSet`  
`struct FPictureParameterSet`  
_L318-385_
- L320 _public function_ `FPictureParameterSet()`
- L324 _public function_ `void Reset()`
- L356 _public member_ `uint32 pic_parameter_set_id;` — ue(v), 0-255
- L357 _public member_ `uint32 seq_parameter_set_id;` — ue(v), 0-31
- L358 _public member_ `uint8 entropy_coding_mode_flag;` — u(1)
- L359 _public member_ `uint8 bottom_field_pic_order_in_frame_present_flag;` — u(1)
- L360 _public member_ `uint32 num_slice_groups_minus1;` — ue(v), 0-7 (specified in Annex A, G and J)
- L361 _public member_ `uint32 slice_group_map_type;` — ue(v), 0-6
- L362 _public member_ `uint32 run_length_minus1[8];` — ue(v), 0 - PicSizeInMapUnits-1
- L363 _public member_ `uint32 top_left[8];` — ue(v), <= bottom_right[i]
- L364 _public member_ `uint32 bottom_right[8];` — ue(v), < PicSizeInMapUnits
- L365 _public member_ `uint8 slice_group_change_direction_flag;` — u(1)
- L366 _public member_ `uint32 slice_group_change_rate_minus1;` — ue(v), 0 - PicSizeInMapUnits-1
- L367 _public member_ `uint32 pic_size_in_map_units_minus1;` — ue(v), == PicSizeInMapUnits-1
- L368 _public member_ `TArray<uint8> slice_group_id;` — u(v), 0 - num_slice_groups_minus1
- L369 _public member_ `uint32 num_ref_idx_l0_default_active_minus1;` — ue(v), 0-31
- L370 _public member_ `uint32 num_ref_idx_l1_default_active_minus1;` — ue(v), 0-31
- L371 _public member_ `uint8 weighted_pred_flag;` — u(1)
- L372 _public member_ `uint32 weighted_bipred_idc;` — u(2), 0-2
- L373 _public member_ `int32 pic_init_qp_minus26;` — se(v), -(26 + QpBdOffsetY) to +25
- L374 _public member_ `int32 pic_init_qs_minus26;` — se(v), -26 - +25
- L375 _public member_ `int32 chroma_qp_index_offset;` — se(v), -12 - +12
- L376 _public member_ `uint8 deblocking_filter_control_present_flag;` — u(1)
- L377 _public member_ `uint8 constrained_intra_pred_flag;` — u(1)
- L378 _public member_ `uint8 redundant_pic_cnt_present_flag;` — u(1)
- L379 _public member_ `uint8 transform_8x8_mode_flag;` — u(1)
- L380 _public member_ `uint8 pic_scaling_matrix_present_flag;` — u(1)
- L381 _public member_ `uint8 pic_scaling_list_present_flag[12];` — u(1)
- L382 _public member_ `uint8 ScalingList4x4[6][16];`
- L383 _public member_ `uint8 ScalingList8x8[6][64];`
- L384 _public member_ `int32 second_chroma_qp_index_offset;` — se(v), -12 - +12

#### struct `ElectraDecodersUtil::MPEG::H264::FSliceHeader`  
`struct FSliceHeader`  
_L387-451_
- L389 _public member_ `uint32 first_mb_in_slice = 0;` — ue(v)
- L390 _public member_ `uint32 slice_type = 0;` — ue(v), 0-9
- L391 _public member_ `uint32 pic_parameter_set_id = 0;` — ue(v)
- L392 _public member_ `uint32 colour_plane_id = 0;` — u(2)
- L393 _public member_ `uint32 frame_num = 0;` — u(v)
- L394 _public member_ `uint8 field_pic_flag = 0;` — u(1)
- L395 _public member_ `uint8 bottom_field_flag = 0;` — u(1)
- L396 _public member_ `uint32 idr_pic_id = 0;` — ue(v)
- L397 _public member_ `uint32 pic_order_cnt_lsb = 0;` — u(v)
- L398 _public member_ `int32 delta_pic_order_cnt_bottom = 0;` — se(v), default 0
- L399 _public member_ `int32 delta_pic_order_cnt[2] {0,0};` — se(v), default 0 for both
- L400 _public member_ `uint32 redundant_pic_cnt = 0;` — ue(v), 0-127
- L401 _public member_ `uint8 direct_spatial_mv_pred_flag = 0;` — u(1)
- L402 _public member_ `uint8 num_ref_idx_active_override_flag = 0;` — u(1)
- L403 _public member_ `uint32 num_ref_idx_l0_active_minus1 = 0;` — ue(v), 0-15 for frame coded pictures
- L404 _public member_ `uint32 num_ref_idx_l1_active_minus1 = 0;` — ue(v), 0-15 for frame coded pictures
- L405 _public member_ `uint32 cabac_init_idc = 0;` — ue(v), 0-2
- L406 _public member_ `int32 slice_qp_delta = 0;` — se(v)
- L407 _public member_ `uint8 sp_for_switch_flag = 0;` — u(1)
- L408 _public member_ `int32 slice_qs_delta = 0;` — se(v)
- L409 _public member_ `uint32 disable_deblocking_filter_idc = 0;` — ue(v), 0-2
- L410 _public member_ `int32 slice_alpha_c0_offset_div2 = 0;` — se(v), -6 - +6, default 0
- L411 _public member_ `int32 slice_beta_offset_div2 = 0;` — se(v), -6 - +6, default 0
- L412 _public member_ `uint32 slice_group_change_cycle = 0;` — u(v)
- L421 _public member_ `uint8 ref_pic_list_modification_flag_l0 = 0;` — u(1)
- L422 _public member_ `uint8 ref_pic_list_modification_flag_l1 = 0;` — u(1)
- L423 _public member_ `TArray<FRefPicModification> RefPicListModifications[2];`
- L433 _public member_ `uint32 luma_log2_weight_denom = 0;` — ue(v), 0-7
- L434 _public member_ `uint32 chroma_log2_weight_denom = 0;` — ue(v), 0-7
- L435 _public member_ `PredWeightTable_t PredWeightTable0;`
- L436 _public member_ `PredWeightTable_t PredWeightTable1;`
- L439 _public member_ `uint8 no_output_of_prior_pic_flag = 0;` — dec_ref_pic_marking
- L440 _public member_ `uint8 long_term_reference_flag = 0;` — u(1)
- L441 _public member_ `uint8 adaptive_ref_pic_marking_mode_flag = 0;` — u(1)
- L450 _public member_ `TArray<MemoryManagementControl_t> MemoryManagementControl;`

#### struct `ElectraDecodersUtil::MPEG::H264::FSliceHeader::FRefPicModification`  
`struct FRefPicModification`  
_L415-420_
- desc: ref_pic_list_modification
- L417 _public member_ `uint32 modification_of_pic_nums_idc = 0;` — ue(v), 0-3
- L418 _public member_ `uint32 abs_diff_pic_num_minus1 = 0;` — ue(v)
- L419 _public member_ `uint32 long_term_pic_num = 0;` — ue(v)

#### struct `ElectraDecodersUtil::MPEG::H264::FSliceHeader::PredWeightTable_t`  
`struct PredWeightTable_t`  
_L426-432_
- desc: pred_weight_table
- L428 _public member_ `TArray<int32> luma_weight_l;` — se(v), -128 - + 127
- L429 _public member_ `TArray<int32> luma_offset_l;` — se(v), -128 - + 127
- L430 _public member_ `TArray<int32> chroma_weight_l[2];` — se(v), -128 - + 127
- L431 _public member_ `TArray<int32> chroma_offset_l[2];` — se(v), -128 - + 127

#### struct `ElectraDecodersUtil::MPEG::H264::FSliceHeader::MemoryManagementControl_t`  
`struct MemoryManagementControl_t`  
_L442-449_
- L444 _public member_ `uint32 memory_management_control_operation = 0;` — ue(v)
- L445 _public member_ `uint32 difference_of_pic_nums_minus1 = 0;` — ue(v)
- L446 _public member_ `uint32 long_term_pic_num = 0;` — ue(v)
- L447 _public member_ `uint32 long_term_frame_idx = 0;` — ue(v)
- L448 _public member_ `uint32 max_long_term_frame_idx_plus1 = 0;` — ue(v)

#### struct `ElectraDecodersUtil::MPEG::H264::FOutputFrameInfo`  
`struct FOutputFrameInfo`  
_L453-460_
- L455 _public member_ `int32 IndexInBuffer = -1;`
- L456 _public member_ `FTimespan PTS;`
- L457 _public member_ `uint64 UserValue0 = 0;`
- L458 _public member_ `uint64 UserValue1 = 0;`
- L459 _public member_ `bool bDoNotOutput = false;`

#### class `ElectraDecodersUtil::MPEG::H264::FSlicePOCVars`  
`class FSlicePOCVars`  
_L462-595_
- L484 _public function_ `FSlicePOCVars()`
- L490 _public prototype_ `void GetCurrentReferenceFrames(TArray<FReferenceFrameListEntry>& OutCurrentReferenceFrames);` — Call this to get the current short- and long-term reference frames.
- L493 _public prototype_ `bool GetReferenceFrameLists(TArray<FReferenceFrameListEntry>& OutReferenceFrameList0, TArray<FReferenceFrameListEntry>& OutReferenceFrameList1, const FSliceHeader& InSliceHeader);` — Call this per slice to get the list of references needed for decoding the slice.
- L496 _public prototype_ `bool BeginFrame(uint8 InNalUnitType, uint8 InNalRefIdc, const FSliceHeader& InSliceHeader, const FSequenceParameterSet& InSequenceParameterSet, const FPictureParameterSet& InPictureParameterSet);` — Call this on the first slice of an image to be decoded.
- L498 _public prototype_ `bool HandleMissingFrames(TArray<FOutputFrameInfo>& OutOutputFrameInfos, TArray<FOutputFrameInfo>& OutUnrefFrameInfos, uint8 InNalUnitType, uint8 InNalRefIdc, const FSliceHeader& InSliceHeader, const FSequenceParameterSet& InSequenceParameterSet);` — Call this next to see if there are any missing frames between this and the last.
- L500 _public prototype_ `bool UpdatePOC(uint8 InNalUnitType, uint8 InNalRefIdc, const FSliceHeader& InSliceHeader, const FSequenceParameterSet& InSequenceParameterSet);` — Update the POC values for the current frame.
- L502 _public prototype_ `void UndoPOCUpdate();` — Undo the POC value updates in case the decoding process could not run.
- L504 _public function_ `int32 GetFramePOC() const`
- L506 _public function_ `int32 GetTopPOC() const`
- L508 _public function_ `int32 GetBottomPOC() const`
- L512 _public prototype_ `bool EndFrame(TArray<FOutputFrameInfo>& OutOutputFrameInfos, TArray<FOutputFrameInfo>& OutUnrefFrameInfos, const FOutputFrameInfo& InOutputFrameInfo, uint8 InNalUnitType, uint8 InNalRefIdc, const FSliceHeader& InSliceHeader, bool bIsNonExisting);` — Call this when decoding of the entire frame (all slices) is done.
- L515 _public prototype_ `void Flush(TArray<FOutputFrameInfo>& OutRemainingFrameInfos, TArray<FOutputFrameInfo>& OutUnrefFrameInfos);` — Call this to get all pending frame infos and clear the structure.
- L518 _public prototype_ `void Reset();` — Call this to reset this structure.
- L520 _public function_ `FString GetLastError() const`
- L539 _private prototype_ `void UpdatePOCInternal(uint8 InNalUnitType, uint8 InNalRefIdc, const FSliceHeader& InSliceHeader, const FSequenceParameterSet& InSequenceParameterSet);`
- L540 _private prototype_ `void UpdateRefLists();`
- L541 _private prototype_ `FSmallestPOC GetSmallestPOC();`
- L542 _private prototype_ `bool ReorderRefPicList(TArray<FReferenceFrameListEntry>& InOutReferenceFrameList, const FSliceHeader& InSliceHeader, int32 InListNum);`
- L543 _private prototype_ `void FlushDPB(TArray<FOutputFrameInfo>& InOutInfos, TArray<FOutputFrameInfo>& InUnrefInfos);`
- L544 _private prototype_ `bool SetLastError(const FString& InLastErrorMsg);`
- L546 _private member_ `bool bLastHadMMCO5 = false;`
- L581 _private member_ `FPOCValues CurrentPOC;`
- L582 _private member_ `FPOCValues PreviousPOC;`
- L585 _private member_ `int32 MaxDPBSize = 0;` — DPB
- L586 _private member_ `int32 max_num_ref_frames = 0;`
- L587 _private member_ `int32 max_frame_num = 0;`
- L588 _private member_ `int32 max_long_term_pic_index = -1;`
- L590 _private member_ `TArray<TSharedPtr<FFrameInDPBInfo>> FrameDPBInfos;`
- L591 _private member_ `TArray<TSharedPtr<FFrameInDPBInfo>> ShortTermRefs;`
- L592 _private member_ `TArray<TSharedPtr<FFrameInDPBInfo>> LongTermRefs;`
- L594 _private member_ `FString LastErrorMsg;`

#### struct `ElectraDecodersUtil::MPEG::H264::FSlicePOCVars::FReferenceFrameListEntry`  
`struct FReferenceFrameListEntry`  
_L465-482_
- L467 _public member_ `FOutputFrameInfo UserFrameInfo;`
- L468 _public member_ `int32 FramePOC = 0;`
- L469 _public member_ `int32 TopPOC = 0;`
- L470 _public member_ `int32 BottomPOC = 0;`
- L471 _public member_ `int32 DPBIndex = -1;`
- L472 _public member_ `uint32 FrameNum = 0;`
- L473 _public member_ `int32 PicNum = 0;`
- L474 _public member_ `int32 LongTermFrameIndex = 0;`
- L475 _public member_ `int32 LongTermPicNum = 0;`
- L476 _public member_ `bool bIsLongTerm = false;`
- L477 _public member_ `bool bIsNonExisting = false;`
- L478 _public function_ `bool operator == (const FReferenceFrameListEntry& rhs) const`
- L480 _public function_ `bool operator != (const FReferenceFrameListEntry& rhs) const`

#### struct `ElectraDecodersUtil::MPEG::H264::FSlicePOCVars::FSmallestPOC`  
`struct FSmallestPOC`  
_L525-529_
- L527 _public member_ `int32 Pos = -1;`
- L528 _public member_ `int32 POC = 0x7fffffff;`

#### struct `ElectraDecodersUtil::MPEG::H264::FSlicePOCVars::FFrameInDPBInfo`  
`struct FFrameInDPBInfo : public FReferenceFrameListEntry`  
_L531-537_
- inherits: `FReferenceFrameListEntry`
- L533 _public member_ `int32 FrameNumWrap = 0;`
- L534 _public member_ `bool bIsUsedForReference = false;`
- L535 _public member_ `bool bIsLongTermReference = false;`
- L536 _public member_ `bool bHasBeenOutput = false;`

#### struct `ElectraDecodersUtil::MPEG::H264::FSlicePOCVars::FPOCValues`  
`struct FPOCValues`  
_L548-580_
- L550 _public function_ `FPOCValues()`
- L554 _public function_ `void Reset()`
- L567 _public member_ `int32 pic_order_cnt_msb = 0;` — POC mode 0
- L568 _public member_ `int32 prev_pic_order_cnt_msb = 0;`
- L569 _public member_ `uint32 prev_pic_order_cnt_lsb = 0;`
- L572 _public member_ `uint32 FrameNumOffset = 0;` — POC mode 1 & 2
- L573 _public member_ `uint32 PrevFrameNumOffset = 0;`
- L575 _public member_ `int32 FramePOC = 0;`
- L576 _public member_ `int32 TopPOC = 0;`
- L577 _public member_ `int32 BottomPOC = 0;`
- L579 _public member_ `uint32 prev_frame_num = 0;`

#### class `ElectraDecodersUtil::MPEG::H264::FAVCDecoderConfigurationRecord`  
`class FAVCDecoderConfigurationRecord`  
_L614-663_
- desc: ISO/IEC 14496-15:2022 - 5.3.2 Decoder configuration information
- L617 _public prototype_ `bool Parse(const TConstArrayView<uint8>& InDCR);`
- L618 _public prototype_ `bool CreateFromCodecSpecificData(const TConstArrayView<uint8>& InCSD);`
- L620 _public function_ `inline const TArray<uint8>& GetRawData() const`
- L622 _public function_ `inline const TArray<uint8>& GetCodecSpecificData() const`
- L624 _public function_ `inline const TArray<TArray<uint8>>& GetSequenceParameterSets() const`
- L626 _public function_ `inline const TArray<TArray<uint8>>& GetPictureParameterSets() const`
- L629 _public function_ `inline uint8 GetAVCProfileIndication() const`
- L631 _public function_ `inline uint8 GetProfileCompatibility() const`
- L633 _public function_ `inline uint8 GetAVCLevelIndication() const`
- L636 _public function_ `inline uint8 GetChromaFormat() const`
- L638 _public function_ `inline uint8 GetBitDepthLuma() const`
- L640 _public function_ `inline uint8 GetBitDepthChroma() const`
- L643 _public function_ `inline FString GetCodecSpecifierRFC6381(const TCHAR* InPrefix) const`
- L646 _public prototype_ `FString GetFormatInfo() const;`
- L649 _private member_ `TArray<TArray<uint8>> SequenceParameterSets;`
- L650 _private member_ `TArray<TArray<uint8>> PictureParameterSets;`
- L651 _private member_ `TArray<TArray<uint8>> SequenceParameterSetsExt;`
- L652 _private member_ `TArray<uint8> CSD;`
- L653 _private member_ `TArray<uint8> RawData;`
- L654 _private member_ `uint8 ConfigurationVersion = 0;`
- L655 _private member_ `uint8 AVCProfileIndication = 0;`
- L656 _private member_ `uint8 ProfileCompatibility = 0;`
- L657 _private member_ `uint8 AVCLevelIndication = 0;`
- L658 _private member_ `uint8 NALUnitLength = 0;`
- L659 _private member_ `uint8 ChromaFormat = 0;`
- L660 _private member_ `uint8 BitDepthLumaMinus8 = 0;`
- L661 _private member_ `uint8 BitDepthChromaMinus8 = 0;`
- L662 _private member_ `bool bHaveAdditionalProfileIndication = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ELECTRADECODERS_API`
- L16 _namespace_ `namespace ElectraDecodersUtil`
- L18 _namespace_ `namespace MPEG` (scope `ElectraDecodersUtil`)
- L20 _namespace_ `namespace H264` (scope `ElectraDecodersUtil::MPEG`)
- L30 _prototype_ `bool ParseBitstreamForNALUs(TArray<FNaluInfo>& OutNALUs, const uint8* InBitstream, uint64 InBitstreamLength);` (scope `ElectraDecodersUtil::MPEG::H264`)
- L54 _prototype_ `uint64 EBSPtoRBSP(TArray<uint64>& OutRemovedInBufPos, uint8* OutBuf, const uint8* InBuf, uint64 InNumBytes);` (scope `ElectraDecodersUtil::MPEG::H264`)
- L55 _prototype_ `TUniquePtr<FRBSP> MakeRBSP(const uint8* InData, uint64 InDataSize);` (scope `ElectraDecodersUtil::MPEG::H264`)
- L598 _prototype_ `bool ParseSequenceParameterSet(TMap<uint32, FSequenceParameterSet>& InOutSequenceParameterSets, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H264`)
- L599 _prototype_ `bool ParsePictureParameterSet(TMap<uint32, FPictureParameterSet>& InOutPictureParameterSets, const TMap<uint32, FSequenceParameterSet>& InSequenceParameterSets, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H264`)
- L600 _prototype_ `bool ParseSliceHeader(TUniquePtr<FRBSP>& OutRBSP, FBitstreamReaderH264& OutRBSPReader, FSliceHeader& OutSlice, const TMap<uint32, FSequenceParameterSet>& InSequenceParameterSets, const TMap<uint32, FPictureParameterSet>& InPictureParameterSets, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H264`)
- L602 _prototype_ `bool ParseSequenceParameterSet(FSequenceParameterSet& OutSequenceParameterSet, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H264`)
- L603 _function_ `inline bool ParseSequenceParameterSet(FSequenceParameterSet& OutSequenceParameterSet, const TArray<uint8>& InData)` (scope `ElectraDecodersUtil::MPEG::H264`)
- L607 _prototype_ `int32 CalcNumBytesInNAL(int32 InProfileLevel, int32 InFrameWidth, int32 InFrameHeight, double InFrameRate);` (scope `ElectraDecodersUtil::MPEG::H264`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/MPEG/ElectraUtilsMPEGVideo_H265.h` (Public)


#### struct `ElectraDecodersUtil::MPEG::H265::FNaluInfo`  
`struct FNaluInfo`  
_L21-29_
- L23 _public member_ `uint64 Offset;` — Offset into the bitstream where the startcode begins
- L24 _public member_ `uint64 Size;` — Number of bytes, including the nal unit type, that follow the startcode
- L25 _public member_ `uint8 Type;` — Nal unit type
- L26 _public member_ `uint8 LayerId;` — Nuh layer id
- L27 _public member_ `uint8 TemporalIdPlusOne;` — Nuh temporal id +1
- L28 _public member_ `uint8 UnitLength;` — Length of the start code in bytes (3 or 4)

#### struct `ElectraDecodersUtil::MPEG::H265::FRBSP`  
`struct FRBSP`  
_L32-46_
- L34 _public function_ `FRBSP(uint64 InDataSize)`
- L39 _public function_ `~FRBSP()`
- L43 _public member_ `uint8* Data = nullptr;`
- L44 _public member_ `uint64 Size = 0;`
- L45 _public member_ `TArray<uint64> RemovedAtSrc;`

#### class `ElectraDecodersUtil::MPEG::H265::FBitstreamReaderH265`  
`class FBitstreamReaderH265 : public Electra::FBitstreamReader`  
_L50-120_
- inherits: `Electra::FBitstreamReader`
- L53 _public prototype_ `FBitstreamReaderH265() = default;`
- L54 _public function_ `FBitstreamReaderH265(const uint8* InData, uint64 InDataSize) : Electra::FBitstreamReader(InData, InDataSize)`
- L58 _public function_ `uint32 ue_v()`
- L71 _public function_ `int32 se_v()`
- L77 _public function_ `const uint8* GetData() const`
- L82 _public function_ `bool more_rbsp_data()`
- L100 _public function_ `bool rbsp_trailing_bits()`
- L115 _public function_ `bool byte_alignment()`

#### struct `ElectraDecodersUtil::MPEG::H265::FProfileTierLevel`  
`struct FProfileTierLevel`  
_L122-237_
- L124 _public function_ `FProfileTierLevel()`
- L128 _public prototype_ `bool Parse(FBitstreamReaderH265& br, bool profilePresentFlag, uint32 maxNumSubLayersMinus1);`
- L129 _public function_ `void Reset()`
- L212 _public member_ `uint8 general_profile_space;` — u(2)
- L213 _public member_ `uint8 general_tier_flag;` — u(1)
- L214 _public member_ `uint8 general_profile_idc;` — u(5)
- L215 _public member_ `uint8 general_profile_compatibility_flag[32];` — u(1)
- L216 _public member_ `uint32 general_profile_compatibility_flags;` — u(32), same as general_profile_compatibility_flag[32] but in a single word
- L217 _public member_ `uint64 general_constraint_indicator_flags;` — u(48), bits starting with `general_progressive_source_flag` and extending through the 44 constraint bits
- L218 _public member_ `uint8 general_progressive_source_flag;` — u(1)
- L219 _public member_ `uint8 general_interlaced_source_flag;` — u(1)
- L220 _public member_ `uint8 general_non_packed_constraint_flag;` — u(1)
- L221 _public member_ `uint8 general_frame_only_constraint_flag;` — u(1)
- L222 _public member_ `uint8 general_max_12bit_constraint_flag;` — u(1)
- L223 _public member_ `uint8 general_max_10bit_constraint_flag;` — u(1)
- L224 _public member_ `uint8 general_max_8bit_constraint_flag;` — u(1)
- L225 _public member_ `uint8 general_max_422chroma_constraint_flag;` — u(1)
- L226 _public member_ `uint8 general_max_420chroma_constraint_flag;` — u(1)
- L227 _public member_ `uint8 general_max_monochrome_constraint_flag;` — u(1)
- L228 _public member_ `uint8 general_intra_constraint_flag;` — u(1)
- L229 _public member_ `uint8 general_one_picture_only_constraint_flag;` — u(1)
- L230 _public member_ `uint8 general_lower_bit_rate_constraint_flag;` — u(1)
- L231 _public member_ `uint8 general_max_14bit_constraint_flag;` — u(1)
- L232 _public member_ `uint8 general_inbld_flag;` — u(1)
- L233 _public member_ `uint8 general_level_idc;` — u(8)
- L234 _public member_ `uint8 sub_layer_profile_present_flag[7];` — u(1)
- L235 _public member_ `uint8 sub_layer_level_present_flag[7];` — u(1)
- L236 _public member_ `FSubLayer sub_layers[7];`

#### struct `ElectraDecodersUtil::MPEG::H265::FProfileTierLevel::FSubLayer`  
`struct FSubLayer`  
_L161-210_
- L163 _public function_ `FSubLayer()`
- L167 _public function_ `void Reset()`
- L190 _public member_ `uint8 sub_layer_profile_space;` — u(2)
- L191 _public member_ `uint8 sub_layer_tier_flag;` — u(1)
- L192 _public member_ `uint8 sub_layer_profile_idc;` — u(5)
- L193 _public member_ `uint8 sub_layer_profile_compatibility_flag[32];` — u(1)
- L194 _public member_ `uint8 sub_layer_progressive_source_flag;` — u(1)
- L195 _public member_ `uint8 sub_layer_interlaced_source_flag;` — u(1)
- L196 _public member_ `uint8 sub_layer_non_packed_constraint_flag;` — u(1)
- L197 _public member_ `uint8 sub_layer_frame_only_constraint_flag;` — u(1)
- L198 _public member_ `uint8 sub_layer_max_12bit_constraint_flag;` — u(1)
- L199 _public member_ `uint8 sub_layer_max_10bit_constraint_flag;` — u(1)
- L200 _public member_ `uint8 sub_layer_max_8bit_constraint_flag;` — u(1)
- L201 _public member_ `uint8 sub_layer_max_422chroma_constraint_flag;` — u(1)
- L202 _public member_ `uint8 sub_layer_max_420chroma_constraint_flag;` — u(1)
- L203 _public member_ `uint8 sub_layer_max_monochrome_constraint_flag;` — u(1)
- L204 _public member_ `uint8 sub_layer_intra_constraint_flag;` — u(1)
- L205 _public member_ `uint8 sub_layer_one_picture_only_constraint_flag;` — u(1)
- L206 _public member_ `uint8 sub_layer_lower_bit_rate_constraint_flag;` — u(1)
- L207 _public member_ `uint8 sub_layer_max_14bit_constraint_flag;` — u(1)
- L208 _public member_ `uint8 sub_layer_inbld_flag;` — u(1)
- L209 _public member_ `uint8 sub_layer_level_idc;` — u(8)

#### struct `ElectraDecodersUtil::MPEG::H265::FHRDParameters`  
`struct FHRDParameters`  
_L239-297_
- L241 _public prototype_ `bool Parse(FBitstreamReaderH265& br, bool commonInfPresentFlag, uint32 maxNumSubLayersMinus1);`
- L242 _public function_ `void Reset()`
- L283 _public member_ `uint8 nal_hrd_parameters_present_flag = 0;` — u(1)
- L284 _public member_ `uint8 vcl_hrd_parameters_present_flag = 0;` — u(1)
- L285 _public member_ `uint8 sub_pic_hrd_params_present_flag = 0;` — u(1)
- L286 _public member_ `uint8 tick_divisor_minus2 = 0;` — u(8)
- L287 _public member_ `uint8 du_cpb_removal_delay_increment_length_minus1 = 0;` — u(5)
- L288 _public member_ `uint8 sub_pic_cpb_params_in_pic_timing_sei_flag = 0;` — u(1)
- L289 _public member_ `uint8 dpb_output_delay_du_length_minus1 = 0;` — u(5)
- L290 _public member_ `uint8 bit_rate_scale = 0;` — u(4)
- L291 _public member_ `uint8 cpb_size_scale = 0;` — u(4)
- L292 _public member_ `uint8 cpb_size_du_scale = 0;` — u(4)
- L293 _public member_ `uint8 initial_cpb_removal_delay_length_minus1 = 0;` — u(5)
- L294 _public member_ `uint8 au_cpb_removal_delay_length_minus1 = 0;` — u(5)
- L295 _public member_ `uint8 dpb_output_delay_length_minus1 = 0;` — u(5)
- L296 _public member_ `TArray<FSubLayer> SubLayers;`

#### struct `ElectraDecodersUtil::MPEG::H265::FHRDParameters::FSubLayer`  
`struct FSubLayer`  
_L260-281_
- L274 _public member_ `uint8 fixed_pic_rate_general_flag = 0;` — u(1)
- L275 _public member_ `uint8 fixed_pic_rate_within_cvs_flag = 0;` — u(1)
- L276 _public member_ `uint32 elemental_duration_in_tc_minus1 = 0;` — ue(v)
- L277 _public member_ `uint8 low_delay_hrd_flag = 0;` — u(1)
- L278 _public member_ `uint32 cpb_cnt_minus1 = 0;` — ue(v)
- L279 _public member_ `FSubLayerParameters nal_sub_layer_hrd_parameters;`
- L280 _public member_ `FSubLayerParameters vcl_sub_layer_hrd_parameters;`

#### struct `ElectraDecodersUtil::MPEG::H265::FHRDParameters::FSubLayer::FSubLayerParameters`  
`struct FSubLayerParameters`  
_L262-273_
- L272 _public member_ `TArray<FCpbEntry> cpb;`

#### struct `ElectraDecodersUtil::MPEG::H265::FHRDParameters::FSubLayer::FSubLayerParameters::FCpbEntry`  
`struct FCpbEntry`  
_L264-271_
- L266 _public member_ `uint32 bit_rate_value_minus1 = 0;` — ue(v)
- L267 _public member_ `uint32 cpb_size_value_minus1 = 0;` — ue(v)
- L268 _public member_ `uint32 cpb_size_du_value_minus1 = 0;` — ue(v)
- L269 _public member_ `uint32 bit_rate_du_value_minus1 = 0;` — ue(v)
- L270 _public member_ `uint8 cbr_flag = 0;` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FVUIParameters`  
`struct FVUIParameters`  
_L299-389_
- L301 _public function_ `FVUIParameters()`
- L305 _public prototype_ `bool Parse(FBitstreamReaderH265& br, uint32 In_sps_max_sub_layers_minus1);`
- L306 _public function_ `void Reset()`
- L349 _public member_ `uint8 aspect_ratio_info_present_flag;` — u(1)
- L350 _public member_ `uint8 aspect_ratio_idc;` — u(8)
- L351 _public member_ `uint16 sar_width;` — u(16)
- L352 _public member_ `uint16 sar_height;` — u(16)
- L353 _public member_ `uint8 overscan_info_present_flag;` — u(1)
- L354 _public member_ `uint8 overscan_appropriate_flag;` — u(1)
- L355 _public member_ `uint8 video_signal_type_present_flag;` — u(1)
- L356 _public member_ `uint8 video_format;` — u(3), default 5
- L357 _public member_ `uint8 video_full_range_flag;` — u(1)
- L358 _public member_ `uint8 colour_description_present_flag;` — u(1)
- L359 _public member_ `uint8 colour_primaries;` — u(8), default 2
- L360 _public member_ `uint8 transfer_characteristics;` — u(8), default 2
- L361 _public member_ `uint8 matrix_coeffs;` — u(8), default 2
- L362 _public member_ `uint8 chroma_loc_info_present_flag;` — u(1)
- L363 _public member_ `uint32 chroma_sample_loc_type_top_field;` — ue(v), 0 to 5, default 0
- L364 _public member_ `uint32 chroma_sample_loc_type_bottom_field;` — ue(v), 0 to 5, default 0
- L365 _public member_ `uint8 neutral_chroma_indication_flag;` — u(1)
- L366 _public member_ `uint8 field_seq_flag;` — u(1)
- L367 _public member_ `uint8 frame_field_info_present_flag;` — u(1)
- L368 _public member_ `uint8 default_display_window_flag;` — u(1)
- L369 _public member_ `uint32 def_disp_win_left_offset;` — ue(v), default 0
- L370 _public member_ `uint32 def_disp_win_right_offset;` — ue(v), default 0
- L371 _public member_ `uint32 def_disp_win_top_offset;` — ue(v), default 0
- L372 _public member_ `uint32 def_disp_win_bottom_offset;` — ue(v), default 0
- L373 _public member_ `uint8 vui_timing_info_present_flag;` — u(1)
- L374 _public member_ `uint32 vui_num_units_in_tick;` — u(32)
- L375 _public member_ `uint32 vui_time_scale;` — u(32)
- L376 _public member_ `uint8 vui_poc_proportional_to_timing_flag;` — u(1)
- L377 _public member_ `uint32 vui_num_ticks_poc_diff_one_minus1;` — ue(v)
- L378 _public member_ `uint8 vui_hrd_parameters_present_flag;` — u(1)
- L379 _public member_ `FHRDParameters hrd_parameters;`
- L380 _public member_ `uint8 bitstream_restriction_flag;` — u(1)
- L381 _public member_ `uint8 tiles_fixed_structure_flag;` — u(1)
- L382 _public member_ `uint8 motion_vectors_over_pic_boundaries_flag;` — u(1)
- L383 _public member_ `uint8 restricted_ref_pic_lists_flag;` — u(1)
- L384 _public member_ `uint32 min_spatial_segmentation_idc;` — ue(v), 0 to 4095
- L385 _public member_ `uint32 max_bytes_per_pic_denom;` — ue(v), 0 to 16
- L386 _public member_ `uint32 max_bits_per_min_cu_denom;` — ue(v), 0 to 16
- L387 _public member_ `uint32 log2_max_mv_length_horizontal;` — ue(v), 0 to 15
- L388 _public member_ `uint32 log2_max_mv_length_vertical;` — ue(v), 0 to 15

#### struct `ElectraDecodersUtil::MPEG::H265::FScalingListData`  
`struct FScalingListData`  
_L391-409_
- L393 _public prototype_ `bool Parse(FBitstreamReaderH265& br);`
- L394 _public prototype_ `void SetDefaults();`
- L395 _public function_ `void Reset()`
- L407 _public member_ `uint8 scaling_list_dc[4][6];`
- L408 _public member_ `TArray<uint8> scaling_list[4][6];`

#### struct `ElectraDecodersUtil::MPEG::H265::FStRefPicSet`  
`struct FStRefPicSet`  
_L411-475_
- L413 _public prototype_ `bool Parse(FBitstreamReaderH265& br, int32 stRpsIdx, const TArray<FStRefPicSet>& InReferencePicSetList, int32 InReferencePicSetListNum);`
- L414 _public function_ `void Reset()`
- L428 _public member_ `uint8 inter_ref_pic_set_prediction_flag = 0;` — u(1)
- L429 _public member_ `uint32 delta_idx_minus1 = 0;` — ue(v)
- L430 _public member_ `uint8 delta_rps_sign = 0;` — u(1)
- L431 _public member_ `uint32 abs_delta_rps_minus1 = 0;` — ue(v)
- L432 _public member_ `uint32 num_negative_pics = 0;` — ue(v)
- L433 _public member_ `uint32 num_positive_pics = 0;` — ue(v)
- L455 _public member_ `FRawValues raw_values;`
- L458 _public member_ `int32 delta_poc[32] {};` — Calculated and sorted values as they are commonly used.
- L459 _public member_ `uint8 used_by_curr_pic_flag[32] {};`
- L462 _public member_ `uint32 NumDeltaPocsInSliceReferencedSet = 0;` — When parsing this from a slice header we note the number of delta_poc's in the referenced set from the SPS. This is needed by some accelerators.
- L464 _public function_ `uint32 NumNegativePics() const`
- L466 _public function_ `uint32 NumPositivePics() const`
- L468 _public function_ `uint32 NumDeltaPocs() const`
- L470 _public function_ `int32 GetDeltaPOC(uint32 InIndex) const`
- L472 _public function_ `bool IsUsed(uint32 InIndex) const`
- L474 _public prototype_ `void SortDeltaPOC();`

#### struct `ElectraDecodersUtil::MPEG::H265::FStRefPicSet::FRawValues`  
`struct FRawValues`  
_L437-454_
- desc: Raw values as read from the bitstream. These are kept in case some type of hardware accelerator needs them.
- L439 _public function_ `void Reset()`
- L448 _public member_ `uint8 used_by_curr_pic_flag[32] {};` — u(1)
- L449 _public member_ `uint8 use_delta_flag[32] {};` — u(1)
- L450 _public member_ `uint32 delta_poc_s0_minus1[16] {};` — ue(v)
- L451 _public member_ `uint8 used_by_curr_pic_s0_flag[16] {};` — u(1)
- L452 _public member_ `uint32 delta_poc_s1_minus1[16] {};` — ue(v)
- L453 _public member_ `uint8 used_by_curr_pic_s1_flag[16] {};` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FVideoParameterSet`  
`struct FVideoParameterSet`  
_L477-536_
- L479 _public function_ `FVideoParameterSet()`
- L483 _public function_ `void Reset()`
- L515 _public member_ `uint8 vps_video_parameter_set_id;` — u(4)
- L516 _public member_ `uint8 vps_base_layer_internal_flag;` — u(1)
- L517 _public member_ `uint8 vps_base_layer_available_flag;` — u(1)
- L518 _public member_ `uint8 vps_max_layers_minus1;` — u(6), 0-63 (63 is reserved)
- L519 _public member_ `uint8 vps_max_sub_layers_minus1;` — u(3), 0-6
- L520 _public member_ `uint8 vps_temporal_id_nesting_flag;` — u(1)
- L521 _public member_ `FProfileTierLevel profile_tier_level;`
- L522 _public member_ `uint8 vps_sub_layer_ordering_info_present_flag;` — u(1)
- L523 _public member_ `uint32 vps_max_dec_pic_buffering_minus1[8];` — ue(v), 0 to MaxDpbSize-1
- L524 _public member_ `uint32 vps_max_num_reorder_pics[8];` — ue(v), 0 to vps_max_dec_pic_buffering_minus1[i]
- L525 _public member_ `uint32 vps_max_latency_increase_plus1[8];` — ue(v)
- L526 _public member_ `uint8 vps_max_layer_id;` — u(6), 0-63 (63 is reserved)
- L527 _public member_ `uint32 vps_num_layer_sets_minus1;` — ue(v), 0-1023
- L528 _public member_ `TArray<TArray<uint8>> layer_id_included_flag;` — u(1)
- L529 _public member_ `uint8 vps_timing_info_present_flag;` — u(1)
- L530 _public member_ `uint32 vps_num_units_in_tick;` — u(32)
- L531 _public member_ `uint32 vps_time_scale;` — u(32)
- L532 _public member_ `uint8 vps_poc_proportional_to_timing_flag;` — u(1)
- L533 _public member_ `uint32 vps_num_ticks_poc_diff_one_minus1;` — ue(v)
- L534 _public member_ `TArray<FVPSHRD> ListOf_hrd_parameters;`
- L535 _public member_ `uint8 vps_extension_flag;` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FVideoParameterSet::FVPSHRD`  
`struct FVPSHRD`  
_L508-513_
- L510 _public member_ `uint32 hrd_layer_set_idx = 0;` — ue(v)
- L511 _public member_ `uint8 cprms_present_flag = 0;` — u(1)
- L512 _public member_ `FHRDParameters hrd_parameter;`

#### struct `ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet`  
`struct FSequenceParameterSet`  
_L538-818_
- L540 _public function_ `FSequenceParameterSet()`
- L544 _public function_ `void Reset()`
- L624 _public prototype_ `int32 GetMaxDPBSize() const;`
- L625 _public prototype_ `int32 GetDPBSize() const;`
- L626 _public prototype_ `int32 GetMinCbSizeY() const;`
- L627 _public prototype_ `int32 GetWidth() const;`
- L628 _public prototype_ `int32 GetHeight() const;`
- L629 _public prototype_ `void GetDisplaySize(int32& OutWidth, int32& OutHeight) const;`
- L630 _public prototype_ `void GetDisplaySize(uint32& OutWidth, uint32& OutHeight) const;`
- L631 _public prototype_ `void GetCrop(int32& OutLeft, int32& OutRight, int32& OutTop, int32& OutBottom) const;`
- L632 _public prototype_ `void GetAspect(int32& OutSarW, int32& OutSarH) const;`
- L633 _public prototype_ `FFractionalValue GetTiming() const;`
- L634 _public prototype_ `uint64 GetConstraintFlags() const;`
- L635 _public prototype_ `FString GetRFC6381(const TCHAR* SampleTypePrefix) const;`
- L636 _public prototype_ `FString GetFormatInfo() const;`
- L637 _public prototype_ `static FString GetFormatInfo(uint32 InProfileIDC, uint32 InLevelIDC, uint64 InConstraintFlags);`
- L639 _public member_ `uint8 sps_video_parameter_set_id;` — u(4)
- L640 _public member_ `uint8 sps_max_sub_layers_minus1;` — u(3), 0-6
- L641 _public member_ `uint8 sps_temporal_id_nesting_flag;` — u(1)
- L642 _public member_ `FProfileTierLevel profile_tier_level;`
- L643 _public member_ `uint32 sps_seq_parameter_set_id;` — ue(v), 0-15
- L644 _public member_ `uint32 chroma_format_idc;` — ue(v), 0-3
- L645 _public member_ `uint8 separate_colour_plane_flag;` — u(1)
- L646 _public member_ `uint32 pic_width_in_luma_samples;` — ue(v)
- L647 _public member_ `uint32 pic_height_in_luma_samples;` — ue(v)
- L648 _public member_ `uint8 conformance_window_flag;` — u(1)
- L649 _public member_ `uint32 conf_win_left_offset;` — ue(v)
- L650 _public member_ `uint32 conf_win_right_offset;` — ue(v)
- L651 _public member_ `uint32 conf_win_top_offset;` — ue(v)
- L652 _public member_ `uint32 conf_win_bottom_offset;` — ue(v)
- L653 _public member_ `uint32 bit_depth_luma_minus8;` — ue(v)
- L654 _public member_ `uint32 bit_depth_chroma_minus8;` — ue(v)
- L655 _public member_ `uint32 log2_max_pic_order_cnt_lsb_minus4;` — ue(v)
- L656 _public member_ `uint8 sps_sub_layer_ordering_info_present_flag;` — u(1)
- L657 _public member_ `uint32 sps_max_dec_pic_buffering_minus1[8];` — ue(v)
- L658 _public member_ `uint32 sps_max_num_reorder_pics[8];` — ue(v)
- L659 _public member_ `uint32 sps_max_latency_increase_plus1[8];` — ue(v)
- L660 _public member_ `uint32 log2_min_luma_coding_block_size_minus3;` — ue(v)
- L661 _public member_ `uint32 log2_diff_max_min_luma_coding_block_size;` — ue(v)
- L662 _public member_ `uint32 log2_min_luma_transform_block_size_minus2;` — ue(v)
- L663 _public member_ `uint32 log2_diff_max_min_luma_transform_block_size;` — ue(v)
- L664 _public member_ `uint32 max_transform_hierarchy_depth_inter;` — ue(v)
- L665 _public member_ `uint32 max_transform_hierarchy_depth_intra;` — ue(v)
- L666 _public member_ `uint8 scaling_list_enabled_flag;` — u(1)
- L667 _public member_ `uint8 sps_scaling_list_data_present_flag;` — u(1)
- L668 _public member_ `FScalingListData scaling_list_data;`
- L669 _public member_ `uint8 amp_enabled_flag;` — u(1)
- L670 _public member_ `uint8 sample_adaptive_offset_enabled_flag;` — u(1)
- L671 _public member_ `uint8 pcm_enabled_flag;` — u(1)
- L672 _public member_ `uint8 pcm_sample_bit_depth_luma_minus1;` — u(4)
- L673 _public member_ `uint8 pcm_sample_bit_depth_chroma_minus1;` — u(4)
- L674 _public member_ `uint32 log2_min_pcm_luma_coding_block_size_minus3;` — ue(v)
- L675 _public member_ `uint32 log2_diff_max_min_pcm_luma_coding_block_size;` — ue(v)
- L676 _public member_ `uint8 pcm_loop_filter_disabled_flag;` — u(1)
- L677 _public member_ `uint32 num_short_term_ref_pic_sets;` — ue(v)
- L678 _public member_ `TArray<FStRefPicSet> st_ref_pic_set;`
- L679 _public member_ `uint8 long_term_ref_pics_present_flag;` — u(1)
- L680 _public member_ `uint32 num_long_term_ref_pics_sps;` — ue(v)
- L686 _public member_ `TArray<FLongTermRefPic> long_term_ref_pics;`
- L687 _public member_ `uint8 sps_temporal_mvp_enabled_flag;` — u(1)
- L688 _public member_ `uint8 strong_intra_smoothing_enabled_flag;` — u(1)
- L689 _public member_ `uint8 vui_parameters_present_flag;` — u(1)
- L690 _public member_ `FVUIParameters vui_parameters;`
- L691 _public member_ `uint8 sps_extension_present_flag;` — u(1)
- L692 _public member_ `uint8 sps_range_extension_flag;` — u(1)
- L693 _public member_ `uint8 sps_multilayer_extension_flag;` — u(1)
- L694 _public member_ `uint8 sps_3d_extension_flag;` — u(1)
- L695 _public member_ `uint8 sps_scc_extension_flag;` — u(1)
- L696 _public member_ `uint8 sps_extension_4bits;` — u(4)
- L722 _public member_ `FSPSRangeExtension sps_range_extension;`
- L732 _public member_ `FSPSMultilayerExtension sps_multilayer_extension;`
- L768 _public member_ `FSPS3DExtension sps_3d_extension;`
- L797 _public member_ `FSPSSCCExtension sps_scc_extension;`
- L800 _public member_ `uint32 ChromaArrayType = 0;` — Calculated common values
- L801 _public member_ `uint32 MinCbLog2SizeY = 0;`
- L802 _public member_ `uint32 CtbLog2SizeY = 0;`
- L803 _public member_ `uint32 MinCbSizeY = 0;`
- L804 _public member_ `uint32 CtbSizeY = 0;`
- L805 _public member_ `uint32 PicWidthInMinCbsY = 0;`
- L806 _public member_ `uint32 PicWidthInCtbsY = 0;`
- L807 _public member_ `uint32 PicHeightInMinCbsY = 0;`
- L808 _public member_ `uint32 PicHeightInCtbsY = 0;`
- L809 _public member_ `uint32 PicSizeInMinCbsY = 0;`
- L810 _public member_ `uint32 PicSizeInCtbsY = 0;`
- L811 _public member_ `uint32 PicSizeInSamplesY = 0;`
- L812 _public member_ `uint32 PicWidthInSamplesC = 0;`
- L813 _public member_ `uint32 PicHeightInSamplesC = 0;`
- L814 _public member_ `uint32 CtbWidthC = 0;`
- L815 _public member_ `uint32 CtbHeightC = 0;`
- L816 _public member_ `uint32 SubWidthC = 0;`
- L817 _public member_ `uint32 SubHeightC = 0;`

#### struct `ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet::FLongTermRefPic`  
`struct FLongTermRefPic`  
_L681-685_
- L683 _public member_ `uint32 lt_ref_pic_poc_lsb_sps = 0;` — u(v)
- L684 _public member_ `uint8 used_by_curr_pic_lt_sps_flag = 0;` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet::FSPSRangeExtension`  
`struct FSPSRangeExtension`  
_L698-721_
- L700 _public function_ `void Reset()`
- L712 _public member_ `uint8 transform_skip_rotation_enabled_flag;` — u(1)
- L713 _public member_ `uint8 transform_skip_context_enabled_flag;` — u(1)
- L714 _public member_ `uint8 implicit_rdpcm_enabled_flag;` — u(1)
- L715 _public member_ `uint8 explicit_rdpcm_enabled_flag;` — u(1)
- L716 _public member_ `uint8 extended_precision_processing_flag;` — u(1)
- L717 _public member_ `uint8 intra_smoothing_disabled_flag;` — u(1)
- L718 _public member_ `uint8 high_precision_offsets_enabled_flag;` — u(1)
- L719 _public member_ `uint8 persistent_rice_adaptation_enabled_flag;` — u(1)
- L720 _public member_ `uint8 cabac_bypass_alignment_enabled_flag;` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet::FSPSMultilayerExtension`  
`struct FSPSMultilayerExtension`  
_L724-731_
- L726 _public function_ `void Reset()`
- L730 _public member_ `uint8 inter_view_mv_vert_constraint_flag;` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet::FSPS3DExtension`  
`struct FSPS3DExtension`  
_L734-767_
- L736 _public function_ `void Reset()`
- L753 _public member_ `uint8 iv_di_mc_enabled_flag[2];` — u(1)
- L754 _public member_ `uint8 iv_mv_scal_enabled_flag[2];` — u(1)
- L755 _public member_ `uint32 log2_ivmc_sub_pb_size_minus3[2];` — ue(v)
- L756 _public member_ `uint8 iv_res_pred_enabled_flag[2];` — u(1)
- L757 _public member_ `uint8 depth_ref_enabled_flag[2];` — u(1)
- L758 _public member_ `uint8 vsp_mc_enabled_flag[2];` — u(1)
- L759 _public member_ `uint8 dbbp_enabled_flag[2];` — u(1)
- L760 _public member_ `uint8 tex_mc_enabled_flag[2];` — u(1)
- L761 _public member_ `uint32 log2_texmc_sub_pb_size_minus3[2];` — ue(v)
- L762 _public member_ `uint8 intra_contour_enabled_flag[2];` — u(1)
- L763 _public member_ `uint8 intra_dc_only_wedge_enabled_flag[2];` — u(1)
- L764 _public member_ `uint8 cqt_cu_part_pred_enabled_flag[2];` — u(1)
- L765 _public member_ `uint8 inter_dc_only_enabled_flag[2];` — u(1)
- L766 _public member_ `uint8 skip_intra_enabled_flag[2];` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FSequenceParameterSet::FSPSSCCExtension`  
`struct FSPSSCCExtension`  
_L770-796_
- L772 _public function_ `void Reset()`
- L787 _public member_ `uint8 sps_curr_pic_ref_enabled_flag;` — u(1)
- L788 _public member_ `uint8 palette_mode_enabled_flag;` — u(1)
- L789 _public member_ `uint32 palette_max_size;` — ue(v)
- L790 _public member_ `uint32 delta_palette_max_predictor_size;` — ue(v)
- L791 _public member_ `uint8 sps_palette_predictor_initializers_present_flag;` — u(1)
- L792 _public member_ `uint32 sps_num_palette_predictor_initializers_minus1;` — ue(v)
- L793 _public member_ `TArray<uint32> sps_palette_predictor_initializer[3];`
- L794 _public member_ `uint8 motion_vector_resolution_control_idc;` — u(2)
- L795 _public member_ `uint8 intra_boundary_filtering_disabled_flag;` — u(1)

#### struct `ElectraDecodersUtil::MPEG::H265::FPictureParameterSet`  
`struct FPictureParameterSet`  
_L820-1079_
- L822 _public function_ `FPictureParameterSet()`
- L826 _public function_ `void Reset()`
- L879 _public member_ `uint32 pps_pic_parameter_set_id;` — ue(v), 0-63
- L880 _public member_ `uint32 pps_seq_parameter_set_id;` — ue(v), 0-15
- L881 _public member_ `uint8 dependent_slice_segments_enabled_flag;` — u(1)
- L882 _public member_ `uint8 output_flag_present_flag;` — u(1)
- L883 _public member_ `uint8 num_extra_slice_header_bits;` — u(3), 0-2
- L884 _public member_ `uint8 sign_data_hiding_enabled_flag;` — u(1)
- L885 _public member_ `uint8 cabac_init_present_flag;` — u(1)
- L886 _public member_ `uint32 num_ref_idx_l0_default_active_minus1;` — ue(v)
- L887 _public member_ `uint32 num_ref_idx_l1_default_active_minus1;` — ue(v)
- L888 _public member_ `int32 init_qp_minus26;` — se(v), -26 to 25
- L889 _public member_ `uint8 constrained_intra_pred_flag;` — u(1)
- L890 _public member_ `uint8 transform_skip_enabled_flag;` — u(1)
- L891 _public member_ `uint8 cu_qp_delta_enabled_flag;` — u(1)
- L892 _public member_ `uint32 diff_cu_qp_delta_depth;` — ue(v), 0 to log2_diff_max_min_luma_coding_block_size, default 0
- L893 _public member_ `int32 pps_cb_qp_offset;` — se(v), -12 to 12
- L894 _public member_ `int32 pps_cr_qp_offset;` — se(v), -12 to 12
- L895 _public member_ `uint8 pps_slice_chroma_qp_offsets_present_flag;` — u(1)
- L896 _public member_ `uint8 weighted_pred_flag;` — u(1)
- L897 _public member_ `uint8 weighted_bipred_flag;` — u(1)
- L898 _public member_ `uint8 transquant_bypass_enabled_flag;` — u(1)
- L899 _public member_ `uint8 tiles_enabled_flag;` — u(1)
- L900 _public member_ `uint8 entropy_coding_sync_enabled_flag;` — u(1)
- L901 _public member_ `uint32 num_tile_columns_minus1;` — ue(v), 0 to PicWidthInCtbsY-1
- L902 _public member_ `uint32 num_tile_rows_minus1;` — ue(v), 0 to PicHeightInCtbsY-1
- L903 _public member_ `uint8 uniform_spacing_flag;` — u(1), default 1
- L904 _public member_ `TArray<uint32> column_width_minus1;` — ue(v)
- L905 _public member_ `TArray<uint32> row_height_minus1;` — ue(v)
- L906 _public member_ `uint8 loop_filter_across_tiles_enabled_flag;` — u(1), default 1
- L907 _public member_ `uint8 pps_loop_filter_across_slices_enabled_flag;` — u(1)
- L908 _public member_ `uint8 deblocking_filter_control_present_flag;` — u(1)
- L909 _public member_ `uint8 deblocking_filter_override_enabled_flag;` — u(1), default 0
- L910 _public member_ `uint8 pps_deblocking_filter_disabled_flag;` — u(1), default 0
- L911 _public member_ `int32 pps_beta_offset_div2;` — se(v), -6 to 6, default 0
- L912 _public member_ `int32 pps_tc_offset_div2;` — se(v), -6 to 6, default 0
- L913 _public member_ `uint8 pps_scaling_list_data_present_flag;` — u(1)
- L914 _public member_ `FScalingListData scaling_list_data;`
- L915 _public member_ `uint8 lists_modification_present_flag;` — u(1)
- L916 _public member_ `uint32 log2_parallel_merge_level_minus2;` — ue(v), 0 to CtbLog2SizeY-2
- L917 _public member_ `uint8 slice_segment_header_extension_present_flag;` — u(1)
- L918 _public member_ `uint8 pps_extension_present_flag;` — u(1)
- L919 _public member_ `uint8 pps_range_extension_flag;` — u(1), default 0
- L920 _public member_ `uint8 pps_multilayer_extension_flag;` — u(1), default 0
- L921 _public member_ `uint8 pps_3d_extension_flag;` — u(1), default 0
- L922 _public member_ `uint8 pps_scc_extension_flag;` — u(1), default 0
- L923 _public member_ `uint8 pps_extension_4bits;` — u(4), default 0
- L1075 _public member_ `FPPSRangeExtension pps_range_extension;`
- L1076 _public member_ `FPPSMultilayerExtension pps_multilayer_extension;`
- L1077 _public member_ `FPPS3DExtension pps_3d_extension;`
- L1078 _public member_ `FPPSSCCExtension pps_scc_extension;`

#### struct `ElectraDecodersUtil::MPEG::H265::FPictureParameterSet::FPPSRangeExtension`  
`struct FPPSRangeExtension`  
_L925-953_
- L927 _public function_ `FPPSRangeExtension()`
- L931 _public prototype_ `bool Parse(FBitstreamReaderH265& br);`
- L932 _public function_ `void Reset()`
- L944 _public member_ `uint32 log2_max_transform_skip_block_size_minus2;` — ue(v)
- L945 _public member_ `uint8 cross_component_prediction_enabled_flag;` — u(1)
- L946 _public member_ `uint8 chroma_qp_offset_list_enabled_flag;` — u(1)
- L947 _public member_ `uint32 diff_cu_chroma_qp_offset_depth;` — ue(v)
- L948 _public member_ `uint32 chroma_qp_offset_list_len_minus1;` — ue(v)
- L949 _public member_ `TArray<int32> cb_qp_offset_list;` — se(v)
- L950 _public member_ `TArray<int32> cr_qp_offset_list;` — se(v)
- L951 _public member_ `uint32 log2_sao_offset_scale_luma;` — ue(v)
- L952 _public member_ `uint32 log2_sao_offset_scale_chroma;` — ue(v)

#### struct `ElectraDecodersUtil::MPEG::H265::FPictureParameterSet::FPPSMultilayerExtension`  
`struct FPPSMultilayerExtension`  
_L955-1029_
- L957 _public function_ `FPPSMultilayerExtension()`
- L961 _public prototype_ `bool Parse(FBitstreamReaderH265& br);`
- L962 _public function_ `void Reset()`
- L1022 _public member_ `uint8 poc_reset_info_present_flag;` — u(1)
- L1023 _public member_ `uint8 pps_infer_scaling_list_flag;` — u(1)
- L1024 _public member_ `uint8 pps_scaling_list_ref_layer_id;` — u(6), 0-62
- L1025 _public member_ `uint32 num_ref_loc_offsets;` — ue(v), 0 to vps_max_layers_minus1
- L1026 _public member_ `TArray<FRefLocOffset> rlos;`
- L1027 _public member_ `uint8 colour_mapping_enabled_flag;` — u(1)
- L1028 _public member_ `FColourMappingTable colour_mapping_table;`

#### struct `ElectraDecodersUtil::MPEG::H265::FPictureParameterSet::FPPSMultilayerExtension::FColourMappingTable`  
`struct FColourMappingTable`  
_L972-1002_
- L974 _public function_ `void Reset()`
- L989 _public member_ `uint32 num_cm_ref_layers_minus1;` — ue(v), 0-61
- L990 _public member_ `uint8 cm_ref_layer_id[62];` — u(6)
- L991 _public member_ `uint8 cm_octant_depth;` — u(2), 0-1
- L992 _public member_ `uint8 cm_y_part_num_log2;` — u(2), (cm_y_part_num_log2 + cm_octant_depth) shall be in the range of 0 to 3
- L993 _public member_ `uint32 luma_bit_depth_cm_input_minus8;` — ue(v)
- L994 _public member_ `uint32 chroma_bit_depth_cm_input_minus8;` — ue(v)
- L995 _public member_ `uint32 luma_bit_depth_cm_output_minus8;` — ue(v)
- L996 _public member_ `uint32 chroma_bit_depth_cm_output_minus8;` — ue(v)
- L997 _public member_ `uint8 cm_res_quant_bits;` — u(2)
- L998 _public member_ `uint8 cm_delta_flc_bits_minus1;` — u(2)
- L999 _public member_ `int32 cm_adapt_threshold_u_delta;` — se(v)
- L1000 _public member_ `int32 cm_adapt_threshold_v_delta;` — se(v)

#### struct `ElectraDecodersUtil::MPEG::H265::FPictureParameterSet::FPPSMultilayerExtension::FRefLocOffset`  
`struct FRefLocOffset`  
_L1003-1021_
- L1005 _public member_ `uint8 ref_loc_offset_layer_id = 0;` — u(6)
- L1006 _public member_ `uint8 scaled_ref_layer_offset_present_flag = 0;` — u(1)
- L1007 _public member_ `int32 scaled_ref_layer_left_offset = 0;` — se(v)
- L1008 _public member_ `int32 scaled_ref_layer_top_offset = 0;` — se(v)
- L1009 _public member_ `int32 scaled_ref_layer_right_offset = 0;` — se(v)
- L1010 _public member_ `int32 scaled_ref_layer_bottom_offset = 0;` — se(v)
- L1011 _public member_ `uint8 ref_region_offset_present_flag = 0;` — u(1)
- L1012 _public member_ `int32 ref_region_left_offset = 0;` — se(v)
- L1013 _public member_ `int32 ref_region_top_offset = 0;` — se(v)
- L1014 _public member_ `int32 ref_region_right_offset = 0;` — se(v)
- L1015 _public member_ `int32 ref_region_bottom_offset = 0;` — se(v)
- L1016 _public member_ `uint8 resample_phase_set_present_flag = 0;` — u(1)
- L1017 _public member_ `uint32 phase_hor_luma = 0;` — ue(v)
- L1018 _public member_ `uint32 phase_ver_luma = 0;` — ue(v)
- L1019 _public member_ `uint32 phase_hor_chroma_plus8 = 0;` — ue(v)
- L1020 _public member_ `uint32 phase_ver_chroma_plus8 = 0;` — ue(v)

#### struct `ElectraDecodersUtil::MPEG::H265::FPictureParameterSet::FPPS3DExtension`  
`struct FPPS3DExtension`  
_L1031-1037_
- L1033 _public prototype_ `bool Parse(FBitstreamReaderH265& br);`
- L1034 _public function_ `void Reset()`

#### struct `ElectraDecodersUtil::MPEG::H265::FPictureParameterSet::FPPSSCCExtension`  
`struct FPPSSCCExtension`  
_L1039-1073_
- L1041 _public function_ `FPPSSCCExtension()`
- L1045 _public prototype_ `bool Parse(FBitstreamReaderH265& br);`
- L1046 _public function_ `void Reset()`
- L1061 _public member_ `uint8 pps_curr_pic_ref_enabled_flag;` — u(1)
- L1062 _public member_ `uint8 residual_adaptive_colour_transform_enabled_flag;` — u(1)
- L1063 _public member_ `uint8 pps_slice_act_qp_offsets_present_flag;` — u(1)
- L1064 _public member_ `int32 pps_act_y_qp_offset_plus5;` — se(v)
- L1065 _public member_ `int32 pps_act_cb_qp_offset_plus5;` — se(v)
- L1066 _public member_ `int32 pps_act_cr_qp_offset_plus3;` — se(v)
- L1067 _public member_ `uint8 pps_palette_predictor_initializers_present_flag;` — u(1)
- L1068 _public member_ `uint32 pps_num_palette_predictor_initializers;` — ue(v)
- L1069 _public member_ `uint8 monochrome_palette_flag;` — u(1)
- L1070 _public member_ `uint32 luma_bit_depth_entry_minus8;` — ue(v)
- L1071 _public member_ `uint32 chroma_bit_depth_entry_minus8;` — ue(v)
- L1072 _public member_ `TArray<TArray<uint32>> pps_palette_predictor_initializer;` — u(v)

#### struct `ElectraDecodersUtil::MPEG::H265::FSliceSegmentHeader`  
`struct FSliceSegmentHeader`  
_L1081-1177_
- L1083 _public member_ `uint8 first_slice_segment_in_pic_flag = 0;` — u(1)
- L1084 _public member_ `uint8 no_output_of_prior_pics_flag = 0;` — u(1)
- L1085 _public member_ `uint32 slice_pic_parameter_set_id = 0;` — ue(v), 0-63
- L1086 _public member_ `uint8 dependent_slice_segment_flag = 0;` — u(1), default 0
- L1087 _public member_ `uint32 slice_segment_address = 0;` — u(v)
- L1088 _public member_ `uint32 slice_type;` — ue(v), 0-2
- L1089 _public member_ `uint8 pic_output_flag = 1;` — u(1)
- L1090 _public member_ `uint8 colour_plane_id = 0;` — u(2), 0-2
- L1091 _public member_ `uint32 slice_pic_order_cnt_lsb = 0;` — u(v)
- L1092 _public member_ `uint8 short_term_ref_pic_set_sps_flag = 0;` — u(1)
- L1093 _public member_ `uint32 short_term_ref_pic_set_idx = 0;` — u(v), default 0
- L1094 _public member_ `FStRefPicSet st_ref_pic_set;`
- L1095 _public member_ `uint32 num_long_term_sps = 0;` — ue(v), default 0
- L1096 _public member_ `uint32 num_long_term_pics = 0;` — ue(v), default 0
- L1105 _public member_ `TArray<FLongTermRef> long_term_ref;`
- L1106 _public member_ `uint8 slice_temporal_mvp_enabled_flag = 0;` — u(1)
- L1107 _public member_ `uint8 slice_sao_luma_flag = 0;` — u(1)
- L1108 _public member_ `uint8 slice_sao_chroma_flag = 0;` — u(1)
- L1110 _public member_ `uint8 num_ref_idx_active_override_flag = 0;` — u(1)
- L1111 _public member_ `uint32 num_ref_idx_l0_active_minus1 = 0;` — ue(v), 0-14, defaults to PPS's num_ref_idx_l0_default_active_minus1
- L1112 _public member_ `uint32 num_ref_idx_l1_active_minus1 = 0;` — ue(v), 0-14, defaults to PPS's num_ref_idx_l1_default_active_minus1
- L1118 _public member_ `FRefPicListModification ref_pic_lists_modification;`
- L1120 _public member_ `uint8 mvd_l1_zero_flag = 0;` — u(1)
- L1121 _public member_ `uint8 cabac_init_flag = 0;` — u(1), default 0
- L1122 _public member_ `uint8 collocated_from_l0_flag = 1;` — u(1), default 1
- L1123 _public member_ `uint32 collocated_ref_idx = 0;` — ue(v), default 0
- L1136 _public member_ `FPredWeightTable pred_weight_table;`
- L1138 _public member_ `uint32 five_minus_max_num_merge_cand = 0;` — ue(v), 0-4
- L1139 _public member_ `uint8 use_integer_mv_flag = 0;` — u(1), defaults to motion_vector_resolution_control_idc
- L1141 _public member_ `int32 slice_qp_delta = 0;` — se(v), -QpBdOffsetY to +51
- L1142 _public member_ `int32 slice_cb_qp_offset = 0;` — se(v), -12 to +12, default 0
- L1143 _public member_ `int32 slice_cr_qp_offset = 0;` — se(v), -12 to +12, default 0
- L1144 _public member_ `int32 slice_act_y_qp_offset = 0;` — se(v), -12 to +12, default 0
- L1145 _public member_ `int32 slice_act_cb_qp_offset = 0;` — se(v), -12 to +12, default 0
- L1146 _public member_ `int32 slice_act_cr_qp_offset = 0;` — se(v), -12 to +12, default 0
- L1147 _public member_ `uint8 cu_chroma_qp_offset_enabled_flag = 0;` — u(1)
- L1148 _public member_ `uint8 deblocking_filter_override_flag = 0;` — u(1)
- L1149 _public member_ `uint8 slice_deblocking_filter_disabled_flag = 0;` — u(1), defaults to pps_deblocking_filter_disabled_flag
- L1150 _public member_ `int32 slice_beta_offset_div2 = 0;` — se(v), -6 to +6, defaults to pps_beta_offset_div2
- L1151 _public member_ `int32 slice_tc_offset_div2 = 0;` — se(v), -6 to +6, defaults to pps_tc_offset_div2
- L1152 _public member_ `uint8 slice_loop_filter_across_slices_enabled_flag = 0;` — u(1), defaults to pps_loop_filter_across_slices_enabled_flag
- L1153 _public member_ `uint32 num_entry_point_offsets = 0;` — ue(v)
- L1154 _public member_ `uint32 offset_len_minus1 = 0;` — ue(v)
- L1155 _public member_ `TArray<uint32> entry_point_offset_minus1;` — u(v)
- L1158 _public member_ `int32 NumBitsForPOCValues = 0;` — Convenience values used for parsing that do not come from the slice header itself.
- L1159 _public member_ `uint32 NalUnitType = 0;`
- L1160 _public member_ `uint32 NuhLayerId = 0;`
- L1161 _public member_ `uint32 NuhTemporalIdPlus1 = 0;`
- L1162 _public member_ `bool bIsIDR = false;`
- L1163 _public member_ `bool bIsCRA = false;`
- L1164 _public member_ `bool bIsIRAP = false;`
- L1165 _public member_ `bool bIsBLA = false;`
- L1166 _public member_ `bool bIsReferenceNalu = false;`
- L1167 _public member_ `bool bIsSLNR = false;`
- L1168 _public member_ `uint32 CurrRpsIdx = 0;`
- L1169 _public member_ `uint8 HighestTid = 0;` — sps_max_sub_layers_minus1
- L1170 _public member_ `uint32 sps_max_num_reorder_pics_HighestTid = 0;`
- L1171 _public member_ `uint32 sps_max_latency_increase_plus1_HighestTid = 0;`
- L1172 _public member_ `uint32 sps_max_dec_pic_buffering_minus1_HighestTid = 0;`
- L1173 _public member_ `bool SPSLongTermRefPicsPresentFlag = false;`
- L1174 _public member_ `TArray<FSequenceParameterSet::FLongTermRefPic> SPSLongTermRefPics;`
- L1175 _public member_ `uint32 NumBitsForShortTermRefs = 0;`
- L1176 _public member_ `uint32 NumBitsForLongTermRefs = 0;`

#### struct `ElectraDecodersUtil::MPEG::H265::FSliceSegmentHeader::FLongTermRef`  
`struct FLongTermRef`  
_L1097-1104_
- L1099 _public member_ `uint32 lt_idx_sps = 0;` — u(v)
- L1100 _public member_ `uint32 poc_lsb_lt = 0;` — u(v)
- L1101 _public member_ `uint8 used_by_curr_pic_lt_flag = 0;` — u(1)
- L1102 _public member_ `uint8 delta_poc_msb_present_flag = 0;` — u(1)
- L1103 _public member_ `uint32 delta_poc_msb_cycle_lt = 0;` — ue(v)

#### struct `ElectraDecodersUtil::MPEG::H265::FSliceSegmentHeader::FRefPicListModification`  
`struct FRefPicListModification`  
_L1113-1117_
- L1115 _public member_ `TArray<uint32> list_entry_l0;` — u(v)
- L1116 _public member_ `TArray<uint32> list_entry_l1;` — u(v)

#### struct `ElectraDecodersUtil::MPEG::H265::FSliceSegmentHeader::FPredWeightTable`  
`struct FPredWeightTable`  
_L1125-1135_
- L1127 _public member_ `uint32 luma_log2_weight_denom = 0;` — ue(v), 0-7
- L1128 _public member_ `int32 delta_chroma_log2_weight_denom = 0;` — se(v), default 0
- L1129 _public member_ `uint8 luma_weight_lX_flag[2][16] {};` — u(1)
- L1130 _public member_ `uint8 chroma_weight_lX_flag[2][16] {};` — u(1)
- L1131 _public member_ `int32 delta_luma_weight_lX[2][16] {};` — se(v), -128 to 127, defaults to 1 << luma_log2_weight_denom
- L1132 _public member_ `int32 luma_offset_lX[2][16] {};` — se(v), default 0
- L1133 _public member_ `int32 delta_chroma_weight_lX[2][16][2] {};` — se(v), -127 to 128, defaults to 1 << (luma_log2_weight_denom + delta_chroma_log2_weight_denom)
- L1134 _public member_ `int32 delta_chroma_offset_lX[2][16][2] {};` — se(v), default 0

#### class `ElectraDecodersUtil::MPEG::H265::FSliceSegmentHeaderPOCVars`  
`class FSliceSegmentHeaderPOCVars`  
_L1179-1267_
- L1182 _public function_ `FSliceSegmentHeaderPOCVars()`
- L1186 _public function_ `void Reset()`
- L1200 _public prototype_ `void Update(const FSliceSegmentHeader& InFromSliceHeader);`
- L1201 _public function_ `int32 GetSlicePOC() const`
- L1203 _public function_ `int32 GetMaxPocLsb() const`
- L1206 _public function_ `const TArray<int32>& GetPocStCurrBefore() const`
- L1208 _public function_ `const TArray<int32>& GetPocStCurrAfter() const`
- L1210 _public function_ `const TArray<int32>& GetPocStFoll() const`
- L1212 _public function_ `const TArray<int32>& GetPocLtCurr() const`
- L1214 _public function_ `const TArray<int32>& GetPocLtFoll() const`
- L1216 _public function_ `const TArray<bool>& GetCurrDeltaPocMsbPresentFlag() const`
- L1218 _public function_ `const TArray<bool>& GetFollDeltaPocMsbPresentFlag() const`
- L1256 _private member_ `FRefPicSet rps;`
- L1257 _private member_ `int32 prevTid0POC = 0;`
- L1258 _private member_ `int32 SlicePOC = 0;`
- L1259 _private member_ `int32 MaxPocLsb = 0;`
- L1260 _private member_ `TArray<int32> PocStCurrBefore;`
- L1261 _private member_ `TArray<int32> PocStCurrAfter;`
- L1262 _private member_ `TArray<int32> PocStFoll;`
- L1263 _private member_ `TArray<int32> PocLtCurr;`
- L1264 _private member_ `TArray<int32> PocLtFoll;`
- L1265 _private member_ `TArray<bool> CurrDeltaPocMsbPresentFlag;`
- L1266 _private member_ `TArray<bool> FollDeltaPocMsbPresentFlag;`

#### struct `ElectraDecodersUtil::MPEG::H265::FSliceSegmentHeaderPOCVars::FRefPicSet`  
`struct FRefPicSet : public FStRefPicSet`  
_L1222-1254_
- inherits: `FStRefPicSet`
- L1224 _public function_ `void Reset()`
- L1232 _public function_ `FRefPicSet& operator = (const FStRefPicSet& rhs)`
- L1241 _public member_ `int32 poc_lt[32] {};`
- L1242 _public member_ `uint8 used_by_curr_pic_lt_flag[32] {};`
- L1243 _public member_ `uint8 delta_poc_msb_present_lt_flag[32] {};`
- L1244 _public member_ `uint32 num_long_term_pics = 0;`
- L1246 _public function_ `uint32 GetNumLongTermPics() const`
- L1248 _public function_ `int32 GetLongTermPOC(uint32 InIndex) const`
- L1250 _public function_ `bool IsUsedLongTerm(uint32 InIndex) const`
- L1252 _public function_ `bool IsLongTermPOCMSBPresent(uint32 InIndex) const`

#### struct `ElectraDecodersUtil::MPEG::H265::FOutputFrameInfo`  
`struct FOutputFrameInfo`  
_L1269-1276_
- L1271 _public member_ `int32 IndexInBuffer = -1;`
- L1272 _public member_ `FTimespan PTS;`
- L1273 _public member_ `uint64 UserValue0 = 0;`
- L1274 _public member_ `uint64 UserValue1 = 0;`
- L1275 _public member_ `bool bDoNotOutput = false;`

#### class `ElectraDecodersUtil::MPEG::H265::FDecodedPictureBuffer`  
`class FDecodedPictureBuffer : public FSliceSegmentHeaderPOCVars`  
_L1278-1363_
- inherits: `FSliceSegmentHeaderPOCVars`
- L1306 _public function_ `FDecodedPictureBuffer()`
- L1318 _public prototype_ `void ProcessFirstSliceOfFrame(TArray<FDPBOutputFrame>& OutFrames, const FSliceSegmentHeader& InFromSliceHeader, bool bIsFirstInSequence);`
- L1319 _public prototype_ `bool AddDecodedFrame(TArray<FDPBOutputFrame>& OutFrames, const FOutputFrameInfo& InNewDecodedFrame, const FSliceSegmentHeader& InFromSliceHeader);`
- L1330 _public prototype_ `void GetReferenceFramesFromDPB(TArray<FReferenceFrameListEntry>& OutReferenceFrames, TArray<int32> OutDPBIndexLists[eMAX]);`
- L1331 _public prototype_ `const FReferenceFrameListEntry* GetDPBEntryAtIndex(int32 InIndex) const;`
- L1334 _public prototype_ `void Flush(TArray<FDPBOutputFrame>& OutRemainingFrameInfos);` — Call this to get all pending frame infos and clear the structure.
- L1337 _public prototype_ `void Reset();` — Call this to reset this structure.
- L1339 _public function_ `FString GetLastError() const`
- L1344 _private prototype_ `bool UpdatePOCandRPS(const FSliceSegmentHeader& InFromSliceHeader);`
- L1345 _private prototype_ `FReferenceFrameListEntry* GenerateMissingFrame(int32 InPOC, bool bIsLongterm);`
- L1346 _private prototype_ `void EmitNoLongerNeeded(TArray<FDPBOutputFrame>& OutFrames);`
- L1347 _private prototype_ `void EmitAllRemainingAndEmpty(TArray<FDPBOutputFrame>& OutFrames);`
- L1348 _private prototype_ `void BumpPictures(TArray<FDPBOutputFrame>& OutFrames, const FSliceSegmentHeader& InFromSliceHeader, bool bAdditionalBumping);`
- L1350 _private prototype_ `bool SetLastError(const FString& InLastErrorMsg);`
- L1352 _private member_ `bool bNoRaslOutputFlag = false;`
- L1353 _private member_ `bool bCRANoRaslOutputFlag = false;`
- L1355 _private member_ `TArray<FReferenceFrameListEntry> DPBEntries;`
- L1356 _private member_ `TArray<int32> DPBIdxStCurrBefore;`
- L1357 _private member_ `TArray<int32> DPBIdxStCurrAfter;`
- L1358 _private member_ `TArray<int32> DPBIdxStFoll;`
- L1359 _private member_ `TArray<int32> DPBIdxLtCurr;`
- L1360 _private member_ `TArray<int32> DPBIdxLtFoll;`
- L1362 _private member_ `FString LastErrorMsg;`

#### struct `ElectraDecodersUtil::MPEG::H265::FDecodedPictureBuffer::FReferenceFrameListEntry`  
`struct FReferenceFrameListEntry`  
_L1281-1304_
- L1283 _public function_ `void Reset()`
- L1295 _public member_ `FOutputFrameInfo UserFrameInfo;`
- L1296 _public member_ `int32 POC = 0;`
- L1297 _public member_ `int32 DPBIndex = -1;`
- L1298 _public member_ `bool bIsShortTermReference = false;`
- L1299 _public member_ `bool bIsLongTermReference = false;`
- L1300 _public member_ `bool bNeededForOutput = false;`
- L1301 _public member_ `bool bWasAlreadyOutput = false;`
- L1302 _public member_ `bool bIsMissing = false;` — set to true when a "missing frame" reference frame had to be inserted.
- L1303 _public member_ `int32 PicLatencyCount = 0;`

#### struct `ElectraDecodersUtil::MPEG::H265::FDecodedPictureBuffer::FDPBOutputFrame`  
`struct FDPBOutputFrame`  
_L1312-1316_
- L1314 _public member_ `FOutputFrameInfo UserFrameInfo;`
- L1315 _public member_ `bool bDoNotDisplay = true;`

#### enum `ElectraDecodersUtil::MPEG::H265::FDecodedPictureBuffer::EList`  
`enum EList`  
_L1321-1329_
- L1323 _public enumerator_ `eStCurrBefore`
- L1324 _public enumerator_ `eStCurrAfter`
- L1325 _public enumerator_ `eStFoll`
- L1326 _public enumerator_ `eLtCurr`
- L1327 _public enumerator_ `eLtFoll`
- L1328 _public enumerator_ `eMAX`

#### class `ElectraDecodersUtil::MPEG::H265::FHEVCDecoderConfigurationRecord`  
`class FHEVCDecoderConfigurationRecord`  
_L1381-1457_
- L1384 _public prototype_ `bool Parse(const TConstArrayView<uint8>& InDCR);`
- L1385 _public prototype_ `bool CreateFromCodecSpecificData(const TConstArrayView<uint8>& InCSD);`
- L1387 _public function_ `inline const TArray<uint8>& GetRawData() const`
- L1389 _public function_ `inline const TArray<uint8>& GetCodecSpecificData() const`
- L1392 _public function_ `inline const TArray<TArray<uint8>>& GetVideoParameterSets() const`
- L1394 _public function_ `inline const TArray<TArray<uint8>>& GetSequenceParameterSets() const`
- L1396 _public function_ `inline const TArray<FSequenceParameterSet>& GetParsedSequenceParameterSets() const`
- L1398 _public function_ `inline uint8 GetGeneralProfileSpace() const`
- L1400 _public function_ `inline uint8 GetGeneralTierFlag() const`
- L1402 _public function_ `inline uint8 GetGeneralProfileIDC() const`
- L1404 _public function_ `inline uint32 GetGeneralProfileCompatibilityFlags() const`
- L1406 _public function_ `inline uint64 GetGeneralConstraintIndicatorFlags() const`
- L1408 _public function_ `inline uint8 GetGeneralLevelIDC() const`
- L1410 _public function_ `inline uint8 GetChromaFormat() const`
- L1412 _public function_ `inline uint8 GetBitDepthLumaMinus8() const`
- L1414 _public function_ `inline uint8 GetBitDepthChromaMinus8() const`
- L1416 _public function_ `inline const TArray<TArray<uint8>>& GetPrefixNUTs() const`
- L1418 _public function_ `inline const TArray<TArray<uint8>>& GetSuffixNUTs() const`
- L1421 _public prototype_ `FString GetCodecSpecifierRFC6381(const TCHAR* InPrefix) const;`
- L1422 _public prototype_ `FString GetFormatInfo() const;`
- L1431 _private member_ `TArray<FArray> Arrays;`
- L1432 _private member_ `TArray<TArray<uint8>> VideoParameterSets;`
- L1433 _private member_ `TArray<TArray<uint8>> SequenceParameterSets;`
- L1434 _private member_ `TArray<TArray<uint8>> PrefixNUTs;`
- L1435 _private member_ `TArray<TArray<uint8>> SuffixNUTs;`
- L1436 _private member_ `TArray<FVideoParameterSet> ParsedVideoParameterSets;`
- L1437 _private member_ `TArray<FSequenceParameterSet> ParsedSequenceParameterSets;`
- L1438 _private member_ `TArray<uint8> RawData;`
- L1439 _private member_ `TArray<uint8> CSD;`
- L1440 _private member_ `uint64 GeneralConstraintIndicatorFlags = 0;`
- L1441 _private member_ `uint32 GeneralProfileCompatibilityFlags = 0;`
- L1442 _private member_ `uint16 MinSpatialSegmentationIDC = 0;`
- L1443 _private member_ `uint16 AverageFrameRate = 0;`
- L1444 _private member_ `uint8 ConfigurationVersion = 0;`
- L1445 _private member_ `uint8 GeneralProfileSpace = 0;`
- L1446 _private member_ `uint8 GeneralTierFlag = 0;`
- L1447 _private member_ `uint8 GeneralProfileIDC = 0;`
- L1448 _private member_ `uint8 GeneralLevelIDC = 0;`
- L1449 _private member_ `uint8 ParallelismType = 0;`
- L1450 _private member_ `uint8 ChromaFormat = 0;`
- L1451 _private member_ `uint8 BitDepthLumaMinus8 = 0;`
- L1452 _private member_ `uint8 BitDepthChromaMinus8 = 0;`
- L1453 _private member_ `uint8 ConstantFrameRate = 0;`
- L1454 _private member_ `uint8 NumTemporalLayers = 0;`
- L1455 _private member_ `uint8 TemporalIdNested = 0;`
- L1456 _private member_ `uint8 NALUnitLengthMinus1 = 0;`

#### struct `ElectraDecodersUtil::MPEG::H265::FHEVCDecoderConfigurationRecord::FArray`  
`struct FArray`  
_L1425-1430_
- L1427 _public member_ `TArray<TArray<uint8>> NALUs;`
- L1428 _public member_ `uint8 Completeness = 0;`
- L1429 _public member_ `uint8 NALUnitType = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ELECTRADECODERS_API`
- L15 _namespace_ `namespace ElectraDecodersUtil`
- L17 _namespace_ `namespace MPEG` (scope `ElectraDecodersUtil`)
- L19 _namespace_ `namespace H265` (scope `ElectraDecodersUtil::MPEG`)
- L30 _prototype_ `bool ParseBitstreamForNALUs(TArray<FNaluInfo>& OutNALUs, const uint8* InBitstream, uint64 InBitstreamLength);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L47 _prototype_ `uint64 EBSPtoRBSP(TArray<uint64>& OutRemovedInBufPos, uint8* OutBuf, const uint8* InBuf, uint64 InNumBytes);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L48 _prototype_ `TUniquePtr<FRBSP> MakeRBSP(const uint8* InData, uint64 InDataSize);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1366 _prototype_ `bool ParseVideoParameterSet(TMap<uint32, FVideoParameterSet>& InOutVideoParameterSets, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1367 _prototype_ `bool ParseSequenceParameterSet(TMap<uint32, FSequenceParameterSet>& InOutSequenceParameterSets, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1368 _prototype_ `bool ParsePictureParameterSet(TMap<uint32, FPictureParameterSet>& InOutPictureParameterSets, const TMap<uint32, FSequenceParameterSet>& InSequenceParameterSets, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1369 _prototype_ `bool ParseSliceHeader(TUniquePtr<FRBSP>& OutRBSP, FBitstreamReaderH265& OutRBSPReader, FSliceSegmentHeader& OutSlice, const TMap<uint32, FVideoParameterSet>& InVideoParameterSets, const TMap<uint32, FSequenceParameterSet>& InSequenceParameterSets, const TMap<uint32, FPictureParameterSet>& InPictureParameterSets, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1371 _prototype_ `bool ParseVideoParameterSet(FVideoParameterSet& OutSequenceParameterSet, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1372 _function_ `inline bool ParseVideoParameterSet(FVideoParameterSet& OutSequenceParameterSet, const TArray<uint8>& InData)` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1375 _prototype_ `bool ParseSequenceParameterSet(FSequenceParameterSet& OutSequenceParameterSet, const uint8* InBitstream, uint64 InBitstreamLenInBytes);` (scope `ElectraDecodersUtil::MPEG::H265`)
- L1376 _function_ `inline bool ParseSequenceParameterSet(FSequenceParameterSet& OutSequenceParameterSet, const TArray<uint8>& InData)` (scope `ElectraDecodersUtil::MPEG::H265`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/OpenAPV/ElectraBitstreamProcessor_APV.h` (Public)


#### class `FElectraDecoderBitstreamProcessorAPV`  
`class FElectraDecoderBitstreamProcessorAPV : public IElectraDecoderBitstreamProcessor`  
_L8-25_
- inherits: `IElectraDecoderBitstreamProcessor`
- L11 _public function_ `static TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> Create(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams)`
- L14 _public prototype_ `virtual ~FElectraDecoderBitstreamProcessorAPV();`
- L15 _public prototype_ `bool WillModifyBitstreamInPlace() override;`
- L16 _public prototype_ `void Clear() override;`
- L17 _public prototype_ `EProcessResult ProcessInputForDecoding(TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>& OutBSI, FElectraDecoderInputAccessUnit& InOutAccessUnit, const TMap<FString, FVariant>& InAccessUnitSidebandData) override;`
- L18 _public prototype_ `void SetPropertiesOnOutput(TMap<FString, FVariant>& InOutProperties, TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> InBSI) override;`
- L19 _public prototype_ `FString GetLastError() override;`
- L22 _private prototype_ `FElectraDecoderBitstreamProcessorAPV(const TMap<FString, FVariant>& InDecoderParams, const Electra::FCodecTypeFormat& InInitialCodecFormat, const TMap<FString, FVariant>& InAdditionalFormatParams);`
- L24 _private member_ `TPimplPtr<FImpl> Impl;`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/OpenAPV/ElectraUtilsAPVVideo.h` (Public)


#### struct `ElectraDecodersUtil::APVVideo::FColorInfo`  
`struct FColorInfo`  
_L15-21_
- L17 _public member_ `uint8 ColorPrimaries = 2;`
- L18 _public member_ `uint8 TransferCharacteristics = 2;`
- L19 _public member_ `uint8 MatrixCoefficients = 2;`
- L20 _public member_ `uint8 VideoFullRangeFlag = 0;`

#### struct `ElectraDecodersUtil::APVVideo::FFrameInfo`  
`struct FFrameInfo`  
_L22-35_
- L24 _public member_ `uint32 FrameWidth = 0;`
- L25 _public member_ `uint32 FrameHeight = 0;`
- L26 _public member_ `uint8 ProfileIDC = 0;`
- L27 _public member_ `uint8 LevelIDC = 0;`
- L28 _public member_ `uint8 BandIDC = 0;`
- L29 _public member_ `uint8 ChromaFormatIDC = 0;`
- L30 _public member_ `uint8 BitDepthMinus8 = 0;`
- L31 _public member_ `uint8 CaptureTimeDistance = 0;`
- L32 _public member_ `bool bHaveColorDescription = false;`
- L33 _public member_ `bool bCaptureTimeDistanceIgnored = true;`
- L34 _public member_ `FColorInfo ColorInfo;`

#### class `ElectraDecodersUtil::APVVideo::FAPVDecoderConfigurationRecord`  
`class FAPVDecoderConfigurationRecord`  
_L43-102_
- desc: APV Codec ISO Media File Format Binding see: https://github.com/AcademySoftwareFoundation/openapv/blob/main/readme/apv_isobmff.md#apv-decoder-configuration-record-apvdecoderconfigurationrecord
- L52 _public prototype_ `bool Parse(const TConstArrayView<uint8> InDCR);`
- L53 _public prototype_ `bool ParseFromAU(const TConstArrayView64<uint8> InAccessUnit);`
- L55 _public function_ `inline const TArray<uint8>& GetRawData() const`
- L58 _public function_ `inline int32 GetNumEncodedFrameVariants() const`
- L61 _public function_ `inline uint32 GetWidth() const`
- L63 _public function_ `inline uint32 GetHeight() const`
- L65 _public function_ `inline uint8 GetProfile() const`
- L67 _public function_ `inline uint8 GetLevel() const`
- L69 _public function_ `inline uint8 GetBand() const`
- L71 _public function_ `inline uint8 GetBitDepth() const`
- L73 _public function_ `inline const FColorInfo& GetColorInfo() const`
- L75 _public function_ `inline const TArray<FConfigurationEntry>& GetConfigurationEntries() const`
- L78 _public function_ `inline FString GetCodecSpecifierRFC6381() const`
- L84 _public prototype_ `FString GetFormatInfo();`
- L86 _public prototype_ `static FString GetFormatInfo(uint32 InProfile, uint32 InLevel);`
- L88 _private member_ `TArray<FConfigurationEntry> ConfigurationEntries;`
- L89 _private member_ `TArray<uint8> RawData;`
- L90 _private member_ `FColorInfo ColorInfo;`
- L91 _private member_ `uint32 Width = 0;`
- L92 _private member_ `uint32 Height = 0;`
- L93 _private member_ `uint8 Profile = 0;`
- L94 _private member_ `uint8 Level = 0;`
- L95 _private member_ `uint8 Band = 0;`
- L96 _private member_ `uint8 BitDepth = 0;`
- L97 _private member_ `uint8 LargestProfile = 0;`
- L98 _private member_ `uint8 LargestLevel = 0;`
- L99 _private member_ `uint8 LargestBand = 0;`
- L100 _private member_ `int32 NumEncodedFrameVariants = 0;`
- L101 _private member_ `bool bIsNonConformant = false;`

#### struct `ElectraDecodersUtil::APVVideo::FAPVDecoderConfigurationRecord::FConfigurationEntry`  
`struct FConfigurationEntry`  
_L46-50_
- L48 _public member_ `uint8 PBUType = 0;`
- L49 _public member_ `TArray<FFrameInfo> FrameInfos;`

#### struct `ElectraDecodersUtil::APVVideo::FFramePBUInfo`  
`struct FFramePBUInfo`  
_L105-112_
- L108 _public member_ `int64 PBUOffset = 0;` — Offset to where the size of the PBU is located
- L110 _public member_ `uint32 PBUSize = 0;` — Size of the PBU including the size field.
- L111 _public member_ `bool bIsPrimaryFrame = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ElectraDecodersUtil`
- L13 _namespace_ `namespace APVVideo` (scope `ElectraDecodersUtil`)
- L36 _prototype_ `bool ParseFrameHeader(FFrameInfo& OutFrameInfo, const TConstArrayView<uint8> InFramePBU);` (scope `ElectraDecodersUtil::APVVideo`)
- L113 _prototype_ `void ParseAUIntoFramePBUSubsamples(TArray<FFramePBUInfo>& OutPBUInfos, const TConstArrayView64<uint8> InAccessUnit);` (scope `ElectraDecodersUtil::APVVideo`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Utils/VideoDecoderHelpers.h` (Public)


#### class `Electra::MPEG::FVideoDecoderTimecode`  
`class FVideoDecoderTimecode : public IVideoDecoderTimecode`  
_L18-48_
- inherits: `IVideoDecoderTimecode`
- L21 _public prototype_ `virtual ~FVideoDecoderTimecode() = default;`
- L22 _public function_ `virtual FMPEGDefinition const* GetMPEGDefinition() const override`
- L24 _public function_ `void Update(const IVideoDecoderTimecode::FMPEGDefinition& InTimecode)`
- L26 _public function_ `void UpdateWith(const ElectraDecodersUtil::MPEG::FCommonPictureTiming& InTiming)`
- L47 _private member_ `IVideoDecoderTimecode::FMPEGDefinition DecoderTimecode;`

#### class `Electra::MPEG::FColorimetryHelper`  
`class FColorimetryHelper`  
_L52-80_
- L55 _public prototype_ `void Reset();`
- L56 _public prototype_ `void Update(uint8 colour_primaries, uint8 transfer_characteristics, uint8 matrix_coeffs, uint8 video_full_range_flag, uint8 video_format);`
- L57 _public prototype_ `void Update(const TArray<uint8>& InFromCOLRBox);`
- L58 _public prototype_ `void UpdateParamDict(FParamDict& InOutDictionary);`
- L59 _public prototype_ `bool GetCurrentValues(uint8& colour_primaries, uint8& transfer_characteristics, uint8& matrix_coeffs) const;`
- L79 _private member_ `TSharedPtr<FVideoDecoderColorimetry, ESPMode::ThreadSafe> CurrentColorimetry;`

#### class `Electra::MPEG::FColorimetryHelper::FVideoDecoderColorimetry`  
`class FVideoDecoderColorimetry : public IVideoDecoderColorimetry`  
_L62-77_
- inherits: `IVideoDecoderColorimetry`
- L65 _public function_ `FVideoDecoderColorimetry(uint8 colour_primaries, uint8 transfer_characteristics, uint8 matrix_coeffs, uint8 video_full_range_flag, uint8 video_format)`
- L73 _public prototype_ `virtual ~FVideoDecoderColorimetry() = default;`
- L74 _public function_ `IVideoDecoderColorimetry::FMPEGDefinition const* GetMPEGDefinition() const override`
- L76 _public member_ `IVideoDecoderColorimetry::FMPEGDefinition Colorimetry;`

#### class `Electra::MPEG::FHDRHelper`  
`class FHDRHelper`  
_L84-124_
- L87 _public prototype_ `void Reset();`
- L88 _public prototype_ `void Update(int32 BitDepth, const FColorimetryHelper& InColorimetry, const TArray<ElectraDecodersUtil::MPEG::FSEIMessage>& InGlobalPrefixSEIs, const TArray<ElectraDecodersUtil::MPEG::FSEIMessage>& InLocalPrefixSEIs, bool bIsNewCLVS);`
- L89 _public prototype_ `void UpdateFromMPEGBoxes(int32 BitDepth, const FColorimetryHelper& InColorimetry, const TArray<uint8>& InMDCVBox, const TArray<uint8>& InCLLIBox);`
- L90 _public prototype_ `void Update(int32 BitDepth, const FColorimetryHelper& InColorimetry, const TOptional<FVideoDecoderHDRMetadata_mastering_display_colour_volume>& InMDCV, const TOptional<FVideoDecoderHDRMetadata_content_light_level_info>& InCLLI);`
- L91 _public prototype_ `void UpdateWith(const ElectraDecodersUtil::MPEG::FSEImastering_display_colour_volume& InSEI);`
- L92 _public prototype_ `void UpdateWith(const ElectraDecodersUtil::MPEG::FSEIcontent_light_level_info& InSEI);`
- L93 _public prototype_ `void UpdateWith(const ElectraDecodersUtil::MPEG::FSEIalternative_transfer_characteristics& InSEI);`
- L94 _public prototype_ `void SetHDRType(int32 BitDepth, const FColorimetryHelper& InColorimetry);`
- L95 _public prototype_ `void UpdateParamDict(FParamDict& InOutDictionary);`
- L118 _private member_ `TSharedPtr<FVideoDecoderHDRInformation, ESPMode::ThreadSafe> CurrentHDRInfo;`
- L119 _private member_ `TOptional<ElectraDecodersUtil::MPEG::FSEIMessage> ActiveMasteringDisplayColourVolume;`
- L120 _private member_ `TOptional<ElectraDecodersUtil::MPEG::FSEIMessage> ActiveContentLightLevelInfo;`
- L121 _private member_ `TOptional<ElectraDecodersUtil::MPEG::FSEIMessage> ActiveAlternativeTransferCharacteristics;`
- L122 _private member_ `bool bIsFirst = true;`
- L123 _private member_ `int32 CurrentAlternativeTransferCharacteristics = -1;`

#### class `Electra::MPEG::FHDRHelper::FVideoDecoderHDRInformation`  
`class FVideoDecoderHDRInformation : public IVideoDecoderHDRInformation`  
_L97-117_
- inherits: `IVideoDecoderHDRInformation`
- L100 _public prototype_ `virtual ~FVideoDecoderHDRInformation() = default;`
- L101 _public function_ `IVideoDecoderHDRInformation::EType GetHDRType() const override`
- L103 _public function_ `const FVideoDecoderHDRMetadata_mastering_display_colour_volume* GetMasteringDisplayColourVolume() const override`
- L105 _public function_ `const FVideoDecoderHDRMetadata_content_light_level_info* GetContentLightLevelInfo() const override`
- L107 _public function_ `void SetHDRType(IVideoDecoderHDRInformation::EType InHDRType)`
- L109 _public function_ `void SetMasteringDisplayColourVolume(const FVideoDecoderHDRMetadata_mastering_display_colour_volume& In)`
- L111 _public function_ `void SetContentLightLevelInfo(const FVideoDecoderHDRMetadata_content_light_level_info& In)`
- L114 _private member_ `IVideoDecoderHDRInformation::EType HDRType = IVideoDecoderHDRInformation::EType::Unknown;`
- L115 _private member_ `TOptional<FVideoDecoderHDRMetadata_mastering_display_colour_volume> MasteringDisplayColourVolume;`
- L116 _private member_ `TOptional<FVideoDecoderHDRMetadata_content_light_level_info> ContentLightLevelInfo;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Electra`
- L15 _namespace_ `namespace MPEG` (scope `Electra`)

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Windows/WindowsElectraDecoderPlatformOutputHandleTypes.h` (Public)


#### enum `EElectraDecoderPlatformOutputHandleType`  
`enum class EElectraDecoderPlatformOutputHandleType`  
_L17-23_
- L19 _public enumerator_ `MFSample`
- L20 _public enumerator_ `DXDevice`
- L21 _public enumerator_ `DXDeviceContext`
- L22 _public enumerator_ `ImageBuffers` — IElectraDecoderVideoOutputImageBuffers interface

#### class `FElectraDecoderOutputSync`  
`class FElectraDecoderOutputSync final`  
_L25-44_
- L28 _public function_ `FElectraDecoderOutputSync() : SyncValue(0), CopyDoneSyncValue(0)`
- L29 _public function_ `FElectraDecoderOutputSync(TRefCountPtr<IUnknown> InSync, uint64 InSyncValue, TRefCountPtr<IMFSample> InMFSample = nullptr) : Sync(InSync), SyncValue(InSyncValue), CopyDoneSyncValue(0), MFSample(InMFSample)`
- L32 _public function_ `FElectraDecoderOutputSync(TRefCountPtr<IUnknown> InSync, uint64 InSyncValue, TRefCountPtr<ID3D12Fence> InCopyDoneSync, uint64 InCopyDoneSyncValue) : Sync(InSync), SyncValue(InSyncValue), CopyDoneSync(InCopyDoneSync), CopyDoneSyncValue(InCopyDoneSyncValue)`
- L36 _public member_ `TRefCountPtr<IUnknown> Sync;` — Optional IUnknown based sync primitive (fence, or DX12 specific WMF object)
- L37 _public member_ `uint64 SyncValue;` — Optionally needed sync value
- L39 _public member_ `TRefCountPtr<ID3D12Fence> CopyDoneSync;` — Optional fence to signal end of copy from this buffer back to decoder
- L40 _public member_ `uint64 CopyDoneSyncValue;` — Value to be used with CopyDoneSync fence
- L43 _private member_ `TRefCountPtr<IMFSample> MFSample;` — The sample reference can ride along to ensure that the DX12 WMF interface properly keeps reference to the sample until we enqueue their sync primitives with the a D3D queue

#### class `IElectraDecoderVideoOutputImageBuffers`  
`class IElectraDecoderVideoOutputImageBuffers`  
_L46-72_
- L50 _public prototype_ `virtual uint32 GetCodec4CC() const = 0;` — Return the 4cc of the codec.
- L53 _public prototype_ `virtual int32 GetNumberOfBuffers() const = 0;` — Returns the number of separate image buffers making up the frame.
- L56 _public prototype_ `virtual TSharedPtr<TArray64<uint8>, ESPMode::ThreadSafe> GetBufferDataByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer as CPU data buffer.
- L59 _public prototype_ `virtual void* GetBufferTextureByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer as GPU texture resource.
- L62 _public prototype_ `virtual bool GetBufferTextureSyncByIndex(int32 InBufferIndex, FElectraDecoderOutputSync& SyncObject) const = 0;` — Returns the n'th image buffer's GPU sync object to signal texture data as being ready to be read
- L65 _public prototype_ `virtual EPixelFormat GetBufferFormatByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer format
- L68 _public prototype_ `virtual EElectraTextureSamplePixelEncoding GetBufferEncodingByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer encoding
- L71 _public prototype_ `virtual int32 GetBufferPitchByIndex(int32 InBufferIndex) const = 0;` — Returns the n'th image buffer pitch

#### Free symbols / members of external scopes

- L74 _macro_ `#define ELECTRA_HAVE_IMAGEBUFFERS 1`

### `Plugins/Media/ElectraCodecs/Source/ElectraDecoders/Public/Windows/WindowsElectraDecodersPlatformResources.h` (Public)


#### class `FElectraDecodersPlatformResourcesWindows`  
`class FElectraDecodersPlatformResourcesWindows`  
_L12-26_
- L15 _public prototype_ `static bool GetD3DDeviceAndVersion(void** OutD3DDevice, int32* OutD3DVersion);`
- L18 _public prototype_ `static TSharedPtr<FAsyncConsecutiveTaskSync, ESPMode::ThreadSafe> CreateAsyncConsecutiveTaskSync();`
- L19 _public prototype_ `static bool RunCodeAsync(TFunction<void()>&& InCodeToRun, TSharedPtr<FAsyncConsecutiveTaskSync, ESPMode::ThreadSafe> InTaskSync);`
- L22 _public prototype_ `static IDecoderPlatformResource* CreatePlatformVideoResource(void* InOwnerHandle, const TMap<FString, FVariant> InOptions);`
- L23 _public prototype_ `static void ReleasePlatformVideoResource(void* InOwnerHandle, IDecoderPlatformResource* InHandleToRelease);`
- L25 _public prototype_ `static bool SetupOutputTextureSample(FString& OutErrorMessage, TSharedPtr<FElectraTextureSample, ESPMode::ThreadSafe> InOutTextureSampleToSetup, TSharedPtr<IElectraDecoderVideoOutput, ESPMode::ThreadSafe> InDecoderOutput, TSharedPtr<Electra::FParamDict, ESPMode::ThreadSafe> InOutBufferPropertes, FElectraDecodersPlatformResourcesWindows::IDecoderPlatformResource* InPlatformResource);`

#### Free symbols / members of external scopes

- L28 _typedef_ `using FElectraDecodersPlatformResources = FElectraDecodersPlatformResourcesWindows;`
