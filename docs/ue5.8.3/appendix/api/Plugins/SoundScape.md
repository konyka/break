# Plugins / SoundScape

- module root: `Plugins/Runtime/Soundscape/Source/SoundScape`
- headers: 7; symbols: 263
- symbol kinds: class=13, delegate=3, enum=2, enumerator=5, function=2, member=147, prototype=81, struct=10
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, GameplayTags

### `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundScape.h` (Public)


#### class `USoundscapeBPFunctionLibrary`  
`class USoundscapeBPFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L19 _private prototype_ `static bool SpawnSoundscapeColor(UObject* WorldContextObject, class USoundscapeColor* SoundscapeColorIn, UActiveSoundscapeColor*& ActiveSoundscapeColor);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape", meta = (WorldContext = "WorldContextObject"))` — Spawns, but does not play, a new Soundscape Elemental Agent. Returns true if spawn was successful. "Play" can be called on the resulting Active Soundscape Color
- L23 _private prototype_ `static bool SpawnSoundscapePalette(UObject* WorldContextObject, class USoundscapePalette* SoundscapePaletteIn, UActiveSoundscapePalette*& SoundscapePaletteAgentsOut);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape", meta = (WorldContext = "WorldContextObject"))` — Spawns a new Soundscape Palette Agent. Returns true if spawn was successful.

### `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundScapeModule.h` (Public)


#### class `FSoundscapeModule`  
`class FSoundscapeModule: public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundscape, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundscape, Log, All);`

### `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundScapePalette.h` (Public)


#### struct `FSoundscapePaletteColor`  
`struct FSoundscapePaletteColor`  
_L16-39_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct storing Modulation State
- L22 _public member_ `TObjectPtr<USoundscapeColor> SoundscapeColor = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette")` — Soundscape Color to Play
- L26 _public member_ `float ColorVolume = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette", meta = (ClampMin = "0.0", ClampMax = "4.0", UIMin = "0.0", UIMax = "4.0", SliderExponent = "6.0"))` — Base Volume Scalar
- L30 _public member_ `float ColorPitch = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette", meta = (ClampMin = "0.2", ClampMax = "4.0", UIMin = "0.2", UIMax = "4.0", SliderExponent = "3.0"))` — Base Pitch Scalar
- L34 _public member_ `float ColorFadeIn = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Volume Fade In Time
- L38 _public member_ `float ColorFadeOut = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Volume Fade Out Time

#### class `USoundscapePalette`  
`class USoundscapePalette : public UObject`  
_L43-61_
- reflection: `UCLASS(BlueprintType, ClassGroup = Soundscape)`
- inherits: `UObject`
- desc: Class containing relevant data for a Soundscape Element
- L48 _public prototype_ `USoundscapePalette();`
- L51 _public member_ `FGameplayTagQuery SoundscapePalettePlaybackConditions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette")`
- L55 _public member_ `TArray<FSoundscapePaletteColor> Colors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette")` — Elements
- L58 _public prototype_ `virtual void PostLoad() override;`
- L59 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`

#### class `UActiveSoundscapePalette`  
`class UActiveSoundscapePalette : public UObject`  
_L65-85_
- reflection: `UCLASS(BlueprintType, ClassGroup = Soundscape)`
- inherits: `UObject`
- L70 _public prototype_ `void InitializeSettings(UObject* WorldContextObject, USoundscapePalette* SoundscapePalette);`
- L73 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")`
- L76 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")`
- L80 _private member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()`
- L83 _private member_ `TArray<TObjectPtr<UActiveSoundscapeColor>> ActiveSoundscapeColors;` — `UPROPERTY()`

### `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundscapeColor.h` (Public)


#### enum `ESoundscapeColorAltitudeClampMode`  
`enum class ESoundscapeColorAltitudeClampMode : uint8`  
_L22-29_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `Relative = 0 UMETA(DisplayName = "Relative Altitude")` — Altitude relative to the listener location
- L28 _public enumerator_ `Absolute = 1 UMETA(DisplayName = "Absolute Altitude")` — Altitude based on world coordinates

#### struct `FSoundscapeColorSpawnSettings`  
`struct FSoundscapeColorSpawnSettings`  
_L33-154_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct
- L39 _public member_ `bool bDelayFirstSpawn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior")` — Include an additional delay for the first spawn attempt between MinFirstSpawnDelay and MaxFirstSpawnDelay times.
- L43 _public member_ `float MinFirstSpawnDelay = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bDelayFirstSpawn"))` — Sets the minimum time delay before the first spawn
- L47 _public member_ `float MaxFirstSpawnDelay = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bDelayFirstSpawn"))` — Sets the maximum time delay before the first spawn
- L51 _public member_ `bool bContinuouslyRespawn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior")` — When true, color will continue to attempt to spawn sounds at an update frequency between the MinSpawnDelay and MaxSpawnDelay times. When false, it will only spawn once.
- L55 _public member_ `float MinSpawnDelay = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bContinuouslyRespawn"))` — Sets the minimum time between respawns
- L59 _public member_ `float MaxSpawnDelay = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bContinuouslyRespawn"))` — Sets the maximum time between respawns
- L63 _public member_ `int32 MaxNumberOfSpawnedElements = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "1", UIMin = "1"))` — Max number of concurrent Elements of this type playing back at once, will not Spawn New ones until current ones are Finished Playing
- L67 _public member_ `float MinSpawnDistance = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Sets Minimum Distance from Base for Playback of the Element
- L71 _public member_ `float MaxSpawnDistance = 3500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Sets the Maximum Distance from Base for Playback of the Element
- L75 _public member_ `bool bCullByMaxSpawnDistance = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior")` — Culls the voices by the Max Spawn Distance
- L79 _public member_ `float MinSpawnAngle = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"))` — The Minimum Azimuth based on the Base's Forward Vector in which to position Element Playback
- L83 _public member_ `float MaxSpawnAngle = 180.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"))` — The Maximum Azimuth based on the Base's Forward Vector in which to position Element Playback
- L87 _public member_ `bool bClampHeight = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior")` — When true, spawn locations will clamp the z axis according to the ClampMode rules between the MinSpawnHeightClamp and the MaxSpawnHeightClamp
- L91 _public member_ `ESoundscapeColorAltitudeClampMode ClampMode = ESoundscapeColorAltitudeClampMode::Relative;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (EditCondition = "bClampHeight"))` — What mode of altitude clamping to use, Relative clamps the z-axis about the location of the Listener, Absolute clamps the z-axis of the world coordinates
- L95 _public member_ `float MinSpawnHeightClamp = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (EditCondition = "bClampHeight"))` — After Element Playback position is determined, will clamp the Z-Axis to these ranges
- L99 _public member_ `float MaxSpawnHeightClamp = 5000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (EditCondition = "bClampHeight"))` — After Element Playback position is determined, will clamp the Z-Axis to these ranges
- L103 _public member_ `bool bRotateSoundSource = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior")` — When false, the sound rotation will be unmodified
- L107 _public member_ `float MinAzimuthalRotationAngle = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0", EditCondition = "bRotateSoundSource"))` — The Minimum azimuthal rotation in the world orientation for Element Playback
- L111 _public member_ `float MaxAzimuthalRotationAngle = 360.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0", EditCondition = "bRotateSoundSource"))` — The Maximum azimuthal rotation in the world orientation for Element Playback
- L115 _public member_ `float MinAltitudinalRotationAngle = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0", EditCondition = "bRotateSoundSource"))` — The Minimum Altitudinal rotation in the world orientation for Element Playback
- L119 _public member_ `float MaxAltitudinalRotationAngle = 360.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehavior", meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0", EditCondition = "bRotateSoundSource"))` — The Maximum Altitudinal rotation in the world orientation for Element Playback
- L124 _public member_ `bool bPositionByTrace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "SpawnBehavior")` — Position By Trace allows sounds to be repositioned from their spawn point to a new point in space based on the success of an async trace call, unsuccessful hits will result in the sound not spawning
- L128 _public member_ `FVector TraceVector = { 0.0f, 0.0f, -1.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "SpawnBehavior", meta = (EditCondition = "bPositionByTrace"))` — The Minimum normalized directional vector in world orientation for the Trace to fire (default to down, z = -1.0f)
- L132 _public member_ `float TraceDistance = 500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "SpawnBehavior", meta = (EditCondition = "bPositionByTrace"))` — Trace distance
- L140 _public member_ `bool bFilterByColorPointDensity = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "SpawnBehavior")` — Filter by Color Point Density allows designers to only allow this Color to spawn in spaces with a specified range of Color Points
- L144 _public member_ `FGameplayTag ColorPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "SpawnBehavior", meta = (EditCondition = "bFilterByColorPointDensity"))` — Color Point
- L148 _public member_ `int32 MinColorPointNumber = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "SpawnBehavior", meta = (EditCondition = "bFilterByColorPointDensity"))` — Minimum number of Color Point density required before spawn is successful
- L152 _public member_ `bool bIgnoreZAxisWhenCullingByMaxDistance = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "SpawnBehavior", meta = (EditCondition = "bCullByMaxSpawnDistance"))` — Culls the voices by the Max Spawn Distance

#### struct `FSoundscapeColorModulationSettings`  
`struct FSoundscapeColorModulationSettings`  
_L158-210_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct
- L164 _public member_ `bool bRandomizeVolume = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior")` — An additional randomization of Volume between VolumeMin and VolumeMax on top of previous volume adjustments
- L168 _public member_ `float VolumeMin = 0.95f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.0", ClampMax = "4.0", UIMin = "0.0", UIMax = "4.0", SliderExponent = "6.0", EditCondition = "bRandomizeVolume"))` — Minimum Volume Range for Step
- L172 _public member_ `float VolumeMax = 1.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.0", ClampMax = "4.0", UIMin = "0.0", UIMax = "4.0", SliderExponent = "6.0", EditCondition = "bRandomizeVolume"))` — Maximum Volume Range for Step
- L176 _public member_ `bool bRandomizePitch = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior")` — An additional randomization of Pitch between PitchMin and PitchMax on top of previous pitch adjustments
- L180 _public member_ `float PitchMin = 0.95f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.2", ClampMax = "4.0", UIMin = "0.2", UIMax = "4.0", SliderExponent = "3.0", EditCondition = "bRandomizePitch"))` — Minimum Pitch Range for Step
- L184 _public member_ `float PitchMax = 1.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.2", ClampMax = "4.0", UIMin = "0.2", UIMax = "4.0", SliderExponent = "3.0", EditCondition = "bRandomizePitch"))` — Maximum Pitch Range for Step
- L188 _public member_ `bool bFadeVolume = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior")` — Add Volume Fades to the Re-trigger Sound playback
- L192 _public member_ `float MinFadeInTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bFadeVolume"))` — This is the minimum Fade-In duration for re-triggered sounds
- L196 _public member_ `float MaxFadeInTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bFadeVolume"))` — This is the maximum Fade-In duration for re-triggered sounds
- L200 _public member_ `float MinFadeOutTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bFadeVolume"))` — This is the minimum Fade-Out duration for re-triggered sounds
- L204 _public member_ `float MaxFadeOutTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bFadeVolume"))` — This is the maximum Fade-Out duration for re-triggered sounds
- L208 _public member_ `bool bOnlyFadeInOnRetrigger = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModulationBehavior", meta = (EditCondition = "bFadeVolume"))` — Only Fade-In on retriggers

#### struct `FSoundscapeColorPlaybackSettings`  
`struct FSoundscapeColorPlaybackSettings`  
_L214-234_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct containing Sound Scape Element Control Data
- L220 _public member_ `bool bRandomizeStartingSeekTime = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlaybackBehavior")` — Upon starting playback, will randomly seek into the Sound if true
- L224 _public member_ `bool bLimitPlaybackDuration = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlaybackBehavior")` — Limit Ambient Bed's playback duration
- L228 _public member_ `float MinPlaybackDuration = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlaybackBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bLimitPlaybackDuration"))` — This is the minimum playback duration for this ambient bed (assuming a looping sound), ignored if bLimitPlaybackDuration is false
- L232 _public member_ `float MaxPlaybackDuration = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlaybackBehavior", meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "bLimitPlaybackDuration"))` — This is the maximum playback duration for this ambient bed (assuming a looping sound), ignored if bLimitPlaybackDuration is false

#### struct `FSoundscapeColorVoiceParams`  
`struct FSoundscapeColorVoiceParams`  
_L238-248_
- reflection: `USTRUCT()`
- desc: New SoundColorVoice Spawning Parameters
- L242 _public member_ `float Volume = 1.0f;`
- L243 _public member_ `float Pitch = 1.0f;`
- L244 _public member_ `float FadeInTime = 0.0f;`
- L245 _public member_ `float StartTime = 0.0f;`
- L246 _public member_ `FVector Location;`
- L247 _public member_ `FRotator Rotation;`

#### class `USoundscapeColor`  
`class USoundscapeColor : public UObject`  
_L254-299_
- reflection: `UCLASS(BlueprintType, ClassGroup = Soundscape)`
- inherits: `UObject`
- L259 _public prototype_ `USoundscapeColor();`
- L262 _public prototype_ `virtual void PostLoad() override;`
- L263 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L266 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L272 _public member_ `TObjectPtr<USoundBase> Sound;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Color")` — Sound to Play
- L276 _public member_ `float VolumeBase = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Color", meta = (ClampMin = "0.0", ClampMax = "4.0", UIMin = "0.0", UIMax = "4.0", SliderExponent = "6.0"))` — Base Volume Scalar
- L280 _public member_ `float PitchBase = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Color", meta = (ClampMin = "0.2", ClampMax = "4.0", UIMin = "0.2", UIMax = "4.0", SliderExponent = "3.0"))` — Base Pitch Scalar
- L284 _public member_ `FSoundscapeColorModulationSettings ModulationBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Color", meta = (ShowOnlyInnerProperties))` — Modulation behavior
- L288 _public member_ `FSoundscapeColorPlaybackSettings PlaybackBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Color", meta = (ShowOnlyInnerProperties))` — Playback behavior
- L292 _public member_ `FSoundscapeColorSpawnSettings SpawnBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Color", meta = (ShowOnlyInnerProperties))` — Playback behavior
- L297 _public member_ `FOnSoundscapeColorParameterChanges OnSoundscapeColorParameterChanges;` — `UPROPERTY()` — Delegate call for property changes

#### class `UActiveSoundscapeColorVoice`  
`class UActiveSoundscapeColorVoice : public UObject`  
_L302-323_
- reflection: `UCLASS()`
- inherits: `UObject`
- L308 _public prototype_ `void BeginDestroy();`
- L312 _public member_ `TObjectPtr<UAudioComponent> AudioComponent = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Soundscape|Color")`
- L315 _public member_ `FTimerHandle TimerHandle;` — `UPROPERTY(EditAnywhere, Category = "Soundscape|Color")`
- L318 _public member_ `bool bFree = false;` — `UPROPERTY(EditAnywhere, Category = "Soundscape|Color")`
- L322 _public prototype_ `void StopLimitedDurationVoice(float FadeOutTime);` — `UFUNCTION()` — Limited duration timer

#### class `UActiveSoundscapeColor`  
`class UActiveSoundscapeColor : public UObject`  
_L326-462_
- reflection: `UCLASS(BlueprintType, ClassGroup = Soundscape)`
- inherits: `UObject`
- L333 _public prototype_ `virtual void BeginDestroy() override;`
- L337 _public prototype_ `void SetParameterValues(const USoundscapeColor* SoundscapeColor);` — Initializes parameters based on SoundscapeColor settings
- L345 _public prototype_ `void BindToParameterChangeDelegate(USoundscapeColor* SoundscapeColor);` — Setup to bind to parameter change delegate
- L349 _public prototype_ `void OnSoundscapeColorParameterChange(const USoundscapeColor* SoundscapeColor);` — `UFUNCTION()` — Function bound to the Parameter change delegate
- L354 _public member_ `FScriptDelegate SoundscapeParameterChangeDelegate;` — Delegates for parameter change bindings
- L360 _private member_ `TObjectPtr<USoundBase> Sound;` — `UPROPERTY()` — Sound to Play
- L363 _private member_ `float VolumeBase = 1.0f;` — Base Volume Scalar
- L366 _private member_ `float PitchBase = 1.0f;` — Base Pitch Scalar
- L370 _private member_ `FSoundscapeColorModulationSettings ModulationBehavior;` — `UPROPERTY()` — Modulation behavior
- L374 _private member_ `FSoundscapeColorPlaybackSettings PlaybackBehavior;` — `UPROPERTY()` — Playback behavior
- L378 _private member_ `FSoundscapeColorSpawnSettings SpawnBehavior;` — `UPROPERTY()` — Playback behavior
- L382 _public member_ `float VolumeMod = 1.0f;` — Playback start values
- L383 _public member_ `float PitchMod = 1.0f;`
- L384 _public member_ `float FadeInMin = 1.0f;`
- L387 _public member_ `float FadeOutMin = 1.0f;` — Playback stop values
- L390 _public prototype_ `void PlayNative();` — Native play function
- L393 _public prototype_ `void StopNative();` — Native stop function
- L397 _public prototype_ `void Play(float ColorVolume = 1.0f, float ColorPitch = 1.0f, float ColorFadeInTime = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")` — Play Active Soundscape Color
- L401 _public prototype_ `void Stop(float ColorFadeOutTime = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")` — Stop Active Soundscape Color
- L405 _public prototype_ `bool IsPlaying();` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")` — Is playing
- L409 _public prototype_ `void UpdateSoundscapeColor();` — `UFUNCTION()` — Timer Update Call
- L412 _public member_ `FTimerHandle UpdateTimer;` — Timer delegate for amortized updates
- L417 _protected prototype_ `FTraceHandle SpawnSoundByTrace();` — Call an async trace
- L420 _protected prototype_ `void OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);` — Function called on completion of trace
- L422 _protected member_ `FTraceHandle TraceHandle;`
- L423 _protected member_ `FTraceDelegate TraceDelegate;`
- L427 _private prototype_ `void StartPlaying();` — Internal begin playing and bind FTimer Delegate set first time delays
- L430 _private prototype_ `void StopPlaying();` — Internal stop playing, tear down FTimer delegate, etc.
- L433 _private prototype_ `void Update();` — Internal update call
- L436 _private prototype_ `void CalculateSpawnParams();` — Calculate spawning parameters
- L439 _private prototype_ `bool EvaluateColorPointDensity();` — Evaluate color point density meets threshold, returns true if evaluation passes or if we are not filtering by color point density
- L442 _private prototype_ `void SpawnSoundscapeColorVoice();` — Spawn a Color Voice
- L445 _private member_ `FSoundscapeColorVoiceParams NewSoundParams;` — Last calculated color voice parameters
- L448 _private member_ `bool bTracing = false;` — Currently mid trace
- L452 _private member_ `TArray<TObjectPtr<UActiveSoundscapeColorVoice>> SoundscapeColorVoicePool;` — `UPROPERTY()` — Audio Component Pool
- L455 _private member_ `bool bIsPlaying = false;` — Is Playing Bool
- L458 _private member_ `bool bFirstSpawn = true;` — First Spawn
- L461 _private member_ `bool bVoiceInPoolFree = false;` — Voice in pool is free

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSoundscapeColorParameterChanges, const class USoundscapeColor*, SoundscapeColor);` — UObject delegate to broadcast parameter changes to ActiveSoundscapeColor instances.
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSoundscapeColorParameterChanges, const class USoundscapeColor*, SoundscapeColor);` — UObject delegate to broadcast parameter changes to ActiveSoundscapeColor instances.

### `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundscapeColorPoint.h` (Public)


#### struct `FSoundscapeColorPoint`  
`struct FSoundscapeColorPoint`  
_L11-20_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `FGameplayTag ColorPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|ColorPoint")`
- L19 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|ColorPoint")`

#### struct `FSoundscapeColorPointVectorArray`  
`struct FSoundscapeColorPointVectorArray`  
_L23-32_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `FGameplayTag ColorPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|ColorPoint")`
- L31 _public member_ `TArray<FVector> Locations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|ColorPoint")`

#### class `USoundscapeColorPointComponent`  
`class USoundscapeColorPointComponent : public UActorComponent`  
_L35-57_
- reflection: `UCLASS(ClassGroup=(Soundscape), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L41 _public prototype_ `USoundscapeColorPointComponent();` — Sets default values for this component's properties
- L45 _public member_ `FGameplayTag ColorPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|ColorPoint", meta = (Categories = "Soundscape"))` — This Component's Soundscape Pigment value
- L48 _public prototype_ `void GetInfo(FGameplayTag& ColorPoint, FVector& Location) const;` — Outputs information about this Active Color Point (Color Point value and Location of Parent Actor)
- L52 _protected prototype_ `virtual void BeginPlay() override;` — Called when the game starts
- L55 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;` — Called when the game ends

### `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundscapeSettings.h` (Public)


#### class `USoundscapeSettings`  
`class USoundscapeSettings : public UDeveloperSettings`  
_L14-68_
- reflection: `UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Soundscape"))`
- inherits: `UDeveloperSettings`
- L22 _public member_ `TSet<FSoftObjectPath> SoundscapePaletteCollection;` — `UPROPERTY(config, EditAnywhere, Category = "Soundscape", meta = (AllowedClasses = "/Script/Soundscape.SoundscapePalette"))` — Soundscape Palette Collection
- L25 _public member_ `bool bDebugDraw = false;` — `UPROPERTY(config, EditAnywhere, Category = "Soundscape")`
- L29 _public member_ `float LOD1ColorPointHashWidth = 500.0f;` — `UPROPERTY(config, EditAnywhere, Category = "ColorPointSystem", meta = (ClampMin = "1.0", UIMin = "1.0"))` — Hash Cell Width for LOD1
- L33 _public member_ `float LOD1ColorPointHashDistance = 5000.0f;` — `UPROPERTY(config, EditAnywhere, Category = "ColorPointSystem", meta = (ClampMin = "1.0", UIMin = "1.0"))` — Hash Cell LOD1 Max Distance
- L37 _public member_ `float LOD2ColorPointHashWidth = 2500.0f;` — `UPROPERTY(config, EditAnywhere, Category = "ColorPointSystem", meta = (ClampMin = "1.0", UIMin = "1.0"))` — Hash Cell Width for LOD2
- L41 _public member_ `float LOD2ColorPointHashDistance = 10000.0f;` — `UPROPERTY(config, EditAnywhere, Category = "ColorPointSystem", meta = (ClampMin = "1.0", UIMin = "1.0"))` — Hash Cell LOD2 Max Distance
- L45 _public member_ `float LOD3ColorPointHashWidth = 10000.0f;` — `UPROPERTY(config, EditAnywhere, Category = "ColorPointSystem", meta = (ClampMin = "1.0", UIMin = "1.0"))` — Hash Cell Width for LOD3
- L49 _public member_ `float ActiveColorPointHashWidth = 500.0f;` — `UPROPERTY(config, EditAnywhere, Category = "ColorPointSystem", meta = (ClampMin = "1.0", UIMin = "1.0"))` — Hash Cell Width for the Active Hash
- L53 _public member_ `float ActiveColorPointHashUpdateTimeSeconds = 1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "ColorPointSystem", meta = (ClampMin = "0.1", UIMin = "0.1"))` — Hash Cell Update Timing for the Active Hash
- L58 _public function_ `virtual FName GetCategoryName() const override` — Beginning of UDeveloperSettings Interface
- L60 _public function_ `virtual FText GetSectionText() const override`
- L66 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundscapeSubsystem.h` (Public)


#### struct `FSoundscapePaletteCollection`  
`struct FSoundscapePaletteCollection`  
_L20-27_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct
- L26 _public member_ `TSet<FSoftObjectPath> SoundscapePaletteCollection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|Palette", meta = (AllowedClasses = "/Script/Soundscape.SoundscapePalette"))` — Soundscape Palette Collection

#### struct `FSoundscapePaletteCollectionLoaded`  
`struct FSoundscapePaletteCollectionLoaded`  
_L31-38_
- reflection: `USTRUCT()`
- desc: Struct
- L37 _public member_ `TSet<TObjectPtr<USoundscapePalette>> SoundscapePaletteCollection;` — `UPROPERTY(EditAnywhere, Category = "Soundscape|Palette")` — Soundscape Palette Collection

#### struct `FSoundscapeColorPointCollection`  
`struct FSoundscapeColorPointCollection`  
_L42-49_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct
- L48 _public member_ `TArray<FSoundscapeColorPointVectorArray> ColorPointCollection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soundscape|ColorPoint")` — Soundscape Color Point Collection

#### class `USoundscapeColorPointHashCellDensity`  
`class USoundscapeColorPointHashCellDensity : public UObject`  
_L53-63_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class
- L61 _public member_ `TMap<uint64, int32> ColorPointHashCellDensity;` — `UPROPERTY(EditAnywhere, Category = "Soundscape|ColorPoint")` — Soundscape Color Point Density for a Hash Cell

#### class `USoundscapeColorPointHashMap`  
`class USoundscapeColorPointHashMap : public UObject`  
_L66-141_
- reflection: `UCLASS()`
- inherits: `UObject`
- L73 _public prototype_ `void InitializeHash(float HashCellSizeIn, FVector GridCenterIn);` — `UFUNCTION()` — Clears and initializes hash map, sizes grid to HashCellWidth in Uunits
- L77 _public prototype_ `void ClearHash();` — `UFUNCTION()` — Clears hash map
- L81 _public prototype_ `int32 NumColorPointsInCell(const FVector& Location, const FGameplayTag ColorPoint);` — `UFUNCTION()` — Returns the number of ColorPoints in a Cell containing the Location
- L85 _public prototype_ `bool AddColorPointToHash(const FVector& Location, const FGameplayTag ColorPoint);` — `UFUNCTION()` — Returns true if ColorPoint added to hash, false if failed (likely location is out of Hash Bounds)
- L89 _public prototype_ `void AddColorPointArrayToHash(const TArray<FVector>& Locations, const FGameplayTag ColorPoint);` — `UFUNCTION()` — Returns true if ColorPoint added to hash, false if failed (likely location is out of Hash Bounds)
- L93 _public prototype_ `uint64 CalculateHashIndex(const FVector& Location);` — `UFUNCTION()` — Calculates Hash Index
- L97 _public prototype_ `void SetGridCenterpoint(const FVector& Location);` — `UFUNCTION()` — Sets ceterpoint of grid to Location
- L99 _public prototype_ `TMap<FGameplayTag, int32> GetHashMapColorPointDensitySummary();`
- L103 _protected prototype_ `USoundscapeColorPointHashCellDensity* GetColorPointDensityMap(FGameplayTag ColorPoint);` — Returns ColorPointDensityMap from Hash Map given a Color Point
- L108 _private member_ `TMap<FGameplayTag, TObjectPtr<USoundscapeColorPointHashCellDensity>> ColorPointHashMap;` — `UPROPERTY()` — Color Point Hash Map
- L111 _private member_ `static const int32 MaxGridWidth = 2000000;` — Cubic Root of the Max Value of int64 rounded down to the nearest million
- L112 _private member_ `static const int32 HalfMaxGridWidth = 1000000;`
- L116 _private member_ `float HashCellSize = 500.0f;` — `UPROPERTY()` — Hash Cell Width
- L120 _private member_ `int32 GridWidth = 4000;` — `UPROPERTY()` — MaxGridWidth / Hash Cell Size
- L124 _private member_ `int64 NumCells = 64000000000;` — `UPROPERTY()` — Grid Width Cubed
- L128 _private member_ `float HashCellFactor = 0.002f;` — `UPROPERTY()` — Cell Size Inverted
- L132 _private member_ `FVector GridCenter;` — `UPROPERTY()` — Current Grid Centerpoint
- L136 _private member_ `FVector GridOriginOffset;` — `UPROPERTY()` — Grid Origin Offset
- L139 _public prototype_ `const FVector GetHashCellCenterpoint(FVector Location);`
- L140 _public prototype_ `const float GetHashCellWidth();`

#### enum `ESoundscapeLOD`  
`enum class ESoundscapeLOD : uint8`  
_L144-149_
- reflection: `UENUM()`
- L146 _public enumerator_ `LOD1 = 0 UMETA(DisplayName = "LOD 1")`
- L147 _public enumerator_ `LOD2 UMETA(DisplayName = "LOD 2")`
- L148 _public enumerator_ `LOD3 UMETA(DisplayName = "LOD 3")`

#### class `USoundscapeColorPointHashMapCollection`  
`class USoundscapeColorPointHashMapCollection : public UObject`  
_L152-199_
- reflection: `UCLASS()`
- inherits: `UObject`
- L158 _public prototype_ `void InitializeCollection();`
- L160 _public prototype_ `void AddColorPointArrayToHashMapCollection(const TArray<FVector>& Locations, const FGameplayTag ColorPoint);`
- L162 _public prototype_ `void ClearColorPointHashMapCollection();`
- L164 _public prototype_ `int32 GetColorPointHashMapCollectionDensity(const FVector Location, const FGameplayTag ColorPoint, const ESoundscapeLOD SoundscapeLOD);`
- L167 _public prototype_ `void CalculateTotalColorPointDensity(TMap<FGameplayTag, int32>& TotalHashMapColorPointDensity, ESoundscapeLOD SoundscapeLOD);`
- L173 _private member_ `TObjectPtr<USoundscapeColorPointHashMap> ColorPointHashMapLOD1;` — `UPROPERTY()` — Color Point Hash Maps
- L175 _private member_ `TObjectPtr<USoundscapeColorPointHashMap> ColorPointHashMapLOD2;` — `UPROPERTY()`
- L177 _private member_ `TObjectPtr<USoundscapeColorPointHashMap> ColorPointHashMapLOD3;` — `UPROPERTY()`
- L181 _private member_ `float LOD1ColorPointHashWidth = 500.0f;` — `UPROPERTY()` — Hash Cell Width for LOD1
- L185 _private member_ `float LOD1ColorPointHashDistance = 5000.0f;` — `UPROPERTY()` — Hash Cell LOD1 Max Distance
- L189 _private member_ `float LOD2ColorPointHashWidth = 2500.0f;` — `UPROPERTY()` — Hash Cell Width for LOD2
- L193 _private member_ `float LOD2ColorPointHashDistance = 10000.0f;` — `UPROPERTY()` — Hash Cell LOD2 Max Distance
- L197 _private member_ `float LOD3ColorPointHashWidth = 10000.0f;` — `UPROPERTY()` — Hash Cell Width for LOD3

#### class `USoundscapeSubsystem`  
`class USoundscapeSubsystem : public UGameInstanceSubsystem`  
_L205-349_
- reflection: `UCLASS()`
- inherits: `UGameInstanceSubsystem`
- L211 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L212 _public prototype_ `virtual void Deinitialize() override;`
- L213 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L221 _public prototype_ `void SetState(FGameplayTag SoundscapeState);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")`
- L224 _public prototype_ `void ClearState(FGameplayTag SoundscapeState);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")`
- L227 _public prototype_ `void RestartSoundscape();` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")`
- L230 _public prototype_ `bool AddPaletteCollection(FName PaletteCollectionName, FSoundscapePaletteCollection PaletteCollection);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")`
- L233 _public prototype_ `bool RemovePaletteCollection(FName PaletteCollectionName);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")`
- L235 _public member_ `bool bDebugMode = false;`
- L239 _private member_ `TSet<TObjectPtr<USoundscapePalette>> LoadedPaletteCollectionSet;` — `UPROPERTY()`
- L242 _private member_ `TMap<FName, FSoundscapePaletteCollection> UnloadedPaletteCollections;` — `UPROPERTY()`
- L244 _private member_ `FGameplayTagContainer SubsystemState;`
- L247 _private member_ `TMap<TObjectPtr<USoundscapePalette>, TObjectPtr<UActiveSoundscapePalette>> ActivePalettes;` — `UPROPERTY()`
- L250 _private prototype_ `bool LoadPaletteCollection(FName PaletteCollectionName);` — Start Asynchronous Loading
- L251 _private prototype_ `void CompleteAsyncLoading(FName PaletteCollectionName);`
- L253 _private member_ `TMap<FName, TSharedPtr<FStreamableHandle>> ActiveAssetLoadHandles;`
- L255 _private prototype_ `bool UnloadPaletteCollection(FName PaletteCollectionName);`
- L257 _private prototype_ `void UpdateState();`
- L261 _private member_ `Audio::FDeviceId AudioDeviceID;`
- L267 _public prototype_ `void AddColorPointCollection(FName ColorPointCollectionName, FSoundscapeColorPointCollection ColorPointCollection);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")` — Add a Color Point Collection to the Subsystem, returns true if successful
- L271 _public prototype_ `bool RemoveColorPointCollection(FName ColorPointCollectionName);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")` — Remove a Color Point Collection from the Subsystem, returns true if successful
- L275 _public prototype_ `int32 CheckColorPointDensity(FVector Location, FGameplayTag ColorPoint);` — `UFUNCTION(BlueprintCallable, Category = "Soundscape")` — Check Color Point Density for a Location Cell
- L278 _public prototype_ `void AddColorPointHashMapCollection(USoundscapeColorPointHashMapCollection* ColorPointHashMapCollection);` — Add Hash Map Collection
- L281 _public prototype_ `bool RemoveColorPointHashMapCollection(USoundscapeColorPointHashMapCollection* ColorPointHashMapCollection);` — Add Hash Map Collection
- L284 _public prototype_ `void DrawDebugCell(FVector Location, bool bSuccess);` — Draw Debug Cell
- L287 _public prototype_ `TPair<FVector, FVector> CalculateDebugCellDimensions(FVector Location, ESoundscapeLOD SoundscapeLOD);` — Calculate Debug Cell Dimensions
- L290 _public prototype_ `void AddActiveColorPoint(const USoundscapeColorPointComponent* SoundscapeColorPointComponent);` — Add Active Color Point
- L293 _public prototype_ `void RemoveActiveColorPoint(const USoundscapeColorPointComponent* SoundscapeColorPointComponent);` — Remove Active Color Point
- L298 _private member_ `TArray<TObjectPtr<USoundscapeColorPointHashMapCollection>> ColorPointHashMapCollections;` — `UPROPERTY(Transient)` — Stored Hash Map Collections
- L301 _private member_ `TMap<FName, FSoundscapeColorPointCollection> ColorPointCollections;` — Stored Color Point Collections
- L304 _private member_ `FSoundscapeColorPointCollection ActiveColorPointCollection;` — Active Color Point Collection
- L308 _private member_ `TObjectPtr<USoundscapeColorPointHashMap> ColorPointHashMapLOD1;` — `UPROPERTY()` — Color Point Hash Maps
- L310 _private member_ `TObjectPtr<USoundscapeColorPointHashMap> ColorPointHashMapLOD2;` — `UPROPERTY()`
- L312 _private member_ `TObjectPtr<USoundscapeColorPointHashMap> ColorPointHashMapLOD3;` — `UPROPERTY()`
- L315 _private member_ `TObjectPtr<USoundscapeColorPointHashMap> ActiveColorPointHashMap;` — `UPROPERTY()`
- L318 _private member_ `float LOD1ColorPointHashWidth = 500.0f;` — Hash Cell Width for LOD1
- L321 _private member_ `float LOD1ColorPointHashDistance = 5000.0f;` — Hash Cell LOD1 Max Distance
- L324 _private member_ `float LOD2ColorPointHashWidth = 2500.0f;` — Hash Cell Width for LOD2
- L327 _private member_ `float LOD2ColorPointHashDistance = 10000.0f;` — Hash Cell LOD2 Max Distance
- L330 _private member_ `float LOD3ColorPointHashWidth = 10000.0f;` — Hash Cell Width for LOD3
- L333 _private member_ `float ActiveColorPointHashWidth = 500.0f;` — Hash Cell Width for the Active Hash
- L336 _private member_ `float ActiveColorPointHashUpdateTimeSeconds = 1.0f;` — Hash Cell Update Timing for the Active Hash
- L339 _private prototype_ `void UpdateColorPointHashMap(USoundscapeColorPointHashMap& SoundscapeColorPointHashMap);` — Update Hash Map
- L342 _private prototype_ `void UpdateActiveColorPointHashMap();` — Update Active Hash Map
- L345 _private member_ `FTimerHandle ActiveColorPointUpdateTimer;` — Timer delegate for amortized updates
- L348 _private member_ `TArray<const USoundscapeColorPointComponent*> ActiveSoundscapeColorPointComponents;` — Active Color Point Components

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundscapeSubsystem, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundscapeSubsystem, Log, All);`
