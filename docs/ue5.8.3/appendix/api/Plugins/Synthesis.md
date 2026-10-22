# Plugins / Synthesis

- module root: `Plugins/Runtime/Synthesis/Source/Synthesis`
- headers: 47; symbols: 2095
- symbol kinds: class=77, delegate=13, enum=38, enumerator=206, function=66, macro=37, member=786, namespace=18, prototype=791, struct=52, typedef=11
- PrivateDependencyModuleNames: AudioMixer, AudioSynesthesiaCore, InputCore, Projects, SignalProcessing, Slate, SlateCore, UMG
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectBitCrusher.h` (Public)


#### struct `FSourceEffectBitCrusherBaseSettings`  
`struct FSourceEffectBitCrusherBaseSettings`  
_L17-28_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `float SampleRate = 8000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "0.1", ClampMax = "96000.0", UIMin = "500.0", UIMax = "16000.0"))` — The reduced frequency to use for the audio stream.
- L27 _public member_ `float BitDepth = 8.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "1.0", ClampMax = "24.0", UIMin = "1.0", UIMax = "16.0"))` — The reduced bit depth to use for the audio stream

#### struct `FSourceEffectBitCrusherSettings`  
`struct FSourceEffectBitCrusherSettings`  
_L31-48_
- reflection: `USTRUCT(BlueprintType)`
- L37 _public member_ `FSoundModulationDestinationSettings SampleRateModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BitCrusher, meta = (DisplayName = "Sample Rate", AudioParam = "SampleRate", AudioParamClass = "SoundModulationParameterFrequency", ClampMin = "0.1", ClampMax = "96000.0", UIMin = "500.0", UIMax = "16000.0"))` — The reduced frequency to use for the audio stream.
- L41 _public member_ `FSoundModulationDestinationSettings BitModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BitCrusher, meta = (DisplayName = "Bit Depth", AudioParam = "BitDepth", AudioParamClass = "SoundModulationParameterScaled", ClampMin = "1.0", ClampMax = "24.0", UIMin = "1.0", UIMax = "16.0"))` — The reduced bit depth to use for the audio stream
- L43 _public function_ `FSourceEffectBitCrusherSettings()`

#### class `FSourceEffectBitCrusher`  
`class FSourceEffectBitCrusher : public FSoundEffectSource`  
_L50-75_
- inherits: `FSoundEffectSource`
- L54 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L57 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L60 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L62 _public prototype_ `void SetBitModulator(const USoundModulatorBase* Modulator);`
- L63 _public prototype_ `void SetBitModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L65 _public prototype_ `void SetSampleRateModulator(const USoundModulatorBase* Modulator);`
- L66 _public prototype_ `void SetSampleRateModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L69 _protected member_ `Audio::FBitCrusher BitCrusher;`
- L71 _protected member_ `FSourceEffectBitCrusherSettings SettingsCopy;`
- L73 _protected member_ `Audio::FModulationDestination SampleRateMod;`
- L74 _protected member_ `Audio::FModulationDestination BitMod;`

#### class `USourceEffectBitCrusherPreset`  
`class USourceEffectBitCrusherPreset : public USoundEffectSourcePreset`  
_L78-116_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L83 _public prototype_ `EFFECT_PRESET_METHODS(SourceEffectBitCrusher) virtual void OnInit() override;`
- L87 _public function_ `virtual FColor GetPresetColor() const override`
- L90 _public prototype_ `void SetBits(float Bits);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)`
- L93 _public prototype_ `void SetBitModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)`
- L96 _public prototype_ `void SetBitModulators(const TSet<USoundModulatorBase*>& InModulators);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)`
- L99 _public prototype_ `void SetSampleRate(float SampleRate);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)`
- L102 _public prototype_ `void SetSampleRateModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)`
- L105 _public prototype_ `void SetSampleRateModulators(const TSet<USoundModulatorBase*>& InModulators);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)`
- L109 _public prototype_ `void SetSettings(const FSourceEffectBitCrusherBaseSettings& Settings);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)` — Sets just base (i.e. carrier) setting values without modifying modulation source references
- L112 _public prototype_ `void SetModulationSettings(const FSourceEffectBitCrusherSettings& ModulationSettings);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPreset)`
- L115 _public member_ `FSourceEffectBitCrusherSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectChorus.h` (Public)


#### struct `FSourceEffectChorusBaseSettings`  
`struct FSourceEffectChorusBaseSettings`  
_L14-41_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `float Depth = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The depth of the chorus effect
- L24 _public member_ `float Frequency = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (UIMin = "0.0", UIMax = "5.0"))` — The frequency of the chorus effect
- L28 _public member_ `float Feedback = 0.3f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The feedback of the chorus effect
- L32 _public member_ `float WetLevel = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The wet level of the chorus effect
- L36 _public member_ `float DryLevel = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The dry level of the chorus effect
- L40 _public member_ `float Spread = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The spread of the effect (larger means greater difference between left and right delay lines)

#### struct `FSourceEffectChorusSettings`  
`struct FSourceEffectChorusSettings`  
_L44-99_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `float Depth = 0.2f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L52 _public member_ `float Frequency = 2.0f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L55 _public member_ `float Feedback = 0.3f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L58 _public member_ `float WetLevel = 0.5f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L61 _public member_ `float DryLevel = 0.5f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L64 _public member_ `float Spread = 0.0f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L68 _public member_ `FSoundModulationDestinationSettings DepthModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chorus, meta = (DisplayName = "Depth", AudioParamClass = "SoundModulationParameter", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The depth of the chorus effect
- L72 _public member_ `FSoundModulationDestinationSettings FrequencyModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chorus, meta = (DisplayName = "Frequency (hz)", AudioParam = "LowRateFrequency", AudioParamClass = "SoundModulationParameterFrequency", UIMin = "0.0", UIMax = "5.0"))` — The frequency of the chorus effect
- L76 _public member_ `FSoundModulationDestinationSettings FeedbackModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chorus, meta = (DisplayName = "Feedback", AudioParamClass = "SoundModulationParameter", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The feedback of the chorus effect
- L80 _public member_ `FSoundModulationDestinationSettings WetModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chorus, meta = (DisplayName = "Wet Level", AudioParamClass = "SoundModulationParameterVolume", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The wet level of the chorus effect
- L84 _public member_ `FSoundModulationDestinationSettings DryModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chorus, meta = (DisplayName = "Dry Level", AudioParamClass = "SoundModulationParameterVolume", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The dry level of the chorus effect
- L88 _public member_ `FSoundModulationDestinationSettings SpreadModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chorus, meta = (DisplayName = "Spread", AudioParamClass = "SoundModulationParameter", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The spread of the effect (larger means greater difference between left and right delay lines)
- L90 _public function_ `FSourceEffectChorusSettings()`

#### class `FSourceEffectChorus`  
`class FSourceEffectChorus : public FSoundEffectSource`  
_L101-138_
- inherits: `FSoundEffectSource`
- L105 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L108 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L111 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L113 _public prototype_ `void SetDepthModulator(const USoundModulatorBase* InModulator);`
- L114 _public prototype_ `void SetFeedbackModulator(const USoundModulatorBase* InModulator);`
- L115 _public prototype_ `void SetFrequencyModulator(const USoundModulatorBase* InModulator);`
- L116 _public prototype_ `void SetWetModulator(const USoundModulatorBase* InModulator);`
- L117 _public prototype_ `void SetDryModulator(const USoundModulatorBase* InModulator);`
- L118 _public prototype_ `void SetSpreadModulator(const USoundModulatorBase* InModulator);`
- L120 _public prototype_ `void SetDepthModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L121 _public prototype_ `void SetFeedbackModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L122 _public prototype_ `void SetSpreadModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L123 _public prototype_ `void SetDryModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L124 _public prototype_ `void SetWetModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L125 _public prototype_ `void SetFrequencyModulators(const TSet<USoundModulatorBase*>& InModulators);`
- L128 _protected member_ `Audio::FChorus Chorus;`
- L130 _protected member_ `FSourceEffectChorusSettings SettingsCopy;`
- L132 _protected member_ `Audio::FModulationDestination DepthMod;`
- L133 _protected member_ `Audio::FModulationDestination FeedbackMod;`
- L134 _protected member_ `Audio::FModulationDestination FrequencyMod;`
- L135 _protected member_ `Audio::FModulationDestination WetMod;`
- L136 _protected member_ `Audio::FModulationDestination DryMod;`
- L137 _protected member_ `Audio::FModulationDestination SpreadMod;`

#### class `USourceEffectChorusPreset`  
`class USourceEffectChorusPreset : public USoundEffectSourcePreset`  
_L141-215_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L146 _public function_ `EFFECT_PRESET_METHODS(SourceEffectChorus) virtual FColor GetPresetColor() const override`
- L150 _public prototype_ `virtual void OnInit() override;`
- L153 _public prototype_ `void SetDepth(float Depth);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L156 _public prototype_ `void SetDepthModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L159 _public prototype_ `void SetDepthModulators(const TSet<USoundModulatorBase*>& Modulators);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L162 _public prototype_ `void SetFeedback(float Feedback);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L165 _public prototype_ `void SetFeedbackModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L168 _public prototype_ `void SetFeedbackModulators(const TSet<USoundModulatorBase*>& Modulators);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L171 _public prototype_ `void SetFrequency(float Frequency);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L174 _public prototype_ `void SetFrequencyModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L177 _public prototype_ `void SetFrequencyModulators(const TSet<USoundModulatorBase*>& Modulators);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L180 _public prototype_ `void SetWet(float WetAmount);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L183 _public prototype_ `void SetWetModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L186 _public prototype_ `void SetWetModulators(const TSet<USoundModulatorBase*>& Modulators);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L189 _public prototype_ `void SetDry(float DryAmount);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L192 _public prototype_ `void SetDryModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L195 _public prototype_ `void SetDryModulators(const TSet<USoundModulatorBase*>& Modulators);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L198 _public prototype_ `void SetSpread(float Spread);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L201 _public prototype_ `void SetSpreadModulator(const USoundModulatorBase* Modulator);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L204 _public prototype_ `void SetSpreadModulators(const TSet<USoundModulatorBase*>& Modulators);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L208 _public prototype_ `void SetSettings(const FSourceEffectChorusBaseSettings& Settings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")` — Sets just base (i.e. carrier) setting values without modifying modulation source references
- L211 _public prototype_ `void SetModulationSettings(const FSourceEffectChorusSettings& ModulationSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Chorus")`
- L214 _public member_ `FSourceEffectChorusSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectConvolutionReverb.h` (Public)


#### struct `FSourceEffectConvolutionReverbSettings`  
`struct FSourceEffectConvolutionReverbSettings`  
_L16-39_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FSourceEffectConvolutionReverbSettings();`
- L26 _public member_ `float NormalizationVolumeDb;` — `UPROPERTY()` — Used to account for energy added by convolution with "loud" Impulse Responses. This value is not directly editable in the editor because it is copied from the associated UAudioImpulseResponse.
- L30 _public member_ `float WetVolumeDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConvolutionReverb, meta = (DisplayName = "Wet Volume (dB)", ClampMin = "-96.0", ClampMax = "0.0", EditCondition = "!bBypass"))` — Controls how much of the wet signal is mixed into the output, in Decibels
- L34 _public member_ `float DryVolumeDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConvolutionReverb, meta = (DisplayName = "Dry Volume (dB)", ClampMin = "-96.0", ClampMax = "0.0", EditCondition = "!bBypass"))` — Controls how much of the dry signal is mixed into the output, in Decibels
- L38 _public member_ `bool bBypass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConvolutionReverb)` — If true, input audio is directly routed to output audio with applying any effect.

#### class `FSourceEffectConvolutionReverb`  
`class FSourceEffectConvolutionReverb : public FSoundEffectSource`  
_L43-78_
- inherits: `FSoundEffectSource`
- desc: Audio render thread effect object.
- L46 _public prototype_ `FSourceEffectConvolutionReverb() = delete;`
- L48 _public prototype_ `FSourceEffectConvolutionReverb(const USourceEffectConvolutionReverbPreset* InPreset);` — Construct a convolution object with an existing preset.
- L50 _public prototype_ `~FSourceEffectConvolutionReverb();`
- L53 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InInitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L56 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset settings is changed.
- L59 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L63 _public prototype_ `AudioConvReverbIntrinsics::FVersionData UpdateConvolutionReverb(const USourceEffectConvolutionReverbPreset* InPreset);` — Call on the game thread in order to update the impulse response and hardware acceleration used in this effect.
- L65 _public prototype_ `void RebuildConvolutionReverb();`
- L70 _private prototype_ `void SetConvolutionReverbParameters(const FSourceEffectConvolutionReverbSettings& InSettings);` — Sets current runtime settings for convolution reverb which do *not* trigger a FConvolutionReverb rebuild.  These settings will be applied to FConvolutionReverb at the next call to UpdateParameters()
- L73 _private member_ `TSharedRef<Audio::FEffectConvolutionReverb> Reverb;` — Reverb performs majority of DSP operations
- L75 _private member_ `float WetVolume = 1.f;`
- L76 _private member_ `float DryVolume = 1.f;`
- L77 _private member_ `int32 NumChannels = 0;`

#### class `USourceEffectConvolutionReverbPreset`  
`class USourceEffectConvolutionReverbPreset : public USoundEffectSourcePreset`  
_L81-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSourcePreset`
- L87 _public prototype_ `USourceEffectConvolutionReverbPreset(const FObjectInitializer& ObjectInitializer);`
- L94 _public prototype_ `virtual bool CanFilter() const override;`
- L96 _public prototype_ `virtual bool HasAssetActions() const;`
- L98 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L100 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L102 _public prototype_ `virtual FSoundEffectBase* CreateNewEffect() const override;`
- L104 _public prototype_ `virtual USoundEffectPreset* CreateNewPreset(UObject* InParent, FName Name, EObjectFlags Flags) const override;`
- L106 _public prototype_ `virtual void Init() override;`
- L109 _public prototype_ `FSourceEffectConvolutionReverbSettings GetSettings() const;`
- L113 _public prototype_ `void SetSettings(const FSourceEffectConvolutionReverbSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Set the convolution reverb settings
- L117 _public prototype_ `void SetImpulseResponse(UAudioImpulseResponse* InImpulseResponse);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Audio|Effects")` — Set the convolution reverb impulse response
- L121 _public member_ `TObjectPtr<UAudioImpulseResponse> ImpulseResponse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetImpulseResponse, Category = SourceEffectPreset)` — The impulse response used for convolution.
- L125 _public member_ `FSourceEffectConvolutionReverbSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetSettings, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))` — ConvolutionReverbPreset Preset Settings.
- L134 _public member_ `ESubmixEffectConvolutionReverbBlockSize BlockSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = SourceEffectPreset)` — Set the internal block size. This can effect latency and performance. Higher values will result in lower CPU costs while lower values will result higher CPU costs. Latency may be affected depending on the interplay between audio engines buffer sizes and this effects block size. Generally, higher values result in higher latency, and lower values result in lower latency.
- L138 _public member_ `bool bEnableHardwareAcceleration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = SourceEffectPreset)` — Opt into hardware acceleration of the convolution reverb (if available)
- L143 _public prototype_ `void BindToImpulseResponseObjectChange();` — Binds to the UAudioImpulseRespont::OnObjectPropertyChanged delegate of the current ImpulseResponse
- L145 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L146 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L149 _public prototype_ `void PostEditChangeImpulseProperty(FPropertyChangedEvent& PropertyChangedEvent);` — Called when a property changes on the ImpulseResponse object
- L152 _public prototype_ `virtual void PostLoad() override;`
- L155 _private prototype_ `void SetImpulseResponseSettings(UAudioImpulseResponse* InImpulseResponse);`
- L157 _private prototype_ `void UpdateSettings();`
- L159 _private prototype_ `void UpdateDeprecatedProperties();`
- L164 _private prototype_ `void RebuildConvolutionReverb();` — This method requires that the effect is registered with a preset.  If this effect is not registered with a preset, then this will not update the convolution algorithm.
- L166 _private member_ `mutable FCriticalSection SettingsCritSect;`
- L167 _private member_ `FSourceEffectConvolutionReverbSettings SettingsCopy;`
- L171 _private member_ `TMap<UObject*, FDelegateHandle> DelegateHandles;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SYNTHESIS_API`
- L12 _namespace_ `namespace Audio`
- L13 _namespace_ `namespace AudioConvReverbIntrinsics`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectDynamicsProcessor.h` (Public)


#### enum `ESourceEffectDynamicsProcessorType`  
`enum class ESourceEffectDynamicsProcessorType : uint8`  
_L12-20_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Compressor = 0`
- L15 _public enumerator_ `Limiter`
- L16 _public enumerator_ `Expander`
- L17 _public enumerator_ `Gate`
- L18 _public enumerator_ `UpwardsCompressor`
- L19 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceEffectDynamicsPeakMode`  
`enum class ESourceEffectDynamicsPeakMode : uint8`  
_L23-29_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `MeanSquared = 0`
- L26 _public enumerator_ `RootMeanSquared`
- L27 _public enumerator_ `Peak`
- L28 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSourceEffectDynamicsProcessorSettings`  
`struct FSourceEffectDynamicsProcessorSettings`  
_L32-94_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public member_ `ESourceEffectDynamicsProcessorType DynamicsProcessorType = ESourceEffectDynamicsProcessorType::Compressor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Type"))` — Type of processor to apply
- L42 _public member_ `ESourceEffectDynamicsPeakMode PeakMode = ESourceEffectDynamicsPeakMode::RootMeanSquared;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (EditCondition = "!bBypass"))` — Mode of peak detection used on input key signal
- L46 _public member_ `float LookAheadMsec = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (DisplayName = "Look Ahead (ms)", ClampMin = "0.0", ClampMax = "50.0", UIMin = "0.0", UIMax = "50.0", EditCondition = "!bBypass"))` — The amount of time to look ahead of the current audio (Allows for transients to be included in dynamics processing)
- L50 _public member_ `float AttackTimeMsec = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (DisplayName = "Attack Time (ms)", ClampMin = "1.0", ClampMax = "300.0", UIMin = "1.0", UIMax = "200.0", EditCondition = "!bBypass"))` — The amount of time to ramp into any dynamics processing effect
- L54 _public member_ `float ReleaseTimeMsec = 100.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (DisplayName = "Release Time (ms)", ClampMin = "20.0", ClampMax = "5000.0", UIMin = "20.0", UIMax = "5000.0", EditCondition = "!bBypass"))` — The amount of time to release the dynamics processing effect
- L58 _public member_ `float ThresholdDb = -6.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (DisplayName = "Threshold (dB)", ClampMin = "-60.0", ClampMax = "0.0", UIMin = "-60.0", UIMax = "0.0", EditCondition = "!bBypass"))` — The threshold at which to perform a dynamics processing operation
- L62 _public member_ `float Ratio = 1.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (ClampMin = "1.0", ClampMax = "20.0", UIMin = "1.0", UIMax = "20.0", EditCondition = "!bBypass"))` — The dynamics processor ratio used for compression/expansion
- L66 _public member_ `float KneeBandwidthDb = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (DisplayName = "Knee Bandwidth (dB)", ClampMin = "0.0", ClampMax = "20.0", UIMin = "0.0", UIMax = "20.0", EditCondition = "!bBypass"))` — The knee bandwidth of the processor to use
- L70 _public member_ `float InputGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Input Gain (dB)", ClampMin = "-12.0", ClampMax = "20.0", UIMin = "-12.0", UIMax = "20.0", EditCondition = "!bBypass"))` — The input gain of the dynamics processor
- L74 _public member_ `float OutputGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Output Gain (dB)", ClampMin = "0.0", ClampMax = "20.0", UIMin = "0.0", UIMax = "20.0", EditCondition = "!bBypass"))` — The output gain of the dynamics processor
- L78 _public member_ `uint32 bStereoLinked : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (EditCondition = "!bBypass"))` — Whether the left and right channels are linked when determining envelopes
- L82 _public member_ `uint32 bAnalogMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (EditCondition = "!bBypass"))` — Toggles treating the attack and release envelopes as analog-style vs digital-style (Analog will respond a bit more naturally/slower)
- L86 _public member_ `uint8 bBypass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Bypass", DisplayAfter = "DynamicsProcessorType"))` — Whether or not to bypass effect
- L88 _public function_ `FSourceEffectDynamicsProcessorSettings() : bStereoLinked(true) , bAnalogMode(true) , bBypass(false)`

#### class `FSourceEffectDynamicsProcessor`  
`class FSourceEffectDynamicsProcessor : public FSoundEffectSource`  
_L96-114_
- inherits: `FSoundEffectSource`
- L99 _public prototype_ `FSourceEffectDynamicsProcessor();`
- L102 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L105 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L108 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L112 _protected member_ `Audio::FDynamicsProcessor DynamicsProcessor;`
- L113 _protected member_ `bool bBypass = false;`

#### class `USourceEffectDynamicsProcessorPreset`  
`class USourceEffectDynamicsProcessorPreset : public USoundEffectSourcePreset`  
_L119-133_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L124 _public function_ `EFFECT_PRESET_METHODS(SourceEffectDynamicsProcessor) virtual FColor GetPresetColor() const override`
- L129 _public prototype_ `void SetSettings(const FSourceEffectDynamicsProcessorSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = SourceEffectPresets)`
- L132 _public member_ `FSourceEffectDynamicsProcessorSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectEQ.h` (Public)


#### struct `FSourceEffectEQBand`  
`struct FSourceEffectEQBand`  
_L14-41_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `float Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer, meta = (DisplayName = "Frequency (hz)", ClampMin = "20.0", ClampMax = "20000.0", UIMin = "0.0", UIMax = "15000.0", EditCondition = "bEnabled"))` — The cutoff frequency of the band
- L24 _public member_ `float Bandwidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer, meta = (DisplayName = "Bandwidth (octaves)", ClampMin = "0.1", ClampMax = "2.0", UIMin = "0.1", UIMax = "2.0", EditCondition = "bEnabled"))` — The bandwidth (in octaves) of the band
- L28 _public member_ `float GainDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer, meta = (DisplayName = "Gain (dB)", ClampMin = "-90.0", ClampMax = "20.0", UIMin = "-90.0", UIMax = "20.0", EditCondition = "bEnabled"))` — The gain in decibels to apply to the eq band
- L32 _public member_ `uint32 bEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equalizer, meta = (DisplayName = "Enabled"))` — Whether or not the band is enabled. Allows changing bands on the fly.
- L34 _public function_ `FSourceEffectEQBand() : Frequency(500.0f) , Bandwidth(2.0f) , GainDb(0.0f) , bEnabled(false)`

#### struct `FSourceEffectEQSettings`  
`struct FSourceEffectEQSettings`  
_L45-52_
- reflection: `USTRUCT(BlueprintType)`
- desc: EQ source effect settings
- L51 _public member_ `TArray<FSourceEffectEQBand> EQBands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SourceEffectPreset)` — The EQ bands to use

#### class `FSourceEffectEQ`  
`class FSourceEffectEQ : public FSoundEffectSource`  
_L54-76_
- inherits: `FSoundEffectSource`
- L57 _public prototype_ `FSourceEffectEQ();`
- L60 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L63 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L66 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L71 _protected member_ `TArray<Audio::FBiquadFilter> Filters;` — Bank of biquad filters
- L72 _protected member_ `float InAudioFrame[2];`
- L73 _protected member_ `float OutAudioFrame[2];`
- L74 _protected member_ `float SampleRate;`
- L75 _protected member_ `int32 NumChannels;`

#### class `USourceEffectEQPreset`  
`class USourceEffectEQPreset : public USoundEffectSourcePreset`  
_L79-93_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L84 _public function_ `EFFECT_PRESET_METHODS(SourceEffectEQ) virtual FColor GetPresetColor() const override`
- L89 _public prototype_ `void SetSettings(const FSourceEffectEQSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L92 _public member_ `FSourceEffectEQSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SYNTHESIS_API`
- L10 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectEnvelopeFollower.h` (Public)


#### enum `EEnvelopeFollowerPeakMode`  
`enum class EEnvelopeFollowerPeakMode : uint8`  
_L15-21_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `MeanSquared = 0`
- L18 _public enumerator_ `RootMeanSquared`
- L19 _public enumerator_ `Peak`
- L20 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSourceEffectEnvelopeFollowerSettings`  
`struct FSourceEffectEnvelopeFollowerSettings`  
_L24-50_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `float AttackTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnvelopeFollower, meta = (DisplayName = "Attack Time (ms)", ClampMin = "0.0", UIMin = "0.0"))` — The attack time of the envelope follower in milliseconds
- L34 _public member_ `float ReleaseTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnvelopeFollower, meta = (DisplayName = "Release Time (ms)", ClampMin = "0.0", UIMin = "0.0"))` — The release time of the envelope follower in milliseconds
- L38 _public member_ `EEnvelopeFollowerPeakMode PeakMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnvelopeFollower)` — The peak mode of the envelope follower
- L42 _public member_ `bool bIsAnalogMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnvelopeFollower)` — Whether or not the envelope follower is in analog mode
- L44 _public function_ `FSourceEffectEnvelopeFollowerSettings() : AttackTime(10.0f) , ReleaseTime(100.0f) , PeakMode(EEnvelopeFollowerPeakMode::Peak) , bIsAnalogMode(true)`

#### class `FSourceEffectEnvelopeFollower`  
`class FSourceEffectEnvelopeFollower : public FSoundEffectSource`  
_L52-75_
- inherits: `FSoundEffectSource`
- L55 _public prototype_ `~FSourceEffectEnvelopeFollower();`
- L58 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L61 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L64 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L68 _protected member_ `Audio::FInlineEnvelopeFollower EnvelopeFollower;`
- L69 _protected member_ `float CurrentEnvelopeValue;`
- L70 _protected member_ `uint32 OwningPresetUniqueId;`
- L71 _protected member_ `uint32 InstanceId;`
- L72 _protected member_ `int32 FrameCount;`
- L73 _protected member_ `int32 FramesToNotify;`
- L74 _protected member_ `int32 NumChannels;`

#### class `IEnvelopeFollowerNotifier`  
`class IEnvelopeFollowerNotifier`  
_L79-83_
- L82 _public prototype_ `virtual void UnregisterEnvelopeFollowerListener(uint32 PresetUniqueId, UEnvelopeFollowerListener* EnvFollowerListener) = 0;`

#### class `UEnvelopeFollowerListener`  
`class UEnvelopeFollowerListener : public UActorComponent`  
_L86-126_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, hidecategories = (Object, ActorComponent, Physics, Rendering, Mobility, LOD), meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L91 _public function_ `UEnvelopeFollowerListener(const FObjectInitializer& ObjInit) : Super(ObjInit) , bRegistered(false) , PresetUniqueId(INDEX_NONE) , EnvelopeFollowerNotifier(nullptr)`
- L99 _public function_ `~UEnvelopeFollowerListener()`
- L109 _public member_ `FOnEnvelopeFollowerUpdate OnEnvelopeFollowerUpdate;` — `UPROPERTY(BlueprintAssignable)`
- L111 _public function_ `void Init(IEnvelopeFollowerNotifier* InNotifier, uint32 InPresetUniqueId)`
- L123 _protected member_ `bool bRegistered;`
- L124 _protected member_ `uint32 PresetUniqueId;`
- L125 _protected member_ `IEnvelopeFollowerNotifier* EnvelopeFollowerNotifier;`

#### class `USourceEffectEnvelopeFollowerPreset`  
`class USourceEffectEnvelopeFollowerPreset : public USoundEffectSourcePreset`  
_L129-151_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L134 _public function_ `EFFECT_PRESET_METHODS(SourceEffectEnvelopeFollower) virtual FColor GetPresetColor() const override`
- L139 _public prototype_ `void SetSettings(const FSourceEffectEnvelopeFollowerSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L143 _public prototype_ `void RegisterEnvelopeFollowerListener(UEnvelopeFollowerListener* EnvelopeFollowerListener);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Registers an envelope follower listener with the effect.
- L147 _public prototype_ `void UnregisterEnvelopeFollowerListener(UEnvelopeFollowerListener* EnvelopeFollowerListener);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects", meta = (WorldContext = "WorldContextObject"))` — Unregisters an envelope follower listener with the effect.
- L150 _public member_ `FSourceEffectEnvelopeFollowerSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SYNTHESIS_API`
- L77 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnvelopeFollowerUpdate, float, EnvelopeValue);`
- L77 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnvelopeFollowerUpdate, float, EnvelopeValue);`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectFilter.h` (Public)


#### enum `ESourceEffectFilterCircuit`  
`enum class ESourceEffectFilterCircuit : uint8`  
_L16-22_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `OnePole = 0`
- L19 _public enumerator_ `StateVariable`
- L20 _public enumerator_ `Ladder`
- L21 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceEffectFilterType`  
`enum class ESourceEffectFilterType : uint8`  
_L25-32_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `LowPass = 0`
- L28 _public enumerator_ `HighPass`
- L29 _public enumerator_ `BandPass`
- L30 _public enumerator_ `BandStop`
- L31 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceEffectFilterParam`  
`enum class ESourceEffectFilterParam : uint8`  
_L35-40_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `FilterFrequency = 0`
- L38 _public enumerator_ `FilterResonance`
- L39 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSourceEffectFilterAudioBusModulationSettings`  
`struct FSourceEffectFilterAudioBusModulationSettings`  
_L43-82_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `TObjectPtr<UAudioBus> AudioBus = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter)` — Audio bus to use to modulate the filter
- L53 _public member_ `int32 EnvelopeFollowerAttackTimeMsec = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (ClampMin = "0", UIMin = "0", UIMax = "2000.0", DisplayName = "Attack Time (ms)"))` — The amplitude envelope follower attack time (in milliseconds) on the audio bus.
- L57 _public member_ `int32 EnvelopeFollowerReleaseTimeMsec = 100;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (ClampMin = "0", UIMin = "0", UIMax = "2000.0", DisplayName = "Release Time (ms)"))` — The amplitude envelope follower release time (in milliseconds) on the audio bus.
- L61 _public member_ `float EnvelopeGainMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (ClampMin = "0"))` — An amount to scale the envelope follower output to map to the modulation values.
- L65 _public member_ `ESourceEffectFilterParam FilterParam = ESourceEffectFilterParam::FilterFrequency;` — `UPROPERTY(EditAnywhere, Category = ModulationParameters, meta = (InlineCategoryProperty))` — Which parameter to modulate.
- L69 _public member_ `float MinFrequencyModulation = -12.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModulationParameters, meta = (EditCondition = "FilterParam == ESourceEffectFilterParam::FilterFrequency", DisplayName = "Min Frequency Modulation Amount", EditConditionHides))` — The frequency modulation value (in semitones from the filter frequency) to use when the envelope is quietest
- L73 _public member_ `float MaxFrequencyModulation = 12.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModulationParameters, meta = (EditCondition = "FilterParam == ESourceEffectFilterParam::FilterFrequency", DisplayName = "Max Frequency Modulation Amount", EditConditionHides))` — The frequency modulation value (in semitones from the filter frequency) to use when the envelope is loudest
- L77 _public member_ `float MinResonanceModulation = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModulationParameters, meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0", UIMax = "10.0", EditCondition = "FilterParam == ESourceEffectFilterParam::FilterResonance", DisplayName = "Min Resonance Modulation Amount", EditConditionHides))` — The resonance modulation value to use when the envelope is quietest
- L81 _public member_ `float MaxResonanceModulation = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModulationParameters, meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0", UIMax = "10.0", EditCondition = "FilterParam == ESourceEffectFilterParam::FilterResonance", DisplayName = "Max Resonance Modulation Amount", EditConditionHides))` — The resonance modulation value to use when the envelope is loudest

#### struct `FSourceEffectFilterSettings`  
`struct FSourceEffectFilterSettings`  
_L85-108_
- reflection: `USTRUCT(BlueprintType)`
- L91 _public member_ `ESourceEffectFilterCircuit FilterCircuit = ESourceEffectFilterCircuit::StateVariable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Circuit"))` — The type of filter circuit to use.
- L95 _public member_ `ESourceEffectFilterType FilterType = ESourceEffectFilterType::LowPass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Type"))` — The type of filter to use.
- L99 _public member_ `float CutoffFrequency = 800.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Cutoff Frequency (hz)", ClampMin = "20.0", UIMin = "20.0", UIMax = "12000.0"))` — The filter cutoff frequency
- L103 _public member_ `float FilterQ = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Resonance (Q)", ClampMin = "0.5", ClampMax = "10.0", UIMin = "0.5", UIMax = "10.0"))` — The filter resonance.
- L107 _public member_ `TArray<FSourceEffectFilterAudioBusModulationSettings> AudioBusModulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (ShowOnlyInnerProperties))` — Audio bus settings to use to modulate the filter frequency cutoff (auto-wah) with arbitrary audio from an audio bus

#### class `FSourceEffectFilter`  
`class FSourceEffectFilter : public FSoundEffectSource`  
_L110-162_
- inherits: `FSoundEffectSource`
- L113 _public prototype_ `FSourceEffectFilter();`
- L114 _public prototype_ `virtual ~FSourceEffectFilter();`
- L117 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L120 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L123 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L126 _protected prototype_ `void UpdateFilter();`
- L128 _protected member_ `Audio::FStateVariableFilter StateVariableFilter;`
- L129 _protected member_ `Audio::FLadderFilter LadderFilter;`
- L130 _protected member_ `Audio::FOnePoleFilter OnePoleFilter;`
- L131 _protected member_ `Audio::IFilter* CurrentFilter;`
- L133 _protected member_ `float SampleRate;`
- L134 _protected member_ `float CutoffFrequency;`
- L135 _protected member_ `float BaseCutoffFrequency;`
- L136 _protected member_ `float FilterQ;`
- L137 _protected member_ `float BaseFilterQ;`
- L138 _protected member_ `ESourceEffectFilterCircuit CircuitType;`
- L139 _protected member_ `ESourceEffectFilterType FilterType;`
- L141 _protected member_ `Audio::FAlignedFloatBuffer ScratchModBuffer;`
- L142 _protected member_ `Audio::FAlignedFloatBuffer ScratchEnvFollowerBuffer;`
- L156 _protected member_ `TArray<FAudioBusModulationData> ModData;`
- L158 _protected member_ `float AudioInput[2];`
- L159 _protected member_ `float AudioOutput[2];`
- L160 _protected member_ `int32 NumChannels;`
- L161 _protected member_ `uint32 AudioDeviceId;`

#### struct `FSourceEffectFilter::FAudioBusModulationData`  
`struct FAudioBusModulationData`  
_L144-155_
- L146 _public member_ `Audio::FPatchOutputStrongPtr AudioBusPatch;`
- L147 _public member_ `Audio::FEnvelopeFollower AudioBusEnvelopeFollower;`
- L149 _public member_ `ESourceEffectFilterParam FilterParam;`
- L150 _public member_ `float MinFreqModValue = 0.0f;`
- L151 _public member_ `float MaxFreqModValue = 0.0f;`
- L152 _public member_ `float MinResModValue = 0.0f;`
- L153 _public member_ `float MaxResModValue = 0.0f;`
- L154 _public member_ `float EnvelopeGain = 0.0f;`

#### class `USourceEffectFilterPreset`  
`class USourceEffectFilterPreset : public USoundEffectSourcePreset`  
_L165-179_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, AutoExpandCategories = (SourceEffect), meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L170 _public function_ `EFFECT_PRESET_METHODS(SourceEffectFilter) virtual FColor GetPresetColor() const override`
- L175 _public prototype_ `void SetSettings(const FSourceEffectFilterSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L178 _public member_ `FSourceEffectFilterSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectFoldbackDistortion.h` (Public)


#### struct `FSourceEffectFoldbackDistortionSettings`  
`struct FSourceEffectFoldbackDistortionSettings`  
_L12-27_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `float InputGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Distortion, meta = (DisplayName = "Input Gain (dB)", ClampMin = "0.0", ClampMax = "60.0", UIMin = "0.0", UIMax = "20.0"))` — The amount of gain to add to input to allow forcing the triggering of the threshold
- L22 _public member_ `float ThresholdDb = -6.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Distortion, meta = (DisplayName = "Threshold (dB)", ClampMin = "-90.0", ClampMax = "0.0", UIMin = "-60.0", UIMax = "0.0"))` — If the audio amplitude is higher than this, it will fold back
- L26 _public member_ `float OutputGainDb = -3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Distortion, meta = (DisplayName = "Output Gain (dB)", ClampMin = "-90.0", ClampMax = "20.0", UIMin = "-60.0", UIMax = "20.0"))` — The amount of gain to apply to the output

#### class `FSourceEffectFoldbackDistortion`  
`class FSourceEffectFoldbackDistortion : public FSoundEffectSource`  
_L29-43_
- inherits: `FSoundEffectSource`
- L33 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L36 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L39 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData);` — Process the input block of audio. Called on audio thread.
- L42 _protected member_ `Audio::FFoldbackDistortion FoldbackDistortion;`

#### class `USourceEffectFoldbackDistortionPreset`  
`class USourceEffectFoldbackDistortionPreset : public USoundEffectSourcePreset`  
_L46-60_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L51 _public function_ `EFFECT_PRESET_METHODS(SourceEffectFoldbackDistortion) virtual FColor GetPresetColor() const override`
- L56 _public prototype_ `void SetSettings(const FSourceEffectFoldbackDistortionSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L59 _public member_ `FSourceEffectFoldbackDistortionSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectMidSideSpreader.h` (Public)


#### enum `EStereoChannelMode`  
`enum class EStereoChannelMode : uint8`  
_L12-17_
- reflection: `UENUM(BlueprintType)`
- desc: Stereo channel mode
- L14 _public enumerator_ `MidSide`
- L15 _public enumerator_ `LeftRight`
- L16 _public enumerator_ `count UMETA(Hidden)`

#### struct `FSourceEffectMidSideSpreaderSettings`  
`struct FSourceEffectMidSideSpreaderSettings`  
_L25-44_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `float SpreadAmount = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MidSideSpreader, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Amount of Mid/Side Spread. 0.0 is no spread, 1.0 is full wide.
- L35 _public member_ `EStereoChannelMode InputMode = EStereoChannelMode::LeftRight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MidSideSpreader)` — Indicate the channel mode of the input signal
- L39 _public member_ `EStereoChannelMode OutputMode = EStereoChannelMode::LeftRight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MidSideSpreader)` — Indicate the channel mode of the output signal
- L43 _public member_ `bool bEqualPower = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MidSideSpreader)` — Indicate whether an equal power relationship between the mid and side channels should be maintained

#### class `FSourceEffectMidSideSpreader`  
`class FSourceEffectMidSideSpreader : public FSoundEffectSource`  
_L51-74_
- inherits: `FSoundEffectSource`
- L54 _public prototype_ `FSourceEffectMidSideSpreader();`
- L57 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InInitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L60 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L63 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L67 _protected member_ `float MidScale;`
- L68 _protected member_ `float SideScale;`
- L70 _protected member_ `int32 NumChannels;`
- L72 _protected member_ `FSourceEffectMidSideSpreaderSettings SpreaderSettings;`

#### class `USourceEffectMidSideSpreaderPreset`  
`class USourceEffectMidSideSpreaderPreset : public USoundEffectSourcePreset`  
_L83-102_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L89 _public function_ `EFFECT_PRESET_METHODS(SourceEffectMidSideSpreader)` — Macro which declares and implements useful functions.
- L96 _public prototype_ `void SetSettings(const FSourceEffectMidSideSpreaderSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Change settings of your effect from blueprints. Will broadcast changes to active instances.
- L101 _public member_ `FSourceEffectMidSideSpreaderSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))` — The copy of the settings struct. Can't be written to in BP, but can be read. Note that the value read in BP is the serialized settings, will not reflect dynamic changes made in BP.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectMotionFilter.h` (Public)


#### enum `ESourceEffectMotionFilterModSource`  
`enum class ESourceEffectMotionFilterModSource : uint8`  
_L14-31_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `DistanceFromListener = 0` — Uunits between Listener and Sound Source.
- L20 _public enumerator_ `SpeedRelativeToListener` — Uunits per second change in distance between Listener and Sound Source.
- L23 _public enumerator_ `SpeedOfSourceEmitter` — Uunits per second change in world location of Sound Source.
- L26 _public enumerator_ `SpeedOfListener` — Uunits per second change in world location of Listener.
- L29 _public enumerator_ `SpeedOfAngleDelta` — Degrees per second change in Angle of Source from Listener.
- L30 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceEffectMotionFilterModDestination`  
`enum class ESourceEffectMotionFilterModDestination : uint8`  
_L34-57_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `FilterACutoffFrequency = 0 UMETA(DisplayName = "Filter A Cutoff Frequency (hz)")` — Filter input frequencies range between 20.0f and 15000.0f.
- L40 _public enumerator_ `FilterAResonance UMETA(DisplayName = "Filter A Resonance (Q)")` — Filter input resonances range between 0.5f and 10.0f.
- L43 _public enumerator_ `FilterAOutputVolumeDB UMETA(DisplayName = "Filter A Output Volume (dB)")` — Filter output dB range between 10.0f and -96.0f. Final Filter output is clamped to +6 dB, use positive values with caution.
- L46 _public enumerator_ `FilterBCutoffFrequency UMETA(DisplayName = "Filter B Cutoff Frequency (hz)")` — Filter input frequencies range between 20.0f and 15000.0f.
- L49 _public enumerator_ `FilterBResonance UMETA(DisplayName = "Filter B Resonance (Q)")` — Filter input resonances range between 0.5f and 10.0f.
- L52 _public enumerator_ `FilterBOutputVolumeDB UMETA(DisplayName = "Filter B Output Volume (dB)")` — Filter output dB range between 10.0f and -96.0f. Final Filter output is clamped to +6 dB, use positive values with caution.
- L55 _public enumerator_ `FilterMix` — Filter Mix values range from -1.0f (Filter A) and 1.0f (Filter B).
- L56 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceEffectMotionFilterTopology`  
`enum class ESourceEffectMotionFilterTopology : uint8`  
_L60-65_
- reflection: `UENUM(BlueprintType)`
- L62 _public enumerator_ `SerialMode = 0`
- L63 _public enumerator_ `ParallelMode`
- L64 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceEffectMotionFilterCircuit`  
`enum class ESourceEffectMotionFilterCircuit : uint8`  
_L68-74_
- reflection: `UENUM(BlueprintType)`
- L70 _public enumerator_ `OnePole = 0`
- L71 _public enumerator_ `StateVariable`
- L72 _public enumerator_ `Ladder`
- L73 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceEffectMotionFilterType`  
`enum class ESourceEffectMotionFilterType : uint8`  
_L77-84_
- reflection: `UENUM(BlueprintType)`
- L79 _public enumerator_ `LowPass = 0`
- L80 _public enumerator_ `HighPass`
- L81 _public enumerator_ `BandPass`
- L82 _public enumerator_ `BandStop`
- L83 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSourceEffectIndividualFilterSettings`  
`struct FSourceEffectIndividualFilterSettings`  
_L87-106_
- reflection: `USTRUCT(BlueprintType)`
- L93 _public member_ `ESourceEffectMotionFilterCircuit FilterCircuit = ESourceEffectMotionFilterCircuit::Ladder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Circuit"))` — The type of filter circuit to use.
- L97 _public member_ `ESourceEffectMotionFilterType FilterType = ESourceEffectMotionFilterType::LowPass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Type"))` — The type of filter to use.
- L101 _public member_ `float CutoffFrequency = 800.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Cutoff Frequency (hz)", ClampMin = "20.0", UIMin = "20.0", UIMax = "12000.0"))` — The filter cutoff frequency
- L105 _public member_ `float FilterQ = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Resonance (Q)", ClampMin = "0.5", ClampMax = "10.0", UIMin = "0.5", UIMax = "10.0"))` — The filter resonance.

#### struct `FSourceEffectMotionFilterModulationSettings`  
`struct FSourceEffectMotionFilterModulationSettings`  
_L110-133_
- reflection: `USTRUCT(BlueprintType)`
- L116 _public member_ `ESourceEffectMotionFilterModSource ModulationSource = ESourceEffectMotionFilterModSource::DistanceFromListener;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilterModulation)` — The Modulation Source
- L120 _public member_ `FVector2D ModulationInputRange = { 0.0f, 1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilterModulation)` — The Modulation Clamped Input Range
- L124 _public member_ `FVector2D ModulationOutputMinimumRange = { 0.0f, 0.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilterModulation)` — The Modulation Random Minimum Output Range
- L128 _public member_ `FVector2D ModulationOutputMaximumRange = { 1.0f, 1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilterModulation)` — The Modulation Random Maximum Output Range
- L132 _public member_ `float UpdateEaseMS = 50.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilterModulation, meta = (DisplayName = "Update Ease (ms)", ClampMin = "0.0", UIMin = "0.0"))` — Update Ease Speed in milliseconds

#### struct `FSourceEffectMotionFilterSettings`  
`struct FSourceEffectMotionFilterSettings`  
_L141-173_
- reflection: `USTRUCT(BlueprintType)`
- L147 _public member_ `ESourceEffectMotionFilterTopology MotionFilterTopology = ESourceEffectMotionFilterTopology::ParallelMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilter)` — In Serial Mode, Filter A will process then Filter B will process; in Parallel mode, Filter A and Filter B will process the dry input seprately, then be mixed together afterward.
- L151 _public member_ `float MotionFilterMix = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilter, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — Filter Mix controls the amount of each filter in the signal where -1.0f outputs Only Filter A, 0.0f is an equal balance between Filter A and B, and 1.0f outputs only Filter B. How this blend works depends on the Topology.
- L155 _public member_ `FSourceEffectIndividualFilterSettings FilterASettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilter, meta = (DisplayName = "Filter A"))` — Initial settings for Filter A
- L159 _public member_ `FSourceEffectIndividualFilterSettings FilterBSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilter, meta = (DisplayName = "Filter B"))` — Initial settings for Filter B
- L163 _public member_ `TMap<ESourceEffectMotionFilterModDestination,FSourceEffectMotionFilterModulationSettings> ModulationMappings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilter)` — Modulation Mappings
- L167 _public member_ `float DryVolumeDb = -96.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MotionFilter, meta = (DisplayName = "Dry Volume (dB)", ClampMin = "-96.0", UIMin = "-96.0", UIMax = "10.0"))` — Dry volume pass-through in dB.
- L169 _public function_ `FSourceEffectMotionFilterSettings()`

#### struct `FMotionFilter`  
`struct FMotionFilter`  
_L183-207_
- L186 _public member_ `Audio::FOnePoleFilter OnePoleFilter;` — Filter Settings
- L187 _public member_ `Audio::FStateVariableFilter StateVarFilter;`
- L188 _public member_ `Audio::FLadderFilter LadderFilter;`
- L190 _public member_ `Audio::IFilter* CurrentFilter;` — Which filter we're currently using
- L192 _public member_ `ESourceEffectMotionFilterCircuit CurrentFilterCircuit;`
- L195 _public member_ `Audio::EFilter::Type FilterType;` — Filter Type
- L197 _public member_ `float FilterFrequency;`
- L198 _public member_ `float FilterQ;`
- L200 _public function_ `FMotionFilter() : CurrentFilter(nullptr) , CurrentFilterCircuit(ESourceEffectMotionFilterCircuit::OnePole) , FilterType(Audio::EFilter::LowPass) , FilterFrequency(800.0f) , FilterQ(2.0f)`

#### class `FSourceEffectMotionFilter`  
`class FSourceEffectMotionFilter : public FSoundEffectSource`  
_L215-316_
- inherits: `FSoundEffectSource`
- L218 _public prototype_ `FSourceEffectMotionFilter();`
- L221 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InInitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L224 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L227 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L231 _protected member_ `ESourceEffectMotionFilterTopology Topology;` — Motion filter topology
- L233 _protected member_ `FMotionFilter MotionFilterA;`
- L234 _protected member_ `FMotionFilter MotionFilterB;`
- L237 _protected member_ `float FilterMixAmount;` — Filter Mix
- L240 _protected member_ `TMap<ESourceEffectMotionFilterModDestination, FSourceEffectMotionFilterModulationSettings> ModMap;` — Mod Map
- L243 _protected member_ `TMap<ESourceEffectMotionFilterModDestination, FVector2D> ModMapOutputRange;` — Mod Map Random Output Range
- L246 _protected member_ `TArray<TArray<float>> ModMatrix;` — Current Mod Matrix comprised of [Source] x [Destination] coordinates
- L249 _protected member_ `TArray<TArray<float>> TargetMatrix;` — Target values for the Mod Matrix
- L252 _protected member_ `TArray<TArray<float>> LastTargetMatrix;` — Last Target values for the Mod Matrix
- L255 _protected member_ `TArray<TArray<Audio::FLinearEase>> LinearEaseMatrix;` — Linear Ease Matrix
- L258 _protected member_ `TArray<TArray<bool>> LinearEaseMatrixInit;` — Linear Ease Matrix is Initialized
- L261 _protected member_ `float DryVolumeScalar;` — Attenuation of sound in linear units
- L264 _protected member_ `TArray<float> ModSources;` — Modulation Sources
- L267 _protected member_ `double ModSourceTimeStamp;` — This is the last time Mod Source data has been updated
- L269 _protected member_ `float LastDistance;`
- L270 _protected member_ `FVector LastEmitterWorldPosition;`
- L271 _protected member_ `FVector LastListenerWorldPosition;`
- L272 _protected member_ `FVector LastEmitterNormalizedPosition;`
- L275 _protected member_ `TArray<float> BaseDestinationValues;` — Base Destination Values
- L278 _protected member_ `TArray<float> ModDestinationValues;` — Modulation Destination Values
- L281 _protected member_ `TArray<float> ModDestinationUpdateTimeMS;` — Modulation Destination Values
- L284 _protected member_ `Audio::FAlignedFloatBuffer ScratchBufferA;` — Intermediary Scratch Buffers
- L285 _protected member_ `Audio::FAlignedFloatBuffer ScratchBufferB;`
- L288 _protected member_ `float FilterAMixScale;` — Filter Output Scalars
- L289 _protected member_ `float FilterBMixScale;`
- L290 _protected member_ `float FilterAOutputScale;`
- L291 _protected member_ `float FilterBOutputScale;`
- L294 _protected prototype_ `void UpdateFilter(FMotionFilter* MotionFilter, ESourceEffectMotionFilterCircuit FilterCircuitType, ESourceEffectMotionFilterType MotionFilterType, float FilterFrequency, float FilterQ);` — Update Filter Parameters
- L297 _protected prototype_ `void ApplyFilterModulation(const TArray<float>& DestinationSettings);` — Applies modulation changes to Filter based on Destination Input Values
- L300 _protected prototype_ `void UpdateModulationSources(const FSoundEffectSourceInputData& InData);` — Update Modulation Source Parameters
- L303 _protected prototype_ `bool UpdateModulationMatrix(const float UpdateTime);` — Updates Modulated Parameters, returns true if parameters were updated
- L306 _protected prototype_ `void UpdateModulationDestinations();` — Updates Modulation Destinations based on updated Matrix Values
- L309 _protected member_ `float SampleRate;` — Sample Rate cached
- L312 _protected member_ `int32 NumChannels;` — Number of channels in source
- L315 _protected member_ `float ChannelRate;` — SampleRate * NumChannels

#### class `USourceEffectMotionFilterPreset`  
`class USourceEffectMotionFilterPreset : public USoundEffectSourcePreset`  
_L325-344_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L331 _public function_ `EFFECT_PRESET_METHODS(SourceEffectMotionFilter)` — Macro which declares and implements useful functions.
- L338 _public prototype_ `void SetSettings(const FSourceEffectMotionFilterSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Change settings of your effect from blueprints. Will broadcast changes to active instances.
- L343 _public member_ `FSourceEffectMotionFilterSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))` — The copy of the settings struct. Can't be written to in BP, but can be read. Note that the value read in BP is the serialized settings, will not reflect dynamic changes made in BP.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`
- L11 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectPanner.h` (Public)


#### struct `FSourceEffectPannerSettings`  
`struct FSourceEffectPannerSettings`  
_L11-22_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `float Spread = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Panner, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — The spread of the source. 1.0 means left only in left channel, right only in right; 0.0 means both mixed, -1.0 means right and left channels are inverted.
- L21 _public member_ `float Pan = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Panner, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — The pan of the source. -1.0 means left, 0.0 means center, 1.0 means right.

#### class `FSourceEffectPanner`  
`class FSourceEffectPanner : public FSoundEffectSource`  
_L24-52_
- inherits: `FSoundEffectSource`
- L28 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L31 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L34 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio render thread.
- L36 _public function_ `FSourceEffectPanner()`
- L49 _protected member_ `float SpreadGains[2];` — The pan value of the source effect
- L50 _protected member_ `float PanGains[2];`
- L51 _protected member_ `int32 NumChannels;`

#### class `USourceEffectPannerPreset`  
`class USourceEffectPannerPreset : public USoundEffectSourcePreset`  
_L55-69_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L60 _public function_ `EFFECT_PRESET_METHODS(SourceEffectPanner) virtual FColor GetPresetColor() const override`
- L65 _public prototype_ `void SetSettings(const FSourceEffectPannerSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L68 _public member_ `FSourceEffectPannerSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectPhaser.h` (Public)


#### enum `EPhaserLFOType`  
`enum class EPhaserLFOType : uint8`  
_L12-22_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Sine = 0`
- L15 _public enumerator_ `UpSaw`
- L16 _public enumerator_ `DownSaw`
- L17 _public enumerator_ `Square`
- L18 _public enumerator_ `Triangle`
- L19 _public enumerator_ `Exponential`
- L20 _public enumerator_ `RandomSampleHold`
- L21 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSourceEffectPhaserSettings`  
`struct FSourceEffectPhaserSettings`  
_L25-48_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `float WetLevel = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phaser, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The wet level of the phaser effect
- L35 _public member_ `float Frequency = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phaser, meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "5.0"))` — The LFO frequency of the phaser effect
- L39 _public member_ `float Feedback = 0.3f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phaser, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The feedback of the phaser effect
- L43 _public member_ `EPhaserLFOType LFOType = EPhaserLFOType::Sine;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phaser, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The phaser LFO type
- L47 _public member_ `bool UseQuadraturePhase = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Phaser, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Whether or not to use quadtrature phase for the LFO modulation

#### class `FSourceEffectPhaser`  
`class FSourceEffectPhaser : public FSoundEffectSource`  
_L50-64_
- inherits: `FSoundEffectSource`
- L54 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L57 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L60 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L63 _protected member_ `Audio::FPhaser Phaser;`

#### class `USourceEffectPhaserPreset`  
`class USourceEffectPhaserPreset : public USoundEffectSourcePreset`  
_L67-82_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L72 _public function_ `EFFECT_PRESET_METHODS(SourceEffectPhaser) virtual FColor GetPresetColor() const override`
- L77 _public prototype_ `void SetSettings(const FSourceEffectPhaserSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L81 _public member_ `FSourceEffectPhaserSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))` — The depth of the chorus effect

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectRingModulation.h` (Public)


#### enum `ERingModulatorTypeSourceEffect`  
`enum class ERingModulatorTypeSourceEffect : uint8`  
_L14-21_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Sine`
- L17 _public enumerator_ `Saw`
- L18 _public enumerator_ `Triangle`
- L19 _public enumerator_ `Square`
- L20 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSourceEffectRingModulationSettings`  
`struct FSourceEffectRingModulationSettings`  
_L24-51_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `ERingModulatorTypeSourceEffect ModulatorType = ERingModulatorTypeSourceEffect::Sine;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RingModulation, meta = (ClampMin = "5.0", UIMin = "10.0", UIMax = "5000.0"))` — Ring modulation modulator oscillator type
- L34 _public member_ `float Frequency = 100.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RingModulation, meta = (DisplayName = "Frequency (hz)", ClampMin = "5.0", UIMin = "10.0", UIMax = "5000.0"))` — Ring modulation frequency
- L38 _public member_ `float Depth = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RingModulation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Ring modulation depth
- L42 _public member_ `float DryLevel = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RingModulation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Gain for the dry signal (no ring mod)
- L46 _public member_ `float WetLevel = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RingModulation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Gain for the wet signal (with ring mod)
- L50 _public member_ `TObjectPtr<UAudioBus> AudioBusModulator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RingModulation)` — Audio bus to use to modulate the effect

#### class `FSourceEffectRingModulation`  
`class FSourceEffectRingModulation : public FSoundEffectSource`  
_L53-69_
- inherits: `FSoundEffectSource`
- L57 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L60 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L63 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L66 _protected member_ `Audio::FRingModulation RingModulation;`
- L67 _protected member_ `uint32 AudioDeviceId;`
- L68 _protected member_ `int32 NumChannels = 0;`

#### class `USourceEffectRingModulationPreset`  
`class USourceEffectRingModulationPreset : public USoundEffectSourcePreset`  
_L72-86_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L77 _public function_ `EFFECT_PRESET_METHODS(SourceEffectRingModulation) virtual FColor GetPresetColor() const override`
- L82 _public prototype_ `void SetSettings(const FSourceEffectRingModulationSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L85 _public member_ `FSourceEffectRingModulationSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectSimpleDelay.h` (Public)


#### struct `FSourceEffectSimpleDelaySettings`  
`struct FSourceEffectSimpleDelaySettings`  
_L12-48_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `float SpeedOfSound = 343.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delay, meta = (DisplayAfter = "bDelayBasedOnDistance", ClampMin = "0.01", UIMin = "0.01", UIMax = "10000.0", EditCondition = "bDelayBasedOnDistance"))` — Speed of sound in meters per second when using distance-based delay
- L22 _public member_ `float DelayAmount = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delay, meta = (DisplayAfter = "SpeedOfSound", ClampMin = "0.0", ClampMax = "2.0", UIMin = "0.0", UIMax = "2.0", EditCondition = "!bDelayBasedOnDistance"))` — Delay amount in seconds
- L26 _public member_ `float DryAmount = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delay, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Gain stage on dry (non-delayed signal)
- L30 _public member_ `float WetAmount = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delay, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Gain stage on wet (delayed) signal
- L34 _public member_ `float Feedback = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delay, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Amount to feedback into the delay line (because why not)
- L38 _public member_ `uint32 bDelayBasedOnDistance : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delay)` — Whether or not to delay the audio based on the distance to the listener or use manual delay
- L42 _public member_ `uint32 bUseDistanceOverride : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delay)` — Whether or not to allow the attenuation distance override value vs the distance to listener to be used for distance-based delay.
- L44 _public function_ `FSourceEffectSimpleDelaySettings() : bDelayBasedOnDistance(true) , bUseDistanceOverride(true)`

#### class `FSourceEffectSimpleDelay`  
`class FSourceEffectSimpleDelay : public FSoundEffectSource`  
_L50-68_
- inherits: `FSoundEffectSource`
- L54 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L57 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L60 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L64 _protected member_ `TArray<Audio::FDelay> Delays;` — 2 Delay lines, one for each channel
- L65 _protected member_ `TArray<float> FeedbackSamples;`
- L66 _protected member_ `FSourceEffectSimpleDelaySettings SettingsCopy;`
- L67 _protected member_ `bool bIsInit = true;`

#### class `USourceEffectSimpleDelayPreset`  
`class USourceEffectSimpleDelayPreset : public USoundEffectSourcePreset`  
_L71-85_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L76 _public function_ `EFFECT_PRESET_METHODS(SourceEffectSimpleDelay) virtual FColor GetPresetColor() const override`
- L81 _public prototype_ `void SetSettings(const FSourceEffectSimpleDelaySettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L84 _public member_ `FSourceEffectSimpleDelaySettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectStereoDelay.h` (Public)


#### enum `EStereoDelaySourceEffect`  
`enum class EStereoDelaySourceEffect : uint8`  
_L12-27_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Normal = 0` — Left input mixes with left delay line output and feeds to left output. Right input mixes with right delay line output and feeds to right output.
- L20 _public enumerator_ `Cross` — Left input mixes right delay line output and feeds to right output. Right input mixes with left delay line output and feeds to left output.
- L24 _public enumerator_ `PingPong` — Left input mixes with left delay line output and feeds to right output. Right input mixes with right delay line output and feeds to left output.
- L26 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EStereoDelayFiltertype`  
`enum class EStereoDelayFiltertype : uint8`  
_L31-39_
- reflection: `UENUM(BlueprintType)`
- desc: Stereo delay filter types
- L33 _public enumerator_ `Lowpass = 0`
- L34 _public enumerator_ `Highpass`
- L35 _public enumerator_ `Bandpass`
- L36 _public enumerator_ `Notch`
- L38 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSourceEffectStereoDelaySettings`  
`struct FSourceEffectStereoDelaySettings`  
_L42-85_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public member_ `EStereoDelaySourceEffect DelayMode = EStereoDelaySourceEffect::PingPong;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StereoDelay, meta = (DisplayName = "Mode"))` — What mode to set the stereo delay effect.
- L52 _public member_ `float DelayTimeMsec = 500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StereoDelay, meta = (DisplayName = "Delay Time (ms)", ClampMin = "0.0", ClampMax = "2000.0", UIMin = "0.0", UIMax = "2000.0"))` — The base amount of delay in the left and right channels of the delay line.
- L56 _public member_ `float Feedback = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StereoDelay, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of audio to feedback into the delay line once the delay has been tapped.
- L60 _public member_ `float DelayRatio = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StereoDelay, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — Delay spread for left and right channels. Allows left and right channels to have differential delay amounts. Useful for stereo channel decorrelation.
- L64 _public member_ `float WetLevel = 0.4f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StereoDelay, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of delay effect to mix with the dry input signal into the effect.
- L68 _public member_ `float DryLevel = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StereoDelay, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The dry level of the effect
- L72 _public member_ `bool bFilterEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Enabled"))` — Whether or not to enable filtering
- L76 _public member_ `EStereoDelayFiltertype FilterType = EStereoDelayFiltertype::Lowpass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Type", EditCondition = "bFilterEnabled"))` — Filter type to feed feedback audio to
- L80 _public member_ `float FilterFrequency = 20000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Cutoff Frequency (hz)", ClampMin = "20.0", ClampMax = "20000", UIMin = "20.0", UIMax = "20000", EditCondition = "bFilterEnabled"))` — Cutoff frequency of the filter
- L84 _public member_ `float FilterQ = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Resonance (Q)", ClampMin = "0.5", ClampMax = "10.0", UIMin = "0.5", UIMax = "10.0", EditCondition = "bFilterEnabled"))` — Q of the filter

#### class `FSourceEffectStereoDelay`  
`class FSourceEffectStereoDelay : public FSoundEffectSource`  
_L87-101_
- inherits: `FSoundEffectSource`
- L91 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L94 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L97 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L100 _protected member_ `Audio::FDelayStereo DelayStereo;`

#### class `USourceEffectStereoDelayPreset`  
`class USourceEffectStereoDelayPreset : public USoundEffectSourcePreset`  
_L104-119_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L110 _public function_ `EFFECT_PRESET_METHODS(SourceEffectStereoDelay) virtual FColor GetPresetColor() const override`
- L115 _public prototype_ `void SetSettings(const FSourceEffectStereoDelaySettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L118 _public member_ `FSourceEffectStereoDelaySettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SourceEffects/SourceEffectWaveShaper.h` (Public)


#### struct `FSourceEffectWaveShaperSettings`  
`struct FSourceEffectWaveShaperSettings`  
_L12-23_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `float Amount = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveShaper, meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "500.0"))` — The amount of wave shaping. 0.0 = no wave shaping.
- L22 _public member_ `float OutputGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveShaper, meta = (DisplayName = "Output Gain (dB)", ClampMin = "-60.0", ClampMax = "20.0", UIMin = "-60.0", UIMax = "20.0"))` — The amount of wave shaping. 0.0 = no wave shaping.

#### class `FSourceEffectWaveShaper`  
`class FSourceEffectWaveShaper : public FSoundEffectSource`  
_L25-40_
- inherits: `FSoundEffectSource`
- L29 _public prototype_ `virtual void Init(const FSoundEffectSourceInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L32 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L35 _public prototype_ `virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;` — Process the input block of audio. Called on audio thread.
- L38 _protected member_ `Audio::FWaveShaper WaveShaper;`
- L39 _protected member_ `int32 NumChannels;`

#### class `USourceEffectWaveShaperPreset`  
`class USourceEffectWaveShaperPreset : public USoundEffectSourcePreset`  
_L43-57_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSourcePreset`
- L48 _public function_ `EFFECT_PRESET_METHODS(SourceEffectWaveShaper) virtual FColor GetPresetColor() const override`
- L53 _public prototype_ `void SetSettings(const FSourceEffectWaveShaperSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L56 _public member_ `FSourceEffectWaveShaperSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SourceEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectConvolutionReverb.h` (Public)


#### struct `FSubmixEffectConvolutionReverbSettings`  
`struct FSubmixEffectConvolutionReverbSettings`  
_L16-74_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FSubmixEffectConvolutionReverbSettings();`
- L26 _public member_ `float NormalizationVolumeDb;` — `UPROPERTY()` — Used to account for energy added by convolution with "loud" Impulse Responses. This value is not directly editable in the editor because it is copied from the associated UAudioImpulseResponse.
- L30 _public member_ `float WetVolumeDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (DisplayName = "Wet Volume (dB)", ClampMin = "-96.0", ClampMax = "0.0"))` — Controls how much of the wet signal is mixed into the output, in Decibels
- L34 _public member_ `float DryVolumeDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (DisplayName = "Dry Volume (dB)", ClampMin = "-96.0", ClampMax = "0.0"))` — Controls how much of the dry signal is mixed into the output, in Decibels
- L38 _public member_ `bool bBypass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset)` — If true, input audio is directly routed to output audio with applying any effect.
- L45 _public member_ `bool bMixInputChannelFormatToImpulseResponseFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (EditCondition = "!bBypass"))` — If true, the submix input audio is downmixed to match the IR asset audio channel format. If false, the input audio's channels are matched to the IR assets audio channels.
- L52 _public member_ `bool bMixReverbOutputToOutputChannelFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (EditCondition = "!bBypass"))` — If true, the reverberated audio is upmixed or downmixed to match the submix output audio format. If false, the reverberated audio's channels are matched to the submixs output audio channels.
- L56 _public member_ `float SurroundRearChannelBleedDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubmixEffectPreset|Surround", meta = (DisplayName = "Surround Rear Channel Bleed (dB)", EditCondition = "bMixReverbOutputToOutputChannelFormat && !bBypass", ClampMin = "-60.0", UIMin = "-60.0", ClampMax = "15.0", UIMax = "15.0"))` — Amount of audio to be sent to rear channels in quad/surround configurations
- L60 _public member_ `bool bInvertRearChannelBleedPhase;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SumixEffectPreset|Surround", meta = (EditCondition = "bMixReverbOutputToOutputChannelFormat && !bBypass"))` — If true, rear channel bleed sends will have their phase inverted.
- L64 _public member_ `bool bSurroundRearChannelFlip;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubmixEffectPreset|Surround", meta = (EditCondition = "bMixReverbOutputToOutputChannelFormat && !bBypass"))` — If true, send Surround Rear Channel Bleed Amount sends front left to back right and vice versa
- L67 _public member_ `float SurroundRearChannelBleedAmount_DEPRECATED;` — `UPROPERTY(meta = ( DeprecatedProperty ))`
- L70 _public member_ `TObjectPtr<UAudioImpulseResponse> ImpulseResponse_DEPRECATED;` — `UPROPERTY(meta = ( DeprecatedProperty ))`
- L73 _public member_ `bool AllowHardwareAcceleration_DEPRECATED;` — `UPROPERTY(meta = ( DeprecatedProperty ))`

#### class `FSubmixEffectConvolutionReverb`  
`class FSubmixEffectConvolutionReverb : public FSoundEffectSubmix`  
_L78-114_
- inherits: `FSoundEffectSubmix`
- desc: Audio render thread effect object.
- L82 _public prototype_ `FSubmixEffectConvolutionReverb() = delete;`
- L84 _public prototype_ `FSubmixEffectConvolutionReverb(const USubmixEffectConvolutionReverbPreset* InPreset);` — Construct a convolution object with an existing preset.
- L86 _public prototype_ `~FSubmixEffectConvolutionReverb();`
- L89 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InitData) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L92 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset settings is changed.
- L95 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;` — Process the input block of audio. Called on audio thread.
- L99 _public prototype_ `AudioConvReverbIntrinsics::FVersionData UpdateConvolutionReverb(const USubmixEffectConvolutionReverbPreset* InPreset);` — Call on the game thread in order to update the impulse response and hardware acceleration used in this submix effect.
- L101 _public prototype_ `void RebuildConvolutionReverb();`
- L103 _public member_ `float WetVolume = 1.f;`
- L104 _public member_ `float DryVolume = 1.f;`
- L110 _private prototype_ `void SetConvolutionReverbParameters(const FSubmixEffectConvolutionReverbSettings& InSettings);` — Sets current runtime settings for convolution reverb which do *not* trigger a FConvolutionReverb rebuild.  These settings will be applied to FConvolutionReverb at the next call to UpdateParameters()
- L113 _private member_ `TSharedRef<Audio::FEffectConvolutionReverb> Reverb;` — Reverb performs majority of DSP operations

#### class `USubmixEffectConvolutionReverbPreset`  
`class USubmixEffectConvolutionReverbPreset : public USoundEffectSubmixPreset`  
_L117-209_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L123 _public prototype_ `USubmixEffectConvolutionReverbPreset(const FObjectInitializer& ObjectInitializer);`
- L130 _public prototype_ `virtual bool CanFilter() const override;`
- L132 _public prototype_ `virtual bool HasAssetActions() const;`
- L134 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L136 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L138 _public prototype_ `virtual FSoundEffectBase* CreateNewEffect() const override;`
- L140 _public prototype_ `virtual USoundEffectPreset* CreateNewPreset(UObject* InParent, FName Name, EObjectFlags Flags) const override;`
- L142 _public prototype_ `virtual void Init() override;`
- L145 _public prototype_ `FSubmixEffectConvolutionReverbSettings GetSettings() const;`
- L149 _public prototype_ `void SetSettings(const FSubmixEffectConvolutionReverbSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Set the convolution reverb settings
- L153 _public prototype_ `void SetImpulseResponse(UAudioImpulseResponse* InImpulseResponse);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Audio|Effects")` — Set the convolution reverb impulse response
- L157 _public member_ `TObjectPtr<UAudioImpulseResponse> ImpulseResponse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetImpulseResponse, Category = SubmixEffectPreset)` — The impulse response used for convolution.
- L161 _public member_ `FSubmixEffectConvolutionReverbSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetSettings, Category = SubmixEffectPreset, meta = (ShowOnlyInnerProperties))` — ConvolutionReverbPreset Preset Settings.
- L170 _public member_ `ESubmixEffectConvolutionReverbBlockSize BlockSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = SubmixEffectPreset)` — Set the internal block size. This can effect latency and performance. Higher values will result in lower CPU costs while lower values will result higher CPU costs. Latency may be affected depending on the interplay between audio engines buffer sizes and this effects block size. Generally, higher values result in higher latency, and lower values result in lower latency.
- L174 _public member_ `bool bEnableHardwareAcceleration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = SubmixEffectPreset)` — Opt into hardware acceleration of the convolution reverb (if available)
- L179 _public prototype_ `void BindToImpulseResponseObjectChange();` — Binds to the UAudioImpulseRespont::OnObjectPropertyChanged delegate of the current ImpulseResponse
- L181 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L182 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L185 _public prototype_ `void PostEditChangeImpulseProperty(FPropertyChangedEvent& PropertyChangedEvent);` — Called when a property changes on the ImpulseResponse object
- L188 _public prototype_ `virtual void PostLoad() override;`
- L191 _private prototype_ `void SetImpulseResponseSettings(UAudioImpulseResponse* InImpulseResponse);`
- L193 _private prototype_ `void UpdateSettings();`
- L195 _private prototype_ `void UpdateDeprecatedProperties();`
- L200 _private prototype_ `void RebuildConvolutionReverb();` — This method requires that the submix effect is registered with a preset.  If this submix effect is not registered with a preset, then this will not update the convolution algorithm.
- L202 _private member_ `mutable FCriticalSection SettingsCritSect;`
- L203 _private member_ `FSubmixEffectConvolutionReverbSettings SettingsCopy;`
- L207 _private member_ `TMap<UObject*, FDelegateHandle> DelegateHandles;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SYNTHESIS_API`
- L12 _namespace_ `namespace Audio`
- L13 _namespace_ `namespace AudioConvReverbIntrinsics`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectDelay.h` (Public)


#### struct `FSubmixEffectDelaySettings`  
`struct FSubmixEffectDelaySettings`  
_L20-35_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `float MaximumDelayLength = 2000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Initialization, meta = (DisplayName = "Maximum Delay Length (ms)", ClampMin = "10.0", UIMin = "10.0", UIMax = "20000.0"))` — Maximum possible length for a delay, in milliseconds. Changing this at runtime will reset the effect.
- L30 _public member_ `float InterpolationTime = 400.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime, meta = (DisplayName = "Interpolation Time (ms)", ClampMin = "0.0", UIMin = "0.0", UIMax = "20000.0"))` — Number of milliseconds over which a tap will reach it's set length and gain. Smaller values are more responsive, while larger values will make pitching less dramatic.
- L34 _public member_ `float DelayLength = 1000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime, meta = (DisplayName = "Delay Length (ms)", ClampMin = "0.0", UIMin = "0.0", UIMax = "20000.0"))` — Number of milliseconds of delay.  Caps at max delay at runtime.

#### class `USubmixEffectDelayStatics`  
`class USubmixEffectDelayStatics : public UBlueprintFunctionLibrary`  
_L38-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L44 _public function_ `static FSubmixEffectDelaySettings& SetMaximumDelayLength(UPARAM(ref) FSubmixEffectDelaySettings& DelaySettings, float MaximumDelayLength)` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Delay")`
- L52 _public function_ `static FSubmixEffectDelaySettings& SetInterpolationTime(UPARAM(ref) FSubmixEffectDelaySettings& DelaySettings, float InterpolationTime)` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Delay")`
- L59 _public function_ `static FSubmixEffectDelaySettings& SetDelayLength(UPARAM(ref) FSubmixEffectDelaySettings& DelaySettings, float DelayLength)` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Delay")`

#### class `FSubmixEffectDelay`  
`class FSubmixEffectDelay : public FSoundEffectSubmix`  
_L68-120_
- inherits: `FSoundEffectSubmix`
- L71 _public prototype_ `FSubmixEffectDelay();`
- L72 _public prototype_ `~FSubmixEffectDelay();`
- L75 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InData) override;`
- L76 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;`
- L80 _public prototype_ `virtual void OnPresetChanged() override;`
- L84 _public prototype_ `void SetEffectParameters(const FSubmixEffectDelaySettings& InTapEffectParameters);` — Sets the reverb effect parameters based from audio thread code
- L87 _public prototype_ `void SetInterpolationTime(float Time);` — Set the time it takes, in milliseconds, to arrive at a new parameter.
- L90 _public prototype_ `void SetDelayLineLength(float Length);` — Set how long the actually delay is, in milliseconds.
- L93 _private member_ `static const float MinLengthDelaySec;`
- L96 _private prototype_ `void UpdateParameters();` — This is called on the audio render thread to query the parameters.
- L99 _private prototype_ `void OnNumChannelsChanged(int32 NumChannels);` — Called on the audio render thread when the number of channels is changed
- L102 _private member_ `Audio::TParams<FSubmixEffectDelaySettings> Params;` — Params struct used to pass parameters safely to the audio render thread.
- L105 _private member_ `float SampleRate;` — Sample rate cached at initialization. Used to gage interpolation times.
- L108 _private member_ `float MaxDelayLineLength;` — Current maximum delay line length, in milliseconds.
- L111 _private member_ `float InterpolationTime;` — Current interpolation time, in seconds.
- L114 _private member_ `float TargetDelayLineLength;` — Most recently set delay line length.
- L116 _private member_ `Audio::FLinearEase InterpolationInfo;`
- L119 _private member_ `TArray<Audio::FDelay> DelayLines;` — Delay lines for each channel.

#### class `USubmixEffectDelayPreset`  
`class USubmixEffectDelayPreset : public USoundEffectSubmixPreset`  
_L128-168_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L133 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectDelay)`
- L143 _public prototype_ `void SetDefaultSettings(const FSubmixEffectDelaySettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Delay")` — Sets object's default settings. This will update both the default UObject settings (and mark it as dirty), as well as any dynamically set settings.
- L147 _public function_ `float GetMaxDelayInMilliseconds() const` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Delay")` — Get the maximum delay possible.
- L154 _public prototype_ `void SetInterpolationTime(float Time);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Delay")` — Set the time it takes to interpolate between parameters, in milliseconds.
- L158 _public prototype_ `void SetDelay(float Length);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Delay")` — Set how long the delay actually is, in milliseconds.
- L161 _public prototype_ `virtual void OnInit() override;`
- L164 _public member_ `FSubmixEffectDelaySettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDefaultSettings, Category = SubmixEffectPreset, Meta = (ShowOnlyInnerProperties))`
- L167 _public member_ `FSubmixEffectDelaySettings DynamicSettings;` — `UPROPERTY(transient)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SYNTHESIS_API`
- L12 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectFilter.h` (Public)


#### enum `ESubmixFilterType`  
`enum class ESubmixFilterType : uint8`  
_L12-19_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `LowPass = 0`
- L15 _public enumerator_ `HighPass`
- L16 _public enumerator_ `BandPass`
- L17 _public enumerator_ `BandStop`
- L18 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESubmixFilterAlgorithm`  
`enum class ESubmixFilterAlgorithm : uint8`  
_L22-28_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `OnePole = 0`
- L25 _public enumerator_ `StateVariable`
- L26 _public enumerator_ `Ladder`
- L27 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSubmixEffectFilterSettings`  
`struct FSubmixEffectFilterSettings`  
_L36-55_
- reflection: `USTRUCT(BlueprintType)`
- L42 _public member_ `ESubmixFilterType FilterType = ESubmixFilterType::LowPass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Type"))` — What type of filter to use for the submix filter effect
- L46 _public member_ `ESubmixFilterAlgorithm FilterAlgorithm = ESubmixFilterAlgorithm::OnePole;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Circuit"))` — What type of filter algorithm to use for the submix filter effect
- L50 _public member_ `float FilterFrequency = 20000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Cutoff Frequency (hz)", ClampMin = "0.0", ClampMax = "20000.0", UIMin = "0.0", UIMax = "20000.0"))` — The output filter cutoff frequency (hz) [0.0, 20000.0]
- L54 _public member_ `float FilterQ = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter, meta = (DisplayName = "Resonance (Q)", ClampMin = "0.5", ClampMax = "10.0", UIMin = "0.5", UIMax = "10.0"))` — The output filter resonance (Q) [0.5, 10]

#### class `FSubmixEffectFilter`  
`class FSubmixEffectFilter : public FSoundEffectSubmix`  
_L57-116_
- inherits: `FSoundEffectSubmix`
- L60 _public prototype_ `FSubmixEffectFilter();`
- L61 _public prototype_ `virtual ~FSubmixEffectFilter() = default;`
- L64 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InData) override;`
- L65 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;`
- L69 _public prototype_ `virtual void OnPresetChanged() override;`
- L73 _public prototype_ `void SetFilterType(ESubmixFilterType InType);` — Sets the filter type
- L76 _public prototype_ `void SetFilterAlgorithm(ESubmixFilterAlgorithm InAlgorithm);` — Sets the filter algorithm
- L79 _public prototype_ `void SetFilterCutoffFrequency(float InFrequency);` — Sets the base filter cutoff frequency
- L82 _public prototype_ `void SetFilterCutoffFrequencyMod(float InFrequency);` — Sets the mod filter cutoff frequency
- L85 _public prototype_ `void SetFilterQ(float InQ);` — Sets the filter Q
- L88 _public prototype_ `void SetFilterQMod(float InQ);` — Sets the filter Q
- L92 _private prototype_ `void InitFilter();`
- L95 _private member_ `float SampleRate;` — Sample rate of the submix effect
- L98 _private member_ `Audio::FOnePoleFilter OnePoleFilter;` — Filters for each channel and type
- L99 _private member_ `Audio::FStateVariableFilter StateVariableFilter;`
- L100 _private member_ `Audio::FLadderFilter LadderFilter;`
- L103 _private member_ `Audio::IFilter* CurrentFilter;` — The current filter selected
- L106 _private member_ `ESubmixFilterAlgorithm FilterAlgorithm;` — Filter control data
- L107 _private member_ `ESubmixFilterType FilterType;`
- L109 _private member_ `float FilterFrequency;`
- L110 _private member_ `float FilterFrequencyMod;`
- L112 _private member_ `float FilterQ;`
- L113 _private member_ `float FilterQMod;`
- L115 _private member_ `int32 NumChannels;`

#### class `USubmixEffectFilterPreset`  
`class USubmixEffectFilterPreset : public USoundEffectSubmixPreset`  
_L124-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L129 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectFilter)`
- L137 _public prototype_ `void SetFilterType(ESubmixFilterType InType);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Filter")` — Sets the filter type
- L141 _public prototype_ `void SetFilterAlgorithm(ESubmixFilterAlgorithm InAlgorithm);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Filter")` — Sets the filter algorithm
- L145 _public prototype_ `void SetFilterCutoffFrequency(float InFrequency);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Filter")` — Sets the base filter cutoff frequency
- L149 _public prototype_ `void SetFilterCutoffFrequencyMod(float InFrequency);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Filter")` — Sets the mod filter cutoff frequency
- L153 _public prototype_ `void SetFilterQ(float InQ);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Filter")` — Sets the filter Q
- L157 _public prototype_ `void SetFilterQMod(float InQ);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|Filter")` — Sets the filter Q
- L162 _public member_ `FSubmixEffectFilterSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectFlexiverb.h` (Public)


#### struct `FSubmixEffectFlexiverbSettings`  
`struct FSubmixEffectFlexiverbSettings`  
_L12-38_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `float PreDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReverbParameters, meta = (DisplayName = "Pre Delay (ms)", ClampMin = "0.01", ClampMax = "30"))` — PreDelay - 0.01 < 10.0 < 40.0 - Amount of delay to the first echo in milliseconds.
- L22 _public member_ `float DecayTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReverbParameters, meta = (DisplayName = "Decay Time (seconds)", ClampMin = "0.4", ClampMax = "5.0"))` — Time in seconds it will take for the impulse response to decay to -60 dB.
- L26 _public member_ `float RoomDampening;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReverbParameters, meta = (ClampMin = "60.0", ClampMax = "12000.0"))` — Room Dampening - 0.0 < 0.85 < 1.0 - Frequency at which the room dampens.
- L29 _public member_ `int32 Complexity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReverbParameters, meta = (ClampMin = "2", ClampMax = "6"))`
- L31 _public function_ `FSubmixEffectFlexiverbSettings() : PreDelay(10.0f) , DecayTime(7.0f) , RoomDampening(220.0f) , Complexity(2)`

#### class `FSubmixEffectFlexiverb`  
`class FSubmixEffectFlexiverb : public FSoundEffectSubmix`  
_L40-70_
- inherits: `FSoundEffectSubmix`
- L43 _public prototype_ `FSubmixEffectFlexiverb();`
- L46 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InSampleRate) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L49 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L52 _public function_ `virtual uint32 GetDesiredInputChannelCountOverride() const override` — We want to receive downmixed submix audio to stereo input for the reverb effect
- L55 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;` — Process the input block of audio. Called on audio thread.
- L58 _public prototype_ `void SetEffectParameters(const Audio::FFlexiverbSettings& InReverbEffectParameters);` — Sets the reverb effect parameters based from audio thread code
- L61 _private prototype_ `void UpdateParameters();`
- L64 _private member_ `Audio::FFlexiverb Flexiverb;` — The reverb effect
- L67 _private member_ `Audio::TParams<Audio::FFlexiverbSettings> Params;` — The reverb effect params
- L69 _private member_ `bool bIsEnabled;`

#### class `USubmixEffectFlexiverbPreset`  
`class USubmixEffectFlexiverbPreset : public USoundEffectSubmixPreset`  
_L73-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L78 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectFlexiverb) UFUNCTION(BlueprintCallable, Category = "Audio|Effects") void SetSettings(const FSubmixEffectFlexiverbSettings& InSettings);`
- L84 _public member_ `FSubmixEffectFlexiverbSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta =(ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectMultiBandCompressor.h` (Public)


#### struct `FDynamicsBandSettings`  
`struct FDynamicsBandSettings`  
_L14-49_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `float CrossoverTopFrequency = 20000.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (ClampMin = "20.0", ClampMax = "20000.0", UIMin = "20.0", UIMax = "20000"))` — Frequency of the crossover between this band and the next. The last band will have this property ignored
- L24 _public member_ `float AttackTimeMsec = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (ClampMin = "1.0", ClampMax = "300.0", UIMin = "1.0", UIMax = "200.0"))` — The amount of time to ramp into any dynamics processing effect in milliseconds.
- L28 _public member_ `float ReleaseTimeMsec = 100.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (ClampMin = "20.0", ClampMax = "5000.0", UIMin = "20.0", UIMax = "5000.0"))` — The amount of time to release the dynamics processing effect in milliseconds
- L32 _public member_ `float ThresholdDb = -6.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (ClampMin = "-72.0", ClampMax = "0.0", UIMin = "-72.0", UIMax = "0.0"))` — The threshold at which to perform a dynamics processing operation
- L36 _public member_ `float Ratio = 1.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (ClampMin = "1.0", ClampMax = "20.0", UIMin = "1.0", UIMax = "20.0"))` — The dynamics processor ratio -- has different meaning depending on the processor type.
- L40 _public member_ `float KneeBandwidthDb = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics, meta = (DisplayName = "Knee (dB)", ClampMin = "0.0", ClampMax = "20.0", UIMin = "0.0", UIMax = "20.0"))` — The knee bandwidth of the compressor to use in dB
- L44 _public member_ `float InputGainDb = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gain, meta = (DisplayName = "Input Gain (dB)", ClampMin = "-12.0", ClampMax = "20.0", UIMin = "-12.0", UIMax = "20.0"))` — The input gain of the dynamics processor in dB
- L48 _public member_ `float OutputGainDb = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gain, meta = (DisplayName = "Output Gain (dB)", ClampMin = "-12.0", ClampMax = "20.0", UIMin = "-12.0", UIMax = "20.0"))` — The output gain of the dynamics processor in dB

#### struct `FSubmixEffectMultibandCompressorSettings`  
`struct FSubmixEffectMultibandCompressorSettings`  
_L53-107_
- reflection: `USTRUCT(BlueprintType)`
- desc: A submix dynamics processor
- L59 _public member_ `ESubmixEffectDynamicsProcessorType DynamicsProcessorType = ESubmixEffectDynamicsProcessorType::Compressor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Type"))` — Controls how each band will react to audio above its threshold
- L63 _public member_ `ESubmixEffectDynamicsPeakMode PeakMode = ESubmixEffectDynamicsPeakMode::RootMeanSquared;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics)` — Controls how quickly the bands will react to a signal above its threshold
- L67 _public member_ `ESubmixEffectDynamicsChannelLinkMode LinkMode = ESubmixEffectDynamicsChannelLinkMode::Average;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dynamics)` — Whether to compress all channels equally, and how to evaluate the overall level
- L71 _public member_ `float LookAheadMsec = 3.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response, meta = (DisplayName = "Look Ahead (ms)", ClampMin = "0.0", ClampMax = "50.0", UIMin = "0.0", UIMax = "50.0"))` — The amount of time to look ahead of the current audio. Allows for transients to be included in dynamics processing.
- L75 _public member_ `bool bAnalogMode = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Response)` — Toggles treating the attack and release envelopes as analog-style vs digital-style. Analog will respond a bit more naturally/slower.
- L79 _public member_ `bool bFourPole = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crossover)` — Turning off FourPole mode will use cheaper, shallower 2-pole crossovers
- L83 _public member_ `bool bBypass = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (DisplayName = "Bypass", DisplayAfter = "DynamicsProcessorType"))` — Whether or not to bypass effect
- L86 _public member_ `ESubmixEffectDynamicsKeySource KeySource = ESubmixEffectDynamicsKeySource::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (EditCondition = "!bBypass"))`
- L90 _public member_ `TObjectPtr<UAudioBus> ExternalAudioBus = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (EditCondition = "!bBypass && KeySource == ESubmixEffectDynamicsKeySource::AudioBus", EditConditionHides))` — If set, uses output of provided submix as modulator of input signal for dynamics processor (Uses input signal as default modulator)
- L94 _public member_ `TObjectPtr<USoundSubmix> ExternalSubmix = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (EditCondition = "!bBypass && KeySource == ESubmixEffectDynamicsKeySource::Submix", EditConditionHides))` — If set, uses output of provided submix as modulator of input signal for dynamics processor (Uses input signal as default modulator)
- L98 _public member_ `float KeyGainDb = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (DisplayName = "External Input Gain (dB)", EditCondition = "ExternalSubmix != nullptr || ExternalAudioBus != nullptr", UIMin = "-60.0", UIMax = "30.0"))` — Gain to apply to key signal if external input is supplied
- L102 _public member_ `bool bKeyAudition = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sidechain, meta = (DisplayName = "Key Audition", EditCondition = "!bBypass"))` — Audition the key modulation signal, bypassing enveloping and processing the input signal.
- L106 _public member_ `TArray<FDynamicsBandSettings> Bands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bands)` — Each band is a full dynamics processor, affecting at a unique frequency range

#### class `FSubmixEffectMultibandCompressor`  
`class FSubmixEffectMultibandCompressor : public FSoundEffectSubmix`  
_L109-177_
- inherits: `FSoundEffectSubmix`
- L112 _public prototype_ `FSubmixEffectMultibandCompressor();`
- L114 _public prototype_ `virtual ~FSubmixEffectMultibandCompressor();`
- L117 _public prototype_ `Audio::FDeviceId GetDeviceId() const;` — Gets the effect's deviceId that owns it
- L120 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InSampleRate) override;` — Called on an audio effect at initialization on main thread before audio processing begins.
- L123 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;` — Process the input block of audio. Called on audio thread.
- L126 _public prototype_ `virtual void OnPresetChanged() override;` — Called when an audio effect preset is changed
- L129 _public prototype_ `void Initialize(FSubmixEffectMultibandCompressorSettings& Settings);` — called from OnPresetChanged when something is changed that needs extra attention
- L133 _protected prototype_ `void ResetKey();` — ISubmixBufferListener interface
- L134 _protected prototype_ `void UpdateKeyFromSettings(const FSubmixEffectMultibandCompressorSettings& InSettings);`
- L135 _protected prototype_ `bool UpdateKeySourcePatch();`
- L137 _protected prototype_ `void OnDeviceCreated(Audio::FDeviceId InDeviceId);`
- L138 _protected prototype_ `void OnDeviceDestroyed(Audio::FDeviceId InDeviceId);`
- L140 _protected prototype_ `Audio::FMixerDevice* GetMixerDevice();`
- L142 _protected member_ `Audio::FAlignedFloatBuffer AudioExternal;`
- L145 _private member_ `static constexpr int32 MaxBlockNumSamples = 8192;` — 8 channels * 1024 samples
- L147 _private member_ `FKeySource KeySource;`
- L149 _private member_ `Audio::FDeviceId DeviceId;`
- L151 _private member_ `FDelegateHandle DeviceCreatedHandle;`
- L152 _private member_ `FDelegateHandle DeviceDestroyedHandle;`
- L154 _private member_ `Audio::FAlignedFloatBuffer ScratchBuffer;`
- L156 _private member_ `TArray<Audio::FDynamicsProcessor> DynamicsProcessors;`
- L158 _private member_ `Audio::FLinkwitzRileyBandSplitter KeyBandSplitter;`
- L159 _private member_ `Audio::FMultibandBuffer KeyMultiBandBuffer;`
- L161 _private member_ `Audio::FLinkwitzRileyBandSplitter BandSplitter;`
- L162 _private member_ `Audio::FMultibandBuffer MultiBandBuffer;`
- L165 _private member_ `int32 PrevNumBands = 0;` — cached crossover + band info, so we can check if they need a re-build when editing
- L166 _private member_ `TArray<float> PrevCrossovers;`
- L167 _private member_ `bool bPrevFourPole = true;`
- L169 _private member_ `int32 NumChannels = 0;`
- L170 _private member_ `int32 FrameSize = 0;`
- L171 _private member_ `float SampleRate = 48000.f;`
- L173 _private member_ `bool bInitialized = false;`
- L174 _private member_ `bool bBypass = false;`

#### class `USubmixEffectMultibandCompressorPreset`  
`class USubmixEffectMultibandCompressorPreset : public USoundEffectSubmixPreset`  
_L180-214_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundEffectSubmixPreset`
- L185 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectMultibandCompressor) virtual void OnInit() override;`
- L190 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& InChainEvent) override;`
- L194 _public prototype_ `void ResetKey();` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L199 _public prototype_ `void SetAudioBus(UAudioBus* AudioBus);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Sets the source key input as the provided AudioBus' output.  If no object is provided, key is set to effect's input.
- L204 _public prototype_ `void SetExternalSubmix(USoundSubmix* Submix);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")` — Sets the source key input as the provided Submix's output.  If no object is provided, key is set to effect's input.
- L207 _public prototype_ `void SetSettings(const FSubmixEffectMultibandCompressorSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects")`
- L210 _public member_ `FSubmixEffectMultibandCompressorSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, meta = (ShowOnlyInnerProperties))`
- L213 _private prototype_ `void SetKey(ESubmixEffectDynamicsKeySource InKeySource, UObject* InObject, int32 InNumChannels = 0);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`
- L11 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectStereoDelay.h` (Public)


#### struct `FSubmixEffectStereoDelaySettings`  
`struct FSubmixEffectStereoDelaySettings`  
_L13-56_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `EStereoDelaySourceEffect DelayMode = EStereoDelaySourceEffect::PingPong;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay")` — What mode to set the stereo delay effect.
- L23 _public member_ `float DelayTimeMsec = 500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (ClampMin = "0.0", ClampMax = "2000.0", UIMin = "0.0", UIMax = "2000.0"))` — The base amount of delay in the left and right channels of the delay line.
- L27 _public member_ `float Feedback = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of audio to feedback into the delay line once the delay has been tapped.
- L31 _public member_ `float DelayRatio = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — Delay spread for left and right channels. Allows left and right channels to have differential delay amounts. Useful for stereo channel decorrelation.
- L35 _public member_ `float WetLevel = 0.4f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of delay effect to mix with the dry input signal into the effect.
- L39 _public member_ `float DryLevel = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The dry level of the effect
- L43 _public member_ `bool bFilterEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay")` — Whether or not to enable filtering
- L47 _public member_ `EStereoDelayFiltertype FilterType = EStereoDelayFiltertype::Lowpass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (EditCondition = "bFilterEnabled"))` — Filter type to feed feedback audio to
- L51 _public member_ `float FilterFrequency = 20000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (ClampMin = "20.0", ClampMax = "20000", UIMin = "20.0", UIMax = "20000", EditCondition = "bFilterEnabled"))` — Cutoff frequency of the filter
- L55 _public member_ `float FilterQ = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay", meta = (ClampMin = "0.5", ClampMax = "10.0", UIMin = "0.5", UIMax = "10.0", EditCondition = "bFilterEnabled"))` — Q of the filter

#### class `FSubmixEffectStereoDelay`  
`class FSubmixEffectStereoDelay : public FSoundEffectSubmix`  
_L58-77_
- inherits: `FSoundEffectSubmix`
- L61 _public prototype_ `FSubmixEffectStereoDelay();`
- L62 _public prototype_ `~FSubmixEffectStereoDelay();`
- L65 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InData) override;`
- L66 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;`
- L70 _public prototype_ `virtual void OnPresetChanged() override;`
- L75 _private member_ `Audio::FAlignedFloatBuffer ScratchStereoBuffer;`
- L76 _private member_ `Audio::FDelayStereo DelayStereo;`

#### class `USubmixEffectStereoDelayPreset`  
`class USubmixEffectStereoDelayPreset : public USoundEffectSubmixPreset`  
_L85-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- L90 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectStereoDelay)`
- L98 _public prototype_ `virtual void OnInit() override;`
- L101 _public member_ `FSubmixEffectStereoDelaySettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, Meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectStereoToQuad.h` (Public)


#### struct `FSubmixEffectStereoToQuadSettings`  
`struct FSubmixEffectStereoToQuadSettings`  
_L12-24_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `bool bFlipChannels = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StereoToQuad")` — Whether or not to flip the left and right input channels when sending to the rear channel. This can be useful to have a stereo field when hearing audio to the left and right in surround output configuration.
- L23 _public member_ `float RearChannelGain = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StereoToQuad")` — The gain (in decibels) of the rear channels

#### class `FSubmixEffectStereoToQuad`  
`class FSubmixEffectStereoToQuad : public FSoundEffectSubmix`  
_L26-46_
- inherits: `FSoundEffectSubmix`
- L29 _public prototype_ `FSubmixEffectStereoToQuad();`
- L30 _public prototype_ `~FSubmixEffectStereoToQuad();`
- L33 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InData) override;`
- L34 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;`
- L38 _public prototype_ `virtual void OnPresetChanged() override;`
- L43 _private member_ `FSubmixEffectStereoToQuadSettings CurrentSettings;`
- L44 _private member_ `float LinearGain = 1.0f;`
- L45 _private member_ `Audio::FAlignedFloatBuffer ScratchStereoBuffer;`

#### class `USubmixEffectStereoToQuadPreset`  
`class USubmixEffectStereoToQuadPreset : public USoundEffectSubmixPreset`  
_L50-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundEffectSubmixPreset`
- desc: Submix effect which sends stereo audio to quad (left surround and right surround) if the channel count is greater than 2.
- L55 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectStereoToQuad)`
- L63 _public prototype_ `virtual void OnInit() override;`
- L66 _public member_ `FSubmixEffectStereoToQuadSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, Meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SubmixEffects/SubmixEffectTapDelay.h` (Public)


#### enum `ETapLineMode`  
`enum class ETapLineMode : uint8`  
_L14-24_
- reflection: `UENUM()`
- L17 _public enumerator_ `SendToChannel` — Send tap audio output to a channel directly
- L20 _public enumerator_ `Panning` — Allow tap to pan between channels based on azimuth angle
- L23 _public enumerator_ `Disabled` — Disables the tap audio and performs a fadeout

#### struct `FTapDelayInterpolationInfo`  
`struct FTapDelayInterpolationInfo`  
_L26-43_
- L28 _public function_ `FTapDelayInterpolationInfo()`
- L32 _public prototype_ `void Init(float SampleRate);`
- L34 _public prototype_ `void SetGainValue(float Value, float InterpolationTime);`
- L35 _public prototype_ `float GetGainValue();`
- L37 _public prototype_ `void SetLengthValue(float Value, float InterpolationTime);`
- L38 _public prototype_ `float GetLengthValue();`
- L41 _private member_ `Audio::FLinearEase LengthParam;`
- L42 _private member_ `Audio::FLinearEase GainParam;`

#### struct `FTapDelayInfo`  
`struct FTapDelayInfo`  
_L46-78_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public member_ `ETapLineMode TapLineMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime)` — Whether the tap line should send directly to a channel, pan, or not produce sound at all.
- L56 _public member_ `float DelayLength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime, meta = (DisplayName = "Delay Length (ms)", ClampMin = "0.0", ClampMax = "10000"))` — Amount of time before this echo is heard in milliseconds.
- L60 _public member_ `float Gain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime, meta = (ClampMin = "-60.0", ClampMax = "6.0"))` — How loud this echo should be, in decibels.
- L64 _public member_ `int32 OutputChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime, meta = (EditCondition = "TapLineMode == ETapLineMode::SendToChannel", ClampMin = "0", ClampMax = "8"))` — When the Tap Line Mode is set to Send To Channel, designates index of channel from which the echo should play.
- L70 _public member_ `float PanInDegrees;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime, meta = (EditCondition = "TapLineMode == ETapLineMode::Panning", ClampMin = "-180.0", ClampMax = "180.0"))` — When the Tap Line Mode is set to Panning, designates the angle at which the echo should be panned. On Surround systems, 0 is directly in front of the listener, -90 is left, 90 is right, and 180/-180 is directly behind the listener. On Stereo systems, <-90 is fully in the left ear, and >90 is fully in the right ear
- L73 _public member_ `int32 TapId;` — `UPROPERTY(Transient, meta = (IgnoreForMemberInitializationTest))`
- L77 _public prototype_ `FTapDelayInfo();`

#### struct `FSubmixEffectTapDelaySettings`  
`struct FSubmixEffectTapDelaySettings`  
_L86-101_
- reflection: `USTRUCT(BlueprintType)`
- L92 _public member_ `float MaximumDelayLength = 10000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Initialization, meta = (DisplayName = "Maximum Delay Length (ms)", ClampMin = "10.0", UIMin = "10.0", UIMax = "20000.0"))` — Maximum possible length for a delay, in milliseconds. Changing this at runtime will reset the effect.
- L96 _public member_ `float InterpolationTime = 400.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime, meta = (DisplayName = "Interpolation Time (ms)", ClampMin = "0.0", UIMin = "0.0", UIMax = "20000.0"))` — Number of milliseconds over which a tap will reach it's set length and gain. Smaller values are more responsive, while larger values will make pitching less dramatic.
- L100 _public member_ `TArray<FTapDelayInfo> Taps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realtime)` — Each tap's metadata

#### class `FSubmixEffectTapDelay`  
`class FSubmixEffectTapDelay : public FSoundEffectSubmix`  
_L103-162_
- inherits: `FSoundEffectSubmix`
- L106 _public prototype_ `FSubmixEffectTapDelay();`
- L108 _public prototype_ `virtual ~FSubmixEffectTapDelay() = default;`
- L111 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InData) override;`
- L112 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;`
- L116 _public prototype_ `virtual void OnPresetChanged() override;`
- L120 _public prototype_ `void SetEffectParameters(const FSubmixEffectTapDelaySettings& InTapEffectParameters);` — Sets the reverb effect parameters based from audio thread code
- L122 _public prototype_ `void AddTap(int32 TapId);`
- L123 _public prototype_ `void RemoveTap(int32 TapId);`
- L124 _public prototype_ `void SetTap(int32 TapId, const FTapDelayInfo& DelayInfo);`
- L127 _public prototype_ `void SetInterpolationTime(float Time);` — Set the interpolation time
- L132 _private prototype_ `void UpdateParameters();` — This is called on the audio render thread to query the parameters.
- L135 _private prototype_ `void UpdateInterpolations();` — This is called in UpdateParameters to set up our per-sample parameter interpolation.
- L138 _private member_ `Audio::TParams<FSubmixEffectTapDelaySettings> Params;` — Params struct used to pass parameters safely to the audio render thread.
- L141 _private member_ `float SampleRate;` — Sample rate cached at initialization. Used to gauge interpolation times.
- L144 _private member_ `float MaxDelayLineLength;` — Current maximum delay line length, in milliseconds.
- L147 _private member_ `float InterpolationTime;` — Current interpolation time, in seconds.
- L150 _private member_ `TArray<FTapDelayInfo> TargetTaps;` — Target parameters that we interpolate to. Updated directly from params.
- L153 _private member_ `TArray<FTapDelayInterpolationInfo> CurrentTaps;` — Current state of each tap.
- L156 _private member_ `int32 TapIncrementsRemaining;` — How many increments we have left before all CurrentTaps reach the TargetTaps
- L159 _private member_ `bool bSettingsModified;` — Whether taps have been modified.
- L161 _private member_ `Audio::FDelay DelayLine;`

#### class `USubmixEffectTapDelayPreset`  
`class USubmixEffectTapDelayPreset : public USoundEffectSubmixPreset`  
_L170-217_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent), AutoExpandCategories = (Realtime))`
- inherits: `USoundEffectSubmixPreset`
- L175 _public prototype_ `EFFECT_PRESET_METHODS(SubmixEffectTapDelay)`
- L183 _public prototype_ `void AddTap(int32& TapId);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|TapDelay")` — Adds a dynamic tap delay with the given settings. Returns the tap id.
- L187 _public prototype_ `void RemoveTap(int32 TapId);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|TapDelay")` — Remove the tap from the preset.
- L191 _public prototype_ `void SetTap(int32 TapId, const FTapDelayInfo& TapInfo);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|TapDelay")` — Modify a specific tap.
- L195 _public prototype_ `void GetTap(int32 TapId, FTapDelayInfo& TapInfo);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|TapDelay")` — Get the current info about a specific tap.
- L199 _public prototype_ `void GetTapIds(TArray<int32>& TapIds);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|TapDelay")` — Retrieve an array of all tap ids for the submix effect.
- L203 _public function_ `float GetMaxDelayInMilliseconds()` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|TapDelay")` — Get the maximum delay possible.
- L207 _public prototype_ `void SetInterpolationTime(float Time);` — `UFUNCTION(BlueprintCallable, Category = "Audio|Effects|TapDelay")` — Set the time it takes to interpolate between parameters, in milliseconds.
- L211 _public prototype_ `virtual void OnInit() override;`
- L214 _public member_ `FSubmixEffectTapDelaySettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubmixEffectPreset, Meta = (ShowOnlyInnerProperties))`
- L216 _public member_ `FSubmixEffectTapDelaySettings DynamicSettings;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTapDelay, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTapDelay, Log, All);`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SynthComponents/EpicSynth1Component.h` (Public)


#### struct `FEpicSynth1Patch`  
`struct FEpicSynth1Patch`  
_L13-24_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `ESynth1PatchSource PatchSource = ESynth1PatchSource::LFO1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — A modular synth patch source (e.g. LFO1/LFO2/Modulation Envelope)
- L23 _public member_ `TArray<FSynth1PatchCable> PatchCables;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Patch cables to patch destinations from the patch source.

#### struct `FModularSynthPreset`  
`struct FModularSynthPreset : public FTableRowBase`  
_L27-327_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- L33 _public member_ `uint32 bEnablePolyphony : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not to allow multiple synth voices.
- L37 _public member_ `ESynth1OscType Osc1Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — What type of oscillator to use for oscillator 1
- L41 _public member_ `float Osc1Gain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The linear gain of oscillator 1 [0.0, 1.0]
- L45 _public member_ `float Osc1Octave;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "-8.0", ClampMax = "8.0", UIMin = "-8.0", UIMax = "8.0"))` — The octave of oscillator 1. [-8.0, 8.0]
- L49 _public member_ `float Osc1Semitones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "-12.0", ClampMax = "12.0", UIMin = "-12.0", UIMax = "12.0"))` — The semi-tones of oscillator 1. [-12.0, 12.0]
- L53 _public member_ `float Osc1Cents;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "-100.0", ClampMax = "100.0", UIMin = "-100.0", UIMax = "100.0"))` — The cents (hundreds of a semitone) of oscillator 1. [-100.0, 100.0]
- L57 _public member_ `float Osc1PulseWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The pulsewidth of oscillator 1 (when using a square wave type oscillator). [0.0, 1.0]
- L61 _public member_ `ESynth1OscType Osc2Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — What type of oscillator to use for oscillator 2
- L65 _public member_ `float Osc2Gain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The linear gain of oscillator 2 [0.0, 1.0]
- L69 _public member_ `float Osc2Octave;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "-8.0", ClampMax = "8.0", UIMin = "-8.0", UIMax = "8.0"))` — The octave of oscillator 2. [-8.0, 8.0]
- L73 _public member_ `float Osc2Semitones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "-12.0", ClampMax = "12.0", UIMin = "-12.0", UIMax = "12.0"))` — The semi-tones of oscillator 2. [-12.0, 12.0]
- L77 _public member_ `float Osc2Cents;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "-100.0", ClampMax = "100.0", UIMin = "-100.0", UIMax = "100.0"))` — The cents (hundreds of a semitone) of oscillator 2. [-100.0, 100.0]
- L81 _public member_ `float Osc2PulseWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The pulsewidth of oscillator 2 (when using a square wave type oscillator). [0.0, 1.0]
- L85 _public member_ `float Portamento;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of portamento to use, which is the amount of pitch sliding from current note to next [0.0, 1.0]
- L89 _public member_ `uint32 bEnableUnison : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Enables forcing the oscillators to have no stereo spread.
- L93 _public member_ `uint32 bEnableOscillatorSync : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not oscillator sync is enabled. Oscillator sync forces oscillator 2's phase to align with oscillator 1's phase.
- L97 _public member_ `float Spread;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of stereo spread to use between oscillator 1 and oscillator 2 [0.0, 1.0]
- L101 _public member_ `float Pan;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — The stereo pan to use. 0.0 is center. -1.0 is left, 1.0 is right.
- L105 _public member_ `float LFO1Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "50.0", UIMin = "0.0", UIMax = "50.0"))` — The frequency to use for LFO 1 (in hz) [0.0, 50.0]
- L109 _public member_ `float LFO1Gain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The linear gain to use for LFO 1 [0.0, 1.0]
- L113 _public member_ `ESynthLFOType LFO1Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The type of LFO to use for LFO 1
- L117 _public member_ `ESynthLFOMode LFO1Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The mode to use for LFO 1
- L121 _public member_ `ESynthLFOPatchType LFO1PatchType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The built-in patch type to use for LFO 1 (you can route this to any patchable parameter using the Patches parameter)
- L125 _public member_ `float LFO2Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "50.0", UIMin = "0.0", UIMax = "50.0"))` — The frequency to use for LFO 2 (in hz) [0.0, 50.0]
- L129 _public member_ `float LFO2Gain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The linear gain to use for LFO 2 [0.0, 1.0]
- L133 _public member_ `ESynthLFOType LFO2Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The type of LFO to use for LFO 2
- L137 _public member_ `ESynthLFOMode LFO2Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The mode to use for LFO 2
- L141 _public member_ `ESynthLFOPatchType LFO2PatchType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The built-in patch type to use for LFO 2 (you can route this to any patchable parameter using the Patches parameter)
- L145 _public member_ `float GainDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (DisplayName = "Gain (dB)", ClampMin = "-90.0", ClampMax = "20.0", UIMin = "-90.0", UIMax = "20.0"))` — The overall gain to use for the synthesizer in dB [-90.0, 20.0]
- L149 _public member_ `float AttackTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10000.0"))` — The amplitude envelope attack time (in ms) [0.0, 10000]
- L153 _public member_ `float DecayTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10000.0"))` — The amplitude envelope decay time (in ms)[0.0, 10000]
- L157 _public member_ `float SustainGain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amplitude envelope sustain amount (linear gain) [0.0, 1.0]
- L161 _public member_ `float ReleaseTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10000.0"))` — The amplitude envelope release time (in ms) [0.0, 10000]
- L165 _public member_ `ESynthModEnvPatch ModEnvPatchType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The built-in patch type for the envelope modulator
- L169 _public member_ `ESynthModEnvBiasPatch ModEnvBiasPatchType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The built-in patch type for the envelope modulator bias output. Bias is when the envelope output is offset by the sustain gain.
- L173 _public member_ `uint32 bInvertModulationEnvelope : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not to invert the modulation envelope
- L177 _public member_ `uint32 bInvertModulationEnvelopeBias : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not to invert the modulation envelope bias output
- L181 _public member_ `float ModulationEnvelopeDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The "depth" (i.e. how much) modulation envelope to use. This scales the modulation envelope output. [0.0, 1.0]
- L185 _public member_ `float ModulationEnvelopeAttackTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))` — The modulation envelope attack time (in ms) [0.0, 10000]
- L189 _public member_ `float ModulationEnvelopeDecayTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))` — The modulation envelope decay time (in ms) [0.0, 10000]
- L193 _public member_ `float ModulationEnvelopeSustainGain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The modulation envelope sustain gain (linear gain) [0.0, 1.0]
- L197 _public member_ `float ModulationEnvelopeReleaseTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))` — The modulation envelope release time (in ms) [0.0, 10000]
- L201 _public member_ `uint32 bLegato : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not to use legato mode.
- L205 _public member_ `uint32 bRetrigger : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not to use retrigger mode.
- L209 _public member_ `float FilterFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "20000.0", UIMin = "0.0", UIMax = "20000.0"))` — The output filter cutoff frequency (hz) [0.0, 20000.0]
- L213 _public member_ `float FilterQ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.5", ClampMax = "10.0", UIMin = "0.5", UIMax = "10.0"))` — The output filter resonance (Q) [0.5, 10]
- L217 _public member_ `ESynthFilterType FilterType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The output filter type (lowpass, highpass, bandpass, bandstop)
- L221 _public member_ `ESynthFilterAlgorithm FilterAlgorithm;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The output filter circuit/algorithm type (one-pole ladder, ladder, state-variable)
- L225 _public member_ `uint32 bStereoDelayEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not stereo delay is enabled on the synth
- L229 _public member_ `ESynthStereoDelayMode StereoDelayMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The stereo delay mode of the synth
- L233 _public member_ `float StereoDelayTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "2000.0", UIMin = "0.0", UIMax = "2000.0"))` — The stereo delay time (in ms) [0.0, 2000.0]
- L237 _public member_ `float StereoDelayFeedback;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of feedback in the stereo delay line [0.0, 1.0]
- L241 _public member_ `float StereoDelayWetlevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The output wet level to use for the stereo delay time [0.0, 1.0]
- L245 _public member_ `float StereoDelayRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The ratio between left and right stereo delay lines (wider value is more separation) [0.0, 1.0]
- L249 _public member_ `uint32 bChorusEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Whether or not the chorus effect is enabled
- L253 _public member_ `float ChorusDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The depth of the chorus effect [0.0, 1.0]
- L257 _public member_ `float ChorusFeedback;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The amount of feedback in the chorus effect [0.0, 1.0]
- L261 _public member_ `float ChorusFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset", meta = (ClampMin = "0.0", ClampMax = "20.0", UIMin = "0.0", UIMax = "20.0"))` — The chorus LFO frequency [0.0, 20.0]
- L265 _public member_ `TArray<FEpicSynth1Patch> Patches;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The modular synth patch cords to use for the synth. Allows routing the LFO1/LFO2 and Modulation Envelope to any patchable destination.
- L267 _public function_ `FModularSynthPreset() : bEnablePolyphony(false) , Osc1Type(ESynth1OscType::Saw) , Osc1Gain(1.0f) , Osc1Octave(0.0f) , Osc1Semitones(0.0f) , Osc1Cents(0.0f) , Osc1PulseWidth(0.5f) , Osc2Type(ESynth1OscType::Saw) , Osc2Gain(1.0f) , Osc2Octave(0.0f) , Osc2Semitones(0.0f) , Osc2Cents(2.5f) , Osc2PulseWidth(0.5f) , Portamento(0.0f) , bEnableUnison(false) , bEnableOscillatorSync(false) , Spread(0.5f) , Pan(0.0f) , LFO1Frequency(1.0f) , LFO1Gain(0.0f) , LFO1Type(ESynthLFOType::Sine) , LFO1Mode(ESynthLFOMode::Sync) , LFO1PatchType(ESynthLFOPatchType::PatchToNone) , LFO2Frequency(1.0f) , LFO2Gain(0.0f) , LFO2Type(ESynthLFOType::Sine) , LFO2Mode(ESynthLFOMode::Sync) , LFO2PatchType(ESynthLFOPatchType::PatchToNone) , GainDb(-3.0f) , AttackTime(10.0f) , DecayTime(100.0f) , SustainGain(0.707f) , ReleaseTime(5000.0f) , ModEnvPatchType(ESynthModEnvPatch::PatchToNone) , ModEnvBiasPatchType(ESynthModEnvBiasPatch::PatchToNone) , bInvertModulationEnvelope(false) , bInvertModulationEnvelopeBias(false) , ModulationEnvelopeDepth(1.0f) , ModulationEnvelopeAttackTime(10.0f)`

#### struct `FModularSynthPresetBankEntry`  
`struct FModularSynthPresetBankEntry`  
_L330-343_
- reflection: `USTRUCT(BlueprintType)`
- L335 _public member_ `FString PresetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")`
- L338 _public member_ `FModularSynthPreset Preset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")`
- L340 _public function_ `FModularSynthPresetBankEntry() : PresetName(TEXT("Init"))`

#### class `UModularSynthPresetBank`  
`class UModularSynthPresetBank : public UObject`  
_L347-355_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `UObject`
- L354 _public member_ `TArray<FModularSynthPresetBankEntry> Presets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")`

#### class `UModularSynthLibrary`  
`class UModularSynthLibrary : public UBlueprintFunctionLibrary`  
_L358-365_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L364 _private prototype_ `static void AddModularSynthPresetToBankAsset(UModularSynthPresetBank* InBank, const FModularSynthPreset& Preset, const FString& PresetName);` — `UFUNCTION(BlueprintCallable, Category = "Synthesis")` — Adds the modular synth preset to the bank asset in the content browser. Only call during editor.

#### class `UModularSynthComponent`  
`class UModularSynthComponent : public USynthComponent`  
_L373-659_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent`
- desc: UModularSynthComponent Implementation of a USynthComponent.
- L377 _private prototype_ `UModularSynthComponent(const FObjectInitializer& ObjectInitializer);`
- L380 _private prototype_ `virtual bool Init(int32& SampleRate) override;` — Initialize the synth component
- L383 _private prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;` — Called to generate more audio
- L389 _public member_ `int32 VoiceCount;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Synth|VoiceCount", meta = (ClampMin = "1", ClampMax = "32"))` — The voice count to use for the synthesizer. Cannot be changed
- L395 _public prototype_ `void NoteOn(const float Note, const int32 Velocity, const float Duration = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Play a new note. Optionally pass in a duration to automatically turn off the note.
- L399 _public prototype_ `void NoteOff(const float Note, const bool bAllNotesOff = false, const bool bKillAllNotes = false);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Stop the note (will only do anything if a voice is playing with that note)
- L404 _public prototype_ `void SetEnablePolyphony(bool bEnablePolyphony);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not to use polyphony for the synthesizer. @param bEnablePolyphony Whether or not to enable polyphony for the synth.
- L410 _public prototype_ `void SetOscGain(int32 OscIndex, float OscGain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the oscillator gain. @param OscIndex Which oscillator to set the type for. @param OscGain The oscillator gain.
- L416 _public prototype_ `void SetOscGainMod(int32 OscIndex, float OscGainMod);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the oscillator gain modulation. @param OscIndex Which oscillator to set the type for. @param OscGainMod The oscillator gain modulation to use.
- L422 _public prototype_ `void SetOscFrequencyMod(int32 OscIndex, float OscFreqMod);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the oscillator frequency modulation @param OscIndex Which oscillator to set the type for. @param OscFreqMod The oscillator frequency modulation to use.
- L428 _public prototype_ `void SetOscType(int32 OscIndex, ESynth1OscType OscType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the oscillator type. @param OscIndex Which oscillator to set the type for. @param OscType The oscillator type to set.
- L434 _public prototype_ `void SetOscOctave(int32 OscIndex, float Octave);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the oscillator octaves @param OscIndex Which oscillator to set the type for. @param Octave Which octave to set the oscillator to (relative to base frequency/pitch).
- L440 _public prototype_ `void SetOscSemitones(int32 OscIndex, float Semitones);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the oscillator semitones. @param OscIndex Which oscillator to set the type for. @param Semitones The amount of semitones to set the oscillator to (relative to base frequency/pitch).
- L446 _public prototype_ `void SetOscCents(int32 OscIndex, float Cents);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the oscillator cents. @param OscIndex Which oscillator to set the type for. @param Cents The amount of cents to set the oscillator to (relative to base frequency/pitch)..
- L450 _public prototype_ `void SetPitchBend(float PitchBend);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the synth pitch bend amount.
- L454 _public prototype_ `void SetPortamento(float Portamento);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the synth portamento [0.0, 1.0]
- L458 _public prototype_ `void SetOscPulsewidth(int32 OscIndex, float Pulsewidth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the square wave pulsewidth [0.0, 1.0]
- L462 _public prototype_ `void SetEnableUnison(bool EnableUnison);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not the synth is in unison mode (i.e. no spread)
- L466 _public prototype_ `void SetOscSync(const bool bIsSynced);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set whether or not to follow the phase of osc2 to osc1
- L470 _public prototype_ `void SetPan(float Pan);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the pan of the synth [-1.0, 1.0].
- L474 _public prototype_ `void SetSpread(float Spread);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the amount of spread of the oscillators. [0.0, 1.0]
- L480 _public prototype_ `void SetLFOFrequency(int32 LFOIndex, float FrequencyHz);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the LFO frequency in hz @param LFOIndex Which LFO to set the frequency for. @param FrequencyHz The LFO frequency to use.
- L486 _public prototype_ `void SetLFOFrequencyMod(int32 LFOIndex, float FrequencyModHz);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the LFO frequency modulation in hz @param LFOIndex Which LFO to set the frequency for. @param FrequencyModHz The LFO frequency to use.
- L492 _public prototype_ `void SetLFOGain(int32 LFOIndex, float Gain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the LFO gain factor @param LFOIndex Which LFO to set the frequency for. @param Gain The gain factor to use for the LFO.
- L498 _public prototype_ `void SetLFOGainMod(int32 LFOIndex, float GainMod);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the LFO gain mod factor (external modulation) @param LFOIndex Which LFO to set the frequency for. @param Gain The gain factor to use for the LFO.
- L504 _public prototype_ `void SetLFOType(int32 LFOIndex, ESynthLFOType LFOType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the LFO type @param LFOIndex Which LFO to set the frequency for. @param LFOType The LFO type to use.
- L510 _public prototype_ `void SetLFOMode(int32 LFOIndex, ESynthLFOMode LFOMode);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the LFO type @param LFOIndex Which LFO to set the frequency for. @param LFOMode The LFO mode to use.
- L516 _public prototype_ `void SetLFOPatch(int32 LFOIndex, ESynthLFOPatchType LFOPatchType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the LFO patch type. LFO patch determines what parameter is modulated by the LFO. @param LFOIndex Which LFO to set the frequency for. @param LFOPatchType The LFO patch type to use.
- L520 _public prototype_ `void SetGainDb(float GainDb);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio", meta = (DisplayName = "Set Gain (dB)"))` — Sets the synth gain in decibels.
- L524 _public prototype_ `void SetAttackTime(float AttackTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope attack time in msec.
- L528 _public prototype_ `void SetDecayTime(float DecayTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope decay time in msec.
- L532 _public prototype_ `void SetSustainGain(float SustainGain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope sustain gain value.
- L536 _public prototype_ `void SetReleaseTime(float ReleaseTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope release time in msec.
- L540 _public prototype_ `void SetModEnvPatch(const ESynthModEnvPatch InPatchType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not to modulate a param based on the envelope. Uses bias envelope output (offset from sustain gain).
- L544 _public prototype_ `void SetModEnvBiasPatch(const ESynthModEnvBiasPatch InPatchType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not to modulate a param based on the envelope. Uses bias envelope output (offset from sustain gain).
- L548 _public prototype_ `void SetModEnvInvert(const bool bInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not to invert the envelope modulator.
- L552 _public prototype_ `void SetModEnvBiasInvert(const bool bInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not to invert the bias output of the envelope modulator.
- L556 _public prototype_ `void SetModEnvDepth(const float Depth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope modulator depth (amount to apply the output modulation)
- L560 _public prototype_ `void SetModEnvAttackTime(const float AttackTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope modulator attack time in msec
- L564 _public prototype_ `void SetModEnvDecayTime(const float DecayTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope modulator attack time in msec
- L568 _public prototype_ `void SetModEnvSustainGain(const float SustainGain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope modulator sustain gain
- L572 _public prototype_ `void SetModEnvReleaseTime(const float Release);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the envelope modulator release
- L576 _public prototype_ `void SetEnableLegato(bool LegatoEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not to use legato for the synthesizer.
- L580 _public prototype_ `void SetEnableRetrigger(bool RetriggerEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not to retrigger envelope per note on.
- L584 _public prototype_ `void SetFilterFrequency(float FilterFrequencyHz);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the filter cutoff frequency in hz.
- L588 _public prototype_ `void SetFilterFrequencyMod(float FilterFrequencyHz);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the filter cutoff frequency in hz.
- L592 _public prototype_ `void SetFilterQ(float FilterQ);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the filter Q (resonance)
- L596 _public prototype_ `void SetFilterQMod(float FilterQ);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets a modulated filter Q (resonance)
- L600 _public prototype_ `void SetFilterType(ESynthFilterType FilterType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the filter type.
- L604 _public prototype_ `void SetFilterAlgorithm(ESynthFilterAlgorithm FilterAlgorithm);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the filter algorithm.
- L608 _public prototype_ `void SetStereoDelayIsEnabled(bool StereoDelayEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether not stereo delay is enabled.
- L612 _public prototype_ `void SetStereoDelayMode(ESynthStereoDelayMode StereoDelayMode);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether not stereo delay is enabled.
- L616 _public prototype_ `void SetStereoDelayTime(float DelayTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the amount of stereo delay time in msec.
- L620 _public prototype_ `void SetStereoDelayFeedback(float DelayFeedback);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the amount of stereo delay feedback [0.0, 1.0]
- L624 _public prototype_ `void SetStereoDelayWetlevel(float DelayWetlevel);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the amount of stereo delay wetlevel [0.0, 1.0]
- L628 _public prototype_ `void SetStereoDelayRatio(float DelayRatio);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the amount of stereo delay ratio between left and right delay lines [0.0, 1.0]
- L632 _public prototype_ `void SetChorusEnabled(bool EnableChorus);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets whether or not chorus is enabled.
- L636 _public prototype_ `void SetChorusDepth(float Depth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the chorus depth
- L640 _public prototype_ `void SetChorusFeedback(float Feedback);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the chorus feedback
- L644 _public prototype_ `void SetChorusFrequency(float Frequency);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the chorus frequency
- L648 _public prototype_ `void SetSynthPreset(const FModularSynthPreset& SynthPreset);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the preset struct for the synth
- L652 _public prototype_ `FPatchId CreatePatch(const ESynth1PatchSource PatchSource, const TArray<FSynth1PatchCable>& PatchCables, const bool bEnableByDefault);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Creates a new modular synth patch between a modulation source and a set of modulation destinations
- L655 _public prototype_ `bool SetEnablePatch(const FPatchId PatchId, const bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L658 _protected member_ `Audio::FEpicSynth1 EpicSynth1;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SynthComponents/SynthComponentGranulator.h` (Public)


#### enum `EGranularSynthEnvelopeType`  
`enum class EGranularSynthEnvelopeType : uint8`  
_L14-31_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Rectangular`
- L17 _public enumerator_ `Triangle`
- L18 _public enumerator_ `DownwardTriangle`
- L19 _public enumerator_ `UpwardTriangle`
- L20 _public enumerator_ `ExponentialDecay`
- L21 _public enumerator_ `ExponentialIncrease`
- L22 _public enumerator_ `Gaussian`
- L23 _public enumerator_ `Hanning`
- L24 _public enumerator_ `Lanczos`
- L25 _public enumerator_ `Cosine`
- L26 _public enumerator_ `CosineSquared`
- L27 _public enumerator_ `Welch`
- L28 _public enumerator_ `Blackman`
- L29 _public enumerator_ `BlackmanHarris`
- L30 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EGranularSynthSeekType`  
`enum class EGranularSynthSeekType : uint8`  
_L34-39_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `FromBeginning`
- L37 _public enumerator_ `FromCurrentPosition`
- L38 _public enumerator_ `Count UMETA(Hidden)`

#### class `UGranularSynth`  
`class UGranularSynth : public USynthComponent`  
_L43-137_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent`
- L47 _private prototype_ `UGranularSynth(const FObjectInitializer& ObjInitializer);`
- L48 _private prototype_ `~UGranularSynth();`
- L51 _private prototype_ `virtual bool Init(int32& SampleRate) override;` — Initialize the synth component
- L54 _private prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;` — Called to generate more audio
- L57 _private prototype_ `virtual void OnRegister() override;`
- L58 _private prototype_ `virtual void OnUnregister() override;`
- L59 _private prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L66 _public prototype_ `void SetSoundWave(USoundWave* InSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — This will override the current sound wave if one is set, stop audio, and reload the new sound wave
- L69 _public prototype_ `void SetAttackTime(const float AttackTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L72 _public prototype_ `void SetDecayTime(const float DecayTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L75 _public prototype_ `void SetSustainGain(const float SustainGain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L78 _public prototype_ `void SetReleaseTimeMsec(const float ReleaseTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L81 _public prototype_ `void NoteOn(const float Note, const int32 Velocity, const float Duration = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L84 _public prototype_ `void NoteOff(const float Note, const bool bKill = false);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L87 _public prototype_ `void SetGrainsPerSecond(const float InGrainsPerSecond);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L90 _public prototype_ `void SetGrainProbability(const float InGrainProbability);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L93 _public prototype_ `void SetGrainEnvelopeType(const EGranularSynthEnvelopeType EnvelopeType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L96 _public prototype_ `void SetPlaybackSpeed(const float InPlayheadRate);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L99 _public prototype_ `void SetGrainPitch(const float BasePitch, const FVector2D PitchRange = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L102 _public prototype_ `void SetGrainVolume(const float BaseVolume, const FVector2D VolumeRange = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L105 _public prototype_ `void SetGrainPan(const float BasePan, const FVector2D PanRange = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L108 _public prototype_ `void SetGrainDuration(const float BaseDurationMsec, const FVector2D DurationRange = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L111 _public prototype_ `float GetSampleDuration() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L114 _public prototype_ `void SetScrubMode(const bool bScrubMode);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L117 _public prototype_ `void SetPlayheadTime(const float InPositionSec, const float LerpTimeSec = 0.0f, EGranularSynthSeekType SeekType = EGranularSynthSeekType::FromBeginning);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L120 _public prototype_ `float GetCurrentPlayheadTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L123 _public prototype_ `bool IsLoaded() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L128 _protected member_ `TObjectPtr<USoundWave> GranulatedSoundWave;` — `UPROPERTY(Transient)`
- L130 _protected member_ `Audio::FGranularSynth GranularSynth;`
- L131 _protected member_ `Audio::FSoundWavePCMLoader SoundWaveLoader;`
- L133 _protected member_ `bool bIsLoaded;`
- L134 _protected member_ `bool bRegistered;`
- L136 _protected member_ `bool bIsLoading;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SynthComponents/SynthComponentMonoWaveTable.h` (Public)


#### struct `AssetChangeInfo`  
`struct AssetChangeInfo`  
_L19-37_
- desc: struct passed from Mono WaveTable Asset to USynthObject
- L21 _public member_ `uint8 bNeedsFullRebuild : 1;`
- L22 _public member_ `int32 CurveThatWasAltered{ -1 };`
- L24 _public function_ `void FlagCurveAsAltered(const int32 CurveIndex)`
- L36 _public function_ `AssetChangeInfo() : bNeedsFullRebuild(false)`

#### class `UMonoWaveTableSynthPreset`  
`class UMonoWaveTableSynthPreset : public UObject`  
_L41-121_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `UObject`
- desc: UStruct Mono Wave Table Synth Preset
- L48 _public prototype_ `UMonoWaveTableSynthPreset();` — ctor
- L52 _public member_ `FString PresetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Name the preset
- L56 _public member_ `uint8 bLockKeyframesToGridBool : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Synth|Preset", Meta = (InlineEditConditionToggle))` — Lock wavetables to evenly spaced keyframes that can be edited vertically only (will re-sample)
- L60 _public member_ `int32 LockKeyframesToGrid;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Synth|Preset", Meta = (EditCondition = "bLockKeyframesToGridBool", ClampMin = "3", UIMin = "3", ClampMax = "256", UIMax = "256"))` — How many evenly-spaced keyframes to use when LockKeyframesToGrid is true
- L64 _public member_ `int32 WaveTableResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Synth|Preset", Meta = (ClampMin = "3", UIMin = "3", ClampMax = "4096", UIMax = "4096"))` — How many samples will be taken of the curve from time = [0.0, 1.0]
- L68 _public member_ `TArray<FRuntimeFloatCurve> WaveTable;` — `UPROPERTY(EditAnywhere, NonTransactional, BlueprintReadOnly, Category = "Synth|Preset")` — Wave Table Editor
- L72 _public member_ `uint8 bNormalizeWaveTables : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — Normalize the WaveTable data? False will allow clipping, True will normalize the tables when sent to the synth for rendering
- L75 _public prototype_ `void RegisterWTComponentCallback(uint32 ID, TFunction<void(const AssetChangeInfo& ChangeInfo)> Callback);` — function to register lambdas to call when a property is changed
- L78 _public prototype_ `void UnRegisterWTSynthComponentCallback(const uint32 ID);` — function to UNregister same lambdas
- L83 _protected prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent&) override;` — Override on Post property change thing here (loop and call lambdas)
- L86 _protected prototype_ `void EditChangeInternal();`
- L88 _protected prototype_ `void SampleAllToGrid(uint32 InGridsize);`
- L90 _protected prototype_ `void SampleToGrid(uint32 InGridSize, uint32 InTableIndex);`
- L94 _protected prototype_ `void DuplicateCurveToEnd();` — Since wavetable synthesis sounds good when there are subtle changes between curves, this helps work flow when adding a new curve by making it a duplicate of a the curve before it
- L97 _protected prototype_ `void CacheAssetData();` — saves data from the asset to see what changed when
- L100 _protected prototype_ `bool IsCachedTableEntryStillValid(Audio::DefaultWaveTableIndexType Index);` — Compares Underlying rich curves to see if the Index(th) curve was changed in the editor
- L103 _protected member_ `TMap<uint32, TFunction<void(const AssetChangeInfo&)>> PropertyChangedCallbacks;` — Map of registered TFunctions
- L105 _protected member_ `TArray<float> CurveBiDirTangents;`
- L108 _protected member_ `FRuntimeFloatCurve DefaultCurve;` — Default curve to use for work flow QOL (Never expose empty/silent curve)
- L110 _protected member_ `int32 CachedGridSize;`
- L113 _protected member_ `int8 bWasLockedToGrid : 1;` — cached asset data (before last edit)
- L114 _protected member_ `int32 CachedTableResolution;`
- L115 _protected member_ `TArray<FRuntimeFloatCurve> CachedWaveTable;`
- L116 _protected member_ `uint8 bCachedNormalizationSetting : 1;`

#### enum `CurveInterpolationType`  
`enum class CurveInterpolationType : uint8`  
_L127-132_
- reflection: `UENUM(BlueprintType)`
- L129 _public enumerator_ `AUTOINTERP UMETA(DisplayName = "Auto")`
- L130 _public enumerator_ `LINEAR UMETA(DisplayName = "Linear")`
- L131 _public enumerator_ `CONSTANT UMETA(DisplayName = "Constant")`

#### class `USynthComponentMonoWaveTable`  
`class USynthComponentMonoWaveTable : public USynthComponent`  
_L136-395_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent`
- L140 _private prototype_ `USynthComponentMonoWaveTable(const FObjectInitializer& ObjectInitializer);`
- L143 _private function_ `~USynthComponentMonoWaveTable()` — if in editor, unregister with the asset
- L152 _private prototype_ `virtual bool Init(int32& InSampleRate) override;` — Called when synth is created
- L155 _private prototype_ `virtual Audio::DefaultWaveTableIndexType OnGenerateAudio(float* OutAudio, int32 NumSamples) override;` — Called to generate more audio
- L162 _public prototype_ `int32 GetNumTableEntries();` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Get the number of table elements from Blueprint
- L166 _public prototype_ `void NoteOn(const float InMidiNote, const float InVelocity);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Starts a new note (retrigs modulators, etc.)
- L170 _public prototype_ `void NoteOff(const float InMidiNote);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Starts a new note (retrigs modulators, etc.)
- L174 _public prototype_ `void SetSustainPedalState(bool InSustainPedalState);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Inform the synth if the sustain pedal is pressed or not
- L178 _public prototype_ `void SetFrequency(const float FrequencyHz);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Sets the oscillator's frequency
- L182 _public prototype_ `void SetFrequencyPitchBend(const float FrequencyOffsetCents);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set a frequency offset in cents (for pitch modulation such as the Pitch Bend Wheel)
- L186 _public prototype_ `void SetFrequencyWithMidiNote(const float InMidiNote);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the oscillator's frequency via midi note number
- L190 _public prototype_ `void SetWaveTablePosition(float InPosition);` — `UFUNCTION(BLueprintCallable, Category = "Synth|Components|Audio", Meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Sets the wavetable position. Expects a percentage between 0.0 and 1.0
- L194 _public prototype_ `void RefreshWaveTable(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Refresh a particular wavetable (from Game Thread data)
- L198 _public prototype_ `void RefreshAllWaveTables();` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Refresh all wavetables (from Game Thread data)
- L202 _public prototype_ `void SetSynthPreset(UMonoWaveTableSynthPreset* SynthPreset);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Switch to another preset (STOPS SYNTH FROM PLAYING)
- L206 _public prototype_ `void SetPosLfoFrequency(const float InLfoFrequency);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set frequency of LFO controlling Table Position (in Hz)
- L211 _public prototype_ `void SetPosLfoDepth(const float InLfoDepth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the Modulation depth of the Lfo controlling the Table Position around the current position value 0.0 = no modulation, 1.0 = current position +/- 0.5 (Lfo + Position result will clamp [0.0, 1.0])
- L215 _public prototype_ `void SetPosLfoType(const ESynthLFOType InLfoType);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the shape of the Lfo controlling the position
- L217 _public prototype_ `virtual void SetLowPassFilterFrequency(float InLowPassFilterFrequency) override;`
- L221 _public prototype_ `void SetLowPassFilterResonance(float InNewQ);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio", Meta = (ClampMin = "0.0", ClampMax = "10.0"))` — Set the Cut-off frequency of the low-pass filter
- L225 _public prototype_ `void SetAmpEnvelopeAttackTime(const float InAttackTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Amp envelope attack time (msec)
- L229 _public prototype_ `void SetAmpEnvelopeDecayTime(const float InDecayTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Amp envelope decay time (msec)
- L233 _public prototype_ `void SetAmpEnvelopeSustainGain(const float InSustainGain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Amp envelope sustain gain [0.0, 1.0]
- L237 _public prototype_ `void SetAmpEnvelopeReleaseTime(const float InReleaseTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Amp envelope release time (msec)
- L241 _public prototype_ `void SetAmpEnvelopeInvert(const bool bInInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set whether or not the Amp envelope is inverted
- L245 _public prototype_ `void SetAmpEnvelopeBiasInvert(const bool bInBiasInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set whether or not the Amp envelope's bias is inverted
- L249 _public prototype_ `void SetAmpEnvelopeDepth(const float InDepth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the overall depth of the Amp envelope
- L253 _public prototype_ `void SetAmpEnvelopeBiasDepth(const float InDepth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the bias depth of the the Amp envelope
- L257 _public prototype_ `void SetFilterEnvelopeAttackTime(const float InAttackTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope attack time (msec)
- L261 _public prototype_ `void SetFilterEnvelopenDecayTime(const float InDecayTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope decay time (msec)
- L265 _public prototype_ `void SetFilterEnvelopeSustainGain(const float InSustainGain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope sustain gain
- L269 _public prototype_ `void SetFilterEnvelopeReleaseTime(const float InReleaseTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope release time (msec)
- L273 _public prototype_ `void SetFilterEnvelopeInvert(const bool bInInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope inversion
- L277 _public prototype_ `void SetFilterEnvelopeBiasInvert(const bool bInBiasInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope bias inversion
- L281 _public prototype_ `void SetFilterEnvelopeDepth(const float InDepth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope depth
- L285 _public prototype_ `void SetFilterEnvelopeBiasDepth(const float InDepth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Low-Pass Filter envelope bias depth
- L289 _public prototype_ `void SetPositionEnvelopeAttackTime(const float InAttackTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope attack time (msec)
- L293 _public prototype_ `void SetPositionEnvelopeDecayTime(const float InDecayTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope decay time (msec)
- L297 _public prototype_ `void SetPositionEnvelopeSustainGain(const float InSustainGain);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope sustain gain
- L301 _public prototype_ `void SetPositionEnvelopeReleaseTime(const float InReleaseTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope release time (msec)
- L305 _public prototype_ `void SetPositionEnvelopeInvert(const bool bInInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope envelope inversion
- L309 _public prototype_ `void SetPositionEnvelopeBiasInvert(const bool bInBiasInvert);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope bias inversion
- L313 _public prototype_ `void SetPositionEnvelopeDepth(const float InDepth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope envelope depth
- L317 _public prototype_ `void SetPositionEnvelopeBiasDepth(const float InDepth);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set Position envelope bias depth
- L321 _public function_ `int32 GetMaxTableIndex() const` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Get the number of curves in the wave table. (returns -1 if there is no asset)
- L327 _public prototype_ `bool SetCurveValue(int32 TableIndex, int32 KeyframeIndex, const float NewValue);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set a Keyframe value given a Table number and Keyframe number. Returns false if the request was invalid. NewValue will be clamped from +/- 1.0
- L334 _public prototype_ `bool SetCurveInterpolationType(CurveInterpolationType InterpolationType, int32 TableIndex);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the curve interpolation type (What the curve is doing between keyframes) This should only be used for live-editing features! (changing the curves at runtime is expensive)
- L341 _public prototype_ `bool SetCurveTangent(int32 TableIndex, float InNewTangent);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Set the curve tangent ("Curve depth" between keyframes) This should only be used for live-editing features! (changing the curves at runtime is expensive)
- L354 _public prototype_ `float GetCurveTangent(int32 TableIndex);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Get the curve interpolation type (What the curve is doing between keyframes)
- L358 _public prototype_ `TArray<float> GetKeyFrameValuesForTable(float TableIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — Get an array of floats that represent the key frames in the requested curve
- L362 _public member_ `FOnTableAltered OnTableAltered;` — `UPROPERTY(BlueprintAssignable, Category = "Synth|Preset")` — Wave Table curve was edited
- L366 _public member_ `FNumTablesChanged OnNumTablesChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Synth|Preset")` — Curve array altered
- L371 _protected prototype_ `void ResetCurve(int32 Index);` — Helper function that resets a curve to a default saw-tooth (so a curve is always immediately audible without user effort)
- L375 _protected prototype_ `void InitSynth();` — Initializes the underlying synthesizer. Called when underlying wave table containers in the Synth FObject need resizing.
- L379 _protected prototype_ `void ReactToAssetChange(const AssetChangeInfo& ChangeInfo);` — Callback for the UAsset this synth component is subscribed to Compares cached data to current UAsset data and makes updates
- L383 _protected prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& Eevnt) override;` — Override on Post property change thing here (see if we got a new preset)
- L388 _protected member_ `TObjectPtr<UMonoWaveTableSynthPreset> CurrentPreset;` — `UPROPERTY(EditAnywhere, Category = "Synth|Components|Audio")` — The settings asset to use for this synth
- L390 _protected member_ `UMonoWaveTableSynthPreset* CachedPreset;`
- L393 _protected member_ `Audio::FMonoWaveTable Synth;` — underlying wavetable synth
- L394 _protected member_ `Audio::DefaultWaveTableIndexType SampleRate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SYNTHESIS_API`
- L123 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTableAltered, int32, TableIndex);`
- L123 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTableAltered, int32, TableIndex);`
- L124 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNumTablesChanged);`
- L124 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNumTablesChanged);`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SynthComponents/SynthComponentToneGenerator.h` (Public)


#### class `FToneGenerator`  
`class FToneGenerator : public ISoundGenerator`  
_L15-38_
- inherits: `ISoundGenerator`
- L18 _public prototype_ `FToneGenerator(int32 InSampleRate, int32 InNumChannels, int32 InFrequency, float InVolume, const Audio::FAudioBufferDistanceAttenuationSettings& InAttenuationSettings);`
- L19 _public prototype_ `virtual ~FToneGenerator() = default;`
- L22 _public function_ `virtual int32 GetNumChannels() const override`
- L23 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;`
- L26 _public prototype_ `void SetFrequency(float InFrequency);`
- L27 _public prototype_ `void SetVolume(float InVolume);`
- L28 _public prototype_ `void SetDistance(float InDistance);`
- L31 _private member_ `int32 NumChannels = 2;`
- L32 _private member_ `Audio::FSineOsc SineOsc;`
- L33 _private member_ `Audio::FAlignedFloatBuffer Buffer;`
- L35 _private member_ `float CurrentDistance = 0.0f;`
- L36 _private member_ `float CurrentAttenuation = 1.0f;`
- L37 _private member_ `Audio::FAudioBufferDistanceAttenuationSettings DistanceAttenuationSettings;`

#### class `USynthComponentToneGenerator`  
`class USynthComponentToneGenerator : public USynthComponent`  
_L41-87_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent`
- L45 _private prototype_ `USynthComponentToneGenerator(const FObjectInitializer& ObjInitializer);`
- L46 _private prototype_ `virtual ~USynthComponentToneGenerator();`
- L51 _public member_ `float Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tone Generator", meta = (ClampMin = "10.0", ClampMax = "20000.0"))` — The frequency (in hz) of the tone generator.
- L55 _public member_ `float Volume;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tone Generator", meta = (ClampMin = "0.0", ClampMax = "1.0"))` — The linear volume of the tone generator.
- L59 _public member_ `FRuntimeFloatCurve DistanceAttenuationCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation)` — A distance attenuation curve to use to attenuate the audio.
- L63 _public member_ `FVector2D DistanceRange = { 400.0f, 4000.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation)` — A distance range over which to apply distance attenuation using the supplied curve.
- L67 _public member_ `float AttenuationDbAtMaxRange = -60.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation)` — An attenuation, in decibels, to apply to the sound at max range.
- L71 _public prototype_ `void SetFrequency(float InFrequency);` — `UFUNCTION(BlueprintCallable, Category = "Tone Generator")` — Sets the frequency of the tone generator
- L75 _public prototype_ `void SetVolume(float InVolume);` — `UFUNCTION(BlueprintCallable, Category = "Tone Generator")` — Sets the volume of the tone generator
- L78 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — Tick this component to get the current position of the component to pass to the attenuator
- L80 _public prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L85 _private member_ `Audio::FAudioBufferDistanceAttenuationSettings DistanceAttenuationSettings;`
- L86 _private member_ `ISoundGeneratorPtr ToneGenerator;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Classes/SynthComponents/SynthComponentWaveTable.h` (Public)


#### enum `ESamplePlayerSeekType`  
`enum class ESamplePlayerSeekType : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `FromBeginning`
- L16 _public enumerator_ `FromCurrentPosition`
- L17 _public enumerator_ `FromEnd`
- L18 _public enumerator_ `Count UMETA(Hidden)`

#### class `USynthSamplePlayer`  
`class USynthSamplePlayer : public USynthComponent`  
_L30-99_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent`
- L34 _private prototype_ `USynthSamplePlayer(const FObjectInitializer& ObjInitializer);`
- L35 _private prototype_ `~USynthSamplePlayer();`
- L38 _private prototype_ `virtual bool Init(int32& SampleRate) override;` — Initialize the synth component
- L41 _private prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;` — Called to generate more audio
- L44 _private prototype_ `virtual void OnRegister() override;`
- L45 _private prototype_ `virtual void OnUnregister() override;`
- L46 _private prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L52 _public member_ `TObjectPtr<USoundWave> SoundWave;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")`
- L55 _public member_ `FOnSampleLoaded OnSampleLoaded;` — `UPROPERTY(BlueprintAssignable, Category = "Synth|Components|Audio")`
- L58 _public member_ `FOnSamplePlaybackProgress OnSamplePlaybackProgress;` — `UPROPERTY(BlueprintAssignable, Category = "Synth|Components|Audio")`
- L62 _public prototype_ `void SetSoundWave(USoundWave* InSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")` — This will override the current sound wave if one is set, stop audio, and reload the new sound wave
- L65 _public prototype_ `void SetPitch(float InPitch, float TimeSec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L68 _public prototype_ `void SeekToTime(float TimeSec, ESamplePlayerSeekType SeekType, bool bWrap = true);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L71 _public prototype_ `void SetScrubMode(bool bScrubMode);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L74 _public prototype_ `void SetScrubTimeWidth(float InScrubTimeWidthSec);` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L77 _public prototype_ `float GetSampleDuration() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L80 _public prototype_ `float GetCurrentPlaybackProgressTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L83 _public prototype_ `float GetCurrentPlaybackProgressPercent() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L86 _public prototype_ `bool IsLoaded() const;` — `UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")`
- L89 _protected prototype_ `void LoadSoundWaveInternal();`
- L91 _protected member_ `Audio::FSampleBufferReader SampleBufferReader;`
- L92 _protected member_ `Audio::TSampleBuffer<int16> SampleBuffer;`
- L93 _protected member_ `Audio::FSoundWavePCMLoader SoundWaveLoader;`
- L95 _protected member_ `float SampleDurationSec;`
- L96 _protected member_ `float SamplePlaybackProgressSec;`
- L98 _protected member_ `bool bIsLoaded;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SYNTHESIS_API`
- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSampleLoaded);` — Called when a sample has finished loading into the sample player
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSampleLoaded);` — Called when a sample has finished loading into the sample player
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSamplePlaybackProgress, float, ProgressPercent, float, ProgressTimeSeconds);` — Called while a sample player is playing back. Indicates the playhead progress in percent and as absolute time value (within the file).
- L26 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSamplePlaybackProgress, float, ProgressPercent, float, ProgressTimeSeconds);` — Called while a sample player is playing back. Indicates the playhead progress in percent and as absolute time value (within the file).

### `Plugins/Runtime/Synthesis/Source/Synthesis/Private/SubmixChannelFormatConverter.h` (Private)


#### struct `Audio::FAC3DownmixerFactory`  
`struct FAC3DownmixerFactory`  
_L20-46_
- desc: Factory for creating downmixers based on the AC3 downmixing gain values.
- L22 _public typedef_ `using FChannelMixEntry = FBaseChannelFormatConverter::FChannelMixEntry;`
- L23 _public typedef_ `using FInputFormat = IChannelFormatConverter::FInputFormat;`
- L24 _public typedef_ `using FOutputFormat = IChannelFormatConverter::FOutputFormat;`
- L34 _public prototype_ `static bool GetAC3DownmixEntries(const FInputFormat& InInputFormat, const FOutputFormat& InOutputFormat, TArray<FChannelMixEntry>& OutMixEntries);` — Populate an array of mix entries to go from an input format to an output format using AC3 conforming gains. @param InInputFormat - The format of the input audio. @param InOutputFormat - The desired output audio format. @param OutMixEntries - An array of channel mix entries. @return True on success, false on failure.
- L45 _public prototype_ `static TUniquePtr<FBaseChannelFormatConverter> CreateAC3Downmixer(const FInputFormat& InInputFormat, const FOutputFormat& InOutputFormat, int32 InNumFramesPerCall);` — Creates an FBaseChannelFormatConverter using AC3 downmixing weights to convert the InInputFormat to the InOutputFormat. @param InInputFormat - The format of the input audio. @param InOutputFormat - The desired output audio format. @param InNumFramesPerCall - The number of frames used for each call to ProcessAudio. @return A TUniquePtr to a FBaseChannelFormatConverter.

#### class `Audio::FSimpleRouter`  
`class FSimpleRouter : public IChannelFormatConverter`  
_L48-102_
- inherits: `IChannelFormatConverter`
- L52 _public typedef_ `using FInputFormat = IChannelFormatConverter::FInputFormat;`
- L53 _public typedef_ `using FOutputFormat = IChannelFormatConverter::FOutputFormat;`
- L55 _public prototype_ `virtual ~FSimpleRouter() = default;`
- L58 _public prototype_ `const FInputFormat& GetInputFormat() const override;` — Return the input format handled by this converter.
- L61 _public prototype_ `const FOutputFormat& GetOutputFormat() const override;` — Return the output format handled by this converter.
- L72 _public prototype_ `void ProcessAudio(const TArray<FAlignedFloatBuffer>& InInputBuffers, TArray<FAlignedFloatBuffer>& OutOutputBuffers) override;` — Converter the audio format from the FInputFormat to the FOutputFormat. The input buffer array must have the same number of channels as the FInputFormat return from GetInputFormat().  Each buffer within that array must have the same number of samples. @param InInputBuffers - An array of input audio buffers. @param OutOutputBuffers - An array of buffers where output audio is stored.
- L85 _public prototype_ `static TUniquePtr<FSimpleRouter> CreateSimpleRouter(const TArray<EAudioMixerChannel::Type>& InInputChannelTypes, const TArray<EAudioMixerChannel::Type>& InOutputChannelTypes, int32 InNumFramesPerCall);` — Create a simple router. The simple router copies input data to output data if the channel types match for the input and output channel types. @param InInputChannelTypes - Array denoting input channel type order. @param InOutputChannelTypes - Array denoting input channel type order. @param InNumFramesPerCall - Number of frames used for each call to ProcessAudio. @return A valid TUniquePtr<FSimpleRouter> on success. An invalid pointer on failure.
- L89 _protected prototype_ `FSimpleRouter(const TArray<EAudioMixerChannel::Type>& InInputChannelTypes, const TArray<EAudioMixerChannel::Type>& InOutputChannelTypes, int32 InNumFramesPerCall);`
- L93 _private member_ `FInputFormat InputFormat;`
- L94 _private member_ `FOutputFormat OutputFormat;`
- L96 _private member_ `TArray<EAudioMixerChannel::Type> InputChannelTypes;`
- L97 _private member_ `TArray<EAudioMixerChannel::Type> OutputChannelTypes;`
- L99 _private member_ `int32 NumFramesPerCall;`
- L101 _private member_ `TArray<TPair<int32, int32>> ChannelPairs;`

#### class `Audio::FSimpleUpmixer`  
`class FSimpleUpmixer : public FBaseChannelFormatConverter`  
_L111-183_
- inherits: `FBaseChannelFormatConverter`
- desc: FSimpleUpmixer handles a handful of upmixing scenarios.  Mono to Stereo, Mono to Surround and Stereo to Surround. When upmixing from stereo to surround, front left and front right audio is mixed to the rear left and rear right audio in accordance with the set RearChannelBleep and RearChannelFlip.
- L115 _public prototype_ `virtual ~FSimpleUpmixer() = default;`
- L124 _public prototype_ `void SetRearChannelBleed(float InGain, bool bFadeToGain=true);` — Sets amount of mixing from front channels to paired rear channels. @param InGain - Scalar gain to apply front channels when adding them to rear channels. @param bFadeToGain - If true, gain values are linearly faded over the duration of a single buffer. If false, gain values are applied immediately.
- L134 _public prototype_ `void SetRearChannelFlip(bool bInDoRearChannelFlip, bool bFadeFlip=true);` — Set whether left and right rear channels should be swapped. @param bInDoRearChannelFlip - If true, front left is paired with rear right and vice-a-versa. If false, front left is paired with rear left and vice-a-versa. @param bFadeToGain - If true, gain values are linearly faded over the duration of a single buffer. If false, gain values are applied immediately.
- L137 _public prototype_ `bool GetRearChannelFlip() const;` — Returns whether the rear channel is flipped.
- L149 _public prototype_ `static bool GetSimpleUpmixerStaticMixEntries(const TArray<EAudioMixerChannel::Type>& InInputChannelTypes, const TArray<EAudioMixerChannel::Type>& InOutputChannelTypes, TArray<FChannelMixEntry>& OutEntries);` — Gets the unchanging mix entries for the simple upmixer. These mix entries are generally unchanged during the lifetime of a simple upmixer. @param InInputChannelTypes - An array of channels describing the input channel order. @param InOutputChannelTypes - An array of channels describing the output channel order. @param OutEntries - An array of channel mix entries. @return True on success, false on failure.
- L158 _public prototype_ `static TUniquePtr<FSimpleUpmixer> CreateSimpleUpmixer(const TArray<EAudioMixerChannel::Type>& InInputChannelTypes, const TArray<EAudioMixerChannel::Type>& InOutputChannelTypes, int32 InNumFramesPerCall);` — Creates an FSimpleUpmixer. @param InInputChannelTypes - An array of channels describing the input channel order. @param InOutputChannelTypes - An array of channels describing the output channel order. @param InNumFramesPerCall - The number of frames used for each call to ProcessAudio.
- L162 _protected prototype_ `FSimpleUpmixer(const TArray<EAudioMixerChannel::Type>& InInputChannelTypes, const TArray<EAudioMixerChannel::Type>& InOutputChannelTypes, TArrayView<const FChannelMixEntry> InMixEntries, int32 InNumFramesPerCall);`
- L166 _private prototype_ `void UpdateOutputGain(bool bFadeToGain);`
- L168 _private prototype_ `void InitFrontChannelIndices(TArray<int32>& OutFrontChannelIndices) const;`
- L171 _private prototype_ `void InitPairedRearChannelIndices(int32 InInputChannelIndex, bool bInFlipped, TArray<int32>& OutRearChannelIndices) const;` — Returns the channels associated with a rear channel indices.
- L173 _private prototype_ `const TArray<int32>& GetPairedRearChannelIndices(int32 InInputChannelIndex) const;`
- L175 _private member_ `TArray<EAudioMixerChannel::Type> InputChannelTypes;`
- L176 _private member_ `TArray<EAudioMixerChannel::Type> OutputChannelTypes;`
- L178 _private member_ `TArray<int32> FrontChannelIndices;`
- L179 _private member_ `TSortedMap<int32, TArray<int32>> PairedRearChannelIndices;`
- L180 _private member_ `TSortedMap<int32, TArray<int32>> PairedFlippedRearChannelIndices;`
- L182 _private member_ `bool bDoRearChannelFlip = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L17 _prototype_ `bool GetSubmixChannelOrderForNumChannels(int32 InNumChannels, TArray<EAudioMixerChannel::Type>& OutChannelOrder);` (scope `Audio`) — Returns the defualt channeel order for a given number of submix channels. @param InNumChannels - The number of channels in the submix. @param OutChannelOrder - An array of channel types denoting the channel order. @return True on success, false on error.

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/ConvolutionReverb.h` (Public)


#### struct `Audio::FConvolutionReverbGainEntry`  
`struct FConvolutionReverbGainEntry`  
_L19-36_
- desc: Gain entry into convolution matrix.
- L21 _public member_ `int32 InputIndex = 0;`
- L23 _public member_ `int32 ImpulseIndex = 0;`
- L25 _public member_ `int32 OutputIndex = 0;`
- L27 _public member_ `float Gain = 0.f;`
- L29 _public function_ `FConvolutionReverbGainEntry(int32 InInputIndex, int32 InImpulseIndex, int32 InOutputIndex, float InGain) : InputIndex(InInputIndex) , ImpulseIndex(InImpulseIndex) , OutputIndex(InOutputIndex) , Gain(InGain)`

#### struct `Audio::FConvolutionReverbSettings`  
`struct FConvolutionReverbSettings`  
_L39-53_
- desc: Runtime settings for convolution reverb.
- L41 _public prototype_ `FConvolutionReverbSettings();`
- L44 _public member_ `float NormalizationVolume = -24.f;` — Used to account for energy added by convolution with "loud" Impulse Responses.  Not meant to be updated dynamically (linear gain)
- L47 _public member_ `float RearChannelBleed = 0.f;` — Amount of audio to be sent to rear channels in quad/surround configurations (linear gain, < 0 = phase inverted)
- L50 _public member_ `bool bRearChannelFlip = false;` — If true, send Surround Rear Channel Bleed Amount sends front left to back right and vice versa
- L52 _public member_ `static const FConvolutionReverbSettings DefaultSettings;`

#### struct `Audio::FConvolutionReverbInitData`  
`struct FConvolutionReverbInitData`  
_L56-99_
- desc: Data used to initialize the convolution algorithm
- L58 _public typedef_ `using FInputFormat = IChannelFormatConverter::FInputFormat;`
- L59 _public typedef_ `using FOutputFormat = IChannelFormatConverter::FOutputFormat;`
- L62 _public member_ `FInputFormat InputAudioFormat;` — Input audio format.
- L65 _public member_ `FOutputFormat OutputAudioFormat;` — Output audio format.
- L68 _public member_ `Audio::FConvolutionSettings AlgorithmSettings;` — Algorithm configuration.
- L71 _public member_ `float ImpulseSampleRate = 0.f;` — Sample rate of the impulse response samples.
- L74 _public member_ `float TargetSampleRate = 0.f;` — Target sample rate of audio to be processed.
- L77 _public member_ `TArray<float> Samples;` — Impulse response samples in interleaved format.
- L80 _public member_ `float NormalizationVolume;` — Normalization gain to apply to reverb output.
- L85 _public member_ `bool bMixInputChannelFormatToImpulseResponseFormat = true;` — If true, input audio is mixed to match the channel format of the impulse response. If false, input audio is matched to equivalent audio channels of the impulse response.
- L90 _public member_ `bool bMixReverbOutputToOutputChannelFormat = true;` — If true, the reverberated audio is mixed to match the output audio format. If false, the reverberated audio is matched to the equivalent audio channels of the output audio format.
- L95 _public member_ `bool bIsImpulseTrueStereo = false;` — If true, impulse response channels are interpreted as true stereo. If false, impulse response channels are interpreted as individual channel filters.
- L98 _public member_ `TArray<FConvolutionReverbGainEntry> GainMatrix;` — Array of gain values for convolution algorithm.

#### class `Audio::FConvolutionReverb`  
`class FConvolutionReverb`  
_L142-265_
- desc: FConvolutionReverb applies an impulse response to audio. The audio pipeline within an FConvolutionReverb is described in ascii art here. +-----------+ |Input Audio| +-----------+ | v +------------+ |Deinterleave| +------------+ | v +----------------------------+ |Mix Input Audio to IR Format| +----------------------------+ | v +-----------------+ |Convolve with IRs| +-----------------+ | v +---------------------------------+ |Mix Reverb Audio to Output Format| +---------------------------------+ | v +----------+ |Interleave| +----------+ | v +------------+ |Output Audio| +------------+
- L144 _private prototype_ `FConvolutionReverb() = delete;`
- L145 _private prototype_ `FConvolutionReverb(const FConvolutionReverb&) = delete;`
- L146 _private prototype_ `FConvolutionReverb& operator=(const FConvolutionReverb&) = delete;`
- L147 _private prototype_ `FConvolutionReverb(const FConvolutionReverb&&) = delete;`
- L151 _public prototype_ `~FConvolutionReverb();`
- L161 _public prototype_ `static TUniquePtr<FConvolutionReverb> CreateConvolutionReverb(const FConvolutionReverbInitData& InInitData, const FConvolutionReverbSettings& InSettings=FConvolutionReverbSettings::DefaultSettings);` — Create a convolution reverb object. This performs creation of the convolution algorithm object, converting sample rates of impulse responses, sets the impulse response and initializes the gain matrix of the convolution algorithm, and initializes and upmix or downmix objects. @params InInitData - Contains all the information needed to create a convolution reverb. @params InSettings - The initial settings for the convolution reverb. @return TUniquePtr<Audio::IConvolutionAlgorithm>  Will be invalid if there was an error.
- L163 _public prototype_ `void SetSettings(const FConvolutionReverbSettings& InSettings);`
- L165 _public prototype_ `const FConvolutionReverbSettings& GetSettings() const;`
- L169 _public prototype_ `void ProcessAudio(int32 InNumInputChannels, const FAlignedFloatBuffer& InputAudio, int32 InNumOutputChannels, FAlignedFloatBuffer& OutputAudio);` — If the number of input frames changes between callbacks, the output may contain discontinuities.
- L170 _public prototype_ `void ProcessAudio(int32 InNumInputChannels, const float* InputAudio, int32 InNumOutputChannels, float* OutputAudio, const int32 InNumFrames);`
- L172 _public prototype_ `int32 GetNumInputChannels() const;`
- L173 _public prototype_ `int32 GetNumOutputChannels() const;`
- L175 _public prototype_ `static void InterleaveBuffer(FAlignedFloatBuffer& OutBuffer, const TArray<FAlignedFloatBuffer>& InputBuffers, const int32 NumChannels);`
- L176 _public prototype_ `static void DeinterleaveBuffer(TArray<FAlignedFloatBuffer>& OutputBuffers, TArrayView<const float> InputBuffer, const int32 NumChannels);`
- L180 _private typedef_ `using FInputFormat = IChannelFormatConverter::FInputFormat;`
- L181 _private typedef_ `using FOutputFormat = IChannelFormatConverter::FOutputFormat;`
- L222 _private prototype_ `FConvolutionReverb(TUniquePtr<IConvolutionAlgorithm> InAlgorithm, TUniquePtr<IChannelFormatConverter> InInputConverter, FChannelFormatConverterWrapper&& InOutputConverter, const FConvolutionReverbSettings& InSettings);`
- L224 _private prototype_ `void SetConvolutionAlgorithm(TUniquePtr<IConvolutionAlgorithm> InAlgorithm);`
- L226 _private prototype_ `void ProcessAudioBlock(const float* InputAudio, int32 InNumInputChannels, FAlignedFloatBuffer& OutputAudio, int32 InNumOutputChannels);`
- L228 _private prototype_ `void Update(bool bFadeToParams);`
- L230 _private prototype_ `void ResizeBlockBuffers();`
- L232 _private prototype_ `void ResizeProcessingBuffers();`
- L234 _private prototype_ `void ResizeArrayOfBuffers(TArray<FAlignedFloatBuffer>& InArrayOfBuffers, int32 MinNumBuffers, int32 NumFrames) const;`
- L236 _private member_ `FConvolutionReverbSettings Settings;`
- L238 _private member_ `TUniquePtr<IConvolutionAlgorithm> ConvolutionAlgorithm;`
- L239 _private member_ `TUniquePtr<IChannelFormatConverter> InputChannelFormatConverter;`
- L241 _private member_ `FChannelFormatConverterWrapper OutputChannelFormatConverter;`
- L244 _private member_ `TArray<FAlignedFloatBuffer> InputDeinterleaveBuffers;` — data is passed to the convolution algorithm as 2D arrays
- L245 _private member_ `TArray<FAlignedFloatBuffer> InputChannelConverterBuffers;`
- L248 _private member_ `TArray<FAlignedFloatBuffer> OutputDeinterleaveBuffers;` — data is recieved from the convolution algorithm as 2D arrays
- L249 _private member_ `TArray<FAlignedFloatBuffer> OutputChannelConverterBuffers;`
- L251 _private member_ `TArray<float*> InputBufferPtrs;`
- L252 _private member_ `TArray<float*> OutputBufferPtrs;`
- L254 _private member_ `TUniquePtr<FAlignedBlockBuffer> InputBlockBuffer;`
- L255 _private member_ `TUniquePtr<FAlignedBlockBuffer> OutputBlockBuffer;`
- L256 _private member_ `FAlignedFloatBuffer InterleavedOutputBlock;`
- L258 _private member_ `int32 ExpectedNumFramesPerCallback;`
- L259 _private member_ `int32 NumInputSamplesPerBlock;`
- L260 _private member_ `int32 NumOutputSamplesPerBlock;`
- L262 _private member_ `float OutputGain;`
- L263 _private member_ `bool bIsConvertingInputChannelFormat;`
- L264 _private member_ `bool bIsConvertingOutputChannelFormat;`

#### class `Audio::FConvolutionReverb::FChannelFormatConverterWrapper`  
`class FChannelFormatConverterWrapper`  
_L184-219_
- desc: Wraps the various channel converters to provide single interface
- L188 _public prototype_ `FChannelFormatConverterWrapper() = default;`
- L189 _public prototype_ `FChannelFormatConverterWrapper(TUniquePtr<FSimpleUpmixer> InConverter);`
- L190 _public prototype_ `FChannelFormatConverterWrapper(TUniquePtr<IChannelFormatConverter> InConverter);`
- L191 _public prototype_ `FChannelFormatConverterWrapper(FChannelFormatConverterWrapper&& InOther);`
- L192 _public prototype_ `FChannelFormatConverterWrapper& operator=(FChannelFormatConverterWrapper&& InOther);`
- L194 _public prototype_ `FChannelFormatConverterWrapper(const FChannelFormatConverterWrapper& InOther) = delete;`
- L195 _public prototype_ `FChannelFormatConverterWrapper& operator=(const FChannelFormatConverterWrapper& InOther) = delete;`
- L197 _public prototype_ `bool IsValid() const;`
- L199 _public prototype_ `const FInputFormat& GetInputFormat() const;`
- L201 _public prototype_ `const FOutputFormat& GetOutputFormat() const;`
- L203 _public prototype_ `void ProcessAudio(const TArray<FAlignedFloatBuffer>& InInputBuffers, TArray<FAlignedFloatBuffer>& OutOutputBuffers);`
- L205 _public prototype_ `void SetRearChannelBleed(float InGain, bool bFadeToGain=true);`
- L207 _public prototype_ `void SetRearChannelFlip(bool bInDoRearChannelFlip, bool bFadeFlip=true);`
- L209 _public prototype_ `bool GetRearChannelFlip() const;`
- L212 _private member_ `TUniquePtr<IChannelFormatConverter> Storage;`
- L214 _private member_ `IChannelFormatConverter* BaseConverter = nullptr;`
- L215 _private member_ `FSimpleUpmixer* SimpleUpmixer = nullptr;`
- L217 _private member_ `static FInputFormat DefaultInputFormat;`
- L218 _private member_ `static FOutputFormat DefaultOutputFormat;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SYNTHESIS_API`
- L11 _namespace_ `namespace Audio`
- L13 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/EffectConvolutionReverb.h` (Public)


#### enum `ESubmixEffectConvolutionReverbBlockSize`  
`enum class ESubmixEffectConvolutionReverbBlockSize : uint8`  
_L13-23_
- reflection: `UENUM()`
- desc: Block size of convolution reverb algorithm.
- L16 _public enumerator_ `BlockSize256` — 256 audio frames per a block.
- L19 _public enumerator_ `BlockSize512` — 512 audio frames per a block.
- L22 _public enumerator_ `BlockSize1024` — 1024 audio frames per a block.

#### class `UAudioImpulseResponse`  
`class UAudioImpulseResponse : public UObject`  
_L34-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L39 _public prototype_ `UAudioImpulseResponse();`
- L42 _public member_ `TArray<float> ImpulseResponse;` — `UPROPERTY()` — The interleaved audio samples used in convolution.
- L46 _public member_ `int32 NumChannels;` — `UPROPERTY()` — The number of channels in impulse response.
- L50 _public member_ `int32 SampleRate;` — `UPROPERTY()` — The original sample rate of the impulse response.
- L54 _public member_ `float NormalizationVolumeDb;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SubmixEffectPreset, meta = (DisplayName = "Normalization Volume (dB)", ClampMin = "-60.0", ClampMax = "15.0"))` — Used to account for energy added by convolution with "loud" Impulse Responses.
- L58 _public member_ `bool bTrueStereo;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SubmixEffectPreset, meta = (EditCondition = "(NumChannels > 0) && bIsEvenChannelCount"))` — If true, impulse response channels are interpreted as true stereo which allows channel crosstalk. If false, impulse response channels are interpreted as independent channel impulses.
- L61 _public member_ `TArray<float> IRData_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L63 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L66 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L69 _public member_ `FAudioImpulseResponsePropertyChange OnObjectPropertyChanged;` — This delegate is called whenever PostEditChangeProperty called.
- L73 _public member_ `bool bIsEvenChannelCount;` — `UPROPERTY()` — Used to evaluate whether TrueStereo should be editable

#### struct `AudioConvReverbIntrinsics::FVersionData`  
`struct FVersionData`  
_L83-97_
- L85 _public member_ `FConvolutionReverbID ConvolutionID;`
- L87 _public function_ `FVersionData()`
- L92 _public function_ `bool operator==(const FVersionData& Other) const`

#### class `Audio::FEffectConvolutionReverb`  
`class FEffectConvolutionReverb : public TSharedFromThis<FEffectConvolutionReverb, ESPMode::ThreadSafe>`  
_L102-154_
- inherits: `TSharedFromThis<FEffectConvolutionReverb,ESPMode::ThreadSafe>`
- L106 _public prototype_ `void ProcessAudio(int32 InNumInputChannels, const float* InputAudio, int32 InNumOutputChannels, float* OutputAudio, const int32 InNumFrames);`
- L108 _public prototype_ `FConvolutionReverbInitData CreateConvolutionReverbInitData();`
- L111 _public prototype_ `void BuildReverb();` — Fire off an async task to build a new reverb algorithm with new settings
- L114 _public prototype_ `void Init();` — Immediately build the initial reverb algorithm
- L116 _public prototype_ `void SetSettings(const FConvolutionReverbSettings& InSettings);`
- L117 _public prototype_ `void SetSampleRate(const float InSampleRate);`
- L118 _public prototype_ `void SetInitData(const FConvolutionReverbInitData& InData);`
- L119 _public prototype_ `void SetReverb(TUniquePtr<FConvolutionReverb> InReverb);`
- L120 _public prototype_ `void SetBypass(const bool InBypass);`
- L122 _public prototype_ `AudioConvReverbIntrinsics::FVersionData UpdateVersion();`
- L123 _public prototype_ `void UpdateChannelCount(const int32 InNumInputChannels, const int32 InNumOutputChannels);`
- L124 _public prototype_ `void UpdateParameters();`
- L126 _public prototype_ `void EnqueueNewReverb(TUniquePtr<FConvolutionReverb> InReverb, const AudioConvReverbIntrinsics::FVersionData& InVersionData);`
- L127 _public prototype_ `void DequeueNewReverb();`
- L129 _public prototype_ `bool IsVersionCurrent(const AudioConvReverbIntrinsics::FVersionData& InVersionData) const;`
- L130 _public prototype_ `bool IsChannelCountUpToDate(const int32 InNumInputChannels, const int32 InNumOutputChannels) const;`
- L133 _private member_ `TUniquePtr<FConvolutionReverb> Reverb;`
- L136 _private member_ `TUniquePtr<FConvolutionReverb> QueuedReverb;` — Reverb created by our async builder
- L138 _private member_ `mutable FCriticalSection VersionDataCriticalSection;`
- L139 _private member_ `AudioConvReverbIntrinsics::FVersionData VersionData;`
- L140 _private member_ `AudioConvReverbIntrinsics::FVersionData QueuedVersionData;`
- L142 _private member_ `mutable FCriticalSection ConvReverbInitDataCriticalSection;`
- L144 _private member_ `FConvolutionReverbInitData ConvReverbInitData;` — Internal copy of data needed to create FConvolutionReverb
- L146 _private member_ `TAtomic<int32> NumInputChannels = 2;`
- L147 _private member_ `TAtomic<int32> NumOutputChannels = 2;`
- L150 _private member_ `TParams<FConvolutionReverbSettings> Params;` — Params object for copying between audio render thread and outside threads.
- L152 _private member_ `bool bBypass = false;`
- L153 _private member_ `float SampleRate = 0.f;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SYNTHESIS_API`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAudioImpulseResponsePropertyChange, FPropertyChangedEvent&);`
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAudioImpulseResponsePropertyChange, FPropertyChangedEvent&);`
- L77 _namespace_ `namespace AudioConvReverbIntrinsics`
- L81 _typedef_ `typedef int32 FConvolutionReverbID;` (scope `AudioConvReverbIntrinsics`)
- L100 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/EpicSynth1.h` (Public)


#### class `Audio::FEpicSynth1Voice`  
`class FEpicSynth1Voice`  
_L16-103_
- L19 _public member_ `static const int32 NumOscillators = 2;`
- L20 _public member_ `static const int32 NumLFOs = 2;`
- L22 _public prototype_ `FEpicSynth1Voice();`
- L23 _public prototype_ `~FEpicSynth1Voice();`
- L25 _public prototype_ `void Init(FEpicSynth1* InParentSynth, const int32 InVoiceId);`
- L26 _public prototype_ `void Reset();`
- L28 _public prototype_ `void NoteOn(const uint32 InMidiNote, const float InVelocity, const float InDurationSec);`
- L29 _public prototype_ `void NoteOff(const uint32 InMidiNote, const bool bAllNotesOff = false);`
- L30 _public prototype_ `void Kill();`
- L31 _public prototype_ `void Shutdown();`
- L33 _public function_ `bool IsFinished() const`
- L34 _public function_ `bool IsActive() const`
- L36 _public function_ `uint32 GetGeneration() const`
- L37 _public function_ `int32 GetMidiNote() const`
- L38 _public prototype_ `void SetLFOPatch(const int32 InLFOIndex, const ESynthLFOPatchType InPatchType);`
- L39 _public prototype_ `void SetEnvModPatch(const ESynthModEnvPatch InPatchType);`
- L40 _public prototype_ `void SetEnvModBiasPatch(const ESynthModEnvBiasPatch InPatchType);`
- L42 _public prototype_ `void Generate(float InSamples[2]);`
- L44 _public prototype_ `void ClearPatches();`
- L45 _public prototype_ `bool CreatePatch(const FPatchId PatchId, const ESynth1PatchSource PatchSource, const TArray<FSynth1PatchCable>& PatchCables, const bool bEnableByDefault);`
- L46 _public prototype_ `bool SetEnablePatch(const FPatchId PatchId, const bool bIsEnabled);`
- L50 _protected prototype_ `FPatchSource GetPatchSource(ESynth1PatchSource PatchSource);`
- L51 _protected prototype_ `void GetPatchDestinations(ESynth1PatchDestination PatchDestination, TArray<FPatchDestination>& Destinations);`
- L54 _protected member_ `FOsc Oscil[NumOscillators];` — Audio rate objects
- L55 _protected member_ `FAmp OscilPan[NumOscillators];`
- L56 _protected member_ `FAmp Amp;`
- L57 _protected member_ `FOnePoleFilter OnePoleFilter;`
- L58 _protected member_ `FStateVariableFilter StateVarFilter;`
- L59 _protected member_ `FLadderFilter LadderFilter;`
- L61 _protected member_ `IFilter* CurrentFilter;` — Which filter we're currently using
- L64 _protected member_ `FEnvelope GainEnv;` — Control rate objects
- L65 _protected member_ `FEnvelope ModEnv;`
- L66 _protected member_ `FLFO LFO[NumLFOs];`
- L67 _protected member_ `FLinearEase PortamentoFrequency;`
- L70 _protected member_ `FPatch LFOPatches[NumLFOs][(int32)ESynthLFOPatchType::Count];` — Mod-matrix patches for the voice
- L71 _protected member_ `FPatch ModEnvPatches[(int32)ESynthModEnvPatch::Count];`
- L72 _protected member_ `FPatch ModEnvBiasPatches[(int32)ESynthModEnvBiasPatch::Count];`
- L74 _protected member_ `TMap<int32, TSharedPtr<FPatch>> DynamicPatches;`
- L76 _protected member_ `ESynthLFOPatchType CurrentPatchType[NumLFOs];`
- L77 _protected member_ `ESynthModEnvPatch CurrentModPatchType;`
- L78 _protected member_ `ESynthModEnvBiasPatch CurrentModBiasPatchType;`
- L80 _protected member_ `FPatch Env_To_Amp;`
- L81 _protected member_ `FPatch Env_To_Filter;`
- L84 _protected member_ `int32 MidiNote;` — Data.
- L85 _protected member_ `int32 VoiceId;`
- L86 _protected member_ `int32 ControlSampleCount;`
- L87 _protected member_ `int32 DurationSampleCount;`
- L88 _protected member_ `int32 CurrentSampleCount;`
- L91 _protected member_ `uint32 VoiceGeneration;` — Used to do voice stealing
- L94 _protected member_ `FEpicSynth1* ParentSynth;` — Owning synth
- L97 _protected member_ `bool bIsFinished;` — If voice has finished
- L100 _protected member_ `bool bIsActive;` — If voice is active (i.e. not free)

#### class `Audio::FEpicSynth1`  
`class FEpicSynth1`  
_L105-265_
- L108 _public prototype_ `FEpicSynth1();`
- L109 _public prototype_ `virtual ~FEpicSynth1();`
- L111 _public prototype_ `void Init(const float InSampleRate, const int32 InMaxVoices);`
- L114 _public prototype_ `void SetMonoMode(const bool bIsMono);` — Set the synth to be in mono mode
- L117 _public prototype_ `void NoteOn(const uint32 InMidiNote, const float InVelocity, const float Duration = -1.0f);` — Plays a note with the given midi note and midi velocity
- L120 _public prototype_ `void NoteOff(const uint32 InMidiNote, const bool bAllNotesOff = false, const bool bKillAllNotes = false);` — Turns the note off (triggers release envelope)
- L123 _public prototype_ `void SetOscType(const int32 InOscIndex, const EOsc::Type InOscType);` — Oscillator setting
- L124 _public prototype_ `void SetOscGain(const int32 InOscIndex, const float InGain);`
- L125 _public prototype_ `void SetOscGainMod(const int32 InOscIndex, const float InGain);`
- L126 _public prototype_ `void SetOscDetune(const int32 InOscIndex, const float InDetuneFreq);`
- L127 _public prototype_ `void SetOscOctave(const int32 InOscIndex, const float InOctave);`
- L128 _public prototype_ `void SetOscSemitones(const int32 InOscIndex, const float InSemitones);`
- L129 _public prototype_ `void SetOscCents(const int32 InOscIndex, const float InCents);`
- L130 _public prototype_ `void SetOscPitchBend(const int32 InOscIndex, const float InPitchBend);`
- L131 _public prototype_ `void SetOscPulseWidth(const int32 InOscIndex, const float InPulseWidth);`
- L132 _public prototype_ `void SetOscPortamento(const float InPortamento);`
- L133 _public prototype_ `void SetOscSpread(const float InSpread);`
- L134 _public prototype_ `void SetOscUnison(const bool bInUnison);`
- L135 _public prototype_ `void SetOscSync(const bool bIsSync);`
- L138 _public prototype_ `void SetFilterAlgorithm(const ESynthFilterAlgorithm FilterAlgorithm);` — Filter setting
- L139 _public prototype_ `void SetFilterType(const EFilter::Type FilterType);`
- L140 _public prototype_ `void SetFilterFrequency(const float InFilterFrequency);`
- L141 _public prototype_ `void SetFilterFrequencyMod(const float InFilterFrequencyModulation);`
- L142 _public prototype_ `void SetFilterQ(const float InFilterQ);`
- L143 _public prototype_ `void SetFilterQMod(const float InFilterQModulation);`
- L146 _public prototype_ `void SetLFOType(const int32 LFOIndex, const ELFO::Type InLFOType);` — LFO setting
- L147 _public prototype_ `void SetLFOMode(const int32 LFOIndex, const ELFOMode::Type InLFOMode);`
- L148 _public prototype_ `void SetLFOPatch(const int32 LFOIndex, const ESynthLFOPatchType InRouteType);`
- L149 _public prototype_ `void SetLFOGain(const int32 LFOIndex, const float InLFOGain);`
- L150 _public prototype_ `void SetLFOGainMod(const int32 LFOIndex, const float InLFOGainMod);`
- L151 _public prototype_ `void SetLFOFrequency(const int32 LFOIndex, const float InLFOFrequency);`
- L152 _public prototype_ `void SetLFOFrequencyMod(const int32 LFOIndex, const float InLFOFrequencyMod);`
- L153 _public prototype_ `void SetLFOPulseWidth(const int32 LFOIndex, const float InPulseWidth);`
- L156 _public prototype_ `void SetEnvAttackTime(const float InAttackTimeMsec);` — Envelope setting
- L157 _public prototype_ `void SetEnvDecayTime(const float InDecayTimeMsec);`
- L158 _public prototype_ `void SetEnvSustainGain(const float InSustainGain);`
- L159 _public prototype_ `void SetEnvReleaseTime(const float InReleaseTimeMsec);`
- L160 _public prototype_ `void SetEnvLegatoEnabled(const bool bIsLegatoEnabled);`
- L161 _public prototype_ `void SetEnvRetriggerMode(const bool bIsRetriggerMode);`
- L164 _public prototype_ `void SetModEnvPatch(const ESynthModEnvPatch InPatchType);` — Modulation Envelope Setting
- L165 _public prototype_ `void SetModEnvBiasPatch(const ESynthModEnvBiasPatch InPatchType);`
- L166 _public prototype_ `void SetModEnvInvert(const bool bInInvert);`
- L167 _public prototype_ `void SetModEnvBiasInvert(const bool bInInvert);`
- L168 _public prototype_ `void SetModEnvDepth(const float InDepth);`
- L169 _public prototype_ `void SetModEnvAttackTime(const float InAttackTimeMsec);`
- L170 _public prototype_ `void SetModEnvDecayTime(const float InDecayTimeMsec);`
- L171 _public prototype_ `void SetModEnvSustainGain(const float InSustainGain);`
- L172 _public prototype_ `void SetModEnvReleaseTime(const float InReleaseTimeMsec);`
- L175 _public prototype_ `void SetPan(const float InPan);` — Pan and gain setting
- L176 _public prototype_ `void SetGainDb(const float InGainDb);`
- L179 _public prototype_ `void SetStereoDelayIsEnabled(const bool bInIsStereoEnabled);` — Stereo Delay parameters
- L180 _public prototype_ `void SetStereoDelayMode(EStereoDelayMode::Type InStereoDelayMode);`
- L181 _public prototype_ `void SetStereoDelayTimeMsec(const float InDelayTimeMsec);`
- L182 _public prototype_ `void SetStereoDelayFeedback(const float InDelayFeedback);`
- L183 _public prototype_ `void SetStereoDelayRatio(const float InDelayRatio);`
- L184 _public prototype_ `void SetStereoDelayWetLevel(const float InDelayWetLevel);`
- L187 _public prototype_ `void SetChorusEnabled(const bool bInIsChorusEnabled);` — Chorus parameters
- L188 _public prototype_ `void SetChorusDepth(const EChorusDelays::Type InType, const float InDepth);`
- L189 _public prototype_ `void SetChorusFeedback(const EChorusDelays::Type InType, const float InFeedback);`
- L190 _public prototype_ `void SetChorusFrequency(const EChorusDelays::Type InType, const float InFrequency);`
- L192 _public prototype_ `void ClearPatches();`
- L193 _public prototype_ `FPatchId CreatePatch(const ESynth1PatchSource PatchSource, const TArray<FSynth1PatchCable>& PatchCables, const bool bEnableByDefault);`
- L194 _public prototype_ `bool SetEnablePatch(const FPatchId PatchId, bool bIsEnabled);`
- L197 _public prototype_ `void GenerateFrame(float* OutFrame);` — Generate the next frame of audio
- L201 _protected prototype_ `void SwitchFilter();`
- L202 _protected prototype_ `uint32 GetOldestPlayingId();`
- L203 _protected prototype_ `void StopAllVoicesExceptNewest();`
- L206 _protected member_ `int32 MaxNumVoices;` — The max number of voices allowed in the synth
- L209 _protected member_ `int32 NumVoices;` — The current number of voices, may be less than MaxNumVoices
- L212 _protected member_ `int32 NumActiveVoices;` — Count of number of voices in flight. Should not be greater than NumVoices.
- L215 _protected member_ `int32 NumStoppingVoices;` — Number of buffer voices used for stopping voices
- L218 _protected member_ `FEpicSynth1Voice* LastVoice;` — The last played voice
- L221 _protected member_ `float SampleRate;` — Sample rate of the synth
- L224 _protected member_ `float ControlSampleRate;` — Control sample rate (LFOs, etc)
- L227 _protected member_ `int32 ControlSamplePeriod;` — The number of real samples per control rate tick
- L230 _protected member_ `FModulationMatrix ModMatrix;` — Mod matrix object (used to route connections)
- L233 _protected member_ `float Portamento;` — Time to pitch shift up or down to target notes
- L236 _protected member_ `uint32 LastMidiNote;` — Last midi note played, used for portamento
- L239 _protected member_ `TArray<FEpicSynth1Voice*> Voices;` — The allocated voice pool
- L242 _protected member_ `TArray<int32> FreeVoices;` — List of free voice indices
- L245 _protected member_ `uint32 VoiceGeneration;` — An incremented number used to track voice age. Older voices have smaller generation counts.
- L248 _protected member_ `float BaseFilterFreq;` — Filter data
- L249 _protected member_ `float FilterFreqMod;`
- L251 _protected member_ `float BaseFilterQ;`
- L252 _protected member_ `float FilterQMod;`
- L254 _protected member_ `EFilter::Type FilterType;`
- L255 _protected member_ `ESynthFilterAlgorithm FilterAlgorithm;`
- L258 _protected member_ `FDelayStereo StereoDelay;` — Stereo delay effect
- L259 _protected member_ `FChorus Chorus;`
- L262 _protected member_ `bool bIsUnison : 1;`
- L263 _protected member_ `bool bIsStereoEnabled : 1;`
- L264 _protected member_ `bool bIsChorusEnabled : 1;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/EpicSynth1Types.h` (Public)


#### enum `ESynth1OscType`  
`enum class ESynth1OscType : uint8`  
_L8-16_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `Sine = 0`
- L11 _public enumerator_ `Saw`
- L12 _public enumerator_ `Triangle`
- L13 _public enumerator_ `Square`
- L14 _public enumerator_ `Noise`
- L15 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthLFOType`  
`enum class ESynthLFOType : uint8`  
_L19-29_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Sine = 0`
- L22 _public enumerator_ `UpSaw`
- L23 _public enumerator_ `DownSaw`
- L24 _public enumerator_ `Square`
- L25 _public enumerator_ `Triangle`
- L26 _public enumerator_ `Exponential`
- L27 _public enumerator_ `RandomSampleHold`
- L28 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthLFOMode`  
`enum class ESynthLFOMode : uint8`  
_L32-38_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `Sync = 0`
- L35 _public enumerator_ `OneShot`
- L36 _public enumerator_ `Free`
- L37 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthLFOPatchType`  
`enum class ESynthLFOPatchType : uint8`  
_L41-54_
- reflection: `UENUM(BlueprintType)`
- L43 _public enumerator_ `PatchToNone = 0`
- L45 _public enumerator_ `PatchToGain`
- L46 _public enumerator_ `PatchToOscFreq`
- L47 _public enumerator_ `PatchToFilterFreq`
- L48 _public enumerator_ `PatchToFilterQ`
- L49 _public enumerator_ `PatchToOscPulseWidth`
- L50 _public enumerator_ `PatchToOscPan`
- L51 _public enumerator_ `PatchLFO1ToLFO2Frequency`
- L52 _public enumerator_ `PatchLFO1ToLFO2Gain`
- L53 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthModEnvPatch`  
`enum class ESynthModEnvPatch : uint8`  
_L57-69_
- reflection: `UENUM(BlueprintType)`
- L59 _public enumerator_ `PatchToNone = 0`
- L61 _public enumerator_ `PatchToOscFreq`
- L62 _public enumerator_ `PatchToFilterFreq`
- L63 _public enumerator_ `PatchToFilterQ`
- L64 _public enumerator_ `PatchToLFO1Gain`
- L65 _public enumerator_ `PatchToLFO2Gain`
- L66 _public enumerator_ `PatchToLFO1Freq`
- L67 _public enumerator_ `PatchToLFO2Freq`
- L68 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthModEnvBiasPatch`  
`enum class ESynthModEnvBiasPatch : uint8`  
_L72-84_
- reflection: `UENUM(BlueprintType)`
- L74 _public enumerator_ `PatchToNone = 0`
- L76 _public enumerator_ `PatchToOscFreq`
- L77 _public enumerator_ `PatchToFilterFreq`
- L78 _public enumerator_ `PatchToFilterQ`
- L79 _public enumerator_ `PatchToLFO1Gain`
- L80 _public enumerator_ `PatchToLFO2Gain`
- L81 _public enumerator_ `PatchToLFO1Freq`
- L82 _public enumerator_ `PatchToLFO2Freq`
- L83 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthFilterType`  
`enum class ESynthFilterType : uint8`  
_L87-94_
- reflection: `UENUM(BlueprintType)`
- L89 _public enumerator_ `LowPass = 0`
- L90 _public enumerator_ `HighPass`
- L91 _public enumerator_ `BandPass`
- L92 _public enumerator_ `BandStop`
- L93 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthFilterAlgorithm`  
`enum class ESynthFilterAlgorithm : uint8`  
_L97-103_
- reflection: `UENUM(BlueprintType)`
- L99 _public enumerator_ `OnePole = 0`
- L100 _public enumerator_ `StateVariable`
- L101 _public enumerator_ `Ladder`
- L102 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthStereoDelayMode`  
`enum class ESynthStereoDelayMode : uint8`  
_L106-112_
- reflection: `UENUM(BlueprintType)`
- L108 _public enumerator_ `Normal = 0`
- L109 _public enumerator_ `Cross`
- L110 _public enumerator_ `PingPong`
- L111 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynth1PatchSource`  
`enum class ESynth1PatchSource : uint8`  
_L115-122_
- reflection: `UENUM(BlueprintType)`
- L117 _public enumerator_ `LFO1`
- L118 _public enumerator_ `LFO2`
- L119 _public enumerator_ `Envelope`
- L120 _public enumerator_ `BiasEnvelope`
- L121 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynth1PatchDestination`  
`enum class ESynth1PatchDestination : uint8`  
_L125-142_
- reflection: `UENUM(BlueprintType)`
- L127 _public enumerator_ `Osc1Gain`
- L128 _public enumerator_ `Osc1Frequency`
- L129 _public enumerator_ `Osc1Pulsewidth`
- L130 _public enumerator_ `Osc2Gain`
- L131 _public enumerator_ `Osc2Frequency`
- L132 _public enumerator_ `Osc2Pulsewidth`
- L133 _public enumerator_ `FilterFrequency`
- L134 _public enumerator_ `FilterQ`
- L135 _public enumerator_ `Gain`
- L136 _public enumerator_ `Pan`
- L137 _public enumerator_ `LFO1Frequency`
- L138 _public enumerator_ `LFO1Gain`
- L139 _public enumerator_ `LFO2Frequency`
- L140 _public enumerator_ `LFO2Gain`
- L141 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSynth1PatchCable`  
`struct FSynth1PatchCable`  
_L145-156_
- reflection: `USTRUCT(BlueprintType)`
- L151 _public member_ `float Depth = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The patch depth (how much the modulator modulates the destination)
- L155 _public member_ `ESynth1PatchDestination Destination = ESynth1PatchDestination::Osc1Gain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The patch destination type

#### struct `FPatchId`  
`struct FPatchId`  
_L159-165_
- reflection: `USTRUCT(BlueprintType)`
- L164 _public member_ `int32 Id = INDEX_NONE;` — `UPROPERTY()`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/Flexiverb.h` (Public)


#### struct `Audio::FFlexiverbSettings`  
`struct FFlexiverbSettings`  
_L11-35_
- L16 _public member_ `float Complexity;` — The higher the complexity value, the higher the computational and memory requirements. However, increasing the complexity value will also increase the echo density of the reverb. Note that setting a new complexity value will induce reallocation of memory.
- L19 _public member_ `float DecayTime;` — An approximation of the time, in seconds, the reverb should take to decay to -60 dB.
- L23 _public member_ `float PreDelay;` — The amount, in milliseconds, of delay before the reverberation effect begins. This is equivalent to the hearing the first reflection of a sound source in a room.
- L26 _public member_ `float RoomDampening;` — Frequency, in HZ. All frequencies above this value are attenuated.
- L28 _public function_ `FFlexiverbSettings() : Complexity(4) , DecayTime(6.0f) , PreDelay(6.0f) , RoomDampening(220.0f)`

#### class `Audio::FFlexiverb`  
`class FFlexiverb`  
_L49-94_
- L52 _public prototype_ `FFlexiverb();`
- L53 _public prototype_ `~FFlexiverb();`
- L56 _public prototype_ `void Init(const int32 InSampleRate, const FFlexiverbSettings Settings = FFlexiverbSettings());` — Initialize the reverb with the given sample rate and initial settings.
- L59 _public prototype_ `void SetSettings(const FFlexiverbSettings& InSettings);` — Updates the current settings of this reverb.
- L62 _public prototype_ `void ProcessAudioFrame(const float* InBuffer, const int32 InChannels, float* OutBuffer, const int32 OutChannels);` — Process a single audio frame.
- L66 _private prototype_ `void Update();` — Calculates coefficients based on the current settings.
- L69 _private prototype_ `void UpdateComplexity(const int32 Complexity);` — Manage memory associated with our FDN.
- L72 _private member_ `float SampleRate;` — Sample rate this instance is initialized to.
- L75 _private member_ `FFlexiverbSettings PrivateSettings;` — Private copy of the current reverb settings.
- L78 _private member_ `FDelay PreDelayLine;` — Delay Line used for pre-delay.
- L81 _private member_ `TArray<FDelayAPF> DelayLines;` — Delay lines used for the primary FDN.
- L84 _private member_ `TArray<FDelayAPF> APFArray;` — Series of APF filters used to decorrelate the input before it enters the FDN.
- L87 _private member_ `TArray<FOnePoleLPF> DampeningArray;` — Room dampening is handled with second order parametric filters.
- L90 _private member_ `float DecayFactor;` — Factor applied to the input of all delays lines.
- L93 _private member_ `int32 ScatteringMatrixLength;` — Amount of delay lines in our FDN.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Audio`
- L7 _namespace_ `namespace Audio`
- L9 _namespace_ `namespace Audio`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/MonoWaveTable.h` (Public)


#### class `Audio::FMonoWaveTable`  
`class FMonoWaveTable`  
_L14-132_
- L17 _public prototype_ `FMonoWaveTable();`
- L18 _public prototype_ `~FMonoWaveTable();`
- L20 _public prototype_ `void Init(int32& InSampleRate, DefaultWaveTableIndexType InNumTableElements, float InWaveTableResolution);`
- L21 _public prototype_ `void NoteOn(float InFrequency, float Velocity = 1.0f);`
- L22 _public prototype_ `void NoteOff(float InFrequency);`
- L25 _public function_ `float GetWaveTableResolution()` — Oscillator/Table setting
- L26 _public prototype_ `void UpdateWaveTable(DefaultWaveTableIndexType Index, const TArray<float>& InTable);`
- L27 _public function_ `void SetFrequency(float InFrequencyHz)`
- L28 _public function_ `void SetFrequencyOffset(float InFrequencyCents)`
- L29 _public function_ `void SetPosition(float InPosition)`
- L32 _public function_ `void SetLpfFreq(float InNewFrequency)` — Filter setting
- L33 _public function_ `void SetLpfRes(float InNewQ)`
- L37 _public prototype_ `void SetPosLFOFrequency(const float InPosLFOFrequency);` — LFO setting Table Position
- L38 _public prototype_ `void SetPosLFODepth(const float InPosLFODepth);`
- L39 _public prototype_ `void SetPosLFOType(const ELFO::Type InPosLFOType);`
- L43 _public prototype_ `void SetAmpEnvelopeAttackTime(const float InAttackTimeMsec);` — Envelope setting Amp
- L44 _public prototype_ `void SetAmpEnvelopeDecayTime(const float InDecayTimeMsec);`
- L45 _public prototype_ `void SetAmpEnvelopeSustainGain(const float InSustainGain);`
- L46 _public prototype_ `void SetAmpEnvelopeReleaseTime(const float InReleaseTimeMsec);`
- L47 _public prototype_ `void SetAmpEnvelopeInvert(const bool bInInvert);`
- L48 _public prototype_ `void SetAmpEnvelopeBiasInvert(const bool bInBiasInvert);`
- L49 _public prototype_ `void SetAmpEnvelopeDepth(const float InDepth);`
- L50 _public prototype_ `void SetAmpEnvelopeBiasDepth(const float InDepth);`
- L53 _public prototype_ `void SetFilterEnvelopeAttackTime(const float InAttackTimeMsec);` — Filter
- L54 _public prototype_ `void SetFilterEnvelopenDecayTime(const float InDecayTimeMsec);`
- L55 _public prototype_ `void SetFilterEnvelopeSustainGain(const float InSustainGain);`
- L56 _public prototype_ `void SetFilterEnvelopeReleaseTime(const float InReleaseTimeMsec);`
- L57 _public prototype_ `void SetFilterEnvelopeInvert(const bool bInInvert);`
- L58 _public prototype_ `void SetFilterEnvelopeBiasInvert(const bool bInBiasInvert);`
- L59 _public prototype_ `void SetFilterEnvelopeDepth(const float InDepth);`
- L60 _public prototype_ `void SetFilterEnvelopeBiasDepth(const float InDepth);`
- L63 _public prototype_ `void SetPositionEnvelopeAttackTime(const float InAttackTimeMsec);` — Table Position
- L64 _public prototype_ `void SetPositionEnvelopeDecayTime(const float InDecayTimeMsec);`
- L65 _public prototype_ `void SetPositionEnvelopeSustainGain(const float InSustainGain);`
- L66 _public prototype_ `void SetPositionEnvelopeReleaseTime(const float InReleaseTimeMsec);`
- L67 _public prototype_ `void SetPositionEnvelopeInvert(const bool bInInvert);`
- L68 _public prototype_ `void SetPositionEnvelopeBiasInvert(const bool bInBiasInvert);`
- L69 _public prototype_ `void SetPositionEnvelopeDepth(const float InDepth);`
- L70 _public prototype_ `void SetPositionEnvelopeBiasDepth(const float InDepth);`
- L73 _public prototype_ `void SetSustainPedalPressed(bool bInSustainPedalState);` — Performance
- L77 _public prototype_ `DefaultWaveTableIndexType OnGenerateAudio(float* OutAudio, DefaultWaveTableIndexType NumSamples);` — Generate the next frame of audio
- L81 _protected member_ `float WaveTableResolution;` — The number of samples in a wave table entry
- L84 _protected member_ `float OutputSampleRate;` — Audio rendering Sample rate
- L87 _protected member_ `float FrequencyInHz;` — frequency of current note (mono)
- L90 _protected member_ `float Phase;` — Index into Wave Table
- L94 _protected member_ `float WaveTablePosition;` — Current base index into wave table (modulators contribute to final position) (float between [0.0, 1.0]; 0.0 = first wave table, 1.0 = last wave table)
- L96 _protected member_ `float LastWaveTablePosition;`
- L99 _protected member_ `float LPFBaseFreqHz { 1'000.0f };` — The current base frequency of LPF (modulators contribute to final value)
- L100 _protected member_ `float LPFMaxModOffsetOctaves;`
- L101 _protected member_ `float LPFCeilingHz;`
- L102 _protected member_ `float LastLPFFreqHz;`
- L103 _protected member_ `float NewAmpSustain { 0.0f };`
- L104 _protected member_ `float LastAmpSustain { 0.0f };`
- L106 _protected member_ `float PitchOffsetCents;` — Pitch bend wheel
- L110 _protected member_ `TArray<TSampleBuffer<float>> WaveTableMatrix;` — Table TArray<TArray<float>> WaveTableMatrix;
- L111 _protected member_ `TArray<float> WaveTableLookupOutput;`
- L114 _protected member_ `Audio::FLFO PosLfo;` — control data
- L115 _protected member_ `Audio::FEnvelope AmpEnv;`
- L116 _protected member_ `Audio::FEnvelope LPFEnv;`
- L117 _protected member_ `Audio::FEnvelope PosEnv;`
- L120 _protected member_ `Audio::FLadderFilter LPF;` — Filters
- L123 _protected prototype_ `float UpdateWaveTableLookupOutput(float InPhaseIndex);` — helper that performs fractional indexing and wraps TableIndex
- L124 _protected prototype_ `float GetMonoSynthOutput(float InTablePosition);`
- L127 _protected member_ `TArray<float> NoteStack;` — frequencies of unreleased notes
- L129 _protected member_ `uint8 bInitialized : 1;`
- L130 _protected member_ `uint8 bIsPlaying : 1;`
- L131 _protected member_ `uint8 bIsSustainPedalPressed : 1;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L12 _typedef_ `typedef int32 DefaultWaveTableIndexType;` (scope `Audio`)

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/SynthesisBlueprintUtilities.h` (Public)


#### class `USynthesisUtilitiesBlueprintFunctionLibrary`  
`class USynthesisUtilitiesBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L12-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Synthesis Utilities Blueprint Function Library A library of synthesis related functions for use in Blueprints
- L18 _private prototype_ `static float GetLogFrequency(float InLinearValue, float InDomainMin, float InDomainMax, float InRangeMin, float InRangeMax);` — `UFUNCTION(BlueprintCallable, Category = "Synthesis Utilities Library")` — Returns the log frequency of the input value. Maps linear domain and range values to log output (good for linear slider controlling frequency)
- L22 _private prototype_ `static float GetLinearFrequency(float InLogFrequencyValue, float InDomainMin, float InDomainMax, float InRangeMin, float InRangeMax);` — `UFUNCTION(BlueprintCallable, Category = "Synthesis Utilities Library")` — Returns the log frequency of the input value. Maps linear domain and range values to log output (good for linear slider controlling frequency)

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/SynthesisModule.h` (Public)


#### class `FSynthesisModule`  
`class FSynthesisModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSynthesis, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSynthesis, Log, All);`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/SSynth2DSlider.h` (Public)


#### class `SSynth2DSlider`  
`class SSynth2DSlider : public SLeafWidget`  
_L22-204_
- inherits: `SLeafWidget`
- desc: A Slate slider control is a linear scale and draggable handle.
- L26 _public function_ `SLATE_BEGIN_ARGS(SSynth2DSlider) : _IndentHandle(true) , _Locked(false) , _Style(&FSynthSlateStyleSet::Get()->GetWidgetStyle<FSynth2DSliderStyle>("Synth2DSliderStyle")) , _StepSize(0.01f) , _ValueX(1.f) , _ValueY(1.f) , _IsFocusable(true) , _OnMouseCaptureBegin() , _OnMouseCaptureEnd() , _OnValueChangedX() , _OnValueChangedY()`
- L41 _public prototype_ `SLATE_ATTRIBUTE(bool, IndentHandle) SLATE_ATTRIBUTE(bool, Locked) SLATE_STYLE_ARGUMENT(FSynth2DSliderStyle, Style) SLATE_ATTRIBUTE(float, StepSize) SLATE_ATTRIBUTE(float, ValueX) SLATE_ATTRIBUTE(float, ValueY) SLATE_ARGUMENT(bool, IsFocusable) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_EVENT(FSimpleDelegate, OnControllerCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnControllerCaptureEnd) SLATE_EVENT(FOnFloatValueChanged, OnValueChangedX) SLATE_EVENT(FOnFloatValueChanged, OnValueChangedY) SLATE_END_ARGS()` — Whether the slidable area should be indented to fit the handle.
- L89 _public prototype_ `float GetValueX() const;` — See the Value attribute
- L90 _public prototype_ `float GetValueY() const;`
- L93 _public prototype_ `void SetValueX(const TAttribute<float>& InValueAttribute);` — See the Value attribute
- L94 _public prototype_ `void SetValueY(const TAttribute<float>& InValueAttribute);`
- L97 _public prototype_ `void SetIndentHandle(const TAttribute<bool>& InIndentHandle);` — See the IndentHandle attribute
- L100 _public prototype_ `void SetLocked(const TAttribute<bool>& InLocked);` — See the Locked attribute
- L103 _public prototype_ `void SetOrientation(EOrientation InOrientation);` — See the Orientation attribute
- L106 _public prototype_ `void SetSliderBarColor(FSlateColor InSliderBarColor);` — See the SliderBarColor attribute
- L109 _public prototype_ `void SetSliderHandleColor(FSlateColor InSliderHandleColor);` — See the SliderHandleColor attribute
- L112 _public prototype_ `void SetStepSize(const TAttribute<float>& InStepSize);` — See the StepSize attribute
- L118 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L119 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L120 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L121 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L122 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L123 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L124 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L125 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L127 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L128 _public prototype_ `virtual bool IsInteractable() const override;`
- L131 _public prototype_ `bool IsLocked() const;` — @return Is the handle locked or not? Defaults to false
- L140 _protected prototype_ `void CommitValue(float NewValueX, float NewValueY);` — Commits the specified slider value. @param NewValue The value to commit.
- L149 _protected prototype_ `FVector2D PositionToValue(const FGeometry& MyGeometry, const FVector2D& AbsolutePosition);` — Calculates the new value based on the given absolute coordinates. @param MyGeometry The slider's geometry. @param AbsolutePosition The absolute position of the slider. @return The new value.
- L154 _private member_ `const FSynth2DSliderStyle* Style;` — Holds the style passed to the widget upon construction.
- L157 _private member_ `TAttribute<bool> IndentHandle;` — Holds a flag indicating whether the slideable area should be indented to fit the handle.
- L160 _private member_ `TAttribute<bool> LockedAttribute;` — Holds a flag indicating whether the slider is locked.
- L163 _private member_ `EOrientation Orientation;` — Holds the slider's orientation.
- L166 _private member_ `TAttribute<FSlateColor> SliderBarColor;` — Holds the color of the slider bar.
- L169 _private member_ `TAttribute<FSlateColor> SliderHandleColor;` — Holds the color of the slider handle.
- L171 _private member_ `TAttribute<float> ValueAttributeX;`
- L172 _private member_ `TAttribute<float> ValueAttributeY;`
- L175 _private member_ `TAttribute<float> StepSize;` — Holds the amount to adjust the value by when using a controller or keyboard
- L179 _private member_ `bool bControllerInputCaptured;` — Holds a flag indicating whether a controller/keyboard is manipulating the slider's value. When true, navigation away from the widget is prevented until a new value has been accepted or canceled.
- L182 _private member_ `bool bIsFocusable;` — When true, this slider will be keyboard focusable. Defaults to false.
- L187 _private prototype_ `void ResetControllerState();` — Resets controller input state. Fires delegates.
- L190 _private member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L193 _private member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when the mouse is let up and a capture ends.
- L196 _private member_ `FSimpleDelegate OnControllerCaptureBegin;` — Holds a delegate that is executed when capture begins for controller or keyboard.
- L199 _private member_ `FSimpleDelegate OnControllerCaptureEnd;` — Holds a delegate that is executed when capture ends for controller or keyboard.
- L202 _private member_ `FOnFloatValueChanged OnValueChangedX;` — Holds a delegate that is executed when the slider's value changed.
- L203 _private member_ `FOnFloatValueChanged OnValueChangedY;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/SSynthKnob.h` (Public)


#### class `SSynthKnob`  
`class SSynthKnob : public SLeafWidget`  
_L17-214_
- inherits: `SLeafWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SSynthKnob) : _Locked(false) , _Style(&FSynthSlateStyleSet::Get()->GetWidgetStyle<FSynthKnobStyle>("SynthKnobStyle")) , _StepSize(0.01f) , _MouseSpeed(1.0f) , _MouseFineTuneSpeed(0.2f) , _Value(0.5f) , _ParameterName(FText::GetEmpty()) , _ParameterUnits(FText::GetEmpty()) , _ParameterRange(FVector2D(0.0f, 1.0f)) , _ShowParamTooltip(true) , _IsFocusable(true) , _OnMouseCaptureBegin() , _OnMouseCaptureEnd() , _OnValueChanged()`
- L39 _public prototype_ `SLATE_ATTRIBUTE(bool, Locked) SLATE_STYLE_ARGUMENT(FSynthKnobStyle, Style) SLATE_ATTRIBUTE(float, StepSize) SLATE_ATTRIBUTE(float, MouseSpeed) SLATE_ATTRIBUTE(float, MouseFineTuneSpeed) SLATE_ATTRIBUTE(float, Value) SLATE_ATTRIBUTE(FText, ParameterName) SLATE_ATTRIBUTE(FText, ParameterUnits) SLATE_ATTRIBUTE(FVector2D, ParameterRange) SLATE_ARGUMENT(bool, ShowParamTooltip) SLATE_ARGUMENT(bool, IsFocusable) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_EVENT(FSimpleDelegate, OnControllerCaptureBegin)` — Whether the handle is interactive or fixed.
- L96 _public prototype_ `float GetValue() const;` — See the Value attribute
- L99 _public prototype_ `void SetValue(const TAttribute<float>& InValueAttribute);` — See the Value attribute
- L102 _public prototype_ `void SetLocked(const TAttribute<bool>& InLocked);` — See the Locked attribute
- L105 _public prototype_ `void SetStepSize(const float InStepSize);` — See the StepSize attribute
- L108 _public prototype_ `void SetMouseSpeed(const float InMouseSpeed);` — See the MousePeed attribute
- L111 _public prototype_ `void SetMouseFineTuneSpeed(const float InMouseFineTuneSpeed);` — See the MousePeed attribute
- L114 _public prototype_ `FVector2D GetMouseDownPosition();` — Return the last mouse down position.
- L120 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L121 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L122 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L123 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L124 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L125 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L126 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L127 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L128 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L129 _public prototype_ `virtual bool IsInteractable() const override;`
- L132 _public prototype_ `bool IsLocked() const;` — @return Is the handle locked or not? Defaults to false
- L138 _public prototype_ `void CommitValue(float NewValue);` — Commits the specified slider value. @param NewValue The value to commit.
- L143 _private member_ `const FSynthKnobStyle* Style;` — Holds the style passed to the widget upon construction.
- L146 _private member_ `TAttribute<bool> LockedAttribute;` — Holds a flag indicating whether the slider is locked.
- L149 _private member_ `EOrientation Orientation;` — Holds the slider's orientation.
- L152 _private member_ `TAttribute<float> ValueAttribute;` — Holds the slider's current value.
- L155 _private member_ `TAttribute<float> StepSize;` — Holds the amount to adjust the value by when using a controller or keyboard
- L158 _private member_ `TAttribute<float> MouseSpeed;` — Holds the amount to adjust the value by when using a controller or keyboard
- L161 _private member_ `TAttribute<float> MouseFineTuneSpeed;` — Holds the amount to adjust the value by when using a controller or keyboard
- L163 _private member_ `TAttribute<FText> ParameterName;`
- L164 _private member_ `TAttribute<FText> ParameterUnits;`
- L165 _private member_ `TAttribute<FVector2D> ParameterRange;`
- L166 _private member_ `TAttribute<bool> ShowTooltip;`
- L169 _private member_ `FVector2D MouseDownPosition;` — The position of the mouse when it pushed down and started rotating the knob
- L172 _private member_ `float MouseDownValue;` — the value when the mouse was pushed down
- L175 _private member_ `int32 PixelDelta;` — the max pixels to go to min or max value (clamped to 0 or 1) in one drag period
- L178 _private member_ `FKey FineTuneKey;` — The key to use when fine tuning
- L182 _private member_ `bool bControllerInputCaptured;` — Holds a flag indicating whether a controller/keyboard is manipulating the slider's value. When true, navigation away from the widget is prevented until a new value has been accepted or canceled.
- L185 _private member_ `bool bIsFineTune;` — Whether or not we're in fine-tune mode
- L188 _private member_ `bool bIsMouseDown;` — Whether or not the mouse is down
- L191 _private member_ `bool bIsFocusable;` — When true, this slider will be keyboard focusable. Defaults to false.
- L195 _private member_ `TArray<FSlateBrush*> KnobImages;`
- L198 _private prototype_ `void ResetControllerState();` — Resets controller input state. Fires delegates.
- L201 _private member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L204 _private member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when the mouse is let up and a capture ends.
- L207 _private member_ `FSimpleDelegate OnControllerCaptureBegin;` — Holds a delegate that is executed when capture begins for controller or keyboard.
- L210 _private member_ `FSimpleDelegate OnControllerCaptureEnd;` — Holds a delegate that is executed when capture ends for controller or keyboard.
- L213 _private member_ `FOnFloatValueChanged OnValueChanged;` — Holds a delegate that is executed when the slider's value changed.

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/SSynthTooltip.h` (Public)


#### class `SSynthTooltip`  
`class SSynthTooltip : public SOverlay`  
_L11-31_
- inherits: `SOverlay`
- desc: Special tooltip that doesn't follow the mouse position Creates a simple window at the designated position.
- L14 _public function_ `SLATE_BEGIN_ARGS(SSynthTooltip)`
- L16 _public prototype_ `SLATE_SLOT_ARGUMENT(SOverlay::FOverlaySlot, Slots) SLATE_END_ARGS() ~SSynthTooltip();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetWindowContainerVisibility(bool bShowVisibility);`
- L22 _public prototype_ `void SetOverlayWindowPosition(FVector2D Position);`
- L23 _public prototype_ `void SetOverlayText(const FText& InText);`
- L26 _private member_ `TSharedPtr<SWindow> WindowContainer;`
- L27 _private member_ `TSharedPtr<STextBlock> TooltipText;`
- L28 _private member_ `FVector2D WindowPosition;`
- L29 _private member_ `bool bIsVisible;`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/Synth2DSlider.h` (Public)


#### class `USynth2DSlider`  
`class USynth2DSlider : public UWidget`  
_L25-150_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A simple widget that shows a sliding bar with a handle that allows you to control the value between 0..1. * No Children
- L31 _public member_ `float ValueX;` — `UPROPERTY(EditAnywhere, Category=Appearance, meta=( ClampMin="0", ClampMax="1", UIMin="0", UIMax="1"))`
- L34 _public member_ `float ValueY;` — `UPROPERTY(EditAnywhere, Category = Appearance, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))`
- L38 _public member_ `FGetFloat ValueXDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L42 _public member_ `FGetFloat ValueYDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L48 _public member_ `FSynth2DSliderStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=( DisplayName="Style" ))` — The progress bar style
- L52 _public member_ `FLinearColor SliderHandleColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)` — The color to draw the slider handle in.
- L56 _public member_ `bool IndentHandle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, AdvancedDisplay)` — Whether the slidable area should be indented to fit the handle.
- L60 _public member_ `bool Locked;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, AdvancedDisplay)` — Whether the handle is interactive or fixed.
- L64 _public member_ `float StepSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, meta=( ClampMin="0", ClampMax="1", UIMin="0", UIMax="1"))` — The amount to adjust the value by, when using a controller or keyboard
- L68 _public member_ `bool IsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")` — Should the slider be focusable?
- L74 _public member_ `FOnMouseCaptureBeginEventSynth2D OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is pressed and a capture begins.
- L78 _public member_ `FOnMouseCaptureEndEventSynth2D OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is released and a capture ends.
- L82 _public member_ `FOnControllerCaptureBeginEventSynth2D OnControllerCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture begins.
- L86 _public member_ `FOnControllerCaptureEndEventSynth2D OnControllerCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture ends.
- L90 _public member_ `FOnFloatValueChangedEventSynth2D OnValueChangedX;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Called when the value is changed by slider or typing.
- L94 _public member_ `FOnFloatValueChangedEventSynth2D OnValueChangedY;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when the value is changed by slider or typing.
- L98 _public prototype_ `FVector2D GetValue() const;` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Gets the current value of the slider.
- L102 _public prototype_ `void SetValue(FVector2D InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the current value of the slider.
- L106 _public prototype_ `void SetIndentHandle(bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets if the slidable area should be indented to fit the handle
- L110 _public prototype_ `void SetLocked(bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the handle to be interactive or fixed
- L114 _public prototype_ `void SetStepSize(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the amount to adjust the value by, when using a controller or keyboard
- L118 _public prototype_ `void SetSliderHandleColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Appearance")` — Sets the color of the handle bar
- L121 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L125 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L129 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L134 _protected member_ `TSharedPtr<SSynth2DSlider> MySlider;` — Native Slate Widget
- L137 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L140 _protected prototype_ `void HandleOnValueChangedX(float InValue);`
- L141 _protected prototype_ `void HandleOnValueChangedY(float InValue);`
- L142 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L143 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L144 _protected prototype_ `void HandleOnControllerCaptureBegin();`
- L145 _protected prototype_ `void HandleOnControllerCaptureEnd();`
- L148 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, ValueX);`
- L149 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, ValueY);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureBeginEventSynth2D);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureBeginEventSynth2D);`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureEndEventSynth2D);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseCaptureEndEventSynth2D);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureBeginEventSynth2D);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureBeginEventSynth2D);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureEndEventSynth2D);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerCaptureEndEventSynth2D);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatValueChangedEventSynth2D, float, Value);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatValueChangedEventSynth2D, float, Value);`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/Synth2DSliderStyle.h` (Public)


#### struct `FSynth2DSliderStyle`  
`struct FSynth2DSliderStyle : public FSlateWidgetStyle`  
_L17-54_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an SSynth2DSlider
- L21 _public prototype_ `FSynth2DSliderStyle();`
- L23 _public prototype_ `virtual ~FSynth2DSliderStyle();`
- L25 _public prototype_ `static void Initialize();`
- L29 _public member_ `FSlateBrush NormalThumbImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the 2D handle
- L33 _public member_ `FSlateBrush DisabledThumbImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the 2D handle
- L36 _public member_ `FSlateBrush NormalBarImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L39 _public member_ `FSlateBrush DisabledBarImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L42 _public member_ `FSlateBrush BackgroundImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L45 _public member_ `float BarThickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L47 _public member_ `static const FName TypeName;`
- L48 _public function_ `virtual const FName GetTypeName() const override`
- L50 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L52 _public prototype_ `static const FSynth2DSliderStyle& GetDefault();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/SynthKnob.h` (Public)


#### class `USynthKnob`  
`class USynthKnob : public UWidget`  
_L19-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A simple widget that shows a sliding bar with a handle that allows you to control the value between 0..1. * No Children
- L26 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, Category=Appearance, meta=( ClampMin="0", ClampMax="1", UIMin="0", UIMax="1"))` — The volume value to display.
- L30 _public member_ `float StepSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — The amount to adjust the value by, when using a controller or keyboard
- L34 _public member_ `float MouseSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — The speed of the mouse knob control
- L38 _public member_ `float MouseFineTuneSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — The speed of the mouse knob control when fine-tuning the knob
- L42 _public member_ `uint32 ShowTooltipInfo:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SynthTooltip)` — Enable tool tip window to show parameter information while knob turns
- L46 _public member_ `FText ParameterName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SynthTooltip)` — The name of the pararameter. Will show when knob turns.
- L50 _public member_ `FText ParameterUnits;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SynthTooltip)` — The parameter units (e.g. hz). Will append to synth tooltip info.
- L54 _public member_ `FGetFloat ValueDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L60 _public member_ `FSynthKnobStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=( DisplayName="Style" ))` — The synth knob style
- L64 _public member_ `bool Locked;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, AdvancedDisplay)` — Whether the handle is interactive or fixed.
- L68 _public member_ `bool IsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")` — Should the slider be focusable?
- L74 _public member_ `FOnMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is pressed and a capture begins.
- L78 _public member_ `FOnMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Invoked when the mouse is released and a capture ends.
- L82 _public member_ `FOnControllerCaptureBeginEvent OnControllerCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture begins.
- L86 _public member_ `FOnControllerCaptureEndEvent OnControllerCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Invoked when the controller capture ends.
- L90 _public member_ `FOnFloatValueChangedEvent OnValueChanged;` — `UPROPERTY(BlueprintAssignable, Category="Widget Event")` — Called when the value is changed by slider or typing.
- L94 _public prototype_ `float GetValue() const;` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Gets the current value of the slider.
- L98 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the current value of the slider.
- L102 _public prototype_ `void SetLocked(bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the handle to be interactive or fixed
- L106 _public prototype_ `void SetStepSize(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Behavior")` — Sets the amount to adjust the value by, when using a controller or keyboard
- L109 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L113 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L117 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L122 _protected member_ `TSharedPtr<SSynthKnob> MySynthKnob;` — Native Slate Widget
- L125 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L128 _protected prototype_ `void HandleOnValueChanged(float InValue);`
- L129 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L130 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L131 _protected prototype_ `void HandleOnControllerCaptureBegin();`
- L132 _protected prototype_ `void HandleOnControllerCaptureEnd();`
- L135 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, Value);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/SynthKnobStyle.h` (Public)


#### enum `ESynthKnobSize`  
`enum class ESynthKnobSize : uint8`  
_L14-19_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Medium`
- L17 _public enumerator_ `Large`
- L18 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FSynthKnobStyle`  
`struct FSynthKnobStyle : public FSlateWidgetStyle`  
_L25-77_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an SSynthKnob
- L29 _public prototype_ `FSynthKnobStyle();`
- L31 _public prototype_ `virtual ~FSynthKnobStyle();`
- L33 _public prototype_ `static void Initialize();`
- L35 _public member_ `static const FName TypeName;`
- L36 _public function_ `virtual const FName GetTypeName() const override`
- L38 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L40 _public prototype_ `static const FSynthKnobStyle& GetDefault();`
- L43 _public prototype_ `const FSlateBrush* GetBaseBrush() const;` — Returns the base brush to use
- L46 _public prototype_ `const FSlateBrush* GetOverlayBrush() const;` — Returns the overlay brush to represent the given value
- L50 _public member_ `FSlateBrush LargeKnob;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the large knob
- L54 _public member_ `FSlateBrush LargeKnobOverlay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the dot handle
- L58 _public member_ `FSlateBrush MediumKnob;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the medium large knob
- L62 _public member_ `FSlateBrush MediumKnobOverlay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the medium knob dot handle
- L66 _public member_ `float MinValueAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the medium knob dot handle
- L70 _public member_ `float MaxValueAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use for the medium knob dot handle
- L74 _public member_ `ESynthKnobSize KnobSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — The size of the knobs to use.
- L75 _public function_ `FSynthKnobStyle& SetKnobSize(const ESynthKnobSize& InKnobSize)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/SynthSlateStyle.h` (Public)


#### enum `ESynthSlateSizeType`  
`enum class ESynthSlateSizeType : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Small`
- L16 _public enumerator_ `Medium`
- L17 _public enumerator_ `Large`
- L18 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESynthSlateColorStyle`  
`enum class ESynthSlateColorStyle : uint8`  
_L22-27_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Light`
- L25 _public enumerator_ `Dark`
- L26 _public enumerator_ `Count UMETA(Hidden)`

#### struct `ISynthSlateResources`  
`struct ISynthSlateResources`  
_L29-45_
- L31 _public prototype_ `ISynthSlateResources();`
- L32 _public prototype_ `virtual ~ISynthSlateResources();`
- L34 _public prototype_ `virtual void LoadResources() = 0;`
- L35 _public prototype_ `virtual const TArray<TSharedPtr<FSlateDynamicImageBrush>>& GetImagesList(ESynthSlateSizeType SizeType, ESynthSlateColorStyle ColorStyle) const = 0;`
- L39 _protected prototype_ `int32 GetNumberForImageName(const FString& ImageName);`
- L41 _protected prototype_ `virtual void GetImagesAtPath(const FString& DirPath, TArray<TSharedPtr<FSlateDynamicImageBrush>>& OutImages, const float Size) = 0;`
- L42 _protected prototype_ `virtual float GetSize(ESynthSlateSizeType SizeType) const = 0;`
- L44 _protected member_ `bool bResourcesLoaded;`

#### struct `FSynthSlateStyleSet`  
`struct FSynthSlateStyleSet`  
_L48-57_
- L50 _public prototype_ `static void Initialize();`
- L51 _public prototype_ `static void Shutdown();`
- L53 _public prototype_ `static TSharedPtr< class FSlateStyleSet > Get();`
- L56 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

#### struct `FSynthSlateStyle`  
`struct FSynthSlateStyle : public FSlateWidgetStyle`  
_L63-92_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of synth UI elements in slate.
- L67 _public prototype_ `FSynthSlateStyle();`
- L69 _public prototype_ `virtual ~FSynthSlateStyle();`
- L71 _public member_ `static const FName TypeName;`
- L72 _public function_ `virtual const FName GetTypeName() const override`
- L74 _public prototype_ `static const FSynthSlateStyle& GetDefault();`
- L76 _public prototype_ `const FSlateBrush* GetBrushForValue(const float InValue) const;`
- L80 _public member_ `ESynthSlateSizeType SizeType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — The size of the knobs to use.
- L81 _public function_ `FSynthSlateStyle& SetSizeType(const ESynthSlateSizeType& InSizeType)`
- L85 _public member_ `ESynthSlateColorStyle ColorStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image to use when the slider bar is in its disabled state
- L86 _public function_ `FSynthSlateStyle& SetColorStyle(const ESynthSlateColorStyle& InColorStyle)`
- L89 _protected function_ `virtual ISynthSlateResources* CreateSynthSlateResources()`
- L91 _protected member_ `static ISynthSlateResources* SynthSlateResources;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SYNTHESIS_API`

### `Plugins/Runtime/Synthesis/Source/Synthesis/Public/UI/SynthTypes.h` (Public)
_(no declarations extracted)_
