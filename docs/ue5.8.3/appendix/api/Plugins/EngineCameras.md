# Plugins / EngineCameras

- module root: `Plugins/Cameras/EngineCameras/Source/EngineCameras`
- headers: 13; symbols: 252
- symbol kinds: class=13, delegate=1, enum=5, enumerator=18, function=14, macro=8, member=105, prototype=80, struct=8
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, Engine, HeadMountedDisplay, MovieScene, MovieSceneTracks, TemplateSequence, TraceLog

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Legacy/Camera/CameraShake.h` (Other)
_(no declarations extracted)_

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Legacy/CameraAnimationCameraModifier.h` (Other)
_(no declarations extracted)_

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Legacy/LegacyCameraShake.h` (Other)
_(no declarations extracted)_

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Animations/CameraAnimationCameraModifier.h` (Public)


#### enum `ECameraAnimationPlaySpace`  
`enum class ECameraAnimationPlaySpace : uint8`  
_L19-27_
- reflection: `UENUM()`
- L22 _public enumerator_ `CameraLocal` — This anim is applied in camera space.
- L24 _public enumerator_ `World` — This anim is applied in world space.
- L26 _public enumerator_ `UserDefined` — This anim is applied in a user-specified space (defined by UserPlaySpaceMatrix).

#### enum `ECameraAnimationEasingType`  
`enum class ECameraAnimationEasingType : uint8`  
_L30-40_
- reflection: `UENUM()`
- L32 _public enumerator_ `Linear`
- L33 _public enumerator_ `Sinusoidal`
- L34 _public enumerator_ `Quadratic`
- L35 _public enumerator_ `Cubic`
- L36 _public enumerator_ `Quartic`
- L37 _public enumerator_ `Quintic`
- L38 _public enumerator_ `Exponential`
- L39 _public enumerator_ `Circular`

#### struct `FCameraAnimationParams`  
`struct FCameraAnimationParams`  
_L44-88_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameter struct for adding new camera animations to UCameraAnimationCameraModifier
- L50 _public member_ `float PlayRate = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Time scale for playing the new camera animation
- L53 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Global scale to use for the new camera animation
- L57 _public member_ `ECameraAnimationEasingType EaseInType = ECameraAnimationEasingType::Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Ease-in function type
- L60 _public member_ `float EaseInDuration = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Ease-in duration in seconds
- L64 _public member_ `ECameraAnimationEasingType EaseOutType = ECameraAnimationEasingType::Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Ease-out function type
- L67 _public member_ `float EaseOutDuration = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Ease-out duration in seconds
- L71 _public member_ `bool bLoop = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Whether the camera animation should loop
- L74 _public member_ `int32 StartOffset = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Offset, in frames, into the animation to start at
- L77 _public member_ `bool bRandomStartTime = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Whether the camera animation should have a random start time
- L80 _public member_ `float DurationOverride = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — Override the duration of the animation with a new duration (including blends)
- L84 _public member_ `ECameraAnimationPlaySpace PlaySpace = ECameraAnimationPlaySpace::CameraLocal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — The transform space to use for the new camera shake
- L87 _public member_ `FRotator UserPlaySpaceRot = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Animation")` — User space to use when PlaySpace is UserDefined

#### struct `FCameraAnimationHandle`  
`struct FCameraAnimationHandle`  
_L92-128_
- reflection: `USTRUCT(BlueprintType)`
- desc: A handle to a camera animation running in UCameraAnimationCameraModifier
- L96 _public member_ `static FCameraAnimationHandle Invalid;`
- L98 _public function_ `FCameraAnimationHandle() : InstanceID(MAX_uint16), InstanceSerial(0)`
- L99 _public function_ `FCameraAnimationHandle(uint16 InInstanceID, uint16 InInstanceSerial) : InstanceID(InInstanceID), InstanceSerial(InInstanceSerial)`
- L101 _public function_ `bool IsValid() const`
- L124 _private member_ `uint16 InstanceID;`
- L125 _private member_ `uint16 InstanceSerial;`

#### struct `FActiveCameraAnimationInfo`  
`struct FActiveCameraAnimationInfo`  
_L134-181_
- reflection: `USTRUCT()`
- desc: Information about an active camera animation inside UCameraAnimationCameraModifier.
- L138 _public prototype_ `FActiveCameraAnimationInfo();`
- L141 _public prototype_ `bool IsValid() const;` — Whether this is a valid, ongoing camera animation
- L144 _public prototype_ `bool HasValidPlayer() const;` — Whether this camera animation's player is valid
- L148 _public member_ `TObjectPtr<UCameraAnimationSequence> Sequence;` — `UPROPERTY()` — The sequence to use for the animation.
- L152 _public member_ `FCameraAnimationParams Params;` — `UPROPERTY()` — The parameters for playing the animation.
- L156 _public member_ `FCameraAnimationHandle Handle;` — `UPROPERTY()` — A reference handle for use with UCameraAnimationCameraModifier.
- L160 _public member_ `TObjectPtr<UCameraAnimationSequencePlayer> Player;` — `UPROPERTY(Transient)` — The player for playing the animation.
- L164 _public member_ `TObjectPtr<UCameraAnimationSequenceCameraStandIn> CameraStandIn;` — `UPROPERTY(Transient)` — Standin for the camera actor and components
- L168 _public member_ `float EaseInCurrentTime;` — `UPROPERTY()` — Current time into easing in
- L172 _public member_ `float EaseOutCurrentTime;` — `UPROPERTY()` — Current time into easing out
- L176 _public member_ `bool bIsEasingIn;` — `UPROPERTY()` — Whether easing in is ongoing
- L180 _public member_ `bool bIsEasingOut;` — `UPROPERTY()` — Whether easing out is ongoing

#### class `UCameraAnimationCameraModifier`  
`class UCameraAnimationCameraModifier : public UCameraModifier`  
_L187-269_
- reflection: `UCLASS(MinimalAPI, config=Camera)`
- inherits: `UCameraModifier`
- desc: A camera modifier that plays camera animation sequences.
- L192 _public prototype_ `UCameraAnimationCameraModifier(const FObjectInitializer& ObjectInitializer);`
- L200 _public prototype_ `FCameraAnimationHandle PlayCameraAnimation(UCameraAnimationSequence* Sequence, FCameraAnimationParams Params);` — `UFUNCTION(BlueprintCallable, Category="Camera Animation")` — Play a new camera animation sequence. @param Sequence		The sequence to use for the new camera animation. @param Params		The parameters for the new camera animation instance.
- L208 _public prototype_ `bool IsCameraAnimationActive(const FCameraAnimationHandle& Handle) const;` — `UFUNCTION(BlueprintCallable, Category="Camera Animation")` — Returns whether the given camera animation is playing. @param Handle		A handle to a previously started camera animation. @return				Whether the corresponding camera animation is playing or not.
- L216 _public prototype_ `void StopCameraAnimation(const FCameraAnimationHandle& Handle, bool bImmediate = false);` — `UFUNCTION(BlueprintCallable, Category = "Camera Animation")` — Stops the given camera animation instance. @param Hanlde		A handle to a previously started camera animation. @param bImmediate	True to stop it right now and ignore blend out, false to let it blend out as indicated.
- L224 _public prototype_ `void StopAllCameraAnimationsOf(UCameraAnimationSequence* Sequence, bool bImmediate = false);` — `UFUNCTION(BlueprintCallable, Category="Camera Animation")` — Stop playing all instances of the given camera animation sequence. @param Sequence		The sequence of which to stop all instances. @param bImmediate	True to stop it right now and ignore blend out, false to let it blend out as indicated.
- L231 _public prototype_ `virtual void StopAllCameraAnimations(bool bImmediate = false);` — `UFUNCTION(BlueprintCallable, Category="Camera Animation")` — Stop all camera animation instances. @param bImmediate	True to stop it right now and ignore blend out, false to let it blend out as indicated.
- L234 _public prototype_ `virtual bool ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV) override;` — UCameraModifier interface
- L235 _public prototype_ `virtual void DisplayDebug(class UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;`
- L240 _public prototype_ `static UCameraAnimationCameraModifier* GetCameraAnimationCameraModifier(const UObject* WorldContextObject, int32 PlayerIndex);` — `UFUNCTION(BlueprintPure, Category="Camera Animation", meta=(WorldContext="WorldContextObject"))`
- L243 _public prototype_ `static UCameraAnimationCameraModifier* GetCameraAnimationCameraModifierFromID(const UObject* WorldContextObject, int32 ControllerID);` — `UFUNCTION(BlueprintPure, Category="Camera Animation", meta=(WorldContext="WorldContextObject"))`
- L246 _public prototype_ `static UCameraAnimationCameraModifier* GetCameraAnimationCameraModifierFromPlayerController(const APlayerController* PlayerController);` — `UFUNCTION(BlueprintPure, Category="Camera Animation")`
- L250 _protected prototype_ `static float EvaluateEasing(ECameraAnimationEasingType EasingType, float Interp);`
- L252 _protected prototype_ `int32 FindInactiveCameraAnimation();`
- L253 _protected prototype_ `const FActiveCameraAnimationInfo* GetActiveCameraAnimation(const FCameraAnimationHandle& Handle) const;`
- L254 _protected prototype_ `FActiveCameraAnimationInfo* GetActiveCameraAnimation(const FCameraAnimationHandle& Handle);`
- L255 _protected prototype_ `void DeactivateCameraAnimation(int32 Index);`
- L257 _protected prototype_ `void TickAllAnimations(float DeltaTime, FMinimalViewInfo& InOutPOV);`
- L258 _protected prototype_ `void TickAnimation(FActiveCameraAnimationInfo& CameraAnimation, float DeltaTime, FMinimalViewInfo& InOutPOV);`
- L264 _protected member_ `TArray<FActiveCameraAnimationInfo> ActiveAnimations;` — `UPROPERTY()` — List of active camera animation instances
- L268 _protected member_ `uint16 NextInstanceSerialNumber;` — `UPROPERTY()` — Next serial number to use for a camera animation instance

#### class `UEngineCameraAnimationFunctionLibrary`  
`class UEngineCameraAnimationFunctionLibrary : public UBlueprintFunctionLibrary`  
_L276-290_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for autocasting a player camera manager into the camera animation camera modifier. This prevents breaking Blueprints now that APlayerCameraManager::StartCameraShake returns the base class.
- L283 _public prototype_ `static UCameraAnimationCameraModifier* Conv_CameraAnimationCameraModifier(APlayerCameraManager* PlayerCameraManager);` — `UFUNCTION(BlueprintPure, Category="Camera Animation", meta=(BlueprintAutocast))`
- L286 _public prototype_ `static ECameraShakePlaySpace Conv_CameraShakePlaySpace(ECameraAnimationPlaySpace CameraAnimationPlaySpace);` — `UFUNCTION(BlueprintPure, Category = "Camera Animation", meta = (BlueprintAutocast))`
- L289 _public prototype_ `static ECameraAnimationPlaySpace Conv_CameraAnimationPlaySpace(ECameraShakePlaySpace CameraShakePlaySpace);` — `UFUNCTION(BlueprintPure, Category = "Camera Animation", meta = (BlueprintAutocast))`

#### class `UGameplayCamerasFunctionLibrary`  
`class UGameplayCamerasFunctionLibrary : public UEngineCameraAnimationFunctionLibrary`  
_L293-295_
- reflection: `UE_DEPRECATED(5.5, "Please use UEngineCameraAnimationFunctionLibrary")`
- inherits: `UEngineCameraAnimationFunctionLibrary`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ENGINECAMERAS_API`
- L106 _function_ `friend bool operator==(FCameraAnimationHandle A, FCameraAnimationHandle B)`
- L110 _function_ `friend bool operator!=(FCameraAnimationHandle A, FCameraAnimationHandle B)`
- L114 _function_ `friend bool operator<(FCameraAnimationHandle A, FCameraAnimationHandle B)`
- L118 _function_ `friend uint32 GetTypeHash(FCameraAnimationHandle In)`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/EngineCamerasModule.h` (Public)


#### class `IEngineCamerasModule`  
`class IEngineCamerasModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_STATS_GROUP(TEXT("Camera Animation Evaluation"), STATGROUP_CameraAnimation, STATCAT_Advanced)`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/EngineCamerasSubsystem.h` (Public)


#### class `UEngineCamerasSubsystem`  
`class UEngineCamerasSubsystem : public UWorldSubsystem`  
_L18-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: World subsystem that holds global objects for handling camera animation sequences.
- L25 _public prototype_ `static UEngineCamerasSubsystem* GetEngineCamerasSubsystem(const UWorld* InWorld);` — Get the camera animation sequence subsystem for the given world
- L36 _public prototype_ `FCameraAnimationHandle PlayCameraAnimation(APlayerController* PlayerController, UCameraAnimationSequence* Sequence, FCameraAnimationParams Params);` — `UFUNCTION(BlueprintCallable, Category="Camera Animation")` — Play a new camera animation sequence. @param PlayerController The player controller on which to play the animation. @param Sequence		The sequence to use for the new camera animation. @param Params		The parameters for the new camera animation instance.
- L45 _public prototype_ `bool IsCameraAnimationActive(APlayerController* PlayerController, const FCameraAnimationHandle& Handle) const;` — `UFUNCTION(BlueprintPure, Category="Camera Animation")` — Returns whether the given camera animation is playing. @param PlayerController The player controller on which to play the animation. @param Handle		A handle to a previously started camera animation. @return				Whether the corresponding camera animation is playing or not.
- L54 _public prototype_ `void StopCameraAnimation(APlayerController* PlayerController, const FCameraAnimationHandle& Handle, bool bImmediate = false);` — `UFUNCTION(BlueprintCallable, Category = "Camera Animation")` — Stops the given camera animation instance. @param PlayerController The player controller on which to play the animation. @param Hanlde		A handle to a previously started camera animation. @param bImmediate	True to stop it right now and ignore blend out, false to let it blend out as indicated.
- L63 _public prototype_ `void StopAllCameraAnimationsOf(APlayerController* PlayerController, UCameraAnimationSequence* Sequence, bool bImmediate = false);` — `UFUNCTION(BlueprintCallable, Category="Camera Animation")` — Stop playing all instances of the given camera animation sequence. @param PlayerController The player controller on which to play the animation. @param Sequence		The sequence of which to stop all instances. @param bImmediate	True to stop it right now and ignore blend out, false to let it blend out as indicated.
- L71 _public prototype_ `void StopAllCameraAnimations(APlayerController* PlayerController, bool bImmediate = false);` — `UFUNCTION(BlueprintCallable, Category="Camera Animation")` — Stop all camera animation instances. @param PlayerController The player controller on which to play the animation. @param bImmediate	True to stop it right now and ignore blend out, false to let it blend out as indicated.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENGINECAMERAS_API`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Shakes/CompositeCameraShakePattern.h` (Public)


#### class `UCompositeCameraShakePattern`  
`class UCompositeCameraShakePattern : public UCameraShakePattern`  
_L14-46_
- reflection: `UCLASS(MinimalAPI, meta=(AutoExpandCategories="CameraShake"))`
- inherits: `UCameraShakePattern`
- desc: A base class for a simple camera shake.
- L20 _public function_ `UCompositeCameraShakePattern(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L23 _public function_ `template<typename PatternClass> PatternClass* AddChildPattern()`
- L34 _public member_ `TArray<TObjectPtr<UCameraShakePattern>> ChildPatterns;` — `UPROPERTY(EditAnywhere, Instanced, Category=CameraShake)` — The list of child shake patterns
- L39 _private prototype_ `virtual void GetShakePatternInfoImpl(FCameraShakeInfo& OutInfo) const override;` — UCameraShakePattern interface
- L40 _private prototype_ `virtual void StartShakePatternImpl(const FCameraShakePatternStartParams& Params) override;`
- L41 _private prototype_ `virtual void UpdateShakePatternImpl(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L42 _private prototype_ `virtual void ScrubShakePatternImpl(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L43 _private prototype_ `virtual bool IsFinishedImpl() const override;`
- L44 _private prototype_ `virtual void StopShakePatternImpl(const FCameraShakePatternStopParams& Params) override;`
- L45 _private prototype_ `virtual void TeardownShakePatternImpl() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENGINECAMERAS_API`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Shakes/DefaultCameraShakeBase.h` (Public)


#### class `UDefaultCameraShakeBase`  
`class UDefaultCameraShakeBase : public UCameraShakeBase`  
_L14-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraShakeBase`
- desc: Like UCameraShakeBase but with a perlin noise shake pattern by default, for convenience.
- L20 _public prototype_ `UDefaultCameraShakeBase(const FObjectInitializer& ObjInit);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENGINECAMERAS_API`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Shakes/LegacyCameraShake.h` (Public)


#### enum `EOscillatorWaveform`  
`enum class EOscillatorWaveform : uint8`  
_L21-28_
- reflection: `UENUM(BlueprintType)`
- desc: Types of waveforms that can be used for camera shake oscillators
- L24 _public enumerator_ `SineWave` — A sinusoidal wave
- L27 _public enumerator_ `PerlinNoise` — Perlin noise

#### enum `EInitialOscillatorOffset`  
`enum EInitialOscillatorOffset : int`  
_L32-39_
- reflection: `UENUM()`
- desc: Shake start offset parameter
- L35 _public enumerator_ `EOO_OffsetRandom UMETA(DisplayName = "Random")` — Start with random offset (default).
- L37 _public enumerator_ `EOO_OffsetZero UMETA(DisplayName = "Zero")` — Start with zero offset.
- L38 _public enumerator_ `EOO_MAX`

#### struct `FFOscillator`  
`struct FFOscillator`  
_L43-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines oscillation of a single number.
- L49 _public member_ `float Amplitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOscillator)` — Amplitude of the sinusoidal oscillation.
- L53 _public member_ `float Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOscillator)` — Frequency of the sinusoidal oscillation.
- L61 _public member_ `EOscillatorWaveform Waveform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOscillator)` — Type of waveform to use for oscillation.
- L63 _public function_ `FFOscillator() : Amplitude(0) , Frequency(0) , InitialOffset(0) , Waveform(EOscillatorWaveform::SineWave)`
- L71 _public prototype_ `static float UpdateOffset(FFOscillator const& Osc, float& CurrentOffset, float DeltaTime);` — Advances the oscillation time and returns the current value.
- L74 _public prototype_ `static float UpdateOffset(FFOscillator const& Osc, double& CurrentOffset, float DeltaTime);` — Advances the oscillation time and returns the current value.
- L77 _public prototype_ `static float GetInitialOffset(FFOscillator const& Osc);` — Returns the initial value of the oscillator.
- L80 _public prototype_ `static float GetOffsetAtTime(FFOscillator const& Osc, float InitialOffset, float Time);` — Returns the offset at the given time

#### struct `FROscillator`  
`struct FROscillator`  
_L85-101_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines FRotator oscillation.
- L91 _public member_ `struct FFOscillator Pitch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ROscillator)` — Pitch oscillation.
- L95 _public member_ `struct FFOscillator Yaw;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ROscillator)` — Yaw oscillation.
- L99 _public member_ `struct FFOscillator Roll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ROscillator)` — Roll oscillation.

#### struct `FVOscillator`  
`struct FVOscillator`  
_L105-120_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines FVector oscillation.
- L111 _public member_ `struct FFOscillator X;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VOscillator)` — Oscillation in the X axis.
- L115 _public member_ `struct FFOscillator Y;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VOscillator)` — Oscillation in the Y axis.
- L119 _public member_ `struct FFOscillator Z;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VOscillator)` — Oscillation in the Z axis.

#### class `ULegacyCameraShake`  
`class ULegacyCameraShake : public UCameraShakeBase`  
_L127-285_
- reflection: `UCLASS(MinimalAPI, Blueprintable, HideCategories = (CameraShakePattern))`
- inherits: `UCameraShakeBase`
- desc: Legacy camera shake which can do either oscillation or run camera anims.
- L134 _public member_ `float OscillationDuration;` — `UPROPERTY(EditAnywhere, Category = Oscillation)` — Duration in seconds of current screen shake. Less than 0 means indefinite, 0 means no oscillation.
- L138 _public member_ `float OscillationBlendInTime;` — `UPROPERTY(EditAnywhere, Category = Oscillation, meta = (ClampMin = "0.0"))` — Duration of the blend-in, where the oscillation scales from 0 to 1.
- L142 _public member_ `float OscillationBlendOutTime;` — `UPROPERTY(EditAnywhere, Category = Oscillation, meta = (ClampMin = "0.0"))` — Duration of the blend-out, where the oscillation scales from 1 to 0.
- L146 _public member_ `struct FROscillator RotOscillation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Oscillation)` — Rotational oscillation
- L150 _public member_ `struct FVOscillator LocOscillation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Oscillation)` — Positional oscillation
- L154 _public member_ `struct FFOscillator FOVOscillation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Oscillation)` — FOV oscillation
- L162 _public member_ `float AnimPlayRate;` — `UPROPERTY(EditAnywhere, Category = AnimShake, meta = (ClampMin = "0.001"))` — Scalar defining how fast to play the anim.
- L166 _public member_ `float AnimScale;` — `UPROPERTY(EditAnywhere, Category = AnimShake, meta = (ClampMin = "0.0"))` — Scalar defining how "intense" to play the anim.
- L170 _public member_ `float AnimBlendInTime;` — `UPROPERTY(EditAnywhere, Category = AnimShake, meta = (ClampMin = "0.0"))` — Linear blend-in time.
- L174 _public member_ `float AnimBlendOutTime;` — `UPROPERTY(EditAnywhere, Category = AnimShake, meta = (ClampMin = "0.0"))` — Linear blend-out time.
- L178 _public member_ `float RandomAnimSegmentDuration;` — `UPROPERTY(EditAnywhere, Category = AnimShake, meta = (ClampMin = "0.0", editcondition = "bRandomAnimSegment"))` — When bRandomAnimSegment is true, this defines how long the anim should play.
- L182 _public member_ `TObjectPtr<class UCameraAnimationSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = AnimShake)` — Source camera animation sequence to play. Can be null.
- L189 _public member_ `uint32 bRandomAnimSegment : 1;` — `UPROPERTY(EditAnywhere, Category = AnimShake)` — If true, play a random snippet of the animation of length Duration.  Implies bLoop and bRandomStartTime = true for the AnimSequence. If false, play the full anim once, non-looped. Useful for getting variety out of a single looped AnimSequence asset.
- L195 _public member_ `float OscillatorTimeRemaining;` — `UPROPERTY(transient, BlueprintReadOnly, Category = CameraShake)` — Time remaining for oscillation shakes. Less than 0.f means shake infinitely.
- L203 _public prototype_ `void ReceivePlayShake(float Scale);` — `UFUNCTION(BlueprintImplementableEvent, Category = CameraShake)` — Called when the shake starts playing
- L207 _public prototype_ `void BlueprintUpdateCameraShake(float DeltaTime, float Alpha, const FMinimalViewInfo& POV, FMinimalViewInfo& ModifiedPOV);` — `UFUNCTION(BlueprintImplementableEvent, Category = CameraShake)` — Called every tick to let the shake modify the point of view
- L211 _public prototype_ `bool ReceiveIsFinished() const;` — `UFUNCTION(BlueprintNativeEvent, Category = CameraShake)` — Called to allow a shake to decide when it's finished playing.
- L218 _public prototype_ `void ReceiveStopShake(bool bImmediately);` — `UFUNCTION(BlueprintImplementableEvent, Category = CameraShake)` — Called when the shake is explicitly stopped. @param bImmediatly		If true, shake stops right away regardless of blend out settings. If false, shake may blend out according to its settings.
- L227 _public prototype_ `static ULegacyCameraShake* StartLegacyCameraShake(APlayerCameraManager* PlayerCameraManager, TSubclassOf<ULegacyCameraShake> ShakeClass, float Scale = 1.f, ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal, FRotator UserPlaySpaceRot = FRotator::ZeroRotator);` — `UFUNCTION(BlueprintCallable, Category = "Camera Shakes")` — Backwards compatible method used by core BP redirectors. This is needed because the return value is specifically a legacy camera shake, which some BP logic often uses directly to set oscillator/anim properties.
- L234 _public prototype_ `static ULegacyCameraShake* StartLegacyCameraShakeFromSource(APlayerCameraManager* PlayerCameraManager, TSubclassOf<ULegacyCameraShake> ShakeClass, UCameraShakeSourceComponent* SourceComponent, float Scale = 1.f, ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal, FRotator UserPlaySpaceRot = FRotator::ZeroRotator);` — `UFUNCTION(BlueprintCallable, Category = "Camera Shakes")` — Backwards compatible method used by core BP redirectors. This is needed because the return value is specifically a legacy camera shake, which some BP logic often uses directly to set oscillator/anim properties.
- L239 _public prototype_ `bool IsLooping() const;` — Returns true if this camera shake will loop forever
- L243 _private prototype_ `void DoStartShake(const FCameraShakePatternStartParams& Params);`
- L244 _private prototype_ `void DoUpdateShake(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult);`
- L245 _private prototype_ `void DoScrubShake(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult);`
- L246 _private prototype_ `void DoStopShake(bool bImmediately);`
- L247 _private prototype_ `bool DoGetIsFinished() const;`
- L248 _private prototype_ `void DoTeardownShake();`
- L253 _protected member_ `float ActualOscillationDuration;` — Actual oscillation duration.
- L256 _protected member_ `FVector LocSinOffset;` — Current location sinusoidal offset.
- L259 _protected member_ `FVector RotSinOffset;` — Current rotational sinusoidal offset.
- L262 _protected member_ `float FOVSinOffset;` — Current FOV sinusoidal offset.
- L265 _protected member_ `FVector InitialLocSinOffset;` — Initial offset (could have been assigned at random).
- L268 _protected member_ `FVector InitialRotSinOffset;` — Initial offset (could have been assigned at random).
- L271 _protected member_ `float InitialFOVSinOffset;` — Initial offset (could have been assigned at random).
- L275 _protected member_ `TObjectPtr<class USequenceCameraShakePattern> SequenceShakePattern;` — `UPROPERTY(Instanced)` — Sequence shake pattern for when using a sequence instead of a camera anim
- L279 _private member_ `float CurrentBlendInTime;`
- L280 _private member_ `float CurrentBlendOutTime;`
- L281 _private member_ `bool bBlendingIn : 1;`
- L282 _private member_ `bool bBlendingOut : 1;`

#### class `ULegacyCameraShakePattern`  
`class ULegacyCameraShakePattern : public UCameraShakePattern`  
_L295-309_
- reflection: `UCLASS(MinimalAPI, HideDropdown)`
- inherits: `UCameraShakePattern`
- desc: Shake pattern for the ULegacyCameraShake class. It doesn't do anything because, for backwards compatibility reasons, all the data was left on the shake class itself... so this pattern delegates everything back to the owner shake.
- L302 _private prototype_ `virtual void GetShakePatternInfoImpl(FCameraShakeInfo& OutInfo) const override;` — UCameraShakePattern interface
- L303 _private prototype_ `virtual void StartShakePatternImpl(const FCameraShakePatternStartParams& Params) override;`
- L304 _private prototype_ `virtual void UpdateShakePatternImpl(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L305 _private prototype_ `virtual void ScrubShakePatternImpl(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L306 _private prototype_ `virtual bool IsFinishedImpl() const override;`
- L307 _private prototype_ `virtual void StopShakePatternImpl(const FCameraShakePatternStopParams& Params) override;`
- L308 _private prototype_ `virtual void TeardownShakePatternImpl() override;`

#### class `ULegacyCameraShakeFunctionLibrary`  
`class ULegacyCameraShakeFunctionLibrary : public UBlueprintFunctionLibrary`  
_L316-326_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for autocasting from a base camera shake to a legacy camera shake. This prevents breaking Blueprints now that APlayerCameraManager::StartCameraShake returns the base class.
- L322 _public function_ `static ULegacyCameraShake* Conv_LegacyCameraShake(UCameraShakeBase* CameraShake)` — `UFUNCTION(BlueprintPure, Category = "Camera Shakes", meta = (BlueprintAutocast))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ENGINECAMERAS_API`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Shakes/MatineeCameraShake.h` (Public)
_(no declarations extracted)_

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Shakes/PerlinNoiseCameraShakePattern.h` (Public)


#### struct `FPerlinNoiseShaker`  
`struct FPerlinNoiseShaker`  
_L12-32_
- reflection: `USTRUCT(BlueprintType)`
- desc: A perlin noise shaker for a single number.
- L18 _public member_ `float Amplitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PerlinNoise)` — Amplitude of the perlin noise.
- L22 _public member_ `float Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PerlinNoise)` — Frequency of the sinusoidal oscillation.
- L25 _public function_ `FPerlinNoiseShaker() : Amplitude(1.f) , Frequency(1.f)` — Creates a new perlin noise shaker.
- L31 _public prototype_ `float Update(float DeltaTime, float AmplitudeMultiplier, float FrequencyMultiplier, float& InOutCurrentOffset) const;` — Advances the shake time and returns the current value

#### class `UPerlinNoiseCameraShakePattern`  
`class UPerlinNoiseCameraShakePattern : public USimpleCameraShakePattern`  
_L38-117_
- reflection: `UCLASS(MinimalAPI, meta=(AutoExpandCategories="Location,Rotation,FOV,Timing"))`
- inherits: `USimpleCameraShakePattern`
- desc: A camera shake that uses Perlin noise to shake the camera.
- L44 _public prototype_ `UPerlinNoiseCameraShakePattern(const FObjectInitializer& ObjInit);`
- L50 _public member_ `float LocationAmplitudeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Amplitude multiplier for all location shake
- L54 _public member_ `float LocationFrequencyMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Frequency multiplier for all location shake
- L58 _public member_ `FPerlinNoiseShaker X;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Shake in the X axis.
- L62 _public member_ `FPerlinNoiseShaker Y;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Shake in the Y axis.
- L66 _public member_ `FPerlinNoiseShaker Z;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Shake in the Z axis.
- L70 _public member_ `float RotationAmplitudeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Amplitude multiplier for all rotation shake
- L74 _public member_ `float RotationFrequencyMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Frequency multiplier for all rotation shake
- L78 _public member_ `FPerlinNoiseShaker Pitch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Pitch shake.
- L82 _public member_ `FPerlinNoiseShaker Yaw;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Yaw shake.
- L86 _public member_ `FPerlinNoiseShaker Roll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Roll shake.
- L90 _public member_ `FPerlinNoiseShaker FOV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FOV)` — FOV shake.
- L95 _private prototype_ `virtual void StartShakePatternImpl(const FCameraShakePatternStartParams& Params) override;` — UCameraShakePattern interface
- L96 _private prototype_ `virtual void UpdateShakePatternImpl(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L97 _private prototype_ `virtual void ScrubShakePatternImpl(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L99 _private prototype_ `void UpdatePerlinNoise(float DeltaTime, FCameraShakePatternUpdateResult& OutResult);`
- L104 _private member_ `FVector3f InitialLocationOffset;` — Initial perlin noise offset for location oscillation.
- L106 _private member_ `FVector3f CurrentLocationOffset;` — Current perlin noise offset for location oscillation.
- L109 _private member_ `FVector3f InitialRotationOffset;` — Initial perlin noise offset for rotation oscillation.
- L111 _private member_ `FVector3f CurrentRotationOffset;` — Current perlin noise offset for rotation oscillation.
- L114 _private member_ `float InitialFOVOffset;` — Initial perlin noise offset for FOV oscillation
- L116 _private member_ `float CurrentFOVOffset;` — Current perlin noise offset for FOV oscillation

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENGINECAMERAS_API`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Shakes/SimpleCameraShakePattern.h` (Public)


#### class `USimpleCameraShakePattern`  
`class USimpleCameraShakePattern : public UCameraShakePattern`  
_L14-49_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UCameraShakePattern`
- desc: A base class for a simple camera shake.
- L20 _public function_ `USimpleCameraShakePattern(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L26 _public member_ `float Duration = 1.f;` — `UPROPERTY(EditAnywhere, Category=Timing)` — Duration in seconds of this shake. Zero or less means infinite.
- L30 _public member_ `float BlendInTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category=Timing)` — Blend-in time for this shake. Zero or less means no blend-in.
- L34 _public member_ `float BlendOutTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category=Timing)` — Blend-out time for this shake. Zero or less means no blend-out.
- L39 _protected prototype_ `virtual void GetShakePatternInfoImpl(FCameraShakeInfo& OutInfo) const override;` — UCameraShakePattern interface
- L40 _protected prototype_ `virtual void StartShakePatternImpl(const FCameraShakePatternStartParams& Params) override;`
- L41 _protected prototype_ `virtual bool IsFinishedImpl() const override;`
- L42 _protected prototype_ `virtual void StopShakePatternImpl(const FCameraShakePatternStopParams& Params) override;`
- L43 _protected prototype_ `virtual void TeardownShakePatternImpl() override;`
- L48 _protected member_ `FCameraShakeState State;` — The ongoing state for this shake

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENGINECAMERAS_API`

### `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Shakes/WaveOscillatorCameraShakePattern.h` (Public)


#### enum `EInitialWaveOscillatorOffsetType`  
`enum class EInitialWaveOscillatorOffsetType : uint8`  
_L12-18_
- reflection: `UENUM()`
- desc: Shake start offset parameter.
- L15 _public enumerator_ `Random` — Start with random offset (default).
- L17 _public enumerator_ `Zero` — Start with zero offset.

#### struct `FWaveOscillator`  
`struct FWaveOscillator`  
_L22-50_
- reflection: `USTRUCT(BlueprintType)`
- desc: A wave oscillator for a single number.
- L28 _public member_ `float Amplitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Oscillation)` — Amplitude of the sinusoidal oscillation.
- L32 _public member_ `float Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Oscillation)` — Frequency of the sinusoidal oscillation.
- L36 _public member_ `EInitialWaveOscillatorOffsetType InitialOffsetType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Oscillation)` — Defines how to begin the oscillation.
- L39 _public function_ `FWaveOscillator() : Amplitude(1.f) , Frequency(1.f) , InitialOffsetType(EInitialWaveOscillatorOffsetType::Random)` — Creates a new wave oscillator.
- L46 _public prototype_ `float Initialize(float& OutInitialOffset) const;` — Sets the initial offset and returns the initial value of the oscillator
- L49 _public prototype_ `float Update(float DeltaTime, float AmplitudeMultiplier, float FrequencyMultiplier, float& InOutCurrentOffset) const;` — Advances the oscillation time and returns the current value

#### class `UWaveOscillatorCameraShakePattern`  
`class UWaveOscillatorCameraShakePattern : public USimpleCameraShakePattern`  
_L56-135_
- reflection: `UCLASS(MinimalAPI, meta=(AutoExpandCategories="Location,Rotation,FOV,Timing"))`
- inherits: `USimpleCameraShakePattern`
- desc: A camera shake that uses oscillations to move the camera.
- L62 _public prototype_ `UWaveOscillatorCameraShakePattern(const FObjectInitializer& ObjInit);`
- L68 _public member_ `float LocationAmplitudeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Amplitude multiplier for all location oscillation
- L72 _public member_ `float LocationFrequencyMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Frequency multiplier for all location oscillation
- L76 _public member_ `FWaveOscillator X;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Oscillation in the X axis.
- L80 _public member_ `FWaveOscillator Y;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Oscillation in the Y axis.
- L84 _public member_ `FWaveOscillator Z;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)` — Oscillation in the Z axis.
- L88 _public member_ `float RotationAmplitudeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Amplitude multiplier for all rotation oscillation
- L92 _public member_ `float RotationFrequencyMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Frequency multiplier for all rotation oscillation
- L96 _public member_ `FWaveOscillator Pitch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Pitch oscillation.
- L100 _public member_ `FWaveOscillator Yaw;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Yaw oscillation.
- L104 _public member_ `FWaveOscillator Roll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Roll oscillation.
- L108 _public member_ `FWaveOscillator FOV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FOV)` — FOV oscillation.
- L113 _private prototype_ `virtual void StartShakePatternImpl(const FCameraShakePatternStartParams& Params) override;` — UCameraShakePattern interface
- L114 _private prototype_ `virtual void UpdateShakePatternImpl(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L115 _private prototype_ `virtual void ScrubShakePatternImpl(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L117 _private prototype_ `void UpdateOscillators(float DeltaTime, FCameraShakePatternUpdateResult& OutResult);`
- L122 _private member_ `FVector3f InitialLocationOffset;` — Initial sinusoidal offset for location oscillation.
- L124 _private member_ `FVector3f CurrentLocationOffset;` — Current sinusoidal offset for location oscillation.
- L127 _private member_ `FVector3f InitialRotationOffset;` — Initial sinusoidal offset for rotation oscillation.
- L129 _private member_ `FVector3f CurrentRotationOffset;` — Current sinusoidal offset for rotation oscillation.
- L132 _private member_ `float InitialFOVOffset;` — Initial sinusoidal offset for FOV oscillation
- L134 _private member_ `float CurrentFOVOffset;` — Current sinusoidal offset for FOV oscillation

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ENGINECAMERAS_API`
