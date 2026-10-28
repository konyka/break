# Plugins / ColorCorrectRegions

- module root: `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions`
- headers: 9; symbols: 234
- symbol kinds: class=20, delegate=1, enum=6, enumerator=22, function=23, member=66, prototype=89, struct=2, typedef=4, union=1
- PrivateDependencyModuleNames: ConcertSyncClient, Core, CoreUObject, EditorWidgets, Engine, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: DisplayClusterLightCardExtender

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.h` (Private)


#### class `FColorCorrectRegionsPostProcessMaterialShader`  
`class FColorCorrectRegionsPostProcessMaterialShader : public FGlobalShader`  
_L98-114_
- inherits: `FGlobalShader`
- L101 _public typedef_ `using FParameters = FCCRShaderInputParameters;`
- L102 _public prototype_ `SHADER_USE_PARAMETER_STRUCT_WITH_LEGACY_BASE(FColorCorrectRegionsPostProcessMaterialShader, FGlobalShader);`
- L104 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L109 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FColorCorrectRegionMaterialVS`  
`class FColorCorrectRegionMaterialVS : public FColorCorrectRegionsPostProcessMaterialShader`  
_L116-130_
- inherits: `FColorCorrectRegionsPostProcessMaterialShader`
- L119 _public prototype_ `DECLARE_GLOBAL_SHADER(FColorCorrectRegionMaterialVS);`
- L121 _public prototype_ `FColorCorrectRegionMaterialVS() = default;`
- L122 _public function_ `FColorCorrectRegionMaterialVS(const ShaderMetaType::CompiledShaderInitializerType & Initializer) : FColorCorrectRegionsPostProcessMaterialShader(Initializer)`
- L126 _public function_ `void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FSceneView& View)`

#### class `FColorCorrectGenericPS`  
`class FColorCorrectGenericPS : public FColorCorrectRegionsPostProcessMaterialShader`  
_L132-157_
- inherits: `FColorCorrectRegionsPostProcessMaterialShader`
- L148 _public prototype_ `FColorCorrectGenericPS() = default;`
- L149 _public function_ `FColorCorrectGenericPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FColorCorrectRegionsPostProcessMaterialShader(Initializer)`
- L153 _public function_ `void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FSceneView& View)`

#### enum `FColorCorrectGenericPS::ETemperatureType`  
`enum class ETemperatureType : uint8`  
_L135-142_
- L137 _public enumerator_ `LegacyTemperature = static_cast<uint8>(EColorCorrectRegionTemperatureType::LegacyTemperature)`
- L138 _public enumerator_ `WhiteBalance = static_cast<uint8>(EColorCorrectRegionTemperatureType::WhiteBalance)`
- L139 _public enumerator_ `ColorTemperature = static_cast<uint8>(EColorCorrectRegionTemperatureType::ColorTemperature)`
- L140 _public enumerator_ `Disabled`
- L141 _public enumerator_ `MAX`

#### class `FColorCorrectRegionMaterialPS`  
`class FColorCorrectRegionMaterialPS : public FColorCorrectGenericPS`  
_L159-173_
- inherits: `FColorCorrectGenericPS`
- L163 _public prototype_ `DECLARE_GLOBAL_SHADER(FColorCorrectRegionMaterialPS);`
- L167 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FShaderType, FTemperatureType, FAdvancedShader, FStencilEnabled>;`
- L169 _public prototype_ `FColorCorrectRegionMaterialPS() = default;`
- L170 _public function_ `FColorCorrectRegionMaterialPS(const ShaderMetaType::CompiledShaderInitializerType & Initializer) : FColorCorrectGenericPS(Initializer)`

#### class `FColorCorrectWindowMaterialPS`  
`class FColorCorrectWindowMaterialPS : public FColorCorrectGenericPS`  
_L176-190_
- inherits: `FColorCorrectGenericPS`
- L180 _public prototype_ `DECLARE_GLOBAL_SHADER(FColorCorrectWindowMaterialPS);`
- L184 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FShaderType, FTemperatureType, FAdvancedShader, FStencilEnabled>;`
- L186 _public prototype_ `FColorCorrectWindowMaterialPS() = default;`
- L187 _public function_ `FColorCorrectWindowMaterialPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FColorCorrectGenericPS(Initializer)`

#### class `FColorCorrectScreenPassVS`  
`class FColorCorrectScreenPassVS : public FGlobalShader`  
_L193-202_
- inherits: `FGlobalShader`
- desc: The vertex shader used by DrawScreenPass to draw a rectangle.
- L196 _public prototype_ `DECLARE_GLOBAL_SHADER(FColorCorrectScreenPassVS);`
- L198 _public prototype_ `FColorCorrectScreenPassVS() = default;`
- L199 _public function_ `FColorCorrectScreenPassVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`

#### class `FClearRectPS`  
`class FClearRectPS : public FGlobalShader`  
_L205-219_
- inherits: `FGlobalShader`
- desc: A simple shader that outputs (0.,0.,0.,0.)
- L207 _private prototype_ `DECLARE_GLOBAL_SHADER(FClearRectPS);`
- L208 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FClearRectPS, FGlobalShader);`
- L210 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FCCRStencilMergerVS`  
`class FCCRStencilMergerVS : public FGlobalShader`  
_L223-232_
- inherits: `FGlobalShader`
- desc: Vertex shader to rasterize obstructive CCR Plane.
- L226 _public prototype_ `DECLARE_GLOBAL_SHADER(FCCRStencilMergerVS);`
- L228 _public prototype_ `FCCRStencilMergerVS() = default;`
- L229 _public function_ `FCCRStencilMergerVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`

#### class `FCCRStencilMergerPS`  
`class FCCRStencilMergerPS : public FGlobalShader`  
_L235-253_
- inherits: `FGlobalShader`
- desc: Pixel shader to rasterize obstructive CCR Plane.
- L237 _private prototype_ `DECLARE_GLOBAL_SHADER(FCCRStencilMergerPS);`
- L238 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FCCRStencilMergerPS, FGlobalShader);`
- L240 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsSceneViewExtension.h` (Private)


#### class `FColorCorrectRegionsSceneViewExtension`  
`class FColorCorrectRegionsSceneViewExtension : public FWorldSceneViewExtension`  
_L11-27_
- inherits: `FWorldSceneViewExtension`
- L14 _public prototype_ `FColorCorrectRegionsSceneViewExtension(const FAutoRegister& AutoRegister, UWorld* InWorld, UColorCorrectRegionsSubsystem* InWorldSubsystem);`
- L17 _public function_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override`
- L18 _public function_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override`
- L19 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L20 _public prototype_ `virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;`
- L24 _public prototype_ `void Invalidate();` — Called when owning subsystem needs to release this extension.
- L26 _private member_ `UColorCorrectRegionsSubsystem* WorldSubsystem;`

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsStencilManager.h` (Private)


#### class `FColorCorrectRegionsStencilManager`  
`class FColorCorrectRegionsStencilManager`  
_L10-22_
- L13 _public prototype_ `static void AssignStencilNumberToActorForSelectedRegion(UWorld* CurrentWorld, AColorCorrectRegion* Region, TSoftObjectPtr<AActor> ActorToAssignStencilTo, bool bIgnoreUserNotifications, bool bSoftAssign);`
- L14 _public prototype_ `static void RemoveStencilNumberForSelectedRegion(UWorld* CurrentWorld, AColorCorrectRegion* Region);`
- L15 _public prototype_ `static void OnCCRRemoved(UWorld* CurrentWorld, AColorCorrectRegion* Region);`
- L16 _public prototype_ `static void ClearInvalidActorsForSelectedRegion(AColorCorrectRegion* Region);`
- L17 _public prototype_ `static void AssignStencilIdsToAllActorsForCCR(UWorld* CurrentWorld, AColorCorrectRegion* Region, bool bIgnoreUserNotifications, bool bSoftAssign);`
- L18 _public prototype_ `static void CleanActor(AActor* Actor);`
- L21 _public prototype_ `static void CheckAssignedActorsValidity(AColorCorrectRegion* Region);` — Runs over all actors assigned to the selected Region and makes sure that Stencil Ids match the ones assigned to it.

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsSubsystem.h` (Private)


#### class `UColorCorrectRegionsSubsystem`  
`class UColorCorrectRegionsSubsystem : public UTickableWorldSubsystem`  
_L39-122_
- reflection: `UCLASS()`
- inherits: `UTickableWorldSubsystem`
- desc: World Subsystem responsible for managing AColorCorrectRegion classes in level. This subsystem handles: Level Loaded, Undo/Redo, Added to level, Removed from level events. Unfortunately AActor class itself is not aware of when it is added/removed, Undo/Redo etc in the level. This is the only way (that we found) that was handling all region aggregation cases in more or less efficient way. Covered cases: Region added to a level, deleted from level, level loaded, undo, redo, level closed, editor closed: World subsystem keeps track of all Regions in a level via three events OnLevelActorAdded and OnLevelActorDeleted. Actor classes are unaware of when they are added/deleted/undo/redo etc in the level, therefore this is the best place to manage this. Alternative strategies (All tested): World's AddOnActorSpawnedHandler. Flawed. Invoked in some cases we don't need, but does not get called during UNDO/REDO AActor's PostSpawnInitialize, PostActorCreated  and OnConstruction are also flawed. AActor does not have an internal event for when its deleted (EndPlay is the closest we have).
- L45 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Subsystem Init/Deinit
- L46 _public prototype_ `virtual void Deinitialize() override;`
- L48 _public function_ `virtual bool IsTickableInEditor() const`
- L49 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L50 _public function_ `virtual TStatId GetStatId() const override`
- L55 _public prototype_ `void OnActorSpawned(AActor* InActor);` — A callback for CC Region creation.
- L58 _public prototype_ `void OnActorDeleted(AActor* InActor, bool bClearStencilIdValues);` — A callback for CC Region deletion.
- L61 _public function_ `void OnDuplicateActorsBegin()` — Called when duplication process is started in the level.
- L64 _public prototype_ `void OnDuplicateActorsEnd();` — Called when duplication process is ended in the level.
- L67 _public prototype_ `void AssignStencilIdsToPerActorCC(AColorCorrectRegion* Region, bool bIgnoreUserNotificaion = false, bool bSoftAssign = false);` — Handles Stencil Ids for the selected CCR and corresponding actor.
- L70 _public prototype_ `void ClearStencilIdsToPerActorCC(AColorCorrectRegion* Region);` — Handles removal of Stencil Ids for the selected CCR.
- L73 _public prototype_ `void CheckAssignedActorsValidity(AColorCorrectRegion* Region);` — Handles cases when stencil Id has been changed from outside by the user manually.
- L80 _public prototype_ `void NotifyPerActorCCChanged(AColorCorrectRegion* Region);` — Notifies connected multi-user clients that per-actor CC stencil assignment changed for the given region. Called after local stencil operations complete. No-op when no Concert session is active or in non-editor builds.
- L85 _private prototype_ `void RefreshRegions();` — Repopulates array of region actors.
- L91 _private prototype_ `void TransferStates();` — Copy states required for rendering to be consumed by Scene view extension to render all active CCRs and CCWs.
- L96 _private member_ `TArray<TWeakObjectPtr<AColorCorrectRegion>> RegionsPriorityBased;` — Stores pointers to ColorCorrectRegion Actors that use priority for sorting.
- L98 _private member_ `TArray<TWeakObjectPtr<AColorCorrectRegion>> RegionsDistanceBased;` — Stores pointers to ColorCorrectRegion Actors that are based on distance from camera.
- L102 _private member_ `TArray<FColorCorrectRenderProxyPtr> ProxiesPriorityBased;` — Proxies to be used exclusively on render thread. Copies of the state of CC Actors sorted by priority.
- L104 _private member_ `TArray<FColorCorrectRenderProxyPtr> ProxiesDistanceBased;` — Proxies to be used exclusively on render thread. Copies of the state of CC Actors sorted by distance.
- L106 _private member_ `TSharedPtr< class FColorCorrectRegionsSceneViewExtension, ESPMode::ThreadSafe > PostProcessSceneViewExtension;`
- L109 _private member_ `bool bDuplicationStarted = false;` — This is to handle actor duplication for Per Actor CC.
- L110 _private member_ `TArray<AActor*> DuplicatedActors;`
- L113 _private member_ `float TimeSinceLastValidityCheck = 0;` — This is for optimization purposes that would let us check assigned actors component's stencil ids every once in a while.
- L117 _private member_ `TUniquePtr<FCCRMultiUserManager> MultiUserManager;` — Sends Concert custom events when Per Actor CC assignment changes. Null when Concert is unavailable.

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/MultiUser/ColorCorrectRegionsMultiUserManager.h` (Private)


#### class `FCCRMultiUserManager`  
`class FCCRMultiUserManager`  
_L29-58_
- desc: Manages multi-user synchronization of per-actor CC stencil ID assignments. When the per-actor CC AffectedActors list changes on one machine, this manager sends a FConcertCCRPerActorAssignmentEvent Concert custom event. Passive clients in the session receive the event and re-apply stencil assignments immediately rather than waiting for the subsystem tick to detect the missing PerAffectedActorStencilData. Owned by UColorCorrectRegionsSubsystem; lifetime is aligned with the subsystem.
- L32 _public prototype_ `explicit FCCRMultiUserManager(UColorCorrectRegionsSubsystem* InSubsystem);`
- L33 _public prototype_ `~FCCRMultiUserManager();`
- L40 _public prototype_ `void SendPerActorAssignmentEvent(AColorCorrectRegion* Region);` — Sends a Concert custom event to all connected clients indicating that per-actor CC stencil assignment changed for the given region. Should be called after local stencil assignment is complete. Does nothing when no Concert session is active.
- L43 _private prototype_ `void OnSessionStartup(TSharedRef<IConcertClientSession> Session);`
- L44 _private prototype_ `void OnSessionShutdown(TSharedRef<IConcertClientSession> Session);`
- L45 _private prototype_ `void OnSessionConnectionChanged(IConcertClientSession& Session, EConcertConnectionStatus ConnectionStatus);`
- L48 _private prototype_ `void HandlePerActorAssignmentEvent( const FConcertSessionContext& Context, const FConcertCCRPerActorAssignmentEvent& Event);` — Called when a remote client sends a FConcertCCRPerActorAssignmentEvent.
- L52 _private member_ `TWeakObjectPtr<UColorCorrectRegionsSubsystem> WeakSubsystem;`
- L53 _private member_ `TWeakPtr<IConcertClientSession> WeakSession;`
- L54 _private member_ `TWeakPtr<IConcertClient> ConcertClient;`
- L55 _private member_ `FDelegateHandle SessionStartupHandle;`
- L56 _private member_ `FDelegateHandle SessionShutdownHandle;`
- L57 _private member_ `FDelegateHandle SessionConnectionChangedHandle;`

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/MultiUser/ColorCorrectRegionsSyncData.h` (Private)


#### struct `FConcertCCRPerActorAssignmentEvent`  
`struct FConcertCCRPerActorAssignmentEvent`  
_L18-29_
- reflection: `USTRUCT()`
- desc: Concert custom event sent when the per-actor CC AffectedActors list changes on a Color Correction Actor. The event is self-contained: it carries the full current AffectedActors state so the receiving client can apply stencil assignments immediately without waiting for Concert's property transaction to arrive and update AffectedActors first.
- L24 _public member_ `FSoftObjectPath CCRActorPath;` — `UPROPERTY()` — Soft path to the CCR actor whose per-actor CC assignment changed.
- L28 _public member_ `TArray<FSoftObjectPath> AffectedActors;` — `UPROPERTY()` — Full AffectedActors list as it stands on the sending client after the change.

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Public/ColorCorrectRegion.h` (Public)


#### enum `EColorCorrectRegionsType`  
`enum class EColorCorrectRegionsType : uint8`  
_L22-29_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Sphere UMETA(DisplayName = "Sphere")`
- L25 _public enumerator_ `Box UMETA(DisplayName = "Box")`
- L26 _public enumerator_ `Cylinder UMETA(DisplayName = "Cylinder")`
- L27 _public enumerator_ `Cone UMETA(DisplayName = "Cone")`
- L28 _public enumerator_ `MAX`

#### enum `EColorCorrectWindowType`  
`enum class EColorCorrectWindowType : uint8`  
_L32-37_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `Square UMETA(DisplayName = "Square")`
- L35 _public enumerator_ `Circle UMETA(DisplayName = "Circle")`
- L36 _public enumerator_ `MAX`

#### enum `EColorCorrectRegionTemperatureType`  
`enum class EColorCorrectRegionTemperatureType : uint8`  
_L40-46_
- reflection: `UENUM(BlueprintType)`
- L42 _public enumerator_ `LegacyTemperature UMETA(DisplayName = "Temperature (Legacy)")`
- L43 _public enumerator_ `WhiteBalance UMETA(DisplayName = "White Balance")`
- L44 _public enumerator_ `ColorTemperature UMETA(DisplayName = "Color Temperature")`
- L45 _public enumerator_ `MAX`

#### enum `EColorCorrectRegionStencilType`  
`enum class EColorCorrectRegionStencilType : uint8`  
_L49-54_
- reflection: `UENUM(BlueprintType)`
- L51 _public enumerator_ `ExcludeStencil UMETA(DisplayName = "Exclude Selected Actors")`
- L52 _public enumerator_ `IncludeStencil UMETA(DisplayName = "Affect Only Selected Actors")`
- L53 _public enumerator_ `MAX`

#### class `FStencilData`  
`class FStencilData`  
_L56-60_
- L59 _public member_ `uint32 AssignedStencil = 0;`

#### struct `FColorCorrectRenderProxy`  
`struct FColorCorrectRenderProxy`  
_L63-110_
- desc: A state to store a copy of CCR properties to be used on render thread.
- L71 _public member_ `EProxyType ProxyType;`
- L79 _public member_ `int32 Priority;` — CCR Properties
- L80 _public member_ `float Intensity;`
- L81 _public member_ `float Inner;`
- L82 _public member_ `float Outer;`
- L83 _public member_ `float Falloff;`
- L84 _public member_ `bool Invert;`
- L85 _public member_ `EColorCorrectRegionTemperatureType TemperatureType;`
- L86 _public member_ `float Temperature;`
- L87 _public member_ `float Tint;`
- L88 _public member_ `FColorGradingSettings ColorGradingSettings;`
- L90 _public member_ `bool bEnablePerActorCC;`
- L96 _public member_ `TArray<uint32> StencilIds;` — A list of actors that need to be excluded or included from color correction to be used on render thread. This list is populated during engine tick and populated with Stencil Ids from Primitive Components of AffectedActors. The main reason for this is accessing Primitive Components is not thread-safe and should be accessed on Game thread.
- L97 _public member_ `EColorCorrectRegionStencilType PerActorColorCorrection;`
- L99 _public member_ `TWeakObjectPtr<UWorld> World;`
- L100 _public member_ `FVector BoxOrigin;`
- L101 _public member_ `FVector BoxExtent;`
- L103 _public member_ `FVector3f ActorLocation;`
- L104 _public member_ `FVector3f ActorRotation;`
- L105 _public member_ `FVector3f ActorScale;`
- L107 _public member_ `FPrimitiveComponentId FirstPrimitiveId;`
- L109 _public member_ `bool bIsActiveThisFrame;`

#### enum `FColorCorrectRenderProxy::EProxyType`  
`enum EProxyType`  
_L65-69_
- L67 _public enumerator_ `PriorityBased`
- L68 _public enumerator_ `DistanceBased`

#### union `FColorCorrectRenderProxy::(anonymous)`  
`union`  
_L73-76_

#### class `AColorCorrectRegion`  
`class AColorCorrectRegion : public AActor, public IDisplayClusterStageActor`  
_L121-399_
- reflection: `UCLASS(Blueprintable, NotPlaceable, Abstract, HideCategories=(Actor, HLOD, Collision, Replication, Cooking, Input, DataLayers, Physics, Streaming, WorldPartition))`
- inherits: `AActor,IDisplayClusterStageActor`
- desc: An instance of Color Correction Region. Used to aggregate all active regions. This actor is aggregated by ColorCorrectRegionsSubsystem on Tick. AActor class itself is not aware of when it is added/removed, Undo/Redo etc in the Editor. More information in ColorCorrectRegionsSubsytem.h
- L126 _public member_ `TArray<TObjectPtr<UStaticMeshComponent>> MeshComponents;` — `UPROPERTY()`
- L133 _public member_ `EColorCorrectRegionsType Type;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Region")` — Region type.
- L141 _public member_ `int32 Priority;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Region")` — Render priority/order. The higher the number the later region will be applied. A region with Priority 1 will be rendered before a region with Priority 10. This property is hidden if priority is determined by distance from the camera (When Window CCR is being used).
- L145 _public member_ `float Intensity;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Region", meta = (UIMin = 0.0, UIMax = 1.0))` — Color correction intensity. Clamped to 0-1 range.
- L149 _public member_ `float Inner;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Region", meta = (UIMin = 0.0, UIMax = 1.0))` — Inner of the region. Swapped with Outer in case it is higher than Outer.
- L153 _public member_ `float Outer;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Region", meta = (UIMin = 0.0, UIMax = 1.0))` — Outer of the region.
- L157 _public member_ `float Falloff;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Region", meta = (UIMin = 0.0))` — Falloff. Softening the region.
- L161 _public member_ `bool Invert;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Region")` — Invert region.
- L165 _public member_ `EColorCorrectRegionTemperatureType TemperatureType;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Grading")` — Type of algorithm to be used to control color temperature or white balance.
- L169 _public member_ `float Temperature;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Grading", meta = (UIMin = "1500.0", UIMax = "15000.0"))` — Color correction temperature.
- L173 _public member_ `float Tint;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Grading", meta=(UIMin = "-1.0", UIMax = "1.0"))` — Color temperature tint.
- L177 _public member_ `FColorGradingSettings ColorGradingSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Grading", meta = (ShowOnlyInnerProperties))` — Color correction settings.
- L181 _public member_ `bool Enabled;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Grading", meta = (DisplayName = "Enable Color Grading", DisplayPriority = 1))` — Enable/Disable color correction provided by this region.
- L185 _public member_ `bool bEnablePerActorCC;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Per Actor CC", meta = (DisplayName = "Enable Per-Actor CC"))` — Enables or disabled per actor color correction.
- L189 _public member_ `EColorCorrectRegionStencilType PerActorColorCorrection;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Per Actor CC", meta = (editcondition = "bEnablePerActorCC", DisplayName = "Per-Actor CC Mode"))` — Controls in which way the below targets will be affected by color correction.
- L193 _public member_ `TSet<TSoftObjectPtr<AActor>> AffectedActors;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Per Actor CC", meta = (editcondition = "bEnablePerActorCC", DisplayName = "Actor Selection"))` — List of actors that get affected or ignored by Per actor CC. Effect depends on the above option.
- L200 _public member_ `TMap<TSoftObjectPtr<AActor>, TSharedPtr<FStencilData>> PerAffectedActorStencilData;` — This is a temporary property that is used to keep track of managed actors for per actor CC. PerAffectedActorStencilData is managed by FColorCorrectRegionsStencilManager and CCR Subsystem Its lifetime is aligned with selected level and gets reset often.
- L206 _public member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY(Transient)` — Billboard component for this actor.
- L212 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Called when any of the properties are changed.
- L213 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L214 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L220 _public member_ `TObjectPtr<UColorCorrectionInvisibleComponent> IdentityComponent;` — `UPROPERTY()` — The main purpose of this component is to determine the visibility status of this Color Correction Actor.
- L222 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const;`
- L230 _public function_ `FColorCorrectRenderProxyPtr GetCCProxy_RenderThread()` — `UE_DEPRECATED(5.5, "State management is now done by subsystem.")` — Gets a full state for rendering.
- L236 _public function_ `void TransferState()` — `UE_DEPRECATED(5.5, "State management is now done by subsystem.")` — Copy state required for rendering to be consumed by Scene view extension.
- L245 _protected function_ `virtual void ChangeShapeVisibilityForActorType()` — All CC Actors rely on a shape for selection. These shapes need to be swapped depending on the type. This function forces the refresh of the shape if the Type was changed outside of UI. For internal use only.
- L249 _protected function_ `template <typename TCCActorType> void ChangeShapeVisibilityForActorTypeInternal(TCCActorType InDesiredType)` — All CC Actors rely on a shape for selection. These shapes need to be swapped depending on the type.
- L286 _protected function_ `virtual void FixMeshComponentReferences()` — Used to validate child components.
- L289 _protected function_ `template <typename TCCActorType> void FixMeshComponentReferencesInternal(TCCActorType InDesiredType)`
- L324 _private prototype_ `void HandleAffectedActorsPropertyChange(uint32 ActorListChangeType);` — AffectedActors property change could potentially invoke a Dialog Window, which should be displayed on Game Thread. ActorListChangeType represents EPropertyChangeType
- L328 _private prototype_ `void OnSequencerTimeChanged(TWeakPtr<class ISequencer> InSequencer);` — Called when a sequencer has its time changed.
- L335 _public prototype_ `virtual void SetLongitude(double InValue) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L337 _public prototype_ `virtual double GetLongitude() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L340 _public prototype_ `virtual void SetLatitude(double InValue) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L342 _public prototype_ `virtual double GetLatitude() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L345 _public prototype_ `virtual void SetDistanceFromCenter(double InValue) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L347 _public prototype_ `virtual double GetDistanceFromCenter() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L350 _public prototype_ `virtual void SetSpin(double InValue) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L352 _public prototype_ `virtual double GetSpin() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L355 _public prototype_ `virtual void SetPitch(double InValue) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L357 _public prototype_ `virtual double GetPitch() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L360 _public prototype_ `virtual void SetYaw(double InValue) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L362 _public prototype_ `virtual double GetYaw() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L365 _public prototype_ `virtual void SetRadialOffset(double InValue) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L367 _public prototype_ `virtual double GetRadialOffset() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L370 _public prototype_ `virtual void SetScale(const FVector2D& InScale) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L372 _public prototype_ `virtual FVector2D GetScale() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L375 _public prototype_ `virtual void SetOrigin(const FTransform& InOrigin) override;` — `UFUNCTION(BlueprintSetter)`
- L377 _public prototype_ `virtual FTransform GetOrigin() const override;` — `UFUNCTION(BlueprintGetter)`
- L380 _public prototype_ `virtual void SetPositionalParams(const FDisplayClusterPositionalParams& InParams) override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L382 _public prototype_ `virtual FDisplayClusterPositionalParams GetPositionalParams() const override;` — `UFUNCTION(BlueprintCallable, Category = Orientation)`
- L384 _public prototype_ `virtual void GetPositionalProperties(FPositionalPropertyArray& OutPropertyPairs) const override;`
- L385 _public prototype_ `virtual FName GetPositionalPropertiesMemberName() const override;`
- L391 _protected member_ `FDisplayClusterPositionalParams PositionalParams;` — `UPROPERTY(EditAnywhere, Category = Orientation, meta = (ShowOnlyInnerProperties))` — Spherical coordinates in relation to the origin, primarily used with the ICVFX panel.
- L395 _protected member_ `FTransform Origin;` — `UPROPERTY(VisibleAnywhere, BlueprintSetter=SetOrigin, BlueprintGetter=GetOrigin, Category = Orientation)` — The origin when used in the ICVFX panel.
- L398 _protected member_ `bool bNotifyOnParamSetter = true;` — Update the transform when a positional setter is called.

#### class `AColorCorrectionRegion`  
`class AColorCorrectionRegion : public AColorCorrectRegion`  
_L409-431_
- reflection: `UCLASS(Blueprintable, NotPlaceable)`
- inherits: `AColorCorrectRegion`
- desc: A placeable Color Correction Regions actor that replaces previous implementation (blueprint). Color Correction Regions allow users to adjust color of anything that is within it (or outside, if Invert option is selected).
- L415 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Called when any of the properties are changed.
- L416 _private prototype_ `virtual FName GetCustomIconName() const override;`
- L419 _protected prototype_ `virtual void FixMeshComponentReferences() override;`
- L423 _protected prototype_ `virtual void ChangeShapeVisibilityForActorType() override;`
- L428 _private prototype_ `void CreateIcon();` — Creates an icon for CCR/CCW to be clicked on in Editor.

#### class `UColorCorrectionInvisibleComponent`  
`class UColorCorrectionInvisibleComponent : public UPrimitiveComponent`  
_L438-442_
- reflection: `UCLASS(NotBlueprintable, NotPlaceable)`
- inherits: `UPrimitiveComponent`
- desc: This component class is used to determine if Color Correction Window/Region is hidden via HiddenPrimitives/ShowOnlyPrimitivesShowOnlyPrimitives

#### Free symbols / members of external scopes

- L74 _member_ `EColorCorrectRegionsType Type;` (scope `FColorCorrectRenderProxy::__anon76dfdaab010a`)
- L75 _member_ `EColorCorrectWindowType WindowType;` (scope `FColorCorrectRenderProxy::__anon76dfdaab010a`)
- L112 _typedef_ `typedef TSharedPtr<FColorCorrectRenderProxy, ESPMode::ThreadSafe> FColorCorrectRenderProxyPtr;`

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Public/ColorCorrectRegionsModule.h` (Public)


#### class `FColorCorrectRegionsModule`  
`class FColorCorrectRegionsModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation start
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `void RegisterOutlinerFilters();`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(ColorCorrectRegions, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(ColorCorrectRegions, Log, All);`

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Public/ColorCorrectWindow.h` (Public)


#### class `AColorCorrectionWindow`  
`class AColorCorrectionWindow : public AColorCorrectRegion`  
_L23-52_
- reflection: `UCLASS(Blueprintable, notplaceable)`
- inherits: `AColorCorrectRegion`
- desc: A Color Correction Window that functions the same way as Color Correction Regions except it modifies anything that is behind it. Color Correction Windows do not have Priority property and instead are sorted based on the distance from the camera.
- L31 _public member_ `EColorCorrectWindowType WindowType;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Region", Meta = (DisplayName = "Type"))` — Region type.
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Called when any of the properties are changed.
- L36 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L37 _public prototype_ `virtual FName GetCustomIconName() const override;`
- L40 _protected prototype_ `virtual void FixMeshComponentReferences() override;`
- L44 _protected prototype_ `virtual void ChangeShapeVisibilityForActorType() override;`
- L48 _private prototype_ `void CreateIcon();`

#### class `ADEPRECATED_ColorCorrectWindow`  
`class ADEPRECATED_ColorCorrectWindow : public AColorCorrectionWindow`  
_L55-58_
- reflection: `UCLASS(Deprecated, Blueprintable, notplaceable, meta = (DeprecationMessage = "This is a deprecated version of Color Correct Window. Please re-create Color Correct Window to remove this warning."))`
- inherits: `AColorCorrectionWindow`
