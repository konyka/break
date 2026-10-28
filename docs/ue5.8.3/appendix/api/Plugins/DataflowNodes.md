# Plugins / DataflowNodes

- module root: `Plugins/Dataflow/Source/DataflowNodes`
- headers: 74; symbols: 1589
- symbol kinds: class=7, delegate=3, enum=9, enumerator=24, function=66, macro=14, member=612, namespace=63, prototype=588, struct=193, typedef=10
- PrivateDependencyModuleNames: DynamicMesh, GeometryFramework, ImageCore, InputCore, ModelingComponents, PropertyEditor, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StaticMeshDescription
- PublicDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowEnginePlugin, Engine, GeometryCore, MeshConversion, MeshDescription, SkeletalMeshDescription

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/Customization/DataflowToolNodeSnapshotCustomization.h` (Private)


#### class `FDataflowToolNodeSnapshotCustomization`  
`class FDataflowToolNodeSnapshotCustomization : public IPropertyTypeCustomization`  
_L11-30_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L17 _public prototype_ `static TSharedRef<SWidget> BuildWidget(TSharedRef<IPropertyHandle> SnapshotHandle);` — Reusable — call this anywhere you have a handle to a snapshot element
- L19 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _public function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

#### class `FDataflowToolNodeSnapshotSetCustomization`  
`class FDataflowToolNodeSnapshotSetCustomization : public IPropertyTypeCustomization`  
_L32-72_
- inherits: `IPropertyTypeCustomization`
- L35 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L37 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L42 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L48 _private typedef_ `using FSnapshotItemPtr = TSharedPtr<IPropertyHandle>;`
- L50 _private member_ `TSharedPtr<IPropertyHandle> SnapshotSetHandle;`
- L51 _private member_ `TSharedPtr<IPropertyHandle> ArrayHandle;`
- L52 _private member_ `TSharedPtr<IPropertyHandle> ActiveIndexHandle;`
- L53 _private member_ `TArray<FSnapshotItemPtr> ListItems;`
- L54 _private member_ `TSharedPtr<SListView<FSnapshotItemPtr>> ListView;`
- L55 _private member_ `FSnapshotItemPtr SelectedItem;`
- L57 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L58 _private prototype_ `void RefreshView();`
- L59 _private prototype_ `void RefreshListItems();`
- L60 _private prototype_ `int32 GetSnapshotIndex(const FSnapshotItemPtr& Item) const;`
- L61 _private prototype_ `bool IsActiveSnapshot(const FSnapshotItemPtr& Item) const;`
- L63 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow( FSnapshotItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L67 _private prototype_ `void OnSelectionChanged( FSnapshotItemPtr Item, ESelectInfo::Type SelectInfo);`
- L71 _private prototype_ `FText GetHeaderText() const;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowCollectionAttributeUtils.h` (Private)


#### struct `UE::Dataflow::FDataflowCollectionFacade`  
`struct FDataflowCollectionFacade`  
_L13-27_
- desc: General collection facade to help nodes to deal with both Cloth and geometry collections
- L16 _public prototype_ `FDataflowCollectionFacade(const FManagedArrayCollection& Collection, FName TargetGroup);`
- L18 _public prototype_ `TConstArrayView<FVector3f> GetVertexPositions() const;`
- L19 _public prototype_ `TConstArrayView<FIntVector> GetTriangleIndices() const;`
- L20 _public prototype_ `TConstArrayView<int32> Get2Dto3DMapping() const;`
- L23 _private typedef_ `using FTargetGroupInfo = FDataflowAddScalarVertexPropertyCallbackRegistry::FTargetGroupInfo;`
- L25 _private member_ `const FManagedArrayCollection& Collection;`
- L26 _private member_ `FTargetGroupInfo TargetGroupInfo;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowCollectionSetSkinningSkeletalMesh.h` (Private)


#### struct `FDataflowCollectionSetSkinningSkeletalMesh`  
`struct FDataflowCollectionSetSkinningSkeletalMesh : public FDataflowNode`  
_L17-44_
- reflection: `USTRUCT(meta = (Experimental, DataflowGroom))`
- inherits: `FDataflowNode`
- desc: Set the skeletal mesh for the collection
- L27 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L32 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))` — Managed array collection to be used to store datas
- L36 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh", meta = (DataflowInput, DataflowPassthrough = "SkeletalMesh"))` — Skeletal mesh binding to be stored in the collection
- L39 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh", meta = (DataflowInput, DisplayName = "LOD Index"))`
- L43 _public member_ `FDataflowGeometrySelection GeometrySelection;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh", meta = (DataflowInput))` — Geometries to set skinning skeletal mesh on

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowCollectionSkeletalMeshUtils.h` (Private)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Dataflow` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L24 _function_ `static bool CreateSkeletalMesh(USkeletalMesh* SkeletalMesh, const TArray<UE::Geometry::FDynamicMesh3>& DynamicMeshes, const FReferenceSkeleton& ReferenceSkeleton)` (scope `UE::Dataflow::Private`)
- L81 _function_ `static bool BuildSkeletalMeshes(TArray<TObjectPtr<USkeletalMesh>>& SkeletalMeshes, const TSharedPtr<const FManagedArrayCollection>& RenderCollection, const FReferenceSkeleton& ReferenceSkeleton)` (scope `UE::Dataflow::Private`)
- L111 _function_ `static int32 ComputeHasFromRefSkeleton(const FReferenceSkeleton& ReferenceSkeleton)` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowContextOverridesNodes.h` (Private)


#### struct `FFloatOverrideDataflowNode`  
`struct FFloatOverrideDataflowNode : public FDataflowNode`  
_L14-36_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L24 _public member_ `FName KeyName = "Fl` — `UPROPERTY(EditAnywhere, Category = "Overrides")`
- L27 _public member_ `float ValueOut = 0.f;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Float"))`
- L29 _public function_ `FFloatOverrideDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L35 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWNODES_API`
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace Dataflow` (scope `UE`)
- L41 _prototype_ `void RegisterContextOverridesNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowGetCollectionBoundsNode.h` (Private)


#### struct `FDataflowGetCollectionBoundsNode`  
`struct FDataflowGetCollectionBoundsNode : public FDataflowNode`  
_L15-45_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get the bounds of the vertices of a specific collection
- L26 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection))` — Collection to compute the bounds from
- L30 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowInput))` — Selection input. To set the selection type rt mouse click on the Selection output
- L34 _private member_ `FBox Bounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DisplayName = "Box", DataflowOutput))` — resulting bounding box of the collection
- L38 _private member_ `FSphere Sphere = FSphere(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DataflowOutput))` — resulting bounding sphere of the collection
- L42 _private member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = Target)` — Vertex group to use
- L44 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace Dataflow` (scope `UE`)
- L49 _prototype_ `void RegisterGetCollectionBoundsNode();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowMeshMakeNodes.h` (Private)


#### enum `EMakeMeshTypeEnum`  
`enum class EMakeMeshTypeEnum : uint8`  
_L23-28_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `Sphere UMETA(DisplayName = "Sphere")`
- L26 _public enumerator_ `Capsule UMETA(DisplayName = "Capsule")`
- L27 _public enumerator_ `Cylinder UMETA(DisplayName = "Cylinder")`

#### struct `FMakeSphereMeshDataflowNode`  
`struct FMakeSphereMeshDataflowNode : public FDataflowNode`  
_L35-62_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a sphere mesh DEPRECATED 5.8 - use FMakeSphereMeshDataflowNode_v2 instead
- L43 _public member_ `float Radius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Sphere Radius
- L47 _public member_ `int32 NumPhi = 12;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DisplayName = "Steps Phi", UIMin = "3", ClampMin = "3"))` — Sphere numphi
- L51 _public member_ `int32 NumTheta = 12;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DisplayName = "Steps Theta", UIMin = "3", ClampMin = "3"))` — Sphere numtheta
- L55 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L58 _public prototype_ `FMakeSphereMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L61 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeSphereMeshDataflowNode_v2`  
`struct FMakeSphereMeshDataflowNode_v2 : public FDataflowNode`  
_L68-95_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a sphere mesh
- L76 _private member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Sphere Radius
- L80 _private member_ `int32 NumPhi = 12;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DisplayName = "Steps Phi", UIMin = "3", ClampMin = "3"))` — Sphere numphi
- L84 _private member_ `int32 NumTheta = 12;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DisplayName = "Steps Theta", UIMin = "3", ClampMin = "3"))` — Sphere numtheta
- L88 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L91 _public prototype_ `FMakeSphereMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L94 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeCapsuleMeshDataflowNode`  
`struct FMakeCapsuleMeshDataflowNode : public FDataflowNode`  
_L102-137_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a capsule mesh DEPRECATED 5.8 - use FMakeCapsuleMeshDataflowNode_v2 instead
- L110 _private member_ `float Radius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Radius of capsule
- L114 _private member_ `float SegmentLength = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Length of capsule line segment, so total height is SegmentLength + 2*Radius
- L118 _private member_ `int32 NumHemisphereArcSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "5", ClampMin = "5"))` — Number of vertices along the 90-degree arc from the pole to edge of spherical cap.
- L122 _private member_ `int32 NumCircleSteps = 6;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "3", ClampMin = "3"))` — Number of vertices along each circle
- L126 _private member_ `int32 NumSegmentSteps = 0;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "0", ClampMin = "0"))` — Number of subdivisions lengthwise along the cylindrical section
- L130 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L133 _public prototype_ `FMakeCapsuleMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L136 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeCapsuleMeshDataflowNode_v2`  
`struct FMakeCapsuleMeshDataflowNode_v2 : public FDataflowNode`  
_L143-178_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a capsule mesh
- L151 _private member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Radius of capsule
- L155 _private member_ `float SegmentLength = 100.f;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Length of capsule line segment, so total height is SegmentLength + 2*Radius
- L159 _private member_ `int32 NumHemisphereArcSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "5", ClampMin = "5"))` — Number of vertices along the 90-degree arc from the pole to edge of spherical cap.
- L163 _private member_ `int32 NumCircleSteps = 6;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "3", ClampMin = "3"))` — Number of vertices along each circle
- L167 _private member_ `int32 NumSegmentSteps = 0;` — `UPROPERTY(EditAnywhere, Category = "Capsule", meta = (UIMin = "0", ClampMin = "0"))` — Number of subdivisions lengthwise along the cylindrical section
- L171 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L174 _public prototype_ `FMakeCapsuleMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L177 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeCylinderMeshDataflowNode`  
`struct FMakeCylinderMeshDataflowNode : public FDataflowNode`  
_L185-220_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a cylinder mesh DEPRECATED 5.8 - use FMakeCylinderMeshDataflowNode_v2 instead
- L193 _private member_ `float Radius1 = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Radius1 of cylinder
- L197 _private member_ `float Radius2 = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Radius2 of cylinder
- L201 _private member_ `float Height = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Height of cylinder
- L205 _private member_ `int32 LengthSamples = 0;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0", ClampMin = "0"))` — LengthSamples of cylinder
- L209 _private member_ `int32 AngleSamples = 12;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "4", ClampMin = "4"))` — AngleSamples of cylinder
- L213 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L216 _public prototype_ `FMakeCylinderMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L219 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeCylinderMeshDataflowNode_v2`  
`struct FMakeCylinderMeshDataflowNode_v2 : public FDataflowNode`  
_L226-261_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a cylinder mesh
- L234 _private member_ `float Radius1 = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Radius1 of cylinder
- L238 _private member_ `float Radius2 = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Radius2 of cylinder
- L242 _private member_ `float Height = 100.f;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Height of cylinder
- L246 _private member_ `int32 LengthSamples = 0;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "0", ClampMin = "0"))` — LengthSamples of cylinder
- L250 _private member_ `int32 AngleSamples = 12;` — `UPROPERTY(EditAnywhere, Category = "Cylinder", meta = (UIMin = "4", ClampMin = "4"))` — AngleSamples of cylinder
- L254 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L257 _public prototype_ `FMakeCylinderMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L260 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeBoxMeshDataflowNode`  
`struct FMakeBoxMeshDataflowNode : public FDataflowNode`  
_L268-303_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a box mesh DEPRECATED 5.8 - use FMakeBoxMeshDataflowNode_v2 instead
- L276 _private member_ `FVector Center = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Box")`
- L280 _private member_ `FVector Size = FVector(5.0);` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "0.1", ClampMin = "0.1"))`
- L284 _private member_ `int32 SubdivisionsX = 3;` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "1", ClampMin = "1"))`
- L288 _private member_ `int32 SubdivisionsY = 3;` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "1", ClampMin = "1"))`
- L292 _private member_ `int32 SubdivisionsZ = 3;` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "1", ClampMin = "1"))`
- L296 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L299 _public prototype_ `FMakeBoxMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L302 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeBoxMeshDataflowNode_v2`  
`struct FMakeBoxMeshDataflowNode_v2 : public FDataflowNode`  
_L309-344_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a box mesh
- L317 _private member_ `FVector Center = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (GizmoType = "Translate"))` — Center of box
- L321 _private member_ `FVector Size = FVector(100.0);` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Size of box
- L325 _private member_ `int32 SubdivisionsX = 3;` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "1", ClampMin = "1"))` — Subdivisions in X
- L329 _private member_ `int32 SubdivisionsY = 3;` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "1", ClampMin = "1"))` — Subdivisions in Y
- L333 _private member_ `int32 SubdivisionsZ = 3;` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (UIMin = "1", ClampMin = "1"))` — Subdivisions in Z
- L337 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L340 _public prototype_ `FMakeBoxMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L343 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeDiscMeshDataflowNode`  
`struct FMakeDiscMeshDataflowNode : public FDataflowNode`  
_L351-390_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a disc mesh DEPRECATED 5.8 - use FMakeDiscMeshDataflowNode_v2 instead
- L359 _private member_ `float Radius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (UIMin = "0.1"))` — Radius
- L363 _private member_ `FVector Normal = FVector::UnitZ();` — `UPROPERTY(EditAnywhere, Category = "Disc")` — Normal vector of all vertices will be set to this value. Default is +Z axis.
- L367 _private member_ `int32 AngleSamples = 12;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices around circumference
- L371 _private member_ `int32 RadialSamples = 2;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices along radial spokes
- L375 _private member_ `float StartAngle = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Disc")` — Start of angle range spanned by disc, in degrees
- L379 _private member_ `float EndAngle = 360.f;` — `UPROPERTY(EditAnywhere, Category = "Disc")` — End of angle range spanned by disc, in degrees
- L383 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L386 _public prototype_ `FMakeDiscMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L389 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeDiscMeshDataflowNode_v2`  
`struct FMakeDiscMeshDataflowNode_v2 : public FDataflowNode`  
_L396-435_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a disc mesh
- L404 _private member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (UIMin = "0.1"))` — Radius
- L408 _private member_ `FVector Normal = FVector::UnitZ();` — `UPROPERTY(EditAnywhere, Category = "Disc")` — Normal vector of all vertices will be set to this value. Default is +Z axis.
- L412 _private member_ `int32 AngleSamples = 12;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices around circumference
- L416 _private member_ `int32 RadialSamples = 2;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices along radial spokes
- L420 _private member_ `float StartAngle = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (Units = "Degrees"))` — Start of angle range spanned by disc, in degrees
- L424 _private member_ `float EndAngle = 360.f;` — `UPROPERTY(EditAnywhere, Category = "Disc", meta = (Units = "Degrees"))` — End of angle range spanned by disc, in degrees
- L428 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L431 _public prototype_ `FMakeDiscMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L434 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowStairTypeEnum`  
`enum class EDataflowStairTypeEnum : uint8`  
_L438-444_
- reflection: `UENUM(BlueprintType)`
- L440 _public enumerator_ `Linear UMETA(DisplayName = "Linear")`
- L441 _public enumerator_ `Floating UMETA(DisplayName = "Floating")`
- L442 _public enumerator_ `Curved UMETA(DisplayName = "Curved")`
- L443 _public enumerator_ `Spiral UMETA(DisplayName = "Spiral")`

#### struct `FMakeStairMeshDataflowNode`  
`struct FMakeStairMeshDataflowNode : public FDataflowNode`  
_L451-494_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a stair mesh DEPRECATED 5.8 - use FMakeStairMeshDataflowNode_v2 instead
- L459 _private member_ `EDataflowStairTypeEnum StairType = EDataflowStairTypeEnum::Linear;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "2"))` — Type of staircase
- L463 _private member_ `int32 NumSteps = 8;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "2"))` — The number of steps in this staircase.
- L467 _private member_ `float StepWidth = 150.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10"))` — The width of each step.
- L471 _private member_ `float StepHeight = 20.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10"))` — The height of each step.
- L475 _private member_ `float StepDepth = 30.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10", EditCondition = "StairType == EDataflowStairTypeEnum::Linear || StairType == EDataflowStairTypeEnum::Floating", EditConditionHides))` — The depth of each step.
- L479 _private member_ `float CurveAngle = 90.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10", EditCondition = "StairType == EDataflowStairTypeEnum::Curved || StairType == EDataflowStairTypeEnum::Spiral", EditConditionHides))` — Curve angle of the staircase (in degrees)
- L483 _private member_ `float InnerRadius = 150.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10", EditCondition = "StairType == EDataflowStairTypeEnum::Curved || StairType == EDataflowStairTypeEnum::Spiral", EditConditionHides))` — Inner radius of the curved staircase
- L487 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L490 _public prototype_ `FMakeStairMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L493 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeStairMeshDataflowNode_v2`  
`struct FMakeStairMeshDataflowNode_v2 : public FDataflowNode`  
_L500-543_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a stair mesh
- L508 _private member_ `EDataflowStairTypeEnum StairType = EDataflowStairTypeEnum::Linear;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "2"))` — Type of staircase
- L512 _private member_ `int32 NumSteps = 8;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "2"))` — The number of steps in this staircase.
- L516 _private member_ `float StepWidth = 150.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10"))` — The width of each step.
- L520 _private member_ `float StepHeight = 20.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10"))` — The height of each step.
- L524 _private member_ `float StepDepth = 30.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10", EditCondition = "StairType == EDataflowStairTypeEnum::Linear || StairType == EDataflowStairTypeEnum::Floating", EditConditionHides))` — The depth of each step.
- L528 _private member_ `float CurveAngle = 90.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (Units = "Degrees", UIMin = "10.", ClampMin = "10", EditCondition = "StairType == EDataflowStairTypeEnum::Curved || StairType == EDataflowStairTypeEnum::Spiral", EditConditionHides))` — Curve angle of the staircase (in degrees)
- L532 _private member_ `float InnerRadius = 150.f;` — `UPROPERTY(EditAnywhere, Category = "Stair", meta = (UIMin = "10.", ClampMin = "10", EditCondition = "StairType == EDataflowStairTypeEnum::Curved || StairType == EDataflowStairTypeEnum::Spiral", EditConditionHides))` — Inner radius of the curved staircase
- L536 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L539 _public prototype_ `FMakeStairMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L542 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeRectangleMeshDataflowNode`  
`struct FMakeRectangleMeshDataflowNode : public FDataflowNode`  
_L550-589_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a rectangle mesh DEPRECATED 5.8 - use FMakeRectangleMeshDataflowNode_v2 instead
- L558 _private member_ `FVector Origin = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (DataflowInput))` — Rectangle will be translated so that center is at this point
- L562 _private member_ `FVector Normal = FVector::UnitZ();` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (DataflowInput))` — Normal vector of all vertices will be set to this value. Default is +Z axis.
- L566 _private member_ `float Width = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Width of rectangle
- L570 _private member_ `float Height = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Height of rectangle
- L574 _private member_ `int32 WidthVertexCount = 3;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices along Width axis
- L578 _private member_ `int32 HeightVertexCount = 3;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices along Height axis
- L582 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L585 _public prototype_ `FMakeRectangleMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L588 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeRectangleMeshDataflowNode_v2`  
`struct FMakeRectangleMeshDataflowNode_v2 : public FDataflowNode`  
_L595-634_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a rectangle mesh
- L603 _private member_ `FVector Origin = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (DataflowInput, GizmoType = "Translate"))` — Rectangle will be translated so that center is at this point
- L607 _private member_ `FVector Normal = FVector::UnitZ();` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (DataflowInput))` — Normal vector of all vertices will be set to this value. Default is +Z axis.
- L611 _private member_ `float Width = 100.f;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Width of rectangle
- L615 _private member_ `float Height = 100.f;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "0.1", ClampMin = "0.1"))` — Height of rectangle
- L619 _private member_ `int32 WidthVertexCount = 3;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices along Width axis
- L623 _private member_ `int32 HeightVertexCount = 3;` — `UPROPERTY(EditAnywhere, Category = "Rectangle", meta = (UIMin = "2", ClampMin = "2"))` — Number of vertices along Height axis
- L627 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L630 _public prototype_ `FMakeRectangleMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L633 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeTorusMeshDataflowNode`  
`struct FMakeTorusMeshDataflowNode : public FDataflowNode`  
_L641-676_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a torus mesh DEPRECATED 5.8 - use FMakeTorusMeshDataflowNode_v2 instead
- L649 _private member_ `FVector Origin = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (DataflowInput))` — Torus will be translated so that center is at this point
- L653 _private member_ `float Radius1 = 4.f;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "0.01", ClampMin = "0.01"))` — Radius of the profile
- L657 _private member_ `int32 ProfileVertexCount = 12;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "3", ClampMin = "3"))` — Number of vertices on the profile
- L661 _private member_ `float Radius2 = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "0.01", ClampMin = "0.01"))` — Radius of sweep curve
- L665 _private member_ `int32 SweepVertexCount = 12;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "3", ClampMin = "3"))` — Number of vertices on the sweep curve
- L669 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L672 _public prototype_ `FMakeTorusMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L675 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeTorusMeshDataflowNode_v2`  
`struct FMakeTorusMeshDataflowNode_v2 : public FDataflowNode`  
_L682-717_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a torus mesh
- L690 _private member_ `FVector Origin = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (DataflowInput, GizmoType = "Translate"))` — Torus will be translated so that center is at this point
- L694 _private member_ `float Radius1 = 25.f;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "0.01", ClampMin = "0.01"))` — Radius of the profile
- L698 _private member_ `int32 ProfileVertexCount = 12;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "3", ClampMin = "3"))` — Number of vertices on the profile
- L702 _private member_ `float Radius2 = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "0.01", ClampMin = "0.01"))` — Radius of sweep curve
- L706 _private member_ `int32 SweepVertexCount = 12;` — `UPROPERTY(EditAnywhere, Category = "Torus", meta = (UIMin = "3", ClampMin = "3"))` — Number of vertices on the sweep curve
- L710 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L713 _public prototype_ `FMakeTorusMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L716 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L719 _namespace_ `namespace UE`
- L719 _namespace_ `namespace Dataflow` (scope `UE`)
- L721 _prototype_ `void DataflowMeshMakeNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowMeshNodes.h` (Private)


#### struct `FDisplaceDataflowMeshDataflowNode`  
`struct FDisplaceDataflowMeshDataflowNode : public FDataflowNode`  
_L19-48_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Displace mesh vertices by a sampler If the connected sampler is a VectorSampler, the selected vertices will be displaced by the sampled vector value. If the connected sampler is a FloatSampler, the selected vertices will be displaced along the vertex normal by the sampled float value.
- L31 _public member_ `FDataflowVertexSelection Selection;` — `UPROPERTY(meta = (DataflowInput))` — VertexSelection to specify which vertices will be displaced. If it is not connected, all vertices will be displaced.
- L37 _public member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowInput))` — Sampler to displace vertices If the sampler is a VectorSampler, the selected vertices will be displaced by the sampled vector value. If the sampler is a FloatSampler, the selected vertices will be displaced along the vertex normal by the sampled float value.
- L41 _public member_ `bool bRecomputeNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Normals", DisplayName = "Recompute Vertex Normals")` — If it is true, vertex normals will be recomputed after diplacement
- L44 _public prototype_ `FDisplaceDataflowMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L47 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace Dataflow` (scope `UE`)
- L52 _prototype_ `void DataflowMeshNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowMeshSelectionNodes.h` (Private)


#### struct `FDataflowMeshSelectionCustomDataflowNode`  
`struct FDataflowMeshSelectionCustomDataflowNode : public FDataflowNode`  
_L23-46_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Creates any type of selection from a DataflowMesh by using a comma separated list Currentlly supperted types: Vertex/Face
- L35 _public member_ `FString Indices;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput))` — Comma separated list of indices (example: "0, 2, 5-10, 12-15") to specify the selection
- L39 _public member_ `FDataflowMeshSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Selection from the indices. To set the selection type rt mouse click on the Selection output
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L44 _public prototype_ `FDataflowMeshSelectionCustomDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Dataflow` (scope `UE`)
- L50 _prototype_ `void DataflowMeshSelectionNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowNodesPlugin.h` (Private)


#### class `IDataflowNodesPlugin`  
`class IDataflowNodesPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowPointsNodes.h` (Private)


#### struct `FFilterPointsByAttributeDataflowNode`  
`struct FFilterPointsByAttributeDataflowNode : public FDataflowNode`  
_L20-59_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects specified points from an incoming point set by an attribute value Currently supported attribute types: float, int32, bool
- L32 _public member_ `EFilterByAttributeOperation Operation = EFilterByAttributeOperation::Equal;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Operation
- L36 _public member_ `FString Attribute = FString("Dum` — `UPROPERTY(EditAnywhere, Category = "Filter", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Attribute"))` — Attribute used for the filtering operation
- L40 _public member_ `float Value = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Attribute value for the operation
- L44 _public member_ `float Value2 = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta = (EditCondition = "Operation == EFilterByAttributeOperation::InRangeInclusive || Operation == EFilterByAttributeOperation::InRangeExclusive"))` — Attribute value for the operation
- L48 _public member_ `FDataflowPoints FilteredPoints;` — `UPROPERTY(meta = (DataflowOutput))` — Points after filtering with the operation
- L52 _public member_ `FDataflowVertexSelection PointSelection;` — `UPROPERTY(meta = (DataflowOutput))` — VertexSelection storing the filtered points
- L54 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L55 _public prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`
- L58 _public prototype_ `FFilterPointsByAttributeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetPointsCollectionDataflowNode`  
`struct FGetPointsCollectionDataflowNode : public FDataflowNode`  
_L65-83_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Adds access to the collection of the DataflowPoints
- L73 _private member_ `FDataflowPoints Points;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Points", DataflowIntrinsic))` — FDataflowPoints  for the information
- L77 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Formatted string containing the groups and attributes
- L79 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L82 _public prototype_ `FGetPointsCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowSamplerToPointsNode`  
`struct FDataflowSamplerToPointsNode : public FDataflowNode`  
_L89-112_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Use a sampler to generate an attribute on points
- L95 _public prototype_ `FDataflowSamplerToPointsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L100 _private member_ `FDataflowPoints Points;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Points", DataflowIntrinsic))`
- L104 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(EditAnywhere, Category = "Source", meta = (DataflowInput))` — Sampler to use to set the value of the attribute
- L108 _private member_ `FString Attribute = FString("Dum` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Attribute"))` — Name of the attribute to set the value on
- L110 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L111 _private prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`

#### struct `FDataflowCollectionVerticesToPointsNode`  
`struct FDataflowCollectionVerticesToPointsNode : public FDataflowNode`  
_L118-160_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Create points from vertices in a collection
- L124 _public prototype_ `FDataflowCollectionVerticesToPointsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L129 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — GeometryCollection for the vertices
- L133 _private member_ `bool bCopyAttributes = true;` — `UPROPERTY(EditAnywhere, Category = "Attributes", meta = (EditCondition = "!bScatterExtraPoints"))` — Copy attributes from vertices to points, it is ignored when ScatterExtraPoints is on
- L137 _private member_ `FDataflowVertexSelection Selection;` — `UPROPERTY(meta = (DataflowInput))` — If connected, only the selected vertices will be part of the output
- L141 _private member_ `bool bScatterExtraPoints = false;` — `UPROPERTY(EditAnywhere, Category = "Extra Points")` — Add extra points
- L145 _private member_ `bool bDeterministic = true;` — `UPROPERTY(EditAnywhere, Category = "Extra Points")` — Use deterministic noise for the extra points generation
- L149 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Extra Points")` — Seed for the noise for the extra points generation
- L153 _private member_ `float PointDensity = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Extra Points", meta = (UIMin = 0.1f, ClampMin = 0.1f))` — Density for the extra points generation
- L157 _private member_ `FDataflowPoints Points;` — `UPROPERTY(meta = (DataflowOutput))` — Output points
- L159 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FPointsToDataflowPointsDataflowNode`  
`struct FPointsToDataflowPointsDataflowNode : public FDataflowNode`  
_L166-184_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts points (TArray<FVector>) to DataflowPoints
- L174 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Points to convert
- L178 _private member_ `FDataflowPoints OutPoints;` — `UPROPERTY(meta = (DataflowOutput))` — DataflowPoints output
- L180 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L183 _public prototype_ `FPointsToDataflowPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowPointsToPointsDataflowNode`  
`struct FDataflowPointsToPointsDataflowNode : public FDataflowNode`  
_L190-208_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts DataflowPoints to points (TArray<FVector>)
- L198 _private member_ `FDataflowPoints Points;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — DataflowPoints to convert
- L202 _private member_ `TArray<FVector> OutPoints;` — `UPROPERTY(meta = (DataflowOutput))` — Points output
- L204 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L207 _public prototype_ `FDataflowPointsToPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowGetPointsBoundsNode`  
`struct FDataflowGetPointsBoundsNode : public FDataflowNode`  
_L214-240_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get the bounds of the points
- L220 _public prototype_ `FDataflowGetPointsBoundsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L225 _private member_ `FDataflowPoints Points;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Points))` — Collection to compute the bounds from
- L229 _private member_ `FDataflowVertexSelection Selection;` — `UPROPERTY(meta = (DataflowInput))` — Selection input. To set the selection type rt mouse click on the Selection output
- L233 _private member_ `FBox Bounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DisplayName = "Box", DataflowOutput))` — resulting bounding box of the collection
- L237 _private member_ `FSphere Sphere = FSphere(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DataflowOutput))` — resulting bounding sphere of the collection
- L239 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L241 _namespace_ `namespace UE`
- L241 _namespace_ `namespace Dataflow` (scope `UE`)
- L243 _prototype_ `void DataflowPointsNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowSamplerToAttributeNode.h` (Private)


#### struct `FDataflowFloatSamplerToAttributeNode`  
`struct FDataflowFloatSamplerToAttributeNode : public FDataflowNode`  
_L18-45_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper", Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Use a foat sampler to generate the value of an attribute DEPRECATED 5.8 - use FDataflowSamplerToAttributeNode instead
- L29 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection))` — Collection to set the attribute data to
- L33 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DataflowInput))` — Sampler to use to set the value of the attribute
- L37 _private member_ `FString AttributeName;` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DataflowInput))` — Name of the attribute to set the value on
- L41 _private member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = Target)` — Vertex group to use
- L43 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L44 _private prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`

#### struct `FDataflowSamplerToAttributeNode`  
`struct FDataflowSamplerToAttributeNode : public FDataflowNode`  
_L53-102_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Use a float or vector sampler to generate the value of an attribute
- L59 _public prototype_ `FDataflowSamplerToAttributeNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L64 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection, DataflowIntrinsic))` — Collection to set the attribute data to
- L68 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DataflowInput))` — Sampler to use to set the value of the attribute
- L72 _private member_ `FString AttributeName = FString("Dum` — `UPROPERTY(EditAnywhere, Category = Attribute, meta = (DataflowInput, DataflowOutput, DataflowPassthrough = AttributeName))` — Name of the attribute to set the value on
- L79 _private member_ `bool bSaveAsColor = false;` — `UPROPERTY(EditAnywhere, Category = Attribute)` — If Sampler input is a FloatSampler and this flag is on then data will be saved as LinearColor using the sampled float values to create grayscale colors, If Sampler input is a VectorSampler type and this flag is on then data will be saved as LinearColor using the sampled vector values to set the colors
- L83 _private member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = Target)` — Vertex group to use
- L87 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput))` — Select vertices to sample value on them
- L90 _private member_ `bool bUseDefaultValue = false;` — `UPROPERTY(EditAnywhere, Category = Selection)`
- L94 _private member_ `float DefaultValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = Selection, meta = (EditCondition = bUseDefaultValue))` — This value gets assigned to the non-selected vertices, when the input sampler is a FloatSampler
- L98 _private member_ `FVector DefaultVectorValue = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Selection, meta = (EditCondition = bUseDefaultValue))` — This value gets assigned to the non-selected vertices, when the input sampler is a VectorSampler
- L100 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L101 _private prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`

#### Free symbols / members of external scopes

- L104 _namespace_ `namespace UE`
- L104 _namespace_ `namespace Dataflow` (scope `UE`)
- L106 _prototype_ `void RegisterSamplerToAttributeNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowSelectionNodes.h` (Private)


#### struct `FSelectionSetDataflowNode`  
`struct FSelectionSetDataflowNode : public FDataflowNode`  
_L17-38_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L23 _public typedef_ `typedef TArray<int32> DataType;`
- L26 _public member_ `FString Indices = FString("1 2` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L29 _public member_ `TArray<int32> IndicesOut;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "SelectionSet"))`
- L31 _public function_ `FSelectionSetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L37 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeSelectionSetDataflowNode`  
`struct FMakeSelectionSetDataflowNode : public FDataflowNode`  
_L41-68_
- reflection: `USTRUCT(meta = (GeometryCollection))`
- inherits: `FDataflowNode`
- L53 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Selection", DataflowIntrinsic))` — Selection to store in collection
- L57 _public member_ `FString Attribute = FString("Dum` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DataflowInput))` — Attribute used to store the selection in the collection. The group decided by the incoming selection's type
- L61 _public member_ `bool bStoreAsFloat = false;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — Store the selection as float instead of bool
- L63 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L64 _public prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`
- L67 _public prototype_ `FMakeSelectionSetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetSelectionSetDataflowNode`  
`struct FGetSelectionSetDataflowNode : public FDataflowNode`  
_L71-95_
- reflection: `USTRUCT(meta = (GeometryCollection))`
- inherits: `FDataflowNode`
- L79 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to use
- L84 _private member_ `FString Attribute = FString("Dum` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DataflowInput))` — Attribute used to store the selection in the collection. To set the selection type rt mouse click on the Selection output
- L88 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Output selection
- L90 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L91 _private prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`
- L94 _public prototype_ `FGetSelectionSetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAFLOWNODES_API`
- L97 _namespace_ `namespace UE`
- L97 _namespace_ `namespace Dataflow` (scope `UE`)
- L99 _prototype_ `void RegisterSelectionNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowSkeletonAssetTerminalNode.h` (Private)


#### struct `FSkeletonAssetTerminalNode`  
`struct FSkeletonAssetTerminalNode : public FDataflowTerminalNode`  
_L17-38_
- reflection: `USTRUCT(meta = (DataflowFlesh, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Dataflow terminal node to save a skeleton asset
- L28 _private member_ `TObjectPtr<const USkeleton> SourceSkeleton = nullptr;` — `UPROPERTY(meta = (DataflowInput))` — Source Skeleton used to override the skeleton asset
- L32 _private member_ `TObjectPtr<USkeleton> SkeletonAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Skeleton Asset to be saved
- L35 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L36 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowStaticMeshAssetNodes.h` (Private)


#### struct `FDataflowStaticMeshTerminalNode`  
`struct FDataflowStaticMeshTerminalNode : public FDataflowTerminalNode`  
_L17-49_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: terminal node to a save a static mesh asset
- L29 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowInput))` — Materials to set on the static mesh
- L36 _public member_ `FString AssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path of the asset to save to if not specified this will use the asset bound the dataflow graph this node belong to
- L40 _public member_ `TObjectPtr<UStaticMesh> StaticMeshAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Output static mesh asset created by this node
- L42 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L43 _public prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L45 _public prototype_ `bool ConvertDynamicMeshToStaticMesh(UE::Dataflow::FContext& Context, const UDynamicMesh& InMesh, const TArray<TObjectPtr<UMaterialInterface>>& InMaterials, UStaticMesh& OutMesh) const;`
- L48 _public prototype_ `FDataflowStaticMeshTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace Dataflow` (scope `UE`)
- L53 _prototype_ `void RegisterStaticMeshAssetNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowStaticMeshNodes.h` (Private)


#### struct `FGetStaticMeshDataflowNode_v2`  
`struct FGetStaticMeshDataflowNode_v2 : public FDataflowNode`  
_L21-37_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get a existing static mesh asset
- L31 _private member_ `TObjectPtr<const UStaticMesh> StaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput, DisplayName = "StaticMesh"))`
- L33 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L35 _private prototype_ `virtual bool SupportsAssetProperty(UObject* Asset) const override;`
- L36 _private prototype_ `virtual void SetAssetProperty(UObject* Asset) override;`

#### struct `FGetStaticMeshBoundingBoxDataflowNode`  
`struct FGetStaticMeshBoundingBoxDataflowNode : public FDataflowNode`  
_L43-70_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the local geometric bounding box a static mesh
- L51 _private member_ `TObjectPtr<const UStaticMesh> StaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput))` — Static Mesh to compute the bouning box from
- L55 _private member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Geometric bounding box of the input Static Mesh
- L59 _private member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Center of the resulting bounding box
- L63 _private member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Dimensions of the resulting bounding box in centimers
- L65 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L68 _public prototype_ `FGetStaticMeshBoundingBoxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetStaticMeshDataflowNode`  
`struct FGetStaticMeshDataflowNode : public FDataflowNode`  
_L79-98_
- reflection: `USTRUCT(meta = (Deprecated = 5.8))`
- inherits: `FDataflowNode`
- desc: Get a existing static mesh asset Note that this version of the node is deprecated, please use non deprecated version of the StaticMesh node
- L87 _public member_ `TObjectPtr<const UStaticMesh> StaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput, DisplayName = "StaticMesh"))`
- L90 _public member_ `FName PropertyName = "St` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L92 _public prototype_ `FGetStaticMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L94 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L96 _public prototype_ `virtual bool SupportsAssetProperty(UObject* Asset) const override;`
- L97 _public prototype_ `virtual void SetAssetProperty(UObject* Asset) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWNODES_API`
- L13 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogDataflowStaticMeshNodes, Log, All);`
- L101 _namespace_ `namespace UE`
- L101 _namespace_ `namespace Dataflow` (scope `UE`)
- L103 _prototype_ `void RegisterStaticMeshNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowTextureToAttributeNode.h` (Private)


#### struct `FDataflowTextureToAttributeNode`  
`struct FDataflowTextureToAttributeNode : public FDataflowNode`  
_L20-63_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Transfer data from a texture to a an attribute in a collection The texture is sampled at the specific UVs (UVChannel parameter) and is transfered to an float attribute in the selected vertex group Sampling is done using bilinear filtering
- L27 _public prototype_ `virtual ~FDataflowTextureToAttributeNode();`
- L32 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection))` — Collection to transfer the attribute data to
- L36 _private member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DataflowInput))` — Texture to transfer the attribute from
- L40 _private member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DataflowInput))` — UV channel to use to sample the texture
- L44 _private member_ `FString AttributeName;` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DataflowInput, DataflowOutput, DataflowPassthrough = AttributeName))` — Name of the attribute to to transfer the texture color to
- L48 _private member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = Target)` — Vertex group to use
- L52 _private member_ `bool bMultithreadProcessing = true;` — `UPROPERTY(EditAnywhere, Category = Performance)` — transfers texture data to vertices using Parallelfor
- L54 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L55 _private prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`
- L57 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L58 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L59 _private prototype_ `void StartListeningToTextureChanges();`
- L60 _private prototype_ `void StopListeningToTextureChanges();`
- L61 _private prototype_ `void OnTextureChanged(UObject* Object, FPropertyChangedEvent& Event);`
- L62 _private member_ `FDelegateHandle TextureChangeDelegateHandle;`

#### Free symbols / members of external scopes

- L65 _namespace_ `namespace UE`
- L65 _namespace_ `namespace Dataflow` (scope `UE`)
- L67 _prototype_ `void RegisterTextureToAttributeNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowTools.h` (Private)


#### struct `UE::Dataflow::FDataflowTools`  
`struct FDataflowTools`  
_L17-28_
- desc: Dataflow Node Tools
- L19 _public prototype_ `static void LogAndToastWarning(const FDataflowNode& DataflowNode, const FText& Headline, const FText& Details);`
- L27 _public prototype_ `static void MakeCollectionName(FString& InOutString);` — Turn a string into a valid collection group or attribute name. The resulting name won't contains spaces and any other special characters as listed in INVALID_OBJECTNAME_CHARACTERS (currently "',/.:|&!~\n\r\t@#(){}[]=;^%$`). It will also have all leading underscore removed, as these names are reserved for internal use.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)
- L31 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowNodes, Log, All);`
- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowNodes, Log, All);`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowVertexColorToAttributeNode.h` (Private)


#### struct `FDataflowVertexColorToAttributeNode`  
`struct FDataflowVertexColorToAttributeNode : public FDataflowNode`  
_L17-47_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Transfer data from a vertex color to a an attribute in a collection
- L28 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection))` — Collection to transfer the attribute data to
- L32 _private member_ `EDataflowImageChannel ColorChannel = EDataflowImageChannel::Red;` — `UPROPERTY(EditAnywhere, Category = Source, meta = (DataflowInput))` — Color channel to use as attribute value
- L36 _private member_ `FString AttributeName;` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DataflowInput))` — Name of the attribute to to transfer the vertex color to
- L40 _private member_ `float ScalingFactor = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DataflowInput, UIMin = 0.0, UIMax = 1.0, ClampMin = 0.0, ClampMax = 1.0))` — Scaling factor applied to vertex colours (in range 0-1)
- L44 _private member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = Target)` — Vertex group to use
- L46 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace Dataflow` (scope `UE`)
- L51 _prototype_ `void RegisterVertexColorToAttributeNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/DataflowVisualizeAttributeNode.h` (Private)


#### struct `FDataflowVisualizeAttributeNode`  
`struct FDataflowVisualizeAttributeNode : public FDataflowNode`  
_L16-39_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Node to visualize a specific attribute in the construction viewport as vertex color it supports a number of attribute type ( decimal, vector or boolean )
- L27 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection))` — Collection to read the data from
- L31 _private member_ `FString AttributeName;` — `UPROPERTY(EditAnywhere, Category = Target, meta = (DataflowInput))` — Name of the attribute to visualize
- L35 _private member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = Target)` — Vertex group matching the attribute
- L37 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L38 _private prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace Dataflow` (scope `UE`)
- L43 _prototype_ `void RegisterVisualizeAttributeNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowAbsSamplerNode.h` (Private)


#### struct `FDataflowAbsFloatSampler`  
`struct FDataflowAbsFloatSampler : public FDataflowFloatSamplerBase`  
_L14-25_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- desc: No Input Sampler nodes
- L18 _public prototype_ `virtual ~FDataflowAbsFloatSampler() override = default;`
- L19 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L20 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L24 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowAbsVectorSampler`  
`struct FDataflowAbsVectorSampler : public FDataflowVectorSamplerBase`  
_L28-39_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L32 _public prototype_ `virtual ~FDataflowAbsVectorSampler() override = default;`
- L33 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L34 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L38 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> Sampler;`

#### struct `FDataflowAbsSamplerNode`  
`struct FDataflowAbsSamplerNode : public FDataflowNode`  
_L45-58_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output an abs float sampler
- L51 _public prototype_ `FDataflowAbsSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L55 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L57 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowAddSamplerNode.h` (Private)


#### struct `FDataflowAddFloatSampler`  
`struct FDataflowAddFloatSampler : public FDataflowFloatSamplerBase`  
_L10-20_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L13 _public prototype_ `virtual ~FDataflowAddFloatSampler() override = default;`
- L14 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L15 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L19 _public member_ `TArray<TSharedPtr<const FDataflowFloatSamplerBase>> Samplers;` — list of samplers to add results from

#### struct `FDataflowAddVectorSampler`  
`struct FDataflowAddVectorSampler : public FDataflowVectorSamplerBase`  
_L23-33_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L26 _public prototype_ `virtual ~FDataflowAddVectorSampler() override = default;`
- L27 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L28 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L32 _public member_ `TArray<TSharedPtr<const FDataflowVectorSamplerBase>> Samplers;` — list of samplers to add results from

#### struct `FDataflowAddSamplerNode`  
`struct FDataflowAddSamplerNode : public FDataflowMultiInputSamplerNodeBase`  
_L39-48_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowMultiInputSamplerNodeBase`
- desc: add sampler results together
- L46 _public prototype_ `FDataflowAddSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L47 _public prototype_ `virtual void EvaluateSampler(UE::Dataflow::FContext& Context, FDataflowSamplerTypes::FStorageType& OutSampler) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowClampSamplerNode.h` (Private)


#### struct `FDataflowClampFloatSampler`  
`struct FDataflowClampFloatSampler : public FDataflowFloatSamplerBase`  
_L11-30_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowClampFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = Clamp, meta = (DataflowInput))`
- L26 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = Clamp, meta = (DataflowInput))`
- L29 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowClampFloatSamplerNode`  
`struct FDataflowClampFloatSamplerNode : public FDataflowNode`  
_L36-52_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output an Clamp float sampler
- L42 _public prototype_ `FDataflowClampFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L46 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L49 _private member_ `FDataflowClampFloatSampler ClampSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L51 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowColorRampSamplerNode.h` (Private)


#### struct `FDataflowColorRampVectorSampler`  
`struct FDataflowColorRampVectorSampler : public FDataflowVectorSamplerBase`  
_L13-35_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L17 _public prototype_ `virtual ~FDataflowColorRampVectorSampler() override = default;`
- L18 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L19 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L24 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Attribute minimum value for coloring. This value represents the minimum color on the color ramp.
- L28 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Attribute maximum value for coloring. This value represents the maximum color on the color ramp.
- L32 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Color ramp specifiyng the color for displayed points using a single value attribute. Only used with FloatSampler input.
- L34 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowColorRampSamplerNode`  
`struct FDataflowColorRampSamplerNode : public FDataflowNode`  
_L45-67_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: ColorRamp Sampler Input(s) : Float Sampler Output(s): Vector sampler representing colors generated by the color ramp using the sampled float values
- L51 _public prototype_ `FDataflowColorRampSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L56 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput))` — Sampler input
- L60 _private member_ `FDataflowVectorSampler ColorSampler;` — `UPROPERTY(meta = (DataflowOutput))` — Sampler output
- L63 _private member_ `FDataflowColorRampVectorSampler ColorRampSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L66 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowCombineSamplerNode.h` (Private)


#### struct `FDataflowCombineVectorSampler`  
`struct FDataflowCombineVectorSampler : public FDataflowVectorSamplerBase`  
_L11-25_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowCombineVectorSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L20 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSamplerX;`
- L22 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSamplerY;`
- L24 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSamplerZ;`

#### struct `FDataflowCombineFloatSamplerNode`  
`struct FDataflowCombineFloatSamplerNode : public FDataflowNode`  
_L35-57_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Combine float sampler Input(s):  3 float samplers (X, Y, Z) to combine into a single vector sampler Output(s): vector sampler
- L41 _public prototype_ `FDataflowCombineFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L45 _private member_ `FDataflowFloatSampler FloatSamplerX;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L48 _private member_ `FDataflowFloatSampler FloatSamplerY;` — `UPROPERTY(meta = (DataflowInput))`
- L51 _private member_ `FDataflowFloatSampler FloatSamplerZ;` — `UPROPERTY(meta = (DataflowInput))`
- L54 _private member_ `FDataflowVectorSampler VectorSampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L56 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowDistanceFromBoxSamplerNode.h` (Private)


#### struct `FDataflowDistanceFromBoxFloatSampler`  
`struct FDataflowDistanceFromBoxFloatSampler : public FDataflowFloatSamplerBase`  
_L11-23_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowDistanceFromBoxFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `FBox Box;` — `UPROPERTY(meta = (DataflowInput))` — Box to compute the distance from

#### struct `FDataflowDistanceFromBoxFloatSamplerNode`  
`struct FDataflowDistanceFromBoxFloatSamplerNode : public FDataflowNode`  
_L33-49_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Distance from a box float sampler Input(s) : an AABB Output(s): for every sampled point the distance from the input box
- L39 _public prototype_ `FDataflowDistanceFromBoxFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L43 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L46 _private member_ `FDataflowDistanceFromBoxFloatSampler DistanceFromBoxSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L48 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowDistanceFromPlaneSamplerNode.h` (Private)


#### struct `FDataflowDistanceFromPlaneFloatSampler`  
`struct FDataflowDistanceFromPlaneFloatSampler : public FDataflowFloatSamplerBase`  
_L12-24_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L16 _public prototype_ `virtual ~FDataflowDistanceFromPlaneFloatSampler() override = default;`
- L17 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L18 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L23 _public member_ `FDataflowPlane Plane;` — `UPROPERTY(meta = (DataflowInput))` — Plane to compute the distance from

#### struct `FDataflowDistanceFromPlaneFloatSamplerNode`  
`struct FDataflowDistanceFromPlaneFloatSamplerNode : public FDataflowNode`  
_L34-50_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Distance from a plane float sampler Input(s) : a plane Output(s): for every sampled point the distance from the input plane
- L40 _public prototype_ `FDataflowDistanceFromPlaneFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L44 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L47 _private member_ `FDataflowDistanceFromPlaneFloatSampler DistanceFromPlaneSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L49 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowDistanceFromSphereSamplerNode.h` (Private)


#### struct `FDataflowDistanceFromSphereFloatSampler`  
`struct FDataflowDistanceFromSphereFloatSampler : public FDataflowFloatSamplerBase`  
_L11-23_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowDistanceFromSphereFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `FSphere Sphere = FSphere(0.0);` — `UPROPERTY(meta = (DataflowInput))` — Sphere to compute the distance from

#### struct `FDataflowDistanceFromSphereFloatSamplerNode`  
`struct FDataflowDistanceFromSphereFloatSamplerNode : public FDataflowNode`  
_L33-49_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Distance from a sphere float sampler Input(s) : a sphere Output(s): for every sampled point the distance from the input sphere
- L39 _public prototype_ `FDataflowDistanceFromSphereFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L43 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L46 _private member_ `FDataflowDistanceFromSphereFloatSampler DistanceFromSphereSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L48 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowElectricFieldVectorSamplerNode.h` (Private)


#### struct `FDataflowCharge`  
`struct FDataflowCharge`  
_L16-47_
- reflection: `USTRUCT()`
- desc: Represents a charge for an electric field
- L20 _public function_ `FDataflowCharge() : Position(FVector::ZeroVector), Charge(0.0)`
- L26 _public function_ `FDataflowCharge(const FVector& InPosition, const double InCharge) : Position(InPosition), Charge(InCharge)`
- L32 _public function_ `FDataflowCharge(const FDataflowCharge& InCharge)`
- L38 _public function_ `FVector GetPosition() const`
- L39 _public function_ `double GetCharge() const`
- L43 _private member_ `FVector Position;` — `UPROPERTY(EditAnywhere, Category = "Charge")`
- L46 _private member_ `double Charge;` — `UPROPERTY(EditAnywhere, Category = "Charge")`

#### struct `FDataflowElectricFieldVectorSampler`  
`struct FDataflowElectricFieldVectorSampler : public FDataflowVectorSamplerBase`  
_L50-76_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L54 _public prototype_ `virtual ~FDataflowElectricFieldVectorSampler() override = default;`
- L55 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L56 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L60 _public member_ `TArray<FDataflowCharge> Charges;` — `UPROPERTY(EditAnywhere, Category = "Charges")`
- L63 _public member_ `double Scalar = 1e-3;` — `UPROPERTY(EditAnywhere, Category = "Charges")`
- L66 _public member_ `bool bClamp = false;` — `UPROPERTY(EditAnywhere, Category = "Charges")`
- L69 _public member_ `double MaxMagnitude = 10.0;` — `UPROPERTY(EditAnywhere, Category = "Charges")`
- L72 _public member_ `FDataflowPoints ChargesFromSampler;` — `UPROPERTY()`
- L75 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowElectricFieldVectorSamplerNode`  
`struct FDataflowElectricFieldVectorSamplerNode : public FDataflowNode`  
_L82-101_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a ElectricField vector sampler
- L88 _public prototype_ `FDataflowElectricFieldVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L92 _private member_ `FDataflowPoints Charges;` — `UPROPERTY(meta = (DataflowInput))`
- L95 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L98 _private member_ `FDataflowElectricFieldVectorSampler ElectricFieldSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L100 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowGradientSamplerNode.h` (Private)


#### struct `FDataflowLinearGradientFloatSampler`  
`struct FDataflowLinearGradientFloatSampler : public FDataflowFloatSamplerBase`  
_L14-42_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowFloatSamplerBase`
- L18 _public prototype_ `virtual ~FDataflowLinearGradientFloatSampler() override = default;`
- L19 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L20 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L25 _public member_ `FVector3f StartPoint = { 0, 0, 100 };` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput, GizmoType = "Translate"))` — Point in space where the start value is defined
- L29 _public member_ `float StartValue = 1.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — Value defined at start point
- L33 _public member_ `FVector3f EndPoint = { 0, 0, 0 };` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput, GizmoType = "Translate"))` — Point in space where end value is defined
- L37 _public member_ `float EndValue = 0.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — Value defined at end point
- L41 _public member_ `bool bClamp = true;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — If true generated value will be clamped beyond end and start point, otherwise, they will be extrapolated

#### struct `FDataflowLinearGradientFloatSamplerNode`  
`struct FDataflowLinearGradientFloatSamplerNode : public FDataflowNode`  
_L48-64_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a linear gradient sampler
- L54 _public prototype_ `FDataflowLinearGradientFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L58 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L61 _private member_ `FDataflowLinearGradientFloatSampler Gradient;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L63 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowLinearGradientFromBoxFloatSampler`  
`struct FDataflowLinearGradientFromBoxFloatSampler : public FDataflowFloatSamplerBase`  
_L69-100_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowFloatSamplerBase`
- L73 _public prototype_ `virtual ~FDataflowLinearGradientFromBoxFloatSampler() override = default;`
- L74 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L75 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L80 _public member_ `FBox Box;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — Box to use for the gradient - one axis is chosen to be the axis of the gradient
- L84 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — Transform to apply to the box
- L88 _public member_ `TEnumAsByte<EAxis::Type> Axis = EAxis::Z;` — `UPROPERTY(EditAnywhere, Category = Gradient)` — Axis of the box to use for the gradient
- L92 _public member_ `bool bClamp = true;` — `UPROPERTY(EditAnywhere, Category = Gradient)` — If true generated value will be clamped beyond end and start point, otherwise, they will be extrapolated
- L96 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = Gradient)` — Ramp representing the values for the gradient, since the values are float, it will read the R channel of the colors
- L99 _private prototype_ `void ComputePoints(FVector& StartPoint, FVector& EndPoint) const;`

#### struct `FDataflowLinearGradientFromBoxFloatSamplerNode`  
`struct FDataflowLinearGradientFromBoxFloatSamplerNode : public FDataflowNode`  
_L106-122_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a linear gradient sampler
- L112 _public prototype_ `FDataflowLinearGradientFromBoxFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L116 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L119 _private member_ `FDataflowLinearGradientFromBoxFloatSampler Gradient;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L121 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowRadialGradientFloatSampler`  
`struct FDataflowRadialGradientFloatSampler : public FDataflowFloatSamplerBase`  
_L127-155_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowFloatSamplerBase`
- L131 _public prototype_ `virtual ~FDataflowRadialGradientFloatSampler() override = default;`
- L132 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L133 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L138 _public member_ `FVector3f Center = { 0, 0, 0 };` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — center defining the radial gradient
- L142 _public member_ `float Radius = 100.f;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput, UIMin = 0.01, ClampMin = 0.01))` — Radius of the gradient
- L146 _public member_ `float CenterValue = 1.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — Value defined at center
- L150 _public member_ `float EdgeValue = 0.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — Value defined at the radius distance from the center
- L154 _public member_ `bool bClamp = true;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (DataflowInput))` — If true generated values will be clamped beyond the radius otherwise they will they will be extrapolated

#### struct `FDataflowRadialGradientFloatSamplerNode`  
`struct FDataflowRadialGradientFloatSamplerNode : public FDataflowNode`  
_L161-177_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a radial gradient sampler
- L167 _public prototype_ `FDataflowRadialGradientFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L171 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L174 _private member_ `FDataflowRadialGradientFloatSampler Gradient;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L176 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L181 _namespace_ `namespace UE`
- L181 _namespace_ `namespace Dataflow` (scope `UE`)
- L183 _prototype_ `void RegisterGradientSamplerNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowLerpSamplerNode.h` (Private)


#### struct `FDataflowLerpFloatSampler`  
`struct FDataflowLerpFloatSampler : public FDataflowFloatSamplerBase`  
_L11-28_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowLerpFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `float Blend = 0.f;` — `UPROPERTY()`
- L23 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSamplerA;`
- L25 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSamplerB;`
- L27 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> BlendSampler;`

#### struct `FDataflowLerpVectorSampler`  
`struct FDataflowLerpVectorSampler : public FDataflowVectorSamplerBase`  
_L31-48_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L35 _public prototype_ `virtual ~FDataflowLerpVectorSampler() override = default;`
- L36 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L37 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L41 _public member_ `float Blend = 0.f;` — `UPROPERTY()`
- L43 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSamplerA;`
- L45 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSamplerB;`
- L47 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> BlendSampler;`

#### struct `FDataflowLerpSamplerNode`  
`struct FDataflowLerpSamplerNode : public FDataflowNode`  
_L58-84_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: LerpSampler Input(s) : 2 Float or Vector Sampler, optional BlendSampler (if not connected blend value can be used) Output(s): Same type of sampler as the input ooutputting the lerped value
- L64 _public prototype_ `FDataflowLerpSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L69 _private member_ `FDataflowSamplerTypes SamplerA;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = SamplerA))` — First input for lerp
- L73 _private member_ `FDataflowSamplerTypes SamplerB;` — `UPROPERTY(meta = (DataflowInput))` — Second input for lerp
- L77 _private member_ `FDataflowFloatSampler BlendSampler;` — `UPROPERTY(meta = (DataflowInput))` — Optional FloatSampler to control lerp per sampled points
- L81 _private member_ `float Blend = 0.f;` — `UPROPERTY(EditAnywhere, Category = Lerp, meta = (DataflowInput, UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))` — If BlendSampler is not connected this value controls the lerp
- L83 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowMaxSamplerNode.h` (Private)


#### struct `FDataflowMaxFloatSampler`  
`struct FDataflowMaxFloatSampler : public FDataflowFloatSamplerBase`  
_L11-21_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L14 _public prototype_ `virtual ~FDataflowMaxFloatSampler() override = default;`
- L15 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L16 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L20 _public member_ `TArray<TSharedPtr<const FDataflowFloatSamplerBase>> Samplers;` — list of samplers to Max results from

#### struct `FDataflowMaxVectorSampler`  
`struct FDataflowMaxVectorSampler : public FDataflowVectorSamplerBase`  
_L24-34_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L27 _public prototype_ `virtual ~FDataflowMaxVectorSampler() override = default;`
- L28 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L29 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L33 _public member_ `TArray<TSharedPtr<const FDataflowVectorSamplerBase>> Samplers;` — list of samplers to Max results from

#### struct `FDataflowMaxSamplerNode`  
`struct FDataflowMaxSamplerNode : public FDataflowMultiInputSamplerNodeBase`  
_L40-49_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowMultiInputSamplerNodeBase`
- desc: Max sampler results together
- L47 _public prototype_ `FDataflowMaxSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L48 _public prototype_ `virtual void EvaluateSampler(UE::Dataflow::FContext& Context, FDataflowSamplerTypes::FStorageType& OutSampler) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowMeshSamplerNode.h` (Private)


#### enum `EDataflowMeshFloatSamplerOutputType`  
`enum class EDataflowMeshFloatSamplerOutputType : uint8`  
_L12-16_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `ClosestPointDistance UMETA(DisplayName = "Closest Point Distance")`
- L15 _public enumerator_ `ClosestTriangleID UMETA(DisplayName = "Closest Triangle ID")`

#### struct `FDataflowMeshFloatSampler`  
`struct FDataflowMeshFloatSampler : public FDataflowFloatSamplerBase`  
_L19-34_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L23 _public prototype_ `virtual ~FDataflowMeshFloatSampler() override = default;`
- L24 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L25 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L30 _public member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput))` — Mesh to sample data from
- L33 _public member_ `EDataflowMeshFloatSamplerOutputType OutputType = EDataflowMeshFloatSamplerOutputType::ClosestPointDistance;` — `UPROPERTY(EditAnywhere, Category = Sampler, DisplayName = "Sampled Value")`

#### struct `FDataflowMeshFloatSamplerNode`  
`struct FDataflowMeshFloatSamplerNode : public FDataflowNode`  
_L44-60_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Mesh float sampler Input: a DataflowMesh Output: for every sampled point certain data from the mesh (ClosestPointDistance, ClosestTriangleID)
- L50 _public prototype_ `FDataflowMeshFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L54 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L57 _private member_ `FDataflowMeshFloatSampler MeshSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L59 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowMeshVectorSamplerOutputType`  
`enum class EDataflowMeshVectorSamplerOutputType : uint8`  
_L65-71_
- reflection: `UENUM(BlueprintType)`
- L67 _public enumerator_ `VectorToClosestPoint UMETA(DisplayName = "Vector To Closest Point")`
- L68 _public enumerator_ `ClosestPoint UMETA(DisplayName = "Closest Point")`
- L69 _public enumerator_ `ClosestTriangleNormal UMETA(DisplayName = "Closest Triangle Normal")`
- L70 _public enumerator_ `UV UMETA(DisplayName = "UV")`

#### struct `FDataflowMeshVectorSampler`  
`struct FDataflowMeshVectorSampler : public FDataflowVectorSamplerBase`  
_L74-93_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L78 _public prototype_ `virtual ~FDataflowMeshVectorSampler() override = default;`
- L79 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L80 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L85 _public member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput))` — Mesh to sample data from
- L88 _public member_ `EDataflowMeshVectorSamplerOutputType OutputType = EDataflowMeshVectorSamplerOutputType::VectorToClosestPoint;` — `UPROPERTY(EditAnywhere, Category = Sampler, DisplayName = "Sampled Value")`
- L92 _public member_ `int32 UVLayer = 0;` — `UPROPERTY(meta = (UIMin = 0, ClampMin = 0, EditCondition = "OutputType == EDataflowMeshVectorSamplerOutputType::UV"))` — UV layer

#### struct `FDataflowMeshVectorSamplerNode`  
`struct FDataflowMeshVectorSamplerNode : public FDataflowNode`  
_L104-120_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Mesh vector sampler Input: a DataflowMesh Output: for every sampled point certain data from the mesh (VectorToClosestPoint, ClosestTriangleNormal ClosestPoint, ClosestPointUV etc)
- L110 _public prototype_ `FDataflowMeshVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L114 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L117 _private member_ `FDataflowMeshVectorSampler MeshSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L119 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowMinSamplerNode.h` (Private)


#### struct `FDataflowMinFloatSampler`  
`struct FDataflowMinFloatSampler : public FDataflowFloatSamplerBase`  
_L11-21_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L14 _public prototype_ `virtual ~FDataflowMinFloatSampler() override = default;`
- L15 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L16 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L20 _public member_ `TArray<TSharedPtr<const FDataflowFloatSamplerBase>> Samplers;` — list of samplers to Min results from

#### struct `FDataflowMinVectorSampler`  
`struct FDataflowMinVectorSampler : public FDataflowVectorSamplerBase`  
_L24-34_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L27 _public prototype_ `virtual ~FDataflowMinVectorSampler() override = default;`
- L28 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L29 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L33 _public member_ `TArray<TSharedPtr<const FDataflowVectorSamplerBase>> Samplers;` — list of samplers to Min results from

#### struct `FDataflowMinSamplerNode`  
`struct FDataflowMinSamplerNode : public FDataflowMultiInputSamplerNodeBase`  
_L40-49_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowMultiInputSamplerNodeBase`
- desc: Min sampler results together
- L47 _public prototype_ `FDataflowMinSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L48 _public prototype_ `virtual void EvaluateSampler(UE::Dataflow::FContext& Context, FDataflowSamplerTypes::FStorageType& OutSampler) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowModuloSamplerNode.h` (Private)


#### struct `FDataflowModuloFloatSampler`  
`struct FDataflowModuloFloatSampler : public FDataflowFloatSamplerBase`  
_L11-29_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowModuloFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `float Base = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Modulo", meta = (DataflowInput))` — Base for modulo. Base can't be zero
- L26 _public member_ `float Offset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Modulo", meta = (DataflowInput))` — Offset for modulo
- L28 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSampler;`

#### struct `FDataflowModuloFloatSamplerNode`  
`struct FDataflowModuloFloatSamplerNode : public FDataflowNode`  
_L39-55_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: ModuloSampler Input(s) : Float Sampler Output(s): Modulo applied on sampled values
- L45 _public prototype_ `FDataflowModuloFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L49 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L52 _private member_ `FDataflowModuloFloatSampler ModuloSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L54 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowModuloVectorSampler`  
`struct FDataflowModuloVectorSampler : public FDataflowVectorSamplerBase`  
_L58-76_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L62 _public prototype_ `virtual ~FDataflowModuloVectorSampler() override = default;`
- L63 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L64 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L69 _public member_ `FVector Base = FVector(2.0);` — `UPROPERTY(EditAnywhere, Category = "Modulo", meta = (DataflowInput))` — Base for component wise modulo, none of the components of Base can be zero
- L73 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Modulo", meta = (DataflowInput))` — Offset for the modulo
- L75 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSampler;`

#### struct `FDataflowModuloVectorSamplerNode`  
`struct FDataflowModuloVectorSamplerNode : public FDataflowNode`  
_L86-102_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: ModuloSampler Input(s) : Vector Sampler Output(s): Vector modulo applied on components
- L92 _public prototype_ `FDataflowModuloVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L96 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L99 _private member_ `FDataflowModuloVectorSampler ModuloSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L101 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowMultiplySamplerNode.h` (Private)


#### struct `FDataflowMultiplyFloatSampler`  
`struct FDataflowMultiplyFloatSampler : public FDataflowFloatSamplerBase`  
_L10-20_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L13 _public prototype_ `virtual ~FDataflowMultiplyFloatSampler() override = default;`
- L14 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L15 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L19 _public member_ `TArray<TSharedPtr<const FDataflowFloatSamplerBase>> Samplers;` — list of samplers to add results from

#### struct `FDataflowMultiplyVectorSampler`  
`struct FDataflowMultiplyVectorSampler : public FDataflowVectorSamplerBase`  
_L23-33_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L26 _public prototype_ `virtual ~FDataflowMultiplyVectorSampler() override = default;`
- L27 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L28 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L32 _public member_ `TArray<TSharedPtr<const FDataflowVectorSamplerBase>> Samplers;` — list of samplers to add results from

#### struct `FDataflowMultiplySamplerNode`  
`struct FDataflowMultiplySamplerNode : public FDataflowMultiInputSamplerNodeBase`  
_L39-48_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowMultiInputSamplerNodeBase`
- desc: Multiply sampler results together
- L46 _public prototype_ `FDataflowMultiplySamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L47 _public prototype_ `virtual void EvaluateSampler(UE::Dataflow::FContext& Context, FDataflowSamplerTypes::FStorageType& OutSampler) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowNegateSamplerNode.h` (Private)


#### struct `FDataflowNegateFloatSampler`  
`struct FDataflowNegateFloatSampler : public FDataflowFloatSamplerBase`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowNegateFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowNegateVectorSampler`  
`struct FDataflowNegateVectorSampler : public FDataflowVectorSamplerBase`  
_L25-36_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L29 _public prototype_ `virtual ~FDataflowNegateVectorSampler() override = default;`
- L30 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L31 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L35 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> Sampler;`

#### struct `FDataflowNegateSamplerNode`  
`struct FDataflowNegateSamplerNode : public FDataflowNode`  
_L42-55_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output an Negate float sampler
- L48 _public prototype_ `FDataflowNegateSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L52 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L54 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowNormalizeSamplerNode.h` (Private)


#### struct `FDataflowNormalizeFloatSampler`  
`struct FDataflowNormalizeFloatSampler : public FDataflowFloatSamplerBase`  
_L11-30_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowNormalizeFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = Normalize, meta = (DataflowInput))`
- L26 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = Normalize, meta = (DataflowInput))`
- L29 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowNormalizeVectorSampler`  
`struct FDataflowNormalizeVectorSampler : public FDataflowVectorSamplerBase`  
_L33-44_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L37 _public prototype_ `virtual ~FDataflowNormalizeVectorSampler() override = default;`
- L38 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L39 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L43 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> Sampler;`

#### struct `FDataflowNormalizeSamplerNode`  
`struct FDataflowNormalizeSamplerNode : public FDataflowNode`  
_L50-63_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a normalize vector sampler
- L56 _public prototype_ `FDataflowNormalizeSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L60 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L62 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowOneMinusSamplerNode.h` (Private)


#### struct `FDataflowOneMinusFloatSampler`  
`struct FDataflowOneMinusFloatSampler : public FDataflowFloatSamplerBase`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowOneMinusFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowOneMinusFloatSamplerNode`  
`struct FDataflowOneMinusFloatSamplerNode : public FDataflowNode`  
_L28-44_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output an OneMinus float sampler
- L34 _public prototype_ `FDataflowOneMinusFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L38 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L41 _private member_ `FDataflowOneMinusFloatSampler OneMinusSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L43 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowPerlinNoiseSamplerNode.h` (Private)


#### struct `FDataflowPerlinNoiseFloatSampler`  
`struct FDataflowPerlinNoiseFloatSampler : public FDataflowFloatSamplerBase`  
_L11-33_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowPerlinNoiseFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L25 _public member_ `float Frequency = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L29 _public member_ `FVector Offset = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L32 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowPerlinNoiseFloatSamplerNode`  
`struct FDataflowPerlinNoiseFloatSamplerNode : public FDataflowNode`  
_L39-55_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a Perlin Noise float sampler
- L45 _public prototype_ `FDataflowPerlinNoiseFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L49 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L52 _private member_ `FDataflowPerlinNoiseFloatSampler PerlinNoiseSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L54 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowPerlinNoiseVectorSampler`  
`struct FDataflowPerlinNoiseVectorSampler : public FDataflowVectorSamplerBase`  
_L58-80_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L62 _public prototype_ `virtual ~FDataflowPerlinNoiseVectorSampler() override = default;`
- L63 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L64 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L68 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L72 _public member_ `float Frequency = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L76 _public member_ `FVector Offset = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L79 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowPerlinNoiseVectorSamplerNode`  
`struct FDataflowPerlinNoiseVectorSamplerNode : public FDataflowNode`  
_L86-102_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a Perlin Noise vector sampler
- L92 _public prototype_ `FDataflowPerlinNoiseVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L96 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L99 _private member_ `FDataflowPerlinNoiseVectorSampler PerlinNoiseSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L101 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowRandomSamplerNode.h` (Private)


#### struct `FDataflowRandomFloatSampler`  
`struct FDataflowRandomFloatSampler : public FDataflowFloatSamplerBase`  
_L11-34_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowRandomFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `int32 Seed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Random seed
- L26 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))` — Random Min
- L30 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))` — Random Max
- L33 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowRandomFloatSamplerNode`  
`struct FDataflowRandomFloatSamplerNode : public FDataflowNode`  
_L40-56_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a Random float sampler
- L46 _public prototype_ `FDataflowRandomFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L50 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L53 _private member_ `FDataflowRandomFloatSampler RandomSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L55 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowRandomVectorSampler`  
`struct FDataflowRandomVectorSampler : public FDataflowVectorSamplerBase`  
_L59-82_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L63 _public prototype_ `virtual ~FDataflowRandomVectorSampler() override = default;`
- L64 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L65 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L70 _public member_ `int32 Seed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Random seed
- L74 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))` — Random Min
- L78 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))` — Random Max
- L81 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowRandomVectorSamplerNode`  
`struct FDataflowRandomVectorSamplerNode : public FDataflowNode`  
_L88-104_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a random vector sampler
- L94 _public prototype_ `FDataflowRandomVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L98 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L101 _private member_ `FDataflowRandomVectorSampler RandomSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L103 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowRemapSamplerNode.h` (Private)


#### struct `FDataflowRemapFloatSampler`  
`struct FDataflowRemapFloatSampler : public FDataflowFloatSamplerBase`  
_L12-47_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L16 _public prototype_ `virtual ~FDataflowRemapFloatSampler() override = default;`
- L17 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L18 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L23 _public member_ `float OriginalMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = Remap, meta = (DataflowInput))`
- L27 _public member_ `float OriginalMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = Remap, meta = (DataflowInput))`
- L31 _public member_ `float NewMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = Remap, meta = (DataflowInput))`
- L35 _public member_ `float NewMax = 2.f;` — `UPROPERTY(EditAnywhere, Category = Remap, meta = (DataflowInput))`
- L39 _public member_ `float Power = 1.f;` — `UPROPERTY(EditAnywhere, Category = Remap, meta = (DataflowInput))`
- L43 _public member_ `bool bClamp = false;` — `UPROPERTY(EditAnywhere, Category = Remap)`
- L46 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowRemapFloatSamplerNode`  
`struct FDataflowRemapFloatSamplerNode : public FDataflowNode`  
_L53-69_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output an Remap float sampler
- L59 _public prototype_ `FDataflowRemapFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L63 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L66 _private member_ `FDataflowRemapFloatSampler RemapSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L68 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSLerpSamplerNode.h` (Private)


#### struct `FDataflowSLerpVectorSampler`  
`struct FDataflowSLerpVectorSampler : public FDataflowVectorSamplerBase`  
_L11-28_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowSLerpVectorSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `float Blend = 0.f;` — `UPROPERTY()`
- L23 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSamplerA;`
- L25 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSamplerB;`
- L27 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> BlendSampler;`

#### struct `FDataflowSLerpSamplerNode`  
`struct FDataflowSLerpSamplerNode : public FDataflowNode`  
_L38-64_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: SLerpSampler Input(s) : 2 Vector Samplers, optional BlendSampler (if not connected blend value will be used) Output(s): Vector sampler outputting the spherical linear interpolated value of the incoming vectors
- L44 _public prototype_ `FDataflowSLerpSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L49 _private member_ `FDataflowVectorSampler SamplerA;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = SamplerA))` — First vector input for slerp
- L53 _private member_ `FDataflowVectorSampler SamplerB;` — `UPROPERTY(meta = (DataflowInput))` — Second vector input for slerp
- L57 _private member_ `FDataflowFloatSampler BlendSampler;` — `UPROPERTY(meta = (DataflowInput))` — Optional FloatSampler to control blend per sampled vectors
- L61 _private member_ `float Blend = 0.f;` — `UPROPERTY(EditAnywhere, Category = SLerp, meta = (DataflowInput, UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))` — If BlendSampler is not connected this value controls the blend
- L63 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSamplerFunctions.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Dataflow` (scope `UE`)
- L8 _namespace_ `namespace Sampler` (scope `UE::Dataflow`)
- L10 _prototype_ `float FRandom(const FVector InPosition, float InRandomMin, float InRandomMax, const int32 InSeed);` (scope `UE::Dataflow::Sampler`)
- L12 _prototype_ `FVector VRandom(const FVector InPosition, float InRandomMin, float InRandomMax, const int32 InSeed);` (scope `UE::Dataflow::Sampler`)
- L14 _prototype_ `float SPerlinNoise(const FVector& InPosition);` (scope `UE::Dataflow::Sampler`)
- L16 _prototype_ `FVector VPerlinNoise(const FVector& InPosition);` (scope `UE::Dataflow::Sampler`)
- L18 _prototype_ `float fBm(const FVector InPoisition, const float InAmplitude, const float InFrequency, const FVector& InOffset, const int32 InOctaves, const float InLacunarity, const float InGain);` (scope `UE::Dataflow::Sampler`)
- L20 _prototype_ `FVector VfBm(const FVector InPoisition, const float InAmplitude, const float InFrequency, const FVector& InOffset, const int32 InOctaves, const float InLacunarity, const float InGain);` (scope `UE::Dataflow::Sampler`)
- L22 _prototype_ `float Turbulence(const FVector InPoisition, const float InAmplitude, const float InFrequency, const FVector& InOffset, const int32 InOctaves, const float InLacunarity, const float InGain);` (scope `UE::Dataflow::Sampler`)
- L24 _prototype_ `float Remap(float Value, const float OriginalMin, const float OriginalMax, const float NewMin, const float NewMax, const float Power, const bool bClamp);` (scope `UE::Dataflow::Sampler`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSamplerMultiInput.h` (Private)


#### struct `FDataflowMultiInputSamplerNodeBase`  
`struct FDataflowMultiInputSamplerNodeBase : public FDataflowNode`  
_L14-47_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L19 _public prototype_ `FDataflowMultiInputSamplerNodeBase() = default;`
- L20 _public prototype_ `FDataflowMultiInputSamplerNodeBase(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L23 _protected prototype_ `void RegisterInitialConnections();`
- L24 _protected prototype_ `int32 GetNumSamplerInputs() const;`
- L25 _protected prototype_ `FDataflowSamplerTypes::FStorageType GetSamplerInput(UE::Dataflow::FContext& Context, int32 Index) const;`
- L26 _protected prototype_ `virtual void EvaluateSampler(UE::Dataflow::FContext& Context, FDataflowSamplerTypes::FStorageType& OutSampler) const;`
- L27 _protected prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L31 _private member_ `TArray<FDataflowSamplerTypes> InputSamplers;` — `UPROPERTY()`
- L34 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "InputSamplers[0]"))`
- L36 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L37 _private prototype_ `virtual bool CanAddPin() const override;`
- L38 _private prototype_ `virtual bool CanRemovePin() const override;`
- L39 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L40 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L41 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L42 _private prototype_ `UE::Dataflow::TConnectionReference<FDataflowSamplerTypes> GetConnectionReference(int32 Index) const;`
- L44 _private member_ `static constexpr int32 NumRequiredDataflowInputs = 0;`
- L45 _private member_ `static constexpr int32 NumInitialInputs = 2;`
- L46 _private member_ `static const FName DependencyTypeGroup;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWNODES_API`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSamplerRangeNode.h` (Private)


#### struct `FSamplerRangeDataflowNode`  
`struct FSamplerRangeDataflowNode : public FDataflowNode`  
_L17-47_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: If the input is a FloatSampler, it samples a 3D grid of points into the input samplers RenderBounds, samples the the input sampler using these points and computes the Min/Max values of the sampled values. If the input is a VectorSampler, it samples a 3D grid of points into the input samplers RenderBounds, samples the the input sampler using these points and computes the Min/Max values of the sampled vectors length values.
- L29 _public member_ `float PointSeparation = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Points", meta = (DisplayName = "Point Separation", UIMin = 0.01f, ClampMin = 0.01f))` — PointSeparation used for the 3D grid point generation in the input sampler's RenderBounds
- L33 _public member_ `int32 NumSamplePoints = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of sampled points output
- L37 _public member_ `float MinSampledValue = 0.0;` — `UPROPERTY(meta = (DataflowOutput))` — Minimum value of the sampled points output
- L41 _public member_ `float MaxSampledValue = 0.0;` — `UPROPERTY(meta = (DataflowOutput))` — Maximum value of the sampled points output
- L43 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L46 _public prototype_ `FSamplerRangeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSamplerToImageNode.h` (Private)


#### enum `EDataflowSlicePlaneOrientation`  
`enum class EDataflowSlicePlaneOrientation : uint8`  
_L13-18_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `XYPlane UMETA(DisplayName = "XY Plane")`
- L16 _public enumerator_ `YZPlane UMETA(DisplayName = "YZ Plane")`
- L17 _public enumerator_ `ZXPlane UMETA(DisplayName = "ZX Plane")`

#### struct `FDataflowSamplerToImageNode`  
`struct FDataflowSamplerToImageNode : public FDataflowNode`  
_L28-70_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Sampler to Image Input(s) : Float or Vector Sample Output(s): an image created from the sampled values
- L39 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowInput))` — Sampler input
- L43 _private member_ `FVector Center = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Render Bounds")` — Center of the render bounds
- L47 _private member_ `FVector Extent = FVector(50.0f);` — `UPROPERTY(EditAnywhere, Category = "Render Bounds", meta = (UIMin = 0.01f, ClampMin = 0.01f))` — Extent of the render bounds
- L51 _private member_ `EDataflowSlicePlaneOrientation Plane = EDataflowSlicePlaneOrientation::XYPlane;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings")` — Slice plane orientation
- L55 _private member_ `float Offset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings", meta = (ClampMin = "-1", ClampMax = "1"))` — Relative offset of the slice plane inside the render bounds. The offset is beetween -1 and 1
- L59 _private member_ `bool bNormalize = false;` — `UPROPERTY(EditAnywhere, Category = "Normalize")` — Normalize the incoming vector data, if incoming vector data represents colors this must be turned off
- L63 _private member_ `EDataflowImageResolution Resolution = EDataflowImageResolution::Resolution256;` — `UPROPERTY(EditAnywhere, Category = "Image")` — Output image resolution
- L67 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowOutput))` — Output image
- L69 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowScaleSamplerNode.h` (Private)


#### struct `FDataflowScaleVectorSampler`  
`struct FDataflowScaleVectorSampler : public FDataflowVectorSamplerBase`  
_L11-25_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowScaleVectorSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSampler;`
- L24 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSampler;`

#### struct `FDataflowScaleVectorSamplerNode`  
`struct FDataflowScaleVectorSamplerNode : public FDataflowNode`  
_L31-47_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a scale vector sampler
- L37 _public prototype_ `FDataflowScaleVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L41 _private member_ `FDataflowVectorSampler VectorSampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = VectorSampler))`
- L44 _private member_ `FDataflowFloatSampler FloatSampler;` — `UPROPERTY(meta = (DataflowInput))`
- L46 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSignSamplerNode.h` (Private)


#### struct `FDataflowSignFloatSampler`  
`struct FDataflowSignFloatSampler : public FDataflowFloatSamplerBase`  
_L14-25_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- desc: No Input Sampler nodes
- L18 _public prototype_ `virtual ~FDataflowSignFloatSampler() override = default;`
- L19 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L20 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L24 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowSignVectorSampler`  
`struct FDataflowSignVectorSampler : public FDataflowVectorSamplerBase`  
_L28-39_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L32 _public prototype_ `virtual ~FDataflowSignVectorSampler() override = default;`
- L33 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L34 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L38 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> Sampler;`

#### struct `FDataflowSignSamplerNode`  
`struct FDataflowSignSamplerNode : public FDataflowNode`  
_L45-58_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output an Sign float sampler
- L51 _public prototype_ `FDataflowSignSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L55 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L57 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSmoothStepSamplerNode.h` (Private)


#### struct `FDataflowSmoothStepFloatSampler`  
`struct FDataflowSmoothStepFloatSampler : public FDataflowFloatSamplerBase`  
_L11-39_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowSmoothStepFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L24 _public member_ `float MinValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — MinValue for SmoothStep
- L28 _public member_ `float MaxValue = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — MaxValue for SmoothStep
- L32 _public member_ `float ValueA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value at MinValue
- L36 _public member_ `float ValueB = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value at MaxValue
- L38 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSampler;`

#### struct `FDataflowSmoothStepFloatSamplerNode`  
`struct FDataflowSmoothStepFloatSamplerNode : public FDataflowNode`  
_L49-65_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: SmoothStepSampler Input(s) : Float Sampler Output(s): Returns a smooth Hermite interpolation between ValueA and ValueB for the sampled value (where X ranges between MinValue and MaxValue)
- L55 _public prototype_ `FDataflowSmoothStepFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L59 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L62 _private member_ `FDataflowSmoothStepFloatSampler SmoothStepSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L64 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowSmoothStepVectorSampler`  
`struct FDataflowSmoothStepVectorSampler : public FDataflowVectorSamplerBase`  
_L68-94_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L72 _public prototype_ `virtual ~FDataflowSmoothStepVectorSampler() override = default;`
- L73 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L74 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L79 _public member_ `FVector MinValue = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — MinValue for SmoothStep
- L83 _public member_ `FVector MaxValue = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — MaxValue for SmoothStep
- L87 _public member_ `FVector ValueA = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value at MinValue
- L91 _public member_ `FVector ValueB = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value at MaxValue
- L93 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSampler;`

#### struct `FDataflowSmoothStepVectorSamplerNode`  
`struct FDataflowSmoothStepVectorSamplerNode : public FDataflowNode`  
_L104-120_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: SmoothStepSampler Input(s) : Vector Sampler Output(s): Returns a component wise smooth Hermite interpolation between ValueA and ValueB for the sampled value (where X ranges between MinValue and MaxValue)
- L110 _public prototype_ `FDataflowSmoothStepVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L114 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L117 _private member_ `FDataflowSmoothStepVectorSampler SmoothStepSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L119 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowSplitSamplerNode.h` (Private)


#### struct `FDataflowVectorToFloatSampler`  
`struct FDataflowVectorToFloatSampler : public FDataflowFloatSamplerBase`  
_L11-25_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowVectorToFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSampler;`
- L24 _public member_ `int32 ElementIndex = 0;` — `UPROPERTY()`

#### struct `FDataflowSplitVectorSamplerNode`  
`struct FDataflowSplitVectorSamplerNode : public FDataflowNode`  
_L35-57_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Split vector sampler Input(s): a vector sampler to split it into X, Y, Z float samplers Output(s): 3 float samplers (X, Y, Z)
- L41 _public prototype_ `FDataflowSplitVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L45 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L48 _private member_ `FDataflowFloatSampler SamplerX;` — `UPROPERTY(meta = (DataflowOutput))`
- L51 _private member_ `FDataflowFloatSampler SamplerY;` — `UPROPERTY(meta = (DataflowOutput))`
- L54 _private member_ `FDataflowFloatSampler SamplerZ;` — `UPROPERTY(meta = (DataflowOutput))`
- L56 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowStepSamplerNode.h` (Private)


#### struct `FDataflowStepFloatSampler`  
`struct FDataflowStepFloatSampler : public FDataflowFloatSamplerBase`  
_L11-33_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowStepFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `float Step = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Step value, x < Step -> ValueA, x >= Step -> ValueB
- L26 _public member_ `float ValueA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value when x < Step
- L30 _public member_ `float ValueB = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value when x >= Step
- L32 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> FloatSampler;`

#### struct `FDataflowStepFloatSamplerNode`  
`struct FDataflowStepFloatSamplerNode : public FDataflowNode`  
_L43-59_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: StepSampler Input(s) : Float Sampler Output(s): Step applied on sampled values
- L49 _public prototype_ `FDataflowStepFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L53 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L56 _private member_ `FDataflowStepFloatSampler StepSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L58 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowStepVectorSampler`  
`struct FDataflowStepVectorSampler : public FDataflowVectorSamplerBase`  
_L62-84_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L66 _public prototype_ `virtual ~FDataflowStepVectorSampler() override = default;`
- L67 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L68 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L73 _public member_ `FVector Step = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Step value, x < Step -> ValueA, x >= Step -> ValueB
- L77 _public member_ `FVector ValueA = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value when x < Step
- L81 _public member_ `FVector ValueB = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Step", meta = (DataflowInput))` — Return value when x >= Step
- L83 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSampler;`

#### struct `FDataflowStepVectorSamplerNode`  
`struct FDataflowStepVectorSamplerNode : public FDataflowNode`  
_L93-109_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: StepSampler Input(s) : Vector Sampler Output(s): Returns a component wise step on the sampled values
- L99 _public prototype_ `FDataflowStepVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L103 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L106 _private member_ `FDataflowStepVectorSampler StepSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L108 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowTextureSamplerNode.h` (Private)


#### struct `FDataflowTextureVectorSampler`  
`struct FDataflowTextureVectorSampler : public FDataflowVectorSamplerBase`  
_L13-28_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L17 _public prototype_ `virtual ~FDataflowTextureVectorSampler() override = default;`
- L18 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L19 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L24 _public member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY(meta = (DataflowInput))` — Texture to sample data from
- L27 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> Sampler;` — This must be a vector sampler with UV values

#### struct `FDataflowTextureVectorSamplerNode`  
`struct FDataflowTextureVectorSamplerNode : public FDataflowNode`  
_L39-55_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Texture vector sampler Inputs: - a vector sampler to get the UVs from - a 2D texture Output: for every sampled point color from the texture
- L45 _public prototype_ `FDataflowTextureVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L49 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L52 _private member_ `FDataflowTextureVectorSampler TextureSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L54 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowTilingSamplerNode.h` (Private)


#### struct `FDataflowTilingFloatSampler`  
`struct FDataflowTilingFloatSampler : public FDataflowFloatSamplerBase`  
_L11-27_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowTilingFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `FVector Offset = FVector(0.0);` — `UPROPERTY()`
- L24 _public member_ `FVector TileSize = FVector(1.0);` — `UPROPERTY()`
- L26 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;`

#### struct `FDataflowTilingVectorSampler`  
`struct FDataflowTilingVectorSampler : public FDataflowVectorSamplerBase`  
_L30-46_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L34 _public prototype_ `virtual ~FDataflowTilingVectorSampler() override = default;`
- L35 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L36 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L40 _public member_ `FVector Offset = FVector(0.0);` — `UPROPERTY()`
- L43 _public member_ `FVector TileSize = FVector(1.0);` — `UPROPERTY()`
- L45 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> Sampler;`

#### struct `FDataflowTilingSamplerNode`  
`struct FDataflowTilingSamplerNode : public FDataflowNode`  
_L56-78_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: TilingSampler Input(s) : Float or Vector Sampler Output(s): Same type of sampler as the input outputting the tiled values
- L62 _public prototype_ `FDataflowTilingSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L67 _private member_ `FDataflowSamplerTypes Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))` — Input for Tiling
- L71 _private member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Tiling, meta = (DataflowInput))` — Tile offset (min point of the tile)
- L75 _private member_ `FVector TileSize = FVector(50.0);` — `UPROPERTY(EditAnywhere, Category = Tiling, meta = (DataflowInput))` — Tile size
- L77 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowTransformSamplerNode.h` (Private)


#### struct `FDataflowTransformFloatSampler`  
`struct FDataflowTransformFloatSampler : public FDataflowFloatSamplerBase`  
_L11-30_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowTransformFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = Transform, meta = (DataflowInput))` — Transform to transform the points into a different space
- L26 _public member_ `bool bInverseTransform = false;` — `UPROPERTY(EditAnywhere, Category = Transform)` — Use inverse transform
- L29 _public member_ `TSharedPtr<const FDataflowFloatSamplerBase> Sampler;` — Sampler to send the transformed point to

#### struct `FDataflowTransformFloatSamplerNode`  
`struct FDataflowTransformFloatSamplerNode : public FDataflowNode`  
_L36-52_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a transform sampler
- L42 _public prototype_ `FDataflowTransformFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L46 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Sampler))`
- L49 _private member_ `FDataflowTransformFloatSampler TransformSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L51 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace Dataflow` (scope `UE`)
- L56 _prototype_ `void RegisterTransformSamplerNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowTurbulenceSamplerNode.h` (Private)


#### struct `FDataflowTurbulenceFloatSampler`  
`struct FDataflowTurbulenceFloatSampler : public FDataflowFloatSamplerBase`  
_L11-46_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowTurbulenceFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Amplitude of the noise
- L26 _public member_ `float Frequency = 1.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Frequency of the noise
- L30 _public member_ `FVector Offset = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Offset for the noise
- L34 _public member_ `int32 Octaves = 1;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Number of layers of the summed instances of noise()
- L38 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Controls the uniform irregularity exponent of the series
- L42 _public member_ `float Gain = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Gain
- L45 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowTurbulenceFloatSamplerNode`  
`struct FDataflowTurbulenceFloatSamplerNode : public FDataflowNode`  
_L52-68_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a Turbulence float sampler
- L58 _public prototype_ `FDataflowTurbulenceFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L62 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L65 _private member_ `FDataflowTurbulenceFloatSampler TurbulenceSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L67 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowUniformSamplerNode.h` (Private)


#### struct `FDataflowUniformFloatSampler`  
`struct FDataflowUniformFloatSampler : public FDataflowFloatSamplerBase`  
_L11-26_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowUniformFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `float Value = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Uniform", meta = (DataflowInput))` — Uniform float value to set on all sampled points
- L25 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowUniformFloatSamplerNode`  
`struct FDataflowUniformFloatSamplerNode : public FDataflowNode`  
_L32-48_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a uniform float sampler
- L38 _public prototype_ `FDataflowUniformFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L42 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L45 _private member_ `FDataflowUniformFloatSampler UniformSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L47 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowUniformVectorSampler`  
`struct FDataflowUniformVectorSampler : public FDataflowVectorSamplerBase`  
_L51-66_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L55 _public prototype_ `virtual ~FDataflowUniformVectorSampler() override = default;`
- L56 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L57 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L62 _public member_ `FVector3f Value = FVector3f(0.f);` — `UPROPERTY(EditAnywhere, Category = "Uniform", meta = (DataflowInput))` — Uniform vector value to set on all sampled points
- L65 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowUniformVectorSamplerNode`  
`struct FDataflowUniformVectorSamplerNode : public FDataflowNode`  
_L72-88_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a uniform vector sampler
- L78 _public prototype_ `FDataflowUniformVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L82 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L85 _private member_ `FDataflowUniformVectorSampler UniformSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L87 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowVectorDeviationSamplerNode.h` (Private)


#### struct `FDataflowVectorDeviationFloatSampler`  
`struct FDataflowVectorDeviationFloatSampler : public FDataflowFloatSamplerBase`  
_L11-25_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowVectorDeviationFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `FVector ReferenceVector =FVector::UpVector;` — `UPROPERTY()`
- L24 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSampler;`

#### struct `FDataflowVectorDeviationSamplerNode`  
`struct FDataflowVectorDeviationSamplerNode : public FDataflowNode`  
_L31-51_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- L37 _public prototype_ `FDataflowVectorDeviationSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L41 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L44 _private member_ `FDataflowFloatSampler VectorDeviationSampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L48 _private member_ `FVector ReferenceVector = FVector::UpVector;` — `UPROPERTY(EditAnywhere, Category = Deviation, meta = (DataflowInput))` — If BlendSampler is not connected this value controls the lerp
- L50 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowVectorLengthSamplerNode.h` (Private)


#### struct `FDataflowVectorLengthFloatSampler`  
`struct FDataflowVectorLengthFloatSampler : public FDataflowFloatSamplerBase`  
_L11-22_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowVectorLengthFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L21 _public member_ `TSharedPtr<const FDataflowVectorSamplerBase> VectorSampler;`

#### struct `FDataflowVectorLengthSamplerNode`  
`struct FDataflowVectorLengthSamplerNode : public FDataflowNode`  
_L28-44_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- L34 _public prototype_ `FDataflowVectorLengthSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L38 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L41 _private member_ `FDataflowFloatSampler VectorLengthSampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L43 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Private/Dataflow/SamplerNodes/DataflowfBmSamplerNode.h` (Private)


#### struct `FDataflowfBmFloatSampler`  
`struct FDataflowfBmFloatSampler : public FDataflowFloatSamplerBase`  
_L11-46_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L15 _public prototype_ `virtual ~FDataflowfBmFloatSampler() override = default;`
- L16 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L17 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L22 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L26 _public member_ `float Frequency = 1.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L30 _public member_ `FVector Offset = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L34 _public member_ `int32 Octaves = 1;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Number of layers of the summed instances of noise()
- L38 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Controls the uniform irregularity exponent of the series
- L42 _public member_ `float Gain = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Gain
- L45 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowfBmFloatSamplerNode`  
`struct FDataflowfBmFloatSamplerNode : public FDataflowNode`  
_L52-68_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a fBm Noise float sampler
- L58 _public prototype_ `FDataflowfBmFloatSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L62 _private member_ `FDataflowFloatSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L65 _private member_ `FDataflowfBmFloatSampler fBmSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L67 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowfBmVectorSampler`  
`struct FDataflowfBmVectorSampler : public FDataflowVectorSamplerBase`  
_L71-106_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L75 _public prototype_ `virtual ~FDataflowfBmVectorSampler() override = default;`
- L76 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L77 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L82 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L86 _public member_ `float Frequency = 1.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L90 _public member_ `FVector Offset = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))`
- L94 _public member_ `int32 Octaves = 1;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Number of layers of the summed instances of noise()
- L98 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Controls the uniform irregularity exponent of the series
- L102 _public member_ `float Gain = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "fBm", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Gain
- L105 _public member_ `FBox RenderBounds = FBox(FVector(-50.0), FVector(50.0));` — `UPROPERTY(EditAnywhere, Category = RenderBounds, meta = (DataflowInput))`

#### struct `FDataflowfBmVectorSamplerNode`  
`struct FDataflowfBmVectorSamplerNode : public FDataflowNode`  
_L112-128_
- reflection: `USTRUCT(meta = (Icon = "Icons.EyeDropper"))`
- inherits: `FDataflowNode`
- desc: Output a fBm vector sampler
- L118 _public prototype_ `FDataflowfBmVectorSamplerNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L122 _private member_ `FDataflowVectorSampler Sampler;` — `UPROPERTY(meta = (DataflowOutput))`
- L125 _private member_ `FDataflowfBmVectorSampler fBmSampler;` — `UPROPERTY(EditAnywhere, Category = Sampler, meta = (ShowOnlyInnerProperties, SkipInDisplayNameChain))`
- L127 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/CollectionRenderingPatternUtility.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Geometry` (scope `UE`)
- L7 _namespace_ `namespace GeometryCollection`
- L7 _namespace_ `namespace Facades` (scope `GeometryCollection`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Dataflow` (scope `UE`)
- L13 _namespace_ `namespace Conversion` (scope `UE::Dataflow`)
- L16 _prototype_ `void RenderingFacadeToDynamicMesh(const GeometryCollection::Facades::FRenderingFacade& Facade, int32 InMeshIndex, UE::Geometry::FDynamicMesh3& DynamicMesh, const bool bBuildRemapping = true);` (scope `UE::Dataflow::Conversion`) — Convert a rendering facade to a dynamic mesh. if InMeshIndex==INDEX_NONE then all Geometry is converted.
- L19 _prototype_ `void DynamicMeshToRenderingFacade(const UE::Geometry::FDynamicMesh3& DynamicMesh, GeometryCollection::Facades::FRenderingFacade& Facade);` (scope `UE::Dataflow::Conversion`) — Convert a dynamic mesh to a rendering facade

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowCollectionAddScalarVertexPropertyNode.h` (Public)


#### enum `EDataflowWeightMapOverrideType`  
`enum class EDataflowWeightMapOverrideType : uint8`  
_L18-27_
- reflection: `UENUM()`
- desc: How the map stored on the AddWeightMapNode should be applied to an existing map. If no map exists, it is treated as zero.
- L22 _public enumerator_ `ReplaceAll` — Replace all the values.
- L24 _public enumerator_ `AddDifference` — Add the values difference to the input one.
- L26 _public enumerator_ `ReplaceChanged` — Replace only the values that has changed.

#### struct `FDataflowCollectionAddScalarVertexPropertyNode`  
`struct FDataflowCollectionAddScalarVertexPropertyNode : public FDataflowVertexAttributeEditableNode`  
_L31-108_
- reflection: `USTRUCT(Meta = (DataflowCollection))`
- inherits: `FDataflowVertexAttributeEditableNode`
- desc: Scalar vertex properties.
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParametersImpl() const override;`
- L41 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L45 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Attribute Name"))` — The name to be set as a weight map attribute.
- L48 _public member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(meta = (DisplayName = "Attribute Key", DataflowInput, DataflowOutput, DataflowPassthrough = "AttributeKey"))`
- L53 _public member_ `TArray<float> VertexWeights;` — `UPROPERTY()` — This property should be technically deprecated but we need to keep it because we cannot post serialize fix it as we need a dataflow Context to create a snapshot deprecated methods are still using it and we still use it to load the data when there's no pre-existing snapshot
- L56 _public member_ `FScalarVertexPropertyGroup TargetGroup;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Vertex Group"))`
- L60 _public member_ `EDataflowWeightMapOverrideType OverrideType = EDataflowWeightMapOverrideType::ReplaceAll;` — `UPROPERTY(EditAnywhere, Category = "Weight Map")` — This type will define how the data are applied to the input data
- L62 _public prototype_ `FDataflowCollectionAddScalarVertexPropertyNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L66 _public prototype_ `void ReportVertexWeights(const TArray<float>& SetupWeights, const TArray<float>& FinalWeights, const TArray<int32>& WeightIndices);` — `UE_DEPRECATED(5.8, "ReportVertexWeights is now deprecated, use the FDataflowVertexAttributeEditableNode API instead")` — Report the vertex weights back onto the property ones
- L70 _public prototype_ `void ExtractVertexWeights(const TArray<float>& SetupWeights, TArrayView<float> FinalWeights) const;` — `UE_DEPRECATED(5.8, "ExtractVertexWeights is now deprecated, use the FDataflowVertexAttributeEditableNode API instead")` — Extract the vertex weights back from the property ones
- L74 _public prototype_ `bool FillAttributeWeights(const TSharedPtr<const FManagedArrayCollection> SelectedCollection, const FCollectionAttributeKey& InAttributeKey, TArray<float>& OutAttributeValues) const;` — `UE_DEPRECATED(5.8, "FillAttributeWeights is now deprecated, use the FDataflowVertexAttributeEditableNode API instead")` — Fill the weight attribute values from the collection
- L77 _public prototype_ `FCollectionAttributeKey GetWeightAttributeKey(UE::Dataflow::FContext& Context) const;` — Get the weights attribute key to retrieve/set the weight values
- L82 _private member_ `static constexpr float ReplaceChangedPassthroughValue = UE_BIG_NUMBER;` — Pass through value to skip replacing the weight map value if nothing has changed
- L84 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L85 _private prototype_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const override;`
- L88 _private prototype_ `virtual void GetSupportedViewModes(UE::Dataflow::FContext& Context, TArray<FName>& OutViewModeNames) const override;`
- L89 _private prototype_ `virtual void GetVertexAttributeValues(UE::Dataflow::FContext& Context, TArray<float>& OutValues) const override;`
- L90 _private prototype_ `virtual void SetVertexAttributeValues(UE::Dataflow::FContext& Context, const TArray<float>& InValues, const TArray<int32>& InWeightIndices) override;`
- L91 _private prototype_ `virtual void GetExtraVertexMapping(UE::Dataflow::FContext& Context, FName SelectedViewMode, TArray<int32>& OutMappingToWeight, TArray<TArray<int32>>& OutMappingFromWeight) const override;`
- L94 _private prototype_ `void GetWeightsFromActiveSnapshot(const FManagedArrayCollection& Collection, FName TargetGroupName, TArrayView<float> OutValues) const;`
- L95 _private prototype_ `void GetWeightsFromSnapshot(const FManagedArrayCollection& Collection, const FDataflowToolNodeSnapshot& Snapshot, FName TargetGroupName, TArrayView<float> OutValues) const;`
- L96 _private prototype_ `void StoreWeightsInSnapshot(const FManagedArrayCollection& Collection, TConstArrayView<float> InValues, FName TargetGroupName, FDataflowToolNodeSnapshot& OutSnapshot) const;`
- L99 _private prototype_ `void ComputeFinalWeights(TConstArrayView<float> InputWeights, TConstArrayView<float> StoredWeights, TArrayView<float> FinalWeights) const;` — use the input and stored weights and process final weights based on the selected override type
- L105 _private prototype_ `void ComputeWeightsToStore(TConstArrayView<float> InputWeights, TConstArrayView<float> FinalWeights, TConstArrayView<int32> WeightIndices, TArrayView<float> WeightsToStore);` — Compute weights to store from the final weights, input weights and the selected override type Only processed the indices contained in WeightIndices, if non-empty

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAFLOWNODES_API`

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowCollectionAttributeKeyNodes.h` (Public)


#### struct `FMakeAttributeKeyDataflowNode`  
`struct FMakeAttributeKeyDataflowNode : public FDataflowNode`  
_L15-40_
- reflection: `USTRUCT(meta = (Dataflow))`
- inherits: `FDataflowNode`
- L26 _public member_ `FString AttributeIn = "";` — `UPROPERTY(EditAnywhere, Category = "Collection Key", meta = (DataflowInput, DisplayName = "Attribute"))`
- L29 _public member_ `FCollectionAttributeKey AttributeKeyOut;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "AttributeKey"))`
- L31 _public function_ `FMakeAttributeKeyDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L39 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBreakAttributeKeyDataflowNode`  
`struct FBreakAttributeKeyDataflowNode : public FDataflowNode`  
_L43-70_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L54 _public member_ `FString AttributeOut = "";` — `UPROPERTY(EditAnywhere, Category = "Attribute Key", meta = (DataflowOutput, DisplayName = "Attribute"))`
- L57 _public member_ `FString GroupOut = "";` — `UPROPERTY(EditAnywhere, Category = "Attribute Key", meta = (DataflowOutput, DisplayName = "Group"))`
- L61 _public function_ `FBreakAttributeKeyDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L69 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L72 _namespace_ `namespace UE`
- L72 _namespace_ `namespace Dataflow` (scope `UE`)
- L74 _prototype_ `void DataflowCollectionAttributeKeyNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowCollectionEditSkeletonBonesNode.h` (Public)


#### struct `FDataflowCollectionEditSkeletonBonesNode`  
`struct FDataflowCollectionEditSkeletonBonesNode : public FDataflowPrimitiveNode`  
_L17-73_
- reflection: `USTRUCT(Meta = (Experimental,DataflowCollection))`
- inherits: `FDataflowPrimitiveNode`
- desc: Edit skeleton bones properties.
- L27 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L31 _public member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Vertex Group"))` — Target group in which the attributes are stored
- L35 _public member_ `TObjectPtr<USkeleton> Skeleton = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Skeleton Binding", Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Skeleton"))` — Skeleton to be edited
- L39 _public member_ `TObjectPtr<USkeleton> ToolSkeleton = nullptr;` — `UPROPERTY()` — Skeleton used to store the tool result
- L42 _public function_ `void ValidateSkeletalMeshes()` — Validate the skeletal mesh construction
- L45 _public member_ `FDataflowBoneSelectionChangedNotifyDelegate OnBoneSelectionChanged;` — Delegate to transfer the bone selection to the tool
- L50 _private prototype_ `TObjectPtr<USkeleton> UpdateToolSkeleton(UE::Dataflow::FContext& Context);` — Update the tool skeleton
- L53 _private prototype_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParametersImpl() const override;`
- L54 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L55 _private prototype_ `virtual void AddPrimitiveComponents(UE::Dataflow::FContext& Context, const TSharedPtr<const FManagedArrayCollection> RenderCollection, TObjectPtr<UObject> NodeOwner, TObjectPtr<AActor> RootActor, TArray<TObjectPtr<UPrimitiveComponent>>& PrimitiveComponents) override;`
- L57 _private prototype_ `virtual void OnInvalidate() override;`
- L59 _private function_ `virtual bool CanDebugDraw() const override`
- L60 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L61 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L69 _private member_ `TArray<TObjectPtr<USkeletalMesh>> SkeletalMeshes;` — `UPROPERTY(Transient)` — Transient skeletal mesh built from dataflow render collection
- L72 _private member_ `bool bValidSkeletalMeshes = false;` — Valid skeletal mesh boolean to trigger the construction

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWNODES_API`

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowCollectionEditSkinWeightsNode.h` (Public)


#### struct `FDataflowSkinWeightData`  
`struct FDataflowSkinWeightData`  
_L23-32_
- reflection: `USTRUCT()`
- desc: Dataflow skin weights data
- L28 _public member_ `TArray<float> BoneWeights;` — `UPROPERTY()`
- L31 _public member_ `TArray<int32> BoneIndices;` — `UPROPERTY()`

#### struct `FDataflowVertexSkinWeightData`  
`struct FDataflowVertexSkinWeightData`  
_L41-65_
- reflection: `USTRUCT()`
- desc: FDataflowVertexSkinWeightData is a replacement for FDataflowSkinWeightData in FDataflowCollectionEditSkinWeightsNode This allow storing all the data linearly and enable bulk serialization for speed This solve the problem when we have million vertices meshes that was causing the serialization of the node to take a very long time this is now an order of magnitude faster that using FDataflowSkinWeightData
- L46 _public member_ `static constexpr const int32 MaxNumInflences = MAX_TOTAL_INFLUENCES;`
- L48 _public prototype_ `int32 Num() const;`
- L49 _public prototype_ `void SetNum(int32 VertexNum);`
- L50 _public prototype_ `void Reset();`
- L52 _public prototype_ `void FromArrays(int32 VertexIndex, const TArray<int32>& InIndices, const TArray<float>& InWeights);`
- L53 _public prototype_ `void ToArrays(int32 VertexIndex, TArray<int32>& OutIndices, TArray<float>& OutWeights) const;`
- L55 _public prototype_ `bool Serialize(FArchive& Ar);`
- L60 _private member_ `TArray<int16> Bones;`
- L62 _private member_ `TArray<float> Weights;`
- L64 _private member_ `int32 ArrayNum = 0;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataflowVertexSkinWeightData> : public TStructOpsTypeTraitsBase2<FDataflowVertexSkinWeightData>`  
_L68-75_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowVertexSkinWeightData>`
- L74 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L71-73_

#### struct `FDataflowCollectionEditSkinWeightsNode`  
`struct FDataflowCollectionEditSkinWeightsNode : public FDataflowPrimitiveNode`  
_L79-211_
- reflection: `USTRUCT(Meta = (Experimental,DataflowCollection))`
- inherits: `FDataflowPrimitiveNode`
- desc: Edit skin weights vertex properties.
- L86 _public prototype_ `FDataflowCollectionEditSkinWeightsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L89 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L93 _public member_ `FString BoneIndicesName;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Bone Indices"))` — The name to be set as a weight map attribute.
- L97 _public member_ `FString BoneWeightsName;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Bone Weights"))` — The name to be set as a weight map attribute.
- L101 _public member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Vertex Group"))` — Target group in which the attributes are stored
- L105 _public member_ `FCollectionAttributeKey BoneIndicesKey;` — `UPROPERTY(meta = (DisplayName = "Bone Indices", DataflowInput, DataflowOutput, DataflowPassthrough = "BoneIndicesKey"))` — Bone indices key to be used in other nodes if necessary
- L109 _public member_ `FCollectionAttributeKey BoneWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Bone Weights", DataflowInput, DataflowOutput, DataflowPassthrough = "BoneWeightsKey"))` — Bone weights key to be used in other nodes if necessary
- L113 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Skeleton Binding", meta = (DataflowInput))` — Skeletal mesh to extract the skeleton from for the skinning
- L117 _public member_ `bool bCompressSkinWeights = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton Binding")` — Boolean to use a compressed format (FVector4f, FIntVector) to store the skin weights
- L121 _public member_ `TArray<FDataflowSkinWeightData> SkinWeights_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use VertexSkinWeights instead"))` — List of skin weights
- L124 _public member_ `FDataflowVertexSkinWeightData VertexSkinWeights;` — `UPROPERTY()`
- L131 _public member_ `int32 SkinWeightsRefSkeletonHash = 0;` — `UPROPERTY()` — Hash of the ref skeleton the stored skin weight are based on This allow invalidating the SkinWeights when the ref skeleton does not match anymore instead of having broken weights
- L134 _public member_ `FDataflowBoneSelectionChangedNotifyDelegate OnBoneSelectionChanged;` — Delegate to transfer the bone selection to the tool
- L137 _public prototype_ `void ReportVertexWeights(UE::Dataflow::FContext& Context, const TArray<TArray<int32>>&SetupIndices, const TArray<TArray<float>>& SetupWeights, const TArray<TArray<int32>>& FinalIndices, const TArray<TArray<float>>& FinalWeights);` — Report the vertex weights back onto the property ones
- L140 _public prototype_ `void ExtractVertexWeights(UE::Dataflow::FContext& Context, const TArray<TArray<int32>>& SetupIndices, const TArray<TArray<float>>& SetupWeights, TArrayView<TArray<int32>> FinalIndices, TArrayView<TArray<float>> FinalWeights) const;` — Extract the vertex weights back from the property ones
- L143 _public prototype_ `static bool FillAttributeWeights(const FManagedArrayCollection& SelectedCollection, const FCollectionAttributeKey& IndicesAttributeKey, const FCollectionAttributeKey& WeightsAttributeKey, TArray<TArray<int32>>& AttributeIndices, TArray<TArray<float>>& AttributeWeights);` — Fill the weight attribute values from the collection
- L147 _public prototype_ `static bool GetAttributeWeights(FManagedArrayCollection& SelectedCollection, const FCollectionAttributeKey& InBoneIndicesKey, const FCollectionAttributeKey& InBoneWeightsKey, TArray<TArray<int32>>& AttributeIndices, TArray<TArray<float>>& AttributeWeights, const bool bCanCompressSkinWeights);` — Get the weight attribute values and add them if not there
- L152 _public prototype_ `static bool SetAttributeWeights(FManagedArrayCollection& SelectedCollection, const FCollectionAttributeKey& InBoneIndicesKey, const FCollectionAttributeKey& InBoneWeightsKey, const TArray<TArray<int32>>& AttributeIndices, const TArray<TArray<float>>& AttributeWeights);` — Set back the attribute values into the collection
- L157 _public prototype_ `FCollectionAttributeKey GetBoneIndicesKey(UE::Dataflow::FContext& Context) const;` — Get the weights attribute key to retrieve/set the weight values
- L160 _public prototype_ `FCollectionAttributeKey GetBoneWeightsKey(UE::Dataflow::FContext& Context) const;` — Get the weights attribute key to retrieve/set the weight values
- L162 _public function_ `TRefCountPtr<FDataflowDebugDrawSkeletonObject> GetDebugDrawSkeleton() const`
- L165 _public function_ `void ValidateSkeletalMeshes()` — Validate the skeletal mesh construction
- L168 _public prototype_ `int32 GetSkeletalMeshOffset(const TObjectPtr<USkeletalMesh>& SkeletalMesh) const;` — Return the collection offset given a skeletal mesh
- L171 _public prototype_ `TUniquePtr<class FToolCommandChange> MakeEditNodeToolChange();`
- L176 _private prototype_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParametersImpl() const override;`
- L177 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L178 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L179 _private prototype_ `virtual void AddPrimitiveComponents(UE::Dataflow::FContext& Context, const TSharedPtr<const FManagedArrayCollection> RenderCollection, TObjectPtr<UObject> NodeOwner, TObjectPtr<AActor> RootActor, TArray<TObjectPtr<UPrimitiveComponent>>& PrimitiveComponents) override;`
- L181 _private prototype_ `virtual void OnInvalidate() override;`
- L183 _private function_ `virtual bool CanDebugDraw() const override`
- L184 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L185 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L191 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L193 _private prototype_ `int32 ComputeInputRefSkeletonHashFromInput(UE::Dataflow::FContext& Context) const;`
- L197 _private member_ `TArray<TObjectPtr<USkeletalMesh>> SkeletalMeshes;` — `UPROPERTY(Transient)` — Transient skeletal mesh built from dataflow render collection
- L200 _private member_ `bool bValidSkeletalMeshes = false;` — Valid skeletal mesh boolean to trigger the construction
- L204 _private member_ `TArray<TObjectPtr<UDynamicMesh>> DynamicMeshes;` — `UPROPERTY(Transient)` — Transient dynamic meshes built from dataflow render collection
- L210 _private member_ `mutable TRefCountPtr<FDataflowDebugDrawSkeletonObject> SkeletonObject;` — not ideal but for now this is the only way we can update the displayed skeleton todo(dataflow) : find a better way to handle skeleton drawing and manipulation post 5.7

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API DATAFLOWNODES_API`
- L72 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anona96610610103`)

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowPrimitiveNode.h` (Public)


#### struct `FDataflowPrimitiveNode`  
`struct FDataflowPrimitiveNode : public FDataflowNode`  
_L14-44_
- reflection: `USTRUCT(Meta = (Experimental))`
- inherits: `FDataflowNode`
- desc: FDataflowPrimitiveNode Base class for nodes that could add a primitive component to the construction scene within the Dataflow graph.
- L18 _public function_ `FDataflowPrimitiveNode() : Super()`
- L21 _public function_ `FDataflowPrimitiveNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid()) : Super(Param,InGuid)`
- L26 _public prototype_ `virtual ~FDataflowPrimitiveNode() = default;` — FDataflowNode interface
- L28 _public function_ `static FName StaticType()`
- L30 _public function_ `virtual bool IsA(FName InType) const override`
- L36 _public function_ `virtual bool HasRenderCollectionPrimitives() const override`
- L42 _public function_ `virtual void AddPrimitiveComponents(UE::Dataflow::FContext& Context, const TSharedPtr<const FManagedArrayCollection> RenderCollection, TObjectPtr<UObject> NodeOwner, TObjectPtr<AActor> RootActor, TArray<TObjectPtr<UPrimitiveComponent>>& PrimitiveComponents)` — Add primitive components to the construction scene

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowSelectionToolNode.h` (Public)


#### struct `FDataflowSelectionToolNodeData`  
`struct FDataflowSelectionToolNodeData`  
_L16-36_
- L19 _public prototype_ `void DeselectVertices(TConstArrayView<int32> Vertices);`
- L20 _public prototype_ `void DeselectVertices(const TSet<int32>& Vertices);`
- L21 _public prototype_ `void DeselectAllVertices();`
- L22 _public prototype_ `void SelectVertices(TConstArrayView<int32> Vertices);`
- L23 _public prototype_ `void SelectVertices(const TSet<int32>& Vertices);`
- L25 _public prototype_ `void GetSelectedVertices(TSet<int32>& OutSelection) const;`
- L27 _public prototype_ `const FDataflowVertexSelection& GetVertexSelection() const;`
- L30 _private prototype_ `void Init(const FManagedArrayCollection& InCollection);`
- L31 _private prototype_ `void LoadFromSnapshot(const FDataflowToolNodeSnapshot& InSnapshot);`
- L32 _private prototype_ `void SaveToSnapshot(FDataflowToolNodeSnapshot& OutSnapshot) const;`
- L35 _private member_ `FDataflowVertexSelection Selection;`

#### struct `FDataflowSelectionToolNode`  
`struct FDataflowSelectionToolNode : public FDataflowToolNode`  
_L43-65_
- reflection: `USTRUCT(meta=(icon="LevelEditor.StrictBoxSelect"))`
- inherits: `FDataflowToolNode`
- desc: Dataflow selection tool node When selected this node opens a selection tool to select vertex or face selection
- L50 _public prototype_ `FDataflowSelectionToolNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L52 _public prototype_ `void LoadData(UE::Dataflow::FContext& Context, FDataflowSelectionToolNodeData& OutData) const;`
- L53 _public prototype_ `void SaveData(const FDataflowSelectionToolNodeData& InData);`
- L58 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection))` — Collection to use for selecting on
- L62 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Output selection - this supports many types and will convert the internal vertex selection to the concrete type of the output
- L64 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAFLOWNODES_API`
- L67 _namespace_ `namespace UE`
- L67 _namespace_ `namespace Dataflow` (scope `UE`)
- L69 _prototype_ `void RegisterSelectionToolNode();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowSkeletalMeshNodes.h` (Public)


#### struct `FDataflowDebugDrawSkeletonObject`  
`struct FDataflowDebugDrawSkeletonObject : public FDataflowDebugDrawBaseObject`  
_L25-60_
- inherits: `FDataflowDebugDrawBaseObject`
- desc: Debug draw skeleton object to debug skeletal meshes
- L27 _public function_ `FDataflowDebugDrawSkeletonObject(IDataflowDebugDrawInterface::FDataflowElementsType& InDataflowElements, const FReferenceSkeleton& InReferenceSkeleton, const bool bBonesVisible = true) : FDataflowDebugDrawBaseObject(InDataflowElements), ReferenceSkeleton(InReferenceSkeleton), bBonesVisible(bBonesVisible)`
- L32 _public prototype_ `virtual void PopulateDataflowElements() override;` — Populate dataflow elements
- L35 _public prototype_ `virtual void DrawDataflowElements(FPrimitiveDrawInterface* PDI) override;` — Debug draw dataflow element
- L38 _public prototype_ `virtual FBox ComputeBoundingBox() const override;` — Compute the dataflow elements bounding box
- L41 _public prototype_ `void OverrideBoneTransforms(const TArray<FTransform>& InBoneTransforms);` — override the bone transforms
- L43 _public prototype_ `const FReferenceSkeleton& GetReferenceSkeleton() const;`
- L46 _public member_ `FDataflowBoneSelectionChangedNotifyDelegate OnBoneSelectionChanged;` — Delegate to broadcast bones selection changes
- L49 _private member_ `FCriticalSection TransformOverridesLockGuard;`
- L50 _private member_ `TArray<FTransform> TransformOverrides;`
- L53 _private member_ `const FReferenceSkeleton ReferenceSkeleton;` — Skeletal mesh to use to populate/draw scene elements
- L56 _private member_ `TArray<bool> PreviousSelection;` — Previous element selection
- L59 _private member_ `bool bBonesVisible = true;` — Boolean to make the bones visible or not

#### struct `FGetSkeletalMeshDataflowNode`  
`struct FGetSkeletalMeshDataflowNode: public FDataflowNode`  
_L63-95_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L71 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput, DisplayName = "SkeletalMesh"))`
- L74 _public member_ `FName PropertyName = "Sk` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L76 _public function_ `FGetSkeletalMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L82 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L85 _private prototype_ `virtual bool SupportsAssetProperty(UObject* Asset) const override;`
- L86 _private prototype_ `virtual void SetAssetProperty(UObject* Asset) override;`
- L89 _private function_ `virtual bool CanDebugDraw() const override`
- L90 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L91 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FGetSkeletonDataflowNode`  
`struct FGetSkeletonDataflowNode : public FDataflowNode`  
_L98-130_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L106 _public member_ `TObjectPtr<const USkeleton> Skeleton = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput, DisplayName = "Skeleton"))`
- L109 _public member_ `FName PropertyName = "Sk` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L111 _public function_ `FGetSkeletonDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L117 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L120 _private prototype_ `virtual bool SupportsAssetProperty(UObject* Asset) const override;`
- L121 _private prototype_ `virtual void SetAssetProperty(UObject* Asset) override;`
- L124 _private function_ `virtual bool CanDebugDraw() const override`
- L125 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L126 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FSkeletalMeshBoneDataflowNode`  
`struct FSkeletalMeshBoneDataflowNode : public FDataflowNode`  
_L134-161_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L141 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L144 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L147 _public member_ `int BoneIndexOut = INDEX_NONE;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Index"))`
- L150 _public member_ `FName PropertyName = "Ov` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L152 _public function_ `FSkeletalMeshBoneDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L160 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSkeletalMeshReferenceTransformDataflowNode`  
`struct FSkeletalMeshReferenceTransformDataflowNode : public FDataflowNode`  
_L165-191_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L173 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMeshIn = nullptr;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L176 _public member_ `int32 BoneIndexIn = INDEX_NONE;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Index"))`
- L179 _public member_ `FTransform TransformOut = FTransform::Identity;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Transform"))`
- L181 _public function_ `FSkeletalMeshReferenceTransformDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L190 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetPhysicsAssetFromSkeletalMeshDataflowNode`  
`struct FGetPhysicsAssetFromSkeletalMeshDataflowNode : public FDataflowNode`  
_L195-218_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get the physics assets from input skeletal mesh.
- L203 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh", Meta = (DataflowInput))` — Input skeletal mesh
- L207 _public member_ `TObjectPtr<const UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(Meta = (DataflowOutput))` — Output physics asset
- L209 _public function_ `FGetPhysicsAssetFromSkeletalMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L217 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAFLOWNODES_API`
- L16 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogDataflowSkeletalMeshNodes, Log, All);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDataflowBoneSelectionChangedNotifyDelegate, const TArray<FName>& );` — A delegate for monitoring dataflow skeleton selection changes.
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDataflowBoneSelectionChangedNotifyDelegate, const TArray<FName>& );` — A delegate for monitoring dataflow skeleton selection changes.
- L220 _namespace_ `namespace UE`
- L220 _namespace_ `namespace Dataflow` (scope `UE`)
- L222 _prototype_ `void RegisterSkeletalMeshNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowToolNode.h` (Public)


#### struct `FDataflowToolNodeSnapshot`  
`struct FDataflowToolNodeSnapshot`  
_L22-52_
- reflection: `USTRUCT()`
- desc: Represents data for tool node to store when the user press accept or explictly store a snapshot
- L27 _public prototype_ `uint64 GetAllocatedSize() const;` — Returns the approximate amount of memory taken by the snapshot in bytes
- L29 _public function_ `const FDateTime& GetDate() const`
- L30 _public function_ `bool IsLocked() const`
- L34 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = Snapshots)` — Display name of the snapshot
- L38 _public member_ `FString Description;` — `UPROPERTY(VisibleAnywhere, Category = Snapshots)` — description of the snapshot , not user editable
- L42 _public member_ `FManagedArrayCollection Data;` — `UPROPERTY()` — collection that stores the data of the snapshot
- L47 _private member_ `FDateTime Date = FDateTime::Now();` — `UPROPERTY(VisibleAnywhere, Category = Snapshots)` — Date time at when the snapshot was created - Read-only
- L51 _private member_ `bool bLocked = false;` — `UPROPERTY(EditAnywhere, Category = Snapshots)` — When true, this snapshot cannot be dropped if the maximum number of snapshot is reached and room needs to be made for a new one

#### struct `FDataflowToolNodeSnapshotSet`  
`struct FDataflowToolNodeSnapshotSet`  
_L58-81_
- reflection: `USTRUCT()`
- desc: This represent a set of snapshots
- L62 _public prototype_ `TConstArrayView<FDataflowToolNodeSnapshot> GetSnapshots() const;`
- L63 _public prototype_ `const FDataflowToolNodeSnapshot* GetActiveSnapshot() const;`
- L65 _public prototype_ `FDataflowToolNodeSnapshot& AddSnapshot(bool bNotify = false);`
- L66 _public prototype_ `void SetActiveSnapshot(int32 ActiveIndex, bool bNotify = false);`
- L67 _public prototype_ `bool RemoveSnapshot(int32 Index, bool bNotify = false);`
- L68 _public prototype_ `int32 FindOldestUnlockedSnapShot();`
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSnapshotSetChanged, FDataflowToolNodeSnapshotSet&);`
- L71 _public member_ `FOnSnapshotSetChanged OnSnapshotSetChanged;`
- L74 _private prototype_ `void NotifyChanged();`
- L77 _private member_ `int32 ActiveSnapshot = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = Snapshots)`
- L80 _private member_ `TArray<FDataflowToolNodeSnapshot> Snapshots;` — `UPROPERTY(EditAnywhere, Category = Snapshots, meta = (EditFixedSize, TitleProperty = "{Name} {Date}"))`

#### struct `FDataflowToolNode`  
`struct FDataflowToolNode : public FDataflowNode`  
_L87-132_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Base class for a node that can bring up a tool
- L91 _public prototype_ `FDataflowToolNode() = default;`
- L93 _public prototype_ `FDataflowToolNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L94 _public prototype_ `virtual ~FDataflowToolNode();`
- L97 _public prototype_ `TConstArrayView<FDataflowToolNodeSnapshot> GetSnapshots() const;`
- L98 _public prototype_ `const FDataflowToolNodeSnapshot* GetActiveSnapshot() const;`
- L101 _protected prototype_ `FDataflowToolNodeSnapshot& AddSnapshot();`
- L102 _protected prototype_ `bool RemoveSnapshot(int32 Index);`
- L103 _protected prototype_ `int32 FindOldestUnlockedSnapShot();`
- L123 _private prototype_ `void SwapSnapshots(FDataflowToolNodeSnapshotSet& InOutSnapshots);`
- L125 _private prototype_ `void RegisterNotifyChanged();`
- L126 _private prototype_ `void UnregisterNotifyChanged();`
- L127 _private member_ `FDelegateHandle OnNotifyChangedHandle;`
- L128 _private prototype_ `void OnSnapshotSetChanged(FDataflowToolNodeSnapshotSet& Set);`
- L131 _private member_ `FDataflowToolNodeSnapshotSet Snapshots;` — `UPROPERTY(EditAnywhere, Category = Snapshots)`

#### class `FDataflowToolNode::FSnapshotToolChange`  
`class FSnapshotToolChange : public FToolCommandChange`  
_L105-120_
- inherits: `FToolCommandChange`
- L108 _public prototype_ `FSnapshotToolChange(FDataflowToolNode& Node);`
- L111 _protected prototype_ `virtual FString ToString() const override;`
- L112 _protected prototype_ `virtual void Apply(UObject* Object) override;`
- L113 _protected prototype_ `virtual void Revert(UObject* Object) override;`
- L115 _protected prototype_ `virtual void SwapApplyRevert(UObject* Object, FDataflowToolNode& Node);`
- L118 _private member_ `TWeakPtr<FDataflowToolNode> WeakNode;`
- L119 _private member_ `FDataflowToolNodeSnapshotSet SavedSnapshots;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DATAFLOWNODES_API`
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSnapshotSetChanged, FDataflowToolNodeSnapshotSet&);`

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowVertexAttributeEditableNode.h` (Public)


#### struct `FDataflowVertexAttributeEditableNode`  
`struct FDataflowVertexAttributeEditableNode : public FDataflowToolNode`  
_L15-38_
- reflection: `USTRUCT()`
- inherits: `FDataflowToolNode`
- desc: Base class for node using the vertex attribute paint tool
- L19 _public function_ `FDataflowVertexAttributeEditableNode()`
- L21 _public prototype_ `FDataflowVertexAttributeEditableNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L25 _public prototype_ `TUniquePtr<class FToolCommandChange> MakeEditNodeToolChange();`
- L28 _public function_ `virtual void GetSupportedViewModes(UE::Dataflow::FContext& Context, TArray<FName>& OutViewModeNames) const` — Get the list of view mode supported by this node when being edited
- L31 _public function_ `virtual void GetVertexAttributeValues(UE::Dataflow::FContext& Context, TArray<float>& OutValues) const` — Get the absolute vertex attribute values
- L34 _public function_ `virtual void SetVertexAttributeValues(UE::Dataflow::FContext& Context, const TArray<float>& InValues, const TArray<int32>& InWeightIndices)` — Set the absolute vertex attribute values - InWeightIndices can be used to sepcify which indices are to be set
- L37 _public prototype_ `virtual void GetExtraVertexMapping(UE::Dataflow::FContext& Context, FName SelectedViewMode, TArray<int32>& OutMappingToWeight, TArray<TArray<int32>>& OutMappingFromWeight) const;` — Provide a extra indirection vertex mapping - optional will return empty by default

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAFLOWNODES_API`

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/DataflowVertexPropertyGroup.h` (Public)


#### class `IDataflowAddScalarVertexPropertyCallbacks`  
`class IDataflowAddScalarVertexPropertyCallbacks`  
_L19-37_
- desc: interface for defining vertex property groups this is used by nodes to know how to access collection data from a specific vertex group
- L22 _public typedef_ `using FAttributeKey = FDataflowNode::FAttributeKey;`
- L32 _public prototype_ `virtual ~IDataflowAddScalarVertexPropertyCallbacks() = default;`
- L33 _public prototype_ `virtual FName GetName() const = 0;`
- L34 _public prototype_ `virtual TArray<FName> GetTargetGroupNames() const = 0;`
- L35 _public function_ `virtual void GetTargetGroupInfos(TArray<FTargetGroupInfo>& OutInfos) const`
- L36 _public prototype_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderingParameters() const = 0;`

#### struct `IDataflowAddScalarVertexPropertyCallbacks::FTargetGroupInfo`  
`struct FTargetGroupInfo`  
_L24-30_
- L26 _public member_ `FName TargetGroup;`
- L27 _public member_ `FAttributeKey PositionAttributeKey;`
- L28 _public member_ `FAttributeKey IndicesAttributeKey;`
- L29 _public member_ `FAttributeKey MappingFrom2DTo3DAttributeKey;`

#### class `FDataflowAddScalarVertexPropertyCallbackRegistry`  
`class FDataflowAddScalarVertexPropertyCallbackRegistry`  
_L42-65_
- desc: Registry for implementations of IDataflowAddScalarVertexPropertyCallbacks
- L46 _public typedef_ `using FTargetGroupInfo = IDataflowAddScalarVertexPropertyCallbacks::FTargetGroupInfo;`
- L48 _public prototype_ `static FDataflowAddScalarVertexPropertyCallbackRegistry& Get();`
- L50 _public prototype_ `void RegisterCallbacks(TUniquePtr<IDataflowAddScalarVertexPropertyCallbacks>&& Callbacks);`
- L52 _public prototype_ `void DeregisterCallbacks(const FName& CallbacksName);`
- L54 _public prototype_ `TArray<FName> GetTargetGroupNames() const;`
- L56 _public prototype_ `FTargetGroupInfo GetTargetGroupInfo(FName TargetGroup) const;`
- L58 _public prototype_ `TArray<UE::Dataflow::FRenderingParameter> GetRenderingParameters() const;`
- L60 _public prototype_ `TArray<UE::Dataflow::FRenderingParameter> GetRenderingParameters(const FName& TargetGroup) const;`
- L64 _private member_ `TMap<FName, TUniquePtr<IDataflowAddScalarVertexPropertyCallbacks>> AllCallbacks;`

#### struct `FScalarVertexPropertyGroup`  
`struct FScalarVertexPropertyGroup`  
_L72-78_
- reflection: `USTRUCT()`
- desc: Custom type so that we can use property type customization Used by Dataflow nodes as a property type - displays as a combobox with the registered groups
- L77 _public member_ `FName Name = FGeometryCollection::VerticesGroup;` — `UPROPERTY(EditAnywhere, Category = "Vertex Group")`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWNODES_API`

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/SamplerNodes/DataflowSamplerTypes.h` (Public)


#### struct `FDataflowFloatSamplerBase`  
`struct FDataflowFloatSamplerBase`  
_L17-25_
- reflection: `USTRUCT()`
- desc: A float sampler, sample at a specific 3D position  and return a single float value per position
- L22 _public prototype_ `virtual ~FDataflowFloatSamplerBase() = default;`
- L23 _public function_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const`
- L24 _public function_ `virtual FBox GetRenderBounds() const`

#### struct `FDataflowFloatSampler`  
`struct FDataflowFloatSampler : public FDataflowFloatSamplerBase`  
_L28-45_
- reflection: `USTRUCT()`
- inherits: `FDataflowFloatSamplerBase`
- L33 _public prototype_ `FDataflowFloatSampler() = default;`
- L34 _public prototype_ `FDataflowFloatSampler(const FDataflowFloatSampler&) = default;`
- L35 _public prototype_ `FDataflowFloatSampler& operator=(const FDataflowFloatSampler&) = default;`
- L36 _public prototype_ `FDataflowFloatSampler(const TSharedPtr<const FDataflowFloatSamplerBase>& InImpl);`
- L38 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<float> OutValues) const override;`
- L39 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L41 _public function_ `const TSharedPtr<const FDataflowFloatSamplerBase>& GetImpl() const`
- L44 _private member_ `TSharedPtr<const FDataflowFloatSamplerBase> Impl;`

#### struct `FDataflowVectorSamplerBase`  
`struct FDataflowVectorSamplerBase`  
_L53-60_
- reflection: `USTRUCT()`
- desc: A vector sampler, sample at a specific 3D position  and return a FVector3f value per position
- L57 _public prototype_ `virtual ~FDataflowVectorSamplerBase() = default;`
- L58 _public function_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const`
- L59 _public function_ `virtual FBox GetRenderBounds() const`

#### struct `FDataflowVectorSampler`  
`struct FDataflowVectorSampler : public FDataflowVectorSamplerBase`  
_L63-80_
- reflection: `USTRUCT()`
- inherits: `FDataflowVectorSamplerBase`
- L68 _public prototype_ `FDataflowVectorSampler() = default;`
- L69 _public prototype_ `FDataflowVectorSampler(const FDataflowVectorSampler&) = default;`
- L70 _public prototype_ `FDataflowVectorSampler& operator=(const FDataflowVectorSampler&) = default;`
- L71 _public prototype_ `FDataflowVectorSampler(const TSharedPtr<const FDataflowVectorSamplerBase>& InImpl);`
- L73 _public prototype_ `virtual void Sample(TArrayView<const FVector3f> Positions, TArrayView<FVector3f> OutValues) const override;`
- L74 _public prototype_ `virtual FBox GetRenderBounds() const override;`
- L76 _public function_ `const TSharedPtr<const FDataflowVectorSamplerBase>& GetImpl() const`
- L79 _private member_ `TSharedPtr<const FDataflowVectorSamplerBase> Impl;`

#### struct `FDataflowSamplerTypesStorage`  
`struct FDataflowSamplerTypesStorage`  
_L85-112_
- reflection: `USTRUCT()`
- L89 _public prototype_ `FDataflowSamplerTypesStorage() = default;`
- L90 _public prototype_ `FDataflowSamplerTypesStorage(const FDataflowSamplerTypesStorage& Other) = default;`
- L91 _public prototype_ `FDataflowSamplerTypesStorage& operator=(const FDataflowSamplerTypesStorage& Other) = default;`
- L92 _public prototype_ `FDataflowSamplerTypesStorage(FDataflowSamplerTypesStorage&& Other) = default;`
- L93 _public prototype_ `FDataflowSamplerTypesStorage& operator=(FDataflowSamplerTypesStorage&& Other) = default;`
- L94 _public function_ `FDataflowSamplerTypesStorage(const FDataflowFloatSampler& Sampler) : Storage(TInPlaceType<FDataflowFloatSampler>(), Sampler)`
- L98 _public function_ `FDataflowSamplerTypesStorage(const FDataflowVectorSampler& Sampler) : Storage(TInPlaceType<FDataflowVectorSampler>(), Sampler)`
- L104 _public function_ `template<typename T> const T* TryGet() const`
- L111 _private member_ `TVariant<FDataflowFloatSampler, FDataflowVectorSampler> Storage;` — Currently we don't support serialization for this storage

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FDataflowSamplerTypesStorage>`  
_L115-130_
- L118 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowSamplerTypesStorage& To)`
- L123 _public function_ `template <typename TToType> static void To(const FDataflowSamplerTypesStorage& From, TToType& To)`

#### struct `FDataflowSamplerTypePolicy`  
`struct FDataflowSamplerTypePolicy : public TDataflowMultiTypePolicy<FDataflowFloatSampler, FDataflowVectorSampler>`  
_L139-142_
- inherits: `TDataflowMultiTypePolicy<FDataflowFloatSampler,FDataflowVectorSampler>`

#### struct `FDataflowSamplerTypes`  
`struct FDataflowSamplerTypes : public FDataflowAnyType`  
_L145-155_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- L147 _public typedef_ `using FPolicyType = FDataflowSamplerTypePolicy;`
- L148 _public typedef_ `using FStorageType = FDataflowSamplerTypesStorage;`
- L154 _public member_ `FDataflowSamplerTypesStorage Value;` — `UPROPERTY()` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWNODES_API`
- L157 _namespace_ `namespace UE`
- L157 _namespace_ `namespace Dataflow` (scope `UE`)
- L159 _prototype_ `void RegisterSamplerTypes();` (scope `UE::Dataflow`)
- L164 _namespace_ `namespace UE`
- L164 _namespace_ `namespace Dataflow` (scope `UE`)
- L166 _prototype_ `void RegisterSamplerNodes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/Transfer/DataflowMeshAttributesTransferNodes.h` (Public)


#### struct `FDataflowAttributeProxy`  
`struct FDataflowAttributeProxy`  
_L31-36_
- reflection: `USTRUCT(meta=(Abstract))`
- desc: Abstract base USTRUCT for all attribute proxy descriptors used by FTransferMeshAttributesDataflowNode. Subclass this to represent a specific attribute type (skin weights, morph targets, etc.) that should be transferred.
- L35 _public prototype_ `virtual ~FDataflowAttributeProxy() = default;`

#### struct `FDataflowSkeletonProxy`  
`struct FDataflowSkeletonProxy: public FDataflowAttributeProxy`  
_L42-45_
- reflection: `USTRUCT(meta=(DisplayName="Skeleton"))`
- inherits: `FDataflowAttributeProxy`
- desc: Proxy descriptor representing the skeleton (bone hierarchy) to carry over during an attribute transfer.

#### enum `EProxySourceType`  
`enum class EProxySourceType : uint8`  
_L51-57_
- reflection: `UENUM()`
- desc: Controls whether an attribute proxy operates on all layers of a given type or only a specific named layer.
- L54 _public enumerator_ `All` — Transfer every instance (layer) of this attribute type found on the source mesh.
- L56 _public enumerator_ `Specific` — Transfer only the single named attribute specified by Source, writing the result under the name Destination.

#### struct `FDataflowSkinWeightsProxy`  
`struct FDataflowSkinWeightsProxy: public FDataflowAttributeProxy`  
_L64-79_
- reflection: `USTRUCT(meta=(DisplayName="Skin Weights"))`
- inherits: `FDataflowAttributeProxy`
- desc: Proxy descriptor that configures the transfer of a skin-weight attribute from a source mesh to a target mesh. Add one of these to FTransferMeshAttributesDataflowNode::AttributeProxies to include skin weights in the transfer.
- L70 _public member_ `EProxySourceType SourceType = EProxySourceType::All;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy)` — Determines whether all skin-weight layers are transferred or only the one named by Source.
- L74 _public member_ `FName Source = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name of the skin-weight attribute layer to read from the source mesh.
- L78 _public member_ `FName Destination = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name to assign the skin-weight attribute layer on the destination mesh.

#### struct `FDataflowMorphTargetProxy`  
`struct FDataflowMorphTargetProxy: public FDataflowAttributeProxy`  
_L86-101_
- reflection: `USTRUCT(meta=(DisplayName="Morph Target"))`
- inherits: `FDataflowAttributeProxy`
- desc: Proxy descriptor that configures the transfer of a morph-target delta attribute from a source mesh to a target mesh. Add one of these to FTransferMeshAttributesDataflowNode::AttributeProxies to include morph targets in the transfer.
- L92 _public member_ `EProxySourceType SourceType = EProxySourceType::All;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy)` — Determines whether all morph-target layers are transferred or only the one named by Source.
- L96 _public member_ `FName Source = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name of the morph-target attribute to read from the source mesh
- L100 _public member_ `FName Destination = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name to assign the morph-target attribute on the destination mesh.

#### struct `FDataflowPolygroupProxy`  
`struct FDataflowPolygroupProxy: public FDataflowAttributeProxy`  
_L108-123_
- reflection: `USTRUCT(meta=(DisplayName="Polygroup"))`
- inherits: `FDataflowAttributeProxy`
- desc: Proxy descriptor that configures the transfer of a polygroup layer from a source mesh to a target mesh. Add one of these to FTransferMeshAttributesDataflowNode::AttributeProxies to include polygroups in the transfer.
- L114 _public member_ `EProxySourceType SourceType = EProxySourceType::All;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy)` — Determines whether all polygroup layers are transferred or only the one named by Source.
- L118 _public member_ `FName Source = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name of the polygroup layer to read from the source mesh.
- L122 _public member_ `FName Destination = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name to assign the polygroup layer on the destination mesh.

#### struct `FDataflowTriangleLabelsProxy`  
`struct FDataflowTriangleLabelsProxy: public FDataflowAttributeProxy`  
_L130-145_
- reflection: `USTRUCT(meta=(DisplayName="Triangle Labels"))`
- inherits: `FDataflowAttributeProxy`
- desc: Proxy descriptor that configures the transfer of a triangle-label attribute from a source mesh to a target mesh. Add one of these to FTransferMeshAttributesDataflowNode::AttributeProxies to include triangle labels in the transfer.
- L136 _public member_ `EProxySourceType SourceType = EProxySourceType::All;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy)` — Determines whether all triangle-label layers are transferred or only the one named by Source.
- L140 _public member_ `FName Source = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name of the triangle-label attribute to read from the source mesh.
- L144 _public member_ `FName Destination = NAME_None;` — `UPROPERTY(EditAnywhere, Category = AttributeProxy, meta = (EditCondition = "SourceType!=EProxySourceType::All"))` — Name to assign the triangle-label attribute on the destination mesh.

#### struct `FTransferMeshAttributesDataflowNode`  
`struct FTransferMeshAttributesDataflowNode : public FDataflowNode`  
_L156-237_
- reflection: `USTRUCT(Meta = (Experimental))`
- inherits: `FDataflowNode`
- L163 _public prototype_ `FTransferMeshAttributesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L167 _public member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Mesh, DataflowIntrinsic))` — The destination mesh modified in-place during evaluation.
- L171 _public member_ `TObjectPtr<const UDataflowMesh> SourceMesh;` — `UPROPERTY(EditAnywhere, Category = "SourceMesh", Meta = (DataflowInput))` — The source mesh whose attributes are sampled during transfer.
- L175 _public member_ `FDataflowFunctionProperty All;` — `UPROPERTY(EditAnywhere, Transient, SkipSerialization, Category=Attributes)` — Adds all available proxies for transfer.
- L179 _public member_ `FDataflowFunctionProperty None;` — `UPROPERTY(EditAnywhere, Transient, SkipSerialization, Category=Attributes)` — Removes all proxies.
- L183 _public member_ `TArray<FInstancedStruct> AttributeProxies;` — `UPROPERTY(EditAnywhere, Category = Attributes, meta = (ExcludeBaseStruct, BaseStruct = "/Script/DataflowNodes.DataflowAttributeProxy"))` — Attribute proxies descriptors that determines which attributes are transferred and how.
- L188 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;` — Reads Mesh and SourceMesh from Context, transfer proxies and writes the modified mesh back as the node's output.
- L196 _private prototype_ `void TransferProxies( UE::Dataflow::FContext& Context, const UE::Geometry::FDynamicMesh3& InSrcDynaMesh, UE::Geometry::FDynamicMesh3& InOutDstDynaMesh) const;` — Constructs an FTransferAttributes operator from InSrcDynaMesh and InOutDstDynaMesh then invokes TransferAttributesToMesh. @param Context          Dataflow context, forwarded to BuildProxies for any context-dependent lookups. @param InSrcDynaMesh    Source dynamic mesh to sample attributes from. @param InOutDstDynaMesh Destination dynamic mesh to receive the transferred attributes.
- L207 _private prototype_ `void BuildProxies( UE::Geometry::FTransferAttributes& TransferAttributes, const UE::Geometry::FDynamicMeshAttributeSet* SrcAttributes, UE::Geometry::FDynamicMeshAttributeSet* DstAttributes) const;` — Converts the AttributeProxies array into concrete geometry proxy objects (FSkinWeightsProxy, FMorphTargetProxy, etc.). @param TransferAttributes  The operator to populate with proxy objects. @param SrcAttributes       Attribute set of the source dynamic mesh, used to look up source layers. @param DstAttributes       Attribute set of the destination dynamic mesh.
- L213 _private prototype_ `void AddAllAttributes(UE::Dataflow::FContext& Context);` — Adds all available proxies for transfer.
- L216 _private prototype_ `void RemoveAllAttributes(UE::Dataflow::FContext& Context);` — Removes all proxies.
- L225 _private function_ `template<typename ProxyType> TArray<const ProxyType*> GetProxies() const` — Filters AttributeProxies and returns typed const pointers to all entries of type ProxyType. @tparam ProxyType  A concrete FDataflowAttributeProxy subtype to filter for. @return Array of non-owning const pointers to matching proxy entries in AttributeProxies.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATAFLOWNODES_API`
- L18 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogDataflowMeshAttributesTransferNode, Log, All);`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowNodes/Public/Dataflow/Transfer/TransferAttributes.h` (Public)


#### struct `UE::Geometry::FClosestSample`  
`struct FClosestSample`  
_L34-40_
- desc: Stores the result of a closest-point query on a mesh surface. Used internally by FTransferAttributes to record which triangle a projected point landed on and its position within that triangle.
- L37 _public member_ `int32 TriID = IndexConstants::InvalidID;` — Index of the triangle that contains the closest point. Set to IndexConstants::InvalidID when no match was found.
- L39 _public member_ `FVector3d Bary = FVector3d::ZeroVector;` — Barycentric coordinates of the closest point relative to the vertices of TriID.

#### struct `UE::Geometry::FSkinWeightsProxy`  
`struct UE_EXPERIMENTAL(5.8, "Generic attribute transfer is experimental while under active development.") FSkinWeightsProxy`  
_L49-202_
- desc: Proxy that transfers a single named skin-weight attribute from a source FDynamicMesh3 to a target mesh. Weights are blended using barycentric interpolation over the source triangle found at each target vertex. Optionally remaps bone indices when the source and target skeletons differ. @experimental Available since UE 5.8; the API may change without notice.
- L86 _public function_ `FSkinWeightsProxy( const FDynamicMeshVertexSkinWeightsAttribute* InAttribute, const FName InDstName, const FSkinWeightsProxyOptions& InOptions = FSkinWeightsProxyOptions()) : SrcAttribute(InAttribute) , DstName(InDstName) , Options(InOptions)` — Constructs a proxy bound to the given source skin-weight attribute. @param InAttribute  Source attribute to read from. Must not be null. @param InDstName    Name of the attribute to write on the destination mesh. @param InOptions    Optional configuration controlling bone remapping and normalization.
- L104 _public function_ `bool GetOrCreateDestAttribute(FDynamicMesh3& InDstMesh)` — Looks up or creates the named skin-weight attribute on InDstMesh. If the attribute already exists it is reused; otherwise a new one is allocated and attached. @param InDstMesh  Destination mesh to query/modify. @return true on success, false if the attribute could not be created.
- L125 _public function_ `void Transfer(const int32 VertexID, const FIndex3i& Triangle, const FVector3f& BaryWeights) const` — Blends the skin weights of the three triangle vertices using BaryWeights, optionally remaps bone indices from the source skeleton to the target skeleton, and writes the result to VertexID. Must be called after GetOrCreateDestAttribute. @param VertexID     Target mesh vertex to write the blended weights to. @param Triangle     Indices of the three source mesh vertices forming the enclosing triangle. @param BaryWeights  Barycentric blend weights (sum to 1) for the three triangle vertices.
- L195 _public member_ `const FDynamicMeshVertexSkinWeightsAttribute* SrcAttribute = nullptr;` — Read-only pointer to the source skin-weight attribute.
- L197 _public member_ `FDynamicMeshVertexSkinWeightsAttribute* DstAttribute = nullptr;` — Pointer to the destination attribute on the target mesh; populated by GetOrCreateDestAttribute.
- L199 _public member_ `FName DstName = NAME_None;` — Name used to look up or create the destination attribute on the target mesh.
- L201 _public member_ `FSkinWeightsProxyOptions Options;` — Options supplied at construction time.

#### struct `UE::Geometry::FSkinWeightsProxy::FSkinWeightsProxyOptions`  
`struct FSkinWeightsProxyOptions`  
_L54-77_
- desc: Configuration options for FSkinWeightsProxy.
- L56 _public function_ `FSkinWeightsProxyOptions() : MaxNumInfluences(AnimationCore::MaxInlineBoneWeightCount) , bNormalizeToOne(true)`
- L62 _public member_ `const int32 MaxNumInfluences = AnimationCore::MaxInlineBoneWeightCount;` — Maximum number of bone influences kept per vertex after blending. Excess influences are pruned.
- L68 _public member_ `TArray<FName> SourceIndexToBone;` — Maps each source bone index to its bone name. Must be provided (together with TargetBoneToIndex) when transferring across skeletons with different index layouts. May be empty when source and target share identical bone indices.
- L74 _public member_ `TMap<FName, FBoneIndexType> TargetBoneToIndex;` — Maps each bone name to its index in the target skeleton. Must be provided (together with SourceIndexToBone) when transferring across skeletons with different index layouts. May be empty when source and target share identical bone indices.
- L76 _public member_ `bool bNormalizeToOne = true;` — If true, blended weights are renormalized to sum to 1 after interpolation and remapping.

#### struct `UE::Geometry::FMorphTargetProxy`  
`struct UE_EXPERIMENTAL(5.8, "Generic attribute transfer is experimental while under active development.") FMorphTargetProxy`  
_L210-275_
- desc: Proxy that transfers a single named morph-target delta attribute from a source FDynamicMesh3 to a target mesh. Per-vertex position deltas are blended via barycentric interpolation over the enclosing source triangle. @experimental Available since UE 5.8; the API may change without notice.
- L218 _public function_ `FMorphTargetProxy(const FDynamicMeshMorphTargetAttribute* InAttribute, const FName InDstName) : SrcAttribute(InAttribute) , DstName(InDstName)` — Constructs a proxy bound to the given source morph-target attribute. @param InAttribute  Source attribute to read from. Must not be null. @param InDstName    Name of the morph-target attribute to write on the destination mesh.
- L231 _public function_ `bool GetOrCreateDestAttribute(FDynamicMesh3& InDstMesh)` — Looks up or creates the named morph-target attribute on InDstMesh. @param InDstMesh  Destination mesh to query/modify. @return true on success, false if the attribute could not be created.
- L252 _public function_ `void Transfer(const int32 VertexID, const FIndex3i& Triangle, const FVector3f& BaryWeights) const` — Linearly interpolates the morph-target position deltas of the three triangle vertices using BaryWeights and writes the resulting delta to VertexID on the destination attribute. Must be called after GetOrCreateDestAttribute. @param VertexID     Target mesh vertex to write the interpolated delta to. @param Triangle     Indices of the three source mesh vertices forming the enclosing triangle. @param BaryWeights  Barycentric blend weights (sum to 1) for the three triangle vertices.
- L269 _public member_ `const FDynamicMeshMorphTargetAttribute* SrcAttribute = nullptr;` — Read-only pointer to the source morph-target attribute.
- L271 _public member_ `FDynamicMeshMorphTargetAttribute* DstAttribute = nullptr;` — Pointer to the destination attribute on the target mesh; populated by GetOrCreateDestAttribute.
- L274 _public member_ `FName DstName = NAME_None;` — Name used to look up or create the destination attribute on the target mesh.

#### struct `UE::Geometry::FPolygroupProxy`  
`struct UE_EXPERIMENTAL(5.8, "Generic attribute transfer is experimental while under active development.") FPolygroupProxy`  
_L293-346_
- desc: Proxy that copies a single named polygroup layer from source triangles to matching target triangles. Polygroup values are discrete integer labels, so no interpolation is performed; the value of the closest source triangle is assigned directly. @experimental Available since UE 5.8; the API may change without notice.
- L301 _public function_ `FPolygroupProxy(const FDynamicMeshPolygroupAttribute* InAttribute, const FName InDstName) : SrcAttribute(InAttribute) , DstName(InDstName)` — Constructs a proxy bound to the given source polygroup attribute. @param InAttribute  Source attribute to read from. Must not be null. @param InDstName    Name of the polygroup layer to write on the destination mesh.
- L314 _public function_ `bool GetOrCreateDestAttribute(FDynamicMesh3& InDstMesh)` — Finds the named polygroup layer on InDstMesh, or appends a new layer if it does not exist. @param InDstMesh  Destination mesh to query/modify. @return true on success, false if the layer could not be found or created.
- L335 _public function_ `void Transfer(const int32 SrcTriangleID, const int32 DstTriangleID) const` — Copies the polygroup value from SrcTriangleID on the source attribute to DstTriangleID on the destination attribute. Must be called after GetOrCreateDestAttribute. @param SrcTriangleID  Triangle index on the source mesh to read the group value from. @param DstTriangleID  Triangle index on the destination mesh to write the group value to.
- L341 _public member_ `const FDynamicMeshPolygroupAttribute* SrcAttribute = nullptr;` — Read-only pointer to the source polygroup attribute.
- L343 _public member_ `FDynamicMeshPolygroupAttribute* DstAttribute = nullptr;` — Pointer to the destination attribute on the target mesh; populated by GetOrCreateDestAttribute.
- L345 _public member_ `FName DstName = NAME_None;` — Name used to look up or create the destination polygroup layer on the target mesh.

#### struct `UE::Geometry::FTriangleLabelProxy`  
`struct UE_EXPERIMENTAL(5.8, "Generic attribute transfer is experimental while under active development.") FTriangleLabelProxy`  
_L354-405_
- desc: Proxy that copies a single named triangle-label attribute from source triangles to matching target triangles. Labels are discrete values so no interpolation is performed. @experimental Available since UE 5.8; the API may change without notice.
- L362 _public function_ `FTriangleLabelProxy(const FDynamicMeshTriangleLabelAttribute* InAttribute, const FName InDstName) : SrcAttribute(InAttribute) , DstName(InDstName)` — Constructs a proxy bound to the given source triangle-label attribute. @param InAttribute  Source attribute to read from. Must not be null. @param InDstName    Name of the triangle-label attribute to write on the destination mesh.
- L375 _public function_ `bool GetOrCreateDestAttribute(FDynamicMesh3& InDstMesh)` — Looks up or creates the named triangle-label attribute on InDstMesh. @param InDstMesh  Destination mesh to query/modify. @return true on success, false if the attribute could not be created.
- L394 _public function_ `void Transfer(const int32 SrcTriangleID, const int32 DstTriangleID) const` — Copies the label value from SrcTriangleID on the source attribute to DstTriangleID on the destination attribute. Must be called after GetOrCreateDestAttribute. @param SrcTriangleID  Triangle index on the source mesh to read the label from. @param DstTriangleID  Triangle index on the destination mesh to write the label to.
- L400 _public member_ `const FDynamicMeshTriangleLabelAttribute* SrcAttribute = nullptr;` — Read-only pointer to the source triangle-label attribute.
- L402 _public member_ `FDynamicMeshTriangleLabelAttribute* DstAttribute = nullptr;` — Pointer to the destination attribute on the target mesh; populated by GetOrCreateDestAttribute.
- L404 _public member_ `FName DstName = NAME_None;` — Name used to look up or create the destination triangle-label attribute on the target mesh.

#### class `UE::Geometry::FTransferAttributes`  
`class UE_EXPERIMENTAL(5.8, "Generic attribute transfer is experimental while under active development.") FTransferAttributes`  
_L429-630_
- L440 _public prototype_ `FTransferAttributes(const FDynamicMesh3* InSourceMesh, const FDynamicMeshAABBTree3* InSourceBVH = nullptr);` — Constructs the operator with a mandatory source mesh and an optional pre-built BVH. Providing a BVH is an optimization when the same source mesh is used for multiple targets. @param InSourceMesh  The mesh whose attributes will be sampled. Must outlive this object. @param InSourceBVH   Optional pre-built spatial acceleration structure for InSourceMesh. If null, an internal BVH is constructed on the first transfer call.
- L442 _public prototype_ `virtual ~FTransferAttributes();`
- L448 _public prototype_ `virtual EOperationValidationResult Validate();` — Validates that all required inputs are set before running the transfer. @return EOperationValidationResult::Ok if the operator is ready to run.
- L457 _public prototype_ `virtual bool TransferAttributesToMesh(FDynamicMesh3& InOutTargetMesh);` — Executes the configured attribute transfer, writing results into InOutTargetMesh. All registered vertex and triangle proxies are applied in order. @param InOutTargetMesh  The mesh to receive the transferred attributes. @return true on success, false if the operation was cancelled or an error occurred.
- L465 _public function_ `template<typename T, typename... ArgTypes> void AddVertexProxy(ArgTypes&&... Args)` — Constructs a vertex proxy of type T in-place at the end of VertexProxies. @tparam T        One of the types contained in FVertexProxy (e.g. FSkinWeightsProxy). @param Args      Constructor arguments forwarded to T.
- L477 _public function_ `template<typename T, typename... ArgTypes> void AddTriangleProxy(ArgTypes&&... Args)` — Constructs a triangle proxy of type T in-place at the end of TriangleProxies. @tparam T        One of the types contained in FTriangleProxy (e.g. FPolygroupProxy). @param Args      Constructor arguments forwarded to T.
- L485 _private member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel the running operation.
- L488 _private member_ `bool bUseParallel = true;` — Enable/disable multi-threading.
- L491 _private member_ `FTransformSRT3d TargetToWorld = FTransformSRT3d::Identity();` — Transform applied to the input target mesh or target point before transfer.
- L506 _private member_ `ETransferMethod TransferMethod = ETransferMethod::ClosestPointOnSurface;` — The transfer method to transfer data.
- L509 _private member_ `double SearchRadius = -1;` — Radius for searching the closest point. If negative, all points are considered.
- L515 _private member_ `double NormalThreshold = -1;` — Maximum angle (in radians) difference between target and source point normals to be considered a match. If negative, normals are ignored.
- L522 _private member_ `bool LayeredMeshSupport = false;` — If true, when the closest point doesn't pass the normal threshold test, will try again with a flipped normal. This helps with layered meshes where the "inner" and "outer" layers are close to each other but whose normals are pointing in the opposite directions.
- L525 _private member_ `int32 NumSmoothingIterations = 0;` — The number of optional post-processing smoothing iterations applied to the vertices without the match.
- L528 _private member_ `float SmoothingStrength = 0.0f;` — The strength of each post-processing smoothing iteration.
- L531 _private member_ `bool bUseIntrinsicLaplacian = false;` — If true, will use the intrinsic Delaunay mesh to construct sparse Cotangent Laplacian matrix.
- L540 _private member_ `TArray<float> ForceInpaint;` — Optional mask where if ForceInpaint[VertexID] != 0 we want to force the colors for the vertex to be computed automatically. @note Only used when TransferMethod == ETransferMethod::Inpaint. The size must be equal to the InTargetMesh.MaxVertexID(), otherwise the mask is ignored.
- L546 _private member_ `TArray<int32> TargetVerticesSubset;` — Optional subset of target mesh vertices to transfer weights to. If left empty, skin weights will be transferred to all target mesh vertices.
- L549 _private member_ `TArray<FVertexProxy> VertexProxies;` — Ordered list of vertex-level attribute proxies (skin weights, morph targets) to be applied during transfer.
- L555 _private member_ `TArray<int32> TargetTrianglesSubset;` — Optional subset of target mesh triangles to consider during triangle-level attribute transfer. If empty, all triangles in the target mesh are processed.
- L558 _private member_ `TArray<FTriangleProxy> TriangleProxies;` — Ordered list of triangle-level attribute proxies (polygroups, triangle labels) to be applied during transfer.
- L561 _private member_ `TBitArray<> MatchedVertices;` — Output bitmask: MatchedVertices[VertexID] is true for every target VERTICES whose closest source triangle was found.
- L564 _private member_ `TBitArray<> MatchedTriangles;` — Output bitmask: MatchedTriangles[TriangleID] is true for every target triangle whose closest source triangle was found.
- L567 _private member_ `const FDynamicMesh3* SourceMesh = nullptr;` — Source mesh we are transferring colors from.
- L573 _private member_ `const FDynamicMeshAABBTree3* SourceBVH = nullptr;` — The caller can optionally specify the source mesh BVH in case this operator is run on multiple target meshes while the source mesh remains the same. Otherwise BVH tree will be computed.
- L576 _private member_ `TUniquePtr<FDynamicMeshAABBTree3> InternalSourceBVH;` — If the caller doesn't pass BVH for the source mesh then we compute one.
- L579 _private member_ `TUniquePtr<FMeshNormals> InternalSourceMeshNormals;` — If the source mesh doesn't have per-vertex normals then compute them
- L589 _private prototype_ `FClosestSample GetClosestSample(const FVector3d& InPoint, const FVector3f& InNormal = FVector3f::Zero()) const;` — Returns the closest point on the source mesh surface to InPoint, filtered by InNormal when NormalThreshold >= 0. The result triangle ID is set to InvalidID when no match satisfies the configured constraints. @param InPoint   Query point in world space. @param InNormal  Query normal used for the normal-angle filter. Pass FVector3f::Zero() to skip normal filtering. @return FClosestSample with the enclosing triangle ID and barycentric coordinates, or InvalidID if no match.
- L592 _private prototype_ `bool Cancelled();` — @return if true, abort the computation.
- L600 _private prototype_ `bool FindClosestPointOnSourceSurface(const FVector3d& InPoint, const FTransformSRT3d& InToWorld, int32& OutTriID, FVector3d& OutBary) const;` — Find the closest point on the surface of the source mesh and return the ID of the triangle containing it and its barycentric coordinates. @return true if point is found, false otherwise
- L610 _private prototype_ `bool TransferUsingClosestPoint(FDynamicMesh3& InOutTargetMesh, const TUniquePtr<FMeshNormals>& InTargetMeshNormals);` — Drives the full closest-point transfer: processes both vertex proxies and triangle proxies. Called internally by TransferAttributesToMesh when TransferMethod == ClosestPointOnSurface. @param InOutTargetMesh          Mesh being modified. @param InTargetMeshNormals      Per-vertex normals for the target mesh, used for normal-angle filtering. @return false if the operation was cancelled, true otherwise.
- L620 _private prototype_ `int32 TransferVerticesUsingClosestPoint(FDynamicMesh3& InOutTargetMesh, const TUniquePtr<FMeshNormals>& InTargetMeshNormals);` — Iterates over target vertices (or TargetVerticesSubset), finds the closest source surface point for each, and dispatches to all registered vertex proxies. @param InOutTargetMesh          Mesh being modified; vertex attributes are written here. @param InTargetMeshNormals      Per-vertex normals for the target mesh used in normal filtering. @return Number of target vertices that were successfully matched to a source surface point.
- L629 _private prototype_ `int32 TransferTrianglesUsingClosestPoint(FDynamicMesh3& InOutTargetMesh);` — Iterates over target triangles (or TargetTrianglesSubset), finds the closest source triangle for each, and dispatches to all registered triangle proxies. @param InOutTargetMesh  Mesh being modified; triangle attributes are written here. @return Number of target triangles that were successfully matched to a source triangle.

#### enum `UE::Geometry::FTransferAttributes::ETransferMethod`  
`enum class ETransferMethod : uint8`  
_L493-503_
- L498 _public enumerator_ `ClosestPointOnSurface = 0` — For every vertex on the target mesh, find the closest point on the surface of the source mesh. If that point is within the SearchRadius, and their normals differ by less than the NormalThreshold, then we directly copy the weights from the source point to the target mesh vertex.
- L502 _public enumerator_ `Inpaint = 1` — Same as the ClosestPointOnSurface but for all the vertices we didn't copy the weights directly, automatically compute the smooth weights.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)
- L20 _typedef_ `template<typename MeshType> class TMeshAABBTree3;` (scope `UE::Geometry`)
- L25 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Geometry` (scope `UE`)
- L281 _typedef_ `using FVertexProxy = TVariant< FSkinWeightsProxy, FMorphTargetProxy >;` (scope `UE::Geometry`) — Variant holding any per-vertex attribute proxy. FTransferAttributes stores an array of these to dispatch transfers across different attribute types without virtual dispatch.
- L411 _typedef_ `using FTriangleProxy = TVariant< FPolygroupProxy, FTriangleLabelProxy >;` (scope `UE::Geometry`) — Variant holding any per-triangle attribute proxy. FTransferAttributes stores an array of these to dispatch transfers across different attribute types without virtual dispatch.
