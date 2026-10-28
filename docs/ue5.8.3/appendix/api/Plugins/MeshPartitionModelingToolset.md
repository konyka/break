# Plugins / MeshPartitionModelingToolset

- module root: `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset`
- headers: 24; symbols: 695
- symbol kinds: class=66, delegate=1, enum=11, enumerator=37, function=68, macro=17, member=178, namespace=58, prototype=255, struct=1, typedef=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DynamicMesh, Engine, GeometryAlgorithms, GeometryCore, GeometryFramework, HairStrandsCore, ImageCore, InteractiveToolsFramework, MathCore, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsExp, MeshPartitionEditorUI, ModelingComponents, ModelingComponentsEditorOnly, ModelingOperators, ModelingOperatorsEditorOnly, ModelingToolsEditorMode, Projects, Slate, SlateCore, SourceControl, StaticMeshDescription, ToolMenus, TypedElementFramework, TypedElementRuntime, UnrealEd
- PublicDependencyModuleNames: Core, MeshPartition, MeshPartitionEditor

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Private/MeshPartitionModelingToolCommands.h` (Private)


#### class `FMegaMeshModelingToolCommands`  
`class FMegaMeshModelingToolCommands : public TCommands<FMegaMeshModelingToolCommands>`  
_L9-30_
- inherits: `TCommands<FMegaMeshModelingToolCommands>`
- L12 _public prototype_ `FMegaMeshModelingToolCommands();`
- L14 _public member_ `TSharedPtr<FUICommandInfo> MegaMeshToolsTabButton;`
- L15 _public member_ `TSharedPtr<FUICommandInfo> BeginConvertMeshTool;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> BeginSplitMeshTool;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> BeginMergeMeshTool;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> BeginResectionMeshTool;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> BeginStitchMeshTool;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> BeginHeightmapImport;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> BeginHeightSculptTool;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> BeginExpandMeshTool;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> BeginCreateMegaMeshRectangleTool;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> BeginAddModifierTool;`
- L29 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `UE::Geometry::FMegaMeshToolActionCommands`  
`class FMegaMeshToolActionCommands : public TInteractiveToolCommands<FMegaMeshToolActionCommands>`  
_L35-46_
- inherits: `TInteractiveToolCommands<FMegaMeshToolActionCommands>`
- L38 _public prototype_ `FMegaMeshToolActionCommands();`
- L40 _public prototype_ `static void RegisterAllToolActions();`
- L41 _public prototype_ `static void UnregisterAllToolActions();`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Geometry` (scope `UE`)
- L50 _macro_ `#define DECLARE_TOOL_ACTION_COMMANDS(CommandsClassName) \`
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace Geometry` (scope `UE`)
- L60 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMegaMeshHeightSculptToolCommands);` (scope `UE::Geometry`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Private/MeshPartitionModelingToolsStyle.h` (Private)


#### class `FMegaMeshModelingToolsStyle`  
`class FMegaMeshModelingToolsStyle`  
_L9-24_
- L12 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L20 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L23 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Private/MeshPartitionPreviewUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)
- L13 _prototype_ `void CreatePreviewGridLines(const FBox& Box, FIntVector Dims, const FString& LineGroupName, UPreviewGeometry* PreviewGeometry);` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Private/MeshPartitionToolPreviewActor.h` (Private)


#### class `UE::MeshPartition::AToolPreviewMesh`  
`class AToolPreviewMesh : public AActor`  
_L24-47_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `AActor`
- L28 _public prototype_ `AToolPreviewMesh();`
- L30 _public prototype_ `void SetMesh(TSharedRef<const MeshPartition::FMeshData> InMeshData);`
- L31 _public prototype_ `void SetChannelData(const MeshPartition::FSectionChannels& InChannelData);`
- L32 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial);`
- L37 _private member_ `TObjectPtr<MeshPartition::UPreviewMeshComponent> PreviewMeshComponent;` — `UPROPERTY(Transient)`
- L40 _private member_ `TObjectPtr<UTexture> ChannelTexture;` — `UPROPERTY(Transient)`
- L43 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MID;` — `UPROPERTY(Transient)`
- L45 _private member_ `TArray<uint8> ChannelTable;`
- L46 _private member_ `FVector2f ChannelTexcoordDesc;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Private/MeshPartitionToolTargetUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshPartition` (scope `UE`)
- L17 _prototype_ `TArray<int32> AssignMeshTrisToClosestBounds( const UE::Geometry::FDynamicMesh3& Mesh, const TArray<UE::Geometry::FAxisAlignedBox3d>& Bounds, int32 DefaultAssignment = 0);` (scope `UE::MeshPartition`) — Helper method used to split triangles out to sections, via bounding boxes @param DefaultAssignment If no bounds are valid, all triangles will be assigned this value. @return Array mapping triangle IDs to the index of the triangle centroid's closest Bounds

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Private/Sculpting/HeightBrushes.h` (Private)


#### class `UMeshHeightSculptBrushOpProps`  
`class UMeshHeightSculptBrushOpProps : public UMeshSculptBrushOpProps`  
_L17-36_
- reflection: `UCLASS()`
- inherits: `UMeshSculptBrushOpProps`
- L24 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10.", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L28 _public member_ `float Falloff = 0.85f;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L30 _public function_ `virtual float GetStrength() override`
- L31 _public function_ `virtual float GetFalloff() override`
- L32 _public function_ `virtual void SetStrength(float NewStrength)`
- L33 _public function_ `virtual void SetFalloff(float NewFalloff)`
- L35 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `UMeshHeightSculptFlattenBrushOpProps`  
`class UMeshHeightSculptFlattenBrushOpProps : public UMeshHeightSculptBrushOpProps`  
_L39-59_
- reflection: `UCLASS()`
- inherits: `UMeshHeightSculptBrushOpProps`
- L46 _public member_ `bool bFlattenToTarget = false;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta = (DisplayName = "To Target"))` — Whether to flatten to the target plane/sphere (set by the gizmo). Otherwise, flatten based on the stroke start position.
- L50 _public member_ `EPlaneBrushSideMode WhichSide = EPlaneBrushSideMode::BothSides;` — `UPROPERTY(EditAnywhere, Category = HeightBrush)` — Control whether effect of brush should be limited to one side of the plane/sphere.
- L54 _public member_ `float ZGridSnap = 0.f;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta=(ClampMin="0.0", EditCondition="!bFlattenToTarget"))` — Snap the per-stroke flattening plane to global height multiples of this value (if non-zero).
- L58 _public member_ `double SphereRadius = 10000.0;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta=(EditCondition="bFlattenToTarget"))` — Radius of sphere to which to set the height of vertices, if using sphere reference surface.

#### class `UMeshHeightSculptSlopeErodeBrushOpProps`  
`class UMeshHeightSculptSlopeErodeBrushOpProps : public UMeshSculptBrushOpProps`  
_L63-99_
- reflection: `UCLASS()`
- inherits: `UMeshSculptBrushOpProps`
- desc: Erosion (slope) brush properties
- L71 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L75 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply (0.0 - 1.0)
- L79 _public member_ `double SlopeThreshold = 30;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta=(ClampMin=0, ClampMax=89, Units="Degrees"))` — Desired maximum slope angle in degrees
- L83 _public member_ `int32 Iterations = 20;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta=(ClampMin = 1, UIMax = 50))` — Number of times to apply sloping per brush application
- L87 _public member_ `double ErodeStrength = .5;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta = (ClampMin = -1, ClampMax = 1))` — Downward strength of erode. Positive erode strength creates mountain-like ridges; negative erode strength will pull up hills.
- L91 _public member_ `double SmoothingBlend = 0.;` — `UPROPERTY(EditAnywhere, Category = HeightBrush, meta = (ClampMin = 0, ClampMax = 1))` — Amount of smoothing to blend into the brush; a value of 1 will apply only smoothing and no erosion/sloping
- L94 _public function_ `virtual float GetStrength() override`
- L95 _public function_ `virtual void SetStrength(float NewStrength) override`
- L96 _public function_ `virtual float GetFalloff() override`
- L97 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `UHeightSmoothBrushOpProps`  
`class UHeightSmoothBrushOpProps : public UBaseSmoothBrushOpProps`  
_L102-126_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseSmoothBrushOpProps`
- L108 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L112 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply (0.0 - 1.0)
- L115 _public member_ `int32 Iterations = 1;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (ClampMin = 1, UIMax = 50))`
- L119 _public member_ `bool bPreserveUVFlow = false;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush)` — If true, try to preserve the shape of the UV/3D mapping. This will limit Smoothing and Remeshing in some cases.
- L121 _public function_ `virtual float GetStrength() override`
- L122 _public function_ `virtual void SetStrength(float NewStrength) override`
- L123 _public function_ `virtual float GetFalloff() override`
- L124 _public function_ `virtual bool GetPreserveUVFlow() override`
- L125 _public function_ `virtual int32 GetIterations()`

#### class `USecondaryHeightSmoothBrushOpProps`  
`class USecondaryHeightSmoothBrushOpProps : public UBaseSmoothBrushOpProps`  
_L131-155_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseSmoothBrushOpProps`
- L137 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Strength of the Brush
- L141 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L144 _public member_ `int32 Iterations = 1;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush, meta = (ClampMin = 1, UIMax = 50))`
- L148 _public member_ `bool bPreserveUVFlow = false;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush)` — If true, try to preserve the shape of the UV/3D mapping. This will limit Smoothing and Remeshing in some cases.
- L150 _public function_ `virtual float GetStrength() override`
- L151 _public function_ `virtual void SetStrength(float NewStrength) override`
- L152 _public function_ `virtual float GetFalloff() override`
- L153 _public function_ `virtual bool GetPreserveUVFlow() override`
- L154 _public function_ `virtual int32 GetIterations()`

#### class `UE::Geometry::FHeightBrushOpBase`  
`class FHeightBrushOpBase : public FMeshSculptBrushOp`  
_L160-212_
- inherits: `FMeshSculptBrushOp`
- L164 _public prototype_ `FHeightBrushOpBase(UE::MeshPartition::UHeightSculptToolProperties* HeightSculptPropertiesIn);`
- L166 _public function_ `virtual EBrushRegionType GetBrushRegionType() const`
- L173 _public function_ `virtual EStampAlignmentType GetStampAlignmentType() const override`
- L178 _public function_ `virtual bool IgnoreZeroMovements() const`
- L183 _public function_ `virtual bool UseLastStampFrameOnZeroMovement() const override`
- L188 _public function_ `virtual bool SupportsVariableSpacing() const override`
- L193 _public function_ `virtual EReferencePlaneType GetReferencePlaneType() const override`
- L198 _public function_ `virtual void BeginStroke(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& InitialVertices) override`
- L204 _protected prototype_ `bool IsSphereBrush() const;`
- L207 _protected member_ `FFrame3d SphereFrame;` — Used when using sphere reference surface
- L211 _private member_ `TWeakObjectPtr<UE::MeshPartition::UHeightSculptToolProperties> HeightSculptProperties;` — Shared property struct that can be accessed in addition to the brush-specific one

#### class `UE::Geometry::FHeightSculptBrushOp`  
`class FHeightSculptBrushOp : public FHeightBrushOpBase`  
_L214-240_
- inherits: `FHeightBrushOpBase`
- L217 _public function_ `FHeightSculptBrushOp(UE::MeshPartition::UHeightSculptToolProperties* HeightSculptPropertiesIn) : FHeightBrushOpBase(HeightSculptPropertiesIn)`
- L221 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const override`
- L234 _public function_ `virtual bool UsesAlpha() const override`
- L236 _public prototype_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override;`
- L239 _public function_ `static UClass* GetPropertiesClass()`

#### class `UE::Geometry::FHeightSmoothBrushOp`  
`class FHeightSmoothBrushOp : public FHeightBrushOpBase`  
_L242-253_
- inherits: `FHeightBrushOpBase`
- L245 _public function_ `FHeightSmoothBrushOp(UE::MeshPartition::UHeightSculptToolProperties* HeightSculptPropertiesIn) : FHeightBrushOpBase(HeightSculptPropertiesIn)`
- L249 _public prototype_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override;`
- L252 _public prototype_ `static UClass* GetPropertiesClass(bool bPrimaryBrush);`

#### class `UE::Geometry::FHeightFlattenBrushOp`  
`class FHeightFlattenBrushOp : public FHeightBrushOpBase`  
_L255-279_
- inherits: `FHeightBrushOpBase`
- L258 _public function_ `FHeightFlattenBrushOp(UE::MeshPartition::UHeightSculptToolProperties* HeightSculptPropertiesIn) : FHeightBrushOpBase(HeightSculptPropertiesIn)`
- L263 _public prototype_ `virtual EReferencePlaneType GetReferencePlaneType() const override;` — Reference plane is required for the To Target flattening mode
- L265 _public prototype_ `virtual void BeginStroke(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& InitialVertices) override;`
- L268 _public prototype_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override;`
- L271 _public function_ `static UClass* GetPropertiesClass()`
- L275 _private member_ `FFrame3d StrokePlane;` — Used when using plane reference surface
- L278 _private member_ `double StrokeHeight = 0.0;` — Used when using sphere reference surface

#### class `UE::Geometry::FSlopeErodeBrushOp`  
`class FSlopeErodeBrushOp : public FHeightBrushOpBase`  
_L281-293_
- inherits: `FHeightBrushOpBase`
- L284 _public function_ `FSlopeErodeBrushOp(UE::MeshPartition::UHeightSculptToolProperties* HeightSculptPropertiesIn) : FHeightBrushOpBase(HeightSculptPropertiesIn)`
- L289 _public prototype_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override;`
- L292 _public function_ `static UClass* GetPropertiesClass()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)
- L158 _namespace_ `namespace UE`
- L158 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionAttributePaintTool.h` (Public)


#### class `UE::MeshPartition::UAttributePaintToolAddChannelProperties`  
`class UAttributePaintToolAddChannelProperties : public UInteractiveToolPropertySet`  
_L17-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L21 _public prototype_ `void Initialize(MeshPartition::UAttributePaintTool* ParentTool);`
- L25 _public member_ `MeshPartition::FChannelName WeightChannelName;` — `UPROPERTY(EditAnywhere, Category = "Mesh Partition Channels", Meta = (GetOptions = "GetChannelOptions", ModelingQuickSettings=400, DisplayName = "Channel"))` — The target channel to paint.
- L29 _private prototype_ `TArray<FName> GetChannelOptions() const;` — `UFUNCTION()`
- L31 _private member_ `TWeakObjectPtr<MeshPartition::UAttributePaintTool> ParentTool;`

#### class `UE::MeshPartition::UAttributePaintTool`  
`class UAttributePaintTool : public UMeshAttributePaintTool`  
_L35-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshAttributePaintTool`
- L39 _public prototype_ `virtual void Setup() override;`
- L40 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L43 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;` — UDynamicMeshBrushTool
- L46 _protected prototype_ `virtual void ExternalUpdateValues(int32 AttribIndex, const TArray<int32>& VertexIndices, const TArray<float>& NewValues) override;`
- L47 _protected prototype_ `virtual void ApplyStamp(const FBrushStampData& Stamp);`
- L49 _protected prototype_ `virtual FString GetPropertyCacheIdentifier() const override;`
- L51 _protected prototype_ `virtual void InitializeAttributes() override;`
- L55 _private member_ `TObjectPtr<MeshPartition::UAttributePaintToolAddChannelProperties> AddChannelProperties = nullptr;` — `UPROPERTY()`
- L58 _private prototype_ `void AddChannel(FName NewChannel);` — Used by MeshPartition::UAttributePaintToolAddChannelProperties
- L59 _private prototype_ `TArray<FName> GetChannelOptions();`
- L61 _private member_ `TValueWatcher<FName> WeightChannelNameWatcher;`
- L62 _private member_ `bool bFilteredAttributeSourceInitialized = false;`

#### class `UE::MeshPartition::UAttributePaintToolBuilder`  
`class UAttributePaintToolBuilder : public UMeshAttributePaintToolBuilder`  
_L68-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshAttributePaintToolBuilder`
- L73 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionCommonProperties.h` (Public)


#### class `UE::MeshPartition::UCreateProperties`  
`class UCreateProperties : public UInteractiveToolPropertySet`  
_L25-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L32 _public member_ `TObjectPtr<AMeshPartition> ExistingMegaMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category=Add, meta=(EditCondition="NewMegaMeshDefinition == nullptr", TransientToolProperty))`
- L35 _public member_ `TObjectPtr<UMeshPartitionDefinition> NewMegaMeshDefinition = nullptr;` — `UPROPERTY(EditAnywhere, Category=Add, meta=(EditCondition="ExistingMegaMesh == nullptr", TransientToolProperty))`

#### class `UE::MeshPartition::USplitProperties`  
`class USplitProperties : public UInteractiveToolPropertySet`  
_L39-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L50 _public member_ `FIntVector SectionLayout = FIntVector(3, 3, 1);` — `UPROPERTY(EditAnywhere, Category = Split, meta = (DisplayName = "Layout", ClampMin = 1, UIMax = 64, ClampMax = 1024))` — Number of sections in X/Y/Z dimension.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionComponentBackedTarget.h` (Public)


#### class `UE::MeshPartition::UMeshPartitionComponentBackedTarget`  
`class UMeshPartitionComponentBackedTarget : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `UE::MeshPartition::IMeshPartitionComponentBackedTarget`  
`class IMeshPartitionComponentBackedTarget`  
_L18-22_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionConvertTool.h` (Public)


#### class `UE::MeshPartition::UConvertToolBuilder`  
`class UConvertToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L27-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L32 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& InSceneState) const override;`
- L34 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UE::MeshPartition::UConvertTool`  
`class UConvertTool : public USingleSelectionMeshEditingTool`  
_L43-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- desc: Modeling Mode Tool to convert an arbitrary mesh into a MegaMesh actor. Provides utilities to optionally automatically split the mesh.
- L47 _public prototype_ `virtual void Setup() override;`
- L48 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L50 _public function_ `virtual bool HasCancel() const override`
- L51 _public function_ `virtual bool HasAccept() const override`
- L52 _public prototype_ `virtual bool CanAccept() const override;`
- L54 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L57 _protected prototype_ `TArray<TUniquePtr<Geometry::FDynamicMesh3>> SplitMesh(const Geometry::FDynamicMesh3& InMesh) const;`
- L59 _protected prototype_ `FIntVector GetClampedSectionLayout() const;`
- L60 _protected prototype_ `void CreateOrUpdatePreviewGeometry();`
- L63 _protected member_ `TObjectPtr<MeshPartition::USplitProperties> SplitProperties;` — `UPROPERTY()`
- L66 _protected member_ `TObjectPtr<MeshPartition::UCreateProperties> CreateProperties;` — `UPROPERTY()`
- L69 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry;` — `UPROPERTY()`
- L71 _protected member_ `FBox SplitBounds;`
- L72 _protected member_ `bool bPreviewGeometryNeedsUpdate = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionCreateMeshTool.h` (Public)


#### class `UE::MeshPartition::UCreateMeshToolBuilder`  
`class UCreateMeshToolBuilder : public UInteractiveToolBuilder`  
_L33-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L44 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L45 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L47 _public member_ `EMakeMeshShapeType ShapeType{ EMakeMeshShapeType::Rectangle };`

#### enum `UE::MeshPartition::UCreateMeshToolBuilder::EMakeMeshShapeType`  
`enum class EMakeMeshShapeType : uint32`  
_L39-42_
- L41 _public enumerator_ `Rectangle`

#### enum `UE::MeshPartition::ECreateMeshPlacementType`  
`enum class ECreateMeshPlacementType : uint8`  
_L55-60_
- reflection: `UENUM()`
- desc: Placement Target Types
- L57 _public enumerator_ `GroundPlane = 0`
- L58 _public enumerator_ `OnScene = 1`
- L59 _public enumerator_ `AtOrigin = 2`

#### class `UE::MeshPartition::UPlacementProperties`  
`class UPlacementProperties : public UInteractiveToolPropertySet`  
_L63-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L71 _public member_ `MeshPartition::ECreateMeshPlacementType TargetSurface = MeshPartition::ECreateMeshPlacementType::AtOrigin;` — `UPROPERTY(EditAnywhere, Category = Positioning, meta = (DisplayName = "Target Position"))` — How the shape is placed in the scene.
- L75 _public member_ `float Rotation = 0.0;` — `UPROPERTY(EditAnywhere, Category = Positioning, DisplayName = "Initial Rotation", meta = (UIMin = "0.0", UIMax = "360.0", EditCondition = "!bShowGizmoOptions", HideEditConditionToggle))` — Initial rotation of the shape around its up axis, before placement. After placement, use the gizmo to control rotation.
- L79 _public member_ `bool bAlignToNormal = false;` — `UPROPERTY(EditAnywhere, Category = Positioning, meta = (EditCondition = "TargetSurface == ECreateMeshPlacementType::OnScene"))` — If true, aligns the shape along the normal of the surface it is placed on.
- L83 _public member_ `bool bShowGizmo = true;` — `UPROPERTY(EditAnywhere, Category = Positioning, meta = (EditCondition = "bShowGizmoOptions", EditConditionHides, HideEditConditionToggle))` — Show a gizmo to allow the mesh to be repositioned after the initial placement click.
- L87 _public member_ `bool bShowGizmoOptions = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L91 _public member_ `bool bSnapToExistingMegaMesh;` — `UPROPERTY(EditAnywhere, Category = Snapping, meta = (EditCondition = "bEnableSnapOptions", HideEditConditionToggle))` — Should snap the boundary of the new mesh to the existing base mesh boundary.  Available only if this mesh is being added to an existing Mesh Partition.
- L95 _public member_ `float AlignmentThreshold = 5.0f;` — `UPROPERTY(EditAnywhere, Category = Snapping, meta = (UIMin = "0.0", UIMax = "90.0", EditCondition = "bEnableSnapOptions && bSnapToExistingMegaMesh", EditConditionHides,HideEditConditionToggle))` — Angle tolerance for edges to be considered aligned for snapping (in degrees), only enabled if this mesh is being added to an existing mesh.
- L99 _public member_ `float DistanceThreshold = 100.0f;` — `UPROPERTY(EditAnywhere, Category = Snapping, meta = (UIMin = "0.0", UIMax = "10000.0", ClampMax = "10000000.0", EditCondition = "bEnableSnapOptions && bSnapToExistingMegaMesh", EditConditionHides, HideEditConditionToggle))` — Distance threshold for edge snapping, only enabled if this mesh is being added to an existing mesh.
- L103 _public member_ `bool bDrawSnapTargets = false;` — `UPROPERTY(EditAnywhere, Category = Snapping, meta = (EditCondition = "bEnableSnapOptions && bSnapToExistingMegaMesh", EditConditionHides, HideEditConditionToggle))` — Should render the boundary spans that the tool will snap to, only enabled if this mesh is being added to an existing mesh.
- L113 _public member_ `float CornerThresholdDegrees = 135.f;` — `UPROPERTY(EditAnywhere, Category = Snapping, meta = (UIMin = 0.0f, UIMax = 180.0f, ClampMin = 0.0f, ClampMax = 180.0f, EditCondition = "bEnableSnapOptions && bSnapToExistingMegaMesh", HideEditConditionToggle))` — When generating boundary corners, how sharp the angle needs to be to warrant corner placement there. Lower values require sharper corners, so are more tolerant of curved boundary edges. For instance, 180 will place corners at every vertex along a boundary even if the boundary is perfectly straight, and 135 will place a vertex only once the boundary edge bends 45 degrees off the straight path (i.e. 135 degrees to the previous edge). Only enabled if this mesh is being added to an existing mesh.
- L117 _public member_ `bool bEnableSnapOptions = false;` — `UPROPERTY(meta = (TransientToolProperty))`

#### enum `UE::MeshPartition::ECreateRectangleSectionsGenerationMode`  
`enum class ECreateRectangleSectionsGenerationMode : uint8`  
_L123-133_
- reflection: `UENUM()`
- L126 _public enumerator_ `Automatic` — Automatically generate a grid of sections based on the maximum number of triangles allowed in a section.
- L129 _public enumerator_ `Explicit` — Generate a grid of sections based on explicit user input for resolution in X and Y.
- L132 _public enumerator_ `LastSectionGenerationMode UMETA(Hidden)` — Insert new SectionGeneration types

#### class `UE::MeshPartition::UCreateRectangleToolProperties`  
`class UCreateRectangleToolProperties : public UInteractiveToolPropertySet`  
_L136-209_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L143 _public member_ `FVector2D MeshSize = FVector2D(100000., 100000.);` — `UPROPERTY(EditAnywhere, Category=Mesh, meta=(DisplayName="Size"))` — World space size of the generated mesh.
- L148 _public member_ `FInt32Point MeshResolution = FInt32Point(1000, 1000);` — `UPROPERTY(EditAnywhere, Category=Mesh, meta=(EditCondition = "SectionsGeneration == ECreateRectangleSectionsGenerationMode::Automatic", DisplayName="Resolution"))` — Number of quads in X/Y dimension for the generated mesh, only editable for automatic section generation.
- L155 _public member_ `MeshPartition::ECreateRectangleSectionsGenerationMode SectionsGeneration = MeshPartition::ECreateRectangleSectionsGenerationMode::Automatic;` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(DisplayName="Generation"))` — Defines how sections are generated.
- L165 _public member_ `int32 MaxTrianglesPerSection = 500 * 500 * 2;` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(DisplayName="Max Triangles", ClampMin=2, UIMax=1000000))` — Maximum number of triangles allowed per section. This is used to control the partitioning of the imported mesh into manageable sections. These sections can later be combined and split out manually as desired with the Split and Merge tools. When Sections Generation is Explicit, blocks creation when above limit.
- L175 _public member_ `FInt32Point SectionLayout = FInt32Point(4, 4);` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(EditCondition = "SectionsGeneration == ECreateRectangleSectionsGenerationMode::Explicit", EditConditionHides, DisplayName = "Layout"))` — Number of sections in X/Y dimension. This is only available if the Sections Generation is set to Explicit.
- L184 _public member_ `FInt32Point SectionsResolution = FInt32Point(250, 250);` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(EditCondition="SectionsGeneration == ECreateRectangleSectionsGenerationMode::Explicit", EditConditionHides, DisplayName="Resolution"))` — Number of quads in X/Y dimension per section. This is only available if the Sections Generation is set to Explicit.
- L193 _public member_ `bool bSaveAndUnload = false;` — `UPROPERTY(EditAnywhere, Category=Sections)` — Save and unload sections as they are created. This is only available when World Partition is enabled.
- L202 _private prototype_ `FInt32Point ComputeMeshResolutionInSections() const;` — Resolution in terms of sections, but not all sections will necessarily contain the same number of quads
- L205 _private prototype_ `FInt32Point ComputeMeshResolutionInQuads() const;` — compute mesh resolution in terms of quads
- L208 _private member_ `FInt32Point CachedMeshResolution = FInt32Point(-1, -1);` — `UPROPERTY(meta=(TransientToolProperty))`

#### class `UE::MeshPartition::ULocationVolumesProperties`  
`class ULocationVolumesProperties : public UInteractiveToolPropertySet`  
_L212-239_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L223 _public member_ `bool bCreateLocationVolumes = false;` — `UPROPERTY(EditAnywhere, Category=LocationVolumes, meta=(DisplayName="Create Volumes"))` — Create location volumes to make it easy to load and unload parts of the mesh. This is especially useful when generating large meshes in combination with save and unload. This is only available when World Partition is enabled.
- L231 _public member_ `FInt32Point LocationVolumesResolution = FInt32Point(2, 2);` — `UPROPERTY(EditAnywhere, Category=LocationVolumes, meta=(DisplayName="Volume Resolution"))` — Number of location volumes in X/Y dimension. This is only available when World Partition is enabled.
- L238 _private prototype_ `FInt32Point GetLocationVolumesResolution() const;`

#### class `UE::MeshPartition::UCreateMeshTool`  
`class UCreateMeshTool : public USingleClickTool, public IHoverBehaviorTarget, public IInteractiveToolCameraFocusAPI, public IInteractiveToolShutdownQueryAPI`  
_L247-381_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickTool,IHoverBehaviorTarget,IInteractiveToolCameraFocusAPI,IInteractiveToolShutdownQueryAPI`
- desc: Basic functionality used creating and placing a MeshPartition.  Derive from this class and override functions such as GenerateAsset(), for example see MeshPartition::UCreateRectangleMeshTool
- L251 _public prototype_ `UCreateMeshTool(const FObjectInitializer&);`
- L253 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L255 _public prototype_ `virtual void Setup() override;`
- L256 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L258 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L260 _public function_ `virtual bool HasCancel() const override`
- L261 _public function_ `virtual bool HasAccept() const override`
- L262 _public prototype_ `virtual bool CanAccept() const override;`
- L264 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L267 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;` — USingleClickTool
- L268 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L271 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget interface
- L272 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L273 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L274 _public prototype_ `virtual void OnEndHover() override;`
- L277 _public prototype_ `virtual bool SupportsWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L278 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L279 _public prototype_ `virtual bool SupportsWorldSpaceFocusPoint() override;`
- L280 _public prototype_ `virtual bool GetWorldSpaceFocusPoint(const FRay& WorldRay, FVector& PointOut) override;`
- L283 _public function_ `virtual EToolShutdownType GetPreferredShutdownType(EToolShutdownReason, EToolShutdownType) const override` — IInteractiveToolShutdownQueryAPI implementation
- L293 _protected member_ `EState CurrentState = EState::PlacingPrimitive;`
- L294 _protected prototype_ `void SetState(EState NewState);`
- L296 _protected function_ `virtual void GeneratePreviewMesh(FDynamicMesh3* OutMesh) const`
- L298 _protected prototype_ `virtual void UpdatePreview();`
- L301 _protected prototype_ `void UpdateDisplayMessage() const;` — Refresh the host's display w/ result of BuildDisplayMessage()
- L304 _protected function_ `virtual void BuildDisplayMessage(FText& OutMessage) const` — Override to set tool-specific warning messages
- L308 _protected function_ `virtual void GenerateAsset()`
- L311 _protected member_ `TObjectPtr<MeshPartition::UCreateRectangleToolProperties> CreateRectangleProperties;` — `UPROPERTY()`
- L314 _protected member_ `TObjectPtr<MeshPartition::UPlacementProperties> PlacementProperties;` — `UPROPERTY()`
- L317 _protected member_ `TObjectPtr<MeshPartition::UCreateProperties> MegaMeshCreateProperties;` — `UPROPERTY()`
- L320 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L323 _protected member_ `TObjectPtr<UCombinedTransformGizmo> Gizmo = nullptr;` — `UPROPERTY()`
- L326 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L329 _protected member_ `FString AssetName = TEXT("Gen` — `UPROPERTY()`
- L332 _protected member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()`
- L334 _protected prototype_ `void UpdatePreviewPosition(const FInputDeviceRay& ClickPos);`
- L335 _protected member_ `Geometry::FFrame3d ShapeFrame;`
- L339 _protected prototype_ `void UpdateTargetSurface();`
- L342 _protected function_ `virtual bool ShouldCenterXY() const` — @return true if the primitive needs to be centered in the XY plane when placed.
- L369 _protected prototype_ `static TArray<TUniquePtr<FDynamicMesh3>> SplitMesh(const FDynamicMesh3& InMesh, const FVector3d SectionsPerSide);` — helper that maybe of use in segmenting an existing mesh in a derived class
- L371 _protected prototype_ `void InitSnapTarget();`
- L372 _protected prototype_ `bool SnapPreviewMeshToExisting(const FTransform& ShapeTransform, FVector3d& OutSnapOffset) const;`
- L375 _protected member_ `TArray<Geometry::FSegment3d> PreviewBoundarySegments;` — Boundary spans of the preview mesh (stored in preview mesh space)
- L378 _protected member_ `TArray<Geometry::FSegment3d> SnapTargetSegments;` — Boundary spans of existing mesh providers
- L379 _protected member_ `TUniquePtr<FSegmentTree3> SnapTargetSegmentSpatial;`

#### enum `UE::MeshPartition::UCreateMeshTool::EState`  
`enum class EState`  
_L287-291_
- L289 _public enumerator_ `PlacingPrimitive`
- L290 _public enumerator_ `AdjustingSettings`

#### class `UE::MeshPartition::UCreateMeshTool::FStateChange`  
`class FStateChange : public FToolCommandChange`  
_L349-366_
- inherits: `FToolCommandChange`
- desc: Used to make the initial placement of the mesh undoable
- L352 _public function_ `FStateChange(const FTransform& MeshTransformIn) : MeshTransform(MeshTransformIn)`
- L357 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L358 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L359 _public function_ `virtual FString ToString() const override`
- L365 _protected member_ `FTransform MeshTransform;`

#### class `UE::MeshPartition::UCreateRectangleMeshTool`  
`class UCreateRectangleMeshTool : public MeshPartition::UCreateMeshTool`  
_L385-416_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `MeshPartition::UCreateMeshTool`
- L390 _public prototype_ `explicit UCreateRectangleMeshTool(const FObjectInitializer& ObjectInitializer);`
- L391 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L394 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L395 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L396 _public prototype_ `virtual void GenerateAsset() override;`
- L397 _public prototype_ `virtual bool CanAccept() const override;`
- L401 _protected typedef_ `using FSectionInfo = MeshPartition::FRectangleGeneratorUtils::FSectionInfo;`
- L402 _protected prototype_ `virtual void UpdatePreview() override;`
- L404 _protected prototype_ `virtual void GeneratePreviewMesh(FDynamicMesh3* OutMesh) const override;`
- L407 _protected prototype_ `bool IsConfigurationValid(FText* OutErrorMessage = nullptr) const;` — Validate that the current configuration is buildable / within triangle limits
- L409 _protected prototype_ `void RenderSections(IToolsContextRenderAPI* RenderAPI) const;`
- L411 _protected prototype_ `virtual void BuildDisplayMessage(FText& OutMessage) const override;`
- L412 _protected prototype_ `FMegaMeshRectangleGeneratorParams GetGeneratorParams() const ;`
- L414 _protected member_ `TArray<FSectionInfo> SectionInfos;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L20 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L21 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FSegmentTree3);`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionExpandTool.h` (Public)


#### class `UE::MeshPartition::UExpandToolBuilder`  
`class UExpandToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L28-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L33 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L34 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L35 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `UE::MeshPartition::EExpandType`  
`enum class EExpandType`  
_L41-48_
- reflection: `UENUM()`
- L44 _public enumerator_ `Extrude` — Extrude one or more selected topology edges simultaneously
- L47 _public enumerator_ `Mirror` — Mirror the existing mesh across selected edge or corner

#### enum `UE::MeshPartition::EExpandExtrudeEdgeDirectionMode`  
`enum class EExpandExtrudeEdgeDirectionMode`  
_L51-58_
- reflection: `UENUM()`
- L54 _public enumerator_ `LocalExtrudeFrames` — Each vertex gets its own local frame to extrude along.
- L57 _public enumerator_ `SingleDirection` — All vertices are extruded in the same direction

#### class `UE::MeshPartition::UExpandToolProperties`  
`class UExpandToolProperties : public UInteractiveToolPropertySet`  
_L61-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L74 _public member_ `float CornerThresholdDegrees = 135.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (UIMin = 0.0f, UIMax = 180.0f, ClampMin = 0.0f, ClampMax = 180.0f))` — When generating corners, how sharp the angle needs to be to warrant corner placement there. Lower values require sharper corners, so are more tolerant of curved boundary edges. For instance, 180 will place corners at every vertex along a boundary even if the boundary is perfectly straight, and 135 will place a vertex only once the boundary edge bends 45 degrees off the straight path (i.e. 135 degrees to the previous edge).
- L77 _public member_ `int32 MinSpanSize = 1;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (UIMin = 0, UIMax = 10, ClampMin = 0))`
- L81 _public member_ `MeshPartition::EExpandType ExpandType = MeshPartition::EExpandType::Extrude;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Which algorithm to use to expand the current selection
- L85 _public member_ `int32 NumSteps = 10;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (UIMin = 0, UIMax = 1000, ClampMin = 0, ClampMax = 1000000, EditCondition = "ExpandType == EExpandType::Extrude"))` — Number of steps to extend outward
- L89 _public member_ `float StepSize = 100.0f;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (UIMin = 0.0f, UIMax = 10000.0f, ClampMin = 0.0f, ClampMax = 1000000.0f, EditCondition = "ExpandType == EExpandType::Extrude"))` — Size of each outward-extending step
- L93 _public member_ `MeshPartition::EExpandExtrudeEdgeDirectionMode ExtrudeDirection = MeshPartition::EExpandExtrudeEdgeDirectionMode::LocalExtrudeFrames;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (EditCondition = "ExpandType == EExpandType::Extrude"))` — How direction to move the vertices is determined
- L97 _public member_ `bool bAdjustToExtrudeEvenly = true;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (EditCondition = "ExpandType == EExpandType::Extrude && ExtrudeDirection == EExpandExtrudeEdgeDirectionMode::LocalExtrudeFrames"))` — Adjust individual extrude directions in an effort to make extruded edges parallel to their original edges
- L101 _public member_ `bool bUseUnselectedForFrames = false;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (EditCondition = "ExpandType == EExpandType::Extrude && ExtrudeDirection == EExpandExtrudeEdgeDirectionMode::LocalExtrudeFrames"))` — When generating extrude frames, whether to use unselected neighbors for setting the frame.
- L105 _public member_ `bool bShouldMirrorCorners = true;` — `UPROPERTY(EditAnywhere, Category = Mirror, meta = (EditCondition = "ExpandType == EExpandType::Mirror"))` — Whether to mirror across topological corners as well as edges
- L109 _public member_ `bool bRenderNewSections = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Render potenetial new sections in different colors

#### class `UE::MeshPartition::UExpandTool`  
`class UExpandTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolExclusiveToolAPI`  
_L116-168_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolExclusiveToolAPI`
- L123 _private prototype_ `virtual void Setup() override;` — UMultiSelectionMeshEditingTool overrides
- L124 _private prototype_ `virtual void OnShutdown(EToolShutdownType InShutdownType) override;`
- L125 _private function_ `virtual bool HasCancel() const override`
- L126 _private function_ `virtual bool HasAccept() const override`
- L127 _private prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L130 _private member_ `TObjectPtr<MeshPartition::UExpandToolProperties> ExpandProperties;` — `UPROPERTY()`
- L133 _private member_ `TWeakObjectPtr<AMeshPartition> MegaMeshActor;` — Note we use a WeakObjectPtr (rather than UPROPERTY) here b/c this actor belongs to the world, not the tool
- L136 _private member_ `TArray<TObjectPtr<UBoundarySelectionMechanic>> SelectionMechanics;` — `UPROPERTY()`
- L138 _private member_ `TArray<TUniquePtr<Geometry::FDynamicMesh3>> OriginalMeshes;`
- L140 _private member_ `TArray<TUniquePtr<Geometry::FMeshBoundaryLoops>> MeshBoundaryLoops;`
- L142 _private member_ `TArray<TUniquePtr<Geometry::FDynamicMeshAABBTree3>> MeshSpatials;`
- L145 _private member_ `TArray<TObjectPtr<UPreviewMesh>> PreviewMeshes;` — `UPROPERTY()`
- L150 _private prototype_ `FVector3d AverageOutDirection(int32 TargetIndex, int32 SpanIndex) const;` — For a given span, compute the average "perpendicular to span edge" vector
- L153 _private prototype_ `double InputMeshWidth() const;` — For all selected input meshes, find the average largest bounding box dimension
- L156 _private prototype_ `double AverageInputMeshBoundaryEdgeLength() const;` — For all selected input meshes, find the average boundary edge length
- L159 _private prototype_ `void OnSelectionModified();` — Respond to UI events
- L160 _private prototype_ `void RecomputeBoundaryTopology();`
- L161 _private prototype_ `void GeneratePreviewMeshes();`
- L164 _private prototype_ `void Extrude();` — Generate new geometry
- L165 _private prototype_ `void Mirror();`
- L167 _private prototype_ `void CreateNewBaseModifiers();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L15 _typedef_ `template <class T> class TMeshAABBTree3;` (scope `UE::Geometry`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionHeightSculptTool.h` (Public)


#### enum `UE::MeshPartition::EHeightSculptReferenceSurface`  
`enum class EHeightSculptReferenceSurface : uint8`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `Plane`
- L18 _public enumerator_ `Sphere`

#### class `UE::MeshPartition::UHeightSculptToolProperties`  
`class UHeightSculptToolProperties : public UInteractiveToolPropertySet`  
_L22-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L35 _public member_ `bool bRequireConnectivity = true;` — `UPROPERTY(EditAnywhere, Category = HeightSculptOptions)` — When true, only vertices that are connected to the mouse hit point through vertices inside the brush are moved. For example, if you brush vertices of a hill that has a cave close to the surface, only the vertices of the outside surface will be moved even if the brush happens to overlap some hidden cave vertices. However this prevents brushing off of the mesh, because the tool requires a hit triangle.
- L42 _public member_ `bool bInitializeReferenceTransformFromTarget = true;` — `UPROPERTY(EditAnywhere, Category = HeightSculptOptions, AdvancedDisplay, Meta=(DisplayName = "Initialize From Target"))` — When true, the reference plane/sphere transform is initialized using the target object's transform
- L46 _public member_ `EHeightSculptReferenceSurface ReferenceSurface = EHeightSculptReferenceSurface::Plane;` — `UPROPERTY(EditAnywhere, Category = HeightSculptOptions)` — Specify the type of height sculpt for the tool

#### class `UE::MeshPartition::UHeightSculptToolSettingsProperties`  
`class UHeightSculptToolSettingsProperties : public UInteractiveToolPropertySet`  
_L50-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L57 _public member_ `bool bAllowEditorGizmo = true;` — `UPROPERTY(EditAnywhere, Category = ToolSettings, Meta = (ModelingQuickSettings))` — When true, the standard editor transform gizmo is shown when selecting other actors, allowing you to reposition reference objects without leaving the tool

#### class `UE::MeshPartition::UHeightSculptToolBuilder`  
`class UHeightSculptToolBuilder : public UMeshVertexSculptToolBuilder`  
_L61-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexSculptToolBuilder`
- L66 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### class `UE::MeshPartition::UHeightSculptTool`  
`class UHeightSculptTool : public UMeshVertexSculptTool, public IInteractiveToolEditorGizmoAPI`  
_L70-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexSculptTool,IInteractiveToolEditorGizmoAPI`
- L77 _public prototype_ `virtual bool GetAllowStandardEditorGizmos() override;` — IInteractiveToolEditorGizmoAPI - allow standard editor gizmo while this tool is active, so users can reposition reference objects without leaving the tool
- L90 _protected prototype_ `virtual void RegisterBrushes() override;` — UMeshVertexSculptTool
- L91 _protected prototype_ `virtual FString GetPropertyCacheIdentifier() const override;`
- L92 _protected prototype_ `virtual bool RequireConnectivityToHitPointInStamp() const override;`
- L93 _protected prototype_ `virtual void UpdateBrushType(int32 BrushID) override;`
- L96 _protected prototype_ `virtual bool ShowWorkPlane() const override;` — UMeshSculptToolBase
- L99 _protected prototype_ `virtual void Setup() override;` — UInteractiveTool
- L100 _protected prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L104 _private member_ `TObjectPtr<MeshPartition::UHeightSculptToolProperties> HeightSculptProperties = nullptr;` — `UPROPERTY()`
- L107 _private member_ `TObjectPtr<MeshPartition::UHeightSculptToolSettingsProperties> ToolSettingsProperties = nullptr;` — `UPROPERTY()`
- L110 _private member_ `bool bHaveHeightBrushActive = false;` — True when the active brush is one that we added in the subclass

#### enum `UE::MeshPartition::UHeightSculptTool::EBrushType`  
`enum class EBrushType`  
_L80-86_
- desc: BrushIDs that can be used by SetActiveBrushType
- L82 _public enumerator_ `HeightSculpt = (int32)EMeshVertexSculptBrushType::LastValue + 1`
- L83 _public enumerator_ `HeightSmooth`
- L84 _public enumerator_ `HeightFlatten`
- L85 _public enumerator_ `SlopeErode`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionHeightmapImportTool.h` (Public)


#### class `UE::MeshPartition::UHeightmapImportToolBuilder`  
`class UHeightmapImportToolBuilder : public UInteractiveToolBuilder`  
_L18-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L22 _public function_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override`
- L24 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### enum `UE::MeshPartition::EHeightmapImportSectionsGenerationMode`  
`enum class EHeightmapImportSectionsGenerationMode : uint8`  
_L28-35_
- reflection: `UENUM()`
- L31 _public enumerator_ `Automatic` — Automatically generate a grid of sections based on the maximum number of triangles allowed in a section.
- L34 _public enumerator_ `Explicit` — Generate a grid of sections based on explicit user input for resolution in X and Y.

#### class `UE::MeshPartition::UHeightmapImportPropertySet`  
`class UHeightmapImportPropertySet : public UInteractiveToolPropertySet`  
_L38-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L44 _public member_ `FFilePath HeightmapFile;` — `UPROPERTY(EditAnywhere, Category = Heightmap, meta=(DisplayName="Filename"))` — Filename of  the heightmap to use for import.
- L48 _public member_ `FInt32Point MeshResolution = FInt32Point(1024, 1024);` — `UPROPERTY(EditAnywhere, Category=Mesh, meta=(DisplayName="Resolution"))` — Number of vertices in X/Y dimension for the generated mesh.
- L52 _public member_ `FVector MeshSize = FVector(1024.0, 1024.0, 250.0);` — `UPROPERTY(EditAnywhere, Category=Mesh, meta=(DisplayName="Size"))` — World space size of the generated mesh.
- L58 _public member_ `MeshPartition::EHeightmapImportSectionsGenerationMode SectionsGeneration = MeshPartition::EHeightmapImportSectionsGenerationMode::Automatic;` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(DisplayName="Generation"))` — Defines how sections are generated.
- L68 _public member_ `int32 MaxTrianglesPerSection = 512 * 512 * 2;` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(EditCondition="SectionsGeneration == EHeightmapImportSectionsGenerationMode::Automatic", EditConditionHides, DisplayName="Max Triangles"))` — Maximum number of triangles allowed per section. This is used to control the automatic partitioning of the imported mesh into manageable sections. These sections can later be combined and split out manually as desired with the Split and Merge tools. This is only available if the Sections Generation is set to Automatic.
- L77 _public member_ `FInt32Point SectionsResolution = FInt32Point(4, 4);` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(EditCondition="SectionsGeneration == EHeightmapImportSectionsGenerationMode::Explicit", EditConditionHides, DisplayName="Resolution"))` — Number of sections in X/Y dimension. This is only available if the Sections Generation is set to Explicit.
- L85 _public member_ `bool bSaveAndUnload = false;` — `UPROPERTY(EditAnywhere, Category=Sections, meta=(EditCondition="bWorldPartitionIsAvailable", HideEditConditionToggle))` — Save and unload sections as they are created. This is only available when World Partition is enabled.
- L94 _public member_ `bool bCreateLocationVolumes = false;` — `UPROPERTY(EditAnywhere, Category=LocationVolumes, meta=(EditCondition="bWorldPartitionIsAvailable", HideEditConditionToggle, DisplayName="Create Volumes"))` — Create location volumes to make it easy to load and unload parts of the mesh imported from the heightmap. This is especially useful when generating large meshes in combination with save and unload. This is only available when World Partition is enabled.
- L100 _public member_ `FInt32Point LocationVolumesResolution = FInt32Point(2, 2);` — `UPROPERTY(EditAnywhere, Category=LocationVolumes, meta=(EditCondition="bWorldPartitionIsAvailable && bCreateLocationVolumes", DisplayName="Resolution"))` — Number of location volumes in X/Y dimension.
- L105 _private prototype_ `FInt32Point GetSectionsResolution() const;`
- L106 _private prototype_ `FInt32Point GetLocationVolumesResolution() const;`
- L109 _private member_ `bool bWorldPartitionIsAvailable;` — `UPROPERTY(meta=(TransientToolProperty))`

#### class `UE::MeshPartition::UHeightmapImportTool`  
`class UHeightmapImportTool : public UInteractiveTool, public IInteractiveToolShutdownQueryAPI`  
_L117-146_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolShutdownQueryAPI`
- L121 _public prototype_ `virtual void SetWorld(UWorld* InWorld);`
- L123 _public prototype_ `virtual void Setup() override;`
- L124 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L126 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L128 _public function_ `virtual bool HasAccept() const override`
- L129 _public function_ `virtual bool HasCancel() const override`
- L130 _public prototype_ `virtual bool CanAccept() const override;`
- L131 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L134 _public function_ `virtual EToolShutdownType GetPreferredShutdownType(EToolShutdownReason, EToolShutdownType) const override` — IInteractiveToolShutdownQueryAPI implementation
- L138 _private member_ `TObjectPtr<MeshPartition::UHeightmapImportPropertySet> Properties;` — `UPROPERTY()`
- L141 _private member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()`
- L143 _private prototype_ `bool IsConfigurationValid(FText* OutErrorMessage = nullptr) const;`
- L144 _private prototype_ `void UpdateDisplayMessage() const;`
- L145 _private prototype_ `FHeightmapImportParams GetParams() const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionMergeTool.h` (Public)


#### class `UE::MeshPartition::UMergeToolBuilder`  
`class UMergeToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L17-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L22 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L23 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L24 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UE::MeshPartition::UMergeToolProperties`  
`class UMergeToolProperties : public UInteractiveToolPropertySet`  
_L30-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L35 _public member_ `bool bWeldEdges = true;` — `UPROPERTY(EditAnywhere, Category=Merge)`

#### class `UE::MeshPartition::UMergeTool`  
`class UMergeTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolExclusiveToolAPI`  
_L44-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolExclusiveToolAPI`
- desc: Modeling Mode Tool to merge multiple MegaMesh Sections to a single section.
- L49 _public prototype_ `virtual void Setup() override;`
- L50 _public prototype_ `virtual void OnShutdown(EToolShutdownType InShutdownType) override;`
- L52 _public function_ `virtual bool HasCancel() const override`
- L53 _public function_ `virtual bool HasAccept() const override`
- L55 _protected prototype_ `void Merge();`
- L58 _protected member_ `TObjectPtr<MeshPartition::UMergeToolProperties> MergeProperties;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionModelingToolsetModule.h` (Public)


#### class `UE::MeshPartition::FMegaMeshModelingToolsetModule`  
`class FMegaMeshModelingToolsetModule : public IModuleInterface, public IModelingModeToolExtension`  
_L16-29_
- inherits: `IModuleInterface,IModelingModeToolExtension`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `virtual FText GetExtensionName() override;` — IModelingModeToolExtension implementation
- L25 _public prototype_ `virtual FText GetToolSectionName() override;`
- L26 _public prototype_ `virtual void GetExtensionTools(const FExtensionToolQueryInfo& QueryInfo, TArray<FExtensionToolDescription>& ToolsOut) override;`
- L27 _public prototype_ `virtual bool GetExtensionExtendedInfo(FModelingModeExtensionExtendedInfo& InfoOut) override;`
- L28 _public prototype_ `virtual bool GetExtensionToolTargets(TArray<TSubclassOf<UToolTargetFactory>>& ToolTargetFactoriesOut) override;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMeshModelingToolset, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMeshModelingToolset, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionModifierToolTarget.h` (Public)


#### class `UE::MeshPartition::UModifierToolTarget`  
`class UModifierToolTarget : public USceneComponentToolTarget, public IDynamicMeshProvider, public IMaterialProvider, public IPhysicsDataSource`  
_L43-107_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `USceneComponentToolTarget,IDynamicMeshProvider,IMaterialProvider,IPhysicsDataSource`
- desc: UToolTarget specialization that supports viewing megamesh modifiers by extracting the mesh as it exists after the modifier is applied
- L52 _public prototype_ `void Initialize(MeshPartition::UModifierComponent* ModifierComponent);`
- L55 _public prototype_ `virtual Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider implementation
- L58 _public prototype_ `int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L59 _public prototype_ `UMaterialInterface* GetMaterial(int32 InMaterialIndex) const override;`
- L60 _public prototype_ `void GetMaterialSet(FComponentMaterialSet& OutMaterialSet, bool bInPreferAssetMaterials) const override;`
- L61 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& InMaterialSet, bool bInApplyToAsset) override;`
- L64 _public prototype_ `virtual UBodySetup* GetBodySetup() const override;` — IPhysicsDataSource implementation
- L65 _public prototype_ `virtual IInterface_CollisionDataProvider* GetComplexCollisionProvider() const override;`
- L68 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget
- L71 _public prototype_ `virtual void SetOwnerVisibility(bool bInVisible) const override;` — USceneComponentToolTarget
- L73 _public prototype_ `void ConfigurePreviewForRendering(UPrimitiveComponent* PrimitiveComponent) const;`
- L75 _public prototype_ `void UpdateRenderTextureForPreview(const Geometry::FDynamicMesh3& PreviewMesh);`
- L77 _protected prototype_ `void BuildModifiedMeshUpToTarget(Geometry::FDynamicMesh3& OutResultMesh, bool bIncludeTargetModifier = false);`
- L79 _protected prototype_ `virtual TArray<Geometry::FOrientedBox3d> GetBounds() const;`
- L80 _protected prototype_ `virtual TArray<MeshPartition::UModifierComponent*> GetModifiersToProcess() const;`
- L83 _protected member_ `TObjectPtr<MeshPartition::UModifierComponent> TargetModifier = nullptr;` — `UPROPERTY()`
- L85 _protected member_ `mutable TArray<TWeakObjectPtr<MeshPartition::APreviewSection>> PreviewSections;` — `UPROPERTY()`
- L87 _protected member_ `TArray<uint8> ChannelTable;`
- L88 _protected member_ `FVector2f ChannelTexcoordDesc;`
- L91 _protected member_ `TObjectPtr<UTexture> ChannelTexture;` — `UPROPERTY()`
- L93 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> MID;` — `UPROPERTY()`
- L96 _protected typedef_ `template <typename KeyType, typename ValueType> using TWeakObjectPtrKeyMap = TMap<KeyType, ValueType, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<KeyType, ValueType>>;`
- L99 _protected member_ `TOptional<MeshPartition::FChannelTextureRenderer::FChannelRenderUVMeshTopology> CachedUVTopology;` — Cached UV topology for fast texture updates during painting
- L101 _protected member_ `mutable TWeakObjectPtrKeyMap<TWeakObjectPtr<MeshPartition::APreviewSection>, TWeakObjectPtr<AActor>> PreviewActors;`
- L106 _private member_ `mutable TArray<TWeakObjectPtr<MeshPartition::UMeshProviderModifier>> HiddenBaseSections;` — When using SetOwnerVisibility, we hide all base sections that were entangled with our preview sections. This keeps track of them so that we can unhide them.

#### class `UE::MeshPartition::UEditableModifierToolTarget`  
`class UEditableModifierToolTarget : public MeshPartition::UModifierToolTarget, public IDynamicMeshCommitter`  
_L114-131_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `MeshPartition::UModifierToolTarget,IDynamicMeshCommitter`
- desc: UToolTarget specialization that supports editing megamesh modifiers by extracting the mesh as it exists before or after the modifier is applied
- L122 _public prototype_ `virtual Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider implementation
- L125 _public prototype_ `virtual void CommitDynamicMesh(const Geometry::FDynamicMesh3& InMesh, const FDynamicMeshCommitInfo& InCommitInfo) override;` — IDynamicMeshCommitter implementation
- L129 _protected prototype_ `virtual TArray<Geometry::FOrientedBox3d> GetBounds() const override;`
- L130 _protected prototype_ `virtual TArray<MeshPartition::UModifierComponent*> GetModifiersToProcess() const override;`

#### class `UE::MeshPartition::UModifierToolTargetFactory`  
`class UModifierToolTargetFactory : public UToolTargetFactory`  
_L136-144_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTargetFactory`
- L141 _public prototype_ `virtual bool CanBuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InRequirements) const override;`
- L143 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InRequirements) override;`

#### class `UE::MeshPartition::UEditableModifierToolTargetFactory`  
`class UEditableModifierToolTargetFactory : public UToolTargetFactory`  
_L149-157_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTargetFactory`
- L154 _public prototype_ `virtual bool CanBuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InRequirements) const override;`
- L156 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InRequirements) override;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Geometry` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionMultiSectionToolTarget.h` (Public)


#### class `UE::MeshPartition::UMultiSectionToolTarget`  
`class UMultiSectionToolTarget : public UToolTarget , public IDynamicMeshProvider , public IDynamicMeshCommitter`  
_L24-80_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTarget,IDynamicMeshProvider,IDynamicMeshCommitter,IPrimitiveComponentBackedTarget,IMaterialProvider`
- desc: Tool target that combines multiple base sections to allow them to be edited together, and splits them back out on commit. Also supports single base section editing.
- L42 _public prototype_ `void Initialize(const TArray<TObjectPtr<MeshPartition::UMeshProviderModifier>> BaseSections);`
- L45 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget
- L48 _public prototype_ `virtual Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider implementation
- L51 _public prototype_ `virtual void CommitDynamicMesh(const Geometry::FDynamicMesh3& InMesh, const FDynamicMeshCommitInfo& InCommitInfo) override;` — IDynamicMeshCommitter implementation
- L55 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L56 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 InMaterialIndex) const override;`
- L57 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& OutMaterialSet, bool bInPreferAssetMaterials) const override;`
- L58 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& InMaterialSet, bool bInApplyToAsset) override;`
- L61 _public prototype_ `virtual UPrimitiveComponent* GetOwnerComponent() const override;` — IPrimitiveComponentBackedTarget implementation
- L62 _public prototype_ `virtual USceneComponent* GetOwnerSceneComponent() const override;`
- L63 _public prototype_ `virtual AActor* GetOwnerActor() const override;`
- L64 _public prototype_ `virtual void SetOwnerVisibility(bool bVisible) const override;`
- L65 _public prototype_ `virtual FTransform GetWorldTransform() const override;`
- L66 _public prototype_ `virtual bool HitTestComponent(const FRay& WorldRay, FHitResult& OutHit) const override;`
- L68 _public function_ `const TArray<TWeakObjectPtr<MeshPartition::UMeshProviderModifier>>& GetBaseSections() const`
- L71 _private prototype_ `Geometry::FDynamicMesh3 BuildMergedMesh();`
- L72 _private prototype_ `void SplitMeshesToSections(const Geometry::FDynamicMesh3& InMesh);`
- L74 _private member_ `FTransform TargetTransform = FTransform::Identity;`
- L77 _private member_ `TArray<TWeakObjectPtr<MeshPartition::UMeshProviderModifier>> BaseSections;` — `UPROPERTY()`
- L79 _private member_ `TArray<TArray<FName>> PerSectionChannels;` — 1:1 with BaseSections. Used to figure out which channels a section originally had.

#### class `UE::MeshPartition::UMultiSectionToolTargetFactory`  
`class UMultiSectionToolTargetFactory : public UToolTargetFactory`  
_L83-93_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTargetFactory`
- L87 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L88 _public prototype_ `virtual UToolTarget* BuildTarget(UObject * SourceObject, const FToolTargetTypeRequirements & TargetTypeInfo) override;`
- L90 _public prototype_ `virtual int32 CanBuildTargets(const TArray<UObject*>&InputObjects, const FToolTargetTypeRequirements & TargetTypeInfo, TArray<bool>&WouldBeUsedOut) override;`
- L91 _public prototype_ `virtual TArray<UToolTarget*> BuildTargets(const TArray<UObject*>&InputObjects, const FToolTargetTypeRequirements & TargetTypeInfo, TArray<bool>&WasUsedOut) override;`
- L92 _public prototype_ `virtual UToolTarget* BuildFirstTarget(const TArray<UObject*>&InputObjects, const FToolTargetTypeRequirements & TargetTypeInfo, TArray<bool>&WasUsedOut) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionPlaceModifierTool.h` (Public)


#### enum `UE::MeshPartition::EModifierClassType`  
`enum class EModifierClassType : uint8`  
_L19-36_
- reflection: `UENUM()`
- L21 _public enumerator_ `InstancedPatch`
- L22 _public enumerator_ `Project`
- L23 _public enumerator_ `Patch`
- L24 _public enumerator_ `Remesh`
- L25 _public enumerator_ `Spline`
- L26 _public enumerator_ `TexturePatch`
- L27 _public enumerator_ `MeshLayer`
- L28 _public enumerator_ `Noise`
- L29 _public enumerator_ `Boolean`
- L30 _public enumerator_ `Lattice`
- L31 _public enumerator_ `SplineRemesh`
- L32 _public enumerator_ `WeightUtility`
- L35 _public enumerator_ `LastModifier UMETA(Hidden)` — Insert new modifier types above this line

#### class `UE::MeshPartition::UPlaceModifierToolBuilder`  
`class UPlaceModifierToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L43-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L48 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L49 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`
- L51 _public member_ `int32 DefaultModifierTypeID = -1;`

#### class `UE::MeshPartition::UPlaceModifierToolProperties`  
`class UPlaceModifierToolProperties : public UInteractiveToolPropertySet`  
_L57-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L64 _public member_ `MeshPartition::EModifierClassType ModifierType = MeshPartition::EModifierClassType::Patch;` — `UPROPERTY(EditAnywhere, Category = "Add Modifier")`

#### class `UE::MeshPartition::UPlaceModifierTool`  
`class UPlaceModifierTool : public USingleSelectionMeshEditingTool`  
_L71-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- L77 _public prototype_ `UPlaceModifierTool();`
- L79 _public prototype_ `virtual void Setup() override;`
- L80 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L82 _public prototype_ `void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L84 _public function_ `virtual bool HasCancel() const override`
- L85 _public function_ `virtual bool HasAccept() const override`
- L86 _public function_ `virtual bool CanAccept() const override`
- L88 _public prototype_ `void SetDefaultModifierType(int32 InModifierTypeID);`
- L92 _protected prototype_ `TObjectPtr<UClass> GetModifierToCreateClass();`
- L93 _protected prototype_ `void SetupNewModifier(AActor*, MeshPartition::UModifierComponent*);`
- L94 _protected prototype_ `void AssignToActiveLayer(MeshPartition::UModifierComponent*);`
- L96 _protected member_ `TWeakObjectPtr<AMeshPartition> TargetMegaMesh;`
- L99 _protected member_ `TObjectPtr<MeshPartition::UPlaceModifierToolProperties> Settings;` — `UPROPERTY()`
- L102 _protected member_ `TObjectPtr<UCombinedTransformGizmo> Gizmo = nullptr;` — `UPROPERTY()`
- L105 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L107 _private member_ `int32 DefaultModifierTypeID = -1;`
- L109 _private member_ `TArray<MeshPartition::EModifierClassType> ModifierTypes;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionResectionTool.h` (Public)


#### class `UE::MeshPartition::UMeshPartitionResectionToolBuilder`  
`class UMeshPartitionResectionToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L19-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L24 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L25 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L26 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UE::MeshPartition::UMeshPartitionResectionToolProperties`  
`class UMeshPartitionResectionToolProperties : public UInteractiveToolPropertySet`  
_L32-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L37 _public member_ `bool bWeldEdges = true;` — `UPROPERTY(EditAnywhere, Category=Merge)`
- L44 _public member_ `FIntVector SectionLayout = FIntVector(4, 4, 1);` — `UPROPERTY(EditAnywhere, Category = Sections, meta = (DisplayName = "Layout", ClampMin=1, UIMax=64, ClampMax=1024))` — Number of sections in X/Y/Z dimension.

#### class `UE::MeshPartition::UMeshPartitionResectionTool`  
`class UMeshPartitionResectionTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolExclusiveToolAPI, public IInteractiveToolShutdownQueryAPI`  
_L54-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolExclusiveToolAPI,IInteractiveToolShutdownQueryAPI`
- desc: Modeling Mode Tool to merge multiple MegaMesh Sections to a single section.
- L59 _public prototype_ `virtual void Setup() override;`
- L60 _public prototype_ `virtual void OnShutdown(EToolShutdownType InShutdownType) override;`
- L68 _private function_ `virtual EToolShutdownType GetPreferredShutdownType(EToolShutdownReason, EToolShutdownType) const override` — IInteractiveToolShutdownQueryAPI implementation
- L70 _private function_ `virtual bool HasCancel() const override`
- L71 _private function_ `virtual bool HasAccept() const override`
- L72 _private prototype_ `virtual void OnTick(float DeltaTime) override;`
- L76 _private prototype_ `void Resection();`
- L77 _private prototype_ `void CreateOrUpdatePreviewGeometry();`
- L80 _private function_ `FIntVector GetClampedSectionLayout() const`
- L86 _private member_ `TObjectPtr<UMeshPartitionResectionToolProperties> Properties;` — `UPROPERTY()`
- L89 _private member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry;` — `UPROPERTY()`
- L91 _private member_ `FBox ResectionBounds;`
- L92 _private member_ `bool bPreviewGeometryNeedsUpdate = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionSectionToolTarget.h` (Public)


#### class `UE::MeshPartition::USectionToolTarget`  
`class USectionToolTarget : public UDynamicMeshComponentToolTarget, public IMeshPartitionComponentBackedTarget`  
_L21-34_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UDynamicMeshComponentToolTarget,IMeshPartitionComponentBackedTarget`
- desc: Target that has the exact same support as a dynamic mesh component, by operating on the underlying base section dynamic mesh component.
- L30 _public prototype_ `virtual void SetOwnerVisibility(bool bVisible) const override;` — IPrimitiveComponentBackedTarget

#### class `UE::MeshPartition::USectionToolTargetFactory`  
`class USectionToolTargetFactory : public UToolTargetFactory`  
_L39-48_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTargetFactory`
- L45 _public prototype_ `virtual bool CanBuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InTargetTypeInfo) const override;`
- L47 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InTargetTypeInfo) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionSplitTool.h` (Public)


#### class `UE::MeshPartition::USplitToolBuilder`  
`class USplitToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L17-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- L22 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& InSceneState) const override;`
- L24 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UE::MeshPartition::USplitTool`  
`class USplitTool : public UMeshSelectionTool`  
_L30-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSelectionTool`
- L36 _public prototype_ `USplitTool();`
- L38 _public prototype_ `virtual void Setup() override;`
- L40 _public prototype_ `virtual void OnShutdown(EToolShutdownType InShutdownType) override;`
- L42 _public function_ `virtual void ApplyAction(EMeshSelectionToolActions InActionType) override`
- L44 _protected prototype_ `void SeparateSelectedTriangles();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionStitchTool.h` (Public)


#### class `UE::MeshPartition::UStitchToolBuilder`  
`class UStitchToolBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L31-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- desc: ToolBuilder
- L35 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L36 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L39 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;` — Returns the tool target type requirements for the target MegaMesh for this tool.
- L41 _public prototype_ `const FToolTargetTypeRequirements& GetStitchableTargetRequirements() const;` — Returns the tool target type requirements for meshes that are stitchable into the target MegaMesh.

#### enum `UE::MeshPartition::EStitchToolActions`  
`enum class EStitchToolActions`  
_L45-50_
- reflection: `UENUM()`
- L47 _public enumerator_ `NoAction`
- L48 _public enumerator_ `WeldEdges`
- L49 _public enumerator_ `FillHole`

#### class `UE::MeshPartition::UStitchToolActions`  
`class UStitchToolActions : public UInteractiveToolPropertySet`  
_L53-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L58 _public member_ `TWeakObjectPtr<MeshPartition::UStitchTool> ParentTool;`
- L60 _public function_ `void Initialize(MeshPartition::UStitchTool* ParentToolIn)`
- L62 _public prototype_ `void PostAction(MeshPartition::EStitchToolActions InAction);`
- L65 _public prototype_ `void Weld();` — `UFUNCTION(CallInEditor)`
- L68 _public prototype_ `void FillHole();` — `UFUNCTION(CallInEditor)`

#### class `UE::MeshPartition::FStitchToolMeshChange`  
`class FStitchToolMeshChange : public FToolCommandChange`  
_L71-83_
- inherits: `FToolCommandChange`
- L74 _public function_ `FStitchToolMeshChange(TUniquePtr<UE::Geometry::FDynamicMeshChange> MeshChangeIn) : MeshChange(MoveTemp(MeshChangeIn))`
- L78 _public prototype_ `virtual void Apply(UObject* InObject) override;`
- L79 _public prototype_ `virtual void Revert(UObject* InObject) override;`
- L80 _public function_ `virtual FString ToString() const override`
- L82 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMeshChange> MeshChange;`

#### class `UE::MeshPartition::UStitchTool`  
`class UStitchTool : public USingleSelectionMeshEditingTool`  
_L86-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- L90 _public prototype_ `virtual void Setup() override;`
- L91 _public prototype_ `virtual void OnShutdown(EToolShutdownType InShutdownType) override;`
- L92 _public prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L93 _public prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI) override;`
- L95 _public function_ `virtual bool HasCancel() const override`
- L96 _public function_ `virtual bool HasAccept() const override`
- L98 _public prototype_ `void RequestAction(MeshPartition::EStitchToolActions InAction);`
- L100 _public prototype_ `UE::Geometry::FDynamicMeshAABBTree3& GetSpatial();`
- L102 _public prototype_ `void OnSelectionModifiedEvent();`
- L104 _public prototype_ `void UpdateFromCurrentMesh(bool bUpdateTopology);`
- L106 _public prototype_ `void SetTargetToStitch(UToolTarget* InTargetToStitch);`
- L109 _protected prototype_ `void ApplyWeld();`
- L110 _protected prototype_ `void ApplyFillHole();`
- L112 _protected prototype_ `bool BeginMeshFaceEditChange();`
- L113 _protected prototype_ `bool BeginMeshEdgeEditChange();`
- L114 _protected prototype_ `void EmitCurrentMeshChangeAndUpdate(const FText& InTransactionLabel, TUniquePtr<UE::Geometry::FDynamicMeshChange> InMeshChange);`
- L117 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L120 _protected member_ `TObjectPtr<UToolTarget> TargetToStitch = nullptr;` — `UPROPERTY()`
- L123 _protected member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L125 _protected member_ `TSharedPtr<UE::Geometry::FGroupTopology> Topology;`
- L126 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> CurrentMesh;`
- L127 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> MeshSpatial;`
- L130 _protected member_ `TObjectPtr<MeshPartition::UStitchToolActions> EditActions = nullptr;` — `UPROPERTY()`
- L132 _protected member_ `FTransform WorldTransform;`
- L134 _protected member_ `UE::Geometry::FFrame3d ActiveSelectionFrameLocal;`
- L135 _protected member_ `UE::Geometry::FFrame3d ActiveSelectionFrameWorld;`
- L136 _protected member_ `TArray<int32> ActiveTriangleSelection;`
- L137 _protected member_ `UE::Geometry::FAxisAlignedBox3d ActiveSelectionBounds;`
- L143 _protected member_ `TArray<FSelectedEdge> ActiveEdgeSelection;`
- L145 _protected member_ `MeshPartition::EStitchToolActions PendingAction = MeshPartition::EStitchToolActions::NoAction;`
- L147 _protected member_ `bool bSpatialDirty = true;`
- L148 _protected member_ `bool bSelectionStateDirty = true;`

#### struct `UE::MeshPartition::UStitchTool::FSelectedEdge`  
`struct FSelectedEdge`  
_L138-142_
- L140 _public member_ `int32 EdgeTopoID;`
- L141 _public member_ `TArray<int32> EdgeIDs;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L15 _prototype_ `PREDECLARE_GEOMETRY(struct FGroupTopologySelection);`
- L16 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L17 _prototype_ `PREDECLARE_GEOMETRY(class FGroupTopology);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionModelingToolset/Public/MeshPartitionToolTarget.h` (Public)


#### class `UE::MeshPartition::UMeshPartitionToolTarget`  
`class UMeshPartitionToolTarget : public UPrimitiveComponentToolTarget, public IDynamicMeshProvider, public IDynamicMeshCommitter, public IMaterialProvider, public IPhysicsDataSource`  
_L28-70_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UPrimitiveComponentToolTarget,IDynamicMeshProvider,IDynamicMeshCommitter,IMaterialProvider,IPhysicsDataSource`
- desc: UToolTarget specialization that supports a entire AMeshPartition actor and its corresponding UMeshPartitionEditorComponent. A specialized per-section target is available in UMegaMeshSectionTooLTarget.
- L38 _public prototype_ `void Initialize(UMeshPartitionEditorComponent* InEditorComponent);`
- L41 _public prototype_ `virtual Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider implementation
- L44 _public prototype_ `virtual void CommitDynamicMesh(const Geometry::FDynamicMesh3& InMesh, const FDynamicMeshCommitInfo& InCommitInfo) override;` — IDynamicMeshCommitter implementation
- L48 _public prototype_ `int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L49 _public prototype_ `UMaterialInterface* GetMaterial(int32 InMaterialIndex) const override;`
- L50 _public prototype_ `void GetMaterialSet(FComponentMaterialSet& OutMaterialSet, bool bInPreferAssetMaterials) const override;`
- L51 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& InMaterialSet, bool bInApplyToAsset) override;`
- L54 _public prototype_ `virtual UBodySetup* GetBodySetup() const override;` — IPhysicsDataSource implementation
- L55 _public prototype_ `virtual IInterface_CollisionDataProvider* GetComplexCollisionProvider() const override;`
- L58 _public prototype_ `virtual void SetOwnerVisibility(bool bInVisible) const override;` — UPrimitiveComponentToolTarget
- L59 _public prototype_ `virtual FTransform GetWorldTransform() const override;`
- L62 _protected prototype_ `Geometry::FDynamicMesh3 BuildMergedMesh();`
- L63 _protected prototype_ `void SplitMeshesToSections(const Geometry::FDynamicMesh3& InMesh);`
- L66 _protected member_ `TArray<MeshPartition::UMeshProviderModifier*> MeshModifiers;`
- L68 _protected member_ `FTransform TargetTransform;` — Cached world frame for the merged mesh
- L69 _protected member_ `bool bIsMeshModifiersInitialized = false;`

#### class `UE::MeshPartition::UMeshPartitionToolTargetFactory`  
`class UMeshPartitionToolTargetFactory : public UToolTargetFactory`  
_L75-83_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UToolTargetFactory`
- L80 _public prototype_ `virtual bool CanBuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InRequirements) const override;`
- L82 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* InSourceObject, const FToolTargetTypeRequirements& InRequirements) override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHPARTITIONMODELINGTOOLSET_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)
