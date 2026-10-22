# Plugins / AvalancheCamera

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheCamera`
- headers: 4; symbols: 43
- symbol kinds: class=3, function=3, member=9, prototype=24, struct=3, typedef=1
- PrivateDependencyModuleNames: CoreUObject, Engine, SlateCore
- PublicDependencyModuleNames: ActorModifierCore, AvalancheTransition, Core, StateTreeModule

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCamera/Private/Transition/AvaTransitionCameraLibrary.h` (Private)


#### class `UAvaTransitionCameraLibrary`  
`class UAvaTransitionCameraLibrary : public UBlueprintFunctionLibrary`  
_L9-16_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L15 _public prototype_ `static bool ConditionallyUpdateViewTarget(UObject* InTransitionNode);` — `UFUNCTION(BlueprintCallable, Category="Transition Logic|Camera", meta=(DefaultToSelf="InTransitionNode"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCamera/Public/AvaCameraPriorityModifier.h` (Public)


#### class `UAvaCameraPriorityModifier`  
`class UAvaCameraPriorityModifier : public UActorModifierCoreBase`  
_L10-39_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierCoreBase`
- L15 _public prototype_ `UAvaCameraPriorityModifier();`
- L17 _public function_ `int32 GetPriority() const`
- L22 _public function_ `const FViewTargetTransitionParams& GetTransitionParams() const`
- L29 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L30 _protected prototype_ `virtual void Apply() override;`
- L34 _protected member_ `int32 Priority = 0;` — `UPROPERTY(EditInstanceOnly, Category="Camera", meta=(ClampMin="0", UIMin="0", AllowPrivateAccess="true"))`
- L38 _protected member_ `FViewTargetTransitionParams TransitionParams;` — `UPROPERTY(EditInstanceOnly, Category="Camera", meta=(AllowPrivateAccess="true"))` — The parameters to blend to the view target

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCamera/Public/AvaCameraSubsystem.h` (Public)


#### struct `FAvaViewTarget`  
`struct FAvaViewTarget`  
_L16-36_
- reflection: `USTRUCT()`
- L21 _public prototype_ `bool IsValid() const;` — returns true if the View Target Actor is valid
- L24 _public prototype_ `int32 GetPriority() const;` — Returns the priority of the camera priority modifier of the actor, or 0 if the priority modifier doesn't exist
- L27 _public prototype_ `const FViewTargetTransitionParams& GetTransitionParams() const;` — Returns the Transition Params of the camera priority modifier of the actor, or default transition params if the modifier doesn't exist
- L31 _public member_ `TObjectPtr<AActor> Actor;` — `UPROPERTY()` — The View Target Actor
- L35 _public member_ `TObjectPtr<const UAvaCameraPriorityModifier> CameraPriorityModifier;` — `UPROPERTY()` — The Camera Modifier that the View Target Actor has, if any

#### class `UAvaCameraSubsystem`  
`class UAvaCameraSubsystem : public UWorldSubsystem`  
_L39-76_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Camera Subsystem")`
- inherits: `UWorldSubsystem`
- L44 _public prototype_ `static UAvaCameraSubsystem* Get(const UObject* InObject);`
- L46 _public prototype_ `void RegisterScene(const ULevel* InSceneLevel);`
- L47 _public prototype_ `void UnregisterScene(const ULevel* InSceneLevel);`
- L49 _public prototype_ `bool IsBlendingToViewTarget(const ULevel* InSceneLevel) const;`
- L51 _public prototype_ `void UpdatePlayerControllerViewTarget(const FViewTargetTransitionParams* InOverrideTransitionParams = nullptr);`
- L53 _public prototype_ `bool ConditionallyUpdateViewTarget(const ULevel* InSceneLevel);`
- L57 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L58 _protected prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L62 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L63 _protected prototype_ `virtual void Deinitialize() override;`
- L67 _private prototype_ `void OnTransitionStart(const IAvaTransitionExecutor& InExecutor);`
- L69 _private prototype_ `bool HasCustomViewTargetting(const ULevel* InSceneLevel) const;`
- L72 _private member_ `TObjectPtr<APlayerController> PlayerController;` — `UPROPERTY()`
- L75 _private member_ `TArray<FAvaViewTarget> ViewTargets;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCamera/Public/Transition/Tasks/AvaCameraBlendTask.h` (Public)


#### struct `FAvaCameraBlendInstanceData`  
`struct FAvaCameraBlendInstanceData`  
_L12-23_
- reflection: `USTRUCT()`
- L16 _public prototype_ `FAvaCameraBlendInstanceData();`
- L19 _public member_ `bool bOverrideTransitionParams = false;` — `UPROPERTY(EditAnywhere, Category="Camera")`
- L22 _public member_ `FViewTargetTransitionParams TransitionParams;` — `UPROPERTY(EditAnywhere, Category="Camera", meta=(EditCondition="bOverrideTransitionParams"))`

#### struct `FAvaCameraBlendTask`  
`struct FAvaCameraBlendTask : public FAvaTransitionTask`  
_L26-46_
- reflection: `USTRUCT(DisplayName="Blend Scene Camera", Category="Scene Camera")`
- inherits: `FAvaTransitionTask`
- L30 _public typedef_ `using FInstanceDataType = FAvaCameraBlendInstanceData;`
- L33 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L34 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L38 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`
- L39 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& InContext, const float InDeltaTime) const override;`
- L43 _protected prototype_ `const ULevel* GetTransitionLevel(FStateTreeExecutionContext& InContext) const;`
- L45 _protected member_ `TStateTreeExternalDataHandle<UAvaCameraSubsystem> CameraSubsystemHandle;`
