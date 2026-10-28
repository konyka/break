# Plugins / PCGGeometryScriptInterop

- module root: `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop`
- headers: 20; symbols: 315
- symbol kinds: class=33, enum=5, enumerator=16, function=30, macro=1, member=98, namespace=7, prototype=119, struct=4, typedef=1, variable=1
- PrivateDependencyModuleNames: AdvancedPreviewScene, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, ModelingComponents, PCGEditor, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryScriptingCore, ModelingOperators, PCG, Projects, RHI, RenderCore

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Private/Editor/PCGDynamicMeshDataVisualization.h` (Private)


#### class `FPCGDynamicMeshDataVisualization`  
`class FPCGDynamicMeshDataVisualization : public IPCGSpatialDataVisualization`  
_L13-20_
- inherits: `IPCGSpatialDataVisualization`
- L17 _public prototype_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const override;`
- L18 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGAppendMeshesFromPoints.h` (Public)


#### enum `EPCGAppendMeshesFromPointsMode`  
`enum class EPCGAppendMeshesFromPointsMode : uint8`  
_L14-19_
- reflection: `UENUM(Blueprintable)`
- L16 _public enumerator_ `SingleStaticMesh UMETA(DisplayName="SingleMesh", ToolTip="Mesh taken from the node settings")`
- L17 _public enumerator_ `StaticMeshFromAttribute UMETA(DisplayName="MeshFromAttribute", ToolTip="Mesh taken from attributes on the points")`
- L18 _public enumerator_ `DynamicMesh UMETA(ToolTip="Mesh taken from another dynamic mesh")`

#### class `UPCGAppendMeshesFromPointsSettings`  
`class UPCGAppendMeshesFromPointsSettings : public UPCGDynamicMeshBaseSettings`  
_L25-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Append meshes at the points transforms. Mesh can be a single static/skeletal mesh, multiple meshes coming from the points or another dynamic mesh.
- L32 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L33 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L34 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L35 _public prototype_ `virtual void GetStaticTrackedKeys(FPCGSelectionKeyToSettingsMap& OutKeysToSettings, TArray<TObjectPtr<const UPCGGraph>>& OutVisitedGraphs) const override;`
- L36 _public function_ `virtual bool CanDynamicallyTrackKeys() const override`
- L40 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L41 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L42 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L44 _protected prototype_ `virtual EPCGChangeType GetChangeTypeForProperty(const FName& InPropertyName) const override;`
- L50 _public member_ `EPCGAppendMeshesFromPointsMode Mode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")`
- L53 _public member_ `TSoftObjectPtr<UObject> Mesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (EditCondition = "Mode==EPCGAppendMeshesFromPointsMode::SingleStaticMesh", EditConditionHides, PCG_Overridable, PCG_OverrideAliases="StaticMesh", AllowedClasses="/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))`
- L56 _public member_ `FPCGAttributePropertyInputSelector MeshAttribute;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings", meta = (EditCondition = "Mode==EPCGAppendMeshesFromPointsMode::StaticMeshFromAttribute", EditConditionHides, PCG_Overridable))`
- L60 _public member_ `bool bExtractMaterials = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings", meta = (EditCondition = "Mode!=EPCGAppendMeshesFromPointsMode::DynamicMesh", EditConditionHides, PCG_Overridable))` — Allows to extract materials from the static/skeletal mesh and set them in the resulting append.
- L64 _public member_ `EGeometryScriptLODType RequestedLODType = EGeometryScriptLODType::RenderData;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|LODSettings", meta = (EditCondition = "Mode!=EPCGAppendMeshesFromPointsMode::DynamicMesh", EditConditionHides, PCG_Overridable))` — LOD type to use when creating DynamicMesh from specified StaticMesh/SkeletalMesh.
- L67 _public member_ `int32 RequestedLODIndex = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|LODSettings", meta = (EditCondition = "Mode!=EPCGAppendMeshesFromPointsMode::DynamicMesh", EditConditionHides, PCG_Overridable))`
- L70 _public member_ `bool bSynchronousLoad = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Debug", meta = (EditCondition = "Mode!=EPCGAppendMeshesFromPointsMode::DynamicMesh", EditConditionHides))`
- L73 _public member_ `TSoftObjectPtr<UStaticMesh> StaticMesh;` — `UE_DEPRECATED(5.8, "Use Mesh property")`

#### struct `FPCGAppendMeshesFromPointsContext`  
`struct FPCGAppendMeshesFromPointsContext : public FPCGContext, public IPCGAsyncLoadingContext`  
_L76-80_
- inherits: `FPCGContext,IPCGAsyncLoadingContext`
- L78 _public member_ `bool bPrepareDataSucceeded = false;`
- L79 _public member_ `TMap<FSoftObjectPath, TArray<int32>> MeshToPointIndicesMapping;`

#### class `FPCGAppendMeshesFromPointsElement`  
`class FPCGAppendMeshesFromPointsElement : public IPCGDynamicMeshBaseElement`  
_L82-91_
- inherits: `IPCGDynamicMeshBaseElement`
- L85 _public prototype_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override;`
- L87 _protected prototype_ `virtual FPCGContext* CreateContext() override;`
- L88 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* InContext) const override;`
- L89 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L90 _protected function_ `virtual bool SupportsBasePointDataInputs(FPCGContext* InContext) const override`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGBooleanOperation.h` (Public)


#### enum `EPCGBooleanOperationTagInheritanceMode`  
`enum class EPCGBooleanOperationTagInheritanceMode : uint8`  
_L12-17_
- reflection: `UENUM(Blueprintable)`
- L14 _public enumerator_ `Both`
- L15 _public enumerator_ `A`
- L16 _public enumerator_ `B`

#### enum `EPCGBooleanOperationMode`  
`enum class EPCGBooleanOperationMode : uint8`  
_L20-25_
- reflection: `UENUM(Blueprintable)`
- L22 _public enumerator_ `EachAWithEachB UMETA(DisplayName="Each A With Each B", Tooltip="Each input in A is boolean'd with its associated input in B (A1 with B1, A2 with B2, etc...). Produces N outputs.")`
- L23 _public enumerator_ `EachAWithEachBSequentially UMETA(DisplayName="Each A With Each B Sequentially", Tooltip="Each input in A is boolean'd with every input in B sequentially. (A1 with B1 then with B2, A2 with B1 then B2, etc...). Produces N outputs.")`
- L24 _public enumerator_ `EachAWithEveryB UMETA(DisplayName="Each A With Every B", Tooltip="Each input in A is boolean'd with input in B individually (Cartesian product: A1 with B1, A1 with B2, A2 with B1, A2 with B2, etc...). Produces N * M outputs.")`

#### class `UPCGBooleanOperationSettings`  
`class UPCGBooleanOperationSettings : public UPCGDynamicMeshBaseSettings`  
_L31-60_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Do a boolean operation between dynamic meshes.
- L38 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L39 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L40 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L44 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L45 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L50 _public member_ `EGeometryScriptBooleanOperation BooleanOperation = EGeometryScriptBooleanOperation::Intersection;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))`
- L53 _public member_ `FGeometryScriptMeshBooleanOptions BooleanOperationOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))`
- L56 _public member_ `EPCGBooleanOperationTagInheritanceMode TagInheritanceMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))`
- L59 _public member_ `EPCGBooleanOperationMode Mode = EPCGBooleanOperationMode::EachAWithEachB;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))`

#### class `FPCGBooleanOperationElement`  
`class FPCGBooleanOperationElement : public IPCGDynamicMeshBaseElement`  
_L62-66_
- inherits: `IPCGDynamicMeshBaseElement`
- L65 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGCreateEmptyDynamicMesh.h` (Public)


#### class `UPCGCreateEmptyDynamicMeshSettings`  
`class UPCGCreateEmptyDynamicMeshSettings : public UPCGDynamicMeshBaseSettings`  
_L13-30_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Create an empty dynamic mesh data.
- L20 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L21 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L22 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L27 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L28 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `FPCGCreateEmptyDynamicMeshElement`  
`class FPCGCreateEmptyDynamicMeshElement : public IPCGDynamicMeshBaseElement`  
_L32-36_
- inherits: `IPCGDynamicMeshBaseElement`
- L35 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGDynamicMeshBaseElement.h` (Public)


#### class `UPCGDynamicMeshBaseSettings`  
`class UPCGDynamicMeshBaseSettings : public UPCGSettings`  
_L16-30_
- reflection: `UCLASS(Abstract, MinimalAPI, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Base class for Dynamic Mesh nodes
- L23 _public function_ `virtual EPCGSettingsType GetType() const override`
- L27 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L28 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`

#### class `IPCGDynamicMeshBaseElement`  
`class IPCGDynamicMeshBaseElement : public IPCGElement`  
_L35-44_
- inherits: `IPCGElement`
- desc: Base class for Dynamic Mesh elements
- L39 _protected function_ `virtual bool IsCacheable(const UPCGSettings*) const override` — All dyn mesh elements are not cacheable to benefit from stealing data.
- L40 _protected function_ `virtual bool ShouldVerifyIfOutputsAreUsedMultipleTimes(const UPCGSettings*) const override`
- L43 _public prototype_ `static UPCGDynamicMeshData* CopyOrSteal(const FPCGTaggedData& InTaggedData, FPCGContext* InContext);`

#### class `IPCGDynamicMeshBaseElementWithCustomContext`  
`template <typename ContextType> requires std::is_base_of_v<FPCGContext, ContextType> class IPCGDynamicMeshBaseElementWithCustomContext : public IPCGDynamicMeshBaseElement`  
_L47-51_
- inherits: `IPCGDynamicMeshBaseElement`
- L50 _protected function_ `virtual FPCGContext* CreateContext() override`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGDynamicMeshTransform.h` (Public)


#### class `UPCGDynamicMeshTransformSettings`  
`class UPCGDynamicMeshTransformSettings : public UPCGDynamicMeshBaseSettings`  
_L13-32_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Apply a transform to all dynamic meshes.
- L20 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L21 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L22 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L31 _public member_ `FTransform Transform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings", meta = (PCG_Overridable))`

#### class `FPCGDynamicMeshTransformElement`  
`class FPCGDynamicMeshTransformElement : public IPCGDynamicMeshBaseElement`  
_L34-38_
- inherits: `IPCGDynamicMeshBaseElement`
- L37 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGGeometryBlueprintElement.h` (Public)


#### class `UPCGGeometryBlueprintElement`  
`class UPCGGeometryBlueprintElement : public UPCGBlueprintBaseElement`  
_L19-44_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, hidecategories = (Object))`
- inherits: `UPCGBlueprintBaseElement`
- desc: Subclass of PCG Blueprint Base Element, it comes with pre-configured pins as input and output for Dynamic meshes and force to be non-cacheable. The function CopyOrStealInputData is a helper to either steal (efficient) or copy the input data (less efficient) so work can be done in place on the Dynamic Mesh. More importantly, a user deriving from this class will want to implement ProcessDynamicMesh, the only thing needed to streamline the process and removes all the boilerplate when in a simple input->output case.
- L24 _public prototype_ `UPCGGeometryBlueprintElement();`
- L27 _public function_ `virtual void ExecuteWithContext_Implementation(FPCGContext& InContext, const FPCGDataCollection& Input, FPCGDataCollection& Output)` — `UE_DEPRECATED(5.7, "Use Execute_Implementation instead")`
- L30 _public prototype_ `virtual void Execute_Implementation(const FPCGDataCollection& Input, FPCGDataCollection& Output) override;` — Virtual implementation to streamline the creation of a Geometry Script node processing. Do not override this function or Execute if you want to use the streamlined version.
- L39 _public prototype_ `void ProcessDynamicMesh(UDynamicMesh* InDynMesh, TArray<FString>& OutTags);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "PCG|Execution", meta = (AutoCreateRefTerm = "InTags"))` — Streamlined version of the Execute function, to only process the dynamic meshes. For each input that is a dynamic mesh, we will call this function, and it will create as many output data as there are inputs. @param InDynMesh  - Dynamic mesh to process. Can be used as is and do operation in place. @param OutTags  - Optional tags to add to the output. By default, it will inherit the tags of the input.
- L43 _public prototype_ `UPCGDynamicMeshData* CopyOrStealInputData(const FPCGTaggedData& InTaggedData) const;` — `UFUNCTION(BlueprintCallable, Category = "PCG|DynamicMesh", meta = (HidePin = "Self"))` — Allows to steal the data and work in place if the data is not used elsewhere. If this element is cacheable, it will automatically copy.

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGGetDynamicMeshData.h` (Public)


#### class `UPCGGetDynamicMeshDataSettings`  
`class UPCGGetDynamicMeshDataSettings : public UPCGDataFromActorSettings`  
_L15-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDataFromActorSettings`
- L22 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L23 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L27 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L32 _public function_ `virtual EPCGDataType GetDataFilter() const override`
- L36 _protected function_ `virtual bool DisplayModeSettings() const override`
- L43 _public member_ `FGeometryScriptCopyMeshFromComponentOptions Options;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dynamic Mesh Settings", meta = (PCG_Overridable, ShowOnlyInnerProperties))` — If data is coming from a component, you can impact the options there.

#### Free symbols / members of external scopes

- L46 _namespace_ `namespace PCGGetDynamicMeshData`
- L48 _prototype_ `bool GetDynamicMeshDataFromActor(FPCGContext*, const FPCGGetDataFunctionRegistryParams&, AActor*, FPCGGetDataFunctionRegistryOutput&);` (scope `PCGGetDynamicMeshData`)
- L49 _prototype_ `bool GetDynamicMeshDataFromComponent(FPCGContext*, const FPCGGetDataFunctionRegistryParams&, UActorComponent*, FPCGGetDataFunctionRegistryOutput&);` (scope `PCGGetDynamicMeshData`)

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGGetMaterialsDynamicMesh.h` (Public)


#### class `UPCGGetMaterialsDynamicMeshSettings`  
`class UPCGGetMaterialsDynamicMeshSettings : public UPCGDynamicMeshBaseSettings`  
_L13-29_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Retrieve the array of materials on a dynamic mesh data.
- L20 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L21 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L22 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L27 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`

#### class `FPCGGetMaterialsDynamicMeshElement`  
`class FPCGGetMaterialsDynamicMeshElement : public IPCGDynamicMeshBaseElement`  
_L31-35_
- inherits: `IPCGDynamicMeshBaseElement`
- L34 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGMergeDynamicMeshes.h` (Public)


#### class `UPCGMergeDynamicMeshesSettings`  
`class UPCGMergeDynamicMeshesSettings : public UPCGDynamicMeshBaseSettings`  
_L13-29_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Appends all incoming dynamic meshes to the first dynamic mesh in order.
- L20 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L21 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L22 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L27 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `FPCGMergeDynamicMeshesElement`  
`class FPCGMergeDynamicMeshesElement : public IPCGDynamicMeshBaseElement`  
_L31-35_
- inherits: `IPCGDynamicMeshBaseElement`
- L34 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGMeshSampler.h` (Public)


#### enum `EPCGMeshSamplingMethod`  
`enum class EPCGMeshSamplingMethod : uint8`  
_L32-42_
- reflection: `UENUM(BlueprintType)`
- L35 _public enumerator_ `OnePointPerTriangle` — Sample one point (at the center) of each triangle of the mesh.
- L38 _public enumerator_ `OnePointPerVertex` — Sample one point per vertex on the mesh.
- L41 _public enumerator_ `PoissonSampling` — Use Poisson sampling to sample points on the mesh. Can be expensive and therefore it is not framebound.

#### enum `EPCGColorChannel`  
`enum class EPCGColorChannel`  
_L45-51_
- reflection: `UENUM()`
- L47 _public enumerator_ `Red`
- L48 _public enumerator_ `Green`
- L49 _public enumerator_ `Blue`
- L50 _public enumerator_ `Alpha`

#### class `UPCGMeshSamplerSettings`  
`class UPCGMeshSamplerSettings : public UPCGSettings`  
_L57-182_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Sample points on a mesh.
- L62 _public prototype_ `UPCGMeshSamplerSettings();`
- L65 _public prototype_ `virtual void PostLoad() override;`
- L70 _public function_ `virtual FName GetDefaultNodeName() const override`
- L71 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L72 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L73 _public function_ `virtual EPCGSettingsType GetType() const override`
- L74 _public function_ `virtual bool CanDynamicallyTrackKeys() const override`
- L75 _public prototype_ `virtual void GetStaticTrackedKeys(FPCGSelectionKeyToSettingsMap& OutKeysToSettings, TArray<TObjectPtr<const UPCGGraph>>& OutVisitedGraphs) const override;`
- L77 _public function_ `virtual bool UseSeed() const override`
- L78 _public prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L79 _public prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L82 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L92 _public member_ `bool bExtractMeshFromInput = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — Can provide a list of inputs to sample the meshes from. It can be a list of StaticMeshes/SkeletalMeshes, a list of Actors that have a Scene Component (like a Static Mesh Component), or a list of Scene Components directly. Geometry Script needs to be able to extract a dynamic mesh from this scene component (so won't work for ISMCs for example) and for now will work only with a single scene component. Each entry (either in the same data or separate data) will produce a unique output data.
- L96 _public member_ `TSoftObjectPtr<UObject> Mesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable, PCG_OverrideAliases="StaticMesh", AllowedClasses="/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh", EditCondition = "!bExtractMeshFromInput", EditConditionHides, ShowAfter = "bExtractMeshFromInput"))` — Soft Object Path to the mesh to sample from. Supports Static Meshes and Skeletal Meshes. Will be loaded.
- L100 _public member_ `FPCGAttributePropertyInputSelector InputSource;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (PCG_Overridable, EditCondition = "bExtractMeshFromInput", EditConditionHides, ShowAfter = "bExtractMeshFromInput"))` — Selector to read data from.
- L103 _public member_ `EPCGMeshSamplingMethod SamplingMethod = EPCGMeshSamplingMethod::OnePointPerTriangle;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")`
- L107 _public member_ `bool bUseColorChannelAsDensity = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Color & Density", meta = (PCG_Overridable, InlineEditConditionToggle, PCG_OverrideAliases="bUseRedAsDensity"))` — Will extract the color channel into the density.
- L110 _public member_ `EPCGColorChannel ColorChannelAsDensity = EPCGColorChannel::Red;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Color & Density", meta = (PCG_Overridable, EditCondition="bUseColorChannelAsDensity"))`
- L113 _public member_ `bool bHasDefaultColorOverride = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Color & Density", meta = (InlineEditConditionToggle, PCG_Overridable))`
- L117 _public member_ `FLinearColor DefaultColorOverride = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Color & Density", meta = (PCG_Overridable, EditCondition=bHasDefaultColorOverride))` — When the mesh doesn't have any vertex color, will use this color instead. Otherwise, it will use (0,0,0,0) for "per point" and white for the rest.
- L121 _public member_ `bool bVoxelize = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Voxelize Options", meta = (PCG_Overridable))` — Enable voxelisation as a preparation pass. Can be more expensive given the VoxelSize.
- L125 _public member_ `float VoxelSize = 100.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Voxelize Options", meta = (PCG_Overridable, EditCondition = "bVoxelize"))` — Size of a voxel for the voxelization.
- L129 _public member_ `bool bRemoveHiddenTriangles = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Voxelize Options", meta = (PCG_Overridable, EditCondition = "bVoxelize"))` — Post-processing pass after voxelization to remove hidden triangles.
- L133 _public member_ `EGeometryScriptLODType RequestedLODType = EGeometryScriptLODType::RenderData;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|LODSettings", meta = (PCG_Overridable))` — LOD type to use when creating DynamicMesh from specified StaticMesh/SkeletalMesh.
- L136 _public member_ `int32 RequestedLODIndex = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|LODSettings", meta = (PCG_Overridable))`
- L140 _public member_ `FGeometryScriptMeshPointSamplingOptions SamplingOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Poisson sampling", meta = (PCG_Overridable, EditCondition = "SamplingMethod == EPCGMeshSamplingMethod::PoissonSampling"))` — Poisson Sampling parameters
- L143 _public member_ `FGeometryScriptNonUniformPointSamplingOptions NonUniformSamplingOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Poisson sampling", meta = (PCG_Overridable, EditCondition = "SamplingMethod == EPCGMeshSamplingMethod::PoissonSampling"))`
- L146 _public member_ `bool bExtractUVAsAttribute = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UVs", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex"))`
- L149 _public member_ `FName UVAttributeName = TEXT("UV"` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UVs", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex && bExtractUVAsAttribute", EditConditionHides))`
- L152 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UVs", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex && bExtractUVAsAttribute", EditConditionHides))`
- L155 _public member_ `bool bOutputTriangleIds = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Extra", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex"))`
- L158 _public member_ `FName TriangleIdAttributeName = TEXT("Tri` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Extra", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex && bOutputTriangleIds", EditConditionHides))`
- L161 _public member_ `bool bOutputMaterialInfo = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Extra", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex"))`
- L164 _public member_ `FName MaterialIdAttributeName = TEXT("Mat` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Extra", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex && bOutputMaterialInfo", EditConditionHides))`
- L167 _public member_ `FName MaterialAttributeName = TEXT("Mat` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Extra", meta = (PCG_Overridable, EditCondition = "SamplingMethod != EPCGMeshSamplingMethod::OnePointPerVertex && bOutputMaterialInfo", EditConditionHides))`
- L175 _public member_ `float PointSteepness = 0.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Points", meta=(ClampMin="0", ClampMax="1", PCG_Overridable))` — Each PCG point represents a discretized, volumetric region of world space. The points' Steepness value [0.0 to 1.0] establishes how "hard" or "soft" that volume will be represented. From 0, it will ramp up linearly increasing its influence over the density from the point's center up to two times the bounds. At 1, it will represent a binary box function with the size of the point's bounds.
- L178 _public member_ `bool bSynchronousLoad = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Debug")`
- L181 _public member_ `TSoftObjectPtr<UStaticMesh> StaticMesh;` — `UE_DEPRECATED(5.8, "Use Mesh property")`

#### struct `FPCGMeshSamplerContext`  
`struct FPCGMeshSamplerContext : public FPCGLoadObjectsFromPathContext`  
_L187-240_
- inherits: `FPCGLoadObjectsFromPathContext`
- desc: Extra context to store all the data that need to be kept between multiple executions (time slicing)
- L191 _public prototype_ `FPCGMeshSamplerContext() = default;`
- L192 _public prototype_ `virtual ~FPCGMeshSamplerContext();`
- L195 _public typedef_ `using SetPointDensityFunc = void(*)(const FLinearColor&, FPCGPoint&);`
- L197 _public prototype_ `void SetAttributeValues(int32 UVChannel, int32 TriangleId, const FVector& BarycentricCoord, int64& MetadataEntry, int32 DataIndex);`
- L198 _public prototype_ `void SetPointColorAndDensity(SetPointDensityFunc SetPointDensityFuncPtr, int32 TriangleId, const FVector& BarycentricCoord, FPCGPoint& OutPoint, int32 DataIndex, TOptional<FLinearColor> DefaultColor);`
- L201 _protected prototype_ `virtual void AddExtraStructReferencedObjects(FReferenceCollector& Collector) override;`
- L205 _public member_ `TArray<TObjectPtr<UDynamicMesh>> DynamicMeshes;` — Dynamic meshes. Will be added to root.
- L208 _public member_ `TArray<FGeometryScriptVectorList> Positions;` — Lists extracted from the meshes
- L209 _public member_ `TArray<FGeometryScriptColorList> Colors;`
- L210 _public member_ `TArray<FGeometryScriptVectorList> Normals;`
- L211 _public member_ `TArray<FGeometryScriptIndexList> TriangleIds;`
- L215 _public member_ `TArray<UPCGPointData*> OutPointData;` — `UE_DEPRECATED(5.6, "Use OutputData instead")` — Output point data.
- L217 _public member_ `TArray<UPCGBasePointData*> OutputData;`
- L220 _public member_ `TArray<FPCGMetadataAttribute<FVector2D>*> UVAttributes;` — Optional attributes.
- L221 _public member_ `TArray<FPCGMetadataAttribute<int32>*> TriangleIdAttributes;`
- L222 _public member_ `TArray<FPCGMetadataAttribute<int32>*> MaterialIdAttributes;`
- L223 _public member_ `TArray<FPCGMetadataAttribute<FSoftObjectPath>*> MaterialAttributes;`
- L226 _public member_ `TArray<TArray<UMaterialInterface*>> ComponentMaterialList;` — Material Specific
- L227 _public member_ `TArray<TArray<UMaterialInterface*>> AssetMaterialList;`
- L231 _public member_ `TArray<TFuture<bool>> SamplingFutures;` — For Poisson sampling, we are starting futures that are not framebound Store the futures and synchronisation items in the context
- L232 _public member_ `std::atomic<bool> StopSampling = false;`
- L233 _public member_ `TUniquePtr<FProgressCancel> SamplingProgess;`
- L236 _public member_ `TArray<int32> StartingIndices;` — Starting indices for each different object to sample. If we have 3 meshes of 20 elements (like vertices) each, the array will be [0, 20, 40, 60]
- L239 _public member_ `bool bDataPrepared = false;` — Set to true if prepared data succeeded.

#### class `FPCGMeshSamplerElement`  
`class FPCGMeshSamplerElement : public IPCGElement`  
_L242-253_
- inherits: `IPCGElement`
- L246 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override` — Loading needs to be done on the main thread and accessing objects outside of PCG might not be thread safe, so taking the safe approach
- L249 _protected prototype_ `virtual FPCGContext* CreateContext() override;`
- L250 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* InContext) const override;`
- L251 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L252 _protected function_ `virtual bool SupportsBasePointDataInputs(FPCGContext* InContext) const override`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API PCGGEOMETRYSCRIPTINTEROP_API`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGMeshToDynamicMeshElement.h` (Public)


#### class `UPCGMeshToDynamicMeshSettings`  
`class UPCGMeshToDynamicMeshSettings : public UPCGDynamicMeshBaseSettings`  
_L17-61_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Convert a static/skeletal mesh into a dynamic mesh data.
- L24 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L25 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L26 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L27 _public prototype_ `virtual void GetStaticTrackedKeys(FPCGSelectionKeyToSettingsMap& OutKeysToSettings, TArray<TObjectPtr<const UPCGGraph>>& OutVisitedGraphs) const override;`
- L28 _public function_ `virtual bool CanDynamicallyTrackKeys() const override`
- L32 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L33 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L34 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L39 _public member_ `TSoftObjectPtr<UObject> Mesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable, PCG_OverrideAliases="StaticMesh", AllowedClasses="/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))`
- L43 _public member_ `bool bExtractMaterials = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings", meta = (PCG_Overridable))` — Allows to extract materials from the static/skeletal mesh and store them in the PCG Dynamic Mesh Data.
- L47 _public member_ `TArray<TSoftObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bExtractMaterials", EditConditionHides, PCG_Overridable))` — If it extracts materials, we can specify override materials. It needs to have the same number of material overrides than there are materials on the static mesh.
- L51 _public member_ `EGeometryScriptLODType RequestedLODType = EGeometryScriptLODType::MaxAvailable;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|LODSettings", meta = (PCG_Overridable))` — LOD type to use when creating DynamicMesh from specified StaticMesh/SkeletalMesh.
- L54 _public member_ `int32 RequestedLODIndex = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|LODSettings", meta = (PCG_Overridable))`
- L57 _public member_ `bool bSynchronousLoad = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Debug")`
- L60 _public member_ `TSoftObjectPtr<UStaticMesh> StaticMesh;` — `UE_DEPRECATED(5.8, "Use Mesh property")`

#### struct `FPCGMeshToDynamicMeshContext`  
`struct FPCGMeshToDynamicMeshContext : public FPCGContext, public IPCGAsyncLoadingContext`  
_L63-63_
- inherits: `FPCGContext,IPCGAsyncLoadingContext`

#### class `FPCGMeshToDynamicMeshElement`  
`class FPCGMeshToDynamicMeshElement : public IPCGDynamicMeshBaseElement`  
_L65-73_
- inherits: `IPCGDynamicMeshBaseElement`
- L68 _public prototype_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override;`
- L70 _protected prototype_ `virtual FPCGContext* CreateContext() override;`
- L71 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* Context) const override;`
- L72 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGPrimitiveCrossSection.h` (Public)


#### class `UPCGPrimitiveCrossSectionSettings`  
`class UPCGPrimitiveCrossSectionSettings : public UPCGSettings`  
_L18-83_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Creates spline cross-sections of one more primitives based on vertex features.
- L23 _public prototype_ `UPCGPrimitiveCrossSectionSettings();`
- L27 _public function_ `virtual FName GetDefaultNodeName() const override`
- L28 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L29 _public function_ `virtual FText GetNodeTooltipText() const override`
- L30 _public function_ `virtual EPCGSettingsType GetType() const override`
- L34 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L35 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L36 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L42 _public member_ `FVector SliceDirection = FVector::UpVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Slicing will happen from the minimum vertex along this direction vector (normalized).
- L46 _public member_ `FPCGAttributePropertyOutputSelector ExtrusionVectorAttribute;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — The attribute that will be populated with each cross-section's extrusion vector.
- L50 _public member_ `int32 MinimumCoplanarVertices = 3;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — The minimum required number of vertices that must be co-planar in order to be considered a tier "feature".
- L54 _public member_ `int32 MaxMeshVertexCount = 2048;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, AdvancedDisplay, meta = (PCG_Overridable, EditCondition = "GenerateCrossSectionMode != EPCGGenerateCrossSectionMode::TierSlicing", EditConditionHides))` — A safeguard to prevent finding features on an overly complex mesh.
- L58 _public member_ `bool bEnableTierMerging = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable, InlineEditConditionToggle))` — Cull tiers that are within a specified threshold.
- L62 _public member_ `double TierMergingThreshold = 1.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (ClampMin = "0.01", PCG_Overridable, EditCondition = "bEnableTierMerging"))` — If a tier is within this distance (in cm) of the previous tier, it will be culled.
- L66 _public member_ `bool bEnableMinAreaCulling = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable, InlineEditConditionToggle))` — Cull tiers that have a surface area smaller than a specified threshold.
- L70 _public member_ `double MinAreaCullingThreshold = 100.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable, EditCondition = "bEnableMinAreaCulling"))` — If a tier is smaller in area than this threshold, it will be culled.
- L74 _public member_ `bool bEnableMinHeightCulling = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable, InlineEditConditionToggle))` — Culls tiers that don't meed a minimum height requirement.
- L78 _public member_ `double MinHeightCullingThreshold = 1.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable, EditCondition = "bEnableMinHeightCulling"))` — If a tier is smaller in height than this threshold, it will be culled.
- L82 _public member_ `bool bRemoveRedundantSections = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — If multiple tiers can be combined into a single tier without affecting the contour, remove the redundant one. Note: This will currently cull even if there are other unique tiers in between.

#### class `FPCGPrimitiveCrossSectionElement`  
`class FPCGPrimitiveCrossSectionElement : public IPCGElement`  
_L85-90_
- inherits: `IPCGElement`
- L88 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* Context) const override;`
- L89 _protected function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PCGPrimitiveCrossSection`
- L9 _namespace_ `namespace Constants` (scope `PCGPrimitiveCrossSection`)
- L11 _variable_ `static constexpr double MinTierMergingThreshold = 0.01;` (scope `PCGPrimitiveCrossSection::Constants`)

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGSaveDynamicMeshToAsset.h` (Public)


#### class `UPCGSaveDynamicMeshToAssetSettings`  
`class UPCGSaveDynamicMeshToAssetSettings : public UPCGDynamicMeshBaseSettings`  
_L16-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Saves dynamic mesh data into a static mesh asset.
- L23 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L24 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L29 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L30 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L31 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L36 _public member_ `FPCGAssetExporterParameters ExportParams;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (ShowOnlyInnerProperties, PCG_Overridable))`
- L44 _public member_ `bool bExportMaterialsFromDynamicMesh = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — This option has higher priority than CopyMeshToAssetOptions.ReplaceMaterials. If true, we will replace the materials from the materials stored on the PCG Dynamic Mesh data. Otherwise, we will follow what is set in CopyMeshToAssetOptions.
- L47 _public member_ `FGeometryScriptCopyMeshToAssetOptions CopyMeshToAssetOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))`
- L50 _public member_ `FGeometryScriptMeshWriteLOD MeshWriteLOD;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))`

#### class `FPCGSaveDynamicMeshToAssetElement`  
`class FPCGSaveDynamicMeshToAssetElement : public IPCGElement`  
_L53-59_
- inherits: `IPCGElement`
- L56 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L58 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGSetMaterialsDynamicMesh.h` (Public)


#### class `UPCGSetMaterialsDynamicMeshSettings`  
`class UPCGSetMaterialsDynamicMeshSettings : public UPCGDynamicMeshBaseSettings`  
_L15-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Replace the array of materials on the dynamic mesh data.
- L22 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L23 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L24 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L28 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L33 _public member_ `TArray<TSoftObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings", meta = (PCG_Overridable))`

#### struct `FPCGSetMaterialsDynamicMeshContext`  
`struct FPCGSetMaterialsDynamicMeshContext : public FPCGContext, public IPCGAsyncLoadingContext`  
_L36-36_
- inherits: `FPCGContext,IPCGAsyncLoadingContext`

#### class `FPCGSetMaterialsDynamicMeshElement`  
`class FPCGSetMaterialsDynamicMeshElement : public IPCGDynamicMeshBaseElementWithCustomContext<FPCGSetMaterialsDynamicMeshContext>`  
_L38-46_
- inherits: `IPCGDynamicMeshBaseElementWithCustomContext<FPCGSetMaterialsDynamicMeshContext>`
- L42 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override` — Loading needs to be done on the main thread and accessing objects outside of PCG might not be thread safe, so taking the safe approach
- L44 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* InContext) const override;`
- L45 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGSpawnDynamicMesh.h` (Public)


#### class `UPCGSpawnDynamicMeshSettings`  
`class UPCGSpawnDynamicMeshSettings : public UPCGDynamicMeshBaseSettings`  
_L14-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGDynamicMeshBaseSettings`
- desc: Spawn a dynamic mesh component for each dynamic mesh data in input.
- L21 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L22 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L23 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L27 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L32 _public member_ `TSoftObjectPtr<AActor> TargetActor;` — `UPROPERTY(BlueprintReadWrite, Category = Settings, meta = (PCG_Overridable))`
- L36 _public member_ `TArray<FName> PostProcessFunctionNames;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings)` — Specify a list of functions to be called on the target actor after instances are spawned. Functions need to be parameter-less and with "CallInEditor" flag enabled.

#### class `FPCGSpawnDynamicMeshElement`  
`class FPCGSpawnDynamicMeshElement : public IPCGElement`  
_L39-46_
- inherits: `IPCGElement`
- L42 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext*) const override`
- L43 _public function_ `virtual bool IsCacheable(const UPCGSettings*) const override`
- L45 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGSplineToMesh.h` (Public)


#### class `UPCGSplineToMeshSettings`  
`class UPCGSplineToMeshSettings : public UPCGDynamicMeshBaseSettings`  
_L12-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural), AutoExpandCategories="Settings|Spline, Settings|Mesh")`
- inherits: `UPCGDynamicMeshBaseSettings`
- L19 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L25 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L26 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L34 _public member_ `double ErrorTolerance = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Settings|Spline", meta = (ClampMin = 0.001))` — How far to allow the triangulation boundary can deviate from the spline curve before we add more vertices
- L38 _public member_ `EFlattenCurveMethod FlattenMethod = EFlattenCurveMethod::DoNotFlatten;` — `UPROPERTY(EditAnywhere, Category = "Settings|Spline")` — Whether and how to flatten the curves. If curves are flattened, they can also be offset.
- L42 _public member_ `double Thickness = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Settings|Mesh", meta = (PCG_Overridable, ClampMin = 0.0))` — If > 0, Extrude the triangulation by this amount.
- L45 _public member_ `FVector ExtrusionVector = FVector::ZAxisVector;` — `UPROPERTY(EditAnywhere, Category = "Settings|Mesh", meta = (PCG_Overridable))`
- L48 _public member_ `bool bExtrudeInLocalSpace = true;` — `UPROPERTY(EditAnywhere, Category = "Settings|Mesh")`
- L52 _public member_ `bool bFlipResult = false;` — `UPROPERTY(EditAnywhere, Category = "Settings|Mesh")` — Whether to flip the facing direction of the generated mesh.
- L56 _public member_ `EOffsetOpenCurvesMethod OpenCurves = EOffsetOpenCurvesMethod::TreatAsClosed;` — `UPROPERTY(EditAnywhere, Category = "Settings|Offset", meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten", EditConditionHides))` — How to handle open curves: Either offset them, or treat them as closed curves.
- L60 _public member_ `double CurveOffset = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Settings|Offset", meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten", EditConditionHides))` — How much offset to apply to curves.
- L64 _public member_ `EOffsetClosedCurvesMethod OffsetClosedCurves = EOffsetClosedCurvesMethod::OffsetOuterSide;` — `UPROPERTY(EditAnywhere, Category = "Settings|Offset", meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && CurveOffset != 0", EditConditionHides))` — Whether and how to apply offset to closed curves.
- L68 _public member_ `EOpenCurveEndShapes EndShapes = EOpenCurveEndShapes::Square;` — `UPROPERTY(EditAnywhere, Category = "Settings|Offset", meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && OpenCurves != EOffsetOpenCurvesMethod::TreatAsClosed && CurveOffset != 0", EditConditionHides))` — The shape of the ends of offset curves.
- L72 _public member_ `EOffsetJoinMethod JoinMethod = EOffsetJoinMethod::Square;` — `UPROPERTY(EditAnywhere, Category = "Settings|Offset", meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && CurveOffset != 0", EditConditionHides))` — The shape of joins between segments of an offset curve.
- L76 _public member_ `double MiterLimit = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Settings|Offset", meta = (ClampMin = 0.0, EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && CurveOffset != 0 && JoinMethod == EOffsetJoinMethod::Miter", EditConditionHides))` — How far a miter join can extend before it is replaced by a square join.

#### class `FPCGSplineToMeshElement`  
`class FPCGSplineToMeshElement : public IPCGDynamicMeshBaseElement`  
_L79-83_
- inherits: `IPCGDynamicMeshBaseElement`
- L82 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Elements/PCGStaticMeshToDynamicMeshElement.h` (Public)
_(no declarations extracted)_

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Helpers/PCGGeometryHelpers.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)
- L20 _namespace_ `namespace PCGGeometryHelpers`
- L22 _prototype_ `void GeometryScriptDebugToPCGLog(FPCGContext* Context, const UGeometryScriptDebug* Debug);` (scope `PCGGeometryHelpers`)
- L23 _prototype_ `UE::Conversion::EMeshLODType SafeConversionLODType(const EGeometryScriptLODType LODType);` (scope `PCGGeometryHelpers`)
- L32 _prototype_ `void RemapMaterials(UE::Geometry::FDynamicMesh3& InMesh, const TArray<UMaterialInterface*>& FromMaterials, TArray<TObjectPtr<UMaterialInterface>>& ToMaterials, const UE::Geometry::FMeshIndexMappings* OptionalMappings = nullptr);` (scope `PCGGeometryHelpers`) — Adaptation of UGeometryScriptLibrary_MeshMaterialFunctions::RemapToNewMaterialIDsByMaterial, to work on UE::Geometry::FDynamicMesh3 and with optional mappings. @param InMesh: Mesh to modify @param FromMaterials: Original array of materials for the mesh @param ToMaterials: New array of materials for the mesh. Mutable. If the original material is not in the new array, add it. @param OptionalMappings: Optional mappings if we want to update a subset of the triangles in the mesh.
- L34 _prototype_ `bool ConvertDataToDynMeshes(const UPCGData* InData, FPCGContext* Context, TArray<UDynamicMesh*>& OutMeshes, bool bMergeMeshes, UGeometryScriptDebug* DynamicMeshDebug = nullptr);` (scope `PCGGeometryHelpers`)

### `Plugins/PCGInterops/PCGGeometryScriptInterop/Source/PCGGeometryScriptInterop/Public/Resources/PCGDynamicMeshManagedComponent.h` (Public)


#### class `UPCGDynamicMeshManagedComponent`  
`class UPCGDynamicMeshManagedComponent : public UPCGManagedComponent`  
_L18-38_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UPCGManagedComponent`
- L24 _public function_ `virtual void ResetComponent() override`
- L25 _public function_ `virtual bool SupportsComponentReset() const override`
- L26 _public prototype_ `virtual void MarkAsReused() override;`
- L29 _public prototype_ `UDynamicMeshComponent* GetComponent() const;`
- L30 _public prototype_ `void SetComponent(UDynamicMeshComponent* InComponent);`
- L32 _public function_ `uint64 GetDataUID() const`
- L33 _public function_ `void SetDataUID(uint64 InDataUID)`
- L37 _protected member_ `uint64 DataUID = -1;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace PCGDynamicMeshManagedComponent`
- L42 _prototype_ `UPCGDynamicMeshManagedComponent* GetOrCreateDynamicMeshManagedComponent(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGDynamicMeshData* InMeshData, AActor* TargetActor, TOptional<EPCGEditorDirtyMode> OptionalDirtyModeOverride = TOptional<EPCGEditorDirtyMode>{});` (scope `PCGDynamicMeshManagedComponent`)
