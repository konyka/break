# Plugins / MeshResizingDataflowNodes

- module root: `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes`
- headers: 10; symbols: 194
- symbol kinds: enum=2, enumerator=5, function=7, macro=1, member=113, namespace=14, prototype=35, struct=17
- PrivateDependencyModuleNames: DataflowCore, DataflowEditor, DataflowEngine, DataflowNodes, DynamicMesh, GeometryFramework, ImageCore, MeshConversion, MeshConversionEngineTypes, MeshResizingCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryCore
- PublicIncludePathModuleNames: 

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/AlignUVMeshNode.h` (Private)


#### struct `FAlignUVMeshNode`  
`struct FAlignUVMeshNode : public FDataflowNode`  
_L11-41_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- L23 _private member_ `TObjectPtr<UDataflowMesh> ResizingMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "ResizingMesh"))`
- L26 _private member_ `TObjectPtr<UDataflowMesh> BaseMesh;` — `UPROPERTY(meta = (DataflowInput))`
- L29 _private member_ `int32 UVChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Align", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "UVChannelIndex", DataflowUVChannel, ClampMin = 0, ClampMax = 7, UIMin = 0, UIMax = 7))`
- L33 _private member_ `int32 BaseUVChannelIndex = -1;` — `UPROPERTY(EditAnywhere, Category = "Align", meta = (DataflowInput, ClampMin = -1, ClampMax = 7, UIMin = -1, UIMax = 7))` — Base UV channel index in case it differs from the ResizingMesh UV channel index, or -1 to use the same channel.
- L36 _private member_ `bool bScale = true;` — `UPROPERTY(EditAnywhere, Category = "Align")`
- L39 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace MeshResizing` (scope `UE`)
- L46 _prototype_ `void RegisterAlignUVMeshNodes();` (scope `UE::MeshResizing`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/BaseBodyDataflowNodes.h` (Private)


#### struct `FSkeletalMeshToMeshDataflowNode`  
`struct FSkeletalMeshToMeshDataflowNode final : public FDataflowNode`  
_L22-67_
- reflection: `USTRUCT(meta = (MeshResizing, Experimental, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Converts a SkeletalMesh into a DynamicMesh with Imported Vertex information DEPRECATED 5.8 - use FSkeletalMeshToMeshDataflowNode_v2 instead
- L31 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh", meta = (DataflowInput))` — SkeletalMesh to convert
- L35 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L39 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowOutput))` — Output materials
- L41 _public function_ `FSkeletalMeshToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L51 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L55 _private member_ `int32 LODLevel = 0;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh", meta = (DisplayName = "LOD Level"))` — Specifies the LOD level to use
- L61 _private member_ `bool bRecordImportedVertices = true;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh")` — Generate from the SkeletalMeshLODModel (vertex order will match SKM vertex order). Record ImportedVertices (if available) as NonManifold mapping data. This requires Editor-Only data.
- L65 _private member_ `bool bUseMeshDescription = false;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh", meta = (EditCondition = "!bRecordImportedVertices"))` — Generate from mesh description (vertex order will match mesh description / ImportedVertices). Requires Editor-Only data.

#### struct `FGenerateResizableProxyDataflowNode`  
`struct FGenerateResizableProxyDataflowNode final : public FDataflowNode`  
_L78-132_
- reflection: `USTRUCT(meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Generate a pair of Dynamic Meshes with the same topology that can be interpolated. Currently, this node relies on the vertex mapping data existing on the input source and target meshes, and that the mapped vertices on both meshes match.
- L87 _public member_ `TObjectPtr<UDynamicMesh> SourceMesh;` — `UPROPERTY(meta = (DataflowInput))` — Source mesh
- L91 _public member_ `TArray<TObjectPtr<UMaterialInterface>> SourceMaterialArray;` — `UPROPERTY(meta = (DataflowInput))` — Source materials.
- L95 _public member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput))` — Target mesh
- L99 _public member_ `TObjectPtr<UDynamicMesh> SourceProxyMesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SourceMesh"))` — Output source proxy mesh
- L103 _public member_ `TObjectPtr<UDynamicMesh> TargetProxyMesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SourceMesh"))` — Output source proxy mesh
- L107 _public member_ `TArray<TObjectPtr<UMaterialInterface>> ProxyMaterialArray;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SourceMaterialArray"))` — Target materials.
- L110 _public function_ `FGenerateResizableProxyDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L125 _private member_ `FString SourceMappingData = "Im` — `UPROPERTY(EditAnywhere, Category = "Resizable Proxy")` — Source vertex mapping data. TODO: only have two choices that work currently. Make this an enum or something
- L129 _private member_ `FString TargetMappingData = "Im` — `UPROPERTY(EditAnywhere, Category = "Resizable Proxy")` — Target vertex mapping data. TODO: only have two choices that work currently. Make this an enum or something
- L131 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGenerateInterpolatedProxyDataflowNode`  
`struct FGenerateInterpolatedProxyDataflowNode final : public FDataflowNode`  
_L141-186_
- reflection: `USTRUCT(meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Generate a pair of Dynamic Meshes with the same topology that can be interpolated. Currently, this node relies on the vertex mapping data existing on the input source and target meshes, and that the mapped vertices on both meshes match.
- L150 _public member_ `TObjectPtr<UDynamicMesh> SourceMesh;` — `UPROPERTY(meta = (DataflowInput))` — Source mesh
- L154 _public member_ `TArray<TObjectPtr<UMaterialInterface>> SourceMaterialArray;` — `UPROPERTY(meta = (DataflowInput))` — Source materials.
- L158 _public member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput))` — Target mesh
- L162 _public member_ `TObjectPtr<UDynamicMesh> ProxyMesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SourceMesh"))` — Output proxy mesh
- L166 _public member_ `TArray<TObjectPtr<UMaterialInterface>> ProxyMaterialArray;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SourceMaterialArray"))` — Proxy materials.
- L169 _public function_ `FGenerateInterpolatedProxyDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L183 _private member_ `float BlendAlpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Interpolate Proxy", meta = (ClampMin = "0", ClampMax = "1"))` — Alpha between source (0) and target (1)
- L185 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSkeletalMeshToMeshDataflowNode_v2`  
`struct FSkeletalMeshToMeshDataflowNode_v2 final : public FDataflowNode`  
_L194-227_
- reflection: `USTRUCT(meta = (MeshResizing, Experimental, Icon = "Icons.SkeletalMesh"))`
- inherits: `FDataflowNode`
- desc: Converts a SkeletalMesh into a DataflowMesh with Imported Vertex information
- L203 _private member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh", meta = (DataflowInput))` — SkeletalMesh to convert
- L207 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L209 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L213 _private member_ `int32 LODLevel = 0;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh", meta = (DisplayName = "LOD Level"))` — Specifies the LOD level to use
- L218 _private member_ `bool bRecordImportedVertices = true;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh")` — Generate from the SkeletalMeshLODModel (vertex order will match SKM vertex order). Record ImportedVertices (if available) as NonManifold mapping data. This requires Editor-Only data.
- L222 _private member_ `bool bUseMeshDescription = false;` — `UPROPERTY(EditAnywhere, Category = "SkeletalMesh", meta = (EditCondition = "!bRecordImportedVertices"))` — Generate from mesh description (vertex order will match mesh description / ImportedVertices). Requires Editor-Only data.
- L226 _public prototype_ `FSkeletalMeshToMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L229 _namespace_ `namespace UE`
- L229 _namespace_ `namespace MeshResizing` (scope `UE`)
- L231 _prototype_ `void RegisterBaseBodyDataflowNodes();` (scope `UE::MeshResizing`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/MeshConstraintNodes.h` (Private)


#### struct `FMeshConstrainedDeformationNode`  
`struct FMeshConstrainedDeformationNode : public FDataflowNode`  
_L15-63_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- L27 _private member_ `TObjectPtr<UDataflowMesh> ResizingMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "ResizingMesh"))`
- L30 _private member_ `TObjectPtr<UDataflowMesh> BaseMesh;` — `UPROPERTY(meta = (DataflowInput))`
- L33 _private member_ `TArray<float> InvMass;` — `UPROPERTY(meta = (DataflowInput))`
- L36 _private member_ `TArray<float> EdgeConstraintWeights;` — `UPROPERTY(meta = (DataflowInput))`
- L39 _private member_ `int32 Iterations = 100;` — `UPROPERTY(EditAnywhere, Category = "Constrained Deformation|Solver", meta = (Min = 0, UIMax = 100))`
- L43 _private member_ `bool bEnableShearConstraint = true;` — `UPROPERTY(EditAnywhere, Category = "Constrained Deformation|Shear Constraint")` — Remove shear deformation
- L45 _private member_ `float ShearConstraintStrength = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Constrained Deformation|Shear Constraint", meta = (Min = 0, Max = 1, EditCondition = "bEnableShearConstraint"))`
- L48 _private member_ `bool bEnableBendingConstraint = true;` — `UPROPERTY(EditAnywhere, Category = "Constrained Deformation|Bending Constraints")`
- L50 _private member_ `float BendingConstraintStrength = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Constrained Deformation|Bending Constraints", meta = (Min = 0, EditCondition = "bEnableBendingConstraint"))`
- L53 _private member_ `bool bEnableEdgeConstraint = true;` — `UPROPERTY(EditAnywhere, Category = "Constrained Deformation|Edge Constraints")`
- L55 _private member_ `float EdgeConstraintStrength = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Constrained Deformation|Edge Constraints", meta = (Min = 0, EditCondition = "bEnableEdgeConstraint"))`
- L58 _private member_ `FVector3d Gravity = FVector3d(0,0,0);` — `UPROPERTY(EditAnywhere, Category = "Gravity")`
- L61 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L65 _namespace_ `namespace UE`
- L65 _namespace_ `namespace MeshResizing` (scope `UE`)
- L67 _prototype_ `void RegisterMeshConstraintDataflowNodes();` (scope `UE::MeshResizing`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/MeshResizingTextureNodes.h` (Private)


#### struct `FMeshResizingGrowTileRegionNode`  
`struct FMeshResizingGrowTileRegionNode : public FDataflowNode`  
_L17-47_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Finds a square tile within a specified image region and duplicates it over the whole image. The image region to search is determined by the UV coordinates in ValidRegionMesh -- only texels inside a 2D UV mesh triangle are considered when searching for a tile. Note this node does not try to detect any repeating patterns, it just grabs the first square tile of the specified size that is entirely inside the UV mesh.
- L29 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowIntrinsic, DataflowInput, DataflowOutput, DataflowPassthrough = "Image"))`
- L32 _private member_ `TObjectPtr<UDataflowMesh> ValidRegionMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L35 _private member_ `int MeshUVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = "Valid Region", meta = (UIMin = 0, ClampMin = 0))`
- L38 _private member_ `int TileWidth = 10;` — `UPROPERTY(EditAnywhere, Category = "Tile", meta = (UIMin = 1, ClampMin = 1))`
- L41 _private member_ `FDataflowImage MeshMask;` — `UPROPERTY(meta = (DataflowOutput))`
- L45 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace MeshResizing` (scope `UE`)
- L51 _prototype_ `void RegisterTextureNodes();` (scope `UE::MeshResizing`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/MeshWarpNode.h` (Private)


#### enum `EMeshResizingWarpMethod`  
`enum struct EMeshResizingWarpMethod : uint8`  
_L14-18_
- reflection: `UENUM()`
- L16 _public enumerator_ `WrapDeform`
- L17 _public enumerator_ `RBFInterpolate`

#### struct `FMeshWarpNode`  
`struct FMeshWarpNode : public FDataflowNode`  
_L21-67_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- L25 _public prototype_ `DATAFLOW_NODE_RENDER_TYPE_START() DATAFLOW_NODE_RENDER_TYPE_ADD("SurfaceRender", FName("UDataflowMesh"), "BlendedTargetMesh") DATAFLOW_NODE_RENDER_TYPE_ADD("SurfaceRender", FName("UDataflowMesh"), "ResizedMesh") DATAFLOW_NODE_RENDER_TYPE_END() public: FMeshWarpNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L37 _private member_ `TObjectPtr<UDataflowMesh> MeshToResize;` — `UPROPERTY(meta = (DataflowInput))`
- L40 _private member_ `TObjectPtr<UDataflowMesh> SourceMesh;` — `UPROPERTY(meta = (DataflowInput))`
- L43 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput))`
- L47 _private member_ `TObjectPtr<UDataflowMesh> BlendedTargetMesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SourceMesh"))`
- L50 _private member_ `TObjectPtr<UDataflowMesh> ResizedMesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "MeshToResize"))`
- L53 _private member_ `float Alpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Warp", meta = (Min = 0.0f, UIMin = 0.0f, Max = 1.0f, UIMax = 1.0f))`
- L56 _private member_ `EMeshResizingWarpMethod WarpMethod = EMeshResizingWarpMethod::RBFInterpolate;` — `UPROPERTY(EditAnywhere, Category = "Warp")`
- L59 _private member_ `int32 NumInterpolationPoints = 100;` — `UPROPERTY(EditAnywhere, Category = "Warp", meta = (Min = 1, EditCondition = "WarpMethod == EMeshResizingWarpMethod::RBFInterpolate", EditConditionHides))`
- L62 _private member_ `bool bInterpolateNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Warp", meta = (EditCondition = "WarpMethod == EMeshResizingWarpMethod::RBFInterpolate", EditConditionHides))`
- L65 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/RBFInterpolationNodes.h` (Private)


#### struct `FGenerateRBFResizingWeightsNode`  
`struct FGenerateRBFResizingWeightsNode : public FDataflowNode`  
_L19-57_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Sample points and generate RBF Interpolation data for a given Source mesh.
- L32 _private member_ `TObjectPtr<UDataflowMesh> MeshToResize;` — `UPROPERTY(meta = (DataflowInput))` — The mesh to resize. This is currently unused but may be used to improve point sampling in the future.
- L36 _private member_ `TObjectPtr<UDataflowMesh> SourceMesh;` — `UPROPERTY(meta = (DataflowInput))` — The source mesh to be sampled.
- L40 _private member_ `FMeshResizingRBFInterpolationData InterpolationData;` — `UPROPERTY(meta = (DataflowOutput))` — The calculated interpolation points and RBF weights
- L44 _private member_ `int32 NumInterpolationPoints = 1500;` — `UPROPERTY(EditAnywhere, Category = "RBF Resizing Weights", meta = (Min = 1, DataflowInput))` — The number of interpolation points to be sampled.
- L47 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L49 _private function_ `virtual bool CanDebugDraw() const override`
- L53 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L54 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FApplyRBFResizingNode`  
`struct FApplyRBFResizingNode : public FDataflowNode`  
_L63-112_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Apply the interpolation data calculated by GenerateRBFResizingWeights to resize a mesh.
- L69 _public prototype_ `FApplyRBFResizingNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L75 _private member_ `TObjectPtr<const UDataflowMesh> MeshToResize;` — `UPROPERTY(meta = (DataflowInput))` — The mesh being resized
- L81 _private member_ `bool bUseSkeletalMeshTarget = false;` — `UPROPERTY(EditAnywhere, Category = "RBF Resize")` — Use a skeletal mesh for the target mesh (instead of a dynamic mesh)
- L83 _private member_ `static constexpr bool bUseSkeletalMeshTarget = false;`
- L88 _private member_ `TObjectPtr<const USkeletalMesh> TargetSkeletalMesh;` — `UPROPERTY(meta = (DataflowInput, EditCondition = "bUseSkeletalMeshTarget"))` — The target mesh that corresponds with the SourceMesh used to generate the InterpolationData. Must have matching vertices with SourceMesh
- L91 _private member_ `int32 TargetSkeletalMeshLODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "RBF Resize", meta = (DataflowInput, EditCondition = "bUseSkeletalMeshTarget", ClampMin = 0))`
- L95 _private member_ `TObjectPtr<const UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, EditCondition = "!bUseSkeletalMeshTarget"))` — The target mesh that corresponds with the SourceMesh used to generate the InterpolationData. Must have matching vertices with SourceMesh
- L99 _private member_ `FMeshResizingRBFInterpolationData InterpolationData;` — `UPROPERTY(meta = (DataflowInput))` — The pre-calculated base RBF interpolation data.
- L103 _private member_ `TObjectPtr<const UDataflowMesh> ResizedMesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "MeshToResize"))` — The resulting resized mesh
- L107 _private member_ `bool bInterpolateNormals = true;` — `UPROPERTY(EditAnywhere, Category = "RBF Resize")` — Whether or not to interpolate the normals as well as the positions
- L110 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/UVMeshTransformNode.h` (Private)


#### struct `FUVMeshTransformNode`  
`struct FUVMeshTransformNode : public FDataflowNode`  
_L11-41_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- L23 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh"))`
- L26 _private member_ `int32 UVChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Mesh", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "UVChannelIndex", DataflowUVChannel, ClampMin = 0, ClampMax = 7, UIMin = 0, UIMax = 7))`
- L29 _private member_ `FVector2f Scale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Transform", Meta = (AllowPreserveRatio))`
- L33 _private member_ `float Rotation = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Transform", Meta = (UIMin = -360, UIMax = 360, ClampMin = -360, ClampMax = 360))` — Rotation angle in degrees
- L36 _private member_ `FVector2f Translation = { 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "Transform")`
- L39 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace MeshResizing` (scope `UE`)
- L47 _prototype_ `void RegisterUVMeshTransformNodes();` (scope `UE::MeshResizing`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/UVResizeControllerNode.h` (Private)


#### struct `FUVResizeControllerNode`  
`struct FUVResizeControllerNode : public FDataflowNode`  
_L16-52_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: UV Resizing logic. Returns whether this dynamic mesh is suitable for UV resizing and which UV channels to use.
- L27 _private member_ `FString TextureSuffix = TEXT("Tex` — `UPROPERTY(EditAnywhere, Category = "UVResizeController")` — The texture name suffix .
- L31 _private member_ `FString UVChannelSuffix = TEXT("UVI` — `UPROPERTY(EditAnywhere, Category = "UVResizeController")` — The suffix to replace the texture name with pointing to the UV channel index scalar parameter.
- L35 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh"))` — The input/output Dataflow mesh.
- L39 _private member_ `TArray<int32> UVChannelIndices;` — `UPROPERTY(Meta = (DataflowOutput))` — The UV channels to resize.
- L43 _private member_ `TArray<int32> SourceUVChannelIndices;` — `UPROPERTY(Meta = (DataflowOutput))` — The matching UV channels on the original source mesh.
- L47 _private member_ `bool bHasUVChannelsToResize = false;` — `UPROPERTY(Meta = (DataflowOutput))` — Whether the input mesh has any UV channels to resize.
- L50 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Private/MeshResizing/UVUnwrapNode.h` (Private)


#### enum `EUVUnwrapMethod`  
`enum class EUVUnwrapMethod`  
_L12-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `ExponentialMap = 0`
- L15 _public enumerator_ `ConformalFreeBoundary = 1`
- L16 _public enumerator_ `SpectralConformal = 2`

#### struct `FUVUnwrapNode`  
`struct FUVUnwrapNode : public FDataflowNode`  
_L20-43_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- L32 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh"))`
- L35 _private member_ `int32 UVChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "UVChannelIndex", DataflowUVChannel, ClampMin = 0, ClampMax = 7, UIMin = 0, UIMax = 7))`
- L38 _private member_ `EUVUnwrapMethod Method = EUVUnwrapMethod::SpectralConformal;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap")`
- L41 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace MeshResizing` (scope `UE`)
- L47 _prototype_ `void RegisterUVUnwrapNodes();` (scope `UE::MeshResizing`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingNodes/Public/MeshResizing/MeshWrapNode.h` (Public)


#### struct `FMeshWrapLandmark`  
`struct FMeshWrapLandmark`  
_L21-32_
- reflection: `USTRUCT()`
- desc: Mesh Wrap Node landmark. Matched landmarks between source topology and target shape meshes are used to guide the Mesh Wrap operation.
- L27 _public member_ `FString Identifier;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap")` — String name. Landmarks will be matched by comparing identifiers.
- L31 _public member_ `int32 VertexIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", meta = (ClampMin = "-1"))` — Vertex of this landmark.

#### struct `FMeshWrapCorrespondence`  
`struct FMeshWrapCorrespondence`  
_L38-53_
- reflection: `USTRUCT()`
- desc: Matched Mesh Wrap Node landmark correspondence.
- L44 _public member_ `FString Identifier;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap")` — Matched landmark name.
- L48 _public member_ `int32 SourceVertexIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", meta = (ClampMin = "-1"))` — Vertex on source topology mesh.
- L52 _public member_ `int32 TargetVertexIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", meta = (ClampMin = "-1"))` — Vertex on target shape mesh.

#### struct `FMeshWrapLandmarksNode`  
`struct FMeshWrapLandmarksNode : public FDataflowNode`  
_L57-106_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Node for defining landmarks used by MeshWrapNode. The Mesh Wrap Landmark Selection Tool allows generating these landmarks via selection.
- L68 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L70 _private function_ `virtual bool CanDebugDraw() const override`
- L74 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L75 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L82 _private prototype_ `static TUniquePtr<class FToolCommandChange> MakeSelectedNodeChange(const FMeshWrapLandmarksNode& Node);`
- L86 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh"))` — The mesh to define landmarks on.
- L90 _private member_ `TArray<FMeshWrapLandmark> Landmarks;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", meta = (DataflowOutput))` — The defined landmarks (identifier, vertex pair). Can be hand-input/edited or generated using the Mesh Wrap Landmark Selection Tool
- L94 _private member_ `float PointSize = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Display", meta = (ClampMin = 0.f))` — Point size of displayed landmarks
- L98 _private member_ `bool bShowIndex = true;` — `UPROPERTY(EditAnywhere, Category = "Display")` — Display the landmark indices
- L102 _private member_ `bool bShowIdentifier = true;` — `UPROPERTY(EditAnywhere, Category = "Display")` — Display the landmark identifier strings
- L105 _private member_ `bool bCanDebugDraw = true;` — This will be set by UMeshWrapLandmarkSelectionTool to false to not double draw.

#### struct `FMeshWrapNode`  
`struct FMeshWrapNode : public FDataflowPrimitiveNode`  
_L110-220_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowPrimitiveNode`
- desc: Dataflow node for wrapping one mesh's topology to another mesh's shape. Uses point landmarks defined by the Mesh Wrap Landmarks node to match corresponding points between the two meshes.
- L118 _public prototype_ `FMeshWrapNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L124 _private member_ `TObjectPtr<UDataflowMesh> SourceTopologyMesh;` — `UPROPERTY(meta = (DataflowInput))` — Input mesh with the desired wrapped mesh topology.
- L128 _private member_ `TObjectPtr<UDataflowMesh> TargetShapeMesh;` — `UPROPERTY(meta = (DataflowInput))` — Input mesh with the desired wrapped mesh shape.
- L132 _private member_ `TObjectPtr<UDataflowMesh> WrappedMesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SourceTopologyMesh"))` — Output wrapped mesh.
- L136 _private member_ `TArray<FMeshWrapLandmark> SourceTopologyLandmarks;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", meta = (DataflowInput))` — Landmarks defined on SourceTopologyMesh. TargetShapeLandmarks with matching Identifiers will be used to find correspondences that help improve the wrap.
- L140 _private member_ `TArray<FMeshWrapLandmark> TargetShapeLandmarks;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", meta = (DataflowInput))` — Landmarks defined on TargetShapeMesh. SourceTopologyLandmarks with matching Identifiers will be used to find correspondences that help improve the wrap.
- L144 _private member_ `TArray<FMeshWrapCorrespondence> MatchedLandmarks;` — `UPROPERTY(meta = (DataflowOutput))` — Landmarks matched by Identifier from SourceTopologyLandmarks and TargetShapeLandmarks.
- L148 _private member_ `int32 MaxNumOuterIterations = 10;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", Meta = (ClampMin ="0"))` — Mesh Wrap is calculated with an inner and outer loop. This is the maximum number of outer loops. Each outer loop increases the Projection Stiffness by ProjectionStiffnessMultiplier.
- L152 _private member_ `int32 NumInnerIterations = 20;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", Meta = (ClampMin = "0"))` — Mesh Wrap is calculated with an inner and outer loop. This is the number of inner loops run before increasing the Projection Stiffness in the outer loop.
- L156 _private member_ `float ProjectionTolerance = 1e-4f;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", Meta =(ClampMin = "0"))` — Mesh Wrap will terminate early if the Projection tolerance is within this threshold.
- L160 _private member_ `float LaplacianStiffness = 1.;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", AdvancedDisplay, Meta = (ClampMin = "0"))` — Weight of mesh wrap to retain Source Topology mesh features.
- L164 _private member_ `float InitialProjectionStiffness = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", AdvancedDisplay, Meta = (ClampMin = "0"))` — Initial weight of mesh wrap to match projected Target Shape. Each outer loop will multiply this stiffness by ProjectionStiffnessMultiplier.
- L168 _private member_ `float ProjectionStiffnessMuliplier = 10.;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", AdvancedDisplay, Meta = (ClampMin = "0"))` — Each outer loop will multiply InitialProjectionStiffness by this to improve Target Shape match.
- L172 _private member_ `float CorrespondenceStiffness = 1.;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap", AdvancedDisplay, Meta = (ClampMin = "0"))` — Weight of mesh wrap to match Landmark correspondences.
- L176 _private member_ `TObjectPtr<UMaterial> DefaultDisplayMaterial;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap Display")` — Display material for Source or Target when none is supplied.
- L180 _private member_ `bool bDisplayLandmarks = true;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap Display")` — Display landmarks.
- L184 _private member_ `bool bDisplaySource = false;` — `UPROPERTY(EditAnywhere, Category ="Mesh Wrap Display")` — Draw source mesh.
- L188 _private member_ `float SourceDisplayOffset = -150.f;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap Display", Meta =(EditCondition = "bDisplaySource"))` — Offset of source mesh display for side-by-side drawing.
- L192 _private member_ `bool bDisplayTarget = false;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap Display")` — Draw target mesh.
- L196 _private member_ `float TargetDisplayOffset = 150.f;` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap Display", Meta = (EditCondition = "bDisplayTarget"))` — Offset of target mesh display for side-by-side drawing.
- L199 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L201 _private function_ `virtual bool CanDebugDraw() const override`
- L205 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L206 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L211 _private function_ `virtual bool HasRenderCollectionPrimitives() const override`
- L215 _private prototype_ `virtual void AddPrimitiveComponents(UE::Dataflow::FContext& Context, const TSharedPtr<const FManagedArrayCollection> RenderCollection, TObjectPtr<UObject> NodeOwner, TObjectPtr<AActor> RootActor, TArray<TObjectPtr<UPrimitiveComponent>>& PrimitiveComponents) override;`
- L219 _private prototype_ `TArray<FMeshWrapCorrespondence> CalculateMatchedLandmarks(UE::Dataflow::FContext& Context) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHRESIZINGDATAFLOWNODES_API`
- L222 _namespace_ `namespace UE`
- L222 _namespace_ `namespace MeshResizing` (scope `UE`)
- L224 _prototype_ `void RegisterMeshWrapNodes();` (scope `UE::MeshResizing`)
