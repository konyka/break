# Plugins / MeshModelingTools

- module root: `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools`
- headers: 64; symbols: 4103
- symbol kinds: class=272, delegate=5, enum=95, enumerator=409, function=572, macro=45, member=1550, namespace=22, prototype=1107, struct=14, typedef=12
- PrivateDependencyModuleNames: CoreUObject, Engine, SlateCore
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, MeshConversion, MeshDescription, ModelingComponents, ModelingOperators, StaticMeshDescription

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Private/ToolActivities/PolyEditBevelEdgeActivity.h` (Private)


#### class `UPolyEditBevelEdgeProperties`  
`class UPolyEditBevelEdgeProperties : public UInteractiveToolPropertySet`  
_L25-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L32 _public member_ `double BevelDistance = 4.0;` — `UPROPERTY(EditAnywhere, Category = Bevel, meta = (UIMin = ".001", UIMax = "100", ClampMin = "0.0001", ClampMax = "10000", SliderExponent = "3", ModelingQuickEdit))` — Distance that each beveled mesh edge is inset from its initial position
- L36 _public member_ `int Subdivisions = 0;` — `UPROPERTY(EditAnywhere, Category = Bevel, meta=(UIMax="10", ClampMin="0", ClampMax="1000"))` — Number of edge loops added along the bevel faces
- L40 _public member_ `float RoundWeight = 1.0;` — `UPROPERTY(EditAnywhere, Category = Bevel, meta = (UIMin = "-2", UIMax="2"))` — Roundness of the bevel. Ignored if Subdivisions = 0.
- L44 _public member_ `bool bInferMaterialID = true;` — `UPROPERTY(EditAnywhere, Category = Bevel)` — If true, when faces on either side of a beveled mesh edges have the same Material ID, beveled edge will be set to that Material ID. Otherwise SetMaterialID is used.
- L48 _public member_ `int SetMaterialID = 0;` — `UPROPERTY(EditAnywhere, Category = Bevel, meta = (ClampMin="0", NoSpinbox))` — Material ID to set on the new faces introduced by bevel operation, unless bInferMaterialID=true and non-ambiguous MaterialID can be inferred from adjacent faces

#### class `UPolyEditBevelEdgeActivity`  
`class UPolyEditBevelEdgeActivity : public UInteractiveToolActivity, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L56-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolActivity,UE::Geometry::IDynamicMeshOperatorFactory`
- L65 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L66 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L67 _public prototype_ `virtual bool CanStart() const override;`
- L68 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L69 _public function_ `virtual bool IsRunning() const override`
- L70 _public function_ `virtual bool HasAccept() const override`
- L71 _public prototype_ `virtual bool CanAccept() const override;`
- L72 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L73 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L74 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L77 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L80 _public member_ `TObjectPtr<UPolyEditBevelEdgeProperties> BevelProperties = nullptr;` — `UPROPERTY()`
- L84 _protected prototype_ `virtual void BeginBevel();`
- L85 _protected prototype_ `virtual void ApplyBevel();`
- L86 _protected prototype_ `virtual void EndInternal();`
- L89 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L91 _protected member_ `bool bIsRunning = false;`
- L93 _protected member_ `UE::Geometry::FGroupTopologySelection ActiveSelection;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L20 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Private/ToolActivities/PolyEditExtrudeEdgeActivity.h` (Private)


#### enum `EPolyEditExtrudeEdgeDirectionMode`  
`enum class EPolyEditExtrudeEdgeDirectionMode`  
_L20-26_
- reflection: `UENUM()`
- L23 _public enumerator_ `LocalExtrudeFrames` — Each vertex gets its own local frame to extrude along.
- L25 _public enumerator_ `SingleDirection` — All vertices are extruded in the same direction

#### enum `EPolyEditExtrudeEdgeDistanceMode`  
`enum class EPolyEditExtrudeEdgeDistanceMode`  
_L30-36_
- reflection: `UENUM()`
- L33 _public enumerator_ `Fixed` — Sets the distance numerically using the Distance parameter.
- L35 _public enumerator_ `Gizmo` — Uses a gizmo attached to one of the vertices to determine distance to extrude.

#### class `UPolyEditExtrudeEdgeActivityProperties`  
`class UPolyEditExtrudeEdgeActivityProperties : public UInteractiveToolPropertySet`  
_L39-66_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L47 _public member_ `EPolyEditExtrudeEdgeDirectionMode DirectionMode = EPolyEditExtrudeEdgeDirectionMode::LocalExtrudeFrames;` — `UPROPERTY(EditAnywhere, Category = Extrude)` — How direction to move the vertices is determined.
- L51 _public member_ `EPolyEditExtrudeEdgeDistanceMode DistanceMode = EPolyEditExtrudeEdgeDistanceMode::Gizmo;` — `UPROPERTY(EditAnywhere, Category = Extrude)` — How distance to extrude along a given direction is determined.
- L55 _public member_ `double Distance = 20;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (EditCondition = "DistanceMode == EPolyEditExtrudeEdgeDistanceMode::Fixed", EditConditionHides, UIMin = "0", UIMax = "200", ClampMin = "-100000", ClampMax = "100000"))`
- L60 _public member_ `bool bUseUnselectedForFrames = false;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = ( EditCondition = "DirectionMode == EPolyEditExtrudeEdgeDirectionMode::LocalExtrudeFrames", EditConditionHides))` — When a vertex has both a selected and nonselected neighbor, use the unselected neighbor in picking an extrude frame as well.
- L65 _public member_ `bool bAdjustToExtrudeEvenly = false;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = ( EditCondition = "DirectionMode == EPolyEditExtrudeEdgeDirectionMode::LocalExtrudeFrames", EditConditionHides))` — Adjust individual extrude directions in an effort to make extruded edges parallel to their original edges.

#### class `UPolyEditExtrudeEdgeActivity`  
`class UPolyEditExtrudeEdgeActivity : public UInteractiveToolActivity, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L73-157_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolActivity,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Extrudes boundary edges.
- L80 _public typedef_ `using FFrame3d = UE::Geometry::FFrame3d;`
- L83 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L84 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L85 _public prototype_ `virtual bool CanStart() const override;`
- L86 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L87 _public function_ `virtual bool IsRunning() const override`
- L88 _public function_ `virtual bool HasAccept() const override`
- L89 _public prototype_ `virtual bool CanAccept() const override;`
- L90 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L91 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L92 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L95 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L99 _private member_ `TObjectPtr<UPolyEditExtrudeEdgeActivityProperties> Settings = nullptr;` — `UPROPERTY()`
- L102 _private member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L106 _private member_ `TObjectPtr<UTransformProxy> ExtrudeFrameProxy;` — `UPROPERTY()` — Support for gizmos.
- L108 _private member_ `TObjectPtr<UCombinedTransformGizmo> ExtrudeFrameGizmo;` — `UPROPERTY()`
- L110 _private member_ `TObjectPtr<UTransformProxy> SingleDirectionProxy;` — `UPROPERTY()`
- L112 _private member_ `TObjectPtr<UCombinedTransformGizmo> SingleDirectionGizmo;` — `UPROPERTY()`
- L117 _private member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry;` — `UPROPERTY()` — Used for drawing the boundaries of the new faces to make them look similar to the rest of the mesh.
- L119 _private member_ `bool bIsRunning = false;`
- L121 _private prototype_ `void ApplyExtrude();`
- L122 _private prototype_ `void EndInternal();`
- L124 _private member_ `UE::Geometry::FExtrudeBoundaryEdges::FExtrudeFrame ExtrudeFrameForGizmoMeshSpace;`
- L126 _private member_ `FFrame3d ExtrudeFrameForGizmoWorldSpace;`
- L129 _private member_ `FVector3d SingleDirectionVectorWorldSpace;` — These are the parameters we actually end up using, initialized from gizmos or detail panel.
- L130 _private member_ `FVector3d ParamsInWorldExtrudeFrame;`
- L132 _private prototype_ `void UpdateGizmosFromCurrentParams();`
- L133 _private prototype_ `void UpdateDistanceFromParams();`
- L134 _private prototype_ `void ConvertToNewDirectionMode(bool bToSingleDirection);`
- L135 _private prototype_ `void ResetParams();`
- L137 _private prototype_ `void RecalculateGizmoExtrudeFrame();`
- L138 _private prototype_ `void UpdateGizmoVisibility();`
- L140 _private member_ `UE::Geometry::FGroupTopologySelection ActiveSelection;`
- L141 _private member_ `bool bRevertedSelection = false;`
- L142 _private member_ `TArray<int32> SelectedEids;`
- L143 _private member_ `TArray<int32> GroupsToSetPerEid;`
- L144 _private prototype_ `void GatherSelectedEids();`
- L146 _private member_ `TArray<int32> EidsToRender;`
- L147 _private prototype_ `void UpdateDrawnPreviewEdges();`
- L149 _private member_ `TArray<int32> NewSelectionEids;`
- L152 _private member_ `FTransform CurrentMeshTransform;` — TODO: Might be worth having a getter in ActivityContext
- L156 _private member_ `bool bExtrudeDistanceWasNegative = false;` — This is helpful so that in our distance watcher, we know that the previous distance was negative, and therefore the extrude direction is actually opposite.

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/AddPrimitiveTool.h` (Public)


#### class `UAddPrimitiveToolBuilder`  
`class UAddPrimitiveToolBuilder : public UInteractiveToolBuilder`  
_L26-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: Builder
- L45 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L46 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L48 _public member_ `EMakeMeshShapeType ShapeType{EMakeMeshShapeType::Box};`

#### enum `UAddPrimitiveToolBuilder::EMakeMeshShapeType`  
`enum class EMakeMeshShapeType : uint32`  
_L31-43_
- L33 _public enumerator_ `Box`
- L34 _public enumerator_ `Cylinder`
- L35 _public enumerator_ `Cone`
- L36 _public enumerator_ `Arrow`
- L37 _public enumerator_ `Rectangle`
- L38 _public enumerator_ `Disc`
- L39 _public enumerator_ `Torus`
- L40 _public enumerator_ `Sphere`
- L41 _public enumerator_ `Stairs`
- L42 _public enumerator_ `Capsule`

#### enum `EMakeMeshPlacementType`  
`enum class EMakeMeshPlacementType : uint8`  
_L53-58_
- reflection: `UENUM()`
- desc: Placement Target Types
- L55 _public enumerator_ `GroundPlane = 0`
- L56 _public enumerator_ `OnScene = 1`
- L57 _public enumerator_ `AtOrigin = 2`

#### enum `EMakeMeshPivotLocation`  
`enum class EMakeMeshPivotLocation : uint8`  
_L62-67_
- reflection: `UENUM()`
- desc: Placement Pivot Location
- L64 _public enumerator_ `Base`
- L65 _public enumerator_ `Centered`
- L66 _public enumerator_ `Top`

#### enum `EMakeMeshPolygroupMode`  
`enum class EMakeMeshPolygroupMode : uint8`  
_L71-79_
- reflection: `UENUM()`
- desc: PolyGroup mode for shape
- L74 _public enumerator_ `PerShape` — One PolyGroup for the entire shape
- L76 _public enumerator_ `PerFace` — One PolyGroup for each geometric face
- L78 _public enumerator_ `PerQuad` — One PolyGroup for each quad/triangle

#### class `UProceduralShapeToolProperties`  
`class UProceduralShapeToolProperties : public UInteractiveToolPropertySet`  
_L82-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L90 _public member_ `EMakeMeshPolygroupMode PolygroupMode = EMakeMeshPolygroupMode::PerFace;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (ProceduralShapeSetting, DisplayName = "PolyGroup Mode"))` — How PolyGroups are assigned to shape primitives.
- L94 _public member_ `EMakeMeshPlacementType TargetSurface = EMakeMeshPlacementType::OnScene;` — `UPROPERTY(EditAnywhere, Category = Positioning, meta = (DisplayName = "Target Position"))` — How the shape is placed in the scene.
- L98 _public member_ `EMakeMeshPivotLocation PivotLocation = EMakeMeshPivotLocation::Base;` — `UPROPERTY(EditAnywhere, Category = Positioning, meta = (ProceduralShapeSetting))` — Location of pivot within the shape
- L102 _public member_ `float Rotation = 0.0;` — `UPROPERTY(EditAnywhere, Category = Positioning, DisplayName = "Initial Rotation", meta = (UIMin = "0.0", UIMax = "360.0", EditCondition = "!bShowGizmoOptions", HideEditConditionToggle))` — Initial rotation of the shape around its up axis, before placement. After placement, use the gizmo to control rotation.
- L106 _public member_ `bool bAlignToNormal = true;` — `UPROPERTY(EditAnywhere, Category = Positioning, meta = (EditCondition = "TargetSurface == EMakeMeshPlacementType::OnScene"))` — If true, aligns the shape along the normal of the surface it is placed on.
- L110 _public member_ `bool bShowGizmo = true;` — `UPROPERTY(EditAnywhere, Category = Positioning, meta = (EditCondition = "bShowGizmoOptions", EditConditionHides, HideEditConditionToggle))` — Show a gizmo to allow the mesh to be repositioned after the initial placement click.
- L114 _public member_ `bool bShowGizmoOptions = false;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UProceduralBoxToolProperties`  
`class UProceduralBoxToolProperties : public UProceduralShapeToolProperties`  
_L118-146_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L125 _public member_ `float Width = 100.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Width of the box
- L129 _public member_ `float Depth = 100.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Depth of the box
- L133 _public member_ `float Height = 100.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Height of the box
- L137 _public member_ `int WidthSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along the width
- L141 _public member_ `int DepthSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along the depth
- L145 _public member_ `int HeightSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along the height

#### enum `EProceduralRectType`  
`enum class EProceduralRectType`  
_L149-155_
- reflection: `UENUM()`
- L152 _public enumerator_ `Rectangle` — Create a rectangle
- L154 _public enumerator_ `RoundedRectangle` — Create a rounded rectangle

#### class `UProceduralRectangleToolProperties`  
`class UProceduralRectangleToolProperties : public UProceduralShapeToolProperties`  
_L158-198_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L165 _public member_ `EProceduralRectType RectangleType = EProceduralRectType::Rectangle;` — `UPROPERTY(EditAnywhere, Category = Shape)` — Type of rectangle
- L169 _public member_ `float Width = 100.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Width of the rectangle
- L173 _public member_ `float Depth = 100.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Depth of the rectangle
- L177 _public member_ `int WidthSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along the width
- L181 _public member_ `int DepthSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along the depth
- L185 _public member_ `bool bMaintainDimension = true;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (EditCondition = "RectangleType == EProceduralRectType::RoundedRectangle"))` — Whether to preserve the overall Width and Depth for a Rounded Rectangle, or to allow the rounded corners to extend outside those dimensions.
- L191 _public member_ `float CornerRadius = 25.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting, EditCondition = "RectangleType == EProceduralRectType::RoundedRectangle"))` — Radius of rounded corners. This is only available for Rounded Rectangles.
- L197 _public member_ `int CornerSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "128", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting, EditCondition = "RectangleType == EProceduralRectType::RoundedRectangle"))` — Number of radial slices for each rounded corner. This is only available for Rounded Rectangles.

#### enum `EProceduralDiscType`  
`enum class EProceduralDiscType`  
_L201-207_
- reflection: `UENUM()`
- L204 _public enumerator_ `Disc` — Create a disc
- L206 _public enumerator_ `PuncturedDisc` — Create a disc with a hole

#### class `UProceduralDiscToolProperties`  
`class UProceduralDiscToolProperties : public UProceduralShapeToolProperties`  
_L210-236_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L217 _public member_ `EProceduralDiscType DiscType = EProceduralDiscType::Disc;` — `UPROPERTY(EditAnywhere, Category = Shape)` — Type of disc
- L221 _public member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Radius of the disc
- L225 _public member_ `int RadialSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "128", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting))` — Number of radial slices for the disc
- L229 _public member_ `int RadialSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of radial subdivisions for each radial slice of the disc
- L235 _public member_ `float HoleRadius = 25.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting, EditCondition = "DiscType == EProceduralDiscType::PuncturedDisc"))` — Radius of the hole in the disc. This is only available for Punctured Discs.

#### class `UProceduralTorusToolProperties`  
`class UProceduralTorusToolProperties : public UProceduralShapeToolProperties`  
_L239-259_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L246 _public member_ `float MajorRadius = 50.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Major radius of the torus, measured from the torus center to the center of the torus tube
- L250 _public member_ `float MinorRadius = 25.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Minor radius of the torus, measured from the center ot the torus tube to the tube surface
- L254 _public member_ `int MajorSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "128", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting))` — Number of radial slices along the torus tube
- L258 _public member_ `int MinorSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "128", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting))` — Number of radial slices around the torus tube

#### class `UProceduralCylinderToolProperties`  
`class UProceduralCylinderToolProperties : public UProceduralShapeToolProperties`  
_L262-283_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L270 _public member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Radius of the cylinder
- L274 _public member_ `float Height = 200.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Height of the cylinder
- L278 _public member_ `int RadialSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "128", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting))` — Number of radial slices for the cylinder
- L282 _public member_ `int HeightSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along the height of the cylinder

#### class `UProceduralConeToolProperties`  
`class UProceduralConeToolProperties : public UProceduralShapeToolProperties`  
_L286-306_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L293 _public member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Radius of the cone
- L297 _public member_ `float Height = 200.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Height of the cone
- L301 _public member_ `int RadialSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "128", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting))` — Number of radial slices for the cone
- L305 _public member_ `int HeightSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along the height of the cone

#### class `UProceduralArrowToolProperties`  
`class UProceduralArrowToolProperties : public UProceduralShapeToolProperties`  
_L309-337_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L316 _public member_ `float ShaftRadius = 20.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Radius of the arrow shaft
- L320 _public member_ `float ShaftHeight = 200.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Height of arrow shaft
- L324 _public member_ `float HeadRadius = 60.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Radius of the arrow head base
- L328 _public member_ `float HeadHeight = 120.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Height of arrow head
- L332 _public member_ `int RadialSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "100", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting))` — Number of radial slices for the arrow
- L336 _public member_ `int HeightSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting))` — Number of subdivisions along each part of the arrow, i.e. shaft, head base, head cone

#### enum `EProceduralSphereType`  
`enum class EProceduralSphereType`  
_L340-346_
- reflection: `UENUM()`
- L343 _public enumerator_ `LatLong` — Create a Sphere with Lat Long parameterization
- L345 _public enumerator_ `Box` — Create a Sphere with Box parameterization

#### class `UProceduralSphereToolProperties`  
`class UProceduralSphereToolProperties : public UProceduralShapeToolProperties`  
_L349-376_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L356 _public member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Radius of the sphere
- L360 _public member_ `EProceduralSphereType SubdivisionType = EProceduralSphereType::Box;` — `UPROPERTY(EditAnywhere, Category = Shape)` — Type of subdivision for the sphere
- L365 _public member_ `int Subdivisions = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "500", ProceduralShapeSetting, EditCondition = "SubdivisionType == EProceduralSphereType::Box"))` — Number of subdivisions for each side of the sphere. This is only available for spheres with Box subdivision.
- L370 _public member_ `int HorizontalSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "100", ClampMin = "4", ClampMax = "500", ProceduralShapeSetting, EditCondition = "SubdivisionType == EProceduralSphereType::LatLong"))` — Number of horizontal slices of the sphere. This is only available for spheres with Lat Long subdivision.
- L375 _public member_ `int VerticalSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "100", ClampMin = "4", ClampMax = "500", ProceduralShapeSetting, EditCondition = "SubdivisionType == EProceduralSphereType::LatLong"))` — Number of vertical slices of the sphere. This is only available for spheres with Lat Long subdivision.

#### class `UProceduralCapsuleToolProperties`  
`class UProceduralCapsuleToolProperties : public UProceduralShapeToolProperties`  
_L379-403_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L386 _public member_ `float Radius = 25.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Radius of the capsule
- L390 _public member_ `float CylinderLength = 50.f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Length of cylindrical section of the capsule
- L394 _public member_ `int HemisphereSlices = 8;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "2", UIMax = "100", ClampMin = "2", ClampMax = "500", ProceduralShapeSetting))` — Number of slices of the hemispherical end caps.
- L398 _public member_ `int CylinderSlices = 16;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "100", ClampMin = "3", ClampMax = "500", ProceduralShapeSetting))` — Number of radial slices of the cylindrical section.
- L402 _public member_ `int CylinderSubdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "500", ProceduralShapeSetting))` — Number of lengthwise subdivisions along cylindrical section

#### enum `EProceduralStairsType`  
`enum class EProceduralStairsType`  
_L406-416_
- reflection: `UENUM()`
- L409 _public enumerator_ `Linear` — Create a linear staircase
- L411 _public enumerator_ `Floating` — Create a floating staircase
- L413 _public enumerator_ `Curved` — Create a curved staircase
- L415 _public enumerator_ `Spiral` — Create a spiral staircase

#### class `UProceduralStairsToolProperties`  
`class UProceduralStairsToolProperties : public UProceduralShapeToolProperties`  
_L419-463_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralShapeToolProperties`
- L426 _public member_ `EProceduralStairsType StairsType = EProceduralStairsType::Linear;` — `UPROPERTY(EditAnywhere, Category = Shape)` — Type of staircase
- L430 _public member_ `int NumSteps = 8;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (DisplayName = "Number of Steps", UIMin = "2", UIMax = "100", ClampMin = "2", ClampMax = "1000000", ProceduralShapeSetting))` — Number of steps
- L434 _public member_ `float StepWidth = 150.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Width of each step
- L438 _public member_ `float StepHeight = 20.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting))` — Height of each step
- L444 _public member_ `float StepDepth = 30.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting, EditCondition = "StairsType == EProceduralStairsType::Linear || StairsType == EProceduralStairsType::Floating"))` — Depth of each step of linear stairs
- L450 _public member_ `float CurveAngle = 90.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "-360.0", UIMax = "360.0", ClampMin = "-360.0", ClampMax = "360.0", ProceduralShapeSetting, EditCondition = "StairsType == EProceduralStairsType::Curved"))` — Angular length of curved stairs. Positive values are for clockwise and negative values are for counterclockwise.
- L456 _public member_ `float SpiralAngle = 90.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "-720.0", UIMax = "720.0", ClampMin = "-360000.0", ClampMax = "360000.0", ProceduralShapeSetting, EditCondition = "StairsType == EProceduralStairsType::Spiral"))` — Angular length of spiral stairs. Positive values are for clockwise and negative values are for counterclockwise.
- L462 _public member_ `float InnerRadius = 150.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0", ProceduralShapeSetting, EditCondition = "StairsType == EProceduralStairsType::Curved || StairsType == EProceduralStairsType::Spiral"))` — Inner radius of curved and spiral stairs

#### class `UAddPrimitiveTool`  
`class UAddPrimitiveTool : public USingleClickTool, public IHoverBehaviorTarget, public IInteractiveToolCameraFocusAPI`  
_L470-581_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickTool,IHoverBehaviorTarget,IInteractiveToolCameraFocusAPI`
- desc: Base tool to create primitives
- L475 _public prototype_ `explicit UAddPrimitiveTool(const FObjectInitializer&);`
- L477 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L479 _public prototype_ `virtual void Setup() override;`
- L480 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L482 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L484 _public function_ `virtual bool HasCancel() const override`
- L485 _public function_ `virtual bool HasAccept() const override`
- L486 _public prototype_ `virtual bool CanAccept() const override;`
- L488 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L491 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;` — USingleClickTool
- L492 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L495 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget interface
- L496 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L497 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L498 _public prototype_ `virtual void OnEndHover() override;`
- L501 _public prototype_ `virtual bool SupportsWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L502 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L503 _public prototype_ `virtual bool SupportsWorldSpaceFocusPoint() override;`
- L504 _public prototype_ `virtual bool GetWorldSpaceFocusPoint(const FRay& WorldRay, FVector& PointOut) override;`
- L508 _protected function_ `virtual EMakeMeshPolygroupMode GetDefaultPolygroupMode() const`
- L516 _protected member_ `EState CurrentState = EState::PlacingPrimitive;`
- L517 _protected prototype_ `void SetState(EState NewState);`
- L519 _protected function_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const`
- L520 _protected function_ `virtual UProceduralShapeToolProperties* CreateShapeSettings()`
- L522 _protected prototype_ `virtual void GenerateAsset();`
- L526 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()` — Property set for type of output object (StaticMesh, Volume, etc)
- L529 _protected member_ `TObjectPtr<UProceduralShapeToolProperties> ShapeSettings;` — `UPROPERTY()`
- L532 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties;` — `UPROPERTY()`
- L535 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L538 _protected member_ `TObjectPtr<UCombinedTransformGizmo> Gizmo = nullptr;` — `UPROPERTY()`
- L541 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L544 _protected member_ `FString AssetName = TEXT("Gen` — `UPROPERTY()`
- L546 _protected member_ `UWorld* TargetWorld;`
- L548 _protected prototype_ `void UpdatePreviewPosition(const FInputDeviceRay& ClickPos);`
- L549 _protected member_ `UE::Geometry::FFrame3d ShapeFrame;`
- L551 _protected prototype_ `void UpdatePreviewMesh() const;`
- L553 _protected prototype_ `void UpdateTargetSurface();`
- L556 _protected function_ `virtual bool ShouldCenterXY() const` — @return true if the primitive needs to be centered in the XY plane when placed.

#### enum `UAddPrimitiveTool::EState`  
`enum class EState`  
_L510-514_
- L512 _public enumerator_ `PlacingPrimitive`
- L513 _public enumerator_ `AdjustingSettings`

#### class `UAddPrimitiveTool::FStateChange`  
`class FStateChange : public FToolCommandChange`  
_L563-580_
- inherits: `FToolCommandChange`
- desc: Used to make the initial placement of the mesh undoable
- L566 _public function_ `FStateChange(const FTransform& MeshTransformIn) : MeshTransform(MeshTransformIn)`
- L571 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L572 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L573 _public function_ `virtual FString ToString() const override`
- L579 _protected member_ `FTransform MeshTransform;`

#### class `UAddBoxPrimitiveTool`  
`class UAddBoxPrimitiveTool : public UAddPrimitiveTool`  
_L585-592_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L589 _public prototype_ `explicit UAddBoxPrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L591 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddCylinderPrimitiveTool`  
`class UAddCylinderPrimitiveTool : public UAddPrimitiveTool`  
_L595-602_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L599 _public prototype_ `explicit UAddCylinderPrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L601 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddCapsulePrimitiveTool`  
`class UAddCapsulePrimitiveTool : public UAddPrimitiveTool`  
_L605-612_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L609 _public prototype_ `explicit UAddCapsulePrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L611 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddConePrimitiveTool`  
`class UAddConePrimitiveTool : public UAddPrimitiveTool`  
_L615-622_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L619 _public prototype_ `explicit UAddConePrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L621 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddRectanglePrimitiveTool`  
`class UAddRectanglePrimitiveTool : public UAddPrimitiveTool`  
_L625-632_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L629 _public prototype_ `explicit UAddRectanglePrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L631 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddDiscPrimitiveTool`  
`class UAddDiscPrimitiveTool : public UAddPrimitiveTool`  
_L635-643_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L639 _public prototype_ `explicit UAddDiscPrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L640 _public prototype_ `virtual void Setup() override;`
- L642 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddTorusPrimitiveTool`  
`class UAddTorusPrimitiveTool : public UAddPrimitiveTool`  
_L646-653_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L650 _public prototype_ `explicit UAddTorusPrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L652 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddArrowPrimitiveTool`  
`class UAddArrowPrimitiveTool : public UAddPrimitiveTool`  
_L656-663_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L660 _public prototype_ `explicit UAddArrowPrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L662 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddSpherePrimitiveTool`  
`class UAddSpherePrimitiveTool : public UAddPrimitiveTool`  
_L666-677_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L670 _public prototype_ `explicit UAddSpherePrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L672 _protected function_ `virtual EMakeMeshPolygroupMode GetDefaultPolygroupMode() const override`
- L676 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`

#### class `UAddStairsPrimitiveTool`  
`class UAddStairsPrimitiveTool : public UAddPrimitiveTool`  
_L680-691_
- reflection: `UCLASS()`
- inherits: `UAddPrimitiveTool`
- L684 _public prototype_ `explicit UAddStairsPrimitiveTool(const FObjectInitializer& ObjectInitializer);`
- L686 _protected prototype_ `virtual void GenerateMesh(FDynamicMesh3* OutMesh) const override;`
- L687 _protected function_ `virtual bool ShouldCenterXY() const override`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L18 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/CSGMeshesTool.h` (Public)


#### class `UCSGMeshesToolProperties`  
`class UCSGMeshesToolProperties : public UInteractiveToolPropertySet`  
_L23-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the CSG operation
- L29 _public member_ `ECSGOperation Operation = ECSGOperation::DifferenceAB;` — `UPROPERTY(EditAnywhere, Category = Boolean)` — Type of Boolean operation
- L33 _public member_ `bool bTryFixHoles = false;` — `UPROPERTY(EditAnywhere, Category = Boolean, AdvancedDisplay)` — Try to fill holes created by the Boolean operation, e.g. due to numerical errors
- L37 _public member_ `bool bTryCollapseEdges = true;` — `UPROPERTY(EditAnywhere, Category = Boolean, AdvancedDisplay)` — Try to collapse extra edges created by the Boolean operation
- L41 _public member_ `float WindingThreshold = 0.5;` — `UPROPERTY(EditAnywhere, Category = Boolean, AdvancedDisplay, meta = (UIMin = "0", UIMax = "1"))` — Threshold to determine whether a triangle in one mesh is inside or outside of the other
- L45 _public member_ `bool bShowNewBoundaries = true;` — `UPROPERTY(EditAnywhere, Category = Display)` — Show boundary edges created by the Boolean operation, which might happen due to numerical errors
- L49 _public member_ `bool bShowSubtractedMesh = true;` — `UPROPERTY(EditAnywhere, Category = Display, meta = (EditCondition = "Operation == ECSGOperation::DifferenceAB || Operation == ECSGOperation::DifferenceBA"))` — Show a translucent version of the subtracted mesh, to help visualize geometry that is being removed
- L54 _public member_ `float SubtractedMeshOpacity = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Display, meta = (DisplayName = "Opacity Subtracted Mesh", ClampMin = "0", ClampMax = "1", EditCondition = "bShowSubtractedMesh && Operation == ECSGOperation::DifferenceAB || bShowSubtractedMesh && Operation == ECSGOperation::DifferenceBA"))` — Opacity of the translucent subtracted mesh
- L59 _public member_ `FLinearColor SubtractedMeshColor = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = Display, meta = (DisplayName = "Color Subtracted Mesh", HideAlphaChannel, ClampMin = "0", ClampMax = "1", EditCondition = "bShowSubtractedMesh && Operation == ECSGOperation::DifferenceAB || bShowSubtractedMesh && Operation == ECSGOperation::DifferenceBA"))` — Color of the translucent subtracted mesh
- L63 _public member_ `bool bUseFirstMeshMaterials = false;` — `UPROPERTY(EditAnywhere, Category = Materials)` — If true, only the first mesh will keep its material assignments, and all other faces will have the first material assigned

#### class `UTrimMeshesToolProperties`  
`class UTrimMeshesToolProperties : public UInteractiveToolPropertySet`  
_L71-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties of the trim mode
- L77 _public member_ `ETrimOperation WhichMesh = ETrimOperation::TrimA;` — `UPROPERTY(EditAnywhere, Category = Operation)` — Which object to trim
- L81 _public member_ `ETrimSide TrimSide = ETrimSide::RemoveInside;` — `UPROPERTY(EditAnywhere, Category = Operation)` — Whether to remove the surface inside or outside of the trimming geometry
- L85 _public member_ `float WindingThreshold = 0.5;` — `UPROPERTY(EditAnywhere, Category = Operation, AdvancedDisplay, meta = (UIMin = "0", UIMax = "1"))` — Threshold to determine whether a triangle in one mesh is inside or outside of the other
- L89 _public member_ `bool bShowTrimmingMesh = true;` — `UPROPERTY(EditAnywhere, Category = Display)` — Whether to show a translucent version of the trimming mesh, to help visualize what is being cut
- L93 _public member_ `float OpacityOfTrimmingMesh = .2f;` — `UPROPERTY(EditAnywhere, Category = Display, meta = (EditCondition = "bShowTrimmingMesh", ClampMin = "0", ClampMax = "1"))` — Opacity of translucent version of the trimming mesh
- L97 _public member_ `FLinearColor ColorOfTrimmingMesh = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = Display, meta = (EditCondition = "bShowTrimmingMesh"), AdvancedDisplay)` — Color of translucent version of the trimming mesh

#### class `UCSGMeshesTool`  
`class UCSGMeshesTool : public UBaseCreateFromSelectedTool`  
_L106-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedTool`
- desc: Simple Mesh Plane Cutting Tool
- L112 _public function_ `UCSGMeshesTool()`
- L114 _public prototype_ `void EnableTrimMode();`
- L118 _protected prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L120 _protected prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L122 _protected prototype_ `virtual void ConvertInputsAndSetPreviewMaterials(bool bSetPreviewMesh = true) override;`
- L124 _protected prototype_ `virtual void SetupProperties() override;`
- L125 _protected prototype_ `virtual void SaveProperties() override;`
- L126 _protected prototype_ `virtual void SetPreviewCallbacks() override;`
- L128 _protected prototype_ `virtual FString GetCreatedAssetName() const;`
- L129 _protected prototype_ `virtual FText GetActionName() const;`
- L132 _protected prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L134 _protected prototype_ `void UpdateVisualization();`
- L137 _protected member_ `TObjectPtr<UCSGMeshesToolProperties> CSGProperties;` — `UPROPERTY()`
- L140 _protected member_ `TObjectPtr<UTrimMeshesToolProperties> TrimProperties;` — `UPROPERTY()`
- L142 _protected member_ `TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>> OriginalDynamicMeshes;`
- L145 _protected member_ `TArray<TObjectPtr<UPreviewMesh>> OriginalMeshPreviews;` — `UPROPERTY()`
- L149 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewsGhostMaterial;` — `UPROPERTY()` — Material used to show the otherwise-invisible cutting/trimming mesh
- L152 _protected member_ `TObjectPtr<ULineSetComponent> DrawnLineSet;` — `UPROPERTY()`
- L155 _protected member_ `TArray<int> CreatedBoundaryEdges;` — for visualization of any errors in the currently-previewed CSG operation
- L157 _protected member_ `bool bTrimMode = false;`
- L159 _protected prototype_ `virtual int32 GetHiddenGizmoIndex() const;`
- L162 _protected prototype_ `void UpdatePreviewsVisibility();` — Update visibility of ghostly preview meshes (used to show trimming or subtracting surface)
- L165 _protected prototype_ `void UpdatePreviewsMaterial();` — update the material of ghostly preview meshes (used to show trimming or subtracting surface)
- L167 _protected function_ `virtual bool KeepCollisionFrom(int32 TargetIdx) const override`

#### class `UCSGMeshesToolBuilder`  
`class UCSGMeshesToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L187-214_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L193 _public member_ `bool bTrimMode = false;`
- L195 _public function_ `virtual TOptional<int32> MaxComponentsSupported() const override`
- L200 _public function_ `virtual int32 MinComponentsSupported() const override`
- L205 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L16 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);` — Forward declarations

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/CombineMeshesTool.h` (Public)


#### class `UCombineMeshesToolBuilder`  
`class UCombineMeshesToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L25-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L30 _public member_ `bool bIsDuplicateTool = false;`
- L32 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L33 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L36 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UCombineMeshesToolProperties`  
`class UCombineMeshesToolProperties : public UInteractiveToolPropertySet`  
_L45-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Common properties
- L51 _public member_ `bool bIsDuplicateMode = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L56 _public member_ `EBaseCreateFromSelectedTargetType OutputWriteTo = EBaseCreateFromSelectedTargetType::NewObject;` — `UPROPERTY(EditAnywhere, Category = OutputObject, meta = (DisplayName = "Write To", EditCondition = "bIsDuplicateMode == false", EditConditionHides, HideEditConditionToggle))` — Defines the object the tool output is written to.
- L61 _public member_ `FString OutputNewName;` — `UPROPERTY(EditAnywhere, Category = OutputObject, meta = (TransientToolProperty, DisplayName = "Name", EditCondition = "bIsDuplicateMode || OutputWriteTo == EBaseCreateFromSelectedTargetType::NewObject", EditConditionHides, NoResetToDefault))` — Base name of the newly generated object to which the output is written to.
- L66 _public member_ `FString OutputExistingName;` — `UPROPERTY(VisibleAnywhere, Category = OutputObject, meta = (TransientToolProperty, DisplayName = "Name", EditCondition = "bIsDuplicateMode == false && OutputWriteTo != EBaseCreateFromSelectedTargetType::NewObject", EditConditionHides, NoResetToDefault))` — Name of the existing object to which the output is written to.

#### class `UCombineMeshesTool`  
`class UCombineMeshesTool : public UMultiSelectionMeshEditingTool,`  
_L74-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolExclusiveToolAPI`
- desc: Simple tool to combine multiple meshes into a single mesh asset
- L82 _public prototype_ `virtual void SetDuplicateMode(bool bDuplicateMode);`
- L84 _public prototype_ `virtual void Setup() override;`
- L85 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L87 _public function_ `virtual bool HasCancel() const override`
- L88 _public function_ `virtual bool HasAccept() const override`
- L93 _protected member_ `TObjectPtr<UCombineMeshesToolProperties> BasicProperties;` — `UPROPERTY()`
- L96 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()`
- L99 _protected member_ `TObjectPtr<UOnAcceptHandleSourcesPropertiesBase> HandleSourceProperties;` — `UPROPERTY()`
- L101 _protected member_ `bool bDuplicateMode;`
- L103 _protected prototype_ `void CreateNewAsset();`
- L104 _protected prototype_ `void UpdateExistingAsset();`
- L106 _protected prototype_ `void BuildCombinedMaterialSet(TArray<UMaterialInterface*>& NewMaterialsOut, TArray<TArray<int32>>& MaterialIDRemapsOut);`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Commands/DeleteGeometrySelectionCommand.h` (Public)


#### class `UDeleteGeometrySelectionCommand`  
`class UDeleteGeometrySelectionCommand : public UGeometrySelectionEditCommand`  
_L17-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGeometrySelectionEditCommand`
- desc: UDeleteGeometrySelectionCommand deletes the geometric elements identified by the Selection. Currently only supports mesh selections (Triangle and Polygroup types) Deletes selected faces, or faces connected to selected edges, or faces connected to selected vertices.
- L22 _public prototype_ `virtual FText GetCommandShortString() const override;`
- L24 _public prototype_ `virtual bool CanExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments) override;`
- L25 _public prototype_ `virtual void ExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments, UInteractiveCommandResult** Result) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Commands/DisconnectGeometrySelectionCommand.h` (Public)


#### class `UDisconnectGeometrySelectionCommand`  
`class UDisconnectGeometrySelectionCommand : public UGeometrySelectionEditCommand`  
_L17-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGeometrySelectionEditCommand`
- desc: UDisconnectGeometrySelectionCommand disconnects the geometric elements identified by the Selection. Currently only supports mesh selections (Triangle and Polygroup types) Disconnects selected faces, or faces connected to selected edges, or faces connected to selected vertices.
- L22 _public prototype_ `virtual FText GetCommandShortString() const override;`
- L24 _public prototype_ `virtual bool CanExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments) override;`
- L25 _public prototype_ `virtual void ExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments, UInteractiveCommandResult** Result) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Commands/ModifyGeometrySelectionCommand.h` (Public)


#### class `UModifyGeometrySelectionCommand`  
`class UModifyGeometrySelectionCommand : public UGeometrySelectionEditCommand`  
_L17-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGeometrySelectionEditCommand`
- desc: UModifyGeometrySelectionCommand updates/edits the current selection in various ways. Default operation is to Select All. Subclasses below can be used in situations where specific per-modification types are needed.
- L33 _public function_ `virtual EModificationType GetModificationType() const`
- L35 _public function_ `virtual bool AllowEmptySelection() const override`
- L37 _public function_ `virtual bool IsModifySelectionCommand() const override`
- L38 _public prototype_ `virtual FText GetCommandShortString() const override;`
- L40 _public prototype_ `virtual bool CanExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments) override;`
- L41 _public prototype_ `virtual void ExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments, UInteractiveCommandResult** Result) override;`

#### enum `UModifyGeometrySelectionCommand::EModificationType`  
`enum class EModificationType`  
_L22-32_
- L24 _public enumerator_ `SelectAll = 0`
- L25 _public enumerator_ `ExpandToConnected = 1`
- L27 _public enumerator_ `Invert = 10`
- L28 _public enumerator_ `InvertConnected = 11`
- L30 _public enumerator_ `Expand = 20`
- L31 _public enumerator_ `Contract = 21`

#### class `UModifyGeometrySelectionCommand_Invert`  
`class UModifyGeometrySelectionCommand_Invert : public UModifyGeometrySelectionCommand`  
_L49-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModifyGeometrySelectionCommand`
- desc: Command to Invert the current Selection
- L53 _public function_ `virtual EModificationType GetModificationType() const override`

#### class `UModifyGeometrySelectionCommand_ExpandToConnected`  
`class UModifyGeometrySelectionCommand_ExpandToConnected : public UModifyGeometrySelectionCommand`  
_L61-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModifyGeometrySelectionCommand`
- desc: Command to Expand the current Selection to all connected geometry
- L65 _public function_ `virtual EModificationType GetModificationType() const override`

#### class `UModifyGeometrySelectionCommand_InvertConnected`  
`class UModifyGeometrySelectionCommand_InvertConnected : public UModifyGeometrySelectionCommand`  
_L73-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModifyGeometrySelectionCommand`
- desc: Command to Invert the current Selection, only considering connected geometry
- L77 _public function_ `virtual EModificationType GetModificationType() const override`

#### class `UModifyGeometrySelectionCommand_Expand`  
`class UModifyGeometrySelectionCommand_Expand : public UModifyGeometrySelectionCommand`  
_L84-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModifyGeometrySelectionCommand`
- desc: Command to Expand the current Selection by a one-ring
- L88 _public function_ `virtual EModificationType GetModificationType() const override`

#### class `UModifyGeometrySelectionCommand_Contract`  
`class UModifyGeometrySelectionCommand_Contract : public UModifyGeometrySelectionCommand`  
_L95-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModifyGeometrySelectionCommand`
- desc: Command to Contract the current Selection by a one-ring
- L99 _public function_ `virtual EModificationType GetModificationType() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Commands/RetriangulateGeometrySelectionCommand.h` (Public)


#### class `URetriangulateGeometrySelectionCommand`  
`class URetriangulateGeometrySelectionCommand : public UGeometrySelectionEditCommand`  
_L15-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGeometrySelectionEditCommand`
- desc: URetriangulateGeometrySelectionCommand
- L20 _public function_ `virtual bool AllowEmptySelection() const override`
- L21 _public prototype_ `virtual FText GetCommandShortString() const override;`
- L23 _public prototype_ `virtual bool CanExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments) override;`
- L24 _public prototype_ `virtual void ExecuteCommandForSelection(UGeometrySelectionEditCommandArguments* Arguments, UInteractiveCommandResult** Result) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ConvertToPolygonsTool.h` (Public)


#### class `UConvertToPolygonsToolBuilder`  
`class UConvertToPolygonsToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L31-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionToolBuilder`
- L35 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState & SceneState) const override;`
- L36 _public function_ `virtual bool RequiresInputSelection() const override`
- L37 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EConvertToPolygonsMode`  
`enum class EConvertToPolygonsMode`  
_L44-62_
- reflection: `UENUM()`
- L47 _public enumerator_ `FaceNormalDeviation = 0 UMETA(DisplayName = "Face Normal Deviation")` — Convert based on Angle Tolerance between Face Normals
- L49 _public enumerator_ `FindPolygons = 1 UMETA(DisplayName = "Find Quads")` — Create Polygroups by merging triangle pairs into Quads
- L51 _public enumerator_ `FromMaterialIDs = 7 UMETA(DisplayName = "From Material IDs")` — Create PolyGroups based on Material IDs
- L53 _public enumerator_ `FromUVIslands = 2 UMETA(DisplayName = "From UV Islands")` — Create PolyGroups based on UV Islands
- L55 _public enumerator_ `FromNormalSeams = 3 UMETA(DisplayName = "From Hard Normal Seams")` — Create PolyGroups based on Hard Normal Seams
- L57 _public enumerator_ `FromConnectedTris = 4 UMETA(DisplayName = "From Connected Tris")` — Create Polygroups based on Connected Triangles
- L59 _public enumerator_ `FromFurthestPointSampling = 5 UMETA(DisplayName = "Furthest Point Sampling")` — Create Polygroups centered on well-spaced sample points, approximating a surface Voronoi diagram
- L61 _public enumerator_ `CopyFromLayer = 6 UMETA(DisplayName = "Copy From Layer")` — Copy from existing Polygroup Layer

#### enum `EPerTriangleAttributeType`  
`enum class EPerTriangleAttributeType`  
_L65-71_
- reflection: `UENUM()`
- L68 _public enumerator_ `Integer = 0 UMETA(DisplayName = "Int32")` — Create per-triangle integer attribute.
- L70 _public enumerator_ `Label = 1 UMETA(DisplayName = "FName")` — Create per-triangle label attribute.

#### class `UConvertToPolygonsToolProperties`  
`class UConvertToPolygonsToolProperties : public UInteractiveToolPropertySet`  
_L76-167_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L83 _public member_ `EConvertToPolygonsMode ConversionMode = EConvertToPolygonsMode::FaceNormalDeviation;` — `UPROPERTY(EditAnywhere, Category = PolyGroups)` — Strategy to use to group triangles
- L87 _public member_ `float AngleTolerance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = NormalDeviation, meta = (UIMin = "0.001", UIMax = "60.0", ClampMin = "0.0", ClampMax = "90.0", EditCondition = "ConversionMode == EConvertToPolygonsMode::FaceNormalDeviation", EditConditionHides))` — Tolerance for planarity
- L91 _public member_ `bool bUseAverageGroupNormal = true;` — `UPROPERTY(EditAnywhere, Category = NormalDeviation, meta = (EditCondition = "ConversionMode == EConvertToPolygonsMode::FaceNormalDeviation", EditConditionHides))` — Whether to compute Face Normal Deviation based on the overall PolyGroup's average normal, or to only consider the normals of the individual triangles
- L95 _public member_ `int32 NumPoints = 100;` — `UPROPERTY(EditAnywhere, Category = FurthestPoint, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "10000", EditCondition = "ConversionMode == EConvertToPolygonsMode::FromFurthestPointSampling", EditConditionHides))` — Furthest-Point Sample count, approximately this number of polygroups will be generated
- L99 _public member_ `bool bSplitExisting = false;` — `UPROPERTY(EditAnywhere, Category = FurthestPoint, meta = (EditCondition = "ConversionMode == EConvertToPolygonsMode::FromFurthestPointSampling", EditConditionHides))` — If enabled, then furthest-point sampling happens with respect to existing Polygroups, ie the existing groups are further subdivided
- L103 _public member_ `bool bNormalWeighted = true;` — `UPROPERTY(EditAnywhere, Category = FurthestPoint, meta = (EditCondition = "ConversionMode == EConvertToPolygonsMode::FromFurthestPointSampling", EditConditionHides))` — If true, region-growing in Sampling modes will be controlled by face normals, resulting in regions with borders that are more-aligned with curvature ridges
- L107 _public member_ `float NormalWeighting = 1.0f;` — `UPROPERTY(EditAnywhere, Category = FurthestPoint, meta = (UIMin = "0.1", UIMax = "2.0", ClampMin = "0.01", ClampMax = "100.0", EditCondition = "ConversionMode == EConvertToPolygonsMode::FromFurthestPointSampling", EditConditionHides))` — This parameter modulates the effect of normal weighting during region-growing
- L112 _public member_ `float QuadAdjacencyWeight = 1.0;` — `UPROPERTY(EditAnywhere, Category = FindQuads, meta = (UIMin = 0, UIMax = 5, EditCondition = "ConversionMode == EConvertToPolygonsMode::FindPolygons", EditConditionHides))` — Bias for Quads that are adjacent to already-discovered Quads. Set to 0 to disable.
- L116 _public member_ `float QuadMetricClamp = 1.0;` — `UPROPERTY(EditAnywhere, Category = FindQuads, meta = (AdvancedDisplay, UIMin = 0, UIMax = 1, EditCondition = "ConversionMode == EConvertToPolygonsMode::FindPolygons", EditConditionHides))` — Set to values below 1 to ignore less-likely triangle pairings
- L120 _public member_ `int QuadSearchRounds = 1;` — `UPROPERTY(EditAnywhere, Category = FindQuads, meta = (AdvancedDisplay, UIMin = 1, UIMax = 5, EditCondition = "ConversionMode == EConvertToPolygonsMode::FindPolygons", EditConditionHides))` — Iteratively repeat quad-searching in uncertain areas, to try to slightly improve results
- L124 _public member_ `bool bRespectUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Topology, meta = (EditCondition = "ConversionMode == EConvertToPolygonsMode::FaceNormalDeviation || ConversionMode == EConvertToPolygonsMode::FindPolygons", EditConditionHides))` — If true, polygroup borders will not cross existing UV seams
- L128 _public member_ `bool bRespectHardNormals = false;` — `UPROPERTY(EditAnywhere, Category = Topology, meta = (EditCondition = "ConversionMode == EConvertToPolygonsMode::FaceNormalDeviation || ConversionMode == EConvertToPolygonsMode::FindPolygons", EditConditionHides))` — If true, polygroup borders will not cross existing hard normal seams
- L133 _public member_ `int32 MinGroupSize = 2;` — `UPROPERTY(EditAnywhere, Category = Filtering, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "10000", EditCondition = "ConversionMode != EConvertToPolygonsMode::CopyFromLayer"))` — Minimum number of triangles to include in a group. Any group containing fewer triangles will be merged with an adjacent group (if possible).
- L137 _public member_ `bool bShowGroupColors = true;` — `UPROPERTY(EditAnywhere, Category = Display)` — Display each group with a different auto-generated color
- L141 _public member_ `bool bCalculateNormals = false;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (EditCondition = "ConversionMode != EConvertToPolygonsMode::CopyFromLayer"))` — If true, normals are recomputed per-group, with hard edges at group boundaries
- L145 _public member_ `FName GroupLayer = "De` — `UPROPERTY(EditAnywhere, Category = Output, meta = (DisplayName = "Output Layer", GetOptions = GetGroupOptionsList, NoResetToDefault))` — Select PolyGroup layer to use.
- L149 _public function_ `TArray<FString> GetGroupOptionsList()` — `UFUNCTION()` — Provides set of available group layers
- L153 _public member_ `TArray<FString> OptionsList;` — `UPROPERTY(meta = (TransientToolProperty))` — internal list used to implement above
- L156 _public member_ `bool bShowNewLayerName = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L161 _public member_ `FString NewLayerName = TEXT("pol` — `UPROPERTY(EditAnywhere, Category = Output, meta = (TransientToolProperty, DisplayName = "New Layer Name", EditCondition = "bShowNewLayerName", HideEditConditionToggle, NoResetToDefault))` — Name of the new Group Layer
- L166 _public member_ `EPerTriangleAttributeType LayerType = EPerTriangleAttributeType::Integer;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (TransientToolProperty, EditCondition = "bShowNewLayerName", HideEditConditionToggle, NoResetToDefault))` — Type of the new Group Layer

#### class `UConvertToPolygonsOperatorFactory`  
`class UConvertToPolygonsOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L173-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L179 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L182 _public member_ `TObjectPtr<UConvertToPolygonsTool> ConvertToPolygonsTool;` — `UPROPERTY()` — back pointer

#### class `UConvertToPolygonsTool`  
`class UConvertToPolygonsTool : public USingleTargetWithSelectionTool`  
_L189-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionTool`
- L194 _public prototype_ `UConvertToPolygonsTool();`
- L196 _public prototype_ `virtual void Setup() override;`
- L197 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L199 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L201 _public function_ `virtual bool HasCancel() const override`
- L202 _public function_ `virtual bool HasAccept() const override`
- L203 _public prototype_ `virtual bool CanAccept() const override;`
- L206 _public prototype_ `void UpdateOpParameters(FConvertToPolygonsOp& ConvertToPolygonsOp) const;` — update parameters in ConvertToPolygonsOp based on current Settings
- L210 _protected prototype_ `void OnSettingsModified();`
- L214 _protected member_ `TObjectPtr<UConvertToPolygonsToolProperties> Settings;` — `UPROPERTY()`
- L217 _protected member_ `TObjectPtr<UPolygroupLayersProperties> CopyFromLayerProperties = nullptr;` — `UPROPERTY()`
- L221 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> PreviewCompute = nullptr;` — `UPROPERTY()`
- L224 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry = nullptr;` — `UPROPERTY()`
- L229 _protected member_ `TObjectPtr<UPreviewMesh> UnmodifiedAreaPreviewMesh = nullptr;` — `UPROPERTY()` — If a selection was provided (bUsingSelection = true), UnmodifiedAreaPreviewMesh is used to render the unmodified (non-selected) part of the input mesh, as the PreviewCompute input mesh will be limited to the input selected area
- L233 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalDynamicMesh;` — copy of the input mesh (possibly does not need to be SharedPtr anymore now that FSharedConstDynamicMesh3 is used below, but then needs PimplPtr...)
- L236 _protected member_ `bool bUsingSelection = false;` — If there is an active selection, bUsingSelection will be true and the ROI and Submesh will be initialized
- L237 _protected member_ `TSharedPtr<TSet<int32>> SelectionTriangleROI;`
- L238 _protected member_ `TSharedPtr<UE::Geometry::FDynamicSubmesh3, ESPMode::ThreadSafe> OriginalSubmesh;`
- L241 _protected member_ `TSharedPtr<UE::Geometry::FSharedConstDynamicMesh3> ComputeOperatorSharedMesh;` — The mesh passed to the Compute operator to base result on, will either be OriginalDynamicMesh or the submesh from OriginalSubmesh if using a selection
- L244 _protected member_ `TArray<int> PolygonEdges;` — current set of detected polygroup edges, relative to ComputeOperatorSharedMesh
- L246 _protected prototype_ `void UpdateVisualization();`
- L249 _protected member_ `TSharedPtr<UE::Geometry::ITriangleGroupSetAdapter, ESPMode::ThreadSafe> ActiveFromGroupSetAdapter;` — current input group set used in CopyFromLayer mode, relative to ComputeOperatorSharedMesh
- L250 _protected prototype_ `void OnSelectedFromGroupLayerChanged();`
- L251 _protected prototype_ `void UpdateFromGroupLayer();`
- L254 _protected prototype_ `void DoUpdateMeshAttribute(const FDynamicMesh3& InMesh) const;` — updates the group layer data to the mesh

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/CutMeshWithMeshTool.h` (Public)


#### class `UCutMeshWithMeshToolProperties`  
`class UCutMeshWithMeshToolProperties : public UInteractiveToolPropertySet`  
_L23-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the CutMeshWithMesh operation
- L29 _public member_ `bool bTryFixHoles = false;` — `UPROPERTY(EditAnywhere, Category = Boolean)` — Try to fill holes created by the Boolean operation, e.g. due to numerical errors
- L33 _public member_ `bool bTryCollapseEdges = true;` — `UPROPERTY(EditAnywhere, Category = Boolean)` — Try to collapse extra edges created by the Boolean operation
- L37 _public member_ `float WindingThreshold = 0.5;` — `UPROPERTY(EditAnywhere, Category = Boolean, AdvancedDisplay, meta = (UIMin = "0", UIMax = "1"))` — Threshold to determine whether a triangle in one mesh is inside or outside of the other
- L41 _public member_ `bool bShowNewBoundaries = true;` — `UPROPERTY(EditAnywhere, Category = Display)` — Show boundary edges created by the Boolean operation, which might happen due to numerical errors
- L45 _public member_ `bool bUseFirstMeshMaterials = false;` — `UPROPERTY(EditAnywhere, Category = Materials)` — If true, only the first mesh will keep its material assignments, and all other faces will have the first material assigned

#### class `UCutMeshWithMeshTool`  
`class UCutMeshWithMeshTool : public UBaseCreateFromSelectedTool`  
_L56-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedTool`
- desc: UCutMeshWithMeshTool cuts an input mesh into two pieces based on a second input mesh. Essentially this just both a Boolean Subtract and a Boolean Intersection. However doing those as two separate operations involves quite a few steps, so this Tool does it in a single step and with some improved efficiency.
- L62 _public function_ `UCutMeshWithMeshTool()`
- L66 _protected prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L68 _protected prototype_ `virtual void ConvertInputsAndSetPreviewMaterials(bool bSetPreviewMesh = true) override;`
- L70 _protected prototype_ `virtual void SetupProperties() override;`
- L71 _protected prototype_ `virtual void SaveProperties() override;`
- L72 _protected prototype_ `virtual void SetPreviewCallbacks() override;`
- L74 _protected prototype_ `virtual FString GetCreatedAssetName() const override;`
- L75 _protected prototype_ `virtual FText GetActionName() const override;`
- L78 _protected prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L80 _protected prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L82 _protected prototype_ `void UpdateVisualization();`
- L85 _protected member_ `TObjectPtr<UCutMeshWithMeshToolProperties> CutProperties;` — `UPROPERTY()`
- L88 _protected member_ `TObjectPtr<UPreviewMesh> IntersectPreviewMesh;` — `UPROPERTY()`
- L90 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalTargetMesh;`
- L91 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalCuttingMesh;`
- L94 _protected member_ `TObjectPtr<ULineSetComponent> DrawnLineSet;` — `UPROPERTY()`
- L97 _protected member_ `TArray<int> CreatedSubtractBoundaryEdges;` — for visualization of any errors in the currently-previewed CSG operation
- L98 _protected member_ `TArray<int> CreatedIntersectBoundaryEdges;`
- L100 _protected member_ `FDynamicMesh3 IntersectionMesh;`

#### class `UCutMeshWithMeshToolBuilder`  
`class UCutMeshWithMeshToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L107-126_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L112 _public function_ `virtual TOptional<int32> MaxComponentsSupported() const override`
- L117 _public function_ `virtual int32 MinComponentsSupported() const override`
- L122 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L16 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/DeformMeshPolygonsTool.h` (Public)


#### class `UDeformMeshPolygonsToolBuilder`  
`class UDeformMeshPolygonsToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L34-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: ToolBuilder
- L40 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `EGroupTopologyDeformationStrategy`  
`enum class EGroupTopologyDeformationStrategy : uint8`  
_L45-52_
- reflection: `UENUM()`
- desc: Deformation strategies
- L48 _public enumerator_ `Linear UMETA(DisplayName = "Linear")` — Deforms the mesh using linear deformation.
- L51 _public enumerator_ `Laplacian UMETA(DisplayName = "Smooth")` — Deforms the mesh using Laplacian deformation.

#### enum `EWeightScheme`  
`enum class EWeightScheme`  
_L56-65_
- reflection: `UENUM()`
- desc: Laplacian weight schemes determine how we will look at the curvature at a given vertex in relation to its neighborhood
- L58 _public enumerator_ `Uniform UMETA(DisplayName = "Uniform")`
- L59 _public enumerator_ `Umbrella UMETA(DisplayName = "Umbrella")`
- L60 _public enumerator_ `Valence UMETA(DisplayName = "Valence")`
- L61 _public enumerator_ `MeanValue UMETA(DisplayName = "MeanValue")`
- L62 _public enumerator_ `Cotangent UMETA(DisplayName = "Cotangent")`
- L63 _public enumerator_ `ClampedCotangent UMETA(DisplayName = "ClampedCotangent")`
- L64 _public enumerator_ `IDTCotangent UMETA(DisplayName = "IDTCotangent")`

#### enum `EQuickTransformerMode`  
`enum class EQuickTransformerMode : uint8`  
_L76-83_
- reflection: `UENUM()`
- desc: Modes for quick transformer
- L79 _public enumerator_ `AxisTranslation = 0 UMETA(DisplayName = "Translate")` — Translation along axes
- L82 _public enumerator_ `AxisRotation = 1 UMETA(DisplayName = "Rotate")` — Rotation around axes

#### class `UDeformMeshPolygonsTransformProperties`  
`class UDeformMeshPolygonsTransformProperties : public UInteractiveToolPropertySet`  
_L89-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L94 _public prototype_ `UDeformMeshPolygonsTransformProperties();`
- L100 _public member_ `EGroupTopologyDeformationStrategy DeformationStrategy;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Deformation"))` — Type of deformation used.
- L104 _public member_ `EQuickTransformerMode TransformMode;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Transformation"))` — Type of transformation used.
- L108 _public member_ `bool bSelectFaces;` — `UPROPERTY(EditAnywhere, Category = Selection)` — Allow for faces (PolyGroups) to be selected.
- L112 _public member_ `bool bSelectEdges;` — `UPROPERTY(EditAnywhere, Category = Selection)` — Allow for edges to be selected.
- L116 _public member_ `bool bSelectVertices;` — `UPROPERTY(EditAnywhere, Category = Selection)` — Allow for vertices to be selected.
- L120 _public member_ `bool bShowWireframe;` — `UPROPERTY(EditAnywhere, Category = Display)` — If true, overlays preview with wireframe.
- L125 _public member_ `EWeightScheme SelectedWeightScheme = EWeightScheme::IDTCotangent;` — `UPROPERTY()`
- L128 _public member_ `double HandleWeight = 1000.0;` — `UPROPERTY()`
- L131 _public member_ `bool bPostFixHandles = false;` — `UPROPERTY()`

#### class `UDeformMeshPolygonsTool`  
`class UDeformMeshPolygonsTool : public UMeshSurfacePointTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L152-276_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointTool,IInteractiveToolManageGeometrySelectionAPI`
- L157 _public prototype_ `UDeformMeshPolygonsTool();`
- L159 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L161 _public prototype_ `virtual void Setup() override;`
- L162 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L164 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L165 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L167 _public function_ `virtual bool HasCancel() const override`
- L168 _public function_ `virtual bool HasAccept() const override`
- L170 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;`
- L172 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L173 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L174 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L175 _public prototype_ `virtual void OnCancelDrag() override;`
- L176 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L179 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L185 _public prototype_ `virtual void NextTransformTypeAction();`
- L188 _public member_ `float VisualAngleSnapThreshold = 0.5;`
- L193 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L196 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent;` — `UPROPERTY()`
- L199 _protected member_ `TObjectPtr<UDeformMeshPolygonsTransformProperties> TransformProps;` — `UPROPERTY()`
- L202 _protected prototype_ `void OnDynamicMeshComponentChanged();` — realtime visualization
- L203 _protected member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L205 _protected prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L208 _protected member_ `FViewCameraState CameraState;` — camera state at last render
- L209 _protected member_ `FTransform3d WorldTransform;`
- L211 _protected member_ `FToolDataVisualizer PolyEdgesRenderer;`
- L214 _protected member_ `bool bInDrag;` — True for the duration of UI click+drag
- L216 _protected member_ `FPlane ActiveDragPlane;`
- L217 _protected member_ `FVector StartHitPosWorld;`
- L218 _protected member_ `FVector StartHitNormalWorld;`
- L219 _protected member_ `FVector LastHitPosWorld;`
- L220 _protected member_ `FVector LastBrushPosLocal;`
- L221 _protected member_ `FVector StartBrushPosLocal;`
- L223 _protected member_ `UE::Geometry::FFrame3d ActiveSurfaceFrame;`
- L224 _protected prototype_ `UE::Geometry::FQuickTransformer* GetActiveQuickTransformer();`
- L225 _protected prototype_ `void UpdateActiveSurfaceFrame(FGroupTopologySelection& Selection);`
- L226 _protected prototype_ `void UpdateQuickTransformer();`
- L228 _protected member_ `FRay UpdateRay;`
- L229 _protected member_ `bool bUpdatePending = false;`
- L230 _protected prototype_ `void ComputeUpdate();`
- L232 _protected member_ `FVector3d LastMoveDelta;`
- L233 _protected member_ `UE::Geometry::FQuickAxisTranslater QuickAxisTranslater;`
- L234 _protected prototype_ `void ComputeUpdate_Translate();`
- L236 _protected member_ `UE::Geometry::FQuickAxisRotator QuickAxisRotator;`
- L237 _protected member_ `FVector3d RotationStartPointWorld;`
- L238 _protected member_ `UE::Geometry::FFrame3d RotationStartFrame;`
- L239 _protected prototype_ `void ComputeUpdate_Rotate();`
- L241 _protected member_ `FGroupTopology Topology;`
- L242 _protected prototype_ `void PrecomputeTopology();`
- L244 _protected member_ `FGroupTopologySelector TopoSelector;`
- L245 _protected prototype_ `FGroupTopologySelector::FSelectionSettings GetTopoSelectorSettings();`
- L251 _protected member_ `FGroupTopologySelection HilightSelection;`
- L252 _protected member_ `FToolDataVisualizer HilightRenderer;`
- L254 _protected member_ `UE::Geometry::FDynamicMeshAABBTree3 MeshSpatial;`
- L255 _protected prototype_ `UE::Geometry::FDynamicMeshAABBTree3& GetSpatial();`
- L257 _protected member_ `FMeshVertexChangeBuilder* ActiveVertexChange;`
- L259 _protected member_ `EGroupTopologyDeformationStrategy DeformationStrategy;`
- L262 _protected member_ `UE::Geometry::FGroupTopologyDeformer LinearDeformer;` — The two deformer type options.
- L263 _protected member_ `TPimplPtr<FGroupTopologyLaplacianDeformer> LaplacianDeformer;`
- L268 _protected member_ `bool bSpatialDirty;` — This is true when the spatial index needs to reflect a modification
- L270 _protected prototype_ `void BeginChange();`
- L271 _protected prototype_ `void EndChange();`
- L272 _protected prototype_ `void UpdateChangeFromROI(bool bFinal);`
- L275 _private member_ `UE::TransactionUtil::FLongTransactionTracker LongTransactions;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L68 _function_ `static ELaplacianWeightScheme ConvertToLaplacianWeightScheme(const EWeightScheme WeightScheme)` — The ELaplacianWeightScheme enum is the same..

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/DisplaceMeshTool.h` (Public)


#### enum `EDisplaceMeshToolDisplaceType`  
`enum class EDisplaceMeshToolDisplaceType : uint8`  
_L27-48_
- reflection: `UENUM()`
- L30 _public enumerator_ `Constant UMETA(DisplayName = "Constant")` — Offset a set distance in the normal direction.
- L33 _public enumerator_ `DisplacementMap UMETA(DisplayName = "Texture2D Map")` — Offset in the normal direction using the first channel of a 2D texture.
- L36 _public enumerator_ `RandomNoise UMETA(DisplayName = "Random Noise")` — Offset vertices randomly.
- L44 _public enumerator_ `PerlinNoise UMETA(DisplayName = "Perlin Noise")` — Offset in the normal direction weighted by Perlin noise. We use the following formula to compute the weighting for each vertex: w = PerlinNoise3D(f * (X + r)) Where f is a frequency parameter, X is the vertex position, and r is a randomly-generated offset (using the Seed property). Note the range of 3D Perlin noise is [-sqrt(3/4), sqrt(3/4)].
- L47 _public enumerator_ `SineWave UMETA(DisplayName = "Sine Wave")` — Move vertices in spatial sine wave pattern

#### enum `EDisplaceMeshToolSubdivisionType`  
`enum class EDisplaceMeshToolSubdivisionType : uint8`  
_L51-61_
- reflection: `UENUM()`
- L54 _public enumerator_ `Flat UMETA(DisplayName = "Flat")` — Subdivide the mesh using loop-style subdivision.
- L60 _public enumerator_ `PNTriangles UMETA(DisplayName = "PN Triangles")` — Subdivide the mesh using PN triangles which replace each original flat triangle by a curved shape that is retriangulated into a number of small subtriangles. The geometry of a PN triangle is defined as one cubic Bezier patch using control points. The patch matches the point and normal information at the vertices of the original flat triangle.

#### enum `EDisplaceMeshToolTriangleSelectionType`  
`enum class EDisplaceMeshToolTriangleSelectionType : uint8`  
_L64-71_
- reflection: `UENUM()`
- L67 _public enumerator_ `None UMETA(DisplayName = "None")` — Tessellate the whole mesh
- L70 _public enumerator_ `Material UMETA(DisplayName = "Material")` — Tessellate only triangles assigned to the chosen material

#### enum `EDisplaceMeshToolChannelType`  
`enum class EDisplaceMeshToolChannelType : uint8`  
_L74-80_
- reflection: `UENUM()`
- L76 _public enumerator_ `Red`
- L77 _public enumerator_ `Green`
- L78 _public enumerator_ `Blue`
- L79 _public enumerator_ `Alpha`

#### class `UDisplaceMeshCommonProperties`  
`class UDisplaceMeshCommonProperties : public UInteractiveToolPropertySet`  
_L84-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: The basic set of properties shared by (more or less) all DisplacementTypes.
- L91 _public member_ `EDisplaceMeshToolDisplaceType DisplacementType = EDisplaceMeshToolDisplaceType::PerlinNoise;` — `UPROPERTY(EditAnywhere, Category = Options)` — Displacement type
- L96 _public member_ `float DisplaceIntensity = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "-100.0", UIMax = "100.0", ClampMin = "-10000.0", ClampMax = "100000.0"))` — Displacement intensity
- L101 _public member_ `int RandomSeed = 31337;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "DisplacementType == EDisplaceMeshToolDisplaceType::RandomNoise || DisplacementType == EDisplaceMeshToolDisplaceType::PerlinNoise", Delta = 1, LinearDeltaSensitivity = 50))` — Seed for randomization
- L105 _public member_ `EDisplaceMeshToolSubdivisionType SubdivisionType = EDisplaceMeshToolSubdivisionType::PNTriangles;` — `UPROPERTY(EditAnywhere, Category = Options)` — Type of the  mesh subdivision.
- L110 _public member_ `int Subdivisions = 4;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "100"))` — Number of times to subdivide the mesh before displacing it.
- L114 _public member_ `FName WeightMap;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (GetOptions = GetWeightMapsFunc))` — Select vertex weight map. If configured, the weight map value will be sampled to modulate displacement intensity.
- L117 _public prototype_ `TArray<FString> GetWeightMapsFunc();` — `UFUNCTION()`
- L120 _public member_ `TArray<FString> WeightMapsList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L123 _public member_ `bool bInvertWeightMap = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L126 _public member_ `bool bShowWireframe = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L129 _public member_ `bool bDisableSizeWarning = false;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (TransientToolProperty))`

#### class `USelectiveTessellationProperties`  
`class USelectiveTessellationProperties : public UInteractiveToolPropertySet`  
_L134-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: PropertySet for properties affecting the selective tessellation.
- L142 _public member_ `EDisplaceMeshToolTriangleSelectionType SelectionType = EDisplaceMeshToolTriangleSelectionType::None;` — `UPROPERTY(EditAnywhere, Category = SelectiveTessellationOptions)` — Optionally, restrict tessellation to a subset of the triangles.
- L146 _public member_ `FName ActiveMaterial;` — `UPROPERTY(EditAnywhere, Category = SelectiveTessellationOptions, meta = (EditCondition = "SelectionType == EDisplaceMeshToolTriangleSelectionType::Material", EditConditionHides, GetOptions = GetMaterialIDsFunc))` — Name of the selected material.
- L149 _public function_ `TArray<FString> GetMaterialIDsFunc()` — `UFUNCTION()`
- L152 _public member_ `TArray<FString> MaterialIDList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UDisplaceMeshTextureMapProperties`  
`class UDisplaceMeshTextureMapProperties : public UInteractiveToolPropertySet`  
_L158-201_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: PropertySet for properties affecting the Image Map displacement type.
- L165 _public member_ `TObjectPtr<UTexture2D> DisplacementMap = nullptr;` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions)` — The texture to sample for displacement.
- L169 _public member_ `EDisplaceMeshToolChannelType Channel = EDisplaceMeshToolChannelType::Red;` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions)` — Channel in the displacement map to use.
- L175 _public member_ `float DisplacementMapBaseValue = 128.0f/255;` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The value in the texture map that corresponds to no displacement. For instance, if set to 0, then all displacement will be positive. If set to 0.5, displacement below 0.5 will be negative, and above will be positive. Default is for 128/255 to be no displacement.
- L181 _public member_ `FVector2D UVScale = FVector2D(1,1);` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions, meta = (Delta = 0.01, LinearDeltaSensitivity = 1))` — When sampling from the texture map, how to scale the mesh UV's in the x and y directions. For a mesh with UV's in the range 0 to 1, setting a scale above 1 will result in tiling the texture map, and scaling below 1 will result in using only part of the texture map.
- L186 _public member_ `FVector2D UVOffset = FVector2D(0, 0);` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions, meta = (UIMin = "-1", UIMax = "1"))` — When sampling from the texture map, how to offset the mesh UV's. This will result in offsetting the tiling of the texture map across the mesh.
- L192 _public member_ `bool bApplyAdjustmentCurve = false;` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions)` — When true, applies a function to remap the values in the displacement map, which can be used for contrast adjustment. The texture map values are converted to the range [0,1] before applying the remapping.
- L196 _public member_ `TObjectPtr<UCurveFloat> AdjustmentCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions, meta = (EditCondition = "bApplyAdjustmentCurve", EditConditionHides))` — This curve is queried in the range [0,1] to adjust contrast of the displacement map.
- L200 _public member_ `bool bRecalcNormals = true;` — `UPROPERTY(EditAnywhere, Category = TextureMapOptions)` — Recalculate normals from displaced mesh. Disable this if you are applying Displacements that are paired with an existing Normal Map in your Material.

#### class `UDisplaceMeshDirectionalFilterProperties`  
`class UDisplaceMeshDirectionalFilterProperties : public UInteractiveToolPropertySet`  
_L207-230_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for a directional filter. Allows for displacement to be applied only to vertices whose normals point in a given direction
- L214 _public member_ `bool bEnableFilter = false;` — `UPROPERTY(EditAnywhere, Category = DirectionalFilterOptions)` — Whether the directional filter is active.
- L219 _public member_ `FVector FilterDirection = {0.0f, 0.0f, 1.0f};` — `UPROPERTY(EditAnywhere, Category = DirectionalFilterOptions, meta = (EditCondition = "bEnableFilter == true", Delta = 0.5, LinearDeltaSensitivity = 1))` — Unit vector representing the direction to filter along.
- L228 _public member_ `float FilterWidth = 0.25f;` — `UPROPERTY(EditAnywhere, Category = DirectionalFilterOptions, meta = (EditCondition = "bEnableFilter == true", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Scalar value determining how close to the filter direction the vertex normals must be in order to be displaced. 0: Only normals pointing exactly in the filter direction are displaced. 0.5: Normals forming angle up to 90 from the filter direction are displaced. 1.0: All vertices are displaced.

#### struct `FPerlinLayerProperties`  
`struct FPerlinLayerProperties`  
_L234-254_
- reflection: `USTRUCT()`
- desc: Per-layer properties for Perlin noise. Each layer has independent Frequency and Intensity.
- L238 _public prototype_ `FPerlinLayerProperties() = default;`
- L240 _public function_ `FPerlinLayerProperties(float FrequencyIn, float IntensityIn) : Frequency(FrequencyIn), Intensity(IntensityIn)`
- L248 _public member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = PerlinNoiseOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0"))` — Frequency of Perlin noise layer
- L253 _public member_ `float Intensity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = PerlinNoiseOptions, meta = (UIMin = "-10.0", UIMax = "10.0", ClampMin = "-100.0", ClampMax = "100.0"))` — Intensity/amplitude of Perlin noise layer

#### class `UDisplaceMeshPerlinNoiseProperties`  
`class UDisplaceMeshPerlinNoiseProperties : public UInteractiveToolPropertySet`  
_L258-266_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: PropertySet for properties affecting the Perlin Noise displacement type.
- L264 _public member_ `TArray<FPerlinLayerProperties> PerlinLayerProperties = { {0.05f, 1.0f}, {0.25f, 0.5f}, {0.5f, 0.2f}, {1.0f, 0.1f} };` — `UPROPERTY(EditAnywhere, Category = PerlinNoiseOptions)`

#### class `UDisplaceMeshSineWaveProperties`  
`class UDisplaceMeshSineWaveProperties : public UInteractiveToolPropertySet`  
_L271-289_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: PropertySet for Sine wave displacement
- L279 _public member_ `float SineWaveFrequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = SineWaveOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0"))` — Sine wave displacement frequency
- L284 _public member_ `float SineWavePhaseShift = 0.0f;` — `UPROPERTY(EditAnywhere, Category = SineWaveOptions, meta = (UIMin = "0.0", UIMax = "6.28318531", ClampMin = "0.0", ClampMax = "6.28318531"))` — Sine wave phase shift
- L288 _public member_ `FVector SineWaveDirection = { 0.0f, 0.0f, 1.0f };` — `UPROPERTY(EditAnywhere, Category = SineWaveOptions, meta = (Delta = 0.5, LinearDeltaSensitivity = 1))` — Unit vector representing the direction of wave displacement.

#### class `UDisplaceMeshToolBuilder`  
`class UDisplaceMeshToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L295-303_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionToolBuilder`
- desc: Builder for Simple Mesh Displacement Tool
- L299 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override final;`
- L302 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UDisplaceMeshTool`  
`class UDisplaceMeshTool : public USingleTargetWithSelectionTool`  
_L309-391_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionTool`
- desc: Simple Mesh Displacement Tool
- L313 _public prototype_ `void Setup() final;`
- L314 _public prototype_ `void OnShutdown(EToolShutdownType ShutdownType) final;`
- L315 _public prototype_ `void OnTick(float DeltaTime) final;`
- L317 _public function_ `bool HasCancel() const final`
- L318 _public function_ `bool HasAccept() const final`
- L321 _public prototype_ `void OnPropertyModified(UObject* PropertySet, FProperty* Property) final;`
- L326 _public member_ `TObjectPtr<UDisplaceMeshCommonProperties> CommonProperties;` — `UPROPERTY()` — Shared properties for all displacement modes.
- L330 _public member_ `TObjectPtr<UDisplaceMeshDirectionalFilterProperties> DirectionalFilterProperties;` — `UPROPERTY()` — Properties defining the directional filter.
- L334 _public member_ `TObjectPtr<UDisplaceMeshTextureMapProperties> TextureMapProperties;` — `UPROPERTY()` — Properties defining the texture map
- L338 _public member_ `TObjectPtr<UDisplaceMeshPerlinNoiseProperties> NoiseProperties;` — `UPROPERTY()` — Multi-layer Perlin noise frequencies and intensities
- L342 _public member_ `TObjectPtr<UDisplaceMeshSineWaveProperties> SineWaveProperties;` — `UPROPERTY()` — Sine wave parameters and direction of displacement
- L346 _public member_ `TObjectPtr<USelectiveTessellationProperties> SelectiveTessellationProperties;` — `UPROPERTY()` — Selective tessellation properties
- L350 _public member_ `TObjectPtr<UCurveFloat> ActiveContrastCurveTarget = nullptr;` — `UPROPERTY()` — Contrast Curve we are actively listening to
- L353 _public member_ `TObjectPtr<UMeshStatisticsProperties> MeshStatistics;` — `UPROPERTY()`
- L357 _private prototype_ `void StartComputation();`
- L358 _private prototype_ `void AdvanceComputation();`
- L359 _private prototype_ `void ValidateSubdivisions();`
- L361 _private member_ `double ComputationStartTime = 0;`
- L363 _private member_ `UE::Geometry::FAsyncTaskExecuterWithAbort<UE::Geometry::TModelingOpTask<UE::Geometry::FDynamicMeshOperator>>* SubdivideTask = nullptr;`
- L364 _private member_ `bool bNeedsSubdivided = true;`
- L365 _private member_ `UE::Geometry::FAsyncTaskExecuterWithAbort<UE::Geometry::TModelingOpTask<UE::Geometry::FDynamicMeshOperator>>* DisplaceTask = nullptr;`
- L366 _private member_ `bool bNeedsDisplaced = true;`
- L368 _private member_ `UE::Geometry::FDynamicMesh3 OriginalMesh;`
- L369 _private member_ `UE::Geometry::FDynamicMeshAABBTree3 OriginalMeshSpatial;`
- L370 _private member_ `TSharedPtr<UE::Geometry::FIndexedWeightMap, ESPMode::ThreadSafe> ActiveWeightMap;`
- L371 _private prototype_ `void UpdateActiveWeightMap();`
- L372 _private prototype_ `float WeightMapQuery(const FVector3d& Position, const UE::Geometry::FIndexedWeightMap& WeightMap) const;`
- L374 _private member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> SubdividedMesh = nullptr;`
- L375 _private member_ `TSharedPtr<TArray<int>, ESPMode::ThreadSafe> VerticesToDisplace = nullptr;`
- L376 _private member_ `int32 NumTrianglesInSelection;`
- L379 _private member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L382 _private member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent = nullptr;` — `UPROPERTY()`
- L384 _private member_ `TUniquePtr<UE::Geometry::IDynamicMeshOperatorFactory> Subdivider = nullptr;`
- L385 _private member_ `TUniquePtr<UE::Geometry::IDynamicMeshOperatorFactory> Displacer = nullptr;`
- L388 _private member_ `FDelegateHandle ActiveContrastCurveListenerHandle;` — management of TextureMapProperties->AdjustmentCurve.OnUpdateCurve listener
- L389 _private prototype_ `void UpdateActiveContrastCurveTarget();`
- L390 _private prototype_ `void DisconnectActiveContrastCurveTarget();`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/DrawAndRevolveTool.h` (Public)


#### class `UDrawAndRevolveToolBuilder`  
`class UDrawAndRevolveToolBuilder : public UInteractiveToolBuilder`  
_L24-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L29 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L30 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `URevolveToolProperties`  
`class URevolveToolProperties : public URevolveProperties`  
_L34-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URevolveProperties`
- L43 _public member_ `ERevolvePropertiesCapFillMode CapFillMode = ERevolvePropertiesCapFillMode::Delaunay;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (DisplayAfter = "QuadSplitMode", EditCondition = "HeightOffsetPerDegree != 0 || RevolveDegrees != 360", ValidEnumValues = "None, CenterFan, Delaunay"))` — Determines how end caps are created. This is not relevant if the end caps are not visible or if the path is not closed.
- L48 _public member_ `bool bClosePathToAxis = true;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay)` — Connect the ends of an open path to the axis to add caps to the top and bottom of the revolved result. This is not relevant for paths that are already closed.
- L53 _public member_ `FVector DrawPlaneOrigin = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = DrawPlane, meta = (DisplayName = "Origin", EditCondition = "bAllowedToEditDrawPlane", HideEditConditionToggle, Delta = 5, LinearDeltaSensitivity = 1))` — Sets the draw plane origin. The revolution axis is the X axis in the plane.
- L58 _public member_ `FRotator DrawPlaneOrientation = FRotator(90, 0, 0);` — `UPROPERTY(EditAnywhere, Category = DrawPlane, meta = (DisplayName = "Orientation", EditCondition = "bAllowedToEditDrawPlane", HideEditConditionToggle, UIMin = -180, UIMax = 180, ClampMin = -180000, ClampMax = 180000))` — Sets the draw plane orientation. The revolution axis is the X axis in the plane.
- L62 _public member_ `bool bEnableSnapping = true;` — `UPROPERTY(EditAnywhere, Category = Snapping)` — Enables snapping while editing the path.
- L66 _public member_ `bool bAllowedToEditDrawPlane = true;` — `UPROPERTY(meta = (TransientToolProperty))` — Not user visible- used to disallow draw plane modification.
- L69 _protected function_ `virtual ERevolvePropertiesCapFillMode GetCapFillMode() const override`

#### class `URevolveOperatorFactory`  
`class URevolveOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L76-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L82 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L85 _public member_ `TObjectPtr<UDrawAndRevolveTool> RevolveTool;` — `UPROPERTY()`

#### class `UDrawAndRevolveTool`  
`class UDrawAndRevolveTool : public UInteractiveTool`  
_L91-162_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool`
- desc: Draws a profile curve and revolves it around an axis.
- L96 _public function_ `virtual void SetWorld(UWorld* World)`
- L98 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L99 _public prototype_ `virtual void OnPointDeletionKeyPress();`
- L101 _public function_ `virtual bool HasCancel() const override`
- L102 _public function_ `virtual bool HasAccept() const override`
- L103 _public prototype_ `virtual bool CanAccept() const override;`
- L105 _public prototype_ `virtual void Setup() override;`
- L106 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L108 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L109 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L111 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L113 _public function_ `void SetInitialDrawFrame(UE::Geometry::FFrame3d InFrame)`
- L118 _public prototype_ `bool CanGenerateAsset() const;`
- L122 _protected member_ `UWorld* TargetWorld;`
- L124 _protected member_ `FViewCameraState CameraState;`
- L128 _protected member_ `FVector3d RevolutionAxisOrigin;` — This information is replicated in the user-editable transform in the settings and in the PlaneMechanic plane, but the tool turned out to be much easier to write and edit with this decoupling.
- L129 _protected member_ `FVector3d RevolutionAxisDirection;`
- L132 _protected member_ `UE::Geometry::FFrame3d InitialDrawFrame;` — The initial frame, used in tool setup to place the axis
- L134 _protected member_ `bool bProfileCurveComplete = false;`
- L136 _protected prototype_ `void UpdateRevolutionAxis();`
- L139 _protected member_ `TObjectPtr<UCurveControlPointsMechanic> ControlPointsMechanic = nullptr;` — `UPROPERTY()`
- L142 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L146 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()` — Property set for type of output object (StaticMesh, Volume, etc)
- L149 _protected member_ `TObjectPtr<URevolveToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L152 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties;` — `UPROPERTY()`
- L155 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L157 _protected prototype_ `void StartPreview();`
- L159 _protected prototype_ `void GenerateAsset(const FDynamicMeshOpResult& Result);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/DrawPolygonTool.h` (Public)


#### class `UDrawPolygonToolBuilder`  
`class UDrawPolygonToolBuilder : public UInteractiveToolBuilder`  
_L33-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L38 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L39 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EDrawPolygonDrawMode`  
`enum class EDrawPolygonDrawMode : uint8`  
_L46-65_
- reflection: `UENUM()`
- desc: Polygon tool draw type
- L49 _public enumerator_ `Freehand` — Draw a freehand polygon
- L52 _public enumerator_ `Circle` — Draw a circle
- L55 _public enumerator_ `Square` — Draw a square
- L58 _public enumerator_ `Rectangle` — Draw a rectangle
- L61 _public enumerator_ `RoundedRectangle` — Draw a rounded rectangle
- L64 _public enumerator_ `Ring` — Draw a circle with a hole in the center

#### enum `EDrawPolygonExtrudeMode`  
`enum class EDrawPolygonExtrudeMode : uint8`  
_L70-80_
- reflection: `UENUM()`
- desc: How the drawn polygon gets extruded
- L73 _public enumerator_ `Flat` — Flat polygon without extrusion
- L76 _public enumerator_ `Fixed` — Extrude drawn polygon to fixed height determined by the Extrude Height property
- L79 _public enumerator_ `Interactive` — Extrude drawn polygon to height set via additional mouse input after closing the polygon

#### class `UDrawPolygonToolStandardProperties`  
`class UDrawPolygonToolStandardProperties : public UInteractiveToolPropertySet`  
_L87-129_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L92 _public prototype_ `UDrawPolygonToolStandardProperties();`
- L96 _public member_ `EDrawPolygonDrawMode PolygonDrawMode = EDrawPolygonDrawMode::Freehand;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Polygon, meta = (DisplayName = "Draw Mode"))` — Type of polygon to draw in the viewport
- L101 _public member_ `bool bAllowSelfIntersections = false;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Polygon, meta = (DisplayName ="Self-Intersections", EditCondition = "PolygonDrawMode == EDrawPolygonDrawMode::Freehand"))` — Allow freehand drawn polygons to self-intersect
- L106 _public member_ `float FeatureSizeRatio = .25;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Polygon, meta = (UIMin = "0.01", UIMax = "0.99", ClampMin = "0.01", ClampMax = "0.99", EditCondition = "PolygonDrawMode == EDrawPolygonDrawMode::RoundedRectangle || PolygonDrawMode == EDrawPolygonDrawMode::Ring"))` — Size of secondary features, e.g. the rounded corners of a rounded rectangle, as fraction of the overall shape size
- L111 _public member_ `int RadialSlices = 16;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Polygon, meta = (UIMin = "3", UIMax = "100", ClampMin = "3", ClampMax = "10000", EditCondition = "PolygonDrawMode == EDrawPolygonDrawMode::Circle || PolygonDrawMode == EDrawPolygonDrawMode::RoundedRectangle || PolygonDrawMode == EDrawPolygonDrawMode::Ring"))` — Number of radial subdivisions in round features, e.g. circles or rounded corners
- L115 _public member_ `float Distance = 0.0f;` — `UPROPERTY(VisibleAnywhere, NonTransactional, Category = Polygon, meta = (TransientToolProperty))` — Distance between the last clicked point and the current point
- L119 _public member_ `bool bShowGridGizmo = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Polygon)` — If true, shows a gizmo to manipulate the additional grid used to draw the polygon on
- L123 _public member_ `EDrawPolygonExtrudeMode ExtrudeMode = EDrawPolygonExtrudeMode::Interactive;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Extrude)` — If and how the drawn polygon gets extruded
- L128 _public member_ `float ExtrudeHeight = 100.0f;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Extrude, meta = (UIMin = "-1000", UIMax = "1000", ClampMin = "-10000", ClampMax = "10000", EditCondition = "ExtrudeMode == EDrawPolygonExtrudeMode::Fixed"))` — Extrude distance when using the Fixed extrude mode

#### class `UDrawPolygonToolSnapProperties`  
`class UDrawPolygonToolSnapProperties : public UInteractiveToolPropertySet`  
_L132-169_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L139 _public member_ `bool bEnableSnapping = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Snapping)` — Enables additional snapping controls. If false, all snapping is disabled.
- L143 _public member_ `bool bSnapToWorldGrid = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L147 _public member_ `bool bSnapToVertices = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Snapping, meta = (EditCondition = "bEnableSnapping"))` — Snap to vertices in other meshes. Requires Enable Snapping to be true.
- L151 _public member_ `bool bSnapToEdges = false;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Snapping, meta = (EditCondition = "bEnableSnapping"))` — Snap to edges in other meshes. Requires Enable Snapping to be true.
- L155 _public member_ `bool bSnapToAxes = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Snapping, meta = (EditCondition = "bEnableSnapping && !bSnapToWorldGrid"))` — Snap to axes of the drawing grid and axes relative to the last segment. Requires grid snapping to be disabled in viewport, and Enable Snapping to be true.
- L159 _public member_ `bool bSnapToLengths = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Snapping, meta = (EditCondition = "bEnableSnapping && !bSnapToWorldGrid && bSnapToAxes"))` — When snapping to axes, also try to snap to the length of an existing segment in the polygon. Requires grid snapping to be disabled in viewport, and Snap to Axes and Enable Snapping to be true.
- L163 _public member_ `bool bSnapToSurfaces = false;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Snapping, meta = (EditCondition = "bEnableSnapping && !bSnapToWorldGrid"))` — Snap to surfaces of existing objects. Requires grid snapping to be disabled in viewport, and Enable Snapping to be true.
- L168 _public member_ `float SnapToSurfacesOffset = 0.0f;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Snapping, meta = (DisplayName = "Surface Offset", EditCondition = "bEnableSnapping && !bSnapToWorldGrid && bSnapToSurfaces"))` — Offset for snap point on the surface of an existing object in the direction of the surface normal. Requires grid snapping to be disabled in viewport, and Snap to Surfaces and Enable Snapping to be true.

#### class `UDrawPolygonTool`  
`class UDrawPolygonTool : public UInteractiveTool, public IClickSequenceBehaviorTarget, public IInteractiveToolManageGeometrySelectionAPI`  
_L179-336_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IClickSequenceBehaviorTarget,IInteractiveToolManageGeometrySelectionAPI`
- desc: This tool allows the user to draw and extrude 2D polygons
- L183 _public prototype_ `UDrawPolygonTool();`
- L185 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L187 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L189 _public prototype_ `virtual void Setup() override;`
- L190 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L192 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L193 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L195 _public function_ `virtual bool HasCancel() const override`
- L196 _public function_ `virtual bool HasAccept() const override`
- L197 _public function_ `virtual bool CanAccept() const override`
- L201 _public prototype_ `virtual void OnBeginSequencePreview(const FInputDeviceRay& ClickPos) override;`
- L202 _public prototype_ `virtual bool CanBeginClickSequence(const FInputDeviceRay& ClickPos) override;`
- L203 _public prototype_ `virtual void OnBeginClickSequence(const FInputDeviceRay& ClickPos) override;`
- L204 _public prototype_ `virtual void OnNextSequencePreview(const FInputDeviceRay& ClickPos) override;`
- L205 _public prototype_ `virtual bool OnNextSequenceClick(const FInputDeviceRay& ClickPos) override;`
- L206 _public prototype_ `virtual void OnTerminateClickSequence() override;`
- L207 _public prototype_ `virtual bool RequestAbortClickSequence() override;`
- L208 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L211 _public prototype_ `virtual void ResetPolygon();` — polygon drawing functions
- L212 _public prototype_ `virtual void UpdatePreviewVertex(const FVector3d& PreviewVertex);`
- L213 _public prototype_ `virtual void AppendVertex(const FVector3d& Vertex);`
- L214 _public prototype_ `virtual bool FindDrawPlaneHitPoint(const FInputDeviceRay& ClickPos, FVector3d& HitPosOut);`
- L215 _public prototype_ `virtual void EmitCurrentPolygon();`
- L217 _public prototype_ `virtual void BeginInteractiveExtrude();`
- L218 _public prototype_ `virtual void EndInteractiveExtrude();`
- L220 _public prototype_ `virtual void ApplyUndoPoints(const TArray<FVector3d>& ClickPointsIn, const TArray<FVector3d>& PolygonVerticesIn);`
- L222 _public function_ `void SetInitialDrawFrame(UE::Geometry::FFrame3d Frame)`
- L228 _public prototype_ `virtual bool IsInputSelectionValidOnOutput() override;` — IInteractiveToolManageGeometrySelectionAPI - enables restoration of previous selection when applicable
- L233 _protected member_ `static constexpr int IgnoreSnappingModifier = 1;` — flags used to identify modifier keys/buttons
- L234 _protected member_ `static constexpr int AngleSnapModifier = 2;`
- L238 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()` — Property set for type of output object (StaticMesh, Volume, etc)
- L242 _protected member_ `TObjectPtr<UDrawPolygonToolStandardProperties> PolygonProperties;` — `UPROPERTY()` — Properties that control polygon generation exposed to user via details view
- L245 _protected member_ `TObjectPtr<UDrawPolygonToolSnapProperties> SnapProperties;` — `UPROPERTY()`
- L248 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties;` — `UPROPERTY()`
- L251 _protected member_ `TArray<FVector3d> PolygonVertices;` — Vertices of current preview polygon
- L254 _protected member_ `TArray<TArray<FVector3d>> PolygonHolesVertices;` — Vertices of holes in current preview polygon
- L257 _protected member_ `FVector3d PreviewVertex;` — last vertex of polygon that is actively being updated as input device is moved
- L259 _protected member_ `UWorld* TargetWorld;`
- L261 _protected member_ `FViewCameraState CameraState;`
- L264 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L267 _protected prototype_ `void PlaneTransformChanged();` — called on PlaneMechanic.OnPlaneChanged
- L270 _protected prototype_ `bool AllowDrawPlaneUpdates();` — whether to allow the draw plane to be updated in the UI -- returns false if there is an in-progress shape relying on the current draw plane
- L274 _protected member_ `UE::Geometry::FFrame3d InitialDrawFrame;`
- L276 _protected member_ `bool bAbortActivePolygonDraw;`
- L278 _protected member_ `bool bInFixedPolygonMode = false;`
- L279 _protected member_ `TArray<FVector3d> FixedPolygonClickPoints;`
- L282 _protected prototype_ `bool UpdateSelfIntersection();` — can close poly if current segment intersects existing segment
- L283 _protected member_ `bool bHaveSelfIntersection;`
- L284 _protected member_ `int SelfIntersectSegmentIdx;`
- L285 _protected member_ `FVector3d SelfIntersectionPoint;`
- L288 _protected member_ `bool bHaveSurfaceHit;` — only used when SnapSettings.bSnapToSurfaces = true
- L289 _protected member_ `FVector3d SurfaceHitPoint;`
- L290 _protected member_ `FVector3d SurfaceOffsetPoint;`
- L292 _protected member_ `bool bIgnoreSnappingToggle = false;` — toggled by hotkey (shift)
- L293 _protected member_ `UE::Geometry::FPointPlanarSnapSolver SnapEngine;`
- L294 _protected member_ `ToolSceneQueriesUtil::FSnapGeometry LastSnapGeometry;`
- L295 _protected member_ `FVector3d LastGridSnapPoint;`
- L297 _protected prototype_ `void GetPolygonParametersFromFixedPoints(const TArray<FVector3d>& FixedPoints, FVector2d& FirstReferencePt, FVector2d& BoxSize, double& YSign, double& AngleRad);`
- L298 _protected prototype_ `void GenerateFixedPolygon(const TArray<FVector3d>& FixedPoints, TArray<FVector3d>& VerticesOut, TArray<TArray<FVector3d>>& HolesVerticesOut);`
- L303 _protected member_ `bool bInInteractiveExtrude = false;`
- L304 _protected member_ `bool bHasSavedExtrudeHeight = false;`
- L305 _protected member_ `float SavedExtrudeHeight;`
- L307 _protected prototype_ `void UpdateLivePreview();`
- L308 _protected member_ `bool bPreviewUpdatePending;`
- L311 _protected member_ `TObjectPtr<UPlaneDistanceFromHitMechanic> HeightMechanic;` — `UPROPERTY()`
- L314 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L317 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L320 _protected prototype_ `bool GeneratePolygonMesh(const TArray<FVector3d>& Polygon, const TArray<TArray<FVector3d>>& PolygonHoles, FDynamicMesh3* ResultMeshOut, UE::Geometry::FFrame3d& WorldFrameOut, bool bIncludePreviewVtx, double ExtrudeDistance, bool bExtrudeSymmetric);` — Generate extruded meshes.  Returns true on success.
- L324 _protected prototype_ `void ShowStartupMessage();` — user feedback messages
- L325 _protected prototype_ `void ShowExtrudeMessage();`
- L329 _protected member_ `int32 CurrentCurveTimestamp = 1;`
- L330 _protected prototype_ `void UndoCurrentOperation(const TArray<FVector3d>& ClickPointsIn, const TArray<FVector3d>& PolygonVerticesIn);`
- L331 _protected function_ `bool CheckInCurve(int32 Timestamp) const`
- L335 _private member_ `bool bRestoreInputSelection = true;` — if the drawn path is incomplete upon 'Accept' of the tool, no mesh should be created and the previous mesh element selection from before entering the tool should be restored

#### class `FDrawPolygonStateChange`  
`class FDrawPolygonStateChange : public FToolCommandChange`  
_L342-362_
- inherits: `FToolCommandChange`
- desc: Change event used by DrawPolygonTool to undo draw state. Currently does not redo.
- L345 _public member_ `bool bHaveDoneUndo = false;`
- L346 _public member_ `int32 CurveTimestamp = 0;`
- L347 _public member_ `const TArray<FVector3d> FixedVertexPoints;`
- L348 _public member_ `const TArray<FVector3d> PolyPoints;`
- L350 _public function_ `FDrawPolygonStateChange(int32 CurveTimestampIn, const TArray<FVector3d>& FixedVertexPointsIn, const TArray<FVector3d>& PolyPointsIn) : CurveTimestamp(CurveTimestampIn), FixedVertexPoints(FixedVertexPointsIn), PolyPoints(PolyPointsIn)`
- L358 _public function_ `virtual void Apply(UObject* Object) override`
- L359 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L360 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L361 _public prototype_ `virtual FString ToString() const override;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L27 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/DynamicMeshBrushTool.h` (Public)


#### class `UDynamicMeshBrushTool`  
`class UDynamicMeshBrushTool : public UBaseBrushTool`  
_L27-71_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBaseBrushTool`
- desc: UDynamicMeshBrushTool is a base class that specializes UBaseBrushTool for brushing on an FDynamicMesh3. The input FPrimitiveComponentTarget is hidden and a UPreviewMesh is created and shown in its place. This UPreviewMesh is used for hit-testing and dynamic rendering.
- L32 _public prototype_ `UDynamicMeshBrushTool();`
- L36 _public prototype_ `virtual void Setup() override;`
- L37 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L39 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;`
- L41 _public function_ `TObjectPtr<UPreviewMesh> GetPreviewMesh()`
- L45 _protected function_ `virtual void OnShutdown(EToolShutdownType ShutdownType)` — subclasses can override these to customize behavior
- L50 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L53 _protected function_ `virtual void OnBaseMeshComponentChanged()` — this function is called when the component inside the PreviewMesh is modified (eg via an undo/redo event)
- L54 _protected member_ `FDelegateHandle OnBaseMeshComponentChangedHandle;`
- L56 _protected member_ `UE::Geometry::FAxisAlignedBox3d InputMeshBoundsLocal;`
- L61 _protected member_ `bool bBakeRotateScale = false;` — When true during Setup(), Rotation and Scale will be baked into the PreviewMesh. The rotate/scale portion of the transform will be stored in BakedTargetTransform. The translate portion of the transform will be stored in CurrentTargetTransform.
- L62 _protected member_ `UE::Geometry::FTransformSRT3d BakedTargetTransform;`
- L63 _protected member_ `UE::Geometry::FTransformSRT3d CurrentTargetTransform;`
- L68 _protected prototype_ `virtual double EstimateMaximumTargetDimension() override;` — UBaseBrushTool private interface
- L70 _protected member_ `UE::TransactionUtil::FLongTransactionTracker LongTransactions;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L17 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/DynamicMeshSculptTool.h` (Public)


#### enum `EDynamicMeshSculptBrushType`  
`enum class EDynamicMeshSculptBrushType : uint8`  
_L44-96_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L47 _public enumerator_ `Move UMETA(DisplayName = "Move")` — Move vertices parallel to the view plane
- L50 _public enumerator_ `PullKelvin UMETA(DisplayName = "Kelvin Grab")` — Grab Brush, fall-off alters the influence of the grab
- L53 _public enumerator_ `PullSharpKelvin UMETA(DisplayName = "Sharp Kelvin Grab")` — Grab Brush that may generate cusps, fall-off alters the influence of the grab
- L56 _public enumerator_ `Smooth UMETA(DisplayName = "Smooth")` — Smooth mesh vertices
- L59 _public enumerator_ `Offset UMETA(DisplayName = "Sculpt (Normal)")` — Displace vertices along the average surface normal (Ctrl to invert)
- L62 _public enumerator_ `SculptView UMETA(DisplayName = "Sculpt (Viewpoint)")` — Displace vertices towards the camera viewpoint (Ctrl to invert)
- L65 _public enumerator_ `SculptMax UMETA(DisplayName = "Sculpt Max")` — Displaces vertices along the average surface normal to a maximum height based on the brush size (Ctrl to invert)
- L68 _public enumerator_ `Inflate UMETA(DisplayName = "Inflate")` — Displace vertices along their vertex normals
- L71 _public enumerator_ `ScaleKelvin UMETA(DisplayName = "Kelvin Scale")` — Scale Brush will inflate or pinch radially from the center of the brush
- L74 _public enumerator_ `Pinch UMETA(DisplayName = "Pinch")` — Move vertices towards the center of the brush (Ctrl to push away)
- L77 _public enumerator_ `TwistKelvin UMETA(DisplayName = "Kelvin Twist")` — Twist Brush moves vertices in the plane perpendicular to the local mesh normal
- L80 _public enumerator_ `Flatten UMETA(DisplayName = "Flatten")` — Move vertices towards the average plane of the brush stamp region
- L83 _public enumerator_ `Plane UMETA(DisplayName = "Plane (Normal)")` — Move vertices towards a plane defined by the initial brush position
- L86 _public enumerator_ `PlaneViewAligned UMETA(DisplayName = "Plane (Viewpoint)")` — Move vertices towards a view-facing plane defined at the initial brush position
- L89 _public enumerator_ `FixedPlane UMETA(DisplayName = "FixedPlane")` — Move vertices towards a fixed plane in world space, positioned with a 3D gizmo
- L92 _public enumerator_ `Resample UMETA(DisplayName = "Resample")` — Remesh the brushed region but do not otherwise deform it
- L94 _public enumerator_ `LastValue UMETA(Hidden)`

#### class `UDynamicMeshSculptToolBuilder`  
`class UDynamicMeshSculptToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L102-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: Tool Builder
- L107 _public member_ `bool bEnableRemeshing;`
- L109 _public function_ `UDynamicMeshSculptToolBuilder()`
- L114 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L116 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UDynamicMeshBrushProperties`  
`class UDynamicMeshBrushProperties : public UInteractiveToolPropertySet`  
_L124-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L129 _public member_ `FBrushToolRadius BrushSize;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayPriority = 1))`
- L133 _public member_ `float BrushFalloffAmount = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", DisplayPriority = 3))` — Amount of falloff to apply (0.0 - 1.0)
- L137 _public member_ `float Depth = 0;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = "-0.5", UIMax = "0.5", ClampMin = "-1.0", ClampMax = "1.0", DisplayPriority = 5))` — Depth of Brush into surface along view ray or surface normal, depending on the Active Brush Type
- L141 _public member_ `bool bHitBackFaces = true;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayPriority = 6))` — Allow the Brush to hit the back-side of the mesh

#### class `UDynamicMeshBrushSculptProperties`  
`class UDynamicMeshBrushSculptProperties : public UInteractiveToolPropertySet`  
_L149-181_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L156 _public member_ `bool bIsRemeshingEnabled = false;` — `UPROPERTY(meta = (TransientToolProperty))` — This is a dupe of the bool in the tool class.  I needed it here so it could be checked as an EditCondition
- L160 _public member_ `EDynamicMeshSculptBrushType PrimaryBrushType = EDynamicMeshSculptBrushType::Move;` — `UPROPERTY(EditAnywhere, Category = Sculpting, meta = (DisplayName = "Brush Type"))` — Primary Brush Mode
- L164 _public member_ `float PrimaryBrushSpeed = 0.5;` — `UPROPERTY(EditAnywhere, Category = Sculpting, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "PrimaryBrushType != EDynamicMeshSculptBrushType::Pull", ModelingQuickEdit))` — Strength of the Primary Brush
- L168 _public member_ `bool bPreserveUVFlow = false;` — `UPROPERTY(EditAnywhere, Category = Sculpting)` — If true, try to preserve the shape of the UV/3D mapping. This will limit Smoothing and Remeshing in some cases.
- L172 _public member_ `bool bFreezeTarget = false;` — `UPROPERTY(EditAnywhere, Category = Sculpting, meta = (EditCondition = "PrimaryBrushType == EDynamicMeshSculptBrushType::Sculpt || PrimaryBrushType == EDynamicMeshSculptBrushType::SculptMax || PrimaryBrushType == EDynamicMeshSculptBrushType::SculptView || PrimaryBrushType == EDynamicMeshSculptBrushType::Pinch || PrimaryBrushType == EDynamicMeshSculptBrushType::Resample" ))` — When Freeze Target is toggled on, the Brush Target Surface will be Frozen in its current state, until toggled off. Brush strokes will be applied relative to the Target Surface, for applicable Brushes
- L176 _public member_ `float SmoothBrushSpeed = 0.25;` — `UPROPERTY(EditAnywhere, Category = Smoothing, meta = (DisplayName = "Smoothing Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Strength of Shift-to-Smooth Brushing and Smoothing Brush
- L180 _public member_ `bool bDetailPreservingSmooth = true;` — `UPROPERTY(EditAnywhere, Category = Smoothing, meta = (DisplayName = "Preserve Tri Density", EditConditionHides, HideEditConditionToggle, EditCondition = "bIsRemeshingEnabled"))` — If enabled, Remeshing is limited during Smoothing to avoid wiping out higher-density triangle areas

#### class `UDynamicSculptToolActions`  
`class UDynamicSculptToolActions : public UInteractiveToolPropertySet`  
_L185-195_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L189 _public member_ `TWeakObjectPtr<UDynamicMeshSculptTool> ParentTool;`
- L191 _public function_ `void Initialize(UDynamicMeshSculptTool* ParentToolIn)`
- L194 _public prototype_ `void DiscardAttributes();` — `UFUNCTION(CallInEditor, Category = MeshEdits)`

#### class `UBrushRemeshProperties`  
`class UBrushRemeshProperties : public URemeshProperties`  
_L201-221_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URemeshProperties`
- L208 _public member_ `bool bEnableRemeshing = true;` — `UPROPERTY(EditAnywhere, Category = Remeshing, meta = (DisplayPriority = 1))` — Toggle remeshing on/off
- L213 _public member_ `int TriangleSize = 0;` — `UPROPERTY(EditAnywhere, Category = Remeshing, meta = (DisplayName = "Relative Tri Size", UIMin = "-5", UIMax = "5", ClampMin = "-5", ClampMax = "5", DisplayPriority = 2))` — Desired size of triangles after Remeshing, relative to average initial triangle size. Larger value results in larger triangles.
- L217 _public member_ `int PreserveDetail = 0;` — `UPROPERTY(EditAnywhere, Category = Remeshing, meta = (UIMin = "0", UIMax = "5", ClampMin = "0", ClampMax = "5", DisplayPriority = 3))` — Control the amount of simplification during sculpting. Higher values will avoid wiping out fine details on the mesh.
- L220 _public member_ `int Iterations = 5;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay)`

#### class `UFixedPlaneBrushProperties`  
`class UFixedPlaneBrushProperties : public UInteractiveToolPropertySet`  
_L226-254_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L232 _public member_ `bool bPropertySetEnabled = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L236 _public member_ `bool bShowGizmo = true;` — `UPROPERTY(EditAnywhere, Category = TargetPlane, meta = (HideEditConditionToggle, EditCondition = "bPropertySetEnabled == true"))` — Toggle whether Work Plane Positioning Gizmo is visible
- L239 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = TargetPlane, AdvancedDisplay, meta = (HideEditConditionToggle, EditCondition = "bPropertySetEnabled == true"))`
- L242 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = TargetPlane, AdvancedDisplay, meta = (HideEditConditionToggle, EditCondition = "bPropertySetEnabled == true"))`
- L245 _public function_ `void RecenterGizmoIfFar(FVector CenterPosition, double BoundsMaxDim, double TooFarDistance = 1000)` — Recenter the gizmo around the target position (without changing work plane), if it is "too far" (> 10 meters + max bounds dim) from that position currently

#### class `UDynamicMeshSculptTool`  
`class UDynamicMeshSculptTool : public UMeshSurfacePointTool`  
_L263-548_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointTool`
- desc: Dynamic Mesh Sculpt Tool Class
- L268 _public typedef_ `using FFrame3d = UE::Geometry::FFrame3d;`
- L270 _public prototype_ `UDynamicMeshSculptTool();`
- L272 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L273 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L275 _public prototype_ `virtual void Setup() override;`
- L276 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L278 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L279 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L280 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L282 _public function_ `virtual bool HasCancel() const override`
- L283 _public function_ `virtual bool HasAccept() const override`
- L285 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;`
- L287 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L288 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L289 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L290 _public prototype_ `virtual void OnCancelDrag() override;`
- L292 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L293 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L295 _public function_ `virtual void SetEnableRemeshing(bool bEnable)`
- L296 _public function_ `virtual bool GetEnableRemeshing() const`
- L298 _public prototype_ `virtual void DiscardAttributes();`
- L300 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L303 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI override to focus on brush w/ 'F'
- L308 _public member_ `TObjectPtr<UDynamicMeshBrushProperties> BrushProperties;` — `UPROPERTY()` — Properties that control brush size/etc
- L312 _public member_ `TObjectPtr<UDynamicMeshBrushSculptProperties> SculptProperties;` — `UPROPERTY()` — Properties that control sculpting
- L315 _public member_ `TObjectPtr<USculptMaxBrushProperties> SculptMaxBrushProperties;` — `UPROPERTY()`
- L318 _public member_ `TObjectPtr<UKelvinBrushProperties> KelvinBrushProperties;` — `UPROPERTY()`
- L322 _public member_ `TObjectPtr<UBrushRemeshProperties> RemeshProperties;` — `UPROPERTY()` — Properties that control dynamic remeshing
- L325 _public member_ `TObjectPtr<UFixedPlaneBrushProperties> GizmoProperties;` — `UPROPERTY()`
- L328 _public member_ `TObjectPtr<UMeshEditingViewProperties> ViewProperties;` — `UPROPERTY()`
- L331 _public member_ `TObjectPtr<UDynamicSculptToolActions> SculptToolActions;` — `UPROPERTY()`
- L334 _public prototype_ `virtual void IncreaseBrushRadiusAction();`
- L335 _public prototype_ `virtual void DecreaseBrushRadiusAction();`
- L336 _public prototype_ `virtual void IncreaseBrushRadiusSmallStepAction();`
- L337 _public prototype_ `virtual void DecreaseBrushRadiusSmallStepAction();`
- L339 _public prototype_ `virtual void IncreaseBrushSpeedAction();`
- L340 _public prototype_ `virtual void DecreaseBrushSpeedAction();`
- L342 _public prototype_ `virtual void NextHistoryBrushModeAction();`
- L343 _public prototype_ `virtual void PreviousHistoryBrushModeAction();`
- L346 _private member_ `UWorld* TargetWorld;` — required to spawn UPreviewMesh/etc
- L347 _private member_ `FViewCameraState CameraState;`
- L349 _private member_ `TWeakObjectPtr<ULocalTwoAxisPropertyEditInputBehavior> BrushEditBehavior;`
- L352 _private member_ `TObjectPtr<UBrushStampIndicator> BrushIndicator;` — `UPROPERTY()`
- L355 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BrushIndicatorMaterial;` — `UPROPERTY()`
- L358 _private member_ `TObjectPtr<UPreviewMesh> BrushIndicatorMesh;` — `UPROPERTY()`
- L361 _private member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L364 _private member_ `TObjectPtr<UOctreeDynamicMeshComponent> DynamicMeshComponent;` — `UPROPERTY()`
- L367 _private member_ `TObjectPtr<UMaterialInstanceDynamic> ActiveOverrideMaterial;` — `UPROPERTY()`
- L369 _private member_ `UE::Geometry::FTransformSRT3d InitialTargetTransform;`
- L370 _private member_ `UE::Geometry::FTransformSRT3d CurTargetTransform;`
- L373 _private prototype_ `void OnDynamicMeshComponentChanged();` — realtime visualization
- L374 _private member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L376 _private member_ `TValueWatcher<bool> ShowWireframeWatcher;`
- L377 _private member_ `TValueWatcher<EMeshEditingMaterialModes> MaterialModeWatcher;`
- L378 _private member_ `TValueWatcher<TWeakObjectPtr<UMaterialInterface>> CustomMaterialWatcher;`
- L379 _private member_ `TValueWatcher<bool> FlatShadingWatcher;`
- L380 _private member_ `TValueWatcher<FLinearColor> ColorWatcher;`
- L381 _private member_ `TValueWatcher<FLinearColor> TransparentColorWatcher;`
- L382 _private member_ `TValueWatcher<double> OpacityWatcher;`
- L383 _private member_ `TValueWatcher<bool> TwoSidedWatcher;`
- L384 _private member_ `TValueWatcher<UTexture2D*> ImageWatcher;`
- L385 _private member_ `TValueWatcher<EDynamicMeshSculptBrushType> BrushTypeWatcher;`
- L386 _private member_ `TValueWatcher<FVector> GizmoPositionWatcher;`
- L387 _private member_ `TValueWatcher<FQuat> GizmoRotationWatcher;`
- L388 _private prototype_ `void UpdateMaterialMode(EMeshEditingMaterialModes NewMode);`
- L389 _private prototype_ `void UpdateFlatShadingSetting(bool bNewValue);`
- L390 _private prototype_ `void UpdateColorSetting(FLinearColor NewColor);`
- L391 _private prototype_ `void UpdateOpacitySetting(double Opacity);`
- L392 _private prototype_ `void UpdateTwoSidedSetting(bool bOn);`
- L393 _private prototype_ `void UpdateCustomMaterial(TWeakObjectPtr<UMaterialInterface> NewMaterial);`
- L394 _private prototype_ `void UpdateImageSetting(UTexture2D* NewImage);`
- L395 _private prototype_ `void UpdateBrushType(EDynamicMeshSculptBrushType BrushType);`
- L396 _private prototype_ `void UpdateGizmoFromProperties();`
- L398 _private member_ `UE::Geometry::FInterval1d BrushRelativeSizeRange;`
- L399 _private member_ `double CurrentBrushRadius;`
- L400 _private prototype_ `void CalculateBrushRadius();`
- L402 _private member_ `bool bEnableRemeshing;`
- L403 _private member_ `double InitialEdgeLength;`
- L404 _private prototype_ `void ScheduleRemeshPass();`
- L405 _private prototype_ `void ConfigureRemesher(UE::Geometry::FSubRegionRemesher& Remesher);`
- L406 _private prototype_ `void InitializeRemesherROI(UE::Geometry::FSubRegionRemesher& Remesher);`
- L408 _private member_ `TSharedPtr<FPersistentStampRemesher> ActiveRemesher;`
- L409 _private prototype_ `void InitializeActiveRemesher();`
- L410 _private prototype_ `void PrecomputeRemesherROI();`
- L411 _private prototype_ `void RemeshROIPass_ActiveRemesher(bool bHasPrecomputedROI);`
- L414 _private member_ `bool bInDrag;`
- L416 _private member_ `UE::Geometry::FFrame3d ActiveDragPlane;`
- L417 _private member_ `FVector3d LastHitPosWorld;`
- L418 _private member_ `FVector3d BrushStartCenterWorld;`
- L419 _private member_ `FVector3d BrushStartNormalWorld;`
- L420 _private member_ `FVector3d LastBrushPosLocal;`
- L421 _private member_ `FVector3d LastBrushPosWorld;`
- L422 _private member_ `FVector3d LastBrushPosNormalWorld;`
- L423 _private member_ `FVector3d LastSmoothBrushPosLocal;`
- L424 _private member_ `int32 LastBrushTriangleID = -1;`
- L426 _private member_ `TArray<int> UpdateROITriBuffer;`
- L427 _private member_ `UE::Geometry::FUniqueIndexSet VertexROIBuilder;`
- L428 _private member_ `TArray<int> VertexROI;`
- L429 _private member_ `UE::Geometry::FUniqueIndexSet TriangleROIBuilder;`
- L430 _private member_ `TSet<int> TriangleROI;`
- L432 _private prototype_ `void UpdateROI(const FVector3d& BrushPos);` — TSet<int> TriangleROI;
- L434 _private member_ `bool bRemeshPending;`
- L435 _private member_ `bool bNormalUpdatePending;`
- L437 _private member_ `bool bTargetDirty;`
- L438 _private member_ `TFuture<void> PendingTargetUpdate;`
- L440 _private member_ `bool bSmoothing;`
- L441 _private member_ `bool bInvert;`
- L442 _private member_ `float ActivePressure = 1.0f;`
- L444 _private member_ `bool bHaveRemeshed;`
- L446 _private member_ `bool bStampPending;`
- L447 _private member_ `FRay PendingStampRay;`
- L448 _private member_ `int StampTimestamp = 0;`
- L449 _private member_ `EDynamicMeshSculptBrushType LastStampType = EDynamicMeshSculptBrushType::LastValue;`
- L450 _private member_ `EDynamicMeshSculptBrushType PendingStampType = LastStampType;`
- L451 _private prototype_ `void ApplyStamp(const FRay& WorldRay);`
- L453 _private member_ `FDynamicMesh3 BrushTargetMesh;`
- L454 _private member_ `UE::Geometry::FDynamicMeshAABBTree3 BrushTargetMeshSpatial;`
- L455 _private member_ `UE::Geometry::FMeshNormals BrushTargetNormals;`
- L456 _private member_ `bool bCachedFreezeTarget = false;`
- L457 _private prototype_ `void UpdateTarget();`
- L458 _private prototype_ `bool GetTargetMeshNearest(const FVector3d& Position, double SearchRadius, FVector3d& TargetPosOut, FVector3d& TargetNormalOut);`
- L460 _private prototype_ `int FindHitSculptMeshTriangle(const FRay3d& LocalRay);`
- L461 _private prototype_ `int FindHitTargetMeshTriangle(const FRay3d& LocalRay);`
- L462 _private prototype_ `bool IsHitTriangleBackFacing(int32 TriangleID, const FDynamicMesh3* QueryMesh);`
- L464 _private prototype_ `bool UpdateBrushPosition(const FRay& WorldRay);`
- L465 _private prototype_ `bool UpdateBrushPositionOnActivePlane(const FRay& WorldRay);`
- L466 _private prototype_ `bool UpdateBrushPositionOnTargetMesh(const FRay& WorldRay, bool bFallbackToViewPlane);`
- L467 _private prototype_ `bool UpdateBrushPositionOnSculptMesh(const FRay& WorldRay, bool bFallbackToViewPlane);`
- L468 _private prototype_ `void AlignBrushToView();`
- L470 _private prototype_ `bool ApplySmoothBrush(const FRay& WorldRay);`
- L471 _private prototype_ `bool ApplyMoveBrush(const FRay& WorldRay);`
- L472 _private prototype_ `bool ApplyOffsetBrush(const FRay& WorldRay, bool bUseViewDirection);`
- L473 _private prototype_ `bool ApplySculptMaxBrush(const FRay& WorldRay);`
- L474 _private prototype_ `bool ApplyPinchBrush(const FRay& WorldRay);`
- L475 _private prototype_ `bool ApplyInflateBrush(const FRay& WorldRay);`
- L476 _private prototype_ `bool ApplyPlaneBrush(const FRay& WorldRay);`
- L477 _private prototype_ `bool ApplyFixedPlaneBrush(const FRay& WorldRay);`
- L478 _private prototype_ `bool ApplyFlattenBrush(const FRay& WorldRay);`
- L479 _private prototype_ `bool ApplyResampleBrush(const FRay& WorldRay);`
- L480 _private prototype_ `bool ApplyPullKelvinBrush(const FRay& WorldRay);`
- L481 _private prototype_ `bool ApplyPullSharpKelvinBrush(const FRay& WorldRay);`
- L482 _private prototype_ `bool ApplyTwistKelvinBrush(const FRay& WorldRay);`
- L483 _private prototype_ `bool ApplyScaleKelvinBrush(const FRay& WorldRay);`
- L485 _private member_ `double SculptMaxFixedHeight = -1.0;`
- L487 _private prototype_ `double CalculateBrushFalloff(double Distance);`
- L488 _private member_ `TArray<FVector3d> ROIPositionBuffer;`
- L489 _private prototype_ `void SyncMeshWithPositionBuffer(FDynamicMesh3* Mesh);`
- L491 _private member_ `UE::Geometry::FFrame3d ActiveFixedBrushPlane;`
- L492 _private prototype_ `UE::Geometry::FFrame3d ComputeROIBrushPlane(const FVector3d& BrushCenter, bool bIgnoreDepth, bool bViewAligned);`
- L494 _private member_ `TArray<int> NormalsBuffer;`
- L495 _private member_ `TArray<bool> NormalsVertexFlags;`
- L496 _private prototype_ `void RecalculateNormals_PerVertex(const TSet<int32>& Triangles);`
- L497 _private prototype_ `void RecalculateNormals_Overlay(const TSet<int32>& Triangles);`
- L499 _private member_ `bool bHaveMeshBoundaries;`
- L500 _private member_ `bool bHaveUVSeams;`
- L501 _private member_ `bool bHaveNormalSeams;`
- L502 _private member_ `TSet<int32> RemeshRemovedTriangles;`
- L503 _private member_ `TSet<int32> RemeshFinalTriangleROI;`
- L504 _private prototype_ `void PrecomputeRemeshInfo();`
- L505 _private prototype_ `void RemeshROIPass();`
- L507 _private member_ `FMeshVertexChangeBuilder* ActiveVertexChange = nullptr;`
- L508 _private member_ `UE::Geometry::FDynamicMeshChangeTracker* ActiveMeshChange = nullptr;`
- L509 _private member_ `UE::TransactionUtil::FLongTransactionTracker LongTransactions;`
- L511 _private prototype_ `void BeginChange(bool bIsVertexChange);`
- L512 _private prototype_ `void EndChange();`
- L513 _private prototype_ `void CancelChange();`
- L514 _private prototype_ `void SaveActiveROI();`
- L516 _private prototype_ `double EstimateIntialSafeTargetLength(const FDynamicMesh3& Mesh, int MinTargetTriCount);`
- L518 _private member_ `TArray<EDynamicMeshSculptBrushType> BrushTypeHistory;`
- L519 _private member_ `int BrushTypeHistoryIndex = 0;`
- L521 _private prototype_ `UPreviewMesh* MakeDefaultSphereMesh(UObject* Parent, UWorld* World, int Resolution = 32);`
- L529 _private member_ `TObjectPtr<UCombinedTransformGizmo> PlaneTransformGizmo;` — `UPROPERTY()` — plane gizmo
- L532 _private member_ `TObjectPtr<UTransformProxy> PlaneTransformProxy;` — `UPROPERTY()`
- L534 _private prototype_ `void PlaneTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L543 _private member_ `EPendingWorkPlaneUpdate PendingWorkPlaneUpdate;`
- L544 _private prototype_ `void SetFixedSculptPlaneFromWorldPos(const FVector& Position, const FVector& Normal, EPendingWorkPlaneUpdate UpdateType);`
- L545 _private prototype_ `void UpdateFixedSculptPlanePosition(const FVector& Position);`
- L546 _private prototype_ `void UpdateFixedSculptPlaneRotation(const FQuat& Rotation);`
- L547 _private prototype_ `void UpdateFixedPlaneGizmoVisibility(bool bVisible);`

#### enum `UDynamicMeshSculptTool::EPendingWorkPlaneUpdate`  
`enum class EPendingWorkPlaneUpdate`  
_L536-542_
- L538 _public enumerator_ `NoUpdatePending`
- L539 _public enumerator_ `MoveToHitPositionNormal`
- L540 _public enumerator_ `MoveToHitPosition`
- L541 _public enumerator_ `MoveToHitPositionViewAligned`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L36 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMeshChangeTracker);`
- L37 _prototype_ `PREDECLARE_GEOMETRY(class FSubRegionRemesher);`
- L38 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/EditMeshPolygonsTool.h` (Public)


#### class `UEditMeshPolygonsToolBuilder`  
`class UEditMeshPolygonsToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L50-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionToolBuilder`
- desc: ToolBuilder
- L54 _public member_ `bool bTriangleMode = false;`
- L56 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L57 _public prototype_ `virtual void InitializeNewTool(USingleTargetWithSelectionTool* Tool, const FToolBuilderState& SceneState) const override;`
- L59 _public function_ `virtual bool RequiresInputSelection() const override`

#### enum `ELocalFrameMode`  
`enum class ELocalFrameMode`  
_L64-68_
- reflection: `UENUM()`
- L66 _public enumerator_ `FromObject`
- L67 _public enumerator_ `FromGeometry`

#### class `UPolyEditCommonProperties`  
`class UPolyEditCommonProperties : public UInteractiveToolPropertySet`  
_L75-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: These are properties that do not get enabled/disabled based on the action
- L81 _public member_ `bool bShowWireframe = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L84 _public member_ `bool bShowSelectableCorners = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L88 _public member_ `bool bGizmoVisible = true;` — `UPROPERTY(EditAnywhere, Category = Gizmo)` — When true, allows the transform gizmo to be rendered
- L93 _public member_ `ELocalFrameMode LocalFrameMode = ELocalFrameMode::FromGeometry;` — `UPROPERTY(EditAnywhere, Category = Gizmo, meta = (HideEditConditionToggle, EditCondition = "bLocalCoordSystem && !bLockRotation"))` — Determines whether, on selection changes, the gizmo's rotation is taken from the object transform, or from the geometry elements selected. Only relevant with a local coordinate system and when rotation is not locked.
- L98 _public member_ `bool bLockRotation = false;` — `UPROPERTY(EditAnywhere, Category = Gizmo, meta = (HideEditConditionToggle, EditCondition = "bLocalCoordSystem"))` — When true, keeps rotation of gizmo constant through selection changes and manipulations (but not middle-click repositions). Only active with a local coordinate system.
- L102 _public member_ `bool bLocalCoordSystem = true;` — `UPROPERTY()` — This gets updated internally so that properties can respond to whether the coordinate system is set to local or global

#### enum `EEditMeshPolygonsToolActions`  
`enum class EEditMeshPolygonsToolActions`  
_L107-156_
- reflection: `UENUM()`
- L109 _public enumerator_ `NoAction`
- L110 _public enumerator_ `AcceptCurrent`
- L111 _public enumerator_ `CancelCurrent`
- L112 _public enumerator_ `Extrude`
- L113 _public enumerator_ `PushPull`
- L114 _public enumerator_ `Offset`
- L115 _public enumerator_ `Inset`
- L116 _public enumerator_ `Outset`
- L117 _public enumerator_ `BevelFaces`
- L118 _public enumerator_ `InsertEdge`
- L119 _public enumerator_ `InsertEdgeLoop`
- L120 _public enumerator_ `Complete`
- L122 _public enumerator_ `PlaneCut`
- L123 _public enumerator_ `Merge`
- L124 _public enumerator_ `Delete`
- L125 _public enumerator_ `CutFaces`
- L126 _public enumerator_ `RecalculateNormals`
- L127 _public enumerator_ `FlipNormals`
- L128 _public enumerator_ `Retriangulate`
- L129 _public enumerator_ `Decompose`
- L130 _public enumerator_ `Disconnect`
- L131 _public enumerator_ `Duplicate`
- L133 _public enumerator_ `CollapseEdge`
- L134 _public enumerator_ `WeldEdges`
- L135 _public enumerator_ `WeldEdgesCentered`
- L136 _public enumerator_ `StraightenEdge`
- L137 _public enumerator_ `FillHole`
- L138 _public enumerator_ `BridgeEdges`
- L139 _public enumerator_ `ExtrudeEdges`
- L140 _public enumerator_ `BevelEdges`
- L141 _public enumerator_ `SimplifyAlongEdges`
- L143 _public enumerator_ `PlanarProjectionUV`
- L145 _public enumerator_ `SimplifyByGroups`
- L146 _public enumerator_ `RegenerateExtraCorners`
- L149 _public enumerator_ `PokeSingleFace` — triangle-specific edits
- L150 _public enumerator_ `SplitSingleEdge`
- L151 _public enumerator_ `FlipSingleEdge`
- L152 _public enumerator_ `CollapseSingleEdge`
- L155 _public enumerator_ `BevelAuto` — for external use

#### class `UEditMeshPolygonsActionModeToolBuilder`  
`class UEditMeshPolygonsActionModeToolBuilder : public UEditMeshPolygonsToolBuilder`  
_L159-167_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolBuilder`
- L163 _public member_ `EEditMeshPolygonsToolActions StartupAction = EEditMeshPolygonsToolActions::Extrude;`
- L165 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L166 _public prototype_ `virtual void InitializeNewTool(USingleTargetWithSelectionTool* Tool, const FToolBuilderState& SceneState) const override;`

#### enum `EEditMeshPolygonsToolSelectionMode`  
`enum class EEditMeshPolygonsToolSelectionMode`  
_L170-178_
- reflection: `UENUM()`
- L172 _public enumerator_ `Faces`
- L173 _public enumerator_ `Edges`
- L174 _public enumerator_ `Vertices`
- L175 _public enumerator_ `Loops`
- L176 _public enumerator_ `Rings`
- L177 _public enumerator_ `FacesEdgesVertices`

#### class `UEditMeshPolygonsSelectionModeToolBuilder`  
`class UEditMeshPolygonsSelectionModeToolBuilder : public UEditMeshPolygonsToolBuilder`  
_L181-189_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolBuilder`
- L185 _public member_ `EEditMeshPolygonsToolSelectionMode SelectionMode = EEditMeshPolygonsToolSelectionMode::Faces;`
- L187 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L188 _public prototype_ `virtual void InitializeNewTool(USingleTargetWithSelectionTool* Tool, const FToolBuilderState& SceneState) const override;`

#### class `UEditMeshPolygonsToolActionPropertySet`  
`class UEditMeshPolygonsToolActionPropertySet : public UInteractiveToolPropertySet`  
_L194-204_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L199 _public member_ `TWeakObjectPtr<UEditMeshPolygonsTool> ParentTool;`
- L201 _public function_ `void Initialize(UEditMeshPolygonsTool* ParentToolIn)`
- L203 _public prototype_ `void PostAction(EEditMeshPolygonsToolActions Action);`

#### class `UPolyEditTopologyProperties`  
`class UPolyEditTopologyProperties : public UEditMeshPolygonsToolActionPropertySet`  
_L207-235_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolActionPropertySet`
- L221 _public member_ `bool bAddExtraCorners = true;` — `UPROPERTY(EditAnywhere, Category = TopologyOptions)` — When true, adds extra corners at sharp group edge bends (in addition to the normal corners that are placed at junctures of three or more group edges). For instance, a single disconnected quad-like group would normally have a single group edge with no corners, since it has no neighboring groups, but this setting will allow for the generation of corners at the quad corners, which is very useful for editing. Note that the setting takes effect only after clicking Regenerate Extra Corners or performing some operation that changes the group topology.
- L224 _public function_ `void RegenerateExtraCorners()` — `UFUNCTION(CallInEditor, Category = TopologyOptions)`
- L234 _public member_ `double ExtraCornerAngleThresholdDegrees = 135;` — `UPROPERTY(EditAnywhere, Category = TopologyOptions, meta = (ClampMin = "0", ClampMax = "180", EditCondition = "bAddExtraCorners"))` — When generating extra corners, how sharp the angle needs to be to warrant an extra corner placement there. Lower values require sharper corners, so are more tolerant of curved group edges. For instance, 180 will place corners at every vertex along a group edge even if the edge is perfectly straight, and 135 will place a vertex only once the edge bends 45 degrees off the straight path (i.e. 135 degrees to the previous edge). The setting is applied either when Regenerate Extra Corners is clicked, or after any operation that modifies topology.

#### class `UEditMeshPolygonsToolActions`  
`class UEditMeshPolygonsToolActions : public UEditMeshPolygonsToolActionPropertySet`  
_L239-323_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolActionPropertySet`
- desc: PolyEdit Actions
- L245 _public function_ `void Extrude()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Extrude", DisplayPriority = 1))` — Extrude the current set of selected faces by moving and stitching them.
- L249 _public function_ `void PushPull()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Push/Pull", DisplayPriority = 1))` — Like Extrude/Offset, but performed in a boolean way, meaning that the faces can cut away the mesh or bridge mesh parts.
- L253 _public function_ `void Offset()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Offset", DisplayPriority = 1))` — Like Extrude, but defaults to moving verts along vertex normals instead of a single direction.
- L261 _public function_ `void Inset()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Inset", DisplayPriority = 2))` — Inset the current set of selected faces. Click in viewport to confirm inset distance. (An Inset operation stitches in a smaller version of selected faces inside the existing ones)
- L269 _public function_ `void Outset()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Outset", DisplayPriority = 3))` — Outset the current set of selected faces. Click in viewport to confirm outset distance. (An Outset operation stitches in a larger version of selected faces inside the existing ones)
- L273 _public function_ `void Bevel()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Bevel", DisplayPriority = 4))` — Bevel the edge loops around the selected faces, inserting edge-aligned faces that interpolate the normals of the selected faces
- L277 _public function_ `void Merge()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Merge", DisplayPriority = 4))` — Merge the current set of selected faces into a single face
- L281 _public function_ `void Delete()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Delete Faces", DisplayPriority = 4))` — Delete the current set of selected faces
- L285 _public function_ `void CutFaces()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "CutFaces", DisplayPriority = 5))` — Cut the current set of selected faces. Click twice in viewport to set cut line.
- L289 _public function_ `void RecalcNormals()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "RecalcNormals", DisplayPriority = 6))` — Recalculate normals for the current set of selected faces
- L293 _public function_ `void Flip()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Flip", DisplayPriority = 7))` — Flip normals and face orientation for the current set of selected faces
- L297 _public function_ `void Retriangulate()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Retriangulate", DisplayPriority = 9))` — Retriangulate each of the selected faces
- L301 _public function_ `void Decompose()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Decompose", DisplayPriority = 10))` — Split each of the selected faces into a separate polygon for each triangle
- L305 _public function_ `void Disconnect()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Disconnect", DisplayPriority = 11))` — Separate the selected faces at their borders
- L309 _public function_ `void Duplicate()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Duplicate", DisplayPriority = 12))` — Duplicate the selected faces at their borders
- L313 _public function_ `void InsertEdgeLoop()` — `UFUNCTION(CallInEditor, Category = ShapeEdits, meta = (DisplayName = "InsertEdgeLoop", DisplayPriority = 13))` — Insert a chain of edges across quads (faces with four edges) in the mesh. Due to ambiguity, edges will not be inserted on non-quad faces.
- L317 _public function_ `void InsertEdge()` — `UFUNCTION(CallInEditor, Category = ShapeEdits, meta = (DisplayName = "Insert Edge", DisplayPriority = 14))` — Insert a new edge connecting existing edges or vertices on a single face
- L321 _public function_ `void SimplifyByGroups()` — `UFUNCTION(CallInEditor, Category = ShapeEdits, meta = (DisplayName = "SimplifyByGroups", DisplayPriority = 15))` — Simplify every polygon group by removing vertices on shared straight edges and retriangulating

#### class `UEditMeshPolygonsToolActions_Triangles`  
`class UEditMeshPolygonsToolActions_Triangles : public UEditMeshPolygonsToolActionPropertySet`  
_L328-379_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolActionPropertySet`
- L334 _public function_ `void Extrude()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Extrude", DisplayPriority = 1))` — Extrude the current set of selected faces. Click in viewport to confirm extrude height.
- L338 _public function_ `void PushPull()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Push/Pull", DisplayPriority = 1))` — Like Extrude/Offset, but performed in a boolean way, meaning that the faces can cut away the mesh or bridge mesh parts.
- L342 _public function_ `void Offset()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Offset", DisplayPriority = 1))` — Like Extrude, but defaults to moving verts along vertex normals instead of a single direction.
- L346 _public function_ `void Inset()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Inset", DisplayPriority = 2))` — Inset the current set of selected faces. Click in viewport to confirm inset distance.
- L350 _public function_ `void Outset()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Outset", DisplayPriority = 3))` — Outset the current set of selected faces. Click in viewport to confirm outset distance.
- L354 _public function_ `void Delete()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Delete Faces", DisplayPriority = 4))` — Delete the current set of selected faces
- L358 _public function_ `void CutFaces()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "CutFaces", DisplayPriority = 5))` — Cut the current set of selected faces. Click twice in viewport to set cut line.
- L362 _public function_ `void RecalcNormals()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "RecalcNormals", DisplayPriority = 6))` — Recalculate normals for the current set of selected faces
- L366 _public function_ `void Flip()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Flip", DisplayPriority = 7))` — Flip normals and face orientation for the current set of selected faces
- L370 _public function_ `void Disconnect()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Disconnect", DisplayPriority = 11))` — Separate the selected faces at their borders
- L374 _public function_ `void Duplicate()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Duplicate", DisplayPriority = 12))` — Duplicate the selected faces
- L378 _public function_ `void Poke()` — `UFUNCTION(CallInEditor, Category = TriangleEdits, meta = (DisplayName = "Poke", DisplayPriority = 13))` — Insert a new vertex at the center of each selected face

#### class `UEditMeshPolygonsToolUVActions`  
`class UEditMeshPolygonsToolUVActions : public UEditMeshPolygonsToolActionPropertySet`  
_L386-398_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolActionPropertySet`
- L394 _public function_ `void PlanarProjection()` — `UFUNCTION(CallInEditor, Category = UVs, meta = (DisplayName = "PlanarProjection", DisplayPriority = 11))` — Assign planar-projection UVs to mesh

#### class `UEditMeshPolygonsToolEdgeActions`  
`class UEditMeshPolygonsToolEdgeActions : public UEditMeshPolygonsToolActionPropertySet`  
_L405-448_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolActionPropertySet`
- L411 _public function_ `void WeldCentered()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Weld", DisplayPriority = 0))` — Merge selected boundary edges, centering the result
- L415 _public function_ `void Weld()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Weld To", DisplayPriority = 1))` — Merge selected boundary edges, moving the first edge to the second
- L419 _public function_ `void Straighten()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Straighten", DisplayPriority = 2))` — Make each selected polygroup edge follow a straight path between its endpoints
- L423 _public function_ `void FillHole()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Fill Hole", DisplayPriority = 3))` — Fill the adjacent hole for any selected boundary edges
- L427 _public function_ `void Bevel()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Bevel", DisplayPriority = 4))` — Bevel the selected edges, replacing them with angled faces
- L431 _public function_ `void Bridge()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Bridge", DisplayPriority = 5))` — Create a new face that connects the selected edges
- L435 _public function_ `void Extrude()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayPriority = 6))` — Duplicate and move boundary edge vertices outwards and connect them to the original boundary to create new faces.
- L439 _public function_ `void Simplify()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayPriority = 7))` — Simplify the underlying triangulation along the selected edges, when doing so won't change the shape or UVs, or make low-quality triangles
- L443 _public function_ `void DeleteEdge()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Delete Edges", DisplayPriority = 8))` — Delete selected edge, implicitly merging any connected faces
- L447 _public function_ `void Collapse()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Collapse", DisplayPriority = 5))` — Collapse the selected edges, deleting the attached triangles and merging their vertices into one

#### class `UEditMeshPolygonsToolEdgeActions_Triangles`  
`class UEditMeshPolygonsToolEdgeActions_Triangles : public UEditMeshPolygonsToolActionPropertySet`  
_L452-487_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditMeshPolygonsToolActionPropertySet`
- L458 _public function_ `void WeldCentered()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Weld", DisplayPriority = 0))` — Merge selected boundary edges, centering the result
- L462 _public function_ `void Weld()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Weld To", DisplayPriority = 1))` — Merge selected boundary edges, moving the first edge to the second
- L466 _public function_ `void FillHole()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Fill Hole", DisplayPriority = 2))` — Fill the adjacent hole for any selected boundary edges
- L470 _public function_ `void Bridge()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Bridge", DisplayPriority = 3))` — Create a new face that connects the selected edges
- L474 _public function_ `void Extrude()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Extrude", DisplayPriority = 4))` — Duplicate and move boundary vertices outwards and connect them to the original boundary to create new faces.
- L478 _public function_ `void Collapse()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Collapse", DisplayPriority = 5))` — Collapse the selected edges, deleting the attached triangles and merging its two vertices into one
- L482 _public function_ `void Flip()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Flip", DisplayPriority = 6))` — Flip the selected (non-border, non-seam) edges, replacing them with new edges in the crossing direction
- L486 _public function_ `void Split()` — `UFUNCTION(CallInEditor, Category = EdgeEdits, meta = (DisplayName = "Split", DisplayPriority = 7))` — Split the selected edges, inserting a new vertex at each edge midpoint

#### class `UEditMeshPolygonsTool`  
`class UEditMeshPolygonsTool : public USingleTargetWithSelectionTool, public IToolActivityHost, public IMeshVertexCommandChangeTarget, public IInteractiveToolNestedAcceptCancelAPI`  
_L495-767_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionTool,IToolActivityHost,IMeshVertexCommandChangeTarget,IInteractiveToolNestedAcceptCancelAPI`
- L501 _private typedef_ `using FFrame3d = UE::Geometry::FFrame3d;`
- L504 _public prototype_ `UEditMeshPolygonsTool();`
- L506 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L507 _public prototype_ `void EnableTriangleMode();`
- L510 _public prototype_ `void RebuildTopologyWithGivenExtraCorners(const TSet<int32>& Vids);` — used by undo/redo
- L512 _public prototype_ `virtual void Setup() override;`
- L513 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L515 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L516 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L517 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L519 _public function_ `virtual bool HasCancel() const override`
- L520 _public function_ `virtual bool HasAccept() const override`
- L522 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L525 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L526 _public prototype_ `virtual bool GetWorldSpaceFocusPoint(const FRay& WorldRay, FVector& PointOut) override;`
- L529 _public prototype_ `virtual void NotifyActivitySelfEnded(UInteractiveToolActivity* Activity) override;` — IToolActivityHost
- L532 _public prototype_ `virtual void ApplyChange(const FMeshVertexChange* Change, bool bRevert) override;` — IMeshVertexCommandChangeTarget
- L535 _public function_ `virtual bool SupportsNestedCancelCommand() override` — IInteractiveToolNestedAcceptCancelAPI
- L536 _public prototype_ `virtual bool CanCurrentlyNestedCancel() override;`
- L537 _public prototype_ `virtual bool ExecuteNestedCancelCommand() override;`
- L538 _public function_ `virtual bool SupportsNestedAcceptCommand() override`
- L539 _public prototype_ `virtual bool CanCurrentlyNestedAccept() override;`
- L540 _public prototype_ `virtual bool ExecuteNestedAcceptCommand() override;`
- L544 _public prototype_ `virtual void RequestAction(EEditMeshPolygonsToolActions ActionType);`
- L546 _public prototype_ `virtual void RequestSingleShotAction(EEditMeshPolygonsToolActions ActionType);`
- L548 _public prototype_ `void SetActionButtonsVisibility(bool bVisible);`
- L554 _protected member_ `bool bTriangleMode;` — If bTriangleMode = true, then we use a per-triangle FTriangleGroupTopology instead of polygroup topology. This allows low-level mesh editing with mainly the same code, at a significant cost in overhead. This is a fundamental mode switch, must be set before ::Setup() is called!
- L559 _protected member_ `bool bToolDisabled = false;` — TODO: This is a hack to allow us to disallow any actions inside the tool after Setup() is called. We use it if the user tries to run the tool on a mesh that has too many edges for us to render, to avoid hanging the editor.
- L562 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L565 _protected member_ `TObjectPtr<UPolyEditCommonProperties> CommonProps = nullptr;` — `UPROPERTY()`
- L568 _protected member_ `TObjectPtr<UEditMeshPolygonsToolActions> EditActions = nullptr;` — `UPROPERTY()`
- L570 _protected member_ `TObjectPtr<UEditMeshPolygonsToolActions_Triangles> EditActions_Triangles = nullptr;` — `UPROPERTY()`
- L573 _protected member_ `TObjectPtr<UEditMeshPolygonsToolEdgeActions> EditEdgeActions = nullptr;` — `UPROPERTY()`
- L575 _protected member_ `TObjectPtr<UEditMeshPolygonsToolEdgeActions_Triangles> EditEdgeActions_Triangles = nullptr;` — `UPROPERTY()`
- L578 _protected member_ `TObjectPtr<UEditMeshPolygonsToolUVActions> EditUVActions = nullptr;` — `UPROPERTY()`
- L581 _protected member_ `TObjectPtr<UPolyEditTopologyProperties> TopologyProperties = nullptr;` — `UPROPERTY()`
- L587 _protected member_ `TObjectPtr<UPolyEditExtrudeActivity> ExtrudeActivity = nullptr;` — `UPROPERTY()` — Activity objects that handle multi-interaction operations
- L589 _protected member_ `TObjectPtr<UPolyEditInsetOutsetActivity> InsetOutsetActivity = nullptr;` — `UPROPERTY()`
- L591 _protected member_ `TObjectPtr<UPolyEditCutFacesActivity> CutFacesActivity = nullptr;` — `UPROPERTY()`
- L593 _protected member_ `TObjectPtr<UPolyEditPlanarProjectionUVActivity> PlanarProjectionUVActivity = nullptr;` — `UPROPERTY()`
- L595 _protected member_ `TObjectPtr<UPolyEditInsertEdgeActivity> InsertEdgeActivity = nullptr;` — `UPROPERTY()`
- L597 _protected member_ `TObjectPtr<UPolyEditInsertEdgeLoopActivity> InsertEdgeLoopActivity = nullptr;` — `UPROPERTY()`
- L599 _protected member_ `TObjectPtr<UPolyEditBevelEdgeActivity> BevelEdgeActivity = nullptr;` — `UPROPERTY()`
- L601 _protected member_ `TObjectPtr<UPolyEditExtrudeEdgeActivity> ExtrudeEdgeActivity = nullptr;` — `UPROPERTY()`
- L603 _protected member_ `TMap<UInteractiveToolActivity*, FText> ActivityLabels;`
- L604 _protected member_ `TMap<UInteractiveToolActivity*, FName> ActivityIconNames;`
- L609 _protected member_ `TObjectPtr<UInteractiveToolActivity> CurrentActivity = nullptr;` — Points to one of the activities when it is active
- L611 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> CurrentMesh;`
- L612 _protected member_ `TSharedPtr<UE::Geometry::FGroupTopology> Topology;`
- L613 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> MeshSpatial;`
- L616 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext = nullptr;` — `UPROPERTY()`
- L619 _protected member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L622 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L625 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L628 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L630 _protected member_ `FText DefaultMessage;`
- L632 _protected prototype_ `void ResetUserMessage();`
- L634 _protected member_ `bool bSelectionStateDirty = false;`
- L635 _protected prototype_ `void OnSelectionModifiedEvent();`
- L637 _protected prototype_ `void OnBeginGizmoTransform(UTransformProxy* Proxy);`
- L638 _protected prototype_ `void OnEndGizmoTransform(UTransformProxy* Proxy);`
- L639 _protected prototype_ `void OnGizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L640 _protected prototype_ `void UpdateGizmoFrame(const FFrame3d* UseFrame = nullptr);`
- L641 _protected member_ `FFrame3d LastGeometryFrame;`
- L642 _protected member_ `FFrame3d LastTransformerFrame;`
- L643 _protected member_ `FFrame3d LockedTransfomerFrame;`
- L644 _protected member_ `bool bInGizmoDrag = false;`
- L646 _protected member_ `UE::Geometry::FTransformSRT3d BakedTransform;` — We bake the scale part of the Target -> World transform
- L647 _protected member_ `UE::Geometry::FTransformSRT3d WorldTransform;` — Transform from Baked to World
- L649 _protected member_ `FFrame3d InitialGizmoFrame;`
- L650 _protected member_ `FVector3d InitialGizmoScale;`
- L651 _protected member_ `bool bGizmoUpdatePending = false;`
- L652 _protected member_ `FFrame3d LastUpdateGizmoFrame;`
- L653 _protected member_ `FVector3d LastUpdateGizmoScale;`
- L654 _protected member_ `bool bLastUpdateUsedWorldFrame = false;`
- L655 _protected prototype_ `void ComputeUpdate_Gizmo();`
- L657 _protected prototype_ `UE::Geometry::FDynamicMeshAABBTree3& GetSpatial();`
- L658 _protected member_ `bool bSpatialDirty;`
- L661 _protected member_ `float UVScaleFactor = 1.0f;` — UV Scale factor to apply to texturing on any new geometry (e.g. new faces added by extrude)
- L663 _protected member_ `EEditMeshPolygonsToolActions PendingAction = EEditMeshPolygonsToolActions::NoAction;`
- L664 _protected member_ `bool bTerminateOnPendingActionComplete = false;`
- L666 _protected member_ `int32 ActivityTimestamp = 1;`
- L668 _protected prototype_ `void StartActivity(TObjectPtr<UInteractiveToolActivity> Activity);`
- L669 _protected prototype_ `void EndCurrentActivity(EToolShutdownType ShutdownType);`
- L670 _protected prototype_ `void SetActionButtonPanelsVisible(bool bVisible);`
- L673 _protected prototype_ `void EmitCurrentMeshChangeAndUpdate(const FText& TransactionLabel, TUniquePtr<UE::Geometry::FDynamicMeshChange> MeshChangeIn, const UE::Geometry::FGroupTopologySelection& OutputSelection);` — Emit an undoable change to CurrentMesh and update related structures (preview, spatial, etc)
- L678 _protected prototype_ `void EmitActivityStart(const FText& TransactionLabel);` — Emit an undoable start of an activity
- L680 _protected prototype_ `void UpdateGizmoVisibility();`
- L682 _protected prototype_ `void ApplyDelete();`
- L684 _protected prototype_ `void ApplyMerge();`
- L685 _protected prototype_ `void ApplyDeleteFaces();`
- L686 _protected prototype_ `void ApplyRecalcNormals();`
- L687 _protected prototype_ `void ApplyFlipNormals();`
- L688 _protected prototype_ `void ApplyRetriangulate();`
- L689 _protected prototype_ `void ApplyDecompose();`
- L690 _protected prototype_ `void ApplyDisconnect();`
- L691 _protected prototype_ `void ApplyDuplicate();`
- L692 _protected prototype_ `void ApplyPokeSingleFace();`
- L694 _protected prototype_ `void ApplyCollapseEdge();`
- L695 _protected prototype_ `void ApplyWeldEdges();`
- L696 _protected prototype_ `void ApplyStraightenEdges();`
- L697 _protected prototype_ `void ApplyDeleteEdges();`
- L698 _protected prototype_ `void ApplyFillHole();`
- L699 _protected prototype_ `void ApplyBridgeEdges();`
- L700 _protected prototype_ `void ApplySimplifyAlongEdges();`
- L702 _protected prototype_ `void ApplyFlipSingleEdge();`
- L704 _protected prototype_ `void ApplyCollapseSingleEdge();` — `UE_DEPRECATED(5.5, "Use ApplyCollapseEdge instead.")`
- L705 _protected prototype_ `void ApplySplitSingleEdge();`
- L707 _protected prototype_ `void SimplifyByGroups();`
- L709 _protected prototype_ `void ApplyRegenerateExtraCorners();`
- L710 _protected member_ `double ExtraCornerDotProductThreshold = -1;`
- L712 _protected member_ `FFrame3d ActiveSelectionFrameLocal;`
- L713 _protected member_ `FFrame3d ActiveSelectionFrameWorld;`
- L714 _protected member_ `TArray<int32> ActiveTriangleSelection;`
- L715 _protected member_ `UE::Geometry::FAxisAlignedBox3d ActiveSelectionBounds;`
- L722 _protected member_ `TArray<FSelectedEdge> ActiveEdgeSelection;`
- L728 _protected prototype_ `void UpdateEditPreviewMaterials(EPreviewMaterialType MaterialType);`
- L729 _protected member_ `EPreviewMaterialType CurrentPreviewMaterial;`
- L735 _protected member_ `UE::Geometry::FGroupTopologyDeformer LinearDeformer;` — data for current drag
- L736 _protected prototype_ `void UpdateDeformerFromSelection(const UE::Geometry::FGroupTopologySelection& Selection);`
- L738 _protected member_ `FMeshVertexChangeBuilder* ActiveVertexChange;`
- L739 _protected prototype_ `void UpdateDeformerChangeFromROI(bool bFinal);`
- L740 _protected prototype_ `void BeginDeformerChange();`
- L741 _protected prototype_ `void EndDeformerChange();`
- L743 _protected prototype_ `bool BeginMeshFaceEditChange();`
- L745 _protected prototype_ `bool BeginMeshEdgeEditChange();`
- L746 _protected prototype_ `bool BeginMeshBoundaryEdgeEditChange(bool bOnlySimple);`
- L747 _protected prototype_ `bool BeginMeshEdgeEditChange(TFunctionRef<bool(int32)> GroupEdgeIDFilterFunc);`
- L749 _protected prototype_ `void UpdateFromCurrentMesh(bool bRebuildTopology);`
- L750 _protected member_ `int32 ModifiedTopologyCounter = 0;`
- L751 _protected member_ `bool bWasTopologyEdited = false;`
- L759 _protected member_ `TUniqueFunction<void(UEditMeshPolygonsTool*)> PostSetupFunction;`
- L760 _protected prototype_ `void SetToSelectionModeInterface();`
- L763 _private prototype_ `void ApplyWeldEdges(double InterpolationT);`
- L764 _private prototype_ `void ApplyWeldVertices(double InterpolationT);`
- L765 _private prototype_ `void CollapseGroupEdges(TSet<int32>& GroupEdgesToCollapse, UE::Geometry::FDynamicMeshChangeTracker& ChangeTracker);`

#### struct `UEditMeshPolygonsTool::FSelectedEdge`  
`struct FSelectedEdge`  
_L717-721_
- L719 _public member_ `int32 EdgeTopoID;`
- L720 _public member_ `TArray<int32> EdgeIDs;`

#### enum `UEditMeshPolygonsTool::EPreviewMaterialType`  
`enum class EPreviewMaterialType`  
_L724-727_
- L726 _public enumerator_ `SourceMaterials`
- L726 _public enumerator_ `SourceMaterials`
- L726 _public enumerator_ `SourceMaterials`

#### class `FEditMeshPolygonsToolMeshChange`  
`class FEditMeshPolygonsToolMeshChange : public FToolCommandChange`  
_L775-790_
- inherits: `FToolCommandChange`
- desc: Wraps a FDynamicMeshChange so that it can be expired and so that other data structures in the tool can be updated. On apply/revert, the topology is rebuilt using stored extra corner vids.
- L778 _public function_ `FEditMeshPolygonsToolMeshChange(TUniquePtr<UE::Geometry::FDynamicMeshChange> MeshChangeIn) : MeshChange(MoveTemp(MeshChangeIn))`
- L782 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L783 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L784 _public prototype_ `virtual FString ToString() const override;`
- L786 _public member_ `TSet<int32> ExtraCornerVidsBefore;`
- L787 _public member_ `TSet<int32> ExtraCornerVidsAfter;`
- L789 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMeshChange> MeshChange;`

#### class `FPolyEditActivityStartChange`  
`class FPolyEditActivityStartChange : public FToolCommandChange`  
_L798-813_
- inherits: `FToolCommandChange`
- desc: FPolyEditActivityStartChange is used to cancel out of an active action on Undo. No action is taken on Redo, ie we do not re-start the Tool on Redo.
- L801 _public function_ `FPolyEditActivityStartChange(int32 ActivityTimestampIn)`
- L805 _public function_ `virtual void Apply(UObject* Object) override`
- L806 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L807 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L808 _public prototype_ `virtual FString ToString() const override;`
- L811 _protected member_ `bool bHaveDoneUndo = false;`
- L812 _protected member_ `int32 ActivityTimestamp = 0;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L23 _prototype_ `PREDECLARE_GEOMETRY(class FGroupTopology);`
- L24 _prototype_ `PREDECLARE_GEOMETRY(struct FGroupTopologySelection);`
- L25 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMeshChangeTracker);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/HoleFillTool.h` (Public)


#### class `UHoleFillToolBuilder`  
`class UHoleFillToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L32-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L37 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L38 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `USmoothHoleFillProperties`  
`class USmoothHoleFillProperties : public UInteractiveToolPropertySet`  
_L46-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L54 _public member_ `bool bConstrainToHoleInterior;` — `UPROPERTY(EditAnywhere, Category = SmoothHoleFillOptions)` — Allow smoothing and remeshing of triangles outside of the fill region
- L59 _public member_ `int RemeshingExteriorRegionWidth;` — `UPROPERTY(EditAnywhere, Category = SmoothHoleFillOptions, meta = (UIMin = "0", ClampMin = "0", EditCondition = "!bConstrainToHoleInterior", Delta = 1, LinearDeltaSensitivity = 50))` — Number of vertex rings outside of the fill region to allow remeshing
- L63 _public member_ `int SmoothingExteriorRegionWidth;` — `UPROPERTY(EditAnywhere, Category = SmoothHoleFillOptions, meta = (UIMin = "0", ClampMin = "0", Delta = 1, LinearDeltaSensitivity = 50))` — Number of vertex rings outside of the fill region to perform smoothing
- L67 _public member_ `int SmoothingInteriorRegionWidth;` — `UPROPERTY(EditAnywhere, Category = SmoothHoleFillOptions, meta = (UIMin = "0", ClampMin = "0", Delta = 1, LinearDeltaSensitivity = 50))` — Number of vertex rings away from the fill region boundary to constrain smoothing
- L71 _public member_ `float InteriorSmoothness;` — `UPROPERTY(EditAnywhere, Category = SmoothHoleFillOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "100.0"))` — Desired Smoothness. This is not a linear quantity, but larger numbers produce smoother results
- L75 _public member_ `double FillDensityScalar = 1.0;` — `UPROPERTY(EditAnywhere, Category = SmoothHoleFillOptions, meta = (UIMin = "0.001", UIMax = "10.0", ClampMin = "0.001", ClampMax = "10.0"))` — Relative triangle density of fill region
- L82 _public member_ `bool bProjectDuringRemesh = false;` — `UPROPERTY(EditAnywhere, Category = SmoothHoleFillOptions)` — Whether to project to the original mesh during post-smooth remeshing. This can be expensive on large meshes with many holes.
- L86 _public function_ `USmoothHoleFillProperties()` — Set default property values
- L99 _public function_ `UE::Geometry::FSmoothFillOptions ToSmoothFillOptions() const`

#### class `UHoleFillToolProperties`  
`class UHoleFillToolProperties : public UInteractiveToolPropertySet`  
_L114-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L120 _public member_ `EHoleFillOpFillType FillType = EHoleFillOpFillType::Minimal;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L124 _public member_ `bool bRemoveIsolatedTriangles = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Clean up triangles that have no neighbors
- L128 _public member_ `bool bQuickFillSmallHoles = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Identify and quickly fill single-triangle holes

#### enum `EHoleFillToolActions`  
`enum class EHoleFillToolActions`  
_L134-139_
- reflection: `UENUM()`
- L136 _public enumerator_ `NoAction`
- L137 _public enumerator_ `SelectAll`
- L138 _public enumerator_ `ClearSelection`

#### class `UHoleFillToolActions`  
`class UHoleFillToolActions : public UInteractiveToolPropertySet`  
_L142-168_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L146 _private member_ `TWeakObjectPtr<UHoleFillTool> ParentTool;`
- L150 _public function_ `void Initialize(UHoleFillTool* ParentToolIn)`
- L155 _public prototype_ `void PostAction(EHoleFillToolActions Action);`
- L158 _public function_ `void SelectAll()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayName = "Select All", DisplayPriority = 1))`
- L164 _public function_ `void Clear()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayName = "Clear", DisplayPriority = 1))`

#### class `UHoleFillStatisticsProperties`  
`class UHoleFillStatisticsProperties : public UInteractiveToolPropertySet`  
_L172-195_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L178 _public member_ `FString InitialHoles;` — `UPROPERTY(VisibleAnywhere, Category = HoleFillStatistics, meta = (NoResetToDefault))`
- L181 _public member_ `FString SelectedHoles;` — `UPROPERTY(VisibleAnywhere, Category = HoleFillStatistics, meta = (NoResetToDefault))`
- L184 _public member_ `FString SuccessfulFills;` — `UPROPERTY(VisibleAnywhere, Category = HoleFillStatistics, meta = (NoResetToDefault))`
- L187 _public member_ `FString FailedFills;` — `UPROPERTY(VisibleAnywhere, Category = HoleFillStatistics, meta = (NoResetToDefault))`
- L190 _public member_ `FString RemainingHoles;` — `UPROPERTY(VisibleAnywhere, Category = HoleFillStatistics, meta = (NoResetToDefault))`
- L192 _public prototype_ `void Initialize(const UHoleFillTool& HoleFillTool);`
- L194 _public prototype_ `void Update(const UHoleFillTool& HoleFillTool, const UE::Geometry::FHoleFillOp& HoleFillOp);`

#### class `UHoleFillOperatorFactory`  
`class UHoleFillOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L203-213_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L209 _public prototype_ `TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;`
- L212 _public member_ `TObjectPtr<UHoleFillTool> FillTool;` — `UPROPERTY()`

#### class `UHoleFillTool`  
`class UHoleFillTool : public USingleSelectionMeshEditingTool`  
_L221-304_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- L228 _public prototype_ `void Setup() override;` — UMeshSurfacePointTool
- L229 _public prototype_ `void OnTick(float DeltaTime) override;`
- L230 _public prototype_ `void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L231 _public function_ `bool HasCancel() const override`
- L232 _public function_ `bool HasAccept() const override`
- L233 _public prototype_ `bool CanAccept() const override;`
- L234 _public prototype_ `void OnShutdown(EToolShutdownType ShutdownType) override;`
- L236 _public prototype_ `void OnSelectionModified();`
- L238 _public prototype_ `virtual void RequestAction(EHoleFillToolActions Action);`
- L247 _protected member_ `TObjectPtr<USmoothHoleFillProperties> SmoothHoleFillProperties = nullptr;` — `UPROPERTY()`
- L250 _protected member_ `TObjectPtr<UHoleFillToolProperties> Properties = nullptr;` — `UPROPERTY()`
- L253 _protected member_ `TObjectPtr<UHoleFillToolActions> Actions = nullptr;` — `UPROPERTY()`
- L256 _protected member_ `TObjectPtr<UHoleFillStatisticsProperties> Statistics = nullptr;` — `UPROPERTY()`
- L259 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L262 _protected member_ `TObjectPtr<UBoundarySelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L265 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Input mesh. Ownership shared with Op.
- L268 _protected member_ `float MeshUVScaleFactor = 0.0f;` — UV Scale factor is cached based on the bounding box of the mesh before any fills are performed
- L271 _protected member_ `UE::Geometry::FDynamicMeshAABBTree3 MeshSpatial;` — Used for hit querying
- L273 _protected member_ `TSet<int32> NewTriangleIDs;`
- L276 _protected prototype_ `void SetupPreview();` — Create the Preview object
- L279 _protected prototype_ `void InvalidatePreviewResult();` — Invalidate background compute result (some input changed)
- L281 _protected member_ `bool bHavePendingAction = false;`
- L282 _protected member_ `EHoleFillToolActions PendingAction;`
- L283 _protected prototype_ `virtual void ApplyAction(EHoleFillToolActions ActionType);`
- L284 _protected prototype_ `void SelectAll();`
- L285 _protected prototype_ `void ClearSelection();`
- L287 _protected member_ `TUniquePtr<UE::Geometry::FMeshBoundaryLoops> BoundaryLoops;`
- L294 _protected member_ `TArray<FSelectedBoundaryLoop> ActiveBoundaryLoopSelection;`
- L295 _protected prototype_ `void UpdateActiveBoundaryLoopSelection();`
- L298 _protected prototype_ `void Render(IToolsContextRenderAPI* RenderAPI) override;` — Just call the SelectionMechanism's Render function
- L302 _protected prototype_ `void GetLoopsToFill(TArray<UE::Geometry::FEdgeLoop>& OutLoops) const;` — Populate an array of Edge Loops to be processed by an FHoleFillOp. Returns the edge loops currently selected by this tool.

#### struct `UHoleFillTool::FSelectedBoundaryLoop`  
`struct FSelectedBoundaryLoop`  
_L289-293_
- L291 _public member_ `int32 EdgeTopoID;`
- L292 _public member_ `TArray<int32> EdgeIDs;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/LatticeDeformerTool.h` (Public)


#### class `ULatticeDeformerToolBuilder`  
`class ULatticeDeformerToolBuilder : public UMultiTargetWithSelectionToolBuilder`  
_L31-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiTargetWithSelectionToolBuilder`
- L36 _public prototype_ `virtual UMultiTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L37 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L39 _public function_ `virtual bool RequiresInputSelection() const override`
- L42 _private prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `ELatticeDeformerToolAction`  
`enum class ELatticeDeformerToolAction : uint8`  
_L47-52_
- reflection: `UENUM()`
- L49 _public enumerator_ `NoAction`
- L50 _public enumerator_ `Constrain`
- L51 _public enumerator_ `ClearConstraints`

#### class `ULatticeDeformerToolProperties`  
`class ULatticeDeformerToolProperties : public UInteractiveToolPropertySet`  
_L55-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L60 _public member_ `TWeakObjectPtr<ULatticeDeformerTool> ParentTool;`
- L61 _public function_ `void Initialize(ULatticeDeformerTool* ParentToolIn)`
- L62 _public prototype_ `void PostAction(ELatticeDeformerToolAction Action);`
- L66 _public member_ `int XAxisResolution = 5;` — `UPROPERTY(EditAnywhere, Category = Resolution, meta = (UIMin = "2", ClampMin = "2", UIMax = "25", ClampMax = "40", EditCondition = "bCanChangeResolution", HideEditConditionToggle))` — Number of lattice vertices along the X axis
- L70 _public member_ `int YAxisResolution = 5;` — `UPROPERTY(EditAnywhere, Category = Resolution, meta = (UIMin = "2", ClampMin = "2", UIMax = "25", ClampMax = "40", EditCondition = "bCanChangeResolution", HideEditConditionToggle))` — Number of lattice vertices along the Y axis
- L74 _public member_ `int ZAxisResolution = 5;` — `UPROPERTY(EditAnywhere, Category = Resolution, meta = (UIMin = "2", ClampMin = "2", UIMax = "25", ClampMax = "40", EditCondition = "bCanChangeResolution", HideEditConditionToggle))` — Number of lattice vertices along the Z axis
- L78 _public member_ `float Padding = 0.01f;` — `UPROPERTY(EditAnywhere, Category = Resolution, meta = (UIMin = "0.01", ClampMin = "0.01", UIMax = "2", ClampMax = "5", EditCondition = "bCanChangeResolution", HideEditConditionToggle))` — Relative distance the lattice extends from the mesh
- L82 _public member_ `ELatticeInterpolationType InterpolationType = ELatticeInterpolationType::Linear;` — `UPROPERTY(EditAnywhere, Category = Interpolation)` — Whether to use linear or cubic interpolation to get new mesh vertex positions from the lattice
- L86 _public member_ `bool bDeformNormals = false;` — `UPROPERTY(EditAnywhere, Category = Interpolation)` — Whether to use approximate new vertex normals using the deformer
- L90 _public member_ `bool bCanChangeResolution = true;` — `UPROPERTY(meta = (TransientToolProperty))` — Not user visible - used to disallow changing the lattice resolution after deformation
- L94 _public member_ `EToolContextCoordinateSystem GizmoCoordinateSystem = EToolContextCoordinateSystem::Local;` — `UPROPERTY(EditAnywhere, Category = Gizmo)` — Whether the gizmo's axes remain aligned with world axes or rotate as the gizmo is transformed
- L98 _public member_ `bool bSetPivotMode = false;` — `UPROPERTY(EditAnywhere, Category = Gizmo)` — If Set Pivot Mode is active, the gizmo can be repositioned without moving the selected lattice points
- L102 _public member_ `bool bSoftDeformation = false;` — `UPROPERTY(EditAnywhere, Category = Deformation)` — Whether to use soft deformation of the lattice
- L106 _public function_ `void Constrain()` — `UFUNCTION(CallInEditor, Category = Deformation, meta = (DisplayName = "Constrain"))` — Constrain selected lattice points
- L113 _public function_ `void ClearConstraints()` — `UFUNCTION(CallInEditor, Category = Deformation, meta = (DisplayName = "Clear Constraints"))` — Clear all constrained lattice points

#### class `ULatticeDeformerOperatorFactory`  
`class ULatticeDeformerOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L122-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L128 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L131 _public member_ `TObjectPtr<ULatticeDeformerTool> LatticeDeformerTool;` — `UPROPERTY()`

#### class `ULatticeDeformerTool`  
`class ULatticeDeformerTool : public UMultiTargetWithSelectionTool, public IInteractiveToolManageGeometrySelectionAPI, public IModelingToolExternalDynamicMeshUpdateAPI`  
_L137-231_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiTargetWithSelectionTool,IInteractiveToolManageGeometrySelectionAPI,IModelingToolExternalDynamicMeshUpdateAPI`
- desc: Deform a mesh using a regular hexahedral lattice
- L143 _public prototype_ `virtual ~ULatticeDeformerTool() = default;`
- L145 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L147 _public function_ `virtual bool HasCancel() const override`
- L148 _public function_ `virtual bool HasAccept() const override`
- L149 _public prototype_ `virtual bool CanAccept() const override;`
- L151 _public prototype_ `virtual void Setup() override;`
- L152 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L154 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L155 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L157 _public prototype_ `UE::Geometry::FVector3i GetLatticeResolution() const;`
- L158 _public prototype_ `void SetLatticeStorage(const TScriptInterface<ILatticeStateStorage>& InLatticeStorage);`
- L161 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L169 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Input mesh
- L171 _protected member_ `TSharedPtr<UE::Geometry::FDynamicSubmesh3, ESPMode::ThreadSafe> Submesh = nullptr;`
- L173 _protected member_ `FTransform3d WorldTransform;`
- L175 _protected member_ `TSharedPtr<UE::Geometry::FFFDLattice, ESPMode::ThreadSafe> Lattice;`
- L178 _protected member_ `TObjectPtr<ULatticeControlPointsMechanic> ControlPointsMechanic = nullptr;` — `UPROPERTY()`
- L181 _protected member_ `TObjectPtr<ULatticeDeformerToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L184 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L187 _protected member_ `TObjectPtr<UMeshSculptLayerProperties> SculptLayerProperties;` — `UPROPERTY()`
- L190 _protected member_ `TScriptInterface<ILatticeStateStorage> LatticeStorage;` — `UPROPERTY()`
- L193 _protected member_ `bool bLatticeDeformed = false;` — `UPROPERTY()`
- L195 _protected member_ `bool bShouldRebuild = false;`
- L197 _protected member_ `bool bHasSelection = false;`
- L200 _protected prototype_ `virtual bool AllowToolMeshUpdates() const override;` — IInteractiveToolExternalDynamicMeshUpdateAPI methods
- L201 _protected prototype_ `virtual void UpdateToolMeshes(TFunctionRef<TUniquePtr<FMeshRegionChangeBase>(UE::Geometry::FDynamicMesh3&, int32 MeshIdx)> UpdateMesh) override;`
- L202 _protected prototype_ `virtual void ProcessToolMeshes(TFunctionRef<void(const UE::Geometry::FDynamicMesh3&, int32 MeshIdx)> ProcessMesh) const override;`
- L203 _protected prototype_ `virtual int32 NumToolMeshes() const override;`
- L206 _protected prototype_ `void InitializeLattice(TArray<FVector3d>& OutLatticePoints, TArray<UE::Geometry::FVector2i>& OutLatticeEdges);` — Create and store an FFFDLattice. Pass out the lattice's positions and edges.
- L208 _protected prototype_ `void StartPreview();`
- L210 _protected member_ `TUniquePtr<UE::Solvers::IConstrainedMeshSolver> DeformationSolver;`
- L211 _protected member_ `TPimplPtr<UE::Geometry::FDynamicGraph3d> LatticeGraph;`
- L213 _protected member_ `TMap<int32, FVector3d> ConstrainedLatticePoints;`
- L214 _protected prototype_ `void ConstrainSelectedPoints();`
- L215 _protected prototype_ `void ClearConstrainedPoints();`
- L216 _protected prototype_ `void UpdateMechanicColorOverrides();`
- L217 _protected prototype_ `void ResetConstrainedPoints();`
- L219 _protected prototype_ `void RebuildDeformer();`
- L220 _protected prototype_ `void SoftDeformLattice();`
- L222 _protected member_ `int32 CurrentChangeStamp = 0;`
- L224 _protected member_ `ELatticeDeformerToolAction PendingAction = ELatticeDeformerToolAction::NoAction;`
- L225 _protected prototype_ `void RequestAction(ELatticeDeformerToolAction Action);`
- L226 _protected prototype_ `void ApplyAction(ELatticeDeformerToolAction Action);`

#### class `FLatticeDeformerToolConstrainedPointsChange`  
`class FLatticeDeformerToolConstrainedPointsChange : public FToolCommandChange`  
_L235-262_
- inherits: `FToolCommandChange`
- desc: Set of constrained points change
- L239 _public function_ `FLatticeDeformerToolConstrainedPointsChange(const TMap<int, FVector3d>& PrevConstrainedLatticePointsIn, const TMap<int, FVector3d>& NewConstrainedLatticePointsIn, int32 ChangeStampIn) : PrevConstrainedLatticePoints(PrevConstrainedLatticePointsIn), NewConstrainedLatticePoints(NewConstrainedLatticePointsIn), ChangeStamp(ChangeStampIn)`
- L247 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L248 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L250 _public function_ `virtual bool HasExpired(UObject* Object) const override`
- L255 _public prototype_ `virtual FString ToString() const override;`
- L259 _protected member_ `TMap<int, FVector3d> PrevConstrainedLatticePoints;`
- L260 _protected member_ `TMap<int, FVector3d> NewConstrainedLatticePoints;`
- L261 _protected member_ `int32 ChangeStamp;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/MeshAttributePaintTool.h` (Public)


#### class `FFloatAttributeColorMapper`  
`class FFloatAttributeColorMapper`  
_L23-47_
- desc: Maps float values to linear color ramp.
- L26 _public prototype_ `virtual ~FFloatAttributeColorMapper() = default;`
- L28 _public member_ `FLinearColor LowColor = FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);`
- L29 _public member_ `FLinearColor HighColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);`
- L31 _public function_ `virtual FLinearColor ToColor(float Value)`
- L42 _public function_ `template<typename VectorType> VectorType ToColor(float Value)`

#### class `IMeshVertexAttributeAdapter`  
`class IMeshVertexAttributeAdapter`  
_L53-62_
- desc: Abstract interface to a single-channel indexed floating-point attribute
- L56 _public prototype_ `virtual ~IMeshVertexAttributeAdapter() = default;`
- L58 _public prototype_ `virtual int ElementNum() const = 0;`
- L59 _public prototype_ `virtual float GetValue(int32 Index) const = 0;`
- L60 _public prototype_ `virtual void SetValue(int32 Index, float Value) = 0;`
- L61 _public prototype_ `virtual UE::Geometry::FInterval1f GetValueRange() = 0;`

#### class `IMeshVertexAttributeSource`  
`class IMeshVertexAttributeSource`  
_L69-78_
- desc: Abstract interface to a set of single-channel indexed floating-point attributes
- L72 _public prototype_ `virtual ~IMeshVertexAttributeSource() = default;`
- L74 _public prototype_ `virtual TArray<FName> GetAttributeList() = 0;`
- L75 _public prototype_ `virtual TUniquePtr<IMeshVertexAttributeAdapter> GetAttribute(FName AttributeName) = 0;`
- L77 _public prototype_ `virtual int32 GetAttributeElementNum() = 0;` — @return number of indices in each attribute

#### class `UMeshAttributePaintToolBuilder`  
`class UMeshAttributePaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L90-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: Tool Builder for Attribute Paint Tool Note: a new experimental version of this tool is UMeshAttributePaintToolV2
- L95 _public member_ `TUniqueFunction<TUniquePtr<FFloatAttributeColorMapper>()> ColorMapFactory;` — Optional color map customization
- L97 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L98 _public prototype_ `virtual void InitializeNewTool(UMeshSurfacePointTool* NewTool, const FToolBuilderState& SceneState) const override;`
- L99 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L102 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EMeshAttributePaintMaterialMode`  
`enum class EMeshAttributePaintMaterialMode`  
_L108-113_
- reflection: `UENUM()`
- L110 _public enumerator_ `Shaded`
- L111 _public enumerator_ `ColorOnly`
- L112 _public enumerator_ `ExistingMaterial`

#### enum `EBrushActionMode`  
`enum class EBrushActionMode`  
_L117-127_
- reflection: `UENUM()`
- L120 _public enumerator_ `Paint` — Clicking adds to the weight, Ctrl subtracts, Shift smooths
- L122 _public enumerator_ `FloodFill` — Clicking sets the weight for the entire mesh component. Ctrl unsets the weight for the entire component, Shift is unused.
- L124 _public enumerator_ `Erase` — Clicking subtracts from the weight, Ctrl adds, Shift smooths
- L126 _public enumerator_ `Smooth` — Clicking smooths values, Ctrl and Shift are unused

#### class `UMeshAttributePaintBrushOperationProperties`  
`class UMeshAttributePaintBrushOperationProperties : public UInteractiveToolPropertySet`  
_L134-157_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Selected-Attribute settings Attribute Paint Tool
- L144 _public member_ `bool bIsolateGeometrySelection = false;` — `UPROPERTY(EditAnywhere, Category = Attribute, meta = (EditCondition = "bToolHasSelection", HideEditConditionToggle))` — If the tool was started with a mesh element selection, this setting hides everything except that selection, to make painting it easier. Requires that a mesh element selection exist on tool start.
- L148 _public member_ `bool bToolHasSelection = false;` — `UPROPERTY()`
- L152 _public member_ `EBrushActionMode BrushAction = EBrushActionMode::Paint;` — `UPROPERTY(EditAnywhere, Category = Attribute, meta=(DisplayName="Action"))` — The mode of action for the brush.
- L156 _public member_ `float BrushValue = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Attribute, meta=(UIMin=0.0, UIMax=1.0, DisplayName="Value", ModelingQuickEdit, ModelingQuickSettings=150))` — The target value that the brush will accumulate towards.

#### class `UMeshAttributePaintToolVisualizationProperties`  
`class UMeshAttributePaintToolVisualizationProperties : public UInteractiveToolPropertySet`  
_L161-171_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L167 _public member_ `EMeshAttributePaintMaterialMode MaterialMode = EMeshAttributePaintMaterialMode::Shaded;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta=(DisplayName="Preview", ModelingQuickSettings=1000))`
- L170 _public member_ `bool bFlatShading = true;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditCondition ="MaterialMode==EMeshAttributePaintMaterialMode::Shaded"))`

#### class `UMeshAttributePaintToolProperties`  
`class UMeshAttributePaintToolProperties : public UInteractiveToolPropertySet`  
_L175-206_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L181 _public member_ `FString Attribute;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Selected Attribute", GetOptions = GetAttributeNames))`
- L184 _public function_ `const TArray<FString>& GetAttributeNames()` — `UFUNCTION()`
- L186 _public member_ `TArray<FString> Attributes;`
- L193 _public prototype_ `void Initialize(const TArray<FName>& AttributeNames, bool bInitialize = false);` — Initialize the internal array of attribute names @param bInitialize if set, selected Attribute will be reset to the first attribute or empty if there are none.
- L200 _public prototype_ `bool ValidateSelectedAttribute(bool bUpdateIfInvalid);` — Verify that the attribute selection is valid @param bUpdateIfInvalid if selection is not valid, use attribute at index 0 or empty if there are no attributes @return true if selection is in the Attributes array
- L205 _public prototype_ `int32 GetSelectedAttributeIndex();` — @return selected attribute index, or -1 if invalid selection

#### enum `EMeshAttributePaintToolActions`  
`enum class EMeshAttributePaintToolActions`  
_L213-216_
- reflection: `UENUM()`
- L215 _public enumerator_ `NoAction`

#### class `UMeshAttributePaintEditActions`  
`class UMeshAttributePaintEditActions : public UInteractiveToolPropertySet`  
_L221-231_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L226 _public member_ `TWeakObjectPtr<UMeshAttributePaintTool> ParentTool;`
- L228 _public function_ `void Initialize(UMeshAttributePaintTool* ParentToolIn)`
- L230 _public prototype_ `void PostAction(EMeshAttributePaintToolActions Action);`

#### class `FMeshAttributePaintChange`  
`class FMeshAttributePaintChange : public TCustomIndexedValuesChange<float, int32>`  
_L238-245_
- inherits: `TCustomIndexedValuesChange<float,int32>`
- desc: FCommandChange for color map changes
- L241 _public function_ `virtual FString ToString() const override`

#### class `UMeshAttributePaintTool`  
`class UMeshAttributePaintTool : public UDynamicMeshBrushTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L254-406_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDynamicMeshBrushTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: UMeshAttributePaintTool paints single-channel float attributes on a MeshDescription or DynamicMesh Note: a new experimental version of this tool is UMeshAttributePaintToolV2
- L259 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L260 _public prototype_ `void SetGeometrySelection(const UE::Geometry::FGeometrySelection& SelectionIn);`
- L262 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L264 _public prototype_ `virtual void Setup() override;`
- L265 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L267 _public function_ `virtual bool HasCancel() const override`
- L268 _public function_ `virtual bool HasAccept() const override`
- L271 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;` — UBaseBrushTool overrides
- L272 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L273 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L274 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L277 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;` — UMeshSurfacePointTool
- L279 _public prototype_ `virtual void RequestAction(EMeshAttributePaintToolActions ActionType);`
- L281 _public prototype_ `virtual void SetColorMap(TUniquePtr<FFloatAttributeColorMapper> ColorMap);`
- L284 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L289 _public function_ `UE::Geometry::TDynamicVerticesOctree3<FDynamicMesh3>& GetVerticesOctree()`
- L292 _protected prototype_ `virtual void ApplyStamp(const FBrushStampData& Stamp);`
- L303 _protected prototype_ `virtual void ApplyStamp_Paint(const FBrushStampData& Stamp, FStampActionData& ActionData);`
- L304 _protected prototype_ `virtual void ApplyStamp_FloodFill(const FBrushStampData& Stamp, FStampActionData& ActionData);`
- L306 _protected prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L310 _protected prototype_ `virtual FString GetPropertyCacheIdentifier() const;` — Should be overriden by subclasses so that settings are not shared across this tool and subclasses.
- L315 _protected member_ `TObjectPtr<UMeshAttributePaintBrushOperationProperties> BrushActionProps;` — `UPROPERTY()`
- L318 _protected member_ `TObjectPtr<UMeshAttributePaintToolProperties> AttribProps;` — `UPROPERTY()`
- L321 _protected member_ `TObjectPtr<UMeshAttributePaintToolVisualizationProperties> ViewProperties;` — `UPROPERTY()`
- L323 _protected member_ `TValueWatcher<int32> SelectedAttributeWatcher;`
- L329 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> ActiveOverrideMaterial;` — `UPROPERTY()`
- L332 _protected member_ `UWorld* TargetWorld;`
- L334 _protected member_ `bool bInRemoveStroke = false;`
- L335 _protected member_ `bool bInSmoothStroke = false;`
- L336 _protected member_ `FBrushStampData StartStamp;`
- L337 _protected member_ `FBrushStampData LastStamp;`
- L338 _protected member_ `bool bStampPending;`
- L341 _protected member_ `TUniquePtr<FMeshDescription> EditedMesh;` — Note: This is used if the target supports mesh description read/write; otherwise EditedDynamicMesh is used
- L343 _protected member_ `TUniquePtr<FDynamicMesh3> EditedDynamicMesh;` — This is used if the target doesn't support mesh description read/write; otherwise EditedMesh is used
- L345 _protected member_ `bool bPreferMeshDescription = true;` — Can be set by subclasses to determine which to use when both mesh description and dynamic mesh are options.
- L347 _protected prototype_ `double CalculateBrushFalloff(double Distance);`
- L348 _protected member_ `UE::Geometry::TDynamicVerticesOctree3<FDynamicMesh3> VerticesOctree;`
- L349 _protected member_ `TArray<int> PreviewBrushROI;`
- L350 _protected prototype_ `void CalculateVertexROI(const FBrushStampData& Stamp, TArray<int>& VertexROI);`
- L352 _protected member_ `TUniquePtr<FFloatAttributeColorMapper> ColorMapper;`
- L353 _protected member_ `TUniquePtr<IMeshVertexAttributeSource> AttributeSource;`
- L362 _protected member_ `TArray<FAttributeData> Attributes;`
- L363 _protected member_ `int32 AttributeBufferCount;`
- L364 _protected member_ `int32 CurrentAttributeIndex;`
- L365 _protected member_ `UE::Geometry::FInterval1f CurrentValueRange;`
- L369 _protected member_ `bool bHavePendingAction = false;`
- L370 _protected member_ `EMeshAttributePaintToolActions PendingAction;`
- L371 _protected prototype_ `virtual void ApplyAction(EMeshAttributePaintToolActions ActionType);`
- L373 _protected member_ `bool bVisibleAttributeValid = false;`
- L374 _protected member_ `int32 PendingNewSelectedIndex = -1;`
- L376 _protected prototype_ `virtual void InitializeAttributes();`
- L377 _protected prototype_ `void StoreCurrentAttribute();`
- L378 _protected prototype_ `void UpdateVisibleAttribute();`
- L379 _protected prototype_ `void UpdateSelectedAttribute(int32 NewSelectedIndex);`
- L381 _protected member_ `TUniquePtr<TIndexedValuesChangeBuilder<float, FMeshAttributePaintChange>> ActiveChangeBuilder;`
- L382 _protected prototype_ `void BeginChange();`
- L383 _protected prototype_ `TUniquePtr<FMeshAttributePaintChange> EndChange();`
- L384 _protected prototype_ `virtual void ExternalUpdateValues(int32 AttribIndex, const TArray<int32>& VertexIndices, const TArray<float>& NewValues);`
- L394 _private member_ `TOptional<UE::Geometry::FGeometrySelection> GeometrySelection;`
- L395 _private member_ `TSet<int32> SelectionTids;`
- L396 _private member_ `TSet<int32> SelectionVids;`
- L397 _private prototype_ `bool IsFilteringTrianglesBySelection() const;`
- L398 _private prototype_ `bool IsFilteringTrianglesByFrontFacing() const;`
- L400 _private prototype_ `void ApplyStamp_Paint(const FBrushStampData& Stamp, FStampActionData& ActionData, const FBrushActionData& BrushData);`
- L402 _private prototype_ `void UpdateMaterialMode(EMeshAttributePaintMaterialMode MaterialMode);`
- L403 _private prototype_ `void UpdateFlatShadingSetting(bool bNewValue);`
- L405 _private prototype_ `bool IsTriangleBackFacing(int32 TriangleID, const FDynamicMesh3* QueryMesh) const;`

#### struct `UMeshAttributePaintTool::FStampActionData`  
`struct FStampActionData`  
_L295-300_
- L297 _public member_ `TArray<int32> ROIVertices;`
- L298 _public member_ `TArray<float> ROIBefore;`
- L299 _public member_ `TArray<float> ROIAfter;`

#### struct `UMeshAttributePaintTool::FAttributeData`  
`struct FAttributeData`  
_L355-361_
- L357 _public member_ `FName Name;`
- L358 _public member_ `TUniquePtr<IMeshVertexAttributeAdapter> Attribute;`
- L359 _public member_ `TArray<float> CurrentValues;`
- L360 _public member_ `TArray<float> InitialValues;`

#### struct `UMeshAttributePaintTool::FBrushActionData`  
`struct FBrushActionData`  
_L387-392_
- L389 _public member_ `float BrushValue = 1.0f;`
- L390 _public member_ `bool bSmooth = false;`
- L391 _public member_ `bool bErase = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/MeshGroupPaintTool.h` (Public)


#### class `UMeshGroupPaintToolBuilder`  
`class UMeshGroupPaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L59-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: Tool Builder
- L64 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L65 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EMeshGroupPaintInteractionType`  
`enum class EMeshGroupPaintInteractionType : uint8`  
_L73-81_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L75 _public enumerator_ `Brush`
- L76 _public enumerator_ `Fill`
- L77 _public enumerator_ `GroupFill`
- L78 _public enumerator_ `PolyLasso`
- L80 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EMeshGroupPaintBrushType`  
`enum class EMeshGroupPaintBrushType : uint8`  
_L91-100_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L94 _public enumerator_ `Paint UMETA(DisplayName = "Paint")` — Paint active group
- L97 _public enumerator_ `Erase UMETA(DisplayName = "Erase")` — Erase active group
- L99 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EMeshGroupPaintBrushAreaType`  
`enum class EMeshGroupPaintBrushAreaType : uint8`  
_L105-109_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Area Types
- L107 _public enumerator_ `Connected`
- L108 _public enumerator_ `Volumetric`

#### enum `EMeshGroupPaintVisibilityType`  
`enum class EMeshGroupPaintVisibilityType : uint8`  
_L113-118_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L115 _public enumerator_ `None`
- L116 _public enumerator_ `FrontFacing`
- L117 _public enumerator_ `Unoccluded`

#### class `UGroupPaintBrushFilterProperties`  
`class UGroupPaintBrushFilterProperties : public UInteractiveToolPropertySet`  
_L124-211_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L132 _public member_ `EMeshGroupPaintBrushType PrimaryBrushType = EMeshGroupPaintBrushType::Paint;` — `UPROPERTY(EditAnywhere, Category = Brush2, meta = (DisplayName = "Brush Type"))` — `UPROPERTY()` — Primary Brush Mode
- L135 _public member_ `EMeshGroupPaintInteractionType SubToolType = EMeshGroupPaintInteractionType::Brush;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Action"))`
- L140 _public member_ `float BrushSize = 0.25f;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Brush Size", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType != EMeshGroupPaintInteractionType::PolyLasso"))` — Relative size of brush
- L145 _public member_ `EMeshGroupPaintBrushAreaType BrushAreaMode = EMeshGroupPaintBrushAreaType::Connected;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Brush Area Mode", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType != EMeshGroupPaintInteractionType::PolyLasso"))` — When Volumetric, all faces inside the brush sphere are selected, otherwise only connected faces are selected
- L150 _public member_ `bool bHitBackFaces = true;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Hit Back Faces", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType != EMeshGroupPaintInteractionType::PolyLasso"))` — Allow the Brush to hit the back-side of the mesh
- L155 _public member_ `int32 SetGroup = 1;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (UIMin = 0, ClampMin = 0, Delta = 1, LinearDeltaSensitivity = 50, HideEditConditionToggle, EditConditionHides, EditCondition = "bPaintingLabels == false"))` — The group index that will be assigned to triangles
- L159 _public member_ `FName SetLabel = NAME_None;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = bUseLabel))` — The group label that will be assigned to triangles
- L163 _public member_ `bool bOnlySetUngrouped = false;` — `UPROPERTY(EditAnywhere, Category = ActionType)` — If true, only triangles with no group assigned will be painted
- L168 _public member_ `int32 EraseGroup = 0;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (UIMin = 0, ClampMin = 0, Delta = 1, LinearDeltaSensitivity = 50, HideEditConditionToggle, EditConditionHides, EditCondition = "bPaintingLabels == false"))` — Group index to set as Erased value
- L172 _public member_ `FName EraseLabel = NAME_None;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = bUseLabel))` — Group label to set as Erased value
- L176 _public member_ `bool bOnlyEraseCurrent = false;` — `UPROPERTY(EditAnywhere, Category = ActionType)` — When enabled, only the current group configured in the Paint brush is erased
- L180 _public member_ `float AngleThreshold = 180.0f;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (UIMin = "0.0", UIMax = "180.0", EditCondition = "SubToolType != EMeshGroupPaintInteractionType::PolyLasso && BrushAreaMode == EMeshGroupPaintBrushAreaType::Connected"))` — The Region affected by the current operation will be bounded by edge angles larger than this threshold
- L184 _public member_ `bool bUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (EditCondition = "SubToolType != EMeshGroupPaintInteractionType::PolyLasso && BrushAreaMode == EMeshGroupPaintBrushAreaType::Connected"))` — The Region affected by the current operation will be bounded by UV borders/seams
- L188 _public member_ `bool bNormalSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (EditCondition = "SubToolType != EMeshGroupPaintInteractionType::PolyLasso && BrushAreaMode == EMeshGroupPaintBrushAreaType::Connected"))` — The Region affected by the current operation will be bounded by Hard Normal edges/seams
- L192 _public member_ `EMeshGroupPaintVisibilityType VisibilityFilter = EMeshGroupPaintVisibilityType::None;` — `UPROPERTY(EditAnywhere, Category = Filters)` — Control which triangles can be affected by the current operation based on visibility. Applied after all other filters.
- L197 _public member_ `int MinTriVertCount = 1;` — `UPROPERTY(EditAnywhere, Category = Filters, AdvancedDisplay, meta = (UIMin = 1, UIMax = 3, EditCondition = "SubToolType == EMeshGroupPaintInteractionType::PolyLasso"))` — Number of vertices in a triangle the Lasso must hit to be counted as "inside"
- L202 _public member_ `bool bShowHitGroup = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Display the Group ID of the last triangle under the cursor
- L206 _public member_ `bool bShowAllGroups = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Display the Group ID for all visible groups in the mesh
- L210 _public member_ `bool bPaintingLabels = false;` — `UPROPERTY()` — whether the user is painting labels

#### enum `EMeshGroupPaintToolActions`  
`enum class EMeshGroupPaintToolActions`  
_L218-231_
- reflection: `UENUM()`
- L220 _public enumerator_ `NoAction`
- L222 _public enumerator_ `ClearFrozen`
- L223 _public enumerator_ `FreezeCurrent`
- L224 _public enumerator_ `FreezeOthers`
- L226 _public enumerator_ `GrowCurrent`
- L227 _public enumerator_ `ShrinkCurrent`
- L228 _public enumerator_ `ClearCurrent`
- L229 _public enumerator_ `FloodFillCurrent`
- L230 _public enumerator_ `ClearAll`

#### class `UMeshGroupPaintToolActionPropertySet`  
`class UMeshGroupPaintToolActionPropertySet : public UInteractiveToolPropertySet`  
_L235-245_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L240 _public member_ `TWeakObjectPtr<UMeshGroupPaintTool> ParentTool;`
- L242 _public function_ `void Initialize(UMeshGroupPaintTool* ParentToolIn)`
- L244 _public prototype_ `void PostAction(EMeshGroupPaintToolActions Action);`

#### class `UMeshGroupPaintToolFreezeActions`  
`class UMeshGroupPaintToolFreezeActions : public UMeshGroupPaintToolActionPropertySet`  
_L250-305_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshGroupPaintToolActionPropertySet`
- L256 _public function_ `void UnfreezeAll()` — `UFUNCTION(CallInEditor, Category = Freezing, meta = (DisplayPriority = 1))`
- L262 _public function_ `void FreezeCurrent()` — `UFUNCTION(CallInEditor, Category = Freezing, meta = (DisplayPriority = 2))`
- L268 _public function_ `void FreezeOthers()` — `UFUNCTION(CallInEditor, Category = Freezing, meta = (DisplayPriority = 3))`
- L274 _public function_ `void ClearAll()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 10))`
- L280 _public function_ `void ClearCurrent()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 11))`
- L286 _public function_ `void FloodFillCurrent()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 12))`
- L293 _public function_ `void GrowCurrent()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 20))`
- L299 _public function_ `void ShrinkCurrent()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 21))`

#### class `UMeshGroupPaintTool`  
`class UMeshGroupPaintTool : public UMeshSculptToolBase`  
_L314-525_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptToolBase`
- desc: Mesh Element Paint Tool Class
- L319 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L321 _public prototype_ `virtual void Setup() override;`
- L322 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L324 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L325 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L327 _public function_ `virtual bool HasCancel() const override`
- L328 _public function_ `virtual bool HasAccept() const override`
- L329 _public function_ `virtual bool CanAccept() const override`
- L331 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L333 _public prototype_ `bool IsInBrushSubMode() const;`
- L335 _public prototype_ `virtual void CommitResult(UBaseDynamicMeshComponent* Component, bool bModifiedTopology) override;`
- L341 _public member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties;` — `UPROPERTY()`
- L345 _public member_ `TObjectPtr<UGroupPaintBrushFilterProperties> FilterProperties;` — `UPROPERTY()` — Filters on paint brush
- L351 _private member_ `TObjectPtr<UGroupPaintBrushOpProps> PaintBrushOpProperties;` — `UPROPERTY()` — This will be of type UGroupPaintBrushOpProps, we keep a ref so we can change active group ID on pick
- L354 _private member_ `TObjectPtr<UGroupEraseBrushOpProps> EraseBrushOpProperties;` — `UPROPERTY()`
- L357 _public prototype_ `void AllocateNewGroupAndSetAsCurrentAction();`
- L358 _public prototype_ `void GrowCurrentGroupAction();`
- L359 _public prototype_ `void ShrinkCurrentGroupAction();`
- L360 _public prototype_ `void ClearCurrentGroupAction();`
- L361 _public prototype_ `void FloodFillCurrentGroupAction();`
- L362 _public prototype_ `void ClearAllGroupsAction();`
- L364 _public prototype_ `void SetTrianglesToGroupID(const TSet<int32>& Triangles, int32 ToGroupID, bool bIsErase);`
- L366 _public prototype_ `bool HaveVisibilityFilter() const;`
- L367 _public prototype_ `void ApplyVisibilityFilter(const TArray<int32>& Triangles, TArray<int32>& VisibleTriangles);`
- L368 _public prototype_ `void ApplyVisibilityFilter(TSet<int32>& Triangles, TArray<int32>& ROIBuffer, TArray<int32>& OutputBuffer);`
- L371 _public prototype_ `virtual void IncreaseBrushRadiusAction();` — we override these so we can update the separate BrushSize property added for this tool
- L372 _public prototype_ `virtual void DecreaseBrushRadiusAction();`
- L373 _public prototype_ `virtual void IncreaseBrushRadiusSmallStepAction();`
- L374 _public prototype_ `virtual void DecreaseBrushRadiusSmallStepAction();`
- L378 _protected function_ `virtual UBaseDynamicMeshComponent* GetSculptMeshComponent()` — UMeshSculptToolBase API
- L379 _protected function_ `virtual FDynamicMesh3* GetBaseMesh()`
- L380 _protected function_ `virtual const FDynamicMesh3* GetBaseMesh() const`
- L382 _protected prototype_ `virtual int32 FindHitSculptMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L383 _protected prototype_ `virtual int32 FindHitTargetMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L385 _protected prototype_ `virtual void OnBeginStroke(const FRay& WorldRay) override;`
- L386 _protected prototype_ `virtual void OnEndStroke() override;`
- L387 _protected prototype_ `virtual void OnCancelStroke() override;`
- L389 _protected function_ `virtual bool SharesBrushPropertiesChanges() const override`
- L391 _protected prototype_ `virtual TUniquePtr<FMeshSculptBrushOp>& GetActiveBrushOp();`
- L401 _public prototype_ `virtual void RequestAction(EMeshGroupPaintToolActions ActionType);`
- L404 _public member_ `TObjectPtr<UMeshGroupPaintToolFreezeActions> FreezeActions;` — `UPROPERTY()`
- L407 _protected member_ `bool bHavePendingAction = false;`
- L408 _protected member_ `EMeshGroupPaintToolActions PendingAction;`
- L409 _protected prototype_ `virtual void ApplyAction(EMeshGroupPaintToolActions ActionType);`
- L418 _public member_ `TObjectPtr<UPolyLassoMarqueeMechanic> PolyLassoMechanic;` — `UPROPERTY()`
- L421 _protected prototype_ `void OnPolyLassoFinished(const FCameraPolyLasso& Lasso, bool bCanceled);`
- L431 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L434 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent;` — `UPROPERTY()`
- L437 _protected member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay;` — `UPROPERTY()`
- L440 _protected prototype_ `void OnDynamicMeshComponentChanged();` — realtime visualization
- L441 _protected member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L443 _protected prototype_ `int32 GetGroup(const int32 TriangleID) const;`
- L444 _protected prototype_ `void SetGroup(const int32 TriangleID, const int32 GroupID, FDynamicMesh3& Mesh) const;`
- L446 _protected prototype_ `int32 GetGroupToSet() const;`
- L447 _protected prototype_ `int32 GetGroupToErase() const;`
- L449 _protected member_ `TUniquePtr<UE::Geometry::FPolygroupSet> ActiveGroupSet;`
- L450 _protected member_ `TSharedPtr<UE::Geometry::FTriangleLabelAdapter> LabelAdapter;`
- L452 _protected function_ `bool IsPaintingLabel() const`
- L457 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L458 _protected prototype_ `void UpdateActiveGroupLayer();`
- L460 _protected prototype_ `void UpdateSubToolType(EMeshGroupPaintInteractionType NewType);`
- L462 _protected prototype_ `void UpdateBrushType(EMeshGroupPaintBrushType BrushType);`
- L464 _protected member_ `TSet<int32> AccumulatedTriangleROI;`
- L465 _protected member_ `bool bUndoUpdatePending = false;`
- L466 _protected member_ `TArray<int> NormalsBuffer;`
- L467 _protected prototype_ `void WaitForPendingUndoRedoUpdate();`
- L469 _protected member_ `TArray<int> TempROIBuffer;`
- L470 _protected member_ `TArray<int> VertexROI;`
- L471 _protected member_ `TArray<bool> VisibilityFilterBuffer;`
- L472 _protected member_ `TSet<int> VertexSetBuffer;`
- L473 _protected member_ `TSet<int> TriangleROI;`
- L474 _protected prototype_ `void UpdateROI(const FSculptBrushStamp& CurrentStamp);`
- L476 _protected member_ `EMeshGroupPaintBrushType PendingStampType = EMeshGroupPaintBrushType::Paint;`
- L478 _protected prototype_ `bool UpdateStampPosition(const FRay& WorldRay);`
- L479 _protected prototype_ `bool ApplyStamp();`
- L481 _protected member_ `UE::Geometry::FDynamicMeshOctree3 Octree;`
- L483 _protected prototype_ `bool UpdateBrushPosition(const FRay& WorldRay);`
- L485 _protected function_ `bool GetInEraseStroke()`
- L492 _protected member_ `bool bPendingPickGroup = false;`
- L493 _protected member_ `bool bPendingToggleFreezeGroup = false;`
- L496 _protected member_ `TArray<int32> ROITriangleBuffer;`
- L497 _protected member_ `TArray<int32> ROIGroupBuffer;`
- L498 _protected prototype_ `bool SyncMeshWithGroupBuffer(FDynamicMesh3* Mesh);`
- L500 _protected member_ `TUniquePtr<FDynamicMeshGroupEditBuilder> ActiveGroupEditBuilder;`
- L501 _protected member_ `TUniquePtr<FDynamicMeshTriangleLabelEditBuilder> ActiveLabelEditBuilder;`
- L502 _protected prototype_ `void BeginChange();`
- L503 _protected prototype_ `void EndChange();`
- L504 _protected prototype_ `void SaveTriangleEdits() const;`
- L506 _protected member_ `TArray<int32> FrozenGroups;`
- L507 _protected prototype_ `void ToggleFrozenGroup(int32 GroupID);`
- L508 _protected prototype_ `void FreezeOtherGroups(int32 GroupID);`
- L509 _protected prototype_ `void ClearAllFrozenGroups();`
- L510 _protected prototype_ `void EmitFrozenGroupsChange(const TArray<int32>& FromGroups, const TArray<int32>& ToGroups, const FText& ChangeText);`
- L512 _protected prototype_ `FColor GetColorForGroup(int32 GroupID);`
- L514 _protected member_ `TArray<FVector3d> TriNormals;`
- L515 _protected member_ `TArray<int32> UVSeamEdges;`
- L516 _protected member_ `TArray<int32> NormalSeamEdges;`
- L517 _protected prototype_ `void PrecomputeFilterData();`
- L520 _protected member_ `bool bDrawGroupsDataValid = false;`
- L521 _protected member_ `UE::Geometry::FGroupVisualizationCache GroupVisualizationCache;`
- L524 _protected function_ `virtual bool ShowWorkPlane() const override`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace Geometry` (scope `UE`)
- L38 _delegate_ `DECLARE_STATS_GROUP(TEXT("GroupPaintTool"), STATGROUP_GroupPaintTool, STAT`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/MeshModelingTools.h` (Public)


#### class `FMeshModelingToolsModule`  
`class FMeshModelingToolsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/MeshSpaceDeformerTool.h` (Public)


#### class `UMeshSpaceDeformerToolBuilder`  
`class UMeshSpaceDeformerToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L38-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- desc: ToolBuilder
- L43 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `ENonlinearOperationType`  
`enum class ENonlinearOperationType : int8`  
_L48-64_
- reflection: `UENUM()`
- desc: ENonlinearOperation determines which type of nonlinear deformation will be applied
- L54 _public enumerator_ `Bend` — Will bend the mesh in the direction of the gizmo Y axis along the Z axis. A line along the Z axis from the lower bound to the upper bound would not change length as it bends.
- L60 _public enumerator_ `Flare UMETA(DisplayName = "Flare/Squish")` — Depening on 'Flare Percent", will either flare or squish the mesh along the Gizmo Z axis, from lower bound to upper bound.
- L63 _public enumerator_ `Twist` — Twists the mesh along the gizmo Z axis, from lower bound to upper bound.

#### enum `EFlareProfileType`  
`enum class EFlareProfileType : int8`  
_L67-77_
- reflection: `UENUM()`
- L70 _public enumerator_ `SinMode` — Displaced by sin(pi x) with x in 0 to 1
- L73 _public enumerator_ `SinSquaredMode` — Displaced by sin(pi x)*sin(pi x) with x in 0 to 1. This provides a smooth normal transition.
- L76 _public enumerator_ `TriangleMode` — Displaced by piecewise-linear trianglular mode

#### class `UMeshSpaceDeformerToolProperties`  
`class UMeshSpaceDeformerToolProperties : public UInteractiveToolPropertySet`  
_L80-156_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L86 _public member_ `ENonlinearOperationType SelectedOperationType = ENonlinearOperationType::Bend;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Operation Type"))`
- L90 _public member_ `float UpperBoundsInterval = 100.0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Upper Bound", UIMin = "0.0", ClampMin = "0.0"))` — The upper bound to the region of space which the operation will affect. Measured along the gizmo Z axis from the gizmo center.
- L94 _public member_ `float LowerBoundsInterval = -100.0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Lower Bound", UIMax = "0", ClampMax = "0"))` — The lower bound to the region of space which the operation will affect. Measured along the gizmo Z axis from the gizmo center.
- L103 _public member_ `float BendDegrees = 90;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "-360", UIMax = "360", ClampMin = "-3600", ClampMax = "3600", EditCondition = "SelectedOperationType == ENonlinearOperationType::Bend", EditConditionHides))` — A line along the Z axis of the gizmo from lower bound to upper bound will be bent into a perfect arc of this many degrees in the direction of the Y axis without changing length.
- L108 _public member_ `float TwistDegrees = 180;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "-360", UIMax = "360", ClampMin = "-3600", ClampMax = "3600", EditCondition = "SelectedOperationType == ENonlinearOperationType::Twist", EditConditionHides))` — Degrees of twist from the lower bound to the upper bound along the gizmo Z axis.
- L114 _public member_ `EFlareProfileType FlareProfileType = EFlareProfileType::SinMode;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "SelectedOperationType == ENonlinearOperationType::Flare", EditConditionHides))` — Determines the profile used as a displacement
- L123 _public member_ `float FlarePercentY = 100;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "-100", UIMax = "200", ClampMin = "-1000", ClampMax = "2000", EditCondition = "SelectedOperationType == ENonlinearOperationType::Flare", EditConditionHides))` — Determines how much to flare perpendicular to the Z axis. When set to 100%, points are moved double the distance away from the gizmo Z axis at the most extreme flare point. 0% does not flare at all, whereas -100% pinches all the way to the gizmo Z axis at the most extreme flare point.
- L129 _public member_ `bool bLockXAndYFlaring = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "SelectedOperationType == ENonlinearOperationType::Flare", EditConditionHides))` — If true, flaring is applied along the gizmo X and Y axis the same amount.
- L137 _public member_ `float FlarePercentX = 100;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "-100", UIMax = "200", ClampMin = "-1000", ClampMax = "2000", EditCondition = "SelectedOperationType == ENonlinearOperationType::Flare && !bLockXAndYFlaring", EditConditionHides))` — Determines how much to flare perpendicular to the Z axis in the X direction if the flaring is not locked to be the same in the X and Y directions.
- L145 _public member_ `bool bLockBottom = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "SelectedOperationType == ENonlinearOperationType::Bend || SelectedOperationType == ENonlinearOperationType::Twist", EditConditionHides))` — If true, the "bottom" of the mesh relative to the gizmo Z axis will stay in place while the rest bends or twists. If false, the bend or twist will happen around the gizmo location.
- L148 _public member_ `bool bShowOriginalMesh = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L151 _public member_ `bool bDrawVisualization = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "SelectedOperationType == ENonlinearOperationType::Bend", EditConditionHides))`
- L155 _public member_ `bool bAlignToNormalOnCtrlClick = false;` — `UPROPERTY(EditAnywhere, Category = Gizmo)` — When true, Ctrl+click not only moves the gizmo to the clicked location, but also aligns the Z axis with the normal at that point.

#### enum `EMeshSpaceDeformerToolAction`  
`enum class EMeshSpaceDeformerToolAction`  
_L159-164_
- reflection: `UENUM()`
- L161 _public enumerator_ `NoAction`
- L163 _public enumerator_ `ShiftToCenter`

#### class `UMeshSpaceDeformerToolActionPropertySet`  
`class UMeshSpaceDeformerToolActionPropertySet : public UInteractiveToolPropertySet`  
_L167-180_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L172 _public member_ `TWeakObjectPtr<UMeshSpaceDeformerTool> ParentTool;`
- L174 _public function_ `void Initialize(UMeshSpaceDeformerTool* ParentToolIn)`
- L175 _public prototype_ `void PostAction(EMeshSpaceDeformerToolAction Action);`
- L179 _public function_ `void ShiftToCenter()` — `UFUNCTION(CallInEditor, Category = Gizmo)` — Move the gizmo to the center of the object without changing the orientation.

#### class `USpaceDeformerOperatorFactory`  
`class USpaceDeformerOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L184-194_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L190 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L193 _public member_ `TObjectPtr<UMeshSpaceDeformerTool> SpaceDeformerTool;` — `UPROPERTY()` — back pointer

#### class `UMeshSpaceDeformerTool`  
`class UMeshSpaceDeformerTool : public USingleSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L201-303_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Applies non-linear deformations to a mesh
- L205 _public prototype_ `UMeshSpaceDeformerTool();`
- L207 _public prototype_ `virtual void Setup() override;`
- L208 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L210 _public prototype_ `void RequestAction(EMeshSpaceDeformerToolAction ActionType);`
- L212 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L213 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L215 _public function_ `virtual bool HasCancel() const override`
- L216 _public function_ `virtual bool HasAccept() const override`
- L217 _public prototype_ `virtual bool CanAccept() const override;`
- L219 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L222 _public prototype_ `void UpdateOpParameters(UE::Geometry::FMeshSpaceDeformerOp& MeshSpaceDeformerOp) const;` — sync the parameters owned by the MeshSpaceDeformerOp
- L225 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L233 _protected member_ `TObjectPtr<UMeshSpaceDeformerToolProperties> Settings;` — `UPROPERTY()`
- L236 _protected member_ `TObjectPtr<UMeshSpaceDeformerToolActionPropertySet> ToolActions;` — `UPROPERTY()`
- L239 _protected member_ `TObjectPtr<UGizmoTransformChangeStateTarget> StateTarget = nullptr;` — `UPROPERTY()`
- L242 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic;` — `UPROPERTY()`
- L247 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L251 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalDynamicMesh;`
- L254 _protected member_ `TObjectPtr<UPreviewMesh> OriginalMeshPreview;` — `UPROPERTY()`
- L257 _protected member_ `TObjectPtr<UIntervalGizmo> IntervalGizmo;` — `UPROPERTY()`
- L260 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo;` — `UPROPERTY()`
- L263 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy;` — `UPROPERTY()`
- L268 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> UpIntervalSource;` — `UPROPERTY()`
- L271 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> DownIntervalSource;` — `UPROPERTY()`
- L274 _protected member_ `TObjectPtr<UGizmoLocalFloatParameterSource> ForwardIntervalSource;` — `UPROPERTY()`
- L277 _protected member_ `EMeshSpaceDeformerToolAction PendingAction;` — Button click support
- L278 _protected member_ `FVector3d MeshCenter;`
- L280 _protected member_ `UE::Geometry::FFrame3d GizmoFrame;`
- L284 _protected member_ `double ModifierGizmoLength;` — The length of the third interval gizmo (which sets the intensity of the deformation) when the modifier is set to some reasonable maximum.
- L286 _protected member_ `TPimplPtr<FSelectClickedAction> SetPointInWorldConnector;`
- L288 _protected member_ `TArray<FVector3d> VisualizationPoints;`
- L289 _protected member_ `FToolDataVisualizer VisualizationRenderer;`
- L291 _protected prototype_ `void TransformProxyChanged(UTransformProxy* Proxy, FTransform Transform);`
- L292 _protected prototype_ `void SetGizmoFrameFromWorldPos(const FVector& Position, const FVector& Normal = FVector(), bool bAlignNormal = false);`
- L294 _protected prototype_ `double GetModifierGizmoValue() const;`
- L295 _protected prototype_ `void ApplyModifierGizmoValue(double Value);`
- L298 _protected prototype_ `void ApplyAction(EMeshSpaceDeformerToolAction Action);` — Apply clicked action
- L300 _protected prototype_ `void UpdatePreview();`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/MeshVertexPaintTool.h` (Public)


#### class `UMeshVertexPaintToolBuilder`  
`class UMeshVertexPaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L45-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: Tool Builder
- L50 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L51 _public prototype_ `virtual void InitializeNewTool(UMeshSurfacePointTool* NewTool, const FToolBuilderState& SceneState) const override;`
- L52 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L55 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EMeshVertexPaintInteractionType`  
`enum class EMeshVertexPaintInteractionType : uint8`  
_L63-77_
- reflection: `UENUM()`
- desc: Mesh Vertex Paint Primary Interactions
- L66 _public enumerator_ `Brush UMETA(DisplayName = "Paint Vertices")` — Paint Vertices of hit triangles with a smooth falloff
- L68 _public enumerator_ `TriFill UMETA(DisplayName = "Paint Triangles")` — Fill any painted triangles, by setting all 3 vertices to the same color
- L70 _public enumerator_ `Fill UMETA(DisplayName = "Flood Fill Connected")` — Fill any triangles connected to the brushed triangles
- L72 _public enumerator_ `GroupFill UMETA(DisplayName = "Flood Fill Groups")` — Fill any polygroups connected to the brushed triangles
- L74 _public enumerator_ `PolyLasso` — Paint any triangles inside polygonal or freehand Lassos drawn in the viewport
- L76 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EMeshVertexPaintColorChannel`  
`enum class EMeshVertexPaintColorChannel : uint8`  
_L81-87_
- reflection: `UENUM()`
- L83 _public enumerator_ `Red = 0`
- L84 _public enumerator_ `Green = 1`
- L85 _public enumerator_ `Blue = 2`
- L86 _public enumerator_ `Alpha = 3`

#### enum `EMeshVertexPaintColorBlendMode`  
`enum class EMeshVertexPaintColorBlendMode : uint8`  
_L92-100_
- reflection: `UENUM()`
- desc: currently in-sync with EVertexColorPaintBrushOpBlendMode
- L95 _public enumerator_ `Lerp = 0` — Interpolate between Paint color and existing Color
- L97 _public enumerator_ `Mix = 1` — Alpha-Blend the Paint accumulated during each stroke with the existing Colors
- L99 _public enumerator_ `Multiply = 2` — Multiply the Paint color with the existing Color

#### enum `EMeshVertexPaintBrushType`  
`enum class EMeshVertexPaintBrushType : uint8`  
_L107-122_
- reflection: `UENUM()`
- desc: Mesh Vertex Painting Brush Types
- L110 _public enumerator_ `Paint UMETA(DisplayName = "Paint")` — Paint the Primary Color
- L113 _public enumerator_ `Erase UMETA(DisplayName = "Erase")` — Paint the Erase/Secondary Color
- L116 _public enumerator_ `Soften UMETA(DisplayName = "Soften")` — Average any seam colors at a vertex
- L119 _public enumerator_ `Smooth UMETA(DisplayName = "Smooth")` — Smooth the colors
- L121 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EMeshVertexPaintSecondaryActionType`  
`enum class EMeshVertexPaintSecondaryActionType : uint8`  
_L126-134_
- reflection: `UENUM()`
- desc: Secondary/Erase Vertex Color Painting Types
- L129 _public enumerator_ `Erase` — Paint the Erase/Secondary Color
- L131 _public enumerator_ `Soften` — Blend any split color values at painted vertices
- L133 _public enumerator_ `Smooth` — Blend vertex colors with nearby vertex colors (ie blur)

#### enum `EMeshVertexPaintBrushAreaType`  
`enum class EMeshVertexPaintBrushAreaType : uint8`  
_L140-146_
- reflection: `UENUM()`
- desc: Brush Area Types
- L143 _public enumerator_ `Connected` — Brush affects any triangles inside a sphere around the cursor
- L145 _public enumerator_ `Volumetric` — Brush affects any triangles geometrically connected to the triangle under the cursor

#### enum `EMeshVertexPaintVisibilityType`  
`enum class EMeshVertexPaintVisibilityType : uint8`  
_L150-157_
- reflection: `UENUM()`
- desc: Visibility Types
- L152 _public enumerator_ `None`
- L154 _public enumerator_ `FrontFacing` — Only paint vertices that are front-facing relative to the current camera direction
- L156 _public enumerator_ `Unoccluded` — Only paint triangles that are visible. Only considers active mesh, visibility test is based on triangle centers

#### enum `EMeshVertexPaintMaterialMode`  
`enum class EMeshVertexPaintMaterialMode : uint8`  
_L161-169_
- reflection: `UENUM()`
- desc: Visualization Materials
- L164 _public enumerator_ `LitVertexColor` — Display Vertex Colors using a Lit flat-shaded material
- L166 _public enumerator_ `UnlitVertexColor` — Display Vertex Colors using an Unlit smooth-shaded material
- L168 _public enumerator_ `OriginalMaterial` — Display Materials assigned to target Mesh

#### class `UVertexPaintBasicProperties`  
`class UVertexPaintBasicProperties : public UInteractiveToolPropertySet`  
_L174-227_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L182 _public member_ `EMeshVertexPaintBrushType PrimaryBrushType = EMeshVertexPaintBrushType::Paint;` — `UPROPERTY(EditAnywhere, Category = Brush2, meta = (DisplayName = "Brush Type"))` — `UPROPERTY()` — Primary Brush Mode
- L186 _public member_ `EMeshVertexPaintInteractionType SubToolType = EMeshVertexPaintInteractionType::Brush;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "Action"))` — Painting Operation to apply when left-clicking and dragging
- L190 _public member_ `double Strength = 1.0;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (UIMin = 0, UIMax = 1))` — The strength of the brush effect when stamped on the mesh
- L194 _public member_ `FLinearColor PaintColor = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = ())` — The Color that will be assigned to painted triangle vertices
- L198 _public member_ `bool bIsPaintPressureEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Should pressure sensitivity affect Paint brush strength?
- L202 _public member_ `EMeshVertexPaintColorBlendMode BlendMode = EMeshVertexPaintColorBlendMode::Lerp;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Controls how painted Colors will be combined with the existing Colors
- L206 _public member_ `EMeshVertexPaintSecondaryActionType SecondaryActionType = EMeshVertexPaintSecondaryActionType::Erase;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "Secondary Brush"))` — The Brush Operation that will be applied when holding the Shift key when in Painting
- L210 _public member_ `FLinearColor EraseColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditConditionHides, EditCondition = "SecondaryActionType != EMeshVertexPaintSecondaryActionType::Smooth"))` — Color to set when using Erase brush
- L214 _public member_ `bool bIsErasePressureEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditConditionHides, EditCondition = "SecondaryActionType != EMeshVertexPaintSecondaryActionType::Smooth"))` — Should pressure sensitivity affect Erase brush strength?
- L218 _public member_ `float SmoothStrength = 0.25;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (UIMin = 0, UIMax = 1, EditConditionHides, EditCondition = "SecondaryActionType == EMeshVertexPaintSecondaryActionType::Smooth"))` — Strength of Smooth Brush
- L222 _public member_ `FModelingToolsColorChannelFilter ChannelFilter;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Controls which Color Channels will be affected by Operations. Only enabled Channels are rendered.
- L226 _public member_ `bool bHardEdges = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "Hard Edges"))` — Create Split Colors / Hard Color Edges at the borders of the painted area. Use Soften operations to un-split.

#### class `UVertexPaintBrushFilterProperties`  
`class UVertexPaintBrushFilterProperties : public UInteractiveToolPropertySet`  
_L233-289_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L241 _public member_ `EMeshVertexPaintBrushAreaType BrushAreaMode = EMeshVertexPaintBrushAreaType::Connected;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (DisplayName = "Brush Area Mode", EditConditionHides, EditCondition = "CurrentSubToolType != EMeshVertexPaintInteractionType::PolyLasso"))` — Area Mode specifies the shape of the brush and which triangles will be included relative to the cursor
- L245 _public member_ `float AngleThreshold = 180.0f;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (UIMin = "0.0", UIMax = "180.0", EditCondition = "CurrentSubToolType != EMeshVertexPaintInteractionType::PolyLasso && BrushAreaMode == EMeshVertexPaintBrushAreaType::Connected"))` — The Region affected by the current operation will be bounded by edge angles larger than this threshold
- L249 _public member_ `bool bUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (DisplayName = "UV Seams", EditCondition = "CurrentSubToolType != EMeshVertexPaintInteractionType::PolyLasso && BrushAreaMode == EMeshVertexPaintBrushAreaType::Connected"))` — The Region affected by the current operation will be bounded by UV borders/seams
- L253 _public member_ `bool bNormalSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (DisplayName = "Hard Normals", EditCondition = "CurrentSubToolType != EMeshVertexPaintInteractionType::PolyLasso && BrushAreaMode == EMeshVertexPaintBrushAreaType::Connected"))` — The Region affected by the current operation will be bounded by Hard Normal edges/seams
- L257 _public member_ `EMeshVertexPaintVisibilityType VisibilityFilter = EMeshVertexPaintVisibilityType::None;` — `UPROPERTY(EditAnywhere, Category = Filters)` — Control which triangles can be affected by the current operation based on visibility. Applied after all other filters.
- L265 _public member_ `bool bIsolateGeometrySelection = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (EditCondition = "bToolHasSelection", HideEditConditionToggle))` — If the tool was started with a mesh element selection, this setting hides everything except that selection, to make painting it easier. Requires that a mesh element selection exist on tool start.
- L269 _public member_ `bool bToolHasSelection = false;` — `UPROPERTY()`
- L274 _public member_ `int MinTriVertCount = 1;` — `UPROPERTY(EditAnywhere, Category = Filters, AdvancedDisplay, meta = (UIMin = 1, UIMax = 3, EditCondition = "CurrentSubToolType == EMeshVertexPaintInteractionType::PolyLasso"))` — `UPROPERTY()` — Number of vertices in a triangle the Lasso must hit to be counted as "inside"
- L278 _public member_ `EMeshVertexPaintMaterialMode MaterialMode = EMeshVertexPaintMaterialMode::UnlitVertexColor;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Specify which Materials should be used to render the Mesh
- L282 _public member_ `bool bShowHitColor = false;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta=(DisplayName="Show Color Under Cursor"))` — Display the Color under the cursor
- L288 _public member_ `EMeshVertexPaintInteractionType CurrentSubToolType;` — `UPROPERTY(meta=(TransientToolProperty))`

#### enum `EMeshVertexPaintToolActions`  
`enum class EMeshVertexPaintToolActions`  
_L294-308_
- reflection: `UENUM()`
- L296 _public enumerator_ `NoAction`
- L299 _public enumerator_ `PaintAll` — Fill all Vertex Colors with the current Paint Color
- L301 _public enumerator_ `EraseAll` — Fill all Vertex Colors with the current Erase Color
- L303 _public enumerator_ `FillBlack` — Fill all Vertex Colors with Black (0,0,0,1)
- L305 _public enumerator_ `FillWhite` — Fill all Vertex Colors with White (1,1,1,1)
- L307 _public enumerator_ `ApplyCurrentUtility`

#### class `UMeshVertexPaintToolActionPropertySet`  
`class UMeshVertexPaintToolActionPropertySet : public UInteractiveToolPropertySet`  
_L312-322_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L317 _public member_ `TWeakObjectPtr<UMeshVertexPaintTool> ParentTool;`
- L319 _public function_ `void Initialize(UMeshVertexPaintTool* ParentToolIn)`
- L321 _public prototype_ `void PostAction(EMeshVertexPaintToolActions Action);`

#### class `UMeshVertexPaintToolQuickActions`  
`class UMeshVertexPaintToolQuickActions : public UMeshVertexPaintToolActionPropertySet`  
_L327-368_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexPaintToolActionPropertySet`
- L337 _public function_ `void PaintAll()` — `UFUNCTION(CallInEditor, Category = QuickActions, meta = (DisplayPriority = 12))` — Fill all Vertex Colors with the current Paint color. Current Channel Filter still applies.
- L346 _public function_ `void EraseAll()` — `UFUNCTION(CallInEditor, Category = QuickActions, meta = (DisplayPriority = 13))` — Fill all Vertex Colors with the current Erase color. Current Channel Filter still applies.
- L355 _public function_ `void FillBlack()` — `UFUNCTION(CallInEditor, Category = QuickActions, meta = (DisplayPriority = 14))` — Fill all Vertex Colors with the Color (0,0,0,1). Current Channel Filter still applies.
- L364 _public function_ `void FillWhite()` — `UFUNCTION(CallInEditor, Category = QuickActions, meta = (DisplayPriority = 14))` — Fill all Vertex Colors with the Color (1,1,1,1). Current Channel Filter still applies.

#### enum `EMeshVertexPaintToolUtilityOperations`  
`enum class EMeshVertexPaintToolUtilityOperations`  
_L373-407_
- reflection: `UENUM()`
- L378 _public enumerator_ `BlendAllSeams` — Average the current color values at each vertex with split colors, so that there are no split vertices or seams in the color values
- L382 _public enumerator_ `FillChannels` — Set selected channels to a fixed value
- L386 _public enumerator_ `InvertChannels` — Invert channel values
- L390 _public enumerator_ `CopyChannelToChannel` — Copy the color value from a source channel to all the selected target channels
- L394 _public enumerator_ `SwapChannels` — Swap values between two Channels
- L398 _public enumerator_ `CopyFromWeightMap` — Copy values from WeightMap into Vertex Color channels
- L402 _public enumerator_ `CopyToOtherLODs` — Copy current values to any other LODs defined on the target
- L406 _public enumerator_ `CopyToSingleLOD` — Copy current values to a specific LOD defined on the target

#### class `UMeshVertexPaintToolUtilityActions`  
`class UMeshVertexPaintToolUtilityActions : public UMeshVertexPaintToolActionPropertySet`  
_L413-472_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexPaintToolActionPropertySet`
- L422 _public member_ `EMeshVertexPaintToolUtilityOperations Operation = EMeshVertexPaintToolUtilityOperations::BlendAllSeams;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (NoResetToDefault, DisplayPriority = 1))` — Operation to apply to current Vertex Colors
- L425 _public member_ `EMeshVertexPaintColorChannel SourceChannel = EMeshVertexPaintColorChannel::Red;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (EditConditionHides, EditCondition = "Operation == EMeshVertexPaintToolUtilityOperations::CopyChannelToChannel || Operation == EMeshVertexPaintToolUtilityOperations::SwapChannels"))`
- L428 _public member_ `float SourceValue = 0.0f;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (UIMin = 0, UIMax = 1, EditConditionHides, EditCondition = "Operation == EMeshVertexPaintToolUtilityOperations::FillChannels"))`
- L432 _public member_ `FName WeightMap;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (TransientToolProperty, NoResetToDefault, GetOptions = GetWeightMapsFunc, EditConditionHides, EditCondition = "Operation == EMeshVertexPaintToolUtilityOperations::CopyFromWeightMap"))` — Target Vertex Weight Map
- L436 _public function_ `TArray<FString> GetWeightMapsFunc()` — `UFUNCTION()` — this function is called provide set of available weight maps
- L440 _public member_ `TArray<FString> WeightMapsList;` — `UPROPERTY(meta = (TransientToolProperty))` — internal list used to implement above
- L443 _public member_ `FModelingToolsColorChannelFilter TargetChannels;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (EditConditionHides, EditCondition = "Operation == EMeshVertexPaintToolUtilityOperations::FillChannels || Operation == EMeshVertexPaintToolUtilityOperations::InvertChannels || Operation == EMeshVertexPaintToolUtilityOperations::CopyChannelToChannel || Operation == EMeshVertexPaintToolUtilityOperations::CopyFromWeightMap"))`
- L446 _public member_ `EMeshVertexPaintColorChannel TargetChannel = EMeshVertexPaintColorChannel::Green;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (EditConditionHides, EditCondition = "Operation == EMeshVertexPaintToolUtilityOperations::SwapChannels"))`
- L450 _public member_ `bool bCopyToHiRes = false;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (EditConditionHides, EditCondition = "Operation == EMeshVertexPaintToolUtilityOperations::CopyToOtherLODs"))` — Copy colors to HiRes Source Mesh, if it exists
- L454 _public member_ `FString CopyToLODName;` — `UPROPERTY(EditAnywhere, Category = UtilityOperations, meta = (TransientToolProperty, DisplayName = "Copy To LOD", NoResetToDefault, GetOptions = GetLODNamesFunc, EditConditionHides, EditCondition = "Operation == EMeshVertexPaintToolUtilityOperations::CopyToSingleLOD"))` — Target LOD to copy Colors to
- L457 _public function_ `const TArray<FString>& GetLODNamesFunc() const` — `UFUNCTION()`
- L460 _public member_ `TArray<FString> LODNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L467 _public function_ `void ApplySelectedOperation()` — `UFUNCTION(CallInEditor, Category = UtilityOperations, meta = (DisplayPriority = 10))` — Apply the Operation currently selected below

#### class `FMeshVertexColorPaintChange`  
`class FMeshVertexColorPaintChange : public TCustomIndexedValuesChange<FVector4f, int32>`  
_L479-486_
- inherits: `TCustomIndexedValuesChange<FVector4f,int32>`
- desc: FCommandChange for Vertex Color changes
- L482 _public function_ `virtual FString ToString() const override`

#### class `UMeshVertexPaintTool`  
`class UMeshVertexPaintTool : public UMeshSculptToolBase, public IInteractiveToolManageGeometrySelectionAPI`  
_L495-743_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptToolBase,IInteractiveToolManageGeometrySelectionAPI`
- desc: Mesh Vertex Color Painting TOol
- L500 _public prototype_ `void SetGeometrySelection(const UE::Geometry::FGeometrySelection& SelectionIn);`
- L502 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L504 _public prototype_ `virtual void Setup() override;`
- L505 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L507 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L508 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L509 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L511 _public function_ `virtual bool HasCancel() const override`
- L512 _public function_ `virtual bool HasAccept() const override`
- L513 _public function_ `virtual bool CanAccept() const override`
- L515 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L517 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L519 _public prototype_ `bool IsInBrushSubMode() const;`
- L521 _public prototype_ `virtual void CommitResult(UBaseDynamicMeshComponent* Component, bool bModifiedTopology) override;`
- L524 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L532 _public member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties;` — `UPROPERTY()`
- L535 _public member_ `TObjectPtr<UVertexPaintBasicProperties> BasicProperties;` — `UPROPERTY()`
- L539 _public member_ `TObjectPtr<UVertexPaintBrushFilterProperties> FilterProperties;` — `UPROPERTY()` — Filters on paint brush
- L542 _public member_ `TObjectPtr<UMeshSymmetryProperties> SymmetryProperties;` — `UPROPERTY()`
- L547 _private member_ `TObjectPtr<UVertexColorPaintBrushOpProps> PaintBrushOpProperties;` — `UPROPERTY()` — This will be of type UVertexPaintBrushOpProps, we keep a ref so we can change active color on pick
- L551 _private member_ `TObjectPtr<UVertexColorPaintBrushOpProps> EraseBrushOpProperties;` — `UPROPERTY()` — This will be of type UVertexPaintBrushOpProps, we keep a ref so we can change active color on pick
- L554 _public prototype_ `void FloodFillColorAction(FLinearColor Color);`
- L558 _public prototype_ `void SetTrianglesToVertexColor(const TArray<int32>& Triangles, const FLinearColor& ToColor);`
- L559 _public prototype_ `void SetTrianglesToVertexColor(const TSet<int32>& Triangles, const FLinearColor& ToColor);`
- L561 _public prototype_ `bool HaveVisibilityFilter() const;`
- L562 _public prototype_ `void ApplyVisibilityFilter(const TArray<int32>& Triangles, TArray<int32>& VisibleTriangles);`
- L563 _public prototype_ `void ApplyVisibilityFilter(TSet<int32>& Triangles, TArray<int32>& ROIBuffer, TArray<int32>& OutputBuffer);`
- L567 _protected function_ `virtual UBaseDynamicMeshComponent* GetSculptMeshComponent()` — UMeshSculptToolBase API
- L568 _protected function_ `virtual FDynamicMesh3* GetBaseMesh()`
- L569 _protected function_ `virtual const FDynamicMesh3* GetBaseMesh() const`
- L571 _protected prototype_ `virtual int32 FindHitSculptMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L572 _protected prototype_ `virtual int32 FindHitTargetMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L574 _protected prototype_ `virtual void OnBeginStroke(const FRay& WorldRay) override;`
- L575 _protected prototype_ `virtual void OnEndStroke() override;`
- L576 _protected prototype_ `virtual void OnCancelStroke() override;`
- L578 _protected prototype_ `virtual TUniquePtr<FMeshSculptBrushOp>& GetActiveBrushOp();`
- L581 _protected prototype_ `virtual FString GetPropertyCacheIdentifier() const;`
- L588 _public prototype_ `virtual void RequestAction(EMeshVertexPaintToolActions ActionType);`
- L591 _public member_ `TObjectPtr<UMeshVertexPaintToolQuickActions> QuickActions;` — `UPROPERTY()`
- L596 _public member_ `TObjectPtr<UMeshVertexPaintToolUtilityActions> UtilityActions;` — `UPROPERTY()`
- L598 _public prototype_ `void ApplyCurrentUtilityAction();`
- L599 _public prototype_ `void BlendAllSeams();`
- L600 _public prototype_ `void FillChannels();`
- L601 _public prototype_ `void InvertChannels();`
- L602 _public prototype_ `void CopyChannelToChannel();`
- L603 _public prototype_ `void SwapChannels();`
- L604 _public prototype_ `void CopyFromWeightMap();`
- L605 _public prototype_ `void CopyToOtherLODs();`
- L606 _public prototype_ `void CopyToSpecificLOD();`
- L609 _protected member_ `bool bHavePendingAction = false;`
- L610 _protected member_ `EMeshVertexPaintToolActions PendingAction;`
- L611 _protected prototype_ `virtual void ApplyAction(EMeshVertexPaintToolActions ActionType);`
- L620 _public member_ `TObjectPtr<UPolyLassoMarqueeMechanic> PolyLassoMechanic;` — `UPROPERTY()`
- L623 _protected prototype_ `void OnPolyLassoFinished(const FCameraPolyLasso& Lasso, bool bCanceled);`
- L633 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L636 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent;` — `UPROPERTY()`
- L639 _protected member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay;` — `UPROPERTY()`
- L642 _protected prototype_ `void OnDynamicMeshComponentChanged();` — realtime visualization
- L643 _protected member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L645 _protected member_ `EMeshLODIdentifier SourceLOD;`
- L646 _protected member_ `TArray<EMeshLODIdentifier> AvailableLODs;`
- L647 _protected member_ `bool bTargetSupportsLODs = false;`
- L649 _protected member_ `UE::Geometry::FDynamicMeshColorOverlay* ActiveColorOverlay = nullptr;`
- L650 _protected function_ `UE::Geometry::FDynamicMeshColorOverlay* GetActiveColorOverlay() const`
- L652 _protected member_ `TUniquePtr<UE::Geometry::FPolygroupSet> ActiveGroupSet;`
- L653 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L654 _protected prototype_ `void UpdateActiveGroupLayer();`
- L656 _protected prototype_ `void UpdateSubToolType(EMeshVertexPaintInteractionType NewType);`
- L657 _protected prototype_ `void UpdateBrushType(EMeshVertexPaintBrushType BrushType);`
- L658 _protected prototype_ `void UpdateSecondaryBrushType(EMeshVertexPaintSecondaryActionType NewType);`
- L659 _protected prototype_ `void UpdateVertexPaintMaterialMode();`
- L661 _protected member_ `TSet<int32> AccumulatedTriangleROI;`
- L662 _protected member_ `bool bUndoUpdatePending = false;`
- L663 _protected member_ `TArray<int> NormalsBuffer;`
- L664 _protected prototype_ `void WaitForPendingUndoRedoUpdate();`
- L666 _protected member_ `TArray<int> TempROIBuffer;`
- L667 _protected member_ `TArray<int> VertexROI;`
- L668 _protected member_ `TArray<bool> VisibilityFilterBuffer;`
- L669 _protected member_ `TSet<int> TempVertexSet;`
- L670 _protected member_ `TSet<int> TriangleROI;`
- L671 _protected prototype_ `void UpdateROI(const FSculptBrushStamp& CurrentStamp);`
- L675 _protected member_ `TArray<FVector4f> StrokeInitialColorBuffer;` — in Mix blending mode we need to accumulate each stroke in a fully separate buffer and blend it with the background colors. So we need that buffer and also save initial colors
- L676 _protected member_ `TArray<FVector4f> StrokeAccumColorBuffer;`
- L678 _protected member_ `EMeshVertexPaintBrushType PendingStampType = EMeshVertexPaintBrushType::Paint;`
- L680 _protected prototype_ `bool UpdateStampPosition(const FRay& WorldRay);`
- L681 _protected prototype_ `bool ApplyStamp();`
- L686 _protected member_ `UE::Geometry::FDynamicMeshOctree3 Octree;` — initial code here was ported from MeshVertexSculptTool, which requires an Octree. However since mesh shape is static, we can actually use an AABBTree, and in one case a required query (nearest-point) is not supported by Octree (currently). So currently using both (gross)
- L687 _protected member_ `UE::Geometry::FDynamicMeshAABBTree3 AABBTree;`
- L689 _protected prototype_ `bool UpdateBrushPosition(const FRay& WorldRay);`
- L691 _protected function_ `bool GetInEraseStroke()`
- L698 _protected member_ `bool bPendingPickColor = false;`
- L699 _protected member_ `bool bPendingPickEraseColor = false;`
- L702 _protected member_ `TArray<int32> ROITriangleBuffer;`
- L703 _protected member_ `TSet<int32> ROIElementSet;`
- L704 _protected member_ `TArray<int32> ROIElementBuffer;`
- L705 _protected member_ `TArray<FVector4f> ROIColorBuffer;`
- L706 _protected prototype_ `void InitializeElementROIFromTriangleROI(const TArray<int32>& TriangleROI, bool bInitializeFlatBuffers);`
- L707 _protected prototype_ `bool SyncMeshWithColorBuffer(FDynamicMesh3* Mesh);`
- L709 _protected member_ `TUniquePtr<TIndexedValuesChangeBuilder<FVector4f, FMeshVertexColorPaintChange>> ActiveChangeBuilder;`
- L710 _protected prototype_ `void BeginChange();`
- L711 _protected prototype_ `void EndChange();`
- L712 _protected prototype_ `void ExternalUpdateValues(const TArray<int32>& ElementIDs, const TArray<FVector4f>& NewValues);`
- L714 _protected prototype_ `FColor GetColorForGroup(int32 GroupID);`
- L715 _protected prototype_ `void ApplyChannelFilter(const FVector4f& CurColor, FVector4f& NewColor);`
- L716 _protected prototype_ `void OnChannelFilterModified();`
- L718 _protected member_ `TArray<FVector3d> TriNormals;`
- L719 _protected member_ `TArray<int32> UVSeamEdges;`
- L720 _protected member_ `TArray<int32> NormalSeamEdges;`
- L721 _protected prototype_ `void PrecomputeFilterData();`
- L725 _protected function_ `virtual bool ShowWorkPlane() const override`
- L728 _protected function_ `virtual float GetStampTemporalFlowRate() const override` — Currently using flow rate as 'brush strength', so disable temporal stamp spacing
- L731 _private member_ `TOptional<UE::Geometry::FGeometrySelection> GeometrySelection;`
- L732 _private member_ `TSet<int32> SelectionTids;`
- L733 _private prototype_ `bool ShouldFilterTrianglesBySelection() const;`
- L735 _private member_ `TPimplPtr<UE::Geometry::FMeshPlanarSymmetry> Symmetry;`
- L736 _private member_ `bool bMeshSymmetryIsValid = false;`
- L737 _private prototype_ `void TryToInitializeSymmetry();`
- L739 _private member_ `bool bApplySymmetry = false;`
- L740 _private member_ `TArray<int> SymmetricVertexROI;`
- L741 _private member_ `TSet<int> SymmetricTriangleROI;`
- L742 _private member_ `TArray<int32> SymmetricROITriangleBuffer;`

#### Free symbols / members of external scopes

- L33 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/MeshVertexSculptTool.h` (Public)


#### class `UMeshVertexSculptToolBuilder`  
`class UMeshVertexSculptToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L39-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: Tool Builder
- L44 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L46 _public member_ `int32 DefaultPrimaryBrushID = -1;`
- L48 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`
- L50 _private member_ `static FToolTargetTypeRequirements VSculptTypeRequirements;`

#### enum `EMeshVertexSculptBrushType`  
`enum class EMeshVertexSculptBrushType : uint8`  
_L59-120_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L62 _public enumerator_ `Move UMETA(DisplayName = "Move")` — Move vertices parallel to the view plane
- L65 _public enumerator_ `PullKelvin UMETA(DisplayName = "Kelvin Grab")` — Grab Brush, fall-off alters the influence of the grab
- L68 _public enumerator_ `PullSharpKelvin UMETA(DisplayName = "Sharp Kelvin Grab")` — Grab Brush that may generate cusps, fall-off alters the influence of the grab
- L71 _public enumerator_ `Smooth UMETA(DisplayName = "Smooth")` — Smooth mesh vertices
- L74 _public enumerator_ `SmoothFill UMETA(DisplayName = "SmoothFill")` — Smooth mesh vertices but only in direction of normal (Ctrl to invert)
- L77 _public enumerator_ `Offset UMETA(DisplayName = "Sculpt (Normal)")` — Displace vertices along the pre-stroke surface normal (Ctrl to invert)
- L80 _public enumerator_ `SculptView UMETA(DisplayName = "Sculpt (Viewpoint)")` — Displace vertices towards the camera viewpoint (Ctrl to invert)
- L83 _public enumerator_ `SculptMax UMETA(DisplayName = "Sculpt Max")` — Displaces vertices along the pre-stroke surface normal to a maximum height based on the brush size (Ctrl to invert)
- L86 _public enumerator_ `Inflate UMETA(DisplayName = "Inflate")` — Displace vertices along their vertex normals
- L89 _public enumerator_ `InflateStroke UMETA(DisplayName = "Inflate (Stroke)")` — Displace vertices along their vertex normals, operating on pre-stroke mesh.
- L92 _public enumerator_ `InflateMax UMETA(DisplayName = "Inflate Max")` — Displace vertices along their vertex normals to a maximum distance based on the brush size (Ctrl to invert)
- L95 _public enumerator_ `ScaleKelvin UMETA(DisplayName = "Kelvin Scale")` — Scale Brush will inflate or pinch radially from the center of the brush
- L98 _public enumerator_ `Pinch UMETA(DisplayName = "Pinch")` — Move vertices towards the center of the brush (Ctrl to push away)
- L101 _public enumerator_ `TwistKelvin UMETA(DisplayName = "Kelvin Twist")` — Twist Brush moves vertices in the plane perpendicular to the local mesh normal
- L104 _public enumerator_ `Flatten UMETA(DisplayName = "Flatten")` — Move vertices towards the average plane of the brush stamp region
- L107 _public enumerator_ `Plane UMETA(DisplayName = "Plane (Normal)")` — Move vertices towards a plane defined by the initial brush position
- L110 _public enumerator_ `PlaneViewAligned UMETA(DisplayName = "Plane (Viewpoint)")` — Move vertices towards a view-facing plane defined at the initial brush position
- L113 _public enumerator_ `FixedPlane UMETA(DisplayName = "FixedPlane")` — Move vertices towards a fixed plane in world space, positioned with a 3D gizmo
- L116 _public enumerator_ `EraseSculptLayer UMETA(DisplayName = "Erase Sculpt Layer")` — Erase sculpt layers
- L118 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EMeshVertexSculptBrushFilterType`  
`enum class EMeshVertexSculptBrushFilterType : uint8`  
_L125-133_
- reflection: `UENUM()`
- desc: Brush Triangle Filter Type
- L128 _public enumerator_ `None = 0` — Do not filter brush area
- L130 _public enumerator_ `Component = 1` — Only apply brush to triangles in the same connected mesh component/island
- L132 _public enumerator_ `PolyGroup = 2` — Only apply brush to triangles with the same PolyGroup

#### class `UVertexBrushSculptProperties`  
`class UVertexBrushSculptProperties : public UInteractiveToolPropertySet`  
_L138-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L146 _public member_ `EMeshVertexSculptBrushType PrimaryBrushType = EMeshVertexSculptBrushType::Offset;` — `UE_DEPRECATED(5.6, "Vertex sculpt now uses an integer for a brush ID to allow custom brush registration")` — `UPROPERTY()`
- L150 _public member_ `int32 PrimaryBrushID = 0;` — `UPROPERTY(EditAnywhere, Category = Sculpting, meta = (DisplayName = "Brush"))` — Primary Brush Mode
- L154 _public member_ `EMeshSculptFalloffType PrimaryFalloffType = EMeshSculptFalloffType::Smooth;` — `UPROPERTY(EditAnywhere, Category = Sculpting, meta = (DisplayName = "Falloff", ModelingQuickSettings = 300))` — Primary Brush Falloff Type, multiplied by Alpha Mask where applicable
- L158 _public member_ `EMeshVertexSculptBrushFilterType BrushFilter = EMeshVertexSculptBrushFilterType::None;` — `UPROPERTY(EditAnywhere, Category = Sculpting, meta = (DisplayName = "Region"))` — Filter applied to Stamp Region Triangles, based on first Stroke Stamp
- L162 _public member_ `bool bFreezeTarget = false;` — `UPROPERTY(EditAnywhere, Category = Sculpting, meta = (EditCondition = "bCanFreezeTarget", HideEditConditionToggle))` — When Freeze Target is toggled on, the Brush Target Surface will be Frozen in its current state, until toggled off. Brush strokes will be applied relative to the Target Surface, for applicable Brushes
- L166 _public member_ `bool bLockBoundaries = false;` — `UPROPERTY(EditAnywhere, Category = Sculpting)` — Whether to prevent sculpt brushes from moving mesh boundary vertices
- L170 _public member_ `float StampOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Sculpting, AdvancedDisplay, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Scale the rendered opacity of the on-surface brush stamp indicator
- L173 _public member_ `bool bCanFreezeTarget = false;` — `UPROPERTY()`
- L177 _public member_ `TWeakObjectPtr<UMeshVertexSculptTool> Tool;` — `UPROPERTY(meta = (TransientToolProperty))` — parent ref required for details customization

#### class `UVertexBrushAlphaProperties`  
`class UVertexBrushAlphaProperties : public UInteractiveToolPropertySet`  
_L186-210_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Tool Properties for a brush alpha mask
- L193 _public member_ `TObjectPtr<UTexture2D> Alpha = nullptr;` — `UPROPERTY(EditAnywhere, Category = Alpha, meta = (DisplayName = "Alpha Mask", ModelingQuickSettings = 400))` — Alpha mask applied to brush stamp. Red channel is used.
- L197 _public member_ `float RotationAngle = 0.0;` — `UPROPERTY(EditAnywhere, Category = Alpha, meta = (DisplayName = "Angle", UIMin = "-180.0", UIMax = "180.0", ClampMin = "-360.0", ClampMax = "360.0"))` — Alpha is rotated by this angle, inside the brush stamp frame (vertically aligned)
- L201 _public member_ `bool bRandomize = false;` — `UPROPERTY(EditAnywhere, Category = Alpha, AdvancedDisplay)` — If true, a random angle in +/- RandomRange is added to Rotation angle for each stamp
- L205 _public member_ `float RandomRange = 180.0;` — `UPROPERTY(EditAnywhere, Category = Alpha, AdvancedDisplay, meta = (UIMin = "0.0", UIMax = "180.0"))` — Bounds of random generation (positive and negative) for randomized stamps
- L209 _public member_ `TWeakObjectPtr<UMeshVertexSculptTool> Tool;` — `UPROPERTY(meta = (TransientToolProperty))` — parent ref required for details customization

#### class `UMeshSymmetryProperties`  
`class UMeshSymmetryProperties : public UInteractiveToolPropertySet`  
_L216-227_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L222 _public member_ `bool bEnableSymmetry = false;` — `UPROPERTY(EditAnywhere, Category = Symmetry, meta = (HideEditConditionToggle, EditCondition = bSymmetryCanBeEnabled, ModelingQuickSettings = 500))` — Enable/Disable symmetric sculpting. This option will not be available if symmetry cannot be detected, or a non-symmetric edit has been made
- L226 _public member_ `bool bSymmetryCanBeEnabled = false;` — `UPROPERTY(meta = (TransientToolProperty))` — this flag is set/updated by the Tool to enable/disable the bEnableSymmetry toggle

#### class `UMeshVertexSculptTool`  
`class UMeshVertexSculptTool : public UMeshSculptToolBase, public IInteractiveToolManageGeometrySelectionAPI, public IModelingToolExternalDynamicMeshUpdateAPI`  
_L239-528_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptToolBase,IInteractiveToolManageGeometrySelectionAPI,IModelingToolExternalDynamicMeshUpdateAPI`
- desc: Mesh Vertex Sculpt Tool Class
- L243 _public prototype_ `bool DoesTargetHaveSculptLayers() const;`
- L245 _public prototype_ `virtual void Setup() override;`
- L246 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L247 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L248 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L250 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L252 _public function_ `virtual bool HasCancel() const override`
- L253 _public function_ `virtual bool HasAccept() const override`
- L255 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L257 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L260 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L266 _public function_ `virtual bool AllowToolMeshUpdates() const override` — IInteractiveToolExternalDynamicMeshUpdateAPI methods
- L267 _public prototype_ `virtual void UpdateToolMeshes(TFunctionRef<TUniquePtr<FMeshRegionChangeBase>(FDynamicMesh3&, int32 MeshIdx)> UpdateMesh) override;`
- L268 _public function_ `virtual void ProcessToolMeshes(TFunctionRef<void(const FDynamicMesh3&, int32 MeshIdx)> ProcessMesh) const override`
- L272 _public function_ `virtual int32 NumToolMeshes() const override`
- L281 _public member_ `TObjectPtr<UVertexBrushSculptProperties> SculptProperties;` — `UPROPERTY()` — Properties that control sculpting
- L284 _public member_ `TObjectPtr<UVertexBrushAlphaProperties> AlphaProperties;` — `UPROPERTY()`
- L287 _public member_ `TObjectPtr<UTexture2D> BrushAlpha;` — `UPROPERTY()`
- L290 _public member_ `TObjectPtr<UMeshSymmetryProperties> SymmetryProperties;` — `UPROPERTY()`
- L295 _private member_ `TObjectPtr<UMeshSculptLayerProperties> SculptLayerProperties;` — `UPROPERTY()` — TODO: These sculpt layer properties should be moved off this tool, to a separate UI
- L298 _private prototype_ `void RefreshSculptLayerProperties();` — Call to sync sculpt layer properties to the current mesh state
- L301 _public prototype_ `virtual void IncreaseBrushSpeedAction() override;`
- L302 _public prototype_ `virtual void DecreaseBrushSpeedAction() override;`
- L304 _public prototype_ `virtual void UpdateBrushAlpha(UTexture2D* NewAlpha);`
- L306 _public prototype_ `virtual void SetActiveBrushType(int32 Identifier);`
- L307 _public prototype_ `virtual void SetActiveFalloffType(int32 Identifier);`
- L308 _public prototype_ `virtual void SetRegionFilterType(int32 Identifier);`
- L311 _public function_ `virtual TSet<UMeshSculptToolBase::FBrushTypeInfo> GetAvailableBrushTypes()` — retrieves a set of FBrushTypeInfos representing the brushes currently available to be enabled
- L313 _public prototype_ `void SetDefaultPrimaryBrushID(int32 InPrimaryBrushID);`
- L315 _public prototype_ `bool CanUpdateBrushType() const;`
- L325 _public prototype_ `DECLARE_MULTICAST_DELEGATE(OnInteractiveToolDetailsPanelRequestRebuild);`
- L326 _public member_ `OnInteractiveToolDetailsPanelRequestRebuild OnDetailsPanelRequestRebuild;`
- L330 _protected prototype_ `virtual void RegisterBrushes();` — Overriden by subclasses to choose the brushes they use
- L333 _protected prototype_ `virtual FString GetPropertyCacheIdentifier() const override;` — Should be overriden by subclasses so that settings are not shared across this tool and subclasses.
- L336 _protected prototype_ `virtual void SaveActiveStrokeModifiers() override;` — UMeshSculptToolBase API
- L337 _protected prototype_ `virtual void InitializeIndicator() override;`
- L338 _protected prototype_ `virtual UPreviewMesh* MakeBrushIndicatorMesh(UObject* Parent, UWorld* World) override;`
- L340 _protected function_ `virtual UBaseDynamicMeshComponent* GetSculptMeshComponent() override`
- L341 _protected function_ `virtual FDynamicMesh3* GetBaseMesh() override`
- L342 _protected function_ `virtual const FDynamicMesh3* GetBaseMesh() const override`
- L344 _protected prototype_ `virtual int32 FindHitSculptMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L345 _protected prototype_ `virtual int32 FindHitTargetMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L346 _protected prototype_ `bool IsHitTriangleBackFacing(int32 TriangleID, const FDynamicMesh3* QueryMesh) const;`
- L348 _protected prototype_ `virtual void UpdateHoverStamp(const FFrame3d& StampFrameWorld) override;`
- L350 _protected prototype_ `virtual void OnBeginStroke(const FRay& WorldRay) override;`
- L351 _protected prototype_ `virtual void OnEndStroke() override;`
- L352 _protected prototype_ `virtual void OnCancelStroke() override;`
- L358 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L361 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent = nullptr;` — `UPROPERTY()`
- L364 _protected prototype_ `void OnDynamicMeshComponentChanged(UDynamicMeshComponent* Component, const FMeshRegionChangeBase* Change, bool bRevert);` — realtime visualization
- L365 _protected member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L368 _protected prototype_ `void UpdateBrushType(EMeshVertexSculptBrushType BrushType);` — `UE_DEPRECATED(5.6, "Vertex sculpt now uses an integer for a brush ID to allow custom brush registration")`
- L370 _protected prototype_ `virtual void UpdateBrushType(int32 BrushID);`
- L379 _protected prototype_ `FFrame3d GetSymmetricBrushFrameWorld() const;` — Fetch the BrushFrame in World space with considerations for symmetry. When symmetry is enabled, the frame will always be in the positive side of the symmetry plane to simplify the mirror ROI computation. This should be used wherever we use the BrushFrame to compute an ROI to properly support symmetry. @return The brush frame in world space.
- L389 _protected prototype_ `FFrame3d GetSymmetricBrushFrameLocal() const;` — Fetch the BrushFrame in Local space with considerations for symmetry. When symmetry is enabled, the frame will always be in the positive side of the symmetry plane to simplify the mirror ROI computation. This should be used wherever we use the BrushFrame to compute an ROI to properly support symmetry. @return The brush frame in local space.
- L392 _protected member_ `TUniquePtr<UE::Geometry::FPolygroupSet> ActiveGroupSet;`
- L393 _protected member_ `TArray<int32> TriangleComponentIDs;`
- L395 _protected member_ `int32 InitialStrokeTriangleID = -1;`
- L397 _protected member_ `TSet<int32> AccumulatedTriangleROI;`
- L399 _protected member_ `bool bUndoUpdatePending = false;` — `UE_DEPRECATED(5.8, "bUndoUpdatePending is no longer used")`
- L401 _protected member_ `TFuture<bool> UndoNormalsFuture;` — `UE_DEPRECATED(5.8, "UndoNormalsFuture is no longer used")`
- L402 _protected member_ `TFuture<bool> UndoUpdateOctreeFuture;`
- L403 _protected member_ `TFuture<bool> UndoUpdateBaseMeshFuture;`
- L404 _protected member_ `TFuture<void> UndoUpdateFuture;`
- L405 _protected member_ `TArray<int> NormalsBuffer;`
- L408 _protected function_ `void WaitForPendingUndoRedo()` — `UE_DEPRECATED(5.7, "Vertex sculpt now uses a const version of WaitForPendingUndoRedo")`
- L409 _protected prototype_ `void WaitForPendingUndoRedoUpdate() const;`
- L411 _protected member_ `TArray<uint32> OctreeUpdateTempBuffer;`
- L412 _protected member_ `TArray<bool> OctreeUpdateTempFlagBuffer;`
- L413 _protected member_ `TFuture<void> StampUpdateOctreeFuture;`
- L415 _protected member_ `bool bStampUpdatePending = false;` — `UE_DEPRECATED(5.7, "Check StampUpdateOctreeFuture directly instead")`
- L418 _protected function_ `void WaitForPendingStampUpdate()` — `UE_DEPRECATED(5.7, "Vertex sculpt now uses a const version of WaitForPendingStampUpdate")`
- L419 _protected prototype_ `void WaitForPendingStampUpdateConst() const;`
- L422 _protected member_ `TArray<int> RangeQueryTriBuffer;` — `UE_DEPRECATED(5.8, "RangeQueryTriBuffer is not used anymore")`
- L423 _protected member_ `UE::Geometry::FUniqueIndexSet VertexROIBuilder;`
- L424 _protected member_ `UE::Geometry::FUniqueIndexSet TriangleROIBuilder;`
- L426 _protected member_ `TArray<UE::Geometry::FIndex3i> TriangleROIInBuf;` — `UE_DEPRECATED(5.8, "TriangleROIInBuf is not used anymore")`
- L427 _protected member_ `TArray<int> VertexROI;`
- L428 _protected member_ `TArray<int> TriangleROIArray;`
- L429 _protected prototype_ `void UpdateROI(const FFrame3d& LocalFrame);`
- L431 _protected prototype_ `void UpdateROI(const FVector3d& BrushPos);` — `UE_DEPRECATED(5.6, "Use the FFrame3d overload instead.")`
- L433 _private prototype_ `void ComputeVertexAndTriangleROI(const FFrame3d& LocalFrame);`
- L434 _private prototype_ `void PrepROIVertPositionBuffers();`
- L436 _protected function_ `virtual bool RequireConnectivityToHitPointInStamp() const`
- L438 _protected member_ `UE::Geometry::FUniqueIndexSet NormalsROIBuilder;`
- L439 _protected member_ `TArray<std::atomic<bool>> NormalsFlags;` — set of per-vertex or per-element-id flags that indicate
- L443 _protected member_ `bool bTargetDirty;`
- L446 _protected member_ `EMeshVertexSculptBrushType PendingStampType = EMeshVertexSculptBrushType::Smooth;` — `UE_DEPRECATED(5.6, "Vertex sculpt now uses an integer for a brush ID to allow custom brush registration")`
- L448 _private member_ `int32 PendingStampBrushID = (int32)EMeshVertexSculptBrushType::Smooth;`
- L451 _protected prototype_ `bool UpdateStampPosition(const FRay& WorldRay);`
- L452 _protected prototype_ `TFuture<void> ApplyStamp();`
- L454 _protected member_ `FVector3d PreviousRayDirection;`
- L455 _protected member_ `bool bMouseMoved = false;`
- L457 _protected member_ `FSculptBrushStamp LastMovedStamp;` — The stamp used last time bMouseMoved was true
- L459 _protected member_ `FRandomStream StampRandomStream;`
- L466 _protected member_ `FDynamicMesh3 BaseMesh;` — The base mesh is a second copy of our mesh that we can intentionally not update during some sculpt strokes so that we can base certain hittesting or processing off that mesh instead of the latest result, e.g. when using brushes that offset some max amount, so that we only offset relative to the mesh as it was before the start of the stroke.
- L467 _protected member_ `UE::Geometry::FDynamicMeshOctree3 BaseMeshSpatial;`
- L468 _protected member_ `TArray<int32> BaseMeshIndexBuffer;`
- L469 _protected member_ `bool bCachedFreezeTarget = false;`
- L470 _protected prototype_ `void UpdateBaseMesh(const TSet<int32>* TriangleROI = nullptr);`
- L471 _protected prototype_ `bool GetBaseMeshNearest(int32 VertexID, const FVector3d& Position, double SearchRadius, FVector3d& TargetPosOut, FVector3d& TargetNormalOut);`
- L472 _protected member_ `TFunction<bool(int32, const FVector3d&, double MaxDist, FVector3d&, FVector3d&)> BaseMeshQueryFunc;`
- L475 _protected member_ `UE::Geometry::FDynamicMeshOctree3 Octree;` — triangle octree used for raycast queries; for ROI queries we use the VertexOctree (in private scope, below)
- L476 _protected member_ `bool bOctreeUpdated = false;`
- L477 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshOctree3::FTreeCutSet> CutTree;`
- L479 _protected member_ `TObjectPtr<UPreviewGeometry> OctreeGeometry;` — `UPROPERTY()`
- L481 _protected prototype_ `bool UpdateBrushPosition(const FRay& WorldRay);`
- L483 _protected member_ `double SculptMaxFixedHeight = -1.0;`
- L485 _protected member_ `bool bHaveBrushAlpha = false;`
- L486 _protected member_ `UE::Geometry::TImageBuilder<FVector4f> BrushAlphaValues;`
- L487 _protected member_ `UE::Geometry::FImageDimensions BrushAlphaDimensions;`
- L488 _protected prototype_ `double SampleBrushAlpha(const FSculptBrushStamp& Stamp, const FVector3d& Position) const;`
- L490 _protected member_ `TArray<FVector3d> ROIPositionBuffer;`
- L491 _protected member_ `TArray<FVector3d> ROIPrevPositionBuffer;`
- L493 _protected member_ `TPimplPtr<UE::Geometry::FMeshPlanarSymmetry> Symmetry;`
- L494 _protected member_ `bool bMeshSymmetryIsValid = false;`
- L495 _protected prototype_ `void TryToInitializeSymmetry();`
- L497 _protected prototype_ `virtual void UndoRedo_RestoreSymmetryPossibleState(bool bSetToValue);`
- L499 _protected member_ `bool bApplySymmetry = false;`
- L500 _protected member_ `TArray<int> SymmetricVertexROI;`
- L501 _protected member_ `TArray<FVector3d> SymmetricROIPositionBuffer;`
- L502 _protected member_ `TArray<FVector3d> SymmetricROIPrevPositionBuffer;`
- L504 _protected member_ `FMeshVertexChangeBuilder* ActiveVertexChange = nullptr;`
- L505 _protected prototype_ `void BeginChange();`
- L506 _protected prototype_ `void EndChange();`
- L508 _protected member_ `int32 DefaultPrimaryBrushID = -1;`
- L512 _protected function_ `virtual bool ShowWorkPlane() const override`
- L516 _private prototype_ `void RealignBrush(FMeshSculptBrushOp::EStampAlignmentType AlignmentType);` — Assumes that brush is currently aligned to hit normal
- L519 _private prototype_ `void OnDynamicMeshComponentChanged_Internal(UDynamicMeshComponent* Component, const FMeshRegionChangeBase* Change, bool bRevert, bool bUpdateRender = false);` — internal implementation of OnDynamicMeshComponentChanged, exposing option to update component rendering as well
- L521 _private member_ `double InitialBoundsMaxDim = 0;`
- L523 _private member_ `TArray<TArray<int32, TInlineAllocator<8>>> CachedVtxTriConnectivity, CachedVtxVtxConnectivity;` — Cached mesh connectivity for faster iteration
- L523 _private member_ `TArray<TArray<int32, TInlineAllocator<8>>> CachedVtxTriConnectivity, CachedVtxVtxConnectivity;` — Cached mesh connectivity for faster iteration
- L525 _private member_ `UE::Geometry::FUniqueIndexSet VertexROILookup;` — Re-used index set for looking up the initial ROI during connected component growth
- L527 _private member_ `UE::Geometry::TDynamicVerticesOctree3<FDynamicMesh3> VertexOctree;` — Octree used for vertex queries

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Geometry` (scope `UE`)
- L31 _prototype_ `PREDECLARE_GEOMETRY(class FMeshPlanarSymmetry);`
- L325 _delegate_ `DECLARE_MULTICAST_DELEGATE(OnInteractiveToolDetailsPanelRequestRebuild);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/OffsetMeshTool.h` (Public)


#### enum `EOffsetMeshToolOffsetType`  
`enum class EOffsetMeshToolOffsetType : uint8`  
_L14-21_
- reflection: `UENUM()`
- L17 _public enumerator_ `Iterative UMETA(DisplayName = "Iterative")` — Iterative Offsetting with N iterations
- L20 _public enumerator_ `Implicit UMETA(DisplayName = "Implicit")` — Implicit Offsetting, produces smoother output and does a better job at preserving UVs, but can be very slow on large meshes

#### class `UOffsetMeshToolProperties`  
`class UOffsetMeshToolProperties : public UInteractiveToolPropertySet`  
_L27-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Base properties of Offset
- L34 _public member_ `EOffsetMeshToolOffsetType OffsetType = EOffsetMeshToolOffsetType::Iterative;` — `UPROPERTY(EditAnywhere, Category = Offset)` — Type of Offsetting to apply
- L38 _public member_ `float Distance = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (UIMin = "-100.0", UIMax = "100.0", ClampMin = "-10000.0", ClampMax = "100000.0"))` — Offset Distance in World Units
- L42 _public member_ `bool bCreateShell = false;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (EditCondition = "OffsetType == EOffsetMeshToolOffsetType::Iterative"))` — If true, create a thickened shell, instead of only moving the input vertices

#### class `UOffsetWeightMapSetProperties`  
`class UOffsetWeightMapSetProperties : public UWeightMapSetProperties`  
_L48-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWeightMapSetProperties`
- L55 _public member_ `float MinDistance = 1.0f;` — `UPROPERTY(EditAnywhere, Category = WeightMap, meta = (UIMin = "-100.0", UIMax = "100.0", ClampMin = "-10000.0", ClampMax = "100000.0", DisplayPriority = 5))` — Minimum Offset Distance in World Units, for Weight Map values of zero (clamped to Distance)

#### class `UIterativeOffsetProperties`  
`class UIterativeOffsetProperties : public UInteractiveToolPropertySet`  
_L61-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for Iterative Offsetting
- L68 _public member_ `int32 Steps = 10;` — `UPROPERTY(EditAnywhere, Category = IterativeOffsetOptions, meta = (UIMin = "1", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — Number of Offsetting iterations
- L72 _public member_ `bool bOffsetBoundaries = true;` — `UPROPERTY(EditAnywhere, Category = IterativeOffsetOptions)` — Control whether the boundary is allowed to move
- L76 _public member_ `float SmoothingPerStep = 0.0f;` — `UPROPERTY(EditAnywhere, Category = IterativeOffsetOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of smoothing applied per Offset step
- L80 _public member_ `bool bReprojectSmooth = false;` — `UPROPERTY(EditAnywhere, Category = IterativeOffsetOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition="SmoothingPerStep > 0"))` — Reproject smooth vertices onto non-smoothed Offset Surface at each step (expensive but better-preserves uniform distance)

#### class `UImplicitOffsetProperties`  
`class UImplicitOffsetProperties : public UInteractiveToolPropertySet`  
_L86-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for Implicit Offsetting
- L93 _public member_ `float Smoothness = 0.2f;` — `UPROPERTY(EditAnywhere, Category = ImplicitOffsettingOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "100.0"))` — How tightly we should constrain the constrained implicit offset to the explicit offset
- L97 _public member_ `bool bPreserveUVs = true;` — `UPROPERTY(EditAnywhere, Category = ImplicitOffsettingOptions)` — If this is false, triangles will be reshaped to be more regular, which will distort UVs

#### class `UOffsetMeshTool`  
`class UOffsetMeshTool : public UBaseMeshProcessingTool`  
_L109-140_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseMeshProcessingTool`
- desc: Mesh Offsetting Tool
- L114 _public prototype_ `UOffsetMeshTool();`
- L116 _public prototype_ `virtual void InitializeProperties() override;`
- L117 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L119 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;`
- L121 _public function_ `virtual bool RequiresInitialVtxNormals() const`
- L122 _public function_ `virtual bool RequiresInitialBoundaryLoops() const`
- L123 _public prototype_ `virtual bool HasMeshTopologyChanged() const override;`
- L125 _public prototype_ `virtual FText GetToolMessageString() const override;`
- L126 _public prototype_ `virtual FText GetAcceptTransactionName() const override;`
- L130 _protected member_ `TObjectPtr<UOffsetMeshToolProperties> OffsetProperties = nullptr;` — `UPROPERTY()`
- L133 _protected member_ `TObjectPtr<UIterativeOffsetProperties> IterativeProperties = nullptr;` — `UPROPERTY()`
- L136 _protected member_ `TObjectPtr<UImplicitOffsetProperties> ImplicitProperties = nullptr;` — `UPROPERTY()`
- L139 _protected member_ `TObjectPtr<UOffsetWeightMapSetProperties> WeightMapProperties = nullptr;` — `UPROPERTY()`

#### class `UOffsetMeshToolBuilder`  
`class UOffsetMeshToolBuilder : public UBaseMeshProcessingToolBuilder`  
_L149-154_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseMeshProcessingToolBuilder`
- L153 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ProjectToTargetTool.h` (Public)


#### class `UProjectToTargetToolBuilder`  
`class UProjectToTargetToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L15-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- desc: Determine if/how we can build UProjectToTargetTool. It requires two selected mesh components.
- L19 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L20 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### class `UProjectToTargetToolProperties`  
`class UProjectToTargetToolProperties : public URemeshMeshToolProperties`  
_L29-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URemeshMeshToolProperties`
- desc: Subclass URemeshMeshToolProperties just so we can set default values for some properties. Setting these values in the Setup function of UProjectToTargetTool turns out to be tricky to achieve with the property cache.
- L36 _public member_ `bool bWorldSpace = true;` — `UPROPERTY(EditAnywhere, Category = ProjectionSpace)`
- L39 _public member_ `bool bParallel = true;` — `UPROPERTY(EditAnywhere, Category = Remeshing)`
- L42 _public member_ `int FaceProjectionPassesPerRemeshIteration = 1;` — `UPROPERTY(EditAnywhere, Category = NormalFlow, meta = (EditCondition = "RemeshType == ERemeshType::NormalFlow", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "100"))`
- L45 _public member_ `float SurfaceProjectionSpeed = 0.2f;` — `UPROPERTY(EditAnywhere, Category = NormalFlow, meta = (EditCondition = "RemeshType == ERemeshType::NormalFlow", UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "10.0"))`
- L48 _public member_ `float NormalAlignmentSpeed = 0.2f;` — `UPROPERTY(EditAnywhere, Category = NormalFlow, meta = (EditCondition = "RemeshType == ERemeshType::NormalFlow", UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "10.0"))`
- L51 _public member_ `bool bSmoothInFillAreas = true;` — `UPROPERTY(EditAnywhere, Category = NormalFlow, meta = (EditCondition = "RemeshType == ERemeshType::NormalFlow"))`
- L54 _public member_ `float FillAreaDistanceMultiplier = 0.25f;` — `UPROPERTY(EditAnywhere, Category = NormalFlow, meta = (EditCondition = "RemeshType == ERemeshType::NormalFlow && bSmoothInFillAreas", UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "10.0"))`
- L57 _public member_ `float FillAreaSmoothMultiplier = 0.25f;` — `UPROPERTY(EditAnywhere, Category = NormalFlow, meta = (EditCondition = "RemeshType == ERemeshType::NormalFlow && bSmoothInFillAreas", UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "10.0"))`
- L60 _public function_ `UProjectToTargetToolProperties() : URemeshMeshToolProperties()`

#### class `UProjectToTargetTool`  
`class UProjectToTargetTool : public URemeshMeshTool`  
_L73-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URemeshMeshTool`
- desc: Project one mesh surface onto another, while undergoing remeshing. Subclass of URemeshMeshTool to avoid duplication.
- L79 _public function_ `UProjectToTargetTool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UProjectToTargetToolProperties>(TEXT("RemeshProperties")))`
- L83 _public prototype_ `virtual void Setup() override;`
- L85 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;`
- L89 _private member_ `TUniquePtr<UE::Geometry::FDynamicMesh3> ProjectionTarget;`
- L90 _private member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> ProjectionTargetSpatial;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Properties/MeshMaterialProperties.h` (Public)


#### class `UNewMeshMaterialProperties`  
`class UNewMeshMaterialProperties : public UInteractiveToolPropertySet`  
_L20-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard material property settings for tools that generate new meshes
- L24 _public prototype_ `UNewMeshMaterialProperties();`
- L28 _public member_ `TWeakObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Material)` — Material for new mesh
- L32 _public member_ `float UVScale = 1.0;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DisplayName = "UV Scale", HideEditConditionToggle, EditConditionHides, EditCondition = "bShowExtendedOptions", Delta = 0.01, LinearDeltaSensitivity = 1))` — Scale factor for generated UVs
- L36 _public member_ `bool bWorldSpaceUVScale = false;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DisplayName = "World Space UV Scale", HideEditConditionToggle, EditConditionHides, EditCondition = "bShowExtendedOptions"))` — If true, UV scale will be relative to world space. This means objects of different sizes created with the same UV scale have the same average texel size.
- L40 _public member_ `bool bShowWireframe = false;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "bShowExtendedOptions"))` — If true, overlays preview with wireframe
- L44 _public member_ `bool bShowExtendedOptions = true;` — `UPROPERTY(meta = (TransientToolProperty))` — If true, extended options are available

#### enum `ESetMeshMaterialMode`  
`enum class ESetMeshMaterialMode : uint8`  
_L51-61_
- reflection: `UENUM()`
- desc: Standard material modes for tools that need to set custom materials for visualization
- L54 _public enumerator_ `Original` — Input material
- L57 _public enumerator_ `Checkerboard` — Checkerboard material
- L60 _public enumerator_ `Override` — Override material

#### class `UExistingMeshMaterialProperties`  
`class UExistingMeshMaterialProperties : public UInteractiveToolPropertySet`  
_L65-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard material property settings for tools that visualize materials on existing meshes (e.g. to help show UVs)
- L72 _public member_ `ESetMeshMaterialMode MaterialMode = ESetMeshMaterialMode::Original;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial)` — Material that will be used on the mesh
- L77 _public member_ `float CheckerDensity = 20.0f;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (UIMin = "1.0", UIMax = "40.0", ClampMin = "0.01", ClampMax = "1000.0", EditConditionHides, EditCondition = "MaterialMode == ESetMeshMaterialMode::Checkerboard"))` — Number of checkerboard tiles within the 0 to 1 range; only available when Checkerboard is selected as material mode
- L81 _public member_ `TObjectPtr<UMaterialInterface> OverrideMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (EditConditionHides, EditCondition = "MaterialMode == ESetMeshMaterialMode::Override"))` — Material to use instead of the original material; only available when Override is selected as material mode
- L87 _public member_ `FString UVChannel;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (DisplayName = "Preview UV Channel", GetOptions = GetUVChannelNamesFunc, EditConditionHides, EditCondition = "MaterialMode == ESetMeshMaterialMode::Checkerboard", NoResetToDefault))` — Which UV channel to use for visualizing the checkerboard material on the mesh; note that this does not affect the preview layout
- L90 _public member_ `TArray<FString> UVChannelNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L93 _public prototype_ `const TArray<FString>& GetUVChannelNamesFunc() const;` — `UFUNCTION()`
- L96 _public member_ `TObjectPtr<UMaterialInstanceDynamic> CheckerMaterial = nullptr;` — `UPROPERTY(meta = (TransientToolProperty))`
- L99 _public prototype_ `virtual void RestoreProperties(UInteractiveTool* RestoreToTool, const FString& CacheIdentifier = TEXT("")) override;` — Needs custom restore in order to call setup
- L101 _public prototype_ `void Setup();`
- L103 _public prototype_ `void UpdateMaterials();`
- L104 _public prototype_ `UMaterialInterface* GetActiveOverrideMaterial() const;`
- L106 _public prototype_ `void UpdateUVChannels(int32 UVChannelIndex, const TArray<FString>& UVChannelNames, bool bUpdateSelection = true);`

#### enum `EMeshEditingMaterialModes`  
`enum class EMeshEditingMaterialModes`  
_L110-121_
- reflection: `UENUM()`
- L112 _public enumerator_ `ExistingMaterial`
- L113 _public enumerator_ `Diffuse`
- L114 _public enumerator_ `Grey`
- L115 _public enumerator_ `Soft`
- L116 _public enumerator_ `Transparent`
- L117 _public enumerator_ `TangentNormal`
- L118 _public enumerator_ `VertexColor`
- L119 _public enumerator_ `CustomImage`
- L120 _public enumerator_ `Custom`

#### class `UMeshEditingViewProperties`  
`class UMeshEditingViewProperties : public UInteractiveToolPropertySet`  
_L125-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L132 _public member_ `bool bShowWireframe = false;` — `UPROPERTY(EditAnywhere, Category = Rendering)` — Toggle drawing of wireframe overlay on/off [Alt+W]
- L136 _public member_ `EMeshEditingMaterialModes MaterialMode = EMeshEditingMaterialModes::Diffuse;` — `UPROPERTY(EditAnywhere, Category = Rendering)` — Set which material to use on object
- L141 _public member_ `bool bFlatShading = true;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditConditionHides, EditCondition = "MaterialMode != EMeshEditingMaterialModes::ExistingMaterial && MaterialMode != EMeshEditingMaterialModes::Transparent && MaterialMode != EMeshEditingMaterialModes::Custom"))` — Toggle flat shading on/off
- L145 _public member_ `FLinearColor Color = FLinearColor(0.4f, 0.4f, 0.4f);` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshEditingMaterialModes::Diffuse"))` — Main Color of Material
- L149 _public member_ `TObjectPtr<UTexture2D> Image;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshEditingMaterialModes::CustomImage", TransientToolProperty))` — Image used in Image-Based Material
- L153 _public member_ `double Opacity = 0.65;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshEditingMaterialModes::Transparent", ClampMin = "0", ClampMax = "1.0"))` — Opacity of transparent material
- L157 _public member_ `FLinearColor TransparentMaterialColor = FLinearColor(0.0606f, 0.309f, 0.842f);` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshEditingMaterialModes::Transparent", DisplayName = "Color"))`
- L161 _public member_ `bool bTwoSided = true;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshEditingMaterialModes::Transparent"))` — Although a two-sided transparent material causes rendering issues with overlapping faces, it is still frequently useful to see the shape when sculpting around other objects.
- L164 _public member_ `TWeakObjectPtr<UMaterialInterface> CustomMaterial;` — `UPROPERTY(EditAnywhere, Category = Rendering, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshEditingMaterialModes::Custom"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Properties/MeshSculptLayerProperties.h` (Public)


#### class `UMeshSculptLayerProperties`  
`class UMeshSculptLayerProperties : public UObject`  
_L15-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L23 _public member_ `int32 ActiveLayer = 0;` — `UPROPERTY(EditAnywhere, Category = MeshLayers, meta = (ClampMin = 0, HideEditConditionToggle, EditCondition = bCanEditLayers, ModelingQuickSettings))` — Set the active mesh layer
- L27 _public member_ `TArray<double> LayerWeights;` — `UPROPERTY(EditAnywhere, EditFixedSize, NoClear, Category = MeshLayers, meta = (NoResetToDefault, HideEditConditionToggle, EditCondition = bCanEditLayers, ModelingQuickSettings))` — Set the mesh layer weights
- L30 _public member_ `bool bCanEditLayers = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L33 _public prototype_ `void AddLayer();` — Add a sculpt layer
- L36 _public prototype_ `bool RemoveLayer();` — Remove the active sculpt layer
- L40 _public prototype_ `bool RemoveLayerAtIndex(const int32 IndexOfLayerToRemove);` — `UFUNCTION(Category = MeshLayers)` — Remove the sculpt layer at the provided index
- L44 _public prototype_ `FName GetLayerName(const int32 InIndex);` — `UFUNCTION(Category = MeshLayers)` — Return the name of the sculpt layer at the provided index
- L48 _public prototype_ `void SetLayerName(const int32 InIndex, const FName InLayerName);` — `UFUNCTION(Category = MeshLayers)` — Set the name of the layer at the provided index to the provided name
- L52 _public prototype_ `void MoveLayer(const int32 InInitIndex, int32 InTargetIndex);` — `UFUNCTION(Category = MeshLayers)` — Move the layer at the first provided index to the location provided by the second index
- L56 _public prototype_ `void SetActiveLayer(const int32 InIndex);` — `UFUNCTION(Category = MeshLayers)` — Sets the currently active sculpt layer to be the one at the provided index
- L60 _public prototype_ `void SetLayerWeight(const int32 InIndex, double InWeight, const uint32 ChangeType);` — `UFUNCTION(Category = MeshLayers)` — Sets the weight of the layer at the provided index to the provided weight
- L62 _public prototype_ `void Init(IModelingToolExternalDynamicMeshUpdateAPI* InTool, int32 InNumLockedBaseLayers);`
- L65 _public prototype_ `void RefreshFromMesh();` — Refresh properties from current mesh data
- L68 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L71 _public function_ `int32 GetNumLockedBaseLayers() const`
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE(OnMeshLayersPropertiesPanelRequestRebuild);`
- L75 _public member_ `OnMeshLayersPropertiesPanelRequestRebuild OnMeshLayersPanelRequestRebuild;`
- L79 _private member_ `IModelingToolExternalDynamicMeshUpdateAPI* Tool = nullptr;`
- L81 _private member_ `int32 NumLockedBaseLayers = 0;`
- L85 _private member_ `TSharedPtr<FDynamicMesh3> InitialMesh;` — Mesh before layer change has been applied. Used for tracking mesh changes that occur over multiple frames (i.e., from an interactive drag) TODO: Add/update a mesh FChange to track sculpt layer changes, and use that instead of saving an entire mesh here
- L88 _private prototype_ `void SetLayerWeights(FDynamicMeshSculptLayers* SculptLayers) const;` — Helper to set sculpt layers from the current LayerWeights property (accounting for the NumLockedBaseLayers)
- L91 _private prototype_ `void UpdateSettingsFromMesh(const FDynamicMeshSculptLayers* SculptLayers);` — Update the ActiveLayer and LayerWeights settings from the current sculpt layers
- L96 _private prototype_ `void EditSculptLayers(TFunctionRef<void(UE::Geometry::FDynamicMesh3& Mesh, UE::Geometry::FDynamicMeshSculptLayers* SculptLayers)> EditFn, bool bEmitChange);` — Helper to apply edits to the current sculpt layers if possible, with associated book keeping @param EditFn The edit to apply if possible @param bEmitChange Whether to emit a change object along with the edit
- L99 _private prototype_ `bool ReadSculptLayers(TFunctionRef<void(const UE::Geometry::FDynamicMesh3& Mesh, const UE::Geometry::FDynamicMeshSculptLayers* SculptLayers)> ReadFn);` — Helper to read current sculpt layers if possible

#### Free symbols / members of external scopes

- L10 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L11 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMeshSculptLayers);`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE(OnMeshLayersPropertiesPanelRequestRebuild);`
- L102 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSculptLayerProps, Warning, All);`
- L102 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSculptLayerProps, Warning, All);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Properties/MeshStatisticsProperties.h` (Public)


#### class `UMeshStatisticsProperties`  
`class UMeshStatisticsProperties : public UInteractiveToolPropertySet`  
_L18-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L24 _public member_ `FString Mesh;` — `UPROPERTY(VisibleAnywhere, Category = MeshStatistics, meta = (NoResetToDefault))`
- L27 _public member_ `FString UV;` — `UPROPERTY(VisibleAnywhere, Category = MeshStatistics, AdvancedDisplay, meta = (NoResetToDefault))`
- L30 _public member_ `FString Attributes;` — `UPROPERTY(VisibleAnywhere, Category = MeshStatistics, AdvancedDisplay, meta = (NoResetToDefault))`
- L32 _public prototype_ `void Update(const FDynamicMesh3& Mesh);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L14 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);` — predeclarations

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Properties/MeshUVChannelProperties.h` (Public)


#### class `UMeshUVChannelProperties`  
`class UMeshUVChannelProperties : public UInteractiveToolPropertySet`  
_L17-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L24 _public member_ `FString UVChannel;` — `UPROPERTY(EditAnywhere, Category = "UV Channel", meta = (DisplayName = "UV Channel", GetOptions = GetUVChannelNamesFunc, NoResetToDefault))` — Select UV channel in the mesh
- L27 _public prototype_ `const TArray<FString>& GetUVChannelNamesFunc() const;` — `UFUNCTION()`
- L30 _public member_ `TArray<FString> UVChannelNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L32 _public prototype_ `void Initialize(int32 NumUVChannels, bool bInitializeSelection = true);`
- L33 _public prototype_ `void Initialize(const FMeshDescription* MeshDescription, bool bInitializeSelection = true);`
- L34 _public prototype_ `void Initialize(const FDynamicMesh3* Mesh, bool bInitializeSelection = true);`
- L41 _public prototype_ `bool ValidateSelection(bool bUpdateIfInvalid);` — Verify that the UV channel selection is valid @param bUpdateIfInvalid if selection is not valid, reset UVChannel to UV0 or empty if no UV channels exist @return true if selection in UVChannel is an entry in UVChannelNamesList.
- L47 _public prototype_ `int32 GetSelectedChannelIndex(bool bForceToZeroOnFailure = false);` — @param bForceToZeroOnFailure if true, then instead of returning -1 we return 0 so calling code can fallback to default UV paths @return selected UV channel index, or -1 if invalid selection, or 0 if invalid selection and bool bForceToZeroOnFailure = true

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L13 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Properties/MeshWeightChannelProperties.h` (Public)


#### class `UMeshWeightChannelDensityProperties`  
`class UMeshWeightChannelDensityProperties : public UInteractiveToolPropertySet`  
_L16-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L23 _public member_ `bool bUseWeightMap;` — `UPROPERTY(EditAnywhere, Category = WeightMap)` — Whether to use a vertex weight map layer to control relative mesh density
- L27 _public member_ `FName SelectedAttribute;` — `UPROPERTY(EditAnywhere, Category = WeightMap, meta = (DisplayName = "Attribute", GetOptions = GetAttributeNames, EditCondition = bUseWeightMap))` — Name of the vertex weight map layer that will be used to adjust relative mesh density
- L30 _public function_ `const TArray<FName>& GetAttributeNames()` — `UFUNCTION()`
- L32 _public member_ `TArray<FName> AttributeNames;`
- L36 _public member_ `float RelativeDensity = 1.f;` — `UPROPERTY(EditAnywhere, Category = WeightMap, meta = (EditCondition = bUseWeightMap, UIMin = "-2.0", UIMax = "2.0"))` — Amount to adjust density in regions where the vertex weight map is greater than zero. A positive value here results in a denser mesh, a negative value results in a coarser one
- L41 _public prototype_ `void InitializeAttributes(const UE::Geometry::FDynamicMesh3* const Mesh);` — Set up the list of available attributes
- L46 _public prototype_ `void ValidateSelectedAttribute();` — If the attribute selection is not valid, use the attribute at index 0 or empty if there are no attributes
- L49 _public prototype_ `int32 GetSelectedWeightAttributeIndex(const UE::Geometry::FDynamicMesh3* const Mesh) const;` — @return the selected weight attribute on the given dynamic mesh or INDEX_NONE if not found

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L12 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Properties/RemeshProperties.h` (Public)


#### enum `EMeshBoundaryConstraint`  
`enum class EMeshBoundaryConstraint : uint8`  
_L14-19_
- reflection: `UENUM()`
- desc: Mesh Boundary Constraint Types
- L16 _public enumerator_ `Fixed = (uint8)EEdgeRefineFlags::FullyConstrained UMETA(DisplayName = "Fixed")`
- L17 _public enumerator_ `Refine = (uint8)EEdgeRefineFlags::SplitsOnly UMETA(DisplayName = "Refine")`
- L18 _public enumerator_ `Free = (uint8)EEdgeRefineFlags::NoFlip UMETA(DisplayName = "Free")`

#### enum `EGroupBoundaryConstraint`  
`enum class EGroupBoundaryConstraint : uint8`  
_L23-29_
- reflection: `UENUM()`
- desc: Group Boundary Constraint Types
- L25 _public enumerator_ `Fixed = (uint8)EEdgeRefineFlags::FullyConstrained UMETA(DisplayName = "Fixed")`
- L26 _public enumerator_ `Refine = (uint8)EEdgeRefineFlags::SplitsOnly UMETA(DisplayName = "Refine")`
- L27 _public enumerator_ `Free = (uint8)EEdgeRefineFlags::NoFlip UMETA(DisplayName = "Free")`
- L28 _public enumerator_ `Ignore = (uint8)EEdgeRefineFlags::NoConstraint UMETA(DisplayName = "Ignore")`

#### enum `EMaterialBoundaryConstraint`  
`enum class EMaterialBoundaryConstraint : uint8`  
_L33-39_
- reflection: `UENUM()`
- desc: Material Boundary Constraint Types
- L35 _public enumerator_ `Fixed = (uint8)EEdgeRefineFlags::FullyConstrained UMETA(DisplayName = "Fixed")`
- L36 _public enumerator_ `Refine = (uint8)EEdgeRefineFlags::SplitsOnly UMETA(DisplayName = "Refine")`
- L37 _public enumerator_ `Free = (uint8)EEdgeRefineFlags::NoFlip UMETA(DisplayName = "Free")`
- L38 _public enumerator_ `Ignore = (uint8)EEdgeRefineFlags::NoConstraint UMETA(DisplayName = "Ignore")`

#### class `UMeshConstraintProperties`  
`class UMeshConstraintProperties : public UInteractiveToolPropertySet`  
_L42-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L48 _public member_ `bool bPreserveSharpEdges;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Edge Constraints")` — If true, sharp edges are preserved
- L52 _public member_ `EMeshBoundaryConstraint MeshBoundaryConstraint = EMeshBoundaryConstraint::Free;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Boundary Constraints", meta = (DisplayName = "Mesh Boundary"))` — Mesh Boundary Constraint Type
- L56 _public member_ `EGroupBoundaryConstraint GroupBoundaryConstraint = EGroupBoundaryConstraint::Free;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Boundary Constraints", meta = (DisplayName = "Group Boundary"))` — Group Boundary Constraint Type
- L60 _public member_ `EMaterialBoundaryConstraint MaterialBoundaryConstraint = EMaterialBoundaryConstraint::Free;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Boundary Constraints", meta = (DisplayName = "Material Boundary"))` — Material Boundary Constraint Type
- L64 _public member_ `bool bPreventNormalFlips = false;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Edge Constraints", meta=(EditCondition = "IsPreventNormalFlipsEnabled"))` — Prevent normal flips
- L68 _public member_ `bool bPreventTinyTriangles = false;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Edge Constraints", meta=(EditCondition = "IsPreventTinyTrianglesEnabled"))` — Prevent introduction of tiny triangles or slivers
- L73 _protected function_ `virtual bool IsPreventNormalFlipsEnabled() const` — `UFUNCTION()`
- L76 _protected function_ `virtual bool IsPreventTinyTrianglesEnabled() const` — `UFUNCTION()`

#### class `URemeshProperties`  
`class URemeshProperties : public UMeshConstraintProperties`  
_L80-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshConstraintProperties`
- L87 _public member_ `float SmoothingStrength = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Remeshing, meta = (DisplayName = "Smoothing Rate", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of Vertex Smoothing applied within Remeshing
- L91 _public member_ `bool bFlips = false;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Edge Constraints", meta = (DisplayName = "Allow Flips"))` — Enable edge flips in Remeshing (tends to lose edges/detail)
- L95 _public member_ `bool bSplits = true;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Edge Constraints", meta = (DisplayName = "Allow Splits"))` — Enable edge splits in Remeshing
- L99 _public member_ `bool bCollapses = true;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Edge Constraints", meta = (DisplayName = "Allow Collapses"))` — Enable edge collapses in Remeshing

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Properties/RevolveProperties.h` (Public)


#### enum `ERevolvePropertiesCapFillMode`  
`enum class ERevolvePropertiesCapFillMode : uint8`  
_L18-29_
- reflection: `UENUM()`
- L21 _public enumerator_ `None` — No caps will be generated.
- L24 _public enumerator_ `CenterFan` — Caps are triangulated by placing a vertex in the center and creating a fan to the boundary. This works well if the path is convex, but can create invalid geometry if it is concave.
- L26 _public enumerator_ `Delaunay` — Caps are triangulated to maximize the minimal angle in the triangles using Delaunay triangulation.
- L28 _public enumerator_ `EarClipping` — Caps are triangulated using a standard ear clipping approach. This could result in some very thin triangles.

#### enum `ERevolvePropertiesPolygroupMode`  
`enum class ERevolvePropertiesPolygroupMode : uint8`  
_L33-43_
- reflection: `UENUM()`
- L36 _public enumerator_ `PerShape` — One PolyGroup for the entire shape
- L38 _public enumerator_ `PerFace` — One PolyGroup for each geometric face
- L40 _public enumerator_ `PerRevolveStep` — One PolyGroup along the path for each revolution step
- L42 _public enumerator_ `PerPathSegment` — One PolyGroup along the revolution steps for each path segment

#### enum `ERevolvePropertiesQuadSplit`  
`enum class ERevolvePropertiesQuadSplit : uint8`  
_L46-53_
- reflection: `UENUM()`
- L49 _public enumerator_ `Uniform` — Quads will always be split into triangles the same way regardless of quad shape.
- L52 _public enumerator_ `Compact` — Quads will be split into triangles by connecting the shortest diagonal.

#### class `URevolveProperties`  
`class URevolveProperties : public UInteractiveToolPropertySet`  
_L59-200_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Common properties for revolving a PolyPath to create a mesh.
- L64 _public function_ `URevolveProperties()`
- L89 _public member_ `double RevolveDegreesClamped = 360;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (DisplayName = "Degrees", UIMin = "0", UIMax = "360", ClampMin = "0", ClampMax = "360", EditCondition = "HeightOffsetPerDegree == 0", EditConditionHides))` — Revolution extent in degrees. Clamped to a maximum of 360 if Height Offset Per Degree is set to 0.
- L94 _public member_ `double RevolveDegrees = 360;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (DisplayName = "Degrees", UIMin = "0", UIMax = "3600", ClampMin = "0", ClampMax = "360000", EditCondition = "HeightOffsetPerDegree != 0", EditConditionHides))` — Revolution extent in degrees. Clamped to a maximum of 360 if Height Offset Per Degree is set to 0.
- L98 _public member_ `double RevolveDegreesOffset = 0;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (DisplayName = "Degrees Offset", UIMin = "-360", UIMax = "360", ClampMin = "-36000", ClampMax = "36000"))` — The angle by which to rotate the path around the axis before beginning the revolve.
- L102 _public member_ `double StepsMaxDegrees = 15;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (UIMin = "1", ClampMin = "1", UIMax = "120", ClampMax = "180", EditCondition = "!bExplicitSteps"))` — Implicitly defines the number of steps in the revolution such that each step moves the revolution no more than the given number of degrees. This is only available if Explicit Steps is disabled.
- L106 _public member_ `bool bExplicitSteps = false;` — `UPROPERTY(EditAnywhere, Category = Revolve)` — If true, the number of steps can be specified explicitly via Steps. If false, the number of steps is adjusted automatically based on Steps Max Degrees.
- L111 _public member_ `int NumExplicitSteps = 24;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (DisplayName = "Steps", UIMin = "1", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "bExplicitSteps"))` — Number of steps in the revolution. This is only available if Explicit Steps is enabled.
- L115 _public member_ `double HeightOffsetPerDegree = 0;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (DisplayName = "Height Offset", UIMin = "-10", UIMax = "10", ClampMin = "-100000", ClampMax = "100000"))` — How far to move each step along the revolution axis per degree. Non-zero values are useful for creating spirals.
- L119 _public member_ `bool bReverseRevolutionDirection = false;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (DisplayName = "Reverse"))` — By default, revolution is done counterclockwise if looking down the revolution axis. This reverses the revolution direction to clockwise.
- L123 _public member_ `bool bFlipMesh = false;` — `UPROPERTY(EditAnywhere, Category = Revolve)` — Flips the mesh inside out.
- L127 _public member_ `bool bSharpNormals = false;` — `UPROPERTY(EditAnywhere, Category = Revolve)` — If true, normals are not averaged or shared between triangles beyond the Sharp Normals Degree Threshold.
- L132 _public member_ `double SharpNormalsDegreeThreshold = 0.1;` — `UPROPERTY(EditAnywhere, Category = Revolve, meta = (DisplayName = "Sharp Normals Threshold", ClampMin = "0.0", ClampMax = "90.0", EditCondition = "bSharpNormals"))` — The threshold in degrees beyond which normals are not averaged or shared between triangles anymore. This is only available if Sharp Normals is enabled.
- L136 _public member_ `bool bPathAtMidpointOfStep = false;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (DisplayName = "Path at Midpoint"))` — If true, the path is placed at the midpoint of each step instead of at the start and/or end of a step. For example, this is useful for creating square columns.
- L140 _public member_ `ERevolvePropertiesPolygroupMode PolygroupMode = ERevolvePropertiesPolygroupMode::PerFace;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (DisplayName = "PolyGroup Mode"))` — How PolyGroups are assigned to shape primitives. If caps are generated, they will always be in separate groups.
- L144 _public member_ `ERevolvePropertiesQuadSplit QuadSplitMode = ERevolvePropertiesQuadSplit::Compact;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay)` — How generated quads are split into triangles.
- L153 _public member_ `double QuadSplitCompactTolerance = 0.01;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (DisplayName = "Quad Split Tolerance", ClampMin = "0.0", ClampMax = "2.0", // EditCondition = "QuadSplitMode == ERevolvePropertiesQuadSplit::Compact"))` — For quad split mode Compact, this biases the length comparison to prefer one diagonal over the other. For example, a value of 0.01 allows a 1% difference in lengths before the triangulation is flipped. This helps symmetric quads to be triangulated more uniformly.
- L162 _public member_ `bool bWeldFullRevolution = true;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (EditCondition = "HeightOffsetPerDegree == 0 && RevolveDegrees == 360"))` — If true, the ends of a fully revolved path are welded together, rather than duplicating vertices at the seam. This is not relevant if the revolution is not full and/or there is a height offset.
- L166 _public member_ `bool bWeldVertsOnAxis = true;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay)` — If true, vertices close to the axis will not be replicated, instead reusing the same vertex for any adjacent triangles.
- L170 _public member_ `double AxisWeldTolerance = 0.1;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (ClampMin = "0.0", ClampMax = "20.0", EditCondition = "bWeldVertsOnAxis"))` — If welding vertices on the axis, the distance that a vertex can be from the axis and still be welded.
- L174 _public member_ `bool bFlipVs = false;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay)` — If true, UV coordinates will be flipped in the V direction.
- L179 _public member_ `bool bUVsSkipFullyWeldedEdges = true;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay)` — If true, UV layout is not affected by segments of the path that do not result in any triangles. For example, when both ends of a segment are welded due to being on the revolution axis.
- L188 _public prototype_ `void ApplyToCurveSweepOp(const UNewMeshMaterialProperties& MaterialProperties, const FVector3d& RevolutionAxisOrigin, const FVector3d& RevolutionAxisDirection, UE::Geometry::FCurveSweepOp& CurveSweepOpOut) const;` — Sets most of the settings for a FCurveSweepOp except for the profile curve itself. Should be called after setting the profile curve, as the function reverses it if necessary. CurveSweepOpOut.ProfileCurve and CurveSweepOpOut.bProfileCurveIsClosed must be initialized in advance.
- L193 _protected function_ `virtual ERevolvePropertiesCapFillMode GetCapFillMode() const`
- L198 _protected member_ `int32 ClampedRevolutionDegreesWatcherIndex;`
- L199 _protected member_ `int32 RevolutionDegreesWatcherIndex;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L15 _prototype_ `PREDECLARE_GEOMETRY(class FCurveSweepOp);`
- L73 _function_ `` (scope `URevolveProperties::URevolveProperties`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/RecomputeUVsTool.h` (Public)


#### class `URecomputeUVsToolBuilder`  
`class URecomputeUVsToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L33-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L38 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L39 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `URecomputeUVsTool`  
`class URecomputeUVsTool : public USingleSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L47-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: URecomputeUVsTool Recomputes UVs based on existing segmentations of the mesh
- L52 _public prototype_ `virtual void Setup() override;`
- L53 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L55 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L56 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L58 _public function_ `virtual bool HasCancel() const override`
- L59 _public function_ `virtual bool HasAccept() const override`
- L60 _public prototype_ `virtual bool CanAccept() const override;`
- L62 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L65 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L72 _protected member_ `TObjectPtr<UMeshUVChannelProperties> UVChannelProperties = nullptr;` — `UPROPERTY()`
- L75 _protected member_ `TObjectPtr<URecomputeUVsToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L78 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L81 _protected member_ `TObjectPtr<UExistingMeshMaterialProperties> MaterialSettings = nullptr;` — `UPROPERTY()`
- L84 _protected member_ `bool bCreateUVLayoutViewOnSetup = true;` — `UPROPERTY()`
- L87 _protected member_ `TObjectPtr<UUVLayoutPreview> UVLayoutView = nullptr;` — `UPROPERTY()`
- L90 _protected member_ `TObjectPtr<URecomputeUVsOpFactory> RecomputeUVsOpFactory;` — `UPROPERTY()`
- L93 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L95 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L97 _protected member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> ActiveGroupSet;`
- L98 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L99 _protected prototype_ `void UpdateActiveGroupLayer();`
- L100 _protected prototype_ `int32 GetSelectedUVChannel() const;`
- L101 _protected prototype_ `void OnPreviewMeshUpdated();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/RemeshMeshTool.h` (Public)


#### class `URemeshMeshToolBuilder`  
`class URemeshMeshToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L25-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L34 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — Return true if we have one object selected. URemeshMeshTool is a UMultiSelectionTool, however we currently only ever apply it to a single mesh. (See comment at URemeshMeshTool definition below.)
- L36 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L38 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `URemeshMeshToolProperties`  
`class URemeshMeshToolProperties : public URemeshProperties`  
_L45-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URemeshProperties`
- desc: Standard properties of the Remesh operation
- L50 _public prototype_ `URemeshMeshToolProperties();`
- L54 _public member_ `int TargetTriangleCount;` — `UPROPERTY(EditAnywhere, Category = Remeshing, meta = (ClampMin = 0, EditCondition = "bUseTargetEdgeLength == false"))` — Target triangle count
- L58 _public member_ `ERemeshSmoothingType SmoothingType;` — `UPROPERTY(EditAnywhere, Category = Remeshing)` — Smoothing type
- L62 _public member_ `bool bDiscardAttributes;` — `UPROPERTY(EditAnywhere, Category = Remeshing)` — Discard UVs and existing normals, allowing the remesher to ignore any UV and normal seams. New per-vertex normals are computed.
- L66 _public member_ `bool bShowGroupColors = false;` — `UPROPERTY(EditAnywhere, Category = Display)` — Display colors corresponding to the mesh's polygon groups
- L70 _public member_ `ERemeshType RemeshType;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay)` — Remeshing type
- L74 _public member_ `int RemeshIterations;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay, meta = (EditCondition = "RemeshType == ERemeshType::FullPass", UIMin = "0", UIMax = "50", ClampMin = "0", ClampMax = "1000"))` — Number of Remeshing passes
- L78 _public member_ `int MaxRemeshIterations;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay, meta = (EditCondition = "RemeshType != ERemeshType::FullPass", UIMin = "0", UIMax = "200", ClampMin = "0", ClampMax = "200"))` — Maximum number of Remeshing passes, for Remeshers that have convergence criteria
- L82 _public member_ `int ExtraProjectionIterations;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay, meta = (EditCondition = "RemeshType == ERemeshType::NormalFlow", UIMin = "0", UIMax = "200", ClampMin = "0", ClampMax = "200"))` — For NormalFlowRemesher: extra iterations of normal flow with no remeshing
- L86 _public member_ `bool bUseTargetEdgeLength;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay)` — If true, the target count is ignored and the target edge length is used directly
- L90 _public member_ `float TargetEdgeLength;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay, meta = (NoSpinbox = "true", EditCondition = "bUseTargetEdgeLength == true", NoResetToDefault))` — Remesh to have edges approximately this length. An attempt at a reasonable value is computed automatically for this field based on the selected target mesh.
- L94 _public member_ `bool bReproject;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay)` — Enable projection back to input mesh
- L98 _public member_ `bool bReprojectConstraints;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay)` — Project constrained vertices back to original constraint curves
- L102 _public member_ `float BoundaryCornerAngleThreshold;` — `UPROPERTY(EditAnywhere, Category = Remeshing, AdvancedDisplay, meta = (EditCondition = "bReprojectConstraints", UIMin = "0", UIMax = "180", ClampMin = "0", ClampMax = "180"))` — Angle threshold in degrees for classifying a boundary vertex as a corner. Corners will be fixed if Reproject Constraints is active.

#### class `URemeshMeshTool`  
`class URemeshMeshTool : public UMultiSelectionMeshEditingTool, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L116-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Simple Mesh Remeshing Tool Note this is a subclass of UMultiSelectionTool, however we currently only ever apply it to one mesh at a time. The function URemeshMeshToolBuilder::CanBuildTool will return true only when a single mesh is selected, and the tool will only be applied to the first mesh in the selection list. The reason we inherit from UMultiSelectionTool is so that subclasses of this class can work with multiple meshes (see, for example, UProjectToTargetTool.)
- L122 _public prototype_ `URemeshMeshTool(const FObjectInitializer&);`
- L124 _public prototype_ `virtual void Setup() override;`
- L125 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L127 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L129 _public function_ `virtual bool HasCancel() const override`
- L130 _public function_ `virtual bool HasAccept() const override`
- L131 _public prototype_ `virtual bool CanAccept() const override;`
- L133 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L136 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L139 _public member_ `TObjectPtr<URemeshMeshToolProperties> BasicProperties;` — `UPROPERTY()`
- L142 _public member_ `TObjectPtr<UMeshWeightChannelDensityProperties> WeightMapProperties;` — `UPROPERTY()`
- L145 _public member_ `TObjectPtr<UMeshStatisticsProperties> MeshStatisticsProperties;` — `UPROPERTY()`
- L148 _public member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview;` — `UPROPERTY()`
- L151 _public member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay;` — `UPROPERTY()`
- L154 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L155 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> OriginalMeshSpatial;`
- L156 _protected member_ `double InitialMeshArea;`
- L158 _protected prototype_ `void UpdateVisualization();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L18 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L19 _prototype_ `PREDECLARE_GEOMETRY(typedef TMeshAABBTree3<FDynamicMesh3> FDynamicMeshAABBTree3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/RemoveOccludedTrianglesTool.h` (Public)


#### class `URemoveOccludedTrianglesToolBuilder`  
`class URemoveOccludedTrianglesToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L27-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L31 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `EOcclusionTriangleSamplingUIMode`  
`enum class EOcclusionTriangleSamplingUIMode : uint8`  
_L38-45_
- reflection: `UENUM()`
- L41 _public enumerator_ `Vertices` — Test for occlusion at vertices
- L43 _public enumerator_ `VerticesAndCentroids` — Test for occlusion at vertices and triangle centroids

#### enum `EOcclusionCalculationUIMode`  
`enum class EOcclusionCalculationUIMode : uint8`  
_L48-55_
- reflection: `UENUM()`
- L52 _public enumerator_ `GeneralizedWindingNumber` — Test for occlusion by a 3D 'Winding Number' test (Note: Allows internal 'air pockets' to be considered 'not occluded')
- L54 _public enumerator_ `RaycastOcclusionSamples` — Test for occlusion by casting rays against the mesh

#### enum `EOccludedAction`  
`enum class EOccludedAction : uint8`  
_L58-62_
- reflection: `UENUM()`
- L60 _public enumerator_ `Remove`
- L61 _public enumerator_ `SetNewGroup`

#### class `URemoveOccludedTrianglesToolProperties`  
`class URemoveOccludedTrianglesToolProperties : public UInteractiveToolPropertySet`  
_L68-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties
- L73 _public prototype_ `URemoveOccludedTrianglesToolProperties();`
- L77 _public member_ `EOcclusionCalculationUIMode OcclusionTestMethod = EOcclusionCalculationUIMode::GeneralizedWindingNumber;` — `UPROPERTY(EditAnywhere, Category = OcclusionCalculation)` — The method for deciding whether a triangle is occluded
- L81 _public member_ `EOcclusionTriangleSamplingUIMode TriangleSampling = EOcclusionTriangleSamplingUIMode::VerticesAndCentroids;` — `UPROPERTY(EditAnywhere, Category = OcclusionCalculation)` — Where to sample triangles to test occlusion
- L85 _public member_ `double WindingIsoValue = 0.5;` — `UPROPERTY(EditAnywhere, Category = OcclusionCalculation, meta = (UIMin = "-1", UIMax = "1", ClampMin = "-2", ClampMax = "2", EditCondition = "OcclusionTestMethod==EOcclusionCalculationUIMode::GeneralizedWindingNumber"))` — The winding isovalue for GeneralizedWindingNumber mode
- L89 _public member_ `int AddRandomRays = 0;` — `UPROPERTY(EditAnywhere, Category = OcclusionCalculation, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", EditCondition = "OcclusionTestMethod==EOcclusionCalculationUIMode::RaycastOcclusionSamples"))` — For raycast-based occlusion tests, optionally add random ray direction to increase the accuracy of the visibility sampling
- L93 _public member_ `int AddTriangleSamples = 0;` — `UPROPERTY(EditAnywhere, Category = OcclusionCalculation, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — Optionally add random samples to each triangle (in addition to those from TriangleSampling) to increase the accuracy of the visibility sampling
- L97 _public member_ `bool bOnlySelfOcclude = false;` — `UPROPERTY(EditAnywhere, Category = OcclusionCalculation)` — If false, when multiple meshes are selected the meshes can occlude each other.  When true, we process each selected mesh independently and only consider self-occlusions.
- L101 _public member_ `int ShrinkRemoval = 0;` — `UPROPERTY(EditAnywhere, Category = OcclusionCalculation, meta = (UIMin = "0", ClampMin = "0", Delta = 1, LinearDeltaSensitivity = 1))` — Shrink (erode) the boundary of the set of triangles to remove.
- L104 _public member_ `double MinAreaIsland = 0;` — `UPROPERTY(EditAnywhere, Category = RemoveIslands, meta = (UIMin = "0", ClampMin = "0", Delta = 0.5, LinearDeltaSensitivity = 1))`
- L107 _public member_ `int MinTriCountIsland = 0;` — `UPROPERTY(EditAnywhere, Category = RemoveIslands, meta = (UIMin = "0", ClampMin = "0", Delta = 1, LinearDeltaSensitivity = 1))`
- L111 _public member_ `EOccludedAction Action = EOccludedAction::Remove;` — `UPROPERTY(EditAnywhere, Category = Action)` — What action to perform on occluded triangles

#### class `URemoveOccludedTrianglesAdvancedProperties`  
`class URemoveOccludedTrianglesAdvancedProperties : public UInteractiveToolPropertySet`  
_L121-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Advanced properties
- L126 _public prototype_ `URemoveOccludedTrianglesAdvancedProperties();`
- L131 _public member_ `double NormalOffset = FMathd::ZeroTolerance;` — `UPROPERTY(EditAnywhere, Category = NormalsTopology, meta = (UIMin = "0.000000001", UIMax = ".0001", ClampMin = "0.0", ClampMax = "0.01"))` — probably not actually a good idea to expose this to the user

#### class `URemoveOccludedTrianglesOperatorFactory`  
`class URemoveOccludedTrianglesOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L140-152_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Factory with enough info to spawn the background-thread Operator to do a chunk of work for the tool stores a pointer to the tool and enough info to know which specific operator it should spawn
- L146 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L149 _public member_ `TObjectPtr<URemoveOccludedTrianglesTool> Tool;` — `UPROPERTY()`
- L151 _public member_ `int PreviewIdx;`

#### class `URemoveOccludedTrianglesTool`  
`class URemoveOccludedTrianglesTool : public UMultiSelectionMeshEditingTool`  
_L159-227_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool`
- desc: Simple Mesh Normal Updating Tool
- L167 _public prototype_ `URemoveOccludedTrianglesTool();`
- L169 _public prototype_ `virtual void Setup() override;`
- L170 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L172 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L174 _public function_ `virtual bool HasCancel() const override`
- L175 _public function_ `virtual bool HasAccept() const override`
- L176 _public prototype_ `virtual bool CanAccept() const override;`
- L179 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;`
- L182 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L187 _protected member_ `TObjectPtr<URemoveOccludedTrianglesToolProperties> BasicProperties;` — `UPROPERTY()`
- L190 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayersProperties;` — `UPROPERTY()`
- L193 _protected member_ `TObjectPtr<URemoveOccludedTrianglesAdvancedProperties> AdvancedProperties;` — `UPROPERTY()`
- L196 _protected member_ `TArray<TObjectPtr<UMeshOpPreviewWithBackgroundCompute>> Previews;` — `UPROPERTY()`
- L201 _protected member_ `TArray<TObjectPtr<UPreviewMesh>> PreviewCopies;` — `UPROPERTY()` — When multiple meshes in the selection correspond to the same asset, only one needs a PreviewWithBackgroundCompute all others just get a plain PreviewMesh copy that is updated via OnMeshUpdated broadcast from the source Preview
- L205 _protected member_ `TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>> OriginalDynamicMeshes;`
- L208 _protected member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe>> OccluderTrees;` — AABB trees and winding trees for every mesh target, with repeated instances as pointers to the same data
- L209 _protected member_ `TArray<TSharedPtr<UE::Geometry::TFastWindingTree<FDynamicMesh3>, ESPMode::ThreadSafe>> OccluderWindings;`
- L210 _protected member_ `TArray<UE::Geometry::FTransformSRT3d> OccluderTransforms;`
- L212 _protected member_ `TArray<TArray<int32>> PreviewToCopyIdx;`
- L213 _protected member_ `TArray<int32> PreviewToTargetIdx;`
- L214 _protected member_ `TArray<int32> TargetToPreviewIdx;`
- L217 _protected member_ `TArray<int32> OccludedGroupIDs;` — Group IDs for occluded triangles, per mesh in the Previews array, if OccludedAction is SetNewGroup
- L219 _protected member_ `TArray<int32> OccludedGroupLayers;` — Selected layer indices for Group IDs, per mesh in the Previews array
- L221 _protected member_ `FViewCameraState CameraState;`
- L223 _protected prototype_ `void SetupPreviews();`
- L224 _protected prototype_ `void MakePolygroupLayerProperties();`
- L226 _protected prototype_ `void GenerateAsset(const TArray<FDynamicMeshOpResult>& Results);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L19 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/KelvinletBrushOp.h` (Public)


#### class `UBaseKelvinletBrushOpProps`  
`class UBaseKelvinletBrushOpProps : public UMeshSculptBrushOpProps`  
_L29-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L37 _public member_ `float Stiffness = 1.f;` — `UPROPERTY()` — How much the mesh resists shear
- L41 _public member_ `float Incompressiblity = 1.f;` — `UPROPERTY()` — How compressible the spatial region is: 1 - 2 x Poisson ratio
- L45 _public member_ `int32 BrushSteps = 3;` — `UPROPERTY()` — Integration steps
- L47 _public function_ `virtual float GetStiffness()`
- L48 _public function_ `virtual float GetIncompressiblity()`
- L49 _public function_ `virtual int32 GetNumSteps()`

#### class `FBaseKelvinletBrushOp`  
`class FBaseKelvinletBrushOp : public FMeshSculptBrushOp`  
_L57-184_
- inherits: `FMeshSculptBrushOp`
- L61 _public function_ `void SetBaseProperties(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp)`
- L81 _public function_ `template <typename KelvinletType> void ApplyKelvinlet(const KelvinletType& Kelvinlet, const FFrame3d& LocalFrame, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) const`
- L96 _public function_ `virtual void ApplyStamp(const FDynamicMesh3*SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L100 _protected function_ `void ApplyFalloff(const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) const`
- L121 _protected function_ `template <typename KelvinletType> void DisplaceKelvinlet(const KelvinletType& Kelvinlet, const FFrame3d& LocalFrame, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) const` — NB: this just moves the verts, but doesn't update the normal.  The kelvinlets will have to be extended if we want to do the Jacobian Transpose operation on the normals - but for now, we should just rebuild the normals after the brush
- L144 _protected function_ `template <typename KelvinletType> void IntegrateKelvinlet(const KelvinletType& Kelvinlet, const FFrame3d& LocalFrame, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut, const double Dt, const int32 Steps) const`
- L174 _protected member_ `float Mu;` — physical properties.
- L175 _protected member_ `float Nu;`
- L177 _protected member_ `float Size;` — model regularization parameter
- L180 _protected member_ `int32 NumSteps;` — integration parameters
- L181 _protected member_ `double IntegrationTime = 1.;`
- L183 _protected member_ `const FDynamicMesh3* Mesh;`

#### class `UScaleKelvinletBrushOpProps`  
`class UScaleKelvinletBrushOpProps : public UBaseKelvinletBrushOpProps`  
_L191-208_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseKelvinletBrushOpProps`
- L198 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = KelvinScaleBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10.", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L202 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = KelvinScaleBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L205 _public function_ `virtual float GetStrength() override`
- L206 _public function_ `virtual float GetFalloff() override`
- L207 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FScaleKelvinletBrushOp`  
`class FScaleKelvinletBrushOp : public FBaseKelvinletBrushOp`  
_L210-229_
- inherits: `FBaseKelvinletBrushOp`
- L215 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### class `UPullKelvinletBrushOpProps`  
`class UPullKelvinletBrushOpProps : public UBaseKelvinletBrushOpProps`  
_L232-243_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseKelvinletBrushOpProps`
- L239 _public member_ `float Falloff = 0.1f;` — `UPROPERTY(EditAnywhere, Category = KelvinGrabBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L242 _public function_ `virtual float GetFalloff() override` — these get routed into the Stamp

#### class `FPullKelvinletBrushOp`  
`class FPullKelvinletBrushOp : public FBaseKelvinletBrushOp`  
_L245-278_
- inherits: `FBaseKelvinletBrushOp`
- L250 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L269 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L274 _public function_ `virtual bool IgnoreZeroMovements() const override`

#### class `USharpPullKelvinletBrushOpProps`  
`class USharpPullKelvinletBrushOpProps : public UBaseKelvinletBrushOpProps`  
_L281-292_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseKelvinletBrushOpProps`
- L288 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = KelvinSharpGrabBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L291 _public function_ `virtual float GetFalloff() override` — these get routed into the Stamp

#### class `FSharpPullKelvinletBrushOp`  
`class FSharpPullKelvinletBrushOp : public FBaseKelvinletBrushOp`  
_L294-328_
- inherits: `FBaseKelvinletBrushOp`
- L299 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L318 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L323 _public function_ `virtual bool IgnoreZeroMovements() const override`

#### class `FLaplacianPullKelvinletBrushOp`  
`class FLaplacianPullKelvinletBrushOp : public FBaseKelvinletBrushOp`  
_L330-356_
- inherits: `FBaseKelvinletBrushOp`
- L334 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L347 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L352 _public function_ `virtual bool IgnoreZeroMovements() const override`

#### class `FBiLaplacianPullKelvinletBrushOp`  
`class FBiLaplacianPullKelvinletBrushOp : public FBaseKelvinletBrushOp`  
_L358-385_
- inherits: `FBaseKelvinletBrushOp`
- L362 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L375 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L380 _public function_ `virtual bool IgnoreZeroMovements() const override`

#### class `UTwistKelvinletBrushOpProps`  
`class UTwistKelvinletBrushOpProps : public UBaseKelvinletBrushOpProps`  
_L388-405_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseKelvinletBrushOpProps`
- L395 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = KelvinTwistBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10.", ModelingQuickSettings = 200))` — Twisting strength of the Brush
- L399 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = KelvinTwistBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L402 _public function_ `virtual float GetStrength() override`
- L403 _public function_ `virtual float GetFalloff() override`
- L404 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FTwistKelvinletBrushOp`  
`class FTwistKelvinletBrushOp : public FBaseKelvinletBrushOp`  
_L407-433_
- inherits: `FBaseKelvinletBrushOp`
- L412 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L429 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`

#### class `FPinchKelvinletBrushOp`  
`class FPinchKelvinletBrushOp : public FBaseKelvinletBrushOp`  
_L435-454_
- inherits: `FBaseKelvinletBrushOp`
- L438 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* SrcMesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### enum `EKelvinletBrushMode`  
`enum class EKelvinletBrushMode`  
_L462-473_
- L464 _public enumerator_ `ScaleKelvinlet`
- L465 _public enumerator_ `PinchKelvinlet`
- L466 _public enumerator_ `TwistKelvinlet`
- L467 _public enumerator_ `PullKelvinlet`
- L468 _public enumerator_ `LaplacianPullKelvinlet`
- L469 _public enumerator_ `BiLaplacianPullKelvinlet`
- L470 _public enumerator_ `BiLaplacianTwistPullKelvinlet`
- L471 _public enumerator_ `LaplacianTwistPullKelvinlet`
- L472 _public enumerator_ `SharpPullKelvinlet`

#### class `FKelvinletBrushOp`  
`class FKelvinletBrushOp`  
_L475-746_
- L510 _public function_ `FKelvinletBrushOp(const FDynamicMesh3& DynamicMesh) : Mesh(&DynamicMesh)`
- L514 _public function_ `void ExtractTransform(const FMatrix& WorldToBrush)`
- L543 _public prototype_ `~FKelvinletBrushOp() = default;`
- L546 _public member_ `const FDynamicMesh3* Mesh;`
- L549 _public member_ `double TimeStep = 1.0;`
- L550 _public member_ `double NumSteps = 0.0;`
- L554 _public member_ `FMatrix3d WorldToBrushMat;` — To be applied as WorlToBrushMat * v + Trans Note: could use FTransform3d in TransformTypes.h
- L555 _public member_ `FMatrix3d BrushToWorldMat;`
- L556 _public member_ `FVector3d Translation;`
- L562 _public function_ `void ApplyBrush(const FKelvinletBrushOpProperties& Properties, const FMatrix& WorldToBrush, const TArray<int>& VertRIO, TArray<FVector3d>& ROIPositionBuffer)`
- L668 _public function_ `template <typename KelvinletType> void DisplaceKelvinlet(const KelvinletType& Kelvinlet, const TArray<int>& VertexROI, TArray<FVector3d>& ROIPositionBuffer)` — NB: this just moves the verts, but doesn't update the normal.  The kelvinlets will have to be extended if we want to do the Jacobian Transpose operation on the normals - but for now, we should just rebuild the normals after the brush
- L692 _public function_ `template <typename KelvinletType> void IntegrateKelvinlet(const KelvinletType& Kelvinlet, const TArray<int>& VertexROI, TArray<FVector3d>& ROIPositionBuffer, const double Dt, const int Steps)`
- L719 _public function_ `template <typename KelvinletType> void ApplyKelvinlet(const KelvinletType& Kelvinlet, const TArray<int>& VertexROI, TArray<FVector3d>& ROIPositionBuffer, const double Dt, const int NumIntegrationSteps)`
- L735 _private function_ `FVector3d XForm(const FVector3d& Pos) const` — apply the transform.
- L741 _private function_ `FVector3d InvXForm(const FVector3d& Pos) const` — apply the inverse transform.

#### struct `FKelvinletBrushOp::FKelvinletBrushOpProperties`  
`struct FKelvinletBrushOpProperties`  
_L480-508_
- L482 _public function_ `FKelvinletBrushOpProperties(const EKelvinletBrushMode& BrushMode, const UKelvinBrushProperties& Properties, double BrushRadius, double BrushFalloff) : Mode(BrushMode) , Direction(1.0, 0.0, 0.0)`
- L495 _public member_ `EKelvinletBrushMode Mode;`
- L496 _public member_ `FVector Direction;`
- L498 _public member_ `double Speed;` — Optionally used
- L499 _public member_ `double FallOff;` — Optionally used
- L500 _public member_ `double Mu;` — Shear Modulus
- L501 _public member_ `double Nu;` — Poisson ratio
- L504 _public member_ `double Size;` — regularization parameter
- L506 _public member_ `int NumSteps;`

#### Free symbols / members of external scopes

- L105 _function_ `` (scope `FBaseKelvinletBrushOp::ApplyFalloff`)
- L129 _function_ `` (scope `FBaseKelvinletBrushOp::DisplaceKelvinlet`)
- L152 _function_ `` (scope `FBaseKelvinletBrushOp::IntegrateKelvinlet`)
- L677 _function_ `` (scope `FKelvinletBrushOp::DisplaceKelvinlet`)
- L700 _function_ `` (scope `FKelvinletBrushOp::IntegrateKelvinlet`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshBrushOpBase.h` (Public)


#### enum `ESculptBrushOpTargetType`  
`enum class ESculptBrushOpTargetType : uint8`  
_L15-22_
- L18 _public enumerator_ `SculptMesh` — The "live" mesh that is updated by each stamp
- L20 _public enumerator_ `TargetMesh` — The "base" mesh that is typically updated after every stroke
- L21 _public enumerator_ `ActivePlane`

#### enum `EPlaneBrushSideMode`  
`enum class EPlaneBrushSideMode : uint8`  
_L26-31_
- reflection: `UENUM()`
- L28 _public enumerator_ `BothSides = 0`
- L29 _public enumerator_ `PushDown = 1`
- L30 _public enumerator_ `PullTowards = 2`

#### struct `FSculptBrushStamp`  
`struct FSculptBrushStamp`  
_L34-61_
- L36 _public member_ `FFrame3d WorldFrame;`
- L37 _public member_ `FFrame3d LocalFrame;`
- L38 _public member_ `double Radius;`
- L39 _public member_ `double Falloff;`
- L40 _public member_ `double Power;`
- L41 _public member_ `double Direction;`
- L42 _public member_ `double Depth;`
- L43 _public member_ `double DeltaTime;`
- L45 _public member_ `FFrame3d PrevWorldFrame;`
- L46 _public member_ `FFrame3d PrevLocalFrame;`
- L48 _public member_ `FDateTime TimeStamp;`
- L51 _public member_ `FFrame3d RegionPlane;` — only initialized if current op requires it
- L54 _public member_ `TFunction<double(const FSculptBrushStamp& Stamp, const FVector3d& Position)> StampAlphaFunc;` — stamp alpha
- L55 _public function_ `bool HasAlpha() const`
- L57 _public function_ `FSculptBrushStamp()`

#### struct `FSculptBrushOptions`  
`struct FSculptBrushOptions`  
_L64-69_
- L68 _public member_ `FFrame3d ConstantReferencePlane;`

#### class `FMeshSculptFallofFunc`  
`class FMeshSculptFallofFunc`  
_L72-81_
- L75 _public member_ `TUniqueFunction<double(const FSculptBrushStamp& StampInfo, const FVector3d& Position)> FalloffFunc;`
- L77 _public function_ `inline double Evaluate(const FSculptBrushStamp& StampInfo, const FVector3d& Position) const`

#### class `UMeshSculptBrushOpProps`  
`class UMeshSculptBrushOpProps : public UInteractiveToolPropertySet`  
_L86-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L91 _public function_ `virtual float GetStrength()`
- L92 _public function_ `virtual float GetDepth()`
- L93 _public function_ `virtual float GetFalloff()`
- L96 _public function_ `virtual void SetStrength(float NewStrength)` — support for this is optional, used by UI level to edit brush props via hotkeys/etc
- L97 _public function_ `virtual void SetFalloff(float NewFalloff)`
- L100 _public function_ `virtual bool GetStrengthPressureEnabled()` — is Pressure Sensitivity for Brush Strength currently toggled on?
- L103 _public function_ `virtual bool SupportsStrengthPressure()` — is Pressure Sensitivity for Brush Strength supported?
- L107 _public member_ `bool bIsStrengthPressureEnabled = true;` — `UPROPERTY(EditAnywhere, Category = BrushOp)` — Should pressure affect brush strength?

#### enum `EMeshSculptStrokeType`  
`enum class EMeshSculptStrokeType : uint8`  
_L112-122_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Stroke Types
- L115 _public enumerator_ `Spacing = 0` — Brushes stamp at regular distance intervals as the stroke is drawn
- L117 _public enumerator_ `Airbrush = 1` — Brushes stamp at regular time intervals as the stroke is drawn
- L119 _public enumerator_ `Dots = 2` — Brushes stamp once per frame as the stroke is drawn.
- L121 _public enumerator_ `LastValue UMETA(Hidden)`

#### class `FMeshSculptBrushOp`  
`class FMeshSculptBrushOp`  
_L124-321_
- L187 _public prototype_ `virtual ~FMeshSculptBrushOp() = default;`
- L189 _public member_ `TWeakObjectPtr<UMeshSculptBrushOpProps> PropertySet;`
- L192 _public function_ `template<typename PropType> PropType* GetPropertySetAs()`
- L201 _public function_ `template<typename PropType> const PropType* GetPropertySetAs() const`
- L210 _public member_ `TSharedPtr<FMeshSculptFallofFunc> Falloff;`
- L211 _public member_ `FSculptBrushOptions CurrentOptions;`
- L213 _public function_ `const FMeshSculptFallofFunc& GetFalloff() const`
- L215 _public function_ `virtual void ConfigureOptions(const FSculptBrushOptions& Options)`
- L220 _public function_ `virtual void BeginStroke(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& InitialVertices)`
- L221 _public function_ `virtual void EndStroke(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& FinalVertices)`
- L222 _public function_ `virtual void CancelStroke()`
- L223 _public prototype_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewValuesOut) = 0;`
- L231 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const`
- L237 _public function_ `virtual EBrushRegionType GetBrushRegionType() const` — Determines what region of a mesh a brush wants to affect
- L243 _public function_ `virtual EStampAlignmentType GetStampAlignmentType() const` — Determines how the brush expects its local frame to be aligned as the mouse is moved
- L253 _public function_ `virtual bool GetAlignStampToView() const`
- L258 _public function_ `virtual bool IgnoreZeroMovements() const`
- L268 _public function_ `virtual bool UseLastStampFrameOnZeroMovement() const` — If this is true and there is no mouse movement, the stamp will be applied with the same Local/World frames as the previous application. Irrelevant if IgnoreZeroMovements() returns true, since in that case the stamp requires mouse movement to be applied. Useful for height brushes which change the mesh (and therefore the hit location) but want to continue being applied in the same vertical region while the mouse is not moved.
- L275 _public function_ `virtual EReferencePlaneType GetReferencePlaneType() const` — Determines what kind of plane (if any) the brush wants to be stored at the start of the stroke in CurrentOptions.ConstantReferencePlane.
- L282 _public function_ `virtual bool WantsStampRegionPlane() const` — Whether the brush wants an average plane to be computed at each stamp application out of the affected triangles (accessed through Stamp.RegionPlane)
- L287 _public function_ `virtual bool UsesAlpha() const`
- L293 _public function_ `virtual bool SupportsVariableSpacing() const` — `UE_DEPRECATED(5.7, "Deprecated in favor of SupportsStrokeType to provide more fine grained description of what strokes brushes support.")`
- L298 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const`
- L312 _public function_ `virtual EROIUpdateType GetROIUpdateType() const`
- L317 _public function_ `virtual EStampInputMeshType GetStampInputMeshType() const`

#### enum `FMeshSculptBrushOp::EBrushRegionType`  
`enum class EBrushRegionType`  
_L128-138_
- desc: Determines what region of a mesh a brush wants to affect
- L131 _public enumerator_ `LocalSphere` — Affect a sphere around the current brush location
- L134 _public enumerator_ `InfiniteCylinder` — Affect a cylinder centered at current brush location and extending infinitely upwards and downwards (based on local frame)
- L137 _public enumerator_ `CylinderOnSphere` — Affect a cylinder whose axis starts at a reference sphere center, passes through the brush position, and extends further away from the sphere.

#### enum `FMeshSculptBrushOp::EStampAlignmentType`  
`enum class EStampAlignmentType`  
_L141-151_
- desc: Determines how the brush expects its local frame to be aligned as the mouse is moved
- L144 _public enumerator_ `HitNormal` — Align brush to the hit normal
- L146 _public enumerator_ `Camera` — Align brush to have its local plane face the camera
- L148 _public enumerator_ `ReferencePlane` — Align brush such that its local plane is parallel to a reference plane
- L150 _public enumerator_ `ReferenceSphere` — Align brush such that its local plane normal points away from a reference sphere center

#### enum `FMeshSculptBrushOp::EReferencePlaneType`  
`enum class EReferencePlaneType`  
_L155-167_
- desc: Determines what kind of reference plane the brush wants to use (which will be accessed via CurrentOptions.ConstantReferencePlane)
- L158 _public enumerator_ `None` — Reference plane is not used
- L161 _public enumerator_ `InitialROI` — The reference plane is expected to have been caluclated using triangles in the region of interest affected by the brush at its initial application (at start of stroke)
- L164 _public enumerator_ `InitialROI_ViewAligned` — Like InitialROI, but the plane normal is aligned to camera direction, so only the centroid is calculated from the region of interest.
- L166 _public enumerator_ `WorkPlane` — The brush expects custom "work" plane (typically set via gizmo)

#### enum `FMeshSculptBrushOp::EROIUpdateType`  
`enum class EROIUpdateType`  
_L170-176_
- desc: Determines which vertices should be moved by the stroke
- L173 _public enumerator_ `UseInitial` — ROI is initialized from the first stamp and remains constant
- L175 _public enumerator_ `UpdatePerStamp` — ROI grows as new stamps overlap with more vertices

#### enum `FMeshSculptBrushOp::EStampInputMeshType`  
`enum class EStampInputMeshType`  
_L179-185_
- desc: Determines which mesh should be used by ApplyStamp
- L182 _public enumerator_ `SculptMesh` — The "live" mesh that is updated by each stamp
- L184 _public enumerator_ `BaseMesh` — The "base" mesh that is typically updated after every stroke

#### class `FMeshSculptBrushOpFactory`  
`class FMeshSculptBrushOpFactory`  
_L326-331_
- L329 _public prototype_ `virtual ~FMeshSculptBrushOpFactory() = default;`
- L330 _public prototype_ `virtual TUniquePtr<FMeshSculptBrushOp> Build() = 0;`

#### class `TBasicMeshSculptBrushOpFactory`  
`template<typename OpType> class TBasicMeshSculptBrushOpFactory : public FMeshSculptBrushOpFactory`  
_L334-341_
- inherits: `FMeshSculptBrushOpFactory`
- L337 _public function_ `virtual TUniquePtr<FMeshSculptBrushOp> Build() override`

#### class `FLambdaMeshSculptBrushOpFactory`  
`class FLambdaMeshSculptBrushOpFactory : public FMeshSculptBrushOpFactory`  
_L344-362_
- inherits: `FMeshSculptBrushOpFactory`
- L347 _public member_ `TUniqueFunction<TUniquePtr<FMeshSculptBrushOp>(void)> BuildFunc;`
- L349 _public function_ `FLambdaMeshSculptBrushOpFactory()`
- L353 _public function_ `FLambdaMeshSculptBrushOpFactory(TUniqueFunction<TUniquePtr<FMeshSculptBrushOp>(void)> BuildFuncIn)`
- L358 _public function_ `virtual TUniquePtr<FMeshSculptBrushOp> Build() override`

#### Free symbols / members of external scopes

- L11 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshEraseSculptLayerBrushOps.h` (Public)


#### class `UEraseSculptLayerBrushOpProps`  
`class UEraseSculptLayerBrushOpProps : public UMeshSculptBrushOpProps`  
_L13-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L20 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = EraseSculptLayerBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10.", ModelingQuickSettings = 200))` — Strength of the Brush
- L24 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = EraseSculptLayerBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L27 _public function_ `virtual float GetStrength() override`
- L28 _public function_ `virtual float GetFalloff() override`
- L29 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FEraseSculptLayerBrushOp`  
`class FEraseSculptLayerBrushOp : public FMeshSculptBrushOp`  
_L33-98_
- inherits: `FMeshSculptBrushOp`
- L37 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L88 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L94 _public function_ `virtual bool IgnoreZeroMovements() const`

#### Free symbols / members of external scopes

- L57 _function_ `` (scope `FEraseSculptLayerBrushOp::ApplyStamp`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshGroupPaintBrushOps.h` (Public)


#### class `FMeshTriangleGroupEditBrushOp`  
`class FMeshTriangleGroupEditBrushOp : public FMeshSculptBrushOp`  
_L14-35_
- inherits: `FMeshSculptBrushOp`
- L19 _public function_ `virtual void ApplyStamp( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewColorsOut) override` — not supported for this kind of brush op
- L29 _public prototype_ `virtual void ApplyStampByTriangles( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Triangles, TArray<int32>& NewGroupsOut) = 0;`

#### class `UGroupEraseBrushOpProps`  
`class UGroupEraseBrushOpProps : public UMeshSculptBrushOpProps`  
_L43-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L49 _public member_ `int32 Group = 0;` — `UPROPERTY(EditAnywhere, Category = EraseBrush, meta = (DisplayName = "Erase Group", UIMin = 1))` — Group to set as Erased value
- L53 _public member_ `bool bOnlyEraseCurrent = false;` — `UPROPERTY(EditAnywhere, Category = EraseBrush, meta = (DisplayName = "Only Current"))` — When enabled, only the current group configured in the Paint brush is erased
- L55 _public function_ `virtual int32 GetGroup()`
- L58 _public function_ `TUniqueFunction<int32()> GetCurrentGroupLambda = []()` — this lambda defines the "current" group for bOnlyEraseCurrent mode
- L58 _public member_ `TUniqueFunction<int32()> GetCurrentGroupLambda = []() { return -1; };` — this lambda defines the "current" group for bOnlyEraseCurrent mode

#### class `FGroupEraseBrushOp`  
`class FGroupEraseBrushOp : public FMeshTriangleGroupEditBrushOp`  
_L63-95_
- inherits: `FMeshTriangleGroupEditBrushOp`
- L67 _public function_ `virtual void ApplyStampByTriangles( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Triangles, TArray<int32>& NewGroupsOut) override`

#### class `UGroupPaintBrushOpProps`  
`class UGroupPaintBrushOpProps : public UMeshSculptBrushOpProps`  
_L101-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L107 _public member_ `int32 Group = 1;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Group", UIMin = 0))` — The group that will be assigned to triangles within the brush region
- L111 _public member_ `bool bOnlyPaintUngrouped = false;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Only Ungrouped"))` — If true, only triangles with no group assigned will be painted
- L113 _public function_ `virtual int32 GetGroup()`

#### class `FGroupPaintBrushOp`  
`class FGroupPaintBrushOp : public FMeshTriangleGroupEditBrushOp`  
_L118-149_
- inherits: `FMeshTriangleGroupEditBrushOp`
- L122 _public function_ `virtual void ApplyStampByTriangles( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Triangles, TArray<int32>& NewGroupsOut) override`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshInflateBrushOps.h` (Public)


#### class `UInflateBrushOpProps`  
`class UInflateBrushOpProps : public UMeshSculptBrushOpProps`  
_L14-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L20 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = InflateBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L24 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = InflateBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L26 _public function_ `virtual float GetStrength() override`
- L27 _public function_ `virtual void SetStrength(float NewStrength) override`
- L28 _public function_ `virtual float GetFalloff() override`
- L29 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FInflateBrushOp`  
`class FInflateBrushOp : public FMeshSculptBrushOp`  
_L34-65_
- inherits: `FMeshSculptBrushOp`
- desc: Like FSurfaceSculptBrushOp (moves vertices along individual vertex normals), but operates on the sculpt mesh (i.e. the live mesh) instead of the pre-stroke mesh.
- L38 _public member_ `double BrushSpeedTuning = 2.0;`
- L40 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L45 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### Free symbols / members of external scopes

- L52 _function_ `` (scope `FInflateBrushOp::ApplyStamp`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshMoveBrushOps.h` (Public)


#### class `UMoveBrushOpProps`  
`class UMoveBrushOpProps : public UMeshSculptBrushOpProps`  
_L16-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L22 _public member_ `float Strength = 1.0;` — `UPROPERTY(EditAnywhere, Category = MoveBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L26 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = MoveBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L28 _public function_ `virtual float GetStrength() override`
- L29 _public function_ `virtual void SetStrength(float NewStrength) override`
- L30 _public function_ `virtual float GetFalloff() override`
- L31 _public function_ `virtual bool SupportsStrengthPressure() override`
- L35 _public member_ `FModelingToolsAxisFilter AxisFilters;` — `UPROPERTY(EditAnywhere, Category = MoveBrush)` — Axis filters restrict mesh movement to World X/Y/Z axes

#### class `FMoveBrushOp`  
`class FMoveBrushOp : public FMeshSculptBrushOp`  
_L39-101_
- inherits: `FMeshSculptBrushOp`
- L42 _private member_ `FSculptBrushStamp FirstStamp;`
- L46 _public function_ `virtual void BeginStroke(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& InitialVertices) override`
- L51 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L82 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L87 _public function_ `virtual bool IgnoreZeroMovements() const override`
- L92 _public function_ `virtual EROIUpdateType GetROIUpdateType() const override`
- L97 _public function_ `virtual EStampInputMeshType GetStampInputMeshType() const override`

#### Free symbols / members of external scopes

- L70 _function_ `` (scope `FMoveBrushOp::ApplyStamp`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshPinchBrushOps.h` (Public)


#### class `UPinchBrushOpProps`  
`class UPinchBrushOpProps : public UMeshSculptBrushOpProps`  
_L13-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L19 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PinchBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L23 _public member_ `float Falloff = 0.75;` — `UPROPERTY(EditAnywhere, Category = PinchBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L27 _public member_ `float Depth = 0;` — `UPROPERTY(EditAnywhere, Category = PinchBrush, meta = (UIMin = "-0.5", UIMax = "0.5", ClampMin = "-1.0", ClampMax = "1.0"))` — Depth of Brush into surface along surface normal
- L31 _public member_ `bool bPerpDamping = true;` — `UPROPERTY(EditAnywhere, Category = PinchBrush)` — When enabled, brush will damp motion of vertices that would move perpendicular to brush stroke direction
- L33 _public function_ `virtual float GetStrength() override`
- L34 _public function_ `virtual void SetStrength(float NewStrength) override`
- L35 _public function_ `virtual float GetFalloff() override`
- L36 _public function_ `virtual float GetDepth() override`
- L37 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FPinchBrushOp`  
`class FPinchBrushOp : public FMeshSculptBrushOp`  
_L41-108_
- inherits: `FMeshSculptBrushOp`
- L45 _public member_ `double BrushSpeedTuning = 3.0;`
- L47 _public member_ `FVector3d LastSmoothBrushPosLocal;`
- L48 _public member_ `FVector3d LastSmoothBrushNormalLocal;`
- L50 _public function_ `virtual void BeginStroke(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& InitialVertices)`
- L57 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L104 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const`

#### Free symbols / members of external scopes

- L77 _function_ `` (scope `FPinchBrushOp::ApplyStamp`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshPlaneBrushOps.h` (Public)


#### class `UBasePlaneBrushOpProps`  
`class UBasePlaneBrushOpProps : public UMeshSculptBrushOpProps`  
_L15-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L19 _public function_ `virtual EPlaneBrushSideMode GetWhichSide()`
- L20 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `UPlaneBrushOpProps`  
`class UPlaneBrushOpProps : public UBasePlaneBrushOpProps`  
_L24-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasePlaneBrushOpProps`
- L30 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PlaneBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L34 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = PlaneBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L38 _public member_ `float Depth = 0;` — `UPROPERTY(EditAnywhere, Category = PlaneBrush, meta = (UIMin = "-0.5", UIMax = "0.5", ClampMin = "-1.0", ClampMax = "1.0"))` — Depth of Brush into surface along surface normal
- L42 _public member_ `EPlaneBrushSideMode WhichSide = EPlaneBrushSideMode::BothSides;` — `UPROPERTY(EditAnywhere, Category = PlaneBrush)` — Control whether effect of brush should be limited to one side of the Plane
- L44 _public function_ `virtual float GetStrength() override`
- L45 _public function_ `virtual void SetStrength(float NewStrength) override`
- L46 _public function_ `virtual float GetFalloff() override`
- L47 _public function_ `virtual float GetDepth() override`
- L48 _public function_ `virtual EPlaneBrushSideMode GetWhichSide()`

#### class `UViewAlignedPlaneBrushOpProps`  
`class UViewAlignedPlaneBrushOpProps : public UBasePlaneBrushOpProps`  
_L53-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasePlaneBrushOpProps`
- L59 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = ViewPlaneBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L63 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = ViewPlaneBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L67 _public member_ `float Depth = 0;` — `UPROPERTY(EditAnywhere, Category = ViewPlaneBrush, meta = (UIMin = "-0.5", UIMax = "0.5", ClampMin = "-1.0", ClampMax = "1.0"))` — Depth of Brush into surface along view ray
- L71 _public member_ `EPlaneBrushSideMode WhichSide = EPlaneBrushSideMode::BothSides;` — `UPROPERTY(EditAnywhere, Category = ViewPlaneBrush)` — Control whether effect of brush should be limited to one side of the Plane
- L73 _public function_ `virtual float GetStrength() override`
- L74 _public function_ `virtual void SetStrength(float NewStrength) override`
- L75 _public function_ `virtual float GetFalloff() override`
- L76 _public function_ `virtual float GetDepth() override`
- L77 _public function_ `virtual EPlaneBrushSideMode GetWhichSide()`

#### class `UFixedPlaneBrushOpProps`  
`class UFixedPlaneBrushOpProps : public UBasePlaneBrushOpProps`  
_L82-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasePlaneBrushOpProps`
- L88 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = FixedPlaneBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L92 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = FixedPlaneBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L96 _public member_ `EPlaneBrushSideMode WhichSide = EPlaneBrushSideMode::BothSides;` — `UPROPERTY(EditAnywhere, Category = FixedPlaneBrush)` — Control whether effect of brush should be limited to one side of the Plane
- L98 _public function_ `virtual float GetStrength() override`
- L99 _public function_ `virtual void SetStrength(float NewStrength) override`
- L100 _public function_ `virtual float GetFalloff() override`
- L101 _public function_ `virtual EPlaneBrushSideMode GetWhichSide()`

#### class `FPlaneBrushOp`  
`class FPlaneBrushOp : public FMeshSculptBrushOp`  
_L106-176_
- inherits: `FMeshSculptBrushOp`
- L110 _public member_ `double BrushSpeedTuning = 6.0;`
- L112 _public member_ `FFrame3d StrokePlane;`
- L114 _public function_ `virtual EReferencePlaneType GetReferencePlaneType() const`
- L139 _public function_ `virtual void BeginStroke(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& InitialVertices) override`
- L144 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### Free symbols / members of external scopes

- L155 _function_ `` (scope `FPlaneBrushOp::ApplyStamp`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshSculptBrushOps.h` (Public)


#### class `UStandardSculptBrushOpProps`  
`class UStandardSculptBrushOpProps : public UMeshSculptBrushOpProps`  
_L14-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L20 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = SculptBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L24 _public member_ `float Falloff = 1.0;` — `UPROPERTY(EditAnywhere, Category = SculptBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L26 _public function_ `virtual float GetStrength() override`
- L27 _public function_ `virtual void SetStrength(float NewStrength) override`
- L28 _public function_ `virtual float GetFalloff() override`
- L29 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `UE::Geometry::FSingleNormalSculptBrushOp`  
`class FSingleNormalSculptBrushOp : public FMeshSculptBrushOp`  
_L36-89_
- inherits: `FMeshSculptBrushOp`
- desc: Brush that sculpts all vertices in one direction, set by the normal at the brush position. Operates on pre-stroke mesh.
- L39 _public member_ `double BrushSpeedTuning = 6.0;`
- L41 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L46 _public function_ `virtual bool SupportsVariableSpacing() const override`
- L51 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const override`
- L64 _public function_ `virtual bool UsesAlpha() const override`
- L69 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### class `FSurfaceSculptBrushOp`  
`class FSurfaceSculptBrushOp : public FMeshSculptBrushOp`  
_L95-165_
- inherits: `FMeshSculptBrushOp`
- desc: Uses the vertex normal at the "base" mesh (i.e. pre-stroke mesh) vertex to move vertices. Basically just like the inflate brush, but using the pre-stroke mesh.
- L98 _public member_ `double BrushSpeedTuning = 6.0;`
- L100 _public typedef_ `typedef TUniqueFunction<bool(int32, const FVector3d&, double, FVector3d&, FVector3d&)> NearestQueryFuncType;`
- L102 _public member_ `NearestQueryFuncType BaseMeshNearestQueryFunc;`
- L104 _public function_ `FSurfaceSculptBrushOp(NearestQueryFuncType QueryFunc)`
- L109 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L113 _public function_ `virtual bool SupportsVariableSpacing() const override`
- L118 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const override`
- L131 _public function_ `virtual bool UsesAlpha() const override`
- L136 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### class `UViewAlignedSculptBrushOpProps`  
`class UViewAlignedSculptBrushOpProps : public UMeshSculptBrushOpProps`  
_L172-188_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L178 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = SculptToViewBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L182 _public member_ `float Falloff = 1.0;` — `UPROPERTY(EditAnywhere, Category = SculptToViewBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L184 _public function_ `virtual float GetStrength() override`
- L185 _public function_ `virtual void SetStrength(float NewStrength) override`
- L186 _public function_ `virtual float GetFalloff() override`
- L187 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FViewAlignedSculptBrushOp`  
`class FViewAlignedSculptBrushOp : public FMeshSculptBrushOp`  
_L193-268_
- inherits: `FMeshSculptBrushOp`
- desc: Starts with the base mesh, and moves all vertices towards the camera (by asking the owning tool to align the stamp normal to view, and using that value).
- L196 _public member_ `double BrushSpeedTuning = 6.0;`
- L198 _public typedef_ `typedef TUniqueFunction<bool(int32, const FVector3d&, double, FVector3d&, FVector3d&)> NearestQueryFuncType;`
- L200 _public member_ `NearestQueryFuncType BaseMeshNearestQueryFunc;`
- L202 _public function_ `FViewAlignedSculptBrushOp(NearestQueryFuncType QueryFunc)`
- L207 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L212 _public function_ `virtual bool GetAlignStampToView() const override`
- L216 _public function_ `virtual bool SupportsVariableSpacing() const override`
- L220 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const override`
- L232 _public function_ `virtual bool UsesAlpha() const override`
- L237 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### class `USculptMaxBrushOpProps`  
`class USculptMaxBrushOpProps : public UMeshSculptBrushOpProps`  
_L275-304_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L281 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = SculptMaxBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L285 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = SculptMaxBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L289 _public member_ `float MaxHeight = 0.5;` — `UPROPERTY(EditAnywhere, Category = SculptMaxBrush, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Maximum height as fraction of brush size
- L293 _public member_ `bool bUseFixedHeight = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = SculptMaxBrush)` — If true, maximum height is defined using the FixedHeight constant instead of brush-relative size
- L297 _public member_ `float FixedHeight = 0.0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = SculptMaxBrush)` — Maximum height in world-space dimension
- L300 _public function_ `virtual float GetStrength() override`
- L301 _public function_ `virtual void SetStrength(float NewStrength) override`
- L302 _public function_ `virtual float GetFalloff() override`
- L303 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `UE::Geometry::FSingleNormalMaxSculptBrushOp`  
`class FSingleNormalMaxSculptBrushOp : public FSingleNormalSculptBrushOp`  
_L310-363_
- inherits: `FSingleNormalSculptBrushOp`
- desc: Brush that sculpts all vertices in one direction, set by the normal at the brush position, and capped by a max value. Operates on pre-stroke mesh.
- L313 _public typedef_ `typedef TUniqueFunction<bool(int32, const FVector3d&, double, FVector3d&, FVector3d&)> NearestQueryFuncType;`
- L316 _public member_ `NearestQueryFuncType BaseMeshNearestQueryFunc;` — To cap the movement distance, we need to know the original position on the pre-sculpt mesh
- L318 _public function_ `FSingleNormalMaxSculptBrushOp(NearestQueryFuncType QueryFunc)`
- L323 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### class `FSurfaceMaxSculptBrushOp`  
`class FSurfaceMaxSculptBrushOp : public FMeshSculptBrushOp`  
_L369-448_
- inherits: `FMeshSculptBrushOp`
- desc: Like FSurfaceSculptBrushOp, but caps the movement to some maximum distance. In other words, it is an inflate (movement along individual vertex normals) based off of base (i.e. pre-stroke) mesh normals, but capped in offset distance from the pre-stroke mesh.
- L372 _public member_ `double BrushSpeedTuning = 6.0;`
- L374 _public typedef_ `typedef TUniqueFunction<bool(int32, const FVector3d&, double, FVector3d&, FVector3d&)> NearestQueryFuncType;`
- L376 _public member_ `NearestQueryFuncType BaseMeshNearestQueryFunc;`
- L378 _public function_ `FSurfaceMaxSculptBrushOp(NearestQueryFuncType QueryFunc)`
- L383 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L387 _public function_ `virtual bool SupportsVariableSpacing() const override`
- L391 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const override`
- L403 _public function_ `virtual bool UsesAlpha() const override`
- L408 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Geometry` (scope `UE`)
- L77 _function_ `` (scope `UE::Geometry::FSingleNormalSculptBrushOp::ApplyStamp`)
- L143 _function_ `` (scope `FSurfaceSculptBrushOp::ApplyStamp`)
- L246 _function_ `` (scope `FViewAlignedSculptBrushOp::ApplyStamp`)
- L306 _namespace_ `namespace UE`
- L306 _namespace_ `namespace Geometry` (scope `UE`)
- L334 _function_ `` (scope `UE::Geometry::FSingleNormalMaxSculptBrushOp::ApplyStamp`)
- L418 _function_ `` (scope `FSurfaceMaxSculptBrushOp::ApplyStamp`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshSculptToolBase.h` (Public)


#### enum `EBrushToolSizeType`  
`enum class EBrushToolSizeType : uint8`  
_L30-36_
- reflection: `UENUM()`
- desc: Type of Brush Size currently active in FBrushToolRadius
- L33 _public enumerator_ `Adaptive = 0` — Brush size is a dimensionless scale relative to the target object size
- L35 _public enumerator_ `World = 1` — Brush size is defined in world dimensions

#### struct `FBrushToolRadius`  
`struct FBrushToolRadius`  
_L43-84_
- reflection: `USTRUCT()`
- desc: FBrushToolRadius is used to define the size of 3D "brushes" used in (eg) sculpting tools. The brush size can be defined in various ways.
- L49 _public member_ `EBrushToolSizeType SizeType = EBrushToolSizeType::Adaptive;` — `UPROPERTY(EditAnywhere, Category = Brush)` — Specify the type of brush size currently in use
- L54 _public member_ `float AdaptiveSize = 0.25;` — `UPROPERTY(EditAnywhere, Category = Brush, AdvancedDisplay, meta = (EditCondition = "SizeType == EBrushToolSizeType::Adaptive", DisplayName = "Size", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0"))` — Adaptive brush size is used to interpolate between an object-specific minimum and maximum brush size
- L59 _public member_ `float WorldRadius = 100.0;` — `UPROPERTY(EditAnywhere, Category = Brush, AdvancedDisplay, meta = (EditCondition = "SizeType == EBrushToolSizeType::World", DisplayName = "World Radius", UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.1", ClampMax = "50000.0"))` — World brush size is a dimension in world coordinates
- L62 _public member_ `bool bToolSupportsPressureSensitivity = false;` — `UPROPERTY(EditAnywhere, Category = Brush)`
- L65 _public member_ `bool bEnablePressureSensitivity = false;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (EditCondition = "bToolSupportsPressureSensitivity"))`
- L70 _public member_ `TInterval<float> WorldSizeRange = TInterval<float>(1.0f, 1000.0f);` — WorldSizeRange defines the min/max dimensions for Adaptive brush size
- L77 _public prototype_ `void InitializeWorldSizeRange(TInterval<float> Range, bool bValidateWorldRadius = true);` — Set the WorldSizeRange value and optionally clamp the WorldRadius based on this new range
- L79 _public prototype_ `float GetWorldRadius() const;` — Return the set/calculated world-space radius for the current settings
- L81 _public prototype_ `void IncreaseRadius(bool bSmallStep);` — Increase the current radius dimension by a fixed step (or a smaller fixed step)
- L83 _public prototype_ `void DecreaseRadius(bool bSmallStep);` — Decrease the current radius dimension by a fixed step (or a smaller fixed step)

#### enum `EMeshSculptFalloffType`  
`enum class EMeshSculptFalloffType : uint8`  
_L89-101_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L91 _public enumerator_ `Smooth = 0`
- L92 _public enumerator_ `Linear = 1`
- L93 _public enumerator_ `Inverse = 2`
- L94 _public enumerator_ `Round = 3`
- L95 _public enumerator_ `BoxSmooth = 4`
- L96 _public enumerator_ `BoxLinear = 5`
- L97 _public enumerator_ `BoxInverse = 6`
- L98 _public enumerator_ `BoxRound = 7`
- L100 _public enumerator_ `LastValue UMETA(Hidden)`

#### class `USculptBrushProperties`  
`class USculptBrushProperties : public UInteractiveToolPropertySet`  
_L105-166_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L111 _public member_ `EMeshSculptStrokeType StrokeType = EMeshSculptStrokeType::Spacing;` — `UPROPERTY(EditAnywhere, Category = Stroke)`
- L114 _public member_ `FBrushToolRadius BrushSize;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayPriority = 1, ModelingQuickEdit, ModelingQuickSettings = 100))`
- L118 _public member_ `float BrushFalloffAmount;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", HideEditConditionToggle, EditConditionHides, EditCondition="bShowFalloff", DisplayPriority = 3))` — Amount of falloff to apply (0.0 - 1.0)
- L122 _public member_ `bool bShowFalloff = true;` — `UPROPERTY(meta = (TransientToolProperty))` — If false, then BrushFalloffAmount will not be shown in DetailsView panels (otherwise no effect)
- L126 _public member_ `float Depth = 0;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = "-0.5", UIMax = "0.5", ClampMin = "-1.0", ClampMax = "1.0", DisplayPriority = 5, HideEditConditionToggle, EditConditionHides, EditCondition = "bShowPerBrushProps"))` — Depth of Brush into surface along view ray or surface normal, depending on the Active Brush Type
- L130 _public member_ `bool bHitBackFaces = true;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayPriority = 6))` — Allow the Brush to hit the back-side of the mesh
- L134 _public member_ `float FlowRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Flow", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", DisplayPriority = 7, HideEditConditionToggle, EditConditionHides, EditCondition = "bShowFlowRate && StrokeType == EMeshSculptStrokeType::Airbrush"))` — Brush stamps are applied at this time interval. 0 for a single stamp, 1 for continuous stamps, 0.5 is a stamp every half-second
- L140 _public member_ `float RayDensity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Brush, AdvancedDisplay, meta = (UIMin = "0.0", UIMax = "2.0", ClampMin = "0.0", ClampMax = "10.0", DisplayPriority = 8, HideEditConditionToggle, EditConditionHides, EditCondition = "bShowSpacing && StrokeType == EMeshSculptStrokeType::Spacing"))` — When moving the mouse quickly in Spacing mode, determines how initial rays are upsampled before being filtered by StampSpacing.
- L146 _public member_ `float Spacing = .05f;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1000.0", DisplayPriority = 8, DisplayName = "Stamp Spacing", HideEditConditionToggle, EditConditionHides, EditCondition = "bShowSpacing && StrokeType == EMeshSculptStrokeType::Spacing"))` — Space out stamp centers at distances Spacing*BrushDiameter along the stroke (so Spacing of 1 means that stamps will be adjacent but non-overlapping). Zero spacing means continuous stamps.
- L150 _public member_ `float Lazyness = 0;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Lazy", UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "1.0", DisplayPriority = 9, HideEditConditionToggle, EditConditionHides, EditCondition = "bShowLazyness"))` — Lazy brush smooths out the brush path by averaging the cursor positions
- L154 _public member_ `bool bShowPerBrushProps = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L158 _public member_ `bool bShowLazyness = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L162 _public member_ `bool bShowFlowRate = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L165 _public member_ `bool bShowSpacing = true;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UKelvinBrushProperties`  
`class UKelvinBrushProperties : public UInteractiveToolPropertySet`  
_L172-192_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L179 _public member_ `float FallOffDistance = 1.f;` — `UPROPERTY(EditAnywhere, Category = Kelvin, meta = (UIMin = "0.0", ClampMin = "0.0"))` — Brush Fall off as fraction of brush size
- L183 _public member_ `float Stiffness = 1.f;` — `UPROPERTY(EditAnywhere, Category = Kelvin, meta = (UIMin = "0.0", ClampMin = "0.0"))` — How much the mesh resists shear
- L187 _public member_ `float Incompressiblity = 1.f;` — `UPROPERTY(EditAnywhere, Category = Kelvin, meta = (UIMin = "0.0", UIMax = "0.1", ClampMin = "0.0", ClampMax = "1.0"))` — How compressible the spatial region is: 1 - 2 x Poisson ratio
- L191 _public member_ `int BrushSteps = 3;` — `UPROPERTY(EditAnywhere, Category = Kelvin, meta = (UIMin = "0.0", UIMax = "100", ClampMin = "0.0", ClampMax = "100"))` — Integration steps

#### class `UWorkPlaneProperties`  
`class UWorkPlaneProperties : public UInteractiveToolPropertySet`  
_L198-230_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L204 _public member_ `bool bPropertySetEnabled = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L208 _public member_ `bool bShowGizmo = true;` — `UPROPERTY(EditAnywhere, Category = TargetPlane, meta = (HideEditConditionToggle, EditCondition = "bPropertySetEnabled == true", ModelingQuickSettings))` — Toggle whether Work Plane Positioning Gizmo is visible
- L212 _public member_ `bool bShowPlane = true;` — `UPROPERTY(EditAnywhere, Category = TargetPlane)` — Toggle whether Work Plane is visible
- L215 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = TargetPlane, AdvancedDisplay, meta = (HideEditConditionToggle, EditCondition = "bPropertySetEnabled == true"))`
- L218 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = TargetPlane, AdvancedDisplay, meta = (HideEditConditionToggle, EditCondition = "bPropertySetEnabled == true"))`
- L221 _public function_ `void RecenterGizmoIfFar(FVector CenterPosition, double BoundsMaxDim, double TooFarDistance = 1000)` — Recenter the gizmo around the target position (without changing work plane), if it is "too far" (> 10 meters + max bounds dim) from that position currently

#### class `USculptMaxBrushProperties`  
`class USculptMaxBrushProperties : public UInteractiveToolPropertySet`  
_L236-247_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L242 _public member_ `float MaxHeight = 0.5;` — `UPROPERTY(EditAnywhere, Category = SculptMaxBrush, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Specify maximum displacement height (relative to brush size)
- L246 _public member_ `bool bFreezeCurrentHeight = false;` — `UPROPERTY(EditAnywhere, Category = SculptMaxBrush)` — Use maximum height from last brush stroke, regardless of brush size. Note that spatial brush falloff still applies.

#### class `UMeshSculptToolBase`  
`class UMeshSculptToolBase : public UMeshSurfacePointTool`  
_L256-727_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointTool`
- desc: Base Tool for mesh sculpting tools, provides some shared functionality
- L260 _protected typedef_ `using FFrame3d = UE::Geometry::FFrame3d;`
- L263 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L265 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L267 _public prototype_ `virtual void Setup() override;`
- L268 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L269 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L272 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;` — UMeshSurfacePointTool API
- L273 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L274 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L275 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L276 _public prototype_ `virtual void OnCancelDrag() override;`
- L280 _protected prototype_ `virtual void OnTick(float DeltaTime) override;`
- L283 _protected prototype_ `virtual void OnCompleteSetup();`
- L284 _protected function_ `virtual void OnBeginStroke(const FRay& WorldRay)`
- L285 _protected function_ `virtual void OnEndStroke()`
- L286 _protected function_ `virtual void OnCancelStroke()`
- L291 _public member_ `TObjectPtr<USculptBrushProperties> BrushProperties;` — `UPROPERTY()` — Properties that control brush size/etc
- L295 _public member_ `TObjectPtr<UWorkPlaneProperties> GizmoProperties;` — `UPROPERTY()` — Properties for 3D workplane / gizmo
- L299 _protected member_ `UWorld* TargetWorld;` — required to spawn UPreviewMesh/etc
- L300 _protected member_ `FViewCameraState CameraState;`
- L303 _protected member_ `UE::Geometry::FTransformSRT3d InitialTargetTransform;` — Initial transformation on target mesh
- L305 _protected member_ `UE::Geometry::FTransformSRT3d CurTargetTransform;` — Active transformation on target mesh, includes baked scale
- L307 _protected prototype_ `FRay3d GetLocalRay(const FRay& WorldRay) const;`
- L310 _protected prototype_ `bool GetBrushSizePressureSensitivityEnabled() const;` — Returns true if BrushSize Pressure Sensitivity is both supported by the tool and currently enabled.
- L314 _public prototype_ `bool GetBrushStrengthPressureEnabled();` — Returns true if Pressure Sensitivity for Brush Strength is both supported by the tool and currently enabled.
- L316 _public prototype_ `void SetBrushStrengthPressureEnabled(const bool bEnabled);` — Sets the Pressure Sensitivity for Brush Strength to be enabled/disabled
- L322 _protected function_ `virtual UBaseDynamicMeshComponent* GetSculptMeshComponent()` — Subclass must implement this and return relevant rendering component
- L324 _protected function_ `virtual FDynamicMesh3* GetSculptMesh()`
- L325 _protected function_ `virtual const FDynamicMesh3* GetSculptMesh() const`
- L327 _protected function_ `virtual FDynamicMesh3* GetBaseMesh()`
- L328 _protected function_ `virtual const FDynamicMesh3* GetBaseMesh() const`
- L331 _protected function_ `virtual bool SharesBrushPropertiesChanges() const` — For any subclass where this returns false, BrushProperties will not be automatically saved/restored, so the class won't use BrushProperties changes made in other tools.
- L334 _protected prototype_ `virtual FString GetPropertyCacheIdentifier() const;` — Should be overriden by subclasses so that settings are not shared across this tool and subclasses.
- L340 _protected prototype_ `virtual void InitializeSculptMeshComponent(UBaseDynamicMeshComponent* Component, AActor* Actor);` — Subclass calls this to set up editing component
- L347 _protected prototype_ `virtual void CommitResult(UBaseDynamicMeshComponent* Component, bool bModifiedTopology);` — Subclass can override this to change what results are written. Default is to apply a default vertex positions update to the target object.
- L365 _public function_ `friend uint32 GetTypeHash(const FBrushTypeInfo& Other)`
- L370 _public function_ `const TSet<FBrushTypeInfo>& GetRegisteredPrimaryBrushTypes() const`
- L371 _public function_ `const TSet<FBrushTypeInfo>& GetRegisteredSecondaryBrushTypes() const`
- L374 _protected member_ `TSet<FBrushTypeInfo> RegisteredPrimaryBrushTypes;`
- L375 _protected member_ `TSet<FBrushTypeInfo> RegisteredSecondaryBrushTypes;`
- L378 _protected member_ `TMap<int32, TObjectPtr<UMeshSculptBrushOpProps>> BrushOpPropSets;` — `UPROPERTY()`
- L380 _protected member_ `TMap<int32, TUniquePtr<FMeshSculptBrushOpFactory>> BrushOpFactories;`
- L383 _protected member_ `TMap<int32, TObjectPtr<UMeshSculptBrushOpProps>> SecondaryBrushOpPropSets;` — `UPROPERTY()`
- L385 _protected member_ `TMap<int32, TUniquePtr<FMeshSculptBrushOpFactory>> SecondaryBrushOpFactories;`
- L387 _protected prototype_ `void RegisterBrushType(int32 Identifier, FText Name, TUniquePtr<FMeshSculptBrushOpFactory> Factory, UMeshSculptBrushOpProps* PropSet);`
- L388 _protected prototype_ `void RegisterSecondaryBrushType(int32 Identifier, FText Name, TUniquePtr<FMeshSculptBrushOpFactory> Factory, UMeshSculptBrushOpProps* PropSet);`
- L390 _protected prototype_ `virtual void SaveAllBrushTypeProperties(UInteractiveTool* SaveFromTool);`
- L391 _protected prototype_ `virtual void RestoreAllBrushTypeProperties(UInteractiveTool* RestoreToTool);`
- L394 _protected member_ `TUniquePtr<FMeshSculptBrushOp> PrimaryBrushOp;`
- L395 _protected member_ `UMeshSculptBrushOpProps* PrimaryVisiblePropSet = nullptr;` — BrushOpPropSets prevents GC of this
- L397 _protected member_ `TUniquePtr<FMeshSculptBrushOp> SecondaryBrushOp;`
- L398 _protected member_ `UMeshSculptBrushOpProps* SecondaryVisiblePropSet = nullptr;`
- L400 _protected member_ `bool bBrushOpPropsVisible = true;`
- L402 _protected prototype_ `void SetActivePrimaryBrushType(int32 Identifier);`
- L403 _protected prototype_ `void SetActiveSecondaryBrushType(int32 Identifier);`
- L404 _protected prototype_ `virtual TUniquePtr<FMeshSculptBrushOp>& GetActiveBrushOp();`
- L405 _protected prototype_ `void SetBrushOpPropsVisibility(bool bVisible);`
- L417 _public function_ `const TArray<FFalloffTypeInfo>& GetRegisteredPrimaryFalloffTypes() const`
- L420 _public prototype_ `virtual void SetPrimaryFalloffType(EMeshSculptFalloffType Falloff);` — Set the active falloff type for the primary brush
- L423 _protected member_ `TSharedPtr<FMeshSculptFallofFunc> PrimaryFalloff;`
- L425 _protected member_ `TArray<FFalloffTypeInfo> RegisteredPrimaryFalloffTypes;`
- L426 _protected prototype_ `void RegisterStandardFalloffTypes();`
- L433 _protected member_ `UE::Geometry::FInterval1d BrushRelativeSizeRange;`
- L434 _protected member_ `double CurrentBrushRadius = 1.0;`
- L435 _protected prototype_ `virtual void InitializeBrushSizeRange(const UE::Geometry::FAxisAlignedBox3d& TargetBounds);`
- L436 _protected prototype_ `virtual void CalculateBrushRadius();`
- L437 _protected prototype_ `virtual double GetActiveBrushRadius();`
- L438 _protected function_ `virtual double GetCurrentBrushRadius() const`
- L440 _protected member_ `double CurrentBrushFalloff = 0.5;`
- L441 _protected function_ `virtual double GetCurrentBrushFalloff() const`
- L443 _protected member_ `double ActivePressure = 1.0;`
- L444 _protected function_ `virtual double GetActivePressure() const`
- L447 _protected prototype_ `virtual double GetActiveBrushStrength();` — returns brush strength, factoring in pressure sensitivity if applicable
- L448 _protected prototype_ `virtual double GetCurrentBrushStrength();`
- L449 _protected prototype_ `virtual double GetCurrentBrushDepth();`
- L452 _public prototype_ `virtual void IncreaseBrushRadiusAction();`
- L453 _public prototype_ `virtual void DecreaseBrushRadiusAction();`
- L454 _public prototype_ `virtual void IncreaseBrushRadiusSmallStepAction();`
- L455 _public prototype_ `virtual void DecreaseBrushRadiusSmallStepAction();`
- L459 _public function_ `virtual void IncreaseBrushSpeedAction()` — client currently needs to implement these...
- L460 _public function_ `virtual void DecreaseBrushSpeedAction()`
- L461 _public function_ `virtual void NextBrushModeAction()`
- L462 _public function_ `virtual void PreviousBrushModeAction()`
- L467 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI override to focus on brush w/ 'F'
- L475 _protected member_ `FFrame3d LastBrushFrameWorld;`
- L476 _protected member_ `FFrame3d LastBrushFrameLocal;`
- L477 _protected member_ `int32 LastBrushTriangleID = IndexConstants::InvalidID;`
- L478 _protected member_ `double MinimumBrushAdaptiveSizeRatio = 0.01;`
- L480 _protected function_ `const FFrame3d& GetBrushFrameWorld() const`
- L481 _protected function_ `const FFrame3d& GetBrushFrameLocal() const`
- L482 _protected function_ `int32 GetBrushTriangleID() const`
- L483 _protected prototype_ `void UpdateBrushFrameWorld(const FVector3d& NewPosition, const FVector3d& NewNormal);`
- L484 _protected prototype_ `void AlignBrushToView();`
- L486 _protected function_ `bool GetBrushCanHitBackFaces() const`
- L495 _protected function_ `virtual int32 FindHitSculptMeshTriangle(const FRay3d& LocalRay)` — @return hit triangle at ray position - subclass *may* implement this
- L497 _protected function_ `virtual int32 FindHitSculptMeshTriangleConst(const FRay3d& LocalRay) const` — @return hit triangle at ray position - subclass *must* implement this
- L499 _protected function_ `virtual int32 FindHitTargetMeshTriangle(const FRay3d& LocalRay)` — @return hit triangle at ray position - subclass *may* implement this
- L501 _protected function_ `virtual int32 FindHitTargetMeshTriangleConst(const FRay3d& LocalRay) const` — @return hit triangle at ray position - subclass *should* implement this for most brushes
- L503 _protected prototype_ `bool ProjectWorldRayOnActivePlane(const FRay& WorldRay, FVector3d& ProjectedPosition, FVector3d& ProjectedNormal) const;`
- L504 _protected prototype_ `bool ProjectWorldRayOnTargetMesh(const FRay& WorldRay, bool bFallbackToViewPlane, FVector3d& ProjectedPosition, FVector3d& ProjectedNormal, int32& HitTriangle) const;`
- L505 _protected prototype_ `bool ProjectWorldRayOnSculptMesh(const FRay& WorldRay, bool bFallbackToViewPlane, FVector3d& ProjectedPosition, FVector3d& ProjectedNormal, int32& HitTriangle) const;`
- L507 _protected prototype_ `virtual bool UpdateBrushPositionOnActivePlane(const FRay& WorldRay);`
- L508 _protected prototype_ `virtual bool UpdateBrushPositionOnTargetMesh(const FRay& WorldRay, bool bFallbackToViewPlane);`
- L509 _protected prototype_ `virtual bool UpdateBrushPositionOnSculptMesh(const FRay& WorldRay, bool bFallbackToViewPlane);`
- L517 _protected function_ `virtual void UpdateHitSculptMeshTriangle(int32 TriangleID, const FRay3d& LocalRay)` — Provides a hook for informing subclasses which triangle was last hit during a brush update. Subclass should implement this if it needs to know which triangle was hit @param TriangleID the triangle last hit during brush updates on the Sculpt Mesh @param LocalRay the ray in local space which caused the triangle to be hit
- L525 _protected function_ `virtual void UpdateHitTargetMeshTriangle(int32 TriangleID, const FRay3d& LocalRay)` — Provides a hook for informing subclasses which triangle was last hit during a brush update. Subclass should implement this if it needs to know which triangle was hit @param TriangleID the triangle last hit during brush updates on the Target Mesh @param LocalRay the ray in local space which caused the triangle to be hit
- L531 _protected member_ `FFrame3d ActiveBrushTargetPlaneWorld;`
- L532 _protected prototype_ `virtual void UpdateBrushTargetPlaneFromHit(const FRay& WorldRay, const FHitResult& Hit);`
- L539 _protected member_ `bool bInStroke = false;`
- L540 _protected member_ `bool bSmoothing = false;`
- L541 _protected member_ `bool bInvert = false;`
- L542 _protected prototype_ `virtual void SaveActiveStrokeModifiers();`
- L543 _protected function_ `virtual bool InStroke() const`
- L544 _protected function_ `virtual bool GetInSmoothingStroke() const`
- L545 _protected function_ `virtual bool GetInInvertStroke() const`
- L554 _private member_ `TArray<FInputRayData> PendingInputRays;`
- L556 _private member_ `TOptional<FInputRayData> PreviousInputRay;` — If this is not the first time we're processing PendingInputRays during a stroke, the previous ray
- L557 _private member_ `TOptional<FVector3d> PreviousUnfilteredHitPosition;`
- L558 _private member_ `double PreviousUnfilteredHitRadius = 0;`
- L561 _private member_ `TObjectPtr<UPreviewGeometry> StrokeGeometry;` — `UPROPERTY()`
- L565 _protected prototype_ `virtual void UpdateStampPendingState();` — when in a stroke, this function determines when a new stamp should be emitted, based on spacing and flow rate settings
- L568 _protected member_ `double ActiveStrokeTime = 0.0;` — for tracking stroke time and length, to apply spacing and flow rate settings
- L569 _protected member_ `double ActiveStrokePathArcLen = 0.0;`
- L570 _protected member_ `int LastFlowTimeStamp = 0;`
- L571 _protected member_ `int LastSpacingTimestamp = 0;`
- L572 _protected prototype_ `virtual void ResetStrokeTime();`
- L573 _protected prototype_ `virtual void AccumulateStrokeTime(float DeltaTime);`
- L579 _protected member_ `bool bIsStampPending = false;`
- L580 _protected member_ `FRay PendingStampRay;`
- L590 _private member_ `TArray<FStampRayData> PendingStampRays;` — Sequence of stamps to apply. Initialized by UpdateStampPendingState and immediately applied, though potentially with filtering
- L593 _protected member_ `FSculptBrushStamp HoverStamp;`
- L594 _protected member_ `FSculptBrushStamp CurrentStamp;`
- L595 _protected member_ `FSculptBrushStamp LastStamp;`
- L596 _protected prototype_ `virtual void UpdateHoverStamp(const FFrame3d& StampFrameWorld);`
- L597 _protected function_ `virtual bool IsStampPending() const`
- L598 _protected function_ `virtual const FRay& GetPendingStampRayWorld() const`
- L600 _protected prototype_ `virtual float GetStampTemporalFlowRate() const;` — Temporal Flow Rate defines the frequency of stamp placement. 1 is max rate, 0 is no stamps. Defaults to BrushProperties->FlowRate, but subclasses can re-use that setting for other things
- L602 _protected prototype_ `void ProcessPerTickStamps(TFunction<bool(const FRay& StampRay)> UpdateStampPosition, TFunction<void(int StampIndex, const FRay& StampRay)> ExecuteStampOperation);`
- L603 _protected prototype_ `void ProcessPerTickStamps(TFunction<bool(const FRay& StampRay)> UpdateStampPosition, TFunction<void(int StampCount )> PreExecuteStampsOperation, TFunction<void(int StampIndex, const FRay& StampRay)> ExecuteStampOperation, TFunction<void()> PostExecuteStampsOperation );`
- L609 _protected member_ `FFrame3d StampRegionPlane;`
- L610 _protected prototype_ `virtual FFrame3d ComputeStampRegionPlane(const FFrame3d& StampFrame, const TArray<int32>& StampTriangles, bool bIgnoreDepth, bool bViewAligned, bool bInvDistFalloff = true);`
- L611 _protected prototype_ `virtual FFrame3d ComputeStampRegionPlane(const FFrame3d& StampFrame, const TSet<int32>& StampTriangles, bool bIgnoreDepth, bool bViewAligned, bool bInvDistFalloff = true);`
- L617 _protected member_ `FFrame3d StrokePlane;`
- L618 _protected function_ `virtual const FFrame3d& GetCurrentStrokeReferencePlane() const`
- L620 _protected prototype_ `virtual void UpdateStrokeReferencePlaneForROI(const FFrame3d& StampFrame, const TArray<int32>& TriangleROI, bool bViewAligned);`
- L621 _protected prototype_ `virtual void UpdateStrokeReferencePlaneFromWorkPlane();`
- L629 _public member_ `TObjectPtr<UMeshEditingViewProperties> ViewProperties;` — `UPROPERTY()`
- L632 _public member_ `TObjectPtr<UMaterialInstanceDynamic> ActiveOverrideMaterial;` — `UPROPERTY()`
- L635 _protected prototype_ `virtual void SetViewPropertiesEnabled(bool bNewValue);`
- L636 _protected prototype_ `virtual void UpdateWireframeVisibility(bool bNewValue);`
- L637 _protected prototype_ `virtual void UpdateMaterialMode(EMeshEditingMaterialModes NewMode);`
- L638 _protected prototype_ `virtual void UpdateFlatShadingSetting(bool bNewValue);`
- L639 _protected prototype_ `virtual void UpdateColorSetting(FLinearColor NewColor);`
- L640 _protected prototype_ `virtual void UpdateTransparentColorSetting(FLinearColor NewColor);`
- L641 _protected prototype_ `virtual void UpdateOpacitySetting(double Opacity);`
- L642 _protected prototype_ `virtual void UpdateTwoSidedSetting(bool bOn);`
- L643 _protected prototype_ `virtual void UpdateCustomMaterial(TWeakObjectPtr<UMaterialInterface> NewMaterial);`
- L644 _protected prototype_ `virtual void UpdateImageSetting(UTexture2D* NewImage);`
- L653 _protected prototype_ `virtual void InitializeIndicator();` — subclasses should call this to create indicator in their ::Setup()
- L656 _protected prototype_ `virtual UPreviewMesh* MakeBrushIndicatorMesh(UObject* Parent, UWorld* World);` — Called by InitializeIndicator to create a mesh for the brush ROI indicator. Default is sphere.
- L658 _protected prototype_ `virtual void ConfigureIndicator(bool bVolumetric);`
- L659 _protected prototype_ `virtual bool GetIsVolumetricIndicator();`
- L661 _protected prototype_ `virtual void SetIndicatorVisibility(bool bVisible);`
- L662 _protected prototype_ `virtual bool GetIndicatorVisibility() const;`
- L664 _protected prototype_ `virtual void SetupBrushEditBehaviorSetup(ULocalTwoAxisPropertyEditInputBehavior& OutBehavior);`
- L666 _protected prototype_ `void MapHorizontalBrushEditBehaviorToBrushSize(ULocalTwoAxisPropertyEditInputBehavior& OutBehavior);`
- L670 _protected member_ `TObjectPtr<UBrushStampIndicator> BrushIndicator;` — `UPROPERTY()`
- L673 _protected member_ `bool bIsVolumetricIndicator;` — `UPROPERTY()`
- L677 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> BrushIndicatorMaterial;` — `UPROPERTY()`
- L680 _protected member_ `TObjectPtr<UPreviewMesh> BrushIndicatorMesh;` — `UPROPERTY()`
- L683 _protected member_ `TWeakObjectPtr<ULocalTwoAxisPropertyEditInputBehavior> BrushEditBehavior;`
- L692 _public member_ `TObjectPtr<UCombinedTransformGizmo> PlaneTransformGizmo;` — `UPROPERTY()` — plane gizmo
- L695 _public member_ `TObjectPtr<UTransformProxy> PlaneTransformProxy;` — `UPROPERTY()`
- L698 _protected prototype_ `virtual void UpdateWorkPlane();`
- L699 _protected function_ `virtual bool ShowWorkPlane() const`
- L702 _protected member_ `bool bDrawWorkPlaneGridLines = true;` — Only relevant when ShowWorkPlane() returns true. Determines whether the plane grid lines are drawn.
- L705 _protected member_ `TValueWatcher<FVector> GizmoPositionWatcher;`
- L706 _protected member_ `TValueWatcher<FQuat> GizmoRotationWatcher;`
- L708 _protected prototype_ `virtual void UpdateGizmoFromProperties();`
- L709 _protected prototype_ `virtual void PlaneTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L718 _protected member_ `EPendingWorkPlaneUpdate PendingWorkPlaneUpdate;`
- L719 _protected prototype_ `virtual void SetFixedSculptPlaneFromWorldPos(const FVector& Position, const FVector& Normal, EPendingWorkPlaneUpdate UpdateType);`
- L720 _protected prototype_ `virtual void UpdateFixedSculptPlanePosition(const FVector& Position);`
- L721 _protected prototype_ `virtual void UpdateFixedSculptPlaneRotation(const FQuat& Rotation);`
- L722 _protected prototype_ `virtual void UpdateFixedPlaneGizmoVisibility(bool bVisible);`
- L725 _protected member_ `UE::TransactionUtil::FLongTransactionTracker LongTransactions;`

#### struct `UMeshSculptToolBase::FBrushTypeInfo`  
`struct FBrushTypeInfo`  
_L354-369_
- L356 _public member_ `FText Name;`
- L357 _public member_ `int32 Identifier;`
- L359 _public function_ `bool operator==( const FBrushTypeInfo& Other ) const`

#### struct `UMeshSculptToolBase::FFalloffTypeInfo`  
`struct FFalloffTypeInfo`  
_L411-416_
- L413 _public member_ `FText Name;`
- L414 _public member_ `FString StringIdentifier;`
- L415 _public member_ `int32 Identifier;`

#### struct `UMeshSculptToolBase::FInputRayData`  
`struct FInputRayData`  
_L548-553_
- L550 _public member_ `FRay Ray;`
- L551 _public member_ `double Timestamp;`
- L552 _public member_ `double Pressure;`

#### struct `UMeshSculptToolBase::FStampRayData`  
`struct FStampRayData`  
_L583-587_
- L585 _public member_ `FRay StampRay;`
- L586 _public member_ `double Pressure;`

#### enum `UMeshSculptToolBase::EPendingWorkPlaneUpdate`  
`enum class EPendingWorkPlaneUpdate`  
_L711-717_
- L713 _public enumerator_ `NoUpdatePending`
- L714 _public enumerator_ `MoveToHitPositionNormal`
- L715 _public enumerator_ `MoveToHitPosition`
- L716 _public enumerator_ `MoveToHitPositionViewAligned`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshSculptUtil.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SculptUtil` (scope `UE`)
- L22 _prototype_ `void RecalculateNormals_Overlay(FDynamicMesh3* Mesh, const TSet<int32>& ModifiedTris, TSet<int32>& ElementSetBuffer, TArray<int32>& NormalsBuffer);` (scope `UE::SculptUtil`) — Recompute overlay normals for the overlay elements belonging to all the ModifiedTris. ElementSetBuffer and NormalsBuffer will be populated with all the normal overlay element IDs (you provide to allow for re-use of allocated memory)
- L28 _prototype_ `void RecalculateNormals_PerVertex(FDynamicMesh3* Mesh, const TSet<int32>& ModifiedTris, TSet<int32>& VertexSetBuffer, TArray<int32>& NormalsBuffer);` (scope `UE::SculptUtil`) — Recompute mesh vertex normals for the vertices belonging to all the ModifiedTris. VertexSetBuffer and NormalsBuffer will be populated with all the vertex IDs (you provide to allow for re-use of allocated memory)
- L34 _prototype_ `void RecalculateROINormals(FDynamicMesh3* Mesh, const TSet<int32>& TriangleROI, TSet<int32>& TempSetBuffer, TArray<int32>& NormalsBuffer, bool bForceVertex = false);` (scope `UE::SculptUtil`) — Recompute normals for either the normals overlay or vertex normals of the mesh that belong to all the ModifiedTris TempSetBuffer and NormalsBuffer will be populated with either the recomputed overlay element IDs or vertex IDs
- L43 _prototype_ `void RecalculateNormals_Overlay(FDynamicMesh3* Mesh, const TSet<int32>& ModifiedTris, FUniqueIndexSet& ElementSetTemp);` (scope `UE::SculptUtil`) — Recompute overlay normals for the overlay elements belonging to all the ModifiedTris. ElementSetTemp will be populated with all the normal overlay element IDs (you provide to allow for re-use of allocated memory)
- L49 _prototype_ `void RecalculateNormals_PerVertex(FDynamicMesh3* Mesh, const TSet<int32>& ModifiedTris, FUniqueIndexSet& VertexSetTemp);` (scope `UE::SculptUtil`) — Recompute mesh vertex normals for the vertices belonging to all the ModifiedTris. VertexSetTemp will be populated with all the vertex IDs (you provide to allow for re-use of allocated memory)
- L55 _prototype_ `void RecalculateROINormals(FDynamicMesh3* Mesh, const TSet<int32>& TriangleROI, FUniqueIndexSet& IndexSetTemp, bool bForceVertex = false);` (scope `UE::SculptUtil`) — Recompute normals for either the normals overlay or vertex normals of the mesh that belong to all the ModifiedTris IndexSetTemp will be populated with either the recomputed overlay element IDs or vertex IDs
- L63 _prototype_ `void PrecalculateNormalsROI(const FDynamicMesh3* Mesh, const TArray<int32>& TriangleROI, FUniqueIndexSet& IndexSetTemp, bool& bIsOverlayElementsOut, bool bForceVertex = false);` (scope `UE::SculptUtil`) — Precalculate IndexSetTemp for the modified TriangleROI, the indices will either be overlay normal element IDs, or vertex IDs @param bIsOverlayElementsOut will be returned as true for overlay normals, false for vertex normals
- L69 _prototype_ `void RecalculateROINormals(FDynamicMesh3* Mesh, const TArray<int32>& Indices, bool bIsOverlayElements);` (scope `UE::SculptUtil`) — Recalculate either overlay normals or vertex normals for the given Indices @param bIsOverlayElements if true, Indices is interpreted as overlay element IDs, otherwise as vertex IDs
- L78 _prototype_ `void PrecalculateNormalsROI(const FDynamicMesh3* Mesh, const TArray<int32>& TriangleROI, TArray<std::atomic<bool>>& ROIFlags, bool& bIsOverlayElementsOut, bool bForceVertex = false);` (scope `UE::SculptUtil`) — Precalculate ROIFlags for the modified TriangleROI, the indices will either be overlay normal element IDs, or vertex IDs. ROIFlags will be resized to either the max overlay element ID, or the max vertex ID, and indices in the ROI will be set to true @param bIsOverlayElementsOut will be returned as true for overlay normals, false for vertex normals
- L85 _prototype_ `void RecalculateROINormals(FDynamicMesh3* Mesh, TArray<std::atomic<bool>>& ROIFlags, bool bIsOverlayElements);` (scope `UE::SculptUtil`) — Recalculate either overlay normals or vertex normals for the given indices that are true in ROIFlags @param bIsOverlayElements if true, ROIFlags is interpreted as overlay element ID flags, otherwise as vertex IDs
- L91 _prototype_ `void RecalculateROINormalForTriangles(FDynamicMesh3* Mesh, TArray<int> Triangles, bool bIsOverlayElements);` (scope `UE::SculptUtil`) — Recalculate either overlay normals or vertex normals for the given indices defined by a set of triangles @param bIsOverlayElements if true, normals are computed on the overlay. Otherwise, they are computed as vertex normals

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshSmoothingBrushOps.h` (Public)


#### class `UBaseSmoothBrushOpProps`  
`class UBaseSmoothBrushOpProps : public UMeshSculptBrushOpProps`  
_L14-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L18 _public function_ `virtual bool GetPreserveUVFlow()`
- L20 _public function_ `virtual float GetPolyGroupEdgesWeight()` — @return a float value in the [0,1] range controlling the desired relative weight of PolyGroup edges in smoothing (1 = maximally favor PolyGroup edges, 0 = ignore PolyGroup edges)
- L21 _public function_ `virtual bool SupportsStrengthPressure() override`
- L22 _public function_ `virtual int32 GetIterations()`

#### class `USmoothBrushOpProps`  
`class USmoothBrushOpProps : public UBaseSmoothBrushOpProps`  
_L27-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseSmoothBrushOpProps`
- L33 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L37 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply (0.0 - 1.0)
- L40 _public member_ `int32 Iterations = 1;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush, meta = (ClampMin = 1, UIMax = 50))`
- L44 _public member_ `bool bPreserveUVFlow = true;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush)` — If true, try to preserve the shape of the UV/3D mapping. This will limit Smoothing and Remeshing in some cases.
- L48 _public member_ `bool bFavorPolyGroupEdges = false;` — `UPROPERTY(EditAnywhere, Category = SmoothBrush)` — If true, favor smoothing along PolyGroup edges where they are present. Can help to preserve quads. No effect where PolyGroups are not defined.
- L50 _public function_ `virtual float GetStrength() override`
- L51 _public function_ `virtual void SetStrength(float NewStrength) override`
- L52 _public function_ `virtual float GetFalloff() override`
- L53 _public function_ `virtual bool GetPreserveUVFlow() override`
- L54 _public function_ `virtual float GetPolyGroupEdgesWeight() override`
- L55 _public function_ `virtual int32 GetIterations()`

#### class `USecondarySmoothBrushOpProps`  
`class USecondarySmoothBrushOpProps : public UBaseSmoothBrushOpProps`  
_L61-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseSmoothBrushOpProps`
- L67 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Strength of the Brush
- L71 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L74 _public member_ `int32 Iterations = 1;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush, meta = (ClampMin = 1, UIMax = 50))`
- L78 _public member_ `bool bPreserveUVFlow = true;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush)` — If true, try to preserve the shape of the UV/3D mapping. This will limit Smoothing and Remeshing in some cases.
- L82 _public member_ `bool bFavorPolyGroupEdges = false;` — `UPROPERTY(EditAnywhere, Category = ShiftSmoothBrush)` — If true, favor smoothing along PolyGroup edges where they are present. Can help to preserve quads. No effect where PolyGroups are not defined.
- L84 _public function_ `virtual float GetStrength() override`
- L85 _public function_ `virtual void SetStrength(float NewStrength) override`
- L86 _public function_ `virtual float GetFalloff() override`
- L87 _public function_ `virtual bool GetPreserveUVFlow() override`
- L88 _public function_ `virtual float GetPolyGroupEdgesWeight() override`
- L89 _public function_ `virtual int32 GetIterations()`

#### class `FSmoothBrushOp`  
`class FSmoothBrushOp : public FMeshSculptBrushOp`  
_L94-183_
- inherits: `FMeshSculptBrushOp`
- L99 _public function_ `static void ApplyIterativeStamp(const FDynamicMesh3* Mesh, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut, int32 NumIters, TFunctionRef<FVector3d(int32 Iter, FVector3d OrigPos, int32 VID, TFunctionRef<FVector3d(int32)> GetVertexFn)> GetStampVertPos)`
- L141 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### class `USmoothFillBrushOpProps`  
`class USmoothFillBrushOpProps : public UBaseSmoothBrushOpProps`  
_L190-210_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseSmoothBrushOpProps`
- L196 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothFillBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L200 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = SmoothFillBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply (0.0 - 1.0)
- L204 _public member_ `bool bPreserveUVFlow = false;` — `UPROPERTY(EditAnywhere, Category = SmoothFillBrush)` — If true, try to preserve the shape of the UV/3D mapping. This will limit Smoothing and Remeshing in some cases.
- L206 _public function_ `virtual float GetStrength() override`
- L207 _public function_ `virtual void SetStrength(float NewStrength) override`
- L208 _public function_ `virtual float GetFalloff() override`
- L209 _public function_ `virtual bool GetPreserveUVFlow() override`

#### class `FSmoothFillBrushOp`  
`class FSmoothFillBrushOp : public FMeshSculptBrushOp`  
_L214-257_
- inherits: `FMeshSculptBrushOp`
- L219 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### class `UFlattenBrushOpProps`  
`class UFlattenBrushOpProps : public UMeshSculptBrushOpProps`  
_L264-284_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L270 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = FlattenBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L274 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = FlattenBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply (0.0 - 1.0)
- L278 _public member_ `EPlaneBrushSideMode WhichSide = EPlaneBrushSideMode::BothSides;` — `UPROPERTY(EditAnywhere, Category = FlattenBrush)` — Control whether effect of brush should be limited to one side of the Plane
- L280 _public function_ `virtual float GetStrength() override`
- L281 _public function_ `virtual void SetStrength(float NewStrength) override`
- L282 _public function_ `virtual float GetFalloff() override`
- L283 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FFlattenBrushOp`  
`class FFlattenBrushOp : public FMeshSculptBrushOp`  
_L287-335_
- inherits: `FMeshSculptBrushOp`
- L291 _public member_ `double BrushSpeedTuning = 5.0;`
- L293 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`
- L331 _public function_ `virtual bool WantsStampRegionPlane() const`

#### class `UEraseBrushOpProps`  
`class UEraseBrushOpProps : public UMeshSculptBrushOpProps`  
_L343-359_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L349 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = EraseBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L353 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = EraseBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply (0.0 - 1.0)
- L355 _public function_ `virtual float GetStrength() override`
- L356 _public function_ `virtual void SetStrength(float NewStrength) override`
- L357 _public function_ `virtual float GetFalloff() override`
- L358 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FEraseToBaseMeshBrushOp`  
`class FEraseToBaseMeshBrushOp : public FMeshSculptBrushOp`  
_L362-415_
- inherits: `FMeshSculptBrushOp`
- L365 _public member_ `double BrushSpeedTuning = 3.0;`
- L367 _public typedef_ `typedef TUniqueFunction<bool(int32, const FVector3d&, double, FVector3d&, FVector3d&)> NearestQueryFuncType;`
- L369 _public member_ `NearestQueryFuncType BaseMeshNearestQueryFunc;`
- L371 _public function_ `FEraseToBaseMeshBrushOp(NearestQueryFuncType QueryFunc)`
- L376 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L381 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### Free symbols / members of external scopes

- L114 _function_ `auto MeshVertPos = [&Mesh](int32 VID)` (scope `FSmoothBrushOp::ApplyIterativeStamp`)
- L116 _function_ `` (scope `FSmoothBrushOp::ApplyIterativeStamp`)
- L148 _function_ `` (scope `FSmoothBrushOp::ApplyStamp`)
- L165 _function_ `` (scope `FSmoothBrushOp::ApplyStamp::__anon377366520402`)
- L226 _function_ `` (scope `FSmoothFillBrushOp::ApplyStamp`)
- L308 _function_ `` (scope `FFlattenBrushOp::ApplyStamp`)
- L387 _function_ `` (scope `FEraseToBaseMeshBrushOp::ApplyStamp`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/MeshVertexPaintBrushOps.h` (Public)


#### enum `EVertexColorPaintBrushOpBlendMode`  
`enum class EVertexColorPaintBrushOpBlendMode`  
_L16-21_
- reflection: `UENUM()`
- L18 _public enumerator_ `Lerp = 0`
- L19 _public enumerator_ `Mix = 1`
- L20 _public enumerator_ `Multiply = 2`

#### class `UVertexColorBaseBrushOpProps`  
`class UVertexColorBaseBrushOpProps : public UMeshSculptBrushOpProps`  
_L120-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L127 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit))` — Strength of the Brush
- L131 _public member_ `float Falloff = 1.0;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L134 _public member_ `EVertexColorPaintBrushOpBlendMode BlendMode = EVertexColorPaintBrushOpBlendMode::Mix;` — `UPROPERTY(EditAnywhere, Category = PaintBrush)`
- L138 _public member_ `bool bApplyFalloff = true;` — `UPROPERTY(EditAnywhere, Category = PaintBrush)` — If bApplyFalloff is disabled, 1.0 is used as "falloff" for all vertices
- L140 _public function_ `virtual bool SupportsStrengthPressure() override`
- L141 _public function_ `virtual float GetStrength() override`
- L142 _public function_ `virtual void SetStrength(float NewStrength) override`
- L143 _public function_ `virtual float GetFalloff() override`
- L144 _public function_ `virtual void SetFalloff(float NewFalloff) override`

#### class `UVertexColorPaintBrushOpProps`  
`class UVertexColorPaintBrushOpProps : public UVertexColorBaseBrushOpProps`  
_L152-161_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UVertexColorBaseBrushOpProps`
- L158 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category = Paint, meta = (DisplayName = "Color"))` — The paint color
- L160 _public function_ `virtual FLinearColor GetColor() const`

#### class `UVertexColorSoftenBrushOpProps`  
`class UVertexColorSoftenBrushOpProps : public UVertexColorBaseBrushOpProps`  
_L165-171_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UVertexColorBaseBrushOpProps`
- L170 _public function_ `virtual float GetFalloff() override`

#### class `UVertexColorSmoothBrushOpProps`  
`class UVertexColorSmoothBrushOpProps : public UVertexColorBaseBrushOpProps`  
_L174-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UVertexColorBaseBrushOpProps`

#### class `UE::Geometry::FMeshVertexColorBrushOp`  
`class FMeshVertexColorBrushOp : public FMeshSculptBrushOp`  
_L186-210_
- inherits: `FMeshSculptBrushOp`
- L191 _public function_ `virtual void ApplyStamp( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewColorsOut) override` — not supported for this kind of brush op
- L201 _public prototype_ `virtual void ApplyStampToVertexColors( const FDynamicMesh3* Mesh, const FDynamicMeshColorOverlay* VertexColors, TArray<FVector4f>& InitialVertexColorBuffer, TArray<FVector4f>& StrokeVertexColorBuffer, const FSculptBrushStamp& Stamp, const TArray<int32>& ElementIDs, TArray<FVector4f>& NewColorsOut) = 0;`

#### class `UE::Geometry::FVertexPaintBrushOp`  
`class FVertexPaintBrushOp : public FMeshVertexColorBrushOp`  
_L215-288_
- inherits: `FMeshVertexColorBrushOp`
- L218 _public member_ `double BrushSpeedTuning = 6.0;`
- L220 _public function_ `virtual void ApplyStampToVertexColors( const FDynamicMesh3* Mesh, const FDynamicMeshColorOverlay* VertexColors, TArray<FVector4f>& InitialVertexColorBuffer, TArray<FVector4f>& StrokeVertexColorBuffer, const FSculptBrushStamp& Stamp, const TArray<int32>& ElementIDs, TArray<FVector4f>& NewColorsOut) override`
- L271 _public function_ `virtual bool SupportsVariableSpacing() const override`
- L276 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const override`

#### class `UE::Geometry::FVertexColorSoftenBrushOp`  
`class FVertexColorSoftenBrushOp : public FMeshVertexColorBrushOp`  
_L296-336_
- inherits: `FMeshVertexColorBrushOp`
- desc: Soften brush averages colors at any vertices that have split elements, effectively un-splitting them Currently this averaging is done in a single step, ie falloff/etc is ignored, but it could be done more gradually...
- L299 _public member_ `TArray<int32> TempElementIDs;`
- L301 _public function_ `virtual void ApplyStampToVertexColors( const FDynamicMesh3* Mesh, const FDynamicMeshColorOverlay* VertexColors, TArray<FVector4f>& InitialVertexColorBuffer, TArray<FVector4f>& StrokeVertexColorBuffer, const FSculptBrushStamp& Stamp, const TArray<int32>& ElementIDs, TArray<FVector4f>& NewColorsOut) override`

#### class `UE::Geometry::FVertexColorSmoothBrushOp`  
`class FVertexColorSmoothBrushOp : public FMeshVertexColorBrushOp`  
_L341-449_
- inherits: `FMeshVertexColorBrushOp`
- L344 _public member_ `double BrushSpeedTuning = 6.0;`
- L345 _public member_ `TArray<int32> TempElementIDs;`
- L346 _public member_ `TArray<int32> ElementIDVertices;`
- L347 _public member_ `TArray<int32> ElementIDVertexIndices;`
- L348 _public member_ `TArray<int32> UniqueVertices;`
- L349 _public member_ `TArray<FVector4f> SoftenedVertexColors;`
- L350 _public member_ `TArray<FVector4f> SmoothedVertexColors;`
- L353 _public function_ `virtual void ApplyStampToVertexColors( const FDynamicMesh3* Mesh, const FDynamicMeshColorOverlay* VertexColors, TArray<FVector4f>& InitialVertexColorBuffer, TArray<FVector4f>& StrokeVertexColorBuffer, const FSculptBrushStamp& Stamp, const TArray<int32>& ElementIDs, TArray<FVector4f>& NewColorsOut) override`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UELocal`
- L28 _function_ `template <typename RealType> inline UE::Math::TVector4<RealType> BlendColors_Mix( const UE::Math::TVector4<RealType>& BackColor, const UE::Math::TVector4<RealType>& ForeColor, RealType Alpha)` (scope `UELocal`)
- L66 _function_ `template <typename RealType> inline UE::Math::TVector4<RealType> BlendColors_Lerp( const UE::Math::TVector4<RealType>& A, const UE::Math::TVector4<RealType>& B, RealType Alpha)` (scope `UELocal`)
- L81 _function_ `template <typename RealType> inline UE::Math::TVector4<RealType> BlendColors_Multiply( const UE::Math::TVector4<RealType>& A, const UE::Math::TVector4<RealType>& B, RealType Alpha)` (scope `UELocal`)
- L96 _function_ `template <typename RealType> inline UE::Math::TVector4<RealType> BlendColors( const UE::Math::TVector4<RealType>& Background, const UE::Math::TVector4<RealType>& Foreground, RealType Alpha, EVertexColorPaintBrushOpBlendMode BlendMode)` (scope `UELocal`)
- L182 _namespace_ `namespace UE`
- L182 _namespace_ `namespace Geometry` (scope `UE`)
- L246 _function_ `` (scope `UE::Geometry::FVertexPaintBrushOp::ApplyStampToVertexColors`)
- L386 _function_ `` (scope `UE::Geometry::FVertexColorSmoothBrushOp::ApplyStampToVertexColors`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/Sculpting/StampFalloffs.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SculptFalloffs` (scope `UE`)
- L15 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeStandardSmoothFalloff()` (scope `UE::SculptFalloffs`)
- L18 _function_ `` (scope `UE::SculptFalloffs::MakeStandardSmoothFalloff`)
- L34 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeLinearFalloff()` (scope `UE::SculptFalloffs`)
- L37 _function_ `` (scope `UE::SculptFalloffs::MakeLinearFalloff`)
- L54 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeInverseFalloff()` (scope `UE::SculptFalloffs`)
- L57 _function_ `` (scope `UE::SculptFalloffs::MakeInverseFalloff`)
- L73 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeRoundFalloff()` (scope `UE::SculptFalloffs`)
- L76 _function_ `` (scope `UE::SculptFalloffs::MakeRoundFalloff`)
- L91 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeSmoothBoxFalloff()` (scope `UE::SculptFalloffs`)
- L94 _function_ `` (scope `UE::SculptFalloffs::MakeSmoothBoxFalloff`)
- L122 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeLinearBoxFalloff()` (scope `UE::SculptFalloffs`)
- L125 _function_ `` (scope `UE::SculptFalloffs::MakeLinearBoxFalloff`)
- L152 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeRoundBoxFalloff()` (scope `UE::SculptFalloffs`)
- L155 _function_ `` (scope `UE::SculptFalloffs::MakeRoundBoxFalloff`)
- L182 _function_ `static TUniqueFunction<double(const FSculptBrushStamp&, const FVector3d&)> MakeInverseBoxFalloff()` (scope `UE::SculptFalloffs`)
- L185 _function_ `` (scope `UE::SculptFalloffs::MakeInverseBoxFalloff`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/SmoothMeshTool.h` (Public)


#### enum `ESmoothMeshToolSmoothType`  
`enum class ESmoothMeshToolSmoothType : uint8`  
_L13-23_
- reflection: `UENUM()`
- L16 _public enumerator_ `Iterative UMETA(DisplayName = "Fast Iterative")` — Iterative smoothing with N iterations
- L19 _public enumerator_ `Implicit UMETA(DisplayName = "Fast Implicit")` — Implicit smoothing, produces smoother output and does a better job at preserving UVs, but can be very slow on large meshes
- L22 _public enumerator_ `Diffusion UMETA(DisplayName = "Iterative Diffusion")` — Iterative implicit-diffusion smoothing with N iterations

#### class `USmoothMeshToolProperties`  
`class USmoothMeshToolProperties : public UInteractiveToolPropertySet`  
_L29-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: PropertySet for properties affecting the Smoother.
- L36 _public member_ `ESmoothMeshToolSmoothType SmoothingType = ESmoothMeshToolSmoothType::Iterative;` — `UPROPERTY(EditAnywhere, Category = SmoothingType)` — Type of smoothing to apply

#### class `UIterativeSmoothProperties`  
`class UIterativeSmoothProperties : public UInteractiveToolPropertySet`  
_L43-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for Iterative Smoothing
- L49 _public member_ `float SmoothingPerStep = 0.8f;` — `UPROPERTY(EditAnywhere, Category = IterativeSmoothingOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of smoothing allowed per step. Smaller steps will avoid things like collapse of small/thin features.
- L53 _public member_ `int32 Steps = 10;` — `UPROPERTY(EditAnywhere, Category = IterativeSmoothingOptions, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — Number of Smoothing iterations
- L57 _public member_ `bool bSmoothBoundary = true;` — `UPROPERTY(EditAnywhere, Category = IterativeSmoothingOptions)` — If this is false, the smoother will try to reshape the triangles to be more regular, which will distort UVs

#### class `UDiffusionSmoothProperties`  
`class UDiffusionSmoothProperties : public UInteractiveToolPropertySet`  
_L64-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for Diffusion Smoothing
- L71 _public member_ `float SmoothingPerStep = 0.8f;` — `UPROPERTY(EditAnywhere, Category = DiffusionSmoothingOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of smoothing allowed per step. Smaller steps will avoid things like collapse of small/thin features.
- L75 _public member_ `int32 Steps = 1;` — `UPROPERTY(EditAnywhere, Category = DiffusionSmoothingOptions, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — Number of Smoothing iterations
- L79 _public member_ `bool bPreserveUVs = true;` — `UPROPERTY(EditAnywhere, Category = DiffusionSmoothingOptions)` — If this is false, the smoother will try to reshape the triangles to be more regular, which will distort UVs

#### class `UImplicitSmoothProperties`  
`class UImplicitSmoothProperties : public UInteractiveToolPropertySet`  
_L87-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for Implicit smoothing
- L95 _public member_ `float SmoothSpeed = 0.1f;` — `UPROPERTY(EditAnywhere, Category = ImplicitSmoothing, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — `UPROPERTY()` — Smoothing speed
- L99 _public member_ `float Smoothness = 0.2f;` — `UPROPERTY(EditAnywhere, Category = ImplicitSmoothingOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "100.0"))` — Desired Smoothness. This is not a linear quantity, but larger numbers produce smoother results
- L103 _public member_ `bool bPreserveUVs = true;` — `UPROPERTY(EditAnywhere, Category = ImplicitSmoothingOptions)` — If this is false, the smoother will try to reshape the triangles to be more regular, which will distort UVs
- L107 _public member_ `float VolumeCorrection = 0.0f;` — `UPROPERTY(EditAnywhere, Category = ImplicitSmoothingOptions, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0"))` — Magic number that allows you to try to correct for shrinking caused by smoothing

#### class `USmoothWeightMapSetProperties`  
`class USmoothWeightMapSetProperties : public UWeightMapSetProperties`  
_L113-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWeightMapSetProperties`
- L120 _public member_ `float MinSmoothMultiplier = 0.0f;` — `UPROPERTY(EditAnywhere, Category = WeightMap, AdvancedDisplay, meta = (UIMin = "0.0", UIMax = "1.0", DisplayPriority = 5))` — Fractional Minimum Smoothing Parameter in World Units, for Weight Map values of zero

#### class `USmoothMeshTool`  
`class USmoothMeshTool : public UBaseMeshProcessingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L130-169_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseMeshProcessingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Mesh Smoothing Tool
- L135 _public prototype_ `USmoothMeshTool();`
- L137 _public prototype_ `virtual void InitializeProperties() override;`
- L138 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L140 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;`
- L142 _public function_ `virtual bool RequiresInitialVtxNormals() const`
- L143 _public prototype_ `virtual bool HasMeshTopologyChanged() const override;`
- L145 _public prototype_ `virtual FText GetToolMessageString() const override;`
- L146 _public prototype_ `virtual FText GetAcceptTransactionName() const override;`
- L149 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L156 _protected member_ `TObjectPtr<USmoothMeshToolProperties> SmoothProperties = nullptr;` — `UPROPERTY()`
- L159 _protected member_ `TObjectPtr<UIterativeSmoothProperties> IterativeProperties = nullptr;` — `UPROPERTY()`
- L162 _protected member_ `TObjectPtr<UDiffusionSmoothProperties> DiffusionProperties = nullptr;` — `UPROPERTY()`
- L165 _protected member_ `TObjectPtr<UImplicitSmoothProperties> ImplicitProperties = nullptr;` — `UPROPERTY()`
- L168 _protected member_ `TObjectPtr<USmoothWeightMapSetProperties> WeightMapProperties = nullptr;` — `UPROPERTY()`

#### class `USmoothMeshToolBuilder`  
`class USmoothMeshToolBuilder : public UBaseMeshProcessingToolBuilder`  
_L178-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseMeshProcessingToolBuilder`
- L182 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditActivityContext.h` (Public)


#### class `UPolyEditActivityContext`  
`class UPolyEditActivityContext : public UObject`  
_L22-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L29 _public member_ `TObjectPtr<UPolyEditCommonProperties> CommonProperties;` — `UPROPERTY()`
- L35 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> CurrentMesh;` — The CurrentMesh is the authoritative current version of the mesh, which would be baked back to the asset on accept.
- L43 _public member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview;` — `UPROPERTY()` — The mesh stored in the preview is not authoritative. It may be altered in various ways as the user previews potential changes, and may be reset back to CurrentMesh if an activity is cancelled.
- L48 _public member_ `TSharedPtr<UE::Geometry::FGroupTopology, ESPMode::ThreadSafe> CurrentTopology;` — The activity should update CurrentTopology and MeshSpatial if it alters CurrentMesh.
- L49 _public member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> MeshSpatial;`
- L51 _public member_ `bool bTriangleMode = false;`
- L59 _public member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic;` — `UPROPERTY()` — The activity may use the selection mechanic to get (or alter) the current selection, though if selection is just being changed at the end of the activity, it should probably be done through EmitCurrentMeshChangeAndUpdate so that it is lumped with the same undo transaction.
- L70 _public member_ `EmitCurrentMeshChangeAndUpdate;`
- L76 _public member_ `TUniqueFunction<void(const FText& TransactionLabel)> EmitActivityStart;` — If an activity starts running, it should use this function to have the host emit an appropriate undoable transaction with the given transaction label.
- L84 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUndoRedo, bool bGroupTopologyChanged);` — Gets broadcast when the CurrentMesh is modified by an undo/redo transaction emitted via EmitCurrentMeshChangeAndUpdate. Only activities that issue multiple transactions via EmitCurrentMeshChangeAndUpdate during the same invocation need to use this, since a transaction that ends immediately after the call will not have to deal with the undo.
- L85 _public member_ `FOnUndoRedo OnUndoRedo;`

#### Free symbols / members of external scopes

- L12 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L13 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMeshChange);`
- L14 _prototype_ `PREDECLARE_GEOMETRY(struct FGroupTopologySelection);`
- L15 _prototype_ `PREDECLARE_GEOMETRY(class FGroupTopology);`
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUndoRedo, bool bGroupTopologyChanged);` — Gets broadcast when the CurrentMesh is modified by an undo/redo transaction emitted via EmitCurrentMeshChangeAndUpdate. Only activities that issue multiple transactions via EmitCurrentMeshChangeAndUpdate during the same invocation need to use this, since a transaction that ends immediately after the call will not have to deal with the undo.

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditActivityUtil.h` (Public)


#### enum `UE::Geometry::PolyEditActivityUtil::EPreviewMaterialType`  
`enum class EPreviewMaterialType`  
_L15-18_
- L17 _public enumerator_ `SourceMaterials`
- L17 _public enumerator_ `SourceMaterials`
- L17 _public enumerator_ `SourceMaterials`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
- L13 _namespace_ `namespace PolyEditActivityUtil` (scope `UE::Geometry`)
- L20 _prototype_ `UPolyEditPreviewMesh* CreatePolyEditPreviewMesh(UInteractiveTool& Tool, const UPolyEditActivityContext& ActivityContext);` (scope `UE::Geometry::PolyEditActivityUtil`)
- L22 _prototype_ `void UpdatePolyEditPreviewMaterials(UInteractiveTool& Tool, const UPolyEditActivityContext& ActivityContext, UPolyEditPreviewMesh& EditPreviewMesh, EPreviewMaterialType MaterialType);` (scope `UE::Geometry::PolyEditActivityUtil`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditCutFacesActivity.h` (Public)


#### enum `EPolyEditCutPlaneOrientation`  
`enum class EPolyEditCutPlaneOrientation`  
_L21-25_
- reflection: `UENUM()`
- L23 _public enumerator_ `FaceNormals`
- L24 _public enumerator_ `ViewDirection`

#### class `UPolyEditCutProperties`  
`class UPolyEditCutProperties : public UInteractiveToolPropertySet`  
_L28-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L34 _public member_ `EPolyEditCutPlaneOrientation Orientation = EPolyEditCutPlaneOrientation::FaceNormals;` — `UPROPERTY(EditAnywhere, Category = Cut)`
- L37 _public member_ `bool bSnapToVertices = true;` — `UPROPERTY(EditAnywhere, Category = Cut)`

#### class `UPolyEditCutFacesActivity`  
`class UPolyEditCutFacesActivity : public UInteractiveToolActivity, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L45-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolActivity,IClickBehaviorTarget,IHoverBehaviorTarget`
- L52 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L53 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L54 _public prototype_ `virtual bool CanStart() const override;`
- L55 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L56 _public function_ `virtual bool IsRunning() const override`
- L57 _public prototype_ `virtual bool CanAccept() const override;`
- L58 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L59 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L60 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L63 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L64 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L67 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L68 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L69 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L70 _public function_ `virtual void OnEndHover() override`
- L73 _protected prototype_ `void Clear();`
- L74 _protected prototype_ `void BeginCutFaces();`
- L75 _protected prototype_ `void ApplyCutFaces();`
- L78 _protected member_ `TObjectPtr<UPolyEditCutProperties> CutProperties;` — `UPROPERTY()`
- L81 _protected member_ `TObjectPtr<UPolyEditPreviewMesh> EditPreview;` — `UPROPERTY()`
- L84 _protected member_ `TObjectPtr<UCollectSurfacePathMechanic> SurfacePathMechanic = nullptr;` — `UPROPERTY()`
- L87 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L89 _protected member_ `bool bIsRunning = false;`
- L90 _protected member_ `int32 ActivityStamp = 1;`
- L92 _protected member_ `FViewCameraState CameraState;`

#### class `FPolyEditCutFacesActivityFirstPointChange`  
`class FPolyEditCutFacesActivityFirstPointChange : public FToolCommandChange`  
_L100-121_
- inherits: `FToolCommandChange`
- desc: This should get emitted when setting the first point so that we can undo it.
- L103 _public function_ `FPolyEditCutFacesActivityFirstPointChange(int32 CurrentActivityStamp) : ActivityStamp(CurrentActivityStamp)`
- L107 _public function_ `virtual void Apply(UObject* Object) override`
- L108 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L109 _public function_ `virtual bool HasExpired(UObject* Object) const override`
- L113 _public function_ `virtual FString ToString() const override`
- L119 _protected member_ `int32 ActivityStamp;`
- L120 _protected member_ `bool bHaveDoneUndo = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditExtrudeActivity.h` (Public)


#### enum `EPolyEditExtrudeDirection`  
`enum class EPolyEditExtrudeDirection`  
_L24-33_
- reflection: `UENUM()`
- L26 _public enumerator_ `SelectionNormal`
- L27 _public enumerator_ `WorldX`
- L28 _public enumerator_ `WorldY`
- L29 _public enumerator_ `WorldZ`
- L30 _public enumerator_ `LocalX`
- L31 _public enumerator_ `LocalY`
- L32 _public enumerator_ `LocalZ`

#### enum `EPolyEditExtrudeDistanceMode`  
`enum class EPolyEditExtrudeDistanceMode`  
_L36-46_
- reflection: `UENUM()`
- L39 _public enumerator_ `ClickInViewport` — Set distance by clicking in the viewport.
- L42 _public enumerator_ `Fixed` — Set distance with an explicit numerical value, then explictly accept.

#### enum `EPolyEditExtrudeModeOptions`  
`enum class EPolyEditExtrudeModeOptions`  
_L63-75_
- reflection: `UENUM()`
- L66 _public enumerator_ `SingleDirection = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::SingleDirection)` — Extrude all triangles in the same direction regardless of their facing.
- L70 _public enumerator_ `SelectedTriangleNormals = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::SelectedTriangleNormals)` — Take the angle-weighed average of the selected triangles around each extruded vertex to determine vertex movement direction.
- L74 _public enumerator_ `SelectedTriangleNormalsEven = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::SelectedTriangleNormalsEven)` — Like Selected Triangle Normals, but also adjusts the distances moved in an attempt to keep triangles parallel to their original facing.

#### enum `EPolyEditOffsetModeOptions`  
`enum class EPolyEditOffsetModeOptions`  
_L78-90_
- reflection: `UENUM()`
- L81 _public enumerator_ `VertexNormals = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::VertexNormals)` — Vertex normals, regardless of selection.
- L85 _public enumerator_ `SelectedTriangleNormals = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::SelectedTriangleNormals)` — Take the angle-weighed average of the selected triangles around offset vertex to determine vertex movement direction.
- L89 _public enumerator_ `SelectedTriangleNormalsEven = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::SelectedTriangleNormalsEven)` — Like Selected Triangle Normals, but also adjusts the distances moved in an attempt to keep triangles parallel to their original facing.

#### enum `EPolyEditPushPullModeOptions`  
`enum class EPolyEditPushPullModeOptions`  
_L93-108_
- reflection: `UENUM()`
- L97 _public enumerator_ `SelectedTriangleNormals = static_cast<int>(EPolyEditOffsetModeOptions::SelectedTriangleNormals)` — Take the angle-weighed average of the selected triangles around offset vertex to determine vertex movement direction.
- L101 _public enumerator_ `SelectedTriangleNormalsEven = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::SelectedTriangleNormalsEven)` — Like Selected Triangle Normals, but also adjusts the distances moved in an attempt to keep triangles parallel to their original facing.
- L104 _public enumerator_ `SingleDirection = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::SingleDirection)` — Move all triangles in the same direction regardless of their facing.
- L107 _public enumerator_ `VertexNormals = static_cast<int>(UE::Geometry::FExtrudeOp::EDirectionMode::VertexNormals)` — Vertex normals, regardless of selection.

#### class `UPolyEditExtrudeProperties`  
`class UPolyEditExtrudeProperties : public UInteractiveToolPropertySet`  
_L111-156_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L118 _public member_ `EPolyEditExtrudeDistanceMode DistanceMode = EPolyEditExtrudeDistanceMode::ClickInViewport;` — `UPROPERTY(EditAnywhere, Category = Extrude)` — How the extrude distance is set.
- L123 _public member_ `double Distance = 100;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (UIMin = "-1000", UIMax = "1000", ClampMin = "-10000", ClampMax = "10000", EditConditionHides, EditCondition = "DistanceMode == EPolyEditExtrudeDistanceMode::Fixed"))` — Distance to extrude.
- L127 _public member_ `EPolyEditExtrudeModeOptions DirectionMode = EPolyEditExtrudeModeOptions::SingleDirection;` — `UPROPERTY(EditAnywhere, Category = Extrude)` — How to move the vertices during the extrude
- L132 _public member_ `EPolyEditExtrudeDirection Direction = EPolyEditExtrudeDirection::SelectionNormal;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (EditConditionHides, EditCondition = "DirectionMode == EPolyEditExtrudeModeOptions::SingleDirection"))` — Direction in which to extrude.
- L137 _public member_ `double MaxDistanceScaleFactor = 4.0;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = (ClampMin = "1", EditConditionHides, EditCondition = "DirectionMode == EPolyEditExtrudeModeOptions::SelectedTriangleNormalsEven"))` — Controls the maximum distance vertices can move from the target distance in order to stay parallel with their source triangles.
- L141 _public member_ `bool bShellsToSolids = true;` — `UPROPERTY(EditAnywhere, Category = Extrude)` — Controls whether extruding an entire open-border patch should create a solid or an open shell
- L146 _public member_ `EPolyEditExtrudeDirection MeasureDirection = EPolyEditExtrudeDirection::SelectionNormal;` — `UPROPERTY(EditAnywhere, Category = Extrude, AdvancedDisplay, meta = (EditConditionHides, EditCondition = "DirectionMode != EPolyEditExtrudeModeOptions::SingleDirection && DistanceMode == EPolyEditExtrudeDistanceMode::ClickInViewport"))` — What axis to measure the extrusion distance along.
- L155 _public member_ `bool bUseColinearityForSettingBorderGroups = true;` — `UPROPERTY(EditAnywhere, Category = Extrude, AdvancedDisplay)` — When extruding regions that touch the mesh border, assign the side groups (groups on the stitched side of the extrude) in a way that considers edge colinearity. For instance, when true, extruding a flat rectangle will give four different groups on its sides rather than one connected group.

#### class `UPolyEditOffsetProperties`  
`class UPolyEditOffsetProperties : public UInteractiveToolPropertySet`  
_L159-199_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L166 _public member_ `EPolyEditExtrudeDistanceMode DistanceMode = EPolyEditExtrudeDistanceMode::ClickInViewport;` — `UPROPERTY(EditAnywhere, Category = Offset)` — How the offset distance is set.
- L171 _public member_ `double Distance = 100;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (EditConditionHides, EditCondition = "DistanceMode == EPolyEditExtrudeDistanceMode::Fixed"))` — Offset distance.
- L175 _public member_ `EPolyEditOffsetModeOptions DirectionMode = EPolyEditOffsetModeOptions::VertexNormals;` — `UPROPERTY(EditAnywhere, Category = Offset)` — Which way to move vertices during the offset
- L180 _public member_ `double MaxDistanceScaleFactor = 4.0;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (ClampMin = "1", EditConditionHides, EditCondition = "DirectionMode == EPolyEditOffsetModeOptions::SelectedTriangleNormalsEven"))` — Controls the maximum distance vertices can move from the target distance in order to stay parallel with their source triangles.
- L184 _public member_ `bool bShellsToSolids = true;` — `UPROPERTY(EditAnywhere, Category = Offset)` — Controls whether offsetting an entire open-border patch should create a solid or an open shell
- L189 _public member_ `EPolyEditExtrudeDirection MeasureDirection = EPolyEditExtrudeDirection::SelectionNormal;` — `UPROPERTY(EditAnywhere, Category = Offset, AdvancedDisplay, meta = (EditConditionHides, EditCondition = "DistanceMode == EPolyEditExtrudeDistanceMode::ClickInViewport"))` — What axis to measure the offset distance along.
- L198 _public member_ `bool bUseColinearityForSettingBorderGroups = true;` — `UPROPERTY(EditAnywhere, Category = Offset, AdvancedDisplay)` — When offsetting regions that touch the mesh border, assign the side groups (groups on the stitched side of the offset) in a way that considers edge colinearity. For instance, when true, extruding a flat rectangle will give four different groups on its sides rather than one connected group.

#### class `UPolyEditPushPullProperties`  
`class UPolyEditPushPullProperties : public UInteractiveToolPropertySet`  
_L202-247_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L209 _public member_ `EPolyEditExtrudeDistanceMode DistanceMode = EPolyEditExtrudeDistanceMode::ClickInViewport;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions)` — How the extrusion distance is set.
- L214 _public member_ `double Distance = 100;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions, meta = (EditConditionHides, EditCondition = "DistanceMode == EPolyEditExtrudeDistanceMode::Fixed"))` — Extrusion distance.
- L218 _public member_ `EPolyEditPushPullModeOptions DirectionMode = EPolyEditPushPullModeOptions::SelectedTriangleNormals;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions)` — Which way to move vertices while extruding.
- L223 _public member_ `EPolyEditExtrudeDirection SingleDirection = EPolyEditExtrudeDirection::SelectionNormal;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions, meta = (DisplayName="Direction", EditConditionHides, EditCondition = "DirectionMode == EPolyEditPushPullModeOptions::SingleDirection"))` — Direction in which to extrude.
- L228 _public member_ `double MaxDistanceScaleFactor = 4.0;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions, meta = (ClampMin = "1", EditConditionHides, EditCondition = "DirectionMode == EPolyEditPushPullModeOptions::SelectedTriangleNormalsEven"))` — Controls the maximum distance vertices can move from the target distance in order to stay parallel with their source triangles.
- L232 _public member_ `bool bShellsToSolids = true;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions)` — Controls whether offsetting an entire open-border patch should create a solid or an open shell
- L237 _public member_ `EPolyEditExtrudeDirection MeasureDirection = EPolyEditExtrudeDirection::SelectionNormal;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions, AdvancedDisplay, meta = (EditConditionHides, EditCondition = "DirectionMode != EPolyEditPushPullModeOptions::SingleDirection && DistanceMode == EPolyEditExtrudeDistanceMode::ClickInViewport"))` — What axis to measure the extrusion distance along.
- L246 _public member_ `bool bUseColinearityForSettingBorderGroups = true;` — `UPROPERTY(EditAnywhere, Category = ExtrusionOptions, AdvancedDisplay)` — When offsetting regions that touch the mesh border, assign the side groups (groups on the stitched side of the extrude) in a way that considers edge colinearity. For instance, when true, extruding a flat rectangle will give four different groups on its sides rather than one connected group.

#### class `UPolyEditExtrudeActivity`  
`class UPolyEditExtrudeActivity : public UInteractiveToolActivity, public UE::Geometry::IDynamicMeshOperatorFactory, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L253-333_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolActivity,UE::Geometry::IDynamicMeshOperatorFactory,IClickBehaviorTarget,IHoverBehaviorTarget`
- L261 _public typedef_ `using FExtrudeOp = UE::Geometry::FExtrudeOp;`
- L272 _public member_ `FExtrudeOp::EExtrudeMode ExtrudeMode = FExtrudeOp::EExtrudeMode::MoveAndStitch;` — Set to different values depending on whether we're using this activity on behalf of extrude, offset, or push/pull
- L273 _public member_ `EPropertySetToUse PropertySetToUse = EPropertySetToUse::Extrude;`
- L276 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L277 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L278 _public prototype_ `virtual bool CanStart() const override;`
- L279 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L280 _public function_ `virtual bool IsRunning() const override`
- L281 _public function_ `virtual bool HasAccept() const`
- L282 _public prototype_ `virtual bool CanAccept() const override;`
- L283 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L284 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L285 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L288 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L291 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L292 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L295 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L296 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L297 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L298 _public function_ `virtual void OnEndHover() override`
- L301 _public member_ `TObjectPtr<UPolyEditExtrudeProperties> ExtrudeProperties = nullptr;` — `UPROPERTY()`
- L304 _public member_ `TObjectPtr<UPolyEditOffsetProperties> OffsetProperties = nullptr;` — `UPROPERTY()`
- L307 _public member_ `TObjectPtr<UPolyEditPushPullProperties> PushPullProperties = nullptr;` — `UPROPERTY()`
- L311 _protected prototype_ `FVector3d GetExtrudeDirection() const;`
- L312 _protected prototype_ `virtual void BeginExtrude();`
- L313 _protected prototype_ `virtual void ApplyExtrude();`
- L314 _protected prototype_ `virtual void ReinitializeExtrudeHeightMechanic();`
- L315 _protected prototype_ `virtual void EndInternal();`
- L318 _protected member_ `TObjectPtr<UPlaneDistanceFromHitMechanic> ExtrudeHeightMechanic = nullptr;` — `UPROPERTY()`
- L321 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L323 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> PatchMesh;`
- L324 _protected member_ `TArray<int32> NewSelectionGids;`
- L326 _protected member_ `bool bIsRunning = false;`
- L328 _protected member_ `UE::Geometry::FGroupTopologySelection ActiveSelection;`
- L329 _protected member_ `UE::Geometry::FFrame3d ActiveSelectionFrameWorld;`
- L330 _protected member_ `float UVScaleFactor = 1.0f;`
- L332 _protected member_ `bool bRequestedApply = false;`

#### enum `UPolyEditExtrudeActivity::EPropertySetToUse`  
`enum class EPropertySetToUse`  
_L263-268_
- L265 _public enumerator_ `Extrude`
- L266 _public enumerator_ `Offset`
- L267 _public enumerator_ `PushPull`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L21 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditInsertEdgeActivity.h` (Public)


#### enum `EGroupEdgeInsertionMode`  
`enum class EGroupEdgeInsertionMode`  
_L27-35_
- reflection: `UENUM()`
- L31 _public enumerator_ `Retriangulate` — Existing groups will be deleted and new triangles will be created for the new groups. Keeps topology simple but breaks non-planar groups.
- L34 _public enumerator_ `PlaneCut` — Keeps existing triangles and cuts them to create a new path. May result in fragmented triangles over time.

#### class `UGroupEdgeInsertionProperties`  
`class UGroupEdgeInsertionProperties : public UInteractiveToolPropertySet`  
_L38-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L45 _public member_ `EGroupEdgeInsertionMode InsertionMode = EGroupEdgeInsertionMode::PlaneCut;` — `UPROPERTY(EditAnywhere, Category = InsertEdge)` — Determines how group edges are added to the geometry
- L49 _public member_ `bool bContinuousInsertion = true;` — `UPROPERTY(EditAnywhere, Category = InsertEdge)` — If true, edge insertions are chained together so that each end point becomes the new start point
- L53 _public member_ `double VertexTolerance = 0.001;` — `UPROPERTY(EditAnywhere, Category = InsertEdge, AdvancedDisplay, meta = (UIMin = "0", UIMax = "0.01", ClampMin = "0", ClampMax = "10"))` — How close a new loop edge needs to pass next to an existing vertex to use that vertex rather than creating a new one (used for plane cut).

#### class `UPolyEditInsertEdgeActivity`  
`class UPolyEditInsertEdgeActivity : public UInteractiveToolActivity, public UE::Geometry::IDynamicMeshOperatorFactory, public IHoverBehaviorTarget, public IClickBehaviorTarget`  
_L58-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolActivity,UE::Geometry::IDynamicMeshOperatorFactory,IHoverBehaviorTarget,IClickBehaviorTarget`
- desc: Interactive activity for inserting a group edge into a mesh.
- L64 _private typedef_ `using FGroupEdgeInserter = UE::Geometry::FGroupEdgeInserter;`
- L65 _private typedef_ `using FDynamicMesh3 = UE::Geometry::FDynamicMesh3;`
- L78 _public function_ `UPolyEditInsertEdgeActivity()`
- L80 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property);`
- L83 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L84 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L85 _public prototype_ `virtual bool CanStart() const override;`
- L86 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L87 _public function_ `virtual bool IsRunning() const override`
- L88 _public prototype_ `virtual bool CanAccept() const override;`
- L89 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L90 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L91 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L94 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L97 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget
- L98 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L101 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget
- L102 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L103 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L104 _public prototype_ `virtual void OnEndHover() override;`
- L108 _protected member_ `TObjectPtr<UGroupEdgeInsertionProperties> Settings = nullptr;` — `UPROPERTY()`
- L111 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L113 _protected member_ `bool bIsRunning = false;`
- L115 _protected member_ `FTransform TargetTransform;`
- L116 _protected member_ `TSharedPtr<FMeshTopologySelector, ESPMode::ThreadSafe> TopologySelector;`
- L118 _protected member_ `TArray<TPair<FVector3d, FVector3d>> PreviewEdges;`
- L119 _protected member_ `TArray<FVector3d> PreviewPoints;`
- L121 _protected member_ `FViewCameraState CameraState;`
- L123 _protected member_ `FToolDataVisualizer ExistingEdgesRenderer;`
- L124 _protected member_ `FToolDataVisualizer PreviewEdgeRenderer;`
- L125 _protected member_ `FMeshTopologySelector::FSelectionSettings TopologySelectorSettings;`
- L129 _protected member_ `FGroupEdgeInserter::FGroupEdgeSplitPoint StartPoint;` — Inputs from user interaction:
- L130 _protected member_ `int32 StartTopologyID = FDynamicMesh3::InvalidID;`
- L131 _protected member_ `bool bStartIsCorner = false;`
- L133 _protected member_ `FGroupEdgeInserter::FGroupEdgeSplitPoint EndPoint;`
- L134 _protected member_ `int32 EndTopologyID = FDynamicMesh3::InvalidID;`
- L135 _protected member_ `bool bEndIsCorner = false;`
- L137 _protected member_ `int32 CommonGroupID = FDynamicMesh3::InvalidID;`
- L138 _protected member_ `int32 CommonBoundaryIndex = FDynamicMesh3::InvalidID;`
- L140 _protected member_ `FRay LastEndPointWorldRay;`
- L143 _protected member_ `EState ToolState = EState::GettingStart;` — State control:
- L145 _protected member_ `bool bShowingBaseMesh = false;`
- L146 _protected member_ `bool bLastComputeSucceeded = false;`
- L147 _protected member_ `TSharedPtr<UE::Geometry::FGroupTopology, ESPMode::ThreadSafe> LatestOpTopologyResult;`
- L148 _protected member_ `TSharedPtr<TSet<int32>, ESPMode::ThreadSafe> LatestOpChangedTids;`
- L150 _protected member_ `int32 CurrentChangeStamp = 0;`
- L153 _protected member_ `TSharedPtr<const UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> ComputeStartMesh;` — Safe inputs for the background compute to use, untouched by undo/redo/other CurrentMesh updates.
- L154 _protected member_ `TSharedPtr<const UE::Geometry::FGroupTopology, ESPMode::ThreadSafe> ComputeStartTopology;`
- L155 _protected prototype_ `void UpdateComputeInputs();`
- L157 _protected prototype_ `void SetupPreview();`
- L159 _protected prototype_ `bool TopologyHitTest(const FRay& WorldRay, FVector3d& RayPositionOut, FRay3d* LocalRayOut = nullptr);`
- L160 _protected prototype_ `bool GetHoveredItem(const FRay& WorldRay, FGroupEdgeInserter::FGroupEdgeSplitPoint& PointOut, int32& TopologyElementIDOut, bool& bIsCornerOut, FVector3d& PositionOut, FRay3d* LocalRayOut = nullptr);`
- L163 _protected prototype_ `void ConditionallyUpdatePreview(const FGroupEdgeInserter::FGroupEdgeSplitPoint& NewEndPoint, int32 NewEndTopologyID, bool bNewEndIsCorner, int32 NewCommonGroupID, int32 NewBoundaryIndex);`
- L166 _protected prototype_ `void ClearPreview(bool bClearDrawnElements);`
- L168 _protected prototype_ `void GetCornerTangent(int32 CornerID, int32 GroupID, int32 BoundaryIndex, FVector3d& TangentOut);`
- L174 _protected function_ `inline void ExpireChanges()` — Expires the tool-associated changes in the undo/redo stack. The ComponentTarget changes will stay (we want this).

#### enum `UPolyEditInsertEdgeActivity::EState`  
`enum class EState`  
_L67-72_
- L69 _public enumerator_ `GettingStart`
- L70 _public enumerator_ `GettingEnd`
- L71 _public enumerator_ `WaitingForInsertComplete`

#### class `FGroupEdgeInsertionFirstPointChange`  
`class FGroupEdgeInsertionFirstPointChange : public FToolCommandChange`  
_L183-208_
- inherits: `FToolCommandChange`
- desc: This should get emitted when selecting the first point in an edge insertion so that we can undo it.
- L186 _public function_ `FGroupEdgeInsertionFirstPointChange(int32 CurrentChangeStamp) : ChangeStamp(CurrentChangeStamp)`
- L190 _public function_ `virtual void Apply(UObject* Object) override`
- L191 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L192 _public function_ `virtual bool HasExpired(UObject* Object) const override`
- L200 _public function_ `virtual FString ToString() const override`
- L206 _protected member_ `int32 ChangeStamp;`
- L207 _protected member_ `bool bHaveDoneUndo = false;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L23 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMeshChange);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditInsertEdgeLoopActivity.h` (Public)


#### enum `EEdgeLoopPositioningMode`  
`enum class EEdgeLoopPositioningMode`  
_L26-37_
- reflection: `UENUM()`
- L29 _public enumerator_ `Even` — Edge loops will be evenly centered within a group. Allows for multiple insertions at a time.
- L32 _public enumerator_ `ProportionOffset` — Edge loops will fall at the same length proportion at each edge they intersect (e.g., a quarter way down).
- L36 _public enumerator_ `DistanceOffset` — Edge loops will fall a constant distance away from the start of each edge they intersect (e.g., 20 units down). Clamps to end if edge is too short.

#### enum `EEdgeLoopInsertionMode`  
`enum class EEdgeLoopInsertionMode`  
_L40-48_
- reflection: `UENUM()`
- L44 _public enumerator_ `Retriangulate` — Existing groups will be deleted and new triangles will be created for the new groups. Keeps topology simple but breaks non-planar groups.
- L47 _public enumerator_ `PlaneCut` — Keeps existing triangles and cuts them to create a new path. May result in fragmented triangles over time.

#### class `UEdgeLoopInsertionProperties`  
`class UEdgeLoopInsertionProperties : public UInteractiveToolPropertySet`  
_L51-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L58 _public member_ `EEdgeLoopPositioningMode PositionMode = EEdgeLoopPositioningMode::ProportionOffset;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop)` — Determines how edge loops position themselves vertically relative to loop direction.
- L62 _public member_ `EEdgeLoopInsertionMode InsertionMode = EEdgeLoopInsertionMode::PlaneCut;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop)` — Determines how edge loops are added to the geometry
- L67 _public member_ `int32 NumLoops = 1;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop, meta = (UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "500", EditCondition = "PositionMode == EEdgeLoopPositioningMode::Even", EditConditionHides))` — How many loops to insert at a time. Only used with "even" positioning mode.
- L71 _public member_ `double ProportionOffset = 0.5;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop, AdvancedDisplay, meta = (UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "1.0", EditCondition = "PositionMode == EEdgeLoopPositioningMode::ProportionOffset && !bInteractive", EditConditionHides))`
- L75 _public member_ `double DistanceOffset = 10.0;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop, AdvancedDisplay, meta = (UIMin = "0", ClampMin = "0", EditCondition = "PositionMode == EEdgeLoopPositioningMode::DistanceOffset && !bInteractive", EditConditionHides))`
- L80 _public member_ `bool bInteractive = true;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop, AdvancedDisplay, meta = ( EditCondition = "PositionMode != EEdgeLoopPositioningMode::Even", EditConditionHides))` — When false, the distance/proportion offset is numerically specified, and mouse clicks just choose the edge.
- L85 _public member_ `bool bFlipOffsetDirection = false;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop, meta = ( EditCondition = "PositionMode == EEdgeLoopPositioningMode::DistanceOffset", EditConditionHides))` — Measure the distance offset from the opposite side of the edges.
- L89 _public member_ `bool bHighlightProblemGroups = true;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop)` — When true, non-quad-like groups that stop the loop will be highlighted, with X's marking the corners.
- L93 _public member_ `double VertexTolerance = 0.001;` — `UPROPERTY(EditAnywhere, Category = InsertEdgeLoop, AdvancedDisplay, meta = (UIMin = "0", UIMax = "0.01", ClampMin = "0", ClampMax = "10"))` — How close a new loop edge needs to pass next to an existing vertex to use that vertex rather than creating a new one.

#### class `UPolyEditInsertEdgeLoopActivity`  
`class UPolyEditInsertEdgeLoopActivity : public UInteractiveToolActivity, public UE::Geometry::IDynamicMeshOperatorFactory, public IHoverBehaviorTarget, public IClickBehaviorTarget`  
_L98-185_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolActivity,UE::Geometry::IDynamicMeshOperatorFactory,IHoverBehaviorTarget,IClickBehaviorTarget`
- desc: Interactive activity for inserting (group) edge loops into a mesh.
- L107 _public function_ `UPolyEditInsertEdgeLoopActivity()`
- L109 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property);`
- L112 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L113 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L114 _public prototype_ `virtual bool CanStart() const override;`
- L115 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L116 _public function_ `virtual bool IsRunning() const override`
- L117 _public prototype_ `virtual bool CanAccept() const override;`
- L118 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L119 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L120 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L123 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L126 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget
- L127 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L130 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget
- L131 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L132 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L133 _public prototype_ `virtual void OnEndHover() override;`
- L137 _protected member_ `TObjectPtr<UEdgeLoopInsertionProperties> Settings = nullptr;` — `UPROPERTY()`
- L140 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L142 _protected member_ `bool bIsRunning = false;`
- L144 _protected member_ `FTransform TargetTransform;`
- L145 _protected member_ `TSharedPtr<FMeshTopologySelector, ESPMode::ThreadSafe> TopologySelector;`
- L147 _protected member_ `TArray<TPair<FVector3d, FVector3d>> PreviewEdges;`
- L150 _protected member_ `TArray<TPair<FVector3d, FVector3d>> ProblemTopologyEdges;` — Used to highlight problematic topology (non-quad groups) when it stops a loop.
- L151 _protected member_ `TArray<FVector3d> ProblemTopologyVerts;`
- L153 _protected member_ `FViewCameraState CameraState;`
- L155 _protected member_ `FToolDataVisualizer PreviewEdgeRenderer;`
- L156 _protected member_ `FToolDataVisualizer ProblemTopologyRenderer;`
- L157 _protected member_ `FMeshTopologySelector::FSelectionSettings TopologySelectorSettings;`
- L158 _protected member_ `float ProblemVertTickWidth = 8;`
- L160 _protected prototype_ `void SetupPreview();`
- L162 _protected prototype_ `FInputRayHit HitTest(const FRay& WorldRay);`
- L163 _protected prototype_ `bool UpdateHoveredItem(const FRay& WorldRay);`
- L166 _protected member_ `TSharedPtr<const UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> ComputeStartMesh;` — Safe inputs for the background compute to use, untouched by undo/redo/other CurrentMesh updates.
- L167 _protected member_ `TSharedPtr<const UE::Geometry::FGroupTopology, ESPMode::ThreadSafe> ComputeStartTopology;`
- L168 _protected prototype_ `void UpdateComputeInputs();`
- L170 _protected prototype_ `void ConditionallyUpdatePreview(int32 NewGroupID, double* NewInputLength = nullptr);`
- L171 _protected prototype_ `void ClearPreview();`
- L174 _protected member_ `int32 InputGroupEdgeID = FDynamicMesh3::InvalidID;` — Taken from user interaction, read as inputs by the op factory
- L175 _protected member_ `double InteractiveInputLength = 0;`
- L179 _protected member_ `bool bWaitingForInsertionCompletion = false;` — On valid clicks, we wait to finish the background op and apply it before taking more input. Gets reset OnTick when the result is ready.
- L182 _protected member_ `bool bLastComputeSucceeded = false;` — Copied over on op completion
- L183 _protected member_ `TSharedPtr<UE::Geometry::FGroupTopology, ESPMode::ThreadSafe> LatestOpTopologyResult;`
- L184 _protected member_ `TSharedPtr<TSet<int32>, ESPMode::ThreadSafe> LatestOpChangedTids;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L22 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMeshChange);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditInsetOutsetActivity.h` (Public)


#### class `UPolyEditInsetOutsetProperties`  
`class UPolyEditInsetOutsetProperties : public UInteractiveToolPropertySet`  
_L19-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L27 _public member_ `float Softness = 0.5;` — `UPROPERTY(EditAnywhere, Category = "Region", meta = (UIMin = "0.0", UIMax = "1.0", EditCondition = "bBoundaryOnly == false"))` — Amount of smoothing applied to the boundary
- L31 _public member_ `bool bBoundaryOnly = false;` — `UPROPERTY(EditAnywhere, Category = "Region", AdvancedDisplay)` — Controls whether operation will move interior vertices as well as border vertices
- L36 _public member_ `float AreaScale = true;` — `UPROPERTY(EditAnywhere, Category = "Region", AdvancedDisplay, meta = (UIMin = "0.0", UIMax = "1.0", EditCondition = "bBoundaryOnly == false"))` — Tweak area scaling when solving for interior vertices
- L40 _public member_ `bool bReproject = true;` — `UPROPERTY(EditAnywhere, Category = "Region", Meta = (EditCondition = "!bOutset", HideEditConditionToggle, EditConditionHides))` — When insetting, determines whether vertices in inset region should be projected back onto input surface
- L48 _public member_ `bool bOutset = false;` — `UPROPERTY()`

#### class `UPolyEditInsetOutsetActivity`  
`class UPolyEditInsetOutsetActivity : public UInteractiveToolActivity, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L56-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolActivity,IClickBehaviorTarget,IHoverBehaviorTarget`
- L63 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L64 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L65 _public prototype_ `virtual bool CanStart() const override;`
- L66 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L67 _public function_ `virtual bool IsRunning() const override`
- L68 _public prototype_ `virtual bool CanAccept() const override;`
- L69 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L70 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L71 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L74 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L75 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L78 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L79 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L80 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L81 _public function_ `virtual void OnEndHover() override`
- L84 _public member_ `TObjectPtr<UPolyEditInsetOutsetProperties> Settings;` — `UPROPERTY()`
- L87 _protected prototype_ `void Clear();`
- L88 _protected prototype_ `bool BeginInset();`
- L89 _protected prototype_ `void ApplyInset();`
- L91 _protected member_ `bool bIsRunning = false;`
- L92 _protected member_ `bool bPreviewUpdatePending = false;`
- L95 _protected member_ `TObjectPtr<UPolyEditPreviewMesh> EditPreview;` — `UPROPERTY()`
- L98 _protected member_ `TObjectPtr<USpatialCurveDistanceMechanic> CurveDistMechanic = nullptr;` — `UPROPERTY()`
- L101 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L103 _protected member_ `float UVScaleFactor = 1.0f;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/ToolActivities/PolyEditPlanarProjectionUVActivity.h` (Public)


#### class `UPolyEditSetUVProperties`  
`class UPolyEditSetUVProperties : public UInteractiveToolPropertySet`  
_L22-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L28 _public member_ `bool bShowMaterial = false;` — `UPROPERTY(EditAnywhere, Category = PlanarProjectUV)`

#### class `UPolyEditPlanarProjectionUVActivity`  
`class UPolyEditPlanarProjectionUVActivity : public UInteractiveToolActivity, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L36-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolActivity,IClickBehaviorTarget,IHoverBehaviorTarget`
- L43 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;` — IInteractiveToolActivity
- L44 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L45 _public prototype_ `virtual bool CanStart() const override;`
- L46 _public prototype_ `virtual EToolActivityStartResult Start() override;`
- L47 _public function_ `virtual bool IsRunning() const override`
- L48 _public prototype_ `virtual bool CanAccept() const override;`
- L49 _public prototype_ `virtual EToolActivityEndResult End(EToolShutdownType) override;`
- L50 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L51 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L54 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L55 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L58 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L59 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L60 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L61 _public function_ `virtual void OnEndHover() override`
- L64 _protected prototype_ `void Clear();`
- L65 _protected prototype_ `void BeginSetUVs();`
- L66 _protected prototype_ `void UpdateSetUVS();`
- L67 _protected prototype_ `void ApplySetUVs();`
- L70 _protected member_ `TObjectPtr<UPolyEditSetUVProperties> SetUVProperties;` — `UPROPERTY()`
- L73 _protected member_ `TObjectPtr<UPolyEditPreviewMesh> EditPreview;` — `UPROPERTY()`
- L76 _protected member_ `TObjectPtr<UCollectSurfacePathMechanic> SurfacePathMechanic = nullptr;` — `UPROPERTY()`
- L79 _protected member_ `TObjectPtr<UPolyEditActivityContext> ActivityContext;` — `UPROPERTY()`
- L81 _protected member_ `bool bIsRunning = false;`
- L83 _protected member_ `bool bPreviewUpdatePending = false;`
- L84 _protected member_ `UE::Geometry::PolyEditActivityUtil::EPreviewMaterialType CurrentPreviewMaterial;`
- L85 _protected member_ `UE::Geometry::FAxisAlignedBox3d ActiveSelectionBounds;`
- L86 _protected member_ `FViewCameraState CameraState;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/UVLayoutTool.h` (Public)


#### class `UUVLayoutToolBuilder`  
`class UUVLayoutToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L33-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L38 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L39 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L42 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UUVLayoutTool`  
`class UUVLayoutTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L50-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: The level editor version of the UV layout tool.
- L56 _public prototype_ `UUVLayoutTool();`
- L58 _public prototype_ `virtual void Setup() override;`
- L59 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L61 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L62 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L64 _public function_ `virtual bool HasCancel() const override`
- L65 _public function_ `virtual bool HasAccept() const override`
- L66 _public prototype_ `virtual bool CanAccept() const override;`
- L68 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L70 _public prototype_ `int32 GetSelectedUVChannel() const;`
- L73 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L81 _protected member_ `TObjectPtr<UMeshUVChannelProperties> UVChannelProperties = nullptr;` — `UPROPERTY()`
- L84 _protected member_ `TObjectPtr<UUVLayoutProperties> BasicProperties = nullptr;` — `UPROPERTY()`
- L87 _protected member_ `TObjectPtr<UExistingMeshMaterialProperties> MaterialSettings = nullptr;` — `UPROPERTY()`
- L90 _protected member_ `TArray<TObjectPtr<UMeshOpPreviewWithBackgroundCompute>> Previews;` — `UPROPERTY()`
- L93 _protected member_ `TArray<TObjectPtr<UUVLayoutOperatorFactory>> Factories;` — `UPROPERTY()`
- L95 _protected member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe>> OriginalDynamicMeshes;`
- L97 _protected member_ `FViewCameraState CameraState;`
- L99 _protected prototype_ `void UpdateNumPreviews();`
- L101 _protected prototype_ `void UpdateVisualization();`
- L103 _protected prototype_ `void UpdatePreviewMaterial();`
- L105 _protected prototype_ `void OnPreviewMeshUpdated(UMeshOpPreviewWithBackgroundCompute* Compute);`
- L107 _protected prototype_ `void GenerateAsset(const TArray<FDynamicMeshOpResult>& Results);`
- L110 _protected member_ `TObjectPtr<UUVLayoutPreview> UVLayoutView = nullptr;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
- L27 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/UVProjectionTool.h` (Public)


#### class `UUVProjectionToolBuilder`  
`class UUVProjectionToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L33-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionToolBuilder`
- L37 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L39 _public function_ `virtual bool RequiresInputSelection() const override`
- L40 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EUVProjectionToolActions`  
`enum class EUVProjectionToolActions`  
_L45-51_
- reflection: `UENUM()`
- L47 _public enumerator_ `NoAction`
- L48 _public enumerator_ `AutoFit`
- L49 _public enumerator_ `AutoFitAlign`
- L50 _public enumerator_ `Reset`

#### class `UUVProjectionToolEditActions`  
`class UUVProjectionToolEditActions : public UInteractiveToolPropertySet`  
_L55-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L60 _public member_ `TWeakObjectPtr<UUVProjectionTool> ParentTool;`
- L62 _public function_ `void Initialize(UUVProjectionTool* ParentToolIn)`
- L63 _public prototype_ `void PostAction(EUVProjectionToolActions Action);`
- L67 _public function_ `void AutoFit()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "AutoFit", DisplayPriority = 1))` — Automatically fit the UV Projection Dimensions based on the current projection orientation
- L74 _public function_ `void AutoFitAlign()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "AutoFitAlign", DisplayPriority = 2))` — Automatically orient the projection and then automatically fit the UV Projection Dimensions
- L81 _public function_ `void Reset()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Reset", DisplayPriority = 3))` — Re-initialize the projection based on the UV Projection Initialization property

#### enum `EUVProjectionToolInitializationMode`  
`enum class EUVProjectionToolInitializationMode`  
_L89-99_
- reflection: `UENUM()`
- L92 _public enumerator_ `Default` — Initialize projection to bounding box center
- L94 _public enumerator_ `UsePrevious` — Initialize projection based on previous usage of the Project tool
- L96 _public enumerator_ `AutoFit` — Initialize projection using Auto Fitting for the initial projection type
- L98 _public enumerator_ `AutoFitAlign` — Initialize projection using Auto Fitting with Alignment for the initial projection type

#### class `UUVProjectionToolProperties`  
`class UUVProjectionToolProperties : public UInteractiveToolPropertySet`  
_L106-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties
- L113 _public member_ `EUVProjectionMethod ProjectionType = EUVProjectionMethod::Plane;` — `UPROPERTY(EditAnywhere, Category = "UV Projection")` — Shape and/or algorithm to use for UV projection
- L117 _public member_ `FVector Dimensions = FVector(100.0f, 100.0f, 100.0f);` — `UPROPERTY(EditAnywhere, Category = "UV Projection", meta = (Delta = 0.5, LinearDeltaSensitivity = 1))` — Width, length, and height of the projection shape before rotation
- L121 _public member_ `bool bProportionalDimensions = false;` — `UPROPERTY(EditAnywhere, Category = "UV Projection")` — If true, changes to Dimensions result in all components be changed proportionally
- L125 _public member_ `EUVProjectionToolInitializationMode Initialization = EUVProjectionToolInitializationMode::Default;` — `UPROPERTY(EditAnywhere, Category = "UV Projection")` — Determines how projection settings will be initialized; this only takes effect if the projection shape dimensions or position are unchanged
- L134 _public member_ `float CylinderSplitAngle = 45.0f;` — `UPROPERTY(EditAnywhere, Category = CylinderProjection, meta = (DisplayName = "Split Angle", UIMin = "0", UIMax = "90", EditCondition = "ProjectionType == EUVProjectionMethod::Cylinder", EditConditionHides))` — Angle in degrees to determine whether faces should be assigned to the cylinder or the flat end caps
- L143 _public member_ `float ExpMapNormalBlending = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "ExpMap Projection", meta = (DisplayName = "Normal Blending", UIMin = "0", UIMax = "1", EditCondition = "ProjectionType == EUVProjectionMethod::ExpMap", EditConditionHides))` — Blend between surface normals and projection normal; ExpMap projection becomes Plane projection when this value is 1
- L148 _public member_ `int ExpMapSmoothingSteps = 0;` — `UPROPERTY(EditAnywhere, Category = "ExpMap Projection", meta = (DisplayName = "Smoothing Steps", UIMin = "0", UIMax = "100", EditCondition = "ProjectionType == EUVProjectionMethod::ExpMap", EditConditionHides))` — Number of smoothing steps to apply; this slightly increases distortion but produces more stable results.
- L153 _public member_ `float ExpMapSmoothingAlpha = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "ExpMap Projection", meta = (DisplayName = "Smoothing Alpha", UIMin = "0", UIMax = "1", EditCondition = "ProjectionType == EUVProjectionMethod::ExpMap", EditConditionHides))` — Smoothing parameter; larger values result in faster smoothing in each step.
- L161 _public member_ `float Rotation = 0.0;` — `UPROPERTY(EditAnywhere, Category = "UV Transform", meta = (ClampMin = -360, ClampMax = 360))` — Rotation in degrees applied after computing projection
- L165 _public member_ `FVector2D Scale = FVector2D::UnitVector;` — `UPROPERTY(EditAnywhere, Category = "UV Transform", meta = (Delta = 0.01, LinearDeltaSensitivity = 1))` — Scaling applied after computing projection
- L169 _public member_ `FVector2D Translation = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "UV Transform")` — Translation applied after computing projection
- L176 _public member_ `FVector SavedDimensions = FVector::ZeroVector;` — `UPROPERTY()`
- L179 _public member_ `bool bSavedProportionalDimensions = false;` — `UPROPERTY()`
- L182 _public member_ `FTransform SavedTransform;` — `UPROPERTY()`

#### class `UUVProjectionOperatorFactory`  
`class UUVProjectionOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L191-200_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Factory with enough info to spawn the background-thread Operator to do a chunk of work for the tool stores a pointer to the tool and enough info to know which specific operator it should spawn
- L196 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L199 _public member_ `TObjectPtr<UUVProjectionTool> Tool;` — `UPROPERTY()`

#### class `UUVProjectionTool`  
`class UUVProjectionTool : public USingleTargetWithSelectionTool`  
_L207-316_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionTool`
- desc: UV projection tool
- L215 _public prototype_ `virtual void Setup() override;`
- L216 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L218 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L219 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L221 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L223 _public function_ `virtual bool HasCancel() const override`
- L224 _public function_ `virtual bool HasAccept() const override`
- L225 _public prototype_ `virtual bool CanAccept() const override;`
- L227 _public prototype_ `virtual void RequestAction(EUVProjectionToolActions ActionType);`
- L232 _protected member_ `TObjectPtr<UMeshUVChannelProperties> UVChannelProperties = nullptr;` — `UPROPERTY()`
- L235 _protected member_ `TObjectPtr<UUVProjectionToolProperties> BasicProperties = nullptr;` — `UPROPERTY()`
- L238 _protected member_ `TObjectPtr<UUVProjectionToolEditActions> EditActions = nullptr;` — `UPROPERTY()`
- L241 _protected member_ `TObjectPtr<UExistingMeshMaterialProperties> MaterialSettings = nullptr;` — `UPROPERTY()`
- L244 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L247 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> CheckerMaterial = nullptr;` — `UPROPERTY()`
- L250 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L253 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L256 _protected member_ `TObjectPtr<UUVProjectionOperatorFactory> OperatorFactory = nullptr;` — `UPROPERTY()`
- L259 _protected member_ `TObjectPtr<UPreviewGeometry> EdgeRenderer = nullptr;` — `UPROPERTY()`
- L261 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L262 _protected member_ `TSharedPtr<TArray<int32>, ESPMode::ThreadSafe> TriangleROI;`
- L263 _protected member_ `TSharedPtr<TArray<int32>, ESPMode::ThreadSafe> VertexROI;`
- L264 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> InputMeshROISpatial;`
- L265 _protected member_ `TSet<int32> TriangleROISet;`
- L267 _protected member_ `FTransform3d WorldTransform;`
- L268 _protected member_ `UE::Geometry::FAxisAlignedBox3d WorldBounds;`
- L270 _protected member_ `FVector CachedDimensions;`
- L271 _protected member_ `FVector InitialDimensions;`
- L272 _protected member_ `bool bInitialProportionalDimensions;`
- L273 _protected member_ `FTransform InitialTransform;`
- L274 _protected member_ `int32 DimensionsWatcher = -1;`
- L275 _protected member_ `int32 DimensionsModeWatcher = -1;`
- L276 _protected member_ `bool bTransformModified = false;`
- L277 _protected prototype_ `void OnInitializationModeChanged();`
- L278 _protected prototype_ `void ApplyInitializationMode();`
- L280 _protected member_ `FViewCameraState CameraState;`
- L282 _protected member_ `FToolDataVisualizer ProjectionShapeVisualizer;`
- L284 _protected prototype_ `void InitializeMesh();`
- L285 _protected prototype_ `void UpdateNumPreviews();`
- L287 _protected prototype_ `void TransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L289 _protected prototype_ `void OnMaterialSettingsChanged();`
- L290 _protected prototype_ `void OnMeshUpdated(UMeshOpPreviewWithBackgroundCompute* PreviewCompute);`
- L292 _protected prototype_ `UE::Geometry::FOrientedBox3d GetProjectionBox() const;`
- L299 _protected member_ `TUniquePtr<FSelectClickedAction> SetPlaneCtrlClickBehaviorTarget;`
- L302 _protected member_ `TObjectPtr<USingleClickInputBehavior> ClickToSetPlaneBehavior;` — `UPROPERTY()`
- L304 _protected prototype_ `void UpdatePlaneFromClick(const FVector3d& Position, const FVector3d& Normal, bool bTransitionOnly);`
- L310 _protected member_ `bool bHavePendingAction = false;`
- L311 _protected member_ `EUVProjectionToolActions PendingAction;`
- L312 _protected prototype_ `virtual void ApplyAction(EUVProjectionToolActions ActionType);`
- L313 _protected prototype_ `void ApplyAction_AutoFit(bool bAlign);`
- L314 _protected prototype_ `void ApplyAction_Reset();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLS_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingTools/Public/WeldMeshEdgesTool.h` (Public)


#### class `UWeldMeshEdgesToolBuilder`  
`class UWeldMeshEdgesToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L28-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionToolBuilder`
- L32 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L34 _public function_ `virtual bool RequiresInputSelection() const override`

#### enum `EWeldMeshEdgesAttributeUIMode`  
`enum class EWeldMeshEdgesAttributeUIMode : uint8`  
_L38-46_
- reflection: `UENUM()`
- L41 _public enumerator_ `None` — Do not weld split-attributes
- L43 _public enumerator_ `OnWeldedMeshEdgesOnly` — Apply attribute welding only along the current mesh welds
- L45 _public enumerator_ `OnFullMesh` — Apply attribute welding to all split-attributes

#### class `UWeldMeshEdgesToolProperties`  
`class UWeldMeshEdgesToolProperties : public UInteractiveToolPropertySet`  
_L50-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L57 _public member_ `float Tolerance = FMathf::ZeroTolerance;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.000001", UIMax = "0.01", ClampMin = "0.00000001", ClampMax = "1000.0"))` — Edges are considered matching if both pairs of endpoint vertices are closer than this distance
- L61 _public member_ `bool bOnlyUnique = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Only merge unambiguous pairs that have unique duplicate-edge matches
- L65 _public member_ `bool bResolveTJunctions = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — If enabled, after an initial attempt at Welding, attempt to resolve remaining open edges in T-junction configurations via edge splits, and then retry Weld
- L69 _public member_ `bool bSplitBowties = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If enabled, will split bowtie vertices before welding. This can in some cases enable more edges to be successfully welded
- L73 _public member_ `int32 InitialEdges;` — `UPROPERTY(VisibleAnywhere, Category = Statistics)` — Initial number of open boundary edges
- L77 _public member_ `int32 RemainingEdges;` — `UPROPERTY(VisibleAnywhere, Category = Statistics)` — Number of remaining open boundary edges
- L81 _public member_ `EWeldMeshEdgesAttributeUIMode AttrWeldingMode = EWeldMeshEdgesAttributeUIMode::OnWeldedMeshEdgesOnly;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Split-Attribute Welding"))` — Controls split-attribute welding performed after the Mesh weld.  Applies to normals, tangents, UVs and colors.
- L86 _public member_ `float SplitNormalThreshold = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "AttrWeldingMode != EWeldMeshEdgesAttributeUIMode::None", UIMin = "0.0", UIMax = "180.0", ClampMin = "0.0", ClampMax = "180.0", DisplayName="Normal Angle Threshold"))` — Threshold on the angle between normals used to determine if split normals should be merged
- L90 _public member_ `float SplitTangentsThreshold = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "AttrWeldingMode != EWeldMeshEdgesAttributeUIMode::None", UIMin = "0.0", UIMax = "180.0", ClampMin = "0.0", ClampMax = "180.0", DisplayName="Tangent Angle Threshold"))` — Threshold on the angle between tangent used to determine if split tangents should be merged
- L94 _public member_ `float SplitUVThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "AttrWeldingMode != EWeldMeshEdgesAttributeUIMode::None", UIMin = "0" , DisplayName = "UV Distance Threshold"))` — Threshold uv-distance used to determine if split UVs should be merged
- L98 _public member_ `float SplitColorThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "AttrWeldingMode != EWeldMeshEdgesAttributeUIMode::None", UIMin = "0", DisplayName = "Color Distance Threshold"))` — Threshold color-distance used to determine if split colors should be merged

#### class `UWeldMeshEdgesOperatorFactory`  
`class UWeldMeshEdgesOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L106-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L112 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L115 _public member_ `TObjectPtr<UWeldMeshEdgesTool> WeldMeshEdgesTool;` — `UPROPERTY()`

#### class `UWeldMeshEdgesTool`  
`class UWeldMeshEdgesTool : public USingleTargetWithSelectionTool`  
_L123-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionTool`
- desc: Mesh Weld Edges Tool
- L127 _public prototype_ `UWeldMeshEdgesTool();`
- L129 _public prototype_ `virtual void Setup() override;`
- L130 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L132 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L134 _public function_ `virtual bool HasCancel() const override`
- L135 _public function_ `virtual bool HasAccept() const override`
- L136 _public prototype_ `virtual bool CanAccept() const override;`
- L139 _public prototype_ `void UpdateOpParameters(FWeldMeshEdgesOp& Op) const;` — update parameters in FWeldMeshEdgesOp based on current Settings
- L143 _protected member_ `TObjectPtr<UWeldMeshEdgesToolProperties> Settings;` — `UPROPERTY()`
- L146 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> PreviewCompute = nullptr;` — `UPROPERTY()`
- L149 _protected member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay = nullptr;` — `UPROPERTY()`
- L152 _protected member_ `TObjectPtr<UWeldMeshEdgesOperatorFactory> OperatorFactory;` — `UPROPERTY()`
- L156 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> SourceMesh;`
- L159 _protected member_ `TSet<int32> SelectedEdges;` — If there is an active selection, SelectedEdges will be initialized

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLS_API`
