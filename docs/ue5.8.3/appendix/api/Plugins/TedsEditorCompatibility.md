# Plugins / TedsEditorCompatibility

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility`
- headers: 8; symbols: 65
- symbol kinds: class=6, macro=1, member=7, namespace=7, prototype=37, struct=4, typedef=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, TypedElementFramework, UnrealEd

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Private/ActorDesc/TedsActorDescFactory.h` (Private)


#### class `UTedsActorDescFactory`  
`class UTedsActorDescFactory : public UEditorDataStorageFactory`  
_L18-33_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Factory to manage queries for unloaded actors in TEDS
- L23 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L24 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L26 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L29 _protected prototype_ `void RegisterActorDesc(UActorDescContainerInstance* ContainerInstance, FWorldPartitionActorDescInstance* ActorDescInstance);`
- L30 _protected prototype_ `void UnregisterActorDesc(UActorDescContainerInstance* ContainerInstance, FWorldPartitionActorDescInstance* ActorDescInstance);`
- L31 _protected prototype_ `void OnActorDescUpdated(FWorldPartitionActorDescInstance* ActorDescInstance);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Private/ActorDesc/TedsWorldPartitionPinnedQueries.h` (Private)


#### class `UActorWorldPartitionPinnedDataStorageFactory`  
`class UActorWorldPartitionPinnedDataStorageFactory : public UEditorDataStorageFactory`  
_L17-65_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Registers queries that keep FWorldPartitionPinnedColumn in sync with the World Partition pinned actor/actor desc state.
- L22 _public prototype_ `~UActorWorldPartitionPinnedDataStorageFactory() override = default;`
- L24 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L26 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L32 _private prototype_ `void RegisterActorAddWorldPartitionPinnedColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds FWorldPartitionPinnedColumn to actor rows that support pinning and do not already have the column.
- L38 _private prototype_ `void RegisterActorDescAddWorldPartitionPinnedColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds FWorldPartitionPinnedColumn to actor desc rows that support pinning and do not already have the column.
- L43 _private prototype_ `void RegisterWorldToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Syncs the World Partition pinned state to FWorldPartitionPinnedColumn if they differ.
- L49 _private prototype_ `void RegisterColumnToWorldQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage);` — Applies the column's bIsPinned value back to the World Partition via PinActors / UnpinActors if the FTypedElementSyncBackToWorldTag has been set and the bIsPinned differs.
- L54 _private prototype_ `bool Tick(float);` — Custom ticker to process pending pins/unpins since they cannot be done inside a processor
- L60 _private member_ `TMap<TWeakObjectPtr<UWorldPartition>, TArray<FGuid>> PendingPinMap;` — Store maps of the actors/actor descs that need to be pinned/unpinned, keyed by the world partition they belong to so we can batch pin/unpin them at once
- L61 _private member_ `TMap<TWeakObjectPtr<UWorldPartition>, TArray<FGuid>> PendingUnpinMap;`
- L63 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Private/ActorFolders/FolderCompatibilityWidget.h` (Private)


#### class `UFolderCompatibilityWidgetFactory`  
`class UFolderCompatibilityWidgetFactory : public UEditorDataStorageFactory`  
_L12-21_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L17 _public prototype_ `~UFolderCompatibilityWidgetFactory() override = default;`
- L19 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FFolderCompatibilityWidgetConstructor`  
`struct FFolderCompatibilityWidgetConstructor : public FSimpleWidgetConstructor`  
_L24-38_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L29 _public prototype_ `FFolderCompatibilityWidgetConstructor();`
- L30 _public prototype_ `~FFolderCompatibilityWidgetConstructor() override = default;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Private/Level/TedsLevelFactory.h` (Private)


#### class `UTedsLevelFactory`  
`class UTedsLevelFactory : public UEditorDataStorageFactory`  
_L10-20_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L15 _public prototype_ `virtual ~UTedsLevelFactory() override = default;`
- L17 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L18 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L19 _public prototype_ `virtual void PostRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Private/World/TedsWorldFactory.h` (Private)


#### class `UTedsWorldFactory`  
`class UTedsWorldFactory : public UEditorDataStorageFactory`  
_L12-31_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L17 _public prototype_ `~UTedsWorldFactory() override = default;`
- L19 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L20 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L21 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L22 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L26 _private prototype_ `void PostWorldInitialized(UWorld* InWorld, const UWorld::InitializationValues IVS) const;`
- L27 _private prototype_ `void OnPreWorldFinishDestroy(UWorld* World) const;`
- L30 _private member_ `UE::Editor::DataStorage::ICompatibilityProvider* DataStorageCompat;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Public/ActorDesc/TedsActorDescColumns.h` (Public)


#### struct `FEditorDataStorageActorDescTag`  
`struct FEditorDataStorageActorDescTag final : public FEditorDataStorageTag`  
_L14-17_
- reflection: `USTRUCT(meta = (DisplayName = "Unloaded Actor"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify a row with an unloaded actor

#### struct `FEditorDataStorageWorldPartitionHandleColumn`  
`struct FEditorDataStorageWorldPartitionHandleColumn final : public FEditorDataStorageColumn`  
_L23-27_
- reflection: `USTRUCT(meta = (DisplayName = "World Partition Handle"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column containing the world partition handle for an actor desc in TEDS
- L26 _public member_ `FWorldPartitionHandle Handle;`

#### struct `FEditorDataStorageWorldPartitionPinnedColumn`  
`struct FEditorDataStorageWorldPartitionPinnedColumn final : public FEditorDataStorageColumn`  
_L33-39_
- reflection: `USTRUCT(meta = (DisplayName = "World Partition Pinned"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the World Partition pinned state of a row
- L38 _public member_ `bool bIsPinned = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace Editor` (scope `UE`)
- L41 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L43 _typedef_ `using FActorDescTag = FEditorDataStorageActorDescTag;` (scope `UE::Editor::DataStorage`)
- L44 _typedef_ `using FWorldPartitionHandleColumn = FEditorDataStorageWorldPartitionHandleColumn;` (scope `UE::Editor::DataStorage`)
- L45 _typedef_ `using FWorldPartitionPinnedColumn = FEditorDataStorageWorldPartitionPinnedColumn;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Public/ActorDesc/TedsActorDescUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEDSEDITORCOMPATIBILITY_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _namespace_ `namespace UnloadedActor` (scope `UE::Editor::DataStorage`)
- L13 _prototype_ `FName GetActorDescTableName();` (scope `UE::Editor::DataStorage::UnloadedActor`)
- L15 _prototype_ `FName GetActorDescMappingDomain();` (scope `UE::Editor::DataStorage::UnloadedActor`)
- L17 _prototype_ `FMapKey GetActorDescMappingKey(const FWorldPartitionActorDescInstance* ActorDescInstance);` (scope `UE::Editor::DataStorage::UnloadedActor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsEditorCompatibility/Public/Factories/TedsEditorHierarchyFactory.h` (Public)


#### class `UTedsEditorHierarchyFactory`  
`class UTedsEditorHierarchyFactory : public UEditorDataStorageFactory`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `~UTedsEditorHierarchyFactory() override = default;`
- L21 _public member_ `static FName EditorObjectHierarchyName;` — Hierarchy for objects in the editor (e.g UWorld, ULevel, AActor)
- L23 _public prototype_ `virtual void RegisterHierarchies(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
