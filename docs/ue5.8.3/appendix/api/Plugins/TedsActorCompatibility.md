# Plugins / TedsActorCompatibility

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility`
- headers: 27; symbols: 148
- symbol kinds: class=20, function=1, member=17, namespace=18, prototype=80, struct=10, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, LevelInstanceEditor, Slate, SlateCore, TedsEditorCompatibility, TedsQueryStack, TedsTableViewer, TypedElementFramework, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: 

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/ActorComponentDebugHierarchyWidget/ActorComponentTree.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Editor` (scope `UE`)
- L5 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L5 _namespace_ `namespace ActorCompatibility` (scope `UE::Editor::DataStorage`)
- L7 _prototype_ `void RegisterActionComponentDebugHierarchyWidget();` (scope `UE::Editor::DataStorage::ActorCompatibility`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/ActorComponentDebugHierarchyWidget/QueryStackNodes/RowQueryCallbackResultsNode.h` (Private)


#### class `UE::Editor::DataStorage::QueryStack::FRowQueryCallbackResultsNode`  
`class FRowQueryCallbackResultsNode : public FRowQueryResultsNode`  
_L19-40_
- inherits: `FRowQueryResultsNode`
- desc: A node that is configured with a query and a callback.  The callback can be used to read and filter data from the rows that match the query and can emit 0 or more rows that will be added to the node. This node can be useful for collating rows referenced from other rows.
- L22 _public typedef_ `using EmitRowFn = TFunctionRef<void(TArrayView<const RowHandle>)>;`
- L23 _public typedef_ `using CallbackFn = TFunction<void(IDirectQueryContext&, TArrayView<const RowHandle>, EmitRowFn EmitRows)>;`
- L25 _public prototype_ `FRowQueryCallbackResultsNode( ICoreProvider& Storage, TSharedPtr<IQueryNode> InQueryNode, CallbackFn InCallback);`
- L29 _public prototype_ `FRowQueryCallbackResultsNode( ICoreProvider& Storage, TSharedPtr<IQueryNode> InQueryNode, ESyncActions SyncAction, CallbackFn InCallback);`
- L36 _protected prototype_ `virtual void RefreshInternal(FRowHandleArray& TargetRows) override;`
- L39 _private member_ `CallbackFn Callback;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Editor` (scope `UE`)
- L6 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/ActorComponentDebugHierarchyWidget/SActorComponentTreeWidget.h` (Private)


#### class `SActorComponentTreeWidget`  
`class SActorComponentTreeWidget : public SCompoundWidget`  
_L23-39_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SActorComponentTreeWidget)`
- L28 _public prototype_ `SLATE_END_ARGS();`
- L33 _public prototype_ `void Construct( const FArguments& InArgs, UE::Editor::DataStorage::FHierarchyHandle InHierarchyHandle, TSharedPtr<UE::Editor::DataStorage::QueryStack::IRowNode>& InRowProvider);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorComponentFactory.h` (Private)


#### class `UTedsActorComponentFactory`  
`class UTedsActorComponentFactory : public UEditorDataStorageFactory`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L17 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L18 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorGuidQueries.h` (Private)


#### class `UActorGuidDataStorageFactory`  
`class UActorGuidDataStorageFactory : public UEditorDataStorageFactory`  
_L15-23_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Registers queries that keep FGuidColumn in sync with the actor's Guid.
- L20 _public prototype_ `~UActorGuidDataStorageFactory() override = default;`
- L22 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorIconOverrideQueries.h` (Private)


#### class `UActorIconOverrideDataStorageFactory`  
`class UActorIconOverrideDataStorageFactory : public UEditorDataStorageFactory`  
_L11-19_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `virtual ~UActorIconOverrideDataStorageFactory() override = default;`
- L18 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorLabelQueries.h` (Private)


#### class `UActorLabelDataStorageFactory`  
`class UActorLabelDataStorageFactory : public UEditorDataStorageFactory`  
_L12-31_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L17 _public prototype_ `~UActorLabelDataStorageFactory() override = default;`
- L19 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _private prototype_ `void RegisterActorLabelToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the label set on an actor and copies it to the Data Storage if they differ.
- L30 _private prototype_ `void RegisterLabelColumnToActorQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the label stored in the Data Storage and copies it to the actor's label if the FTypedElementSyncBackToWorldTag has been set and the labels differ.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorLevelQueries.h` (Private)


#### class `UActorLevelDataStorageFactory`  
`class UActorLevelDataStorageFactory : public UEditorDataStorageFactory`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UActorLevelDataStorageFactory() override = default;`
- L18 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L24 _private prototype_ `void RegisterActorAddLevelColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds the level column to new actors that do not have one already.
- L28 _private prototype_ `void RegisterActorLevelToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the level of the actor and copies it to the Data Storage if they differ.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorMobilityQueries.h` (Private)


#### class `UActorMobilityDataStorageFactory`  
`class UActorMobilityDataStorageFactory : public UEditorDataStorageFactory`  
_L11-47_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UActorMobilityDataStorageFactory() override = default;`
- L18 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L24 _private prototype_ `void RegisterActorAddMobilityColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds the mobility column to new actors that do not have one already.
- L28 _private prototype_ `void RegisterActorMobilityToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the mobility set on an actor and copies it to the Data Storage if they differ.
- L33 _private prototype_ `void RegisterMobilityColumnToActorQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the mobility stored in the Data Storage and copies it to the actor's mobility if the FTypedElementSyncBackToWorldTag has been set and the visibility differ.
- L39 _private prototype_ `void RegisterLockTransformActorToTagQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes each actor's IsLockLocation status, and adds/removes a FTypedElementLockTransformTag in the Data Storage if FTypedElementSyncFromWorldTag is set.
- L46 _private prototype_ `void RegisterLockTransformTagToActorQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the FTypedElementLockTransformTag presence/absence in the Data Storage and calls SetLockLocation on the actor if the FTypedElementSyncBackToWorldTag has been set and the lock status differs.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorParentQueries.h` (Private)


#### class `UActorParentDataStorageFactory`  
`class UActorParentDataStorageFactory : public UEditorDataStorageFactory`  
_L13-38_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `~UActorParentDataStorageFactory() override = default;`
- L20 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L21 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L22 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L28 _private prototype_ `void RegisterActorParentQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Sets the hierarchy for an actor in the editor
- L33 _private prototype_ `void OnLevelActorDetached(AActor* Actor, const AActor* OldParent) const;` — Function called when an actor is detached from its parent in the world
- L36 _private member_ `UE::Editor::DataStorage::FHierarchyHandle EditorActorHierarchyHandle;`
- L37 _private member_ `UE::Editor::DataStorage::ICoreProvider* DataStorage;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorRootObjectQueries.h` (Private)


#### class `UActorRootObjectDataStorageFactory`  
`class UActorRootObjectDataStorageFactory : public UEditorDataStorageFactory`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UActorRootObjectDataStorageFactory() override = default;`
- L18 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L24 _private prototype_ `void RegisterActorAddRootObjectColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds the root object column to new actors that do not have one already.
- L28 _private prototype_ `void RegisterActorRootObjectToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the folder root object of the actor and copies it to the Data Storage.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorSocketQueries.h` (Private)


#### class `UActorSocketDataStorageFactory`  
`class UActorSocketDataStorageFactory : public UEditorDataStorageFactory`  
_L10-28_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L15 _public prototype_ `~UActorSocketDataStorageFactory() override = default;`
- L17 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L23 _private prototype_ `void RegisterActorAddSocketColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds the socket column to new actors that do not have one already.
- L27 _private prototype_ `void RegisterActorSocketToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the socket name set on an actor and copies it to the Data Storage.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorUIDisplayQueries.h` (Private)


#### class `UActorUIDisplayDataStorageFactory`  
`class UActorUIDisplayDataStorageFactory : public UEditorDataStorageFactory`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UActorUIDisplayDataStorageFactory() override = default;`
- L18 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L23 _private prototype_ `void RegisterSyncActorHideRowFromUITagQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Registers queries to check if the updated Actor row or the Component row of an Actor should be given the HideRowFromUITag

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorViewportProcessors.h` (Private)


#### class `UActorViewportDataStorageFactory`  
`class UActorViewportDataStorageFactory : public UEditorDataStorageFactory`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UActorViewportDataStorageFactory() override = default;`
- L18 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L21 _private prototype_ `void RegisterOutlineColorColumnToActor(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L22 _private prototype_ `void RegisterOverlayColorColumnToActor(UE::Editor::DataStorage::ICoreProvider& DataStorage);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorVisibilityQueries.h` (Private)


#### class `UActorVisibilityDataStorageFactory`  
`class UActorVisibilityDataStorageFactory : public UEditorDataStorageFactory`  
_L13-38_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `~UActorVisibilityDataStorageFactory() override = default;`
- L20 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L27 _private prototype_ `void RegisterActorAddVisibilityColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds the Visibility columns to new actors that do not have one already.
- L32 _private prototype_ `void RegisterActorVisibilityToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the visibility set on an actor and copies it to the Data Storage if they differ.
- L37 _private prototype_ `void RegisterVisibilityColumnToActorQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the visibility stored in the Data Storage and copies it to the actor's visibility if the FTypedElementSyncBackToWorldTag has been set and the visibility differ.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorWorldPartitionContentBundleQueries.h` (Private)


#### class `UActorWorldPartitionContentBundleDataStorageFactory`  
`class UActorWorldPartitionContentBundleDataStorageFactory : public UEditorDataStorageFactory`  
_L15-36_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Registers queries that keep FWorldPartitionContentBundleColumn in sync with the actor's content bundle assignment. Read-only — no write-back to world.
- L20 _public prototype_ `~UActorWorldPartitionContentBundleDataStorageFactory() override = default;`
- L22 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L29 _private prototype_ `void RegisterActorAddWorldPartitionContentBundleColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds FWorldPartitionContentBundleColumn to actor rows in WP worlds with content bundles enabled that do not already have the column.
- L35 _private prototype_ `void RegisterActorWorldPartitionContentBundleToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Syncs the actor's content bundle display name into FWorldPartitionContentBundleColumn when it may have changed.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorWorldPartitionDataLayerQueries.h` (Private)


#### class `UActorWorldPartitionDataLayerDataStorageFactory`  
`class UActorWorldPartitionDataLayerDataStorageFactory : public UEditorDataStorageFactory`  
_L15-34_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Registers queries that keep FWorldPartitionDataLayerColumn in sync with the actor's data layer assignments. Read-only — no write-back to world.
- L20 _public prototype_ `~UActorWorldPartitionDataLayerDataStorageFactory() override = default;`
- L22 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L28 _private prototype_ `void RegisterActorAddWorldPartitionDataLayerColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds FWorldPartitionDataLayerColumn to actor rows in WP worlds that do not already have the column.
- L33 _private prototype_ `void RegisterActorWorldPartitionDataLayerToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Syncs the actor's data layer names into FWorldPartitionDataLayerColumn when they may have changed.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/Compatibility/TedsActorWorldPartitionSubPackageQueries.h` (Private)


#### class `UActorWorldPartitionSubPackageDataStorageFactory`  
`class UActorWorldPartitionSubPackageDataStorageFactory : public UEditorDataStorageFactory`  
_L16-36_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Registers queries that keep FWorldPartitionSubPackageColumn in sync with the actor's world asset package name. Read-only — no write-back to world. Only added to Level Instance actors (those implementing ILevelInstanceInterface).
- L21 _public prototype_ `~UActorWorldPartitionSubPackageDataStorageFactory() override = default;`
- L23 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L30 _private prototype_ `void RegisterActorAddWorldPartitionSubPackageColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds FWorldPartitionSubPackageColumn to actor rows for Level Instance actors that do not already have the column.
- L35 _private prototype_ `void RegisterActorWorldPartitionSubPackageToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Syncs the actor's world asset package name into FWorldPartitionSubPackageColumn when it may have changed.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/LevelInstanceFactory.h` (Private)


#### class `UTedsLevelInstanceFactory`  
`class UTedsLevelInstanceFactory : public UEditorDataStorageFactory`  
_L15-29_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `virtual ~UTedsLevelInstanceFactory() override = default;`
- L20 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& InDataStorage) override;`
- L21 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L22 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _private prototype_ `void LevelInstanceEditModeChanged(ILevelInstanceInterface* LevelInstanceInterface, ILevelInstanceEditorModule::ELevelInstanceEditMode LevelInstanceEditMode) const;`
- L27 _private member_ `UE::Editor::DataStorage::ICoreProvider* DataStorage;`
- L28 _private member_ `UE::Editor::DataStorage::ICompatibilityProvider* CompatibilityProvider;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/TedsActorCompatibilityFactory.h` (Private)


#### class `UTedsActorCompatibilityFactory`  
`class UTedsActorCompatibilityFactory : public UEditorDataStorageFactory`  
_L13-37_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L19 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L22 _private prototype_ `void RegisterTable(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L24 _private prototype_ `void OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues InitializationValues);`
- L25 _private prototype_ `void OnPreWorldFinishDestroy(UWorld* World);`
- L26 _private prototype_ `void OnActorDestroyed(AActor* Actor);`
- L27 _private prototype_ `void OnActorOuterChanged(AActor* Actor, UObject* Outer);`
- L29 _private member_ `UE::Editor::DataStorage::ICompatibilityProvider* DataStorageCompatibility{nullptr};`
- L31 _private member_ `UE::Editor::DataStorage::TableHandle StandardActorTable{ UE::Editor::DataStorage::InvalidTableHandle };`
- L33 _private member_ `TMap<UWorld*, FDelegateHandle> ActorDestroyedDelegateHandles;`
- L34 _private member_ `FDelegateHandle PostWorldInitializationDelegateHandle;`
- L35 _private member_ `FDelegateHandle PreWorldFinishDestroyDelegateHandle;`
- L36 _private member_ `FDelegateHandle ActorOuterChangedDelegateHandle;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Private/TedsActorCompatibilityModule.h` (Private)


#### class `UE::Editor::DataStorage::FTedsActorCompatibilityModule`  
`class FTedsActorCompatibilityModule : public IModuleInterface`  
_L9-19_
- inherits: `IModuleInterface`
- L14 _public prototype_ `FTedsActorCompatibilityModule() = default;`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Public/Columns/TedsActorComponentCompatibilityColumns.h` (Public)


#### struct `FActorComponentTypeTag`  
`struct FActorComponentTypeTag : public FEditorDataStorageTag`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageTag`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Public/Columns/TedsActorMobilityColumns.h` (Public)


#### struct `FTedsActorMobilityColumn`  
`struct FTedsActorMobilityColumn final : public FEditorDataStorageColumn`  
_L14-20_
- reflection: `USTRUCT(meta = (DisplayName = "Mobility"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the mobility of an actor's scene component.
- L19 _public member_ `TEnumAsByte<EComponentMobility::Type> Mobility = EComponentMobility::Movable;` — `UPROPERTY(meta = (Sortable))`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Public/Columns/TedsActorSocketColumns.h` (Public)


#### struct `FTedsActorSocketColumn`  
`struct FTedsActorSocketColumn final : public FEditorDataStorageColumn`  
_L13-19_
- reflection: `USTRUCT(meta = (DisplayName = "Socket"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the name of the socket the actor is attached to.
- L18 _public member_ `FName AttachedSocket = NAME_None;` — `UPROPERTY(meta = (Sortable, Searchable))`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Public/Columns/TedsActorUncachedLightsColumns.h` (Public)


#### struct `FTedsActorUncachedLightsTag`  
`struct FTedsActorUncachedLightsTag final : public FEditorDataStorageTag`  
_L14-17_
- reflection: `USTRUCT(meta = (DisplayName = "Uncached Lights"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag identifying actor rows that should be evaluated for uncached static lighting interactions in a widget. Added when an actor has Static or Stationary mobility, removed when Movable.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Public/Columns/TedsActorWorldPartitionColumns.h` (Public)


#### struct `FWorldPartitionDataLayerColumn`  
`struct FWorldPartitionDataLayerColumn final : public FEditorDataStorageColumn`  
_L14-20_
- reflection: `USTRUCT(meta = (DisplayName = "World Partition Data Layer"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the World Partition data layer names for an actor. Only added to rows for actors in worlds with World Partition enabled.
- L19 _public member_ `FString DataLayers;` — `UPROPERTY(meta = (Sortable, Searchable))`

#### struct `FWorldPartitionContentBundleColumn`  
`struct FWorldPartitionContentBundleColumn final : public FEditorDataStorageColumn`  
_L27-33_
- reflection: `USTRUCT(meta = (DisplayName = "World Partition Content Bundle"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the World Partition content bundle display name for an actor. Only added to rows for actors in worlds with content bundles enabled.
- L32 _public member_ `FString ContentBundle;` — `UPROPERTY(meta = (Sortable, Searchable))`

#### struct `FWorldPartitionSubPackageColumn`  
`struct FWorldPartitionSubPackageColumn final : public FEditorDataStorageColumn`  
_L40-46_
- reflection: `USTRUCT(meta = (DisplayName = "World Partition Sub Package"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that stores the World Asset Package name for Level Instance actors. Only added to rows for actors that implement ILevelInstanceInterface.
- L45 _public member_ `FString SubPackage;` — `UPROPERTY(meta = (Sortable, Searchable))`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsActorCompatibility/Public/Columns/TedsLevelInstanceColumns.h` (Public)


#### struct `FLevelInstanceEditingColumn`  
`struct FLevelInstanceEditingColumn final : public FEditorDataStorageColumn`  
_L13-18_
- reflection: `USTRUCT(meta = (DisplayName = "Editing Level Instance"))`
- inherits: `FEditorDataStorageColumn`
- desc: Tag to identify a row with an LevelInstance actor that is being edited.
- L17 _public member_ `ILevelInstanceEditorModule::ELevelInstanceEditMode EditMode;`

#### struct `FLevelInstanceTag`  
`struct FLevelInstanceTag final : public FEditorDataStorageTag`  
_L24-27_
- reflection: `USTRUCT(meta = (DisplayName = "Level Instance"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag set on a row whose underlying object is an ILevelInstanceInterface

#### struct `FInLevelInstanceTag`  
`struct FInLevelInstanceTag final : public FEditorDataStorageTag`  
_L33-36_
- reflection: `USTRUCT(meta = (DisplayName = "In Level Instance"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag set on a row that lives inside a level instance.
