# Plugins / UAFLayering

- module root: `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering`
- headers: 13; symbols: 115
- symbol kinds: class=3, delegate=1, enum=1, enumerator=4, function=6, macro=4, member=40, namespace=11, prototype=26, struct=15, typedef=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, RigVM, Slate, SlateCore, UAFAnimGraph
- PublicDependencyModuleNames: Core, UAF

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Internal/Traits/CachePoseTraitData.h` (Internal)


#### struct `FUAFCachePoseTraitSharedData`  
`struct FUAFCachePoseTraitSharedData : public FAnimNextTraitSharedData`  
_L13-16_
- reflection: `USTRUCT(meta = (DisplayName = "Cache Pose", ShowTooltip=true, Hidden))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that caches the top keyframe of the keyframe stack TODO: Not implemented yet, at the moment it will simply pop the top keyframe and throw it away

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Internal/Traits/LayerAssetDataTraitData.h` (Internal)


#### struct `FUAFLayerAssetDataTraitSharedData`  
`struct FUAFLayerAssetDataTraitSharedData : public FAnimNextTraitSharedData`  
_L15-29_
- reflection: `USTRUCT(meta = (DisplayName = "Layer Data Provider", ShowTooltip=true, Hidden))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that creates an UAF Graph at runtime based on the given asset in the layering setup and pushes it onto a blend stack
- L20 _public member_ `TInstancedStruct<FUAFGraphFactoryAsset> GraphAssetHandle;` — `UPROPERTY(EditAnywhere, Category = "Layer|Content")`

#### Free symbols / members of external scopes

- L23 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Internal/Traits/LayerDataProviderTraitData.h` (Internal)


#### struct `FUAFLayerProperties`  
`struct FUAFLayerProperties`  
_L15-50_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `void AddEvent(const UE::UAF::Layering::FLayerStack_LayerEvent& Event);`
- L21 _public prototype_ `void ProcessEvents();`
- L26 _public member_ `bool bLayerEnabled = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layering")` — TODO: this should be a binding
- L30 _public member_ `float DesiredLayerWeight = 1.0f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layering")` — TODO: this should be a binding
- L34 _public member_ `float BlendInTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layering")` — TODO: this should be a binding
- L38 _public member_ `float BlendOutTime = 0.0f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layering")` — TODO: this should be a binding
- L42 _public member_ `TObjectPtr<UCurveFloat> BlendCurve = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layering")` — TODO: this should be a binding
- L46 _public member_ `EAlphaBlendOption BlendOption = EAlphaBlendOption::Linear;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layering")` — TODO: this should be a binding
- L49 _private member_ `TArray<UE::UAF::Layering::FLayerStack_LayerEvent> EventsToProcess;`

#### struct `FUAFLayerDataProviderTraitSharedData`  
`struct FUAFLayerDataProviderTraitSharedData : public FAnimNextTraitSharedData`  
_L54-87_
- reflection: `USTRUCT(meta = (DisplayName = "Layer Data Provider", ShowTooltip=true, Hidden))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that provides blend data based the outer layer stack
- L59 _public member_ `FUAFLayerProperties LayerProperties;` — `UPROPERTY(EditAnywhere, Category = "Layer")`
- L63 _public member_ `int32 LayerIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))` — The index of this layer in its owning layer stack
- L67 _public member_ `FName LayerName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))` — The layer name of this layer
- L71 _public member_ `FString LayerStackPath;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))` — The soft object path to the owning layer stack
- L74 _public member_ `bool bCreateCacheInput = false;` — If this is true we will allocate the input to allow for update/eval of cache only branches of the tree
- L78 _public member_ `FAnimNextTraitHandle CacheOnlyInput;` — `UPROPERTY()` — This is only used to enqueue Cache Only layers to the graph update without actually blending them in in-place

#### Free symbols / members of external scopes

- L81 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Internal/Traits/MontageLayerTraitData.h` (Internal)


#### struct `FUAFMontageLayerTraitSharedData`  
`struct FUAFMontageLayerTraitSharedData : public FAnimNextTraitSharedData`  
_L12-33_
- reflection: `USTRUCT(meta = (DisplayName = "Montage Layer Data", ShowTooltip=true, Hidden))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that supports modifying an existing layer based on montage runtime data
- L17 _public member_ `bool bAutoEnableLayer = false;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))`
- L20 _public member_ `bool bAutoSetBlendTimes = false;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))`
- L24 _public member_ `FName SlotName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))` — The montage slot name of this layer
- L28 _public member_ `FName LayerName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))` — The layer name of this layer
- L32 _public member_ `FString LayerStackPath;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (Inline))` — The soft object path to the owning layer stack

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Internal/UAFLayerStack.h` (Internal)


#### class `UUAFLayerStack`  
`class UUAFLayerStack : public UUAFAnimGraph`  
_L8-15_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UUAFAnimGraph`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Private/Tasks/UAFCachePoseTask.h` (Private)


#### struct `FUAFCachePoseTask`  
`struct FUAFCachePoseTask : public FAnimNextEvaluationTask`  
_L18-28_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L22 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FUAFCachePoseTask) static FUAFCachePoseTask Make();`
- L27 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task Entry point

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF Task: CachePose"), STAT_AnimNext_Task_CachePose, STATGROUP_AnimNext`
- L15 _macro_ `#define UE_API UAFLAYERING_API`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Private/Traits/CachePoseTrait.h` (Private)


#### struct `UE::UAF::FCachePoseTrait`  
`struct FCachePoseTrait : FAdditiveTrait, IEvaluate`  
_L11-27_
- inherits: `FAdditiveTrait,IEvaluate`
- L19 _public typedef_ `using FSharedData = FUAFCachePoseTraitSharedData;`
- L22 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L25 _public function_ `virtual bool IsHidden() const override`

#### struct `UE::UAF::FCachePoseTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L15-17_
- inherits: `FTrait::FInstanceData`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Private/Traits/LayerAssetDataProviderTrait.h` (Private)


#### struct `UE::UAF::FLayerAssetDataProviderTrait`  
`struct FLayerAssetDataProviderTrait : FAdditiveTrait, IUpdate, IGarbageCollection`  
_L12-35_
- inherits: `FAdditiveTrait,IUpdate,IGarbageCollection`
- L23 _public typedef_ `using FSharedData = FUAFLayerAssetDataTraitSharedData;`
- L26 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L29 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl
- L32 _public function_ `virtual bool IsHidden() const override`

#### struct `UE::UAF::FLayerAssetDataProviderTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L17-21_
- inherits: `FTrait::FInstanceData`
- L19 _public member_ `FGraphAssetHandle CachedAssetHandle;`
- L20 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Private/Traits/LayerDataProviderTrait.h` (Private)


#### struct `UE::UAF::FLayerDataProviderTrait`  
`struct FLayerDataProviderTrait : FAdditiveTrait, IUpdate, IContinuousBlend, IHierarchy`  
_L13-73_
- inherits: `FAdditiveTrait,IUpdate,IContinuousBlend,IHierarchy`
- L49 _public typedef_ `using FSharedData = FUAFLayerDataProviderTraitSharedData;`
- L52 _public prototype_ `virtual void PostUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate imp
- L55 _public prototype_ `virtual float GetBlendWeight(const FExecutionContext& Context, const TTraitBinding<IContinuousBlend>& Binding, int32 ChildIndex) const override;` — IContinuousBlend impl - this allows us to override the weight for any lower blend trait
- L58 _public prototype_ `ETraitStackPropagation OnLayerEvent(const FExecutionContext& Context, FTraitBinding& Binding, Layering::FLayerStack_LayerEvent& Event) const;` — Event Handling
- L61 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy Impl
- L62 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L65 _public function_ `virtual bool IsHidden() const override`
- L69 _private prototype_ `void UpdateTargetLayerWeight(FInstanceData* InstanceData, const FUAFLayerProperties& LayerData) const;`
- L70 _private prototype_ `void UpdateLayerBlendTimes(FInstanceData* InstanceData, const FUAFLayerProperties& LayerData) const;`
- L71 _private prototype_ `void HandleLayerActivation(FInstanceData* InstanceData, const FUAFLayerProperties& LayerData) const;`

#### struct `UE::UAF::FLayerDataProviderTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L17-47_
- inherits: `FTrait::FInstanceData`
- L20 _public member_ `bool bLayerEnabled = true;` — If the layer is currently enabled or not.
- L23 _public member_ `float EffectiveLayerWeight = 1.0f;` — The cached effective layer weight - the actual weight used when applying this layer based on the target weight and any active blends
- L27 _public member_ `float TargetLayerWeight = 1.0f;` — The target weight of this layer. This is the desired weight to apply for this layer, however if the layer is currently blending in/out this might not be the weight that gets applied - see EffectiveLayerWeight.
- L30 _public member_ `float LayerBlendInTime = 0.0f;` — The blend in time used when blending this layer in
- L33 _public member_ `float LayerBlendOutTime = 0.0f;` — The blend out time used when blending this layer out
- L36 _public member_ `FTraitPtr CacheOnlyInput;` — Trait handle to execute cache only parts of the graph
- L39 _public member_ `FAlphaBlend AlphaBlend;` — This updated the discrete blend when a layer blends in or out
- L44 _public member_ `FUAFLayerProperties LayerProperties;` — This layer data is likely not going to live here once bindings are implemented This contains all the bound / desired layer properties versus the rest of the instance data containing the currently used data based on any blending between properties and to check if data has changed between frames
- L46 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Private/Traits/MontageLayerDataTrait.h` (Private)


#### struct `UE::UAF::FMontageLayerDataTrait`  
`struct FMontageLayerDataTrait : FAdditiveTrait, IUpdate`  
_L11-30_
- inherits: `FAdditiveTrait,IUpdate`
- L21 _public typedef_ `using FSharedData = FUAFMontageLayerTraitSharedData;`
- L24 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L27 _public function_ `virtual bool IsHidden() const override`

#### struct `UE::UAF::FMontageLayerDataTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L15-19_
- inherits: `FTrait::FInstanceData`
- L17 _public member_ `bool bLastEnableState = false;`
- L18 _public member_ `TWeakObjectPtr<const UAnimMontage> LastActiveMontage = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Private/UAFLayeringModule.h` (Private)


#### class `FUAFLayeringModule`  
`class FUAFLayeringModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Public/UAFLayeringTypes.h` (Public)


#### enum `UE::UAF::Layering::ELayerEventAction`  
`enum class ELayerEventAction : uint8`  
_L10-16_
- L12 _public enumerator_ `None`
- L13 _public enumerator_ `EnableLayer`
- L14 _public enumerator_ `DisableLayer`
- L15 _public enumerator_ `SetFloatValue`

#### struct `UE::UAF::Layering::FLayerStack_LayerEvent`  
`struct FLayerStack_LayerEvent : public FAnimNextTraitEvent`  
_L18-57_
- inherits: `FAnimNextTraitEvent`
- L20 _public function_ `DECLARE_ANIM_TRAIT_EVENT(FLayerStack_LayerEvent, FAnimNextTraitEvent) FLayerStack_LayerEvent(FName InLayerName, const FSoftObjectPath& InObjectPath) : LayerName(InLayerName) , LayerStackAssetPath(InObjectPath)`
- L27 _public function_ `FLayerStack_LayerEvent(int32 InLayerIndex, const FSoftObjectPath& InObjectPath) : LayerIndex(InLayerIndex) , LayerStackAssetPath(InObjectPath)`
- L33 _public member_ `const FName LayerName = NAME_None;` — The name of the layer to affect
- L36 _public member_ `const int32 LayerIndex = INDEX_NONE;` — The index in the layer stack for the layer to affect
- L39 _public member_ `const FSoftObjectPath LayerStackAssetPath = FSoftObjectPath();` — The soft object path of the layer stack asset the layer exists in
- L42 _public member_ `ELayerEventAction Action = ELayerEventAction::None;` — The action to perform
- L45 _public member_ `FName PropertyToSet = NAME_None;` — The name of the property to change if applicable
- L48 _public member_ `float FloatValue = 0.0f;` — The float value to set, if applicable
- L52 _public member_ `bool bAutoConsumeEvent = false;` — If this event should be consumed by the first found layer that matches the description Per default the event will be passed through the UAF system and every layer gets the option to react to it
- L54 _public member_ `static const FName LayerWeightProperty;`
- L55 _public member_ `static const FName BlendInTimeProperty;`
- L56 _public member_ `static const FName BlendOutTimeProperty;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Layering` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayering/Public/UAFLayeringUtils.h` (Public)


#### class `UUAFLayeringUtils`  
`class UUAFLayeringUtils : public UBlueprintFunctionLibrary`  
_L15-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L21 _private prototype_ `static void EnableLayer(UUAFComponent* UAFComponent, FName LayerName, const TSoftObjectPtr<UUAFLayerStack> LayerStackPath);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Layering", meta = (ScriptMethod))` — Enables the specified layer by name in the specified Layer Stack
- L25 _private prototype_ `static void DisableLayer(UUAFComponent* UAFComponent, FName LayerName, const TSoftObjectPtr<UUAFLayerStack> LayerStackPath);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Layering", meta = (ScriptMethod))` — Disables the specified layer by name in the specified Layer Stack
- L29 _private prototype_ `static void SetLayerWeight(UUAFComponent* UAFComponent, FName LayerName, const TSoftObjectPtr<UUAFLayerStack> LayerStackPath, const float Weight);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Layering", meta = (ScriptMethod))` — Sets the weight of the specified layer by name in the specified Layer Stack
- L33 _private prototype_ `static void EnableLayerByIndex(UUAFComponent* UAFComponent, int32 LayerIndex, const TSoftObjectPtr<UUAFLayerStack> LayerStackPath);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Layering", meta = (ScriptMethod))` — Enables the specified layer by index in the specified Layer Stack
- L37 _private prototype_ `static void DisableLayerByIndex(UUAFComponent* UAFComponent, int32 LayerIndex, const TSoftObjectPtr<UUAFLayerStack> LayerStackPath);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Layering", meta = (ScriptMethod))` — Disables the specified layer by index in the specified Layer Stack
- L41 _private prototype_ `static void SetLayerWeightByIndex(UUAFComponent* UAFComponent, int32 LayerIndex, const TSoftObjectPtr<UUAFLayerStack> LayerStackPath, const float Weight);` — `UFUNCTION(BlueprintCallable, Category = "UAF|Layering", meta = (ScriptMethod))` — Sets the weight of the specified layer by index in the specified Layer Stack

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFLAYERING_API`
