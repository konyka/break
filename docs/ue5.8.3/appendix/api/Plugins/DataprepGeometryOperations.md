# Plugins / DataprepGeometryOperations

- module root: `Plugins/Experimental/Enterprise/DataprepGeometryOperations/Source`
- headers: 4; symbols: 81
- symbol kinds: class=9, delegate=1, enum=2, enumerator=5, function=11, member=31, prototype=22
- PrivateDependencyModuleNames: Core, CoreUObject, DataprepCore, DataprepLibraries, DynamicMesh, EditorScriptingUtilities, Engine, GeometryCore, MeshConversion, MeshDescription, MeshMergeUtilities, MeshModelingTools, MeshModelingToolsExp, MeshReductionInterface, MeshUtilitiesCommon, ModelingOperators, ModelingOperatorsEditorOnly, ProxyLODMeshReduction, StaticMeshDescription, UnrealEd

### `Plugins/Experimental/Enterprise/DataprepGeometryOperations/Source/Private/DataprepGeometryFilters.h` (Private)


#### class `UDataprepJacketingFilter`  
`class UDataprepJacketingFilter : public UDataprepFilterNoFetcher`  
_L14-47_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, HideCategories = (Filter), Meta = (DisplayName="Jacketing", ToolTip = "Apply mesh jacketing to selected objects"))`
- inherits: `UDataprepFilterNoFetcher`
- L19 _public function_ `UDataprepJacketingFilter()`
- L21 _public prototype_ `float GetAccuracy() const;`
- L22 _public prototype_ `float GetMergeDistance() const;`
- L24 _public prototype_ `void SetAccuracy(float NewAccuracy);`
- L25 _public prototype_ `void SetMergeDistance(float NewMergeDistance);`
- L28 _public prototype_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const override;`
- L29 _public prototype_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const override;`
- L30 _public prototype_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const override;`
- L31 _public function_ `virtual bool IsThreadSafe() const override`
- L32 _public prototype_ `virtual FText GetFilterCategoryText() const override;`
- L33 _public function_ `virtual bool UseFetchers() const`
- L37 _private prototype_ `void ExecuteJacketing(const TArrayView<UObject* const>& InputObjects, TArray<UObject*>& FilteredObjects, const TArrayView<bool>* OutFilterResults) const;`
- L42 _private member_ `float VoxelPrecision = 3.0f;` — `UPROPERTY(EditAnywhere, Category = JacketingFilter, meta = (Units = cm, UIMin = "0.1", UIMax = "100", ClampMin = "0"))` — Accuracy of the distance field approximation, in cm.
- L46 _private member_ `float GapMaxDiameter = 4.0f;` — `UPROPERTY(EditAnywhere, Category = JacketingFilter, meta = (Units = cm, UIMin = "0.1", UIMax = "100", ClampMin = "0"))` — Merge distance used to fill gap, in cm.

### `Plugins/Experimental/Enterprise/DataprepGeometryOperations/Source/Private/DataprepGeometryOperations.h` (Private)


#### class `UDataprepRemeshOperation`  
`class UDataprepRemeshOperation : public UDataprepEditingOperation`  
_L27-75_
- reflection: `UCLASS(Experimental, Category = ObjectOperation, Meta = (DisplayName="Remesh", ToolTip = "Experimental - Remesh input meshes"))`
- inherits: `UDataprepEditingOperation`
- L35 _public member_ `int TargetTriangleCount = 1000;` — `UPROPERTY(EditAnywhere, Category = Remeshing)` — Target triangle count
- L39 _public member_ `float SmoothingStrength = 0.25;` — `UPROPERTY(EditAnywhere, Category = Remeshing, meta = (DisplayName = "Smoothing Rate", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of Vertex Smoothing applied within Remeshing
- L43 _public member_ `bool bDiscardAttributes = false;` — `UPROPERTY(EditAnywhere, Category = Remeshing)` — Discard UVs and existing normals, allowing the remesher to ignore any UV and normal seams. New per-vertex normals are computed.
- L47 _public member_ `ERemeshType RemeshType = ERemeshType::Standard;` — `UPROPERTY(EditAnywhere, Category = Remeshing)` — Remeshing type
- L51 _public member_ `int RemeshIterations = 20;` — `UPROPERTY(EditAnywhere, Category = Remeshing, meta = (EditCondition = "RemeshType == ERemeshType::FullPass", UIMin = "0", UIMax = "50", ClampMin = "0", ClampMax = "1000"))` — Number of Remeshing passes
- L55 _public member_ `EMeshBoundaryConstraint MeshBoundaryConstraint = EMeshBoundaryConstraint::Free;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Boundary Constraints", meta = (DisplayName = "Mesh Boundary"))` — Mesh Boundary Constraint Type
- L59 _public member_ `EGroupBoundaryConstraint GroupBoundaryConstraint = EGroupBoundaryConstraint::Free;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Boundary Constraints", meta = (DisplayName = "Group Boundary"))` — Group Boundary Constraint Type
- L63 _public member_ `EMaterialBoundaryConstraint MaterialBoundaryConstraint = EMaterialBoundaryConstraint::Free;` — `UPROPERTY(EditAnywhere, Category = "Remeshing|Boundary Constraints", meta = (DisplayName = "Material Boundary"))` — Material Boundary Constraint Type
- L67 _public function_ `virtual FText GetCategory_Implementation() const override`
- L73 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepBakeTransformOperation`  
`class UDataprepBakeTransformOperation : public UDataprepEditingOperation`  
_L78-106_
- reflection: `UCLASS(Experimental, Category = ObjectOperation, Meta = (DisplayName="Bake Transform", ToolTip = "Experimental - Bake transform of input meshes"))`
- inherits: `UDataprepEditingOperation`
- L86 _public member_ `bool bBakeRotation = true;` — `UPROPERTY(EditAnywhere, Category = BakeTransform)` — Bake rotation
- L90 _public member_ `EBakeScaleMethod BakeScale = EBakeScaleMethod::BakeNonuniformScale;` — `UPROPERTY(EditAnywhere, Category = BakeTransform)` — Bake scale
- L94 _public member_ `bool bRecenterPivot = false;` — `UPROPERTY(EditAnywhere, Category = BakeTransform)` — Recenter pivot after baking transform
- L98 _public function_ `virtual FText GetCategory_Implementation() const override`
- L104 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepWeldEdgesOperation`  
`class UDataprepWeldEdgesOperation : public UDataprepEditingOperation`  
_L109-133_
- reflection: `UCLASS(Experimental, Category = ObjectOperation, Meta = (DisplayName="Weld Edges", ToolTip = "Experimental - Weld edges of input meshes"))`
- inherits: `UDataprepEditingOperation`
- L117 _public member_ `float Tolerance;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.000001", UIMax = "0.01", ClampMin = "0.00000001", ClampMax = "1000.0"))` — Merge search tolerance
- L121 _public member_ `bool bOnlyUnique;` — `UPROPERTY(EditAnywhere, Category = Options)` — Apply to only unique pairs
- L125 _public function_ `virtual FText GetCategory_Implementation() const override`
- L131 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSimplifyMeshOperation`  
`class UDataprepSimplifyMeshOperation : public UDataprepEditingOperation`  
_L136-172_
- reflection: `UCLASS(Experimental, Category = ObjectOperation, Meta = (DisplayName="Simplify Mesh", ToolTip = "Experimental - Simplify input meshes"))`
- inherits: `UDataprepEditingOperation`
- L144 _public member_ `int TargetPercentage = 50;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "100"))` — Target percentage of original triangle count
- L148 _public member_ `bool bDiscardAttributes = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Discard UVs and existing normals, allowing the simplifier to ignore any UV and normal seams. New per-vertex normals are computed.
- L152 _public member_ `EMeshBoundaryConstraint MeshBoundaryConstraint = EMeshBoundaryConstraint::Free;` — `UPROPERTY(EditAnywhere, Category = "SimplifyMesh|Boundary Constraints", meta = (DisplayName = "Mesh Boundary"))` — Mesh Boundary Constraint Type
- L156 _public member_ `EGroupBoundaryConstraint GroupBoundaryConstraint = EGroupBoundaryConstraint::Ignore;` — `UPROPERTY(EditAnywhere, Category = "SimplifyMesh|Boundary Constraints", meta = (DisplayName = "Group Boundary"))` — Group Boundary Constraint Type
- L160 _public member_ `EMaterialBoundaryConstraint MaterialBoundaryConstraint = EMaterialBoundaryConstraint::Ignore;` — `UPROPERTY(EditAnywhere, Category = "SimplifyMesh|Boundary Constraints", meta = (DisplayName = "Material Boundary"))` — Material Boundary Constraint Type
- L164 _public function_ `virtual FText GetCategory_Implementation() const override`
- L170 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### enum `EPlaneCutKeepSide`  
`enum class EPlaneCutKeepSide : uint8`  
_L175-180_
- reflection: `UENUM()`
- L177 _public enumerator_ `Positive`
- L178 _public enumerator_ `Negative`
- L179 _public enumerator_ `Both`

#### class `UDataprepPlaneCutOperation`  
`class UDataprepPlaneCutOperation : public UDataprepEditingOperation`  
_L183-266_
- reflection: `UCLASS(Experimental, Category = MeshOperation, Meta = (DisplayName="Plane Cut", ToolTip = "Experimental - Plane cut input meshes"))`
- inherits: `UDataprepEditingOperation`
- L189 _public function_ `UDataprepPlaneCutOperation()`
- L201 _public member_ `FVector CutPlaneOrigin;` — `UPROPERTY(EditAnywhere, Category = PlaneCut, meta = (DisplayName = "Plane's Origin"))` — Origin of the cutting plane
- L205 _public member_ `FVector CutPlaneNormalAngles;` — `UPROPERTY(EditAnywhere, Category = PlaneCut, meta = (DisplayName = "Plane's Orientation"))` — Euler angles of the normal to the cutting plane (default plane is XY plane)
- L211 _public member_ `EPlaneCutKeepSide CutPlaneKeepSide;` — `UPROPERTY(EditAnywhere, Category = PlaneCut, meta = (DisplayName = "Side(s) To Keep"))` — Specify which section(s) of the cut to keep. If 'Keep Both' is selected, both sides of the cut are computed and a new actor added with the negative side.
- L215 _public member_ `float SpacingBetweenHalves;` — `UPROPERTY(EditAnywhere, Category = PlaneCut, meta = (EditCondition = "CutPlaneKeepSide == EPlaneCutKeepSide::Both", UIMin = "0", ClampMin = "0"))` — If keeping both halves, separate the two pieces by this amount
- L219 _public member_ `bool bFillCutHole;` — `UPROPERTY(EditAnywhere, Category = PlaneCut, meta = (DisplayName = "Fill Holes"))` — If true, the cut surface is filled with simple planar hole fill surface(s)
- L223 _public member_ `bool bExportSeparatePieces;` — `UPROPERTY(EditAnywhere, Category = PlaneCut, meta = (DisplayName = "Export Separated Pieces As New Mesh Assets"))` — If true, meshes cut into multiple pieces will be saved as separate assets.
- L227 _public function_ `virtual FText GetCategory_Implementation() const override`
- L233 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`
- L242 _private prototype_ `UStaticMeshComponent* FinalizeStaticMeshActor( AStaticMeshActor* InActor, const FString& InMeshName, const FMeshDescription* InMeshDescription, int InNumMaterialSlots, const UStaticMesh* InOriginalMesh);` — Create new mesh component and assign new static mesh to it, and then add it to the Actor. If Actor is a AStaticMeshActor instance, then the new mesh component will be it's existing StaticMeshComponent, and we will assign the new static mesh to it. Otherwise, we create new StaticMeshComponent, assign NewStaticMesh, and set it as the Root Component of the Actor
- L249 _private prototype_ `TUniquePtr<FDynamicMesh3> CutStaticMesh( const FTransform& InTransform, const UStaticMesh* InStaticMesh);`
- L253 _private prototype_ `void PerformCutting( bool bKeepOriginalMesh, TArray<UStaticMesh*>& InStaticMeshes, const TArray<FTransform>& InCutPlaneTransforms, TArray<TArray<UStaticMeshComponent*>>& InReferencingComponentsToUpdate, TArray<UObject*>& OutModifiedStaticMeshes, TArray<UStaticMeshComponent*>& OutCutawayMeshes);`
- L262 _private prototype_ `TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator( const FTransform& InMeshLocalToWorld, TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> InOriginalMesh, float InMeshUVScaleFactor);` — Borrowed from UPlaneCutOperatorFactory::MakeNewOperator

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogDataprepGeometryOperations, Log, All );`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogDataprepGeometryOperations, Log, All );`

### `Plugins/Experimental/Enterprise/DataprepGeometryOperations/Source/Private/DataprepGeometrySelectionTransforms.h` (Private)


#### class `UDataprepOverlappingActorsSelectionTransform`  
`class UDataprepOverlappingActorsSelectionTransform : public UDataprepSelectionTransform`  
_L18-33_
- reflection: `UCLASS(Category = SelectionTransform, Meta = (DisplayName = "Select In Volume", ToolTip = "Return all actors overlapping the selected actors"))`
- inherits: `UDataprepSelectionTransform`
- L23 _protected prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects) override;`
- L28 _private member_ `float JacketingAccuracy = 3.0f;` — `UPROPERTY(EditAnywhere, Category = SelectionTransform, meta = (Units = cm, UIMin = "0.1", UIMax = "100", ClampMin = "0"))` — Accuracy of the distance field approximation
- L32 _private member_ `bool bSelectOverlapping = false;` — `UPROPERTY(EditAnywhere, Category = SelectionTransform)` — If checked, select fully inside + overlapping actors. Else, select only actors that are fully inside.

### `Plugins/Experimental/Enterprise/DataprepGeometryOperations/Source/Private/JacketingProcess.h` (Private)


#### enum `EJacketingTarget`  
`enum class EJacketingTarget : uint8`  
_L10-16_
- L13 _public enumerator_ `Level` — Apply jacketing on the level, will hide/tag/destroy actors and static mesh components.
- L15 _public enumerator_ `Mesh` — Apply jacketing on the mesh, will remove triangles/vertices.

#### class `FJacketingOptions`  
`class FJacketingOptions`  
_L18-38_
- L21 _public function_ `FJacketingOptions() : Accuracy(1.0F), MergeDistance(0.0F), Target(EJacketingTarget::Level)`
- L24 _public function_ `FJacketingOptions(float InAccuracy, float InMergeDistance, EJacketingTarget InTarget) : Accuracy(InAccuracy) , MergeDistance(InMergeDistance) , Target(InTarget)`
- L31 _public member_ `float Accuracy;` — Accuracy of the distance field approximation, in UE units.
- L34 _public member_ `float MergeDistance;` — Merge distance used to fill gap, in UE units.
- L37 _public member_ `EJacketingTarget Target;` — Target to apply the jacketing to.

#### class `FJacketingProcess`  
`class FJacketingProcess`  
_L40-53_
- L43 _public prototype_ `static void ApplyJacketingOnMeshActors(const TArray<AActor*>& Actors, const FJacketingOptions* Options, TArray<AActor*>& OccludedActorArray, bool bSilent);`
- L52 _public prototype_ `static void FindOverlappingActors(const TArray<AActor*>& InActorsToTest, const TArray<AActor*>& InActorsToTestAgainst, const FJacketingOptions* Options, TArray<AActor*>& OutOverlappingActors, bool bSilent);` — Find the set of all actors that overlap any of the actors in another set. @param	InActorsToTest			Input actors to test for overlap. @param	InActorsToTestAgainst	Input actors to test against. Each actor in InActorsToTest will be tested against the volume built from InActorsToTestAgainst. @param	Options					Parameter values to use for the overlapping. @param	OutOverlappingActors	The actors that pass the overlap test (a subset from InActorsToTest). @param	bSilent					Enable/disable progress dialog.
