# Plugins / FoliageSupport

- module root: `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport`
- headers: 8; symbols: 102
- symbol kinds: class=6, externvar=1, function=10, member=17, namespace=32, prototype=36
- PrivateDependencyModuleNames: CoreUObject, Engine, Foliage, FoliageEdit, LevelSnapshots
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageLevelSnapshotsConsoleVariables.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L7 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L7 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)
- L16 _externvar_ `extern TAutoConsoleVariable<bool> CVarAllowFoliageDataPre5dot1;` (scope `UE::LevelSnapshots::Foliage::Private`) — Foliage data saved before 5.2 was saved in a bad format which may cause a crash. It is safe to enable this if either: 1. All foliage were assets (possible / conceivable) 2. All foliage were subobjects (possible / conceivable) 3. First assets were added, then subobjects subobjects (unlikely) Subobject = add by drag-droping static mesh, asset = drag-drop UFoliageType asset

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageSupport/Apply/ApplyDataUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)
- L16 _prototype_ `FFoliageInfo* FindOrAddFoliageInfo(UFoliageType* FoliageType, AInstancedFoliageActor* FoliageActor);` (scope `UE::LevelSnapshots::Foliage::Private`) — Adds the foliage type to the instanced actor or returns the associated FFoliageInfo if already present.
- L31 _prototype_ `void HandleExistingFoliageUsingRequiredComponent(AInstancedFoliageActor* FoliageActor, FName RequiredComponentName, const TMap<FName, UFoliageType*>& PreexistingComponentToFoliageType, UFoliageType* AllowedFoliageType);` (scope `UE::LevelSnapshots::Foliage::Private`) — Handles name clashes with pre-existing instanced components. This handles in particular this case 1. Add (static mesh) foliage type FoliageA. Let's suppose the component that is added is called Component01. 2. Take snapshot 3. Reload map without saving 4. Add foliage type FoliageB. This creates a new component that is also called Component01. 5. Restore snapshot Both FoliageA and FoliageB would use Component01 to add instances. We remove the foliage type under the "interpretation" that Component01 is "restored" to reuse the previous foliage type
- L34 _prototype_ `void RemoveComponentAutoRecreatedByLevelSnapshots(AInstancedFoliageActor* FoliageActor, TOptional<FName> RecreatedComponentName);` (scope `UE::LevelSnapshots::Foliage::Private`) — Default LS restoration will recreate all components. However, if the user said to skip restoring some of the components, we'll remove the wrongly added components again.
- L37 _prototype_ `TMap<FName, UFoliageType*> BuildComponentToFoliageType(AInstancedFoliageActor* FoliageActor);` (scope `UE::LevelSnapshots::Foliage::Private`) — Returns an inverse map binding hierarchical mesh component names to the foliage type they represent.

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageSupport/Apply/FoliageRestorationInfo.h` (Private)


#### class `UE::LevelSnapshots::Foliage::Private::FFoliageRestorationInfo`  
`class FFoliageRestorationInfo`  
_L16-29_
- desc: Tells us whether foliage types should be added / removed / serialized into AInstancedFoliageActor::FoliageInfos
- L18 _private member_ `TArray<UActorComponent*> ModifiedComponents;`
- L19 _private member_ `TArray<TWeakObjectPtr<UActorComponent>> EditorWorldComponentsToRemove;`
- L20 _private member_ `TArray<TWeakObjectPtr<UActorComponent>> SnapshotComponentsToAdd;`
- L22 _private member_ `bool bWasRecreated = false;`
- L25 _public prototype_ `static FFoliageRestorationInfo From(AInstancedFoliageActor* Object, const FPropertySelectionMap& SelectionMap, bool bWasRecreated);`
- L27 _public prototype_ `bool ShouldSkipFoliageType(const FFoliageInfoData& SavedData) const;`
- L28 _public prototype_ `bool ShouldSerializeFoliageType(const FFoliageInfoData& SavedData) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L11 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L11 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageSupport/Data/FoliageInfoData.h` (Private)


#### class `UE::LevelSnapshots::Foliage::Private::FFoliageInfoData`  
`class FFoliageInfoData`  
_L11-49_
- desc: Data we'll send to FFoliageImpl::Serialize
- L13 _private member_ `EFoliageImplType ImplType = EFoliageImplType::Unknown;`
- L14 _private member_ `FName ComponentName;`
- L17 _private member_ `TArray<uint8> SerializedData_DEPRECATED;` — Used before FSnapshotCustomVersion::CustomSubobjectSoftObjectPathRefactor
- L19 _private member_ `int64 FoliageInfoArchiveSize = 0;` — Added after FSnapshotCustomVersion::CustomSubobjectSoftObjectPathRefactor
- L25 _private member_ `int64 ArchiveTellBeforeSerialization;` — What Ar.Tell returned at the beginning of CaptureDataAndWriteFoliageInfoIntoArchive (since 5.2, FoliageTypesUnreadable). Used to jump across data to selectively apply data to foliage (since the user can choose to restore partially).
- L27 _private prototype_ `FArchive& SerializeInternal(FArchive& Ar);`
- L32 _public prototype_ `void FillDataMembersAndWriteFoliageInfoIntoArchive(FArchive& Archive, FFoliageInfo& DataToReadFrom);` — Saves FFoliageInfo into the archive and updates our data members. The our data members are NOT saved into the archive at this point.
- L37 _public prototype_ `void ApplyTo(FArchive& Archive, FFoliageInfo& DataToWriteInto) const;` — Given an archive containing data written by FillDataMembersAndWriteFoliageInfoIntoArchive previously and applies that data to the FFoliageInfo. 5.0 and before still uses SerializedData_DEPRECATED for this while 5.2 and beyond seeks to ArchiveTellBeforeSerialization and then reads.
- L39 _public function_ `EFoliageImplType GetImplType() const`
- L40 _public function_ `TOptional<FName> GetComponentName() const`
- L42 _public function_ `int64 GetFoliageInfoArchiveSize() const`
- L43 _public function_ `int64 GetArchiveTellBeforeSerialization() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L8 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)
- L45 _function_ `friend FArchive& operator<<(FArchive& Ar, FFoliageInfoData& MeshInfo)` (scope `UE::LevelSnapshots::Foliage::Private`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageSupport/Data/InstancedFoliageActorData.h` (Private)


#### class `UE::LevelSnapshots::Foliage::Private::FInstancedFoliageActorData`  
`class FInstancedFoliageActorData`  
_L16-47_
- desc: Handles saving of AInstancedFoliageActor::FoliageInfos
- L24 _private member_ `TMap<TSoftObjectPtr<UFoliageType>, FFoliageInfoData> FoliageAssets;` — Foliage type asset references. Consists of foliage type assets added via the green Add button or drag-drop a foliage type or if you drag-drop a foliage type from the content browser.
- L30 _private member_ `TArray<FSubobjectFoliageInfoData> SubobjectData;` — Saves foliage type subobjects. Consists of foliage types created when you drag-drop a static mesh or add Blueprint derived foliage types.
- L33 _private prototype_ `void ApplyData_Pre5dot2(FArchive& Archive, AInstancedFoliageActor* FoliageActor, const FPropertySelectionMap& SelectedProperties, bool bWasRecreated) const;` — Serialization version pre 5.1. Data saved in 5.1 is discarded. Looks up saved foliage types and restores the passed in foliage actor.
- L36 _private prototype_ `void ApplyTo_5dot2(FArchive& Archive, AInstancedFoliageActor* FoliageActor, const FPropertySelectionMap& SelectedProperties, bool bWasRecreated) const;` — Serialization version starting 5.2. Data saved in 5.1 is discarded.
- L43 _public prototype_ `static void CaptureData(FArchive& Archive, AInstancedFoliageActor* FoliageActor);` — Saves foliage actor into this object
- L46 _public prototype_ `static void LoadAndApplyTo(FArchive& Archive, AInstancedFoliageActor* FoliageActor, const FPropertySelectionMap& SelectedProperties, bool bWasRecreated);` — Loads the saved foliage data and applies it to FoliageActor respecting the selection in SelectedProperties.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageSupport/Data/SubobjectFoliageInfoData.h` (Private)


#### class `UE::LevelSnapshots::Foliage::Private::FSubobjectFoliageInfoData`  
`class FSubobjectFoliageInfoData : public FFoliageInfoData`  
_L18-44_
- inherits: `FFoliageInfoData`
- L20 _private member_ `TSubclassOf<UFoliageType> Class;`
- L21 _private member_ `FName SubobjectName;`
- L24 _private member_ `TArray<uint8> SerializedSubobjectData_DEPRECATED;` — Used before FSnapshotCustomVersion::CustomSubobjectSoftObjectPathRefactor
- L26 _private member_ `int64 FoliageTypeArchiveSize = 0;` — Added after FSnapshotCustomVersion::CustomSubobjectSoftObjectPathRefactor
- L28 _private prototype_ `FArchive& SerializeInternal(FArchive& Ar);`
- L32 _public prototype_ `void FillDataMembersAndSerializeFoliageTypeAndInfoIntoArchive(FArchive& Archive, UFoliageType* FoliageSubobject, FFoliageInfo& FoliageInfo);`
- L34 _public prototype_ `UFoliageType* FindOrRecreateSubobject(AInstancedFoliageActor* Outer) const;`
- L35 _public prototype_ `bool ApplyToFoliageType(FArchive& Archive, UFoliageType* FoliageSubobject) const;`
- L36 _public prototype_ `void ApplyToFoliageInfo(FArchive& Archive, FFoliageInfo& DataToWriteInto) const;`
- L38 _public function_ `int64 GetFoliageTypeArchiveSize() const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)
- L16 _prototype_ `FArchive& operator<<(FArchive& Ar, FSubobjectFoliageInfoData& Data);` (scope `UE::LevelSnapshots::Foliage::Private`)
- L40 _function_ `friend FArchive& operator<<(FArchive& Ar, FSubobjectFoliageInfoData& Data)` (scope `UE::LevelSnapshots::Foliage::Private`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageSupport/FoliageSupport.h` (Private)


#### class `UE::LevelSnapshots::Foliage::Private::FFoliageSupport`  
`class FFoliageSupport : public ISnapshotRestorabilityOverrider, public ICustomObjectSnapshotSerializer, public IRestorationListener, public IActorSnapshotFilter`  
_L17-63_
- inherits: `ISnapshotRestorabilityOverrider,ICustomObjectSnapshotSerializer,IRestorationListener,IActorSnapshotFilter`
- L25 _private member_ `TWeakObjectPtr<AInstancedFoliageActor> CurrentFoliageActor;` — Just used to verify snapshots is in a valid state
- L28 _private member_ `TArray<TWeakObjectPtr<AInstancedFoliageActor>> ActorsNeedingRefresh;` — Tracks modified foliage actors since they must be refreshed AFTER the snapshot has serialized all properties (in PostApplySnapshot).
- L34 _public prototype_ `static void Register(ILevelSnapshotsModule& Module);`
- L37 _public prototype_ `virtual ERestorabilityOverride IsActorDesirableForCapture(const AActor* Actor) override;`
- L41 _public prototype_ `virtual void OnTakeSnapshot(UObject* EditorObject, ICustomSnapshotSerializationData& DataStorage) override;`
- L42 _public function_ `virtual UObject* FindOrRecreateSubobjectInSnapshotWorld(UObject* SnapshotObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`
- L43 _public function_ `virtual UObject* FindOrRecreateSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`
- L44 _public function_ `virtual UObject* FindSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`
- L45 _public prototype_ `virtual void PostApplyToEditorObject(UObject* Object, const ICustomSnapshotSerializationData& DataStorage, const FPropertySelectionMap& SelectionMap) override;`
- L49 _public prototype_ `virtual void PostApplySnapshot(const FPostApplySnapshotParams& Params) override;`
- L50 _public prototype_ `virtual void PostApplySnapshotToActor(const FApplySnapshotToActorParams& Params) override;`
- L51 _public prototype_ `virtual void PreApplySnapshotProperties(const FApplySnapshotPropertiesParams& Params) override;`
- L52 _public prototype_ `virtual void PostApplySnapshotProperties(const FApplySnapshotPropertiesParams& Params) override;`
- L53 _public prototype_ `virtual void PreRecreateActor(UWorld* World, TSubclassOf<AActor> ActorClass, FActorSpawnParameters& InOutSpawnParameters) override;`
- L54 _public prototype_ `virtual void PostRecreateActor(AActor* RecreatedActor) override;`
- L55 _public prototype_ `virtual void PreRemoveActor(const FPreRemoveActorParams& Params) override;`
- L56 _public prototype_ `virtual void PreRemoveComponent(UActorComponent* ComponentToRemove) override;`
- L60 _public prototype_ `virtual FFilterResultData CanModifyMatchedActor(const FCanModifyMatchedActorParams& Params) override;`
- L61 _public prototype_ `virtual FFilterResultData CanRecreateMissingActor(const FCanRecreateActorParams& Params) override;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L15 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L15 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/FoliageSupport/Private/FoliageSupportModule.h` (Private)


#### class `UE::LevelSnapshots::Foliage::Private::FFoliageSupportModule`  
`class FFoliageSupportModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace Foliage` (scope `UE::LevelSnapshots`)
- L8 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::Foliage`)
