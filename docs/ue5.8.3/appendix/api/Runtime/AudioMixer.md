# Runtime / AudioMixer

- module root: `Source/Runtime/AudioMixer`
- headers: 40; symbols: 2761
- symbol kinds: class=55, delegate=29, enum=24, enumerator=193, externvar=2, function=162, macro=7, member=1000, namespace=39, prototype=1156, struct=73, typedef=19, variable=2
- PrivateDependencyModuleNames: AudioExtensions, AudioLinkCore, AudioMixerCore, AudioPlatformConfiguration, Engine, HeadMountedDisplay, NonRealtimeAudioRenderer, SignalProcessing, SoundFieldRendering, TraceLog
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: AudioLinkEngine, Core, CoreUObject
- PublicIncludePathModuleNames: Engine, TargetPlatform

### `Source/Runtime/AudioMixer/Classes/Generators/AudioGenerator.h` (Public)


#### struct `FAudioGeneratorHandle`  
`struct FAudioGeneratorHandle`  
_L11-18_
- L13 _public member_ `int32 Id;`
- L15 _public function_ `FAudioGeneratorHandle() : Id(INDEX_NONE)`

#### class `UAudioGenerator`  
`class UAudioGenerator : public UObject`  
_L23-55_
- reflection: `UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UObject`
- L28 _public prototype_ `UAudioGenerator();`
- L29 _public prototype_ `virtual ~UAudioGenerator();`
- L32 _public function_ `int32 GetSampleRate() const` — Returns the sample rate of the generator
- L35 _public function_ `int32 GetNumChannels() const` — Returns the number of channels of the generator
- L38 _public prototype_ `FAudioGeneratorHandle AddGeneratorDelegate(FOnAudioGenerate InFunction);` — Adds a generator delegate. Returns a handle for the generator delegate, so it can be removed.
- L41 _public prototype_ `void RemoveGeneratorDelegate(FAudioGeneratorHandle InHandle);` — Removes the given audio generator delegate handle
- L46 _protected prototype_ `void Init(int32 InSampleRate, int32 InNumChannels);` — Called by derived classes to initialize the sample rate and num channels of the generator
- L49 _protected prototype_ `void OnGeneratedAudio(const float* InAudio, int32 NumSamples);` — Called by derived classes when new audio is generated
- L51 _protected member_ `FCriticalSection CritSect;`
- L52 _protected member_ `int32 SampleRate;`
- L53 _protected member_ `int32 NumChannels;`
- L54 _protected member_ `TMap<uint32, FOnAudioGenerate> OnGeneratedMap;`

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef TFunction<void(const float * InAudio, int32 NumSamples)> FOnAudioGenerate;`

### `Source/Runtime/AudioMixer/Classes/Generators/SoundWaveScrubber.h` (Public)


#### class `Audio::FSoundWaveScrubber`  
`class FSoundWaveScrubber`  
_L24-174_
- desc: Class manages the runtime generation of scrubbed audio from a reference sound wave It does this using a simple granulation technique of overlapping grains using a Hanning window.
- L27 _public prototype_ `FSoundWaveScrubber();`
- L28 _public prototype_ `~FSoundWaveScrubber();`
- L31 _public prototype_ `void Init(TSharedRef<const FSoundWaveProxy> InSoundWaveProxyRef, float InSampleRate, int32 InNumChannels, float InPlayheadTimeSeconds = 0.0f);` — Initialize the sound wave scrubber
- L34 _public prototype_ `void Init(FSoundWaveProxyPtr InSoundWaveProxyPtr, float InSampleRate, int32 InNumChannels, float InPlayheadTimeSeconds = 0.0f);` — `UE_DEPRECATED(5.8, "Please use the TSharedRef<const FSoundWaveProxy> overload instead")`
- L37 _public prototype_ `void SetIsScrubbing(bool bInIsScrubbing);` — Sets whether or not to scrub the audio file. If false, then the output of the scrubber will be silence.
- L40 _public prototype_ `void SetIsScrubbingWhileStationary(bool bInIsScrubWhileStationary);` — Sets if the scrubber should scrub while playhead is stationary (after it hits it's target playhead)
- L43 _public prototype_ `void SetPlayheadTime(float InPlayheadTimeSeconds);` — Sets the scrubbing location in seconds
- L47 _public prototype_ `void SetGrainDurationRange(const FVector2D& InGrainDurationRange);` — Sets the grain duration range in seconds (clamped in range of of 0.01 to 0.5 seconds) The grain duration used during grain spawn is based the scrubbing speed. Sloweer the speed, the longer the grain.
- L50 _public prototype_ `int32 RenderAudio(TArrayView<float>& OutAudio);` — Renders the audio from the sound wave scrubber into the output audio buffer.
- L56 _private member_ `float AudioMixerSampleRate = 0.0f;` — General state and/or settings
- L57 _private member_ `float SourceFileSampleRate = 0.0f;`
- L58 _private member_ `float SourceFileDurationSeconds = 0.0f;`
- L59 _private member_ `int32 NumChannels = 0;`
- L62 _private member_ `static constexpr float DecodedAudioSizeInSeconds = 1.0f;` — How much audio to decode per decode block
- L67 _private member_ `float TargetPlayheadTimeSeconds = 0.0f;` — The current target playhead time in seconds The scrubber will interpolate to this if the current playhead time is less than a given threshold, otherwise the scrubber will "jump" to the playhead time.
- L70 _private member_ `float TimeSincePlayheadHasNotChanged = 0.0f;` — How long we've been stationary
- L73 _private member_ `FDynamicParameter CurrentPlayheadTimeSeconds;` — Interpolated playhead time
- L90 _private member_ `TArray<FDecodedDataChunk> DecodedChunks;` — Place to store decoded chunks. We need 2 chunks for actively playing grains plus a free chunk.
- L93 _private member_ `TSharedPtr<const FSoundWaveData> SoundWaveDataPtr;` — Sound wave data to safely query and use the referenced sound wave asset
- L95 _private member_ `TUniquePtr<FSoundWaveProxyPlayer> SoundWaveProxyPlayerPtr;` — Sound wave proxy player is a decoder we can use to decode audio into chunks
- L97 _private member_ `TUniquePtr<Audio::ISampleRateConverter> SRC;` — Simple SRC interface. Decoded audio is SRC'd to match the audio mixer sample rate
- L100 _private prototype_ `void DecodeToDataChunk(FDecodedDataChunk& InOutDataChunk, float InDecoderSeekTimeSeconds);` — Function utility to decode audio from the current sate to the given decoded data chunk
- L104 _private prototype_ `int32 GetDecodedDataChunkIndexForCurrentReadIndex(int32 InReadFrameIndex);` — This retrieves decoded data for the given read frame index. Returns INDEX_NONE if no decoded data was available for the given read index
- L108 _private prototype_ `int32 DecodeDataChunkIndexForCurrentReadIndex(int32 InReadFrameIndex);` — This function will decode the audio and cache it. Returns the index for the decoded chunk
- L113 _private member_ `Audio::Grain::FEnvelope GrainEnvelope;` — Data for granulation Envelope shared across grains
- L116 _private member_ `FVector2D TargetGrainDurationRange;` — The grain duration in frames
- L117 _private member_ `FVector2D GrainDurationRange;`
- L118 _private member_ `float GrainDurationSeconds = 0.0f;`
- L121 _private member_ `int32 CurrentGrainDurationFrames = 0;` — Grain duration as computed by scrub velocity based on the grain duration ranges
- L122 _private member_ `int32 CurrentHalfGrainDurationFrames = 0;`
- L126 _private member_ `int32 GrainCount = 0;` — Utility data useful for debugging the scrubber. The grain count is a running tally of the numebr of grains rendered
- L128 _private member_ `int32 NumActiveGrains = 0;` — This should never go above 2
- L148 _private member_ `TArray<FGrain> ActiveGrains;` — The grain data used to render the granular audio
- L151 _private member_ `int32 NumFramesTillNextGrainSpawn = 0;` — This is a frame count until we need to spawn another grain
- L154 _private prototype_ `FGrain SpawnGrain();` — Spawns a new grain at the value of the current playhead
- L157 _private prototype_ `void UpdateGrainDecodeData(FGrain& InGrain);` — Makes sure the grain is referencing valid decoded data
- L160 _private prototype_ `void RenderActiveGrains(TArrayView<float>& OutAudio, int32 InStartFrame, int32 InNumFramesToRender);` — Renders the grain, mixing it into the output buffer. Returns the frame index that is half
- L163 _private member_ `FCriticalSection CritSect;` — Used for setting user parameters
- L166 _private member_ `bool bIsScrubbing = false;` — Whether or not we're actively scrubbing audio playback.
- L167 _private member_ `bool bIsScrubbingDueToBeingStationary = true;`
- L170 _private member_ `bool bIsScrubbingWhileStationary = true;` — Whether or not we scrub while the playhead doesn't move
- L173 _private member_ `bool bHasErrorWithDecoder = false;` — Whether or not we have an error with the decoder

#### struct `Audio::FSoundWaveScrubber::FDecodedDataChunk`  
`struct FDecodedDataChunk`  
_L77-88_
- desc: Data for managing the decoded audio
- L80 _public member_ `int32 FrameStart = INDEX_NONE;` — The start frame of the decoded audio chunk
- L84 _public member_ `Audio::FAlignedFloatBuffer PCMAudio;` — The actual decoded audio. Size is NumFrames * NumChannels * AudioMixerSampleRate (after SRC)
- L87 _public member_ `int32 NumGrainsUsingChunk = 0;` — Count of the number of grains actively using this chunk

#### struct `Audio::FSoundWaveScrubber::FGrain`  
`struct FGrain`  
_L131-146_
- desc: Active grain data for a single grain
- L136 _public member_ `int32 CurrentRenderedFramesCount = INDEX_NONE;` — The number of frames this grain has rendered If this is larger than GrainDurationFrames it's an inactive grain this is used to look up the grain envelope to find the amplitude of the grain per frame
- L139 _public member_ `int32 DecodedDataChunkIndex = 0;` — Index into the decoded data array
- L142 _public member_ `int32 CurrentReadFrame = INDEX_NONE;` — The current read frame of the grain
- L145 _public member_ `int32 GrainDurationFrames = 0;` — The duration of this grain. Set when the grain spawns.

#### class `Audio::FSoundWaveScrubberGenerator`  
`class FSoundWaveScrubberGenerator : public ISoundGenerator`  
_L177-208_
- inherits: `ISoundGenerator`
- L180 _public prototype_ `void Init(TSharedRef<const FSoundWaveProxy> InSoundWaveProxyRef, float InSampleRate, int32 InNumChannels, float InPlayheadTimeSeconds = 0.0f);`
- L183 _public prototype_ `void Init(FSoundWaveProxyPtr InSoundWaveProxyPtr, float InSampleRate, int32 InNumChannels, float InPlayheadTimeSeconds = 0.0f);` — `UE_DEPRECATED(5.8, "Please use the TSharedRef<const FSoundWaveProxy> overload instead")`
- L186 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;`
- L187 _public prototype_ `virtual int32 GetDesiredNumSamplesToRenderPerCallback() const override;`
- L188 _public prototype_ `virtual bool IsFinished() const override;`
- L192 _public prototype_ `void SetIsScrubbing(bool bInIsScrubbing);` — Sets whether or not to scrub the audio file. If false, then the output of the scrubber will be silence.
- L195 _public prototype_ `void SetIsScrubbingWhileStationary(bool bInScrubWhileStationary);` — Sets if the scrubber should scrub while playhead is stationary (after it hits it's target playhead)
- L198 _public prototype_ `void SetPlayheadTime(float InPlayheadTimeSeconds);` — Sets the scrubbing location in seconds
- L202 _public prototype_ `void SetGrainDurationRange(const FVector2D& InGrainDurationRange);` — Sets the grain duration range in seconds (clamped in range of of 0.01 to 0.5 seconds) The grain duration used during grain spawn is based the scrubbing speed. Sloweer the speed, the longer the grain.
- L205 _private member_ `int32 NumChannels = 0;`
- L206 _private member_ `FSoundWaveScrubber SoundWaveScrubber;`

#### class `UScrubbedSound`  
`class UScrubbedSound : public USoundWave`  
_L214-262_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundWave`
- L220 _public prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L223 _public function_ `ISoundGeneratorPtr GetSoundGenerator()`
- L227 _public prototype_ `void SetSoundWave(USoundWave* InSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Scrubbing")` — Sets the sound wave to scrub
- L231 _public prototype_ `void SetPlayheadTime(float InPlayheadTimeSeconds);` — `UFUNCTION(BlueprintCallable, Category = "Scrubbing")` — Sets the scrub time in seconds
- L235 _public function_ `float GetPlayheadTime() const` — `UFUNCTION(BlueprintCallable, Category = "Scrubbing")` — Returns the current playhead time
- L239 _public prototype_ `void SetGrainDurationRange(const FVector2D& InGrainDurationRangeSeconds);` — `UFUNCTION(BlueprintCallable, Category = "Scrubbing")` — Sets the scrub grain duration range.
- L243 _public prototype_ `void SetIsScrubbing(bool bInIsScrubbing);` — `UFUNCTION(BlueprintCallable, Category = "Scrubbing")` — Sets if the scrubber is actively scrubbing or not
- L247 _public prototype_ `void SetIsScrubbingWhileStationary(bool bInScrubWhileStationary);` — `UFUNCTION(BlueprintCallable, Category = "Scrubbing")` — Sets if the scrubber should scrub while playhead is stationary (after it hits it's target playhead)
- L250 _private member_ `float PlayheadTimeSeconds = 0.0f;`
- L251 _private member_ `FVector2D GrainDurationRange = { 0.4f, 0.05f };`
- L253 _private member_ `bool bIsScrubbing = false;`
- L254 _private member_ `bool bScrubWhileStationary = true;`
- L255 _private member_ `float StationaryTimeSeconds = 0.1f;`
- L257 _private member_ `ISoundGeneratorPtr SoundWaveScrubber;`
- L260 _private member_ `TObjectPtr<USoundWave> SoundWaveToScrub;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOMIXER_API`
- L19 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Classes/SubmixEffects/AudioMixerSubmixEffectDynamicsProcessor.h` (Public)


#### enum `ESubmixEffectDynamicsProcessorType`  
`enum class ESubmixEffectDynamicsProcessorType : uint8`  
_L26-34_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Compressor = 0`
- L29 _public enumerator_ `Limiter`
- L30 _public enumerator_ `Expander`
- L31 _public enumerator_ `Gate`
- L32 _public enumerator_ `UpwardsCompressor`
- L33 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESubmixEffectDynamicsPeakMode`  
`enum class ESubmixEffectDynamicsPeakMode : uint8`  
_L37-43_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `MeanSquared = 0`
- L40 _public enumerator_ `RootMeanSquared`
- L41 _public enumerator_ `Peak`
- L42 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESubmixEffectDynamicsChannelLinkMode`  
`enum class ESubmixEffectDynamicsChannelLinkMode : uint8`  
_L46-52_
- reflection: `UENUM(BlueprintType)`
- L48 _public enumerator_ `Disabled = 0`
- L49 _public enumerator_ `Average`
- L50 _public enumerator_ `Peak`
- L51 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESubmixEffectDynamicsKeySource`  
`enum class ESubmixEffectDynamicsKeySource : uint8`  
_L55-67_
- reflection: `UENUM(BlueprintType)`
- L58 _public enumerator_ `Default = 0` — Defaults to use local submix (input) as key
- L61 _public enumerator_ `AudioBus` — Uses audio bus as key
- L64 _public enumerator_ `Submix` — Uses external submix as key
- L66 _public enumerator_ `Count UMETA(Hidden)`

#### class `FKeySource`  
`class FKeySource`  
_L69-137_
- L71 _private member_ `ESubmixEffectDynamicsKeySource Type = ESubmixEffectDynamicsKeySource::Default;`
- L72 _private member_ `int32 NumChannels = 0;`
- L73 _private member_ `uint32 ObjectId = INDEX_NONE;`
- L75 _private member_ `mutable FCriticalSection MutateSourceCritSection;`
- L78 _public member_ `Audio::FPatchOutputStrongPtr Patch;`
- L80 _public function_ `void Reset()`
- L92 _public function_ `uint32 GetObjectId() const`
- L98 _public function_ `int32 GetNumChannels() const`
- L104 _public function_ `ESubmixEffectDynamicsKeySource GetType() const`
- L110 _public function_ `void SetNumChannels(const int32 InNumChannels)`
- L116 _public function_ `void Update(ESubmixEffectDynamicsKeySource InType, uint32 InObjectId, int32 InNumChannels = 0)`

#### struct `FSubmixEffectDynamicProcessorFilterSettings`  
`struct FSubmixEffectDynamicProcessorFilterSettings`  
_L140-162_
- reflection: `USTRUCT(BlueprintType)`
- L146 _public member_ `uint8 bEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Enabled"))` — Whether or not filter is enabled
- L150 _public member_ `float Cutoff;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Cutoff (Hz)", EditCondition = "bEnabled", ClampMin = "20.0", ClampMax = "20000.0", UIMin = "20.0", UIMax = "20000.0"))` — The cutoff frequency of the HPF applied to key signal
- L154 _public member_ `float GainDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Gain (dB)", EditCondition = "bEnabled", ClampMin = "-60.0", ClampMax = "6.0", UIMin = "-60.0", UIMax = "6.0"))` — The gain of the filter shelf applied to the key signal
- L156 _public function_ `FSubmixEffectDynamicProcessorFilterSettings() : bEnabled(false) , Cutoff(20.0f) , GainDb(0.0f)`

#### struct `FSubmixEffectDynamicsProcessorSettings`  
`struct FSubmixEffectDynamicsProcessorSettings`  
_L166-266_
- reflection: `USTRUCT(BlueprintType)`
- desc: Submix dynamics processor settings
- L172 _public member_ `ESubmixEffectDynamicsProcessorType DynamicsProcessorType = ESubmixEffectDynamicsProcessorType::Compressor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Type"))` — Type of processor to apply
- L176 _public member_ `ESubmixEffectDynamicsPeakMode PeakMode = ESubmixEffectDynamicsPeakMode::Peak;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (EditCondition = "!bBypass"))` — Mode of peak detection used on input key signal
- L180 _public member_ `ESubmixEffectDynamicsChannelLinkMode LinkMode = ESubmixEffectDynamicsChannelLinkMode::Average;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (EditCondition = "!bBypass"))` — Mode of peak detection if key signal is multi-channel
- L184 _public member_ `float InputGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Input Gain (dB)", UIMin = "-12.0", UIMax = "20.0", EditCondition = "!bBypass"))` — The input gain of the dynamics processor
- L188 _public member_ `float ThresholdDb = -6.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (DisplayName = "Threshold (dB)", ClampMin = "-60.0", ClampMax = "0.0", UIMin = "-60.0", UIMax = "0.0", EditCondition = "!bBypass"))` — The threshold at which to perform a dynamics processing operation
- L194 _public member_ `float Ratio = 1.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = ( EditCondition = "!bBypass && DynamicsProcessorType == ESubmixEffectDynamicsProcessorType::Compressor || DynamicsProcessorType == ESubmixEffectDynamicsProcessorType::Expander || DynamicsProcessorType == ESubmixEffectDynamicsProcessorType::UpwardsCompressor", ClampMin = "1.0", ClampMax = "20.0", UIMin = "1.0", UIMax = "20.0"))` — The dynamics processor ratio used for compression/expansion
- L198 _public member_ `float KneeBandwidthDb = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (DisplayName = "Knee (dB)", ClampMin = "0.0", ClampMax = "20.0", UIMin = "0.0", UIMax = "20.0", EditCondition = "!bBypass"))` — The knee bandwidth of the processor to use
- L202 _public member_ `float LookAheadMsec = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (DisplayName = "Look Ahead (ms)", ClampMin = "0.0", ClampMax = "50.0", UIMin = "0.0", UIMax = "50.0", EditCondition = "!bBypass"))` — The amount of time to look ahead of the current audio (Allows for transients to be included in dynamics processing)
- L206 _public member_ `float AttackTimeMsec = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (DisplayName = "AttackTime (ms)", ClampMin = "1.0", ClampMax = "300.0", UIMin = "1.0", UIMax = "200.0", EditCondition = "!bBypass"))` — The amount of time to ramp into any dynamics processing effect
- L210 _public member_ `float ReleaseTimeMsec = 100.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (DisplayName = "Release Time (ms)", ClampMin = "20.0", ClampMax = "5000.0", UIMin = "20.0", UIMax = "5000.0", EditCondition = "!bBypass"))` — The amount of time to release the dynamics processing effect
- L213 _public member_ `ESubmixEffectDynamicsKeySource KeySource = ESubmixEffectDynamicsKeySource::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (EditCondition = "!bBypass"))`
- L217 _public member_ `TObjectPtr<UAudioBus> ExternalAudioBus = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (EditCondition = "!bBypass && KeySource == ESubmixEffectDynamicsKeySource::AudioBus", EditConditionHides))` — If set, uses output of provided audio bus as modulator of input signal for dynamics processor (Uses input signal as default modulator)
- L221 _public member_ `TObjectPtr<USoundSubmix> ExternalSubmix = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (EditCondition = "!bBypass && KeySource == ESubmixEffectDynamicsKeySource::Submix", EditConditionHides))` — If set, uses output of provided submix as modulator of input signal for dynamics processor (Uses input signal as default modulator)
- L224 _public member_ `uint8 bChannelLinked_DEPRECATED : 1;` — `UPROPERTY()`
- L228 _public member_ `uint8 bAnalogMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (EditCondition = "!bBypass"))` — Toggles treating the attack and release envelopes as analog-style vs digital-style (Analog will respond a bit more naturally/slower)
- L232 _public member_ `uint8 bBypass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Bypass", DisplayAfter = "DynamicsProcessorType"))` — Whether or not to bypass effect
- L236 _public member_ `uint8 bKeyAudition : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (DisplayName = "Key Audition", EditCondition = "!bBypass"))` — Audition the key modulation signal, bypassing enveloping and processing the input signal.
- L244 _public member_ `float KeyGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = ( DisplayName = "External Input Gain (dB)", EditCondition = "!bBypass && KeySource != ESubmixEffectDynamicsKeySource::Default", UIMin = "-60.0", UIMax = "30.0"))` — Gain to apply to key signal if key source not set to default (input).
- L248 _public member_ `float OutputGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Output, meta = (DisplayName = "Output Gain (dB)", UIMin = "-60.0", UIMax = "30.0", EditCondition = "!bBypass"))` — The output gain of the dynamics processor
- L252 _public member_ `FSubmixEffectDynamicProcessorFilterSettings KeyHighshelf;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (DisplayName = "Key Highshelf", EditCondition = "!bBypass"))` — High Shelf filter settings for key signal (external signal if supplied or input signal if not)
- L256 _public member_ `FSubmixEffectDynamicProcessorFilterSettings KeyLowshelf;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (DisplayName = "Key Lowshelf", EditCondition = "!bBypass"))` — Low Shelf filter settings for key signal (external signal if supplied or input signal if not)
- L258 _public function_ `FSubmixEffectDynamicsProcessorSettings() : bChannelLinked_DEPRECATED(true) , bAnalogMode(true) , bBypass(false) , bKeyAudition(false)`

#### class `FSubmixEffectDynamicsProcessor`  
`class FSubmixEffectDynamicsProcessor : public FSoundEffectSubmix`  
_L269-313_
- inherits: `FSoundEffectSubmix`
- L272 _public prototype_ `FSubmixEffectDynamicsProcessor();`
- L274 _public prototype_ `virtual ~FSubmixEffectDynamicsProcessor();`
- L277 _public prototype_ `Audio::FDeviceId GetDeviceId() const;` — Gets the effect's deviceId that owns it
- L280 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InInitData) override;` — Called on an audio effect at initialization on audio thread before audio processing begins.
- L283 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;` — Process the input block of audio. Called on audio render thread.
- L286 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L290 _protected prototype_ `Audio::FMixerDevice* GetMixerDevice();`
- L292 _protected prototype_ `void ResetKey();`
- L293 _protected prototype_ `void UpdateKeyFromSettings(const FSubmixEffectDynamicsProcessorSettings& InSettings);`
- L294 _protected prototype_ `bool UpdateKeySourcePatch();`
- L296 _protected prototype_ `void OnDeviceCreated(Audio::FDeviceId InDeviceId);`
- L297 _protected prototype_ `void OnDeviceDestroyed(Audio::FDeviceId InDeviceId);`
- L299 _protected member_ `Audio::FAlignedFloatBuffer AudioExternal;`
- L301 _protected member_ `Audio::FDeviceId DeviceId = INDEX_NONE;`
- L303 _protected member_ `bool bBypass = false;`
- L306 _private member_ `FKeySource KeySource;`
- L307 _private member_ `Audio::FDynamicsProcessor DynamicsProcessor;`
- L309 _private member_ `FDelegateHandle DeviceCreatedHandle;`
- L310 _private member_ `FDelegateHandle DeviceDestroyedHandle;`

#### class `USubmixEffectDynamicsProcessorPreset`  
`class USubmixEffectDynamicsProcessorPreset : public USoundEffectSubmixPreset`  
_L316-352_
- reflection: `UCLASS(ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L321 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectDynamicsProcessor) virtual void OnInit() override;`
- L325 _public prototype_ `virtual void Serialize(FStructuredArchive::FRecord Record) override;`
- L328 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& InChainEvent) override;`
- L332 _public prototype_ `void ResetKey();` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L337 _public prototype_ `void SetAudioBus(UAudioBus* AudioBus);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Sets the source key input as the provided AudioBus' output.  If no object is provided, key is set to effect's input.
- L342 _public prototype_ `void SetExternalSubmix(USoundSubmix* Submix);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Sets the source key input as the provided Submix's output.  If no object is provided, key is set to effect's input.
- L345 _public prototype_ `void SetSettings(const FSubmixEffectDynamicsProcessorSettings& Settings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L348 _public member_ `FSubmixEffectDynamicsProcessorSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (ShowOnlyInnerProperties))`
- L351 _private prototype_ `void SetKey(ESubmixEffectDynamicsKeySource InKeySource, UObject* InObject, int32 InNumChannels = 0);`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Dynamics"), STAT_AudioMixerSubmixDynamics, STATGROUP_AudioMixer, A` — The time it takes to process the master dynamics.
- L19 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Classes/SubmixEffects/AudioMixerSubmixEffectEQ.h` (Public)


#### struct `FSubmixEffectEQBand`  
`struct FSubmixEffectEQBand`  
_L17-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: A multiband EQ submix effect.
- L23 _public member_ `float Frequency = 500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer, meta = (EditCondition = "bEnabled", DisplayName = "Cutoff Frequency (hz)", ClampMin = "20.0", ClampMax = "20000.0", UIMin = "20.0", UIMax = "15000.0"))` — Cutoff frequency (in hz) of the EQ band
- L27 _public member_ `float Bandwidth = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer, meta = (EditCondition = "bEnabled", DisplayName = "Bandwidth (octaves)", ClampMin = "0.1", ClampMax = "2.0", UIMin = "0.1", UIMax = "2.0"))` — The bandwidth, in octaves, of the EQ band
- L31 _public member_ `float GainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer, meta = (EditCondition = "bEnabled", DisplayName = "Gain (dB)", ClampMin = "-90.0", ClampMax = "20.0", UIMin = "-90.0", UIMax = "20.0"))` — The gain in decibels of the EQ band
- L35 _public member_ `uint32 bEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer)` — Whether or not the EQ band is enabled
- L37 _public function_ `FSubmixEffectEQBand() : bEnabled(false)`

#### struct `FSubmixEffectSubmixEQSettings`  
`struct FSubmixEffectSubmixEQSettings`  
_L45-52_
- reflection: `USTRUCT(BlueprintType)`
- desc: EQ submix effect
- L51 _public member_ `TArray<FSubmixEffectEQBand> EQBands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubmixEffect|Preset")` — The EQ bands to use.

#### class `FSubmixEffectSubmixEQ`  
`class FSubmixEffectSubmixEQ : public FSoundEffectSubmix`  
_L54-107_
- inherits: `FSoundEffectSubmix`
- L57 _public prototype_ `FSubmixEffectSubmixEQ();`
- L60 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InSampleRate) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L63 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;` — Process the input block of audio. Called on audio thread.
- L66 _public prototype_ `virtual bool SetParameters(const FAudioEffectParameters& InParameters) override;` — Sets the effect parameters using the old audio engine preset setting object
- L68 _public function_ `virtual bool SupportsDefaultEQ() const override`
- L74 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L77 _protected prototype_ `void UpdateParameters(const int32 NumOutputChannels);`
- L91 _protected member_ `TArray<FEQ> FiltersPerChannel;` — Each of these filters is a 2 channel biquad filter. 1 for each stereo pair
- L93 _protected member_ `float ScratchInBuffer[2];`
- L94 _protected member_ `float ScratchOutBuffer[2];`
- L95 _protected member_ `float SampleRate;`
- L96 _protected member_ `float NumOutputChannels;`
- L97 _protected member_ `bool bEQSettingsSet;`
- L100 _protected member_ `Audio::TParams<FSubmixEffectSubmixEQSettings> PendingSettings;` — A pending eq setting change
- L103 _protected member_ `FSubmixEffectSubmixEQSettings GameThreadEQSettings;` — Game thread copy of the eq setting
- L106 _protected member_ `FSubmixEffectSubmixEQSettings RenderThreadEQSettings;` — Audio render thread copy of the eq setting

#### struct `FSubmixEffectSubmixEQ::FEQ`  
`struct FEQ`  
_L80-88_
- desc: An EQ effect is a bank of biquad filters
- L82 _public member_ `bool bEnabled;`
- L83 _public member_ `TArray<Audio::FBiquadFilter> Bands;`
- L85 _public function_ `FEQ() : bEnabled(true)`

#### class `USubmixEffectSubmixEQPreset`  
`class USubmixEffectSubmixEQPreset : public USoundEffectSubmixPreset`  
_L110-123_
- reflection: `UCLASS(ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L116 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectSubmixEQ) UFUNCTION(BlueprintCallable, Category = "Audio|Effects") void SetSettings(const FSubmixEffectSubmixEQSettings& InSettings);`
- L122 _public member_ `FSubmixEffectSubmixEQSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix EQ"), STAT_AudioMixerSubmixEQ, STATGROUP_AudioMixer, AUDIOMI` — The time it takes to process the master EQ effect.

### `Source/Runtime/AudioMixer/Classes/SubmixEffects/AudioMixerSubmixEffectReverb.h` (Public)


#### struct `FSubmixEffectReverbSettings`  
`struct FSubmixEffectReverbSettings`  
_L23-90_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `bool bBypassEarlyReflections = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EarlyReflections)` — Bypasses early reflections
- L33 _public member_ `float ReflectionsDelay = 0.007f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EarlyReflections, meta = (DisplayName = "Reflections Delay (seconds)", ClampMin = "0.0", ClampMax = "0.3", EditCondition = "!bBypass && !bBypassEarlyReflections"))` — Reflections Delay - 0.0 < 0.007 < 0.3 Seconds - the time between the listener receiving the direct path sound and the first reflection
- L37 _public member_ `float GainHF = 0.89f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EarlyReflections, meta = (DisplayName = "High Frequency Gain", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "!bBypass && !bBypassEarlyReflections"))` — Reverb Gain High Frequency - 0.0 < 0.89 < 1.0 - attenuates the high frequency reflected sound
- L41 _public member_ `float ReflectionsGain = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EarlyReflections, meta = (ClampMin = "0.0", ClampMax = "3.16", EditCondition = "!bBypass && !bBypassEarlyReflections"))` — Reflections Gain - 0.0 < 0.05 < 3.16 - controls the amount of initial reflections
- L45 _public member_ `bool bBypassLateReflections = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections)` — Bypasses late reflections.
- L49 _public member_ `float LateDelay = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (DisplayName = "Late Delay (seconds)", ClampMin = "0.0", ClampMax = "0.1", EditCondition = "!bBypass && !bBypassLateReflections"))` — Late Reverb Delay - 0.0 < 0.011 < 0.1 Seconds - time difference between late reverb and first reflections
- L53 _public member_ `float DecayTime = 1.49f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (DisplayName = "Decay Time (seconds)", ClampMin = "0.1", ClampMax = "20.0", EditCondition = "!bBypass && !bBypassLateReflections"))` — Decay Time - 0.1 < 1.49 < 20.0 Seconds - larger is more reverb
- L57 _public member_ `float Density = 0.85f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "!bBypass && !bBypassLateReflections"))` — Density - 0.0 < 0.85 < 1.0 - Coloration of the late reverb - lower value is more grainy
- L61 _public member_ `float Diffusion = 0.85f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "!bBypass && !bBypassLateReflections"))` — Diffusion - 0.0 < 0.85 < 1.0 - Echo density in the reverberation decay - lower is more grainy
- L65 _public member_ `float AirAbsorptionGainHF = 0.994f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (DisplayName = "High Frequency Air Absorption Gain", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "!bBypass && !bBypassLateReflections"))` — Air Absorption - 0.0 < 0.994 < 1.0 - lower value means more absorption
- L69 _public member_ `float DecayHFRatio = 0.83f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (DisplayName = "High Frequency Decay Ratio", ClampMin = "0.1", ClampMax = "2.0", EditCondition = "!bBypass && !bBypassLateReflections"))` — Decay High Frequency Ratio - 0.1 < 0.83 < 2.0 - how much quicker or slower the high frequencies decay relative to the lower frequencies.
- L73 _public member_ `float LateGain = 1.26f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (DisplayName = "Late Reflections Gain", ClampMin = "0.0", ClampMax = "10.0", EditCondition = "!bBypass && !bBypassLateReflections"))` — Late Reverb Gain - 0.0 < 1.26 < 10.0 - gain of the late reverb
- L77 _public member_ `float Gain = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LateReflections, meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "!bBypass && !bBypassLateReflections"))` — Reverb Gain - 0.0 < 0.32 < 1.0 - overall reverb gain - master volume control
- L81 _public member_ `float WetLevel = 0.3f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Routing, meta = (EditCondition = "!bBypass", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0"))` — Overall wet level of the reverb effect
- L85 _public member_ `float DryLevel = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Routing, meta = (EditCondition = "!bBypass", ClampMin = "0.0", ClampMax = "1.0"))` — Overall dry level of the reverb effect
- L89 _public member_ `bool bBypass = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)` — Bypasses reverb

#### class `FSubmixEffectReverb`  
`class FSubmixEffectReverb : public FSoundEffectSubmix`  
_L92-146_
- inherits: `FSoundEffectSubmix`
- L95 _public prototype_ `FSubmixEffectReverb();`
- L98 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InSampleRate) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L101 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L104 _public function_ `virtual uint32 GetDesiredInputChannelCountOverride() const override` — Forces receiving downmixed submix audio to stereo input for the reverb effect
- L107 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;` — Process the input block of audio. Called on audio thread.
- L110 _public prototype_ `virtual bool SetParameters(const FAudioEffectParameters& InParameters) override;` — Sets the reverb effect parameters based from audio thread code
- L113 _public function_ `virtual bool SupportsDefaultReverb() const override` — Whether this effect supports the default reverb system
- L119 _public function_ `virtual float GetDryLevel() const override` — Returns the drylevel of the effect
- L123 _private member_ `static const float MinWetness;`
- L124 _private member_ `static const float MaxWetness;`
- L126 _private prototype_ `void UpdateParameters();`
- L129 _private member_ `TUniquePtr<Audio::FPlateReverbFast> PlateReverb;` — The reverb effect
- L132 _private member_ `Audio::TParams<Audio::FPlateReverbFastSettings> ReverbParams;` — The reverb effect params
- L135 _private member_ `Audio::TParams<Audio::FWetDry> WetDryParams;` — Settings for wet and dry signal to be consumed on next buffer
- L138 _private member_ `Audio::FWetDry CurrentWetDry;` — Level of wet/dry signal on current buffer
- L140 _private member_ `Audio::FAlignedFloatBuffer WetInputBuffer;`
- L143 _private member_ `FRichCurve DecayCurve;` — Curve which maps old reverb times to new decay value
- L145 _private member_ `float SampleRate = 1.f;`

#### class `USubmixEffectReverbPreset`  
`class USubmixEffectReverbPreset : public USoundEffectSubmixPreset`  
_L149-166_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L154 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectReverb) virtual void PostInitProperties() override;`
- L159 _public prototype_ `void SetSettings(const FSubmixEffectReverbSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L162 _public prototype_ `void SetSettingsWithReverbEffect(const UReverbEffect* InReverbEffect, const float WetLevel, const float DryLevel = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L165 _public member_ `FSubmixEffectReverbSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Reverb"), STAT_AudioMixerSubmixReverb, STATGROUP_AudioMixer, AUD` — The time it takes to process the master reverb.

### `Source/Runtime/AudioMixer/Private/AudioMixerBuffer.h` (Private)


#### enum `Audio::EBufferType::Type`  
`enum Type`  
_L13-20_
- L15 _public enumerator_ `PCM`
- L16 _public enumerator_ `PCMPreview`
- L17 _public enumerator_ `PCMRealTime`
- L18 _public enumerator_ `Streaming`
- L19 _public enumerator_ `Invalid`

#### class `Audio::FMixerBuffer`  
`class FMixerBuffer : public FSoundBuffer`  
_L27-98_
- inherits: `FSoundBuffer`
- L30 _public prototype_ `FMixerBuffer(FAudioDevice* InAudioDevice, USoundWave* InWave, EBufferType::Type InBufferType);`
- L31 _public prototype_ `~FMixerBuffer();`
- L34 _public prototype_ `int32 GetSize() override;`
- L35 _public prototype_ `int32 GetCurrentChunkIndex() const override;`
- L36 _public prototype_ `int32 GetCurrentChunkOffset() const override;`
- L37 _public prototype_ `bool IsRealTimeSourceReady() override;`
- L38 _public prototype_ `bool ReadCompressedInfo(USoundWave* SoundWave) override;`
- L39 _public prototype_ `void Seek(const float SeekTime) override;`
- L42 _public prototype_ `static FMixerBuffer* Init(FAudioDevice* AudioDevice, USoundWave* InWave, bool bForceRealtime);`
- L43 _public prototype_ `static FMixerBuffer* CreatePreviewBuffer(FAudioDevice* AudioDevice, USoundWave* InWave);`
- L44 _public prototype_ `static FMixerBuffer* CreateProceduralBuffer(FAudioDevice* AudioDevice, USoundWave* InWave);`
- L45 _public prototype_ `static FMixerBuffer* CreateNativeBuffer(FAudioDevice* AudioDevice, USoundWave* InWave);`
- L46 _public prototype_ `static FMixerBuffer* CreateStreamingBuffer(FAudioDevice* AudioDevice, USoundWave* InWave);`
- L47 _public prototype_ `static FMixerBuffer* CreateRealTimeBuffer(FAudioDevice* AudioDevice, USoundWave* InWave);`
- L50 _public prototype_ `EBufferType::Type GetType() const;` — Returns the buffer's format
- L51 _public prototype_ `bool IsRealTimeBuffer() const;`
- L54 _public prototype_ `ICompressedAudioInfo* GetDecompressionState(bool bTakesOwnership = false);` — Retrieve the compressed audio info pointer. This transfers ownership of the decompression state.
- L57 _public prototype_ `void GetPCMData(uint8** OutData, uint32* OutDataSize);` — Returns the contained raw PCM data and data size
- L59 _public prototype_ `void EnsureHeaderParseTaskFinished();`
- L61 _public function_ `float GetSampleRate() const`
- L62 _public function_ `int32 GetNumChannels() const`
- L63 _public function_ `uint32 GetNumFrames() const`
- L64 _public function_ `void InitSampleRate(const float InSampleRate)`
- L65 _public function_ `void InitNumFrames(const uint32 InNumFrames)`
- L70 _private member_ `IAudioTask* RealtimeAsyncHeaderParseTask;` — Async task for parsing real-time decompressed compressed info headers.
- L73 _private member_ `ICompressedAudioInfo* DecompressionState;` — Wrapper to handle the decompression of audio codecs.
- L76 _private member_ `EBufferType::Type BufferType;` — Format of the sound referenced by this buffer
- L79 _private member_ `int32 SampleRate;` — Sample rate of the audio buffer.
- L82 _private member_ `uint32 NumFrames;` — Number of frames of the audio.
- L85 _private member_ `int16 BitsPerSample;` — Number of bits per sample.
- L88 _private member_ `uint8* Data;` — Ptr to raw PCM data.
- L91 _private member_ `uint32 DataSize;` — The raw PCM data size.
- L94 _private member_ `FThreadSafeBool bIsRealTimeSourceReady;` — Bool indicating the that the real-time source is ready for real-time decoding.
- L97 _private member_ `bool bIsDynamicResource;` — Set to true when the PCM data should be freed when the buffer is destroyed

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L11 _namespace_ `namespace EBufferType` (scope `Audio`)
- L101 _function_ `inline const TCHAR* LexToString(const Audio::EBufferType::Type In)`
- L103 _macro_ `#define CASE_TO_STRING(X) case X: return TEXT(#X);`

### `Source/Runtime/AudioMixer/Private/AudioMixerCVars.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AudioMixerCVars`
- L11 _externvar_ `extern int32 UseRenderScheduler;` (scope `AudioMixerCVars`) — This is used to decide whether or not to create a render scheduler when the mixer device is created. Most code should test FMixerDevice::UseRenderScheduler() instead of using this.

### `Source/Runtime/AudioMixer/Private/AudioMixerEffectsManager.h` (Private)


#### class `Audio::FAudioMixerEffectsManager`  
`class FAudioMixerEffectsManager : public FAudioEffectsManager`  
_L17-35_
- inherits: `FAudioEffectsManager`
- L20 _public prototype_ `FAudioMixerEffectsManager(FAudioDevice* InDevice);`
- L24 _public prototype_ `virtual void SetReverbEffectParameters(const FAudioEffectParameters& InEffectParameters) override;`
- L25 _public prototype_ `virtual void SetEQEffectParameters(const FAudioEffectParameters& InEffectParameters) override;`
- L26 _public prototype_ `virtual void SetRadioEffectParameters(const FAudioEffectParameters& InEffectParameters) override;`
- L30 _protected member_ `FRuntimeFloatCurve MasterReverbWetLevelCurve;`
- L33 _private member_ `FSoundEffectSubmixPtr InvalidReverbEffect;`
- L34 _private member_ `FSoundEffectSubmixPtr InvalidEQEffect;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Private/AudioMixerGeneratorSource.h` (Private)


#### class `Audio::FAudioMixerGeneratorSource`  
`class FAudioMixerGeneratorSource : public IAudioMixerGeneratorSource`  
_L12-27_
- inherits: `IAudioMixerGeneratorSource`
- L17 _public prototype_ `FAudioMixerGeneratorSource(FMixerDevice& InMixerDevice, ISoundGeneratorRef InGenerator);`
- L20 _public prototype_ `virtual void Play() override;`
- L21 _public prototype_ `virtual void Stop() override;`
- L23 _public prototype_ `virtual bool IsDone() override;`
- L25 _private member_ `FMixerDevice& MixerDevice;`
- L26 _private member_ `int32 SourceId = INDEX_NONE;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Private/AudioMixerSource.h` (Private)


#### enum `Audio::EMixerSourceInitializationState`  
`enum class EMixerSourceInitializationState : uint8`  
_L19-24_
- desc: State to track initialization stages.
- L21 _public enumerator_ `NotInitialized`
- L22 _public enumerator_ `Initializing`
- L23 _public enumerator_ `Initialized`

#### class `Audio::FMixerSource`  
`class FMixerSource : public FSoundSource, public ISourceListener`  
_L30-216_
- inherits: `FSoundSource,ISourceListener`
- desc: FMixerSource Class which implements a sound source object for the audio mixer module.
- L35 _public prototype_ `FMixerSource(FAudioDevice* InAudioDevice);` — Constructor.
- L38 _public prototype_ `~FMixerSource();` — Destructor.
- L41 _public prototype_ `virtual bool Init(FWaveInstance* InWaveInstance) override;`
- L42 _public prototype_ `virtual void Update() override;`
- L43 _public prototype_ `virtual bool PrepareForInitialization(FWaveInstance* InWaveInstance) override;`
- L44 _public prototype_ `virtual bool IsPreparedToInit() override;`
- L45 _public prototype_ `virtual bool IsInitialized() const override;`
- L46 _public prototype_ `virtual void Play() override;`
- L47 _public prototype_ `virtual void Stop() override;`
- L48 _public prototype_ `virtual void StopNow() override;`
- L49 _public function_ `virtual bool IsStopping() override`
- L50 _public prototype_ `virtual void Pause() override;`
- L51 _public prototype_ `virtual bool IsFinished() override;`
- L52 _public prototype_ `virtual float GetPlaybackPercent() const override;`
- L53 _public prototype_ `virtual int64 GetNumFramesPlayed() const override;`
- L54 _public prototype_ `virtual float GetEnvelopeValue() const override;`
- L55 _public prototype_ `virtual float GetRelativeRenderCost() const override;`
- L59 _public prototype_ `virtual void OnBeginGenerate() override;`
- L60 _public prototype_ `virtual void OnDone() override;`
- L61 _public prototype_ `virtual void OnEffectTailsDone() override;`
- L62 _public function_ `virtual void OnLoopEnd() override`
- L68 _private prototype_ `void SetupBusData(TArray<FInitAudioBusSend>* OutAudioBusSends = nullptr, bool bEnableBusSends = true);` — Initializes the bus sends.
- L71 _private prototype_ `void FreeResources();` — Frees any resources for this sound source.
- L74 _private prototype_ `void UpdatePitch();` — Updates the pitch parameter set from the game thread.
- L77 _private prototype_ `void UpdateVolume();` — Updates the volume parameter set from the game thread.
- L80 _private prototype_ `void UpdateSpatialization();` — Gets updated spatialization information for the voice.
- L83 _private prototype_ `void UpdateEffects();` — Updates and source effect on this voice.
- L86 _private prototype_ `void UpdateModulation();` — Updates the Modulation Routing settings on this voice.
- L89 _private prototype_ `void UpdateSourceBusSends();` — Updates source bus send levels based on game data.
- L92 _private prototype_ `void UpdateChannelMaps();` — Updates the channel map of the sound if its a 3d sound.
- L95 _private prototype_ `void UpdateRelativeRenderCost();` — Updates the relative render cost estimate of the playing sound source.
- L98 _private prototype_ `void UpdateCPUCoreUtilization();`
- L102 _private prototype_ `void SendSoundWaveStartTraceMessage() const;`
- L103 _private prototype_ `void SendSoundWaveStopTraceMessage() const;`
- L104 _private prototype_ `void UpdateIsAlivePingTraceMessage() const;`
- L108 _private prototype_ `bool ComputeMonoChannelMap(Audio::FAlignedFloatBuffer& OutChannelMap);` — Computes the mono-channel map.
- L111 _private prototype_ `bool ComputeStereoChannelMap(Audio::FAlignedFloatBuffer& OutChannelMap);` — Computes the stereo-channel map.
- L114 _private prototype_ `bool ComputeChannelMap(const int32 NumSourceChannels, Audio::FAlignedFloatBuffer& OutChannelMap);` — Compute the channel map based on the number of output and source channels.
- L117 _private prototype_ `bool UseObjectBasedSpatialization() const;` — Whether or not we should create the source voice with the HRTF spatializer.
- L120 _private prototype_ `bool IsUsingObjectBasedSpatialization() const;` — Whether or not existing or new sources will use the HRTF spatializer.
- L123 _private prototype_ `bool UseSpatializationPlugin() const;` — Whether or not to use the spatialization plugin.
- L126 _private prototype_ `bool UseOcclusionPlugin() const;` — Whether or not to use the occlusion plugin.
- L129 _private prototype_ `bool UseReverbPlugin() const;` — Whether or not to use the reverb plugin.
- L132 _private prototype_ `bool UseSourceDataOverridePlugin() const;` — Whether or not to use the source data override plugin
- L135 _private prototype_ `float GetInheritedSubmixVolumeModulation() const;` — Gets an accumulated volume value based on the Modulation Destination data of the WaveInstance's submix and all of the submix's ancestors
- L138 _private prototype_ `void UpdateSubmixSendLevels(const FSoundSubmixSendInfoBase& InSendInfo, EMixerSourceSubmixSendStage InSendStage, TSet<FMixerSubmixWeakPtr>& OutTouchedSubmixes);`
- L140 _private prototype_ `bool Is3D(const FSoundBuffer* SoundBuffer) const;`
- L142 _private member_ `FMixerDevice* MixerDevice;`
- L143 _private member_ `FMixerBuffer* MixerBuffer;`
- L144 _private member_ `TSharedPtr<FMixerSourceBuffer, ESPMode::ThreadSafe> MixerSourceBuffer;`
- L145 _private member_ `FMixerSourceVoice* MixerSourceVoice;`
- L146 _private member_ `IAudioLinkFactory::FAudioLinkSourcePushedSharedPtr AudioLink;`
- L147 _private member_ `FMixerSubmixWeakPtr PreviousSubmixResolved;`
- L148 _private member_ `TObjectKey<USoundSubmixBase> PrevousSubmix;`
- L151 _private member_ `bool bBypassingSubmixModulation;` — These modulators are obtained from the submix and used only on binaural assets
- L153 _private member_ `uint32 bPreviousBusEnablement;`
- L154 _private member_ `uint32 bPreviousBaseSubmixEnablement;`
- L180 _private member_ `Audio::FAlignedFloatBuffer ChannelMap;` — Mapping of channel map types to channel maps. Determined by what submixes this source sends its audio to.
- L181 _private member_ `FRWLock ChannelMapLock;`
- L183 _private member_ `float PreviousAzimuth;`
- L184 _private member_ `mutable float PreviousPlaybackPercent;`
- L186 _private member_ `FSpatializationParams SpatializationParams;`
- L188 _private member_ `EMixerSourceInitializationState InitializationState;`
- L190 _private member_ `FThreadSafeBool bPlayedCachedBuffer;`
- L191 _private member_ `FThreadSafeBool bPlaying;`
- L192 _private member_ `FThreadSafeBool bIsStopping;`
- L193 _private member_ `FThreadSafeBool bLoopCallback;`
- L194 _private member_ `FThreadSafeBool bIsDone;`
- L195 _private member_ `FThreadSafeBool bIsEffectTailsDone;`
- L196 _private member_ `FThreadSafeBool bIsPlayingEffectTails;`
- L197 _private member_ `FThreadSafeBool bFreeAsyncTask;`
- L201 _private member_ `TArray<FDynamicBusSendInfo> DynamicBusSendInfos;` — Array of copied FSoundSourceBusSendInfo data for all the bus sends this source may need to live-update during its lifespan
- L204 _private member_ `TSet<FMixerSubmixWeakPtr> PreviousSubmixSends;` — An array of submixes from previous update. Allows us to clear out submix sends if they are no longer being sent.
- L207 _private member_ `FThreadSafeBool bIsReleasing;` — Whether or not we're currently releasing our resources. Prevents recycling the source until release is finished.
- L209 _private member_ `uint32 bEditorWarnedChangedSpatialization : 1;`
- L210 _private member_ `uint32 bIs3D : 1;`
- L211 _private member_ `uint32 bDebugMode : 1;`
- L212 _private member_ `uint32 bIsVorbis : 1;`
- L213 _private member_ `uint32 bIsStoppingVoicesEnabled : 1;`
- L214 _private member_ `uint32 bSendingAudioToBuses : 1;`
- L215 _private member_ `uint32 bPrevAllowedSpatializationSetting : 1;`

#### struct `Audio::FMixerSource::FDynamicBusSendInfo`  
`struct FDynamicBusSendInfo`  
_L158-177_
- desc: This holds data copied from FSoundSourceBusSendInfo when a new sound starts playing so that distance-based level control can be calculated during rendering
- L160 _public member_ `float SendLevel = 0.0f;`
- L161 _public member_ `uint32 BusId = 0;`
- L163 _public member_ `FString BusName;`
- L165 _public member_ `ESourceBusSendLevelControlMethod BusSendLevelControlMethod = ESourceBusSendLevelControlMethod::Manual;`
- L166 _public member_ `EBusSendType BusSendType = EBusSendType::PreEffect;`
- L167 _public member_ `float MinSendLevel = 0.0f;`
- L168 _public member_ `float MaxSendLevel = 0.0f;`
- L169 _public member_ `float MinSendDistance = 0.0f;`
- L170 _public member_ `float MaxSendDistance = 0.0f;`
- L171 _public member_ `FRuntimeFloatCurve CustomSendLevelCurve;`
- L172 _public member_ `bool bIsInit = true;`
- L173 _public member_ `FSendFilterSettings Filter;`
- L176 _public member_ `bool bFilterStateChanged = false;` — Set when filter params change via the bHasNewBusSends path so the dynamic tick loop re-sends the update even if send level didn't change.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L219 _function_ `inline const TCHAR* LexToString(const Audio::EMixerSourceInitializationState State)`

### `Source/Runtime/AudioMixer/Private/AudioMixerSourceBuffer.h` (Private)


#### struct `Audio::FRawPCMDataBuffer`  
`struct FRawPCMDataBuffer`  
_L19-36_
- L21 _public member_ `uint8* Data;`
- L22 _public member_ `uint32 DataSize;`
- L23 _public member_ `int32 LoopCount;`
- L24 _public member_ `uint32 CurrentSample;`
- L25 _public member_ `uint32 NumSamples;`
- L27 _public prototype_ `bool GetNextBuffer(TArrayView<float> OutSourceBufferPtr, const uint32 NumSampleToGet);`
- L29 _public function_ `FRawPCMDataBuffer() : Data(nullptr) , DataSize(0) , LoopCount(0) , CurrentSample(0) , NumSamples(0)`

#### enum `Audio::EBufferReadMode`  
`enum class EBufferReadMode : uint8`  
_L39-46_
- desc: Enum describing the data-read mode of an audio buffer.
- L42 _public enumerator_ `Asynchronous` — Read the next buffer asynchronously.
- L45 _public enumerator_ `AsynchronousSkipFirstFrame` — Read the next buffer asynchronously but skip the first chunk of audio.

#### struct `Audio::FMixerSourceBufferInitArgs`  
`struct FMixerSourceBufferInitArgs`  
_L50-64_
- L52 _public member_ `FDeviceId AudioDeviceID = 0;`
- L53 _public member_ `uint64 AudioComponentID = 0;`
- L54 _public member_ `uint64 InstanceID = 0;`
- L55 _public member_ `int32 SampleRate = 0;`
- L56 _public member_ `int32 AudioMixerNumOutputFrames = 0;`
- L57 _public member_ `FMixerBuffer* Buffer = nullptr;`
- L58 _public member_ `USoundWave* SoundWave = nullptr;`
- L59 _public member_ `ELoopingMode LoopingMode = ELoopingMode::LOOP_Never;`
- L60 _public member_ `float StartTime = 0.0f;`
- L61 _public member_ `bool bIsSeeking = false;`
- L62 _public member_ `bool bForceSyncDecode = false;`
- L63 _public member_ `bool bIsPreviewSound = false;`

#### class `Audio::FMixerSourceBuffer`  
`class FMixerSourceBuffer : public ISoundWaveClient`  
_L67-201_
- inherits: `ISoundWaveClient`
- desc: Class which handles decoding audio for a particular source buffer.
- L70 _public prototype_ `static FMixerSourceBufferPtr Create(FMixerSourceBufferInitArgs& InArgs, TArray<FAudioParameter>&& InDefaultParams=TArray<FAudioParameter>());`
- L72 _public prototype_ `~FMixerSourceBuffer();`
- L74 _public prototype_ `bool Init();`
- L77 _public prototype_ `void SetDecoder(ICompressedAudioInfo* InCompressedAudioInfo);` — Sets the decoder to use for realtime async decoding
- L80 _public prototype_ `void SetPCMData(const FRawPCMDataBuffer& InPCMDataBuffer);` — Sets the raw PCM data buffer to use for the source buffer
- L83 _public prototype_ `void SetCachedRealtimeFirstBuffers(TArray<uint8>&& InPrecachedBuffer);` — Sets the precached buffers
- L86 _public prototype_ `void OnBufferEnd();` — Called by source manager when needing more buffers
- L89 _public prototype_ `int32 GetNumBuffersQueued() const;` — Return the number of buffers enqueued on the mixer source buffer
- L92 _public prototype_ `TSharedPtr<FAlignedFloatBuffer, ESPMode::ThreadSafe> GetNextBuffer();` — Returns the next enqueued buffer, returns nullptr if no buffers enqueued
- L95 _public function_ `bool DidBufferLoop() const` — Returns if buffer looped
- L98 _public function_ `bool DidBufferFinish() const` — Returns true if buffer finished
- L101 _public prototype_ `bool IsEndOfAudio() const;` — Returns true if the last buffer has been read
- L104 _public prototype_ `bool ReadMoreRealtimeData(ICompressedAudioInfo* InDecoder, int32 BufferIndex, EBufferReadMode BufferReadMode);` — Called to start an async task to read more data
- L107 _public prototype_ `bool IsAsyncTaskInProgress() const;` — Returns true if async task is in progress
- L110 _public prototype_ `bool IsAsyncTaskDone() const;` — Returns true if the async task is done
- L113 _public prototype_ `uint64 GetInstanceID() const;` — Get the unique instance ID (transmitter ID) for the source
- L123 _public prototype_ `void GetDiagnosticState(FDiagnosticState& OutState);`
- L126 _public prototype_ `void EnsureAsyncTaskFinishes();` — Ensures the async task finishes
- L129 _public prototype_ `void OnBeginGenerate();`
- L130 _public prototype_ `void OnEndGenerate();`
- L131 _public function_ `void ClearWave()`
- L134 _public prototype_ `double GetCPUCoreUtilization() const;`
- L138 _public prototype_ `float GetRelativeRenderCost() const;` — Returns the runtime render cost
- L141 _public prototype_ `void DoProceduralRendering(const FProceduralAudioTaskData& ProceduralTaskData, FProceduralAudioTaskResults& ProceduralResult);` — Note: can be called either directly on the rendering thread or from a background decode task.
- L142 _public prototype_ `void FinishProceduralRendering(const FProceduralAudioTaskResults& TaskResult);`
- L145 _private prototype_ `FMixerSourceBuffer(FMixerSourceBufferInitArgs& InArgs, TArray<FAudioParameter>&& InDefaultParams);`
- L147 _private prototype_ `void SubmitInitialPCMBuffers();`
- L148 _private prototype_ `void SubmitInitialRealtimeBuffers();`
- L149 _private prototype_ `void SubmitRealTimeSourceData(const bool bFinishedOrLooped);`
- L150 _private prototype_ `void ProcessRealTimeSource();`
- L151 _private prototype_ `void SubmitBuffer(TSharedPtr<FAlignedFloatBuffer, ESPMode::ThreadSafe> InSourceVoiceBuffer);`
- L152 _private prototype_ `void DeleteDecoder();`
- L153 _private prototype_ `void ConnectToBuses();`
- L155 _private member_ `int32 NumBuffersQueued;`
- L156 _private member_ `FRawPCMDataBuffer RawPCMDataBuffer;`
- L158 _private member_ `TArray<TSharedPtr<FAlignedFloatBuffer, ESPMode::ThreadSafe>> SourceVoiceBuffers;`
- L159 _private member_ `TQueue<TSharedPtr<FAlignedFloatBuffer, ESPMode::ThreadSafe>> BufferQueue;`
- L160 _private member_ `int32 CurrentBuffer;`
- L162 _private member_ `USoundWave* SoundWave;` — SoundWaves are only set for procedural sound waves
- L163 _private member_ `ISoundGeneratorPtr SoundGenerator;`
- L164 _private member_ `IAudioTask* AsyncRealtimeAudioTask;`
- L165 _private member_ `ICompressedAudioInfo* DecompressionState;`
- L166 _private member_ `ELoopingMode LoopingMode;`
- L167 _private member_ `int32 NumChannels;`
- L168 _private member_ `Audio::EBufferType::Type BufferType;`
- L169 _private member_ `int32 NumPrecacheFrames;`
- L170 _private member_ `Audio::FDeviceId AuioDeviceID;`
- L171 _private member_ `uint64 InstanceID;`
- L172 _private member_ `TArray<uint8> CachedRealtimeFirstBuffer;`
- L173 _private member_ `FName WaveName;`
- L174 _private member_ `uint64 AsyncTaskStartTimeInCycles=0;`
- L177 _private member_ `int32 SampleRate = 0;`
- L178 _private member_ `std::atomic<double> CPUCoreUtilization = 0.0;`
- L179 _private prototype_ `void UpdateCPUCoreUtilization(double InCPUTime, double InAudioTime);`
- L182 _private member_ `std::atomic<float> RelativeRenderCost = 1.0f;`
- L183 _private prototype_ `void SetRelativeRenderCost(float InRelativeRenderCost);`
- L185 _private member_ `mutable FCriticalSection SoundWaveCritSec;`
- L186 _private member_ `mutable FCriticalSection DecodeTaskCritSec;`
- L188 _private member_ `uint32 bInitialized : 1;`
- L189 _private member_ `uint32 bBufferFinished : 1;`
- L190 _private member_ `uint32 bPlayedCachedBuffer : 1;`
- L191 _private member_ `uint32 bIsSeeking : 1;`
- L192 _private member_ `uint32 bLoopCallback : 1;`
- L193 _private member_ `uint32 bProcedural : 1;`
- L194 _private member_ `uint32 bIsBus : 1;`
- L195 _private member_ `uint32 bForceSyncDecode : 1;`
- L196 _private member_ `uint32 bHasError : 1;`
- L198 _private prototype_ `virtual bool OnBeginDestroy(class USoundWave* Wave) override;`
- L199 _private prototype_ `virtual bool OnIsReadyForFinishDestroy(class USoundWave* Wave) const override;`
- L200 _private prototype_ `virtual void OnFinishDestroy(class USoundWave* Wave) override;`

#### struct `Audio::FMixerSourceBuffer::FDiagnosticState`  
`struct FDiagnosticState`  
_L116-122_
- desc: Returns some diagnostic state
- L118 _public member_ `FName WaveName;`
- L119 _public member_ `float RunTimeInSecs=0.f;`
- L120 _public member_ `bool bInFlight=false;`
- L121 _public member_ `bool bProcedural=false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`
- L13 _variable_ `static const int32 MAX_BUFFERS_QUEUED = 3;` (scope `Audio`)
- L14 _variable_ `static const int32 LOOP_FOREVER = -1;` (scope `Audio`)
- L48 _typedef_ `using FMixerSourceBufferPtr = TSharedPtr<class FMixerSourceBuffer, ESPMode::ThreadSafe>;` (scope `Audio`)

### `Source/Runtime/AudioMixer/Private/AudioMixerSourceDecode.h` (Private)


#### struct `Audio::FDecodeAudioTaskData`  
`struct FDecodeAudioTaskData`  
_L17-58_
- desc: Data needed for a decode audio task
- L20 _public member_ `float* AudioData;` — A pointer to a buffer of audio which will be decoded to
- L23 _public member_ `ICompressedAudioInfo* DecompressionState;` — Decompression state for decoder
- L26 _public member_ `Audio::EBufferType::Type BufferType;` — The buffer type for the decoder
- L29 _public member_ `int32 NumChannels;` — Number of channels of the decoder
- L32 _public member_ `int32 NumPrecacheFrames;` — The number of frames which are precached
- L35 _public member_ `int32 NumFramesToDecode;` — The number of frames to decode
- L38 _public member_ `bool bLoopingMode;` — Whether or not this sound is intending to be looped
- L41 _public member_ `bool bSkipFirstBuffer;` — Whether or not to skip the first buffer
- L45 _public member_ `bool bForceSyncDecode;` — Force this decoding operation to occur synchronously, regardless of the value of au.ForceSyncAudioDecodes. (used by time synth)
- L47 _public function_ `FDecodeAudioTaskData() : AudioData(nullptr) , DecompressionState(nullptr) , BufferType(Audio::EBufferType::Invalid) , NumChannels(0) , NumPrecacheFrames(0) , NumFramesToDecode(0) , bLoopingMode(false) , bSkipFirstBuffer(false) , bForceSyncDecode(false)`

#### struct `Audio::FHeaderParseAudioTaskData`  
`struct FHeaderParseAudioTaskData`  
_L61-73_
- desc: Data needed for a header parse audio task
- L64 _public member_ `FMixerBuffer* MixerBuffer;` — The mixer buffer object which results will be written to
- L67 _public member_ `USoundWave* SoundWave;` — The sound wave object which contains the encoded file
- L69 _public function_ `FHeaderParseAudioTaskData() : MixerBuffer(nullptr) , SoundWave(nullptr)`

#### struct `Audio::FDecodeAudioTaskResults`  
`struct FDecodeAudioTaskResults`  
_L76-90_
- desc: Results from decode audio task
- L80 _public member_ `bool bIsFinishedOrLooped;` — Whether or not the audio buffer looped
- L81 _public member_ `int32 NumSamplesWritten = 0;`
- L84 _public member_ `double CPUDuration = 0;`
- L87 _public function_ `FDecodeAudioTaskResults() : bIsFinishedOrLooped(false)`

#### enum `Audio::EAudioTaskType`  
`enum class EAudioTaskType`  
_L93-103_
- desc: The types of audio tasks
- L96 _public enumerator_ `Header` — The job is a header decode job
- L99 _public enumerator_ `Decode` — The job is a decode job
- L102 _public enumerator_ `Invalid` — The job is invalid (or unknown)

#### class `Audio::IAudioTask`  
`class IAudioTask`  
_L106-125_
- desc: Handle to an in-flight decode job. Can be queried and used on any thread.
- L109 _public prototype_ `virtual ~IAudioTask() = default;`
- L112 _public prototype_ `virtual bool IsDone() const = 0;` — Queries if the decode job has finished.
- L115 _public prototype_ `virtual EAudioTaskType GetType() const = 0;` — Returns the job type of the handle.
- L118 _public prototype_ `virtual void EnsureCompletion() = 0;` — Ensures the completion of the decode operation.
- L121 _public prototype_ `virtual void CancelTask() = 0;` — Cancel the decode operation
- L124 _public function_ `virtual void GetResult(FDecodeAudioTaskResults& OutResult)` — Returns the result of a decode job

#### struct `Audio::FScopeDecodeTimer`  
`struct FScopeDecodeTimer`  
_L134-152_
- L136 _public function_ `FScopeDecodeTimer(double* OutResultSeconds) : Result(OutResultSeconds)`
- L141 _public function_ `~FScopeDecodeTimer()`
- L150 _public member_ `double* Result = nullptr;`
- L151 _public member_ `uint64 StartCycle = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
- L128 _prototype_ `IAudioTask* CreateAudioTask(Audio::FDeviceId InDeviceId, const FHeaderParseAudioTaskData& InJobData);` (scope `Audio`) — Creates a task to decode a decoded file header
- L131 _prototype_ `IAudioTask* CreateAudioTask(Audio::FDeviceId InDeviceId, const FDecodeAudioTaskData& InJobData);` (scope `Audio`) — Creates a task to decode a chunk of audio

### `Source/Runtime/AudioMixer/Private/AudioMixerSourceManager.h` (Private)


#### enum `ESourceManagerRenderThreadPhase`  
`enum class ESourceManagerRenderThreadPhase: uint8`  
_L54-72_
- reflection: `UENUM()`
- desc: For diagnostics, keep track of what phase of updating the Source manager is in currently.
- L56 _public enumerator_ `Begin`
- L58 _public enumerator_ `PumpMpscCmds`
- L59 _public enumerator_ `PumpCmds`
- L60 _public enumerator_ `ProcessModulators`
- L61 _public enumerator_ `UpdatePendingReleaseData`
- L62 _public enumerator_ `RunScheduledRenderSteps`
- L63 _public enumerator_ `GenerateSrcAudio_WithBusses`
- L64 _public enumerator_ `ComputeBusses`
- L65 _public enumerator_ `GenerateSrcAudio_WithoutBusses`
- L66 _public enumerator_ `UpdateBusses`
- L67 _public enumerator_ `SpatialInterface_OnAllSourcesProcessed`
- L68 _public enumerator_ `SourceDataOverride_OnAllSourcesProcessed`
- L69 _public enumerator_ `UpdateGameThreadCopies`
- L71 _public enumerator_ `Finished`

#### class `Audio::ISourceListener`  
`class ISourceListener`  
_L83-100_
- L86 _public prototype_ `virtual ~ISourceListener() = default;`
- L89 _public prototype_ `virtual void OnBeginGenerate() = 0;` — Called before a source begins to generate audio.
- L92 _public prototype_ `virtual void OnLoopEnd() = 0;` — Called when a loop point is hit
- L95 _public prototype_ `virtual void OnDone() = 0;` — Called when the source finishes on the audio render thread
- L98 _public prototype_ `virtual void OnEffectTailsDone() = 0;` — Called when the source's effect tails finish on the audio render thread.

#### struct `Audio::FMixerSourceSubmixSend`  
`struct FMixerSourceSubmixSend`  
_L102-127_
- L105 _public member_ `FMixerSubmixWeakPtr Submix;` — The submix ptr
- L108 _public member_ `uint32 SubmixId = TNumericLimits<uint32>::Max();` — Cached submix ID — avoids atomic Pin() calls in the render-thread hot path
- L111 _public member_ `float SendLevel = 0.0f;` — The amount of audio that is to be mixed into this submix
- L114 _public member_ `bool bIsMainSend = false;` — Whather or not this is the primary send (i.e. first in the send chain)
- L117 _public member_ `EMixerSourceSubmixSendStage SubmixSendStage = EMixerSourceSubmixSendStage::PostDistanceAttenuation;` — Whether or not this is a pre-distance attenuation send
- L121 _public member_ `ISoundfieldFactory* SoundfieldFactory = nullptr;` — If this is a soundfield submix, this is a pointer to the submix's Soundfield Factory. If this is nullptr, the submix is not a soundfield submix.
- L123 _public member_ `FSendFilterSettings Filter;`
- L125 _public member_ `FInterpolatedLPF Lpf;`
- L126 _public member_ `FInterpolatedHPF Hpf;`

#### struct `Audio::FInitAudioBusSend`  
`struct FInitAudioBusSend`  
_L130-139_
- desc: Struct holding mappings of bus ids (unique ids) to send level
- L132 _public member_ `uint32 AudioBusId = INDEX_NONE;`
- L133 _public member_ `float SendLevel = 0.0f;`
- L134 _public member_ `int32 BusChannels = 0;`
- L135 _public member_ `FSendFilterSettings Filter;`
- L137 _public member_ `FString AudioBusName;`

#### struct `Audio::FMixerSourceVoiceInitParams`  
`struct FMixerSourceVoiceInitParams`  
_L141-193_
- L143 _public member_ `TSharedPtr<FMixerSourceBuffer, ESPMode::ThreadSafe> MixerSourceBuffer = nullptr;`
- L144 _public member_ `ISourceListener* SourceListener = nullptr;`
- L145 _public member_ `TArray<FMixerSourceSubmixSend> SubmixSends;`
- L146 _public member_ `TArray<FInitAudioBusSend> AudioBusSends[(int32)EBusSendType::Count];`
- L147 _public member_ `uint32 AudioBusId = INDEX_NONE;`
- L148 _public member_ `int32 AudioBusChannels = 0;`
- L150 _public member_ `FString AudioBusName;`
- L152 _public member_ `float SourceBusDuration = 0.0f;`
- L153 _public member_ `uint32 SourceEffectChainId = INDEX_NONE;`
- L154 _public member_ `TArray<FSourceEffectChainEntry> SourceEffectChain;`
- L155 _public member_ `int32 SourceEffectChainMaxSupportedChannels = 0;`
- L156 _public member_ `FMixerSourceVoice* SourceVoice = nullptr;`
- L157 _public member_ `int32 NumInputChannels = 0;`
- L158 _public member_ `int32 NumInputFrames = 0;`
- L159 _public member_ `float EnvelopeFollowerAttackTime = 10.0f;`
- L160 _public member_ `float EnvelopeFollowerReleaseTime = 100.0f;`
- L161 _public member_ `FString DebugName;`
- L162 _public member_ `USpatializationPluginSourceSettingsBase* SpatializationPluginSettings = nullptr;`
- L163 _public member_ `UOcclusionPluginSourceSettingsBase* OcclusionPluginSettings = nullptr;`
- L164 _public member_ `UReverbPluginSourceSettingsBase* ReverbPluginSettings = nullptr;`
- L165 _public member_ `USourceDataOverridePluginSourceSettingsBase* SourceDataOverridePluginSettings = nullptr;`
- L167 _public member_ `FSoundModulationDefaultSettings ModulationSettings;`
- L169 _public member_ `FQuartzQuantizedRequestData QuantizedRequestData;`
- L171 _public member_ `FSharedISourceBufferListenerPtr SourceBufferListener;`
- L173 _public member_ `IAudioLinkFactory::FAudioLinkSourcePushedSharedPtr AudioLink;`
- L175 _public member_ `FName AudioComponentUserID;`
- L176 _public member_ `uint64 AudioComponentID = 0;`
- L177 _public member_ `bool bIs3D = false;`
- L178 _public member_ `bool bPlayEffectChainTails = false;`
- L179 _public member_ `bool bUseHRTFSpatialization = false;`
- L180 _public member_ `bool bIsExternalSend = false;`
- L181 _public member_ `bool bIsDebugMode = false;`
- L182 _public member_ `bool bEnableBusSends = false;`
- L183 _public member_ `bool bEnableBaseSubmix = false;`
- L184 _public member_ `bool bEnableSubmixSends = false;`
- L185 _public member_ `bool bHasAttenuationSubmixSends = false;`
- L186 _public member_ `bool bIsVorbis = false;`
- L187 _public member_ `bool bIsSoundfield = false;`
- L188 _public member_ `bool bIsSeeking = false;`
- L189 _public member_ `bool bShouldSourceBufferListenerZeroBuffer = false;`
- L191 _public member_ `uint32 PlayOrder = INDEX_NONE;`
- L192 _public member_ `uint32 ActiveSoundPlayOrder = INDEX_NONE;`

#### struct `Audio::FSourceManagerInitParams`  
`struct FSourceManagerInitParams`  
_L195-200_
- L198 _public member_ `int32 NumSources = 0;` — Total number of sources to use in the source manager
- L199 _public member_ `int32 NumGeneratorSources = 0;`

#### class `Audio::FMixerSourceManager`  
`class FMixerSourceManager`  
_L202-791_
- L207 _public prototype_ `FMixerSourceManager(FMixerDevice* InMixerDevice);`
- L208 _public prototype_ `~FMixerSourceManager();`
- L210 _public prototype_ `void Init(const FSourceManagerInitParams& InitParams);`
- L211 _public prototype_ `void Update(bool bTimedOut = false);`
- L213 _public prototype_ `bool GetFreeSourceId(int32& OutSourceId);`
- L214 _public prototype_ `int32 GetNumActiveSources() const;`
- L215 _public prototype_ `int32 GetNumActiveAudioBuses() const;`
- L217 _public prototype_ `void ReleaseSourceId(const int32 SourceId);`
- L218 _public prototype_ `void InitSource(const int32 SourceId, const FMixerSourceVoiceInitParams& InitParams);`
- L222 _public prototype_ `void StartAudioBus(FAudioBusKey InAudioBusKey, int32 InNumChannels, bool bInIsAutomatic);` — `UE_DEPRECATED(5.6, "Use the StartAudioBus version that requires an AudioBus name.")` — Creates and starts an audio bus manually.
- L224 _public prototype_ `void StartAudioBus(FAudioBusKey InAudioBusKey, const FString& InAudioBusName, int32 InNumChannels, bool bInIsAutomatic);`
- L227 _public prototype_ `void StopAudioBus(FAudioBusKey InAudioBusKey);` — Stops an audio bus manually
- L230 _public prototype_ `bool IsAudioBusActive(FAudioBusKey InAudioBusKey) const;` — Queries if an audio bus is active. Must be called from the audio thread.
- L234 _public prototype_ `int32 GetAudioBusNumChannels(FAudioBusKey InAudioBusKey) const;` — Returns the number of channels currently set for the audio bus associated with the provided BusId.  Returns 0 if the audio bus is inactive.
- L237 _public prototype_ `void AddPatchOutputForAudioBus(FAudioBusKey InAudioBusKey, const FPatchOutputStrongPtr& InPatchOutputStrongPtr);` — Adds a patch output for an audio bus from the Audio Render Thread
- L240 _public prototype_ `void AddPatchOutputForAudioBus_AudioThread(FAudioBusKey InAudioBusKey, const FPatchOutputStrongPtr& InPatchOutputStrongPtr);` — Adds a patch output for an audio bus from the Audio Thread
- L243 _public prototype_ `void AddPatchInputForAudioBus(FAudioBusKey InAudioBusKey, const FPatchInput& InPatchInput);` — Adds a patch input for an audio bus
- L246 _public prototype_ `void AddPatchInputForAudioBus_AudioThread(FAudioBusKey InAudioBusKey, const FPatchInput& InPatchInput);` — Adds a patch input for an audio bus from the Audio Thread
- L248 _public prototype_ `void Play(const int32 SourceId);`
- L249 _public prototype_ `void Stop(const int32 SourceId);`
- L250 _public prototype_ `void CancelQuantizedSound(const int32 SourceId);`
- L251 _public prototype_ `void StopInternal(const int32 SourceId);`
- L252 _public prototype_ `void StopFade(const int32 SourceId, const int32 NumFrames);`
- L253 _public prototype_ `void Pause(const int32 SourceId);`
- L254 _public prototype_ `void SetPitch(const int32 SourceId, const float Pitch);`
- L255 _public prototype_ `void SetVolume(const int32 SourceId, const float Volume);`
- L256 _public prototype_ `void SetDistanceAttenuation(const int32 SourceId, const float DistanceAttenuation);`
- L257 _public prototype_ `void SetSpatializationParams(const int32 SourceId, const FSpatializationParams& InParams);`
- L258 _public prototype_ `void SetChannelMap(const int32 SourceId, const uint32 NumInputChannels, const Audio::FAlignedFloatBuffer& InChannelMap, const bool bInIs3D, const bool bInIsCenterChannelOnly);`
- L259 _public prototype_ `void SetLPFFrequency(const int32 SourceId, const float Frequency);`
- L260 _public prototype_ `void SetHPFFrequency(const int32 SourceId, const float Frequency);`
- L263 _public prototype_ `void SetModPitch(const int32 SourceId, const float InModPitch);` — Sets base (i.e. carrier) frequency of modulatable parameters
- L264 _public prototype_ `void SetModVolume(const int32 SourceId, const float InModVolume);`
- L265 _public prototype_ `void SetModLPFFrequency(const int32 SourceId, const float InModFrequency);`
- L266 _public prototype_ `void SetModHPFFrequency(const int32 SourceId, const float InModFrequency);`
- L268 _public prototype_ `void SetModulationRouting(const int32 SourceId, FSoundModulationDefaultSettings& ModulationSettings);`
- L270 _public prototype_ `void SetSourceBufferListener(const int32 SourceId, FSharedISourceBufferListenerPtr& InSourceBufferListener, bool InShouldSourceBufferListenerZeroBuffer);`
- L272 _public prototype_ `void SetListenerTransforms(const TArray<FTransform>& ListenerTransforms);`
- L273 _public prototype_ `const TArray<FTransform>* GetListenerTransforms() const;`
- L275 _public prototype_ `int64 GetNumFramesPlayed(const int32 SourceId) const;`
- L276 _public prototype_ `float GetEnvelopeValue(const int32 SourceId) const;`
- L278 _public prototype_ `float GetVolumeModulationValue(const int32 SourceId) const;`
- L281 _public prototype_ `double GetCPUCoreUtilization(const int32 SourceId) const;`
- L283 _public prototype_ `float GetRelativeRenderCost(const int32 SourceId) const;`
- L284 _public prototype_ `bool IsUsingHRTFSpatializer(const int32 SourceId) const;`
- L285 _public prototype_ `bool NeedsSpeakerMap(const int32 SourceId) const;`
- L286 _public prototype_ `void ComputeNextBlockOfSamples();`
- L287 _public prototype_ `void UpdateSourceState();`
- L288 _public prototype_ `void ClearStoppingSounds();`
- L289 _public prototype_ `void MixOutputBuffers(const int32 SourceId, int32 InNumOutputChannels, const float InSendLevel, EMixerSourceSubmixSendStage InSubmixSendStage, uint32 InSubmixId, FAlignedFloatBuffer& ScratchBuffer, FAlignedFloatBuffer& OutWetBuffer);`
- L290 _public prototype_ `void RenderSource(const int32 SourceId);`
- L294 _public prototype_ `void Get2DChannelMap(const int32 SourceId, int32 InNumOutputChannels, Audio::FAlignedFloatBuffer& OutChannelMap);` — Retrieves a channel map for the given source ID for the given output channels can be used even when a source is 3D if the source is doing any kind of bus sending or otherwise needs a channel map
- L300 _public prototype_ `const ISoundfieldAudioPacket* GetEncodedOutput(const int32 SourceId, const FSoundfieldEncodingKey& InKey) const;` — Called by a soundfield submix to get encoded audio. If this source wasn't encoded (possibly because it is paused or finished playing), this returns nullptr. Returned nonnull pointers are only guaranteed to be valid on the audio mixer render thread.
- L302 _public prototype_ `const FQuat GetListenerRotation(const int32 SourceId) const;`
- L304 _public prototype_ `void SetSubmixSendInfo(const int32 SourceId, const FMixerSourceSubmixSend& SubmixSend);`
- L305 _public prototype_ `void ClearSubmixSendInfo(const int32 SourceId, const FMixerSourceSubmixSend& SubmixSend);`
- L307 _public prototype_ `void SetBusSendInfo(const int32 SourceId, EBusSendType InAudioBusSendType, uint32 AudiobusId, float BusSendLevel, const FString& InBusName, const FSendFilterSettings& InFilter = FSendFilterSettings{});`
- L309 _public prototype_ `void UpdateDeviceChannelCount(const int32 InNumOutputChannels);`
- L311 _public prototype_ `void UpdateSourceEffectChain(const uint32 SourceEffectChainId, const TArray<FSourceEffectChainEntry>& SourceEffectChain, const bool bPlayEffectChainTails);`
- L315 _public prototype_ `void PauseSoundForQuantizationCommand(const int32 SourceId);` — Quantized event methods
- L316 _public prototype_ `void SetSubBufferDelayForSound(const int32 SourceId, const int32 FramesToDelay);`
- L317 _public prototype_ `void UnPauseSoundForQuantizationCommand(const int32 SourceId);`
- L320 _public prototype_ `const float* GetPreDistanceAttenuationBuffer(const int32 SourceId) const;` — Buffer getters
- L321 _public prototype_ `const float* GetPostDistanceAttenuationBuffer(const int32 SourceId) const;`
- L322 _public prototype_ `const float* GetPreEffectBuffer(const int32 SourceId) const;`
- L323 _public prototype_ `const float* GetPreviousSourceBusBuffer(const int32 SourceId) const;`
- L324 _public prototype_ `const float* GetPreviousAudioBusBuffer(const int32 AudioBusId) const;`
- L325 _public prototype_ `int32 GetNumChannels(const int32 SourceId) const;`
- L326 _public function_ `int32 GetNumOutputFrames() const`
- L327 _public prototype_ `bool IsSourceBus(const int32 SourceId) const;`
- L328 _public prototype_ `void PumpCommandQueue();`
- L329 _public prototype_ `void UpdatePendingReleaseData(bool bForceWait = false);`
- L330 _public prototype_ `void FlushCommandQueue(bool bPumpCommandQueue = false, bool bSkipWaitForRenderThread = false);`
- L333 _public prototype_ `void AudioMixerThreadMPSCCommand(TFunction<void()>&& InCommand, const char* InDebugString=nullptr);` — Pushes a TFUnction command into an MPSC queue from an arbitrary thread to the audio render thread
- L335 _public function_ `void AddPendingAudioBusConnection(FAudioBusKey AudioBusKey, int32 NumChannels, bool bIsAutomatic, FPatchInput PatchInput, uint32 WaveInstancePlayOrder = INDEX_NONE, const uint64 InstanceID = 0u)`
- L349 _public function_ `void AddPendingAudioBusConnection(FAudioBusKey AudioBusKey, int32 NumChannels, bool bIsAutomatic, FPatchOutputStrongPtr PatchOutputStrongPtr, uint32 WaveInstancePlayOrder = INDEX_NONE, const uint64 InstanceID = 0u)`
- L363 _public function_ `bool UseRenderScheduler() const`
- L368 _public function_ `FAudioRenderScheduler& GetRenderScheduler() const`
- L373 _public function_ `const bool CheckAndResetHardwareCallbackStallFlag()`
- L380 _public prototype_ `int32 AllocateGeneratorSource(ISoundGeneratorRef InGenerator);`
- L381 _public prototype_ `bool IsGeneratorSourceDone(const int32 SourceId);`
- L382 _public prototype_ `void FreeGeneratorSource(const int32 SourceId);`
- L383 _public prototype_ `void PlayGeneratorSource(const int32 SourceId);`
- L384 _public prototype_ `void StopGeneratorSource(const int32 SourceId);`
- L388 _private member_ `uint32 AudioRenderThreadId = INVALID_AUDIO_RENDER_THREAD_ID;`
- L389 _private prototype_ `void ReleaseSource(const int32 SourceId);`
- L390 _private prototype_ `void BuildSourceEffectChain(const int32 SourceId, FSoundEffectSourceInitData& InitData, const TArray<FSourceEffectChainEntry>& SourceEffectChain, TArray<TSoundEffectSourcePtr>& OutSourceEffects);`
- L391 _private prototype_ `void ResetSourceEffectChain(const int32 SourceId);`
- L392 _private prototype_ `void SetSourceDone(const int32 SourceId);`
- L394 _private prototype_ `void GenerateSourceAudio(const bool bGenerateBuses);`
- L395 _private prototype_ `void GenerateSourceAudio(const bool bGenerateBuses, const int32 SourceIdStart, const int32 SourceIdEnd);`
- L397 _private prototype_ `void ComputeSourceBuffer(const bool bGenerateBuses, const int32 SourceId);`
- L398 _private prototype_ `void ComputePostSourceEffectBuffer(const bool bGenerateBuses, const int32 SourceId);`
- L399 _private prototype_ `void ComputeOutputBuffers(const bool bGenerateBuses, const int32 SourceId);`
- L401 _private prototype_ `void ConnectBusPatches();`
- L402 _private prototype_ `void ComputeBuses();`
- L403 _private prototype_ `void UpdateBuses();`
- L404 _private prototype_ `void AddBusPatchDependency(const uint32 WaveInstancePlayOrder, const FAudioRenderStepId FirstStep, const FAudioRenderStepId SecondStep);`
- L405 _private prototype_ `void RemoveBusPatchDependencies(const uint32 WaveInstancePlayOrder);`
- L407 _private prototype_ `float GetFloatCompareTolerance() const;`
- L408 _private prototype_ `float GetCommandQueueFillPercentage() const;`
- L436 _private prototype_ `void AudioMixerThreadCommand(TFunction<void()>&& InFunction, const char* InDebugString = nullptr, bool bInDeferExecution = false);`
- L439 _private member_ `FCriticalSection EffectChainMutationCriticalSection;` — Critical section to ensure mutating effect chains is thread-safe
- L441 _private member_ `FMixerDevice* MixerDevice;`
- L444 _private member_ `FAudioDevice::FAudioSpatializationInterfaceInfo SpatialInterfaceInfo;` — Info about spatialization plugin
- L447 _private member_ `TAudioSourceDataOverridePtr SourceDataOverridePlugin;` — Cached ptr to an optional source data override plugin
- L449 _private member_ `IAudioLinkFactory* AudioLinkFactory = nullptr;`
- L452 _private member_ `TArray<FMixerSourceVoice*> MixerSources;` — Array of pointers to game thread audio source objects
- L461 _private member_ `FCommands CommandBuffers[2];`
- L462 _private member_ `FThreadSafeCounter RenderThreadCommandBufferIndex;`
- L463 _private member_ `bool bShouldResetHardwareCallback = false;`
- L465 _private member_ `FEvent* CommandsProcessedEvent;`
- L466 _private member_ `FCriticalSection CommandBufferIndexCriticalSection;`
- L468 _private member_ `TArray<int32> DebugSoloSources;`
- L470 _private typedef_ `using FAudioMixerMpscCommand = FAudioMixerThreadCommand;`
- L471 _private member_ `TMpscQueue<FAudioMixerMpscCommand> MpscCommandQueue;`
- L658 _private prototype_ `static void ApplyDistanceAttenuation(FSourceInfo& InSourceInfo, int32 NumSamples);`
- L659 _private prototype_ `void ComputePluginAudio(FSourceInfo& InSourceInfo, FMixerSourceSubmixOutputBuffer& InSourceSubmixOutputBuffer, int32 SourceId, int32 NumSamples);`
- L662 _private prototype_ `void DoStallDiagnostics();` — Hang/crash diagnostics.
- L664 _private prototype_ `void LogRenderThreadStall();`
- L665 _private prototype_ `void LogInflightAsyncTasks();`
- L666 _private prototype_ `void LogCallstacks();`
- L667 _private prototype_ `void LogCallstack(uint32 InThreadId);`
- L669 _private prototype_ `TSharedRef<FMixerAudioBus> FindOrAddAudioBus(const FAudioBusKey BusKey, const int32 InNumChannels, const bool bIsAutomatic, bool* bOutAlreadyExisted = nullptr);`
- L672 _private prototype_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L673 _private prototype_ `void OnTraceStopped(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L675 _private prototype_ `void RegisterAudioBusEnvelopeFollowerCVars();`
- L676 _private prototype_ `void UnregisterAudioBusEnvelopeFollowerCVars();`
- L678 _private prototype_ `void OnStartAudioBusEnvelopeFollowerCVarChanged(IConsoleVariable* InStartAudioBusEnvelopeFollowerCVar);`
- L679 _private prototype_ `void OnStopAudioBusEnvelopeFollowerCVarChanged(IConsoleVariable* InStopAudioBusEnvelopeFollowerCVar);`
- L681 _private prototype_ `void StartAudioBusEnvelopeFollowerFromCVar(const uint32 InAudioBusId);`
- L682 _private prototype_ `void StopAudioBusEnvelopeFollowerFromCVar(const uint32 InAudioBusId);`
- L684 _private prototype_ `void AutomaticallyStartAudioBusEnvelopeFollower(const FAudioBusKey& InAudioBusKey, const TSharedPtr<FMixerAudioBus>& InAudioBus);`
- L685 _private prototype_ `void StopAutoAudioBusEnvelopeFollower(const uint32 InAudioBusId, FMixerAudioBus& InAudioBus);`
- L687 _private prototype_ `void TraceSourceToSubmixSendMessage(const FSourceInfo& SourceInfo) const;`
- L688 _private prototype_ `void TraceSourceToBusSendMessage(const uint32 SourceId, const FSourceInfo& SourceInfo) const;`
- L690 _private prototype_ `uint32 ResolvePlayOrder(const FPendingAudioBusConnection& Connection) const;`
- L692 _private member_ `IConsoleVariable* StartAudioBusEnvelopeFollowerCVar = nullptr;`
- L693 _private member_ `IConsoleVariable* StopAudioBusEnvelopeFollowerCVar = nullptr;`
- L695 _private member_ `TSet<uint32> AudioBusesWithAutoEnvelopeFollowers;`
- L697 _private member_ `double BusIsAlivePingTimeSec = 0.0;`
- L698 _private member_ `static constexpr double BusIsAlivePingWaitTimeSec = 1.0;`
- L701 _private member_ `TMultiMap<uint32, uint32> ActiveBusPatchWriters;` — Audio render thread only
- L702 _private member_ `TMultiMap<uint32, uint32> ActiveBusPatchReaders;` — WaveInstancePlayOrder -> BusObjectId (bus->source, reader)
- L703 _private member_ `TMap<uint64, uint32> InstanceIdToPlayOrderMap;` — MixerSourceBuffer InstanceID -> WaveInstancePlayOrder
- L707 _private member_ `TArray<FTransform> ListenerTransforms;` — Array of listener transforms
- L710 _private member_ `TArray<FSourceInfo> SourceInfos;` — Array of source infos.
- L713 _private member_ `TArray<FMixerSourceSubmixOutputBuffer> SourceSubmixOutputBuffers;` — This array is independent of SourceInfos array to optimize for cache coherency
- L716 _private member_ `TMap<FAudioBusKey, TSharedPtr<FMixerAudioBus>> AudioBuses;` — Map of bus object Id's to audio bus data.
- L717 _private member_ `TArray<FAudioBusKey> AudioBusKeys_AudioThread;`
- L720 _private member_ `TArray<TSharedPtr<FMixerSourceBuffer, ESPMode::ThreadSafe>> PendingSourceBuffers;` — Array of task data waiting to finished. Processed on audio render thread.
- L735 _private member_ `} GameThreadInfo;`
- L737 _private member_ `int32 NumActiveSources;`
- L738 _private member_ `int32 NumTotalSources;`
- L739 _private member_ `int32 NumLegacySources;`
- L740 _private member_ `int32 NumGeneratorSources;`
- L741 _private member_ `int32 NumOutputFrames;`
- L742 _private member_ `int32 NumOutputSamples;`
- L756 _private member_ `TArray<FGeneratorSourceState> GeneratorSourceState;`
- L759 _private member_ `FThreadSafeCounter NumCommands;` — Commands queued up to execute
- L761 _private member_ `uint8 bInitialized : 1;`
- L762 _private member_ `uint8 bUsingSpatializationPlugin : 1;`
- L763 _private member_ `uint8 bUsingSourceDataOverridePlugin : 1;`
- L766 _private member_ `FThreadSafeBool bPumpQueue;` — Set to true when the audio source manager should pump the command queue
- L767 _private member_ `std::atomic<uint64> LastPumpCompleteTimeInCycles=0;`
- L768 _private member_ `std::atomic<ESourceManagerRenderThreadPhase> RenderThreadPhase=ESourceManagerRenderThreadPhase::Begin;`
- L769 _private member_ `FRWLock CurrentlyExecutingCmdLock;` — R/W slim lock for the currently executing cmd, so we can safely query it.
- L770 _private member_ `FAudioMixerThreadCommand CurrentlyExecuteingCmd;` — Keep this as a member so we can't always peek the executing cmd.
- L786 _private member_ `TMpscQueue<FPendingAudioBusConnection> PendingAudioBusConnections;`
- L788 _private member_ `TMultiMap<uint64, TPair<FAudioRenderStepId, FAudioRenderStepId>> BusPatchDependencies;`

#### struct `Audio::FMixerSourceManager::FAudioMixerThreadCommand`  
`struct FAudioMixerThreadCommand`  
_L410-434_
- L413 _public prototype_ `FAudioMixerThreadCommand() = default;` — ctor
- L414 _public prototype_ `FAudioMixerThreadCommand(TFunction<void()>&& InFunction, const char* InDebugString, bool bInDeferExecution = false);`
- L417 _public prototype_ `void operator()() const;` — function-call operator
- L420 _public member_ `TFunction<void()> Function;` — data
- L425 _public member_ `bool bDeferExecution = false;` — Defers the execution by a single call to PumpCommandQueue() (used for commands that affect a playing source, and that source gets initialized after the command executes
- L428 _public member_ `const char* DebugString=nullptr;` — Statically defined string from macro AUDIO_MIXER_THREAD_COMMAND_STRING
- L429 _public member_ `mutable uint64_t StartExecuteTimeInCycles=0;` — Set just before Function is called, for diagnostics.
- L432 _public prototype_ `FString GetSafeDebugString() const;`
- L433 _public prototype_ `float GetExecuteTimeInSeconds() const;`

#### struct `Audio::FMixerSourceManager::FCommands`  
`struct FCommands`  
_L455-459_
- desc: A command queue to execute commands from audio thread (or game thread) to audio mixer device thread.
- L457 _public member_ `FThreadSafeCounter NumTimesOvergrown = 0;`
- L458 _public member_ `TArray<FAudioMixerThreadCommand> SourceCommandQueue;`

#### struct `Audio::FMixerSourceManager::FSourceInfo`  
`struct FSourceInfo : public IAudioMixerRenderStep`  
_L473-656_
- inherits: `IAudioMixerRenderStep`
- L475 _public function_ `FSourceInfo() : Resampler(1 )`
- L476 _public prototype_ `~FSourceInfo() = default;`
- L479 _public member_ `FMixerSourceManager* SourceManager;` — The owning source manager
- L482 _public member_ `TSharedPtr<FMixerSourceBuffer, ESPMode::ThreadSafe> MixerSourceBuffer;` — Object which handles source buffer decoding
- L483 _public member_ `ISourceListener* SourceListener;`
- L486 _public member_ `TSharedPtr<Audio::FAlignedFloatBuffer, ESPMode::ThreadSafe> CurrentPCMBuffer;` — Data used for rendering sources
- L489 _public member_ `Audio::FAlignedFloatBuffer SourceBuffer;` — The post-attenuation source buffer, used to send audio to submixes
- L490 _public member_ `Audio::FAlignedFloatBuffer PreEffectBuffer;`
- L491 _public member_ `Audio::FAlignedFloatBuffer PreDistanceAttenuationBuffer;`
- L492 _public member_ `Audio::FAlignedFloatBuffer PostDistanceAttenuationBuffer;`
- L493 _public member_ `Audio::FAlignedFloatBuffer SourceEffectScratchBuffer;`
- L496 _public member_ `int32 SubCallbackDelayLengthInFrames{ 0 };` — Data used for delaying the rendering of source audio for sample-accurate quantization
- L497 _public member_ `int32 CurrentFrameIndex;`
- L498 _public member_ `int64 NumFramesPlayed;`
- L500 _public member_ `TArray<FMixerSourceSubmixSend> SubmixSends;`
- L503 _public member_ `uint32 AudioBusId;` — What audio bus Id this source is sonfiying, if it is a source bus. This is INDEX_NONE for sources which are not source buses.
- L506 _public member_ `int64 SourceBusDurationFrames;` — Number of samples to count for source bus
- L509 _public member_ `TArray<uint32> AudioBusSends[(int32)EBusSendType::Count];` — What buses this source is sending its audio to. Used to remove this source from the bus send list.
- L512 _public member_ `FParam PitchSourceParam;` — Interpolated source params
- L513 _public member_ `float VolumeSourceStart;`
- L514 _public member_ `float VolumeSourceDestination;`
- L515 _public member_ `float VolumeFadeSlope;`
- L516 _public member_ `float VolumeFadeStart;`
- L517 _public member_ `int32 VolumeFadeFramePosition;`
- L518 _public member_ `int32 VolumeFadeNumFrames;`
- L520 _public member_ `float DistanceAttenuationSourceStart;`
- L521 _public member_ `float DistanceAttenuationSourceDestination;`
- L524 _public member_ `float LowPassFreq;` — Legacy filter LFP & HPF frequency set directly (not by modulation) on source
- L525 _public member_ `float HighPassFreq;`
- L528 _public member_ `Audio::FInterpolatedLPF LowPassFilter;` — One-Pole LPFs and HPFs per source
- L529 _public member_ `Audio::FInterpolatedHPF HighPassFilter;`
- L532 _public member_ `uint32 SourceEffectChainId;` — Source effect instances
- L533 _public member_ `TArray<TSoundEffectSourcePtr> SourceEffects;`
- L534 _public member_ `TArray<USoundEffectSourcePreset*> SourceEffectPresets;`
- L535 _public member_ `bool bEffectTailsDone;`
- L536 _public member_ `FSoundEffectSourceInputData SourceEffectInputData;`
- L538 _public member_ `FAudioPluginSourceOutputData AudioPluginOutputData;`
- L541 _public member_ `Audio::FInlineEnvelopeFollower SourceEnvelopeFollower;` — A DSP object which tracks the amplitude envelope of a source.
- L542 _public member_ `float SourceEnvelopeValue;`
- L545 _public member_ `Audio::FModulationDestination VolumeModulation;` — Modulation destinations
- L546 _public member_ `Audio::FModulationDestination PitchModulation;`
- L547 _public member_ `Audio::FModulationDestination LowpassModulation;`
- L548 _public member_ `Audio::FModulationDestination HighpassModulation;`
- L551 _public member_ `float VolumeModulationBase;` — Modulation Base (i.e. Carrier) Values
- L552 _public member_ `float PitchModulationBase;`
- L553 _public member_ `float LowpassModulationBase;`
- L554 _public member_ `float HighpassModulationBase;`
- L556 _public member_ `FSpatializationParams SpatParams;`
- L557 _public member_ `Audio::FAlignedFloatBuffer ScratchChannelMap;`
- L560 _public member_ `FQuartzQuantizedCommandHandle QuantizedCommandHandle;` — Quantization data
- L563 _public member_ `FSharedISourceBufferListenerPtr SourceBufferListener;` — Optional Source buffer listener.
- L566 _public member_ `IAudioLinkFactory::FAudioLinkSourcePushedSharedPtr AudioLink;` — Optional AudioLink.
- L569 _public member_ `uint8 bIs3D:1;` — State management
- L570 _public member_ `uint8 bIsCenterChannelOnly:1;`
- L571 _public member_ `uint8 bIsActive:1;`
- L572 _public member_ `uint8 bIsPlaying:1;`
- L573 _public member_ `uint8 bIsPaused:1;`
- L574 _public member_ `uint8 bIsPausedForQuantization:1;`
- L575 _public member_ `uint8 bDelayLineSet:1;`
- L576 _public member_ `uint8 bIsStopping:1;`
- L577 _public member_ `uint8 bHasStarted:1;`
- L578 _public member_ `uint8 bIsBusy:1;`
- L579 _public member_ `uint8 bUseHRTFSpatializer:1;`
- L580 _public member_ `uint8 bIsExternalSend:1;`
- L581 _public member_ `uint8 bUseOcclusionPlugin:1;`
- L582 _public member_ `uint8 bUseReverbPlugin:1;`
- L583 _public member_ `uint8 bIsDone:1;`
- L584 _public member_ `uint8 bIsLastBuffer:1;`
- L585 _public member_ `uint8 bEnableBusSends : 1;`
- L586 _public member_ `uint8 bEnableBaseSubmix : 1;`
- L587 _public member_ `uint8 bEnableSubmixSends : 1;`
- L588 _public member_ `uint8 bHasAttenuationSubmixSends : 1;`
- L589 _public member_ `uint8 bIsVorbis:1;`
- L590 _public member_ `uint8 bIsSoundfield:1;`
- L591 _public member_ `uint8 bHasPreDistanceAttenuationSend:1;`
- L592 _public member_ `uint8 bModFiltersUpdated : 1;`
- L593 _public member_ `uint8 bShouldSourceBufferListenerZeroBuffer : 1;`
- L594 _public member_ `uint8 bResampling : 1;`
- L597 _public member_ `int32 NumInputChannels;` — Source format info
- L598 _public member_ `int32 NumPostEffectChannels;`
- L599 _public member_ `int32 NumInputFrames;`
- L601 _public member_ `uint32 PlayOrder;`
- L602 _public member_ `uint32 ActiveSoundPlayOrder;`
- L605 _public member_ `uint64 AudioComponentID;` — ID for associated Audio Component if there is one, 0 otherwise
- L608 _public member_ `FRuntimeResampler Resampler;` — Resampler instance
- L610 _public function_ `FORCEINLINE void ResetModulators(const Audio::FDeviceId InDeviceId)`
- L624 _public prototype_ `bool IsRenderingToSubmixes() const;` — Helper function for determining if OutputToBusOnly is enabled
- L627 _public member_ `uint8 bIsDebugMode : 1;`
- L628 _public member_ `FString DebugName;`
- L630 _public function_ `FString GetDebugName() const`
- L641 _public function_ `int32 GetCurrentAudioChunkNumFrames() const` — return the number of sample frames in the current input PCM buffer (if any)
- L654 _public prototype_ `virtual void DoRenderStep() override;`
- L655 _public prototype_ `virtual const TCHAR* GetRenderStepName() override;`

#### struct `Audio::FMixerSourceManager::FGameThreadInfo`  
`struct FGameThreadInfo`  
_L723-735_
- desc: General information about sources in source manager accessible from game thread
- L725 _public member_ `TArray<int32> FreeSourceIndices;`
- L726 _public member_ `TArray<bool> bIsBusy;`
- L727 _public member_ `TArray<bool> bNeedsSpeakerMap;`
- L728 _public member_ `TArray<bool> bIsDebugMode;`
- L729 _public member_ `TArray<bool> bIsUsingHRTFSpatializer;`
- L731 _public member_ `TArray<double> CPUCoreUtilization;`
- L733 _public member_ `TArray<float> RelativeRenderCost;`
- L734 _public member_ `TArray<float> ModulationVolume;`

#### struct `Audio::FMixerSourceManager::FGeneratorSourceState`  
`struct FGeneratorSourceState`  
_L744-754_
- L747 _public member_ `ISoundGeneratorPtr Generator;` — Generator used for rendering, owned by render thread.
- L750 _public member_ `std::atomic<uint8> bSourceBusy = false;` — Set on game thread, cleared from render thread when rendering is complete
- L753 _public member_ `uint8 bAllocated:1 = false;` — Is this voice allocated on the game thread?

#### struct `Audio::FMixerSourceManager::FPendingAudioBusConnection`  
`struct FPendingAudioBusConnection`  
_L772-784_
- L774 _public typedef_ `using FPatchVariant = TVariant<FPatchInput, FPatchOutputStrongPtr>;`
- L775 _public member_ `FPatchVariant PatchVariant;`
- L776 _public member_ `FAudioBusKey AudioBusKey;`
- L777 _public member_ `int32 NumChannels = 0;`
- L778 _public member_ `bool bIsAutomatic = false;`
- L779 _public member_ `uint32 WaveInstancePlayOrder = INDEX_NONE;`
- L782 _public member_ `uint64 InstanceID = 0u;` — MixerSourceBuffer instance ID, used for PlayOrder resolution in trace profiling

#### Free symbols / members of external scopes

- L34 _macro_ `#define WITH_AUDIO_MIXER_THREAD_COMMAND_DEBUG (1)`
- L38 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Source Manager Update"), STAT_AudioMixerSourceManagerUpdate, STATGROUP_AudioMi` — Tracks the time it takes to up the source manager (computes source buffers, source effects, sample rate conversion)
- L41 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Source Buffers"), STAT_AudioMixerSourceBuffers, STATGROUP_AudioMixer, AU` — The time it takes to compute the source buffers (handle decoding tasks, resampling)
- L44 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Source Effect Buffers"), STAT_AudioMixerSourceEffectBuffers, STATGROUP_AudioMi` — The time it takes to process the source buffers through their source effects
- L47 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Source Output Buffers"), STAT_AudioMixerSourceOutputBuffers, STATGROUP_AudioMi` — The time it takes to apply channel maps and get final pre-submix source buffers
- L50 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("HRTF"), STAT_AudioMixerHRTF, STATGROUP_AudioMixer, AUDIOMIXER_A` — The time it takes to process the HRTF effect.
- L74 _namespace_ `namespace Audio`
- L387 _macro_ `#define INVALID_AUDIO_RENDER_THREAD_ID static_cast<uint32>(-1)`

### `Source/Runtime/AudioMixer/Private/AudioMixerSourceOutputBuffer.h` (Private)


#### struct `Audio::FMixerSourceSubmixOutputBufferSettings`  
`struct FMixerSourceSubmixOutputBufferSettings`  
_L20-28_
- L22 _public member_ `uint32 NumSourceChannels;`
- L23 _public member_ `uint32 NumOutputChannels;`
- L24 _public member_ `TArray<FMixerSubmixPtr> SoundfieldSubmixSends;`
- L25 _public member_ `bool bIs3D;`
- L26 _public member_ `bool bIsVorbis;`
- L27 _public member_ `bool bIsSoundfield;`

#### class `Audio::FMixerSourceSubmixOutputBuffer`  
`class FMixerSourceSubmixOutputBuffer`  
_L33-212_
- desc: Used in audio mixer source manager to convert source audio to channel output and mix into submixes
- L36 _public prototype_ `FMixerSourceSubmixOutputBuffer(FMixerDevice* InMixerDevice, uint32 InNumSourceChannels, uint32 InNumOutputChannels, uint32 InNumFrames);`
- L38 _public prototype_ `~FMixerSourceSubmixOutputBuffer();`
- L41 _public prototype_ `void Reset(const FMixerSourceSubmixOutputBufferSettings& InResetSettings);` — Resets the source submix output to prepare for new source data
- L44 _public prototype_ `void SetNumOutputChannels(uint32 InNumOutputChannels);` — Sets the number of output channels
- L47 _public function_ `uint32 GetNumSourceChannels() const` — Returns the number of source channels of this source
- L50 _public prototype_ `bool SetChannelMap(const FAlignedFloatBuffer& InChannelMap, bool bInIsCenterChannelOnly);` — Sets the channel map
- L53 _public prototype_ `void SetPreAttenuationSourceBuffer(FAlignedFloatBuffer* InPreAttenuationBuffer);` — Sets the pre and post attenuation source buffers. This is the source buffer data derived from source manager source processing.
- L54 _public prototype_ `void SetPostAttenuationSourceBuffer(FAlignedFloatBuffer* InPostAttenuationBuffer);`
- L55 _public prototype_ `void CopyReverbPluginOutputData(FAlignedFloatBuffer& InAudioBuffer);`
- L56 _public prototype_ `const float* GetReverbPluginOutputData() const;`
- L59 _public prototype_ `const ISoundfieldAudioPacket* GetSoundfieldPacket(const FSoundfieldEncodingKey& InKey) const;` — Retrieves the current sound field packet for the given key
- L60 _public prototype_ `ISoundfieldAudioPacket* GetSoundFieldPacket(const FSoundfieldEncodingKey& InKey);`
- L63 _public prototype_ `void ComputeOutput(const FSpatializationParams& InSpatParams);` — Computes the output buffer given the spat params. This buffer can then be mixed to submixes
- L66 _public prototype_ `void MixOutput(float SendLevel, EMixerSourceSubmixSendStage InSubmixSendStage, FAlignedFloatBuffer& OutMixedBuffer) const;` — Called by submixes to mix this output buffer to their buffer
- L67 _public prototype_ `void MixOutput(float InSendLevel, EMixerSourceSubmixSendStage InSubmixSendStage, const FSendFilterSettings& InFilter, FInterpolatedLPF& InLpf, FInterpolatedHPF& InHpf, FAlignedFloatBuffer& ScratchBuffer, FAlignedFloatBuffer& OutMixedBuffer);`
- L71 _public prototype_ `FQuat GetListenerRotation() const;` — Return the listener rotation TODO: consolidate the code that is using this to be private to this class.
- L148 _private prototype_ `void ComputeOutput3D(FAlignedFloatBuffer& InSource, FAlignedFloatBuffer& InOutput);`
- L149 _private prototype_ `void ComputeOutput3D();`
- L150 _private prototype_ `void ComputeOutput2D(FAlignedFloatBuffer& InSource, FAlignedFloatBuffer& InOutput);`
- L151 _private prototype_ `void ComputeOutput2D();`
- L153 _private prototype_ `void EncodeSoundfield(FSoundfieldData& InSoundfieldData, Audio::FAlignedFloatBuffer& InSourceBuffer);`
- L154 _private prototype_ `void EncodeToSoundfieldFormats(const FSpatializationParams& InSpatParams);`
- L159 _private member_ `FAlignedFloatBuffer ReverbPluginOutputBuffer;` — Buffer for reverb plugins to write into
- L162 _private member_ `FAlignedFloatBuffer* PreAttenuationSourceBuffer;` — The source buffer created before distance attenuation is applied
- L165 _private member_ `FAlignedFloatBuffer* PostAttenuationSourceBuffer;` — The source buffer created after distance attenuation is applied
- L168 _private member_ `FSourceChannelMap SourceChannelMap;` — Data used to map the source channel data to the output channel configuration
- L171 _private member_ `FAlignedFloatBuffer PreAttenuationOutputBuffer;` — The result of the source output with source data derived pre distance attenuation
- L174 _private member_ `FAlignedFloatBuffer PostAttenuationOutputBuffer;` — The result of the source output with source data derived post distance attenuation
- L177 _private member_ `uint32 NumSourceChannels;` — The number of source channels (sound input)
- L180 _private member_ `const uint32 NumFrames;` — The number of interleaved frames in the source
- L183 _private member_ `uint32 NumOutputChannels;` — The number of device output channels
- L186 _private member_ `FMixerDevice* MixerDevice;` — The owning mixer device
- L189 _private member_ `bool bIsInitialDownmix;` — Whether this is the initial downmix
- L192 _private member_ `bool bIs3D;` — If this is a 3D sound source
- L195 _private member_ `bool bIsVorbis;` — Whether this source is vorbis encoded (used for 2D speakermapping)
- L198 _private member_ `FSoundfieldSpeakerPositionalData SoundfieldPositionalData;` — Cached parameters for encoding to a soundfield format
- L201 _private member_ `FQuat SoundSourceRotation;` — The current sound source rotation
- L204 _private member_ `TMap<FSoundfieldEncodingKey, FSoundfieldData> EncodedSoundfieldDownmixes;` — Map of sound field encoding to encoding data
- L207 _private member_ `TArray<Audio::FChannelPositionInfo> InputChannelPositions;` — Channel positions of the sound field
- L210 _private member_ `TUniquePtr<ISoundfieldDecoderStream> SoundfieldDecoder;` — If this source is an ambisonics source, we use this to down mix the source to output channel mix.

#### struct `Audio::FMixerSourceSubmixOutputBuffer::FSourceChannelMap`  
`struct FSourceChannelMap`  
_L76-126_
- desc: Private struct used for channel mapping
- L78 _public member_ `alignas(16) float ChannelStartGains[AUDIO_MIXER_MAX_OUTPUT_CHANNELS * AUDIO_MIXER_MAX_OUTPUT_CHANNELS];`
- L79 _public member_ `alignas(16) float ChannelDestinationGains[AUDIO_MIXER_MAX_OUTPUT_CHANNELS * AUDIO_MIXER_MAX_OUTPUT_CHANNELS];`
- L83 _public member_ `int32 CopySize = 0;` — This is the number of bytes the gain array is using: (Number of input channels * number of output channels) * sizeof float.
- L84 _public member_ `bool bIsInit = false;`
- L86 _public function_ `FSourceChannelMap(int32 InNumInChannels, int32 InNumOutChannels) : CopySize(InNumInChannels* InNumOutChannels * sizeof(float))`
- L94 _public function_ `FORCEINLINE void Reset(int32 InNumInChannels, int32 InNumOutChannels)`
- L105 _public function_ `FORCEINLINE void CopyDestinationToStart()`
- L110 _public function_ `FORCEINLINE void SetChannelMap(const float* RESTRICT InChannelGains)`
- L121 _private function_ `FSourceChannelMap() : CopySize(0) , bIsInit(false)`

#### struct `Audio::FMixerSourceSubmixOutputBuffer::FSoundfieldData`  
`struct FSoundfieldData`  
_L128-144_
- L131 _public member_ `TUniquePtr<ISoundfieldEncoderStream> SoundfieldEncoder;` — If the sound source is not a soundfield source and we're sending to a soundfield submix, it gets encoded
- L134 _public member_ `TUniquePtr<ISoundfieldTranscodeStream> SoundfieldTranscoder;` — If the sound source is soundfield, and we're sending to a soundfield submix, it gets transcoded
- L137 _public member_ `TUniquePtr<ISoundfieldEncodingSettingsProxy> EncoderSettings;` — The optional soundfield encoder settings
- L140 _public member_ `TUniquePtr<ISoundfieldAudioPacket> EncodedPacket;` — The encoded soundfield packet
- L143 _public member_ `bool bIsUnrealAmbisonicsSubmix;` — If this is a unreal ambisonics soundfield buffer, we hand it the submixed buffer directly.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Private/AudioMixerSourceVoice.h` (Private)


#### class `Audio::FMixerSourceVoice`  
`class FMixerSourceVoice`  
_L19-176_
- L22 _public prototype_ `FMixerSourceVoice();`
- L23 _public prototype_ `~FMixerSourceVoice();`
- L26 _public prototype_ `void Reset(FMixerDevice* InMixerDevice);` — Resets the source voice state
- L29 _public prototype_ `bool Init(const FMixerSourceVoiceInitParams& InFormat);` — Initializes the mixer source voice
- L32 _public prototype_ `void Release();` — Releases the source voice back to the source buffer pool
- L35 _public prototype_ `void SetPitch(const float InPitch);` — Sets the source voice pitch value.
- L38 _public prototype_ `void SetVolume(const float InVolume);` — Sets the source voice volume value.
- L41 _public prototype_ `void SetDistanceAttenuation(const float InDistanceAttenuation);` — Sets the source voice distance attenuation.
- L44 _public prototype_ `void SetLPFFrequency(const float InFrequency);` — Sets the source voice's LPF filter frequency.
- L47 _public prototype_ `void SetHPFFrequency(const float InFrequency);` — Sets the source voice's HPF filter frequency.
- L50 _public prototype_ `void SetModPitch(const float InPitch);` — Sets the source voice modulation base pitch value.
- L53 _public prototype_ `void SetModVolume(const float InVolume);` — Sets the source voice's volume modulation base frequency.
- L56 _public prototype_ `void SetModLPFFrequency(const float InFrequency);` — Sets the source voice's LPF filter modulation base frequency.
- L59 _public prototype_ `void SetModHPFFrequency(const float InFrequency);` — Sets the source voice's HPF filter modulation base frequency.
- L61 _public prototype_ `void SetModulationRouting(FSoundModulationDefaultRoutingSettings& RoutingSettings);`
- L64 _public prototype_ `void SetSourceBufferListener(FSharedISourceBufferListenerPtr& InSourceBufferListener, bool InShouldSourceBufferListenerZeroBuffer);` — Set the source voice's SourceBufferListener and associated boolean.
- L67 _public prototype_ `void SetChannelMap(const uint32 NumInputChannels, const Audio::FAlignedFloatBuffer& InChannelMap, const bool bInIs3D, const bool bInIsCenterChannelOnly);` — Sets the source voice's channel map (2d or 3d).
- L70 _public prototype_ `void SetSpatializationParams(const FSpatializationParams& InParams);` — Sets params used by HRTF spatializer
- L73 _public prototype_ `void Play();` — Starts the source voice generating audio output into it's submix.
- L76 _public prototype_ `void Pause();` — Pauses the source voice (i.e. stops generating output but keeps its state as "active and playing". Can be restarted.)
- L79 _public prototype_ `void Stop();` — Immediately stops the source voice (no longer playing or active, can't be restarted.)
- L82 _public prototype_ `void StopFade(int32 NumFrames);` — Does a faded stop (to avoid discontinuity)
- L85 _public prototype_ `int32 GetSourceId() const;` — Returns the source's Id
- L88 _public prototype_ `float GetDistanceAttenuation() const;` — Returns the source's distance attenuation
- L91 _public prototype_ `float GetDistance() const;` — Returns the source's distance from the closest listener
- L94 _public prototype_ `bool IsPlaying() const;` — Queries if the voice is playing
- L97 _public prototype_ `bool IsPaused() const;` — Queries if the voice is paused
- L100 _public prototype_ `bool IsActive() const;` — Queries if the source voice is active.
- L103 _public function_ `bool IsStopFadedOut() const` — Queries if the source has finished its fade out.
- L106 _public prototype_ `bool NeedsSpeakerMap() const;` — Whether or not the device changed and needs another speaker map sent
- L111 _public prototype_ `bool IsUsingHRTFSpatializer(bool bDefaultValue) const;` — Whether or not the voice is currently using HRTF spatialization. @param bDefaultValue - This value will be returned if voice does not have a valid source id.
- L114 _public prototype_ `int64 GetNumFramesPlayed() const;` — Retrieves the total number of samples played.
- L117 _public prototype_ `float GetEnvelopeValue() const;` — Retrieves the envelope value of the source.
- L120 _public prototype_ `float GetVolumeModulationValue() const;` — Retrieves final mixed Modulation value of the source.
- L123 _public prototype_ `double GetCPUCoreUtilization() const;`
- L129 _public prototype_ `float GetRelativeRenderCost() const;` — Retrieves the current "render cost" of the mixer source voice. Used for debug display and for limiting voice count. 1.0 is equivalent to a single decoding sound source. Useful as a metric more human-centric than CPU utilization.
- L132 _public prototype_ `void SetSubmixSendInfo(FMixerSubmixWeakPtr Submix, const float SendLevel, const EMixerSourceSubmixSendStage SendStage = EMixerSourceSubmixSendStage::PostDistanceAttenuation, const FSendFilterSettings& InFilter = FSendFilterSettings{});` — Sets the send level and optional filter for a single submix send
- L135 _public prototype_ `void ClearSubmixSendInfo(FMixerSubmixWeakPtr Submix);` — Clears the submix send to the given submix
- L138 _public prototype_ `void SetOutputToBusOnly(bool bInOutputToBusOnly);` — Sets whether or not we are enabling sending audio to submixes (we could be sending audio to source buses though).
- L141 _public prototype_ `void SetEnablement(bool bInEnableBusSendRouting, bool bInEnableMainSubmixOutput, bool bInEnableSubmixSendRouting);` — Updates internal settings on which output types are enabled
- L144 _public prototype_ `void SetAudioBusSendInfo(EBusSendType InBusSendType, uint32 AudioBusId, float BusSendLevel, const FString& InBusName, const FSendFilterSettings& InFilter = FSendFilterSettings{});` — Set the source bus send levels
- L150 _private member_ `FMixerSourceManager* SourceManager;`
- L151 _private member_ `TMap<uint32, FMixerSourceSubmixSend> SubmixSends;`
- L152 _private member_ `FMixerDevice* MixerDevice;`
- L153 _private member_ `TArray<float> DeviceChannelMap;`
- L154 _private member_ `FThreadSafeBool bStopFadedOut;`
- L155 _private member_ `float Pitch;`
- L156 _private member_ `float Volume;`
- L157 _private member_ `float DistanceAttenuation;`
- L158 _private member_ `float Distance;`
- L159 _private member_ `float LPFFrequency;`
- L160 _private member_ `float HPFFrequency;`
- L161 _private member_ `float PitchModBase;`
- L162 _private member_ `float VolumeModBase;`
- L163 _private member_ `float LPFFrequencyModBase;`
- L164 _private member_ `float HPFFrequencyModBase;`
- L165 _private member_ `int32 SourceId;`
- L166 _private member_ `uint16 bIsPlaying : 1;`
- L167 _private member_ `uint16 bIsPaused : 1;`
- L168 _private member_ `uint16 bIsActive : 1;`
- L169 _private member_ `uint16 bIsBus : 1;`
- L170 _private member_ `uint16 bEnableBusSends : 1;`
- L171 _private member_ `uint16 bEnableBaseSubmix : 1;`
- L172 _private member_ `uint16 bEnableSubmixSends : 1;`
- L173 _private member_ `uint16 bHasAttenuationSubmixSends : 1;`
- L175 _private prototype_ `bool IsRenderingToSubmixes() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Private/AudioRenderScheduler.h` (Private)


#### class `Audio::FAudioRenderStepId`  
`class FAudioRenderStepId`  
_L19-62_
- desc: An identifier that uniquely identifies a given render step to the scheduler.
- L22 _public function_ `FAudioRenderStepId() : Value(INDEX_NONE)`
- L27 _public prototype_ `static FAudioRenderStepId FromWaveInstancePlayOrder(const uint32 PlayOrder);`
- L28 _public prototype_ `static FAudioRenderStepId FromAudioBusKey(const FAudioBusKey BusKey);`
- L30 _public function_ `uint64 GetRawValue() const`
- L50 _public function_ `bool IsValid() const`
- L56 _protected function_ `FAudioRenderStepId(uint64 InValue) : Value(InValue)`
- L61 _protected member_ `uint64 Value;`

#### class `Audio::FAudioRenderScheduler`  
`class FAudioRenderScheduler`  
_L74-156_
- L79 _public prototype_ `FAudioRenderScheduler(FMixerDevice* InMixerDevice);`
- L82 _public prototype_ `void AddStep(const FAudioRenderStepId Id, IAudioMixerRenderStep* Step);` — Add/remove a render step.
- L83 _public prototype_ `void RemoveStep(const FAudioRenderStepId Id);`
- L88 _public prototype_ `void AddDependency(const FAudioRenderStepId FirstStep, const FAudioRenderStepId SecondStep);` — Declare that one step is dependent on another. It's possible to add a dependency without having previously called AddStep; in this case the dependency will still be respected with an empty placeholder step.
- L91 _public prototype_ `void RemoveDependency(const FAudioRenderStepId FirstStep, const FAudioRenderStepId SecondStep);` — All dependencies declared with AddDependency() must be removed by a corresponding call to RemoveDependency().
- L94 _public prototype_ `void RenderBlock(const bool bSingleThreaded);` — Execute all steps and block until they're done.
- L98 _public prototype_ `void DumpSteps();` — Dump the state of the scheduler after next run
- L103 _private typedef_ `using FInternalIndex = int16;` — Internally the step id's are mapped to smaller internal indices to reduce memory footprint.
- L105 _private prototype_ `void ScheduleAll(const bool bSingleThreaded);`
- L107 _private prototype_ `FInternalIndex GetInternalIndex(const FAudioRenderStepId Id);`
- L108 _private prototype_ `void RemoveReference(FAudioRenderScheduler::FInternalIndex Index);`
- L110 _private prototype_ `void BreakCycle(const int FirstPendingStepIndex);`
- L111 _private prototype_ `void CheckBrokenLinks();`
- L112 _private prototype_ `void BreakLink(FInternalIndex FirstStep, FInternalIndex SecondStep);`
- L115 _private prototype_ `bool FindIndirectLink(const FInternalIndex FirstStep, const FInternalIndex SecondStep);` — Helpers to verify that a link is still part of a cycle
- L116 _private prototype_ `bool FindIndirectLinkSkipping(const FInternalIndex FirstStep, const FInternalIndex SecondStep, TArray<FInternalIndex>& StepsToSkip);`
- L119 _private prototype_ `void DumpStepsInternal();`
- L120 _private prototype_ `void DumpOnError();`
- L122 _private member_ `bool bShouldDumpSteps = false;`
- L123 _private member_ `bool bDidDumpOnError = false;`
- L141 _private member_ `FMixerDevice* MixerDevice;` — Only used to check the current thread; may be null.
- L143 _private member_ `TMap<FAudioRenderStepId, FInternalIndex> IndexMap;`
- L144 _private member_ `TArray<FStepEntry> Steps;`
- L145 _private member_ `FInternalIndex FirstFreeIndex = INDEX_NONE;`
- L148 _private member_ `TArray<FInternalIndex> ActiveSteps;` — Array of all used step indices. Ends up sorted at the end of RenderBlock().
- L151 _private member_ `bool bDirty = true;` — Have any changes happened since the previous call to RenderBlock()?
- L155 _private member_ `TArray<TPair<FInternalIndex, FInternalIndex>> BrokenLinks;` — Links that have been broken to eliminate cycles. These are retained between blocks to improve stability of step ordering.

#### struct `Audio::FAudioRenderScheduler::FStepEntry`  
`struct FStepEntry`  
_L126-138_
- L128 _public member_ `FAudioRenderStepId StepId;`
- L129 _public member_ `IAudioMixerRenderStep* StepInterface = nullptr;`
- L130 _public member_ `TArray<FInternalIndex, TInlineAllocator<4>> Prerequisites;`
- L131 _public member_ `int32 ReferenceCount = 0;`
- L132 _public member_ `bool bLaunched = false;`
- L133 _public member_ `bool bCheckBrokenLinks = false;`
- L134 _public member_ `UE::Tasks::FTask TaskHandle;`
- L137 _public member_ `FInternalIndex NextFreeIndex = INDEX_NONE;` — Unused step entries are added to a free list.

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioRenderScheduler, Display, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioRenderScheduler, Display, All);`
- L11 _namespace_ `namespace Audio`
- L35 _function_ `friend uint32 GetTypeHash(FAudioRenderStepId Id)` (scope `Audio`)
- L40 _function_ `friend bool operator==(const FAudioRenderStepId InLHS, const FAudioRenderStepId InRHS)` (scope `Audio`)
- L45 _function_ `friend bool operator!=(const FAudioRenderStepId InLHS, const FAudioRenderStepId InRHS)` (scope `Audio`)

### `Source/Runtime/AudioMixer/Private/IAudioMixerRenderStep.h` (Private)


#### struct `Audio::IAudioMixerRenderStep`  
`struct IAudioMixerRenderStep`  
_L12-21_
- desc: Interface representing an item of audio rendering work that can be scheduled as part of an AudioMixerDevice's rendering pass.
- L14 _public prototype_ `virtual ~IAudioMixerRenderStep() = default;`
- L17 _public prototype_ `virtual void DoRenderStep() = 0;` — Do the work associated with this render step.
- L20 _public prototype_ `virtual const TCHAR* GetRenderStepName() = 0;` — Get a name for this render step to display for debugging purposes.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Private/SoundFileIO/SoundFile.h` (Private)


#### struct `Audio::FSoundFileDescription`  
`struct FSoundFileDescription`  
_L19-38_
- desc: Specifies a sound file description. Note that libsndfile reads some of these fields (noteably FormatFlags and bIsSeekable) at file open time so we zero them out at construction time to avoid unexpected/intermintent issues.
- L22 _public member_ `int64 NumFrames = 0;` — The number of frames (interleaved samples) in the sound file.
- L25 _public member_ `int32 SampleRate = 0;` — The sample rate of the sound file.
- L28 _public member_ `int32 NumChannels = 0;` — The number of channels of the sound file.
- L31 _public member_ `int32 FormatFlags = 0;` — The format flags of the sound file.
- L34 _public member_ `int32 NumSections = 0;` — The number of sections of the sound file.
- L37 _public member_ `int32 bIsSeekable = 0;` — Whether or not the sound file is seekable.

#### struct `Audio::FSoundFileConvertFormat`  
`struct FSoundFileConvertFormat`  
_L40-65_
- L43 _public member_ `int32 Format;` — Desired convert format.
- L46 _public member_ `uint32 SampleRate;` — Desired convert sample rate.
- L49 _public member_ `double EncodingQuality;` — For compression-type target formats that used an encoding quality (0.0 = low, 1.0 = high).
- L52 _public member_ `bool bPerformPeakNormalization;` — Whether or not to peak-normalize the audio file during import.
- L55 _public function_ `static FSoundFileConvertFormat CreateDefault()` — Creates audio engine's default source format

#### struct `Audio::FSoundFileChunkInfo`  
`struct FSoundFileChunkInfo`  
_L71-84_
- L74 _public member_ `ANSICHAR ChunkId[64];` — Chunk Id
- L77 _public member_ `uint32 ChunkIdSize = 0;` — Size of the Chunk Id
- L80 _public member_ `uint32 DataLength = 0;` — Size of the data in this chunk
- L83 _public member_ `void* DataPtr = nullptr;` — Pointer to chunk data

#### struct `Audio::FSoundFileCuePoint`  
`struct FSoundFileCuePoint`  
_L89-98_
- desc: FSoundFileCuePoint which maps to libsndfile SF_CUE_POINT struct.
- L91 _public member_ `int32 CueId = 0;`
- L92 _public member_ `uint32 Position = 0;`
- L93 _public member_ `int32 ChunkId = 0;`
- L94 _public member_ `int32 ChunkStart = 0;`
- L95 _public member_ `int32 BlockStart = 0;`
- L96 _public member_ `uint32 SampleOffset = 0;`
- L97 _public member_ `char Name[256];`

#### struct `Audio::FSoundFileCues`  
`struct FSoundFileCues`  
_L103-107_
- desc: FSoundFileCues which maps to libsndfile SF_CUES struct.
- L105 _public member_ `uint32 CueCount = 0;`
- L106 _public member_ `FSoundFileCuePoint CuePoints[100];`

#### struct `Audio::FRiffCueChunk`  
`struct FRiffCueChunk`  
_L114-119_
- desc: ChunkID: 'cue ' A cue chunk specifies one or more sample offsets which are often used to mark noteworthy sections of audio. For example, the beginning and end of a verse in a song may have cue points to make them easier to find. The cue chunk is optional and if included, a single cue chunk should specify all cue points for the "WAVE" chunk. No more than one cue chunk is allowed in a "WAVE" chunk.
- L116 _public member_ `uint32 ChunkID;` — 'cue '
- L117 _public member_ `uint32 ChunkDataSize;` — Depends on the number of cue points
- L118 _public member_ `uint32 NumCuePoints;` — Number of cue points in the list

#### struct `Audio::FRiffCuePointChunk`  
`struct FRiffCuePointChunk`  
_L121-129_
- L123 _public member_ `uint32 CueID;` — Unique ID value for the cue point
- L124 _public member_ `uint32 Position;` — Play order position
- L125 _public member_ `uint32 DataChunkID;` — RIFF ID of corresponding data chunk
- L126 _public member_ `uint32 ChunkStart;` — Byte offset of data chunk
- L127 _public member_ `uint32 BlockStart;` — Byte offset of sample of first channel
- L128 _public member_ `uint32 SampleOffset;` — Byte offset to sample byte of first channel

#### struct `Audio::FRiffSampleChunk`  
`struct FRiffSampleChunk`  
_L131-144_
- L133 _public member_ `uint32 ChunkID;` — 'smpl'
- L134 _public member_ `uint32 ChunkDataSize;` — Depends on the number of sample loops
- L135 _public member_ `uint32 ManufacturerCode;` — The MIDI Manufacturers Association manufacturer code
- L136 _public member_ `uint32 Product;` — The Product / Model ID of the target device, specific to the manufacturer
- L137 _public member_ `uint32 SamplePeriod;` — The period of one sample in nanoseconds.
- L138 _public member_ `uint32 MidiUnityNote;` — The MIDI note that will play when this sample is played at its current pitch
- L139 _public member_ `uint32 MidiPitchFraction;` — The fraction of a semitone up from the specified note.
- L140 _public member_ `uint32 SmpteFormat;` — The SMPTE format. Possible values: 0, 24, 25, 29, 30
- L141 _public member_ `uint32 SmpteOffset;` — Specifies a time offset for the sample, if the sample should start at a later time and not immediately.
- L142 _public member_ `uint32 NumSampleLoops;` — Number of sample loops contained in this chunks data
- L143 _public member_ `uint32 NumSampleDataBytes;` — Number of bytes of optional sampler specific data that follows the sample loops. zero if there is no such data.

#### struct `Audio::FRiffSampleLoopChunk`  
`struct FRiffSampleLoopChunk`  
_L146-154_
- L148 _public member_ `uint32 LoopID;` — A unique ID of the loop, which could be a cue point
- L149 _public member_ `uint32 LoopType;` — The loop type. 0: Forward Looping, 1: Ping-Pong, 2: Backward, 3-31: future standard types. >=32: manufacturer specific types
- L150 _public member_ `uint32 StartFrame;` — Start point of the loop in samples
- L151 _public member_ `uint32 EndFrame;` — End point of the loop in samples. The end sample is also played.
- L152 _public member_ `uint32 Fraction;` — The resolution at which this loop should be fine tuned.
- L153 _public member_ `uint32 NumPlayTimes;` — The number of times to play the loop. A value of zero means inifity. In a Midi sampler, that may mean infinite sustain.

#### struct `Audio::FRiffListChunk`  
`struct FRiffListChunk`  
_L156-161_
- L158 _public member_ `uint32 ChunkID;` — 'list'
- L159 _public member_ `uint32 ChunkDataSize;` — Depends on contained text
- L160 _public member_ `uint32 TypeID;` — always 'adtl'

#### struct `Audio::FRiffLabelChunk`  
`struct FRiffLabelChunk`  
_L163-168_
- L165 _public member_ `uint32 ChunkID;` — 'labl'
- L166 _public member_ `uint32 ChunkDataSize;` — depends on contained text
- L167 _public member_ `uint32 CuePointID;` — Cue Point ID associated with the label

#### class `Audio::FSoundFileChunkInfoWrapper`  
`class FSoundFileChunkInfoWrapper`  
_L174-232_
- desc: FSoundFileChunkInfoWrapper wraps FSoundFileChunkInfo and manages chunk data memory.
- L177 _public prototype_ `FSoundFileChunkInfoWrapper() = default;`
- L178 _public prototype_ `~FSoundFileChunkInfoWrapper() = default;`
- L179 _public prototype_ `FSoundFileChunkInfoWrapper(const FSoundFileChunkInfoWrapper& Other) = delete;`
- L180 _public prototype_ `FSoundFileChunkInfoWrapper& operator=(const FSoundFileChunkInfoWrapper& Other) = delete;`
- L182 _public function_ `FSoundFileChunkInfoWrapper(FSoundFileChunkInfoWrapper&& Other) noexcept`
- L195 _public function_ `FSoundFileChunkInfoWrapper& operator=(FSoundFileChunkInfoWrapper&& Other) noexcept`
- L210 _public function_ `void AllocateChunkData()`
- L219 _public function_ `FSoundFileChunkInfo* GetPtr()`
- L224 _public function_ `const FSoundFileChunkInfo* GetPtr() const`
- L230 _private member_ `FSoundFileChunkInfo ChunkInfo;`
- L231 _private member_ `TUniquePtr<uint8[]> ChunkData;`

#### class `Audio::ISoundFile`  
`class ISoundFile`  
_L238-251_
- desc: ISoundFile
- L241 _public prototype_ `virtual ~ISoundFile() = default;`
- L242 _public prototype_ `virtual ESoundFileError::Type GetState(ESoundFileState::Type& OutState) const = 0;`
- L243 _public prototype_ `virtual ESoundFileError::Type GetError() const = 0;`
- L244 _public prototype_ `virtual ESoundFileError::Type GetId(uint32& OutId) const = 0;`
- L245 _public prototype_ `virtual ESoundFileError::Type GetPath(FName& OutPath) const = 0;`
- L246 _public prototype_ `virtual ESoundFileError::Type GetBulkData(TArray<uint8>** OutData) const = 0;`
- L247 _public prototype_ `virtual ESoundFileError::Type GetDataSize(int32& DataSize) const = 0;`
- L248 _public prototype_ `virtual ESoundFileError::Type GetDescription(FSoundFileDescription& OutDescription) const = 0;`
- L249 _public prototype_ `virtual ESoundFileError::Type GetChannelMap(TArray<ESoundFileChannelMap::Type>& OutChannelMap) const = 0;`
- L250 _public prototype_ `virtual ESoundFileError::Type IsStreamed(bool& bOutIsStreamed) const = 0;`

#### class `Audio::ISoundFileReader`  
`class ISoundFileReader`  
_L253-268_
- L256 _public prototype_ `virtual ~ISoundFileReader() = default;`
- L258 _public prototype_ `virtual ESoundFileError::Type Init(TSharedPtr<ISoundFile> InSoundFileData, bool bIsStreamed) = 0;`
- L259 _public prototype_ `virtual ESoundFileError::Type Init(const TArray<uint8>* InData) = 0;`
- L260 _public prototype_ `virtual ESoundFileError::Type Release() = 0;`
- L261 _public prototype_ `virtual ESoundFileError::Type SeekFrames(SoundFileCount Offset, ESoundFileSeekMode::Type SeekMode, SoundFileCount& OutOffset) = 0;`
- L262 _public prototype_ `virtual ESoundFileError::Type ReadFrames(float* DataPtr, SoundFileCount NumFrames, SoundFileCount& OutNumFramesRead) = 0;`
- L263 _public prototype_ `virtual ESoundFileError::Type ReadFrames(double* DataPtr, SoundFileCount NumFrames, SoundFileCount& OutNumFramesRead) = 0;`
- L264 _public prototype_ `virtual ESoundFileError::Type ReadSamples(float* DataPtr, SoundFileCount NumSamples, SoundFileCount& OutNumSamplesRead) = 0;`
- L265 _public prototype_ `virtual ESoundFileError::Type ReadSamples(double* DataPtr, SoundFileCount NumSamples, SoundFileCount& OutNumSamplesRead) = 0;`
- L266 _public prototype_ `virtual ESoundFileError::Type GetDescription(FSoundFileDescription& OutputDescription, TArray<ESoundFileChannelMap::Type>& OutChannelMap) = 0;`
- L267 _public prototype_ `virtual ESoundFileError::Type GetOptionalChunks(FSoundFileChunkArray& OutChunkInfoArray, const TSet<uint32>& ChunkIdsToSkip = {}) = 0;`

#### class `Audio::ISoundFileWriter`  
`class ISoundFileWriter`  
_L270-286_
- L273 _public prototype_ `virtual ~ISoundFileWriter() = default;`
- L275 _public prototype_ `virtual ESoundFileError::Type Init(const FSoundFileDescription& FileDescription, const TArray<ESoundFileChannelMap::Type>& InChannelMap, double EncodingQuality) = 0;`
- L276 _public prototype_ `virtual ESoundFileError::Type Release() = 0;`
- L277 _public prototype_ `virtual ESoundFileError::Type SeekFrames(SoundFileCount Offset, ESoundFileSeekMode::Type SeekMode, SoundFileCount& OutOffset) = 0;`
- L278 _public prototype_ `virtual ESoundFileError::Type WriteFrames(const float* Data, SoundFileCount NumFrames, SoundFileCount& OutNumFramesWritten) = 0;`
- L279 _public prototype_ `virtual ESoundFileError::Type WriteFrames(const double* Data, SoundFileCount NumFrames, SoundFileCount& OutNumFramesWritten) = 0;`
- L280 _public prototype_ `virtual ESoundFileError::Type WriteSamples(const float* DataPtr, SoundFileCount NumSamples, SoundFileCount& OutNumSampleWritten) = 0;`
- L281 _public prototype_ `virtual ESoundFileError::Type WriteSamples(const double* DataPtr, SoundFileCount NumSamples, SoundFileCount& OutNumSampleWritten) = 0;`
- L282 _public prototype_ `virtual ESoundFileError::Type GetData(TArray<uint8>** OutData) = 0;`
- L283 _public prototype_ `virtual ESoundFileError::Type WriteOptionalChunks(const FSoundFileChunkArray& ChunkInfoArray) = 0;`
- L284 _public prototype_ `virtual ESoundFileError::Type WriteByteArrayChunk(TArray<uint8>& InSoundFileChunk) = 0;`
- L285 _public prototype_ `virtual ESoundFileError::Type WriteCueCommandData(FSoundFileCues& InSoundFileData) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L11 _typedef_ `using SoundFileCount = int64;` (scope `Audio`)
- L233 _typedef_ `typedef TArray<FSoundFileChunkInfoWrapper> FSoundFileChunkArray;` (scope `Audio`)

### `Source/Runtime/AudioMixer/Private/SoundFileIO/SoundFileIOEnums.h` (Private)


#### enum `Audio::ESoundFileError::Type`  
`enum class Type : uint8`  
_L11-31_
- L13 _public enumerator_ `NONE = 0`
- L14 _public enumerator_ `INVALID_SOUND_FILE`
- L15 _public enumerator_ `INVALID_SOUND_FILE_HANDLE`
- L16 _public enumerator_ `BAD_ENCODING_QUALITY`
- L17 _public enumerator_ `FAILED_TO_LOAD_BYTE_DATA`
- L18 _public enumerator_ `ALREADY_OPENED`
- L19 _public enumerator_ `ALREADY_HAS_DATA`
- L20 _public enumerator_ `INVALID_DATA`
- L21 _public enumerator_ `FILE_DOESNT_EXIST`
- L22 _public enumerator_ `INVALID_INPUT_FORMAT`
- L23 _public enumerator_ `INVALID_CHANNEL_MAP`
- L24 _public enumerator_ `FAILED_TO_OPEN`
- L25 _public enumerator_ `FAILED_TO_SEEK`
- L26 _public enumerator_ `ALREADY_INITIALIZED`
- L27 _public enumerator_ `LOADING`
- L28 _public enumerator_ `INVALID_STATE`
- L29 _public enumerator_ `INVALID_CHUNK`
- L30 _public enumerator_ `UNKNOWN`

#### enum `Audio::ESoundFileSeekMode::Type`  
`enum Type`  
_L60-65_
- L62 _public enumerator_ `FROM_START = 0`
- L63 _public enumerator_ `FROM_CURRENT = 1`
- L64 _public enumerator_ `FROM_END = 2`

#### enum `Audio::ESoundFileFormat::Flags`  
`enum Flags`  
_L77-119_
- L80 _public enumerator_ `WAV = 0x010000` — Major Formats
- L81 _public enumerator_ `AIFF = 0x020000` — Apple AIFF format
- L82 _public enumerator_ `FLAC = 0x170000` — FLAC lossless
- L83 _public enumerator_ `OGG = 0x200000` — Xiph OGG
- L86 _public enumerator_ `PCM_SIGNED_8 = 0x0001` — Uncompressed Minor Formats
- L87 _public enumerator_ `PCM_SIGNED_16 = 0x0002` — Signed 16 bit PCM
- L88 _public enumerator_ `PCM_SIGNED_24 = 0x0003` — Signed 24 bit PCM
- L89 _public enumerator_ `PCM_SIGNED_32 = 0x0004` — Signed 32 bit PCM
- L90 _public enumerator_ `PCM_UNSIGNED_8 = 0x0005` — Unsigned 8 bit PCM
- L91 _public enumerator_ `PCM_FLOAT = 0x0006` — 32 bit float
- L92 _public enumerator_ `PCM_DOUBLE = 0x0007` — 64 bit float
- L95 _public enumerator_ `MU_LAW = 0x0010` — Compressed Minor Formats
- L96 _public enumerator_ `A_LAW = 0x0011` — A-law encoding
- L97 _public enumerator_ `IMA_ADPCM = 0x0012` — IMA ADPCM encoding
- L98 _public enumerator_ `MS_ADPCM = 0x0013` — Microsoft ADPCM encoding
- L99 _public enumerator_ `GSM_610 = 0x0020` — GSM 6.10 encoding
- L100 _public enumerator_ `G721_32 = 0x0030` — 32 kbps G721 ADPCM encoding
- L101 _public enumerator_ `G723_24 = 0x0031` — 23 kbps G723 ADPCM encoding
- L102 _public enumerator_ `G723_40 = 0x0032` — 40 kbps G723 ADPCM encoding
- L103 _public enumerator_ `DWVW_12 = 0x0040` — 12 bit delta-width variable word encoding
- L104 _public enumerator_ `DMVW_16 = 0x0041` — 16 bit delta-width variable word encoding
- L105 _public enumerator_ `DMVW_24 = 0x0042` — 24 bit delta-width variable word encoding
- L106 _public enumerator_ `DMVW_N = 0x0043` — N bit delta-width variable word encoding
- L107 _public enumerator_ `VORBIS = 0x0060` — Xiph vorbis encoding
- L110 _public enumerator_ `ENDIAN_FILE = 0x00000000` — Endian opts
- L111 _public enumerator_ `ENDIAN_LITTLE = 0x10000000` — little-endian
- L112 _public enumerator_ `ENDIAN_BIG = 0x20000000` — big-endian
- L113 _public enumerator_ `ENDIAN_CPU = 0x30000000` — cpu-endian
- L116 _public enumerator_ `MINOR_FORMAT_MASK = 0x0000FFFF` — Masks
- L117 _public enumerator_ `MAJOR_FORMAT_MASK = 0x0FFF0000`
- L118 _public enumerator_ `ENDIAN_MASK = 0x30000000`

#### enum `Audio::ESoundFileChannelMap::Type`  
`enum class Type : uint32`  
_L170-195_
- desc: this is used to populate an array which is passed into a sound file API call so must be uint32
- L172 _public enumerator_ `INVALID = 0`
- L173 _public enumerator_ `MONO`
- L174 _public enumerator_ `LEFT`
- L175 _public enumerator_ `RIGHT`
- L176 _public enumerator_ `CENTER`
- L177 _public enumerator_ `FRONT_LEFT`
- L178 _public enumerator_ `FRONT_RIGHT`
- L179 _public enumerator_ `FRONT_CENTER`
- L180 _public enumerator_ `BACK_CENTER`
- L181 _public enumerator_ `BACK_LEFT`
- L182 _public enumerator_ `BACK_RIGHT`
- L183 _public enumerator_ `LFE`
- L184 _public enumerator_ `LEFT_CENTER`
- L185 _public enumerator_ `RIGHT_CENTER`
- L186 _public enumerator_ `SIDE_LEFT`
- L187 _public enumerator_ `SIDE_RIGHT`
- L188 _public enumerator_ `TOP_CENTER`
- L189 _public enumerator_ `TOP_FRONT_LEFT`
- L190 _public enumerator_ `TOP_FRONT_RIGHT`
- L191 _public enumerator_ `TOP_FRONT_CENTER`
- L192 _public enumerator_ `TOP_BACK_LEFT`
- L193 _public enumerator_ `TOP_BACK_RIGHT`
- L194 _public enumerator_ `TOP_BACK_CENTER`

#### enum `Audio::ESoundFileOpenMode::Type`  
`enum Type`  
_L231-236_
- L233 _public enumerator_ `READING = 0x10`
- L234 _public enumerator_ `WRITING = 0x20`
- L235 _public enumerator_ `UNKNOWN = 0`

#### enum `Audio::ESoundFileState::Type`  
`enum Type`  
_L241-250_
- L243 _public enumerator_ `UNINITIALIZED = 0`
- L244 _public enumerator_ `INITIALIZED`
- L245 _public enumerator_ `LOADING`
- L246 _public enumerator_ `LOADED`
- L247 _public enumerator_ `STREAMING`
- L248 _public enumerator_ `WRITING`
- L249 _public enumerator_ `HAS_ERROR`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L9 _namespace_ `namespace ESoundFileError` (scope `Audio`)
- L33 _function_ `inline const TCHAR* ToString(ESoundFileError::Type SoundFileError)` (scope `Audio::ESoundFileError`)
- L58 _namespace_ `namespace ESoundFileSeekMode` (scope `Audio`)
- L75 _namespace_ `namespace ESoundFileFormat` (scope `Audio`)
- L121 _function_ `inline const TCHAR* ToStringMajor(int32 FormatFlags)` (scope `Audio::ESoundFileFormat`)
- L133 _function_ `inline const TCHAR* ToStringMinor(int32 FormatFlags)` (scope `Audio::ESoundFileFormat`)
- L167 _namespace_ `namespace ESoundFileChannelMap` (scope `Audio`)
- L197 _function_ `inline const TCHAR* ToString(ESoundFileChannelMap::Type ChannelMap)` (scope `Audio::ESoundFileChannelMap`)
- L229 _namespace_ `namespace ESoundFileOpenMode` (scope `Audio`)
- L239 _namespace_ `namespace ESoundFileState` (scope `Audio`)

### `Source/Runtime/AudioMixer/Private/SoundFileIO/SoundFileIOManager.h` (Private)


#### class `Audio::FSoundFileIOManager`  
`class FSoundFileIOManager`  
_L12-30_
- L15 _public prototype_ `FSoundFileIOManager();`
- L16 _public prototype_ `~FSoundFileIOManager();`
- L18 _public prototype_ `TSharedPtr<ISoundFileReader> CreateSoundFileReader();`
- L19 _public prototype_ `TSharedPtr<ISoundFileReader> CreateSoundDataReader();`
- L20 _public prototype_ `TSharedPtr<ISoundFileWriter> CreateSoundFileWriter();`
- L22 _public prototype_ `bool GetSoundFileDescription(const FString& FilePath, FSoundFileDescription& OutputDescription, TArray<ESoundFileChannelMap::Type>& OutChannelMap);`
- L23 _public prototype_ `bool GetSoundFileDescription(const FString& FilePath, FSoundFileDescription& OutputDescription);`
- L24 _public prototype_ `bool GetFileExtensionForFormatFlags(int32 FormatFlags, FString& OutExtension);`
- L25 _public prototype_ `ESoundFileError::Type GetSoundFileInfoFromPath(const FString& FilePath, FSoundFileDescription& Description, TArray<ESoundFileChannelMap::Type>& ChannelMap);`
- L26 _public prototype_ `ESoundFileError::Type LoadSoundFileFromPath(const FString& FilePath, FSoundFileDescription& Description, TArray<ESoundFileChannelMap::Type>& ChannelMap, TArray<uint8>& BulkData);`
- L29 _private member_ `TUniquePtr<FSoundFileIOManagerImpl> Impl;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L32 _prototype_ `bool SoundFileIOManagerInit();` (scope `Audio`)
- L33 _prototype_ `bool SoundFileIOManagerShutdown();` (scope `Audio`)

### `Source/Runtime/AudioMixer/Private/SoundFileIO/SoundFileIOManagerImpl.h` (Private)


#### class `Audio::FSoundFileIOManagerImpl`  
`class FSoundFileIOManagerImpl`  
_L12-27_
- L15 _public prototype_ `FSoundFileIOManagerImpl();`
- L16 _public prototype_ `~FSoundFileIOManagerImpl();`
- L18 _public prototype_ `TSharedPtr<ISoundFileReader> CreateSoundFileReader();`
- L19 _public prototype_ `TSharedPtr<ISoundFileReader> CreateSoundDataReader();`
- L20 _public prototype_ `TSharedPtr<ISoundFileWriter> CreateSoundFileWriter();`
- L22 _public prototype_ `bool GetSoundFileDescription(const FString& FilePath, FSoundFileDescription& OutputDescription, TArray<ESoundFileChannelMap::Type>& OutChannelMap);`
- L23 _public prototype_ `bool GetSoundFileDescription(const FString& FilePath, FSoundFileDescription& OutputDescription);`
- L24 _public prototype_ `bool GetFileExtensionForFormatFlags(int32 FormatFlags, FString& OutExtension);`
- L25 _public prototype_ `ESoundFileError::Type GetSoundFileInfoFromPath(const FString& FilePath, FSoundFileDescription& Description, TArray<ESoundFileChannelMap::Type>& ChannelMap);`
- L26 _public prototype_ `ESoundFileError::Type LoadSoundFileFromPath(const FString& FilePath, FSoundFileDescription& Description, TArray<ESoundFileChannelMap::Type>& ChannelMap, TArray<uint8>& BulkData);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Public/AudioBusSubsystem.h` (Public)


#### struct `Audio::FAudioBusKey`  
`struct FAudioBusKey`  
_L22-61_
- L24 _public member_ `uint32 ObjectId = INDEX_NONE;` — from a corresponding UObject (UAudioBus) if applicable
- L25 _public member_ `uint32 InstanceId = INDEX_NONE;`
- L27 _public function_ `FAudioBusKey() : InstanceId(InstanceIdCounter++)`
- L33 _public function_ `FAudioBusKey(uint32 InObjectId) : ObjectId(InObjectId)` — For construction with a given UObject unique id
- L38 _public function_ `const bool IsValid() const`
- L60 _private member_ `static std::atomic<uint32> InstanceIdCounter;`

#### class `UAudioBusSubsystem`  
`class UAudioBusSubsystem : public UAudioEngineSubsystem`  
_L68-138_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioEngineSubsystem`
- desc: UAudioBusSubsystem
- L73 _public prototype_ `UAudioBusSubsystem();`
- L74 _public prototype_ `virtual ~UAudioBusSubsystem() = default;`
- L77 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L78 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L79 _public prototype_ `virtual void Deinitialize() override;`
- L84 _public prototype_ `void StartAudioBus(Audio::FAudioBusKey InAudioBusKey, int32 InNumChannels, bool bInIsAutomatic);` — `UE_DEPRECATED(5.6, "Use the StartAudioBus version that requires an AudioBus name.")` — Audio bus API from FMixerDevice
- L86 _public prototype_ `void StartAudioBus(Audio::FAudioBusKey InAudioBusKey, const FString& InAudioBusName, int32 InNumChannels, bool bInIsAutomatic);`
- L87 _public prototype_ `void StopAudioBus(Audio::FAudioBusKey InAudioBusKey);`
- L88 _public prototype_ `bool IsAudioBusActive(Audio::FAudioBusKey InAudioBusKey) const;`
- L90 _public prototype_ `Audio::FPatchInput AddPatchInputForAudioBus(Audio::FAudioBusKey InAudioBusKey, int32 InFrames, int32 InChannels, float InGain = 1.f);`
- L91 _public prototype_ `Audio::FPatchOutputStrongPtr AddPatchOutputForAudioBus(Audio::FAudioBusKey InAudioBusKey, int32 InFrames, int32 InChannels, float InGain = 1.f);`
- L93 _public prototype_ `Audio::FPatchInput AddPatchInputForSoundAndAudioBus(uint64 SoundInstanceID, Audio::FAudioBusKey AudioBusKey, int32 InFrames, int32 NumChannels, float InGain = 1.f);`
- L94 _public prototype_ `Audio::FPatchOutputStrongPtr AddPatchOutputForSoundAndAudioBus(uint64 SoundInstanceID, Audio::FAudioBusKey AudioBusKey, int32 InFrames, int32 NumChannels, float InGain = 1.f);`
- L95 _public prototype_ `void ConnectPatches(uint64 SoundInstanceID);`
- L96 _public prototype_ `void RemoveSound(uint64 SoundInstanceID);`
- L98 _public prototype_ `void InitDefaultAudioBuses();`
- L99 _public prototype_ `void ShutdownDefaultAudioBuses();`
- L109 _private member_ `TArray<TStrongObjectPtr<UAudioBus>> DefaultAudioBuses;`
- L111 _private member_ `TMap<Audio::FAudioBusKey, FActiveBusData> ActiveAudioBuses_GameThread;` — The active audio bus list accessible on the game thread
- L127 _private prototype_ `void AddPendingConnection(uint64 SoundInstanceID, FPendingConnection&& PendingConnection);`
- L134 _private prototype_ `TArray<FPendingConnection> ExtractPendingConnectionsIfReady(uint64 SoundInstanceID);`
- L136 _private member_ `TMap<uint64, FSoundInstanceConnections> SoundInstanceConnectionMap;`
- L137 _private member_ `FCriticalSection Mutex;`

#### struct `UAudioBusSubsystem::FActiveBusData`  
`struct FActiveBusData`  
_L102-107_
- L104 _public member_ `Audio::FAudioBusKey BusKey = 0;`
- L105 _public member_ `int32 NumChannels = 0;`
- L106 _public member_ `bool bIsAutomatic = false;`

#### struct `UAudioBusSubsystem::FPendingConnection`  
`struct FPendingConnection`  
_L113-125_
- L115 _public typedef_ `using FPatchVariant = TVariant<Audio::FPatchInput, Audio::FPatchOutputStrongPtr>;`
- L116 _public member_ `FPatchVariant PatchVariant;`
- L117 _public member_ `Audio::FAudioBusKey AudioBusKey;`
- L118 _public member_ `int32 BlockSizeFrames = 0;`
- L119 _public member_ `int32 NumChannels = 0;`
- L120 _public member_ `bool bIsAutomatic = false;`
- L123 _public member_ `uint64 InstanceID = 0u;` — MixerSourceBuffer instance ID, used for PlayOrder resolution in trace profiling

#### struct `UAudioBusSubsystem::FSoundInstanceConnections`  
`struct FSoundInstanceConnections`  
_L129-132_
- L131 _public member_ `TArray<FPendingConnection> PendingConnections;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Audio`
- L43 _function_ `inline friend uint32 GetTypeHash(const FAudioBusKey& Key)` (scope `Audio`)
- L48 _function_ `inline friend bool operator==(const FAudioBusKey& InLHS, const FAudioBusKey& InRHS)` (scope `Audio`)
- L53 _function_ `inline friend bool operator!=(const FAudioBusKey& InLHS, const FAudioBusKey& InRHS)` (scope `Audio`)

### `Source/Runtime/AudioMixer/Public/AudioDeviceNotificationSubsystem.h` (Public)


#### enum `EAudioDeviceChangedRole`  
`enum class EAudioDeviceChangedRole : uint8`  
_L15-22_
- reflection: `UENUM(BlueprintType)`
- desc: EAudioDeviceChangedRole
- L17 _public enumerator_ `Invalid`
- L18 _public enumerator_ `Console`
- L19 _public enumerator_ `Multimedia`
- L20 _public enumerator_ `Communications`
- L21 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EAudioDeviceChangedState`  
`enum class EAudioDeviceChangedState : uint8`  
_L28-36_
- reflection: `UENUM(BlueprintType)`
- desc: EAudioDeviceChangedState
- L30 _public enumerator_ `Invalid`
- L31 _public enumerator_ `Active`
- L32 _public enumerator_ `Disabled`
- L33 _public enumerator_ `NotPresent`
- L34 _public enumerator_ `Unplugged`
- L35 _public enumerator_ `Count UMETA(Hidden)`

#### class `UAudioDeviceNotificationSubsystem`  
`class UAudioDeviceNotificationSubsystem : public UEngineSubsystem , public Audio::IAudioMixerDeviceChangedListener`  
_L50-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem,Audio::IAudioMixerDeviceChangedListener`
- desc: UAudioDeviceNotificationSubsystem
- L57 _public prototype_ `virtual ~UAudioDeviceNotificationSubsystem() = default;`
- L59 _public function_ `static UAudioDeviceNotificationSubsystem* Get()`
- L62 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L63 _public prototype_ `virtual void Deinitialize() override;`
- L67 _public prototype_ `virtual void OnDefaultCaptureDeviceChanged(const Audio::EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L68 _public prototype_ `virtual void OnDefaultRenderDeviceChanged(const Audio::EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L69 _public prototype_ `virtual void OnDeviceAdded(const FString& DeviceId, bool bIsRenderDevice) override;`
- L70 _public prototype_ `virtual void OnDeviceRemoved(const FString& DeviceId, bool bIsRenderDevice) override;`
- L71 _public prototype_ `virtual void OnDeviceStateChanged(const FString& DeviceId, const Audio::EAudioDeviceState InState, bool bIsRenderDevice) override;`
- L74 _public prototype_ `virtual void OnDeviceSwitched(const FString& DeviceId);`
- L78 _public member_ `FOnAudioDefaultDeviceChanged DefaultCaptureDeviceChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Audio Delegates")` — Multicast delegate triggered when default capture device changes
- L80 _public member_ `FOnAudioDefaultDeviceChangedNative DefaultCaptureDeviceChangedNative;` — Multicast delegate triggered when default capture device changes (native code only)
- L84 _public member_ `FOnAudioDefaultDeviceChanged DefaultRenderDeviceChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Audio Delegates")` — Multicast delegate triggered when default render device changes
- L86 _public member_ `FOnAudioDefaultDeviceChangedNative DefaultRenderDeviceChangedNative;` — Multicast delegate triggered when default render device changes (native code only)
- L90 _public member_ `FOnAudioDeviceChange DeviceAdded;` — `UPROPERTY(BlueprintAssignable, Category = "Audio Delegates")` — Multicast delegate triggered when a device is added
- L92 _public member_ `FOnAudioDeviceChangeNative DeviceAddedNative;` — Multicast delegate triggered when a device is added (native code only)
- L96 _public member_ `FOnAudioDeviceChange DeviceRemoved;` — `UPROPERTY(BlueprintAssignable, Category = "Audio Delegates")` — Multicast delegate triggered when a device is removed
- L98 _public member_ `FOnAudioDeviceChangeNative DeviceRemovedNative;` — Multicast delegate triggered when a device is removed (native code only)
- L102 _public member_ `FOnAudioDeviceStateChanged DeviceStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Audio Delegates")` — Multicast delegate triggered on device state change
- L104 _public member_ `FOnAudioDeviceStateChangedNative DeviceStateChangedNative;` — Multicast delegate triggered on device state change (native code only)
- L108 _public member_ `FOnAudioDeviceChange DeviceSwitched;` — `UPROPERTY(BlueprintAssignable, Category = "Audio Delegates")` — Multicast delegate triggered on device switch
- L110 _public member_ `FOnAudioDeviceChangeNative DeviceSwitchedNative;` — Multicast delegate triggered on device switch (native code only)
- L114 _protected prototype_ `EAudioDeviceChangedRole GetDeviceChangedRole(Audio::EAudioDeviceRole InRole) const;`
- L115 _protected prototype_ `EAudioDeviceChangedState GetDeviceChangedState(Audio::EAudioDeviceState InState) const;`

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioDefaultDeviceChanged, EAudioDeviceChangedRole, AudioDeviceRole, FString, DeviceId);`
- L38 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioDefaultDeviceChanged, EAudioDeviceChangedRole, AudioDeviceRole, FString, DeviceId);`
- L39 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioDeviceStateChanged, FString, DeviceId, EAudioDeviceChangedState, NewState);`
- L39 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAudioDeviceStateChanged, FString, DeviceId, EAudioDeviceChangedState, NewState);`
- L40 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioDeviceChange, FString, DeviceId);`
- L40 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioDeviceChange, FString, DeviceId);`
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioDefaultDeviceChangedNative, EAudioDeviceChangedRole, FString);`
- L42 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioDefaultDeviceChangedNative, EAudioDeviceChangedRole, FString);`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioDeviceStateChangedNative, FString, EAudioDeviceChangedState);`
- L43 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioDeviceStateChangedNative, FString, EAudioDeviceChangedState);`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioDeviceChangeNative, FString);`
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioDeviceChangeNative, FString);`

### `Source/Runtime/AudioMixer/Public/AudioMixerBlueprintLibrary.h` (Public)


#### enum `EMusicalNoteName`  
`enum class EMusicalNoteName : uint8`  
_L28-42_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `C = 0`
- L31 _public enumerator_ `Db = 1`
- L32 _public enumerator_ `D = 2`
- L33 _public enumerator_ `Eb = 3`
- L34 _public enumerator_ `E = 4`
- L35 _public enumerator_ `F = 5`
- L36 _public enumerator_ `Gb = 6`
- L37 _public enumerator_ `G = 7`
- L38 _public enumerator_ `Ab = 8`
- L39 _public enumerator_ `A = 9`
- L40 _public enumerator_ `Bb = 10`
- L41 _public enumerator_ `B = 11`

#### enum `EAudioMixerStreamDataFormatType`  
`enum class EAudioMixerStreamDataFormatType : uint8`  
_L46-52_
- reflection: `UENUM()`
- desc: Duplicate of Audio::EAudioMixerStreamDataFormat::Type, to get around UHT's lack of namespace support
- L48 _public enumerator_ `Unknown`
- L49 _public enumerator_ `Float`
- L50 _public enumerator_ `Int16`
- L51 _public enumerator_ `Unsupported`

#### enum `EAudioMixerChannelType`  
`enum class EAudioMixerChannelType : uint8`  
_L58-81_
- reflection: `UENUM()`
- desc: A copy of Audio::EAudioMixerChannel::Type to get around UHT's refusal of namespaces
- L60 _public enumerator_ `FrontLeft`
- L61 _public enumerator_ `FrontRight`
- L62 _public enumerator_ `FrontCenter`
- L63 _public enumerator_ `LowFrequency`
- L64 _public enumerator_ `BackLeft`
- L65 _public enumerator_ `BackRight`
- L66 _public enumerator_ `FrontLeftOfCenter`
- L67 _public enumerator_ `FrontRightOfCenter`
- L68 _public enumerator_ `BackCenter`
- L69 _public enumerator_ `SideLeft`
- L70 _public enumerator_ `SideRight`
- L71 _public enumerator_ `TopCenter`
- L72 _public enumerator_ `TopFrontLeft`
- L73 _public enumerator_ `TopFrontCenter`
- L74 _public enumerator_ `TopFrontRight`
- L75 _public enumerator_ `TopBackLeft`
- L76 _public enumerator_ `TopBackCenter`
- L77 _public enumerator_ `TopBackRight`
- L78 _public enumerator_ `Unknown`
- L79 _public enumerator_ `ChannelTypeCount`
- L80 _public enumerator_ `DefaultChannel = FrontLeft`

#### enum `ESwapAudioOutputDeviceResultState`  
`enum class ESwapAudioOutputDeviceResultState : uint8`  
_L114-119_
- reflection: `UENUM(BlueprintType)`
- desc: Resulting State of SwapAudioOutputDevice call
- L116 _public enumerator_ `Failure`
- L117 _public enumerator_ `Success`
- L118 _public enumerator_ `None`

#### struct `FSwapAudioOutputResult`  
`struct FSwapAudioOutputResult`  
_L125-142_
- reflection: `USTRUCT(BlueprintType)`
- desc: Out structure for use with AudioMixerBlueprintLibrary::SwapAudioOutputDevice
- L129 _public prototype_ `FSwapAudioOutputResult() = default;`
- L133 _public member_ `FString CurrentDeviceId;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — ID of the currently set device.  This is the device at the time of the call, NOT the resulting deviceId
- L137 _public member_ `FString RequestedDeviceId;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — ID of the requested device.
- L141 _public member_ `ESwapAudioOutputDeviceResultState Result = ESwapAudioOutputDeviceResultState::None;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — Result of the call

#### struct `FAudioOutputDeviceInfo`  
`struct FAudioOutputDeviceInfo`  
_L148-195_
- reflection: `USTRUCT(BlueprintType)`
- desc: Platform audio output device info, in a Blueprint-readable format
- L152 _public function_ `FAudioOutputDeviceInfo() : Name("") , DeviceId("") , NumChannels(0) , SampleRate(0) , Format(EAudioMixerStreamDataFormatType::Unknown) , bIsSystemDefault(true) , bIsCurrentDevice(false)`
- L162 _public prototype_ `FAudioOutputDeviceInfo(const Audio::FAudioPlatformDeviceInfo& InDeviceInfo);`
- L166 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category="Audio")` — The name of the audio device
- L170 _public member_ `FString DeviceId;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — ID of the device.
- L174 _public member_ `int32 NumChannels = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — The number of channels supported by the audio device
- L178 _public member_ `int32 SampleRate = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — The sample rate of the audio device
- L182 _public member_ `EAudioMixerStreamDataFormatType Format = EAudioMixerStreamDataFormatType::Unknown;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — The data format of the audio stream
- L186 _public member_ `TArray<EAudioMixerChannelType> OutputChannelArray;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — The output channel array of the audio device
- L190 _public member_ `uint8 bIsSystemDefault : 1;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — Whether or not this device is the system default
- L194 _public member_ `uint8 bIsCurrentDevice : 1;` — `UPROPERTY(BlueprintReadOnly, Category = "Audio")` — Whether or not this device is the device currently in use

#### class `UAudioMixerBlueprintLibrary`  
`class UAudioMixerBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L213-411_
- reflection: `UCLASS(meta=(ScriptName="AudioMixerLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L224 _public prototype_ `static FString Conv_AudioOutputDeviceInfoToString(const FAudioOutputDeviceInfo& Info);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Audio Output Device Info To String", CompactNodeTitle = "->", BlueprintAutocast), Category = "Audio")` — Returns the device info in a human readable format @param info - The audio device data to print @return The data in a string format
- L228 _public prototype_ `static void AddMasterSubmixEffect(const UObject* WorldContextObject, USoundEffectSubmixPreset* SubmixEffectPreset);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta=(WorldContext="WorldContextObject"))` — Adds a submix effect preset to the master submix.
- L232 _public prototype_ `static void RemoveMasterSubmixEffect(const UObject* WorldContextObject, USoundEffectSubmixPreset* SubmixEffectPreset);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta=(WorldContext="WorldContextObject"))` — Removes a submix effect preset from the master submix.
- L236 _public prototype_ `static void ClearMasterSubmixEffects(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Clears all master submix effects.
- L240 _public prototype_ `static int32 AddSubmixEffect(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, USoundEffectSubmixPreset* SubmixEffectPreset);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Adds a submix effect preset to the given submix at the end of its submix effect chain. Returns the number of submix effects.
- L244 _public prototype_ `static void RemoveSubmixEffectPreset(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, USoundEffectSubmixPreset* SubmixEffectPreset);` — `UE_DEPRECATED(4.27, "RemoveSubmixEffectPreset is deprecated, use RemoveSubmixEffect.")` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject", DeprecatedFunction))`
- L248 _public prototype_ `static void RemoveSubmixEffect(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, USoundEffectSubmixPreset* SubmixEffectPreset);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Removes all instances of a submix effect preset from the given submix.
- L252 _public prototype_ `static void RemoveSubmixEffectPresetAtIndex(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, int32 SubmixChainIndex);` — `UE_DEPRECATED(4.27, "RemoveSubmixEffectPresetAtIndex is deprecated, use RemoveSubmixEffectAtIndex.")` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject", DeprecatedFunction))`
- L256 _public prototype_ `static void RemoveSubmixEffectAtIndex(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, int32 SubmixChainIndex);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Removes the submix effect at the given submix chain index, if there is a submix effect at that index.
- L260 _public prototype_ `static void ReplaceSoundEffectSubmix(const UObject* WorldContextObject, USoundSubmix* InSoundSubmix, int32 SubmixChainIndex, USoundEffectSubmixPreset* SubmixEffectPreset);` — `UE_DEPRECATED(4.27, "ReplaceSoundEffectSubmix is deprecated, use ReplaceSubmixEffect.")` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject", DeprecatedFunction))`
- L264 _public prototype_ `static void ReplaceSubmixEffect(const UObject* WorldContextObject, USoundSubmix* InSoundSubmix, int32 SubmixChainIndex, USoundEffectSubmixPreset* SubmixEffectPreset);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Replaces the submix effect at the given submix chain index, adds the effect if there is none at that index.
- L268 _public prototype_ `static void ClearSubmixEffects(const UObject* WorldContextObject, USoundSubmix* SoundSubmix);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Clears all submix effects on the given submix.
- L272 _public prototype_ `static void SetSubmixEffectChainOverride(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, TArray<USoundEffectSubmixPreset*> SubmixEffectPresetChain, float FadeTimeSec);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Sets a submix effect chain override on the given submix. The effect chain will cross fade from the base effect chain or current override to the new override.
- L276 _public prototype_ `static void ClearSubmixEffectChainOverride(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, float FadeTimeSec);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Clears all submix effect overrides on the given submix and returns it to the default effect chain.
- L280 _public prototype_ `static void StartRecordingOutput(const UObject* WorldContextObject, float ExpectedDuration, USoundSubmix* SubmixToRecord = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Recording", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 1))` — Start recording audio. By leaving the Submix To Record field blank, you can record the master output of the game.
- L284 _public prototype_ `static USoundWave* StopRecordingOutput(const UObject* WorldContextObject, EAudioRecordingExportType ExportType, const FString& Name, FString Path, USoundSubmix* SubmixToRecord = nullptr, USoundWave* ExistingSoundWaveToOverwrite= nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Recording", meta = (WorldContext = "WorldContextObject", DisplayName = "Finish Recording Output", AdvancedDisplay = 4))` — Stop recording audio. Path can be absolute, or relative (to the /Saved/BouncedWavFiles folder). By leaving the Submix To Record field blank, you can record the master output of the game.
- L288 _public prototype_ `static void PauseRecordingOutput(const UObject* WorldContextObject, USoundSubmix* SubmixToPause = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Recording", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 1))` — Pause recording audio, without finalizing the recording to disk. By leaving the Submix To Record field blank, you can record the master output of the game.
- L292 _public prototype_ `static void ResumeRecordingOutput(const UObject* WorldContextObject, USoundSubmix* SubmixToPause = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Recording", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 1))` — Resume recording audio after pausing. By leaving the Submix To Pause field blank, you can record the master output of the game.
- L296 _public prototype_ `static void StartAnalyzingOutput(const UObject* WorldContextObject, USoundSubmix* SubmixToAnalyze = nullptr, EFFTSize FFTSize = EFFTSize::DefaultSize, EFFTPeakInterpolationMethod InterpolationMethod = EFFTPeakInterpolationMethod::Linear, EFFTWindowType WindowType = EFFTWindowType::Hann, float HopSize = 0, EAudioSpectrumType SpectrumType = EAudioSpectrumType::MagnitudeSpectrum);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Analysis", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 1))` — Start spectrum analysis of the audio output. By leaving the Submix To Analyze blank, you can analyze the master output of the game.
- L300 _public prototype_ `static void StopAnalyzingOutput(const UObject* WorldContextObject, USoundSubmix* SubmixToStopAnalyzing = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Analysis", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 1))` — Stop spectrum analysis.
- L311 _public prototype_ `static TArray<FSoundSubmixSpectralAnalysisBandSettings> MakeMusicalSpectralAnalysisBandSettings(int32 InNumSemitones=60, EMusicalNoteName InStartingMusicalNote = EMusicalNoteName::C, int32 InStartingOctave = 2, int32 InAttackTimeMsec = 10, int32 InReleaseTimeMsec = 10);` — `UFUNCTION(BlueprintPure, Category = "Audio|Analysis", meta = (AdvancedDisplay = 3))` — Make an array of musically spaced bands with ascending frequency. @param InNumSemitones - The number of semitones to represent. @param InStartingMuiscalNote - The name of the first note in the array. @param InStartingOctave - The octave of the first note in the array. @param InAttackTimeMsec - The attack time (in milliseconds) to apply to each band's envelope tracker. @param InReleaseTimeMsec - The release time (in milliseconds) to apply to each band's envelope tracker.
- L322 _public prototype_ `static TArray<FSoundSubmixSpectralAnalysisBandSettings> MakeFullSpectrumSpectralAnalysisBandSettings(int32 InNumBands = 30, float InMinimumFrequency=40.f, float InMaximumFrequency=16000.f, int32 InAttackTimeMsec = 10, int32 InReleaseTimeMsec = 10);` — `UFUNCTION(BlueprintPure, Category = "Audio|Analysis", meta = (AdvancedDisplay = 3))` — Make an array of logarithmically spaced bands. @param InNumBands - The number of bands to used to represent the spectrum. @param InMinimumFrequency - The center frequency of the first band. @param InMaximumFrequency - The center frequency of the last band. @param InAttackTimeMsec - The attack time (in milliseconds) to apply to each band's envelope tracker. @param InReleaseTimeMsec - The release time (in milliseconds) to apply to each band's envelope tracker.
- L332 _public prototype_ `static TArray<FSoundSubmixSpectralAnalysisBandSettings> MakePresetSpectralAnalysisBandSettings(EAudioSpectrumBandPresetType InBandPresetType, int32 InNumBands = 10, int32 InAttackTimeMsec = 10, int32 InReleaseTimeMsec = 10);` — `UFUNCTION(BlueprintPure, Category = "Audio|Analysis", meta = (AdvancedDisplay = 2))` — Make an array of bands which span the frequency range of a given EAudioSpectrumBandPresetType. @param InBandPresetType - The type audio content which the bands encompass. @param InNumBands - The number of bands used to represent the spectrum. @param InAttackTimeMsec - The attack time (in milliseconds) to apply to each band's envelope tracker. @param InReleaseTimeMsec - The release time (in milliseconds) to apply to each band's envelope tracker.
- L336 _public prototype_ `static void GetMagnitudeForFrequencies(const UObject* WorldContextObject, const TArray<float>& Frequencies, TArray<float>& Magnitudes, USoundSubmix* SubmixToAnalyze = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Analysis", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 3))` — Retrieve the magnitudes for the given frequencies.
- L340 _public prototype_ `static void GetPhaseForFrequencies(const UObject* WorldContextObject, const TArray<float>& Frequencies, TArray<float>& Phases, USoundSubmix* SubmixToAnalyze = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Analysis", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 3))` — Retrieve the phases for the given frequencies.
- L344 _public prototype_ `static void AddSourceEffectToPresetChain(const UObject* WorldContextObject, USoundEffectSourcePresetChain* PresetChain, FSourceEffectChainEntry Entry);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Adds source effect entry to preset chain. Only effects the instance of the preset chain
- L348 _public prototype_ `static void RemoveSourceEffectFromPresetChain(const UObject* WorldContextObject, USoundEffectSourcePresetChain* PresetChain, int32 EntryIndex);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Removes source effect entry from preset chain. Only affects the instance of preset chain.
- L352 _public prototype_ `static void SetBypassSourceEffectChainEntry(const UObject* WorldContextObject, USoundEffectSourcePresetChain* PresetChain, int32 EntryIndex, bool bBypassed);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Set whether or not to bypass the effect at the source effect chain index.
- L356 _public prototype_ `static int32 GetNumberOfEntriesInSourceEffectChain(const UObject* WorldContextObject, USoundEffectSourcePresetChain* PresetChain);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Returns the number of effect chain entries in the given source effect chain.
- L360 _public prototype_ `static void PrimeSoundForPlayback(USoundWave* SoundWave, const FOnSoundLoadComplete OnLoadCompletion);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Cache")` — Begin loading a sound into the cache so that it can be played immediately.
- L364 _public prototype_ `static void PrimeSoundCueForPlayback(USoundCue* SoundCue);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Cache")` — Begin loading any sounds referenced by a sound cue into the cache so that it can be played immediately.
- L368 _public prototype_ `static float TrimAudioCache(float InMegabytesToFree);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Cache")` — Trim memory used by the audio cache. Returns the number of megabytes freed.
- L372 _public prototype_ `static void StartAudioBus(const UObject* WorldContextObject, UAudioBus* AudioBus);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Bus", meta = (WorldContext = "WorldContextObject"))` — Starts the given audio bus.
- L376 _public prototype_ `static void StopAudioBus(const UObject* WorldContextObject, UAudioBus* AudioBus);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Bus", meta = (WorldContext = "WorldContextObject"))` — Stops the given audio bus.
- L380 _public prototype_ `static bool IsAudioBusActive(const UObject* WorldContextObject, UAudioBus* AudioBus);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Bus", meta = (WorldContext = "WorldContextObject"))` — Queries if the given audio bus is active (and audio can be mixed to it).
- L384 _public prototype_ `static void RegisterAudioBusToSubmix(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, UAudioBus* AudioBus);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Bus", meta = (WorldContext = "WorldContextObject"))` — Registers an audio bus to a submix so the submix output can be routed to the audiobus.
- L388 _public prototype_ `static void UnregisterAudioBusFromSubmix(const UObject* WorldContextObject, USoundSubmix* SoundSubmix, UAudioBus* AudioBus);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Bus", meta = (WorldContext = "WorldContextObject"))` — Unregisters an audio bus that could have been registered to a submix.
- L395 _public prototype_ `static void GetAvailableAudioOutputDevices(const UObject* WorldContextObject, const FOnAudioOutputDevicesObtained& OnObtainDevicesEvent);` — `UFUNCTION(BlueprintCallable, Category = "Audio", meta = (WorldContext = "WorldContextObject"))` — Gets information about all audio output devices available in the system @param OnObtainDevicesEvent - the event to fire when the audio endpoint devices have been retrieved
- L402 _public prototype_ `static void GetCurrentAudioOutputDeviceName(const UObject* WorldContextObject, const FOnMainAudioOutputDeviceObtained& OnObtainCurrentDeviceEvent);` — `UFUNCTION(BlueprintCallable, Category = "Audio", meta = (WorldContext = "WorldContextObject"))` — Gets information about the currently used audio output device @param OnObtainCurrentDeviceEvent - the event to fire when the audio endpoint devices have been retrieved
- L410 _public prototype_ `static void SwapAudioOutputDevice(const UObject* WorldContextObject, const FString& NewDeviceId, const FOnCompletedDeviceSwap& OnCompletedDeviceSwap);` — `UFUNCTION(BlueprintCallable, Category = "Audio", meta = (WorldContext = "WorldContextObject"))` — Hotswaps to the requested audio output device @param NewDeviceId - the device Id to swap to @param OnCompletedDeviceSwap - the event to fire when the audio endpoint devices have been retrieved

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSoundLoadComplete, const class USoundWave*, LoadedSoundWave, const bool, WasCancelled);` — Called when a load request for a sound has completed.
- L23 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSoundLoadComplete, const class USoundWave*, LoadedSoundWave, const bool, WasCancelled);` — Called when a load request for a sound has completed.
- L54 _prototype_ `FString DataFormatAsString(EAudioMixerStreamDataFormatType type);`
- L83 _function_ `inline const TCHAR* ToString(EAudioMixerChannelType InType)`
- L200 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAudioOutputDevicesObtained, const TArray<FAudioOutputDeviceInfo>&, AvailableDevices);` — Called when a list of all available audio devices is retrieved
- L200 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAudioOutputDevicesObtained, const TArray<FAudioOutputDeviceInfo>&, AvailableDevices);` — Called when a list of all available audio devices is retrieved
- L205 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMainAudioOutputDeviceObtained, const FString&, CurrentDevice);` — Called when a list of all available audio devices is retrieved
- L205 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMainAudioOutputDeviceObtained, const FString&, CurrentDevice);` — Called when a list of all available audio devices is retrieved
- L210 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCompletedDeviceSwap, const FSwapAudioOutputResult&, SwapResult);` — Called when the system has swapped to another audio output device
- L210 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCompletedDeviceSwap, const FSwapAudioOutputResult&, SwapResult);` — Called when the system has swapped to another audio output device

### `Source/Runtime/AudioMixer/Public/AudioMixerBus.h` (Public)


#### struct `Audio::FSendFilterSettings`  
`struct FSendFilterSettings`  
_L23-49_
- desc: Consolidated filter settings for a single bus/submix send. Passed between the game thread and render thread as a simple value type.
- L25 _public member_ `uint8 bEnableLPF : 1 = 0;`
- L26 _public member_ `uint8 bEnableHPF : 1 = 0;`
- L27 _public member_ `float LpfCutoff = 20000.0f;`
- L28 _public member_ `float HpfCutoff = 20.0f;`
- L30 _public prototype_ `FSendFilterSettings() = default;`
- L31 _public function_ `FSendFilterSettings(bool bInEnableLPF, bool bInEnableHPF, float InLpfCutoff, float InHpfCutoff) : LpfCutoff(InLpfCutoff), HpfCutoff(InHpfCutoff)`
- L38 _public function_ `bool IsFiltering() const`
- L42 _public function_ `bool HasChanged(const FSendFilterSettings& Other) const` — Returns true if any filter parameter differs significantly from Other. Use to determine whether a render-thread update is needed.

#### struct `Audio::FAudioBusSend`  
`struct FAudioBusSend`  
_L52-61_
- desc: Struct holding mappings of runtime source ids (bus instances) to bus send level
- L54 _public member_ `int32 SourceId = INDEX_NONE;`
- L55 _public member_ `uint32 WaveInstancePlayOrder = INDEX_NONE;`
- L56 _public member_ `float SendLevel = 0.0f;`
- L58 _public member_ `FSendFilterSettings Filter;`
- L59 _public member_ `FInterpolatedLPF Lpf;`
- L60 _public member_ `FInterpolatedHPF Hpf;`

#### class `Audio::FMixerAudioBus`  
`class FMixerAudioBus : public IAudioMixerRenderStep`  
_L64-190_
- inherits: `IAudioMixerRenderStep`
- desc: Bus instance data. Holds source id bus instances and bus sends data
- L72 _public prototype_ `FMixerAudioBus(FMixerSourceManager* SourceManager, bool bInIsAutomatic, int32 InNumChannels, const FAudioBusKey InBusKey);` — Creates an audio bus. SourceManager		The owning source manager object. bInIsAutomatic	Whether or not this audio bus was created automatically via source buses. InNumChannels	The number of channels of the source bus. InBusKey         The unique key used to identify this bus.
- L74 _public prototype_ `~FMixerAudioBus();`
- L77 _public prototype_ `void AddNewPatchOutput(const FPatchOutputStrongPtr& InPatchOutputStrongPtr);` — Allow anybody to add a pre-existing patch output object to the audio bus
- L80 _public prototype_ `void AddNewPatchInput(const FPatchInput& InPatchInput);` — Allow anybody to write audio into this audio bus from any thread.
- L83 _public prototype_ `void RemovePatchInput(const FPatchInput& InPatchInput);` — Allow anybody to write audio into this audio bus from any thread.
- L88 _private function_ `void SetAutomatic(bool bInIsAutomatic)` — Sets whether or not this audio bus is automatic.
- L91 _private function_ `bool IsAutomatic() const` — Returns if this is a manual audio bus vs automatic
- L94 _private function_ `int32 GetNumChannels() const` — Returns the number of channels of the audio bus
- L97 _private prototype_ `void Update();` — Update the mixer bus after a render block
- L100 _private prototype_ `void AddInstanceId(const int32 InSourceInstanceId, const uint32 WaveInstancePlayOrder, int32 InNumOutputChannels);` — Adds a source id for instances of this bus
- L103 _private prototype_ `bool RemoveInstanceId(const int32 InSourceId, const uint32 WaveInstancePlayOrder);` — Removes the source id from this bus. Returns true if there are no more instances or sends.
- L106 _private prototype_ `void AddSend(EBusSendType BusSendType, const FAudioBusSend& InBusSend);` — Adds a bus send to the bus
- L109 _private prototype_ `bool RemoveSend(EBusSendType BusSendType, const int32 InSourceId);` — Removes the source instance from this bus's send list
- L112 _private prototype_ `const float* GetCurrentBusBuffer() const;` — Gets the current mixed bus buffer
- L115 _private prototype_ `const float* GetPreviousBusBuffer() const;` — Gets the previous mixed bus buffer
- L118 _private prototype_ `void MixBuffer();` — Compute the mixed buffer
- L121 _private prototype_ `void CopyCurrentBuffer(Audio::FAlignedFloatBuffer& InChannelMap, int32 InNumOutputChannels, FAlignedFloatBuffer& OutBuffer, int32 NumOutputFrames) const;` — Copies the current internal buffer to a provided output buffer. Only supports mono or stereo input/output formats.
- L122 _private prototype_ `void CopyCurrentBuffer(int32 InNumOutputChannels, FAlignedFloatBuffer& OutBuffer, int32 NumOutputFrames) const;`
- L125 _private prototype_ `void SetNumOutputChannels(int32 InNumOutputChannels);` — If this bus was constructed before
- L128 _private prototype_ `virtual void DoRenderStep() override;` — IAudioMixerRenderStep interface
- L129 _private prototype_ `virtual const TCHAR* GetRenderStepName() override;`
- L132 _private prototype_ `bool StartEnvelopeFollower(const float InAttackTime, const float InReleaseTime, const float InSampleRate);`
- L133 _private prototype_ `bool StopEnvelopeFollower();`
- L134 _private prototype_ `void ProcessEnvelopeFollower(const float* InBuffer);`
- L141 _private member_ `TArray<int32> InstanceIds;` — Array of instance ids. These are sources which are instances of this. It's possible for this data to have bus sends but no instance ids. This means a source would send its audio to the bus if the bus had an instance. Once and instance plays, it will then start sending its audio to the bus instances.
- L144 _private member_ `TArray<FAudioBusSend> AudioBusSends[(int32)EBusSendType::Count];` — Bus sends to this instance
- L148 _private member_ `FAlignedFloatBuffer MixedSourceData[2];` — The mixed source data. This is double-buffered to allow buses to send audio to themselves. Buses feed audio to each other by storing their previous buffer. Current buses mix in previous other buses (including themselves)
- L152 _private member_ `FAlignedFloatBuffer FilterScratchBuffer;` — Scratch buffer used for intermediate filter output in MixBuffer(). Kept as a member so its heap allocation persists across render callbacks and avoids per-frame reallocation.
- L155 _private member_ `int32 CurrentBufferIndex;` — The index of the bus data currently being rendered
- L158 _private member_ `int32 NumChannels;` — The number of channels of this bus
- L161 _private member_ `int32 NumFrames;` — The number of output frames
- L164 _private member_ `FMixerSourceManager* SourceManager;` — Owning source manager
- L167 _private member_ `Audio::FPatchMixer PatchMixer;` — Multiple places can produce and consume from audio buses
- L168 _private member_ `Audio::FPatchSplitter PatchSplitter;`
- L171 _private member_ `FAudioBusKey BusKey;` — Unique bus identifier
- L174 _private member_ `bool bIsAutomatic;` — Was created manually, not via source buses.
- L177 _private member_ `FString BusName;`
- L181 _private member_ `Audio::FEnvelopeFollower EnvelopeFollower;`
- L182 _private member_ `float EnvelopeValues[AUDIO_MIXER_MAX_OUTPUT_CHANNELS];`
- L183 _private member_ `int32 EnvelopeNumChannels = 0;`
- L184 _private member_ `int32 EnvelopeFollowerRequestsRefCount = 0;`
- L185 _private member_ `bool bIsEnvelopeFollowing = false;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Public/AudioMixerDevice.h` (Public)


#### enum `ERequiredSubmixes`  
`enum class ERequiredSubmixes : uint8`  
_L32-39_
- reflection: `UENUM()`
- L34 _public enumerator_ `Main = 0`
- L35 _public enumerator_ `BaseDefault = 1`
- L36 _public enumerator_ `Reverb = 2`
- L37 _public enumerator_ `EQ = 3`
- L38 _public enumerator_ `Count = 4 UMETA(Hidden)`

#### struct `Audio::FAudioThreadTimingData`  
`struct FAudioThreadTimingData`  
_L58-78_
- desc: Data used to schedule events automatically in the audio renderer in audio mixer.
- L61 _public member_ `double StartTime;` — The time since audio device started.
- L64 _public member_ `double AudioThreadTime;` — The clock of the audio thread, periodically synced to the audio render thread time.
- L67 _public member_ `double AudioRenderThreadTime;` — The clock of the audio render thread.
- L70 _public member_ `double AudioThreadTimeJitterDelta;` — The current audio thread fraction for audio events relative to the render thread.
- L72 _public function_ `FAudioThreadTimingData() : StartTime(0.0) , AudioThreadTime(0.0) , AudioRenderThreadTime(0.0) , AudioThreadTimeJitterDelta(0.05)`

#### struct `Audio::FAudioClockTimingData`  
`struct FAudioClockTimingData`  
_L81-88_
- desc: Data used to interpolate the audio clock in between buffer callbacks
- L84 _public member_ `double UpdateTime = 0.0;` — Time in secods of previous audio clock update
- L87 _public prototype_ `double GetInterpolatedAudioClock(const double InAudioClock, const double InAudioClockDelta) const;` — Interpolates the given clock based on the amount of platform time that has passed since last update

#### enum `Audio::EMasterSubmixType::Type`  
`enum Type`  
_L93-100_
- L95 _public enumerator_ `Master = static_cast<uint8>(ERequiredSubmixes::Main)`
- L96 _public enumerator_ `BaseDefault = static_cast<uint8>(ERequiredSubmixes::BaseDefault)`
- L97 _public enumerator_ `Reverb = static_cast<uint8>(ERequiredSubmixes::Reverb)`
- L98 _public enumerator_ `EQ = static_cast<uint8>(ERequiredSubmixes::EQ)`
- L99 _public enumerator_ `Count = static_cast<uint8>(ERequiredSubmixes::Count)`

#### struct `Audio::FSubmixMap`  
`struct FSubmixMap`  
_L103-120_
- L106 _public typedef_ `using FObjectId = uint32;`
- L107 _public typedef_ `using FPair = TPair<FObjectId, FMixerSubmixPtr>;`
- L108 _public typedef_ `using FIterFunc = TUniqueFunction<void(const FPair&)>;`
- L110 _public prototype_ `void Add(const FObjectId InObjectId, FMixerSubmixPtr InMixerSubmix);`
- L111 _public prototype_ `void Iterate(FIterFunc InFunction);`
- L112 _public prototype_ `FMixerSubmixPtr FindRef(FObjectId InObjectId) const;`
- L113 _public prototype_ `int32 Remove(const FObjectId InObjectId);`
- L114 _public prototype_ `void Reset();`
- L115 _public prototype_ `TSet<FSubmixMap::FObjectId> GetKeys() const;`
- L117 _private member_ `TMap<FObjectId, FMixerSubmixPtr> SubmixMap;`
- L119 _private member_ `mutable FCriticalSection MutationLock;`

#### class `Audio::FMixerDevice`  
`class FMixerDevice : public FAudioDevice, public IAudioMixer, public FGCObject`  
_L123-577_
- inherits: `FAudioDevice,IAudioMixer,FGCObject`
- L128 _public prototype_ `FMixerDevice(IAudioMixerPlatformInterface* InAudioMixerPlatform);`
- L129 _public prototype_ `~FMixerDevice();`
- L132 _public prototype_ `virtual void UpdateDeviceDeltaTime() override;`
- L133 _public prototype_ `virtual void GetAudioDeviceList(TArray<FString>& OutAudioDeviceNames) const override;`
- L134 _public prototype_ `virtual bool InitializeHardware() override;`
- L135 _public prototype_ `virtual void FadeIn() override;`
- L136 _public prototype_ `virtual void FadeOut() override;`
- L137 _public prototype_ `virtual void TeardownHardware() override;`
- L138 _public prototype_ `virtual void UpdateHardwareTiming() override;`
- L139 _public prototype_ `virtual void UpdateGameThread() override;`
- L140 _public prototype_ `virtual void UpdateHardware() override;`
- L141 _public prototype_ `virtual double GetAudioTime() const override;`
- L142 _public prototype_ `virtual double GetInterpolatedAudioClock() const override;`
- L143 _public prototype_ `virtual FAudioEffectsManager* CreateEffectsManager() override;`
- L144 _public prototype_ `virtual FSoundSource* CreateSoundSource() override;`
- L145 _public prototype_ `virtual bool HasCompressedAudioInfoClass(USoundWave* SoundWave) override;`
- L146 _public prototype_ `virtual bool ValidateAPICall(const TCHAR* Function, uint32 ErrorCode) override;`
- L148 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L150 _public prototype_ `virtual void CountBytes(class FArchive& Ar) override;`
- L151 _public prototype_ `virtual bool IsExernalBackgroundSoundActive() override;`
- L152 _public prototype_ `virtual void ResumeContext() override;`
- L153 _public prototype_ `virtual void SuspendContext() override;`
- L154 _public prototype_ `virtual void EnableDebugAudioOutput() override;`
- L155 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;`
- L156 _public prototype_ `virtual void RegisterSoundSubmix(USoundSubmixBase* SoundSubmix, bool bInit = true) override;`
- L157 _public prototype_ `virtual void UnregisterSoundSubmix(const USoundSubmixBase* SoundSubmix, const bool bReparentChildren) override;`
- L159 _public prototype_ `virtual int32 GetNumActiveSources() const override;`
- L162 _public prototype_ `virtual void UpdateSourceEffectChain(const uint32 SourceEffectChainId, const TArray<FSourceEffectChainEntry>& SourceEffectChain, const bool bPlayEffectChainTails) override;` — Updates the source effect chain (using unique object id).
- L163 _public prototype_ `virtual bool GetCurrentSourceEffectChain(const uint32 SourceEffectChainId, TArray<FSourceEffectChainEntry>& OutCurrentSourceEffectChainEntries) override;`
- L166 _public prototype_ `virtual void UpdateSubmixProperties(USoundSubmixBase* InSubmix) override;` — Submix dry/wet settings
- L167 _public prototype_ `virtual void SetSubmixWetDryLevel(USoundSubmix* InSoundSubmix, float InOutputVolume, float InWetLevel, float InDryLevel) override;`
- L168 _public prototype_ `virtual void SetSubmixOutputVolume(USoundSubmix* InSoundSubmix, float InOutputVolume) override;`
- L169 _public prototype_ `virtual void SetSubmixWetLevel(USoundSubmix* InSoundSubmix, float InWetLevel) override;`
- L170 _public prototype_ `virtual void SetSubmixDryLevel(USoundSubmix* InSoundSubmix, float InDryLevel) override;`
- L173 _public prototype_ `virtual void SetSubmixAutoDisable(USoundSubmix* InSoundSubmix, bool bInAutoDisable) override;` — Submix auto-disable setteings
- L174 _public prototype_ `virtual void SetSubmixAutoDisableTime(USoundSubmix* InSoundSubmix, float InDisableTime) override;`
- L177 _public prototype_ `virtual void UpdateSubmixModulationSettings(USoundSubmix* InSoundSubmix, const TSet<TObjectPtr<USoundModulatorBase>>& InOutputModulation, const TSet<TObjectPtr<USoundModulatorBase>>& InWetLevelModulation, const TSet<TObjectPtr<USoundModulatorBase>>& InDryLevelModulation) override;` — Submix Modulation Settings
- L178 _public prototype_ `virtual void SetSubmixModulationBaseLevels(USoundSubmix* InSoundSubmix, float InVolumeModBase, float InWetModBase, float InDryModBase) override;`
- L181 _public prototype_ `virtual void SetSubmixEffectChainOverride(USoundSubmix* InSoundSubmix, const TArray<FSoundEffectSubmixPtr>& InSubmixEffectPresetChain, float InFadeTimeSec) override;` — Submix effect chain override settings
- L182 _public prototype_ `virtual void ClearSubmixEffectChainOverride(USoundSubmix* InSoundSubmix, float InFadeTimeSec) override;`
- L185 _public prototype_ `virtual void StartRecording(USoundSubmix* InSubmix, float ExpectedRecordingDuration) override;` — Submix recording callbacks:
- L186 _public prototype_ `virtual Audio::FAlignedFloatBuffer& StopRecording(USoundSubmix* InSubmix, float& OutNumChannels, float& OutSampleRate) override;`
- L188 _public prototype_ `virtual void PauseRecording(USoundSubmix* InSubmix);`
- L189 _public prototype_ `virtual void ResumeRecording(USoundSubmix* InSubmix);`
- L192 _public prototype_ `virtual void StartEnvelopeFollowing(USoundSubmix* InSubmix) override;` — Submix envelope following
- L193 _public prototype_ `virtual void StopEnvelopeFollowing(USoundSubmix* InSubmix) override;`
- L194 _public prototype_ `virtual void AddEnvelopeFollowerDelegate(USoundSubmix* InSubmix, const FOnSubmixEnvelopeBP& OnSubmixEnvelopeBP) override;`
- L195 _public prototype_ `virtual void RemoveEnvelopeFollowerDelegate(USoundSubmix* InSubmix, const FOnSubmixEnvelopeBP& OnSubmixEnvelopeBP) override;`
- L198 _public prototype_ `virtual void StartSpectrumAnalysis(USoundSubmix* InSubmix, const FSoundSpectrumAnalyzerSettings& InSettings) override;` — Submix Spectrum Analysis
- L199 _public prototype_ `virtual void StopSpectrumAnalysis(USoundSubmix* InSubmix) override;`
- L200 _public prototype_ `virtual void GetMagnitudesForFrequencies(USoundSubmix* InSubmix, const TArray<float>& InFrequencies, TArray<float>& OutMagnitudes) override;`
- L201 _public prototype_ `virtual void GetPhasesForFrequencies(USoundSubmix* InSubmix, const TArray<float>& InFrequencies, TArray<float>& OutPhases) override;`
- L202 _public prototype_ `virtual void AddSpectralAnalysisDelegate(USoundSubmix* InSubmix, const FSoundSpectrumAnalyzerDelegateSettings& InDelegateSettings, const FOnSubmixSpectralAnalysisBP& OnSubmixSpectralAnalysisBP) override;`
- L203 _public prototype_ `virtual void RemoveSpectralAnalysisDelegate(USoundSubmix* InSubmix, const FOnSubmixSpectralAnalysisBP& OnSubmixSpectralAnalysisBP) override;`
- L206 _public prototype_ `virtual void RegisterSubmixBufferListener(TSharedRef<ISubmixBufferListener, ESPMode::ThreadSafe> InSubmixBufferListener, USoundSubmix& InSubmix) override;` — Submix buffer listener callbacks
- L210 _public prototype_ `virtual void UnregisterSubmixBufferListener(TSharedRef<ISubmixBufferListener, ESPMode::ThreadSafe> InSubmixBufferListener, USoundSubmix& InSubmix) override;` — This is optional, and should only be used to manually unregister before the ISubmixBufferListener is getting destroyed (do not call this in the destructor of ISubmixBufferListener or derived classes)
- L212 _public prototype_ `virtual FPatchOutputStrongPtr AddPatchForSubmix(uint32 InObjectId, float InPatchGain) override;`
- L214 _public prototype_ `virtual void FlushExtended(UWorld* WorldToFlush, bool bClearActivatedReverb);`
- L215 _public prototype_ `virtual void FlushAudioRenderingCommands(bool bPumpSynchronously = false, bool bRenderThreadStopped = false) override;`
- L218 _public prototype_ `virtual bool IsNonRealtime() const override;` — Audio Device Properties
- L223 _public prototype_ `virtual bool OnProcessAudioStream(FAlignedFloatBuffer& OutputBuffer) override;`
- L224 _public prototype_ `virtual void OnAudioStreamShutdown() override;`
- L228 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L229 _public function_ `virtual FString GetReferencerName() const override`
- L235 _public prototype_ `FMixerSubmixPtr FindSubmixInstanceByObjectId(uint32 InObjectId);`
- L237 _public prototype_ `FMixerSubmixWeakPtr GetSubmixInstance(const USoundSubmixBase* SoundSubmix) const;`
- L242 _public prototype_ `ISoundfieldFactory* GetFactoryForSubmixInstance(USoundSubmix* SoundSubmix);` — If SoundSubmix is a soundfield submix, this will return the factory used to encode source audio to it's soundfield format. Otherwise, returns nullptr.
- L243 _public prototype_ `ISoundfieldFactory* GetFactoryForSubmixInstance(FMixerSubmixWeakPtr& SoundSubmixPtr);`
- L246 _public prototype_ `void CheckAudioThread() const;` — Functions which check the thread it's called on and helps make sure functions are called from correct threads
- L247 _public prototype_ `void CheckAudioRenderingThread() const;`
- L248 _public prototype_ `bool IsAudioRenderingThread() const;`
- L251 _public prototype_ `FMixerSourceVoice* GetMixerSourceVoice();` — Public Functions
- L252 _public prototype_ `void ReleaseMixerSourceVoice(FMixerSourceVoice* InSourceVoice);`
- L253 _public prototype_ `int32 GetNumSources() const;`
- L256 _public prototype_ `IAudioLinkFactory* GetAudioLinkFactory() const;` — AudioLink
- L258 _public function_ `const FAudioPlatformDeviceInfo& GetPlatformDeviceInfo() const`
- L260 _public function_ `inline int32 GetNumDeviceChannels() const`
- L261 _public function_ `inline int32 GetNumDirectOutChannels() const`
- L263 _public function_ `int32 GetNumOutputFrames() const`
- L265 _public function_ `int32 GetNumOutputBuffers() const`
- L268 _public function_ `IAudioMixerPlatformInterface* GetAudioMixerPlatform() const` — Retrieve a pointer to the currently active platform. Only use this if you know what you are doing. The returned IAudioMixerPlatformInterface will only be alive as long as this FMixerDevice is alive.
- L271 _public prototype_ `void Get3DChannelMap(const int32 InSubmixNumChannels, const FWaveInstance* InWaveInstance, const float EmitterAzimuth, const float NonSpatiliazedFactor, const TMap<EAudioMixerChannel::Type, float>* InOmniMap, float InDefaultOmniValue, Audio::FAlignedFloatBuffer& OutChannelMap);` — Builds a 3D channel map for a spatialized source.
- L274 _public prototype_ `void Get2DChannelMap(bool bIsVorbis, const int32 NumSourceChannels, const bool bIsCenterChannelOnly, Audio::FAlignedFloatBuffer& OutChannelMap) const;` — Builds a channel gain matrix for a non-spatialized source. The non-static variation of this function queries AudioMixerDevice->NumOutputChannels directly which may not be thread safe.
- L275 _public prototype_ `static void Get2DChannelMap(bool bIsVorbis, const int32 NumSourceChannels, const int32 NumOutputChannels, const bool bIsCenterChannelOnly, Audio::FAlignedFloatBuffer& OutChannelMap);`
- L277 _public prototype_ `int32 GetDeviceSampleRate() const;`
- L278 _public prototype_ `int32 GetDeviceOutputChannels() const;`
- L280 _public prototype_ `FMixerSourceManager* GetSourceManager();`
- L281 _public prototype_ `const FMixerSourceManager* GetSourceManager() const;`
- L283 _public prototype_ `virtual USoundSubmix& GetMainSubmixObject() const override;`
- L285 _public prototype_ `FMixerSubmixWeakPtr GetBaseDefaultSubmix();`
- L286 _public prototype_ `FMixerSubmixWeakPtr GetMainSubmix();`
- L287 _public prototype_ `FMixerSubmixWeakPtr GetReverbSubmix();`
- L288 _public prototype_ `FMixerSubmixWeakPtr GetEQSubmix();`
- L291 _public prototype_ `void AddMasterSubmixEffect(FSoundEffectSubmixPtr SoundEffect);` — Renamed Main submix: these functions will be deprecated in a future release
- L292 _public prototype_ `void RemoveMasterSubmixEffect(uint32 SubmixEffectId);`
- L293 _public prototype_ `void ClearMasterSubmixEffects();`
- L294 _public prototype_ `FMixerSubmixWeakPtr GetMasterSubmix();`
- L295 _public prototype_ `FMixerSubmixWeakPtr GetMasterReverbSubmix();`
- L296 _public prototype_ `FMixerSubmixWeakPtr GetMasterEQSubmix();`
- L299 _public prototype_ `void AddMainSubmixEffect(FSoundEffectSubmixPtr SoundEffect);` — Add submix effect to main submix
- L302 _public prototype_ `void RemoveMainSubmixEffect(uint32 SubmixEffectId);` — Remove submix effect from main submix
- L305 _public prototype_ `void ClearMainSubmixEffects();` — Clear all submix effects from main submix
- L308 _public prototype_ `int32 AddSubmixEffect(USoundSubmix* InSoundSubmix, FSoundEffectSubmixPtr SoundEffect);` — Add submix effect to given submix
- L311 _public prototype_ `void RemoveSubmixEffect(USoundSubmix* InSoundSubmix, uint32 SubmixEffectId);` — Remove submix effect to given submix
- L314 _public prototype_ `void RemoveSubmixEffectAtIndex(USoundSubmix* InSoundSubmix, int32 SubmixChainIndex);` — Remove submix effect at the given submix chain index
- L317 _public prototype_ `void ReplaceSoundEffectSubmix(USoundSubmix* InSoundSubmix, int32 InSubmixChainIndex, FSoundEffectSubmixPtr SoundEffect);` — Replace the submix effect of the given submix at the submix chain index with the new submix effect id and submix instance
- L320 _public prototype_ `void ClearSubmixEffects(USoundSubmix* InSoundSubmix);` — Clear all submix effects from given submix
- L323 _public prototype_ `const TArray<EAudioMixerChannel::Type>& GetChannelArray() const;` — Returns the channel array for the given submix channel type
- L326 _public prototype_ `const TArray<FTransform>* GetListenerTransforms();` — Retrieves the listener transforms
- L329 _public prototype_ `const FChannelPositionInfo* GetDefaultChannelPositions() const;` — Retrieves spherical locations of channels for a given submix format
- L332 _public function_ `double GetAudioThreadTime() const` — Audio thread tick timing relative to audio render thread timing
- L333 _public function_ `double GetAudioRenderThreadTime() const`
- L334 _public function_ `double GetAudioClockDelta() const`
- L336 _public function_ `EMonoChannelUpmixMethod GetMonoChannelUpmixMethod() const`
- L338 _public prototype_ `TArray<Audio::FChannelPositionInfo>* GetDefaultPositionMap(int32 NumChannels);`
- L340 _public prototype_ `static bool IsEndpointSubmix(const USoundSubmixBase* InSubmix);`
- L342 _public prototype_ `FPatchOutputStrongPtr MakePatch(int32 InFrames, int32 InChannels, float InGain) const;`
- L345 _public member_ `FQuartzClockManager QuantizedEventClockManager;` — Clock Manager for quantized event handling on Audio Render Thread
- L348 _public member_ `TSharedPtr<FPersistentQuartzSubsystemData, ESPMode::ThreadSafe> QuartzSubsystemData { nullptr };` — Keep a reference alive to UQuartzSubsystem state that needs to persist across level transitions (UWorld destruction
- L353 _public member_ `FCriticalSection QuartzPersistentStateCritSec;` — Technically, in editor, multiple UQuartz(World)Subsystem's will reference the same FMixerDevice object. We need to protect around mutation/access of the "shared" state. (in practice this should be low/zero contention)
- L356 _public prototype_ `void AudioRenderThreadCommand(TFunction<void()> Command);` — Pushes the command to a audio render thread command queue to be executed on render thread
- L359 _public prototype_ `void GameThreadMPSCCommand(TFunction<void()> InCommand);` — Pushes the command to a MPSC queue to be executed on the game thread
- L362 _public prototype_ `void DrawSubmixes(FOutputDevice& InOutput, const TArray<FString>& InArgs) const;` — Debug Commands
- L365 _public prototype_ `void UpdateSubmixDebugVolumes();`
- L368 _public function_ `bool UseRenderScheduler() const`
- L373 _public function_ `FAudioRenderScheduler& GetRenderScheduler() const`
- L382 _protected prototype_ `virtual void InitSoundSubmixes() override;`
- L384 _protected prototype_ `virtual void OnListenerUpdated(const TArray<FListener>& InListeners) override;`
- L386 _protected member_ `TArray<FTransform> ListenerTransforms;`
- L390 _private prototype_ `void ResetAudioRenderingThreadId();` — Resets the thread ID used for audio rendering
- L392 _private prototype_ `void RebuildSubmixLinks(const USoundSubmixBase& SoundSubmix, FMixerSubmixPtr& SubmixInstance);`
- L394 _private prototype_ `void InitializeChannelMaps();`
- L395 _private prototype_ `static int32 GetChannelMapCacheId(const int32 NumSourceChannels, const int32 NumOutputChannels, const bool bIsCenterChannelOnly);`
- L396 _private prototype_ `void CacheChannelMap(const int32 NumSourceChannels, const int32 NumOutputChannels, const bool bIsCenterChannelOnly);`
- L397 _private prototype_ `void InitializeChannelAzimuthMap(const int32 NumChannels);`
- L399 _private prototype_ `void WhiteNoiseTest(FAlignedFloatBuffer& Output);`
- L400 _private prototype_ `void SineOscTest(FAlignedFloatBuffer& Output);`
- L402 _private prototype_ `bool IsMainAudioDevice() const;`
- L404 _private prototype_ `void LoadRequiredSubmix(ERequiredSubmixes InType, const FString& InDefaultName, bool bInDefaultMuteWhenBackgrounded, FSoftObjectPath& InOutObjectPath);`
- L405 _private prototype_ `void LoadPluginSoundSubmixes();`
- L406 _private prototype_ `void LoadSoundSubmix(USoundSubmixBase& SoundSubmix);`
- L408 _private prototype_ `void InitSoundfieldAndEndpointDataForSubmix(const USoundSubmixBase& InSoundSubmix, FMixerSubmixPtr MixerSubmix, bool bAllowReInit);`
- L410 _private prototype_ `void UnloadSoundSubmix(const USoundSubmixBase& SoundSubmix, const bool bReparentChildren);`
- L412 _private prototype_ `bool IsRequiredSubmixType(const USoundSubmixBase* InSubmix) const;`
- L413 _private prototype_ `FMixerSubmixPtr GetRequiredSubmixInstance(uint32 InSubmixId) const;`
- L414 _private prototype_ `FMixerSubmixPtr GetRequiredSubmixInstance(const USoundSubmixBase* InSubmix) const;`
- L417 _private prototype_ `void PumpCommandQueue();` — Pumps the audio render thread command queue
- L418 _private prototype_ `void PumpGameThreadCommandQueue();`
- L421 _private prototype_ `void UpdateAudioClock();` — Updates the audio clock and the associated timing data
- L424 _private prototype_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L425 _private prototype_ `void OnTraceStopped(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination);`
- L427 _private prototype_ `void InitializeMainSubmixTruePeakEnvelopeFollower(int32 InSampleRate, int32 InNumChannels, int32 InNumSamples);`
- L428 _private prototype_ `void InitializeMainSubmixLKFSAnalyzer(int32 InSampleRate, int32 InNumChannels);`
- L430 _private prototype_ `void SendMainSubmixLoadedMessage();`
- L431 _private prototype_ `void SendMainSubmixAlivePingMessage();`
- L433 _private prototype_ `void UpdateAndSendMainSubmixTruePeakMaxValueMessage(const FAlignedFloatBuffer& InMainSubmixAudioBuffer);`
- L434 _private prototype_ `void UpdateAndSendMainSubmixLKFSValuesMessage(const FAlignedFloatBuffer& InMainSubmixAudioBuffer);`
- L436 _private prototype_ `void SendSubmixesAlivePing();`
- L437 _private prototype_ `void UpdateSubmixesAlivePingTime();`
- L438 _private prototype_ `void SendSubmixesSendLevelTraceMessages();`
- L440 _private prototype_ `void RegisterSubmixEnvelopeFollowerCVars();`
- L441 _private prototype_ `void UnregisterSubmixEnvelopeFollowerCVars();`
- L443 _private prototype_ `void OnStartSubmixEnvelopeFollowerCVarChanged(IConsoleVariable* InStartSubmixEnvelopeFollowerCVar);`
- L444 _private prototype_ `void OnStopSubmixEnvelopeFollowerCVarChanged(IConsoleVariable* InStopSubmixEnvelopeFollowerCVar);`
- L446 _private prototype_ `void StartSubmixEnvelopeFollowing(const FMixerSubmixPtr& InSubmix);`
- L447 _private prototype_ `void StopSubmixEnvelopeFollowing(const FMixerSubmixPtr& InSubmix);`
- L449 _private prototype_ `void AutomaticallyStartSubmixEnvelopeFollowers();`
- L451 _private prototype_ `void RegisterResetMainSubmixAnalyzersCmd();`
- L452 _private prototype_ `void UnregisterResetMainSubmixAnalyzersCmd();`
- L454 _private prototype_ `void OnResetMainSubmixAnalyzersCmdInvoked();`
- L456 _private prototype_ `void ResetMainSubmixAnalyzers();`
- L459 _private member_ `TArray<USoundSubmix*> RequiredSubmixes;`
- L460 _private member_ `TArray<FMixerSubmixPtr> RequiredSubmixInstances;`
- L462 _private member_ `TArray<TStrongObjectPtr<UAudioBus>> DefaultAudioBuses;`
- L464 _private member_ `IAudioMixerPlatformInterface* AudioMixerPlatform;` — Ptr to the platform interface, which handles streaming audio to the hardware device.
- L467 _private member_ `FChannelPositionInfo DefaultChannelAzimuthPositions[EAudioMixerChannel::MaxSupportedChannel];` — Contains a map of channel/speaker azimuth positions.
- L470 _private member_ `TArray<FChannelPositionInfo> DeviceChannelAzimuthPositions;` — The azimuth positions for submix channel types.
- L472 _private member_ `int32 DeviceOutputChannels;`
- L475 _private member_ `EMonoChannelUpmixMethod MonoChannelUpmixMethod;` — What upmix method to use for mono channel upmixing.
- L478 _private member_ `EPanningMethod PanningMethod;` — What panning method to use for panning.
- L481 _private member_ `FAudioMixerOpenStreamParams OpenStreamParams;` — The audio output stream parameters used to initialize the audio hardware.
- L484 _private member_ `double AudioClockDelta;` — The time delta for each callback block.
- L487 _private member_ `FAudioClockTimingData AudioClockTimingData;` — The timing data used to interpolate the audio clock
- L490 _private member_ `float PreviousPrimaryVolume;` — What the previous master volume was.
- L493 _private member_ `FAudioThreadTimingData AudioThreadTimingData;` — Timing data for audio thread.
- L496 _private member_ `FAudioPlatformDeviceInfo PlatformInfo;` — The platform device info for this mixer device.
- L499 _private member_ `FSubmixMap Submixes;` — Map of USoundSubmix static data objects to the dynamic audio mixer submix.
- L503 _private member_ `TArray<FMixerSubmixPtr> DefaultEndpointSubmixes;` — Submixes that will sum their audio and send it directly to AudioMixerPlatform. Submixes are added to this list in RegisterSoundSubmix, and removed in UnregisterSoundSubmix.
- L507 _private member_ `TArray<FMixerSubmixPtr> ExternalEndpointSubmixes;` — Submixes that need to be processed, but will be sending their audio to external sends. Submixes are added to this list in RegisterSoundSubmix and removed in UnregisterSoundSubmix.
- L510 _private member_ `FCriticalSection EndpointSubmixesMutationLock;` — Contended between RegisterSoundSubmix/UnregisterSoundSubmix on the audio thread and OnProcessAudioStream on the audio mixer thread.
- L513 _private member_ `TMap<FString, TMap<FString, TSharedRef<ISubmixBufferListener, ESPMode::ThreadSafe>>> PendingSubmixBufferListeners;` — Submix Buffer Listeners which are trying to listen to submixes which have not been registered yet
- L516 _private member_ `TArray<USoundSubmix*> DelegateBoundSubmixes;` — Which submixes have been told to envelope follow with this audio device.
- L519 _private member_ `TSpscQueue<FMixerSourceVoice*> SourceVoices;` — Queue of mixer source voices.
- L521 _private member_ `TMap<uint32, TArray<FSourceEffectChainEntry>> SourceEffectChainOverrides;`
- L524 _private member_ `TUniquePtr<FAudioRenderScheduler> RenderScheduler;` — Scheduler responsible for launching rendering tasks
- L525 _private member_ `bool bUseRenderScheduler = true;`
- L528 _private member_ `TUniquePtr<FMixerSourceManager> SourceManager;` — The mixer source manager. Should be cleaned up before the scheduler so dependencies can be removed correctly.
- L531 _private member_ `mutable int32 GameOrAudioThreadId;` — ThreadId for the game thread (or if audio is running a separate thread, that ID)
- L534 _private member_ `mutable std::atomic<int32> AudioPlatformThreadId;` — ThreadId for the low-level platform audio mixer.
- L537 _private member_ `TMpscQueue<TFunction<void()>> CommandQueue;` — Command queue to send commands to audio render thread from game thread or audio thread.
- L540 _private member_ `TMpscQueue<TFunction<void()>> GameThreadCommandQueue;` — MPSC command queue to send commands to the game thread
- L542 _private member_ `IAudioLinkFactory* AudioLinkFactory = nullptr;`
- L545 _private member_ `TSet<uint32> SubmixesWithAutoEnvelopeFollowers;`
- L546 _private member_ `TSet<FString> SubmixesWithCVarEnvelopeFollowers;`
- L548 _private member_ `IConsoleVariable* StartSubmixEnvelopeFollowerCVar = nullptr;`
- L549 _private member_ `IConsoleVariable* StopSubmixEnvelopeFollowerCVar = nullptr;`
- L550 _private member_ `IConsoleObject* ResetMainSubmixAnalyzersCmd = nullptr;`
- L552 _private member_ `TUniquePtr<FEnvelopeFollower> MainSubmixTruePeakEnvelopeFollower;`
- L553 _private member_ `FAlignedFloatBuffer MainSubmixTruePeakOutputEnvelope;`
- L555 _private member_ `TUniquePtr<FLKFSAnalyzer> MainSubmixLKFSAnalyzer;`
- L557 _private member_ `double SubmixesAlivePingTimeSec = 0.0;`
- L558 _private member_ `static constexpr double SubmixesAlivePingWaitTimeSec = 1.0;`
- L562 _private member_ `bool bDebugOutputEnabled;` — Whether or not we generate output audio to test multi-platform mixer.
- L565 _private member_ `bool bSubmixRegistrationDisabled;` — Whether or not initialization of the submix system is underway and submixes can be registered
- L570 _public prototype_ `static void CreateSynchronizedAudioTaskQueue(AudioTaskQueueId QueueId);` — `UE_DEPRECATED(5.8, "Synchronized audio task queues are deprecated.")`
- L573 _public prototype_ `static void DestroySynchronizedAudioTaskQueue(AudioTaskQueueId QueueId, bool RunCurrentQueue = false);` — `UE_DEPRECATED(5.8, "Synchronized audio task queues are deprecated.")`
- L576 _public prototype_ `static int KickQueuedTasks(AudioTaskQueueId QueueId);` — `UE_DEPRECATED(5.8, "Synchronized audio task queues are deprecated.")`

#### Free symbols / members of external scopes

- L42 _namespace_ `namespace Audio`
- L44 _externvar_ `extern int32 GRemoveSubmixesFromRoot;` (scope `Audio`)
- L54 _typedef_ `typedef TSharedPtr<FMixerSubmix, ESPMode::ThreadSafe> FMixerSubmixPtr;` (scope `Audio`)
- L55 _typedef_ `typedef TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> FMixerSubmixWeakPtr;` (scope `Audio`)
- L91 _namespace_ `namespace EMasterSubmixType` (scope `Audio`)

### `Source/Runtime/AudioMixer/Public/AudioMixerModule.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/AudioMixer/Public/AudioMixerSubmix.h` (Public)


#### enum `Audio::EMixerSourceSubmixSendStage`  
`enum EMixerSourceSubmixSendStage`  
_L65-72_
- L68 _public enumerator_ `PostDistanceAttenuation` — Whether to do the send pre distance attenuation
- L71 _public enumerator_ `PreDistanceAttenuation` — Whether to do the send post distance attenuation

#### struct `Audio::FSubmixVoiceData`  
`struct FSubmixVoiceData`  
_L74-84_
- L76 _public member_ `float SendLevel;`
- L77 _public member_ `EMixerSourceSubmixSendStage SubmixSendStage;`
- L79 _public function_ `FSubmixVoiceData() : SendLevel(1.0f) , SubmixSendStage(EMixerSourceSubmixSendStage::PostDistanceAttenuation)`

#### struct `Audio::FChildSubmixInfo`  
`struct FChildSubmixInfo`  
_L88-110_
- L90 _public member_ `TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> SubmixPtr;`
- L93 _public member_ `TUniquePtr<ISoundfieldEncoderStream> Encoder;` — If the child submix is not a soundfield submix, we may need to encode its audio output in ProcessAudio.
- L96 _public member_ `TUniquePtr<ISoundfieldTranscodeStream> Transcoder;` — If this child submix is a soundfield submix that we can read the output of, we may need to transcode it's audio output.
- L99 _public member_ `TUniquePtr<ISoundfieldAudioPacket> IncomingPacketToTranscode;` — This is filled by either the Encoder or the Transcoder, and passed to this submix' mixer.
- L101 _public function_ `FChildSubmixInfo()`
- L104 _public function_ `FChildSubmixInfo(TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> SubmixWeakPtr) : SubmixPtr(SubmixWeakPtr)`

#### class `Audio::FMixerSubmix`  
`class FMixerSubmix`  
_L112-731_
- L115 _public prototype_ `FMixerSubmix(FMixerDevice* InMixerDevice);`
- L116 _public prototype_ `virtual ~FMixerSubmix();`
- L119 _public prototype_ `void Init(const USoundSubmixBase* InSoundSubmix, bool bAllowReInit = true);` — Initialize the submix object with the USoundSubmix ptr. Sets up child and parent connects.
- L122 _public function_ `uint32 GetId() const` — Returns the mixer submix Id
- L125 _public function_ `const FString& GetName() const` — Return the owners name
- L129 _public function_ `const FString& GetPathName() const` — Return the owners path name
- L133 _public prototype_ `void SetParentSubmix(TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> Submix);` — Sets the parent submix to the given submix
- L136 _public prototype_ `void AddChildSubmix(TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> Submix);` — Adds the given submix to this submix's children
- L139 _public prototype_ `void RemoveChildSubmix(TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> SubmixWeakPtr);` — Removes the given submix from this submix's children
- L142 _public prototype_ `void RegisterAudioBus(const Audio::FAudioBusKey& InAudioBusKey, Audio::FPatchInput&& InPatchInput);` — Registers the given audiobus to this submix
- L145 _public prototype_ `void UnregisterAudioBus(const Audio::FAudioBusKey& InAudioBusKey);` — Unregisters a registered audiobus from this submix (if any)
- L148 _public prototype_ `void UpdateDebugVolume();` — Updates the cached debug volume from the audio debugger (must be called on the AudioThread)
- L151 _public function_ `float GetDebugVolume() const` — Returns the cached debug volume for this submix (0.0 if muted/soloed out, 1.0 otherwise)
- L154 _public prototype_ `void SetOutputVolume(float InOutputLevel);` — Sets the output level of the submix in linear gain
- L157 _public prototype_ `void SetDryLevel(float InDryLevel);` — Sets the static output volume of the submix in linear gain
- L160 _public prototype_ `void SetWetLevel(float InWetLevel);` — Sets the wet level of the submix in linear gain
- L163 _public prototype_ `void UpdateModulationSettings(const TSet<TObjectPtr<USoundModulatorBase>>& InOutputModulators, const TSet<TObjectPtr<USoundModulatorBase>>& InWetLevelModulators, const TSet<TObjectPtr<USoundModulatorBase>>& InDryLevelModulators);` — Update modulation settings of the submix
- L166 _public prototype_ `void SetModulationBaseLevels(float InVolumeModBaseDb, float InWetModeBaseDb, float InDryModBaseDb);` — Update modulation settings of the submix with Decibel values
- L169 _public prototype_ `float GetOutputVolumeModulationValueThreadSafe() const;` — Returns the cached output volume modulation value
- L172 _public prototype_ `float GetWetVolumeModulationValueThreadSafe() const;` — Returns the cached wet level modulation value
- L175 _public prototype_ `int32 GetSubmixChannels() const;` — Gets the submix channels channels
- L178 _public prototype_ `TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> GetParentSubmix();` — Gets this submix's parent submix
- L181 _public prototype_ `int32 GetNumSourceVoices() const;` — Returns the number of source voices currently a part of this submix.
- L184 _public prototype_ `int32 GetNumEffects() const;` — Returns the number of wet effects in this submix.
- L187 _public prototype_ `int32 GetSizeOfSubmixChain() const;` — Returns the size of the submix chain.
- L190 _public prototype_ `void AddOrSetSourceVoice(FMixerSourceVoice* InSourceVoice, const float SendLevel, EMixerSourceSubmixSendStage InSubmixSendStage);` — `UE_DEPRECATED(5.8, "Use FMixerSubmix::AddOrSetSourceById instead.")`
- L193 _public prototype_ `void AddOrSetSourceById(const int32 InSourceId, const float SendLevel, EMixerSourceSubmixSendStage InSubmixSendStage);` — Add (if not already added) or sets the amount of the source voice's send amount
- L195 _public prototype_ `FPatchOutputStrongPtr AddPatch(float InGain);`
- L198 _public prototype_ `void RemoveSourceVoice(FMixerSourceVoice* InSourceVoice);` — `UE_DEPRECATED(5.8, "Use FMixerSubmix::RemoveSourceById instead.")`
- L201 _public prototype_ `void RemoveSourceById(const int32 InSourceId);` — Removes the given source voice from the submix.
- L204 _public prototype_ `void AddSoundEffectSubmix(FSoundEffectSubmixPtr InSoundEffectSubmix);` — Appends the effect submix to the effect submix chain.
- L207 _public prototype_ `void RemoveSoundEffectSubmix(uint32 SubmixPresetId);` — Removes the submix effect from the effect submix chain.
- L210 _public prototype_ `void RemoveSoundEffectSubmixAtIndex(int32 InIndex);` — Removes the submix effect from the effect submix chain at the given submix index.
- L213 _public prototype_ `void ClearSoundEffectSubmixes();` — Clears all submix effects from the effect submix chain.
- L216 _public prototype_ `void SetSubmixEffectChainOverride(const TArray<FSoundEffectSubmixPtr>& InSubmixEffectPresetChain, float InFadeTimeSec);` — Sets a submix effect chain override with the given fade time in seconds.
- L219 _public prototype_ `void ClearSubmixEffectChainOverride(float InFadeTimeSec);` — Clears any submix effect chain overrides in the given fade time in seconds.
- L222 _public prototype_ `void ReplaceSoundEffectSubmix(int32 InIndex, FSoundEffectSubmixPtr InEffectInstance);` — Swaps effect for provided submix at the given index.  Fails if effect at index doesn't exist
- L225 _public prototype_ `void SetBackgroundMuted(bool bInMuted);` — Whether or not this submix instance is muted.
- L230 _public prototype_ `bool IsOwnerValid() const;` — Checks to see if submix is valid.  Submix can be considered invalid if the OwningSubmix pointer is stale.
- L233 _public prototype_ `bool IsValid() const;` — `UE_DEPRECATED(5.8, "Use IsOwnerValid() instead, to avoid confusion with TSharedPtr::IsValid().")`
- L236 _public prototype_ `void ProcessAudio(FAlignedFloatBuffer& OutAudio);` — Function which processes audio.
- L237 _public prototype_ `void ProcessAudio(ISoundfieldAudioPacket& OutputAudio);`
- L239 _public prototype_ `void SendAudioToSubmixBufferListeners(FAlignedFloatBuffer& OutAudioBuffer);`
- L243 _public prototype_ `void ProcessAudioAndSendToEndpoint();` — This should be called if this submix doesn't send it's audio to a parent submix, but rather an external endpoint.
- L246 _public prototype_ `int32 GetSampleRate() const;` — Returns the device sample rate this submix is rendering to
- L249 _public prototype_ `int32 GetNumOutputChannels() const;` — Returns the output channels this submix is rendering to
- L252 _public prototype_ `int32 GetNumChainEffects();` — Returns the number of effects in this submix's effect chain
- L255 _public prototype_ `FSoundEffectSubmixPtr GetSubmixEffect(const int32 InIndex);` — Returns the submix effect at the given effect chain index
- L258 _public prototype_ `void SetSoundfieldFactory(ISoundfieldFactory* InSoundfieldFactory);` — This must be called on the entire submix graph before calling SetupSoundfieldStreams.
- L261 _public prototype_ `void SetupSoundfieldStreams(const USoundfieldEncodingSettingsBase* SoundfieldSettings, TArray<USoundfieldEffectBase*>& Processors, ISoundfieldFactory* InSoundfieldFactory);` — updates settings, potentially creating or removing ambisonics streams based on what types of submixes this submix is connected to.
- L262 _public prototype_ `void TeardownSoundfieldStreams();`
- L264 _public prototype_ `void SetupEndpoint(IAudioEndpointFactory* InFactory, const UAudioEndpointSettingsBase* InSettings);`
- L265 _public prototype_ `void SetupEndpoint(ISoundfieldEndpointFactory* InFactory, const USoundfieldEndpointSettingsBase* InSettings);`
- L267 _public prototype_ `void UpdateEndpointSettings(TUniquePtr<IAudioEndpointSettingsProxy>&& InSettings);`
- L268 _public prototype_ `void UpdateEndpointSettings(TUniquePtr<ISoundfieldEndpointSettingsProxy>&& InSettings);`
- L271 _public prototype_ `void OnStartRecordingOutput(float ExpectedDuration);` — This is called by the corresponding USoundSubmix when StartRecordingOutput is called.
- L274 _public prototype_ `FAlignedFloatBuffer& OnStopRecordingOutput(float& OutNumChannels, float& OutSampleRate);` — This is called by the corresponding USoundSubmix when StopRecordingOutput is called.
- L277 _public prototype_ `void PauseRecordingOutput();` — This is called by the corresponding USoundSubmix when PauseRecording is called.
- L280 _public prototype_ `void ResumeRecordingOutput();` — This is called by the corresponding USoundSubmix when ResumeRecording is called.
- L283 _public prototype_ `void RegisterBufferListener(TSharedRef<ISubmixBufferListener, ESPMode::ThreadSafe> BufferListener);` — Register buffer listener with this submix
- L286 _public prototype_ `void UnregisterBufferListener(TSharedRef<ISubmixBufferListener, ESPMode::ThreadSafe> BufferListener);` — Unregister buffer listener with this submix
- L289 _public prototype_ `void StartEnvelopeFollowing(int32 AttackTime, int32 ReleaseTime);` — Starts envelope following with the given attack time and release time
- L292 _public prototype_ `void StopEnvelopeFollowing();` — Stops envelope following the submix
- L295 _public prototype_ `void AddEnvelopeFollowerDelegate(const FOnSubmixEnvelopeBP& OnSubmixEnvelopeBP);` — Adds an envelope follower delegate
- L298 _public prototype_ `void RemoveEnvelopeFollowerDelegate(const FOnSubmixEnvelopeBP& OnSubmixEnvelopeBP);` — Removes an existing envelope follower delegate
- L301 _public prototype_ `void StartSpectrumAnalysis(const FSoundSpectrumAnalyzerSettings& InSettings);` — Initializes a new FFT analyzer for this submix and immediately begins feeding audio to it.
- L304 _public prototype_ `void StopSpectrumAnalysis();` — Terminates whatever FFT Analyzer is being used for this submix.
- L307 _public prototype_ `void AddSpectralAnalysisDelegate(const FSoundSpectrumAnalyzerDelegateSettings& InDelegateSettings, const FOnSubmixSpectralAnalysisBP& OnSubmixSpectralAnalysisBP);` — Adds an spectral analysis delegate
- L310 _public prototype_ `void RemoveSpectralAnalysisDelegate(const FOnSubmixSpectralAnalysisBP& OnSubmixSpectralAnalysisBP);` — Removes an existing spectral analysis delegate
- L314 _public prototype_ `void GetMagnitudeForFrequencies(const TArray<float>& InFrequencies, TArray<float>& OutMagnitudes);` — Gets the most recent magnitude values for each corresponding value in InFrequencies (in Hz). This requires StartSpectrumAnalysis to be called first.
- L318 _public prototype_ `void GetPhaseForFrequencies(const TArray<float>& InFrequencies, TArray<float>& OutPhases);` — Gets the most recent phase values for each corresponding value in InFrequencies (in Hz). This requires StartSpectrumAnalysis to be called first.
- L321 _public prototype_ `void BroadcastDelegates();` — Broadcast the envelope and submix delegates on the game thread
- L324 _public prototype_ `bool IsSoundfieldSubmix() const;` — returns true if this submix is encoded to a soundfield.
- L327 _public prototype_ `bool IsDefaultEndpointSubmix() const;` — returns true if this submix sends it's audio to the default endpoint.
- L330 _public prototype_ `bool IsExternalEndpointSubmix() const;` — Returns true if this submix sends its audio to an IAudioEndpoint.
- L333 _public prototype_ `bool IsSoundfieldEndpointSubmix() const;` — returns true if this submix sends its audio to an ISoundfieldEndpoint.
- L336 _public prototype_ `bool IsDummyEndpointSubmix() const;` — Returns true if this is an endpoint type that should no-op for this platform
- L339 _public prototype_ `bool IsRenderingAudio() const;` — Returns true if the submix is currently rendering audio. The current rendering time is passed in.
- L342 _public prototype_ `void SetAutoDisable(bool bInAutoDisable);` — Set whether or not this submix is told to auto disable.
- L345 _public prototype_ `void SetAutoDisableTime(float InAutoDisableTime);` — Sets the auto-disable time
- L349 _public prototype_ `FSoundfieldEncodingKey GetKeyForSubmixEncoding();` — Get a unique key for this submix's format and settings. If another submix has an identical format and settings it will have an equivalent key.
- L351 _public prototype_ `ISoundfieldFactory* GetSoundfieldFactory();`
- L353 _public prototype_ `ISoundfieldEncodingSettingsProxy& GetSoundfieldSettings();`
- L355 _public prototype_ `FAudioPluginInitializationParams GetInitializationParamsForSoundfieldStream();`
- L357 _public prototype_ `FSoundfieldSpeakerPositionalData GetDefaultPositionalDataForAudioDevice();`
- L359 _public function_ `TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> GetParent() const`
- L360 _public function_ `const TMap<uint32, FChildSubmixInfo>& GetChildren() const`
- L364 _protected prototype_ `void InitInternal();` — Initialize the submix internal
- L367 _protected prototype_ `static void DownmixBuffer(const int32 InChannels, const FAlignedFloatBuffer& InBuffer, const int32 OutChannels, FAlignedFloatBuffer& OutNewBuffer);` — Down mix the given buffer to the desired down mix channel count
- L369 _protected prototype_ `void MixBufferDownToMono(const FAlignedFloatBuffer& InBuffer, int32 NumInputChannels, FAlignedFloatBuffer& OutBuffer);`
- L371 _protected prototype_ `void SetupSoundfieldEncodersForChildren();`
- L372 _protected prototype_ `void SetupSoundfieldEncodingForChild(FChildSubmixInfo& InChild);`
- L375 _protected prototype_ `void SetupSoundfieldStreamForParent();` — Check to see if we need to decode from ambisonics for parent
- L378 _protected prototype_ `void SetUpSoundfieldPositionalData(const TSharedPtr<Audio::FMixerSubmix, ESPMode::ThreadSafe>& InParentSubmix);` — This sets up the ambisonics positional data for speakers, based on what new format we need to convert to.
- L381 _protected prototype_ `void MixInSource(const ISoundfieldAudioPacket& InAudio, const ISoundfieldEncodingSettingsProxy& InSettings, ISoundfieldAudioPacket& PacketToSumTo);` — Encode a source and sum it into the mixed soundfield.
- L383 _protected prototype_ `void UpdateListenerRotation(const FQuat& InRotation);`
- L386 _protected prototype_ `void MixInChildSubmix(FChildSubmixInfo& Child, ISoundfieldAudioPacket& PacketToSumTo);` — Calls ProcessAudio on the child submix, performs all necessary conversions and mixes in it's resulting audio.
- L388 _protected prototype_ `FName GetSoundfieldFormat() const;`
- L390 _protected prototype_ `TUniquePtr<ISoundfieldTranscodeStream> GetTranscoderForChildSubmix(const TSharedPtr<Audio::FMixerSubmix, ESPMode::ThreadSafe>& InChildSubmix);`
- L400 _protected prototype_ `void PumpCommandQueue();` — Pump command queue
- L403 _protected prototype_ `void SubmixCommand(TFunction<void()> Command);` — Add command to the command queue
- L406 _protected prototype_ `bool GenerateEffectChainAudio(FSoundEffectSubmixInputData& InputData, const FAlignedFloatBuffer& InAudioBuffer, TArray<FSoundEffectSubmixPtr>& InEffectChain, FAlignedFloatBuffer& OutBuffer);` — Generates audio from the given effect chain into the given buffer
- L409 _protected prototype_ `void TraceSubmixEnvelopeValues(int32 InNumChannels, float InOutputVolume);`
- L413 _protected member_ `FString SubmixName;` — The name of this submix (the owning USoundSubmix) (at top so we can see in debugger it's name)
- L417 _protected member_ `FString SubmixPathName;` — The path name of this submix (the owning USoundSubmix)
- L421 _protected member_ `uint32 Id;` — This mixer submix's Id
- L424 _protected member_ `TWeakPtr<FMixerSubmix, ESPMode::ThreadSafe> ParentSubmix;` — Parent submix.
- L427 _protected member_ `TMap<uint32, FChildSubmixInfo> ChildSubmixes;` — Child submixes
- L444 _protected member_ `TArray<FSubmixEffectFadeInfo> EffectChains;` — The array of submix effect overrides. There may be more than one if multiple are fading out. There should be only one fading in (the current override).
- L445 _protected member_ `FAlignedFloatBuffer EffectChainOutputBuffer;`
- L448 _protected member_ `FMixerDevice* MixerDevice;` — Owning mixer device.
- L451 _protected member_ `TMap<int32, FSubmixVoiceData> MixerSourceIds;` — Map of mixer source voices identified by SourceId with a given send level for this submix
- L453 _protected member_ `FAlignedFloatBuffer ScratchBuffer;`
- L454 _protected member_ `FAlignedFloatBuffer SubmixChainMixBuffer;`
- L455 _protected member_ `FAlignedFloatBuffer FilterScratchBuffer;`
- L456 _protected member_ `FAlignedFloatBuffer InputBuffer;`
- L457 _protected member_ `FAlignedFloatBuffer DownmixedBuffer;`
- L458 _protected member_ `FAlignedFloatBuffer SourceInputBuffer;`
- L460 _protected member_ `int32 NumChannels;`
- L461 _protected member_ `int32 NumSamples;`
- L534 _protected member_ `FSoundfieldStreams SoundfieldStreams;`
- L579 _protected member_ `FEndpointData EndpointData;`
- L581 _protected member_ `float CurrentOutputVolume;`
- L582 _protected member_ `float TargetOutputVolume;`
- L583 _protected member_ `float CurrentWetLevel;`
- L584 _protected member_ `float TargetWetLevel;`
- L585 _protected member_ `float CurrentDryLevel;`
- L586 _protected member_ `float TargetDryLevel;`
- L588 _protected member_ `FModulationDestination VolumeMod;`
- L589 _protected member_ `FModulationDestination DryLevelMod;`
- L590 _protected member_ `FModulationDestination WetLevelMod;`
- L592 _protected member_ `std::atomic<float> CachedVolumeModValue { 1.0f };`
- L593 _protected member_ `std::atomic<float> CachedWetLevelModValue { 1.0f };`
- L595 _protected member_ `float VolumeModBaseDb = 0.f;`
- L596 _protected member_ `float DryModBaseDb = MIN_VOLUME_DECIBELS;`
- L597 _protected member_ `float WetModBaseDb = 0.f;`
- L600 _protected member_ `float VolumeModifier = 1.f;` — modifiers set from BP code
- L601 _protected member_ `float DryLevelModifier = 1.f;`
- L602 _protected member_ `float WetLevelModifier = 1.f;`
- L605 _protected member_ `std::atomic<float> DebugVolume { 1.f };` — Debug mute/solo volume
- L608 _protected member_ `float EnvelopeValues[AUDIO_MIXER_MAX_OUTPUT_CHANNELS];` — Envelope following data
- L609 _protected member_ `Audio::FEnvelopeFollower EnvelopeFollower;`
- L610 _protected member_ `int32 EnvelopeNumChannels;`
- L611 _protected member_ `FCriticalSection EnvelopeCriticalSection;`
- L614 _protected member_ `FCriticalSection SpectrumAnalyzerCriticalSection;` — Spectrum analyzer. Created and destroyed on the audio thread.
- L615 _protected member_ `FSoundSpectrumAnalyzerSettings SpectrumAnalyzerSettings;`
- L616 _protected member_ `TSharedPtr<FAsyncSpectrumAnalyzer, ESPMode::ThreadSafe> SpectrumAnalyzer;`
- L619 _protected member_ `FAlignedFloatBuffer MonoMixBuffer;` — This buffer is used to downmix the submix output to mono before submitting it to the SpectrumAnalyzer.
- L622 _protected member_ `FAlignedFloatBuffer DryChannelBuffer;` — The dry channel buffer
- L625 _protected member_ `TQueue<TFunction<void()>> CommandQueue;` — Submix command queue to shuffle commands from audio thread to audio render thread.
- L629 _protected member_ `mutable TArray<TWeakPtr<ISubmixBufferListener>> BufferListenerPtrs;`
- L631 _protected member_ `mutable FCriticalSection BufferListenerCriticalSection;` — Critical section used for modifying and interacting with buffer listeners
- L634 _protected member_ `FAlignedFloatBuffer RecordingData;` — This buffer is used for recorded output of the submix.
- L637 _protected member_ `int32 NumSubmixEffects;` — Returns the number of submix effects
- L640 _protected member_ `uint8 bIsRecording : 1;` — Bool set to true when this submix is recording data.
- L643 _protected member_ `uint8 bIsBackgroundMuted : 1;` — Whether or not this submix is muted.
- L646 _protected member_ `uint8 bAutoDisable : 1;` — Whether or not auto-disablement is enabled. If true, the submix will disable itself.
- L649 _protected member_ `uint8 bIsSilent : 1;` — Whether or not the submix is currently rendering audio. I.e. audio was sent to it and mixing it, or any of its child submixes are rendering audio.
- L652 _protected member_ `uint8 bIsCurrentlyDisabled : 1;` — Whether or not we're currently disabled (i.e. the submix has been silent)
- L655 _protected member_ `double AutoDisableTime;` — The time to wait to disable the submix if the auto-disablement is active.
- L658 _protected member_ `double SilenceTimeStartSeconds;` — The time that the first full silent buffer was detected in the submix. Submix will auto-disable if the timeout is reached and the submix has bAutoDisable set to true.
- L661 _protected member_ `FThreadSafeBool bIsEnvelopeFollowing;` — Bool set to true when envelope following is enabled
- L664 _protected member_ `FThreadSafeCounter EnvelopeFollowerRequestsRefCount = 0;` — Ref count for the number of times a request for submixes to start envelope following
- L667 _protected member_ `FOnSubmixEnvelope OnSubmixEnvelope;` — Multi-cast delegate to broadcast envelope data from this submix instance
- L701 _protected member_ `TArray<FSpectrumAnalysisDelegateInfo> SpectralAnalysisDelegates;`
- L704 _protected member_ `FThreadSafeBool bIsSpectrumAnalyzing;` — Bool set to true when spectrum analysis is enabled
- L707 _protected member_ `FCriticalSection RecordingCriticalSection;` — Critical section used for when we are appending recorded data.
- L710 _protected member_ `FCriticalSection EffectChainMutationCriticalSection;` — Critical section for mutation of the effect chain.
- L713 _protected member_ `TWeakObjectPtr<const USoundSubmixBase> OwningSubmixObject;` — Handle back to the owning USoundSubmix. Used when the device is shutdown to prematurely end a recording.
- L715 _protected member_ `Audio::FPatchSplitter PatchSplitter;`
- L717 _protected member_ `TUniquePtr<IAudioLink> AudioLinkInstance;`
- L722 _private prototype_ `void SendAudioToRegisteredAudioBuses(FAlignedFloatBuffer& OutAudioBuffer);`
- L724 _private prototype_ `void UnregisterBufferListenerInternal(UPTRINT ListenerBufferPtr);`
- L726 _private prototype_ `void PruneSubmixBufferListeners();`
- L729 _private member_ `TMap<Audio::FAudioBusKey, Audio::FPatchInput> AudioBuses;` — Registered audio buses
- L730 _private member_ `FAlignedFloatBuffer AudioBusSendBuffer;`

#### struct `Audio::FMixerSubmix::FSubmixBufferListenerInfo`  
`struct FSubmixBufferListenerInfo`  
_L393-397_
- L395 _public member_ `ISubmixBufferListener* Listener = nullptr;`
- L396 _public member_ `FString Descriptor;`

#### struct `Audio::FMixerSubmix::FSubmixEffectFadeInfo`  
`struct FSubmixEffectFadeInfo`  
_L430-441_
- desc: Struct to hold record keeping data about effect chain overrides
- L432 _public member_ `TArray<FSoundEffectSubmixPtr> EffectChain;`
- L434 _public member_ `FDynamicParameter FadeVolume = FDynamicParameter(1.0f);`
- L437 _public member_ `bool bIsCurrentChain = false;` — If true, this effect override will be fading in or all the way faded in
- L440 _public member_ `bool bIsBaseEffect = false;` — If this effect fade info is the base effect

#### struct `Audio::FMixerSubmix::FSoundfieldEffectProcessorData`  
`struct FSoundfieldEffectProcessorData`  
_L466-489_
- desc: Individual processor in our
- L468 _public member_ `TUniquePtr<ISoundfieldEffectSettingsProxy> Settings;`
- L469 _public member_ `TUniquePtr<ISoundfieldEffectInstance> Processor;`
- L471 _public function_ `FSoundfieldEffectProcessorData(ISoundfieldFactory* InFactory, ISoundfieldEncodingSettingsProxy& InSettings, USoundfieldEffectBase* InProcessorBase)`

#### struct `Audio::FMixerSubmix::FSoundfieldStreams`  
`struct FSoundfieldStreams`  
_L491-532_
- L493 _public member_ `ISoundfieldFactory* Factory;`
- L498 _public member_ `TUniquePtr<ISoundfieldEncoderStream> DownmixedChildrenEncoder;` — This encoder is used for the mixed down audio from all non-soundfield submixes plugged into this submix. Will not be set up if ISoundfieldFactory::ShouldEncodeAllStreamsIndependently returns true.
- L501 _public member_ `TUniquePtr<ISoundfieldDecoderStream> ParentDecoder;` — Encoder used if a normal submix outputs to this submix.
- L504 _public member_ `FSoundfieldSpeakerPositionalData CachedPositionalData;` — This is the positional data we are decoding
- L507 _public member_ `TUniquePtr<ISoundfieldMixerStream> Mixer;` — Mixes all encoded child submix inputs.
- L510 _public member_ `TUniquePtr<ISoundfieldAudioPacket> MixedDownAudio;` — This is the packet we mix all input sources and child submixes to.
- L513 _public member_ `TUniquePtr<ISoundfieldEncodingSettingsProxy> Settings;` — Current settings for this submix.
- L516 _public member_ `TArray<FSoundfieldEffectProcessorData> EffectProcessors;` — All soundfield processors attached to this submix.
- L519 _public member_ `FCriticalSection StreamsLock;` — This critical section is contended by the soundfield overload of ProcessAudio and SetupSoundfieldStreams.
- L521 _public function_ `FSoundfieldStreams() : Factory(nullptr)`
- L525 _public function_ `void Reset()`

#### struct `Audio::FMixerSubmix::FEndpointData`  
`struct FEndpointData`  
_L536-577_
- L540 _public member_ `Audio::FPatchInput Input;` — For endpoint submixes, this is the primary method of pushing audio to the endpoint.
- L542 _public member_ `TUniquePtr<IAudioEndpoint> NonSoundfieldEndpoint;`
- L543 _public member_ `TUniquePtr<ISoundfieldEndpoint> SoundfieldEndpoint;`
- L546 _public member_ `FAlignedFloatBuffer AudioBuffer;` — for non-soundfield endpoints, we use these buffers for processing.
- L547 _public member_ `FAlignedFloatBuffer ResampledAudioBuffer;`
- L548 _public member_ `FAlignedFloatBuffer DownmixedResampledAudioBuffer;`
- L549 _public member_ `FAlignedFloatBuffer DownmixChannelMap;`
- L552 _public member_ `int32 NumChannels;` — Number of channels and sample rate for the external endpoint.
- L553 _public member_ `float SampleRate;`
- L556 _public member_ `Audio::FResampler Resampler;` — This is used if the endpoint has a different sample rate than our audio engine.
- L557 _public member_ `bool bShouldResample;`
- L560 _public member_ `TUniquePtr<ISoundfieldAudioPacket> AudioPacket;` — for soundfield endpoints, this is the buffer we use to send audio to the endpoint.
- L562 _public function_ `FEndpointData() : NumChannels(0) , SampleRate(0.0f) , bShouldResample(false)`
- L568 _public function_ `void Reset()`

#### struct `Audio::FMixerSubmix::FSpectralAnalysisBandInfo`  
`struct FSpectralAnalysisBandInfo`  
_L669-672_
- L671 _public member_ `FInlineEnvelopeFollower EnvelopeFollower;`

#### struct `Audio::FMixerSubmix::FSpectrumAnalysisDelegateInfo`  
`struct FSpectrumAnalysisDelegateInfo`  
_L674-699_
- L676 _public member_ `FSoundSpectrumAnalyzerDelegateSettings DelegateSettings;`
- L678 _public member_ `FOnSubmixSpectralAnalysis OnSubmixSpectralAnalysis;`
- L680 _public member_ `TUniquePtr<ISpectrumBandExtractor> SpectrumBandExtractor;`
- L681 _public member_ `TArray<FSpectralAnalysisBandInfo> SpectralBands;`
- L683 _public member_ `float LastUpdateTime = -1.0f;`
- L684 _public member_ `float UpdateDelta = 0.0f;`
- L686 _public function_ `FSpectrumAnalysisDelegateInfo()`
- L690 _public function_ `FSpectrumAnalysisDelegateInfo(FSpectrumAnalysisDelegateInfo&& Other)`
- L698 _public prototype_ `~FSpectrumAnalysisDelegateInfo() = default;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Graph"), STAT_AudioMixerSubmixes, STATGROUP_AudioMixer, AUDI` — The time it takes to process the submix graph. Process submix effects, mix into the submix buffer, etc.
- L29 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Graph Endpoint"), STAT_AudioMixerEndpointSubmixes, STATGROUP_AudioMi` — The time it takes to process the endpoint submixes.
- L32 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Graph Child Processing"), STAT_AudioMixerSubmixChildren, STATGROUP` — The time it takes to process the submix graph. Process submix effects, mix into the submix buffer, etc.
- L35 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Graph Source Mixing"), STAT_AudioMixerSubmixSource, STATGROUP_Au` — The time it takes to process the submix graph. Process submix effects, mix into the submix buffer, etc.
- L38 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Graph Effect Processing"), STAT_AudioMixerSubmixEffectProcessing, STATGROU` — The time it takes to process the submix graph. Process submix effects, mix into the submix buffer, etc.
- L44 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Soundfield Children"), STAT_AudioMixerSubmixSoundfieldChildren, STATGROUP_Au` — The time it takes to process the submix soundfield child submixes.
- L47 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Soundfield Sources"), STAT_AudioMixerSubmixSoundfieldSources, STATGROUP_Aud` — The time it takes to process the submix soundfield sources.
- L50 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Submix Soundfield Processors"), STAT_AudioMixerSubmixSoundfieldProcessors, STATGROUP_` — The time it takes to process the submix soundfield processors..
- L59 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Public/AudioRenderSchedulerTester.h` (Public)


#### class `IAudioRenderSchedulerTester`  
`class IAudioRenderSchedulerTester`  
_L11-28_
- desc: A simple test harness for the scheduler. Numbered steps and dependencies between them can be added and the order the steps were run in is returned.
- L14 _public prototype_ `static TUniquePtr<IAudioRenderSchedulerTester> Create();`
- L16 _public prototype_ `virtual ~IAudioRenderSchedulerTester() = default;`
- L19 _public prototype_ `virtual void AddStep(int Step) = 0;` — Add a numbered step to the scheduler.
- L22 _public prototype_ `virtual void AddDependency(int FirstStep, int SecondStep) = 0;` — Automatically creates the steps if they don't exist yet.
- L24 _public prototype_ `virtual void RemoveDependency(int FirstStep, int SecondStep) = 0;`
- L27 _public prototype_ `virtual TArray<int> Run() = 0;` — Runs the scheduler, and returns the order steps were executed in.

### `Source/Runtime/AudioMixer/Public/Components/SynthComponent.h` (Public)


#### class `IAudioBufferListener`  
`class IAudioBufferListener`  
_L25-29_
- desc: Simple interface class to allow objects to route audio between them.
- L28 _public prototype_ `virtual void OnGeneratedBuffer(const float* AudioBuffer, const int32 NumSamples, const int32 NumChannels) = 0;`

#### class `USynthSound`  
`class USynthSound : public USoundWaveProcedural`  
_L45-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundWaveProcedural`
- L49 _private prototype_ `void Init(USynthComponent* InSynthComponent, const int32 InNumChannels, const int32 SampleRate, const int32 InCallbackSize);`
- L50 _private prototype_ `void StartOnAudioDevice(FAudioDevice* InAudioDevice);`
- L53 _private prototype_ `virtual void OnBeginGenerate() override;` — Begin USoundWave
- L54 _private prototype_ `virtual int32 OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples) override;`
- L55 _private prototype_ `virtual void OnEndGenerate() override;`
- L56 _private prototype_ `virtual Audio::EAudioMixerStreamDataFormat::Type GetGeneratedPCMDataFormat() const override;`
- L57 _private prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L62 _protected member_ `TWeakObjectPtr<USynthComponent> OwningSynthComponent = nullptr;` — `UPROPERTY()`
- L64 _protected member_ `TArray<float> FloatBuffer;`
- L67 _public function_ `USynthComponent* GetOwningSynthComponent()`
- L72 _public function_ `TWeakObjectPtr<USynthComponent>& GetOwningSynthComponentPtr()`

#### class `USynthComponent`  
`class USynthComponent : public USceneComponent`  
_L79-397_
- reflection: `UCLASS(abstract, ClassGroup = Synth, hidecategories = (Object, ActorComponent, Physics, Rendering, Mobility, LOD), MinimalAPI)`
- inherits: `USceneComponent`
- L84 _public prototype_ `USynthComponent(const FObjectInitializer& ObjectInitializer);`
- L87 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L88 _public prototype_ `virtual void Deactivate() override;`
- L92 _public prototype_ `virtual void OnRegister() override;`
- L93 _public prototype_ `virtual void OnUnregister() override;`
- L94 _public prototype_ `virtual bool IsReadyForOwnerToAutoDestroy() const override;`
- L95 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type Reason) override;`
- L100 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L104 _public prototype_ `virtual void PostLoad() override;`
- L107 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L112 _public prototype_ `void Start();` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Starts the synth generating audio.
- L116 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Stops the synth generating audio.
- L120 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Returns true if this component is currently playing.
- L124 _public prototype_ `void SetVolumeMultiplier(float VolumeMultiplier);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Set a new volume multiplier
- L128 _public prototype_ `void SetSubmixSend(USoundSubmixBase* Submix, float SendLevel);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets how much audio the sound should send to the given submix.
- L132 _public prototype_ `void SetSourceBusSendPreEffect(USoundSourceBus* SoundSourceBus, float SourceBusSendLevel);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets how much audio the sound should send to the given SourceBus (pre effect).
- L136 _public prototype_ `void SetSourceBusSendPostEffect(USoundSourceBus* SoundSourceBus, float SourceBusSendLevel);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets how much audio the sound should send to the given SourceBus (post effect).
- L140 _public prototype_ `void SetAudioBusSendPreEffect(UAudioBus* AudioBus, float AudioBusSendLevel);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets how much audio the sound should send to the given AudioBus (pre effect).
- L144 _public prototype_ `void SetAudioBusSendPostEffect(UAudioBus* AudioBus, float AudioBusSendLevel);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets how much audio the sound should send to the given AudioBus (post effect).
- L148 _public prototype_ `void SetLowPassFilterEnabled(bool InLowPassFilterEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets whether or not the low pass filter is enabled on the audio component.
- L152 _public prototype_ `virtual void SetLowPassFilterFrequency(float InLowPassFilterFrequency);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets lowpass filter frequency of the audio component.
- L156 _public prototype_ `void SetOutputToBusOnly(bool bInOutputToBusOnly);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — Sets whether or not the synth component outputs its audio to any source or audio buses.
- L167 _public prototype_ `void FadeIn(float FadeInDuration, float FadeVolumeLevel = 1.0f, float StartTime = 0.0f, const EAudioFaderCurve FadeCurve = EAudioFaderCurve::Linear) const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — This function allows designers to call Play on an Audio Component instance while applying a volume curve over time. Parameters allow designers to indicate the duration of the fade, the curve shape, and the start time if seeking into the sound. @param FadeInDuration How long it should take to reach the FadeVolumeLevel @param FadeVolumeLevel The percentage of the AudioComponents's calculated volume to fade to @param FadeCurve The curve to use when interpolating between the old and new volume
- L178 _public prototype_ `void FadeOut(float FadeOutDuration, float FadeVolumeLevel, const EAudioFaderCurve FadeCurve = EAudioFaderCurve::Linear) const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — This function allows designers to call a delayed Stop on an Audio Component instance while applying a volume curve over time. Parameters allow designers to indicate the duration of the fade and the curve shape. @param FadeOutDuration how long it should take to reach the FadeVolumeLevel @param FadeVolumeLevel the percentage of the AudioComponents's calculated volume in which to fade to @param FadeCurve The curve to use when interpolating between the old and new volume
- L186 _public prototype_ `void AdjustVolume(float AdjustVolumeDuration, float AdjustVolumeLevel, const EAudioFaderCurve FadeCurve = EAudioFaderCurve::Linear) const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio")` — This function allows designers to trigger an adjustment to the sound instance’s playback Volume with options for smoothly applying a curve over time. @param AdjustVolumeDuration The length of time in which to interpolate between the initial volume and the new volume. @param AdjustVolumeLevel The new volume to set the Audio Component to. @param FadeCurve The curve used when interpolating between the old and new volume.
- L195 _public prototype_ `void SetModulationRouting(const TSet<USoundModulatorBase*>& Modulators, const EModulationDestination Destination, const EModulationRouting RoutingMethod = EModulationRouting::Inherit);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Components|Audio", DisplayName = "Set Modulation Routing")` — Sets the routing for one of the given Synth component's Modulation Destinations. @param Modulators The set of modulators to apply to the given destination on the component. @param Destination The destination to assign the modulators to. @param RoutingMethod The routing method to use for the given modulator.
- L203 _public prototype_ `UPARAM(DisplayName = "Modulators") TSet<USoundModulatorBase*> GetModulators(const EModulationDestination Des` — `UFUNCTION(BlueprintPure, Category = "Audio|Components|Audio", DisplayName = "Get Modulators")` — Gets the set of currently active modulators for a given Modulation Destination. @param Destination The Destination to retrieve the Modulators from. @return The set of of Modulators applied to this component for the given Destination.
- L207 _public member_ `uint8 bAutoDestroy : 1;` — `UPROPERTY()` — Auto destroy this component on completion
- L211 _public member_ `uint8 bStopWhenOwnerDestroyed : 1;` — `UPROPERTY()` — Stop sound when owner is destroyed
- L215 _public member_ `uint8 bAllowSpatialization : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation)` — Is this audio component allowed to be spatialized?
- L219 _public member_ `uint8 bOverrideAttenuation : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation)` — Should the Attenuation Settings asset be used (false) or should the properties set directly on the component be used for attenuation properties
- L224 _public member_ `uint32 bOutputToBusOnly_DEPRECATED : 1;` — `UPROPERTY()` — Whether or not to only send this audio's output to a bus. If true, this sound will not be audible except through bus sends.
- L229 _public member_ `uint32 bEnableBusSends : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)` — Whether or not to enable sending this audio's output to buses.
- L233 _public member_ `uint32 bEnableBaseSubmix : 1;` — `UPROPERTY(EditAnywhere, Category = Effects)` — If enabled, sound will route to the Master Submix by default or to the Base Submix if defined. If disabled, sound will route ONLY to the Submix Sends and/or Bus Sends
- L237 _public member_ `uint32 bEnableSubmixSends : 1;` — `UPROPERTY(EditAnywhere, Category = Effects, meta = (DisplayAfter = "SoundSubmixObject"))` — Whether or not to enable Submix Sends other than the Base Submix.
- L241 _public member_ `TObjectPtr<class USoundAttenuation> AttenuationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation, meta = (EditCondition = "!bOverrideAttenuation"))` — If bOverrideSettings is false, the asset to use to determine attenuation properties for sounds generated by this component
- L245 _public member_ `struct FSoundAttenuationSettings AttenuationOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation, meta = (EditCondition = "bOverrideAttenuation"))` — If bOverrideSettings is true, the attenuation properties to use for sounds generated by this component
- L249 _public member_ `TObjectPtr<USoundConcurrency> ConcurrencySettings_DEPRECATED;` — `UPROPERTY()` — What sound concurrency to use for sounds generated by this audio component
- L253 _public member_ `TSet<TObjectPtr<USoundConcurrency>> ConcurrencySet;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Concurrency)` — What sound concurrency to use for sounds generated by this audio component
- L256 _public member_ `FSoundModulationDefaultRoutingSettings ModulationRouting;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modulation)`
- L260 _public member_ `TObjectPtr<USoundClass> SoundClass;` — `UPROPERTY(EditAnywhere, Category = SoundClass)` — Sound class this sound belongs to
- L264 _public member_ `TObjectPtr<USoundEffectSourcePresetChain> SourceEffectChain;` — `UPROPERTY(EditAnywhere, Category = Effects)` — The source effect chain to use for this sound.
- L268 _public member_ `TObjectPtr<USoundSubmixBase> SoundSubmix;` — `UPROPERTY(EditAnywhere, Category = Effects, meta = (EditCondition = "bEnableBaseSubmix", DisplayName = "Base Submix"))` — Submix this sound belongs to
- L272 _public member_ `TArray<FSoundSubmixSendInfo> SoundSubmixSends;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects, meta = (EditCondition = "bEnableSubmixSends"))` — An array of submix sends. Audio from this sound will send a portion of its audio to these effects.
- L276 _public member_ `TArray<FSoundSourceBusSendInfo> BusSends;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects, meta = (DisplayName = "Post-Effect Bus Sends", EditCondition = "bEnableBusSends"))` — This sound will send its audio output to this list of buses if there are bus instances playing after source effects are processed.
- L280 _public member_ `TArray<FSoundSourceBusSendInfo> PreEffectBusSends;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects, meta = (DisplayName = "Pre-Effect Bus Sends", EditCondition = "bEnableBusSends"))` — This sound will send its audio output to this list of buses if there are bus instances playing before source effects are processed.
- L284 _public member_ `uint8 bIsUISound : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)` — Whether or not this sound plays when the game is paused in the UI
- L288 _public member_ `uint8 bIsPreviewSound : 1;` — `UPROPERTY()` — Whether or not this synth is playing as a preview sound
- L291 _public member_ `uint8 bAlwaysPlay : 1;` — Whether to artificially prioritize the component to play
- L296 _public prototype_ `void Initialize(int32 SampleRateOverride = INDEX_NONE);` — Call if creating this synth component not via an actor component in BP, but in code or some other location. Optionally override the sample rate of the sound wave, otherwise it uses the audio device's sample rate.
- L301 _public prototype_ `void CreateAudioComponent();` — Creates the audio component if it hasn't already been created yet. This should only be used when trying to assign explicit settings to the AudioComponent before calling Start().
- L304 _public prototype_ `UAudioComponent* GetAudioComponent();` — Retrieves this synth component's audio component.
- L310 _public member_ `int32 EnvelopeFollowerAttackTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, meta = (ClampMin = "0", UIMin = "0"))` — The attack time in milliseconds for the envelope follower. Delegate callbacks can be registered to get the envelope value of sounds played with this audio component. Only used in audio mixer.
- L316 _public member_ `int32 EnvelopeFollowerReleaseTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, meta = (ClampMin = "0", UIMin = "0"))` — The release time in milliseconds for the envelope follower. Delegate callbacks can be registered to get the envelope value of sounds played with this audio component. Only used in audio mixer.
- L319 _public member_ `FOnSynthEnvelopeValue OnAudioEnvelopeValue;` — `UPROPERTY(BlueprintAssignable)`
- L322 _public member_ `FOnSynthEnvelopeValueNative OnAudioEnvelopeValueNative;` — Shadow delegate for non UObject subscribers
- L324 _public prototype_ `void OnAudioComponentEnvelopeValue(const UAudioComponent* AudioComponent, const USoundWave* SoundWave, const float EnvelopeValue);`
- L327 _public prototype_ `void AddAudioBufferListener(IAudioBufferListener* InAudioBufferListener);` — Adds and removes audio buffer listener
- L328 _public prototype_ `void RemoveAudioBufferListener(IAudioBufferListener* InAudioBufferListener);`
- L330 _public prototype_ `virtual USoundClass* GetSoundClass();`
- L332 _public prototype_ `virtual void BeginDestroy() override;`
- L337 _protected prototype_ `void SynthCommand(TFunction<void()> Command);` — Method to execute parameter changes on game thread in audio render thread
- L340 _protected function_ `virtual bool Init(int32& SampleRate)` — Called when synth is created.
- L343 _protected function_ `virtual void OnBeginGenerate()` — Called when the synth component begins generating audio in render thread
- L346 _protected function_ `virtual void OnEndGenerate()` — Called when the synth has finished generating audio on the render thread
- L350 _protected function_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples)` — Called when more audio is needed to be generated This method of generating audio is soon to be deprecated. For all new synth components, create an FSoundGenerator instance and implement CreateSoundGenerator method to create an instance.
- L354 _protected function_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams)` — Implemented by the synth component to create a generator object instead of generating audio directly on the synth component. This method prevents UObjects from having to exist in the audio render thread.
- L358 _protected prototype_ `int32 OnGeneratePCMAudio(float* GeneratedPCMData, int32 NumSamples);` — Called by procedural sound wave Returns the number of samples actually generated
- L361 _protected prototype_ `FAudioDevice* GetAudioDevice() const;` — Gets the audio device associated with this synth component
- L364 _protected member_ `int32 NumChannels;` — Can be set by the derived class, defaults to 2
- L367 _protected member_ `int32 PreferredBufferLength;` — Can be set by the derived class- sets the preferred callback size for the synth component.
- L371 _private prototype_ `ISoundGeneratorPtr CreateSoundGeneratorInternal(const FSoundGeneratorInitParams& InParams);` — Creates the synth component's sound generator, calls into overridden client code to create the instance.
- L374 _private member_ `TObjectPtr<USynthSound> Synth;` — `UPROPERTY(Transient)`
- L377 _private member_ `TObjectPtr<UAudioComponent> AudioComponent;` — `UPROPERTY(Transient)`
- L379 _private prototype_ `void PumpPendingMessages();`
- L382 _private member_ `Audio::FSineOsc TestSineLeft;`
- L383 _private member_ `Audio::FSineOsc TestSineRight;`
- L387 _private member_ `bool bIsSynthPlaying;` — Whether or not synth is playing
- L388 _private member_ `bool bIsInitialized;`
- L390 _private member_ `TQueue<TFunction<void()>> CommandQueue;`
- L394 _private member_ `ISoundGeneratorPtr SoundGenerator;` — Synth component's handle to its sound generator instance. used to forward BP functions to the instance directly.

#### Free symbols / members of external scopes

- L15 _macro_ `#define SYNTH_GENERATOR_TEST_TONE 0`
- L38 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSynthEnvelopeValue, const float, EnvelopeValue);` — Called by a synth component and returns the sound's envelope value (using an envelope follower in the audio renderer). This only works in the audio mixer.
- L38 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSynthEnvelopeValue, const float, EnvelopeValue);` — Called by a synth component and returns the sound's envelope value (using an envelope follower in the audio renderer). This only works in the audio mixer.
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSynthEnvelopeValueNative, const class UAudioComponent*, const float);` — shadow delegate declaration for above
- L41 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSynthEnvelopeValueNative, const class UAudioComponent*, const float);` — shadow delegate declaration for above

### `Source/Runtime/AudioMixer/Public/FileDecoder.h` (Public)


#### class `FAudioFileReader`  
`class FAudioFileReader`  
_L12-42_
- L19 _public prototype_ `FAudioFileReader(const FString& InPath);` — Constructor. Takes a file path and immediately loads info. Optionally, CallbackSize can be used to indicate the size of chunks that will be popped off of this instance. When set to 0, the entire file is decompressed into memory.
- L22 _public prototype_ `void GetFileInfo(FSoundQualityInfo& OutInfo);` — Returns file information.
- L24 _public prototype_ `bool PopAudio(float* OutAudio, int32 NumSamples);`
- L27 _private prototype_ `FAudioFileReader();`
- L30 _private member_ `TUniquePtr<IFileHandle> FileHandle;` — Handle back to the file this was constructed with.
- L33 _private member_ `TUniquePtr<ICompressedAudioInfo> Decompressor;` — Actual decompressor in question.
- L35 _private member_ `TArray<uint8> CompressedFile;`
- L36 _private member_ `TArray<Audio::DefaultUSoundWaveSampleType> DecompressionBuffer;`
- L38 _private member_ `FSoundQualityInfo QualityInfo;`
- L40 _private prototype_ `ICompressedAudioInfo* GetNewDecompressorForFile(const FString& InPath);`

### `Source/Runtime/AudioMixer/Public/IAudioMixerGeneratorSource.h` (Public)


#### class `Audio::IAudioMixerGeneratorSource`  
`class IAudioMixerGeneratorSource`  
_L10-19_
- L13 _public prototype_ `virtual ~IAudioMixerGeneratorSource() = default;`
- L15 _public prototype_ `virtual void Play() = 0;`
- L16 _public prototype_ `virtual void Stop() = 0;`
- L18 _public prototype_ `virtual bool IsDone() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Public/Quartz/AudioMixerClock.h` (Public)


#### class `Audio::FQuartzClockProxy`  
`class FQuartzClockProxy`  
_L49-92_
- desc: FQuartzClockProxy: This class is a C++ handle to the underlying clock. It is mostly a wrapper around a TWeakPtr<FQuartzClock> and FQuartzClockCommandQueueType The getters query the underlying FQuartzClock directly, which returns values updated during the last audio-engine tick If you need to add more getters, add copies of the members in question to FQuartzClock::FQuartzClockState and update FQuartzClock::UpdateCachedState() for thread-safe access (or manually protect access w/ CachedClockStateCritSec) SendCommandToClock() can be used to execute lambdas at the beginning of the next clock tick.  These lambdas can call FQuartzClock's public methods safely. Your lambda will take an FQuartzClock* as an argument, which will be passed in by the FQuartzClock itself when it pumps the command queue.
- L53 _public function_ `FQuartzClockProxy()` — ctor
- L54 _public function_ `FQuartzClockProxy(const FName& Name) : ClockId(Name)` — conv ctor from FName
- L55 _public prototype_ `FQuartzClockProxy(TSharedPtr<FQuartzClock, ESPMode::ThreadSafe> InClock);`
- L57 _public function_ `FName GetClockName() const`
- L59 _public prototype_ `bool IsValid() const;`
- L60 _public function_ `operator bool() const`
- L62 _public function_ `bool operator==(const FName& Name) const`
- L64 _public prototype_ `bool DoesClockExist() const;`
- L66 _public prototype_ `bool IsClockRunning() const;`
- L68 _public prototype_ `Audio::FQuartzClockTickRate GetTickRate() const;`
- L70 _public prototype_ `float GetEstimatedClockRunTimeSeconds() const;`
- L72 _public prototype_ `FQuartzTransportTimeStamp GetCurrentClockTimestamp() const;`
- L74 _public prototype_ `float GetDurationOfQuantizationTypeInSeconds(const EQuartzCommandQuantization& QuantizationType, float Multiplier) const;`
- L76 _public prototype_ `float GetBeatProgressPercent(const EQuartzCommandQuantization& QuantizationType) const;`
- L79 _public prototype_ `bool SendCommandToClock(TFunction<void(FQuartzClock*)> InCommand);` — returns false if the clock is not valid or has shut down
- L82 _public function_ `operator const FName&() const` — implicit cast to underlying ID (FName)
- L85 _private member_ `FName ClockId;`
- L87 _private member_ `FQuartzClockCommandQueueWeakPtr SharedQueue;`
- L90 _protected member_ `TWeakPtr<FQuartzClock, ESPMode::ThreadSafe> ClockWeakPtr;`

#### class `Audio::FQuartzClock`  
`class FQuartzClock : public FQuartzClockCommandQueueType::TConsumerBase<Audio::Quartz::IQuartzClock>`  
_L110-265_
- inherits: `FQuartzClockCommandQueueType::TConsumerBase<Audio::Quartz::IQuartzClock>`
- L115 _public prototype_ `FQuartzClock(const FName& InName, const FQuartzClockSettings& InClockSettings, FQuartzClockManager* InOwningClockManagerPtr = nullptr);` — ctor
- L122 _public prototype_ `void ChangeTickRate(FQuartzClockTickRate InNewTickRate, int32 NumFramesLeft = 0);` — Transport Control: alter the tick rate (take by-value to make sample-rate adjustments in-place)
- L124 _public prototype_ `void ChangeTimeSignature(const FQuartzTimeSignature& InNewTimeSignature);`
- L126 _public prototype_ `virtual void Resume() override;`
- L128 _public prototype_ `virtual void Pause() override;`
- L130 _public prototype_ `virtual void Restart(bool bPause = true) override;`
- L132 _public prototype_ `virtual void Stop(bool CancelPendingEvents) override;` — Pause + Restart
- L134 _public prototype_ `void SetSampleRate(float InNewSampleRate);`
- L136 _public prototype_ `void ResetTransport(const int32 NumFramesToTickBeforeReset = 0);`
- L139 _public prototype_ `void AddToTickDelay(int32 NumFramesOfDelayToAdd);` — (used for StartOtherClock command to handle the sub-tick as the target clock)
- L142 _public prototype_ `void SetTickDelay(int32 NumFramesOfDelay);` — (used for StartOtherClock command to handle the sub-tick as the target clock)
- L144 _public prototype_ `void Shutdown();`
- L147 _public prototype_ `FQuartzClockTickRate GetTickRate();` — Getters:
- L149 _public prototype_ `FName GetName() const;`
- L151 _public prototype_ `bool IgnoresFlush() const;`
- L153 _public prototype_ `bool DoesMatchSettings(const FQuartzClockSettings& InClockSettings) const;`
- L155 _public prototype_ `bool HasPendingEvents() const;`
- L157 _public prototype_ `int32 NumPendingEvents() const;`
- L159 _public prototype_ `bool IsRunning() const;`
- L161 _public prototype_ `float GetDurationOfQuantizationTypeInSeconds(const EQuartzCommandQuantization& QuantizationType, float Multiplier);`
- L163 _public prototype_ `float GetBeatProgressPercent(const EQuartzCommandQuantization& QuantizationType) const;`
- L165 _public prototype_ `FQuartzTransportTimeStamp GetCurrentTimestamp();`
- L167 _public prototype_ `float GetEstimatedRunTime();`
- L169 _public prototype_ `FMixerDevice* GetMixerDevice();`
- L171 _public prototype_ `FMixerSourceManager* GetSourceManager();`
- L173 _public prototype_ `FQuartzClockManager* GetClockManager();`
- L175 _public prototype_ `FQuartzClockCommandQueueWeakPtr GetCommandQueue() const;`
- L178 _public prototype_ `virtual void SubscribeToTimeDivision(FQuartzGameThreadSubscriber InSubscriber, EQuartzCommandQuantization InQuantizationBoundary) override;` — Metronome Event Subscription:
- L180 _public prototype_ `virtual void SubscribeToAllTimeDivisions(FQuartzGameThreadSubscriber InSubscriber) override;`
- L182 _public prototype_ `virtual void UnsubscribeFromTimeDivision(FQuartzGameThreadSubscriber InSubscriber, EQuartzCommandQuantization InQuantizationBoundary) override;`
- L184 _public prototype_ `virtual void UnsubscribeFromAllTimeDivisions(FQuartzGameThreadSubscriber InSubscriber) override;`
- L187 _public prototype_ `virtual void AddQuantizedCommand(FQuartzQuantizedRequestData& InQuantizedRequestData) override;` — Quantized Command Management:
- L188 _public prototype_ `virtual void AddQuantizedCommand(FQuartzQuantizedCommandInitInfo& InQuantizationCommandInitInfo) override;`
- L190 _public prototype_ `virtual void AddQuantizedCommand(FQuartzQuantizationBoundary InQuantizationBoundary, TSharedPtr<IQuartzQuantizedCommand> InNewEvent) override;`
- L192 _public prototype_ `bool CancelQuantizedCommand(TSharedPtr<IQuartzQuantizedCommand> InCommandPtr);`
- L196 _public prototype_ `void LowResolutionTick(float InDeltaTimeSeconds);` — low-resolution clock update (not sample-accurate!, useful when running without an Audio Device)
- L199 _public prototype_ `void Tick(int32 InNumFramesUntilNextTick);` — sample accurate clock update
- L220 _private member_ `FCriticalSection CachedClockStateCritSec;` — mutex-protected update at the end of Tick()
- L221 _private prototype_ `void UpdateCachedState();`
- L234 _private member_ `} CachedClockState;`
- L236 _private prototype_ `void TickInternal(int32 InNumFramesUntilNextTick, TArray<PendingCommand>& CommandsToTick, int32 FramesOfLatency = 0, int32 FramesOfDelay = 0);`
- L238 _private prototype_ `bool CancelQuantizedCommandInternal(TSharedPtr<IQuartzQuantizedCommand> InCommandPtr, TArray<PendingCommand>& CommandsToTick);`
- L242 _private prototype_ `FQuartzClock() = delete;` — don't allow default ctor, a clock needs to be ready to be used by the clock manager / FMixerDevice once constructed
- L244 _private member_ `FQuartzMetronome Metronome;`
- L246 _private member_ `FQuartzClockManager* OwningClockManagerPtr{ nullptr };`
- L248 _private member_ `FName Name;`
- L250 _private member_ `float ThreadLatencyInMilliseconds{ 40.f };`
- L253 _private member_ `mutable FQuartzClockCommandQueuePtr PreTickCommands;` — Command queue handed out to GameThread objects to queue commands. These get executed at the top of Tick()
- L256 _private member_ `TArray<PendingCommand> ClockAlteringPendingCommands;` — Container of external commands to be executed (TUniquePointer<QuantizedAudioCommand>)
- L257 _private member_ `TArray<PendingCommand> PendingCommands;`
- L259 _private member_ `FThreadSafeBool bIsRunning{ true };`
- L261 _private member_ `bool bIgnoresFlush{ false };`
- L263 _private member_ `int32 TickDelayLengthInFrames{ 0 };`

#### struct `Audio::FQuartzClock::PendingCommand`  
`struct PendingCommand`  
_L203-217_
- desc: Contains the pending command and the number of frames it has to wait to fire
- L206 _public function_ `PendingCommand(TSharedPtr<IQuartzQuantizedCommand> InCommand, int32 InNumFramesUntilExec) : Command(InCommand) , NumFramesUntilExec(InNumFramesUntilExec)` — ctor
- L213 _public member_ `TSharedPtr<IQuartzQuantizedCommand> Command;` — Quantized Command Object
- L216 _public member_ `int32 NumFramesUntilExec{ 0 };` — Countdown to execution

#### struct `Audio::FQuartzClock::FQuartzClockState`  
`struct FQuartzClockState`  
_L224-234_
- desc: data is cached when an FQuartzClock is ticked
- L226 _public member_ `FQuartzClockTickRate TickRate;`
- L227 _public member_ `FQuartzTransportTimeStamp TimeStamp;`
- L228 _public member_ `float RunTimeInSeconds;`
- L229 _public member_ `float MusicalDurationPhases[static_cast<int32>(EQuartzCommandQuantization::Count)] { 0 };`
- L230 _public member_ `float MusicalDurationPhaseDeltas[static_cast<int32>(EQuartzCommandQuantization::Count)] { 0 };`
- L231 _public member_ `uint64 LastCacheTickCpuCycles64 = 0;`
- L232 _public member_ `uint64 LastCacheTickDeltaCpuCycles64 = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOMIXER_API`
- L15 _namespace_ `namespace Audio`
- L23 _typedef_ `using FQuartzClockCommandQueueType = Audio::Quartz::PrivateDefs::TQuartzCommandQueue<IQuartzClock>;` (scope `Audio`)
- L24 _typedef_ `using FQuartzClockCommandQueuePtr = TSharedPtr<FQuartzClockCommandQueueType, ESPMode::ThreadSafe>;` (scope `Audio`)
- L25 _typedef_ `using FQuartzClockCommandQueueWeakPtr = TWeakPtr<FQuartzClockCommandQueueType, ESPMode::ThreadSafe>;` (scope `Audio`)

### `Source/Runtime/AudioMixer/Public/Quartz/AudioMixerClockHandle.h` (Public)


#### class `UQuartzClockHandle`  
`class UQuartzClockHandle : public UObject, public FQuartzTickableObject`  
_L27-180_
- reflection: `UCLASS(BlueprintType, Blueprintable, Transient, ClassGroup = Quartz, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UObject,FQuartzTickableObject`
- desc: This class is a BP / Game thread wrapper around FQuartzClockProxy (to talk to the underlying clock) ...and inherits from FQuartzTickableObject (to listen to the underlying clock) It can subscribe to Quantized Event & Metronome delegates to synchronize gameplay & VFX to Quartz events fired from the Audio Engine
- L33 _public prototype_ `UQuartzClockHandle();` — ctor
- L36 _public prototype_ `~UQuartzClockHandle();` — dtor
- L39 _public prototype_ `void BeginDestroy() override;` — begin UObject interface
- L44 _private prototype_ `virtual bool ShouldUnsubscribe() override;` — begin FQuartzTickableObject interface
- L53 _public prototype_ `void StartClock(const UObject* WorldContextObject, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject"))` — Clock manipulation
- L56 _public prototype_ `void StopClock(const UObject* WorldContextObject, bool CancelPendingEvents, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))`
- L59 _public prototype_ `void PauseClock(const UObject* WorldContextObject, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))`
- L62 _public prototype_ `void ResumeClock(const UObject* WorldContextObject, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject"))`
- L65 _public prototype_ `void ResetTransport(const UObject* WorldContextObject, const FOnQuartzCommandEventBP& InDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "Transport, Counter"))`
- L68 _public prototype_ `void ResetTransportQuantized(const UObject* WorldContextObject, FQuartzQuantizationBoundary InQuantizationBoundary, const FOnQuartzCommandEventBP& InDelegate, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "Transport, Counter"))`
- L71 _public prototype_ `bool IsClockRunning(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject", Keywords = "Transport, Counter"))`
- L74 _public prototype_ `void NotifyOnQuantizationBoundary(const UObject* WorldContextObject, FQuartzQuantizationBoundary InQuantizationBoundary, const FOnQuartzCommandEventBP& InDelegate, float InMsOffset = 0.f);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "Transport, Counter"))`
- L83 _public prototype_ `float GetDurationOfQuantizationTypeInSeconds(const UObject* WorldContextObject, const EQuartzCommandQuantization& QuantizationType, float Multiplier = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject"))` — Returns the duration in seconds of the given Quantization Type @param The Quantization type to measure @param The quantity of the Quantization Type to calculate the time of @return The duration, in seconds, of a multiplier amount of the Quantization Type, or -1 in the case the clock is invalid
- L87 _public prototype_ `FQuartzTransportTimeStamp GetCurrentTimestamp(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — Retrieves a timestamp for the clock
- L91 _public prototype_ `float GetEstimatedRunTime(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — Returns the amount of time, in seconds, the clock has been running. Caution: due to latency, this will not be perfectly accurate
- L95 _public prototype_ `void StartOtherClock(const UObject* WorldContextObject, FName OtherClockName, FQuartzQuantizationBoundary InQuantizationBoundary, const FOnQuartzCommandEventBP& InDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "Transport, Counter"))` — "other" clock manipulation
- L99 _public prototype_ `void SubscribeToQuantizationEvent(const UObject* WorldContextObject, EQuartzCommandQuantization InQuantizationBoundary, const FOnQuartzMetronomeEventBP& OnQuantizationEvent, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject"))` — Metronome subscription
- L102 _public prototype_ `void SubscribeToAllQuantizationEvents(const UObject* WorldContextObject, const FOnQuartzMetronomeEventBP& OnQuantizationEvent, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject"))`
- L105 _public prototype_ `void UnsubscribeFromTimeDivision(const UObject* WorldContextObject, EQuartzCommandQuantization InQuantizationBoundary, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject"))`
- L108 _public prototype_ `void UnsubscribeFromAllTimeDivisions(const UObject* WorldContextObject, UQuartzClockHandle*& ClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock", meta = (WorldContext = "WorldContextObject"))`
- L112 _public prototype_ `void SetMillisecondsPerTick(const UObject* WorldContextObject, UPARAM(ref) const FQuartzQuantizationBoundary& QuantizationBoundary, const FOnQuartzCommandEventBP& Delegate, UQuartzClockHandle*& ClockHandle, float MillisecondsPerTick = 100.f);` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "QuantizationBoundary, Delegate", AutoCreateRefTerm = "QuantizationBoundary, Delegate", Keywords = "BPM, Tempo"))` — Metronome Alteration (setters)
- L115 _public prototype_ `void SetTicksPerSecond(const UObject* WorldContextObject, UPARAM(ref) const FQuartzQuantizationBoundary& QuantizationBoundary, const FOnQuartzCommandEventBP& Delegate, UQuartzClockHandle*& ClockHandle, float TicksPerSecond = 10.f);` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "QuantizationBoundary, Delegate", AutoCreateRefTerm = "QuantizationBoundary, Delegate", Keywords = "BPM, Tempo"))`
- L118 _public prototype_ `void SetSecondsPerTick(const UObject* WorldContextObject, UPARAM(ref) const FQuartzQuantizationBoundary& QuantizationBoundary, const FOnQuartzCommandEventBP& Delegate, UQuartzClockHandle*& ClockHandle, float SecondsPerTick = 0.25f);` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "QuantizationBoundary, Delegate", AutoCreateRefTerm = "QuantizationBoundary, Delegate", Keywords = "BPM, Tempo"))`
- L121 _public prototype_ `void SetThirtySecondNotesPerMinute(const UObject* WorldContextObject, UPARAM(ref) const FQuartzQuantizationBoundary& QuantizationBoundary, const FOnQuartzCommandEventBP& Delegate, UQuartzClockHandle*& ClockHandle, float ThirtySecondsNotesPerMinute = 960.f);` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "QuantizationBoundary, Delegate", AutoCreateRefTerm = "QuantizationBoundary, Delegate", Keywords = "BPM, Tempo"))`
- L124 _public prototype_ `void SetBeatsPerMinute(const UObject* WorldContextObject, UPARAM(ref) const FQuartzQuantizationBoundary& QuantizationBoundary, const FOnQuartzCommandEventBP& Delegate, UQuartzClockHandle*& ClockHandle, float BeatsPerMinute = 60.f);` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "QuantizationBoundary, Delegate", AutoCreateRefTerm = "QuantizationBoundary, Delegate", Keywords = "BPM, Tempo"))`
- L128 _public prototype_ `float GetMillisecondsPerTick(const UObject* WorldContextObject) const;` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "BPM, Tempo"))` — Metronome getters
- L131 _public prototype_ `float GetTicksPerSecond(const UObject* WorldContextObject) const;` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "BPM, Tempo"))`
- L134 _public prototype_ `float GetSecondsPerTick(const UObject* WorldContextObject) const;` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "BPM, Tempo"))`
- L137 _public prototype_ `float GetThirtySecondNotesPerMinute(const UObject* WorldContextObject) const;` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "BPM, Tempo"))`
- L140 _public prototype_ `float GetBeatsPerMinute(const UObject* WorldContextObject) const;` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "InDelegate", Keywords = "BPM, Tempo"))`
- L148 _public prototype_ `float GetBeatProgressPercent(EQuartzCommandQuantization QuantizationBoundary = EQuartzCommandQuantization::Beat, float PhaseOffset = 0.f, float MsOffset = 0.f);` — `UFUNCTION(BlueprintCallable, Category = "Quantization", meta = ( AutoCreateRefTerm = "PhaseOffset", Keywords = "BPM, Tempo"))` — Returns the current progress until the next occurrence of the provided musical duration as a float value from 0 (previous beat) to 1 (next beat). This is useful for indexing into curves to animate parameters to musical time. Ms and Phase offsets are combined internally.
- L160 _public prototype_ `void QueueQuantizedSound(const UObject* WorldContextObject, UQuartzClockHandle*& ClockHandle, const FAudioComponentCommandInfo& AudioComponentData, const FOnQuartzCommandEventBP& InDelegate, const FQuartzQuantizationBoundary& InTargetBoundary);`
- L162 _public prototype_ `UQuartzClockHandle* SubscribeToClock(const UObject* WorldContextObject, FName ClockName, Audio::FQuartzClockProxy const* InHandlePtr = nullptr);`
- L164 _public function_ `FName GetClockName() const`
- L166 _public function_ `bool DoesClockExist(const UObject* WorldContextObject) const`
- L171 _public prototype_ `bool GetCurrentTickRate(const UObject* WorldContextObject, Audio::FQuartzClockTickRate& OutTickRate) const;`
- L174 _private prototype_ `void SetTickRateInternal(const FQuartzQuantizationBoundary& InQuantizationBoundary, const FOnQuartzCommandEventBP& InDelegate, const Audio::FQuartzClockTickRate& NewTickRate);`
- L176 _private member_ `Audio::FQuartzClockProxy RawHandle;`
- L178 _private member_ `FName CurrentClockId;`

### `Source/Runtime/AudioMixer/Public/Quartz/AudioMixerClockManager.h` (Public)


#### class `Audio::FQuartzClockManager`  
`class FQuartzClockManager : public FQuartLatencyTracker`  
_L17-134_
- inherits: `FQuartLatencyTracker`
- desc: Class that owns, updates, and provides access to all active clocks All methods are thread-safe. The method locks if it returns a value, and stages a command if it returns void
- L21 _public prototype_ `FQuartzClockManager(Audio::FMixerDevice* InOwner = nullptr);` — ctor
- L24 _public prototype_ `~FQuartzClockManager();` — dtor
- L26 _public function_ `int32 GetNumClocks() const`
- L29 _public prototype_ `void Update(int32 NumFramesUntilNextUpdate);` — Called on AudioRenderThread
- L30 _public prototype_ `void UpdateClock(FName InClockToAdvance, int32 NumFramesToAdvance);`
- L35 _public prototype_ `void LowResoultionUpdate(float DeltaTimeSeconds);` — can be called from any thread for low-resolution clock updates (i.e. used when running without an audio device) not sample-accurate!
- L39 _public prototype_ `FQuartzClockProxy GetOrCreateClock(const FName& InClockName, const FQuartzClockSettings& InClockSettings, bool bOverrideTickRateIfClockExists = false);` — add (and take ownership of) a new clock safe to call from AudioThread (uses critical section)
- L40 _public prototype_ `FQuartzClockProxy GetClock(const FName& InClockName);`
- L43 _public prototype_ `bool DoesClockExist(const FName& InClockName);` — returns true if a clock with the given name already exists.
- L46 _public prototype_ `bool IsClockRunning(const FName& InClockName);` — returns true if the name is running
- L49 _public prototype_ `float GetDurationOfQuantizationTypeInSeconds(const FName& InClockName, const EQuartzCommandQuantization& QuantizationType, float Multiplier);` — Returns the duration in seconds of the given Quantization Type, or -1 if the Clock is invalid or nonexistent
- L52 _public prototype_ `FQuartzTransportTimeStamp GetCurrentTimestamp(const FName& InClockName);` — Returns the current location of the clock in the transport
- L55 _public prototype_ `float GetEstimatedRunTime(const FName& InClockName);` — Returns the amount of time, in seconds, the clock has been running. Caution: due to latency, this will not be perfectly accurate
- L59 _public prototype_ `void RemoveClock(const FName& InName, bool bForceSynchronous = false);` — remove existing clock safe to call from AudioThread (uses Audio Render Thread Command)
- L63 _public prototype_ `FQuartzClockTickRate GetTickRateForClock(const FName& InName);` — get Tick rate for clock safe to call from AudioThread (uses critical section)
- L65 _public prototype_ `void SetTickRateForClock(const FQuartzClockTickRate& InNewTickRate, const FName& InName);`
- L69 _public prototype_ `void ResumeClock(const FName& InName, int32 NumFramesToDelayStart = 0);` — start the given clock safe to call from AudioThread (uses Audio Render Thread command)
- L73 _public prototype_ `void StopClock(const FName& InName, bool CancelPendingEvents);` — stop the given clock safe to call from AudioThread (uses Audio Render Thread command)
- L77 _public prototype_ `void PauseClock(const FName& InName);` — stop the given clock safe to call from AudioThread (uses Audio Render Thread command)
- L80 _public prototype_ `void Flush();` — shutdown all clocks that don't ignore Flush() (i.e. level change)
- L83 _public prototype_ `void Shutdown();` — stop all clocks and cancel all pending events
- L87 _public prototype_ `FQuartzQuantizedCommandHandle AddCommandToClock(FQuartzQuantizedCommandInitInfo& InQuantizationCommandInitInfo);` — add a new command to a given clock safe to call from AudioThread (uses Audio Render Thread command)
- L92 _public prototype_ `void SubscribeToTimeDivision(FName InClockName, MetronomeCommandQueuePtr InListenerQueue, EQuartzCommandQuantization InQuantizationBoundary);` — subscribe to a specific time division on a clock TODO: update the metronome subscription functions to take an FQuartzGameThreadSubscriber instead of the Command queue ptr (to support metronome event offset)
- L95 _public prototype_ `void SubscribeToAllTimeDivisions(FName InClockName, MetronomeCommandQueuePtr InListenerQueue);` — subscribe to all time divisions on a clock
- L98 _public prototype_ `void UnsubscribeFromTimeDivision(FName InClockName, MetronomeCommandQueuePtr InListenerQueue, EQuartzCommandQuantization InQuantizationBoundary);` — un-subscribe from a specific time division on a clock
- L101 _public prototype_ `void UnsubscribeFromAllTimeDivisions(FName InClockName, MetronomeCommandQueuePtr InListenerQueue);` — un-subscribe from all time divisions on a specific clock
- L104 _public prototype_ `bool CancelCommandOnClock(FName InOwningClockName, TSharedPtr<IQuartzQuantizedCommand> InCommandPtr);` — cancel a queued command on a clock (i.e. cancel a PlayQuantized command if the sound is stopped before it is played)
- L106 _public prototype_ `bool HasClockBeenTickedThisUpdate(FName InClockName);`
- L108 _public function_ `int32 GetLastUpdateSizeInFrames() const`
- L111 _public prototype_ `FMixerDevice* GetMixerDevice() const;` — get access to the owning FMixerDevice
- L115 _private prototype_ `void TickClocks(int32 NumFramesToTick);` — updates all active clocks
- L118 _private prototype_ `TSharedPtr<FQuartzClock> FindClock(const FName& InName);` — find clock with a given key
- L121 _private member_ `FMixerDevice* MixerDevice;` — pointer to owning FMixerDevice
- L124 _private member_ `FCriticalSection ActiveClockCritSec;` — Container of active clocks
- L127 _private member_ `TArray<TSharedPtr<FQuartzClock>> ActiveClocks;` — Our array of active clocks (mutation/access acquires clock)
- L129 _private member_ `FThreadSafeCounter LastClockTickedIndex{ 0 };`
- L130 _private member_ `int32 LastUpdateSizeInFrames{ 0 };`

#### struct `Audio::FPersistentQuartzSubsystemData`  
`struct FPersistentQuartzSubsystemData`  
_L137-145_
- desc: data that the UQuartzSubsystem needs to persist on the AudioDevice across UWorld shutdown/startup
- L140 _public member_ `FQuartzClockManager SubsystemClockManager;` — internal clock manager for game-thread-ticked clocks
- L143 _public member_ `TArray<Audio::FQuartzClockProxy> ActiveExternalClockProxies;` — array of active clock handles (update FindProxyByName() if more are added later)
- L144 _public member_ `TArray<Audio::FQuartzClockProxy> ActiveAudioMixerClockProxies;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Public/Quartz/AudioMixerQuantizedCommands.h` (Public)


#### class `Audio::FQuantizedPlayCommand`  
`class FQuantizedPlayCommand : public IQuartzQuantizedCommand`  
_L9-42_
- inherits: `IQuartzQuantizedCommand`
- desc: QuartzQuantizedCommand that plays a sound on a sample-accurate boundary
- L13 _public prototype_ `FQuantizedPlayCommand();` — ctor
- L16 _public prototype_ `~FQuantizedPlayCommand() = default;` — dtor
- L18 _public prototype_ `virtual TSharedPtr<IQuartzQuantizedCommand> GetDeepCopyOfDerivedObject() const override;`
- L20 _public prototype_ `virtual void OnQueuedCustom(const FQuartzQuantizedCommandInitInfo& InCommandInitInfo) override;`
- L22 _public prototype_ `virtual void OnFinalCallbackCustom(int32 InNumFramesLeft) override;`
- L24 _public prototype_ `virtual void CancelCustom() override;`
- L26 _public function_ `virtual bool RequiresAudioDevice() const override`
- L28 _public prototype_ `virtual FName GetCommandName() const override;`
- L31 _public function_ `virtual EQuartzCommandType GetCommandType() const` — for your implementation, a new EQuartzCommandType needs to be defined in QuartzQuantizationUtilities.h
- L33 _public prototype_ `virtual int32 OverrideFramesUntilExec(int32 NumFramesUntilExec);`
- L36 _protected member_ `TSharedPtr<FQuartzClock> OwningClockPtr{ nullptr };`
- L38 _protected member_ `int32 SourceID{ -1 };`
- L40 _protected member_ `bool bIsCanceled = false;`

#### class `Audio::FQuantizedQueueCommand`  
`class FQuantizedQueueCommand : public IQuartzQuantizedCommand`  
_L45-70_
- inherits: `IQuartzQuantizedCommand`
- L48 _public prototype_ `virtual TSharedPtr<IQuartzQuantizedCommand> GetDeepCopyOfDerivedObject() const override;`
- L50 _public prototype_ `virtual void OnQueuedCustom(const FQuartzQuantizedCommandInitInfo& InCommandInitInfo) override;`
- L52 _public prototype_ `virtual int32 OverrideFramesUntilExec(int32 NumFramesUntilExec) override;`
- L54 _public prototype_ `virtual void OnFinalCallbackCustom(int32 InNumFramesLeft) override;`
- L56 _public function_ `virtual bool RequiresAudioDevice() const override`
- L58 _public prototype_ `virtual FName GetCommandName() const override;`
- L59 _public function_ `virtual EQuartzCommandType GetCommandType() const`
- L61 _public prototype_ `void SetQueueCommand(const FAudioComponentCommandInfo& InAudioCommandData);`
- L63 _public function_ `FQuantizedQueueCommand()`
- L66 _private member_ `TSharedPtr<FQuartzClock> OwningClockPtr{ nullptr };`
- L69 _private member_ `FAudioComponentCommandInfo AudioComponentData;` — Data for the quantization event

#### class `Audio::FQuantizedTickRateChange`  
`class FQuantizedTickRateChange : public IQuartzQuantizedCommand`  
_L73-96_
- inherits: `IQuartzQuantizedCommand`
- desc: QuartzQuantizedCommand that changes the TickRate of a clock on a sample-accurate boundary (i.e. BPM changes)
- L76 _public function_ `void SetTickRate(const FQuartzClockTickRate& InTickRate)`
- L81 _public prototype_ `virtual TSharedPtr<IQuartzQuantizedCommand> GetDeepCopyOfDerivedObject() const override;`
- L83 _public prototype_ `virtual void OnQueuedCustom(const FQuartzQuantizedCommandInitInfo& InCommandInitInfo) override;`
- L85 _public prototype_ `virtual void OnFinalCallbackCustom(int32 InNumFramesLeft) override;`
- L87 _public function_ `virtual bool IsClockAltering() override`
- L89 _public prototype_ `virtual FName GetCommandName() const override;`
- L90 _public function_ `virtual EQuartzCommandType GetCommandType() const`
- L93 _private member_ `FQuartzClockTickRate TickRate;`
- L94 _private member_ `TSharedPtr<FQuartzClock> OwningClockPtr{ nullptr };`

#### class `Audio::FQuantizedTransportReset`  
`class FQuantizedTransportReset : public IQuartzQuantizedCommand`  
_L100-117_
- inherits: `IQuartzQuantizedCommand`
- desc: QuartzQuantizedCommand that resets the transport of a clock's metronome on a sample-accurate boundary
- L103 _public prototype_ `virtual TSharedPtr<IQuartzQuantizedCommand> GetDeepCopyOfDerivedObject() const override;`
- L105 _public prototype_ `virtual void OnQueuedCustom(const FQuartzQuantizedCommandInitInfo& InCommandInitInfo) override;`
- L107 _public prototype_ `virtual void OnFinalCallbackCustom(int32 InNumFramesLeft) override;`
- L109 _public function_ `virtual bool IsClockAltering() override`
- L111 _public prototype_ `virtual FName GetCommandName() const override;`
- L112 _public function_ `virtual EQuartzCommandType GetCommandType() const`
- L115 _private member_ `TSharedPtr<FQuartzClock> OwningClockPtr{ nullptr };`

#### class `Audio::FQuantizedOtherClockStart`  
`class FQuantizedOtherClockStart : public IQuartzQuantizedCommand`  
_L121-139_
- inherits: `IQuartzQuantizedCommand`
- desc: QuartzQuantizedCommand that starts a second clock on a sample-accurate boundary
- L124 _public prototype_ `virtual TSharedPtr<IQuartzQuantizedCommand> GetDeepCopyOfDerivedObject() const override;`
- L126 _public prototype_ `virtual void OnQueuedCustom(const FQuartzQuantizedCommandInitInfo& InCommandInitInfo) override;`
- L128 _public prototype_ `virtual void OnFinalCallbackCustom(int32 InNumFramesLeft) override;`
- L130 _public function_ `virtual bool IsClockAltering() override`
- L132 _public prototype_ `virtual FName GetCommandName() const override;`
- L133 _public function_ `virtual EQuartzCommandType GetCommandType() const`
- L136 _private member_ `TSharedPtr<FQuartzClock> OwningClockPtr{ nullptr };`
- L137 _private member_ `FName NameOfClockToStart;`

#### class `Audio::FQuantizedNotify`  
`class FQuantizedNotify : public IQuartzQuantizedCommand`  
_L143-170_
- inherits: `IQuartzQuantizedCommand`
- desc: QuartzQuantizedCommand that basically no-ops, so the game thread can get notified on a musical boundary
- L147 _public prototype_ `FQuantizedNotify(float InMsOffset = 0.f);` — ctor
- L150 _public prototype_ `virtual ~FQuantizedNotify() override = default;` — dtor
- L152 _public prototype_ `virtual TSharedPtr<IQuartzQuantizedCommand> GetDeepCopyOfDerivedObject() const override;`
- L154 _public function_ `virtual bool RequiresAudioDevice() const override`
- L156 _public prototype_ `virtual FName GetCommandName() const override;`
- L158 _public function_ `virtual EQuartzCommandType GetCommandType() const override`
- L160 _public prototype_ `virtual void OnQueuedCustom(const FQuartzQuantizedCommandInitInfo& InCommandInitInfo) override;`
- L162 _public prototype_ `virtual int32 OverrideFramesUntilExec(int32 NumFramesUntilExec) override;`
- L165 _protected member_ `TSharedPtr<FQuartzClock> OwningClockPtr{ nullptr };`
- L166 _protected member_ `float OffsetInMs = 0.f;`
- L167 _protected member_ `float SampleRate = 0.f;`
- L168 _protected member_ `bool bIsCanceled = false;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixer/Public/Quartz/QuartzMetronome.h` (Public)


#### class `Audio::FQuartzMetronome`  
`class FQuartzMetronome`  
_L18-136_
- desc: Class to track the passage of musical time, and allow subscribers to be notified when these musical events take place
- L22 _public prototype_ `FQuartzMetronome(FName InClockName = {});` — ctor
- L23 _public prototype_ `FQuartzMetronome(const FQuartzTimeSignature& InTimeSignature, FName InClockName = {});`
- L26 _public prototype_ `~FQuartzMetronome();` — dtor
- L29 _public prototype_ `void Tick(int32 InNumSamples, int32 FramesOfLatency = 0);` — Transport Control:
- L31 _public prototype_ `void SetTickRate(FQuartzClockTickRate InNewTickRate, int32 NumFramesLeft = 0);`
- L33 _public prototype_ `void SetSampleRate(float InNewSampleRate);`
- L35 _public prototype_ `void SetTimeSignature(const FQuartzTimeSignature& InNewTimeSignature);`
- L37 _public prototype_ `void ResetTransport();`
- L40 _public function_ `const FQuartzClockTickRate& GetTickRate() const` — Getters
- L42 _public prototype_ `double GetFramesUntilBoundary(FQuartzQuantizationBoundary InQuantizationBoundary) const;`
- L44 _public function_ `const FQuartzTimeSignature & GetTimeSignature() const`
- L46 _public function_ `FQuartzTransportTimeStamp GetTimeStamp() const`
- L48 _public function_ `double GetTimeSinceStart() const`
- L50 _public function_ `uint64 GetLastTickCpuCycles64() const`
- L52 _public prototype_ `void CalculateDurationPhases(float (&OutPhases)[static_cast<int32>(EQuartzCommandQuantization::Count)]) const;`
- L55 _public prototype_ `void SubscribeToTimeDivision(MetronomeCommandQueuePtr InListenerQueue, EQuartzCommandQuantization InQuantizationBoundary);` — Event Subscription
- L57 _public prototype_ `void SubscribeToAllTimeDivisions(MetronomeCommandQueuePtr InListenerQueue);`
- L59 _public prototype_ `void UnsubscribeFromTimeDivision(MetronomeCommandQueuePtr InListenerQueue, EQuartzCommandQuantization InQuantizationBoundary);`
- L61 _public prototype_ `void UnsubscribeFromAllTimeDivisions(MetronomeCommandQueuePtr InListenerQueue);`
- L67 _private prototype_ `void RecalculateDurations();` — Helpers:
- L69 _private prototype_ `void FireEvents();`
- L71 _private prototype_ `float CountNumSubdivisionsPerBar(EQuartzCommandQuantization InSubdivision) const;`
- L73 _private prototype_ `float CountNumSubdivisionsSinceBarStart(EQuartzCommandQuantization InSubdivision) const;`
- L75 _private prototype_ `float CountNumSubdivisionsSinceStart(EQuartzCommandQuantization InSubdivision) const;`
- L77 _private member_ `uint64 LastTickCpuCycles64{ 0 };`
- L79 _private member_ `int32 ListenerFlags{ 0 };`
- L81 _private member_ `FQuartzTransportTimeStamp CurrentTimeStamp;`
- L83 _private member_ `FQuartzTimeSignature CurrentTimeSignature;`
- L85 _private member_ `FQuartzClockTickRate CurrentTickRate;`
- L87 _private member_ `TArray<MetronomeCommandQueuePtr> MetronomeSubscriptionMatrix[static_cast<int32>(EQuartzCommandQuantization::Count)];`
- L115 _private member_ `} PendingMetronomeEvents;`
- L118 _private member_ `FFramesInTimeValue MusicalDurationsInFrames;` — array of lengths of musical durations (in audio frames)
- L121 _private member_ `FFramesInTimeValue FramesLeftInMusicalDuration;` — array of the number of audio frames left until the respective musical duration
- L124 _private member_ `TArray<double> PulseDurations;` — optional array of pulse duration overrides (for odd meters)
- L127 _private member_ `int32 PulseDurationIndex{ -1 };` — the index of the active pulse duration override
- L129 _private member_ `int32 LastFramesOfLatency{ 0 };`
- L132 _private member_ `double TimeSinceStart;` — Keeps track of time in seconds since the Clock was last reset
- L134 _private member_ `FName ClockName;`

#### struct `Audio::FQuartzMetronome::FFramesInTimeValue`  
`struct FFramesInTimeValue`  
_L90-100_
- desc: wrapper around our array so it can be indexed into by different Enums that represent musical time
- L92 _public prototype_ `void Reset();`
- L94 _public prototype_ `double& operator[](EQuartzCommandQuantization InTimeValue);`
- L95 _public prototype_ `const double& operator[](EQuartzCommandQuantization InTimeValue) const;`
- L96 _public prototype_ `double& operator[](int32 Index);`
- L97 _public prototype_ `const double& operator[](int32 Index) const;`
- L99 _public member_ `double FramesInTimeValueInternal[static_cast<int32>(EQuartzCommandQuantization::Count)]{ 0.0 };`

#### struct `Audio::FQuartzMetronome::FMetronomeEventEntry`  
`struct FMetronomeEventEntry`  
_L102-106_
- L104 _public member_ `TArray<int32> EventFrames;`
- L105 _public prototype_ `void Reset();`

#### struct `Audio::FQuartzMetronome::FPendingMetronomeEvents`  
`struct FPendingMetronomeEvents`  
_L108-115_
- L110 _public prototype_ `void Add(const EQuartzCommandQuantization InDuration, const int32 InFrame);`
- L111 _public prototype_ `void Reset();`
- L112 _public prototype_ `bool HasPendingEvent(const EQuartzCommandQuantization InDuration) const;`
- L114 _public member_ `FMetronomeEventEntry CurrentMetronomeEvents[static_cast<int32>(EQuartzCommandQuantization::Count)];`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Audio`
- L15 _typedef_ `using MetronomeCommandQueuePtr = Quartz::FQuartzGameThreadCommandQueuePtr;` (scope `Audio`) — todo: rename, "GameThread is not accurate"

### `Source/Runtime/AudioMixer/Public/Quartz/QuartzSubsystem.h` (Public)


#### struct `FQuartzTickableObjectsManager`  
`struct FQuartzTickableObjectsManager : public FQuartLatencyTracker`  
_L28-42_
- inherits: `FQuartLatencyTracker`
- L31 _public prototype_ `void Tick(float DeltaTime);`
- L32 _public prototype_ `bool IsTickable() const;`
- L33 _public prototype_ `void SubscribeToQuartzTick(FQuartzTickableObject* InObjectToTick);`
- L34 _public prototype_ `void UnsubscribeFromQuartzTick(FQuartzTickableObject* InObjectToTick);`
- L38 _private member_ `TArray<FQuartzTickableObject *> QuartzTickSubscribers;` — list of objects needing to be ticked by Quartz
- L41 _private member_ `int32 UpdateIndex{ 0 };` — index to track the next subscriber to tick (if updates are being amortized across multiple UObject Ticks)

#### class `UQuartzSubsystem`  
`class UQuartzSubsystem : public UTickableWorldSubsystem`  
_L46-183_
- reflection: `UCLASS(DisplayName = "Quartz", MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- L52 _public prototype_ `UQuartzSubsystem() = default;` — ctor/dtor
- L53 _public prototype_ `virtual ~UQuartzSubsystem() override = default;`
- L56 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L57 _public prototype_ `virtual void Deinitialize() override;`
- L58 _public prototype_ `virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;`
- L59 _public prototype_ `void virtual BeginDestroy() override;`
- L63 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L64 _public prototype_ `virtual bool IsTickableWhenPaused() const override;`
- L65 _public prototype_ `virtual bool IsTickable() const override;`
- L66 _public prototype_ `virtual TStatId GetStatId() const override;`
- L70 _public prototype_ `void SubscribeToQuartzTick(FQuartzTickableObject* InObjectToTick);` — these calls are forwarded to the internal FQuartzTickableObjectsManager
- L71 _public prototype_ `void UnsubscribeFromQuartzTick(FQuartzTickableObject* InObjectToTick);`
- L74 _public prototype_ `Audio::FQuartzClockProxy GetProxyForClock(FName ClockName) const;` — get C++ handle (proxy) to a clock if it exists
- L77 _public prototype_ `void AddProxyForExternalClock(const Audio::FQuartzClockProxy& InProxy);` — allow an external clock (not ticked by the Audio Mixer or QuartzSubsystem) to be accessible via this subsystem
- L80 _public prototype_ `static UQuartzSubsystem* Get(const UWorld* const World);` — static methods
- L83 _public prototype_ `static Audio::FQuartzQuantizedRequestData CreateRequestDataForTickRateChange(UQuartzClockHandle* InClockHandle, const FOnQuartzCommandEventBP& InDelegate, const Audio::FQuartzClockTickRate& InNewTickRate, const FQuartzQuantizationBoundary& InQuantizationBoundary);` — Helper functions for initializing quantized command initialization struct (to consolidate eyesore)
- L84 _public prototype_ `static Audio::FQuartzQuantizedRequestData CreateRequestDataForTransportReset(UQuartzClockHandle* InClockHandle, const FQuartzQuantizationBoundary& InQuantizationBoundary, const FOnQuartzCommandEventBP& InDelegate);`
- L85 _public prototype_ `static Audio::FQuartzQuantizedRequestData CreateRequestDataForStartOtherClock(UQuartzClockHandle* InClockHandle, FName InClockToStart, const FQuartzQuantizationBoundary& InQuantizationBoundary, const FOnQuartzCommandEventBP& InDelegate);`
- L86 _public prototype_ `static Audio::FQuartzQuantizedRequestData CreateRequestDataForSchedulePlaySound(UQuartzClockHandle* InClockHandle, const FOnQuartzCommandEventBP& InDelegate, const FQuartzQuantizationBoundary& InQuantizationBoundary);`
- L87 _public prototype_ `static Audio::FQuartzQuantizedRequestData CreateRequestDataForQuantizedNotify(UQuartzClockHandle* InClockHandle, const FQuartzQuantizationBoundary& InQuantizationBoundary, const FOnQuartzCommandEventBP& InDelegate, float InMsOffset = 0.f);`
- L90 _public prototype_ `bool IsQuartzEnabled();` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle")`
- L95 _public prototype_ `UQuartzClockHandle* CreateNewClock(const UObject* WorldContextObject, FName ClockName, FQuartzClockSettings InSettings, bool bOverrideSettingsIfClockExists = false, bool bUseAudioEngineClockManager = true);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "bUseAudioEngineClockManager"))` — Clock Creation create a new clock (or return handle if clock already exists)
- L99 _public prototype_ `void DeleteClockByName(const UObject* WorldContextObject, FName ClockName);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — delete an existing clock given its name
- L103 _public prototype_ `void DeleteClockByHandle(const UObject* WorldContextObject, UPARAM(ref) UQuartzClockHandle*& InClockHandle);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — delete an existing clock given its clock handle
- L107 _public prototype_ `UQuartzClockHandle* GetHandleForClock(const UObject* WorldContextObject, FName ClockName);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — get handle for existing clock
- L111 _public prototype_ `bool DoesClockExist(const UObject* WorldContextObject, FName ClockName);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — returns true if the clock exists
- L115 _public prototype_ `bool IsClockRunning(const UObject* WorldContextObject, FName ClockName);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — returns true if the clock is running
- L119 _public prototype_ `float GetDurationOfQuantizationTypeInSeconds(const UObject* WorldContextObject, FName ClockName, const EQuartzCommandQuantization& QuantizationType, float Multiplier = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — Returns the duration in seconds of the given Quantization Type
- L123 _public prototype_ `FQuartzTransportTimeStamp GetCurrentClockTimestamp(const UObject* WorldContextObject, const FName& InClockName);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — Retrieves a timestamp for the clock
- L127 _public prototype_ `float GetEstimatedClockRunTime(const UObject* WorldContextObject, const FName& InClockName);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Clock Handle", meta = (WorldContext = "WorldContextObject"))` — Returns the amount of time, in seconds, the clock has been running. Caution: due to latency, this will not be perfectly accurate
- L131 _public prototype_ `float GetGameThreadToAudioRenderThreadAverageLatency(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))` — latency data (Game thread -> Audio Render Thread)
- L134 _public prototype_ `float GetGameThreadToAudioRenderThreadMinLatency(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))`
- L137 _public prototype_ `float GetGameThreadToAudioRenderThreadMaxLatency(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))`
- L141 _public prototype_ `float GetAudioRenderThreadToGameThreadAverageLatency();` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem")` — latency data (Audio Render Thread -> Game thread)
- L144 _public prototype_ `float GetAudioRenderThreadToGameThreadMinLatency();` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem")`
- L147 _public prototype_ `float GetAudioRenderThreadToGameThreadMaxLatency();` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem")`
- L151 _public prototype_ `float GetRoundTripAverageLatency(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))` — latency data (Round trip)
- L154 _public prototype_ `float GetRoundTripMinLatency(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))`
- L157 _public prototype_ `float GetRoundTripMaxLatency(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem", meta = (WorldContext = "WorldContextObject"))`
- L160 _public prototype_ `void SetQuartzSubsystemTickableWhenPaused(const bool bInTickableWhenPaused);` — `UFUNCTION(BlueprintCallable, Category = "Quartz Subsystem")`
- L163 _public prototype_ `TWeakPtr<FQuartzTickableObjectsManager> GetTickableObjectManager() const;` — sharable to allow non-UObjects to un-subscribe if the Subsystem is going to outlive them
- L167 _private prototype_ `void PruneStaleProxies();` — deletes proxies to clocks that no longer exists
- L168 _private prototype_ `static void PruneStaleProxiesInternal(TArray<Audio::FQuartzClockProxy>& ContainerToPrune);`
- L171 _private member_ `TSharedPtr<FQuartzTickableObjectsManager> TickableObjectManagerPtr { MakeShared<FQuartzTickableObjectsManager>() };` — sharable tickable object manager to allow for non-UObject subscription / un-subscription
- L174 _private member_ `TSharedPtr<Audio::FPersistentQuartzSubsystemData> ClockManagerDataPtr { nullptr };` — Clock manager/proxy-related data that lives on the AudioDevice for persistence.
- L176 _private member_ `bool bTickEvenWhenPaused = false;`
- L179 _private prototype_ `Audio::FQuartzClockProxy* FindProxyByName(const FName& ClockName);` — helpers
- L180 _private prototype_ `Audio::FQuartzClockProxy const* FindProxyByName(const FName& ClockName) const;`
- L181 _private prototype_ `Audio::FQuartzClockManager* GetClockManager(const UObject* WorldContextObject, bool bUseAudioEngineClockManager = true);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Audio`
- L24 _typedef_ `using MetronomeCommandQueuePtr = TSharedPtr<Audio::FQuartzShareableCommandQueue, ESPMode::ThreadSafe>;`

### `Source/Runtime/AudioMixer/Public/SoundFileIO/SoundFileIO.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L8 _namespace_ `namespace SoundFileUtils` (scope `Audio`)
- L10 _prototype_ `bool InitSoundFileIOManager();` (scope `Audio::SoundFileUtils`)
- L11 _prototype_ `bool ShutdownSoundFileIOManager();` (scope `Audio::SoundFileUtils`)
- L12 _prototype_ `uint32 GetNumSamples(const TArray<uint8>& InAudioData);` (scope `Audio::SoundFileUtils`)
- L13 _prototype_ `bool ConvertAudioToWav(const TArray<uint8>& InAudioData, TArray<uint8>& OutWaveData);` (scope `Audio::SoundFileUtils`)
- L14 _prototype_ `bool CreateCueAndSampleChunks(const TArray<uint8>& InAudioData, TArray<uint8>& OutWaveData, const TArray<FWaveCue>& InWaveCues, const TArray<FWaveSampleLoop>& InSampleLoops);` (scope `Audio::SoundFileUtils`)

### `Source/Runtime/AudioMixer/Public/SoundWaveDecoder.h` (Public)


#### struct `Audio::FDecodingSoundSourceHandle`  
`struct FDecodingSoundSourceHandle`  
_L23-31_
- L25 _public function_ `FDecodingSoundSourceHandle() : Id(INDEX_NONE)`
- L29 _public member_ `int32 Id;`
- L30 _public member_ `FName SoundWaveName;`

#### struct `Audio::FSourceDecodeInit`  
`struct FSourceDecodeInit`  
_L33-49_
- L35 _public function_ `FSourceDecodeInit() : SoundWave(nullptr) , SeekTime(0.0f) , PitchScale(1.0f) , VolumeScale(1.0f) , bForceSyncDecode(false)`
- L43 _public member_ `TObjectPtr<USoundWave> SoundWave;`
- L44 _public member_ `float SeekTime;`
- L45 _public member_ `float PitchScale;`
- L46 _public member_ `float VolumeScale;`
- L47 _public member_ `bool bForceSyncDecode;`
- L48 _public member_ `FDecodingSoundSourceHandle Handle;`

#### class `Audio::FDecodingSoundSource`  
`class FDecodingSoundSource`  
_L51-209_
- L54 _public prototype_ `FDecodingSoundSource(FAudioDevice* AudioDevice, const FSourceDecodeInit& InitData);`
- L55 _public prototype_ `~FDecodingSoundSource();`
- L58 _public prototype_ `bool PreInit(int32 OutputSampleRate);` — Called before we initialize
- L61 _public prototype_ `bool IsReadyToInit();` — Queries if we're ready to initialize
- L64 _public prototype_ `void Init();` — Initializes the decoding source
- L67 _public function_ `bool IsInitialized() const` — Returns if we've been initialized
- L70 _public function_ `bool IsFinished() const` — If the sound source finished playing all its source. Will only return true for non-looping sources.
- L73 _public prototype_ `void SetPitchScale(float InPitchScale, uint32 NumFrames = 512);` — Sets the pitch scale
- L76 _public prototype_ `void SetVolumeScale(float InVolumeScale, uint32 NumFrames = 512);` — Sets the volume scale
- L79 _public prototype_ `void SetForceSyncDecode(bool bShouldForceSyncDecode);` — Sets the ForceSyncDecode flag. (Decodes for this soundwave will not happen in an async task if true)
- L82 _public prototype_ `bool GetAudioBuffer(const int32 InNumFrames, const int32 InNumChannels, FAlignedFloatBuffer& OutAudioBuffer);` — Get audio buffer
- L85 _public function_ `USoundWave* GetSoundWave()` — Return the underlying sound wave
- L87 _public function_ `TObjectPtr<USoundWave>& GetSoundWavePtr()`
- L91 _private prototype_ `void ReadFrame();`
- L92 _private prototype_ `void GetAudioBufferInternal(const int32 InNumFrames, const int32 InNumChannels, FAlignedFloatBuffer& OutAudioBuffer);`
- L95 _private member_ `FDecodingSoundSourceHandle Handle;` — Handle to the decoding source
- L97 _private member_ `FDeviceId AudioDeviceID;`
- L100 _private member_ `TObjectPtr<USoundWave> SoundWave;` — The sound wave object with which this sound is generating
- L103 _private member_ `FMixerBuffer* MixerBuffer;` — Mixer buffer object which is a convenience wrapper around some buffer initialization and management
- L106 _private member_ `FCriticalSection MixerSourceBufferCritSec;` — Critical Section around mixer source buffer access
- L109 _private member_ `TSharedPtr<FMixerSourceBuffer, ESPMode::ThreadSafe> MixerSourceBuffer;` — Object which handles bulk of decoding operations
- L112 _private member_ `FAlignedFloatBuffer ScratchBuffer;` — Scratch buffer used for upmixing and downmixing the audio
- L115 _private member_ `int32 SampleRate;` — Sample rate of the source
- L118 _private member_ `float SeekTime;` — Current seek time
- L121 _private member_ `FThreadSafeBool bInitialized;` — If we've initialized
- L124 _private member_ `bool bForceSyncDecode{false};` — force the decoding of this sound to be synchronous
- L203 _private member_ `FSourceInfo SourceInfo;`
- L206 _private member_ `FSineOsc SineTone[2];`

#### struct `Audio::FDecodingSoundSource::FSourceInfo`  
`struct FSourceInfo`  
_L127-201_
- desc: Object used for source generation from decoded buffers
- L130 _public member_ `int32 NumSourceChannels;` — Number of channels of source file
- L133 _public member_ `uint32 TotalNumFrames;` — Total number of frames of source file
- L136 _public member_ `uint32 NumFramesRead;` — Total number of frames played (or read from decoded buffers) so far. Will always be less than TotalNumFrames
- L139 _public member_ `uint32 NumFramesGenerated;` — Total number of frames generated (could be larger or smaller than number of frames read)
- L142 _public member_ `float CurrentFrameAlpha;` — The current frame alpha (how far we are between current and next frame)
- L145 _public member_ `int32 CurrentFrameIndex;` — The current frame index
- L148 _public member_ `int32 CurrentAudioChunkNumFrames;` — Number of frames of current decoded chunk
- L151 _public member_ `float BasePitchScale;` — The pitch scale to use to account for sample rate differences of source to output sample rate
- L152 _public member_ `float PitchScale;`
- L155 _public member_ `FParam PitchParam;` — The pitch param object, allows easy pitch interpolation
- L158 _public member_ `uint32 PitchResetFrame;` — The frame count (from frames generated) to reset the pitch param
- L161 _public member_ `FParam VolumeParam;` — The volume param object, allows easy volume interpolation
- L164 _public member_ `uint32 VolumeResetFrame;` — The frame count (from frames generated) to reset the volume param
- L167 _public member_ `TArray<float> CurrentFrameValues;` — Buffer to store current decoded audio frame
- L170 _public member_ `TArray<float> NextFrameValues;` — Buffer to store next decoded audio frame
- L173 _public member_ `TSharedPtr<FAlignedFloatBuffer, ESPMode::ThreadSafe> CurrentPCMBuffer;` — The current decoded PCM buffer we are reading from
- L176 _public member_ `bool bIsDone;` — If this sound is done (has decoded all data)
- L179 _public member_ `bool bHasStarted;` — If this sound hasn't yet started rendering audio
- L182 _public member_ `bool bIsLastBuffer;` — If this is the last decoded buffer
- L184 _public function_ `FSourceInfo() : NumSourceChannels(0) , TotalNumFrames(0) , NumFramesRead(0) , NumFramesGenerated(0) , CurrentFrameAlpha(0.0f) , CurrentFrameIndex(0) , CurrentAudioChunkNumFrames(0) , BasePitchScale(1.0f) , PitchScale(1.0f) , PitchResetFrame(0) , VolumeResetFrame(0) , bIsDone(false) , bHasStarted(false) , bIsLastBuffer(false)`

#### class `Audio::FSoundSourceDecoder`  
`class FSoundSourceDecoder : public FGCObject`  
_L213-278_
- inherits: `FGCObject`
- L216 _public prototype_ `FSoundSourceDecoder();`
- L217 _public prototype_ `virtual ~FSoundSourceDecoder();`
- L220 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector & Collector) override;`
- L221 _public function_ `virtual FString GetReferencerName() const override`
- L229 _public prototype_ `void Init(FAudioDevice* InAudioDevice, int32 SampleRate);` — Initialize the source decoder at the given output sample rate Sources will automatically sample rate convert to match this output
- L232 _public prototype_ `FDecodingSoundSourceHandle CreateSourceHandle(USoundWave* InSoundWave);` — Creates a new decoding sound source handle
- L235 _public prototype_ `void Update();` — Called from the audio thread
- L238 _public prototype_ `void UpdateRenderThread();` — Called from the audio render thread
- L241 _public prototype_ `bool InitDecodingSource(const FSourceDecodeInit& InitData);` — Initialize a decoding instance of this sound wave object. Call only from game thread.
- L244 _public prototype_ `void RemoveDecodingSource(const FDecodingSoundSourceHandle& Handle);` — Removes the decoding source from the decoder
- L247 _public prototype_ `void Reset();` — Resets internal state of decoder
- L250 _public prototype_ `void SetSourcePitchScale(const FDecodingSoundSourceHandle& Handle, float InPitchScale);` — Sets the source pitch scale
- L253 _public prototype_ `void SetSourceVolumeScale(const FDecodingSoundSourceHandle& Handle, float InVolumeScale);` — Sets the source volume scale
- L256 _public prototype_ `bool GetSourceBuffer(const FDecodingSoundSourceHandle& InHandle, const int32 NumOutFrames, const int32 NumOutChannels, FAlignedFloatBuffer& OutAudioBuffer);` — Get a decoded buffer for the given decoding sound wave handle. Call only from audio render thread or audio render thread task.
- L259 _public prototype_ `bool IsFinished(const FDecodingSoundSourceHandle& InHandle) const;` — Queries if the decoding source is finished
- L261 _public prototype_ `bool IsInitialized(const FDecodingSoundSourceHandle& InHandle) const;`
- L265 _private prototype_ `void EnqueueDecoderCommand(TFunction<void()> Command);` — Sends a command to the audio render thread from audio thread
- L266 _private prototype_ `void PumpDecoderCommandQueue();`
- L267 _private prototype_ `bool InitDecodingSourceInternal(const FSourceDecodeInit& InitData);`
- L269 _private member_ `int32 AudioThreadId;`
- L270 _private member_ `FAudioDevice* AudioDevice;`
- L271 _private member_ `int32 SampleRate;`
- L272 _private member_ `mutable FCriticalSection DecodingSourcesCritSec;`
- L273 _private member_ `TMap<int32, FDecodingSoundSourcePtr> InitializingDecodingSources;`
- L274 _private member_ `TMap<int32, FDecodingSoundSourcePtr> DecodingSources;`
- L275 _private member_ `TMap<int32, FSourceDecodeInit> PrecachingSources;`
- L277 _private member_ `TQueue<TFunction<void()>> CommandQueue;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define AUDIO_SOURCE_DECODER_DEBUG 0`
- L18 _namespace_ `namespace Audio`
- L211 _typedef_ `typedef TSharedPtr<FDecodingSoundSource> FDecodingSoundSourcePtr;` (scope `Audio`)
