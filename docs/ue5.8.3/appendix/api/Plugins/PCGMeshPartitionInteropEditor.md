# Plugins / PCGMeshPartitionInteropEditor

- module root: `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInteropEditor`
- headers: 4; symbols: 20
- symbol kinds: class=4, delegate=1, function=1, member=1, namespace=2, prototype=11
- PrivateDependencyModuleNames: MeshConversion, MeshConversionEngineTypes, PCGGeometryScriptInterop, PCGMeshPartitionInterop, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, GeometryCore, GeometryFramework, MeshPartition, MeshPartitionEditor, PCG

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInteropEditor/Private/Visualizations/PCGMeshTerrainSectionDataVisualization.h` (Private)


#### class `FPCGMeshTerrainSectionDataVisualization`  
`class FPCGMeshTerrainSectionDataVisualization : public IPCGDataVisualization`  
_L7-14_
- inherits: `IPCGDataVisualization`
- L11 _public function_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const override`
- L12 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInteropEditor/Public/MeshPartitionPCGAdapterComponent.h` (Public)


#### class `UE::MeshPartition::UPCGAdapterComponent`  
`class UPCGAdapterComponent : public MeshPartition::UModifierComponent`  
_L23-35_
- reflection: `UCLASS(meta=(BlueprintSpawnableComponent, DisplayName = "Mesh Partition PCG Adapter Component"))`
- inherits: `MeshPartition::UModifierComponent`
- desc: The PCG Adapter modifier spawns a MeshPartition::UPCGDataComponent on the final processed mesh. The PCGDataComponent contains a cached FDynamicMesh and FDynamicMeshAABBTree which are used for editor and runtime pcg sampling of the built mesh data
- L28 _public prototype_ `UPCGAdapterComponent();`
- L31 _public prototype_ `virtual void PostBuildSectionMesh(AActor* InSection, const MeshPartition::FMeshData& InBuiltMesh) override;`
- L32 _public prototype_ `virtual TArray<FBox> ComputeBounds() const override;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInteropEditor/Public/PCGMeshPartitionInteropEditorModule.h` (Public)


#### class `FPCGMegaMeshInteropEditorModule`  
`class FPCGMegaMeshInteropEditorModule final : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void RegisterPinColors();`
- L18 _private prototype_ `void UnregisterPinColors();`
- L20 _private prototype_ `void RegisterDataVisualizations();`
- L21 _private prototype_ `void UnregisterDataVisualizations();`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGMegaMeshInteropEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGMegaMeshInteropEditor, Log, All);`

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInteropEditor/Public/PCGMeshPartitionInteropEditorSettings.h` (Public)


#### class `UPCGMeshPartitionInteropEditorSettings`  
`class UPCGMeshPartitionInteropEditorSettings : public UObject`  
_L10-18_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta = (DisplayName = "PCG Mesh Partition Interop Editor Settings"))`
- inherits: `UObject`
- L17 _public member_ `FLinearColor MeshTerrainSectionDataPinColor = FLinearColor(0.75f, 0.55f, 0.35f);` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Mesh Terrain Section
