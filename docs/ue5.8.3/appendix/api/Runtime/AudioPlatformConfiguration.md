# Runtime / AudioPlatformConfiguration

- module root: `Source/Runtime/AudioPlatformConfiguration`
- headers: 3; symbols: 67
- symbol kinds: class=1, delegate=1, enum=2, enumerator=10, function=4, macro=1, member=28, namespace=2, prototype=12, struct=5, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject
- PrivateIncludePathModuleNames: Engine
- PublicIncludePathModuleNames: CoreUObject

### `Source/Runtime/AudioPlatformConfiguration/Public/AudioCompressionSettings.h` (Public)


#### enum `ESoundwaveSampleRateSettings`  
`enum class ESoundwaveSampleRateSettings : uint8`  
_L14-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `Max`
- L17 _public enumerator_ `High`
- L18 _public enumerator_ `Medium`
- L19 _public enumerator_ `Low`
- L20 _public enumerator_ `Min`

#### struct `FAudioStreamCachingSettings`  
`struct FAudioStreamCachingSettings`  
_L28-53_
- desc: /
- L30 _public member_ `static constexpr int32 DefaultCacheSize = 64 * 1024;`
- L36 _public member_ `int32 CacheSizeKB;` — Target memory usage, in kilobytes. In the future settings for the cache can be more complex, but for now we set the max chunk size to 256 kilobytes, then set the number of elements in our cache as CacheSizeKB / 256.
- L39 _public member_ `bool bForceLegacyStreamChunking;` — Bool flag for keeping sounds flagged for streaming chunked in the style of the legacy streaming manager.
- L41 _public member_ `int32 ZerothChunkSizeForLegacyStreamChunkingKB;`
- L44 _public member_ `int32 MaxChunkSizeOverrideKB;` — will be ignored if < 0
- L46 _public function_ `FAudioStreamCachingSettings() : CacheSizeKB(DefaultCacheSize) , bForceLegacyStreamChunking(false) , ZerothChunkSizeForLegacyStreamChunkingKB(256) , MaxChunkSizeOverrideKB(INDEX_NONE)`

#### struct `FPlatformAudioCookOverrides`  
`struct FPlatformAudioCookOverrides`  
_L60-109_
- desc: /
- L65 _public prototype_ `static int32 GetStreamCachingVersion();` — Increment this return value to force a recook on all Stream Caching assets. For testing, it's useful to set this to either a negative number or absurdly large number, to ensure you do not pollute the DDC.
- L67 _public member_ `bool bResampleForDevice;`
- L70 _public member_ `TMap<ESoundwaveSampleRateSettings, float> PlatformSampleRates;` — Mapping of which sample rates are used for each sample rate quality for a specific platform.
- L73 _public member_ `float CompressionQualityModifier;` — Scales all compression qualities when cooking to this platform. For example, 0.5 will halve all compression qualities, and 1.0 will leave them unchanged.
- L76 _public member_ `int32 SoundCueCookQualityIndex = INDEX_NONE;` — If set, the cooker will keep only this level of quality
- L80 _public member_ `float AutoStreamingThreshold;` — When set to any platform > 0.0, this will automatically set any USoundWave beyond this value to be streamed from disk. If StreamCaching is set to true, this will be used
- L83 _public member_ `bool bInlineFirstAudioChunk = false;` — Wether to inline the first "Audio" chunk, which is typically chunk 1. (Only on assets marked retain-on-load with a size of audio in secs set)
- L88 _public member_ `float LengthOfFirstAudioChunkInSecs = 0.f;` — This will decide how much data to put in the first audio chunk. Anything <= 0 will be ignored. Must be combined with bInlineFirstAudioChunk, this will decide how much data to put in the first chunk. NOTE: This is platform default and can be overriden by each asset or soundclass.
- L91 _public member_ `FAudioStreamCachingSettings StreamCachingSettings;` — If Load On Demand is enabled, these settings are used to determine chunks and cache sizes.
- L93 _public function_ `FPlatformAudioCookOverrides() : bResampleForDevice(false) , CompressionQualityModifier(1.0f) , AutoStreamingThreshold(0.0f) , bInlineFirstAudioChunk(false) , LengthOfFirstAudioChunkInSecs(0.f)`
- L108 _public prototype_ `static void GetHashSuffix(const FPlatformAudioCookOverrides* InOverrides, FString& OutSuffix);` — This is used to invalidate compressed audio for a specific platform.

#### struct `FPlatformRuntimeAudioCompressionOverrides`  
`struct FPlatformRuntimeAudioCompressionOverrides`  
_L112-150_
- reflection: `USTRUCT()`
- L118 _public member_ `bool bOverrideCompressionTimes;` — `UPROPERTY(EditAnywhere, Category = "DecompressOnLoad")` — When true, overrides the Sound Group on each Sound Wave, and instead uses the Duration Threshold value to determine whether a sound should be fully decompressed during initial loading.
- L124 _public member_ `float DurationThreshold;` — `UPROPERTY(EditAnywhere, Category = "DecompressOnLoad")` — When Override Compression Times is set to true, any sound under this threshold (in seconds) will be fully decompressed on load. Otherwise the first chunk of this sound is cached at load and the rest is decompressed in real time. If set to zero, will default to the Sound Group on the relevant Sound Wave
- L129 _public member_ `int32 MaxNumRandomBranches;` — `UPROPERTY(EditAnywhere, Category = "SoundCueLoading", meta = (DisplayName = "Maximum Branches on Random SoundCue nodes", ClampMin = "0"))` — On this platform, any random nodes on Sound Cues will automatically only preload this number of branches and dispose of any others on load. This can drastically cut down on memory usage. If set to 0, no branches are culled.
- L133 _public member_ `int32 SoundCueQualityIndex = 1;` — `UPROPERTY(EditAnywhere, Category = "SoundCueLoading", meta = (DisplayName = "Quality Index for Sound Cues", ClampMin = "0", ClampMax = "50"))` — On this platform, use the specified quality at this index to override the quality used for SoundCues on this platform
- L135 _public prototype_ `FPlatformRuntimeAudioCompressionOverrides();`
- L138 _public function_ `static FPlatformRuntimeAudioCompressionOverrides* GetDefaultCompressionOverrides()` — Get singleton containing default settings for compression.
- L149 _private member_ `static FPlatformRuntimeAudioCompressionOverrides* DefaultCompressionOverrides;`

### `Source/Runtime/AudioPlatformConfiguration/Public/AudioPlatformConfigurationModule.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/AudioPlatformConfiguration/Public/AudioResampler.h` (Public)


#### enum `Audio::EResamplingMethod`  
`enum class EResamplingMethod : uint8`  
_L26-33_
- L28 _public enumerator_ `BestSinc = 0`
- L29 _public enumerator_ `ModerateSinc = 1`
- L30 _public enumerator_ `FastSinc = 2`
- L31 _public enumerator_ `ZeroOrderHold = 3`
- L32 _public enumerator_ `Linear = 4`

#### struct `Audio::FResamplingParameters`  
`struct FResamplingParameters`  
_L35-42_
- L37 _public member_ `EResamplingMethod ResamplerMethod;`
- L38 _public member_ `int32 NumChannels;`
- L39 _public member_ `float SourceSampleRate;`
- L40 _public member_ `float DestinationSampleRate;`
- L41 _public member_ `VectorOps::FAlignedFloatBuffer& InputBuffer;`

#### struct `Audio::FResamplerResults`  
`struct FResamplerResults`  
_L44-60_
- L46 _public member_ `VectorOps::FAlignedFloatBuffer* OutBuffer;`
- L48 _public member_ `float ResultingSampleRate;`
- L50 _public member_ `int32 InputFramesUsed;`
- L52 _public member_ `int32 OutputFramesGenerated;`
- L54 _public function_ `FResamplerResults() : OutBuffer(nullptr) , ResultingSampleRate(0.0f) , InputFramesUsed(0) , OutputFramesGenerated(0)`

#### class `Audio::FResampler`  
`class FResampler`  
_L71-84_
- L74 _public prototype_ `FResampler();`
- L75 _public prototype_ `~FResampler();`
- L77 _public prototype_ `void Init(EResamplingMethod ResamplingMethod, float StartingSampleRateRatio, int32 InNumChannels);`
- L78 _public prototype_ `void SetSampleRateRatio(float InRatio);`
- L79 _public prototype_ `int32 ProcessAudio(float* InAudioBuffer, int32 InSamples, bool bEndOfInput, float* OutAudioBuffer, int32 MaxOutputFrames, int32& OutNumFrames);`
- L82 _private prototype_ `TUniquePtr<FResamplerImpl> CreateImpl();`
- L83 _private member_ `TUniquePtr<FResamplerImpl> Impl;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define AUDIO_BUFFER_ALIGNMENT 16` — TODO: Move BufferVectorOperations AUDIO_BUFFER_ALIGNMENT define to more central location and reference here.
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioResampler, Warning, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioResampler, Warning, All);`
- L17 _namespace_ `namespace Audio`
- L21 _namespace_ `namespace VectorOps` (scope `Audio`)
- L23 _typedef_ `using FAlignedFloatBuffer = TArray<float, TAlignedHeapAllocator<AUDIO_BUFFER_ALIGNMENT>>;` (scope `Audio::VectorOps`)
- L63 _prototype_ `int32 GetOutputBufferSize(const FResamplingParameters& InParameters);` (scope `Audio`) — Get how large the output buffer should be for a resampling operation.
- L66 _prototype_ `bool Resample(const FResamplingParameters& InParameters, FResamplerResults& OutData);` (scope `Audio`) — Simple, inline resampler. Returns true on success, false otherwise.
