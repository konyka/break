# Plugins / SubsonicEngine

- module root: `Plugins/Experimental/Subsonic/Source/SubsonicEngine`
- headers: 12; symbols: 253
- symbol kinds: class=9, enum=4, enumerator=12, function=3, macro=4, member=63, namespace=29, prototype=109, struct=17, typedef=3
- PrivateDependencyModuleNames: AudioExtensions, AudioMixer, MetasoundEngine, MetasoundFrontend, MetasoundGenerator, MetasoundGraphCore, PropertyBindingUtils, SignalProcessing
- PublicDependencyModuleNames: AudioMixerCore, Core, CoreUObject, Engine, GameplayTags, SubsonicCore

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Private/StandardActions/SubsonicAction_AudioComponent.h` (Private)


#### enum `UE::Subsonic::ESubsonicAudioComponentAccess`  
`enum class ESubsonicAudioComponentAccess : uint8`  
_L24-35_
- reflection: `UENUM()`
- L28 _public enumerator_ `Add` — Adds new component, releasing any existing component. Stops existing component if sound is not one-shot.
- L31 _public enumerator_ `FindOrAdd` — Finds existing component, or creates a new one.
- L34 _public enumerator_ `Find` — Ignore request and if component doesn't already exist.

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModify`  
`struct FSubsonicEventAction_AudioComponentModify : public Core::FSubsonicEventActionBase`  
_L38-67_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Modify Audio Component")`
- inherits: `Core::FSubsonicEventActionBase`
- L43 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModify() = default;`
- L45 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, const Core::FActionHandle& InHandle) const override;`
- L48 _public prototype_ `virtual FText GetDisplayInfo() const override;`
- L53 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Addressable name of audio component instance.
- L60 _public member_ `ESubsonicExecutionScope Scope = ESubsonicExecutionScope::Executor;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Scope of component accessor.  If set to executor, named AudioComponent is accessible only by pool of sibling event actions for a given executor instance. If set to global, accesses any named AudioComponent in the global pool.
- L63 _public member_ `ESubsonicAudioComponentAccess Access = ESubsonicAudioComponentAccess::FindOrAdd;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`
- L66 _public member_ `TArray<TInstancedStruct<FSubsonicEventAction_AudioComponentModifierBase>> Modifiers;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentPlay`  
`struct FSubsonicEventAction_AudioComponentPlay : public Core::FSubsonicEventActionBase`  
_L70-100_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Play Sound")`
- inherits: `Core::FSubsonicEventActionBase`
- L74 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentPlay() = default;`
- L77 _public prototype_ `virtual FText GetDisplayInfo() const override;`
- L80 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, const Core::FActionHandle& InHandle) const override;`
- L85 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Addressable name of audio component instance.
- L89 _public member_ `TObjectPtr<USoundBase> Sound;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Sound to play.
- L96 _public member_ `ESubsonicExecutionScope Scope = ESubsonicExecutionScope::Executor;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Scope of component accessor.  If set to executor, named AudioComponent is accessible only by pool of sibling event actions for a given executor instance. If set to global, accesses any named AudioComponent in the global pool.
- L99 _public member_ `ESubsonicAudioComponentAccess Access = ESubsonicAudioComponentAccess::FindOrAdd;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentStop`  
`struct FSubsonicEventAction_AudioComponentStop : public Core::FSubsonicEventActionBase`  
_L103-125_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Stop Sound")`
- inherits: `Core::FSubsonicEventActionBase`
- L107 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentStop() = default;`
- L109 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, const Core::FActionHandle& InHandle) const override;`
- L112 _public prototype_ `virtual FText GetDisplayInfo() const override;`
- L117 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Addressable name of component/sound instance.
- L124 _public member_ `ESubsonicExecutionScope Scope = ESubsonicExecutionScope::Executor;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Scope of component accessor.  If set to executor, named AudioComponent is accessible only by pool of sibling event actions for a given executor instance. If set to global, accesses any named AudioComponent in the global pool.

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifierBase`  
`struct FSubsonicEventAction_AudioComponentModifierBase`  
_L128-136_
- reflection: `USTRUCT(MinimalAPI, meta = (Abstract, Hidden))`
- L133 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifierBase() = default;`
- L135 _public function_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const`

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifier_ExecuteOnFinished`  
`struct FSubsonicEventAction_AudioComponentModifier_ExecuteOnFinished : public FSubsonicEventAction_AudioComponentModifierBase`  
_L140-156_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Execute On Finished")`
- inherits: `FSubsonicEventAction_AudioComponentModifierBase`
- desc: Executes event with the given name within the parent collection on completion
- L145 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifier_ExecuteOnFinished() = default;`
- L147 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const override;`
- L151 _public member_ `FGameplayTag Event;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Event in parent collection to execute.
- L155 _private member_ `mutable FDelegateHandle ActiveDelegate;` — Should really be tracked by subscriber to support cancelation, replacement, data-oriented execution ordering, const correctness, etc.

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifier_Play`  
`struct FSubsonicEventAction_AudioComponentModifier_Play : public FSubsonicEventAction_AudioComponentModifierBase`  
_L159-171_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Play")`
- inherits: `FSubsonicEventAction_AudioComponentModifierBase`
- L164 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifier_Play() = default;`
- L166 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const override;`
- L170 _public member_ `float StartTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Play StartTime Offset (plays immediately if 0.0)

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifier_SetAttenuation`  
`struct FSubsonicEventAction_AudioComponentModifier_SetAttenuation : public FSubsonicEventAction_AudioComponentModifierBase`  
_L174-185_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Set Attenuation")`
- inherits: `FSubsonicEventAction_AudioComponentModifierBase`
- L179 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifier_SetAttenuation() = default;`
- L181 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const override;`
- L184 _public member_ `TObjectPtr<USoundAttenuation> Attenuation;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifier_SetConcurrency`  
`struct FSubsonicEventAction_AudioComponentModifier_SetConcurrency : public FSubsonicEventAction_AudioComponentModifierBase`  
_L188-199_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Set Concurrency")`
- inherits: `FSubsonicEventAction_AudioComponentModifierBase`
- L193 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifier_SetConcurrency() = default;`
- L195 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const override;`
- L198 _public member_ `TSet<TObjectPtr<USoundConcurrency>> Concurrency;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifier_SetModulationRouting`  
`struct FSubsonicEventAction_AudioComponentModifier_SetModulationRouting: public FSubsonicEventAction_AudioComponentModifierBase`  
_L202-219_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Set Modulation Routing")`
- inherits: `FSubsonicEventAction_AudioComponentModifierBase`
- L207 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifier_SetModulationRouting() = default;`
- L209 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const override;`
- L212 _public member_ `TSet<TObjectPtr<USoundModulatorBase>> Modulators;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`
- L215 _public member_ `EModulationDestination Destination = EModulationDestination::Volume;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`
- L218 _public member_ `EModulationRouting RoutingMethod = EModulationRouting::Inherit;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")`

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifier_SetSound`  
`struct FSubsonicEventAction_AudioComponentModifier_SetSound : public FSubsonicEventAction_AudioComponentModifierBase`  
_L222-234_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Set Sound")`
- inherits: `FSubsonicEventAction_AudioComponentModifierBase`
- L227 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifier_SetSound() = default;`
- L229 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const override;`
- L233 _public member_ `TObjectPtr<USoundBase> Sound;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Sound to play.

#### struct `UE::Subsonic::FSubsonicEventAction_AudioComponentModifier_Stop`  
`struct FSubsonicEventAction_AudioComponentModifier_Stop : public FSubsonicEventAction_AudioComponentModifierBase`  
_L237-245_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Stop")`
- inherits: `FSubsonicEventAction_AudioComponentModifierBase`
- L242 _public prototype_ `virtual ~FSubsonicEventAction_AudioComponentModifier_Stop() = default;`
- L244 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, UAudioComponent& AudioComponent) const override;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Private/StandardActions/SubsonicAction_EventCore.h` (Private)


#### enum `UE::Subsonic::EEventResolutionRule`  
`enum class EEventResolutionRule : uint8`  
_L19-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `First`
- L22 _public enumerator_ `Last`
- L23 _public enumerator_ `Random`
- L24 _public enumerator_ `Index`

#### struct `UE::Subsonic::FSubsonicEventAction_DelayEvent`  
`struct FSubsonicEventAction_DelayEvent : public Core::FSubsonicEventActionBase`  
_L28-48_
- reflection: `USTRUCT(MinimalAPI, BlueprintType, DisplayName = "Delay Event")`
- inherits: `Core::FSubsonicEventActionBase`
- L33 _public prototype_ `virtual ~FSubsonicEventAction_DelayEvent() = default;`
- L35 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, const Core::FActionHandle& InHandle) const override;`
- L39 _public member_ `FName DelayName = "De` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")` — Identifier used to cancel or replace delay in progress.
- L43 _public member_ `FGameplayTag EventName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")` — Event to execute after the given delay.
- L47 _public member_ `float Delay = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")` — Executes the given event by the prescribed amount.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Subsonic` (scope `UE`)
- L12 _namespace_ `namespace Core` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Private/StandardEventSubscribers/AudioComponentEventSubscriber.h` (Private)


#### class `UE::Subsonic::USubsonicAudioComponentSubscriber`  
`class USubsonicAudioComponentSubscriber final : public USubsonicEventSubscriberBase`  
_L31-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USubsonicEventSubscriberBase`
- desc: Subsonic Subscriber managing AudioComponent instances, events, and related data.
- L37 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L38 _public prototype_ `virtual void Deinitialize() override;`
- L41 _public prototype_ `UE_INTERNAL virtual void OnExecutorRegistered(const Core::FSubsonicExecutor& InExecutor) override;`
- L42 _public prototype_ `UE_INTERNAL virtual void OnExecutorUnregistered(const Core::FSubsonicExecutor& InExecutor) override;`
- L44 _public prototype_ `UE_INTERNAL UAudioComponent* AddComponent(FName Name, bool bReleaseExisting = true);`
- L45 _public prototype_ `UE_INTERNAL UAudioComponent* AddComponent(const Core::FExecutorScopeKey& InKey, FName Name, bool bReleaseExisting = true);`
- L47 _public prototype_ `UE_INTERNAL UAudioComponent* FindComponent(FName Name);`
- L48 _public prototype_ `UE_INTERNAL UAudioComponent* FindComponent(const Core::FExecutorScopeKey& InKey, FName Name);`
- L50 _public prototype_ `UE_INTERNAL void RemoveComponent(FName Name);`
- L51 _public prototype_ `UE_INTERNAL void RemoveComponent(const Core::FExecutorScopeKey& InKey, FName Name);`
- L54 _private member_ `TSharedPtr<AudioComponentEventSubscriberPrivate::FSubscriberImpl> Impl;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SUBSONICENGINE_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Subsonic` (scope `UE`)
- L22 _namespace_ `namespace AudioComponentEventSubscriberPrivate` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Private/StandardEventSubscribers/SubsonicGenerator.h` (Private)


#### class `UE::Subsonic::FSubsonicGenerator`  
`class FSubsonicGenerator : public ISoundGenerator`  
_L25-124_
- inherits: `ISoundGenerator`
- desc: Wrapper ISoundGenerator that owns either a WaveGenerator or MetsoundGenerator inner generator. Applies DSP (volume, pitch shift, highpass, lowpass) after delegating audio generation to the inner generator. After initialization, these generators are owned by the audio render thread and should be communicated with only through SubsonicRelay.
- L29 _public prototype_ `explicit FSubsonicGenerator(TSharedRef<FWaveGenerator> InWave, float InSampleRate);` — Wave path: inner generator is an FWaveGenerator (pure wave player).
- L32 _public prototype_ `explicit FSubsonicGenerator(ISoundGeneratorPtr InMetaSoundGenerator, float InSampleRate);` — MetaSound path: inner generator is an FMetasoundGenerator (returned by UMetaSoundSource).
- L37 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 InNumSamples) override;`
- L38 _public prototype_ `virtual int32 GetNumChannels() const override;`
- L39 _public prototype_ `virtual bool IsFinished() const override;`
- L44 _public prototype_ `void ApplyParameters(const FSubsonicParameterStore& Store);` — Audio render thread: apply named parameters from the store. Built-in parameters are handled by dedicated DSP handlers, unless the MetasoundGenerator provides a matching input.
- L48 _public prototype_ `void SetSource(Audio::IAudioMixerGeneratorSource* InSource);` — Associate a GeneratorSource with this generator, so the generator can be in charge of source state (play, stop, pause, etc.)
- L51 _public prototype_ `void Play();` — Start playback via the associated GeneratorSource.
- L54 _public prototype_ `void Stop();` — Stop playback. If FadeOutTime > 0, begins a fade; otherwise calls Source->Stop() immediately.
- L58 _public prototype_ `Audio::IAudioMixerGeneratorSource* GetSource() const;` — Game thread: returns the bare source pointer. Null means the generator is done and the subscriber can safely destroy the source.
- L61 _private typedef_ `using FBuiltInParamHandler = void (FSubsonicGenerator::*)(float);`
- L62 _private prototype_ `static const TMap<FName, FBuiltInParamHandler>& GetBuiltInParams();`
- L65 _private prototype_ `static bool TryGetFloat(const FSubsonicParameterStore& Store, const FPropertyBagPropertyDesc& Desc, float& OutValue);` — Attempts to extract a float from a property bag descriptor (handles float and double types).
- L68 _private prototype_ `bool HasMetaSoundInput(FName Name) const;` — Returns true if the pinned MetaSound generator has an input with the given name.
- L71 _private prototype_ `void ForwardToMetaSound(Metasound::FMetasoundGenerator& MSGen, const FSubsonicParameterStore& Store, const FPropertyBagPropertyDesc& Desc);` — Forwards a non-float parameter to the pinned MetaSound generator.
- L74 _private prototype_ `void SetVolume(float dB);` — Built-in parameter handlers.
- L75 _private prototype_ `void SetPitchShift(float Semitones);`
- L76 _private prototype_ `void SetHighpassCutoff(float FreqHz);`
- L77 _private prototype_ `void SetLowpassCutoff(float FreqHz);`
- L78 _private prototype_ `void SetFadeOutTime(float Seconds);`
- L81 _private prototype_ `void InitDSP();` — Initializes DSP state (filters, resampler) after InnerGenerator is set.
- L83 _private member_ `ISoundGeneratorPtr InnerGenerator;`
- L86 _private member_ `TWeakPtr<Metasound::FMetasoundGenerator, ESPMode::ThreadSafe> MetaSoundGeneratorWeak;` — Non-null for MetaSound path only.
- L90 _private member_ `std::atomic<bool> bGraphReady{ false };` — True once the MetaSound graph has been built and its inputs are available. Set via AddGraphSetCallback; always true for wave generators.
- L93 _private member_ `FDelegateHandle GraphSetCallbackHandle;` — Handle for the graph-set callback so we can unregister in the destructor.
- L97 _private member_ `TSharedPtr<FSubsonicParameterStore> DeferredParams;` — Holds the most recent SetParameters payload when the MetaSound graph is not yet ready. Applied and cleared once bGraphReady becomes true. Last-writer-wins.
- L101 _private member_ `float VolumeLinear = 1.0f;` — Current volume as linear gain. Updated from the "Volume" parameter (interpreted as dB). 0 dB = 1.0 linear (unity gain). Render thread only.
- L104 _private member_ `float SampleRate = 0.0f;` — Cached sample rate from the audio device.
- L107 _private member_ `Audio::FBiquadFilter HighpassFilter;` — DSP processors applied in the signal chain after the inner generator.
- L108 _private member_ `Audio::FBiquadFilter LowpassFilter;`
- L111 _private member_ `TUniquePtr<Audio::FRuntimeResampler> Resampler;` — Pitch shifting via resampling.
- L112 _private member_ `TArray<float> ResampleInputBuffer;`
- L113 _private member_ `bool bPitchShiftActive = false;`
- L117 _private member_ `float FadeOutTimeSec = 0.0f;` — Fade-out envelope state. Render thread only. FadeGainDelta > 0 means a fade is in progress; FadeGain <= 0 means it has completed.
- L118 _private member_ `float FadeGain = 1.0f;`
- L119 _private member_ `float FadeGainDelta = 0.0f;`
- L123 _private member_ `Audio::IAudioMixerGeneratorSource* Source = nullptr;` — Non-owning pointer to the associated GeneratorSource. Set on the game thread at creation, nulled on the render thread when the generator is done.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Private/StandardEventSubscribers/SubsonicWaveGenerator.h` (Private)


#### class `UE::Subsonic::FWaveGenerator`  
`class FWaveGenerator : public ISoundGenerator`  
_L20-33_
- inherits: `ISoundGenerator`
- desc: A pure wave-file player. Volume scaling and relay communication are handled by the outer FSubsonicGenerator wrapper.
- L23 _public prototype_ `FWaveGenerator(TSharedRef<const FSoundWaveData> SoundWaveData, Audio::FMixerDevice* MixerDevice);`
- L27 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 InNumSamples) override;`
- L28 _public prototype_ `virtual int32 GetNumChannels() const override;`
- L29 _public prototype_ `virtual bool IsFinished() const override;`
- L32 _protected member_ `TUniquePtr<FSoundWaveProxyPlayer> Player;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Public/StandardActions/SubsonicAction_GeneratorSource.h` (Public)


#### struct `UE::Subsonic::FSubsonicEventAction_GeneratorSourcePlay`  
`struct FSubsonicEventAction_GeneratorSourcePlay : public Core::FSubsonicEventActionBase`  
_L15-46_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Play Sound (GeneratorSource)")`
- inherits: `Core::FSubsonicEventActionBase`
- L19 _public prototype_ `virtual ~FSubsonicEventAction_GeneratorSourcePlay() = default;`
- L21 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, const Core::FActionHandle& InHandle) const override;`
- L24 _public prototype_ `virtual FText GetDisplayInfo() const override;`
- L30 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Addressable name of Generator source instance.
- L34 _public member_ `TObjectPtr<USoundWave> Sound;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Sound to play.
- L41 _public member_ `ESubsonicExecutionScope Scope = ESubsonicExecutionScope::Executor;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Scope of source accessor.  If set to executor, named source is accessible only by pool of sibling event actions for a given executor instance. If set to global, accesses any named source in the global pool.
- L45 _public member_ `FSubsonicParameterStore Parameters;` — `UPROPERTY(EditAnywhere, Category = "Parameters")` — Authored parameters applied to the generator at play time (lowest priority layer).

#### struct `UE::Subsonic::FSubsonicEventAction_GeneratorSourceStop`  
`struct FSubsonicEventAction_GeneratorSourceStop : public Core::FSubsonicEventActionBase`  
_L49-72_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "Stop Sound (GeneratorSource)")`
- inherits: `Core::FSubsonicEventActionBase`
- L53 _public prototype_ `virtual ~FSubsonicEventAction_GeneratorSourceStop() = default;`
- L55 _public prototype_ `virtual void Execute(const Core::FSubsonicExecutor& InExecutor, const Core::FActionHandle& InHandle) const override;`
- L58 _public prototype_ `virtual FText GetDisplayInfo() const override;`
- L64 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Addressable name of source instance.
- L71 _public member_ `ESubsonicExecutionScope Scope = ESubsonicExecutionScope::Executor;` — `UPROPERTY(EditAnywhere, Category = "Subsonic")` — Scope of source accessor.  If set to executor, named source is accessible only by pool of sibling event actions for a given executor instance. If set to global, accesses any named source in the global pool.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Public/StandardEventSubscribers/SubsonicEventSubscriberBase.h` (Public)


#### class `UE::Subsonic::USubsonicEventSubscriberBase`  
`class USubsonicEventSubscriberBase : public UAudioEngineSubsystem, public Core::ISubsonicEventSubscriberInterface`  
_L18-25_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAudioEngineSubsystem,Core::ISubsonicEventSubscriberInterface`
- L23 _public prototype_ `void Initialize(FSubsystemCollectionBase& Collection);`
- L24 _public prototype_ `void Deinitialize();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SUBSONICENGINE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Public/StandardEventSubscribers/SubsonicGeneratorSourceSubscriber.h` (Public)


#### struct `UE::Subsonic::FReleasedSource`  
`struct FReleasedSource`  
_L23-27_
- desc: A source that is no longer addressable from actions but still playing. Paired with its generator so ClearStaleSounds can check completion.
- L25 _public member_ `TUniquePtr<Audio::IAudioMixerGeneratorSource> Source;`
- L26 _public member_ `TSharedPtr<FSubsonicGenerator> Generator;`

#### struct `UE::Subsonic::FInstanceSources`  
`struct FInstanceSources`  
_L29-47_
- L32 _public member_ `TUniquePtr<Audio::IAudioMixerGeneratorSource> ActiveSource;` — Currently addressable generator source via handle
- L35 _public member_ `TArray<FReleasedSource> ReleasedSources;` — Sources no longer addressable from actions but actively playing.
- L39 _public member_ `TSharedPtr<FSubsonicGenerator> Generator;` — The active generator, shared with the relay command queue so that SetParameters commands can target it directly on the render thread.
- L41 _public member_ `FSubsonicParameterStore AuthoredParams;` — from action definition (lowest priority)
- L42 _public member_ `FSubsonicParameterStore RuntimeParams;` — from post-playback SetParameters (highest priority)
- L46 _public prototype_ `void ApplyParameters(FSubsonicRelay& Relay);` — Merges all three layers (authored < trigger < runtime) and enqueues a SetParameters command into the relay's global command queue.

#### class `UE::Subsonic::USubsonicGeneratorSourceSubscriber`  
`class USubsonicGeneratorSourceSubscriber final : public USubsonicEventSubscriberBase, public FTickableGameObject`  
_L53-95_
- reflection: `UCLASS()`
- inherits: `USubsonicEventSubscriberBase,FTickableGameObject`
- desc: Interface to GeneratorSource playback Subsonic implementation.
- L58 _public typedef_ `using FExecutorScopeKey = Core::FExecutorScopeKey;`
- L59 _public typedef_ `using FCollectionHandle = Core::FCollectionHandle;`
- L61 _public prototype_ `USubsonicGeneratorSourceSubscriber();`
- L64 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L65 _public prototype_ `virtual void Deinitialize() override;`
- L68 _public prototype_ `virtual void OnCollectionRegistered(const FCollectionHandle& InEvent) override;`
- L69 _public prototype_ `virtual void OnCollectionUnregistered(const FCollectionHandle& InEvent) override;`
- L71 _public prototype_ `virtual void OnExecutorRegistered(const Core::FSubsonicExecutor& InExecutor) override;`
- L72 _public prototype_ `virtual void OnExecutorUnregistered(const Core::FSubsonicExecutor& InExecutor) override;`
- L74 _public prototype_ `void PlaySound(FName Name, USoundWave& Sound, const FSubsonicParameterStore& Params, bool bReleaseExisting = true);`
- L75 _public prototype_ `void PlaySound(const FExecutorScopeKey& InKey, FName Name, USoundWave& Sound, const FSubsonicParameterStore& Params, bool bReleaseExisting = true);`
- L77 _public prototype_ `void StopSound(FName Name);`
- L78 _public prototype_ `void StopSound(const FExecutorScopeKey& InKey, FName Name);`
- L80 _public prototype_ `void SetParameters(FName SourceName, const FSubsonicParameterStore& Params);`
- L81 _public prototype_ `void SetParameters(const FExecutorScopeKey& InKey, FName SourceName, const FSubsonicParameterStore& Params);`
- L83 _public prototype_ `void SetAuthoredParameters(FName SourceName, FSubsonicParameterStore Params);`
- L84 _public prototype_ `void SetAuthoredParameters(const FExecutorScopeKey& InKey, FName SourceName, FSubsonicParameterStore Params);`
- L87 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject interface
- L88 _public function_ `virtual bool IsTickableInEditor() const override`
- L89 _public prototype_ `virtual TStatId GetStatId() const override;`
- L92 _private member_ `TSharedRef<FSubsonicRelay> Relay;`
- L94 _private member_ `Core::TSubscriberDataStore<FInstanceSources> SourcesDataStore;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Public/StandardEventSubscribers/SubsonicRelay.h` (Public)


#### struct `UE::Subsonic::FRelayCommand`  
`struct FRelayCommand`  
_L18-25_
- desc: Typed command for the per-device command queue on FSubsonicRelay. Commands are expected to be added on the game thread but can be safely added from other threads. All commands in one game tick are pushed to the audio render thread in a single batch.
- L22 _public member_ `EType Type = EType::SetParameters;`
- L23 _public member_ `TSharedPtr<FSubsonicParameterStore> Params;` — SetParameters only
- L24 _public member_ `TSharedPtr<FSubsonicGenerator> Target;` — all types

#### enum `UE::Subsonic::FRelayCommand::EType`  
`enum class EType : uint8`  
_L20-20_
- L20 _public enumerator_ `enum class EType : uint8 { SetParameters, Play, Stop }; EType Type = EType::SetParameters; TSharedPtr<FSubsonicParameterStore> Params; TSharedPtr<FSubsonicGenerator> Target;`
- L20 _public enumerator_ `enum class EType : uint8 { SetParameters, Play, Stop }; EType Type = EType::SetParameters; TSharedPtr<FSubsonicParameterStore> Params; TSharedPtr<FSubsonicGenerator> Target;`
- L20 _public enumerator_ `enum class EType : uint8 { SetParameters, Play, Stop }; EType Type = EType::SetParameters; TSharedPtr<FSubsonicParameterStore> Params; TSharedPtr<FSubsonicGenerator> Target;`

#### class `UE::Subsonic::FSubsonicRelay`  
`class FSubsonicRelay`  
_L28-41_
- desc: Per-device object responsible for communicating state changes to the audio render thread.
- L32 _public prototype_ `void EnqueueCommand(FRelayCommand&& Cmd);` — Append a command to the pending queue (lock-protected).
- L36 _public prototype_ `void Tick(Audio::FMixerDevice& MixerDevice);` — Game thread (called from subscriber Tick): flush pending commands into a single AudioRenderThreadCommand lambda on the mixer device.
- L39 _private member_ `FCriticalSection CommandLock;`
- L40 _private member_ `TArray<FRelayCommand> PendingCommands;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Public/SubsonicDeviceUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Subsonic` (scope `UE`)
- L13 _function_ `template <typename SubsystemType> SubsystemType* FindDeviceSubsystem(const Core::FExecutorScopeKey& InKey)` (scope `UE::Subsonic`) — Utility to find an audio device subsystem from an executor scope key. Free function here in SubsonicEngine to keep SubsonicCore free of AudioDevice dependencies.

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Public/SubsonicEventCollectionObjects.h` (Public)


#### class `UE::Subsonic::USubsonicEventCollection`  
`class USubsonicEventCollection final : public UObject`  
_L16-47_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L21 _public prototype_ `const Core::FSubsonicEventCollectionDefinition& GetDefinition() const;`
- L24 _public prototype_ `static FName GetDefinitionPropertyName();`
- L27 _public prototype_ `Core::FCollectionHandle GetHandle() const;`
- L30 _public prototype_ `UE_INTERNAL Core::FSubsonicEventCollectionDefinition& GetMutableDefinition();`
- L33 _public prototype_ `void SetDefinition(Core::FSubsonicEventCollectionDefinition&& Definition);`
- L37 _private member_ `Core::FSubsonicEventCollectionDefinition CollectionDefinition;` — `UPROPERTY(EditAnywhere, Category = "Subsonic", meta = (ShowOnlyInnerProperties))`
- L39 _private prototype_ `virtual void PostInitProperties() override;`
- L40 _private prototype_ `virtual void PostLoad() override;`
- L41 _private prototype_ `virtual void BeginDestroy() override;`
- L44 _private prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L45 _private prototype_ `virtual void PostEditUndo() override;`

#### enum `UE::Subsonic::ESubsonicExecutionResult`  
`enum class ESubsonicExecutionResult : uint8`  
_L50-54_
- reflection: `UENUM(BlueprintType, meta = (DisplayName = "Execution Result"))`
- L52 _public enumerator_ `Succeeded`
- L53 _public enumerator_ `Failed`

#### class `UE::Subsonic::USubsonicEventCollectionExecutor`  
`class USubsonicEventCollectionExecutor final : public UObject`  
_L58-96_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Executor handle for a Subsonic Event Collection.
- L63 _public prototype_ `virtual void BeginDestroy() override;`
- L66 _public prototype_ `static USubsonicEventCollectionExecutor* Create(UObject& Parent, FName Name, const USubsonicEventCollection& InCollection, Audio::FDeviceId DeviceId);` — Creates a transient executor that is bound to the given collection.
- L72 _public prototype_ `void ExecuteEvent(FGameplayTag EventTag, ESubsonicExecutionResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Subsonic|Collection|Events", meta = (ExpandEnumAsExecs = "OutResult"))` — Executes an event with the given gameplay tag if it exists. Sets OutResult to Succeeded if event was found and executed, Failed if not (enum provided as execution expansion support).
- L75 _public prototype_ `const USubsonicEventCollection* GetCollection() const;` — Returns collection executor is bound to.
- L78 _public prototype_ `const USubsonicEventCollection& GetCollectionChecked() const;` — Returns collection executor is bound to and asserts if no collection is set.
- L81 _public prototype_ `const Core::FSubsonicExecutor& GetExecutor() const;` — Returns underlying executor UObject wraps.
- L84 _public prototype_ `bool IsValid() const;` — Returns whether this executor is valid (has a valid ID and is bound to an event collection)
- L89 _public prototype_ `void Unregister();` — Unregisters the underlying executor implementation, clearing any state pertaining to the given executor managed by subscribers and releasing association with the provided collection when created.
- L93 _private member_ `TObjectPtr<const USubsonicEventCollection> Collection;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Subsonic", meta = (AllowPrivateAccess))`
- L95 _private member_ `TSharedPtr<Core::FSubsonicExecutor> Executor;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SUBSONICENGINE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEngine/Public/SubsonicSubsystem.h` (Public)


#### class `UE::Subsonic::USubsonicSubsystem`  
`class USubsonicSubsystem final : public UEngineSubsystem`  
_L19-31_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UEngineSubsystem`
- desc: Interface to the Subsonic plugin.
- L25 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L26 _public prototype_ `virtual void Deinitialize() override;`
- L30 _public prototype_ `UPARAM(DisplayName = "Executor") USubsonicEventCollectionExecutor* CreateExecutorBP(UObject* WorldContextObject, FName Name, const USubsonicEventCollection* Coll` — `UFUNCTION(BlueprintCallable, Category = "Subsonic", meta = (DisplayName = "Create Executor", WorldContext = "WorldContextObject"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SUBSONICENGINE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Subsonic` (scope `UE`)
