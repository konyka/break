# Plugins / TedsRevisionControl

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsRevisionControl`
- headers: 3; symbols: 44
- symbol kinds: class=3, member=17, namespace=6, prototype=18
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: SourceControlViewport, TedsActorCompatibility
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SourceControl, TypedElementFramework

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsRevisionControl/Private/Processors/RevisionControlProcessors.h` (Private)


#### class `URevisionControlDataStorageFactory`  
`class URevisionControlDataStorageFactory : public UEditorDataStorageFactory`  
_L17-58_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L22 _public prototype_ `~URevisionControlDataStorageFactory() override = default;`
- L24 _public prototype_ `void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L28 _public prototype_ `void UpdateOverlaysForSCCState(UE::Editor::DataStorage::ICoreProvider* DataStorage) const;` — Update the overlays for all SCC rows that contain the Column specified
- L31 _public prototype_ `void UpdateOverlayColors(UE::Editor::DataStorage::ICoreProvider* DataStorage) const;` — Update the color for all actors that currently have an overlay
- L35 _private prototype_ `void RegisterFetchUpdates(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L36 _private prototype_ `void RegisterApplyOverlays(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L37 _private prototype_ `void RegisterRemoveOverlays(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L38 _private prototype_ `void RegisterGeneralQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L40 _private member_ `UE::Editor::DataStorage::QueryHandle MonitorNewPackagesHandle = UE::Editor::DataStorage::InvalidQueryHandle;`
- L41 _private member_ `UE::Editor::DataStorage::QueryHandle FetchUpdates = UE::Editor::DataStorage::InvalidQueryHandle;`
- L42 _private member_ `UE::Editor::DataStorage::QueryHandle StopFetchUpdates = UE::Editor::DataStorage::InvalidQueryHandle;`
- L43 _private member_ `UE::Editor::DataStorage::QueryHandle ApplyOverlaysObjectToSCC = UE::Editor::DataStorage::InvalidQueryHandle;`
- L44 _private member_ `UE::Editor::DataStorage::QueryHandle RemoveOverlays = UE::Editor::DataStorage::InvalidQueryHandle;`
- L45 _private member_ `UE::Editor::DataStorage::QueryHandle UpdateSCCForActors = UE::Editor::DataStorage::InvalidQueryHandle;`
- L46 _private member_ `UE::Editor::DataStorage::QueryHandle SelectionAdded = UE::Editor::DataStorage::InvalidQueryHandle;`
- L47 _private member_ `UE::Editor::DataStorage::QueryHandle SelectionRemoved = UE::Editor::DataStorage::InvalidQueryHandle;`
- L48 _private member_ `UE::Editor::DataStorage::QueryHandle PackageReferenceAdded = UE::Editor::DataStorage::InvalidQueryHandle;`
- L50 _private member_ `UE::Editor::DataStorage::QueryHandle RemoveStatusUpdateEndedTagQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L51 _private member_ `UE::Editor::DataStorage::QueryHandle RemoveStatusUpdateRequiredTagQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L53 _private member_ `UE::Editor::DataStorage::QueryHandle RemoveSccStateDirtyTagQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L56 _private member_ `UE::Editor::DataStorage::QueryHandle UpdateOverlays = UE::Editor::DataStorage::InvalidQueryHandle;` — Query to fetch all rows with overlays

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsRevisionControl/Private/Queries/ObjectPackagePathToColumnQueries.h` (Private)


#### class `UTypedElementUObjectPackagePathFactory`  
`class UTypedElementUObjectPackagePathFactory : public UEditorDataStorageFactory`  
_L16-30_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L21 _public prototype_ `~UTypedElementUObjectPackagePathFactory() override = default;`
- L23 _public prototype_ `void RegisterHierarchies(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L24 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L27 _private prototype_ `void RegisterTryAddPackageRef(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L28 _private member_ `UE::Editor::DataStorage::QueryHandle TryAddPackageRef = UE::Editor::DataStorage::InvalidQueryHandle;`
- L29 _private member_ `UE::Editor::DataStorage::QueryHandle TryReplacePackageRef = UE::Editor::DataStorage::InvalidQueryHandle;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsRevisionControl/Private/TedsRevisionControlModule.h` (Private)


#### class `FTedsRevisionControlModule`  
`class FTedsRevisionControlModule : public IModuleInterface, public FGCObject`  
_L11-34_
- inherits: `IModuleInterface,FGCObject`
- L14 _public prototype_ `~FTedsRevisionControlModule() override = default;`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L29 _public prototype_ `FString GetReferencerName() const override;`
- L32 _private member_ `FDelegateHandle OverlayStatesChangedHandle;`
- L33 _private member_ `FDelegateHandle OverlayColorsChangedHandle;`
