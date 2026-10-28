# Plugins / AvalancheMaterial

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial`
- headers: 24; symbols: 297
- symbol kinds: class=18, delegate=2, enum=4, enumerator=6, function=18, macro=14, member=56, namespace=48, prototype=91, struct=23, typedef=17
- PrivateDependencyModuleNames: RHI, RenderCore
- PublicDependencyModuleNames: AvalancheCore, Core, CoreUObject, DeveloperSettings, Engine

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Internal/MaterialCache/AvaMaterialCacheHelper.h` (Internal)


#### class `UE::Ava::FMaterialCacheHelper`  
`class FMaterialCacheHelper : public TSharedFromThis<FMaterialCacheHelper>, public FGCObject`  
_L24-152_
- inherits: `TSharedFromThis<FMaterialCacheHelper>,FGCObject`
- desc: Helper to cache materials over multiple frames
- L37 _private function_ `friend uint32 GetTypeHash(const FMaterialKey& InKey)`
- L62 _public prototype_ `static FMaterialCacheHelper& Get();`
- L70 _public prototype_ `bool RequestCacheMaterials(const UObject* InObject, FName InShaderProfile = NAME_None);` — Caches the materials in the given object. @param InObject the object to gather materials for via the material bridge api @param InShaderProfile the shader profile to use for caching shaders. If none, it will cache via UMaterial::CacheShaders @return true if materials were gathered for the object, false otherwise. (e.g. if object's materials were already gathered, or no material bridge found)
- L73 _public prototype_ `void Tick();` — Processes materials pending completion with a limited time budget
- L76 _public prototype_ `bool IsCaching() const;` — Returns true if there are still any materials being cached
- L79 _public prototype_ `bool IsCaching(const UObject* InObject) const;` — Returns true if there are materials from the given object that are still being cached
- L82 _public prototype_ `void DumpMaterials();` — Dumps all the materials that are still being processed (i.e. still incomplete) to the output log
- L85 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L86 _public prototype_ `virtual FString GetReferencerName() const override;`
- L91 _private prototype_ `bool IsCachingMaterial(const FMaterialKey& InMaterialKey) const;` — Returns true if the material is still being cached
- L94 _private prototype_ `void Reset();` — Resets the object and material map
- L97 _private prototype_ `void RegisterTick();` — Registers the tick function to get called every frame
- L100 _private prototype_ `void UnregisterTick();` — Unregisters the tick function from being called every frame
- L103 _private prototype_ `void ProcessPendingObjects();` — Processes subobjects that did not have its materials gathered
- L106 _private prototype_ `void ProcessMaterialsPendingCache();` — Caches as many queued materials as the time budget allows
- L109 _private prototype_ `void ProcessMaterialsCaching();` — Checks the status on materials that are being cached, and removes from the map once they're complete
- L112 _private prototype_ `void RemoveCompletedMaterials();` — Removes the complete materials from the objects' IncompleteMaterials set
- L115 _private prototype_ `void ProcessShadersCompiling();` — Process async results if shader is compiling
- L121 _private prototype_ `bool GatherMaterialData(const UObject* InObject, FObjectData& InObjectData, FName InShaderProfile);` — Gathers the material data for an object returns true if a material bridge was found for the object and visited its materials
- L124 _private member_ `TMap<FObjectKey, FObjectData> Objects;` — Objects that have already been gathered, mapped to the incomplete materials that were gathered for the object
- L127 _private member_ `TMap<FMaterialKey, FMaterialData> MaterialsPendingCache;` — All the materials that have been gathered and are pending to start caching their shaders. Once materials start caching, they're removed from this map and added to MaterialsCaching
- L130 _private member_ `TMap<FMaterialKey, FMaterialData> MaterialsCaching;` — All the materials that are caching. Once materials are complete, they're removed from this map
- L133 _private member_ `float PreTickFrameDuration = 0.0;` — The delta time at the start of the tick
- L136 _private member_ `double BeginFrameTime = 0.0;` — Time when BeginFrame was called
- L139 _private member_ `float RemainingTimeBudget = 0.f;` — Current time budget left for the tick. Resets every tick
- L142 _private member_ `int32 FramesStarved = 0;` — Number of frames where Tick was skipped because the frame time was past max frame time
- L145 _private member_ `FDelegateHandle BeginFrameHandle;` — Handle to the BeginFrame delegate to keep track of BeginFrameTime
- L148 _private member_ `FDelegateHandle EndFrameHandle;` — Handle to the delegate for ticking
- L151 _private member_ `bool bResetRequested = false;` — Reset material cache

#### struct `UE::Ava::FMaterialCacheHelper::FMaterialKey`  
`struct FMaterialKey`  
_L26-41_
- L29 _public member_ `TObjectKey<UMaterialInterface> Material;` — Object key to the Material being cached
- L31 _public member_ `FName ShaderProfile;` — Shader profile to use for caching the material shaders
- L33 _public function_ `bool operator==(const FMaterialKey& InOther) const`

#### struct `UE::Ava::FMaterialCacheHelper::FObjectData`  
`struct FObjectData`  
_L43-53_
- L46 _public member_ `FName ShaderProfile;` — Shader profile to use for caching the material shaders
- L48 _public member_ `TSet<FMaterialKey> IncompleteMaterialKeys;` — All the keys to the materials belonging to an object that are still incomplete
- L50 _public member_ `TSet<TObjectPtr<const UObject>> PendingSubobjects;` — List of subobjects that were pending completion and could not gather materials
- L52 _public member_ `float PendingSubobjectElapsedTime = 0.f;` — Time elapsed before checking pending subobjects

#### struct `UE::Ava::FMaterialCacheHelper::FMaterialData`  
`struct FMaterialData`  
_L55-59_
- L58 _public member_ `TObjectPtr<UMaterialInterface> Material;` — Material that is pending completion

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Ava` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Internal/MaterialCache/AvaMaterialCacheLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMaterialCache, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMaterialCache, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Internal/MaterialCache/AvaMaterialCacheSettings.h` (Internal)


#### enum `EAvaShaderProfileType`  
`enum class EAvaShaderProfileType : uint8`  
_L15-29_
- reflection: `UENUM()`
- L21 _public enumerator_ `Generic` — CacheShaders will be used and will gather all the shaders it might need NOTE: this might cause more shaders to be compiled than required.
- L26 _public enumerator_ `Specific` — Only the specified shaders will be cached. Should yield better performance than generic. NOTE: Specified shaders only will apply in editor builds. This will default to generic on non-editor builds
- L28 _public enumerator_ `SkipCaching` — No shaders will be cached

#### struct `UE::Ava::FResolvedShaderProfile`  
`struct FResolvedShaderProfile`  
_L35-41_
- desc: Shader Profile that has all the type pointers cached
- L37 _public member_ `EAvaShaderProfileType ProfileType = EAvaShaderProfileType::Generic;`
- L38 _public member_ `TArray<const FVertexFactoryType*> VertexFactoryTypes;`
- L39 _public member_ `TArray<const FShaderPipelineType*> PipelineTypes;`
- L40 _public member_ `TArray<const FShaderType*> ShaderTypes;`

#### struct `FAvaShaderCombination`  
`struct FAvaShaderCombination`  
_L46-67_
- reflection: `USTRUCT()`
- L50 _public prototype_ `FAvaShaderCombination() = default;`
- L52 _public function_ `explicit FAvaShaderCombination(FName InVertexFactorType, TConstArrayView<FName> InPipelineTypes, TConstArrayView<FName> InShaderTypes) : VertexFactoryType(InVertexFactorType) , PipelineTypes(InPipelineTypes) , ShaderTypes(InShaderTypes)`
- L60 _public member_ `FName VertexFactoryType;` — `UPROPERTY(EditAnywhere, Category="Material Cache")`
- L63 _public member_ `TArray<FName> PipelineTypes;` — `UPROPERTY(EditAnywhere, Category="Material Cache")`
- L66 _public member_ `TArray<FName> ShaderTypes;` — `UPROPERTY(EditAnywhere, Category="Material Cache")`

#### struct `FAvaShaderProfile`  
`struct FAvaShaderProfile`  
_L70-83_
- reflection: `USTRUCT()`
- L75 _public member_ `FName ProfileName;` — `UPROPERTY(EditAnywhere, Category="Material Cache")`
- L78 _public member_ `EAvaShaderProfileType ProfileType = EAvaShaderProfileType::Generic;` — `UPROPERTY(EditAnywhere, Category="Material Cache")`
- L82 _public member_ `TArray<FAvaShaderCombination> ShaderCombinations;` — `UPROPERTY(EditAnywhere, Category="Material Cache", meta=(EditCondition="ProfileType==EAvaShaderProfileType::Specific"))` — Specific Shader Combinations to use

#### class `UAvaMaterialCacheSettings`  
`class UAvaMaterialCacheSettings : public UDeveloperSettings`  
_L86-142_
- reflection: `UCLASS(MinimalAPI, config=Engine, meta=(DisplayName="Material Cache Settings"))`
- inherits: `UDeveloperSettings`
- L91 _public member_ `static const FLazyName DefaultRealtimeProfile;`
- L92 _public member_ `static const FLazyName DefaultOfflineProfile;`
- L94 _public prototype_ `UAvaMaterialCacheSettings();`
- L96 _public function_ `FName GetRealtimeProfile() const`
- L101 _public function_ `FName GetOfflineProfile() const`
- L107 _public prototype_ `const UE::Ava::FResolvedShaderProfile* FindResolvedShaderProfile(FName InProfileName) const;` — Finds the resolved shader profile for a given profile name
- L111 _protected prototype_ `virtual void PostInitProperties() override;`
- L112 _protected prototype_ `virtual void PostReloadConfig(FProperty* InPropertyThatWasLoaded) override;`
- L114 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L120 _private prototype_ `void RegisterDefaultShaderProfile();` — Add the built-in shader profiles
- L123 _private prototype_ `void ResolveShaderProfiles();` — Resolves all the registered shader profiles to its type pointers
- L126 _private prototype_ `void ResolveShaderProfile(const FAvaShaderProfile& InShaderProfile, TMap<FName, FHashedName>& InOutHashedNames);` — Resolves a single shader profile to its type pointers
- L130 _private member_ `FName RealtimeProfile;` — `UPROPERTY(Config, EditAnywhere, Category="Material Cache")` — Profile to use in realtime (e.g. when playing levels)
- L134 _private member_ `FName OfflineProfile;` — `UPROPERTY(Config, EditAnywhere, Category="Material Cache")` — Profile to use offline (e.g. when preloading levels)
- L138 _private member_ `TArray<FAvaShaderProfile> ShaderProfiles;` — `UPROPERTY(Config, EditAnywhere, Category="Material Cache")` — Shader profiles that can be saved to disk
- L141 _private member_ `TMap<FName, UE::Ava::FResolvedShaderProfile> ResolvedShaderProfiles;` — The saved shader profiles turned into resolved pointers

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Private/AvaMaterialModule.h` (Private)


#### class `FAvaMaterialModule`  
`class FAvaMaterialModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/AvaMaterialBridge.h` (Public)


#### class `UE::Ava::FMaterialBridge`  
`class FMaterialBridge`  
_L58-190_
- desc: Base class that allows interacting with material containers from any type (Actors, ActorComponents, etc.). A Material Bridge allows: 1) Access material slots: - Access can either be to read or write. - Read access allows only getting the material - Write access allows getting the material slot and replacing its material. 2) Apply and store material container state - Prior to replacing materials in a slot, the state of a material container can be stored via StoreState. - The Material Bridge can then revert the material container back to its original state via ApplyState with the data that was stored prior to change. - The expected flow could look like the following: 1) Call StoreState. Caller owns the state data. 2) Call AccessSlots (with write context) and replace slot material with a new one. 3) When needing to revert back, call ApplyState with the state data saved from (1) Things to note: - The Material Bridge does not own material container state data. It can only create and interact with it via Apply/Store. The responsibility of the ownership lies with the caller. - ApplyState and StoreState is only concerned with the state of the material container, not the material itself. For example the parameters of a Material Instance Dynamic or any other property within a material object are not considered.
- L61 _public typedef_ `using FSlotId = FAvaMaterialBridgeSlotId;`
- L62 _public typedef_ `using FReadSlot = FMaterialBridgeReadSlot;`
- L63 _public typedef_ `using FReadSlotOptions = FMaterialBridgeReadSlotOptions;`
- L64 _public typedef_ `using FReadSlotContext = FMaterialBridgeReadSlotContext;`
- L65 _public typedef_ `using FWriteSlot = FMaterialBridgeWriteSlot;`
- L66 _public typedef_ `using FWriteSlotOptions = FMaterialBridgeWriteSlotOptions;`
- L67 _public typedef_ `using FWriteSlotContext = FMaterialBridgeWriteSlotContext;`
- L68 _public typedef_ `using FApplyStateOptions = FMaterialBridgeApplyStateOptions;`
- L69 _public typedef_ `using FApplyStateContext = FMaterialBridgeApplyStateContext;`
- L70 _public typedef_ `using FStoreStateOptions = FMaterialBridgeStoreStateOptions;`
- L71 _public typedef_ `using FStoreStateContext = FMaterialBridgeStoreStateContext;`
- L73 _public prototype_ `virtual ~FMaterialBridge() = default;`
- L76 _public prototype_ `void Initialize(uint32 InPriority);` — Initializes the bridge for use
- L79 _public prototype_ `const UStruct* GetBridgedType() const;` — Retrieves the type that this bridge supports
- L82 _public prototype_ `uint32 GetPriority() const;` — Get the priority of this bridge in relation to other bridges of the same bridged type
- L89 _public prototype_ `bool IsMaterialContainerSupported(FConstDataView InMaterialContainer) const;` — Whether this Material Bridge supports the given Material Container. @param InMaterialContainer a valid material container of the supported type of this material bridge. @return true if this material bridge supports the container, false otherwise.
- L98 _public prototype_ `EControlFlow AccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const;` — Access the found material slots in the given context for read. @param InContext the current context to access materials @param InFunc function to call for each material slot accessed. @param InOptions access options. see FMaterialBridgeReadSlotAccessOptions @return the iteration result of AccessSlots.
- L107 _public prototype_ `EControlFlow AccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const;` — Access the found material slots in the given context for write. @param InContext the current context to access materials. @param InFunc function to call for each material slot accessed. @param InOptions access options. see FMaterialBridgeWriteSlotAccessOptions @return the iteration result of AccessSlots.
- L110 _public prototype_ `bool CanCreateContainerState() const;` — Returns whether this material bridge supports container states
- L113 _public prototype_ `TInstancedStruct<FAvaMaterialContainerState> CreateContainerState() const;` — Creates a material container state instance that can be used for this material bridge
- L122 _public prototype_ `bool ApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const;` — Applies the material container state to the context object. @param InContext context used when applying the container state. see FMaterialBridgeApplyStateContext @param InContainerState const view of the container state. Required to match the container state type of this bridge. @param InOptions additional options to how apply should take place. see FMaterialBridgeApplyStateOptions @return true if the container state was valid and was processed
- L132 _public prototype_ `bool StoreState(const FStoreStateContext& InContext, TNotNull<TInstancedStruct<FAvaMaterialContainerState>*> InOutContainerState, const FStoreStateOptions& InOptions) const;` — Stores the state of the context object in the material container state This overload initializes the container state if it is invalid. @param InContext context used when storing the container state. see FMaterialBridgeStoreStateContext @param InOutContainerState the instanced struct where the container state will be stored @param InOptions additional options to how store should take place. see FMaterialBridgeStoreStateOptions @return true if the container state was valid (or initialized to valid) and was processed
- L141 _public prototype_ `bool StoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const;` — Stores the state of the context object in the material container state @param InContext context used when storing the container state. see FMaterialBridgeStoreStateContext @param InContainerState the container state to store to. Required to match the container state type of this bridge. @param InOptions additional options to how store should take place. see FMaterialBridgeStoreStateOptions @return true if the container state was valid and was processed
- L145 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const = 0;` — Retrieves the type that this bridge supports. Only called once in Initialize()
- L148 _protected function_ `virtual bool OnIsMaterialContainerSupported(FConstDataView InMaterialContainer) const` — Whether this material bridge supports the given material container.
- L154 _protected function_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const` — Accesses the found material slots in the given context for read
- L160 _protected function_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const` — Accesses the found material slots in the given context for write
- L166 _protected function_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const` — Returns the material container state type required by this bridge, if any
- L172 _protected function_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const` — Applies the container state to the context object
- L177 _protected function_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const` — Stores the state of the context object in the container state
- L183 _private member_ `TObjectPtr<const UStruct> BridgedType;` — The type that this Material Bridge works on
- L186 _private member_ `TSubScriptStructOf<FAvaMaterialContainerState> ContainerStateType;` — The material container state type of this bridge, if any
- L189 _private member_ `uint32 Priority = 0;` — The priority of this bridge in relation to other bridges of the same bridged type

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Ava` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/AvaMaterialBridgeLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMaterialBridge, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMaterialBridge, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/AvaMaterialBridgeRegistry.h` (Public)


#### class `UE::Ava::FMaterialBridgeRegistry`  
`class FMaterialBridgeRegistry`  
_L22-44_
- desc: Holds all the Material Bridges to use
- L25 _public prototype_ `static const FMaterialBridgeRegistry& Get();`
- L26 _public prototype_ `static FMaterialBridgeRegistry& GetMutable();`
- L29 _public function_ `template<typename InMaterialBridgeType, typename... InArgTypes> requires (UE::CDerivedFrom<InMaterialBridgeType, UE::Ava::FMaterialBridge>) void Register(uint32 InPriority, InArgTypes&&... InArgs)`
- L35 _public prototype_ `const FMaterialBridge* GetMaterialBridge(FConstDataView InMaterialContainer) const;` — Tries to find the most relevant material bridge for a given material container, returning a null if object is invalid, or if a relevant material bridge was not found.
- L39 _protected prototype_ `void RegisterInternal(TUniquePtr<UE::Ava::FMaterialBridge>&& InMaterialBridge, uint32 InPriority);` — Initializes the material bridge and adds it to this registry
- L43 _private member_ `TMap<TObjectKey<UStruct>, TArray<TUniquePtr<FMaterialBridge>>> RegisteredMaterialBridges;` — Registered material bridges by their supported type

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Ava` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/AvaMaterialContainerState.h` (Public)


#### struct `FAvaMaterialContainerState`  
`struct FAvaMaterialContainerState`  
_L9-12_
- reflection: `USTRUCT()`
- desc: Base struct for all material container states

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Common/AvaActorMaterialBridge.h` (Public)


#### struct `FAvaActorMaterialContainerStateComponent`  
`struct FAvaActorMaterialContainerStateComponent`  
_L15-35_
- reflection: `USTRUCT()`
- desc: Struct holding the path for each actor component and the container state data mapped to it
- L20 _public prototype_ `void SetComponent(UActorComponent* InComponent);` — Sets the main component of this material container state
- L23 _public prototype_ `UActorComponent* ResolveComponent(const AActor* InActor) const;` — Tries to resolve component by first resolving the weak ptr, or else using the component path and the given actor
- L27 _public member_ `FString Path;` — `UPROPERTY()` — Path to the actor component
- L30 _public member_ `mutable TWeakObjectPtr<UActorComponent> ComponentWeak;` — Resolved component
- L34 _public member_ `TInstancedStruct<FAvaMaterialContainerState> ContainerState;` — `UPROPERTY()` — The container state data for the component. The type varies as each component could have a different Material Bridge

#### struct `FAvaActorMaterialContainerState`  
`struct FAvaActorMaterialContainerState : public FAvaMaterialContainerState`  
_L39-46_
- reflection: `USTRUCT()`
- inherits: `FAvaMaterialContainerState`
- desc: Material container state for actors
- L45 _public member_ `TArray<FAvaActorMaterialContainerStateComponent> Components;` — `UPROPERTY()` — All the actor component data found for the actor mapped to this data

#### class `UE::Ava::FActorMaterialBridge`  
`class FActorMaterialBridge : public FMaterialBridge`  
_L52-66_
- inherits: `FMaterialBridge`
- desc: Material Bridge for Actors
- L55 _public typedef_ `using FContainerState = FAvaActorMaterialContainerState;`
- L59 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L60 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L61 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`
- L62 _protected prototype_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const override;`
- L63 _protected prototype_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const override;`
- L64 _protected prototype_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Common/AvaDecalComponentMaterialBridge.h` (Public)


#### struct `FAvaDecalComponentMaterialContainerState`  
`struct FAvaDecalComponentMaterialContainerState : public FAvaMaterialContainerState`  
_L15-22_
- reflection: `USTRUCT()`
- inherits: `FAvaMaterialContainerState`
- desc: Material container state for decal components
- L21 _public member_ `TObjectPtr<UMaterialInterface> DecalMaterial;` — `UPROPERTY()` — The decal material of the component

#### class `UE::Ava::FDecalComponentMaterialBridge`  
`class FDecalComponentMaterialBridge : public FMaterialBridge`  
_L28-42_
- inherits: `FMaterialBridge`
- desc: Material Bridge for Decal Components
- L31 _public typedef_ `using FContainerState = FAvaDecalComponentMaterialContainerState;`
- L35 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L36 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L37 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`
- L38 _protected prototype_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const override;`
- L39 _protected prototype_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const override;`
- L40 _protected prototype_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Common/AvaLevelMaterialBridge.h` (Public)


#### class `UE::Ava::FLevelMaterialBridge`  
`class FLevelMaterialBridge : public FMaterialBridge`  
_L18-26_
- inherits: `FMaterialBridge`
- desc: Material Bridge for Levels NOTE: Does not support Material Container State as it's probably better for users to do it per actor on-demand than to store/instantiate an entire level's material data. If it's ever needed, functionality to do this incrementally would be needed so as not to stall on one frame while creating large amounts of data.
- L22 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L23 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L24 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Common/AvaPrimitiveComponentMaterialBridge.h` (Public)


#### struct `FAvaPrimitiveComponentMaterialContainerState`  
`struct FAvaPrimitiveComponentMaterialContainerState : public FAvaMaterialContainerState`  
_L15-22_
- reflection: `USTRUCT()`
- inherits: `FAvaMaterialContainerState`
- desc: Material container state for primitive components
- L21 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY()` — Materials found via the UPrimitiveComponent material api

#### class `UE::Ava::FPrimitiveComponentMaterialBridge`  
`class FPrimitiveComponentMaterialBridge : public FMaterialBridge`  
_L27-41_
- inherits: `FMaterialBridge`
- desc: Material Bridge for Primitive Components
- L30 _public typedef_ `using FContainerState = FAvaPrimitiveComponentMaterialContainerState;`
- L34 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L35 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L36 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`
- L37 _protected prototype_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const override;`
- L38 _protected prototype_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const override;`
- L39 _protected prototype_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Common/AvaStaticMeshMaterialBridge.h` (Public)


#### class `UE::Ava::FStaticMeshMaterialBridge`  
`class FStaticMeshMaterialBridge : public FMaterialBridge`  
_L16-24_
- inherits: `FMaterialBridge`
- desc: Material Bridge for Static Meshes Only deals with the Static Mesh's static materials.
- L20 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L21 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L22 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Context/AvaMaterialBridgeApplyStateContext.h` (Public)


#### struct `UE::Ava::FMaterialBridgeApplyStateOptions`  
`struct FMaterialBridgeApplyStateOptions : public FMaterialBridgeBaseOptions`  
_L16-18_
- inherits: `FMaterialBridgeBaseOptions`
- desc: Additional options when applying state to a material container

#### struct `UE::Ava::TMaterialBridgeContextFlags`  
`template<> struct TMaterialBridgeContextFlags<FMaterialBridgeApplyStateContext> : public TMaterialBridgeContextFlagsBase<FMaterialBridgeApplyStateContext>`  
_L21-27_
- inherits: `TMaterialBridgeContextFlagsBase<FMaterialBridgeApplyStateContext>`

#### enum `UE::Ava::TMaterialBridgeContextFlags::(anonymous)`  
``  
_L24-26_

#### class `UE::Ava::FMaterialBridgeApplyStateContext`  
`class FMaterialBridgeApplyStateContext : public TMaterialBridgeContext<FMaterialBridgeApplyStateContext>`  
_L30-34_
- inherits: `TMaterialBridgeContext<FMaterialBridgeApplyStateContext>`
- desc: Short-lived context information when applying state to a material container

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Ava` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Ava` (scope `UE`)
- L25 _enumerator_ `WithConstMaterialContainer = false` (scope `UE::Ava::TMaterialBridgeContextFlags::__anon611f847a0103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Context/AvaMaterialBridgeContext.h` (Public)


#### struct `UE::Ava::FMaterialBridgeBaseOptions`  
`struct FMaterialBridgeBaseOptions`  
_L20-26_
- desc: Base for all options structs
- L22 _public prototype_ `FMaterialBridgeBaseOptions();`
- L25 _public member_ `TNotNull<const FMaterialBridgeRegistry*> MaterialBridgeRegistry;` — The registry used to get material bridges. Defaults to the global registry.

#### struct `UE::Ava::TMaterialBridgeContextFlagsBase`  
`template<typename InContextType> struct TMaterialBridgeContextFlagsBase`  
_L29-35_

#### enum `UE::Ava::TMaterialBridgeContextFlagsBase::(anonymous)`  
``  
_L32-34_

#### struct `UE::Ava::TMaterialBridgeContextFlags`  
`template<typename InContextType> struct TMaterialBridgeContextFlags : public TMaterialBridgeContextFlagsBase<InContextType>`  
_L38-40_
- inherits: `TMaterialBridgeContextFlagsBase<InContextType>`

#### class `UE::Ava::TMaterialBridgeContext`  
`template<typename InContextType> class TMaterialBridgeContext`  
_L44-70_
- desc: Base context class containing common functionality shared among all material bridge contexts
- L47 _public member_ `static constexpr bool bWithConstMaterialContainer = TMaterialBridgeContextFlags<InContextType>::WithConstMaterialContainer;`
- L49 _public typedef_ `using UObjectType = std::conditional_t<bWithConstMaterialContainer, const UObject, UObject>;`
- L50 _public typedef_ `using FDataViewType = std::conditional_t<bWithConstMaterialContainer, FConstDataView, FDataView>;`
- L52 _public prototype_ `TMaterialBridgeContext() = default;`
- L54 _public prototype_ `explicit TMaterialBridgeContext(FDataViewType InMaterialContainer);`
- L55 _public prototype_ `explicit TMaterialBridgeContext(FDataViewType InMaterialContainer, TNotNull<const InContextType*> InParentContext);`
- L56 _public prototype_ `explicit TMaterialBridgeContext(UObjectType* InMaterialContainer);`
- L57 _public prototype_ `explicit TMaterialBridgeContext(UObjectType* InMaterialContainer, TNotNull<const InContextType*> InParentContext);`
- L60 _public prototype_ `const InContextType& GetTopmostContext() const;` — Gets the topmost slot context in the context chain
- L63 _public prototype_ `UObjectType* GetMaterialContainerObject() const;` — Gets the first material container that is a UObject
- L66 _public member_ `FDataViewType MaterialContainer;` — The object containing the material
- L69 _public member_ `const InContextType* ParentContext = nullptr;` — Parent context. Non-null if in a nested call. Should always be valid checked

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Ava` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Ava` (scope `UE`)
- L33 _enumerator_ `WithConstMaterialContainer = true` (scope `UE::Ava::TMaterialBridgeContextFlagsBase::__anon8d6ffb130103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Context/AvaMaterialBridgeReadSlotContext.h` (Public)


#### struct `UE::Ava::FMaterialBridgeReadSlotOptions`  
`struct FMaterialBridgeReadSlotOptions : public FMaterialBridgeBaseOptions`  
_L18-28_
- inherits: `FMaterialBridgeBaseOptions`
- desc: Options to how read access should take place
- L21 _public member_ `TDelegate<EControlFlow(const FMaterialBridgeReadSlotContext&)> OnContainerPendingCompletion;` — Delegate called when a container is not yet complete and cannot access its materials. Only called when bTrySkipWaitOnContainerCompletion is true.
- L27 _public member_ `bool bTrySkipWaitOnContainerCompletion = false;` — Whether to try to skip wait for container completion to access its materials. 'Try' because there is no guarantee that all material containers have an API that determines whether accessing a material will cause a wait.

#### class `UE::Ava::FMaterialBridgeReadSlotContext`  
`class FMaterialBridgeReadSlotContext : public TMaterialBridgeContext<FMaterialBridgeReadSlotContext>`  
_L31-35_
- inherits: `TMaterialBridgeContext<FMaterialBridgeReadSlotContext>`
- desc: Short-lived context information when accessing a material slot for read

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Ava` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Context/AvaMaterialBridgeStoreStateContext.h` (Public)


#### struct `UE::Ava::FMaterialBridgeStoreStateOptions`  
`struct FMaterialBridgeStoreStateOptions : public FMaterialBridgeBaseOptions`  
_L11-13_
- inherits: `FMaterialBridgeBaseOptions`
- desc: Additional options when applying/storing material container state

#### class `UE::Ava::FMaterialBridgeStoreStateContext`  
`class FMaterialBridgeStoreStateContext : public TMaterialBridgeContext<FMaterialBridgeStoreStateContext>`  
_L16-20_
- inherits: `TMaterialBridgeContext<FMaterialBridgeStoreStateContext>`
- desc: Short-lived context information when storing the state of a material container

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Context/AvaMaterialBridgeWriteSlotContext.h` (Public)


#### struct `UE::Ava::FMaterialBridgeWriteSlotOptions`  
`struct FMaterialBridgeWriteSlotOptions : public FMaterialBridgeBaseOptions`  
_L18-28_
- inherits: `FMaterialBridgeBaseOptions`
- desc: Options used when accessing a slot for write
- L21 _public member_ `TDelegate<EControlFlow(const FMaterialBridgeWriteSlotContext&)> OnContainerPendingCompletion;` — Delegate called when a container is not yet complete and cannot access its materials. Only called when bTrySkipWaitOnContainerCompletion is true.
- L27 _public member_ `bool bTrySkipWaitOnContainerCompletion = false;` — Whether to try to skip wait for container completion to access its materials. 'Try' because there is no guarantee that all material containers have an API that determines whether accessing a material will cause a wait.

#### struct `UE::Ava::TMaterialBridgeContextFlags`  
`template<> struct TMaterialBridgeContextFlags<FMaterialBridgeWriteSlotContext> : public TMaterialBridgeContextFlagsBase<FMaterialBridgeWriteSlotContext>`  
_L31-37_
- inherits: `TMaterialBridgeContextFlagsBase<FMaterialBridgeWriteSlotContext>`

#### enum `UE::Ava::TMaterialBridgeContextFlags::(anonymous)`  
``  
_L34-36_

#### class `UE::Ava::FMaterialBridgeWriteSlotContext`  
`class FMaterialBridgeWriteSlotContext : public TMaterialBridgeContext<FMaterialBridgeWriteSlotContext>`  
_L40-44_
- inherits: `TMaterialBridgeContext<FMaterialBridgeWriteSlotContext>`
- desc: Short-lived context information when accessing a material slot for write

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Ava` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Ava` (scope `UE`)
- L35 _enumerator_ `WithConstMaterialContainer = false` (scope `UE::Ava::TMaterialBridgeContextFlags::__anonfbf40ce00103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Slot/AvaMaterialBridgeFeature.h` (Public)


#### struct `FAvaMaterialBridgeFeature`  
`struct FAvaMaterialBridgeFeature`  
_L9-12_
- reflection: `USTRUCT()`
- desc: Base struct for all slot features

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Slot/AvaMaterialBridgeReadSlot.h` (Public)


#### class `UE::Ava::FMaterialBridgeReadSlot`  
`class FMaterialBridgeReadSlot : public FMaterialBridgeSlot`  
_L14-18_
- inherits: `FMaterialBridgeSlot`
- desc: Short-lived representation of an accessed material slot for read

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Slot/AvaMaterialBridgeSlot.h` (Public)


#### class `UE::Ava::FMaterialBridgeSlot`  
`class FMaterialBridgeSlot`  
_L16-44_
- desc: Base slot class for both the read and write slot
- L19 _public typedef_ `using FSlotId = FAvaMaterialBridgeSlotId;`
- L22 _public prototype_ `explicit FMaterialBridgeSlot(UMaterialInterface* InMaterial, const FSlotId& InSlotId);` — Constructor for when a material slot is indexed
- L24 _public prototype_ `virtual ~FMaterialBridgeSlot() = default;`
- L27 _public function_ `UMaterialInterface* GetMaterial() const` — Gets the material for this slot
- L33 _public function_ `const FSlotId& GetSlotId() const` — Gets the identifier for this slot
- L40 _protected member_ `TObjectPtr<UMaterialInterface> Material;` — Material in this slot
- L43 _protected member_ `FSlotId SlotId;` — Identifier for the slot within its container

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Slot/AvaMaterialBridgeSlotId.h` (Public)


#### struct `FAvaMaterialBridgeSlotId`  
`struct FAvaMaterialBridgeSlotId`  
_L11-46_
- reflection: `USTRUCT()`
- desc: Holds the data to identify a slot within a material container
- L15 _public prototype_ `FAvaMaterialBridgeSlotId() = default;`
- L18 _public prototype_ `explicit FAvaMaterialBridgeSlotId(int32 InSlotIndex);` — Constructor for when a material slot can be identified by its index
- L21 _public prototype_ `explicit FAvaMaterialBridgeSlotId(FName InSlotName);` — Constructor for when a material slot can be identified by an FName
- L24 _public prototype_ `explicit FAvaMaterialBridgeSlotId(FName InSlotName, int32 InSlotIndex);` — Constructor for when a material slot can be identified by a name and index
- L27 _public prototype_ `bool IsValid() const;` — Whether the slot id is valid (i.e. not the defaults)
- L29 _public function_ `bool operator==(const FAvaMaterialBridgeSlotId& InOther) const`
- L42 _private member_ `FName Name;` — Slot name, if any
- L45 _private member_ `int32 Index = INDEX_NONE;` — Slot index, if any

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L35 _function_ `friend uint32 GetTypeHash(const FAvaMaterialBridgeSlotId& InSlotId)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Slot/AvaMaterialBridgeWriteSlot.h` (Public)


#### class `UE::Ava::FMaterialBridgeWriteSlot`  
`class FMaterialBridgeWriteSlot : public FMaterialBridgeSlot`  
_L16-49_
- inherits: `FMaterialBridgeSlot`
- desc: Base struct for short-lived representation of an accessed material slot for write
- L22 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial);` — Sets the new material for the slot
- L29 _public prototype_ `bool RequestFeature(TConstStructView<FAvaMaterialBridgeFeature> InFeature);` — Requests a feature for this material slot @param InFeature the feature to request @return true if the feature was recognized by the slot
- L33 _protected prototype_ `void SetMaterialInternal(UMaterialInterface* InMaterial);` — Sets the material property directly without calling the change notification
- L36 _protected function_ `virtual void OnMaterialChanged()` — Notifies when a new material has been set for the slot
- L45 _protected function_ `virtual bool OnFeatureRequest(TConstStructView<FAvaMaterialBridgeFeature> InFeature)` — Requests a feature for this material slot @param InFeature the feature to request @return true if the feature was recognized by the slot

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHEMATERIAL_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Public/MaterialBridge/Slot/CommonFeatures/AvaMaterialBridgeBlendModeFeature.h` (Public)


#### struct `FAvaMaterialBridgeBlendModeFeature`  
`struct FAvaMaterialBridgeBlendModeFeature : public FAvaMaterialBridgeFeature`  
_L11-18_
- reflection: `USTRUCT()`
- inherits: `FAvaMaterialBridgeFeature`
- desc: Feature representing the blend mode to configure for the slot
- L17 _public member_ `TEnumAsByte<EBlendMode> BlendMode = EBlendMode::BLEND_Opaque;` — `UPROPERTY()` — The desired blend mode for the slot
