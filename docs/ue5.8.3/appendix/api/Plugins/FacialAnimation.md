# Plugins / FacialAnimation

- module root: `Plugins/Editor/FacialAnimation/Source/FacialAnimation`
- headers: 2; symbols: 29
- symbol kinds: class=2, macro=1, member=12, prototype=14
- PrivateDependencyModuleNames: AudioExtensions, AudioMixer, Core, CoreUObject, Engine, InputCore

### `Plugins/Editor/FacialAnimation/Source/FacialAnimation/Private/FacialAnimationModule.h` (Private)


#### class `FFacialAnimationModule`  
`class FFacialAnimationModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/FacialAnimation/Source/FacialAnimation/Public/AudioCurveSourceComponent.h` (Public)


#### class `UAudioCurveSourceComponent`  
`class UAudioCurveSourceComponent : public UAudioComponent, public ICurveSourceInterface`  
_L19-90_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Audio, Experimental, meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioComponent,ICurveSourceInterface`
- desc: An audio component that also provides curves to drive animation
- L24 _public prototype_ `UAudioCurveSourceComponent();`
- L31 _public member_ `FName CurveSourceBindingName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Curves)` — Get the name that this curve source can be bound to by. Clients of this curve source will use this name to identify this source.
- L35 _public member_ `float CurveSyncOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Curves)` — Offset in time applied to audio position when evaluating curves
- L39 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;` — UActorComponent interface
- L42 _public prototype_ `virtual void FadeIn(float FadeInDuration, float FadeVolumeLevel = 1.0f, float StartTime = 0.0f, const EAudioFaderCurve FadeType = EAudioFaderCurve::Linear) override;` — UAudioComponent interface
- L43 _public prototype_ `virtual void FadeOut(float FadeOutDuration, float FadeVolumeLevel, const EAudioFaderCurve FadeType = EAudioFaderCurve::Linear) override;`
- L44 _public prototype_ `virtual void Play(float StartTime = 0.0f) override;`
- L45 _public prototype_ `virtual void Stop() override;`
- L46 _public prototype_ `virtual bool IsPlaying() const override;`
- L49 _public prototype_ `virtual FName GetBindingName_Implementation() const override;` — ICurveSourceInterface interface
- L50 _public prototype_ `virtual float GetCurveValue_Implementation(FName CurveName) const override;`
- L51 _public prototype_ `virtual void GetCurves_Implementation(TArray<FNamedCurveValue>& OutCurve) const override;`
- L55 _private prototype_ `void CacheCurveData();` — Cache the curve parameters when playing back
- L58 _private prototype_ `void HandlePlaybackPercent(const UAudioComponent* InComponent, const USoundWave* InSoundWave, const float InPlaybackPercentage);` — Internal handling of playback percentage
- L62 _private member_ `float CachedCurveEvalTime;` — Cached evaluation time from the last callback of OnPlaybackPercent
- L65 _private member_ `TWeakObjectPtr<class UCurveTable> CachedCurveTable;` — Cached curve table from the last callback of OnPlaybackPercent
- L68 _private member_ `float CachedSyncPreRoll;` — Preroll time we use to sync to curves
- L71 _private member_ `float CachedStartTime;` — Cached param for PlayInternal
- L74 _private member_ `float CachedFadeInDuration;` — Cached param for PlayInternal
- L77 _private member_ `float CachedFadeVolumeLevel;` — Cached param for PlayInternal
- L80 _private member_ `float Delay;` — Delay timer
- L83 _private member_ `float CachedDuration;` — Cached duration
- L86 _private member_ `bool bCachedLooping;` — Cache looping flag
- L89 _private member_ `EAudioFaderCurve CachedFadeType;` — Cached param for PlayInternal

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API FACIALANIMATION_API`
