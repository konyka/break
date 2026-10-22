# Plugins / AvalancheTransition

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition`
- headers: 44; symbols: 456
- symbol kinds: class=22, delegate=1, enum=11, enumerator=33, function=47, macro=3, member=87, namespace=6, prototype=202, struct=35, typedef=9
- PrivateDependencyModuleNames: StateTreeEditorModule, UnrealEd
- PublicDependencyModuleNames: AvalancheTag, Core, CoreUObject, Engine, StateTreeModule

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/AvaTransitionModule.h` (Private)


#### class `FAvaTransitionModule`  
`class FAvaTransitionModule : public IAvaTransitionModule`  
_L10-28_
- inherits: `IAvaTransitionModule`
- L13 _private prototype_ `virtual void StartupModule() override;`
- L14 _private prototype_ `virtual void ShutdownModule() override;`
- L18 _private prototype_ `virtual FOnValidateTransitionTree& GetOnValidateTransitionTree() override;`
- L21 _private prototype_ `void PostEngineInit();`
- L23 _private member_ `TSharedPtr<FAvaTransitionSceneViewExtension> TransitionSceneViewExtension;`
- L25 _private member_ `FOnValidateTransitionTree OnValidateStateTree;`
- L27 _private member_ `FDelegateHandle OnPostEngineInitHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/Behavior/AvaTransitionBehaviorActor.h` (Private)


#### class `AAvaTransitionBehaviorActor`  
`class AAvaTransitionBehaviorActor : public AActor, public IAvaTransitionBehavior`  
_L18-89_
- reflection: `UCLASS(NotPlaceable, Hidden, DisplayName = "Motion Design Transition Behavior Actor")`
- inherits: `AActor,IAvaTransitionBehavior`
- L23 _public prototype_ `AAvaTransitionBehaviorActor();`
- L27 _protected function_ `virtual UObject& AsUObject() override`
- L28 _protected prototype_ `virtual UAvaTransitionTree* GetTransitionTree() const override;`
- L29 _protected prototype_ `virtual FAvaTagHandle GetTransitionLayer() const override;`
- L30 _protected prototype_ `virtual void SetTransitionLayer(FAvaTagHandle InTransitionLayer) override;`
- L31 _protected prototype_ `virtual bool IsEnabled() const override;`
- L32 _protected prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L33 _protected prototype_ `virtual EAvaTransitionInstancingMode GetInstancingMode() const override;`
- L34 _protected prototype_ `virtual void SetInstancingMode(EAvaTransitionInstancingMode InInstancingMode) override;`
- L35 _protected prototype_ `virtual const FStateTreeReference& GetStateTreeReference() const override;`
- L37 _protected prototype_ `virtual void ForEachDetailsEditableProperty(TFunctionRef<void(const FPropertyContext&)> InFunc) const override;`
- L42 _protected prototype_ `virtual void PostActorCreated() override;`
- L44 _protected function_ `virtual bool IsSelectable() const override`
- L45 _protected function_ `virtual bool SupportsExternalPackaging() const override`
- L50 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L51 _protected prototype_ `virtual void PostLoad() override;`
- L53 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L54 _protected prototype_ `virtual void PostEditImport() override;`
- L55 _protected prototype_ `virtual void PostEditUndo() override;`
- L60 _protected prototype_ `void UpdateStateTreeReference();` — Updates the underlying state tree reference, setting it to TransitionTree if null.
- L63 _protected prototype_ `bool IsTransitionTreeOverridden() const;` — Determines whether the transition tree to use in transition logic is the overridden tree instead of the owned one
- L66 _private prototype_ `UAvaTransitionSubsystem* GetTransitionSubsystem() const;`
- L68 _private prototype_ `void ValidateTransitionTree();`
- L71 _private member_ `TObjectPtr<UAvaTransitionTree> TransitionTree;` — `UPROPERTY()`
- L74 _private member_ `mutable FStateTreeReference StateTreeReference;` — `UPROPERTY(EditAnywhere, Category="Transition Logic", DisplayName = "Transition Tree", meta=(Schema="/Script/AvalancheTransition.AvaTransitionTreeSchema"))`
- L78 _private member_ `FAvaTagHandle TransitionLayer;` — `UPROPERTY(EditAnywhere, Category="Transition Logic")` — Transition Layer to use
- L81 _private member_ `EAvaTransitionInstancingMode InstancingMode = EAvaTransitionInstancingMode::New;` — `UPROPERTY(EditAnywhere, Category="Transition Logic")`
- L88 _private member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, Category="Transition Logic", meta=(DisplayPriority=0))` — Determines whether this Transition Logic is enabled. Can be overriden by a Transition Instance to force the logic to run regardless

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/Execution/AvaTransitionExecutionContext.h` (Private)


#### struct `FAvaTransitionExecutionExtension`  
`struct FAvaTransitionExecutionExtension : public FStateTreeExecutionExtension`  
_L12-20_
- reflection: `USTRUCT()`
- inherits: `FStateTreeExecutionExtension`
- L16 _public prototype_ `virtual FString GetInstanceDescription(const FContextParameters& Context) const override;`
- L19 _public member_ `FString SceneDescription;` — `UPROPERTY()`

#### struct `FAvaTransitionExecutionContext`  
`struct FAvaTransitionExecutionContext : FStateTreeExecutionContext`  
_L22-36_
- inherits: `FStateTreeExecutionContext`
- L24 _public prototype_ `FAvaTransitionExecutionContext(const FAvaTransitionBehaviorInstance& InBehaviorInstance, UObject& InOwner, const UStateTree& InStateTree, FStateTreeInstanceData& InInstanceData);`
- L27 _public prototype_ `EStateTreeRunStatus Start(const FInstancedPropertyBag* InitialParameters);` — Start executing.
- L29 _public function_ `const FAvaTransitionBehaviorInstance* GetBehaviorInstance() const`
- L35 _private member_ `const FAvaTransitionBehaviorInstance& BehaviorInstance;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/Execution/AvaTransitionExecutor.h` (Private)


#### class `FAvaTransitionExecutor`  
`class FAvaTransitionExecutor : public IAvaTransitionExecutor, public FTickableGameObject, public FGCObject`  
_L19-74_
- inherits: `IAvaTransitionExecutor,FTickableGameObject,FGCObject`
- desc: Base Implementation of an Executor dealing with multiple behaviors going out (Exit Instances) and multiple behaviors going in (Enter Instances)
- L22 _public prototype_ `explicit FAvaTransitionExecutor(FAvaTransitionExecutorBuilder& InBuilder);`
- L26 _public prototype_ `bool IsRunning() const;`
- L29 _protected prototype_ `void Setup();`
- L32 _protected prototype_ `void DetermineTickWorld();` — Gets the world to tick with from the behavior instances
- L35 _protected prototype_ `virtual TArray<const FAvaTransitionBehaviorInstance*> GetBehaviorInstances(const FAvaTransitionLayerComparator& InComparator) const;`
- L36 _protected prototype_ `virtual void ForEachBehaviorInstance(TFunctionRef<void(const FAvaTransitionBehaviorInstance&)> InCallable) const override;`
- L37 _protected prototype_ `virtual void Start() override;`
- L38 _protected prototype_ `virtual void Stop() override;`
- L42 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L43 _protected prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L44 _protected prototype_ `virtual bool IsTickable() const override;`
- L45 _protected function_ `virtual bool IsTickableInEditor() const override`
- L46 _protected function_ `virtual ETickableTickType GetTickableTickType() const override`
- L47 _protected prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L51 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L52 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L56 _private prototype_ `void ForEachInstance(TFunctionRef<void(FAvaTransitionBehaviorInstance&)> InFunc);`
- L57 _private prototype_ `void ForEachInstance(TFunctionRef<void(const FAvaTransitionBehaviorInstance&)> InFunc) const;`
- L59 _private prototype_ `void ConditionallyFinishBehaviors();`
- L65 _private member_ `TWeakObjectPtr<UWorld> WorldWeak;` — First valid world context found. The transition will tick with this World Tick if valid.
- L67 _private member_ `TArray<FAvaTransitionBehaviorInstance> Instances;`
- L69 _private member_ `const FAvaTransitionBehaviorInstance NullInstance;`
- L71 _private member_ `FString ContextName;`
- L73 _private member_ `FSimpleDelegate OnFinished;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/Preview/AvaTransitionPreviewLevelState.h` (Private)


#### struct `FAvaTransitionPreviewLevelState`  
`struct FAvaTransitionPreviewLevelState`  
_L12-28_
- reflection: `USTRUCT()`
- L17 _public member_ `TObjectPtr<ULevelStreaming> LevelStreaming;` — `UPROPERTY()`
- L20 _public member_ `bool bEnableOverrideTransitionLayer = false;` — `UPROPERTY()`
- L23 _public member_ `FAvaTagHandle OverrideTransitionLayer;` — `UPROPERTY()`
- L27 _public member_ `bool bShouldUnload = false;` — `UPROPERTY()` — Indication of whether this Level should be unloaded after finishing transition

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/Preview/AvaTransitionPreviewManager.h` (Private)


#### class `AAvaTransitionPreviewManager`  
`class AAvaTransitionPreviewManager : public AActor`  
_L25-87_
- reflection: `UCLASS(NotBlueprintable, DisplayName = "Motion Design Transition Preview Manager")`
- inherits: `AActor`
- desc: Actor to preview out Transition Logic via Simple Level Instance Loading and Unloading The Level Instance Loading/Unloading is not set to be
- L30 _public prototype_ `AAvaTransitionPreviewManager();`
- L33 _public prototype_ `void TakeNext();` — `UFUNCTION(CallInEditor, Category="Transition Logic Preview")`
- L36 _public prototype_ `void TakeOut();` — `UFUNCTION(CallInEditor, Category="Transition Logic Preview")`
- L39 _public prototype_ `void TransitionStop();` — `UFUNCTION(CallInEditor, Category="Transition Logic Preview")`
- L42 _private prototype_ `ULevelStreamingDynamic::FLoadLevelInstanceParams MakeLevelInstanceParams() const;`
- L44 _private prototype_ `const FAvaTransitionPreviewLevelState* FindExistingLevelStateForNextLevel() const;`
- L46 _private prototype_ `bool TryReuseLevel();`
- L48 _private prototype_ `static IAvaTransitionBehavior* GetBehavior(ULevelStreaming* InLevelStreaming, const UAvaTransitionSubsystem& InTransitionSubsystem);`
- L50 _private prototype_ `UAvaTransitionSubsystem* GetTransitionSubsystem() const;`
- L52 _private prototype_ `void StartTransition();`
- L54 _private prototype_ `void OnTransitionEnded();`
- L56 _private prototype_ `void OnLevelStreamingStateChanged(UWorld* InWorld , const ULevelStreaming* InLevelStreaming , ULevel* InLevelIfLoaded , ELevelStreamingState InPreviousState , ELevelStreamingState InNewState);`
- L62 _private prototype_ `void UnloadDiscardedLevels();`
- L64 _private prototype_ `void UnloadLevelStreamingInstances(TConstArrayView<ULevelStreaming*> InInstancesToUnload);`
- L67 _private prototype_ `bool ShouldResetTransactionBuffer(TConstArrayView<ULevelStreaming*> InInstancesToUnload) const;`
- L71 _private member_ `TArray<FAvaTransitionPreviewLevelState> LevelStates;` — `UPROPERTY(Transient)`
- L74 _private member_ `bool bTransitionInProgress = false;` — `UPROPERTY(Transient, VisibleAnywhere, Category="Transition Logic Preview")`
- L77 _private member_ `bool bReuseLevel = false;` — `UPROPERTY(Transient, EditAnywhere, Category="Transition Logic Preview", meta=(EditCondition="!bTransitionInProgress"))`
- L81 _private member_ `TSoftObjectPtr<UWorld> NextLevelAsset;` — `UPROPERTY(Transient, EditAnywhere, DisplayName = "Next Level", Category="Transition Logic Preview", meta=(EditCondition="!bTransitionInProgress"))` — The Next Level to Transition to the Scene
- L84 _private member_ `FAvaTransitionPreviewLevelState NextLevelState;` — `UPROPERTY(Transient)`
- L86 _private member_ `TSharedPtr<IAvaTransitionExecutor> TransitionExecutor;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/Preview/AvaTransitionPreviewScene.h` (Private)


#### struct `FAvaTransitionPreviewScene`  
`struct FAvaTransitionPreviewScene : public FAvaTransitionScene`  
_L16-32_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionScene`
- L20 _public prototype_ `FAvaTransitionPreviewScene() = default;`
- L22 _public prototype_ `explicit FAvaTransitionPreviewScene(FAvaTransitionPreviewLevelState* InLevelState);`
- L25 _public prototype_ `virtual EAvaTransitionComparisonResult Compare(const FAvaTransitionScene& InOther) const override;`
- L26 _public prototype_ `virtual ULevel* GetLevel() const override;`
- L27 _public prototype_ `virtual void GetOverrideTransitionLayer(FAvaTagHandle& OutTransitionLayer) const override;`
- L28 _public prototype_ `virtual void OnFlagsChanged() override;`
- L31 _public member_ `TOptional<FAvaTagHandle> OverrideTransitionLayer;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Private/Rendering/AvaTransitionSceneViewExtension.h` (Private)


#### class `FAvaTransitionSceneViewExtension`  
`class FAvaTransitionSceneViewExtension : public FSceneViewExtensionBase`  
_L7-18_
- inherits: `FSceneViewExtensionBase`
- L10 _public function_ `FAvaTransitionSceneViewExtension(const FAutoRegister& InAutoRegister) : FSceneViewExtensionBase(InAutoRegister)`
- L16 _public prototype_ `void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionContext.h` (Public)


#### struct `FAvaTransitionContext`  
`struct FAvaTransitionContext`  
_L17-53_
- reflection: `USTRUCT()`
- desc: A Transition Context is composed of a Transitioning Scene Instance, an indication whether this is an In or an Out Transition, and in which Layer this Transition is taking place
- L21 _public function_ `const FAvaTransitionScene* GetTransitionScene() const`
- L26 _public function_ `FAvaTransitionScene* GetTransitionScene()`
- L31 _public function_ `EAvaTransitionType GetTransitionType() const`
- L36 _public function_ `FAvaTagHandle GetTransitionLayer() const`
- L46 _private member_ `FInstancedStruct TransitionScene;` — `UPROPERTY()` — Instance Struct of the Transition Scene
- L49 _private member_ `FAvaTagHandle TransitionLayer;` — `UPROPERTY()`
- L52 _private member_ `EAvaTransitionType TransitionType = EAvaTransitionType::In;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionDefaultLayerTags.h` (Public)


#### class `UE::AvaTransition::FDefaultTags`  
`class FDefaultTags`  
_L10-19_
- L12 _private prototype_ `FDefaultTags();`
- L15 _public prototype_ `static const FDefaultTags& Get();`
- L18 _public member_ `FAvaTagSoftHandle DefaultLayer;` — Soft handle to the default layer tag

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaTransition` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionEnums.h` (Public)


#### enum `EAvaTransitionSceneFlags`  
`enum class EAvaTransitionSceneFlags : uint8`  
_L7-11_
- L9 _public enumerator_ `None = 0`
- L10 _public enumerator_ `NeedsDiscard = 1 << 0` — Flag indicating that the Scene needs to be discarded at the end of the Transition

#### enum `EAvaTransitionIterationResult`  
`enum class EAvaTransitionIterationResult : uint8`  
_L14-18_
- L16 _public enumerator_ `Break`
- L17 _public enumerator_ `Continue`

#### enum `EAvaTransitionType`  
`enum class EAvaTransitionType : uint8`  
_L21-27_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Type")`
- L23 _public enumerator_ `None = 0 UMETA(Hidden)`
- L24 _public enumerator_ `In = 1 << 0`
- L25 _public enumerator_ `Out = 1 << 1`
- L26 _public enumerator_ `MAX UMETA(Hidden)`

#### enum `EAvaTransitionTypeFilter`  
`enum class EAvaTransitionTypeFilter : uint8`  
_L31-36_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Filter Type")`
- L33 _public enumerator_ `In`
- L34 _public enumerator_ `Out`
- L35 _public enumerator_ `Any`

#### enum `EAvaTransitionRunState`  
`enum class EAvaTransitionRunState : uint8`  
_L39-44_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Run State")`
- L41 _public enumerator_ `Unknown UMETA(Hidden)`
- L42 _public enumerator_ `Running`
- L43 _public enumerator_ `Finished`

#### enum `EAvaTransitionComparisonResult`  
`enum class EAvaTransitionComparisonResult : uint8`  
_L47-52_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Comparison Result")`
- L49 _public enumerator_ `None`
- L50 _public enumerator_ `Different`
- L51 _public enumerator_ `Same`

#### enum `EAvaTransitionSceneType`  
`enum class EAvaTransitionSceneType : uint8`  
_L55-59_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Scene Type")`
- L57 _public enumerator_ `This`
- L58 _public enumerator_ `Other`

#### enum `EAvaTransitionLayerCompareType`  
`enum class EAvaTransitionLayerCompareType : uint8`  
_L62-69_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Layer Compare Type")`
- L64 _public enumerator_ `None UMETA(Hidden)`
- L65 _public enumerator_ `Same`
- L66 _public enumerator_ `Different UMETA(DisplayName="Other")`
- L67 _public enumerator_ `MatchingTag UMETA(DisplayName="Specific Layers")`
- L68 _public enumerator_ `Any`

#### enum `EAvaTransitionInstancingMode`  
`enum class EAvaTransitionInstancingMode : uint8`  
_L72-78_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Instancing Mode")`
- L75 _public enumerator_ `New` — A new scene instance is added to the parent world and exit instance is discarded.
- L77 _public enumerator_ `Reuse` — If previous instance exists, reuse it for the entering behavior.

#### enum `EAvaTransitionLevelHideMode`  
`enum class EAvaTransitionLevelHideMode : uint8`  
_L81-91_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Transition Level Hide Mode")`
- L84 _public enumerator_ `NoHide` — Do not hide the Actors of the Level
- L87 _public enumerator_ `HideUnlessReuse` — Hide the Level's Actors unless it's a Level that is re-used
- L90 _public enumerator_ `AlwaysHide` — Always hide the Level's Actors even if it's re-used

#### Free symbols / members of external scopes

- L12 _prototype_ `ENUM_CLASS_FLAGS(EAvaTransitionSceneFlags);`
- L28 _prototype_ `ENUM_CLASS_FLAGS(EAvaTransitionType);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionLayer.h` (Public)


#### struct `FAvaTransitionLayerComparator`  
`struct FAvaTransitionLayerComparator`  
_L13-26_
- L15 _public prototype_ `bool Compare(const FAvaTagHandle& InLayer) const;`
- L17 _public prototype_ `bool Compare(const FAvaTransitionBehaviorInstance& InInstance) const;`
- L19 _public member_ `FAvaTagHandleContainer LayerContext;`
- L22 _public member_ `const FAvaTransitionContext* ExcludedContext = nullptr;` — Optional pointer to the Transition Context to exclude from the Comparison
- L25 _public member_ `EAvaTransitionLayerCompareType LayerCompareType = EAvaTransitionLayerCompareType::Same;` — The type of comparison to perform

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionLayerUtils.h` (Public)


#### struct `FAvaTransitionLayerUtils`  
`struct FAvaTransitionLayerUtils`  
_L19-40_
- L22 _public prototype_ `static TArray<const FAvaTransitionBehaviorInstance*> QueryBehaviorInstances(UAvaTransitionSubsystem& InTransitionSubsystem, const FAvaTransitionLayerComparator& InComparator);` — Gets all the Behavior Instances that match the Comparator
- L25 _public prototype_ `static FAvaTransitionLayerComparator BuildComparator(const FAvaTransitionContext& InTransitionContext, EAvaTransitionLayerCompareType InCompareType, const FAvaTagHandle& InSpecificLayer);` — Builds a Comparator for the given Context (and optionally Layer), excluding the provided Transition Context (assumes it's the transition context calling this)
- L28 _public prototype_ `static FAvaTransitionLayerComparator BuildComparator(const FAvaTransitionContext& InTransitionContext, EAvaTransitionLayerCompareType InCompareType, const FAvaTagHandleContainer& InSpecificLayers);` — Builds a Comparator for the given Context and specific layers, excluding the provided Transition Context (assumes it's the transition context calling this)
- L38 _public prototype_ `static FText GetLayerQueryText(FLayerQueryTextParams&& InParams, const FGuid& InId, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting);`

#### struct `FAvaTransitionLayerUtils::FLayerQueryTextParams`  
`struct FLayerQueryTextParams`  
_L31-37_
- L33 _public member_ `EAvaTransitionLayerCompareType LayerType;`
- L34 _public member_ `FName SpecificLayerName;`
- L35 _public member_ `FName LayerTypePropertyName;`
- L36 _public member_ `FName SpecificLayerPropertyName;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionLibrary.h` (Public)


#### class `UAvaTransitionLibrary`  
`class UAvaTransitionLibrary : public UBlueprintFunctionLibrary`  
_L17-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L23 _public prototype_ `static const FAvaTransitionContext* GetTransitionContext(UObject* InContextObject);` — Retrieves the transition context from
- L37 _public prototype_ `static bool IsTransitionActiveInLayers(UObject* InContextObject , EAvaTransitionLayerCompareType InLayerComparisonType , const FAvaTagHandleContainer& InSpecificLayers , EAvaTransitionTypeFilter InTransitionTypeFilter = EAvaTransitionTypeFilter::Any);` — `UFUNCTION(BlueprintPure, Category="Transition Logic", meta=(DefaultToSelf="InContextObject"))` — Determines whether a transition is currently taking place at a given layer @param InContextObject the context to retrieve the active transition relating to the context. @param InLayerComparisonType the type of layer to filter. "Same": the same layer as this context's. "Other": a layer different from this context's. "Specific Layers": layers specified by "InSpecificLayers". "Any": any layer found. @param InSpecificLayers the specific layers to filter. InLayerComparisonType should be set to "Specific Layers" for this to be considered. @param InTransitionTypeFilter the transition type to filter (whether it should only consider Ins or Outs, or any type is allowed)
- L44 _public prototype_ `static bool IsTransitionActiveInLayer(UObject* InContextObject , EAvaTransitionComparisonResult InSceneComparisonType , EAvaTransitionLayerCompareType InLayerComparisonType , const FAvaTagHandleContainer& InSpecificLayers);` — `UE_DEPRECATED(5.7, "Use IsTransitionActiveInLayers instead")` — `UFUNCTION(BlueprintPure, Category="Transition Logic", meta=(DefaultToSelf="InContextObject", DeprecatedFunction, DeprecationMessage="Use \"IsTransitionActiveInLayers\" instead"))`
- L51 _public prototype_ `static EAvaTransitionType GetTransitionType(UObject* InContextObject);` — `UFUNCTION(BlueprintPure, Category="Transition Logic", meta=(DefaultToSelf="InContextObject"))` — Returns the transition type of the current transition taking place if any
- L62 _public prototype_ `static bool AreScenesTransitioning(UObject* InContextObject , const FAvaTagHandleContainer& InLayers , const TArray<TSoftObjectPtr<UWorld>>& InScenesToIgnore);` — `UFUNCTION(BlueprintPure, Category="Transition Logic", meta=(DefaultToSelf="InContextObject"))` — Determines whether there are scenes/levels (other than the one from this context) transitioning. Note: this ignores scenes that are transitioning out and to be discarded. @param InContextObject the context to retrieve the active transition relating to the context. @param InLayers the layers to consider @param InScenesToIgnore the world assets to ignore @return true if the given layers have assets that are involved in a transition.
- L70 _public prototype_ `static TScriptInterface<IAvaTransitionBehavior> GetTransitionBehavior(UObject* InContextObject);` — `UFUNCTION(BlueprintPure, Category="Transition Logic", meta=(DefaultToSelf="InContextObject"))` — Retrieves the transition behavior from this context
- L76 _public prototype_ `static const UAvaTransitionTree* GetTransitionTree(UObject* InContextObject);` — `UFUNCTION(BlueprintPure, Category="Transition Logic", meta=(DefaultToSelf="InContextObject"))` — Retrieves the transition tree from this context

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHETRANSITION_API`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaTransition, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionNode.h` (Public)


#### class `FAvaTransitionNode`  
`class FAvaTransitionNode`  
_L11-19_
- L14 _public prototype_ `bool LinkNode(FStateTreeLinker& InLinker);`
- L16 _public member_ `TStateTreeExternalDataHandle<FAvaTransitionContext> TransitionContextHandle;`
- L18 _public member_ `TStateTreeExternalDataHandle<UAvaTransitionSubsystem> TransitionSubsystemHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionScene.h` (Public)


#### struct `FAvaTransitionSceneOwner`  
`struct FAvaTransitionSceneOwner`  
_L18-76_
- desc: Owner of the Scene Instance. Used to determine whether a Scene Instance is valid or not.
- L20 _public function_ `FAvaTransitionSceneOwner()`
- L25 _public function_ `FAvaTransitionSceneOwner(UObject* InSceneOwner)`
- L31 _public function_ `template<typename T, ESPMode InMode> FAvaTransitionSceneOwner(TWeakPtr<T, InMode> InSceneOwner)`
- L37 _public function_ `template<typename T, ESPMode InMode> FAvaTransitionSceneOwner(TSharedPtr<T, InMode> InSceneOwner)`
- L43 _public function_ `template<typename T, ESPMode InMode> FAvaTransitionSceneOwner(TSharedRef<T, InMode> InSceneOwner)`
- L48 _public function_ `bool operator()(bool InSceneOwner) const`
- L53 _public function_ `bool operator()(const FWeakObjectPtr& InSceneOwner) const`
- L59 _public function_ `template<ESPMode InMode> bool operator()(const TWeakPtr<void, InMode>& InSceneOwner) const`
- L64 _public function_ `bool IsValid() const`
- L75 _private member_ `> SceneOwner;`

#### struct `FAvaTransitionScene`  
`struct FAvaTransitionScene`  
_L111-176_
- reflection: `USTRUCT()`
- desc: A Transition Scene is a representation of what is transitioning in or out. It's validity is bound to the validity of the scene owner because it does not own the data passed to it (i.e. it holds a data view), and so cannot be used without ensuring (through the scene owner) that the scene data is still valid It can be used to represent a page or, more directly, a level streaming object. For example, an implementation could look something like this: USTRUCT() struct FSceneData { GENERATED_BODY() ... }; USTRUCT() struct FMyTransitionScene : public FAvaTransitionScene { GENERATED_BODY() FMyTransitionScene(FSceneData* InData) : FAvaTransitionScene(InData) { } virtual EAvaTransitionComparisonResult Compare(const FAvaTransitionScene& InOther) override { const FSceneData& MySceneData    = GetDataView.Get<FSceneData>(); const FSceneData* OtherSceneData = InOther.GetDataView().GetPtr<FSceneData>(); ... } };
- L115 _public prototype_ `FAvaTransitionScene() = default;`
- L117 _public prototype_ `virtual ~FAvaTransitionScene() = default;`
- L121 _public function_ `template<typename InStructType> requires (!std::is_const_v<InStructType> && TModels_V<CStaticStructProvider, InStructType>) explicit FAvaTransitionScene(InStructType* InStruct) : DataView(InStructType::StaticStruct(), reinterpret_cast<uint8*>(InStruct))`
- L126 _public prototype_ `explicit FAvaTransitionScene(FStateTreeDataView InDataView);`
- L129 _public prototype_ `virtual EAvaTransitionComparisonResult Compare(const FAvaTransitionScene& InOther) const;` — Determines whether this Transition Scene is the same as another
- L132 _public prototype_ `virtual ULevel* GetLevel() const;` — Retrieves the underling Level of the Scene
- L135 _public function_ `virtual void GetOverrideTransitionLayer(FAvaTagHandle& OutTransitionLayer) const` — Optional override of Transition Layer
- L138 _public function_ `virtual void OnFlagsChanged()` — Called when flags have been added / removed
- L141 _public function_ `virtual void UpdateSceneDescription(FString& InOutDescription) const` — Optional override for the passed in Scene Description
- L143 _public prototype_ `void SetFlags(EAvaTransitionSceneFlags InFlags);`
- L145 _public prototype_ `bool HasAnyFlags(EAvaTransitionSceneFlags InFlags) const;`
- L147 _public prototype_ `bool HasAllFlags(EAvaTransitionSceneFlags InFlags) const;`
- L149 _public prototype_ `const FStateTreeDataView& GetDataView() const;`
- L152 _public function_ `template<typename InExtensionType UE_REQUIRES(IAvaTransitionExtension::TIsValidExtension_V<InExtensionType>)> InExtensionType* FindExtension() const`
- L163 _protected function_ `template<typename InExtensionType UE_REQUIRES(IAvaTransitionExtension::TIsValidExtension_V<InExtensionType>)> InExtensionType& AddExtension()`
- L171 _private member_ `FStateTreeDataView DataView;`
- L173 _private member_ `EAvaTransitionSceneFlags Flags = EAvaTransitionSceneFlags::None;`
- L175 _private member_ `TMap<FName, TSharedRef<IAvaTransitionExtension>> Extensions;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionSubsystem.h` (Public)


#### class `UAvaTransitionSubsystem`  
`class UAvaTransitionSubsystem : public UWorldSubsystem`  
_L23-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L28 _public prototype_ `void RegisterTransitionBehavior(const ULevel* InLevel, IAvaTransitionBehavior* InBehavior);`
- L35 _public prototype_ `IAvaTransitionBehavior* GetOrCreateTransitionBehavior(ULevel* InLevel = nullptr);` — Gets or Creates a Transition Behavior for the given Level in this Subsystem's World @param InLevel the level to get or create the transition behavior. if null, will default to the persistent level of the world @return the behavior for the provided level
- L42 _public prototype_ `IAvaTransitionBehavior* GetTransitionBehavior(const ULevel* InLevel = nullptr) const;` — Gets the Transition Behavior for the given Level in this Subsystem's World @param InLevel the level containing the transition behavior. if null, will default to the persistent level of the world @return the behavior for the provided level
- L44 _public prototype_ `static IAvaTransitionBehavior* FindTransitionBehavior(const ULevel* InLevel);`
- L46 _public prototype_ `void RegisterTransitionExecutor(const TSharedRef<IAvaTransitionExecutor>& InExecutor);`
- L52 _public prototype_ `void ForEachTransitionExecutor(TFunctionRef<EAvaTransitionIterationResult(IAvaTransitionExecutor&)> InFunc);` — Executes the provided function for each Registered valid Transition Executor @param InFunc the function to execute for each executor reference with option to break iteration
- L56 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L57 _protected prototype_ `virtual void PostInitialize() override;`
- L61 _private member_ `TMap<TObjectKey<ULevel>, TWeakInterfacePtr<IAvaTransitionBehavior>> TransitionBehaviors;`
- L63 _private member_ `TArray<TWeakPtr<IAvaTransitionExecutor>> TransitionExecutors;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionTree.h` (Public)


#### class `UAvaTransitionTree`  
`class UAvaTransitionTree : public UStateTree`  
_L19-68_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Transition Tree")`
- inherits: `UStateTree`
- desc: Motion Design Transition Tree is a State Tree with the purpose of executing user-defined logic when there's a Transition between multiple scenes in multiple layers.
- L25 _public prototype_ `FAvaTagHandle GetTransitionLayer() const;` — `UE_DEPRECATED(5.8, "GetTransitionLayer deprecated. Use IAvaTransitionBehavior::GetTransitionLayer instead")`
- L28 _public prototype_ `void SetTransitionLayer(FAvaTagHandle InTransitionLayer);` — `UE_DEPRECATED(5.8, "SetTransitionLayer deprecated. Use IAvaTransitionBehavior::SetTransitionLayer instead")`
- L31 _public prototype_ `bool IsEnabled() const;` — `UE_DEPRECATED(5.8, "IsEnabled deprecated. Use IAvaTransitionBehavior::IsEnabled instead")`
- L34 _public prototype_ `void SetEnabled(bool bInEnabled);` — `UE_DEPRECATED(5.8, "SetEnabled deprecated. Use IAvaTransitionBehavior::SetEnabled instead")`
- L37 _public prototype_ `bool ContainsTask(const UScriptStruct* InTaskStruct) const;` — Returns whether a Task of a given type exists and is enabled within an enabled state in the Transition Tree
- L41 _public function_ `template <class InTaskType UE_REQUIRES(std::is_base_of_v<FAvaTransitionTask, InTaskType>)> bool ContainsTask() const` — Returns whether a Task of a given type exists and is enabled within an enabled state in the Transition Tree
- L47 _public prototype_ `void SetInstancingMode(EAvaTransitionInstancingMode InInstancingMode);` — `UE_DEPRECATED(5.8, "SetInstancingMode deprecated. Use IAvaTransitionBehavior::SetInstancingMode instead")`
- L51 _public prototype_ `EAvaTransitionInstancingMode GetInstancingMode() const;` — `UE_DEPRECATED(5.8, "GetInstancingMode deprecated. Use IAvaTransitionBehavior::GetInstancingMode instead")` — `UFUNCTION(BlueprintPure, Category = "Transition Logic", meta=(DeprecatedFunction, DeprecationMessage="Use GetInstancingMode from the Transition Behavior Interface (via GetTransitionBehavior)instead."))`
- L54 _public prototype_ `static FName GetEnabledPropertyName();` — `UE_DEPRECATED(5.8, "GetEnabledPropertyName deprecated. Use enabled via IAvaTransitionBehavior instead")`
- L59 _private member_ `FAvaTagHandle TransitionLayer_DEPRECATED;` — `UE_DEPRECATED(5.8, "TransitionLayer deprecated. Use IAvaTransitionBehavior instead")` — `UPROPERTY()`
- L63 _private member_ `bool bEnabled_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "bEnabled deprecated. Use IAvaTransitionBehavior instead")` — `UPROPERTY()`
- L67 _private member_ `EAvaTransitionInstancingMode InstancingMode_DEPRECATED = EAvaTransitionInstancingMode::New;` — `UE_DEPRECATED(5.8, "InstancingMode deprecated. Use IAvaTransitionBehavior instead")` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AVALANCHETRANSITION_API`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionTreeSchema.h` (Public)


#### class `UAvaTransitionTreeSchema`  
`class UAvaTransitionTreeSchema : public UStateTreeSchema`  
_L10-28_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, HideDropdown, DisplayName="Motion Design Transition Tree Schema")`
- inherits: `UStateTreeSchema`
- L15 _public prototype_ `UAvaTransitionTreeSchema() = default;`
- L19 _protected prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;`
- L20 _protected prototype_ `virtual bool IsClassAllowed(const UClass* InClass) const override;`
- L21 _protected prototype_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override;`
- L23 _protected function_ `virtual bool AllowEnterConditions() const override`
- L24 _protected function_ `virtual bool AllowEvaluators() const override`
- L25 _protected function_ `virtual bool AllowMultipleTasks() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AvaTransition` (scope `UE`)
- L14 _function_ `template<typename InNodeType> static typename InNodeType::FInstanceDataType* TryGetInstanceData(const InNodeType& InNode, FStateTreeDataView InInstanceDataView)` (scope `UE::AvaTransition`) — Safely gets the Instance Data if the Struct type matches or nullptr if there is type mismatch
- L29 _prototype_ `const FAvaTransitionBehaviorInstance* GetBehaviorInstance(const FStateTreeExecutionContext& InExecutionContext);` (scope `UE::AvaTransition`) — Retrieves the Behavior Instance from the Execution Context The Execution Context *must* have originated from Motion Design to return a valid pointer

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/AvaTransitionVersion.h` (Public)


#### struct `UE::AvaTransition::FBehaviorVersion`  
`struct FBehaviorVersion`  
_L13-35_
- desc: Describes the versions of transition behaviors
- L16 _private prototype_ `FBehaviorVersion() = delete;`
- L34 _public member_ `const static FGuid Guid;`

#### enum `UE::AvaTransition::FBehaviorVersion::Type`  
`enum Type : uint8`  
_L19-32_
- L21 _public enumerator_ `PreVersioning = 0`
- L27 _public enumerator_ `InstanceProperties` — Proper location for instance-only properties like Transition Layer. Moved away from UAvaTransitionTree into IAvaTransitionBehavior Transition Trees are designed to be re-usable, so these instance-related properties now live in the Transition Behavior.
- L30 _public enumerator_ `VersionPlusOne`
- L31 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHETRANSITION_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AvaTransition` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Behavior/AvaTransitionBehaviorInstance.h` (Public)


#### struct `FAvaTransitionBehaviorInstance`  
`struct FAvaTransitionBehaviorInstance`  
_L18-104_
- desc: Struct containing Instance Data for a Transition Behavior running or about to run
- L20 _public function_ `FAvaTransitionBehaviorInstance() : TransitionSceneOwner(nullptr)`
- L25 _public prototype_ `FAvaTransitionBehaviorInstance& SetBehavior(IAvaTransitionBehavior* InBehavior);`
- L27 _public prototype_ `bool IsEnabled() const;`
- L31 _public function_ `FAvaTransitionBehaviorInstance& CreateScene(FAvaTransitionSceneOwner InTransitionSceneOwner, InArgTypes&&... InArgs)`
- L40 _public prototype_ `IAvaTransitionBehavior* GetBehavior() const;` — Gets the Behavior this Instance is based on
- L42 _public prototype_ `const UAvaTransitionTree* GetTransitionTree() const;`
- L44 _public prototype_ `FAvaTagHandle GetTransitionLayer() const;`
- L46 _public prototype_ `EAvaTransitionType GetTransitionType() const;`
- L48 _public prototype_ `bool IsRunning() const;`
- L51 _public prototype_ `const FAvaTransitionContext& GetTransitionContext() const;` — Gets the Transition Context of this instance
- L53 _public prototype_ `FAvaTransitionContext& GetTransitionContext();`
- L55 _public prototype_ `FAvaTransitionSceneOwner GetTransitionSceneOwner() const;`
- L57 _public prototype_ `void SetTransitionType(EAvaTransitionType InTransitionType);`
- L59 _public prototype_ `bool Setup();`
- L61 _public prototype_ `void Start();`
- L63 _public prototype_ `void Tick(float InDeltaSeconds);`
- L65 _public prototype_ `void Stop();`
- L67 _public prototype_ `void SetOverrideLayer(const FAvaTagHandle& InOverrideLayer);`
- L69 _public prototype_ `void SetLogContext(const FString& InContext);`
- L71 _public prototype_ `void AddReferencedObjects(FReferenceCollector& InCollector);`
- L75 _private prototype_ `void ConditionallyStop();` — Stops Execution if the Tree is no longer running
- L77 _private prototype_ `bool UpdateContext(TOptional<FAvaTransitionExecutionContext>& OutContext);`
- L79 _private prototype_ `bool ValidateTransitionScene();`
- L81 _private prototype_ `void UpdateTransitionLayers(const IAvaTransitionBehavior* InBehavior);`
- L83 _private prototype_ `bool MakeContext(IAvaTransitionBehavior* InBehavior, TOptional<FAvaTransitionExecutionContext>& OutContext);`
- L86 _private member_ `TWeakInterfacePtr<IAvaTransitionBehavior> BehaviorWeak;` — The Behavior this Instance is based on
- L89 _private member_ `FStateTreeInstanceData InstanceData;` — The Instance Data used when running the State Tree
- L92 _private member_ `FAvaTransitionContext TransitionContext;` — Context information on the current Transition taking place
- L95 _private member_ `FAvaTransitionSceneOwner TransitionSceneOwner;` — The Owner of the Scene Instance. If this Owner is alive, it is assumed that the Scene Instance underlying Struct will also be alive
- L98 _private member_ `EStateTreeRunStatus RunStatus = EStateTreeRunStatus::Unset;` — The current run status of this Instance
- L101 _private member_ `TOptional<FAvaTagHandle> OverrideLayer;` — If not none, this is the Transition Layer that will be set
- L103 _private member_ `FString LogContext;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Behavior/AvaTransitionBehaviorInstanceCache.h` (Public)


#### struct `FAvaTransitionBehaviorInstanceCache`  
`struct FAvaTransitionBehaviorInstanceCache`  
_L12-26_
- L14 _public prototype_ `const FAvaTransitionContext* GetTransitionContext() const;`
- L16 _public prototype_ `IAvaTransitionBehavior* GetTransitionBehavior() const;`
- L18 _public prototype_ `void SetCachedInstanceDataFromContext(const FStateTreeExecutionContext& InExecutionContext);`
- L20 _public prototype_ `void ClearCachedInstanceData();`
- L23 _private member_ `FAvaTransitionSceneOwner CachedSceneOwner;`
- L25 _private member_ `const FAvaTransitionBehaviorInstance* CachedBehaviorInstance = nullptr;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Behavior/IAvaTransitionBehavior.h` (Public)


#### class `UAvaTransitionBehavior`  
`class UAvaTransitionBehavior : public UInterface`  
_L21-24_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IAvaTransitionBehavior`  
`class IAvaTransitionBehavior`  
_L26-68_
- L31 _public prototype_ `virtual UObject& AsUObject() = 0;`
- L34 _public prototype_ `virtual UAvaTransitionTree* GetTransitionTree() const = 0;` — Gets the underlying Transition Tree that this Transition Behavior runs
- L38 _public prototype_ `virtual FAvaTagHandle GetTransitionLayer() const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Transition Logic")` — Gets the transition layer that this transition behavior uses
- L41 _public prototype_ `virtual void SetTransitionLayer(FAvaTagHandle InTransitionLayer) = 0;` — Set the transition layer that this transition behavior will use
- L44 _public prototype_ `virtual void SetEnabled(bool bInEnabled) = 0;` — Sets whether this transition behavior is enabled
- L47 _public prototype_ `virtual bool IsEnabled() const = 0;` — Determines whether the transition behavior is enabled
- L51 _public prototype_ `virtual EAvaTransitionInstancingMode GetInstancingMode() const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Transition Logic")` — Determines the instancing mode of the transition behavior
- L54 _public prototype_ `virtual void SetInstancingMode(EAvaTransitionInstancingMode InInstancingMode) = 0;` — Sets the instancing mode for this transition behavior
- L57 _public prototype_ `virtual const FStateTreeReference& GetStateTreeReference() const = 0;` — Gets the underlying State Tree reference that this transition behavior runs
- L66 _public prototype_ `virtual void ForEachDetailsEditableProperty(TFunctionRef<void(const FPropertyContext&)> InFunc) const = 0;` — Calls the given functor on each property that is allowed to be visible in an external details panel

#### struct `IAvaTransitionBehavior::FPropertyContext`  
`struct FPropertyContext`  
_L60-64_
- L63 _public member_ `FName Name;` — Name of the property

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Conditions/AvaTransitionCondition.h` (Public)


#### struct `FAvaTransitionCondition`  
`struct FAvaTransitionCondition : public FStateTreeConditionBase #if CPP , public FAvaTransitionNode #endif`  
_L11-21_
- reflection: `USTRUCT(Category="Transition Logic", meta=(Hidden))`
- inherits: `FStateTreeConditionBase,FAvaTransitionNode`
- L19 _public function_ `virtual bool Link(FStateTreeLinker& InLinker) override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Conditions/AvaTransitionConditionBlueprint.h` (Public)


#### class `UAvaTransitionConditionBlueprint`  
`class UAvaTransitionConditionBlueprint : public UStateTreeConditionBlueprintBase, public IAvaTransitionNodeInterface`  
_L11-26_
- reflection: `UCLASS(MinimalAPI, Abstract, DisplayName="Motion Design Transition Condition Blueprint")`
- inherits: `UStateTreeConditionBlueprintBase,IAvaTransitionNodeInterface`
- L17 _protected prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;`
- L21 _protected prototype_ `virtual const FAvaTransitionBehaviorInstanceCache& GetBehaviorInstanceCache() const override;`
- L25 _private member_ `mutable FAvaTransitionBehaviorInstanceCache BehaviorInstanceCache;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Conditions/AvaTransitionLayerCondition.h` (Public)


#### struct `FAvaTransitionLayerConditionInstanceData`  
`struct FAvaTransitionLayerConditionInstanceData`  
_L13-22_
- reflection: `USTRUCT()`
- L18 _public member_ `EAvaTransitionLayerCompareType LayerType = EAvaTransitionLayerCompareType::Same;` — `UPROPERTY(EditAnywhere, Category="Parameter")`
- L21 _public member_ `FAvaTagHandle SpecificLayer;` — `UPROPERTY(EditAnywhere, Category="Parameter", meta=(EditCondition="LayerType==EAvaTransitionLayerCompareType::MatchingTag", EditConditionHides))`

#### struct `FAvaTransitionLayerCondition`  
`struct FAvaTransitionLayerCondition : public FAvaTransitionCondition`  
_L25-40_
- reflection: `USTRUCT(Category="Transition Logic", meta=(Hidden))`
- inherits: `FAvaTransitionCondition`
- L29 _public typedef_ `using FInstanceDataType = FAvaTransitionLayerConditionInstanceData;`
- L33 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L35 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L39 _public prototype_ `TArray<const FAvaTransitionBehaviorInstance*> QueryBehaviorInstances(const FStateTreeExecutionContext& InContext) const;` — Gets all the Behavior Instances that match the Layer Query. Always excludes the Instance belonging to this Transition

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Conditions/AvaTransitionLayerMatchCondition.h` (Public)


#### struct `FAvaTransitionLayerMatchConditionInstanceData`  
`struct FAvaTransitionLayerMatchConditionInstanceData : public FAvaTransitionLayerConditionInstanceData`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionLayerConditionInstanceData`

#### struct `FAvaTransitionLayerMatchCondition`  
`struct FAvaTransitionLayerMatchCondition : public FAvaTransitionLayerCondition`  
_L15-31_
- reflection: `USTRUCT(DisplayName="Layer is Transitioning", Category="Transition Logic")`
- inherits: `FAvaTransitionLayerCondition`
- L19 _public typedef_ `using FInstanceDataType = FAvaTransitionLayerMatchConditionInstanceData;`
- L23 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L25 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L29 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Conditions/AvaTransitionSceneMatchCondition.h` (Public)


#### struct `FAvaTransitionSceneMatchConditionInstanceData`  
`struct FAvaTransitionSceneMatchConditionInstanceData : public FAvaTransitionLayerConditionInstanceData`  
_L10-16_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionLayerConditionInstanceData`
- L15 _public member_ `EAvaTransitionComparisonResult SceneComparisonType = EAvaTransitionComparisonResult::None;` — `UPROPERTY(EditAnywhere, Category="Parameter")`

#### struct `FAvaTransitionSceneMatchCondition`  
`struct FAvaTransitionSceneMatchCondition : public FAvaTransitionLayerCondition`  
_L19-35_
- reflection: `USTRUCT(DisplayName="Compare other Scene in Layer", Category="Transition Logic")`
- inherits: `FAvaTransitionLayerCondition`
- L23 _public typedef_ `using FInstanceDataType = FAvaTransitionSceneMatchConditionInstanceData;`
- L27 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L29 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L33 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Conditions/AvaTransitionStateMatchCondition.h` (Public)


#### struct `FAvaTransitionStateMatchConditionInstanceData`  
`struct FAvaTransitionStateMatchConditionInstanceData : public FAvaTransitionLayerConditionInstanceData`  
_L10-16_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionLayerConditionInstanceData`
- L15 _public member_ `EAvaTransitionRunState TransitionState = EAvaTransitionRunState::Running;` — `UPROPERTY(EditAnywhere, Category="Parameter")`

#### struct `FAvaTransitionStateMatchCondition`  
`struct FAvaTransitionStateMatchCondition : public FAvaTransitionLayerCondition`  
_L19-35_
- reflection: `USTRUCT(DisplayName="Check State of other Scene in Layer", Category="Transition Logic")`
- inherits: `FAvaTransitionLayerCondition`
- L23 _public typedef_ `using FInstanceDataType = FAvaTransitionStateMatchConditionInstanceData;`
- L27 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L29 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L33 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Conditions/AvaTransitionTypeMatchCondition.h` (Public)


#### struct `FAvaTransitionTypeMatchConditionInstanceData`  
`struct FAvaTransitionTypeMatchConditionInstanceData`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `EAvaTransitionType TransitionType = EAvaTransitionType::In;` — `UPROPERTY(EditAnywhere, Category="Parameter")`

#### struct `FAvaTransitionTypeMatchCondition`  
`struct FAvaTransitionTypeMatchCondition : public FAvaTransitionCondition`  
_L19-35_
- reflection: `USTRUCT(DisplayName="My Transition Type is", Category="Transition Logic")`
- inherits: `FAvaTransitionCondition`
- L23 _public typedef_ `using FInstanceDataType = FAvaTransitionTypeMatchConditionInstanceData;`
- L27 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L29 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L33 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Execution/AvaTransitionExecutorBuilder.h` (Public)


#### class `FAvaTransitionExecutorBuilder`  
`class FAvaTransitionExecutorBuilder`  
_L14-50_
- desc: Builder Class for Base Transition Executor Implementation
- L19 _public prototype_ `FAvaTransitionExecutorBuilder();`
- L21 _public prototype_ `FAvaTransitionExecutorBuilder& SetContextName(const FString& InContextName);`
- L23 _public prototype_ `FAvaTransitionExecutorBuilder& AddEnterInstance(FAvaTransitionBehaviorInstance& InInstance);`
- L25 _public prototype_ `FAvaTransitionExecutorBuilder& AddExitInstance(FAvaTransitionBehaviorInstance& InInstance);`
- L33 _public prototype_ `FAvaTransitionExecutorBuilder& SetNullInstance(FAvaTransitionBehaviorInstance& InInstance);` — Optional: Sets a null instance to use as "no transition" This is used as filler if there are missing behavior instances in a layer. For example if there is an Enter Instance for a layer, but there was no Exit Instance added for that layer, a Null Instance is created for that Layer
- L36 _public prototype_ `FAvaTransitionExecutorBuilder& SetOnFinished(FSimpleDelegate InDelegate);` — Set the delegate to call when the Transition finishes
- L38 _public prototype_ `[[nodiscard]] TSharedRef<IAvaTransitionExecutor> Build(UAvaTransitionSubsystem& InTransitionSubsystem);`
- L41 _private member_ `TArray<FAvaTransitionBehaviorInstance> EnterInstances;`
- L43 _private member_ `TArray<FAvaTransitionBehaviorInstance> ExitInstances;`
- L45 _private member_ `FAvaTransitionBehaviorInstance NullInstance;`
- L47 _private member_ `FString ContextName;`
- L49 _private member_ `FSimpleDelegate OnFinished;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Execution/IAvaTransitionExecutor.h` (Public)


#### class `IAvaTransitionExecutor`  
`class IAvaTransitionExecutor : public TSharedFromThis<IAvaTransitionExecutor>`  
_L14-38_
- inherits: `TSharedFromThis<IAvaTransitionExecutor>`
- desc: Responsible for execution of Transition Behaviors and signaling when these Behaviors have completed. NOTE: The Executor shared reference should be kept alive until it completes the behaviors
- L17 _public prototype_ `virtual ~IAvaTransitionExecutor() = default;`
- L20 _public prototype_ `virtual TArray<const FAvaTransitionBehaviorInstance*> GetBehaviorInstances(const FAvaTransitionLayerComparator& InComparator) const = 0;` — Gets all the Behavior Instances matching the Layer Comparator
- L23 _public prototype_ `virtual void ForEachBehaviorInstance(TFunctionRef<void(const FAvaTransitionBehaviorInstance&)> InCallable) const = 0;` — Runs the provided callback for each Behavior Instance
- L26 _public prototype_ `virtual void Start() = 0;` — Start Transition. Should only be called once
- L29 _public prototype_ `virtual void Stop() = 0;` — Stop the current Execution
- L31 _public function_ `static TMulticastDelegate<void(const IAvaTransitionExecutor&)>& GetOnTransitionStart()`
- L37 _private member_ `static TMulticastDelegate<void(const IAvaTransitionExecutor&)> OnTransitionStart;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/IAvaTransitionExtension.h` (Public)


#### class `IAvaTransitionExtension`  
`class IAvaTransitionExtension`  
_L27-40_
- desc: Transition Extensions offers capabilities that connect a transition task/condition to some external logic. The Base Extension must be implemented with a ExtensionIdentifier static variable so that it can be identified as T::ExtensionIdentifier. This Extension Identifier is used as the map key to the extensions in the Transition Scene. Example Base Class: class IMyTransitionExtension : public IAvaTransitionExtension { public: static constexpr const TCHAR* ExtensionIdentifier = TEXT("MyExtension"); virtual bool Compare(...) = 0; }; @see FAvaTransitionScene::FindExtension, FAvaTransitionScene::AddExtension
- L39 _public member_ `template<typename T> static constexpr bool TIsValidExtension_V = std::is_base_of_v<IAvaTransitionExtension, T> && TModels_V<CTransitionExtensionProvider, T>;`

#### struct `IAvaTransitionExtension::CTransitionExtensionProvider`  
`struct CTransitionExtensionProvider`  
_L29-35_
- L32 _public prototype_ `template<typename T> auto Requires(FName& OutIdentifier)->decltype( OutIdentifier = T::ExtensionIdentifier );`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/IAvaTransitionModule.h` (Public)


#### class `IAvaTransitionModule`  
`class IAvaTransitionModule : public IModuleInterface`  
_L11-29_
- inherits: `IModuleInterface`
- L13 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("Ava`
- L16 _public function_ `static bool IsLoaded()`
- L21 _public function_ `static IAvaTransitionModule& Get()`
- L27 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValidateTransitionTree, UAvaTransitionTree*);` — Delegate to ensure that the Tree has been Initialized correctly
- L28 _public prototype_ `virtual FOnValidateTransitionTree& GetOnValidateTransitionTree() = 0;`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValidateTransitionTree, UAvaTransitionTree*);` — Delegate to ensure that the Tree has been Initialized correctly

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/IAvaTransitionNodeInterface.h` (Public)


#### class `UAvaTransitionNodeInterface`  
`class UAvaTransitionNodeInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta=(DisplayName="Motion Design Transition Node Interface", CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface that enable nodes that store a Behavior Instance Cache to expose this execution cache for others like function libraries to retrieve it

#### class `IAvaTransitionNodeInterface`  
`class IAvaTransitionNodeInterface`  
_L17-23_
- L22 _public prototype_ `virtual const FAvaTransitionBehaviorInstanceCache& GetBehaviorInstanceCache() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Rendering/AvaTransitionRenderingSubsystem.h` (Public)


#### class `UAvaTransitionRenderingSubsystem`  
`class UAvaTransitionRenderingSubsystem : public UWorldSubsystem`  
_L16-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L21 _public prototype_ `void ShowLevel(TObjectKey<ULevel> InLevel);`
- L22 _public prototype_ `void HideLevel(TObjectKey<ULevel> InLevel);`
- L24 _public prototype_ `void SetupView(FSceneView& InView);`
- L28 _private member_ `TArray<TObjectKey<ULevel>> HiddenLevels;` — List of levels that will be hidden. Same level can be repeated to indicate multiple places are actively trying to have the level hidden
- L30 _private member_ `TSet<FPrimitiveComponentId> HiddenPrimitives;`
- L33 _private member_ `TSet<TObjectKey<ULevel>> ProcessedLevels;` — Temporary Member Variable to keep Track of the Processed Levels when Iterating Hidden Levels

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Tasks/AvaTransitionDelayTask.h` (Public)


#### struct `FAvaTransitionDelayTaskInstanceData`  
`struct FAvaTransitionDelayTaskInstanceData`  
_L14-30_
- reflection: `USTRUCT()`
- L20 _public member_ `float Duration = 0.5f;` — `UPROPERTY(EditAnywhere, Category="Parameter", meta=(ClampMin="0.0"))` — Delay in seconds before the task ends.
- L24 _public member_ `EAvaTransitionLevelHideMode HideMode = EAvaTransitionLevelHideMode::NoHide;` — `UPROPERTY(EditAnywhere, Category="Transition Logic")` — Hide mode to use while the Wait is taking place
- L27 _public member_ `float RemainingTime = 0.f;` — Internal countdown in seconds.
- L29 _public member_ `TObjectKey<ULevel> HiddenLevel;`

#### struct `FAvaTransitionDelayTask`  
`struct FAvaTransitionDelayTask : public FAvaTransitionTask`  
_L33-57_
- reflection: `USTRUCT(DisplayName="Delay", Category="Transition Logic")`
- inherits: `FAvaTransitionTask`
- L37 _public typedef_ `using FInstanceDataType = FAvaTransitionDelayTaskInstanceData;`
- L41 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L43 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L44 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L48 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`
- L49 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& InContext, const float InDeltaTime) const override;`
- L52 _public prototype_ `EStateTreeRunStatus WaitForDelayCompletion(FStateTreeExecutionContext& InContext, FInstanceDataType& InInstanceData) const;`
- L54 _public prototype_ `bool ShouldHideLevel(const FStateTreeExecutionContext& InContext, const FInstanceDataType& InInstanceData) const;`
- L56 _public member_ `TStateTreeExternalDataHandle<UAvaTransitionRenderingSubsystem> RenderingSubsystemHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Tasks/AvaTransitionDiscardSceneTask.h` (Public)


#### struct `FAvaTransitionDiscardSceneInstanceData`  
`struct FAvaTransitionDiscardSceneInstanceData`  
_L9-12_
- reflection: `USTRUCT()`

#### struct `FAvaTransitionDiscardSceneTask`  
`struct FAvaTransitionDiscardSceneTask : public FAvaTransitionTask`  
_L15-28_
- reflection: `USTRUCT(DisplayName = "Discard Self", Category="Transition Logic")`
- inherits: `FAvaTransitionTask`
- L19 _public typedef_ `using FInstanceDataType = FAvaTransitionDiscardSceneInstanceData;`
- L22 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L26 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Tasks/AvaTransitionLayerTask.h` (Public)


#### struct `FAvaTransitionLayerTaskInstanceData`  
`struct FAvaTransitionLayerTaskInstanceData`  
_L11-20_
- reflection: `USTRUCT()`
- L16 _public member_ `EAvaTransitionLayerCompareType LayerType = EAvaTransitionLayerCompareType::Same;` — `UPROPERTY(EditAnywhere, Category="Parameter")`
- L19 _public member_ `FAvaTagHandle SpecificLayer;` — `UPROPERTY(EditAnywhere, Category="Parameter", meta=(EditCondition="LayerType==EAvaTransitionLayerCompareType::MatchingTag", EditConditionHides))`

#### struct `FAvaTransitionLayerTask`  
`struct FAvaTransitionLayerTask : public FAvaTransitionTask`  
_L23-38_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FAvaTransitionTask`
- L27 _public typedef_ `using FInstanceDataType = FAvaTransitionLayerTaskInstanceData;`
- L31 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L33 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L37 _public prototype_ `TArray<const FAvaTransitionBehaviorInstance*> QueryBehaviorInstances(const FStateTreeExecutionContext& InContext) const;` — Gets all the Behavior Instances that match the Layer Query. Always excludes the Instance belonging to this Transition

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Tasks/AvaTransitionTask.h` (Public)


#### struct `FAvaTransitionTask`  
`struct FAvaTransitionTask : public FStateTreeTaskBase #if CPP , public FAvaTransitionNode #endif`  
_L11-21_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FStateTreeTaskBase,FAvaTransitionNode`
- L19 _public function_ `virtual bool Link(FStateTreeLinker& InLinker) override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Tasks/AvaTransitionTaskBlueprint.h` (Public)


#### class `UAvaTransitionTaskBlueprint`  
`class UAvaTransitionTaskBlueprint : public UStateTreeTaskBlueprintBase, public IAvaTransitionNodeInterface`  
_L11-27_
- reflection: `UCLASS(MinimalAPI, Abstract, DisplayName="Motion Design Transition Task Blueprint")`
- inherits: `UStateTreeTaskBlueprintBase,IAvaTransitionNodeInterface`
- L17 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InExecutionContext, const FStateTreeTransitionResult& InTransition) override;`
- L18 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& InExecutionContext, const FStateTreeTransitionResult& InTransition) override;`
- L22 _protected prototype_ `virtual const FAvaTransitionBehaviorInstanceCache& GetBehaviorInstanceCache() const override;`
- L26 _private member_ `FAvaTransitionBehaviorInstanceCache BehaviorInstanceCache;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransition/Public/Tasks/AvaTransitionWaitForLayerTask.h` (Public)


#### struct `FAvaTransitionWaitForLayerTaskInstanceData`  
`struct FAvaTransitionWaitForLayerTaskInstanceData : public FAvaTransitionLayerTaskInstanceData`  
_L13-22_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionLayerTaskInstanceData`
- L19 _public member_ `EAvaTransitionLevelHideMode HideMode = EAvaTransitionLevelHideMode::HideUnlessReuse;` — `UPROPERTY(EditAnywhere, Category="Transition Logic")` — Hide mode to use while the Wait is taking place
- L21 _public member_ `TObjectKey<ULevel> HiddenLevel;`

#### struct `FAvaTransitionWaitForLayerTask`  
`struct FAvaTransitionWaitForLayerTask : public FAvaTransitionLayerTask`  
_L25-49_
- reflection: `USTRUCT(DisplayName = "Wait for other Scenes in Layer to Finish", Category="Transition Logic")`
- inherits: `FAvaTransitionLayerTask`
- L29 _public typedef_ `using FInstanceDataType = FAvaTransitionWaitForLayerTaskInstanceData;`
- L33 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L35 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L36 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L40 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`
- L41 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& InContext, const float InDeltaTime) const override;`
- L44 _public prototype_ `EStateTreeRunStatus WaitForLayer(FStateTreeExecutionContext& InContext) const;`
- L46 _public prototype_ `bool ShouldHideLevel(const FStateTreeExecutionContext& InContext, const FAvaTransitionWaitForLayerTask::FInstanceDataType& InInstanceData) const;`
- L48 _public member_ `TStateTreeExternalDataHandle<UAvaTransitionRenderingSubsystem> RenderingSubsystemHandle;`
