# Plugins / PCGNaniteAssembliesInterop

- module root: `Plugins/Experimental/PCGInterops/PCGNaniteAssembliesInterop/Source/PCGNaniteAssembliesInterop`
- headers: 2; symbols: 27
- symbol kinds: class=3, delegate=1, function=6, member=7, prototype=9, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, NaniteAssemblyEditorUtils, PCG

### `Plugins/Experimental/PCGInterops/PCGNaniteAssembliesInterop/Source/PCGNaniteAssembliesInterop/Private/Elements/PCGNaniteAssemblyStaticMeshBuilder.h` (Private)


#### class `UPCGNaniteAssemblyStaticMeshBuilderSettings`  
`class UPCGNaniteAssemblyStaticMeshBuilderSettings : public UPCGSettings`  
_L17-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: [Experimental] Create a Static Mesh using Nanite assemblies from the input point data. Points are expected to be in local coordinates.
- L24 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L25 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L26 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L27 _public function_ `virtual EPCGSettingsType GetType() const override`
- L31 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L32 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L33 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L38 _public member_ `FPCGAssetExporterParameters ExportParams;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (ShowOnlyInnerProperties, PCG_Overridable))`
- L42 _public member_ `FPCGAttributePropertyInputSelector MeshAttribute;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Attribute for the mesh to spawn for a given point.
- L46 _public member_ `TArray<FPCGAttributePropertyInputSelector> MaterialOverrides;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings)` — Array of attributes for material overrides. 1 Attribute per slot.
- L50 _public member_ `bool bSynchronousLoad = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Debug")` — Meshes/Materials will be synchronously loaded before spawning instead of asynchronously.

#### struct `FPCGNaniteAssemblyStaticMeshBuilderContext`  
`struct FPCGNaniteAssemblyStaticMeshBuilderContext : public FPCGContext, public IPCGAsyncLoadingContext`  
_L53-58_
- inherits: `FPCGContext,IPCGAsyncLoadingContext`
- L55 _public member_ `TArray<TTuple<TSoftObjectPtr<UStaticMesh>, TArray<TSoftObjectPtr<UMaterialInterface>>, TArray<int32>>> Mapping;`
- L56 _public member_ `bool bPartitionDone = false;`
- L57 _public member_ `bool bPrepareValid = false;`

#### class `FPCGNaniteAssemblyStaticMeshBuilderElement`  
`class FPCGNaniteAssemblyStaticMeshBuilderElement : public IPCGElementWithCustomContext<FPCGNaniteAssemblyStaticMeshBuilderContext>`  
_L60-72_
- inherits: `IPCGElementWithCustomContext<FPCGNaniteAssemblyStaticMeshBuilderContext>`
- L63 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* InContext) const override;`
- L64 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L66 _protected function_ `virtual bool SupportsBasePointDataInputs(FPCGContext* InContext) const override`
- L69 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L70 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L71 _public function_ `virtual bool IsCancellable() const override`

### `Plugins/Experimental/PCGInterops/PCGNaniteAssembliesInterop/Source/PCGNaniteAssembliesInterop/Private/PCGNaniteAssembliesInteropModule.h` (Private)


#### class `FPCGNaniteAssembliesInteropModule`  
`class FPCGNaniteAssembliesInteropModule final : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public function_ `virtual bool SupportsDynamicReloading() override`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGNaniteAssembliesInterop, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGNaniteAssembliesInterop, Log, All);`
