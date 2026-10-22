# Runtime / Foliage

- module root: `Source/Runtime/Foliage`
- headers: 25; symbols: 929
- symbol kinds: class=18, delegate=6, enum=11, enumerator=55, function=82, member=289, namespace=4, prototype=433, struct=24, typedef=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, RHI, RenderCore

### `Source/Runtime/Foliage/Private/FoliageActor.h` (Private)


#### struct `FFoliageActor`  
`struct FFoliageActor : public FFoliageImpl`  
_L6-73_
- inherits: `FFoliageImpl`
- L9 _public member_ `TArray<TWeakObjectPtr<AActor>> ActorInstances_Deprecated;`
- L12 _public member_ `TArray<TObjectPtr<AActor>> ActorInstances;`
- L13 _public member_ `UClass* ActorClass;`
- L14 _public member_ `bool bShouldAttachToBaseComponent;`
- L16 _public function_ `FFoliageActor(FFoliageInfo* Info) : FFoliageImpl(Info) , ActorClass(nullptr) , bShouldAttachToBaseComponent(true) #if WITH_EDITOR , bActorsDestroyed(false) #endif`
- L26 _public prototype_ `virtual void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector) override;`
- L27 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L28 _public prototype_ `void DestroyActors(bool bOnLoad);`
- L31 _public prototype_ `virtual bool IsInitialized() const override;`
- L32 _public prototype_ `virtual void Initialize(const UFoliageType* FoliageType) override;`
- L33 _public prototype_ `virtual void Uninitialize() override;`
- L34 _public prototype_ `virtual int32 GetInstanceCount() const override;`
- L35 _public prototype_ `virtual void PreAddInstances(const UFoliageType* FoliageType, int32 Count) override;`
- L36 _public prototype_ `virtual void AddInstance(const FFoliageInstance& NewInstance) override;`
- L37 _public prototype_ `virtual void AddExistingInstance(const FFoliageInstance& ExistingInstance, UObject* InstanceImplementation) override;`
- L38 _public prototype_ `virtual void RemoveInstance(int32 InstanceIndex) override;`
- L39 _public prototype_ `virtual void MoveInstance(int32 InstanceIndex, UObject*& OutInstanceImplementation) override;`
- L40 _public prototype_ `virtual void SetInstanceWorldTransform(int32 InstanceIndex, const FTransform& Transform, bool bTeleport) override;`
- L41 _public prototype_ `virtual FTransform GetInstanceWorldTransform(int32 InstanceIndex) const override;`
- L42 _public prototype_ `virtual bool IsOwnedComponent(const UPrimitiveComponent* PrimitiveComponent) const override;`
- L43 _public prototype_ `int32 FindIndex(const AActor* InActor) const;`
- L44 _public prototype_ `virtual int32 GetInstanceIndexFrom(const UPrimitiveComponent* PrimitiveComponent, int32 ComponentIndex) const override;`
- L46 _public prototype_ `virtual void SelectAllInstances(bool bSelect) override;`
- L47 _public prototype_ `virtual void SelectInstance(bool bSelect, int32 Index) override;`
- L48 _public prototype_ `virtual void SelectInstances(bool bSelect, const TSet<int32>& SelectedIndices) override;`
- L49 _public prototype_ `virtual FBox GetSelectionBoundingBox(const TSet<int32>& SelectedIndices) const override;`
- L50 _public prototype_ `virtual void ApplySelection(bool bApply, const TSet<int32>& SelectedIndices) override;`
- L51 _public prototype_ `virtual void ClearSelection(const TSet<int32>& SelectedIndices) override;`
- L53 _public prototype_ `virtual void BeginUpdate() override;`
- L54 _public prototype_ `virtual void EndUpdate() override;`
- L55 _public prototype_ `virtual void Refresh(bool Async, bool Force) override;`
- L56 _public prototype_ `virtual void OnHiddenEditorViewMaskChanged(uint64 InHiddenEditorViews) override;`
- L57 _public prototype_ `virtual void PostEditUndo(FFoliageInfo* InInfo, UFoliageType* FoliageType) override;`
- L58 _public prototype_ `virtual void PreMoveInstances(TArrayView<const int32> InInstancesMoved) override;`
- L59 _public prototype_ `virtual void PostMoveInstances(TArrayView<const int32> InInstancesMoved, bool bFinished) override;`
- L60 _public prototype_ `virtual bool NotifyFoliageTypeChanged(UFoliageType* FoliageType, bool bSourceChanged) override;`
- L61 _public prototype_ `virtual void Reapply(const UFoliageType* FoliageType) override;`
- L62 _public prototype_ `AActor* Spawn(const FFoliageInstance& Instance);`
- L63 _public prototype_ `TArray<AActor*> GetActorsFromSelectedIndices(const TSet<int32>& SelectedIndices) const;`
- L64 _public function_ `virtual bool ShouldAttachToBaseComponent() const override`
- L65 _public prototype_ `bool UpdateInstanceFromActor(int32 Index, FFoliageInfo& FoliageInfo);`
- L66 _public prototype_ `void GetInvalidInstances(TArray<int32>& InvalidInstances);`
- L69 _private prototype_ `void UpdateActorTransforms(const TArray<FFoliageInstance>& Instances);`
- L71 _private member_ `bool bActorsDestroyed;`

### `Source/Runtime/Foliage/Private/FoliageISMActor.h` (Private)


#### struct `FFoliageISMActor`  
`struct FFoliageISMActor : public FFoliageImpl, public IISMPartitionInstanceManager`  
_L16-98_
- inherits: `FFoliageImpl,IISMPartitionInstanceManager`
- L18 _public function_ `FFoliageISMActor(FFoliageInfo* Info) : FFoliageImpl(Info) #if WITH_EDITORONLY_DATA , Guid(FGuid::NewGuid()) , ActorClass(nullptr) #endif`
- L27 _public prototype_ `virtual ~FFoliageISMActor();`
- L30 _public member_ `FGuid Guid;`
- L31 _public member_ `FISMClientHandle ClientHandle;`
- L32 _public member_ `TSortedMap<int32, TArray<FTransform>> ISMDefinition;`
- L33 _public member_ `TObjectPtr<UClass> ActorClass;`
- L35 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L36 _public prototype_ `virtual void PostSerialize(FArchive& Ar) override;`
- L37 _public prototype_ `virtual void PostLoad() override;`
- L40 _public prototype_ `virtual void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector) override;`
- L41 _public prototype_ `virtual bool IsInitialized() const override;`
- L42 _public prototype_ `virtual void Initialize(const UFoliageType* FoliageType) override;`
- L43 _public prototype_ `virtual void Uninitialize() override;`
- L44 _public prototype_ `virtual void Reapply(const UFoliageType* FoliageType) override;`
- L45 _public prototype_ `virtual int32 GetInstanceCount() const override;`
- L46 _public prototype_ `virtual void PreAddInstances(const UFoliageType* FoliageType, int32 AddedInstanceCount) override;`
- L47 _public prototype_ `virtual void AddInstance(const FFoliageInstance& NewInstance) override;`
- L48 _public prototype_ `virtual void RemoveInstance(int32 InstanceIndex) override;`
- L49 _public prototype_ `virtual void SetInstanceWorldTransform(int32 InstanceIndex, const FTransform& Transform, bool bTeleport) override;`
- L50 _public prototype_ `virtual FTransform GetInstanceWorldTransform(int32 InstanceIndex) const override;`
- L51 _public prototype_ `virtual bool IsOwnedComponent(const UPrimitiveComponent* Component) const override;`
- L53 _public prototype_ `virtual void SelectAllInstances(bool bSelect) override;`
- L54 _public prototype_ `virtual void SelectInstance(bool bSelect, int32 Index) override;`
- L55 _public prototype_ `virtual void SelectInstances(bool bSelect, const TSet<int32>& SelectedIndices) override;`
- L56 _public prototype_ `virtual int32 GetInstanceIndexFrom(const UPrimitiveComponent* Component, int32 ComponentIndex) const;`
- L57 _public prototype_ `virtual FBox GetSelectionBoundingBox(const TSet<int32>& SelectedIndices) const override;`
- L58 _public prototype_ `virtual void ApplySelection(bool bApply, const TSet<int32>& SelectedIndices) override;`
- L59 _public prototype_ `virtual void ClearSelection(const TSet<int32>& SelectedIndices) override;`
- L61 _public prototype_ `virtual void ForEachSMInstance(TFunctionRef<bool(FSMInstanceId)> Callback) const override;`
- L62 _public prototype_ `virtual void ForEachSMInstance(int32 InstanceIndex, TFunctionRef<bool(FSMInstanceId)> Callback) const override;`
- L64 _public prototype_ `virtual void BeginUpdate() override;`
- L65 _public prototype_ `virtual void EndUpdate() override;`
- L66 _public prototype_ `virtual void Refresh(bool bAsync, bool bForce) override;`
- L67 _public prototype_ `virtual void OnHiddenEditorViewMaskChanged(uint64 InHiddenEditorViews) override;`
- L68 _public prototype_ `virtual void PreEditUndo(UFoliageType* FoliageType) override;`
- L69 _public prototype_ `virtual void PostEditUndo(FFoliageInfo* InInfo, UFoliageType* FoliageType) override;`
- L70 _public prototype_ `virtual void NotifyFoliageTypeWillChange(UFoliageType* FoliageType) override;`
- L71 _public prototype_ `virtual bool NotifyFoliageTypeChanged(UFoliageType* FoliageType, bool bSourceChanged) override;`
- L74 _private prototype_ `void RegisterDelegates();`
- L75 _private prototype_ `void UnregisterDelegates();`
- L76 _private prototype_ `void OnBlueprintChanged(UBlueprint* InBlueprint);`
- L81 _private prototype_ `virtual FText GetISMPartitionInstanceDisplayName(const FISMClientInstanceId& InstanceId) const override;`
- L82 _private prototype_ `virtual FText GetISMPartitionInstanceTooltip(const FISMClientInstanceId& InstanceId) const override;`
- L83 _private prototype_ `virtual bool CanEditISMPartitionInstance(const FISMClientInstanceId& InstanceId) const override;`
- L84 _private prototype_ `virtual bool CanMoveISMPartitionInstance(const FISMClientInstanceId& InstanceId, const ETypedElementWorldType InWorldType) const override;`
- L85 _private prototype_ `virtual bool GetISMPartitionInstanceTransform(const FISMClientInstanceId& InstanceId, FTransform& OutInstanceTransform, bool bWorldSpace = false) const override;`
- L86 _private prototype_ `virtual bool SetISMPartitionInstanceTransform(const FISMClientInstanceId& InstanceId, const FTransform& InstanceTransform, bool bWorldSpace = false, bool bTeleport = false) override;`
- L87 _private prototype_ `virtual void NotifyISMPartitionInstanceMovementStarted(const FISMClientInstanceId& InstanceId) override;`
- L88 _private prototype_ `virtual void NotifyISMPartitionInstanceMovementOngoing(const FISMClientInstanceId& InstanceId) override;`
- L89 _private prototype_ `virtual void NotifyISMPartitionInstanceMovementEnded(const FISMClientInstanceId& InstanceId) override;`
- L90 _private prototype_ `virtual void NotifyISMPartitionInstanceSelectionChanged(const FISMClientInstanceId& InstanceId, const bool bIsSelected) override;`
- L91 _private prototype_ `virtual bool DeleteISMPartitionInstances(TArrayView<const FISMClientInstanceId> InstanceIds) override;`
- L92 _private prototype_ `virtual bool DuplicateISMPartitionInstances(TArrayView<const FISMClientInstanceId> InstanceIds, TArray<FISMClientInstanceId>& OutNewInstanceIds) override;`
- L95 _private prototype_ `FFoliageInstanceId ISMClientInstanceIdToFoliageInstanceId(const FISMClientInstanceId& InstanceId) const;`
- L96 _private prototype_ `TArray<FFoliageInstanceId> ISMClientInstanceIdsToFoliageInstanceIds(TArrayView<const FISMClientInstanceId> InstanceIds) const;`

### `Source/Runtime/Foliage/Private/InteractiveFoliageComponent.h` (Private)


#### class `UInteractiveFoliageComponent`  
`class UInteractiveFoliageComponent : public UStaticMeshComponent`  
_L14-31_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UStaticMeshComponent`
- L20 _public member_ `class FInteractiveFoliageSceneProxy* FoliageSceneProxy;`
- L23 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L27 _public prototype_ `virtual void DestroyRenderState_Concurrent() override;`

### `Source/Runtime/Foliage/Private/ProceduralFoliageCustomVersion.h` (Private)


#### struct `FProceduralFoliageCustomVersion`  
`struct FProceduralFoliageCustomVersion`  
_L9-27_
- desc: Custom serialization version for all packages containing ProceduralFoliage
- L23 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L26 _private function_ `FProceduralFoliageCustomVersion()`

#### enum `FProceduralFoliageCustomVersion::Type`  
`enum Type`  
_L11-20_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L16 _public enumerator_ `SerializeTypeMap = 1` — We serialize the type clean change map to ensure validity
- L18 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L19 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Source/Runtime/Foliage/Public/FoliageHelper.h` (Public)


#### class `FFoliageHelper`  
`class FFoliageHelper`  
_L11-42_
- desc: Foliage Helper class
- L15 _public function_ `static inline FName GetFoliageActorInstanceTag()`
- L21 _public function_ `static inline void SetIsOwnedByFoliage(AActor* InActor, bool bOwned = true)`
- L37 _public function_ `static inline bool IsOwnedByFoliage(const AActor* InActor)`

### `Source/Runtime/Foliage/Public/FoliageInstanceBase.h` (Public)


#### struct `FFoliageInstanceBaseInfo`  
`struct FFoliageInstanceBaseInfo`  
_L23-43_
- desc: FFoliageInstanceBaseInfo Cached transform information about base component Used for adjusting instance transforms after operations on base components with foliage painted on them.
- L26 _public prototype_ `FFoliageInstanceBaseInfo();` — tors
- L27 _public prototype_ `FFoliageInstanceBaseInfo(UActorComponent* InComponent);`
- L30 _public prototype_ `void UpdateLocationFromComponent(UActorComponent* InComponent);` — Cache the location and rotation from the actor
- L35 _public member_ `FFoliageInstanceBasePtr BasePtr;`
- L36 _public member_ `FVector CachedLocation;`
- L37 _public member_ `FRotator CachedRotation;`
- L38 _public member_ `FVector CachedDrawScale;`
- L41 _public member_ `FFoliageInstanceBasePtr_DEPRECATED BasePtr_DEPRECATED;` — Deprecated data stored for deserializaton done in PostLoad

#### struct `FFoliageInstanceBaseCache`  
`struct FFoliageInstanceBaseCache`  
_L45-96_
- L47 _public prototype_ `FFoliageInstanceBaseCache();`
- L50 _public prototype_ `FFoliageInstanceBaseId AddInstanceBaseId(UActorComponent* InComponent);` — Adds new base to cache and/or returns existing base Id
- L53 _public prototype_ `FFoliageInstanceBaseId GetInstanceBaseId(UActorComponent* InComponent) const;` — Returns Id for a registered base component, invalid Id otherwise
- L56 _public prototype_ `FFoliageInstanceBaseId GetInstanceBaseId(const FFoliageInstanceBasePtr& BasePtr) const;` — Returns Id for a registered base component, invalid Id otherwise
- L59 _public prototype_ `FFoliageInstanceBasePtr GetInstanceBasePtr(FFoliageInstanceBaseId BaseId) const;` — Returns registered base component for specified Id, null otherwise
- L62 _public prototype_ `FFoliageInstanceBaseInfo GetInstanceBaseInfo(FFoliageInstanceBaseId BaseId) const;` — Returns base info for registered Id
- L65 _public prototype_ `FFoliageInstanceBaseInfo UpdateInstanceBaseInfoTransform(UActorComponent* InComponent);` — Updates base info for a specified base component and returns updated info
- L68 _public prototype_ `static void CompactInstanceBaseCache(AInstancedFoliageActor* IFA);` — Compacts cross-level references, removing dead links
- L71 _public prototype_ `void UpdateInstanceBaseCachedTransforms();` — Refreshes base component transforms cache
- L76 _public member_ `static FFoliageInstanceBaseId InvalidBaseId;`
- L80 _public member_ `FFoliageInstanceBaseId NextBaseId;` — ID generator serialized
- L84 _public member_ `TMap<FFoliageInstanceBaseId, FFoliageInstanceBaseInfo> InstanceBaseMap;` — Map for looking up base info by ID serialized
- L88 _public member_ `TMap<FFoliageInstanceBasePtr, FFoliageInstanceBaseId> InstanceBaseInvMap;` — Map for looking up base ID by pointer to component transient
- L92 _public member_ `TMap<TSoftObjectPtr<UWorld>, TArray<FFoliageInstanceBasePtr>> InstanceBaseLevelMap;` — Map for detecting removed bases serialized
- L95 _public member_ `TMap<TSoftObjectPtr<UWorld>, TArray<FFoliageInstanceBasePtr_DEPRECATED>> InstanceBaseLevelMap_DEPRECATED;` — Deprecated data stored for deserializaton done in PostLoad

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef int32 FFoliageInstanceBaseId;`
- L12 _typedef_ `typedef TSoftObjectPtr<UActorComponent> FFoliageInstanceBasePtr;`
- L14 _typedef_ `typedef TLazyObjectPtr<UActorComponent> FFoliageInstanceBasePtr_DEPRECATED;`

### `Source/Runtime/Foliage/Public/FoliageInstancedStaticMeshComponent.h` (Public)


#### class `UFoliageInstancedStaticMeshComponent`  
`class UFoliageInstancedStaticMeshComponent : public UHierarchicalInstancedStaticMeshComponent`  
_L20-55_
- reflection: `UCLASS(ClassGroup = Foliage, Blueprintable, MinimalAPI)`
- inherits: `UHierarchicalInstancedStaticMeshComponent`
- L26 _public member_ `FInstancePointDamageSignature OnInstanceTakePointDamage;` — `UPROPERTY(BlueprintAssignable, Category = "Game|Damage")`
- L29 _public member_ `FInstanceRadialDamageSignature OnInstanceTakeRadialDamage;` — `UPROPERTY(BlueprintAssignable, Category = "Game|Damage")`
- L32 _public member_ `bool bEnableDiscardOnLoad;` — `UPROPERTY()`
- L36 _public member_ `uint64 FoliageHiddenEditorViews;` — `UPROPERTY(transient)`
- L39 _public prototype_ `virtual void ReceiveComponentDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;`
- L43 _public prototype_ `virtual uint64 GetHiddenEditorViews() const override;`
- L44 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L48 _public function_ `void SetGenerationGuid(const FGuid& InGuid)` — Used by procedural generation to link generated component with its creator
- L49 _public function_ `const FGuid& GetGenerationGuid() const`
- L54 _private member_ `FGuid GenerationGuid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FInstancePointDamageSignature, int32, InstanceIndex, float, Damage, class AController*, InstigatedBy, FVector, HitLocation, FVector, ShotFromDirection, const class UDamageType*, DamageType, AActor*, DamageCauser);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FInstancePointDamageSignature, int32, InstanceIndex, float, Damage, class AController*, InstigatedBy, FVector, HitLocation, FVector, ShotFromDirection, const class UDamageType*, DamageType, AActor*, DamageCauser);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FInstanceRadialDamageSignature, const TArray<int32>&, Instances, const TArray<float>&, Damages, class AController*, InstigatedBy, FVector, Origin, float, MaxRadius, const class UDamageType*, DamageType, AActor*, DamageCauser);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FInstanceRadialDamageSignature, const TArray<int32>&, Instances, const TArray<float>&, Damages, class AController*, InstigatedBy, FVector, Origin, float, MaxRadius, const class UDamageType*, DamageType, AActor*, DamageCauser);`

### `Source/Runtime/Foliage/Public/FoliageModule.h` (Public)


#### class `IFoliageEditModuleBase`  
`class IFoliageEditModuleBase : public IModuleInterface`  
_L15-42_
- inherits: `IModuleInterface`
- desc: Foliage Edit mode module interface
- L20 _public prototype_ `virtual void MoveSelectedFoliageToLevel(ULevel* InTargetLevel) = 0;` — Move the selected foliage to the specified level
- L22 _public prototype_ `virtual void UpdateMeshList() = 0;` — Notifies us that the foliage has been externally changed and needs refreshing.
- L23 _public prototype_ `virtual bool CanMoveSelectedFoliageToLevel(ULevel* InTargetLevel) const = 0;`
- L25 _public prototype_ `virtual bool ShouldIgnoreComponentForBaseID(UActorComponent* InComponent) const = 0;`
- L26 _public prototype_ `virtual void RegisterComponentBaseIDClassToIgnore(TSubclassOf<UActorComponent> InClassToIgnore) = 0;`
- L27 _public prototype_ `virtual void UnregisterComponentBaseIDClassToIgnore(TSubclassOf<UActorComponent> InClassToUnregister) = 0;`
- L29 _public prototype_ `static IFoliageEditModuleBase* Get();`
- L35 _protected prototype_ `static void SetFoliageEditModulePtr(IFoliageEditModuleBase* InFoliageEditModulePtr);`
- L40 _private member_ `static IFoliageEditModuleBase* FoliageEditModulePtr;`

#### class `IFoliageModule`  
`class IFoliageModule : public IModuleInterface`  
_L44-47_
- inherits: `IModuleInterface`

### `Source/Runtime/Foliage/Public/FoliageStatistics.h` (Public)


#### class `UFoliageStatistics`  
`class UFoliageStatistics : public UBlueprintFunctionLibrary`  
_L13-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L27 _private prototype_ `static int32 FoliageOverlappingSphereCount(UObject* WorldContextObject, const UStaticMesh* StaticMesh, FVector CenterPosition, float Radius);` — `UFUNCTION(BlueprintCallable, Category = "Foliage", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))` — Counts how many foliage instances overlap a given sphere @param	Mesh			The static mesh we are interested in counting @param	CenterPosition	The center position of the sphere @param	Radius			The radius of the sphere. return number of foliage instances with their mesh set to Mesh that overlap the sphere
- L35 _private prototype_ `static int32 FoliageOverlappingBoxCount(UObject* WorldContextObject, const UStaticMesh* StaticMesh, FBox Box);` — `UFUNCTION(BlueprintCallable, Category = "Foliage", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))` — Gets the number of instances overlapping a provided box @param StaticMesh Mesh to count @param Box Box to overlap
- L44 _private prototype_ `static void FoliageOverlappingBoxTransforms(UObject* WorldContextObject, const UStaticMesh* StaticMesh, FBox Box, TArray<FTransform>& OutTransforms);` — `UFUNCTION(BlueprintCallable, Category = "Foliage", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))` — Get the transform of every instance overlapping the provided FBox @param StaticMesh Mesh to get instances of @param Box Box to use for overlap @param OutTransforms Array to populate with transforms
- L53 _private prototype_ `static void FoliageOverlappingMeshCounts_Debug(UObject* WorldContextObject, FVector CenterPosition, float Radius, TMap<UStaticMesh*, int32>& OutMeshCounts);` — DEBUG FUNCTION: This is not fast, use only for debug/development. Gets an instance count for each unique mesh type overlapping the given sphere. @param	CenterPosition	The center position of the sphere @param	Radius			The radius of the sphere. @param OutMeshCounts	Map of Meshes to instance counts

### `Source/Runtime/Foliage/Public/FoliageType.h` (Public)


#### enum `FoliageVertexColorMask`  
`enum FoliageVertexColorMask : int`  
_L18-25_
- reflection: `UENUM()`
- L20 _public enumerator_ `FOLIAGEVERTEXCOLORMASK_Disabled UMETA(DisplayName="Disabled")`
- L21 _public enumerator_ `FOLIAGEVERTEXCOLORMASK_Red UMETA(DisplayName="Red")`
- L22 _public enumerator_ `FOLIAGEVERTEXCOLORMASK_Green UMETA(DisplayName="Green")`
- L23 _public enumerator_ `FOLIAGEVERTEXCOLORMASK_Blue UMETA(DisplayName="Blue")`
- L24 _public enumerator_ `FOLIAGEVERTEXCOLORMASK_Alpha UMETA(DisplayName="Alpha")`

#### enum `EVertexColorMaskChannel`  
`enum class EVertexColorMaskChannel : uint8`  
_L28-36_
- reflection: `UENUM()`
- L30 _public enumerator_ `Red`
- L31 _public enumerator_ `Green`
- L32 _public enumerator_ `Blue`
- L33 _public enumerator_ `Alpha`
- L35 _public enumerator_ `MAX_None UMETA(Hidden)`

#### struct `FFoliageVertexColorChannelMask`  
`struct FFoliageVertexColorChannelMask`  
_L39-65_
- reflection: `USTRUCT()`
- L47 _public member_ `uint32 UseMask:1;` — `UPROPERTY(EditAnywhere, Category=VertexColorMask)` — When checked, foliage will be masked from this mesh using this color channel
- L51 _public member_ `float MaskThreshold;` — `UPROPERTY(EditAnywhere, Category=VertexColorMask)` — Specifies the threshold value above which the static mesh vertex color value must be, in order for foliage instances to be placed in a specific area
- L58 _public member_ `uint32 InvertMask:1;` — `UPROPERTY(EditAnywhere, Category=VertexColorMask)` — When unchecked, foliage instances will be placed only when the vertex color in the specified channel(s) is above the threshold amount. When checked, the vertex color must be less than the threshold amount
- L60 _public function_ `FFoliageVertexColorChannelMask() : UseMask(false) , MaskThreshold(0.5f) , InvertMask(false)`

#### enum `EFoliageScaling`  
`enum class EFoliageScaling : uint8`  
_L68-80_
- reflection: `UENUM()`
- L71 _public enumerator_ `Uniform` — Foliage instances will have uniform X,Y and Z scales.
- L73 _public enumerator_ `Free` — Foliage instances will have random X,Y and Z scales.
- L75 _public enumerator_ `LockXY` — Locks the X and Y axis scale.
- L77 _public enumerator_ `LockXZ` — Locks the X and Z axis scale.
- L79 _public enumerator_ `LockYZ` — Locks the Y and Z axis scale.

#### struct `FFoliageDensityFalloff`  
`struct FFoliageDensityFalloff`  
_L83-102_
- reflection: `USTRUCT()`
- L87 _public prototype_ `FFoliageDensityFalloff();`
- L90 _public member_ `bool bUseFalloffCurve = false;` — `UPROPERTY(Category = Procedural, EditAnywhere, meta = (Subcategory = "Density"))`
- L98 _public member_ `FRuntimeFloatCurve FalloffCurve;` — `UPROPERTY(Category = Procedural, EditAnywhere, meta = (Subcategory = "Density", XAxisName = "Normalized Distance", YAxisName = "Density Factor"))` — Density as a function of normalized distance (i.e. distance from Procedural Foliage Volume / Max Volume Extent). X = 0 corresponds to Normalized distance = 0, X = 1 corresponds to Normalized distance = Max distance. Y = 0 corresponds to 0% probability of keeping instance, Y = 1 corresponds to 100% probability of keeping instance.
- L100 _public prototype_ `bool IsInstanceFiltered(const FVector2D& Position, const FVector2D& Origin, FVector::FReal MaxDistance) const;`
- L101 _public prototype_ `float GetDensityFalloffValue(const FVector2D& Position, const FVector2D& Origin, FVector::FReal MaxDistance) const;`

#### class `UFoliageType`  
`class UFoliageType : public UObject`  
_L105-699_
- reflection: `UCLASS(abstract, hidecategories = Object, editinlinenew, MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UObject`
- L110 _private prototype_ `virtual UObject* GetSource() const PURE_VIRTUAL(UFoliageType::GetSource, return nullptr; );` — Gets/Sets the source data associated with this FoliageType
- L112 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L113 _private prototype_ `virtual void PostLoad() override;`
- L115 _private prototype_ `virtual bool IsNotAssetOrBlueprint() const;`
- L116 _private prototype_ `FVector3f GetRandomScale() const;`
- L119 _private function_ `virtual FString GetDefaultNewAssetName() const`
- L124 _private prototype_ `virtual void SetSource(UObject* InSource) PURE_VIRTUAL(UFoliageType::SetSource, );`
- L125 _private function_ `virtual void UpdateBounds()`
- L127 _private function_ `virtual bool IsFoliageReallocationRequiredForPropertyChange(const FProperty* Property) const` — Lets subclasses decide if the InstancedFoliageActor should reallocate its instances if the specified property change event occurs
- L129 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L130 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L131 _private function_ `virtual bool IsSourcePropertyChange(const FProperty* Property) const`
- L134 _private prototype_ `void OnHiddenEditorViewMaskChanged(UWorld* InWorld);` — Notifies all relevant foliage actors that HiddenEditorView mask has been changed
- L137 _private prototype_ `FName GetDisplayFName() const;` — Nice and clean name for user interface
- L143 _private member_ `FGuid UpdateGuid;` — `UPROPERTY()` — A GUID that is updated every time the foliage type is modified, so foliage placed in the level can detect the FoliageType has changed.
- L151 _public member_ `float Density;` — `UPROPERTY(EditAnywhere, Category=Painting, meta=(DisplayName="Density / 1Kuu", UIMin = 0, ClampMin = 0, UIMax = 10000, ClampMax = 10000))` — Foliage instances will be placed at this density, specified in instances per 1000x1000 unit area
- L155 _public member_ `float DensityAdjustmentFactor;` — `UPROPERTY(EditAnywhere, Category=Painting, meta=(UIMin=0, ClampMin=0, UIMax = 1000, ClampMax = 1000, ReapplyCondition="ReapplyDensity"))` — The factor by which to adjust the density of instances. Values >1 will increase density while values <1 will decrease it.
- L159 _public member_ `float Radius;` — `UPROPERTY(EditAnywhere, Category=Painting, meta=(UIMin=0, ClampMin=0, UIMax = 100000, ClampMax = 100000, ReapplyCondition="ReapplyRadius"))` — The minimum distance between foliage instances
- L163 _public member_ `bool bSingleInstanceModeOverrideRadius = false;` — `UPROPERTY(EditAnywhere, Category = Painting)` — Option to override radius used to detect collision with other instances when painting in single instance mode
- L167 _public member_ `float SingleInstanceModeRadius = 0.f;` — `UPROPERTY(EditAnywhere, Category = Painting, meta = (EditCondition = "bSingleInstanceModeOverrideRadius", UIMin = 0, ClampMin = 0, UIMax = 100000, ClampMax = 100000))` — The radius used in single instance mode to detect collision with other instances
- L171 _public member_ `EFoliageScaling Scaling;` — `UPROPERTY(EditAnywhere, Category=Painting, meta=(ReapplyCondition="ReapplyScaling"))` — Specifies foliage instance scaling behavior when painting.
- L175 _public member_ `FFloatInterval ScaleX;` — `UPROPERTY(EditAnywhere, Category=Painting, meta=(ClampMin="0.001", UIMin="0.001", ReapplyCondition="ReapplyScaleX"))` — Specifies the range of scale, from minimum to maximum, to apply to a foliage instance's X Scale property
- L179 _public member_ `FFloatInterval ScaleY;` — `UPROPERTY(EditAnywhere, Category=Painting, meta=(ClampMin="0.001", UIMin="0.001", ReapplyCondition="ReapplyScaleY"))` — Specifies the range of scale, from minimum to maximum, to apply to a foliage instance's Y Scale property
- L183 _public member_ `FFloatInterval ScaleZ;` — `UPROPERTY(EditAnywhere, Category=Painting, meta=(ClampMin="0.001", UIMin="0.001", ReapplyCondition="ReapplyScaleZ"))` — Specifies the range of scale, from minimum to maximum, to apply to a foliage instance's Z Scale property
- L186 _public member_ `FFoliageVertexColorChannelMask VertexColorMaskByChannel[(uint8)EVertexColorMaskChannel::MAX_None];` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Painting, meta=(HideBehind="VertexColorMask"))`
- L197 _public member_ `float VertexColorMaskThreshold_DEPRECATED;` — `UPROPERTY()` — Specifies the threshold value above which the static mesh vertex color value must be, in order for foliage instances to be placed in a specific area
- L204 _public member_ `uint32 VertexColorMaskInvert_DEPRECATED:1;` — `UPROPERTY()` — When unchecked, foliage instances will be placed only when the vertex color in the specified channel(s) is above the threshold amount. When checked, the vertex color must be less than the threshold amount
- L211 _public member_ `FFloatInterval ZOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(DisplayName="Z Offset", ReapplyCondition="ReapplyZOffset"))` — Specifies a range from minimum to maximum of the offset to apply to a foliage instance's Z location
- L216 _public member_ `uint32 AlignToNormal:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(ReapplyCondition="ReapplyAlignToNormal"))` — Whether foliage instances should have their angle adjusted away from vertical to match the normal of the surface they're painted on If AlignToNormal is enabled and RandomYaw is disabled, the instance will be rotated so that the +X axis points down-slope
- L220 _public member_ `uint32 AverageNormal:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(ToolTip="Will average normal based on Foliage Type base radius (this as a cost as it will do extra line traces)"))` — Whether the normal should be averaged on a number of samples around the hit location
- L224 _public member_ `uint32 AverageNormalSingleComponent:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Placement, meta = (EditCondition = "AverageNormal", ToolTip = "Whether to discard normals originating from other hit components or not when averaging normals"))` — Average Normal should use all hit components or only the original hit component
- L228 _public member_ `float AlignMaxAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, HideBehind="AlignToNormal"))` — The maximum angle in degrees that foliage instances will be adjusted away from the vertical
- L232 _public member_ `uint32 RandomYaw:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(ReapplyCondition="ReapplyRandomYaw"))` — If selected, foliage instances will have a random yaw rotation around their vertical axis applied
- L236 _public member_ `float RandomPitchAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, ReapplyCondition="ReapplyRandomPitchAngle"))` — A random pitch adjustment can be applied to each instance, up to the specified angle in degrees, from the original vertical
- L240 _public member_ `FFloatInterval GroundSlopeAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin=0, ClampMin = 0, UIMax = 359, ClampMax = 359, ReapplyCondition="ReapplyGroundSlope"))` — Foliage instances will only be placed on surfaces sloping in the specified angle range from the horizontal
- L244 _public member_ `FFloatInterval Height;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(ReapplyCondition="ReapplyHeight"))` — The valid altitude range where foliage instances will be placed, specified using minimum and maximum world coordinate Z values
- L248 _public member_ `TArray<FName> LandscapeLayers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category=Placement, meta=(ReapplyCondition="ReapplyLandscapeLayers", DisplayName="Inclusion Landscape Layers"))` — If layer names are specified, painting on landscape will limit the foliage to areas of landscape with the specified layers painted
- L252 _public member_ `float MinimumLayerWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category=Placement, meta=(UIMin=0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideBehind="LandscapeLayers", DisplayName="Minimum Inclusion Landscape Weight"))` — Specifies the minimum value above which the landscape layer weight value must be, in order for foliage instances to be placed in a specific area
- L256 _public member_ `TArray<FName> ExclusionLandscapeLayers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Placement, meta = (ReapplyCondition = "ReapplyLandscapeLayers"))` — If layer names are specified, painting on landscape will exclude the foliage to areas of landscape without the specified layers painted
- L260 _public member_ `float MinimumExclusionLayerWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Placement, meta = (UIMin=0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideBehind = "ExclusionLandscapeLayers"))` — Specifies the minimum value above which the landscape exclusion layer weight value must be, in order for foliage instances to be excluded in a specific area
- L263 _public member_ `FName LandscapeLayer_DEPRECATED;` — `UPROPERTY()`
- L267 _public member_ `uint32 CollisionWithWorld:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category=Placement, meta=(ReapplyCondition="ReapplyCollisionWithWorld"))` — If checked, an overlap test with existing world geometry is performed before each instance is placed
- L271 _public member_ `FVector CollisionScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category=Placement, meta=(HideBehind="CollisionWithWorld"))` — The foliage instance's collision bounding box will be scaled by the specified amount before performing the overlap check
- L275 _public member_ `int32 AverageNormalSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Placement, meta=(EditCondition="AverageNormal"))` — Line trace count to use around hit location when averaging normal
- L278 _public member_ `FBoxSphereBounds MeshBounds;` — `UPROPERTY()`
- L282 _public member_ `FVector LowBoundOriginRadius;` — `UPROPERTY()` — X, Y is origin position and Z is radius...
- L289 _public member_ `TEnumAsByte<EComponentMobility::Type> Mobility;` — `UPROPERTY(Category = InstanceSettings, EditAnywhere, BlueprintReadOnly)` — Mobility property to apply to foliage components
- L296 _public member_ `FInt32Interval CullDistance;` — `UPROPERTY(EditAnywhere, Category=InstanceSettings, meta=(UIMin=0))` — The distance where instances will begin to fade out if using a PerInstanceFadeAmount material node. 0 disables. When the entire cluster is beyond this distance, the cluster is completely culled and not rendered at all.
- L300 _public member_ `uint32 bEnableStaticLighting_DEPRECATED : 1;` — `UPROPERTY()` — Deprecated. Now use the Mobility setting to control static/dynamic lighting
- L304 _public member_ `uint32 CastShadow:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings)` — Controls whether the foliage should cast a shadow or not.
- L308 _public member_ `uint32 bAffectDynamicIndirectLighting:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings, meta=(EditCondition="CastShadow"))` — Controls whether the foliage should inject light into the Light Propagation Volume.  This flag is only used if CastShadow is true.
- L312 _public member_ `uint32 bAffectDistanceFieldLighting:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings, meta=(EditCondition="CastShadow"))` — Controls whether the primitive should affect dynamic distance field lighting methods.  This flag is only used if CastShadow is true.
- L316 _public member_ `uint32 bCastDynamicShadow:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings, meta=(EditCondition="CastShadow"))` — Controls whether the foliage should cast shadows in the case of non precomputed shadowing.  This flag is only used if CastShadow is true.
- L320 _public member_ `uint32 bCastStaticShadow:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings, meta=(EditCondition="CastShadow"))` — Whether the foliage should cast a static shadow from shadow casting lights.  This flag is only used if CastShadow is true.
- L324 _public member_ `uint8 bCastContactShadow : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings, meta=(EditCondition = "CastShadow"))` — Whether the object should cast contact shadows. This flag is only used if CastShadow is true.
- L328 _public member_ `uint32 bCastShadowAsTwoSided:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings, meta=(EditCondition="bCastDynamicShadow"))` — Whether this foliage should cast dynamic shadows as if it were a two sided material.
- L332 _public member_ `uint32 bReceivesDecals : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings)` — Whether the foliage receives decals.
- L336 _public member_ `uint32 bOverrideLightMapRes:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings, meta=(InlineEditConditionToggle))` — Whether to override the lightmap resolution defined in the static mesh.
- L340 _public member_ `EShadowCacheInvalidationBehavior ShadowCacheInvalidationBehavior;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings, meta=(EditCondition="CastShadow"))` — Control shadow invalidation behavior, in particular with respect to Virtual Shadow Maps and material effects like World Position Offset.
- L344 _public member_ `int32 OverriddenLightMapRes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings, meta=(DisplayName="Light Map Resolution", EditCondition="bOverrideLightMapRes"))` — Overrides the lightmap resolution defined in the static mesh
- L348 _public member_ `ELightmapType LightmapType;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings)` — Controls the type of lightmap used for this component.
- L355 _public member_ `uint32 bUseAsOccluder : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = InstanceSettings)` — If enabled, foliage will render a pre-pass which allows it to occlude other primitives, and also allows it to correctly receive DBuffer decals. Enabling this setting may have a negative performance impact.
- L358 _public member_ `uint8 bVisibleInRayTracing : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = InstanceSettings)`
- L361 _public member_ `uint8 bVisibleInReflections : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = InstanceSettings)`
- L364 _public member_ `uint8 bEvaluateWorldPositionOffset : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = InstanceSettings)`
- L367 _public member_ `int32 WorldPositionOffsetDisableDistance;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = InstanceSettings, meta = (ClampMin=0))`
- L371 _public member_ `float NanitePixelProgrammableDistance = 0.0f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = InstanceSettings, meta = (ClampMin = 0))` — Used to forcefully disable pixel programmable rasterization of Nanite when the mesh is further than a given distance from the camera.
- L375 _public member_ `struct FBodyInstance BodyInstance;` — `UPROPERTY(EditAnywhere, Category=InstanceSettings, meta=(HideObjectType=true))` — Custom collision for foliage
- L379 _public member_ `TEnumAsByte<EHasCustomNavigableGeometry::Type> CustomNavigableGeometry;` — `UPROPERTY(EditAnywhere, Category=InstanceSettings, meta=(HideObjectType=true))` — Force navmesh
- L386 _public member_ `FLightingChannels LightingChannels;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings)` — Lighting channels that placed foliage will be assigned. Lights with matching channels will affect the foliage. These channels only apply to opaque materials, direct lighting, and dynamic lighting and shadowing.
- L390 _public member_ `uint32 bRenderCustomDepth:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings, meta=(DisplayName = "Render CustomDepth Pass"))` — If true, the foliage will be rendered in the CustomDepth pass (usually used for outlines)
- L394 _public member_ `ERendererStencilMask CustomDepthStencilWriteMask;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings, meta = (editcondition = "bRenderCustomDepth"))` — Mask used for stencil buffer writes.
- L398 _public member_ `int32 CustomDepthStencilValue;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=InstanceSettings, meta=(UIMin = "0", UIMax = "255", editcondition = "bRenderCustomDepth", DisplayName = "CustomDepth Stencil Value"))` — Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3)
- L410 _public member_ `int32 TranslucencySortPriority;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InstanceSettings)` — Translucent objects with a lower sort priority draw behind objects with a higher priority. Translucent objects with the same priority are rendered from back-to-front based on their bounds origin. This setting is also used to sort objects being drawn into a runtime virtual texture. Ignored if the object is not translucent.  The default priority is zero. Warning: This should never be set to a non-default value unless you know what you are doing, as it will prevent the renderer from sorting correctly. It is especially problematic on dynamic gameplay effects.
- L415 _public member_ `uint64 HiddenEditorViews;` — `UPROPERTY(transient)` — Bitflag to represent in which editor views this foliage mesh is hidden.
- L418 _public member_ `uint32 IsSelected:1;` — `UPROPERTY(transient)`
- L421 _public function_ `float GetRadius(bool bInSingleInstanceMode) const`
- L425 _public function_ `float GetSeedDensitySquared() const`
- L426 _public prototype_ `float GetMaxRadius() const;`
- L427 _public prototype_ `float GetScaleForAge(const float Age) const;`
- L428 _public prototype_ `float GetInitAge(FRandomStream& RandomStream) const;`
- L429 _public prototype_ `float GetNextAge(const float CurrentAge, const int32 NumSteps) const;`
- L430 _public prototype_ `bool GetSpawnsInShade() const;`
- L436 _public member_ `float CollisionRadius;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Collision", ClampMin="0.0", UIMin="0.0"))` — The CollisionRadius determines when two instances overlap. When two instances overlap a winner will be picked based on rules and priority.
- L440 _public member_ `float ShadeRadius;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Collision", ClampMin="0.0", UIMin="0.0"))` — The ShadeRadius determines when two instances overlap. If an instance can grow in the shade this radius is ignored.
- L444 _public member_ `int32 NumSteps;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Clustering", ClampMin="0", UIMin="0"))` — The number of times we age the species and spread its seeds.
- L450 _public member_ `float InitialSeedDensity;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Clustering", ClampMin="0.0", UIMin="0.0"))` — Specifies the number of seeds to populate along 10 meters. The number is implicitly squared to cover a 10m x 10m area
- L454 _public member_ `float AverageSpreadDistance;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Clustering", ClampMin="0.0", UIMin="0.0"))` — The average distance between the spreading instance and its seeds. For example, a tree with an AverageSpreadDistance 10 will ensure the average distance between the tree and its seeds is 10cm
- L458 _public member_ `float SpreadVariance;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Clustering", ClampMin="0.0", UIMin="0.0"))` — Specifies how much seed distance varies from the average. For example, a tree with an AverageSpreadDistance 10 and a SpreadVariance 1 will produce seeds with an average distance of 10cm plus or minus 1cm
- L462 _public member_ `int32 SeedsPerStep;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Clustering", ClampMin="0", UIMin="0"))` — The number of seeds an instance will spread in a single step of the simulation.
- L466 _public member_ `int32 DistributionSeed;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Clustering"))` — The seed that determines placement of initial seeds.
- L470 _public member_ `float MaxInitialSeedOffset;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Clustering"))` — The max seed used to compute global offset.
- L476 _public member_ `bool bCanGrowInShade;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Growth"))` — If true, seeds of this type will ignore shade radius during overlap tests with other types.
- L483 _public member_ `bool bSpawnsInShade;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Growth", EditCondition="bCanGrowInShade"))` — Whether new seeds are spawned exclusively in shade. Occurs in a second pass after all types that do not spawn in shade have been simulated. Only valid when CanGrowInShade is true.
- L487 _public member_ `float MaxInitialAge;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Growth", ClampMin="0.0", UIMin="0.0"))` — Allows a new seed to be older than 0 when created. New seeds will be randomly assigned an age in the range [0,MaxInitialAge]
- L491 _public member_ `float MaxAge;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Growth", ClampMin="0.0", UIMin="0.0"))` — Specifies the oldest a seed can be. After reaching this age the instance will still spread seeds, but will not get any older
- L499 _public member_ `float OverlapPriority;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta=(Subcategory="Growth"))` — When two instances overlap we must determine which instance to remove. The instance with a lower OverlapPriority will be removed. In the case where OverlapPriority is the same regular simulation rules apply.
- L503 _public member_ `FFloatInterval ProceduralScale;` — `UPROPERTY(Category=Procedural, EditAnywhere, meta = (Subcategory = "Growth", ClampMin = "0.001", UIMin = "0.001"))` — The scale range of this type when being procedurally generated. Configured with the Scale Curve.
- L511 _public member_ `FRuntimeFloatCurve ScaleCurve;` — `UPROPERTY(Category = Procedural, EditAnywhere, meta = (Subcategory = "Growth", XAxisName = "Normalized Age", YAxisName = "Scale Factor"))` — Instance scale factor as a function of normalized age (i.e. Current Age / Max Age). X = 0 corresponds to Age = 0, X = 1 corresponds to Age = Max Age. Y = 0 corresponds to Min Scale, Y = 1 corresponds to Max Scale.
- L514 _public member_ `FFoliageDensityFalloff DensityFalloff;` — `UPROPERTY(Category = Procedural, EditAnywhere)`
- L517 _public member_ `int32 ChangeCount;` — `UPROPERTY(Transient)`
- L524 _public member_ `uint32 ReapplyDensity:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, the density of foliage instances already placed will be adjusted by the density adjustment factor.
- L528 _public member_ `uint32 ReapplyRadius:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances not meeting the new Radius constraint will be removed
- L532 _public member_ `uint32 ReapplyAlignToNormal:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their normal alignment adjusted by the Reapply tool
- L536 _public member_ `uint32 ReapplyRandomYaw:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their yaw adjusted by the Reapply tool
- L540 _public member_ `uint32 ReapplyScaling:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their scale adjusted to fit the specified scaling behavior by the Reapply tool
- L544 _public member_ `uint32 ReapplyScaleX:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their X scale adjusted by the Reapply tool
- L548 _public member_ `uint32 ReapplyScaleY:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their Y scale adjusted by the Reapply tool
- L552 _public member_ `uint32 ReapplyScaleZ:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their Z scale adjusted by the Reapply tool
- L556 _public member_ `uint32 ReapplyRandomPitchAngle:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their pitch adjusted by the Reapply tool
- L560 _public member_ `uint32 ReapplyGroundSlope:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances not meeting the ground slope condition will be removed by the Reapply too
- L564 _public member_ `uint32 ReapplyHeight:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances not meeting the valid Z height condition will be removed by the Reapply tool
- L568 _public member_ `uint32 ReapplyLandscapeLayers:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances painted on areas that do not have the appropriate landscape layer painted will be removed by the Reapply tool
- L572 _public member_ `uint32 ReapplyZOffset:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have their Z offset adjusted by the Reapply tool
- L576 _public member_ `uint32 ReapplyCollisionWithWorld:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances will have an overlap test with the world reapplied, and overlapping instances will be removed by the Reapply tool
- L580 _public member_ `uint32 ReapplyVertexColorMask:1;` — `UPROPERTY(EditDefaultsOnly, Category=Reapply)` — If checked, foliage instances no longer matching the vertex color constraint will be removed by the Reapply too
- L591 _public member_ `uint32 bEnableDensityScaling:1;` — `UPROPERTY(EditAnywhere, Category=Scalability)` — Whether this foliage type should be affected by the Engine Scalability system's Foliage scalability setting. Enable for detail meshes that don't really affect the game. Disable for anything important. Typically, this will be enabled for small meshes without collision (e.g. grass) and disabled for large meshes with collision (e.g. trees)
- L597 _public member_ `uint32 bEnableDiscardOnLoad:1;` — `UPROPERTY(EditAnywhere, Category=Scalability)` — Whether this foliage type should be discarded when CVarFoliageDiscardDataOnLoad is enabled.
- L603 _public member_ `uint32 bEnableCullDistanceScaling : 1;` — `UPROPERTY(EditAnywhere, Category = Scalability)` — Whether this foliage type should be affected by the Engine's "foliage.CullDistanceScale" setting
- L613 _public member_ `TArray<TObjectPtr<URuntimeVirtualTexture>> RuntimeVirtualTextures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=VirtualTexture, meta = (DisplayName = "Draw in Virtual Textures"))` — Array of runtime virtual textures into which we draw the instances. The mesh material also needs to be set up to output to a virtual texture.
- L621 _public member_ `int32 VirtualTextureCullMips = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = VirtualTexture, meta = (DisplayName = "Virtual Texture Skip Mips", UIMin = "0", UIMax = "7"))` — Number of lower mips in the runtime virtual texture to skip for rendering this primitive. Larger values reduce the effective draw distance in the runtime virtual texture. This culling method doesn't take into account primitive size or virtual texture size.
- L625 _public member_ `ERuntimeVirtualTextureMainPassType VirtualTextureRenderPassType = ERuntimeVirtualTextureMainPassType::Exclusive;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VirtualTexture, meta = (DisplayName = "Draw in Main Pass"))` — Controls if this component draws in the main pass as well as in the virtual texture.
- L632 _public member_ `uint32 bIncludeInHLOD:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HLOD)`
- L640 _private member_ `float ScaleMinX_DEPRECATED;` — `UPROPERTY()` — Deprecated since FFoliageCustomVersion::FoliageTypeCustomization
- L643 _private member_ `float ScaleMinY_DEPRECATED;` — `UPROPERTY()`
- L646 _private member_ `float ScaleMinZ_DEPRECATED;` — `UPROPERTY()`
- L649 _private member_ `float ScaleMaxX_DEPRECATED;` — `UPROPERTY()`
- L652 _private member_ `float ScaleMaxY_DEPRECATED;` — `UPROPERTY()`
- L655 _private member_ `float ScaleMaxZ_DEPRECATED;` — `UPROPERTY()`
- L658 _private member_ `float HeightMin_DEPRECATED;` — `UPROPERTY()`
- L661 _private member_ `float HeightMax_DEPRECATED;` — `UPROPERTY()`
- L664 _private member_ `float ZOffsetMin_DEPRECATED;` — `UPROPERTY()`
- L667 _private member_ `float ZOffsetMax_DEPRECATED;` — `UPROPERTY()`
- L670 _private member_ `int32 StartCullDistance_DEPRECATED;` — `UPROPERTY()`
- L673 _private member_ `int32 EndCullDistance_DEPRECATED;` — `UPROPERTY()`
- L676 _private member_ `uint32 UniformScale_DEPRECATED:1;` — `UPROPERTY()`
- L679 _private member_ `uint32 LockScaleX_DEPRECATED:1;` — `UPROPERTY()`
- L682 _private member_ `uint32 LockScaleY_DEPRECATED:1;` — `UPROPERTY()`
- L685 _private member_ `uint32 LockScaleZ_DEPRECATED:1;` — `UPROPERTY()`
- L688 _private member_ `float GroundSlope_DEPRECATED;` — `UPROPERTY()`
- L691 _private member_ `float MinGroundSlope_DEPRECATED;` — `UPROPERTY()`
- L694 _private member_ `float MinScale_DEPRECATED;` — `UPROPERTY()`
- L697 _private member_ `float MaxScale_DEPRECATED;` — `UPROPERTY()`

### `Source/Runtime/Foliage/Public/FoliageTypeObject.h` (Public)


#### struct `FFoliageTypeObject`  
`struct FFoliageTypeObject`  
_L14-58_
- reflection: `USTRUCT()`
- desc: A wrapper struct used to allow the use of either FoliageType assets or FoliageType blueprint classes
- L18 _public function_ `FFoliageTypeObject() : FoliageTypeObject(nullptr), TypeInstance(nullptr), bIsAsset(false)`
- L22 _public prototype_ `void RefreshInstance();` — Refreshes the type instance based on the assigned object. Intended to be called after some change is made.
- L25 _public prototype_ `const UFoliageType* GetInstance();` — Gets the instance of this foliage type. Creates the instance if needed.
- L28 _public prototype_ `const UFoliageType* GetInstance() const;` — Gets the instance of this foliage type.
- L31 _public prototype_ `bool ContainsValidInstance() const;` — @return Whether this would return a valid instance
- L34 _public prototype_ `bool HasFoliageType() const;` — @return Whether any foliage type is assigned at all
- L36 _public prototype_ `bool IsDirty() const;`
- L37 _public prototype_ `void SetClean();`
- L40 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L46 _private member_ `TObjectPtr<UObject> FoliageTypeObject;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere, meta=(AllowedClasses="/Script/Foliage.FoliageType_InstancedStaticMesh,/Script/Foliage.FoliageType_Actor,/Script/Engine.Blueprint", DisplayThumbnail="true", ThumbnailSize="X=40 Y=40"))` — The foliage type that will be spawned by the procedural foliage simulation
- L50 _private member_ `TObjectPtr<UFoliageType> TypeInstance;` — `UPROPERTY(transient)` — The actual instance of the foliage type that is used for spawning
- L54 _private member_ `bool bIsAsset;` — `UPROPERTY()` — Whether this contains an asset object (as opposed to a BP class)
- L57 _private member_ `TSubclassOf<UFoliageType_InstancedStaticMesh> Type_DEPRECATED;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FFoliageTypeObject> : public TStructOpsTypeTraitsBase2<FFoliageTypeObject>`  
_L62-68_
- inherits: `TStructOpsTypeTraitsBase2<FFoliageTypeObject>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L65-67_

#### Free symbols / members of external scopes

- L66 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonae1986830103`)

### `Source/Runtime/Foliage/Public/FoliageType_Actor.h` (Public)


#### class `UFoliageType_Actor`  
`class UFoliageType_Actor : public UFoliageType`  
_L11-46_
- reflection: `UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)`
- inherits: `UFoliageType`
- L16 _private member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, Category = Actor)`
- L19 _private member_ `bool bShouldAttachToBaseComponent;` — `UPROPERTY(EditAnywhere, Category = Actor)`
- L22 _private member_ `bool bStaticMeshOnly;` — `UPROPERTY(EditAnywhere, Category = Mesh, meta = (ToolTip = "If enabled, will place an instanced static mesh representation of this actor without placing an actual actor"))`
- L25 _private member_ `TSubclassOf<UFoliageInstancedStaticMeshComponent> StaticMeshOnlyComponentClass;` — `UPROPERTY(EditAnywhere, Category = Mesh, meta = (EditCondition = "bStaticMeshOnly"))`
- L27 _private function_ `virtual UObject* GetSource() const override`
- L30 _private function_ `virtual FString GetDefaultNewAssetName() const override`
- L35 _private prototype_ `virtual void UpdateBounds();`
- L36 _private function_ `virtual bool IsSourcePropertyChange(const FProperty* Property) const override`
- L40 _private function_ `virtual void SetSource(UObject* InSource) override`

### `Source/Runtime/Foliage/Public/FoliageType_InstancedStaticMesh.h` (Public)


#### class `UFoliageType_InstancedStaticMesh`  
`class UFoliageType_InstancedStaticMesh : public UFoliageType`  
_L13-62_
- reflection: `UCLASS(hidecategories=Object, editinlinenew, MinimalAPI)`
- inherits: `UFoliageType`
- L18 _private member_ `TObjectPtr<UStaticMesh> Mesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh, meta=(DisplayThumbnail="true"))`
- L21 _private member_ `TArray<TObjectPtr<class UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Mesh, Meta = (ToolTip = "Material overrides for foliage instances."))`
- L24 _private member_ `TArray<TObjectPtr<class UMaterialInterface>> NaniteOverrideMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Mesh, Meta = (ToolTip = "Nanite material overrides for foliage instances."))`
- L29 _private member_ `TSubclassOf<UFoliageInstancedStaticMeshComponent> ComponentClass;` — `UPROPERTY(EditAnywhere, Category = Mesh)` — The component class to use for foliage instances. You can make a Blueprint subclass of FoliageInstancedStaticMeshComponent to implement custom behavior and assign that class here.
- L31 _private function_ `UStaticMesh* GetStaticMesh() const`
- L36 _private function_ `UClass* GetComponentClass() const`
- L41 _private prototype_ `virtual UObject* GetSource() const override;`
- L44 _private function_ `virtual FString GetDefaultNewAssetName() const override`
- L49 _private prototype_ `virtual void UpdateBounds() override;`
- L50 _private function_ `virtual bool IsSourcePropertyChange(const FProperty* Property) const override`
- L54 _private prototype_ `virtual void SetSource(UObject* InSource) override;`
- L56 _private function_ `void SetStaticMesh(UStaticMesh* InStaticMesh)`

### `Source/Runtime/Foliage/Public/GrassInstancedStaticMeshComponent.h` (Public)


#### class `UGrassInstancedStaticMeshComponent`  
`class UGrassInstancedStaticMeshComponent : public UHierarchicalInstancedStaticMeshComponent`  
_L10-29_
- reflection: `UCLASS(ClassGroup = Foliage, MinimalAPI, Hidden)`
- inherits: `UHierarchicalInstancedStaticMeshComponent`
- L15 _public prototype_ `static void BuildTreeAnyThread(TArray<FMatrix>& InstanceTransforms, TArray<float>& InstanceCustomDataFloats, int32 NumCustomDataFloats, const FBox& MeshBox, TArray<FClusterNode>& OutClusterTree, TArray<int32>& OutSortedInstances, TArray<int32>& OutInstanceReorderTable, int32& OutOcclusionLayerNum, int32 MaxInstancesPerLeaf, bool InGenerateInstanceScalingRange);`
- L17 _public prototype_ `void AcceptPrebuiltTree(TArray<FClusterNode>& InClusterTree, int32 InOcclusionLayerNumNodes, int32 InNumBuiltRenderInstances, FStaticMeshInstanceData* InSharedInstanceBufferData);`
- L19 _public prototype_ `bool SupportsWorldPositionOffsetVelocity() const override;`
- L21 _public function_ `int32 GetNumRenderInstances() const override`
- L24 _private prototype_ `virtual void BuildTree() override final;`
- L25 _private prototype_ `virtual void BuildTreeAsync() override final;`
- L27 _private prototype_ `virtual void BuildComponentInstanceData(ERHIFeatureLevel::Type FeatureLevel, FInstanceUpdateComponentDesc& OutData) override final;` — `UE_DEPRECATED(5.7, "Please use BuildComponentInstanceData with EShaderPlatform argument and not ERHIFeatureLevel::Type")`
- L28 _private prototype_ `virtual void BuildComponentInstanceData(EShaderPlatform InShaderPlatform, FInstanceUpdateComponentDesc& OutData) override final;`

### `Source/Runtime/Foliage/Public/InstancedFoliage.h` (Public)


#### enum `EFoliageInstanceFlags`  
`enum EFoliageInstanceFlags`  
_L38-44_
- desc: Flags stored with each instance
- L40 _public enumerator_ `FOLIAGE_AlignToNormal = 0x00000001`
- L41 _public enumerator_ `FOLIAGE_NoRandomYaw = 0x00000002`
- L42 _public enumerator_ `FOLIAGE_Readjusted = 0x00000004`
- L43 _public enumerator_ `FOLIAGE_InstanceDeleted = 0x00000008` — Used only for migration from pre-HierarchicalISM foliage.

#### struct `FFoliageInstancePlacementInfo`  
`struct FFoliageInstancePlacementInfo`  
_L49-66_
- desc: FFoliageInstancePlacementInfo - placement info an individual instance
- L51 _public member_ `FVector Location;`
- L52 _public member_ `FRotator Rotation;`
- L53 _public member_ `FRotator PreAlignRotation;`
- L54 _public member_ `FVector3f DrawScale3D;`
- L55 _public member_ `float ZOffset;`
- L56 _public member_ `uint32 Flags;`
- L58 _public function_ `FFoliageInstancePlacementInfo() : Location(0.f, 0.f, 0.f) , Rotation(0, 0, 0) , PreAlignRotation(0, 0, 0) , DrawScale3D(1.f, 1.f, 1.f) , ZOffset(0.f) , Flags(0)`

#### struct `FFoliageInstance_Deprecated`  
`struct FFoliageInstance_Deprecated : public FFoliageInstancePlacementInfo`  
_L71-76_
- inherits: `FFoliageInstancePlacementInfo`
- desc: Legacy instance
- L73 _public member_ `UActorComponent* Base;`
- L74 _public member_ `FGuid ProceduralGuid;`

#### struct `FFoliageInstance`  
`struct FFoliageInstance : public FFoliageInstancePlacementInfo`  
_L81-136_
- inherits: `FFoliageInstancePlacementInfo`
- desc: FFoliageInstance - editor info an individual instance
- L84 _public member_ `FFoliageInstanceBaseId BaseId;` — ID of base this instance was painted on
- L86 _public member_ `FGuid ProceduralGuid;`
- L88 _public member_ `UActorComponent* BaseComponent;`
- L90 _public function_ `FFoliageInstance() : BaseId(0) , BaseComponent(nullptr)`
- L97 _public function_ `FTransform GetInstanceWorldTransform() const`
- L102 _public function_ `void SetInstanceWorldTransform(const FTransform& Transform)`
- L109 _public function_ `void AlignToNormal(const FVector& InNormal, float AlignMaxAngle = 0.f)`

#### struct `FFoliageMeshInfo_Deprecated`  
`struct FFoliageMeshInfo_Deprecated`  
_L138-156_
- L140 _public member_ `UHierarchicalInstancedStaticMeshComponent* Component;`
- L144 _public member_ `FGuid FoliageTypeUpdateGuid;` — Allows us to detect if FoliageType was updated while this level wasn't loaded
- L147 _public member_ `TArray<FFoliageInstance_Deprecated> Instances;` — Editor-only placed instances
- L150 _public function_ `FFoliageMeshInfo_Deprecated() : Component(nullptr)`

#### struct `FFoliageMeshInfo_Deprecated2`  
`struct FFoliageMeshInfo_Deprecated2`  
_L161-177_
- desc: FFoliageInfo - editor info for all matching foliage meshes
- L163 _public member_ `UHierarchicalInstancedStaticMeshComponent* Component;`
- L167 _public member_ `FGuid FoliageTypeUpdateGuid;` — Allows us to detect if FoliageType was updated while this level wasn't loaded
- L170 _public member_ `TArray<FFoliageInstance> Instances;` — Editor-only placed instances
- L174 _public prototype_ `FFoliageMeshInfo_Deprecated2();`

#### enum `EFoliageImplType`  
`enum class EFoliageImplType : uint8`  
_L182-188_
- L184 _public enumerator_ `Unknown = 0`
- L185 _public enumerator_ `StaticMesh = 1`
- L186 _public enumerator_ `Actor = 2`
- L187 _public enumerator_ `ISMActor = 3`

#### struct `FFoliageImpl`  
`struct FFoliageImpl`  
_L195-265_
- L197 _public function_ `FFoliageImpl(FFoliageInfo* InInfo) #if WITH_EDITORONLY_DATA : Info(InInfo) #endif`
- L202 _public prototype_ `virtual ~FFoliageImpl() = default;`
- L204 _public function_ `virtual void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)`
- L205 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;`
- L206 _public function_ `virtual void PostSerialize(FArchive& Ar)`
- L207 _public function_ `virtual void PostLoad()`
- L211 _public member_ `FFoliageInfo* Info;` — Not serialized but FFoliageInfo will make sure it stays valid (mostly Undo/Redo)
- L215 _public prototype_ `virtual bool IsInitialized() const = 0;`
- L216 _public prototype_ `virtual void Initialize(const UFoliageType* FoliageType) = 0;`
- L217 _public prototype_ `virtual void Uninitialize() = 0;`
- L218 _public prototype_ `virtual void Reapply(const UFoliageType* FoliageType) = 0;`
- L219 _public prototype_ `virtual int32 GetInstanceCount() const = 0;`
- L220 _public prototype_ `virtual void PreAddInstances(const UFoliageType* FoliageType, int32 Count) = 0;`
- L221 _public prototype_ `virtual void AddInstance(const FFoliageInstance& NewInstance) = 0;`
- L222 _public prototype_ `virtual void RemoveInstance(int32 InstanceIndex) = 0;`
- L223 _public function_ `virtual void MoveInstance(int32 InstanceIndex, UObject*& OutInstanceImplementation)`
- L224 _public function_ `virtual void AddExistingInstance(const FFoliageInstance& ExistingInstance, UObject* InstanceImplementation)`
- L225 _public prototype_ `virtual void SetInstanceWorldTransform(int32 InstanceIndex, const FTransform& Transform, bool bTeleport) = 0;`
- L226 _public prototype_ `virtual FTransform GetInstanceWorldTransform(int32 InstanceIndex) const = 0;`
- L227 _public function_ `virtual void PostUpdateInstances()`
- L228 _public function_ `virtual void PreMoveInstances(TArrayView<const int32> InInstancesMoved)`
- L229 _public function_ `virtual void PostMoveInstances(TArrayView<const int32> InInstancesMoved, bool bFinished)`
- L230 _public prototype_ `virtual bool IsOwnedComponent(const UPrimitiveComponent* PrimitiveComponent) const = 0;`
- L232 _public prototype_ `virtual void SelectAllInstances(bool bSelect) = 0;`
- L233 _public prototype_ `virtual void SelectInstance(bool bSelect, int32 Index) = 0;`
- L234 _public prototype_ `virtual void SelectInstances(bool bSelect, const TSet<int32>& SelectedIndices) = 0;`
- L235 _public prototype_ `virtual int32 GetInstanceIndexFrom(const UPrimitiveComponent* PrimitiveComponent, int32 ComponentIndex) const = 0;`
- L236 _public prototype_ `virtual FBox GetSelectionBoundingBox(const TSet<int32>& SelectedIndices) const = 0;`
- L237 _public prototype_ `virtual void ApplySelection(bool bApply, const TSet<int32>& SelectedIndices) = 0;`
- L238 _public prototype_ `virtual void ClearSelection(const TSet<int32>& SelectedIndices) = 0;`
- L240 _public function_ `virtual void ForEachSMInstance(TFunctionRef<bool(FSMInstanceId)> Callback) const`
- L241 _public function_ `virtual void ForEachSMInstance(int32 InstanceIndex, TFunctionRef<bool(FSMInstanceId)> Callback) const`
- L243 _public function_ `virtual void BeginUpdate()`
- L244 _public function_ `virtual void EndUpdate()`
- L245 _public function_ `virtual void Refresh(bool Async, bool Force)`
- L246 _public prototype_ `virtual void OnHiddenEditorViewMaskChanged(uint64 InHiddenEditorViews) = 0;`
- L247 _public function_ `virtual void PreEditUndo(UFoliageType* FoliageType)`
- L248 _public function_ `virtual void PostEditUndo(FFoliageInfo* InInfo, UFoliageType* FoliageType)`
- L249 _public function_ `virtual void NotifyFoliageTypeWillChange(UFoliageType* FoliageType)`
- L252 _public prototype_ `virtual bool NotifyFoliageTypeChanged(UFoliageType* FoliageType, bool bSourceChanged) = 0;` — Return true if implementation needs to change
- L253 _public function_ `virtual void EnterEditMode()`
- L254 _public function_ `virtual void ExitEditMode()`
- L255 _public function_ `virtual bool ShouldAttachToBaseComponent() const`
- L257 _public prototype_ `AInstancedFoliageActor* GetIFA() const;`
- L258 _public function_ `FFoliageInfo* GetInfo() const`
- L261 _public function_ `virtual int32 GetOverlappingSphereCount(const FSphere& Sphere) const`
- L262 _public function_ `virtual int32 GetOverlappingBoxCount(const FBox& Box) const`
- L263 _public function_ `virtual void GetOverlappingBoxTransforms(const FBox& Box, TArray<FTransform>& OutTransforms) const`
- L264 _public function_ `virtual void GetOverlappingMeshCount(const FSphere& Sphere, TMap<UStaticMesh*, int32>& OutCounts) const`

#### struct `FFoliageInfo`  
`struct FFoliageInfo`  
_L270-404_
- L272 _public member_ `EFoliageImplType Type;`
- L273 _public member_ `TUniquePtr<FFoliageImpl> Implementation;`
- L277 _public member_ `AInstancedFoliageActor* IFA;` — Owning IFA
- L280 _public member_ `FGuid FoliageTypeUpdateGuid;` — Allows us to detect if FoliageType was updated while this level wasn't loaded
- L283 _public member_ `TArray<FFoliageInstance> Instances;` — Editor-only placed instances
- L286 _public member_ `TUniquePtr<FFoliageInstanceHash> InstanceHash;` — Transient, editor-only locality hash of instances
- L289 _public member_ `TMap<FFoliageInstanceBaseId, TSet<int32>> ComponentHash;` — Transient, editor-only set of instances per component
- L292 _public member_ `TSet<int32> SelectedIndices;` — Transient, editor-only list of selected instances.
- L295 _public member_ `TSet<int32> MovingInstances;` — Moving instances
- L298 _public prototype_ `FFoliageInfo();`
- L299 _public prototype_ `~FFoliageInfo();`
- L301 _public prototype_ `FFoliageInfo(FFoliageInfo&& Other) = default;`
- L302 _public prototype_ `FFoliageInfo& operator=(FFoliageInfo&& Other) = default;`
- L305 _public prototype_ `UHierarchicalInstancedStaticMeshComponent* GetComponent() const;` — Will only return a valid component in the case of non-actor foliage
- L307 _public prototype_ `void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L308 _public prototype_ `void PostSerialize(FArchive& Ar);`
- L309 _public prototype_ `void PostLoad();`
- L311 _public prototype_ `void CreateImplementation(EFoliageImplType InType);`
- L312 _public prototype_ `void Initialize(const UFoliageType* FoliageType);`
- L313 _public prototype_ `void Uninitialize();`
- L314 _public prototype_ `bool IsInitialized() const;`
- L316 _public prototype_ `int32 GetOverlappingSphereCount(const FSphere& Sphere) const;`
- L317 _public prototype_ `int32 GetOverlappingBoxCount(const FBox& Box) const;`
- L318 _public prototype_ `void GetOverlappingBoxTransforms(const FBox& Box, TArray<FTransform>& OutTransforms) const;`
- L319 _public prototype_ `void GetOverlappingMeshCount(const FSphere& Sphere, TMap<UStaticMesh*, int32>& OutCounts) const;`
- L323 _public prototype_ `EFoliageImplType GetImplementationType(const UFoliageType* FoliageType) const;`
- L324 _public prototype_ `void CreateImplementation(const UFoliageType* FoliageType);`
- L325 _public prototype_ `void NotifyFoliageTypeWillChange(UFoliageType* FoliageType);`
- L326 _public prototype_ `void NotifyFoliageTypeChanged(UFoliageType* FoliageType, bool bSourceChanged);`
- L328 _public prototype_ `void ClearSelection();`
- L330 _public prototype_ `void SetInstanceWorldTransform(int32 InstanceIndex, const FTransform& Transform, bool bTeleport);`
- L332 _public prototype_ `void SetRandomSeed(int32 seed);`
- L333 _public prototype_ `void AddInstance(const UFoliageType* InSettings, const FFoliageInstance& InNewInstance);`
- L334 _public prototype_ `void AddInstance(const UFoliageType* InSettings, const FFoliageInstance& InNewInstance, UActorComponent* InBaseComponent);`
- L335 _public prototype_ `void AddInstances(const UFoliageType* InSettings, const TArray<const FFoliageInstance*>& InNewInstances);`
- L336 _public prototype_ `void ReserveAdditionalInstances(const UFoliageType* InSettings, uint32 ReserveNum);`
- L338 _public prototype_ `void RemoveInstances(TArrayView<const int32> InInstancesToRemove, bool RebuildFoliageTree);`
- L340 _public prototype_ `void MoveInstances(AInstancedFoliageActor* InToIFA, const TSet<int32>& InInstancesToMove, bool bKeepSelection);`
- L343 _public prototype_ `void PreMoveInstances(TArrayView<const int32> InInstancesMoved);` — Apply changes in the FoliageType to the component
- L344 _public prototype_ `void PostMoveInstances(TArrayView<const int32> InInstancesMoved, bool bFinished = false);`
- L345 _public prototype_ `void PostUpdateInstances(TArrayView<const int32>, bool bReAddToHash = false, bool InUpdateSelection = false);`
- L346 _public prototype_ `void DuplicateInstances(UFoliageType* InSettings, TArrayView<const int32> InInstancesToDuplicate);`
- L347 _public prototype_ `void GetInstancesInsideBounds(const FBox& Box, TArray<int32>& OutInstances) const;`
- L348 _public prototype_ `void GetInstancesInsideSphere(const FSphere& Sphere, TArray<int32>& OutInstances) const;`
- L349 _public prototype_ `void GetInstanceAtLocation(const FVector& Location, int32& OutInstance, bool& bOutSucess) const;`
- L350 _public prototype_ `bool CheckForOverlappingSphere(const FSphere& Sphere) const;`
- L351 _public prototype_ `bool CheckForOverlappingInstanceExcluding(int32 TestInstanceIdx, float Radius, TSet<int32>& ExcludeInstances) const;`
- L352 _public prototype_ `TArray<int32> GetInstancesOverlappingBox(const FBox& Box) const;`
- L355 _public prototype_ `void ReallocateClusters(UFoliageType* InSettings);` — Destroy existing clusters and reassign all instances to new clusters
- L357 _public prototype_ `void SelectInstances(bool bSelect, TArrayView<const int32> Instances);`
- L359 _public prototype_ `void SelectInstances(bool bSelect);`
- L361 _public prototype_ `FBox GetSelectionBoundingBox() const;`
- L364 _public prototype_ `int32 GetPlacedInstanceCount() const;` — Get the number of placed instances
- L366 _public prototype_ `void AddToBaseHash(int32 InstanceIdx);`
- L367 _public prototype_ `void RemoveFromBaseHash(int32 InstanceIdx);`
- L368 _public prototype_ `void RecomputeHash();`
- L369 _public function_ `bool ShouldAttachToBaseComponent() const`
- L372 _public prototype_ `void CheckValid();` — For debugging. Validate state after editing.
- L374 _public prototype_ `void ForEachSMInstance(TFunctionRef<bool(FSMInstanceId)> Callback) const;`
- L375 _public prototype_ `void ForEachSMInstance(int32 InstanceIndex, TFunctionRef<bool(FSMInstanceId)> Callback) const;`
- L377 _public prototype_ `void Refresh(bool Async, bool Force);`
- L378 _public prototype_ `void OnHiddenEditorViewMaskChanged(uint64 InHiddenEditorViews);`
- L379 _public prototype_ `void PostEditUndo(UFoliageType* FoliageType);`
- L380 _public prototype_ `void PreEditUndo(UFoliageType* FoliageType);`
- L381 _public prototype_ `void EnterEditMode();`
- L382 _public prototype_ `void ExitEditMode();`
- L384 _public prototype_ `void RemoveBaseComponentOnInstances();`
- L385 _public prototype_ `void IncludeActor(const UFoliageType* FoliageType, AActor* InActor);`
- L386 _public prototype_ `void ExcludeActors();`
- L388 _public prototype_ `FBox GetApproximatedInstanceBounds() const;`
- L394 _public prototype_ `FFoliageInfo(const FFoliageInfo&) = delete;` — Non-copyable
- L395 _public prototype_ `FFoliageInfo& operator=(const FFoliageInfo&) = delete;`
- L398 _private typedef_ `using FAddImplementationFunc = TFunctionRef<void(FFoliageImpl*, AInstancedFoliageActor*, const FFoliageInstance&)>;`
- L399 _private prototype_ `void AddInstancesImpl(const UFoliageType* InSettings, const TArray<const FFoliageInstance*>& InNewInstances, FFoliageInfo::FAddImplementationFunc ImplementationFunc);`
- L400 _private prototype_ `void AddInstanceImpl(const FFoliageInstance& InNewInstance, FAddImplementationFunc ImplementationFunc);`
- L402 _private typedef_ `using FRemoveImplementationFunc = TFunctionRef<void(FFoliageImpl*, int32)>;`
- L403 _private prototype_ `void RemoveInstancesImpl(TArrayView<const int32> InInstancesToRemove, bool RebuildFoliageTree, FRemoveImplementationFunc ImplementationFunc);`

#### struct `FFoliageInstanceId`  
`struct FFoliageInstanceId`  
_L406-448_
- L408 _public function_ `explicit operator bool() const`
- L414 _public function_ `bool operator==(const FFoliageInstanceId& InRHS) const`
- L420 _public function_ `bool operator!=(const FFoliageInstanceId& InRHS) const`
- L426 _public function_ `FFoliageInstance* GetInstance() const`
- L433 _public function_ `FFoliageInstance& GetInstanceChecked() const`
- L446 _public member_ `FFoliageInfo* Info = nullptr;`
- L447 _public member_ `int32 Index = INDEX_NONE;`

#### enum `EFoliagePlacementMode::Type`  
`enum Type`  
_L453-457_
- L455 _public enumerator_ `Manual = 0`
- L456 _public enumerator_ `Procedural = 1`

#### struct `FDesiredFoliageInstance`  
`struct FDesiredFoliageInstance`  
_L462-496_
- desc: Used to define a vector along which we'd like to spawn an instance.
- L464 _public function_ `FDesiredFoliageInstance() : FoliageType(nullptr) , StartTrace(ForceInit) , EndTrace(ForceInit) , Rotation(ForceInit) , TraceRadius(0.f) , Age(0.f) , PlacementMode(EFoliagePlacementMode::Manual)`
- L476 _public function_ `FDesiredFoliageInstance(const FVector& InStartTrace, const FVector& InEndTrace, const UFoliageType* InFoliageType, const float InTraceRadius = 0.f) : FoliageType(InFoliageType) , StartTrace(InStartTrace) , EndTrace(InEndTrace) , Rotation(ForceInit) , TraceRadius(InTraceRadius) , Age(0.f) , PlacementMode(EFoliagePlacementMode::Manual)`
- L487 _public member_ `const UFoliageType* FoliageType;`
- L488 _public member_ `FGuid ProceduralGuid;`
- L489 _public member_ `FVector StartTrace;`
- L490 _public member_ `FVector EndTrace;`
- L491 _public member_ `FQuat Rotation;`
- L492 _public member_ `float TraceRadius;`
- L493 _public member_ `float Age;`
- L494 _public member_ `const struct FBodyInstance* ProceduralVolumeBodyInstance;`
- L495 _public member_ `EFoliagePlacementMode::Type PlacementMode;`

#### struct `FPotentialInstance`  
`struct FPotentialInstance`  
_L500-510_
- desc: Struct to hold potential instances we've sampled
- L502 _public member_ `FVector HitLocation;`
- L503 _public member_ `FVector HitNormal;`
- L504 _public member_ `UPrimitiveComponent* HitComponent;`
- L505 _public member_ `float HitWeight;`
- L506 _public member_ `FDesiredFoliageInstance DesiredInstance;`
- L508 _public prototype_ `FPotentialInstance(FVector InHitLocation, FVector InHitNormal, UPrimitiveComponent* InHitComponent, float InHitWeight, const FDesiredFoliageInstance& InDesiredInstance = FDesiredFoliageInstance());`
- L509 _public prototype_ `bool PlaceInstance(const UWorld* InWorld, const UFoliageType* Settings, FFoliageInstance& Inst, bool bSkipCollision = false);`

#### Free symbols / members of external scopes

- L25 _typedef_ `using FFoliageInstanceHash = FInstancedPlacementHash;`
- L28 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInstancedFoliage, Log, All);`
- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInstancedFoliage, Log, All);`
- L30 _namespace_ `namespace FoliageElementUtil`
- L32 _prototype_ `bool FoliageInstanceElementsEnabled();` (scope `FoliageElementUtil`)
- L441 _function_ `friend inline uint32 GetTypeHash(const FFoliageInstanceId& InId)`
- L451 _namespace_ `namespace EFoliagePlacementMode`

### `Source/Runtime/Foliage/Public/InstancedFoliageActor.h` (Public)


#### class `AInstancedFoliageActor`  
`class AInstancedFoliageActor : public AISMPartitionActor`  
_L28-321_
- reflection: `UCLASS(notplaceable, hidecategories = (Object, Rendering, Mobility), MinimalAPI, NotBlueprintable)`
- inherits: `AISMPartitionActor`
- L35 _public member_ `FFoliageInstanceBaseCache InstanceBaseCache;` — Cross level references cache for instances base
- L37 _public prototype_ `UActorComponent* GetBaseComponentFromBaseId(const FFoliageInstanceBaseId& BaseId) const;`
- L43 _private member_ `TMap<TObjectPtr<UFoliageType>, TUniqueObj<FFoliageInfo>> FoliageInfos;`
- L46 _public prototype_ `bool ForEachFoliageInfo(TFunctionRef<bool(UFoliageType* FoliageType, FFoliageInfo& FoliageInfo)> InOperation);`
- L47 _public function_ `const TMap<UFoliageType*, TUniqueObj<FFoliageInfo>>& GetFoliageInfos() const`
- L48 _public prototype_ `TUniqueObj<FFoliageInfo>& AddFoliageInfo(UFoliageType* FoliageType);`
- L49 _public prototype_ `TUniqueObj<FFoliageInfo>& AddFoliageInfo(UFoliageType* FoliageType, TUniqueObj<FFoliageInfo>&& FoliageInfo);`
- L50 _public prototype_ `bool RemoveFoliageInfoAndCopyValue(UFoliageType* FoliageType, TUniqueObj<FFoliageInfo>& OutFoliageInfo);`
- L53 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L54 _public prototype_ `virtual void PostLoad() override;`
- L56 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L59 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L65 _public function_ `virtual void RerunConstructionScripts() override`
- L67 _public function_ `virtual bool IsLevelBoundsRelevant() const override`
- L71 _public function_ `bool CanDeleteSelectedActor(FText& OutReason) const override`
- L72 _public prototype_ `bool CanEditFoliageInstance(const FFoliageInstanceId& InstanceId) const;`
- L73 _public prototype_ `bool CanMoveFoliageInstance(const FFoliageInstanceId& InstanceId, const ETypedElementWorldType WorldType) const;`
- L74 _public prototype_ `bool GetFoliageInstanceTransform(const FFoliageInstanceId& InstanceId, FTransform& OutInstanceTransform, bool bWorldSpace) const;`
- L75 _public prototype_ `bool SetFoliageInstanceTransform(const FFoliageInstanceId& InstanceId, const FTransform& InstanceTransform, bool bWorldSpace, bool bTeleport);`
- L76 _public prototype_ `void NotifyFoliageInstanceMovementStarted(const FFoliageInstanceId& InstanceId);`
- L77 _public prototype_ `void NotifyFoliageInstanceMovementOngoing(const FFoliageInstanceId& InstanceId);`
- L78 _public prototype_ `void NotifyFoliageInstanceMovementEnded(const FFoliageInstanceId& InstanceId);`
- L79 _public prototype_ `void NotifyFoliageInstanceSelectionChanged(const FFoliageInstanceId& InstanceId, const bool bIsSelected);`
- L80 _public prototype_ `bool DeleteFoliageInstances(TArrayView<const FFoliageInstanceId> InstanceIds);`
- L81 _public prototype_ `bool DuplicateFoliageInstances(TArrayView<const FFoliageInstanceId> InstanceIds, TArray<FFoliageInstanceId>& OutNewInstanceIds);`
- L83 _public prototype_ `UFoliageType* GetFoliageTypeForInfo(const FFoliageInfo* FoliageInfo) const;`
- L88 _protected prototype_ `void HandleFoliageInstancePreMove(const FFoliageInstanceId& InstanceId);`
- L89 _protected prototype_ `void HandleFoliageInstancePostMove(const FFoliageInstanceId& InstanceId);`
- L93 _protected prototype_ `virtual ISMInstanceManager* GetSMInstanceManager(const FSMInstanceId& InstanceId) override;`
- L96 _protected prototype_ `virtual float InternalTakeRadialDamage(float Damage, struct FRadialDamageEvent const& RadialDamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;` — Default InternalTakeRadialDamage behavior finds and scales damage for the closest component which isn't appropriate for foliage.
- L100 _public prototype_ `void EnterEditMode();`
- L101 _public prototype_ `void ExitEditMode();`
- L103 _public prototype_ `virtual void PostInitProperties() override;`
- L104 _public prototype_ `virtual void BeginDestroy() override;`
- L105 _public prototype_ `virtual void Destroyed() override;`
- L106 _public prototype_ `virtual bool IsListedInSceneOutliner() const override;`
- L108 _public prototype_ `void CleanupDeletedFoliageType();`
- L109 _public prototype_ `void DetectFoliageTypeChangeAndUpdate();`
- L111 _public prototype_ `virtual uint32 GetDefaultGridSize(UWorld* InWorld) const override;`
- L112 _public prototype_ `virtual bool ShouldIncludeGridSizeInName(UWorld* InWorld, const FActorPartitionIdentifier& InIdentifier) const override;`
- L115 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChanged, bool, const TArray<AActor*>&);` — Delegate type for selection change events
- L116 _public member_ `static FOnSelectionChanged SelectionChanged;`
- L118 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInstanceCoundChanged, const UFoliageType*);`
- L119 _public member_ `static FOnInstanceCoundChanged InstanceCountChanged;`
- L125 _public prototype_ `UFoliageType* GetLocalFoliageTypeForSource(const UObject* InSource, FFoliageInfo** OutMeshInfo = nullptr);` — Performs a reverse lookup from a source object to a local foliage type (i.e. the foliage type owned exclusively by this IFA)
- L128 _public prototype_ `void GetAllFoliageTypesForSource(const UObject* InSource, TArray<const UFoliageType*>& OutFoliageTypes);` — Performs a reverse lookup from a source object to all the foliage types that are currently using that object (includes assets and blueprint classes)
- L130 _public prototype_ `FFoliageInfo* FindFoliageTypeOfClass(TSubclassOf<UFoliageType_InstancedStaticMesh> Class);`
- L133 _public prototype_ `int32 GetOverlappingSphereCount(const UFoliageType* FoliageType, const FSphere& Sphere) const;` — Finds the number of instances overlapping with the sphere.
- L135 _public prototype_ `int32 GetOverlappingBoxCount(const UFoliageType* FoliageType, const FBox& Box) const;` — Finds the number of instances overlapping with the box.
- L137 _public prototype_ `void GetOverlappingBoxTransforms(const UFoliageType* FoliageType, const FBox& Box, TArray<FTransform>& OutTransforms) const;` — Finds all instances in the provided box and get their transforms
- L140 _public prototype_ `void GetOverlappingMeshCounts(const FSphere& Sphere, TMap<UStaticMesh*, int32>& OutCounts) const;` — Perf Warnin: potentially slow! Dev-only use recommended. Returns list of meshes and counts for all nearby instances. OutCounts accumulates between runs.
- L143 _public prototype_ `FFoliageInfo* FindInfo(const UFoliageType* InType);` — Finds a mesh entry
- L146 _public prototype_ `const FFoliageInfo* FindInfo(const UFoliageType* InType) const;` — Finds a mesh entry
- L155 _public prototype_ `static AInstancedFoliageActor* GetInstancedFoliageActorForCurrentLevel(const UWorld* InWorld, bool bCreateIfNone = false);` — Get the instanced foliage actor for the current streaming level. @param InWorld						World to create the foliage instance in @param bCreateIfNone					Create if doesnt already exist returns								pointer to foliage object instance
- L164 _public prototype_ `static AInstancedFoliageActor* GetInstancedFoliageActorForLevel(ULevel* Level, bool bCreateIfNone = false);` — Get the instanced foliage actor for the specified streaming level. @param InLevel						Level to create the foliage instance in @param bCreateIfNone					Create if doesnt already exist returns								pointer to foliage object instance
- L174 _public prototype_ `static AInstancedFoliageActor* Get(UWorld* InWorld, bool bCreateIfNone, ULevel* InLevelHint = nullptr, const FVector& InLocationHint = FVector(ForceInitToZero));` — Get the instanced foliage actor for the specified params @param InWorld						World to create the foliage instance in @param bCreateIfNone					Create if doesnt already exist @param InLevelHint					Level hint for foliage instance creation @param InLocationHint				Location hint for foliage instance creation
- L176 _public prototype_ `static AInstancedFoliageActor* GetDefault(UWorld* InWorld);`
- L178 _public prototype_ `static void UpdateInstancePartitioning(UWorld* InWorld);`
- L179 _public prototype_ `static void MoveSelectedInstancesToActorEditorContext(UWorld* InWorld);`
- L181 _public prototype_ `static bool FoliageTrace(const UWorld* InWorld, FHitResult& OutHit, const FDesiredFoliageInstance& DesiredInstance, FName InTraceTag = NAME_None, bool InbReturnFaceIndex = false, const FFoliageTraceFilterFunc& FilterFunc = FFoliageTraceFilterFunc(), bool bAverageNormal = false);`
- L182 _public prototype_ `static bool CheckCollisionWithWorld(const UWorld* InWorld, const UFoliageType* Settings, const FFoliageInstance& Inst, const FVector& HitNormal, const FVector& HitLocation, UPrimitiveComponent* HitComponent);`
- L184 _public prototype_ `virtual void PreEditUndo() override;`
- L185 _public prototype_ `virtual void PostEditUndo() override;`
- L186 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L187 _public prototype_ `virtual bool ShouldExport() override;`
- L188 _public prototype_ `virtual bool ShouldImport(FStringView ActorPropString, bool IsMovingLevel) override;`
- L191 _public prototype_ `void MapRebuild();` — Called in response to BSP rebuilds to migrate foliage from obsolete to new components.
- L194 _public prototype_ `static void MoveInstancesForComponentToCurrentLevel(UActorComponent* InComponent);` — Moves instances based on the specified component to the current streaming level
- L195 _public prototype_ `static void MoveInstancesForComponentToLevel(UActorComponent* InComponent, ULevel* TargetLevel);`
- L199 _public prototype_ `void MoveInstancesToNewComponent(UPrimitiveComponent* InOldComponent, UPrimitiveComponent* InNewComponent);` — Change all instances based on one component to a new component (possible in another level). The instances keep the same world locations
- L200 _public prototype_ `void MoveInstancesToNewComponent(UPrimitiveComponent* InOldComponent, const FBox& InBoxWithInstancesToMove, UPrimitiveComponent* InNewComponent);`
- L201 _public prototype_ `static void MoveInstancesToNewComponent(UWorld* InWorld, UPrimitiveComponent* InOldComponent, const FBox& InBoxWithInstancesToMove, UPrimitiveComponent* InNewComponent);`
- L202 _public prototype_ `static void MoveInstancesToNewComponent(UWorld* InWorld, UPrimitiveComponent* InOldComponent, UPrimitiveComponent* InNewComponent);`
- L205 _public prototype_ `void MoveSelectedInstancesToLevel(ULevel* InTargetLevel);` — Move selected instances to a foliage actor in target level
- L208 _public prototype_ `void MoveAllInstancesToLevel(ULevel* InTargetLevel);` — Move all instances to a foliage actor in target level
- L211 _public prototype_ `void MoveInstancesToLevel(ULevel* InTargetLevel, TSet<int32>& InInstanceList, FFoliageInfo* InCurrentMeshInfo, UFoliageType* InFoliageType, bool bSelect = false);` — Move instances to a foliage actor in target level
- L214 _public prototype_ `TMap<UFoliageType*, TArray<const FFoliageInstancePlacementInfo*>> GetInstancesForComponent(UActorComponent* InComponent);` — Returns a map of Static Meshes and their placed instances attached to a component.
- L217 _public prototype_ `void DeleteInstancesForComponent(UActorComponent* InComponent);` — Deletes the instances attached to a component
- L218 _public prototype_ `void DeleteInstancesForComponent(UActorComponent* InComponent, const UFoliageType* InFoliageType);`
- L221 _public prototype_ `static void DeleteInstancesForComponent(UWorld* InWorld, UActorComponent* InComponent);` — Deletes the instances attached to a component, traverses all foliage actors in the world
- L224 _public prototype_ `bool DeleteInstancesForProceduralFoliageComponent(const UProceduralFoliageComponent* InProceduralFoliageComponent, bool bInRebuildTree);` — Deletes the instances spawned by a procedural component
- L225 _public prototype_ `bool DeleteInstancesForProceduralFoliageComponent(const FGuid& InProceduralGuid, bool bInRebuildTree);`
- L226 _public prototype_ `bool DeleteInstancesForAllProceduralFoliageComponents(bool bInRebuildTree);`
- L229 _public prototype_ `bool ContainsInstancesFromProceduralFoliageComponent(const UProceduralFoliageComponent* InProceduralFoliageComponent);` — @return True if any instances exist that were spawned by the given procedural component
- L230 _public prototype_ `bool ContainsInstancesFromProceduralFoliageComponent(const FGuid& InProceduralGuid);`
- L233 _public prototype_ `FFoliageInfo* FindOrAddMesh(UFoliageType* InType);` — Finds a mesh entry or adds it if it doesn't already exist
- L235 _public prototype_ `UFoliageType* AddFoliageType(const UFoliageType* InType, FFoliageInfo** OutInfo = nullptr);`
- L237 _public prototype_ `FFoliageInfo* AddMesh(UStaticMesh* InMesh, UFoliageType** OutSettings = nullptr, const UFoliageType_InstancedStaticMesh* DefaultSettings = nullptr);` — Add a new static mesh.
- L238 _public prototype_ `FFoliageInfo* AddMesh(UFoliageType* InType);`
- L241 _public prototype_ `void RemoveFoliageType(UFoliageType** InFoliageType, int32 Num);` — Remove the FoliageType from the list, and all its instances.
- L244 _public prototype_ `void SelectInstance(UInstancedStaticMeshComponent* InComponent, int32 InComponentInstanceIndex, bool bToggle);` — Select an individual instance.
- L247 _public prototype_ `bool SelectInstance(AActor* InActor, bool bToggle);` — Select an individual instance.
- L250 _public prototype_ `FBox GetSelectionBoundingBox() const;` — Get the bounds of all selected instances
- L253 _public prototype_ `bool HasSelectedInstances() const;` — Whether actor has selected instances
- L256 _public prototype_ `TMap<UFoliageType*, FFoliageInfo*> GetSelectedInstancesFoliageType();` — Will return all the foliage type used by currently selected instances
- L259 _public prototype_ `const UFoliageType* FindFoliageType(const FFoliageInfo* InFoliageInfo) const;` — Returns FoliageType associated to this FoliageInfo
- L262 _public prototype_ `TMap<UFoliageType*, FFoliageInfo*> GetAllInstancesFoliageType();` — Will return all the foliage type used
- L265 _public prototype_ `void ApplySelection(bool bApply);` — Propagate the selected instances to the actual foliage implementation
- L268 _public prototype_ `bool GetSelectionLocation(FBox& OutLocation) const;` — Returns the location for the widget
- L271 _public prototype_ `static bool HasFoliageAttached(UActorComponent* InComponent);` — Whether there any foliage instances painted on specified component
- L274 _public prototype_ `void NotifyFoliageTypeChanged(UFoliageType* FoliageType, bool bSourceChanged);` — Called to notify InstancedFoliageActor that a UFoliageType has been modified
- L275 _public prototype_ `void NotifyFoliageTypeWillChange(UFoliageType* FoliageType);`
- L277 _public prototype_ `DECLARE_EVENT_OneParam(AInstancedFoliageActor, FOnFoliageTypeMeshChanged, UFoliageType*);`
- L278 _public function_ `FOnFoliageTypeMeshChanged& OnFoliageTypeMeshChanged()`
- L281 _public prototype_ `void RepairDuplicateIFA(AInstancedFoliageActor* InDuplicateIFA);` — Fix up a duplicate IFA
- L283 _public prototype_ `void RemoveBaseComponentOnFoliageTypeInstances(UFoliageType* FoliageType);`
- L286 _public prototype_ `static void AddInstances(UObject* WorldContextObject, UFoliageType* InFoliageType, const TArray<FTransform>& InTransforms);` — `UFUNCTION(BlueprintCallable, Category="Foliage", meta = (WorldContext = "WorldContextObject"))`
- L289 _public prototype_ `static void RemoveAllInstances(UObject* WorldContextObject, UFoliageType* InFoliageType);` — `UFUNCTION(BlueprintCallable, Category="Foliage", meta = (WorldContext = "WorldContextObject"))`
- L295 _private member_ `TMap<UFoliageType*, TUniqueObj<struct FFoliageMeshInfo_Deprecated>> FoliageMeshes_Deprecated;` — Deprecated data, will be converted and cleaned up in PostLoad
- L296 _private member_ `TMap<UFoliageType*, TUniqueObj<struct FFoliageMeshInfo_Deprecated2>> FoliageMeshes_Deprecated2;`
- L300 _private prototype_ `void ClearSelection();`
- L301 _private prototype_ `void MoveInstancesToNewComponent(UPrimitiveComponent* InOldComponent, UPrimitiveComponent* InNewComponent, TFunctionRef<TArray<int32>(const FFoliageInfo&)> GetInstancesToMoveFunc);`
- L302 _private prototype_ `bool DeleteInstancesForProceduralFoliageComponentInternal(const FGuid& InProceduralGuid, bool bInRebuildTree, bool bInDeleteAll);`
- L305 _private prototype_ `bool MoveInstancesForMovedComponent(UActorComponent* InComponent);`
- L306 _private prototype_ `void UpdateInstancePartitioningForMovedComponent(UActorComponent* InComponent);`
- L308 _private prototype_ `void MoveInstancesForMovedOwnedActors(AActor* InActor);`
- L310 _private prototype_ `void UpdateFoliageActorInstance(AActor* InActor);`
- L311 _private prototype_ `void DeleteFoliageActorInstance(AActor* InActor);`
- L313 _private prototype_ `void PostApplyLevelOffset(const FVector& InOffset, bool bWorldShift);`
- L314 _private prototype_ `void PostApplyLevelTransform(const FTransform& InTransform);`
- L318 _private member_ `FOnFoliageTypeMeshChanged OnFoliageTypeMeshChangedEvent;`

#### Free symbols / members of external scopes

- L25 _typedef_ `typedef TFunction<bool(const UPrimitiveComponent*)> FFoliageTraceFilterFunc;` — Function for filtering out hit components during FoliageTrace
- L115 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChanged, bool, const TArray<AActor*>&);` — Delegate type for selection change events
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInstanceCoundChanged, const UFoliageType*);`
- L277 _delegate_ `DECLARE_EVENT_OneParam(AInstancedFoliageActor, FOnFoliageTypeMeshChanged, UFoliageType*);`

### `Source/Runtime/Foliage/Public/InstancedFoliageCustomVersion.h` (Public)


#### struct `FFoliageCustomVersion`  
`struct FFoliageCustomVersion`  
_L10-56_
- desc: Custom serialization version for all packages containing Instance Foliage
- L52 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L55 _private function_ `FFoliageCustomVersion()`

#### enum `FFoliageCustomVersion::Type`  
`enum Type`  
_L12-49_
- L15 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L17 _public enumerator_ `FoliageUsingHierarchicalISMC = 1` — Converted to use HierarchicalInstancedStaticMeshComponent
- L19 _public enumerator_ `HierarchicalISMCNonTransactional = 2` — Changed Component to not RF_Transactional
- L21 _public enumerator_ `AddedFoliageTypeUpdateGuid = 3` — Added FoliageTypeUpdateGuid
- L23 _public enumerator_ `ProceduralGuid = 4` — Use a GUID to determine whic procedural actor spawned us
- L25 _public enumerator_ `CrossLevelBase = 5` — Support for cross-level bases
- L27 _public enumerator_ `FoliageTypeCustomization = 6` — FoliageType for details customization
- L29 _public enumerator_ `FoliageTypeCustomizationScaling = 7` — FoliageType for details customization continued
- L31 _public enumerator_ `FoliageTypeProceduralScaleAndShade = 8` — FoliageType procedural scale and shade settings updated
- L33 _public enumerator_ `FoliageHISMCBlueprints = 9` — Added FoliageHISMC and blueprint support
- L35 _public enumerator_ `AddedMobility = 10` — Added Mobility setting to UFoliageType
- L37 _public enumerator_ `FoliageUsingFoliageISMC = 11` — Make sure that foliage has FoliageHISMC class
- L39 _public enumerator_ `FoliageActorSupport = 12` — Foliage Actor Support
- L41 _public enumerator_ `FoliageActorSupportNoWeakPtr = 13` — Foliage Actor (No weak ptr)
- L43 _public enumerator_ `FoliageRepairInstancesWithLevelTransform = 14` — Foliage Instances are now always saved local to Level
- L45 _public enumerator_ `FoliageDiscardOnLoad = 15` — Supports discarding foliage types on load independently from density scaling
- L47 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L48 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Source/Runtime/Foliage/Public/InteractiveFoliageActor.h` (Public)


#### class `AInteractiveFoliageActor`  
`class AInteractiveFoliageActor : public AStaticMeshActor`  
_L16-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AStaticMeshActor`
- L23 _private member_ `TObjectPtr<class UCapsuleComponent> CapsuleComponent;` — `UPROPERTY()` — Collision cylinder
- L30 _private member_ `FVector TouchingActorEntryPosition;` — `UPROPERTY(transient)` — Position of the last actor to enter the collision cylinder. This currently does not handle multiple actors affecting the foliage simultaneously.
- L34 _private member_ `FVector FoliageVelocity;` — `UPROPERTY(transient)` — Simulated physics state
- L38 _private member_ `FVector FoliageForce;` — `UPROPERTY(transient)` — @todo document
- L42 _private member_ `FVector FoliagePosition;` — `UPROPERTY(transient)` — @todo document
- L47 _public member_ `float FoliageDamageImpulseScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Scales forces applied from damage events.
- L51 _public member_ `float FoliageTouchImpulseScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Scales forces applied from touch events.
- L55 _public member_ `float FoliageStiffness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Determines how strong the force that pushes toward the spring's center will be.
- L62 _public member_ `float FoliageStiffnessQuadratic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Same as FoliageStiffness, but the strength of this force increases with the square of the distance to the spring's center. This force is used to prevent the spring from extending past a certain point due to touch and damage forces.
- L69 _public member_ `float FoliageDamping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Determines the amount of energy lost by the spring as it oscillates. This force is similar to air friction.
- L73 _public member_ `float MaxDamageImpulse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Clamps the magnitude of each damage force applied.
- L77 _public member_ `float MaxTouchImpulse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Clamps the magnitude of each touch force applied.
- L81 _public member_ `float MaxForce;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FoliagePhysics)` — Clamps the magnitude of combined forces applied each update.
- L85 _public member_ `float Mass;` — `UPROPERTY()` — @todo - hook this up	  @todo document
- L89 _protected prototype_ `void SetupCollisionCylinder();` — @todo document
- L93 _protected prototype_ `void CapsuleTouched(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& OverlapInfo);` — `UFUNCTION()` — Called when capsule is touched
- L96 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L97 _public prototype_ `virtual void PostActorCreated() override;`
- L98 _public prototype_ `virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;`
- L102 _public prototype_ `virtual void PostLoad() override;`

### `Source/Runtime/Foliage/Public/ProceduralFoliageBlockingVolume.h` (Public)


#### class `AProceduralFoliageBlockingVolume`  
`class AProceduralFoliageBlockingVolume : public AVolume`  
_L16-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AVolume`
- desc: An invisible volume used to block ProceduralFoliage instances from being spawned.
- L21 _private member_ `TObjectPtr<AProceduralFoliageVolume> ProceduralFoliageVolume;` — `UPROPERTY(Category = ProceduralFoliage, EditAnywhere)`
- L24 _private member_ `FFoliageDensityFalloff DensityFalloff;` — `UPROPERTY(Category = ProceduralFoliage, EditAnywhere)`

### `Source/Runtime/Foliage/Public/ProceduralFoliageBroadphase.h` (Public)


#### class `FProceduralFoliageBroadphase`  
`class FProceduralFoliageBroadphase`  
_L9-25_
- L12 _public prototype_ `FProceduralFoliageBroadphase(float TileSize = 0.f, float MinimumQuadTreeSize = 100.f);`
- L13 _public prototype_ `FProceduralFoliageBroadphase(const FProceduralFoliageBroadphase& OtherBroadphase);`
- L14 _public prototype_ `FProceduralFoliageBroadphase& operator=(const FProceduralFoliageBroadphase& OtherBroadphase);`
- L16 _public prototype_ `bool TestAgainstAABB(FProceduralFoliageInstance* Instance);`
- L17 _public prototype_ `void Insert(FProceduralFoliageInstance* Instance);`
- L18 _public prototype_ `bool GetOverlaps(FProceduralFoliageInstance* Instance, TArray<FProceduralFoliageOverlap>& Overlaps) const;`
- L19 _public prototype_ `void GetInstancesInBox(const FBox2D& Box, TArray<FProceduralFoliageInstance*>& Instances) const;`
- L20 _public prototype_ `void Remove(FProceduralFoliageInstance* Instance);`
- L21 _public prototype_ `void Empty();`
- L24 _private member_ `TQuadTree<FProceduralFoliageInstance*, 4> QuadTree;`

### `Source/Runtime/Foliage/Public/ProceduralFoliageComponent.h` (Public)


#### struct `FTileLayout`  
`struct FTileLayout`  
_L18-39_
- desc: Describes the layout of the tiles used for procedural foliage simulation
- L20 _public function_ `FTileLayout() : BottomLeftX(0), BottomLeftY(0), NumTilesX(0), NumTilesY(0), HalfHeight(0.f)`
- L26 _public member_ `int32 BottomLeftX;` — The X coordinate (in whole tiles) of the bottom-left-most active tile
- L29 _public member_ `int32 BottomLeftY;` — The Y coordinate (in whole tiles) of the bottom-left-most active tile
- L32 _public member_ `int32 NumTilesX;` — The total number of active tiles along the x-axis
- L35 _public member_ `int32 NumTilesY;` — The total number of active tiles along the y-axis
- L38 _public member_ `FVector::FReal HalfHeight;`

#### class `UProceduralFoliageComponent`  
`class UProceduralFoliageComponent : public UActorComponent`  
_L42-160_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UActorComponent`
- L48 _private member_ `TObjectPtr<UProceduralFoliageSpawner> FoliageSpawner;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — The procedural foliage spawner used to generate foliage instances within this volume.
- L52 _private member_ `float TileOverlap;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — The amount of overlap between simulation tiles (in cm).
- L58 _private member_ `bool bAllowLandscape;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — Whether to place foliage on landscape
- L62 _private member_ `bool bAllowBSP;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — Whether to place foliage on BSP
- L66 _private member_ `bool bAllowStaticMesh;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — Whether to place foliage on StaticMesh
- L70 _private member_ `bool bAllowTranslucent;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — Whether to place foliage on translucent geometry
- L74 _private member_ `bool bAllowFoliage;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — Whether to place foliage on other blocking foliage geometry
- L78 _private member_ `bool bShowDebugTiles;` — `UPROPERTY(Category = "ProceduralFoliage", BlueprintReadWrite, EditAnywhere)` — Whether to visualize the tiles used for the foliage spawner simulation
- L100 _private prototype_ `virtual void PostEditImport() override;` — UObject interface
- L105 _private prototype_ `FGenerateProceduralContentParams GetGenerateProceduralContentParams() const;` — Returns a params struct based on this component properties.
- L111 _private prototype_ `bool ResimulateProceduralFoliage(TFunctionRef<void(const TArray<FDesiredFoliageInstance>&)> AddInstancesFunc);` — Runs the procedural foliage simulation, removes the old result, creates instances with the new result @return True if the simulation succeeded
- L117 _private prototype_ `bool GenerateProceduralContent(TArray<FDesiredFoliageInstance>& OutInstances);` — Runs the procedural foliage simulation to generate a list of desired instances to spawn. @return True if the simulation succeeded
- L118 _private prototype_ `static bool GenerateProceduralContent(const FGenerateProceduralContentParams& InParams, TArray<FDesiredFoliageInstance>& OutInstances);`
- L121 _private prototype_ `void RemoveProceduralContent(bool bInRebuildTree = true);` — Removes all spawned foliage instances in the level that were spawned by this component
- L122 _private prototype_ `static void RemoveProceduralContent(UWorld* InWorld, const FGuid& InProceduralGuid, bool bInRebuildTree, TSet<AInstancedFoliageActor*>& OutModifiedActors);`
- L125 _private prototype_ `bool HasSpawnedAnyInstances();` — @return True if any foliage instances in the level were spawned by this component
- L128 _private prototype_ `FVector GetWorldPosition() const;` — @return The position in world space of the bottom-left corner of the bottom-left-most active tile
- L129 _private prototype_ `static FVector GetWorldPosition(const FGenerateProceduralContentParams& Param);`
- L132 _private prototype_ `virtual FBox GetBounds() const;` — @return The bounds of area encompassed by the simulation
- L135 _private prototype_ `FBodyInstance* GetBoundsBodyInstance() const;` — @return The body instanced used for bounds checking
- L138 _private prototype_ `void GetTileLayout(FTileLayout& OutTileLayout) const;` — Determines the basic layout of the tiles used in the simulation
- L139 _private prototype_ `static void GetTileLayout(const FGenerateProceduralContentParams& Params, FTileLayout& OutTileLayout);`
- L141 _private function_ `void SetSpawningVolume(AVolume* InSpawningVolume)`
- L142 _private function_ `const FGuid& GetProceduralGuid() const`
- L145 _private prototype_ `void LoadSimulatedRegion();`
- L146 _private prototype_ `void UnloadSimulatedRegion();`
- L147 _private prototype_ `bool IsSimulatedRegionLoaded();`
- L152 _private member_ `TObjectPtr<AVolume> SpawningVolume;` — `UPROPERTY()`
- L155 _private member_ `FGuid ProceduralGuid;` — `UPROPERTY()`

#### struct `UProceduralFoliageComponent::FGenerateProceduralContentParams`  
`struct FGenerateProceduralContentParams`  
_L82-97_
- L84 _public function_ `FGenerateProceduralContentParams() : FoliageSpawner(nullptr) , Bounds(EForceInit::ForceInit) , TileOverlap(0.f) , ProceduralVolumeInstance(nullptr)`
- L92 _public member_ `TObjectPtr<UProceduralFoliageSpawner> FoliageSpawner;`
- L93 _public member_ `FBox Bounds;`
- L94 _public member_ `float TileOverlap;`
- L95 _public member_ `FGuid ProceduralGuid;`
- L96 _public member_ `FBodyInstance* ProceduralVolumeInstance;`

### `Source/Runtime/Foliage/Public/ProceduralFoliageInstance.h` (Public)


#### enum `ESimulationOverlap::Type`  
`enum Type : int`  
_L17-25_
- L20 _public enumerator_ `CollisionOverlap` — Instances overlap with collision
- L22 _public enumerator_ `ShadeOverlap` — Instances overlap with shade
- L24 _public enumerator_ `None` — No overlap

#### enum `ESimulationQuery::Type`  
`enum Type : int`  
_L31-40_
- L33 _public enumerator_ `None = 0 UMETA(Hidden)`
- L35 _public enumerator_ `CollisionOverlap = 1` — Instances overlap with collision
- L37 _public enumerator_ `ShadeOverlap = 2` — Instances overlap with shade
- L39 _public enumerator_ `AnyOverlap = 3` — any overlap

#### struct `FProceduralFoliageOverlap`  
`struct FProceduralFoliageOverlap`  
_L44-55_
- L46 _public function_ `FProceduralFoliageOverlap(FProceduralFoliageInstance* InA, FProceduralFoliageInstance* InB, ESimulationOverlap::Type InType) : A(InA) , B(InB) , OverlapType(InType)`
- L52 _public member_ `FProceduralFoliageInstance* A;`
- L53 _public member_ `FProceduralFoliageInstance* B;`
- L54 _public member_ `ESimulationOverlap::Type OverlapType;`

#### struct `FProceduralFoliageInstance`  
`struct FProceduralFoliageInstance`  
_L58-98_
- reflection: `USTRUCT(BlueprintType)`
- L62 _public prototype_ `FProceduralFoliageInstance();`
- L64 _public prototype_ `static FProceduralFoliageInstance* Domination(FProceduralFoliageInstance* A, FProceduralFoliageInstance* B, ESimulationOverlap::Type OverlapType);`
- L66 _public prototype_ `float GetMaxRadius() const;`
- L67 _public prototype_ `float GetShadeRadius() const;`
- L68 _public prototype_ `float GetCollisionRadius() const;`
- L70 _public function_ `bool IsAlive() const`
- L72 _public prototype_ `void TerminateInstance();`
- L76 _public member_ `FQuat Rotation;` — `UPROPERTY()`
- L79 _public member_ `FVector Location;` — `UPROPERTY(Category = ProceduralFoliageInstance, EditAnywhere, BlueprintReadWrite)`
- L82 _public member_ `float Age;` — `UPROPERTY(Category = ProceduralFoliageInstance, EditAnywhere, BlueprintReadWrite)`
- L85 _public member_ `FVector Normal;` — `UPROPERTY(Category = ProceduralFoliageInstance, EditAnywhere, BlueprintReadWrite)`
- L88 _public member_ `float Scale;` — `UPROPERTY()`
- L91 _public member_ `TObjectPtr<const UFoliageType> Type;` — `UPROPERTY()`
- L93 _public member_ `UActorComponent* BaseComponent;`
- L95 _public member_ `bool bBlocker;`
- L97 _private member_ `bool bAlive;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ESimulationOverlap`
- L29 _namespace_ `namespace ESimulationQuery`

### `Source/Runtime/Foliage/Public/ProceduralFoliageSpawner.h` (Public)


#### class `UProceduralFoliageSpawner`  
`class UProceduralFoliageSpawner : public UObject`  
_L17-87_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L23 _private member_ `int32 RandomSeed;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere, BlueprintReadOnly)` — The seed used for generating the randomness of the simulation.
- L27 _private member_ `float TileSize;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere, BlueprintReadOnly)` — Length of the tile (in cm) along one axis. The total area of the tile will be TileSize*TileSize.
- L31 _private member_ `int32 NumUniqueTiles;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere, BlueprintReadOnly)` — The number of unique tiles to generate. The final simulation is a procedurally determined combination of the various unique tiles.
- L35 _private member_ `float MinimumQuadTreeSize;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere, BlueprintReadOnly)` — Minimum size of the quad tree used during the simulation. Reduce if too many instances are in splittable leaf quads (as warned in the log).
- L37 _private member_ `FThreadSafeCounter LastCancel;`
- L42 _private member_ `TArray<FFoliageTypeObject> FoliageTypes;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere)` — The types of foliage to procedurally spawn.
- L49 _private member_ `bool bUseOverrideFoliageTerrainMaterials = false;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere)` — If checked, will override the default behavior of using the global foliage material list and instead use the Override Foliage Terrain Materials defined here. If the override is used, you must manually provide ALL materials this procedural foliage spawner should spawn on top of.
- L53 _private member_ `TArray<TSoftObjectPtr<UMaterialInterface>> OverrideFoliageTerrainMaterials;` — `UPROPERTY(Category = ProceduralFoliageSimulation, EditAnywhere)` — Procedural foliage will only spawn on materials specified here. These are only used if 'Use Override Foliage Terrain Materials' is checked.
- L57 _public prototype_ `void Simulate(int32 NumSteps = -1);` — `UFUNCTION(BlueprintCallable, Category = ProceduralFoliageSimulation)`
- L58 _public prototype_ `void Empty();`
- L60 _public prototype_ `int32 GetRandomNumber();`
- L62 _public function_ `const TArray<FFoliageTypeObject>& GetFoliageTypes() const`
- L64 _public function_ `bool UsesOverrideFoliageTerrainMaterials() const`
- L66 _public function_ `const TArray<TSoftObjectPtr<UMaterialInterface>>& GetFoliageTerrainMaterials() const`
- L69 _public prototype_ `void GetInstancesToSpawn(TArray<FProceduralFoliageInstance>& OutInstances, const FVector& Min = FVector(-FLT_MAX, -FLT_MAX, -FLT_MAX), const FVector& Max = FVector(FLT_MAX, FLT_MAX, FLT_MAX) ) const;` — Returns the instances that need to spawn for a given min,max region
- L71 _public prototype_ `virtual void Serialize(FArchive& Ar);`
- L74 _public prototype_ `const UProceduralFoliageTile* GetRandomTile(int32 X, int32 Y);` — Takes a tile index and returns a random tile associated with that index.
- L77 _public prototype_ `UProceduralFoliageTile* CreateTempTile();` — Creates a temporary empty tile with the appropriate settings created for it.
- L80 _private prototype_ `void CreateProceduralFoliageInstances();`
- L82 _private prototype_ `void SetClean();`
- L84 _private member_ `TArray<TWeakObjectPtr<UProceduralFoliageTile>> PrecomputedTiles;`
- L86 _private member_ `FRandomStream RandomStream;`

### `Source/Runtime/Foliage/Public/ProceduralFoliageTile.h` (Public)


#### class `UProceduralFoliageTile`  
`class UProceduralFoliageTile : public UObject`  
_L30-146_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Procedurally determines where to spawn foliage meshes within a discrete area. Generally, a procedural foliage simulation as a whole is composed of multiple tiles. Tiles are able to overlap one another as well to create a seamless appearance. Note that the tile is not responsible for actually spawning any instances, it only determines where they should be placed. Following a simulation, call ExtractDesiredInstances for information about where each instance should spawn. Note also that, barring any core changes to the ordering of TSet, foliage generation is deterministic (i.e. given the same inputs, the result of the simulation will always be the same).
- L40 _private prototype_ `void Simulate(const UProceduralFoliageSpawner* InFoliageSpawner, const int32 RandomSeed, const int32 MaxNumSteps, const int32 InLastCancel);` — Procedurally determine the placement of foliage instances. @param InFoliageSpawner the foliage spawner containing the various foliage types to simulate @param RandomSeed For seeding (in the RNG sense) the random dispersion of seeds (in the foliage sense) @param MaxNumSteps The maximum number of steps to run the simulation
- L45 _private prototype_ `void ExtractDesiredInstances(TArray<FDesiredFoliageInstance>& OutDesiredInstances, const FTransform& WorldTM, const FVector2D& ActorVolumeLocation, FVector::FReal ActorVolumeMaxExtent, const FGuid& ProceduralGuid, const FVector::FReal HalfHeight, const FBodyInstance* VolumeBodyInstance, bool bEmptyTileInfo = true);` — Extracts information on each instance that should be spawned based on the simulation.
- L54 _private prototype_ `void CopyInstancesToTile(UProceduralFoliageTile* ToTile, const FBox2D& LocalAABB, const FTransform& RelativeTM, const float Overlap) const;` — Copies instances within this tile to another @param ToTile The tile to copy instances to @param LocalAABB The region (in local space) to copy instances from @param RelativeTM The transform of the destination tile relative to this tile @param Overlap The amount by which the tiles are overlapping
- L60 _private prototype_ `void RemoveInstance(FProceduralFoliageInstance* Inst);` — Removes a single instance from the tile @param Inst The instance to remove
- L63 _private prototype_ `void RemoveInstances();` — Removes all instances from the tile
- L66 _private prototype_ `void Empty();` — Empty arrays and sets
- L69 _private prototype_ `void InitSimulation(const UProceduralFoliageSpawner* InFoliageSpawner, const int32 InRandomSeed);` — Initializes the tile for simulation. Called automatically by Simulate, so only bother to call if the tile won't actually simulate.
- L72 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;` — UObject interface
- L73 _private prototype_ `virtual void BeginDestroy() override;`
- L85 _private prototype_ `void GetInstancesInAABB(const FBox2D& LocalAABB, TArray<FProceduralFoliageInstance* >& OutInstances, bool bFullyContainedOnly = true) const;` — Finds all the instances within an AABB. The instances are returned in the space local to the AABB. That is, an instance in the bottom left AABB will have a coordinate of (0,0). @param LocalAABB The AABB to get instances within @param OutInstances Contains the instances within the specified AABB @param bFullyContainedOnly If true, will only get instances that are fully contained within the AABB
- L93 _private prototype_ `void AddInstances(const TArray<FProceduralFoliageInstance*>& NewInstances, const FTransform& ToLocalTM, const FBox2D& InnerLocalAABB);` — Adds procedural instances to the tile from some external source. @param The new instances to add to the tile @param ToLocalTM Used to transform the new instances to this tile's local space @param InnerLocalAABB New instances outside this region will be tracked for blocking purposes only (and never spawned)
- L96 _private prototype_ `void InstancesToArray();` — Fills the InstancesArray by iterating through the contents of the InstancesSet
- L101 _private prototype_ `void RunSimulation(const int32 MaxNumSteps, bool bOnlyInShade);` — Run the simulation for the appropriate number of steps. @param bOnlyInShade Whether the simulation should run exclusively within existing shade from other instances
- L104 _private prototype_ `void StepSimulation();` — Advance the simulation by a step (think of a step as a generation)
- L107 _private prototype_ `void AddRandomSeeds(TArray<FProceduralFoliageInstance*>& OutInstances);` — Randomly seed the next step of the simulation
- L110 _private prototype_ `bool HandleOverlaps(FProceduralFoliageInstance* Instance);` — Determines whether the instance will survive all the overlaps, and then kills the appropriate instances. Returns true if the instance survives
- L113 _private prototype_ `FProceduralFoliageInstance* NewSeed(const FVector& Location, float Scale, const UFoliageType* Type, float InAge, bool bBlocker = false);` — Attempts to create a new instance and resolves any overlaps. Returns the new instance if successful for calling code to add to Instances
- L115 _private prototype_ `void SpreadSeeds(TArray<FProceduralFoliageInstance*>& NewSeeds);`
- L116 _private prototype_ `void AgeSeeds();`
- L118 _private prototype_ `void MarkPendingRemoval(FProceduralFoliageInstance* ToRemove);`
- L119 _private prototype_ `void FlushPendingRemovals();`
- L121 _private prototype_ `bool UserCancelled() const;`
- L126 _private member_ `TObjectPtr<const UProceduralFoliageSpawner> FoliageSpawner;` — `UPROPERTY()`
- L128 _private member_ `TSet<FProceduralFoliageInstance*> PendingRemovals;`
- L129 _private member_ `TSet<FProceduralFoliageInstance*> InstancesSet;`
- L132 _private member_ `TArray<FProceduralFoliageInstance> InstancesArray;` — `UPROPERTY()`
- L134 _private member_ `int32 SimulationStep;`
- L135 _private member_ `FProceduralFoliageBroadphase Broadphase;`
- L137 _private member_ `int32 RandomSeed;`
- L138 _private member_ `FRandomStream RandomStream;`
- L139 _private member_ `bool bSimulateOnlyInShade;`
- L141 _private member_ `int32 LastCancel;`
- L144 _private prototype_ `float GetRandomGaussian();`
- L145 _private prototype_ `FVector GetSeedOffset(const UFoliageType* Type, float MinDistance);`

### `Source/Runtime/Foliage/Public/ProceduralFoliageVolume.h` (Public)


#### class `AProceduralFoliageVolume`  
`class AProceduralFoliageVolume: public AVolume, public IWorldPartitionActorLoaderInterface`  
_L15-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AVolume,IWorldPartitionActorLoaderInterface`
- L20 _private member_ `TObjectPtr<UProceduralFoliageComponent> ProceduralComponent;` — `UPROPERTY(Category = ProceduralFoliage, VisibleAnywhere, BlueprintReadOnly)`
- L24 _private prototype_ `virtual void PostRegisterAllComponents();`
- L28 _private prototype_ `virtual void BeginDestroy() override;`
- L29 _private prototype_ `virtual void PostEditImport() override;`
- L32 _private prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L35 _private prototype_ `virtual ILoaderAdapter* GetLoaderAdapter() override;`
- L39 _private member_ `FLoaderAdapterActor* WorldPartitionActorLoader;`
