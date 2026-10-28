# Plugins / MotoSynth

- module root: `Plugins/Experimental/MotoSynth/Source/MotoSynth`
- headers: 6; symbols: 303
- symbol kinds: class=11, delegate=1, function=3, macro=4, member=193, prototype=86, struct=4, typedef=1
- PrivateDependencyModuleNames: AudioMixer, SignalProcessing
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine

### `Plugins/Experimental/MotoSynth/Source/MotoSynth/Classes/SynthComponents/SynthComponentMoto.h` (Public)


#### class `USynthComponentMoto`  
`class USynthComponentMoto : public USynthComponent`  
_L13-55_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent`
- L18 _public prototype_ `USynthComponentMoto(const FObjectInitializer& ObjInitializer);`
- L19 _public prototype_ `virtual ~USynthComponentMoto();`
- L23 _public member_ `TObjectPtr<UMotoSynthPreset> MotoSynthPreset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotoSynth")` — The moto synth preset to use for the moto synth component.
- L27 _public member_ `float RPM = 1000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotoSynth", meta = (ClampMin = "500.0", ClampMax = "20000.0", UIMin = "500.0", UIMax = "20000.0"))` — Sets the starting RPM of the engine
- L31 _public prototype_ `void SetRPM(float InRPM, float InTimeSec);` — `UFUNCTION(BlueprintCallable, Category = "MotoSynth")` — Sets the RPM of the granular engine directly.
- L35 _public prototype_ `void SetSettings(const FMotoSynthRuntimeSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "MotoSynth")` — Sets a moto synth settings dynamically.
- L39 _public prototype_ `void GetRPMRange(float& OutMinRPM, float& OutMaxRPM);` — `UFUNCTION(BlueprintCallable, Category = "MotoSynth")` — Retrieves RPM range of the moto synth, taking into account the acceleration and deceleration sources. The min RPM is the largest of the min RPms of either and the max RPM is min of the max RPMs of either.
- L43 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "MotoSynth")` — Returns if the moto synth is enabled.
- L45 _public prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L48 _private prototype_ `FMotoSynthRuntimeSettings* GetSettingsToUse();`
- L50 _private member_ `FCriticalSection SettingsCriticalSection;`
- L51 _private member_ `FVector2D RPMRange;`
- L52 _private member_ `ISoundGeneratorPtr MotoSynthEngine;`
- L53 _private member_ `FMotoSynthRuntimeSettings OverrideSettings;`
- L54 _private member_ `bool bSettingsOverridden = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTOSYNTH_API`

### `Plugins/Experimental/MotoSynth/Source/MotoSynth/Private/MotoSynthDataManager.h` (Private)


#### struct `FMotoSynthSourceData`  
`struct FMotoSynthSourceData`  
_L9-28_
- L12 _public member_ `TArray<int16> AudioSource;` — The raw audio source used for the data
- L15 _public member_ `TArray<uint8> AudioSourceBitCrushed;` — Bit-crushed audio source data (reduced bit-size)
- L18 _public member_ `int32 SourceSampleRate = 0;` — The sample rate of the source file
- L21 _public member_ `FRichCurve RPMCurve;` — The RPM pitch curve used for the source
- L24 _public member_ `FName SourceName;` — The name of the source
- L27 _public member_ `TArray<FGrainTableEntry> GrainTable;` — The grain table derived during editor time

#### class `FMotoSynthSourceDataManager`  
`class FMotoSynthSourceDataManager`  
_L32-57_
- L35 _public prototype_ `static FMotoSynthSourceDataManager& Get();`
- L36 _public prototype_ `static void LogMemory();`
- L39 _public prototype_ `void RegisterData(uint32 InSourceID, const FName& InSourceName, TArray<int16>&& InSourceDataPCM, int32 InSourceSampleRate, TArray<FGrainTableEntry>&& InGrainTable, const FRichCurve& InRPMCurve, bool bConvertTo8Bit);` — Registers the moto synth source data
- L40 _public prototype_ `void UnRegisterData(uint32 InSourceID);`
- L44 _public prototype_ `MotoSynthDataPtr GetMotoSynthData(uint32 SourceID);` — Retrieves data view for the given SourceID if the source data exists. Returns true if the data existed for the SourceID, false if it did not.
- L47 _public prototype_ `void LogMemoryUsage();` — Logs the memory usage of this data manager
- L50 _private prototype_ `FMotoSynthSourceDataManager();`
- L51 _private prototype_ `~FMotoSynthSourceDataManager();`
- L53 _private member_ `TMap<uint32, MotoSynthDataPtr> SourceDataTable;`
- L55 _private member_ `FCriticalSection DataCriticalSection;`

#### Free symbols / members of external scopes

- L30 _typedef_ `typedef TSharedPtr<FMotoSynthSourceData, ESPMode::ThreadSafe> MotoSynthDataPtr;`

### `Plugins/Experimental/MotoSynth/Source/MotoSynth/Public/MotoSynthEngine.h` (Public)


#### class `FMotoSynthAssetManager`  
`class FMotoSynthAssetManager`  
_L17-26_
- L22 _public prototype_ `static FMotoSynthAssetManager& Get();` — Retrieves the moto synth asset manager
- L24 _public prototype_ `FMotoSynthAssetManager();`
- L25 _public prototype_ `~FMotoSynthAssetManager();`

#### struct `FGrainInitParams`  
`struct FGrainInitParams`  
_L28-38_
- L30 _public member_ `const Audio::FGrainEnvelope* GrainEnvelope = nullptr;`
- L31 _public member_ `TArrayView<const uint8> GrainView;`
- L32 _public member_ `uint8 NumBytesPerSample = 0;`
- L33 _public member_ `int32 NumSamplesCrossfade = 0;`
- L34 _public member_ `float GrainStartRPM = 0.0f;`
- L35 _public member_ `float GrainEndRPM = 0.0f;`
- L36 _public member_ `float StartingRPM = 0.0f;`
- L37 _public member_ `float EnginePitchScale = 0.0f;`

#### class `FMotoSynthGrainRuntime`  
`class FMotoSynthGrainRuntime`  
_L40-71_
- L43 _public prototype_ `void Init(const FGrainInitParams& InInitParams);`
- L46 _public prototype_ `float GenerateSample();` — Generates a sample from the grain. Returns true if fading out
- L49 _public prototype_ `bool IsNearingEnd() const;` — Returns true if the grain is nearing its end (and a new grain needs to start fading in
- L52 _public prototype_ `bool IsDone() const;` — If the grain is done
- L55 _public prototype_ `void SetRPM(int32 InRPM);` — Updates the grain's RPM
- L58 _private member_ `const Audio::FGrainEnvelope* GrainEnvelope = nullptr;`
- L59 _private member_ `TArrayView<const uint8> GrainArrayView;`
- L60 _private member_ `float CurrentSampleIndex = 0.0f;`
- L61 _private member_ `float FadeSamples = 0;`
- L62 _private member_ `float FadeOutStartIndex = 0.0f;`
- L63 _private member_ `float GrainPitchScale = 1.0f;`
- L64 _private member_ `float EnginePitchScale = 1.0f;`
- L65 _private member_ `float CurrentRuntimeRPM = 0.0f;`
- L66 _private member_ `float GrainRPMStart = 0.0f;`
- L67 _private member_ `float GrainRPMDelta = 0.0f;`
- L68 _private member_ `float StartingRPM = 0.0f;`
- L69 _private member_ `uint8 NumBytesPerSample = 2;`
- L70 _private member_ `int32 NumSamples = 0;`

#### class `IMotoSynthEngine`  
`class IMotoSynthEngine`  
_L73-77_
- L76 _public prototype_ `virtual void SetSettings(const FMotoSynthRuntimeSettings& InSettings) = 0;`

#### class `FMotoSynthEngine`  
`class FMotoSynthEngine : public ISoundGenerator, public IMotoSynthEngine`  
_L80-207_
- inherits: `ISoundGenerator,IMotoSynthEngine`
- desc: Class for granulating an engine
- L84 _public prototype_ `FMotoSynthEngine();`
- L85 _public prototype_ `~FMotoSynthEngine();`
- L88 _public prototype_ `static bool IsMotoSynthEngineEnabled();` — Queries if the engine is enabled at all. Checks a cvar.
- L91 _public prototype_ `void SetSettings(const FMotoSynthRuntimeSettings& InSettings) final;`
- L95 _public function_ `virtual int32 GetDesiredNumSamplesToRenderPerCallback() const`
- L96 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;`
- L99 _public prototype_ `void Init(int32 InSampleRate);`
- L100 _public prototype_ `void Reset();`
- L103 _public prototype_ `void SetSourceData(uint32 AccelerationSourceID, uint32 DecelerationSourceID);` — Sets all the source data for the moto synth
- L106 _public prototype_ `void GetRPMRange(FVector2D& OutRPMRange);` — Returns the min and max RPM range, taking into account the acceleration and deceleration data.
- L109 _public prototype_ `void SetRPM(float InRPM, float InTimeSec = 0.0f);` — Sets the RPM directly. Used if the engine is in ManualRPM mode. Will be ignored if we're in simulation mode.
- L112 _public prototype_ `void SetPitchScale(float InPitchScale);` — Sets a pitch scale on the moto synth to scale up or down the pitch of the output
- L115 _private prototype_ `void GenerateGranularEngine(float* OutAudio, int32 NumSamples);`
- L117 _private prototype_ `bool NeedsSpawnGrain();`
- L118 _private prototype_ `void SpawnGrain(int32& StartingIndex, const MotoSynthDataPtr& SynthData);`
- L120 _private member_ `float RendererSampleRate = 0.0f;`
- L123 _private member_ `float CurrentRPM = 0.0f;` — The current RPM state
- L124 _private member_ `float PreviousRPM = 0.0f;`
- L125 _private member_ `float CurrentRPMSlope = 0.0f;`
- L126 _private member_ `float PreviousRPMSlope = 0.0f;`
- L127 _private member_ `float TargetRPM = 0.0f;`
- L128 _private member_ `float StartingRPM = 0.0f;`
- L129 _private member_ `float RPMFadeTime = 0.0f;`
- L130 _private member_ `float CurrentRPMTime = 0.0f;`
- L131 _private member_ `float PitchScale = 1.0f;`
- L133 _private member_ `int32 CurrentAccelerationSourceDataIndex = 0;`
- L134 _private member_ `int32 CurrentDecelerationSourceDataIndex = 0;`
- L137 _private member_ `MotoSynthDataPtr AccelerationSourceData;` — The source data
- L138 _private member_ `MotoSynthDataPtr DecelerationSourceData;`
- L140 _private member_ `FVector2f RPMRange;`
- L141 _private member_ `FVector2f RPMRange_RendererCallback;`
- L144 _private member_ `int32 GrainCrossfadeSamples = 10;` — Number of samples to use to do a grain crossfade. Smooths out discontinuities on grain boundaries.
- L145 _private member_ `int32 NumGrainTableEntriesPerGrain = 3;`
- L146 _private member_ `int32 GrainTableRandomOffsetForConstantRPMs = 20;`
- L147 _private member_ `int32 GrainCrossfadeSamplesForConstantRPMs = 40;`
- L150 _private member_ `TArray<FMotoSynthGrainRuntime> GrainPool;` — The grain pool for runtime generation of audio
- L153 _private member_ `TArray<int32> ActiveGrains;` — The grain state management arrays
- L154 _private member_ `TArray<int32> FreeGrains;` — Grain indicies which are free to be used. max size should be equal to grain pool size.
- L156 _private member_ `TArray<float> SynthBuffer;`
- L157 _private member_ `FVector2f SynthFilterFreqRange = { 100.0f, 5000.0f };`
- L158 _private member_ `Audio::FLadderFilter SynthFilter;`
- L159 _private member_ `Audio::FOsc SynthOsc;`
- L160 _private member_ `Audio::FADEnvelope SynthEnv;`
- L161 _private member_ `Audio::AlignedFloatBuffer SynthEnvBuffer;`
- L163 _private member_ `Audio::FBiquadFilter NoiseFilter;`
- L164 _private member_ `Audio::FWhiteNoise NoiseGen;`
- L165 _private member_ `Audio::FADEnvelope NoiseEnv;`
- L166 _private member_ `Audio::AlignedFloatBuffer NoiseEnvBuffer;`
- L168 _private member_ `int32 SynthPitchUpdateSampleIndex = 0;`
- L169 _private member_ `int32 SynthPitchUpdateDeltaSamples = 1023;`
- L172 _private member_ `Audio::FDelayStereo DelayStereo;` — Stereo delay to "widen" the moto synth output
- L175 _private member_ `Audio::FGrainEnvelope GrainEnvelope;` — Grain Envelope buffer
- L178 _private member_ `TArray<float> GrainEngineBuffer;` — Mono scratch buffer for engine generation
- L180 _private member_ `FVector2f SynthToneVolumeRange = { 0.0f, 0.0f };`
- L181 _private member_ `FVector2f SynthToneFilterFrequencyRange = { 500.0f, 500.0f };`
- L182 _private member_ `FVector2f SynthToneAttackTimeMsecRange = { 10.0f, 10.0f };`
- L183 _private member_ `FVector2f SynthToneDecayTimeMsecRange = { 100.0f, 100.0f };`
- L184 _private member_ `FVector2f SynthToneAttackCurveRange = { 1.0f, 1.0f };`
- L185 _private member_ `FVector2f SynthToneDecayCurveRange = { 1.0f, 1.0f };`
- L187 _private member_ `FVector2f NoiseVolumeRange = { 0.0f, 0.0f };`
- L188 _private member_ `FVector2f NoiseLPFRange = { 0.0f, 0.0f };`
- L189 _private member_ `FVector2f NoiseAttackTimeMsecRange = { 10.0f, 10.0f };`
- L190 _private member_ `FVector2f NoiseAttackCurveRange = { 1.0f, 1.0f };`
- L191 _private member_ `FVector2f NoiseDecayTimeMsecRange = { 10.0f, 10.0f };`
- L192 _private member_ `FVector2f NoiseDecayCurveRange = { 1.0f, 1.0f };`
- L194 _private member_ `int32 SynthOctaveShift = 0;`
- L195 _private member_ `float GranularEngineVolume = 1.0f;`
- L196 _private member_ `float TargetGranularEngineVolume = 1.0f;`
- L198 _private member_ `bool bWasAccelerating = false;`
- L199 _private member_ `bool bSynthToneEnabled = false;`
- L200 _private member_ `bool bSynthToneEnvelopeEnabled = false;`
- L201 _private member_ `bool bNoiseEnabled = false;`
- L202 _private member_ `bool bNoiseEnvelopeEnabled = false;`
- L203 _private member_ `bool bGranularEngineEnabled = true;`
- L204 _private member_ `bool bStereoWidenerEnabled = true;`
- L205 _private member_ `bool bRPMWasSet = false;`
- L206 _private member_ `bool bUpdateRPMCalculations = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOTOSYNTH_API`

### `Plugins/Experimental/MotoSynth/Source/MotoSynth/Public/MotoSynthModule.h` (Public)


#### class `FMotoSynthModule`  
`class FMotoSynthModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotoSynth, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotoSynth, Log, All);`

### `Plugins/Experimental/MotoSynth/Source/MotoSynth/Public/MotoSynthPreset.h` (Public)


#### struct `FMotoSynthRuntimeSettings`  
`struct FMotoSynthRuntimeSettings`  
_L17-168_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `bool bSynthToneEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth")` — If the synth tone is enabled
- L27 _public member_ `float SynthToneVolume_DEPRECATED = 0.0f;` — `UPROPERTY()`
- L30 _public member_ `float SynthToneFilterFrequency_DEPRECATED = 0.0f;` — `UPROPERTY()`
- L35 _public member_ `FVector2D SynthToneVolumeRange = { 0.0f, 0.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bSynthToneEnabled"))` — The volume of the synth tone	between min and max RPM
- L39 _public member_ `FVector2D SynthToneFilterFrequencyRange = { 500.0f, 500.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bSynthToneEnabled"))` — The filter frequency of the synth tone between min/max RPM
- L43 _public member_ `bool bSynthToneEnvelopeEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bSynthToneEnabled"))` — Enable the synth tone envelope generator
- L47 _public member_ `FVector2D SynthToneAttackTimeMsecRange = { 10.0f, 10.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bSynthToneEnabled"))` — Synth tone envelope attack time in milliseconds between min/max RPM
- L51 _public member_ `FVector2D SynthToneAttackCurveRange = { 1.0f, 1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bSynthToneEnabled"))` — Synth tone envelope attack curve.  1.0 = linear growth, < 1.0 logorithmic growth, > 1.0 exponential growth.
- L55 _public member_ `FVector2D SynthToneDecayTimeMsecRange = { 100.0f, 100.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bSynthToneEnabled"))` — Synth tone decay time in milliseconds
- L59 _public member_ `FVector2D SynthToneDecayCurveRange = { 1.0f, 1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bSynthToneEnabled"))` — Synth tone envelope decay curve.  1.0 = linear decay, < 1.0 exponential decay, > 1.0 logarithmic decay.
- L63 _public member_ `int32 SynthOctaveShift = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (ClampMin = "-3", ClampMax = "3", UIMin = "-3", UIMax = "3", EditCondition = "bSynthToneEnabled"))` — Octave shift of the synth
- L67 _public member_ `bool bNoiseEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth")` — If the noise generator enabled
- L71 _public member_ `FVector2D NoiseVolumeRange = { 1.0f, 1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bNoiseEnabled"))` — The volume of the noise source
- L75 _public member_ `bool bNoiseEnvelopeEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bNoiseEnabled"))` — If the noise generator has the envelope enabled
- L79 _public member_ `FVector2D NoiseLPFRange = { 500.0f, 500.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bNoiseEnabled"))` — The filter frequency of the noise generator between min/max RPM
- L83 _public member_ `FVector2D NoiseAttackTimeMsecRange = { 10.0f, 10.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bNoiseEnabled"))` — Noise envelope attack time in milliseconds between min/max RPM
- L87 _public member_ `FVector2D NoiseAttackCurveRange = { 1.0f, 1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bNoiseEnabled"))` — Noise envelope attack curve.  1.0 = linear growth, < 1.0 logorithmic growth, > 1.0 exponential growth.
- L91 _public member_ `FVector2D NoiseDecayTimeMsecRange = { 10.0f, 10.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bNoiseEnabled"))` — Noise envelope attack time in milliseconds between min/max RPM
- L95 _public member_ `FVector2D NoiseDecayCurveRange = { 1.0f, 1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth", meta = (EditCondition = "bNoiseEnabled"))` — Noise envelope attack curve between min/max RPM.  1.0 = linear growth, < 1.0 logorithmic growth, > 1.0 exponential growth.
- L99 _public member_ `bool bGranularEngineEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Granular Engine")` — If the granular engine is enabled
- L103 _public member_ `float GranularEngineVolume = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Granular Engine", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bGranularEngineEnabled"))` — The volume of the granular engine
- L107 _public member_ `float GranularEnginePitchScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Granular Engine", meta = (ClampMin = "0.001", UIMin = "0.001", EditCondition = "bGranularEngineEnabled"))` — The pitch scale of the granular engine
- L111 _public member_ `int32 NumSamplesToCrossfadeBetweenGrains = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Granular Engine", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bGranularEngineEnabled"))` — The volume of the granular engine
- L115 _public member_ `int32 NumGrainTableEntriesPerGrain = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Granular Engine", meta = (ClampMin = "1", ClampMax = "20", UIMin = "1", UIMax = "20", EditCondition = "bGranularEngineEnabled"))` — How many grain-table entries to use per runtime grain
- L119 _public member_ `int32 GrainTableRandomOffsetForConstantRPMs = 20;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Granular Engine", meta = (ClampMin = "0", ClampMax = "50", UIMin = "0", UIMax = "50", EditCondition = "bGranularEngineEnabled"))` — Random grain table offset for cases where RPM is constant. Allows random shuffling of grains to avoid a robotic sound.
- L123 _public member_ `int32 GrainCrossfadeSamplesForConstantRPMs = 20;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Granular Engine", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bGranularEngineEnabled"))` — Number of samples to cross fade grains when on a constant-RPM state. More crossfaded samples can reduce the robotic sound.
- L127 _public member_ `TObjectPtr<UMotoSynthSource> AccelerationSource = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Granular Engine", meta = (EditCondition = "bGranularEngineEnabled"))` — Motosynth source to use for granular engine acceleration
- L131 _public member_ `TObjectPtr<UMotoSynthSource> DecelerationSource = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Granular Engine", meta = (EditCondition = "bGranularEngineEnabled"))` — Motosynth source to use for granular engine deceleration
- L135 _public member_ `bool bStereoWidenerEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")` — If the stereo widener is enabled
- L139 _public member_ `float StereoDelayMsec = 25.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0", EditCondition = "bStereoWidenerEnabled"))` — If the stereo widener is enabled
- L143 _public member_ `float StereoFeedback = 0.37f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bStereoWidenerEnabled"))` — Amount of feedback for stereo widener
- L147 _public member_ `float StereoWidenerWetlevel = 0.68f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bStereoWidenerEnabled"))` — Wet level of stereo delay used for stereo widener
- L151 _public member_ `float StereoWidenerDryLevel = 0.8f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bStereoWidenerEnabled"))` — Dry level of stereo delay used for stereo widener
- L155 _public member_ `float StereoWidenerDelayRatio = 0.43f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bStereoWidenerEnabled"))` — Delay ratio of left/right channels for stereo widener effect
- L159 _public member_ `bool bStereoWidenerFilterEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (EditCondition = "bStereoWidenerEnabled"))` — Delay ratio of left/right channels for stereo widener effect
- L163 _public member_ `float StereoWidenerFilterFrequency = 4000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ClampMin = "20.0", ClampMax = "20000.0", UIMin = "20.0", UIMax = "20000.0", EditCondition = "bStereoWidenerEnabled && bStereoWidenerFilterEnabled"))` — Delay ratio of left/right channels for stereo widener effect
- L167 _public member_ `float StereoWidenerFilterQ = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ClampMin = "0.0", ClampMax = "2.0", UIMin = "0.0", UIMax = "2.0", EditCondition = "bStereoWidenerEnabled && bStereoWidenerFilterEnabled"))` — Delay ratio of left/right channels for stereo widener effect

#### class `FMotoSynthEnginePreviewer`  
`class FMotoSynthEnginePreviewer : public ISubmixBufferListener`  
_L176-212_
- inherits: `ISubmixBufferListener`
- desc: FMotoSynthEnginePreviewer Class used to render the moto synth audio in the content browser. Used to preview the moto synth engine without running PIE.
- L179 _public prototype_ `FMotoSynthEnginePreviewer();`
- L182 _public prototype_ `void StartPreviewing();`
- L183 _public prototype_ `void StopPreviewing();`
- L184 _public prototype_ `void Reset();`
- L186 _public prototype_ `void SetSettings(const FMotoSynthRuntimeSettings& InSettings);`
- L187 _public prototype_ `void SetPreviewRPMCurve(const FRichCurve& InRPMCurve);`
- L190 _public prototype_ `void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 InSampleRate, double AudioClock) override;` — ISubmixBufferListener
- L191 _public prototype_ `const FString& GetListenerName() const override;`
- L195 _private member_ `FCriticalSection PreviewEngineCritSect;`
- L196 _private member_ `FRichCurve PreviewRPMCurve;`
- L198 _private member_ `float CurrentPreviewCurveStartTime = 0.0f;`
- L199 _private member_ `float CurrentPreviewCurveTime = 0.0f;`
- L201 _private member_ `TArray<float> OutputBuffer;`
- L202 _private member_ `TUniquePtr<FMotoSynthEngine> SynthEngine;`
- L204 _private member_ `FVector2D RPMRange;`
- L206 _private member_ `UMotoSynthPreset* MotoSynthPreset;`
- L207 _private member_ `FMotoSynthRuntimeSettings Settings;`
- L209 _private member_ `bool bRegistered = false;`
- L210 _private member_ `bool bEngineInitialized = false;`
- L211 _private member_ `bool bPreviewFinished = false;`

#### class `UMotoSynthPreset`  
`class UMotoSynthPreset : public UObject`  
_L219-255_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `UObject`
- desc: Asset used to store moto synth preset data.
- L225 _public prototype_ `virtual void BeginDestroy() override;`
- L226 _public prototype_ `virtual void PostLoad() override;`
- L231 _public member_ `FRuntimeFloatCurve EnginePreviewRPMCurve;` — `UPROPERTY(EditAnywhere, Category = "Engine Preview")` — Engine preview RPM curve
- L235 _public member_ `FMotoSynthRuntimeSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotoSynthSettings, Meta = (ShowOnlyInnerProperties))`
- L239 _public prototype_ `void StartEnginePreview();` — `UFUNCTION(Category = "Engine Preview", meta = (CallInEditor = "true"))`
- L242 _public prototype_ `void StopEnginePreview();` — `UFUNCTION(Category = "Engine Preview", meta = (CallInEditor = "true"))`
- L246 _public prototype_ `void DumpRuntimeMemoryUsage();` — `UFUNCTION(Category = "Memory", meta = (CallInEditor = "true"))` — Dumps memory usage of the preset (i.e. of the source assets)
- L248 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L253 _public member_ `TSharedRef<FMotoSynthEnginePreviewer> EnginePreviewer = MakeShared<FMotoSynthEnginePreviewer>();` — The engine previewer which is using this preset

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTOSYNTH_API`

### `Plugins/Experimental/MotoSynth/Source/MotoSynth/Public/MotoSynthSourceAsset.h` (Public)


#### struct `FGrainTableEntry`  
`struct FGrainTableEntry`  
_L18-33_
- reflection: `USTRUCT()`
- L23 _public member_ `int32 SampleIndex = 0;` — `UPROPERTY()`
- L27 _public member_ `float RPM = 0.0f;` — `UPROPERTY()` — The RPM of the grain when it starts
- L31 _public member_ `int32 AnalysisSampleIndex = 0;` — `UPROPERTY()`

#### class `FRPMEstimationPreviewTone`  
`class FRPMEstimationPreviewTone : public ISubmixBufferListener`  
_L37-70_
- inherits: `ISubmixBufferListener`
- desc: Class for playing a match tone for estimating RPMs
- L40 _public prototype_ `FRPMEstimationPreviewTone();`
- L41 _public prototype_ `virtual ~FRPMEstimationPreviewTone();`
- L43 _public prototype_ `void StartTestTone(float InVolume);`
- L44 _public prototype_ `void StopTestTone();`
- L46 _public prototype_ `void Reset();`
- L47 _public prototype_ `void SetAudioFile(TArrayView<const int16>& InAudioFile, int32 SampleRate);`
- L48 _public prototype_ `void SetPitchCurve(FRichCurve& InRPMCurve);`
- L49 _public function_ `bool IsDone() const`
- L52 _public prototype_ `virtual void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override;` — ISubmixBufferListener
- L53 _public prototype_ `virtual const FString& GetListenerName() const override;`
- L58 _private member_ `FCriticalSection CallbackCritSect;` — Critical section used to set params from game thread while synth is running
- L61 _private member_ `TArray<float> ScratchBuffer;` — Scratch buffer to generate audio into
- L62 _private member_ `TArrayView<const int16> AudioFileBuffer;`
- L63 _private member_ `Audio::FOsc Osc;`
- L64 _private member_ `Audio::FLadderFilter Filter;`
- L65 _private member_ `int32 SampleRate = 0;`
- L66 _private member_ `FRichCurve RPMCurve;`
- L67 _private member_ `int32 CurrentFrame = 0;`
- L68 _private member_ `float VolumeScale = 1.0f;`
- L69 _private member_ `bool bRegistered = false;`

#### class `UMotoSynthSource`  
`class UMotoSynthSource : public UObject`  
_L78-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: UMotoSynthSource UAsset used to represent Imported MotoSynth Sources
- L83 _public prototype_ `UMotoSynthSource();`
- L84 _public prototype_ `~UMotoSynthSource();`
- L89 _public prototype_ `virtual void BeginDestroy() override;` — Needed to remove the data entry in the data manager
- L92 _public prototype_ `virtual void PostLoad() override;` — Used to register data w/ the data manager
- L98 _public member_ `TObjectPtr<USoundWave> SoundWaveSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grain Table | Analysis")` — The source to use for the moto synth source
- L103 _public member_ `bool bConvertTo8Bit = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory")` — Whether or not to convert this moto synth source to 8 bit on load to use less memory
- L107 _public member_ `float DownSampleFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount to scale down the sample rate of the source
- L112 _public member_ `FRuntimeFloatCurve RPMCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grain Table | Analysis")` — A curve to define the RPM contour from the min and max estimated RPM Curve values are non-normalized and accurate to time
- L118 _public member_ `float RPMSynthVolume = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grain Table | Analysis")` — Sets the volume of the RPM curve synth for testing RPM curve to source
- L122 _public member_ `bool bEnableFilteringForAnalysis = true;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Filtering")` — Whether not to enable a low pass filter frequency before analyzing the audio file
- L126 _public member_ `float LowPassFilterFrequency = 500.0f;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Filtering", meta = (ClampMin = "0.0", ClampMax = "20000.0", EditCondition = "bEnableFiltering"))` — Frequency of a low pass filter to apply before running grain table analysis
- L130 _public member_ `float HighPassFilterFrequency = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Filtering", meta = (ClampMin = "0.0", ClampMax = "20000.0", EditCondition = "bEnableFiltering"))` — Whether not to enable a low pass filter frequency before analyzing the audio file
- L134 _public member_ `bool bEnableDynamicsProcessorForAnalysis = true;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Dynamics Processor")` — Whether not to enable a dynamics processor to the analysis step
- L137 _public member_ `float DynamicsProcessorLookahead = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grain Table | Dynamics Processor", meta = (ClampMin = "0.0", ClampMax = "50.0", UIMin = "0.0", UIMax = "50.0", EditCondition = "bEnableDynamicsProcessor"))`
- L140 _public member_ `float DynamicsProcessorInputGainDb = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Dynamics Processor", meta = (ClampMin = "-20.0", ClampMax = "100.0", EditCondition = "bEnableDynamicsProcessor"))`
- L143 _public member_ `float DynamicsProcessorRatio = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Dynamics Processor", meta = (ClampMin = "1.0", ClampMax = "20.0", EditCondition = "bEnableDynamicsProcessor"))`
- L146 _public member_ `float DynamicsKneeBandwidth = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grain Table | Dynamics Processor", meta = (ClampMin = "0.0", ClampMax = "20.0", UIMin = "0.0", UIMax = "20.0", EditCondition = "bEnableDynamicsProcessor"))`
- L149 _public member_ `float DynamicsProcessorThreshold = -6.0f;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Dynamics Processor", meta = (ClampMin = "-60.0", ClampMax = "0.0", EditCondition = "bEnableDynamicsProcessor"))`
- L152 _public member_ `float DynamicsProcessorAttackTimeMsec = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Dynamics Processor", meta = (ClampMin = "0.0", ClampMax = "5000.0", EditCondition = "bEnableDynamicsProcessor"))`
- L155 _public member_ `float DynamicsProcessorReleaseTimeMsec = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Dynamics Processor", meta = (ClampMin = "0.0", ClampMax = "5000.0", EditCondition = "bEnableDynamicsProcessor"))`
- L158 _public member_ `bool bEnableNormalizationForAnalysis = true;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Normalization")`
- L161 _public member_ `int32 SampleShiftOffset = 68;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Grain Table Algorithm")`
- L165 _public member_ `int32 RPMCycleCalibrationSample = 0;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Grain Table Algorithm")` — A samples to use to calibrate when an engine cycle begins
- L169 _public member_ `int32 RPMFirstCycleSampleEnd = 0;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Grain Table Algorithm")` — The end of the first cycle sample. Cut the source file to start exactly on the cycle start
- L172 _public member_ `int32 RPMEstimationOctaveOffset = 0;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | Grain Table Algorithm")`
- L176 _public member_ `bool bWriteAnalysisInputToFile = true;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | File Writing")` — Whether not to write the audio used for analysis to a wav file
- L180 _public member_ `FString AnalysisInputFilePath;` — `UPROPERTY(EditAnywhere, Category = "Grain Table | File Writing", meta = (EditCondition = "bWriteAnalysisInputToFile"))` — The path to write the audio analysis data (LPF and normalized asset)
- L185 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L188 _public prototype_ `void PerformGrainTableAnalysis();` — `UFUNCTION(Category = "Grain Table", meta = (CallInEditor = "true"))`
- L191 _public prototype_ `void PlayToneMatch();` — `UFUNCTION(Category = "Grain Table", meta = (CallInEditor = "true"))`
- L194 _public prototype_ `void StopToneMatch();` — `UFUNCTION(Category = "Grain Table", meta = (CallInEditor = "true"))`
- L197 _public prototype_ `void UpdateSourceData();` — Updates the source data from the associated USoundWave
- L202 _public function_ `uint32 GetDataID() const` — Retrieves the data ID of the source in the moto synth data manager
- L205 _public prototype_ `float GetRuntimeMemoryUsageMB() const;` — Retrieves the memory usage of this in MB that will be used at runtime (i.e. from data manager)
- L209 _protected prototype_ `uint32 GetNextSourceID() const;`
- L210 _protected prototype_ `void RegisterSourceData();`
- L213 _protected prototype_ `float GetCurrentRPMForSampleIndex(int32 CurrentSampleIndex);`
- L214 _protected prototype_ `void FilterSourceDataForAnalysis();`
- L215 _protected prototype_ `void DynamicsProcessForAnalysis();`
- L216 _protected prototype_ `void NormalizeForAnalysis();`
- L217 _protected prototype_ `void BuildGrainTableByRPMEstimation();`
- L218 _protected prototype_ `void BuildGrainTableByFFT();`
- L220 _protected prototype_ `void WriteDebugDataToWaveFiles();`
- L221 _protected prototype_ `void WriteAnalysisBufferToWaveFile();`
- L222 _protected prototype_ `void WriteGrainTableDataToWaveFile();`
- L226 _protected member_ `Audio::FAlignedFloatBuffer AnalysisBuffer;`
- L231 _protected member_ `TArray<float> SourceData_DEPRECATED;` — `UPROPERTY()` — Data containing PCM audio of the imported source asset (filled out by the factory)
- L234 _protected member_ `TArray<int16> SourceDataPCM;` — `UPROPERTY()`
- L238 _protected member_ `int32 SourceSampleRate = 0;` — `UPROPERTY()` — Sample rate of the imported sound wave and the serialized data of the granulator
- L242 _protected member_ `TArray<FGrainTableEntry> GrainTable;` — `UPROPERTY()` — Grain table containing information about how to granulate the source data buffer.
- L245 _protected member_ `TSharedPtr<FRPMEstimationPreviewTone, ESPMode::ThreadSafe> MotoSynthSineToneTest;`
- L249 _protected member_ `uint32 SourceDataID = INDEX_NONE;` — Data ID used to track the source data with the data manager

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOTOSYNTH_API`
