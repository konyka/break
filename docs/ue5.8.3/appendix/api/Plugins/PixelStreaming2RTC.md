# Plugins / PixelStreaming2RTC

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC`
- headers: 55; symbols: 1397
- symbol kinds: class=95, delegate=3, enum=2, enumerator=7, externvar=70, function=210, macro=27, member=271, namespace=102, prototype=589, struct=4, typedef=2, variable=15
- PrivateDependencyModuleNames: AVCodecsCore, AVCodecsCoreRHI, AudioMixer, AudioPlatformConfiguration, Core, CoreUObject, D3D11RHI, D3D12RHI, DeveloperSettings, Engine, EngineSettings, EpicRtc, HTTP, InputCore, Json, LibVpx, MediaUtils, NVML, PixelCaptureShaders, PixelStreaming2HMD, PixelStreaming2Servers, PixelStreaming2Settings, RHI, RenderCore, Renderer, SignalProcessing, Slate, SlateCore, Sockets, VulkanRHI, WebRTC, WebSockets, XRBase
- PublicDependencyModuleNames: AVCodecsCore, ApplicationCore, EpicRtc, InputDevice, Launch, PixelCapture, PixelStreaming2, PixelStreaming2Core, PixelStreaming2Input, TraceLog, WebRTC

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/AtomicOnceFlag.h` (Internal)


#### class `UE::PixelStreaming2::FAtomicOnceFlag`  
`class FAtomicOnceFlag`  
_L11-18_
- L15 _public function_ `inline bool Trigger()` — Sets flag to true and returns if the flag had fired before
- L17 _private member_ `std::atomic<bool> bFlag = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcAllocator.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcAllocator`  
`class FEpicRtcAllocator : public EpicRtcMemoryInterface`  
_L11-31_
- inherits: `EpicRtcMemoryInterface`
- L14 _public prototype_ `FEpicRtcAllocator() = default;`
- L15 _public prototype_ `virtual ~FEpicRtcAllocator() = default;`
- L17 _public function_ `[[nodiscard]] virtual void* Allocate(uint64_t Size, uint64_t Alignment, const char* Tag) override`
- L22 _public function_ `[[nodiscard]] virtual void* Reallocate(void* Pointer, uint64_t Size, uint64_t Alignment, const char* Tag) override`
- L27 _public function_ `virtual void Free(void* Pointer) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcAudioCapturer.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcAudioCapturer`  
`class FEpicRtcAudioCapturer : public FAudioCapturer`  
_L15-34_
- inherits: `FAudioCapturer`
- desc: FEpicRtcAudioCapturer overrides the default PushAudio behaviour of the FAudioCapturer in order to break up the pushed audio into 10ms chunks
- L18 _public prototype_ `virtual ~FEpicRtcAudioCapturer() = default;`
- L21 _public prototype_ `virtual void PushAudio(const float* AudioData, int32 NumSamples, int32 NumChannels, int32 SampleRate) override;` — Override the push audio method as EpicRtc needs the broadcasted audio to be in 10ms chunks
- L24 _protected function_ `FEpicRtcAudioCapturer(const int SampleRate = 48000, const int NumChannels = 2, const float SampleSizeInSeconds = 0.5f) : FAudioCapturer(SampleRate, NumChannels, SampleSizeInSeconds)`
- L30 _private member_ `TArray<int16_t> RecordingBuffer;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcAudioSink.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcAudioSink`  
`class FEpicRtcAudioSink : public FAudioSink, public TEpicRtcTrack<EpicRtcAudioTrackInterface>`  
_L13-20_
- inherits: `FAudioSink,TEpicRtcTrack<EpicRtcAudioTrackInterface>`
- desc: Collects audio coming in from EpicRtc and passes into into UE's audio system.
- L16 _public prototype_ `static TSharedPtr<FEpicRtcAudioSink> Create(TRefCountPtr<EpicRtcAudioTrackInterface> InTrack);`
- L17 _public prototype_ `virtual ~FEpicRtcAudioSink() = default;`
- L19 _private prototype_ `FEpicRtcAudioSink(TRefCountPtr<EpicRtcAudioTrackInterface> InTrack);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcAudioSource.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcAudioSource`  
`class FEpicRtcAudioSource : public FAudioSource, public TEpicRtcTrack<EpicRtcAudioTrackInterface>`  
_L15-23_
- inherits: `FAudioSource,TEpicRtcTrack<EpicRtcAudioTrackInterface>`
- L18 _public prototype_ `static TSharedPtr<FEpicRtcAudioSource> Create(TRefCountPtr<EpicRtcAudioTrackInterface> InTrack, TSharedPtr<class FEpicRtcAudioCapturer> InCapturer);`
- L20 _public prototype_ `virtual void OnAudioBuffer(const int16_t* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate);`
- L22 _private prototype_ `FEpicRtcAudioSource(TRefCountPtr<EpicRtcAudioTrackInterface> InTrack);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcAudioTrackObserver.h` (Internal)


#### class `UPixelStreaming2AudioTrackObserver`  
`class UPixelStreaming2AudioTrackObserver : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2AudioTrackObserver`  
`class IPixelStreaming2AudioTrackObserver`  
_L20-28_
- L25 _public prototype_ `virtual void OnAudioTrackMuted(EpicRtcAudioTrackInterface* AudioTrack, EpicRtcBool bIsMuted) = 0;`
- L26 _public prototype_ `virtual void OnAudioTrackFrame(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcAudioFrame& Frame) = 0;`
- L27 _public prototype_ `virtual void OnAudioTrackState(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcTrackState State) = 0;`

#### class `UE::PixelStreaming2::FEpicRtcAudioTrackObserver`  
`class FEpicRtcAudioTrackObserver : public EpicRtcAudioTrackObserverInterface`  
_L32-52_
- inherits: `EpicRtcAudioTrackObserverInterface`
- L35 _public prototype_ `FEpicRtcAudioTrackObserver(TObserverVariant<IPixelStreaming2AudioTrackObserver> UserObserver);`
- L36 _public prototype_ `virtual ~FEpicRtcAudioTrackObserver() = default;`
- L40 _private prototype_ `virtual void OnAudioTrackMuted(EpicRtcAudioTrackInterface* AudioTrack, EpicRtcBool bIsMuted) override;`
- L41 _private prototype_ `virtual void OnAudioTrackFrame(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcAudioFrame& Frame) override;`
- L42 _private prototype_ `virtual void OnAudioTrackState(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcTrackState State) override;`
- L51 _private member_ `TObserverVariant<IPixelStreaming2AudioTrackObserver> UserObserver;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcAudioTrackObserverFactory.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcAudioTrackObserverFactory`  
`class FEpicRtcAudioTrackObserverFactory : public EpicRtcAudioTrackObserverFactoryInterface`  
_L16-34_
- inherits: `EpicRtcAudioTrackObserverFactoryInterface`
- L19 _public prototype_ `FEpicRtcAudioTrackObserverFactory(TObserverVariant<IPixelStreaming2AudioTrackObserver> UserObserver);`
- L20 _public prototype_ `virtual ~FEpicRtcAudioTrackObserverFactory() = default;`
- L24 _public prototype_ `virtual EpicRtcErrorCode CreateAudioTrackObserver(const EpicRtcStringView ParticipantId, const EpicRtcStringView AudioTrackId, EpicRtcAudioTrackObserverInterface** OutAudioTrackObserver) override;`
- L33 _private member_ `TObserverVariant<IPixelStreaming2AudioTrackObserver> UserObserver;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcCallstack.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcCallstack`  
`class FEpicRtcCallstack : public EpicRtcCallstackInterface`  
_L20-127_
- inherits: `EpicRtcCallstackInterface`
- L22 _private member_ `static constexpr bool USE_EPICRTC_PREFIX = false;`
- L23 _private member_ `static constexpr bool USE_EPICRTC_CHANNEL = true;`
- L25 _private function_ `virtual EpicRtcCallstackType SupportsEntryExit() const override`
- L47 _private function_ `static FString GetScopeString(const char* InScopeName)`
- L57 _private function_ `virtual void OnEntry(const char* InScopeName, EpicRtcCallstackType InType, void* volatile* InLocalStatic, uint8_t InLocalStackStorage[EpicRtcCallstackInterface::LOCALSTACK_BYTES]) override`
- L112 _private function_ `virtual void OnExit(EpicRtcCallstackType InType, uint8_t InLocalStackStorage[EpicRtcCallstackInterface::LOCALSTACK_BYTES]) override`

#### class `UE::PixelStreaming2::FEpicRtcCallstack::LocalLLMScope`  
`class LocalLLMScope`  
_L30-44_
- L33 _public function_ `LocalLLMScope(FName& ScopeName) : LLMScope(ScopeName, false, ELLMTagSet::None, ELLMTracker::Default) , MemScope(ScopeName)`
- L39 _public prototype_ `~LocalLLMScope() = default;`
- L42 _public member_ `FLLMScope LLMScope;` — UE Insights handles scope with multiple objects, so it's easier to wrap them into this class
- L43 _public member_ `FMemScope MemScope;`

#### Free symbols / members of external scopes

- L13 _prototype_ `UE_TRACE_CHANNEL_EXTERN(EpicRtcProfilingChannel);`
- L15 _macro_ `#define ENABLE_EPICRTC_TRACING (ENABLE_LOW_LEVEL_MEM_TRACKER && UE_MEMORY_TAGS_TRACE_ENABLED && UE_TRACE_ENABLED)`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcConferenceUtils.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcTickConferenceTask`  
`class FEpicRtcTickConferenceTask : public FPixelStreamingTickableTask`  
_L14-65_
- inherits: `FPixelStreamingTickableTask`
- L17 _public function_ `FEpicRtcTickConferenceTask(TRefCountPtr<EpicRtcConferenceInterface>& EpicRtcConference, const FString& TaskName = TEXT("EpicRtcTickConferenceTask")) : EpicRtcConference(EpicRtcConference) , TaskName(TaskName)`
- L23 _public function_ `virtual ~FEpicRtcTickConferenceTask() override`
- L38 _public function_ `virtual void Tick(float DeltaMs) override`
- L56 _public function_ `virtual const FString& GetName() const override`
- L63 _private member_ `TRefCountPtr<EpicRtcConferenceInterface> EpicRtcConference;`
- L64 _private member_ `FString TaskName;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcContainers.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcString`  
`class FEpicRtcString : public EpicRtcStringInterface`  
_L21-47_
- inherits: `EpicRtcStringInterface`
- L24 _public prototype_ `FEpicRtcString() = default;`
- L25 _public function_ `FEpicRtcString(const FString& String) : String(String)`
- L30 _public function_ `virtual const char* Get() const override`
- L35 _public function_ `virtual uint64_t Length() const override`
- L41 _private member_ `FUtf8String String;`

#### class `UE::PixelStreaming2::FEpicRtcEncodedVideoBuffer`  
`class FEpicRtcEncodedVideoBuffer : public EpicRtcEncodedVideoBufferInterface`  
_L49-69_
- inherits: `EpicRtcEncodedVideoBufferInterface`
- L52 _public prototype_ `FEpicRtcEncodedVideoBuffer() = default;`
- L53 _public function_ `FEpicRtcEncodedVideoBuffer(uint8_t* InData, uint64_t InSize) : Data(InData, InSize)`
- L57 _public prototype_ `virtual ~FEpicRtcEncodedVideoBuffer() = default;`
- L59 _public function_ `virtual const uint8_t* GetData() const override`
- L60 _public function_ `virtual uint64_t GetSize() const override`
- L63 _private member_ `TArray<uint8> Data;`

#### class `UE::PixelStreaming2::FEpicRtcParameterPair`  
`class FEpicRtcParameterPair : public EpicRtcParameterPairInterface`  
_L71-98_
- inherits: `EpicRtcParameterPairInterface`
- L74 _public function_ `FEpicRtcParameterPair(EpicRtcStringInterface* Key, EpicRtcStringInterface* Value) : Key(Key) , Value(Value)`
- L80 _public function_ `virtual EpicRtcStringInterface* GetKey() override`
- L85 _public function_ `virtual EpicRtcStringInterface* GetValue() override`
- L91 _private member_ `TRefCountPtr<EpicRtcStringInterface> Key;`
- L92 _private member_ `TRefCountPtr<EpicRtcStringInterface> Value;`

#### class `UE::PixelStreaming2::FEpicRtcParameterPairArray`  
`class FEpicRtcParameterPairArray : public EpicRtcParameterPairArrayInterface`  
_L100-186_
- inherits: `EpicRtcParameterPairArrayInterface`
- L103 _public prototype_ `FEpicRtcParameterPairArray() = default;`
- L105 _public function_ `virtual ~FEpicRtcParameterPairArray()`
- L116 _public function_ `FEpicRtcParameterPairArray(const TArray<TRefCountPtr<EpicRtcParameterPairInterface>>& ParameterPairs)`
- L128 _public function_ `FEpicRtcParameterPairArray(const TArray<EpicRtcParameterPairInterface*>& ParameterPairs)`
- L140 _public function_ `FEpicRtcParameterPairArray(std::initializer_list<EpicRtcParameterPairInterface*> ParameterPairs)`
- L152 _public function_ `virtual EpicRtcParameterPairInterface* const* Get() const override`
- L157 _public function_ `virtual EpicRtcParameterPairInterface** Get() override`
- L162 _public function_ `virtual uint64_t Size() const override`
- L167 _public function_ `void Append(std::initializer_list<EpicRtcParameterPairInterface*> ParameterPairs)`
- L180 _private member_ `TArray<EpicRtcParameterPairInterface*> Data;`

#### class `UE::PixelStreaming2::FEpicRtcScalabilityModeArray`  
`class FEpicRtcScalabilityModeArray : public EpicRtcVideoScalabilityModeArrayInterface`  
_L188-239_
- inherits: `EpicRtcVideoScalabilityModeArrayInterface`
- L191 _public prototype_ `FEpicRtcScalabilityModeArray() = default;`
- L192 _public prototype_ `virtual ~FEpicRtcScalabilityModeArray() = default;`
- L194 _public function_ `FEpicRtcScalabilityModeArray(const TArray<EpicRtcVideoScalabilityMode>& ScalabilityModes) : Data(ScalabilityModes)`
- L199 _public function_ `FEpicRtcScalabilityModeArray(std::initializer_list<EpicRtcVideoScalabilityMode> ScalabilityModes) : Data(ScalabilityModes)`
- L204 _public function_ `FEpicRtcScalabilityModeArray(const TArray<EScalabilityMode>& ScalabilityModes)`
- L212 _public function_ `virtual const EpicRtcVideoScalabilityMode* Get() const override`
- L217 _public function_ `virtual EpicRtcVideoScalabilityMode* Get() override`
- L222 _public function_ `virtual uint64_t Size() const override`
- L227 _public function_ `void Append(std::initializer_list<EpicRtcVideoScalabilityMode> ScalabilityModes)`
- L233 _private member_ `TArray<EpicRtcVideoScalabilityMode> Data;`

#### class `UE::PixelStreaming2::FEpicRtcVideoCodecInfo`  
`class FEpicRtcVideoCodecInfo : public EpicRtcVideoCodecInfoInterface`  
_L241-277_
- inherits: `EpicRtcVideoCodecInfoInterface`
- L244 _public function_ `FEpicRtcVideoCodecInfo(EpicRtcVideoCodec Codec, EpicRtcParameterPairArrayInterface* Parameters = new FEpicRtcParameterPairArray(), EpicRtcVideoScalabilityModeArrayInterface* ScalabilityModes = new FEpicRtcScalabilityModeArray()) : Codec(Codec) , Parameters(Parameters) , ScalabilityModes(ScalabilityModes)`
- L251 _public prototype_ `virtual ~FEpicRtcVideoCodecInfo() = default;`
- L253 _public function_ `EpicRtcVideoCodec GetCodec() override`
- L258 _public function_ `virtual EpicRtcParameterPairArrayInterface* GetParameters() override`
- L263 _public function_ `EpicRtcVideoScalabilityModeArrayInterface* GetScalabilityModes() override`
- L269 _private member_ `EpicRtcVideoCodec Codec;`
- L270 _private member_ `TRefCountPtr<EpicRtcParameterPairArrayInterface> Parameters;`
- L271 _private member_ `TRefCountPtr<EpicRtcVideoScalabilityModeArrayInterface> ScalabilityModes;`

#### class `UE::PixelStreaming2::FVideoCodecInfoArray`  
`class FVideoCodecInfoArray : public EpicRtcVideoCodecInfoArrayInterface`  
_L279-353_
- inherits: `EpicRtcVideoCodecInfoArrayInterface`
- L282 _public prototype_ `FVideoCodecInfoArray() = default;`
- L284 _public function_ `virtual ~FVideoCodecInfoArray()`
- L295 _public function_ `FVideoCodecInfoArray(const TArray<TRefCountPtr<EpicRtcVideoCodecInfoInterface>>& Codecs)`
- L307 _public function_ `FVideoCodecInfoArray(const TArray<EpicRtcVideoCodecInfoInterface*>& Codecs)`
- L319 _public function_ `FVideoCodecInfoArray(std::initializer_list<EpicRtcVideoCodecInfoInterface*> Codecs)`
- L331 _public function_ `virtual EpicRtcVideoCodecInfoInterface* const* Get() const override`
- L336 _public function_ `virtual EpicRtcVideoCodecInfoInterface** Get() override`
- L341 _public function_ `virtual uint64_t Size() const override`
- L347 _private member_ `TArray<EpicRtcVideoCodecInfoInterface*> Data;`

#### class `UE::PixelStreaming2::FEpicRtcVideoResolutionBitrateLimitsArray`  
`class FEpicRtcVideoResolutionBitrateLimitsArray : public EpicRtcVideoResolutionBitrateLimitsArrayInterface`  
_L355-393_
- inherits: `EpicRtcVideoResolutionBitrateLimitsArrayInterface`
- L358 _public prototype_ `FEpicRtcVideoResolutionBitrateLimitsArray() = default;`
- L359 _public prototype_ `virtual ~FEpicRtcVideoResolutionBitrateLimitsArray() = default;`
- L361 _public function_ `FEpicRtcVideoResolutionBitrateLimitsArray(const TArray<EpicRtcVideoResolutionBitrateLimits>& BitrateLimits) : Data(BitrateLimits)`
- L366 _public function_ `FEpicRtcVideoResolutionBitrateLimitsArray(std::initializer_list<EpicRtcVideoResolutionBitrateLimits> BitrateLimits) : Data(BitrateLimits)`
- L371 _public function_ `virtual const EpicRtcVideoResolutionBitrateLimits* Get() const override`
- L376 _public function_ `virtual EpicRtcVideoResolutionBitrateLimits* Get() override`
- L381 _public function_ `virtual uint64_t Size() const override`
- L387 _private member_ `TArray<EpicRtcVideoResolutionBitrateLimits> Data;`

#### class `UE::PixelStreaming2::FEpicRtcPixelFormatArray`  
`class FEpicRtcPixelFormatArray : public EpicRtcPixelFormatArrayInterface`  
_L395-433_
- inherits: `EpicRtcPixelFormatArrayInterface`
- L398 _public prototype_ `FEpicRtcPixelFormatArray() = default;`
- L399 _public prototype_ `virtual ~FEpicRtcPixelFormatArray() = default;`
- L401 _public function_ `FEpicRtcPixelFormatArray(const TArray<EpicRtcPixelFormat>& PixelFormats) : Data(PixelFormats)`
- L406 _public function_ `FEpicRtcPixelFormatArray(std::initializer_list<EpicRtcPixelFormat> PixelFormats) : Data(PixelFormats)`
- L411 _public function_ `virtual const EpicRtcPixelFormat* Get() const override`
- L416 _public function_ `virtual EpicRtcPixelFormat* Get() override`
- L421 _public function_ `virtual uint64_t Size() const override`
- L427 _private member_ `TArray<EpicRtcPixelFormat> Data;`

#### class `UE::PixelStreaming2::FEpicRtcVideoFrameTypeArray`  
`class FEpicRtcVideoFrameTypeArray : public EpicRtcVideoFrameTypeArrayInterface`  
_L435-468_
- inherits: `EpicRtcVideoFrameTypeArrayInterface`
- L438 _public prototype_ `FEpicRtcVideoFrameTypeArray() = default;`
- L439 _public prototype_ `virtual ~FEpicRtcVideoFrameTypeArray() = default;`
- L441 _public function_ `FEpicRtcVideoFrameTypeArray(const TArray<EpicRtcVideoFrameType>& FrameTypes) : Data(FrameTypes)`
- L446 _public function_ `FEpicRtcVideoFrameTypeArray(std::initializer_list<EpicRtcVideoFrameType> FrameTypes) : Data(FrameTypes)`
- L451 _public function_ `virtual const EpicRtcVideoFrameType* Get() const override`
- L456 _public function_ `virtual uint64_t Size() const override`
- L462 _private member_ `TArray<EpicRtcVideoFrameType> Data;`

#### class `UE::PixelStreaming2::FEpicRtcInt32Array`  
`class FEpicRtcInt32Array : public EpicRtcInt32ArrayInterface`  
_L470-513_
- inherits: `EpicRtcInt32ArrayInterface`
- L473 _public prototype_ `FEpicRtcInt32Array() = default;`
- L474 _public prototype_ `virtual ~FEpicRtcInt32Array() = default;`
- L476 _public function_ `FEpicRtcInt32Array(const TArray<int32_t>& Ints) : Data(Ints)`
- L481 _public function_ `FEpicRtcInt32Array(std::initializer_list<int32_t> Ints) : Data(Ints)`
- L486 _public function_ `virtual const int32_t* Get() const override`
- L491 _public function_ `virtual int32_t* Get() override`
- L496 _public function_ `virtual uint64_t Size() const override`
- L501 _public function_ `void Append(std::initializer_list<int32_t> Ints)`
- L507 _private member_ `TArray<int32_t> Data;`

#### class `UE::PixelStreaming2::FEpicRtcBoolArray`  
`class FEpicRtcBoolArray : public EpicRtcBoolArrayInterface`  
_L515-570_
- inherits: `EpicRtcBoolArrayInterface`
- L518 _public prototype_ `FEpicRtcBoolArray() = default;`
- L519 _public prototype_ `virtual ~FEpicRtcBoolArray() = default;`
- L521 _public function_ `FEpicRtcBoolArray(const TArray<EpicRtcBool>& Bools) : Data(Bools)`
- L526 _public function_ `FEpicRtcBoolArray(const TArray<bool>& Bools)`
- L535 _public function_ `FEpicRtcBoolArray(std::initializer_list<EpicRtcBool> Bools) : Data(Bools)`
- L540 _public function_ `FEpicRtcBoolArray(std::initializer_list<bool> Bools)`
- L548 _public function_ `virtual const EpicRtcBool* Get() const override`
- L553 _public function_ `virtual EpicRtcBool* Get() override`
- L558 _public function_ `virtual uint64_t Size() const override`
- L564 _private member_ `TArray<EpicRtcBool> Data;`

#### class `UE::PixelStreaming2::FEpicRtcDecodeTargetIndicationArray`  
`class FEpicRtcDecodeTargetIndicationArray : public EpicRtcDecodeTargetIndicationArrayInterface`  
_L572-637_
- inherits: `EpicRtcDecodeTargetIndicationArrayInterface`
- L575 _public prototype_ `FEpicRtcDecodeTargetIndicationArray() = default;`
- L576 _public prototype_ `virtual ~FEpicRtcDecodeTargetIndicationArray() = default;`
- L578 _public function_ `FEpicRtcDecodeTargetIndicationArray(const TArray<EpicRtcDecodeTargetIndication>& DecodeTargetIndications) : Data(DecodeTargetIndications)`
- L583 _public function_ `FEpicRtcDecodeTargetIndicationArray(std::initializer_list<EpicRtcDecodeTargetIndication> DecodeTargetIndications) : Data(DecodeTargetIndications)`
- L589 _public function_ `FEpicRtcDecodeTargetIndicationArray(const TArray<EDecodeTargetIndication>& DecodeTargetIndications)` — Helper method for converting array AVCodecs' EDecodeTargetIndication to array of EpicRtc's EpicRtcDecodeTargetIndication
- L615 _public function_ `virtual const EpicRtcDecodeTargetIndication* Get() const override`
- L620 _public function_ `virtual EpicRtcDecodeTargetIndication* Get() override`
- L625 _public function_ `virtual uint64_t Size() const override`
- L631 _private member_ `TArray<EpicRtcDecodeTargetIndication> Data;`

#### class `UE::PixelStreaming2::FEpicRtcCodecBufferUsageArray`  
`class FEpicRtcCodecBufferUsageArray : public EpicRtcCodecBufferUsageArrayInterface`  
_L639-692_
- inherits: `EpicRtcCodecBufferUsageArrayInterface`
- L642 _public prototype_ `FEpicRtcCodecBufferUsageArray() = default;`
- L643 _public prototype_ `virtual ~FEpicRtcCodecBufferUsageArray() = default;`
- L645 _public function_ `FEpicRtcCodecBufferUsageArray(const TArray<EpicRtcCodecBufferUsage>& CodecBufferUsages) : Data(CodecBufferUsages)`
- L650 _public function_ `FEpicRtcCodecBufferUsageArray(std::initializer_list<EpicRtcCodecBufferUsage> CodecBufferUsages) : Data(CodecBufferUsages)`
- L656 _public function_ `FEpicRtcCodecBufferUsageArray(const TArray<FCodecBufferUsage>& CodecBufferUsages)` — Helper method for converting array AVCodecs' FCodecBufferUsage to array of EpicRtc's EpicRtcCodecBufferUsage
- L670 _public function_ `virtual const EpicRtcCodecBufferUsage* Get() const override`
- L675 _public function_ `virtual EpicRtcCodecBufferUsage* Get() override`
- L680 _public function_ `virtual uint64_t Size() const override`
- L686 _private member_ `TArray<EpicRtcCodecBufferUsage> Data;`

#### class `UE::PixelStreaming2::FEpicRtcVideoResolutionArray`  
`class FEpicRtcVideoResolutionArray : public EpicRtcVideoResolutionArrayInterface`  
_L694-746_
- inherits: `EpicRtcVideoResolutionArrayInterface`
- L697 _public prototype_ `FEpicRtcVideoResolutionArray() = default;`
- L698 _public prototype_ `virtual ~FEpicRtcVideoResolutionArray() = default;`
- L700 _public function_ `FEpicRtcVideoResolutionArray(const TArray<EpicRtcVideoResolution>& Resolutions) : Data(Resolutions)`
- L705 _public function_ `FEpicRtcVideoResolutionArray(std::initializer_list<EpicRtcVideoResolution> Resolutions) : Data(Resolutions)`
- L711 _public function_ `FEpicRtcVideoResolutionArray(const TArray<FIntPoint>& Resolutions)` — Helper method for converting array AVCodecs' FResolution to array of EpicRtc's EpicRtcVideoResolution
- L724 _public function_ `virtual const EpicRtcVideoResolution* Get() const override`
- L729 _public function_ `virtual EpicRtcVideoResolution* Get() override`
- L734 _public function_ `virtual uint64_t Size() const override`
- L740 _private member_ `TArray<EpicRtcVideoResolution> Data;`

#### class `UE::PixelStreaming2::FEpicRtcGenericFrameInfoArray`  
`class FEpicRtcGenericFrameInfoArray : public EpicRtcGenericFrameInfoArrayInterface`  
_L748-822_
- inherits: `EpicRtcGenericFrameInfoArrayInterface`
- L751 _public prototype_ `FEpicRtcGenericFrameInfoArray() = default;`
- L753 _public function_ `virtual ~FEpicRtcGenericFrameInfoArray()`
- L764 _public function_ `FEpicRtcGenericFrameInfoArray(const TArray<TRefCountPtr<EpicRtcGenericFrameInfoInterface>>& GenericFrameInfos)`
- L776 _public function_ `FEpicRtcGenericFrameInfoArray(const TArray<EpicRtcGenericFrameInfoInterface*>& GenericFrameInfos)`
- L788 _public function_ `FEpicRtcGenericFrameInfoArray(std::initializer_list<EpicRtcGenericFrameInfoInterface*> GenericFrameInfos)`
- L800 _public function_ `virtual EpicRtcGenericFrameInfoInterface* const* Get() const override`
- L805 _public function_ `virtual EpicRtcGenericFrameInfoInterface** Get() override`
- L810 _public function_ `virtual uint64_t Size() const override`
- L816 _private member_ `TArray<EpicRtcGenericFrameInfoInterface*> Data;`

#### class `UE::PixelStreaming2::FEpicRtcGenericFrameInfo`  
`class FEpicRtcGenericFrameInfo : public EpicRtcGenericFrameInfoInterface`  
_L824-864_
- inherits: `EpicRtcGenericFrameInfoInterface`
- L827 _public function_ `FEpicRtcGenericFrameInfo(const FGenericFrameInfo& GenericFrameInfo) : SpatialId(GenericFrameInfo.SpatialId) , TemporalId(GenericFrameInfo.TemporalId) , DecodeTargetIndications(MakeRefCount<FEpicRtcDecodeTargetIndicationArray>(GenericFrameInfo.DecodeTargetIndications)) , FrameDiffs(MakeRefCount<FEpicRtcInt32Array>(GenericFrameInfo.FrameDiffs)) , ChainDiffs(MakeRefCount<FEpicRtcInt32Array>(GenericFrameInfo.ChainDiffs)) , EncoderBuffers(MakeRefCount<FEpicRtcCodecBufferUsageArray>(GenericFrameInfo.EncoderBuffers)) , PartOfChain(MakeRefCount<FEpicRtcBoolArray>(GenericFrameInfo.PartOfChain)) , ActiveDecodeTargets(MakeRefCount<FEpicRtcBoolArray>(GenericFrameInfo.ActiveDecodeTargets))`
- L839 _public prototype_ `virtual ~FEpicRtcGenericFrameInfo() = default;`
- L841 _public function_ `virtual int32_t GetSpatialLayerId() override`
- L842 _public function_ `virtual int32_t GetTemporalLayerId() override`
- L843 _public function_ `virtual EpicRtcDecodeTargetIndicationArrayInterface* GetDecodeTargetIndications() override`
- L844 _public function_ `virtual EpicRtcInt32ArrayInterface* GetFrameDiffs() override`
- L845 _public function_ `virtual EpicRtcInt32ArrayInterface* GetChainDiffs() override`
- L846 _public function_ `virtual EpicRtcCodecBufferUsageArrayInterface* GetEncoderBufferUsages() override`
- L847 _public function_ `virtual EpicRtcBoolArrayInterface* GetPartOfChain() override`
- L848 _public function_ `virtual EpicRtcBoolArrayInterface* GetActiveDecodeTargets() override`
- L851 _private member_ `int32_t SpatialId;`
- L852 _private member_ `int32_t TemporalId;`
- L853 _private member_ `TRefCountPtr<FEpicRtcDecodeTargetIndicationArray> DecodeTargetIndications;`
- L854 _private member_ `TRefCountPtr<FEpicRtcInt32Array> FrameDiffs;`
- L855 _private member_ `TRefCountPtr<FEpicRtcInt32Array> ChainDiffs;`
- L856 _private member_ `TRefCountPtr<FEpicRtcCodecBufferUsageArray> EncoderBuffers;`
- L857 _private member_ `TRefCountPtr<FEpicRtcBoolArray> PartOfChain;`
- L858 _private member_ `TRefCountPtr<FEpicRtcBoolArray> ActiveDecodeTargets;`

#### class `UE::PixelStreaming2::FEpicRtcFrameDependencyStructure`  
`class FEpicRtcFrameDependencyStructure : public EpicRtcFrameDependencyStructure`  
_L866-933_
- inherits: `EpicRtcFrameDependencyStructure`
- L869 _public function_ `FEpicRtcFrameDependencyStructure(const FFrameDependencyStructure& FrameDependencyStructure) : StructureId(FrameDependencyStructure.StructureId) , NumDecodeTargets(FrameDependencyStructure.NumDecodeTargets) , NumChains(FrameDependencyStructure.NumChains) , DecodeTargetProtectedByChain(MakeRefCount<FEpicRtcInt32Array>(FrameDependencyStructure.DecodeTargetProtectedByChain)) , Resolutions(MakeRefCount<FEpicRtcVideoResolutionArray>(FrameDependencyStructure.Resolutions))`
- L894 _public prototype_ `virtual ~FEpicRtcFrameDependencyStructure() = default;`
- L896 _public function_ `virtual int32_t GetStructureId() override`
- L897 _public function_ `virtual int32_t GetNumDecodeTargets() override`
- L898 _public function_ `virtual int32_t GetNumChains() override`
- L899 _public function_ `virtual EpicRtcInt32ArrayInterface* GetDecodeTargetProtectedByChain() override`
- L900 _public function_ `virtual EpicRtcVideoResolutionArrayInterface* GetResolutions() override`
- L901 _public function_ `virtual EpicRtcGenericFrameInfoArrayInterface* GetTemplates() override`
- L922 _private member_ `int StructureId;`
- L923 _private member_ `int NumDecodeTargets;`
- L924 _private member_ `int NumChains;`
- L925 _private member_ `TRefCountPtr<FEpicRtcInt32Array> DecodeTargetProtectedByChain;`
- L926 _private member_ `TRefCountPtr<FEpicRtcVideoResolutionArray> Resolutions;`
- L927 _private member_ `TRefCountPtr<FEpicRtcGenericFrameInfoArray> Templates;`

#### class `UE::PixelStreaming2::FEpicRtcSignallingJoinOptionsArray`  
`class FEpicRtcSignallingJoinOptionsArray : public EpicRtcSignallingJoinOptionsArrayInterface`  
_L935-973_
- inherits: `EpicRtcSignallingJoinOptionsArrayInterface`
- L938 _public prototype_ `FEpicRtcSignallingJoinOptionsArray() = default;`
- L939 _public prototype_ `virtual ~FEpicRtcSignallingJoinOptionsArray() = default;`
- L941 _public function_ `FEpicRtcSignallingJoinOptionsArray(const TArray<EpicRtcSignallingJoinOptions>& SignallingJoinOptions) : Data(SignallingJoinOptions)`
- L946 _public function_ `FEpicRtcSignallingJoinOptionsArray(std::initializer_list<EpicRtcSignallingJoinOptions> SignallingJoinOptions) : Data(SignallingJoinOptions)`
- L951 _public function_ `virtual const EpicRtcSignallingJoinOptions* Get() const override`
- L956 _public function_ `virtual EpicRtcSignallingJoinOptions* Get() override`
- L961 _public function_ `virtual uint64_t Size() const override`
- L967 _private member_ `TArray<EpicRtcSignallingJoinOptions> Data;`

#### Free symbols / members of external scopes

- L14 _function_ `FORCEINLINE bool operator==(const EpicRtcVideoResolution& Lhs, const EpicRtcVideoResolution& Rhs)`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L903 _function_ `friend bool operator==(FEpicRtcFrameDependencyStructure& Lhs, FEpicRtcFrameDependencyStructure& Rhs)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcDataTrack.h` (Internal)


#### struct `UE::PixelStreaming2::FBufferBuilder`  
`struct FBufferBuilder`  
_L65-96_
- L67 _public member_ `TArray<uint8> Buffer;`
- L68 _public member_ `size_t Pos;`
- L70 _public function_ `FBufferBuilder(size_t size) : Pos(0)`
- L76 _public function_ `size_t Serialize(const void* Data, size_t DataSize)`
- L84 _public function_ `template <typename T> void Insert(const T&& Value)`

#### class `UE::PixelStreaming2::FEpicRtcDataTrack`  
`class FEpicRtcDataTrack : public TEpicRtcTrack<EpicRtcDataTrackInterface>, public TSharedFromThis<FEpicRtcDataTrack>`  
_L98-180_
- inherits: `TEpicRtcTrack<EpicRtcDataTrackInterface>,TSharedFromThis<FEpicRtcDataTrack>`
- L101 _public prototype_ `static TSharedPtr<FEpicRtcDataTrack> Create(TRefCountPtr<EpicRtcDataTrackInterface> InTrack, TWeakPtr<IPixelStreaming2DataProtocol> InDataProtocol);`
- L103 _public prototype_ `virtual ~FEpicRtcDataTrack() = default;`
- L105 _public function_ `void SetDataProtocol(TWeakPtr<IPixelStreaming2DataProtocol> InDataProtocol)`
- L116 _public function_ `template <typename... Args> bool SendMessage(FString MessageType, Args... VarArgs) const` — Sends a series of arguments to the data channel with the given type. @param MessageType The name of the message you want to send. This message name must be registered IPixelStreaming2InputHandler::GetFromStreamerProtocol(). @returns True of the message was successfully sent.
- L140 _public prototype_ `bool SendArbitraryData(const FString& MessageType, const TArray64<uint8>& DataBytes) const;` — Sends a large buffer of data to the data track, will chunk into multiple data frames if frames greater than 16KB. @param MessageType The name of the message, it must be registered in IPixelStreaming2InputHandler::GetTo/FromStreamerProtocol() @param DataBytes The raw byte buffer to send. @returns True of the message was successfully sent.
- L145 _public function_ `EpicRtcTrackState GetState() const` — @return The state of the underlying EpicRtc data track.
- L147 _public function_ `void SetSendTrack(TRefCountPtr<EpicRtcDataTrackInterface> InSendTrack)`
- L150 _protected prototype_ `FEpicRtcDataTrack(TRefCountPtr<EpicRtcDataTrackInterface> InTrack, TWeakPtr<IPixelStreaming2DataProtocol> InDataProtocol);`
- L151 _protected prototype_ `FEpicRtcDataTrack(TSharedPtr<FEpicRtcDataTrack> InTrack, TWeakPtr<IPixelStreaming2DataProtocol> InDataProtocol);`
- L153 _protected function_ `virtual void PrependData(FBufferBuilder& Builder) const`
- L155 _protected prototype_ `bool IsActive() const;`
- L157 _protected prototype_ `bool GetMessageId(const FString& MessageType, uint8& OutMessageId) const;`
- L163 _private member_ `TRefCountPtr<EpicRtcDataTrackInterface> SendTrack;` — Track that is used for sending data with Consumer/Producer architecture.
- L165 _private member_ `TWeakPtr<IPixelStreaming2DataProtocol> WeakDataProtocol;`
- L167 _private prototype_ `bool Send(TArray<uint8>& Buffer) const;`
- L170 _private function_ `template <typename... Args> FBufferBuilder EncodeMessage(uint8 Type, Args... VarArgs) const`

#### class `UE::PixelStreaming2::FEpicRtcMutliplexDataTrack`  
`class FEpicRtcMutliplexDataTrack : public FEpicRtcDataTrack`  
_L182-194_
- inherits: `FEpicRtcDataTrack`
- L185 _public prototype_ `static TSharedPtr<FEpicRtcMutliplexDataTrack> Create(TSharedPtr<FEpicRtcDataTrack> InTrack, TWeakPtr<IPixelStreaming2DataProtocol> InDataProtocol, const FString& InPlayerId);`
- L188 _protected prototype_ `FEpicRtcMutliplexDataTrack(TSharedPtr<FEpicRtcDataTrack> InTrack, TWeakPtr<IPixelStreaming2DataProtocol> InDataProtocol, const FString& InPlayerId);`
- L190 _protected prototype_ `virtual void PrependData(FBufferBuilder& Builder) const override;`
- L193 _private member_ `const FString PlayerId;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L14 _function_ `template <typename T> inline size_t GetByteSizeOf(const T&& Value)` (scope `UE::PixelStreaming2`)
- L23 _function_ `template <typename T> inline const void* GetDataPointer(const T&& Value)` (scope `UE::PixelStreaming2`)
- L31 _function_ `inline size_t GetByteSizeOf(const FString&& Value)` (scope `UE::PixelStreaming2`)
- L39 _function_ `inline const void* GetDataPointer(const FString&& Value)` (scope `UE::PixelStreaming2`)
- L48 _function_ `template <typename T> inline size_t GetByteSizeOf(const TArray<T>&& Value)` (scope `UE::PixelStreaming2`)
- L57 _function_ `template <typename T> inline const void* GetDataPointer(const TArray<T>&& Value)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcDataTrackObserver.h` (Internal)


#### class `UPixelStreaming2DataTrackObserver`  
`class UPixelStreaming2DataTrackObserver : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2DataTrackObserver`  
`class IPixelStreaming2DataTrackObserver`  
_L20-28_
- L25 _public prototype_ `virtual void OnDataTrackState(EpicRtcDataTrackInterface* DataTrack, const EpicRtcTrackState State) = 0;`
- L26 _public prototype_ `virtual void OnDataTrackMessage(EpicRtcDataTrackInterface* DataTrack, const EpicRtcDataFrame& DataFrame) = 0;`
- L27 _public prototype_ `virtual void OnDataTrackError(EpicRtcDataTrackInterface*, const EpicRtcErrorCode) = 0;`

#### class `UE::PixelStreaming2::FEpicRtcDataTrackObserver`  
`class FEpicRtcDataTrackObserver : public EpicRtcDataTrackObserverInterface`  
_L32-52_
- inherits: `EpicRtcDataTrackObserverInterface`
- L35 _public prototype_ `FEpicRtcDataTrackObserver(TObserverVariant<IPixelStreaming2DataTrackObserver> UserObserver);`
- L36 _public prototype_ `virtual ~FEpicRtcDataTrackObserver() = default;`
- L40 _private prototype_ `virtual void OnDataTrackState(EpicRtcDataTrackInterface* DataTrack, const EpicRtcTrackState State) override;`
- L41 _private prototype_ `virtual void OnDataTrackMessage(EpicRtcDataTrackInterface* DataTrack, const EpicRtcDataFrame& DataFrame) override;`
- L42 _private prototype_ `virtual void OnDataTrackError(EpicRtcDataTrackInterface*, const EpicRtcErrorCode) override;`
- L51 _private member_ `TObserverVariant<IPixelStreaming2DataTrackObserver> UserObserver;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcDataTrackObserverFactory.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcDataTrackObserverFactory`  
`class FEpicRtcDataTrackObserverFactory : public EpicRtcDataTrackObserverFactoryInterface`  
_L16-34_
- inherits: `EpicRtcDataTrackObserverFactoryInterface`
- L19 _public prototype_ `FEpicRtcDataTrackObserverFactory(TObserverVariant<IPixelStreaming2DataTrackObserver> UserObserver);`
- L20 _public prototype_ `virtual ~FEpicRtcDataTrackObserverFactory() = default;`
- L24 _public prototype_ `virtual EpicRtcErrorCode CreateDataTrackObserver(const EpicRtcStringView ParticipantId, const EpicRtcStringView DataTrackId, EpicRtcDataTrackObserverInterface** OutDataTrackObserver) override;`
- L33 _private member_ `TObserverVariant<IPixelStreaming2DataTrackObserver> UserObserver;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcLogging.h` (Internal)


#### class `UE::PixelStreaming2::ILogManipulator`  
`class ILogManipulator`  
_L47-60_
- desc: An interface providing functionality for manipulating EpicRtc logs. This includes completely removing log messages by checking IsFiltered() or by redacting sensitive information using Censor()
- L50 _public prototype_ `virtual ~ILogManipulator() = default;`
- L57 _public prototype_ `virtual bool IsFiltered(ELogVerbosity::Type LogVerbosity, const FString& LogString) = 0;` — Checks if a log message should or shouldn't be logged. @return true is the log message is filtered and shouldn't be displayed
- L59 _public prototype_ `virtual FString Censor(ELogVerbosity::Type LogVerbosity, const FString& LogString) = 0;`

#### class `UE::PixelStreaming2::FEpicRtcLogFilter`  
`class FEpicRtcLogFilter : public ILogManipulator`  
_L62-84_
- inherits: `ILogManipulator`
- L66 _public prototype_ `FEpicRtcLogFilter();` — Default constructor. Populates the contents of RegexPatterns with values from CVarEpicRtcLogFilter
- L68 _public prototype_ `FEpicRtcLogFilter(const TArray<FRegexPattern>& RegexPatterns);` — Alternate constructor that takes in a pre-populated array. Used for internal testing
- L70 _public prototype_ `virtual ~FEpicRtcLogFilter();`
- L72 _public prototype_ `virtual bool IsFiltered(ELogVerbosity::Type LogVerbosity, const FString& LogString) override;`
- L74 _public function_ `virtual FString Censor(ELogVerbosity::Type LogVerbosity, const FString& LogString) override`
- L77 _private prototype_ `void OnEpicRtcLogFilterChanged(IConsoleVariable* Var);`
- L78 _private prototype_ `void ParseFilterString(const FString& LogFilterString);`
- L81 _private member_ `TArray<FRegexPattern> RegexPatterns;`
- L83 _private member_ `FDelegateHandle EpicRtcLogFilterChangedHandle;`

#### class `UE::PixelStreaming2::FEpicRtcLogsRedirector`  
`class FEpicRtcLogsRedirector : public EpicRtcLoggerInterface`  
_L86-100_
- inherits: `EpicRtcLoggerInterface`
- L89 _public prototype_ `FEpicRtcLogsRedirector(TSharedPtr<ILogManipulator> LogManipulator = nullptr);`
- L91 _public prototype_ `virtual void Log(const EpicRtcLogMessage& Message) override;`
- L94 _private member_ `TSharedPtr<ILogManipulator> LogManipulator;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2EpicRtc, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2WebRtc, Fatal, All);`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L19 _variable_ `constexpr EpicRtcLogLevel UnrealLogToEpicRtcCategoryMap[] = { EpicRtcLogLevel::Off, EpicRtcLogLevel::Critical, EpicRtcLogLevel::Error, EpicRtcLogLevel::Warning, EpicRtcLogLevel::Info, EpicRtcLogLevel::Info, EpicRtcLogLevel::Debug, EpicRtcLogLevel::Trace, EpicRtcLogLevel::Trace };` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcObserver.h` (Internal)


#### class `UE::PixelStreaming2::TObserverVariant`  
`template <typename T> class TObserverVariant`  
_L15-73_
- L18 _public prototype_ `TObserverVariant() = default;`
- L20 _public function_ `TObserverVariant(TVariant<TYPE_OF_NULLPTR, TWeakPtr<T>, TWeakInterfacePtr<T>> ObserverVariant) : ObserverVariant(ObserverVariant)`
- L25 _public function_ `T* operator->() const`
- L53 _public function_ `operator bool() const`
- L72 _private member_ `TVariant<TYPE_OF_NULLPTR, TWeakPtr<T>, TWeakInterfacePtr<T>> ObserverVariant;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L76 _function_ `template <typename T> inline TObserverVariant<T> TObserver(TWeakPtr<T> WeakObserver)` (scope `UE::PixelStreaming2`)
- L82 _function_ `template <typename T> inline TObserverVariant<T> TObserver(TWeakInterfacePtr<T> WeakObserver)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcPlatform.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcAndroidPlatform`  
`class FEpicRtcAndroidPlatform : public EpicRtcAndroidPlatformInterface`  
_L19-24_
- inherits: `EpicRtcAndroidPlatformInterface`
- L21 _private prototype_ `virtual JavaVM* GetJavaVM() override;`
- L23 _private prototype_ `virtual ~FEpicRtcAndroidPlatform() = default;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcRoomObserver.h` (Internal)


#### class `UPixelStreaming2RoomObserver`  
`class UPixelStreaming2RoomObserver : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2RoomObserver`  
`class IPixelStreaming2RoomObserver`  
_L20-34_
- L25 _public prototype_ `virtual void OnRoomStateUpdate(const EpicRtcRoomState State) = 0;`
- L26 _public prototype_ `virtual void OnRoomJoinedUpdate(EpicRtcParticipantInterface* Participant) = 0;`
- L27 _public prototype_ `virtual void OnRoomLeftUpdate(const EpicRtcStringView ParticipantId) = 0;`
- L28 _public prototype_ `virtual void OnAudioTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcAudioTrackInterface* AudioTrack) = 0;`
- L29 _public prototype_ `virtual void OnVideoTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcVideoTrackInterface* VideoTrack) = 0;`
- L30 _public prototype_ `virtual void OnDataTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcDataTrackInterface* DataTrack) = 0;`
- L31 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnLocalSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) = 0;`
- L32 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnRemoteSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) = 0;`
- L33 _public prototype_ `virtual void OnRoomErrorUpdate(const EpicRtcErrorCode Error) = 0;`

#### class `UE::PixelStreaming2::FEpicRtcRoomObserver`  
`class FEpicRtcRoomObserver : public EpicRtcRoomObserverInterface`  
_L38-64_
- inherits: `EpicRtcRoomObserverInterface`
- L41 _public prototype_ `FEpicRtcRoomObserver(TObserverVariant<IPixelStreaming2RoomObserver> UserObserver);`
- L42 _public prototype_ `virtual ~FEpicRtcRoomObserver() = default;`
- L46 _private prototype_ `virtual void OnRoomStateUpdate(const EpicRtcRoomState State) override;`
- L47 _private prototype_ `virtual void OnRoomJoinedUpdate(EpicRtcParticipantInterface* Participant) override;`
- L48 _private prototype_ `virtual void OnRoomLeftUpdate(const EpicRtcStringView ParticipantId) override;`
- L49 _private prototype_ `virtual void OnAudioTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcAudioTrackInterface* AudioTrack) override;`
- L50 _private prototype_ `virtual void OnVideoTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcVideoTrackInterface* VideoTrack) override;`
- L51 _private prototype_ `virtual void OnDataTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcDataTrackInterface* DataTrack) override;`
- L52 _private prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnLocalSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L53 _private prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnRemoteSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L54 _private prototype_ `virtual void OnRoomErrorUpdate(const EpicRtcErrorCode Error) override;`
- L63 _private member_ `TObserverVariant<IPixelStreaming2RoomObserver> UserObserver;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcSessionObserver.h` (Internal)


#### class `UPixelStreaming2SessionObserver`  
`class UPixelStreaming2SessionObserver : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2SessionObserver`  
`class IPixelStreaming2SessionObserver`  
_L20-28_
- L25 _public prototype_ `virtual void OnSessionStateUpdate(const EpicRtcSessionState State) = 0;`
- L26 _public prototype_ `virtual void OnSessionErrorUpdate(const EpicRtcErrorCode Error) = 0;`
- L27 _public prototype_ `virtual void OnSessionRoomsAvailableUpdate(EpicRtcStringArrayInterface* RoomsList) = 0;`

#### class `UE::PixelStreaming2::FEpicRtcSessionObserver`  
`class FEpicRtcSessionObserver : public EpicRtcSessionObserverInterface`  
_L32-50_
- inherits: `EpicRtcSessionObserverInterface`
- L35 _public prototype_ `FEpicRtcSessionObserver(TObserverVariant<IPixelStreaming2SessionObserver> UserObserver);`
- L36 _public prototype_ `virtual ~FEpicRtcSessionObserver() = default;`
- L40 _private prototype_ `virtual void OnSessionStateUpdate(const EpicRtcSessionState State) override;`
- L41 _private prototype_ `virtual void OnSessionErrorUpdate(const EpicRtcErrorCode Error) override;`
- L42 _private prototype_ `virtual void OnSessionRoomsAvailableUpdate(EpicRtcStringArrayInterface* RoomsList) override;`
- L49 _private member_ `TObserverVariant<IPixelStreaming2SessionObserver> UserObserver;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcStatsCollector.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcStatsCollector`  
`class FEpicRtcStatsCollector : public EpicRtcStatsCollectorCallbackInterface`  
_L16-33_
- inherits: `EpicRtcStatsCollectorCallbackInterface`
- L19 _public prototype_ `FEpicRtcStatsCollector() = default;`
- L20 _public prototype_ `~FEpicRtcStatsCollector() = default;`
- L23 _public prototype_ `void OnStatsDelivered(const EpicRtcStatsReport& InReport) override;`
- L31 _public prototype_ `DECLARE_EVENT_TwoParams(FEpicRtcStatsCollector, FOnStatsReady, const FString&, const EpicRtcConnectionStats&);`
- L32 _public member_ `FOnStatsReady OnStatsReady;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L31 _delegate_ `DECLARE_EVENT_TwoParams(FEpicRtcStatsCollector, FOnStatsReady, const FString&, const EpicRtcConnectionStats&);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcTrace.h` (Internal)
_(no declarations extracted)_

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcTrack.h` (Internal)


#### class `UE::PixelStreaming2::TEpicRtcTrack`  
`template <typename TrackInterface UE_REQUIRES(std::is_same_v<TrackInterface, EpicRtcAudioTrackInterface> || std::is_same_v<TrackInterface, EpicRtcDataTrackInterface> || std::is_same_v<TrackInterface, EpicRtcVideoTrackInterface>)> class TEpicRtcTrack`  
_L16-36_
- L19 _public function_ `TEpicRtcTrack(TrackInterface* Track) : Track(Track)`
- L24 _public prototype_ `virtual ~TEpicRtcTrack() = default;`
- L29 _public function_ `EpicRtcStringView GetTrackId() const` — @return The id of the underlying EpicRtc track.
- L35 _protected member_ `TRefCountPtr<TrackInterface> Track;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcVideoCapturer.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcVideoCapturer`  
`class FEpicRtcVideoCapturer : public FVideoCapturer`  
_L13-23_
- inherits: `FVideoCapturer`
- L16 _public prototype_ `static TSharedPtr<FEpicRtcVideoCapturer> Create(bool bIsSRGB = false);`
- L17 _public prototype_ `virtual ~FEpicRtcVideoCapturer() = default;`
- L19 _public prototype_ `TRefCountPtr<EpicRtcVideoBufferInterface> GetFrameBuffer();`
- L22 _private prototype_ `FEpicRtcVideoCapturer(bool bIsSRGB);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcVideoDecoderInitializer.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcVideoDecoderInitializer`  
`class FEpicRtcVideoDecoderInitializer : public EpicRtcVideoDecoderInitializerInterface`  
_L16-35_
- inherits: `EpicRtcVideoDecoderInitializerInterface`
- L19 _public prototype_ `FEpicRtcVideoDecoderInitializer() = default;`
- L20 _public prototype_ `virtual ~FEpicRtcVideoDecoderInitializer() = default;`
- L23 _public prototype_ `virtual void CreateDecoder(EpicRtcVideoCodecInfoInterface* CodecInfo, EpicRtcVideoDecoderInterface** OutDecoder) override;`
- L24 _public prototype_ `virtual EpicRtcStringView GetName() override;`
- L25 _public prototype_ `virtual EpicRtcVideoCodecInfoArrayInterface* GetSupportedCodecs() override;`
- L29 _private prototype_ `TMap<EVideoCodec, TArray<TRefCountPtr<EpicRtcVideoCodecInfoInterface>>> CreateSupportedDecoderMap();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcVideoEncoderInitializer.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcVideoEncoderInitializer`  
`class FEpicRtcVideoEncoderInitializer : public EpicRtcVideoEncoderInitializerInterface`  
_L16-35_
- inherits: `EpicRtcVideoEncoderInitializerInterface`
- L19 _public prototype_ `FEpicRtcVideoEncoderInitializer() = default;`
- L20 _public prototype_ `virtual ~FEpicRtcVideoEncoderInitializer() = default;`
- L23 _public prototype_ `virtual void CreateEncoder(EpicRtcVideoCodecInfoInterface* CodecInfo, EpicRtcVideoEncoderInterface** OutEncoder) override;`
- L24 _public prototype_ `virtual EpicRtcStringView GetName() override;`
- L25 _public prototype_ `virtual EpicRtcVideoCodecInfoArrayInterface* GetSupportedCodecs() override;`
- L29 _private prototype_ `TMap<EVideoCodec, TArray<TRefCountPtr<EpicRtcVideoCodecInfoInterface>>> CreateSupportedEncoderMap();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcVideoSink.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcVideoSink`  
`class FEpicRtcVideoSink : public FVideoSink, public TEpicRtcTrack<EpicRtcVideoTrackInterface>, public TSharedFromThis<FEpicRtcVideoSink>`  
_L20-40_
- inherits: `FVideoSink,TEpicRtcTrack<EpicRtcVideoTrackInterface>,TSharedFromThis<FEpicRtcVideoSink>`
- desc: Video sink class that receives a frame from EpicRtc and passes the frame to all added consumers
- L23 _public prototype_ `static TSharedPtr<FEpicRtcVideoSink> Create(TRefCountPtr<EpicRtcVideoTrackInterface> InTrack);`
- L25 _public prototype_ `virtual ~FEpicRtcVideoSink() = default;` — Note: destructor will call destroy on any attached video consumers
- L27 _public prototype_ `void OnEpicRtcFrame(const EpicRtcVideoFrame& Frame);`
- L29 _private prototype_ `FEpicRtcVideoSink(TRefCountPtr<EpicRtcVideoTrackInterface> InTrack);`
- L31 _private prototype_ `void OnFrameCaptured();`
- L33 _private member_ `FCriticalSection RenderSyncContext;`
- L34 _private member_ `FPooledRenderTargetDesc RenderTargetDescriptor;`
- L35 _private member_ `TRefCountPtr<IPooledRenderTarget> RenderTarget;`
- L36 _private member_ `TArray<uint8_t> Buffer;`
- L37 _private member_ `FTextureRHIRef SourceTexture;`
- L39 _private member_ `TSharedPtr<FVideoCapturer> VideoCapturer;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcVideoSource.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcVideoSource`  
`class FEpicRtcVideoSource : public FVideoSource, public TEpicRtcTrack<EpicRtcVideoTrackInterface>`  
_L25-41_
- inherits: `FVideoSource,TEpicRtcTrack<EpicRtcVideoTrackInterface>`
- desc: A source of video frames for an EpicRtc peer. Has a video input which will provide frame data to this source. The source will then pass that data to an adapter which will have one or many adapt processes that are provided by the input object and are responsible for converting the frame data to the format required for the selected video encoder. This video source should be contained within a FVideoSourceGroup which is responsible for telling each source to push a frame to EpicRtc at the expected rate. This source will make sure that the adapter has valid output and if so will create a frame for EpicRtc. Otherwise it will continue to wait until the next frame.
- L28 _public prototype_ `static TSharedPtr<FEpicRtcVideoSource> Create(TRefCountPtr<EpicRtcVideoTrackInterface> InVideoTrack, TSharedPtr<FEpicRtcVideoCapturer> InVideoCapturer, TSharedPtr<FVideoSourceGroup> InVideoSourceGroup);`
- L29 _public prototype_ `virtual ~FEpicRtcVideoSource() = default;`
- L31 _public prototype_ `virtual void PushFrame() override;`
- L32 _public prototype_ `virtual void ForceKeyFrame() override;`
- L34 _public prototype_ `TRefCountPtr<EpicRtcVideoTrackInterface> GetVideoTrack();`
- L37 _private prototype_ `FEpicRtcVideoSource(TRefCountPtr<EpicRtcVideoTrackInterface> InVideoTrack, TSharedPtr<FEpicRtcVideoCapturer> InVideoCapturer);`
- L40 _private member_ `TSharedPtr<FEpicRtcVideoCapturer> VideoCapturer;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcVideoTrackObserver.h` (Internal)


#### class `UPixelStreaming2VideoTrackObserver`  
`class UPixelStreaming2VideoTrackObserver : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2VideoTrackObserver`  
`class IPixelStreaming2VideoTrackObserver`  
_L20-30_
- L25 _public prototype_ `virtual void OnVideoTrackMuted(EpicRtcVideoTrackInterface* VideoTrack, EpicRtcBool bIsMuted) = 0;`
- L26 _public prototype_ `virtual void OnVideoTrackFrame(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcVideoFrame& Frame) = 0;`
- L27 _public prototype_ `virtual void OnVideoTrackState(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcTrackState State) = 0;`
- L28 _public prototype_ `virtual void OnVideoTrackEncodedFrame(EpicRtcStringView ParticipantId, EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcEncodedVideoFrame& EncodedFrame) = 0;`
- L29 _public prototype_ `virtual EpicRtcBool Enabled() const = 0;`

#### class `UE::PixelStreaming2::FEpicRtcVideoTrackObserver`  
`class FEpicRtcVideoTrackObserver : public EpicRtcVideoTrackObserverInterface`  
_L34-56_
- inherits: `EpicRtcVideoTrackObserverInterface`
- L37 _public prototype_ `FEpicRtcVideoTrackObserver(TObserverVariant<IPixelStreaming2VideoTrackObserver> UserObserver);`
- L38 _public prototype_ `virtual ~FEpicRtcVideoTrackObserver() = default;`
- L42 _private prototype_ `virtual void OnVideoTrackMuted(EpicRtcVideoTrackInterface* VideoTrack, EpicRtcBool bIsMuted) override;`
- L43 _private prototype_ `virtual void OnVideoTrackFrame(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcVideoFrame& Frame) override;`
- L44 _private prototype_ `virtual void OnVideoTrackState(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcTrackState State) override;`
- L45 _private prototype_ `virtual void OnVideoTrackEncodedFrame(EpicRtcStringView ParticipantId, EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcEncodedVideoFrame& EncodedFrame) override;`
- L46 _private prototype_ `virtual EpicRtcBool Enabled() const override;`
- L55 _private member_ `TObserverVariant<IPixelStreaming2VideoTrackObserver> UserObserver;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcVideoTrackObserverFactory.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcVideoTrackObserverFactory`  
`class FEpicRtcVideoTrackObserverFactory : public EpicRtcVideoTrackObserverFactoryInterface`  
_L16-34_
- inherits: `EpicRtcVideoTrackObserverFactoryInterface`
- L19 _public prototype_ `FEpicRtcVideoTrackObserverFactory(TObserverVariant<IPixelStreaming2VideoTrackObserver> UserObserver);`
- L20 _public prototype_ `virtual ~FEpicRtcVideoTrackObserverFactory() = default;`
- L24 _public prototype_ `virtual EpicRtcErrorCode CreateVideoTrackObserver(const EpicRtcStringView ParticipantId, const EpicRtcStringView VideoTrackId, EpicRtcVideoTrackObserverInterface** OutVideoTrackObserver) override;`
- L33 _private member_ `TObserverVariant<IPixelStreaming2VideoTrackObserver> UserObserver;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcWebsocket.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcWebsocket`  
`class FEpicRtcWebsocket : public EpicRtcWebsocketInterface, public FTickableGameObject`  
_L17-64_
- inherits: `EpicRtcWebsocketInterface,FTickableGameObject`
- L20 _public prototype_ `FEpicRtcWebsocket(bool bKeepAlive = true, TSharedPtr<IWebSocket> WebSocket = nullptr);`
- L21 _public prototype_ `virtual ~FEpicRtcWebsocket() = default;`
- L24 _public prototype_ `virtual EpicRtcBool Connect(EpicRtcStringView Url, EpicRtcWebsocketObserverInterface* Observer) override;`
- L25 _public prototype_ `virtual void Disconnect(const EpicRtcStringView Reason) override;`
- L26 _public prototype_ `virtual void Send(EpicRtcStringView Message) override;`
- L30 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L31 _public function_ `virtual bool IsTickableInEditor() const override`
- L32 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L33 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L37 _private prototype_ `void OnConnected();`
- L38 _private prototype_ `void OnConnectionError(const FString& Error);`
- L39 _private prototype_ `void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);`
- L40 _private prototype_ `void OnMessage(const FString& Msg);`
- L41 _private prototype_ `void OnBinaryMessage(const uint8* Data, int32 Length, bool bIsLastFragment);`
- L42 _private prototype_ `void KeepAlive();`
- L45 _private member_ `FDelegateHandle OnConnectedHandle;`
- L46 _private member_ `FDelegateHandle OnConnectionErrorHandle;`
- L47 _private member_ `FDelegateHandle OnClosedHandle;`
- L48 _private member_ `FDelegateHandle OnMessageHandle;`
- L49 _private member_ `FDelegateHandle OnBinaryMessageHandle;`
- L52 _private member_ `FString Url;`
- L53 _private member_ `FString LastError;`
- L54 _private member_ `TSharedPtr<IWebSocket> WebSocket;`
- L55 _private member_ `TRefCountPtr<EpicRtcWebsocketObserverInterface> Observer;`
- L56 _private member_ `uint64 LastKeepAliveCycles = 0;`
- L57 _private member_ `bool bSendKeepAlive = false;`
- L58 _private member_ `bool bCloseRequested = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/EpicRtcWebsocketFactory.h` (Internal)


#### class `UE::PixelStreaming2::FEpicRtcWebsocketFactory`  
`class FEpicRtcWebsocketFactory : public EpicRtcWebsocketFactoryInterface`  
_L15-34_
- inherits: `EpicRtcWebsocketFactoryInterface`
- L18 _public function_ `FEpicRtcWebsocketFactory(bool bInSendKeepAlive = true) : bSendKeepAlive(bInSendKeepAlive)`
- L23 _public prototype_ `virtual ~FEpicRtcWebsocketFactory() = default;`
- L25 _public prototype_ `virtual EpicRtcErrorCode CreateWebsocket(EpicRtcWebsocketInterface** OutWebsocket) override;`
- L33 _private member_ `bool bSendKeepAlive;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/RTCStatsCollector.h` (Internal)


#### enum `UE::PixelStreaming2::EDisplayFlags`  
`enum EDisplayFlags : uint8`  
_L34-39_
- L36 _public enumerator_ `HIDDEN = 0`
- L37 _public enumerator_ `TEXT = 1 << 0`
- L38 _public enumerator_ `GRAPH = 1 << 1`

#### struct `UE::PixelStreaming2::FStatConfig`  
`struct FStatConfig`  
_L41-46_
- L43 _public member_ `FName Name;`
- L44 _public member_ `TOptional<FName> Alias;`
- L45 _public member_ `EDisplayFlags DisplayFlags = EDisplayFlags::TEXT;`

#### class `UE::PixelStreaming2::FStat`  
`class FStat`  
_L50-128_
- L53 _public prototype_ `FStat() = default;`
- L55 _public prototype_ `FStat(FStatConfig Config, double InitialValue, int NDecimalPlacesToPrint = 0, bool bSmooth = false);`
- L56 _public prototype_ `FStat(FStatConfig Config, FString InitialValue);`
- L57 _public prototype_ `FStat(FStatConfig Config, bool bInitialValue);`
- L58 _public prototype_ `FStat(const FStat& Other);`
- L60 _public prototype_ `bool IsNumeric() const;`
- L62 _public prototype_ `bool IsTextual() const;`
- L64 _public prototype_ `bool IsBoolean() const;`
- L66 _public prototype_ `FString ToString();`
- L68 _public prototype_ `bool SetValue(FStatVariant ValueVariant);`
- L71 _public function_ `template <typename T> T GetValue()`
- L77 _public prototype_ `template <> FString GetValue();`
- L80 _public prototype_ `template <> double GetValue();`
- L83 _public prototype_ `template <> bool GetValue();`
- L86 _public function_ `template <typename T> T GetPrevValue()`
- L92 _public prototype_ `template <> FString GetPrevValue();`
- L95 _public prototype_ `template <> double GetPrevValue();`
- L98 _public prototype_ `template <> bool GetPrevValue();`
- L100 _public prototype_ `bool operator==(const FStat& Other) const;`
- L102 _public prototype_ `bool IsHidden();`
- L104 _public prototype_ `bool ShouldGraph();`
- L106 _public prototype_ `bool ShouldDisplayText();`
- L108 _public prototype_ `FName GetName() const;`
- L110 _public prototype_ `FName GetDisplayName() const;`
- L113 _private prototype_ `double CalcMA(double InPrevAvg, int InNumSamples, double InValue);`
- L114 _private prototype_ `double CalcEMA(double InPrevAvg, int InNumSamples, double InValue);`
- L117 _protected member_ `FName Name;`
- L118 _protected member_ `EDisplayFlags DisplayFlags = EDisplayFlags::TEXT;`
- L119 _protected member_ `TOptional<FName> Alias;`
- L122 _protected member_ `int NDecimalPlacesToPrint = 0;` — variable used for calculating and displaying numeric stat data
- L123 _protected member_ `bool bSmooth = false;`
- L124 _protected member_ `int NumSamples = 0;`
- L126 _protected member_ `FStatVariant StatVariant;`
- L127 _protected member_ `FStatVariant PrevStatVariant;`

#### class `UE::PixelStreaming2::FRTCStatsCollector`  
`class FRTCStatsCollector`  
_L136-271_
- L139 _public prototype_ `static TSharedPtr<FRTCStatsCollector> Create(const FString& PlayerId);`
- L142 _private prototype_ `FRTCStatsCollector();`
- L143 _private prototype_ `explicit FRTCStatsCollector(const FString& PlayerId);`
- L145 _private prototype_ `void OnWebRTCDisableStatsChanged(IConsoleVariable* Var);`
- L148 _public prototype_ `void Process(const EpicRtcConnectionStats& InStats);`
- L251 _private member_ `FString AssociatedPlayerId;`
- L252 _private member_ `uint64 LastCalculationCycles;`
- L253 _private member_ `bool bIsEnabled;`
- L256 _private member_ `TMap<uint64, TMap<uint32, TUniquePtr<FRTPLocalVideoTrackStatsSink>>> LocalVideoTrackSinks;` — index,         ssrc                          sink
- L257 _private member_ `TMap<uint64, TMap<uint32, TUniquePtr<FRTPLocalAudioTrackStatsSink>>> LocalAudioTrackSinks;`
- L259 _private member_ `TMap<uint64, TMap<uint32, TUniquePtr<FRTPRemoteTrackStatsSink>>> RemoteVideoTrackSinks;`
- L260 _private member_ `TMap<uint64, TMap<uint32, TUniquePtr<FRTPRemoteTrackStatsSink>>> RemoteAudioTrackSinks;`
- L262 _private member_ `TMap<uint64, TUniquePtr<FVideoSourceStatsSink>> VideoSourceSinks;`
- L263 _private member_ `TMap<uint64, TUniquePtr<FVideoCodecStatsSink>> VideoCodecSinks;`
- L265 _private member_ `TMap<uint64, TUniquePtr<FAudioSourceStatsSink>> AudioSourceSinks;`
- L266 _private member_ `TMap<uint64, TUniquePtr<FAudioCodecStatsSink>> AudioCodecSinks;`
- L268 _private member_ `TMap<uint64, TUniquePtr<FDataTrackStatsSink>> DataTrackSinks;`
- L270 _private member_ `TUniquePtr<FCandidatePairStatsSink> CandidatePairStatsSink;`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FStatsSink`  
`class FStatsSink`  
_L151-172_
- L154 _public prototype_ `FStatsSink(FName InCategory);`
- L155 _public prototype_ `virtual ~FStatsSink() = default;`
- L157 _public function_ `virtual FStat* Get(const FName& StatName)`
- L162 _public prototype_ `virtual void PostProcess(FStats* PSStats, const FString& PeerId, double SecondsDelta);`
- L166 _protected member_ `TMap<FName, FStat> Stats;` — Stats that are stored as is.
- L168 _protected member_ `TArray<TFunction<TOptional<FStat>(FStatsSink&, double)>> Calculators;` — Stats we calculate based on the stats map above. This calculation is done in FStatsSink::PostProcess by the `Calculators` below.
- L171 _protected member_ `FName Category;`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FRTPLocalVideoTrackStatsSink`  
`class FRTPLocalVideoTrackStatsSink : public FStatsSink`  
_L174-180_
- inherits: `FStatsSink`
- L177 _public prototype_ `FRTPLocalVideoTrackStatsSink(FName Category);`
- L178 _public prototype_ `virtual ~FRTPLocalVideoTrackStatsSink() = default;`
- L179 _public prototype_ `void Process(const EpicRtcLocalTrackRtpStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FRTPLocalAudioTrackStatsSink`  
`class FRTPLocalAudioTrackStatsSink : public FStatsSink`  
_L182-188_
- inherits: `FStatsSink`
- L185 _public prototype_ `FRTPLocalAudioTrackStatsSink(FName Category);`
- L186 _public prototype_ `virtual ~FRTPLocalAudioTrackStatsSink() = default;`
- L187 _public prototype_ `void Process(const EpicRtcLocalTrackRtpStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FRTPRemoteTrackStatsSink`  
`class FRTPRemoteTrackStatsSink : public FStatsSink`  
_L190-196_
- inherits: `FStatsSink`
- L193 _public prototype_ `FRTPRemoteTrackStatsSink(FName Category);`
- L194 _public prototype_ `virtual ~FRTPRemoteTrackStatsSink() = default;`
- L195 _public prototype_ `void Process(const EpicRtcRemoteTrackRtpStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FVideoSourceStatsSink`  
`class FVideoSourceStatsSink : public FStatsSink`  
_L198-204_
- inherits: `FStatsSink`
- L201 _public prototype_ `FVideoSourceStatsSink(FName Category);`
- L202 _public prototype_ `virtual ~FVideoSourceStatsSink() = default;`
- L203 _public prototype_ `void Process(const EpicRtcVideoSourceStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FVideoCodecStatsSink`  
`class FVideoCodecStatsSink : public FStatsSink`  
_L206-212_
- inherits: `FStatsSink`
- L209 _public prototype_ `FVideoCodecStatsSink(FName Category);`
- L210 _public prototype_ `virtual ~FVideoCodecStatsSink() = default;`
- L211 _public prototype_ `void Process(const EpicRtcCodecStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FAudioSourceStatsSink`  
`class FAudioSourceStatsSink : public FStatsSink`  
_L214-220_
- inherits: `FStatsSink`
- L217 _public prototype_ `FAudioSourceStatsSink(FName Category);`
- L218 _public prototype_ `virtual ~FAudioSourceStatsSink() = default;`
- L219 _public prototype_ `void Process(const EpicRtcAudioSourceStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FAudioCodecStatsSink`  
`class FAudioCodecStatsSink : public FStatsSink`  
_L222-228_
- inherits: `FStatsSink`
- L225 _public prototype_ `FAudioCodecStatsSink(FName Category);`
- L226 _public prototype_ `virtual ~FAudioCodecStatsSink() = default;`
- L227 _public prototype_ `void Process(const EpicRtcCodecStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FDataTrackStatsSink`  
`class FDataTrackStatsSink : public FStatsSink`  
_L233-240_
- inherits: `FStatsSink`
- desc: ---------- FDataChannelSink -------------------
- L236 _public prototype_ `FDataTrackStatsSink(FName Category);`
- L237 _public prototype_ `virtual ~FDataTrackStatsSink() = default;`
- L239 _public prototype_ `void Process(const EpicRtcDataTrackStats& InStats, const FString& PeerId, double SecondsDelta);`

#### class `UE::PixelStreaming2::FRTCStatsCollector::FCandidatePairStatsSink`  
`class FCandidatePairStatsSink : public FStatsSink`  
_L242-248_
- inherits: `FStatsSink`
- L245 _public prototype_ `FCandidatePairStatsSink(FName Category);`
- L246 _public prototype_ `virtual ~FCandidatePairStatsSink() = default;`
- L247 _public prototype_ `void Process(const EpicRtcIceCandidatePairStats& InStats, const FString& PeerId, double SecondsDelta);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L20 _namespace_ `namespace RTCStatCategories` (scope `UE::PixelStreaming2`)
- L22 _variable_ `const FString LocalVideoTrack = TEXT("vid` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L23 _variable_ `const FString LocalAudioTrack = TEXT("aud` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L24 _variable_ `const FString VideoSource = TEXT("vid` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L25 _variable_ `const FString AudioSource = TEXT("aud` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L26 _variable_ `const FString VideoCodec = TEXT("vid` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L27 _variable_ `const FString AudioCodec = TEXT("aud` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L28 _variable_ `const FString DataChannel = TEXT("dat` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L29 _variable_ `const FString RemoteVideoTrack = TEXT("vid` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L30 _variable_ `const FString RemoteAudioTrack = TEXT("aud` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L31 _variable_ `const FString CandidatePair = TEXT("can` (scope `UE::PixelStreaming2::RTCStatCategories`)
- L48 _typedef_ `using FStatVariant = TVariant<TYPE_OF_NULLPTR, double, FString, bool>;` (scope `UE::PixelStreaming2`)
- L130 _function_ `FORCEINLINE uint32 GetTypeHash(const FStat& Obj)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/SharedTickableTasks.h` (Internal)


#### class `UE::PixelStreaming2::FSharedTickableTasks`  
`class FSharedTickableTasks`  
_L10-21_
- L13 _public function_ `FSharedTickableTasks(TSharedPtr<FEpicRtcTickConferenceTask> InTickConferenceTask) : TickConferenceTask(InTickConferenceTask)`
- L20 _private member_ `TSharedPtr<FEpicRtcTickConferenceTask> TickConferenceTask;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Internal/UtilsString.h` (Internal)


#### Free symbols / members of external scopes

- L18 _macro_ `#define BEGIN_ENUM_TO_STRING(EnumType, Value) \`
- L22 _macro_ `#define ENUM_CASE_TO_STRING(Name) case Type::Name: return TEXT(#Name);`
- L24 _macro_ `#define END_ENUM_TO_STRING() \`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L30 _function_ `inline FString ToString(EpicRtcPixelFormat Format)` (scope `UE::PixelStreaming2`)
- L44 _function_ `inline FString ToString(EpicRtcErrorCode Error)` (scope `UE::PixelStreaming2`)
- L67 _function_ `inline FString ToString(EpicRtcQualityLimitationReason Reason)` (scope `UE::PixelStreaming2`)
- L77 _function_ `inline FString ToString(EpicRtcVideoCodec Codec)` (scope `UE::PixelStreaming2`)
- L87 _function_ `inline FString ToString(EpicRtcRoomState State)` (scope `UE::PixelStreaming2`)
- L99 _function_ `inline FString ToString(EpicRtcTrackState State)` (scope `UE::PixelStreaming2`)
- L108 _function_ `inline FString ToString(const TSharedPtr<FJsonObject>& JsonObj, bool bPretty = true)` (scope `UE::PixelStreaming2`)
- L124 _function_ `inline FString ToString(const EpicRtcStringView& Str)` (scope `UE::PixelStreaming2`)
- L130 _function_ `inline EpicRtcStringView ToEpicRtcStringView(const FUtf8String& Str)` (scope `UE::PixelStreaming2`)
- L139 _function_ `inline FString ReadString(const uint8*& Data, uint32_t& Size)` (scope `UE::PixelStreaming2`) — Reads a string represented by 2 bytes length (in bytes) followed by UTF16 characters. String and length are encoded in little endian format.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/Blueprints/PixelStreaming2Peer.h` (Private)


#### class `UPixelStreaming2Peer`  
`class UPixelStreaming2Peer : public USynthComponent, public IPixelStreaming2AudioConsumer, public IPixelStreaming2VideoConsumer, public IPixelStreaming2SessionObserver, public IPixelStreaming2RoomObserver, public IPixelStreaming2AudioTrackObserver, public IPixelStreaming2DataTrackObserver, public IPixelStreaming2VideoTrackObserver`  
_L41-187_
- reflection: `UCLASS(Blueprintable, ClassGroup = (PixelStreaming2), meta = (BlueprintSpawnableComponent))`
- reflection: `UCLASS(Blueprintable, Category = "PixelStreaming2", META = (DisplayName = "PixelStreaming Peer Component", BlueprintSpawnableComponent))`
- inherits: `USynthComponent,IPixelStreaming2AudioConsumer,IPixelStreaming2VideoConsumer,IPixelStreaming2SessionObserver,IPixelStreaming2RoomObserver,IPixelStreaming2AudioTrackObserver,IPixelStreaming2DataTrackObserver,IPixelStreaming2VideoTrackObserver`
- desc: A blueprint representation of a Pixel Streaming Peer Connection. Will accept video sinks to receive video data. NOTE: This class is not a peer of a streamer. This class represents a peer in its own right (akin to the browser) and will subscribe to a stream
- L54 _protected prototype_ `virtual void BeginPlay() override;` — UObject overrides
- L55 _protected prototype_ `virtual void BeginDestroy() override;`
- L56 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L59 _protected prototype_ `virtual void OnBeginGenerate() override;` — USynthComponent overrides
- L60 _protected prototype_ `virtual void OnEndGenerate() override;`
- L61 _protected prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L70 _public prototype_ `bool Connect(const FString& Url);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")` — Attempt to connect to a specified signalling server. @param Url The url of the signalling server. Ignored if this component has a MediaSource. In that case the URL on the media source will be used instead. @return Returns false if Connect fails.
- L77 _public prototype_ `bool Disconnect();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")` — Disconnect from the signalling server. No action if no connection exists. @return Returns false if Disconnect fails.
- L85 _public prototype_ `bool Subscribe(const FString& StreamerId);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")` — Subscribe this peer to the streams provided by the specified streamer. @param StreamerId The name of the streamer to subscribe to. @return Returns false if Subscribe fails.
- L91 _public member_ `FPixelStreamingStreamerList OnStreamerList;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired when the connection the list of available streams from the server.
- L97 _public member_ `TObjectPtr<UPixelStreaming2MediaTexture> VideoConsumer = nullptr;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", META = (DisplayName = "Pixel Streaming Video Consumer", AllowPrivateAccess = true))` — A sink for the video data received once this connection has finished negotiating.
- L100 _private member_ `FUtf8String SubscribedStream;`
- L101 _private member_ `FUtf8String PlayerName;`
- L102 _private member_ `static uint32_t PlayerId;`
- L104 _private member_ `TSharedPtr<UE::PixelStreaming2::FSharedTickableTasks> TickableTasks;`
- L106 _private member_ `TSharedPtr<UE::PixelStreaming2::FEpicRtcAudioSink> AudioSink;`
- L107 _private member_ `uintptr_t RemoteAudioTrack;`
- L109 _private member_ `TSharedPtr<UE::PixelStreaming2::FSoundGenerator, ESPMode::ThreadSafe> SoundGenerator;`
- L111 _private member_ `TSharedPtr<UE::PixelStreaming2::FEpicRtcVideoSink> VideoSink;`
- L112 _private member_ `uintptr_t RemoteVideoTrack;`
- L114 _private member_ `TSharedPtr<UE::PixelStreaming2::FRTCStatsCollector> StatsCollector;`
- L116 _private prototype_ `bool Disconnect(const FString& OptionalReason);`
- L120 _public prototype_ `virtual void ConsumeRawPCM(const int16_t* AudioData, int SampleRate, size_t NumChannels, size_t NumFrames) override;`
- L121 _public prototype_ `virtual void OnAudioConsumerAdded() override;`
- L122 _public prototype_ `virtual void OnAudioConsumerRemoved() override;`
- L126 _public prototype_ `virtual void ConsumeFrame(FTextureRHIRef Frame) override;`
- L127 _public prototype_ `virtual void OnVideoConsumerAdded() override;`
- L128 _public prototype_ `virtual void OnVideoConsumerRemoved() override;`
- L132 _public prototype_ `virtual void OnSessionStateUpdate(const EpicRtcSessionState StateUpdate) override;`
- L133 _public prototype_ `virtual void OnSessionErrorUpdate(const EpicRtcErrorCode ErrorUpdate) override;`
- L134 _public prototype_ `virtual void OnSessionRoomsAvailableUpdate(EpicRtcStringArrayInterface* RoomsList) override;`
- L138 _public prototype_ `virtual void OnRoomStateUpdate(const EpicRtcRoomState State) override;`
- L139 _public prototype_ `virtual void OnRoomJoinedUpdate(EpicRtcParticipantInterface* Participant) override;`
- L140 _public prototype_ `virtual void OnRoomLeftUpdate(const EpicRtcStringView ParticipantId) override;`
- L141 _public prototype_ `virtual void OnAudioTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcAudioTrackInterface* AudioTrack) override;`
- L142 _public prototype_ `virtual void OnVideoTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcVideoTrackInterface* VideoTrack) override;`
- L143 _public prototype_ `virtual void OnDataTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcDataTrackInterface* DataTrack) override;`
- L144 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnLocalSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L145 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnRemoteSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L146 _public prototype_ `virtual void OnRoomErrorUpdate(const EpicRtcErrorCode Error) override;`
- L150 _public prototype_ `virtual void OnAudioTrackMuted(EpicRtcAudioTrackInterface* AudioTrack, EpicRtcBool bIsMuted) override;`
- L151 _public prototype_ `virtual void OnAudioTrackFrame(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcAudioFrame& Frame) override;`
- L152 _public prototype_ `virtual void OnAudioTrackState(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcTrackState State) override;`
- L156 _public prototype_ `virtual void OnVideoTrackMuted(EpicRtcVideoTrackInterface* VideoTrack, EpicRtcBool bIsMuted) override;`
- L157 _public prototype_ `virtual void OnVideoTrackFrame(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcVideoFrame& Frame) override;`
- L158 _public prototype_ `virtual void OnVideoTrackState(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcTrackState State) override;`
- L159 _public prototype_ `virtual void OnVideoTrackEncodedFrame(EpicRtcStringView ParticipantId, EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcEncodedVideoFrame& EncodedFrame) override;`
- L160 _public prototype_ `virtual EpicRtcBool Enabled() const override;`
- L164 _public prototype_ `virtual void OnDataTrackState(EpicRtcDataTrackInterface* DataTrack, const EpicRtcTrackState State) override;`
- L165 _public prototype_ `virtual void OnDataTrackMessage(EpicRtcDataTrackInterface* DataTrack, const EpicRtcDataFrame& DataFrame) override;`
- L166 _public prototype_ `virtual void OnDataTrackError(EpicRtcDataTrackInterface* DataTrack, const EpicRtcErrorCode Error) override;`
- L169 _public prototype_ `void OnStatsReady(const FString& PeerId, const EpicRtcConnectionStats& ConnectionStats);`
- L172 _private member_ `EpicRtcSessionState SessionState = EpicRtcSessionState::Disconnected;`
- L175 _private member_ `TRefCountPtr<EpicRtcConferenceInterface> EpicRtcConference;`
- L176 _private member_ `TRefCountPtr<EpicRtcSessionInterface> EpicRtcSession;`
- L177 _private member_ `TRefCountPtr<EpicRtcRoomInterface> EpicRtcRoom;`
- L181 _private member_ `TRefCountPtr<UE::PixelStreaming2::FEpicRtcSessionObserver> SessionObserver;`
- L182 _private member_ `TRefCountPtr<UE::PixelStreaming2::FEpicRtcRoomObserver> RoomObserver;`
- L183 _private member_ `TRefCountPtr<UE::PixelStreaming2::FEpicRtcAudioTrackObserverFactory> AudioTrackObserverFactory;`
- L184 _private member_ `TRefCountPtr<UE::PixelStreaming2::FEpicRtcVideoTrackObserverFactory> VideoTrackObserverFactory;`
- L185 _private member_ `TRefCountPtr<UE::PixelStreaming2::FEpicRtcDataTrackObserverFactory> DataTrackObserverFactory;`

#### Free symbols / members of external scopes

- L28 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingStreamerList, UPixelStreaming2Peer, OnStreamerList, const TArray<FString>&, StreamerList);`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/ColorConversion.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L9 _prototype_ `void ConvertI420ToArgb( const uint8* RESTRICT SrcY, int StrideY, const uint8* RESTRICT SrcU, int StrideU, const uint8* RESTRICT SrcV, int StrideV, uint8* RESTRICT DestArgb, int StrideDest, int Width, int Height);` (scope `UE::PixelStreaming2`)
- L21 _prototype_ `void ConvertArgbToI420( const uint8* RESTRICT SrcArgb, int StrideArgb, uint8* RESTRICT DestY, int StrideY, uint8* RESTRICT DestU, int StrideU, uint8* RESTRICT DestV, int StrideV, int Width, int Height);` (scope `UE::PixelStreaming2`)
- L33 _prototype_ `void ConvertI420ToI010( const uint8* RESTRICT SrcY, int SrcStrideY, const uint8* RESTRICT SrcU, int SrcStrideU, const uint8* RESTRICT SrcV, int SrcStrideV, uint16* RESTRICT DstY, int DstStrideY, uint16* RESTRICT DstU, int DstStrideU, uint16* RESTRICT DstV, int DstStrideV, int Width, int Height);` (scope `UE::PixelStreaming2`)
- L49 _prototype_ `void Convert8To16Plane( const uint8* RESTRICT SrcY, int SrcStrideY, uint16* RESTRICT DstY, int DstStrideY, int Scale,` (scope `UE::PixelStreaming2`)
- L58 _prototype_ `void Convert8To16Row( const uint8* RESTRICT SrcY, uint16* RESTRICT DstY, int Scale, int Width);` (scope `UE::PixelStreaming2`)
- L64 _prototype_ `void CopyI420(const uint8* RESTRICT SrcY, int SrcStrideY, const uint8* RESTRICT SrcU, int SrcStrideU, const uint8* RESTRICT SrcV, int SrcStrideV, uint8* RESTRICT DstY, int DstStrideY, uint8* RESTRICT DstU, int DstStrideU, uint8* RESTRICT DstV, int DstStrideV, int Width, int Height);` (scope `UE::PixelStreaming2`)
- L79 _prototype_ `void CopyPlane(const uint8* RESTRICT SrcY, int SrcStrideY, uint8* RESTRICT DstY, int DstStrideY, int Width, int Height);` (scope `UE::PixelStreaming2`)
- L86 _function_ `constexpr size_t CalcBufferSizeArgb(int Width, int Height)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/DebugGraph.h` (Private)


#### class `UE::PixelStreaming2::FDebugGraph`  
`class FDebugGraph`  
_L10-38_
- L13 _public prototype_ `FDebugGraph(FName InName, int InSamples, float InMinRange, float InMaxRange, float InRefValue = 0.0f);`
- L14 _public prototype_ `FDebugGraph(const FDebugGraph& Other);`
- L15 _public prototype_ `~FDebugGraph() = default;`
- L17 _public prototype_ `void AddValue(float InValue);`
- L18 _public prototype_ `void Draw(FCanvas* Canvas, FVector2D Position, FVector2D Size) const;`
- L21 _private prototype_ `void AddValueInternal(float InValue);`
- L24 _private member_ `FName Name;`
- L25 _private member_ `int MaxSamples = 0;`
- L26 _private member_ `float MinRange = 0.0f;`
- L27 _private member_ `float MaxRange = 0.0f;`
- L28 _private member_ `float RefValue = 0.0f;`
- L30 _private member_ `float Sum = 0;`
- L31 _private member_ `TArray<float> Values;`
- L32 _private member_ `TArray<float> AvgValues;`
- L33 _private member_ `int InsertIndex = 0;`
- L34 _private member_ `int BufferedValues = 0;`
- L35 _private member_ `bool bFirstValue = true;`
- L37 _private member_ `mutable FCriticalSection CriticalSection;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/EpicRtcStreamer.h` (Private)


#### class `UE::PixelStreaming2::FEpicRtcStreamer`  
`class FEpicRtcStreamer : public IPixelStreaming2Streamer, public TSharedFromThis<FEpicRtcStreamer>, public IPixelStreaming2SessionObserver, public IPixelStreaming2RoomObserver, public IPixelStreaming2AudioTrackObserver, public IPixelStreaming2DataTrackObserver, public IPixelStreaming2VideoTrackObserver`  
_L35-272_
- inherits: `IPixelStreaming2Streamer,TSharedFromThis<FEpicRtcStreamer>,IPixelStreaming2SessionObserver,IPixelStreaming2RoomObserver,IPixelStreaming2AudioTrackObserver,IPixelStreaming2DataTrackObserver,IPixelStreaming2VideoTrackObserver`
- L45 _public prototype_ `FEpicRtcStreamer(const FString& StreamerId, TRefCountPtr<EpicRtcConferenceInterface> Conference);`
- L46 _public prototype_ `virtual ~FEpicRtcStreamer();`
- L48 _public prototype_ `virtual void Initialize() override;`
- L49 _public prototype_ `virtual void SetStreamFPS(int32 InFramesPerSecond) override;`
- L50 _public prototype_ `virtual int32 GetStreamFPS() override;`
- L51 _public prototype_ `virtual void SetCoupleFramerate(bool bCouple) override;`
- L53 _public prototype_ `virtual void SetVideoProducer(TSharedPtr<IPixelStreaming2VideoProducer> Input) override;`
- L54 _public prototype_ `virtual TWeakPtr<IPixelStreaming2VideoProducer> GetVideoProducer() override;`
- L56 _public prototype_ `virtual void AddAudioProducer(TSharedPtr<IPixelStreaming2AudioProducer> AudioProducer) override;`
- L57 _public prototype_ `virtual void RemoveAudioProducer(TSharedPtr<IPixelStreaming2AudioProducer> AudioProducer) override;`
- L58 _public prototype_ `virtual TArray<TWeakPtr<IPixelStreaming2AudioProducer>> GetAudioProducers() override;`
- L60 _public prototype_ `virtual void SetConnectionURL(const FString& InConnectionURL) override;`
- L61 _public prototype_ `virtual FString GetConnectionURL() override;`
- L63 _public function_ `virtual FString GetId() override`
- L64 _public function_ `virtual bool IsConnected() override`
- L65 _public prototype_ `virtual void StartStreaming() override;`
- L66 _public prototype_ `virtual void StopStreaming() override;`
- L67 _public function_ `virtual bool IsStreaming() const override`
- L69 _public prototype_ `virtual FPreConnectionEvent& OnPreConnection() override;`
- L70 _public prototype_ `virtual FStreamingStartedEvent& OnStreamingStarted() override;`
- L71 _public prototype_ `virtual FStreamingStoppedEvent& OnStreamingStopped() override;`
- L73 _public prototype_ `virtual void ForceKeyFrame() override;`
- L75 _public prototype_ `virtual void FreezeStream(UTexture2D* Texture) override;`
- L76 _public prototype_ `virtual void UnfreezeStream() override;`
- L78 _public prototype_ `virtual void SendAllPlayersMessage(FString MessageType, const FString& Descriptor) override;`
- L79 _public prototype_ `virtual void SendPlayerMessage(FString PlayerId, FString MessageType, const FString& Descriptor) override;`
- L80 _public prototype_ `virtual void SendFileData(const TArray64<uint8>& ByteData, FString& MimeType, FString& FileExtension) override;`
- L81 _public prototype_ `virtual void KickPlayer(FString PlayerId) override;`
- L82 _public prototype_ `virtual TArray<FString> GetConnectedPlayers() override;`
- L84 _public function_ `virtual TWeakPtr<IPixelStreaming2InputHandler> GetInputHandler() override`
- L85 _public prototype_ `virtual void SetInputHandler(TSharedPtr<IPixelStreaming2InputHandler> Handler) override;`
- L87 _public prototype_ `virtual TWeakPtr<IPixelStreaming2AudioSink> GetPeerAudioSink(FString PlayerId) override;`
- L88 _public prototype_ `virtual TWeakPtr<IPixelStreaming2AudioSink> GetUnlistenedAudioSink() override;`
- L89 _public prototype_ `virtual TWeakPtr<IPixelStreaming2VideoSink> GetPeerVideoSink(FString PlayerId) override;`
- L90 _public prototype_ `virtual TWeakPtr<IPixelStreaming2VideoSink> GetUnwatchedVideoSink() override;`
- L92 _public prototype_ `virtual void SetConfigOption(const FName& OptionName, const FString& Value) override;`
- L93 _public prototype_ `virtual bool GetConfigOption(const FName& OptionName, FString& OutValue) override;`
- L95 _public prototype_ `virtual void PlayerRequestsBitrate(FString PlayerId, int MinBitrate, int MaxBitrate) override;`
- L97 _public prototype_ `virtual void RefreshStreamBitrate() override;`
- L99 _public prototype_ `void ForEachPlayer(const TFunction<void(FString, TSharedPtr<FPlayerContext>)>& Func);`
- L103 _private prototype_ `void OnProtocolUpdated();` — own methods
- L104 _private prototype_ `void ConsumeStats(FString PlayerId, FName StatName, float StatValue);`
- L105 _private prototype_ `void DeletePlayerSession(FString PlayerId);`
- L106 _private prototype_ `void DeleteAllPlayerSessions();`
- L107 _private prototype_ `void SendInitialSettings(FString PlayerId) const;`
- L108 _private prototype_ `void SendProtocol(FString PlayerId) const;`
- L109 _private prototype_ `void SendPeerControllerMessages(FString PlayerId) const;`
- L110 _private prototype_ `void SendLatencyReport(FString PlayerId) const;`
- L111 _private prototype_ `void HandleRelayStatusMessage(const uint8_t* Data, uint32_t Size, EpicRtcDataTrackInterface* DataTrack);`
- L112 _private prototype_ `void TriggerMouseLeave(FString InStreamerId);`
- L113 _private prototype_ `FUtf8String GetAudioStreamID();`
- L114 _private prototype_ `FUtf8String GetVideoStreamID();`
- L117 _private prototype_ `void OnDataTrackOpen(FString PlayerId);` — Function called on track events. Handles broadcasting of delegates and any other logic not related to the track itself (ie sending protocol)
- L118 _private prototype_ `void OnDataTrackClosed(FString PlayerId);`
- L119 _private prototype_ `void OnAudioTrackOpen(FString PlayerId, bool bIsRemote);`
- L120 _private prototype_ `void OnAudioTrackClosed(FString PlayerId, bool bIsRemote);`
- L121 _private prototype_ `void OnVideoTrackOpen(FString PlayerId, bool bIsRemote);`
- L122 _private prototype_ `void OnVideoTrackClosed(FString PlayerId, bool bIsRemote);`
- L123 _private prototype_ `void CloseAudioTrack(const TSharedPtr<FPlayerContext>& Participant, FString PlayerId, bool bIsRemote);`
- L124 _private prototype_ `void CloseDataTrack(const TSharedPtr<FPlayerContext>& Participant, FString PlayerId);`
- L125 _private prototype_ `void CloseVideoTrack(const TSharedPtr<FPlayerContext>& Participant, FString PlayerId, bool bIsRemote);`
- L127 _private prototype_ `void OnStatsReady(const FString& PlayerId, const EpicRtcConnectionStats& ConnectionStats);`
- L128 _private prototype_ `void OnFrameCapturerCreated();`
- L129 _private prototype_ `void OnUIInteraction(FMemoryReader Ar);`
- L130 _private prototype_ `void OnSendMessage(FString MessageName, FMemoryReader Ar);`
- L131 _private prototype_ `EpicRtcBitrate GetBitrates(bool bIncludeStartBitrate) const;`
- L134 _private function_ `template <typename T> bool FindPlayerFromTrack(T Track, FString& OutPlayerId)`
- L178 _private member_ `FString StreamerId;`
- L179 _private member_ `FString CurrentSignallingServerURL;`
- L181 _private member_ `TSharedPtr<IPixelStreaming2InputHandler> InputHandler;`
- L183 _private member_ `TSharedPtr<TThreadSafeMap<FString, TSharedPtr<FPlayerContext>>> Participants;`
- L185 _private member_ `FString InputControllingId = INVALID_PLAYER_ID;`
- L195 _private member_ `EStreamState StreamState = EStreamState::Disconnected;`
- L197 _private member_ `FPreConnectionEvent StreamingPreConnectionEvent;`
- L198 _private member_ `FStreamingStartedEvent StreamingStartedEvent;`
- L199 _private member_ `FStreamingStoppedEvent StreamingStoppedEvent;`
- L201 _private member_ `TSharedPtr<FEpicRtcAudioCapturer> AudioCapturer;`
- L202 _private member_ `TSharedPtr<FEpicRtcVideoCapturer> VideoCapturer;`
- L203 _private member_ `TSharedPtr<FVideoSourceGroup> VideoSourceGroup;`
- L204 _private member_ `TSharedPtr<FFreezeFrame> FreezeFrame;`
- L206 _private member_ `TSharedPtr<FEpicRtcVideoSource> VideoSource;`
- L207 _private member_ `TSharedPtr<FEpicRtcAudioSource> AudioSource;`
- L209 _private member_ `TMap<FName, FString> ConfigOptions;`
- L210 _private member_ `TMap<uintptr_t , FString > AudioTrackPlayerIdMap;`
- L211 _private member_ `TMap<uintptr_t , FString > VideoTrackPlayerIdMap;`
- L213 _private member_ `TSharedPtr<FStreamerReconnectTimer> ReconnectTimer;`
- L214 _private member_ `TSharedPtr<FSharedTickableTasks> TickableTasks;`
- L216 _private member_ `FCriticalSection CustomAudioProducersCS;`
- L217 _private member_ `TArray<TSharedPtr<IPixelStreaming2AudioProducer>> CustomAudioProducers;`
- L221 _public prototype_ `virtual void OnSessionStateUpdate(const EpicRtcSessionState StateUpdate) override;`
- L222 _public prototype_ `virtual void OnSessionErrorUpdate(const EpicRtcErrorCode ErrorUpdate) override;`
- L223 _public prototype_ `virtual void OnSessionRoomsAvailableUpdate(EpicRtcStringArrayInterface* RoomsList) override;`
- L227 _public prototype_ `virtual void OnRoomStateUpdate(const EpicRtcRoomState State) override;`
- L228 _public prototype_ `virtual void OnRoomJoinedUpdate(EpicRtcParticipantInterface* Participant) override;`
- L229 _public prototype_ `virtual void OnRoomLeftUpdate(const EpicRtcStringView ParticipantId) override;`
- L230 _public prototype_ `virtual void OnAudioTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcAudioTrackInterface* AudioTrack) override;`
- L231 _public prototype_ `virtual void OnVideoTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcVideoTrackInterface* VideoTrack) override;`
- L232 _public prototype_ `virtual void OnDataTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcDataTrackInterface* DataTrack) override;`
- L233 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnLocalSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L234 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnRemoteSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L235 _public prototype_ `virtual void OnRoomErrorUpdate(const EpicRtcErrorCode Error) override;`
- L239 _public prototype_ `virtual void OnAudioTrackMuted(EpicRtcAudioTrackInterface* AudioTrack, EpicRtcBool bIsMuted) override;`
- L240 _public prototype_ `virtual void OnAudioTrackFrame(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcAudioFrame& Frame) override;`
- L241 _public prototype_ `virtual void OnAudioTrackState(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcTrackState State) override;`
- L245 _public prototype_ `virtual void OnVideoTrackMuted(EpicRtcVideoTrackInterface* VideoTrack, EpicRtcBool bIsMuted) override;`
- L246 _public prototype_ `virtual void OnVideoTrackFrame(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcVideoFrame& Frame) override;`
- L247 _public prototype_ `virtual void OnVideoTrackState(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcTrackState State) override;`
- L248 _public prototype_ `virtual void OnVideoTrackEncodedFrame(EpicRtcStringView ParticipantId, EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcEncodedVideoFrame& EncodedFrame) override;`
- L249 _public prototype_ `virtual EpicRtcBool Enabled() const override;`
- L253 _public prototype_ `virtual void OnDataTrackState(EpicRtcDataTrackInterface* DataTrack, const EpicRtcTrackState State) override;`
- L254 _public prototype_ `virtual void OnDataTrackMessage(EpicRtcDataTrackInterface* DataTrack, const EpicRtcDataFrame& DataFrame) override;`
- L255 _public prototype_ `virtual void OnDataTrackError(EpicRtcDataTrackInterface* DataTrack, const EpicRtcErrorCode Error) override;`
- L260 _private member_ `TRefCountPtr<EpicRtcConferenceInterface> EpicRtcConference;`
- L261 _private member_ `TRefCountPtr<EpicRtcSessionInterface> EpicRtcSession;`
- L262 _private member_ `TRefCountPtr<EpicRtcRoomInterface> EpicRtcRoom;`
- L266 _private member_ `TRefCountPtr<FEpicRtcSessionObserver> SessionObserver;`
- L267 _private member_ `TRefCountPtr<FEpicRtcRoomObserver> RoomObserver;`
- L268 _private member_ `TRefCountPtr<FEpicRtcAudioTrackObserverFactory> AudioTrackObserverFactory;`
- L269 _private member_ `TRefCountPtr<FEpicRtcVideoTrackObserverFactory> VideoTrackObserverFactory;`
- L270 _private member_ `TRefCountPtr<FEpicRtcDataTrackObserverFactory> DataTrackObserverFactory;`

#### enum `UE::PixelStreaming2::FEpicRtcStreamer::EStreamState`  
`enum class EStreamState : uint8`  
_L187-193_
- L189 _public enumerator_ `Disconnected = 0`
- L190 _public enumerator_ `Connecting`
- L191 _public enumerator_ `Connected`
- L192 _public enumerator_ `Disconnecting`

#### class `UE::PixelStreaming2::FRTCStreamerFactory`  
`class FRTCStreamerFactory : public IPixelStreaming2StreamerFactory`  
_L274-285_
- inherits: `IPixelStreaming2StreamerFactory`
- L277 _public prototype_ `FRTCStreamerFactory(TRefCountPtr<EpicRtcConferenceInterface> Conference);`
- L278 _public prototype_ `virtual ~FRTCStreamerFactory() = default;`
- L280 _public prototype_ `virtual FString GetStreamType() override;`
- L281 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> CreateNewStreamer(const FString& StreamerId) override;`
- L284 _private member_ `TRefCountPtr<EpicRtcConferenceInterface> EpicRtcConference;`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L32 _variable_ `static const FString INVALID_PLAYER_ID = TEXT("Inv` (scope `UE::PixelStreaming2`)
- L33 _variable_ `static const FString RTC_STREAM_TYPE = TEXT("Def` (scope `UE::PixelStreaming2`)
- L156 _function_ `Participants->ApplyUntil([DataTrackId, &OutPlayerId](FString PlayerId, TSharedPtr<FPlayerContext> Participant) { if (Participant->DataTrack) { FString TrackId = ToString(Participant->DataTrack->GetTrackId()); if (TrackId == DataTrackId) { OutPlayerId = PlayerId; return true; } } return false; });` (scope `UE::PixelStreaming2::FEpicRtcStreamer::FindPlayerFromTrack`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/EpicRtcVideoBuffer.h` (Private)


#### class `UE::PixelStreaming2::FEpicRtcVideoBuffer`  
`class FEpicRtcVideoBuffer : public EpicRtcVideoBufferInterface`  
_L19-48_
- inherits: `EpicRtcVideoBufferInterface`
- desc: The base VideoBuffer class that PixelStreaming2 uses. It partially implements the EpicRtcVideoBufferInterface by always returning EpicRtcPixelFormat::Native to signal to EpicRtc that it doesn't need to wrap this buffer in ANOTHER buffer before passing to WebRTC. It provides the GetBufferFormat virtual method for use cases to check the format of the buffer ie RHI or I420 etc
- L22 _public prototype_ `FEpicRtcVideoBuffer() = default;`
- L24 _public prototype_ `virtual ~FEpicRtcVideoBuffer() = default;`
- L27 _public function_ `virtual int32 GetBufferFormat()`
- L34 _public function_ `virtual EpicRtcPixelFormat GetFormat() override` — We always need to return Native so EpicRtc doesn't try to wrap these buffers in software wrappers
- L39 _public function_ `virtual EpicRtcVideoBufferInterface* ToI420() override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/EpicRtcVideoBufferI420.h` (Private)


#### class `UE::PixelStreaming2::FEpicRtcVideoBufferI420`  
`class FEpicRtcVideoBufferI420 : public FEpicRtcVideoBuffer`  
_L10-60_
- inherits: `FEpicRtcVideoBuffer`
- L13 _public function_ `FEpicRtcVideoBufferI420(TSharedPtr<FPixelCaptureBufferI420> Buffer) : Buffer(Buffer)`
- L18 _public prototype_ `virtual ~FEpicRtcVideoBufferI420() = default;`
- L22 _public function_ `virtual int32 GetBufferFormat() override`
- L31 _public function_ `virtual EpicRtcPixelFormat GetFormat() override` — Android uses the internal EpicRtc buffers so we report I420 format here
- L37 _public function_ `virtual void* GetData() override`
- L42 _public function_ `virtual int GetWidth() override`
- L47 _public function_ `virtual int GetHeight() override`
- L53 _public function_ `TSharedPtr<FPixelCaptureBufferI420> GetBuffer()`
- L59 _private member_ `TSharedPtr<FPixelCaptureBufferI420> Buffer;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/EpicRtcVideoBufferMultiFormat.h` (Private)


#### class `UE::PixelStreaming2::FEpicRtcVideoBufferMultiFormatBase`  
`class FEpicRtcVideoBufferMultiFormatBase : public EpicRtcVideoBufferInterface`  
_L18-49_
- inherits: `EpicRtcVideoBufferInterface`
- desc: Base class for our multi format buffers.
- L21 _public prototype_ `FEpicRtcVideoBufferMultiFormatBase(TSharedPtr<FPixelCaptureCapturerMultiFormat> InFrameCapturer);`
- L22 _public prototype_ `virtual ~FEpicRtcVideoBufferMultiFormatBase() = default;`
- L26 _public function_ `virtual void* GetData() override`
- L31 _public function_ `virtual EpicRtcVideoBufferInterface* ToI420() override`
- L36 _public function_ `virtual EpicRtcPixelFormat GetFormat() override`
- L48 _protected member_ `TSharedPtr<FPixelCaptureCapturerMultiFormat> FrameCapturer;`

#### class `UE::PixelStreaming2::FEpicRtcVideoBufferMultiFormatLayered`  
`class FEpicRtcVideoBufferMultiFormatLayered : public FEpicRtcVideoBufferMultiFormatBase`  
_L54-69_
- inherits: `FEpicRtcVideoBufferMultiFormatBase`
- desc: A multi layered, multi format frame buffer for our encoder.
- L57 _public prototype_ `FEpicRtcVideoBufferMultiFormatLayered(TSharedPtr<FPixelCaptureCapturerMultiFormat> InFrameCapturer, FIntPoint SourceResolution);`
- L58 _public prototype_ `virtual ~FEpicRtcVideoBufferMultiFormatLayered() = default;`
- L60 _public prototype_ `virtual int GetWidth() override;`
- L61 _public prototype_ `virtual int GetHeight() override;`
- L62 _public prototype_ `virtual EpicRtcVideoBufferInterface* ToI420() override;`
- L65 _public prototype_ `TRefCountPtr<FEpicRtcVideoBufferMultiFormat> GetLayer(FIntPoint Resolution) const;`
- L68 _private member_ `FIntPoint SourceResolution;`

#### class `UE::PixelStreaming2::FEpicRtcVideoBufferMultiFormat`  
`class FEpicRtcVideoBufferMultiFormat : public FEpicRtcVideoBufferMultiFormatBase`  
_L74-90_
- inherits: `FEpicRtcVideoBufferMultiFormatBase`
- desc: A single layer, multi format frame buffer.
- L77 _public prototype_ `FEpicRtcVideoBufferMultiFormat(TSharedPtr<FPixelCaptureCapturerMultiFormat> InFrameCapturer, FIntPoint InResolution);`
- L78 _public prototype_ `virtual ~FEpicRtcVideoBufferMultiFormat() = default;`
- L80 _public prototype_ `virtual int GetWidth() override;`
- L81 _public prototype_ `virtual int GetHeight() override;`
- L83 _public prototype_ `IPixelCaptureOutputFrame* RequestFormat(int32 Format) const;`
- L86 _private member_ `FIntPoint Resolution;`
- L89 _private member_ `mutable TMap<int32, TSharedPtr<IPixelCaptureOutputFrame>> CachedFormat;` — we want the frame buffer to always refer to the same frame. so the first request for a format will fill this cache.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/EpicRtcVideoBufferRHI.h` (Private)


#### class `UE::PixelStreaming2::FEpicRtcVideoBufferRHI`  
`class FEpicRtcVideoBufferRHI : public FEpicRtcVideoBuffer`  
_L10-61_
- inherits: `FEpicRtcVideoBuffer`
- L13 _public function_ `FEpicRtcVideoBufferRHI(TSharedPtr<FVideoResourceRHI> VideoResourceRHI) : VideoResourceRHI(VideoResourceRHI)`
- L19 _public function_ `virtual ~FEpicRtcVideoBufferRHI()`
- L26 _public function_ `virtual int32 GetBufferFormat() override`
- L33 _public function_ `virtual void* GetData() override`
- L38 _public function_ `virtual int GetWidth() override`
- L43 _public function_ `virtual int GetHeight() override`
- L49 _public function_ `TSharedPtr<FVideoResourceRHI> GetVideoResource()`
- L60 _private member_ `TSharedPtr<FVideoResourceRHI> VideoResourceRHI;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/EpicRtcVideoDecoder.h` (Private)


#### class `UE::PixelStreaming2::TEpicRtcVideoDecoder`  
`template <std::derived_from<FVideoResource> TVideoResource> class TEpicRtcVideoDecoder : public EpicRtcVideoDecoderInterface`  
_L22-60_
- inherits: `EpicRtcVideoDecoderInterface`
- L25 _public prototype_ `TEpicRtcVideoDecoder(EpicRtcVideoCodecInfoInterface* CodecInfo);`
- L28 _public prototype_ `[[nodiscard]] virtual EpicRtcStringView GetName() const override;`
- L29 _public prototype_ `virtual EpicRtcVideoDecoderConfig GetConfig() const override;`
- L30 _public prototype_ `virtual EpicRtcMediaResult SetConfig(const EpicRtcVideoDecoderConfig& VideoDecoderConfig) override;`
- L31 _public prototype_ `virtual EpicRtcVideoDecoderInfo GetInfo() override;`
- L32 _public prototype_ `virtual EpicRtcMediaResult Decode(const EpicRtcEncodedVideoFrame& Frame) override;`
- L33 _public prototype_ `virtual void RegisterCallback(EpicRtcVideoDecoderCallbackInterface* Callback) override;`
- L34 _public prototype_ `virtual void Reset() override;`
- L37 _private member_ `TSharedPtr<TVideoDecoder<TVideoResource>> Decoder;`
- L38 _private member_ `TUniquePtr<FVideoDecoderConfig> InitialVideoConfig;`
- L39 _private member_ `EpicRtcVideoDecoderConfig DecoderConfig;`
- L40 _private member_ `TRefCountPtr<EpicRtcVideoDecoderCallbackInterface> VideoDecoderCallback;`
- L41 _private member_ `TRefCountPtr<EpicRtcVideoCodecInfoInterface> CodecInfo;`
- L42 _private member_ `uint16_t FrameCount;`
- L45 _private typedef_ `using DecoderResourceType = typename std::conditional<std::is_same_v<TVideoResource, FVideoResourceRHI>, FResolvableVideoResourceRHI, typename std::conditional<std::is_same_v<TVideoResource, FVideoResourceCPU>, FResolvableVideoResourceCPU,` — clang-format off
- L50 _private member_ `DecoderResourceType DecoderResource;`
- L54 _private prototype_ `bool LateInitDecoder();`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/EpicRtcVideoEncoder.h` (Private)


#### class `UE::PixelStreaming2::TEpicRtcVideoEncoder`  
`template <std::derived_from<FVideoResource> TVideoResource> class TEpicRtcVideoEncoder : public EpicRtcVideoEncoderInterface`  
_L23-78_
- inherits: `EpicRtcVideoEncoderInterface`
- L26 _public prototype_ `TEpicRtcVideoEncoder(EpicRtcVideoCodecInfoInterface* InCodecInfo);`
- L30 _public prototype_ `virtual EpicRtcStringView GetName() const override;`
- L31 _public prototype_ `virtual EpicRtcVideoEncoderConfig GetConfig() const override;`
- L32 _public prototype_ `virtual EpicRtcMediaResult SetConfig(const EpicRtcVideoEncoderConfig& VideoEncoderConfig) override;`
- L33 _public prototype_ `virtual EpicRtcVideoEncoderInfo GetInfo() override;`
- L34 _public prototype_ `virtual EpicRtcMediaResult Encode(const EpicRtcVideoFrame& VideoFrame, EpicRtcVideoFrameTypeArrayInterface* FrameTypes) override;`
- L35 _public prototype_ `virtual void RegisterCallback(EpicRtcVideoEncoderCallbackInterface* InCallback) override;`
- L36 _public prototype_ `virtual void Reset() override;`
- L40 _private member_ `EpicRtcVideoEncoderConfig EncoderConfig;`
- L41 _private member_ `TSharedPtr<TVideoEncoder<TVideoResource>> Encoder;`
- L42 _private member_ `TRefCountPtr<EpicRtcVideoEncoderCallbackInterface> VideoEncoderCallback;`
- L43 _private member_ `TRefCountPtr<EpicRtcVideoCodecInfoInterface> CodecInfo;`
- L44 _private member_ `TRefCountPtr<FEpicRtcPixelFormatArray> PreferredPixelFormats;`
- L45 _private member_ `TRefCountPtr<FEpicRtcVideoResolutionBitrateLimitsArray> ResolutionBitrateLimits;`
- L47 _private member_ `TOptional<uint32_t> EpicRtcTargetBitrates[Video::MaxSpatialLayers][Video::MaxTemporalStreams];`
- L48 _private member_ `TOptional<double> EpicRtcTargetFramerate;`
- L51 _private member_ `uint32_t EpicRtcProposedTargetBitrate = 5000000;` — We store this so we can restore back to it if the user decides to use then stop using the PixelStreaming2.Encoder.TargetBitrate CVar.
- L54 _private member_ `IFileHandle* FileHandle = nullptr;` — File handle used to save the encoded output to
- L55 _private member_ `bool bDidLastEncodedFramePushFail = false;`
- L58 _private prototype_ `TSharedPtr<TVideoEncoder<TVideoResource>> CreateEncoder(const EpicRtcVideoEncoderConfig& Config, const EpicRtcVideoCodec Codec);`
- L59 _private prototype_ `void SetInitialSettings(const EpicRtcVideoEncoderConfig& CodecSettings, FVideoEncoderConfig& VideoConfig);`
- L60 _private prototype_ `void UpdateConfig();`
- L61 _private prototype_ `void MaybeDumpFrame(EpicRtcEncodedVideoFrame const& EncodedImage);`
- L62 _private prototype_ `uint32_t SumAndResetBitrates();`
- L64 _private prototype_ `void UpdateFrameMetadataPreEncode(IPixelCaptureOutputFrame& Frame);`
- L65 _private prototype_ `void UpdateFrameMetadataPostEncode(IPixelCaptureOutputFrame& Frame);`
- L66 _private prototype_ `void UpdateFrameMetadataPrePacketization(IPixelCaptureOutputFrame& Frame);`
- L67 _private prototype_ `void UpdateFrameMetadataPostPacketization(IPixelCaptureOutputFrame& Frame);`
- L69 _private prototype_ `void OnEncoderDebugDumpFrameChanged(IConsoleVariable* Var);`
- L70 _private prototype_ `void CreateDumpFile();`
- L72 _private member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/FreezeFrame.h` (Private)


#### class `UE::PixelStreaming2::FFreezeFrame`  
`class FFreezeFrame : public TSharedFromThis<FFreezeFrame>`  
_L27-64_
- inherits: `TSharedFromThis<FFreezeFrame>`
- desc: The user of the Pixel Streaming application can trigger a freeze frame to happen at any time during stream. What a freeze frame will do is either: 1) Mode 1 - Send a known texture/image (effectively a still image, e.g. a loading screen). 2) Mode 2 - Send the current rendered frame out of UE as an image This freeze frame will displayed over the top of the video stream with no compression. So a crisp, high quality image, is guaranteed. While this is occuring the stream is not technically frozen, it still encodes and send frames; however, visually, the user is only shown this still. This technique can be used to hide large, known, cpu/gpu lags in the Pixel Streaming experience, for example during a level load or some expensive transition. The better solution is to not lag your application in the first place, but this can be a bandaid.
- L30 _public prototype_ `static TSharedPtr<FFreezeFrame> Create(TWeakPtr<TThreadSafeMap<FString, TSharedPtr<FPlayerContext>>> InPlayers, TWeakPtr<FVideoCapturer> InVideoCapturer, TWeakPtr<IPixelStreaming2InputHandler> InInputHandler);`
- L31 _public prototype_ `virtual ~FFreezeFrame();`
- L37 _public prototype_ `void StartFreeze(UTexture2D* Texture);` — @brief Start the freeze frame process, either mode 1 or 2 depending on if a texture is passed. @param Texture - The still image to send as a freeze frame, pass nullptr to use send the backbuffer instead.
- L38 _public prototype_ `void StopFreeze();`
- L39 _public prototype_ `void SendCachedFreezeFrameTo(FString PlayerId) const;`
- L42 _protected prototype_ `FFreezeFrame(TWeakPtr<TThreadSafeMap<FString, TSharedPtr<FPlayerContext>>> WeakPlayers, TWeakPtr<FVideoCapturer> VideoCapturer, TWeakPtr<IPixelStreaming2InputHandler> InputHandler);`
- L45 _private prototype_ `void SendFreezeFrame(TArray<FColor> RawData, const FIntRect& Rect);`
- L46 _private prototype_ `void SetupFreezeFrameCapture();`
- L47 _private prototype_ `void RemoveFreezeFrameBinding();`
- L48 _private prototype_ `void FreezeFrameCapture();`
- L51 _private member_ `TWeakPtr<TThreadSafeMap<FString, TSharedPtr<FPlayerContext>>> WeakPlayers;`
- L54 _private member_ `TWeakPtr<FVideoCapturer> VideoCapturer;` — Video input used to capture the frame if mode 2 is used.
- L57 _private member_ `TWeakPtr<IPixelStreaming2InputHandler> InputHandler;` — Used to respond to freeze frame messaged being sent by the browser
- L60 _private member_ `TArray64<uint8> CachedJpegBytes;` — When we send a freeze frame we retain the data so we send freeze frame to new peers if they join during a freeze frame.
- L63 _private member_ `TOptional<FDelegateHandle> OnFrameCapturedForFreezeFrameHandle;` — Delegate handle for when we bind to the OnFrameCaptured delegate of the video input - we unbind from this once the freeze frame is captured

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2RTC, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2RTC, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/PixelStreaming2RTCModule.h` (Private)


#### class `UE::PixelStreaming2::FPixelStreaming2RTCModule`  
`class FPixelStreaming2RTCModule : public IPixelStreaming2RTCModule, public IMediaPlayerFactory`  
_L21-78_
- inherits: `IPixelStreaming2RTCModule,IMediaPlayerFactory`
- desc: This plugin allows the back buffer to be sent as a compressed video across a network.
- L24 _public prototype_ `static FPixelStreaming2RTCModule* GetModule();`
- L26 _public prototype_ `virtual ~FPixelStreaming2RTCModule() = default;`
- L29 _public prototype_ `virtual FReadyEvent& OnReady() override;`
- L30 _public prototype_ `virtual bool IsReady() override;`
- L34 _public prototype_ `virtual TSharedPtr<IMediaPlayer> CreatePlayer(IMediaEventSink& EventSink) override;`
- L35 _public prototype_ `virtual FName GetPlayerName() const override;`
- L36 _public prototype_ `virtual FText GetDisplayName() const override;`
- L37 _public prototype_ `virtual bool CanPlayUrl(const FString& Url, const IMediaOptions* Options, TArray<FText>* OutWarnings, TArray<FText>* OutErrors) const override;`
- L38 _public prototype_ `virtual bool SupportsFeature(EMediaFeature Feature) const override;`
- L39 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L40 _public prototype_ `virtual const TArray<FString>& GetSupportedPlatforms() const override;`
- L43 _public prototype_ `TSharedPtr<FSharedTickableTasks> GetSharedTickableTasks();`
- L44 _public function_ `TRefCountPtr<EpicRtcConferenceInterface>& GetEpicRtcConference()`
- L45 _public function_ `TRefCountPtr<FEpicRtcStatsCollector>& GetStatsCollector()`
- L49 _private prototype_ `void StartupModule() override;`
- L50 _private prototype_ `void ShutdownModule() override;`
- L53 _private prototype_ `FString GetFieldTrials();`
- L54 _private prototype_ `bool InitializeEpicRtc();`
- L57 _private member_ `bool bModuleReady = false;`
- L58 _private member_ `bool bStartupCompleted = false;`
- L59 _private member_ `static FPixelStreaming2RTCModule* PixelStreaming2Module;`
- L61 _private member_ `FReadyEvent ReadyEvent;`
- L62 _private member_ `FDelegateHandle LogStatsHandle;`
- L65 _private member_ `TRefCountPtr<EpicRtcPlatformInterface> EpicRtcPlatform;`
- L66 _private member_ `TRefCountPtr<EpicRtcConferenceInterface> EpicRtcConference;`
- L67 _private member_ `TRefCountPtr<FEpicRtcStatsCollector> StatsCollector;`
- L69 _private member_ `TRefCountPtr<FEpicRtcWebsocketFactory> WebsocketFactory;`
- L70 _private member_ `TWeakPtr<FSharedTickableTasks> TickableTasks;`
- L72 _private member_ `TArray<EpicRtcVideoEncoderInitializerInterface*> EpicRtcVideoEncoderInitializers;`
- L73 _private member_ `TArray<EpicRtcVideoDecoderInitializerInterface*> EpicRtcVideoDecoderInitializers;`
- L75 _private member_ `static FUtf8String EpicRtcConferenceName;`
- L77 _private member_ `TUniquePtr<FRTCStreamerFactory> StreamerFactory;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/PixelStreaming2RTCPlayer.h` (Private)


#### class `UE::PixelStreaming2::FPixelStreaming2RTCStreamPlayer`  
`class FPixelStreaming2RTCStreamPlayer : public IMediaPlayer, public IMediaTracks, public IMediaCache, public IMediaControls, public IMediaView, public IPixelStreaming2SessionObserver, public IPixelStreaming2RoomObserver, public IPixelStreaming2AudioTrackObserver, public IPixelStreaming2DataTrackObserver, public IPixelStreaming2VideoTrackObserver, public IPixelStreaming2AudioConsumer, public IPixelStreaming2VideoConsumer, public TSharedFromThis<FPixelStreaming2RTCStreamPlayer>`  
_L35-199_
- inherits: `IMediaPlayer,IMediaTracks,IMediaCache,IMediaControls,IMediaView,IPixelStreaming2SessionObserver,IPixelStreaming2RoomObserver,IPixelStreaming2AudioTrackObserver,IPixelStreaming2DataTrackObserver,IPixelStreaming2VideoTrackObserver,IPixelStreaming2AudioConsumer,IPixelStreaming2VideoConsumer,TSharedFromThis<FPixelStreaming2RTCStreamPlayer>`
- L51 _public prototype_ `FPixelStreaming2RTCStreamPlayer();`
- L52 _public prototype_ `virtual ~FPixelStreaming2RTCStreamPlayer();`
- L55 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L56 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L57 _public prototype_ `virtual void Close() override;`
- L58 _public prototype_ `virtual FString GetUrl() const override;`
- L59 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L60 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L61 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L62 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L63 _public prototype_ `virtual FString GetInfo() const override;`
- L64 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L65 _public prototype_ `virtual FString GetStats() const override;`
- L66 _public prototype_ `virtual IMediaView& GetView() override;`
- L67 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L71 _public prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L72 _public prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L73 _public prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L74 _public prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L75 _public prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L76 _public prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L77 _public prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L78 _public prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L79 _public prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L80 _public prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L81 _public prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L85 _public prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L86 _public prototype_ `virtual FTimespan GetDuration() const override;`
- L87 _public prototype_ `virtual float GetRate() const override;`
- L88 _public prototype_ `virtual EMediaState GetState() const override;`
- L89 _public prototype_ `virtual EMediaStatus GetStatus() const override;`
- L90 _public prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L91 _public prototype_ `virtual FTimespan GetTime() const override;`
- L92 _public prototype_ `virtual bool IsLooping() const override;`
- L93 _public prototype_ `virtual bool Seek(const FTimespan& Time) override;`
- L94 _public prototype_ `virtual bool SetLooping(bool Looping) override;`
- L95 _public prototype_ `virtual bool SetRate(float Rate) override;`
- L100 _private member_ `static uint32_t PlayerId;` — Incremented Id used to construct the PlayerName
- L102 _private member_ `FString PlayerName;` — A unique identifier for the player instance. Used to create unique EpicRtc sessions per player instance
- L104 _private member_ `FString StreamURL;` — The URL of the stream to connect to
- L107 _private member_ `FString TargetStreamerId;` — The id of the streamer to subscribe to. Optionally passed in through the stream URL. If not present in URL the first streamer id returned in the streamer list will be the streamer that is subscribed to
- L110 _private member_ `TSharedPtr<FEpicRtcAudioSink> AudioSink;` — The audio sink used to process remote audio
- L112 _private member_ `uintptr_t RemoteAudioTrack;` — The remote audio track. We only support one track at this time so we make sure we only receive frames for that track
- L115 _private member_ `TSharedPtr<FEpicRtcVideoSink> VideoSink;` — The video sink used to process remote audio
- L117 _private member_ `uintptr_t RemoteVideoTrack;` — The remote video track. We only support one track at this time so we make sure we only receive frames for that track
- L119 _private member_ `TSharedPtr<FRTCStatsCollector> StatsCollector;`
- L120 _private member_ `FDelegateHandle OnStatsReadyHandle;`
- L122 _private member_ `int32 SelectedAudioTrack;`
- L123 _private member_ `int32 SelectedVideoTrack;`
- L125 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> Samples;`
- L127 _private member_ `TSharedPtr<class FPixelStreaming2AudioSamplePool> AudioSamplePool;`
- L128 _private member_ `TSharedPtr<class FPixelStreaming2TextureSamplePool> VideoSamplePool;`
- L132 _public prototype_ `virtual void OnSessionStateUpdate(const EpicRtcSessionState StateUpdate) override;`
- L133 _public prototype_ `virtual void OnSessionErrorUpdate(const EpicRtcErrorCode ErrorUpdate) override;`
- L134 _public prototype_ `virtual void OnSessionRoomsAvailableUpdate(EpicRtcStringArrayInterface* RoomsList) override;`
- L138 _public prototype_ `virtual void OnRoomStateUpdate(const EpicRtcRoomState State) override;`
- L139 _public prototype_ `virtual void OnRoomJoinedUpdate(EpicRtcParticipantInterface* Participant) override;`
- L140 _public prototype_ `virtual void OnRoomLeftUpdate(const EpicRtcStringView ParticipantId) override;`
- L141 _public prototype_ `virtual void OnAudioTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcAudioTrackInterface* AudioTrack) override;`
- L142 _public prototype_ `virtual void OnVideoTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcVideoTrackInterface* VideoTrack) override;`
- L143 _public prototype_ `virtual void OnDataTrackUpdate(EpicRtcParticipantInterface* Participant, EpicRtcDataTrackInterface* DataTrack) override;`
- L144 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnLocalSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L145 _public prototype_ `[[nodiscard]] virtual EpicRtcSdpInterface* OnRemoteSdpUpdate(EpicRtcParticipantInterface* Participant, EpicRtcSdpInterface* Sdp) override;`
- L146 _public prototype_ `virtual void OnRoomErrorUpdate(const EpicRtcErrorCode Error) override;`
- L150 _public prototype_ `virtual void OnAudioTrackMuted(EpicRtcAudioTrackInterface* AudioTrack, EpicRtcBool bIsMuted) override;`
- L151 _public prototype_ `virtual void OnAudioTrackFrame(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcAudioFrame& Frame) override;`
- L152 _public prototype_ `virtual void OnAudioTrackState(EpicRtcAudioTrackInterface* AudioTrack, const EpicRtcTrackState State) override;`
- L156 _public prototype_ `virtual void OnVideoTrackMuted(EpicRtcVideoTrackInterface* VideoTrack, EpicRtcBool bIsMuted) override;`
- L157 _public prototype_ `virtual void OnVideoTrackFrame(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcVideoFrame& Frame) override;`
- L158 _public prototype_ `virtual void OnVideoTrackState(EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcTrackState State) override;`
- L159 _public prototype_ `virtual void OnVideoTrackEncodedFrame(EpicRtcStringView ParticipantId, EpicRtcVideoTrackInterface* VideoTrack, const EpicRtcEncodedVideoFrame& EncodedFrame) override;`
- L160 _public prototype_ `virtual EpicRtcBool Enabled() const override;`
- L164 _public prototype_ `virtual void OnDataTrackState(EpicRtcDataTrackInterface* DataTrack, const EpicRtcTrackState State) override;`
- L165 _public prototype_ `virtual void OnDataTrackMessage(EpicRtcDataTrackInterface* DataTrack, const EpicRtcDataFrame& DataFrame) override;`
- L166 _public prototype_ `virtual void OnDataTrackError(EpicRtcDataTrackInterface* DataTrack, const EpicRtcErrorCode Error) override;`
- L170 _public prototype_ `virtual void ConsumeFrame(FTextureRHIRef Frame) override;`
- L171 _public prototype_ `virtual void OnVideoConsumerAdded() override;`
- L172 _public prototype_ `virtual void OnVideoConsumerRemoved() override;`
- L176 _public prototype_ `virtual void ConsumeRawPCM(const int16_t* AudioData, int SampleRate, size_t NumChannels, size_t NumFrames) override;`
- L177 _public prototype_ `virtual void OnAudioConsumerAdded() override;`
- L178 _public prototype_ `virtual void OnAudioConsumerRemoved() override;`
- L181 _public prototype_ `void OnStatsReady(const FString& PeerId, const EpicRtcConnectionStats& ConnectionStats);`
- L184 _private member_ `EpicRtcSessionState SessionState = EpicRtcSessionState::Disconnected;`
- L187 _private member_ `TRefCountPtr<EpicRtcConferenceInterface> EpicRtcConference;`
- L188 _private member_ `TRefCountPtr<EpicRtcSessionInterface> EpicRtcSession;`
- L189 _private member_ `TRefCountPtr<EpicRtcRoomInterface> EpicRtcRoom;`
- L193 _private member_ `TRefCountPtr<FEpicRtcSessionObserver> SessionObserver;`
- L194 _private member_ `TRefCountPtr<FEpicRtcRoomObserver> RoomObserver;`
- L195 _private member_ `TRefCountPtr<FEpicRtcAudioTrackObserverFactory> AudioTrackObserverFactory;`
- L196 _private member_ `TRefCountPtr<FEpicRtcVideoTrackObserverFactory> VideoTrackObserverFactory;`
- L197 _private member_ `TRefCountPtr<FEpicRtcDataTrackObserverFactory> DataTrackObserverFactory;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/PlayerContext.h` (Private)


#### struct `UE::PixelStreaming2::FPlayerContext`  
`struct FPlayerContext`  
_L37-53_
- desc: NOTE: As all of these members are either ref counted, or shared pointers, usage MUST look something like TSharedPtr<TargetClass> Member; <-- Target member declared outside scope if(TSharedPtr<FPlayerContext> Participant = Particpants->FindRef(ParticipantId); Participant.IsValid()) { Member = Participant->Member; } if (Member) { Member->DoFunc(); } Using this pattern means that we won't be keeping all members of the player context alive longer than required
- L39 _public member_ `TRefCountPtr<EpicRtcParticipantInterface> ParticipantInterface;`
- L41 _public member_ `TSharedPtr<FEpicRtcAudioSink> AudioSink;`
- L42 _public member_ `TSharedPtr<FEpicRtcVideoSink> VideoSink;`
- L43 _public member_ `TSharedPtr<FEpicRtcDataTrack> DataTrack;`
- L47 _public member_ `FAtomicOnceFlag BroadcastLocalAudioTrackClosed;` — One shot flags to keep track of if the delegates for this player has already been broadcast to prevent multiple broadcasts
- L48 _public member_ `FAtomicOnceFlag BroadcastLocalVideoTrackClosed;`
- L49 _public member_ `FAtomicOnceFlag BroadcastRemoteAudioTrackClosed;`
- L50 _public member_ `FAtomicOnceFlag BroadcastRemoteVideoTrackClosed;`
- L52 _public member_ `TSharedPtr<FRTCStatsCollector> StatsCollector;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/RTCInputHandler.h` (Private)


#### class `UE::PixelStreaming2::FRTCInputHandler`  
`class FRTCInputHandler : public UE::PixelStreaming2Input::FPixelStreaming2InputHandler`  
_L9-94_
- inherits: `UE::PixelStreaming2Input::FPixelStreaming2InputHandler`
- L12 _public prototype_ `static TSharedPtr<FRTCInputHandler> Create();`
- L14 _public prototype_ `virtual ~FRTCInputHandler();`
- L17 _protected prototype_ `FRTCInputHandler();`
- L21 _protected prototype_ `void HandleOnTouchStarted(FMemoryReader Ar);` — Touch handling
- L22 _protected prototype_ `void HandleOnTouchMoved(FMemoryReader Ar);`
- L23 _protected prototype_ `void HandleOnTouchEnded(FMemoryReader Ar);`
- L27 _protected prototype_ `void HandleOnKeyChar(FMemoryReader Ar);` — Key press handling
- L28 _protected prototype_ `void HandleOnKeyDown(FMemoryReader Ar);`
- L29 _protected prototype_ `void HandleOnKeyUp(FMemoryReader Ar);`
- L33 _protected prototype_ `void HandleOnMouseEnter(FMemoryReader Ar);` — Mouse handling
- L34 _protected prototype_ `void HandleOnMouseLeave(FMemoryReader Ar);`
- L35 _protected prototype_ `void HandleOnMouseDown(FMemoryReader Ar);`
- L36 _protected prototype_ `void HandleOnMouseUp(FMemoryReader Ar);`
- L37 _protected prototype_ `void HandleOnMouseMove(FMemoryReader Ar);`
- L38 _protected prototype_ `void HandleOnMouseWheel(FMemoryReader Ar);`
- L39 _protected prototype_ `void HandleOnMouseDoubleClick(FMemoryReader Ar);`
- L43 _protected prototype_ `void HandleOnControllerConnected(FMemoryReader Ar);` — Controller handling
- L44 _protected prototype_ `void HandleOnControllerAnalog(FMemoryReader Ar);`
- L45 _protected prototype_ `void HandleOnControllerButtonPressed(FMemoryReader Ar);`
- L46 _protected prototype_ `void HandleOnControllerButtonReleased(FMemoryReader Ar);`
- L47 _protected prototype_ `void HandleOnControllerDisconnected(FMemoryReader Ar);`
- L51 _protected prototype_ `void HandleOnXREyeViews(FMemoryReader Ar);` — XR handling
- L52 _protected prototype_ `void HandleOnXRHMDTransform(FMemoryReader Ar);`
- L53 _protected prototype_ `void HandleOnXRControllerTransform(FMemoryReader Ar);`
- L54 _protected prototype_ `void HandleOnXRButtonTouched(FMemoryReader Ar);`
- L55 _protected prototype_ `void HandleOnXRButtonTouchReleased(FMemoryReader Ar);`
- L56 _protected prototype_ `void HandleOnXRButtonPressed(FMemoryReader Ar);`
- L57 _protected prototype_ `void HandleOnXRButtonReleased(FMemoryReader Ar);`
- L58 _protected prototype_ `void HandleOnXRAnalog(FMemoryReader Ar);`
- L59 _protected prototype_ `void HandleOnXRSystem(FMemoryReader Ar);`
- L63 _protected prototype_ `void HandleOnCommand(FString SourceId, FMemoryReader Ar);` — Command handling
- L67 _protected prototype_ `void HandleUIInteraction(FMemoryReader Ar);` — UI Interaction handling
- L71 _protected prototype_ `void HandleOnTextboxEntry(FMemoryReader Ar);` — Textbox Entry handling
- L77 _private prototype_ `void PopulateDefaultCommandHandlers();` — Populate default command handlers for data channel messages sent with "{ type: "Command" }".
- L82 _private prototype_ `FMatrix ExtractWebXRMatrix(FMemoryReader& Ar);` — Extract 4x4 WebXR ordered matrix and convert to FMatrix.
- L90 _private prototype_ `FTransform WebXRMatrixToUETransform(FMatrix Mat);` — Converts the 'Y up' 'right handed' WebXR coordinate system transform to Unreal's 'Z up' 'left handed' coordinate system. Note: Ignores scale. Assumes WebXR conforms to the following: (https://developer.mozilla.org/en-US/docs/Web/API/WebXR_Device_API/Geometry) @return A 4x4 z-up transform matrix for use with UE.
- L92 _private member_ `TMap<TTuple<EPixelStreaming2XRSystem, EControllerHand, uint8, EPixelStreaming2InputAction>, FKey> XRInputToFKey;`
- L93 _private member_ `TMap<TTuple<uint8, EPixelStreaming2InputAction>, FKey> GamepadInputToFKey;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/Stats.h` (Private)


#### struct `UE::PixelStreaming2::FRenderableStat`  
`struct FRenderableStat : public FStat`  
_L17-25_
- inherits: `FStat`
- desc: Stat that can be optionally rendered
- L19 _public function_ `FRenderableStat(FStat& Stat) : FStat(Stat)`
- L24 _public member_ `TOptional<FCanvasTextItem> Renderable;`

#### class `UE::PixelStreaming2::FStatGroup`  
`class FStatGroup`  
_L28-48_
- desc: A grouping of stats by some category name
- L31 _public function_ `FStatGroup(FName CategoryName) : GroupName(CategoryName) , CategoryCanvasItem(FVector2D(0, 0), FText::FromString(FString::Printf(TEXT("---%s---"), *CategoryName.ToString())), FSlateFontInfo(FSlateFontInfo(UEngine::GetSmallFont(), 12)), FLinearColor(0, 0.9f, 0.1f))`
- L38 _public prototype_ `virtual ~FStatGroup() = default;`
- L39 _public prototype_ `bool StoreStat(FStat& StatToStore);`
- L40 _public function_ `TMap<FName, FRenderableStat>& GetStoredStats()`
- L43 _private member_ `FName GroupName;`
- L44 _private member_ `TMap<FName, FRenderableStat> StoredStats;`
- L47 _public member_ `FCanvasTextItem CategoryCanvasItem;`

#### class `UE::PixelStreaming2::FPeerStats`  
`class FPeerStats`  
_L51-73_
- desc: Pixel Streaming stats that are associated with a specific peer.
- L55 _public function_ `FPeerStats(const FString& InAssociatedPlayer) : AssociatedPlayer(InAssociatedPlayer) , PlayerIdCanvasItem(FVector2D(0, 0), FText::FromString(FString::Printf(TEXT("[Peer Stats(%s)]"), *AssociatedPlayer)), FSlateFontInfo(FSlateFontInfo(UEngine::GetSmallFont(), 15)), FLinearColor(0, 1, 0))`
- L62 _public prototype_ `bool StoreStat(FName StatCategory, FStat& StatToStore);`
- L63 _public prototype_ `bool GetStat(FName StatCategory, FName StatToQuery, double& OutValue);`
- L64 _public function_ `TMap<FName, FStatGroup>& GetStatGroups()`
- L67 _private member_ `int DisplayId = 0;`
- L68 _private member_ `FString AssociatedPlayer;`
- L69 _private member_ `TMap<FName, FStatGroup> StatGroups;`
- L72 _public member_ `FCanvasTextItem PlayerIdCanvasItem;`

#### class `UE::PixelStreaming2::FStats`  
`class FStats : public FTickableGameObject, public IPixelStreaming2Stats`  
_L79-141_
- inherits: `FTickableGameObject,IPixelStreaming2Stats`
- desc: Stats about Pixel Streaming that can displayed either in the in-application HUD, in the log, or simply reported to some subscriber. Stats can be enabled to draw on screen with: `stat pixelstreaming2` `stat pixelstreaming2graphs`
- L82 _public function_ `virtual bool IsTickableInEditor() const override`
- L84 _public member_ `static constexpr double SmoothingPeriod = 3.0 * 60.0;`
- L85 _public member_ `static constexpr double SmoothingFactor = 10.0 / 100.0;`
- L86 _public prototype_ `static FStats* Get();`
- L88 _public prototype_ `FStats(const FStats&) = delete;`
- L89 _public prototype_ `bool QueryPeerStat(const FString& PlayerId, FName StatCategory, FName StatToQuery, double& OutValue);`
- L90 _public prototype_ `void RemovePeerStats(const FString& PlayerId);`
- L91 _public prototype_ `void RemoveAllPeerStats();`
- L92 _public prototype_ `void StorePeerStat(const FString& PlayerId, FName StatCategory, FStat Stat);`
- L93 _public prototype_ `void StoreApplicationStat(FStat PeerStat);`
- L94 _public prototype_ `void RemoveAllApplicationStats();`
- L95 _public prototype_ `void Tick(float DeltaTime);`
- L97 _public prototype_ `bool OnToggleStats(UWorld* World, FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L98 _public prototype_ `int32 OnRenderStats(UWorld* World, FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const FVector* ViewLocation, const FRotator* ViewRotation);`
- L100 _public prototype_ `bool OnToggleGraphs(UWorld* World, FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L101 _public prototype_ `int32 OnRenderGraphs(UWorld* World, FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const FVector* ViewLocation, const FRotator* ViewRotation);`
- L103 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L105 _public prototype_ `double AddTimeStat(double Millis, const FString& Label);`
- L106 _public prototype_ `double AddTimeDeltaStat(uint64 Millis1, uint64 Millis2, const FString& Label);`
- L107 _public prototype_ `void AddFrameTimingStats(const FPixelCaptureFrameMetadata& FrameMetadata, FIntPoint Resolution);`
- L108 _public prototype_ `void AddCanvasTile(FName Name, const FCanvasTileItem& Tile);`
- L112 _public prototype_ `void GraphValue(FName InName, float Value, int InSamples, float InMinRange, float InMaxRange, float InRefValue = 0.0f) override;`
- L116 _private prototype_ `FStats();`
- L118 _private prototype_ `void RegisterEngineHooks();`
- L119 _private prototype_ `void UpdateConsoleAutoComplete(TArray<FAutoCompleteCommand>& AutoCompleteList);`
- L121 _private prototype_ `void PollPixelStreaming2Settings();`
- L122 _private prototype_ `void FireStatChanged(const FString& PlayerId, FName StatName, float StatValue);`
- L123 _private prototype_ `void GraphValue_GameThread(FName InName, float Value, int InSamples, float InMinRange, float InMaxRange, float InRefValue);`
- L124 _private prototype_ `void AddCanvasTile_GameThread(FName Name, const FCanvasTileItem& Tile);`
- L127 _private member_ `static FStats* Instance;`
- L129 _private member_ `FCriticalSection PeerStatsCS;`
- L130 _private member_ `TMap<FString, FPeerStats> PeerStats;`
- L132 _private member_ `FCriticalSection ApplicationStatsCS;`
- L133 _private member_ `TMap<FName, FRenderableStat> ApplicationStats;`
- L135 _private member_ `int64 LastTimeSettingsPolledCycles = 0;`
- L137 _private member_ `TMap<FName, FDebugGraph> Graphs;`
- L138 _private member_ `TMap<FName, FCanvasTileItem> Tiles;`
- L140 _private member_ `FCriticalSection StatNotificationCS;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/UtilsCodecs.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L15 _variable_ `const TArray<EScalabilityMode> AllScalabilityModes = { EScalabilityMode::L1T1, EScalabilityMode::L1T2, EScalabilityMode::L1T3, EScalabilityMode::L2T1, EScalabilityMode::L2T1h, EScalabilityMode::L2T1_KEY, EScalabilityMode::L2T2, EScalabilityMode::L2T2h, EScalabilityMode::L2T2_KEY, EScalabilityMode::L2T2_KEY_SHIFT, EScalabilityMode::L2T3, EScalabilityMode::L2T3h, EScalabilityMode::L2T3_KEY, EScalabilityMode::L3T1, EScalabilityMode::L3T1h, EScalabilityMode::L3T1_KEY, EScalabilityMode::L3T2, EScalabilityMode::L3T2h, EScalabilityMode::L3T2_KEY, EScalabilityMode::L3T3, EScalabilityMode::L3T3h, EScalabilityMode::L3T3_KEY, EScalabilityMode::S2T1, EScalabilityMode::S2T1h, EScalabilityMode::S2T2, EScalabilityMode::S2T2h, EScalabilityMode::S2T3, EScalabilityMode::S2T3h, EScalabilityMode::S3T1, EScalabilityMode::S3T1h, EScalabilityMode::S3T2, EScalabilityMode::S3T2h, EScalabilityMode::S3T3, EScalabilityMode::S3T3h, EScalabilityMode::None };` (scope `UE::PixelStreaming2`) — Helper array for all scalability modes. EScalabilityMode::None must always be the last entry
- L91 _function_ `inline FString H264LevelToString(EH264Level Level)` (scope `UE::PixelStreaming2`)
- L135 _function_ `inline TOptional<FString> H264ProfileLevelToString(EH264Profile Profile, EH264Level Level)` (scope `UE::PixelStreaming2`)
- L190 _function_ `inline FEpicRtcParameterPairArray* CreateH264Format(EH264Profile Profile, EH264Level Level)` (scope `UE::PixelStreaming2`)
- L208 _function_ `inline FEpicRtcParameterPairArray* CreateVP9Format(EProfile Profile)` (scope `UE::PixelStreaming2`)
- L217 _function_ `inline EpicRtcVideoCodec ToEpicRtcVideoCodec(EVideoCodec Codec)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Private/UtilsCommon.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L8 _variable_ `static const FString SFU_PLAYER_ID_PREFIX = FString(TEXT("SFU_` (scope `UE::PixelStreaming2`)
- L10 _function_ `inline bool IsSFU(const FString& InPlayerId)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Public/IPixelStreaming2RTCModule.h` (Public)


#### class `IPixelStreaming2RTCModule`  
`class IPixelStreaming2RTCModule : public IModuleInterface`  
_L16-56_
- inherits: `IModuleInterface`
- desc: The IPixelStreaming2RTCModule interface manages the core functionality of the Pixel Streaming system. This class provides access to streamers, video and audio producers, and handles starting and stopping the streaming process. It also allows interaction with the signalling server and manages the lifecycle of streamers within the Pixel Streaming system.
- L25 _public function_ `static inline IPixelStreaming2RTCModule& Get()` — Singleton-like access to this module's interface. Beware calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L43 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreaming2RTCModule, FReadyEvent, IPixelStreaming2RTCModule&);` — Event fired when internal streamer is initialized and the methods on this module are ready for use.
- L49 _public prototype_ `virtual FReadyEvent& OnReady() = 0;` — A getter for the OnReady event. Intent is for users to call IPixelStreaming2RTCModule::Get().OnReady().AddXXX. @return The bindable OnReady event.
- L55 _public prototype_ `virtual bool IsReady() = 0;` — Is the PixelStreaming2 module actually ready to use? Is the streamer created. @return True if Pixel Streaming module methods are ready for use.

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreaming2RTCModule, FReadyEvent, IPixelStreaming2RTCModule&);` — Event fired when internal streamer is initialized and the methods on this module are ready for use.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Public/IPixelStreaming2Stats.h` (Public)


#### class `IPixelStreaming2Stats`  
`class IPixelStreaming2Stats`  
_L13-32_
- L20 _public prototype_ `static IPixelStreaming2Stats& Get();` — Singleton-like access to the Pixel Streaming stats public API. @return Returns singleton instance of Pixel Streaming stats.
- L31 _public prototype_ `virtual void GraphValue(FName InName, float Value, int InSamples, float InMinRange, float InMaxRange, float InRefValue = 0.0f) = 0;` — Graphs a value in a real-time plot that is visible when `stat PixelStreaming2Graphs` is used. If a graph of this name has not been graphed before this will also create the graph internally. @param InName The name of the stat to graph, this is used in the graph title and must be unique. @param InSamples The number of samples (along the x-axis) we wish to graph. @param InMinRange The minimum value we expect for this value we are graphing. @param InMaxRange The maximum value we expect for this value we are graphing. @param InRefValue A reference value that we draw in the graph as a horizontal line, this can be useful to see if we are within some threshold.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELSTREAMING2RTC_API`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2RTC/Public/PixelStreaming2StatNames.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PixelStreaming2StatNames`
- L12 _externvar_ `extern const FName Bitrate;` (scope `PixelStreaming2StatNames`)
- L13 _externvar_ `extern const FName BitrateMegabits;` (scope `PixelStreaming2StatNames`)
- L14 _externvar_ `extern const FName TargetBitrateMegabits;` (scope `PixelStreaming2StatNames`)
- L15 _externvar_ `extern const FName MeanSendDelay;` (scope `PixelStreaming2StatNames`)
- L16 _externvar_ `extern const FName SourceFps;` (scope `PixelStreaming2StatNames`)
- L17 _externvar_ `extern const FName Fps;` (scope `PixelStreaming2StatNames`)
- L18 _externvar_ `extern const FName MeanEncodeTime;` (scope `PixelStreaming2StatNames`)
- L19 _externvar_ `extern const FName EncodedFramesPerSecond;` (scope `PixelStreaming2StatNames`)
- L20 _externvar_ `extern const FName DecodedFramesPerSecond;` (scope `PixelStreaming2StatNames`)
- L21 _externvar_ `extern const FName MeanQPPerSecond;` (scope `PixelStreaming2StatNames`)
- L22 _externvar_ `extern const FName FramesSentPerSecond;` (scope `PixelStreaming2StatNames`)
- L23 _externvar_ `extern const FName FramesReceivedPerSecond;` (scope `PixelStreaming2StatNames`)
- L24 _externvar_ `extern const FName JitterBufferDelay;` (scope `PixelStreaming2StatNames`)
- L25 _externvar_ `extern const FName FramesSent;` (scope `PixelStreaming2StatNames`)
- L26 _externvar_ `extern const FName FramesReceived;` (scope `PixelStreaming2StatNames`)
- L27 _externvar_ `extern const FName FramesPerSecond;` (scope `PixelStreaming2StatNames`)
- L28 _externvar_ `extern const FName FramesDecoded;` (scope `PixelStreaming2StatNames`)
- L29 _externvar_ `extern const FName FramesDropped;` (scope `PixelStreaming2StatNames`)
- L30 _externvar_ `extern const FName FramesCorrupted;` (scope `PixelStreaming2StatNames`)
- L31 _externvar_ `extern const FName PartialFramesLost;` (scope `PixelStreaming2StatNames`)
- L32 _externvar_ `extern const FName FullFramesLost;` (scope `PixelStreaming2StatNames`)
- L33 _externvar_ `extern const FName HugeFramesSent;` (scope `PixelStreaming2StatNames`)
- L34 _externvar_ `extern const FName JitterBufferTargetDelay;` (scope `PixelStreaming2StatNames`)
- L35 _externvar_ `extern const FName InterruptionCount;` (scope `PixelStreaming2StatNames`)
- L36 _externvar_ `extern const FName TotalInterruptionDuration;` (scope `PixelStreaming2StatNames`)
- L37 _externvar_ `extern const FName FreezeCount;` (scope `PixelStreaming2StatNames`)
- L38 _externvar_ `extern const FName PauseCount;` (scope `PixelStreaming2StatNames`)
- L39 _externvar_ `extern const FName TotalFreezesDuration;` (scope `PixelStreaming2StatNames`)
- L40 _externvar_ `extern const FName TotalPausesDuration;` (scope `PixelStreaming2StatNames`)
- L41 _externvar_ `extern const FName FirCount;` (scope `PixelStreaming2StatNames`)
- L42 _externvar_ `extern const FName PliCount;` (scope `PixelStreaming2StatNames`)
- L43 _externvar_ `extern const FName NackCount;` (scope `PixelStreaming2StatNames`)
- L44 _externvar_ `extern const FName RetransmittedBytesSent;` (scope `PixelStreaming2StatNames`)
- L45 _externvar_ `extern const FName TargetBitrate;` (scope `PixelStreaming2StatNames`)
- L46 _externvar_ `extern const FName TotalEncodeBytesTarget;` (scope `PixelStreaming2StatNames`)
- L47 _externvar_ `extern const FName KeyFramesEncoded;` (scope `PixelStreaming2StatNames`)
- L48 _externvar_ `extern const FName FrameWidth;` (scope `PixelStreaming2StatNames`)
- L49 _externvar_ `extern const FName FrameHeight;` (scope `PixelStreaming2StatNames`)
- L50 _externvar_ `extern const FName BytesSent;` (scope `PixelStreaming2StatNames`)
- L51 _externvar_ `extern const FName BytesReceived;` (scope `PixelStreaming2StatNames`)
- L52 _externvar_ `extern const FName QPSum;` (scope `PixelStreaming2StatNames`)
- L53 _externvar_ `extern const FName TotalEncodeTime;` (scope `PixelStreaming2StatNames`)
- L54 _externvar_ `extern const FName TotalPacketSendDelay;` (scope `PixelStreaming2StatNames`)
- L55 _externvar_ `extern const FName FramesEncoded;` (scope `PixelStreaming2StatNames`)
- L56 _externvar_ `extern const FName AvgSendDelay;` (scope `PixelStreaming2StatNames`)
- L57 _externvar_ `extern const FName MessagesSent;` (scope `PixelStreaming2StatNames`)
- L58 _externvar_ `extern const FName MessagesReceived;` (scope `PixelStreaming2StatNames`)
- L59 _externvar_ `extern const FName PacketsLost;` (scope `PixelStreaming2StatNames`)
- L60 _externvar_ `extern const FName Jitter;` (scope `PixelStreaming2StatNames`)
- L61 _externvar_ `extern const FName RoundTripTime;` (scope `PixelStreaming2StatNames`)
- L62 _externvar_ `extern const FName KeyFramesDecoded;` (scope `PixelStreaming2StatNames`)
- L63 _externvar_ `extern const FName AudioLevel;` (scope `PixelStreaming2StatNames`)
- L64 _externvar_ `extern const FName TotalSamplesDuration;` (scope `PixelStreaming2StatNames`)
- L65 _externvar_ `extern const FName AvailableOutgoingBitrate;` (scope `PixelStreaming2StatNames`)
- L66 _externvar_ `extern const FName AvailableIncomingBitrate;` (scope `PixelStreaming2StatNames`)
- L67 _externvar_ `extern const FName RetransmittedBytesReceived;` (scope `PixelStreaming2StatNames`)
- L68 _externvar_ `extern const FName RetransmittedPacketsReceived;` (scope `PixelStreaming2StatNames`)
- L69 _externvar_ `extern const FName DataChannelBytesSent;` (scope `PixelStreaming2StatNames`)
- L70 _externvar_ `extern const FName DataChannelBytesReceived;` (scope `PixelStreaming2StatNames`)
- L71 _externvar_ `extern const FName DataChannelMessagesSent;` (scope `PixelStreaming2StatNames`)
- L72 _externvar_ `extern const FName DataChannelMessagesReceived;` (scope `PixelStreaming2StatNames`)
- L73 _externvar_ `extern const FName InputController;` (scope `PixelStreaming2StatNames`)
- L74 _externvar_ `extern const FName PacketsSent;` (scope `PixelStreaming2StatNames`)
- L75 _externvar_ `extern const FName EncoderImplementation;` (scope `PixelStreaming2StatNames`)
- L76 _externvar_ `extern const FName DecoderImplementation;` (scope `PixelStreaming2StatNames`)
- L77 _externvar_ `extern const FName MimeType;` (scope `PixelStreaming2StatNames`)
- L78 _externvar_ `extern const FName Channels;` (scope `PixelStreaming2StatNames`)
- L79 _externvar_ `extern const FName ClockRate;` (scope `PixelStreaming2StatNames`)
- L80 _externvar_ `extern const FName QualityLimitationReason;` (scope `PixelStreaming2StatNames`)
- L81 _externvar_ `extern const FName Rid;` (scope `PixelStreaming2StatNames`)
