# Plugins / GeometryScriptingEditor

- module root: `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor`
- headers: 8; symbols: 124
- symbol kinds: class=9, enum=2, enumerator=7, function=1, macro=6, member=42, namespace=2, prototype=47, struct=8
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: BSPUtils, EditorFramework, Engine, GeometryAlgorithms, ImageCore, MeshConversion, MeshDescription, ModelingComponents, ModelingComponentsEditorOnly, ModelingOperators, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DynamicMesh, EditorSubsystem, GeometryCore, GeometryFramework, GeometryScriptingCore, PhysicsCore, RenderCore

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryActors/EditorGeometryGenerationSubsystem.h` (Public)


#### class `UEditorGeometryGenerationSubsystem`  
`class UEditorGeometryGenerationSubsystem : public UEditorSubsystem`  
_L28-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: UEditorGeometryGenerationSubsystem manages recomputation of "generated" mesh actors, eg to provide procedural mesh generation in-Editor. Generally such procedural mesh generation is expensive, and if many objects need to be generated, the regeneration needs to be managed at a higher level to ensure that the Editor remains responsive/interactive. AGeneratedDynamicMeshActors register themselves with this Subsystem, and allow the Subsystem to tell them when they should regenerate themselves (if necessary). The current behavior is to run all pending generations on a Tick, however in future this regeneration will be more carefully managed via throttling / timeslicing / etc.
- L33 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L34 _public prototype_ `virtual void Deinitialize() override;`
- L38 _public member_ `TObjectPtr<UEditorGeometryGenerationManager> GenerationManager;` — `UPROPERTY()`
- L45 _public prototype_ `static bool RegisterGeneratedMeshActor(AGeneratedDynamicMeshActor* Actor);`
- L46 _public prototype_ `static void UnregisterGeneratedMeshActor(AGeneratedDynamicMeshActor* Actor);`
- L51 _protected prototype_ `virtual void OnShutdown();` — callback connected to engine/editor shutdown events to set bIsShuttingDown, which disables the subsystem static functions above
- L54 _private member_ `static bool bIsShuttingDown;`

#### class `UEditorGeometryGenerationManager`  
`class UEditorGeometryGenerationManager : public UObject, public FTickableEditorObject`  
_L65-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,FTickableEditorObject`
- desc: UEditorGeometryGenerationManager is a class used by UEditorGeometryGenerationSubsystem to store registrations and provide a Tick()
- L70 _public prototype_ `virtual void Shutdown();`
- L72 _public prototype_ `virtual void RegisterGeneratedMeshActor(AGeneratedDynamicMeshActor* Actor);`
- L73 _public prototype_ `virtual void UnregisterGeneratedMeshActor(AGeneratedDynamicMeshActor* Actor);`
- L78 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L79 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L80 _public prototype_ `virtual bool IsTickable() const override;`
- L81 _public prototype_ `virtual TStatId GetStatId() const override;`
- L85 _protected member_ `TSet<AGeneratedDynamicMeshActor*> ActiveGeneratedActors;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGEDITOR_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryActors/GeneratedDynamicMeshActor.h` (Public)


#### class `AGeneratedDynamicMeshActor`  
`class AGeneratedDynamicMeshActor : public ADynamicMeshActor`  
_L26-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ADynamicMeshActor`
- desc: AGeneratedDynamicMeshActor is an Editor-only subclass of ADynamicMeshActor that provides special support for dynamic procedural generation of meshes in the Editor, eg via Blueprints. Expensive procedural generation implemented via BP can potentially cause major problems in the Editor, in particular with interactive performance. AGeneratedDynamicMeshActor provides special infrastructure for this use case. Essentially, instead of doing procedural generation in the Construction Script, a BP-implementable event OnRebuildGeneratedMesh is available, and doing the procedural mesh regeneration when that function fires will generally provide better in-Editor interactive performance.
- L32 _public prototype_ `virtual ~AGeneratedDynamicMeshActor();`
- L38 _public member_ `bool bFrozen = false;` — `UPROPERTY(Category = "DynamicMeshActor", EditAnywhere, BlueprintReadWrite)` — If true, the DynamicMeshComponent will be "Frozen" in its current state, and automatic rebuilding will be disabled. However the DynamicMesh can still be modified by explicitly-called functions/etc.
- L42 _public member_ `bool bResetOnRebuild = true;` — `UPROPERTY(Category = "DynamicMeshActor|Advanced", EditAnywhere, BlueprintReadWrite)` — If true, the DynamicMeshComponent will be cleared before the RebuildGeneratedMesh event is executed.
- L50 _public prototype_ `void OnRebuildGeneratedMesh(UDynamicMesh* TargetMesh);` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor, Category = "Events")` — This event will be fired to notify the BP that the generated Mesh should be rebuilt. GeneratedDynamicMeshActor BP subclasses should rebuild their meshes on this event, instead of doing so directly from the Construction Script.
- L56 _public prototype_ `void MarkForMeshRebuild(bool bImmediate = false, bool bImmediateEvenIfFrozen = false);` — `UFUNCTION(BlueprintCallable, Category = "DynamicMeshActor")` — Mark this Actor as modified so that OnRebuildGeneratedMesh runs
- L63 _public prototype_ `virtual void ExecuteRebuildGeneratedMeshIfPending();` — This function will fire the RebuildGeneratedMesh function if the actor has been marked for a pending rebuild (eg via OnConstruction)
- L65 _public prototype_ `virtual bool WantsRebuild();`
- L73 _protected prototype_ `virtual void RebuildGeneratedMesh(UDynamicMesh* TargetMesh);` — Overridable native event for when the generated Mesh should be rebuilt. This function will fire the OnRebuildGeneratedMesh event to the BP.
- L84 _public prototype_ `void CopyPropertiesToStaticMesh(AStaticMeshActor* StaticMeshActor, bool bCopyComponentMaterials = false);` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)` — Attempt to copy Actor Properties to a StaticMeshActor. Optionally copy DynamicMeshComponent material list to the StaticMeshComponent. This function is useful when (eg) swapping from a DynamicMeshActor to a StaticMeshActor as it will allow many configured Actor settings to be preserved (like assigned DataLayers, etc)
- L92 _public prototype_ `void CopyPropertiesFromStaticMesh(AStaticMeshActor* StaticMeshActor, bool bCopyComponentMaterials = false);` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)` — Attempt to copy Actor Properties from a StaticMeshActor. Optionally copy DynamicMeshComponent material list to the StaticMeshComponent. This function is useful when (eg) swapping from a StaticMeshActor to a DynamicMeshActor as it will allow many configured Actor settings to be preserved (like assigned DataLayers, etc)
- L99 _public prototype_ `virtual void PostLoad() override;`
- L100 _public prototype_ `virtual void PostActorCreated() override;`
- L101 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L102 _public prototype_ `virtual void Destroyed() override;`
- L105 _public prototype_ `virtual void PreRegisterAllComponents() override;` — these are called when Actor exists in a sublevel that is hidden/shown
- L106 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L109 _public prototype_ `virtual void PostEditUndo() override;`
- L110 _public prototype_ `virtual void PostEditUndo(TSharedPtr<ITransactionObjectAnnotation> TransactionAnnotation) override;`
- L117 _protected member_ `bool bGeneratedMeshRebuildPending = false;` — this internal flag is set in OnConstruction, and will cause ExecuteRebuildGeneratedMesh to fire the RebuildGeneratedMesh event, after which the flag will be cleared
- L121 _protected member_ `bool bIsRegisteredWithGenerationManager = false;` — indicates that this Actor is registered with the UEditorGeometryGenerationSubsystem, which is where the mesh rebuilds are executed
- L125 _private member_ `bool bIsCurrentlyRebuilding = false;` — flag set during a rebuild -- used to help detect/avoid recursive rebuilds
- L128 _protected prototype_ `virtual void RegisterWithGenerationManager();`
- L129 _protected prototype_ `virtual void UnregisterWithGenerationManager();`
- L143 _public member_ `bool bEnableRebuildProgress = false;` — `UPROPERTY(Category = "DynamicMeshActor|Progress", EditAnywhere, BlueprintReadWrite)` — If enabled, a long-running OnRebuildGeneratedMesh event will show a progress dialog (The Script being executed must call IncrementProgress regularly)
- L147 _public member_ `float DialogDelay = 1;` — `UPROPERTY(Category = "DynamicMeshActor|Progress", EditAnywhere, BlueprintReadWrite)` — Delay in seconds before the progress dialog is shown, if enabled
- L151 _public member_ `int NumProgressSteps = 4;` — `UPROPERTY(Category = "DynamicMeshActor|Progress", EditAnywhere, BlueprintReadWrite)` — Number of progress steps/ticks that the progress bar will be subdivided into
- L155 _public member_ `FString ProgressMessage = TEXT("Reb` — `UPROPERTY(Category = "DynamicMeshActor|Progress", EditAnywhere, BlueprintReadWrite)` — The default progress message
- L159 _public prototype_ `void IncrementProgress(int NumSteps, FString Message);` — `UFUNCTION(BlueprintCallable, Category = "DynamicMeshActor|Progress")` — Call this function from within OnRebuildGeneratedMesh to update progress tracking.
- L162 _protected member_ `FScopedSlowTask* ActiveSlowTask = nullptr;`
- L163 _protected member_ `int32 CurProgressAccumSteps = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYSCRIPTINGEDITOR_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryScript/CreateNewAssetUtilityFunctions.h` (Public)


#### struct `FGeometryScriptUniqueAssetNameOptions`  
`struct FGeometryScriptUniqueAssetNameOptions`  
_L22-28_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public member_ `int32 UniqueIDDigits = 6;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptCreateNewVolumeFromMeshOptions`  
`struct FGeometryScriptCreateNewVolumeFromMeshOptions`  
_L32-44_
- reflection: `USTRUCT(BlueprintType)`
- L37 _public member_ `TSubclassOf<class AVolume> VolumeType = ABlockingVolume::StaticClass();` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L40 _public member_ `bool bAutoSimplify = true;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L43 _public member_ `int32 MaxTriangles = 250;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptCreateNewStaticMeshAssetOptions`  
`struct FGeometryScriptCreateNewStaticMeshAssetOptions`  
_L48-79_
- reflection: `USTRUCT(BlueprintType)`
- L53 _public member_ `bool bEnableRecomputeNormals = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L56 _public member_ `bool bEnableRecomputeTangents = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L59 _public member_ `bool bEnableNanite = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L63 _public member_ `FMeshNaniteSettings NaniteSettings;` — `UPROPERTY(BlueprintReadWrite, Category = Options)` — Nanite settings to set on new StaticMesh Asset
- L67 _public member_ `float NaniteProxyTrianglePercent = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Deprecated, AdvancedDisplay, meta = (DisplayName = "DEPRECATED NANITE SETTING"))` — Replaced NaniteProxyTrianglePercent with usage of Engine FMeshNaniteSettings, use NaniteSettings property instead
- L70 _public member_ `bool bEnableCollision = true;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L73 _public member_ `TEnumAsByte<ECollisionTraceFlag> CollisionMode = ECollisionTraceFlag::CTF_UseDefault;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L78 _public member_ `bool bUseOriginalVertexOrder = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)` — Use the original vertex order found in the source data. This is useful if the inbound mesh was originally non-manifold, and needs to keep the non-manifold structure when re-created.

#### struct `FGeometryScriptCreateNewSkeletalMeshAssetOptions`  
`struct FGeometryScriptCreateNewSkeletalMeshAssetOptions`  
_L83-112_
- reflection: `USTRUCT(BlueprintType)`
- L88 _public member_ `bool bEnableRecomputeNormals = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L91 _public member_ `bool bEnableRecomputeTangents = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L94 _public member_ `TMap<FName, TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(BlueprintReadWrite, Category = Options)`
- L98 _public member_ `bool bUseMeshBoneProportions = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)` — If true, will use the skeleton proportions (if available) stored in the dynamic mesh.
- L102 _public member_ `bool bApplyNaniteSettings = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)` — Whether to apply the provided Nanite Settings to the new Skeletal Mesh asset. If false, the default settings (nanite disabled) will be used.
- L106 _public member_ `FMeshNaniteSettings NaniteSettings;` — `UPROPERTY(BlueprintReadWrite, Category = Options)` — Nanite settings to apply to the new Skeletal Mesh Asset, if bApplyNaniteSettings is true
- L111 _public member_ `bool bUseOriginalVertexOrder = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)` — Use the original vertex order found in the source data. This is useful if the inbound mesh was originally non-manifold, and needs to keep the non-manifold structure when re-created.

#### struct `FGeometryScriptCreateNewTexture2DAssetOptions`  
`struct FGeometryScriptCreateNewTexture2DAssetOptions`  
_L116-123_
- reflection: `USTRUCT(BlueprintType)`
- L122 _public member_ `bool bOverwriteIfExists = false;` — `UPROPERTY(BlueprintReadWrite, Category = Options)` — If true, overwrite any existing texture assets using the same AssetPathAndName

#### class `UGeometryScriptLibrary_CreateNewAssetFunctions`  
`class UGeometryScriptLibrary_CreateNewAssetFunctions : public UBlueprintFunctionLibrary`  
_L127-234_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_NewAssetUtils"))`
- inherits: `UBlueprintFunctionLibrary`
- L134 _public prototype_ `CreateUniqueNewAssetPathName( FString AssetFolderPath, FString BaseAssetName, FString& UniqueAssetPathAndName, FString& UniqueAssetName, FGeometryScriptUniqueAssetNameOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);`
- L148 _public prototype_ `static UPARAM(DisplayName = "Volume Actor") AVolume* CreateNewVolumeFromMesh_WorldContext( UObject* WorldContextObject, UDynamicMesh* FromDynamicMesh, FTransform ActorTransform, FString BaseActorName, FGeometryScriptCreateNewVolumeFromMeshOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|AssetManagement", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome", DisplayName = "Create New Volume From Mesh", WorldContext = "WorldContextObject"))` — Create a new Volume from a Dynamic Mesh, in the same world as the calling blueprint.
- L162 _public prototype_ `static UPARAM(DisplayName = "Volume Actor") AVolume* CreateNewVolumeFromMesh( UDynamicMesh* FromDynamicMesh, UPARAM(ref) UWorld* CreateInWorld, FTransform ActorTransform, FString BaseActorName, FGeometryScriptCreateNewVolumeFromMeshOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|AssetManagement", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome", DisplayName = "Create New Volume From Mesh In Target World"))` — Create a new Volume from a Dynamic Mesh, in the specified world.
- L176 _public prototype_ `static UPARAM(DisplayName = "Static Mesh Asset") UStaticMesh* CreateNewStaticMeshAssetFromMesh( UDynamicMesh* FromDynamicMesh, FString AssetPathAndName, FGeometryScriptCreateNewStaticMeshAssetOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|AssetManagement", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Create a new StaticMesh asset from a DynamicMesh. Save the asset at the AssetPathAndName location.
- L189 _public prototype_ `static UPARAM(DisplayName = "Static Mesh Asset") UStaticMesh* CreateNewStaticMeshAssetFromMeshLODs( TArray<UDynamicMesh*> FromDynamicMesh, FString AssetPathAndName, FGeometryScriptCreateNewStaticMeshAssetOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|AssetManagement", meta = (HidePin = "Debug", ScriptName="CreateNewStaticMeshAssetFromMeshLods;CreateNewStaticMeshAssetFromMeshLODs", ExpandEnumAsExecs = "Outcome"))` — Create a new StaticMesh asset from a collection of LODs represented by an array of DynamicMeshes. Save the asset at the AssetPathAndName location.
- L202 _public prototype_ `static UPARAM(DisplayName = "Skeletal Mesh Asset") USkeletalMesh* CreateNewSkeletalMeshAssetFromMesh( UDynamicMesh* FromDynamicMesh, USkeleton* InSkeleton, FString AssetPathAndName, FGeometryScriptCreateNewSkeletalMeshAssetOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|AssetManagement", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Create a new SkeletalMesh asset from a DynamicMesh and a Skeleton. Save the asset at the AssetPathAndName location.
- L216 _public prototype_ `static UPARAM(DisplayName = "Skeletal Mesh Asset") USkeletalMesh* CreateNewSkeletalMeshAssetFromMeshLODs( TArray<UDynamicMesh*> FromDynamicMeshLODs, USkeleton* InSkeleton, FString AssetPathAndName, FGeometryScriptCreateNewSkeletalMeshAssetOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|AssetManagement", meta = (HidePin = "Debug", ScriptName="CreateNewSkeletalMeshAssetFromMeshLods;CreateNewSkeletalMeshAssetFromMeshLODs", ExpandEnumAsExecs = "Outcome"))` — Create a new SkeletalMesh asset from a collection of LODs represented by an array of DynamicMeshes and a Skeleton. Save the asset at the AssetPathAndName location.
- L226 _public prototype_ `static UPARAM(DisplayName = "Texture 2D Asset") UTexture2D* CreateNewTexture2DAsset( UTexture2D* FromTexture, FString AssetPathAndName, FGeometryScriptCreateNewTexture2DAssetOptions Options, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|AssetManagement", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GEOMETRYSCRIPTINGEDITOR_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryScript/EditorDynamicMeshProcessor.h` (Public)


#### class `UEditorDynamicMeshProcessorBlueprint`  
`class UEditorDynamicMeshProcessorBlueprint : public UDynamicMeshProcessorBlueprint`  
_L14-17_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable)`
- inherits: `UDynamicMeshProcessorBlueprint`
- desc: Editor-only variant of UDynamicMeshProcessorBlueprint. Blueprints with this parent class can use editor-only blueprint nodes (e.g. from GeometryScriptingEditor) that are not available to runtime blueprints.

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryScript/EditorDynamicMeshUtilityFunctions.h` (Public)


#### struct `FDynamicMeshChangeContainer`  
`struct FDynamicMeshChangeContainer`  
_L25-37_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Dynamic Mesh ChangeTracker"))`
- desc: FDynamicMeshChangeContainer is a temporary struct usable in Blueprints to emit "change" transactions for a UDynamicMesh. The internals are hidden and this type is only intended to be used with the BeginTrackedMeshChange() and EmitTrackedMeshChange() functions
- L29 _public member_ `bool bIsActive = false;`
- L33 _public member_ `UDynamicMesh* TargetMesh;` — This is only used as a token to ensure that the ChangeContainer is not applied to a different UDynamicMesh, so it is not a uproperty/etc
- L36 _public member_ `TSharedPtr<UE::Geometry::FDynamicMeshChangeContainerInternals> ChangeInternals;` — internals are only available inside the cpp file and are likely to change

#### class `UGeometryScriptLibrary_EditorDynamicMeshFunctions`  
`class UGeometryScriptLibrary_EditorDynamicMeshFunctions : public UBlueprintFunctionLibrary`  
_L44-87_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_EditorDynamicMeshUtil"))`
- inherits: `UBlueprintFunctionLibrary`
- L55 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* BeginTrackedMeshChange(UDynamicMesh* TargetMesh, FDynamicMeshChangeContainer& ChangeTracker);` — `UFUNCTION(BlueprintCallable, Category = "DynamicMesh|Changes")` — Save current state of TargetMesh so that an undoable/redoable Change can be emitted after TargetMesh is modified, using EmitTrackedMeshChange(). @param ChangeTracker output structure containing initial TargetMesh state
- L64 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* EmitTrackedMeshChange(UDynamicMesh* TargetMesh, UPARAM(ref) FDynamicMeshChangeContainer& ChangeTracker);` — `UFUNCTION(BlueprintCallable, Category = "DynamicMesh|Changes")` — Emit an undo/redo Change for a modified TargetMesh, based on the ChangeTracker information that was saved (via call to BeginTrackedMeshChange) before TargetMesh was modified. This function must be called in the context of a Transaction (ie BeginTransaction / EndTransaction pair)
- L74 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* StashDebugMesh(UDynamicMesh* TargetMesh, FString DebugMeshName);` — `UFUNCTION(BlueprintCallable, Category = "DynamicMesh|Changes")` — Store a copy of TargetMesh with name DebugMeshName. The mesh can later be recovered via FetchDebugMesh. @warning This function stores the mesh in a global data structure, the caller must take care to avoid storing large numbers of debug meshes
- L85 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* FetchDebugMesh(FString DebugMeshName, UDynamicMesh* ToTargetMesh, bool bClearDebugMesh, bool& bDebugMeshExists);` — `UFUNCTION(BlueprintCallable, Category = "DynamicMesh|Changes")` — Fetch a debug FDynamicMesh3 saved with DebugMeshName from the global debug mesh storage and copy to ToTargetMesh. If DebugMeshName does not exist, a cube will be returned. @param bClearDebugMesh if true, debug mesh will be removed from global storage @param bDebugMeshExists will return as true if DebugMeshName existed

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryScript/EditorTextureMapFunctions.h` (Public)


#### enum `EGeometryScriptRGBAChannel`  
`enum class EGeometryScriptRGBAChannel : uint8`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `R = 0`
- L20 _public enumerator_ `G = 1`
- L21 _public enumerator_ `B = 2`
- L22 _public enumerator_ `A = 3`

#### enum `EGeometryScriptReadGammaSpace`  
`enum class EGeometryScriptReadGammaSpace : uint8`  
_L26-34_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `FromTextureSettings = 0` — Read color data from Texture directly, without any conversion
- L31 _public enumerator_ `Linear = 1` — Read linear color data from Texture, converting if needed
- L33 _public enumerator_ `SRGB = 2` — Read sRGB color data from Texture, converting if needed

#### struct `FGeometryScriptChannelPackSource`  
`struct FGeometryScriptChannelPackSource`  
_L37-56_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The Texture which should be read/sourced. If null then the DefaultValue is used instead
- L47 _public member_ `EGeometryScriptReadGammaSpace ReadGammaSpace = EGeometryScriptReadGammaSpace::FromTextureSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If Texture is not null, this determines how the color data will be read/sourced
- L51 _public member_ `EGeometryScriptRGBAChannel Channel = EGeometryScriptRGBAChannel::R;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If Texture is not null, this determines which channel is read/sourced
- L55 _public member_ `float DefaultValue = 255;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Advanced)` — If Texture is null, this value is read/sourced and the Channel and ReadGammaSpace values are ignored

#### struct `FGeometryScriptChannelPackResult`  
`struct FGeometryScriptChannelPackResult`  
_L59-65_
- reflection: `USTRUCT(BlueprintType)`
- L64 _public member_ `TObjectPtr<UTexture2D> Output = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_EditorTextureMapFunctions`  
`class UGeometryScriptLibrary_EditorTextureMapFunctions : public UBlueprintFunctionLibrary`  
_L69-83_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_EditorTextureUtils"))`
- inherits: `UBlueprintFunctionLibrary`
- L76 _public prototype_ `static FGeometryScriptChannelPackResult ChannelPack( FGeometryScriptChannelPackSource RChannelSource, FGeometryScriptChannelPackSource GChannelSource, FGeometryScriptChannelPackSource BChannelSource, FGeometryScriptChannelPackSource AChannelSource, bool OutputSRGB, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|TextureUtils", meta = (HidePin = "Debug"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGEDITOR_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryScript/OpenSubdivUtilityFunctions.h` (Public)


#### class `UGeometryScriptLibrary_OpenSubdivFunctions`  
`class UGeometryScriptLibrary_OpenSubdivFunctions : public UBlueprintFunctionLibrary`  
_L13-35_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_OpenSubdiv"))`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyPolygroupCatmullClarkSubD( UDynamicMesh* FromDynamicMesh, int32 Subdivisions, FGeometryScriptGroupLayer GroupLayer, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|OpenSubdiv", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Apply PolyGroup Catmull Clark SubD"))`
- L29 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyTriangleLoopSubD( UDynamicMesh* FromDynamicMesh, int32 Subdivisions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|OpenSubdiv", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Apply Triangle Loop SubD"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGEDITOR_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingEditor/Public/GeometryScriptingEditorModule.h` (Public)


#### class `FGeometryScriptingEditorModule`  
`class FGeometryScriptingEditorModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
