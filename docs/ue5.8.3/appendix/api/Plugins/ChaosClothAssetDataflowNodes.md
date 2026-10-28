# Plugins / ChaosClothAssetDataflowNodes

- module root: `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes`
- headers: 92; symbols: 1618
- symbol kinds: class=10, delegate=1, enum=25, enumerator=75, function=68, macro=14, member=807, namespace=61, prototype=423, struct=130, typedef=4
- PrivateDependencyModuleNames: AnimationCore, AssetTools, ChaosCaching, ChaosCloth, ChaosClothAsset, ChaosClothAssetEngine, ChaosClothAssetTools, ClothingSystemRuntimeCommon, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowNodes, DetailCustomizations, DynamicMesh, Engine, GeometryCore, GeometryFramework, InputCore, MeshConversion, MeshConversionEngineTypes, MeshDescription, MeshUtilitiesCommon, ModelingComponents, ModelingOperators, ModelingOperatorsEditorOnly, RenderCore, SkeletalMeshDescription, Slate, SlateCore, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: Core, MeshResizingCore

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Internal/ChaosClothAsset/ClothDataflowTools.h` (Internal)


#### struct `UE::Chaos::ClothAsset::FClothDataflowTools`  
`struct FClothDataflowTools`  
_L31-129_
- desc: Tools shared by cloth dataflow nodes
- L33 _public prototype_ `static void AddRenderPatternFromSkeletalMeshSection(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FSkeletalMeshLODModel& SkeletalMeshModel, const int32 SectionIndex, const FSoftObjectPath& RenderMaterialPathName);`
- L35 _public prototype_ `static void AddSimPatternsFromSkeletalMeshSection(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FSkeletalMeshLODModel& SkeletalMeshModel, const int32 SectionIndex, const int32 UVChannelIndex, const FVector2f& UVScale, bool bImportNormals = false, TArray<int32>* OutSim2DToSourceVertex = nullptr);`
- L37 _public prototype_ `static void LogAndToastWarning(const FDataflowNode& DataflowNode, const FText& Headline, const FText& Details);`
- L47 _public prototype_ `static bool MakeCollectionName(FString& InOutString);` — Turn a string into a valid collection group or attribute name. The resulting name won't contains spaces and any other special characters as listed in INVALID_OBJECTNAME_CHARACTERS (currently "',/.:|&!~\n\r\t@#(){}[]=;^%$`). It will also have all leading underscore removed, as these names are reserved for internal use. @param InOutString The string to turn into a valid collection name. @return Whether the InOutString was already a valid collection name.
- L49 _public prototype_ `static bool BuildSkeletalMeshModelFromMeshDescription(const FMeshDescription* const InMeshDescription, const FMeshBuildSettings& InBuildSettings, FSkeletalMeshLODModel& SkeletalMeshModel);`
- L53 _public function_ `template<typename T = FDataflowNode> static T* GetPropertyOwnerDataflowNode(const TSharedPtr<IPropertyHandle>& PropertyHandle)` — Return the Dataflow node owning by this property, and cast it to the desired node type.
- L78 _public prototype_ `template<typename T UE_REQUIRES(std::is_same_v<T, TArray<int32>> || std::is_same_v<T, TSet<int32>>)> static TArray<int32> GetOriginalToNewIndices(const TConstArrayView<T>& NewToOriginals, int32 NumOriginalIndices);` — Returns the inverse mapping from a reduced set of original indices to the new indices.
- L81 _public prototype_ `static bool RemoveDegenerateTriangles( const TArray<FIntVector3>& TriangleToVertexIndex, const TArray<FVector2f>& RestPositions2D, const TArray<FVector3f>& DrapedPositions3D, TArray<FIntVector3>& OutTriangleToVertexIndex, TArray<FVector2f>& OutRestPositions2D, TArray<FVector3f>& OutDrapedPositions3D, TArray<int32>& OutIndices);` — `UE_DEPRECATED(5.6, "Use FSimMeshCleanup instead.")`
- L91 _public function_ `static bool RemoveDuplicateTriangles(TArray<FIntVector3>& TriangleToVertexIndex)` — `UE_DEPRECATED(5.6, "Use FSimMeshCleanup instead.")`
- L99 _public prototype_ `static bool RemoveDuplicateStitches(TArray<TArray<FIntVector2>>& SeamStitches);`
- L104 _public prototype_ `static void SetGroupResizingData(const TSharedRef<FManagedArrayCollection>& ClothCollection, const TConstArrayView<FName>& SetNames, const TConstArrayView<int32>& SetTypes);` — Set Group Resizing data from supplied sets and types.
- L109 _public prototype_ `static void GenerateSimMeshResizingGroupData(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FMeshDescription& SourceMesh, TArray<FMeshResizingCustomRegion>& OutResizingGroupData);` — Generate FMeshResizingCustomRegion data from Sim Mesh Group Resizing data
- L114 _public prototype_ `static void GenerateRenderMeshResizingGroupData(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FMeshDescription& SourceMesh, TArray<FMeshResizingCustomRegion>& OutResizingGroupData);` — Generate FMeshResizingCustomRegion data from Render Mesh Group Resizing data
- L119 _public prototype_ `static void ApplySimGroupResizing(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FMeshDescription& TargetMesh, const FMeshResizingRBFInterpolationData& InterpolationData, const TArray<FMeshResizingCustomRegion>& ResizingGroupData);` — Apply Group Resizing to the sim mesh.
- L124 _public prototype_ `static void ApplyRenderGroupResizing(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FMeshDescription& TargetMesh, const FMeshResizingRBFInterpolationData& InterpolationData, const TArray<FMeshResizingCustomRegion>& ResizingGroupData);` — Apply Group Resizing to the render mesh.
- L128 _private prototype_ `static FDataflowNode* GetPropertyOwnerDataflowNode(const TSharedPtr<IPropertyHandle>& PropertyHandle, const UStruct* DataflowNodeStruct);` — Return the Dataflow node owning by this property.

#### struct `UE::Chaos::ClothAsset::FClothDataflowTools::FSimMeshCleanup`  
`struct FSimMeshCleanup`  
_L59-74_
- desc: Simulation mesh cleanup tools.
- L61 _public member_ `TArray<FIntVector3> TriangleToVertexIndex;`
- L62 _public member_ `TArray<FVector2f> RestPositions2D;`
- L63 _public member_ `TArray<FVector3f> DrapedPositions3D;`
- L64 _public member_ `TArray<TSet<int32>> OriginalTriangles;` — New to original face index lookup
- L65 _public member_ `TArray<TSet<int32>> OriginalVertices;` — New to original vertex index lookup
- L67 _public prototype_ `FSimMeshCleanup( const TArray<FIntVector3>& InTriangleToVertexIndex, const TArray<FVector2f>& InRestPositions2D, const TArray<FVector3f>& InDrapedPositions3D);`
- L72 _public prototype_ `bool RemoveDegenerateTriangles();`
- L73 _public prototype_ `bool RemoveDuplicateTriangles();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSCLOTHASSETDATAFLOWNODES_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Dataflow` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Chaos` (scope `UE`)
- L26 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L132 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothAssetDataflowNodes, Log, All);`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Internal/ChaosClothAsset/ReferenceBoneNode.h` (Internal)


#### struct `FChaosClothAssetReferenceBoneSelection`  
`struct FChaosClothAssetReferenceBoneSelection`  
_L15-21_
- reflection: `USTRUCT()`
- desc: The managed array collection group used in the selection. This separate structure is required to allow for customization of the UI.
- L20 _public member_ `FName Name = "";` — `UPROPERTY(EditAnywhere, Category = "Bone Name")`

#### struct `FChaosClothAssetReferenceBoneNode`  
`struct FChaosClothAssetReferenceBoneNode : public FDataflowNode`  
_L27-50_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Explicitly set the cloth Reference Bone (used when calculating SimulationVelocityScale). This will automatically computed as the bone closest to the root with weights if no valid Reference Bone is explicitly set. Reference bones are shared by all LODs. Only the bones set for LOD0 will be used.
- L38 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L39 _private prototype_ `void OnCalculateDefaultReferenceBone(UE::Dataflow::FContext& Context);`
- L42 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L46 _private member_ `FChaosClothAssetReferenceBoneSelection ReferenceBone;` — `UPROPERTY(EditAnywhere, Category = "Simulation Reference Bone Selection")` — Select the cloth reference bone. This will automatically computed as the bone closest to the root with weights if no valid Reference Bone is explicitly set.
- L49 _private member_ `FDataflowFunctionProperty CalculateDefaultReferenceBone;` — `UPROPERTY(EditAnywhere, Transient, Category = "Simulation Reference Bone Selection", Meta = (DisplayName = "Calculate Default"))`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Internal/ChaosClothAsset/RenderMeshImport.h` (Internal)


#### struct `UE::Chaos::ClothAsset::FRenderMeshImport`  
`struct FRenderMeshImport`  
_L22-68_
- desc: Render mesh import from mesh description.
- L48 _public member_ `TSortedMap<int32, FSection> Sections;`
- L50 _public prototype_ `FRenderMeshImport(const FMeshDescription& InMeshDescription, const FMeshBuildSettings& BuildSettings);`
- L52 _public prototype_ `void AddRenderSections( const TSharedRef<FManagedArrayCollection> ClothCollection, const TArray<FStaticMaterial>& Materials, const FName OriginalTrianglesName, const FName OriginalVerticesName);`
- L58 _public prototype_ `void AddRenderSections( const TSharedRef<FManagedArrayCollection> ClothCollection, const TArray<FSoftObjectPath>& Materials, const FName OriginalTrianglesName, const FName OriginalVerticesName);`
- L64 _public prototype_ `void AddRenderPatternSelectionSets( const TSharedRef<FManagedArrayCollection> ClothCollection, const TMap<FName, TSet<int32>>& PatternNamesToIndices, const FName OriginalTrianglesName);`

#### struct `UE::Chaos::ClothAsset::FRenderMeshImport::FVertex`  
`struct FVertex`  
_L24-33_
- L26 _public member_ `FVector3f RenderPosition;`
- L27 _public member_ `FVector3f RenderNormal;`
- L28 _public member_ `FVector3f RenderTangentU;`
- L29 _public member_ `FVector3f RenderTangentV;`
- L30 _public member_ `TArray<FVector2f> RenderUVs;`
- L31 _public member_ `FLinearColor RenderColor;`
- L32 _public member_ `int32 OriginalIndex;`

#### struct `UE::Chaos::ClothAsset::FRenderMeshImport::FTriangle`  
`struct FTriangle`  
_L35-40_
- L37 _public member_ `FIntVector3 VertexIndices;`
- L38 _public member_ `int32 OriginalIndex;`
- L39 _public member_ `int32 MaterialIndex;`

#### struct `UE::Chaos::ClothAsset::FRenderMeshImport::FSection`  
`struct FSection`  
_L42-47_
- L44 _public member_ `TArray<FVertex> Vertices;`
- L45 _public member_ `TArray<FTriangle> Triangles;`
- L46 _public member_ `int32 NumTexCoords;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSCLOTHASSETDATAFLOWNODES_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Chaos` (scope `UE`)
- L17 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/ClothDataflowViewModes.h` (Private)


#### class `UE::Chaos::ClothAsset::FCloth2DSimViewMode`  
`class FCloth2DSimViewMode : public UE::Dataflow::FDataflowConstruction2DViewModeBase`  
_L9-19_
- inherits: `UE::Dataflow::FDataflowConstruction2DViewModeBase`
- L12 _public member_ `static const FName Name;`
- L13 _public prototype_ `virtual ~FCloth2DSimViewMode() = default;`
- L15 _private prototype_ `virtual FName GetName() const override;`
- L16 _private prototype_ `virtual FText GetButtonText() const override;`
- L17 _private prototype_ `virtual FText GetTooltipText() const override;`
- L18 _private prototype_ `virtual FRotator GetViewportOrientation() const override;`

#### class `UE::Chaos::ClothAsset::FCloth3DSimViewMode`  
`class FCloth3DSimViewMode : public UE::Dataflow::FDataflowConstruction3DViewModeBase`  
_L21-31_
- inherits: `UE::Dataflow::FDataflowConstruction3DViewModeBase`
- L24 _public member_ `static const FName Name;`
- L25 _public prototype_ `virtual ~FCloth3DSimViewMode() = default;`
- L27 _private prototype_ `virtual FName GetName() const override;`
- L28 _private prototype_ `virtual FText GetButtonText() const override;`
- L29 _private prototype_ `virtual FText GetTooltipText() const override;`
- L30 _private function_ `virtual bool CanDisplayGizmo() const`

#### class `UE::Chaos::ClothAsset::FClothRenderViewMode`  
`class FClothRenderViewMode : public UE::Dataflow::FDataflowConstruction3DViewMode`  
_L33-43_
- inherits: `UE::Dataflow::FDataflowConstruction3DViewMode`
- L36 _public member_ `static const FName Name;`
- L37 _public prototype_ `virtual ~FClothRenderViewMode() = default;`
- L39 _private prototype_ `virtual FName GetName() const override;`
- L40 _private prototype_ `virtual FText GetButtonText() const override;`
- L41 _private prototype_ `virtual FText GetTooltipText() const override;`
- L42 _private function_ `virtual bool CanDisplayGizmo() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/ClothRenderableTypes.h` (Private)


#### class `UDataflowClothSimRenderSettings`  
`class UDataflowClothSimRenderSettings : public UDataflowRenderableTypeSettings`  
_L10-42_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "Cloth")`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _public member_ `bool bShowSeams = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth")` — display the seams between patterns
- L21 _public member_ `bool bCollapseSeamLines = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth", meta = (EditCondition = bShowSeams))` — when seams are displayed, collapse the multiple seams lines into one
- L25 _public member_ `bool bShowSeamPoints = true;` — `UPROPERTY(EditAnywhere, Category = "Cloth", meta = (EditCondition = bShowSeams))` — Whether to show the seam points or not
- L29 _public member_ `float SeamPointSize = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Cloth", meta = (UIMin = 0.01, ClampMin = 0.01, EditCondition = "bShowSeams && bShowSeamPoints"))` — Size of the seam points
- L33 _public member_ `bool bShowSeamLines = true;` — `UPROPERTY(EditAnywhere, Category = "Cloth", meta = (EditCondition = bShowSeams))` — Whether to show the seam lines or not
- L37 _public member_ `float SeamLineThickness = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Cloth", meta = (UIMin = 0.01, ClampMin = 0.01, EditCondition = "bShowSeams && bShowSeamLines"))` — Thickness of the seam lines
- L41 _public member_ `bool bShowPatternColors = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth")` — display the patterns colors

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Chaos` (scope `UE`)
- L44 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L46 _prototype_ `void RegisterClothRenderableTypes();` (scope `UE::Chaos::ClothAsset`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/ConnectableValueCustomization.h` (Private)


#### class `UE::Chaos::ClothAsset::FConnectableValueCustomization`  
`class FConnectableValueCustomization : public FImportedValueCustomization`  
_L13-40_
- inherits: `FImportedValueCustomization`
- desc: Customization for all connectable property that could be imported Works like a FMathStructCustomization.
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `FConnectableValueCustomization();`
- L23 _protected prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L30 _protected prototype_ `virtual void MakeHeaderRow(TSharedRef<class IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row) override;`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> MakeChildWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle) override;`
- L35 _protected prototype_ `static bool IsOverrideProperty(const TSharedPtr<IPropertyHandle>& Property);` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")`
- L37 _protected prototype_ `static bool IsOverridePropertyOf(const TSharedPtr<IPropertyHandle>& OverrideProperty, const TSharedPtr<IPropertyHandle>& Property);` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")`
- L38 _protected prototype_ `static bool BuildFabricMapsProperty(const TSharedPtr<IPropertyHandle>& Property);`
- L39 _protected prototype_ `static bool CouldUseFabricsProperty(const TSharedPtr<IPropertyHandle>& Property);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/ImportedValueCustomization.h` (Private)


#### class `UE::Chaos::ClothAsset::FImportedValueCustomization`  
`class FImportedValueCustomization : public FMathStructCustomization`  
_L15-34_
- inherits: `FMathStructCustomization`
- desc: Customization for all base property that could be imported Works like a FMathStructCustomization.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `FImportedValueCustomization();`
- L24 _protected prototype_ `virtual void MakeHeaderRow(TSharedRef<class IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row) override;`
- L25 _protected prototype_ `virtual TSharedRef<SWidget> MakeChildWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle) override;`
- L28 _protected prototype_ `static void AddToggledCheckBox(const TSharedRef<IPropertyHandle>& PropertyHandle, const TSharedPtr<SHorizontalBox>& HorizontalBox, const FSlateBrush* SlateBrush);` — Add a toggled check box to the horizontal one
- L31 _private prototype_ `TOptional<float> GetAxisValue(TSharedRef<IPropertyHandle> InPropertyHandle, EAxis::Type InAxis) const;`
- L32 _private prototype_ `void CommitAxisValue(float InNewValue, ETextCommit::Type CommitInfo, TSharedRef<IPropertyHandle> InPropertyHandle, EAxis::Type InAxis) const;`
- L33 _private prototype_ `void ChangeAxisValue(float InNewValue, TSharedRef<IPropertyHandle> InPropertyHandle, EAxis::Type InAxis) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/MakeClothAssetNode.h` (Private)


#### struct `FChaosClothAssetMakeClothAssetNode`  
`struct FChaosClothAssetMakeClothAssetNode : public FDataflowNode`  
_L14-50_
- reflection: `USTRUCT(Meta = (Experimental, DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Cloth terminal node to generate a cloth asset from a cloth collection.
- L24 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L25 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L26 _private function_ `virtual bool CanAddPin() const override`
- L27 _private function_ `virtual bool CanRemovePin() const override`
- L28 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L29 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L30 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L33 _private prototype_ `TArray<TSharedRef<const FManagedArrayCollection>> GetCleanedCollectionLodValues(UE::Dataflow::FContext& Context) const;`
- L34 _private prototype_ `UE::Dataflow::TConnectionReference<FManagedArrayCollection> GetConnectionReference(int32 Index) const;`
- L38 _private member_ `TArray<FManagedArrayCollection> CollectionLodsArray;` — `UPROPERTY(Meta = (DataflowInput))` — Input cloth collections for this LOD -- Array connection. Individual CollectionLods will be ignored if there is a CollectionLodsArray connection.
- L42 _private member_ `TArray<FManagedArrayCollection> CollectionLods;` — `UPROPERTY()` — Input cloth collection for this LOD. Individual CollectionLods will be ignored if there is a CollectionLodsArray connection.
- L46 _private member_ `TObjectPtr<const UChaosClothAsset> ClothAsset;` — `UPROPERTY(Meta = (DataflowOutput))` — The cloth asset output.
- L48 _private member_ `static constexpr int32 NumRequiredInputs = 1;`
- L49 _private member_ `static constexpr int32 NumInitialCollectionLods = 1;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/SelectionGroupCustomization.h` (Private)


#### class `UE::Chaos::ClothAsset::FSelectionGroupCustomization`  
`class FSelectionGroupCustomization : public UE::Dataflow::FPropertyGroupCustomization`  
_L12-21_
- inherits: `UE::Dataflow::FPropertyGroupCustomization`
- desc: Customization for selection node group names input.
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _private prototype_ `virtual TArray<FName> GetTargetGroupNames(const FManagedArrayCollection& Collection) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/SimAccessoryMeshNode.h` (Private)


#### struct `FChaosClothAssetSimAccessoryMeshNode`  
`struct FChaosClothAssetSimAccessoryMeshNode : public FDataflowNode`  
_L12-47_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Add a SimAccessoryMesh by converting a cloth collection into an accessory mesh and attaching it to an existing cloth collection. Any unmatched vertices will use the existing cloth collection's sim mesh data to populate the accessory mesh data
- L23 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L25 _private function_ `virtual bool CanDebugDraw() const override`
- L29 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L30 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L35 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L38 _private member_ `FManagedArrayCollection SimAccessoryMeshCollection;` — `UPROPERTY(Meta = (DataflowInput))`
- L42 _private member_ `FString AccessoryMeshName = TEXT("Acc` — `UPROPERTY(EditAnywhere, Category = "Sim Accessory Mesh", Meta = (DataflowOutput))` — Name of the new accessory mesh
- L46 _private member_ `bool bUseSimImportVertexID = true;` — `UPROPERTY(EditAnywhere, Category = "Sim Accessory Mesh")` — Use SimImportVertexID (e.g., imported vertex ID from an FBX->SKM->ClothCollection conversion) to match vertices

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/SimulationBaseConfigNodePrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTY(Property) \` — Macro for adding and setting value properties from inside AddProperties()
- L16 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYBOOL(Property) \` — Macro for adding and setting boolean value properties from inside AddProperties()
- L21 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYENUM(Property) \` — Macro for adding and setting enum value as int32 properties from inside AddProperties()
- L26 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYSTRING(Property) \` — Macro for adding and setting string value from inside AddProperties()
- L31 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYCHECKED1(Property, SimilarProperty1) \` — Macro for adding and setting weighted value properties from inside AddProperties() and check for a similar property being overriden.
- L37 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYCHECKED2(Property, SimilarProperty1, SimilarProperty2) \` — Macro for adding and setting weighted value properties from inside AddProperties() and check for two similar properties being overriden.
- L43 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYENUMCHECKED2(Property, SimilarProperty1, SimilarProperty2) \` — Macro for adding and setting enum value as int32 properties from inside AddProperties() and check for two similar properties being overriden.
- L49 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYWEIGHTED(Property) \` — Macro for adding and setting weighted value properties from inside AddProperties()
- L57 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYWEIGHTEDCHECKED1(Property, SimilarProperty1) \` — Macro for adding and setting weighted value properties from inside AddProperties() and check for a similar property being overriden.
- L66 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYWEIGHTEDCHECKED2(Property, SimilarProperty1, SimilarProperty2) \` — Macro for adding and setting weighted value properties from inside AddProperties() and check for two similar properties being overriden.
- L75 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYWEIGHTEDCHECKED3(Property, SimilarProperty1, SimilarProperty2, SimilarProperty3) \` — Macro for adding and setting weighted value properties from inside AddProperties() and check for three similar properties being overriden.
- L84 _macro_ `#define UE_CHAOS_CLOTHASSET_SIMULATIONCONFIG_SETPROPERTYWEIGHTEDCHECKED4(Property, SimilarProperty1, SimilarProperty2, SimilarProperty3, SimilarProperty4) \` — Macro for adding and setting weighted value properties from inside AddProperties() and check for four similar properties being overriden.

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Private/ChaosClothAsset/WeightedValueCustomization.h` (Private)


#### class `UE::Chaos::ClothAsset::FWeightedValueCustomization`  
`class FWeightedValueCustomization : public FConnectableValueCustomization`  
_L16-58_
- inherits: `FConnectableValueCustomization`
- desc: Customization for all property that also uses weight maps. Works like a FMathStructCustomization with the difference that the structure member short names are displayed in the header's row.
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _public prototype_ `FWeightedValueCustomization();`
- L27 _protected function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)`
- L38 _protected prototype_ `virtual void MakeHeaderRow(TSharedRef<class IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row) override;`
- L39 _protected prototype_ `virtual TSharedRef<SWidget> MakeChildWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle) override;`
- L43 _private prototype_ `static void ExtractFloatMetadata( TSharedRef<IPropertyHandle>& PropertyHandle, TOptional<float>& MinValue, TOptional<float>& MaxValue, TOptional<float>& SliderMinValue, TOptional<float>& SliderMaxValue, float& SliderExponent, float& Delta, float& ShiftMultiplier, float& CtrlMultiplier, bool& SupportDynamicSliderMaxValue, bool& SupportDynamicSliderMinValue);`
- L55 _private prototype_ `TSharedRef<SWidget> MakeFloatWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle);`
- L56 _private prototype_ `void OnDynamicSliderMaxValueChanged(float NewMaxSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfHigher);`
- L57 _private prototype_ `void OnDynamicSliderMinValueChanged(float NewMinSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfLower);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/AddStitchNode.h` (Public)


#### struct `FChaosClothAssetAddStitchNode`  
`struct FChaosClothAssetAddStitchNode : public FDataflowNode`  
_L13-30_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- L21 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L25 _public member_ `FChaosClothAssetConnectableIStringValue MergeToSingleVertexSelection;` — `UPROPERTY(EditAnywhere, Category = "Add Stitch")` — Set of vertices to stitch together. Can be 2D or 3D vertices. A seam will be created by making a chain of stitches (all vertices will merge to a single 3D vertex).
- L27 _public prototype_ `FChaosClothAssetAddStitchNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/AddWeightMapNode.h` (Public)


#### enum `EChaosClothAssetWeightMapTransferType`  
`enum class EChaosClothAssetWeightMapTransferType : uint8`  
_L13-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `Use2DSimMesh UMETA(DisplayName = "Use 2D Sim Mesh")` — Transfer weight maps from the 2D simulation mesh (pattern against pattern).
- L18 _public enumerator_ `Use3DSimMesh UMETA(DisplayName = "Use 3D Sim Mesh")` — Transfer weight maps from the 3D simulation mesh (rest mesh against rest mesh).
- L20 _public enumerator_ `UseRenderMesh UMETA(DisplayName = "Use Render Mesh")` — Transfer weight maps from the 3D render mesh into the sim mesh using spatial (BVH) mapping. Use this when the source collection contains an imported render mesh with painted weight maps.

#### enum `EChaosClothAssetWeightMapMeshType`  
`enum class EChaosClothAssetWeightMapMeshType : uint8`  
_L25-30_
- reflection: `UENUM()`
- desc: Which mesh to update with the corresponding weight map
- L27 _public enumerator_ `Simulation`
- L28 _public enumerator_ `Render`
- L29 _public enumerator_ `Both`

#### enum `EChaosClothAssetWeightMapOverrideType`  
`enum class EChaosClothAssetWeightMapOverrideType : uint8`  
_L34-42_
- reflection: `UENUM()`
- desc: How the map stored on the AddWeightMapNode should be applied to an existing map. If no map exists, it is treated as zero.
- L37 _public enumerator_ `ReplaceAll` — The full map is stored and reapplied.
- L39 _public enumerator_ `ReplaceChanged` — Only changed values are stored and reapplied.
- L41 _public enumerator_ `Add` — Add values.

#### struct `FChaosClothAssetAddWeightMapNode`  
`struct UE_DEPRECATED(5.5, "Use FChaosClothAssetWeightMapNode instead.") FChaosClothAssetAddWeightMapNode : public FDataflowTerminalNode`  
_L51-133_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated="5.5"))`
- inherits: `FDataflowTerminalNode`
- desc: Painted weight map attributes node. Deprecated, use FChaosClothAssetWeightMapNode instead.
- L57 _public member_ `static constexpr float ReplaceChangedPassthroughValue = UE_BIG_NUMBER;`
- L60 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L70 _public member_ `FManagedArrayCollection TransferCollection;` — `UPROPERTY(VisibleAnywhere, Category = "Add Weight Map", Meta = (DataflowInput))` — The collection used to transfer weight map from. Connecting a collection containing a weight map with Input Name (or Name if Input Name is empty) will transfer the weights to the input collection vertices. Note this operation only happens once when the TransferCollection is first connected, or updated. Changing the InputName or the TransferType will also redo the transfer operation.
- L74 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Add Weight Map", Meta = (DataflowOutput))` — The name to be set as a weight map attribute.
- L78 _public member_ `FChaosClothAssetConnectableIStringValue InputName = {TEXT("")};` — `UPROPERTY(VisibleAnywhere, Category = "Add Weight Map")` — The name to populate this map from and override based on Map Override Type. Name will be used if Input Name is empty.
- L83 _public member_ `EChaosClothAssetWeightMapOverrideType MapOverrideType = EChaosClothAssetWeightMapOverrideType::ReplaceAll;` — `UPROPERTY(VisibleAnywhere, Category = "Add Weight Map")` — How to apply this node's weight values onto existing maps. Changing this value will change the output map. To change how the node's stored weights are calculated, change the equivalent value on the Weight Map Paint Tool context.
- L90 _public member_ `EChaosClothAssetWeightMapTransferType TransferType = EChaosClothAssetWeightMapTransferType::Use2DSimMesh;` — `UPROPERTY(VisibleAnywhere, Category = "Add Weight Map", Meta = (EditCondition = "TransferCollectionHash != 0"))` — The type of transfer used to transfer the weight map when a TransferCollection is connected. This property is disabled when no TransferCollection input has been conencted.
- L94 _public member_ `TArray<float> VertexWeights;` — `UE_DEPRECATED(5.4, "This property will be made private.")` — `UPROPERTY()`
- L97 _public member_ `EChaosClothAssetWeightMapMeshType MeshTarget = EChaosClothAssetWeightMapMeshType::Simulation;` — `UPROPERTY(VisibleAnywhere, Category = "Add Weight Map")`
- L99 _public prototype_ `FChaosClothAssetAddWeightMapNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L105 _private prototype_ `static TUniquePtr<class FToolCommandChange> MakeWeightMapNodeChange(const FChaosClothAssetAddWeightMapNode& Node);`
- L107 _private function_ `const TArray<float>& GetVertexWeights() const`
- L108 _private function_ `TArray<float>& GetVertexWeights()`
- L110 _private function_ `const TArray<float>& GetRenderVertexWeights() const`
- L111 _private function_ `TArray<float>& GetRenderVertexWeights()`
- L114 _private member_ `TArray<float> RenderVertexWeights;` — `UPROPERTY()`
- L117 _private prototype_ `FName GetInputName(UE::Dataflow::FContext& Context) const;` — These methods are exported for UClothEditorWeightMapPaintTool which lives in a different module.
- L119 _private prototype_ `void SetVertexWeights(const TConstArrayView<float> InputMap, const TArray<float>& FinalValues);`
- L120 _private prototype_ `void SetRenderVertexWeights(const TConstArrayView<float> InputMap, const TArray<float>& FinalValues);`
- L123 _private prototype_ `void CalculateFinalVertexWeightValues(const TConstArrayView<float> InputMap, TArrayView<float> FinalOutputMap) const;` — Input and FinalOutputMap can be the same array, but should not otherwise be interleaved.
- L124 _private prototype_ `void CalculateFinalRenderVertexWeightValues(const TConstArrayView<float> InputMap, TArrayView<float> FinalOutputMap) const;`
- L127 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L128 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L132 _private member_ `uint32 TransferCollectionHash = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ApplyProxyDeformerNode.h` (Public)


#### struct `FChaosClothAssetApplyProxyDeformerNode`  
`struct FChaosClothAssetApplyProxyDeformerNode final : public FDataflowNode`  
_L13-31_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Update the Render Mesh by applying any existing proxy deformer data. This node can be used to deform the render mesh after the sim mesh has changed after the proxy deformer data was calculated. It has no effect if there is no existing proxy deformer data, or if the sim or render mesh have not deformed since that data was calculated.
- L22 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L26 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Input/output collection
- L30 _private member_ `bool bIgnoreSkinningBlendWeights = false;` — `UPROPERTY(EditAnywhere, Category = "Apply Proxy Deformer")` — Ignore Skinning Blend Weights (apply proxy deformer to all points)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ApplyResizingNode.h` (Public)


#### struct `FChaosClothAssetApplyResizingNode`  
`struct FChaosClothAssetApplyResizingNode final : public FChaosClothAssetSimulationBaseConfigNode`  
_L14-59_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Apply resizing for a given Target Mesh.
- L24 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`
- L26 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L30 _private member_ `TObjectPtr<const USkeletalMesh> TargetSkeletalMesh;` — `UPROPERTY(meta = (DataflowInput))` — The target mesh that corresponds with the SourceMesh used to generate the InterpolationData. Must have matching vertices with SourceMesh
- L34 _private member_ `int32 SkeletalMeshLODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Resizing", meta = (DataflowInput, ClampMin = 0))` — Source and Target mesh LOD.
- L38 _private member_ `FMeshResizingRBFInterpolationData InterpolationData;` — `UPROPERTY(meta = (DataflowInput))` — The pre-calculated base RBF interpolation data.
- L42 _private member_ `bool bForceApplyToRenderMesh = false;` — `UPROPERTY(EditAnywhere, Category = "Resizing", meta = (DataflowInput))` — Force apply to the render mesh. Otherwise, the sim mesh will be resized if it exists, only resizing the render mesh if no sim mesh data exists.
- L46 _private member_ `TObjectPtr<const USkeletalMesh> SourceSkeletalMesh;` — `UPROPERTY(meta = (DataflowInput))` — The source mesh. Used for CustomResizingRegions. Must have matching vertices with TargetMesh
- L50 _private member_ `bool bSkipCustomRegionResizing = false;` — `UPROPERTY(EditAnywhere, Category = "Resizing", meta = (DataflowInput))` — Skip applying Custom Region Resizing data.
- L58 _private member_ `bool bSavePreResizedSimPosition3D = false;` — `UPROPERTY(EditAnywhere, Category = "Resizing", meta = (DataflowInput, DisplayName = "Save Pre-Resized Sim Position 3D"))` — Save pre-resized sim 3d vertices for scaling 2D rest length in XPBD anisotropic stretch constraints. IMPORTANT: Using Save Pre-Resized Sim Position 3D requires the following settings in SimulationStretchConfig node: Stretch Use 3d Rest Lengths: false Solver Type: XPBD Distribution Type: Anisotropic

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/AttributeNode.h` (Public)


#### struct `FChaosClothAssetNodeAttributeGroup`  
`struct FChaosClothAssetNodeAttributeGroup`  
_L17-23_
- reflection: `USTRUCT()`
- desc: The managed array collection group used for the attribute creation. This separate structure is required to allow for customization of the UI.
- L22 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Attribute Group")`

#### enum `EChaosClothAssetNodeAttributeType`  
`enum class EChaosClothAssetNodeAttributeType : uint8`  
_L26-31_
- reflection: `UENUM()`
- L28 _public enumerator_ `Integer`
- L29 _public enumerator_ `Float`
- L30 _public enumerator_ `Vector`

#### struct `FChaosClothAssetAttributeNode_v2`  
`struct FChaosClothAssetAttributeNode_v2 final : public FDataflowNode`  
_L35-75_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Create a new attribute for the specified group.
- L43 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L47 _public member_ `FChaosClothAssetConnectableIOStringValue Name;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — The name of the attribute to create.
- L51 _public member_ `FChaosClothAssetNodeAttributeGroup Group;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — The attribute group.
- L55 _public member_ `EChaosClothAssetNodeAttributeType Type = EChaosClothAssetNodeAttributeType::Integer;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — The attribute type.
- L59 _public member_ `int32 IntValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Attribute", Meta = (EditCondition = "Type == EChaosClothAssetNodeAttributeType::Integer", EditConditionHides))` — Default integer value.
- L63 _public member_ `float FloatValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Attribute", Meta = (EditCondition = "Type == EChaosClothAssetNodeAttributeType::Float", EditConditionHides))` — Default float value.
- L67 _public member_ `FVector3f VectorValue = FVector3f::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Attribute", Meta = (EditCondition = "Type == EChaosClothAssetNodeAttributeType::Vector", EditConditionHides))` — Default vector value.
- L69 _public prototype_ `FChaosClothAssetAttributeNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L73 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FChaosClothAssetAttributeNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetAttributeNode : public FDataflowNode`  
_L79-129_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Create a new attribute for the specified group.
- L87 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L91 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Attribute", Meta = (DataflowOutput))` — The name of the attribute to create.
- L95 _public member_ `FChaosClothAssetNodeAttributeGroup Group;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — The attribute group.
- L99 _public member_ `EChaosClothAssetNodeAttributeType Type = EChaosClothAssetNodeAttributeType::Integer;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — The attribute type.
- L103 _public member_ `int32 IntValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Attribute", Meta = (EditCondition = "Type == EChaosClothAssetNodeAttributeType::Integer", EditConditionHides))` — Default integer value.
- L107 _public member_ `float FloatValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Attribute", Meta = (EditCondition = "Type == EChaosClothAssetNodeAttributeType::Float", EditConditionHides))` — Default float value.
- L111 _public member_ `FVector3f VectorValue = FVector3f::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Attribute", Meta = (EditCondition = "Type == EChaosClothAssetNodeAttributeType::Vector", EditConditionHides))` — Default vector value.
- L113 _public prototype_ `FChaosClothAssetAttributeNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L117 _public function_ `const TArray<FName>& GetCachedCollectionGroupNames() const` — `UE_DEPRECATED(5.5, "This function is deprecated and will now return an empty array.")` — Return a cached array of all the groups used by the input collection during at the time of the latest evaluation.
- L121 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L123 _private function_ `virtual void OnSelected(UE::Dataflow::FContext& Context)` — `UE_DEPRECATED(5.5, "This function is deprecated and will not be called on selection/deselection.")`
- L125 _private function_ `virtual void OnDeselected()` — `UE_DEPRECATED(5.5, "This function is deprecated and will not be called on selection/deselection.")`
- L128 _private member_ `TArray<FName> CachedCollectionGroupNames;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/BindToRootBoneNode.h` (Public)


#### struct `FChaosClothAssetBindToRootBoneNode`  
`struct FChaosClothAssetBindToRootBoneNode : public FDataflowNode`  
_L13-34_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Bind an entire mesh to the single root bone of the current skeleton set on the cloth collection.
- L20 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L24 _public member_ `bool bBindSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Bind To Root Bone")` — Whether to bind the simulation mesh.
- L28 _public member_ `bool bBindRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Bind To Root Bone")` — Whether to bind the render mesh.
- L30 _public prototype_ `FChaosClothAssetBindToRootBoneNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L33 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/BlendVerticesNode.h` (Public)


#### struct `FChaosClothAssetBlendVerticesNode`  
`struct FChaosClothAssetBlendVerticesNode final : public FDataflowNode`  
_L11-74_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Blend vertex values from another cloth collection. The topology of the Collection will remain the same.
- L24 _public member_ `FManagedArrayCollection BlendCollection;` — `UPROPERTY(Meta = (Dataflowinput))` — Collection to blend in.
- L28 _public member_ `bool bRequireSameVertexCounts = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices")` — Require same vertex counts between Collection and BlendCollection in order to blend a vertex type. Otherwise the shared subset will be blended.
- L32 _public member_ `float BlendingWeight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices", Meta = (ClampMin = 0, ClampMax = 1))` — Blending Weight. 0 = Keep existing values in Collection. 1 = Set values from BlendCollection.
- L36 _public member_ `bool bBlendSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Sim Mesh", Meta = (EditCondition = "BlendingWeight > 0"))` — Blend Sim Mesh.
- L40 _public member_ `bool bBlend2DSimPositions = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Sim Mesh", Meta = (EditCondition = "bBlendSimMesh && BlendingWeight > 0"))` — Blend 2D Sim Positions.
- L44 _public member_ `bool bBlend3DSimPositions = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Sim Mesh", Meta = (EditCondition = "bBlendSimMesh && BlendingWeight > 0"))` — Blend 3D Sim Positions.
- L48 _public member_ `bool bBlendSimNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Sim Mesh", Meta = (EditCondition = "bBlendSimMesh && BlendingWeight > 0"))` — Blend 3D Sim Normals.
- L52 _public member_ `bool bBlendRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Render Mesh", Meta = (EditCondition = "BlendingWeight > 0.f"))` — Blend Render Mesh.
- L56 _public member_ `bool bBlendRenderPositions = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Render Mesh", Meta = (EditCondition = "bBlendRenderMesh && BlendingWeight > 0"))` — Blend Render Positions.
- L60 _public member_ `bool bBlendRenderNormalsAndTangents = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Render Mesh", Meta = (EditCondition = "bBlendRenderMesh && BlendingWeight > 0"))` — Blend Render Normals and Tangents.
- L64 _public member_ `bool bBlendRenderUVs = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Render Mesh", Meta = (EditCondition = "bBlendRenderMesh && BlendingWeight > 0"))` — Blend Render UVs. Only existing UV sets on Collection will be updated.
- L68 _public member_ `bool bBlendRenderColors = true;` — `UPROPERTY(EditAnywhere, Category = "Blend Vertices - Render Mesh", Meta = (EditCondition = "bBlendRenderMesh && BlendingWeight > 0"))` — Blend Render Colors.
- L70 _public prototype_ `FChaosClothAssetBlendVerticesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L73 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ClothCollectionQueryNode.h` (Public)


#### struct `FChaosClothAssetCollectionQueryNode`  
`struct FChaosClothAssetCollectionQueryNode : public FDataflowNode`  
_L16-56_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Query a Managed Array Collection about its Cloth Collection properties.
- L25 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L31 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Input/output collection (Output is always a passthrough)
- L35 _private member_ `bool bIsClothCollection = false;` — `UPROPERTY(Meta = (DataflowOutput))` — Is this collection a valid cloth collection
- L39 _private member_ `bool bHasClothSimMesh = false;` — `UPROPERTY(Meta = (DataflowOutput))` — Does this collection have a cloth sim mesh
- L43 _private member_ `bool bHasClothRenderMesh = false;` — `UPROPERTY(Meta = (DataflowOutput))` — Does this collection have a cloth render mesh
- L47 _private member_ `bool bHasClothProxyDeformer = false;` — `UPROPERTY(Meta = (DataflowOutput))` — Does this collection have proxy deformer data
- L51 _private member_ `FString BooleanPropertyName = TEXT("Pro` — `UPROPERTY(EditAnywhere, Category = "Cloth Collection Query")` — Name of boolean property to query
- L55 _private member_ `bool bBooleanPropertyValue = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth Collection Query", Meta =(DataflowOutput))` — Result of querying BooleanPropertyName. Default value if property doesn't exist matches node value.

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ClothCollectionToDynamicMeshNode.h` (Public)


#### struct `FChaosClothAssetCollectionToDynamicMeshNode`  
`struct FChaosClothAssetCollectionToDynamicMeshNode : public FDataflowNode`  
_L18-50_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Convert a Cloth Collection mesh to a dynamic mesh.
- L22 _public prototype_ `DATAFLOW_NODE_RENDER_TYPE_START() DATAFLOW_NODE_RENDER_TYPE_ADD("SurfaceRender", FName("FDynamicMesh3"), {"SimDynamicMesh"}) DATAFLOW_NODE_RENDER_TYPE_ADD("SurfaceRender", FName("FDynamicMesh3"), {"RenderDynamicMesh", "RenderMaterials"}) DATAFLOW_NODE_RENDER_TYPE_END() public: FChaosClothAssetCollectionToDynamicMeshNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L36 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput))`
- L40 _private member_ `TObjectPtr<UDynamicMesh> SimDynamicMesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output sim collection dynamic mesh.
- L44 _private member_ `TObjectPtr<UDynamicMesh> RenderDynamicMesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output render collection dynamic mesh.
- L48 _private member_ `TArray<TObjectPtr<UMaterialInterface>> RenderMaterials;` — `UPROPERTY(meta = (DataflowOutput))` — Render materials.

#### struct `FChaosClothAssetUpdateClothFromDynamicMeshNode`  
`struct FChaosClothAssetUpdateClothFromDynamicMeshNode : public FDataflowNode`  
_L56-109_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Update cloth collection attributes from a DynamicMesh
- L63 _public prototype_ `FChaosClothAssetUpdateClothFromDynamicMeshNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L65 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L70 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L73 _private member_ `TObjectPtr<const UDynamicMesh> DynamicMesh;` — `UPROPERTY(Meta = (DataflowInput))`
- L76 _private member_ `TArray<TObjectPtr<const UMaterialInterface>> Materials;` — `UPROPERTY(Meta = (DataflowInput))`
- L80 _private member_ `bool bCopyToRenderPositions = false;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection")` — Copy DynamicMesh Vertex Positions to Render Positions
- L84 _private member_ `bool bCopyToRendeNormalsAndTangents = false;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection")` — Copy DynamicMesh Vertex Normals and Tangents to Render Normals and Tangents
- L88 _private member_ `bool bCopyUVsToRenderUVs = false;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection")` — Copy DynamicMesh UVs to Render UVs
- L92 _private member_ `bool bCopyToRenderMaterials = false;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection")` — Copy input materials to Render Materials (order and number must match otherwise only the minimum common number of materials are updated)
- L96 _private member_ `bool bCopyToSim3DPositions = false;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection")` — Copy DynamicMesh Vertex Positions to Sim3D Positions
- L100 _private member_ `bool bCopyToSimNormals = false;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection")` — Copy DynamicMesh Vertex Normals to Sim Normals
- L104 _private member_ `bool bCopyUVsToSim2DPositions = false;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection")` — Copy DynamicMesh UVs to Sim2D Positions
- L108 _private member_ `int32 UVChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "DynamicMesh To Cloth Collection", meta = (EditCondition = "bCopyUVsToSim2DPositions || bCopyUVsToRenderUVs", EditConditionHides))` — Which UV Channel to use at Sim2D Positions or Render UVs. Use -1 to copy all Render UVs.

#### struct `FChaosClothAssetExtractWeightMapNode`  
`struct FChaosClothAssetExtractWeightMapNode : public FDataflowNode`  
_L114-149_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Extract a weight map from a Cloth Collection.
- L121 _public prototype_ `FChaosClothAssetExtractWeightMapNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L123 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L128 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput))`
- L132 _private member_ `FChaosClothAssetConnectableIStringValue WeightMap = { TEXT("Weigh` — `UPROPERTY(EditAnywhere, Category = "Extract Weight Map", Meta = (DataflowInput))` — Name of the weight map to be extracted
- L136 _private member_ `EChaosClothAssetWeightMapMeshTarget MeshTarget = EChaosClothAssetWeightMapMeshTarget::Simulation;` — `UPROPERTY(EditAnywhere, Category = "Extract Weight Map")` — Type of the weight map to be extracted
- L140 _private member_ `bool bReorderForDynamicMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Extract Weight Map")` — Reorder extracted weights to match the order of a DynamicMesh that was created via ClothCollectionToDynamicMesh
- L144 _private member_ `TObjectPtr<UDynamicMesh> DynamicMesh;` — `UPROPERTY(meta = (DataflowInput, EditCondition = "bReorderForDynamicMesh"))` — Dynamic mesh used to reorder weights.
- L147 _private member_ `TArray<float> ExtractedWeightMap;` — `UPROPERTY(meta = (DataflowOutput))`

#### struct `FChaosClothAssetExtractSelectionSetNode`  
`struct FChaosClothAssetExtractSelectionSetNode : public FDataflowNode`  
_L155-191_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Extract a selection set from a Cloth Collection.
- L162 _public prototype_ `FChaosClothAssetExtractSelectionSetNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L164 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L169 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput))`
- L173 _private member_ `FChaosClothAssetConnectableIStringValue Selection = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "Extract Selection Set", Meta = (DataflowInput))` — Name of the selection set to be extracted. Currently only SimVertices3D and RenderVertices sets are supported.
- L177 _private member_ `bool bReorderForDynamicMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Extract Selection Set")` — Reorder extracted indices to match the order of a DynamicMesh that was created via ClothCollectionToDynamicMesh
- L181 _private member_ `TObjectPtr<UDynamicMesh> DynamicMesh;` — `UPROPERTY(meta = (DataflowInput, EditCondition = "bReorderForDynamicMesh"))` — Dynamic mesh used to reorder indices.
- L185 _private member_ `TSet<int32> ExtractedSelectionSet;` — `UPROPERTY(meta = (DataflowOutput))` — Extracted Selection Set as a Set
- L189 _private member_ `TArray<int32> ExtractedSelectionArray;` — `UPROPERTY(meta = (DataflowOutput))` — Extracted Selection Set as an array

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ConnectableValue.h` (Public)


#### struct `FChaosClothAssetConnectableStringValue`  
`struct FChaosClothAssetConnectableStringValue`  
_L10-22_
- reflection: `USTRUCT()`
- L17 _public member_ `FString StringValue;` — `UPROPERTY(EditAnywhere, Category = "Value", Meta = (SkipInDisplayNameChain))` — The value for this property.
- L21 _public member_ `mutable FString StringValue_Override;` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")` — `UPROPERTY(Transient)`

#### struct `FChaosClothAssetConnectableIStringValue`  
`struct FChaosClothAssetConnectableIStringValue`  
_L26-50_
- reflection: `USTRUCT()`
- L33 _public member_ `FString StringValue;` — `UPROPERTY(EditAnywhere, Category = "Value", Meta = (DataflowInput, SkipInDisplayNameChain))` — The value for this property.
- L39 _public member_ `bool bCouldUseFabrics = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Value", Meta = (EditCondition = "false", EditConditionHides))` — Whether the property could import fabrics datas or not
- L43 _public member_ `mutable FString StringValue_Override;` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")` — `UPROPERTY(Transient)`
- L49 _public member_ `bool bBuildFabricMaps = false;` — `UPROPERTY(EditAnywhere, Category = "Value", Meta = (EditCondition = "bCouldUseFabrics", EditConditionHides))` — Whether the property can override the weight map based on the imported fabrics

#### struct `FChaosClothAssetConnectableOStringValue`  
`struct FChaosClothAssetConnectableOStringValue`  
_L53-60_
- reflection: `USTRUCT()`
- L59 _public member_ `FString StringValue;` — `UPROPERTY(EditAnywhere, Category = "Value", Meta = (DataflowOutput, SkipInDisplayNameChain))` — The value for this property.

#### struct `FChaosClothAssetConnectableIOStringValue`  
`struct FChaosClothAssetConnectableIOStringValue`  
_L64-76_
- reflection: `USTRUCT()`
- L71 _public member_ `FString StringValue;` — `UPROPERTY(EditAnywhere, Category = "Value", Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "StringValue", SkipInDisplayNameChain))` — The value for this property.
- L75 _public member_ `mutable FString StringValue_Override;` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")` — `UPROPERTY(Transient)`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/CopySimulationToRenderMeshNode.h` (Public)


#### struct `FChaosClothAssetCopySimulationToRenderMeshNode`  
`struct FChaosClothAssetCopySimulationToRenderMeshNode : public FDataflowNode`  
_L15-37_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Copy the simulation mesh to the render mesh to be able to render the simulation mesh, or when not using a different mesh for rendering.
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L27 _public member_ `TObjectPtr<const UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = "Copy Simulation To Render Mesh")` — New material for the render mesh.
- L31 _public member_ `bool bGenerateSingleRenderPattern = true;` — `UPROPERTY(EditAnywhere, Category = "Copy Simulation To Render Mesh")` — Generate a single render pattern rather than a render pattern per sim pattern.
- L33 _public prototype_ `FChaosClothAssetCopySimulationToRenderMeshNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L36 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/CustomRegionResizingNode.h` (Public)


#### struct `FChaosClothAssetCustomRegionResizingInput`  
`struct FChaosClothAssetCustomRegionResizingInput`  
_L15-26_
- reflection: `USTRUCT()`
- desc: Data to generate a Custom Resizing Region.
- L21 _public member_ `FChaosClothAssetConnectableIStringValue InputSet = {TEXT("Inpu` — `UPROPERTY(EditAnywhere, Category = "Custom Region Resizing")` — Source Set. Must be convertible to a vertex set. Render sets will only be used if this ClothAsset does not have a sim mesh.
- L25 _public member_ `EMeshResizingCustomRegionType ResizingType = EMeshResizingCustomRegionType::TrilinearInterpolation;` — `UPROPERTY(EditAnywhere, Category = "Custom Region Resizing")` — Custom Resizing type.

#### struct `FChaosClothAssetCustomRegionResizingNode`  
`struct FChaosClothAssetCustomRegionResizingNode final : public FDataflowNode`  
_L30-91_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Node for adding custom region resizing data used by the ChaosOutfitAsset's Resizeable Outfit.
- L41 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L42 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L43 _private function_ `virtual bool CanAddPin() const override`
- L47 _private function_ `virtual bool CanRemovePin() const override`
- L51 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L52 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L53 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L57 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetConnectionReference(int32 Index) const;`
- L59 _private member_ `static constexpr int32 NumRequiredInputs = 1;` — non-construction set inputs
- L60 _private member_ `static constexpr int32 NumInitialOptionalInputs = 1;`
- L67 _private prototype_ `TArray<FRegionData> GetRegionData(UE::Dataflow::FContext& Context) const;`
- L70 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L74 _private member_ `TArray<FChaosClothAssetCustomRegionResizingInput> InputGroupData;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Custom Region Resizing", Meta = (SkipInDisplayNameChain))` — Input custom region data. This data will be stored in the resulting Cloth Asset, and available for use when resizing.
- L82 _private member_ `FString SimCustomResizingBlendName;` — `UPROPERTY(VisibleAnywhere, Category = "Custom Region Resizing", Meta = (DataflowOutput))` — The name of the sim mesh weight map generated by this node detailing the vertices should use Custom Regions as opposed to traditional resizing interpolation. Value ranges between 0 (use traditional resizing interpolation) and 1 (use resizing custom group interpolation). These regions can be blended if desired. The name of this sim mesh weight map cannot be changed and is only provided for further tweaking.
- L90 _private member_ `FString RenderCustomResizingBlend;` — `UPROPERTY(VisibleAnywhere, Category = "Custom Region Resizing", Meta = (DataflowOutput))` — The name of the render mesh weight map generated by this node detailing the vertices should use Custom Regions as opposed to traditional resizing interpolation. Value ranges between 0 (use traditional resizing interpolation) and 1 (use resizing custom group interpolation). These regions can be blended if desired. The name of this render mesh weight map cannot be changed and is only provided for further tweaking.

#### struct `FChaosClothAssetCustomRegionResizingNode::FRegionData`  
`struct FRegionData`  
_L62-66_
- L64 _public member_ `FString InputSet;`
- L65 _public member_ `EMeshResizingCustomRegionType ResizingType;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/DatasmithImportNode.h` (Public)


#### class `UChaosClothAssetDatasmithClothAssetFactory`  
`class UChaosClothAssetDatasmithClothAssetFactory final : public UObject`  
_L14-30_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Deprecated.
- L20 _public prototype_ `UChaosClothAssetDatasmithClothAssetFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L22 _public prototype_ `virtual ~UChaosClothAssetDatasmithClothAssetFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L25 _public function_ `UObject* CreateClothAsset(UObject* , const FName& , EObjectFlags ) const` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L27 _public function_ `UObject* DuplicateClothAsset(UObject* , UObject* Outer, const FName& ) const` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L29 _public function_ `void InitializeClothAsset(UObject* , const class FDatasmithCloth& ) const` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`

#### class `UChaosClothAssetDatasmithClothComponentFactory`  
`class UChaosClothAssetDatasmithClothComponentFactory final : public UObject`  
_L35-49_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Deprecated.
- L41 _public prototype_ `UChaosClothAssetDatasmithClothComponentFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L43 _public prototype_ `virtual ~UChaosClothAssetDatasmithClothComponentFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L46 _public function_ `USceneComponent* CreateClothComponent(UObject* ) const` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L48 _public function_ `void InitializeClothComponent(class USceneComponent* , UObject* , class USceneComponent* ) const` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`

#### struct `FChaosClothAssetDatasmithImportNode`  
`struct FChaosClothAssetDatasmithImportNode : public FDataflowNode`  
_L53-80_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: Deprecated. The experimental Datasmith cloth importer is no longer supported. Use the USDImport node instead.
- L60 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))`
- L64 _public member_ `FFilePath ImportFile;` — `UPROPERTY(VisibleAnywhere, Category = "Datasmith Import", Meta = (EditCondition = "false"))` — Path of the file to import using any available Datasmith cloth translator.
- L67 _public function_ `static void RegisterModularFeature()` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L69 _public function_ `static void UnregisterModularFeature()` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L71 _public prototype_ `FChaosClothAssetDatasmithImportNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L75 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L76 _private prototype_ `virtual void Serialize(FArchive& Archive) override;`
- L79 _private member_ `FManagedArrayCollection ImportCache;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/DeleteElementNode.h` (Public)


#### enum `EChaosClothAssetElementType`  
`enum class UE_DEPRECATED(5.4, "Use FChaosClothAssetNodeSelectionGroup instead") EChaosClothAssetElementType : uint8`  
_L14-29_
- reflection: `UENUM()`
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `SimMesh`
- L18 _public enumerator_ `RenderMesh`
- L19 _public enumerator_ `SimPattern`
- L20 _public enumerator_ `RenderPattern`
- L21 _public enumerator_ `SimVertex2D`
- L22 _public enumerator_ `SimVertex3D`
- L23 _public enumerator_ `RenderVertex`
- L24 _public enumerator_ `SimFace`
- L25 _public enumerator_ `RenderFace`
- L26 _public enumerator_ `Seam`
- L28 _public enumerator_ `Deprecated UMETA(Hidden)` — Deprecated marker

#### struct `FChaosClothAssetDeleteElementNode`  
`struct FChaosClothAssetDeleteElementNode : public FDataflowNode`  
_L33-83_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- L41 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L46 _public member_ `EChaosClothAssetElementType ElementType_DEPRECATED = EChaosClothAssetElementType::Deprecated;` — `UE_DEPRECATED(5.4, "Use Group instead")` — `UPROPERTY()` — Element type to delete.
- L50 _public member_ `bool bDeleteSimMesh = false;` — `UPROPERTY(EditAnywhere, Category = "Delete Element")` — Delete the sim mesh.
- L54 _public member_ `bool bDeleteRenderMesh = false;` — `UPROPERTY(EditAnywhere, Category = "Delete Element")` — Delete the render mesh.
- L58 _public member_ `FChaosClothAssetNodeSelectionGroup Group;` — `UPROPERTY(EditAnywhere, Category = "Delete Element")` — Delete specific elements.
- L62 _public member_ `TArray<int32> Elements;` — `UPROPERTY(EditAnywhere, Category = "Delete Element")` — List of Elements to delete from Group. All Elements will be used if left empty.
- L66 _public member_ `FChaosClothAssetConnectableIStringValue SelectionName = {""};` — `UPROPERTY(EditAnywhere, Category = "Delete Element")` — Set of Elements to delete. This selection set will be deleted from the downstream collection since it will now be empty.
- L68 _public prototype_ `FChaosClothAssetDeleteElementNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L72 _public function_ `const TArray<FName>& GetCachedCollectionGroupNames() const` — `UE_DEPRECATED(5.5, "This function is deprecated and will now return an empty array.")` — Return a cached array of all the groups used by the input collection during at the time of the latest evaluation.
- L75 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L77 _private function_ `virtual void OnSelected(UE::Dataflow::FContext& Context)` — `UE_DEPRECATED(5.5, "This function is deprecated and will not be called on selection/deselection.")`
- L79 _private function_ `virtual void OnDeselected()` — `UE_DEPRECATED(5.5, "This function is deprecated and will not be called on selection/deselection.")`
- L80 _private prototype_ `virtual void Serialize(FArchive& Ar);`
- L82 _private member_ `TArray<FName> CachedCollectionGroupNames;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/EnableUVResizingNode.h` (Public)


#### struct `FChaosClothAssetEnableUVResizingNode`  
`struct FChaosClothAssetEnableUVResizingNode final : public FChaosClothAssetSimulationBaseConfigNode`  
_L10-21_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Node for enabling UV Resizing used by the ChaosOutfitAsset's Resizeable Outfit.
- L20 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/GenerateSimMorphTargetNode.h` (Public)


#### struct `FChaosClothAssetGenerateSimMorphTargetNode`  
`struct FChaosClothAssetGenerateSimMorphTargetNode final : public FDataflowNode`  
_L11-38_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Generate a Sim Morph target from a cloth collection sim mesh (with matching topology).
- L24 _public member_ `FManagedArrayCollection MorphTargetCollection;` — `UPROPERTY(Meta = (Dataflowinput))` — Collection to generate the morph target from.
- L28 _public member_ `FString MorphTargetName;` — `UPROPERTY(EditAnywhere, Category = "Sim Morph Target", meta = (DataflowOutput))` — Morph target name
- L32 _public member_ `bool bGenerateNormalDeltas = false;` — `UPROPERTY(EditAnywhere, Category = "Sim Morph Target")` — Whether or not to generate normal deltas
- L34 _public prototype_ `FChaosClothAssetGenerateSimMorphTargetNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L37 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ImportFilePath.h` (Public)


#### struct `FChaosClothAssetImportFilePath`  
`struct FChaosClothAssetImportFilePath`  
_L14-32_
- reflection: `USTRUCT()`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FDelegate, UE::Dataflow::FContext&);`
- L22 _public member_ `FString FilePath;` — `UPROPERTY(EditAnywhere, Category = "Import File Path")`
- L24 _public prototype_ `FChaosClothAssetImportFilePath() = default;`
- L26 _public function_ `explicit FChaosClothAssetImportFilePath(FDelegate&& InDelegate) : Delegate(MoveTemp(InDelegate))`
- L28 _public function_ `void Execute(UE::Dataflow::FContext& Context) const`
- L31 _private member_ `FDelegate Delegate;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Dataflow` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FDelegate, UE::Dataflow::FContext&);`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ImportNode.h` (Public)


#### struct `FChaosClothAssetImportNodeRefreshAsset`  
`struct UE_DEPRECATED(5.5, "Use UE::Dataflow::FunctionProperty instead.") FChaosClothAssetImportNodeRefreshAsset`  
_L16-22_
- reflection: `USTRUCT()`
- desc: Refresh structure for push button customization.
- L21 _public member_ `bool bRefreshAsset = false;` — `UPROPERTY(EditAnywhere, Category = "Import Node Refresh Asset")`

#### struct `FChaosClothAssetImportNode`  
`struct FChaosClothAssetImportNode : public FDataflowNode`  
_L27-59_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Import an existing Cloth Asset into the graph.
- L35 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowOutput))`
- L39 _public member_ `TObjectPtr<const UChaosClothAsset> ClothAsset;` — `UPROPERTY(EditAnywhere, Category = "Cloth Asset Import", Meta = (DataflowInput))` — The Cloth Asset to import into a collection.
- L43 _public member_ `FDataflowFunctionProperty Reimport;` — `UPROPERTY(EditAnywhere, Category = "Cloth Asset Import", Meta = (ButtonImage = "Persona.ReimportAsset", DisplayName = "Reimport Asset"))` — Reimport the imported cloth asset.
- L47 _public member_ `int32 ImportLod = 0;` — `UPROPERTY(EditAnywhere, Category = "Cloth Asset Import", Meta = (DisplayName = "Import LOD", ClampMin = "0"))` — The LOD to import into the collection. Only one LOD can be imported at a time.
- L52 _public member_ `mutable FChaosClothAssetImportNodeRefreshAsset ReimportAsset;` — `UE_DEPRECATED(5.5, "Use FDataflowFunctionProperty Reimport instead.")` — `UPROPERTY()`
- L55 _public prototype_ `FChaosClothAssetImportNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L58 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ImportSimulationCacheNode.h` (Public)


#### struct `FChaosClothAssetImportSimulationCacheNode`  
`struct FChaosClothAssetImportSimulationCacheNode final : public FDataflowNode`  
_L13-61_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Set vertex values from a simulation cache. The topology of the Collection will remain the same.
- L23 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L27 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))` — Input/output collection
- L31 _private member_ `TObjectPtr<const UChaosCacheCollection> ImportedCache;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache", Meta =(Dataflowinput))` — Cache to import in.
- L35 _private member_ `int32 CacheIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache")` — Cache index to read
- L39 _private member_ `float CacheTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache")` — Cache time to read
- L43 _private member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache")` — Transform cache data.
- L47 _private member_ `int32 ParticleOffset = 0;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache")` — Particle cache offset.
- L51 _private member_ `bool bUpdateSimulationMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache")` — Update simulation mesh from cache.
- L55 _private member_ `bool bRecalculateNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache", Meta = (EditCondition = "bUpdateSimulationMesh"))` — Recalculate simulation normals based on imported positions.
- L59 _private member_ `bool bUpdateRenderMesh = false;` — `UPROPERTY(EditAnywhere, Category = "Import Simulation Cache")` — Update render mesh from cache via proxy deformer data.

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ImportedValue.h` (Public)


#### struct `FChaosClothAssetImportedVectorValue`  
`struct FChaosClothAssetImportedVectorValue`  
_L8-25_
- reflection: `USTRUCT()`
- L12 _public typedef_ `using ImportedType = FVector3f;`
- L18 _public member_ `mutable FVector3f ImportedValue = FVector3f::Zero();` — `UPROPERTY(EditAnywhere, Category = "Imported Value", Meta = (EditCondition = "!bUseImportedValue"))` — Property vector Value
- L24 _public member_ `bool bUseImportedValue = false;` — `UPROPERTY(EditAnywhere, Category = "Imported Value")` — Whether the property can use the values imported from USD

#### struct `FChaosClothAssetImportedIntValue`  
`struct FChaosClothAssetImportedIntValue`  
_L28-45_
- reflection: `USTRUCT()`
- L32 _public typedef_ `using ImportedType = int32;`
- L38 _public member_ `mutable int32 ImportedValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Imported Value", Meta = (EditCondition = "!bUseImportedValue"))` — Property integer Value
- L44 _public member_ `bool bUseImportedValue = false;` — `UPROPERTY(EditAnywhere, Category = "Imported Value")` — Whether the property can use the values imported from USD

#### struct `FChaosClothAssetImportedFloatValue`  
`struct FChaosClothAssetImportedFloatValue`  
_L48-65_
- reflection: `USTRUCT()`
- L52 _public typedef_ `using ImportedType = float;`
- L58 _public member_ `mutable float ImportedValue = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Imported Value", Meta = (EditCondition = "!bUseImportedValue"))` — Property float value
- L64 _public member_ `bool bUseImportedValue = false;` — `UPROPERTY(EditAnywhere, Category = "Imported Value")` — Whether the property can use the values imported from USD

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/MergeClothCollectionsNode.h` (Public)


#### struct `FChaosClothAssetMergeClothCollectionsNode_v2`  
`struct FChaosClothAssetMergeClothCollectionsNode_v2 : public FDataflowNode`  
_L13-42_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Merge multiple cloth collections into a single cloth collection of multiple patterns.
- L20 _public member_ `TArray<FManagedArrayCollection> Collections;` — `UPROPERTY()`
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowOutput, DataflowPassthrough = "Collections[0]"))`
- L25 _public prototype_ `FChaosClothAssetMergeClothCollectionsNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L30 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L31 _private function_ `virtual bool CanAddPin() const override`
- L32 _private function_ `virtual bool CanRemovePin() const override`
- L33 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L34 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L35 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L39 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L40 _private member_ `static constexpr int32 NumInitialOptionalInputs = 2;`
- L41 _private prototype_ `UE::Dataflow::TConnectionReference<FManagedArrayCollection> GetConnectionReference(int32 Index) const;`

#### struct `FChaosClothAssetMergeClothCollectionsNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetMergeClothCollectionsNode : public FDataflowNode`  
_L48-98_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated="5.5"))`
- inherits: `FDataflowNode`
- desc: Merge multiple cloth collections into a single cloth collection of multiple patterns.
- L54 _public member_ `static constexpr int32 MaxInputs = 6;` — Hardcoded number of inputs since it is currently not possible to use arrays for optional inputs
- L58 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Input 0, right click on the node and add pins to add more merge inputs.
- L61 _public member_ `FManagedArrayCollection Collection1;` — `UPROPERTY(Meta = (DisplayName = "Collection 1"))` — Input 1, right click on the node and add pins to add more merge inputs.
- L64 _public member_ `FManagedArrayCollection Collection2;` — `UPROPERTY(Meta = (DisplayName = "Collection 2"))` — Input 2, right click on the node and add pins to add more merge inputs.
- L67 _public member_ `FManagedArrayCollection Collection3;` — `UPROPERTY(Meta = (DisplayName = "Collection 3"))` — Input 3, right click on the node and add pins to add more merge inputs.
- L70 _public member_ `FManagedArrayCollection Collection4;` — `UPROPERTY(Meta = (DisplayName = "Collection 4"))` — Input 4, right click on the node and add pins to add more merge inputs.
- L73 _public member_ `FManagedArrayCollection Collection5;` — `UPROPERTY(Meta = (DisplayName = "Collection 5"))` — Input 5, right click on the node and add pins to add more merge inputs.
- L77 _public member_ `int32 NumInputs = NumInitialOptionalInputs;` — `UPROPERTY()` — The number of inputs currently exposed to the node UI.
- L80 _public prototype_ `FChaosClothAssetMergeClothCollectionsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L84 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L85 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L86 _private function_ `virtual bool CanAddPin() const override`
- L87 _private function_ `virtual bool CanRemovePin() const override`
- L88 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L89 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L90 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L93 _private prototype_ `TArray<const FManagedArrayCollection*> GetCollections() const;`
- L94 _private prototype_ `const FManagedArrayCollection* GetCollection(int32 Index) const;`
- L96 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L97 _private member_ `static constexpr int32 NumInitialOptionalInputs = 1;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ProceduralSelectionNode.h` (Public)


#### enum `EChaosClothAssetProceduralSelectionType`  
`enum class EChaosClothAssetProceduralSelectionType : uint8`  
_L12-16_
- reflection: `UENUM()`
- desc: Type of procedural selection
- L14 _public enumerator_ `SelectAll`
- L15 _public enumerator_ `Conversion`

#### struct `FChaosClothAssetProceduralSelectionNode`  
`struct FChaosClothAssetProceduralSelectionNode : public FDataflowNode`  
_L20-51_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Procedurally generate a Cloth Selection set.
- L32 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L36 _private member_ `FString OutputName;` — `UPROPERTY(EditAnywhere, Category = "Procedural Selection", Meta = (DataflowOutput))` — The name to be use as a selection.
- L40 _private member_ `FChaosClothAssetNodeSelectionGroup Group;` — `UPROPERTY(EditAnywhere, Category = "Procedural Selection")` — The type of element the selection refers to
- L44 _private member_ `EChaosClothAssetProceduralSelectionType SelectionType = EChaosClothAssetProceduralSelectionType::SelectAll;` — `UPROPERTY(EditAnywhere, Category = "Procedural Selection")` — The procedural selection method
- L48 _private member_ `FChaosClothAssetConnectableIStringValue ConversionInputName;` — `UPROPERTY(EditAnywhere, Category = "Procedural Selection", Meta = (Dataflowinput, EditCondition = "SelectionType == EChaosClothAssetProceduralSelectionType::Conversion"))` — Selection set to convert from when using Conversion selection type.
- L50 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ProxyDeformerNode.h` (Public)


#### struct `FChaosClothAssetSelectionFilterSet`  
`struct FChaosClothAssetSelectionFilterSet`  
_L15-24_
- reflection: `USTRUCT()`
- desc: Selection Filter Set
- L20 _public member_ `FChaosClothAssetConnectableIStringValue RenderSelection = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")`
- L23 _public member_ `FChaosClothAssetConnectableIStringValue SimSelection = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")`

#### struct `FChaosClothAssetProxyDeformerNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetProxyDeformerNode : public FDataflowNode`  
_L28-138_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Add the proxy deformer information to this cloth collection's render data.
- L36 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L45 _public member_ `FChaosClothAssetConnectableIStringValue SimVertexSelection;` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — The name of a selection containing all the dynamic points. Must be of group type SimVertices2D, SimVertices3D, or SimFaces. Using an empty (or invalid) selection will make the proxy deformer consider all simulation points as dynamic points, and will fully contribute to the render mesh animations (as opposed to using the render mesh skinning for the non dynamic points). This selection is usually built from the same weight map set to the MaxDistance config using a WeightMapToSelection node and a very low threshold.
- L49 _public member_ `FChaosClothAssetConnectableIStringValue SelectionFilterSet0 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L53 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet1 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L57 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet2 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L61 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet3 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L65 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet4 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L69 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet5 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L73 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet6 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L77 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet7 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L81 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet8 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L85 _public member_ `FChaosClothAssetConnectableStringValue SelectionFilterSet9 = { TEXT("Selec` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Selection filter set used to restrict a primary selection of render vertices to a secondary selection of simulation mesh triangles. Right click and do AddPin to add more selection sets .
- L89 _public member_ `bool bUseMultipleInfluences = false;` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Whether using multiple simulation mesh triangles to influence the position of the deformed render vertex.
- L93 _public member_ `float InfluenceRadius = 5.f;` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer", Meta = (EditCondition = "bUseMultipleInfluences"))` — The radius around the render vertices to look for all simulation mesh triangles influencing it (AKA SkinningKernelRadius).
- L101 _public member_ `bool bUseSmoothTransition = true;` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Whether to create a smoothed _SkinningBlendWeight render weight map to ease the transition between the deformed part and the skinned part of the render mesh. When no transition is created there will be a visible step in the rendered triangles around the edge of the kinematic/dynamic transition of the proxy simulation mesh. The _SkinningBlendWeight render weight map is created regardless of the transition being created smooth or not, and can be later adjusted using the weight map tool.
- L109 _public member_ `FString SkinningBlendName;` — `UPROPERTY(VisibleAnywhere, Category = "ProxyDeformer", Meta = (DataflowOutput))` — The name of the render mesh weight map generated by this node detailing the contribution of the proxy deformer. Value ranges between 0 (fully deformed) and 1 (fully skinned). The name of this render mesh weight map cannot be changed and is only provided for further tweaking.
- L111 _public prototype_ `FChaosClothAssetProxyDeformerNode(const UE::Dataflow::FNodeParameters & InParam, FGuid InGuid = FGuid::NewGuid());`
- L115 _private member_ `static constexpr int32 MaxNumFilterSets = 10;` — Hardcoded number of FilterSets since it is currently not possible to use arrays for optional inputs.
- L120 _private member_ `int32 NumFilterSets = NumInitialOptionalInputs;` — `UPROPERTY()` — The number of filter sets currently exposed to the node UI.
- L124 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext & Context, const FDataflowOutput * Out) const override;`
- L125 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L126 _private function_ `virtual bool CanAddPin() const override`
- L127 _private function_ `virtual bool CanRemovePin() const override`
- L128 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L129 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin & Pin) override;`
- L130 _private prototype_ `virtual void PostSerialize(const FArchive & Ar) override;`
- L133 _private prototype_ `TArray<FName> GetSelectionFilterNames(UE::Dataflow::FContext & Context) const;`
- L134 _private prototype_ `TArray<const FChaosClothAssetConnectableStringValue*> Get1To9SelectionFilterSets() const;`
- L136 _private member_ `static constexpr int32 NumRequiredInputs = 2;` — non-filter set inputs
- L137 _private member_ `static constexpr int32 NumInitialOptionalInputs = 1;` — filter set inputs that are created in the constructor.

#### struct `FChaosClothAssetProxyDeformerNode_v2`  
`struct FChaosClothAssetProxyDeformerNode_v2 : public FDataflowNode`  
_L172-220_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Adds the proxy deformer information to this cloth collection's render data. This version of the node does not try to preserve existing Render Tangents by default to maintain existing behavior. This node is only required to selectively assign specific areas of the render mesh to the sim mesh in the proxy deformer data. When this node isn't provided to the construction graph, default proxy deformer data are automatically generated. This node can be used to either override or remove the default proxy deformer data. To enable deformer areas, selection filter sets must be provided. With no selection filter sets, the Cloth Asset is by default fully skinned. When more selection filter sets are needed, right-click on the node and do AddOptionPin to add more sets. Each selection filter set is composed by two selections: * A render mesh selection (natively a RenderVertices selection, but RenderFaces selections can also be used). * A simulation mesh selection (natively a SimFaces selection, but SimVertices3D and SimVertices2D selections can also be used). The render mesh selection of vertices will then only be deformed by the associated simulation mesh selection of faces. The Proxy Deformer node evaluations are usually slower than the equivalent default proxy deformer due to the added processing cost of the selection filter sets. When in use, it is therefore better to place it earlier in the graph. A default SkinningBlend weight map is also generated by the node that masks the areas for
- L180 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L184 _public member_ `TArray<FChaosClothAssetSelectionFilterSet> SelectionFilterSets;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "ProxyDeformer", Meta = (SkipInDisplayNameChain))` — Selection filter set used to restrict a selection of render vertices to a selection of simulation mesh triangles. Right click and do AddOptionPin to add more selection sets .
- L188 _public member_ `bool bUseMultipleInfluences = false;` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Whether using multiple simulation mesh triangles to influence the position of the deformed render vertex.
- L192 _public member_ `float InfluenceRadius = 5.f;` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer", Meta = (EditCondition = "bUseMultipleInfluences"))` — The radius around the render vertices to look for all simulation mesh triangles influencing it (AKA SkinningKernelRadius).
- L196 _public member_ `bool bPreserveRenderTangents = false;` — `UPROPERTY(EditAnywhere, Category = "ProxyDeformer")` — Whether or not to include the RenderTangents when generating the proxy deformer data.
- L198 _public prototype_ `FChaosClothAssetProxyDeformerNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid(), bool bInPreserveRenderTangents = false);`
- L203 _protected prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L204 _protected prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L205 _protected function_ `virtual bool CanAddPin() const override`
- L206 _protected function_ `virtual bool CanRemovePin() const override`
- L207 _protected prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L208 _protected prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L209 _protected prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L214 _private prototype_ `TArray<TPair<FName, FName>> GetSelectionFilterNames(UE::Dataflow::FContext& Context) const;`
- L215 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetRenderConnectionReference(int32 Index) const;`
- L216 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetSimConnectionReference(int32 Index) const;`
- L218 _private member_ `static constexpr int32 NumRequiredInputs = 1;` — non-filter set inputs
- L219 _private member_ `static constexpr int32 NumInitialSelectionFilterSets = 1;`

#### struct `FChaosClothAssetProxyDeformerNode_v3`  
`struct FChaosClothAssetProxyDeformerNode_v3 : public FChaosClothAssetProxyDeformerNode_v2`  
_L255-262_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetProxyDeformerNode_v2`
- desc: Adds the proxy deformer information to this cloth collection's render data. This version will include the render tangents when generating the proxy deformer data by default (matches the default behavior if no proxy deformer node is added). This node is only required to selectively assign specific areas of the render mesh to the sim mesh in the proxy deformer data. When this node isn't provided to the construction graph, default proxy deformer data are automatically generated. This node can be used to either override or remove the default proxy deformer data. To enable deformer areas, selection filter sets must be provided. With no selection filter sets, the Cloth Asset is by default fully skinned. When more selection filter sets are needed, right-click on the node and do AddOptionPin to add more sets. Each selection filter set is composed by two selections: * A render mesh selection (natively a RenderVertices selection, but RenderFaces selections can also be used). * A simulation mesh selection (natively a SimFaces selection, but SimVertices3D and SimVertices2D selections can also be used). The render mesh selection of vertices will then only be deformed by the associated simulation mesh selection of faces. The Proxy Deformer node evaluations are usually slower than the equivalent default proxy deformer due to the added processing cost of the selection filter sets. When in use, it is therefore better to place it earlier in the graph. A default SkinningBlend weight map is also
- L261 _public prototype_ `FChaosClothAssetProxyDeformerNode_v3(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/RecalculateNormalsNode.h` (Public)


#### struct `FChaosClothAssetRecalculateNormalsNode`  
`struct FChaosClothAssetRecalculateNormalsNode : public FDataflowNode`  
_L11-26_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FDataflowNode`
- desc: Recalculate the geometry's normals. Experimental, only does the render geometry.
- L21 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L25 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/RemeshNode.h` (Public)


#### enum `EChaosClothAssetRemeshMethod`  
`enum class EChaosClothAssetRemeshMethod : uint8`  
_L14-18_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Remesh`
- L17 _public enumerator_ `Simplify`

#### enum `EChaosClothAssetRemeshSelectionSource`  
`enum class EChaosClothAssetRemeshSelectionSource : uint8`  
_L21-25_
- reflection: `UENUM()`
- L23 _public enumerator_ `SelectionInput UMETA(DisplayName = "From Selection Input")`
- L24 _public enumerator_ `DensityMapInput UMETA(DisplayName = "From DensityMap Input (With Threshold)")`

#### struct `FChaosClothAssetRemeshNode_v2`  
`struct FChaosClothAssetRemeshNode_v2 : public FDataflowNode`  
_L31-148_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Remesh the cloth surface(s) to get the specified mesh resolution(s). NOTE: Accessory Meshes, Weight Maps, Skinning Data, Self Collision Spheres, and Long Range Attachment Constraints will be reconstructed on the output mesh, however all other Selections will be removed
- L38 _public prototype_ `FChaosClothAssetRemeshNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L44 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))` — Cloth collection to remesh
- L48 _private member_ `bool bRemeshSim = true;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh")` — True if the sim mesh needs to be remeshed
- L52 _private member_ `EChaosClothAssetRemeshSelectionSource SelectionSourceSim = EChaosClothAssetRemeshSelectionSource::DensityMapInput;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", Meta = (EditCondition = "bRemeshSim"))` — Defines the source for selecting which part of the sim mesh is being remeshed
- L59 _private member_ `FChaosClothAssetConnectableIStringValue TriangleSelectionSim;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", Meta = (EditCondition = "bRemeshSim && SelectionSourceSim == EChaosClothAssetRemeshSelectionSource::SelectionInput"))` — Optional sim mesh triangle selection to use for remeshing the selection defines what triangles will can remeshed, the one not in the selection will remain unchanged
- L66 _private member_ `FChaosClothAssetWeightedValueNonAnimatable DensityMapSim = { 100.f, 200.f, TEXT("Densi` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", Meta = (EditCondition = "bRemeshSim"))` — Range of target mesh resolutions, as a percentage of input triangle mesh resolution. A value of 50 on all vertices should roughly halve the total number of triangles. If a valid vertex weight map is specified, it will use vertex weights to interpolate between the Lo and Hi values. Otherwise it will use the Lo value on all vertices.
- L73 _private member_ `float DensityMapThresholdSim = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshSim && SelectionSourceSim == EChaosClothAssetRemeshSelectionSource::DensityMapInput"))` — Threshold used to define how to convert the sim mesh density into a selection map Triangles with all their vertices above or equal to the threshold will remain untouched
- L77 _private member_ `int32 IterationsSim = 10;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", meta = (UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "200", EditCondition = "bRemeshSim"))` — Number of iterations to use for remeshing the sim mesh
- L81 _private member_ `double SmoothingSim = 0.25;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshSim"))` — Smoothing factor for the sim remeshing operation
- L85 _private member_ `bool bRemeshRender = false;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh")` — True if the render mesh needs to be remeshed
- L89 _private member_ `EChaosClothAssetRemeshMethod RemeshMethodRender = EChaosClothAssetRemeshMethod::Remesh;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshRender"))` — Method to use when remeshing the render mesh
- L93 _private member_ `EChaosClothAssetRemeshSelectionSource SelectionSourceRender = EChaosClothAssetRemeshSelectionSource::DensityMapInput;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", Meta = (EditCondition = "bRemeshRender"))` — Defines the source for selecting which part of the Render mesh is being remeshed
- L100 _private member_ `FChaosClothAssetConnectableIStringValue TriangleSelectionRender;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", Meta = (EditCondition = "bRemeshRender && && SelectionSourceRender == EChaosClothAssetRemeshSelectionSource::SelectionInput"))` — Optional render mesh triangle selection to use for remeshing The selection defines what traingles will can remeshed, the one not in teh selection will remain unchanged
- L107 _private member_ `FChaosClothAssetWeightedValueNonAnimatable DensityMapRender = { 100.f, 200.f, TEXT("Densi` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", Meta = (EditCondition = "bRemeshRender && RemeshMethodRender == EChaosClothAssetRemeshMethod::Remesh"))` — Range of target mesh resolutions when using the Remesh method, as a percentage of input triangle mesh resolution. A value of 50 on all vertices should roughly halve the total number of triangles. If a valid vertex weight map is specified, it will use vertex weights to interpolate between the Lo and Hi values. Otherwise it will use the Lo value on all vertices.
- L114 _private member_ `float DensityMapThresholdRender = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshRender && SelectionSourceRender == EChaosClothAssetRemeshSelectionSource::DensityMapInput"))` — Threshold used to define how to convert the render mesh density into a selection map Triangles with all their vertices above or equal to the threshold will remain untouched
- L120 _private member_ `int32 TargetPercentRender = 100;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "1", UIMax = "200", ClampMin = "1", EditCondition = "bRemeshRender && RemeshMethodRender == EChaosClothAssetRemeshMethod::Simplify"))` — Target mesh resolution when using the Simplify method, as a percentage of input triangle mesh resolution. A value of 50 should roughly halve the total number of triangles.
- L124 _private member_ `int32 IterationsRender = 10;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "100", EditCondition = "bRemeshRender && RemeshMethodRender == EChaosClothAssetRemeshMethod::Remesh"))` — number of iterations to use for remeshing the render mesh
- L128 _private member_ `double SmoothingRender = 0.25;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshRender && RemeshMethodRender == EChaosClothAssetRemeshMethod::Remesh"))` — smoothing factor for the render remeshing operation
- L132 _private member_ `bool bRemeshRenderSeams = false;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (EditCondition = "bRemeshRender"))` — If checked, attempt to find matching vertices along Render mesh boundaries and remesh these separately
- L136 _private member_ `int32 RenderSeamRemeshIterations = 1;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "100", EditCondition = "bRemeshRender && bRemeshRenderSeams"))` — Number of remesh iterations over the Render mesh seams
- L138 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext & Context, const FDataflowOutput * Out) const override;`
- L141 _private prototype_ `virtual bool CanDebugDraw() const override;`
- L142 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L143 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L146 _private prototype_ `void GetSimSelectionFromContext(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& Collection, const FString& SimDensityMap, TSet<int32>& OutSelection) const;`
- L147 _private prototype_ `void GetRenderSelectionFromContext(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& Collection, const FString& RenderDensityMap, TSet<int32>& OutSelection) const;`

#### struct `FChaosClothAssetRemeshNode`  
`struct UE_DEPRECATED(5.6, "Use the newer version of this node instead.") FChaosClothAssetRemeshNode : public FDataflowNode`  
_L156-221_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Remesh the cloth surface(s) to get the specified mesh resolution(s). NOTE: Weight Maps, Skinning Data, Self Collision Spheres, and Long Range Attachment Constraints will be reconstructed on the output mesh, however all other Selections will be removed
- L164 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L167 _public member_ `bool bRemeshSim = true;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh")`
- L170 _public member_ `int32 TargetPercentSim = 100;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", meta=(UIMin = "1", UIMax = "200", ClampMin = "1", EditCondition = "bRemeshSim"))`
- L173 _public member_ `int32 IterationsSim = 10;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", meta = (UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "200", EditCondition = "bRemeshSim"))`
- L176 _public member_ `double SmoothingSim = 0.25;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshSim"))`
- L179 _public member_ `FChaosClothAssetConnectableIStringValue DensityMapSim;` — `UPROPERTY(EditAnywhere, Category = "Sim Mesh", Meta = (EditCondition = "bRemeshSim"))`
- L182 _public member_ `bool bRemeshRender = false;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh")`
- L185 _public member_ `int32 TargetPercentRender = 100;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta=(UIMin = "1", UIMax = "200", ClampMin = "1", EditCondition = "bRemeshRender"))`
- L188 _public member_ `EChaosClothAssetRemeshMethod RemeshMethodRender = EChaosClothAssetRemeshMethod::Remesh;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshRender"))`
- L191 _public member_ `int32 IterationsRender = 10;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "100", EditCondition = "bRemeshRender && RemeshMethodRender == EChaosClothAssetRemeshMethod::Remesh"))`
- L194 _public member_ `double SmoothingRender = 0.25;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bRemeshRender && RemeshMethodRender == EChaosClothAssetRemeshMethod::Remesh"))`
- L198 _public member_ `bool bRemeshRenderSeams = false;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (EditCondition = "bRemeshRender"))` — If checked, attempt to find matching vertices along Render mesh boundaries and remesh these separately
- L202 _public member_ `int32 RenderSeamRemeshIterations = 1;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (UIMin = "0", UIMax = "20", ClampMin = "0", ClampMax = "100", EditCondition = "bRemeshRender && bRemeshRenderSeams"))` — Number of remesh iterations over the Render mesh seams
- L205 _public member_ `FChaosClothAssetConnectableIStringValue DensityMapRender;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", Meta = (EditCondition = "bRemeshRender && RemeshMethodRender == EChaosClothAssetRemeshMethod::Remesh"))`
- L207 _public prototype_ `FChaosClothAssetRemeshNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L209 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L213 _private prototype_ `void RemeshSimMesh(const TSharedRef<const FManagedArrayCollection>& ClothCollection, const FString& DensityMapName, const TSharedRef<FManagedArrayCollection>& OutClothCollection) const;`
- L217 _private prototype_ `void RemeshRenderMesh(const TSharedRef<const FManagedArrayCollection>& ClothCollection, const FString& DensityMapName, const TSharedRef<FManagedArrayCollection>& OutClothCollection) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/ReverseNormalsNode.h` (Public)


#### struct `FChaosClothAssetReverseNormalsNode`  
`struct FChaosClothAssetReverseNormalsNode : public FDataflowNode`  
_L13-50_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Reverse the geometry's normals or/and winding order of the simulation or/and render meshes stored in the cloth collection.
- L20 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L24 _public member_ `TArray<int32> SimPatterns;` — `UPROPERTY(EditAnywhere, Category = "Reverse Normals|Simulation Mesh")` — List of sim patterns to apply the operation on. All patterns will be used if left empty.
- L28 _public member_ `bool bReverseSimMeshNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Reverse Normals|Simulation Mesh")` — Whether to reverse the simulation mesh normals.
- L32 _public member_ `bool bReverseSimMeshWindingOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Reverse Normals|Simulation Mesh")` — Whether to reverse the simulation mesh triangles' winding order.
- L36 _public member_ `TArray<int32> RenderPatterns;` — `UPROPERTY(EditAnywhere, Category = "Reverse Normals|Render Mesh")` — List of render patterns to apply the operation on. All patterns will be used if left empty.
- L40 _public member_ `bool bReverseRenderMeshNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Reverse Normals|Render Mesh")` — Whether to reverse the render mesh normals.
- L44 _public member_ `bool bReverseRenderMeshWindingOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Reverse Normals|Render Mesh")` — Whether to reverse the render mesh triangles' winding order.
- L46 _public prototype_ `FChaosClothAssetReverseNormalsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L49 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SelectionNode.h` (Public)


#### enum `EChaosClothAssetSelectionType`  
`enum class UE_DEPRECATED(5.4, "Use FChaosClothAssetNodeSelectionGroup instead") EChaosClothAssetSelectionType : uint8`  
_L16-35_
- reflection: `UENUM()`
- desc: What type of element is selected in the Selection
- L19 _public enumerator_ `SimVertex2D` — 2D simulation vertices
- L22 _public enumerator_ `SimVertex3D` — 3D simulation vertices
- L25 _public enumerator_ `RenderVertex` — Render vertices
- L28 _public enumerator_ `SimFace` — Simulation faces (2D/3D are the same)
- L31 _public enumerator_ `RenderFace` — Render faces
- L34 _public enumerator_ `Deprecated UMETA(Hidden)` — Deprecated marker

#### struct `FChaosClothAssetNodeSelectionGroup`  
`struct FChaosClothAssetNodeSelectionGroup`  
_L42-48_
- reflection: `USTRUCT()`
- desc: The managed array collection group used in the selection. This separate structure is required to allow for customization of the UI.
- L47 _public member_ `FString Name = TEXT("Sim` — `UPROPERTY(EditAnywhere, Category = "Selection Group")`

#### enum `EChaosClothAssetSelectionOverrideType`  
`enum class EChaosClothAssetSelectionOverrideType : uint8`  
_L52-58_
- reflection: `UENUM()`
- desc: How the sets stored on the SelectionNode should be applied to an existing set. If no set exists, it is treated as empty.
- L55 _public enumerator_ `ReplaceAll` — Replace the existing set with values in [Secondary]Indices.
- L57 _public enumerator_ `Modify` — Append values in [Secondary]Indices. Remove values in [Secondary]RemoveIndices.

#### struct `FChaosClothAssetSelectionNode_v2`  
`struct FChaosClothAssetSelectionNode_v2 final : public FDataflowNode`  
_L61-149_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- L70 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L74 _public member_ `FManagedArrayCollection TransferCollection;` — `UPROPERTY(Meta = (DataflowInput))` — The collection used to transfer sets from.
- L78 _public member_ `FChaosClothAssetConnectableOStringValue OutputName;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — The name to be use as a selection.
- L82 _public member_ `FChaosClothAssetConnectableIStringValue InputName;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — The name to populate this set from and override based on Selection Override Type. Output Name will be used if Input Name is empty.
- L87 _public member_ `EChaosClothAssetSelectionOverrideType SelectionOverrideType = EChaosClothAssetSelectionOverrideType::ReplaceAll;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — How to apply this node's Indices onto existing sets. Changing this value will change the output set. To change how the node's stored indices are calculated, change the equivalent value on the Selection Tool context.
- L91 _public member_ `FChaosClothAssetNodeSelectionGroup Group;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — The type of element the selection refers to
- L95 _public member_ `TSet<int32> Indices;` — `UPROPERTY(EditAnywhere, Category = "Selection", Meta = (ClampMin = "0"))` — Selected element indices
- L99 _public member_ `TSet<int32> RemoveIndices;` — `UPROPERTY(EditAnywhere, Category = "Selection", Meta = (ClampMin = "0", EditCondition = "SelectionOverrideType == EChaosClothAssetSelectionOverrideType::Modify"))` — Indices to remove from the Input selection
- L103 _public member_ `FDataflowFunctionProperty Import;` — `UPROPERTY(EditAnywhere, Category = "Selection", Meta = (ButtonImage = "Icons.Refresh"))` — Import (replace) the current selection from the input Collection's selection with the given Input Name (or Output Name if Input Name is empty).
- L110 _public member_ `FDataflowFunctionProperty ImportSecondary;` — `UPROPERTY(EditAnywhere, Category = "Selection", Meta = (ButtonImage = "Icons.Refresh"))` — Import (replace) the current selection from the input Collection's secondary selection with the given Input Name (or Output Name if Input Name is empty). Secondary selections are only supported in v1 of this node. This function is provided as a migration tool to this current version.
- L117 _public member_ `EChaosClothAssetWeightMapTransferType SimTransferType = EChaosClothAssetWeightMapTransferType::Use2DSimMesh;` — `UPROPERTY(EditAnywhere, Category = "Selection Transfer")` — The type of transfer used to transfer the sim mesh sets when a TransferCollection is connected. This property is disabled when no TransferCollection input has been connected.
- L124 _public member_ `float TransferSelectionThreshold = 0.95f;` — `UPROPERTY(EditAnywhere, Category = "Selection Transfer", Meta = (ClampMin = "0", ClampMax = "1"))` — Selections are internally converted to maps in order to do the transfer and then converted back. This value is used to do the conversion back. Decrease this value to (possibly) expand the converted selection.
- L128 _public member_ `FDataflowFunctionProperty Transfer;` — `UPROPERTY(EditAnywhere, Category = "Selection Transfer", Meta = (ButtonImage = "Icons.Convert"))` — Transfer the selection from the connected Transfer Collection containing a selection with Input Name (or Output Name if Input Name is empty).
- L130 _public prototype_ `FChaosClothAssetSelectionNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L137 _private prototype_ `FName GetInputName(UE::Dataflow::FContext& Context) const;`
- L138 _private prototype_ `void SetIndices(const TSet<int32>& InputSet, const TSet<int32>& FinalSet);`
- L139 _private prototype_ `void CalculateFinalSet(const TSet<int32>& InputSet, TSet<int32>& FinalSet) const;`
- L140 _private prototype_ `static TUniquePtr<class FToolCommandChange> MakeSelectedNodeChange(const FChaosClothAssetSelectionNode_v2& Node);`
- L143 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L146 _private prototype_ `void OnImport(UE::Dataflow::FContext& Context);`
- L147 _private prototype_ `void OnImportSecondary(UE::Dataflow::FContext& Context);`
- L148 _private prototype_ `void OnTransfer(UE::Dataflow::FContext& Context);`

#### struct `FChaosClothAssetSelectionNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetSelectionNode : public FDataflowTerminalNode`  
_L155-262_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.5"))`
- inherits: `FDataflowTerminalNode`
- desc: Integer index set selection node.
- L164 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L174 _public member_ `FManagedArrayCollection TransferCollection;` — `UPROPERTY(Meta = (DataflowInput))` — The collection used to transfer sets from. Connecting a collection containing a set with Input Name (or Name if Input Name is empty) and compatible Group will transfer the set to the input collection topology. Note this operation only happens once when the TransferCollection is first connected, or updated. Changing the InputName or the TransferType will also redo the transfer operation.
- L178 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Selection", Meta = (DataflowOutput))` — The name to give the selection attribute
- L182 _public member_ `FChaosClothAssetConnectableIStringValue InputName = { TEXT("") };` — `UPROPERTY(EditAnywhere, Category = "Selection")` — The name to populate this set from and override based on Selection Override Type. Name will be used if Input Name is empty.
- L187 _public member_ `EChaosClothAssetSelectionOverrideType SelectionOverrideType = EChaosClothAssetSelectionOverrideType::ReplaceAll;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — How to apply this node's Indices onto existing sets. Changing this value will change the output set. To change how the node's stored indices are calculated, change the equivalent value on the Selection Tool context.
- L192 _public member_ `EChaosClothAssetSelectionType Type_DEPRECATED = EChaosClothAssetSelectionType::Deprecated;` — `UE_DEPRECATED(5.4, "Use Group instead")` — `UPROPERTY()` — The type of element the selection refers to
- L196 _public member_ `FChaosClothAssetNodeSelectionGroup Group;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — The type of element the selection refers to
- L200 _public member_ `TSet<int32> Indices;` — `UPROPERTY(EditAnywhere, Category = "Selection", Meta = (ClampMin = "0"))` — Selected element indices
- L204 _public member_ `TSet<int32> RemoveIndices;` — `UPROPERTY(EditAnywhere, Category = "Selection", Meta = (ClampMin = "0", EditCondition = "SelectionOverrideType == EChaosClothAssetSelectionOverrideType::Modify"))` — Indices to remove from the Input selection
- L208 _public member_ `FChaosClothAssetNodeSelectionGroup SecondaryGroup;` — `UPROPERTY(EditAnywhere, Category = "Secondary Selection")` — The type of element the secondary selection refers to
- L212 _public member_ `TSet<int32> SecondaryIndices;` — `UPROPERTY(EditAnywhere, Category = "Secondary Selection", Meta = (ClampMin = "0"))` — Secondary set of element indices
- L216 _public member_ `TSet<int32> RemoveSecondaryIndices;` — `UPROPERTY(EditAnywhere, Category = "Secondary Selection", Meta = (ClampMin = "0", EditCondition = "SelectionOverrideType == EChaosClothAssetSelectionOverrideType::Modify"))` — Secondary set indices to remove from the Input selection
- L223 _public member_ `EChaosClothAssetWeightMapTransferType SimTransferType = EChaosClothAssetWeightMapTransferType::Use2DSimMesh;` — `UPROPERTY(EditAnywhere, Category = "Selection Transfer", Meta = (EditCondition = "TransferCollectionHash != 0"))` — The type of transfer used to transfer the sim mesh sets when a TransferCollection is connected. This property is disabled when no TransferCollection input has been connected.
- L230 _public member_ `float TransferSelectionThreshold = 0.95f;` — `UPROPERTY(EditAnywhere, Category = "Selection Transfer", Meta = (EditCondition = "TransferCollectionHash != 0", ClampMin = "0", ClampMax = "1"))` — Selections are internally converted to maps in order to do the transfer and then converted back. This value is used to do the conversion back. Decrease this value to (possibly) expand the converted selection.
- L232 _public prototype_ `FChaosClothAssetSelectionNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L236 _public function_ `const TArray<FName>& GetCachedCollectionGroupNames() const` — `UE_DEPRECATED(5.5, "This function is deprecated and will now return an empty array.")` — Return a cached array of all the groups used by the input collection during at the time of the latest evaluation.
- L238 _public prototype_ `FName GetInputName(UE::Dataflow::FContext& Context) const;`
- L241 _public prototype_ `void SetIndices(const TSet<int32>& InputSet, const TSet<int32>& FinalSet);` — Set Indices based on SelectionOverrideType
- L243 _public prototype_ `void SetSecondaryIndices(const TSet<int32>& InputSet, const TSet<int32>& FinalSet);` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")`
- L245 _public prototype_ `void CalculateFinalSet(const TSet<int32>& InputSet, TSet<int32>& FinalSet) const;`
- L247 _public prototype_ `void CalculateFinalSecondarySet(const TSet<int32>& InputSet, TSet<int32>& FinalSet) const;` — `UE_DEPRECATED(5.6, "Secondary selection sets are no longer supported.")`
- L250 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L251 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L253 _private function_ `virtual void OnSelected(UE::Dataflow::FContext& )` — `UE_DEPRECATED(5.5, "This function is deprecated and will not be called on selection/deselection.")`
- L255 _private function_ `virtual void OnDeselected()` — `UE_DEPRECATED(5.5, "This function is deprecated and will not be called on selection/deselection.")`
- L256 _private prototype_ `virtual void Serialize(FArchive& Ar);`
- L258 _private member_ `TArray<FName> CachedCollectionGroupNames;`
- L261 _private member_ `uint32 TransferCollectionHash = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SelectionToIntMapNode.h` (Public)


#### struct `FChaosClothAssetSelectionToIntMapNode`  
`struct FChaosClothAssetSelectionToIntMapNode : public FDataflowNode`  
_L14-53_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Convert an integer index selection to an integer map. Map type will match the selection type.
- L22 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L26 _public member_ `FChaosClothAssetConnectableIStringValue SelectionName;` — `UPROPERTY(EditAnywhere, Category = "Selection To Int Map")` — The name of the selection to convert.
- L33 _public member_ `FChaosClothAssetConnectableIOStringValue IntMapName;` — `UPROPERTY(EditAnywhere, Category = "Selection To Int Map")` — The name of the integer map attribute that will be added to the collection. If left empty the same name as the selection name will be used instead.
- L38 _public member_ `bool bKeepExistingUnselectedValues = true;` — `UPROPERTY(EditAnywhere, Category = "Selection To Int Map")` — If the IntMapName already exists, keep existing values rather than overwriting them with 'Unselected Value'.
- L42 _public member_ `int32 UnselectedValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Selection To Int Map")` — The value unselected elements receive. Unselected existing values can be kept by setting 'Keep Existing Unselected Values'
- L46 _public member_ `int32 SelectedValue = 1;` — `UPROPERTY(EditAnywhere, Category = "Selection To Int Map")` — The value selected elements receive.
- L48 _public prototype_ `FChaosClothAssetSelectionToIntMapNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L52 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SelectionToWeightMapNode.h` (Public)


#### struct `FChaosClothAssetSelectionToWeightMapNode`  
`struct FChaosClothAssetSelectionToWeightMapNode : public FDataflowNode`  
_L13-47_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Convert an integer index selection to a vertex weight map where different map values can be set for selected and unselected vertices.
- L21 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L25 _public member_ `FString SelectionName;` — `UPROPERTY(Meta = (DataflowInput))` — The name of the selection to convert.
- L32 _public member_ `FString WeightMapName;` — `UPROPERTY(EditAnywhere, Category = "Selection To Weight Map", Meta = (DataflowOutput))` — The name of the weight map attribute that will be added to the collection. If left empty the same name as the selection name will be used instead.
- L36 _public member_ `float UnselectedValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Selection To Weight Map", Meta = (ClampMin = "0", ClampMax = "1"))` — The value unselected vertices receive.
- L40 _public member_ `float SelectedValue = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Selection To Weight Map", Meta = (ClampMin = "0", ClampMax = "1"))` — The value selected vertices receive.
- L42 _public prototype_ `FChaosClothAssetSelectionToWeightMapNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L46 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SetPhysicsAssetNode.h` (Public)


#### struct `FChaosClothAssetSetPhysicsAssetNode`  
`struct FChaosClothAssetSetPhysicsAssetNode : public FDataflowNode`  
_L15-32_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Replace the current physics assets to collide the simulation mesh against.
- L22 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L26 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = "Set Physics Asset", Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "PhysicsAsset"))` — The physics asset to assign to the Cloth Collection.
- L28 _public prototype_ `FChaosClothAssetSetPhysicsAssetNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L31 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationAerodynamicsConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationAerodynamicsConfigNode`  
`struct FChaosClothAssetSimulationAerodynamicsConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-142_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Aerodynamics properties configuration node.
- L34 _public member_ `float FluidDensity = 1.225f;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000", InteractorName = "FluidDensity"))` — The density of the medium in which the aerodynamic forces take place, usually air. The fluid density is given in kg/m^3. Air density is considered to be around 1.225 kg/m^3 in average atmospheric conditions.
- L40 _public member_ `EChaosSoftsSimulationSpace WindVelocitySpace = EChaosSoftsSimulationSpace::WorldSpace;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (InteractorName = "WindVelocitySpace"))` — Wind velocity is specified in this space.
- L47 _public member_ `FVector3f WindVelocity = { 0.f, 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "10", InteractorName = "WindVelocity"))` — The fixed wind velocity [m/s] for this asset. For reference a wind gust is above 8m/s (18mph).
- L55 _public member_ `float TurbulenceRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (ClampMin = "0", ClampMax = "1", InteractorName = "TurbulenceRatio"))` — Ratio of aerodynamic forces applied as turbulent rather than laminar flow. Typically, you will want to use turbulent flow for wind and laminar flow for swimming underwater (unless the water is flowing very rapidly). Turbulent forces scale like velocity squared. Laminar forces scale like velocity.
- L66 _public member_ `FChaosClothAssetWeightedValue Drag = { true, 0.035f, 1.f, TEXT("Drag"), tru` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "!bUsePointBasedWindModel", EditConditionHides, InteractorName = "Drag"))` — The aerodynamic coefficient of drag applying on each particle. When "Outer Drag" is enabled, this acts as the "Inner Drag", i.e., drag applied when the air velocity is moving in the mesh normal direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L69 _public member_ `bool bEnableOuterDrag = false;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (InlineEditConditionToggle))`
- L79 _public member_ `FChaosClothAssetWeightedValue OuterDrag = { true, 0.035f, 1.f, TEXT("OuterDrag")` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "bEnableOuterDrag", InteractorName = "OuterDrag"))` — The aerodynamic coefficient of drag applying on each particle when the air velocity is moving against the mesh normal direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L91 _public member_ `FChaosClothAssetWeightedValue Lift = { true, 0.035f, 1.f, TEXT("Lift"), tru` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "!bUsePointBasedWindModel", EditConditionHides, InteractorName = "Lift"))` — The aerodynamic coefficient of lift applying on each particle. When "Outer Lift" is enabled, this acts as the "Inner Lift", i.e., lift applied when the air velocity is moving in the mesh normal direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L94 _public member_ `bool bEnableOuterLift = false;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (InlineEditConditionToggle))`
- L104 _public member_ `FChaosClothAssetWeightedValue OuterLift = { true, 0.035f, 1.f, TEXT("OuterLift")` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "bEnableOuterLift", InteractorName = "OuterLift"))` — The aerodynamic coefficient of lift applying on each particle when the air velocity is moving against the mesh normal direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L110 _public member_ `bool bUseWithWaterBodies = false;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (EditCondition = "!bUsePointBasedWindModel", EditConditionHides, InteractorName = "UseWithWaterBodies"))` — If true, drag and buoyancy will be used when cloth is submerged under water bodies
- L119 _public member_ `float ClothDensityInWater = 1000.;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "10000", InteractorName = "ClothDensityInWater", EditCondition = "bUseWithWaterBodies && !bUsePointBasedWindModel", EditConditionHides))` — The density of the cloth for buoyancy calculations when submerged in water. Given in kg/m^3 If you want bodies to be neutrally buoyancy, make this the water density.  Larger values make it sink, smaller values make it rise to the surface.
- L127 _public member_ `float WaterDensity = 1000.;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000", InteractorName = "WaterDensity", EditCondition = "bUseWithWaterBodies && !bUsePointBasedWindModel", EditConditionHides))` — The density of the water where buoyancy is taking effect The fluid density is given in kg/m^3. Water density is 1000 kg/m^3
- L136 _public member_ `float WaterTurbulenceRatio = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Aerodynamics", Meta = (ClampMin = "0", ClampMax = "1", InteractorName = "WaterTurbulenceRatio", EditCondition = "bUseWithWaterBodies && !bUsePointBasedWindModel", EditConditionHides))` — Ratio of aerodynamic forces applied as turbulent rather than laminar flow. Typically, you will want to use turbulent flow for wind and laminar flow for swimming underwater (unless the water is flowing very rapidly). Turbulent forces scale like velocity squared. Laminar forces scale like velocity. A value of 0 is appropriate for water.
- L138 _public prototype_ `FChaosClothAssetSimulationAerodynamicsConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L141 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationAnimDriveConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationAnimDriveConfigNode`  
`struct FChaosClothAssetSimulationAnimDriveConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-39_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Anim drive properties configuration node.
- L33 _public member_ `FChaosClothAssetWeightedValue AnimDriveDamping = { true, 0.f, 1.f, TEXT("AnimD` — `UPROPERTY(EditAnywhere, Category = "AnimDrive Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "AnimDriveDamping"))` — The damping amount of the anim drive. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L35 _public prototype_ `FChaosClothAssetSimulationAnimDriveConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L38 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationBackstopConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationBackstopConfigNode`  
`struct FChaosClothAssetSimulationBackstopConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-45_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Backstop properties configuration node.
- L34 _public member_ `FChaosClothAssetWeightedValue BackstopRadius = { true, 0.f, 100.f, TEXT("Backs` — `UPROPERTY(EditAnywhere, Category = "Backstop Properties", Meta = (UIMin = "0", UIMax = "100", ClampMin = "0", InteractorName = "BackstopRadius"))` — The radius of the backstop sphere that each particle collides with. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L38 _public member_ `FChaosClothAssetConnectableIStringValue BackstopMeshName;` — `UPROPERTY(EditAnywhere, Category = "Backstop Properties")` — The name of the accessory mesh to use as the backstop mesh. If none is specified, the default animated mesh will be used
- L41 _public prototype_ `FChaosClothAssetSimulationBackstopConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L44 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationBaseConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationBaseConfigNode`  
`struct FChaosClothAssetSimulationBaseConfigNode : public FDataflowNode`  
_L22-168_
- reflection: `USTRUCT(meta = (Abstract))`
- inherits: `FDataflowNode`
- desc: Base abstract class for all cloth asset config nodes. Inherited class must call RegisterCollectionConnections() in constructor to use this base class Collection.
- L28 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L32 _public member_ `bool bWarnDuplicateProperty = true;` — `UPROPERTY(EditAnywhere, Category = "Simulation Config")` — Warn when overriding an existing property in the collection.
- L34 _public prototype_ `FChaosClothAssetSimulationBaseConfigNode() = default;`
- L36 _public prototype_ `FChaosClothAssetSimulationBaseConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L39 _protected typedef_ `using ECollectionPropertyFlags = ::Chaos::Softs::ECollectionPropertyFlags;` — Short hand for property flag enums
- L138 _protected prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L141 _protected function_ `virtual void AddProperties(UE::Dataflow::FContext& Context, ::Chaos::Softs::FCollectionPropertyMutableFacade& Properties) const` — `UE_DEPRECATED(5.4, "Use AddProperties(FPropertyHelper&) instead.")`
- L143 _protected prototype_ `virtual void AddProperties(struct FPropertyHelper& PropertyHelper) const PURE_VIRTUAL(FChaosClothAssetSimulationBaseConfigNode::AddProperties, );`
- L147 _protected function_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const` — Override this to do additional node-specific evaluate on the cloth collection output. AddProperties has already been called when this is called.
- L149 _protected prototype_ `void RegisterCollectionConnections();`
- L152 _protected function_ `int32 AddPropertyHelper( ::Chaos::Softs::FCollectionPropertyMutableFacade& Properties, const FName& PropertyName, bool bIsAnimatable, const TArray<FName>& SimilarPropertyNames) const` — `UE_DEPRECATED(5.4, "Use FPropertyHelper instead.")`
- L163 _protected prototype_ `int32 AddPropertyHelper( ::Chaos::Softs::FCollectionPropertyMutableFacade& Properties, const FName& PropertyName, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable) const;`

#### struct `FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper`  
`struct FPropertyHelper`  
_L41-136_
- L44 _public prototype_ `FPropertyHelper(const FChaosClothAssetSimulationBaseConfigNode& InConfigNode, UE::Dataflow::FContext& InContext, ::Chaos::Softs::FCollectionPropertyMutableFacade& InProperties, const TSharedRef<FManagedArrayCollection>& InClothCollection);`
- L47 _public prototype_ `template<typename PropertyType UE_REQUIRES(::Chaos::Softs::TIsWeightedType<PropertyType>::Value && !std::is_same_v<PropertyType, bool>)> inline int32 SetProperty(const FName& PropertyName, const PropertyType& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L50 _public prototype_ `template<typename PropertyType UE_REQUIRES(::Chaos::Softs::TIsWeightedType<PropertyType>::Value && !std::is_same_v<PropertyType, bool>)> inline int32 SetPropertyAndString(const FName& PropertyName, const PropertyType& PropertyValue, const FString& StringValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L53 _public prototype_ `template<typename T, typename PropertyType UE_REQUIRES(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T> && ::Chaos::Softs::TIsWeightedType<PropertyType>::Value && !std::is_same_v<PropertyType, bool>)> inline int32 SetProperty(const T* ConfigStruct, const PropertyType* PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L55 _public prototype_ `int32 SetPropertyBool(const FName& PropertyName, bool PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L58 _public prototype_ `template<typename T UE_REQUIRES(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 SetPropertyBool(const T* ConfigStruct, const bool* PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L61 _public prototype_ `template<typename EnumType UE_REQUIRES(TIsEnumClass<EnumType>::Value)> inline int32 SetPropertyEnum(const FName& PropertyName, const EnumType& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L64 _public prototype_ `template<typename T, typename EnumType UE_REQUIRES(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T> && TIsEnumClass<EnumType>::Value)> inline int32 SetPropertyEnum(const T* ConfigStruct, const EnumType* PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L66 _public prototype_ `int32 SetPropertyString(const FName& PropertyName, const FString& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L68 _public prototype_ `int32 SetPropertyString(const FName& PropertyName, const FChaosClothAssetConnectableIStringValue& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L71 _public prototype_ `template<typename T, typename ConnectableStringValueType UE_REQUIRES(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 SetPropertyString(const T* ConfigStruct, const ConnectableStringValueType* PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L73 _public prototype_ `template<typename T UE_REQUIRES(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 SetPropertyString(const T* ConfigStruct, const FString* PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::Animatable);`
- L75 _public prototype_ `int32 SetPropertyWeighted(const FName& PropertyName, const FVector2f& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);`
- L76 _public prototype_ `int32 SetPropertyWeighted(const FName& PropertyName, const FChaosClothAssetWeightedValue& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);`
- L77 _public prototype_ `int32 SetPropertyWeighted(const FName& PropertyName, const FChaosClothAssetWeightedValueNonAnimatable& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);`
- L78 _public prototype_ `int32 SetPropertyWeighted(const FName& PropertyName, const FChaosClothAssetWeightedValueNonAnimatableNoLowHighRange& PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);`
- L80 _public prototype_ `void OverridePropertiesBool(const TArray<FName>& PropertyNames, bool bPropertyValue);`
- L81 _public prototype_ `void OverridePropertiesFloat(const TArray<FName>& PropertyNames, const EChaosClothAssetConstraintOverrideType OverrideType, const float OverrideValue);`
- L82 _public prototype_ `void OverridePropertiesWeighted(const TArray<FName>& PropertyNames, const EChaosClothAssetConstraintOverrideType OverrideType, const FChaosClothAssetWeightedValueOverride& OverrideValue);`
- L85 _public prototype_ `template<typename T, typename WeightedValueType UE_REQUIRES(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 SetPropertyWeighted(const T* ConfigStruct, const WeightedValueType* PropertyValue, const TArray<FName>& SimilarPropertyNames = {}, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);`
- L87 _public prototype_ `FString GetPropertyString(const FString* PropertyReference) const;`
- L89 _public function_ `TSharedRef<FManagedArrayCollection> GetClothCollection() const`
- L96 _public prototype_ `template<typename PropertyType> void SetSolverProperty(const FName& PropertyName, const PropertyType& PropertyValue, const TFunction<typename PropertyType::ImportedType(UE::Chaos::ClothAsset::FCollectionClothFacade&)>& SolverValueFunction, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);` — Set an imported solver value onto the property
- L102 _public prototype_ `template<typename PropertyType> void SetFabricProperty(const FName& PropertyName, const PropertyType& PropertyValue, const TFunction<typename PropertyType::ImportedType(UE::Chaos::ClothAsset::FCollectionClothFabricFacade&)>& FabricValueFunction, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);` — Set an imported averaged fabric value onto the property
- L108 _public prototype_ `template<typename PropertyType> void SetSolverPropertyWeighted(const FName& PropertyName, const PropertyType& PropertyValue, const TFunction<float(const UE::Chaos::ClothAsset::FCollectionClothFacade&)>& SolverValueFunction, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);` — Set an imported solver value onto the weighted value property (animatable or not)
- L114 _public prototype_ `template<typename PropertyType> void SetFabricPropertyWeighted(const FName& PropertyName, const PropertyType& PropertyValue, const TFunction<float(const UE::Chaos::ClothAsset::FCollectionClothFabricFacade&)>& FabricValueFunction, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None);` — Set an imported fabric value onto the weighted value property (animatable or not)
- L119 _public prototype_ `template<typename MapType, typename PropertyType> void SetFabricPropertyString( const FName& PropertyName, const PropertyType& PropertyValue, const TFunction<MapType(const UE::Chaos::ClothAsset::FCollectionClothFabricFacade&)>& FabricValueFunction, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags = ECollectionPropertyFlags::None, const FName& GroupName = "");`
- L128 _private prototype_ `template<typename T UE_REQUIRES(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline FName FindPropertyNameByAddress(const T* ConfigStruct, const void* PropertyAddress);`
- L130 _private prototype_ `int32 SetPropertyWeighted(const FName& PropertyName, const bool bIsAnimatable, const float& PropertyLow, const float& PropertyHigh, const FString& WeightMap, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags) const;`
- L132 _private member_ `const FChaosClothAssetSimulationBaseConfigNode& ConfigNode;`
- L133 _private member_ `UE::Dataflow::FContext& Context;`
- L135 _private member_ `TSharedRef<FManagedArrayCollection> ClothCollection;`
- L180 _function_ `template<typename PropertyType UE_REQUIRES_DEFINITION(::Chaos::Softs::TIsWeightedType<PropertyType>::Value && !std::is_same_v<PropertyType, bool>)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetProperty( const FName& PropertyName, const PropertyType& PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L192 _function_ `template<typename PropertyType UE_REQUIRES_DEFINITION(::Chaos::Softs::TIsWeightedType<PropertyType>::Value && !std::is_same_v<PropertyType, bool>)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetPropertyAndString( const FName& PropertyName, const PropertyType& PropertyValue, const FString& StringValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L206 _function_ `template<typename T, typename PropertyType UE_REQUIRES_DEFINITION(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T> && ::Chaos::Softs::TIsWeightedType<PropertyType>::Value && !std::is_same_v<PropertyType, bool>)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetProperty( const T* ConfigStruct, const PropertyType* PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L219 _function_ `template<typename T UE_REQUIRES_DEFINITION(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetPropertyBool( const T* ConfigStruct, const bool* PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L236 _function_ `template<typename EnumType UE_REQUIRES_DEFINITION(TIsEnumClass<EnumType>::Value)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetPropertyEnum( const FName& PropertyName, const EnumType& PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L248 _function_ `template<typename T, typename EnumType UE_REQUIRES_DEFINITION(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T> && TIsEnumClass<EnumType>::Value)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetPropertyEnum( const T* ConfigStruct, const EnumType* PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L261 _function_ `template<typename T UE_REQUIRES_DEFINITION(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetPropertyString( const T* ConfigStruct, const FString* PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L274 _function_ `template<typename T, typename WeightedValueType UE_REQUIRES_DEFINITION(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetPropertyWeighted( const T* ConfigStruct, const WeightedValueType* PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L287 _function_ `template<typename T, typename ConnectableStringValueType UE_REQUIRES_DEFINITION(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline int32 FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::SetPropertyString( const T* ConfigStruct, const ConnectableStringValueType* PropertyValue, const TArray<FName>& SimilarPropertyNames, ECollectionPropertyFlags PropertyFlags)`
- L300 _function_ `template<typename T UE_REQUIRES_DEFINITION(std::is_base_of_v<FChaosClothAssetSimulationBaseConfigNode, T>)> inline FName FChaosClothAssetSimulationBaseConfigNode::FPropertyHelper::FindPropertyNameByAddress(const T* ConfigStruct, const void* PropertyAddress)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosClothAssetSimulationBaseConfigNode> : public TStructOpsTypeTraitsBase2<FChaosClothAssetSimulationBaseConfigNode>`  
_L171-177_
- inherits: `TStructOpsTypeTraitsBase2<FChaosClothAssetSimulationBaseConfigNode>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L174-176_

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Dataflow`
- L175 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anona622a0620103`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationBendingConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationBendingConfigNode`  
`struct FChaosClothAssetSimulationBendingConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-203_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Bending constraint property configuration node.
- L49 _public member_ `FChaosClothAssetWeightedValueNonAnimatable FlatnessRatio = { 0.f, 0.f, TEXT("Flatn` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "RestAngleType == EChaosClothAssetRestAngleConstructionType::FlatnessRatio", EditConditionHides))` — Calculate rest angles as a ratio between completely flat and whatever is the 3D rest angle. When FlatnessRatio = 0, this is equivalent to "Use3DRestAngles". When FlatnessRatio = 1, the rest angle will be 0 (completely flat). If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L60 _public member_ `FChaosClothAssetWeightedValueNonAnimatable RestAngle = { 0.f, 0.f, TEXT("RestA` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180", EditCondition = "RestAngleType == EChaosClothAssetRestAngleConstructionType::RestAngle", EditConditionHides))` — Set rest angles to be the explicit value set here (in degrees). 0 = Flat, Positive values fold away from the edge normal, Negative values fold toward the edge normal. When converting vertex weight values to edge values, the value with the smallest absolute value is selected. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L64 _public member_ `EChaosClothAssetConstraintSolverType SolverType = EChaosClothAssetConstraintSolverType::PBD;` — `UPROPERTY(EditAnywhere, Category = "Bending Types")` — Constraint solver type
- L68 _public member_ `EChaosClothAssetConstraintDistributionType DistributionType = EChaosClothAssetConstraintDistributionType::Isotropic;` — `UPROPERTY(EditAnywhere, Category = "Bending Types", Meta = (EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides))` — Constraint distribution type
- L72 _public member_ `EChaosClothAssetBendingConstraintType ConstraintType = EChaosClothAssetBendingConstraintType::HingeAngles;` — `UPROPERTY(EditAnywhere, Category = "Bending Types", Meta = (EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::PBD || DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic", EditConditionHides))` — Constraint method type
- L81 _public member_ `FChaosClothAssetWeightedValue BendingStiffnessWarp = { true, 100.f, 100.f, TEXT("BendingStif` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "BendingStiffnessWarp"))` — The stiffness of the bending constraints in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L90 _public member_ `FChaosClothAssetWeightedValue BendingStiffnessWeft = { true, 100.f, 100.f, TEXT("BendingStiff` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "BendingStiffnessWeft"))` — The stiffness of the bending constraints in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L99 _public member_ `FChaosClothAssetWeightedValue BendingStiffnessBias = { true, 100.f, 100.f, TEXT("BendingStif` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "BendingStiffnessBias"))` — The stiffness of the bending constraints in the bias (diagonal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L108 _public member_ `FChaosClothAssetWeightedValue BendingAnisoDamping = { true, 1.f, 1.f, TEXT("BendingAnis` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"), Meta = (EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic", EditConditionHides, InteractorName = "BendingDamping"))` — The damping of the bending anisotropic constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L115 _public member_ `FChaosClothAssetWeightedValue AnisoBucklingRatio= { true, 0.5f, 0.5f, TEXT("BucklingRat` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", DisplayName = "Aniso Buckling Ratio", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"), Meta = (EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic", EditConditionHides, InteractorName = "BucklingRatio"))` — Once the element has bent such that it's folded more than this ratio from its rest angle ("buckled"), switch to using Buckling Stiffness instead of BendingElement Stiffness. When Buckling Ratio = 0, the Buckling Stiffness will never be used. When BucklingRatio = 1, the Buckling Stiffness will be used as soon as it's bent past its rest configuration.
- L127 _public member_ `FChaosClothAssetWeightedValue BucklingStiffnessWarp = { true, 50.f, 50.f, TEXT("BucklingSti` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "BucklingStiffnessWarp"))` — The stiffness after buckling in the warp (vertical) direction. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L139 _public member_ `FChaosClothAssetWeightedValue BucklingStiffnessWeft = { true, 50.f, 50.f, TEXT("BucklingStif` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "BucklingStiffnessWeft"))` — The stiffness after buckling in the weft (horizontal) direction. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L151 _public member_ `FChaosClothAssetWeightedValue BucklingStiffnessBias = { true, 50.f, 50.f, TEXT("BucklingSti` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "BucklingStiffnessBias"))` — The stiffness after buckling in the bias (diagonal) direction. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L161 _public member_ `FChaosClothAssetWeightedValue BendingStiffness = { true, 1.f, 1.f, TEXT("Bendi` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"), Meta = (EditCondition = "((DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD) || SolverType == EChaosClothAssetConstraintSolverType::PBD)", EditConditionHides, InteractorName = "BendingStiffness"))` — The Stiffness of the bending constraints. Increase the iteration count for stiffer materials. Note that PBD stiffnesses will be internally clamped to [0,1]. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L170 _public member_ `FChaosClothAssetWeightedValue BendingDamping = { true, 1.f, 1.f, TEXT("Bendi` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"), Meta = (EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic ", EditConditionHides, InteractorName = "BendingDamping"))` — The damping of the bending constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L183 _public member_ `FChaosClothAssetWeightedValue BucklingStiffness = { true, 0.9f, 0.9f, TEXT("Buckl` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000", EditCondition = "((DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD) || SolverType == EChaosClothAssetConstraintSolverType::PBD) && ConstraintType == EChaosClothAssetBendingConstraintType::HingeAngles", EditConditionHides, InteractorName = "BucklingStiffness"))` — The stiffness after buckling. The constraint will use this stiffness instead of bending Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than Bending Stiffness. Note that PBD stiffnesses will be internally clamped to [0,1]. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L190 _public member_ `FChaosClothAssetWeightedValue BucklingRatioWeighted = { true, 0.5f, 0.5f, TEXT("Buckl` — `UPROPERTY(EditAnywhere, Category = "Bending Properties", DisplayName = "Buckling Ratio", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"), Meta = (EditCondition = "((DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD) || SolverType == EChaosClothAssetConstraintSolverType::PBD) && ConstraintType == EChaosClothAssetBendingConstraintType::HingeAngles", EditConditionHides, InteractorName = "BucklingRatio"))` — Once the element has bent such that it's folded more than this ratio from its rest angle ("buckled"), switch to using Buckling Stiffness instead of BendingElement Stiffness. When Buckling Ratio = 0, the Buckling Stiffness will never be used. When BucklingRatio = 1, the Buckling Stiffness will be used as soon as it's bent past its rest configuration.
- L192 _public prototype_ `FChaosClothAssetSimulationBendingConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L194 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L198 _private member_ `static constexpr float BucklingRatioDeprecatedDefault = 0.5f;`
- L200 _private member_ `float BucklingRatio_DEPRECATED = BucklingRatioDeprecatedDefault;` — `UPROPERTY()`
- L202 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationBendingOverrideConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationBendingOverrideConfigNode`  
`struct FChaosClothAssetSimulationBendingOverrideConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-123_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Bending constraint property override configuration node.
- L25 _public member_ `FChaosClothAssetWeightedValueOverride FlatnessRatio;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "OverrideFlatnessRatio != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Flatness override value.
- L29 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBendingStiffness = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override")` — Bending stiffness override type.
- L33 _public member_ `FChaosClothAssetWeightedValueOverride BendingStiffness;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "OverrideBendingStiffness != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Bending stiffness override value.
- L37 _public member_ `bool bApplyUniformBendingStiffnessOverride = true;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "OverrideBendingStiffness != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Whether or not to apply the Bending Stiffness Override to warp, weft, and bias stiffnesses of anisotropic bending elements.
- L41 _public member_ `bool bApplyBendingStiffnessOverrideToBuckling = true;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "OverrideBendingStiffness != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Whether or not to apply the Bending Stiffness Override to buckling stiffnesses.
- L45 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBucklingRatio = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override")` — Buckling ratio override type.
- L49 _public member_ `float BucklingRatio = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "OverrideBucklingRatio != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Buckling ratio override value.
- L53 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBucklingStiffness = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyBendingStiffnessOverrideToBuckling", EditConditionHides))` — Buckling stiffness override type.
- L57 _public member_ `FChaosClothAssetWeightedValueOverride BucklingStiffness;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyBendingStiffnessOverrideToBuckling) && OverrideBucklingStiffness != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Buckling stiffness override value.
- L61 _public member_ `bool bApplyUniformBucklingStiffnessOverride = true;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyBendingStiffnessOverrideToBuckling) && OverrideBucklingStiffness != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Whether or not to apply the Buckling Stiffness Override to warp, weft, and bias stiffnesses of anisotropic bending elements.
- L65 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBendingStiffnessWarp = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride", EditConditionHides))` — Warp stiffness override type.
- L69 _public member_ `FChaosClothAssetWeightedValueOverride BendingStiffnessWarp;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride) && OverrideBendingStiffnessWarp != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Bending stiffness warp override value.
- L73 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBendingStiffnessWeft = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride", EditConditionHides))` — Weft stiffness override type.
- L77 _public member_ `FChaosClothAssetWeightedValueOverride BendingStiffnessWeft;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride) && OverrideBendingStiffnessWeft != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Bending stiffness weft override value.
- L81 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBendingStiffnessBias = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride", EditConditionHides))` — Bias stiffness override type.
- L85 _public member_ `FChaosClothAssetWeightedValueOverride BendingStiffnessBias;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride) && OverrideBendingStiffnessBias != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Bending stiffness bias override value.
- L89 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBucklingStiffnessWarp = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride || !bApplyBendingStiffnessOverrideToBuckling) && (OverrideBucklingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBucklingStiffnessOverride)", EditConditionHides))` — Warp buckling stiffness override type.
- L93 _public member_ `FChaosClothAssetWeightedValueOverride BucklingStiffnessWarp;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride || !bApplyBendingStiffnessOverrideToBuckling) && (OverrideBucklingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBucklingStiffnessOverride) && OverrideBucklingStiffnessWarp != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Buckling stiffness warp override value.
- L97 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBucklingStiffnessWeft = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride || !bApplyBendingStiffnessOverrideToBuckling) && (OverrideBucklingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBucklingStiffnessOverride)", EditConditionHides))` — Weft buckling stiffness override type.
- L101 _public member_ `FChaosClothAssetWeightedValueOverride BucklingStiffnessWeft;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride || !bApplyBendingStiffnessOverrideToBuckling) && (OverrideBucklingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBucklingStiffnessOverride) && OverrideBucklingStiffnessWeft != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Buckling stiffness Weft override value.
- L105 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBucklingStiffnessBias = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride || !bApplyBendingStiffnessOverrideToBuckling) && (OverrideBucklingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBucklingStiffnessOverride)", EditConditionHides))` — Bias buckling stiffness override type.
- L109 _public member_ `FChaosClothAssetWeightedValueOverride BucklingStiffnessBias;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "(OverrideBendingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBendingStiffnessOverride || !bApplyBendingStiffnessOverrideToBuckling) && (OverrideBucklingStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformBucklingStiffnessOverride) && OverrideBucklingStiffnessBias != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Buckling stiffness Bias override value.
- L113 _public member_ `EChaosClothAssetConstraintOverrideType OverrideBendingDamping = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Bending Override")` — Damping override type.
- L117 _public member_ `FChaosClothAssetWeightedValueOverride BendingDamping;` — `UPROPERTY(EditAnywhere, Category = "Bending Override", meta = (ClampMin = "0", EditCondition = "OverrideBendingDamping != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Bending damping override value.
- L119 _public prototype_ `FChaosClothAssetSimulationBendingOverrideConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L122 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationClothVertexFaceSpringConfigNode.h` (Public)


#### enum `EChaosClothAssetClothVertexFaceSpringConstructionMethod`  
`enum struct EChaosClothAssetClothVertexFaceSpringConstructionMethod`  
_L13-23_
- reflection: `UENUM()`
- desc: Method for generating springs between source vertices and target faces
- L16 _public enumerator_ `SourceToClosestTarget` — For each source, connect the closest target point
- L18 _public enumerator_ `SourceToRayIntersectionTarget` — For each source, shoot a ray in Normal direction
- L20 _public enumerator_ `AllWithinRadius` — For each source, find all targets within a radius.
- L22 _public enumerator_ `Tetrahedralize` — Create a tet mesh and find corresponding tet face-vertex pairs

#### struct `FChaosClothAssetSimulationClothVertexFaceSpringConstructionSet`  
`struct FChaosClothAssetSimulationClothVertexFaceSpringConstructionSet`  
_L27-63_
- reflection: `USTRUCT()`
- desc: Data to procedurally generate ClothVertexFaceSpring Constraints.
- L33 _public member_ `FChaosClothAssetConnectableIStringValue SourceVertexSelection = { TEXT("Sourc` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction")` — Source Vertex Set
- L37 _public member_ `FChaosClothAssetConnectableIStringValue TargetFaceSelection = { TEXT("Targe` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction")` — Target Face Set
- L41 _public member_ `EChaosClothAssetClothVertexFaceSpringConstructionMethod ConstructionMethod = EChaosClothAssetClothVertexFaceSpringConstructionMethod::SourceToRayIntersectionTarget;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction")` — Construction method used to connect sources and targets
- L45 _public member_ `bool bFlipRayNormal = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", Meta = (EditCondition ="ConstructionMethod == EChaosClothAssetClothVertexFaceSpringConstructionMethod::SourceToRayIntersectionTarget", EditConditionHides))` — Flip normal when doing ray intersection.
- L49 _public member_ `float MaxRayLength = 100.f;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", Meta = (EditCondition = "ConstructionMethod == EChaosClothAssetClothVertexFaceSpringConstructionMethod::SourceToRayIntersectionTarget", EditConditionHides, ClampMin = "0", UIMax = "100"))` — Max ray length for intersection test.
- L53 _public member_ `float Radius = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", Meta = (EditCondition = "ConstructionMethod == EChaosClothAssetClothVertexFaceSpringConstructionMethod::AllWithinRadius", EditConditionHides, ClampMin = "0", UIMax = "100"))` — Radius for search.
- L57 _public member_ `int32 DisableNeighborDistance = 2;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", Meta = (EditCondition = "ConstructionMethod == EChaosClothAssetClothVertexFaceSpringConstructionMethod::AllWithinRadius", EditConditionHides, ClampMin = "1", UIMax = "5"))` — Do not consider vertices within this N-ring of connectivity distance.
- L61 _public member_ `bool bSkipZeroVolumeTets = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", Meta = (EditCondition = "ConstructionMethod == EChaosClothAssetClothVertexFaceSpringConstructionMethod::Tetrahedralize", EditConditionHides))` — Cull zero-volume tets when doing Tetrahedralize.

#### struct `FChaosClothAssetSimulationClothVertexFaceSpringConfigNode`  
`struct FChaosClothAssetSimulationClothVertexFaceSpringConfigNode final : public FChaosClothAssetSimulationBaseConfigNode`  
_L67-181_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Node for creating vertex-face constraints and setting their simulation properties.
- L78 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L79 _private function_ `virtual bool CanAddPin() const override`
- L83 _private function_ `virtual bool CanRemovePin() const override`
- L87 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L88 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L89 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L93 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L94 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`
- L97 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetSourceConnectionReference(int32 Index) const;`
- L98 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetTargetConnectionReference(int32 Index) const;`
- L100 _private member_ `static constexpr int32 NumRequiredInputs = 2;` — non-construction set inputs
- L101 _private member_ `static constexpr int32 NumInitialConstructionSets = 1;`
- L103 _private prototype_ `void CreateConstraints(UE::Dataflow::FContext& Context);`
- L116 _private prototype_ `TArray<FConstructionSetData> GetConstructionSetData(UE::Dataflow::FContext& Context) const;`
- L120 _private member_ `bool bAppendToExisting = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties")` — Append to existing set of constraints. Stiffnesses inherited from existing constraints.
- L124 _private member_ `bool bUseTetRepulsionConstraints = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties")` — Treat as tetrahedral repulsion constraints (e.g., for self collisions) rather than spring constraints
- L128 _private member_ `FVector2f VertexFaceSpringExtensionStiffness = { 100.f, 100.f };` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", InteractorName = "VertexFaceSpringExtensionStiffness", EditCondition = "!bUseTetRepulsionConstraints && !bAppendToExisting", EditConditionHides))` — Extension Stiffness is the spring stiffness applied when the spring is currently longer than its rest length. This is a low-high range, but there are currently no ways to author per-spring stiffnesses, so only Low is used in practice.
- L132 _private member_ `FVector2f VertexFaceSpringCompressionStiffness = { 100.f, 100.f };` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", InteractorName = "VertexFaceSpringCompressionStiffness", EditCondition = "!bUseTetRepulsionConstraints && !bAppendToExisting", EditConditionHides))` — Compression Stiffness is the spring stiffness applied when the spring is currently shorter than its rest length. This is a low-high range, but there are currently no ways to author per-spring stiffnesses, so only Low is used in practice.
- L136 _private member_ `FVector2f VertexFaceSpringDamping = { 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000", InteractorName = "VertexFaceSpringDamping", EditCondition = "!bUseTetRepulsionConstraints && !bAppendToExisting", EditConditionHides))` — This damping is the relative to critical damping. This is a low-high range, but there are currently no ways to author per-spring stiffnesses, so only Low is used in practice.
- L140 _private member_ `float VertexFaceRepulsionStiffness = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties", Meta = (ClampMin = "0", ClampMax = "1", InteractorName = "VertexFaceRepulsionStiffness", EditCondition = "bUseTetRepulsionConstraints && !bAppendToExisting", EditConditionHides))` — Stiffness for repulsion constraints
- L144 _private member_ `int32 VertexFaceMaxRepulsionIters = 1;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties", Meta = (ClampMin = "1", UIMax = "5", InteractorName = "VertexFaceRepulsionStiffness", EditCondition = "bUseTetRepulsionConstraints && !bAppendToExisting", EditConditionHides))` — Max Number of iterations to apply (per solver iteration). Helps resolve more collisions, but at additional compute cost.
- L148 _private member_ `TArray<FChaosClothAssetSimulationClothVertexFaceSpringConstructionSet> ConstructionSets;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Cloth Vertex Face Spring Construction", Meta = (SkipInDisplayNameChain))` — Construction data for procedurally generating constraints.
- L152 _private member_ `bool bUseThicknessMap = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction")` — Use Thickness rather than current rest collection state to determine rest lengths.
- L156 _private member_ `FChaosClothAssetWeightedValue Thickness = { false, 0.5f, 0.5f, TEXT("Sprin` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", EditCondition = "bUseThicknessMap", EditConditionHides))` — Thickness for calculating rest lengths. Rest length will be combined value of thickness on both end points.
- L160 _private member_ `float RestLengthScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", Meta = (ClampMin = "0", UIMax = "10", EditCondition = "!bUseThicknessMap", EditConditionHides))` — Scale applied to the rest lengths of the springs. A value of 1 will preserve the distance in the rest collection.
- L164 _private member_ `FDataflowFunctionProperty GenerateConstraints;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Construction", Meta = (DisplayName = "Generate Constraints"))` — Click on this button to generate constraints from the construction data.
- L168 _private member_ `TArray<int32> SourceVertices;` — `UPROPERTY()` — Raw constraint end point data. Modify at your own risk.
- L172 _private member_ `TArray<FIntVector> TargetVertices;` — `UPROPERTY()` — Raw constraint end point data. Modify at your own risk.
- L176 _private member_ `TArray<FVector3f> TargetWeights;` — `UPROPERTY()` — Raw constraint end point data. Modify at your own risk.
- L180 _private member_ `TArray<float> RestLengths;` — `UPROPERTY()` — Raw constraint rest length data. Modify at your own risk.

#### struct `FChaosClothAssetSimulationClothVertexFaceSpringConfigNode::FConstructionSetData`  
`struct FConstructionSetData`  
_L105-115_
- L107 _public member_ `FName SourceSetName;`
- L108 _public member_ `FName TargetSetName;`
- L109 _public member_ `EChaosClothAssetClothVertexFaceSpringConstructionMethod ConstructionMethod;`
- L110 _public member_ `bool bFlipRayNormal;`
- L111 _public member_ `float MaxRayLength;`
- L112 _public member_ `float Radius;`
- L113 _public member_ `int32 DisableNeighborDistance = 2;`
- L114 _public member_ `bool bSkipZeroVolumeTets;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationClothVertexSpringConfigNode.h` (Public)


#### enum `EChaosClothAssetClothVertexSpringConstructionMethod`  
`enum struct EChaosClothAssetClothVertexSpringConstructionMethod`  
_L13-21_
- reflection: `UENUM()`
- desc: Method for generating springs between source to target vertices
- L16 _public enumerator_ `SourceToClosestTarget` — For each source, connect the closest target
- L18 _public enumerator_ `ClosestSourceToClosestTarget` — For each source/target, connect the closest vertex in the other set.
- L20 _public enumerator_ `AllSourceToAllTargets` — For each source/target, connect to all vertices in the other set.

#### struct `FChaosClothAssetSimulationClothVertexSpringConstructionSet`  
`struct FChaosClothAssetSimulationClothVertexSpringConstructionSet`  
_L25-40_
- reflection: `USTRUCT()`
- desc: Data to procedurally generate ClothVertexSpring Constraints.
- L31 _public member_ `FChaosClothAssetConnectableIStringValue SourceVertexSelection = { TEXT("Sourc` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Construction")` — Source Vertex Set
- L35 _public member_ `FChaosClothAssetConnectableIStringValue TargetVertexSelection = { TEXT("Targe` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Construction")` — Target Vertex Set
- L39 _public member_ `EChaosClothAssetClothVertexSpringConstructionMethod ConstructionMethod = EChaosClothAssetClothVertexSpringConstructionMethod::SourceToClosestTarget;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Construction")` — Construction method used to connect sources and targets

#### struct `FChaosClothAssetSimulationClothVertexSpringConfigNode`  
`struct FChaosClothAssetSimulationClothVertexSpringConfigNode final : public FChaosClothAssetSimulationBaseConfigNode`  
_L44-125_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Node for creating vertex-vertex constraints and setting their simulation properties.
- L55 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L56 _private function_ `virtual bool CanAddPin() const override`
- L60 _private function_ `virtual bool CanRemovePin() const override`
- L64 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L65 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L66 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L70 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L71 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`
- L74 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetSourceConnectionReference(int32 Index) const;`
- L75 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetTargetConnectionReference(int32 Index) const;`
- L77 _private member_ `static constexpr int32 NumRequiredInputs = 1;` — non-construction set inputs
- L78 _private member_ `static constexpr int32 NumInitialConstructionSets = 1;`
- L80 _private prototype_ `void CreateConstraints(UE::Dataflow::FContext& Context);`
- L88 _private prototype_ `TArray<FConstructionSetData> GetConstructionSetData(UE::Dataflow::FContext& Context) const;`
- L92 _private member_ `bool bAppendToExisting = false;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Face Spring Properties")` — Append to existing set of constraints. Stiffnesses inherited from existing constraints.
- L96 _private member_ `FVector2f VertexSpringExtensionStiffness = { 100.f, 100.f };` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", InteractorName = "VertexSpringExtensionStiffness", EditCondition = "!bAppendToExisting", EditConditionHides))` — Extension Stiffness is the spring stiffness applied when the spring is currently longer than its rest length. This is a low-high range, but there are currently no ways to author per-spring stiffnesses, so only Low is used in practice.
- L100 _private member_ `FVector2f VertexSpringCompressionStiffness = { 100.f, 100.f };` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", InteractorName = "VertexSpringCompressionStiffness", EditCondition = "!bAppendToExisting", EditConditionHides))` — Compression Stiffness is the spring stiffness applied when the spring is currently shorter than its rest length. This is a low-high range, but there are currently no ways to author per-spring stiffnesses, so only Low is used in practice.
- L104 _private member_ `FVector2f VertexSpringDamping = { 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000", InteractorName = "VertexSpringDamping", EditCondition = "!bAppendToExisting", EditConditionHides))` — This damping is the relative to critical damping. This is a low-high range, but there are currently no ways to author per-spring stiffnesses, so only Low is used in practice.
- L108 _private member_ `TArray<FChaosClothAssetSimulationClothVertexSpringConstructionSet> ConstructionSets;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Cloth Vertex Spring Construction", Meta = (SkipInDisplayNameChain))` — Construction data for procedurally generating constraints.
- L112 _private member_ `float RestLengthScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Construction", Meta = (ClampMin = "0", UIMax = "10"))` — Scale applied to the rest lengths of the springs. A value of 1 will preserve the distance in the rest collection.
- L116 _private member_ `FDataflowFunctionProperty GenerateConstraints;` — `UPROPERTY(EditAnywhere, Category = "Cloth Vertex Spring Construction", Meta = (DisplayName = "Generate Constraints"))` — Click on this button to generate constraints from the construction data.
- L120 _private member_ `TArray<FIntVector2> ConstraintVertices;` — `UPROPERTY(EditAnywhere, Category = "Advanced")` — Raw constraint end point data. Modify at your own risk.
- L124 _private member_ `TArray<float> RestLengths;` — `UPROPERTY(EditAnywhere, Category = "Advanced")` — Raw constraint rest length data. Modify at your own risk.

#### struct `FChaosClothAssetSimulationClothVertexSpringConfigNode::FConstructionSetData`  
`struct FConstructionSetData`  
_L82-87_
- L84 _public member_ `FName SourceSetName;`
- L85 _public member_ `FName TargetSetName;`
- L86 _public member_ `EChaosClothAssetClothVertexSpringConstructionMethod ConstructionMethod;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationCollisionConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationCollisionConfigNode`  
`struct FChaosClothAssetSimulationCollisionConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-105_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Physics mesh collision properties configuration node.
- L24 _public member_ `FChaosClothAssetWeightedValue FrictionCoefficientWeighted = { true, UE::Chaos::ClothAsset::FDefaultFabric::Friction, UE::Chaos::ClothAsset::FDefaultFabric::Friction, TEXT("FrictionCoe` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", DisplayName = "Friction Coefficient", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", InteractorName = "FrictionCoefficient"))` — Friction coefficient for cloth - collider interaction. Currently only Skinned Triangle Meshes use the weighted value. All other collisions only use the Low value.
- L29 _public member_ `bool bEnableSimpleColliders = true;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", Meta = (InteractorName = "EnableSimpleColliders"))` — Enable colliding against any simple (e.g., capsules, convexes, spheres, boxes) colliders..
- L33 _public member_ `bool bUsePlanarConstraintForSimpleColliders = false;` — `UPROPERTY(EditAnywhere, Category="Collision Properties", Meta = (EditCondition = "bEnableSimpleColliders", InteractorName = "UsePlanarConstraintForSimpleColliders"))` — Use Planar Constraints for simple (e.g., capsules, convexes, spheres, boxes) colliders when doing multiple iterations. Planar constraints are cheaper than full collision detection, but less accurate.
- L37 _public member_ `bool bEnableComplexColliders = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Collision Properties", Meta = (InteractorName = "EnableComplexColliders"))` — Enable colliding against any complex (e.g., SkinnedLevelSet, MLLevelSet) colliders.
- L41 _public member_ `bool bUsePlanarConstraintForComplexColliders = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Collision Properties", Meta = (EditCondition = "bEnableComplexColliders", InteractorName = "UsePlanarConstraintForComplexColliders"))` — Use Planar Constraints for complex (e.g., SkinnedLevelSet, MLLevelSet) colliders when doing multiple iterations. Planar constraints are cheaper than full collision detection, but less accurate.
- L45 _public member_ `bool bEnableSkinnedTriangleMeshCollisions = true;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", Meta = (InteractorName = "EnableSkinnedTriangleMeshCollisions"))` — Enable colliding against any Skinned Triangle Mesh colliders.
- L49 _public member_ `bool bUseSelfCollisionSubstepsForSkinnedTriangleMeshes = true;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", Meta = (EditCondition = "bEnableSkinnedTriangleMeshCollisions", InteractorName = "UseSelfCollisionSubstepsForSkinnedTriangleMeshes"))` — Use 'NumSelfCollisionSubsteps' (Located on SimulationSolverConfig) to also control Skinned Triangle Mesh collision updates
- L53 _public member_ `FChaosClothAssetWeightedValue ClothCollisionThicknessImported = { true, UE::Chaos::ClothAsset::FDefaultFabric::ClothCollisionThickness, UE::Chaos::ClothAsset::FDefaultFabric::ClothCollisionThickness, TEXT("ClothCollis` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", DisplayName = "Cloth Collision Thickness", Meta = (InteractorName = "ClothCollisionThickness"))` — Thickness added to the cloth when colliding against collision shapes.
- L59 _public member_ `float ProximityStiffness = 100.f;` — `UE_DEPRECATED(5.8, "This property is not used.")` — `UPROPERTY()` — Stiffness for proximity repulsion forces (Force-based solver only). Units = kg cm/ s^2 (same as XPBD springs)
- L66 _public member_ `bool bUseCCD = false;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", Meta = (InteractorName = "UseCCD"))` — Use continuous collision detection (CCD) to prevent any missed collisions between fast moving particles and colliders. This has a negative effect on performance compared to when resolving collision without using CCD.
- L78 _public member_ `FChaosClothAssetWeightedValueNonAnimatable InnerCollisionThickness = { 0.f, 0.f, TEXT("InnerCollisi` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", DisplayName = "Inner Collision Thickness (Experimental)", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", EditCondition = "bUseCCD == false"))` — Experimental feature, use at your own risk. Improve collision behavior by running the CCD code path, but only where particles penetration exceeds the given inner thickness value. This is using a faster collision code path than CCD, but unlike CCD it does not resolve fast moving objects. Use an inner thickness that is about a few centimeters to start with, up to a quarter of your collider diameter for best results. If the inner thickness is too large (e.g. more than half the collider's diameter), the CCD code path won't ever be activated. This property can be used in conjunction with a weight map to selectively allow certain particles to use the extra calculations or to locally adjust the effect. Set both the low and high values to 0 to disable.
- L82 _public member_ `FChaosClothAssetImportedFloatValue FrictionCoefficientImported = { UE::Chaos::ClothAsset::FDefaultFabric::Friction };` — `UE_DEPRECATED(5.6, "Use FrictionCoefficientWeighted instead.")` — `UPROPERTY()`
- L86 _public member_ `FChaosClothAssetWeightedValue ClothCollisionThickness = { true, 0.f, 0.f, TEXT("ClothCollis` — `UE_DEPRECATED(5.7, "Use ClothCollisionThicknessImported instead.")` — `UPROPERTY(Meta = (DataflowSkipConnection))`
- L88 _public prototype_ `FChaosClothAssetSimulationCollisionConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L90 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L93 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L97 _private member_ `static constexpr float CollisionThicknessDeprecatedDefault = 1.0f;`
- L99 _private member_ `float CollisionThickness_DEPRECATED = CollisionThicknessDeprecatedDefault;` — `UPROPERTY()`
- L101 _private member_ `static constexpr float FrictionCoefficientDeprecatedDefault = 0.8f;`
- L103 _private member_ `float FrictionCoefficient_DEPRECATED = FrictionCoefficientDeprecatedDefault;` — `UPROPERTY()`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationConfigNodePropertyTypes.h` (Public)


#### enum `EChaosClothAssetRestAngleConstructionType`  
`enum class EChaosClothAssetRestAngleConstructionType : uint8`  
_L11-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `Use3DRestAngles = (uint8)Chaos::Softs::FPBDBendingConstraintsBase::ERestAngleConstructionType::Use3DRestAngles` — Calculate rest angles using the 3D draped space simulation mesh.
- L16 _public enumerator_ `FlatnessRatio = (uint8)Chaos::Softs::FPBDBendingConstraintsBase::ERestAngleConstructionType::FlatnessRatio` — Calculate rest angles using the FlatnessRatio property.
- L18 _public enumerator_ `RestAngle = (uint8)Chaos::Softs::FPBDBendingConstraintsBase::ERestAngleConstructionType::ExplicitRestAngles` — Calculate rest angles using the RestAngle property.

#### enum `EChaosClothAssetBendingConstraintType`  
`enum class EChaosClothAssetBendingConstraintType : uint8`  
_L22-28_
- reflection: `UENUM()`
- L25 _public enumerator_ `FacesSpring` — Add a spring in between the opposite vertices of the adjacent faces
- L27 _public enumerator_ `HingeAngles` — Add an angular constraint in between the 2 faces

#### enum `EChaosClothAssetConstraintDistributionType`  
`enum class EChaosClothAssetConstraintDistributionType : uint8`  
_L31-37_
- reflection: `UENUM()`
- L34 _public enumerator_ `Anisotropic` — Having a separate stiffness along the warp, weft, bias direction
- L36 _public enumerator_ `Isotropic` — Uniform stiffness in all directions

#### enum `EChaosClothAssetConstraintSolverType`  
`enum class EChaosClothAssetConstraintSolverType : uint8`  
_L40-46_
- reflection: `UENUM()`
- L43 _public enumerator_ `XPBD` — Physically based PBD with compliance
- L45 _public enumerator_ `PBD` — PBD style with no damping/stiffness

#### enum `EChaosClothAssetConstraintOverrideType`  
`enum class EChaosClothAssetConstraintOverrideType : uint8`  
_L49-57_
- reflection: `UENUM()`
- L52 _public enumerator_ `None` — Do not override
- L54 _public enumerator_ `Override` — Override any existing values with this new value.
- L56 _public enumerator_ `Multiply` — Multiply any existing values with this new value.

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationDampingConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationDampingConfigNode`  
`struct FChaosClothAssetSimulationDampingConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-64_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Damping properties configuration node.
- L28 _public member_ `EChaosSoftsLocalDampingSpace LocalDampingSpace = EChaosSoftsLocalDampingSpace::CenterOfMass;` — `UPROPERTY(EditAnywhere, Category = "Damping Properties", Meta = (InteractorName = "LocalDampingSpace"))` — The space in which local damping is calculated. Center of mass adds the expense of calculating the center of mass.
- L37 _public member_ `float LocalDampingLinearCoefficient = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Damping Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "LocalDampingLinearCoefficient"))` — The amount of local linear damping applied to the cloth velocities. This type of damping only damps individual deviations of the particles velocities from the global linear motion. It makes the cloth deformations more cohesive and reduces jitter without affecting the overall movement. It can also produce synchronization artifacts where part of the cloth mesh are disconnected (which might well be desirable, or not).
- L46 _public member_ `float LocalDampingAngularCoefficient = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Damping Properties", Meta = (EditCondition = "bEnableLocalDampingAngular", UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "LocalDampingAngularCoefficient"))` — The amount of local angular damping applied to the cloth velocities. This type of damping only damps individual deviations of the particles velocities from the global angular motion. It makes the cloth deformations more cohesive and reduces jitter without affecting the overall movement. It can also produce synchronization artifacts where part of the cloth mesh are disconnected (which might well be desirable, or not).
- L48 _public prototype_ `FChaosClothAssetSimulationDampingConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L50 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L52 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L56 _private member_ `static constexpr float DeprecatedDampingCoefficientValue = -1.f;` — This is outside the settable range when it wasn't deprecated.
- L58 _private member_ `float DampingCoefficient_DEPRECATED = DeprecatedDampingCoefficientValue;` — `UPROPERTY()`
- L61 _private member_ `float LocalDampingCoefficient_DEPRECATED = DeprecatedDampingCoefficientValue;` — `UPROPERTY()`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationDefaultConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationDefaultConfigNode`  
`struct FChaosClothAssetSimulationDefaultConfigNode : public FDataflowNode`  
_L16-42_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Add default simulation properties to the cloth collection in the format of the skeletal mesh cloth editor.
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L27 _public member_ `TObjectPtr<UChaosClothConfig> SimulationConfig;` — `UPROPERTY(EditAnywhere, Instanced, NoClear, Category = "Simulation Default Config")` — Cloth Simulation Properties.
- L31 _public member_ `TObjectPtr<UChaosClothSharedSimConfig> SharedSimulationConfig;` — `UPROPERTY(EditAnywhere, Instanced, NoClear, Category = "Simulation Default Config")` — Cloth Shared Simulation Properties.
- L33 _public prototype_ `FChaosClothAssetSimulationDefaultConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L37 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L38 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L41 _private member_ `UObject* OwningObject;` — For backward compatibility when null SimulationConfig and SharedSimulationConfig are reloaded

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationGravityConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationGravityConfigNode`  
`struct FChaosClothAssetSimulationGravityConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L10-44_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Gravity properties configuration node.
- L22 _public member_ `FChaosClothAssetWeightedValue GravityScaleWeighted = {true, 1.f, 1.f, TEXT("Grav` — `UPROPERTY(EditAnywhere, Category = "Gravity Properties", DisplayName = "Gravity Scale", Meta = (UIMin = "0", UIMax = "10", EditCondition = "!bUseGravityOverride", InteractorName = "GravityScale"))` — Scale factor applied to the world gravity and also to the clothing simulation interactor gravity. Does not affect the gravity if set using the override below.
- L26 _public member_ `FChaosClothAssetImportedVectorValue GravityOverrideImported = {UE::Chaos::ClothAsset::FDefaultSolver::Gravity};` — `UPROPERTY(EditAnywhere, Category = "Gravity Properties", DisplayName = "Gravity Override", Meta = (UIMin = "0", UIMax = "10", EditCondition = "bUseGravityOverride", InteractorName = "GravityOverride"))` — The gravitational acceleration vector [cm/s^2].
- L28 _public prototype_ `FChaosClothAssetSimulationGravityConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L30 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L37 _private member_ `float GravityScale_DEPRECATED = 1.f;` — `UPROPERTY()`
- L40 _private member_ `FVector3f GravityOverride_DEPRECATED = UE::Chaos::ClothAsset::FDefaultSolver::Gravity;` — `UPROPERTY()` — TODO: Should we make this a S.I. unit?
- L43 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationLongRangeAttachmentConfigNode.h` (Public)


#### struct `FChaosClothAssetTetherGenerationSet`  
`struct FChaosClothAssetTetherGenerationSet`  
_L10-25_
- reflection: `USTRUCT()`
- L18 _public member_ `FChaosClothAssetConnectableIStringValue CustomFixedEndSet = { TEXT("Kinem` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties")` — Set of Kinematic vertices that tethers will attach to. Will be intersected with (node level) FixedEndSet.
- L24 _public member_ `FChaosClothAssetConnectableIStringValue CustomDynamicEndSet = { TEXT("Dynam` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties")` — Set of Dynamic vertices that will attach to the closest vertex in FixedEndSelection. (Node level) FixedEndSet will be excluded.

#### struct `FChaosClothAssetSimulationLongRangeAttachmentConfigNode_v2`  
`struct FChaosClothAssetSimulationLongRangeAttachmentConfigNode_v2 : public FChaosClothAssetSimulationBaseConfigNode`  
_L29-108_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Long range attachment constraint property configuration node.
- L55 _public member_ `FChaosClothAssetWeightedValue TetherScale = { true, 1.f, 1.f, TEXT("Tethe` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties", Meta = (UIMin = "1.", UIMax = "1.1", ClampMin = "0.01", ClampMax = "10", InteractorName = "TetherScale"))` — The limit scale of the long range attachment constraints (aka tether limit). If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L63 _public member_ `bool bUseGeodesicTethers = true;` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties")` — Use geodesic instead of euclidean distance calculations for the Long Range Attachment constraint, which is slower at setup but more accurate at establishing the correct position and length of the tethers, and therefore is less prone to artifacts during the simulation.
- L76 _public member_ `bool bEnableCustomTetherGeneration = false;` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties")` — Enable more granular control over tether generation via the custom selection sets CustomTetherData. When using custom tether generation, FixedEndSet is still required to contain all kinematic vertices. It is also not possible to provide CustomFixedEndSet indices that are not part of the FixedEndSet. Similarly, it is not possible to provide CustomDynamicEndSet indices that are part of the FixedEndSet. Any fixed tether end provided to a CustomFixedEndSet must be directly connected to a dynamic particles group (island) where at least one of the CustomDynamicEndSet particles resides in order to be valid. When enabling this option, the default tether generation is completely disabled (dynamic particles are no longer connected to their closest kinematic vertex as defined by FixedEndSet).
- L83 _public member_ `FChaosClothAssetConnectableIStringValue FixedEndSet = { TEXT("Kinem` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties")` — The name of the vertex selection set used as fixed tether ends. When using custom tether generation, this set is still needed to contain all kinematic vertices.
- L87 _public member_ `TArray<FChaosClothAssetTetherGenerationSet> CustomTetherData;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Long Range Attachment Properties", Meta = (EditCondition = "bEnableCustomTetherGeneration", SkipInDisplayNameChain))` — Pairs of vertex selections used for custom tether generation. See EnableCustomTetherGeneration.
- L89 _public prototype_ `FChaosClothAssetSimulationLongRangeAttachmentConfigNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L92 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L94 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`
- L96 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L97 _private function_ `virtual bool CanAddPin() const override`
- L98 _private function_ `virtual bool CanRemovePin() const override`
- L99 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L100 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L101 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L103 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetFixedEndConnectionReference(int32 Index) const;`
- L104 _private prototype_ `UE::Dataflow::TConnectionReference<FString> GetDynamicEndConnectionReference(int32 Index) const;`
- L106 _private member_ `static constexpr int32 NumRequiredInputs = 4;` — non-filter set inputs
- L107 _private member_ `static constexpr int32 NumInitialCustomTetherSets = 1;`

#### struct `FChaosClothAssetSimulationLongRangeAttachmentConfigNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetSimulationLongRangeAttachmentConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L112-158_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.5"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Long range attachment constraint property configuration node.
- L129 _public member_ `FChaosClothAssetWeightedValue TetherStiffness = { true, 1.f, 1.f, TEXT("Tethe` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "TetherStiffness"))` — The tethers' stiffness of the long range attachment constraints. The long range attachment connects each of the cloth particles to its closest fixed point with a spring constraint. This can be used to compensate for a lack of stretch resistance when the iterations count is kept low for performance reasons. Can lead to an unnatural pull string puppet like behavior. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L138 _public member_ `FChaosClothAssetWeightedValue TetherScale = { true, 1.f, 1.f, TEXT("Tethe` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties", Meta = (UIMin = "1.", UIMax = "1.1", ClampMin = "0.01", ClampMax = "10", InteractorName = "TetherScale"))` — The limit scale of the long range attachment constraints (aka tether limit). If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L146 _public member_ `bool bUseGeodesicTethers = true;` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties")` — Use geodesic instead of euclidean distance calculations for the Long Range Attachment constraint, which is slower at setup but more accurate at establishing the correct position and length of the tethers, and therefore is less prone to artifacts during the simulation.
- L150 _public member_ `FString FixedEndWeightMap = TEXT("Max` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment Properties", Meta = (DataflowInput))` — The name of the weight map used to calculate fixed tether ends. All vertices with weight = 0 will be considered fixed.
- L152 _public prototype_ `FChaosClothAssetSimulationLongRangeAttachmentConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L155 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L157 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationMassConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationMassConfigNode`  
`struct FChaosClothAssetSimulationMassConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-67_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Mass properties configuration node.
- L28 _public member_ `FChaosClothAssetWeightedValueNonAnimatable UniformMassWeighted = {0.00015f, 0.00015f, TEXT("Unif` — `UPROPERTY(EditAnywhere, Category = "Mass Properties", DisplayName = "Uniform Mass", Meta = (UIMin = "0.000001", UIMax = "0.001", ClampMin = "0", EditCondition = "MassMode == EClothMassMode::UniformMass", EditConditionHides))` — The value used when the Mass Mode is set to Uniform Mass.
- L32 _public member_ `float TotalMass = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Mass Properties", Meta = (UIMin = "0.001", UIMax = "10", ClampMin = "0", EditCondition = "MassMode == EClothMassMode::TotalMass", EditConditionHides))` — The value used when Mass Mode is set to TotalMass.
- L45 _public member_ `FChaosClothAssetWeightedValueNonAnimatable DensityWeighted = {0.35f, 0.35f, TEXT("Density"),` — `UPROPERTY(EditAnywhere, Category = "Mass Properties", DisplayName = "Density", meta = (UIMin = "0.001", UIMax = "1", ClampMin = "0", EditCondition = "MassMode == EClothMassMode::Density", EditConditionHides))` — Density in kg/m^2. Melton Wool: 0.7 Heavy leather: 0.6 Polyurethane: 0.5 Denim: 0.4 Light leather: 0.3 Cotton: 0.2 Silk: 0.1
- L49 _public member_ `float MinPerParticleMass = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "Mass Properties", meta = (ClampMin = "0"))` — Calculated particle masses will be clamped to this minimum value (or 1e-8, whichever is larger).
- L51 _public prototype_ `FChaosClothAssetSimulationMassConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L53 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L60 _private member_ `float UniformMass_DEPRECATED = 0.00015f;` — `UPROPERTY()`
- L63 _private member_ `float Density_DEPRECATED = 0.35f;` — `UPROPERTY()`
- L66 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationMaxDistanceConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationMaxDistanceConfigNode`  
`struct FChaosClothAssetSimulationMaxDistanceConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-54_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Maximum distance constraint property configuration node.
- L31 _public member_ `FChaosClothAssetConnectableIStringValue InKinematic = { TEXT("") };` — `UPROPERTY(VisibleAnywhere, Category = "MaxDistance Properties")` — Selection set of SimVertices3D that should be made kinematic regardless of the MaxDistance map value.
- L39 _public member_ `FString KinematicVertices3D;` — `UPROPERTY(VisibleAnywhere, Category = "MaxDistance Properties", Meta = (DataflowOutput))` — The name of the kinematic vertex set generated by this node. This is the union of InKinematic and any vertices which are below the solver max distance threshold. The name of this set cannot be changed and is only provided for further tweaking.
- L41 _public prototype_ `FChaosClothAssetSimulationMaxDistanceConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L44 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L45 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`
- L47 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L50 _private prototype_ `virtual bool CanDebugDraw() const override;`
- L51 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L52 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationMorphTargetConfigNode.h` (Public)


#### struct `FChaosClothAssetMorphTargetSelection`  
`struct FChaosClothAssetMorphTargetSelection`  
_L11-21_
- reflection: `USTRUCT()`
- desc: The active sim morph target.
- L17 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category ="Simulation Morph Target Properties", meta = (InteractorName = "ActiveMorphTarget"))` — Morph target name
- L20 _public member_ `float Weight = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Simulation Morph Target Properties", meta = (InteractorName = "ActiveMorphTarget"))` — Morph target weight

#### struct `FChaosClothAssetSimulationMorphTargetConfigNode`  
`struct FChaosClothAssetSimulationMorphTargetConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L25-41_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Simulation Morph Target configuration node. This node is necessary to set sim morph targets (e.g., via BP interactor)
- L37 _public prototype_ `FChaosClothAssetSimulationMorphTargetConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L40 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationMultiResConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationMultiResConfigNode`  
`struct UE_DEPRECATED(5.8, "MultiRes Constraints have been deprecated.")FChaosClothAssetSimulationMultiResConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L10-45_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated=5.8, Experimental))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Experimental Solver multires configuration node.
- L23 _public member_ `bool bIsCoarseMultiResLOD = false;` — `UPROPERTY(EditAnywhere, Category = "Multi-resolution", meta = (EditCondition = "!bIsFineLOD", InteractorName = "IsCoarseMultiResLOD"))` — This LOD is a coarse LOD for a finer LOD's multi-res simulation.
- L27 _public member_ `int32 MultiResCoarseLODIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Multi-resolution", meta = (EditCondition = "bIsFineLOD", EditConditionHides, InteractorName = "MultiResCoarseLODIndex"))` — Index of the coarse LOD for multi-res simulation. That LOD also needs a Multi Res Config node with "Is Coarse Multi Res LOD" = true.
- L31 _public member_ `bool bMultiResUseXPBD = false;` — `UPROPERTY(EditAnywhere, Category = "Multi-resolution", meta = (EditCondition = "bIsFineLOD", EditConditionHides, InteractorName = "MultiResUseXPBD"))` — Use XPBD-style constraints
- L35 _public member_ `FChaosClothAssetWeightedValue MultiResStiffness = {true, 1.f, 1.f};` — `UPROPERTY(EditAnywhere, Category = "Multi-resolution", meta = (UIMin = "0", UIMax = "100000", ClampMin = "0", ClampMax = "100000", EditCondition = "bIsFineLOD", EditConditionHides, InteractorName = "MultiResStiffness"))` — MultiRes Spring Stiffness
- L39 _public member_ `FChaosClothAssetWeightedValue MultiResVelocityTargetStiffness = { true, 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Multi-resolution", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bIsFineLOD && !bMultiResUseXPBD", EditConditionHides, InteractorName = "MultiResVelocityTargetStiffness"))` — MultiRes Velocity Target Spring Stiffness (non-XPBD only)
- L41 _public prototype_ `FChaosClothAssetSimulationMultiResConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L44 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationPBDAreaSpringConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationPBDAreaSpringConfigNode`  
`struct FChaosClothAssetSimulationPBDAreaSpringConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-31_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Area spring constraint property configuration node.
- L27 _public prototype_ `FChaosClothAssetSimulationPBDAreaSpringConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L30 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationPBDBendingElementConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationPBDBendingElementConfigNode`  
`struct FChaosClothAssetSimulationPBDBendingElementConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-78_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Bending element constraint property configuration node.
- L33 _public member_ `FChaosClothAssetWeightedValueNonAnimatable FlatnessRatio = { 0.f, 0.f, TEXT("Flatn` — `UPROPERTY(EditAnywhere, Category = "PBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "RestAngleType == EChaosClothAssetRestAngleConstructionType::FlatnessRatio"))` — Calculate rest angles as a ratio between completely flat and whatever is the 3D rest angle. When FlatnessRatio = 0, this is equivalent to "Use3DRestAngles". When FlatnessRatio = 1, the rest angle will be 0 (completely flat). If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L44 _public member_ `FChaosClothAssetWeightedValueNonAnimatable RestAngle = { 0.f, 0.f, TEXT("RestA` — `UPROPERTY(EditAnywhere, Category = "PBDBendingElement Properties", Meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180", EditCondition = "RestAngleType == EChaosClothAssetRestAngleConstructionType::RestAngle"))` — Set rest angles to be the explicit value set here (in degrees). 0 = Flat, Positive values fold away from the edge normal, Negative values fold toward the edge normal. When converting vertex weight values to edge values, the value with the smallest absolute value is selected. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L53 _public member_ `FChaosClothAssetWeightedValue BendingElementStiffness = { true, 1.f, 1.f, TEXT("Bendi` — `UPROPERTY(EditAnywhere, Category = "PBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The Stiffness of the bending elements constraints. Increase the iteration count for stiffer materials. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L60 _public member_ `float BucklingRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "PBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Once the element has bent such that it's folded more than this ratio from its rest angle ("buckled"), switch to using Buckling Stiffness instead of BendingElement Stiffness. When Buckling Ratio = 0, the Buckling Stiffness will never be used. When BucklingRatio = 1, the Buckling Stiffness will be used as soon as its bent past its rest configuration.
- L72 _public member_ `FChaosClothAssetWeightedValue BucklingStiffness = { true, 0.9f, 0.9f, TEXT("Buckl` — `UPROPERTY(EditAnywhere, Category = "PBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "BucklingRatio != 0"))` — The stiffness after buckling. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L74 _public prototype_ `FChaosClothAssetSimulationPBDBendingElementConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L77 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationPBDBendingSpringConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationPBDBendingSpringConfigNode`  
`struct FChaosClothAssetSimulationPBDBendingSpringConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-31_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Bending spring constraint property configuration node.
- L27 _public prototype_ `FChaosClothAssetSimulationPBDBendingSpringConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L30 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationPBDEdgeSpringConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationPBDEdgeSpringConfigNode`  
`struct FChaosClothAssetSimulationPBDEdgeSpringConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-31_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Edge spring constraint property configuration node.
- L27 _public prototype_ `FChaosClothAssetSimulationPBDEdgeSpringConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L30 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationPressureConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationPressureConfigNode`  
`struct FChaosClothAssetSimulationPressureConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-30_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Pressure properties configuration node.
- L26 _public prototype_ `FChaosClothAssetSimulationPressureConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationResolveExtremeDeformationConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationResolveExtremeDeformationConfigNode`  
`struct FChaosClothAssetSimulationResolveExtremeDeformationConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L10-38_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Resolve extreme deformation properties configuration node.
- L22 _public member_ `float ExtremeDeformationEdgeRatioThreshold = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Edge Ratio Threshold Properties", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", InteractorName = "ExtremeDeformationEdgeRatioThreshold"))` — Edges deformed above this threshold will trigger position reset.
- L29 _public member_ `FString ExtremeDeformationVertexSelection = GET_MEMBER_NAME_STRING_CHECKED(FChaosClothAssetSimulationResolveExtremeDeformationConfigNode, ExtremeDeformationVertexSelection);` — `UPROPERTY(VisibleAnywhere, Category = "Output Selection Name", Meta = (DataflowOutput))` — The name of the extreme deformation vertex set generated by this node. The name of this set cannot be changed and is only provided for further tweaking.
- L31 _public prototype_ `FChaosClothAssetSimulationResolveExtremeDeformationConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L34 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L36 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`
- L37 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationSelfCollisionConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationSelfCollisionConfigNode_v2`  
`struct FChaosClothAssetSimulationSelfCollisionConfigNode_v2 final : public FChaosClothAssetSimulationBaseConfigNode`  
_L13-78_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Self-collision repulsion forces (point-face) properties configuration node. Note that the kinematic collider has been deprecated in favor of SkinnedTriangleMesh Physics Asset bodies
- L26 _private member_ `bool bUseSelfCollisions = true;` — `UPROPERTY(VisibleAnywhere, Category = "Self-Collision Properties", meta = (InteractorName = "UseSelfCollisions"))` — Activating this node will enable self collisions.
- L30 _private member_ `FChaosClothAssetWeightedValue SelfCollisionThickness = { true, UE::Chaos::ClothAsset::FDefaultFabric::SelfCollisionThickness, UE::Chaos::ClothAsset::FDefaultFabric::SelfCollisionThickness, TEXT("SelfCollisi` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", InteractorName = "SelfCollisionThickness"))` — The self collision offset per side. Total thickness of cloth is 2x this value.
- L35 _private member_ `float SelfCollisionStiffness = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "SelfCollisionStiffness"))` — The stiffness of the springs used to control self collision.
- L39 _private member_ `FChaosClothAssetImportedFloatValue SelfCollisionFriction = { UE::Chaos::ClothAsset::FDefaultFabric::SelfFriction };` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "SelfCollisionFriction"))` — Friction coefficient for cloth - cloth interaction.
- L43 _private member_ `int32 SelfCollisionDisableNeighborDistance = 5;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (UIMin = "1", UIMax = "5", ClampMin = "1", ClampMax = "10"))` — Disabled neighbor collision ring. Collisions are disabled between vertices within this N-ring connectivity distance.
- L50 _private member_ `FChaosClothAssetConnectableIStringValue SelfCollisionLayers = { TEXT("SelfCollisi` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (InteractorName = "SelfCollisionLayers"))` — Self collision layers face int map. Generate this map using the SelectionsToIntMap node with SimFace Selections. Faces labeled with -1 will collide normally without any layering behavior. Faces labeled with any other number will keep higher layer numbers outside lower layer numbers (outside = front facing normal direction).
- L54 _private member_ `FChaosClothAssetConnectableIStringValue SelfCollisionDisabledFaces = { TEXT("SelfC` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (InteractorName = "SelfCollisionDisabledFaces"))` — Sim face selection set of faces which should not self collide
- L58 _private member_ `bool bUseSelfIntersections = true;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (InteractorName = "UseSelfIntersections"))` — Enable self intersection resolution. This will try to fix any cloth intersections that are not handled by collision repulsions. Can be expensive.
- L62 _private member_ `bool bUseGlobalIntersectionAnalysis = true;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (EditCondition = "bUseSelfIntersections", InteractorName = "UseGlobalIntersectionAnalysis"))` — Do global intersection analysis to determine the correct normals for the collision springs
- L67 _private member_ `bool bUseContourMinimization = true;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (EditCondition = "bUseSelfIntersections", InteractorName = "UseContourMinimization"))` — Do a step of contour minimization at the beginning of the timestep. Contour minimization will attempt to resolve intersections by shortening the intersection edge. Helpful with open intersections that global intersection analysis can't fix.
- L72 _private member_ `int32 NumContourMinimizationPostSteps = 0;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (ClampMin = "0", EditCondition = "bUseSelfIntersections", InteractorName = "NumContourMinimizationPostSteps"))` — Number of post timestep contour minimization steps to do. (Very Expensive!) Contour minimization will attempt to resolve intersections by shortening the intersection edge.Helpful with open intersections that global intersection analysis can't fix.
- L76 _private member_ `bool bUseGlobalPostStepContours = true;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (EditCondition = "bUseSelfIntersections && NumContourMinimizationPostSteps > 0", InteractorName = "UseGlobalPostStepContours"))` — Use global contour gradients when doing post timestep contour minimization
- L77 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

#### struct `FChaosClothAssetSimulationSelfCollisionConfigNode`  
`struct UE_DEPRECATED(5.7, "Use the newer version of this node instead.") FChaosClothAssetSimulationSelfCollisionConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L82-187_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = 5.7))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Self-collision repulsion forces (point-face) properties configuration node.
- L90 _public member_ `bool bUseSelfCollisions = true;` — `UPROPERTY(VisibleAnywhere, Category = "Self-Collision Properties", meta = (InteractorName = "UseSelfCollisions"))` — Activating this node will enable self collisions.
- L94 _public member_ `FChaosClothAssetWeightedValue SelfCollisionThicknessWeighted = {true, UE::Chaos::ClothAsset::FDefaultFabric::SelfCollisionThickness, UE::Chaos::ClothAsset::FDefaultFabric::SelfCollisionThickness, TEXT("SelfCollis` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", InteractorName = "SelfCollisionThickness"))` — The self collision offset per side. Total thickness of cloth is 2x this value.
- L99 _public member_ `float SelfCollisionStiffness = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "!bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "SelfCollisionStiffness"))` — The stiffness of the springs used to control self collision (PBD Solver).
- L103 _public member_ `FChaosClothAssetImportedFloatValue SelfCollisionFrictionImported = {UE::Chaos::ClothAsset::FDefaultFabric::SelfFriction};` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", DisplayName = "Self Collision Friction", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "!bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "SelfCollisionFriction"))` — Friction coefficient for cloth - cloth interaction.
- L107 _public member_ `int32 SelfCollisionDisableNeighborDistance = 5;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (UIMin = "1", UIMax = "5", ClampMin = "1", EditCondition = "!bSelfCollideAgainstKinematicCollidersOnly"))` — Disabled neighbor collision ring. Collisions are disabled between vertices within this N-ring connectivity distance.
- L114 _public member_ `FChaosClothAssetConnectableIStringValue SelfCollisionLayers = { TEXT("SelfCollisi` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (EditCondition = "!bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "SelfCollisionLayers"))` — Self collision layers face int map. Generate this map using the SelectionsToIntMap node with SimFace Selections. Faces labeled with -1 will collide normally without any layering behavior. Faces labeled with any other number will keep higher layer numbers outside lower layer numbers (outside = front facing normal direction).
- L118 _public member_ `FChaosClothAssetConnectableIStringValue SelfCollisionDisabledFaces = { TEXT("SelfC` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties", meta = (InteractorName = "SelfCollisionDisabledFaces"))` — Sim face selection set of faces which should not self collide
- L122 _public member_ `bool bSelfCollideAgainstKinematicCollidersOnly = false;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties - Kinematic Colliders", meta = (InteractorName = "SelfCollideAgainstKinematicCollidersOnly"))` — Collide only against kinematic colliders (no dynamic self collisions). Kinematic colliders do not do Self Intersections. They always collide against the front-face.
- L126 _public member_ `FChaosClothAssetConnectableIStringValue SelfCollisionEnabledKinematicFaces = { TEXT("SelfC` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties - Kinematic Colliders", meta = (EditCondition = "!bSelfCollideAgainstAllKinematicVertices", InteractorName = "SelfCollisionEnabledKinematicFaces"))` — Sim face selection set of kinematic faces which should self collide. Kinematic colliders do not do Self Intersections. They always collide against the front-face.
- L130 _public member_ `float SelfCollisionKinematicColliderThickness = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties - Kinematic Colliders", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", InteractorName = "SelfCollisionKinematicColliderThickness"))` — Thickness of kinematic colliders. Total offset between cloth and kinematic colliders is SelfCollisionThickness + SelfCollisionKinematicColliderThickness.
- L134 _public member_ `float SelfCollisionKinematicColliderStiffness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties - Kinematic Colliders", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "SelfCollisionKinematicColliderStiffness"))` — The stiffness of the springs used to control self collision (PBD Solver).
- L138 _public member_ `FChaosClothAssetWeightedValue SelfCollisionKinematicColliderFrictionWeighted = {true, 0.0f, 0.f, TEXT("Self` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties - Kinematic Colliders", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", InteractorName = "SelfCollisionKinematicColliderFriction"))` — Friction coefficient for cloth - kinematic cloth interaction. Weight map is on the dynamic cloth, not the collider.
- L142 _public member_ `bool bSelfCollideAgainstAllKinematicVertices = false;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Properties - Kinematic Colliders", meta = (InteractorName = "SelfCollideAgainstAllKinematicVertices"))` — Self collide against all kinematic vertices. Kinematic colliders do not do Self Intersections. They always collide against the front-face.
- L146 _public member_ `bool bUseSelfIntersections = false;` — `UPROPERTY(EditAnywhere, Category = "Experimental", meta = (EditCondition = "!bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "UseSelfIntersections"))` — Enable self intersection resolution. This will try to fix any cloth intersections that are not handled by collision repulsions.
- L150 _public member_ `bool bUseGlobalIntersectionAnalysis = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental", meta = (EditCondition = "bUseSelfIntersections && !bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "UseGlobalIntersectionAnalysis"))` — Do global intersection analysis to determine the correct normals for the collision springs
- L154 _public member_ `bool bUseContourMinimization = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental", meta = (EditCondition = "bUseSelfIntersections && !bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "UseContourMinimization"))` — Do a step of contour minimization at the beginning of the timestep.
- L158 _public member_ `int32 NumContourMinimizationPostSteps = 0;` — `UPROPERTY(EditAnywhere, Category = "Experimental", meta = (ClampMin = "0", EditCondition = "bUseSelfIntersections && !bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "NumContourMinimizationPostSteps"))` — Number of post timestep contour minimization steps to do. (Expensive!)
- L162 _public member_ `bool bUseGlobalPostStepContours = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental", meta = (EditCondition = "bUseSelfIntersections && NumContourMinimizationPostSteps > 0 && !bSelfCollideAgainstKinematicCollidersOnly", InteractorName = "UseGlobalPostStepContours"))` — Use global contour gradients when doing post timestep contour minimization
- L166 _public member_ `float SelfCollisionProximityStiffness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Experimental", meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "!bSelfCollideAgainstAllKinematicVertices", InteractorName = "SelfCollisionProximityStiffness"))` — The stiffness of the proximity repulsions used to control self collision (Force-based Solver). Units = kg cm/ s^2 (same as XPBD springs)
- L168 _public prototype_ `FChaosClothAssetSimulationSelfCollisionConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L170 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L174 _private member_ `static constexpr float FrictionDeprecatedValue = -1.f;`
- L176 _private member_ `float SelfCollisionKinematicColliderFriction_DEPRECATED = FrictionDeprecatedValue;` — `UPROPERTY()`
- L178 _private member_ `static constexpr float SelfFrictionDeprecatedValue = 0.0f;`
- L180 _private member_ `float SelfCollisionFriction_DEPRECATED = SelfFrictionDeprecatedValue;` — `UPROPERTY()`
- L182 _private member_ `static constexpr float SelfCollisionThicknessDeprecatedValue = -1.f;`
- L184 _private member_ `float SelfCollisionThickness_DEPRECATED = SelfCollisionThicknessDeprecatedValue;` — `UPROPERTY()`
- L186 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationSelfCollisionSpheresConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationSelfCollisionSpheresConfigNode`  
`struct FChaosClothAssetSimulationSelfCollisionSpheresConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L10-42_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Self-collision spheres properties configuration node.
- L22 _public member_ `float SelfCollisionSphereStiffness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Spheres Properties", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", InteractorName = "SelfCollisionSphereStiffness"))` — The stiffness of the springs used to control self collision.
- L29 _public member_ `float SelfCollisionSphereRadiusCullMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Self-Collision Spheres Properties", meta = (ClampMin = "1"))` — Multiplier for culling the spheres generated by this node. Spheres are seeded on every vertex, and culled based on SelfCollisionSphereRadius * SelfCollisionSphereRadiusCullMultiplier.
- L33 _public member_ `FString SelfCollisionSphereSetName = GET_MEMBER_NAME_STRING_CHECKED(FChaosClothAssetSimulationSelfCollisionSpheresConfigNode, SelfCollisionSphereSetName);` — `UPROPERTY(VisibleAnywhere, Category = "Self-Collision Spheres Properties", Meta = (DataflowOutput))` — The name of the output selection generated from the unculled vertices that receives the collision spheres.
- L35 _public prototype_ `FChaosClothAssetSimulationSelfCollisionSpheresConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L38 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L40 _private prototype_ `virtual void EvaluateClothCollection(UE::Dataflow::FContext& Context, const TSharedRef<FManagedArrayCollection>& ClothCollection) const override;`
- L41 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationSolverConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationSolverConfigNode`  
`struct FChaosClothAssetSimulationSolverConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L10-91_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Solver properties configuration node.
- L30 _public member_ `int32 MaxNumIterations = 6;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (UIMin = "1", UIMax = "10", ClampMin = "1", ClampMax = "100", InteractorName = "MaxNumIterations"))` — The maximum number of solver iterations. This is the upper limit of the number of iterations set in solver, when the frame rate is lower than 60fps.
- L37 _public member_ `FChaosClothAssetImportedIntValue NumSubstepsImported = {UE::Chaos::ClothAsset::FDefaultSolver::SubSteps};` — `UPROPERTY(EditAnywhere, Category = Simulation, DisplayName = "Num Substeps", meta = (UIMin = "1", UIMax = "10", ClampMin = "1", ClampMax = "100", InteractorName = "NumSubsteps"))` — The number of solver substeps. This will increase the precision of the collision inputs and help with constraint resolutions but will increase the CPU cost.
- L43 _public member_ `bool bEnableDynamicSubstepping = false;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (InlineEditConditionToggle))` — Enable dynamic substepping.
- L49 _public member_ `float DynamicSubstepDeltaTime = 16.67f;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (UIMin = "1", UIMax = "30", ClampMin = "0", ClampMax = "1000", EditCondition = "bEnableDynamicSubstepping", InteractorName = "DynamicSubstepDeltaTime"))` — Choose the number of substeps based on a target substep delta time in milliseconds. Substeps are clamped to [1, NumSubsteps].
- L55 _public member_ `bool bEnableNumSelfCollisionSubsteps = false;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (InteractorName = "EnableNumSelfCollisionSubsteps"))` — Enable setting separate SelfCollisionSubsteps. Otherwise, self collisions will be detected every substep.
- L62 _public member_ `int32 NumSelfCollisionSubsteps = 1;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (UIMin = "1", UIMax = "10", ClampMin = "1", ClampMax = "100", EditCondition = "bEnableNumSelfCollisionSubsteps", InteractorName = "NumSelfCollisionSubsteps"))` — Set a separate number of self collision substeps. Lower this number to increase speed at the expense of lower self collision accuracy. Actual value always clamped between [1, NumSubsteps].
- L64 _public prototype_ `FChaosClothAssetSimulationSolverConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L66 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L73 _private member_ `int32 NumSubsteps_DEPRECATED = UE::Chaos::ClothAsset::FDefaultSolver::SubSteps;` — `UPROPERTY()`
- L76 _private member_ `bool bEnableForceBasedSolver_DEPRECATED = false;` — `UPROPERTY()`
- L79 _private member_ `int32 NumNewtonIterations_DEPRECATED = 0;` — `UPROPERTY()`
- L82 _private member_ `int32 MaxNumCGIterations_DEPRECATED = 50;` — `UPROPERTY()`
- L85 _private member_ `float CGResidualTolerance_DEPRECATED = 1e-4f;` — `UPROPERTY()`
- L88 _private member_ `bool bDoQuasistatics_DEPRECATED = false;` — `UPROPERTY()`
- L90 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationStretchConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationStretchConfigNode`  
`struct FChaosClothAssetSimulationStretchConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-129_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Stretching constraint property configuration node.
- L24 _public member_ `EChaosClothAssetConstraintSolverType SolverType = EChaosClothAssetConstraintSolverType::PBD;` — `UPROPERTY(EditAnywhere, Category = "Stretch Types")` — Constraint solver type.
- L28 _public member_ `EChaosClothAssetConstraintDistributionType DistributionType = EChaosClothAssetConstraintDistributionType::Isotropic;` — `UPROPERTY(EditAnywhere, Category = "Stretch Types", Meta = (EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides))` — Constraint distribution type.
- L32 _public member_ `bool bAddAreaConstraint = true;` — `UPROPERTY(EditAnywhere, Category = "Stretch Types", Meta = (EditCondition = "((SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic) || SolverType == EChaosClothAssetConstraintSolverType::PBD)", EditConditionHides))` — Add an area constraint in case of isotropic distribution
- L41 _public member_ `FChaosClothAssetWeightedValue StretchStiffnessWarp = { true, 100.f, 100.f, TEXT("StretchSti` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "StretchStiffnessWarp"))` — The stiffness of the stretch constraints in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L50 _public member_ `FChaosClothAssetWeightedValue StretchStiffnessWeft = { true, 100.f, 100.f, TEXT("StretchStif` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "StretchStiffnessWeft"))` — The stiffness of the stretch constraints in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L59 _public member_ `FChaosClothAssetWeightedValue StretchStiffnessBias = { true, 100.f, 100.f, TEXT("StretchStif` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic && SolverType == EChaosClothAssetConstraintSolverType::XPBD", EditConditionHides, InteractorName = "StretchStiffnessBias"))` — The stiffness of the stretch constraints in the bias (diagonal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L69 _public member_ `FChaosClothAssetWeightedValue StretchAnisoDamping = { true, 1.f, 1.f, TEXT("StretchAnis` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000", EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic", EditConditionHides, InteractorName = "StretchDamping"))` — The damping of the stretch anisotropic constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L78 _public member_ `FChaosClothAssetWeightedValue StretchStiffness = { true, 1.f, 1.f, TEXT("Stret` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "1000000000", EditCondition = "(SolverType == EChaosClothAssetConstraintSolverType::PBD || DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic)", EditConditionHides, InteractorName = "StretchStiffness"))` — The stiffness of the stretch constraints. Note that PBD stiffnesses will be internally clamped to [0,1]. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L88 _public member_ `FChaosClothAssetWeightedValue StretchDamping = { true, 1.f, 1.f, TEXT("Stret` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000", EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic", EditConditionHides, InteractorName = "StretchDamping"))` — The damping of the stretch constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L95 _public member_ `bool bEnableStretchWarpAndWeftScale = false;` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (EditCondition = "SolverType == EChaosClothAssetConstraintSolverType::PBD", EditConditionHides))` — Enable StretchWarp and WeftScale. This adds a small amount of memory and computational cost, so this is optional for the least expensive constraint type (PBD)
- L104 _public member_ `FChaosClothAssetWeightedValue StretchWarpScale = { true, 1.f, 1.f, TEXT("Stret` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000000", EditCondition = "(SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic) || (bEnableStretchWarpAndWeftScale && SolverType == EChaosClothAssetConstraintSolverType::PBD)", EditConditionHides, InteractorName = "StretchWarpScale"))` — The scale of the stretch constraints at rest in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L113 _public member_ `FChaosClothAssetWeightedValue StretchWeftScale = { true, 1.f, 1.f, TEXT("Stret` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000000", EditCondition = "(SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Anisotropic) || (bEnableStretchWarpAndWeftScale && SolverType == EChaosClothAssetConstraintSolverType::PBD)", EditConditionHides, InteractorName = "StretchWeftScale"))` — The scale of the stretch constraints at rest in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L123 _public member_ `FChaosClothAssetWeightedValue AreaStiffness = { true, 1.f, 1.f, TEXT("AreaS` — `UPROPERTY(EditAnywhere, Category = "Stretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "bAddAreaConstraint == true && ((SolverType == EChaosClothAssetConstraintSolverType::XPBD && DistributionType == EChaosClothAssetConstraintDistributionType::Isotropic) || SolverType == EChaosClothAssetConstraintSolverType::PBD)", EditConditionHides, InteractorName = "AreaStiffness"))` — The stiffness of the surface area preservation constraints. Note that PBD stiffnesses will be internally clamped to [0,1]. Increase the solver iteration count for stiffer materials. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L125 _public prototype_ `FChaosClothAssetSimulationStretchConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L128 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationStretchOverrideConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationStretchOverrideConfigNode`  
`struct FChaosClothAssetSimulationStretchOverrideConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-92_
- reflection: `USTRUCT(Meta = (DataflowCloth, Experimental))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Stretching constraint property override configuration node.
- L25 _public member_ `bool bStretchUse3dRestLengths = true;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (EditCondition = "bOverrideStretchUse3dRestLengths"))` — Whether to use the 3D draped space as rest lengths, or use the 2D pattern space instead.
- L29 _public member_ `EChaosClothAssetConstraintOverrideType OverrideStretchStiffness = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override")` — Stretch stiffness override type.
- L33 _public member_ `FChaosClothAssetWeightedValueOverride StretchStiffness;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (ClampMin = "0", EditCondition = "OverrideStretchStiffness != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Stretch stiffness override value.
- L37 _public member_ `bool bApplyUniformStretchStiffnessOverride = true;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (EditCondition = "OverrideStretchStiffness != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Whether or not to apply the Stretch Stiffness Override to warp, weft, and bias stiffnesses of anisotropic springs.
- L41 _public member_ `EChaosClothAssetConstraintOverrideType OverrideStretchStiffnessWarp = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (EditCondition = "OverrideStretchStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformStretchStiffnessOverride", EditConditionHides))` — Warp stiffness override type.
- L45 _public member_ `FChaosClothAssetWeightedValueOverride StretchStiffnessWarp;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (ClampMin = "0", EditCondition = "(OverrideStretchStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformStretchStiffnessOverride) && OverrideStretchStiffnessWarp != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Stretch stiffness warp override value.
- L49 _public member_ `EChaosClothAssetConstraintOverrideType OverrideStretchStiffnessWeft = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (EditCondition = "OverrideStretchStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformStretchStiffnessOverride", EditConditionHides))` — Weft stiffness override type.
- L53 _public member_ `FChaosClothAssetWeightedValueOverride StretchStiffnessWeft;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (ClampMin = "0", EditCondition = "(OverrideStretchStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformStretchStiffnessOverride) && OverrideStretchStiffnessWeft != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Stretch stiffness weft override value.
- L57 _public member_ `EChaosClothAssetConstraintOverrideType OverrideStretchStiffnessBias = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (EditCondition = "OverrideStretchStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformStretchStiffnessOverride", EditConditionHides))` — Bias stiffness override type.
- L61 _public member_ `FChaosClothAssetWeightedValueOverride StretchStiffnessBias;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (ClampMin = "0", EditCondition = "(OverrideStretchStiffness == EChaosClothAssetConstraintOverrideType::None || !bApplyUniformStretchStiffnessOverride) && OverrideStretchStiffnessBias != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Stretch stiffness bias override value.
- L65 _public member_ `EChaosClothAssetConstraintOverrideType OverrideStretchDamping = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override")` — Damping override type.
- L69 _public member_ `FChaosClothAssetWeightedValueOverride StretchDamping;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (ClampMin = "0", EditCondition = "OverrideStretchDamping != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Stretch damping override value.
- L73 _public member_ `EChaosClothAssetConstraintOverrideType OverrideWarpScale = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override")` — Warp scale override type.
- L77 _public member_ `FChaosClothAssetWeightedValueOverride WarpScale;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (ClampMin = "0", EditCondition = "OverrideWarpScale != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Stretch damping override value.
- L81 _public member_ `EChaosClothAssetConstraintOverrideType OverrideWeftScale = EChaosClothAssetConstraintOverrideType::None;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override")` — Weft scale override type.
- L85 _public member_ `FChaosClothAssetWeightedValueOverride WeftScale;` — `UPROPERTY(EditAnywhere, Category = "Stretch Override", meta = (ClampMin = "0", EditCondition = "OverrideWeftScale != EChaosClothAssetConstraintOverrideType::None", EditConditionHides))` — Stretch damping override value.
- L88 _public prototype_ `FChaosClothAssetSimulationStretchOverrideConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L91 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationVelocityScaleConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationVelocityScaleConfigNode`  
`struct FChaosClothAssetSimulationVelocityScaleConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L13-131_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: Velocity scale properties configuration node.
- L33 _public member_ `FVector3f LinearVelocityScale = { 0.75f, 0.75f, 0.75f };` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "100", InteractorName = "LinearVelocityScale"))` — The amount of linear velocities sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned). This value will be clamped by "Max Velocity Scale". A velocity scale of > 1 will amplify the velocities from the reference bone.
- L39 _public member_ `bool bEnableLinearVelocityClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (InlineEditConditionToggle))` — Enable linear velocity clamping.
- L46 _public member_ `FVector3f MaxLinearVelocity = { 1000.f, 1000.f, 1000.f };` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (ClampMin = "0", EditCondition = "bEnableLinearVelocityClamping", InteractorName = "MaxLinearVelocity"))` — The maximum amount of linear velocity sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L52 _public member_ `bool bEnableLinearAccelerationClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (InlineEditConditionToggle))` — Enable linear acceleration clamping.
- L59 _public member_ `FVector3f MaxLinearAcceleration = { 60000.f, 60000.f, 60000.f };` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (ClampMin = "0", EditCondition = "bEnableLinearAccelerationClamping", InteractorName = "MaxLinearAcceleration"))` — The maximum amount of linear acceleration sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L67 _public member_ `float AngularVelocityScale = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "100", InteractorName = "AngularVelocityScale"))` — The amount of angular velocities sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned). This value will be clamped by "Max Velocity Scale". A velocity scale of > 1 will amplify the velocities from the reference bone.
- L73 _public member_ `bool bEnableAngularVelocityClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (InlineEditConditionToggle))` — Enable angular velocity clamping.
- L80 _public member_ `float MaxAngularVelocity = 200.f;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (ClampMin = "0", EditCondition = "bEnableAngularVelocityClamping", InteractorName = "MaxAngularVelocity"))` — The maximum amount of angular velocity sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L86 _public member_ `bool bEnableAngularAccelerationClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (InlineEditConditionToggle))` — Enable angular acceleration clamping.
- L93 _public member_ `float MaxAngularAcceleration = 12000.f;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (ClampMin = "0", EditCondition = "bEnableAngularAccelerationClamping", InteractorName = "MaxAngularAcceleration"))` — The maximum amount of angular acceleration sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L99 _public member_ `float MaxVelocityScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "100", InteractorName = "MaxVelocityScale"))` — Clamp on Linear and Angular Velocity Scale. The final velocity scale (e.g., including contributions from blueprints) will be clamped to this value.
- L106 _public member_ `EChaosClothingSimulationSolverFictitiousForcesModel FictitiousForcesModel = EChaosClothingSimulationSolverFictitiousForcesModel::FullScale;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (InteractorName = "FictitiousForcesModel"))` — Fictitious forces model. Decide how fictitious forces (e.g. centrifugal force) are applied to the simulation.
- L119 _public member_ `float FictitiousAngularScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Velocity Scale Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "2", EditCondition = "FictitiousForcesModel != EChaosClothingSimulationSolverFictitiousForcesModel::None", InteractorName = "FictitiousAngularScale"))` — The portion of the angular velocity that is used to calculate the strength of all fictitious forces (e.g. centrifugal force). In Legacy model, this parameter is only having an effect on the portion of the reference bone's angular velocity that has been removed from the simulation via the Angular Velocity Scale parameter. This means it has no effect when AngularVelocityScale is set to 1 and Angular Velocity and Acceleration clamps are disabled, in which case the cloth is simulated with full world space angular velocities and subjected to the true physical world inertial forces. In FullScale model, this parameter has also an effect when the cloth is simulated with full world space angular velocities, and isn't affected by the Angular Velocity Scale parameter. Values range from 0 to 2, with 0 showing no centrifugal effect, 1 full centrifugal effect, and 2 an overdriven centrifugal effect.
- L121 _public prototype_ `FChaosClothAssetSimulationVelocityScaleConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L125 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`
- L129 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationXPBDAnisoBendingConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationXPBDAnisoBendingConfigNode`  
`struct FChaosClothAssetSimulationXPBDAnisoBendingConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-129_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: XPBD anisotropic bending constraint property configuration node.
- L33 _public member_ `FChaosClothAssetWeightedValueNonAnimatable XPBDAnisoFlatnessRatio = { 0.f, 0.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "XPBDAnisoRestAngleType == EChaosClothAssetRestAngleConstructionType::FlatnessRatio"))` — Calculate rest angles as a ratio between completely flat and whatever is the 3D rest angle. When FlatnessRatio = 0, this is equivalent to "Use3DRestAngles". When FlatnessRatio = 1, the rest angle will be 0 (completely flat). If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L44 _public member_ `FChaosClothAssetWeightedValueNonAnimatable XPBDAnisoRestAngle = { 0.f, 0.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180", EditCondition = "XPBDAnisoRestAngleType == EChaosClothAssetRestAngleConstructionType::RestAngle"))` — Set rest angles to be the explicit value set here (in degrees). 0 = Flat, Positive values fold away from the edge normal, Negative values fold toward the edge normal. When converting vertex weight values to edge values, the value with the smallest absolute value is selected. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L53 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoBendingStiffnessWarp = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the bending constraints in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L62 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoBendingStiffnessWeft = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the bending constraints in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L71 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoBendingStiffnessBias = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the bending constraints in the bias (diagonal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L80 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoBendingDamping = { true, 1.f, 1.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"))` — The damping of the bending constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L87 _public member_ `float XPBDAnisoBucklingRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Once the element has bent such that it's folded more than this ratio from its rest angle ("buckled"), switch to using Buckling Stiffness instead of BendingElement Stiffness. When Buckling Ratio = 0, the Buckling Stiffness will never be used. When BucklingRatio = 1, the Buckling Stiffness will be used as soon as its bent past its rest configuration.
- L99 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoBucklingStiffnessWarp = { true, 50.f, 50.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "XPBDAnisoBucklingRatio != 0"))` — The stiffness after buckling in the warp (vertical) direction. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L111 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoBucklingStiffnessWeft = { true, 50.f, 50.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "XPBDAnisoBucklingRatio != 0"))` — The stiffness after buckling in the weft (horizontal) direction. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L123 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoBucklingStiffnessBias = { true, 50.f, 50.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoBending Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "XPBDAnisoBucklingRatio != 0"))` — The stiffness after buckling in the bias (diagonal) direction. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L125 _public prototype_ `FChaosClothAssetSimulationXPBDAnisoBendingConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L128 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationXPBDAnisoSpringConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationXPBDAnisoSpringConfigNode`  
`struct FChaosClothAssetSimulationXPBDAnisoSpringConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-79_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: XPBD anisotropic spring constraint property configuration node.
- L28 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoSpringStiffnessWarp = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoSpring Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the stretch constraints in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L37 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoSpringStiffnessWeft = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoSpring Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the stretch constraints in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L46 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoSpringStiffnessBias = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoSpring Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the stretch constraints in the bias (diagonal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L55 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoSpringDamping = { true, 1.f, 1.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoSpring Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"))` — The damping of the stretch constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L64 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoSpringWarpScale = { true, 1.f, 1.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoSpring Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000000"))` — The scale of the stretch constraints at rest in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L73 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoSpringWeftScale = { true, 1.f, 1.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoSpring Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000000"))` — The scale of the stretch constraints at rest in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L75 _public prototype_ `FChaosClothAssetSimulationXPBDAnisoSpringConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L78 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationXPBDAnisoStretchConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationXPBDAnisoStretchConfigNode`  
`struct FChaosClothAssetSimulationXPBDAnisoStretchConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-79_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: XPBD anisotropic stretch constraint property configuration node.
- L28 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoStretchStiffnessWarp = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoStretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the stretch constraints in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L37 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoStretchStiffnessWeft = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoStretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the stretch constraints in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L46 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoStretchStiffnessBias = { true, 100.f, 100.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoStretch Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the stretch constraints in the bias (diagonal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L55 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoStretchDamping = { true, 1.f, 1.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoStretch Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"))` — The damping of the stretch constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L64 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoStretchWarpScale = { true, 1.f, 1.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoStretch Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000000"))` — The scale of the stretch constraints at rest in the warp (vertical) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L73 _public member_ `FChaosClothAssetWeightedValue XPBDAnisoStretchWeftScale = { true, 1.f, 1.f, TEXT("XPBDA` — `UPROPERTY(EditAnywhere, Category = "XPBDAnisoStretch Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10000000"))` — The scale of the stretch constraints at rest in the weft (horizontal) direction. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L75 _public prototype_ `FChaosClothAssetSimulationXPBDAnisoStretchConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L78 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationXPBDAreaSpringConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationXPBDAreaSpringConfigNode`  
`struct FChaosClothAssetSimulationXPBDAreaSpringConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-31_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: XPBD area spring constraint property configuration node.
- L27 _public prototype_ `FChaosClothAssetSimulationXPBDAreaSpringConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L30 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationXPBDBendingElementConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationXPBDBendingElementConfigNode`  
`struct FChaosClothAssetSimulationXPBDBendingElementConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L12-87_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: XPBD bending element constraint property configuration node.
- L33 _public member_ `FChaosClothAssetWeightedValueNonAnimatable XPBDFlatnessRatio = { 0.f, 0.f, TEXT("XPBDF` — `UPROPERTY(EditAnywhere, Category = "XPBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "XPBDRestAngleType == EChaosClothAssetRestAngleConstructionType::FlatnessRatio"))` — Calculate rest angles as a ratio between completely flat and whatever is the 3D rest angle. When FlatnessRatio = 0, this is equivalent to "Use3DRestAngles". When FlatnessRatio = 1, the rest angle will be 0 (completely flat). If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L44 _public member_ `FChaosClothAssetWeightedValueNonAnimatable XPBDRestAngle = { 0.f, 0.f, TEXT("XPBDR` — `UPROPERTY(EditAnywhere, Category = "XPBDBendingElement Properties", Meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180", EditCondition = "XPBDRestAngleType == EChaosClothAssetRestAngleConstructionType::RestAngle"))` — Set rest angles to be the explicit value set here (in degrees). 0 = Flat, Positive values fold away from the edge normal, Negative values fold toward the edge normal. When converting vertex weight values to edge values, the value with the smallest absolute value is selected. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L53 _public member_ `FChaosClothAssetWeightedValue XPBDBendingElementStiffness = { true, 100.f, 100.f, TEXT("XPBDB` — `UPROPERTY(EditAnywhere, Category = "XPBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000"))` — The stiffness of the bending element constraints. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L62 _public member_ `FChaosClothAssetWeightedValue XPBDBendingElementDamping = { true, 1.f, 1.f, TEXT("XPBDB` — `UPROPERTY(EditAnywhere, Category = "XPBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"))` — The damping of the bending element constraints, relative to critical damping. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L69 _public member_ `float XPBDBucklingRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "XPBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Once the element has bent such that it's folded more than this ratio from its rest angle ("buckled"), switch to using Buckling Stiffness instead of BendingElement Stiffness. When Buckling Ratio = 0, the Buckling Stiffness will never be used. When BucklingRatio = 1, the Buckling Stiffness will be used as soon as its bent past its rest configuration.
- L81 _public member_ `FChaosClothAssetWeightedValue XPBDBucklingStiffness = { true, 50.f, 50.f, TEXT("XPBDB` — `UPROPERTY(EditAnywhere, Category = "XPBDBendingElement Properties", Meta = (UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "10000000", EditCondition = "XPBDBucklingRatio != 0"))` — The stiffness after buckling. The constraint will use this stiffness instead of element Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than BendingElement Stiffness. Buckling Ratio determines the switch point between using BendingElement Stiffness and Buckling Stiffness. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L83 _public prototype_ `FChaosClothAssetSimulationXPBDBendingElementConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L86 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationXPBDBendingSpringConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationXPBDBendingSpringConfigNode`  
`struct FChaosClothAssetSimulationXPBDBendingSpringConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-39_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.4"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: XPBD bending spring constraint property configuration node.
- L33 _public member_ `FChaosClothAssetWeightedValue XPBDBendingSpringDamping = { true, 1.f, 1.f, TEXT("XPBDB` — `UPROPERTY(EditAnywhere, Category = "XPBDBendingSpring Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"))` — The damping of the bending cross segment constraints. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L35 _public prototype_ `FChaosClothAssetSimulationXPBDBendingSpringConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L38 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SimulationXPBDEdgeSpringConfigNode.h` (Public)


#### struct `FChaosClothAssetSimulationXPBDEdgeSpringConfigNode`  
`struct FChaosClothAssetSimulationXPBDEdgeSpringConfigNode : public FChaosClothAssetSimulationBaseConfigNode`  
_L11-39_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.2"))`
- inherits: `FChaosClothAssetSimulationBaseConfigNode`
- desc: XPBD edge spring constraint property configuration node.
- L33 _public member_ `FChaosClothAssetWeightedValue XPBDEdgeSpringDamping = { true, 1.f, 1.f, TEXT("XPBDE` — `UPROPERTY(EditAnywhere, Category = "XPBDEdgeSpring Properties", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"))` — The damping of the edge segment constraints. If a valid weight map is found with the given Weight Map name, then both Low and High values are interpolated with the per particle weight to make the final value used for the simulation. Otherwise all particles are considered to have a zero weight, and only the Low value is meaningful.
- L35 _public prototype_ `FChaosClothAssetSimulationXPBDEdgeSpringConfigNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L38 _private prototype_ `virtual void AddProperties(FPropertyHelper& PropertyHelper) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SkeletalMeshImportNode.h` (Public)


#### struct `FChaosClothAssetSkeletalMeshImportNode_v2`  
`struct FChaosClothAssetSkeletalMeshImportNode_v2 : public FDataflowNode`  
_L15-75_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Import a skeletal mesh asset into the cloth collection simulation and/or render mesh containers.
- L22 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowOutput))`
- L26 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (DataflowInput))` — The skeletal mesh to import.
- L30 _public member_ `FDataflowFunctionProperty Reimport;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (ButtonImage = "Persona.ReimportAsset", DisplayName = "Reimport Asset"))` — Reimport the imported skeletal mesh asset.
- L34 _public member_ `bool bImportSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Whether to import the simulation mesh from the specified skeletal mesh.
- L38 _public member_ `bool bImportRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Whether to import the render mesh from the specified skeletal mesh.
- L42 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (ClampMin = "0", DisplayName = "LOD Index"))` — The skeletal mesh LOD to import.
- L46 _public member_ `bool bImportSingleSection = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Enable single import section mode.
- L50 _public member_ `int32 SectionIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (ClampMin = "0", EditCondition = "bImportSingleSection"))` — The skeletal mesh LOD section to import. If not enabled, then all sections will be imported.
- L57 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportSimMesh"))` — UV channel of the skeletal mesh to import the 2D simulation mesh patterns from. If set to -1, or the specified UVChannel doesn't exist then the import will unwrap the 3D simulation mesh into 2D simulation mesh patterns.
- L61 _public member_ `FVector2f UVScale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (AllowPreserveRatio, EditCondition = "bImportSimMesh && UVChannel != INDEX_NONE"))` — Apply this scale to the UVs when populating Sim Mesh positions.
- L65 _public member_ `bool bSetPhysicsAsset = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Set the same physics asset as the one used by the imported skeletal mesh.
- L69 _public member_ `bool bImportSimMorphTargets = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (EditCondition = "bImportSimMesh"))` — Import morph targets as Sim Mesh Morph Targets
- L71 _public prototype_ `FChaosClothAssetSkeletalMeshImportNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L74 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FChaosClothAssetSkeletalMeshImportNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetSkeletalMeshImportNode : public FDataflowNode`  
_L80-133_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Import a skeletal mesh asset into the cloth collection simulation and/or render mesh containers. This version re-calculates the Sim Mesh Normals, and they are flipped. It also does not remove topologically degenerate triangles.
- L87 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowOutput))`
- L91 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (DataflowInput))` — The skeletal mesh to import.
- L95 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (ClampMin = "0", DisplayName = "LOD Index"))` — The skeletal mesh LOD to import.
- L99 _public member_ `bool bImportSingleSection = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Enable single import section mode.
- L103 _public member_ `int32 SectionIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (ClampMin = "0", EditCondition = "bImportSingleSection"))` — The skeletal mesh LOD section to import. If not enabled, then all sections will be imported.
- L107 _public member_ `bool bImportSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Whether to import the simulation mesh from the specified skeletal mesh.
- L111 _public member_ `bool bImportRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Whether to import the render mesh from the specified skeletal mesh.
- L118 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportSimMesh"))` — UV channel of the skeletal mesh to import the 2D simulation mesh patterns from. If set to -1, or the specified UVChannel doesn't exist then the import will unwrap the 3D simulation mesh into 2D simulation mesh patterns.
- L122 _public member_ `FVector2f UVScale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import", Meta = (AllowPreserveRatio, EditCondition = "bImportSimMesh && UVChannel != INDEX_NONE"))` — Apply this scale to the UVs when populating Sim Mesh positions.
- L126 _public member_ `bool bSetPhysicsAsset = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Import")` — Set the same physics asset as the one used by the imported skeletal mesh.
- L128 _public prototype_ `FChaosClothAssetSkeletalMeshImportNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L131 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L132 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/SkinningBlendNode.h` (Public)


#### struct `FChaosClothAssetSkinningBlendNode`  
`struct FChaosClothAssetSkinningBlendNode : public FDataflowNode`  
_L24-66_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Initialize the RenderDeformerSkinningBlend weight map from the ProxyDeformer mapping data. The weight map is used by the cloth render shader to decide how much to blend between skinned and simulated points. Value ranges between 0 for fully deformed, to 1 for fully skinned. Editing the RenderDeformerSkinningBlend is possible after this node (via a WeightMap node), as the RenderDeformerSkinningBlend weight map is an intrinsic attribute of the ClothCollection. Note: ProxyDeformer mapping data must exist on the input ClothCollection prior to using this node.
- L32 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L41 _public member_ `FChaosClothAssetConnectableIStringValue KinematicVertices3D;` — `UPROPERTY(EditAnywhere, Category = "SkinningBlend")` — The name of a selection containing all the kinematic points. Must be of group type SimVertices2D, SimVertices3D, or SimFaces. Using an empty (or invalid) selection will make this node consider all points as dynamic. This selection is usually obtained from the MaxDistanceConfig node or built from the same weight map set to the MaxDistanceConfig node using a WeightMapToSelection node and a very low threshold.
- L49 _public member_ `bool bUseSmoothTransition = true;` — `UPROPERTY(EditAnywhere, Category = "SkinningBlend")` — Whether to create a smoothed RenderDeformerSkinningBlend weight map to ease the transition between the deformed part and the skinned part of the render mesh. When no transition is created there will be a visible step in the rendered triangles around the edge of the kinematic/dynamic transition of the proxy simulation mesh. The RenderDeformerSkinningBlend weight map is created regardless of the transition being created smooth or not, and can be later adjusted by using the WeightMap node.
- L57 _public member_ `FString SkinningBlendName;` — `UPROPERTY(VisibleAnywhere, Category = "SkinningBlend", Meta = (DataflowOutput))` — The name of the render mesh weight map generated by this node detailing the contribution of the proxy deformer. Value ranges between 0 (fully deformed) and 1 (fully skinned). The name of this render mesh weight map cannot be changed and is only provided for further tweaking.
- L59 _public prototype_ `FChaosClothAssetSkinningBlendNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L64 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/StaticMeshImportNode.h` (Public)


#### struct `FChaosClothAssetStaticMeshImportNode_v2`  
`struct FChaosClothAssetStaticMeshImportNode_v2 : public FDataflowNode`  
_L16-68_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Import a static mesh asset into the cloth collection simulation and/or render mesh containers.
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowOutput))`
- L27 _public member_ `TObjectPtr<const UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (DataflowInput))` — The Static Mesh to import from.
- L31 _public member_ `FDataflowFunctionProperty Reimport;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ButtonImage = "Persona.ReimportAsset", DisplayName = "Reimport Asset", EditCondition = "!bIsLocked"))` — Reimport the imported static mesh asset.
- L35 _public member_ `bool bImportSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import")` — Import static mesh data as a simulation mesh data.
- L39 _public member_ `bool bImportRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import")` — Import static mesh data as render mesh data.
- L43 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "0", DisplayName = "LOD Index"))` — Which static mesh Lod to import.
- L47 _public member_ `int32 SimMeshSection = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportSimMesh"))` — Material section to import as sim mesh data. Use -1 to import all sections.
- L51 _public member_ `int32 RenderMeshSection = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportRenderMesh"))` — Material section to import as render mesh data. Use -1 to import all sections.
- L58 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportSimMesh"))` — UV channel of the static mesh to import the 2D simulation mesh patterns from. If set to -1, or the specified UVChannel doesn't exist then the import will unwrap the 3D simulation mesh into 2D simulation mesh patterns.
- L62 _public member_ `FVector2f UVScale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (AllowPreserveRatio, EditCondition = "bImportSimMesh && (UVChannel >= 0)"))` — Apply this scale to the UVs when populating Sim Mesh positions.
- L64 _public prototype_ `FChaosClothAssetStaticMeshImportNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L67 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FChaosClothAssetStaticMeshImportNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetStaticMeshImportNode : public FDataflowNode`  
_L74-122_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Import a static mesh asset into the cloth collection simulation and/or render mesh containers. This version re-calculates the Sim Mesh Normals, and they are flipped. It also does not remove topologically degenerate triangles.
- L81 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowOutput))`
- L85 _public member_ `TObjectPtr<const UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (DataflowInput))` — The Static Mesh to import from.
- L89 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "0", DisplayName = "LOD Index"))` — Which static mesh Lod to import.
- L93 _public member_ `bool bImportSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import")` — Import static mesh data as a simulation mesh data.
- L97 _public member_ `int32 SimMeshSection = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportSimMesh"))` — Material section to import as sim mesh data. Use -1 to import all sections.
- L104 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportSimMesh"))` — UV channel of the static mesh to import the 2D simulation mesh patterns from. If set to -1, or the specified UVChannel doesn't exist then the import will unwrap the 3D simulation mesh into 2D simulation mesh patterns.
- L108 _public member_ `FVector2f UVScale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (AllowPreserveRatio, EditCondition = "bImportSimMesh && (UVChannel >= 0)"))` — Apply this scale to the UVs when populating Sim Mesh positions.
- L112 _public member_ `bool bImportRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import")` — Import static mesh data as render mesh data.
- L116 _public member_ `int32 RenderMeshSection = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Static Mesh Import", Meta = (ClampMin = "-1", EditCondition = "bImportRenderMesh"))` — Material section to import as render mesh data. Use -1 to import all sections.
- L118 _public prototype_ `FChaosClothAssetStaticMeshImportNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L121 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/StripUserAttributesNode.h` (Public)


#### struct `FChaosClothStripUserAttributesNode`  
`struct FChaosClothStripUserAttributesNode : public FDataflowNode`  
_L16-72_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Strip User Attributes such as Weight Maps, Sets, and Face Int Maps from a Cloth Collection if they are not referenced by properties. This utility node makes it easier to remove unused attributes from your asset, reducing asset size. Note that if this node is not present in your Cloth Dataflow Graph, unreferenced Sets and Face Int Maps will not be copied to the simulation model. Weight Maps will continue to be copied without this node to retain legacy behavior.
- L28 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L32 _private member_ `bool bStripUnusedSimWeightMaps = true;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes")` — Strip all unused sim vertex weight maps from the asset. This reduces the asset size, but the weight maps will be unavailable in blueprints, for debug display, or in downstream cloth assets which import this one.
- L36 _private member_ `TArray<FString> ExtraSimWeightMaps;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes", Meta = (DataflowInput, EditCondition = "bStripUnusedSimWeightMaps"))` — Extra sim weight maps to keep when stripping unused weight maps.
- L40 _private member_ `bool bStripUnusedSets = true;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes")` — Strip all unused sim and render sets from the asset. This reduces the asset size, but the sets will be unavailable in blueprints, for debug display, or in downstream cloth assets which import this one.
- L44 _private member_ `TArray<FString> ExtraSets;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes", Meta = (DataflowInput, EditCondition = "bStripUnusedSets"))` — Extra sets to keep when stripping unused sets.
- L48 _private member_ `bool bStripUnusedSimFaceIntMaps = true;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes")` — Strip all unused sim face integer maps from the asset. This reduces the asset size, but the maps will be unavailable in blueprints, for debug display, or in downstream cloth assets which import this one.
- L52 _private member_ `TArray<FString> ExtraSimFaceIntMaps;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes", Meta = (DataflowInput, EditCondition = "bStripUnusedSimFaceIntMaps"))` — Extra maps to keep when stripping unused face integer maps.
- L57 _private member_ `bool bStripUnusedRenderWeightMaps = true;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes")` — Strip all unused render vertex weight maps from the asset. This reduces the uncooked asset size, but the maps will be unavailable in downstream assets which import this one. Note that user render weight maps do not currently exist in the cooked asset, so this property has no effect on cooked assets.
- L61 _private member_ `TArray<FString> ExtraRenderWeightMaps;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes", Meta = (DataflowInput, EditCondition = "bStripUnusedRenderWeightMaps"))` — Extra render weight maps to keep when stripping unused weight maps.
- L67 _private member_ `bool bCopyAllUserAttributesToSimModel = true;` — `UPROPERTY(EditAnywhere, Category = "Strip User Attributes")` — Tell the cloth asset to transfer all user attributes from the cloth collection to the internal simulation model rather than skipping unreferenced sets and face int maps. Note that sim weight maps are always transferred.
- L70 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/TerminalNode.h` (Public)


#### struct `FChaosClothAssetTerminalNodeRefreshAsset`  
`struct UE_DEPRECATED(5.5, "Use UE::Dataflow::FunctionProperty instead.") FChaosClothAssetTerminalNodeRefreshAsset`  
_L15-21_
- reflection: `USTRUCT()`
- desc: Refresh structure for push buton customization.
- L20 _public member_ `bool bRefreshAsset = false;` — `UPROPERTY(EditAnywhere, Category = "Terminal Node Refresh Asset")`

#### struct `FChaosClothAssetTerminalNode_v2`  
`struct FChaosClothAssetTerminalNode_v2 : public FDataflowTerminalNode`  
_L25-68_
- reflection: `USTRUCT(Meta = (DataflowCloth, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Cloth terminal node to generate a cloth asset from a cloth collection.
- L33 _public member_ `TArray<FManagedArrayCollection> CollectionLods;` — `UPROPERTY()` — Input cloth collection for this LOD.
- L41 _public member_ `FDataflowFunctionProperty Refresh;` — `UPROPERTY(EditAnywhere, Transient, Category = "Cloth Asset Terminal", Meta = (DisplayName = "Refresh Asset", ButtonImage = "Icons.Refresh"))` — Refresh the asset even if the ClothCollection hasn't changed. Note that it is not required to manually refresh the cloth asset, this is done automatically when there is a change in the Dataflow. This function is a developper utility used for debugging.
- L43 _public prototype_ `FChaosClothAssetTerminalNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L47 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L48 _private function_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override`
- L49 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L50 _private function_ `virtual bool CanAddPin() const override`
- L51 _private function_ `virtual bool CanRemovePin() const override`
- L52 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L53 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L54 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L57 _private prototype_ `TArray<TSharedRef<const FManagedArrayCollection>> GetCleanedCollectionLodValues(UE::Dataflow::FContext& Context) const;`
- L58 _private prototype_ `UE::Dataflow::TConnectionReference<FManagedArrayCollection> GetConnectionReference(int32 Index) const;`
- L61 _private member_ `mutable TArray<FChaosClothAssetLodTransitionDataCache> LODTransitionDataCache;` — `UPROPERTY()`
- L64 _private member_ `mutable bool bClothCollectionChecksumValid = false;` — This is for runtime only--used to determine if only properties need to be updated.
- L65 _private member_ `mutable uint32 ClothColllectionChecksum = 0;`
- L66 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L67 _private member_ `static constexpr int32 NumInitialCollectionLods = 1;`

#### struct `FChaosClothAssetTerminalNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetTerminalNode : public FDataflowTerminalNode`  
_L73-142_
- reflection: `USTRUCT(Meta = (DataflowCloth, DataflowTerminal, Deprecated = 5.5))`
- inherits: `FDataflowTerminalNode`
- desc: Cloth terminal node to generate a cloth asset from a cloth collection.
- L80 _public member_ `static constexpr int32 MaxLods = 6;` — Hardcoded number of LODs since it is currently not possible to use arrays for optional inputs
- L84 _public member_ `FManagedArrayCollection CollectionLod0;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Collection LOD 0"))` — LOD 0 input, right click on the node and add pins to add more LODs.
- L87 _public member_ `FManagedArrayCollection CollectionLod1;` — `UPROPERTY(meta = (DisplayName = "Collection LOD 1"))` — LOD 1 input, right click on the node and add pins to add more LODs.
- L90 _public member_ `FManagedArrayCollection CollectionLod2;` — `UPROPERTY(meta = (DisplayName = "Collection LOD 2"))` — LOD 2 input, right click on the node and add pins to add more LODs.
- L93 _public member_ `FManagedArrayCollection CollectionLod3;` — `UPROPERTY(meta = (DisplayName = "Collection LOD 3"))` — LOD 3 input, right click on the node and add pins to add more LODs.
- L96 _public member_ `FManagedArrayCollection CollectionLod4;` — `UPROPERTY(meta = (DisplayName = "Collection LOD 4"))` — LOD 4 input, right click on the node and add pins to add more LODs.
- L99 _public member_ `FManagedArrayCollection CollectionLod5;` — `UPROPERTY(meta = (DisplayName = "Collection LOD 5"))` — LOD 5 input, right click on the node and add pins to add more LODs.
- L103 _public member_ `int32 NumLods = NumInitialCollectionLods;` — `UPROPERTY()` — The number of LODs currently exposed to the node UI.
- L112 _public member_ `mutable FChaosClothAssetTerminalNodeRefreshAsset RefreshAsset;` — `UPROPERTY(EditAnywhere, Category = "Cloth Asset Terminal")` — Refresh the asset even if the ClothCollection hasn't changed. Note that it is not required to manually refresh the cloth asset, this is done automatically when there is a change in the Dataflow. This function is a developper utility used for debugging.
- L115 _public prototype_ `FChaosClothAssetTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L119 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L120 _private function_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override`
- L121 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L122 _private function_ `virtual bool CanAddPin() const override`
- L123 _private function_ `virtual bool CanRemovePin() const override`
- L124 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L125 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L126 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L129 _private prototype_ `TArray<const FManagedArrayCollection*> GetCollectionLods() const;`
- L130 _private prototype_ `TArray<TSharedRef<const FManagedArrayCollection>> GetCleanedCollectionLodValues(UE::Dataflow::FContext& Context) const;`
- L131 _private prototype_ `const FManagedArrayCollection* GetCollectionLod(int32 LodIndex) const;`
- L134 _private member_ `mutable TArray<FChaosClothAssetLodTransitionDataCache> LODTransitionDataCache;` — `UPROPERTY()`
- L137 _private member_ `mutable bool bClothCollectionChecksumValid = false;` — This is for runtime only--used to determine if only properties need to be updated.
- L138 _private member_ `mutable uint32 ClothColllectionChecksum = 0;`
- L140 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L141 _private member_ `static constexpr int32 NumInitialCollectionLods = 1;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/TransferSkinWeightsNode.h` (Public)


#### enum `EChaosClothAssetTransferSkinWeightsMethod`  
`enum class EChaosClothAssetTransferSkinWeightsMethod : uint8`  
_L15-27_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `ClosestPointOnSurface` — For every vertex on the target mesh, find the closest point on the surface of the source mesh and copy its weights.
- L26 _public enumerator_ `InpaintWeights` — For every vertex on the target mesh, find the closest point on the surface of the source mesh. If that point position is within the search radius, and their normals differ by less than the specified normal threshold, then the vertex weights are directly copied from the source point to the target mesh vertex. For all other vertices whose weights didn't get transferred, smoothed weight values are automatically computed.

#### enum `EChaosClothAssetMaxNumInfluences`  
`enum class EChaosClothAssetMaxNumInfluences : uint8`  
_L31-37_
- reflection: `UENUM(BlueprintType)`
- L33 _public enumerator_ `Uninitialized = 0 UMETA(Hidden)`
- L34 _public enumerator_ `Four = 4 UMETA(DisplayName = "4")`
- L35 _public enumerator_ `Eight = 8 UMETA(DisplayName = "8")`
- L36 _public enumerator_ `Twelve = 12 UMETA(DisplayName = "12")`

#### enum `EChaosClothAssetTransferTargetMeshType`  
`enum class EChaosClothAssetTransferTargetMeshType : uint8`  
_L40-50_
- reflection: `UENUM(BlueprintType)`
- L43 _public enumerator_ `All UMETA(DisplayName = "Sim & Render Meshes")` — Perform the skin weights transfer for both the simulation and render meshes.
- L46 _public enumerator_ `Simulation UMETA(DisplayName = "Sim Mesh")` — Perform the skin weights transfer for the simulation mesh only.
- L49 _public enumerator_ `Render UMETA(DisplayName = "Render Mesh")` — Perform the skin weights transfer for the render mesh only.

#### enum `EChaosClothAssetTransferRenderMeshSource`  
`enum class EChaosClothAssetTransferRenderMeshSource : uint8`  
_L53-60_
- reflection: `UENUM(BlueprintType)`
- L56 _public enumerator_ `SkeletalMesh UMETA(DisplayName = "Skeletal Mesh")` — For render mesh, transfer weights from the source Skeletal Mesh.
- L59 _public enumerator_ `SimulationMesh UMETA(DisplayName = "Collection/Sim Collection")` — For render mesh, transfer weights from the Collection input sim mesh, or Sim Collection input if connected.

#### struct `FChaosClothAssetTransferSkinWeightsNode`  
`struct FChaosClothAssetTransferSkinWeightsNode : public FDataflowNode`  
_L64-184_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Transfer the skinning weights set on a skeletal mesh to the simulation and/or render mesh stored in the cloth collection.
- L72 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L76 _public member_ `EChaosClothAssetTransferTargetMeshType TargetMeshType = EChaosClothAssetTransferTargetMeshType::All;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (DisplayName = "Target Mesh(es)"))` — The type of cloth mesh the skeletal mesh transfer will be applied to, simulation, render mesh, or both.
- L81 _private member_ `FString SimMeshSourceTypeHint = TEXT("Ske` — `UPROPERTY(VisibleAnywhere, Category = "Transfer Skin Weights", Meta = (DisplayName = "Sim Mesh Transfer Source", EditCondition = "TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render", EditConditionHides))` — For the sim mesh, simulation mesh transfers always use the specified skeletal mesh.
- L86 _public member_ `EChaosClothAssetTransferRenderMeshSource RenderMeshSourceType = EChaosClothAssetTransferRenderMeshSource::SimulationMesh;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (DisplayName = "Render Mesh Transfer Source", EditCondition = "TargetMeshType != EChaosClothAssetTransferTargetMeshType::Simulation", EditConditionHides))` — For the render mesh, choose which source to use, either the default or specified simulation mesh or the specified skeletal mesh.
- L90 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (DataflowInput, EditCondition = "TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh", EditConditionHides))` — The skeletal mesh to transfer the skin weights from.
- L94 _public member_ `FManagedArrayCollection SimCollection;` — `UPROPERTY(Meta = (DataflowPassthrough = "Collection", Dataflowinput))` — The collection containing the sim mesh to use when the Render Mesh Transfer Source is set to Collection/Sim Collection. When this input isn't connected, the Collection input is used instead.
- L98 _public member_ `int32 LodIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (DisplayName = "LOD Index", EditCondition = "TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh", EditConditionHides, DataflowInput))` — The skeletal mesh LOD to transfer the skin weights from.
- L102 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (EditCondition = "TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh", EditConditionHides))` — The relative transform between the skeletal mesh and the cloth asset.
- L107 _private member_ `FString TransferMethodHint = TEXT("Clo` — `UPROPERTY(VisibleAnywhere, Category = "Transfer Skin Weights", Meta = (DisplayName = "Transfer Method", EditCondition = "TargetMeshType == EChaosClothAssetTransferTargetMeshType::Render && RenderMeshSourceType != EChaosClothAssetTransferRenderMeshSource::SkeletalMesh", EditConditionHides))` — Algorithm used for the transfer method. When the Render Mesh Transfer Source is set to use the sim mesh from the Collection/Sim Collection input, only the ClosestPointOnSurface method is available.
- L116 _public member_ `EChaosClothAssetTransferSkinWeightsMethod TransferMethod = EChaosClothAssetTransferSkinWeightsMethod::InpaintWeights;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (EditCondition = "TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh", EditConditionHides))` — Algorithm used for the transfer method. Use the simple ClosestPointOnSurface method or the more complex InpaintWeights method for better results. Note: When using the simulation mesh as source for the render mesh transfer, the algorithm will always be the ClosestPointOnSurface method, whatever this setting is.
- L124 _public member_ `double RadiusPercentage = 0.05;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (UIMin = -1, UIMax = 2, ClampMin = -1, ClampMax = 2, EditCondition = "(TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh) && TransferMethod == EChaosClothAssetTransferSkinWeightsMethod::InpaintWeights", EditConditionHides))` — Percentage of the bounding box diagonal of the simulation mesh to use as search radius for the InpaintWeights method. All points outside of the search radius will be ignored. When set to a negative value (e.g. -1), all points will be considered.
- L131 _public member_ `double NormalThreshold = 30;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (UIMin = -1, UIMax = 180, ClampMin = -1, ClampMax = 180, EditCondition = "(TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh) && TransferMethod == EChaosClothAssetTransferSkinWeightsMethod::InpaintWeights", EditConditionHides))` — Maximum angle difference (in degrees) between the target and source point normals to be considered a match for the InpaintWeights method. If set to a negative value (e.g. -1), normals will be ignored.
- L139 _public member_ `bool LayeredMeshSupport = true;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (EditCondition = "(TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh) && TransferMethod == EChaosClothAssetTransferSkinWeightsMethod::InpaintWeights", EditConditionHides))` — If true, when the closest point doesn't pass the normal threshold test, will try again with a flipped normal. This helps with layered meshes where the "inner" and "outer" layers are close to each other but whose normals are pointing in the opposite directions.
- L143 _public member_ `int32 NumSmoothingIterations = 10;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100, DisplayName = "Smoothing Iterations", EditCondition = "(TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh) && TransferMethod == EChaosClothAssetTransferSkinWeightsMethod::InpaintWeights", EditConditionHides))` — The number of smoothing iterations applied to the vertices whose weights were automatically computed.
- L147 _public member_ `float SmoothingStrength = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1, EditCondition = "(TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh) && TransferMethod == EChaosClothAssetTransferSkinWeightsMethod::InpaintWeights", EditConditionHides))` — The smoothing strength of each smoothing iteration.
- L151 _public member_ `FChaosClothAssetWeightedValueNonAnimatableNoLowHighRange InpaintMask = { TEXT("Inpai` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (EditCondition = "(TargetMeshType != EChaosClothAssetTransferTargetMeshType::Render || RenderMeshSourceType == EChaosClothAssetTransferRenderMeshSource::SkeletalMesh) && TransferMethod == EChaosClothAssetTransferSkinWeightsMethod::InpaintWeights", EditConditionHides))` — Optional mask where a non-zero value indicates that we want the skinning weights for the vertex to be computed automatically instead of it being copied over from the source mesh.
- L155 _public member_ `EChaosClothAssetMaxNumInfluences MaxNumInfluences = EChaosClothAssetMaxNumInfluences::Eight;` — `UPROPERTY(EditAnywhere, Category = "Transfer Skin Weights", Meta = (DisplayName = "Max Bone Influences"))` — The maximum number of bones that will influence each vertex.
- L157 _public prototype_ `FChaosClothAssetTransferSkinWeightsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L183 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;` — The node takes a user-selected skinned SkeletalMesh asset and transfers the skin weights to a simulation/render meshes using a selected algorithm. You can either transfer to simulation and render meshes separately or transfer to both in one go using the TargetMeshType property. When transferring to render meshes, you can control the source of the transfer which can either be the body or the simulation mesh (recommended). In the latter case we always use the ClosestPointOnSurface algorithm. InpaintWeights algorithm: Main algorithm for transferring weights, which is based on the "Robust Skin Weights Transfer via Weight Inpainting Siggraph Asia 2023". The implementation and explanation of the algorithm can be found in "Engine\Plugins\Runtime\GeometryProcessing\Source\DynamicMesh\Private\Operations\TransferBoneWeights.h(cpp)" Handling of disconnected render meshes: It is usually the case that sim mesh is welded and manifold meaning that the inpaint method should always succeed and give the best results. However, the render mesh is often not welded and consists of multiple disconnected parts. This is usually fine, and inpaint should work well except in places where there is a big crease along the stitch (like armpit areas), so vertices that are close to each other can have very different normals which could potentially lead to different weights being computed. You can either try to increase the normal threshold or switch to the closest point method.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/TransformPositionsNode.h` (Public)


#### struct `FChaosClothAssetTransformPositionsNode`  
`struct FChaosClothAssetTransformPositionsNode : public FDataflowNode`  
_L12-82_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- L20 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L24 _public member_ `bool bTransform2DSimPositions = false;` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 2D Sim")` — Enable Transforming 2D Sim Mesh Positions
- L28 _public member_ `FVector2f Sim2DScale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 2D Sim", Meta = (AllowPreserveRatio, EditCondition = "bTransform2DSimPositions"))` — 2D Sim Transform scale.
- L32 _public member_ `float Sim2DRotation = 0.f;` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 2D Sim", Meta = (UIMin = -360, UIMax = 360, ClampMin = -360, ClampMax = 360, EditCondition = "bTransform2DSimPositions"))` — 2D Sim Transform rotation angle in degrees.
- L36 _public member_ `FVector2f Sim2DTranslation = { 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 2D Sim", Meta = (EditCondition = "bTransform2DSimPositions"))` — 2D Sim Transform translation.
- L40 _public member_ `int32 Sim2DPattern = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 2D Sim", Meta = (UIMax = 10, ClampMin = -1, EditCondition = "bTransform2DSimPositions"))` — Sim Pattern to transform. All patterns will be used when set to -1.
- L44 _public member_ `bool bTransform3DSimPositions = false;` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 3D Sim")` — Enable Transforming 3D Sim Mesh Positions
- L48 _public member_ `FVector3f Sim3DScale = { 1.f, 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 3D Sim", Meta = (AllowPreserveRatio, EditCondition = "bTransform3DSimPositions"))` — 3D Sim Transform scale.
- L52 _public member_ `FVector3f Sim3DRotation = { 0.f, 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 3D Sim", Meta = (UIMin = -360, UIMax = 360, ClampMin = -360, ClampMax = 360, EditCondition = "bTransform3DSimPositions"))` — 3D Sim Transform rotation angle in degrees (Euler Angles)
- L56 _public member_ `FVector3f Sim3DTranslation = { 0.f, 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - 3D Sim", Meta = (EditCondition = "bTransform3DSimPositions"))` — 3D Sim Transform translation.
- L60 _public member_ `bool bTransformRenderPositions = false;` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - Render")` — Enable Transforming Render Positions
- L64 _public member_ `FVector3f RenderScale = { 1.f, 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - Render", Meta = (AllowPreserveRatio, EditCondition = "bTransformRenderPositions"))` — Render Transform scale.
- L68 _public member_ `FVector3f RenderRotation = { 0.f, 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - Render", Meta = (UIMin = -360, UIMax = 360, ClampMin = -360, ClampMax = 360, EditCondition = "bTransformRenderPositions"))` — Render Transform rotation angle in degrees (Euler Angles)
- L72 _public member_ `FVector3f RenderTranslation = { 0.f, 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - Render", Meta = (EditCondition = "bTransformRenderPositions"))` — Render Transform translation.
- L76 _public member_ `int32 RenderPattern = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "TransformPositions - Render", Meta = (UIMax = 10, ClampMin = -1, EditCondition = "bTransformRenderPositions"))` — Render Pattern to transform. All patterns will be used when set to -1.
- L78 _public prototype_ `FChaosClothAssetTransformPositionsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L81 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/TransformUVsNode.h` (Public)


#### struct `FChaosClothAssetTransformUVsNode`  
`struct FChaosClothAssetTransformUVsNode : public FDataflowNode`  
_L12-45_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- L20 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L24 _public member_ `FVector2f Scale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Transform UVs", Meta = (AllowPreserveRatio))` — Transform scale.
- L28 _public member_ `float Rotation = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Transform UVs", Meta = (UIMin = -360, UIMax = 360, ClampMin = -360, ClampMax = 360))` — Transform rotation angle in degrees.
- L32 _public member_ `FVector2f Translation = { 0.f, 0.f };` — `UPROPERTY(EditAnywhere, Category = "Transform UVs")` — Transform translation.
- L36 _public member_ `int32 Pattern = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Transform UVs", Meta = (UIMax = 10, ClampMin = -1))` — Pattern to transform. All patterns will be used when set to -1.
- L40 _public member_ `int32 UVChannel = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Transform UVs", Meta = (DataflowUVChannel, UIMax = 5, ClampMin = -1))` — UV channel to transform. All UV channels will be used when set to -1.
- L42 _public prototype_ `FChaosClothAssetTransformUVsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L44 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/USDImportNode.h` (Public)


#### struct `FChaosClothAssetUSDImportNode`  
`struct UE_DEPRECATED(5.5, "Use the newer version of this node instead.") FChaosClothAssetUSDImportNode : public FDataflowTerminalNode`  
_L12-54_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.5"))`
- inherits: `FDataflowTerminalNode`
- desc: Import a USD file from a third party garment construction software.
- L23 _public member_ `FChaosClothAssetImportFilePath UsdFile;` — `UE_DEPRECATED(5.7, "This node is deprecated, and this value can no longer be edited.")` — `UPROPERTY()`
- L25 _public prototype_ `FChaosClothAssetUSDImportNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L29 _private function_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override`
- L33 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L34 _private prototype_ `virtual void Serialize(FArchive& Archive) override;`
- L37 _private prototype_ `bool ImportFromCache(const TSharedRef<FManagedArrayCollection>& ClothCollection, class FText& OutErrorText) const;`
- L38 _private prototype_ `void UpdateImportedAssets();`
- L42 _private member_ `FString ImportedFilePath;` — `UPROPERTY(Transient, VisibleAnywhere, Category = "USD Import", Meta = (DisplayName = "USD File"))` — Name of the imported USD file. This node is deprecated, and this value can no longer be edited.
- L46 _private member_ `FString PackagePath;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — Content folder where all the USD assets are imported.
- L50 _private member_ `TArray<TObjectPtr<UObject>> ImportedAssets;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — List of all the dependent assets created from the USD import process.
- L52 _private member_ `FMD5Hash FileHash;`
- L53 _private member_ `FManagedArrayCollection CollectionCache;` — Content cache for data that hasn't got a USD schema yet

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/USDImportNode_v2.h` (Public)


#### struct `FChaosClothAssetUsdClothData`  
`struct FChaosClothAssetUsdClothData final`  
_L15-31_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Support struct for storage of the extra data that doesn't fit inside a static mesh.
- L19 _public member_ `TMap<FName, TSet<int32>> SimPatterns;`
- L20 _public member_ `TMap<FName, TSet<FIntVector2>> Sewings;`
- L21 _public member_ `TMap<FName, TSet<int32>> RenderPatterns;`
- L22 _public member_ `TMap<FName, TSet<FName>> RenderToSimPatterns;`
- L23 _public member_ `TMap<FName, int32> SimPatternFabricIndices;`
- L24 _public member_ `FManagedArrayCollection SimulationCollection;`
- L26 _public prototype_ `FChaosClothAssetUsdClothData();`
- L27 _public prototype_ `~FChaosClothAssetUsdClothData();`
- L29 _public prototype_ `void Reset();`
- L30 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosClothAssetUsdClothData> : public TStructOpsTypeTraitsBase2<FChaosClothAssetUsdClothData>`  
_L33-39_
- inherits: `TStructOpsTypeTraitsBase2<FChaosClothAssetUsdClothData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L36-38_

#### struct `FChaosClothAssetUSDImportNode_v2`  
`struct UE_DEPRECATED(5.8, "Use the newer version of this node instead.") FChaosClothAssetUSDImportNode_v2 : public FDataflowNode`  
_L43-130_
- reflection: `USTRUCT(Meta = (DataflowCloth, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Import a USD file from a third party garment construction software.
- L54 _public member_ `bool bImportSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "USD Import")` — Only import the simulation mesh data from the USD file.
- L58 _public member_ `bool bImportRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "USD Import")` — Only import the render mesh data from the USD file.
- L62 _public member_ `bool bImportWithOpacity = false;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (EditCondition = "bImportRenderMesh", EditConditionHides))` — Importing the render mesh with opacity requires transluscency to be enable in the project settings.
- L66 _public member_ `FChaosClothAssetImportFilePath UsdFile;` — `UE_DEPRECATED(5.8, "This node is deprecated, and this value can no longer be edited.")` — `UPROPERTY()`
- L70 _public member_ `FDataflowFunctionProperty ReimportUsdFile;` — `UE_DEPRECATED(5.8, "This node is deprecated, and this function can no longer be triggered.")` — `UPROPERTY()`
- L74 _public member_ `FDataflowFunctionProperty ReloadSimStaticMesh;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (ButtonImage = "Icons.Refresh", EditCondition = "ImportedSimStaticMesh != nullptr && bImportSimMesh", EditConditionHides))` — The USD import process generates an intermediary simulation static mesh. Click on this button to reimport it without reimporting the USD file.
- L78 _public member_ `FDataflowFunctionProperty ReloadRenderStaticMesh;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (ButtonImage = "Icons.Refresh", EditCondition = "ImportedRenderStaticMesh != nullptr && bImportRenderMesh", EditConditionHides))` — The USD import process generates an intermediary render static mesh. Click on this button to reimport it without reimporting the USD file.
- L80 _public prototype_ `FChaosClothAssetUSDImportNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L84 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L85 _private prototype_ `virtual void Serialize(FArchive& Archive) override;`
- L89 _private prototype_ `bool ImportSimStaticMesh(const TSharedRef<FManagedArrayCollection> ClothCollection, class FText& OutErrorText);` — Import the given static mesh as a simulation mesh into the cloth collection
- L91 _private prototype_ `bool ImportRenderStaticMesh(const TSharedRef<FManagedArrayCollection> ClothCollection, class FText& OutErrorText);` — Import the given static mesh as a render mesh into the cloth collection
- L94 _private prototype_ `void UpdateImportedAssets(const FString& SimMeshName, const FString& RenderMeshName);` — Find the two imported static meshes
- L98 _private member_ `FString PackagePath;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — Content folder where all the USD assets are imported.
- L106 _private member_ `TObjectPtr<UStaticMesh> ImportedSimStaticMesh;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — The static mesh created from the USD import process used as simulation mesh. Note that this property can still be empty after successfully importing a simulation mesh depending on whether the simulation mesh is imported from an older version of USD cloth schema.
- L110 _private member_ `FVector2f ImportedUVScale = { 1.f, 1.f };` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — The UV scale used to import the patterns from the imported static mesh UV coordinates.
- L114 _private member_ `TObjectPtr<UStaticMesh> ImportedRenderStaticMesh;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — The static mesh created from the USD import process used as render mesh.
- L118 _private member_ `TArray<TObjectPtr<UObject>> ImportedSimAssets;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — List of all the simulation static mesh's dependent assets. This does not include any Engine, or Engine plugin content.
- L122 _private member_ `TArray<TObjectPtr<UObject>> ImportedRenderAssets;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — List of all the render static mesh's dependent assets. This does not include any Engine, or Engine plugin content.
- L126 _private member_ `FChaosClothAssetUsdClothData UsdClothData;` — `UPROPERTY()` — Support struct for storage of the extra data that doesn't fit inside a static mesh.
- L129 _private member_ `TArray<TObjectPtr<UObject>> ImportedAssets_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L37 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonade3533a0103`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/WeightMapNode.h` (Public)


#### enum `EChaosClothAssetWeightMapMeshTarget`  
`enum class EChaosClothAssetWeightMapMeshTarget : uint8`  
_L23-27_
- reflection: `UENUM()`
- desc: Which mesh to update with the node's weight map
- L25 _public enumerator_ `Simulation`
- L26 _public enumerator_ `Render`

#### struct `FChaosClothAssetWeightMapNode`  
`struct FChaosClothAssetWeightMapNode : public FDataflowVertexAttributeEditableNode`  
_L32-133_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowVertexAttributeEditableNode`
- desc: Painted weight map attributes node.
- L40 _public member_ `static constexpr float ReplaceChangedPassthroughValue = UE_BIG_NUMBER;`
- L43 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L47 _public member_ `FManagedArrayCollection TransferCollection;` — `UPROPERTY(Meta = (DataflowInput))` — The collection used to transfer weight map from.
- L51 _public member_ `FChaosClothAssetConnectableOStringValue OutputName;` — `UPROPERTY(EditAnywhere, Category = "Weight Map")` — The name to be set as a weight map attribute.
- L55 _public member_ `FChaosClothAssetConnectableIStringValue InputName = { TEXT("") };` — `UPROPERTY(EditAnywhere, Category = "Weight Map")` — The name to populate this map from and override based on Map Override Type. Output Name will be used if Input Name is empty.
- L58 _public member_ `EChaosClothAssetWeightMapMeshTarget MeshTarget = EChaosClothAssetWeightMapMeshTarget::Simulation;` — `UPROPERTY(EditAnywhere, Category = "Weight Map")`
- L63 _public member_ `EChaosClothAssetWeightMapOverrideType MapOverrideType = EChaosClothAssetWeightMapOverrideType::ReplaceChanged;` — `UPROPERTY(EditAnywhere, Category = "Weight Map")` — How to apply this node's weight values onto existing maps. Changing this value will change the output map. To change how the node's stored weights are calculated, change the equivalent value on the Weight Map Paint Tool context.
- L72 _public member_ `EChaosClothAssetWeightMapTransferType TransferType = EChaosClothAssetWeightMapTransferType::Use2DSimMesh;` — `UPROPERTY(EditAnywhere, Category = "Weight Map")` — The type of transfer used to transfer the weight map when a TransferCollection is connected and MeshTarget is Simulation. Use "Use Render Mesh" to transfer from an imported render mesh into the sim mesh via 3D spatial mapping. Render weight maps (MeshTarget == Render) always do a 3D transfer regardless of this setting. This property is disabled when no TransferCollection input has been connected.
- L76 _public member_ `FDataflowFunctionProperty Transfer;` — `UPROPERTY(EditAnywhere, Category = "Weight Map", Meta = (ButtonImage = "Icons.Convert"))` — Transfer the weight map from the connected Transfer Collection containing a weight map with Input Name (or Output Name if Input Name is empty).
- L78 _public prototype_ `FChaosClothAssetWeightMapNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L84 _private prototype_ `static TUniquePtr<class FToolCommandChange> MakeWeightMapNodeChange(FChaosClothAssetWeightMapNode& Node);`
- L86 _private function_ `const TArray<float>& GetLegacyVertexWeights() const`
- L89 _private prototype_ `FName GetInputName(UE::Dataflow::FContext& Context) const;` — These methods are exported for UClothEditorWeightMapPaintTool which lives in a different module.
- L91 _private prototype_ `void SetVertexWeights(const TConstArrayView<float> InputMap, const TArray<float>& FinalValues);`
- L94 _private prototype_ `void CalculateFinalVertexWeightValues(UE::Chaos::ClothAsset::FCollectionClothConstFacade* ClothFacade, const TConstArrayView<float> InputMap, TArrayView<float> FinalOutputMap) const;` — Input and FinalOutputMap can be the same array, but should not otherwise be interleaved.
- L97 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L98 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L99 _private prototype_ `virtual FDataflowOutput* RedirectSerializedOutput(const FName& MissingOutputName) override;`
- L103 _private prototype_ `virtual void GetSupportedViewModes(UE::Dataflow::FContext& Context, TArray<FName>& OutViewModeNames) const override;`
- L104 _private prototype_ `virtual void GetVertexAttributeValues(UE::Dataflow::FContext& Context, TArray<float>& OutValues) const override;`
- L105 _private prototype_ `virtual void SetVertexAttributeValues(UE::Dataflow::FContext& Context, const TArray<float>& InValues, const TArray<int32>& InWeightIndices) override;`
- L106 _private prototype_ `virtual void GetExtraVertexMapping(UE::Dataflow::FContext& Context, FName SelectedViewMode, TArray<int32>& OutMappingToWeight, TArray<TArray<int32>>& OutMappingFromWeight) const override;`
- L109 _private prototype_ `void OnTransfer(UE::Dataflow::FContext& Context);`
- L116 _private prototype_ `void GetWeightsFromSnapshot(UE::Chaos::ClothAsset::FCollectionClothConstFacade* ClothFacade, const FDataflowToolNodeSnapshot& Snapshot, TArray<float>& OutValues) const;` — Get weights values from a specific snaphot If there's data in the snapshot, the original topology wioll be compared to the one in the optional ClothFacade, and data will be projected to match the new topology if needed
- L117 _private prototype_ `void GetWeightsFromActiveSnapshot(UE::Chaos::ClothAsset::FCollectionClothConstFacade* ClothFacade, TArray<float>& OutValues) const;`
- L123 _private prototype_ `void StoreWeightsInSnapshot(UE::Chaos::ClothAsset::FCollectionClothConstFacade* ClothFacade, const TArray<float>& InValues, FDataflowToolNodeSnapshot& OutSnapshot) const;` — store weights values in a specific snapshot if the cloth facade is available, the topology information will be also stored in the snapshot
- L128 _private member_ `TArray<float> VertexWeights;` — `UPROPERTY()` — This property should be technically deprecated but we need to keep it because we cannot post serialize fix it as we need a dataflow Context to create a snapshot deprecated methods are still using it and we still use it to load the data when there's no pre-existing snapshot
- L132 _private member_ `FString Name;` — `UE_DEPRECATED(5.5, "Use OutputName instead.")` — `UPROPERTY()` — TODO: Discard in future v2. but keep for backward compatibility here as some weight maps have been created with it

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Dataflow`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Chaos` (scope `UE`)
- L15 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/WeightMapToSelectionNode.h` (Public)


#### enum `EChaosClothAssetWeightMapConvertableSelectionType`  
`enum class EChaosClothAssetWeightMapConvertableSelectionType : uint8`  
_L13-23_
- reflection: `UENUM()`
- desc: What type of element to convert to
- L16 _public enumerator_ `SimVertices2D` — 2D simulation vertices
- L19 _public enumerator_ `SimVertices3D` — 3D simulation vertices
- L22 _public enumerator_ `SimFaces` — Simulation faces (2D/3D are the same)

#### struct `FChaosClothAssetWeightMapToSelectionNode`  
`struct FChaosClothAssetWeightMapToSelectionNode : public FDataflowNode`  
_L27-60_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Convert a vertex weight map to an integer selection set.
- L35 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (Dataflowinput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L39 _public member_ `FString WeightMapName;` — `UPROPERTY(Meta = (DataflowInput))` — The name of the Weight Map to convert.
- L46 _public member_ `FString SelectionName;` — `UPROPERTY(EditAnywhere, Category = "Weight Map To Selection", Meta = (DataflowOutput, DataflowSelection))` — The name of the select attribute that will be added to the collection. If left empty the same name as the Weight Map  name will be used instead.
- L50 _public member_ `EChaosClothAssetWeightMapConvertableSelectionType SelectionType = EChaosClothAssetWeightMapConvertableSelectionType::SimVertices3D;` — `UPROPERTY(EditAnywhere, Category = "Weight Map To Selection")` — The type of element the selection refers to
- L54 _public member_ `float SelectionThreshold = 0.95f;` — `UPROPERTY(EditAnywhere, Category = "Weight Map To Selection", Meta = (ClampMin = "0", ClampMax = "1"))` — Map values above this will be selected.
- L56 _public prototype_ `FChaosClothAssetWeightMapToSelectionNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L59 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Dataflow`

### `Plugins/ChaosClothAssetDataflowNodes/Source/ChaosClothAssetDataflowNodes/Public/ChaosClothAsset/WeightedValue.h` (Public)


#### struct `UE::Chaos::ClothAsset::FWeightMapTools`  
`struct FWeightMapTools`  
_L10-23_
- L14 _public member_ `inline static const FString NotOverridden = TEXT("#")` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")`
- L22 _public prototype_ `static void MakeWeightMapName(FString& InOutString);` — Modifies a string to make it suitable as a weight map name. Replaces any deemed special characters and spaces by underscores, and remove leading and ending underscores from the name. Note that leading underscores are reserved for non user/internal attribute names.

#### struct `UE::Chaos::ClothAsset::FWeightedValueBounds`  
`struct FWeightedValueBounds`  
_L26-30_
- desc: Weight value bounds that could be used to build a cloth asset weighted value
- L28 _public member_ `float Low;`
- L29 _public member_ `float High;`

#### struct `FChaosClothAssetWeightedValue`  
`struct FChaosClothAssetWeightedValue`  
_L35-92_
- reflection: `USTRUCT()`
- L45 _public member_ `bool bIsAnimatable = true;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value")` — Whether the property can ever be updated/animated in real time. This could make the simulation takes more CPU time, even more so if the weight maps needs updating.
- L55 _public member_ `mutable float Low = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "Low Weight", ChaosClothAssetShortName = "Lo", EditCondition = "!bImportFabricBounds"))` — Property value corresponding to the lower bound of the Weight Map. A Weight Map stores a series of Weight values assigned to each point, all between 0 and 1. The weights are used to interpolate the individual values from Low to High assigned to each different point. A Weight of 0 always corresponds to the Low parameter value, and a Weight of 1 to the High parameter value. The value for Low can be set to be bigger than for High in order to reverse the effect of the Weight Map.
- L65 _public member_ `mutable float High = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "High Weight", ChaosClothAssetShortName = "Hi", EditCondition = "!bImportFabricBounds"))` — Property value corresponding to the upper bound of the Weight Map. A Weight Map stores a series of Weight values assigned to each point, all between 0 and 1. The weights are used to interpolate the individual values from Low to High assigned to each different point. A Weight of 0 always corresponds to the Low parameter value, and a Weight of 1 to the High parameter value. The value for Low can be set to be bigger than for High in order to reverse the effect of the Weight Map.
- L69 _public member_ `mutable FString WeightMap = TEXT("Wei` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DataflowInput))` — The name of the weight map for this property.
- L75 _public member_ `bool bCouldUseFabrics = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Weighted Value", Meta = (EditCondition = "false", EditConditionHides))` — Whether the property could import fabrics datas or not
- L79 _public member_ `mutable FString WeightMap_Override;` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")` — `UPROPERTY(Transient)`
- L85 _public member_ `bool bImportFabricBounds = false;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (EditCondition = "bCouldUseFabrics", EditConditionHides))` — Whether the property can use the fabric bounds (low/high) values imported from USD
- L91 _public member_ `bool bBuildFabricMaps = false;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (EditCondition = "bCouldUseFabrics", EditConditionHides))` — Whether the property can override the weight map based on the imported fabrics

#### struct `FChaosClothAssetWeightedValueNonAnimatable`  
`struct FChaosClothAssetWeightedValueNonAnimatable`  
_L96-148_
- reflection: `USTRUCT()`
- L101 _public member_ `static constexpr bool bIsAnimatable = false;`
- L111 _public member_ `mutable float Low = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "Low Weight", ChaosClothAssetShortName = "Lo", EditCondition = "!bImportFabricBounds"))` — Property value corresponding to the lower bound of the Weight Map. A Weight Map stores a series of Weight values assigned to each point, all between 0 and 1. The weights are used to interpolate the individual values from Low to High assigned to each different point. A Weight of 0 always corresponds to the Low parameter value, and a Weight of 1 to the High parameter value. The value for Low can be set to be bigger than for High in order to reverse the effect of the Weight Map.
- L121 _public member_ `mutable float High = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "High Weight", ChaosClothAssetShortName = "Hi", EditCondition = "!bImportFabricBounds"))` — Property value corresponding to the upper bound of the Weight Map. A Weight Map stores a series of Weight values assigned to each point, all between 0 and 1. The weights are used to interpolate the individual values from Low to High assigned to each different point. A Weight of 0 always corresponds to the Low parameter value, and a Weight of 1 to the High parameter value. The value for Low can be set to be bigger than for High in order to reverse the effect of the Weight Map.
- L125 _public member_ `mutable FString WeightMap = TEXT("Wei` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DataflowInput))` — The name of the weight map for this property.
- L131 _public member_ `bool bCouldUseFabrics = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Weighted Value", Meta = (EditCondition = "false", EditConditionHides))` — Whether the property could import fabrics datas or not
- L135 _public member_ `mutable FString WeightMap_Override;` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")` — `UPROPERTY(Transient)`
- L141 _public member_ `bool bImportFabricBounds = false;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (EditCondition = "bCouldUseFabrics", EditConditionHides))` — Whether the property can use the fabric bounds (low/high) values imported from USD
- L147 _public member_ `bool bBuildFabricMaps = false;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (EditCondition = "bCouldUseFabrics", EditConditionHides))` — Whether the property can override the weight map based on the imported fabrics

#### struct `FChaosClothAssetWeightedValueNonAnimatableNoLowHighRange`  
`struct FChaosClothAssetWeightedValueNonAnimatableNoLowHighRange`  
_L152-164_
- reflection: `USTRUCT()`
- L159 _public member_ `FString WeightMap = TEXT("Wei` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DataflowInput))` — The name of the weight map for this property.
- L163 _public member_ `mutable FString WeightMap_Override;` — `UE_DEPRECATED(5.5, "Override properties are no longer used.")` — `UPROPERTY(Transient)`

#### struct `FChaosClothAssetWeightedValueOverride`  
`struct FChaosClothAssetWeightedValueOverride`  
_L167-182_
- reflection: `USTRUCT()`
- L175 _public member_ `float Low = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "Low Weight", ChaosClothAssetShortName = "Lo"))` — Low value override.
- L181 _public member_ `float High = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "High Weight", ChaosClothAssetShortName = "Hi"))` — High value override

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Chaos` (scope `UE`)
- L8 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
