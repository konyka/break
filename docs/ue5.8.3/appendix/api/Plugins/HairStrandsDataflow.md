# Plugins / HairStrandsDataflow

- module root: `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow`
- headers: 14; symbols: 274
- symbol kinds: class=2, enum=3, enumerator=13, function=3, member=139, namespace=11, prototype=74, struct=29
- PublicDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin, DataflowNodes, DynamicMesh, Engine, GeometryAlgorithms, GeometryCore, HairStrandsCore, MeshConversion, MeshConversionEngineTypes, MeshDescription, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StaticMeshDescription, UnrealEd

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Private/AverageCurvesNode.h` (Private)


#### struct `FDataflowAverageCurves`  
`struct FDataflowAverageCurves : public FDataflowNode`  
_L15-40_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Take an collection curve selection and generate a single curve collection that is the average of the input curves
- L26 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L31 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowRenderGroups = "Surface"))` — Managed array collection source of the curves to be average from
- L35 _private member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput))` — Curve selection to use
- L39 _private member_ `int32 NumSamples = 8;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DataflowInput, ClampMin = 2, UIMin = 2))` — Number of samples to use for averaged result curve

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Private/GroomDataflowVisualization.h` (Private)


#### class `UE::Groom::FGroomDataflowSimulationVisualization`  
`class FGroomDataflowSimulationVisualization : public Dataflow::IDataflowSimulationVisualization`  
_L12-34_
- inherits: `Dataflow::IDataflowSimulationVisualization`
- desc: Dataflow simulation customisation for groom
- L15 _public member_ `static const FName Name;`
- L16 _public prototype_ `virtual ~FGroomDataflowSimulationVisualization() = default;`
- L17 _public prototype_ `FGroomDataflowSimulationVisualization();`
- L22 _private prototype_ `virtual FName GetName() const override;`
- L23 _private prototype_ `virtual void ExtendSimulationVisualizationMenu(const TSharedPtr<FDataflowSimulationViewportClient>& ViewportClient, FMenuBuilder& MenuBuilder) override;`
- L24 _private prototype_ `virtual void Draw(const FDataflowSimulationScene* SimulationScene, FPrimitiveDrawInterface* PDI) override;`
- L25 _private prototype_ `virtual void DrawCanvas(const FDataflowSimulationScene* SimulationScene, FCanvas* Canvas, const FSceneView* SceneView) override;`
- L26 _private prototype_ `virtual FText GetDisplayString(const FDataflowSimulationScene* SimulationScene) const override;`
- L30 _private prototype_ `const UGroomComponent* GetGroomComponent(const FDataflowSimulationScene* SimulationScene) const;` — Get the groom component given a simulation scene
- L33 _private member_ `TArray<bool> VisualizationFlags;` — Visualization flags

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Groom` (scope `UE`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Private/GuidesToJointsNode.h` (Private)


#### struct `FDataflowGuidesToJointsNode`  
`struct FDataflowGuidesToJointsNode : public FDataflowTerminalNode`  
_L21-89_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowTerminalNode`
- desc: Generate joints/bones from a guide selection and save the resulting skeleton asset on disk
- L33 _private prototype_ `virtual void OnDoubleClicked(UE::Dataflow::FContext* Context) const override;`
- L38 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L39 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L42 _private prototype_ `void ClearSkeleton(USkeleton* InOutSkeleton) const;`
- L43 _private prototype_ `void UpdateSkeleton(UE::Dataflow::FContext& Context, USkeleton* InOutSkeleton) const;`
- L44 _private prototype_ `void InitializeSkeletonFromRefSkeleton(const FReferenceSkeleton& RefSkeleton, USkeleton* InOutSkeleton) const;`
- L45 _private prototype_ `int32 GetRefSkeletonRootIndex(const FReferenceSkeleton& RefSkeleton) const;`
- L47 _private prototype_ `void UpdateSkeletalMesh(UE::Dataflow::FContext& Context, USkeletalMesh* InOutSkeletalMesh, USkeleton* InOutSkeleton) const;`
- L48 _private prototype_ `FName GenerateUniqueBoneName(FName BaseName, const FReferenceSkeleton& RefSkeleton) const;`
- L52 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DataflowRenderGroups = "Surface"))` — Managed array collection source of the guides - Required
- L56 _private member_ `FString SkeletalMeshAssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the skeletal mesh asset to create or update
- L60 _private member_ `FString SkeletonAssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the skeleton asset to create or update
- L64 _private member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput))` — Curve selection to use to generate bones/joints - if none specified all curve will be considered
- L68 _private member_ `FDataflowStringTypes BoneBaseName;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Base name for the bones created from the curve
- L72 _private member_ `FDataflowStringTypes ParentBone;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DataflowInput))` — Optional name of parent bone from the input skeletal mesh to use as the root of the generate bones
- L76 _private member_ `TObjectPtr<USkeletalMesh> BaseSkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = Base, meta = (DataflowInput))` — Skeletal Mesh to use a base
- L80 _private member_ `bool bCopyGeometryFromBaseSkeletalMesh = false;` — `UPROPERTY(EditAnywhere, Category = Base)` — Option to copy the geometry from the base skeletal mesh
- L84 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Created Skeletal Mesh
- L88 _private member_ `TObjectPtr<USkeleton> SkeletonAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Created Skeleton

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/AttachGuidesRootsNode.h` (Public)


#### struct `FAttachGuidesRootsDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use AttachCurveRoots node instead.") FAttachGuidesRootsDataflowNode : public FDataflowNode`  
_L15-47_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Attach the guides roots by setting their kinematic weights to 1.0f
- L33 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L38 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L42 _public member_ `int32 GroupIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category="Groups", meta = (DisplayName = "Group Index"))` — Group index on which the roots will be attached. -1 will attach all the groups
- L46 _public member_ `FCollectionAttributeKey KinematicWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Kinematic Weights", DataflowOutput))` — Point Kinematic weights key to be used in other nodes if necessary

#### struct `FAttachCurveRootsDataflowNode`  
`struct FAttachCurveRootsDataflowNode : public FDataflowNode`  
_L51-77_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Attach the curve roots by setting their kinematic weights to 1.0f
- L63 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L68 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L72 _private member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Curve Selection"))` — Curve selection to focus the geometry transfer spatially
- L76 _private member_ `FCollectionAttributeKey KinematicWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Kinematic Weights", DataflowOutput))` — Vertex kinematic weights key to be used in other nodes if necessary

#### struct `FBuildCurveWeightsDataflowNode`  
`struct FBuildCurveWeightsDataflowNode : public FDataflowNode`  
_L81-117_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Build a weight map that will be identical on every curves
- L89 _public function_ `FBuildCurveWeightsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L99 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L104 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L108 _public member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Curve Selection"))` — Curve selection to focus the geometry transfer spatially
- L112 _public member_ `FRuntimeFloatCurve CurveWeights;` — `UPROPERTY(EditAnywhere, Category = "Curves", meta = (DisplayName = "Curve Weights", ViewMinInput = "0.0", ViewMaxInput = "1.0", ViewMinOutput = "0.0", ViewMaxOutput = "1.0", TimeLineLength = "1.0", XAxisName = "Curve Coordinate (0,1)", YAxisName = "Weight value", ToolTip = "This curve determines the weight value from root to tip. \n The X axis range is [0,1], 0 mapping the root and 1 the tip"))` — Weight value along each curves
- L116 _public member_ `FCollectionAttributeKey WeightsAttribute;` — `UPROPERTY(EditAnywhere, Category = "Curves", meta = (DisplayName = "Weights Attribute", DataflowInput))` — Vertex kinematic weights key to be used in other nodes if necessary

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/BuildGroomSkinningNodes.h` (Public)


#### struct `FTransferSkinWeightsGroomNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FTransferSkinWeightsGroomNode : public FDataflowNode`  
_L26-73_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Build the curves skinning by transferring the indices weights from a skelmesh
- L34 _public prototype_ `FTransferSkinWeightsGroomNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L39 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L44 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L48 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "SkeletalMesh"))` — SkeletalMesh used to transfer the skinning weights. Will be stored onto the groom asset
- L52 _private member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DisplayName = "LOD Index"))` — LOD used to transfer the weights
- L56 _private member_ `int32 GroupIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category="Groom Groups", meta = (DisplayName = "Group Index"))` — Group index on which the dats will be transfered. -1 will transfer on all the groups
- L60 _private member_ `FTransform RelativeTransform;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh")` — The relative transform between the skeletal mesh and the groom asset.
- L64 _private member_ `EGroomCollectionType CurvesType = EGroomCollectionType::Guides;` — `UPROPERTY(EditAnywhere, Category = "Groom Groups", meta = (DisplayName = "Curves Type"))` — Type of curves to use to fill the groom collection (guides/strands)
- L68 _private member_ `FCollectionAttributeKey BoneIndicesKey;` — `UPROPERTY(meta = (DisplayName = "Bone Indices", DataflowOutput))` — Bone indices key to be used in other nodes if necessary
- L72 _private member_ `FCollectionAttributeKey BoneWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Bone Weights", DataflowOutput))` — Bone weights key to be used in other nodes if necessary

#### struct `FTransferGeometrySkinWeightsDataflowNode`  
`struct FTransferGeometrySkinWeightsDataflowNode : public FDataflowNode`  
_L77-119_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Build the curves skinning by transferring the indices weights from a skelmesh geometry
- L84 _public prototype_ `FTransferGeometrySkinWeightsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L89 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L94 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L98 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Vertex Selection"))` — Vertex selection to focus the geometry transfer spatially
- L102 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DataflowInput, DataflowPassthrough = "SkeletalMesh"))` — SkeletalMesh used to transfer the skinning weights. Will be stored onto the groom asset
- L106 _private member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DataflowInput, DisplayName = "LOD Index"))` — LOD used to transfer the weights
- L110 _private member_ `FTransform RelativeTransform;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh", meta = (DataflowInput, DisplayName = "Relative Transform"))` — The relative transform between the skeletal mesh and the groom asset.
- L114 _private member_ `FCollectionAttributeKey BoneIndicesKey;` — `UPROPERTY(meta = (DisplayName = "Bone Indices", DataflowOutput))` — Bone indices key to be used in other nodes if necessary
- L118 _private member_ `FCollectionAttributeKey BoneWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Bone Weights", DataflowOutput))` — Bone weights key to be used in other nodes if necessary

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Groom` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Groom`)
- L18 _prototype_ `FCollectionAttributeKey GetBoneIndicesKey();` (scope `UE::Groom::Private`) — Retrieve the bone indices key
- L21 _prototype_ `FCollectionAttributeKey GetBoneWeightsKey();` (scope `UE::Groom::Private`) — Retrieve the bone weights key

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/BuildGroomSplineSkinningNode.h` (Public)


#### struct `FBuildGroomSplineSkinWeightsNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FBuildGroomSplineSkinWeightsNode : public FDataflowNode`  
_L24-81_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Build spline skinning data from skeletal mesh
- L31 _public prototype_ `FBuildGroomSplineSkinWeightsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L34 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L39 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L43 _public member_ `FCollectionAttributeKey SplineParamKey;` — `UPROPERTY(meta = (DisplayName = "Spline Parameter Key", DataflowOutput))` — Spline Skinning Parameter key
- L47 _public member_ `FCollectionAttributeKey SplineBoneKey;` — `UPROPERTY(meta = (DataflowOutput))` — Spline Bones key containing root and end spline bone. To be used in other nodes if necessary
- L52 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DataFlowInput))` — SkeletalMesh used for spline skinning. Will be stored onto the groom asset
- L56 _public member_ `TArray<FString> RootBones;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh")` — Root bones to be used for spline skinning. Uses all bones if empty. Note that branches in the skeleton is currently not supported.
- L60 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DisplayName = "LOD Index"))` — LOD used to build skinning weights
- L64 _public member_ `int32 SamplesPerSegment = 64;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh")` — Number of spline samples per bone segment.
- L68 _public member_ `int32 GroupIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category="Groom Groups")` — Groom group index to build skinning weights for. -1 will build all groups
- L72 _public member_ `EGroomCollectionType CurvesType = EGroomCollectionType::Guides;` — `UPROPERTY(EditAnywhere, Category = "Groom Groups")` — Type of curves to build skinning for (guides/strands)
- L76 _public member_ `FString SplineParamName = "Sp` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Spline Parameter"))` — Spline skinning parameter attribute name
- L80 _public member_ `FString SplineBonesParamName = "Sp` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes")` — Spline bones attribute name. Used for storing root and end spline bone for each vertex.

#### struct `FConvertSplineToLinearSkinWeightsNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FConvertSplineToLinearSkinWeightsNode : public FDataflowNode`  
_L85-133_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Convert spline skinning data to linear data
- L92 _public prototype_ `FConvertSplineToLinearSkinWeightsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L95 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L100 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L104 _public member_ `FString SplineParamName = "Sp` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Spline Parameter"))` — Spline skinning parameter attribute name
- L108 _public member_ `FString SplineBonesName = "Sp` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Spline Bones"))` — Spline bones attribute name. Used for storing root and end spline bone for each vertex.
- L112 _public member_ `FCollectionAttributeKey SplineParamKey;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Spline Parameter Key"))` — Spline skinning parameter key
- L116 _public member_ `FCollectionAttributeKey SplineBonesKey;` — `UPROPERTY(meta = (DataflowInput))` — Spline bones key. Used for storing root and end spline bone for each vertex.
- L120 _public member_ `int32 GroupIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Groom Groups")` — Groom group index for converting skinning weight. -1 will convert all the groups
- L124 _public member_ `FCollectionAttributeKey BoneIndicesKey;` — `UPROPERTY(meta = (DataflowOutput))` — Linear skinning bone indices key
- L128 _public member_ `FCollectionAttributeKey BoneWeightsKey;` — `UPROPERTY(meta = (DataflowOutput))` — Linear skinning bone weights key
- L132 _public member_ `EGroomCollectionType CurvesType = EGroomCollectionType::Guides;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes")` — Type of curves to convert skinning for (guides/strands)

#### struct `FConvertLinearToSplineSkinWeightsNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FConvertLinearToSplineSkinWeightsNode : public FDataflowNode`  
_L137-177_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Convert linear skinning data to spline skinning data
- L144 _public prototype_ `FConvertLinearToSplineSkinWeightsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L147 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L152 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L156 _public member_ `int32 GroupIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Groom Groups")` — Groom group index for converting skinning weights. -1 will convert all groups
- L160 _public member_ `FCollectionAttributeKey SplineParamKey;` — `UPROPERTY(meta = (DisplayName = "Spline Parameter Key", DataflowOutput))` — Spline Skinning Parameter key
- L164 _public member_ `FCollectionAttributeKey SplineBoneKey;` — `UPROPERTY(meta = (DataflowOutput))` — Spline Bones key containing root and end spline bone.
- L168 _public member_ `FString SplineParamName = "Sp` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Spline Parameter"))` — Spline skinning parameter attribute name.
- L172 _public member_ `FString SplineBonesName = "Sp` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Spline Bones"))` — Spline bones parameter attribute name. Contains root and end spline bone for each vertex.
- L176 _public member_ `EGroomCollectionType CurvesType = EGroomCollectionType::Guides;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes")` — Type of curves to convert skinning for (guides/strands)

#### struct `UE::Groom::Private::FCollectionSplineAttributes`  
`struct FCollectionSplineAttributes`  
_L181-185_
- L183 _public member_ `static const FName VertexSplineParamAttribute;`
- L184 _public member_ `static const FName VertexSplineBonesAttribute;`

#### struct `FBuildSplineSkinWeightsDataflowNode`  
`struct FBuildSplineSkinWeightsDataflowNode : public FDataflowNode`  
_L190-236_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Build spline skinning data from skeletal mesh
- L197 _public prototype_ `FBuildSplineSkinWeightsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L202 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L207 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L211 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Vertex Selection"))` — Vertex selection to focus the geometry transfer spatially
- L215 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DataFlowInput))` — SkeletalMesh used to compute spline skinning weights. Will be stored onto the groom asset
- L219 _private member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category="Skeletal Mesh", meta = (DataflowInput, DisplayName = "LOD Index"))` — LOD used to build skinning weights
- L223 _private member_ `TArray<FString> RootBones;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh", meta = (DataFlowInput))` — Root bones to be used for spline skinning. Uses all bones if empty. Note that branches in the skeleton is currently not supported.
- L227 _private member_ `int32 SamplesPerSegment = 64;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh", meta = (DataflowInput))` — Number of spline samples per bone segment.
- L231 _private member_ `FCollectionAttributeKey SplineParamKey;` — `UPROPERTY(meta = (DisplayName = "Spline Parameter", DataflowOutput))` — Spline Skinning Parameter key
- L235 _private member_ `FCollectionAttributeKey SplineBonesKey;` — `UPROPERTY(meta = (DisplayName = "Spline Bones", DataflowOutput))` — Spline Bones key containing root and end spline bone. To be used in other nodes if necessary

#### struct `FSplineToLinearSkinWeightsDataflowNode`  
`struct FSplineToLinearSkinWeightsDataflowNode : public FDataflowNode`  
_L240-283_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Convert spline skinning data to linear data
- L247 _public prototype_ `FSplineToLinearSkinWeightsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L251 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L256 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L260 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Vertex Selection"))` — Vertex selection to process vertices subset
- L264 _private member_ `FCollectionAttributeKey SplineParamKey;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Spline Parameter"))` — Spline skinning parameter key
- L268 _private member_ `FCollectionAttributeKey SplineBonesKey;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Spline Bones"))` — Spline bones key. Used for storing root and end spline bone for each vertex.
- L272 _private member_ `FCollectionAttributeKey BoneIndicesKey;` — `UPROPERTY(meta = (DisplayName = "Bone Indices", DataflowOutput))` — Bone indices key to be used in other nodes if necessary
- L276 _private member_ `FCollectionAttributeKey BoneWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Bone Weights", DataflowOutput))` — Bone weights key to be used in other nodes if necessary
- L279 _private prototype_ `FCollectionAttributeKey GetSplineParamKey(UE::Dataflow::FContext& Context) const;` — Get spline parameter key
- L282 _private prototype_ `FCollectionAttributeKey GetSplineBonesKey(UE::Dataflow::FContext& Context) const;` — Get spline bones key

#### struct `FLinearToSplineSkinWeightsDataflowNode`  
`struct FLinearToSplineSkinWeightsDataflowNode : public FDataflowNode`  
_L287-324_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Convert linear skinning data to spline skinning data
- L294 _public prototype_ `FLinearToSplineSkinWeightsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L298 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L303 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L307 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Vertex Selection"))` — Vertex selection to process vertices subset
- L311 _private member_ `FCollectionAttributeKey BoneIndicesKey;` — `UPROPERTY(meta = (DisplayName = "Bone Indices", DataflowIndices))` — Bone indices key to be used in other nodes if necessary
- L315 _private member_ `FCollectionAttributeKey BoneWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Bone Weights", DataflowWeights))` — Bone weights key to be used in other nodes if necessary
- L319 _private member_ `FCollectionAttributeKey SplineParamKey;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Spline Parameter"))` — Spline skinning parameter key
- L323 _private member_ `FCollectionAttributeKey SplineBonesKey;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Spline Bones"))` — Spline bones key. Used for storing root and end spline bone for each vertex.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Groom` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Groom`)
- L16 _prototype_ `FCollectionAttributeKey GetSplineParamKey();` (scope `UE::Groom::Private`) — Retrieve the spline param key
- L19 _prototype_ `FCollectionAttributeKey GetSplineBonesKey();` (scope `UE::Groom::Private`) — Retrieve the spline bones key
- L179 _namespace_ `namespace UE`
- L179 _namespace_ `namespace Groom` (scope `UE`)
- L179 _namespace_ `namespace Private` (scope `UE::Groom`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/BuildGuidesLODsNode.h` (Public)


#### struct `FBuildGuidesLODsDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FBuildGuidesLODsDataflowNode : public FDataflowNode`  
_L17-50_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Builds the guides LODs
- L36 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L41 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Managed array collection to be used to store data
- L45 _public member_ `FCollectionAttributeKey CurveParentsKey;` — `UPROPERTY(meta = (DisplayName = "Curve Parents", DataflowOutput))` — Curve parent indices key to be used in other nodes if necessary
- L49 _public member_ `FCollectionAttributeKey CurveLodsKey;` — `UPROPERTY(meta = (DisplayName = "Curve Lods", DataflowOutput))` — Curve lods indices key to be used in other nodes if necessary

#### struct `FBuildCurveLODsDataflowNode`  
`struct FBuildCurveLODsDataflowNode : public FDataflowNode`  
_L54-85_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Builds the curves LODs
- L67 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L72 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store data
- L76 _private member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Curve Selection"))` — Curve selection to focus the geometry LODs spatially
- L80 _private member_ `FCollectionAttributeKey CurveParentsKey;` — `UPROPERTY(meta = (DisplayName = "Curve Parents", DataflowOutput))` — Curve parent indices key to be used in other nodes if necessary
- L84 _private member_ `FCollectionAttributeKey CurveLodsKey;` — `UPROPERTY(meta = (DisplayName = "Curve Lods", DataflowOutput))` — Curve lods indices key to be used in other nodes if necessary

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/GenerateGuidesCurvesNode.h` (Public)


#### struct `FGenerateGuidesCurvesDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FGenerateGuidesCurvesDataflowNode : public FDataflowNode`  
_L14-41_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Build the guides curves from the strands
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L36 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L40 _public member_ `int32 GuidesCount = 0;` — `UPROPERTY(EditAnywhere, Category="Geometry", meta = (DisplayName = "Guides Count"))` — Max number of guides

#### struct `FGenerateCurveGeometryDataflowNode`  
`struct FGenerateCurveGeometryDataflowNode : public FDataflowNode`  
_L45-80_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Build the curve geometry from a collection containing curves
- L58 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L63 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L67 _private member_ `FManagedArrayCollection SourceCurves;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Source Curves"))` — Managed array collection to be used to store datas
- L71 _private member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Curve Selection"))` — Curve selection to focus the curves generation spatially
- L75 _private member_ `int32 CurveCount = 0;` — `UPROPERTY(EditAnywhere, Category="Geometry", meta = (DataflowInput, DisplayName = "Guides Count"))` — Max number of guides
- L79 _private member_ `bool bMergeCurves = false;` — `UPROPERTY(EditAnywhere, Category="Geometry", meta = (DisplayName = "Merge Curves"))` — Flag to check if we can merge guides or not

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/GetGroomAssetNode.h` (Public)


#### enum `EGroomCollectionType`  
`enum class EGroomCollectionType : uint8`  
_L14-21_
- reflection: `UENUM()`
- L17 _public enumerator_ `Strands UMETA(DisplayName = "Strands")` — Strands type (Rendering Mesh)
- L20 _public enumerator_ `Guides UMETA(DisplayName = "Guides")` — Guides type (Simulation Mesh)

#### struct `FGetGroomAssetDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FGetGroomAssetDataflowNode : public FDataflowNode`  
_L25-54_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Get the groom asset
- L40 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L45 _public member_ `TObjectPtr<const UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DisplayName = "GroomAsset"))` — Input asset to read the guides from
- L49 _public member_ `EGroomCollectionType CurvesType = EGroomCollectionType::Strands;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DisplayName = "Display Curves"))` — Type of curves to use to fill the groom collection (guides/strands)
- L53 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))` — Managed array collection used to store the guides

#### struct `FGetGroomAssetDataflowNode_v2`  
`struct FGetGroomAssetDataflowNode_v2 : public FDataflowNode`  
_L58-78_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Get the groom asset
- L72 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L77 _public member_ `TObjectPtr<const UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DataflowOutput, DisplayName = "Groom Asset"))` — Groom asset that will be used in the dataflow graph

#### struct `FGroomAssetToCollectionDataflowNode`  
`struct FGroomAssetToCollectionDataflowNode : public FDataflowNode`  
_L82-113_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Transform a groom asset to a collection
- L95 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L100 _private member_ `TObjectPtr<const UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DataflowInput, DisplayName = "Groom Asset"))` — Input asset to read the guides from
- L104 _private member_ `EGroomCollectionType CurvesType = EGroomCollectionType::Guides;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DisplayName = "Curves Type"), meta = (DataflowInput))` — Type of curves to use to fill the groom collection (guides/strands)
- L108 _private member_ `float CurvesThickness = 0.5;` — `UPROPERTY(EditAnywhere, Category = "Geometry", meta = (DataflowInput, DisplayName = "Curves Thickness"))` — Curves thickness for geometry generation
- L112 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection used to store the curves

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/GetGroomAttributesNodes.h` (Public)


#### enum `EGroomAttributeType`  
`enum class EGroomAttributeType : uint8`  
_L15-22_
- reflection: `UENUM()`
- desc: Enum to pick groom attribute type
- L17 _public enumerator_ `KinematicWeights UMETA(DisplayName = "Kinematic Weights")`
- L18 _public enumerator_ `BoneIndices UMETA(DisplayName = "Bone Indices")`
- L19 _public enumerator_ `BoneWeights UMETA(DisplayName = "Bone Weights")`
- L20 _public enumerator_ `CurveParents UMETA(DisplayName = "Curve Parents")`
- L21 _public enumerator_ `CurveLods UMETA(DisplayName = "Curve Lods")`

#### struct `FGetGroomAttributesDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FGetGroomAttributesDataflowNode : public FDataflowNode`  
_L26-55_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Get the kinematic weights attributes names
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L46 _public member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(meta = (DisplayName = "Attribute Key", DataflowOutput))` — Attribute key to build
- L50 _public member_ `EGroomCollectionType CurvesType = EGroomCollectionType::Guides;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DisplayName = "Curves Type"))` — Type of curves to use (guides/strands)
- L54 _public member_ `EGroomAttributeType AttributeType = EGroomAttributeType::KinematicWeights;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DisplayName = "Attribute Type"))` — Type of attribute to use

#### struct `FGetCurveAttributesDataflowNode`  
`struct FGetCurveAttributesDataflowNode : public FDataflowNode`  
_L60-83_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Get the kinematic weights attributes names
- L73 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L78 _private member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(meta = (DisplayName = "Attribute Key", DataflowOutput))` — Attribute key to build
- L82 _private member_ `EGroomAttributeType AttributeType = EGroomAttributeType::KinematicWeights;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DisplayName = "Attribute Type"))` — Type of attribute to use

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/GroomAssetTerminalNode.h` (Public)


#### struct `FGroomAssetTerminalDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FGroomAssetTerminalDataflowNode : public FDataflowTerminalNode`  
_L18-47_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, DataflowTerminal, Deprecated="5.7"))`
- inherits: `FDataflowTerminalNode`
- L28 _public prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L29 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L33 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L37 _public member_ `TArray<FCollectionAttributeKey> AttributeKeys;` — `UPROPERTY()` — List of attribute keys that will be used to save matching attributes in the collection.
- L40 _public member_ `TArray<FName> AttributeNames;` — `UPROPERTY(EditAnyWhere, Category = Attributes, EditFixedSize)`
- L44 _private member_ `TWeakObjectPtr<UDataflow> DataflowAssetWeakPtr;`
- L46 _private member_ `static constexpr int32 NumOtherInputs = 1;`

#### struct `FGroomAssetTerminalDataflowNode_v2`  
`struct FGroomAssetTerminalDataflowNode_v2 : public FDataflowTerminalNode`  
_L50-105_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- L57 _public prototype_ `FGroomAssetTerminalDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L62 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L63 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L64 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L65 _private function_ `virtual bool CanAddPin() const override`
- L66 _private function_ `virtual bool CanRemovePin() const override`
- L67 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L68 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L69 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L73 _private member_ `FManagedArrayCollection StrandsCollection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Strands Collection"))`
- L76 _private member_ `FManagedArrayCollection GuidesCollection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Guides Collection"))`
- L80 _private member_ `TArray<FCollectionAttributeKey> AttributeKeys;` — `UPROPERTY()` — List of attribute keys that will be used to save matching attributes in the collection.
- L84 _private member_ `TArray<FName> AttributeNames;` — `UPROPERTY(EditAnyWhere, Category = Attributes, EditFixedSize)` — Attributes names used for the keys
- L87 _private prototype_ `UE::Dataflow::TConnectionReference<FCollectionAttributeKey> GetConnectionReference(int32 Index) const;` — Get the connection reference matching an attribute key index
- L90 _private prototype_ `virtual bool ShouldInvalidateOnPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent) const override;`
- L91 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L92 _private prototype_ `virtual bool SupportsDropConnectionOnNode(FName TypeName, UE::Dataflow::FPin::EDirection Direction) const override;`
- L93 _private prototype_ `virtual const FDataflowConnection* OnDropConnectionOnNode(const FDataflowConnection& DroppedConnection) override;`
- L97 _private prototype_ `void SyncInputNames();` — Sync input names with the keys
- L100 _private prototype_ `FName GenerateUniqueInputName(FName BaseName) const;` — Generate a unique input name
- L102 _private member_ `TWeakObjectPtr<UDataflow> DataflowAssetWeakPtr;`
- L104 _private member_ `static constexpr int32 NumOtherInputs = 2;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/HairStrandsDataflowModule.h` (Public)


#### class `FHairStrandsDataflowModule`  
`class FHairStrandsDataflowModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- desc: Hair dataflow construction module public interface
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/ResampleGuidesPointsNode.h` (Public)


#### enum `EGroomNumPoints`  
`enum class EGroomNumPoints : uint8`  
_L15-34_
- reflection: `UENUM(BlueprintType)`
- desc: Enum to pick the number of points per guide
- L18 _public enumerator_ `Default = 0 UMETA(DisplayName = "Default")` — Default behavior coming from the strands size in the physics settings
- L21 _public enumerator_ `Size4 = 4 UMETA(DisplayName = "4 Points")` — 4 points / curve
- L24 _public enumerator_ `Size8 = 8 UMETA(DisplayName = "8 Points")` — 8 points / curve
- L27 _public enumerator_ `Size16 = 16 UMETA(DisplayName = "16 Points")` — 16 points / curve
- L30 _public enumerator_ `Size32 = 32 UMETA(DisplayName = "32 Points")` — 32 points / curve
- L33 _public enumerator_ `Size64 = 64 UMETA(DisplayName = "64 Points")` — 64 points / curve

#### struct `FResampleGuidesPointsDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FResampleGuidesPointsDataflowNode : public FDataflowNode`  
_L38-65_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Resample the groom guides with a fixed number of points (in physics strands size)
- L55 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L60 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Managed array collection to be used to store datas
- L64 _public member_ `EGroomNumPoints PointsCount = EGroomNumPoints::Default;` — `UPROPERTY(EditAnywhere, Category="Geometry", meta = (DisplayName = "Points Count"))` — Max number of points

#### struct `FResampleCurvePointsDataflowNode`  
`struct FResampleCurvePointsDataflowNode : public FDataflowNode`  
_L69-108_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Resample the curves with a fixed number of points
- L82 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L87 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L91 _private member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Curve Selection"))` — Curve selection to focus the guides generation spatially
- L99 _private member_ `bool bResampleForSimulation = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When true, the resampling is done in the context of simulation - Favors power of two point count ( optimized for GPU solvers ) - Extend the begginning of the curve to maintain stiffness
- L103 _private member_ `EGroomNumPoints PointsCount = EGroomNumPoints::Size16;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "Points Count", EditCondition="bResampleForSimulation", EditConditionHides))` — Max number of points
- L107 _private member_ `int32 NumPoints = 16;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DataflowInput, DisplayName = "Points Count", ClampMin = "2", UIMin = "2", EditCondition = "!bResampleForSimulation", EditConditionHides))` — Max number of points (to be able to plug into a variable since enum is not supported in dataflow)

### `Plugins/Runtime/HairStrands/Source/HairStrandsDataflow/Public/SmoothGuidesCurvesNode.h` (Public)


#### struct `FSmoothGuidesCurvesDataflowNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FSmoothGuidesCurvesDataflowNode : public FDataflowNode`  
_L16-43_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom, Deprecated="5.7"))`
- inherits: `FDataflowNode`
- desc: Smooth the guides for more stable simulation
- L33 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L38 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Managed array collection to be used to store data
- L42 _public member_ `float SmoothingFactor = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Geometry", meta = (DisplayName = "Smoothing Factor", ClampMin="0", ClampMax="1", UIMin="0", UIMax="1"))` — Smoothing factor between 0 and 1

#### struct `FSmoothCurvePointsDataflowNode`  
`struct FSmoothCurvePointsDataflowNode : public FDataflowNode`  
_L47-74_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Smooth the curves for more stable deformation
- L60 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L65 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store data
- L69 _private member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Curve Selection"))` — Curve selection to focus the guides smoothing spatially
- L73 _private member_ `float SmoothingFactor = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Geometry", meta = (DataflowInput, DisplayName = "Smoothing Factor", ClampMin="0", ClampMax="1", UIMin="0", UIMax="1"))` — Smoothing factor between 0 and 1
