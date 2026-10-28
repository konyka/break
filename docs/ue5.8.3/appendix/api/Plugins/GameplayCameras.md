# Plugins / GameplayCameras

- module root: `Plugins/Cameras/GameplayCameras/Source/GameplayCameras`
- headers: 242; symbols: 5686
- symbol kinds: class=270, delegate=8, enum=67, enumerator=243, externvar=4, function=790, macro=107, member=1611, namespace=323, prototype=1804, struct=308, typedef=149, variable=2
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, DeveloperSettings, Engine, EnhancedInput, GameplayTags, HeadMountedDisplay, MovieScene, MovieSceneTracks, RewindDebuggerRuntimeInterface, StateTreeModule, TemplateSequence, TraceLog

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/Compat/PostProcessUtils.h` (Private)


#### struct `FPostProcessUtils`  
`struct FPostProcessUtils`  
_L16-20_
- desc: Copy of UE 5.6's FPostProcessUtils class for backwards compatible code. Implementation only supports post process settings that existed up to UE 5.5.
- L18 _public prototype_ `static bool OverridePostProcessSettings(FPostProcessSettings& ThisFrom, const FPostProcessSettings& OtherTo);`
- L19 _public prototype_ `static bool BlendPostProcessSettings(FPostProcessSettings& ThisFrom, const FPostProcessSettings& OtherTo, float BlendFactor);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/Core/BlendStackRootCameraNode.h` (Private)


#### class `UBlendStackRootCameraNode`  
`class UBlendStackRootCameraNode : public UCameraNode`  
_L20-43_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UCameraNode`
- desc: Root camera node for running a camera rig in a blend stack. This camera node wraps both the camera rig's root node, and the blend node used to blend it.
- L26 _public prototype_ `UBlendStackRootCameraNode(const FObjectInitializer& ObjInit);`
- L31 _protected prototype_ `virtual FCameraNodeChildrenView OnGetChildren() override;` — UCameraNode interface.
- L32 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L38 _public member_ `TObjectPtr<UBlendCameraNode> Blend;` — `UPROPERTY()` — The blend to use on the camera rig.
- L42 _public member_ `TObjectPtr<UCameraNode> RootNode;` — `UPROPERTY()` — The root of the instantied camera node tree.

#### enum `UE::Cameras::ECameraRigMergingEligibility`  
`enum class ECameraRigMergingEligibility`  
_L51-56_
- L53 _public enumerator_ `Different`
- L54 _public enumerator_ `EligibleForMerge`
- L55 _public enumerator_ `Active`

#### class `UE::Cameras::FBlendStackRootCameraNodeEvaluator`  
`class FBlendStackRootCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L61-132_
- inherits: `FCameraNodeEvaluator`
- desc: Evaluator for the blend stack entry root node.
- L67 _public prototype_ `FBlendStackRootCameraNodeEvaluator();`
- L69 _public function_ `FBlendCameraNodeEvaluator* GetBlendEvaluator() const`
- L70 _public function_ `FCameraNodeEvaluator* GetRootEvaluator() const`
- L72 _public prototype_ `void SetBlendEvaluator(FBlendCameraNodeEvaluator* InBlendEvaluator);`
- L73 _public prototype_ `void SetRootEvaluator(FCameraNodeEvaluator* InRootEvaluator);`
- L75 _public prototype_ `ECameraRigMergingEligibility CompareCameraRigForMerging(const UCameraRigAsset* CameraRig) const;`
- L77 _public prototype_ `void MergeCameraRig( const FCameraNodeEvaluatorBuildParams& BuildParams, const FCameraNodeEvaluatorInitializeParams& InitParams, FCameraNodeEvaluationResult& InitResult, const UCameraRigAsset* CameraRig, const UBlendCameraNode* Blend);`
- L87 _protected prototype_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren() override;` — FCameraNodeEvaluator interface.
- L88 _protected prototype_ `virtual void OnBuild(const FCameraNodeEvaluatorBuildParams& Params) override;`
- L89 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L90 _protected prototype_ `virtual void OnUpdateParameters(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult) override;`
- L91 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L92 _protected prototype_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector) override;`
- L95 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L102 _private prototype_ `static const UCameraRigAsset* FindInnermostCameraRigPrefab(const UCameraRigAsset* CameraRig);`
- L103 _private prototype_ `static FCameraNodeEvaluator* FindInnermostCameraRigEvaluator(FCameraNodeEvaluator* CameraNodeEvaluator);`
- L105 _private prototype_ `static const UCameraRigAsset* BuildNestedPrefabTrail(const UCameraRigAsset* CameraRig, TArray<TObjectPtr<const UCameraRigCameraNode>>& OutPrefabNodes);`
- L106 _private prototype_ `static FCameraNodeEvaluator* BuildNestedEvaluatorTrail(FCameraNodeEvaluator* CameraNodeEvaluator, TArray<FCameraRigCameraNodeEvaluator*>& OutPrefabEvaluators);`
- L108 _private prototype_ `void InitializeBlendedParameterOverridesStack();`
- L109 _private prototype_ `void RunBlendedParameterOverridesStack(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult);`
- L113 _private member_ `FBlendCameraNodeEvaluator* BlendEvaluator = nullptr;`
- L114 _private member_ `FCameraNodeEvaluator* RootEvaluator = nullptr;`
- L116 _private member_ `TObjectPtr<const UCameraRigAsset> BlendablePrefabCameraRig;`
- L127 _private member_ `TArray<FBlendedParameterOverrides> BlendedParameterOverridesStack;`
- L130 _private member_ `FString CameraRigAssetName;`

#### struct `UE::Cameras::FBlendStackRootCameraNodeEvaluator::FBlendedParameterOverrides`  
`struct FBlendedParameterOverrides`  
_L118-126_
- L120 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;`
- L121 _public member_ `TObjectPtr<const UBlendCameraNode> Blend;`
- L122 _public member_ `TArray<TObjectPtr<const UCameraRigCameraNode>> PrefabTrail;`
- L124 _public member_ `FBlendCameraNodeEvaluator* BlendEvaluator = nullptr;`
- L125 _public member_ `FCameraNodeEvaluationResult Result;`

#### Free symbols / members of external scopes

- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/Core/CameraRigCombinationRegistry.h` (Private)


#### class `UE::Cameras::FCameraRigCombinationRegistry`  
`class FCameraRigCombinationRegistry`  
_L15-48_
- L19 _public prototype_ `const UCameraRigAsset* FindOrCreateCombination(TArrayView<const UCameraRigAsset*> InCombination);`
- L21 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L25 _private typedef_ `using FCameraRigCombination = TArray<TWeakObjectPtr<const UCameraRigAsset>, TInlineAllocator<4>>;`
- L44 _private typedef_ `using FCameraRigCombinationMap = TMap<FCameraRigCombinationKey, int32>;`
- L45 _private member_ `FCameraRigCombinationMap Combinations;`
- L47 _private member_ `TArray<TObjectPtr<const UCameraRigAsset>> CombinedCameraRigs;`

#### struct `UE::Cameras::FCameraRigCombinationRegistry::FCameraRigCombinationKey`  
`struct FCameraRigCombinationKey`  
_L27-32_
- L29 _public prototype_ `FCameraRigCombinationKey(TArrayView<const UCameraRigAsset*> InCombination);`
- L30 _public member_ `FCameraRigCombination Combination;`
- L31 _public member_ `uint32 CachedHash = 0;`

#### class `UCombinedCameraRigsCameraNode`  
`class UCombinedCameraRigsCameraNode : public UCameraNode`  
_L53-71_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UCameraNode`
- L59 _public prototype_ `static void GetAllCombinationCameraRigs(const UCameraRigAsset* InCameraRig, TArray<const UCameraRigAsset*>& OutCameraRigs);`
- L64 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L70 _public member_ `TArray<FCameraRigAssetReference> CameraRigReferences;` — `UPROPERTY()` — The camera rigs to run.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)
- L34 _function_ `friend inline uint32 GetTypeHash(const FCameraRigCombinationKey& Key)` (scope `UE::Cameras`)
- L39 _function_ `friend inline bool operator==(const FCameraRigCombinationKey& A, const FCameraRigCombinationKey& B)` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/Debug/ViewfinderRenderer.h` (Private)


#### enum `UE::Cameras::FViewfinderDrawElements`  
`enum class FViewfinderDrawElements`  
_L15-22_
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `RuleOfThirds = 1 << 0`
- L19 _public enumerator_ `FocusReticle = 1 << 1`
- L21 _public enumerator_ `All = RuleOfThirds | FocusReticle`

#### class `UE::Cameras::FViewfinderRenderer`  
`class FViewfinderRenderer`  
_L26-31_
- L30 _public prototype_ `static void DrawViewfinder(FCameraDebugRenderer& Renderer, FViewfinderDrawElements Elements);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/GameFramework/ViewTargetTransitionParamsBlendNode.h` (Private)


#### class `UViewTargetTransitionParamsBlendCameraNode`  
`class UViewTargetTransitionParamsBlendCameraNode : public USimpleBlendCameraNode`  
_L14-28_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `USimpleBlendCameraNode`
- desc: A blend node that implements the blend algorithms of the FViewTargetTransitionParams.
- L22 _public member_ `FViewTargetTransitionParams TransitionParams;` — `UPROPERTY()` — The transition params to use.
- L27 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/Helpers/CameraObjectInterfaceParameterOverrideHelper.h` (Private)


#### struct `UE::Cameras::FCameraObjectInterfaceParameterOverrideHelper`  
`struct FCameraObjectInterfaceParameterOverrideHelper`  
_L29-87_
- desc: A helper class for applying camera object interface parameter overrides from a property bag, such as with camera asset references, camera rig asset references, and camera shake asset references.
- L39 _public prototype_ `FCameraObjectInterfaceParameterOverrideHelper(FCameraVariableTable* OutVariableTable, FCameraContextDataTable* OutContextDataTable);` — Creates a new helper instance. The given variable or context data tables can be null, in which case blendable or data interface parameters will be skipped.
- L42 _public prototype_ `FCameraObjectInterfaceParameterOverrideHelper(FCameraNodeEvaluationResult& OutResult);` — Creates a new helper instance.
- L47 _public prototype_ `void ApplyParameters( const UBaseCameraObject* CameraObject, const FInstancedPropertyBag& Parameters);` — Sets all values of interface parameters in the given variable and context data tables.
- L52 _public prototype_ `void ApplyParameterOverrides( const UBaseCameraObject* CameraObject, const FInstancedOverridablePropertyBag& ParameterOverrides);` — Sets overriden values of interface parameters in the given variable and context data tables.
- L57 _public prototype_ `void ApplyParameterDefaults( const UBaseCameraObject* CameraObject, bool bUnwrittenOnly = true);` — Sets all of the given object's default parameter values in the given variable and context data tables.
- L64 _public prototype_ `void ApplyFilteredParameters( const UObject* CameraObject, TConstArrayView<FCameraObjectInterfaceParameterDefinition> ParameterDefinitions, const FInstancedPropertyBag& ParameterOverrides, TFunctionRef<bool(const FCameraObjectInterfaceParameterDefinition&)> ParameterFilter);` — Sets the parameter values for those that pass the given filter.
- L72 _private prototype_ `void ApplyParameterValue( const UObject* CameraObject, const FCameraObjectInterfaceParameterDefinition& ParameterDefinition, const FInstancedPropertyBag& PropertyBag, const FPropertyBagPropertyDesc& PropertyBagPropertyDesc);`
- L81 _public member_ `bool bDrivenOnly = false;` — Only parameters that are dynamicaly driven should be applied.
- L85 _private member_ `FCameraVariableTable* VariableTable;`
- L86 _private member_ `FCameraContextDataTable* ContextDataTable;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/Helpers/CameraRigTransitionFinder.h` (Private)


#### class `UE::Cameras::FCameraRigTransitionFinder`  
`class FCameraRigTransitionFinder`  
_L20-29_
- desc: Helper class for finding a camera rig transition that matches a given situation.
- L23 _public prototype_ `static const UCameraRigTransition* FindTransition( TArrayView<const TObjectPtr<UCameraRigTransition>> Transitions, TSharedPtr<const FCameraEvaluationContext> FromEvaluationContext, const UCameraRigAsset* FromCameraRig, const UCameraAsset* FromCameraAsset, bool bFromFrozen, TSharedPtr<const FCameraEvaluationContext> ToEvaluationContext, const UCameraRigAsset* ToCameraRig, const UCameraAsset* ToCameraAsset);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/MovieScene/MovieSceneCameraFramingZonePropertySystem.h` (Private)


#### class `UMovieSceneCameraFramingZonePropertySystem`  
`class UMovieSceneCameraFramingZonePropertySystem : public UMovieScenePropertySystem`  
_L13-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L19 _public prototype_ `UMovieSceneCameraFramingZonePropertySystem(const FObjectInitializer& ObjInit);`
- L21 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

#### Free symbols / members of external scopes

- L10 _prototype_ `Expose_TNameOf(FCameraFramingZone);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/MovieScene/MovieSceneGameplayCamerasComponentTypes.h` (Private)


#### struct `UE::Cameras::FMovieSceneGameplayCamerasComponentTypes`  
`struct FMovieSceneGameplayCamerasComponentTypes`  
_L31-48_
- L33 _public prototype_ `~FMovieSceneGameplayCamerasComponentTypes();`
- L35 _public member_ `UE::MovieScene::TComponentTypeID<FGuid> CameraParameterOverrideID;`
- L37 _public member_ `UE::MovieScene::TPropertyComponents<FCameraFramingZoneTraits> CameraFramingZone;`
- L39 _public member_ `UE::MovieScene::TCustomPropertyRegistration<FCameraFramingZoneTraits, 1> CustomCameraFramingZoneAccessors;`
- L41 _public prototype_ `static void Destroy();`
- L43 _public prototype_ `static FMovieSceneGameplayCamerasComponentTypes* Get();`
- L47 _private prototype_ `FMovieSceneGameplayCamerasComponentTypes();`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieScene` (scope `UE`)
- L21 _prototype_ `void UnpackChannelsFromOperational(FCameraFramingZone InZone, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Cameras` (scope `UE`)
- L29 _typedef_ `using FCameraFramingZoneTraits = UE::MovieScene::TDirectPropertyTraits<FCameraFramingZone>;` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Private/Nodes/Input/InputAxisBindingHelpers.h` (Private)


#### class `UE::Cameras::FInputAxisBindingHelpers`  
`class FInputAxisBindingHelpers`  
_L20-34_
- L24 _public prototype_ `static UEnhancedInputComponent* FindInputComponent(const UE::Cameras::FCameraNodeEvaluatorInitializeParams& Params);`
- L26 _public prototype_ `static void BindActionValues( const UE::Cameras::FCameraNodeEvaluatorInitializeParams& Params, const UCameraNode* CameraNode, UEnhancedInputComponent* InputComponent, const TArray<TObjectPtr<UInputAction>>& AxisActions, TArray<FEnhancedInputActionValueBinding*>& OutAxisValueBindings);`
- L33 _public prototype_ `static FVector2d GetHighestValue(const TArray<FEnhancedInputActionValueBinding*>& AxisValueBindings);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Actions/AimAtActorCameraAction.h` (Public)


#### class `UAimAtActorCameraAction`  
`class UAimAtActorCameraAction : public UBaseAimAtCameraAction`  
_L13-35_
- reflection: `UCLASS()`
- inherits: `UBaseAimAtCameraAction`
- desc: A camera action that aims at a given target, using a given interpolation.
- L21 _public member_ `TObjectPtr<AActor> TargetActor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Aiming", meta=(ExposeOnSpawn=true))` — The actor to attach to.
- L25 _public member_ `FName TargetSocketName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Aiming", meta=(ExposeOnSpawn=true))` — An optional socket to attach to on the actor.
- L29 _public member_ `FName TargetBoneName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Aiming", meta=(ExposeOnSpawn=true))` — An optional bone to attach to on the actor.
- L34 _protected prototype_ `virtual FCameraActionEvaluatorPtr OnBuildEvaluator(FCameraActionEvaluatorBuilder& Builder) const override;` — UCameraAction interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Actions/AimAtCameraAction.h` (Public)


#### class `UAimAtCameraAction`  
`class UAimAtCameraAction : public UBaseAimAtCameraAction`  
_L13-27_
- reflection: `UCLASS()`
- inherits: `UBaseAimAtCameraAction`
- desc: A camera action that aims at a given target, using a given interpolation.
- L21 _public member_ `FVector TargetLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Common, meta=(ExposeOnSpawn=true))` — The target to aim at.
- L26 _protected prototype_ `virtual FCameraActionEvaluatorPtr OnBuildEvaluator(FCameraActionEvaluatorBuilder& Builder) const override;` — UCameraAction interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Actions/BaseAimAtCameraAction.h` (Public)


#### enum `EAimAtCameraActionLockOnPolicy`  
`enum class EAimAtCameraActionLockOnPolicy : uint8`  
_L14-20_
- reflection: `UENUM()`
- desc: Lock-on policy for the aim-at camera action.
- L17 _public enumerator_ `Disengage` — End the action once the aiming is accomplished.
- L19 _public enumerator_ `KeepLock` — Continuously aim at the target until the action is explicitly stopped.

#### class `UBaseAimAtCameraAction`  
`class UBaseAimAtCameraAction : public UCameraAction`  
_L26-47_
- reflection: `UCLASS()`
- inherits: `UCameraAction`
- desc: The base class for all aiming camera actions.
- L34 _public member_ `TObjectPtr<UCameraValueInterpolator> Interpolator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Common, meta=(ExposeOnSpawn=true))` — The interpolation to use for aiming.
- L38 _public member_ `float LockOnAngleTolerance = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Common, meta=(ExposeOnSpawn=true))` — The tolerance within which we can consider the aiming to be locked on target.
- L42 _public member_ `EAimAtCameraActionLockOnPolicy LockOnPolicy = EAimAtCameraActionLockOnPolicy::Disengage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Common, meta=(ExposeOnSpawn=true))` — The lock-on policy.
- L46 _public member_ `FVector2D TargetFraming = { 0.5, 0.5 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aiming, meta=(ExposeOnSpawn=true))` — Where to aim the target in screen-space.

#### class `UE::Cameras::FBaseAimAtCameraActionEvaluator`  
`class FBaseAimAtCameraActionEvaluator : public FCameraActionEvaluator`  
_L55-106_
- inherits: `FCameraActionEvaluator`
- desc: Base class for any aiming camera action evaluator.
- L62 _protected prototype_ `virtual void OnInitialize(const FCameraActionEvaluatorInitializeParams& Params, FCameraActionEvaluationResult& OutResult) override;` — FCameraActionEvaluator
- L63 _protected prototype_ `virtual void OnPreScopeRun(const FCameraActionEvaluationParams& Params, FCameraActionEvaluationResult& OutResult) override;`
- L64 _protected prototype_ `virtual void OnSerialize(const FCameraActionEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L66 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L72 _protected prototype_ `virtual FVector3d UpdateTargetLocation(const FCameraActionEvaluationParams& Params, const FCameraActionEvaluationResult& Result);` — FBaseAimAtCameraActionEvaluator
- L76 _private prototype_ `void LockUserInputThisFrame(const FCameraActionEvaluationParams& Params);`
- L77 _private prototype_ `void RunPreviewEvaluation(const FCameraActionEvaluationParams& Params, const FCameraNodeEvaluationResult& Result);`
- L78 _private prototype_ `bool ComputeDesiredCorrection(const FCameraActionEvaluationParams& Params, FRotator3d& OutCorrection);`
- L79 _private prototype_ `bool ExecuteYawPitchCorrection(const FCameraActionEvaluationParams& Params, const FRotator3d& Correction);`
- L81 _private prototype_ `bool ContinueAimAction(const FCameraActionEvaluationParams& Params, FCameraActionEvaluationResult& OutResult);`
- L82 _private prototype_ `bool KeepLockOn(const FCameraActionEvaluationParams& Params, FCameraActionEvaluationResult& OutResult);`
- L86 _private member_ `TUniquePtr<TCameraValueInterpolator<FVector2d>> Interpolator;`
- L88 _private member_ `FCameraNodeEvaluatorHierarchy ChildHierarchy;`
- L90 _private member_ `FCameraNodeEvaluationResult ScratchResult;`
- L91 _private member_ `TArray<uint8> EvaluatorSnapshot;`
- L93 _private member_ `FVector3d TargetLocation;`
- L94 _private member_ `FVector2d TargetFraming = { 0.5, 0.5 };`
- L96 _private member_ `bool bIsLockedOn = false;`
- L99 _private member_ `float DebugElapsedTime = 0.f;`
- L100 _private member_ `FRotator3d DebugCorrectionLeft;`
- L101 _private member_ `FRotator3d DebugCurrentCorrection;`
- L102 _private member_ `FVector3d DebugTargetFramingAim;`
- L103 _private member_ `FVector3d DebugCameraLocation;`
- L104 _private member_ `FVector3d DebugCameraAim;`

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraAssetAssembleUtils.h` (Public)


#### struct `UE::Cameras::TScopedConstruction`  
`template<typename ParentType> struct TScopedConstruction`  
_L35-47_
- desc: Template mix-in for adding "go back to parent" support to an assembler class.
- L37 _public function_ `TScopedConstruction(ParentType& InParent) : Parent(InParent)`
- L42 _public function_ `ParentType& Done()` — Return the parent assembler instance.
- L46 _protected member_ `ParentType& Parent;`

#### struct `UE::Cameras::TCameraObjectInitializer`  
`template<typename ObjectType> struct TCameraObjectInitializer`  
_L54-84_
- desc: A generic utility class that defines a fluent interface for setting properties and adding items to array properties on a given object.
- L58 _public function_ `template<typename PropertyType> TCameraObjectInitializer<ObjectType>& Set(PropertyType ObjectType::*Field, typename TCallTraits<PropertyType>::ParamType Value)` — Sets a value on the given public property (via its member field).
- L67 _public function_ `template<typename ItemType> TCameraObjectInitializer<ObjectType>& Add(TArray<ItemType> ObjectType::*Field, typename TCallTraits<ItemType>::ParamType NewItem)` — Adds an item to a given public array property (via its member field).
- L76 _protected function_ `void SetObject(ObjectType* InObject)`
- L83 _private member_ `ObjectType* Object = nullptr;`

#### class `UE::Cameras::FNamedObjectRegistry`  
`class FNamedObjectRegistry : public TSharedFromThis<FNamedObjectRegistry>`  
_L89-122_
- inherits: `TSharedFromThis<FNamedObjectRegistry>`
- desc: A simple repository matching UObject instances to names.
- L94 _public function_ `void Register(UObject* InObject, const FString& InName)` — Adds an object to the repository.
- L103 _public function_ `UObject* Get(const FString& InName) const` — Gets an object from the repository.
- L114 _public function_ `template<typename ObjectClass> ObjectClass* Get(const FString& InName) const` — Gets an object from the repository with a call to CastChecked.
- L121 _private member_ `TMap<FString, UObject*> NamedObjects;`

#### struct `UE::Cameras::IHasNamedObjectRegistry`  
`struct IHasNamedObjectRegistry`  
_L127-132_
- desc: Interface for something that has access to a named object repository.
- L129 _public prototype_ `virtual ~IHasNamedObjectRegistry() = default;`
- L131 _public prototype_ `virtual TSharedPtr<FNamedObjectRegistry> GetNamedObjectRegistry() = 0;`

#### class `UE::Cameras::TCameraNodeAssembler`  
`class TCameraNodeAssembler : public TScopedConstruction<ParentType> , public TCameraObjectInitializer<NodeType> , public IHasNamedObjectRegistry`  
_L142-291_
- inherits: `TScopedConstruction<ParentType>,TCameraObjectInitializer<NodeType>,IHasNamedObjectRegistry`
- L149 _public typedef_ `using ThisType = TCameraNodeAssembler<ParentType, NodeType, V>;`
- L152 _public function_ `TCameraNodeAssembler(ParentType& InParent, UObject* Outer = nullptr) : TScopedConstruction<ParentType>(InParent)` — Creates a new instance of this assembler class.
- L164 _public function_ `NodeType* Get() const` — Gets the built camera node.
- L167 _public function_ `ThisType& Pin(NodeType*& OutPtr)` — Pins the built camera node to a given pointer, for being able to later refer to it.
- L171 _public function_ `template<typename VV = std::enable_if_t<TPointerIsConvertibleFromTo<ParentType, IHasNamedObjectRegistry>::Value>> ThisType& Named(const TCHAR* InName)` — Give a name to the built camera node, to be recalled later.
- L183 _public function_ `template<typename ParameterType> ThisType& SetParameter( ParameterType NodeType::*ParameterField, typename TCallTraits<typename ParameterType::ValueType>::ParamType Value)` — Sets the value of a camera parameter field on the camera node.
- L195 _public function_ `ThisType& Setup(TFunction<void(NodeType*)> SetupCallback)` — Runs a custom setup callback on the camera node.
- L204 _public function_ `ThisType& Setup(TFunction<void(NodeType*, FNamedObjectRegistry*)> SetupCallback)` — Runs a custom setup callback on the camera node with the named object registry provided.
- L222 _public function_ `AddChild(TArray<TObjectPtr<ArrayItemType>> NodeType::*ArrayField)`
- L240 _public function_ `AddArrayChild()`
- L256 _public function_ `operator TCameraNodeAssembler<ParentType, OtherNodeType>() const`
- L265 _public function_ `virtual TSharedPtr<FNamedObjectRegistry> GetNamedObjectRegistry() override` — Gets the named object registry from the parent.
- L281 _private function_ `TCameraNodeAssembler(EForceReuseCameraNode ForceReuse, ParentType& InParent, NodeType* ExistingCameraNode) : TScopedConstruction<ParentType>(InParent) , CameraNode(ExistingCameraNode)`
- L290 _private member_ `NodeType* CameraNode;`

#### enum `UE::Cameras::TCameraNodeAssembler::EForceReuseCameraNode`  
`enum class EForceReuseCameraNode`  
_L279-279_
- L279 _public enumerator_ `enum class EForceReuseCameraNode { Yes }; TCameraNodeAssembler(EForceReuseCameraNode ForceReuse, ParentType& InParent, NodeType* ExistingCameraNode) : TScopedConstruction<ParentType>(InParent)`

#### class `UE::Cameras::TCameraRigTransitionAssembler`  
`template<typename ParentType> class TCameraRigTransitionAssembler : public TScopedConstruction<ParentType> , public TCameraObjectInitializer<UCameraRigTransition> , public IHasNamedObjectRegistry`  
_L297-393_
- inherits: `TScopedConstruction<ParentType>,TCameraObjectInitializer<UCameraRigTransition>,IHasNamedObjectRegistry`
- desc: Assembler class for camera rig transitions.
- L304 _public typedef_ `using ThisType = TCameraRigTransitionAssembler<ParentType>;`
- L307 _public function_ `TCameraRigTransitionAssembler(ParentType& InParent, UObject* Outer = nullptr) : TScopedConstruction<ParentType>(InParent)` — Creates a new instance of this assembler class.
- L320 _public function_ `UCameraRigTransition* Get() const` — Gets the built transition object.
- L323 _public function_ `ThisType& Pin(UCameraRigTransition*& OutPtr)` — Pins the built transition to a given pointer, for being able to later refer to it.
- L327 _public function_ `template<typename VV = std::enable_if_t<TPointerIsConvertibleFromTo<ParentType, IHasNamedObjectRegistry>::Value>> ThisType& Named(const TCHAR* InName)` — Give a name to the built transition, to be recalled later.
- L345 _public function_ `TCameraNodeAssembler<ThisType, BlendType> MakeBlend()`
- L357 _public function_ `ThisType& AddCondition()`
- L369 _public function_ `ThisType& AddCondition(TFunction<void(ConditionType*)> SetupCallback)`
- L378 _public function_ `virtual TSharedPtr<FNamedObjectRegistry> GetNamedObjectRegistry() override` — Gets the named object registry from the parent.
- L392 _private member_ `UCameraRigTransition* Transition;`

#### class `UE::Cameras::TCameraRigAssetAssemblerBase`  
`template<typename ThisType> class TCameraRigAssetAssemblerBase : public TCameraObjectInitializer<UCameraRigAsset> , public IHasNamedObjectRegistry`  
_L416-756_
- inherits: `TCameraObjectInitializer<UCameraRigAsset>,IHasNamedObjectRegistry`
- desc: The root assembler class for building a camera rig. Follow the fluent interface to construct the hierarchy of camera nodes, add transitions, etc. For instance: UCameraRigAsset* CameraRig = FCameraRigAssetAssembler(TEXT("SimpleTest")) .MakeRootNode<UArrayCameraNode>() .AddChild<UOffsetCameraNode>(&UArrayCameraNode::Children) .SetParameter(&UOffsetCameraNode::TranslationOffset, FVector3d{ 1, 0, 0 }) .Done() .AddChild<ULensParametersCameraNode>(&UArrayCameraNode::Children) .SetParameter(&ULensParametersCameraNode::FocalLength, 18.f) .Done() .Done() .AddEnterTransition() .MakeBlend<USmoothBlendCameraNode>() .Done() .Get();
- L423 _public function_ `UCameraRigAsset* Get()` — Gets the built camera rig.
- L426 _public function_ `ThisType& Pin(UCameraRigAsset*& OutPtr)` — Pins the built camera rig to a given pointer, for being able to later refer to it.
- L433 _public function_ `ThisType& Named(const TCHAR* InName)` — Give a name to the built camera rig, to be recalled later.
- L448 _public function_ `template<typename NodeType> TCameraNodeAssembler<ThisType, NodeType> MakeRootNode()` — Creates a new camera node and sets it as the root node of the rig. Returns the assembler for the root camera node. You can come back to the rig assembler by calling Done() on the node assembler.
- L459 _public function_ `TCameraNodeAssembler<ThisType, UArrayCameraNode> MakeArrayRootNode()` — A convenience method that calls MakeRootNode with a UArrayCameraNode.
- L468 _public function_ `TCameraRigTransitionAssembler<ThisType> AddEnterTransition()` — Adds a new enter transition and returns an assembler for it. You can come back to the rig assembler by calling Done() on the transition assembler.
- L479 _public function_ `TCameraRigTransitionAssembler<ThisType> AddExitTransition()` — Adds a new exit transition and returns an assembler for it. You can come back to the rig assembler by calling Done() on the transition assembler.
- L493 _public function_ `ThisType& AddBlendableParameter(const FString& ParameterName, ECameraVariableType ParameterType, UCameraNode* Target, FName TargetPropertyName)` — Creates a new exposed rig parameter and hooks it up to the given camera node's property. When building the node hierarchy, you can use the Pin() method on the node assemblers to save a pointer to nodes you need for ExposeParameter(). The created parameter is automatically stored in the named object registry under its name.
- L515 _public function_ `ThisType& AddBlendableParameter(const FString& ParameterName, ECameraVariableType ParameterType, const FString& TargetName, FName TargetPropertyName)` — A variant of ExposeParameter that retrieves the target node from the named registry. The created parameter is automatically stored in the named object registry under its name.
- L529 _public function_ `ThisType& AddDataParameter(const FString& ParameterName, TSubclassOf<UObject> ObjectClass, UCameraNode* Target, FName TargetPropertyName)` — Creates a new exposed rig parameter and hooks it up to the given camera node's property. When building the node hierarchy, you can use the Pin() method on the node assemblers to save a pointer to nodes you need for ExposeParameter(). The created parameter is automatically stored in the named object registry under its name.
- L555 _public function_ `ThisType& AddDataParameter(const FString& ParameterName, const UScriptStruct* InScriptStruct, UCameraNode* Target, FName TargetPropertyName)` — Creates a new exposed rig parameter and hooks it up to the given camera node's property. When building the node hierarchy, you can use the Pin() method on the node assemblers to save a pointer to nodes you need for ExposeParameter(). The created parameter is automatically stored in the named object registry under its name.
- L579 _public function_ `ThisType& AddDataParameter(const FString& ParameterName, TSubclassOf<UObject> ObjectClass, const FString& TargetName, FName TargetPropertyName)` — A variant of AddDataParameter that retrieves the target node from the named registry. The created parameter is automatically stored in the named object registry under its name.
- L591 _public function_ `ThisType& AddDataParameter(const FString& ParameterName, const UScriptStruct* InScriptStruct, const FString& TargetName, FName TargetPropertyName)` — A variant of AddDataParameter that retrieves the target node from the named registry. The created parameter is automatically stored in the named object registry under its name.
- L599 _public function_ `ThisType& Setup(TFunction<void(UCameraRigAsset*)> SetupCallback)` — Runs arbitrary setup logic on the camera rig.
- L606 _public function_ `ThisType& Setup(TFunction<void(UCameraRigAsset*, FNamedObjectRegistry*)> SetupCallback)` — Runs arbitrary setup logic on the camera rig.
- L615 _public function_ `ThisType& BuildCameraRig()` — Builds the camera rig.
- L626 _public function_ `template<typename ValueType> ThisType& SetDefaultParameterValue(const FName ParameterName, TCallTraits<ValueType>::ParamType ParameterValue)` — Sets the default value for a camera rig parameter. Requires that the camera rig has been built first.
- L689 _public function_ `virtual TSharedPtr<FNamedObjectRegistry> GetNamedObjectRegistry() override` — Gets the named object registry.
- L696 _protected function_ `TCameraRigAssetAssemblerBase(TSharedPtr<FNamedObjectRegistry> InNamedObjectRegistry, FName Name = NAME_None, UObject* Outer = nullptr)`
- L703 _private function_ `void Initialize(TSharedPtr<FNamedObjectRegistry> InNamedObjectRegistry, FName Name, UObject* Outer)`
- L723 _private prototype_ `template<typename ValueType> void SetDefaultBlendableParameterValue(const FCameraObjectInterfaceParameterDefinition& ParameterDefinition, void* TargetAddress, ValueType ParameterValue);`
- L742 _private function_ `template <typename ValueType> static constexpr bool IsSupportedBlendableParameterType()`
- L750 _private prototype_ `UE_CAMERA_VARIABLE_FOR_ALL_TYPES() #undef UE_CAMERA_VARIABLE_FOR_TYPE UCameraRigAsset* CameraRig;`
- L755 _private member_ `TSharedPtr<FNamedObjectRegistry> NamedObjectRegistry;`

#### class `UE::Cameras::FCameraRigAssetAssembler`  
`class FCameraRigAssetAssembler : public TCameraRigAssetAssemblerBase<FCameraRigAssetAssembler>`  
_L761-768_
- inherits: `TCameraRigAssetAssemblerBase<FCameraRigAssetAssembler>`
- desc: Default version of the camera rig asset assembler.
- L766 _public prototype_ `FCameraRigAssetAssembler(FName Name = NAME_None, UObject* Outer = nullptr);`
- L767 _public prototype_ `FCameraRigAssetAssembler(TSharedPtr<FNamedObjectRegistry> InNamedObjectRegistry, FName Name = NAME_None, UObject* Outer = nullptr);`

#### class `UE::Cameras::TScopedCameraRigAssetAssembler`  
`template<typename ParentType> class TScopedCameraRigAssetAssembler : public TScopedConstruction<ParentType> , public TCameraRigAssetAssemblerBase<TScopedCameraRigAssetAssembler<ParentType>>`  
_L775-792_
- inherits: `TScopedConstruction<ParentType>,TCameraRigAssetAssemblerBase<TScopedCameraRigAssetAssembler<ParentType>>`
- desc: Version of the camera rig asset assembler that has a scoped parent, with a Done() method exposed to go back to it.
- L781 _public function_ `TScopedCameraRigAssetAssembler(ParentType& InParent, FName Name = NAME_None, UObject* Outer = nullptr) : TScopedConstruction<ParentType>(InParent) , TCameraRigAssetAssemblerBase<TScopedCameraRigAssetAssembler<ParentType>>(Name, Outer)`
- L787 _public function_ `TScopedCameraRigAssetAssembler(ParentType& InParent, TSharedPtr<FNamedObjectRegistry> InNamedObjectRegistry, FName Name = NAME_None, UObject* Outer = nullptr) : TScopedConstruction<ParentType>(InParent) , TCameraRigAssetAssemblerBase<TScopedCameraRigAssetAssembler<ParentType>>(InNamedObjectRegistry, Name, Outer)`

#### class `UE::Cameras::TCameraDirectorAssembler`  
`class TCameraDirectorAssembler : public TScopedConstruction<ParentType> , public TCameraObjectInitializer<DirectorType> , public IHasNamedObjectRegistry`  
_L802-883_
- inherits: `TScopedConstruction<ParentType>,TCameraObjectInitializer<DirectorType>,IHasNamedObjectRegistry`
- L809 _public typedef_ `using ThisType = TCameraDirectorAssembler<ParentType, DirectorType, V>;`
- L812 _public function_ `TCameraDirectorAssembler(ParentType& InParent, UObject* Outer = nullptr) : TScopedConstruction<ParentType>(InParent)` — Creates a new instance of this assembler class.
- L824 _public function_ `UCameraDirector* Get() const` — Gets the build camera director.
- L827 _public function_ `ThisType& Pin(DirectorType*& OutPtr)` — Pins the built camera director to a given pointer, for being able to later refer to it.
- L831 _public function_ `template<typename VV = std::enable_if_t<TPointerIsConvertibleFromTo<ParentType, IHasNamedObjectRegistry>::Value>> ThisType& Named(const TCHAR* InName)` — Give a name to the built camera drector, to be recalled later.
- L843 _public function_ `template<typename ParameterType> ThisType& SetParameter( ParameterType DirectorType::*ParameterField, typename TCallTraits<typename ParameterType::ValueType>::ParamType Value)` — Set a parameter on the camera director.
- L853 _public function_ `ThisType& Setup(TFunction<void(DirectorType*)> SetupCallback)` — Runs arbitrary setup logic on the camera director.
- L860 _public function_ `ThisType& Setup(TFunction<void(DirectorType*, FNamedObjectRegistry*)> SetupCallback)` — Runs arbitrary setup logic on the camera director.
- L868 _public function_ `virtual TSharedPtr<FNamedObjectRegistry> GetNamedObjectRegistry() override` — Gets the named object registry from the parent.
- L882 _private member_ `DirectorType* CameraDirector;`

#### class `UE::Cameras::FCameraAssetAssembler`  
`class FCameraAssetAssembler : public TCameraObjectInitializer<UCameraAsset> , public IHasNamedObjectRegistry`  
_L888-960_
- inherits: `TCameraObjectInitializer<UCameraAsset>,IHasNamedObjectRegistry`
- desc: Assembler class for a camera asset.
- L894 _public typedef_ `using ThisType = FCameraAssetAssembler;`
- L897 _public prototype_ `FCameraAssetAssembler(UObject* Owner = nullptr);` — Create a new instance of this assembler class.
- L900 _public function_ `UCameraAsset* Get() const` — Gets the created camera asset.
- L904 _public function_ `template<typename DirectorType> TCameraDirectorAssembler<ThisType, DirectorType> MakeDirector()` — Builds a new camera director of the given type and returns an assembler object for its.
- L915 _public function_ `ThisType& AddInterfaceParameter(UCameraRigAsset* SourceCameraRig, const FName SourceParameterName, const FString& InterfaceParameterName)` — Creates a new interface parameter that exposes the given camera rig parameter, optionally under a different name.
- L931 _public function_ `ThisType& AddInterfaceParameter(UCameraRigAsset* SourceCameraRig, const FName SourceParameterName)`
- L936 _public function_ `ThisType& AddInterfaceParameter(const FString& SourceCameraRigName, const FName& SourceParameterName, const FString& InterfaceParameterName)`
- L944 _public function_ `ThisType& AddInterfaceParameter(const FString& SourceCameraRigName, const FName SourceParameterName)`
- L950 _public function_ `virtual TSharedPtr<FNamedObjectRegistry> GetNamedObjectRegistry() override` — Gets the named object registry.
- L957 _private member_ `UCameraAsset* CameraAsset;`
- L959 _private member_ `TSharedPtr<FNamedObjectRegistry> NamedObjectRegistry;`

#### class `UE::Cameras::FCameraEvaluationContextAssembler`  
`class FCameraEvaluationContextAssembler : public TCameraObjectInitializer<FCameraEvaluationContext> , public IHasNamedObjectRegistry`  
_L965-1059_
- inherits: `TCameraObjectInitializer<FCameraEvaluationContext>,IHasNamedObjectRegistry`
- desc: Assembler class for a camera evaluation context and its camera asset.
- L971 _public typedef_ `using ThisType = FCameraEvaluationContextAssembler;`
- L974 _public prototype_ `FCameraEvaluationContextAssembler(UObject* Owner = nullptr);` — Creates a new instance of this assembler class.
- L977 _public function_ `TSharedRef<FCameraEvaluationContext> Get() const` — Gets the created evaluation context.
- L980 _public function_ `ThisType& PinCameraAsset(UCameraAsset*& OutPtr)` — Pins the created camera asset.
- L983 _public function_ `ThisType& BuildCameraAsset()` — Builds the camera asset.
- L987 _public function_ `template<typename DirectorType> TCameraDirectorAssembler<ThisType, DirectorType> MakeDirector()` — Builds a new camera director of the given type and returns an assembler object for its.
- L995 _public function_ `TCameraDirectorAssembler<ThisType, USingleCameraDirector> MakeSingleDirector()` — Builds a new single camera director and returns an assembler object for its.
- L1001 _public function_ `TCameraDirectorAssembler<ThisType, USingleCameraDirector> MakeSingleDirector(UCameraRigAsset* InCameraRig)` — Builds a new single camera director, set its camera rig, and returns an assembler object for its.
- L1012 _public function_ `TCameraDirectorAssembler<ThisType, USingleCameraDirector> MakeSingleDirector(const FString& InCameraRigName)` — Builds a new single camera director, set its camera rig to the named object, and returns an assembler object for its.
- L1025 _public function_ `TScopedCameraRigAssetAssembler<ThisType> CreateCameraRig(FName Name = NAME_None)` — Creates a new camera rig asset assembler and gives it a name to be recalled later.
- L1032 _public function_ `ThisType& Setup(TFunction<void(TSharedRef<FCameraEvaluationContext>)> SetupCallback)` — Runs arbitrary setup logic on the evaluation context.
- L1039 _public function_ `ThisType& Setup(TFunction<void(TSharedRef<FCameraEvaluationContext>, FNamedObjectRegistry*)> SetupCallback)` — Runs arbitrary setup logic on the evaluation context.
- L1047 _public function_ `virtual TSharedPtr<FNamedObjectRegistry> GetNamedObjectRegistry() override` — Gets the named object registry.
- L1054 _private member_ `UCameraAsset* CameraAsset;`
- L1056 _private member_ `TSharedPtr<FCameraEvaluationContext> EvaluationContext;`
- L1058 _private member_ `TSharedPtr<FNamedObjectRegistry> NamedObjectRegistry;`

#### class `UE::Cameras::FCameraSystemEvaluatorAssembler`  
`class FCameraSystemEvaluatorAssembler`  
_L1064-1075_
- desc: Assembler class for a camera system evaluator.
- L1069 _public function_ `static TSharedRef<FCameraSystemEvaluator> Build(UObject* OwnerObject = nullptr)` — Makes a new camera system evaluator.

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Cameras` (scope `UE`)
- L630 _function_ `` (scope `UE::Cameras::TCameraRigAssetAssemblerBase::SetDefaultParameterValue`)
- L725 _macro_ `#define UE_CAMERA_VARIABLE_FOR_TYPE(ValueType, ValueName)\`
- L1005 _function_ `` (scope `UE::Cameras::FCameraEvaluationContextAssembler::MakeSingleDirector`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraAssetBuilder.h` (Public)


#### class `UE::Cameras::FCameraAssetBuilder`  
`class FCameraAssetBuilder`  
_L21-56_
- desc: A class that can prepare a camera asset for runtime use.
- L26 _public prototype_ `FCameraAssetBuilder(FCameraBuildContext& InBuildContext);` — Creates a new camera builder.
- L29 _public prototype_ `void BuildCamera(UCameraAsset* InCameraAsset, bool bBuildReferencedAssets = true);` — Builds the given camera.
- L32 _public function_ `TConstArrayView<UObject*> GetBuiltReferencedAssets() const` — Gets the last built referenced assets.
- L38 _public prototype_ `static bool BuildDefaultInterfaceIfNeeded(UCameraAsset* InCameraAsset);`
- L42 _private prototype_ `void BuildCameraImpl(bool bBuildReferencedAssets);`
- L44 _private prototype_ `void BuildParameters();`
- L45 _private prototype_ `void CopyDefaultParameterValue(const UCameraRigAsset* InCameraRig, const FGuid& PropertyID, FInstancedPropertyBag& DefaultParameters);`
- L47 _private prototype_ `void UpdateBuildStatus();`
- L51 _private member_ `FCameraBuildContext BuildContext;`
- L53 _private member_ `UCameraAsset* CameraAsset = nullptr;`
- L55 _private member_ `TArray<UObject*> BuiltReferencedAssets;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraBuildContext.h` (Public)


#### enum `UE::Cameras::ECameraBuildReason`  
`enum ECameraBuildReason`  
_L10-20_
- L13 _public enumerator_ `Undefined` — The reason for this build is undefined.
- L15 _public enumerator_ `UserAction` — A user clicked on the Build button, or similar.
- L17 _public enumerator_ `Cooking` — The build is happening during cooking.
- L19 _public enumerator_ `StartingPIE` — The build is happening for starting PIE.

#### struct `UE::Cameras::FCameraBuildContext`  
`struct FCameraBuildContext`  
_L25-46_
- desc: Camera build context.
- L27 _public function_ `FCameraBuildContext(FCameraBuildLog& InBuildLog, ECameraBuildReason InBuildReason = ECameraBuildReason::Undefined) : BuildLog(InBuildLog) , BuildReason(InBuildReason)`
- L33 _public member_ `FCameraBuildLog& BuildLog;` — The build log for emitting messages.
- L36 _public function_ `ECameraBuildReason GetBuildReason() const` — The reason for this build.
- L41 _public function_ `bool IsCooking() const` — Whether the build reason is for cooking.
- L45 _private member_ `ECameraBuildReason BuildReason = ECameraBuildReason::Undefined;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraBuildLog.h` (Public)


#### struct `UE::Cameras::FCameraBuildLogMessage`  
`struct FCameraBuildLogMessage`  
_L17-30_
- desc: A message emitted by a camera build process.
- L20 _public member_ `EMessageSeverity::Type Severity = EMessageSeverity::Info;` — Severity of the message.
- L22 _public member_ `const UObject* Object = nullptr;` — An optional object that the message relates to.
- L24 _public member_ `FText Text;` — The actual message.
- L27 _public prototype_ `FString ToString() const;` — Generates a plain string representation of this message.
- L29 _public prototype_ `void SendToLogging(const FString& InLoggingPrefix) const;` — Sends a string version of this message to the LogCameraSystem console log.

#### class `UE::Cameras::FCameraBuildLog`  
`class FCameraBuildLog`  
_L35-76_
- desc: Build log, populated when building a camera rig, or other camera asset.
- L44 _public prototype_ `void SetLoggingPrefix(const FString& InPrefix);` — Sets a string that will be prefixed to all messages sent to the console. Only useful when IsForwardingMessagesToLogging is true. This is generally set to the name of the camera asset being built.
- L47 _public function_ `bool IsForwardingMessagesToLogging() const` — Returns whether build messages are sent to the console.
- L49 _public prototype_ `void SetForwardMessagesToLogging(bool bInForwardToLogging);` — Sets whether build messages are sent to the console.
- L52 _public prototype_ `void AddMessage(EMessageSeverity::Type InSeverity, FText&& InText);` — Adds a new message.
- L54 _public prototype_ `void AddMessage(EMessageSeverity::Type InSeverity, const UObject* InObject, FText&& InText);` — Adds a new message.
- L57 _public function_ `TArrayView<const FCameraBuildLogMessage> GetMessages() const` — Gets the list of received messages so far.
- L60 _public prototype_ `void ResetMessages();` — Clears all messages.
- L63 _public function_ `bool HasWarnings() const` — Returns whether any warning has been logged.
- L65 _public function_ `bool HasErrors() const` — Returns whether any error has been logged.
- L69 _private member_ `TArray<FCameraBuildLogMessage> Messages;`
- L71 _private member_ `FString LoggingPrefix;`
- L72 _private member_ `bool bForwardToLogging = true;`
- L74 _private member_ `bool bHasWarnings = false;`
- L75 _private member_ `bool bHasErrors = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraBuildStatus.h` (Public)


#### enum `ECameraBuildStatus`  
`enum class ECameraBuildStatus : uint8`  
_L14-20_
- reflection: `UENUM()`
- desc: Enumeration that describes if a camera asset needs to be rebuilt.
- L16 _public enumerator_ `Clean`
- L17 _public enumerator_ `CleanWithWarnings`
- L18 _public enumerator_ `WithErrors`
- L19 _public enumerator_ `Dirty`

#### class `UHasCameraBuildStatus`  
`class UHasCameraBuildStatus : public UInterface`  
_L23-26_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IHasCameraBuildStatus`  
`class IHasCameraBuildStatus`  
_L32-43_
- desc: Interface for an object that can be built and has a build status, such as a camera asset or camera rig.
- L39 _public prototype_ `virtual ECameraBuildStatus GetBuildStatus() const PURE_VIRTUAL(IHasCameraBuildStatus::GetBuildStatus, return ECameraBuildStatus::Dirty;);` — Gets the build status of the object.
- L42 _public prototype_ `virtual void DirtyBuildStatus() PURE_VIRTUAL();` — Dirties the build status of the object.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraNodeHierarchyBuilder.h` (Public)


#### class `UE::Cameras::FCameraNodeHierarchyBuilder`  
`class FCameraNodeHierarchyBuilder`  
_L20-46_
- desc: A helper class that can build a hierarchy of camera nodes.
- L25 _public prototype_ `FCameraNodeHierarchyBuilder(FCameraBuildContext& InBuildContext, UBaseCameraObject* InCameraObject);` — Creates a new camera node hierarchy builder.
- L28 _public function_ `const FCameraNodeHierarchy& GetHierarchy() const` — Gets the camera node hierarchy.
- L31 _public prototype_ `void PreBuild();` — Calls PreBuild on all the camera nodes.
- L34 _public prototype_ `void Build();` — Calls Build on all the camera nodes and computes the allocation info.
- L38 _private prototype_ `void CallBuild(FCameraObjectBuildContext& BuildContext, UCameraNode* CameraNode);`
- L39 _private prototype_ `void BuildParametersAllocationInfo(FCameraObjectBuildContext& BuildContext);`
- L43 _private member_ `FCameraBuildContext BuildContext;`
- L44 _private member_ `UBaseCameraObject* CameraObject = nullptr;`
- L45 _private member_ `FCameraNodeHierarchy CameraNodeHierarchy;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraObjectBuildContext.h` (Public)


#### struct `UE::Cameras::FCameraObjectBuildContext`  
`struct FCameraObjectBuildContext : public FCameraBuildContext`  
_L14-22_
- inherits: `FCameraBuildContext`
- desc: Camera object build context.
- L16 _public function_ `FCameraObjectBuildContext(const FCameraBuildContext& InParentContext) : FCameraBuildContext(InParentContext)`
- L21 _public member_ `FCameraObjectAllocationInfo AllocationInfo;` — The allocation information for the camera rig.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraObjectInterfaceBuilder.h` (Public)


#### class `UE::Cameras::FCameraObjectInterfaceBuilder`  
`class FCameraObjectInterfaceBuilder`  
_L25-63_
- L29 _public prototype_ `FCameraObjectInterfaceBuilder(FCameraBuildContext& InBuildContext);`
- L31 _public prototype_ `void BuildInterface(UBaseCameraObject* InCameraObject, const FCameraNodeHierarchy& InHierarchy, bool bCollectStrayNodes);`
- L32 _public prototype_ `void BuildInterface(UBaseCameraObject* InCameraObject, TArrayView<UCameraNode*> InCameraObjectNodes);`
- L36 _private prototype_ `void BuildInterfaceImpl();`
- L38 _private prototype_ `void GatherOldDrivenParameters();`
- L39 _private prototype_ `void BuildInterfaceParameters();`
- L40 _private prototype_ `void BuildInterfaceParameterBindings();`
- L41 _private prototype_ `void DiscardUnusedParameters();`
- L45 _private prototype_ `bool SetupCameraParameterOrVariableReferenceOverride(const UCameraObjectInterfaceBlendableParameter* BlendableParameter, UCameraNode* Target, FName TargetPropertyName);`
- L46 _private prototype_ `bool SetupCustomBlendableParameterOverride(const UCameraObjectInterfaceBlendableParameter* BlendableParameter, UCameraNode* Target, FName TargetPropertyName);`
- L48 _private prototype_ `bool SetupDataContextPropertyOverride(const UCameraObjectInterfaceDataParameter* DataParameter, UCameraNode* Target, FName TargetPropertyName);`
- L49 _private prototype_ `bool SetupCustomDataParameterOverride(const UCameraObjectInterfaceDataParameter* DataParameter, UCameraNode* Target, FName TargetPropertyName);`
- L53 _private member_ `FCameraBuildContext BuildContext;`
- L55 _private member_ `UBaseCameraObject* CameraObject = nullptr;`
- L56 _private member_ `TArray<UCameraNode*> CameraObjectNodes;`
- L58 _private typedef_ `using FDrivenParameterKey = TTuple<UObject*, FName>;`
- L59 _private member_ `TMap<FDrivenParameterKey, FCameraVariableID> OldDrivenBlendableParameters;`
- L60 _private member_ `TMap<FDrivenParameterKey, FCameraContextDataID> OldDrivenDataParameters;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Cameras` (scope `UE`)
- L23 _namespace_ `namespace Internal` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraObjectInterfaceParameterBuilder.h` (Public)


#### class `UE::Cameras::FCameraObjectInterfaceParameterBuilder`  
`class FCameraObjectInterfaceParameterBuilder`  
_L23-50_
- desc: Builds the property bag that contains a property for each exposed parameter on the given camera object. Each property's value is set to the default value of the corresponding parameter.
- L27 _public prototype_ `FCameraObjectInterfaceParameterBuilder();`
- L29 _public prototype_ `void BuildParameters(UBaseCameraObject* InCameraObject);`
- L33 _public prototype_ `static void AppendDefaultParameterProperties(const UBaseCameraObject* CameraObject, TArray<FPropertyBagPropertyDesc>& OutProperties);`
- L34 _public prototype_ `static void AppendDefaultParameterProperties(TConstArrayView<FCameraObjectInterfaceParameterDefinition> ParameterDefinitions, TArray<FPropertyBagPropertyDesc>& OutProperties);`
- L36 _public prototype_ `static bool SetDefaultParameterValue(UBaseCameraObject* CameraObject, const FCameraObjectInterfaceParameterDefinition& ParameterDefinition, UCameraNode* TargetNode, FName TargetPropertyName, bool bAddParameterIfMissing = true);`
- L38 _public prototype_ `static void FixUpDefaultParameterProperties(TConstArrayView<FCameraObjectInterfaceParameterDefinition> ParameterDefinitions, FInstancedPropertyBag& InOutPropertyBag);`
- L42 _private prototype_ `void BuildParametersImpl();`
- L44 _private prototype_ `void BuildParameterDefinitions();`
- L45 _private prototype_ `void BuildDefaultParameters();`
- L49 _private member_ `UBaseCameraObject* CameraObject = nullptr;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraRigAssetBuilder.h` (Public)


#### class `UE::Cameras::FCameraRigAssetBuilder`  
`class FCameraRigAssetBuilder`  
_L24-47_
- desc: A class that can prepare a camera rig for runtime use. This builder class sets up internal camera variables that handle exposed camera rig parameters, computes the allocation information of the camera rig, and does various kinds of validation. Once the build process is done, the BuildStatus property is set on the camera rig.
- L29 _public prototype_ `FCameraRigAssetBuilder(FCameraBuildContext& InBuildContext);` — Creates a new camera rig builder.
- L32 _public prototype_ `void BuildCameraRig(UCameraRigAsset* InCameraRig);` — Builds the given camera rig.
- L36 _private prototype_ `void BuildCameraRigImpl();`
- L38 _private prototype_ `void UpdateBuildStatus();`
- L42 _private member_ `FCameraBuildContext BuildContext;`
- L44 _private member_ `UCameraRigAsset* CameraRig = nullptr;`
- L46 _private member_ `FCameraNodeHierarchy CameraNodeHierarchy;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Build/CameraShakeAssetBuilder.h` (Public)


#### class `UE::Cameras::FCameraShakeAssetBuilder`  
`class FCameraShakeAssetBuilder`  
_L15-36_
- L19 _public prototype_ `FCameraShakeAssetBuilder(FCameraBuildContext& InBuildContext);`
- L21 _public prototype_ `void BuildCameraShake(UCameraShakeAsset* InCameraShake);`
- L25 _private prototype_ `void BuildCameraShakeImpl();`
- L27 _private prototype_ `void UpdateBuildStatus();`
- L31 _private member_ `FCameraBuildContext BuildContext;`
- L33 _private member_ `UCameraShakeAsset* CameraShake = nullptr;`
- L35 _private member_ `FCameraNodeHierarchy CameraNodeHierarchy;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/BaseCameraObject.h` (Public)


#### class `UE::Cameras::ICameraObjectEventHandler`  
`class ICameraObjectEventHandler`  
_L31-38_
- desc: Interface for listening to changes on a camera rig asset.
- L34 _public prototype_ `virtual ~ICameraObjectEventHandler() = default;`
- L37 _public function_ `virtual void OnCameraObjectInterfaceChanged()` — Called when the camera object's interface has changed.

#### struct `FCameraObjectAllocationInfo`  
`struct FCameraObjectAllocationInfo`  
_L45-66_
- reflection: `USTRUCT()`
- desc: Structure describing various allocations needed by a camera rig.
- L51 _public member_ `FCameraNodeEvaluatorAllocationInfo EvaluatorInfo;` — `UPROPERTY()` — Allocation info for node evaluators.
- L55 _public member_ `FCameraVariableTableAllocationInfo VariableTableInfo;` — `UPROPERTY()` — Allocation info for the variable table.
- L59 _public member_ `FCameraContextDataTableAllocationInfo ContextDataTableInfo;` — `UPROPERTY()` — Allocation info for the context data table.
- L63 _public prototype_ `void Append(const FCameraObjectAllocationInfo& OtherAllocationInfo);`
- L65 _public prototype_ `bool operator==(const FCameraObjectAllocationInfo& Other) const = default;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraObjectAllocationInfo> : public TStructOpsTypeTraitsBase2<FCameraObjectAllocationInfo>`  
_L69-76_
- inherits: `TStructOpsTypeTraitsBase2<FCameraObjectAllocationInfo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L72-75_

#### struct `FCameraObjectConnection`  
`struct FCameraObjectConnection`  
_L82-103_
- reflection: `USTRUCT()`
- desc: A connection inside a camera object graph.
- L90 _public member_ `TObjectPtr<UObject> Source;` — `UPROPERTY()` — The source object of the connection.
- L94 _public member_ `FName SourcePropertyName;` — `UPROPERTY()` — The source object property of the connection.
- L98 _public member_ `TObjectPtr<UObject> Target;` — `UPROPERTY()` — The target object of the connection.
- L102 _public member_ `FName TargetPropertyName;` — `UPROPERTY()` — The target object property of the connection.

#### struct `FCameraObjectConnections`  
`struct FCameraObjectConnections`  
_L109-127_
- reflection: `USTRUCT()`
- desc: A collection of connections inside a camera object graph.
- L117 _public member_ `TArray<FCameraObjectConnection> Connections;` — `UPROPERTY()` — The list of connections.
- L121 _public prototype_ `void Add(UObject* InSource, FName InSourcePropertyName, UObject* InTarget, FName InTargetPropertyName);`
- L123 _public prototype_ `FCameraObjectConnection* FindBySource(UObject* InSource);`
- L124 _public prototype_ `FCameraObjectConnection* FindBySource(UObject* InSource, FName InSourcePropertyName);`
- L125 _public prototype_ `FCameraObjectConnection* FindByTarget(UObject* InTarget);`
- L126 _public prototype_ `FCameraObjectConnection* FindByTarget(UObject* InTarget, FName InTargetPropertyName);`

#### class `UBaseCameraObject`  
`class UBaseCameraObject : public UObject`  
_L134-214_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A base class for a camera object that has a graph of camera nodes, connections between them, and some exposed parameters.
- L142 _public member_ `FCameraObjectInterface Interface;` — `UPROPERTY()` — The public data interface of this camera object.
- L145 _public member_ `FCameraObjectConnections Connections;` — `UPROPERTY()`
- L148 _public member_ `UE::Cameras::TCameraEventHandlerContainer<UE::Cameras::ICameraObjectEventHandler> EventHandlers;` — Event handlers to be notified of data changes.
- L152 _public member_ `FCameraObjectAllocationInfo AllocationInfo;` — `UPROPERTY()` — Allocation information for all the nodes and variables in this camera object.
- L157 _public function_ `const FGuid& GetGuid() const` — Gets the object's unique ID.
- L160 _public function_ `const FInstancedPropertyBag& GetDefaultParameters() const` — Gets the default values for the parameters exposed on this camera rig.
- L163 _public function_ `FInstancedPropertyBag& GetDefaultParameters()` — Gets the default values for the parameters exposed on this camera rig.
- L166 _public function_ `TConstArrayView<FCameraObjectInterfaceParameterDefinition> GetParameterDefinitions() const` — Gets the definitions of parameters exposed on this camera rig.
- L171 _public prototype_ `bool FindParameterDefinitionByName(const FName ParameterName, FCameraObjectInterfaceParameterDefinition& OutParameterDefinition) const;` — Finds a parameter definition by name.
- L174 _public prototype_ `bool FindParameterDefinitionByGuid(const FGuid& ParameterGuid, FCameraObjectInterfaceParameterDefinition& OutParameterDefinition) const;` — Finds a parameter definition by ID.
- L179 _public function_ `virtual UCameraNode* GetRootNode()` — Get the root node of this camera object.
- L184 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface.
- L185 _public prototype_ `virtual void PostLoad() override;`
- L186 _public prototype_ `virtual void PostInitProperties() override;`
- L187 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L193 _protected prototype_ `void UpgradeInterfaceConnections(IObjectTreeGraphRootObject* RootObject, FName DefaultGraphName);` — Utility method to be called on PostLoad by subclasses that need upgrading old data.
- L200 _private member_ `FGuid Guid;` — `UPROPERTY()` — The camera object's unique ID.
- L204 _private member_ `FInstancedPropertyBag DefaultParameters;` — `UPROPERTY()` — The default interface parameter values, generated during build.
- L208 _private member_ `TArray<FCameraObjectInterfaceParameterDefinition> ParameterDefinitions;` — `UPROPERTY()` — The definitions of parameters exposed on this camera rig.
- L211 _private member_ `bool bDefaultParametersMayHaveMissingPropertyFlags = false;` — Flag for DefaultParameters maybe having missing property flags.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)
- L73 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon1d0b7bbf0103`)
- L74 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon1d0b7bbf0103`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/BaseCameraObjectReference.h` (Public)


#### struct `FCameraObjectInterfaceParameterMetaData`  
`struct FCameraObjectInterfaceParameterMetaData`  
_L23-48_
- reflection: `USTRUCT()`
- desc: Metadata for a referenced camera object's interface parameters.
- L29 _public member_ `FGuid ParameterGuid;` — `UPROPERTY()` — The GUID of the parameter.
- L37 _public member_ `FCameraVariableID OverrideVariableID;` — `UPROPERTY()` — The ID to use for overriding a blendable parameter. NOTE: only used for blendable structs, since other types are parameter structs with their own variable ID inside.
- L41 _public member_ `FCameraContextDataID OverrideDataID;` — `UPROPERTY()` — The ID to use for overriding a data parameter.
- L47 _public member_ `bool bIsOverridden_DEPRECATED = false;` — `UPROPERTY()`

#### struct `FBaseCameraObjectReference`  
`struct FBaseCameraObjectReference`  
_L51-122_
- reflection: `USTRUCT(BlueprintType)`
- L57 _public prototype_ `virtual ~FBaseCameraObjectReference() = default;`
- L60 _public function_ `const FInstancedOverridablePropertyBag& GetParameters() const` — Gets the parameters for this camera rig, some of which containing overrides.
- L66 _public function_ `FInstancedOverridablePropertyBag& GetParameters()` — Gets the parameters for this camera rig, some of which containing overrides.
- L72 _public function_ `TConstArrayView<FGuid> GetOverriddenParameterGuids() const` — Gets the IDs of the parameters with override values.
- L80 _public function_ `virtual const UBaseCameraObject* GetCameraObject() const` — Gets the camera object that this reference points to.
- L83 _public prototype_ `bool NeedsRebuildParameters() const;` — Returns whether the override parameters structure needs to be rebuilt.
- L85 _public prototype_ `bool RebuildParametersIfNeeded();` — Rebuilds the override parameters structure, if needed.
- L87 _public prototype_ `void RebuildParameters();` — Rebuilds the override parameters structure.
- L93 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L95 _public prototype_ `void GetCustomCameraNodeParameters(UE::Cameras::FCameraNodeParameterInfos& OutParameterInfos);`
- L97 _public prototype_ `bool PostBuild();`
- L99 _public prototype_ `bool IsParameterOverridden(const FGuid& PropertyID) const;`
- L100 _public prototype_ `void SetParameterOverridden(const FGuid& PropertyID, bool bIsOverridden);`
- L103 _public prototype_ `template<typename ContainerType> void GetOverriddenParameterGuids(ContainerType& OutOverriddenIDs) const;`
- L107 _protected prototype_ `const FCameraObjectInterfaceParameterMetaData* FindMetaData(const FGuid& PropertyID) const;`
- L111 _private prototype_ `FCameraObjectInterfaceParameterMetaData& GetMetaData(const FGuid& PropertyID);`
- L117 _protected member_ `FInstancedOverridablePropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category="", meta=(FixedLayout, InterpBagProperties))` — The camera rig's parameters.
- L121 _protected member_ `TArray<FCameraObjectInterfaceParameterMetaData> ParameterMetaData;` — `UPROPERTY()` — Metadata for the parameters.
- L125 _function_ `template<typename ContainerType> void FBaseCameraObjectReference::GetOverriddenParameterGuids(ContainerType& OutOverriddenIDs) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FBaseCameraObjectReference> : public TStructOpsTypeTraitsBase2<FBaseCameraObjectReference>`  
_L131-137_
- inherits: `TStructOpsTypeTraitsBase2<FBaseCameraObjectReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L134-136_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L135 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anona08689ee0103`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/BlendCameraNode.h` (Public)


#### class `UBlendCameraNode`  
`class UBlendCameraNode : public UCameraNode`  
_L14-17_
- reflection: `UCLASS(MinimalAPI, Abstract, meta=(CameraNodeCategories="Blends"))`
- inherits: `UCameraNode`
- desc: Base class for blend camera nodes.

#### struct `UE::Cameras::FCameraNodePreBlendParams`  
`struct FCameraNodePreBlendParams`  
_L27-46_
- desc: Parameter struct for blending camera node parameters.
- L29 _public function_ `FCameraNodePreBlendParams( const FCameraNodeEvaluationParams& InEvaluationParams, const FCameraPose& InLastCameraPose, const FCameraVariableTable& InChildVariableTable) : EvaluationParams(InEvaluationParams) , LastCameraPose(InLastCameraPose) , ChildVariableTable(InChildVariableTable)`
- L39 _public member_ `const FCameraNodeEvaluationParams& EvaluationParams;` — The parameters for the evaluation that will happen afterwards.
- L41 _public member_ `const FCameraPose& LastCameraPose;` — Last frame's camera pose.
- L43 _public member_ `const FCameraVariableTable& ChildVariableTable;` — The variable table of the node tree being blended.
- L45 _public member_ `ECameraVariableTableFilter VariableTableFilter = ECameraVariableTableFilter::None;` — The filter to use for variable table blending.

#### struct `UE::Cameras::FCameraNodePreBlendResult`  
`struct FCameraNodePreBlendResult`  
_L51-65_
- desc: Result struct for blending camera node parameters.
- L53 _public function_ `FCameraNodePreBlendResult(FCameraVariableTable& InVariableTable) : VariableTable(InVariableTable)`
- L58 _public member_ `FCameraVariableTable& VariableTable;` — The variable table to received blended parameters.
- L61 _public member_ `bool bIsBlendFull = false;` — Whether the blend has reached 100%.
- L64 _public member_ `bool bIsBlendFinished = false;` — Whether the blend is finished.

#### struct `UE::Cameras::FCameraNodeBlendParams`  
`struct FCameraNodeBlendParams`  
_L70-83_
- desc: Parameter struct for blending camera node tree results.
- L72 _public function_ `FCameraNodeBlendParams( const FCameraNodeEvaluationParams& InChildParams, const FCameraNodeEvaluationResult& InChildResult) : ChildParams(InChildParams) , ChildResult(InChildResult)`
- L80 _public member_ `const FCameraNodeEvaluationParams& ChildParams;` — The parameters that the blend received during the evaluation.
- L82 _public member_ `const FCameraNodeEvaluationResult& ChildResult;` — The result that the blend should apply over another result.

#### struct `UE::Cameras::FCameraNodeBlendResult`  
`struct FCameraNodeBlendResult`  
_L88-102_
- desc: Result struct for blending camera node tree results.
- L90 _public function_ `FCameraNodeBlendResult(FCameraNodeEvaluationResult& InBlendedResult) : BlendedResult(InBlendedResult)`
- L95 _public member_ `FCameraNodeEvaluationResult& BlendedResult;` — The result upon which another result should be blended.
- L98 _public member_ `bool bIsBlendFull = false;` — Whether the blend has reached 100%.
- L101 _public member_ `bool bIsBlendFinished = false;` — Whether the blend is finished.

#### struct `UE::Cameras::FCameraNodeBlendInterruptionParams`  
`struct FCameraNodeBlendInterruptionParams`  
_L107-111_
- desc: Parameter struct for initializing a blend from an interrupted blend.
- L110 _public member_ `const FBlendCameraNodeEvaluator* InterruptedBlend = nullptr;` — The existing blend that was interrupted.

#### class `UE::Cameras::FBlendCameraNodeEvaluator`  
`class FBlendCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L116-170_
- inherits: `FCameraNodeEvaluator`
- desc: Base evaluator class for blend camera nodes.
- L123 _public prototype_ `void BlendParameters(const FCameraNodePreBlendParams& Params, FCameraNodePreBlendResult& OutResult);` — Blend the parameters produced by a camera node tree over another set of values.
- L126 _public prototype_ `void BlendResults(const FCameraNodeBlendParams& Params, FCameraNodeBlendResult& OutResult);` — Blend the result of a camera node tree over another result.
- L137 _public prototype_ `bool InitializeFromInterruption(const FCameraNodeBlendInterruptionParams& Params);` — Initialize this blend from an interrupted blend. @return If true, the blend sub-class fully supports seamless transition from the interrupted blend. If false, the blend will be wrapped in an Interrupted Blend node that will freeze the interrupted blend to ensure a seamless transition.
- L146 _public prototype_ `bool SetReversed(bool bInReverse);` — Reverse the direction of this blend. @return If true, the blend sub-class fully supports reverse blending. If false, the blend will be wrapped in a Reverse Blend node that will cache and swap the "from" and "to" results given to the BlendParameters and BlendResults methods.
- L152 _public prototype_ `void Freeze();` — Freezes this blend. A frozen blend can't access its evaluation context or underlying camera node anymore, and must operate entirely standalone.
- L157 _protected function_ `virtual void OnBlendParameters(const FCameraNodePreBlendParams& Params, FCameraNodePreBlendResult& OutResult)` — Blend the parameters produced by a camera node tree over another set of values.
- L160 _protected function_ `virtual void OnBlendResults(const FCameraNodeBlendParams& Params, FCameraNodeBlendResult& OutResult)` — Blend the result of a camera node tree over another result.
- L163 _protected function_ `virtual bool OnInitializeFromInterruption(const FCameraNodeBlendInterruptionParams& Params)` — Initialize this blend from an interrupted blend. See comments from InitializeFromInterruption.
- L166 _protected function_ `virtual bool OnSetReversed(bool bInReverse)` — Reverse the direction of this blend. See comments from SetReversed.
- L169 _protected function_ `virtual void OnFreeze()` — Freezes this blend. See commands from Freeze.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Cameras` (scope `UE`)
- L179 _macro_ `#define UE_DECLARE_BLEND_CAMERA_NODE_EVALUATOR(ApiDeclSpec, ClassName)\` — Macros for declaring and defining new blend node evaluators. They are the same as the base ones for generic node evaluators, but the first one prevents you from having to specify FBlendCameraNodeEvaluator as the base class, which saves a little bit of typing.
- L182 _macro_ `#define UE_DECLARE_BLEND_CAMERA_NODE_EVALUATOR_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L185 _macro_ `#define UE_DEFINE_BLEND_CAMERA_NODE_EVALUATOR(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/BlendStackCameraNode.h` (Public)


#### enum `ECameraBlendStackType`  
`enum class ECameraBlendStackType`  
_L46-60_
- reflection: `UENUM()`
- desc: Describes a type of blend stack.
- L53 _public enumerator_ `IsolatedTransient` — Camera rigs are evaluated in isolation before being blended together, and get automatically popped out of the stack when another rig has reached 100% blend above them.
- L59 _public enumerator_ `AdditivePersistent` — Camera rigs are evaluated in an additive way, i.e. the result of a lower camera rig becomes the input of the next ones. Also, camera rigs stay in the stack until explicitly removed.

#### class `UBlendStackCameraNode`  
`class UBlendStackCameraNode : public UCameraNode`  
_L66-84_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UCameraNode`
- desc: A blend stack implemented as a camera node.
- L73 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface
- L79 _public member_ `ECameraBlendStackType BlendStackType = ECameraBlendStackType::IsolatedTransient;` — `UPROPERTY()` — The type of blend stack this should run as.
- L83 _public member_ `ECameraRigLayer Layer = ECameraRigLayer::None;` — `UPROPERTY()` — The layer that this blend stack represents, if any.

#### class `UE::Cameras::FBlendStackCameraNodeEvaluator`  
`class FBlendStackCameraNodeEvaluator : public TCameraNodeEvaluator<UBlendStackCameraNode> #if WITH_EDITOR , public IGameplayCamerasLiveEditListener #endif`  
_L94-263_
- inherits: `TCameraNodeEvaluator<UBlendStackCameraNode>,IGameplayCamerasLiveEditListener`
- desc: Evaluator for a blend stack camera node.
- L104 _public prototype_ `FBlendStackCameraNodeEvaluator();`
- L105 _public prototype_ `~FBlendStackCameraNodeEvaluator();`
- L108 _public prototype_ `FCameraRigEvaluationInfo GetActiveCameraRigEvaluationInfo() const;` — Returns information about the top (active) camera rig, if any.
- L111 _public prototype_ `FCameraRigEvaluationInfo GetCameraRigEvaluationInfo(FBlendStackEntryID EntryID) const;` — Returns information about a given camera rig, if any.
- L114 _public prototype_ `bool HasAnyRunningCameraRig(TSharedPtr<const FCameraEvaluationContext> InContext) const;` — Returns whether the stack contains any running camera rig with the given context.
- L117 _public prototype_ `FBlendStackCameraDebugBlock* BuildDetailedDebugBlock( const FCameraDebugBlockBuildParams& Params, const FLinearColor& StartColor, const FLinearColor& EndColor, FCameraDebugBlockBuilder& Builder);`
- L126 _public function_ `FOnBlendStackCameraRigEvent& OnCameraRigEvent()` — Gets the delegate for blend stack events.
- L131 _protected prototype_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren() override;` — FCameraNodeEvaluator interface
- L132 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L133 _protected prototype_ `virtual void OnExecuteOperation(const FCameraOperationParams& Params, FCameraOperation& Operation) override;`
- L134 _protected prototype_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector) override;`
- L135 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L138 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L143 _protected prototype_ `virtual void OnPostBuildAsset(const FGameplayCameraAssetBuildEvent& BuildEvent) override;` — IGameplayCamerasLiveEditListener interface
- L150 _protected prototype_ `void InitializeEntry( FCameraRigEntry& NewEntry, const UCameraRigAsset* CameraRig, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, UBlendStackRootCameraNode* EntryRootNode, bool bIsActiveEntry);`
- L157 _protected prototype_ `int32 IndexOfEntry(const FBlendStackEntryID EntryID) const;`
- L159 _protected prototype_ `void FreezeEntry(FCameraRigEntry& Entry);`
- L161 _protected prototype_ `void PopEntry(int32 EntryIndex);`
- L162 _protected prototype_ `void PopEntries(int32 FirstIndexToKeep);`
- L164 _protected prototype_ `void BroadcastCameraRigEvent(EBlendStackCameraRigEventType EventType, const FCameraRigEntry& Entry, const UCameraRigTransition* Transition = nullptr) const;`
- L167 _protected prototype_ `void AddPackageListeners(FCameraRigEntry& Entry);`
- L168 _protected prototype_ `void RemoveListenedPackages(FCameraRigEntry& Entry);`
- L169 _protected prototype_ `void RemoveListenedPackages(TSharedPtr<IGameplayCamerasLiveEditManager> LiveEditManager, FCameraRigEntry& Entry);`
- L175 _protected function_ `virtual void OnEntryReinitialized(int32 EntryIndex)`
- L192 _protected prototype_ `void ResolveEntries(const FCameraNodeEvaluationParams& Params, TArray<FResolvedEntry>& OutResolvedEntries);`
- L193 _protected prototype_ `void OnRunFinished(FCameraNodeEvaluationResult& OutResult);`
- L240 _protected member_ `FCameraSystemEvaluator* OwningEvaluator = nullptr;` — The camera system evaluator running this node.
- L243 _protected member_ `TArray<FCameraRigEntry> Entries;` — Entries in the blend stack.
- L246 _protected member_ `uint32 NextEntryID = 0;` — Next entry ID to use.
- L249 _protected member_ `ECameraRigLayer Layer = ECameraRigLayer::None;` — The layer that this blend stack represents, if any.
- L252 _protected member_ `FOnBlendStackCameraRigEvent OnCameraRigEventDelegate;` — The delegate to invoke when an event occurs in this blend stack.
- L255 _protected member_ `TMap<TWeakObjectPtr<const UPackage>, int32> AllListenedPackages;`
- L256 _protected member_ `TSet<TWeakObjectPtr<const UCameraRigAsset>> BuiltCameraRigs;`

#### struct `UE::Cameras::FBlendStackCameraNodeEvaluator::FResolvedEntry`  
`struct FResolvedEntry`  
_L180-190_
- L182 _public function_ `FResolvedEntry(FCameraRigEntry& InEntry, TSharedPtr<const FCameraEvaluationContext> InContext) : Entry(InEntry), Context(InContext)`
- L186 _public member_ `FCameraRigEntry& Entry;`
- L187 _public member_ `TSharedPtr<const FCameraEvaluationContext> Context;`
- L188 _public member_ `int32 EntryIndex = INDEX_NONE;`
- L189 _public member_ `bool bIsActiveEntry = false;`

#### struct `UE::Cameras::FBlendStackCameraNodeEvaluator::FCameraRigEntry`  
`struct FCameraRigEntry`  
_L197-237_
- L200 _public member_ `FBlendStackEntryID EntryID;` — The ID for this entry.
- L202 _public member_ `TWeakPtr<const FCameraEvaluationContext> EvaluationContext;` — Evaluation context in which this entry runs.
- L204 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The camera rig asset that this entry runs.
- L206 _public member_ `TObjectPtr<UBlendStackRootCameraNode> RootNode;` — The root node.
- L208 _public member_ `FCameraNodeEvaluatorStorage EvaluatorStorage;` — Storage buffer for all evaluators in this node tree.
- L210 _public member_ `FBlendStackRootCameraNodeEvaluator* RootEvaluator = nullptr;` — Root evaluator.
- L212 _public member_ `FCameraNodeEvaluatorHierarchy EvaluatorHierarchy;` — The evaluator tree.
- L214 _public member_ `FCameraNodeEvaluationResult ContextResult;` — Context result for this node tree.
- L216 _public member_ `FCameraNodeEvaluationResult Result;` — Evaluation result for this node tree.
- L232 _public member_ `} Flags;`
- L235 _public member_ `TArray<TWeakObjectPtr<const UPackage>, TInlineAllocator<4>> ListenedPackages;`

#### struct `UE::Cameras::FBlendStackCameraNodeEvaluator::FCameraRigEntry::(anonymous)`  
``  
_L219-232_

#### class `UE::Cameras::FBlendStackSummaryCameraDebugBlock`  
`class FBlendStackSummaryCameraDebugBlock : public FCameraDebugBlock`  
_L267-286_
- inherits: `FCameraDebugBlock`
- L273 _public prototype_ `FBlendStackSummaryCameraDebugBlock();`
- L274 _public prototype_ `FBlendStackSummaryCameraDebugBlock(const FBlendStackCameraNodeEvaluator& InEvaluator);`
- L278 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L279 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L283 _private member_ `int32 NumEntries;`
- L284 _private member_ `ECameraBlendStackType BlendStackType;`
- L285 _private member_ `ECameraRigLayer BlendStackLayer;`

#### class `UE::Cameras::FBlendStackCameraDebugBlock`  
`class FBlendStackCameraDebugBlock : public FCameraDebugBlock`  
_L288-300_
- inherits: `FCameraDebugBlock`
- L294 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L298 _private typedef_ `using FBlendStackStartEndColors = TTuple<FLinearColor, FLinearColor>;`
- L299 _private member_ `FBlendStackStartEndColors StartEndColors;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)
- L86 _namespace_ `namespace UE`
- L86 _namespace_ `namespace Cameras` (scope `UE`)
- L89 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBlendStackCameraRigEvent, const FBlendStackCameraRigEvent&);`
- L89 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBlendStackCameraRigEvent, const FBlendStackCameraRigEvent&);` (scope `UE::Cameras`)
- L221 _member_ `bool bIsFirstFrame:1 = false;` (scope `UE::Cameras::FBlendStackCameraNodeEvaluator::FCameraRigEntry::__anonad224eae0108`) — Whether this is the first frame this entry runs.
- L223 _member_ `bool bWasContextInitialResultValid:1 = false;` (scope `UE::Cameras::FBlendStackCameraNodeEvaluator::FCameraRigEntry::__anonad224eae0108`) — Whether the context's initial result was valid last frame.
- L225 _member_ `bool bForceCameraCut:1 = false;` (scope `UE::Cameras::FBlendStackCameraNodeEvaluator::FCameraRigEntry::__anonad224eae0108`) — Whether to force a camera cut on this entry this frame.
- L227 _member_ `bool bIsFrozen:1 = false;` (scope `UE::Cameras::FBlendStackCameraNodeEvaluator::FCameraRigEntry::__anonad224eae0108`) — Whether this entry is frozen.
- L230 _member_ `bool bLogWarnings:1 = true;` (scope `UE::Cameras::FBlendStackCameraNodeEvaluator::FCameraRigEntry::__anonad224eae0108`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/BlendStackCameraRigEvent.h` (Public)


#### enum `UE::Cameras::EBlendStackCameraRigEventType`  
`enum class EBlendStackCameraRigEventType`  
_L16-24_
- desc: A type of blend stack event.
- L19 _public enumerator_ `Pushed` — A camera rig was pushed on the blend stack.
- L21 _public enumerator_ `Frozen` — A camera rig was frozen.
- L23 _public enumerator_ `Popped` — A camera rig was popped out of the blend stack.

#### struct `UE::Cameras::FBlendStackCameraRigEvent`  
`struct FBlendStackCameraRigEvent`  
_L29-39_
- desc: A structure describing an event happening on a blend stack.
- L32 _public member_ `EBlendStackCameraRigEventType EventType;` — The event type.
- L34 _public member_ `const FBlendStackCameraNodeEvaluator* BlendStackEvaluator = nullptr;` — The blend stack evaluator in which the event is happening.
- L36 _public member_ `FCameraRigEvaluationInfo CameraRigInfo;` — The evaluation information for the camera rig associated with the event.
- L38 _public member_ `TObjectPtr<const UCameraRigTransition> Transition;` — If the event is Pushed, the transition used for the new camera rig.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/BlendStackEntryID.h` (Public)


#### struct `UE::Cameras::FBlendStackEntryID`  
`struct FBlendStackEntryID`  
_L24-74_
- desc: An ID for an entry in a camera blend stack. Note about overflowing: the max value for a uint32 is 4294967295. We use it for an INVALID blend stack entry, so we have at most 4294967294 instances to go through before overflowing. If somehow we wanted to push, on average, one new camera rig on a blend stack every second, we would only overflow after ~136 years.
- L28 _public function_ `FBlendStackEntryID() : Value(INVALID)`
- L30 _public function_ `bool IsValid() const`
- L32 _public function_ `explicit operator bool() const`
- L64 _private function_ `FBlendStackEntryID(uint32 InValue) : Value(InValue)`
- L68 _private member_ `static const uint32 INVALID = uint32(-1);`
- L70 _private member_ `uint32 Value;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)
- L36 _function_ `friend bool operator==(FBlendStackEntryID A, FBlendStackEntryID B)` (scope `UE::Cameras`)
- L41 _function_ `friend bool operator!=(FBlendStackEntryID A, FBlendStackEntryID B)` (scope `UE::Cameras`)
- L46 _function_ `friend uint32 GetTypeHash(FBlendStackEntryID In)` (scope `UE::Cameras`)
- L51 _function_ `friend FArchive& operator<< (FArchive& Ar, FBlendStackEntryID& In)` (scope `UE::Cameras`)
- L57 _function_ `friend FString LexToString(FBlendStackEntryID In)` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/BuiltInCameraVariables.h` (Public)


#### enum `EBuiltInDoubleCameraVariable`  
`enum class EBuiltInDoubleCameraVariable`  
_L19-26_
- reflection: `UENUM()`
- desc: Built-in floating point camera variables.
- L21 _public enumerator_ `None`
- L22 _public enumerator_ `Yaw`
- L23 _public enumerator_ `Pitch`
- L24 _public enumerator_ `Roll`
- L25 _public enumerator_ `Zoom`

#### enum `EBuiltInVector2dCameraVariable`  
`enum class EBuiltInVector2dCameraVariable`  
_L32-36_
- reflection: `UENUM()`
- desc: Built-in 2-dimensional camera variables.
- L34 _public enumerator_ `None`
- L35 _public enumerator_ `YawPitch`

#### enum `EBuiltInRotator3dCameraVariable`  
`enum class EBuiltInRotator3dCameraVariable`  
_L39-43_
- reflection: `UENUM()`
- L41 _public enumerator_ `None`
- L42 _public enumerator_ `ControlRotation`

#### class `UE::Cameras::FBuiltInCameraVariables`  
`class FBuiltInCameraVariables`  
_L51-80_
- desc: A utility class that provides definitions for "well-known" camera variables.
- L56 _public prototype_ `static const FBuiltInCameraVariables& Get();` — Singleton access.
- L59 _public prototype_ `const FCameraVariableDefinition& GetDefinition(EBuiltInDoubleCameraVariable BuiltInVariable) const;` — Get the definition of a built-in camera variable.
- L61 _public prototype_ `const FCameraVariableDefinition& GetDefinition(EBuiltInVector2dCameraVariable BuiltInVariable) const;` — Get the definition of a built-in camera variable.
- L63 _public prototype_ `const FCameraVariableDefinition& GetDefinition(EBuiltInRotator3dCameraVariable BuiltInVariable) const;` — Get the definition of a built-in camera variable.
- L67 _public member_ `FCameraVariableDefinition YawDefinition;`
- L68 _public member_ `FCameraVariableDefinition PitchDefinition;`
- L69 _public member_ `FCameraVariableDefinition RollDefinition;`
- L70 _public member_ `FCameraVariableDefinition ZoomDefinition;`
- L72 _public member_ `FCameraVariableDefinition YawPitchDefinition;`
- L74 _public member_ `FCameraVariableDefinition FreezeControlRotationDefinition;`
- L75 _public member_ `FCameraVariableDefinition ControlRotationDefinition;`
- L79 _protected prototype_ `FBuiltInCameraVariables();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraAsset.h` (Public)


#### class `UE::Cameras::ICameraAssetEventHandler`  
`class ICameraAssetEventHandler`  
_L31-44_
- desc: Interface for listening to changes on a camera asset.
- L34 _public prototype_ `virtual ~ICameraAssetEventHandler() = default;`
- L37 _public function_ `virtual void OnCameraDirectorChanged(UCameraAsset* InCameraAsset, const TCameraPropertyChangedEvent<UCameraDirector*>& Event)` — Called when the camera director has been changed.
- L39 _public function_ `virtual void OnEnterTransitionsChanged(UCameraAsset* InCameraAsset, const TCameraArrayChangedEvent<UCameraRigTransition*>& Event)` — Changed when the enter transitions have been changed.
- L41 _public function_ `virtual void OnExitTransitionsChanged(UCameraAsset* InCameraAsset, const TCameraArrayChangedEvent<UCameraRigTransition*>& Event)` — Changed when the exit transitions have been changed.
- L43 _public function_ `virtual void OnCameraAssetInterfaceChanged()` — Called when the camera asset's interface has changed.

#### class `UCameraAssetInterfaceParameter`  
`class UCameraAssetInterfaceParameter : public UObject`  
_L51-89_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: An interface parameter on a camera asset, which exposes one of its camera rigs' own interface parameters.
- L59 _public member_ `FString InterfaceParameterName;` — `UPROPERTY(EditAnywhere, Category="Camera")` — The exposed name for this parameter.
- L63 _public member_ `TSoftObjectPtr<UCameraRigAsset> SourceCameraRig;` — `UPROPERTY(EditAnywhere, Category="Camera")` — The camera rig that owns the source parameter.
- L67 _public member_ `FName SourceParameterName;` — `UPROPERTY(EditAnywhere, Category="Camera")` — The name of the parameter on the source camera rig.
- L72 _public function_ `const FGuid& GetGuid() const` — Gets this parameter's unique ID.
- L75 _public prototype_ `bool GetParameterDefinition(FCameraObjectInterfaceParameterDefinition& OutParameterDefinition) const;` — Gets the parameter definition.
- L81 _protected member_ `FGuid Guid;` — `UPROPERTY()` — The Guid of this parameter.
- L86 _protected prototype_ `virtual void PostLoad() override;` — UObject interface.
- L87 _protected prototype_ `virtual void PostInitProperties() override;`
- L88 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`

#### struct `FCameraAssetInterface`  
`struct FCameraAssetInterface`  
_L95-104_
- reflection: `USTRUCT()`
- desc: A structure defining the public interface of a camera asset.
- L103 _public member_ `TArray<TObjectPtr<UCameraAssetInterfaceParameter>> Parameters;` — `UPROPERTY(Instanced)` — The list of exposed parameters on the camera asset.

#### struct `FCameraAssetAllocationInfo`  
`struct FCameraAssetAllocationInfo`  
_L110-123_
- reflection: `USTRUCT()`
- desc: Structure describing various allocations needed by a camera asset.
- L116 _public member_ `FCameraVariableTableAllocationInfo VariableTableInfo;` — `UPROPERTY()` — Combined variable table allocation info for all the camera rigs.
- L120 _public member_ `FCameraContextDataTableAllocationInfo ContextDataTableInfo;` — `UPROPERTY()` — Combined context data table allocation info for all the camera rigs.

#### class `UCameraAsset`  
`class UCameraAsset : public UObject , public IHasCameraBuildStatus , public IObjectTreeGraphObject , public IObjectTreeGraphRootObject`  
_L129-288_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IHasCameraBuildStatus,IObjectTreeGraphObject,IObjectTreeGraphRootObject`
- desc: A complete camera asset.
- L140 _public function_ `UCameraDirector* GetCameraDirector() const` — Gets the camera director.
- L142 _public prototype_ `void SetCameraDirector(UCameraDirector* InCameraDirector);` — Sets the camera director.
- L145 _public function_ `TArrayView<const TObjectPtr<UCameraRigTransition>> GetEnterTransitions() const` — Gets the enter transitions.
- L147 _public prototype_ `void AddEnterTransition(UCameraRigTransition* InTransition);` — Adds an enter transition.
- L149 _public prototype_ `int32 RemoveEnterTransition(UCameraRigTransition* InTransition);` — Removes an enter transition.
- L152 _public function_ `TArrayView<const TObjectPtr<UCameraRigTransition>> GetExitTransitions() const` — Gets the exit transitions.
- L154 _public prototype_ `void AddExitTransition(UCameraRigTransition* InTransition);` — Adds an exit transition.
- L156 _public prototype_ `int32 RemoveExitTransition(UCameraRigTransition* InTransition);` — Removes an exit transition.
- L161 _public function_ `const FInstancedPropertyBag& GetDefaultParameters() const` — Gets the default parameter values for all camera rigs.
- L163 _public function_ `FInstancedPropertyBag& GetDefaultParameters()` — Gets the default parameter values for all camera rigs.
- L166 _public function_ `TConstArrayView<FCameraObjectInterfaceParameterDefinition> GetParameterDefinitions() const` — Gets the definitions of parameters exposed on this camera asset.
- L174 _public prototype_ `void BuildCamera();` — Builds and validates this camera, including all its camera rigs. Errors and warnings will go to the console.
- L180 _public prototype_ `void BuildCamera(UE::Cameras::FCameraBuildContext& InBuildContext);` — Builds and validates this camera, including all its camera rigs. Errors and warnings will go to the provided build context.
- L185 _public member_ `static const FName SharedTransitionsGraphName;` — Graph names for ObjectTreeGraph API.
- L188 _public function_ `virtual ECameraBuildStatus GetBuildStatus() const override` — IHasCameraBuildStatus interface.
- L189 _public prototype_ `virtual void DirtyBuildStatus() override;`
- L192 _public function_ `void SetBuildStatus(ECameraBuildStatus InBuildStatus)` — Sets the build status.
- L195 _public function_ `const FCameraAssetAllocationInfo& GetAllocationInfo() const` — Gets the allocation info for this camera asset.
- L201 _protected prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;`
- L202 _protected prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`
- L203 _protected function_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override`
- L204 _protected prototype_ `virtual const FString& GetGraphNodeCommentText(FName InGraphName) const override;`
- L205 _protected prototype_ `virtual void OnUpdateGraphNodeCommentText(FName InGraphName, const FString& NewComment) override;`
- L210 _protected prototype_ `virtual void GetConnectableObjects(FName InGraphName, TSet<UObject*>& OutObjects) const override;`
- L211 _protected prototype_ `virtual void AddConnectableObject(FName InGraphName, UObject* InObject) override;`
- L212 _protected prototype_ `virtual void RemoveConnectableObject(FName InGraphName, UObject* InObject) override;`
- L216 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface.
- L217 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L218 _protected prototype_ `virtual void PostLoad() override;`
- L219 _protected prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L221 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L227 _public member_ `UE::Cameras::TCameraEventHandlerContainer<UE::Cameras::ICameraAssetEventHandler> EventHandlers;` — Event handlers to be notified of data changes.
- L231 _public member_ `FCameraAssetInterface Interface;` — `UPROPERTY()` — The public interface of this camera asset.
- L237 _private member_ `TObjectPtr<UCameraDirector> CameraDirector;` — `UPROPERTY(Instanced)` — The camera director to use in this camera.
- L241 _private member_ `TArray<TObjectPtr<UCameraRigTransition>> EnterTransitions;` — `UPROPERTY(Instanced)` — A list of default enter transitions for all the camera rigs in this asset.
- L245 _private member_ `TArray<TObjectPtr<UCameraRigTransition>> ExitTransitions;` — `UPROPERTY(Instanced)` — A list of default exit transitions for all the camera rigs in this asset.
- L249 _private member_ `ECameraBuildStatus BuildStatus = ECameraBuildStatus::Dirty;` — `UPROPERTY(Transient)` — The current build state of this camera asset.
- L253 _private member_ `FInstancedPropertyBag DefaultParameters;` — `UPROPERTY()` — Generated values for all camera rig parameters.
- L257 _private member_ `TArray<FCameraObjectInterfaceParameterDefinition> ParameterDefinitions;` — `UPROPERTY()` — Generated list of all the camera rigs' parameters.
- L261 _private member_ `FCameraAssetAllocationInfo AllocationInfo;` — `UPROPERTY()` — Allocation info for the camera asset.
- L267 _private member_ `FIntVector2 TransitionGraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the camera node in the shared transitions graph editor.
- L271 _private member_ `FString TransitionGraphNodeComment;` — `UPROPERTY()` — User-written comment in the transition graph editor.
- L275 _private member_ `TArray<TObjectPtr<UObject>> AllSharedTransitionsObjects;` — `UPROPERTY(Instanced, meta=(ObjectTreeGraphHidden=true))` — All nodes used in the shared transitions graph editor.
- L283 _private member_ `bool bDefaultParametersMayHaveMissingPropertyFlags = false;` — Flag for DefaultParameters maybe having missing property flags.
- L285 _private member_ `bool bNeedsDefaultInterface = false;` — Flag for whether we need to upgrade the interface on the next build.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraAssetReference.h` (Public)


#### struct `FCameraAssetReference`  
`struct FCameraAssetReference`  
_L24-120_
- reflection: `USTRUCT(BlueprintType)`
- desc: A structure holding a reference to a camera asset, along with the interface parameter override values for any of its camera rigs.
- L30 _public prototype_ `FCameraAssetReference();`
- L31 _public prototype_ `FCameraAssetReference(UCameraAsset* InCameraAsset);`
- L34 _public function_ `bool IsValid() const` — Returns whether this reference points to a valid camera asset.
- L40 _public function_ `UCameraAsset* GetCameraAsset()` — Gets the referenced camera asset.
- L46 _public function_ `const UCameraAsset* GetCameraAsset() const` — Gets the referenced camera asset.
- L52 _public function_ `void SetCameraAsset(UCameraAsset* InCameraAsset)` — Sets the referenced camera asset.
- L62 _public function_ `const FInstancedOverridablePropertyBag& GetParameters() const` — Gets the parameters for this camera, some of which containing overrides.
- L68 _public function_ `FInstancedOverridablePropertyBag& GetParameters()` — Gets the parameters for this camera, some of which containing overrides.
- L74 _public function_ `TConstArrayView<FGuid> GetOverriddenParameterGuids() const` — Gets the IDs of the parameters with override values.
- L82 _public prototype_ `void ApplyParameterOverrides(UE::Cameras::FCameraNodeEvaluationResult& OutResult, bool bDrivenOnly) const;` — Applies the parameter override values to the given evaluation result.
- L87 _public prototype_ `bool NeedsRebuildParameters() const;` — Returns whether the override parameters structure needs to be rebuilt.
- L89 _public prototype_ `bool RebuildParametersIfNeeded();` — Rebuilds the override parameters structure, if needed.
- L91 _public prototype_ `void RebuildParameters();` — Rebuilds the override parameters structure.
- L97 _public prototype_ `bool SerializeFromMismatchedTag(FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);`
- L98 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L100 _public prototype_ `bool IsParameterOverridden(const FGuid PropertyID) const;`
- L101 _public prototype_ `void SetParameterOverridden(const FGuid PropertyID, bool bIsOverridden);`
- L107 _private member_ `TObjectPtr<UCameraAsset> CameraAsset;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The referenced camera asset.
- L111 _private member_ `FInstancedOverridablePropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category="", meta=(FixedLayout, InterpBagProperties))` — The camera asset's parameters.
- L117 _private member_ `TArray<FGuid> ParameterOverrideGuids_DEPRECATED;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraAssetReference> : public TStructOpsTypeTraitsBase2<FCameraAssetReference>`  
_L123-130_
- inherits: `TStructOpsTypeTraitsBase2<FCameraAssetReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L126-129_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L127 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonf44cdadc0103`)
- L128 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonf44cdadc0103`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraContextDataReader.h` (Public)


#### struct `UE::Cameras::TCameraContextDataReader`  
`template<typename DataType> struct TCameraContextDataReader`  
_L13-100_
- L15 _public function_ `TCameraContextDataReader()`
- L18 _public function_ `template<typename ParameterType> TCameraContextDataReader(const ParameterType& Parameter)`
- L23 _public function_ `TCameraContextDataReader(const DataType* InDefaultValuePtr, FCameraContextDataID InDataID)`
- L29 _public function_ `template<typename ParameterType> void Initialize(const ParameterType& Parameter)`
- L41 _public function_ `void Initialize(const DataType* InDefaultValuePtr, FCameraContextDataID InDataID)`
- L49 _public function_ `DataType Get(const FCameraContextDataTable& ContextDataTable) const`
- L78 _public function_ `const DataType& GetRef(const FCameraContextDataTable& ContextDataTable) const`
- L98 _private member_ `const DataType* DefaultValuePtr = nullptr;`
- L99 _private member_ `FCameraContextDataID DataID;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraContextDataTable.h` (Public)


#### struct `UE::Cameras::TCameraContextDataTraits`  
`template<typename DataType> struct TCameraContextDataTraits`  
_L30-34_
- L32 _public prototype_ `static ECameraContextDataType GetDataType();`
- L33 _public prototype_ `static const UObject* GetDataTypeObject();`
- L520 _function_ `template<typename DataType> ECameraContextDataType TCameraContextDataTraits<DataType>::GetDataType()`
- L558 _function_ `template<typename DataType> const UObject* TCameraContextDataTraits<DataType>::GetDataTypeObject()`

#### enum `UE::Cameras::ECameraContextDataTableFilter`  
`enum class ECameraContextDataTableFilter`  
_L39-46_
- desc: Filter for context data table operations.
- L41 _public enumerator_ `None = 0`
- L43 _public enumerator_ `KnownOnly = 1 << 0` — Only include data that is common to both tables.
- L45 _public enumerator_ `ChangedOnly = 1 << 1` — Only include data that was written this frame.

#### class `UE::Cameras::FCameraContextDataTable`  
`class FCameraContextDataTable`  
_L54-318_
- desc: The camera context data table is a container for a collection of arbitrary values of various types. It is the companion of the camera variable table (see FCameraVariableTable) but for non-blendable values.
- L58 _public prototype_ `FCameraContextDataTable();`
- L59 _public prototype_ `~FCameraContextDataTable();`
- L62 _public prototype_ `void Initialize(const FCameraContextDataTableAllocationInfo& AllocationInfo);` — Initializes the context data table so that it fits the provided allocation info.
- L68 _public prototype_ `bool EnsureData(const FCameraContextDataTableAllocationInfo& AllocationInfo);` — Ensure that all the data referenced in the given allocation info exist in the table. Returns false if some data had to be added.
- L71 _public prototype_ `void AddData(const FCameraContextDataDefinition& DataDefinition);` — Adds a data entry to the table.
- L77 _public prototype_ `const FName& GetNameData(FCameraContextDataID InID) const;`
- L78 _public prototype_ `const FString& GetStringData(FCameraContextDataID InID) const;`
- L79 _public prototype_ `uint32 GetEnumData(FCameraContextDataID InID, const UEnum* EnumType) const;`
- L80 _public prototype_ `FConstStructView GetStructViewData(FCameraContextDataID InID, const UScriptStruct* StructType) const;`
- L81 _public prototype_ `FInstancedStruct GetInstancedStructData(FCameraContextDataID InID, const UScriptStruct* StructType) const;`
- L82 _public prototype_ `UObject* GetObjectData(FCameraContextDataID InID) const;`
- L83 _public prototype_ `UClass* GetClassData(FCameraContextDataID InID) const;`
- L86 _public prototype_ `template<typename EnumType> EnumType GetEnumData(FCameraContextDataID InID) const;`
- L89 _public prototype_ `template<typename StructType> const StructType& GetStructData(FCameraContextDataID InID) const;`
- L92 _public prototype_ `template<typename ObjectClass> ObjectClass* GetObjectData(FCameraContextDataID InID) const;`
- L95 _public prototype_ `template<typename BaseClass> TSubclassOf<BaseClass> GetClassData(FCameraContextDataID InID) const;`
- L98 _public prototype_ `template<typename ValueType> const ValueType* TryGetData(FCameraContextDataID InID) const;`
- L101 _public prototype_ `template<typename ValueType> TConstArrayView<ValueType> TryGetArrayData(FCameraContextDataID InID) const;`
- L104 _public prototype_ `template<typename ValueType> bool TryGetArrayData(FCameraContextDataID InID, TConstArrayView<ValueType>& OutValues) const;`
- L107 _public prototype_ `template<typename ValueType> const ValueType* TryGetArrayData(FCameraContextDataID InID, int32 ArrayIndex) const;`
- L111 _public prototype_ `void SetNameData(FCameraContextDataID InID, const FName& InData);`
- L112 _public prototype_ `void SetStringData(FCameraContextDataID InID, const FString& InData);`
- L113 _public prototype_ `void SetEnumData(FCameraContextDataID InID, const UEnum* EnumType, uint32 InData);`
- L114 _public prototype_ `void SetObjectData(FCameraContextDataID InID, UObject* InData);`
- L115 _public prototype_ `void SetClassData(FCameraContextDataID InID, UClass* InData);`
- L118 _public prototype_ `template<typename EnumType> void SetEnumData(FCameraContextDataID InID, EnumType InData);`
- L121 _public prototype_ `template<typename StructType> void SetStructData(FCameraContextDataID InID, const StructType& InData);`
- L123 _public prototype_ `void SetStructViewData(FCameraContextDataID InID, const FStructView& InData);`
- L124 _public prototype_ `void SetInstancedStructData(FCameraContextDataID InID, const FInstancedStruct& InData);`
- L126 _public prototype_ `void SetNameArrayData(FCameraContextDataID InID, TConstArrayView<FName> InData);`
- L127 _public prototype_ `void SetStringArrayData(FCameraContextDataID InID, TConstArrayView<FString> InData);`
- L128 _public prototype_ `void SetEnumArrayData(FCameraContextDataID InID, const UEnum* EnumType, TConstArrayView<uint32> InData);`
- L129 _public prototype_ `void SetObjectArrayData(FCameraContextDataID InID, TConstArrayView<UObject*> InData);`
- L130 _public prototype_ `void SetClassArrayData(FCameraContextDataID InID, TConstArrayView<UClass*> InData);`
- L133 _public prototype_ `template<typename EnumType> void SetEnumArrayData(FCameraContextDataID InID, TConstArrayView<EnumType> InData);`
- L136 _public prototype_ `template<typename StructType> void SetStructArrayData(FCameraContextDataID InID, TConstArrayView<StructType> InData);`
- L138 _public prototype_ `void SetStructViewArrayData(FCameraContextDataID InID, TConstArrayView<FStructView> InData);`
- L139 _public prototype_ `void SetInstancedStructArrayData(FCameraContextDataID InID, TConstArrayView<FInstancedStruct> InData);`
- L145 _public prototype_ `void OverrideAll(const FCameraContextDataTable& OtherTable);`
- L146 _public prototype_ `void OverrideKnown(const FCameraContextDataTable& OtherTable);`
- L147 _public prototype_ `void Override(const FCameraContextDataTable& OtherTable, ECameraContextDataTableFilter Filter);`
- L152 _public prototype_ `void AddReferencedObjects(FReferenceCollector& ReferenceCollector);` — Collects referenced objects.
- L157 _public typedef_ `using FEntryScriptArray = FScriptArray;` — Type of data for array entries.
- L160 _public prototype_ `const uint8* GetData( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, bool bOnlyIfWritten = true) const;` — Low-level API.
- L166 _public prototype_ `const uint8* TryGetData( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, bool bOnlyIfWritten = true) const;`
- L172 _public prototype_ `const FEntryScriptArray* TryGetArrayData( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, bool bOnlyIfWritten = true) const;`
- L178 _public prototype_ `const uint8* TryGetRawDataPtr( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, bool bOnlyIfWritten = true) const;`
- L184 _public prototype_ `void SetData( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, const uint8* InRawDataPtr, bool bMarkAsWrittenThisFrame = true);`
- L191 _public prototype_ `bool TrySetData( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, const uint8* InRawDataPtr, bool bMarkAsWrittenThisFrame = true);`
- L198 _public prototype_ `bool TrySetArrayDataNum( FCameraContextDataID DataID, int32 Count, bool bMarkAsWrittenThisFrame = true);`
- L203 _public prototype_ `bool TrySetArrayData( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, int32 Index, const uint8* InRawDataPtr, bool bMarkAsWrittenThisFrame = true);`
- L211 _public prototype_ `uint8* TryGetMutableRawDataPtr( FCameraContextDataID DataID, ECameraContextDataType ExpectedDataType, const UObject* ExpectedDataTypeObject, bool bMarkAsWrittenThisFrame = true);`
- L217 _public prototype_ `bool IsValueWritten(FCameraContextDataID InID) const;`
- L218 _public prototype_ `void UnsetValue(FCameraContextDataID InID);`
- L219 _public prototype_ `void UnsetAllValues();`
- L221 _public prototype_ `bool IsValueWrittenThisFrame(FCameraContextDataID InID) const;`
- L222 _public prototype_ `void ClearAllWrittenThisFrameFlags();`
- L224 _public prototype_ `void AutoResetValues();`
- L269 _private prototype_ `static bool GetDataTypeAllocationInfo(ECameraContextDataType DataType, const UObject* DataTypeObject, uint32& OutSizeOf, uint32& OutAlignOf);`
- L270 _private prototype_ `static bool GetDataTypeAllocationInfo(ECameraContextDataType DataType, ECameraContextDataContainerType DataContainerType, const UObject* DataTypeObject, uint32& OutSizeOf, uint32& OutAlignOf);`
- L272 _private prototype_ `static bool ConstructDataValue(ECameraContextDataType DataType, const UObject* DataTypeObject, uint8* DataPtr);`
- L273 _private prototype_ `static bool ConstructDataValue(ECameraContextDataType DataType, ECameraContextDataContainerType DataContainerType, const UObject* DataTypeObject, uint8* DataPtr);`
- L274 _private prototype_ `static bool DestroyDataValue(ECameraContextDataType DataType, const UObject* DataTypeObject, uint8* DataPtr);`
- L275 _private prototype_ `static bool DestroyDataValue(ECameraContextDataType DataType, ECameraContextDataContainerType DataContainerType, const UObject* DataTypeObject, uint8* DataPtr);`
- L277 _private prototype_ `static bool SetDataValue(ECameraContextDataType DataType, ECameraContextDataContainerType DataContainerType, const UObject* DataTypeObject, uint8* DestDataPtr, const uint8* SrcDataPtr);`
- L278 _private prototype_ `static bool SetDataValue(ECameraContextDataType DataType, const UObject* DataTypeObject, uint8* DestDataPtr, const uint8* SrcDataPtr);`
- L280 _private prototype_ `static void CreateEntry(const FCameraContextDataDefinition& DataDefinition, FEntry& OutEntry);`
- L282 _private prototype_ `const FEntry* FindEntry(FCameraContextDataID InID) const;`
- L283 _private prototype_ `FEntry* FindEntry(FCameraContextDataID InID);`
- L285 _private prototype_ `void InternalOverride(const FCameraContextDataTable& OtherTable, ECameraContextDataTableFilter Filter);`
- L287 _private prototype_ `void ReallocateBuffer(uint32 MinRequired = 0);`
- L288 _private prototype_ `void DestroyBuffer();`
- L291 _private prototype_ `template<typename StorageType> const StorageType* GetDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject) const;`
- L294 _private prototype_ `template<typename StorageType> bool SetDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject, const StorageType& InData);`
- L297 _private prototype_ `template<typename StorageType> TConstArrayView<StorageType> GetArrayDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject) const;`
- L300 _private prototype_ `template<typename StorageType> bool SetArrayDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject, TConstArrayView<StorageType> InData);`
- L304 _private member_ `static const uint32 GDefaultCapacity;`
- L305 _private member_ `static const uint32 GDefaultAlignment;`
- L307 _private member_ `TArray<FEntry> Entries;`
- L308 _private member_ `TMap<FCameraContextDataID, int32> EntryLookup;`
- L310 _private member_ `uint8* Memory = nullptr;`
- L311 _private member_ `uint32 Capacity = 0;`
- L312 _private member_ `uint32 Alignment = 0;`
- L313 _private member_ `uint32 Used = 0;`
- L333 _function_ `template<typename StructType> const StructType& FCameraContextDataTable::GetStructData(FCameraContextDataID InID) const`
- L345 _function_ `template<typename ObjectClass> ObjectClass* FCameraContextDataTable::GetObjectData(FCameraContextDataID InID) const`
- L355 _function_ `template<typename BaseClass> TSubclassOf<BaseClass> FCameraContextDataTable::GetClassData(FCameraContextDataID InID) const`
- L365 _function_ `template<typename ValueType> const ValueType* FCameraContextDataTable::TryGetData(FCameraContextDataID InID) const`
- L380 _function_ `template<typename ValueType> TConstArrayView<ValueType> FCameraContextDataTable::TryGetArrayData(FCameraContextDataID InID) const`
- L391 _function_ `template<typename ValueType> bool FCameraContextDataTable::TryGetArrayData(FCameraContextDataID InID, TConstArrayView<ValueType>& OutValues) const`
- L408 _function_ `template<typename ValueType> const ValueType* FCameraContextDataTable::TryGetArrayData(FCameraContextDataID InID, int32 ArrayIndex) const`
- L419 _function_ `template<typename EnumType> void FCameraContextDataTable::SetEnumData(FCameraContextDataID InID, EnumType InData)`
- L425 _function_ `template<typename StructType> void FCameraContextDataTable::SetStructData(FCameraContextDataID InID, const StructType& InData)`
- L431 _function_ `template<typename EnumType> void FCameraContextDataTable::SetEnumArrayData(FCameraContextDataID InID, TConstArrayView<EnumType> InData)`
- L442 _function_ `template<typename StructType> void FCameraContextDataTable::SetStructArrayData(FCameraContextDataID InID, TConstArrayView<StructType> InData)`
- L448 _function_ `template<typename StorageType> const StorageType* FCameraContextDataTable::GetDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject) const`
- L464 _function_ `template<typename StorageType> bool FCameraContextDataTable::SetDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject, const StorageType& InData)`
- L481 _function_ `template<typename StorageType> TConstArrayView<StorageType> FCameraContextDataTable::GetArrayDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject) const`
- L498 _function_ `template<typename StorageType> bool FCameraContextDataTable::SetArrayDataImpl(FCameraContextDataID InID, ECameraContextDataType DataType, const UObject* DataTypeObject, TConstArrayView<StorageType> InData)`

#### enum `UE::Cameras::FCameraContextDataTable::EEntryFlags`  
`enum class EEntryFlags : uint8`  
_L228-234_
- L230 _public enumerator_ `None = 0`
- L231 _public enumerator_ `AutoReset = 1 << 1`
- L232 _public enumerator_ `Written = 1 << 2`
- L233 _public enumerator_ `WrittenThisFrame = 1 << 3`

#### struct `UE::Cameras::FCameraContextDataTable::FEntry`  
`struct FEntry`  
_L237-248_
- L239 _public member_ `FCameraContextDataID ID;`
- L240 _public member_ `ECameraContextDataType Type;`
- L241 _public member_ `ECameraContextDataContainerType ContainerType;`
- L242 _public member_ `TObjectPtr<const UObject> TypeObject;`
- L243 _public member_ `uint32 Offset;`
- L244 _public member_ `EEntryFlags Flags;`
- L246 _public member_ `FString DebugName;`

#### struct `UE::Cameras::FCameraContextDataTable::FArrayEntryHelper`  
`struct FArrayEntryHelper`  
_L250-267_
- L252 _public prototype_ `FArrayEntryHelper(const FEntry& Entry, uint8* TableMemory);`
- L253 _public prototype_ `FArrayEntryHelper(ECameraContextDataType DataType, const UObject* DataTypeObject, uint8* RawPtr);`
- L255 _public prototype_ `bool IsValidIndex(int32 Index) const;`
- L256 _public prototype_ `int32 Num() const;`
- L257 _public prototype_ `uint8* GetRawPtr(int32 Index);`
- L258 _public prototype_ `void Resize(int32 Count);`
- L260 _public member_ `ECameraContextDataType ElementType;`
- L261 _public member_ `TObjectPtr<const UObject> ElementTypeObject;`
- L263 _public member_ `uint32 ElementSizeOf;`
- L264 _public member_ `uint32 ElementAlignOf;`
- L266 _public member_ `FEntryScriptArray* ScriptArray;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Cameras` (scope `UE`)
- L320 _function_ `ENUM_CLASS_FLAGS(FCameraContextDataTable::EEntryFlags) template<typename EnumType> EnumType FCameraContextDataTable::GetEnumData(FCameraContextDataID InID) const` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraContextDataTableAllocationInfo.h` (Public)


#### struct `FCameraContextDataDefinition`  
`struct FCameraContextDataDefinition`  
_L18-49_
- reflection: `USTRUCT()`
- desc: Definition for one entry in a camera rig's context data registry.
- L24 _public member_ `FCameraContextDataID DataID;` — `UPROPERTY()` — The ID of data.
- L28 _public member_ `ECameraContextDataType DataType = ECameraContextDataType::Name;` — `UPROPERTY()` — The type of the data.
- L32 _public member_ `ECameraContextDataContainerType DataContainerType = ECameraContextDataContainerType::None;` — `UPROPERTY()` — The type of container for the data.
- L36 _public member_ `TObjectPtr<const UObject> DataTypeObject;` — `UPROPERTY()` — An extra type object for the data.
- L40 _public member_ `bool bAutoReset = false;` — `UPROPERTY()` — Whether the data should auto-reset to an "unset" state after every evaluation.
- L45 _public member_ `FString DataName;` — `UPROPERTY()` — The name of the data, for debugging purposes.
- L48 _public prototype_ `bool operator==(const FCameraContextDataDefinition& Other) const = default;`

#### struct `FCameraContextDataTableAllocationInfo`  
`struct FCameraContextDataTableAllocationInfo`  
_L55-70_
- reflection: `USTRUCT()`
- desc: Collection of context data entries for a camera rig.
- L61 _public member_ `TArray<FCameraContextDataDefinition> DataDefinitions;` — `UPROPERTY()` — The list of context data definitions.
- L64 _public prototype_ `void Combine(const FCameraContextDataTableAllocationInfo& OtherInfo);` — Combines the given allocation info with this one.
- L67 _public prototype_ `bool Contains(const FCameraContextDataTableAllocationInfo& OtherInfo) const;` — Returns whether the given data definitions already exist in our list.
- L69 _public prototype_ `bool operator==(const FCameraContextDataTableAllocationInfo& Other) const = default;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraContextDataTableFwd.h` (Public)


#### enum `ECameraContextDataType`  
`enum class ECameraContextDataType`  
_L26-36_
- reflection: `UENUM()`
- desc: Supported types for a camera node's context data. NOTE: simple types (bool, integer, float, etc.) and vector types (vector, rotator, transform) are not supported as context data because they are supported as blendable parameters.
- L28 _public enumerator_ `Name`
- L29 _public enumerator_ `String`
- L30 _public enumerator_ `Enum UMETA(Hidden)`
- L31 _public enumerator_ `Struct UMETA(Hidden)`
- L32 _public enumerator_ `Object UMETA(Hidden)`
- L33 _public enumerator_ `Class UMETA(Hidden)`
- L35 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ECameraContextDataContainerType`  
`enum class ECameraContextDataContainerType`  
_L42-46_
- reflection: `UENUM()`
- desc: Supported container types for a camera node's context data.
- L44 _public enumerator_ `None`
- L45 _public enumerator_ `Array`

#### struct `FCameraContextDataID`  
`struct FCameraContextDataID`  
_L52-107_
- reflection: `USTRUCT(BlueprintType)`
- desc: The ID of a context data, used to refer to it in a camera context data table.
- L58 _public function_ `FCameraContextDataID() : Value(INVALID)`
- L60 _public function_ `uint32 GetValue() const`
- L62 _public function_ `bool IsValid() const`
- L64 _public function_ `explicit operator bool() const`
- L66 _public function_ `static FCameraContextDataID FromHashValue(uint32 InValue)`
- L101 _private function_ `FCameraContextDataID(uint32 InValue) : Value(InValue)`
- L103 _private member_ `static const uint32 INVALID = uint32(-1);`
- L106 _private member_ `uint32 Value;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)
- L73 _function_ `friend bool operator<(FCameraContextDataID A, FCameraContextDataID B)`
- L78 _function_ `friend bool operator==(FCameraContextDataID A, FCameraContextDataID B)`
- L83 _function_ `friend bool operator!=(FCameraContextDataID A, FCameraContextDataID B)`
- L88 _function_ `friend uint32 GetTypeHash(FCameraContextDataID In)`
- L93 _function_ `friend FArchive& operator<< (FArchive& Ar, FCameraContextDataID& In)`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraDirector.h` (Public)


#### struct `FCameraDirectorFactoryCreateParams`  
`struct FCameraDirectorFactoryCreateParams`  
_L26-28_
- desc: Parameter struct passed by an asset factory when a new camera asset is created. This lets a camera director setup data before the editor opens.

#### struct `FCameraDirectorRigUsageInfo`  
`struct FCameraDirectorRigUsageInfo`  
_L35-41_
- desc: Parameter struct for gathering camera rigs used by a director.
- L38 _public member_ `TArray<UCameraRigAsset*> CameraRigs;` — Camera rigs used by the camera director.
- L40 _public member_ `TArray<UCameraRigProxyAsset*> CameraRigProxies;` — Camera rig proxies used by the camera director.

#### class `UCameraDirector`  
`class UCameraDirector : public UObject`  
_L47-117_
- reflection: `UCLASS(MinimalAPI, Abstract, DefaultToInstanced)`
- inherits: `UObject`
- desc: Base class for a camera director.
- L53 _public typedef_ `using FCameraDirectorEvaluatorBuilder = UE::Cameras::FCameraDirectorEvaluatorBuilder;`
- L56 _public prototype_ `FCameraDirectorEvaluatorPtr BuildEvaluator(FCameraDirectorEvaluatorBuilder& Builder) const;` — Build the evaluator for this director.
- L59 _public prototype_ `void BuildCameraDirector(UE::Cameras::FCameraBuildContext& BuildContext);` — Builds and validates this camera director.
- L62 _public prototype_ `void GatherRigUsageInfo(FCameraDirectorRigUsageInfo& UsageInfo) const;` — Gets the list of camera rigs used by this camera director.
- L65 _public prototype_ `void ExtendAssetRegistryTags(FAssetRegistryTagsContext Context) const;` — Extend the owning camera asset's tags.
- L69 _public prototype_ `void FactoryCreateAsset(const FCameraDirectorFactoryCreateParams& InParams);` — Called by the asset factories to setup new data before the editor opens.
- L75 _public prototype_ `virtual void PostLoad() override;` — UObject interface.
- L80 _protected function_ `virtual FCameraDirectorEvaluatorPtr OnBuildEvaluator(FCameraDirectorEvaluatorBuilder& Builder) const` — Build the evaluator for this director.
- L83 _protected function_ `virtual void OnBuildCameraDirector(UE::Cameras::FCameraBuildContext& BuildContext)` — Builds and validates this camera director.
- L86 _protected function_ `virtual void OnGatherRigUsageInfo(FCameraDirectorRigUsageInfo& UsageInfo) const` — Gets the list of camera rigs used by this camera director.
- L89 _protected function_ `virtual void OnExtendAssetRegistryTags(FAssetRegistryTagsContext Context) const` — Extend the owning camera asset's tags.
- L93 _protected function_ `virtual void OnFactoryCreateAsset(const FCameraDirectorFactoryCreateParams& InParams)` — Called by the asset factories to setup new data before the editor opens.
- L103 _public member_ `FCameraRigProxyRedirectTable CameraRigProxyRedirectTable;` — `UPROPERTY(EditAnywhere, Category="Evaluation")` — The table that maps camera rig proxies (used in the evaluator Blueprint graph) to actual camera rigs.
- L109 _public member_ `bool bRunInEditor = false;` — `UPROPERTY(EditAnywhere, Category="Evaluation")` — Whether this camera director should run in the editor.
- L115 _private member_ `TObjectPtr<UCameraRigProxyTable> CameraRigProxyTable_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraDirectorEvaluator.h` (Public)


#### struct `UE::Cameras::FCameraDirectorInitializeParams`  
`struct FCameraDirectorInitializeParams`  
_L28-32_
- desc: Parameter structure for initializing a newly created camera director evaluator.
- L31 _public member_ `TSharedPtr<FCameraEvaluationContext> OwnerContext;` — The evaluation context that owns the camera director.

#### struct `UE::Cameras::FCameraDirectorActivateParams`  
`struct FCameraDirectorActivateParams`  
_L40-44_
- desc: Parameter structure for activating a camera director evaluator. A camera director evaluator can be activated and deactivated multiple times. This means that OnActivated/OnDeactivated can be called multiple times in pairs, unlike OnInitialize which is only called once.
- L43 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The camera system that will run the camera director.

#### struct `UE::Cameras::FCameraDirectorDeactivateParams`  
`struct FCameraDirectorDeactivateParams`  
_L49-51_
- desc: Parameter structure for deactivating a camera director evaluator.

#### struct `UE::Cameras::FCameraDirectorEvaluationParams`  
`struct FCameraDirectorEvaluationParams`  
_L56-60_
- desc: Parameter structure for running a camera director.
- L59 _public member_ `float DeltaTime = 0.f;` — Time interval for the update.

#### enum `UE::Cameras::ECameraRigActivationDeactivationRequestType`  
`enum class ECameraRigActivationDeactivationRequestType`  
_L63-67_
- desc: The type of request for activating or deactivating a camera rig.
- L65 _public enumerator_ `Activate`
- L66 _public enumerator_ `Deactivate`

#### struct `UE::Cameras::FCameraRigActivationDeactivationRequest`  
`struct FCameraRigActivationDeactivationRequest`  
_L72-117_
- desc: Structure for requesting that a camera rig be activated or deactivated.
- L75 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context to run the specified camera rig.
- L77 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The camera rig that should be running.
- L79 _public member_ `TObjectPtr<const UCameraRigProxyAsset> CameraRigProxy;` — The camera proxy that determines the rig that should be running (if CameraRig is null).
- L81 _public member_ `ECameraRigActivationDeactivationRequestType RequestType = ECameraRigActivationDeactivationRequestType::Activate;` — The type of the request.
- L83 _public member_ `ECameraRigLayer Layer = ECameraRigLayer::Main;` — The layer on which to activate or deactivate this camera rig.
- L85 _public member_ `TObjectPtr<const UCameraRigTransition> TransitionOverride;` — A transition to use for this activation, if possible, instead of looking up one according to usual rules.
- L87 _public member_ `int32 OrderKey = 0;` — An order key for activating camera rigs on ordered layers.
- L89 _public member_ `bool bForceActivateDeactivate = false;` — Whether to force creating a new instance, even if an identical one is already active.
- L93 _public function_ `FCameraRigActivationDeactivationRequest()`
- L95 _public function_ `FCameraRigActivationDeactivationRequest( TSharedPtr<const FCameraEvaluationContext> InContext, TObjectPtr<const UCameraRigAsset> InCameraRig) : EvaluationContext(InContext) , CameraRig(InCameraRig)`
- L101 _public function_ `FCameraRigActivationDeactivationRequest( TSharedPtr<const FCameraEvaluationContext> InContext, TObjectPtr<const UCameraRigProxyAsset> InCameraRigProxy) : EvaluationContext(InContext) , CameraRigProxy(InCameraRigProxy)`
- L108 _public function_ `bool IsValid() const`
- L115 _public prototype_ `bool ResolveCameraRigProxyIfNeeded(const FCameraDirectorEvaluator* InDirectorEvaluator);`
- L116 _public prototype_ `bool ResolveCameraRigProxyIfNeeded(const UCameraDirector* InDirector);`

#### struct `UE::Cameras::FCameraDirectorEvaluationResult`  
`struct FCameraDirectorEvaluationResult`  
_L122-173_
- desc: Result structure for running a camera director.
- L124 _public typedef_ `using FRequests = TArray<FCameraRigActivationDeactivationRequest, TInlineAllocator<4>>;`
- L127 _public member_ `FRequests Requests;` — Requests for activating/deactivating camera rigs this frame.
- L130 _public function_ `void Add( TSharedPtr<const FCameraEvaluationContext> InEvaluationContext, TObjectPtr<const UCameraRigAsset> InCameraRig)` — Adds a simple activation request for the main layer.
- L138 _public function_ `void Add( TSharedPtr<const FCameraEvaluationContext> InEvaluationContext, TObjectPtr<const UCameraRigProxyAsset> InCameraRigProxy)` — Adds a simple activation request for the main layer.
- L146 _public function_ `void Add( TSharedPtr<const FCameraEvaluationContext> InEvaluationContext, TObjectPtr<const UCameraRigAsset> InCameraRig, ECameraRigLayer Layer, int32 OrderKey)` — Adds an activation request for the specified layer
- L158 _public function_ `void Remove( TSharedPtr<const FCameraEvaluationContext> InEvaluationContext, TObjectPtr<const UCameraRigAsset> InCameraRig, ECameraRigLayer Layer)` — Adds a deactivation request for the specified layer
- L169 _public function_ `void Reset()` — Reset this result.

#### struct `UE::Cameras::FCameraDirectorEvaluatorBuilder`  
`struct FCameraDirectorEvaluatorBuilder`  
_L178-191_
- desc: Structure for building director evaluators.
- L180 _public function_ `FCameraDirectorEvaluatorBuilder(FCameraDirectorEvaluatorStorage& InStorage) : Storage(InStorage)`
- L186 _public prototype_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* BuildEvaluator(ArgTypes&&... InArgs);` — Builds a director evaluator of the given type.
- L190 _private member_ `FCameraDirectorEvaluatorStorage& Storage;`
- L349 _function_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* FCameraDirectorEvaluatorBuilder::BuildEvaluator(ArgTypes&&... InArgs)`

#### class `UE::Cameras::FCameraDirectorEvaluatorStorage`  
`class FCameraDirectorEvaluatorStorage`  
_L196-213_
- desc: Storage for a director evaluator.
- L201 _public function_ `FCameraDirectorEvaluator* GetEvaluator() const` — Gets the stored evaluator, if any.
- L204 _public prototype_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* BuildEvaluator(ArgTypes&&... InArgs);`
- L206 _public prototype_ `void DestroyEvaluator();`
- L210 _private member_ `TSharedPtr<FCameraDirectorEvaluator> Evaluator;`
- L355 _function_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* FCameraDirectorEvaluatorStorage::BuildEvaluator(ArgTypes&&... InArgs)`

#### class `UE::Cameras::FCameraDirectorEvaluator`  
`class FCameraDirectorEvaluator`  
_L218-346_
- desc: Base class for camera director evaluators.
- L224 _public prototype_ `FCameraDirectorEvaluator();`
- L225 _public prototype_ `virtual ~FCameraDirectorEvaluator() = default;`
- L228 _public prototype_ `void Initialize(const FCameraDirectorInitializeParams& Params);` — Initializes a camera director evalutor.
- L231 _public prototype_ `void Activate(const FCameraDirectorActivateParams& Params, FCameraDirectorEvaluationResult& OutResult);` — Activates the camera director evaluator.
- L234 _public prototype_ `void Deactivate(const FCameraDirectorDeactivateParams& Params, FCameraDirectorEvaluationResult& OutResult);` — Deactivates the camera director evaluator.
- L237 _public function_ `const UCameraDirector* GetCameraDirector() const` — Gets the camera director.
- L241 _public function_ `template<typename CameraDirectorType> const CameraDirectorType* GetCameraDirectorAs() const` — Gets the camera director.
- L247 _public function_ `TSharedPtr<FCameraEvaluationContext> GetEvaluationContext() const` — Gets the owning evaluation context.
- L252 _public prototype_ `void Run(const FCameraDirectorEvaluationParams& Params, FCameraDirectorEvaluationResult& OutResult);` — Runs the camera director to determine what camera rig(s) should be active this frame.
- L255 _public prototype_ `void OverrideNextActivationTransition(const UCameraRigTransition* TransitionOverride);` — Request that the next camera rig activation use the provided transition.
- L258 _public prototype_ `void ForceNextActivation();` — Request that the next camera rig activation be forced.
- L263 _public prototype_ `bool AddChildEvaluationContext(TSharedRef<FCameraEvaluationContext> InContext);` — Add a child context to this camera director.
- L266 _public prototype_ `bool RemoveChildEvaluationContext(TSharedRef<FCameraEvaluationContext> InContext);` — Remove the given child context from this camera director.
- L269 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Garbage collection pass.
- L275 _public prototype_ `void SetPrivateCameraDirector(const UCameraDirector* InCameraDirector);`
- L277 _public prototype_ `const UCameraRigAsset* FindCameraRigByProxy(const UCameraRigProxyAsset* InProxy) const;`
- L279 _public prototype_ `void OnEndCameraSystemUpdate();`
- L310 _protected function_ `virtual void OnInitialize(const FCameraDirectorInitializeParams& Params)` — Initializes a camera director evalutor. Only called once after construction.
- L313 _protected function_ `virtual void OnActivate(const FCameraDirectorActivateParams& Params, FCameraDirectorEvaluationResult& OutResult)` — Activates the camera director evaluator. May be called multiple times, in pair with OnDeactivate.
- L316 _protected function_ `virtual void OnDeactivate(const FCameraDirectorDeactivateParams& Params, FCameraDirectorEvaluationResult& OutResult)` — Deactivates the camera director evaluator. May be called multiple times, in pair with OnActivate.
- L319 _protected function_ `virtual void OnRun(const FCameraDirectorEvaluationParams& Params, FCameraDirectorEvaluationResult& OutResult)` — Runs the camera director to determine what camera rig(s) should be active this frame.
- L322 _protected function_ `virtual void OnAddChildEvaluationContext(const FChildContextManulationParams& Params, FChildContextManulationResult& Result)` — Add a child context to this camera director.
- L325 _protected function_ `virtual void OnRemoveChildEvaluationContext(const FChildContextManulationParams& Params, FChildContextManulationResult& Result)` — Remove the given child context from this camera director.
- L328 _protected function_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector)` — Garbage collection pass.
- L333 _private member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The camera system this evaluator is running inside of.
- L336 _private member_ `TWeakPtr<FCameraEvaluationContext> WeakOwnerContext;` — The evaluation context that owns this evaluator.
- L339 _private member_ `TObjectPtr<const UCameraDirector> PrivateCameraDirector;` — The camera director this evaluator is running.
- L342 _private member_ `TObjectPtr<const UCameraRigTransition> NextActivationTransitionOverride;` — A forced transition to use on the next update. Cleared after every system update.
- L345 _private member_ `bool bNextActivationForce = false;` — Whether to force camera rig activation on the next update. Cleared after every system update.

#### enum `UE::Cameras::FCameraDirectorEvaluator::EChildContextManipulationResult`  
`enum class EChildContextManipulationResult`  
_L284-292_
- desc: Result for adding/removing children contexts.
- L287 _public enumerator_ `Failure` — The add or removal failed.
- L289 _public enumerator_ `Success` — The add or removal was successful.
- L291 _public enumerator_ `ChildContextSuccess` — The add or removal was successfully handled by a child director.

#### struct `UE::Cameras::FCameraDirectorEvaluator::FChildContextManulationParams`  
`struct FChildContextManulationParams`  
_L295-299_
- desc: Parameter struct for adding/removing children contexts.
- L297 _public member_ `TSharedPtr<FCameraEvaluationContext> ParentContext;`
- L298 _public member_ `TSharedPtr<FCameraEvaluationContext> ChildContext;`

#### struct `UE::Cameras::FCameraDirectorEvaluator::FChildContextManulationResult`  
`struct FChildContextManulationResult`  
_L302-307_
- desc: Result struct for adding/removing children contexts.
- L304 _public member_ `EChildContextManipulationResult Result = EChildContextManipulationResult::Failure;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)
- L366 _typedef_ `using FCameraDirectorEvaluatorPtr = UE::Cameras::FCameraDirectorEvaluator*;` — Typedef to avoid having to deal with namespaces in UCameraNode subclasses.
- L370 _macro_ `#define UE_DECLARE_CAMERA_DIRECTOR_EVALUATOR(ApiDeclSpec, ClassName)\` — Utility macros for declaring and defining camera director evaluators.
- L373 _macro_ `#define UE_DECLARE_CAMERA_DIRECTOR_EVALUATOR_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L376 _macro_ `#define UE_DEFINE_CAMERA_DIRECTOR_EVALUATOR(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraEvaluationContext.h` (Public)


#### enum `ECameraEvaluationDataCondition`  
`enum class ECameraEvaluationDataCondition : uint8`  
_L19-22_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `ActiveCameraRig`

#### struct `UE::Cameras::FCameraEvaluationContextInitializeParams`  
`struct FCameraEvaluationContextInitializeParams`  
_L33-41_
- desc: Parameter struct for initializing an evaluation context.
- L36 _public member_ `TObjectPtr<UObject> Owner;` — The owner of the context, if any.
- L38 _public member_ `TObjectPtr<const UCameraAsset> CameraAsset;` — The camera asset to run inside the context, if any.
- L40 _public member_ `TObjectPtr<APlayerController> PlayerController;` — The player controller driving this context, if any.

#### struct `UE::Cameras::FCameraEvaluationContextActivateParams`  
`struct FCameraEvaluationContextActivateParams`  
_L47-54_
- desc: Parameter struct for activating an evaluation context, which happens when it is added to the camera system's context stack.
- L50 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The system the context will evaluate inside of.
- L53 _public member_ `TSharedPtr<FCameraEvaluationContext> ParentContext;` — The parent context, if any.

#### struct `UE::Cameras::FCameraEvaluationContextDeactivateParams`  
`struct FCameraEvaluationContextDeactivateParams`  
_L60-62_
- desc: Parameter struct for deactivating an evaluation context, which happens when it is removed from the camera system's context stack.

#### class `UE::Cameras::FCameraEvaluationContext`  
`class FCameraEvaluationContext : public TSharedFromThis<FCameraEvaluationContext>`  
_L67-241_
- inherits: `TSharedFromThis<FCameraEvaluationContext>`
- desc: Base class for providing a context to running camera rigs.
- L74 _public prototype_ `FCameraEvaluationContext();` — Constructs an evaluation context.
- L76 _public prototype_ `FCameraEvaluationContext(const FCameraEvaluationContextInitializeParams& Params);` — Constructs an evaluation context.
- L79 _public prototype_ `void Initialize(const FCameraEvaluationContextInitializeParams& Params);` — Initializes the evaluation context, if it was created with the default constructor.
- L82 _public prototype_ `virtual ~FCameraEvaluationContext();` — Destroys this evaluation context.
- L85 _public function_ `UObject* GetOwner() const` — Gets the owner of this evaluation context, if any, and if still valid.
- L91 _public prototype_ `UWorld* GetWorld() const;` — Gets the world in which this evaluation context runs. This is the owner's world.
- L97 _public function_ `APlayerController* GetPlayerController() const` — Gets the player controller (if any) in control of the cameras running inside of this evaluation context.
- L100 _public function_ `const UCameraAsset* GetCameraAsset() const` — Gets the camera asset that is hosted in this context.
- L103 _public function_ `const FCameraNodeEvaluationResult& GetInitialResult() const` — Gets the initial evaluation result for all camera rigs in this context.
- L106 _public function_ `FCameraNodeEvaluationResult& GetInitialResult()` — Gets the initial evaluation result for all camera rigs in this context.
- L109 _public function_ `FCameraDirectorEvaluator* GetDirectorEvaluator() const` — Gets the camera director evaluator that runs the camera rigs of this context.
- L112 _public function_ `TSharedPtr<const FCameraEvaluationContext> GetParentContext() const` — Gets the parent evaluation context, if any.
- L115 _public function_ `TSharedPtr<FCameraEvaluationContext> GetParentContext()` — Gets the parent evaluation context, if any.
- L118 _public function_ `TArrayView<const TSharedPtr<FCameraEvaluationContext>> GetChildrenContexts() const` — Gets the children evaluation contexts running inside this context.
- L121 _public prototype_ `FIntPoint GetViewportSize() const;` — Gets the size of the viewport that cameras inside the context are being viewed through.
- L126 _public function_ `const FCameraNodeEvaluationResult* GetConditionalResult(ECameraEvaluationDataCondition Condition) const` — Gets an evaluation result that will be conditionally overlaid on some camera rigs in this context.
- L129 _public function_ `FCameraNodeEvaluationResult* GetConditionalResult(ECameraEvaluationDataCondition Condition)` — Gets an evaluation result that will be conditionally overlaid on some camera rigs in this context.
- L132 _public prototype_ `FCameraNodeEvaluationResult& GetOrAddConditionalResult(ECameraEvaluationDataCondition Condition);` — Gets or adds an evaluation result that will be conditionally overlaid on some camera rigs in this context.
- L140 _public prototype_ `void Activate(const FCameraEvaluationContextActivateParams& Params);` — Activates this evaluation context. This will create the camera director evaluator if necessary.
- L145 _public prototype_ `void Deactivate(const FCameraEvaluationContextDeactivateParams& Params);` — Deactivates this evaluation context.
- L148 _public function_ `bool IsActive() const` — Whether this context is active.
- L154 _public prototype_ `TSharedPtr<FCameraSystemEvaluator> GetCameraSystemEvaluator() const;` — Returns the camera system for which this context was activated, or null if this context is currently not active.
- L159 _public prototype_ `bool AddChildContext(TSharedRef<FCameraEvaluationContext> ChildContext);` — Adds a child context.
- L162 _public prototype_ `bool RemoveChildContext(TSharedRef<FCameraEvaluationContext> ChildContext);` — Removes a child context.
- L167 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Internal API.
- L169 _public prototype_ `void OnEndCameraSystemUpdate();`
- L171 _public prototype_ `bool RegisterChildContext(TSharedRef<FCameraEvaluationContext> ChildContext);`
- L172 _public prototype_ `bool UnregisterChildContext(TSharedRef<FCameraEvaluationContext> ChildContext);`
- L175 _public prototype_ `void SetEditorPreviewCameraRigIndex(int32 Index);`
- L180 _protected function_ `virtual void OnActivate(const FCameraEvaluationContextActivateParams& Params)`
- L181 _protected function_ `virtual void OnDeactivate(const FCameraEvaluationContextDeactivateParams& Params)`
- L182 _protected function_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector)`
- L184 _protected function_ `FCameraSystemEvaluator* GetPrivateCameraSystemEvaluator() const`
- L186 _protected prototype_ `void AutoCreateDirectorEvaluator();`
- L189 _protected prototype_ `void AutoCreateEditorPreviewDirectorEvaluator(const FCameraEvaluationContextActivateParams& Params);`
- L194 _private prototype_ `void ExecuteSetupAndTeardownRequests(FCameraDirectorEvaluationResult& DirectorResult);`
- L199 _protected member_ `TWeakObjectPtr<> WeakOwner;` — The owner of this context, if any.
- L205 _protected member_ `TWeakObjectPtr<APlayerController> WeakPlayerController;` — The player controller (if any) in control of the cameras running inside of this evaluation context.
- L208 _protected member_ `TObjectPtr<const UCameraAsset> CameraAsset;` — The camera asset hosted in this context.
- L211 _protected member_ `FCameraNodeEvaluationResult InitialResult;` — The initial result for all camera rigs in this context.
- L214 _protected member_ `TOptional<FIntPoint> OverrideViewportSize;` — An optional viewport size, if there is no PlayerController, or its viewport should not be used.
- L219 _private member_ `FCameraDirectorEvaluatorStorage DirectorEvaluatorStorage;` — The camera director evaluator, usually only valid if this context has been activated.
- L220 _private member_ `FCameraDirectorEvaluator* DirectorEvaluator = nullptr;`
- L223 _private member_ `FCameraSystemEvaluator* CameraSystemEvaluator = nullptr;` — The camera system that this context has been activated for, or null if the context isn't currently active.
- L226 _private member_ `TWeakPtr<FCameraEvaluationContext> WeakParent;` — The parent context, if any.
- L229 _private typedef_ `using FChildrenContexts = TArray<TSharedPtr<FCameraEvaluationContext>>;` — The children contexts, if any.
- L230 _private member_ `FChildrenContexts ChildrenContexts;`
- L233 _private typedef_ `using FConditionalResults = TMap<ECameraEvaluationDataCondition, FCameraNodeEvaluationResult>;` — Conditional camera data for camera rigs running inside this context.
- L234 _private member_ `FConditionalResults ConditionalResults;`
- L237 _private member_ `bool bInitialized = false;` — Whether this context was initialized.
- L240 _private member_ `bool bActivated = false;` — Whether this context is active.

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Cameras` (scope `UE`)
- L247 _macro_ `#define UE_DECLARE_CAMERA_EVALUATION_CONTEXT(ApiDeclSpec, ClassName)\` — Utility macros for declaring and defining camera evaluation contexts.
- L250 _macro_ `#define UE_DECLARE_CAMERA_EVALUATION_CONTEXT_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L253 _macro_ `#define UE_DEFINE_CAMERA_EVALUATION_CONTEXT(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraEvaluationContextStack.h` (Public)


#### struct `UE::Cameras::FCameraEvaluationContextStack`  
`struct FCameraEvaluationContextStack`  
_L23-108_
- desc: A simple stack of evaluation contexts. The top one is the active one.
- L27 _public prototype_ `~FCameraEvaluationContextStack();`
- L32 _public prototype_ `TSharedPtr<FCameraEvaluationContext> GetActiveContext() const;` — Gets the active (top) context.
- L35 _public prototype_ `bool HasContext(TSharedRef<FCameraEvaluationContext> Context) const;` — Returns whether the given context exists in the stack.
- L38 _public prototype_ `void PushContext(TSharedRef<FCameraEvaluationContext> Context);` — Push a new context on the stack and instantiate its director.
- L48 _public prototype_ `bool AddChildContext(TSharedRef<FCameraEvaluationContext> Context, TSharedPtr<FCameraEvaluationContext> ParentContext = nullptr);` — Tries to add a context inside the given context. This will query the active context's director in order to find an "available spot" for the child context. @param Context  The new context to activate. @param ParentContext  The parent context to activate inside of, or the active context (if any) if null. @return Whether the child context was acccepted.
- L51 _public prototype_ `bool RemoveContext(TSharedRef<FCameraEvaluationContext> Context);` — Remove an existing context from the stack.
- L54 _public prototype_ `bool RemoveContextsOwnedBy(UObject* ContextOwner, bool bAlsoRemoveInnerOwners = false);` — Remove contexts owned by the given object.
- L57 _public prototype_ `void PopContext();` — Pop the active (top) context.
- L60 _public function_ `int32 NumContexts() const` — The number of contexts on the stack.
- L63 _public prototype_ `void GetAllContexts(TArray<TSharedPtr<FCameraEvaluationContext>>& OutContexts) const;` — Gets all the contexts in the stack, from bottom to top.
- L66 _public prototype_ `TSharedPtr<FCameraEvaluationContext> FindContextByOwner(const UObject* InOwner) const;` — Finds a context owned by the given object, if any.
- L74 _public prototype_ `template<typename Predicate> TSharedPtr<FCameraEvaluationContext> FindContextByPredicate(Predicate Pred) const;` — Finds a context that fulfills the given predicate. The predicate function must have the signature: (TSharedRef<FCameraEvaluationContext>) -> bool
- L77 _public prototype_ `void Reset();` — Empties the stack of all contexts.
- L80 _public function_ `FSimpleMulticastDelegate& OnStackChanged()` — An event raised when the stack changes.
- L85 _public prototype_ `void Initialize(FCameraSystemEvaluator& InEvaluator);` — Internal API
- L86 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L87 _public prototype_ `void OnEndCameraSystemUpdate();`
- L97 _private member_ `TArray<FContextEntry> Entries;` — The entries in the stack.
- L100 _private member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The owner evaluator.
- L103 _private member_ `FSimpleMulticastDelegate OnStackChangedEvent;` — An event raised when the stack changes.
- L111 _function_ `template<typename Predicate> TSharedPtr<FCameraEvaluationContext> FCameraEvaluationContextStack::FindContextByPredicate(Predicate Pred) const`

#### struct `UE::Cameras::FCameraEvaluationContextStack::FContextEntry`  
`struct FContextEntry`  
_L91-94_
- L93 _public member_ `TWeakPtr<FCameraEvaluationContext> WeakContext;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraEvaluationService.h` (Public)


#### enum `UE::Cameras::ECameraEvaluationServiceFlags`  
`enum class ECameraEvaluationServiceFlags`  
_L21-30_
- desc: Flags for what callbacks an evaluation service wants to opt-into.
- L23 _public enumerator_ `None = 0`
- L24 _public enumerator_ `NeedsPreUpdate = 1 << 0`
- L25 _public enumerator_ `NeedsPostCameraDirectorUpdate = 1 << 1`
- L26 _public enumerator_ `NeedsPostUpdate = 1 << 2`
- L27 _public enumerator_ `NeedsRootCameraNodeEvents = 1 << 3`
- L29 _public enumerator_ `Default = NeedsPreUpdate | NeedsPostCameraDirectorUpdate | NeedsPostUpdate | NeedsRootCameraNodeEvents`

#### struct `UE::Cameras::FCameraEvaluationServiceInitializeParams`  
`struct FCameraEvaluationServiceInitializeParams`  
_L34-37_
- desc: Parameter structure for initializing an evaluation service.
- L36 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;`

#### struct `UE::Cameras::FCameraEvaluationServiceTeardownParams`  
`struct FCameraEvaluationServiceTeardownParams`  
_L40-43_
- desc: Parameter structure for tearing down an evaluation service.
- L42 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;`

#### struct `UE::Cameras::FCameraEvaluationServiceUpdateParams`  
`struct FCameraEvaluationServiceUpdateParams`  
_L46-51_
- desc: Parameter structure for updating an evaluation service.
- L48 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;`
- L49 _public member_ `float DeltaTime = 0.f;`
- L50 _public member_ `ECameraNodeEvaluationType EvaluationType = ECameraNodeEvaluationType::Standard;`

#### struct `UE::Cameras::FCameraEvaluationServiceUpdateResult`  
`struct FCameraEvaluationServiceUpdateResult`  
_L54-61_
- desc: Result structure for updating an evaluation service.
- L56 _public function_ `FCameraEvaluationServiceUpdateResult(FCameraNodeEvaluationResult& InEvaluationResult) : EvaluationResult(InEvaluationResult)`
- L60 _public member_ `FCameraNodeEvaluationResult& EvaluationResult;`

#### class `UE::Cameras::FCameraEvaluationService`  
`class FCameraEvaluationService : public TSharedFromThis<FCameraEvaluationService>`  
_L69-150_
- inherits: `TSharedFromThis<FCameraEvaluationService>`
- desc: An evaluation service running on a camera system. Evaluation services can run arbitrary logic before or after the root camera node update, and respond to events in the node tree such as when camera rigs are activated or deactivated.
- L75 _public prototype_ `FCameraEvaluationService();`
- L77 _public prototype_ `virtual ~FCameraEvaluationService();`
- L82 _public prototype_ `void Initialize(const FCameraEvaluationServiceInitializeParams& Params);` — Initializes the evaluation service.
- L84 _public prototype_ `void PreUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult);` — Runs at the start of the camera system update.
- L86 _public prototype_ `void PostCameraDirectorUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult);` — Runs after the camera director update.
- L88 _public prototype_ `void PostUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult);` — Runs at the end of the camera system update.
- L90 _public prototype_ `void Teardown(const FCameraEvaluationServiceTeardownParams& Params);` — Tears down the evaluation service.
- L93 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collect referenced UObjects.
- L97 _public prototype_ `void BuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder);` — Called to create debug blocks for this node evaluator.
- L104 _public function_ `ECameraEvaluationServiceFlags GetEvaluationServiceFlags() const`
- L105 _public prototype_ `bool HasAllEvaluationServiceFlags(ECameraEvaluationServiceFlags InFlags) const;`
- L110 _protected function_ `virtual void OnInitialize(const FCameraEvaluationServiceInitializeParams& Params)` — Initializes the evaluation service.
- L112 _protected function_ `virtual void OnPreUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult)` — Runs at the start of the camera system update.
- L114 _protected function_ `virtual void OnPostCameraDirectorUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult)` — Runs after the camera director update.
- L116 _protected function_ `virtual void OnPostUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult)` — Runs at the end of the camera system update.
- L118 _protected function_ `virtual void OnTeardown(const FCameraEvaluationServiceTeardownParams& Params)` — Tears down the evaluation service.
- L121 _protected function_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector)` — Collect referenced UObjects.
- L124 _protected function_ `virtual void OnRootCameraNodeEvent(const FRootCameraNodeCameraRigEvent& InEvent)` — Called when the root camera node experiences an event.
- L128 _protected function_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder)` — Called to create debug blocks for this node evaluator.
- L133 _private prototype_ `void RootCameraNodeEventHandler(const FRootCameraNodeCameraRigEvent& InEvent);`
- L141 _protected prototype_ `void SetEvaluationServiceFlags(ECameraEvaluationServiceFlags InFlags);` — Sets the flags on this service. Can be called from the constructor, or during OnInitialize().
- L146 _private member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The camera system that this service lives inside of.
- L149 _private member_ `ECameraEvaluationServiceFlags PrivateFlags = ECameraEvaluationServiceFlags::None;` — Evaluation service flags.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(ECameraEvaluationServiceFlags);` (scope `UE::Cameras`)
- L156 _macro_ `#define UE_DECLARE_CAMERA_EVALUATION_SERVICE(ApiDeclSpec, ClassName)\` — Utility macros for declaring and defining camera evaluation services.
- L159 _macro_ `#define UE_DECLARE_CAMERA_EVALUATION_SERVICE_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L162 _macro_ `#define UE_DEFINE_CAMERA_EVALUATION_SERVICE(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraEventHandler.h` (Public)


#### enum `UE::Cameras::ECameraArrayChangedEventType`  
`enum class ECameraArrayChangedEventType`  
_L14-19_
- desc: The type of change on an array property.
- L16 _public enumerator_ `Add`
- L17 _public enumerator_ `Remove`
- L18 _public enumerator_ `Change`

#### struct `UE::Cameras::TCameraPropertyChangedEvent`  
`template<typename T> struct TCameraPropertyChangedEvent`  
_L23-26_
- desc: Parameter structure for a value property change event.
- L25 _public member_ `T NewValue;`

#### struct `UE::Cameras::TCameraArrayChangedEvent`  
`template<typename T> struct TCameraArrayChangedEvent`  
_L30-50_
- desc: Parameter structure for an array property change event.
- L32 _public member_ `ECameraArrayChangedEventType EventType;`
- L34 _public function_ `TCameraArrayChangedEvent()`
- L35 _public function_ `TCameraArrayChangedEvent(EPropertyChangeType::Type InPropertyChangeType)`

#### struct `UE::Cameras::TCameraEventHandler`  
`template<typename HandlerInterface> struct TCameraEventHandler : public TLinkedList<HandlerInterface*>`  
_L59-72_
- inherits: `TLinkedList<HandlerInterface*>`
- desc: Wrapper struct, or handle, for a listener of data change events. The listener class should own one of these for each object they're listening to. The listener class can start listening by calling Register(HandlerWrapper, this) on the object to listen to.
- L61 _public function_ `TCameraEventHandler()`
- L64 _public function_ `TCameraEventHandler(HandlerInterface* InInterface) : TLinkedList<HandlerInterface*>(InInterface)`
- L68 _public function_ `~TCameraEventHandler()`

#### struct `UE::Cameras::TCameraEventHandlerContainer`  
`template<typename HandlerInterface> struct TCameraEventHandlerContainer`  
_L80-114_
- desc: A wrapper struct for a list of listeners waiting to be notified of data changes. A class that can be listened-to should own one of these, and expose it so that listeners can register themselves.
- L86 _public function_ `template<typename FuncType, typename... ArgTypes> void Notify(FuncType&& Func, ArgTypes&&... Args) const` — Invokes the given callback, with the given parameters, on any registered listener.
- L95 _public function_ `void Register(TCameraEventHandler<HandlerInterface>& InOutEventHandler, HandlerInterface* InInterface) const` — Registers a new listener by linking the given wrapper/handle to the list of listeners.
- L104 _private member_ `mutable TLinkedList<HandlerInterface*>* EventHandlers = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraIKAim.h` (Public)


#### struct `UE::Cameras::FCameraIKAimParams`  
`struct FCameraIKAimParams`  
_L19-42_
- desc: Parameter structure for aiming a camera rig at a target.
- L22 _public member_ `float DeltaTime = 0.f;` — The time interval to use when updating the camera rig.
- L24 _public member_ `bool bIsFirstFrame = false;` — Whether this is the first update of the camera rig.
- L26 _public member_ `bool bIsActiveCameraRig = false;` — Whether this camera rig is the active one in its layer (e.g. top of the blend stack).
- L29 _public member_ `FVector3d TargetLocation = FVector3d::ZeroVector;` — The desired target that the camera rig should be aiming at.
- L32 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The camera system inside which the evaluation takes place.
- L35 _public member_ `double MinDistance = -1.0;` — The distance below which aiming should not take place.
- L37 _public member_ `double AngleTolerance = -1.0;` — The angle between desired and actual target below which we consider aiming is complete.
- L39 _public member_ `double DistanceTolerance = -1.0;` — The distance between desired target and line of sight below which we consider aiming is complete.
- L41 _public member_ `uint8 MaxIterations = 0;` — The maximum number of iterations to run.

#### struct `UE::Cameras::FCameraIKAimIterationDebugInfo`  
`struct FCameraIKAimIterationDebugInfo`  
_L46-59_
- L48 _public member_ `FVector3d CameraPoseLocation;`
- L49 _public member_ `FRotator3d CameraPoseRotation;`
- L50 _public member_ `double ErrorAngle = 0;`
- L51 _public member_ `double ErrorDistance = 0;`
- L53 _public member_ `FVector3d PivotJointLocation = FVector3d::ZeroVector;`
- L54 _public member_ `FVector2d YawPitchCorrection = FVector2d::ZeroVector;`
- L56 _public member_ `bool bNeededSolver = false;`
- L57 _public member_ `bool bFoundSolver = false;`
- L58 _public member_ `bool bSolvingSuccess = false;`

#### struct `UE::Cameras::FCameraIKAimDebugInfo`  
`struct FCameraIKAimDebugInfo`  
_L61-69_
- L63 _public member_ `TArray<FCameraIKAimIterationDebugInfo, TInlineAllocator<4>> Iterations;`
- L65 _public member_ `FVector3d DesiredTarget = FVector3d::ZeroVector;`
- L66 _public member_ `bool bSucceeded = false;`
- L68 _public prototype_ `void DebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) const;`

#### class `UE::Cameras::FCameraIKAim`  
`class FCameraIKAim`  
_L79-126_
- desc: A class that can manipulate a camera rig in order to aim it at a desired target.
- L84 _public prototype_ `bool Run(const FCameraIKAimParams& Params, const FCameraRigEvaluationInfo& CameraRigInfo);` — Executes the aiming.
- L87 _public prototype_ `void GetLastRunDebugInfo(FCameraIKAimDebugInfo& OutDebugInfo) const;`
- L108 _private prototype_ `bool DoRun(const FCameraIKAimParams& Params, const FCameraRigEvaluationInfo& CameraRigInfo);`
- L109 _private prototype_ `void DoRunIteration(const FCameraIKAimParams& Params, const FCameraRigEvaluationInfo& CameraRigInfo, FAimIterationInfo& IterationInfo);`
- L111 _private prototype_ `void AimTwoBonesCameraRig(const FCameraIKAimParams& Params, const FCameraRigEvaluationInfo& CameraRigInfo, const FTransform3d& PivotTransform, FAimIterationInfo& IterationInfo);`
- L113 _private prototype_ `void RunRootCameraNode(const FCameraIKAimParams& Params, const FCameraRigEvaluationInfo& CameraRigInfo);`
- L114 _private prototype_ `bool CheckTolerance(const FCameraIKAimParams& Params, const FCameraRigEvaluationInfo& CameraRigInfo, FAimIterationInfo& IterationInfo);`
- L118 _private member_ `FCameraNodeEvaluationResult ScratchResult;`
- L120 _private member_ `FCameraNodeEvaluatorHierarchy CameraSystemHierarchy;`
- L121 _private member_ `TArray<uint8> EvaluatorSnapshot;`
- L124 _private member_ `FCameraIKAimDebugInfo LastRunDebugInfo;`

#### enum `UE::Cameras::FCameraIKAim::EAimResult`  
`enum class EAimResult`  
_L92-98_
- L94 _public enumerator_ `Failed`
- L95 _public enumerator_ `Aborted`
- L96 _public enumerator_ `Corrected`
- L97 _public enumerator_ `Completed`

#### struct `UE::Cameras::FCameraIKAim::FAimIterationInfo`  
`struct FAimIterationInfo`  
_L100-106_
- L102 _public member_ `uint8 IterationIndex = 0;`
- L103 _public member_ `double ErrorAngle = 0.0;`
- L104 _public member_ `double ErrorDistance = 0.0;`
- L105 _public member_ `EAimResult Result = EAimResult::Failed;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)
- L71 _prototype_ `FArchive& operator<< (FArchive& Ar, FCameraIKAimIterationDebugInfo& IterationDebugInfo);` (scope `UE::Cameras`)
- L72 _prototype_ `FArchive& operator<< (FArchive& Ar, FCameraIKAimDebugInfo& DebugInfo);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraNode.h` (Public)


#### enum `ECameraNodeFlags`  
`enum class ECameraNodeFlags`  
_L28-32_
- desc: Flags describing the needs of a camera node.
- L30 _public enumerator_ `None = 0`
- L31 _public enumerator_ `CustomGetChildren = 1 << 0`

#### class `UCameraNode`  
`class UCameraNode : public UObject , public IObjectTreeGraphObject`  
_L39-133_
- reflection: `UCLASS(MinimalAPI, Abstract, DefaultToInstanced, EditInlineNew, meta=(CameraNodeCategories="Miscellaneous"))`
- inherits: `UObject,IObjectTreeGraphObject`
- desc: The base class for a camera node.
- L47 _public typedef_ `using FCameraBuildLog = UE::Cameras::FCameraBuildLog;`
- L48 _public typedef_ `using FCameraBuildContext = UE::Cameras::FCameraBuildContext;`
- L49 _public typedef_ `using FCameraObjectBuildContext = UE::Cameras::FCameraObjectBuildContext;`
- L50 _public typedef_ `using FCameraNodeEvaluatorBuilder = UE::Cameras::FCameraNodeEvaluatorBuilder;`
- L53 _public prototype_ `FCameraNodeChildrenView GetChildren();` — Get the list of children under this node.
- L56 _public prototype_ `void PreBuild(FCameraBuildContext& BuildContext);` — Optional build step executed at the beginning of the build process.
- L59 _public prototype_ `void Build(FCameraObjectBuildContext& BuildContext);` — Gets optional info about this node's required allocations at runtime.
- L62 _public prototype_ `FCameraNodeEvaluatorPtr BuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const;` — Builds the evaluator for this node.
- L67 _protected function_ `void AddNodeFlags(ECameraNodeFlags InFlags)` — Adds the given flags to this node.
- L70 _protected function_ `void SetNodeFlags(ECameraNodeFlags InFlags)` — Sets the flags for this node.
- L75 _protected function_ `virtual FCameraNodeChildrenView OnGetChildren()` — Get the list of children under this node.
- L78 _protected function_ `virtual void OnPreBuild(FCameraBuildContext& BuildContext)` — Optional build step executed at the beginning of the build process.
- L81 _protected function_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext)` — Gets optional info about this node's required allocations at runtime.
- L84 _protected function_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const` — Builds the evaluator for this node.
- L89 _protected prototype_ `virtual void PostLoad() override;` — UObject interface.
- L93 _protected prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;`
- L94 _protected prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`
- L95 _protected function_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override`
- L96 _protected prototype_ `virtual const FString& GetGraphNodeCommentText(FName InGraphName) const override;`
- L97 _protected prototype_ `virtual void OnUpdateGraphNodeCommentText(FName InGraphName, const FString& NewComment) override;`
- L104 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, Category=Common)` — Specifies whether this node is enabled.
- L112 _public member_ `FIntVector2 GraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the camera node in the node graph editor.
- L116 _public member_ `FString GraphNodeComment;` — `UPROPERTY()` — User-written comment in the node graph editor.
- L123 _private member_ `int32 GraphNodePosX_DEPRECATED = 0;` — `UPROPERTY()`
- L125 _private member_ `int32 GraphNodePosY_DEPRECATED = 0;` — `UPROPERTY()`
- L132 _private member_ `ECameraNodeFlags PrivateFlags = ECameraNodeFlags::None;` — Flags on this camera node.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)
- L23 _typedef_ `using FCameraNodeChildrenView = UE::Cameras::TObjectChildrenView<TObjectPtr<UCameraNode>>;` — View on a camera node's children.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraNodeEvaluator.h` (Public)


#### enum `UE::Cameras::ECameraNodeEvaluatorFlags`  
`enum class ECameraNodeEvaluatorFlags`  
_L39-47_
- desc: Flags describing the needs of a camera node evaluator.
- L41 _public enumerator_ `None = 0`
- L42 _public enumerator_ `NeedsParameterUpdate = 1 << 0`
- L43 _public enumerator_ `NeedsSerialize = 1 << 1`
- L44 _public enumerator_ `SupportsOperations = 1 << 2`
- L46 _public enumerator_ `Default = NeedsParameterUpdate | NeedsSerialize | SupportsOperations`

#### struct `UE::Cameras::FCameraNodeEvaluatorBuildParams`  
`struct FCameraNodeEvaluatorBuildParams`  
_L56-73_
- desc: Structure for building the tree of camera node evaluators.
- L58 _public function_ `FCameraNodeEvaluatorBuildParams(FCameraNodeEvaluatorBuilder& InBuilder) : Builder(InBuilder)`
- L63 _public prototype_ `FCameraNodeEvaluator* BuildEvaluator(const UCameraNode* InNode) const;` — Builds an evaluator for the given camera node.
- L67 _public prototype_ `template<typename EvaluatorType> EvaluatorType* BuildEvaluatorAs(const UCameraNode* InNode) const;` — Builds an evaluator for the given camera node, and down-cast it to the given type.
- L72 _private member_ `FCameraNodeEvaluatorBuilder& Builder;` — Builder object for building children evaluators.
- L453 _function_ `template<typename EvaluatorType> EvaluatorType* FCameraNodeEvaluatorBuildParams::BuildEvaluatorAs(const UCameraNode* InNode) const`

#### struct `UE::Cameras::FCameraNodeEvaluatorInitializeParams`  
`struct FCameraNodeEvaluatorInitializeParams`  
_L78-105_
- desc: Structure for initializing a camera node evaluator.
- L81 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The evaluation running this evaluation.
- L83 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context (if any) responsible for this branch of the evaluation.
- L89 _public member_ `FCameraRigEvaluationInfo LastActiveCameraRigInfo;` — Information about the last active camera rig if the node tree being initialized is being pushed on top of a non-empty blend stack.
- L92 _public member_ `ECameraRigLayer Layer = ECameraRigLayer::Main;` — The layer on which the node evaluator is being initialized.
- L96 _public prototype_ `FCameraNodeEvaluatorInitializeParams() = default;`
- L97 _public prototype_ `FCameraNodeEvaluatorInitializeParams(FCameraNodeEvaluatorHierarchy* InHierarchy);`
- L102 _private member_ `FCameraNodeEvaluatorHierarchy* Hierarchy = nullptr;` — An optional hierarchy to populate while initialize the evaluator tree.

#### struct `UE::Cameras::FCameraNodeEvaluatorTeardownParams`  
`struct FCameraNodeEvaluatorTeardownParams`  
_L110-119_
- desc: Structure for tearing down a camera node evaluator.
- L113 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The evaluation running this evaluation.
- L115 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context (if any) responsible for this branch of the evaluation.
- L118 _public member_ `ECameraRigLayer Layer = ECameraRigLayer::Main;` — The layer on which the node evaluator was running.

#### struct `UE::Cameras::FCameraBlendedParameterUpdateParams`  
`struct FCameraBlendedParameterUpdateParams`  
_L124-135_
- desc: Parameter structure for updating the pre-blended parameters of a camera node.
- L126 _public function_ `FCameraBlendedParameterUpdateParams(const FCameraNodeEvaluationParams& InEvaluationParams, const FCameraPose& InLastCameraPose) : EvaluationParams(InEvaluationParams) , LastCameraPose(InLastCameraPose)`
- L132 _public member_ `const FCameraNodeEvaluationParams& EvaluationParams;` — Information about the evaluation pass that will happen afterwards.
- L134 _public member_ `const FCameraPose& LastCameraPose;` — Last frame's camera pose.

#### struct `UE::Cameras::FCameraBlendedParameterUpdateResult`  
`struct FCameraBlendedParameterUpdateResult`  
_L140-148_
- desc: Result of updating the pre-blended parameters of a camera node.
- L142 _public function_ `FCameraBlendedParameterUpdateResult(FCameraVariableTable& InVariableTable) : VariableTable(InVariableTable)`
- L147 _public member_ `FCameraVariableTable& VariableTable;` — Variable table in which parameters should be stored or obtained.

#### enum `UE::Cameras::ECameraNodeEvaluationType`  
`enum class ECameraNodeEvaluationType`  
_L151-164_
- desc: The type of evaluation being run.
- L154 _public enumerator_ `Standard` — Normal evaluation.
- L156 _public enumerator_ `ViewRotationPreview` — View rotation evaluation.
- L158 _public enumerator_ `IK` — Evaluation for IK aiming.
- L162 _public enumerator_ `EditorPreview #endif` — Evaluation for editor preview.

#### struct `UE::Cameras::FCameraNodeEvaluationParams`  
`struct FCameraNodeEvaluationParams`  
_L169-189_
- desc: Parameter structure for running a camera node evaluator.
- L172 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The evaluator running this evaluation.
- L174 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context (if any) responsible for this branch of the evaluation.
- L176 _public member_ `float DeltaTime = 0.f;` — The time interval for the evaluation.
- L178 _public member_ `ECameraNodeEvaluationType EvaluationType = ECameraNodeEvaluationType::Standard;` — The type of evaluation being run.
- L180 _public member_ `bool bIsFirstFrame = false;` — Whether this is the first evaluation of this camera node hierarchy.
- L182 _public member_ `bool bIsActiveCameraRig = false;` — Whether this camera node is running inside the active camera rig in this layer.
- L184 _public function_ `bool IsStatelessEvaluation() const`

#### struct `UE::Cameras::FCameraNodeEvaluationResult`  
`struct FCameraNodeEvaluationResult`  
_L194-258_
- desc: Input/output result structure for running a camera node evaluator.
- L197 _public member_ `FCameraPose CameraPose;` — The camera pose.
- L200 _public member_ `FCameraVariableTable VariableTable;` — The variable table.
- L203 _public member_ `FCameraContextDataTable ContextDataTable;` — The context data table.
- L206 _public member_ `FCameraRigJoints CameraRigJoints;` — The list of joints in the current camera rig.
- L209 _public member_ `FPostProcessSettingsCollection PostProcessSettings;` — Post-process settings for the camera.
- L212 _public member_ `bool bIsCameraCut = false;` — Whether the current frame is a camera cut.
- L215 _public member_ `bool bIsValid = false;` — Whether this result is valid.
- L220 _public prototype_ `void Reset();` — Reset this result to its default (non-valid) state.
- L223 _public prototype_ `void ResetFrameFlags();` — Reset all written-this-frame flags on the camera pose and tables.
- L226 _public prototype_ `void OverrideAll(const FCameraNodeEvaluationResult& OtherResult, bool bIncludePrivateValues = false);` — Override this result with the given other result.
- L229 _public prototype_ `void LerpAll(const FCameraNodeEvaluationResult& ToResult, float BlendFactor, bool bIncludePrivateValues = false);` — Interpolate this result towards the other given result.
- L234 _public prototype_ `void GetViewInfo(FMinimalViewInfo& OutViewInfo) const;` — Export this result into the given view info.
- L237 _public prototype_ `void Serialize(FArchive& Ar);` — Serializes this result to the given archive.
- L240 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collects objects from the context data table.
- L248 _public prototype_ `void AddCameraPoseTrailPointIfNeeded();`
- L249 _public prototype_ `void AddCameraPoseTrailPointIfNeeded(const FVector3d& Point);`
- L250 _public prototype_ `void AppendCameraPoseLocationTrail(const FCameraNodeEvaluationResult& InResult);`
- L251 _public prototype_ `TConstArrayView<FVector3d> GetCameraPoseLocationTrail() const;`
- L255 _private member_ `TArray<FVector3d> CameraPoseLocationTrail;`

#### struct `UE::Cameras::FCameraOperationParams`  
`struct FCameraOperationParams`  
_L263-269_
- desc: Parameter structure for executing camera operations.
- L266 _public member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The evaluator running this operation.
- L268 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context (if any) responsible for this branch of the evaluation.

#### struct `UE::Cameras::FCameraNodeEvaluatorSerializeParams`  
`struct FCameraNodeEvaluatorSerializeParams`  
_L274-276_
- desc: Parameter structure for serializing the state of a camera node evaluator.

#### struct `UE::Cameras::FCameraEditorPreviewDrawParams`  
`struct FCameraEditorPreviewDrawParams`  
_L283-285_
- desc: Parameter structure for drawing editor preview.

#### class `UE::Cameras::FCameraNodeEvaluator`  
`class FCameraNodeEvaluator`  
_L292-435_
- desc: Base class for objects responsible for running a camera node.
- L298 _public prototype_ `FCameraNodeEvaluator() = default;`
- L299 _public prototype_ `virtual ~FCameraNodeEvaluator() = default;`
- L302 _public prototype_ `void Build(const FCameraNodeEvaluatorBuildParams& Params);` — Called to build any children evaluators.
- L305 _public prototype_ `void Initialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult);` — Initialize this evaluator and all its descendants.
- L308 _public prototype_ `void Teardown(const FCameraNodeEvaluatorTeardownParams& Params);` — Tear down this evaluator and all its descendants.
- L311 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collect referenced UObjects for this node and all its descendants.
- L314 _public prototype_ `FCameraNodeEvaluatorChildrenView GetChildren();` — Get the list of children under this evaluator.
- L317 _public prototype_ `void UpdateParameters(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult);` — Called to update and store the blended parameters for this node.
- L320 _public prototype_ `void Run(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — Run this evaluator.
- L323 _public prototype_ `void ExecuteOperation(const FCameraOperationParams& Params, FCameraOperation& Operation);` — Execute an IK operation.
- L326 _public prototype_ `void Serialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar);` — Serializes the state of this evaluator.
- L329 _public function_ `ECameraNodeEvaluatorFlags GetNodeEvaluatorFlags() const` — Gets the flags for this evaluator.
- L332 _public function_ `const UCameraNode* GetCameraNode() const` — Get the camera node.
- L336 _public function_ `template<typename CameraNodeType> const CameraNodeType* GetCameraNodeAs() const` — Get the camera node.
- L342 _public prototype_ `void DrawEditorPreview(const FCameraEditorPreviewDrawParams& Params, FCameraDebugRenderer& Renderer);`
- L347 _public prototype_ `void BuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder);` — Called to create debug blocks for this node evaluator.
- L353 _public prototype_ `void SetPrivateCameraNode(TObjectPtr<const UCameraNode> InCameraNode);` — Internal API.
- L361 _protected prototype_ `void SetNodeEvaluatorFlags(ECameraNodeEvaluatorFlags InFlags);` — Sets the flags for this evaluator. Can be called from the constructor, or during OnInitialize().
- L368 _protected prototype_ `void AddNodeEvaluatorFlags(ECameraNodeEvaluatorFlags InFlags);` — Adds flags for this evaluator. Evaluators default to having all flags enabled, so this is mostly only for re-adding a flag that was removed by a base class.
- L373 _protected function_ `virtual void OnBuild(const FCameraNodeEvaluatorBuildParams& Params)` — Called to build any children evaluators.
- L376 _protected function_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult)` — Initialize this evaluator. Children and descendants will be automatically initialized too.
- L379 _protected function_ `virtual void OnTeardown(const FCameraNodeEvaluatorTeardownParams& Params)` — Tear down this evaluator and all its descendants.
- L382 _protected function_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector)` — Collect referenced UObjects for this node.
- L385 _protected function_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren()` — Get the list of children under this evaluator.
- L391 _protected function_ `virtual void OnUpdateParameters(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult)` — Called to update and store the blended parameters for this node. Requires setting the ECameraNodeEvaluatorFlags::NeedsParameterUpdate flag.
- L396 _protected function_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult)` — Run this evaluator. This node evaluator is responsible for calling Run() on its children as appropriate.
- L402 _protected function_ `virtual void OnExecuteOperation(const FCameraOperationParams& Params, FCameraOperation& Operation)` — Execute an IK operation. Requires setting the ECameraNodeEvaluatorFlags::SupportsOperations flag.
- L408 _protected function_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar)` — Serializes the state of this evaluator. Requires setting the ECameraNodeEvaluatorFlags::NeedsSerialize flag, which is set by default.
- L411 _protected function_ `virtual void OnDrawEditorPreview(const FCameraEditorPreviewDrawParams& Params, FCameraDebugRenderer& Renderer)`
- L416 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder);` — Called to create debug blocks for this node evaluator.
- L424 _protected member_ `bool bAutoCameraPoseMovementTrail = true;` — Whether to automatically add points to the debug trail after this evaluation has run.
- L431 _private member_ `TObjectPtr<const UCameraNode> PrivateCameraNode;` — The camera node to run.
- L434 _private member_ `ECameraNodeEvaluatorFlags PrivateFlags = ECameraNodeEvaluatorFlags::Default;` — The flags for this evaluator.

#### class `UE::Cameras::TCameraNodeEvaluator`  
`template<typename CameraNodeType> class TCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L439-450_
- inherits: `FCameraNodeEvaluator`
- desc: Utility base class for camera node evaluators of a specific camera node type.
- L444 _public function_ `const CameraNodeType* GetCameraNode() const` — Gets the camera node.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Cameras` (scope `UE`)
- L51 _typedef_ `using FCameraNodeEvaluatorChildrenView = TObjectChildrenView<FCameraNodeEvaluator*>;` (scope `UE::Cameras`) — View on a camera node evaluator's children.
- L466 _macro_ `#define UE_DECLARE_CAMERA_NODE_EVALUATOR(ApiDeclSpec, ClassName)\` — Utility macros for declaring and defining camera node evaluators.
- L469 _macro_ `#define UE_DECLARE_CAMERA_NODE_EVALUATOR_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L472 _macro_ `#define UE_DEFINE_CAMERA_NODE_EVALUATOR(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraNodeEvaluatorBuilder.h` (Public)


#### struct `UE::Cameras::FCameraNodeEvaluatorBuilder`  
`struct FCameraNodeEvaluatorBuilder`  
_L11-24_
- desc: Structure for building camera node evaluators.
- L13 _public function_ `FCameraNodeEvaluatorBuilder(FCameraNodeEvaluatorStorage& InStorage) : Storage(InStorage)`
- L19 _public prototype_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* BuildEvaluator(ArgTypes&&... InArgs);` — Builds a camera node evaluator of a given type.
- L23 _private member_ `FCameraNodeEvaluatorStorage& Storage;`
- L27 _function_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* FCameraNodeEvaluatorBuilder::BuildEvaluator(ArgTypes&&... InArgs)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraNodeEvaluatorFwd.h` (Public)


#### struct `FCameraNodeEvaluatorAllocationInfo`  
`struct FCameraNodeEvaluatorAllocationInfo`  
_L23-42_
- reflection: `USTRUCT()`
- desc: Allocation information for an entire tree of node evaluators.
- L29 _public member_ `int16 TotalSizeof = 0;` — `UPROPERTY()` — Total required size for the node evaluators.
- L33 _public member_ `int16 MaxAlignof = 0;` — `UPROPERTY()` — Maximum required alignment for the node evaluators.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraNodeEvaluatorAllocationInfo> : public TStructOpsTypeTraitsBase2<FCameraNodeEvaluatorAllocationInfo>`  
_L45-52_
- inherits: `TStructOpsTypeTraitsBase2<FCameraNodeEvaluatorAllocationInfo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L48-51_

#### struct `TCameraNodeEvaluatorAllocationInfo`  
`template<typename EvaluatorType> struct TCameraNodeEvaluatorAllocationInfo : FCameraNodeEvaluatorAllocationInfo`  
_L56-63_
- inherits: `FCameraNodeEvaluatorAllocationInfo`
- desc: Allocation information for a node evaluator, auto-setup for a given type.
- L58 _public function_ `TCameraNodeEvaluatorAllocationInfo()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)
- L19 _typedef_ `using FCameraNodeEvaluatorPtr = UE::Cameras::FCameraNodeEvaluator*;` — Typedef to avoid having to deal with namespaces in UCameraNode subclasses.
- L37 _function_ `friend bool operator==(const FCameraNodeEvaluatorAllocationInfo& A, const FCameraNodeEvaluatorAllocationInfo& B)`
- L49 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonbeab36a70103`)
- L50 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonbeab36a70103`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraNodeEvaluatorHierarchy.h` (Public)


#### class `UE::Cameras::FCameraNodeEvaluatorHierarchy`  
`class FCameraNodeEvaluatorHierarchy`  
_L16-121_
- desc: A utility class that stores a flattened hierarchy of camera node evaluators.
- L21 _public prototype_ `FCameraNodeEvaluatorHierarchy();` — Builds an empty hierarchy.
- L23 _public prototype_ `FCameraNodeEvaluatorHierarchy(FCameraNodeEvaluator* InRootEvaluator);` — Builds a hierarchy starting from the given root evaluator.
- L26 _public prototype_ `TArrayView<FCameraNodeEvaluator* const> GetFlattenedHierarchy() const;` — Get the list of evaluators in depth-first order.
- L29 _public prototype_ `void GetFlattenedHierarchy(ECameraNodeEvaluatorFlags FilterFlags, TArray<FCameraNodeEvaluator*> OutEvaluators) const;` — Get the list of evaluators matching the given evaluator flags, in depth-first order.
- L34 _public prototype_ `void Build(FCameraNodeEvaluator* InRootEvaluator);` — Builds a hierarchy starting from the given root evaluator.
- L36 _public prototype_ `void Append(FCameraNodeEvaluator* InRootEvaluator);` — Append another hierarchy to the existing hierarchy, starting from the given root evaluator.
- L38 _public prototype_ `void AppendTagged(const FName TaggedRangeName, FCameraNodeEvaluator* InRootEvaluator);` — Append and tag another hierarchy to the existing hierarchy, starting from the given root evaluator.
- L40 _public prototype_ `void AddEvaluator(FCameraNodeEvaluator* Evaluator);` — Add an evaluator to the existing hierarchy.
- L42 _public prototype_ `void Reset();` — Resets this object to an emtpy hierarchy.
- L48 _public function_ `template<typename PredicateClass> void ForEachEvaluator(PredicateClass&& Predicate) const` — Executes the given predicate on each evaluator in depth-first order.
- L58 _public function_ `template<typename PredicateClass> void ForEachEvaluator(const FName TaggedRangeName, PredicateClass&& Predicate) const` — Executes the given predicate on each evaluator in the specified range in depth-first order.
- L73 _public function_ `template<typename PredicateClass> void ForEachEvaluator(ECameraNodeEvaluatorFlags FilterFlags, PredicateClass&& Predicate) const` — Executes the given predicate on each evaluator matching the specified evaluator flags in depth-first order.
- L89 _public function_ `template<typename PredicateClass> void ForEachEvaluator(const FName TaggedRangeName, ECameraNodeEvaluatorFlags FilterFlags, PredicateClass&& Predicate) const` — Executes the given predicate on each evaluator in the specified range matching the specified evaluator flags in depth-first order.
- L105 _public prototype_ `void CallUpdateParameters(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult);` — Helper method to call UpdateParameters on the appropriate nodes in the hierarchy.
- L107 _public prototype_ `void CallExecuteOperation(const FCameraOperationParams& Params, FCameraOperation& Operation);` — Helper method to call ExecuteOperation on the appropriate nodes in the hierarchy.
- L109 _public prototype_ `void CallSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar);` — Helper method to call Serialize on the appropriate nodes in the hierarchy.
- L113 _private member_ `TArray<FCameraNodeEvaluator*> FlattenedHierarchy;`
- L120 _private member_ `TMap<FName, FTaggedRange> TaggedRanges;`

#### struct `UE::Cameras::FCameraNodeEvaluatorHierarchy::FTaggedRange`  
`struct FTaggedRange`  
_L115-119_
- L117 _public member_ `int32 StartIndex;`
- L118 _public member_ `int32 EndIndex;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraNodeEvaluatorStorage.h` (Public)


#### struct `UE::Cameras::FCameraNodeEvaluatorTreeBuildParams`  
`struct FCameraNodeEvaluatorTreeBuildParams`  
_L23-29_
- desc: Structure for building an entire tree of node evaluators.
- L26 _public member_ `TObjectPtr<const UCameraNode> RootCameraNode;` — The root node of the tree.
- L28 _public member_ `const FCameraNodeEvaluatorAllocationInfo* AllocationInfo = nullptr;` — An optional allocation information to optimize storage.

#### class `UE::Cameras::FCameraNodeEvaluatorStorage`  
`class FCameraNodeEvaluatorStorage : public TCameraObjectStorage<FCameraNodeEvaluator>`  
_L34-55_
- inherits: `TCameraObjectStorage<FCameraNodeEvaluator>`
- desc: A class responsible for storing a tree of camera node evaluators.
- L38 _public typedef_ `using Super = TCameraObjectStorage<FCameraNodeEvaluator>;`
- L41 _public prototype_ `FCameraNodeEvaluatorPtr BuildEvaluatorTree(const FCameraNodeEvaluatorTreeBuildParams& Params);` — Build the tree of evaluators for the given tree of camera nodes.
- L44 _public prototype_ `void DestroyEvaluatorTree(bool bFreeAllocations = false);` — Destroy any allocated evaluators.
- L47 _public prototype_ `void DestroyEvaluatorTree(FCameraNodeEvaluator* InRootEvaluator, bool bResetMemory = true);` — Destroy a sub-tree of allocated evaluators.
- L50 _public prototype_ `void GetAllocationInfo(FCameraNodeEvaluatorAllocationInfo& OutAllocationInfo);` — Computes the currently allocated totals.
- L54 _public prototype_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* BuildEvaluator(ArgTypes&&... InArgs);` — Build a new evaluator inside this storage.
- L58 _function_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* FCameraNodeEvaluatorStorage::BuildEvaluator(ArgTypes&&... InArgs)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraNodeHierarchy.h` (Public)


#### class `UE::Cameras::FCameraNodeHierarchy`  
`class FCameraNodeHierarchy`  
_L19-69_
- desc: A utility class that stores a flattened hierarchy of camera nodes. Unconnected camera nodes aren't included, of course.
- L24 _public prototype_ `FCameraNodeHierarchy();` — Build an empty hierarchy.
- L26 _public prototype_ `FCameraNodeHierarchy(UBaseCameraObject* InCameraObject);` — Build a hierarchy starting from the given camera object's root node.
- L28 _public prototype_ `FCameraNodeHierarchy(UCameraNode* InRootCameraNode);` — Build a hierarchy starting from the given root node.
- L31 _public prototype_ `TArrayView<UCameraNode* const> GetFlattenedHierarchy() const;` — Get the list of camera nodes in depth-first order.
- L34 _public prototype_ `int32 Num() const;` — Returns the number of camera nodes in this hierarchy.
- L39 _public prototype_ `void Build(UBaseCameraObject* InCameraObject);` — Build a hierarchy starting from the given camera object's root node.
- L41 _public prototype_ `void Build(UCameraNode* InRootCameraNode);` — Build a hierarchy starting from the given root node.
- L43 _public prototype_ `void Reset();` — Resets this object to an empty hierarchy.
- L49 _public function_ `template<typename PredicateClass> void ForEach(PredicateClass&& Predicate)` — Executes the given predicate on each camera node in depth-first order.
- L62 _public prototype_ `bool FindMissingConnectableObjects(TArrayView<UObject* const> ConnectableObjects, TSet<UObject*>& OutMissingObjects);`
- L63 _public prototype_ `bool FindMissingConnectableObjects(const TSet<UObject*> ConnectableObjectsSet, TSet<UObject*>& OutMissingObjects);`
- L68 _private member_ `TArray<UCameraNode*> FlattenedHierarchy;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraObjectInterface.h` (Public)


#### class `UCameraObjectInterfaceParameterBase`  
`class UCameraObjectInterfaceParameterBase : public UObject`  
_L24-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for interface parameters on a camera rig asset.
- L33 _public member_ `FString InterfaceParameterName;` — `UPROPERTY(EditAnywhere, Category="Camera")` — The exposed name for this parameter.
- L37 _public member_ `bool bIsVisible = true;` — `UPROPERTY(EditAnywhere, Category="Visibility")` — Whether to show this parameter on prefab nodes, references, components, etc.
- L42 _public function_ `const FGuid& GetGuid() const` — Gets this parameter's unique ID.
- L45 _public function_ `virtual void GetParameterDefinition(FCameraObjectInterfaceParameterDefinition& OutParameterDefinition) const` — Gets the parameter definition.
- L51 _protected member_ `FGuid Guid;` — `UPROPERTY()` — The Guid of this parameter.
- L56 _protected prototype_ `virtual void PostLoad() override;` — UObject interface.
- L57 _protected prototype_ `virtual void PostInitProperties() override;`
- L58 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L65 _public member_ `TObjectPtr<UCameraNode> Target_DEPRECATED;` — `UPROPERTY(meta=(ObjectTreeGraphHidden=true))`
- L68 _public member_ `FName TargetPropertyName_DEPRECATED;` — `UPROPERTY()`
- L73 _public member_ `FIntVector2 GraphNodePos_DEPRECATED = FIntVector2::ZeroValue;` — `UPROPERTY()`
- L76 _public member_ `bool bHasGraphNode_DEPRECATED = false;` — `UPROPERTY()`

#### class `UCameraObjectInterfaceBlendableParameter`  
`class UCameraObjectInterfaceBlendableParameter : public UCameraObjectInterfaceParameterBase`  
_L86-133_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraObjectInterfaceParameterBase`
- desc: An exposed camera rig parameter that drives a specific parameter on one of its camera nodes.
- L94 _public member_ `ECameraVariableType VariableType = ECameraVariableType::Boolean;` — `UPROPERTY()` — The type of this parameter.
- L98 _public member_ `TObjectPtr<const UScriptStruct> BlendableStructType;` — `UPROPERTY()` — The struct type of this parameter if it is a blendable struct.
- L108 _public member_ `bool bIsPreBlended = false;` — `UPROPERTY(EditAnywhere, Category="Blending")` — Whether this parameter's value should be pre-blended. Pre-blending means that if two blending camera rigs share this parameter, each of their values will be blended in a first evaluation pass, and then both camera rigs will evaluate with the same blended value.
- L114 _public member_ `FCameraVariableID PrivateVariableID;` — `UPROPERTY()` — The ID to use to access the underlying variable value in the variable table.
- L120 _public member_ `TObjectPtr<UCameraVariableAsset> PrivateVariable_DEPRECATED;` — `UPROPERTY()`
- L125 _public prototype_ `FCameraVariableDefinition GetVariableDefinition() const;` — Gets the camera variable definition for this parameter.
- L128 _public prototype_ `FString GetVariableName() const;`
- L132 _public prototype_ `virtual void GetParameterDefinition(FCameraObjectInterfaceParameterDefinition& OutParameterDefinition) const override;` — UCameraObjectInterfaceParameterBase interface.

#### class `UCameraObjectInterfaceDataParameter`  
`class UCameraObjectInterfaceDataParameter : public UCameraObjectInterfaceParameterBase`  
_L136-171_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraObjectInterfaceParameterBase`
- L144 _public member_ `ECameraContextDataType DataType = ECameraContextDataType::Name;` — `UPROPERTY()` — The type of this parameter.
- L148 _public member_ `ECameraContextDataContainerType DataContainerType = ECameraContextDataContainerType::None;` — `UPROPERTY()` — The type of container for this parameter.
- L152 _public member_ `TObjectPtr<const UObject> DataTypeObject;` — `UPROPERTY()` — An additional type object for this parameter.
- L158 _public member_ `FCameraContextDataID PrivateDataID;` — `UPROPERTY()` — The ID to use to access the underlying data in the context data table.
- L163 _public prototype_ `FCameraContextDataDefinition GetDataDefinition() const;` — Gets the camera context data definition for this parameter.
- L166 _public prototype_ `FString GetDataName() const;`
- L170 _public prototype_ `virtual void GetParameterDefinition(FCameraObjectInterfaceParameterDefinition& OutParameterDefinition) const override;` — UCameraObjectInterfaceParameterBase interface.

#### struct `FCameraObjectInterface`  
`struct FCameraObjectInterface`  
_L177-216_
- reflection: `USTRUCT()`
- desc: Structure defining the public data interface of a camera object.
- L185 _public member_ `TArray<TObjectPtr<UCameraObjectInterfaceBlendableParameter>> BlendableParameters;` — `UPROPERTY(Instanced)` — The list of exposed blendable parameters on the camera rig.
- L189 _public member_ `TArray<TObjectPtr<UCameraObjectInterfaceDataParameter>> DataParameters;` — `UPROPERTY(Instanced)` — The list of exposed data parameters on the camera rig.
- L194 _public prototype_ `UCameraObjectInterfaceBlendableParameter* FindBlendableParameterByName(const FString& ParameterName) const;` — Finds an exposed parameter by name.
- L195 _public prototype_ `UCameraObjectInterfaceDataParameter* FindDataParameterByName(const FString& ParameterName) const;`
- L198 _public prototype_ `UCameraObjectInterfaceBlendableParameter* FindBlendableParameterByGuid(const FGuid& ParameterGuid) const;` — Finds an exposed parameter by Guid.
- L199 _public prototype_ `UCameraObjectInterfaceDataParameter* FindDataParameterByGuid(const FGuid& ParameterGuid) const;`
- L202 _public prototype_ `bool HasBlendableParameter(const FString& ParameterName) const;` — Returns whether an exposed parameter with the given name exists.
- L208 _public function_ `FString GetDisplayName() const` — `UE_DEPRECATED(5.6, "Camera rigs are now all standalone assets and don't need a separate display name.")` — Deprecated methods.
- L215 _private member_ `FString DisplayName_DEPRECATED;` — `UPROPERTY()`

#### class `UCameraObjectInterfaceParameterGetter`  
`class UCameraObjectInterfaceParameterGetter : public UObject , public IObjectTreeGraphObject`  
_L222-251_
- reflection: `UCLASS(MinimalAPI, meta=(ObjectTreeGraphSelfPinDirection="Output"))`
- inherits: `UObject,IObjectTreeGraphObject`
- desc: Getter object for adding a camera parameter to a camera node graph.
- L232 _public member_ `FGuid ParameterGuid;` — `UPROPERTY()` — The Guid of the parameter to get.
- L236 _public member_ `FIntVector2 GraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — The location of this node in the graph.
- L240 _public prototype_ `UCameraObjectInterfaceParameterBase* GetInterfaceParameter() const;`
- L242 _public prototype_ `FString GetInterfaceParameterName() const;`
- L248 _protected prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;`
- L249 _protected prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraObjectInterfaceParameterDefinition.h` (Public)


#### enum `ECameraObjectInterfaceParameterType`  
`enum class ECameraObjectInterfaceParameterType : uint8`  
_L14-18_
- reflection: `UENUM()`
- desc: The type of a camera parameter.
- L16 _public enumerator_ `Blendable`
- L17 _public enumerator_ `Data`

#### struct `FCameraObjectInterfaceParameterDefinition`  
`struct FCameraObjectInterfaceParameterDefinition`  
_L24-87_
- reflection: `USTRUCT()`
- desc: Information about a parameter exposed on a camera asset.
- L30 _public member_ `FName ParameterName;` — `UPROPERTY()` — The name of the parameter.
- L38 _public member_ `FGuid ParameterGuid;` — `UPROPERTY()` — The GUID of the parameter. This matches the GUID on the corresponding UCameraObjectInterfaceBlendableParameter or UCameraObjectInterfaceDataParameter object.
- L42 _public member_ `ECameraObjectInterfaceParameterType ParameterType = ECameraObjectInterfaceParameterType::Blendable;` — `UPROPERTY()` — The type of this parameter.
- L46 _public member_ `bool bIsVisible = true;` — `UPROPERTY()` — Whether to show this parameter on prefab nodes, references, components, etc.
- L54 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()` — The ID of the variable that drives this blendable parameter.
- L58 _public member_ `ECameraVariableType VariableType = ECameraVariableType::Boolean;` — `UPROPERTY()` — The type of the variable that drives this blendable parameter.
- L62 _public member_ `TObjectPtr<const UScriptStruct> BlendableStructType;` — `UPROPERTY()` — The type of the structure if VariableType is BlendableStruct.
- L70 _public member_ `FCameraContextDataID DataID;` — `UPROPERTY()` — The ID of the data that drives this blendable parameter.
- L74 _public member_ `ECameraContextDataType DataType = ECameraContextDataType::Name;` — `UPROPERTY()` — The type of the data that drives this blendable parameter.
- L78 _public member_ `ECameraContextDataContainerType DataContainerType = ECameraContextDataContainerType::None;` — `UPROPERTY()` — The type of container that drives this blendable parameter.
- L82 _public member_ `TObjectPtr<const UObject> DataTypeObject;` — `UPROPERTY()` — The type object of the data that drives this blendable parameter.
- L86 _public prototype_ `bool operator==(const FCameraObjectInterfaceParameterDefinition& Other) const = default;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraObjectInterfaceParameterDefinition> : public TStructOpsTypeTraitsBase2<FCameraObjectInterfaceParameterDefinition>`  
_L90-96_
- inherits: `TStructOpsTypeTraitsBase2<FCameraObjectInterfaceParameterDefinition>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L93-95_

#### Free symbols / members of external scopes

- L94 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anona82c1fdf0103`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraObjectRtti.h` (Public)


#### struct `UE::Cameras::FCameraObjectTypeID`  
`struct FCameraObjectTypeID`  
_L16-59_
- desc: Identifier for a given RTTI-enabled class.
- L33 _public function_ `uint32 GetTypeID() const`
- L38 _public function_ `bool IsValid() const`
- L43 _public function_ `FCameraObjectTypeID(uint32 InID) : ID(InID)`
- L47 _public function_ `static FCameraObjectTypeID Invalid()`
- L54 _protected prototype_ `static uint32 RegisterNewID();`
- L58 _protected member_ `uint32 ID;`

#### struct `UE::Cameras::FCameraObjectTypeInfo`  
`struct FCameraObjectTypeInfo`  
_L64-76_
- desc: Type information about an RTTI-enabled class.
- L66 _public member_ `FName TypeName;`
- L68 _public member_ `uint32 Sizeof = 0;`
- L69 _public member_ `uint32 Alignof = 0;`
- L71 _public typedef_ `using FConstructor = void(*)(void*);`
- L72 _public member_ `FConstructor Constructor;`
- L74 _public typedef_ `using FDestructor = void(*)(void*);`
- L75 _public member_ `FDestructor Destructor;`

#### class `UE::Cameras::FCameraObjectTypeRegistry`  
`class FCameraObjectTypeRegistry`  
_L81-98_
- desc: Type registry of known RTTI-enabled classes.
- L85 _public prototype_ `static FCameraObjectTypeRegistry& Get();`
- L87 _public prototype_ `void RegisterType(FCameraObjectTypeID TypeID, FCameraObjectTypeInfo&& TypeInfo);`
- L88 _public prototype_ `FCameraObjectTypeID FindTypeByName(const FName& TypeName) const;`
- L89 _public prototype_ `const FCameraObjectTypeInfo* GetTypeInfo(FCameraObjectTypeID TypeID) const;`
- L90 _public prototype_ `FName GetTypeNameSafe(FCameraObjectTypeID TypeID) const;`
- L92 _public prototype_ `void ConstructObject(FCameraObjectTypeID TypeID, void* Ptr);`
- L96 _private member_ `TMap<FName, uint32> TypeIDsByName;`
- L97 _private member_ `TSparseArray<FCameraObjectTypeInfo> TypeInfos;`

#### struct `UE::Cameras::TCameraObjectTypeID`  
`template<typename T> struct TCameraObjectTypeID : FCameraObjectTypeID`  
_L104-134_
- inherits: `FCameraObjectTypeID`
- desc: Strongly-typed ID wrapper for an RTTI-enabled class.
- L108 _private function_ `TCameraObjectTypeID(uint32 InID) : FCameraObjectTypeID(InID)`
- L110 _private function_ `static TCameraObjectTypeID RegisterType(const FName& InClassName)`
- L123 _private function_ `static void StaticConstructor(void* Ptr)`
- L128 _private function_ `static void StaticDestructor(void* Ptr)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)
- L18 _function_ `friend uint32 GetTypeHash(FCameraObjectTypeID In)` (scope `UE::Cameras`)
- L23 _function_ `friend bool operator<(FCameraObjectTypeID A, FCameraObjectTypeID B)` (scope `UE::Cameras`)
- L28 _function_ `friend bool operator==(FCameraObjectTypeID A, FCameraObjectTypeID B)` (scope `UE::Cameras`)
- L143 _macro_ `#define UE_GAMEPLAY_CAMERAS_DECLARE_RTTI_BASE(ApiDeclSpec, ClassName)\` — Macros for enabling simple RTTI information on a class hierarchy. The first macro is for the root of the class hierarchy, while the second is for all other classes below it. The third macro goes in the cpp file of each class.
- L157 _macro_ `#define UE_GAMEPLAY_CAMERAS_DECLARE_RTTI(ApiDeclSpec, ClassName, BaseClassName)\`
- L166 _macro_ `#define UE_GAMEPLAY_CAMERAS_DEFINE_RTTI(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraObjectStorage.h` (Public)


#### struct `UE::Cameras::TCameraObjectStorageTraits`  
`template<typename BaseObjectType> struct TCameraObjectStorageTraits`  
_L20-24_
- desc: Default traits for specific storages.
- L22 _public member_ `static const uint32 DefaultPageCapacity = 128;`
- L23 _public member_ `static const uint32 DefaultPageAlignment = 32;`

#### class `UE::Cameras::TCameraObjectStorage`  
`template<typename BaseObjectType> class TCameraObjectStorage`  
_L34-116_
- desc: A utility class that allocates and stores objects of, or derived from, a common base class. The storage is a paged buffer composed of one or more pages. If the needed storage size and alignment are known ahead of time, you can pre-allocate the first page appropriately and avoid any further paging.
- L38 _protected prototype_ `TCameraObjectStorage();`
- L39 _protected prototype_ `TCameraObjectStorage(TCameraObjectStorage&& Other);`
- L40 _protected prototype_ `TCameraObjectStorage& operator=(TCameraObjectStorage&& Other);`
- L41 _protected prototype_ `~TCameraObjectStorage();`
- L43 _protected prototype_ `TCameraObjectStorage(const TCameraObjectStorage&) = delete;`
- L44 _protected prototype_ `TCameraObjectStorage& operator=(const TCameraObjectStorage&) = delete;`
- L57 _protected prototype_ `BuildObject(ArgTypes&&... InArgs);`
- L67 _protected prototype_ `void* BuildObjectUninitialized(uint32 Sizeof, uint32 Alignof);` — Allocates memory for an object of the given size and alignment, but doesn't initialize anything in that memory block. After the caller has constructed the object in-place, they MUST call RegisterInitializedObject() with the actual object pointer, otherwise the storage won't call its destructor.
- L72 _protected prototype_ `void RegisterInitializedObject(BaseObjectType* BaseObjectPtr);` — Called to register an object after it has been constructed.
- L77 _protected prototype_ `void DestroyObject(BaseObjectType* BaseObjectPtr, uint32 MemoryResetSize = 0);` — Destroys a given object.
- L84 _protected prototype_ `void DestroyObjects(bool bFreeAllocations = false);` — Destroys all objects in the storage. @param bFreeAllocations Whether to also free the memory buffers
- L89 _protected prototype_ `void GetAllocationInfo(uint32& OutTotalUsed, uint32& OutFirstAlignment) const;` — Computes information about the overall allocated memory.
- L94 _protected prototype_ `void AllocatePage(uint32 InCapacity, uint32 InAlignment);` — Allocates a new page buffer.
- L107 _private member_ `TArray<FAllocation> Allocations;` — Allocated page buffers
- L115 _private member_ `TArray<FObjectInfo> ObjectInfos;` — List of built objects
- L119 _function_ `template<typename BaseObjectType> TCameraObjectStorage<BaseObjectType>::TCameraObjectStorage()`
- L124 _function_ `template<typename BaseObjectType> TCameraObjectStorage<BaseObjectType>::TCameraObjectStorage(TCameraObjectStorage&& Other)`
- L131 _function_ `template<typename BaseObjectType> TCameraObjectStorage<BaseObjectType>& TCameraObjectStorage<BaseObjectType>::operator=(TCameraObjectStorage&& Other)`
- L142 _function_ `template<typename BaseObjectType> TCameraObjectStorage<BaseObjectType>::~TCameraObjectStorage()`
- L150 _function_ `TCameraObjectStorage<BaseObjectType>::BuildObject(ArgTypes&&... InArgs)`
- L164 _function_ `template<typename BaseObjectType> void* TCameraObjectStorage<BaseObjectType>::BuildObjectUninitialized(uint32 Sizeof, uint32 Alignof)`
- L208 _function_ `template<typename BaseObjectType> void TCameraObjectStorage<BaseObjectType>::RegisterInitializedObject(BaseObjectType* BaseObjectPtr)`
- L214 _function_ `template<typename BaseObjectType> void TCameraObjectStorage<BaseObjectType>::DestroyObject(BaseObjectType* BaseObjectPtr, uint32 MemoryResetSize)`
- L247 _function_ `template<typename BaseObjectType> void TCameraObjectStorage<BaseObjectType>::DestroyObjects(bool bFreeAllocations)`
- L276 _function_ `template<typename BaseObjectType> void TCameraObjectStorage<BaseObjectType>::GetAllocationInfo(uint32& OutTotalUsed, uint32& OutFirstAlignment) const`
- L297 _function_ `template<typename BaseObjectType> void TCameraObjectStorage<BaseObjectType>::AllocatePage(uint32 InCapacity, uint32 InAlignment)`

#### struct `UE::Cameras::TCameraObjectStorage::FAllocation`  
`struct FAllocation`  
_L99-105_
- desc: Allocation page
- L101 _public member_ `uint8* Memory = nullptr;`
- L102 _public member_ `uint32 Alignment = 0;`
- L103 _public member_ `uint32 Capacity = 0;`
- L104 _public member_ `uint32 Used = 0;`

#### struct `UE::Cameras::TCameraObjectStorage::FObjectInfo`  
`struct FObjectInfo`  
_L110-113_
- desc: Pointer and info of objects inside the page buffers
- L112 _public member_ `BaseObjectType* Ptr = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L186 _typedef_ `using FStorageTraits = TCameraObjectStorageTraits<BaseObjectType>;` (scope `UE::Cameras::TCameraObjectStorage::BuildObjectUninitialized`)
- L218 _function_ `` (scope `UE::Cameras::TCameraObjectStorage::DestroyObject`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraOperation.h` (Public)


#### enum `UE::Cameras::EBuiltInCameraOperationTypes`  
`enum EBuiltInCameraOperationTypes : uint32`  
_L14-21_
- desc: Hard-coded type IDs for built-in camera operations.
- L16 _public enumerator_ `YawPitch = 0`
- L17 _public enumerator_ `SingleValue = 1`
- L18 _public enumerator_ `LockUserInput = 2`
- L20 _public enumerator_ `MAX = 3`

#### struct `UE::Cameras::FCameraOperationTypeID`  
`struct FCameraOperationTypeID`  
_L26-50_
- desc: Simple type ID for camera operations.
- L28 _public function_ `FCameraOperationTypeID() : Value(INVALID)`
- L30 _public function_ `FCameraOperationTypeID(uint32 InValue) : Value(InValue)`
- L35 _public prototype_ `static FCameraOperationTypeID RegisterNew();` — Generate a new operation type ID.
- L38 _public function_ `bool IsValid() const` — Returns whether this ID is valid.
- L47 _private member_ `static const uint32 INVALID = (uint32)-1;`
- L49 _private member_ `uint32 Value;`

#### struct `UE::Cameras::FCameraOperation`  
`struct FCameraOperation`  
_L55-79_
- desc: Base class for an operation to be executed on a camera rig.
- L61 _public function_ `template<typename OperationType> OperationType* CastOperation()` — Attempts to cast this operation into a sub-class.
- L72 _protected function_ `FCameraOperation(FCameraOperationTypeID InOperationTypeID) : OperationTypeID(InOperationTypeID)`
- L78 _private member_ `FCameraOperationTypeID OperationTypeID;`

#### struct `UE::Cameras::FYawPitchCameraOperation`  
`struct FYawPitchCameraOperation : public FCameraOperation`  
_L93-101_
- inherits: `FCameraOperation`
- desc: A camera operation that tries to correct the yaw/pitch of a camera rig.
- L95 _public prototype_ `UE_DECLARE_BUILT_IN_CAMERA_OPERATION(FYawPitchCameraOperation, EBuiltInCameraOperationTypes::YawPitch) FConsumableDouble Yaw;`
- L100 _public member_ `FConsumableDouble Pitch;` — The pitch value to set or use as modifier.

#### struct `UE::Cameras::FSingleValueCameraOperation`  
`struct FSingleValueCameraOperation : public FCameraOperation`  
_L107-112_
- inherits: `FCameraOperation`
- desc: A camera operation that tries to correct a single undetermined input value on a camera rig.
- L109 _public prototype_ `UE_DECLARE_BUILT_IN_CAMERA_OPERATION(FSingleValueCameraOperation, EBuiltInCameraOperationTypes::SingleValue) FConsumableDouble Value;`

#### struct `UE::Cameras::FLockUserInputCameraOperation`  
`struct FLockUserInputCameraOperation : public FCameraOperation`  
_L117-123_
- inherits: `FCameraOperation`
- desc: A camera operation that locks user input for a frame.
- L119 _public prototype_ `UE_DECLARE_BUILT_IN_CAMERA_OPERATION(FLockUserInputCameraOperation, EBuiltInCameraOperationTypes::LockUserInput) bool bLockThisFrame = true;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Cameras` (scope `UE`)
- L40 _function_ `friend bool operator==(FCameraOperationTypeID A, FCameraOperationTypeID B)` (scope `UE::Cameras`)
- L81 _macro_ `#define UE_DECLARE_BUILT_IN_CAMERA_OPERATION(OperationName, OperationType)\`
- L129 _macro_ `#define UE_DECLARE_CAMERA_OPERATION(ApiDeclSpec, OperationName)\`
- L136 _macro_ `#define UE_DEFINE_CAMERA_OPERATION(OperationName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraParameterReader.h` (Public)


#### class `UE::Cameras::TCameraParameterReader`  
`template<typename ValueType> class TCameraParameterReader`  
_L16-80_
- desc: A utility class for reading the effective value of a camera parameter.
- L20 _public function_ `TCameraParameterReader()`
- L23 _public function_ `template<typename ParameterType> TCameraParameterReader(const ParameterType& Parameter)`
- L32 _public function_ `template<typename ParameterType> void Initialize(const ParameterType& Parameter)` — Initializes the reader around the given parameter.
- L47 _public function_ `const ValueType& Get(const FCameraVariableTable& VariableTable) const` — Gets the actual value for the parameter.
- L69 _public function_ `bool IsDriven() const` — Returns whether the parameter is driven by a variable.
- L77 _private member_ `const ValueType* DefaultValuePtr = nullptr;` — Pointer to the value in the parameter.
- L79 _private member_ `FCameraVariableID VariableID;` — The ID of the variable driving the parameter, if any.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraParameters.h` (Public)


#### struct `FBooleanCameraParameter`  
`struct FBooleanCameraParameter`  
_L44-63_
- reflection: `USTRUCT(BlueprintType)`
- desc: Boolean camera parameter.
- L48 _public typedef_ `using ValueType = bool;`
- L49 _public typedef_ `using VariableAssetType = UBooleanCameraVariable;`
- L52 _public member_ `bool Value = false;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L55 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L58 _public member_ `TObjectPtr<UBooleanCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L60 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FInteger32CameraParameter`  
`struct FInteger32CameraParameter`  
_L67-86_
- reflection: `USTRUCT(BlueprintType)`
- desc: Integer camera parameter.
- L71 _public typedef_ `using ValueType = int32;`
- L72 _public typedef_ `using VariableAssetType = UInteger32CameraVariable;`
- L75 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L78 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L81 _public member_ `TObjectPtr<UInteger32CameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L83 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FFloatCameraParameter`  
`struct FFloatCameraParameter`  
_L90-109_
- reflection: `USTRUCT(BlueprintType)`
- desc: Float camera parameter.
- L94 _public typedef_ `using ValueType = float;`
- L95 _public typedef_ `using VariableAssetType = UFloatCameraVariable;`
- L98 _public member_ `float Value = 0.f;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L101 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L104 _public member_ `TObjectPtr<UFloatCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L106 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FDoubleCameraParameter`  
`struct FDoubleCameraParameter`  
_L113-132_
- reflection: `USTRUCT(BlueprintType)`
- desc: Double camera parameter.
- L117 _public typedef_ `using ValueType = double;`
- L118 _public typedef_ `using VariableAssetType = UDoubleCameraVariable;`
- L121 _public member_ `double Value = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L124 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L127 _public member_ `TObjectPtr<UDoubleCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L129 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FVector2fCameraParameter`  
`struct FVector2fCameraParameter`  
_L136-156_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vector2f camera parameter.
- L140 _public typedef_ `using ValueType = FVector2f;`
- L141 _public typedef_ `using VariableAssetType = UVector2fCameraVariable;`
- L144 _public member_ `FVector2f Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L147 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L150 _public member_ `TObjectPtr<UVector2fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L152 _public prototype_ `FVector2fCameraParameter();`
- L153 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FVector2dCameraParameter`  
`struct FVector2dCameraParameter`  
_L160-180_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vector2d camera parameter.
- L164 _public typedef_ `using ValueType = FVector2D;`
- L165 _public typedef_ `using VariableAssetType = UVector2dCameraVariable;`
- L168 _public member_ `FVector2D Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L171 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L174 _public member_ `TObjectPtr<UVector2dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L176 _public prototype_ `FVector2dCameraParameter();`
- L177 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FVector3fCameraParameter`  
`struct FVector3fCameraParameter`  
_L184-204_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vector3f camera parameter.
- L188 _public typedef_ `using ValueType = FVector3f;`
- L189 _public typedef_ `using VariableAssetType = UVector3fCameraVariable;`
- L192 _public member_ `FVector3f Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L195 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L198 _public member_ `TObjectPtr<UVector3fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L200 _public prototype_ `FVector3fCameraParameter();`
- L201 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FVector3dCameraParameter`  
`struct FVector3dCameraParameter`  
_L208-228_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vector3d camera parameter.
- L212 _public typedef_ `using ValueType = FVector;`
- L213 _public typedef_ `using VariableAssetType = UVector3dCameraVariable;`
- L216 _public member_ `FVector Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L219 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L222 _public member_ `TObjectPtr<UVector3dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L224 _public prototype_ `FVector3dCameraParameter();`
- L225 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FVector4fCameraParameter`  
`struct FVector4fCameraParameter`  
_L232-252_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vector4f camera parameter.
- L236 _public typedef_ `using ValueType = FVector4f;`
- L237 _public typedef_ `using VariableAssetType = UVector4fCameraVariable;`
- L240 _public member_ `FVector4f Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L243 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L246 _public member_ `TObjectPtr<UVector4fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L248 _public prototype_ `FVector4fCameraParameter();`
- L249 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FVector4dCameraParameter`  
`struct FVector4dCameraParameter`  
_L256-276_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vector4d camera parameter.
- L260 _public typedef_ `using ValueType = FVector4;`
- L261 _public typedef_ `using VariableAssetType = UVector4dCameraVariable;`
- L264 _public member_ `FVector4 Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L267 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L270 _public member_ `TObjectPtr<UVector4dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L272 _public prototype_ `FVector4dCameraParameter();`
- L273 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FRotator3fCameraParameter`  
`struct FRotator3fCameraParameter`  
_L280-300_
- reflection: `USTRUCT(BlueprintType)`
- desc: Rotator3f camera parameter.
- L284 _public typedef_ `using ValueType = FRotator3f;`
- L285 _public typedef_ `using VariableAssetType = URotator3fCameraVariable;`
- L288 _public member_ `FRotator3f Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L291 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L294 _public member_ `TObjectPtr<URotator3fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L296 _public prototype_ `FRotator3fCameraParameter();`
- L297 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FRotator3dCameraParameter`  
`struct FRotator3dCameraParameter`  
_L304-324_
- reflection: `USTRUCT(BlueprintType)`
- desc: Rotator3d camera parameter.
- L308 _public typedef_ `using ValueType = FRotator;`
- L309 _public typedef_ `using VariableAssetType = URotator3dCameraVariable;`
- L312 _public member_ `FRotator Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L315 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L318 _public member_ `TObjectPtr<URotator3dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L320 _public prototype_ `FRotator3dCameraParameter();`
- L321 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FTransform3fCameraParameter`  
`struct FTransform3fCameraParameter`  
_L328-347_
- reflection: `USTRUCT(BlueprintType)`
- desc: Transform3f camera parameter.
- L332 _public typedef_ `using ValueType = FTransform3f;`
- L333 _public typedef_ `using VariableAssetType = UTransform3fCameraVariable;`
- L336 _public member_ `FTransform3f Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L339 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L342 _public member_ `TObjectPtr<UTransform3fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L344 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `FTransform3dCameraParameter`  
`struct FTransform3dCameraParameter`  
_L351-370_
- reflection: `USTRUCT(BlueprintType)`
- desc: Transform3d camera parameter.
- L355 _public typedef_ `using ValueType = FTransform;`
- L356 _public typedef_ `using VariableAssetType = UTransform3dCameraVariable;`
- L359 _public member_ `FTransform Value;` — `UPROPERTY(EditAnywhere, Interp, Category=Common, meta=(SequencerUseParentPropertyName=true))`
- L362 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L365 _public member_ `TObjectPtr<UTransform3dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category=Common)`
- L367 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L18 _macro_ `#define UE_DEFINE_CAMERA_PARAMETER_VALUE_CONSTRUCTORS(ParameterClass)\`
- L28 _macro_ `#define UE_DEFINE_CAMERA_PARAMETER_ALL_CONSTRUCTORS(ParameterClass)\`
- L376 _function_ `template<typename ValueType> bool CameraParameterValueEquals(typename TCallTraits<ValueType>::ParamType A, typename TCallTraits<ValueType>::ParamType B)`
- L382 _function_ `template<> inline bool CameraParameterValueEquals<FTransform3f>(const FTransform3f& A, const FTransform3f& B)`
- L388 _function_ `template<> inline bool CameraParameterValueEquals<FTransform3d>(const FTransform3d& A, const FTransform3d& B)`
- L398 _macro_ `#define UE_CAMERA_VARIABLE_FOR_TYPE(ValueType, ValueName)\` — Any camera parameter might replace a previously non-parameterized property (i.e. a "fixed" property of the underlying type, like bool, int32, float, etc.) When someone upgrades the fixed property to a parameterized property, any previously saved data will run into a mismatched tag. So the parameters will handle that by loading the saved value inside of them.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraPose.h` (Public)


#### struct `FCameraPoseFlags`  
`struct FCameraPoseFlags`  
_L65-93_
- desc: Boolean flags for each of the properties inside FCameraPose.
- L70 _public prototype_ `UE_CAMERA_POSE_FOR_ALL_PROPERTIES() #undef UE_CAMERA_POSE_FOR_PROPERTY public: static const FCameraPoseFlags& All();`
- L80 _public prototype_ `FCameraPoseFlags();` — Creates a new flags structure.
- L82 _public prototype_ `FCameraPoseFlags(bool bInValue);` — Creates a new flags structure with all flags set to the given value.
- L85 _public prototype_ `FCameraPoseFlags& SetAllFlags(bool bInValue);` — Sets all flags to the given value.
- L87 _public prototype_ `FCameraPoseFlags& ExclusiveCombine(const FCameraPoseFlags& OtherFlags);` — Sets the flags that are set in OtherFlags, but checks that no flag is set on both structures.
- L90 _public prototype_ `FCameraPoseFlags& AND(const FCameraPoseFlags& OtherFlags);` — Combines the flags with an AND logical operation.
- L92 _public prototype_ `FCameraPoseFlags& OR(const FCameraPoseFlags& OtherFlags);` — Combines the flags with an OR logical operation.

#### struct `FCameraPose`  
`struct FCameraPose`  
_L102-385_
- reflection: `USTRUCT()`
- desc: Structure describing the state of a camera. Fields are private and can only be accessed via the getters and setters. The ChangedFlags structure keeps track of which fields were changed via the setters.
- L108 _public prototype_ `FCameraPose();`
- L111 _public prototype_ `void Reset();` — Resets this camera pose to its default values, with all changed flags off.
- L140 _public function_ `FCameraPoseFlags& GetChangedFlags()` — Get the changed flags.
- L142 _public function_ `const FCameraPoseFlags& GetChangedFlags() const` — Get the changed flags.
- L145 _public function_ `void SetChangedFlags(const FCameraPoseFlags& InChangedFlags)` — Set the changed flags.
- L147 _public prototype_ `void SetAllChangedFlags();` — Set all fields as changed.
- L149 _public prototype_ `void ClearAllChangedFlags();` — Set all fields as clean.
- L156 _public prototype_ `FTransform3d GetTransform() const;` — Gets the transform of the camera.
- L159 _public prototype_ `void SetTransform(FTransform3d Transform, bool bForceSet = false);` — Sets the transform of the camera.
- L166 _public prototype_ `double GetEffectiveFieldOfView(bool bIncludeOverscan = true) const;` — Computes the horizontal field of view of the camera. The effective field of view can be driven by the FieldOfView property, or the FocalLength property in combination with the sensor size.
- L169 _public prototype_ `double GetSensorAspectRatio() const;` — Gets the aspect ratio of the camera sensor.
- L172 _public prototype_ `EAspectRatioAxisConstraint GetEffectiveAspectRatioAxisConstraint() const;` — Gets the aspect ratio axis constraint if overriden, otherwise a default one.
- L175 _public prototype_ `EAspectRatioAxisConstraint GetEffectiveAspectRatioAxisConstraint(EAspectRatioAxisConstraint DefaultAspectRatioAxisConstraint) const;` — Gets the aspect ratio axis constraint if overriden, otherwise the provided default one.
- L178 _public prototype_ `double GetHorizontalProjectionOffset() const;` — Gets the horizontal projection offset.
- L181 _public prototype_ `double GetVerticalProjectionOffset() const;` — Gets the vertical projection offset.
- L184 _public prototype_ `FRay3d GetAimRay() const;` — Gets the aiming ray of the camera.
- L187 _public prototype_ `FVector3d GetAimDir() const;` — Gets the aiming direction of the camera.
- L190 _public prototype_ `FVector3d GetTarget() const;` — Gets the location of the camera's target.
- L193 _public prototype_ `FVector3d GetTarget(double InTargetDistance) const;` — Gets the location of the camera's target given a specific distance.
- L198 _public prototype_ `static double GetEffectiveFieldOfView(float FocalLength, float FieldOfView, float SensorWidth, float SensorHeight, float SqueezeFactor = 1.f, float Overscan = 1.f);` — Computes the horizontal field of view of a camera.
- L201 _public prototype_ `static double GetSensorAspectRatio(float SensorWidth, float SensorHeight);` — Computes the aspect ratio of a camera sensor.
- L204 _public prototype_ `static void GetDefaultSensorSize(float& OutSensorWidth, float& OutSensorHeight);` — Gets the default sensor size.
- L209 _public prototype_ `void GetViewInfo(FMinimalViewInfo& OutViewInfo) const;` — Exports the current camera pose to the given view info.
- L222 _public prototype_ `bool ApplyPhysicalCameraSettings(FPostProcessSettings& PostProcessSettings, bool bOverwriteSettings = false) const;` — Applies the necessary post-process settings given the current values on this camera pose. This function doesn't do anything if EnablePhysicalCamera is false, or if PhysicalCameraBlendWeight is zero or less. @param PostProcessSettings  The post-process settings to modify @param bOverwriteSettings   Whether to overwrite values found to already be set @return  Whether post-process settings were created.
- L229 _public prototype_ `void OverrideAll(const FCameraPose& OtherPose);` — Takes all properties from OtherPose and sets them on this camera pose.
- L231 _public prototype_ `void OverrideChanged(const FCameraPose& OtherPose);` — Takes all changed properties from OtherPose and sets them on this camera pose.
- L233 _public prototype_ `void LerpAll(const FCameraPose& ToPose, float Factor);` — Interpolates all properties from ToPose using the given factor.
- L235 _public prototype_ `void LerpChanged(const FCameraPose& ToPose, float Factor);` — Interpolates all changed properties from ToPose using the given factor.
- L237 _public prototype_ `void LerpChanged(const FCameraPose& ToPose, float Factor, const FCameraPoseFlags& InMask, bool bInvertMask, FCameraPoseFlags& OutMask);` — Interpolates changed properties from ToPose using the given factor. Only properties defined by InMask are taken into account.
- L242 _public prototype_ `static void SerializeWithFlags(FArchive& Ar, FCameraPose& CameraPose);` — Serializes the given camera pose including the written-property flags.
- L245 _public prototype_ `void SerializeWithFlags(FArchive& Ar);` — Serializes this camera pose including the written-property flags.
- L249 _private prototype_ `void InternalOverrideChanged(const FCameraPose& OtherPose, bool bChangedOnly);`
- L250 _private prototype_ `void InternalLerpChanged(const FCameraPose& ToPose, float Factor, const FCameraPoseFlags& InMask, bool bInvertMask, FCameraPoseFlags& OutMask, bool bChangedOnly);`
- L256 _private member_ `FVector3d Location = {0, 0, 0};` — `UPROPERTY()` — The location of the camera in the world
- L260 _private member_ `FRotator3d Rotation = {0, 0, 0};` — `UPROPERTY()` — The rotation of the camera in the world
- L264 _private member_ `double TargetDistance = 1000.0;` — `UPROPERTY()` — Distance to the target
- L271 _private member_ `float FieldOfView = -1.f;` — `UPROPERTY()` — The horizontal field of view of the camera, in degrees If zero or less, focal length is used instead
- L278 _private member_ `float FocalLength = 35.f;` — `UPROPERTY()` — The focal length of the camera's lens, in millimeters If zero or less, field of view is used instead
- L282 _private member_ `float FirstPersonFieldOfView = -1.f;` — `UPROPERTY()` — The horizontal field of view (in degrees) used for primitives tagged as "IsFirstPerson"
- L286 _private member_ `float FirstPersonScale = 1.f;` — `UPROPERTY()` — The scale to apply to primitives tagged as "IsFirstPerson"
- L290 _private member_ `float OrthographicWidth = DEFAULT_ORTHOWIDTH;` — `UPROPERTY()` — The desired width (in world units) of the orthographic view (ignored in Perspective mode)
- L294 _private member_ `float Aperture = 2.8f;` — `UPROPERTY()` — The aperture of the camera's lens, in f-stops
- L298 _private member_ `float ShutterSpeed = 60.f;` — `UPROPERTY()` — The shutter speed of the camera's lens, in 1/seconds
- L302 _private member_ `float FocusDistance = -1.f;` — `UPROPERTY()` — The focus distance of the camera's lens, in world units
- L306 _private member_ `float SensorWidth = 24.89f;` — `UPROPERTY()` — The width of the camera's sensor, in millimeters
- L310 _private member_ `float SensorHeight = 18.67f;` — `UPROPERTY()` — The height of the camera's sensor, in millimeters
- L314 _private member_ `float SensorHorizontalOffset = 0.f;` — `UPROPERTY()` — Horizontal offset of the sensor, in mm.
- L318 _private member_ `float SensorVerticalOffset = 0.f;` — `UPROPERTY()` — Vertical offset of the sensor, in mm.
- L322 _private member_ `float ISO = 100.f;` — `UPROPERTY()` — The camera sensor sensitivity in ISO.
- L326 _private member_ `float SqueezeFactor = 1.f;` — `UPROPERTY()` — Squeeze factor for anamorphic lenses
- L330 _private member_ `float Overscan = 0.f;` — `UPROPERTY()` — Sensor overscan in percentage
- L334 _private member_ `int32 DiaphragmBladeCount = 8;` — `UPROPERTY()` — Number of blades in the lens diaphragm
- L338 _private member_ `float NearClippingPlane = 10.f;` — `UPROPERTY()` — The distance to the near clipping plane, in world units
- L342 _private member_ `float FarClippingPlane = -1.f;` — `UPROPERTY()` — The distance to the far clipping plane, in world units
- L349 _private member_ `float PhysicalCameraBlendWeight = 0.f;` — `UPROPERTY()` — An internal weight for the physical camera post-process settings, used when blending between cameras with EnablePhysicalCamera enabled/disabled.
- L353 _private member_ `bool EnableFirstPerson = false;` — `UPROPERTY()` — Whether to enable first-person parameters (FOV, scale) for primitives tagged as "IsFirstPerson"
- L360 _private member_ `bool EnablePhysicalCamera = false;` — `UPROPERTY()` — Whether to setup post-process settings based on physical camera properties such as Aperture, FocusDistance, DiaphragmBladeCount, and so on.
- L364 _private member_ `bool ConstrainAspectRatio = false;` — `UPROPERTY()` — Whether to constrain aspect ratio
- L368 _private member_ `bool OverrideAspectRatioAxisConstraint = false;` — `UPROPERTY()` — Whether to override the default aspect ratio axis constraint defined on the player controller
- L372 _private member_ `TEnumAsByte<EAspectRatioAxisConstraint> AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;` — `UPROPERTY()` — If ConstrainAspectRatio is false and OverrideAspectRatioAxisConstraint is true, how we should compute FieldOfView
- L376 _private member_ `TEnumAsByte<ECameraProjectionMode::Type> ProjectionMode = ECameraProjectionMode::Perspective;` — `UPROPERTY()` — Projection mode - Perspective or orthographic
- L384 _private member_ `FCameraPoseFlags ChangedFlags;` — Flags keeping track of which properties were written to since last time the flags were cleared.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L20 _macro_ `#define UE_CAMERA_POSE_FOR_TRANSFORM_PROPERTIES()\`
- L24 _macro_ `#define UE_CAMERA_POSE_FOR_INTERPOLABLE_PROPERTIES()\`
- L44 _macro_ `#define UE_CAMERA_POSE_FOR_FOV_PROPERTIES()\`
- L48 _macro_ `#define UE_CAMERA_POSE_FOR_FLIPPING_PROPERTIES()\`
- L56 _macro_ `#define UE_CAMERA_POSE_FOR_ALL_PROPERTIES()\`
- L67 _macro_ `#define UE_CAMERA_POSE_FOR_PROPERTY(PropType, PropName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigAsset.h` (Public)


#### class `UE::Cameras::ICameraRigAssetEventHandler`  
`class ICameraRigAssetEventHandler`  
_L31-43_
- desc: Interface for listening to changes on a camera rig asset.
- L34 _public prototype_ `virtual ~ICameraRigAssetEventHandler() = default;`
- L37 _public function_ `virtual void OnCameraRigBuilt(const UCameraRigAsset* CameraRigAsset)` — Called when the camera rig asset has been built.
- L40 _public function_ `virtual void OnObjectAddedToGraph(const FName GraphName, UObject* Object)`
- L41 _public function_ `virtual void OnObjectRemovedFromGraph(const FName GraphName, UObject* Object)`

#### class `UCameraRigAsset`  
`class UCameraRigAsset : public UBaseCameraObject , public IGameplayTagAssetInterface , public IHasCameraBuildStatus , public IObjectTreeGraphObject , public IObjectTreeGraphRootObject`  
_L57-203_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBaseCameraObject,IGameplayTagAssetInterface,IHasCameraBuildStatus,IObjectTreeGraphObject,IObjectTreeGraphRootObject`
- desc: A camera rig asset, which runs a hierarchy of camera nodes to drive the behavior of a camera.
- L69 _public prototype_ `void GatherPackages(FCameraRigPackages& OutPackages) const;`
- L76 _public member_ `TObjectPtr<UCameraNode> RootNode;` — `UPROPERTY(Instanced)` — Root camera node.
- L80 _public member_ `FGameplayTagContainer GameplayTags;` — `UPROPERTY(EditAnywhere, Category=GameplayTags)` — The gameplay tags on this camera rig.
- L84 _public member_ `TArray<TObjectPtr<UCameraRigTransition>> EnterTransitions;` — `UPROPERTY(Instanced)` — List of enter transitions for this camera rig.
- L88 _public member_ `TArray<TObjectPtr<UCameraRigTransition>> ExitTransitions;` — `UPROPERTY(Instanced)` — List of exist transitions for this camera rig.
- L92 _public member_ `ECameraRigInitialOrientation InitialOrientation = ECameraRigInitialOrientation::None;` — `UPROPERTY(EditAnywhere, Category="Transition")` — Default orientation initialization when this camera rig is activated.
- L98 _public member_ `ECameraBuildStatus BuildStatus = ECameraBuildStatus::Dirty;` — `UPROPERTY(Transient)` — The current build state of this camera rig.
- L105 _public prototype_ `void BuildCameraRig();` — Builds this camera rig. This will validate the data, build the allocation info, and create internal camera variables for any exposed parameters.
- L110 _public prototype_ `void BuildCameraRig(UE::Cameras::FCameraBuildContext& InBuildContext);` — Builds this camera rig, similar to BuildCameraRig() but using a given build context.
- L115 _public function_ `virtual UCameraNode* GetRootNode() override` — BaseCameraObject interface.
- L118 _public prototype_ `virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;` — IGameplayTagAssetInterface interface.
- L121 _public function_ `virtual ECameraBuildStatus GetBuildStatus() const override` — IHasCameraBuildStatus interface.
- L122 _public prototype_ `virtual void DirtyBuildStatus() override;`
- L127 _public member_ `static const FName NodeTreeGraphName;` — Graph names for ObjectTreeGraph API.
- L128 _public member_ `static const FName TransitionsGraphName;`
- L131 _public member_ `UE::Cameras::TCameraEventHandlerContainer<UE::Cameras::ICameraRigAssetEventHandler> EventHandlers;` — Event handlers to be notified of data changes.
- L137 _protected prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;`
- L138 _protected prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`
- L139 _protected prototype_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override;`
- L140 _protected prototype_ `virtual const FString& GetGraphNodeCommentText(FName InGraphName) const override;`
- L141 _protected prototype_ `virtual void OnUpdateGraphNodeCommentText(FName InGraphName, const FString& NewComment) override;`
- L142 _protected prototype_ `virtual void GetGraphNodeName(FName InGraphName, FText& OutName) const override;`
- L147 _protected prototype_ `virtual void GetConnectableObjects(FName InGraphName, TSet<UObject*>& OutObjects) const override;`
- L148 _protected prototype_ `virtual void AddConnectableObject(FName InGraphName, UObject* InObject) override;`
- L149 _protected prototype_ `virtual void RemoveConnectableObject(FName InGraphName, UObject* InObject) override;`
- L153 _protected prototype_ `virtual void PostLoad() override;` — UObject interface
- L154 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L155 _protected prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L157 _protected prototype_ `virtual void GetAssetRegistryTagMetadata(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;`
- L166 _private member_ `FIntVector2 NodeGraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the camera rig node in the node graph editor.
- L170 _private member_ `FIntVector2 TransitionGraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the camera rig node in the transition graph editor.
- L174 _private member_ `FString NodeGraphNodeComment;` — `UPROPERTY()` — User-written comment in the node graph editor.
- L178 _private member_ `FString TransitionGraphNodeComment;` — `UPROPERTY()` — User-written comment in the transition graph editor.
- L185 _private member_ `TArray<TObjectPtr<UObject>> AllNodeTreeObjects;` — `UPROPERTY(Instanced, meta=(ObjectTreeGraphHidden=true))` — A list of all the camera nodes, including the 'loose' ones that aren't connected to the root node, and therefore would be GC'ed if we didn't hold them here.
- L191 _private member_ `TArray<TObjectPtr<UObject>> AllTransitionsObjects;` — `UPROPERTY(Instanced, meta=(ObjectTreeGraphHidden=true))` — Similar to AllNodeTreeObjects, but for the transitions graph.
- L196 _private member_ `int32 GraphNodePosX_DEPRECATED = 0;` — `UPROPERTY()`
- L198 _private member_ `int32 GraphNodePosY_DEPRECATED = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)
- L50 _typedef_ `using FCameraRigPackages = TArray<const UPackage*, TInlineAllocator<4>>;` — List of packages that contain the definition of a camera rig. In most cases there's only one, but with nested assets there could be more.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigAssetReference.h` (Public)


#### struct `FCameraRigParameterOverrideBase`  
`struct FCameraRigParameterOverrideBase`  
_L46-61_
- reflection: `USTRUCT()`
- L51 _public member_ `FGuid InterfaceParameterGuid;` — `UPROPERTY()`
- L54 _public member_ `FGuid PrivateVariableGuid;` — `UPROPERTY()`
- L57 _public member_ `FString InterfaceParameterName;` — `UPROPERTY()`
- L60 _public member_ `bool bInvalid = false;` — `UPROPERTY()`

#### struct `FBooleanCameraRigParameterOverride`  
`struct FBooleanCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L66-72_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L71 _public member_ `FBooleanCameraParameter Value;` — `UPROPERTY()`

#### struct `FInteger32CameraRigParameterOverride`  
`struct FInteger32CameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L75-81_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L80 _public member_ `FInteger32CameraParameter Value;` — `UPROPERTY()`

#### struct `FFloatCameraRigParameterOverride`  
`struct FFloatCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L84-90_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L89 _public member_ `FFloatCameraParameter Value;` — `UPROPERTY()`

#### struct `FDoubleCameraRigParameterOverride`  
`struct FDoubleCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L93-99_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L98 _public member_ `FDoubleCameraParameter Value;` — `UPROPERTY()`

#### struct `FVector2fCameraRigParameterOverride`  
`struct FVector2fCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L102-108_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L107 _public member_ `FVector2fCameraParameter Value;` — `UPROPERTY()`

#### struct `FVector2dCameraRigParameterOverride`  
`struct FVector2dCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L111-117_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L116 _public member_ `FVector2dCameraParameter Value;` — `UPROPERTY()`

#### struct `FVector3fCameraRigParameterOverride`  
`struct FVector3fCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L120-126_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L125 _public member_ `FVector3fCameraParameter Value;` — `UPROPERTY()`

#### struct `FVector3dCameraRigParameterOverride`  
`struct FVector3dCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L129-135_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L134 _public member_ `FVector3dCameraParameter Value;` — `UPROPERTY()`

#### struct `FVector4fCameraRigParameterOverride`  
`struct FVector4fCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L138-144_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L143 _public member_ `FVector4fCameraParameter Value;` — `UPROPERTY()`

#### struct `FVector4dCameraRigParameterOverride`  
`struct FVector4dCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L147-153_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L152 _public member_ `FVector4dCameraParameter Value;` — `UPROPERTY()`

#### struct `FRotator3fCameraRigParameterOverride`  
`struct FRotator3fCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L156-162_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L161 _public member_ `FRotator3fCameraParameter Value;` — `UPROPERTY()`

#### struct `FRotator3dCameraRigParameterOverride`  
`struct FRotator3dCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L165-171_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L170 _public member_ `FRotator3dCameraParameter Value;` — `UPROPERTY()`

#### struct `FTransform3fCameraRigParameterOverride`  
`struct FTransform3fCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L174-180_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L179 _public member_ `FTransform3fCameraParameter Value;` — `UPROPERTY()`

#### struct `FTransform3dCameraRigParameterOverride`  
`struct FTransform3dCameraRigParameterOverride : public FCameraRigParameterOverrideBase`  
_L183-189_
- reflection: `USTRUCT()`
- inherits: `FCameraRigParameterOverrideBase`
- L188 _public member_ `FTransform3dCameraParameter Value;` — `UPROPERTY()`

#### struct `FCameraRigParameterOverrides`  
`struct FCameraRigParameterOverrides`  
_L198-238_
- reflection: `USTRUCT()`
- desc: A structure that holds lists of camera rig interface parameter overrides, one list per parameter type.
- L207 _private member_ `TArray<FBooleanCameraRigParameterOverride> BooleanOverrides;` — `UPROPERTY()`
- L209 _private member_ `TArray<FInteger32CameraRigParameterOverride> Integer32Overrides;` — `UPROPERTY()`
- L211 _private member_ `TArray<FFloatCameraRigParameterOverride> FloatOverrides;` — `UPROPERTY()`
- L213 _private member_ `TArray<FDoubleCameraRigParameterOverride> DoubleOverrides;` — `UPROPERTY()`
- L215 _private member_ `TArray<FVector2fCameraRigParameterOverride> Vector2fOverrides;` — `UPROPERTY()`
- L217 _private member_ `TArray<FVector2dCameraRigParameterOverride> Vector2dOverrides;` — `UPROPERTY()`
- L219 _private member_ `TArray<FVector3fCameraRigParameterOverride> Vector3fOverrides;` — `UPROPERTY()`
- L221 _private member_ `TArray<FVector3dCameraRigParameterOverride> Vector3dOverrides;` — `UPROPERTY()`
- L223 _private member_ `TArray<FVector4fCameraRigParameterOverride> Vector4fOverrides;` — `UPROPERTY()`
- L225 _private member_ `TArray<FVector4dCameraRigParameterOverride> Vector4dOverrides;` — `UPROPERTY()`
- L227 _private member_ `TArray<FRotator3fCameraRigParameterOverride> Rotator3fOverrides;` — `UPROPERTY()`
- L229 _private member_ `TArray<FRotator3dCameraRigParameterOverride> Rotator3dOverrides;` — `UPROPERTY()`
- L231 _private member_ `TArray<FTransform3fCameraRigParameterOverride> Transform3fOverrides;` — `UPROPERTY()`
- L233 _private member_ `TArray<FTransform3dCameraRigParameterOverride> Transform3dOverrides;` — `UPROPERTY()`

#### struct `FCameraRigAssetReference`  
`struct FCameraRigAssetReference : public FBaseCameraObjectReference`  
_L245-333_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FBaseCameraObjectReference`
- desc: A structure holding a reference to a camera rig asset, along with the interface parameter override values.
- L251 _public prototype_ `FCameraRigAssetReference();`
- L252 _public prototype_ `FCameraRigAssetReference(UCameraRigAsset* InCameraRig);`
- L255 _public function_ `bool IsValid() const` — Returns whether this reference points to a valid camera rig.
- L261 _public function_ `UCameraRigAsset* GetCameraRig()` — Gets the referenced camera rig.
- L267 _public function_ `const UCameraRigAsset* GetCameraRig() const` — Gets the referenced camera rig.
- L273 _public function_ `void SetCameraRig(UCameraRigAsset* InCameraRig)` — Sets the referenced camera rig.
- L285 _public prototype_ `void EnsureAllocationInfo(UE::Cameras::FCameraNodeEvaluationResult& OutResult) const;` — Ensure the variable and data tables have the allocations for our referenced camera rig.
- L288 _public prototype_ `void ApplyParameterOverrides(UE::Cameras::FCameraVariableTable& OutVariableTable, bool bDrivenOnly) const;` — Applies the parameter override values to the given variable table.
- L291 _public prototype_ `void ApplyParameterOverrides(UE::Cameras::FCameraVariableTable& OutVariableTable, UE::Cameras::FCameraContextDataTable& OutContextDataTable, bool bDrivenOnly) const;` — Applies the parameter override values to the given variable and context data tables.
- L294 _public prototype_ `void ApplyParameterOverrides(UE::Cameras::FCameraNodeEvaluationResult& OutResult, bool bDrivenOnly) const;` — Applies the parameter override values to the given evaluation result.
- L297 _public prototype_ `void ApplyParameterOverridesAndDefaults(UE::Cameras::FCameraNodeEvaluationResult& OutResult) const;` — Applies the parameter override values, or the default value if not overriden, to the given evaluation result.
- L301 _private prototype_ `void ApplyParameterOverridesImpl(UE::Cameras::FCameraVariableTable* OutVariableTable, UE::Cameras::FCameraContextDataTable* OutContextDataTable, bool bDrivenOnly, bool bApplyUnwrittenDefaults) const;`
- L306 _public prototype_ `virtual const UBaseCameraObject* GetCameraObject() const override;` — FBaseCameraObjectReference interface.
- L310 _public prototype_ `bool SerializeFromMismatchedTag(FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);`
- L311 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L317 _private member_ `TObjectPtr<UCameraRigAsset> CameraRig;` — `UPROPERTY(EditAnywhere, Category="")` — The referenced camera rig.
- L323 _private member_ `TArray<FGuid> ParameterOverrideGuids_DEPRECATED;` — `UPROPERTY()`
- L328 _private member_ `FCameraRigParameterOverrides ParameterOverrides_DEPRECATED;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraRigAssetReference> : public TStructOpsTypeTraits<FBaseCameraObjectReference>`  
_L336-343_
- inherits: `TStructOpsTypeTraits<FBaseCameraObjectReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L339-342_

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Cameras` (scope `UE`)
- L340 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonb101aa3e0103`)
- L341 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonb101aa3e0103`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigEvaluationInfo.h` (Public)


#### struct `UE::Cameras::FCameraRigEvaluationInfo`  
`struct FCameraRigEvaluationInfo`  
_L24-52_
- desc: A structure describing an active camera rig being evaluated, generally inside a blend stack.
- L27 _public member_ `FCameraRigInstanceID InstanceID;` — The instance ID of this camera rig.
- L29 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The context inside which the evaluation occurs.
- L31 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The camera rig being evaluated.
- L33 _public member_ `const FCameraNodeEvaluationResult* LastResult = nullptr;` — The last evaluated result for this camera rig.
- L35 _public member_ `FCameraNodeEvaluator* RootEvaluator = nullptr;` — The root node evaluator of the camera rig.
- L37 _public function_ `FCameraRigEvaluationInfo()`
- L40 _public function_ `FCameraRigEvaluationInfo( FCameraRigInstanceID InInstanceID, TSharedPtr<const FCameraEvaluationContext> InEvaluationContext, TObjectPtr<const UCameraRigAsset> InCameraRig, const FCameraNodeEvaluationResult* InLastResult, FCameraNodeEvaluator* InRootEvaluator) : InstanceID(InInstanceID) , EvaluationContext(InEvaluationContext) , CameraRig(InCameraRig) , LastResult(InLastResult) , RootEvaluator(InRootEvaluator)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigInstanceID.h` (Public)


#### enum `ECameraRigLayer`  
`enum class ECameraRigLayer : uint8`  
_L15-22_
- reflection: `UENUM(BlueprintType)`
- desc: Defines evaluation layers for camera rigs.
- L17 _public enumerator_ `None UMETA(Hidden)`
- L18 _public enumerator_ `Base UMETA(DisplayName="Base Layer")`
- L19 _public enumerator_ `Main UMETA(DisplayName="Main Layer")`
- L20 _public enumerator_ `Global UMETA(DisplayName="Global Layer")`
- L21 _public enumerator_ `Visual UMETA(DisplayName="Visual Layer")`

#### struct `FCameraRigInstanceID`  
`struct FCameraRigInstanceID`  
_L29-100_
- reflection: `USTRUCT(BlueprintType)`
- desc: A unique instance ID for a running, or previously running, camera rig.
- L35 _public function_ `FCameraRigInstanceID() : Value(INVALID), Layer(ECameraRigLayer::None)`
- L37 _public function_ `bool IsValid() const`
- L39 _public function_ `explicit operator bool() const`
- L68 _public function_ `ECameraRigLayer GetLayer() const` — Gets the layer this camera rig is, or was, running on.
- L71 _public function_ `UE::Cameras::FBlendStackEntryID ToBlendStackEntryID() const` — Gets a blend stack ID from this instance ID.
- L74 _public function_ `static FCameraRigInstanceID FromBlendStackEntryID(UE::Cameras::FBlendStackEntryID EntryID, ECameraRigLayer Layer)` — Creates an instance ID from a blend stack ID and a layer.
- L81 _private function_ `FCameraRigInstanceID(uint32 InValue, ECameraRigLayer InLayer) : Value(InValue) , Layer(InLayer)`
- L86 _private function_ `FCameraRigInstanceID(const UE::Cameras::FBlendStackEntryID InBlendStackID, ECameraRigLayer InLayer) : Value(InBlendStackID.Value) , Layer(InLayer)`
- L91 _private member_ `static const uint32 INVALID = uint32(-1);`
- L94 _private member_ `uint32 Value;` — `UPROPERTY()`
- L97 _private member_ `ECameraRigLayer Layer;` — `UPROPERTY()`

#### class `UCameraRigInstanceFunctions`  
`class UCameraRigInstanceFunctions : public UBlueprintFunctionLibrary`  
_L106-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint functions for camera rig instance IDs.
- L117 _public function_ `static bool IsValid(FCameraRigInstanceID InstanceID)` — `UFUNCTION(BlueprintPure, Category="Camera")` — Whether the given camera rig instance ID is valid. A valid ID doesn't necessarily correspond to a camera rig instance that is still running.

#### Free symbols / members of external scopes

- L43 _function_ `friend bool operator==(FCameraRigInstanceID A, FCameraRigInstanceID B)`
- L48 _function_ `friend bool operator!=(FCameraRigInstanceID A, FCameraRigInstanceID B)`
- L53 _function_ `friend uint32 GetTypeHash(FCameraRigInstanceID In)`
- L58 _function_ `friend FArchive& operator<< (FArchive& Ar, FCameraRigInstanceID& In)`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigJoints.h` (Public)


#### struct `UE::Cameras::FCameraRigJoint`  
`struct FCameraRigJoint`  
_L18-24_
- desc: A structure describing a joint in a camera rig.
- L21 _public member_ `FCameraVariableID VariableID;` — The variable driving the rotation of this joint.
- L23 _public member_ `FTransform3d Transform;` — The position of the this joint.

#### class `UE::Cameras::FCameraRigJoints`  
`class FCameraRigJoints`  
_L33-64_
- desc: A structure describing the joints of a camera rig. These joints allow for "manipulating" the rig, e.g. to make it point towards a desired target or direction.
- L38 _public prototype_ `void AddJoint(const FCameraRigJoint& InJoint);` — Add a joint.
- L40 _public prototype_ `void AddJoint(const FCameraVariableDefinition& InVariableDefinition, const FTransform3d& InTransform);` — Add a joint.
- L42 _public prototype_ `void AddYawPitchJoint(const FTransform3d& InTransform);` — Add a joint related to the yaw/pitch built-in variable.
- L45 _public function_ `TArrayView<const FCameraRigJoint> GetJoints() const` — Gets the joints.
- L48 _public prototype_ `void Reset();` — Removes all previously added joints.
- L50 _public prototype_ `void Serialize(FArchive& Ar);`
- L55 _public prototype_ `void OverrideAll(const FCameraRigJoints& OtherJoints);` — Override the joints with another set of joints.
- L58 _public prototype_ `void LerpAll(const FCameraRigJoints& ToJoints, float BlendFactor);` — Interpolate the joints towards anoter set of joints.
- L62 _private typedef_ `using FJointArray = TArray<FCameraRigJoint, TInlineAllocator<2>>;`
- L63 _private member_ `FJointArray Joints;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)
- L26 _prototype_ `FArchive& operator<< (FArchive& Ar, FCameraRigJoint& RigJoint);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigProxyAsset.h` (Public)


#### class `UCameraRigProxyAsset`  
`class UCameraRigProxyAsset : public UObject`  
_L18-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A proxy for a camera rig asset. This is useful for indicating that a camera rig should be activated in a camera director, but without hard-referencing a particular camera rig. This way, that camera director can be used by multiple cameras with their own camera rigs.
- L25 _public function_ `const FGuid& GetGuid() const` — Gets the camera rig proxy's unique ID.
- L28 _public prototype_ `virtual void PostLoad() override;` — UObject interface.
- L29 _public prototype_ `virtual void PostInitProperties() override;`
- L30 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L36 _private member_ `FGuid Guid;` — `UPROPERTY()` — The camera rig proxy's unique ID.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigProxyRedirectTable.h` (Public)


#### struct `FCameraRigProxyResolveParams`  
`struct FCameraRigProxyResolveParams`  
_L16-20_
- desc: Parameter structure for resolving a camera rig proxy from a proxy table.
- L19 _public member_ `const UCameraRigProxyAsset* CameraRigProxy = nullptr;` — The camera rig proxy to resolve.

#### struct `FCameraRigProxyRedirectTableEntry`  
`struct FCameraRigProxyRedirectTableEntry`  
_L26-37_
- reflection: `USTRUCT()`
- desc: An entry in a camera rig proxy table.
- L32 _public member_ `TObjectPtr<UCameraRigProxyAsset> CameraRigProxy;` — `UPROPERTY(EditAnywhere, Category="Camera")` — The camera rig proxy for this table entry.
- L36 _public member_ `TObjectPtr<UCameraRigAsset> CameraRig;` — `UPROPERTY(EditAnywhere, Category="Camera")` — The actual camera rig that should be mapped to the correspondig proxy.

#### struct `FCameraRigProxyRedirectTable`  
`struct FCameraRigProxyRedirectTable`  
_L43-66_
- reflection: `USTRUCT()`
- desc: A table that defines mappings between camera rig proxies and actual camera rigs.
- L53 _public prototype_ `UCameraRigAsset* ResolveProxy(const FCameraRigProxyResolveParams& InParams) const;` — Resolves a given proxy to an actual camera rig. Returns nullptr if the given proxy wasn't found, or not mapped to anything in the table.
- L59 _public prototype_ `bool SerializeFromMismatchedTag(FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);`
- L65 _public member_ `TArray<FCameraRigProxyRedirectTableEntry> Entries;` — `UPROPERTY(EditAnywhere, Category="Camera")` — The entries in the table.

#### class `UCameraRigProxyTable`  
`class UE_DEPRECATED(5.6, "Use FCameraRigProxyRedirectTable") UCameraRigProxyTable : public UObject`  
_L69-77_
- reflection: `UCLASS()`
- inherits: `UObject`
- L76 _public member_ `TArray<FCameraRigProxyRedirectTableEntry> Entries;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraRigTransition.h` (Public)


#### struct `FCameraRigTransitionConditionMatchParams`  
`struct FCameraRigTransitionConditionMatchParams`  
_L28-43_
- desc: Parameter structure for camera transitions.
- L31 _public member_ `TSharedPtr<const UE::Cameras::FCameraEvaluationContext> FromEvaluationContext;` — The evaluation context of the previous camera rig.
- L33 _public member_ `const UCameraRigAsset* FromCameraRig = nullptr;` — The previous camera rig.
- L35 _public member_ `const UCameraAsset* FromCameraAsset = nullptr;` — The previous camera asset.
- L38 _public member_ `TSharedPtr<const UE::Cameras::FCameraEvaluationContext> ToEvaluationContext;` — The evaluation context of the next camera rig.
- L40 _public member_ `const UCameraRigAsset* ToCameraRig = nullptr;` — The next camera rig.
- L42 _public member_ `const UCameraAsset* ToCameraAsset = nullptr;` — The next camera asset.

#### class `UCameraRigTransitionCondition`  
`class UCameraRigTransitionCondition : public UObject , public IObjectTreeGraphObject`  
_L52-111_
- reflection: `UCLASS(MinimalAPI, Abstract, DefaultToInstanced, meta=( ObjectTreeGraphCategory="Transition Conditions", ObjectTreeGraphSelfPinDirection="Output", ObjectTreeGraphDefaultPropertyPinDirection="Input"))`
- inherits: `UObject,IObjectTreeGraphObject`
- desc: Base class for a camera transition condition.
- L60 _public typedef_ `using FCameraObjectBuildContext = UE::Cameras::FCameraObjectBuildContext;`
- L63 _public prototype_ `bool TransitionMatches(const FCameraRigTransitionConditionMatchParams& Params) const;` — Evaluates whether this transition should be used.
- L66 _public prototype_ `void Build(FCameraObjectBuildContext& BuildContext);` — Build process callback for this transition.
- L71 _protected function_ `virtual bool OnTransitionMatches(const FCameraRigTransitionConditionMatchParams& Params) const` — Evaluates whether this transition should be used.
- L74 _protected function_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext)` — Build process callback for this transition.
- L79 _protected prototype_ `virtual void PostLoad() override;` — UObject interface.
- L83 _protected prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;`
- L84 _protected prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`
- L85 _protected function_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override`
- L86 _protected prototype_ `virtual const FString& GetGraphNodeCommentText(FName InGraphName) const override;`
- L87 _protected prototype_ `virtual void OnUpdateGraphNodeCommentText(FName InGraphName, const FString& NewComment) override;`
- L96 _private member_ `FIntVector2 GraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the transition condition node in the transition graph editor.
- L100 _private member_ `FString GraphNodeComment;` — `UPROPERTY()` — User-written comment in the transition graph editor.
- L106 _private member_ `int32 GraphNodePosX_DEPRECATED = 0;` — `UPROPERTY()`
- L108 _private member_ `int32 GraphNodePosY_DEPRECATED = 0;` — `UPROPERTY()`

#### enum `ECameraRigInitialOrientation`  
`enum class ECameraRigInitialOrientation`  
_L117-136_
- reflection: `UENUM()`
- desc: Determines how a camera rig's initial orientation should be initialized.
- L120 _public enumerator_ `None` — Leave the camera rig to its default orientation.
- L122 _public enumerator_ `ContextYawPitch` — Orient the camera rig in the same direction as its context's initial transform.
- L124 _public enumerator_ `PreviousYawPitch` — Orient the camera rig in the same direction as the previously active camera rig.
- L129 _public enumerator_ `PreviousAbsoluteTarget` — Make the camera rig point at the same target as the previously active camera rig's last frame target.
- L135 _public enumerator_ `PreviousRelativeTarget` — Make the camera rig point at the same target as the previously active camera rig. Last frame's target will be moved and turned by an offset equal to how much the active evaluation context has moved and turned since last frame.

#### class `UCameraRigTransition`  
`class UCameraRigTransition : public UObject , public IObjectTreeGraphObject`  
_L142-225_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IObjectTreeGraphObject`
- desc: A camera transition.
- L152 _public member_ `TArray<TObjectPtr<UCameraRigTransitionCondition>> Conditions;` — `UPROPERTY(Instanced, meta=(ObjectTreeGraphPinDirection=Input))` — The list of conditions that must pass for this transition to be used.
- L156 _public member_ `TObjectPtr<UBlendCameraNode> Blend;` — `UPROPERTY(Instanced)` — The blend to use to blend a given camera rig in or out.
- L160 _public member_ `ECameraRigInitialOrientation InitialOrientation = ECameraRigInitialOrientation::None;` — `UPROPERTY(EditAnywhere, Category="Transition", meta=(EditCondition="bOverrideInitialOrientation"))` — The orientation to set on the camera rig.
- L164 _public member_ `bool bOverrideInitialOrientation = false;` — `UPROPERTY(EditAnywhere, Category="Transition")` — Whether to override the default orientation to set on the camera rig.
- L168 _public member_ `bool bFreezePreviousCameraRigs = false;` — `UPROPERTY(EditAnywhere, Category="Transition")` — Freeze all previously running camera rigs.
- L178 _public member_ `bool bAllowCameraRigMerging = false;` — `UPROPERTY(EditAnywhere, Category="Advanced")` — Whether this transition allows merging two similar camera rigs together. Similar camera rigs run the same underlying camera rig prefab with different parameter overrides. When merged, instead of pushing a new camera rig instance on the blend stack, only the parameter overrides are kept. These parameter overrides are blended together and the underlying camera rig prefab is run only once.
- L182 _public typedef_ `using FCameraObjectBuildContext = UE::Cameras::FCameraObjectBuildContext;`
- L185 _public prototype_ `bool AllConditionsMatch(const FCameraRigTransitionConditionMatchParams& Params) const;` — Returns whether all transition condition matches the given parameters.
- L188 _public prototype_ `void Build(FCameraObjectBuildContext& BuildContext);` — Build process callback for this transition.
- L193 _protected prototype_ `virtual void PostLoad() override;` — UObject interface.
- L197 _protected prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;`
- L198 _protected prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`
- L199 _protected function_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override`
- L200 _protected prototype_ `virtual const FString& GetGraphNodeCommentText(FName InGraphName) const override;`
- L201 _protected prototype_ `virtual void OnUpdateGraphNodeCommentText(FName InGraphName, const FString& NewComment) override;`
- L210 _private member_ `FIntVector2 GraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the transition node in the transition graph editor.
- L214 _private member_ `FString GraphNodeComment;` — `UPROPERTY()` — User-written comment in the transition graph editor.
- L220 _private member_ `int32 GraphNodePosX_DEPRECATED = 0;` — `UPROPERTY()`
- L222 _private member_ `int32 GraphNodePosY_DEPRECATED = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraShakeAsset.h` (Public)


#### class `UCameraShakeAsset`  
`class UCameraShakeAsset : public UBaseCameraObject , public IHasCameraBuildStatus , public IObjectTreeGraphObject , public IObjectTreeGraphRootObject`  
_L23-118_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBaseCameraObject,IHasCameraBuildStatus,IObjectTreeGraphObject,IObjectTreeGraphRootObject`
- L35 _public member_ `TObjectPtr<UShakeCameraNode> RootNode;` — `UPROPERTY(Instanced)` — Root camera node.
- L39 _public member_ `TObjectPtr<USimpleFixedTimeBlendCameraNode> BlendIn;` — `UPROPERTY(Instanced)` — The blend to use for easing into the shake.
- L43 _public member_ `TObjectPtr<USimpleFixedTimeBlendCameraNode> BlendOut;` — `UPROPERTY(Instanced)` — The blend to use for easing out of the shake.
- L50 _public member_ `bool bIsSingleInstance = false;` — `UPROPERTY(EditAnywhere, Category="Common")` — Whether only one instance of this shake can be started via the camera shake functions. Note that this doesn't prevent this shake from being used "inline" inside a camera rig.
- L56 _public member_ `ECameraBuildStatus BuildStatus = ECameraBuildStatus::Dirty;` — `UPROPERTY(Transient)` — The current build state of this camera shake.
- L59 _public prototype_ `void BuildCameraShake();` — Builds this camera shake asset.
- L62 _public prototype_ `void BuildCameraShake(UE::Cameras::FCameraBuildContext& InBuildContext);` — Builds this camera shake asset.
- L67 _public prototype_ `virtual UCameraNode* GetRootNode() override;` — BaseCameraObject interface.
- L70 _public function_ `virtual ECameraBuildStatus GetBuildStatus() const override` — IHasCameraBuildStatus interface.
- L71 _public prototype_ `virtual void DirtyBuildStatus() override;`
- L77 _protected prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;`
- L78 _protected prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`
- L79 _protected prototype_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override;`
- L80 _protected prototype_ `virtual const FString& GetGraphNodeCommentText(FName InGraphName) const override;`
- L81 _protected prototype_ `virtual void OnUpdateGraphNodeCommentText(FName InGraphName, const FString& NewComment) override;`
- L82 _protected prototype_ `virtual void GetGraphNodeName(FName InGraphName, FText& OutName) const override;`
- L87 _protected prototype_ `virtual void GetConnectableObjects(FName InGraphName, TSet<UObject*>& OutObjects) const override;`
- L88 _protected prototype_ `virtual void AddConnectableObject(FName InGraphName, UObject* InObject) override;`
- L89 _protected prototype_ `virtual void RemoveConnectableObject(FName InGraphName, UObject* InObject) override;`
- L93 _protected prototype_ `virtual void PostLoad() override;` — UObject interface.
- L94 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L102 _private member_ `FIntVector2 GraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the camera shake node in the node graph editor.
- L106 _private member_ `FString GraphNodeComment;` — `UPROPERTY()` — User-written comment in the node graph editor.
- L113 _private member_ `TArray<TObjectPtr<UObject>> AllNodeObjects;` — `UPROPERTY(Instanced, meta=(ObjectTreeGraphHidden=true))` — A list of all the camera nodes, including the 'loose' ones that aren't connected to the root node, and therefore would be GC'ed if we didn't hold them here.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraShakeAssetReference.h` (Public)


#### struct `FCameraShakeAssetReference`  
`struct FCameraShakeAssetReference : public FBaseCameraObjectReference`  
_L27-97_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FBaseCameraObjectReference`
- desc: A structure holding a reference to a camera shake asset, along with the interface parameter override values.
- L33 _public prototype_ `FCameraShakeAssetReference();`
- L34 _public prototype_ `FCameraShakeAssetReference(UCameraShakeAsset* InCameraShake);`
- L37 _public function_ `bool IsValid() const` — Returns whether this reference points to a valid camera shake.
- L43 _public function_ `UCameraShakeAsset* GetCameraShake()` — Gets the referenced camera shake.
- L49 _public function_ `const UCameraShakeAsset* GetCameraShake() const` — Gets the referenced camera shake.
- L55 _public function_ `void SetCameraShake(UCameraShakeAsset* InCameraShake)` — Sets the referenced camera shake.
- L67 _public prototype_ `void EnsureAllocationInfo(UE::Cameras::FCameraNodeEvaluationResult& OutResult) const;` — Ensure the variable and data tables have the allocations for our referenced camera shake.
- L70 _public prototype_ `void ApplyParameterOverrides(UE::Cameras::FCameraVariableTable& OutVariableTable, bool bDrivenOnly) const;` — Applies the parameter override values to the given variable table.
- L73 _public prototype_ `void ApplyParameterOverrides(UE::Cameras::FCameraVariableTable& OutVariableTable, UE::Cameras::FCameraContextDataTable& OutContextDataTable, bool bDrivenOnly) const;` — Applies the parameter override values to the given variable and context data tables..
- L76 _public prototype_ `void ApplyParameterOverrides(UE::Cameras::FCameraNodeEvaluationResult& OutResult, bool bDrivenOnly) const;` — Applies the parameter override values to the given evaluation result.
- L79 _public prototype_ `void ApplyParameterOverridesAndDefaults(UE::Cameras::FCameraNodeEvaluationResult& OutResult) const;` — Applies the parameter override values, or the default value if not overriden, to the given evaluation result.
- L83 _private prototype_ `void ApplyParameterOverridesImpl(UE::Cameras::FCameraVariableTable* OutVariableTable, UE::Cameras::FCameraContextDataTable* OutContextDataTable, bool bDrivenOnly, bool bApplyUnwrittenDefaults) const;`
- L88 _public prototype_ `virtual const UBaseCameraObject* GetCameraObject() const override;` — FBaseCameraObjectReference interface.
- L94 _private member_ `TObjectPtr<UCameraShakeAsset> CameraShake;` — `UPROPERTY(EditAnywhere, Category="")` — The referenced camera shake.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraShakeAssetReference> : public TStructOpsTypeTraits<FBaseCameraObjectReference>`  
_L100-102_
- inherits: `TStructOpsTypeTraits<FBaseCameraObjectReference>`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraShakeInstanceID.h` (Public)


#### struct `FCameraShakeInstanceID`  
`struct FCameraShakeInstanceID`  
_L14-59_
- reflection: `USTRUCT(BlueprintType)`
- desc: A unique instance ID for a running, or previously running, camera shake.
- L20 _public function_ `FCameraShakeInstanceID() : Value(INVALID)`
- L22 _public function_ `FCameraShakeInstanceID(uint32 InValue) : Value(InValue)`
- L26 _public function_ `bool IsValid() const`
- L28 _public function_ `explicit operator bool() const`
- L55 _private member_ `static const uint32 INVALID = uint32(-1);`
- L58 _private member_ `uint32 Value;` — `UPROPERTY()`

#### class `UCameraShakeInstanceFunctionLibrary`  
`class UCameraShakeInstanceFunctionLibrary : public UBlueprintFunctionLibrary`  
_L65-81_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for camera shake instance IDs.
- L77 _public function_ `static bool IsValid(const FCameraShakeInstanceID CameraShakeInstanceID)` — `UFUNCTION(BlueprintPure, Category="Camera Shake", meta=(DisplayName="Is Valid Camera Shake Instance ID"))` — Returns whether a camera shake instance ID is valid. Note that this doesn't check if the associated camera shake is still running.

#### Free symbols / members of external scopes

- L32 _function_ `friend bool operator==(FCameraShakeInstanceID A, FCameraShakeInstanceID B)`
- L37 _function_ `friend bool operator!=(FCameraShakeInstanceID A, FCameraShakeInstanceID B)`
- L42 _function_ `friend uint32 GetTypeHash(FCameraShakeInstanceID In)`
- L47 _function_ `friend FArchive& operator<< (FArchive& Ar, FCameraShakeInstanceID& In)`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraSystemEvaluator.h` (Public)


#### enum `UE::Cameras::ECameraSystemEvaluatorRole`  
`enum class ECameraSystemEvaluatorRole`  
_L46-53_
- desc: An enumeration that describes what a camera system evaluator is used for.
- L48 _public enumerator_ `Game`
- L51 _public enumerator_ `EditorPreview #endif`

#### struct `UE::Cameras::FCameraSystemEvaluatorCreateParams`  
`struct FCameraSystemEvaluatorCreateParams`  
_L58-69_
- desc: Parameter structure for initializing a new camera system evaluator.
- L61 _public member_ `TObjectPtr<UObject> Owner;` — The owner of the camera system, if any.
- L64 _public member_ `ECameraSystemEvaluatorRole Role = ECameraSystemEvaluatorRole::Game;` — The role of the camera system.
- L67 _public typedef_ `using FRootNodeFactory = TFunction<URootCameraNode*()>;` — An optional factory for creating the root node.
- L68 _public member_ `FRootNodeFactory RootNodeFactory;`

#### struct `UE::Cameras::FCameraSystemEvaluationParams`  
`struct FCameraSystemEvaluationParams`  
_L74-78_
- desc: Parameter structure for updating the camera system.
- L77 _public member_ `float DeltaTime = 0.f;` — Time interval for the update.

#### struct `UE::Cameras::FCameraSystemEvaluationResult`  
`struct FCameraSystemEvaluationResult`  
_L83-110_
- desc: Result structure for updating the camera system.
- L86 _public member_ `FCameraPose CameraPose;` — The result camera pose.
- L89 _public member_ `FCameraVariableTable VariableTable;` — The result camera variable table.
- L92 _public member_ `FCameraContextDataTable ContextDataTable;` — The result camera context data table.
- L95 _public member_ `FPostProcessSettingsCollection PostProcessSettings;` — The result post-process settings.
- L98 _public member_ `bool bIsCameraCut = false;` — Whether this evaluation was a camera cut.
- L101 _public member_ `bool bIsValid = false;` — Whether this result is valid.
- L106 _public prototype_ `void Reset();` — Reset this result to its default (non-valid) state.
- L109 _public prototype_ `void Reset(const FCameraNodeEvaluationResult& NodeResult);` — Set this result to be equivalent to the given evaluation result.

#### struct `UE::Cameras::FCameraSystemViewRotationEvaluationResult`  
`struct FCameraSystemViewRotationEvaluationResult`  
_L115-122_
- desc: Result structure for view rotation updates of the camera system.
- L118 _public member_ `FRotator ViewRotation;` — View rotation for the player.
- L121 _public member_ `FRotator DeltaRotation;` — Control rotation for the player.

#### struct `UE::Cameras::FCameraSystemDebugUpdateParams`  
`struct FCameraSystemDebugUpdateParams`  
_L129-145_
- desc: Parameter structure for running the debug pass of the camera system.
- L132 _public member_ `UCanvas* CanvasObject = nullptr;` — The canvas to draw upon.
- L135 _public member_ `bool bIsDebugCameraEnabled = false;` — Whether the debug camera is enabled, giving an "outside" view of camera system.
- L141 _public member_ `bool bIsDefaultCameraSystem = false;` — Whether this camera system should be considered the "default" one, such as when running inside the active camera manager or the view target.
- L144 _public member_ `bool bForceDraw = false;` — Whether to force drawing debug info for this camera system.

#### struct `UE::Cameras::FCameraSystemEditorPreviewParams`  
`struct FCameraSystemEditorPreviewParams`  
_L154-174_
- desc: Parameter structure for rendering the state of the camera system in editor.
- L157 _public member_ `FCanvas* Canvas = nullptr;` — The canvas to draw upon.
- L160 _public member_ `const FSceneView* SceneView = nullptr;` — The scene view being renderered.
- L168 _public member_ `bool bIsLockedToCamera = true;` — Whether debug drawing is done from "inside" the camera system. When false, it is acceptable to draw camera frustrums and axes. When true, these things shouldn't be drawn as they would clutter the view and obfuscate the scene.
- L173 _public member_ `bool bDrawWorldDebug = true;` — Whether to enable drawing debug lines and other 3D primitives in the world.

#### class `UE::Cameras::FCameraSystemEvaluator`  
`class FCameraSystemEvaluator : public TSharedFromThis<FCameraSystemEvaluator>`  
_L181-364_
- inherits: `TSharedFromThis<FCameraSystemEvaluator>`
- desc: The main camera system evaluator class.
- L186 _public prototype_ `FCameraSystemEvaluator();` — Builds a new camera system. Initialize must be called before the system is used.
- L189 _public prototype_ `void Initialize(TObjectPtr<UObject> InOwner = nullptr);` — Initializes the camera system.
- L191 _public prototype_ `void Initialize(const FCameraSystemEvaluatorCreateParams& Params);` — Initializes the camera system.
- L193 _public prototype_ `~FCameraSystemEvaluator();`
- L198 _public function_ `UObject* GetOwner() const` — Gets the owner of this camera system, if any, and if still valid.
- L201 _public function_ `ECameraSystemEvaluatorRole GetRole() const` — Gets the role of this camera system.
- L205 _public function_ `FCameraSystemDebugID GetDebugID() const` — Gets the debug ID for this camera system.
- L211 _public prototype_ `void PushEvaluationContext(TSharedRef<FCameraEvaluationContext> EvaluationContext);` — Push a new evaluation context on the stack.
- L213 _public prototype_ `void RemoveEvaluationContext(TSharedRef<FCameraEvaluationContext> EvaluationContext);` — Remove an existing evaluation context from the stack.
- L215 _public prototype_ `void PopEvaluationContext();` — Pop the active (top) evaluation context from the stack.
- L218 _public function_ `FCameraEvaluationContextStack& GetEvaluationContextStack()` — Gets the context stack.
- L220 _public function_ `const FCameraEvaluationContextStack& GetEvaluationContextStack() const` — Gets the context stack.
- L225 _public prototype_ `void RegisterEvaluationService(TSharedRef<FCameraEvaluationService> EvaluationService);` — Registers an evaluation service on this camera system.
- L227 _public prototype_ `void UnregisterEvaluationService(TSharedRef<FCameraEvaluationService> EvaluationService);` — Unregisters an evaluation service from this camera system.
- L229 _public prototype_ `void GetEvaluationServices(TArray<TSharedPtr<FCameraEvaluationService>>& OutEvaluationServices) const;` — Get currently registered evaluation services.
- L232 _public prototype_ `TSharedPtr<FCameraEvaluationService> FindEvaluationService(const FCameraObjectTypeID& TypeID) const;` — Finds an evaluation service of the given type.
- L236 _public function_ `template<typename EvaluationServiceType> TSharedPtr<EvaluationServiceType> FindEvaluationService() const` — Finds an evaluation service of the given type.
- L248 _public function_ `template<typename EvaluationServiceType> TSharedRef<EvaluationServiceType> FindOrRegisterEvaluationService()` — Finds or creates/registers an evaluation service of the given type.
- L262 _public prototype_ `void Update(const FCameraSystemEvaluationParams& Params);` — Run an update of the camera system.
- L265 _public prototype_ `void ViewRotationPreviewUpdate(const FCameraSystemEvaluationParams& Params, FCameraSystemViewRotationEvaluationResult& OutResult);` — Run a view rotation preview update of the camera system.
- L268 _public function_ `FRootCameraNodeEvaluator* GetRootNodeEvaluator() const` — Returns the root node evaluator.
- L271 _public function_ `const FCameraSystemEvaluationResult& GetEvaluatedResult() const` — Gets the evaluated result.
- L274 _public function_ `const FCameraSystemEvaluationResult& GetPreVisualLayerEvaluatedResult() const` — Gets the evaluated result without the contribution of the visual layer.
- L277 _public prototype_ `void GetEvaluatedCameraView(FMinimalViewInfo& DesiredView);` — Get the last evaluated camera.
- L280 _public prototype_ `void ExecuteOperation(FCameraOperation& Operation);` — Executes an operation, to be dispatched by the root node evaluator.
- L283 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collect reference objects for the garbage collector.
- L287 _public prototype_ `void EditorPreviewUpdate(const FCameraSystemEvaluationParams& Params);` — Run an update suitable for an in-editor preview.
- L290 _public prototype_ `void DrawEditorPreview(const FCameraSystemEditorPreviewParams& Params);` — Render information about the state of the camera system in-editor.
- L294 _public prototype_ `void DebugUpdate(const FCameraSystemDebugUpdateParams& Params);`
- L299 _private prototype_ `void UpdateImpl(float DeltaTime, ECameraNodeEvaluationType EvaluationType);`
- L301 _private prototype_ `void UpdateCameraDirector(float DeltaTime, FCameraDirectorEvaluator* CameraDirectorEvaluator);`
- L302 _private prototype_ `void GetCombinedCameraRigRequest(TConstArrayView<FCameraRigActivationDeactivationRequest> Requests, FCameraRigActivationDeactivationRequest& OutCombinedRequest);`
- L304 _private prototype_ `void PreUpdateServices(float DeltaTime, ECameraNodeEvaluationType EvaluationType);`
- L305 _private prototype_ `void PostCameraDirectorUpdateServices(float DeltaTime, ECameraNodeEvaluationType EvaluationType);`
- L306 _private prototype_ `void PostUpdateServices(float DeltaTime, ECameraNodeEvaluationType EvaluationType);`
- L309 _private prototype_ `static bool IsDebugTraceEnabled();`
- L310 _private prototype_ `static bool ShouldBuildOrDrawDebugBlocks();`
- L311 _private prototype_ `void BuildDebugBlocksIfNeeded();`
- L317 _private member_ `TWeakObjectPtr<> WeakOwner;` — The owner (if any) of this camera system evaluator.
- L320 _private member_ `TObjectPtr<URootCameraNode> RootNode;` — The root camera node.
- L323 _private member_ `FCameraEvaluationContextStack ContextStack;` — The stack of active evaluation context.
- L326 _private member_ `TArray<TSharedPtr<FCameraEvaluationService>> EvaluationServices;` — The list of evaluation services.
- L329 _private member_ `TSharedPtr<FCameraRigCombinationRegistry> CameraRigCombinationRegistry;` — Registry for programmatically building combinations of camera rigs.
- L332 _private member_ `FCameraNodeEvaluatorStorage RootEvaluatorStorage;` — Storage buffer for the root evaluator.
- L335 _private member_ `FRootCameraNodeEvaluator* RootEvaluator = nullptr;` — The root evaluator.
- L338 _private member_ `FCameraNodeEvaluationResult RootNodeResult;` — The current result of the root camera node.
- L341 _private member_ `FCameraSystemEvaluationResult Result;` — The current overall result of the camera system.
- L344 _private member_ `FCameraSystemEvaluationResult PreVisualResult;` — The current overall result of the camera system without the contribution of the visual layer.
- L347 _private member_ `TArray<uint8> EvaluatorSnapshot;` — Reusable buffer for node tree snapshots (e.g. view rotation preview update).
- L350 _private member_ `ECameraSystemEvaluatorRole Role = ECameraSystemEvaluatorRole::Game;` — The role of this camera system.
- L354 _private member_ `FCameraSystemDebugID DebugID;` — The debug ID for this camera system.
- L357 _private member_ `FCameraDebugBlockStorage DebugBlockStorage;` — Storage for debug drawing blocks.
- L360 _private member_ `FRootCameraDebugBlock* RootDebugBlock = nullptr;` — The root debug drawing block.

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraValueInterpolator.h` (Public)


#### struct `UE::Cameras::FCameraValueInterpolationParams`  
`struct FCameraValueInterpolationParams`  
_L23-27_
- desc: Parameter structure for updating a value interpolator.
- L25 _public member_ `float DeltaTime = 0.f;`
- L26 _public member_ `bool bIsCameraCut = false;`

#### struct `UE::Cameras::FCameraValueInterpolationResult`  
`struct FCameraValueInterpolationResult`  
_L32-39_
- desc: Result structure for updating a value interpolator.
- L34 _public function_ `FCameraValueInterpolationResult(FCameraVariableTable& InVariableTable) : VariableTable(InVariableTable)`
- L38 _public member_ `FCameraVariableTable& VariableTable;`

#### struct `UE::Cameras::FCameraValueInterpolatorSerializeParams`  
`struct FCameraValueInterpolatorSerializeParams`  
_L44-46_
- desc: Parameter structure for serializing a value interpolator.

#### class `UE::Cameras::TCameraValueInterpolator`  
`template<typename ValueType> class TCameraValueInterpolator`  
_L54-138_
- desc: A value interpolator is a stand-alone object that can interpolate a given value towards a given target value. Various sub-classes of this base class should implement various interpolation algorithms.
- L58 _public typedef_ `using ValueTypeParam = typename TCallTraits<ValueType>::ParamType;`
- L64 _public function_ `TCameraValueInterpolator(const UCameraValueInterpolator* InParameters) : Parameters(InParameters) , CurrentValue(ValueType()) , TargetValue(ValueType()) , bIsFinished(false)` — Creates a new value interpolator given a piece of data containing user-defined settings.
- L72 _public prototype_ `virtual ~TCameraValueInterpolator() = default;` — Destructor
- L76 _public function_ `template<typename TInterpolatorClass> const TInterpolatorClass* GetParametersAs() const` — Gets the parameters class and casts it to the given sub-class.
- L79 _public function_ `ValueType GetCurrentValue() const` — Gets the current value.
- L82 _public function_ `ValueType GetTargetValue() const` — Gets the target value.
- L89 _public function_ `bool IsFinished() const` — Returns whether the interpolation has ended. The current value may not be equal to the target value if for some reason the implemented interpolation algorithm cannot reach the target value.
- L92 _public function_ `void Reset(ValueTypeParam NewCurrentValue, ValueTypeParam NewTargetValue)` — Resets the current and target values.
- L104 _public function_ `ValueType Run(const FCameraValueInterpolationParams& Params, FCameraValueInterpolationResult& OutResult)` — Evaluates the interpolator, advancing the current value towards the target.
- L114 _public function_ `void Serialize(const FCameraValueInterpolatorSerializeParams& Params, FArchive& Ar)` — Serializes the value interpolator to/from the given archive.
- L126 _protected function_ `virtual void OnReset(ValueTypeParam OldCurrentValue, ValueTypeParam OldTargetValue)` — Called when the current and/or target values are forcibly changed.
- L128 _protected function_ `virtual void OnRun(const FCameraValueInterpolationParams& Params, FCameraValueInterpolationResult& OutResult)` — Evaluates the interpolator, advancing the current value towards the target.
- L130 _protected function_ `virtual void OnSerialize(const FCameraValueInterpolatorSerializeParams& Params, FArchive& Ar)` — Serializes the value interpolator to/from the given archive.
- L134 _protected member_ `const UCameraValueInterpolator* Parameters;`
- L135 _protected member_ `ValueType CurrentValue;`
- L136 _protected member_ `ValueType TargetValue;`
- L137 _protected member_ `bool bIsFinished;`

#### struct `UE::Cameras::TCameraValueInterpolationTraits`  
`template<typename ValueType> struct TCameraValueInterpolationTraits`  
_L145-146_
- desc: Generic traits for interpolated value types. Empty by default, overriden for specifically supported value types.
- L151 _public function_ `static double Distance(double A, double B)`
- L156 _public function_ `static double Direction(double A, double B)`
- L165 _public function_ `static double Distance(const FVector2d& A, const FVector2d& B)`
- L170 _public function_ `static FVector2d Direction(const FVector2d& A, const FVector2d& B)`
- L179 _public function_ `static double Distance(const FVector3d& A, const FVector3d& B)`
- L184 _public function_ `static FVector3d Direction(const FVector3d& A, const FVector3d& B)`

#### struct `UE::Cameras::TCameraValueInterpolationTraits`  
`template<> struct TCameraValueInterpolationTraits<double>`  
_L149-160_
- L151 _public function_ `static double Distance(double A, double B)`
- L156 _public function_ `static double Direction(double A, double B)`
- L165 _public function_ `static double Distance(const FVector2d& A, const FVector2d& B)`
- L170 _public function_ `static FVector2d Direction(const FVector2d& A, const FVector2d& B)`
- L179 _public function_ `static double Distance(const FVector3d& A, const FVector3d& B)`
- L184 _public function_ `static FVector3d Direction(const FVector3d& A, const FVector3d& B)`

#### struct `UE::Cameras::TCameraValueInterpolationTraits`  
`template<> struct TCameraValueInterpolationTraits<FVector2d>`  
_L163-174_
- L151 _public function_ `static double Distance(double A, double B)`
- L156 _public function_ `static double Direction(double A, double B)`
- L165 _public function_ `static double Distance(const FVector2d& A, const FVector2d& B)`
- L170 _public function_ `static FVector2d Direction(const FVector2d& A, const FVector2d& B)`
- L179 _public function_ `static double Distance(const FVector3d& A, const FVector3d& B)`
- L184 _public function_ `static FVector3d Direction(const FVector3d& A, const FVector3d& B)`

#### struct `UE::Cameras::TCameraValueInterpolationTraits`  
`template<> struct TCameraValueInterpolationTraits<FVector3d>`  
_L177-188_
- L151 _public function_ `static double Distance(double A, double B)`
- L156 _public function_ `static double Direction(double A, double B)`
- L165 _public function_ `static double Distance(const FVector2d& A, const FVector2d& B)`
- L170 _public function_ `static FVector2d Direction(const FVector2d& A, const FVector2d& B)`
- L179 _public function_ `static double Distance(const FVector3d& A, const FVector3d& B)`
- L184 _public function_ `static FVector3d Direction(const FVector3d& A, const FVector3d& B)`

#### class `UE::Cameras::TPopValueInterpolator`  
`template<typename ValueType> class TPopValueInterpolator : public TCameraValueInterpolator<ValueType>`  
_L196-215_
- inherits: `TCameraValueInterpolator<ValueType>`
- desc: A simple value interpolator that immediately "pops" to the target value.
- L200 _public function_ `TPopValueInterpolator() : TCameraValueInterpolator<ValueType>(nullptr)`
- L204 _public function_ `TPopValueInterpolator(const UPopValueInterpolator* InInterpolator) : TCameraValueInterpolator<ValueType>(InInterpolator)`
- L210 _protected function_ `virtual void OnRun(const FCameraValueInterpolationParams& Params, FCameraValueInterpolationResult& OutResult) override`

#### class `UCameraValueInterpolator`  
`class UCameraValueInterpolator : public UObject`  
_L223-247_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, DefaultToInstanced, EditInlineNew, CollapseCategories)`
- inherits: `UObject`
- desc: Base class for value interpolator parameters.
- L230 _public typedef_ `template<typename ValueType> using TCameraValueInterpolator = UE::Cameras::TCameraValueInterpolator<ValueType>;`
- L233 _public prototype_ `virtual TUniquePtr<TCameraValueInterpolator<double>> BuildDoubleInterpolator() const;` — Creates a value interpolator for double precision floating point numbers.
- L235 _public prototype_ `virtual TUniquePtr<TCameraValueInterpolator<FVector2d>> BuildVector2dInterpolator() const;` — Creates a value interpolator for 2D vectors.
- L237 _public prototype_ `virtual TUniquePtr<TCameraValueInterpolator<FVector3d>> BuildVector3dInterpolator() const;` — Creates a value interpolator for 3D vectors.
- L242 _protected function_ `virtual TUniquePtr<TCameraValueInterpolator<double>> OnBuildDoubleInterpolator() const` — Creates a value interpolator for double precision floating point numbers.
- L244 _protected function_ `virtual TUniquePtr<TCameraValueInterpolator<FVector2d>> OnBuildVector2dInterpolator() const` — Creates a value interpolator for 2D vectors.
- L246 _protected function_ `virtual TUniquePtr<TCameraValueInterpolator<FVector3d>> OnBuildVector3dInterpolator() const` — Creates a value interpolator for 3D vectors.

#### class `UPopValueInterpolator`  
`class UPopValueInterpolator : public UCameraValueInterpolator`  
_L272-277_
- reflection: `UCLASS(meta=(DisplayName="Immediate Pop"))`
- inherits: `UCameraValueInterpolator`
- desc: Simple interpolator that immediately "pops" to the target value.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)
- L190 _typedef_ `using FCameraDoubleValueInterpolator = TCameraValueInterpolator<double>;` (scope `UE::Cameras`)
- L191 _typedef_ `using FCameraVector2dValueInterpolator = TCameraValueInterpolator<FVector2d>;` (scope `UE::Cameras`)
- L192 _typedef_ `using FCameraVector3dDoubleValueInterpolator = TCameraValueInterpolator<FVector3d>;` (scope `UE::Cameras`)
- L249 _macro_ `#define UE_DECLARE_CAMERA_VALUE_INTERPOLATOR()\`
- L256 _macro_ `#define UE_DEFINE_CAMERA_VALUE_INTERPOLATOR_GENERIC(ThisClass, GenericInterpolatorClass)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableAssets.h` (Public)


#### class `UCameraVariableAsset`  
`class UCameraVariableAsset : public UObject`  
_L18-82_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: The base asset class for all camera variables.
- L24 _public prototype_ `UCameraVariableAsset(const FObjectInitializer& ObjectInit);`
- L26 _public prototype_ `FCameraVariableID GetVariableID() const;`
- L28 _public prototype_ `FCameraVariableDefinition GetVariableDefinition() const;`
- L30 _public function_ `const FGuid& GetGuid() const`
- L32 _public prototype_ `virtual ECameraVariableType GetVariableType() const PURE_VIRTUAL(UCameraVariableAsset::GetVariableType, return ECameraVariableType::Boolean;);`
- L33 _public prototype_ `virtual const uint8* GetDefaultValuePtr() const PURE_VIRTUAL(UCameraVariableAsset::GetDefaultValuePtr, return nullptr;);`
- L36 _public prototype_ `FString GetDisplayName() const;`
- L40 _public prototype_ `FText GetDisplayText() const;`
- L42 _public prototype_ `virtual FString FormatDefaultValue() const PURE_VIRTUAL(UCameraVariableAsset::FormatDefaultValue, return FString(););`
- L48 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L49 _public prototype_ `virtual void PostInitProperties() override;`
- L50 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L57 _public member_ `FString DisplayName;` — `UPROPERTY()` — The name of the variable.
- L62 _public member_ `bool bAutoReset = false;` — `UPROPERTY(EditAnywhere, Category=Camera)` — Whether this variable auto-resets to its default value every frame.
- L72 _public member_ `bool bIsPreBlended = false;` — `UPROPERTY(EditAnywhere, Category=Camera)` — Whether this variable should be pre-blended. Pre-blending means that if two blending camera rigs share this variable, each of their values will be blended in a first evaluation pass, and then both camera rigs will evaluate with the same blended value.
- L76 _public member_ `bool bIsPrivate = false;` — `UPROPERTY()` — Whether this variable is private and shouldn't be propagated with evaluation results.
- L81 _private member_ `FGuid Guid;` — `UPROPERTY()`

#### class `UBooleanCameraVariable`  
`class UBooleanCameraVariable : public UCameraVariableAsset`  
_L86-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Boolean camera variable.
- L92 _public typedef_ `using ValueType = bool;`
- L94 _public function_ `bool GetDefaultValue() const`
- L96 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L97 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L100 _public function_ `virtual FString FormatDefaultValue() const override`
- L107 _public member_ `bool bDefaultValue = false;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UInteger32CameraVariable`  
`class UInteger32CameraVariable : public UCameraVariableAsset`  
_L112-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Integer camera variable.
- L118 _public typedef_ `using ValueType = int32;`
- L120 _public function_ `int32 GetDefaultValue() const`
- L122 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L123 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L126 _public function_ `virtual FString FormatDefaultValue() const override`
- L133 _public member_ `int32 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UFloatCameraVariable`  
`class UFloatCameraVariable : public UCameraVariableAsset`  
_L138-160_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Float camera variable.
- L144 _public typedef_ `using ValueType = float;`
- L146 _public function_ `float GetDefaultValue() const`
- L148 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L149 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L152 _public function_ `virtual FString FormatDefaultValue() const override`
- L159 _public member_ `float DefaultValue = 0.f;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UDoubleCameraVariable`  
`class UDoubleCameraVariable : public UCameraVariableAsset`  
_L164-186_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Double camera variable.
- L170 _public typedef_ `using ValueType = double;`
- L172 _public function_ `double GetDefaultValue() const`
- L174 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L175 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L178 _public function_ `virtual FString FormatDefaultValue() const override`
- L185 _public member_ `double DefaultValue = 0.0;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UVector2fCameraVariable`  
`class UVector2fCameraVariable : public UCameraVariableAsset`  
_L190-212_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Vector2f camera variable.
- L196 _public typedef_ `using ValueType = FVector2f;`
- L198 _public function_ `const ValueType& GetDefaultValue() const`
- L200 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L201 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L204 _public function_ `virtual FString FormatDefaultValue() const override`
- L211 _public member_ `FVector2f DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UVector2dCameraVariable`  
`class UVector2dCameraVariable : public UCameraVariableAsset`  
_L216-238_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Vector2d camera variable.
- L222 _public typedef_ `using ValueType = FVector2d;`
- L224 _public function_ `const ValueType& GetDefaultValue() const`
- L226 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L227 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L230 _public function_ `virtual FString FormatDefaultValue() const override`
- L237 _public member_ `FVector2D DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UVector3fCameraVariable`  
`class UVector3fCameraVariable : public UCameraVariableAsset`  
_L242-264_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Vector3f camera variable.
- L248 _public typedef_ `using ValueType = FVector3f;`
- L250 _public function_ `const ValueType& GetDefaultValue() const`
- L252 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L253 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L256 _public function_ `virtual FString FormatDefaultValue() const override`
- L263 _public member_ `FVector3f DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UVector3dCameraVariable`  
`class UVector3dCameraVariable : public UCameraVariableAsset`  
_L268-290_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Vector3d camera variable.
- L274 _public typedef_ `using ValueType = FVector3d;`
- L276 _public function_ `const ValueType& GetDefaultValue() const`
- L278 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L279 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L282 _public function_ `virtual FString FormatDefaultValue() const override`
- L289 _public member_ `FVector3d DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UVector4fCameraVariable`  
`class UVector4fCameraVariable : public UCameraVariableAsset`  
_L294-316_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Vector4f camera variable.
- L300 _public typedef_ `using ValueType = FVector4f;`
- L302 _public function_ `const ValueType& GetDefaultValue() const`
- L304 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L305 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L308 _public function_ `virtual FString FormatDefaultValue() const override`
- L315 _public member_ `FVector4f DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UVector4dCameraVariable`  
`class UVector4dCameraVariable : public UCameraVariableAsset`  
_L320-342_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Vector4d camera variable.
- L326 _public typedef_ `using ValueType = FVector4d;`
- L328 _public function_ `const ValueType& GetDefaultValue() const`
- L330 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L331 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L334 _public function_ `virtual FString FormatDefaultValue() const override`
- L341 _public member_ `FVector4d DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `URotator3fCameraVariable`  
`class URotator3fCameraVariable : public UCameraVariableAsset`  
_L346-368_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Rotator3f camera variable.
- L352 _public typedef_ `using ValueType = FRotator3f;`
- L354 _public function_ `const ValueType& GetDefaultValue() const`
- L356 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L357 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L360 _public function_ `virtual FString FormatDefaultValue() const override`
- L367 _public member_ `FRotator3f DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `URotator3dCameraVariable`  
`class URotator3dCameraVariable : public UCameraVariableAsset`  
_L372-394_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Rotator3d camera variable.
- L378 _public typedef_ `using ValueType = FRotator3d;`
- L380 _public function_ `const ValueType& GetDefaultValue() const`
- L382 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L383 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L386 _public function_ `virtual FString FormatDefaultValue() const override`
- L393 _public member_ `FRotator3d DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UTransform3fCameraVariable`  
`class UTransform3fCameraVariable : public UCameraVariableAsset`  
_L398-420_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Transform3f camera variable.
- L404 _public typedef_ `using ValueType = FTransform3f;`
- L406 _public function_ `const ValueType& GetDefaultValue() const`
- L408 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L409 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L412 _public function_ `virtual FString FormatDefaultValue() const override`
- L419 _public member_ `FTransform3f DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### class `UTransform3dCameraVariable`  
`class UTransform3dCameraVariable : public UCameraVariableAsset`  
_L424-446_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraVariableAsset`
- desc: Transform3d camera variable.
- L430 _public typedef_ `using ValueType = FTransform3d;`
- L432 _public function_ `const ValueType& GetDefaultValue() const`
- L434 _public function_ `virtual ECameraVariableType GetVariableType() const override`
- L435 _public function_ `virtual const uint8* GetDefaultValuePtr() const override`
- L438 _public function_ `virtual FString FormatDefaultValue() const override`
- L445 _public member_ `FTransform3d DefaultValue;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The default value of this variable.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableCollection.h` (Public)


#### class `UCameraVariableCollection`  
`class UCameraVariableCollection : public UObject`  
_L15-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An asset that represents a collection of camera variables.
- L21 _public prototype_ `UCameraVariableCollection(const FObjectInitializer& ObjectInit);`
- L26 _protected prototype_ `virtual void PostLoad() override;` — UObject interface
- L31 _private prototype_ `void CleanUpStrayObjects();`
- L38 _public member_ `TArray<TObjectPtr<UCameraVariableAsset>> Variables;` — `UPROPERTY()` — The variables in this collection.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableReferenceReader.h` (Public)


#### class `UE::Cameras::TCameraVariableReferenceReader`  
`template<typename ValueType> class TCameraVariableReferenceReader`  
_L16-105_
- desc: A utility class for reading the effective value of variable reference.
- L20 _public function_ `TCameraVariableReferenceReader()`
- L23 _public function_ `template<typename VariableReferenceType> TCameraVariableReferenceReader(const VariableReferenceType& Reference)`
- L32 _public function_ `template<typename VariableReferenceType> void Initialize(const VariableReferenceType& Reference)` — Initializes the reader around the given variable reference.
- L41 _public function_ `template<typename VariableReferenceType> void Initialize(const VariableReferenceType& Reference, typename TCallTraits<ValueType>::ParamType DefaultValueIfNoReference)` — Initializes the reader around the given variable reference.
- L62 _public function_ `const ValueType& Get(const FCameraVariableTable& VariableTable) const` — Gets the actual value for the referenced variable.
- L82 _public function_ `bool TryGet(const FCameraVariableTable& VariableTable, ValueType& OutValue) const` — Gets the actual value for the referenced variable, or returns false if the variable doesn't have a value yet.
- L94 _public function_ `bool IsDriven() const` — Returns whether his reference points to a variable.
- L102 _private member_ `ValueType DefaultValue;` — The default value for the variable.
- L104 _private member_ `FCameraVariableID VariableID;` — The ID of the variable, if any.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableReferences.h` (Public)


#### struct `FBooleanCameraVariableReference`  
`struct FBooleanCameraVariableReference`  
_L32-46_
- reflection: `USTRUCT()`
- L36 _public typedef_ `using ValueType = bool;`
- L37 _public typedef_ `using VariableAssetType = UBooleanCameraVariable;`
- L40 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L43 _public member_ `TObjectPtr<UBooleanCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FInteger32CameraVariableReference`  
`struct FInteger32CameraVariableReference`  
_L49-63_
- reflection: `USTRUCT()`
- L53 _public typedef_ `using ValueType = int32;`
- L54 _public typedef_ `using VariableAssetType = UInteger32CameraVariable;`
- L57 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L60 _public member_ `TObjectPtr<UInteger32CameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FFloatCameraVariableReference`  
`struct FFloatCameraVariableReference`  
_L66-80_
- reflection: `USTRUCT()`
- L70 _public typedef_ `using ValueType = float;`
- L71 _public typedef_ `using VariableAssetType = UFloatCameraVariable;`
- L74 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L77 _public member_ `TObjectPtr<UFloatCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FDoubleCameraVariableReference`  
`struct FDoubleCameraVariableReference`  
_L83-97_
- reflection: `USTRUCT()`
- L87 _public typedef_ `using ValueType = double;`
- L88 _public typedef_ `using VariableAssetType = UDoubleCameraVariable;`
- L91 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L94 _public member_ `TObjectPtr<UDoubleCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FVector2fCameraVariableReference`  
`struct FVector2fCameraVariableReference`  
_L100-114_
- reflection: `USTRUCT()`
- L104 _public typedef_ `using ValueType = FVector2f;`
- L105 _public typedef_ `using VariableAssetType = UVector2fCameraVariable;`
- L108 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L111 _public member_ `TObjectPtr<UVector2fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FVector2dCameraVariableReference`  
`struct FVector2dCameraVariableReference`  
_L117-131_
- reflection: `USTRUCT()`
- L121 _public typedef_ `using ValueType = FVector2d;`
- L122 _public typedef_ `using VariableAssetType = UVector2dCameraVariable;`
- L125 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L128 _public member_ `TObjectPtr<UVector2dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FVector3fCameraVariableReference`  
`struct FVector3fCameraVariableReference`  
_L134-148_
- reflection: `USTRUCT()`
- L138 _public typedef_ `using ValueType = FVector3f;`
- L139 _public typedef_ `using VariableAssetType = UVector3fCameraVariable;`
- L142 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L145 _public member_ `TObjectPtr<UVector3fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FVector3dCameraVariableReference`  
`struct FVector3dCameraVariableReference`  
_L151-165_
- reflection: `USTRUCT()`
- L155 _public typedef_ `using ValueType = FVector3d;`
- L156 _public typedef_ `using VariableAssetType = UVector3dCameraVariable;`
- L159 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L162 _public member_ `TObjectPtr<UVector3dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FVector4fCameraVariableReference`  
`struct FVector4fCameraVariableReference`  
_L168-182_
- reflection: `USTRUCT()`
- L172 _public typedef_ `using ValueType = FVector4f;`
- L173 _public typedef_ `using VariableAssetType = UVector4fCameraVariable;`
- L176 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L179 _public member_ `TObjectPtr<UVector4fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FVector4dCameraVariableReference`  
`struct FVector4dCameraVariableReference`  
_L185-199_
- reflection: `USTRUCT()`
- L189 _public typedef_ `using ValueType = FVector4d;`
- L190 _public typedef_ `using VariableAssetType = UVector4dCameraVariable;`
- L193 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L196 _public member_ `TObjectPtr<UVector4dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FRotator3fCameraVariableReference`  
`struct FRotator3fCameraVariableReference`  
_L202-216_
- reflection: `USTRUCT()`
- L206 _public typedef_ `using ValueType = FRotator3f;`
- L207 _public typedef_ `using VariableAssetType = URotator3fCameraVariable;`
- L210 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L213 _public member_ `TObjectPtr<URotator3fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FRotator3dCameraVariableReference`  
`struct FRotator3dCameraVariableReference`  
_L219-233_
- reflection: `USTRUCT()`
- L223 _public typedef_ `using ValueType = FRotator3d;`
- L224 _public typedef_ `using VariableAssetType = URotator3dCameraVariable;`
- L227 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L230 _public member_ `TObjectPtr<URotator3dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FTransform3fCameraVariableReference`  
`struct FTransform3fCameraVariableReference`  
_L236-250_
- reflection: `USTRUCT()`
- L240 _public typedef_ `using ValueType = FTransform3f;`
- L241 _public typedef_ `using VariableAssetType = UTransform3fCameraVariable;`
- L244 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L247 _public member_ `TObjectPtr<UTransform3fCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### struct `FTransform3dCameraVariableReference`  
`struct FTransform3dCameraVariableReference`  
_L253-267_
- reflection: `USTRUCT()`
- L257 _public typedef_ `using ValueType = FTransform3d;`
- L258 _public typedef_ `using VariableAssetType = UTransform3dCameraVariable;`
- L261 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L264 _public member_ `TObjectPtr<UTransform3dCameraVariable> Variable;` — `UPROPERTY(EditAnywhere, Category="Variable")`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)
- L14 _macro_ `#define UE_DEFINE_CAMERA_VARIABLE_REFERENCE(ValueName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableSetter.h` (Public)


#### enum `ECameraVariableSetterBlendType`  
`enum class ECameraVariableSetterBlendType : uint8`  
_L21-27_
- reflection: `UENUM(BlueprintType)`
- desc: The blend type for a camera variable setter.
- L23 _public enumerator_ `None`
- L24 _public enumerator_ `Linear`
- L25 _public enumerator_ `SmoothStep`
- L26 _public enumerator_ `SmootherStep`

#### struct `FCameraVariableSetterHandle`  
`struct FCameraVariableSetterHandle`  
_L33-85_
- reflection: `USTRUCT(BlueprintType)`
- desc: A handle to an ongoing camera variable setter.
- L39 _public function_ `FCameraVariableSetterHandle() : Value(INVALID), SerialNumber(0)`
- L41 _public function_ `bool IsValid() const`
- L43 _public function_ `explicit operator bool() const`
- L71 _private function_ `FCameraVariableSetterHandle(uint32 InValue, uint32 InSerialNumber) : Value(InValue) , SerialNumber(InSerialNumber)`
- L76 _private member_ `static const uint32 INVALID = uint32(-1);`
- L79 _private member_ `uint32 Value;` — `UPROPERTY()`
- L82 _private member_ `uint32 SerialNumber;` — `UPROPERTY()`

#### struct `UE::Cameras::FCameraVariableSetter`  
`struct FCameraVariableSetter`  
_L96-125_
- desc: A base structure for overriding a camera variable value until told to stop. Overriding supports blending in and out. This base structure doesn't apply the values, see TCameraVariableSetter for that.
- L98 _public member_ `ECameraVariableSetterBlendType BlendType = ECameraVariableSetterBlendType::Linear;`
- L99 _public member_ `float BlendInTime = 1.f;`
- L100 _public member_ `float BlendOutTime = 1.f;`
- L102 _public prototype_ `virtual ~FCameraVariableSetter() = default;`
- L104 _public function_ `virtual void Apply(FCameraVariableTable& VariableTable)`
- L106 _public prototype_ `void Update(float DeltaTime);`
- L107 _public prototype_ `void Stop(bool bImmediately);`
- L108 _public function_ `bool IsActive() const`
- L112 _protected function_ `FCameraVariableSetter()`
- L113 _protected function_ `FCameraVariableSetter(FCameraVariableID InVariableID) : VariableID(InVariableID)`
- L115 _protected prototype_ `void UpdateState(float DeltaTime);`
- L116 _protected prototype_ `float GetBlendFactor();`
- L122 _protected member_ `float CurrentTime = 0.f;`
- L123 _protected member_ `EState State = EState::BlendIn;`
- L124 _protected member_ `FCameraVariableID VariableID;`

#### enum `UE::Cameras::FCameraVariableSetter::EState`  
`enum class EState`  
_L120-120_
- L120 _public enumerator_ `enum class EState { Inactive, BlendIn, Full, BlendOut }; float CurrentTime = 0.f; EState State = EState::BlendIn; FCameraVariableID VariableID;`
- L120 _public enumerator_ `enum class EState { Inactive, BlendIn, Full, BlendOut }; float CurrentTime = 0.f; EState State = EState::BlendIn; FCameraVariableID VariableID;`
- L120 _public enumerator_ `enum class EState { Inactive, BlendIn, Full, BlendOut }; float CurrentTime = 0.f; EState State = EState::BlendIn; FCameraVariableID VariableID;`
- L120 _public enumerator_ `enum class EState { Inactive, BlendIn, Full, BlendOut }; float CurrentTime = 0.f; EState State = EState::BlendIn; FCameraVariableID VariableID;`

#### struct `UE::Cameras::Internal::TVariableSetterValueInterpolator`  
`template<typename ValueType> struct TVariableSetterValueInterpolator`  
_L133-139_
- L135 _public function_ `static ValueType Lerp(typename TCallTraits<ValueType>::ParamType FromValue, typename TCallTraits<ValueType>::ParamType ToValue, float BlendFactor)`
- L144 _public function_ `static bool Lerp(bool FromValue, bool ToValue, float BlendFactor)`
- L153 _public function_ `static UE::Math::TTransform<T> Lerp(const UE::Math::TTransform<T>& FromValue, const UE::Math::TTransform<T>& ToValue, float BlendFactor)`

#### struct `UE::Cameras::Internal::TVariableSetterValueInterpolator`  
`template<> struct TVariableSetterValueInterpolator<bool>`  
_L142-148_
- L135 _public function_ `static ValueType Lerp(typename TCallTraits<ValueType>::ParamType FromValue, typename TCallTraits<ValueType>::ParamType ToValue, float BlendFactor)`
- L144 _public function_ `static bool Lerp(bool FromValue, bool ToValue, float BlendFactor)`
- L153 _public function_ `static UE::Math::TTransform<T> Lerp(const UE::Math::TTransform<T>& FromValue, const UE::Math::TTransform<T>& ToValue, float BlendFactor)`

#### struct `UE::Cameras::Internal::TVariableSetterValueInterpolator`  
`template<typename T> struct TVariableSetterValueInterpolator<UE::Math::TTransform<T>>`  
_L151-159_
- L135 _public function_ `static ValueType Lerp(typename TCallTraits<ValueType>::ParamType FromValue, typename TCallTraits<ValueType>::ParamType ToValue, float BlendFactor)`
- L144 _public function_ `static bool Lerp(bool FromValue, bool ToValue, float BlendFactor)`
- L153 _public function_ `static UE::Math::TTransform<T> Lerp(const UE::Math::TTransform<T>& FromValue, const UE::Math::TTransform<T>& ToValue, float BlendFactor)`

#### struct `UE::Cameras::TCameraVariableSetter`  
`template<typename ValueType> struct TCameraVariableSetter : public FCameraVariableSetter`  
_L167-188_
- inherits: `FCameraVariableSetter`
- desc: An actual camera variable setter for a given type of values.
- L169 _public member_ `ValueType ToValue;`
- L171 _public prototype_ `TCameraVariableSetter() = default;`
- L172 _public function_ `TCameraVariableSetter(FCameraVariableID InVariableID, typename TCallTraits<ValueType>::ParamType InToValue) : FCameraVariableSetter(InVariableID) , ToValue(InToValue)`
- L177 _public function_ `virtual void Apply(FCameraVariableTable& VariableTable) override`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)
- L47 _function_ `friend bool operator==(FCameraVariableSetterHandle A, FCameraVariableSetterHandle B)`
- L52 _function_ `friend bool operator!=(FCameraVariableSetterHandle A, FCameraVariableSetterHandle B)`
- L57 _function_ `friend uint32 GetTypeHash(FCameraVariableSetterHandle In)`
- L62 _function_ `friend FArchive& operator<< (FArchive& Ar, FCameraVariableSetterHandle& In)`
- L87 _namespace_ `namespace UE`
- L87 _namespace_ `namespace Cameras` (scope `UE`)
- L127 _typedef_ `using FCameraVariableSetterPtr = TInlineValue<FCameraVariableSetter, 64>;` (scope `UE::Cameras`)
- L129 _namespace_ `namespace Internal` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableTable.h` (Public)


#### struct `UE::Cameras::TCameraVariableTraits`  
`template<typename ValueType> struct TCameraVariableTraits`  
_L20-23_
- L22 _public member_ `static const ECameraVariableType Type = ECameraVariableType::BlendableStruct;`

#### enum `UE::Cameras::ECameraVariableTableFilter`  
`enum class ECameraVariableTableFilter`  
_L31-42_
- desc: Filter for variable table operations.
- L33 _public enumerator_ `None = 0`
- L35 _public enumerator_ `PublicOnly = 1 << 0` — Don't include private variables.
- L37 _public enumerator_ `InputOnly = 1 << 1` — Only include input variables.
- L39 _public enumerator_ `KnownOnly = 1 << 2` — Only include data that is common to both tables.
- L41 _public enumerator_ `ChangedOnly = 1 << 3` — Only include variables that were written this frame.

#### struct `UE::Cameras::FCameraVariableTableFlags`  
`struct FCameraVariableTableFlags`  
_L49-53_
- desc: A structure that keeps track of which variables have been processed in a camera variable table.
- L52 _public member_ `TSet<FCameraVariableID> VariableIDs;` — The list of processed variable IDs.

#### class `UE::Cameras::FCameraVariableTable`  
`class FCameraVariableTable`  
_L71-278_
- desc: The camera variable table is a container for a collection of arbitrary values of various types. Only certain basic types are supported (most primitive types). This table serves both as an implementation of the usual "blackboard" design, where gameplay systems can push any appropriate values into the camera system, and as a place for camera node evaluators to stash various things. The main function of the variable table is that it is blended along with the camera rig it belongs to. Any matching values between to blended tables with be themselves blended, except for values flagged as "private". Internally, the variable table is allocated as one continuous block of memory, plus a map of metadata keyed by variable ID. A variable ID can be anything, but will generally be the hash of the variable name.
- L75 _public prototype_ `FCameraVariableTable();`
- L76 _public prototype_ `FCameraVariableTable(FCameraVariableTable&& Other);`
- L77 _public prototype_ `FCameraVariableTable& operator=(FCameraVariableTable&& Other);`
- L78 _public prototype_ `~FCameraVariableTable();`
- L80 _public prototype_ `FCameraVariableTable(const FCameraVariableTable&) = delete;`
- L81 _public prototype_ `FCameraVariableTable& operator=(const FCameraVariableTable&) = delete;`
- L84 _public prototype_ `void Initialize(const FCameraVariableTableAllocationInfo& AllocationInfo);` — Initializes the variable table so that it fits the provided allocation info.
- L90 _public prototype_ `bool EnsureVariables(const FCameraVariableTableAllocationInfo& AllocationInfo);` — Ensure that all the variables referenced in the given allocation info exist in the table. Returns false if some variables had to be added.
- L97 _public prototype_ `void AddVariable(const FCameraVariableDefinition& VariableDefinition);` — Adds a variable to the table. This may re-allocate the internal memory buffer. It's recommended to pre-compute the allocation information needed for a table, and initialize it once.
- L104 _public prototype_ `template<typename ValueType> const ValueType* FindValue(FCameraVariableID VariableID) const;`
- L107 _public prototype_ `template<typename ValueType> const ValueType& GetValue(FCameraVariableID VariableID) const;`
- L110 _public prototype_ `template<typename ValueType> ValueType GetValue(FCameraVariableID VariableID, typename TCallTraits<ValueType>::ParamType DefaultValue) const;`
- L113 _public prototype_ `template<typename VariableAssetType> typename VariableAssetType::ValueType GetValue(const VariableAssetType* VariableAsset) const;`
- L116 _public prototype_ `template<typename ValueType> bool TryGetValue(FCameraVariableID VariableID, ValueType& OutValue) const;`
- L119 _public prototype_ `template<typename VariableAssetType> bool TryGetValue(const VariableAssetType* VariableAsset, typename VariableAssetType::ValueType& OutValue) const;`
- L121 _public prototype_ `bool ContainsValue(FCameraVariableID VariableID) const;`
- L128 _public prototype_ `template<typename ValueType> void SetValue(FCameraVariableID VariableID, typename TCallTraits<ValueType>::ParamType Value);`
- L131 _public prototype_ `template<typename ValueType> bool TrySetValue(FCameraVariableID VariableID, typename TCallTraits<ValueType>::ParamType Value);`
- L134 _public prototype_ `template<typename ValueType> void SetValue( const FCameraVariableDefinition& VariableDefinition, typename TCallTraits<ValueType>::ParamType Value, bool bCreateIfMissing = false);`
- L140 _public prototype_ `template<typename VariableAssetType> void SetValue( const VariableAssetType* VariableAsset, typename TCallTraits<typename VariableAssetType::ValueType>::ParamType Value, bool bCreateIfMissing = false);`
- L149 _public prototype_ `void OverrideAll(const FCameraVariableTable& OtherTable, bool bIncludePrivateValues = false);`
- L150 _public prototype_ `void Override(const FCameraVariableTable& OtherTable, ECameraVariableTableFilter Filter);`
- L151 _public prototype_ `void Override(const FCameraVariableTable& OtherTable, ECameraVariableTableFilter Filter, const FCameraVariableTableFlags& InMask, bool bInvertMask, FCameraVariableTableFlags& OutMask);`
- L153 _public prototype_ `void LerpAll(const FCameraVariableTable& ToTable, float Factor, bool bIncludePrivateValues = false);`
- L154 _public prototype_ `void Lerp(const FCameraVariableTable& ToTable, ECameraVariableTableFilter Filter, float Factor);`
- L155 _public prototype_ `void Lerp(const FCameraVariableTable& ToTable, ECameraVariableTableFilter Filter, float Factor, const FCameraVariableTableFlags& InMask, bool bInvertMask, FCameraVariableTableFlags& OutMask);`
- L161 _public prototype_ `const uint8* GetValue( FCameraVariableID VariableID, ECameraVariableType ExpectedVariableType, const UScriptStruct* ExpectedBlendableStructType, bool bOnlyIfWritten = true) const;`
- L167 _public prototype_ `const uint8* TryGetValue( FCameraVariableID VariableID, ECameraVariableType ExpectedVariableType, const UScriptStruct* ExpectedBlendableStructType, bool bOnlyIfWritten = true) const;`
- L173 _public prototype_ `uint8* TryGetMutableValue( FCameraVariableID VariableID, ECameraVariableType ExpectedVariableType, const UScriptStruct* ExpectedBlendableStructType, bool bOnlyIfWritten = true);`
- L179 _public prototype_ `void SetValue( FCameraVariableID VariableID, ECameraVariableType ExpectedVariableType, const UScriptStruct* ExpectedBlendableStructType, const uint8* InRawValuePtr, bool bMarkAsWrittenThisFrame = true);`
- L186 _public prototype_ `bool TrySetValue( FCameraVariableID VariableID, ECameraVariableType ExpectedVariableType, const UScriptStruct* ExpectedBlendableStructType, const uint8* InRawValuePtr, bool bMarkAsWrittenThisFrame = true);`
- L193 _public prototype_ `bool IsValueWritten(FCameraVariableID VariableID) const;`
- L194 _public prototype_ `void UnsetValue(FCameraVariableID VariableID);`
- L195 _public prototype_ `void UnsetAllValues();`
- L197 _public prototype_ `bool IsValueWrittenThisFrame(FCameraVariableID VariableID) const;`
- L198 _public prototype_ `void ClearAllWrittenThisFrameFlags();`
- L200 _public prototype_ `void AutoResetValues();`
- L202 _public prototype_ `bool TryGetVariableDefinition(FCameraVariableID VariableID, FCameraVariableDefinition& OutVariableDefinition) const;`
- L204 _public prototype_ `void Serialize(FArchive& Ar);`
- L210 _private prototype_ `static void CacheBlendableStructs();`
- L211 _private prototype_ `static FBlendableStructTypeErasedInterpolator GetBlendableStructInterpolator(const UScriptStruct* StructType);`
- L213 _private prototype_ `static bool GetVariableTypeAllocationInfo(ECameraVariableType VariableType, const UScriptStruct* StructType, uint32& OutSizeOf, uint32& OutAlignOf);`
- L215 _private prototype_ `static void CreateEntry(const FCameraVariableDefinition& VariableDefinition, FEntry& OutEntry);`
- L218 _private function_ `template<typename ValueType> static bool CheckVariableType(ECameraVariableType InType)`
- L223 _private prototype_ `void ReallocateBuffer(uint32 MinRequired = 0);`
- L225 _private prototype_ `FEntry* FindEntry(FCameraVariableID VariableID);`
- L226 _private prototype_ `const FEntry* FindEntry(FCameraVariableID VariableID) const;`
- L228 _private prototype_ `void InternalOverride(const FCameraVariableTable& OtherTable, ECameraVariableTableFilter Filter, const FCameraVariableTableFlags* InMask, bool bInvertMask, FCameraVariableTableFlags* OutMask);`
- L229 _private prototype_ `void InternalLerp(const FCameraVariableTable& ToTable, ECameraVariableTableFilter Filter, float Factor, const FCameraVariableTableFlags* InMask, bool bInvertMask, FCameraVariableTableFlags* OutMask);`
- L231 _private prototype_ `void InitializeEntries(int32 StartIndex = 0, int32 EndIndex = -1);`
- L235 _private member_ `static const uint32 GDefaultCapacity;`
- L236 _private member_ `static const uint32 GDefaultAlignment;`
- L261 _private member_ `TArray<FEntry> Entries;`
- L262 _private member_ `TMap<FCameraVariableID, int32> EntryLookup;`
- L264 _private member_ `uint8* Memory = nullptr;`
- L265 _private member_ `uint32 Capacity = 0;`
- L266 _private member_ `uint32 Alignment = 0;`
- L267 _private member_ `uint32 Used = 0;`
- L269 _private member_ `static TArray<FBlendableStructInfo> CachedBlendableStructs;`
- L270 _private member_ `static bool bCachedBlendableStructs;`
- L297 _function_ `template<typename ValueType> const ValueType& FCameraVariableTable::GetValue(FCameraVariableID VariableID) const`
- L322 _function_ `template<typename ValueType> ValueType FCameraVariableTable::GetValue(FCameraVariableID VariableID, typename TCallTraits<ValueType>::ParamType DefaultValue) const`
- L332 _function_ `template<typename VariableAssetType> typename VariableAssetType::ValueType FCameraVariableTable::GetValue(const VariableAssetType* VariableAsset) const`
- L338 _function_ `template<typename ValueType> bool FCameraVariableTable::TryGetValue(FCameraVariableID VariableID, ValueType& OutValue) const`
- L349 _function_ `template<typename VariableAssetType> bool FCameraVariableTable::TryGetValue(const VariableAssetType* VariableAsset, typename VariableAssetType::ValueType& OutValue) const`
- L355 _function_ `template<typename ValueType> void FCameraVariableTable::SetValue(FCameraVariableID VariableID, typename TCallTraits<ValueType>::ParamType Value)`
- L368 _function_ `template<typename ValueType> bool FCameraVariableTable::TrySetValue(FCameraVariableID VariableID, typename TCallTraits<ValueType>::ParamType Value)`
- L382 _function_ `template<typename ValueType> void FCameraVariableTable::SetValue( const FCameraVariableDefinition& VariableDefinition, typename TCallTraits<ValueType>::ParamType Value, bool bCreateIfMissing)`
- L412 _function_ `template<typename VariableAssetType> void FCameraVariableTable::SetValue( const VariableAssetType* VariableAsset, typename TCallTraits<typename VariableAssetType::ValueType>::ParamType Value, bool bCreateIfMissing)`

#### enum `UE::Cameras::FCameraVariableTable::EEntryFlags`  
`enum class EEntryFlags : uint8`  
_L238-246_
- L240 _public enumerator_ `None = 0`
- L241 _public enumerator_ `Private = 1 << 0`
- L242 _public enumerator_ `Input = 1 << 1`
- L243 _public enumerator_ `AutoReset = 1 << 2`
- L244 _public enumerator_ `Written = 1 << 3`
- L245 _public enumerator_ `WrittenThisFrame = 1 << 4`

#### struct `UE::Cameras::FCameraVariableTable::FEntry`  
`struct FEntry`  
_L249-259_
- L251 _public member_ `FCameraVariableID ID;`
- L252 _public member_ `ECameraVariableType Type;`
- L253 _public member_ `const UScriptStruct* StructType = nullptr;`
- L254 _public member_ `uint32 Offset;`
- L255 _public member_ `EEntryFlags Flags;`
- L257 _public member_ `FString DebugName;`

#### struct `UE::Cameras::TCameraVariableInterpolation`  
`template<typename ValueType> struct TCameraVariableInterpolation`  
_L448-455_
- L450 _public typedef_ `using ValueParam = typename TCallTraits<ValueType>::ParamType;`
- L451 _public function_ `static ValueType Interpolate(const FCameraVariableTable::FEntry& TableEntry, ValueParam From, ValueParam To, float Factor)`
- L460 _public typedef_ `using ValueType = UE::Math::TTransform<T>;`

#### struct `UE::Cameras::TCameraVariableInterpolation`  
`template<typename T> struct TCameraVariableInterpolation<UE::Math::TTransform<T>>`  
_L458-468_
- L450 _public typedef_ `using ValueParam = typename TCallTraits<ValueType>::ParamType;`
- L451 _public function_ `static ValueType Interpolate(const FCameraVariableTable::FEntry& TableEntry, ValueParam From, ValueParam To, float Factor)`
- L460 _public typedef_ `using ValueType = UE::Math::TTransform<T>;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)
- L280 _function_ `ENUM_CLASS_FLAGS(FCameraVariableTable::EEntryFlags) template<typename ValueType> const ValueType* FCameraVariableTable::FindValue(FCameraVariableID VariableID) const` (scope `UE::Cameras`)
- L438 _macro_ `#define UE_CAMERA_VARIABLE_FOR_TYPE(ValueType, ValueName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableTableAllocationInfo.h` (Public)


#### struct `FCameraVariableDefinition`  
`struct FCameraVariableDefinition`  
_L14-85_
- reflection: `USTRUCT()`
- desc: A structure that describes a camera variable.
- L20 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()` — The ID of the variable.
- L24 _public member_ `ECameraVariableType VariableType = ECameraVariableType::Boolean;` — `UPROPERTY()` — The type of the variable.
- L28 _public member_ `TObjectPtr<const UScriptStruct> BlendableStructType;` — `UPROPERTY()` — The type of a blendable struct (only valid when VariableType == BlendableStruct).
- L37 _public member_ `bool bIsPrivate = false;` — `UPROPERTY()` — Whether the variable is private. Private variables are not propagated from one table to another when interpolating or overriding a table.
- L45 _public member_ `bool bIsInput = false;` — `UPROPERTY()` — Whether the variable is an input variable. Input variables are blended during the pre-blend parameter update phase.
- L49 _public member_ `bool bAutoReset = false;` — `UPROPERTY()` — Whether the variable should auto-reset to an "unset" state after every evaluation.
- L54 _public member_ `FString VariableName;` — `UPROPERTY()` — The name of the variable, for debugging purposes.
- L58 _public function_ `bool IsValid() const` — Returns whether this definition has a valid variable ID.
- L64 _public function_ `operator FCameraVariableID() const` — Implicit conversion to a camera variable ID.
- L70 _public function_ `FCameraVariableDefinition CreateVariant(const FString& VariantID) const` — Creates a variant of this camera variable definition.
- L84 _public prototype_ `bool operator==(const FCameraVariableDefinition& Other) const = default;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraVariableDefinition> : public TStructOpsTypeTraitsBase2<FCameraVariableDefinition>`  
_L88-95_
- inherits: `TStructOpsTypeTraitsBase2<FCameraVariableDefinition>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L91-94_

#### struct `FCameraVariableTableAllocationInfo`  
`struct FCameraVariableTableAllocationInfo`  
_L101-116_
- reflection: `USTRUCT()`
- desc: A structure that describes the required camera variable table setup of a camera rig.
- L107 _public member_ `TArray<FCameraVariableDefinition> VariableDefinitions;` — `UPROPERTY()` — The list of variables that should be allocated in a table.
- L110 _public prototype_ `void Combine(const FCameraVariableTableAllocationInfo& OtherInfo);` — Combines the given allocation info with this one.
- L113 _public prototype_ `bool Contains(const FCameraVariableTableAllocationInfo& OtherInfo) const;` — Returns whether the given variable definitions already exist in our list.
- L115 _public prototype_ `bool operator==(const FCameraVariableTableAllocationInfo& Other) const = default;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCameraVariableTableAllocationInfo> : public TStructOpsTypeTraitsBase2<FCameraVariableTableAllocationInfo>`  
_L119-126_
- inherits: `TStructOpsTypeTraitsBase2<FCameraVariableTableAllocationInfo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L122-125_

#### Free symbols / members of external scopes

- L92 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon20001a0d0103`)
- L93 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon20001a0d0103`)
- L123 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon20001a0d0203`)
- L124 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon20001a0d0203`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/CameraVariableTableFwd.h` (Public)


#### enum `ECameraVariableType`  
`enum class ECameraVariableType`  
_L36-53_
- reflection: `UENUM()`
- desc: The type of a camera variable. Only a fixed set of types are supported for camera variables because of simplicity, and because these types need to be blendable.
- L38 _public enumerator_ `Boolean`
- L39 _public enumerator_ `Integer32`
- L40 _public enumerator_ `Float`
- L41 _public enumerator_ `Double`
- L42 _public enumerator_ `Vector2f`
- L43 _public enumerator_ `Vector2d`
- L44 _public enumerator_ `Vector3f`
- L45 _public enumerator_ `Vector3d`
- L46 _public enumerator_ `Vector4f`
- L47 _public enumerator_ `Vector4d`
- L48 _public enumerator_ `Rotator3f`
- L49 _public enumerator_ `Rotator3d`
- L50 _public enumerator_ `Transform3f`
- L51 _public enumerator_ `Transform3d`
- L52 _public enumerator_ `BlendableStruct`

#### struct `FCameraVariableID`  
`struct FCameraVariableID`  
_L59-114_
- reflection: `USTRUCT()`
- desc: The ID of a camera variable, used to refer to it in a camera variable table.
- L65 _public function_ `FCameraVariableID() : Value(INVALID)`
- L67 _public function_ `uint32 GetValue() const`
- L69 _public function_ `bool IsValid() const`
- L71 _public function_ `explicit operator bool() const`
- L73 _public function_ `static FCameraVariableID FromHashValue(uint32 InValue)`
- L108 _private function_ `FCameraVariableID(uint32 InValue) : Value(InValue)`
- L110 _private member_ `static const uint32 INVALID = uint32(-1);`
- L113 _private member_ `uint32 Value;` — `UPROPERTY()`

#### struct `UE::Cameras::FBlendableStructInfo`  
`struct FBlendableStructInfo`  
_L121-125_
- L123 _public member_ `TObjectPtr<const UScriptStruct> StructType;`
- L124 _public member_ `FBlendableStructTypeErasedInterpolator Interpolator;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_CAMERA_VARIABLE_FOR_ALL_TYPES()\`
- L80 _function_ `friend bool operator<(FCameraVariableID A, FCameraVariableID B)`
- L85 _function_ `friend bool operator==(FCameraVariableID A, FCameraVariableID B)`
- L90 _function_ `friend bool operator!=(FCameraVariableID A, FCameraVariableID B)`
- L95 _function_ `friend uint32 GetTypeHash(FCameraVariableID In)`
- L100 _function_ `friend FArchive& operator<< (FArchive& Ar, FCameraVariableID& In)`
- L116 _namespace_ `namespace UE`
- L116 _namespace_ `namespace Cameras` (scope `UE`)
- L119 _typedef_ `using FBlendableStructTypeErasedInterpolator = void(*)(uint8* From, const uint8* To, float Alpha);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/DefaultRootCameraNode.h` (Public)


#### class `UDefaultRootCameraNode`  
`class UDefaultRootCameraNode : public URootCameraNode`  
_L17-42_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `URootCameraNode`
- desc: The default implementation of a root camera node.
- L23 _public prototype_ `UDefaultRootCameraNode(const FObjectInitializer& ObjectInit);`
- L27 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L32 _public member_ `TObjectPtr<UBlendStackCameraNode> BaseLayer;` — `UPROPERTY(Instanced)`
- L35 _public member_ `TObjectPtr<UBlendStackCameraNode> MainLayer;` — `UPROPERTY(Instanced)`
- L38 _public member_ `TObjectPtr<UBlendStackCameraNode> GlobalLayer;` — `UPROPERTY(Instanced)`
- L41 _public member_ `TObjectPtr<UBlendStackCameraNode> VisualLayer;` — `UPROPERTY(Instanced)`

#### class `UE::Cameras::FDefaultRootCameraNodeEvaluator`  
`class FDefaultRootCameraNodeEvaluator : public FRootCameraNodeEvaluator`  
_L54-98_
- inherits: `FRootCameraNodeEvaluator`
- desc: Evaluator for the default root camera node.
- L61 _protected prototype_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren() override;` — FCameraNodeEvaluator interface.
- L62 _protected prototype_ `virtual void OnBuild(const FCameraNodeEvaluatorBuildParams& Params) override;`
- L63 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L64 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L65 _protected prototype_ `virtual void OnExecuteOperation(const FCameraOperationParams& Params, FCameraOperation& Operation) override;`
- L68 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L72 _protected prototype_ `virtual FCameraRigInstanceID OnActivateCameraRig(const FActivateCameraRigParams& Params) override;` — FRootCameraNodeEvaluator interface.
- L73 _protected prototype_ `virtual void OnDeactivateCameraRig(const FDeactivateCameraRigParams& Params) override;`
- L74 _protected prototype_ `virtual void OnDeactivateAllCameraRigs(TSharedPtr<const FCameraEvaluationContext> InContext, bool bImmediately) override;`
- L75 _protected prototype_ `virtual void OnGetActiveCameraRigInfo(FCameraRigEvaluationInfo& OutCameraRigInfo) const override;`
- L76 _protected prototype_ `virtual bool OnHasAnyRunningCameraRig(TSharedPtr<const FCameraEvaluationContext> InContext) const override;`
- L77 _protected prototype_ `virtual void OnGetCameraRigInfo(const FCameraRigInstanceID InstanceID, FCameraRigEvaluationInfo& OutCameraRigInfo) const override;`
- L78 _protected prototype_ `virtual const FCameraVariableTable* OnGetBlendedParameters() const override;`
- L79 _protected prototype_ `virtual void OnBuildSingleCameraRigHierarchy(const FSingleCameraRigHierarchyBuildParams& Params, FCameraNodeEvaluatorHierarchy& OutHierarchy) override;`
- L80 _protected prototype_ `virtual void OnRunSingleCameraRig(const FSingleCameraRigEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L81 _protected prototype_ `virtual TSharedPtr<FCameraActionScope> OnGetActiveCameraRigActionScope(bool bCreateIfNeeded) override;`
- L86 _private prototype_ `template<typename EvaluatorType> EvaluatorType* BuildBlendStackEvaluator(const FCameraNodeEvaluatorBuildParams& Params, UBlendStackCameraNode* BlendStackNode);`
- L88 _private prototype_ `void OnBlendStackEvent(const FBlendStackCameraRigEvent& InEvent);`
- L92 _private member_ `FPersistentBlendStackCameraNodeEvaluator* BaseLayer;`
- L93 _private member_ `FTransientBlendStackCameraNodeEvaluator* MainLayer;`
- L94 _private member_ `FPersistentBlendStackCameraNodeEvaluator* GlobalLayer;`
- L95 _private member_ `FPersistentBlendStackCameraNodeEvaluator* VisualLayer;`
- L97 _private member_ `TSharedPtr<FCameraParameterSetterService> ParameterSetterService;`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/IAssetReferenceCameraNode.h` (Public)


#### class `UAssetReferenceCameraNode`  
`class UAssetReferenceCameraNode : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IAssetReferenceCameraNode`  
`class IAssetReferenceCameraNode`  
_L19-26_
- L25 _public prototype_ `virtual void GatherPackages(FCameraRigPackages& OutPackages) const = 0;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/ICustomCameraNodeParameterProvider.h` (Public)


#### struct `UE::Cameras::FCameraNodeBlendableParameterInfo`  
`struct FCameraNodeBlendableParameterInfo`  
_L23-31_
- desc: Information about a blendable parameter on a camera node.
- L25 _public member_ `FName ParameterName;`
- L26 _public member_ `ECameraVariableType VariableType = ECameraVariableType::Boolean;`
- L27 _public member_ `const UScriptStruct* BlendableStructType = nullptr;`
- L28 _public member_ `const uint8* DefaultValue = nullptr;`
- L29 _public member_ `FCameraVariableID* OverrideVariableID = nullptr;`
- L30 _public member_ `UCameraVariableAsset* OverrideVariable = nullptr;`

#### struct `UE::Cameras::FCameraNodeDataParameterInfo`  
`struct FCameraNodeDataParameterInfo`  
_L34-42_
- desc: Information about a data parameter on a camera node.
- L36 _public member_ `FName ParameterName;`
- L37 _public member_ `ECameraContextDataType DataType = ECameraContextDataType::Name;`
- L38 _public member_ `ECameraContextDataContainerType DataContainerType = ECameraContextDataContainerType::None;`
- L39 _public member_ `const UObject* DataTypeObject = nullptr;`
- L40 _public member_ `const uint8* DefaultValue = nullptr;`
- L41 _public member_ `FCameraContextDataID* OverrideDataID = nullptr;`

#### struct `UE::Cameras::FCameraNodeParameterInfos`  
`struct FCameraNodeParameterInfos`  
_L47-116_
- desc: A structure providing information about the exposed parameters on a camera node.
- L49 _public typedef_ `using FBlendableParameterInfo = FCameraNodeBlendableParameterInfo;`
- L50 _public typedef_ `using FDataParameterInfo = FCameraNodeDataParameterInfo;`
- L59 _public prototype_ `void AddBlendableParameter( FName ParameterName, ECameraVariableType VariableType, const UScriptStruct* BlendableStructType, const uint8* DefaultValue, FCameraVariableID* OverrideVariableID, UCameraVariableAsset* OverrideVariable = nullptr);` — Declares a blendable parameter. Pass a null pointer for OverrideVariableID if this parameter should not be overridable by a camera rig parameter.
- L67 _public prototype_ `void AddBlendableParameter(FCustomCameraNodeBlendableParameter& Parameter, const uint8* DefaultValue);`
- L74 _public prototype_ `void AddDataParameter( FName ParameterName, ECameraContextDataType DataType, ECameraContextDataContainerType DataContainerType, const UObject* DataTypeObject, const uint8* DefaultValue, FCameraContextDataID* OverrideDataID);` — Declares a data parameter. Pass a null pointer for OverrideDataID if this parameter should not be overridable by a camera rig parameter.
- L82 _public prototype_ `void AddDataParameter(FCustomCameraNodeDataParameter& Parameter, const uint8* DefaultValue);`
- L85 _public prototype_ `void Reset();` — Clears the list of parameters in this structure.
- L90 _public function_ `bool HasAnyParameters() const` — Returns whether there are any blendable or data parameters.
- L93 _public function_ `TConstArrayView<FBlendableParameterInfo> GetBlendableParameters() const` — Gets the list of blendable parameters.
- L95 _public function_ `TConstArrayView<FDataParameterInfo> GetDataParameters() const` — Gets the list of data parameters.
- L98 _public prototype_ `const FBlendableParameterInfo* FindBlendableParameter(FName ParameterName) const;` — Finds a blendable parameter of the given name.
- L100 _public prototype_ `const FDataParameterInfo* FindDataParameter(FName ParameterName) const;` — Finds a data parameter of the given name.
- L105 _public prototype_ `void BuildFrom(UCameraNode* InCameraNode);` — Build this structure from the given camera node.
- L109 _private member_ `TArray<FBlendableParameterInfo> BlendableParameters;`
- L110 _private member_ `TArray<FDataParameterInfo> DataParameters;`

#### struct `FCustomCameraNodeBlendableParameter`  
`struct FCustomCameraNodeBlendableParameter`  
_L122-147_
- reflection: `USTRUCT()`
- desc: Describes a custom camera blendable parameter.
- L128 _public member_ `FName ParameterName;` — `UPROPERTY()` — The name of the parameter.
- L132 _public member_ `ECameraVariableType VariableType = ECameraVariableType::Boolean;` — `UPROPERTY()` — The type of the parameter.
- L136 _public member_ `TObjectPtr<const UScriptStruct> BlendableStructType;` — `UPROPERTY()` — The struct type of a blendable struct.
- L140 _public member_ `FCameraVariableID OverrideVariableID;` — `UPROPERTY()` — An optional camera variable ID for dynamically driving the parameter's value.
- L144 _public member_ `TObjectPtr<UCameraVariableAsset> OverrideVariable;` — `UPROPERTY()` — An optional user-defined camera variable for dynamically driving the parameter's value.
- L146 _public prototype_ `bool operator==(const FCustomCameraNodeBlendableParameter& Other) const = default;`

#### struct `FCustomCameraNodeDataParameter`  
`struct FCustomCameraNodeDataParameter`  
_L151-176_
- reflection: `USTRUCT()`
- desc: Describes a custom camera data parameter.
- L157 _public member_ `FName ParameterName;` — `UPROPERTY()` — The name of the parameter.
- L161 _public member_ `ECameraContextDataType DataType = ECameraContextDataType::Name;` — `UPROPERTY()` — The type of the parameter.
- L165 _public member_ `ECameraContextDataContainerType DataContainerType = ECameraContextDataContainerType::None;` — `UPROPERTY()` — The type of the parameter container.
- L169 _public member_ `TObjectPtr<const UObject> DataTypeObject;` — `UPROPERTY()` — An extra type object for the parameter.
- L173 _public member_ `FCameraContextDataID OverrideDataID;` — `UPROPERTY()` — An optional context data ID for dynamically driving the parameter's value.
- L175 _public prototype_ `bool operator==(const FCustomCameraNodeDataParameter& Other) const = default;`

#### struct `FCustomCameraNodeParameters`  
`struct FCustomCameraNodeParameters`  
_L183-202_
- reflection: `USTRUCT()`
- desc: Describes custom camera parameters. This structure is suitable for being owned by a camera node that wants to manage a variable number of custom parameters.
- L189 _public member_ `TArray<FCustomCameraNodeBlendableParameter> BlendableParameters;` — `UPROPERTY()` — The list of blendable parameters.
- L193 _public member_ `TArray<FCustomCameraNodeDataParameter> DataParameters;` — `UPROPERTY()` — The list of data parameters.
- L196 _public function_ `bool HasAnyParameters() const` — Returns whether this struct has any blendable or data parameter.
- L199 _public function_ `void Reset()` — Removes all parameters from this structure.
- L201 _public prototype_ `bool operator==(const FCustomCameraNodeParameters& Other) const = default;`

#### class `UCustomCameraNodeParameterProvider`  
`class UCustomCameraNodeParameterProvider : public UInterface`  
_L205-208_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICustomCameraNodeParameterProvider`  
`class ICustomCameraNodeParameterProvider`  
_L214-227_
- desc: An interface for camera nodes that want to expose a custom interface of blendable parameters and data parameters.
- L220 _public typedef_ `using FCameraNodeParameterInfos = UE::Cameras::FCameraNodeParameterInfos;`
- L223 _public function_ `virtual void GetCustomCameraNodeParameters(FCameraNodeParameterInfos& OutParameterInfos)` — Gathers the custom parameters on this node.
- L226 _public prototype_ `void OnCustomCameraNodeParametersChanged(const UCameraNode* ThisAsCameraNode) const;` — Utility function for sub-classes to broadcast when the custom parameters have changed.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L20 _namespace_ `namespace Internal` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/ObjectChildrenView.h` (Public)


#### struct `UE::Cameras::TObjectChildrenView`  
`template<typename ChildType> struct TObjectChildrenView`  
_L24-165_
- desc: Structure that describes a list of children of an object. This structure can either provide a TArrayView<> on an existing container of children, or store within itself a list of arbitrary camera node children.
- L28 _public typedef_ `using FArrayView = TArrayView<ChildType>;`
- L29 _public typedef_ `using FArray = TArray<ChildType, TInlineAllocator<4>>;`
- L32 _public function_ `TObjectChildrenView()` — An empty view.
- L37 _public function_ `TObjectChildrenView(FArrayView&& InArrayView)` — Sets the view to the given TArrayView<>.
- L43 _public function_ `TObjectChildrenView(std::initializer_list<ChildType> InChildren)` — Sets the view to pointer storage and adds the given list of children pointers.
- L50 _public function_ `template<typename OtherType, bool V = std::is_convertible_v<OtherType, ChildType>> TObjectChildrenView(TArrayView<OtherType> InRange)` — Sets the view to pointer storage and adds the given list of children pointers.
- L59 _public function_ `void Add(typename TCallTraits<ChildType>::ParamType InChild)` — Sets the view to pointer storage (if not already done) and adds the given pointer to the list.
- L70 _public function_ `bool IsEmpty() const` — Whether this view has any children.
- L84 _public function_ `int32 Num() const` — Returns the number of children.
- L98 _public function_ `ChildType operator[](int32 Index) const` — Gets the i'th child.
- L146 _public function_ `inline FIterator begin() const`
- L147 _public function_ `inline FIterator end() const`
- L158 _public function_ `inline FReverseIterator rbegin() const`
- L159 _public function_ `inline FReverseIterator rend() const`
- L163 _private typedef_ `using FStorage = TVariant<FArrayView, FArray>;`
- L164 _private member_ `FStorage Storage;`

#### struct `UE::Cameras::TObjectChildrenView::FBaseIterator`  
`struct FBaseIterator`  
_L115-135_
- L117 _public member_ `const TObjectChildrenView* Owner;`
- L118 _public member_ `int32 Index;`
- L120 _public function_ `inline ChildType operator*()`
- L125 _public function_ `inline bool operator== (const FBaseIterator& Other) const`
- L131 _public function_ `inline bool operator!= (const FBaseIterator& Other) const`

#### struct `UE::Cameras::TObjectChildrenView::FIterator`  
`struct FIterator : FBaseIterator`  
_L137-144_
- inherits: `FBaseIterator`
- L139 _public function_ `inline FIterator& operator++()`

#### struct `UE::Cameras::TObjectChildrenView::FReverseIterator`  
`struct FReverseIterator : FBaseIterator`  
_L149-156_
- inherits: `FBaseIterator`
- L151 _public function_ `inline FReverseIterator& operator++()`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/ObjectTreeGraphComment.h` (Public)


#### class `UObjectTreeGraphComment`  
`class UObjectTreeGraphComment : public UObject , public IObjectTreeGraphObject`  
_L14-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IObjectTreeGraphObject`
- desc: A generic comment node for object tree graphs.
- L22 _public prototype_ `UObjectTreeGraphComment(const FObjectInitializer& ObjInit);`
- L29 _public prototype_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const override;` — IObjectTreeGraphObject interface.
- L30 _public prototype_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty) override;`
- L31 _public prototype_ `virtual void GetGraphNodeName(FName InGraphName, FText& OutName) const override;`
- L32 _public prototype_ `virtual void OnRenameGraphNode(FName InGraphName, const FString& NewName) override;`
- L42 _public member_ `FString CommentText;` — `UPROPERTY()` — The text of the comment node.
- L46 _public member_ `FLinearColor CommentColor = FLinearColor::White;` — `UPROPERTY()` — Color of the comment node in the node graph editor.
- L50 _public member_ `FIntVector2 GraphNodePos = FIntVector2::ZeroValue;` — `UPROPERTY()` — Position of the comment node in the node graph editor.
- L54 _public member_ `FIntVector2 GraphNodeSize = FIntVector2(400, 100);` — `UPROPERTY()` — Size of the comment node in the node graph editor.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/ObjectTreeGraphObject.h` (Public)


#### class `UObjectTreeGraphObject`  
`class UObjectTreeGraphObject : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### enum `EObjectTreeGraphObjectSupportFlags`  
`enum class EObjectTreeGraphObjectSupportFlags`  
_L20-30_
- desc: Flags representing supported optional APIs of an IObjectTreeGraphObject.
- L23 _public enumerator_ `None` — None supported, only graph node position.
- L25 _public enumerator_ `CommentText = 1 << 0` — Supports storing a comment text.
- L27 _public enumerator_ `CustomTitle = 1 << 1` — Has a custom graph node title.
- L29 _public enumerator_ `CustomRename = 1 << 2` — Supports custom renaming the graph node.

#### class `IObjectTreeGraphObject`  
`class IObjectTreeGraphObject`  
_L39-72_
- desc: An interface that UObjects can implement to customize how they are represented and interacted with inside an object tree graph (see UObjectTreeGraph).
- L50 _public function_ `virtual void GetGraphNodePosition(FName InGraphName, int32& NodePosX, int32& NodePosY) const` — Gets the canvas position for the graph node representing this object.
- L52 _public function_ `virtual void OnGraphNodeMoved(FName InGraphName, int32 NodePosX, int32 NodePosY, bool bMarkDirty)` — Called to save the canvas position of the graph node representing this object.
- L57 _public function_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const` — Gets optional APIs support flags.
- L59 _public function_ `bool HasAnySupportFlags(FName InGraphName, EObjectTreeGraphObjectSupportFlags InFlags) const` — Gets whether this object supports the given optional API.
- L62 _public function_ `virtual const FString& GetGraphNodeCommentText(FName InGraphName) const` — Gets the graph node's comment text.
- L64 _public function_ `virtual void OnUpdateGraphNodeCommentText(FName InGraphName, const FString& NewComment)` — Called to save a new comment text.
- L67 _public function_ `virtual void GetGraphNodeName(FName InGraphName, FText& OutName) const` — Gets the custom name for the graph node.
- L69 _public function_ `virtual void OnRenameGraphNode(FName InGraphName, const FString& NewName)` — Called to save a new custom name.

#### Free symbols / members of external scopes

- L31 _prototype_ `ENUM_CLASS_FLAGS(EObjectTreeGraphObjectSupportFlags);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/ObjectTreeGraphRootObject.h` (Public)


#### class `UObjectTreeGraphRootObject`  
`class UObjectTreeGraphRootObject : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IObjectTreeGraphRootObject`  
`class IObjectTreeGraphRootObject`  
_L16-30_
- L24 _public function_ `virtual void GetConnectableObjects(FName InGraphName, TSet<UObject*>& OutObjects) const`
- L25 _public function_ `virtual void AddConnectableObject(FName InGraphName, UObject* InObject)`
- L26 _public function_ `virtual void RemoveConnectableObject(FName InGraphName, UObject* InObject)`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/PersistentBlendStackCameraNode.h` (Public)


#### struct `UE::Cameras::FBlendStackCameraInsertParams`  
`struct FBlendStackCameraInsertParams`  
_L13-38_
- desc: Parameter structure for inserting a camera rig into a persistent blend stack.
- L16 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context within which a camera rig's node tree should run.
- L19 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The source camera rig asset to instantiate and push on the blend stack.
- L22 _public member_ `TObjectPtr<const UCameraRigTransition> TransitionOverride;` — A transition to use, instead of looking one up.
- L31 _public member_ `int32 StackOrder = 0;` — An ordering value for where to insert the camera rig in the stack. Higher values place the camera rig higher in the stack (i.e. evaluating later) Lower values place the camera rig lower in the stack (i.e. evluating earlier) Insertion of an equal pre-existing value will be done on top of (after) existing entries in the stack.
- L37 _public member_ `bool bForceInsert = false;` — Whether to force insert a new instance of the camera rig, even if there is already one in the stack with the same StackOrder.

#### struct `UE::Cameras::FBlendStackCameraRemoveParams`  
`struct FBlendStackCameraRemoveParams`  
_L45-64_
- desc: Parameter structure for removing a camera rig from a persistent blend stack. The camera rig to remove is identified first by a given ID or, if no ID is given, by finding a camera rig matching the provided EvaluationContext and CameraRig.
- L48 _public member_ `FBlendStackEntryID EntryID;` — The ID of the blend stack entry to remove.
- L51 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context within which the camera rig to remove is being run.
- L54 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The source camera rig asset used by the instanced to remove.
- L57 _public member_ `TObjectPtr<const UCameraRigTransition> TransitionOverride;` — A transition to use, instead of looking one up.
- L63 _public member_ `bool bRemoveImmediately = false;` — Whether to immediately remove the given camera rig instead of blending it out. Equivalent to passing a pop blend as the TransitionOverride.

#### class `UE::Cameras::FPersistentBlendStackCameraNodeEvaluator`  
`class FPersistentBlendStackCameraNodeEvaluator : public FBlendStackCameraNodeEvaluator`  
_L71-124_
- inherits: `FBlendStackCameraNodeEvaluator`
- desc: Evaluator for a persistent blend stack, i.e. a blend stack in which camera rigs blend additively on top of each other, but without automatically popping out any fully blended-out entries. This is a stack suitable for a "camera modifier stack" of sorts.
- L79 _public prototype_ `FBlendStackEntryID Insert(const FBlendStackCameraInsertParams& Params);` — Insert a new camera rig onto the blend stack.
- L82 _public prototype_ `void Remove(const FBlendStackCameraRemoveParams& Params);` — Remove an existing camera rig from the blend stack.
- L85 _public prototype_ `void RemoveAll(TSharedPtr<const FCameraEvaluationContext> InContext, bool bImmediately);` — Remove all existing camera rigs with the given context from the blend stack.
- L90 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FCameraNodeEvaluator interface.
- L94 _protected prototype_ `virtual void OnEntryReinitialized(int32 EntryIndex) override;` — FBlendStackCameraNodeEvaluator interface.
- L99 _private prototype_ `void InternalUpdate(TArrayView<FResolvedEntry> ResolvedEntries, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L101 _private prototype_ `void RemoveEntry(int32 EntryIndex, const UCameraRigTransition* TransitionOverride, bool bImmediately);`
- L103 _private prototype_ `const UCameraRigTransition* FindEnterTransition(const FBlendStackCameraInsertParams& Params) const;`
- L104 _private prototype_ `const UCameraRigTransition* FindExitTransition(const FCameraRigEntry& Entry, const UCameraRigTransition* TransitionOverride) const;`
- L123 _private member_ `TArray<FCameraRigEntryExtraInfo> EntryExtraInfos;`

#### enum `UE::Cameras::FPersistentBlendStackCameraNodeEvaluator::EBlendStatus`  
`enum class EBlendStatus`  
_L108-113_
- L110 _public enumerator_ `None`
- L111 _public enumerator_ `BlendIn`
- L112 _public enumerator_ `BlendOut`

#### struct `UE::Cameras::FPersistentBlendStackCameraNodeEvaluator::FCameraRigEntryExtraInfo`  
`struct FCameraRigEntryExtraInfo`  
_L115-121_
- L117 _public member_ `int32 StackOrder = 0;`
- L118 _public member_ `EBlendStatus BlendStatus = EBlendStatus::None;`
- L119 _public member_ `bool bIsBlendFull = false;`
- L120 _public member_ `bool bIsBlendFinished = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/PostProcessSettingsCollection.h` (Public)


#### struct `UE::Cameras::FPostProcessSettingsCollection`  
`struct FPostProcessSettingsCollection`  
_L16-58_
- desc: A class that can collect post-process settings, combining them with their associated blend weights.
- L19 _public function_ `FPostProcessSettings& Get()` — Gets the effective post-process settings.
- L22 _public function_ `const FPostProcessSettings& Get() const` — Gets the effective post-process settings.
- L25 _public prototype_ `void Reset();` — Resets this collection to the default post-process settings.
- L30 _public prototype_ `void OverrideAll(const FPostProcessSettingsCollection& OtherCollection);` — Overwrites the post-process settings in this collection with the values in the other.
- L37 _public prototype_ `void OverrideChanged(const FPostProcessSettingsCollection& OtherCollection);` — Overwrites the post-process settings in this collection with any changed values in the other. Changed values are those whose bOverride_Xxx flag is true. Functionally equivalent to LerpAll with a blend factor of 100%.
- L38 _public prototype_ `void OverrideChanged(const FPostProcessSettings& OtherPostProcessSettings);`
- L45 _public prototype_ `void LerpAll(const FPostProcessSettingsCollection& ToCollection, float BlendFactor);` — Interpolates the post-process settings towards the values in the given other collection. All values are interpolated if either post-process settings have the bOverride_Xxx flag set. This means that some values will interpolate to and/or from default values.
- L46 _public prototype_ `void LerpAll(const FPostProcessSettings& ToPostProcessSettings, float BlendFactor);`
- L49 _public prototype_ `void Serialize(FArchive& Ar);` — Serializes this collection into the given archive.
- L53 _private prototype_ `void InternalLerp(const FPostProcessSettings& ToPostProcessSettings, float BlendFactor);`
- L57 _private member_ `FPostProcessSettings PostProcessSettings;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/RootCameraNode.h` (Public)


#### class `URootCameraNode`  
`class URootCameraNode : public UCameraNode`  
_L21-24_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UCameraNode`
- desc: The base class for a camera node that can act as the root of the camera system evaluation.

#### struct `UE::Cameras::FActivateCameraRigParams`  
`struct FActivateCameraRigParams`  
_L38-57_
- desc: Parameter structure for activating a new camera rig.
- L41 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context in which the camera rig runs.
- L44 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The source camera rig asset that will be instantiated.
- L47 _public member_ `TObjectPtr<const UCameraRigTransition> TransitionOverride;` — A transition to use, instead of looking one up.
- L50 _public member_ `ECameraRigLayer Layer = ECameraRigLayer::Main;` — The evaluation layer on which to instantiate the camera rig.
- L53 _public member_ `int32 OrderKey = 0;` — If the given layer supports ordering, this specifies a priority key.
- L56 _public member_ `bool bForceActivate = false;` — Whether a new instance of the camera rig should be created, even if it is already active in the given layer.

#### struct `UE::Cameras::FDeactivateCameraRigParams`  
`struct FDeactivateCameraRigParams`  
_L62-81_
- desc: Parameter structure for deactivating a running camera rig.
- L65 _public member_ `FCameraRigInstanceID InstanceID;` — The instance to deactivate.
- L68 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context in which the camera rig runs.
- L71 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The source camera rig asset that was instantiated.
- L74 _public member_ `ECameraRigLayer Layer = ECameraRigLayer::Main;` — The evaluation layer on which the camera rig is running.
- L77 _public member_ `TObjectPtr<const UCameraRigTransition> TransitionOverride;` — If deactivation uses a transition (e.g. blending out), then force using the given transition.
- L80 _public member_ `bool bDeactiveImmediately = false;` — If deactivation can take time (e.g. blending out), then force an immediate deactivation.

#### struct `UE::Cameras::FSingleCameraRigHierarchyBuildParams`  
`struct FSingleCameraRigHierarchyBuildParams`  
_L86-93_
- desc: Parameter structure for building a single camera rig hierarchy.
- L89 _public member_ `FCameraRigEvaluationInfo CameraRigInfo;` — The camera rig to build the hierachy for.
- L92 _public member_ `FName CameraRigRangeName = TEXT("Act` — The name of the range to tag for the camera rig's nodes.

#### struct `UE::Cameras::FSingleCameraRigEvaluationParams`  
`struct FSingleCameraRigEvaluationParams`  
_L98-105_
- desc: Parameter structure for evaluating a single camera rig.
- L101 _public member_ `FCameraNodeEvaluationParams EvaluationParams;` — The evaluation parameters.
- L104 _public member_ `FCameraRigEvaluationInfo CameraRigInfo;` — The camera rig to evaluate.

#### class `UE::Cameras::FRootCameraNodeEvaluator`  
`class FRootCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L112-226_
- inherits: `FCameraNodeEvaluator`
- desc: Base class for the evaluator of a root camera node.
- L120 _public prototype_ `FCameraRigInstanceID ActivateCameraRig(const FActivateCameraRigParams& Params);` — Activates a camera rig. What it means to activate a camera rig may differ depending on the layer it runs on.
- L126 _public prototype_ `void DeactivateCameraRig(const FDeactivateCameraRigParams& Params);` — Deactivates a camera rig. What it means to deactivate a camera rig may differ depending on the layer it runs on.
- L129 _public prototype_ `void DeactivateAllCameraRigs(TSharedPtr<const FCameraEvaluationContext> InContext, bool bImmediately);` — Deactivates all camera rigs with the given evaluation context.
- L132 _public prototype_ `void ExecuteCameraDirectorRequest(const FCameraRigActivationDeactivationRequest& Request);` — Execute a request to activate or deactivate a camera rig.
- L135 _public prototype_ `void GetActiveCameraRigInfo(FCameraRigEvaluationInfo& OutCameraRigInfo) const;` — Gets information about the active camera rig in the main layer.
- L138 _public prototype_ `void GetCameraRigInfo(const FCameraRigInstanceID InstanceID, FCameraRigEvaluationInfo& OutCameraRigInfo) const;` — Gets information about a specified camera rig.
- L141 _public prototype_ `bool HasAnyActiveCameraRig() const;` — Gets whether any camera rig is running in the main layer.
- L144 _public prototype_ `bool HasAnyRunningCameraRig(TSharedPtr<const FCameraEvaluationContext> InContext) const;` — Gets whether any camera rig is running with the given context in the main layer.
- L147 _public prototype_ `const FCameraVariableTable* GetBlendedParameters() const;` — Gets the variable table containing the blended camera object interfaces parameters.
- L150 _public prototype_ `const FCameraNodeEvaluationResult& GetPreVisualLayerResult() const;` — Returns the evaluation result without the contribution of the visual layer.
- L158 _public prototype_ `void BuildSingleCameraRigHierarchy(const FSingleCameraRigHierarchyBuildParams& Params, FCameraNodeEvaluatorHierarchy& OutHierarchy);` — Builds the hierarchy of the system for a given single camera rig. This is expected to return the nodes of all the layers, except for the main layer which should only have the nodes of the given camera rig (i.e. it shouldn't have nodes of other currently active camera rigs).
- L165 _public prototype_ `void RunSingleCameraRig(const FSingleCameraRigEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — Evaluates a single camera rig. This is expected to run all layers as usual, except for the main layer which should only run the given camera rig instead.
- L168 _public prototype_ `TSharedPtr<FCameraActionScope> GetActiveCameraRigActionScope(bool bCreateIfNeeded = false);` — Gets the action scope for the active camera rig in the main layer.
- L171 _public function_ `FOnRootCameraNodeCameraRigEvent& OnCameraRigEvent()` — Gets the delegate for camera rig events.
- L176 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FCameraNodeEvaluator interface.
- L181 _protected function_ `virtual FCameraRigInstanceID OnActivateCameraRig(const FActivateCameraRigParams& Params)` — Activates a camera rig.
- L184 _protected function_ `virtual void OnDeactivateCameraRig(const FDeactivateCameraRigParams& Params)` — Deactivates a camera rig.
- L187 _protected function_ `virtual void OnDeactivateAllCameraRigs(TSharedPtr<const FCameraEvaluationContext> InContext, bool bImmediately)` — Deactivates all camera rigs with the given evaluation context.
- L190 _protected function_ `virtual void OnGetActiveCameraRigInfo(FCameraRigEvaluationInfo& OutCameraRigInfo) const` — Gets information about the active camera rig in the main layer.
- L193 _protected function_ `virtual bool OnHasAnyRunningCameraRig(TSharedPtr<const FCameraEvaluationContext> InContext) const` — Gets whether any camera rig is running with the given context in the main layer.
- L196 _protected function_ `virtual void OnGetCameraRigInfo(const FCameraRigInstanceID InstanceID, FCameraRigEvaluationInfo& OutCameraRigInfo) const` — Gets information about a specified camera rig.
- L199 _protected function_ `virtual const FCameraVariableTable* OnGetBlendedParameters() const` — Gets the variable table containing the blended camera object interfaces parameters.
- L202 _protected function_ `virtual void OnBuildSingleCameraRigHierarchy(const FSingleCameraRigHierarchyBuildParams& Params, FCameraNodeEvaluatorHierarchy& OutHierarchy)` — Builds the hierarchy of the system for a given single camera rig.
- L205 _protected function_ `virtual void OnRunSingleCameraRig(const FSingleCameraRigEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult)` — Evaluates a single camera rig. See comments on RunSingleCameraRig.
- L208 _protected function_ `virtual TSharedPtr<FCameraActionScope> OnGetActiveCameraRigActionScope(bool bCreateIfNeeded)` — Gets the action scope for the active camera rig in the main layer.
- L212 _protected prototype_ `void SetPreVisualLayerResult(const FCameraNodeEvaluationResult& InResult);`
- L214 _protected prototype_ `void BroadcastCameraRigEvent(const FRootCameraNodeCameraRigEvent& InEvent) const;`
- L219 _private member_ `FCameraSystemEvaluator* OwningEvaluator = nullptr;` — The camera system that owns this root node.
- L222 _private member_ `FCameraNodeEvaluationResult PreVisualResult;` — Evaluation result before the contribution of the visual layer.
- L225 _private member_ `FOnRootCameraNodeCameraRigEvent OnCameraRigEventDelegate;` — The delegate to notify when an event happens.

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Cameras` (scope `UE`)
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRootCameraNodeCameraRigEvent, const FRootCameraNodeCameraRigEvent&);`
- L107 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRootCameraNodeCameraRigEvent, const FRootCameraNodeCameraRigEvent&);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/RootCameraNodeCameraRigEvent.h` (Public)


#### enum `UE::Cameras::ERootCameraNodeCameraRigEventType`  
`enum class ERootCameraNodeCameraRigEventType`  
_L15-21_
- desc: The type of root node event.
- L18 _public enumerator_ `Activated` — A camera rig was activated.
- L20 _public enumerator_ `Deactivated` — A camera rig was deactivated.

#### struct `UE::Cameras::FRootCameraNodeCameraRigEvent`  
`struct FRootCameraNodeCameraRigEvent`  
_L26-36_
- desc: A structure describing an event on a root node.
- L29 _public member_ `ERootCameraNodeCameraRigEventType EventType = ERootCameraNodeCameraRigEventType::Activated;` — The type of event.
- L31 _public member_ `ECameraRigLayer EventLayer = ECameraRigLayer::Main;` — The layer on which the event happened.
- L33 _public member_ `FCameraRigEvaluationInfo CameraRigInfo;` — The evaluation information of the associated camera rig.
- L35 _public member_ `TObjectPtr<const UCameraRigTransition> Transition;` — If a camera rig was activated, the transition used to activate it, if any.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/ShakeCameraNode.h` (Public)


#### class `UShakeCameraNode`  
`class UShakeCameraNode : public UCameraNode`  
_L15-18_
- reflection: `UCLASS(MinimalAPI, Abstract, meta=(CameraNodeCategories="Shakes"))`
- inherits: `UCameraNode`
- desc: Base class for shake camera nodes.

#### struct `UE::Cameras::FCameraNodeShakeParams`  
`struct FCameraNodeShakeParams`  
_L26-40_
- desc: Parameters for applying a shake to a camera result.
- L28 _public function_ `FCameraNodeShakeParams(const FCameraNodeEvaluationParams& InChildParams) : ChildParams(InChildParams)`
- L33 _public member_ `const FCameraNodeEvaluationParams& ChildParams;` — The parameters that the shake received during the evaluation.
- L35 _public member_ `float ShakeScale = 1.f;` — The intensity to use for the camera shake.
- L37 _public member_ `ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal;` — The play space to modify the result by
- L39 _public member_ `FMatrix UserPlaySpaceMatrix = FMatrix::Identity;` — The custom space to use for the shake. Only used when PlaySpace is UserDefined.

#### struct `UE::Cameras::FCameraNodeShakeDelta`  
`struct FCameraNodeShakeDelta`  
_L45-60_
- desc: A structure that describes a group of offset values representing a shake.
- L48 _public member_ `FVector3d Location = FVector3d::ZeroVector;` — Position shake, which will be scaled and applied as a delta in the desired space.
- L51 _public member_ `FRotator3d Rotation = FRotator3d::ZeroRotator;` — Rotation shake, which will be scaled and applied as a delta in the desired space.
- L54 _public member_ `float FieldOfView = 0.f;` — Field of view shake, which will be scaled and applied as a delta.
- L59 _public prototype_ `void Combine(const FCameraNodeShakeDelta& Other, float OtherScale = 1.f);` — Combines this shake delta with another, optionally scaled, shake delta.

#### struct `UE::Cameras::FCameraNodeShakeResult`  
`struct FCameraNodeShakeResult`  
_L65-91_
- desc: Result structure for applying a shake to a camera result.
- L67 _public function_ `FCameraNodeShakeResult(FCameraNodeEvaluationResult& InShakenResult) : ShakenResult(InShakenResult)`
- L72 _public member_ `FCameraNodeEvaluationResult& ShakenResult;` — The result that should be shaken.
- L82 _public member_ `FCameraNodeShakeDelta ShakeDelta;` — Delta values that should be applied to the shaken result. These are simpler to set and combine inside camera shake nodes, since they will be applied with the correct scale and in the correct space at the end. By comparison, writing to the ShakenResult field directly requires taking into account all the parameters first (see FCameraNodeShakeParams).
- L85 _public member_ `float ShakeTimeLeft = 0.f;` — The time left in this shake, if applicable. Negative values indicate an infinite shake.
- L90 _public prototype_ `void ApplyDelta(const FCameraNodeShakeParams& Params);` — Apply the delta values to the shaken result.

#### struct `UE::Cameras::FCameraNodeShakeRestartParams`  
`struct FCameraNodeShakeRestartParams`  
_L96-98_
- desc: Parameters for restarting a running camera shake.

#### class `UE::Cameras::FShakeCameraNodeEvaluator`  
`class FShakeCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L100-122_
- inherits: `FCameraNodeEvaluator`
- L107 _public prototype_ `void ShakeResult(const FCameraNodeShakeParams& Params, FCameraNodeShakeResult& OutResult);` — Applies the shake to the given result.
- L110 _public prototype_ `void RestartShake(const FCameraNodeShakeRestartParams& Params);` — Restart a running camera shake.
- L115 _protected function_ `virtual void OnShakeResult(const FCameraNodeShakeParams& Params, FCameraNodeShakeResult& OutResult)` — Applies the shake to the given result.
- L118 _protected function_ `virtual void OnSetShakeScale(float InShakeScale)` — Called when the intensity of the shake changes, but before ShakeScale is set.
- L121 _protected function_ `virtual void OnRestartShake(const FCameraNodeShakeRestartParams& Params)` — Restart a running camera shake.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Cameras` (scope `UE`)
- L131 _macro_ `#define UE_DECLARE_SHAKE_CAMERA_NODE_EVALUATOR(ApiDeclSpec, ClassName)\` — Macros for declaring and defining new shake node evaluators. They are the same as the base ones for generic node evaluators, but the first one prevents you from having to specify FShakeCameraNodeEvaluator as the base class, which saves a little bit of typing.
- L134 _macro_ `#define UE_DECLARE_SHAKE_CAMERA_NODE_EVALUATOR_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L137 _macro_ `#define UE_DEFINE_SHAKE_CAMERA_NODE_EVALUATOR(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Core/TransientBlendStackCameraNode.h` (Public)


#### struct `UE::Cameras::FBlendStackCameraPushParams`  
`struct FBlendStackCameraPushParams`  
_L19-32_
- desc: Parameter structure for pushing a camera rig onto a transient blend stack.
- L22 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context within which a camera rig's node tree should run.
- L25 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The source camera rig asset to instantiate and push on the blend stack.
- L28 _public member_ `TObjectPtr<const UCameraRigTransition> TransitionOverride;` — A transition to use, instead of looking one up.
- L31 _public member_ `bool bForcePush = false;` — Whether to force pushing a new instance of the camera rig, even if it is currently active.

#### struct `UE::Cameras::FBlendStackCameraFreezeParams`  
`struct FBlendStackCameraFreezeParams`  
_L37-47_
- desc: Parameter structure for freezing a camera rig inside a transient blend stack.
- L40 _public member_ `FBlendStackEntryID EntryID;` — The ID of the blend stack entry to freeze.
- L43 _public member_ `TSharedPtr<const FCameraEvaluationContext> EvaluationContext;` — The evaluation context within which a camera rig's node tree is running.
- L46 _public member_ `TObjectPtr<const UCameraRigAsset> CameraRig;` — The source camera rig asset that is running.

#### class `UE::Cameras::FTransientBlendStackCameraNodeEvaluator`  
`class FTransientBlendStackCameraNodeEvaluator : public FBlendStackCameraNodeEvaluator`  
_L55-134_
- inherits: `FBlendStackCameraNodeEvaluator`
- desc: Evaluator for a transient blend stack, i.e. a blend stack where camera rigs evaluate together, blending together and blend out those below them, which are then automatically popped out of the stack. This is a stack suitable for "camera modes" of sorts.
- L64 _public prototype_ `FBlendStackEntryID Push(const FBlendStackCameraPushParams& Params);` — Push a new camera rig onto the blend stack.
- L67 _public prototype_ `void Freeze(const FBlendStackCameraFreezeParams& Params);` — Freeze a camera rig.
- L70 _public prototype_ `void FreezeAll(TSharedPtr<const FCameraEvaluationContext> EvaluationContext);` — Freeze all camera rigs that belong to a given evaluation context.
- L73 _public function_ `const FCameraVariableTable& GetBlendedParameters() const` — Gets the variable table containing the blended camera object interfaces parameters.
- L76 _public prototype_ `TSharedPtr<FCameraActionScope> GetActiveCameraRigActionScope(bool bCreateIfNeeded = false);` — Gets the active camera rig's action scope, optionally creating one if needed.
- L81 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FCameraNodeEvaluator interface.
- L82 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L83 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L84 _protected prototype_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector) override;`
- L87 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L92 _protected prototype_ `virtual void OnEntryReinitialized(int32 EntryIndex) override;` — FBlendStackCameraNodeEvaluator interface.
- L98 _private prototype_ `void InternalPreBlendPrepare(TArrayView<FResolvedEntry> ResolvedEntries, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — Update methods.
- L99 _private prototype_ `void InternalPreBlendExecute(TArrayView<FResolvedEntry> ResolvedEntries, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L100 _private prototype_ `void InternalUpdate(TArrayView<FResolvedEntry> ResolvedEntries, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L101 _private prototype_ `void InternalPostBlendExecute(TArrayView<FResolvedEntry> ResolvedEntries, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L102 _private prototype_ `void InternalRunFinished(FCameraNodeEvaluationResult& OutResult);`
- L104 _private prototype_ `const UCameraRigTransition* FindTransition(const FBlendStackCameraPushParams& Params) const;`
- L106 _private prototype_ `FBlendStackEntryID PushNewEntry(const FBlendStackCameraPushParams& Params, const UCameraRigTransition* Transition);`
- L107 _private prototype_ `FBlendStackEntryID PushMergedEntry(const FBlendStackCameraPushParams& Params, const UCameraRigTransition* Transition);`
- L127 _private member_ `TArray<FCameraRigEntryExtraInfo> EntryExtraInfos;`
- L130 _private member_ `FCameraVariableTable PreBlendVariableTable;` — Variable table for pre-blending.
- L133 _private member_ `TSharedPtr<FCameraParameterSetterService> ParameterSetterService;` — Cached pointer to the parameter setter service.

#### struct `UE::Cameras::FTransientBlendStackCameraNodeEvaluator::FCameraRigEntryExtraInfo`  
`struct FCameraRigEntryExtraInfo`  
_L112-125_
- desc: Extra blending-related info for each camera rig entry.
- L115 _public member_ `TSharedPtr<FCameraActionScope> ActionScope;` — Action scope for this entry.
- L118 _public member_ `bool bInputRunThisFrame = false;` — Whether input slots were run.
- L120 _public member_ `bool bBlendRunThisFrame = false;` — Whether the blend node was run.
- L122 _public member_ `bool bHasPreBlendedParameters = false;` — Whether this camera rig has any parameters to pre-blend.
- L124 _public member_ `bool bIsPreBlendFull = false;` — Whether this camera rig's pre-blend was full and finished this frame.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Curves/CameraRotatorCurve.h` (Public)


#### struct `FCameraRotatorCurve`  
`struct FCameraRotatorCurve`  
_L13-22_
- reflection: `USTRUCT()`
- L18 _public member_ `FRichCurve Curves[3];` — `UPROPERTY()`
- L20 _public prototype_ `FRotator GetValue(float InTime) const;`
- L21 _public prototype_ `bool HasAnyData() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Curves/CameraSingleCurve.h` (Public)


#### struct `FCameraSingleCurve`  
`struct FCameraSingleCurve`  
_L13-22_
- reflection: `USTRUCT()`
- L18 _public member_ `FRichCurve Curve;` — `UPROPERTY()`
- L20 _public prototype_ `float GetValue(float InTime) const;`
- L21 _public prototype_ `bool HasAnyData() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Curves/CameraVectorCurve.h` (Public)


#### struct `FCameraVectorCurve`  
`struct FCameraVectorCurve`  
_L13-22_
- reflection: `USTRUCT()`
- L18 _public member_ `FRichCurve Curves[3];` — `UPROPERTY()`
- L20 _public prototype_ `FVector GetValue(float InTime) const;`
- L21 _public prototype_ `bool HasAnyData() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/BlendStacksCameraDebugBlock.h` (Public)


#### class `UE::Cameras::FBlendStacksCameraDebugBlock`  
`class FBlendStacksCameraDebugBlock : public FCameraDebugBlock`  
_L17-39_
- inherits: `FCameraDebugBlock`
- desc: Debug block that shows multiple blend stacks.
- L23 _public prototype_ `FBlendStacksCameraDebugBlock();`
- L29 _public prototype_ `void AddBlendStack(const FString& InBlendStackName, FBlendStackCameraDebugBlock* InDebugBlock);` — Adds the given blend stack block as a child, which will be rendered with the given title. The blend stack block can be obtained from the blend stack evaluator.
- L33 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L34 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L38 _private member_ `TArray<FString> BlendStackNames;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugBlock.h` (Public)


#### struct `UE::Cameras::FCameraDebugBlockDrawParams`  
`struct FCameraDebugBlockDrawParams`  
_L22-28_
- desc: Parameter structure for debug block drawing.
- L25 _public member_ `TSet<FString> ActiveCategories;` — The list of active debug categories.
- L27 _public prototype_ `bool IsCategoryActive(const FString& InCategory) const;`

#### struct `UE::Cameras::FCameraDebugBlockField`  
`struct FCameraDebugBlockField`  
_L34-42_
- desc: Metadata for a debug block's member field. This is mostly used for auto-serialization of debugging info.
- L36 _public prototype_ `virtual ~FCameraDebugBlockField() = default;`
- L37 _public prototype_ `virtual void SerializeField(FCameraDebugBlock* This, FArchive& Ar) = 0;`
- L39 _public member_ `FName FieldName;`
- L40 _public member_ `uint16 FieldIndex = 0;`
- L41 _public member_ `uint16 FieldOffset = 0;`

#### struct `UE::Cameras::TCameraDebugBlockField`  
`template<typename FieldType> struct TCameraDebugBlockField : FCameraDebugBlockField`  
_L48-61_
- inherits: `FCameraDebugBlockField`
- desc: Templated version of the debug block field.
- L50 _public function_ `TCameraDebugBlockField(const FName& InName, uint16 InOffset)`
- L56 _public function_ `virtual void SerializeField(FCameraDebugBlock* This, FArchive& Ar) override`

#### class `UE::Cameras::FCameraDebugBlock`  
`class FCameraDebugBlock`  
_L68-123_
- desc: Debug drawing structure responsible for displaying information about some aspect of the camera system evaluation. For instance, there is generally one debug block per camera node.
- L74 _public prototype_ `virtual ~FCameraDebugBlock() = default;`
- L77 _public prototype_ `void Attach(FCameraDebugBlock* InAttachment);` — Attaches a block to this block.
- L79 _public function_ `TArrayView<FCameraDebugBlock*> GetAttachments()` — Gets the list of blocks attached to this block.
- L82 _public prototype_ `void AddChild(FCameraDebugBlock* InChild);` — Adds a child block to this block.
- L84 _public function_ `TArrayView<FCameraDebugBlock*> GetChildren()` — Gets the children of this block.
- L87 _public prototype_ `void DebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer);` — Called to let this block display its information on screen.
- L90 _public prototype_ `void Serialize(FArchive& Ar);` — Serializes this debug block into a buffer, for recording/replaying purposes.
- L95 _protected function_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer)` — Called to let this block display its information on screen.
- L97 _protected function_ `virtual void OnPostDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer)` — Called after attached and children blocks' debug draw.
- L100 _protected function_ `virtual void OnSerialize(FArchive& Ar)` — Serializes this debug block into a buffer, for recording/replaying purposes.
- L104 _protected typedef_ `using FStaticFieldArray = TArray<FCameraDebugBlockField*>;`
- L107 _protected function_ `template<typename FieldType> static TCameraDebugBlockField<FieldType> CreateField(const FName& FieldName, uint16 FieldOffset)`
- L112 _protected function_ `static int32 RegisterField(FCameraDebugBlockField* InField, FStaticFieldArray& InStaticFields)`
- L120 _private typedef_ `using FRelatedDebugBlockArray = TArray<FCameraDebugBlock*>;`
- L121 _private member_ `FRelatedDebugBlockArray Attachments;`
- L122 _private member_ `FRelatedDebugBlockArray Children;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L129 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK(ApiDeclSpec, ClassName)\` — Macros for defining debug blocks.
- L132 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L135 _macro_ `#define UE_DEFINE_CAMERA_DEBUG_BLOCK(ClassName)\`
- L155 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK_START(ApiDeclSpec, ClassName)\` — Macros for defining "simple" debug blocks with primitive types as fields. This will setup debug block serialization automatically, compared to the macros above where you have to write your own OnSerialize(). Example: UE_DECLARE_CAMERA_DEBUG_BLOCK_START(MYMODULE_API, FMyDebugBlock) UE_DECLARE_CAMERA_DEBUG_BLOCK_FIELD(float, Something) UE_DECLARE_CAMERA_DEBUG_BLOCK_FIELD(bool, bSomethingElse) UE_DECLARE_CAMERA_DEBUG_BLOCK_END() UE_DEFINE_CAMERA_DEBUG_BLOCK_WITH_FIELDS(FMyDebugBlock)
- L177 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK_FIELD(FieldType, FieldName)\`
- L190 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK_END()\`
- L194 _macro_ `#define UE_DEFINE_CAMERA_DEBUG_BLOCK_WITH_FIELDS(ClassName)\`
- L201 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK_START(ApiDeclSpec, ClassName)` — Empty macros for shipping builds.
- L202 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK_FIELD(FieldType, FieldName)`
- L203 _macro_ `#define UE_DECLARE_CAMERA_DEBUG_BLOCK_END()`
- L204 _macro_ `#define UE_DEFINE_CAMERA_DEBUG_BLOCK_WITH_FIELDS(ClassName)`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugBlockBuilder.h` (Public)


#### enum `UE::Cameras::ECameraDebugBlockBuildVisitFlags`  
`enum class ECameraDebugBlockBuildVisitFlags`  
_L22-26_
- L24 _public enumerator_ `None`
- L25 _public enumerator_ `SkipChildren = 1 << 0`

#### struct `UE::Cameras::FCameraDebugBlockBuilder`  
`struct FCameraDebugBlockBuilder`  
_L32-122_
- desc: Builder class for camera debug drawing blocks.
- L37 _public prototype_ `FCameraDebugBlockBuilder(FCameraDebugBlockStorage& InStorage, FRootCameraDebugBlock& InRootBlock);` — Creates a new builder structure.
- L40 _public function_ `FCameraDebugBlockStorage& GetStorage() const` — Gets the storage used by this builder.
- L43 _public function_ `FRootCameraDebugBlock& GetRootDebugBlock() const` — Gets the root debug block.
- L46 _public function_ `FCameraDebugBlock& GetParentDebugBlock() const` — Gets the current parent debug block.
- L53 _public function_ `template<typename BlockType, typename ...ArgTypes> BlockType& BuildDebugBlock(ArgTypes&&... InArgs)` — Creates a new unassociated debug block. It won't render unless it's referenced by or parented under another debug block!
- L66 _public function_ `template<typename BlockType, typename ...ArgTypes> BlockType& AttachDebugBlock(ArgTypes&&... InArgs)` — Creates a new debug block and attaches it to the current active block. Attached debug blocks are rendered/not rendered along with their "anchor" debug block. This differs from children debug blocks which may be rendered/not rendered independently of their parent.
- L79 _public function_ `template<typename BlockType, typename ...ArgTypes> BlockType& StartChildDebugBlock(ArgTypes&& ...InArgs)` — Creates a new debug block and adds it to the current hierarhcy. This sets the new block as the "active" block, and adds it as a child of the previously active block.
- L87 _public prototype_ `void EndChildDebugBlock();` — Ends the currently active debug drawing block.
- L90 _public function_ `int32 GetHierarchyLevel() const` — Gets current hierarchy level.
- L98 _public prototype_ `void SkipChildren();` — Don't visit children node evaluators when building the hierarchy of debug blocks. This implies that a node evaluator will visit its children "manually", otherwise these children node evaluators won't have any debugging information available.
- L100 _public function_ `ECameraDebugBlockBuildVisitFlags GetVisitFlags() const` — Gets visiting flags.
- L102 _public prototype_ `void ResetVisitFlags();` — Resets visiting flags.
- L105 _public prototype_ `void StartParentDebugBlockOverride(FCameraDebugBlock& InNewParent);` — Temporarily overrides the attachment/children to work on the new parent.
- L107 _public prototype_ `void EndParentDebugBlockOverride();` — Ends a temporary attachment/children override.
- L111 _private prototype_ `void OnAttachDebugBlock(FCameraDebugBlock* InNewBlock);`
- L112 _private prototype_ `void OnStartChildDebugBlock(FCameraDebugBlock* InNewBlock);`
- L116 _private member_ `FCameraDebugBlockStorage& Storage;`
- L117 _private member_ `FRootCameraDebugBlock& RootBlock;`
- L118 _private member_ `TArray<FCameraDebugBlock*> CurrentHierarchy;`
- L120 _private member_ `ECameraDebugBlockBuildVisitFlags VisitFlags = ECameraDebugBlockBuildVisitFlags::None;`
- L121 _private member_ `int32 HierarchyOverrideStart = INDEX_NONE;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L27 _prototype_ `ENUM_CLASS_FLAGS(ECameraDebugBlockBuildVisitFlags);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugBlockFwd.h` (Public)


#### struct `UE::Cameras::FCameraDebugBlockBuildParams`  
`struct FCameraDebugBlockBuildParams`  
_L17-20_
- desc: Structure for creating the node evaluator's debug blocks.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugBlockStorage.h` (Public)


#### class `UE::Cameras::FCameraDebugBlockStorage`  
`class FCameraDebugBlockStorage : public TCameraObjectStorage<FCameraDebugBlock>`  
_L18-38_
- inherits: `TCameraObjectStorage<FCameraDebugBlock>`
- desc: A class responsible for storing a tree of debug blocks
- L22 _public typedef_ `using Super = TCameraObjectStorage<FCameraDebugBlock>;`
- L25 _public prototype_ `void DestroyDebugBlocks(bool bFreeAllocations = false);` — Destroy any allocated debug blocks.
- L29 _public prototype_ `template<typename BlockType, typename ...ArgTypes> BlockType* BuildDebugBlock(ArgTypes&&... InArgs);` — Build a new debug block inside this storage.
- L34 _public function_ `void* BuildDebugBlockUninitialized(uint32 Sizeof, uint32 Alignof)` — Internal API.
- L41 _function_ `template<typename BlockType, typename ...ArgTypes> BlockType* FCameraDebugBlockStorage::BuildDebugBlock(ArgTypes&&... InArgs)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugCategories.h` (Public)


#### struct `UE::Cameras::FCameraDebugCategories`  
`struct FCameraDebugCategories`  
_L18-26_
- desc: Standard debug categories for showing different "debug modes".
- L20 _public member_ `static const FString NodeTree;`
- L21 _public member_ `static const FString DirectorTree;`
- L22 _public member_ `static const FString BlendStacks;`
- L23 _public member_ `static const FString Services;`
- L24 _public member_ `static const FString PoseStats;`
- L25 _public member_ `static const FString Viewfinder;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugClock.h` (Public)


#### struct `UE::Cameras::FCameraDebugClockDrawParams`  
`struct FCameraDebugClockDrawParams`  
_L26-46_
- desc: Parameter structure for drawing a debug clock.
- L28 _public prototype_ `FCameraDebugClockDrawParams();`
- L31 _public member_ `FVector2f ClockPosition;` — The position of the clock card on screen.
- L33 _public member_ `FVector2f ClockSize;` — The total size of the clock card on screen.
- L35 _public member_ `FLinearColor ClockBackgroundColor;` — The color of the clock card's background.
- L38 _public member_ `FText ClockName;` — The name of the clock, displayed at the bottom of the card.
- L40 _public member_ `FLinearColor ClockNameColor;` — The color of the clock name text.
- L43 _public member_ `FLinearColor ClockFaceColor;` — The color of the clock face circle.
- L45 _public member_ `FLinearColor ClockValueLineColor;` — The color of the arrow inside the clock.

#### class `UE::Cameras::Internal::FCameraDebugClockRenderer`  
`class FCameraDebugClockRenderer`  
_L51-70_
- L55 _public prototype_ `FCameraDebugClockRenderer(FCanvas* InCanvas, const FCameraDebugClockDrawParams& InDrawParams);`
- L57 _public prototype_ `void DrawVectorClock(const FVector2d& Value, double MaxLength) const;`
- L58 _public prototype_ `void DrawAngleClock(double Angle) const;`
- L62 _private prototype_ `void DrawFrame() const;`
- L63 _private prototype_ `void DrawCurrentValue(const FText& CurrentValueStr) const;`
- L64 _private prototype_ `void GetClockFaceParams(FVector2f& OutClockCenter, double& OutClockRadius) const;`
- L68 _private member_ `FCanvas* Canvas = nullptr;`
- L69 _private member_ `FCameraDebugClockDrawParams DrawParams;`

#### class `UE::Cameras::FCameraDebugClock`  
`class FCameraDebugClock`  
_L77-126_
- desc: A debug clock, for showing a real-time angle or 2D vector in a graphical way.
- L86 _public prototype_ `void Update(double InAngle);` — Update the clock with the given angle. The clock's arrow will reach the edge of the clock face and oriented according to this angle, relative to the direction pointing straight upwards on the screen.
- L93 _public prototype_ `void Update(const FVector2d& InValue);` — Update the clock with the given 2D vector. The clock's arrow will represent this vector, relative to the direction pointing straight updwards on the screen.
- L98 _public prototype_ `void Draw(FCanvas* Canvas, const FCameraDebugClockDrawParams& DrawParams);` — Draw the debug clock onto the given canvas.
- L102 _public prototype_ `void Serialize(FArchive& Ar);`
- L121 _private typedef_ `using FVariant = TVariant<FVectorValue, FAngleValue>;`
- L122 _private member_ `FVariant Value;`

#### struct `UE::Cameras::FCameraDebugClock::FVectorValue`  
`struct FVectorValue`  
_L112-116_
- L114 _public member_ `FVector2d Vector = FVector2d::ZeroVector;`
- L115 _public member_ `double CurrentMaxLength = 0.f;`

#### struct `UE::Cameras::FCameraDebugClock::FAngleValue`  
`struct FAngleValue`  
_L117-120_
- L119 _public member_ `double Angle = 0.f;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Cameras` (scope `UE`)
- L48 _namespace_ `namespace Internal` (scope `UE::Cameras`)
- L104 _function_ `friend FCameraDebugClock& operator<< (FArchive& Ar, FCameraDebugClock& This)` (scope `UE::Cameras`)
- L128 _function_ `inline FCameraDebugClock::FVectorValue& operator<< (FArchive& Ar, FCameraDebugClock::FVectorValue& This)` (scope `UE::Cameras`)
- L135 _function_ `inline FCameraDebugClock::FAngleValue& operator<< (FArchive& Ar, FCameraDebugClock::FAngleValue& This)` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugColors.h` (Public)


#### class `UE::Cameras::FCameraDebugColors`  
`class FCameraDebugColors`  
_L17-78_
- desc: Standard debug drawing colors for the camera system.
- L22 _public member_ `FColor Title;` — Debug category titles and section titles.
- L24 _public member_ `FColor Default;` — Normal text.
- L26 _public member_ `FColor Passive;` — Unimportant text.
- L27 _public member_ `FColor VeryPassive;`
- L29 _public member_ `FColor Hightlighted;` — Important or notable text.
- L31 _public member_ `FColor Notice;` — Text with no specific importance, but that needs to be separate from the rest.
- L32 _public member_ `FColor Notice2;`
- L34 _public member_ `FColor Good;` — Positive text.
- L36 _public member_ `FColor Warning;` — Warning text.
- L38 _public member_ `FColor Error;` — Error text.
- L40 _public member_ `FColor Background;` — Background. Should only be used for the background tile.
- L45 _public prototype_ `static const FCameraDebugColors& Get();` — Gets the current color scheme.
- L48 _public prototype_ `static TOptional<FColor> GetFColorByName(const FString& InColorName);` — Gets a specific color by name on the current scheme.
- L51 _public prototype_ `static const FString& GetName();` — Gets the current color scheme name.
- L53 _public prototype_ `static void Set(const FString& InColorSchemeName);` — Sets the current color scheme.
- L55 _public prototype_ `static void Set(const FCameraDebugColors& InColorScheme);` — Sets the current color scheme.
- L58 _public prototype_ `static void RegisterColorScheme(const FString& InColorSchemeName, const FCameraDebugColors& InColorScheme);` — Registers a new color scheme.
- L60 _public prototype_ `static void GetColorSchemeNames(TArray<FString>& OutColorSchemeNames);` — Gets all registered color scheme names.
- L65 _public prototype_ `static void RegisterBuiltinColorSchemes();` — Internal API.
- L69 _private prototype_ `static void UpdateColorMap(const FCameraDebugColors& Instance);`
- L73 _private member_ `static FString CurrentColorSchemeName;`
- L74 _private member_ `static FCameraDebugColors CurrentColorScheme;`
- L75 _private member_ `static TMap<FString, FColor> ColorMap;`
- L77 _private member_ `static TMap<FString, FCameraDebugColors> ColorSchemes;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)
- L80 _prototype_ `FLinearColor LerpLinearColorUsingHSV( const FLinearColor& Start, const FLinearColor& End, int32 Increment, int32 TotalIncrements);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugGraph.h` (Public)


#### struct `UE::Cameras::FCameraDebugGraphDrawParams`  
`struct FCameraDebugGraphDrawParams`  
_L25-52_
- desc: Parameter structure for drawing a debug graph.
- L28 _public prototype_ `static float GetDefaultMaxHistoryTime();` — Gets the default maximum time shown on the graph.
- L30 _public prototype_ `FCameraDebugGraphDrawParams();`
- L33 _public member_ `FVector2f GraphPosition;` — The position of the graph card on screen.
- L35 _public member_ `FVector2f GraphSize;` — The total size of the graph card on screen.
- L37 _public member_ `FLinearColor GraphBackgroundColor;` — The color of the card's background.
- L40 _public member_ `FText GraphName;` — The name of the graph, displayed at the bottom of the card.
- L42 _public member_ `FLinearColor GraphNameColor;` — The color of the graph name text.
- L45 _public member_ `float HistoryTime;` — How far back in the past the graph goes.
- L47 _public member_ `TArray<FLinearColor, TInlineAllocator<4>> GraphLineColors;` — The colors for the lines of the graph.
- L51 _public prototype_ `template<uint8 NumValues> void SetupDefaultLineColors();` — Setup line colors using the active color scheme.
- L55 _function_ `template<uint8 NumValues> inline void FCameraDebugGraphDrawParams::SetupDefaultLineColors()`
- L66 _function_ `template<> inline void FCameraDebugGraphDrawParams::SetupDefaultLineColors<2>()`
- L75 _function_ `template<> inline void FCameraDebugGraphDrawParams::SetupDefaultLineColors<1>()`

#### class `UE::Cameras::Internal::FCameraDebugGraphRenderer`  
`class FCameraDebugGraphRenderer`  
_L85-110_
- L96 _public prototype_ `FCameraDebugGraphRenderer(FCanvas* InCanvas, const FCameraDebugGraphDrawParams& InDrawParams);`
- L98 _public prototype_ `void DrawEmptyFrame() const;`
- L99 _public prototype_ `void DrawFrame(TArrayView<float> CurrentValues) const;`
- L100 _public prototype_ `void DrawGraphLine(const FLineDrawParams& LineDrawParams, TStridedView<float> Times, TStridedView<float> Values) const;`
- L104 _private prototype_ `void DrawFrameImpl() const;`
- L108 _private member_ `FCanvas* Canvas = nullptr;`
- L109 _private member_ `FCameraDebugGraphDrawParams DrawParams;`

#### struct `UE::Cameras::Internal::FCameraDebugGraphRenderer::FLineDrawParams`  
`struct FLineDrawParams`  
_L89-94_
- L91 _public member_ `FLinearColor LineColor;`
- L92 _public member_ `float MaxValue;`
- L93 _public member_ `float MinValue;`

#### struct `UE::Cameras::TCameraDebugGraphEntry`  
`template<uint8 NumValues> struct TCameraDebugGraphEntry`  
_L118-185_
- desc: An entry on a debug graph, defined by a timestamp and one or more graph values.
- L121 _public member_ `float Time;` — The absolute time of the entry, from an arbitrary start time.
- L123 _public member_ `float Values[NumValues];` — The values of each line on the owning graph.
- L126 _public prototype_ `TCameraDebugGraphEntry() = default;` — Creates a new uninitialized entry.
- L129 _public function_ `TCameraDebugGraphEntry(EForceInit) : Time(0)` — Creates new entry, zero-initialized.
- L140 _public function_ `template<typename... InValueTypes> TCameraDebugGraphEntry(float InTime, float InFirstValue, InValueTypes... InOtherValues) : Time(InTime)` — Creates a new entry given an absolute time and some graph values.
- L148 _public function_ `template<typename... InValueTypes> void SetValues(float InFirstValue, InValueTypes... InOtherValues)` — Sets the values on this entry.
- L155 _public function_ `void Serialize(FArchive& Ar)`
- L173 _private function_ `template<uint8 InValueIndex, typename... InValueTypes> void SetValues(float InNextValue, InValueTypes... InOtherValues)`
- L181 _private function_ `template<uint8 InEndIndex> void SetValues()`

#### class `UE::Cameras::TCameraDebugGraph`  
`template<uint8 NumValues> class TCameraDebugGraph`  
_L193-340_
- desc: A debug graph, showing one or more lines. The lines progress as new timestamped values are added to the graph, with older values being discarded when they go past the maximum history time of the grpah.
- L195 _private typedef_ `using FGraphEntry = TCameraDebugGraphEntry<NumValues>;`
- L200 _public function_ `TCameraDebugGraph()` — Creates a new debug graph.
- L212 _public function_ `template<typename... InValueTypes> void Add(float InDeltaTime, InValueTypes... InValues)` — Adds a new entry to the graph, timestamped relative to the last added entry. @param InDeltaTime  The delta-time elapsed since the last entry was added. @param InValues     The values for the new entry.
- L221 _public function_ `void Draw(FCanvas* InCanvas, const FCameraDebugGraphDrawParams& InDrawParams)` — Draw this debug graph to the given canvas.
- L260 _public function_ `void Serialize(FArchive& Ar)`
- L275 _private function_ `void Add(const FGraphEntry& InEntry)`
- L280 _private function_ `float GetNewEntryTime(float InDeltaTime) const`
- L289 _private function_ `void Update(float InMaxHistoryTime)`
- L336 _private member_ `float CurrentMinValue = 0;`
- L337 _private member_ `float CurrentMaxValue = 0;`
- L339 _private member_ `TArray<FGraphEntry> Entries;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)
- L20 _externvar_ `extern float GGameplayCamerasDebugBackgroundOpacity;` (scope `UE::Cameras`)
- L82 _namespace_ `namespace Internal` (scope `UE::Cameras`)
- L164 _function_ `friend TCameraDebugGraphEntry<NumValues>& operator<< (FArchive& Ar, TCameraDebugGraphEntry<NumValues>& This)` (scope `UE::Cameras`)
- L267 _function_ `friend TCameraDebugGraph<NumValues>& operator<< (FArchive& Ar, TCameraDebugGraph<NumValues>& This)` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDebugRenderer.h` (Public)


#### enum `UE::Cameras::ECameraDebugDrawVisitFlags`  
`enum class ECameraDebugDrawVisitFlags`  
_L30-35_
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `SkipAttachedBlocks = 1 << 0`
- L34 _public enumerator_ `SkipChildrenBlocks = 1 << 1`

#### class `UE::Cameras::FCameraDebugRenderer`  
`class FCameraDebugRenderer`  
_L41-223_
- desc: Utility class for camera-related debug drawing.
- L46 _public prototype_ `FCameraDebugRenderer(UWorld* InWorld, UCanvas* InCanvasObject, bool bInIsExternalRendering = false);` — Creates a new debug renderer.
- L48 _public prototype_ `FCameraDebugRenderer(UWorld* InWorld, const FSceneView* InSceneView, FCanvas* InCanvas, bool bInIsExternalRendering = false);` — Creates a new debug renderer.
- L50 _public prototype_ `~FCameraDebugRenderer();` — Destroys the debug renderer.
- L53 _public function_ `bool IsExternalRendering() const` — Whether we are looking at the camera system from the "outside".
- L55 _public prototype_ `void BeginDrawing();`
- L56 _public prototype_ `void EndDrawing();`
- L59 _public prototype_ `void AddText(const FString& InString);` — Adds text to the text wall.
- L60 _public prototype_ `void AddText(const TCHAR* Fmt, ...);`
- L67 _public prototype_ `bool NewLine(bool bSkipIfEmptyLine = false);` — Move to a new line on the text wall. @return Whether a new line was added.
- L70 _public prototype_ `FColor GetTextColor() const;` — Gets the current text color.
- L72 _public prototype_ `FColor SetTextColor(const FColor& Color);` — Sets the text color for further calls. Returns the previous color.
- L75 _public prototype_ `void AddIndent();` — Increases the indent of the next text wall entry. This will make a new line.
- L77 _public prototype_ `void RemoveIndent();` — Decreases the indent of the next text wall entry. This will make a new line.
- L85 _public prototype_ `void DrawClock(FCameraDebugClock& InClock, const FText& InClockName);` — Draw a debug clock showing an angle or 2D vector at the next position available for a "card" debug item.
- L92 _public prototype_ `template<uint8 NumValues> void DrawGraph(TCameraDebugGraph<NumValues>& InGraph, const FText& InGraphName);` — Draw a debug graph showing one or more graph lines at the next position available for a "card" debug item.
- L97 _public prototype_ `void DrawCameraPose(const FCameraPose& InCameraPose, const FLinearColor& LineColor, float CameraSize = 0.f);` — Draws the given camera pose using the DrawCamera method.
- L102 _public prototype_ `void Draw2DPointCross(const FVector2D& Location, float CrossSize, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 2D cross at a point.
- L104 _public prototype_ `void Draw2DLine(const FVector2D& Start, const FVector2D& End, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 2D line.
- L106 _public prototype_ `void Draw2DBox(const FBox2D& Box, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 2D box.
- L108 _public prototype_ `void Draw2DBox(const FVector2D& BoxPosition, const FVector2D& BoxSize, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 2D box.
- L110 _public prototype_ `void Draw2DCircle(const FVector2D& Center, float Radius, const FLinearColor& LineColor, float LineThickness = 1.f, int32 NumSides = 0);` — Draws a 2D circle.
- L113 _public prototype_ `void DrawPoint(const FVector3d& Location, float PointSize, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 3D point.
- L115 _public prototype_ `void DrawLine(const FVector3d& Start, const FVector3d& End, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 3D line.
- L117 _public prototype_ `void DrawBox(const FVector3d& Center, const FVector3d& Size, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 3D box.
- L119 _public prototype_ `void DrawBox(const FTransform3d& Transform, const FVector3d& Size, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 3D box.
- L121 _public prototype_ `void DrawSphere(const FVector3d& Center, float Radius, int32 Segments, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 3D sphere.
- L123 _public prototype_ `void DrawDirectionalArrow(const FVector3d& Start, const FVector3d& End, float ArrowSize, const FLinearColor& LineColor, float LineThickness = 1.f);` — Draws a 3D arrow.
- L125 _public prototype_ `void DrawCamera(const FTransform3d& Transform, float HorizontalFieldOfView, float AspectRatio, float TargetDistance, const FLinearColor& LineColor, float CameraSize = 0.f, float LineThickness = 1.f);` — Draws a camera.
- L127 _public prototype_ `void DrawCoordinateSystem(const FVector3d& Location, const FRotator3d& Rotation, float AxesLength = 0.f);` — Draws a 3D coordinate system.
- L129 _public prototype_ `void DrawCoordinateSystem(const FTransform3d& Transform, float AxesLength = 0.f);` — Draws a 3D coordinate system.
- L131 _public prototype_ `void DrawText(const FVector3d& WorldPosition, const FString& Text, const FLinearColor& TextColor, UFont* TextFont = nullptr, float TextScale = 1.f);` — Draws text at a projected 3D position.
- L133 _public prototype_ `void DrawTextView(const FVector3d& WorldPosition, FStringView Text, const FLinearColor& TextColor, UFont* TextFont = nullptr, float TextScale = 1.f);` — Draws text at a projected 3D position.
- L135 _public prototype_ `void DrawText(const FVector3d& WorldPosition, const FVector2d& ScreenOffset, const FString& Text, const FLinearColor& TextColor, UFont* TextFont = nullptr, float TextScale = 1.f);` — Draws text at a projected 3D position, with an added screen-space offset.
- L137 _public prototype_ `void DrawTextView(const FVector3d& WorldPosition, const FVector2d& ScreenOffset, FStringView Text, const FLinearColor& TextColor, UFont* TextFont = nullptr, float TextScale = 1.f);` — Draws text at a projected 3D position, with an added screen-space offset.
- L142 _public prototype_ `void SkipAttachedBlocks();` — Request skipping drawing any blocks attached to the current block.
- L144 _public prototype_ `void SkipChildrenBlocks();` — Request skipping drawing any children blocks of the current block.
- L146 _public prototype_ `void SkipAllBlocks();` — Skip all related blocks (attached, children, etc.)
- L148 _public prototype_ `ECameraDebugDrawVisitFlags GetVisitFlags() const;` — Gets block visiting flags.
- L150 _public prototype_ `void ResetVisitFlags();` — Resets block visiting flags.
- L155 _public function_ `FCanvas* GetCanvas() const` — Gets the drawing canvas.
- L158 _public function_ `FVector2D GetCanvasSize() const` — Gets the size of the canvas.
- L161 _public function_ `bool HasCanvas() const` — Returns whether this renderer has a valid canvas to draw upon.
- L166 _public prototype_ `void DrawTextBackgroundTile(float Opacity);` — Internal API.
- L170 _private prototype_ `void Initialize(UWorld* InWorld, const FSceneView* InSceneView, FCanvas* InCanvas, bool bInIsExternalRendering);`
- L172 _private prototype_ `void AddTextFmtImpl(const TCHAR* Fmt, va_list Args);`
- L173 _private prototype_ `void AddTextImpl(const TCHAR* Buffer);`
- L175 _private prototype_ `float GetIndentMargin() const;`
- L176 _private prototype_ `void FlushText();`
- L178 _private prototype_ `FVector2f GetNextCardPosition();`
- L179 _private prototype_ `void GetNextDrawGraphParams(FCameraDebugGraphDrawParams& OutDrawParams, const FText& InGraphName);`
- L181 _private prototype_ `ULineBatchComponent* GetDebugLineBatcher() const;`
- L186 _private member_ `UWorld* World = nullptr;` — The world in which we might draw debug primitives.
- L188 _private member_ `FCanvas* Canvas = nullptr;` — The canvas used to draw the text wall.
- L190 _private member_ `const FSceneView* SceneView = nullptr;`
- L192 _private member_ `FVector2D CanvasSize;` — The size of the canvas.
- L194 _private member_ `bool bIsExternalRendering = false;` — Whether we are looking from the "outside" of the camera system.
- L197 _private member_ `FColor DrawColor;` — The draw color of the canvas.
- L200 _private member_ `const UFont* RenderFont;` — The font used to render the text wall.
- L202 _private member_ `int32 MaxCharHeight;` — The height of one line of the text wall.
- L205 _private member_ `TStringBuilder<512> Formatter;` — Temporary string formatter for variadic methods.
- L207 _private member_ `TStringBuilder<512> LineBuilder;` — String formatter for building a line up until the point it needs to be rendered.
- L210 _private member_ `int8 IndentLevel = 0;` — Current indent level.
- L212 _private member_ `FVector2f NextDrawPosition;` — The screenspace coordinates for the next block of text on the wall.
- L214 _private member_ `float RightMargin = 0;` — The maximum horizontal extent of the text rendered so far.
- L217 _private member_ `FVector2f NextCardPosition;` — The next available position for a card item.
- L219 _private member_ `int8 NextCardColumn;` — The index of the column for displaying the next card item.
- L222 _private member_ `ECameraDebugDrawVisitFlags VisitFlags;` — How to visit the next debug blocks.
- L226 _function_ `template<uint8 NumValues> inline void FCameraDebugRenderer::DrawGraph(TCameraDebugGraph<NumValues>& InGraph, const FText& InGraphName)`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDirectorDebugBlock.h` (Public)


#### class `UE::Cameras::FCameraDirectorDebugBlock`  
`class FCameraDirectorDebugBlock : public FCameraDebugBlock`  
_L20-42_
- inherits: `FCameraDebugBlock`
- desc: A debug block for a camera director entry in the evaluation stack.
- L26 _public prototype_ `void Initialize(TSharedPtr<FCameraEvaluationContext> Context, FCameraDebugBlockBuilder& Builder);`
- L30 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L31 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L35 _private member_ `FName ContextClassName;`
- L36 _private member_ `FName OwnerClassName;`
- L37 _private member_ `FString OwnerName;`
- L38 _private member_ `FString CameraAssetName;`
- L39 _private member_ `FName CameraDirectorClassName;`
- L40 _private member_ `FTransform3d InitialContextTransform = FTransform3d::Identity;`
- L41 _private member_ `bool bIsValid = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraDirectorTreeDebugBlock.h` (Public)


#### class `UE::Cameras::FCameraDirectorTreeDebugBlock`  
`class FCameraDirectorTreeDebugBlock : public FCameraDebugBlock`  
_L19-31_
- inherits: `FCameraDebugBlock`
- desc: A debug block for showing the list of camera directors in the camera system's context stack.
- L25 _public prototype_ `void Initialize(const FCameraEvaluationContextStack& ContextStack, FCameraDebugBlockBuilder& Builder);`
- L26 _public prototype_ `void Initialize(TArrayView<const TSharedPtr<FCameraEvaluationContext>> Contexts, FCameraDebugBlockBuilder& Builder);`
- L30 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraEvaluationServiceDebugBlock.h` (Public)


#### class `UE::Cameras::FCameraEvaluationServiceDebugBlock`  
`class FCameraEvaluationServiceDebugBlock : public FCameraDebugBlock`  
_L19-39_
- inherits: `FCameraDebugBlock`
- desc: Basic debug block for an evaluation service.
- L26 _public prototype_ `FCameraEvaluationServiceDebugBlock();` — Constructs a new evaluation service debug block.
- L28 _public prototype_ `FCameraEvaluationServiceDebugBlock(TSharedPtr<const FCameraEvaluationService> InEvaluationService);` — Constructs a new evaluation service debug block.
- L33 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;` — FCameraDebugBlock interface.
- L34 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L38 _private member_ `FString ServiceClassName;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraNodeEvaluationResultDebugBlock.h` (Public)


#### class `UE::Cameras::FCameraNodeEvaluationResultDebugBlock`  
`class FCameraNodeEvaluationResultDebugBlock : public FCameraDebugBlock`  
_L26-68_
- inherits: `FCameraDebugBlock`
- desc: A debug block that prints an evaluation result. It will print a few basic bits of information, followed by the result camera pose (using FCameraPoseDebugBlock) and the result variable table (using FVariableTableDebugBlock).
- L32 _public prototype_ `FCameraNodeEvaluationResultDebugBlock();`
- L40 _public prototype_ `void Initialize(const FCameraNodeEvaluationResult& InResult, FCameraDebugBlockBuilder& Builder);` — Initializes this block with the given camera node result. @param InResult   The result to display @param Builder    The builder to use to make the children debug blocks
- L48 _public prototype_ `void Initialize(const FCameraSystemEvaluationResult& InResult, FCameraDebugBlockBuilder& Builder);` — Initializes this block with the given camera system result. @param InResult   The result to display @param Builder    The builder to use to make the children debug blocks
- L51 _public prototype_ `FCameraPoseDebugBlock* GetCameraPoseDebugBlock();` — Gets the pose stats debug block.
- L53 _public prototype_ `FVariableTableDebugBlock* GetVariableTableDebugBlock();` — Gets the variable table debug block.
- L55 _public prototype_ `FContextDataTableDebugBlock* GetContextDataTableDebugBlock();` — Gets the context data table debug block.
- L57 _public prototype_ `FPostProcessSettingsDebugBlock* GetPostProcessSettingsDebugBlock();` — Gets the pose stats debug block.
- L61 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L62 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L66 _private member_ `bool bIsCameraCut;`
- L67 _private member_ `bool bIsValid;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraNodeEvaluatorDebugBlock.h` (Public)


#### class `UE::Cameras::FCameraNodeEvaluatorDebugBlock`  
`class FCameraNodeEvaluatorDebugBlock : public FCameraDebugBlock`  
_L20-40_
- inherits: `FCameraDebugBlock`
- desc: Basic debug block for a camera node evaluator.
- L27 _public prototype_ `FCameraNodeEvaluatorDebugBlock();` — Constructs a new node evaluator debug block.
- L29 _public prototype_ `FCameraNodeEvaluatorDebugBlock(TObjectPtr<const UCameraNode> InCameraNode);` — Constructs a new node evaluator debug block.
- L34 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;` — FCameraDebugBlock interface.
- L35 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L39 _private member_ `FString NodeClassName;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraPoseDebugBlock.h` (Public)


#### struct `UE::Cameras::FScopedGlobalCameraPoseRenderingParams`  
`struct FScopedGlobalCameraPoseRenderingParams`  
_L16-27_
- desc: Sets the global options for external rendering of a camera pose.
- L18 _public prototype_ `FScopedGlobalCameraPoseRenderingParams(const FString& Label);`
- L19 _public prototype_ `FScopedGlobalCameraPoseRenderingParams(const FLinearColor& LineColor);`
- L20 _public prototype_ `FScopedGlobalCameraPoseRenderingParams(const FString& Label, const FLinearColor& LineColor);`
- L21 _public prototype_ `~FScopedGlobalCameraPoseRenderingParams();`
- L25 _private member_ `FString PreviousLabel;`
- L26 _private member_ `FLinearColor PreviousLineColor;`

#### class `UE::Cameras::FCameraPoseDebugBlock`  
`class FCameraPoseDebugBlock : public FCameraDebugBlock`  
_L32-83_
- inherits: `FCameraDebugBlock`
- desc: A debug block that displays information about a camera pose.
- L39 _public prototype_ `FCameraPoseDebugBlock();` — Creates a new camera pose debug block.
- L41 _public prototype_ `FCameraPoseDebugBlock(const FCameraPose& InCameraPose);` — Creates a new camera pose debug block.
- L44 _public function_ `FCameraPoseDebugBlock& ShouldDrawText(bool bShouldDraw)` — Sets whether the camera pose values should be printed in the text HUD.
- L51 _public function_ `FCameraPoseDebugBlock& ShouldDrawInExternalRendering(bool bShouldDraw)` — Sets whether the camera pose should be drawn when in external debug rendering.
- L61 _public function_ `FCameraPoseDebugBlock& WithShowUnchangedCVar(const TCHAR* InShowUnchangedCVarName)` — Specifies the console variable to use to toggle between only showing camera pose properties that were written to, or showing all camera pose properties.
- L69 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L70 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L74 _private member_ `static FLinearColor GlobalCameraPoseLineColor;`
- L75 _private member_ `static FString GlobalCameraPoseLabel;`
- L77 _private member_ `FCameraPose CameraPose;`
- L78 _private member_ `FString ShowUnchangedCVarName;`
- L79 _private member_ `bool bDrawText = true;`
- L80 _private member_ `bool bDrawInExternalRendering = true;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraPoseLocationTrailDebugBlock.h` (Public)


#### class `UE::Cameras::FCameraPoseLocationTrailDebugBlock`  
`class FCameraPoseLocationTrailDebugBlock : public FCameraDebugBlock`  
_L17-39_
- inherits: `FCameraDebugBlock`
- desc: A debug block that draws a camera pose location trail.
- L23 _public prototype_ `FCameraPoseLocationTrailDebugBlock();`
- L24 _public prototype_ `FCameraPoseLocationTrailDebugBlock(const FCameraNodeEvaluationResult& InResult);`
- L29 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;` — FCameraDebugBlock interface.
- L30 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L34 _private prototype_ `void DrawCameraPoseLocationTrail(FCameraDebugRenderer& Renderer) const;`
- L38 _private member_ `TArray<FVector3d> Trail;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraRigJointsDebugBlock.h` (Public)


#### class `UE::Cameras::FCameraRigJointsDebugBlock`  
`class FCameraRigJointsDebugBlock : public FCameraDebugBlock`  
_L18-46_
- inherits: `FCameraDebugBlock`
- desc: A debug block that displays information about a camera rig's joints.
- L25 _public prototype_ `FCameraRigJointsDebugBlock();` — Creates a new camera rig joints debug block.
- L27 _public prototype_ `FCameraRigJointsDebugBlock(const FCameraRigJoints& InCameraRigJoints, const FCameraVariableTable& InVariableTable);` — Creates a new camera rig joints debug block.
- L31 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L32 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L43 _private member_ `TArray<FEntry, TInlineAllocator<2>> Entries;`

#### struct `UE::Cameras::FCameraRigJointsDebugBlock::FEntry`  
`struct FEntry`  
_L36-42_
- L38 _public member_ `FVector3d Location;`
- L39 _public member_ `FRotator3d Rotation;`
- L40 _public member_ `FCameraVariableID VariableID;`
- L41 _public member_ `FString VariableName;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraSystemDebugRegistry.h` (Public)


#### struct `UE::Cameras::FCameraSystemDebugID`  
`struct FCameraSystemDebugID`  
_L22-72_
- desc: An identifier for a camera system instance.
- L24 _public function_ `FCameraSystemDebugID() : Value(INVALID)`
- L25 _public function_ `FCameraSystemDebugID(int32 InValue) : Value(InValue)`
- L27 _public function_ `bool IsValid() const`
- L28 _public function_ `bool IsAuto() const`
- L29 _public function_ `bool IsAny() const`
- L30 _public function_ `operator bool() const`
- L32 _public function_ `int32 GetValue() const`
- L34 _public function_ `static FCameraSystemDebugID Invalid()`
- L35 _public function_ `static FCameraSystemDebugID Auto()`
- L36 _public function_ `static FCameraSystemDebugID Any()`
- L64 _private member_ `constexpr static int32 INVALID = -1;`
- L65 _private member_ `constexpr static int32 AUTO = 0;`
- L66 _private member_ `constexpr static int32 ANY = MAX_int32;`
- L68 _private member_ `int32 Value;`

#### class `UE::Cameras::FCameraSystemDebugRegistry`  
`class FCameraSystemDebugRegistry`  
_L79-102_
- desc: A registry for any running camera system instance for which we may want to display debug info.
- L83 _public prototype_ `static FCameraSystemDebugRegistry& Get();`
- L85 _public prototype_ `FCameraSystemDebugID RegisterCameraSystemEvaluator(TSharedRef<FCameraSystemEvaluator> InEvaluator);`
- L86 _public prototype_ `void UnregisterCameraSystemEvaluator(FCameraSystemDebugID InDebugID);`
- L88 _public typedef_ `using FRegisteredCameraSystems = TArray<TSharedPtr<FCameraSystemEvaluator>>;`
- L89 _public prototype_ `void GetRegisteredCameraSystemEvaluators(FRegisteredCameraSystems& OutEvaluators) const;`
- L91 _public prototype_ `int32 NumRegisteredCameraSystemEvaluators() const;`
- L101 _private member_ `TSparseArray<FEntry> Entries;`

#### struct `UE::Cameras::FCameraSystemDebugRegistry::FEntry`  
`struct FEntry`  
_L95-99_
- L97 _public member_ `TWeakPtr<FCameraSystemEvaluator> WeakEvaluator;`
- L98 _public member_ `FString EvaluatorOwnerName;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L40 _function_ `friend bool operator==(FCameraSystemDebugID A, FCameraSystemDebugID B)` (scope `UE::Cameras`)
- L45 _function_ `friend bool operator!=(FCameraSystemDebugID A, FCameraSystemDebugID B)` (scope `UE::Cameras`)
- L50 _function_ `friend uint32 GetTypeHash(FCameraSystemDebugID In)` (scope `UE::Cameras`)
- L55 _function_ `friend FString LexToString(const FCameraSystemDebugID In)` (scope `UE::Cameras`)
- L74 _prototype_ `FArchive& operator <<(FArchive& Ar, FCameraSystemDebugID& InDebugID);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CameraSystemTrace.h` (Public)


#### class `UE::Cameras::FCameraSystemTrace`  
`class FCameraSystemTrace`  
_L25-41_
- desc: Trace utility class for the camera system.
- L29 _public member_ `static FString ChannelName;`
- L30 _public member_ `static FString LoggerName;`
- L31 _public member_ `static FString EvaluationEventName;`
- L36 _public prototype_ `static bool IsTraceEnabled();` — Returns whether tracing of camera system evaluation is enabled.
- L38 _public prototype_ `static void TraceEvaluation(UWorld* InWorld, const FCameraSystemEvaluationResult& InResult, FRootCameraDebugBlock& InRootDebugBlock);` — Records one frame of camera system evaluation.
- L40 _public prototype_ `static FCameraDebugBlock* ReadEvaluationTrace(TArray<uint8> InSerializedBlocks, FCameraDebugBlockStorage& InStorage);` — Reads back one frame of camera system evaluation.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/CategoryTitleDebugBlock.h` (Public)


#### class `UE::Cameras::FCategoryTitleDebugBlock`  
`class FCategoryTitleDebugBlock : public FCameraDebugBlock`  
_L18-39_
- inherits: `FCameraDebugBlock`
- desc: A utility debug block that prints a title for a debug category, if that debug category is active. By default, if the debug category is inactive, it will skip any attachments and children blocks.
- L24 _public prototype_ `FCategoryTitleDebugBlock();`
- L25 _public prototype_ `FCategoryTitleDebugBlock(const FString& InCategory, const FString& InTitle);`
- L29 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L30 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L34 _public member_ `FString Category;`
- L35 _public member_ `FString Title;`
- L37 _public member_ `bool bSkipAttachedBlocksIfInactive = true;`
- L38 _public member_ `bool bSkipChildrenBlocksIfInactive = true;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/ContextDataTableDebugBlock.h` (Public)


#### class `UE::Cameras::FContextDataTableDebugBlock`  
`class FContextDataTableDebugBlock : public FCameraDebugBlock`  
_L18-70_
- inherits: `FCameraDebugBlock`
- desc: A debug block that prints the contents of a context data table.
- L25 _public prototype_ `FContextDataTableDebugBlock();` — Creates a new context data table debug block.
- L27 _public prototype_ `FContextDataTableDebugBlock(const FCameraContextDataTable& InContextDataTable);` — Creates a new context data table debug block.
- L30 _public function_ `FContextDataTableDebugBlock& WithShowDataIDsCVar(const TCHAR* InShowDataIDsCVarName)` — Specifies the console variable to use to toggle the printing of variable IDs.
- L38 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L39 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L41 _protected prototype_ `void Initialize(const FCameraContextDataTable& InContextDataTable);`
- L43 _protected prototype_ `static FString GetDebugValueString( ECameraContextDataType DataType, ECameraContextDataContainerType DataContainerType, const UObject* DataTypeObject, const uint8* DataPtr);`
- L49 _protected prototype_ `static FString GetDebugValueString( ECameraContextDataType DataType, const UObject* DataTypeObject, const uint8* DataPtr);`
- L65 _private member_ `TArray<FEntryDebugInfo> Entries;`
- L67 _private member_ `FString ShowDataIDsCVarName;`

#### struct `UE::Cameras::FContextDataTableDebugBlock::FEntryDebugInfo`  
`struct FEntryDebugInfo`  
_L56-64_
- L58 _public member_ `uint32 ID;`
- L59 _public member_ `FString Name;`
- L60 _public member_ `FName TypeName;`
- L61 _public member_ `FString Value;`
- L62 _public member_ `bool bWritten;`
- L63 _public member_ `bool bWrittenThisFrame;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/DebugTextRenderer.h` (Public)


#### struct `UE::Cameras::FDebugTextDrawCommand`  
`struct FDebugTextDrawCommand`  
_L95-100_
- desc: Command for drawing text on a canvas.
- L97 _public member_ `TStringView<TCHAR> TextView;`
- L99 _public prototype_ `void Execute(FCanvas* Canvas, const FColor& DrawColor, const UFont* Font, FVector2f& InOutDrawPosition) const;`

#### struct `UE::Cameras::FDebugTextNewLineCommand`  
`struct FDebugTextNewLineCommand`  
_L103-109_
- desc: Command for moving the drawing position to a new line.
- L105 _public member_ `float LineSpacing = 0.f;`
- L106 _public member_ `float LeftMargin = 0.f;`
- L108 _public prototype_ `void Execute(FVector2f& InOutDrawPosition) const;`

#### struct `UE::Cameras::FDebugTextSetColorCommand`  
`struct FDebugTextSetColorCommand`  
_L112-117_
- desc: Command for setting the text color on a canvas.
- L114 _public member_ `FColor DrawColor;`
- L116 _public prototype_ `void Execute(FColor* OutDrawColor) const;`

#### class `UE::Cameras::FDebugTextRenderer`  
`class FDebugTextRenderer`  
_L131-181_
- desc: Rendering utility for colored debug text.
- L136 _public member_ `float LineSpacing;` — Space between the lines, defaults to max font character height.
- L138 _public member_ `float LeftMargin;` — The X coordinate for where text drawing starts, and where new lines start from.
- L140 _public member_ `bool bEndWithNewLine = false;` — Moves the next draw position to a new line at the end of the text render.
- L143 _public prototype_ `FDebugTextRenderer(FCanvas* InCanvas, const FColor& InDrawColor, const UFont* InFont);` — Creates a new debug text renderer.
- L146 _public prototype_ `void RenderText(float StartingDrawY, const TStringView<TCHAR> TextView);` — Renders the given text to the canvas.
- L147 _public prototype_ `void RenderText(FVector2f StartingDrawPosition, const TStringView<TCHAR> TextView);`
- L150 _public prototype_ `void ExecuteCommands(float StartingDrawY, FDebugTextCommandArray& Commands);` — Executes the given command queue.
- L151 _public prototype_ `void ExecuteCommands(FVector2f StartingDrawPosition, FDebugTextCommandArray& Commands);`
- L154 _public function_ `FVector2f GetEndDrawPosition() const` — Gets the coordinate of where any new text would go, just after the last render.
- L157 _public function_ `float GetRightMargin() const` — Gets the maximum horizontal extent of the rendered text.
- L161 _public prototype_ `static float GetStringViewSize(const UFont* Font, TStringView<TCHAR> TextView);`
- L165 _private prototype_ `void ParseText(const TStringView<TCHAR> TextView, FDebugTextCommandArray& OutCommands);`
- L166 _private prototype_ `void ExecuteCommands(FDebugTextCommandArray& Commands);`
- L167 _private prototype_ `void UpdateRightMargin();`
- L169 _private prototype_ `void AddDrawCommand(const TCHAR* RangeStart, const TCHAR* RangeEnd, bool bNewLine, FDebugTextCommandArray& OutCommands);`
- L170 _private prototype_ `void AddTokenCommand(const TCHAR* RangeStart, const TCHAR* RangeEnd, FDebugTextCommandArray& OutCommands);`
- L172 _private prototype_ `FColor InterpretColor(const FString& ColorName);`
- L176 _private member_ `FCanvas* Canvas;`
- L177 _private member_ `FColor DrawColor;`
- L178 _private member_ `const UFont* Font;`
- L179 _private member_ `FVector2f NextDrawPosition;`
- L180 _private member_ `float RightMargin = 0;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Cameras` (scope `UE`)
- L24 _function_ `template<typename FieldType> FString ToDebugString(const FieldType& FieldValue)` (scope `UE::Cameras`) — Utility function to print something. Most types have a LexToString implementation, but not all.
- L37 _function_ `template<typename EnumType> FString ToDebugString(TEnumAsByte<EnumType> EnumValue)` (scope `UE::Cameras`)
- L43 _function_ `template<typename T> FString ToDebugString(const UE::Math::TVector<T>& FieldValue)` (scope `UE::Cameras`)
- L48 _function_ `template<typename T> FString ToDebugString(const UE::Math::TVector2<T>& FieldValue)` (scope `UE::Cameras`)
- L53 _function_ `template<typename T> FString ToDebugString(const UE::Math::TVector4<T>& FieldValue)` (scope `UE::Cameras`)
- L58 _function_ `template<typename T> FString ToDebugString(const UE::Math::TRotator<T>& FieldValue)` (scope `UE::Cameras`)
- L63 _function_ `template<typename T> FString ToDebugString(const UE::Math::TTransform<T>& FieldValue)` (scope `UE::Cameras`)
- L68 _function_ `template<> inline FString ToDebugString(const FLinearColor& FieldValue)` (scope `UE::Cameras`)
- L73 _function_ `template<> inline FString ToDebugString(const EAspectRatioAxisConstraint& FieldValue)` (scope `UE::Cameras`)
- L84 _function_ `template<> inline FString ToDebugString(const ECameraProjectionMode::Type& FieldValue)` (scope `UE::Cameras`)
- L120 _typedef_ `using FDebugTextCommand = TVariant< FDebugTextDrawCommand, FDebugTextNewLineCommand, FDebugTextSetColorCommand>;` (scope `UE::Cameras`) — A debug text drawing command, which can be of multiple types.
- L126 _typedef_ `using FDebugTextCommandArray = TArray<FDebugTextCommand>;` (scope `UE::Cameras`) — A command queue for drawing text on a canvas.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/PlayerControllersDebugBlock.h` (Public)


#### class `UE::Cameras::FPlayerControllersDebugBlock`  
`class FPlayerControllersDebugBlock : public FCameraDebugBlock`  
_L19-60_
- inherits: `FCameraDebugBlock`
- desc: A debug block for showing the list of local player controllers and their view targets.
- L25 _public prototype_ `FPlayerControllersDebugBlock();`
- L27 _public prototype_ `void Initialize(UWorld* World);`
- L32 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;` — FCameraDebugBlock interface.
- L33 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L56 _private member_ `TArray<FPlayerControllerDebugInfo> PlayerControllers;`
- L57 _private member_ `bool bHadValidWorld = false;`

#### struct `UE::Cameras::FPlayerControllersDebugBlock::FPlayerControllerDebugInfo`  
`struct FPlayerControllerDebugInfo`  
_L37-55_
- L39 _public member_ `FString PlayerControllerName;`
- L40 _public member_ `FString CameraManagerName;`
- L41 _public member_ `FString LocalPlayerName;`
- L43 _public member_ `FIntPoint ViewportSize;`
- L44 _public member_ `TEnumAsByte<EAspectRatioAxisConstraint> DefaultAspectRatioAxisConstraint = AspectRatio_MaintainXFOV;`
- L45 _public member_ `bool bHasDefaultAspectRatioAxisConstraint = true;`
- L47 _public member_ `FString ViewTargetName;`
- L48 _public member_ `FVector3d ViewTargetLocation;`
- L49 _public member_ `FRotator3d ViewTargetRotation;`
- L50 _public member_ `float ViewTargetFOV;`
- L51 _public member_ `float ViewTargetAspectRatio;`
- L52 _public member_ `TEnumAsByte<EAspectRatioAxisConstraint> ViewTargetAspectRatioAxisConstraint = AspectRatio_MaintainXFOV;`
- L53 _public member_ `bool bViewTargetConstrainAspectRatio;`
- L54 _public member_ `bool bViewTargetOverrideAspectRatioAxisConstraint = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/PostProcessSettingsDebugBlock.h` (Public)


#### class `UE::Cameras::FPostProcessSettingsDebugBlock`  
`class FPostProcessSettingsDebugBlock : public FCameraDebugBlock`  
_L16-35_
- inherits: `FCameraDebugBlock`
- desc: A debug block that displays information about post-process settings.
- L23 _public prototype_ `FPostProcessSettingsDebugBlock();` — Creates a new post-process settings debug block.
- L25 _public prototype_ `FPostProcessSettingsDebugBlock(const FPostProcessSettingsCollection& InPostProcessSettings);` — Creates a new post-process settings debug block.
- L29 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L30 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L34 _private member_ `FPostProcessSettingsCollection PostProcessSettings;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/RootCameraDebugBlock.h` (Public)


#### struct `UE::Cameras::FRootCameraDebugDrawParams`  
`struct FRootCameraDebugDrawParams`  
_L25-35_
- desc: Parameters for drawing a hierarchy of debug blocks.
- L31 _public member_ `bool bFromDefaultCameraSystem = false;` — Whether the debug blocks belong to a camera system that is considered the "default" one, such as the one running inside the camera manager, or the active view target.
- L34 _public member_ `bool bForceDraw = false;` — Whether to force draw the debug blocks.

#### class `UE::Cameras::FRootCameraDebugBlock`  
`class FRootCameraDebugBlock : public FCameraDebugBlock`  
_L40-68_
- inherits: `FCameraDebugBlock`
- desc: The root debug block for the camera system.
- L47 _public prototype_ `void BuildDebugBlocks(const FCameraSystemEvaluator& CameraSystem, const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder);` — Build all debug blocks for the last evaluation frame.
- L50 _public prototype_ `void RootDebugDraw(const FRootCameraDebugDrawParams& Params, FCameraDebugRenderer& Renderer);` — Initiate the debug drawing.
- L53 _public function_ `const FCameraSystemDebugID& GetDebugID() const` — Gets the debug ID of the camera system that generated this debug info.
- L58 _public prototype_ `static bool ShouldDebugDraw(FCameraSystemDebugID InDebugID, bool bIsDefaultCameraSystem);` — Checks whether the debug data with the given ID would be drawn on screen.
- L63 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;` — FCameraDebugBlock interface.
- L67 _private member_ `FCameraSystemDebugID DebugID;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)
- L18 _externvar_ `extern bool GGameplayCamerasDebugEnable;` (scope `UE::Cameras`)
- L19 _externvar_ `extern int32 GGameplayCamerasDebugSystemID;` (scope `UE::Cameras`)
- L20 _externvar_ `extern FString GGameplayCamerasDebugCategories;` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/VariableTableDebugBlock.h` (Public)


#### class `UE::Cameras::FVariableTableDebugBlock`  
`class FVariableTableDebugBlock : public FCameraDebugBlock`  
_L17-59_
- inherits: `FCameraDebugBlock`
- desc: A debug block that prints the contents of a variable table.
- L24 _public prototype_ `FVariableTableDebugBlock();` — Creates a new variable table debug block.
- L26 _public prototype_ `FVariableTableDebugBlock(const FCameraVariableTable& InVariableTable);` — Creates a new variable table debug block.
- L29 _public function_ `FVariableTableDebugBlock& WithShowVariableIDsCVar(const TCHAR* InShowVariableIDsCVarName)` — Specifies the console variable to use to toggle the printing of variable IDs.
- L37 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L38 _protected prototype_ `virtual void OnSerialize(FArchive& Ar) override;`
- L40 _protected prototype_ `void Initialize(const FCameraVariableTable& InVariableTable);`
- L54 _private member_ `TArray<FEntryDebugInfo> Entries;`
- L56 _private member_ `FString ShowVariableIDsCVarName;`

#### struct `UE::Cameras::FVariableTableDebugBlock::FEntryDebugInfo`  
`struct FEntryDebugInfo`  
_L44-53_
- L46 _public member_ `uint32 ID;`
- L47 _public member_ `FString Name;`
- L48 _public member_ `FString Value;`
- L49 _public member_ `bool bIsInput;`
- L50 _public member_ `bool bIsPrivate;`
- L51 _public member_ `bool bWritten;`
- L52 _public member_ `bool bWrittenThisFrame;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Debug/ViewfinderDebugBlock.h` (Public)


#### class `UE::Cameras::FViewfinderDebugBlock`  
`class FViewfinderDebugBlock : public FCameraDebugBlock`  
_L12-23_
- inherits: `FCameraDebugBlock`
- L18 _public prototype_ `FViewfinderDebugBlock();`
- L22 _protected prototype_ `virtual void OnDebugDraw(const FCameraDebugBlockDrawParams& Params, FCameraDebugRenderer& Renderer) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Directors/BlueprintCameraDirector.h` (Public)


#### struct `FBlueprintCameraDirectorEvaluationParams`  
`struct UE_DEPRECATED(5.6, "This parameter structure is deprecated, parameters are now passed directly to RunCameraDirector.") FBlueprintCameraDirectorEvaluationParams`  
_L18-29_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `float DeltaTime = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category="Evaluation", meta=(Deprecated, DeprecationMessage="Use the main DeltaTime parameter on RunCameraDirector"))` — The elapsed time since the last evaluation.
- L28 _public member_ `TObjectPtr<UObject> EvaluationContextOwner;` — `UPROPERTY(BlueprintReadWrite, Category="Evaluation", meta=(Deprecated, DeprecationMessage="Use the main EvaluationContextOwner parameter on RunCameraDirector"))` — The owner (if any) of the evaluation context we are running inside of.

#### struct `FBlueprintCameraDirectorActivateParams`  
`struct UE_DEPRECATED(5.6, "This parameter structure is deprecated, parameters are now passed directly to ActivateCameraDirector.") FBlueprintCameraDirectorActivateParams`  
_L32-39_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public member_ `TObjectPtr<UObject> EvaluationContextOwner;` — `UPROPERTY(BlueprintReadWrite, Category="Evaluation")` — The owner (if any) of the evaluation context we are running inside of.

#### struct `FBlueprintCameraDirectorDeactivateParams`  
`struct UE_DEPRECATED(5.6, "This parameter structure is deprecated, parameters are now passed directly to DeactivateCameraDirector.") FBlueprintCameraDirectorDeactivateParams`  
_L42-49_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public member_ `TObjectPtr<UObject> EvaluationContextOwner;` — `UPROPERTY(BlueprintReadWrite, Category="Evaluation")` — The owner (if any) of the evaluation context we were running inside of.

#### class `UBlueprintCameraDirectorEvaluator`  
`class UBlueprintCameraDirectorEvaluator : public UObject`  
_L55-218_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UObject`
- desc: Base class for a Blueprint camera director evaluator.
- L67 _public prototype_ `void ActivateCameraDirector(UObject* EvaluationContextOwner, const FBlueprintCameraDirectorActivateParams& Params);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Camera Director|Activation")` — Override this method in Blueprint to execute custom logic when this camera director gets activated.
- L76 _public prototype_ `void DeactivateCameraDirector(UObject* EvaluationContextOwner, const FBlueprintCameraDirectorDeactivateParams& Params);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Camera Director|Activation")` — Override this method in Blueprint to execute custom logic when this camera director gets deactivated.
- L85 _public prototype_ `void RunCameraDirector(float DeltaTime, UObject* EvaluationContextOwner, const FBlueprintCameraDirectorEvaluationParams& Params);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Evaluation")` — Override this method in Blueprint to execute the custom logic that determines what camera rig(s) should be active every frame.
- L91 _public prototype_ `FName AddChildEvaluationContext(UObject* ChildEvaluationContextOwner);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Evaluation")`
- L94 _public prototype_ `bool RemoveChildEvaluationContext(UObject* ChildEvaluationContextOwner, FName ChildSlotName);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Evaluation")`
- L97 _public prototype_ `bool RunChildCameraDirector(float DeltaTime, FName ChildSlotName);` — `UFUNCTION(BlueprintCallable, Category="Evaluation")`
- L103 _public prototype_ `void ActivatePersistentBaseCameraRig(UCameraRigAsset* CameraRigPrefab);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Activation")` — Activates the given camera rig prefab in the base layer.
- L107 _public prototype_ `void ActivatePersistentGlobalCameraRig(UCameraRigAsset* CameraRigPrefab);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Activation")` — Activates the given camera rig prefab in the global layer.
- L111 _public prototype_ `void ActivatePersistentVisualCameraRig(UCameraRigAsset* CameraRigPrefab);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Activation")` — Activates the given camera rig prefab in the visual layer.
- L115 _public prototype_ `void DeactivatePersistentBaseCameraRig(UCameraRigAsset* CameraRigPrefab);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Activation")` — Deactivates the given camera rig prefab in the base layer.
- L119 _public prototype_ `void DeactivatePersistentGlobalCameraRig(UCameraRigAsset* CameraRigPrefab);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Activation")` — Deactivates the given camera rig prefab in the global layer.
- L123 _public prototype_ `void DeactivatePersistentVisualCameraRig(UCameraRigAsset* CameraRigPrefab);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Activation")` — Deactivates the given camera rig prefab in the visual layer.
- L129 _public prototype_ `void ActivateCameraRig(UCameraRigAsset* CameraRig, bool bForceNewInstance = false);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Evaluation")` — Specifies a camera rig to be active this frame.
- L136 _public prototype_ `void ActivateCameraRigViaProxy(UCameraRigProxyAsset* CameraRigProxy, bool bForceNewInstance = false);` — `UFUNCTION(BlueprintCallable, Category="Camera Director|Evaluation")` — Specifies a camera rig to be active this frame, via a proxy which is later resolved via the proxy table of the Blueprint camera director.
- L142 _public prototype_ `UCameraRigAsset* ResolveCameraRigProxy(const UCameraRigProxyAsset* CameraRigProxy) const;` — `UFUNCTION(BlueprintPure, Category="Camera Director|Evaluation", meta=(HideSelfPin=true))` — Resolves the camera rig proxy using the camera director's proxy table.
- L152 _public prototype_ `AActor* FindEvaluationContextOwnerActor(TSubclassOf<AActor> ActorClass) const;` — `UFUNCTION(BlueprintPure, Category="Camera Director|Evaluation", meta=(DeterminesOutputType="ActorClass"))` — A utility function that tries to find if an actor owns the evaluation context. Handles the situation where the evaluation context is an actor component (like a UGameplayCameraComponent) or an actor itself.
- L156 _public prototype_ `FBlueprintCameraEvaluationDataRef GetInitialContextResult() const;` — `UFUNCTION(BlueprintPure, Category="Camera Director|Evaluation", meta=(DisplayName="Get Shared Camera Data"))` — Gets the shared evaluation context data.
- L160 _public prototype_ `FBlueprintCameraEvaluationDataRef GetConditionalContextResult(ECameraEvaluationDataCondition Condition) const;` — `UFUNCTION(BlueprintPure, Category="Camera Director|Evaluation", meta=(DisplayName="Get Conditional Camera Data"))` — Gets the evaluation context data for a sub-set of camera rigs.
- L165 _public prototype_ `virtual UWorld* GetWorld() const override;` — UObject interface.
- L167 _public function_ `virtual bool ImplementsGetWorld() const override`
- L172 _public typedef_ `using FCameraEvaluationContext = UE::Cameras::FCameraEvaluationContext;`
- L173 _public typedef_ `using FCameraDirectorEvaluationResult = UE::Cameras::FCameraDirectorEvaluationResult;`
- L177 _public function_ `const FCameraDirectorEvaluationResult& GetEvaluationResult() const`
- L182 _public prototype_ `void NativeInitializeCameraDirector(UE::Cameras::FCameraDirectorEvaluator* InOwningDirectorEvaluator, const UE::Cameras::FCameraDirectorInitializeParams& Params);` — Initialize this camera director evaluator.
- L185 _public prototype_ `void NativeAbandonCameraDirector();` — Abandon this camera director evalutor.
- L190 _public prototype_ `void NativeActivateCameraDirector(const UE::Cameras::FCameraDirectorActivateParams& Params);` — Native wrapper for ActivateCameraDirector.
- L193 _public prototype_ `void NativeDeactivateCameraDirector(const UE::Cameras::FCameraDirectorDeactivateParams& Params);` — Native wrapper for DeactivateCameraDirector.
- L196 _public prototype_ `void NativeRunCameraDirector(const UE::Cameras::FCameraDirectorEvaluationParams& Params);` — Native wrapper for RunCameraDirector.
- L198 _public prototype_ `bool NativeAddChildEvaluationContext(UObject* ChildEvaluationContextOwner);`
- L200 _public prototype_ `bool NativeRemoveChildEvaluationContext(UObject* ChildEvaluationContextOwner);`
- L205 _private member_ `UE::Cameras::FCameraDirectorEvaluator* OwningDirectorEvaluator = nullptr;` — The owning camera director evaluator.
- L208 _private member_ `FCameraDirectorEvaluationResult EvaluationResult;` — The current evaluation result.
- L211 _private member_ `TSharedPtr<FCameraEvaluationContext> EvaluationContext;` — The current evaluation context.
- L214 _private member_ `TArray<FName> ChildrenContextSlotNames;` — Currently registered children contexts.
- L217 _private member_ `mutable TWeakObjectPtr<UWorld> WeakCachedWorld;` — Cached world.

#### class `UBlueprintCameraDirector`  
`class UBlueprintCameraDirector : public UCameraDirector`  
_L224-241_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UCameraDirector`
- desc: A camera director that will instantiate the given Blueprint and run it.
- L232 _public member_ `TSubclassOf<UBlueprintCameraDirectorEvaluator> CameraDirectorEvaluatorClass;` — `UPROPERTY(EditAnywhere, Category="Evaluation")` — The blueprint class that we should instantiate and run.
- L237 _protected prototype_ `virtual FCameraDirectorEvaluatorPtr OnBuildEvaluator(FCameraDirectorEvaluatorBuilder& Builder) const override;` — UCameraDirector interface.
- L238 _protected prototype_ `virtual void OnBuildCameraDirector(UE::Cameras::FCameraBuildContext& BuildContext) override;`
- L239 _protected prototype_ `virtual void OnGatherRigUsageInfo(FCameraDirectorRigUsageInfo& UsageInfo) const override;`
- L240 _protected prototype_ `virtual void OnExtendAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Directors/CameraDirectorStateTreeSchema.h` (Public)


#### struct `UE::Cameras::FStateTreeContextDataNames`  
`struct FStateTreeContextDataNames`  
_L24-27_
- L26 _public member_ `const static FName ContextOwner;`

#### class `UCameraDirectorStateTreeSchema`  
`class UCameraDirectorStateTreeSchema : public UStateTreeSchema`  
_L35-55_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta=(DisplayName="Gameplay Camera Director"))`
- inherits: `UStateTreeSchema`
- desc: The schema of the StateTree for a StateTree camera director.
- L41 _public prototype_ `UCameraDirectorStateTreeSchema();`
- L46 _protected prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;` — UStateTreeSchema interface.
- L47 _protected prototype_ `virtual bool IsClassAllowed(const UClass* InScriptStruct) const override;`
- L48 _protected prototype_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override;`
- L49 _protected function_ `virtual TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const override`
- L54 _private member_ `TArray<FStateTreeExternalDataDesc> ContextDataDescs;` — `UPROPERTY()`

#### struct `FCameraDirectorStateTreeEvaluationData`  
`struct FCameraDirectorStateTreeEvaluationData`  
_L59-75_
- reflection: `USTRUCT(BlueprintType)`
- desc: The evaluation data for the StateTree camera director.
- L65 _public member_ `TArray<TObjectPtr<UCameraRigAsset>> ActiveCameraRigs;` — `UPROPERTY()` — Camera rigs activated during a StateTree's execution frame.
- L69 _public member_ `TArray<TObjectPtr<UCameraRigProxyAsset>> ActiveCameraRigProxies;` — `UPROPERTY()` — Camera rig proxies activated during a StateTree's execution frame.
- L74 _public prototype_ `void Reset();` — Reset this evaluation data for a new frame.

#### struct `FGameplayCamerasStateTreeTask`  
`struct FGameplayCamerasStateTreeTask : public FStateTreeTaskBase`  
_L79-82_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeTaskBase`
- desc: Base classs for camera director StateTree tasks.

#### struct `FGameplayCamerasStateTreeCondition`  
`struct FGameplayCamerasStateTreeCondition : public FStateTreeConditionBase`  
_L86-89_
- reflection: `USTRUCT(meta = (Hidden))`
- inherits: `FStateTreeConditionBase`
- desc: Base classs for camera director StateTree conditions.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Directors/PriorityQueueCameraDirector.h` (Public)


#### class `UPriorityQueueCameraDirector`  
`class UPriorityQueueCameraDirector : public UCameraDirector`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UCameraDirector`
- desc: A camera director that holds multiple sub-directors, and runs the one that has the highest priority.
- L21 _public prototype_ `UPriorityQueueCameraDirector(const FObjectInitializer& ObjectInit);`
- L26 _protected prototype_ `virtual FCameraDirectorEvaluatorPtr OnBuildEvaluator(FCameraDirectorEvaluatorBuilder& Builder) const override;` — UCameraDirector interface.

#### class `UE::Cameras::IPriorityQueueEntry`  
`class IPriorityQueueEntry`  
_L35-43_
- desc: Interface for sub-directors with dynamic priorities.
- L39 _public prototype_ `virtual ~IPriorityQueueEntry() = default;`
- L42 _public prototype_ `virtual int32 GetPriority() = 0;` — Gets the current priority of the sub-director.

#### class `UE::Cameras::FPriorityQueueCameraDirectorEvaluator`  
`class FPriorityQueueCameraDirectorEvaluator : public FCameraDirectorEvaluator`  
_L53-91_
- inherits: `FCameraDirectorEvaluator`
- desc: Evaluator for the priority queue camera director. Use the overriden AddChildEvaluationContext methods here to add sub-directors with a specific priority. Using the base class version will add a sub-director with a priority of 0. Highest priority values mean more priority, which means higher chances of being picked from the queue.
- L62 _public prototype_ `void AddChildEvaluationContext(TSharedRef<FCameraEvaluationContext> InContext, int32 Priority);` — Adds a sub-director with the given fixed priority.
- L69 _public prototype_ `void AddChildEvaluationContext(TSharedRef<FCameraEvaluationContext> InContext, IPriorityQueueEntry* PriorityEntry);` — Adds a sub-director with the given dynamic priority. It's customary to have the evaluation context itself implement the IPriorityQueueEntry interface, and therefore passing the pointer twice to the function.
- L73 _protected prototype_ `virtual void OnRun(const FCameraDirectorEvaluationParams& Params, FCameraDirectorEvaluationResult& OutResult) override;`
- L75 _protected prototype_ `virtual void OnAddChildEvaluationContext(const FChildContextManulationParams& Params, FChildContextManulationResult& Result) override;`
- L76 _protected prototype_ `virtual void OnRemoveChildEvaluationContext(const FChildContextManulationParams& Params, FChildContextManulationResult& Result) override;`
- L80 _private typedef_ `using FPriorityGiver = TVariant<int32, IPriorityQueueEntry*>;`
- L89 _private typedef_ `using FEntryArray = TArray<FEntry>;`
- L90 _private member_ `FEntryArray Entries;`

#### struct `UE::Cameras::FPriorityQueueCameraDirectorEvaluator::FEntry`  
`struct FEntry`  
_L81-87_
- L83 _public member_ `TSharedPtr<FCameraEvaluationContext> ChildContext;`
- L84 _public member_ `FPriorityGiver PriorityGiver;`
- L86 _public prototype_ `int32 GetPriority() const;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Directors/SingleCameraDirector.h` (Public)


#### class `USingleCameraDirector`  
`class USingleCameraDirector : public UCameraDirector`  
_L13-33_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UCameraDirector`
- desc: A simple camera director that only ever returns one single camera rig.
- L19 _public prototype_ `USingleCameraDirector(const FObjectInitializer& ObjectInit);`
- L24 _protected prototype_ `virtual FCameraDirectorEvaluatorPtr OnBuildEvaluator(FCameraDirectorEvaluatorBuilder& Builder) const override;` — UCameraDirector interface.
- L25 _protected prototype_ `virtual void OnBuildCameraDirector(UE::Cameras::FCameraBuildContext& BuildContext) override;`
- L26 _protected prototype_ `virtual void OnGatherRigUsageInfo(FCameraDirectorRigUsageInfo& UsageInfo) const override;`
- L32 _public member_ `TObjectPtr<UCameraRigAsset> CameraRig;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(UseSelfCameraRigPicker=true))` — The camera rig to run every frame.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Directors/StateTreeCameraDirector.h` (Public)


#### class `UStateTreeCameraDirector`  
`class UStateTreeCameraDirector : public UCameraDirector`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UCameraDirector`
- desc: A camera director that runs a StateTree to specify which camera rigs should be active any given frame.
- L21 _public prototype_ `UStateTreeCameraDirector(const FObjectInitializer& ObjectInit);`
- L26 _protected prototype_ `virtual FCameraDirectorEvaluatorPtr OnBuildEvaluator(FCameraDirectorEvaluatorBuilder& Builder) const override;` — UCameraDirector interface.
- L27 _protected prototype_ `virtual void OnBuildCameraDirector(UE::Cameras::FCameraBuildContext& BuildContext) override;`
- L28 _protected prototype_ `virtual void OnGatherRigUsageInfo(FCameraDirectorRigUsageInfo& UsageInfo) const override;`
- L29 _protected prototype_ `virtual void OnExtendAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L36 _public member_ `FStateTreeReference StateTreeReference;` — `UPROPERTY(EditAnywhere, Category="StateTree", DisplayName="State Tree", meta=(Schema="/Script/GameplayCameras.CameraDirectorStateTreeSchema"))` — The StateTree to execute. Must have been created with the CameraDirectorStateTreeSchema.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Directors/StateTreeCameraDirectorTasks.h` (Public)


#### struct `FGameplayCamerasActivateCameraRigTaskInstanceData`  
`struct FGameplayCamerasActivateCameraRigTaskInstanceData`  
_L12-19_
- reflection: `USTRUCT()`
- desc: Instance data for the "Activate Camera Rig" task.
- L18 _public member_ `TObjectPtr<UCameraRigAsset> CameraRig;` — `UPROPERTY(EditAnywhere, Category="Cameras", meta=(UseCameraDirectorRigPicker=true))` — The camera rig to activate.

#### struct `FGameplayCamerasActivateCameraRigTask`  
`struct FGameplayCamerasActivateCameraRigTask : public FGameplayCamerasStateTreeTask`  
_L25-52_
- reflection: `USTRUCT(meta=(DisplayName="Activate Camera Rig", Category="Cameras"))`
- inherits: `FGameplayCamerasStateTreeTask`
- desc: A task that activates a given camera rig inside a StateTreeCameraDirector.
- L29 _public typedef_ `using FInstanceDataType = FGameplayCamerasActivateCameraRigTaskInstanceData;`
- L34 _protected function_ `virtual const UStruct* GetInstanceDataType() const override` — FStateTreeTaskBase interface.
- L35 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L36 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L37 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L41 _private prototype_ `bool UpdateResult(FStateTreeExecutionContext& Context) const;`
- L45 _private member_ `TStateTreeExternalDataHandle<FCameraDirectorStateTreeEvaluationData> CameraDirectorEvaluationDataHandle;`
- L51 _public member_ `bool bRunOnce = false;` — `UPROPERTY(EditAnywhere, Category="State Tree")` — If true, the task will complete immediately. If false, the task will run until a transition triggers.

#### struct `FGameplayCamerasActivateCameraRigViaProxyTaskInstanceData`  
`struct FGameplayCamerasActivateCameraRigViaProxyTaskInstanceData`  
_L56-63_
- reflection: `USTRUCT()`
- desc: Instance data for the "Activate Camera Rig via Proxy" task.
- L62 _public member_ `TObjectPtr<UCameraRigProxyAsset> CameraRigProxy;` — `UPROPERTY(EditAnywhere, Category="Cameras")` — The camera rig proxy to activate.

#### struct `FGameplayCamerasActivateCameraRigViaProxyTask`  
`struct FGameplayCamerasActivateCameraRigViaProxyTask : public FGameplayCamerasStateTreeTask`  
_L71-98_
- reflection: `USTRUCT(meta=(DisplayName="Activate Camera via Proxy", Category="Cameras"))`
- inherits: `FGameplayCamerasStateTreeTask`
- desc: A task that activates a camera rig via the given camera rig proxy inside a StateTreeCameraDirector. The given proxy must be mapped to an actual proxy in each camera asset using this StateTree.
- L75 _public typedef_ `using FInstanceDataType = FGameplayCamerasActivateCameraRigViaProxyTaskInstanceData;`
- L80 _protected function_ `virtual const UStruct* GetInstanceDataType() const override` — FStateTreeTaskBase interface.
- L81 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L82 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L83 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L87 _private prototype_ `bool UpdateResult(FStateTreeExecutionContext& Context) const;`
- L91 _private member_ `TStateTreeExternalDataHandle<FCameraDirectorStateTreeEvaluationData> CameraDirectorEvaluationDataHandle;`
- L97 _public member_ `bool bRunOnce = false;` — `UPROPERTY(EditAnywhere, Category="State Tree")` — If true, the task will complete immediately. If false, the task will run until a transition triggers.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/ActivateCameraRigFunctions.h` (Public)


#### class `UActivateCameraRigFunctions`  
`class UActivateCameraRigFunctions : public UBlueprintFunctionLibrary`  
_L24-46_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint functions for activating camera rigs in the base/global/visual layers. These camera rigs run with a global, shared evaluation context that doesn't provide any meaningful initial result. They are activated on the camera system found to be running on the given player controller. Deprecated in 5.7.0
- L32 _public prototype_ `static void ActivatePersistentBaseCameraRig(UObject* WorldContextObject, APlayerController* PlayerController, UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta=(WorldContext="WorldContextObject", DeprecatedFunction, DeprecationMessage="Use the similar functions on the GameplayCamera components or camera manager"))` — Activates the given camera rig prefab in the base layer.
- L36 _public prototype_ `static void ActivatePersistentGlobalCameraRig(UObject* WorldContextObject, APlayerController* PlayerController, UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta = (WorldContext = "WorldContextObject", DeprecatedFunction, DeprecationMessage="Use the similar functions on the GameplayCamera components or camera manager"))` — Activates the given camera rig prefab in the global layer.
- L40 _public prototype_ `static void ActivatePersistentVisualCameraRig(UObject* WorldContextObject, APlayerController* PlayerController, UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta = (WorldContext = "WorldContextObject", DeprecatedFunction, DeprecationMessage="Use the similar functions on the GameplayCamera components or camera manager"))` — Activates the given camera rig prefab in the visual layer.
- L45 _private prototype_ `static void ActivateCameraRigImpl(UObject* WorldContextObject, APlayerController* PlayerController, UCameraRigAsset* CameraRig, ECameraRigLayer EvaluationLayer);` — Activates the given camera rig in the given layer. Should not be used with Main layer.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/ActorCameraEvaluationContext.h` (Public)


#### class `UE::Cameras::FActorCameraEvaluationContext`  
`class FActorCameraEvaluationContext : public FCameraEvaluationContext`  
_L22-41_
- inherits: `FCameraEvaluationContext`
- desc: An evaluation context for an arbitrary actor. It procedurally creates a single camera director that runs a rig only composed of a camera node that simply copies the actor's properties.
- L28 _public prototype_ `FActorCameraEvaluationContext();`
- L29 _public prototype_ `FActorCameraEvaluationContext(UCameraComponent* InCameraComponent);`
- L30 _public prototype_ `FActorCameraEvaluationContext(AActor* InActor);`
- L34 _public prototype_ `static void ApplyMinimalViewInfo(const FMinimalViewInfo& ViewInfo, FCameraNodeEvaluationResult& OutResult);`
- L38 _private prototype_ `static UCameraAsset* MakeCameraComponentCameraAsset(UObject* OuterObject);`
- L39 _private prototype_ `static UCameraAsset* MakeCalcCameraActorCameraAsset(UObject* OuterObject);`
- L40 _private prototype_ `static UCameraAsset* MakeSimpleCameraAsset(UObject* OuterObject, UCameraNode* RootNode);`

#### class `UCameraComponentCameraNode`  
`class UCameraComponentCameraNode : public UCameraNode`  
_L52-60_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UCameraNode`
- desc: A simple camera node that copies the properties of a camera component and applies them to the evaluation output. Note that this node expects to run inside an evaluation context owned by the camera component's parent actor.
- L59 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

#### class `UCalcCameraActorCameraNode`  
`class UCalcCameraActorCameraNode : public UCameraNode`  
_L68-76_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UCameraNode`
- desc: A simple camera node that calls an actor's CalcCamera functoin and copies the result to the evaluation output. Note that this node expects to run inside an evaluation context owned by that actor.
- L75 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/BlueprintCameraEvaluationDataRef.h` (Public)


#### struct `FBlueprintCameraEvaluationDataRef`  
`struct FBlueprintCameraEvaluationDataRef`  
_L28-54_
- reflection: `USTRUCT(BlueprintType, DisplayName="Camera Evaluation Data Ref", meta=(HasNativeMake="/Script/GameplayCameras.BlueprintCameraEvaluationDataFunctionLibrary.MakeCameraEvaluationData"))`
- desc: Blueprint wrapper for camera evaluation data.
- L34 _public typedef_ `using FCameraNodeEvaluationResult = UE::Cameras::FCameraNodeEvaluationResult;`
- L36 _public prototype_ `FBlueprintCameraEvaluationDataRef();`
- L38 _public function_ `bool IsValid() const`
- L40 _public function_ `FCameraNodeEvaluationResult* GetResult() const`
- L44 _public prototype_ `static FBlueprintCameraEvaluationDataRef MakeExternalRef(FCameraNodeEvaluationResult* InResult);`
- L45 _public prototype_ `static FBlueprintCameraEvaluationDataRef MakeOwningRef();`
- L50 _private member_ `FCameraNodeEvaluationResult* Result = nullptr;` — The underlying camera evaluation result.
- L53 _private member_ `TSharedPtr<FCameraNodeEvaluationResult> SharedResult;` — If the underlying camera evaluation result is owned by this data ref, a shared pointer to keep it alive.

#### class `UBlueprintCameraEvaluationDataFunctionLibrary`  
`class UBlueprintCameraEvaluationDataFunctionLibrary : public UBlueprintFunctionLibrary`  
_L60-89_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for camera evaluation data references.
- L68 _public prototype_ `static FBlueprintCameraEvaluationDataRef MakeCameraEvaluationData();` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(ReturnDisplayName="Camera Evaluation Data"))` — Creates a camera evaluation data.
- L74 _public prototype_ `static FBlueprintCameraPose GetCameraPose(const FBlueprintCameraEvaluationDataRef& CameraData);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the camera pose.
- L78 _public prototype_ `static void SetCameraPose(const FBlueprintCameraEvaluationDataRef& CameraData, const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Sets the camera pose.
- L84 _public prototype_ `static void BlendCameraEvaluationData(const FBlueprintCameraEvaluationDataRef& FromCameraData, const FBlueprintCameraEvaluationDataRef& ToCameraData, float Factor);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Interpolates one camera data towards another.
- L88 _public prototype_ `static void SetDefaultCameraRigParameters(const FBlueprintCameraEvaluationDataRef& CameraData, const UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets the default values for all parameters in the given camera rig.

#### class `UBlueprintCameraVariableTableFunctionLibrary`  
`class UBlueprintCameraVariableTableFunctionLibrary : public UBlueprintFunctionLibrary`  
_L95-174_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for camera variable tables.
- L103 _public prototype_ `static bool GetBooleanCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UBooleanCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Boolean Variable", Category=Camera, meta=(CompactNodeTitle="Get Boolean Variable"))` — Gets a camera variable's value from the given table.
- L107 _public prototype_ `static int32 GetInteger32CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UInteger32CameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Integer Variable", Category=Camera, meta=(CompactNodeTitle="Get Integer Variable"))` — Gets a camera variable's value from the given table.
- L111 _public prototype_ `static float GetFloatCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UFloatCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Float Variable", Category=Camera, meta=(CompactNodeTitle="Get Float Variable"))` — Gets a camera variable's value from the given table.
- L115 _public prototype_ `static double GetDoubleCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UDoubleCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Double Variable", Category=Camera, meta=(CompactNodeTitle="Get Double Variable"))` — Gets a camera variable's value from the given table.
- L119 _public prototype_ `static FVector2D GetVector2CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UVector2dCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Vector 2D Variable", Category=Camera, meta=(CompactNodeTitle="Get Vector 2D Variable"))` — Gets a camera variable's value from the given table.
- L123 _public prototype_ `static FVector GetVector3CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UVector3dCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Vector Variable", Category=Camera, meta=(CompactNodeTitle="Get Vector Variable"))` — Gets a camera variable's value from the given table.
- L127 _public prototype_ `static FVector4 GetVector4CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UVector4dCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Vector 4 Variable", Category=Camera, meta=(CompactNodeTitle="Get Vector 4 Variable"))` — Gets a camera variable's value from the given table.
- L131 _public prototype_ `static FRotator GetRotatorCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, URotator3dCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Rotator Variable", Category=Camera, meta=(CompactNodeTitle="Get Rotator Variable"))` — Gets a camera variable's value from the given table.
- L135 _public prototype_ `static FTransform GetTransformCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UTransform3dCameraVariable* Variable);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Transform Variable", Category=Camera, meta=(CompactNodeTitle="Get Transform Variable"))` — Gets a camera variable's value from the given table.
- L141 _public prototype_ `static void SetBooleanCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UBooleanCameraVariable* Variable, bool Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Boolean Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L145 _public prototype_ `static void SetInteger32CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UInteger32CameraVariable* Variable, int32 Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Integer Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L149 _public prototype_ `static void SetFloatCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UFloatCameraVariable* Variable, float Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Float Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L153 _public prototype_ `static void SetDoubleCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UDoubleCameraVariable* Variable, double Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Double Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L157 _public prototype_ `static void SetVector2CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UVector2dCameraVariable* Variable, const FVector2D& Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Vector 2D Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L161 _public prototype_ `static void SetVector3CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UVector3dCameraVariable* Variable, const FVector& Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Vector Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L165 _public prototype_ `static void SetVector4CameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UVector4dCameraVariable* Variable, const FVector4& Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Vector 4 Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L169 _public prototype_ `static void SetRotatorCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, URotator3dCameraVariable* Variable, const FRotator& Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Rotator Variable", Category=Camera)` — Sets a camera variable's value in the given table.
- L173 _public prototype_ `static void SetTransformCameraVariable(const FBlueprintCameraEvaluationDataRef& CameraData, UTransform3dCameraVariable* Variable, const FTransform& Value);` — `UFUNCTION(BlueprintCallable, DisplayName="Set Transform Variable", Category=Camera)` — Sets a camera variable's value in the given table.

#### class `UBlueprintCameraContextDataTableFunctionLibrary`  
`class UBlueprintCameraContextDataTableFunctionLibrary : public UBlueprintFunctionLibrary`  
_L180-235_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Utility Blueprint functions for camera context data tables.
- L188 _public prototype_ `static FName GetNameData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Gets a value from the given camera context data table.
- L192 _public prototype_ `static FString GetStringData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Gets a value from the given camera context data table.
- L196 _public prototype_ `static uint8 GetEnumData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, const UEnum* EnumType);` — `UFUNCTION(BlueprintCallable, Category=Camera, meta=(DeterminesOutputType="EnumType"))` — Gets a value from the given camera context data table.
- L200 _public prototype_ `static FInstancedStruct GetStructData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, const UScriptStruct* DataStructType);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Gets a value from the given camera context data table.
- L204 _public prototype_ `static UObject* GetObjectData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Gets a value from the given camera context data table.
- L208 _public prototype_ `static UClass* GetClassData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Gets a value from the given camera context data table.
- L214 _public prototype_ `static bool SetNameData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, const FName& Data);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets a value in the given camera context data table.
- L218 _public prototype_ `static bool SetStringData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, const FString& Data);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets a value in the given camera context data table.
- L222 _public prototype_ `static bool SetEnumData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, const UEnum* EnumType, uint8 Data);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets a value in the given camera context data table.
- L226 _public prototype_ `static bool SetStructData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, const FInstancedStruct& Data);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets a value in the given camera context data table.
- L230 _public prototype_ `static bool SetObjectData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, UObject* Data);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets a value in the given camera context data table.
- L234 _public prototype_ `static bool SetClassData(const FBlueprintCameraEvaluationDataRef& CameraData, FCameraContextDataID DataID, UClass* Data);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets a value in the given camera context data table.

#### class `UBlueprintPostProcessSettingsCollectionFunctionLibrary`  
`class UBlueprintPostProcessSettingsCollectionFunctionLibrary : public UBlueprintFunctionLibrary`  
_L241-262_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Utility Blueprint functions for camera post process settings.
- L249 _public prototype_ `static void GetPostProcessSettings(const FBlueprintCameraEvaluationDataRef& CameraData, FPostProcessSettings& OutPostProcessSettings);` — `UFUNCTION(BlueprintPure, Category=Camera)` — Gets the post-process settings.
- L253 _public prototype_ `static void SetPostProcessSettings(const FBlueprintCameraEvaluationDataRef& CameraData, const FPostProcessSettings& PostProcessSettings);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets the post-process settings.
- L257 _public prototype_ `static void OverrideChangedPostProcessSettings(const FBlueprintCameraEvaluationDataRef& CameraData, const FPostProcessSettings& PostProcessSettings);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Overrides the post-process settings with the given ones. Only set properties are written.
- L261 _public prototype_ `static void LerpPostProcessSettings(const FBlueprintCameraEvaluationDataRef& CameraData, const FPostProcessSettings& PostProcessSettings, float BlendFactor);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Interpolate the post-process settings towards the given ones. Only set properties are interpolated.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/BlueprintCameraPose.h` (Public)


#### struct `FBlueprintCameraPose`  
`struct FBlueprintCameraPose`  
_L27-155_
- reflection: `USTRUCT(BlueprintType, meta=(DisplayName="Camera Pose"))`
- desc: Represents a camera pose.
- L35 _public member_ `FVector Location = {0, 0, 0};` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The location of the camera.
- L39 _public member_ `FRotator Rotation = {0, 0, 0};` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The rotation of the camera.
- L43 _public member_ `double TargetDistance = 1000.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The distance of the target of the camera.
- L47 _public member_ `float FieldOfView = -1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The field of view of the camera. May be negative if driven by focal length.
- L51 _public member_ `float FocalLength = 35.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The focal length of the camera. May be negative if driven directly by field of view.
- L55 _public member_ `float FirstPersonFieldOfView = 90.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The horizontal field of view (in degrees) used for primitives tagged as "IsFirstPerson"
- L59 _public member_ `float FirstPersonScale = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The scale to apply to primitives tagged as "IsFirstPerson"
- L63 _public member_ `float OrthographicWidth = DEFAULT_ORTHOWIDTH;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")` — The desired width (in world units) of the orthographic view (ignored in Perspective mode)
- L67 _public member_ `float Aperture = 2.8f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The aperture (f-stop) of the camera's lens.
- L71 _public member_ `float ShutterSpeed = 60.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The shutter speed of the camera's lens, in 1/seconds
- L75 _public member_ `float FocusDistance = -1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The focus distance of the camera, if different from target distance.
- L79 _public member_ `float SensorWidth = 24.89f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The width of the camera's sensor.
- L83 _public member_ `float SensorHeight = 18.67f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The height of the camera's sensor.
- L87 _public member_ `float SensorHorizontalOffset = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — Horizontal offset of the sensor, in mm.
- L91 _public member_ `float SensorVerticalOffset = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — Vertical offset of the sensor, in mm.
- L95 _public member_ `float ISO = 100.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The camera sensor sensitivity in ISO.
- L99 _public member_ `float SqueezeFactor = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The squeeze factor of the camera's lens.
- L103 _public member_ `float Overscan = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — Sensor overscan in percentage
- L107 _public member_ `int32 DiaphragmBladeCount = 8;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — Number of blades in the lens diaphragm
- L111 _public member_ `float NearClippingPlane = 10.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The camera's near clipping plane.
- L115 _public member_ `float FarClippingPlane = -1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The camera's far clipping plane.
- L119 _public member_ `float PhysicalCameraBlendWeight = 0.f;` — `UPROPERTY()` — Internal weight for physical camera post-process settings.
- L123 _public member_ `bool EnableFirstPerson = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")` — Whether to enable first-person parameters (FOV, scale) for primitives tagged as "IsFirstPerson"
- L130 _public member_ `bool EnablePhysicalCamera = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — Whether to setup post-process settings based on physical camera properties such as Aperture, FocusDistance, DiaphragmBladeCount, and so on.
- L134 _public member_ `bool ConstrainAspectRatio = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — Whether the camera should constrain aspect ratio.
- L138 _public member_ `bool OverrideAspectRatioAxisConstraint = false;` — `UPROPERTY()` — Whether to override the default aspect ratio axis constraint defined on the player controller
- L142 _public member_ `TEnumAsByte<EAspectRatioAxisConstraint> AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")` — The aspect ratio axis constraint to use if aspect ratio is constrained.
- L146 _public member_ `TEnumAsByte<ECameraProjectionMode::Type> ProjectionMode = ECameraProjectionMode::Perspective;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")` — Projection mode - Perspective or orthographic
- L151 _public prototype_ `static FBlueprintCameraPose FromCameraPose(const FCameraPose& InCameraPose);` — Creates a new BP camera pose from a raw camera pose structure.
- L154 _public prototype_ `void ApplyTo(FCameraPose& OutCameraPose) const;` — Applies this BP camera pose's values to the given raw camera pose.

#### class `UBlueprintCameraPoseFunctionLibrary`  
`class UBlueprintCameraPoseFunctionLibrary : public UBlueprintFunctionLibrary`  
_L161-242_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Utility Blueprint functions for camera poses.
- L169 _public prototype_ `static FTransform GetTransform(const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the transform matrix of the camera pose.
- L173 _public prototype_ `static double GetEffectiveFieldOfView(const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the effective field of view of the camera pose, possibly computed from focal length.
- L177 _public prototype_ `static double GetSensorAspectRatio(const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the effective aspect ratio of the camera pose, computed from the sensor size.
- L181 _public prototype_ `static FRay GetAimRay(const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the aim ray of the camera pose.
- L185 _public prototype_ `static FVector GetAimDir(const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the facing direction of the camera pose.
- L189 _public prototype_ `static FVector GetTarget(const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the target of the camera pose.
- L193 _public prototype_ `static FVector GetTargetAtDistance(const FBlueprintCameraPose& CameraPose, double TargetDistance);` — `UFUNCTION(BlueprintPure, Category="Camera")` — Gets the target of the camera pose given a specific target distance.
- L199 _public prototype_ `static FBlueprintCameraPose SetTransform(const FBlueprintCameraPose& CameraPose, const FTransform& Transform);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Creates a copy of the given camera pose with the given location and rotation.
- L205 _public prototype_ `static FBlueprintCameraPose MakeCameraPoseFromCameraComponent(const UCameraComponent* CameraComponent);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Creates a new camera pose given a camera component.
- L209 _public prototype_ `static FBlueprintCameraPose MakeCameraPoseFromCineCameraComponent(const UCineCameraComponent* CameraComponent);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Creates a new camera pose given a cine-camera component.
- L214 _public function_ `static inline FVector GetLocation(const FBlueprintCameraPose& CameraPose)` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Break node"))`
- L217 _public function_ `static inline FRotator GetRotation(const FBlueprintCameraPose& CameraPose)` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Break node"))`
- L220 _public function_ `static inline double GetTargetDistance(const FBlueprintCameraPose& CameraPose)` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Break node"))`
- L223 _public function_ `static inline double GetFieldOfView(const FBlueprintCameraPose& CameraPose)` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Break node"))`
- L226 _public function_ `static inline double GetFocalLength(const FBlueprintCameraPose& CameraPose)` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Break node"))`
- L229 _public prototype_ `static FBlueprintCameraPose SetLocation(const FBlueprintCameraPose& CameraPose, const FVector& Location);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Set Members node"))`
- L232 _public prototype_ `static FBlueprintCameraPose SetRotation(const FBlueprintCameraPose& CameraPose, const FRotator& Rotation);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Set Members node"))`
- L235 _public prototype_ `static FBlueprintCameraPose SetTargetDistance(const FBlueprintCameraPose& CameraPose, double TargetDistance);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Set Members node"))`
- L238 _public prototype_ `static FBlueprintCameraPose SetFieldOfView(const FBlueprintCameraPose& CameraPose, float FieldOfView);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Set Members node"))`
- L241 _public prototype_ `static FBlueprintCameraPose SetFocalLength(const FBlueprintCameraPose& CameraPose, float FocalLength);` — `UFUNCTION(BlueprintCallable, Category="Camera", meta=(DeprecatedFunction, DeprecationMessage="Please use the standard Set Members node"))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/CameraRigParameterInterop.h` (Public)


#### class `UCameraRigParameterInterop`  
`class UCameraRigParameterInterop : public UBlueprintFunctionLibrary`  
_L23-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint internal methods to set values on a camera rig's exposed parameters. These functions are internal because users are supposed to use the K2Node_SetCameraRigParameters node instead. That node then gets compiled into one or more of these internal functions.
- L29 _public prototype_ `UCameraRigParameterInterop(const FObjectInitializer& ObjectInit);`
- L34 _public prototype_ `static void GetCameraParameter(UPARAM(Ref) const FBlueprintCameraEvaluationDataRef& CameraData, UCameraRigAsset* CameraRig, FName ParameterName, int32& ReturnValue);` — `UFUNCTION(BlueprintPure, CustomThunk, Category="Camera", meta=(BlueprintInternalUseOnly="true", CustomStructureParam="ReturnValue"))`
- L37 _public prototype_ `static void SetCameraParameter(UPARAM(Ref) const FBlueprintCameraEvaluationDataRef& CameraData, UCameraRigAsset* CameraRig, FName ParameterName, UPARAM(Ref) const int32& NewValue);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category="Camera", meta=(BlueprintInternalUseOnly="true", CustomStructureParam="NewValue"))`

#### class `UCameraRigParameterInteropLibrary`  
`class UCameraRigParameterInteropLibrary : public UBlueprintFunctionLibrary`  
_L49-69_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Internal Blueprint function library for creating default values of the SetCameraParameter node above.
- L56 _public prototype_ `static FVector MakeLiteralVector(FVector Value);` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(BlueprintThreadSafe, BlueprintInternalUseOnly="true"))`
- L59 _public prototype_ `static FVector3f MakeLiteralVector3f(FVector3f Value);` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(BlueprintThreadSafe, BlueprintInternalUseOnly="true"))`
- L62 _public prototype_ `static FVector2D MakeLiteralVector2D(FVector2D Value);` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(BlueprintThreadSafe, BlueprintInternalUseOnly="true"))`
- L65 _public prototype_ `static FRotator MakeLiteralRotator(FRotator Value);` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(BlueprintThreadSafe, BlueprintInternalUseOnly="true"))`
- L68 _public prototype_ `static FLinearColor MakeLiteralLinearColor(FLinearColor Value);` — `UFUNCTION(BlueprintPure, Category="Camera", meta=(BlueprintThreadSafe, BlueprintInternalUseOnly="true"))`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/ControllerGameplayCameraEvaluationComponent.h` (Public)


#### class `UControllerGameplayCameraEvaluationComponent`  
`class UControllerGameplayCameraEvaluationComponent : public UActorComponent`  
_L25-69_
- reflection: `UCLASS(Hidden)`
- inherits: `UActorComponent`
- desc: A component, attached to a player controller, that can run camera rigs activated from a global place like the Blueprint functions inside UActivateCameraRigFunctions.
- L31 _public prototype_ `UControllerGameplayCameraEvaluationComponent(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `void Initialize(TScriptInterface<IGameplayCameraSystemHost> InCameraSystemHost, APlayerController* InPlayerController = nullptr);` — Initializes this component's evaluation context.
- L37 _public prototype_ `void ActivateCameraRig(UCameraRigAsset* CameraRig, ECameraRigLayer EvaluationLayer);` — Activates a new camera rig.
- L41 _public prototype_ `static UControllerGameplayCameraEvaluationComponent* FindComponent(AActor* OwnerActor);`
- L42 _public prototype_ `static UControllerGameplayCameraEvaluationComponent* FindOrAddComponent(AActor* OwnerActor, bool* bOutCreated = nullptr);`
- L47 _public prototype_ `virtual void BeginPlay() override;` — UActorComponent interface.
- L48 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L52 _private prototype_ `void ActivateCameraRigs();`
- L63 _private member_ `TArray<FCameraRigInfo> CameraRigInfos;`
- L65 _private member_ `TSharedPtr<UE::Cameras::FCameraEvaluationContext> EvaluationContext;`
- L68 _private member_ `TScriptInterface<IGameplayCameraSystemHost> CameraSystemHost;` — `UPROPERTY()`

#### struct `UControllerGameplayCameraEvaluationComponent::FCameraRigInfo`  
`struct FCameraRigInfo`  
_L56-61_
- L58 _public member_ `TObjectPtr<UCameraRigAsset> CameraRig;`
- L59 _public member_ `ECameraRigLayer EvaluationLayer;`
- L60 _public member_ `bool bActivated = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraActor.h` (Public)


#### class `AGameplayCameraActor`  
`class AGameplayCameraActor : public AGameplayCameraActorBase`  
_L16-51_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ClassGroup=Camera, HideCategories=(OutputCamera))`
- inherits: `AGameplayCameraActorBase`
- desc: An actor that can run a camera asset.
- L22 _public prototype_ `AGameplayCameraActor(const FObjectInitializer& ObjectInit);`
- L28 _public function_ `UGameplayCameraComponent* GetCameraComponent() const` — `UFUNCTION(BlueprintGetter, Category=Camera)` — Gets the camera component.
- L32 _public function_ `UCineCameraComponent* GetOutputCameraComponent() const` — `UFUNCTION(BlueprintGetter, Category=Camera)` — Gets the output camera component.
- L37 _public prototype_ `virtual USceneComponent* GetDefaultAttachComponent() const override;` — AActor interface.
- L42 _protected prototype_ `virtual UGameplayCameraComponentBase* GetCameraComponentBase() const override;` — AGameplayCameraActorBase interface.
- L47 _private member_ `TObjectPtr<UGameplayCameraComponent> CameraComponent;` — `UPROPERTY(VisibleAnywhere, Category=GameplayCamera, BlueprintGetter="GetCameraComponent", meta=(ExposeFunctionCategories="Camera"))`
- L50 _private member_ `TObjectPtr<UCineCameraComponent> OutputCameraComponent;` — `UPROPERTY(Transient, VisibleAnywhere, Category=OutputCamera, BlueprintGetter="GetOutputCameraComponent")`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraActorBase.h` (Public)


#### class `AGameplayCameraActorBase`  
`class AGameplayCameraActorBase : public AActor`  
_L21-37_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ClassGroup=Camera)`
- inherits: `AActor`
- desc: A base class for actors that can run a camera object. When the actor becomes the view target, it is able to start updating itself by instantiating a private instance of the camera system. It does this if no camera system was found attached under the player controller.
- L27 _public prototype_ `AGameplayCameraActorBase(const FObjectInitializer& ObjectInit);`
- L32 _public prototype_ `virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;` — AActor interface.
- L36 _protected function_ `virtual UGameplayCameraComponentBase* GetCameraComponentBase() const`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraComponent.h` (Public)


#### class `UGameplayCameraComponent`  
`class UGameplayCameraComponent : public UGameplayCameraComponentBase`  
_L16-72_
- reflection: `UCLASS(Blueprintable, MinimalAPI, ClassGroup=Camera, meta=(BlueprintSpawnableComponent))`
- inherits: `UGameplayCameraComponentBase`
- desc: A component that can run a camera asset inside its own camera evaluation context.
- L23 _public prototype_ `UGameplayCameraComponent(const FObjectInitializer& ObjectInit);` — Create a new camera component.
- L28 _public prototype_ `virtual void OnRegister() override;` — UActorComponent interface.
- L29 _public prototype_ `virtual void OnUnregister() override;`
- L32 _public prototype_ `virtual void PostLoad() override;` — UObject interface.
- L33 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _public member_ `FCameraAssetReference CameraReference;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera, meta=(InterpNotify="NotifyChangeCameraReference", SequencerHideProperty=true))` — The camera asset to run.
- L47 _protected prototype_ `void NotifyChangeCameraReference();` — `UFUNCTION()`
- L50 _protected prototype_ `virtual UCameraAsset* OnCreateEvaluationContext() override;` — UGameplayCameraComponentBase interface.
- L51 _protected prototype_ `virtual void OnUpdateEvaluationContext(bool bForceApplyParameterOverrides) override;`
- L55 _private prototype_ `void ApplyChangedParameterOverrides();`
- L58 _private prototype_ `void OnCameraAssetBuilt(const UCameraAsset* InCameraAsset);`
- L65 _private member_ `FInstancedPropertyBag CachedParameterOverrides;` — `UPROPERTY(Transient)` — Cached parameter overrides, for detecting when some of them change.
- L71 _private member_ `TObjectPtr<UCameraAsset> Camera_DEPRECATED;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraComponentBase.h` (Public)


#### class `UGameplayCameraComponentBase`  
`class UGameplayCameraComponentBase : public USceneComponent , public IGameplayCameraSystemHost`  
_L45-347_
- reflection: `UCLASS(Blueprintable, MinimalAPI, Abstract, ClassGroup=Camera, HideCategories=(Object, ActorComponent, Physics, Rendering, Mobility, LOD), PrioritizeCategories=(Camera, EditorCamera, Activation), meta=(BlueprintSpawnableComponent))`
- inherits: `USceneComponent,IGameplayCameraSystemHost`
- desc: A component that can run a camera asset inside its own camera evaluation context.
- L54 _public prototype_ `UGameplayCameraComponentBase(const FObjectInitializer& ObjectInit);` — Create a new camera component.
- L59 _public prototype_ `TSharedPtr<const UE::Cameras::FCameraEvaluationContext> GetEvaluationContext() const;` — Get the camera evaluation context used by this component.
- L62 _public prototype_ `TSharedPtr<UE::Cameras::FCameraEvaluationContext> GetEvaluationContext();` — Get the camera evaluation context used by this component.
- L65 _public function_ `bool HasEvaluationContext() const` — Returns whether an evaluation context exists in this component.
- L71 _public function_ `UCineCameraComponent* GetOutputCameraComponent() const` — `UFUNCTION(BlueprintGetter, Category=Camera)` — Gets the child camera component used as the "output" for the gameplay/procedural camera.
- L80 _public prototype_ `void ActivateCameraForPlayerIndex(int32 PlayerIndex, bool bSetAsViewTarget = true);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Activates the camera for the given player. @param PlayerIndex        The player to activate the camera for. @param bSetAsViewTarget   Whether to set this component's actor as the view target for the player.
- L89 _public prototype_ `void ActivateCameraForPlayerController(APlayerController* PlayerController, bool bSetAsViewTarget = true);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Activates the camera for the given player. @param PlayerController   The player to activate the camera for. @param bSetAsViewTarget   Whether to set this component's actor as the view target for the player.
- L93 _public prototype_ `FBlueprintCameraEvaluationDataRef GetInitialResult() const;` — `UFUNCTION(BlueprintPure, Category=Camera, meta=(DisplayName="Get Shared Camera Data"))` — Gets the shared camera evaluation data for this component's evaluation context.
- L97 _public prototype_ `FBlueprintCameraEvaluationDataRef GetConditionalResult(ECameraEvaluationDataCondition Condition) const;` — `UFUNCTION(BlueprintPure, Category=Camera, meta=(DisplayName="Get Conditional Camera Data"))` — Gets the camera evaluation data for a given sub-set of camera rigs in this component's evaluation context.
- L101 _public prototype_ `FRotator GetEvaluatedCameraRotation() const;` — `UFUNCTION(BlueprintPure, Category=Camera)` — Gets the last evaluated orientation of the camera.
- L107 _public prototype_ `FCameraRigInstanceID ActivatePersistentBaseCameraRig(UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Activates the given camera rig prefab in the base layer.
- L111 _public prototype_ `FCameraRigInstanceID ActivatePersistentGlobalCameraRig(UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Activates the given camera rig prefab in the global layer.
- L115 _public prototype_ `FCameraRigInstanceID ActivatePersistentVisualCameraRig(UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Activates the given camera rig prefab in the visual layer.
- L119 _public prototype_ `void DeactivateCameraRig(FCameraRigInstanceID InstanceID, bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Deactivates a previously activated base, global, or visual camera rig.
- L125 _public prototype_ `FCameraRigInstanceID StartGlobalCameraModifierRig(const UCameraRigAsset* CameraRig, int32 OrderKey = 0);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Starts a camera modifier rig on the global layer.
- L129 _public prototype_ `FCameraRigInstanceID StartVisualCameraModifierRig(const UCameraRigAsset* CameraRig, int32 OrderKey = 0);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Starts a camera modifier rig on the visual layer.
- L133 _public prototype_ `void StopCameraModifierRig(FCameraRigInstanceID InstanceID, bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Stops a camera modifier rig on previously started on the global or visual layer.
- L139 _public prototype_ `FCameraShakeInstanceID StartCameraShakeAsset( const UCameraShakeAsset* CameraShake, float ShakeScale = 1.f, ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal, FRotator UserPlaySpaceRotation = FRotator::ZeroRotator);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Starts a new camera shake.
- L147 _public prototype_ `bool IsCameraShakeAssetPlaying(FCameraShakeInstanceID InInstanceID) const;` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Checks if a camera shake is running.
- L151 _public prototype_ `bool StopCameraShakeAsset(FCameraShakeInstanceID InInstanceID, bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Stops a running camera shake.
- L157 _public prototype_ `FCameraActionInstanceID StartAction(const UCameraAction* CameraAction);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Starts the given camera action.
- L161 _public prototype_ `bool IsActionRunning(FCameraActionInstanceID InInstanceID);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Returns whether the given camera action instance is still running.
- L165 _public prototype_ `bool StopAction(FCameraActionInstanceID InInstanceID);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Stops the given camera action instance.
- L169 _public prototype_ `bool StopAllActionsOfClass(TSubclassOf<UCameraAction> InActionClass);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Stops all camera actions of a given class.
- L174 _public prototype_ `virtual void OnRegister() override;` — UActorComponent interface
- L175 _public prototype_ `virtual void BeginPlay() override;`
- L176 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L177 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L178 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L179 _public prototype_ `virtual void Deactivate() override;`
- L180 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L182 _public prototype_ `virtual bool GetEditorPreviewInfo(float DeltaTime, FMinimalViewInfo& ViewOut) override;`
- L186 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;` — USceneComponent interface.
- L189 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface.
- L191 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L194 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L197 _public function_ `virtual UObject* GetAsObject() override` — IGameplayCameraSystemHost interface.
- L204 _public prototype_ `void OnDrawVisualizationHUD(const FViewport* Viewport, const FSceneView* SceneView, FCanvas* Canvas) const;`
- L212 _public function_ `void DeactivateCamera(bool bImmediately = false)` — `UFUNCTION(BlueprintCallable, Category="Camera", meta=(DeprecatedFunction, DeprecatedMessage="Please use Deactivate"))`
- L217 _protected function_ `virtual UCameraAsset* OnCreateEvaluationContext()` — UGameplayCameraComponentBase interface.
- L218 _protected function_ `virtual void OnUpdateEvaluationContext(bool bForceApplyParameterOverrides)`
- L220 _protected prototype_ `void UpdateEvaluationContext(bool bForceApplyParameterOverrides);`
- L222 _protected prototype_ `void GetChangedParameterOverrides( const FInstancedPropertyBag& InParameterOverrides, FInstancedPropertyBag& InOutCachedParameterOverrides, TArray<FGuid>& OutChangedParameterGuids);`
- L227 _protected prototype_ `bool IsEditorWorld() const;`
- L228 _protected prototype_ `void UpdateControlRotationIfNeeded();`
- L231 _protected prototype_ `void ReinitializeEvaluationContext( const FCameraVariableTableAllocationInfo& VariableTableAllocationInfo, const FCameraContextDataTableAllocationInfo& ContextDataTableAllocationInfo);`
- L234 _protected prototype_ `void RecreateEditorWorldEvaluationContext();`
- L236 _protected prototype_ `void CreateCameraSpriteComponent(const FString& SpriteTexturePath);`
- L241 _private prototype_ `bool CanRunCameraSystem() const;`
- L242 _private prototype_ `bool EnsureCameraSystemHostIfNeeded();`
- L243 _private prototype_ `void DestroyCameraSystemHost();`
- L245 _private prototype_ `void EnsureEvaluationContext(APlayerController* PlayerController);`
- L246 _private prototype_ `void DestroyEvaluationContext();`
- L248 _private prototype_ `void EnsureOutputCameraComponent();`
- L249 _private prototype_ `void UpdateOutputCameraComponent();`
- L252 _private prototype_ `void AutoManageEditorPreviewEvaluator();`
- L253 _private prototype_ `void OnEditorPreviewCameraRigIndexChanged();`
- L254 _private prototype_ `void UpdateCameraSpriteComponent();`
- L267 _public member_ `TEnumAsByte<EAutoReceiveInput::Type> DefaultPlayer = EAutoReceiveInput::Player0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Activation)` — The player controller to bind to by default. Auto-activation and explicit calls to Activate will use this player, if valid. Calls to ActivateCameraForPlayerIndex and ActivateCameraForPlayerController will use their given player, but fall back to this player if they are given an invalid parameter.
- L276 _public member_ `bool bRunStandaloneCameraSystem = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera)` — When enabled, this camera component runs its own camera system when activated, which makes it possible for it to run independently. When disabled, this camera component only creates an evaluation context that must be run with an external camera system, such as the Gameplay Cameras Player Camera Manager.
- L285 _public member_ `bool bSetControlRotationWhenViewTarget = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera, meta=(EditCondition="bRunStandaloneCameraSystem"))` — Specifies whether this component should set the player controller's control rotation to the computed point of view's orientation every frame. This is only used when a player controller is associated with this component, and the view target is that component.
- L293 _public member_ `bool bPlaybackMode = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera)` — Enables or disables playback mode, which turns of any standalone camera system evaluation and lets the output camera component be manipulated externally. This is useful when the evaluated camera was recorded (e.g. with Take Recorder) and turned into keyframed animation.
- L299 _public member_ `bool bRunInEditor = true;` — `UPROPERTY(EditAnywhere, Category=EditorCamera)` — Whether to run this camera in editor.
- L303 _public member_ `int32 EditorPreviewCameraRigIndex = 0;` — `UPROPERTY(EditAnywhere, Category=EditorCamera, meta=(EditCondition="bRunInEditor"))` — The camera rig to run in the editor.
- L310 _public member_ `float EditorSpriteHiddenWhenOutputCameraWithinDistance = 100.f;` — `UPROPERTY(EditAnywhere, Category=EditorCamera)` — When the output camera's location is within this distance of the root, hide the editor sprite. Set this value to zero or negative to never hide the editor sprite.
- L321 _private member_ `TObjectPtr<UCineCameraComponent> OutputCameraComponent;` — `UPROPERTY(Transient)` — Camera component that receives the "output" of the hosted camera system when bRunStandaloneCameraSystem is enabled.
- L325 _private member_ `bool bIsOwnedOutputCameraComponent = false;` — `UPROPERTY()` — Whether the output camera component was auto-created, or obtained from the parent actor.
- L329 _private typedef_ `using FGameplayCameraComponentEvaluationContext = UE::Cameras::FGameplayCameraComponentEvaluationContext;`
- L330 _private typedef_ `using FCameraEvaluationContext = UE::Cameras::FCameraEvaluationContext;`
- L333 _private member_ `TSharedPtr<FGameplayCameraComponentEvaluationContext> EvaluationContext;` — Evaluation context.
- L336 _private member_ `bool bIsCameraCutNextFrame = false;` — Whether to force a camera cut next frame.
- L341 _private member_ `bool bIsEditorWorld = false;` — Whether this component is running in an editor world.
- L344 _private member_ `int32 CustomShowFlag = INDEX_NONE;` — The show flag for camera system debug rendering.

#### class `UE::Cameras::FGameplayCameraComponentEvaluationContext`  
`class FGameplayCameraComponentEvaluationContext : public FCameraEvaluationContext`  
_L355-366_
- inherits: `FCameraEvaluationContext`
- desc: Evaluation context for the gameplay camera component.
- L363 _public prototype_ `void UpdateForEditorPreview();`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Cameras` (scope `UE`)
- L349 _namespace_ `namespace UE`
- L349 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraParameterSetterComponent.h` (Public)


#### class `UGameplayCameraParameterSetterComponent`  
`class UGameplayCameraParameterSetterComponent : public UActorComponent`  
_L18-81_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ClassGroup=Camera, meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L24 _public prototype_ `UGameplayCameraParameterSetterComponent(const FObjectInitializer& ObjInit);`
- L30 _public member_ `FCameraRigAssetReference CameraRigReference;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera)` — The camera asset whose parameters to override.
- L34 _public member_ `float BlendInTime = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera)` — The blend-in time.
- L38 _public member_ `float BlendOutTime = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera)` — The blend-out time.
- L42 _public member_ `ECameraVariableSetterBlendType BlendType = ECameraVariableSetterBlendType::Linear;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera)` — The blend type.
- L48 _public prototype_ `void StartParameterSetters();` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Start setting parameters.
- L56 _public prototype_ `void StopParameterSetters(bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Stop setting parameters. @param bImmediately  If false, blend out the parameter overrides. If true, stop overrides immediately.
- L61 _public prototype_ `virtual void BeginPlay() override;` — UActorComponent interface.
- L62 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L67 _private prototype_ `void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);` — `UFUNCTION()`
- L70 _private prototype_ `void OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);` — `UFUNCTION()`
- L74 _private prototype_ `TSharedPtr<UE::Cameras::FCameraParameterSetterService> GetParameterSetterService();`
- L76 _private prototype_ `void InitializeParameterSetter(UE::Cameras::FCameraVariableSetter& VariableSetter);`
- L80 _private member_ `TArray<FCameraVariableSetterHandle> SetterHandles;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraRigActor.h` (Public)


#### class `AGameplayCameraRigActor`  
`class AGameplayCameraRigActor : public AGameplayCameraActorBase`  
_L16-51_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ClassGroup=Camera, HideCategories=(OutputCamera))`
- inherits: `AGameplayCameraActorBase`
- desc: An actor that can run a camera asset.
- L22 _public prototype_ `AGameplayCameraRigActor(const FObjectInitializer& ObjectInit);`
- L28 _public function_ `UGameplayCameraRigComponent* GetCameraRigComponent() const` — `UFUNCTION(BlueprintGetter, Category=Camera)` — Gets the camera component.
- L32 _public function_ `UCineCameraComponent* GetOutputCameraComponent() const` — `UFUNCTION(BlueprintGetter, Category=Camera)` — Gets the output camera component.
- L37 _public prototype_ `virtual USceneComponent* GetDefaultAttachComponent() const override;` — AActor interface.
- L42 _protected prototype_ `virtual UGameplayCameraComponentBase* GetCameraComponentBase() const override;` — AGameplayCameraActorBase interface.
- L47 _private member_ `TObjectPtr<UGameplayCameraRigComponent> CameraRigComponent;` — `UPROPERTY(VisibleAnywhere, Category=GameplayCamera, BlueprintGetter="GetCameraRigComponent", meta=(ExposeFunctionCategories="Camera"))`
- L50 _private member_ `TObjectPtr<UCineCameraComponent> OutputCameraComponent;` — `UPROPERTY(Transient, VisibleAnywhere, Category=OutputCamera, BlueprintGetter="GetOutputCameraComponent")`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraRigComponent.h` (Public)


#### class `UGameplayCameraRigComponent`  
`class UGameplayCameraRigComponent : public UGameplayCameraComponentBase`  
_L16-74_
- reflection: `UCLASS(Blueprintable, MinimalAPI, ClassGroup=Camera, meta=(BlueprintSpawnableComponent))`
- inherits: `UGameplayCameraComponentBase`
- desc: A component that can run a camera rig asset inside its own camera evaluation context.
- L23 _public prototype_ `UGameplayCameraRigComponent(const FObjectInitializer& ObjectInit);` — Create a new camera component.
- L28 _public prototype_ `virtual void OnRegister() override;` — UActorComponent interface.
- L29 _public prototype_ `virtual void OnUnregister() override;`
- L32 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;` — UObject interface.
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _public member_ `FCameraRigAssetReference CameraRigReference;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera, meta=(InterpNotify="NotifyChangeCameraRigReference", SequencerHideProperty=true))` — The camera rig asset to run.
- L46 _protected prototype_ `void NotifyChangeCameraRigReference();` — `UFUNCTION()`
- L49 _protected prototype_ `virtual UCameraAsset* OnCreateEvaluationContext() override;` — UGameplayCameraComponentBase interface.
- L50 _protected prototype_ `virtual void OnUpdateEvaluationContext(bool bForceApplyParameterOverrides) override;`
- L54 _private prototype_ `void BuildGeneratedCamera();`
- L55 _private prototype_ `void OnCameraRigAssetBuiltImpl();`
- L57 _private prototype_ `void ApplyChangedParameterOverrides();`
- L60 _private prototype_ `void OnCameraRigAssetBuilt(const UCameraRigAsset* InCameraRigAsset);`
- L67 _private member_ `TObjectPtr<UCameraAsset> GeneratedCameraAsset;` — `UPROPERTY(Transient)` — Generated camera asset to run our camera rig.
- L71 _private member_ `FInstancedPropertyBag CachedParameterOverrides;` — `UPROPERTY(Transient)` — Cached parameter overrides, for detecting when some of them change.
- L73 _private member_ `bool bIsBuildingGeneratedCameraAsset = false;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraSystemActor.h` (Public)


#### class `AGameplayCameraSystemActor`  
`class AGameplayCameraSystemActor : public AActor`  
_L21-48_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ClassGroup=Camera, HideCategories=(Input, Rendering))`
- inherits: `AActor`
- desc: An actor that hosts a camera system.
- L27 _public prototype_ `AGameplayCameraSystemActor(const FObjectInitializer& ObjectInit);`
- L33 _public function_ `UGameplayCameraSystemComponent* GetCameraSystemComponent() const` — `UFUNCTION(BlueprintGetter, Category=Camera)` — Gets the camera system component.
- L38 _public prototype_ `virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;` — AActor interface.
- L42 _private prototype_ `static AGameplayCameraSystemActor* GetAutoSpawnedCameraSystemActor(APlayerController* PlayerController, bool bSpawnIfMissing, bool* bOutSpawned);`
- L47 _private member_ `TObjectPtr<UGameplayCameraSystemComponent> CameraSystemComponent;` — `UPROPERTY(VisibleAnywhere, Category=Camera, BlueprintGetter="GetCameraSystemComponent", meta=(ExposeFunctionCategories="CameraSystem"))`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCameraSystemComponent.h` (Public)


#### class `UGameplayCameraSystemComponent`  
`class UGameplayCameraSystemComponent : public USceneComponent , public IGameplayCameraSystemHost`  
_L26-112_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ClassGroup=Camera, HideCategories=(Mobility, Rendering, LOD))`
- inherits: `USceneComponent,IGameplayCameraSystemHost`
- desc: A component that hosts a camera system.
- L34 _public typedef_ `using FCameraSystemEvaluator = UE::Cameras::FCameraSystemEvaluator;`
- L36 _public prototype_ `UGameplayCameraSystemComponent(const FObjectInitializer& ObjectInit);`
- L39 _public prototype_ `void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView);` — Updates the camera system and returns the computed view.
- L43 _public prototype_ `void ActivateCameraSystemForPlayerIndex(int32 PlayerIndex);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets this component's actor as the view target for the given player.
- L47 _public prototype_ `void ActivateCameraSystemForPlayerController(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Sets this component's actor as the view target for the given player.
- L51 _public prototype_ `bool IsCameraSystemActiveForPlayController(APlayerController* PlayerController) const;` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Returns whether this component's actor is set as the view target for the given player.
- L55 _public prototype_ `void DeactivateCameraSystem(AActor* NextViewTarget = nullptr);` — `UFUNCTION(BlueprintCallable, Category=Camera)` — Removes this component's actor from being the view target.
- L60 _public prototype_ `FCameraRigInstanceID StartGlobalCameraModifierRig(const UCameraRigAsset* CameraRig, int32 OrderKey = 0);` — `UFUNCTION(BlueprintCallable, Category=Camera)`
- L63 _public prototype_ `FCameraRigInstanceID StartVisualCameraModifierRig(const UCameraRigAsset* CameraRig, int32 OrderKey = 0);` — `UFUNCTION(BlueprintCallable, Category=Camera)`
- L66 _public prototype_ `void StopCameraModifierRig(FCameraRigInstanceID InstanceID, bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category=Camera)`
- L71 _public prototype_ `virtual void OnRegister() override;` — UActorComponent interface.
- L72 _public prototype_ `virtual void BeginPlay() override;`
- L73 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L76 _public function_ `virtual UObject* GetAsObject()` — IGameplayCameraSystemHost interface.
- L81 _private prototype_ `void CreateCameraSystemSpriteComponent();`
- L91 _public member_ `TEnumAsByte<EAutoReceiveInput::Type> AutoActivateForPlayer;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Activation, meta=(EditCondition="bAutoActivate"))` — If AutoActivate is set, auto-activates the camera system for the given player. This sets this actor as the view target, and is equivalent to calling ActivateCameraSystem on BeginPlay.
- L98 _public member_ `bool bSetPlayerControllerRotation = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Camera)` — If enabled, sets the evaluated camera orientation as the player controller rotation every frame. This is set on the player controller that this component was activated for.
- L103 _private member_ `TWeakObjectPtr<APlayerController> WeakPlayerController;` — `UPROPERTY(Transient)`
- L109 _private member_ `float EditorSpriteTextureScale = 0.5f;` — `UPROPERTY(transient)` — Sprite scaling for the editor.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayCamerasPlayerCameraManager.h` (Public)


#### enum `EGameplayCameraComponentActivationMode`  
`enum class EGameplayCameraComponentActivationMode : uint8`  
_L30-36_
- reflection: `UENUM()`
- desc: Defines how to activate a gameplay camera component.
- L33 _public enumerator_ `Push` — Push the camera director over any existing ones.
- L35 _public enumerator_ `InsertOrPush` — Inserts the camera director as a child of the active one, or push it if there is no active one.

#### enum `EGameplayCamerasViewRotationMode`  
`enum class EGameplayCamerasViewRotationMode`  
_L42-57_
- reflection: `UENUM()`
- desc: Defines how the GameplayCamerasPlayerCameraManager should handle the player's view rotation.
- L49 _public enumerator_ `None` — Don't do anything with the view rotation. This is suitable if the player camera input and control rotation are handled by custom logic, and the Gameplay Cameras only use the resulting control rotation (i.e. none of the camera rigs use player input nodes).
- L56 _public enumerator_ `PreviewUpdate` — Runs a "light" update of the whole camera system and comes up with a good approximation of the resulting camera orientation. Computationally more expensive than just computing a yaw and pitch angle, but handles blending camera rigs with different orientations while preserving aim.

#### class `AGameplayCamerasPlayerCameraManager`  
`class AGameplayCamerasPlayerCameraManager : public APlayerCameraManager , public IGameplayCameraSystemHost`  
_L77-208_
- reflection: `UCLASS(notplaceable, MinimalAPI)`
- inherits: `APlayerCameraManager,IGameplayCameraSystemHost`
- desc: A player camera manager that runs the GameplayCameras camera system. Setting the view target does the following: - Push a new evaluation context for the provided view target actor. - If that actor contains a GameplayCameraComponent, use its evaluation context directly. - If that actor contains a CameraComponent, make an evaluation context that wraps it and runs by simply copying that camera's properties (see FCameraActorCameraEvaluationContext). - For other actors, do as above, but convert the output of the actor's CalcCamera function. - The old view target's evaluation context is immediately removed from the evaluation stack. For other way to handle evaluation contexts, call methods directly on the camera system evaluator instead of going through the base APlayerCameraManager class. There is only ever one active view target, the "pending" view target isn't used. This is because we may be blending between more than two camera rigs that may belong to more than two actors.
- L85 _public prototype_ `AGameplayCamerasPlayerCameraManager(const FObjectInitializer& ObjectInitializer);`
- L91 _public prototype_ `void StealPlayerController(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Replace the camera manager currently set on the provided controller with this camera manager.
- L95 _public prototype_ `void ReleasePlayerController();` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Restore an originally stolen camera manager (see StealPlayerController).
- L101 _public prototype_ `void ActivateGameplayCamera(UGameplayCameraComponentBase* GameplayCamera, EGameplayCameraComponentActivationMode ActivationMode = EGameplayCameraComponentActivationMode::Push);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Activates the given component inside the manager's camera system.
- L105 _public prototype_ `void DeactivateGameplayCamera(UGameplayCameraComponentBase* GameplayCamera, bool bDeactivateAllCameraRigs = false);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Deactivates a previously activated component.
- L111 _public prototype_ `FCameraRigInstanceID ActivatePersistentBaseCameraRig(UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Activates the given camera rig prefab in the base layer.
- L115 _public prototype_ `FCameraRigInstanceID ActivatePersistentGlobalCameraRig(UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Activates the given camera rig prefab in the global layer.
- L119 _public prototype_ `FCameraRigInstanceID ActivatePersistentVisualCameraRig(UCameraRigAsset* CameraRig);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Activates the given camera rig prefab in the visual layer.
- L123 _public prototype_ `void DeactivateCameraRig(FCameraRigInstanceID InstanceID, bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Deactivates a previously activated base, global, or visual camera rig.
- L129 _public prototype_ `FCameraRigInstanceID StartGlobalCameraModifierRig(const UCameraRigAsset* CameraRig, int32 OrderKey = 0);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Starts a camera modifier rig on the global layer.
- L133 _public prototype_ `FCameraRigInstanceID StartVisualCameraModifierRig(const UCameraRigAsset* CameraRig, int32 OrderKey = 0);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Starts a camera modifier rig on the visual layer.
- L137 _public prototype_ `void StopCameraModifierRig(FCameraRigInstanceID InstanceID, bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Stops a camera modifier rig on previously started on the global or visual layer.
- L143 _public prototype_ `FCameraShakeInstanceID StartCameraShakeAsset( const UCameraShakeAsset* CameraShake, float ShakeScale = 1.f, ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal, FRotator UserPlaySpaceRotation = FRotator::ZeroRotator);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Starts a new camera shake.
- L151 _public prototype_ `bool IsCameraShakeAssetPlaying(FCameraShakeInstanceID InInstanceID) const;` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Checks if a camera shake is running.
- L155 _public prototype_ `bool StopCameraShakeAsset(FCameraShakeInstanceID InInstanceID, bool bImmediately = false);` — `UFUNCTION(BlueprintCallable, Category="Camera")` — Stops a running camera shake.
- L160 _public prototype_ `virtual void InitializeFor(APlayerController* PlayerController) override;` — APlayerCameraManager interface.
- L161 _public prototype_ `virtual void SetViewTarget(AActor* NewViewTarget, FViewTargetTransitionParams TransitionParams = FViewTargetTransitionParams()) override;`
- L162 _public prototype_ `virtual void ProcessViewRotation(float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot) override;`
- L165 _public prototype_ `virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;` — AActor interface.
- L168 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface.
- L169 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L172 _public function_ `virtual UObject* GetAsObject() override` — IGameplayCameraSystemHost interface.
- L177 _protected prototype_ `virtual void DoUpdateCamera(float DeltaTime) override;` — APlayerCameraManager interface.
- L181 _private prototype_ `void RunViewRotationPreviewUpdate(float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot);`
- L183 _private prototype_ `void EnsureNullContext();`
- L185 _private prototype_ `void OnContextStackChanged();`
- L186 _private prototype_ `void CleanUpViewTargetContexts();`
- L192 _public member_ `EGameplayCamerasViewRotationMode ViewRotationMode = EGameplayCamerasViewRotationMode::None;` — `UPROPERTY(EditAnywhere, Category="Camera", meta=(EditCondition="bOverrideViewRotationMode"))` — The view rotation handling mode to use.
- L196 _public member_ `bool bOverrideViewRotationMode = false;` — `UPROPERTY(EditAnywhere, Category="Camera")` — Whether the default view rotation mode setting should be overriden.
- L201 _private member_ `TObjectPtr<APlayerCameraManager> OriginalCameraManager;` — `UPROPERTY(Transient)`
- L203 _private member_ `TArray<TSharedRef<UE::Cameras::FCameraEvaluationContext>> ViewTargetContexts;`
- L205 _private member_ `TSharedPtr<UE::Cameras::FCameraEvaluationContext> NullContext;`
- L207 _private member_ `bool bIsSettingNewViewTarget = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/GameplayControlRotationComponent.h` (Public)


#### class `UGameplayControlRotationComponent`  
`class UGameplayControlRotationComponent : public UActorComponent`  
_L26-102_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ClassGroup=Camera, HideCategories=(Mobility, Rendering, LOD), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: An example component that works with the GameplayCameraComponent to manage a player's control rotation when the camera changes or moves in a way that was not initiated by the player themselves.
- L33 _public prototype_ `UGameplayControlRotationComponent(const FObjectInitializer& ObjectInit);` — Create a new control rotation component.
- L40 _public prototype_ `void ActivateControlRotationManagementForPlayerIndex(int32 PlayerIndex);` — `UFUNCTION(BlueprintCallable, Category="Control Rotation")` — Activates management of a player controller's control rotation. The component will set the control rotation every frame based on the latest camera system update.
- L47 _public prototype_ `void ActivateControlRotationManagementForPlayerController(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category="Control Rotation")` — Activates management of a player controller's control rotation. The component will set the control rotation every frame based on the latest camera system update.
- L53 _public prototype_ `void DeactivateControlRotationManagement();` — `UFUNCTION(BlueprintCallable, Category="Control Rotation")` — Deactivates management of a player controller's control rotation.
- L58 _public prototype_ `virtual void BeginPlay() override;` — UActorComponent interface
- L59 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L60 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L66 _public member_ `TArray<TObjectPtr<UInputAction>> AxisActions;` — `UPROPERTY(EditAnywhere, Category="Input")` — The axis input action(s) to read from.
- L73 _public member_ `float AxisActionAngularSpeedThreshold = 20.f;` — `UPROPERTY(EditAnywhere, Category="Input")` — The angular speed, in degrees per second, past which a change in the player input will thaw a frozen control rotation.
- L79 _public member_ `float AxisActionMagnitudeThreshold = 0.1f;` — `UPROPERTY(EditAnywhere, Category="Input")` — The player input magnitude under which the frozen control rotation is thawed.
- L86 _public member_ `TEnumAsByte<EAutoReceiveInput::Type> AutoActivateForPlayer;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Activation", meta=(EditCondition="bAutoActivate"))` — If AutoActivate is set, auto-activates control rotation management for the given player. This is equivalent to calling ActivateControlRotationManagement on BeginPlay.
- L90 _private prototype_ `void InitializeControlRotationService(APlayerController* PlayerController);`
- L91 _private prototype_ `void TeardownControlRotationService(bool bAllowUninitialized);`
- L96 _private member_ `TObjectPtr<APlayerController> PlayerController;` — `UPROPERTY()`
- L99 _private member_ `TScriptInterface<IGameplayCameraSystemHost> CameraSystemHost;` — `UPROPERTY()`
- L101 _private member_ `TSharedPtr<UE::Cameras::FPlayerControlRotationEvaluationService> ControlRotationService;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameFramework/IGameplayCameraSystemHost.h` (Public)


#### class `UGameplayCameraSystemHost`  
`class UGameplayCameraSystemHost : public UInterface`  
_L34-37_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: An interface for objects that host a camera system evaluator.

#### class `IGameplayCameraSystemHost`  
`class IGameplayCameraSystemHost`  
_L42-152_
- desc: An interface for objects that host a camera system evaluator.
- L48 _public typedef_ `using FCameraSystemEvaluator = UE::Cameras::FCameraSystemEvaluator;`
- L49 _public typedef_ `using FCameraEvaluationContext = UE::Cameras::FCameraEvaluationContext;`
- L52 _public prototype_ `TSharedPtr<FCameraSystemEvaluator> GetCameraSystemEvaluator();` — Gets the camera system evaluator.
- L55 _public function_ `bool HasCameraSystem() const` — Returns whether a camera system evaluation has been created in this host.
- L58 _public function_ `virtual UObject* GetAsObject()` — Should be implemented by the underlying class to return itself as a UObject.
- L61 _public prototype_ `TScriptInterface<IGameplayCameraSystemHost> GetAsScriptInterface();` — Returns this object as a script interface.
- L66 _public prototype_ `static IGameplayCameraSystemHost* FindActiveHost(APlayerController* PlayerController);` — Finds a valid host on the player controller's camera manager, or its view target.
- L71 _protected prototype_ `void InitializeCameraSystem();` — Creates a new camera system. Asserts if there is already one.
- L73 _protected prototype_ `void InitializeCameraSystem(const UE::Cameras::FCameraSystemEvaluatorCreateParams& Params);` — Creates a new camera system. Asserts if there is already one.
- L75 _protected prototype_ `void EnsureCameraSystemInitialized();` — Ensures that the camera system is created.
- L77 _protected prototype_ `void DestroyCameraSystem();` — Destroys the camera system.
- L80 _protected prototype_ `void OnAddReferencedObjects(FReferenceCollector& Collector);` — Should be called by the underlying object for garbage collection.
- L83 _protected prototype_ `void UpdateCameraSystem(float DeltaTime);` — Updates the camera system, if it exists.
- L87 _protected prototype_ `void UpdateCameraSystemForEditorPreview(float DeltaTime);` — Updates the camera system, if it exists, for an editor world preview.
- L93 _protected prototype_ `FCameraRigInstanceID ActivateCameraRig( const UCameraRigAsset* CameraRig, TSharedPtr<FCameraEvaluationContext> EvaluationContext, ECameraRigLayer EvaluationLayer);` — Activates the given camera rig in the given layer. Should not be used with Main layer.
- L99 _protected prototype_ `void DeactivateCameraRig(FCameraRigInstanceID InInstanceID, bool bImmediately = false);` — Deactivates a previously activated camera rig.
- L102 _protected prototype_ `FCameraRigInstanceID StartCameraModifierRig( const UCameraRigAsset* CameraRig, TSharedPtr<FCameraEvaluationContext> EvaluationContext, ECameraRigLayer EvaluationLayer, int32 OrderKey = 0);` — Starts a camera modifier rig on the given layer.
- L109 _protected prototype_ `void StopCameraModifierRig(FCameraRigInstanceID InstanceID, bool bImmediately = false);` — Stops a camera modifier rig on previously started on the global or visual layer.
- L112 _protected prototype_ `FCameraShakeInstanceID StartCameraShake( const UCameraShakeAsset* CameraShake, float ShakeScale = 1.f, ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal, FRotator UserPlaySpaceRotation = FRotator::ZeroRotator);` — Starts a new camera shake.
- L119 _protected prototype_ `bool IsCameraShakePlaying(FCameraShakeInstanceID InInstanceID) const;` — Checks if a camera shake is running.
- L122 _protected prototype_ `bool StopCameraShake(FCameraShakeInstanceID InInstanceID, bool bImmediately = false);` — Stops a running camera shake.
- L125 _protected prototype_ `FCameraActionInstanceID StartAction(const UCameraAction* CameraAction);` — Starts a new camera action.
- L128 _protected prototype_ `bool IsActionRunning(const FCameraActionInstanceID InInstanceID) const;` — Returns whether a given camera action instance is running.
- L131 _protected prototype_ `bool StopAction(const FCameraActionInstanceID InInstanceID);` — Stops a given camera action instance.
- L134 _protected prototype_ `bool StopAllActionsOfClass(TSubclassOf<UCameraAction> InActionClass);` — Stops all camera action instances of a given class.
- L139 _protected member_ `TSharedPtr<FCameraSystemEvaluator> CameraSystemEvaluator;` — The camera system evaluator.
- L144 _private prototype_ `void DebugDraw(UCanvas* Canvas, APlayerController* PlayerController);`
- L150 _private member_ `FDelegateHandle DebugDrawDelegateHandle;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameplayCameras.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_GAMEPLAY_CAMERAS_EVENT_HANDLERS WITH_EDITOR`
- L16 _macro_ `#define UE_GAMEPLAY_CAMERAS_DEBUG 1`
- L18 _macro_ `#define UE_GAMEPLAY_CAMERAS_DEBUG 0`
- L23 _macro_ `#define UE_GAMEPLAY_CAMERAS_TRACE 1`
- L25 _macro_ `#define UE_GAMEPLAY_CAMERAS_TRACE 0`
- L28 _delegate_ `DECLARE_STATS_GROUP(TEXT("Camera System Evaluation"), STATGROUP_CameraSystem, STATCAT_Advanced) DECLARE_LOG_CATEGORY_EXTERN(LogCameraSystem, Log, All);`
- L30 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraSystem, Log, All);`
- L30 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraSystem, Log, All);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameplayCamerasCustomVersion.h` (Public)


#### enum `FGameplayCamerasCustomVersion::Type`  
`enum Type`  
_L9-16_
- L11 _public enumerator_ `BeforeCustomVersionWasAdded = 0`
- L12 _public enumerator_ `AddLensNodeParameterFlags = 1`
- L14 _public enumerator_ `VersionPlusOne`
- L15 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace FGameplayCamerasCustomVersion`
- L18 _variable_ `const FGuid GUID(0x8BCB8CA9, 0x642B497C, 0xAB759854, 0x44875CE1);` (scope `FGameplayCamerasCustomVersion`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameplayCamerasDelegates.h` (Public)


#### class `UE::Cameras::FGameplayCamerasDelegates`  
`class FGameplayCamerasDelegates`  
_L28-62_
- desc: Global delegates for the GameplayCameras module.
- L33 _public function_ `static inline FOnCameraAssetBuilt& OnCameraAssetBuilt()` — Broadcast when a camera asset has been built.
- L39 _public function_ `static inline FOnCameraRigAssetBuilt& OnCameraRigAssetBuilt()` — Broadcast when a camera rig has been built.
- L45 _public function_ `static inline FOnCameraShakeAssetBuilt& OnCameraShakeAssetBuilt()` — Broadcast when a camera shake has been built.
- L51 _public function_ `static inline FOnCameraNodeChanged& OnCustomCameraNodeParametersChanged()` — Broadcast when a custom camera parameter provider node changes it parameters.
- L58 _private member_ `static FOnCameraAssetBuilt OnCameraAssetBuiltDelegate;`
- L59 _private member_ `static FOnCameraRigAssetBuilt OnCameraRigAssetBuiltDelegate;`
- L60 _private member_ `static FOnCameraShakeAssetBuilt OnCameraShakeAssetBuiltDelegate;`
- L61 _private member_ `static FOnCameraNodeChanged OnCustomCameraNodeParametersChangedDelegate;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraAssetBuilt, const UCameraAsset*);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraAssetBuilt, const UCameraAsset*);` (scope `UE::Cameras`)
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraRigAssetBuilt, const UCameraRigAsset*);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraRigAssetBuilt, const UCameraRigAsset*);` (scope `UE::Cameras`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraShakeAssetBuilt, const UCameraShakeAsset*);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraShakeAssetBuilt, const UCameraShakeAsset*);` (scope `UE::Cameras`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraNodeChanged, const UCameraNode*);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraNodeChanged, const UCameraNode*);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameplayCamerasSettings.h` (Public)


#### class `UGameplayCamerasSettings`  
`class UGameplayCamerasSettings : public UDeveloperSettings`  
_L17-72_
- reflection: `UCLASS(Config=GameplayCameras, DefaultConfig, MinimalAPI, meta=(DisplayName="Gameplay Cameras"))`
- inherits: `UDeveloperSettings`
- desc: The settings for the Gameplay Cameras runtime.
- L23 _public prototype_ `UGameplayCamerasSettings(const FObjectInitializer& ObjectInitializer);`
- L32 _public member_ `bool bAutoBuildInPIE = true;` — `UPROPERTY(EditAnywhere, Config, Category="General")` — Build camera assets before using them in PIE, so that they automatically run with the latest user edits.
- L39 _public member_ `EGameplayCamerasViewRotationMode DefaultViewRotationMode = EGameplayCamerasViewRotationMode::None;` — `UPROPERTY(EditAnywhere, Config, Category="General")` — The default view rotation handling mode to use when the game's player controller uses a GameplayCamerasPlayerCameraManager instance as its camera manager.
- L45 _public member_ `int32 CombinedCameraRigNumThreshold = 10;` — `UPROPERTY(EditAnywhere, Config, Category="General")` — The number of camera rigs combined in one frame past which the camera system emits a warning.
- L53 _public member_ `int32 MaxUsageSearchDistance = 2;` — `UPROPERTY(EditAnywhere, Config, Category="Camera Director", meta=(ClampMin=1, ClampMax=5))` — How many packages away to look for references to camera rigs and rig proxies from a camera director.
- L59 _public member_ `double DefaultIKAimingAngleTolerance = 0.1;` — `UPROPERTY(EditAnywhere, Config, Category="IK Aiming")` — The default angle tolerance to accept an aiming operation.
- L63 _public member_ `double DefaultIKAimingDistanceTolerance = 1.0;` — `UPROPERTY(EditAnywhere, Config, Category="IK Aiming")` — The default distance tolerance to accept an aiming operation.
- L67 _public member_ `uint8 DefaultIKAimingMaxIterations = 3;` — `UPROPERTY(EditAnywhere, Config, Category="IK Aiming")` — The default number of iterations for an aiming operation.
- L71 _public member_ `double DefaultIKAimingMinDistance = 100.0;` — `UPROPERTY(EditAnywhere, Config, Category="IK Aiming")` — The distance below which any IK aiming operation is disabled.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Helpers/ObjectReferenceFinder.h` (Public)


#### class `UE::Cameras::FObjectReferenceFinder`  
`class FObjectReferenceFinder : public FArchiveUObject`  
_L19-55_
- inherits: `FArchiveUObject`
- desc: A utility class for finding references from a given package to a set of UObjects.
- L24 _public prototype_ `FObjectReferenceFinder(UObject* InRootObject, TArrayView<UObject*> InReferencedObjects);` — Creates a new instance of the reference finder.
- L27 _public prototype_ `void CollectReferences();` — Runs the reference finding.
- L30 _public prototype_ `bool HasAnyObjectReference() const;` — Whether any object was found in the package that references any of the target objects.
- L33 _public prototype_ `int32 GetObjectReferenceCount(UObject* InObject) const;` — Returns the number of found references to the given target object.
- L38 _protected prototype_ `virtual FArchive& operator<<(UObject*& ObjRef) override;` — FArchive interface.
- L42 _private prototype_ `void Initialize(UObject* InRootObject);`
- L46 _private member_ `UObject* RootObject;`
- L47 _private member_ `UPackage* PackageScope;`
- L49 _private member_ `TSet<UObject*> TargetObjects;`
- L51 _private member_ `TArray<UObject*> ObjectsToVisit;`
- L52 _private member_ `TSet<UObject*> VisitedObjects;`
- L54 _private member_ `TMap<UObject*, int32> ObjectReferenceCounts;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Helpers/OutgoingReferenceFinder.h` (Public)


#### class `UE::Cameras::FOutgoingReferenceFinder`  
`class FOutgoingReferenceFinder : public FArchiveUObject`  
_L21-101_
- inherits: `FArchiveUObject`
- desc: A utility class for finding outgoing references from a given package to external UObjects of a given class.
- L32 _public member_ `int32 MaxDistance = 1;` — The maximum distance (in number of packages) to search for references. Zero means only search the root object package. One means search directly referenced packages. Higher distances exponentially grow the number of objects to search, so the maximum value settable is 5.
- L37 _public member_ `uint32 ExcludePackageFlags = 0;` — EPackageFlags that determine what packages to skip.
- L42 _public member_ `TArray<UClass*> ExcludeClasses;` — Classes to not inspect for outgoing references.
- L47 _public prototype_ `FOutgoingReferenceFinder(UObject* InRootObject, UClass* InReferencedObjectClass);` — Creates a new instance of the reference finder.
- L50 _public prototype_ `FOutgoingReferenceFinder(UObject* InRootObject, TArrayView<UClass*> InReferencedObjectClasses);` — Creates a new instance of the reference finder.
- L53 _public prototype_ `void CollectReferences();` — Runs the reference finding.
- L57 _public prototype_ `template<typename ObjectClass> bool GetReferencesOfClass(TArray<ObjectClass*>& OutReferencedObjects) const;` — Gets the references of a given class.
- L60 _public prototype_ `bool GetAllReferences(TArray<UObject*>& OutReferencedObjects) const;` — Gets all referenced objects.
- L65 _protected prototype_ `virtual FArchive& operator<<(UObject*& ObjRef) override;` — FArchive interface.
- L69 _private prototype_ `void Initialize(UObject* InRootObject);`
- L71 _private prototype_ `bool MatchesAnyTargetClass(UClass* InObjClass) const;`
- L72 _private prototype_ `bool IsIgnoredClass(UClass* InObjClass) const;`
- L90 _private member_ `UObject* RootObject;`
- L91 _private member_ `UPackage* PackageScope;`
- L92 _private member_ `int32 ValidMaxDistance = 1;`
- L94 _private member_ `TSet<UClass*> TargetObjectClasses;`
- L96 _private member_ `TArray<FObjectToVisit> ObjectsToVisit;`
- L97 _private member_ `TSet<UObject*> VisitedObjects;`
- L98 _private member_ `FSerializeState SerializeState;`
- L100 _private member_ `TMap<UClass*, TSet<UObject*>> ReferencedObjects;`
- L104 _function_ `template<typename ObjectClass> bool FOutgoingReferenceFinder::GetReferencesOfClass(TArray<ObjectClass*>& OutReferencedObjects) const`

#### struct `UE::Cameras::FOutgoingReferenceFinder::FObjectToVisit`  
`struct FObjectToVisit`  
_L76-81_
- L78 _public member_ `UObject* Obj = nullptr;`
- L79 _public member_ `UPackage* Package = nullptr;`
- L80 _public member_ `int32 Distance = 0;`

#### struct `UE::Cameras::FOutgoingReferenceFinder::FSerializeState`  
`struct FSerializeState`  
_L83-88_
- L85 _public member_ `UObject* CurrentObject = nullptr;`
- L86 _public member_ `UPackage* CurrentPackage = nullptr;`
- L87 _public member_ `int32 CurrentDistance = 0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/IGameplayCamerasLiveEditListener.h` (Public)


#### struct `UE::Cameras::FGameplayCameraAssetBuildEvent`  
`struct FGameplayCameraAssetBuildEvent`  
_L18-21_
- L20 _public member_ `const UPackage* AssetPackage = nullptr;`

#### class `UE::Cameras::IGameplayCamerasLiveEditListener`  
`class IGameplayCamerasLiveEditListener`  
_L26-43_
- desc: Interface for an object that can handle an asset being hot-reloaded at runtime.
- L30 _public prototype_ `virtual ~IGameplayCamerasLiveEditListener() = default;`
- L33 _public function_ `void PostBuildAsset(const FGameplayCameraAssetBuildEvent& BuildEvent)` — Called when a camera asset has been (re)built.
- L35 _public function_ `void PostEditChangeProperty(const UCameraNode* InCameraNode, const FPropertyChangedEvent& PropertyChangedEvent)` — Called when a camera node's property has been changed.
- L40 _protected function_ `virtual void OnPostBuildAsset(const FGameplayCameraAssetBuildEvent& BuildEvent)` — Called when a camera asset has been (re)built.
- L42 _protected function_ `virtual void OnPostEditChangeProperty(const UCameraNode* InCameraNode, const FPropertyChangedEvent& PropertyChangedEvent)` — Called when a camera node's property has been changed.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/IGameplayCamerasLiveEditManager.h` (Public)


#### class `UE::Cameras::IGameplayCamerasLiveEditManager`  
`class IGameplayCamerasLiveEditManager : public TSharedFromThis<IGameplayCamerasLiveEditManager>`  
_L23-50_
- inherits: `TSharedFromThis<IGameplayCamerasLiveEditManager>`
- desc: Interface for an object that can centralize the live-editing features of the camera system.
- L27 _public prototype_ `virtual ~IGameplayCamerasLiveEditManager() = default;`
- L30 _public prototype_ `virtual bool CanRunInEditor() const = 0;` — Whether cameras should be run in editor.
- L33 _public prototype_ `virtual void NotifyPostBuildAsset(const UPackage* InAssetPackage) const = 0;` — Notify all listeners to reload cameras related to the given package.
- L36 _public prototype_ `virtual void AddListener(const UPackage* InAssetPackage, IGameplayCamerasLiveEditListener* Listener) = 0;` — Add a listener for the given package.
- L38 _public prototype_ `virtual void RemoveListener(const UPackage* InAssetPackage, IGameplayCamerasLiveEditListener* Listener) = 0;` — Remove a listener for the given package.
- L41 _public prototype_ `virtual void NotifyPostEditChangeProperty(const UCameraNode* InCameraNode, const FPropertyChangedEvent& PropertyChangedEvent) const = 0;` — Notify all listeners that a property was changed on the given camera node.
- L44 _public prototype_ `virtual void AddListener(const UCameraNode* InCameraNode, IGameplayCamerasLiveEditListener* Listener) = 0;` — Add a listener for the given node.
- L46 _public prototype_ `virtual void RemoveListener(const UCameraNode* InCameraNode, IGameplayCamerasLiveEditListener* Listener) = 0;` — Remove a listener for the given node.
- L49 _public prototype_ `virtual void RemoveListener(IGameplayCamerasLiveEditListener* Listener) = 0;` — Remove the given listener from all notifications.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/IGameplayCamerasModule.h` (Public)


#### class `IGameplayCamerasModule`  
`class IGameplayCamerasModule : public IModuleInterface`  
_L19-50_
- inherits: `IModuleInterface`
- L28 _public prototype_ `static IGameplayCamerasModule& Get();` — Singleton-like access to ICameraModule @return The ICameraModule instance, loading the module on demand if needed
- L31 _public prototype_ `virtual void RegisterBlendableStruct(const UScriptStruct* StructType, UE::Cameras::FBlendableStructTypeErasedInterpolator Interpolator) = 0;` — Register a new blendable structure.
- L33 _public prototype_ `virtual TConstArrayView<UE::Cameras::FBlendableStructInfo> GetBlendableStructs() const = 0;` — Gets the currently registered blendable structures.
- L35 _public prototype_ `virtual void UnregisterBlendableStruct(const UScriptStruct* StructType) = 0;` — Unregisters a blendable structure.
- L38 _public typedef_ `using IGameplayCamerasLiveEditManager = UE::Cameras::IGameplayCamerasLiveEditManager;`
- L43 _public prototype_ `virtual TSharedPtr<IGameplayCamerasLiveEditManager> GetLiveEditManager() const = 0;` — Gets the live edit manager.
- L48 _public prototype_ `virtual void SetLiveEditManager(TSharedPtr<IGameplayCamerasLiveEditManager> InLiveEditManager) = 0;` — Sets the live edit manager.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/CameraAimingMath.h` (Public)


#### enum `UE::Cameras::ECameraAimingResult`  
`enum class ECameraAimingResult`  
_L17-25_
- desc: Result for an aiming operation.
- L20 _public enumerator_ `Success` — The aiming was successful.
- L22 _public enumerator_ `NoSolution` — The aiming did not have a valid solution.
- L24 _public enumerator_ `NoSolver` — The aiming was not possible for the given camera rig.

#### class `UE::Cameras::FCameraAimingMath`  
`class FCameraAimingMath`  
_L30-66_
- desc: A utility class for math operations pertaining to aiming a camera at something.
- L35 _public prototype_ `static ECameraAimingResult ComputeCorrection(const FCameraNodeEvaluationResult& Result, const FVector3d& DesiredTarget, FRotator3d& OutCorrection);` — Computes the rotation correction needed for the given camera to be aimed at the given target.
- L38 _public prototype_ `static const FCameraRigJoint* FindPivotJoint(const FCameraNodeEvaluationResult& Result);` — Finds the pivot joint in the given evaluation result.
- L40 _public prototype_ `static const FCameraRigJoint* FindPivotJoint(const FCameraRigJoints& CameraRigJoints);` — Finds the pivot joint in the given camera rig joints.
- L43 _public prototype_ `static bool ComputeTwoBonesCorrection(const FCameraPose& CurrentPose, const FVector3d& PivotLocation, const FVector3d& DesiredTarget, FRotator3d& OutCorrection);` — Computes the rotation correction needed for the given camera to be aimed at the given target.
- L49 _public prototype_ `static bool ComputeTwoBonesCorrection(const FCameraPose& CurrentPose, const FRotator3d& AimOffsetAngles, const FVector3d& PivotLocation, const FVector3d& DesiredTarget, FRotator3d& OutCorrection);` — As per the other ComputeTwoBonesCorrection function, but take into account an additional angular offset for the camera's line of sight. These angles should be expressed in the pivot's coordinate system.
- L50 _public prototype_ `static bool ComputeTwoBonesCorrection(const FCameraPose& CurrentPose, const FVector3d& CustomAim, const FVector3d& PivotLocation, const FVector3d& DesiredTarget, FRotator3d& OutCorrection);`
- L53 _public prototype_ `static double GetAngleBetween(const FVector3d& AimA, const FVector3d& AimB);` — Computes the difference between two aim vectors.
- L56 _public prototype_ `static FRotator3d GetRotationBetween(const FVector3d& AimA, const FVector3d& AimB);` — Computes the rotation between two aim vectors.
- L59 _public prototype_ `static FRotator3d GetNoRollRotationBetween(const FVector3d& AimA, const FVector3d& AimB);` — Computes the rotation between two aim vectors, using only yaw and pitch.
- L63 _private prototype_ `static bool RaySphereIntersectExit(const FRay3d& Ray, const FVector3d& SphereOrigin, double SphereRadius, double& OutRayIntersectDistance);`
- L64 _private prototype_ `static bool RaySphereIntersectExit(const FVector3d& RayStart, const FVector3d& RayDir, const FVector3d& SphereOrigin, double SphereRadius, double& OutRayIntersectDistance);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/CameraFramingZoneMath.h` (Public)


#### struct `UE::Cameras::FFramingZone`  
`struct FFramingZone`  
_L24-108_
- desc: Effective coordinates for a rectangular screen-space zone. Unlike FCameraFramingZone, whose values can mean anything (margins, offsets, etc) this struct is expected to store actual screen coordinates in 0..1 UI space.
- L26 _public member_ `double LeftBound = 0;`
- L27 _public member_ `double TopBound = 0;`
- L28 _public member_ `double RightBound = 0;`
- L29 _public member_ `double BottomBound = 0;`
- L32 _public prototype_ `FFramingZone();` — Builds an empty framing zone.
- L35 _public function_ `double Width() const` — Gets the width of the framing zone.
- L38 _public function_ `double Height() const` — Gets the height of the framing zone.
- L41 _public function_ `FVector2d Center() const` — Gets the center of the framing zone.
- L47 _public prototype_ `bool IsValid() const;` — Returns whether this framing zone is well-formed (bounds in 0..1 UI space, with left/top bounds lesser than or equal to right/bottom bounds).
- L50 _public prototype_ `void ClampBounds();` — Makes sure all the bounds have valid values between 0 and 1.
- L56 _public prototype_ `void ClampBounds(const FVector2d& MustContain);` — Makes sure all the bounds have valid values between 0 and 1, and that the enclosed rectangle contains the given target point.
- L62 _public prototype_ `void ClampBounds(const FVector2d& MustContain, double Margin);` — Makes sure all the bounds have valid values between 0 and 1, and that the enclosed rectangle contains the given target point, with a uniform margin.
- L68 _public prototype_ `void ClampBounds(const FFramingZone& MustContain);` — Makes sure all the bounds have valid values between 0 and 1, and that the enclosed rectangle contains the given inner rectangle.
- L73 _public prototype_ `void Add(const FFramingZone& Other);` — Expands this framing zone to include the other framing zone.
- L76 _public prototype_ `bool Contains(const FVector2d& Point) const;` — Checks whether the given point (in 0..1 UI space) is inside this zone.
- L82 _public prototype_ `FVector2d ComputeClosestIntersection(const FVector2d& Origin, const FVector2d& LineDir, bool bLineDirIsNormalized = false) const;` — Computes intersections between a line and the zone's box, and returns the one closest to the line's origin point.
- L85 _public prototype_ `FVector4d GetNormalizedBounds() const;` — Gets the inner margins of this zone compared to the screen's center.
- L88 _public prototype_ `FVector2d GetCanvasPosition(const FVector2d& CanvasSize) const;` — Gets the coordinates of the top-left corner of the zone, in 0..Width/Height canvas units.
- L90 _public prototype_ `FVector2d GetCanvasSize(const FVector2d& CanvasSize) const;` — Gets the size of the zone, in 0..Width/Height canvas units.
- L92 _public prototype_ `void Serialize(FArchive& Ar);`
- L97 _public prototype_ `static FFramingZone FromScreenMargins(const FCameraFramingZone& Margins);` — Build a framing zone from a set of margins relative to the screen edge.
- L100 _public prototype_ `static FFramingZone FromRelativeMargins(const FVector2d& ScreenLocation, const FCameraFramingZone& Margins);` — Build a framing zone from a set of margins relative to a screen location.
- L103 _public prototype_ `static FFramingZone FromPoints(TConstArrayView<FVector2d> ScreenPoints);` — Build a framing zone that encompasses all the given points (in 0..1 UI space).
- L107 _private prototype_ `static double GetNormalizedBound(double Bound);`

#### struct `UE::Cameras::FFramingZoneAngles`  
`struct FFramingZoneAngles`  
_L116-122_
- desc: The half-angles (in radians) of a rectangular screen framing zone, relative to the camera pose's aim direction.
- L118 _public member_ `double LeftHalfAngle = 0;`
- L119 _public member_ `double TopHalfAngle = 0;`
- L120 _public member_ `double RightHalfAngle = 0;`
- L121 _public member_ `double BottomHalfAngle = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L110 _prototype_ `FArchive& operator <<(FArchive& Ar, FFramingZone& FramingZone);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/CameraNodeSpaceMath.h` (Public)


#### struct `UE::Cameras::FCameraNodeSpaceParams`  
`struct FCameraNodeSpaceParams`  
_L20-36_
- desc: A structure that can wrap node evaluation parameters and results, and spit out information needed to compute positions and offsets in various evaluation coordinate systems.
- L23 _public prototype_ `FCameraNodeSpaceParams(const FCameraNodeEvaluationParams& InEvaluationParams, const FCameraNodeEvaluationResult& InEvaluationResult);` — Creates a new FCameraNodeSpaceParams.
- L26 _public prototype_ `TSharedPtr<const FCameraEvaluationContext> GetActiveContext() const;` — Gets the active context on the root node's main stack.
- L28 _public prototype_ `TSharedPtr<const FCameraEvaluationContext> GetOwningContext() const;` — Gets the context owning the caller camera node.
- L30 _public prototype_ `bool FindPivotTransform(FTransform3d& OutPivotTransform) const;` — Finds a pivot in the evaluation result.
- L34 _public member_ `const FCameraNodeEvaluationParams& EvaluationParams;`
- L35 _public member_ `const FCameraNodeEvaluationResult& EvaluationResult;`

#### class `UE::Cameras::FCameraNodeSpaceMath`  
`class FCameraNodeSpaceMath`  
_L38-62_
- L43 _public prototype_ `static bool GetCameraNodeOriginPosition(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& Result, ECameraNodeOriginPosition InOriginPosition, FVector3d& OutOrigin);` — Gets the location of the specified camera node origin.
- L46 _public prototype_ `static bool GetCameraNodeOriginPosition(const FCameraNodeSpaceParams& Params, ECameraNodeOriginPosition InOriginPosition, FVector3d& OutOrigin);` — Gets the location of the specified camera node origin.
- L49 _public prototype_ `static bool GetCameraNodeSpaceTransform(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& Result, ECameraNodeSpace InSpace, FTransform3d& OutTransform);` — Gets the transform of the specified camera node space.
- L52 _public prototype_ `static bool GetCameraNodeSpaceTransform(const FCameraNodeSpaceParams& Params, ECameraNodeSpace InSpace, FTransform3d& OutTransform);` — Gets the transform of the specified camera node space.
- L55 _public prototype_ `static bool OffsetCameraNodeSpacePosition(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& Result, const FVector3d& InPosition, const FVector3d& InOffset, ECameraNodeSpace InSpace, FVector3d& OutPosition);` — Offsets a given world position in the specified camera node space.
- L58 _public prototype_ `static bool OffsetCameraNodeSpacePosition(const FCameraNodeSpaceParams& Params, const FVector3d& InPosition, const FVector3d& InOffset, ECameraNodeSpace InSpace, FVector3d& OutPosition);` — Offsets a given world position in the specified camera node space.
- L61 _public prototype_ `static bool OffsetCameraNodeSpaceTransform(const FCameraNodeSpaceParams& Params, const FTransform3d& InTransform, const FVector3d& InLocationOffset, const FRotator3d& InRotationOffset, ECameraNodeSpace InSpace, FTransform3d& OutTransform);` — Offsets a given world transform in the specified camera node space.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/CameraPoseMath.h` (Public)


#### struct `UE::Cameras::FCameraFieldsOfView`  
`struct FCameraFieldsOfView`  
_L25-29_
- desc: Simple struct for holding horizontal and vertical fields of view.
- L27 _public member_ `double HorizontalFieldOfView;`
- L28 _public member_ `double VerticalFieldOfView;`

#### class `UE::Cameras::FCameraPoseMath`  
`class FCameraPoseMath`  
_L35-144_
- desc: A utility class for mathematical functions related to a camera pose.
- L40 _public prototype_ `static FCameraFieldsOfView GetEffectiveFieldsOfView(const FCameraPose& CameraPose);` — Gets both horizontal and vertical effective fields of view, using the sensor aspect ratio.
- L43 _public prototype_ `static FCameraFieldsOfView GetEffectiveFieldsOfView(const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext);` — Gets both horizontal and vertical effective fields of view, using the given player controller's viewport aspect ratio.
- L46 _public prototype_ `static FCameraFieldsOfView GetEffectiveFieldsOfView(const FCameraPose& CameraPose, double ActualAspectRatio, EAspectRatioAxisConstraint DefaultAspectRatioAxisConstraint);` — Gets both horizontal and vertical effective fields of view, using the given aspect ratio.
- L49 _public prototype_ `static double GetEffectiveAspectRatio(const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext);` — Gets the aspect ratio of the viewport associated with the given player controller.
- L52 _public prototype_ `static EAspectRatioAxisConstraint GetDefaultAspectRatioAxisConstraint(TSharedPtr<const FCameraEvaluationContext> EvaluationContext);` — Gets the default aspect ratio axis constraint associated with the given player controller.
- L57 _public prototype_ `static void BuildProjectionData( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, FSceneViewProjectionData& OutProjectionData);` — Builds the projection matrices of the given camera pose.
- L64 _public prototype_ `static void BuildProjectionData( const FCameraPose& CameraPose, const FIntPoint& ViewportSize, EAspectRatioAxisConstraint DefaultAspectRatioAxisConstraint, FSceneViewProjectionData& OutProjectionData);` — Builds the projection matrices of the given camera pose.
- L73 _public prototype_ `static FMatrix BuildProjectionMatrix( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext);` — Builds the projection matrix of the given camera pose. This matrix is suitable for projecting camera-space points onto screen-space.
- L81 _public prototype_ `static FMatrix BuildViewProjectionMatrix( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext);` — Builds the view-projection matrix of the given camera pose. This matrix combines the camera transform and the projection matrix, making it suitable for projecting world-space points onto screen-space.
- L88 _public prototype_ `static FMatrix BuildLocalViewProjectionMatrix( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext);` — Builds a view-projection matrix using an identity view, so that using for unprojecting yields camera-local positions.
- L93 _public prototype_ `static TOptional<FVector2d> ProjectWorldToScreen( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, const FVector3d& WorldLocation, bool bForceLocationInsideFrustum = false);` — Projects the given world point onto screen-space.
- L98 _public prototype_ `static TOptional<FVector2d> ProjectCameraToScreen( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, const FVector3d& CameraSpaceLocation, bool bForceLocationInsideFrustum = false);` — Projects the given camera-local point onto screen-space.
- L108 _public prototype_ `static TOptional<FVector2d> ProjectToScreen( const FMatrix& ViewProjectionMatrix, const FVector3d& Location, bool bForceLocationInsideFrustum = false);` — Projects the given point onto screen-space. The caller is responsible for making sure the view-projection matrix and coordinate system for the given point are compatible.
- L112 _public prototype_ `static FRay3d UnprojectScreenToCamera( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, const FVector2D& ScreenSpacePoint);` — Unproject a screen-space point into a camera-local ray.
- L117 _public prototype_ `static FVector3d UnprojectScreenToCamera( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, const FVector2D& ScreenSpacePoint, double PredictedDistance);` — Unproject a screen-space point into a camera-local point given an expected distance.
- L123 _public prototype_ `static FRay3d UnprojectScreenToWorld( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, const FVector2D& ScreenSpacePoint);` — Unproject a screen-space point into a world-space ray.
- L128 _public prototype_ `static FVector3d UnprojectScreenToWorld( const FCameraPose& CameraPose, TSharedPtr<const FCameraEvaluationContext> EvaluationContext, const FVector2D& ScreenSpacePoint, double PredictedDistance);` — Unproject a screen-space point into a world-space point given an expected distance.
- L135 _public prototype_ `static FRay3d UnprojectFromScreen( const FMatrix& InverseViewProjectionMatrix, const FVector2D& ScreenSpacePoint);` — Unprojects the given screen-space point into a ray.
- L138 _public prototype_ `static FVector3d UnprojectFromScreen( const FMatrix& InverseViewProjectionMatrix, const FVector2D& ScreenSpacePoint, double PredictedDistance);` — Unprojects the given screen-space point into a point given an expected distance.
- L143 _private prototype_ `static FMatrix InverseProjectionMatrix(const FMatrix& ProjectionMatrix);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)
- L30 _prototype_ `FArchive& operator<< (FArchive& Ar, FCameraFieldsOfView& FieldsOfView);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/ConsumableValue.h` (Public)


#### struct `UE::Cameras::TConsumableValue`  
`template<typename ValueType> struct TConsumableValue`  
_L16-178_
- desc: A value that can be "consumed" and applied to another value. The consumable value can be a "delta", which is added to another value, or an "absolute", which is set on another value.
- L21 _public function_ `static TConsumableValue<ValueType> Absolute(ValueType InValue)` — Returns an absolute consumable with the given value.
- L27 _public function_ `static TConsumableValue<ValueType> Delta(ValueType InValue)` — Returns a delta consumable with the given value.
- L33 _public function_ `TConsumableValue() : bHasValue(false)` — Creates a new consumable with no value.
- L38 _public function_ `TConsumableValue(ValueType InValue, bool bInIsDelta) : Value(InValue) , bHasValue(true) , bIsDelta(bInIsDelta)` — Creates a new consumable.
- L47 _public function_ `ValueType Get() const` — Gets the current value. Asserts if there is no value.
- L54 _public function_ `ValueType GetOrDefault(ValueType DefaultValue) const` — Gets the current value, or the default one if there's no value.
- L60 _public function_ `bool HasValue() const` — Returns whether there's any value left in the consumable.
- L66 _public function_ `bool IsDelta() const` — Returns whether the consumable is a delta.
- L84 _public function_ `ValueType Apply(const ValueType InTarget)` — Applies the consumable to the given value and returns the new value. This is meant to be used as follows: MyFooBar = Consumable.Apply(MyFooBar); After this, the consumable doesn't have any value left in it anymore, so HasValue() will return false and further calls to Apply() will just return the same value as the given parameter.
- L118 _public function_ `ValueType Apply(const ValueType InTarget, const ValueType InMinTarget, const ValueType InMaxTarget)` — Applies the consumable to the given value and returns the new value. However, check that the return value falls within the given min/max bounds. If not, only consume enough to reach those bounds and leave the rest to be consumed later. This is meant to be used as follows: MyFooBar = Consumable.Apply(MyFooBar, MyMin, MyMax); After this, the consumable may or may not have any value left in it, depending on whether the given min/max bounds were reached.
- L175 _private member_ `ValueType Value = ValueType();`
- L176 _private member_ `bool bHasValue = false;`
- L177 _private member_ `bool bIsDelta = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)
- L180 _typedef_ `using FConsumableFloat = TConsumableValue<float>;` (scope `UE::Cameras`)
- L181 _typedef_ `using FConsumableDouble = TConsumableValue<double>;` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/CriticalDamper.h` (Public)


#### struct `UE::Cameras::FCriticalDamper`  
`struct FCriticalDamper`  
_L36-115_
- desc: Implements a critically damped spring-mass system. See https://en.wikipedia.org/wiki/Damping Important notes: - A critically damped spring-mass system converges as fast as possible towards its state of equilibrium without overshooting and/or oscillating. That's the theory, though. In practice, probably because of floating point precision, the system can slightly overshoot, so we clamp the result when it's just about to "settle". See the `GameplayCameras.CriticalDamper.StabilizationThreshold` cvar for tweaking how that happens. - In this implementation, the state of equilibrium is 0 (zero). That is, the target that the system is trying to reach is 0. In most practical cases, however, we want to converge towards an arbitrary value, which can even move if the system is being "dragged around". The different overloads of the `Update` method are there for these different use-cases. Don't mix and match calls, though: it's recommended to stick to one of these overloads. - See the math notes in the corresponding cpp file for details about the algorithm and its implementation.
- L40 _public prototype_ `FCriticalDamper();`
- L41 _public prototype_ `FCriticalDamper(float InW0);`
- L47 _public prototype_ `void Reset(float InX0, float InX0Derivative);` — Resets the initial conditions (aka the previous frame's state) of the spring-mass system.
- L54 _public function_ `float GetW0() const` — Gets the damping factor. This is the undamped angular frequency of the oscillator system. It's technically expressed in seconds.
- L60 _public function_ `void SetW0(float InW0)` — Sets the damping factor. This is the undamped angular frequency of the oscillator system. It's technically expressed in seconds.
- L63 _public function_ `float GetX0() const` — Gets the last position of the spring-mass system.
- L65 _public function_ `float GetX0Derivative() const` — Gets the last velocity of the spring-mass system.
- L72 _public prototype_ `float Update(float DeltaTime);` — Updates the system to make it converge towards 0. @param DeltaTime  The elapsed time.
- L83 _public prototype_ `float Update(float X, float DeltaTime);` — Updates the system, given a possibly forced position the system was moved to. The forced position should be last frame's result (also available with GetX0()) if the target wasn't moved. The system will converge towards 0. @param X          The forced position of the system. @param DeltaTime  The elapsed time. @return           The new position of the system.
- L96 _public prototype_ `float Update(float PreviousDamped, float NextTarget, float DeltaTime);` — Updates the system for damping towards arbitrary non-zero values. This call takes last frame's target and this frame's target. The difference between the two indicates by how much the target was forcibly moved, if at all. The result (also available with GetX0()) is returned relative to the current frame's target (i.e. the second parameter). @param PreviousDamped  The previous value returned by this function. @param NextTarget      The new target for the system. @param DeltaTime       The elapsed time. @return			      The new damped value.
- L99 _public prototype_ `void Serialize(FArchive& Ar);` — Saves or loads the state of this critical damper.
- L103 _private prototype_ `void InternalUpdate(float ForcedMovement, float DeltaTime);`
- L108 _private member_ `float W0;` — Angular frequency of the oscillator.
- L110 _private member_ `float X0;` — Initial position of the spring-mass system, aka the previous frame's position.
- L112 _private member_ `float X0Derivative;` — Initial velocity of the spring-mass system, aka the previous frame's velocity.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)
- L117 _prototype_ `FArchive& operator <<(FArchive& Ar, FCriticalDamper& Damper);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/Interpolation.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Cameras` (scope `UE`)
- L13 _function_ `inline float SmoothStep(float Value)` (scope `UE::Cameras`) — Smoothstep interpolation @param Value  A value between 0 and 1
- L23 _function_ `inline float SmootherStep(float Value)` (scope `UE::Cameras`) — Smootherstep interpolation @param Value  A value between 0 and 1

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Math/PerlinNoise.h` (Public)


#### struct `FPerlinNoiseData`  
`struct FPerlinNoiseData`  
_L14-23_
- reflection: `USTRUCT()`
- L19 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`
- L22 _public member_ `float Frequency = 1.f;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`

#### struct `UE::Cameras::FPerlinNoise`  
`struct FPerlinNoise`  
_L42-103_
- desc: Implements a 1-dimensional perlin noise generator. Unlike the FMath::PerlinNoise1D method, this one doesn't use a hard-coded lookup table of pre-generated numbers. Since camera noise doesn't need to generate numbers for thousands or millions of pixels at a time (only a handful every frame), we can afford to get slightly better noise quality here. Other differences include: - Multi-octave noise. - The ability to dynamically change the frequency. - Input is a delta-time, instead of an absolute undefined value.
- L46 _public prototype_ `FPerlinNoise();`
- L47 _public prototype_ `FPerlinNoise(const FPerlinNoiseData& InData, uint8 InOctaves = 1);`
- L48 _public prototype_ `FPerlinNoise(float InAmplitude, float InFrequency, uint8 InOctaves = 1);`
- L50 _public function_ `float GetAmplitude() const`
- L51 _public function_ `void SetAmplitude(float InAmplitude)`
- L53 _public function_ `float GetFrequency() const`
- L54 _public prototype_ `void SetFrequency(float InFrequency);`
- L56 _public function_ `float GetLacunarity() const`
- L57 _public function_ `void SetLacunarity(float InLacunarity)`
- L59 _public function_ `float GetOctaveGain() const`
- L60 _public function_ `void SetOctaveGain(float InOctaveGain)`
- L62 _public function_ `uint8 GetNumOctaves() const`
- L63 _public prototype_ `void SetNumOctaves(uint8 InNumOctaves);`
- L65 _public prototype_ `float GenerateValue(float DeltaTime);`
- L67 _public prototype_ `void Serialize(FArchive& Ar);`
- L77 _private prototype_ `void Initialize(float InFrequency);`
- L79 _private prototype_ `static FVector2f ComputeTangent(float InPrev, float InNext, float Interval, float Tension);`
- L83 _private member_ `static const uint8 MAX_OCTAVES = 4;`
- L95 _private member_ `float Amplitude = 1.f;`
- L97 _private member_ `float Lacunarity = 2.f;`
- L98 _private member_ `float OctaveGain = 0.5f;`
- L100 _private member_ `uint8 NumOctaves = 1;`
- L102 _private member_ `FSinglePerlinNoise Octaves[MAX_OCTAVES];`

#### struct `UE::Cameras::FPerlinNoise::FSinglePerlinNoise`  
`struct FSinglePerlinNoise`  
_L85-93_
- L87 _public member_ `float Frequency = 1.f;`
- L88 _public member_ `float CurTime = 0.f;`
- L89 _public member_ `float SecondPrev = 0.f;`
- L90 _public member_ `float Prev = 0.f;`
- L91 _public member_ `float Next = 0.f;`
- L92 _public member_ `float SecondNext = 0.f;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Cameras` (scope `UE`)
- L69 _function_ `friend FArchive& operator<< (FArchive& Ar, FPerlinNoise& This)` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/MovieScene/MovieSceneCameraFramingZoneSection.h` (Public)


#### class `UMovieSceneCameraFramingZoneSection`  
`class UMovieSceneCameraFramingZoneSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L15-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L24 _public member_ `FMovieSceneDoubleChannel LeftMarginCurve;` — `UPROPERTY()`
- L27 _public member_ `FMovieSceneDoubleChannel TopMarginCurve;` — `UPROPERTY()`
- L30 _public member_ `FMovieSceneDoubleChannel RightMarginCurve;` — `UPROPERTY()`
- L33 _public member_ `FMovieSceneDoubleChannel BottomMarginCurve;` — `UPROPERTY()`
- L37 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L38 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/MovieScene/MovieSceneCameraFramingZoneTrack.h` (Public)


#### class `UMovieSceneCameraFramingZoneTrack`  
`class UMovieSceneCameraFramingZoneTrack : public UMovieScenePropertyTrack`  
_L10-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- L16 _public prototype_ `UMovieSceneCameraFramingZoneTrack(const FObjectInitializer& Init);`
- L19 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface.
- L20 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Attach/AttachToActorCameraNode.h` (Public)


#### class `UAttachToActorCameraNode`  
`class UAttachToActorCameraNode : public UCameraNode`  
_L16-42_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Attachment"))`
- inherits: `UCameraNode`
- desc: A camera node that moves the camera to an actor.
- L23 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L29 _public member_ `FCameraActorAttachmentInfo Attachment;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(CameraContextData=true))` — The actor to attach to.
- L33 _public member_ `FCameraContextDataID AttachmentDataID;` — `UPROPERTY()` — The data ID for the attachment info.
- L37 _public member_ `FBooleanCameraParameter AttachToLocation = true;` — `UPROPERTY(EditAnywhere, Category=Common)` — Whether to move the camera to the actor's location.
- L41 _public member_ `FBooleanCameraParameter AttachToRotation = false;` — `UPROPERTY(EditAnywhere, Category=Common)` — Whether to align the camera rotation to the actor's orientation.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Attach/AttachToActorGroupCameraNode.h` (Public)


#### class `UAttachToActorGroupCameraNode`  
`class UAttachToActorGroupCameraNode : public UCameraNode`  
_L15-32_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Attachment"))`
- inherits: `UCameraNode`
- desc: A camera node that moves the camera to the weighted center of a group of actors.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `TArray<FCameraActorAttachmentInfo> Attachments;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(CameraContextData=true))` — The actors to attach to.
- L31 _public member_ `FCameraContextDataID AttachmentsDataID;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Attach/AttachToPlayerPawnCameraNode.h` (Public)


#### class `UAttachToPlayerPawnCameraNode`  
`class UAttachToPlayerPawnCameraNode : public UCameraNode`  
_L14-40_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Attachment"))`
- inherits: `UCameraNode`
- desc: A camera node that moves the camera to the player pawn.
- L21 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L27 _public member_ `FBooleanCameraParameter AttachToLocation = true;` — `UPROPERTY(EditAnywhere, Category=Common)` — Whether to move the camera to the pawn's location.
- L31 _public member_ `FBooleanCameraParameter AttachToRotation = false;` — `UPROPERTY(EditAnywhere, Category=Common)` — Whether to align the camera rotation to the pawn's orientation.
- L35 _public member_ `FName SocketName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category=Common)` — An optional socket to attach to on the actor.
- L39 _public member_ `FName BoneName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category=Common)` — An optional bone to attach to on the actor.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Attach/CameraActorAttachmentInfo.h` (Public)


#### struct `FCameraActorAttachmentInfo`  
`struct FCameraActorAttachmentInfo`  
_L16-37_
- reflection: `USTRUCT(BlueprintType)`
- desc: Attachment information for a camera rig.
- L22 _public member_ `TObjectPtr<AActor> Actor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attachment")` — The actor to attach to.
- L26 _public member_ `FName SocketName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Attachment")` — An optional socket to attach to on the actor.
- L30 _public member_ `FName BoneName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Target")` — An optional bone to attach to on the actor.
- L34 _public member_ `float Weight = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Attachment")` — The weight of this attachment. Unused if only one attachment is used.
- L36 _public prototype_ `bool operator== (const FCameraActorAttachmentInfo& Other) const = default;`

#### struct `UE::Cameras::FCameraActorAttachmentInfoReader`  
`struct FCameraActorAttachmentInfoReader`  
_L43-70_
- desc: A special reader class for attachment information.
- L45 _public function_ `FCameraActorAttachmentInfoReader()`
- L46 _public prototype_ `FCameraActorAttachmentInfoReader(const FCameraActorAttachmentInfo& InAttachmentInfo, FCameraContextDataID InDataID);`
- L48 _public prototype_ `void Initialize(const FCameraActorAttachmentInfo& InAttachmentInfo, FCameraContextDataID InDataID);`
- L50 _public prototype_ `bool GetAttachmentTransform(const FCameraContextDataTable& ContextDataTable, FTransform3d& OutTransform);`
- L53 _public prototype_ `FString RenderAttachmentInfo() const;`
- L58 _private prototype_ `void CacheAttachmentInfo(const FCameraActorAttachmentInfo& InAttachmentInfo);`
- L62 _private member_ `FCameraActorAttachmentInfo DefaultAttachmentInfo;`
- L63 _private member_ `FCameraContextDataID DataID;`
- L65 _private member_ `FCameraActorAttachmentInfo CachedAttachmentInfo;`
- L66 _private member_ `const USkeletalMeshComponent* CachedSkeletalMeshComponent = nullptr;`
- L67 _private member_ `FName CachedBoneName;`

#### struct `UE::Cameras::FCameraActorAttachmentInfoArrayReader`  
`struct FCameraActorAttachmentInfoArrayReader`  
_L73-90_
- desc: A special reader class for multiple attachment information.
- L75 _public function_ `FCameraActorAttachmentInfoArrayReader()`
- L76 _public prototype_ `FCameraActorAttachmentInfoArrayReader(TConstArrayView<FCameraActorAttachmentInfo> InAttachmentInfos, FCameraContextDataID InDataID);`
- L78 _public prototype_ `void Initialize(TConstArrayView<FCameraActorAttachmentInfo> InAttachmentInfos, FCameraContextDataID InDataID);`
- L80 _public prototype_ `bool GetAttachmentTransform(const FCameraContextDataTable& ContextDataTable, FTransform3d& OutTransform);`
- L84 _private prototype_ `void CacheAttachmentInfos(TConstArrayView<FCameraActorAttachmentInfo> InAttachmentInfos);`
- L88 _private member_ `TArray<FCameraActorAttachmentInfoReader> Readers;`
- L89 _private member_ `FCameraContextDataID DataID;`

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/EasingBlendCameraNode.h` (Public)


#### enum `EEasingCameraBlendType`  
`enum class EEasingCameraBlendType : uint8`  
_L16-50_
- reflection: `UENUM(BlueprintType)`
- desc: The easing type. These types are copied from, and behave in the same way as the corresponding easing types from Sequencer.
- L19 _public enumerator_ `Linear UMETA(Grouping=Linear, DisplayName="Linear")` — Linear easing
- L21 _public enumerator_ `SinIn UMETA(Grouping=Sinusoidal, DisplayName="Sinusoidal In")` — Sinusoidal easing
- L22 _public enumerator_ `SinOut UMETA(Grouping=Sinusoidal, DisplayName="Sinusoidal Out")`
- L23 _public enumerator_ `SinInOut UMETA(Grouping=Sinusoidal, DisplayName="Sinusoidal InOut")`
- L25 _public enumerator_ `QuadIn UMETA(Grouping=Quadratic, DisplayName="Quadratic In")` — Quadratic easing
- L26 _public enumerator_ `QuadOut UMETA(Grouping=Quadratic, DisplayName="Quadratic Out")`
- L27 _public enumerator_ `QuadInOut UMETA(Grouping=Quadratic, DisplayName="Quadratic InOut")`
- L29 _public enumerator_ `Cubic UMETA(Grouping=Cubic, DisplayName="Cubic")` — Cubic easing
- L30 _public enumerator_ `CubicIn UMETA(Grouping=Cubic, DisplayName="Cubic In")`
- L31 _public enumerator_ `CubicOut UMETA(Grouping=Cubic, DisplayName="Cubic Out")`
- L32 _public enumerator_ `CubicInOut UMETA(Grouping=Cubic, DisplayName="Cubic InOut")`
- L33 _public enumerator_ `HermiteCubicInOut UMETA(Grouping=Cubic, DisplayName="Hermite-Cubic InOut")`
- L35 _public enumerator_ `QuartIn UMETA(Grouping=Quartic, DisplayName="Quartic In")` — Quartic easing
- L36 _public enumerator_ `QuartOut UMETA(Grouping=Quartic, DisplayName="Quartic Out")`
- L37 _public enumerator_ `QuartInOut UMETA(Grouping=Quartic, DisplayName="Quartic InOut")`
- L39 _public enumerator_ `QuintIn UMETA(Grouping=Quintic, DisplayName="Quintic In")` — Quintic easing
- L40 _public enumerator_ `QuintOut UMETA(Grouping=Quintic, DisplayName="Quintic Out")`
- L41 _public enumerator_ `QuintInOut UMETA(Grouping=Quintic, DisplayName="Quintic InOut")`
- L43 _public enumerator_ `ExpoIn UMETA(Grouping=Exponential, DisplayName="Exponential In")` — Exponential easing
- L44 _public enumerator_ `ExpoOut UMETA(Grouping=Exponential, DisplayName="Exponential Out")`
- L45 _public enumerator_ `ExpoInOut UMETA(Grouping=Exponential, DisplayName="Exponential InOut")`
- L47 _public enumerator_ `CircIn UMETA(Grouping=Circular, DisplayName="Circular In")` — Circular easing
- L48 _public enumerator_ `CircOut UMETA(Grouping=Circular, DisplayName="Circular Out")`
- L49 _public enumerator_ `CircInOut UMETA(Grouping=Circular, DisplayName="Circular InOut")`

#### class `UEasingBlendCameraNode`  
`class UEasingBlendCameraNode : public USimpleFixedTimeBlendCameraNode`  
_L56-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USimpleFixedTimeBlendCameraNode`
- desc: A blend camera node that implements basic easing curve types.
- L62 _public function_ `void SetCameraBlendType(EEasingCameraBlendType BlendTypeIn)`
- L66 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L72 _public member_ `EEasingCameraBlendType BlendType = EEasingCameraBlendType::Linear;` — `UPROPERTY(EditAnywhere, Category=Blending, meta=(CameraContextData=true))` — The type of curve to use.
- L75 _public member_ `FCameraContextDataID BlendTypeDataID;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/InterruptedBlendCameraNode.h` (Public)


#### class `UE::Cameras::FInterruptedBlendCameraNodeEvaluator`  
`class FInterruptedBlendCameraNodeEvaluator : public FBlendCameraNodeEvaluator`  
_L18-41_
- inherits: `FBlendCameraNodeEvaluator`
- desc: A special blend meant to "freeze" an ongoing blend, and then start running another blend. This is used for instance by the Camera Modifier Service to blend out a camera rig instance that had not fully blended in yet. NOTE: this blend doesn't have any data, and can't be added by the user in the editor. It is meant to be created programmatically only.
- L24 _public prototype_ `FInterruptedBlendCameraNodeEvaluator();`
- L25 _public prototype_ `FInterruptedBlendCameraNodeEvaluator(FBlendCameraNodeEvaluator* InChildBlend, FBlendCameraNodeEvaluator* InFrozenBlend);`
- L30 _protected prototype_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren() override;` — FBlendCameraNodeEvaluator interface.
- L31 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L32 _protected prototype_ `virtual void OnBlendParameters(const FCameraNodePreBlendParams& Params, FCameraNodePreBlendResult& OutResult) override;`
- L33 _protected prototype_ `virtual void OnBlendResults(const FCameraNodeBlendParams& Params, FCameraNodeBlendResult& OutResult) override;`
- L37 _public member_ `FBlendCameraNodeEvaluator* ChildBlend = nullptr;`
- L38 _public member_ `FBlendCameraNodeEvaluator* FrozenBlend = nullptr;`
- L40 _public member_ `FCameraNodeEvaluationResult FrozenResult;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/LinearBlendCameraNode.h` (Public)


#### class `ULinearBlendCameraNode`  
`class ULinearBlendCameraNode : public USimpleFixedTimeBlendCameraNode`  
_L13-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USimpleFixedTimeBlendCameraNode`
- desc: Linear blend node.
- L19 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/LocationRotationBlendCameraNode.h` (Public)


#### class `ULocationRotationBlendCameraNode`  
`class ULocationRotationBlendCameraNode : public UBlendCameraNode`  
_L14-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlendCameraNode`
- desc: A blend node that blends translation and rotation differently.
- L20 _public prototype_ `ULocationRotationBlendCameraNode(const FObjectInitializer& ObjInit);`
- L26 _public member_ `TObjectPtr<USimpleBlendCameraNode> LocationBlend;` — `UPROPERTY()` — The blend to use for the camera's translation.
- L30 _public member_ `TObjectPtr<USimpleBlendCameraNode> RotationBlend;` — `UPROPERTY()` — The blend to use for the camera's rotation.
- L34 _public member_ `TObjectPtr<USimpleBlendCameraNode> OtherBlend;` — `UPROPERTY()` — The blend to use for everything else.
- L39 _protected prototype_ `virtual FCameraNodeChildrenView OnGetChildren() override;` — UCameraNode interface.
- L40 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/OrbitBlendCameraNode.h` (Public)


#### class `UOrbitBlendCameraNode`  
`class UOrbitBlendCameraNode : public UBlendCameraNode`  
_L14-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlendCameraNode`
- desc: Orbit blend node.
- L20 _public prototype_ `UOrbitBlendCameraNode(const FObjectInitializer& ObjInit);`
- L22 _public function_ `void SetDrivingBlend(USimpleBlendCameraNode* DrivingBlendIn)`
- L27 _public member_ `TObjectPtr<USimpleBlendCameraNode> DrivingBlend;` — `UPROPERTY()`
- L32 _protected prototype_ `virtual FCameraNodeChildrenView OnGetChildren() override;` — UCameraNode interface.
- L33 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/PopBlendCameraNode.h` (Public)


#### struct `UE::Cameras::FPopBlendCameraNodeHelper`  
`struct FPopBlendCameraNodeHelper`  
_L20-24_
- desc: Utility function for cutting evaluation results without blending.
- L22 _public prototype_ `static void PopParameters(const UE::Cameras::FCameraNodePreBlendParams& Params, FCameraNodePreBlendResult& OutResult);`
- L23 _public prototype_ `static void PopResults(const UE::Cameras::FCameraNodeBlendParams& Params, FCameraNodeBlendResult& OutResult);`

#### class `UPopBlendCameraNode`  
`class UPopBlendCameraNode : public UBlendCameraNode`  
_L32-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlendCameraNode`
- desc: A blend node that creates a camera cut (i.e. it doesn't blend at all).
- L38 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/ReverseBlendCameraNode.h` (Public)


#### class `UE::Cameras::FReverseBlendCameraNodeEvaluator`  
`class FReverseBlendCameraNodeEvaluator : public FBlendCameraNodeEvaluator`  
_L17-38_
- inherits: `FBlendCameraNodeEvaluator`
- desc: A special blend that can run another blend in "reverse", when that blend doesn't support reverse mode. This is used for instance by the Camera Modifier Service to blend things out. NOTE: this blend doesn't have any data, and can't be added by the user in the editor. It is meant to be created programmatically only.
- L23 _public prototype_ `FReverseBlendCameraNodeEvaluator();`
- L24 _public prototype_ `FReverseBlendCameraNodeEvaluator(FBlendCameraNodeEvaluator* InChildBlend);`
- L29 _protected prototype_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren() override;` — FBlendCameraNodeEvaluator interface.
- L30 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L31 _protected prototype_ `virtual void OnBlendParameters(const FCameraNodePreBlendParams& Params, FCameraNodePreBlendResult& OutResult) override;`
- L32 _protected prototype_ `virtual void OnBlendResults(const FCameraNodeBlendParams& Params, FCameraNodeBlendResult& OutResult) override;`
- L33 _protected prototype_ `virtual bool OnInitializeFromInterruption(const FCameraNodeBlendInterruptionParams& Params) override;`
- L37 _public member_ `FBlendCameraNodeEvaluator* ChildBlend = nullptr;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/SimpleBlendCameraNode.h` (Public)


#### class `USimpleBlendCameraNode`  
`class USimpleBlendCameraNode : public UBlendCameraNode`  
_L14-17_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UBlendCameraNode`
- desc: Base class for a blend camera node that uses a simple scalar factor.

#### class `USimpleFixedTimeBlendCameraNode`  
`class USimpleFixedTimeBlendCameraNode : public USimpleBlendCameraNode`  
_L23-40_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `USimpleBlendCameraNode`
- desc: Base class for a blend camera node that uses a simple scalar factor over a fixed time.
- L30 _public function_ `void SetBlendTime(float BlendTimeIn)` — `UE_DEPRECATED(5.7, "Now sets the default time, use SetDefaultBlendTime instead")` — Returns the volume of this element
- L32 _public function_ `void SetDefaultBlendTime(float BlendTimeIn)`
- L34 _public function_ `float GetDefaultBlendTime()`
- L39 _public member_ `FFloatCameraParameter BlendTime = 1.f;` — `UPROPERTY(EditAnywhere, Category=Blending)` — Duration of the blend.

#### struct `UE::Cameras::FSimpleBlendCameraNodeEvaluationResult`  
`struct FSimpleBlendCameraNodeEvaluationResult`  
_L48-51_
- desc: Result structure for defining a simple scalar-factor-based blend.
- L50 _public member_ `float BlendFactor = 0.f;`

#### class `UE::Cameras::FSimpleBlendCameraNodeEvaluator`  
`class FSimpleBlendCameraNodeEvaluator : public FBlendCameraNodeEvaluator`  
_L53-99_
- inherits: `FBlendCameraNodeEvaluator`
- L59 _public prototype_ `FSimpleBlendCameraNodeEvaluator();`
- L62 _public function_ `float GetBlendFactor() const` — Gets the last evaluated blend factor.
- L65 _public function_ `bool IsBlendFull() const` — Gets whether the blend is currently at 100%.
- L73 _public function_ `bool IsBlendFinished() const` — Gets whether the blend was flagged as finished. A simple blend typically finishes when it reaches 100%, but in rare cases it may want to continue running after that, possibly going back below 100% before going back up.
- L78 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FBlendCameraNodeEvaluator interface.
- L79 _protected prototype_ `virtual void OnBlendParameters(const FCameraNodePreBlendParams& Params, FCameraNodePreBlendResult& OutResult) override;`
- L80 _protected prototype_ `virtual void OnBlendResults(const FCameraNodeBlendParams& Params, FCameraNodeBlendResult& OutResult) override;`
- L81 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L82 _protected prototype_ `virtual bool OnSetReversed(bool bInReverse) override;`
- L84 _protected function_ `virtual void OnComputeBlendFactor(const FCameraNodeEvaluationParams& Params, FSimpleBlendCameraNodeEvaluationResult& OutResult)`
- L86 _protected function_ `void SetBlendFinished()`
- L89 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L92 _protected member_ `TCameraParameterReader<float> BlendTimeReader;`
- L96 _private member_ `float BlendFactor = 0.f;`
- L97 _private member_ `bool bIsBlendFinished = false;`
- L98 _private member_ `bool bReverse = false;`

#### class `UE::Cameras::FSimpleFixedTimeBlendCameraNodeEvaluator`  
`class FSimpleFixedTimeBlendCameraNodeEvaluator : public FSimpleBlendCameraNodeEvaluator`  
_L101-119_
- inherits: `FSimpleBlendCameraNodeEvaluator`
- L108 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FBlendCameraNodeEvaluator interface.
- L109 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L110 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L111 _protected prototype_ `virtual bool OnInitializeFromInterruption(const FCameraNodeBlendInterruptionParams& Params) override;`
- L113 _protected prototype_ `float GetTimeFactor() const;`
- L117 _private member_ `float TotalTime = 0.f;`
- L118 _private member_ `float CurrentTime = 0.f;`

#### Free symbols / members of external scopes

- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Blends/SmoothBlendCameraNode.h` (Public)


#### enum `ESmoothCameraBlendType`  
`enum class ESmoothCameraBlendType`  
_L13-17_
- reflection: `UENUM()`
- desc: The smoothstep type.
- L15 _public enumerator_ `SmoothStep`
- L16 _public enumerator_ `SmootherStep`

#### class `USmoothBlendCameraNode`  
`class USmoothBlendCameraNode : public USimpleFixedTimeBlendCameraNode`  
_L23-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USimpleFixedTimeBlendCameraNode`
- desc: A blend camera node that implements the smoothstep and smoothersteps algorithms.
- L29 _public function_ `void SetCameraBlendType(ESmoothCameraBlendType BlendTypeIn)`
- L33 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L39 _public member_ `ESmoothCameraBlendType BlendType;` — `UPROPERTY(EditAnywhere, Category=Blending)` — The type of algorithm to use.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/CameraNodeTypes.h` (Public)


#### enum `ECameraNodeOriginPosition`  
`enum class ECameraNodeOriginPosition : uint8`  
_L13-25_
- reflection: `UENUM()`
- desc: Defines an origin position for a camera node to operate at.
- L16 _public enumerator_ `CameraPose` — The position of the current camera pose.
- L18 _public enumerator_ `ActiveContext` — The origin of the active evaluation context on the main layer's blend stack.
- L20 _public enumerator_ `OwningContext` — The origin of the evaluation context of the current camera node.
- L22 _public enumerator_ `Pivot` — The location of the current pivot. If no pivot is found, fallback to ActiveContext.
- L24 _public enumerator_ `Pawn` — The location of the player's controlled pawn.

#### enum `ECameraNodeSpace`  
`enum class ECameraNodeSpace : uint8`  
_L31-45_
- reflection: `UENUM()`
- desc: Defines what space a camera node, or one of its features, should operate in.
- L34 _public enumerator_ `CameraPose` — The local space of the current camera pose.
- L36 _public enumerator_ `ActiveContext` — The space of the active evaluation context on the main layer's blend stack.
- L38 _public enumerator_ `OwningContext` — The space of the evaluation context of the current camera node.
- L40 _public enumerator_ `Pivot` — The space of the current pivot. If no pivot is found, fallback to ActiveContext.
- L42 _public enumerator_ `Pawn` — The space of the player's controlled pawn.
- L44 _public enumerator_ `World` — The space of the world in which the camera rig evaluates.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Collision/CollisionPushCameraNode.h` (Public)


#### enum `ECollisionSafePosition`  
`enum class ECollisionSafePosition : uint8`  
_L23-42_
- reflection: `UENUM()`
- desc: Specifies how to compute the default safe position for the collision camera node to push towards.
- L29 _public enumerator_ `ActiveContext` — The initial result location of the active evaluation context on the main layer's blend stack.
- L33 _public enumerator_ `OwningContext` — The initial result location of the evaluation context of the collision camera node.
- L37 _public enumerator_ `Pivot` — The current pivot. If no pivot is found, fallback to ActiveContext.
- L41 _public enumerator_ `Pawn` — The location of the player's controlled pawn.

#### enum `ECollisionSafePositionOffsetSpace`  
`enum class ECollisionSafePositionOffsetSpace : uint8`  
_L49-61_
- reflection: `UENUM()`
- desc: Describes the coordinate system in which to offset the collision camera node's safe position.
- L52 _public enumerator_ `ActiveContext` — The space of the active evaluation context on the main layer's blend stack.
- L54 _public enumerator_ `OwningContext` — The space of the evaluation context of the collision camera node.
- L56 _public enumerator_ `Pivot` — The space of the current pivot. If no pivot is found, fallback to ActiveContext.
- L58 _public enumerator_ `CameraPose` — The local space of the current camera pose.
- L60 _public enumerator_ `Pawn` — The space of the player's controlled pawn.

#### class `UE::Cameras::FCollisionPushCameraNodeEvaluator`  
`class FCollisionPushCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L69-152_
- inherits: `FCameraNodeEvaluator`
- desc: The collision push node evaluator class.
- L76 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FCameraNodeEvaluator interface.
- L77 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L79 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L112 _protected prototype_ `virtual void RunCollisionTrace(const FCameraNodeEvaluationParams& Params, const FCollisionTraceParams& TraceParams, FCameraNodeEvaluationResult& OutResult, FCollisionTraceResult& OutTraceResult);` — Run the collision trace using the given parameters. @param Params  The parameters for the current node evaluation @param TraceParams  The parameters for the collision trace @param OutResult   The result for the current node evaluation @param OutTraceResult  The result with either the handle to the asynchronous trace, if bRequestedAsyncCollision was true and it was possible to honor it, or the list of hit results to be processed synchronously
- L116 _private prototype_ `TOptional<FVector3d> GetFinalSafePosition(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& OutResult);`
- L117 _private prototype_ `TOptional<FVector3d> GetSafePosition(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& OutResult);`
- L119 _private prototype_ `void RunCollisionTrace(UWorld* World, APlayerController* PlayerController, const FVector3d& SafePosition, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L120 _private prototype_ `void HandleAsyncCollisionTraceResult(UWorld* World, const FVector3d& SafePosition, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L121 _private prototype_ `void HandleCollisionTraceResult(UWorld* World, TArrayView<const FHitResult> HitResults, const FVector3d& SafePosition, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L122 _private prototype_ `void HandleDisabledCollision(const FVector3d& SafePosition, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L123 _private prototype_ `void UpdatePushFactor(bool bFoundHit, float CurrentPushFactor, const FVector3d& SafePosition, const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);`
- L127 _private member_ `TCameraVariableReferenceReader<bool> EnableCollisionReader;`
- L128 _private member_ `TCameraVariableReferenceReader<FVector3d> CustomSafePositionReader;`
- L130 _private member_ `TCameraParameterReader<float> CollisionSphereRadiusReader;`
- L131 _private member_ `TCameraParameterReader<FVector3d> SafePositionOffsetReader;`
- L133 _private member_ `TUniquePtr<FCameraDoubleValueInterpolator> PushInterpolator;`
- L134 _private member_ `TUniquePtr<FCameraDoubleValueInterpolator> PullInterpolator;`
- L136 _private member_ `FTraceHandle CollisionTraceHandle;`
- L138 _private member_ `float LastPushFactor = 0.f;`
- L139 _private member_ `float LastDampedPushFactor = 0.f;`
- L142 _private member_ `ECameraCollisionDirection LastDirection = ECameraCollisionDirection::Pushing;`
- L145 _private member_ `bool bDebugCollisionEnabled = false;`
- L146 _private member_ `bool bDebugFoundHit = false;`
- L147 _private member_ `bool bDebugGotSafePosition = false;`
- L148 _private member_ `bool bDebugGotSafePositionOffset = false;`
- L149 _private member_ `FString DebugHitObjectName;`
- L150 _private member_ `FVector3d DebugSafePosition;`

#### struct `UE::Cameras::FCollisionPushCameraNodeEvaluator::FCollisionTraceParams`  
`struct FCollisionTraceParams`  
_L84-94_
- L86 _public member_ `UWorld* World = nullptr;`
- L87 _public member_ `APawn* Pawn = nullptr;`
- L88 _public member_ `FVector3d SafePosition = FVector3d::ZeroVector;`
- L89 _public member_ `FVector3d TraceStart = FVector3d::ZeroVector;`
- L90 _public member_ `FVector3d TraceEnd = FVector3d::ZeroVector;`
- L91 _public member_ `float CollisionSphereRadius = 1.f;`
- L92 _public member_ `ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Camera;`
- L93 _public member_ `bool bRequestedAsyncCollision = false;`

#### struct `UE::Cameras::FCollisionPushCameraNodeEvaluator::FCollisionTraceResult`  
`struct FCollisionTraceResult`  
_L96-100_
- L98 _public member_ `TArray<FHitResult> HitResults;`
- L99 _public member_ `FTraceHandle AsyncTraceHandle;`

#### enum `UE::Cameras::FCollisionPushCameraNodeEvaluator::ECameraCollisionDirection`  
`enum class ECameraCollisionDirection`  
_L141-141_
- L141 _public enumerator_ `enum class ECameraCollisionDirection { Pushing, Pulling }; ECameraCollisionDirection LastDirection = ECameraCollisionDirection::Pushing; #if UE_GAMEPLAY_CAMERAS_DEBUG bool bDebugCollisionEnabled = false; bool bDebugFoundHit = false; bool bDebugGotSafePosition = false; bool bDebugGotSafePositionOffset = false;`
- L141 _public enumerator_ `enum class ECameraCollisionDirection { Pushing, Pulling }; ECameraCollisionDirection LastDirection = ECameraCollisionDirection::Pushing; #if UE_GAMEPLAY_CAMERAS_DEBUG bool bDebugCollisionEnabled = false; bool bDebugFoundHit = false; bool bDebugGotSafePosition = false; bool bDebugGotSafePositionOffset = false;`

#### class `UCollisionPushCameraNode`  
`class UCollisionPushCameraNode : public UCameraNode`  
_L162-226_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Collision"))`
- inherits: `UCameraNode`
- desc: A node that pushes the camera towards a "safe position" when it is colliding with the environment. By default, the "safe position" is the pivot of the camera (if any) or the position of the player pawn.
- L170 _public member_ `ECollisionSafePosition SafePosition = ECollisionSafePosition::Pivot;` — `UPROPERTY(EditAnywhere, Category="Safe Position")` — How to compute the safe position.
- L177 _public member_ `FVector3dCameraVariableReference CustomSafePosition;` — `UPROPERTY(EditAnywhere, Category="Safe Position")` — An optional camera variable to query for a safe position. If null, or if the variable isn't set, fallback to the value defined by SafePosition.
- L181 _public member_ `FVector3dCameraParameter SafePositionOffset;` — `UPROPERTY(EditAnywhere, Category="Safe Position")` — World-space offset from the target to the line trace's end.
- L185 _public member_ `ECollisionSafePositionOffsetSpace SafePositionOffsetSpace = ECollisionSafePositionOffsetSpace::Pivot;` — `UPROPERTY(EditAnywhere, Category="Safe Position")` — What space the safe position offset should be in.
- L193 _public member_ `FBooleanCameraVariableReference EnableCollision;` — `UPROPERTY(EditAnywhere, Category="Collision")` — An optional boolean camera variable that specifies whether collision should be enabled. When enabled/disabled, the collision push amount will interpolate as per the PushInterpolator and PullInterpolator.
- L197 _public member_ `FFloatCameraParameter CollisionSphereRadius;` — `UPROPERTY(EditAnywhere, Category="Collision")` — Radius of the sphere used for collision testing.
- L201 _public member_ `TEnumAsByte<ECollisionChannel> CollisionChannel = ECollisionChannel::ECC_Camera;` — `UPROPERTY(EditAnywhere, Category="Collision")` — Collision channel to use for the line trace.
- L205 _public member_ `TObjectPtr<UCameraValueInterpolator> PushInterpolator;` — `UPROPERTY(EditAnywhere, Category="Collision")` — The interpolation to use when pushing the camera towards the safe position.
- L209 _public member_ `TObjectPtr<UCameraValueInterpolator> PullInterpolator;` — `UPROPERTY(EditAnywhere, Category="Collision")` — The interpolation to use when pulling the camera back to its ideal position.
- L216 _public member_ `bool bRunAsyncCollision = false;` — `UPROPERTY(EditAnywhere, Category="Collision")` — Whether to run the collision asynchrnously. This is better for performance, but results in collision handling being one frame late.
- L220 _public prototype_ `UCollisionPushCameraNode(const FObjectInitializer& ObjectInit);`
- L225 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Collision/OcclusionMaterialCameraNode.h` (Public)


#### class `UOcclusionMaterialCameraNode`  
`class UOcclusionMaterialCameraNode : public UCameraNode`  
_L15-57_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Collision"))`
- inherits: `UCameraNode`
- L23 _public member_ `TObjectPtr<UMaterialInterface> OcclusionTransparencyMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category="Occlusion")` — Material to apply on objects causing occlusion.
- L27 _public member_ `FFloatCameraParameter OcclusionSphereRadius;` — `UPROPERTY(EditAnywhere, Category="Occlusion")` — Radius of the sphere used for occlusion testing.
- L31 _public member_ `TEnumAsByte<ECollisionChannel> OcclusionChannel = ECollisionChannel::ECC_Camera;` — `UPROPERTY(EditAnywhere, Category="Occlusion")` — Collision channel to use for the occlusion testing.
- L39 _public member_ `ECameraNodeOriginPosition OcclusionTargetPosition = ECameraNodeOriginPosition::Pawn;` — `UPROPERTY(EditAnywhere, Category="Occlusion Target")` — The position of the occlusion trace's target. Objects encountered between the current camera pose location and this target will have the transparency material applied to them until they move out of the way.
- L43 _public member_ `ECameraNodeSpace OcclusionTargetOffsetSpace = ECameraNodeSpace::World;` — `UPROPERTY(EditAnywhere, Category="Occlusion Target")` — The space in which to apply the occlusion target offset.
- L47 _public member_ `FVector3dCameraParameter OcclusionTargetOffset;` — `UPROPERTY(EditAnywhere, Category="Occlusion Target")` — Offset from the target to the occlusion trace's end.
- L51 _public prototype_ `UOcclusionMaterialCameraNode(const FObjectInitializer& ObjectInit);`
- L56 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/ArrayCameraNode.h` (Public)


#### class `UArrayCameraNode`  
`class UArrayCameraNode : public UCameraNode`  
_L14-38_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Sequence", CameraNodeCategories="Common,Utility"))`
- inherits: `UCameraNode`
- desc: A camera node that runs a list of other camera nodes.
- L20 _public prototype_ `UArrayCameraNode(const FObjectInitializer& ObjInit);`
- L25 _protected prototype_ `virtual FCameraNodeChildrenView OnGetChildren() override;` — UCameraNode interface.
- L26 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L32 _public member_ `TArray<TObjectPtr<UCameraNode>> Children;` — `UPROPERTY()` — The camera nodes to run.
- L37 _public prototype_ `static TTuple<int32, int32> GetEvaluatorAllocationInfo();` — For unit tests.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/AutoFocusCameraNode.h` (Public)


#### class `UAutoFocusCameraNode`  
`class UAutoFocusCameraNode : public UCameraNode`  
_L15-41_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Rendering"))`
- inherits: `UCameraNode`
- desc: A camera node that sets the focus distance to the distance of the current target.
- L21 _public prototype_ `UAutoFocusCameraNode(const FObjectInitializer& ObjInit);`
- L26 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L32 _public member_ `FBooleanCameraVariableReference EnableAutoFocus;` — `UPROPERTY(EditAnywhere, Category="Auto-Focus")` — Whether auto-focus should be enabled.
- L40 _public member_ `FFloatCameraParameter AutoFocusDampingFactor;` — `UPROPERTY(EditAnywhere, Category="Auto-Focus")` — The damping factor for how fast the focus distance follows the target distance. When zero, damping is disabled and focus distance is always equal to target distance. Low factors are "laggy", high factors are "tight".

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/BodyParametersCameraNode.h` (Public)


#### class `UBodyParametersCameraNode`  
`class UBodyParametersCameraNode : public UCameraNode`  
_L14-32_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Body"))`
- inherits: `UCameraNode`
- desc: A camera node that configures parameters on the camera body.
- L21 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L27 _public member_ `FFloatCameraParameter ShutterSpeed;` — `UPROPERTY(EditAnywhere, Category="Filmback", DisplayName="Shutter Speed (1/s)")` — Current shutter speed, in 1/seconds
- L31 _public member_ `FFloatCameraParameter ISO;` — `UPROPERTY(EditAnywhere, Category="Filmback")` — The camera sensor sensitivity in ISO.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/BoomArmCameraNode.h` (Public)


#### class `UE::Cameras::FBoomArmCameraNodeEvaluator`  
`class FBoomArmCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L26-61_
- inherits: `FCameraNodeEvaluator`
- desc: The boom arm node evaluator class.
- L33 _protected prototype_ `virtual void OnBuild(const FCameraNodeEvaluatorBuildParams& Params) override;` — FCameraNodeEvaluator interface.
- L34 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L35 _protected prototype_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren() override;`
- L36 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L37 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L40 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L44 _protected prototype_ `virtual FRotator ComputeBoomRotation(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — FBoomArmCameraNodeEvaluator interface.
- L48 _private member_ `TCameraParameterReader<FVector3d> BoomOffsetReader;`
- L49 _private member_ `FInput2DCameraNodeEvaluator* InputSlotEvaluator = nullptr;`
- L51 _private member_ `TUniquePtr<TCameraValueInterpolator<double>> BoomLengthInterpolator;`
- L52 _private member_ `TCameraParameterReader<double> MaxForwardInterpolationFactorReader;`
- L53 _private member_ `TCameraParameterReader<double> MaxBackwardInterpolationFactorReader;`
- L54 _private member_ `FVector3d LastPivotLocation;`
- L55 _private member_ `double CumulativePull;`
- L58 _private member_ `FVector2d DebugYawPitch;`
- L59 _private member_ `bool bDebugDidClampPull;`

#### class `UBoomArmCameraNode`  
`class UBoomArmCameraNode : public UCameraNode`  
_L69-120_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that can rotate the camera in yaw and pitch based on player input.
- L75 _public prototype_ `UBoomArmCameraNode(const FObjectInitializer& ObjInit);`
- L80 _protected prototype_ `virtual FCameraNodeChildrenView OnGetChildren() override;` — UCameraNode interface.
- L81 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L87 _public member_ `FVector3dCameraParameter BoomOffset;` — `UPROPERTY(EditAnywhere, Category=Common)` — The offset of the boom. Rotation occurs at the base (i.e. before the offset).
- L91 _public member_ `TObjectPtr<UCameraValueInterpolator> BoomLengthInterpolator;` — `UPROPERTY(EditAnywhere, Category=Common)` — The interpolator to use for changing the boom length based on its pivot's movements.
- L98 _public member_ `FDoubleCameraParameter MaxForwardInterpolationFactor = -1.0;` — `UPROPERTY(EditAnywhere, Category=Common)` — The maximum amount of forward movement the interpolator can introduce, expressed as a factor of the default boom length.
- L105 _public member_ `FDoubleCameraParameter MaxBackwardInterpolationFactor = -1.0;` — `UPROPERTY(EditAnywhere, Category=Common)` — The maximum amount of backward movement the interpolator can introduce, expressed as a factor of the default boom length.
- L112 _public member_ `TObjectPtr<UInput2DCameraNode> InputSlot;` — `UPROPERTY(meta=(ObjectTreeGraphPinDirection=Input))` — The input slot for controlling the boom arm. If no input slot is specified, the boom arm will use the player controller view rotation.
- L118 _public member_ `bool bAdditiveRotation = false;` — `UPROPERTY(EditAnywhere, Category=Common)` — If true, the boom arm's rotation will add to the existing rotation instead of being absolute.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/CameraRigCameraNode.h` (Public)


#### class `UCameraRigCameraNode`  
`class UCameraRigCameraNode : public UCameraNode , public IAssetReferenceCameraNode , public ICustomCameraNodeParameterProvider`  
_L17-53_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Camera Rig Prefab", CameraNodeCategories="Common,Utility"))`
- inherits: `UCameraNode,IAssetReferenceCameraNode,ICustomCameraNodeParameterProvider`
- desc: A camera node that runs a camera rig's own node tree.
- L27 _protected prototype_ `virtual void OnPreBuild(FCameraBuildContext& BuildContext) override;` — UCameraNode interface.
- L28 _protected prototype_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext) override;`
- L29 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L32 _protected prototype_ `virtual void GatherPackages(FCameraRigPackages& OutPackages) const override;` — IAssetReferenceCameraNode interface.
- L35 _protected prototype_ `virtual void GetCustomCameraNodeParameters(FCameraNodeParameterInfos& OutParameterInfos) override;` — ICustomCameraNodeParameterProvider interface.
- L39 _protected prototype_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override;`
- L40 _protected prototype_ `virtual void GetGraphNodeName(FName InGraphName, FText& OutName) const override;`
- L45 _protected prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _public member_ `FCameraRigAssetReference CameraRigReference;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(ObjectTreeGraphHidden=true))` — The camera rig to run.

#### class `UE::Cameras::FCameraRigCameraNodeEvaluator`  
`class FCameraRigCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L58-80_
- inherits: `FCameraNodeEvaluator`
- L64 _public prototype_ `FCameraRigCameraNodeEvaluator();`
- L66 _public function_ `FCameraNodeEvaluator* GetCameraRigRootEvaluator() const`
- L71 _protected prototype_ `virtual FCameraNodeEvaluatorChildrenView OnGetChildren() override;` — FCameraNodeEvaluator interface.
- L72 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L73 _protected prototype_ `virtual void OnUpdateParameters(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult) override;`
- L74 _protected prototype_ `virtual void OnBuild(const FCameraNodeEvaluatorBuildParams& Params) override;`
- L75 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L79 _private member_ `FCameraNodeEvaluator* CameraRigRootEvaluator = nullptr;`

#### Free symbols / members of external scopes

- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/ClippingPlanesCameraNode.h` (Public)


#### class `UClippingPlanesCameraNode`  
`class UClippingPlanesCameraNode : public UCameraNode`  
_L14-30_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Rendering"))`
- inherits: `UCameraNode`
- desc: A camera node that sets the clipping planes for the evaluated camera.
- L21 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L26 _public member_ `FDoubleCameraParameter NearPlane;` — `UPROPERTY(EditAnywhere, Category="Clipping", meta=(ClampMin="0.001"))`
- L29 _public member_ `FDoubleCameraParameter FarPlane;` — `UPROPERTY(EditAnywhere, Category="Clipping", meta=(ClampMin="0.001"))`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/DampenPositionCameraNode.h` (Public)


#### class `UDampenPositionCameraNode`  
`class UDampenPositionCameraNode : public UCameraNode`  
_L15-41_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that smoothes the movement of the camera.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `FFloatCameraParameter ForwardDampingFactor = 0.f;` — `UPROPERTY(EditAnywhere, Category=Damping)` — Damping factor for forward/backward camera movement.
- L32 _public member_ `FFloatCameraParameter LateralDampingFactor = 0.f;` — `UPROPERTY(EditAnywhere, Category=Damping)` — Damping factor for left/right camera movement.
- L36 _public member_ `FFloatCameraParameter VerticalDampingFactor = 0.f;` — `UPROPERTY(EditAnywhere, Category=Damping)` — Damping factor for up/down camera movement.
- L40 _public member_ `ECameraNodeSpace DampenSpace = ECameraNodeSpace::CameraPose;` — `UPROPERTY(EditAnywhere, Category=Damping)` — What space the damping should be in.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/DampenRotationCameraNode.h` (Public)


#### class `UDampenRotationCameraNode`  
`class UDampenRotationCameraNode : public UCameraNode`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that smoothes the rotation of the camera.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `FFloatCameraParameter YawDampingFactor = 0.f;` — `UPROPERTY(EditAnywhere, Category=Damping)` — Damping factor for the camera yaw.
- L32 _public member_ `FFloatCameraParameter PitchDampingFactor = 0.f;` — `UPROPERTY(EditAnywhere, Category=Damping)` — Damping factor for the camera pitch.
- L36 _public member_ `FFloatCameraParameter RollDampingFactor = 0.f;` — `UPROPERTY(EditAnywhere, Category=Damping)` — Damping factor for the camera roll.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/FieldOfViewCameraNode.h` (Public)


#### class `UFieldOfViewCameraNode`  
`class UFieldOfViewCameraNode : public UCameraNode`  
_L15-38_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Lens"))`
- inherits: `UCameraNode`
- desc: A camera node that sets the field of view of the camera.
- L28 _public member_ `FFloatCameraParameter FieldOfView;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(UIMin="5.0", UIMax="170", ClampMin="0.001", ClampMax="360.0", Units=deg))` — The horizontal field of view, in degrees. Note that the effective horizontal field of view may be different, depending on the viewport size and the way aspect ratio constraints have been setup on the camera.
- L32 _public prototype_ `UFieldOfViewCameraNode(const FObjectInitializer& ObjectInit);`
- L37 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/FilmbackCameraNode.h` (Public)


#### class `UFilmbackCameraNode`  
`class UFilmbackCameraNode : public UCameraNode`  
_L14-65_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Body"))`
- inherits: `UCameraNode`
- desc: A camera node that configures the camera filmback.
- L20 _public prototype_ `UFilmbackCameraNode(const FObjectInitializer& ObjectInitializer);`
- L25 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L31 _public member_ `FFloatCameraParameter SensorWidth;` — `UPROPERTY(EditAnywhere, Category="Filmback", meta=(ClampMin="0.001", ForceUnits=mm))` — Horizontal size of filmback or digital sensor, in mm.
- L35 _public member_ `FFloatCameraParameter SensorHeight;` — `UPROPERTY(EditAnywhere, Category="Filmback", meta=(ClampMin="0.001", ForceUnits=mm))` — Vertical size of filmback or digital sensor, in mm.
- L39 _public member_ `FFloatCameraParameter SensorHorizontalOffset;` — `UPROPERTY(EditAnywhere, Category="Advanced", meta=(ForceUnits=mm))` — Horizontal offset of the sensor, in mm.
- L43 _public member_ `FFloatCameraParameter SensorVerticalOffset;` — `UPROPERTY(EditAnywhere, Category="Advanced", meta=(ForceUnits=mm))` — Vertical offset of the sensor, in mm.
- L47 _public member_ `FFloatCameraParameter Overscan;` — `UPROPERTY(EditAnywhere, Category="Advanced", meta=(ForceUnits=Percent))` — Sensor overscan, in percentages (0% for no increase).
- L51 _public member_ `FBooleanCameraParameter ConstrainAspectRatio = false;` — `UPROPERTY(EditAnywhere, Category="Filmback")` — Whether to constrain the aspect ratio of the evaluated camera.
- L57 _public member_ `FBooleanCameraParameter OverrideAspectRatioAxisConstraint = false;` — `UPROPERTY(EditAnywhere, Category="Filmback")` — Whether to override the default aspect ratio axis constraint defined on the player controller.
- L64 _public member_ `TEnumAsByte<EAspectRatioAxisConstraint> AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;` — `UPROPERTY(EditAnywhere, Category="Filmback")` — Defines the axis along which to constrain the aspect ratio of the evaluated camera. Only used when ConstrainAspectRatio is false and OverrideAspectRatioAxisConstraint is true.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/FirstPersonCameraNode.h` (Public)


#### class `UFirstPersonCameraNode`  
`class UFirstPersonCameraNode : public UCameraNode`  
_L14-55_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common"))`
- inherits: `UCameraNode`
- desc: A camera node that sets and enables the first-person parameters on the resulting camera view.
- L21 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L27 _public member_ `FBooleanCameraParameter EnableFirstPerson = true;` — `UPROPERTY(EditAnywhere, Category=Common)` — Whether to enable first-person view parameters on primitives tagged as "IsFirstPerson".
- L36 _public member_ `FFloatCameraParameter FirstPersonFieldOfView = 90.f;` — `UPROPERTY(EditAnywhere, Category=Common, meta=( UIMin="5.0", UIMax="170", ClampMin="0.001", ClampMax="360.0", Units=deg, EditCondition="bEnableFirstPersonFieldOfView"))` — The horizontal field of view (in degrees) used for primitives tagged as "IsFirstPerson". If zero or negative, use the normal field of view.
- L46 _public member_ `FFloatCameraParameter FirstPersonScale = 1.f;` — `UPROPERTY(EditAnywhere, Category=Common, meta=( UIMin="0.001", UIMax="1.0", ClampMin="0.001", Units=%, EditCondition="bEnableFirstPersonScale"))` — The scale to apply to primitives tagged as "IsFirstPerson". This is used to scale down these primitives and prevent them from intersecting with the scene.
- L51 _public member_ `bool bEnableFirstPersonFieldOfView = true;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(InlineEditConditionToggle))`
- L54 _public member_ `bool bEnableFirstPersonScale = true;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(InlineEditConditionToggle))`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/LensParametersCameraNode.h` (Public)


#### class `ULensParametersCameraNode`  
`class ULensParametersCameraNode : public UCameraNode`  
_L15-69_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Lens"))`
- inherits: `UCameraNode`
- desc: A camera node that sets parameter values on the camera lens.
- L22 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface.
- L27 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L35 _public member_ `FFloatCameraParameter FocalLength = { 35.f };` — `UPROPERTY(EditAnywhere, Category="Lens Parameters", meta=( UIMin=5.0, UIMax=200.0, ClampMin=0.001, ForceUnits=mm, EditCondition="bEnableFocalLength"))` — Current focal length of the camera (i.e. controls FoV, zoom)
- L41 _public member_ `FFloatCameraParameter Aperture = { 16.f };` — `UPROPERTY(EditAnywhere, Category="Lens Parameters", meta=( UIMin=0.1, UIMax=20.0, ClampMin=0.001, EditCondition="bEnableAperture"))` — Current aperture, in terms of f-stop (e.g. 2.8 for f/2.8)
- L47 _public member_ `FFloatCameraParameter FocusDistance = { 1000.f };` — `UPROPERTY(EditAnywhere, Category="Lens Parameters", meta=( UIMin=0.001, UIMax=100000.0, ClampMin=0.001, EditCondition="bEnableFocusDistance"))` — Manually-controlled focus distance (manual focus mode only)
- L54 _public member_ `FBooleanCameraParameter EnablePhysicalCamera = false;` — `UPROPERTY(EditAnywhere, Category="Lens Parameters")` — Whether post-process settings should be automatically applied to reflect the lens settings.
- L60 _public member_ `bool bEnableFocalLength = true;` — `UPROPERTY(EditAnywhere, Category="Lens Features", meta=(InlineEditConditionToggle))` — Enable setting the focal length. When false, focal length is not set.
- L64 _public member_ `bool bEnableAperture = true;` — `UPROPERTY(EditAnywhere, Category="Lens Features", meta=(InlineEditConditionToggle))` — Enable setting the aperture. When false, aperture is not set.
- L68 _public member_ `bool bEnableFocusDistance = false;` — `UPROPERTY(EditAnywhere, Category="Lens Features", meta=(InlineEditConditionToggle))` — Enable setting the focus distance. When false, focus distance is not set.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/OffsetCameraNode.h` (Public)


#### class `UOffsetCameraNode`  
`class UOffsetCameraNode : public UCameraNode`  
_L15-42_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that offsets the location of the camera.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `FVector3dCameraParameter TranslationOffset;` — `UPROPERTY(EditAnywhere, Category=Common)` — The translation offset to apply to the camera.
- L32 _public member_ `FRotator3dCameraParameter RotationOffset;` — `UPROPERTY(EditAnywhere, Category=Common)` — The rotation offset to apply to the camera.
- L36 _public member_ `ECameraNodeSpace OffsetSpace = ECameraNodeSpace::CameraPose;` — `UPROPERTY(EditAnywhere, Category=Common)` — The space in which to apply the offset.
- L41 _public prototype_ `static TTuple<int32, int32> GetEvaluatorAllocationInfo();` — For unit tests.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/OrthographicCameraNode.h` (Public)


#### class `UOrthographicCameraNode`  
`class UOrthographicCameraNode : public UCameraNode`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common"))`
- inherits: `UCameraNode`
- desc: A camera node that sets the perspective mode to orthographic.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `FBooleanCameraParameter EnableOrthographicMode = true;` — `UPROPERTY(EditAnywhere, Category="Orthographic")` — Sets the perspective mode to orthographic.
- L32 _public member_ `FFloatCameraParameter OrthographicWidth = DEFAULT_ORTHOWIDTH;` — `UPROPERTY(EditAnywhere, Category="Orthographic", meta=(Units=cm))` — The width of the orthographic view.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/PostProcessCameraNode.h` (Public)


#### class `UPostProcessCameraNode`  
`class UPostProcessCameraNode : public UCameraNode`  
_L15-32_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Rendering"))`
- inherits: `UCameraNode`
- desc: A camera node that adds post-process settings on the evaluated camera.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `FPostProcessSettings PostProcessSettings;` — `UPROPERTY(EditAnywhere, Category="Rendering", meta=(CameraContextData=true))` — The post-process settings to set on the output camera pose.
- L31 _public member_ `FCameraContextDataID PostProcessSettingsDataID;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/SetLocationCameraNode.h` (Public)


#### class `USetLocationCameraNode`  
`class USetLocationCameraNode : public UCameraNode`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that sets the location of the camera.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `FVector3dCameraParameter Location;` — `UPROPERTY(EditAnywhere, Category=Common)` — The location to set on the camera.
- L32 _public member_ `ECameraNodeSpace OffsetSpace = ECameraNodeSpace::OwningContext;` — `UPROPERTY(EditAnywhere, Category=Common)` — The space in which to apply the transform.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/SetRotationCameraNode.h` (Public)


#### class `USetRotationCameraNode`  
`class USetRotationCameraNode : public UCameraNode`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that sets the rotation of the camera.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L28 _public member_ `FRotator3dCameraParameter Rotation;` — `UPROPERTY(EditAnywhere, Category=Common)` — The rotation to set on the camera.
- L32 _public member_ `ECameraNodeSpace OffsetSpace = ECameraNodeSpace::CameraPose;` — `UPROPERTY(EditAnywhere, Category=Common)` — The space in which to apply the transform.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/SplineFieldOfViewCameraNode.h` (Public)


#### class `USplineFieldOfViewCameraNode`  
`class USplineFieldOfViewCameraNode : public UCameraNode`  
_L16-38_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Lens"))`
- inherits: `UCameraNode`
- desc: A camera node that sets the field of view of the camera by evaluating a curve.
- L24 _public member_ `FFloatCameraParameter SplineInput;` — `UPROPERTY(EditAnywhere, Category=Common)` — The input to pass to the field of view spline.
- L28 _public member_ `FCameraSingleCurve FieldOfViewSpline;` — `UPROPERTY(EditAnywhere, Category=Common)` — The field of view, in degrees.
- L32 _public prototype_ `USplineFieldOfViewCameraNode(const FObjectInitializer& ObjectInit);`
- L37 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/SplineOffsetCameraNode.h` (Public)


#### class `USplineOffsetCameraNode`  
`class USplineOffsetCameraNode : public UCameraNode`  
_L17-43_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that offsets the location and rotation of the camera by evaluating curves.
- L24 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.
- L30 _public member_ `FFloatCameraParameter SplineInput;` — `UPROPERTY(EditAnywhere, Category=Common)` — The input to pass to the offset splines.
- L34 _public member_ `FCameraVectorCurve TranslationOffsetSpline;` — `UPROPERTY(EditAnywhere, Category=Common)` — The spline that defines the translation offset to apply to the camera.
- L38 _public member_ `FCameraRotatorCurve RotationOffsetSpline;` — `UPROPERTY(EditAnywhere, Category=Common)` — The rotation offset to apply to the camera.
- L42 _public member_ `ECameraNodeSpace OffsetSpace = ECameraNodeSpace::CameraPose;` — `UPROPERTY(EditAnywhere, Category=Common)` — The space in which to apply the offset.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/SplineOrbitCameraNode.h` (Public)


#### struct `FSplineOrbitControlPoint`  
`struct FSplineOrbitControlPoint`  
_L20-52_
- reflection: `USTRUCT()`
- desc: Control point for the spline orbit camera node.
- L30 _public member_ `FVector3d LocationOffset = FVector3d::ZeroVector;` — `UPROPERTY(EditAnywhere, Category="Spline Orbit")` — The offset of the camera position from the orbit pivot. This defines the radius of the orbit at the given control point, along with any lateral or vertical position offsets.
- L38 _public member_ `FVector3d TargetOffset = FVector3d::ZeroVector;` — `UPROPERTY(EditAnywhere, Category="Target")` — The offset of the camera target as defined by projecting the orbit pivot on the line of sight. This adds rotation to the camera by making it look higher/lower/etc at the given control point.
- L45 _public member_ `FRotator3d RotationOffset = FRotator3d::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category="Target")` — A rotation offset applied to the camera. This adds rotation to the camera, in local space, applied after TargetOffset.
- L51 _public member_ `float PitchAngle = 0.f;` — `UPROPERTY(EditAnywhere, Category="Spline Orbit")` — The pitch angle for this control point.

#### class `USplineOrbitCameraNode`  
`class USplineOrbitCameraNode : public UCameraNode`  
_L59-102_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode`
- desc: A camera node that can orbit around a pivot point, and the shape of the orbit is defined by pitch-based parameters.
- L65 _public prototype_ `USplineOrbitCameraNode(const FObjectInitializer& ObjInit);`
- L70 _protected prototype_ `virtual FCameraNodeChildrenView OnGetChildren() override;` — UCameraNode interface.
- L71 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L77 _public member_ `FCameraVectorCurve LocationOffsetSpline;` — `UPROPERTY(EditAnywhere, Category="Spline Orbit", meta=(CurveEditorXLabelFormat="{0}deg"))` — Spline that defines the camera location's offset for a given pitch angle.
- L81 _public member_ `FCameraVectorCurve TargetOffsetSpline;` — `UPROPERTY(EditAnywhere, Category="Spline Orbit", meta=(CurveEditorXLabelFormat="{0}deg"))` — Spline that defines an additive camera target offset for a given pitch angle.
- L85 _public member_ `FCameraRotatorCurve RotationOffsetSpline;` — `UPROPERTY(EditAnywhere, Category="Spline Orbit", meta=(CurveEditorXLabelFormat="{0}deg"))` — Spline that defines an additive camera rotation offset for a given pitch angle.
- L88 _public member_ `FFloatCameraParameter LocationOffsetMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category="Spline Orbit")`
- L94 _public member_ `ECameraNodeSpace TargetOffsetSpace = ECameraNodeSpace::ActiveContext;` — `UPROPERTY(EditAnywhere, Category="Target")` — The space in which the control points' TargetOffset is applied.
- L101 _public member_ `TObjectPtr<UInput2DCameraNode> InputSlot;` — `UPROPERTY(meta=(ObjectTreeGraphPinDirection=Input))` — The input slot for controlling the orbiting. If no input slot is specified, this node will use the player controller view rotation.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Common/TargetRayCastCameraNode.h` (Public)


#### class `UTargetRayCastCameraNode`  
`class UTargetRayCastCameraNode : public UCameraNode`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Target"))`
- inherits: `UCameraNode`
- desc: A camera node that determines and sets the camera's target by running a ray-cast from the current camera position.
- L23 _public member_ `TEnumAsByte<ECollisionChannel> TraceChannel = ECollisionChannel::ECC_Camera;` — `UPROPERTY(EditAnywhere, Category="Ray-Cast")` — Trace channel to use for the ray-cast.
- L27 _public member_ `FBooleanCameraParameter AutoFocus = true;` — `UPROPERTY(EditAnywhere, Category="Auto-Focus")` — Whether to set the focus distance to the ray-cast hit result.
- L32 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Framing/BaseFramingCameraNode.h` (Public)


#### class `UBaseFramingCameraNode`  
`class UBaseFramingCameraNode : public UCameraNode, public ICustomCameraNodeParameterProvider`  
_L24-128_
- reflection: `UCLASS(MinimalAPI, Abstract, meta=(CameraNodeCategories="Framing"))`
- inherits: `UCameraNode,ICustomCameraNodeParameterProvider`
- desc: The base class for a standard scren-space framing camera node.
- L36 _public member_ `FVector3dCameraVariableReference TargetLocation;` — `UPROPERTY(EditAnywhere, Category="Target")` — A variable whose value is the desired target's location in world space. If set, and if the variable has been set, the obtained value takes priority over the TargetInfos property.
- L40 _public member_ `TArray<FCameraActorTargetInfo> TargetInfos;` — `UPROPERTY(EditAnywhere, Category="Target", meta=(CameraContextData=true))` — Specifies one or more target actors to frame.
- L43 _public member_ `FCameraContextDataID TargetInfosDataID;` — `UPROPERTY()`
- L50 _public member_ `FBooleanCameraParameter SetTargetDistance;` — `UPROPERTY(EditAnywhere, Category="Target")` — Whether the camera pose's target distance should be set to the distance between its location and the effective target's location.
- L56 _public member_ `FBooleanCameraParameter InitializeWithIdealFraming = true;` — `UPROPERTY(EditAnywhere, Category="Target")` — Whether to frame the target with the ideal framing immediately on the first frame.
- L60 _public member_ `FVector2dCameraParameter IdealFramingLocation;` — `UPROPERTY(EditAnywhere, Category="Framing Target")` — The ideal horizontal and vertical screen-space position of the target.
- L64 _public member_ `FFloatCameraParameter ReframeDampingFactor;` — `UPROPERTY(EditAnywhere, Category="Framing Target")` — The damping factor for how fast the framing recenters on the target.
- L72 _public member_ `FFloatCameraParameter LowReframeDampingFactor;` — `UPROPERTY(EditAnywhere, Category="Framing Target")` — If valid, the recentering damping factor will interpolate between LowReframeDampingFactor and ReframeDampingFactor as the target moves between the ideal target position and the boundaries of the hard-zone. If invalid, no interpolation occurs and the damping factor is always equal to ReframeDampingFactor.
- L81 _public member_ `FFloatCameraParameter ReengageTime;` — `UPROPERTY(EditAnywhere, Category="Framing Target")` — The time spent ramping up the reframing after exiting the dead zone. If set to zero or a negative value, reframing will immediately restart once the target has exited the dead zone. Otherwise the ReframeDampingFactor will interpolate from zero to its desired value over the specified amount of seconds.
- L90 _public member_ `FFloatCameraParameter DisengageTime;` — `UPROPERTY(EditAnywhere, Category="Framing Target")` — The time spent ramping down the reframing after entering the dead zone. If set to zero or a negative value, reframing will immediately stop once the target has entered the dead zone. Otherwise, the ReframeDampingFactor will interpolate towards zero over the specified amount of seconds.
- L93 _public member_ `FFloatCameraParameter TargetMovementAnticipationTime;` — `UPROPERTY(EditAnywhere, Category="Framing Target")`
- L100 _public member_ `FCameraFramingZoneParameter DeadZone;` — `UPROPERTY(EditAnywhere, Category="Framing Zones")` — The size of the dead zone, i.e. the zone inside which the target can freely move. Sizes are expressed screen percentages around the desired framing location.
- L110 _public member_ `FCameraFramingZoneParameter SoftZone;` — `UPROPERTY(EditAnywhere, Category="Framing Zones")` — The margins of the soft zone, i.e. the zone inside which the reframing will engage, in order to bring the target back towards the ideal framing position. If the target is outside of the soft zone, it will be forcibly and immedialy brought back to its edges, so this zone also defines the "hard" or "safe" zone of framing. Sizes are expressed in screen percentages from the edges.
- L115 _private member_ `FCameraActorTargetInfo TargetInfo_DEPRECATED;` — `UPROPERTY()`
- L119 _public prototype_ `UBaseFramingCameraNode(const FObjectInitializer& ObjectInit);`
- L124 _public prototype_ `virtual void PostLoad() override;` — UObject interface.
- L127 _public prototype_ `virtual void GetCustomCameraNodeParameters(FCameraNodeParameterInfos& OutParameterInfos) override;` — ICustomCameraNodeParameterProvider interface.

#### class `UE::Cameras::FBaseFramingCameraNodeEvaluator`  
`class FBaseFramingCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L156-346_
- inherits: `FCameraNodeEvaluator`
- desc: The base class for a framing camera node evaluator. This evaluator does nothing per se but provides utility functions to be called in a sub-class' OnRun method. Namely: - AcquireTargetLocation() : a default way to get the world location of the desired target. - UpdateFramingState() : computes the current state of the framing node. The result can be obtained from the State field. The, compute the desired framing state for the current tick, including the desired framing correction. This can be obtained from the Desired field. It is up to the sub-class to implement the necessary logic to honor this correction. For instance, a dolly shot would translate left/right (and maybe up/down too) to try and reframe things accordingly, whereas a panning shot would rotate the camera left/right/up/down to accomplish the same. - EndFramingUpdate() : the sub-class should call near the end of its OnRun method. This will for instance optionally set the target distance.
- L163 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FCameraNodeEvaluator interface.
- L166 _protected prototype_ `virtual void OnDrawEditorPreview(const FCameraEditorPreviewDrawParams& Params, FCameraDebugRenderer& Renderer) override;`
- L170 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L179 _protected prototype_ `TOptional<FVector3d> GetInitialDesiredWorldTarget(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& OutResult);` — The first frame aiming direction we need for proper initialization.
- L181 _protected prototype_ `void UpdateFramingState(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& OutResult, const FTransform3d& LastFraming);` — Updates the framing state for the current tick, see State member field.
- L183 _protected prototype_ `void EndFramingUpdate(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — Wraps-up the update with optional operations.
- L188 _private prototype_ `static void DrawFramingState(const FState& State, const FDesired& Desired, FCameraDebugRenderer& Renderer);`
- L191 _private prototype_ `FVector2d GetHardReframeCoords() const;`
- L193 _private prototype_ `void ComputeCurrentState(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& OutResult, const FTransform3d& LastFraming);`
- L194 _private prototype_ `void ComputeDesiredState(const FCameraNodeEvaluationParams& Params, const FCameraNodeEvaluationResult& OutResult);`
- L196 _private prototype_ `bool AcquireTargetInfo(TSharedPtr<const FCameraEvaluationContext> EvaluationContext, const FCameraNodeEvaluationResult& InResult, TArray<FCameraActorComputedTargetInfo>& OutInfos);`
- L197 _private prototype_ `bool ComputeFinalTargetInfo(const FCameraPose& CameraPose, const FMatrix& ViewProjectionMatrix, FVector3d& OutWorldTarget, FVector2d& OutScreenTarget, FFramingZone& OutScreenBounds);`
- L198 _private prototype_ `float ComputeScreenTargetSpeed(float DeltaTime, const FMatrix& ViewProjectionMatrix, const FVector3d& OldWorldTarget, const FVector3d& NewWorldTarget);`
- L199 _private prototype_ `FVector2d ComputeAnticipatedScreenTarget(float DeltaTime, const FVector2d& InPreviousAnticipatedScreenTarget, const FVector2d& InScreenTarget);`
- L200 _private prototype_ `FFramingZone ComputeEffectiveDeadZone();`
- L202 _private prototype_ `static FFramingZone ComputeScreenTargetBounds(const FMatrix& ViewProjectionMatrix, const FTransform3d& TargetTransform, const FBoxSphereBounds3d& LocalBounds);`
- L244 _protected member_ `FReaders Readers;`
- L302 _protected member_ `FState State;`
- L325 _protected member_ `FDesired Desired;`
- L333 _protected member_ `FWorldTargetInfos WorldTargets;`
- L340 _protected member_ `FScreenTargetHistory ScreenTargetHistory;`

#### enum `UE::Cameras::FBaseFramingCameraNodeEvaluator::ETargetFramingState`  
`enum class ETargetFramingState`  
_L207-224_
- desc: The current location of the target.
- L213 _public enumerator_ `InDeadZone` — The target is in the dead zone, i.e. it can roam freely unless we have an active reframing to finish.
- L218 _public enumerator_ `InSoftZone` — The target is in the soft zone, i.e. we will attempt to gently bring it back to the ideal framing position.
- L223 _public enumerator_ `InHardZone` — The target is in the hard zone, i.e. it has exited the soft zone and we need to bring it back ASAP.

#### struct `UE::Cameras::FBaseFramingCameraNodeEvaluator::FReaders`  
`struct FReaders`  
_L227-243_
- desc: Utility structure for all the parameter readers we need every frame.
- L229 _public member_ `FCameraActorTargetInfoArrayReader TargetInfos;`
- L231 _public member_ `TCameraParameterReader<FVector2d> IdealFramingLocation;`
- L232 _public member_ `TCameraParameterReader<bool> InitializeWithIdealFraming;`
- L233 _public member_ `TCameraParameterReader<bool> SetTargetDistance;`
- L235 _public member_ `TCameraParameterReader<float> ReframeDampingFactor;`
- L236 _public member_ `TCameraParameterReader<float> LowReframeDampingFactor;`
- L237 _public member_ `TCameraParameterReader<float> ReengageTime;`
- L238 _public member_ `TCameraParameterReader<float> DisengageTime;`
- L239 _public member_ `TCameraParameterReader<float> TargetMovementAnticipationTime;`
- L241 _public member_ `TCameraParameterReader<FCameraFramingZone> DeadZone;`
- L242 _public member_ `TCameraParameterReader<FCameraFramingZone> SoftZone;`

#### struct `UE::Cameras::FBaseFramingCameraNodeEvaluator::FState`  
`struct FState`  
_L247-301_
- desc: Utility struct for storing the current known state.
- L250 _public member_ `FVector2d IdealTarget;` — Screen-space position of the ideal framing position.
- L252 _public member_ `float ReframeDampingFactor;` — Current reframing damping factor.
- L254 _public member_ `float LowReframeDampingFactor;` — Current low reframing damping factor.
- L256 _public member_ `float ReframeDampingFactorAlpha;` — Current alpha between reframing damping factors.
- L258 _public member_ `float ReengageTime;` — Current reengage time.
- L260 _public member_ `float DisengageTime;` — Current disengage time.
- L262 _public member_ `float ToggleEngageTimeLeft;` — Current time spent disengaging or reengaging reframing
- L264 _public member_ `float ToggleEngageAlpha;` — Current reframing damping factor alpha due to engage toggle
- L266 _public member_ `float TargetMovementAnticipationTime;` — Current look-ahead time for anticipating target movement
- L268 _public member_ `FFramingZone DeadZone;` — Current coordinates of the dead zone.
- L270 _public member_ `FFramingZone SoftZone;` — Current coordinates of the soft zone.
- L273 _public member_ `FVector3d WorldTarget;` — Current world-space position of the tracked target.
- L275 _public member_ `FVector2d ScreenTarget;` — Current screen-space position of the tracked target.
- L277 _public member_ `FFramingZone ScreenTargetBounds;` — Current target bounds zone.
- L279 _public member_ `FFramingZone EffectiveDeadZone;` — Dead zone minus the screen target bounds.
- L282 _public member_ `ETargetFramingState TargetFramingState;` — Current state of the tracked target.
- L284 _public member_ `float TargetScreenSpaceSpeed = 0.f;` — Current screen-space speed of the tracked target.
- L286 _public member_ `bool bIsReframingTarget = false;` — Whether we are actively trying to bring the target back to the ideal position.
- L289 _public member_ `FCriticalDamper ReframeDamper;` — The damper for reframing from the soft zone.
- L293 _public member_ `FVector2d DebugDeadZoneEdgePoint;` — Intersection of the reframing vector with the dead zone box.
- L295 _public member_ `FVector2d DebugHardZoneEdgePoint;` — Intersection of the reframing vector with the hard zone box.
- L297 _public member_ `TArray<FFramingZone, TInlineAllocator<4>> DebugAllScreenTargetBounds;` — Screen bounds for all the targets.
- L300 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `UE::Cameras::FBaseFramingCameraNodeEvaluator::FDesired`  
`struct FDesired`  
_L305-324_
- desc: Utility struct for the desired reframing to be done in the current tick.
- L312 _public member_ `FVector2d ScreenTarget;` — The desired screen-space position of the tracked target. For instance, if the target is in the soft zone, this desired position will be the next step to get us closer to the ideal position.
- L317 _public member_ `FVector2d FramingCorrection;` — The screen-space correction we want this tick. This is effectively equal to: Desired.ScreenTarget - State.ScreenTarget
- L321 _public member_ `bool bHasCorrection = false;` — Whether we have any correction to do.
- L323 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `UE::Cameras::FBaseFramingCameraNodeEvaluator::FWorldTargetInfos`  
`struct FWorldTargetInfos`  
_L327-332_
- L329 _public member_ `TArray<FCameraActorComputedTargetInfo, TInlineAllocator<4>> TargetInfos;`
- L331 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `UE::Cameras::FBaseFramingCameraNodeEvaluator::FScreenTargetHistory`  
`struct FScreenTargetHistory`  
_L335-339_
- L337 _public member_ `FVector2d UnanticipatedScreenTarget;`
- L338 _public member_ `TArray<TTuple<FVector2d, float>, TInlineAllocator<10>> History;`

#### Free symbols / members of external scopes

- L130 _namespace_ `namespace UE`
- L130 _namespace_ `namespace Cameras` (scope `UE`)
- L348 _prototype_ `FArchive& operator <<(FArchive& Ar, FBaseFramingCameraNodeEvaluator::FState& State);` (scope `UE::Cameras`)
- L349 _prototype_ `FArchive& operator <<(FArchive& Ar, FBaseFramingCameraNodeEvaluator::FDesired& Desired);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Framing/CameraActorTargetInfo.h` (Public)


#### enum `ECameraTargetShape`  
`enum class ECameraTargetShape : uint8`  
_L20-28_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Point` — Use a single-point target.
- L25 _public enumerator_ `AutomaticBounds` — Use the target's computed bounds.
- L27 _public enumerator_ `ManualBounds` — Use custom bounds.

#### struct `FCameraActorTargetInfo`  
`struct FCameraActorTargetInfo`  
_L34-65_
- reflection: `USTRUCT(BlueprintType)`
- desc: Targeting information for a camera rig.
- L40 _public member_ `TSoftObjectPtr<AActor> Actor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Target")` — The actor to target.
- L44 _public member_ `FName SocketName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Target")` — An optional socket to target on the actor.
- L48 _public member_ `FName BoneName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Target")` — An optional bone to target on the actor.
- L52 _public member_ `ECameraTargetShape TargetShape = ECameraTargetShape::Point;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Target")` — Specifies the shape of the target.
- L56 _public member_ `float TargetSize = 10.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Target")` — Specifies the size of target. Only used if TargetShape is set to manual bounds.
- L60 _public member_ `float Weight = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category="Target")` — The weight of this target. Unused when only one target is used.
- L62 _public function_ `bool IsValid() const`
- L64 _public prototype_ `bool operator== (const FCameraActorTargetInfo& Other) const = default;`

#### struct `UE::Cameras::FCameraActorTargetInfoReader`  
`struct FCameraActorTargetInfoReader`  
_L71-96_
- desc: A special reader class for targeting information.
- L73 _public function_ `FCameraActorTargetInfoReader()`
- L74 _public prototype_ `FCameraActorTargetInfoReader(const FCameraActorTargetInfo& InTargetInfo, FCameraContextDataID InDataID);`
- L76 _public prototype_ `void Initialize(const FCameraActorTargetInfo& InTargetInfo, FCameraContextDataID InDataID);`
- L78 _public prototype_ `bool GetTargetInfo(const FCameraContextDataTable& ContextDataTable, FTransform3d& OutTransform, FBoxSphereBounds3d& OutBounds);`
- L82 _private prototype_ `void CacheTargetInfo(const FCameraActorTargetInfo& InTargetInfo);`
- L83 _private prototype_ `void ComputeTargetBounds(const FVector3d& TargetLocation, FBoxSphereBounds3d& OutBounds);`
- L87 _private member_ `FCameraActorTargetInfo DefaultTargetInfo;`
- L88 _private member_ `FCameraContextDataID DataID;`
- L90 _private member_ `FCameraActorTargetInfo CachedTargetInfo;`
- L91 _private member_ `const USkeletalMeshComponent* CachedSkeletalMeshComponent = nullptr;`
- L92 _private member_ `FName CachedBoneName;`
- L93 _private member_ `FName CachedParentBoneName;`

#### struct `UE::Cameras::FCameraActorComputedTargetInfo`  
`struct FCameraActorComputedTargetInfo`  
_L98-103_
- L100 _public member_ `FTransform3d Transform;`
- L101 _public member_ `FBoxSphereBounds3d LocalBounds;`
- L102 _public member_ `float NormalizedWeight = 1.f;`

#### struct `UE::Cameras::FCameraActorTargetInfoArrayReader`  
`struct FCameraActorTargetInfoArrayReader`  
_L108-129_
- desc: A special reader class for multiple targeting information.
- L110 _public function_ `FCameraActorTargetInfoArrayReader()`
- L111 _public prototype_ `FCameraActorTargetInfoArrayReader(TConstArrayView<FCameraActorTargetInfo> InTargetInfos, FCameraContextDataID InDataID);`
- L113 _public prototype_ `void Initialize(TConstArrayView<FCameraActorTargetInfo> InTargetInfos, FCameraContextDataID InDataID);`
- L115 _public prototype_ `bool ComputeTargetInfos(const FCameraContextDataTable& ContextDataTable, TArray<FCameraActorComputedTargetInfo>& ComputedTargets);`
- L118 _public prototype_ `void Refresh(TConstArrayView<FCameraActorTargetInfo> InTargetInfos);`
- L123 _private prototype_ `void CacheTargetInfos(TConstArrayView<FCameraActorTargetInfo> InTargetInfos);`
- L127 _private member_ `TArray<FCameraActorTargetInfoReader> Readers;`
- L128 _private member_ `FCameraContextDataID DataID;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L67 _namespace_ `namespace UE`
- L67 _namespace_ `namespace Cameras` (scope `UE`)
- L105 _prototype_ `FArchive& operator <<(FArchive& Ar, FCameraActorComputedTargetInfo& TargetInfo);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Framing/CameraFramingZone.h` (Public)


#### struct `FCameraFramingZone`  
`struct FCameraFramingZone`  
_L18-112_
- reflection: `USTRUCT(BlueprintType)`
- desc: A structure that defines a zone for use in framing subjects in screen-space. Margins are generally expressed in screen size percentages (between 0 and 1), but don't have a standard meaning. In some cases, they may be margins from the screen's edge, while in other cases they may be margins relative to a given screen point.
- L25 _public member_ `double Left;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Framing")`
- L28 _public member_ `double Top;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Framing")`
- L31 _public member_ `double Right;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Framing")`
- L34 _public member_ `double Bottom;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Framing")`
- L38 _public function_ `FCameraFramingZone()`
- L46 _public function_ `FCameraFramingZone(double UniformValue)`
- L54 _public function_ `FCameraFramingZone(double Horizontal, double Vertical)`
- L62 _public function_ `FCameraFramingZone(double InLeft, double InTop, double InRight, double InBottom)`
- L72 _public function_ `FCameraFramingZone operator*(float Scale) const`
- L77 _public function_ `FCameraFramingZone operator*(const FCameraFramingZone& Scale) const`
- L86 _public function_ `FCameraFramingZone operator+(const FCameraFramingZone& Other) const`
- L95 _public function_ `FCameraFramingZone operator-(const FCameraFramingZone& Other) const`
- L104 _public prototype_ `bool operator== (const FCameraFramingZone& Other) const = default;`
- L105 _public prototype_ `bool operator!= (const FCameraFramingZone& Other) const = default;`
- L109 _public prototype_ `static void TypeErasedInterpolate(uint8* From, const uint8* To, float Alpha);`
- L111 _public prototype_ `FString ToString() const;`

#### struct `TIsPODType`  
`template <> struct TIsPODType<FCameraFramingZone>`  
_L114-117_

#### enum `TIsPODType::(anonymous)`  
`enum`  
_L116-116_

#### struct `FCameraFramingZoneParameter`  
`struct FCameraFramingZoneParameter`  
_L121-137_
- reflection: `USTRUCT()`
- desc: Framing zone camera parameter.
- L125 _public typedef_ `using ValueType = FCameraFramingZone;`
- L128 _public member_ `FCameraFramingZone Value;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(ShowOnlyInnerProperties))`
- L131 _public member_ `FCameraVariableID VariableID;` — `UPROPERTY()`
- L133 _public function_ `FCameraFramingZoneParameter()`
- L134 _public function_ `FCameraFramingZoneParameter(const FCameraFramingZone& InValue) : Value(InValue)`

#### Free symbols / members of external scopes

- L116 _enumerator_ `enum { Value = true };` (scope `TIsPODType::__anonb0b5e3f00103`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Framing/DollyFramingCameraNode.h` (Public)


#### class `UDollyFramingCameraNode`  
`class UDollyFramingCameraNode : public UBaseFramingCameraNode`  
_L14-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseFramingCameraNode`
- desc: A camera node that frames a target by moving along a sideways rail (left/right relative to the camera transform) and optionally also up and down.
- L22 _public member_ `FBooleanCameraParameter CanMoveLaterally;` — `UPROPERTY(EditAnywhere, Category="Dolly")` — Whether the dolly can move laterally.
- L26 _public member_ `FBooleanCameraParameter CanMoveVertically;` — `UPROPERTY(EditAnywhere, Category="Dolly")` — Whether the dolly can move vertically.
- L30 _public prototype_ `UDollyFramingCameraNode(const FObjectInitializer& ObjectInit);`
- L35 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Framing/PanningFramingCameraNode.h` (Public)


#### class `UPanningFramingCameraNode`  
`class UPanningFramingCameraNode : public UBaseFramingCameraNode`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseFramingCameraNode`
- desc: A camera node that frames a target by rotating in place.
- L21 _public member_ `FBooleanCameraParameter CanPanLaterally;` — `UPROPERTY(EditAnywhere, Category="Panning")` — Whether the camera can rotate laterally (yaw).
- L25 _public member_ `FBooleanCameraParameter CanPanVertically;` — `UPROPERTY(EditAnywhere, Category="Panning")` — Whether the camera can rotate vertically (pitch).
- L29 _public prototype_ `UPanningFramingCameraNode(const FObjectInitializer& ObjectInit);`
- L34 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/AutoRotateInput2DCameraNode.h` (Public)


#### enum `ECameraAutoRotateDirection`  
`enum class ECameraAutoRotateDirection`  
_L16-34_
- reflection: `UENUM()`
- desc: Describes the type of auto-rotate.
- L19 _public enumerator_ `Facing` — Re-align towards the evaluation context's facing.
- L24 _public enumerator_ `Movement` — Re-align towards the evaluation context's movement direction. Doesn't do anything when there is no movement.
- L29 _public enumerator_ `MovementOrFacing` — Re-align towards the evaluation context's movement direction if there is movement, or towards its facing otherwise.
- L33 _public enumerator_ `Zero` — Re-align towards the zero direction.

#### class `UAutoRotateInput2DCameraNode`  
`class UAutoRotateInput2DCameraNode : public UInput2DCameraNode`  
_L41-97_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Input"))`
- inherits: `UInput2DCameraNode`
- desc: An input node that modifies a yaw/pitch input in order to re-align its values to a given default direction.
- L49 _public member_ `ECameraAutoRotateDirection Direction;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate")` — The direction to re-align towards.
- L53 _public member_ `FVector3dCameraVariableReference DirectionVector;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate")` — An override for the direction to re-align towards.
- L57 _public member_ `FFloatCameraParameter WaitTime = 1.f;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate")` — The time, in seconds, to wait before re-aligning.
- L61 _public member_ `FFloatCameraParameter DeactivationThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate")` — The minimum player-induced/manual rotation, in degrees, to deactivate auto-rotation.
- L65 _public member_ `TObjectPtr<UCameraValueInterpolator> Interpolator;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate")` — The interpolation for re-alignment.
- L69 _public member_ `FBooleanCameraParameter FreezeControlRotation = false;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate")` — Whether to suggest freezing the input control rotation.
- L73 _public member_ `FBooleanCameraParameter EnableAutoRotate = true;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate Toggle")` — Whether to enable auto-rotation.
- L77 _public member_ `FBooleanCameraParameter AutoRotateYaw = true;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate Toggle")` — Whether to auto-rotate yaw.
- L81 _public member_ `FBooleanCameraParameter AutoRotatePitch = true;` — `UPROPERTY(EditAnywhere, Category="Auto-Rotate Toggle")` — Whether to auto-rotate pitch.
- L85 _public member_ `TObjectPtr<UInput2DCameraNode> InputNode;` — `UPROPERTY()` — The underlying input node.
- L89 _public prototype_ `UAutoRotateInput2DCameraNode(const FObjectInitializer& ObjInit);`
- L94 _protected prototype_ `virtual FCameraNodeChildrenView OnGetChildren() override;` — UCameraNode interface.
- L95 _protected prototype_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext) override;`
- L96 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/CameraRigInput1DSlot.h` (Public)


#### class `UCameraRigInput1DSlot`  
`class UCameraRigInput1DSlot : public UInput1DCameraNode`  
_L22-84_
- reflection: `UCLASS(Abstract)`
- inherits: `UInput1DCameraNode`
- desc: The base class for a node that can handle and accumulate raw player input values.
- L30 _public member_ `FCameraParameterClamping Clamp;` — `UPROPERTY(EditAnywhere, Category="Input")` — Clamping of the final input value.
- L34 _public member_ `FCameraParameterNormalization Normalize;` — `UPROPERTY(EditAnywhere, Category="Input")` — Normalization of the final input value.
- L38 _public member_ `FBooleanCameraParameter RevertAxis = false;` — `UPROPERTY(EditAnywhere, Category="Input")` — Whether to revert the axis.
- L42 _public member_ `FDoubleCameraParameter Speed = 1.0;` — `UPROPERTY(EditAnywhere, Category="Input")` — A speed, in units/seconds, to use on the input value.
- L46 _public member_ `EBuiltInDoubleCameraVariable BuiltInVariable = EBuiltInDoubleCameraVariable::Yaw;` — `UPROPERTY(EditAnywhere, Category="Input")` — The variable to use to blend with other input slots.
- L50 _public member_ `FDoubleCameraVariableReference CustomVariable;` — `UPROPERTY(EditAnywhere, Category="Input", meta=(EditCondition="BuiltInVariable == EBuiltInDoubleCameraVariable::None"))` — The variable to use to blend with other input slots.
- L54 _public member_ `bool bIsPreBlended = true;` — `UPROPERTY(EditAnywhere, Category="Input")` — Whether the multiplier should be pre-blended.
- L60 _public member_ `FCameraRigInputSlotParameters InputSlotParameters_DEPRECATED;` — `UPROPERTY()`
- L64 _public function_ `FCameraVariableID GetVariableID() const`
- L65 _public function_ `FCameraVariableID GetSpeedVariableID() const`
- L70 _public prototype_ `virtual void PostLoad() override;` — UObject interface.
- L75 _protected prototype_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext) override;` — UCameraNode interface.
- L76 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L81 _private member_ `FCameraVariableID SpeedVariableID;` — `UPROPERTY()`
- L83 _private member_ `FCameraVariableID VariableID;` — `UPROPERTY()`

#### class `UE::Cameras::FCameraRigInput1DSlotEvaluator`  
`class FCameraRigInput1DSlotEvaluator : public FInput1DCameraNodeEvaluator`  
_L91-116_
- inherits: `FInput1DCameraNodeEvaluator`
- L97 _public prototype_ `FCameraRigInput1DSlotEvaluator();`
- L102 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FCameraNodeEvaluator interface.
- L103 _protected prototype_ `virtual void OnUpdateParameters(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult) override;`
- L104 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L105 _protected prototype_ `virtual void OnExecuteOperation(const FCameraOperationParams& Params, FCameraOperation& Operation) override;`
- L106 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L110 _protected member_ `TCameraParameterReader<bool> RevertAxisReader;`
- L111 _protected member_ `TCameraParameterReader<double> SpeedReader;`
- L113 _protected member_ `double DeltaInputValue = 0.f;`
- L114 _protected member_ `bool bIsAccumulated = true;`
- L115 _protected member_ `bool bIsLockedThisFrame = false;`

#### Free symbols / members of external scopes

- L86 _namespace_ `namespace UE`
- L86 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/CameraRigInput2DSlot.h` (Public)


#### class `UCameraRigInput2DSlot`  
`class UCameraRigInput2DSlot : public UInput2DCameraNode`  
_L24-98_
- reflection: `UCLASS(Abstract)`
- inherits: `UInput2DCameraNode`
- desc: The base class for a node that can handle and accumulate raw player input values.
- L32 _public member_ `FCameraParameterClamping ClampX;` — `UPROPERTY(EditAnywhere, Category="Input")` — Clamping of the final input value.
- L36 _public member_ `FCameraParameterClamping ClampY;` — `UPROPERTY(EditAnywhere, Category="Input")` — Clamping of the final input value.
- L40 _public member_ `FCameraParameterNormalization NormalizeX;` — `UPROPERTY(EditAnywhere, Category="Input")` — Normalization of the final input value.
- L44 _public member_ `FCameraParameterNormalization NormalizeY;` — `UPROPERTY(EditAnywhere, Category="Input")` — Normalization of the final input value.
- L48 _public member_ `FBooleanCameraParameter RevertAxisX = false;` — `UPROPERTY(EditAnywhere, Category="Input")` — Whether to revert the X axis.
- L52 _public member_ `FBooleanCameraParameter RevertAxisY = false;` — `UPROPERTY(EditAnywhere, Category="Input")` — Whether to revert the Y axis.
- L60 _public member_ `EBuiltInVector2dCameraVariable BuiltInVariable = EBuiltInVector2dCameraVariable::YawPitch;` — `UPROPERTY(EditAnywhere, Category="Input")` — The variable to use to blend with other input slots.
- L64 _public member_ `FVector2dCameraVariableReference CustomVariable;` — `UPROPERTY(EditAnywhere, Category="Input", meta=(EditCondition="BuiltInVariable == EBuiltInVector2dCameraVariable::None"))` — The variable to use to blend with other input slots.
- L68 _public member_ `bool bIsPreBlended = true;` — `UPROPERTY(EditAnywhere, Category="Input")` — Whether parameters such as speed should be pre-blended.
- L74 _public member_ `FCameraRigInputSlotParameters InputSlotParameters_DEPRECATED;` — `UPROPERTY()`
- L78 _public function_ `FCameraVariableID GetVariableID() const`
- L79 _public function_ `FCameraVariableID GetSpeedVariableID() const`
- L84 _public prototype_ `virtual void PostLoad() override;` — UObject interface.
- L89 _protected prototype_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext) override;` — UCameraNode interface.
- L90 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L95 _private member_ `FCameraVariableID SpeedVariableID;` — `UPROPERTY()`
- L97 _private member_ `FCameraVariableID VariableID;` — `UPROPERTY()`

#### class `UE::Cameras::FCameraRigInput2DSlotEvaluator`  
`class FCameraRigInput2DSlotEvaluator : public FInput2DCameraNodeEvaluator`  
_L105-131_
- inherits: `FInput2DCameraNodeEvaluator`
- L111 _public prototype_ `FCameraRigInput2DSlotEvaluator();`
- L116 _protected prototype_ `virtual void OnInitialize(const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult) override;` — FCameraNodeEvaluator interface.
- L117 _protected prototype_ `virtual void OnUpdateParameters(const FCameraBlendedParameterUpdateParams& Params, FCameraBlendedParameterUpdateResult& OutResult) override;`
- L118 _protected prototype_ `virtual void OnRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult) override;`
- L119 _protected prototype_ `virtual void OnExecuteOperation(const FCameraOperationParams& Params, FCameraOperation& Operation) override;`
- L120 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;`
- L124 _protected member_ `TCameraParameterReader<bool> RevertAxisXReader;`
- L125 _protected member_ `TCameraParameterReader<bool> RevertAxisYReader;`
- L126 _protected member_ `TCameraParameterReader<FVector2d> SpeedReader;`
- L128 _protected member_ `FVector2d DeltaInputValue = FVector2d::ZeroVector;`
- L129 _protected member_ `bool bIsAccumulated = true;`
- L130 _protected member_ `bool bIsLockedThisFrame = false;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L100 _namespace_ `namespace UE`
- L100 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/CameraRigInputSlotTypes.h` (Public)


#### struct `FCameraRigInputSlotParameters`  
`struct FCameraRigInputSlotParameters`  
_L15-24_
- reflection: `USTRUCT()`
- desc: General options for an input slot.
- L20 _public member_ `bool bIsAccumulated = true;` — `UPROPERTY(EditAnywhere, Category="Input")`
- L23 _public member_ `bool bIsPreBlended = true;` — `UPROPERTY(EditAnywhere, Category="Input")`

#### struct `FCameraParameterClamping`  
`struct FCameraParameterClamping`  
_L30-57_
- reflection: `USTRUCT()`
- desc: Value clamping parameters.
- L35 _public member_ `double MinValue = 0;` — `UPROPERTY(EditAnywhere, Category="Common", meta=(EditCondition="bClampMin"))`
- L38 _public member_ `double MaxValue = 0;` — `UPROPERTY(EditAnywhere, Category ="Common", meta=(EditCondition="bClampMax"))`
- L41 _public member_ `bool bClampMin = false;` — `UPROPERTY(EditAnywhere, Category="Common")`
- L44 _public member_ `bool bClampMax = false;` — `UPROPERTY(EditAnywhere, Category="Common")`
- L49 _public prototype_ `double ClampValue(double Value) const;` — Clamps the given value.
- L56 _public prototype_ `void GetEffectiveClamping(double& OutMinValue, double& OutMaxValue) const;` — Gets the effective min/max values for this struct. If a bound is disabled, the effective value will be lowest or max double precision values.

#### struct `FCameraParameterNormalization`  
`struct FCameraParameterNormalization`  
_L63-77_
- reflection: `USTRUCT()`
- desc: Value normalization parameters.
- L68 _public member_ `double MaxValue = 360;` — `UPROPERTY(EditAnywhere, Category="Common", meta=(ClampMin=0, EditCondition="bNormalize"))`
- L71 _public member_ `bool bNormalize = false;` — `UPROPERTY(EditAnywhere, Category="Common")`
- L76 _public prototype_ `double NormalizeValue(double Value) const;` — Normalizes the given value.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/DrivenControlRotationCameraNode.h` (Public)


#### class `UDrivenControlRotationCameraNode`  
`class UDrivenControlRotationCameraNode : public UInput2DCameraNode`  
_L15-23_
- reflection: `UCLASS()`
- inherits: `UInput2DCameraNode`
- desc: An input camera node that provides the yaw and pitch components of the control rotation when it is in the active camera rig, and then "detaches" from it while blending out, applying delta-rotations on the last known active control rotation.
- L22 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/Input1DCameraNode.h` (Public)


#### class `UInput1DCameraNode`  
`class UInput1DCameraNode : public UCameraNode`  
_L17-20_
- reflection: `UCLASS(Abstract, MinimalAPI, meta=( CameraNodeCategories="Input", ObjectTreeGraphSelfPinDirection="Output", ObjectTreeGraphDefaultPropertyPinDirection="Input"))`
- inherits: `UCameraNode`
- desc: A camera node that provides a floating-point value to an input slot.

#### class `UE::Cameras::FInput1DCameraNodeEvaluator`  
`class FInput1DCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L28-45_
- inherits: `FCameraNodeEvaluator`
- desc: Base class for a 1D input value node evaluator.
- L35 _public function_ `double GetInputValue() const` — Get the current input value.
- L40 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;` — FCameraNodeEvaluator interface.
- L44 _protected member_ `double InputValue;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/Input2DCameraNode.h` (Public)


#### class `UInput2DCameraNode`  
`class UInput2DCameraNode : public UCameraNode`  
_L18-21_
- reflection: `UCLASS(Abstract, MinimalAPI, meta=( CameraNodeCategories="Input", ObjectTreeGraphSelfPinDirection="Output", ObjectTreeGraphDefaultPropertyPinDirection="Input"))`
- inherits: `UCameraNode`
- desc: A camera node that provides a two-dimensional value to an input slot.

#### class `UE::Cameras::FInput2DCameraNodeEvaluator`  
`class FInput2DCameraNodeEvaluator : public FCameraNodeEvaluator`  
_L29-46_
- inherits: `FCameraNodeEvaluator`
- desc: Base class for a 2D input value node evaluator.
- L36 _public function_ `FVector2d GetInputValue() const` — Get the current input value.
- L41 _protected prototype_ `virtual void OnSerialize(const FCameraNodeEvaluatorSerializeParams& Params, FArchive& Ar) override;` — FCameraNodeEvaluator interface.
- L45 _protected member_ `FVector2d InputValue;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/InputAccumulator2DCameraNode.h` (Public)


#### class `UInputAccumulator2DCameraNode`  
`class UInputAccumulator2DCameraNode : public UCameraRigInput2DSlot`  
_L18-32_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Input"))`
- inherits: `UCameraRigInput2DSlot`
- desc: A camera node that accumulates player input.
- L26 _public member_ `TObjectPtr<UInput2DCameraNode> InputSlot;` — `UPROPERTY()` — Input node to accumulate values from.
- L31 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/InputAxisBinding2DCameraNode.h` (Public)


#### class `UInputAxisBinding2DCameraNode`  
`class UInputAxisBinding2DCameraNode : public UCameraRigInput2DSlot`  
_L19-46_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Input"))`
- inherits: `UCameraRigInput2DSlot`
- desc: An input node that reads player input from an input action and accumulates it into a usable input value. Basically a Raw Input Axis Binding node combined with an Input Accumulator node.
- L27 _public member_ `TArray<TObjectPtr<UInputAction>> AxisActions;` — `UPROPERTY(EditAnywhere, Category="Input")` — The axis input action(s) to read from.
- L31 _public member_ `FVector2dCameraParameter Multiplier = FVector2d(1.0, 1.0);` — `UPROPERTY(EditAnywhere, Category="Input")` — A multiplier to use on the input values.
- L35 _public member_ `bool bIsAccumulated = true;` — `UPROPERTY(EditAnywhere, Category="Input")` — Whether the player input is accumulated from frame to frame.
- L40 _public prototype_ `virtual void PostLoad() override;` — UObject interface.
- L45 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Input/RawInputAxisBinding2DCameraNode.h` (Public)


#### class `URawInputAxisBinding2DCameraNode`  
`class URawInputAxisBinding2DCameraNode : public UInput2DCameraNode`  
_L18-36_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Input"))`
- inherits: `UInput2DCameraNode`
- desc: An input node that reads player input from an input action.
- L26 _public member_ `TArray<TObjectPtr<UInputAction>> AxisActions;` — `UPROPERTY(EditAnywhere, Category="Input")` — The axis input action(s) to read from.
- L30 _public member_ `FVector2dCameraParameter Multiplier = FVector2d(1.0, 1.0);` — `UPROPERTY(EditAnywhere, Category="Input")` — A multiplier to use on the input values.
- L35 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Shakes/CameraShakeCameraNode.h` (Public)


#### enum `ECameraShakeEvaluationMode`  
`enum class ECameraShakeEvaluationMode : uint8`  
_L13-17_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Inline`
- L16 _public enumerator_ `VisualLayer`

#### class `UCameraShakeCameraNode`  
`class UCameraShakeCameraNode : public UCameraNode , public ICustomCameraNodeParameterProvider`  
_L23-52_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Camera Shake Prefab", CameraNodeCategories="Shakes"))`
- inherits: `UCameraNode,ICustomCameraNodeParameterProvider`
- desc: A camera node that runs a camera shake asset.
- L32 _protected prototype_ `virtual void OnPreBuild(FCameraBuildContext& BuildContext) override;` — UCameraNode interface.
- L33 _protected prototype_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext) override;`
- L34 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L37 _protected prototype_ `virtual void GetCustomCameraNodeParameters(FCameraNodeParameterInfos& OutParameterInfos) override;` — ICustomCameraNodeParameterProvider interface.
- L41 _protected prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _public member_ `FCameraShakeAssetReference CameraShakeReference;` — `UPROPERTY(EditAnywhere, Category=Common, meta=(ObjectTreeGraphHidden=true))` — The camera shake to run.
- L51 _public member_ `ECameraShakeEvaluationMode EvaluationMode = ECameraShakeEvaluationMode::VisualLayer;` — `UPROPERTY(EditAnywhere, Category=Common)`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Shakes/CompositeShakeCameraNode.h` (Public)


#### class `UCompositeShakeCameraNode`  
`class UCompositeShakeCameraNode : public UShakeCameraNode`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UShakeCameraNode`
- L19 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const;` — UCameraNode interface.
- L25 _public member_ `TArray<TObjectPtr<UShakeCameraNode>> Shakes;` — `UPROPERTY()` — The shakes to run simultaneously, in order.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Shakes/EnvelopeShakeCameraNode.h` (Public)


#### class `UEnvelopeShakeCameraNode`  
`class UEnvelopeShakeCameraNode : public UShakeCameraNode`  
_L12-34_
- reflection: `UCLASS()`
- inherits: `UShakeCameraNode`
- L19 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const;` — UCameraNode interface.
- L24 _public member_ `FFloatCameraParameter EaseInTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category="Easing")`
- L27 _public member_ `FFloatCameraParameter EaseOutTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category="Easing")`
- L30 _public member_ `FFloatCameraParameter TotalTime = 1.f;` — `UPROPERTY(EditAnywhere, Category="Time")`
- L33 _public member_ `TObjectPtr<UShakeCameraNode> Shake;` — `UPROPERTY(EditAnywhere, Category="Common")`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Shakes/PerlinNoiseLocationShakeCameraNode.h` (Public)


#### class `UPerlinNoiseLocationShakeCameraNode`  
`class UPerlinNoiseLocationShakeCameraNode : public UShakeCameraNode`  
_L12-40_
- reflection: `UCLASS()`
- inherits: `UShakeCameraNode`
- L19 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const;` — UCameraNode interface.
- L24 _public member_ `FFloatCameraParameter AmplitudeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`
- L27 _public member_ `FFloatCameraParameter FrequencyMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`
- L30 _public member_ `FInteger32CameraParameter Octaves = 1;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`
- L33 _public member_ `FPerlinNoiseData X;` — `UPROPERTY(EditAnywhere, Category="Common")`
- L36 _public member_ `FPerlinNoiseData Y;` — `UPROPERTY(EditAnywhere, Category="Common")`
- L39 _public member_ `FPerlinNoiseData Z;` — `UPROPERTY(EditAnywhere, Category="Common")`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Shakes/PerlinNoiseRotationShakeCameraNode.h` (Public)


#### class `UPerlinNoiseRotationShakeCameraNode`  
`class UPerlinNoiseRotationShakeCameraNode : public UShakeCameraNode`  
_L12-40_
- reflection: `UCLASS()`
- inherits: `UShakeCameraNode`
- L19 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const;` — UCameraNode interface.
- L24 _public member_ `FFloatCameraParameter AmplitudeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`
- L27 _public member_ `FFloatCameraParameter FrequencyMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`
- L30 _public member_ `FInteger32CameraParameter Octaves = 1;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")`
- L33 _public member_ `FPerlinNoiseData Yaw;` — `UPROPERTY(EditAnywhere, Category="Common")`
- L36 _public member_ `FPerlinNoiseData Pitch;` — `UPROPERTY(EditAnywhere, Category="Common")`
- L39 _public member_ `FPerlinNoiseData Roll;` — `UPROPERTY(EditAnywhere, Category="Common")`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Nodes/Utility/BlueprintCameraNode.h` (Public)


#### class `UBlueprintCameraNodeEvaluator`  
`class UBlueprintCameraNodeEvaluator : public UObject`  
_L28-142_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract, EditInlineNew, CollapseCategories)`
- inherits: `UObject`
- desc: The base class for Blueprint camera node evaluators.
- L35 _public prototype_ `void InitializeCameraNode();` — `UFUNCTION(BlueprintImplementableEvent, Category="Evaluation")`
- L39 _public prototype_ `void TickCameraNode(float DeltaTime);` — `UFUNCTION(BlueprintImplementableEvent, Category="Evaluation")` — The main execution callback for the camera node. Call SetCameraPose to affect the result.
- L49 _public prototype_ `AActor* FindEvaluationContextOwnerActor(TSubclassOf<AActor> ActorClass = nullptr) const;` — `UFUNCTION(BlueprintPure, Category="Evaluation", meta=(DeterminesOutputType="ActorClass"))` — A utility function that tries to find if an actor owns the evaluation context. Handles the situation where the evaluation context is an actor component (like a UGameplayCameraComponent) or an actor itself.
- L53 _public prototype_ `FBlueprintCameraPose GetCurrentCameraPose() const;` — `UFUNCTION(BlueprintPure, Category="Evaluation")` — A utility function to get the current camera pose from this node's camera data.
- L57 _public prototype_ `void SetCurrentCameraPose(const FBlueprintCameraPose& CameraPose);` — `UFUNCTION(BlueprintCallable, Category="Evaluation")` — A utility function to set the current camera pose on this node's camera data.
- L61 _public prototype_ `void SetDefaultOwningCameraRigParameters(FBlueprintCameraEvaluationDataRef TargetCameraData) const;` — `UFUNCTION(BlueprintCallable, Category="Evaluation")` — Assigns the default parameter values of the owning camera rig to the given camera evaluation data.
- L65 _public prototype_ `UCameraRigAsset* GetCameraRig() const;` — `UFUNCTION(BlueprintPure, Category="Evaluation")` — Gets the owning camera rig for this node.
- L69 _public prototype_ `APlayerController* GetPlayerController() const;` — `UFUNCTION(BlueprintPure, Category="Evaluation")` — Gets the player controller that the node is running for, if any.
- L73 _public typedef_ `using FCameraNodeEvaluatorInitializeParams = UE::Cameras::FCameraNodeEvaluatorInitializeParams;`
- L74 _public typedef_ `using FCameraNodeEvaluationParams = UE::Cameras::FCameraNodeEvaluationParams;`
- L75 _public typedef_ `using FCameraNodeEvaluationResult = UE::Cameras::FCameraNodeEvaluationResult;`
- L76 _public typedef_ `using FCameraEvaluationContext = UE::Cameras::FCameraEvaluationContext;`
- L79 _public prototype_ `void NativeInitializeCameraNode(const UBlueprintCameraNode* InBlueprintNode, const FCameraNodeEvaluatorInitializeParams& Params, FCameraNodeEvaluationResult& OutResult);` — Initialize this camera node.
- L82 _public prototype_ `void NativeRunCameraNode(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — Runs this camera node.
- L87 _public prototype_ `virtual UWorld* GetWorld() const override;` — UObject interface.
- L89 _public function_ `virtual bool ImplementsGetWorld() const override`
- L94 _private prototype_ `void SetupExecution(TSharedPtr<const FCameraEvaluationContext> EvaluationContext, FCameraNodeEvaluationResult& OutResult);`
- L95 _private prototype_ `void TeardownExecution();`
- L101 _protected member_ `bool bIsFirstFrame = false;` — `UPROPERTY(BlueprintReadOnly, Category="Evaluation")` — Whether this is the first frame of this camera node's lifetime.
- L105 _protected member_ `bool bIsActiveCameraRig = false;` — `UPROPERTY(BlueprintReadOnly, Category="Evaluation")` — Whether this camera node is running inside the active camera rig in this layer.
- L109 _protected member_ `TObjectPtr<UObject> EvaluationContextOwner;` — `UPROPERTY(BlueprintReadOnly, Category="Evaluation")` — The owner object of this camera node's evaluation context.
- L113 _protected member_ `FBlueprintCameraEvaluationDataRef CameraData;` — `UPROPERTY(BlueprintReadOnly, Category="Evaluation")` — The input/output camera data for this frame.
- L120 _public function_ `FBlueprintCameraPose GetCameraPose() const` — `UFUNCTION(BlueprintPure, BlueprintGetter, meta=(DeprecatedFunction, DeprecationMessage="Please use GetCurrentCameraPose"))`
- L123 _public function_ `void SetCameraPose(UPARAM(DisplayName="Camera Pose") const FBlueprintCameraPose& InC` — `UFUNCTION(BlueprintSetter, meta=(DeprecatedFunction, DeprecationMessage="Please use SetCurrentCameraPose"))`
- L130 _protected member_ `FBlueprintCameraPose CameraPose;` — `UPROPERTY(BlueprintGetter=GetCameraPose, BlueprintSetter=SetCameraPose, Category="Evaluation", meta=(DeprecatedProperty, DeprecationMessage="Please use CameraData, or GetCurrentCameraPose and SetCurrentCameraPose"))`
- L133 _protected member_ `FBlueprintCameraEvaluationDataRef VariableTable;` — `UPROPERTY(BlueprintReadOnly, Category="Evaluation", meta=(DeprecatedProperty, DeprecationMessage="Please use CameraData"))`
- L137 _private member_ `TSharedPtr<const UE::Cameras::FCameraEvaluationContext> CurrentContext;`
- L139 _private member_ `mutable TWeakObjectPtr<UWorld> WeakCachedWorld;`
- L141 _private member_ `const UBlueprintCameraNode* BlueprintNode = nullptr;`

#### class `UBlueprintCameraNode`  
`class UBlueprintCameraNode : public UCameraNode , public ICustomCameraNodeParameterProvider`  
_L148-213_
- reflection: `UCLASS(MinimalAPI, meta=(CameraNodeCategories="Common,Transform"))`
- inherits: `UCameraNode,ICustomCameraNodeParameterProvider`
- desc: A camera node that runs arbitrary Blueprint logic.
- L156 _public prototype_ `UBlueprintCameraNode(const FObjectInitializer& ObjInit);`
- L161 _protected prototype_ `virtual void OnPreBuild(FCameraBuildContext& BuildContext) override;` — UCameraNode interface.
- L162 _protected prototype_ `virtual void OnBuild(FCameraObjectBuildContext& BuildContext) override;`
- L163 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;`
- L167 _protected prototype_ `virtual EObjectTreeGraphObjectSupportFlags GetSupportFlags(FName InGraphName) const override;`
- L168 _protected prototype_ `virtual void GetGraphNodeName(FName InGraphName, FText& OutName) const override;`
- L172 _protected prototype_ `virtual void GetCustomCameraNodeParameters(FCameraNodeParameterInfos& OutParameterInfos) override;` — ICustomCameraNodeParameterProvider interface.
- L175 _protected prototype_ `virtual void PostLoad() override;` — UObject interface.
- L176 _protected prototype_ `virtual void BeginDestroy() override;`
- L178 _protected prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L183 _public function_ `const UBlueprintCameraNodeEvaluator* GetCameraNodeEvaluatorTemplate() const`
- L187 _private prototype_ `void RebuildOverrides();`
- L190 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L197 _private member_ `TObjectPtr<UBlueprintCameraNodeEvaluator> CameraNodeEvaluatorTemplate;` — `UPROPERTY(Instanced, EditAnywhere, Category=Common)` — The camera node evaluator to instantiate and run.
- L201 _private member_ `FCustomCameraNodeParameters CameraNodeEvaluatorOverrides;` — `UPROPERTY()` — Overrides for the evaluator instance.
- L205 _private member_ `bool bRunInEditor = false;` — `UPROPERTY(EditAnywhere, Category=Common)` — Whether this camera node should run in the editor.
- L210 _private member_ `TSubclassOf<UBlueprintCameraNodeEvaluator> CameraNodeEvaluatorClass_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraAction.h` (Public)


#### class `UCameraAction`  
`class UCameraAction : public UObject`  
_L24-55_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, DefaultToInstanced, EditInlineNew)`
- inherits: `UObject`
- desc: The base class for a camera action. A camera action is a potentially long-running operation that applies to camera rig instances updating in the main layer.
- L35 _public member_ `bool bPropagateToNewCameraRigs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Common, meta=(ExposeOnSpawn=true))` — Whether this action will be cloned onto new camera rigs as they get activated on the main layer.
- L42 _public member_ `float TimeOut = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Common, meta=(ExposeOnSpawn=true))` — The time, in seconds, after which the action should be automatically stopped. Zero or negative time means that this action never times out (it either completes on its own, or gets stopped by the user).
- L46 _public typedef_ `using FCameraActionEvaluatorBuilder = UE::Cameras::FCameraActionEvaluatorBuilder;`
- L49 _public prototype_ `FCameraActionEvaluatorPtr BuildEvaluator(FCameraActionEvaluatorBuilder& Builder) const;` — Builds the evaluator for this action.
- L54 _protected function_ `virtual FCameraActionEvaluatorPtr OnBuildEvaluator(FCameraActionEvaluatorBuilder& Builder) const` — Builds the evaluator for this action.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)
- L17 _typedef_ `using FCameraActionEvaluatorPtr = UE::Cameras::FCameraActionEvaluator*;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraActionEvaluator.h` (Public)


#### enum `UE::Cameras::ECameraActionEvaluatorFlags`  
`enum class ECameraActionEvaluatorFlags`  
_L30-36_
- desc: Flags for camera action evaluators.
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `CloneToNewActionScopes = 1`
- L35 _public enumerator_ `Default = None`

#### struct `UE::Cameras::FCameraActionEvaluatorInitializeParams`  
`struct FCameraActionEvaluatorInitializeParams`  
_L42-46_
- desc: Structure for initializing a new camera action evaluator.
- L45 _public member_ `TSharedPtr<FCameraActionScope> Scope;` — The scope in which the action will be running.

#### struct `UE::Cameras::FCameraActionEvaluatorTeardownParams`  
`struct FCameraActionEvaluatorTeardownParams`  
_L51-55_
- desc: Structure for tearing down a camera action evaluator.
- L54 _public member_ `TSharedPtr<FCameraActionScope> Scope;` — The scope in which the action was be running.

#### struct `UE::Cameras::FCameraActionEvaluationParams`  
`struct FCameraActionEvaluationParams`  
_L60-70_
- desc: Parameter structure for updating a camera action evaluator.
- L62 _public function_ `FCameraActionEvaluationParams(const FCameraNodeEvaluationParams& InParams) : EvaluationParams(InParams)`
- L67 _public member_ `const FCameraNodeEvaluationParams& EvaluationParams;` — Information about the evaluation pass that is currently happening.
- L69 _public member_ `TSharedPtr<FCameraActionScope> Scope;` — The scope in which the action is running.

#### struct `UE::Cameras::FCameraActionEvaluationResult`  
`struct FCameraActionEvaluationResult`  
_L75-86_
- desc: Result of updating the camera action.
- L77 _public function_ `FCameraActionEvaluationResult(FCameraNodeEvaluationResult& InResult) : Result(InResult)`
- L82 _public member_ `FCameraNodeEvaluationResult& Result;` — The evaluation result that pass through the camera rig instance.
- L85 _public member_ `bool bIsActionFinished = false;` — Whether this action has ended.

#### struct `UE::Cameras::FCameraActionEvaluatorSerializeParams`  
`struct FCameraActionEvaluatorSerializeParams`  
_L91-93_
- desc: Parameter structure for serializing a camera action evaluator.

#### struct `UE::Cameras::FCameraActionEvaluatorBuilder`  
`struct FCameraActionEvaluatorBuilder`  
_L98-111_
- desc: Structure for building new camera actions.
- L100 _public function_ `FCameraActionEvaluatorBuilder()`
- L104 _public prototype_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* BuildEvaluator(ArgTypes&&... InArgs);`
- L108 _private member_ `TSharedPtr<FCameraActionEvaluator> BuiltEvaluator;`
- L215 _function_ `template<typename EvaluatorType, typename ...ArgTypes> EvaluatorType* FCameraActionEvaluatorBuilder::BuildEvaluator(ArgTypes&&... InArgs)`

#### class `UE::Cameras::FCameraActionEvaluator`  
`class FCameraActionEvaluator`  
_L116-212_
- desc: Base class for a camera action evaluator.
- L122 _public prototype_ `FCameraActionEvaluator() = default;`
- L123 _public prototype_ `virtual ~FCameraActionEvaluator() = default;`
- L126 _public prototype_ `void Initialize(const FCameraActionEvaluatorInitializeParams& Params, FCameraActionEvaluationResult& OutResult);` — Initialize this action.
- L129 _public prototype_ `void Teardown(const FCameraActionEvaluatorTeardownParams& Params);` — Tear down this action.
- L132 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collect referenced UObjects for this action.
- L135 _public prototype_ `void PreScopeRun(const FCameraActionEvaluationParams& Params, FCameraActionEvaluationResult& OutResult);` — Run this action before its scope evaluates.
- L138 _public prototype_ `void PostScopeRun(const FCameraActionEvaluationParams& Params, FCameraActionEvaluationResult& OutResult);` — Run this action after its scope has evaluated.
- L141 _public prototype_ `void Serialize(const FCameraActionEvaluatorSerializeParams& Params, FArchive& Ar);` — Serializes the state of this action.
- L144 _public function_ `ECameraActionEvaluatorFlags GetActionEvaluatorFlags() const` — Gets the flags for this evaluator.
- L147 _public function_ `const UCameraAction* GetCameraAction() const` — Get the camera action.
- L151 _public function_ `template<typename CameraAction> const CameraAction* GetCameraActionAs() const` — Get the camera action.
- L158 _public prototype_ `void BuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder);` — Called to create debug blocks for this action evaluator.
- L164 _public prototype_ `void SetPrivateCameraAction(TObjectPtr<const UCameraAction> InCameraAction);` — Internal API.
- L169 _protected function_ `virtual void OnInitialize(const FCameraActionEvaluatorInitializeParams& Params, FCameraActionEvaluationResult& OutResult)` — Initialize this action.
- L172 _protected function_ `virtual void OnTeardown(const FCameraActionEvaluatorTeardownParams& Params)` — Tear down this action.
- L175 _protected function_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector)` — Collect referenced UObjects for this action.
- L178 _protected function_ `virtual void OnPreScopeRun(const FCameraActionEvaluationParams& Params, FCameraActionEvaluationResult& OutResult)` — Run this action before its scope evaluates.
- L181 _protected function_ `virtual void OnPostScopeRun(const FCameraActionEvaluationParams& Params, FCameraActionEvaluationResult& OutResult)` — Run this action after its scope has evaluated.
- L184 _protected function_ `virtual void OnSerialize(const FCameraActionEvaluatorSerializeParams& Params, FArchive& Ar)` — Serializes the state of this evaluator.
- L188 _protected function_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder)` — Called to create debug blocks for this action evaluator.
- L197 _protected prototype_ `void SetActionEvaluatorFlags(ECameraActionEvaluatorFlags InFlags);` — Sets the flags for this evaluator. Can be called from the constructor, or during OnInitialize().
- L203 _protected prototype_ `void AddActionEvaluatorFlags(ECameraActionEvaluatorFlags InFlags);` — Adds flags for this evaluator. Can be called from the constructor, or during OnInitialize().
- L208 _private member_ `TObjectPtr<const UCameraAction> PrivateCameraAction;` — The camera action to run.
- L211 _private member_ `ECameraActionEvaluatorFlags PrivateFlags = ECameraActionEvaluatorFlags::Default;` — The flags for this evaluator.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L227 _macro_ `#define UE_DECLARE_CAMERA_ACTION_EVALUATOR(ApiDeclSpec, ClassName)\` — Utility macros for declaring and defining camera actions.
- L230 _macro_ `#define UE_DECLARE_CAMERA_ACTION_EVALUATOR_EX(ApiDeclSpec, ClassName, BaseClassName)\`
- L233 _macro_ `#define UE_DEFINE_CAMERA_ACTION_EVALUATOR(ClassName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraActionInstanceID.h` (Public)


#### struct `FCameraActionInstanceID`  
`struct FCameraActionInstanceID`  
_L20-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: The ID of a camera action instance.
- L26 _public function_ `FCameraActionInstanceID() : Value(INVALID)`
- L28 _public function_ `bool IsValid() const`
- L30 _public function_ `explicit operator bool() const`
- L57 _private function_ `FCameraActionInstanceID(uint32 InValue) : Value(InValue)`
- L61 _private member_ `static const uint32 INVALID = uint32(-1);`
- L64 _private member_ `uint32 Value;` — `UPROPERTY()`

#### class `UCameraActionInstanceFunctions`  
`class UCameraActionInstanceFunctions : public UBlueprintFunctionLibrary`  
_L74-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint functions for camera action instance IDs.
- L85 _public function_ `static bool IsValid(FCameraActionInstanceID InstanceID)` — `UFUNCTION(BlueprintPure, Category="Camera")` — Whether the given camera action instance ID is valid. A valid ID doesn't necessarily correspond to a camera action instance that is still running.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)
- L34 _function_ `friend bool operator==(FCameraActionInstanceID A, FCameraActionInstanceID B)`
- L39 _function_ `friend bool operator!=(FCameraActionInstanceID A, FCameraActionInstanceID B)`
- L44 _function_ `friend uint32 GetTypeHash(FCameraActionInstanceID In)`
- L49 _function_ `friend FArchive& operator<< (FArchive& Ar, FCameraActionInstanceID& In)`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraActionScope.h` (Public)


#### class `UE::Cameras::FCameraActionScope`  
`class FCameraActionScope : public TSharedFromThis<FCameraActionScope>`  
_L39-124_
- inherits: `TSharedFromThis<FCameraActionScope>`
- desc: A camera action scope, which is a logical container for zero or more camera actions to be run for a given camera rig instance.
- L44 _public prototype_ `FCameraActionInstanceID StartAction(const UCameraAction* InCameraAction);` — Adds a new camera action.
- L47 _public prototype_ `bool IsActionRunning(const FCameraActionInstanceID InInstanceID) const;` — Returns whether the given action instance is running.
- L50 _public prototype_ `FCameraActionEvaluator* GetAction(const FCameraActionInstanceID InInstanceID) const;` — Gets a running action.
- L53 _public prototype_ `bool StopAction(const FCameraActionInstanceID InInstanceID);` — Stops a running camera action.
- L58 _public prototype_ `void Initialize(const FCameraRigEvaluationInfo& CameraRigInfo);` — Initialize this scope and associate it with the given camera rig.
- L61 _public function_ `TSharedPtr<const FCameraEvaluationContext> GetEvaluationContext() const` — Gets the evaluation context that the camera rig instance runs inside of.
- L64 _public function_ `const UCameraRigAsset* GetCameraRig() const` — Gets the camera rig associated with this action scope.
- L67 _public function_ `FCameraNodeEvaluator* GetChildEvaluator() const` — Gets the root evaluator for the camera rig instance that this action acts upon.
- L70 _public prototype_ `FCameraRigEvaluationInfo GetCameraRigEvaluationInfo() const;` — Gets the evaluation info of the camera rig instance that this action acts upon.
- L75 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collect referenced UObjects for all actions in the scope.
- L78 _public prototype_ `void PreScopeRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — Runs the pre-scope evaluation for all actions in the scope.
- L81 _public prototype_ `void PostScopeRun(const FCameraNodeEvaluationParams& Params, FCameraNodeEvaluationResult& OutResult);` — Runs the post-scope evaluation for all actions in the scope.
- L84 _public prototype_ `void Serialize(const FCameraActionEvaluatorSerializeParams& Params, FArchive& Ar);` — Serializes the state of all actions in the scope.
- L88 _public prototype_ `void BuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder);` — Called to create debug blocks for this action scope.
- L95 _private prototype_ `bool PrepareActionForRun(FActionInfo& ActionInfo, FCameraActionEvaluationResult& OutResult);`
- L96 _private prototype_ `bool HasActionTimedOut(float DeltaTime, FActionInfo& ActionInfo);`
- L97 _private prototype_ `void StopAction(FActionInfo& ActionInfo);`
- L116 _private member_ `FCameraRigInstanceID CameraRigInstanceID;`
- L117 _private member_ `TWeakPtr<const FCameraEvaluationContext> EvaluationContext;`
- L118 _private member_ `TObjectPtr<const UCameraRigAsset> CameraRig;`
- L119 _private member_ `const FCameraNodeEvaluationResult* ChildResult = nullptr;`
- L120 _private member_ `FCameraNodeEvaluator* ChildEvaluator = nullptr;`
- L122 _private member_ `TArray<FActionInfo> Actions;`
- L123 _private member_ `uint32 NextActionID = 0;`

#### enum `UE::Cameras::FCameraActionScope::EActionState`  
`enum EActionState`  
_L101-106_
- L103 _public enumerator_ `Uninitialized`
- L104 _public enumerator_ `Running`
- L105 _public enumerator_ `Finished`

#### struct `UE::Cameras::FCameraActionScope::FActionInfo`  
`struct FActionInfo`  
_L108-114_
- L110 _public member_ `TSharedPtr<FCameraActionEvaluator> Evaluator;`
- L111 _public member_ `FCameraActionInstanceID InstanceID;`
- L112 _public member_ `float ElapsedTime = 0.f;`
- L113 _public member_ `EActionState State = EActionState::Uninitialized;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraActionService.h` (Public)


#### class `UE::Cameras::FCameraActionService`  
`class FCameraActionService : public FCameraEvaluationService`  
_L29-110_
- inherits: `FCameraEvaluationService`
- desc: An evaluation service for running "camera actions", which allow manipuilating running camera rig instances, such as making them turn towards a given point, freeze them, and so on.
- L35 _public prototype_ `~FCameraActionService();`
- L38 _public prototype_ `FCameraActionInstanceID StartAction(const UCameraAction* CameraAction);` — Starts a new camera action.
- L41 _public prototype_ `bool IsActionRunning(const FCameraActionInstanceID InInstanceID) const;` — Returns whether a given camera action instance is running.
- L44 _public prototype_ `bool StopAction(const FCameraActionInstanceID InInstanceID);` — Stops a given camera action instance.
- L47 _public prototype_ `bool StopAllActionsOfClass(TSubclassOf<UCameraAction> InActionClass);` — Stops all camera action instances of a given class.
- L60 _public prototype_ `int32 GetNumScopeActions(const FCameraActionInstanceID InInstanceID) const;` — Returns how many actual actions are running for the given instance ID. This returns 1 for a running non-propagating action. For a propagating action, this returns the number of running camera rig instances that the action is currently affecting, i.e. the number of running clones. If an action has been started but the camera system hasn't updated yet, it returns 0 since action evaluators are created only on the first update.
- L65 _protected prototype_ `virtual void OnInitialize(const FCameraEvaluationServiceInitializeParams& Params) override;` — FCameraEvaluationService interface.
- L66 _protected prototype_ `virtual void OnPostCameraDirectorUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult) override;`
- L67 _protected prototype_ `virtual void OnPostUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult) override;`
- L68 _protected prototype_ `virtual void OnTeardown(const FCameraEvaluationServiceTeardownParams& Params) override;`
- L70 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L77 _private prototype_ `void OnRootNodeCameraRigEvent(const FRootCameraNodeCameraRigEvent& InEvent);`
- L79 _private prototype_ `void CloneAction(FActionSetInfo& ActionSet, TSharedRef<FCameraActionScope> NewActionScope);`
- L81 _private prototype_ `void CleanUpActions();`
- L99 _private member_ `FRootCameraNodeEvaluator* RootNodeEvaluator = nullptr;`
- L101 _private member_ `TArray<FActionSetInfo> ActionSets;`
- L103 _private member_ `uint32 NextActionSetID = 0;`
- L105 _private member_ `bool bHasAnyNewActiveCameraRigs = false;`

#### struct `UE::Cameras::FCameraActionService::FActionInfo`  
`struct FActionInfo`  
_L85-89_
- L87 _public member_ `TWeakPtr<FCameraActionScope> ActionScope = nullptr;`
- L88 _public member_ `FCameraActionInstanceID ActionID;`

#### struct `UE::Cameras::FCameraActionService::FActionSetInfo`  
`struct FActionSetInfo`  
_L91-97_
- L93 _public member_ `TObjectPtr<const UCameraAction> Data;`
- L94 _public member_ `TArray<FActionInfo, TInlineAllocator<4>> Actions;`
- L95 _public member_ `FCameraActionInstanceID InstanceID;`
- L96 _public member_ `bool bIsPending = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYCAMERAS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraModifierService.h` (Public)


#### class `UE::Cameras::FCameraModifierService`  
`class FCameraModifierService : public FCameraEvaluationService`  
_L19-54_
- inherits: `FCameraEvaluationService`
- desc: An evaluation service for running "camera modifiers", which are context-less camera rig instances meant to run additively in the camera system.
- L26 _public function_ `static int32 GetFirstBlendStackOrderKey()` — Blend stack order key for modifiers.
- L29 _public prototype_ `FCameraRigInstanceID StartCameraModifierRig(const UCameraRigAsset* CameraRig, ECameraRigLayer Layer, int32 OrderKey = 0);` — Starts a new instance of the given camera rig, using a "null" context.
- L32 _public prototype_ `FCameraRigInstanceID StartCameraModifierRig(const UCameraRigAsset* CameraRig, TSharedRef<FCameraEvaluationContext> EvaluationContext, ECameraRigLayer Layer, int32 OrderKey = 0);` — Starts a new instance of the given camera rig, using the given context.
- L35 _public prototype_ `void StopCameraModifierRig(FCameraRigInstanceID CameraRigID, bool bImmediately = false);` — Stops a running instance of a camera rig.
- L40 _protected prototype_ `virtual void OnInitialize(const FCameraEvaluationServiceInitializeParams& Params) override;` — FCameraEvaluationService interface.
- L41 _protected prototype_ `virtual void OnTeardown(const FCameraEvaluationServiceTeardownParams& Params) override;`
- L45 _private prototype_ `void EnsureModifierContextCreated();`
- L49 _private member_ `static const int32 FirstBlendStackOrderKey = 100;`
- L51 _private member_ `FCameraSystemEvaluator* Evaluator = nullptr;`
- L53 _private member_ `TSharedPtr<FCameraEvaluationContext> ModifierContext;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraParameterSetterService.h` (Public)


#### class `UE::Cameras::FCameraParameterSetterService`  
`class FCameraParameterSetterService : public FCameraEvaluationService`  
_L14-52_
- inherits: `FCameraEvaluationService`
- desc: A camera system service that handles running camera parameter setters.
- L20 _public prototype_ `FCameraParameterSetterService();`
- L23 _public prototype_ `template<typename ValueType> FCameraVariableSetterHandle AddCameraVariableSetter(const TCameraVariableSetter<ValueType>& InSetter);`
- L25 _public prototype_ `void StopCameraVariableSetter(const FCameraVariableSetterHandle& InHandle, bool bImmediately = false);`
- L27 _public prototype_ `void ApplyCameraVariableSetters(FCameraVariableTable& OutVariableTable);`
- L33 _protected prototype_ `virtual void OnPreUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult) override;` — FCameraEvaluationService interface.
- L37 _private prototype_ `void UpdateCameraVariableSetters(float DeltaTime);`
- L47 _private member_ `FCameraSystemEvaluator* Evaluator = nullptr;`
- L49 _private typedef_ `using FCameraVariableSetters = TSparseArray<FVariableSetterEntry>;`
- L50 _private member_ `FCameraVariableSetters VariableSetters;`
- L51 _private member_ `uint32 NextVariableSetterSerial = 0;`
- L55 _function_ `template<typename ValueType> FCameraVariableSetterHandle FCameraParameterSetterService::AddCameraVariableSetter(const TCameraVariableSetter<ValueType>& InSetter)`

#### struct `UE::Cameras::FCameraParameterSetterService::FVariableSetterEntry`  
`struct FVariableSetterEntry`  
_L41-45_
- L43 _public member_ `FCameraVariableSetterPtr Setter;`
- L44 _public member_ `FCameraVariableSetterHandle ThisHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/CameraShakeService.h` (Public)


#### struct `UE::Cameras::FStartCameraShakeParams`  
`struct FStartCameraShakeParams`  
_L24-34_
- desc: Parameters for starting a camera shake.
- L27 _public member_ `const UCameraShakeAsset* CameraShake = nullptr;` — The camera shake to play.
- L29 _public member_ `float ShakeScale = 1.f;` — The intensity to use for the camera shake.
- L31 _public member_ `ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal;` — The play space to modify the result by
- L33 _public member_ `FRotator UserPlaySpaceRotation;` — The custom space to use for the shake. Only used when PlaySpace is UserDefined.

#### class `UE::Cameras::FCameraShakeService`  
`class FCameraShakeService : public FCameraEvaluationService`  
_L39-84_
- inherits: `FCameraEvaluationService`
- desc: A camera system service that handles running camera shakes in the visual layer.
- L46 _public prototype_ `FCameraShakeInstanceID StartCameraShake(const FStartCameraShakeParams& Params);` — Starts a new camera shake.
- L49 _public prototype_ `bool IsCameraShakePlaying(FCameraShakeInstanceID InInstanceID) const;` — Checks if a camera shake is running.
- L52 _public prototype_ `bool StopCameraShake(FCameraShakeInstanceID InInstanceID, bool bImmediately = false);` — Stops a running camera shake.
- L59 _public prototype_ `void RequestCameraShakeThisFrame(const FStartCameraShakeParams& Params);` — Requests that a given camera shake runs. Multiple requests for the same camera shake are combined, and the camera shake keeps running as long as there are requests active. Requests are cleared every frame.
- L64 _protected prototype_ `virtual void OnInitialize(const FCameraEvaluationServiceInitializeParams& Params) override;` — FCameraEvaluationService interface.
- L65 _protected prototype_ `virtual void OnTeardown(const FCameraEvaluationServiceTeardownParams& Params) override;`
- L69 _private prototype_ `void EnsureShakeContextCreated();`
- L74 _private member_ `FCameraSystemEvaluator* Evaluator = nullptr;` — The system running this service.
- L77 _private member_ `TSharedPtr<FCameraEvaluationContext> ShakeContext;` — The evaluation context used for running the shakes.
- L80 _private member_ `TObjectPtr<UCameraRigAsset> ShakeContainerRig = nullptr;` — The camera rig used to create the shake container.
- L83 _private member_ `FCameraShakeServiceCameraNodeEvaluator* ShakeEvaluator = nullptr;` — The shake container evaluator.

#### class `UCameraShakeServiceCameraNode`  
`class UCameraShakeServiceCameraNode : public UCameraNode`  
_L89-97_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UCameraNode`
- L96 _protected prototype_ `virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;` — UCameraNode interface.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/OrientationInitializationService.h` (Public)


#### class `UE::Cameras::FOrientationInitializationService`  
`class FOrientationInitializationService : public FCameraEvaluationService`  
_L18-72_
- inherits: `FCameraEvaluationService`
- desc: A camera evaluation service responsible for initializing the orientation of newly activated camera rigs.
- L28 _public prototype_ `void SetYawPitchPreservationOverride(const FRotator3d& InOrientation);` — Override the yaw/pitch to preserve on any camera rig activated this frame. This will affect camera rigs who have the "Preserve Yaw/Pitch" policy.
- L34 _public prototype_ `void SetTargetPreservationOverride(const FVector3d& InTarget);` — Override the target location to preserve on any camera rig activated this frame. This will affect camera rigs who have the "Preserve Absolute/Relative Target" policies.
- L39 _protected prototype_ `virtual void OnInitialize(const FCameraEvaluationServiceInitializeParams& Params) override;` — FCameraEvaluationService interface.
- L40 _protected prototype_ `virtual void OnPostUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult) override;`
- L41 _protected prototype_ `virtual void OnRootCameraNodeEvent(const FRootCameraNodeCameraRigEvent& InEvent) override;`
- L44 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L49 _private prototype_ `void TryInitializeContextYawPitch(const FCameraRigEvaluationInfo& CameraRigInfo);`
- L50 _private prototype_ `void TryPreserveYawPitch(const FCameraRigEvaluationInfo& CameraRigInfo);`
- L51 _private prototype_ `void TryInitializeYawPitch(const FCameraRigEvaluationInfo& CameraRigInfo, TOptional<double> Yaw, TOptional<double> Pitch);`
- L52 _private prototype_ `void TryPreserveTarget(const FCameraRigEvaluationInfo& CameraRigInfo, bool bUseRelativeTarget);`
- L56 _private member_ `FCameraSystemEvaluator* Evaluator = nullptr;`
- L58 _private member_ `TWeakPtr<FCameraEvaluationContext> PreviousEvaluationContext;`
- L59 _private member_ `FVector3d PreviousContextLocation;`
- L60 _private member_ `FRotator3d PreviousContextRotation;`
- L61 _private member_ `bool bHasPreviousContextTransform = false;`
- L63 _private member_ `TOptional<FRotator3d> YawPitchPreservationOverride;`
- L64 _private member_ `TOptional<FVector3d> TargetPreservationOverride;`
- L67 _private member_ `FVector3d DebugLastEvaluatedTarget;`
- L68 _private member_ `FCameraIKAimDebugInfo LastAimDebugInfo;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Services/PlayerControlRotationService.h` (Public)


#### struct `UE::Cameras::FPlayerControlRotationParams`  
`struct FPlayerControlRotationParams`  
_L28-38_
- desc: Parameter structure for the player control rotation service.
- L31 _public member_ `double AxisActionMagnitudeThreshold = 0;` — The input magnitude below which we can change control rotation.
- L33 _public member_ `double AxisActionAngularSpeedThreshold = 0;` — The input angular change speed over which we can change control rotation.
- L35 _public member_ `bool bApplyControlRotation = true;` — Whether the service should set control rotation on the active context's player controller.
- L37 _public member_ `TArray<TObjectPtr<UInputAction>> AxisActions;` — Input actions representing how the player can move their pawn.

#### class `UE::Cameras::FPlayerControlRotationEvaluationService`  
`class FPlayerControlRotationEvaluationService : public FCameraEvaluationService`  
_L44-105_
- inherits: `FCameraEvaluationService`
- desc: An evaluation service that manages the player's control rotation based on what's going on with cameras.
- L51 _public prototype_ `FPlayerControlRotationEvaluationService();` — Create a new player control rotation service.
- L54 _public prototype_ `FPlayerControlRotationEvaluationService(const FPlayerControlRotationParams& InParams);` — Create a new player control rotation service, setting its parameters immediately.
- L59 _public function_ `const FPlayerControlRotationParams& GetParameters() const` — Gets the parameters for managing player control rotation.
- L61 _public function_ `void SetParameters(const FPlayerControlRotationParams& InParams)` — Sets the parameters for managing player control rotation.
- L64 _public function_ `const FRotator3d& GetCurrentControlRotation() const` — Gets the last evaluated control rotation.
- L66 _public function_ `bool IsControlRotationFrozen() const` — Gets whether the control rotation was last frozen.
- L70 _protected prototype_ `virtual void OnPostUpdate(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult) override;`
- L71 _protected prototype_ `virtual void OnAddReferencedObjects(FReferenceCollector& Collector) override;`
- L74 _protected prototype_ `virtual void OnBuildDebugBlocks(const FCameraDebugBlockBuildParams& Params, FCameraDebugBlockBuilder& Builder) override;`
- L79 _private prototype_ `void MonitorActiveContext(TSharedPtr<const FCameraEvaluationContext> ActiveContext);`
- L80 _private prototype_ `void BindActionValues(UEnhancedInputComponent* InputComponent);`
- L81 _private prototype_ `void UnbindActionValues();`
- L83 _private prototype_ `void UpdateControlRotation(const FCameraEvaluationServiceUpdateParams& Params, FCameraEvaluationServiceUpdateResult& OutResult);`
- L87 _private member_ `FPlayerControlRotationParams ServiceParams;`
- L89 _private member_ `TWeakObjectPtr<UEnhancedInputComponent> WeakInputComponent;`
- L90 _private member_ `TArray<FEnhancedInputActionValueBinding*> AxisBindings;`
- L92 _private member_ `FVector2d PreviousAxisBindingValue;`
- L93 _private member_ `FRotator3d CameraRotation;`
- L94 _private member_ `FRotator3d FrozenControlRotation;`
- L95 _private member_ `FRotator3d CurrentControlRotation;`
- L96 _private member_ `bool bIsFrozen = false;`
- L99 _private member_ `FTransform DebugPawnTransform;`
- L100 _private member_ `FString DebugFreezeReason;`
- L101 _private member_ `bool bDebugDidApplyControlRotation;`
- L102 _private member_ `TCameraDebugGraph<1> AxisActionAngularSpeedGraph;`
- L103 _private member_ `FCameraDebugClock AxisActionValueClock;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/StructUtils/OverridablePropertyBag.h` (Public)


#### struct `FInstancedOverridablePropertyBag`  
`struct FInstancedOverridablePropertyBag : public FInstancedPropertyBag`  
_L16-73_
- reflection: `USTRUCT()`
- inherits: `FInstancedPropertyBag`
- desc: Extended version of FInstancedPropertyBag to support "overriden properties" with an extra array of overriden parameter IDs.
- L26 _public prototype_ `template<typename ContainerType> void GetOverridenPropertyIDs(ContainerType& OutPropertyIDs) const;` — Gets the IDs of overriden properties, i.e. properties that have override values.
- L31 _public function_ `TConstArrayView<FGuid> GetOverridenPropertyIDs() const` — Gets the IDs of overriden properties, i.e. properties that have override values.
- L36 _public prototype_ `bool IsPropertyOverriden(const FGuid& InPropertyID) const;` — Returns whether the given property is overriden.
- L41 _public prototype_ `void SetPropertyOverriden(const FGuid& InPropertyID, bool bIsOverriden);` — Sets whether the given property is overriden by setting the matching override property's value.
- L46 _public prototype_ `bool IsPropertyOverriden(const FName InPropertyName) const;` — Returns whether the given property is overriden.
- L51 _public prototype_ `void SetPropertyOverriden(const FName InPropertyName, bool bIsOverriden);` — Sets whether the given property is overriden by setting the matching override property's value.
- L59 _public prototype_ `void MigrateToNewBagInstanceWithOverrides(const FInstancedPropertyBag& NewBagInstance);` — Migrate this property bag to the layout of the given one. Overriden values in this property bag will be preserved. Other values will adopt the values of the given new bag.
- L65 _public prototype_ `bool SerializeFromMismatchedTag(FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);`
- L66 _public prototype_ `bool Serialize(FArchive& Ar);`
- L72 _private member_ `TArray<FGuid> OverridenPropertyIDs;` — `UPROPERTY()` — List of properties that have override values.
- L76 _function_ `template<typename ContainerType> void FInstancedOverridablePropertyBag::GetOverridenPropertyIDs(ContainerType& OutPropertyIDs) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FInstancedOverridablePropertyBag> : public TStructOpsTypeTraits<FInstancedPropertyBag>`  
_L87-94_
- inherits: `TStructOpsTypeTraits<FInstancedPropertyBag>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L90-93_

#### enum `FOverridablePropertyBagCustomVersion::Type`  
`enum Type`  
_L98-106_
- L100 _public enumerator_ `BeforeCustomVersionWasAdded = 0`
- L101 _public enumerator_ `FixSerializer = 1`
- L102 _public enumerator_ `MissingPropertyFlags = 2`
- L104 _public enumerator_ `VersionPlusOne`
- L105 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L91 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonfbe8102f0103`)
- L92 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonfbe8102f0103`)
- L96 _namespace_ `namespace FOverridablePropertyBagCustomVersion`
- L108 _variable_ `const FGuid GUID(0x5426C227, 0x4B3145B2, 0x9B9BED1F, 0x327FB126);` (scope `FOverridablePropertyBagCustomVersion`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Transitions/DefaultTransitionConditions.h` (Public)


#### class `UIsCameraRigTransitionCondition`  
`class UIsCameraRigTransitionCondition : public UCameraRigTransitionCondition`  
_L14-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraRigTransitionCondition`
- desc: A transition condition that matches the previous and/or next camera rigs against one of the owning camera asset's rigs.
- L23 _public member_ `TObjectPtr<UCameraRigAsset> PreviousCameraRig;` — `UPROPERTY(EditAnywhere, Category=Transition, meta=(UseSelfCameraRigPicker=true, ObjectTreeGraphHidden=true))` — Passes if null, or equal to the previous camera rig.
- L27 _public member_ `TObjectPtr<UCameraRigAsset> NextCameraRig;` — `UPROPERTY(EditAnywhere, Category=Transition, meta=(UseSelfCameraRigPicker=true, ObjectTreeGraphHidden=true))` — Passes if null, or equal to the next camera rig.
- L32 _protected prototype_ `virtual bool OnTransitionMatches(const FCameraRigTransitionConditionMatchParams& Params) const override;` — UCameraRigTransitionCondition interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/Transitions/GameplayTagTransitionConditions.h` (Public)


#### class `UGameplayTagTransitionCondition`  
`class UGameplayTagTransitionCondition : public UCameraRigTransitionCondition`  
_L15-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraRigTransitionCondition`
- desc: A transition condition that matches the gameplay tags on the previous and next camera rigs and assets. Both queries need to pass. Empty queries pass by default.
- L24 _public member_ `FGameplayTagQuery PreviousGameplayTagQuery;` — `UPROPERTY(EditAnywhere, Category=Transition)` — The gameplay tags to look for on the previous camera rig/asset.
- L28 _public member_ `FGameplayTagQuery NextGameplayTagQuery;` — `UPROPERTY(EditAnywhere, Category=Transition)` — The gameplay tags to look for on the next camera rig/asset.
- L33 _protected prototype_ `virtual bool OnTransitionMatches(const FCameraRigTransitionConditionMatchParams& Params) const override;` — UCameraRigTransitionCondition interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/ValueInterpolators/AccelerationDecelerationValueInterpolator.h` (Public)


#### class `UAccelerationDecelerationValueInterpolator`  
`class UAccelerationDecelerationValueInterpolator : public UCameraValueInterpolator`  
_L14-33_
- reflection: `UCLASS(meta=(DisplayName="Acceleration-Deceleration"))`
- inherits: `UCameraValueInterpolator`
- desc: A value interpolator that first accelerates up to a maximum speed, and then decelerates before reaching the target value.
- L24 _public member_ `float Acceleration = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed", meta=(ExposeOnSpawn=true))` — The acceleration rate at the start of interpolation.
- L28 _public member_ `float MaxSpeed = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed", meta=(ExposeOnSpawn=true))` — The maximum speed reachable during interpolation.
- L32 _public member_ `float Deceleration = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed", meta=(ExposeOnSpawn=true))` — The deceleration rate at the end of interpolation.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/ValueInterpolators/CriticalDamperValueInterpolator.h` (Public)


#### class `UCriticalDamperValueInterpolator`  
`class UCriticalDamperValueInterpolator : public UCameraValueInterpolator`  
_L14-25_
- reflection: `UCLASS(meta=(DisplayName="Critical Damper"))`
- inherits: `UCameraValueInterpolator`
- desc: A value interpolator that uses a spring-mass system to converge towards the target value.
- L24 _public member_ `float DampingFactor = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damping", meta=(ExposeOnSpawn=true))` — The damping factor of the spring-mass system.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/ValueInterpolators/DoubleIIRValueInterpolator.h` (Public)


#### class `UDoubleIIRValueInterpolator`  
`class UDoubleIIRValueInterpolator : public UCameraValueInterpolator`  
_L13-32_
- reflection: `UCLASS(meta=(DisplayName="Double-IIR"))`
- inherits: `UCameraValueInterpolator`
- desc: Double infinite impulse response filter interpolator.
- L23 _public member_ `float PrimarySpeed = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed", meta=(ExposeOnSpawn=true))` — The primary speed of interpolation.
- L27 _public member_ `float IntermediateSpeed = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed", meta=(ExposeOnSpawn=true))` — The intermediate speed of interpolation.
- L31 _public member_ `bool bUseFixedStep = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interpolation", meta=(ExposeOnSpawn=true))` — Whether to use fixed-step evaluation.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/ValueInterpolators/IIRValueInterpolator.h` (Public)


#### class `UIIRValueInterpolator`  
`class UIIRValueInterpolator : public UCameraValueInterpolator`  
_L15-30_
- reflection: `UCLASS(meta=(DisplayName="IIR"))`
- inherits: `UCameraValueInterpolator`
- desc: Infinite impulse response filter interpolator.
- L25 _public member_ `float Speed = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interpolation", meta=(ExposeOnSpawn=true))` — The speed of interpolation.
- L29 _public member_ `bool bUseFixedStep = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interpolation", meta=(ExposeOnSpawn=true))` — Whether to use fixed-step evaluation.

#### struct `UE::Cameras::TIIRValueInterpolatorTraits`  
`template<typename ValueType> struct TIIRValueInterpolatorTraits`  
_L36-37_
- L154 _public function_ `static double InterpTo(double CurrentValue, double TargetValue, float DeltaTime, double Speed)`
- L163 _public function_ `static FVector2d InterpTo(FVector2d CurrentValue, FVector2d TargetValue, float DeltaTime, double Speed)`
- L172 _public function_ `static FVector3d InterpTo(FVector3d CurrentValue, FVector3d TargetValue, float DeltaTime, double Speed)`
- L181 _public function_ `static FRotator InterpTo(FRotator CurrentValue, FRotator TargetValue, float DeltaTime, double Speed)`
- L190 _public function_ `static FQuat InterpTo(FQuat CurrentValue, FQuat TargetValue, float DeltaTime, double Speed)`

#### class `UE::Cameras::TIIRValueInterpolator`  
`template<typename ValueType> class TIIRValueInterpolator : public TCameraValueInterpolator<ValueType>`  
_L45-149_
- inherits: `TCameraValueInterpolator<ValueType>`
- desc: The actual evaluation code for the IIR interpolator. Exposed here in this header because it's also re-used in the double-IIR interpolator. Most of the code here courtesy of Jeff Farris.
- L49 _public function_ `TIIRValueInterpolator(const UIIRValueInterpolator* InParameters) : TCameraValueInterpolator<ValueType>(nullptr) , Speed(InParameters->Speed) , bUseFixedStep(InParameters->bUseFixedStep)`
- L55 _public function_ `TIIRValueInterpolator(float InSpeed, bool bInUseFixedStep) : TCameraValueInterpolator<ValueType>(nullptr) , Speed(InSpeed) , bUseFixedStep(bInUseFixedStep)`
- L63 _protected typedef_ `using ValueTypeParam = typename TCameraValueInterpolator<ValueType>::ValueTypeParam;`
- L65 _protected function_ `virtual void OnReset(ValueTypeParam OldCurrentValue, ValueTypeParam OldTargetValue) override`
- L72 _protected function_ `virtual void OnRun(const FCameraValueInterpolationParams& Params, FCameraValueInterpolationResult& OutResult) override`
- L124 _protected function_ `virtual void OnSerialize(const FCameraValueInterpolatorSerializeParams& Params, FArchive& Ar) override`
- L134 _private function_ `ValueType RunSubstep(ValueType SubstepTargetValue, float SubstepDeltaTime)`
- L141 _private member_ `static constexpr float MaxSubstepTime = 1.f / 120.f;`
- L143 _private member_ `ValueType ValueAfterLastFullStep;`
- L144 _private member_ `ValueType LastTargetValue;`
- L145 _private member_ `float LastUpdateLeftoverTime = 0.f;`
- L146 _private member_ `float Speed = 1.0;`
- L147 _private member_ `bool bDoLeftoverRewind = true;`
- L148 _private member_ `bool bUseFixedStep = false;`

#### struct `UE::Cameras::TIIRValueInterpolatorTraits`  
`template<> struct TIIRValueInterpolatorTraits<double>`  
_L152-158_
- L154 _public function_ `static double InterpTo(double CurrentValue, double TargetValue, float DeltaTime, double Speed)`
- L163 _public function_ `static FVector2d InterpTo(FVector2d CurrentValue, FVector2d TargetValue, float DeltaTime, double Speed)`
- L172 _public function_ `static FVector3d InterpTo(FVector3d CurrentValue, FVector3d TargetValue, float DeltaTime, double Speed)`
- L181 _public function_ `static FRotator InterpTo(FRotator CurrentValue, FRotator TargetValue, float DeltaTime, double Speed)`
- L190 _public function_ `static FQuat InterpTo(FQuat CurrentValue, FQuat TargetValue, float DeltaTime, double Speed)`

#### struct `UE::Cameras::TIIRValueInterpolatorTraits`  
`template<> struct TIIRValueInterpolatorTraits<FVector2d>`  
_L161-167_
- L154 _public function_ `static double InterpTo(double CurrentValue, double TargetValue, float DeltaTime, double Speed)`
- L163 _public function_ `static FVector2d InterpTo(FVector2d CurrentValue, FVector2d TargetValue, float DeltaTime, double Speed)`
- L172 _public function_ `static FVector3d InterpTo(FVector3d CurrentValue, FVector3d TargetValue, float DeltaTime, double Speed)`
- L181 _public function_ `static FRotator InterpTo(FRotator CurrentValue, FRotator TargetValue, float DeltaTime, double Speed)`
- L190 _public function_ `static FQuat InterpTo(FQuat CurrentValue, FQuat TargetValue, float DeltaTime, double Speed)`

#### struct `UE::Cameras::TIIRValueInterpolatorTraits`  
`template<> struct TIIRValueInterpolatorTraits<FVector3d>`  
_L170-176_
- L154 _public function_ `static double InterpTo(double CurrentValue, double TargetValue, float DeltaTime, double Speed)`
- L163 _public function_ `static FVector2d InterpTo(FVector2d CurrentValue, FVector2d TargetValue, float DeltaTime, double Speed)`
- L172 _public function_ `static FVector3d InterpTo(FVector3d CurrentValue, FVector3d TargetValue, float DeltaTime, double Speed)`
- L181 _public function_ `static FRotator InterpTo(FRotator CurrentValue, FRotator TargetValue, float DeltaTime, double Speed)`
- L190 _public function_ `static FQuat InterpTo(FQuat CurrentValue, FQuat TargetValue, float DeltaTime, double Speed)`

#### struct `UE::Cameras::TIIRValueInterpolatorTraits`  
`template<> struct TIIRValueInterpolatorTraits<FRotator>`  
_L179-185_
- L154 _public function_ `static double InterpTo(double CurrentValue, double TargetValue, float DeltaTime, double Speed)`
- L163 _public function_ `static FVector2d InterpTo(FVector2d CurrentValue, FVector2d TargetValue, float DeltaTime, double Speed)`
- L172 _public function_ `static FVector3d InterpTo(FVector3d CurrentValue, FVector3d TargetValue, float DeltaTime, double Speed)`
- L181 _public function_ `static FRotator InterpTo(FRotator CurrentValue, FRotator TargetValue, float DeltaTime, double Speed)`
- L190 _public function_ `static FQuat InterpTo(FQuat CurrentValue, FQuat TargetValue, float DeltaTime, double Speed)`

#### struct `UE::Cameras::TIIRValueInterpolatorTraits`  
`template<> struct TIIRValueInterpolatorTraits<FQuat>`  
_L188-194_
- L154 _public function_ `static double InterpTo(double CurrentValue, double TargetValue, float DeltaTime, double Speed)`
- L163 _public function_ `static FVector2d InterpTo(FVector2d CurrentValue, FVector2d TargetValue, float DeltaTime, double Speed)`
- L172 _public function_ `static FVector3d InterpTo(FVector3d CurrentValue, FVector3d TargetValue, float DeltaTime, double Speed)`
- L181 _public function_ `static FRotator InterpTo(FRotator CurrentValue, FRotator TargetValue, float DeltaTime, double Speed)`
- L190 _public function_ `static FQuat InterpTo(FQuat CurrentValue, FQuat TargetValue, float DeltaTime, double Speed)`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Cameras` (scope `UE`)
