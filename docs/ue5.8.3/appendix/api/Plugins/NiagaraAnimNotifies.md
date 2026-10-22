# Plugins / NiagaraAnimNotifies

- module root: `Plugins/FX/Niagara/Source/NiagaraAnimNotifies`
- headers: 3; symbols: 57
- symbol kinds: class=4, enum=1, enumerator=3, member=26, prototype=21, struct=2
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Niagara

### `Plugins/FX/Niagara/Source/NiagaraAnimNotifies/Public/AnimNotifyState_TimedNiagaraEffect.h` (Public)


#### enum `ENiagaraAnimNotifyProgressType`  
`enum class ENiagaraAnimNotifyProgressType : uint8`  
_L17-25_
- reflection: `UENUM()`
- L20 _public enumerator_ `None` — Progress information will not be send to the FX component
- L22 _public enumerator_ `Forward` — Send normalized progress (0.0 to 1.0) to the FX component as a float user parameter
- L24 _public enumerator_ `Reverse` — Send reversed normalized progress (1.0 to 0.0) to the FX component as a float user parameter

#### class `UAnimNotifyState_TimedNiagaraEffect`  
`class UAnimNotifyState_TimedNiagaraEffect : public UAnimNotifyState`  
_L31-81_
- reflection: `UCLASS(Blueprintable, meta = (DisplayName = "Timed Niagara Effect"), MinimalAPI)`
- inherits: `UAnimNotifyState`
- desc: Timed Niagara Effect Notify Allows a looping Niagara effect to be played in an animation that will activate at the beginning of the notify and deactivate at the end.
- L37 _private member_ `TObjectPtr<UNiagaraSystem> Template;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem, meta = (DisplayName = "Niagara System", ToolTip = "The niagara system to spawn for the notify state"))` — The niagara system template to use when spawning the niagara component
- L41 _private member_ `FName SocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem, meta = (ToolTip = "The socket or bone to attach the system to", AnimNotifyBoneName = "true"))` — The socket within our mesh component to attach to when we spawn the Niagara component
- L45 _private member_ `FVector LocationOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem, meta = (ToolTip = "Offset from the socket or bone to place the Niagara system"))` — Offset from the socket / bone location
- L49 _private member_ `FRotator RotationOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem, meta = (ToolTip = "Rotation offset from the socket or bone for the Niagara system"))` — Offset from the socket / bone rotation
- L53 _private member_ `FVector Scale = FVector(1.0f);` — `UPROPERTY(EditAnywhere, Category = NiagaraSystem)` — Scale to spawn the Niagara system at
- L57 _private member_ `bool bApplyRateScaleAsTimeDilation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem)` — Should we set the animation rate scale as time dilation on the spawn effect?
- L62 _private member_ `bool bDestroyAtEnd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NiagaraSystem, meta = (DisplayName = "Destroy Immediately", ToolTip = "Whether the Niagara system should be immediately destroyed at the end of the notify state or be allowed to finish"))` — Whether or not we destroy the component at the end of the notify or instead just stop the emitters.
- L64 _private prototype_ `virtual void NotifyBegin(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;`
- L65 _private prototype_ `virtual void NotifyEnd(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;`
- L68 _private prototype_ `FString GetNotifyName_Implementation() const override;` — Overridden from UAnimNotifyState to provide custom notify name.
- L72 _private prototype_ `UFXSystemComponent* GetSpawnedEffect(UMeshComponent* MeshComp);` — `UFUNCTION(BlueprintCallable, Category = "AnimNotify")` — Return FXSystemComponent created from SpawnEffect
- L76 _protected prototype_ `virtual UFXSystemComponent* SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const;` — Spawns the NiagaraSystemComponent. Called from Notify.
- L78 _protected prototype_ `bool ValidateParameters(USkeletalMeshComponent* MeshComp) const;`
- L80 _protected prototype_ `FName GetSpawnedComponentTag() const;`

#### struct `FCurveParameterPair`  
`struct FCurveParameterPair`  
_L84-92_
- reflection: `USTRUCT(BlueprintType)`
- L89 _public member_ `FName AnimCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimCurves, meta = (DisplayName = "Anim Curve Name", ToolTip = "Name of the curve in this montage."))`
- L91 _public member_ `FName UserVariableName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimCurves, meta = (DisplayName = "Niagara User Float", ToolTip = "Name of the Niagara user float variable."))`

#### class `UAnimNotifyState_TimedNiagaraEffectAdvanced`  
`class UAnimNotifyState_TimedNiagaraEffectAdvanced : public UAnimNotifyState_TimedNiagaraEffect`  
_L98-143_
- reflection: `UCLASS(Blueprintable, meta = (DisplayName = "Advanced Timed Niagara Effect"), MinimalAPI)`
- inherits: `UAnimNotifyState_TimedNiagaraEffect`
- desc: Same as Timed Niagara Effect but also provides some more advanced abilities at an additional cost.
- L103 _public prototype_ `virtual void Serialize(class FArchive& Ar) override;`
- L105 _public prototype_ `virtual void PostLoad() override;`
- L108 _public prototype_ `virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;`
- L109 _public prototype_ `virtual void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;`
- L110 _public prototype_ `virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;`
- L114 _public prototype_ `float GetNotifyProgress(UMeshComponent* MeshComp);` — `UFUNCTION(BlueprintCallable, Category = "AnimNotify")` — Returns a 0 to 1 value for the progress of this component along the notify.
- L118 _public member_ `ENiagaraAnimNotifyProgressType NotifyProgressType = ENiagaraAnimNotifyProgressType::Forward;` — `UPROPERTY(EditAnywhere, Category = NotifyProgress)` — How/if we should send progress to the FX component
- L122 _public member_ `bool bApplyRateScaleToProgress = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NotifyProgress, meta = (DisplayName = "Notify Progress Apply Rate Scale"))` — Should we apply the animation rate scale when calculating the elasped time.
- L125 _public member_ `FName NotifyProgressUserParameter;` — `UPROPERTY(EditAnywhere, Category = NotifyProgress, meta = (DisplayName = "User Parameter", ToolTip = "The name of your niagara user variable you would like to send the normalized notify progress to."))`
- L128 _public member_ `TArray<FCurveParameterPair> AnimCurves;` — `UPROPERTY(EditAnywhere, Category = AnimCurves, meta = (DisplayName = "Anim Curve Parameters", ToolTip = "Array of fnames to map Anim Curve names to Niagara Parameters."))`
- L132 _public member_ `bool bEnableNormalizedNotifyProgress_DEPRECATED = true;` — `UPROPERTY()`
- L142 _protected member_ `TMap<UMeshComponent*, FInstanceProgressInfo> ProgressInfoMap;`

#### struct `UAnimNotifyState_TimedNiagaraEffectAdvanced::FInstanceProgressInfo`  
`struct FInstanceProgressInfo`  
_L137-141_
- L139 _public member_ `float Duration = 1.0f;`
- L140 _public member_ `float Elapsed = 0.0f;`

### `Plugins/FX/Niagara/Source/NiagaraAnimNotifies/Public/AnimNotify_PlayNiagaraEffect.h` (Public)


#### class `UAnimNotify_PlayNiagaraEffect`  
`class UAnimNotify_PlayNiagaraEffect : public UAnimNotify`  
_L19-88_
- reflection: `UCLASS(const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Play Niagara Particle Effect"), MinimalAPI)`
- inherits: `UAnimNotify`
- L25 _public prototype_ `UAnimNotify_PlayNiagaraEffect();`
- L28 _public prototype_ `virtual void PostLoad() override;`
- L30 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _public prototype_ `virtual FString GetNotifyName_Implementation() const override;`
- L37 _public prototype_ `virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;`
- L39 _public prototype_ `virtual void ValidateAssociatedAssets() override;`
- L45 _public member_ `TObjectPtr<UNiagaraSystem> Template;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (DisplayName = "Niagara System"))` — Niagara System to Spawn
- L49 _public member_ `FVector LocationOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")` — Location offset from the socket
- L53 _public member_ `FRotator RotationOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")` — Rotation offset from socket
- L57 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, Category = "AnimNotify")` — Scale to spawn the Niagara system at
- L61 _public member_ `bool bAbsoluteScale;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "AnimNotify")` — Whether or not we are in absolute scale mode
- L65 _public prototype_ `UFXSystemComponent* GetSpawnedEffect();` — `UFUNCTION(BlueprintCallable, Category = "AnimNotify")` — Return FXSystemComponent created from SpawnEffect
- L70 _protected member_ `UFXSystemComponent* SpawnedEffect;` — FXSystem Pointer to Spawned Effect called from Notify.
- L73 _protected member_ `FQuat RotationOffsetQuat;` — Cached version of the Rotation Offset already in Quat form
- L76 _protected prototype_ `virtual UFXSystemComponent* SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);` — Spawns the NiagaraSystemComponent. Called from Notify.
- L83 _public member_ `uint32 Attached : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")` — Should attach to the bone/socket
- L87 _public member_ `FName SocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))` — SocketName to attach to

### `Plugins/FX/Niagara/Source/NiagaraAnimNotifies/Public/NiagaraAnimNotifiesModule.h` (Public)


#### class `INiagaraAnimNotifiesModule`  
`class INiagaraAnimNotifiesModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`
- desc: Niagara AnimNotifies module interface
