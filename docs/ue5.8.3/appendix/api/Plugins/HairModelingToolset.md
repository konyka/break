# Plugins / HairModelingToolset

- module root: `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset`
- headers: 7; symbols: 309
- symbol kinds: class=20, enum=2, enumerator=11, function=24, member=136, namespace=2, prototype=104, struct=10
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, ContentBrowser, CoreUObject, EditorFramework, Engine, InputCore, LevelEditor, Niagara, PhysicsCore, Projects, RHI, RenderCore, Slate, SlateCore, StatusBar, UnrealEd
- PublicDependencyModuleNames: Core, DynamicMesh, Eigen, GeometryAlgorithms, GeometryCore, GeometryFramework, HairStrandsCore, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsExp, ModelingComponents, ModelingOperators, ModelingOperatorsEditorOnly, ModelingToolsEditorMode, StaticMeshDescription

### `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset/Private/GroomQueryUtil.h` (Private)


#### struct `UE::GroomQueries::FCardSourceInfo`  
`struct FCardSourceInfo`  
_L22-29_
- desc: source card information
- L24 _public member_ `int32 GroupIndex;` — groom asset group
- L25 _public member_ `int32 LODIndex;` — groom asset LOD
- L26 _public member_ `int32 CardIndex;` — index of card into card arrays
- L27 _public member_ `int32 IndexOffset;` — index offset into card triangle buffer
- L28 _public member_ `int32 IndexCount;` — number of indices after offset that belong to this card

#### struct `UE::GroomQueries::FMeshCardStrip`  
`struct FMeshCardStrip`  
_L31-57_
- L33 _public member_ `FCardSourceInfo SourceInfo;`
- L35 _public member_ `int32 GroupID;`
- L36 _public member_ `TArray<int32> Triangles;`
- L38 _public member_ `TArray<FIndex2i> QuadTriPairs;`
- L39 _public member_ `TArray<FIndex4i> QuadLoops;`
- L41 _public member_ `TArray<FVector3d> CardCurve;`
- L42 _public member_ `TArray<FFrame3d> CardCurveFrames;`
- L43 _public member_ `TArray<double> CardCurveWidth;`
- L45 _public function_ `FIndex2i GetCurvePointVertices(int32 Index) const`

#### struct `UE::GroomQueries::FMeshCardStripSet`  
`struct FMeshCardStripSet`  
_L59-68_
- L61 _public member_ `TArray<FMeshCardStrip> CardStrips;`
- L64 _public member_ `TMap<int32,int32> TriGroupToCardIndex;` — map from mesh triangle GroupIDs to CardStrips array index
- L66 _public prototype_ `const FMeshCardStrip& FindStripForGroup(int32 GroupIdx) const;`
- L67 _public prototype_ `FMeshCardStrip& FindStripForGroup(int32 GroupIdx);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace GroomQueries` (scope `UE`)
- L70 _prototype_ `void ExtractAllHairCards(AGroomActor* GroomActor, int32 LODIndex, FDynamicMesh3& MeshOut, FMeshCardStripSet* CardsOut = nullptr);` (scope `UE::GroomQueries`)
- L75 _prototype_ `void ExtractAllHairCards( const FMeshDescription* SourceMeshIn, FDynamicMesh3& MeshOut, FMeshCardStripSet& CardsOut);` (scope `UE::GroomQueries`)
- L80 _prototype_ `void ExtractCardQuads( const FDynamicMesh3& Mesh, FMeshCardStripSet& CardsInOut);` (scope `UE::GroomQueries`)
- L84 _prototype_ `void ExtractCardCurves( const FDynamicMesh3& Mesh, FMeshCardStripSet& CardsInOut);` (scope `UE::GroomQueries`)
- L88 _prototype_ `void ProcessHairCurves(AGroomActor* GroomActor, bool bUseGuides, TFunctionRef<void(const TArrayView<FVector3f>& Positions, const TArrayView<float>& Radii)> HairCurveFunc);` (scope `UE::GroomQueries`)

### `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset/Public/GenerateLODMeshesTool.h` (Public)


#### class `UGenerateLODMeshesToolBuilder`  
`class UGenerateLODMeshesToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L22-27_
- reflection: `UCLASS()`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L26 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### struct `FLODLevelGenerateSettings`  
`struct FLODLevelGenerateSettings`  
_L32-63_
- reflection: `USTRUCT()`
- L38 _public member_ `ESimplifyType SimplifierType = ESimplifyType::UEStandard;` — `UPROPERTY(EditAnywhere, Category = Options)` — Simplification Scheme
- L42 _public member_ `ESimplifyTargetType TargetMode = ESimplifyTargetType::Percentage;` — `UPROPERTY(EditAnywhere, Category = Options)` — Simplification Target Type
- L46 _public member_ `int32 TargetPercentage = 100;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "100", EditConditionHides, EditCondition = "TargetMode == ESimplifyTargetType::Percentage"))` — Target percentage
- L50 _public member_ `int32 TargetCount = 500;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "4", UIMax = "10000", ClampMin = "1", ClampMax = "9999999999", EditConditionHides, EditCondition = "TargetMode == ESimplifyTargetType::TriangleCount || TargetMode == ESimplifyTargetType::VertexCount"))` — Target vertex/triangle count
- L54 _public member_ `bool bReproject = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Options)` — Target vertex/triangle count
- L57 _public member_ `FString Result;` — `UPROPERTY(VisibleAnywhere, Category = Options)`
- L59 _public function_ `bool operator!=(const FLODLevelGenerateSettings& Other)`

#### class `UGenerateLODMeshesToolProperties`  
`class UGenerateLODMeshesToolProperties : public UMeshConstraintProperties`  
_L71-128_
- reflection: `UCLASS()`
- inherits: `UMeshConstraintProperties`
- desc: Standard properties of the Simplify operation
- L75 _public prototype_ `UGenerateLODMeshesToolProperties();`
- L80 _public member_ `ESimplifyTargetType TargetMode = ESimplifyTargetType::Percentage;` — `UPROPERTY(EditAnywhere, Category = Options)` — `UPROPERTY()` — Simplification Target Type
- L85 _public member_ `ESimplifyType SimplifierType = ESimplifyType::UEStandard;` — `UPROPERTY(EditAnywhere, Category = Options)` — `UPROPERTY()` — Simplification Scheme
- L89 _public member_ `int NameIndexBase = 0;` — `UPROPERTY(EditAnywhere, Category = Options)` — Output LOD Assets will be numbered starting at this number
- L94 _public member_ `int TargetPercentage = 50;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "100", EditCondition = "TargetMode == ESimplifyTargetType::Percentage"))` — `UPROPERTY()` — Target percentage of original triangle count
- L99 _public member_ `float TargetEdgeLength;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "3.0", UIMax = "10.0", ClampMin = "0.001", ClampMax = "1000.0", EditCondition = "TargetMode == ESimplifyTargetType::EdgeLength && SimplifierType != ESimplifyType::UEStandard"))` — `UPROPERTY()` — Target edge length
- L104 _public member_ `int TargetCount = 1000;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "4", UIMax = "10000", ClampMin = "1", ClampMax = "9999999999", EditCondition = "TargetMode == ESimplifyTargetType::TriangleCount"))` — `UPROPERTY()` — Target triangle/vertex count
- L109 _public member_ `bool bDiscardAttributes = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — `UPROPERTY()` — Discard UVs and existing normals, allowing the simplifier to ignore any UV and normal seams. New per-vertex normals are computed.
- L113 _public member_ `bool bShowWireframe = false;` — `UPROPERTY(EditAnywhere, Category = Display)` — If true, display wireframe
- L118 _public member_ `bool bShowGroupColors = false;` — `UPROPERTY(EditAnywhere, Category = Display)` — `UPROPERTY()` — Display colors corresponding to the mesh's polygon groups
- L123 _public member_ `bool bReproject;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay)` — `UPROPERTY()` — Enable projection back to input mesh
- L126 _public member_ `TArray<FLODLevelGenerateSettings> LODLevels;` — `UPROPERTY(EditAnywhere, Category = Options)`

#### class `FGenerateLODOperatorFactory`  
`class FGenerateLODOperatorFactory : public UE::Geometry::IDynamicMeshOperatorFactory`  
_L132-141_
- inherits: `UE::Geometry::IDynamicMeshOperatorFactory`
- L135 _public member_ `TWeakObjectPtr<UGenerateLODMeshesTool> ParentTool;`
- L136 _public member_ `FLODLevelGenerateSettings LODSettings;`
- L137 _public member_ `FTransform UseTransform;`
- L140 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API

#### class `UGenerateLODMeshesTool`  
`class UGenerateLODMeshesTool : public USingleSelectionMeshEditingTool`  
_L149-192_
- reflection: `UCLASS()`
- inherits: `USingleSelectionMeshEditingTool`
- desc: Simple Mesh Simplifying Tool
- L154 _public prototype_ `virtual void Setup() override;`
- L155 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L157 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L158 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L160 _public function_ `virtual bool HasCancel() const override`
- L161 _public function_ `virtual bool HasAccept() const override`
- L162 _public prototype_ `virtual bool CanAccept() const override;`
- L168 _private member_ `TObjectPtr<UGenerateLODMeshesToolProperties> SimplifyProperties;` — `UPROPERTY()`
- L171 _private member_ `TArray<TObjectPtr<UMeshOpPreviewWithBackgroundCompute>> Previews;` — `UPROPERTY()`
- L173 _private member_ `TArray<TUniquePtr<FGenerateLODOperatorFactory>> PreviewFactories;`
- L176 _private prototype_ `void UpdateNumPreviews();`
- L177 _private prototype_ `void InvalidateAllPreviews();`
- L179 _private member_ `TSharedPtr<FMeshDescription, ESPMode::ThreadSafe> OriginalMeshDescription;`
- L181 _private member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Dynamic Mesh versions precomputed in Setup (rather than recomputed for every simplify op)
- L182 _private member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> OriginalMeshSpatial;`
- L184 _private member_ `TArray<FLODLevelGenerateSettings> CachedLODLevels;`
- L186 _private member_ `UE::Geometry::FAxisAlignedBox3d WorldBounds;`
- L188 _private prototype_ `void GenerateAssets();`
- L189 _private prototype_ `void UpdateVisualization();`
- L191 _private prototype_ `void OnPreviewUpdated(UMeshOpPreviewWithBackgroundCompute*);`

### `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset/Public/GroomCardsEditorTool.h` (Public)


#### class `UGroomCardsEditorToolBuilder`  
`class UGroomCardsEditorToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L34-39_
- reflection: `UCLASS()`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- L38 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `EEditGroomCardsToolActions`  
`enum class EEditGroomCardsToolActions`  
_L45-55_
- reflection: `UENUM()`
- L47 _public enumerator_ `NoAction`
- L48 _public enumerator_ `Delete`
- L49 _public enumerator_ `SelectionClear`
- L50 _public enumerator_ `SelectionFill`
- L51 _public enumerator_ `SelectionAddNext`
- L52 _public enumerator_ `SelectionAddPrevious`
- L53 _public enumerator_ `SelectionAddToEnd`
- L54 _public enumerator_ `SelectionAddToStart`

#### class `UEditGroomCardsToolActionPropertySet`  
`class UEditGroomCardsToolActionPropertySet : public UInteractiveToolPropertySet`  
_L59-69_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L64 _public member_ `TWeakObjectPtr<UGroomCardsEditorTool> ParentTool;`
- L66 _public function_ `void Initialize(UGroomCardsEditorTool* ParentToolIn)`
- L68 _public prototype_ `void PostAction(EEditGroomCardsToolActions Action);`

#### class `USelectGroomCardsToolActions`  
`class USelectGroomCardsToolActions : public UEditGroomCardsToolActionPropertySet`  
_L73-101_
- reflection: `UCLASS()`
- inherits: `UEditGroomCardsToolActionPropertySet`
- L79 _public function_ `void Clear()` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayPriority = 1))` — Clear the current selection
- L83 _public function_ `void Fill()` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayPriority = 1))` — Select unselected points along curve between selected points
- L87 _public function_ `void AddNext()` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayPriority = 3))` — Add the next vertex along the card curve to the selection
- L91 _public function_ `void AddPrevious()` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayPriority = 4))` — Add the previous vertex along the card curve to the selection
- L95 _public function_ `void ToEnd()` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayPriority = 5))` — Select all vertices to the end of the card
- L99 _public function_ `void ToStart()` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayPriority = 6))` — Select all vertices to the start of the card

#### class `UEditGroomCardsToolActions`  
`class UEditGroomCardsToolActions : public UEditGroomCardsToolActionPropertySet`  
_L106-113_
- reflection: `UCLASS()`
- inherits: `UEditGroomCardsToolActionPropertySet`
- L112 _public function_ `void Delete()` — `UFUNCTION(CallInEditor, Category = FaceEdits, meta = (DisplayName = "Delete", DisplayPriority = 10))` — Delete the current selected cards

#### class `UGroomCardsInfoToolProperties`  
`class UGroomCardsInfoToolProperties : public UInteractiveToolPropertySet`  
_L124-138_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L130 _public member_ `int32 NumCards = 0;` — `UPROPERTY(VisibleAnywhere, Category = Statistics)`
- L133 _public member_ `int32 NumVertices = 0;` — `UPROPERTY(VisibleAnywhere, Category = Statistics)`
- L136 _public member_ `int32 NumTriangles = 0;` — `UPROPERTY(VisibleAnywhere, Category = Statistics)`

#### class `UGroomCardsEditorTool`  
`class UGroomCardsEditorTool : public UMeshSurfacePointTool, public IClickBehaviorTarget`  
_L146-286_
- reflection: `UCLASS()`
- inherits: `UMeshSurfacePointTool,IClickBehaviorTarget`
- L151 _public prototype_ `UGroomCardsEditorTool();`
- L153 _public function_ `virtual void SetWorld(UWorld* World)`
- L155 _public prototype_ `virtual void Setup() override;`
- L156 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L158 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L159 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L161 _public function_ `virtual bool HasCancel() const override`
- L162 _public prototype_ `virtual bool HasAccept() const override;`
- L163 _public prototype_ `virtual bool CanAccept() const override;`
- L167 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;` — UMeshSurfacePointTool API
- L168 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L169 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L170 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L171 _public prototype_ `virtual void OnCancelDrag() override;`
- L172 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L173 _public prototype_ `virtual void OnEndHover() override;`
- L176 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget API
- L179 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L180 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L184 _public prototype_ `void RequestAction(EEditGroomCardsToolActions ActionType);` — actions API
- L188 _protected member_ `TObjectPtr<USelectGroomCardsToolActions> SelectActions;` — `UPROPERTY()`
- L191 _protected member_ `TObjectPtr<UEditGroomCardsToolActions> EditActions;` — `UPROPERTY()`
- L194 _protected member_ `TObjectPtr<UGroomCardsInfoToolProperties> InfoProperties;` — `UPROPERTY()`
- L197 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L200 _protected member_ `TSoftObjectPtr<AGroomActor> TargetGroom;` — `UPROPERTY()`
- L203 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeom;` — `UPROPERTY()`
- L208 _protected member_ `TObjectPtr<UMaterialInterface> MeshMaterial;` — `UPROPERTY()`
- L211 _protected member_ `TObjectPtr<UMaterialInterface> UVMaterial;` — `UPROPERTY()`
- L216 _protected member_ `TObjectPtr<UPolygonSelectionMechanic> CardMeshSelectionMechanic;` — `UPROPERTY()`
- L219 _protected member_ `TObjectPtr<USpaceCurveDeformationMechanic> ControlPointsMechanic;` — `UPROPERTY()`
- L222 _protected member_ `bool bSelectionStateDirty = false;`
- L223 _protected prototype_ `void OnSelectionModifiedEvent();`
- L227 _protected member_ `UWorld* TargetWorld = nullptr;`
- L229 _protected member_ `TPimplPtr<FEditableGroomCardSet> EditableCardSet;`
- L231 _protected prototype_ `void BeginCardEdit(int32 CardGroupID);`
- L232 _protected prototype_ `void RestoreCardEdit(const FGroomCardEdit* RestoreEdit);`
- L233 _protected prototype_ `void EndCardEdit();`
- L234 _protected prototype_ `void CompleteActiveCardEditAndEmitChanges();`
- L236 _protected member_ `TPimplPtr<FGroomCardEdit> ActiveCardEdit;`
- L237 _protected member_ `int32 ActiveCardGroupID = -1;`
- L238 _protected member_ `bool bCurveUpdatePending = false;`
- L239 _protected member_ `bool bActiveCardEditUpdated = false;`
- L240 _protected prototype_ `void UpdateOnCurveEdit();`
- L242 _protected member_ `FMeshVertexChangeBuilder* ActiveVertexChange = nullptr;`
- L243 _protected prototype_ `void BeginMoveChange();`
- L244 _protected prototype_ `void EndMoveChange();`
- L246 _protected member_ `TSharedPtr<FSpaceCurveSource> CurveSourceAdapter;`
- L249 _protected prototype_ `void UpdateLineSet();`
- L251 _protected member_ `bool bVisualizationChanged = false;`
- L253 _protected member_ `bool bSetupValid = false;`
- L254 _protected prototype_ `void InitializeMesh();`
- L256 _protected member_ `TUniquePtr<FGroupTopology> Topology;`
- L257 _protected prototype_ `void RecomputeTopology();`
- L259 _protected prototype_ `void OnPreviewMeshChanged();`
- L260 _protected member_ `FDelegateHandle OnPreviewMeshChangedHandle;`
- L265 _protected member_ `EEditGroomCardsToolActions PendingAction = EEditGroomCardsToolActions::NoAction;`
- L267 _protected member_ `int32 CurrentOperationTimestamp = 1;`
- L268 _protected function_ `bool CheckInOperation(int32 Timestamp) const`
- L270 _protected prototype_ `void CompleteMeshEditChange(const FText& TransactionLabel, TUniquePtr<FToolCommandChange> EditChange, const FGroupTopologySelection& OutputSelection);`
- L272 _protected prototype_ `void AfterTopologyEdit();`
- L273 _protected member_ `int32 ModifiedTopologyCounter = 0;`
- L274 _protected member_ `bool bWasTopologyEdited = false;`
- L276 _protected prototype_ `void ApplyDeleteAction();`
- L285 _public prototype_ `void ApplyGroomCardEdit(const FGroomCardEdit& Edit, bool bIsRevert);`

#### class `FEditGroomCardsTopologyPreEditChange`  
`class FEditGroomCardsTopologyPreEditChange : public FToolCommandChange`  
_L290-296_
- inherits: `FToolCommandChange`
- L293 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L294 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L295 _public prototype_ `virtual FString ToString() const override;`

#### class `FEditGroomCardsTopologyPostEditChange`  
`class FEditGroomCardsTopologyPostEditChange : public FToolCommandChange`  
_L298-304_
- inherits: `FToolCommandChange`
- L301 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L302 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L303 _public prototype_ `virtual FString ToString() const override;`

#### class `FBeginGroomCardsEditChange`  
`class FBeginGroomCardsEditChange : public FToolCommandChange`  
_L307-316_
- inherits: `FToolCommandChange`
- L310 _public member_ `int32 CardGroupID = -1;`
- L311 _public function_ `FBeginGroomCardsEditChange(int32 GroupID = 0)`
- L313 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L314 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L315 _public prototype_ `virtual FString ToString() const override;`

#### class `FEndGroomCardsEditChange`  
`class FEndGroomCardsEditChange : public FToolCommandChange`  
_L319-327_
- inherits: `FToolCommandChange`
- L322 _public member_ `TPimplPtr<FGroomCardEdit> CardEdit;`
- L324 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L325 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L326 _public prototype_ `virtual FString ToString() const override;`

### `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset/Public/GroomToMeshTool.h` (Public)


#### class `UGroomToMeshToolBuilder`  
`class UGroomToMeshToolBuilder : public UInteractiveToolBuilder`  
_L22-28_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- L26 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L27 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EGroomToMeshUVMode`  
`enum class EGroomToMeshUVMode`  
_L34-39_
- reflection: `UENUM()`
- L36 _public enumerator_ `PlanarSplitting = 1`
- L37 _public enumerator_ `MinimalConformal = 2`
- L38 _public enumerator_ `PlanarSplitConformal = 3`

#### class `UGroomToMeshToolProperties`  
`class UGroomToMeshToolProperties : public UInteractiveToolPropertySet`  
_L44-110_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L51 _public member_ `int32 VoxelCount = 64;` — `UPROPERTY(EditAnywhere, Category = Meshing, meta = (UIMin = "8", UIMax = "512", ClampMin = "8", ClampMax = "1024"))` — The size of the geometry bounding box major axis measured in voxels
- L54 _public member_ `float BlendPower = 1.0;` — `UPROPERTY(EditAnywhere, Category = Meshing, meta = (UIMin = "0.5", UIMax = "16.0", ClampMin = "0.1", ClampMax = "128.0"))`
- L57 _public member_ `float RadiusScale = 100.0;` — `UPROPERTY(EditAnywhere, Category = Meshing, meta = (UIMin = "0.1", UIMax = "200.0", ClampMin = "0.1", ClampMax = "2000.0"))`
- L61 _public member_ `bool bApplyMorphology = true;` — `UPROPERTY(EditAnywhere, Category = Morphology)`
- L64 _public member_ `float ClosingDist = 2.0;` — `UPROPERTY(EditAnywhere, Category = Morphology, meta = (UIMin = "0.0", UIMax = "50.0", ClampMin = "0.0", ClampMax = "128.0"))`
- L67 _public member_ `float OpeningDist = 0.25;` — `UPROPERTY(EditAnywhere, Category = Morphology, meta = (UIMin = "0.0", UIMax = "50.0", ClampMin = "0.0", ClampMax = "128.0"))`
- L72 _public member_ `bool bClipToHead = true;` — `UPROPERTY(EditAnywhere, Category = Clipping)`
- L76 _public member_ `TSoftObjectPtr<AStaticMeshActor> ClipMeshActor;` — `UPROPERTY(EditAnywhere, Category = Clipping)` — todo: this probably also needs to support skeletal mesh
- L80 _public member_ `bool bSmooth = true;` — `UPROPERTY(EditAnywhere, Category = Smoothing)`
- L83 _public member_ `float Smoothness = 0.15f;` — `UPROPERTY(EditAnywhere, Category = Smoothing, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))`
- L86 _public member_ `float VolumeCorrection = -0.25f;` — `UPROPERTY(EditAnywhere, Category = Smoothing, meta = (UIMin = "-1.0", UIMax = "1.0", ClampMin = "-2.0", ClampMax = "2.0"))`
- L90 _public member_ `bool bSimplify = false;` — `UPROPERTY(EditAnywhere, Category = Simplification)`
- L94 _public member_ `int VertexCount = 500;` — `UPROPERTY(EditAnywhere, Category = Simplification, meta = (UIMin = "4", UIMax = "5000", ClampMin = "1", ClampMax = "9999999999", EditCondition = "bSimplify == true"))` — Target triangle count
- L98 _public member_ `EGroomToMeshUVMode UVMode = EGroomToMeshUVMode::MinimalConformal;` — `UPROPERTY(EditAnywhere, Category = UVGeneration)`
- L102 _public member_ `bool bShowSideBySide = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L105 _public member_ `bool bShowGuides = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L108 _public member_ `bool bShowUVs = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`

#### class `UGroomToMeshTool`  
`class UGroomToMeshTool : public UInteractiveTool`  
_L118-271_
- reflection: `UCLASS()`
- inherits: `UInteractiveTool`
- L123 _public prototype_ `UGroomToMeshTool();`
- L125 _public function_ `virtual void SetWorld(UWorld* World)`
- L126 _public prototype_ `virtual void SetSelection(AGroomActor* Groom);`
- L128 _public prototype_ `virtual void Setup() override;`
- L129 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L131 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L132 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L134 _public function_ `virtual bool HasCancel() const override`
- L135 _public prototype_ `virtual bool HasAccept() const override;`
- L136 _public prototype_ `virtual bool CanAccept() const override;`
- L140 _protected member_ `TObjectPtr<UGroomToMeshToolProperties> Settings;` — `UPROPERTY()`
- L143 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L146 _protected member_ `TSoftObjectPtr<AGroomActor> TargetGroom;` — `UPROPERTY()`
- L149 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeom;` — `UPROPERTY()`
- L153 _protected member_ `TObjectPtr<UMaterialInterface> MeshMaterial;` — `UPROPERTY()`
- L156 _protected member_ `TObjectPtr<UMaterialInterface> UVMaterial;` — `UPROPERTY()`
- L159 _protected member_ `UWorld* TargetWorld = nullptr;`
- L161 _protected member_ `FDynamicMesh3 CurrentMesh;`
- L163 _protected prototype_ `void RecalculateMesh();`
- L165 _protected prototype_ `void UpdateLineSet();`
- L167 _protected member_ `bool bResultValid = false;`
- L168 _protected member_ `bool bVisualizationChanged = false;`
- L181 _protected member_ `FVoxelizeSettings CachedVoxelizeSettings;`
- L182 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> CurrentVoxelizeResult;`
- L183 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateVoxelization();`
- L199 _protected member_ `FMorphologySettings CachedMorphologySettings;`
- L200 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> CachedMorphologyResult;`
- L201 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateMorphology(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh);`
- L214 _protected member_ `FClipMeshSettings CachedClipMeshSettings;`
- L215 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> CachedClipMeshResult;`
- L216 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateClipMesh(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh);`
- L230 _protected member_ `FSmoothingSettings CachedSmoothSettings;`
- L231 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> CachedSmoothResult;`
- L232 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateSmoothing(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh);`
- L245 _protected member_ `FSimplifySettings CachedSimplifySettings;`
- L246 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> CachedSimplifyResult;`
- L247 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateSimplification(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh);`
- L260 _protected member_ `FPostprocessSettings CachedPostprocessSettings;`
- L261 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> CachedPostprocessResult;`
- L262 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdatePostprocessing(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh);`
- L265 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateUVs(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh, EGroomToMeshUVMode UVMode);`
- L267 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateUVs_ExpMapPlaneSplits(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh, bool bRecalcAsConformal);`
- L268 _protected prototype_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> UpdateUVs_MinimalConformal(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh);`
- L270 _protected prototype_ `void UpdatePreview(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> ResultMesh);`

#### struct `UGroomToMeshTool::FVoxelizeSettings`  
`struct FVoxelizeSettings`  
_L170-180_
- L172 _public member_ `int32 VoxelCount;`
- L173 _public member_ `float BlendPower;`
- L174 _public member_ `float RadiusScale;`
- L176 _public function_ `bool operator==(const FVoxelizeSettings& Other) const`

#### struct `UGroomToMeshTool::FMorphologySettings`  
`struct FMorphologySettings`  
_L187-198_
- L189 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L190 _public member_ `int32 VoxelCount;`
- L191 _public member_ `float CloseDist;`
- L192 _public member_ `float OpenDist;`
- L194 _public function_ `bool operator==(const FMorphologySettings& Other) const`

#### struct `UGroomToMeshTool::FClipMeshSettings`  
`struct FClipMeshSettings`  
_L204-213_
- L206 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L207 _public member_ `AActor* ClipSource;`
- L209 _public function_ `bool operator==(const FClipMeshSettings& Other) const`

#### struct `UGroomToMeshTool::FSmoothingSettings`  
`struct FSmoothingSettings`  
_L219-229_
- L221 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L222 _public member_ `float Smoothness;`
- L223 _public member_ `float VolumeCorrection;`
- L225 _public function_ `bool operator==(const FSmoothingSettings& Other) const`

#### struct `UGroomToMeshTool::FSimplifySettings`  
`struct FSimplifySettings`  
_L235-244_
- L237 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L238 _public member_ `int32 TargetCount;`
- L240 _public function_ `bool operator==(const FSimplifySettings& Other) const`

#### struct `UGroomToMeshTool::FPostprocessSettings`  
`struct FPostprocessSettings`  
_L250-259_
- L252 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L253 _public member_ `EGroomToMeshUVMode UVGenMode;`
- L255 _public function_ `bool operator==(const FPostprocessSettings& Other) const`

#### Free symbols / members of external scopes

- L16 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset/Public/HairModelingToolCommands.h` (Public)


#### class `FHairModelingToolCommands`  
`class FHairModelingToolCommands : public TCommands<FHairModelingToolCommands>`  
_L11-26_
- inherits: `TCommands<FHairModelingToolCommands>`
- desc: TInteractiveToolCommands implementation for this module that provides standard Editor hotkey support
- L14 _public prototype_ `FHairModelingToolCommands();`
- L16 _public member_ `TSharedPtr<FUICommandInfo> HairToolsTabButton;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> BeginGroomToMeshTool;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> BeginGenerateLODMeshesTool;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> BeginGroomCardsEditorTool;`
- L25 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset/Public/HairModelingToolsStyle.h` (Public)


#### class `FHairModelingToolsStyle`  
`class FHairModelingToolsStyle`  
_L9-24_
- L12 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L20 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L23 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Experimental/HairModelingToolset/Source/HairModelingToolset/Public/HairModelingToolsetModule.h` (Public)


#### class `FHairModelingToolsetModule`  
`class FHairModelingToolsetModule : public IModuleInterface, public IModelingModeToolExtension`  
_L9-22_
- inherits: `IModuleInterface,IModelingModeToolExtension`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual FText GetExtensionName() override;` — IModelingModeToolExtension implementation
- L19 _public prototype_ `virtual FText GetToolSectionName() override;`
- L20 _public prototype_ `virtual void GetExtensionTools(const FExtensionToolQueryInfo& QueryInfo, TArray<FExtensionToolDescription>& ToolsOut) override;`
- L21 _public prototype_ `virtual bool GetExtensionExtendedInfo(FModelingModeExtensionExtendedInfo& InfoOut) override;`
