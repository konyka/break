# Plugins / DirectMeshControl

- module root: `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl`
- headers: 8; symbols: 114
- symbol kinds: class=11, function=6, macro=3, member=36, namespace=8, prototype=47, struct=3
- PrivateDependencyModuleNames: ComputeFramework, Core, CoreUObject, DeveloperSettings, DynamicMesh, EditorInteractiveToolsFramework, EditorSubsystem, Engine, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshModelingToolsEditorOnly, ModelingToolsEditorMode, OptimusCore, Persona, RenderCore, SkeletalMeshDescription, SkeletalMeshModelingTools, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: ModelingComponents

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Private/DMCMeshGenerationSubsystem.h` (Private)


#### class `UDMCMeshGenerationManager`  
`class UDMCMeshGenerationManager : public UObject`  
_L26-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L32 _public prototype_ `virtual void Shutdown();` — Clears all cached sub-mesh entries, releasing references to generated assets.
- L41 _public prototype_ `const FGroupSubMeshes& GetSubMeshes(USkeletalMesh* InSkeletalMesh, const UE::Geometry::FDynamicMesh3* Mesh, const FName LayerName);` — Returns the cached FGroupSubMeshes for InSkeletalMesh / LayerName, rebuilding the entry when the DDC hash indicates the source data has changed. @param InSkeletalMesh  Source skeletal mesh. @param Mesh            Current dynamic mesh representation used to detect changes and rebuild. @param LayerName       Triangle label layer that encodes polygroup IDs. @return Reference to the up-to-date cached FGroupSubMeshes.
- L46 _protected member_ `TSet<FSubSkeletalMeshData> SubSkeletalMeshes;` — `UPROPERTY()` — The set of cached entries keyed by (SkeletalMesh, LayerName).

#### class `UDMCMeshGenerationSubsystem`  
`class UDMCMeshGenerationSubsystem : public UEditorSubsystem`  
_L54-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L60 _public prototype_ `static UDMCMeshGenerationSubsystem* Get();` — Returns the active UDMCMeshGenerationSubsystem instance, or nullptr if the engine is shutting down.
- L66 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Creates the UDMCMeshGenerationManager and binds the engine-exit and pre-exit shutdown callbacks. @param Collection  Subsystem collection (passed to the parent implementation).
- L69 _public prototype_ `virtual void Deinitialize() override;` — Removes bound shutdown callbacks, calls Shutdown() on the manager, and nulls the @c GenerationManager pointer.
- L73 _public member_ `TObjectPtr<UDMCMeshGenerationManager> GenerationManager = nullptr;` — `UPROPERTY()` — The owned mesh generation manager. Accessed via Get()->GenerationManager.
- L77 _protected prototype_ `virtual void OnShutdown();` — Sets bIsShuttingDown to true so that subsequent Get() calls return nullptr.
- L81 _private member_ `static bool bIsShuttingDown;` — Static flag set to true during engine shutdown to guard Get() against use-after-destroy.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DIRECTMESHCONTROL_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Private/OptimusDirectMeshControlComponentSource.h` (Private)


#### class `UOptimusDirectMeshControlComponentSource`  
`class UOptimusDirectMeshControlComponentSource : public UOptimusComponentSource`  
_L11-34_
- reflection: `UCLASS()`
- inherits: `UOptimusComponentSource`
- L23 _public prototype_ `virtual FText GetDisplayName() const override;` — UOptimusComponentSource implementations
- L24 _public prototype_ `virtual FName GetBindingName() const override;`
- L25 _public prototype_ `virtual TSubclassOf<UActorComponent> GetComponentClass() const override;`
- L26 _public prototype_ `virtual TArray<FName> GetExecutionDomains() const override;`
- L27 _public prototype_ `virtual int32 GetLodIndex(const UActorComponent* InComponent) const override;`
- L28 _public prototype_ `virtual uint32 GetDefaultNumInvocations(const UActorComponent* InComponent, int32 InLod) const override;`
- L29 _public prototype_ `virtual bool GetComponentElementCountsForExecutionDomain( FName InDomainName, const UActorComponent* InComponent, int32 InLodIndex, TArray<int32>& OutInvocationElementCounts) const override;`

#### struct `UOptimusDirectMeshControlComponentSource::Domains`  
`struct Domains`  
_L15-20_
- L17 _public member_ `static FName Vertex;`
- L18 _public member_ `static FName Triangle;`
- L19 _public member_ `static FName DuplicateVertex;`

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Public/DirectMeshControlCommands.h` (Public)


#### class `FDirectMeshControlCommands`  
`class FDirectMeshControlCommands : public TCommands<FDirectMeshControlCommands>`  
_L11-24_
- inherits: `TCommands<FDirectMeshControlCommands>`
- desc: FDirectMeshControlCommands holds the registered UI commands for the Direct Mesh Control plugin.
- L14 _public prototype_ `FDirectMeshControlCommands();`
- L17 _public member_ `TSharedPtr<FUICommandInfo> BeginDirectMeshControlTools;` — Global palette command.
- L20 _public member_ `TSharedPtr<FUICommandInfo> BeginDirectMeshPolygroupTool;` — Command that activates the "DMC Polygroups" tool for generating bone-based polygroups.
- L23 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands.

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Public/DirectMeshControlComponent.h` (Public)


#### class `UDirectMeshControlComponent`  
`class UDirectMeshControlComponent : public USkeletalMeshComponent`  
_L17-23_
- reflection: `UCLASS(transient)`
- inherits: `USkeletalMeshComponent`
- desc: UDirectMeshControlComponent is a transient skeletal mesh component that bypasses normal bone transform processing and applies mesh deformers directly. Used by the DMC tools to render per-polygroup visualization sub-meshes. Bone transforms are skipped so that the deformer drives the geometry entirely, enabling the per-polygroup overlay without interfering with the source skeleton.
- L22 _private prototype_ `virtual void SendRenderDynamicData_Concurrent() override;` — UPrimitiveComponent override.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DIRECTMESHCONTROL_API`

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Public/DirectMeshControlModule.h` (Public)


#### class `FDirectMeshControlModule`  
`class FDirectMeshControlModule : public IModuleInterface, public ISkeletalMeshModelingModeToolExtension`  
_L18-31_
- inherits: `IModuleInterface,ISkeletalMeshModelingModeToolExtension`
- desc: FDirectMeshControlModule is the main editor module for the Direct Mesh Control plugin.
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `virtual FText GetExtensionName() override;` — IModelingModeToolExtension implementation
- L28 _public prototype_ `virtual FText GetToolSectionName() override;`
- L29 _public prototype_ `virtual bool GetExtensionExtendedInfo(FModelingModeExtensionExtendedInfo& InfoOut) override;`
- L30 _public prototype_ `virtual void GetExtensionTools(const FExtensionToolQueryInfo& InQueryInfo, TArray<FExtensionToolDescription>& OutTools) override;`

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Public/DirectMeshControlStyle.h` (Public)


#### class `FDirectMeshControlStyle`  
`class FDirectMeshControlStyle`  
_L14-32_
- L18 _public prototype_ `static void Initialize();` — Creates and registers the DMC Slate style set.
- L21 _public prototype_ `static void Shutdown();` — Unregisters and resets the DMC Slate style set.
- L24 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();` — Returns the shared DMC Slate style pointer.
- L27 _public prototype_ `static FName GetStyleSetName();` — Returns the registered name of the DMC style set.
- L31 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;` — The shared FSlateStyleSet instance owned by this class.

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Public/DirectMeshControlUtilities.h` (Public)


#### struct `FGroupSubMeshes`  
`struct FGroupSubMeshes`  
_L29-59_
- reflection: `USTRUCT()`
- L39 _public prototype_ `void Rebuild(USkeletalMesh* InSkeletalMesh, const UE::Geometry::FDynamicMesh3* Mesh, const FName LayerName);` — Splits the input skeletal mesh into one skeletal mesh per polygroup @param InSkeletalMesh  Source skeletal mesh supplying the skeleton. @param Mesh            Dynamic mesh whose triangle label layer is read. @param LayerName       Name of the triangle label layer that stores polygroup IDs.
- L42 _public prototype_ `void Reset();` — Marks all sub-meshes as garbage and clears the mesh and index-map arrays.
- L45 _public prototype_ `const TArray<TObjectPtr<USkeletalMesh>>& GetSubSkeletalMeshes() const;` — Returns the array of generated sub skeletal meshes.
- L48 _public prototype_ `const TMap<int32, int32>& GetGroupIdToSubMesh() const;` — Returns the map from polygroup ID to index into GetSubSkeletalMeshes().
- L54 _private member_ `TArray<TObjectPtr<USkeletalMesh>> SubSkeletalMeshes;` — `UPROPERTY()` — Generated sub skeletal meshes, one entry per unique polygroup in the source layer.
- L58 _private member_ `TMap<int32, int32> GroupIdToSubMesh;` — `UPROPERTY()` — Maps each polygroup ID to the corresponding index in SubSkeletalMeshes.

#### struct `FSubSkeletalMeshData`  
`struct FSubSkeletalMeshData`  
_L66-109_
- reflection: `USTRUCT()`
- L71 _public prototype_ `FSubSkeletalMeshData() = default;` — Default constructor (produces an empty, invalid entry).
- L78 _public function_ `FSubSkeletalMeshData(USkeletalMesh* InSkeletalMesh, const FName InLayerName) : SkeletalMesh(InSkeletalMesh) , LayerName(InLayerName)` — Constructs an entry for the given mesh and layer without yet computing sub-meshes or a DDC hash. @param InSkeletalMesh  Source skeletal mesh to track. @param InLayerName     Triangle label layer name to track.
- L85 _public member_ `TSoftObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY()` — Soft pointer to the source skeletal mesh.
- L89 _public member_ `FName LayerName = NAME_None;` — `UPROPERTY()` — Name of the triangle label layer this entry was built from.
- L93 _public member_ `uint32 Hash = 0;` — `UPROPERTY()` — DDC hash of the source mesh data; used to detect stale cache entries.
- L97 _public member_ `FGroupSubMeshes GroupSubMeshes;` — `UPROPERTY()` — The generated per-polygroup sub-meshes for this (mesh, layer) pair.
- L105 _public function_ `bool operator ==(const FSubSkeletalMeshData& Other) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DIRECTMESHCONTROL_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)
- L100 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FSubSkeletalMeshData& Data)` — Hash computation so that FSubSkeletalMeshData can be stored.
- L116 _namespace_ `namespace UE`
- L116 _namespace_ `namespace DMC` (scope `UE`)
- L125 _prototype_ `const FGroupSubMeshes& GetSubMeshes(USkeletalMesh* InSkeletalMesh, const Geometry::FDynamicMesh3* Mesh, const FName LayerName);` (scope `UE::DMC`) — Fetches or builds the FGroupSubMeshes for the given (mesh, layer) pair. @param InSkeletalMesh  Source skeletal mesh. @param Mesh            Dynamic mesh representation used for splitting. @param LayerName       Triangle label layer that encodes polygroup IDs. @return Reference to the cached (or freshly built) group sub-meshes.
- L128 _prototype_ `const FName& GetSubToSourceAttrName();` (scope `UE::DMC`) — Returns the vertex attribute name used to map sub-mesh vertices back to the source mesh.
- L131 _prototype_ `const FName& GetColorVarName();` (scope `UE::DMC`) — Returns the Optimus deformer variable name that controls the overlay color.
- L134 _prototype_ `UMaterial* GetMaterial();` (scope `UE::DMC`) — Lazy-loads and returns the DMC material or nullptr on failure.
- L137 _prototype_ `UOptimusDeformer* GetDeformer();` (scope `UE::DMC`) — Lazy-loads and returns the DMC deformer or nullptr on failure.

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControl/Public/Tools/DirectMeshPolygroupTool.h` (Public)


#### class `UDirectMeshPolygroupToolBuilder`  
`class UDirectMeshPolygroupToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L28-48_
- reflection: `UCLASS()`
- inherits: `USingleTargetWithSelectionToolBuilder`
- desc: UDirectMeshPolygroupToolBuilder builds a UDirectMeshPolygroupTool instance for the given scene state.
- L37 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState & SceneState) const override;` — Creates and returns a new UDirectMeshPolygroupTool instance for the provided scene state. @param SceneState  Current tool-manager scene state. @return Newly created tool instance.
- L40 _public function_ `virtual bool RequiresInputSelection() const override` — Returns false, the polygroup tool does not require an active selection to launch.
- L47 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — Returns true when the scene state contains exactly one non-volume skeletal mesh component. @param SceneState  Current tool-manager scene state. @return Whether the tool can be built for the given selection.

#### class `UDirectMeshPolygroupToolProperties`  
`class UDirectMeshPolygroupToolProperties : public UInteractiveToolPropertySet`  
_L55-100_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L63 _public member_ `float QuadAdjacencyWeight = 1.0;` — `UPROPERTY(EditAnywhere, Category = Quads, meta = (UIMin = 0, UIMax = 5, EditCondition = "bTryUsingQuads == true"))` — Bias for Quads that are adjacent to already-discovered Quads. Set to 0 to disable.
- L67 _public member_ `float QuadMetricClamp = 1.0;` — `UPROPERTY(EditAnywhere, Category = Quads, meta = (AdvancedDisplay, UIMin = 0, UIMax = 1, EditCondition = "bTryUsingQuads == true"))` — Set to values below 1 to ignore less-likely triangle pairings
- L71 _public member_ `int QuadSearchRounds = 1;` — `UPROPERTY(EditAnywhere, Category = Quads, meta = (AdvancedDisplay, UIMin = 1, UIMax = 5, EditCondition = "bTryUsingQuads == true"))` — Iteratively repeat quad-searching in uncertain areas, to try to slightly improve results
- L75 _public member_ `bool bRespectUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Quads, meta = (EditCondition = "bTryUsingQuads == true"))` — If true, polygroup borders will not cross existing UV seams
- L79 _public member_ `bool bRespectHardNormals = false;` — `UPROPERTY(EditAnywhere, Category = Quads, meta = (EditCondition = "bTryUsingQuads == true"))` — If true, polygroup borders will not cross existing hard normal seams
- L83 _public member_ `int32 MinGroupSize = 2;` — `UPROPERTY(EditAnywhere, Category = Filtering, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "10000"))` — Minimum number of triangles to include in a group. Any group containing fewer triangles will be merged with an adjacent group (if possible).
- L87 _public member_ `bool bShowGroupColors = true;` — `UPROPERTY(EditAnywhere, Category = Display)` — Display each group with a different auto-generated color
- L91 _public member_ `bool bTryUsingQuads = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If true, quads are used to defined skinned areas first
- L95 _public member_ `TArray<FName> BonesToRemove;` — `UPROPERTY(EditAnywhere, Category = Options)` — Bones to remove from the polygroup computation
- L99 _public member_ `FName LayerName = "dm` — `UPROPERTY(EditAnywhere, Category = Output)` — Name of the output layer

#### class `UDirectMeshPolygroupOperatorFactory`  
`class UDirectMeshPolygroupOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L106-120_
- reflection: `UCLASS()`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Operator factory for the Direct Mesh Polygroup tool.
- L115 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — Creates a new FDirectMeshPolygroupOp operator populated with the current settings from DirectMeshPolygroupTool. @return Unique pointer to the configured operator ready for background execution.
- L119 _public member_ `TObjectPtr<UDirectMeshPolygroupTool> DirectMeshPolygroupTool;` — `UPROPERTY()` — Back pointer to the owning tool, provides settings and mesh data for operator creation.

#### class `UDirectMeshPolygroupTool`  
`class UDirectMeshPolygroupTool : public USingleTargetWithSelectionTool`  
_L126-204_
- reflection: `UCLASS()`
- inherits: `USingleTargetWithSelectionTool`
- desc: UDirectMeshPolygroupTool generates bone-based polygroups on a skeletal mesh asynchronously and commits the result to a named triangle label layer on Accept.
- L131 _public prototype_ `UDirectMeshPolygroupTool();`
- L134 _public prototype_ `virtual void Setup() override;` — Builds the preview mesh, registers properties, and starts the background compute operator.
- L140 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;` — Commits the computed polygroup layer to the skeletal mesh on Accept, or discards the result on Cancel. @param ShutdownType  Whether the tool is being accepted or canceled.
- L146 _public prototype_ `virtual void OnTick(float DeltaTime) override;` — Ticks the background compute operator and refreshes the visualization when a new result is available. @param DeltaTime  Time elapsed since the last tick.
- L149 _public function_ `virtual bool HasCancel() const override` — Returns true, the polygroup tool supports cancellation.
- L152 _public function_ `virtual bool HasAccept() const override` — Returns true, the polygroup tool supports acceptance.
- L155 _public prototype_ `virtual bool CanAccept() const override;` — Returns true when the background operator has produced a valid result that can be committed.
- L161 _public prototype_ `void UpdateOpParameters(FDirectMeshPolygroupOp& DirectMeshPolygroupOp) const;` — Copies the current properties values and bone data into DirectMeshPolygroupOp so that the operator uses up-to-date settings on the next compute pass. @param DirectMeshPolygroupOp  Operator instance to populate.
- L166 _protected prototype_ `void OnSettingsModified();` — Invalidates the preview compute, triggering a new background operator run.
- L170 _protected member_ `TObjectPtr<UDirectMeshPolygroupToolProperties> Properties;` — `UPROPERTY()` — Editable properties displayed in the Details panel.
- L174 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> PreviewCompute = nullptr;` — `UPROPERTY()` — Background compute manager that runs FDirectMeshPolygroupOp asynchronously.
- L178 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry = nullptr;` — `UPROPERTY()` — Geometry used to render polygroup border edges on the preview mesh.
- L182 _protected member_ `TObjectPtr<UPreviewMesh> UnmodifiedAreaPreviewMesh = nullptr;` — `UPROPERTY()` — Preview mesh that renders the non-selected (unmodified) portion of the source mesh when a selection ROI is active.
- L185 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalDynamicMesh;` — Thread-safe copy of the full input dynamic mesh, used as the base for all compute passes.
- L188 _protected member_ `bool bUsingSelection = false;` — true when the tool was launched with an active triangle selection.
- L191 _protected member_ `TSharedPtr<TSet<int32>> SelectionTriangleROI;` — Triangle indices that form the selection ROI; populated only when bUsingSelection is true.
- L194 _protected member_ `TSharedPtr<UE::Geometry::FDynamicSubmesh3, ESPMode::ThreadSafe> OriginalSubmesh;` — Sub-mesh extracted from OriginalDynamicMesh for the selection ROI, populated only when bUsingSelection is true.
- L197 _protected member_ `TSharedPtr<UE::Geometry::FSharedConstDynamicMesh3> ComputeOperatorSharedMesh;` — Shared mesh reference passed to the compute operator, points to the full mesh or the selection sub-mesh depending on bUsingSelection.
- L200 _protected member_ `TArray<int> PolygonEdges;` — Edge indices (relative to ComputeOperatorSharedMesh) that form the detected polygroup boundaries, used for edge visualization.
- L203 _protected prototype_ `void UpdateVisualization();` — Refreshes the polygroup edge overlay and per-group color visualization after a new compute result arrives.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)
